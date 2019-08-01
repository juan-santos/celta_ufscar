#include "convertebraille.h"

ConverteBraille::ConverteBraille() {

}

QString ConverteBraille::convertTextToBraille(const QString texto){
    QString aux = "";

    for (int i = 0; i < texto.size(); i++) {

        //caracteres numéricos
        if(texto.at(i) >= 48 && texto.at(i) <= 57){
            aux.append(CODIGO_NUMERICO);
        }

        //caracteres maiusculos
        if(texto.at(i) >= 65 && texto.at(i) <= 90){

        }

        aux.append(texto.at(i));
    }

    return aux;
}
