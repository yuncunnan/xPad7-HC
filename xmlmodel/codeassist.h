#ifndef CODEASSIST_H
#define CODEASSIST_H

#include "xconfig.h"
#include "xmlmodelitem.h"
class FormActAssist;

class CodeAssist : public XmlModelItem
{
	Q_OBJECT
public:
    explicit CodeAssist(QWidget *form);

    virtual bool XmlRead(QXmlStreamReader &reader);
    virtual bool XmlWrite(QXmlStreamWriter &writer);

    virtual bool Update(bool bSaveAndValidate = true);

    virtual bool GenerateCode(quint16 *code, quint32 *para, quint8 other = 0);
    virtual bool IsModified();
    void SetUserVar(quint16 var, int idx = 0);
    quint16 GetUserVar(int idx = 0);

    int GetVar(){return m_var1;}

    void SetParas(int var, int type, int interval, int delay)
    {
        m_var1 = var;
        m_type = type;
        m_interval = interval;
        m_delay = delay;
        UpdateBaseMember();
    }

private:
    int m_interval;
    int m_type;
    int m_delay;    //0.1s
    int m_var1;
	quint16 m_counter;       // 计数器
    FormActAssist *m_form;
protected:
    virtual void UpdateBaseMember();
    bool XmlReadPara(QXmlStreamReader &reader);
};

#endif // CODEASSIST_H
