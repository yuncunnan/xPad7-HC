#include "xconfig.h"
#include "formactsingleloop.h"
#include "codesingleloop.h"
#include "xstringresource.h"
#include "servoalias.h"

CodeSingleLoop::CodeSingleLoop(QWidget *form) :	XmlModelItem(QIcon(":/img/action/Loop.png"), form, QString(tr("单轴循环定位")))
{
    m_form = (FormActSingleLoop*)form;
	m_speed = 50;
	m_poscount = 0;
    m_counter = 0;
    m_axes = 0;
    m_times = 0;
    m_interval = 0;
    m_pos = 0;
    m_code = CODE_LOOP;
    m_codes = 4;
    m_dspeed = 10;
    m_dlen = 0;
}
CodeSingleLoop::~CodeSingleLoop()
{
}

bool CodeSingleLoop::XmlReadPara(QXmlStreamReader &reader)
{
	QString name = reader.attributes().value(XML_ATTR_NAME).toString();
	if ((name==XML_PNAME_PARA1)||
		(name==XML_PNAME_PARA2)||
		(name==XML_PNAME_PARA3)||
        (name==XML_PNAME_PARA4)||
        (name==XML_PNAME_PARA5)||
        (name==XML_PNAME_PARA6)||
        (name==XML_PNAME_PARA7)||
        (name==XML_PNAME_PARA8)||
        (name==XML_PNAME_PARA9))
	{
		QString val = reader.readElementText();
		if (name==XML_PNAME_PARA1) m_speed = val.toInt();
        if (name==XML_PNAME_PARA2) m_poscount = val.toInt();
        if (name==XML_PNAME_PARA3) m_counter = val.toInt();
        if (name==XML_PNAME_PARA4) m_axes = val.toInt();
        if (name==XML_PNAME_PARA5) m_times = val.toInt();
        if (name==XML_PNAME_PARA6) m_interval = val.toInt();
        if (name==XML_PNAME_PARA7) m_pos = val.toInt();
        if (name==XML_PNAME_PARA8) m_dspeed = val.toInt();
        if (name==XML_PNAME_PARA9) m_dlen = val.toInt();
        UpdateBaseMember();
		if (reader.isEndElement())
			reader.readNext();
	}
	else
		XmlSkipUnknownElement(reader);
	return true;
}
bool CodeSingleLoop::XmlRead(QXmlStreamReader &reader)
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
bool CodeSingleLoop::XmlWrite(QXmlStreamWriter &writer)
{
	writer.writeStartElement(XML_ELEMENT_CODE);
    writer.writeAttribute(XML_ATTR_NAME, XML_CNAME_SINGLE_LOOP);
    writer.writeAttribute(XML_ATTR_NOTE, m_note);
    writer.writeAttribute(XML_ATTR_FLAG, QString("%1").arg(m_flag));


	writer.writeStartElement(XML_ELEMENT_PARA);
	writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA1);
    writer.writeCharacters(QString("%1").arg(m_speed));
	writer.writeEndElement();

	writer.writeStartElement(XML_ELEMENT_PARA);
	writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA2);
    writer.writeCharacters(QString("%1").arg(m_poscount));
	writer.writeEndElement();

	writer.writeStartElement(XML_ELEMENT_PARA);
	writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA3);
    writer.writeCharacters(QString("%1").arg(m_counter));
	writer.writeEndElement();

	writer.writeStartElement(XML_ELEMENT_PARA);
	writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA4);
    writer.writeCharacters(QString("%1").arg(m_axes));
	writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA5);
    writer.writeCharacters(QString("%1").arg(m_times));
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA6);
    writer.writeCharacters(QString("%1").arg(m_interval));
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA7);
    writer.writeCharacters(QString("%1").arg(m_pos));
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA8);
    writer.writeCharacters(QString("%1").arg(m_dspeed));
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA9);
    writer.writeCharacters(QString("%1").arg(m_dlen));
    writer.writeEndElement();

	writer.writeEndElement();
	return true;
}
void CodeSingleLoop::UpdateBaseMember()
{
    m_name = tr("单轴循环定位") + tr("[%1] [%2]点 速度 %3").arg(GetServoName(m_axes)).arg(m_poscount).arg(m_speed);
}
bool CodeSingleLoop::Update(bool bSaveAndValidate)
{
	if (m_form)
	{
		if (bSaveAndValidate)
		{
			bool change=false;
			if (m_speed != m_form->GetSpeed())
			{
				m_speed = m_form->GetSpeed();
				change=true;
			}
            if (m_counter != m_form->GetVar())
            {
                m_counter = m_form->GetVar();
                change=true;
            }
            if (m_axes != m_form->GetAxes())
			{
                m_axes = m_form->GetAxes();
				change=true;
			}
            if (m_poscount != m_form->GetPosCount())
			{
                m_poscount = m_form->GetPosCount();
				change=true;
			}
            if (m_times != m_form->GetTimes())
			{
                m_times = m_form->GetTimes();
				change=true;
			}
            if (m_interval != m_form->GetInterval())
            {
                m_interval = m_form->GetInterval();
                change=true;
            }
            if (m_pos != m_form->GetFirstPos())
            {
                m_pos = m_form->GetFirstPos();
                change=true;
            }
            if (m_dspeed != m_form->GetDSpeed())
            {
                m_dspeed = m_form->GetDSpeed();
                change=true;
            }
            if (m_dlen != m_form->GetDLen())
            {
                m_dlen = m_form->GetDLen();
                change=true;
            }
            if (change) UpdateBaseMember();
			return change;
		}
		else
		{
            m_form->SetPosCount(m_poscount);
			m_form->SetSpeed(m_speed);
            m_form->SetAxes(m_axes);
            m_form->SetInterval(m_interval);
            m_form->SetTimes(m_times);
            m_form->SetFirstPos(m_pos);
            m_form->SetVar(m_counter);
            m_form->SetDSpeed(m_dspeed);
            m_form->SetDLen(m_dlen);
			m_form->UpdateWidgetState();
		}
	}
	return false;
}

