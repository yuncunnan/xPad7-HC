#include "dialogcomminputpad.h"
#include "ui_dialogcomminputpad.h"

DialogCommInputPad::DialogCommInputPad(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCommInputPad)
{
    ui->setupUi(this);
}

DialogCommInputPad::~DialogCommInputPad()
{
    delete ui;
}
