#include "dialogparaedit.h"
#include "ui_dialogparaedit.h"

DialogParaEdit::DialogParaEdit(QWidget *parent) : QDialog(parent), ui(new Ui::DialogParaEdit)
{
    ui->setupUi(this);
#if defined(Q_WS_QWS)
    // 设置对话框显示效果
    setWindowFlags(Qt::FramelessWindowHint);
    //setAttribute(Qt::WA_TranslucentBackground, true);
#endif
}

void DialogParaEdit::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type())
    {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

DialogParaEdit::~DialogParaEdit()
{
    delete ui;
}
