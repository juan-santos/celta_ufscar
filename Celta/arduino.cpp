#include "arduino.h"
#include <QtWidgets>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

Arduino::Arduino(QObject *parent): QThread(parent) {
}

Arduino::~Arduino() {
    m_mutex.lock();
        this->finalizarThread();
        m_cond.wakeOne();
    m_mutex.unlock();

    wait();
}

void Arduino::finalizarThread(){
    this->m_quit = true;
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

void Arduino::transaction() {
    const QMutexLocker locker(&m_mutex);

    if (!isRunning())
        start();
    else
        m_cond.wakeOne();
}

void Arduino::run() {
    QSerialPort arduino;

    m_mutex.lock();
        QString currentRequest = m_request;
        int waitTimeout = 50;

        if(!conectarArduino(&arduino)){

            m_mutex.unlock();
            return;
        }

        if (!arduino.open(QSerialPort::ReadWrite)) {
            m_mutex.unlock();
            return;
        }
    m_mutex.unlock();

    int atual = -1, anterior = -1, reiniciar = 0;
    while (!m_quit) {

        m_mutex.lock();

        if (arduino.waitForReadyRead(waitTimeout)) {

            QByteArray responseData = arduino.readAll();
            while (arduino.waitForReadyRead(10)){
                responseData += arduino.readAll();
            }

            const QString response = QString::fromUtf8(responseData);

            if(response == "+1" || response == "++1"){

                reiniciar = 0;

                if(atual+1 < m_request.size()){
                    atual++;
                }

            } else{

                if(response == "-1" || response == "--1"){

                    reiniciar = 0;

                    if(atual > 0){
                        atual--;
                    }
                }

                if(response == "+0" || response == "++0"){
                    anterior = -1;
                    atual = -1;
                    reiniciar++;
                    emit selecionarLetra(-1);
                }
            }

            //qDebug() << " Leitura " << response;
        }

        if(reiniciar >= 2){
            anterior = -1;
            atual = -1;
            reiniciar = 0;

            emit reiniciarLeitura();
        }

        if(atual != anterior){
            anterior = atual;

            emit selecionarLetra(atual);

            QString comando = this->escreveLetra(this->m_request.at(atual));
            arduino.write(comando.toStdString().c_str());

            if (arduino.waitForBytesWritten(waitTimeout)) {
                if (arduino.waitForReadyRead(waitTimeout)) { // ler resposta
                    QByteArray responseData = arduino.readAll();
                    while (arduino.waitForReadyRead(10)){
                        responseData += arduino.readAll();
                    }

                    const QString response = QString::fromUtf8(responseData);
                }
            } else{

            }
        }

        this->sleep(1);
        m_mutex.unlock();
    }
}

QString Arduino::escreveLetra(const QChar &letra){
    if (letra == ' '){
        return "d0";
    }
    if (letra == 'a'){
        return "l1d2d3d4d5d6";
    }
    if (letra == 'b'){
        return "l1l2d3d4d5d6";
    }
    if (letra == 'c'){
        return "l1d2d3l4d5d6";
    }
    if (letra == 'd'){
        return "l1d2d3l4l5d6";
    }
    if (letra == 'e'){
        return "l1d2d3d4l5d6";
    }
    if (letra == 'f'){
        return "l1l2d3l4d5d6";
    }
    if (letra == 'g'){
        return "l1l2d3l4l5d6";
    }
    if (letra == 'h'){
        return "l1l2d3d4l5d6";
    }
    if (letra == 'i'){
        return "d1l2d3l4d5d6";
    }
    if (letra == 'j'){
        return "d1l2d3l4l5d6";
    }
    if (letra == 'k'){
        return "l1d2l3d4d5d6";
    }
    if (letra == 'l'){
        return "l1l2l3d4d5d6";
    }
    if (letra == 'm'){
        return "l1d2l3l4d5d6";
    }
    if (letra == 'n'){
        return "l1d2l3l4l5d6";
    }
    if (letra == 'o'){
        return "l1d2l3d4l5d6";
    }
    if (letra == 'p'){
        return "l1l2l3l4d5d6";
    }
    if (letra == 'q'){
        return "l1l2l3l4l5d6";
    }
    if (letra == 'r'){
        return "l1l2l3d4l5d6";
    }
    if (letra == 's'){
        return "d1l2l3l4d5d6";
    }
    if (letra == 't'){
        return "d1l2l3l4l5d6";
    }
    if (letra == 'u'){
        return "l1d2l3d4d5l6";
    }
    if (letra == 'v'){
        return "l1l2l3d4d5l6";
    }
    if (letra == 'w'){
        return "d1l2d3l4l5l6";
    }
    if (letra == 'x'){
        return "l1d2l3l4d5l6";
    }
    if (letra == 'y'){
        return "l1d2l3l4l5l6";
    }
    if (letra == 'z'){
        return "l1d2l3d4l5l6";
    }

    if (letra == '('){
        return "";
    }
    if (letra == ')'){
        return "";
    }

    if (letra == '0'){
        return "";
    }
    if (letra == '1'){
        return "";
    }
    if (letra == '2'){
        return "";
    }
    if (letra == '3'){
        return "";
    }
    if (letra == '4'){
        return "";
    }
    if (letra == '5'){
        return "";
    }
    if (letra == '6'){
        return "";
    }
    if (letra == '7'){
        return "";
    }
    if (letra == '8'){
        return "";
    }
    if (letra == '9'){
        return "";
    }

    return "d0";
}

void Arduino::setText(const QString texto) {
    this->m_request = texto;
}
