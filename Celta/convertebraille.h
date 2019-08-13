#ifndef CONVERTEBRAILLE_H
#define CONVERTEBRAILLE_H

#include <QString>
#define CODIGO_NUMERICO 0x0002E9
#define CODIGO_MAIUSCULO  0x00035D

class ConverteBraille {
    public:
        ConverteBraille();
        static QString convertTextToBraille(const QString);

    private:

};

#endif // CONVERTEBRAILLE_H
