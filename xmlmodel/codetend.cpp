#include "formactnull.h"
#include "codetend.h"

CodeTEnd::CodeTEnd(QWidget *form) :	XmlModelItem(QIcon(":/img/action/PathEnd.png"), form, QObject::tr("路径结束")),
	m_form((FormActNull*)form)
{
	m_code = CODE_TEND;
}

bool CodeTEnd::XmlWrite(QXmlStreamWriter &writer)
{
	writer.writeStartElement(XML_ELEMENT_CODE);
	writer.writeAttribute(XML_ATTR_NAME, XML_CNAME_TEND);
    writer.writeAttribute(XML_ATTR_NOTE, m_note);
    writer.writeAttribute(XML_ATTR_FLAG, QString("%1").arg(m_flag));

	writer.writeEndElement();
	return true;
}

