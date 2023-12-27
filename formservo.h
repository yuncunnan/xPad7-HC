#ifndef FORMSERVO_H
#define FORMSERVO_H

#include <QVector>
#include <QWidget>
#include "cmbprotocol.h"
#include <QCheckBox>
#include <QComboBox>

#define MAX_AXIS_NUM    6

#define MAX_REV_ANGLE   360.00
#define MAX_REV_LENGTH  60000.00

class xStringResource;

namespace Ui {
class Formservo;
}

class Formservo : public QWidget
{
	Q_OBJECT
	
public:
	explicit Formservo(CMBProtocol *modbus, QWidget *parent);
	~Formservo();

	bool EnterForm(void);
	bool ExitForm(void);
	void GetDistance(quint32 &Pver, quint32 &Rver, quint32 &trv, quint32 &ext, quint32 &disHomP_R, quint32 &MinDisP_R);

protected:
	void changeEvent(QEvent *e);
	
private:
	Ui::Formservo *ui;
	CMBProtocol *pModbus;					// Modbus协议对象
//	QVector<QString> StrDirection;			// 各伺服轴的名称
	ServoParameter ServoPara;				// 伺服参数数据
	ServoParameter ServoParaBak;
	quint64	parModify;						// 参数修改标志
	quint32 trvRelPos;						// 横行模外置物点
	quint32 trvRelPosBak;
	quint32 trvWaitPos;						// 横行轴原点复归后待机位置
	quint32 trvWaitPosBak;
	quint32 trvCatPos;						// 横行模内取物点
	quint32 trvCatPosBak;
	quint32 paVerCatPos;					// 正臂上下取物点
	quint32 paVerCatPosBak;
	quint32 paVerRelPos;					// 正臂上下置物点
	quint32 paVerRelPosBak;
	quint32 paVerWaitPos;					// 正臂上下待机点
	quint32 paVerWaitPosBak;
	quint32 paHorCatPos;					// 正臂引拔
	quint32 paHorCatPosBak;
	quint32 paHorRelPos;
	quint32 paHorRelPosBak;
	quint32 paHorWaitPos;
	quint32 paHorWaitPosBak;
	quint32 raVerCatPos;					// 副臂上下
	quint32 raVerCatPosBak;
	quint32 raVerRelPos;
	quint32 raVerRelPosBak;
	quint32 raVerWaitPos;
	quint32 raVerWaitPosBak;
	quint32 raHorCatPos;					// 副臂引拔
	quint32 raHorCatPosBak;
	quint32 raHorRelPos;
	quint32 raHorRelPosBak;
	quint32 raHorWaitPos;
	quint32 raHorWaitPosBak;
	quint32 extCatPos;						// 扩展
	quint32 extCatPosBak;
	quint32 extRelPos;
	quint32 extRelPosBak;
	quint32 extWaitPos;
	quint32 extWaitPosBak;

    QCheckBox* m_AxisType[MAX_AXIS_NUM];    // 轴类型数组
    QComboBox* m_HomeType[MAX_AXIS_NUM];    // 原点归位模式
    QCheckBox* m_DecType[MAX_AXIS_NUM];     // 减速类型
    QCheckBox* m_DirType[MAX_AXIS_NUM];     // 方向类型
    QCheckBox* m_HomeMod[MAX_AXIS_NUM];     // 找原点方式
    QButtonGroup *pBtnPage;                // 选择按钮组

    QButtonGroup *pRBtnSVDev;               //伺服驱动器参数


	void retranslateUi(void);				// 更新界面字符串翻译
	void setPermissions(void);				// 根据当前用户权限设置界面
	bool QueryPara(void);					// 查询伺服参数设置
	void LoadPara(void);					// 从界面得到伺服参数设置
	bool isModified(void);					// 检查参数是否修改
	bool CheckValid(void);					// 检查参数合法性
	bool SavePara(void);					// 保存伺服参数设置
    // 轴类型
    void GetAngleType(uint8_t idx);
    void SetAngleType(uint8_t idx);
    void CheckBoxStatus(void);
    // 原点归位模式
    void GetHomeType(uint8_t idx);
    void SetHomeType(uint8_t idx);
    // 轴类型
    void GetDecType(uint8_t idx);
    void SetDecType(uint8_t idx);

