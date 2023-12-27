#ifndef FORMTECH_H
#define FORMTECH_H

#include <QWidget>
#include <QItemSelection>
#include "xmlmodelitem.h"
#include "cmbprotocol.h"
#include "dialogedit.h"

///////////////////////////////////////////////
class TeachTableModel;
class DialogSelectAction;
class FormActPos;
class FormActExtPos;
class FormActExtIn;
class FormActExtOut;
class FormActPro;
class FormActIMM;
class FormActPaper;
class FormActLoopFree;
class FormActLoopMatrix;
class FormActDelay;
class FormActFor;
class FormActIf;
class FormActPath;
class FormActNull;
class FormActWait;
class FormActOperate;
class FormActPlus;
class FormVActVacuum;
class FormActVacuum;
class FormActRun;
class FormActSpeed;
class FormActSingleLoop;
class FormActSingleLoopFree;
class FormActInterp;
class FormActPower;
class FormActCircle;
class FormActMExtOut;
class FormActVision;
class FormActAssist;
class DialogParaEdit;
///////////////////////////////////////////////
class FormBtnPos;
class FormBtnExtPos;
class FormBtnIMM;
class FormBtnVacuum;
class FormBtnWait;
class FormBtnMExtOut;
class FormBtnAssist;
class FormBtnPro;
class FormBtnRun;
class FormBtnQuick;
///////////////////////////////////////////////
class QButtonGroup;

namespace Ui {
class FormTeach;
}

class FormTeach : public QWidget
{
	Q_OBJECT

public:
	explicit FormTeach(CMBProtocol *modbus, QWidget *parent = 0);
	~FormTeach();
	bool EnterForm(void);
	bool ExitForm();
    void keyRelease(quint32 key);			// 按键弹起事件处理函数
public slots:
	void GetWidget(int idx, QWidget *&widget);
//	void selectionChanged(const QItemSelection & selected, const QItemSelection & deselected);
protected:
    void changeEvent(QEvent *e);
private slots:
	void userChange(void);					// 当前登录用户更改槽
	void InsertCode();						// 插入指令
	void RemoveCode();						// 删除指令
	void MoveUp();							// 指令上移
	void MoveDown();						// 指令下移
    XmlModelItem *GetCodeItem(int idx);
    void ProcBtnStateChanged(int idx);
    void CodeCombine(void);
    void CodeSeparate(void);
    void EditProgramSlot();

    void clickBtnInsert(void);
    void clickBtnmenu(void);
    void clickBtnPos(void);
    void clickBtnIMM(void);
    void clickBtnVacuum(void);
    void clickBtnMatrix(void);
    void clickBtnWait(void);
    void clickBtnOther(void);
    void clickBtnMExtout(void);
    void clickBtnAssist(void);
    void clickBtnPro(void);
    void clickBtnRun(void);
    void clickBtnQuick(void);
    void clickBtnDelay(void);

    void clickPagePrev(void);
    void clickPageNext(void);
    void clickQuickOK(void);
    bool checkNewProgram(void);
    void test_order(void);                  // 测试按钮，测试指令
    void stop_test(void);
    void tableViewClicked(QModelIndex index);
//    void extOutOn(void);
//    void extOutOff(void);



private:
	Ui::FormTeach *ui;
	CMBProtocol *pModbus;					// Modbus协议对象
    int posBak;
    int curpos[MAX_PROCESS];
    int currentCode;
    bool m_haswarning;
    // 参数编辑窗口部件
    DialogParaEdit *m_dialogparaedit;
	FormActPos *m_actpos;
    FormActExtPos *m_actextpos;
	FormActExtIn *m_actextin;
	FormActExtOut *m_actextout;
    FormActMExtOut *m_actmextout;
	FormActPro *m_actpro;
	FormActRun *m_actrun;
	FormActIMM *m_actimm;
	FormActPaper *m_actpaper;
	FormActLoopFree *m_actloopfree;
	FormActLoopMatrix *m_actloopmatrix;
	FormActDelay *m_actdelay;
	FormActFor *m_actfor;
	FormActIf *m_actif;
	FormActPath *m_actpath;
	FormActNull *m_actnull;
    FormVActVacuum *m_vactvacuum;
	FormActVacuum *m_actvacuum;
	FormActWait *m_actwait;
	FormActOperate *m_actoperator;
    FormActSpeed *m_actspeed;
    FormActSingleLoop *m_actsingleloop;
    FormActSingleLoopFree *m_actsingleloopfree;
    FormActInterp *m_actinterp;
    FormActPower *m_actpower;
    FormActCircle *m_actcircle;
    FormActVision *m_actvision;
    FormActAssist *m_actassist;
    // 程序编辑窗口部件
	TeachTableModel *m_teachmodel;
	DialogSelectAction *m_actdlg;
    Dialogedit *dialogedit;

    ///////////////////////////////////////////////
    FormBtnExtPos *m_btnextpos;
    FormBtnPos *m_btnpos;
    FormBtnIMM *m_btnimm;
    FormBtnVacuum *m_btnvacuum;
    FormBtnWait *m_btnwait;
    FormBtnMExtOut *m_btnextout;
    FormBtnAssist *m_btnassist;
    FormBtnPro *m_btnpro;
    FormBtnRun *m_btnrun;
    FormBtnQuick *m_btnquick;
    ///////////////////////////////////////////////
    QButtonGroup *pBtnProcess;
    ///////////////////////////////////////////////
	void setPermissions(void);				// 根据当前用户权限设置界面
	void ChangeSelect(int pos);
	void SaveProgram(int pos = -1, bool isReset = true);
    void SetProcBtnState(int idx);
    void SetCurPos(int idx);
};

#endif // FORMTECH_H
