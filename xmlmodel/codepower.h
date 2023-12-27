#ifndef CODEPOWER_H
#define CODEPOWER_H

#include "xconfig.h"
#include "xmlmodelitem.h"
class FormActPower;

class CodePower : public XmlModelItem
{
	Q_OBJECT
public:
    explicit CodePower(QWidget* form);

    virtual bool XmlRead(QXmlStreamReader &reader);
    virtual bool XmlWrite(QXmlStreamWriter &writer);

    virtual bool Update(bool bSaveAndValidate = true);

    virtual bool GenerateCode(quint16 *code, quint32 *para, quint8 other = 0);
    virtual bool IsModified();
    int GetAxesbmp() {return m_axes;}

private:
    int m_axes;
    bool m_poweroff;
    FormActPower *m_form;
    
protected:
    virtual void UpdateBaseMember();
    bool XmlReadPara(QXmlStreamReader &reader);
};

#endif // CODEPARM_H
