#ifndef CODELOOPMATRIX_H
#define CODELOOPMATRIX_H

#include "xconfig.h"
#include "xmlmodelitem.h"
class FormActLoopMatrix;

class CodeLoopMatrix : public XmlModelItem
{
	Q_OBJECT
public:
    explicit CodeLoopMatrix(QWidget *form);
    ~CodeLoopMatrix();
    virtual bool XmlRead(QXmlStreamReader &reader);
    virtual bool XmlWrite(QXmlStreamWriter &writer);

    virtual bool Update(bool bSaveAndValidate = true);

    virtual bool GenerateCode(quint16 *code, quint32 *para, quint8 other = 0);
//    virtual void GetExtData(void* ptr);
    virtual bool IsModified();

    void SetUserVar(quint16 var, int idx = 0);
    quint16 GetUserVar(int idx = 0);

    bool isrunner(void){return m_isrunner;}

    void SetParas(quint8 speed, quint8 dspeed, quint16 dlen, quint8 decaxisprior, bool isrun, bool trvrot, bool decaxis, bool horizontal, bool rel[], quint16 num[], qint16 interval[], qint32 pos[], quint16 conveyor_delay, quint16 conveyor_out, bool Conveyor_Use, quint8 horspeed = 50, quint8 trvspeed = 50)
    {
        m_speed = speed;
        m_dspeed = dspeed;
        m_dlen = dlen;
        m_trvrot = trvrot;
        m_isrunner = isrun;
        m_dec_axes = decaxis;
        m_horizontal = horizontal;
        m_dec_axes_prior = decaxisprior;
        m_rel_posx = rel[0];
        m_rel_posy = rel[1];
        m_rel_posz = rel[2];
        m_xs = num[0];
        m_ys = num[1];
        m_zs = num[2];
        m_x_interval = interval[0];
        m_y_interval = interval[1];
        m_z_interval = interval[2];
        m_posx = pos[0];
        m_posy = pos[1];
        m_posz = pos[2];
        m_conveyor_delay = conveyor_delay;
        m_conveyor_out = conveyor_out;
        ConveyorUse = Conveyor_Use;
        m_horspeed = horspeed;
        m_trvspeed = trvspeed;
    }

private:

	quint16 m_counter;       // 计数器
    quint8 m_speed;         // 运行速度（新程序为上下）
    quint8 m_horspeed;      // 引拔轴速度
    quint8 m_trvspeed;      // 横行轴速度
    quint8 m_dspeed;        // 减速速度
    quint16 m_dlen;         // 减速距离
    bool m_isrunner;        // 副臂
    bool m_trvrot;
    bool m_dec_axes;
    bool m_horizontal;      //倒角方式	0:表示回正 1:表示侧姿
    quint8 m_dec_axes_prior;
    bool m_rel_posx;		//引拨轴第一点位置是相对位置
    bool m_rel_posy;		//上下轴第一点位置是相对位置
    bool m_rel_posz;		//横行轴第一点位置是相对位置

    quint16 m_xs;			//引拨轴数量
    qint16 m_x_interval;	//引拨轴间隔

    quint16 m_ys;			//上下轴数量
    qint16 m_y_interval;	//上下轴间隔

    quint16 m_zs;			//横行轴数量
    qint16 m_z_interval; 	//横行轴间隔

    qint32 m_posx;			//引拨轴第一点位置
    qint32 m_posy;			//上下轴第一点位置
    qint32 m_posz;			//横行轴第一点位置

    int m_conveyor_delay;	//输送带延时
	quint16 m_conveyor_out;		//输送带端口
	bool ConveyorUse;			//使用输送带

    FormActLoopMatrix *m_form;
protected:
    bool XmlReadPara(QXmlStreamReader &reader);
};

#endif // CODELOOPMATRIX_H
