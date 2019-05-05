#include "arduino.h"
#include <QtWidgets>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

Arduino::Arduino(QObject *parent): QThread(parent) {
}

Arduino::~Arduino() {
    m_mutex.lock();
        m_quit = true;
        m_cond.wakeOne();
    m_mutex.unlock();

    wait();
}

void Arduino::transaction(const QChar &request, int waitTimeout) {
    const QMutexLocker locker(&m_mutex);
    m_request = request;
    m_waitTimeout = waitTimeout;
    if (!isRunning())
        start();
    else
        m_cond.wakeOne();
}

void Arduino::run() {
    QSerialPort arduino;

    m_mutex.lock();
        QChar currentRequest = m_request;
        int waitTimeout = m_waitTimeout;

        if(!conectarArduino(&arduino)){
            emit error(tr("Arduino não está conectado"));
            m_mutex.unlock();
            return;
        }

        if (!arduino.open(QSerialPort::ReadWrite)) {
            emit error(tr("Não foi possível abrir conexão de escrita/leitura com o Arduino"));
            m_mutex.unlock();
            return;
        }
    m_mutex.unlock();

    while (!m_quit) {

        m_mutex.lock();
            if(!arduino.isOpen()){
                this->conectarArduino(&arduino);
                if (!arduino.open(QSerialPort::ReadWrite)) {
                    emit error(tr("Não foi possível abrir conexão de escrita/leitura com o Arduino"));
                    m_mutex.unlock();
                    return;
                }
            }
        m_mutex.unlock();

        QString comando = this->escreveLetra(currentRequest);
        arduino.write(comando.toStdString().c_str());

        qDebug() << "Letra " << currentRequest << "comando " << comando;

        if (arduino.waitForBytesWritten(waitTimeout)) {
            if (arduino.waitForReadyRead(waitTimeout)) {// ler resposta
                QByteArray responseData = arduino.readAll();
                while (arduino.waitForReadyRead(10)){
                    responseData += arduino.readAll();
                }

                const QString response = QString::fromUtf8(responseData);
                emit this->response("Letra finalizada");

                qDebug() << "Resposta " << response;

            } else {
                emit timeout(tr("Ultrapassou tempo de leitura"));
            }

        } else {
            emit timeout(tr("Ultrapassou tempo de escrita"));
        }

        //this->sleep(3);

        m_mutex.lock();
            m_cond.wait(&m_mutex);
            currentRequest = m_request;
            waitTimeout = m_waitTimeout;
        m_mutex.unlock();
    }
}

bool Arduino::conectarArduino(QSerialPort *arduino){

    //se não for nulo, apago o ponteiro da antiga conexão
    if(arduino->isOpen()){
       delete arduino ;
       arduino = new QSerialPort();
    }

    bool arduino_is_available = false;
    QString arduino_port_name = "";

    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
            if((serialPortInfo.vendorIdentifier() == arduino_uno_vendor_id) &&
                    (serialPortInfo.productIdentifier() == arduino_uno_product_id)){
                arduino_port_name = serialPortInfo.portName();
                arduino_is_available = true;
            }
        }
    }

    if(arduino_is_available){
        arduino->setPortName(arduino_port_name);
        arduino->setBaudRate(QSerialPort::Baud9600);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
        return true;
    }

    return false;
}

QString Arduino::escreveLetra(const QChar &letra){

    if (letra == 'a'){
        return "d0l1";
    }

    if (letra == 'b'){
        return "d0l1l2";
    }

    if (letra == 'c'){
        return "d0l1l4";
    }

    if (letra == ' '){
        return "d0";
    }

    return "d0";
}

void Arduino::stopLeitura(){
    this->m_quit = true;
}
