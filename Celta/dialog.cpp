#include "dialog.h"
#include "ui_dialog.h"
#include <QClipboard>
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog) {
    ui->setupUi(this);

    //finalizar thread ao encerrar o programa
    connect(this, &Dialog::rejected, &arduino, &Arduino::finalizarThread);

    //alterar o conteúdo a ser escrito
    connect(this->ui->txtTexto, &QPlainTextEdit::textChanged, this, &Dialog::textChanged);

    //Reiniciar leitura com dois cliques seguidos
    connect(&this->arduino, &Arduino::reiniciarLeitura, this, &Dialog::reiniciarLeitura);

    //Reiniciar leitura com dois cliques seguidos
    connect(&this->arduino, &Arduino::selecionarLetra, this, &Dialog::selectLetra);

    QClipboard *clipboard = QApplication::clipboard();
    ui->txtTexto->document()->setPlainText(clipboard->text()) ;

    //deixo com tudo desativado como valor inicial
    arduino.transaction();
}

void Dialog::textChanged(){
    arduino.setText(ui->txtTexto->toPlainText());
}

void Dialog::selectLetra(const int letra){

    QTextCursor c = ui->txtTexto->textCursor();

    if(letra == -1){
        c.clearSelection();
    }else{
        c.setPosition(letra);
        c.setPosition(letra+1, QTextCursor::KeepAnchor);
    }

    ui->txtTexto->setTextCursor(c);
}

void Dialog::reiniciarLeitura(){
    qDebug() << " Reiniciado ";   

    selectLetra(-1);

    QClipboard *clipboard = QApplication::clipboard();
    ui->txtTexto->document()->setPlainText(ConverteBraille::convertTextToBraille(clipboard->text()));
}

//Celta
Dialog::~Dialog() {
    delete ui;
}
