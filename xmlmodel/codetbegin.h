#ifndef CODETBEGIN_H
#define CODETBEGIN_H

#include "xconfig.h"
#include "xmlmodelitem.h"
class FormActPath;

class CodeTBegin : public XmlModelItem
{
	Q_OBJECT
public:
	explicit CodeTBegin(QWidget* form);
	virtual bool XmlRead(QXmlStreamReader &reader);
	virtual bool XmlWrite(QXmlStreamWriter &writer);
	virtual bool Update(bool bSaveAndValidate = true);
	bool IsModified();
    virtual bool GenerateCode(quint16 *code, quint32 *para, quint8 other = 0);
private:
	int m_path;
    FormActPath *m_form;
	bool XmlReadPara(QXmlStreamReader &reader);
protected:
	virtual void UpdateBaseMember();
};

#endif // CODETBEGIN_H
