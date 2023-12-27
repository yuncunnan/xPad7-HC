#include "formactnull.h"
#include "codeend.h"

CodeEnd::CodeEnd(QWidget *form) : XmlModelItem(QIcon(":/img/action/PgmEnd.png"), form, QObject::tr("程序结束")),
    m_form((FormActNull*)form)
{
    m_code = CODE_END;
}

bool CodeEnd::XmlWrite(QXmlStreamWriter &writer)
{
	writer.writeStartElement(XML_ELEMENT_CODE);
	writer.writeAttribute(XML_ATTR_NAME, XML_CNAME_END);
    writer.writeAttribute(XML_ATTR_NOTE, m_note);
    writer.writeAttribute(XML_ATTR_FLAG, QString("%1").arg(m_flag));

	writer.writeEndElement();
	return true;
}

