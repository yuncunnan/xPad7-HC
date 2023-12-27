#ifndef CODEENDFOR_H
#define CODEENDFOR_H

#include "xconfig.h"
#include "xmlmodelitem.h"
class FormActNull;

class CodeEndFor : public XmlModelItem
{
	Q_OBJECT
public:
    explicit CodeEndFor(QWidget* form);
    virtual bool XmlWrite(QXmlStreamWriter &writer);

private:
    FormActNull *m_form;
};

#endif // CODEENDFOR_H
