#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "arduino.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_btnIniciar_clicked();
    void on_btnPausar_clicked();
    void on_btnParar_clicked();

    void showResponse(const QString &s);
    void processError(const QString &s);
    void processTimeout(const QString &s);

private:

    void setControlsEnabled(bool enable);
    Ui::Dialog *ui;
    Arduino arduino;
};


#endif // DIALOG_H
