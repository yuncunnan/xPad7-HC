#ifndef FORMACTVACUUM_H
#define FORMACTVACUUM_H

#include <QWidget>

class CMBProtocol;

namespace Ui {
class FormActVacuum;
}

class FormActVacuum : public QWidget
{
    Q_OBJECT
    
public:
    explicit FormActVacuum(CMBProtocol *modbus, QWidget *parent = 0);
    ~FormActVacuum();
    void SetInterval(int interval);
    int GetInterval();
    void SetDelay(int delay);
    int GetDelay();
    void SetType(int type);
    int GetType();
    void SetOutBmp(int bmp);
    int GetOutBmp();
    void SetInBmp(int var);
    int GetInBmp();

	void UpdateWidgetState();

protected:
	void changeEvent(QEvent *e);

private:
    Ui::FormActVacuum *ui;
	CMBProtocol *pModbus;
    void retranslateUi(void);			// 设置界面字符串资源
    quint16 outbmp;     // 治具选择
    quint16 inbmp;      // 检测选择

private slots:
    void inputDelay(void);
	void inputInterval(void);
	void extOutOn(void);
	void extOutOff(void);
    void stateChanged_checkJig03(int state);
    void stateChanged_checkJig04(int state);
    void stateChanged_checkJig05(int state);
    void stateChanged_checkJig06(int state);
    void stateChanged_checkJig07(int state);
    void stateChanged_checkJig08(int state);
    void stateChanged_checkJig09(int state);
    void stateChanged_checkJig10(int state);
    void stateChanged_checkJig11(int state);
    void stateChanged_checkJig12(int state);
    void stateChanged_checkJig13(int state);
    void stateChanged_checkJig14(int state);
    void stateChanged_checkJig15(int state);
    void stateChanged_checkJig16(int state);
    void stateChanged(int state);

    void btnNextclicked(void);
    void btnPrevclicked(void);
};

#endif // FORMACTVACUUM_H
