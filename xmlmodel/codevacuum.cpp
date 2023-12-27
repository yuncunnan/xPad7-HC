#include "xconfig.h"
#include "formactvacuum.h"
#include "codevacuum.h"
#include "xstringresource.h"

CodeVacuum::CodeVacuum(QWidget *form) :	XmlModelItem(QIcon(":/img/action/Fixture.png"), form)
{
    m_form = (FormActVacuum*)form;
	m_type = 0;
	m_delay = 5;
    m_outbmp = 0;
    m_inbmp = 0;
	m_interval = 0;
    m_counter = 0;
    m_code = CODE_VACUUM;
    m_codes = 3;

    UpdateBaseMember();
}
bool CodeVacuum::XmlReadPara(QXmlStreamReader &reader)
{
	QString name = reader.attributes().value(XML_ATTR_NAME).toString();
	if ((name==XML_PNAME_PARA1)||
        (name==XML_PNAME_PARA2)||
        (name==XML_PNAME_PARA3)||
        (name==XML_PNAME_PARA4)||
        (name==XML_PNAME_PARA5))
	{
		QString val = reader.readElementText();
        if (name==XML_PNAME_PARA1) m_outbmp = val.toInt();
		if (name==XML_PNAME_PARA2) m_delay = val.toInt();
        if (name==XML_PNAME_PARA3) m_interval = val.toInt();
        if (name==XML_PNAME_PARA4) m_inbmp = val.toInt();
        if (name==XML_PNAME_PARA5) m_counter = val.toInt();
        UpdateBaseMember();
		if (reader.isEndElement())
			reader.readNext();
	}
	else
		XmlSkipUnknownElement(reader);
	return true;
}
bool CodeVacuum::XmlRead(QXmlStreamReader &reader)
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
bool CodeVacuum::XmlWrite(QXmlStreamWriter &writer)
{
	writer.writeStartElement(XML_ELEMENT_CODE);
    writer.writeAttribute(XML_ATTR_NAME, XML_CNAME_INVACUUM);
	if (m_type==1)
		writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_ON);
	else
		writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_OFF);
    writer.writeAttribute(XML_ATTR_NOTE, m_note);
    writer.writeAttribute(XML_ATTR_FLAG, QString("%1").arg(m_flag));


		writer.writeStartElement(XML_ELEMENT_PARA);
		writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA1);
            writer.writeCharacters(QString("%1").arg(m_outbmp));
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
            writer.writeCharacters(QString("%1").arg(m_inbmp));
        writer.writeEndElement();

        writer.writeStartElement(XML_ELEMENT_PARA);
        writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA5);
            writer.writeCharacters(QString("%1").arg(m_counter));
        writer.writeEndElement();

    writer.writeEndElement();
	return true;
}
bool CodeVacuum::Update(bool bSaveAndValidate)
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
            if (m_outbmp != m_form->GetOutBmp())
			{
                m_outbmp = m_form->GetOutBmp();
				change=true;
			}
            if (m_inbmp != m_form->GetInBmp())
            {
                m_inbmp = m_form->GetInBmp();
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
            m_form->SetOutBmp(m_outbmp);
            m_form->SetInBmp(m_inbmp);
            m_form->UpdateWidgetState();
		}
	}
	return false;
}

bool CodeVacuum::GenerateCode(quint16* code, quint32 *para, quint8 other)
{
    code[0] = CODE_VACUUM | (((quint16)m_flag) << 8);
    para[0] = m_outbmp;
    para[0] |= m_inbmp<<16;

    code[1] = CODE_CONST | (((quint16)m_flag) << 8);
    para[1] = m_delay;
    para[1] |= m_type << 16;

    code[2] = CODE_CONST | (((quint16)m_flag) << 8);
    para[2] = m_counter;
    para[2] |= m_interval << 16;

    return true;
}

