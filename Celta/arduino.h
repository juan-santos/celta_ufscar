#ifndef ARDUINO_H
#define ARDUINO_H

#include <QMutex>
#include <QThread>
#include <QWaitCondition>
#include <QSerialPort>

class Arduino : public QThread {

    Q_OBJECT

public:
    explicit Arduino(QObject *parent = nullptr);
    ~Arduino() override;
    void transaction(const QChar &request, int waitTimeout);
    void stopLeitura();

signals:
    void response(const QString &s);
    void error(const QString &s);
    void timeout(const QString &s);

private:

    void run() override;
    int m_waitTimeout = 0;
    QMutex m_mutex;
    QWaitCondition m_cond;
    bool m_quit = false;
    QChar m_request;

    static const quint16 arduino_uno_vendor_id = 9025;
    static const quint16 arduino_uno_product_id = 67;

    bool conectarArduino(QSerialPort *arduino);
    QString escreveLetra(const QChar &letra);

};

#endif // ARDUINO_H
