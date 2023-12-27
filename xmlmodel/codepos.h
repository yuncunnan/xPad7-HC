#ifndef CODEPOS_H
#define CODEPOS_H

#include "xconfig.h"
#include "xmlmodelitem.h"
class FormActPos;

class CodePos : public XmlModelItem
{
	Q_OBJECT
public:
    explicit CodePos(QWidget* form);

    virtual bool XmlRead(QXmlStreamReader &reader);
    virtual bool XmlWrite(QXmlStreamWriter &writer);

    virtual bool Update(bool bSaveAndValidate = true);

    virtual bool GenerateCode(quint16 *code, quint32 *para, quint8 other = 0);
    virtual bool IsModified();
    int GetAxesbmp() {return m_axes;}

    void SetParas(qint8 axis, int speed, int pos, int delay, int type = POS_TYPE_POINT)
    {
        m_axes = 1<<axis;
        m_speed = speed;
        m_type = 0;//绝对定位0
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
//            m_c_type = POS_TYPE_POINT;
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
    FormActPos *m_form;
protected:
    virtual void UpdateBaseMember();
    bool XmlReadPara(QXmlStreamReader &reader);
};

#endif // CODEPOS_H
