#include "xconfig.h"
#include "formvactvacuum.h"
#include "vcodevacuum.h"
#include "xstringresource.h"

VCodeVacuum::VCodeVacuum(QWidget *form) :	XmlModelItem(QIcon(":/img/action/Fixture.png"), form)
{
    m_form = (FormVActVacuum*)form;
	m_type = 0;
	m_delay = 5;
	m_outvar = EM1_VAR_Y02;
	m_invar = EM1_VAR_X02;
	m_interval = 0;
    m_extout_counter = 0;
    m_extin_counter = 0;
    m_code = VCODE_VACUUM;
    m_codes = 4;

    UpdateBaseMember();
}
bool VCodeVacuum::XmlReadPara(QXmlStreamReader &reader)
{
	QString name = reader.attributes().value(XML_ATTR_NAME).toString();
	if ((name==XML_PNAME_PARA1)||
        (name==XML_PNAME_PARA2)||
        (name==XML_PNAME_PARA3)||
        (name==XML_PNAME_PARA4)||
        (name==XML_PNAME_PARA5)||
        (name==XML_PNAME_PARA6))
	{
		QString val = reader.readElementText();
        if (name==XML_PNAME_PARA1) m_outvar = val.toInt();
		if (name==XML_PNAME_PARA2) m_delay = val.toInt();
        if (name==XML_PNAME_PARA3) m_interval = val.toInt();
        if (name==XML_PNAME_PARA4) m_invar = val.toInt();
        if (name==XML_PNAME_PARA5) m_extin_counter = val.toInt();
        if (name==XML_PNAME_PARA6) m_extout_counter = val.toInt();
        UpdateBaseMember();
		if (reader.isEndElement())
			reader.readNext();
	}
	else
		XmlSkipUnknownElement(reader);
	return true;
}
bool VCodeVacuum::XmlRead(QXmlStreamReader &reader)
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
bool VCodeVacuum::XmlWrite(QXmlStreamWriter &writer)
{
	writer.writeStartElement(XML_ELEMENT_CODE);
    writer.writeAttribute(XML_ATTR_NAME, XML_CNAME_VACUUM);
	if (m_type==1)
		writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_ON);
	else
		writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_OFF);
    writer.writeAttribute(XML_ATTR_NOTE, m_note);
    writer.writeAttribute(XML_ATTR_FLAG, QString("%1").arg(m_flag));


		writer.writeStartElement(XML_ELEMENT_PARA);
		writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA1);
            writer.writeCharacters(QString("%1").arg(m_outvar));
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
            writer.writeCharacters(QString("%1").arg(m_invar));
        writer.writeEndElement();

        writer.writeStartElement(XML_ELEMENT_PARA);
        writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA5);
            writer.writeCharacters(QString("%1").arg(m_extin_counter));
        writer.writeEndElement();

        writer.writeStartElement(XML_ELEMENT_PARA);
        writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA6);
            writer.writeCharacters(QString("%1").arg(m_extout_counter));
        writer.writeEndElement();

    writer.writeEndElement();
	return true;
}
bool VCodeVacuum::Update(bool bSaveAndValidate)
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
            if (m_outvar != m_form->GetVar())
			{
                m_outvar = m_form->GetVar();
				change=true;
			}
            if (m_invar != m_form->GetInVar())
            {
                m_invar = m_form->GetInVar();
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
            m_form->SetVar(m_outvar);
            m_form->SetInVar(m_invar);
            m_form->UpdateWidgetState();
		}
	}
	return false;
}

bool VCodeVacuum::GenerateCode(quint16* code, quint32 *para, quint8 other)
{
    if (m_type==1)//治具开启
	{
        code[0] = CODE_EXT_OUT | (((quint16)m_flag) << 8);
        para[0] = (m_outvar & 0xFFF);
        para[0] |= m_type<<12;
        para[0] |= m_delay<<16;

        code[1] = CODE_CONST | (((quint16)m_flag) << 8);
        para[1] = m_extout_counter;
        para[1] |= m_interval << 16;
    //////////////////////////////////////////////
        code[2] = CODE_EXT_IN | (((quint16)m_flag) << 8);
        para[2] = (m_invar & 0xFFF);
        para[2] |= m_type<<12;

        code[3] = CODE_CONST | (((quint16)m_flag) << 8);
        para[3] = m_extin_counter;
        para[3] |= m_interval << 16;
    }
	else
	{
        code[0] = CODE_EXT_IN | (((quint16)m_flag) << 8);
        para[0] = (m_invar & 0xFFF);
        para[0] |= m_type<<12;

        code[1] = CODE_CONST | (((quint16)m_flag) << 8);
        para[1] = m_extin_counter;
        para[1] |= m_interval << 16;
    //////////////////////////////////////////////
        code[2] = CODE_EXT_OUT | (((quint16)m_flag) << 8);
        para[2] = (m_outvar & 0xFFF);
        para[2] |= m_type<<12;
        para[2] |= m_delay<<16;

        code[3] = CODE_CONST | (((quint16)m_flag) << 8);
        para[3] = m_extout_counter;
        para[3] |= m_interval << 16;
    }
    return true;
}

void VCodeVacuum::UpdateBaseMember()
{
    QString para;
	if (m_type==1)
        m_name = tr("开启[") + xStringResource::GetVarName(m_outvar) + tr("]_开始检测[") + xStringResource::GetVarName(m_invar) + tr("] 时间") + tr(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + tr("秒") + para;
	else
        m_name = tr("关闭[") + xStringResource::GetVarName(m_outvar) + tr("]_停止检测[") + xStringResource::GetVarName(m_invar) + tr("] 时间") + tr(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + tr("秒") + para;
}

bool VCodeVacuum::IsModified()
{
	if (m_form)
	{
        if ((m_outvar != m_form->GetVar())||
            (m_invar != m_form->GetInVar())||
            (m_type != m_form->GetType())||
            (m_delay != m_form->GetDelay())||
			(m_interval != m_form->GetInterval()))
			return true;
	}
	return XmlModelItem::IsModified();
}

void VCodeVacuum::SetUserVar(quint16 var, int idx)
{
    if (idx == 1)
        m_extout_counter = var;
    else
        m_extin_counter = var;
}

quint16 VCodeVacuum::GetUserVar(int idx)
{
    if (idx == 1)
    {
        if ((m_extout_counter &MASK_VAR_TYPE) == VAR_TYPE_USR)
            return m_extout_counter;
        return 0;
    }
    else
    {
        if ((m_extin_counter &MASK_VAR_TYPE) == VAR_TYPE_USR)
            return m_extin_counter;
        return 0;
    }
}

