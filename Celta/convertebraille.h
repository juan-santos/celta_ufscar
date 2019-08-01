#ifndef CONVERTEBRAILLE_H
#define CONVERTEBRAILLE_H

#include <QString>
#define CODIGO_NUMERICO '*'

class ConverteBraille {
    public:
        ConverteBraille();
        static QString convertTextToBraille(const QString);

    private:

};

#endif // CONVERTEBRAILLE_H
