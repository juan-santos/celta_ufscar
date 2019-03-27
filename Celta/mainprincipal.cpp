#include "mainprincipal.h"
#include "ui_mainprincipal.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QtWidgets>
#include <QThread>

MainPrincipal::MainPrincipal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainPrincipal) {

    arduino_is_available = false;
    arduino_port_name = "";

    ui->setupUi(this);
    arduino = new QSerialPort();

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
        arduino->open(QSerialPort::WriteOnly);
        arduino->setBaudRate(QSerialPort::Baud9600);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
    } else{
        QMessageBox::warning(this,"Erro na comunicação", "Não foi possivel encontrar o arduíno. Verifique a conexão e tente novamente");
    }

}

//Celta

MainPrincipal::~MainPrincipal() {
    if(arduino->isOpen()){
        arduino->close();
    }
    delete ui;
}

void MainPrincipal::on_btnIniciar_clicked() {

    for(int i = 0; i < ui->txtTexto->toPlainText().size();i++){
        escreveLetra(ui->txtTexto->toPlainText().at(i));
        //QThread::sleep(1000);
    }

}

void MainPrincipal::on_btnPausar_clicked() {

}

void MainPrincipal::on_btnParar_clicked() {
    //desativo todos os pontos
    this->updateArduino(QString("d1"));
    this->updateArduino(QString("d2"));
    this->updateArduino(QString("d3"));
    this->updateArduino(QString("d4"));
    this->updateArduino(QString("d5"));
    this->updateArduino(QString("d6"));
}

void MainPrincipal::updateArduino(QString command) {
    if(arduino->isWritable()){
         arduino->write(command.toStdString().c_str());
    } else{
        qDebug() << "Não foi possível enviar a informação ao arduíno!";
    }
}

void MainPrincipal::escreveLetra(QChar letra){

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
