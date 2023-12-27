#ifndef CODEOPERATOR_H
#define CODEOPERATOR_H

#include "xconfig.h"
#include "xmlmodelitem.h"
class FormActOperate;

class CodeOperator : public XmlModelItem
{
	Q_OBJECT
public:
    explicit CodeOperator(QWidget *form, int type);

	virtual bool XmlRead(QXmlStreamReader &reader);
	virtual bool XmlWrite(QXmlStreamWriter &writer);

	virtual bool Update(bool bSaveAndValidate = true);

    virtual bool GenerateCode(quint16 *code, quint32 *para, quint8 other = 0);
    virtual bool IsModified();
    void SetUserVar(quint16 var, int idx = 0);
    quint16 GetUserVar(int idx = 0);

private:
	int m_var1;
    int m_type;
    int m_para;
    int m_para_type;
    FormActOperate *m_form;
	bool XmlReadPara(QXmlStreamReader &reader);
protected:
	virtual void UpdateBaseMember();
};

#endif // CODEOPERATOR_H
