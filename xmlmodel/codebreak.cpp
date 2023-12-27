#include "formactnull.h"
#include "codebreak.h"

CodeBreak::CodeBreak(QWidget *form) :
	XmlModelItem(QIcon(":/img/action/For.png"), form, QObject::tr("循环跳出")),
    m_form((FormActNull*)form)
{
    m_code = CODE_BREAK;
}

bool CodeBreak::XmlWrite(QXmlStreamWriter &writer)
{
	writer.writeStartElement(XML_ELEMENT_CODE);
	writer.writeAttribute(XML_ATTR_NAME, XML_CNAME_BREAK);
    writer.writeAttribute(XML_ATTR_NOTE, m_note);
    writer.writeAttribute(XML_ATTR_FLAG, QString("%1").arg(m_flag));

	writer.writeEndElement();
	return true;
}
