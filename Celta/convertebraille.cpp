#include "convertebraille.h"
#include <QDebug>

ConverteBraille::ConverteBraille() {

}

QString ConverteBraille::convertTextToBraille(const QString texto){
    QString aux = "";

    for (int i = 0; i < texto.size(); i++) {

        //caracteres numéricos
        if(texto.at(i) >= 48 && texto.at(i) <= 57){
            aux.append(QChar(CODIGO_NUMERICO));
            aux.append(texto.at(i));
            continue;
        } else{

            qDebug() << texto.at(i);
            //caracteres maiusculos
            if(texto.at(i) >= 65 && texto.at(i) <= 90){

                aux.append(QChar(CODIGO_MAIUSCULO));
                aux.append(texto.at(i).toLower());
                continue;
            }
        }

        aux.append(texto.at(i));
    }

    return aux;
}
