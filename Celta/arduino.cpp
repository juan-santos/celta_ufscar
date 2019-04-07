#include "arduino.h"
#include <QtWidgets>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

Arduino::Arduino() {
    this->conectarArduino();
}

Arduino::~Arduino() {
    if(conexao->isOpen()){
        conexao->close();
    }
}

void Arduino::conectarArduino(){
    conexao = new QSerialPort();
    arduino_is_available = false;
    arduino_port_name = "";

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
        conexao->setPortName(arduino_port_name);
        conexao->open(QSerialPort::WriteOnly);
        conexao->setBaudRate(QSerialPort::Baud9600);
        conexao->setDataBits(QSerialPort::Data8);
        conexao->setParity(QSerialPort::NoParity);
        conexao->setStopBits(QSerialPort::OneStop);
        conexao->setFlowControl(QSerialPort::NoFlowControl);
    }
}

void Arduino::reconectarArduino(){
    if(conexao->isOpen()){
        conexao->close();
    }

    this->conectarArduino();
}

void Arduino::iniciarLeitura(QString texto){

    for(int i = 0; i < texto.size();i++){
        escreveLetra(texto.at(i));
    }

}

void Arduino::pausarLeitura(){

}

void Arduino::reiniciarLeitura(){

}

void Arduino::pararLeitura(){
    this->updateArduino(QString("d0"));
}

