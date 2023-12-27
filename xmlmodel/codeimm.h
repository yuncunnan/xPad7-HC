#ifndef CODEIMM_H
#define CODEIMM_H

#include "xconfig.h"
#include "xmlmodelitem.h"
#include "cmbprotocol.h"
class FormActIMM;

class CodeImm : public XmlModelItem
{
	Q_OBJECT
public:
    explicit CodeImm(QWidget* form);

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
    int m_delay;
    FormActIMM *m_form;
    bool XmlReadPara(QXmlStreamReader &reader);

protected:
    virtual void UpdateBaseMember();
};

#endif // CODEIMM_H
