#ifndef CODEENDIF_H
#define CODEENDIF_H

#include "xconfig.h"
#include "xmlmodelitem.h"
class FormActNull;

class CodeEndIf : public XmlModelItem
{
	Q_OBJECT
public:
    explicit CodeEndIf(QWidget* form);
    virtual bool XmlWrite(QXmlStreamWriter &writer);

private:
    FormActNull *m_form;
};

#endif // CODEENDIF_H
