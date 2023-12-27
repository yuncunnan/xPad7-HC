#ifndef FORMACTMEXTOUT_H
#define FORMACTMEXTOUT_H

#include <QWidget>

class CMBProtocol;

namespace Ui {
class FormActMExtOut;
}

class FormActMExtOut : public QWidget
{
    Q_OBJECT
    
public:
    explicit FormActMExtOut(QWidget *parent = 0);
    ~FormActMExtOut();
    void SetDelay(int delay);
    int GetDelay();
    void SetOutBmp(int bmp);
    int GetOutBmp();
    void SetType(int type);
    int GetType();
    void SetCounter(quint16 var);
    quint16 GetCounter();

    void UpdateWidgetState();

protected:
	void changeEvent(QEvent *e);

private:
    Ui::FormActMExtOut *ui;
    quint16 outbmp;
    quint16 counter;
    void retranslateUi(void);			// 设置界面字符串资源

private slots:
	void inputDelay(void);
};

#endif // FORMACTMEXTOUT_H
