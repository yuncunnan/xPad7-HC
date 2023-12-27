#ifndef FORMBTNIMM_H
#define FORMBTNIMM_H

#include <QWidget>

class CMBProtocol;
class QButtonGroup;

namespace Ui {
class FormBtnIMM;
}

class FormBtnIMM : public QWidget
{
    Q_OBJECT
    
public:
    explicit FormBtnIMM(QWidget *parent = 0);
    ~FormBtnIMM();
    int GetIMMBmp();
    bool EnterForm(void);
    void init(void);

    int GetDelayEmo();
    int GetDelayEmc();
    int GetDelayEef();
    int GetDelayEeb();
    int GetDelayC1p1();
    int GetDelayC1p2();
    int GetDelayC2p1();
    int GetDelayC2p2();

    int GetTypeEmo();
    int GetTypeEmc();
    int GetTypeEef();
    int GetTypeEeb();
    int GetTypeC1p1();
    int GetTypeC1p2();
    int GetTypeC2p1();
    int GetTypeC2p2();

    void UpdateWidgetState();

protected:
	void changeEvent(QEvent *e);

private:
    Ui::FormBtnIMM *ui;
    CMBProtocol *pModbus;
    QButtonGroup *pIMMBtn;

private slots:
    void inputDelayEmo(void);
    void inputDelayEmc(void);
    void inputDelayEef(void);
    void inputDelayEeb(void);
    void inputDelayC1p1(void);
    void inputDelayC1p2(void);
    void inputDelayC2p1(void);
    void inputDelayC2p2(void);

    void btnEefclicked(void);
    void btnEebclicked(void);
    void btnC1p1clicked(void);
    void btnC1p2clicked(void);
    void btnC2p1clicked(void);
    void btnC2p2clicked(void);
};

#endif // FORMBTNIMM_H
