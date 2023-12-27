#include "xconfig.h"
#include "formactpath.h"
#include "codetbegin.h"
#include "xstringresource.h"

CodeTBegin::CodeTBegin(QWidget *form) :
	XmlModelItem(QIcon(":/img/action/PathBegin.png"), form)
{
	m_form = (FormActPath*)form;
	m_code = CODE_TBEGIN;
	m_path = 0;
	UpdateBaseMember();
}

bool CodeTBegin::XmlReadPara(QXmlStreamReader &reader)
{
	QString name = reader.attributes().value(XML_ATTR_NAME).toString();
	if (name==XML_PNAME_PARA1)
	{
		QString val = reader.readElementText();
		m_path = val.toInt();
		UpdateBaseMember();
		if (reader.isEndElement())
			reader.readNext();
	}
	else
		XmlSkipUnknownElement(reader);
	return true;
}
bool CodeTBegin::XmlRead(QXmlStreamReader &reader)
{
    m_note = reader.attributes().value(XML_ATTR_NOTE).toString();
    m_flag = reader.attributes().value(XML_ATTR_FLAG).toString().toUShort();
	reader.readNext();
	while (!reader.atEnd())
	{
		if (reader.isEndElement())
		{
			reader.readNext();
			break;
		}
		if (reader.isStartElement())
		{
			if (reader.name()==XML_ELEMENT_PARA)
			{
				XmlReadPara(reader);
			}
			else
			{
				XmlSkipUnknownElement(reader);
			}
		}
		else
		{
			reader.readNext();
		}
	}
	return true;
}
bool CodeTBegin::XmlWrite(QXmlStreamWriter &writer)
{
	writer.writeStartElement(XML_ELEMENT_CODE);
	writer.writeAttribute(XML_ATTR_NAME, XML_CNAME_TBEGIN);
    writer.writeAttribute(XML_ATTR_NOTE, m_note);
    writer.writeAttribute(XML_ATTR_FLAG, QString("%1").arg(m_flag));

		writer.writeStartElement(XML_ELEMENT_PARA);
		writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA1);
			writer.writeCharacters(QString("%1").arg(m_path));
		writer.writeEndElement();
	writer.writeEndElement();
	return true;
}

bool CodeTBegin::GenerateCode(quint16* code, quint32* para, quint8 other)
{
    code[0] = CODE_TBEGIN | (((quint16)m_flag) << 8);
	para[0] = m_path;
	return true;
}
bool CodeTBegin::Update(bool bSaveAndValidate)
{
	if (m_form)
	{
		if (bSaveAndValidate)
		{
			if (m_path != m_form->GetTrajTime())
			{
				m_path = m_form->GetTrajTime();
				UpdateBaseMember();
				return true;
			}
		}
		else
		{
			m_form->SetTrajTime(m_path);
		}
	}
	return false;
}
void CodeTBegin::UpdateBaseMember()
{
    m_name = QString(tr("路径开始    公差")) + QString(" %1").arg(((double)m_path)/100.00) + QString(("mm"));
}
bool CodeTBegin::IsModified()
{
	if (m_form)
	{
		if (m_path != m_form->GetTrajTime())
			return true;
	}
	return XmlModelItem::IsModified();
}
