#ifndef CODETEND_H
#define CODETEND_H

#include "xconfig.h"
#include "xmlmodelitem.h"
class FormActNull;

class CodeTEnd : public XmlModelItem
{
	Q_OBJECT
public:
	explicit CodeTEnd(QWidget* form);

	virtual bool XmlWrite(QXmlStreamWriter &writer);
	/////////////////////////////////////////////////////////////////////
private:
	FormActNull *m_form;
};
#endif // CODETEND_H
