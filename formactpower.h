#ifndef FORMACTPOWER_H
#define FORMACTPOWER_H

#include <QWidget>

namespace Ui {
class FormActPower;
}

class FormActPower : public QWidget
{
    Q_OBJECT
    
public:
    explicit FormActPower(QWidget *parent = 0);
    ~FormActPower();
	virtual void setVisible(bool visible);

    int GetAxes();
    void SetAxes(int axes);
    void SetPoweroff(bool power);
    bool GetPoweroff(void);

public slots:
	void UpdateWidgetState(void);

protected:
	void changeEvent(QEvent *e);

private:
    Ui::FormActPower *ui;
	void retranslateUi(void);			// 设置界面字符串资源

private slots:
	void checkClick(void);
};

#endif // FORMACTPOWER_H
