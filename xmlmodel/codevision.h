#ifndef CODEVISION_H
#define CODEVISION_H

#include "xconfig.h"
#include "xmlmodelitem.h"
class FormActVision;

class CodeVision : public XmlModelItem
{
	Q_OBJECT
public:
    explicit CodeVision(QWidget* form);

    virtual bool XmlRead(QXmlStreamReader &reader);
    virtual bool XmlWrite(QXmlStreamWriter &writer);

    virtual bool Update(bool bSaveAndValidate = true);

    virtual bool GenerateCode(quint16 *code, quint32 *para, quint8 other = 0);
    virtual bool IsModified();

private:
    int m_vision;
    int m_timeout;
    int m_matchbmp;
    quint16 m_uservar[3][4];
    FormActVision *m_form;
    bool XmlReadPara(QXmlStreamReader &reader);

protected:
    virtual void UpdateBaseMember();
};

#endif // CODEVISION_H
