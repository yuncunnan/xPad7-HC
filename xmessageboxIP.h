#ifndef XMESSAGEBOXIP_H
#define XMESSAGEBOXIP_H

#include <QDialog>

namespace Ui {
class xMessageBoxIP;
}

class xMessageBoxIP : public QDialog
{
	Q_OBJECT
	

public:
    explicit xMessageBoxIP(QWidget *parent = 0);
    ~xMessageBoxIP();
    qint32 DoForm();

private:
    Ui::xMessageBoxIP *ui;

private slots:
    void BtnClicked(void);
    void inputIP1(void);
    void inputIP2(void);
    void inputIP3(void);
    void inputIP4(void);
    void inputSubMask1(void);
    void inputSubMask2(void);
    void inputSubMask3(void);
    void inputSubMask4(void);
    void inputGateWay1(void);
    void inputGateWay2(void);
    void inputGateWay3(void);
    void inputGateWay4(void);
};

#endif // XMESSAGEBOXIP_H
