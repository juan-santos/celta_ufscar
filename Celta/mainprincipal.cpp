#include "mainprincipal.h"
#include "ui_mainprincipal.h"
#include <QDebug>

MainPrincipal::MainPrincipal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainPrincipal) {
    ui->setupUi(this);
    arduino = new Arduino();

    //controles possíveis
    setControlsEnabled(true);
}

//Celta
MainPrincipal::~MainPrincipal() {
    delete ui;
}

void MainPrincipal::on_btnIniciar_clicked() {

   // arduino->iniciarLeitura(ui->txtTexto->toPlainText());
   setControlsEnabled(false);
}

void MainPrincipal::on_btnPausar_clicked() {
    arduino->reconectarArduino();
    setControlsEnabled(true);
}

void MainPrincipal::on_btnParar_clicked() {
    arduino->pararLeitura();
    setControlsEnabled(true);
}

void MainPrincipal::setControlsEnabled(bool enable)
{
    ui->btnParar->setEnabled(!enable);
    ui->btnPausar->setEnabled(!enable);
    ui->btnIniciar->setEnabled(enable);
    ui->txtTexto->setEnabled(enable);
    ui->qSliderVelocimetro->setEnabled(enable);
}
