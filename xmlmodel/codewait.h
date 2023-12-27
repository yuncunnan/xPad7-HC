#ifndef CODEWAIT_H
#define CODEWAIT_H

#include "xconfig.h"
#include "xmlmodelitem.h"
class FormActWait;

class CodeWait : public XmlModelItem
{
	Q_OBJECT
public:
    explicit CodeWait(QWidget* form);

    virtual bool XmlRead(QXmlStreamReader &reader);
    virtual bool XmlWrite(QXmlStreamWriter &writer);

    virtual bool Update(bool bSaveAndValidate = true);

    virtual bool GenerateCode(quint16 *code, quint32 *para, quint8 other = 0);
    virtual bool IsModified();
    void SetParas(int isoff, int var1, int timeout, int var2, int validtime)
    {
        m_isoff = isoff;
        m_var1 = var1;
        m_var2 = var2;
        m_timeout = timeout;
        m_validtime = validtime;
        UpdateBaseMember();
    }

private:
	int m_isoff;
    int m_var1;    //0.1s
    int m_var2;
    int m_var2_isconst;
    int m_timeout;
    int m_timeout_type;
    int m_validtime;
    FormActWait *m_form;
    bool XmlReadPara(QXmlStreamReader &reader);

protected:
    virtual void UpdateBaseMember();
};

#endif // CODEDELAY_H
