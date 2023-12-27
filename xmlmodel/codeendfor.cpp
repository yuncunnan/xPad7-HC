#include "formactnull.h"
#include "codeendfor.h"

CodeEndFor::CodeEndFor(QWidget *form) :
	XmlModelItem(QIcon(":/img/action/For.png"), form, QObject::tr("循环结束")),
    m_form((FormActNull*)form)
{
    m_code = CODE_ENDFOR;
}

bool CodeEndFor::XmlWrite(QXmlStreamWriter &writer)
{
	writer.writeStartElement(XML_ELEMENT_CODE);
	writer.writeAttribute(XML_ATTR_NAME, XML_CNAME_ENDFOR);
    writer.writeAttribute(XML_ATTR_NOTE, m_note);
    writer.writeAttribute(XML_ATTR_FLAG, QString("%1").arg(m_flag));

	writer.writeEndElement();
	return true;
}

