#ifndef CODEVACUUM_H
#define CODEVACUUM_H

#include "xconfig.h"
#include "cmbprotocol.h"
#include "xmlmodelitem.h"
class FormActVacuum;

class CodeVacuum : public XmlModelItem
{
	Q_OBJECT
public:
    explicit CodeVacuum(QWidget *form);

    virtual bool XmlRead(QXmlStreamReader &reader);
    virtual bool XmlWrite(QXmlStreamWriter &writer);

    virtual bool Update(bool bSaveAndValidate = true);

    virtual bool GenerateCode(quint16 *code, quint32 *para, quint8 other = 0);
    virtual bool IsModified();

    void SetUserVar(quint16 var, int idx = 0);
    quint16 GetUserVar(int idx = 0);

    int GetOutBmp(void){return m_outbmp;}
    int GetInBmp(void){return m_inbmp;}

    void SetParas(bool ison, int delay, quint16 outbmp, quint16 inbmp, int interval = 0)
    {
        m_interval = interval;
        m_type = ison;
        m_delay = delay;
        m_outbmp = outbmp;
        m_inbmp = inbmp;
        UpdateBaseMember();
    }

private:
    int m_interval;
    int m_type;//0表示关闭，1表示打开
    int m_delay;    //0.1s
    quint16 m_outbmp;
    quint16 m_inbmp;
    quint16 m_counter;
    FormActVacuum *m_form;
protected:
    virtual void UpdateBaseMember();
    bool XmlReadPara(QXmlStreamReader &reader);
};

#endif // CODEVACUUM_H
