#ifndef CODEINTERP_H
#define CODEINTERP_H

#include "xconfig.h"
#include "xmlmodelitem.h"
class FormActInterp;

class CodeInterp : public XmlModelItem
{
	Q_OBJECT
public:
    explicit CodeInterp(QWidget* form);

    virtual bool XmlRead(QXmlStreamReader &reader);
    virtual bool XmlWrite(QXmlStreamWriter &writer);

    virtual bool Update(bool bSaveAndValidate = true);

    virtual bool GenerateCode(quint16 *code, quint32 *para, quint8 other = 0);
    virtual bool IsModified();
    int GetAxesbmp() {return m_axes;}

    void SetParas(int axes, int speed, int pos[6], int type[6])
    {
        m_axes = axes;
        m_speed = speed;
        m_type = 0;
        if (axes&(1<<AXIS_IDX_PHOR))
        {
            m_x_type = type[0];
            m_x = pos[0];
        }
        if (axes&(1<<AXIS_IDX_PVER))
        {
            m_y_type = type[1];
            m_y = pos[1];
        }
        if (axes&(1<<AXIS_IDX_TRV))
        {
            m_z_type = type[2];
            m_z = pos[2];
        }
        if (axes&(1<<AXIS_IDX_RVER))
        {
            m_a_type = type[3];
            m_a = pos[3];
        }
        if (axes&(1<<AXIS_IDX_RHOR))
        {
            m_b_type = type[4];
            m_b = pos[4];
        }
        if (axes&(1<<AXIS_IDX_EXT))
        {
            m_c_type = type[5];
            m_c = pos[5];
        }
        UpdateBaseMember();
    }

private:
    int m_axes;
	quint32 m_speed;
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
    FormActInterp *m_form;
    
protected:
    virtual void UpdateBaseMember();
    bool XmlReadPara(QXmlStreamReader &reader);
};

#endif // CODEPARM_H
