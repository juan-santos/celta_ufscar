#ifndef MAINPRINCIPAL_H
#define MAINPRINCIPAL_H

#include <QMainWindow>
#include "arduino.h"
#include <thread>

namespace Ui {
class MainPrincipal;
}

class MainPrincipal : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainPrincipal(QWidget *parent = nullptr);
    ~MainPrincipal();

private slots:
    void on_btnIniciar_clicked();
    void on_btnPausar_clicked();
    void on_btnParar_clicked();

private:

    void setControlsEnabled(bool enable);

    Ui::MainPrincipal *ui;
    Arduino *arduino;

    std::thread execucao;
};

#endif // MAINPRINCIPAL_H
