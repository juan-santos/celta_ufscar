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

void Arduino::transaction(const QString &request) {
    const QMutexLocker locker(&m_mutex);
    m_request = request;

    if (!isRunning())
        start();
    else
        m_cond.wakeOne();
}

void Arduino::run() {
    qDebug() << "Executando...";
    QString currentRequest = m_request;
    QSerialPort arduino;

    if(conectarArduino(&arduino)){
        qDebug() << "Conectou!";
    } else{
        emit error(tr("Arduino desconectado"));
        return;
    }

    if (!arduino.open(QSerialPort::ReadWrite)) {
        emit error(tr("Não foi possível abrir conexão de escrita/leitura com o Arduino"));
        return;
    }

    int i = 0;
    while (!m_quit && i < currentRequest.size()) {

        m_mutex.lock();

            qDebug() << "Letra " << currentRequest.at(i);

            QString comando = this->escreveLetra(currentRequest.at(i++));
            arduino.write(comando.toStdString().c_str());
            qDebug() << "comando " << comando;
            this->sleep(3);

            if (arduino.waitForBytesWritten(this->m_waitTimeout)) {

                // ler resposta
                if (arduino.waitForReadyRead(this->m_waitTimeout)) {
                    QByteArray responseData = arduino.readAll();
                    while (arduino.waitForReadyRead(10))
                        responseData += arduino.readAll();

                    const QString response = QString::fromUtf8(responseData);
                    qDebug() << "Resposta " << response;

                } else {
                    emit timeout(tr("Tempo de leitura ultrapassado"));
                    m_mutex.unlock();
                }

            } else{
                emit timeout(tr("Tempo de escrita ultrapassado"));
                m_mutex.unlock();
            }


        m_mutex.unlock();
    }

    emit this->response("Escrita finalizada com sucesso");
    QString comando = this->escreveLetra(' ');
    arduino.write(comando.toStdString().c_str());

    if(arduino.isOpen()){
        arduino.close();
    }
}

bool Arduino::conectarArduino(QSerialPort *arduino){
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
