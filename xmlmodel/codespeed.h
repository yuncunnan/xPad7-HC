#ifndef CODESPEED_H
#define CODESPEED_H

#include "xconfig.h"
#include "xmlmodelitem.h"
class FormActSpeed;

class CodeSpeed : public XmlModelItem
{
	Q_OBJECT
public:
	explicit CodeSpeed(QWidget* form);
	bool XmlReadPara(QXmlStreamReader &reader);
	virtual bool XmlRead(QXmlStreamReader &reader);
	virtual bool XmlWrite(QXmlStreamWriter &writer);
    /////////////////////////////////////////////////////////////////////
    virtual bool GenerateCode(quint16 *code, quint32 *para, quint8 other = 0);

    virtual bool Update(bool bSaveAndValidate = true);
    void UpdateBaseMember();
    virtual bool IsModified();
    int GetAxes(){return m_axes;}
private:
    quint32 m_speed;
    int m_axes;
private:
    FormActSpeed *m_form;
};

#endif // CODEBREAK_H
