#include "mainprincipal.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainPrincipal w;
    w.setFixedSize(615,430);
    w.show();

    return a.exec();
}
