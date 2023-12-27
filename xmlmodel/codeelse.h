#ifndef CODEELSE_H
#define CODEELSE_H

#include "xconfig.h"
#include "xmlmodelitem.h"
class FormActNull;

class CodeElse : public XmlModelItem
{
	Q_OBJECT
public:
    explicit CodeElse(QWidget* form);
    virtual bool XmlWrite(QXmlStreamWriter &writer);

private:
    FormActNull *m_form;
};

#endif // CODEELSE_H
