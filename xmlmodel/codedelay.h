#ifndef CODEDELAY_H
#define CODEDELAY_H

#include "xconfig.h"
#include "xmlmodelitem.h"
class FormActDelay;

class CodeDelay : public XmlModelItem
{
	Q_OBJECT
public:
    explicit CodeDelay(QWidget* form);

    virtual bool XmlRead(QXmlStreamReader &reader);
    virtual bool XmlWrite(QXmlStreamWriter &writer);

    virtual bool Update(bool bSaveAndValidate = true);

    virtual bool GenerateCode(quint16 *code, quint32 *para, quint8 other = 0);
    virtual bool IsModified();
    void SetParas(int delay)
    {
        m_delay = delay;
    }

private:
    int m_delay;    //0.1s
    FormActDelay *m_form;
    bool XmlReadPara(QXmlStreamReader &reader);

protected:
    virtual void UpdateBaseMember();
};

#endif // CODEDELAY_H
