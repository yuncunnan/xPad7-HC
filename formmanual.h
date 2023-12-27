#ifndef FORMMANUAL_H
#define FORMMANUAL_H

#include <QtGlobal>
#include <QWidget>
#include <QMultiMap>
#include <QVector>
#include "cmbprotocol.h"

class QButtonGroup;

namespace Ui {
class FormManual;
}

class FormManual : public QWidget
{
	Q_OBJECT
	
public:
	explicit FormManual(CMBProtocol *modbus, QWidget *parent = 0);
	~FormManual();

	bool EnterForm(void);
	bool ExitForm(void);
	
protected:
	void changeEvent(QEvent *e);
	
private:
	Ui::FormManual *ui;

	CMBProtocol *pModbus;
	bool IsAuto;				// 系统是否在自动状态, true:自动;false:其他(手动或报警)
    int m_outidx;
    int m_inidx;
	void setPortNames(void);	// 设置端口名称
    void SetPortVisible(void);  // 设置端口显示状态
	void InitIoState(void);		// 初始化IO端口状态
    void retranslateUi(void);			// 设置界面字符串资源
    // 输出控制按钮组
	QButtonGroup *pProArm;		// 正臂输出控制
    QButtonGroup *pRunArm;		// 副臂输出控制
	QButtonGroup *pImmCtrl;		// 注塑机输出控制
    QButtonGroup *pOutCtrl;	// 主控模块输出控制
    QButtonGroup *pOutputSelect;// 扩展输出板选择
    QButtonGroup *pInputSelect; // 扩展输入板选择
	bool checkManual(void);		// 检查能否手动操作

    void setOutPortNames(int idx);  // 设置扩展输出端口名称
    void setInPortNames(int idx);   // 设置扩展输入端口名称
    void SetOutPortVisible(int idx);  // 设置扩展输出显示状态
    void SetInPortVisible(int idx);  // 设置扩展输出显示状态
    void SetOutPortState(int idx, bool init);  // 设置扩展输出显示状态
    void SetInPortState(int idx, bool init);  // 设置扩展输出显示状态

    //pyq 最大扭矩，最大转速
    int16_t maxTrqX;
    int16_t maxTrqY;
    int16_t maxTrqZ;
    int16_t maxTrqA;
    int16_t maxTrqB;
    int16_t maxTrqC;
    int16_t maxSpeedX;
    int16_t maxSpeedY;
    int16_t maxSpeedZ;
    int16_t maxSpeedA;
    int16_t maxSpeedB;
    int16_t maxSpeedC;
    //pyq end
private slots:
	// 系统工作状态信号槽
	void SetState(uint16_t state);		// 根据当前系统状态设置页面控件使能属性(自动状态只能观察端口不能手动)
	// IO信号槽
    void SetInIO(bool init);
    void SetOutIO(bool init);
    void InputIO(void);
    void OutputIO(void);
	// 输出控制信号槽
	void ParmCtrl(int code);
    void RarmCtrl(int code);
    void RarmAscDesCtrl(void);
    void RarmAdvCtrl(void);
    void RarmRetCtrl(void);
    void ConvCtrl(void);//传送带
    void CutCtrl(void);//剪刀
	void ImmCtrl(int code);
    void EoCtrl(int code);
    void UpdataActualServo(int16_t actualTrqX,int16_t actualTrqY,int16_t actualTrqZ,int16_t actualTrqA,int16_t actualTrqB,int16_t actualTrqC
          ,int16_t actualSpeedX,int16_t actualSpeedY,int16_t actualSpeedZ,int16_t actualSpeedA,int16_t actualSpeedB,int16_t actualSpeedC);
    void OutputSelect(int idx);
//    void InputSelect(int idx);
};

#endif // FORMMANUAL_H