void Arduino::escreveLetra(QChar letra){

    if (letra == 'a'){
        this->updateArduino(QString("l1"));
        this->updateArduino(QString("d2"));
        this->updateArduino(QString("d3"));
        this->updateArduino(QString("d4"));
        this->updateArduino(QString("d5"));
        this->updateArduino(QString("d6"));
        return;
    }
    if (letra == 'b'){
        this->updateArduino(QString("l1"));
        this->updateArduino(QString("l2"));
        this->updateArduino(QString("d3"));
        this->updateArduino(QString("d4"));
        this->updateArduino(QString("d5"));
        this->updateArduino(QString("d6"));
        return;
    }
    if (letra == 'c'){
        this->updateArduino(QString("l1"));
        this->updateArduino(QString("d2"));
        this->updateArduino(QString("d3"));
        this->updateArduino(QString("l4"));
        this->updateArduino(QString("d5"));
        this->updateArduino(QString("d6"));
        return;
    }
    if (letra == 'd'){
        this->updateArduino(QString("l1"));
        this->updateArduino(QString("d2"));
        this->updateArduino(QString("d3"));
        this->updateArduino(QString("l4"));
        this->updateArduino(QString("l5"));
        this->updateArduino(QString("d6"));
        return;
    }
    if (letra == 'e'){
        this->updateArduino(QString("l1"));
        this->updateArduino(QString("d2"));
        this->updateArduino(QString("d3"));
        this->updateArduino(QString("d4"));
        this->updateArduino(QString("l5"));
        this->updateArduino(QString("d6"));
        return;
    }
    if (letra == 'f'){
        this->updateArduino(QString("l1"));
        this->updateArduino(QString("l2"));
        this->updateArduino(QString("d3"));
        this->updateArduino(QString("l4"));
        this->updateArduino(QString("d5"));
        this->updateArduino(QString("d6"));
        return;
    }
    if (letra == 'g'){
        this->updateArduino(QString("l1"));
        this->updateArduino(QString("l2"));
        this->updateArduino(QString("d3"));
        this->updateArduino(QString("l4"));
        this->updateArduino(QString("l5"));
        this->updateArduino(QString("d6"));
        return;
    }
    if (letra == 'h'){
        this->updateArduino(QString("l1"));
        this->updateArduino(QString("l2"));
        this->updateArduino(QString("d3"));
        this->updateArduino(QString("d4"));
        this->updateArduino(QString("l5"));
        this->updateArduino(QString("d6"));
        return;
    }
    if (letra == 'i'){
        this->updateArduino(QString("d1"));
        this->updateArduino(QString("l2"));
        this->updateArduino(QString("d3"));
        this->updateArduino(QString("l4"));
        this->updateArduino(QString("d5"));
        this->updateArduino(QString("d6"));
        return;
    }
    if (letra == 'j'){
        this->updateArduino(QString("d1"));
        this->updateArduino(QString("l2"));
        this->updateArduino(QString("d3"));
        this->updateArduino(QString("l4"));
        this->updateArduino(QString("l5"));
        this->updateArduino(QString("d6"));
        return;
    }
    if (letra == 'k'){
        this->updateArduino(QString("l1"));
        this->updateArduino(QString("d2"));
        this->updateArduino(QString("l3"));
        this->updateArduino(QString("d4"));
        this->updateArduino(QString("d5"));
        this->updateArduino(QString("d6"));
        return;
    }
    if (letra == 'l'){
        this->updateArduino(QString("l1"));
        this->updateArduino(QString("l2"));
        this->updateArduino(QString("l3"));
        this->updateArduino(QString("d4"));
        this->updateArduino(QString("d5"));
        this->updateArduino(QString("d6"));
        return;
    }
    if (letra == 'm'){
        this->updateArduino(QString("l1"));
        this->updateArduino(QString("d2"));
        this->updateArduino(QString("l3"));
        this->updateArduino(QString("l4"));
        this->updateArduino(QString("d5"));
        this->updateArduino(QString("d6"));
        return;
    }
    if (letra == 'n'){
        this->updateArduino(QString("l1"));
        this->updateArduino(QString("d2"));
        this->updateArduino(QString("l3"));
        this->updateArduino(QString("l4"));
        this->updateArduino(QString("l5"));
        this->updateArduino(QString("d6"));
        return;
    }
    if (letra == 'o'){
        this->updateArduino(QString("l1"));
        this->updateArduino(QString("d2"));
        this->updateArduino(QString("l3"));
        this->updateArduino(QString("d4"));
        this->updateArduino(QString("l5"));
        this->updateArduino(QString("d6"));
        return;
    }
    if (letra == 'p'){
        this->updateArduino(QString("l1"));
        this->updateArduino(QString("l2"));
        this->updateArduino(QString("l3"));
        this->updateArduino(QString("l4"));
        this->updateArduino(QString("d5"));
        this->updateArduino(QString("d6"));
        return;
    }
    if (letra == 'q'){
        this->updateArduino(QString("l1"));
        this->updateArduino(QString("l2"));
        this->updateArduino(QString("l3"));
        this->updateArduino(QString("l4"));
        this->updateArduino(QString("l5"));
        this->updateArduino(QString("d6"));
        return;
    }
    if (letra == 'r'){
        this->updateArduino(QString("l1"));
        this->updateArduino(QString("l2"));
        this->updateArduino(QString("l3"));
        this->updateArduino(QString("d4"));
        this->updateArduino(QString("l5"));
        this->updateArduino(QString("d6"));
        return;
    }
    if (letra == 's'){
        this->updateArduino(QString("d1"));
        this->updateArduino(QString("l2"));
        this->updateArduino(QString("l3"));
        this->updateArduino(QString("l4"));
        this->updateArduino(QString("d5"));
        this->updateArduino(QString("d6"));
        return;
    }
    if (letra == 't'){
        this->updateArduino(QString("d1"));
        this->updateArduino(QString("l2"));
        this->updateArduino(QString("l3"));
        this->updateArduino(QString("l4"));
        this->updateArduino(QString("l5"));
        this->updateArduino(QString("d6"));
        return;
    }
    if (letra == 'u'){
        this->updateArduino(QString("l1"));
        this->updateArduino(QString("d2"));
        this->updateArduino(QString("l3"));
        this->updateArduino(QString("d4"));
        this->updateArduino(QString("d5"));
        this->updateArduino(QString("l6"));
        return;
    }
    if (letra == 'v'){
        this->updateArduino(QString("l1"));
        this->updateArduino(QString("l2"));
        this->updateArduino(QString("l3"));
        this->updateArduino(QString("d4"));
        this->updateArduino(QString("d5"));
        this->updateArduino(QString("l6"));
        return;
    }
    if (letra == 'w'){
        this->updateArduino(QString("d1"));
        this->updateArduino(QString("l2"));
        this->updateArduino(QString("d3"));
        this->updateArduino(QString("l4"));
        this->updateArduino(QString("l5"));
        this->updateArduino(QString("l6"));
        return;
    }
    if (letra == 'x'){
        this->updateArduino(QString("l1"));
        this->updateArduino(QString("d2"));
        this->updateArduino(QString("l3"));
        this->updateArduino(QString("l4"));
        this->updateArduino(QString("d5"));
        this->updateArduino(QString("l6"));
        return;
    }
    if (letra == 'y'){
        this->updateArduino(QString("l1"));
        this->updateArduino(QString("d2"));
        this->updateArduino(QString("l3"));
        this->updateArduino(QString("l4"));
        this->updateArduino(QString("l5"));
        this->updateArduino(QString("l6"));
        return;
    }
    if (letra == 'z'){
        this->updateArduino(QString("l1"));
        this->updateArduino(QString("d2"));
        this->updateArduino(QString("l3"));
        this->updateArduino(QString("d4"));
        this->updateArduino(QString("l5"));
        this->updateArduino(QString("l6"));
        return;
    }

    this->updateArduino(QString("d1"));
    this->updateArduino(QString("d2"));
    this->updateArduino(QString("d3"));
    this->updateArduino(QString("d4"));
    this->updateArduino(QString("d5"));
    this->updateArduino(QString("d6"));
    return;

}

void Arduino::updateArduino(QString command) {
    if(conexao->isWritable()){
         conexao->write(command.toStdString().c_str());
    } else{
        qDebug() << "Não foi possível enviar a informação ao arduíno!";
    }
}
