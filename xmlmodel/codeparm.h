#ifndef CODEPARM_H
#define CODEPARM_H

#include "xconfig.h"
#include "xmlmodelitem.h"
#include "cmbprotocol.h"
class FormActPro;

class CodePArm : public XmlModelItem
{
	Q_OBJECT
public:
    explicit CodePArm(QWidget *form);

    virtual bool XmlRead(QXmlStreamReader &reader);
    virtual bool XmlWrite(QXmlStreamWriter &writer);

    virtual bool Update(bool bSaveAndValidate = true);

    virtual bool GenerateCode(quint16 *code, quint32 *para, quint8 other = 0);
    virtual bool IsModified();
    int GetType(){return m_type;}

    void SetParas(int type, int delay)
    {
        m_type = type;
        m_delay = delay;
        UpdateBaseMember();
    }

private:
    int m_type;
    int m_delay;    //0.1s
    FormActPro *m_form;
protected:
    virtual void UpdateBaseMember();
    bool XmlReadPara(QXmlStreamReader &reader);
};

#endif // CODEPARM_H
