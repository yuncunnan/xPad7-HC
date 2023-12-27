#ifndef VCODEVACUUM_H
#define VCODEVACUUM_H

#include "xconfig.h"
#include "xmlmodelitem.h"
class FormVActVacuum;

class VCodeVacuum : public XmlModelItem
{
	Q_OBJECT
public:
    explicit VCodeVacuum(QWidget *form);

    virtual bool XmlRead(QXmlStreamReader &reader);
    virtual bool XmlWrite(QXmlStreamWriter &writer);

    virtual bool Update(bool bSaveAndValidate = true);

    virtual bool GenerateCode(quint16 *code, quint32 *para, quint8 other = 0);
    virtual bool IsModified();

    void SetUserVar(quint16 var, int idx = 0);
    quint16 GetUserVar(int idx = 0);

    int GetVar(int idx = 0){if (idx==0) return m_outvar; else return m_invar;}
private:
    int m_interval;
    int m_type;//0表示关闭，1表示打开
    int m_delay;    //0.1s
    int m_outvar;
    int m_invar;
    quint16 m_extout_counter;
    quint16 m_extin_counter;
    FormVActVacuum *m_form;
protected:
    virtual void UpdateBaseMember();
    bool XmlReadPara(QXmlStreamReader &reader);
};

#endif // VCODEVACUUM_H
