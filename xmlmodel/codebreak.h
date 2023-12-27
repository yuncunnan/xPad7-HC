#ifndef CODEBREAK_H
#define CODEBREAK_H

#include "xconfig.h"
#include "xmlmodelitem.h"
class FormActNull;

class CodeBreak : public XmlModelItem
{
	Q_OBJECT
public:
    explicit CodeBreak(QWidget* form);
    virtual bool XmlWrite(QXmlStreamWriter &writer);
    /////////////////////////////////////////////////////////////////////
private:
    FormActNull *m_form;
};

#endif // CODEBREAK_H
