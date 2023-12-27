#ifndef FORMALFAOPTION_H
#define FORMALFAOPTION_H

#define ORDER_MODE_XYZ	0x80
#define ORDER_MODE_XZY	0x81
#define ORDER_MODE_YXZ	0x82
#define ORDER_MODE_YZX	0x83
#define ORDER_MODE_ZXY	0x84
#define ORDER_MODE_ZYX	0x85

#include <QWidget>
#include "alfamodel.h"
#include "xstringresource.h"
#include <QRegExpValidator>

class QButtonGroup;

namespace Ui {
class Formalfaoption;
}

#define HOME_ACTION_MAX		11

class Formalfaoption : public QWidget
{
	Q_OBJECT
	
public:
    explicit Formalfaoption(CMBProtocol *modbus, QWidget *parent = 0);
    ~Formalfaoption();
	
	bool EnterForm(void);
	bool ExitForm(void);
    void UpdateTab();                                               // 根据数组内容，刷新TAB函数
    QString TranslateAxis(quint8 Step) ;                            // 解析轴名称
    bool MoveTab(quint8 currentselect, quint8 last_range);			// 调整轴顺序
    int GetFirstDec();	// 定位模式
    void SetFirstDec(int fdec);

protected:
	void changeEvent(QEvent *e);

private:
    Ui::Formalfaoption *ui;
    CMBProtocol *pModbus;					// Modbus协议对象
    AlfaModel *m_alfamodel;
    TeachTableModel pgmModel;
    QButtonGroup *pTrvInBtn;
    QButtonGroup *pTrvOutBtn;
    QButtonGroup *pFetchBtn;
    QButtonGroup *pReleaseBtn;

    quint16 userVar;
    quint16 outport;
    quint8 Axis[3];

    void retranslateUi(void);				// 更新界面字符串翻译
	void setPermissions(void);				// 根据当前用户权限设置界面
	bool isModified(void);					// 检查参数是否修改
    bool SaveAlfaPara(void);				// 保存系统参数设置
    void setPortState(void);                // 设置控件状态

private slots:
	void userChange(void);					// 当前登录用户更改槽
	void AcceptSetup(void);					// 保存参数并且退出信号槽
    void inputProDelay(void);
    void inputRunDelay(void);
    void inputRotateDelay(void);
    void inputMOPTimeout(void);
    void inputEMCDelay(void);
    void inputProRelPos(void);
    void inputRunRelPos(void);
    void inputCatchPos(void);
    void inputXProDown(void);
    void inputXProCatch(void);
    void inputBRunDown(void);
    void inputBRunCatch(void);
    void inputYProCatch(void);
    void inputARunCatch(void);
    void inputYProRel(void);
    void inputARunRel(void);
    void inputXSpeed(void);
    void inputYSpeed(void);
    void inputZSpeed(void);
    void inputASpeed(void);
    void inputBSpeed(void);
    void inputCSpeed(void);
    void inputYSpeedout(void);
    void inputASpeedout(void);    
    void inputXProRel(void);
    void inputBRunRel(void);
    void inputYProWait(void);
    void inputARunWait(void);
    void inputXProUP(void);
    void inputBRunUP(void);

    void inputEjectorFrontDelay(void);
    void inputEjectorBackDelay(void);
    void inputC1FrontDelay(void);
    void inputC1BackDelay(void);
    void inputC2FrontDelay(void);
    void inputC2BackDelay(void);

    void inputConveyorDelay(void);
    void inputConveyorInterval(void);
    void selectPort(void);

    void stateChanged_ProJig1(int state);
    void stateChanged_ProJig2(int state);
    void stateChanged_ProJig3(int state);
    void stateChanged_ProJig4(int state);
    void stateChanged_ProJig5(int state);
    void stateChanged_ProJig6(int state);
    void stateChanged_RunJig1(int state);
    void stateChanged_RunJig2(int state);
    void stateChanged_RunJig3(int state);
    void stateChanged_RunJig4(int state);
    void stateChanged_RunJig5(int state);
    void stateChanged_RunJig6(int state);
    void indexChanged_proMode(int index);
    void indexChanged_runMode(int index);

    void inputHorCnt(void);
    void inputVerCnt(void);
    void inputTrvCnt(void);
    void inputHorInt(void);
    void inputVerInt(void);
    void inputTrvInt(void);
    void inputHorPos(void);
    void inputVerPos(void);
    void inputTrvPos(void);
    void inputHspd(void);
    void inputLspd(void);
    void inputLdis(void);
    void selectUser(void);
    void AxisGoDown(void);
    void AxisGoUp(void);

    void proReleaseState(int state);

};

#endif // FORMALFAOPTION_H
