#include "xconfig.h"
#include "formactextout.h"
#include "codeextout.h"
#include "xstringresource.h"
#include "cmbprotocol.h"

CodeExtOut::CodeExtOut(QWidget *form) :	XmlModelItem(QIcon(":/img/action/ExtOutput.png"), form)
{
	m_form = (FormActExtOut*)form;
	m_type = 0;
	m_delay = 5;
    if(CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)
        m_var1 = MAIN_VAR_Y15;
    else if((CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_5AXIS)||(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H730_5AXIS))
		m_var1 = MAIN_VAR_Y07;
    else
	m_var1 = EM1_VAR_Y02;
	m_interval = 0;
    m_codes = 2;
    m_counter = 0;
    m_code = CODE_EXT_OUT;
    UpdateBaseMember();
}
bool CodeExtOut::XmlReadPara(QXmlStreamReader &reader)
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
bool CodeExtOut::XmlRead(QXmlStreamReader &reader)
{
	QString type = reader.attributes().value(XML_ATTR_TYPE).toString();
	m_type=0;
	if (type==XML_TYPE_ON)
		m_type=1;
    else
    if (type==XML_TYPE_PULSE)
        m_type=2;
    else
    if (type==XML_TYPE_NOT)
        m_type=3;
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
bool CodeExtOut::XmlWrite(QXmlStreamWriter &writer)
{
	writer.writeStartElement(XML_ELEMENT_CODE);
	writer.writeAttribute(XML_ATTR_NAME, XML_CNAME_EXTOUT);
	if (m_type==1)
		writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_ON);
    else
    if (m_type==2)
        writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_PULSE);
    else
    if (m_type==3)
        writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_NOT);
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
bool CodeExtOut::Update(bool bSaveAndValidate)
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
            if (m_var1 != m_form->GetVar())
            {
                m_var1 = m_form->GetVar();
                change=true;
            }
            if (m_counter != m_form->GetCounter())
            {
                m_counter = m_form->GetCounter();
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
			m_form->SetVar(m_var1);
            m_form->SetCounter(m_counter);
			m_form->UpdateWidgetState();
		}
	}
	return false;
}

bool CodeExtOut::GenerateCode(quint16* code, quint32 *para, quint8 other)
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

void CodeExtOut::UpdateBaseMember()
{
	QString para;
	if (m_interval)
	{
		para = QString(tr(" 每")) + QString(" %1 ").arg(m_interval+1) + QString(tr("周期一次"));
	}
	if (m_type==1)
        m_name = QString(tr("开启输出[")) + xStringResource::GetVarName(m_var1) + QString(tr("] 时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒")) + para;
    else
    if (m_type==2)
        m_name = QString(tr("脉冲输出[")) + xStringResource::GetVarName(m_var1) + QString(tr("] 宽度")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒")) + para;
    else
    if (m_type==3)
        m_name = QString(tr("输出取反[")) + xStringResource::GetVarName(m_var1) + QString(tr("] 宽度")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒")) + para;
    else
        m_name = QString(tr("关闭输出[")) + xStringResource::GetVarName(m_var1) + QString(tr("] 时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒")) + para;
}

bool CodeExtOut::IsModified()
{
	if (m_form)
	{
		if ((m_var1 != m_form->GetVar())||
			(m_type != m_form->GetType())||
            (m_delay != m_form->GetDelay())||
            (m_counter != m_form->GetCounter())||
            (m_interval != m_form->GetInterval()))
			return true;
	}
	return XmlModelItem::IsModified();
}
void CodeExtOut::SetUserVar(quint16 var, int idx)
{
    m_counter = var;
}

quint16 CodeExtOut::GetUserVar(int idx)
{
    if ((m_counter &MASK_VAR_TYPE) == VAR_TYPE_USR)
        return m_counter;
    return 0;
}
