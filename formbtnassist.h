#ifndef FORMBTNASSIST_H
#define FORMBTNASSIST_H

#include <QWidget>

class QButtonGroup;

namespace Ui {
class FormBtnAssist;
}

class FormBtnAssist : public QWidget
{
    Q_OBJECT
    
public:
    explicit FormBtnAssist(QWidget *parent = 0);
    ~FormBtnAssist();
    bool EnterForm(void);
    void init(void);
    int GetAssistBmp();
    int GetDelayOil();
    int GetDelayConveyor();
    int GetDelayReject();
    int GetTypeOil();
    int GetTypeConveyor();
    int GetTypeReject();
    int GetVarOil();
    int GetVarConveyor();
    int GetVarReject();
    int GetIntervalOil();
    int GetIntervalConveyor();
    int GetIntervalReject();

    void UpdateWidgetState();
protected:
	void changeEvent(QEvent *e);

private:
    Ui::FormBtnAssist *ui;

private slots:
    void inputDelayOil(void);
    void inputDelayConveyor(void);
    void inputDelayReject(void);

    void inputIntervalOil(void);
    void inputIntervalConveyor(void);
    void inputIntervalReject(void);

    void btnOilclicked(void);
    void btnConveyorclicked(void);
    void btnRejectclicked(void);
};

#endif // FORMBTNASSIST_H
