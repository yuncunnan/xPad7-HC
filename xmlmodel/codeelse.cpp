﻿#include "formactnull.h"
#include "codeelse.h"

CodeElse::CodeElse(QWidget *form) :
	XmlModelItem(QIcon(":/img/action/If.png"), form, QObject::tr("否则")),
    m_form((FormActNull*)form)
{
    m_code = CODE_ELSE;
}

bool CodeElse::XmlWrite(QXmlStreamWriter &writer)
{
	writer.writeStartElement(XML_ELEMENT_CODE);
	writer.writeAttribute(XML_ATTR_NAME, XML_CNAME_ELSE);
    writer.writeAttribute(XML_ATTR_NOTE, m_note);
    writer.writeAttribute(XML_ATTR_FLAG, QString("%1").arg(m_flag));

	writer.writeEndElement();
	return true;
}
