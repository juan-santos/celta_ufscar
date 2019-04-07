#include "mainprincipal.h"
#include "ui_mainprincipal.h"
#include <QDebug>

MainPrincipal::MainPrincipal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainPrincipal) {
    ui->setupUi(this);
    arduino = new Arduino();
}

//Celta
MainPrincipal::~MainPrincipal() {
    delete ui;
}

void MainPrincipal::on_btnIniciar_clicked() {
    arduino->iniciarLeitura(ui->txtTexto->toPlainText());
}

void MainPrincipal::on_btnPausar_clicked() {
    arduino->reconectarArduino();
}

void MainPrincipal::on_btnParar_clicked() {
    arduino->pararLeitura();
}