void CodeVacuum::UpdateBaseMember()
{

    QString para;
    QString strvacuum;
    if(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_5AXIS)
    {
        if ((m_outbmp>>0)&1)
			strvacuum = xStringResource::GetVarName(MAIN_VAR_Y11);
        else
            strvacuum = ("");
        if ((m_outbmp>>1)&1)
			strvacuum += xStringResource::GetVarName(MAIN_VAR_Y12);
        if ((m_outbmp>>2)&1)
			strvacuum += xStringResource::GetVarName(MAIN_VAR_Y13);
        if ((m_outbmp>>3)&1)
			strvacuum += xStringResource::GetVarName(MAIN_VAR_Y14);
        if ((m_outbmp>>4)&1)
			strvacuum += xStringResource::GetVarName(MAIN_VAR_Y15);
        if ((m_outbmp>>5)&1)
			strvacuum += xStringResource::GetVarName(MAIN_VAR_Y16);
        if ((m_outbmp>>6)&1)
			strvacuum += xStringResource::GetVarName(MAIN_VAR_Y17);
        if ((m_outbmp>>7)&1)
			strvacuum += xStringResource::GetVarName(MAIN_VAR_Y18);
        if ((m_outbmp>>8)&1)
			strvacuum += xStringResource::GetVarName(MAIN_VAR_Y19);
        if ((m_outbmp>>9)&1)
			strvacuum += xStringResource::GetVarName(MAIN_VAR_Y20);
        if ((m_outbmp>>10)&1)
			strvacuum += xStringResource::GetVarName(MAIN_VAR_Y21);
        if ((m_outbmp>>11)&1)
			strvacuum += xStringResource::GetVarName(MAIN_VAR_Y22);
        if ((m_outbmp>>12)&1)
			strvacuum += xStringResource::GetVarName(MAIN_VAR_Y23);
        if ((m_outbmp>>13)&1)
			strvacuum += xStringResource::GetVarName(MAIN_VAR_Y24);
    }
    else if(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_DVS)
    {

        if ((m_outbmp>>0)&1)
            strvacuum = xStringResource::GetVarName(MAIN_VAR_Y08).right(3);
        else
            strvacuum = ("");
        if ((m_outbmp>>1)&1)
            strvacuum += xStringResource::GetVarName(MAIN_VAR_Y09).right(3);
        if ((m_outbmp>>2)&1)
            strvacuum += xStringResource::GetVarName(MAIN_VAR_Y10).right(3);
        if ((m_outbmp>>3)&1)
            strvacuum += xStringResource::GetVarName(MAIN_VAR_Y11).right(3);
        if ((m_outbmp>>4)&1)
            strvacuum += xStringResource::GetVarName(MAIN_VAR_Y12).right(3);
        if ((m_outbmp>>5)&1)
            strvacuum += xStringResource::GetVarName(MAIN_VAR_Y13).right(3);
        if ((m_outbmp>>6)&1)
            strvacuum += xStringResource::GetVarName(MAIN_VAR_Y14).right(3);
        if ((m_outbmp>>7)&1)
            strvacuum += xStringResource::GetVarName(MAIN_VAR_Y15).right(3);
        if ((m_outbmp>>8)&1)
            strvacuum += xStringResource::GetVarName(MAIN_VAR_Y16).right(3);
        if ((m_outbmp>>9)&1)
            strvacuum += xStringResource::GetVarName(MAIN_VAR_Y17).right(3);
        if ((m_outbmp>>10)&1)
            strvacuum += xStringResource::GetVarName(MAIN_VAR_Y18).right(3);
        if ((m_outbmp>>11)&1)
            strvacuum += xStringResource::GetVarName(MAIN_VAR_Y19).right(3);
        if ((m_outbmp>>12)&1)
            strvacuum += xStringResource::GetVarName(MAIN_VAR_Y20).right(3);
        if ((m_outbmp>>13)&1)
            strvacuum += xStringResource::GetVarName(MAIN_VAR_Y22).right(3);
    }
    else if(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_ECAT_CANOPEN)
    {

        if ((m_outbmp>>0)&1)
            strvacuum = xStringResource::GetVarName(MAIN_VAR_Y16).right(3);
        else
            strvacuum = ("");
        if ((m_outbmp>>1)&1)
            strvacuum += xStringResource::GetVarName(MAIN_VAR_Y17).right(3);
        if ((m_outbmp>>2)&1)
            strvacuum += xStringResource::GetVarName(MAIN_VAR_Y18).right(3);
        if ((m_outbmp>>3)&1)
            strvacuum += xStringResource::GetVarName(MAIN_VAR_Y19).right(3);
        if ((m_outbmp>>4)&1)
            strvacuum += xStringResource::GetVarName(MAIN_VAR_Y20).right(3);
        if ((m_outbmp>>5)&1)
            strvacuum += xStringResource::GetVarName(MAIN_VAR_Y21).right(3);
        if ((m_outbmp>>6)&1)
            strvacuum += xStringResource::GetVarName(MAIN_VAR_Y22).right(3);
        if ((m_outbmp>>7)&1)
            strvacuum += xStringResource::GetVarName(MAIN_VAR_Y23).right(3);
        if ((m_outbmp>>8)&1)
            strvacuum += xStringResource::GetVarName(MAIN_VAR_Y24).right(3);
        if ((m_outbmp>>9)&1)
            strvacuum += xStringResource::GetVarName(MAIN_VAR_Y25).right(3);
        if ((m_outbmp>>10)&1)
            strvacuum += xStringResource::GetVarName(MAIN_VAR_Y26).right(3);
        if ((m_outbmp>>11)&1)
            strvacuum += xStringResource::GetVarName(MAIN_VAR_Y27).right(3);
        if ((m_outbmp>>12)&1)
            strvacuum += xStringResource::GetVarName(MAIN_VAR_Y28).right(3);
        if ((m_outbmp>>13)&1)
            strvacuum += xStringResource::GetVarName(MAIN_VAR_Y29).right(3);
    }
    else
    {
        if (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)
        {
            if ((m_outbmp>>0)&1)
                strvacuum = xStringResource::GetVarName(MAIN_VAR_Y00).right(3);
            else
                strvacuum = ("");
            if ((m_outbmp>>1)&1)
                strvacuum += xStringResource::GetVarName(MAIN_VAR_Y01).right(3);
            if ((m_outbmp>>2)&1)
                strvacuum += xStringResource::GetVarName(MAIN_VAR_Y02).right(3);
            if ((m_outbmp>>3)&1)
                strvacuum += xStringResource::GetVarName(MAIN_VAR_Y03).right(3);
            if ((m_outbmp>>4)&1)
                strvacuum += xStringResource::GetVarName(MAIN_VAR_Y04).right(3);
            if ((m_outbmp>>5)&1)
                strvacuum += xStringResource::GetVarName(MAIN_VAR_Y05).right(3);
            if ((m_outbmp>>6)&1)
                strvacuum += xStringResource::GetVarName(MAIN_VAR_Y06).right(3);
            if ((m_outbmp>>7)&1)
                strvacuum += xStringResource::GetVarName(MAIN_VAR_Y07).right(3);
            if ((m_outbmp>>8)&1)
                strvacuum += xStringResource::GetVarName(MAIN_VAR_Y08).right(3);
            if ((m_outbmp>>9)&1)
                strvacuum += xStringResource::GetVarName(MAIN_VAR_Y09).right(3);
            if ((m_outbmp>>10)&1)
                strvacuum += xStringResource::GetVarName(MAIN_VAR_Y10).right(3);
            if ((m_outbmp>>11)&1)
                strvacuum += xStringResource::GetVarName(MAIN_VAR_Y11).right(3);
            if ((m_outbmp>>12)&1)
                strvacuum += xStringResource::GetVarName(MAIN_VAR_Y12).right(3);
            if ((m_outbmp>>13)&1)
                strvacuum += xStringResource::GetVarName(MAIN_VAR_Y13).right(3);
            if ((m_outbmp>>14)&1)
                strvacuum += xStringResource::GetVarName(MAIN_VAR_Y14).right(3);
            if ((m_outbmp>>15)&1)
                strvacuum += xStringResource::GetVarName(MAIN_VAR_Y15).right(3);
        }
        else
        {
            if ((m_outbmp>>0)&1)
                strvacuum = xStringResource::GetVarName(EM1_VAR_Y02).right(3);
            else
                strvacuum = ("");
            if ((m_outbmp>>1)&1)
                strvacuum += xStringResource::GetVarName(EM1_VAR_Y03).right(3);
            if ((m_outbmp>>2)&1)
                strvacuum += xStringResource::GetVarName(EM1_VAR_Y04).right(3);
            if ((m_outbmp>>3)&1)
                strvacuum += xStringResource::GetVarName(EM1_VAR_Y05).right(3);
            if ((m_outbmp>>4)&1)
                strvacuum += xStringResource::GetVarName(EM1_VAR_Y06).right(3);
            if ((m_outbmp>>5)&1)
                strvacuum += xStringResource::GetVarName(EM1_VAR_Y07).right(3);
            if ((m_outbmp>>6)&1)
                strvacuum += xStringResource::GetVarName(EM1_VAR_Y08).right(3);
            if ((m_outbmp>>7)&1)
                strvacuum += xStringResource::GetVarName(EM1_VAR_Y09).right(3);
            if ((m_outbmp>>8)&1)
                strvacuum += xStringResource::GetVarName(EM1_VAR_Y10).right(3);
            if ((m_outbmp>>9)&1)
                strvacuum += xStringResource::GetVarName(EM1_VAR_Y11).right(3);
            if ((m_outbmp>>10)&1)
                strvacuum += xStringResource::GetVarName(EM1_VAR_Y12).right(3);
            if ((m_outbmp>>11)&1)
                strvacuum += xStringResource::GetVarName(EM1_VAR_Y13).right(3);
            if ((m_outbmp>>12)&1)
                strvacuum += xStringResource::GetVarName(EM1_VAR_Y14).right(3);
            if ((m_outbmp>>13)&1)
                strvacuum += xStringResource::GetVarName(EM1_VAR_Y15).right(3);
        }

    }

    if (strvacuum == (""))
        strvacuum = tr("未勾选治具动作");
    if (m_type==1)
        m_name = tr("开启[") + strvacuum + tr("] 时间") + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + tr("秒") + para;
    else
        m_name = tr("关闭[") + strvacuum + tr("] 时间") + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + tr("秒") + para;
//#endif
}

bool CodeVacuum::IsModified()
{
	if (m_form)
	{
        if ((m_outbmp != m_form->GetOutBmp())||
            (m_inbmp != m_form->GetInBmp())||
            (m_type != m_form->GetType())||
            (m_delay != m_form->GetDelay())||
			(m_interval != m_form->GetInterval()))
			return true;
	}
	return XmlModelItem::IsModified();
}

void CodeVacuum::SetUserVar(quint16 var, int idx)
{
    m_counter = var;
}

quint16 CodeVacuum::GetUserVar(int idx)
{
    if ((m_counter &MASK_VAR_TYPE) == VAR_TYPE_USR)
        return m_counter;
        return 0;
}

