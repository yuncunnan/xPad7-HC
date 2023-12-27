#ifndef FORMACTVISION_H
#define FORMACTVISION_H

#include <QWidget>

namespace Ui {
class FormActVision;
}

class FormActVision : public QWidget
{
    Q_OBJECT
    
public:
    explicit FormActVision(QWidget *parent = 0);
    ~FormActVision();
    int GetTimeout();
    void SetTimeOut(int delay);
    int GetVision();
    void SetVision(int vision);
    int GetMatch();
    void SetMatch(int match);
    int GetData(int idxmatch, int idxdata);
    void SetData(int idxmatch, int idxdata, int uservar);

protected:
	void changeEvent(QEvent *e);

public slots:
    void UpdateWidgetState(void);

private:
    Ui::FormActVision *ui;
    int m_matchbmp;             // 匹配几组数据
    quint16 m_uservar[3][4];

private slots:
	void inputDelay(void);
    void inputUserVar1(void);
    void inputUserVar2(void);
    void inputUserVar3(void);
    void inputUserVar4(void);
    void inputUserVar5(void);
    void inputUserVar6(void);
    void inputUserVar7(void);
    void inputUserVar8(void);
    void inputUserVar9(void);
    void inputUserVar10(void);
    void inputUserVar11(void);
    void inputUserVar12(void);
};

#endif // FORMACTVISION_H
