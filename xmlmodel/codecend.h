#ifndef CODECEND_H
#define CODECEND_H

#include "xconfig.h"
#include "xmlmodelitem.h"
class FormActNull;

class CodeCEnd : public XmlModelItem
{
	Q_OBJECT
public:
    explicit CodeCEnd(QWidget* form);
    virtual bool XmlWrite(QXmlStreamWriter &writer);

private:
    FormActNull *m_form;
};

#endif // CODECEND_H
