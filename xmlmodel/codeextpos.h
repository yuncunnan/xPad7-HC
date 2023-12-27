#ifndef CODEEXTPOS_H
#define CODEEXTPOS_H

#include "xconfig.h"
#include "xmlmodelitem.h"
class FormActExtPos;

class CodeExtPos : public XmlModelItem
{
	Q_OBJECT
public:
    explicit CodeExtPos(QWidget* form);

    virtual bool XmlRead(QXmlStreamReader &reader);
    virtual bool XmlWrite(QXmlStreamWriter &writer);

    virtual bool Update(bool bSaveAndValidate = true);

    virtual bool GenerateCode(quint16 *code, quint32 *para, quint8 other = 0);
    virtual bool IsModified();
    int GetAxesbmp() {return m_axes;}

    void SetParas(qint8 axis, int speed, int pos, int delay, int type, int offset = 0)
    {
        m_axes = 1<<axis;
        m_speed = speed;
        m_type = offset;//绝对定位0
        m_delay = delay;
        switch(axis)
        {
        case AXES_IDX_X:
            m_x_type = type;
            m_x = pos;
            break;
        case AXES_IDX_Y:
            m_y_type = type;
            m_y = pos;
            break;
        case AXES_IDX_Z:
            m_z_type = type;
            m_z = pos;
            break;
        case AXES_IDX_A:
            m_a_type = type;
            m_a = pos;
            break;
        case AXES_IDX_B:
            m_b_type = type;
            m_b = pos;
            break;
//        case AXES_IDX_C:
        default:
            m_c_type = type;
            m_c = pos;
            break;
        }
        UpdateBaseMember();
    }
private:
    int m_axes;
    int m_speed;
    int m_x_type;
    int m_y_type;
    int m_z_type;
    int m_a_type;
    int m_b_type;
    int m_c_type;
    int m_x;
    int m_y;
    int m_z;
    int m_a;
    int m_b;
    int m_c;
    int m_type;//绝对定位0
    int m_delay;

    int m_advdec;      //提前变速
    int m_advspeed; //变速速度
    int m_advfinish;   //提前结束
    int m_advdis;   //变速距离
    int m_enddis;   // 结束距离
    int m_accspeed;      //加速度
    int m_jerkspeed;      //jerk加加速

    FormActExtPos *m_form;
protected:
    virtual void UpdateBaseMember();
    bool XmlReadPara(QXmlStreamReader &reader);
};

#endif // CODEEXTPOS_H