bool CodeSingleLoop::GenerateCode(quint16* code, quint32 *para, quint8 other)
{
    quint32 relSpd = CMBProtocol::GetSrvSpeed();
    relSpd = qRound((double)(m_speed * relSpd) / 100.0);
    relSpd = (relSpd == 0 ? 1 : relSpd);

    code[0] = CODE_LOOP | (((quint16)m_flag) << 8);
    para[0] = relSpd;
    para[0] |= m_axes << 8;
    para[0] |= m_counter << 16;

    code[1] = CODE_CONST | (((quint16)m_flag) << 8);
    para[1] = m_poscount;
    para[1] |= m_interval << 16;

    code[2] = CODE_CONST | (((quint16)m_flag) << 8);
    para[2] = m_pos;

    code[3] = CODE_CONST | (((quint16)m_flag) << 8);
    para[3] = m_dspeed;
    para[3] |= m_times<<8;
    para[3] |= m_dlen<<16;

    return true;
}

bool CodeSingleLoop::IsModified()
{
	if (m_form)
	{
		if ((m_speed != m_form->GetSpeed())||
            (m_times != m_form->GetTimes())||
            (m_interval != m_form->GetInterval())||
            (m_pos != m_form->GetFirstPos())||
            (m_axes != m_form->GetAxes())||
            (m_poscount != (m_form->GetPosCount()))||
            (m_dspeed != (m_form->GetDSpeed()))||
            (m_dlen != (m_form->GetDLen()))||
            (m_counter != m_form->GetVar()))
			 return true;
	}
	return XmlModelItem::IsModified();
}

void CodeSingleLoop::SetUserVar(quint16 var, int idx)
{
    m_counter = var;
}

quint16 CodeSingleLoop::GetUserVar(int idx)
{
    if ((m_counter &MASK_VAR_TYPE) == VAR_TYPE_USR)
        return m_counter;
    return 0;
}
