#ifndef CODECBEGIN_H
#define CODECBEGIN_H

#include "xconfig.h"
#include "xmlmodelitem.h"
class FormActNull;

class CodeCBegin : public XmlModelItem
{
	Q_OBJECT
public:
    explicit CodeCBegin(QWidget* form);

    virtual bool XmlWrite(QXmlStreamWriter &writer);
    /////////////////////////////////////////////////////////////////////
private:
    FormActNull *m_form;
};

#endif // CODECBEGIN_H
