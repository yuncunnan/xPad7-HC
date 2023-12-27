#ifndef FORMBTNQUICK_H
#define FORMBTNQUICK_H

#include <QWidget>
#include "cmbprotocol.h"

class QButtonGroup;
class TeachTableModel;

namespace Ui {
class FormBtnQuick;
}

class FormBtnQuick : public QWidget
{
	Q_OBJECT

public:
    explicit FormBtnQuick(CMBProtocol *modbus, QWidget *parent = 0);
    ~FormBtnQuick();
    bool EnterForm(bool newprogram);
    void init(void);

    int GetWaitX();
    int GetWaitY();
    int GetWaitZ();
    int GetWaitA();
    int GetWaitB();

    int GetFetchX();
    int GetFetchY();
//    int GetFetchZ();
    int GetFetchA();
    int GetFetchB();

    int GetProductX();
    int GetProductY();
    int GetProductZ();

    int GetWasteZ();
    int GetWasteA();
    int GetWasteB();

    int GetWaitXType(){return m_wait_xtype;}
    int GetWaitYType(){return m_wait_ytype;}
    int GetWaitZType(){return m_wait_ztype;}
    int GetWaitAType(){return m_wait_atype;}
    int GetWaitBType(){return m_wait_btype;}

    int GetFetchXType(){return m_fetch_xtype;}
    int GetFetchYType(){return m_fetch_ytype;}
    int GetFetchZType(){return m_fetch_ztype;}
    int GetFetchAType(){return m_fetch_atype;}
    int GetFetchBType(){return m_fetch_btype;}

    int GetProductXType(){return m_product_xtype;}
    int GetProductYType(){return m_product_ytype;}
    int GetProductZType(){return m_product_ztype;}

    int GetWasteZType(){return m_waste_ztype;}
    int GetWasteAType(){return m_waste_atype;}
    int GetWasteBType(){return m_waste_btype;}

    quint16 GetCheckBoxState();
    quint32 GetVacuumBmp(void);

    int clickPagePrev(void);
    int clickPageNext(void);
    bool CheckBoxWasteRotateFirstState();
    bool GetRarmWaitState_ADV(void);
    bool GetRarmFetch_adv(void);

	bool GetRunnerWasterState(void);

public slots:
    void UpdateWidgetState(void);

protected:
	void changeEvent(QEvent *e);

private:
    Ui::FormBtnQuick *ui;
    QButtonGroup *pAxesBtn;
    CMBProtocol *pModbus;
	void retranslateUi(void);			// 设置界面字符串资源

    int m_checkbox_state;

    int m_wait_xpos;
    int m_wait_ypos;
    int m_wait_zpos;
    int m_wait_apos;
    int m_wait_bpos;
    int m_wait_xtype;
    int m_wait_ytype;
    int m_wait_ztype;
    int m_wait_atype;
    int m_wait_btype;

    int m_fetch_xpos;
    int m_fetch_ypos;
    int m_fetch_zpos;
    int m_fetch_apos;
    int m_fetch_bpos;
    int m_fetch_xtype;
    int m_fetch_ytype;
    int m_fetch_ztype;
    int m_fetch_atype;
    int m_fetch_btype;

    int m_product_xpos;
    int m_product_ypos;
    int m_product_zpos;
    int m_product_xtype;
    int m_product_ytype;
    int m_product_ztype;

    int m_waste_apos;
    int m_waste_bpos;
    int m_waste_zpos;
    int m_waste_atype;
    int m_waste_btype;
    int m_waste_ztype;

    int m_current_page;
    quint16 rotbmp;
    quint32 vacbmp;

    TeachTableModel *m_teachmodel;

private slots:
    void syncWaitPos(void);
    void syncFetchPos(void);
    void syncProductPos(void);
    void syncWastePos(void);

    void inputWaitPaHor(void);
    void inputWaitPaVer(void);
    void inputWaitTrv(void);
    void inputWaitRaHor(void);
    void inputWaitRaVer(void);
    void inputFetchPaHor(void);
    void inputFetchPaVer(void);
//    void inputFetchTrv(void);
    void inputFetchRaHor(void);
    void inputFetchRaVer(void);
    void inputProductPaHor(void);
    void inputProductPaVer(void);
    void inputProductTrv(void);
    void inputWasteTrv(void);
    void inputWasteRaHor(void);
    void inputWasteRaVer(void);

    void checkPAStateChanged(int idx);
    void checkRAStateChanged(int idx);
    void checkMatrixChanged(int idx);
    void btnAdvClick(void);//副臂前进后退按钮
    void btnAscClick(void);//副臂上升下降按钮
    void checkBoxRunnerUseStateChanged(int ischecked);
    void OutputIO(void);
};

#endif // FORMACTQUICK_H
