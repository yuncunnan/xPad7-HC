#ifndef FORMACTIMM_H
#define FORMACTIMM_H

#include <QWidget>

class CMBProtocol;
class QButtonGroup;

namespace Ui {
class FormActIMM;
}

class FormActIMM : public QWidget
{
    Q_OBJECT
    
public:
    explicit FormActIMM(QWidget *parent = 0);
    ~FormActIMM();
    int GetType();
    void SetType(int type);
    int GetDelay();
    void SetDelay(int delay);

	void UpdateWidgetState();

protected:
	void changeEvent(QEvent *e);

private:
    Ui::FormActIMM *ui;
    CMBProtocol *pModbus;
    QButtonGroup *pIMMBtn;

private slots:
	void inputDelay(void);

public slots:
    void IMMBtnClick(int btn);
};

#endif // FORMACTIMM_H
