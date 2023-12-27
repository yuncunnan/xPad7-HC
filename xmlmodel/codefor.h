#ifndef CODEFOR_H
#define CODEFOR_H

#include "xconfig.h"
#include "xmlmodelitem.h"
class FormActFor;

class CodeFor : public XmlModelItem
{
	Q_OBJECT
public:
    explicit CodeFor(QWidget* form, int type);

    virtual bool XmlRead(QXmlStreamReader &reader);
    virtual bool XmlWrite(QXmlStreamWriter &writer);

    virtual bool Update(bool bSaveAndValidate = true);

    virtual bool GenerateCode(quint16 *code, quint32 *para, quint8 other = 0);
    virtual bool IsModified();
    void SetUserVar(quint16 var, int idx = 0);
    quint16 GetUserVar(int idx = 0);

private:
    int m_value;
    int m_value_type;
    quint16 m_counter;
    FormActFor *m_form;
    bool XmlReadPara(QXmlStreamReader &reader);

protected:
    virtual void UpdateBaseMember();
};

#endif // CODEFOR_H
