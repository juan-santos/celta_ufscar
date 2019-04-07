#ifndef ARDUINO_H
#define ARDUINO_H

#include <QSerialPort>

class Arduino {

public:
    Arduino();
    ~Arduino();

    void reconectarArduino();

    //opções de leitura
    void iniciarLeitura(QString texto);
    void reiniciarLeitura();
    void pausarLeitura();
    void pararLeitura();

private:
    void conectarArduino();
    void updateArduino(QString command);
    void escreveLetra(QChar letra);

    QSerialPort *conexao;
    static const quint16 arduino_uno_vendor_id = 9025;
    static const quint16 arduino_uno_product_id = 67;
    QString arduino_port_name;
    bool arduino_is_available;

};

#endif // ARDUINO_H
