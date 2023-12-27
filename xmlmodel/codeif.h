#ifndef CODEIF_H
#define CODEIF_H

#include "xconfig.h"
#include "xmlmodelitem.h"
class FormActIf;

class CodeIf : public XmlModelItem
{
	Q_OBJECT
public:
    explicit CodeIf(QWidget* form, int type=IF_TYPE_DIR);

    virtual bool XmlRead(QXmlStreamReader &reader);
    virtual bool XmlWrite(QXmlStreamWriter &writer);

    virtual bool Update(bool bSaveAndValidate = true);

    virtual bool GenerateCode(quint16 *code, quint32 *para, quint8 other = 0);
    virtual bool IsModified();
    void SetUserVar(quint16 var, int idx = 0);
    quint16 GetUserVar(int idx = 0);

private:
    int m_var1;
    int m_para1;
    int m_para1_type;//0表示立即数，1表示变量
    int m_type;
	quint16 m_counter;       // 计数器
	quint16 m_timeout;
    FormActIf *m_form;

protected:
    virtual void UpdateBaseMember();
    bool XmlReadPara(QXmlStreamReader &reader);
};

#endif // CODEIF_H
