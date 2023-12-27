#include "formactnull.h"
#include "codeendif.h"

CodeEndIf::CodeEndIf(QWidget *form) :
	XmlModelItem(QIcon(":/img/action/If.png"), form, QObject::tr("条件结束")),
    m_form((FormActNull*)form)
{
    m_code = CODE_ENDIF;
}

bool CodeEndIf::XmlWrite(QXmlStreamWriter &writer)
{
	writer.writeStartElement(XML_ELEMENT_CODE);
	writer.writeAttribute(XML_ATTR_NAME, XML_CNAME_ENDIF);
    writer.writeAttribute(XML_ATTR_NOTE, m_note);
    writer.writeAttribute(XML_ATTR_FLAG, QString("%1").arg(m_flag));

	writer.writeEndElement();
	return true;
}
