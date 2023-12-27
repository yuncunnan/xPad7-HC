#include "xconfig.h"
#include "formactextin.h"
#include "codeextin.h"
#include "xstringresource.h"
#include "cmbprotocol.h"

CodeExtIn::CodeExtIn(QWidget *form) : XmlModelItem(QIcon(":/img/action/ExtInput.png"), form)
{
	m_form = (FormActExtIn*)form;
	m_type = 0;
	m_interval = 0;
    if(CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)
        m_var1 = MAIN_VAR_X15;
    else
	m_var1 = EM1_VAR_X02;
    m_codes = 2;
    m_counter = 0;
    m_code = CODE_EXT_IN;
    UpdateBaseMember();
}
bool CodeExtIn::XmlReadPara(QXmlStreamReader &reader)
{
	QString name = reader.attributes().value(XML_ATTR_NAME).toString();
	if ((name==XML_PNAME_PARA1)||
        (name==XML_PNAME_PARA2)||
        (name==XML_PNAME_PARA3))
    {
		QString val = reader.readElementText();
		if (name==XML_PNAME_PARA1) m_var1 = val.toInt();
        if (name==XML_PNAME_PARA2) m_interval = val.toInt();
        if (name==XML_PNAME_PARA3) m_counter = val.toInt();
        UpdateBaseMember();
		if (reader.isEndElement())
			reader.readNext();
	}
	else
		XmlSkipUnknownElement(reader);
	return true;
}
bool CodeExtIn::XmlRead(QXmlStreamReader &reader)
{
	QString type = reader.attributes().value(XML_ATTR_TYPE).toString();
	m_type=0;
	if (type==XML_TYPE_ON)
		m_type=1;
    if (type==XML_TYPE_USELESS)
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
bool CodeExtIn::XmlWrite(QXmlStreamWriter &writer)
{
	writer.writeStartElement(XML_ELEMENT_CODE);
	writer.writeAttribute(XML_ATTR_NAME, XML_CNAME_EXTIN);
    if (m_type==1)
		writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_ON);
    else if (m_type==3)
        writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_USELESS);
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
            writer.writeCharacters(QString("%1").arg(m_interval));
        writer.writeEndElement();

        writer.writeStartElement(XML_ELEMENT_PARA);
        writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA3);
            writer.writeCharacters(QString("%1").arg(m_counter));
        writer.writeEndElement();

    writer.writeEndElement();
	return true;
}
bool CodeExtIn::Update(bool bSaveAndValidate)
{
	if (m_form)
	{
		if (bSaveAndValidate)
		{
			bool change=false;
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
			m_form->SetType(m_type);
			m_form->SetVar(m_var1);
            m_form->SetCounter(m_counter);
			m_form->UpdateWidgetState();
		}
	}
	return false;
}

bool CodeExtIn::GenerateCode(quint16* code, quint32 *para, quint8 other)
{
    code[0] = CODE_EXT_IN | (((quint16)m_flag) << 8);
    para[0] = (m_var1 & 0xFFF);
    para[0] |= m_type<<12;

    code[1] = CODE_CONST | (((quint16)m_flag) << 8);
    para[1] = m_counter;
    para[1] |= m_interval << 16;
    return true;
}

void CodeExtIn::UpdateBaseMember()
{
	QString para;
	if (m_interval)
	{
		para = QString(tr(" 每")) + QString(" %1 ").arg(m_interval+1) + QString(tr("周期执行一次"));
	}
    if (m_type==1)
        m_name = QString(tr("开始检测输入[")) + xStringResource::GetVarName(m_var1) + QString(("]")) + para;
    else if (m_type==3)
        m_name = QString(tr("开始检测输入(信号无效)[")) + xStringResource::GetVarName(m_var1) + QString(("]")) + para;
	else
        m_name = QString(tr("停止检测输入[")) + xStringResource::GetVarName(m_var1) + QString(("]")) + para;
}

bool CodeExtIn::IsModified()
{
	if (m_form)
	{
		if ((m_var1 != m_form->GetVar())||
            (m_type != m_form->GetType())||
            (m_counter != m_form->GetCounter())||
            (m_interval != m_form->GetInterval()))
			return true;
	}
	return XmlModelItem::IsModified();
}
void CodeExtIn::SetUserVar(quint16 var, int idx)
{
    m_counter = var;
}

quint16 CodeExtIn::GetUserVar(int idx)
{
    if ((m_counter &MASK_VAR_TYPE) == VAR_TYPE_USR)
        return m_counter;
    return 0;
}