    void showSVDevPara(uint8_t idx);
    uint8_t SvDevParaPage;
private slots:
	void userChange(void);					// 当前登录用户更改槽
    void SetMain(bool init);
    void InputMain(void);
    // 编辑伺服行程
	void InputHorLen(void);					// 输入正副臂引拔轴原点距离
	void InputHorInt(void);					// 输入正副臂引拔轴最小间距
	void InputPaVerDistance(void);			// 输入正臂上下软件行程
	void InputTravelDistance(void);			// 输入横行软件行程
	void InputRaVerDistance(void);			// 输入副臂上下软件行程
	void InputExtendDistance(void);			// 输入扩展软件行程
	// 输入伺服速度和加减速信号槽
	void InputPaHorSpd(void);
	void InputPaHorAcc(void);
	void InputPaVerSpd(void);
	void InputPaVerAcc(void);
	void InputTrvSpd(void);
	void InputTrvAcc(void);
	void InputRaHorSpd(void);
	void InputRaHorAcc(void);
	void InputRaVerSpd(void);
	void InputRaVerAcc(void);
	void InputExtSpd(void);
	void InputExtAcc(void);
    void InputHomeSpd(void);
    void InputHomeSpdSlow(void);
    // 输入安全区位置
    void InputTrvInS(void);
    void InputTrvInE(void);
    void InputTrvInS2(void);
    void InputTrvInE2(void);
    void InputTrvOutS(void);
    void InputTrvOutE(void);
    void InputSafePaUp(void);
    void InputSafeRaUp(void);
    void InputSafePaHorS(void);
    void InputSafePaHorE(void);
    void InputSafeRaHorS(void);
    void InputSafeRaHorE(void);
    void InputTrvBackWardS(void);
    void InputTrvBackWardE(void);
    void InputTrvWait(void);
    void InputSafeRotS(void);
    void InputSafeRotE(void);
    void InputSafeTrvS(void);
    void InputSafeTrvE(void);
    void InputSafePaTrvS(void);
    void InputSafePaTrvE(void);
    void InputSafeRaTrvS(void);
    void InputSafeRaTrvE(void);
    void InputSafeExtS(void);
    void InputSafeExtE(void);
    void InputSafeExtInmoldS(void);
    void InputSafeExtInmoldE(void);
    // 输入快速定位点
    void InputPaHorCat(void);
    void InputPaHorRel(void);
    void InputPaHorWait(void);
    void InputPaVerCat(void);
    void InputPaVerRel(void);
    void InputPaVerWait(void);
    void InputRaHorCat(void);
    void InputRaHorRel(void);
    void InputRaHorWait(void);
    void InputRaVerCat(void);
    void InputRaVerRel(void);
    void InputRaVerWait(void);
    void InputTrvCat(void);
    void InputTrvRel(void);
	void InputTrvWait2(void);
    void InputExtCat(void);
    void InputExtRel(void);
	void InputExtWait(void);
    // 输入原点偏移
    void InputPaHorOffset(void);
    void InputPaVerOffset(void);
    void InputRaHorOffset(void);
    void InputRaVerOffset(void);
    void InputTrvOffset(void);
    void InputExtOffset(void);
    // 输入原点待机点
    void InputPaHorHomeWait(void);
    void InputPaVerHomeWait(void);
    void InputTrvHomeWait(void);
    void InputRaHorHomeWait(void);
    void InputRaVerHomeWait(void);
    void InputExtHomeWait(void);
    // 输入模
    void InputPaHorMod(void);
    void InputPaVerMod(void);
    void InputTrvMod(void);
    void InputRaHorMod(void);
    void InputRaVerMod(void);
    void InputExtMod(void);
    // 马达
    void InputPaHorUnits(void);
    void InputPaHorPluses(void);
    void InputRaHorUnits(void);
    void InputRaHorPluses(void);
    void InputPaVerUnits(void);
    void InputPaVerPluses(void);
    void InputRaVerUnits(void);
    void InputRaVerPluses(void);
    void InputTrvUnits(void);
    void InputTrvPluses(void);
    void InputExtUnits(void);
    void InputExtPluses(void);
    // 轴按钮选择mm/°切换
    void CheckBoxPaHorChanged(void);
    void CheckBoxRaHorChanged(void);
    void CheckBoxPaVerChanged(void);
    void CheckBoxRaVerChanged(void);
    void CheckBoxTrvChanged(void);
    void CheckBoxExtChanged(void);
    // 编码器类型控制地址
    void PaHorEncoderChanged(int idx);
    void PaVerEncoderChanged(int idx);
    void RaHorEncoderChanged(int idx);
    void RaVerEncoderChanged(int idx);
    void TrvEncoderChanged(int idx);
    void ExtEncoderChanged(int idx);
    void InputPaHorAddr(void);
    void InputPaVerAddr(void);
    void InputRaHorAddr(void);
    void InputRaVerAddr(void);
    void InputTrvAddr(void);
    void InputExtAddr(void);
    // JERK加加速
    void InputPaHorJERK(void);
    void InputPaVerJERK(void);
    void InputTrvJERK(void);
    void InputRaHorJERK(void);
    void InputRaVerJERK(void);
    void InputExtJERK(void);

    void InputSvDevPara(void);

    void setEncoderHomeState(void);
    void SetHomeEncoderClick(void);
    void ClrHomeEncoderClick(void);
    // 页面切换
    void setCurrentpage(int idx);
    void updataSvDevPara(int idx);
    void LoadSvDevPara(int idx);
    // 保存参数信号槽
	void AcceptSetup(void);
    void ECatEncodeStateChanged(int state);
};

#endif // FORMSERVO_H
