#ifndef FORMSYSTEM_H
#define FORMSYSTEM_H

#include <QWidget>
#include <QTimer>
#include "cmbprotocol.h"
#include "xstringresource.h"
#include <QRegExpValidator>

namespace Ui {
class Formsystem;
}

#define HOME_ACTION_MAX		11

#define VISION_DEVICE_MAX   8
#define VISION_DATAS_MAX    4

class Formsystem : public QWidget
{
	Q_OBJECT
	
public:
	explicit Formsystem(CMBProtocol *modbus, QWidget *parent = 0);
	~Formsystem();
	
	bool EnterForm(void);
	bool ExitForm(void);

protected:
	void changeEvent(QEvent *e);

private:
	Ui::Formsystem *ui;
	CMBProtocol *pModbus;					// Modbus协议对象

	SystemParameter SysPara;				// 系统参数设置
	SystemParameter SysParaBak;
    ProductCode ProCode;
    ProductCode ProCodeBak;
    RegistrationCode RegCode;
    quint64 parModify;						// 参数修改标志
	quint8 Axis[HOME_ACTION_MAX];
	quint16 bakhome[HOME_DEF_MAX];
	quint16 home[HOME_DEF_MAX];
	bool TemplateChecked;						// 非教导模式是否选中
    bool AlfaChecked;						// Alfa模式是否选中
    QTimer *m_time;
    qint16 m_visionidx; // 当前选中的视觉标号
    quint32 m_visiondata[VISION_DEVICE_MAX][VISION_DATAS_MAX];  // 使用数组表示8个视觉，4组数据

    void retranslateUi(void);				// 更新界面字符串翻译
    void setPermissions(void);				// 根据当前用户权限设置界面
	void queryHome(quint16 (&home)[HOME_DEF_MAX]); // 查询原点复归顺序
	void TransHome(quint16 (&home)[HOME_DEF_MAX]); // 8个原点复归顺序到20个地址的映射
	bool QueryPara(void);					// 查询系统参数设置
	void LoadPara(void);					// 从界面得到系统参数设置
	bool isModified(void);					// 检查参数是否修改
	bool CheckValid(void);					// 检查参数合法性
	bool SavePara(void);					// 保存系统参数设置
	void UpdateTab();						// 根据数组内容，刷新TAB函数
	QString TranslateAxis(quint8 Step) ;	// 解析轴名称
	bool MoveTab(quint8 currentselect, quint8 last_range);			// 调整轴顺序
    void CombineOilInterval(void);          // 组合打油间隔
    void BreakOilInterval(void);            // 分解打油间隔
    bool checkRegCodeValid(QString strregcode, QString strprocode = "");
    bool IsVaildPCode(const ProductCode & PCode);

private slots:
	void userChange(void);					// 当前登录用户更改槽
	void slotPrdCnt(void);
	void slotRmdCnt(void);
	void slotRjtCnt(void);
	void slotAlmCnt(void);
	void slotAlmTime(void);
	void slotMaintain(void);
	void clrMouldSum(void);
	void resetSysPara(void);
	void resetSrvPara(void);
	void resetSvdevPara(void);
	void resetPwd(void);
	void AxisGoDown(void);					// 向下一项
	void AxisGoUp(void);					// 向上一项
	void AxisGoTop(void);					// 移动至顶部
	void AxisGoBottom(void);				// 移动至底部
	void AcceptSetup(void);					// 保存参数并且退出信号槽
    bool UpdateRegCode(void);               // 更新激活码
    bool UpdateProductCode(void);           // 更新产品密钥
    void inputRegCode(void);
    void inputCurProCode(void);
    void inputNewProCode(void);
    void inputNewProCode2(void);
    void inputIP1(void);
    void inputIP2(void);
    void inputIP3(void);
    void inputIP4(void);
    void inputSubMask1(void);
    void inputSubMask2(void);
    void inputSubMask3(void);
    void inputSubMask4(void);
    void inputGateWay1(void);
    void inputGateWay2(void);
    void inputGateWay3(void);
    void inputGateWay4(void);
    void inputOilIntervalDay(void);
    void inputOilIntervalHour(void);
    void inputOilIntervalMinute(void);
    void inputOilTime(void);
    void IsBtnOKVisible(int idx);           // 激活信息界面保存按钮不可见
    void BtnPageChanged(void);
    void checkOilStateChanged(int state);
    void activeRemainTime(uint32_t time);

    void inputVisionIP1(void);
    void inputVisionIP2(void);
    void inputVisionIP3(void);
    void inputVisionIP4(void);
    void inputVisionPort(void);
    void selectVariable(void);
    void BtnVisionPrevClick(void);
    void BtnVisionNextClick(void);
    void BtnVisonTestClick(void);
    void VisionDataUpdate();
    void VisionProtocolChanged(int idx);
    void VisionInstallChanged(int idx);
    void VisionTypeChanged(int idx);
};

#endif // FORMSYSTEM_H
