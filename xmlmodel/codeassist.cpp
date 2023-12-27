#include "xconfig.h"
#include "formactassist.h"
#include "codeassist.h"
#include "xstringresource.h"

CodeAssist::CodeAssist(QWidget *form) :	XmlModelItem(QIcon(":/img/action/ExtOutput.png"), form)
{
    m_code = VCODE_ASSIST;
    m_form = (FormActAssist*)form;
	m_type = 0;
	m_delay = 5;
    m_var1 = EM1_VAR_Y08;
	m_interval = 0;
    m_codes = 2;
    m_counter = 0;
    UpdateBaseMember();
}
bool CodeAssist::XmlReadPara(QXmlStreamReader &reader)
{
	QString name = reader.attributes().value(XML_ATTR_NAME).toString();
	if ((name==XML_PNAME_PARA1)||
		(name==XML_PNAME_PARA2)||
        (name==XML_PNAME_PARA3)||
        (name==XML_PNAME_PARA4))
    {
		QString val = reader.readElementText();
		if (name==XML_PNAME_PARA1) m_var1 = val.toInt();
		if (name==XML_PNAME_PARA2) m_delay = val.toInt();
        if (name==XML_PNAME_PARA3) m_interval = val.toInt();
        if (name==XML_PNAME_PARA4) m_counter = val.toInt();
        UpdateBaseMember();
		if (reader.isEndElement())
			reader.readNext();
	}
	else
		XmlSkipUnknownElement(reader);
	return true;
}
bool CodeAssist::XmlRead(QXmlStreamReader &reader)
{
	QString type = reader.attributes().value(XML_ATTR_TYPE).toString();
	m_type=0;
	if (type==XML_TYPE_ON)
		m_type=1;
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
bool CodeAssist::XmlWrite(QXmlStreamWriter &writer)
{
	writer.writeStartElement(XML_ELEMENT_CODE);
    writer.writeAttribute(XML_ATTR_NAME, XML_CNAME_ASSIST);
	if (m_type==1)
		writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_ON);
    else
        writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_OFF);
    writer.writeAttribute(XML_ATTR_NOTE, m_note);
    writer.writeAttribute(XML_ATTR_FLAG, QString("%1").arg(m_flag));


    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA1);
    writer.writeCharacters(QString("%1").arg(m_var1));
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA2);
    writer.writeCharacters(QString("%1").arg(m_delay));
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA3);
    writer.writeCharacters(QString("%1").arg(m_interval));
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA4);
    writer.writeCharacters(QString("%1").arg(m_counter));
    writer.writeEndElement();

    writer.writeEndElement();
	return true;
}
bool CodeAssist::Update(bool bSaveAndValidate)
{
	if (m_form)
	{
		if (bSaveAndValidate)
		{
			bool change=false;
			if (m_delay != m_form->GetDelay())
			{
				m_delay = m_form->GetDelay();
				change=true;
			}
			if (m_interval != m_form->GetInterval())
			{
				m_interval = m_form->GetInterval();
				change=true;
			}
			if (m_type != m_form->GetType())
			{
				m_type = m_form->GetType();
				change=true;
			}
            if (m_var1 != m_form->GetOutput())
            {
                m_var1 = m_form->GetOutput();
                change=true;
            }
            if (change) UpdateBaseMember();
			return change;
		}
		else
		{
			m_form->SetInterval(m_interval);
			m_form->SetDelay(m_delay);
			m_form->SetType(m_type);
            m_form->SetOutput(m_var1);
			m_form->UpdateWidgetState();
		}
	}
	return false;
}

bool CodeAssist::GenerateCode(quint16* code, quint32 *para, quint8 other)
{
    code[0] = CODE_EXT_OUT | (((quint16)m_flag) << 8);
    para[0] = (m_var1 & 0xFFF);
    para[0] |= m_type<<12;
    para[0] |= m_delay<<16;

    code[1] = CODE_CONST | (((quint16)m_flag) << 8);
    para[1] = m_counter;
    para[1] |= m_interval << 16;
    return true;
}

void CodeAssist::UpdateBaseMember()
{
	QString para;
	if (m_interval)
		para = QString(tr(" 每")) + QString(" %1 ").arg(m_interval+1) + QString(tr("周期一次"));
    if (m_type==1)
    {
        if (m_var1 == EM1_VAR_Y08)
            m_name = QString(tr("[打油开] 时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒")) + para;
        if (m_var1 == EM1_VAR_Y09)
            m_name = QString(tr("[传送带开] 时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒")) + para;
        if (m_var1 == EM1_VAR_Y10)
            m_name = QString(tr("[不良品] 时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒")) + para;
    }
    else
    {
        if (m_var1 == EM1_VAR_Y08)
            m_name = QString(tr("[打油关] 时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒")) + para;
        if (m_var1 == EM1_VAR_Y09)
            m_name = QString(tr("[传送带关] 时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒")) + para;
        if (m_var1 == EM1_VAR_Y10)
            m_name = QString(tr("[不良品] 时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒")) + para;
    }
}

bool CodeAssist::IsModified()
{
	if (m_form)
	{
        if ((m_var1 != m_form->GetOutput())||
			(m_type != m_form->GetType())||
            (m_delay != m_form->GetDelay())||
            (m_interval != m_form->GetInterval()))
			return true;
	}
	return XmlModelItem::IsModified();
}
void CodeAssist::SetUserVar(quint16 var, int idx)
{
    m_counter = var;
}

quint16 CodeAssist::GetUserVar(int idx)
{
    if ((m_counter &MASK_VAR_TYPE) == VAR_TYPE_USR)
        return m_counter;
    return 0;
}
