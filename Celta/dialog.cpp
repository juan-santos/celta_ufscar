#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog) {
    ui->setupUi(this);

    connect(&arduino, &Arduino::response, this, &Dialog::showResponse);
    connect(&arduino, &Arduino::error, this, &Dialog::processError);
    connect(&arduino, &Arduino::timeout, this, &Dialog::processTimeout);

    //deixo com tudo desativado como valor inicial
    arduino.transaction(' ', 100);

    //controles possíveis
    setControlsEnabled(true);
}

//Celta
Dialog::~Dialog() {
    delete ui;
}

void Dialog::on_btnIniciar_clicked() {

   for(int i = 0; i < ui->txtTexto->toPlainText().size();i++){
      arduino.transaction(ui->txtTexto->toPlainText().at(i), 3000);
      arduino.sleep(3);
   }

   setControlsEnabled(false);
}

void Dialog::on_btnPausar_clicked() {
    setControlsEnabled(true);
}

void Dialog::on_btnParar_clicked() {
    this->arduino.stopLeitura();
    setControlsEnabled(true);
}

void Dialog::setControlsEnabled(bool enable) {
    ui->btnParar->setEnabled(!enable);
    ui->btnPausar->setEnabled(!enable);
    ui->btnIniciar->setEnabled(enable);
    ui->txtTexto->setEnabled(enable);
    ui->qSliderVelocimetro->setEnabled(enable);
}

void Dialog::showResponse(const QString &s) {
    qDebug() << s;
    setControlsEnabled(true);
}

void Dialog::processError(const QString &s) {
    qDebug() << s;
    setControlsEnabled(true);
}

void Dialog::processTimeout(const QString &s){
    qDebug() << s;
    setControlsEnabled(true);
}
