#ifndef FORMACTIF_H
#define FORMACTIF_H

#include <QtGlobal>
#include <QWidget>

class QButtonGroup;

namespace Ui {
class FormActIf;
}

class FormActIf : public QWidget
{
    Q_OBJECT
    
public:
    explicit FormActIf(QWidget *parent = 0);
    ~FormActIf();
    void SetVar(int var);
    int GetVar();
    void SetType(int type);
    int GetType();

    void SetPara(int para, bool isconst);
//    void SetParaType(int paratype);
    int GetPara(bool &isconst);
//    int GetParaType();

	void UpdateWidgetState();

	void SetTimeout(int delay);
	int GetTimeout();

protected:
	void changeEvent(QEvent *e);

private:
    Ui::FormActIf *ui;
	QButtonGroup *pOperator;		// 运算符按钮组
	quint32 varSet;
	quint32 parSet;
    bool m_isconst;

private slots:
	void operatorClick(int id);		// 运算符按钮点击信号槽
	void selectVariable(void);		// 选择第一个参数信号槽
	void selectParameter(void);		// 选择第二个参数信号槽
	void InputDelay(void);
};

#endif // FORMACTIF_H
