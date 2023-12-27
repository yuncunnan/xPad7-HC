#ifndef XMESSAGEBOXACTIVE_H
#define XMESSAGEBOXACTIVE_H

#include <QDialog>

namespace Ui {
class xMessageBoxActive;
}

class xMessageBoxActive : public QDialog
{
	Q_OBJECT
	

public:
    explicit xMessageBoxActive(QWidget *parent = 0);
    ~xMessageBoxActive();
    qint32 DoForm(QString &stractive);

private:
    Ui::xMessageBoxActive *ui;

private slots:
    void inputActive(void);
};

#endif // XMESSAGEBOXIP_H
