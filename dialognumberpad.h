#ifndef DIALOGNUMBERPAD_H
#define DIALOGNUMBERPAD_H

#include <QDialog>

namespace Ui {
class DialogNumberPad;
}

class DialogNumberPad : public QDialog
{
	Q_OBJECT
	
public:
	explicit DialogNumberPad(QWidget *parent = 0);
	~DialogNumberPad();
	
    //int DoForm(double &value);
    int DoForm(int &value, int min, int max);
    int DoFormDouble(double &value, double min, double max);
    int DoFormPos(double &value, double min, double max);
	int DoForm(int &type, double &value, double min, double max);

protected:
	void changeEvent(QEvent *e);
	
private:
	Ui::DialogNumberPad *ui;
	int m_type;
    void retranslateUi(void);
    double m_min;
    double m_max;
private slots:
	void Key0Click(void);
	void Key1Click(void);
	void Key2Click(void);
	void Key3Click(void);
	void Key4Click(void);
	void Key5Click(void);
	void Key6Click(void);
	void Key7Click(void);
	void Key8Click(void);
	void Key9Click(void);
	void KeyDotClick(void);
	void KeySignClick(void);
	void KeyClrClick(void);
	void KeyDelClick(void);
	void KeyCatClick(void);
	void KeyRelClick(void);
	void KeyWaitClick(void);
    void KeyPHorClick(void);
    void KeyPVerClick(void);
    void KeyTrvClick(void);
    void KeyRHorClick(void);
    void KeyRVerClick(void);
    void KeyExtClick(void);
    void KeyVarToggled(bool ischecked);
};

#endif // DIALOGNUMBERPAD_H
