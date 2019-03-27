#ifndef MAINPRINCIPAL_H
#define MAINPRINCIPAL_H

#include <QMainWindow>
#include <QSerialPort>
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

    void updateArduino(QString command);

    void escreveLetra(QChar letra);

private:
    Ui::MainPrincipal *ui;
    QSerialPort *arduino;
    static const quint16 arduino_uno_vendor_id = 9025;
    static const quint16 arduino_uno_product_id = 67;
    QString arduino_port_name;
    bool arduino_is_available;
};

#endif // MAINPRINCIPAL_H
