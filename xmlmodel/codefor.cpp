#include "xconfig.h"
#include "formactfor.h"
#include "codefor.h"
#include "xstringresource.h"

CodeFor::CodeFor(QWidget *form, int type) :	XmlModelItem(QIcon(":/img/action/For.png"), form)
{
	m_form = (FormActFor*)form;
	m_value = 1;
	m_value_type = CODE_FOR_CONST;
    m_codes = 1;
    UpdateBaseMember();
}
bool CodeFor::XmlReadPara(QXmlStreamReader &reader)
{
	QString name = reader.attributes().value(XML_ATTR_NAME).toString();
	if (name==XML_PNAME_PARA1)
	{
		QString val = reader.readElementText();
		m_value = val.toInt();
		UpdateBaseMember();
		if (reader.isEndElement())
			reader.readNext();
	}
	else
		XmlSkipUnknownElement(reader);
	return true;
}
bool CodeFor::XmlRead(QXmlStreamReader &reader)
{
	QString type = reader.attributes().value(XML_ATTR_TYPE).toString();
	m_value_type = CODE_FOR_CONST;
	if (type==XML_TYPE_VAR)
		m_value_type = CODE_FOR_VAR;

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
bool CodeFor::XmlWrite(QXmlStreamWriter &writer)
{
	writer.writeStartElement(XML_ELEMENT_CODE);
	writer.writeAttribute(XML_ATTR_NAME, XML_CNAME_FOR);
	if (m_value_type==CODE_FOR_CONST)
		writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_CONST);
	else
		writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_VAR);
    writer.writeAttribute(XML_ATTR_NOTE, m_note);
    writer.writeAttribute(XML_ATTR_FLAG, QString("%1").arg(m_flag));


		writer.writeStartElement(XML_ELEMENT_PARA);
		writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA1);
			writer.writeCharacters(QString("%1").arg(m_value));
		writer.writeEndElement();
	writer.writeEndElement();
	return true;
}
bool CodeFor::Update(bool bSaveAndValidate)
{
	if (m_form)
	{
		if (bSaveAndValidate)
		{
			bool change=false;
			if (m_value != m_form->GetValue())
			{
				m_value = m_form->GetValue();
				change=true;
			}
			if (m_value_type != m_form->GetType())
			{
				m_value_type = m_form->GetType();
				change=true;
			}
			if (change) UpdateBaseMember();
			return change;
		}
		else
		{
			m_form->SetType(m_value_type);
			m_form->SetValue(m_value);
			m_form->UpdateWidgetState();
		}
	}
	return false;
}
bool CodeFor::GenerateCode(quint16* code, quint32 *para, quint8 other)
{
    code[0] = m_value_type | (((quint16)m_flag) << 8);
	para[0] = m_value;
	return true;
}

void CodeFor::UpdateBaseMember()
{
	QString para;

	m_code = m_value_type;
	if (m_value_type==CODE_FOR_CONST)
	{
		para = QString(" %1 ").arg(m_value);
	}
	else
	{
        para = QString(("[")) + xStringResource::GetVarName(m_value) + QString(("]"));
	}
	m_name = QString(tr("循环")) + para + QString(tr("次"));
}

bool CodeFor::IsModified()
{
	if (m_form)
	{
		if ((m_value != m_form->GetValue())||
			(m_value_type != m_form->GetType()))
			return true;
	}
	return XmlModelItem::IsModified();
}
void CodeFor::SetUserVar(quint16 var, int idx)
{
    if (m_value_type == CODE_FOR_VAR)
        m_value = var;
}

quint16 CodeFor::GetUserVar(int idx)
{
    if (m_value_type == CODE_FOR_CONST)
        return 0;
    else
    {
        if ((m_value&MASK_VAR_TYPE) == VAR_TYPE_USR)
            return m_value;
        else
            return 0;
    }
}
