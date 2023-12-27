#include "dialogoption.h"
#include "ui_dialogoption.h"

DialogOption::DialogOption(QString nameen, QString namedis, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DialogOption)
{
	ui->setupUi(this);
    m_nameen = nameen;
    m_namedis = namedis;
    ui->lineEditUse->setText(m_nameen);
    ui->lineEditUseless->setText(m_namedis);
}

DialogOption::~DialogOption()
{
	delete ui;
}

void DialogOption::on_pushButtonOK_clicked()
{
    m_nameen = ui->lineEditUse->text();
    m_namedis = ui->lineEditUseless->text();
}
