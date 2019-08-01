#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "arduino.h"
#include "convertebraille.h"

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
    void textChanged();
    void reiniciarLeitura();
    void selectLetra(const int);

private:
    Ui::Dialog *ui;
    Arduino arduino;
};


#endif // DIALOG_H
