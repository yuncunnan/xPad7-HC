#ifndef CODEEXTIN_H
#define CODEEXTIN_H

#include "xconfig.h"
#include "xmlmodelitem.h"
class FormActExtIn;

class CodeExtIn : public XmlModelItem
{
	Q_OBJECT
public:
    explicit CodeExtIn(QWidget *form);

    virtual bool XmlRead(QXmlStreamReader &reader);
    virtual bool XmlWrite(QXmlStreamWriter &writer);

    virtual bool Update(bool bSaveAndValidate = true);

    virtual bool GenerateCode(quint16 *code, quint32 *para, quint8 other = 0);
    virtual bool IsModified();
    void SetUserVar(quint16 var, int idx = 0);
    quint16 GetUserVar(int idx = 0);

    int GetVar(){return m_var1;}
private:
    int m_var1;
    int m_interval;
    int m_type;
	quint16 m_counter;       // 计数器
    FormActExtIn *m_form;
protected:
    virtual void UpdateBaseMember();
    bool XmlReadPara(QXmlStreamReader &reader);
};

#endif // CODEEXTIN_H
