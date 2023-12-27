#ifndef CODEEND_H
#define CODEEND_H

#include "xconfig.h"
#include "xmlmodelitem.h"
class FormActNull;

class CodeEnd : public XmlModelItem
{
	Q_OBJECT
public:
    explicit CodeEnd(QWidget* form);
    virtual bool XmlWrite(QXmlStreamWriter &writer);

private:
    FormActNull *m_form;
};

#endif // CODEEND_H
