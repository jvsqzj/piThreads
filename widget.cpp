#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QString>
#include <stdlib.h>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(this,SIGNAL(funcion()),this,SLOT(barras()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    ui->texto->text();  //  se guarda el numero que ingresa el usuario

    //  Conversion de la entrada a entero
    bool convertOK;
    unsigned long int n = ui->texto->text().toULong(&convertOK);

    //  Ahora debemos hacer la cantidad de barras
    //  dependiendo del numero que se introdujo.

    emit funcion(); //  va a brincar
}

void Widget::barras(){
    for (unsigned int num = 0; num < n; num++)
    {
        u
    }
}


