#include "xconfig.h"
#include "formactdelay.h"
#include "codedelay.h"

CodeDelay::CodeDelay(QWidget *form) : XmlModelItem(QIcon(":/img/action/Delay.png"), form)
{
	m_code = CODE_DELAY;
	m_form = (FormActDelay*)form;
    m_delay = 0;
    m_codes = 1;
	UpdateBaseMember();
}
bool CodeDelay::XmlReadPara(QXmlStreamReader &reader)
{
	QString name = reader.attributes().value(XML_ATTR_NAME).toString();
	if (name==XML_PNAME_PARA1)
	{
		QString val = reader.readElementText();
		m_delay = val.toInt();
		UpdateBaseMember();
		if (reader.isEndElement())
			reader.readNext();
	}
	else
		XmlSkipUnknownElement(reader);
	return true;
}
bool CodeDelay::XmlRead(QXmlStreamReader &reader)
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
bool CodeDelay::XmlWrite(QXmlStreamWriter &writer)
{
	writer.writeStartElement(XML_ELEMENT_CODE);
	writer.writeAttribute(XML_ATTR_NAME, XML_CNAME_DELAY);
    writer.writeAttribute(XML_ATTR_NOTE, m_note);
    writer.writeAttribute(XML_ATTR_FLAG, QString("%1").arg(m_flag));

		writer.writeStartElement(XML_ELEMENT_PARA);
		writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA1);
			writer.writeCharacters(QString("%1").arg(m_delay));
		writer.writeEndElement();
	writer.writeEndElement();
	return true;
}
bool CodeDelay::Update(bool bSaveAndValidate)
{
	if (m_form)
	{
		if (bSaveAndValidate)
		{
			if (m_delay != m_form->GetDelay())
			{
				m_delay = m_form->GetDelay();
                UpdateBaseMember();
                return true;
			}
		}
		else
		{
			m_form->SetDelay(m_delay);
            UpdateBaseMember();
        }
    }
	return false;
}
bool CodeDelay::GenerateCode(quint16* code, quint32 *para, quint8 other)
{
    code[0] = CODE_DELAY | (((quint16)m_flag) << 8);
	para[0] = m_delay;
	return true;
}

void CodeDelay::UpdateBaseMember()
{
    m_name = QString(tr("延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
}
bool CodeDelay::IsModified()
{
	if (m_form)
	{
		if (m_delay != m_form->GetDelay())
			return true;
	}
	return XmlModelItem::IsModified();
}

