#ifndef CODEMEXTOUT_H
#define CODEMEXTOUT_H

#include "xconfig.h"
#include "xmlmodelitem.h"
class FormActMExtOut;

class CodeMExtOut : public XmlModelItem
{
	Q_OBJECT
public:
    explicit CodeMExtOut(QWidget *form);

    virtual bool XmlRead(QXmlStreamReader &reader);
    virtual bool XmlWrite(QXmlStreamWriter &writer);

    virtual bool Update(bool bSaveAndValidate = true);

    virtual bool GenerateCode(quint16 *code, quint32 *para, quint8 other = 0);
    virtual bool IsModified();

    void SetUserVar(quint16 var, int idx = 0);
    quint16 GetUserVar(int idx = 0);

    void SetParas(int type, int outbmp, int delay)
    {
        m_type = type;
        m_delay = delay;
        m_outbmp = outbmp;
        UpdateBaseMember();
    }

private:
    int m_delay;    //0.1s
    int m_outbmp;
    int m_type;//0表示关闭，1表示打开
    quint16 m_counter;       // 计数器

    FormActMExtOut *m_form;
protected:
    virtual void UpdateBaseMember();
    bool XmlReadPara(QXmlStreamReader &reader);
};

#endif // CODEMEXTOUT_H
