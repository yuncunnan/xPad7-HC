#ifndef FORMACTASSIST_H
#define FORMACTASSIST_H

#include <QWidget>

class CMBProtocol;
class QButtonGroup;

namespace Ui {
class FormActAssist;
}

class FormActAssist : public QWidget
{
    Q_OBJECT
    
public:
    explicit FormActAssist(CMBProtocol *modbus, QWidget *parent = 0);
    ~FormActAssist();
    void SetInterval(int interval);
    int GetInterval();
    void SetDelay(int delay);
    int GetDelay();
    void SetType(int type);
    int GetType();
    void SetOutput(int out);
    int GetOutput();

	void UpdateWidgetState();

protected:
	void changeEvent(QEvent *e);

private:
    Ui::FormActAssist *ui;
	CMBProtocol *pModbus;
    void retranslateUi(void);	// 设置界面字符串资源
    quint16 output;             // 辅助设备选择
    QButtonGroup *pAssist;

private slots:
    void inputDelay(void);
	void inputInterval(void);
	void extOutOn(void);
	void extOutOff(void);
};

#endif // FORMACTVACUUM_H
