#include "xconfig.h"
#include "formactsingleloopfree.h"
#include "codesingleloopfree.h"
#include "xstringresource.h"
#include "servoalias.h"
#include <QDebug>

CodeSingleLoopFree::CodeSingleLoopFree(QWidget *form) :	XmlModelItem(QIcon(":/img/action/Loop.png"), form, QString(tr("单轴循环自由定位")))
{
    m_form = (FormActSingleLoopFree*)form;
	m_speed = 50;
	m_poscount = 0;
    m_counter = 0;
    m_axes = 0;
    m_times = 0;
    m_code = CODE_LOOPFREE;
    m_dspeed = 10;
    m_dlen = 0;
    for (int i = 0; i < MAX_SINGLELOOPFREE_POINTS; i ++)
    {
        m_pos[i] = 0;
    }
    UpdateBaseMember();
}
CodeSingleLoopFree::~CodeSingleLoopFree()
{
}

bool CodeSingleLoopFree::XmlReadPara(QXmlStreamReader &reader)
{
	QString name = reader.attributes().value(XML_ATTR_NAME).toString();
	if ((name==XML_PNAME_PARA1)||
		(name==XML_PNAME_PARA2)||
		(name==XML_PNAME_PARA3)||
        (name==XML_PNAME_PARA4)||
        (name==XML_PNAME_PARA5)||
        (name==XML_PNAME_PARA6)||
        (name==XML_PNAME_PARA7))
	{
		QString val = reader.readElementText();
		if (name==XML_PNAME_PARA1) m_speed = val.toInt();
        if (name==XML_PNAME_PARA2) m_poscount = val.toInt();
        if (name==XML_PNAME_PARA3) m_counter = val.toInt();
        if (name==XML_PNAME_PARA4) m_axes = val.toInt();
        if (name==XML_PNAME_PARA5) m_times = val.toInt();
        if (name==XML_PNAME_PARA6) m_dspeed = val.toInt();
        if (name==XML_PNAME_PARA7) m_dlen = val.toInt();
        UpdateBaseMember();
		if (reader.isEndElement())
			reader.readNext();
	}
    else
    if (name==XML_PNAME_PARA8)
    {
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
                if (reader.name()==XML_ELEMENT_VALUE)
                {
                    QString strpos = reader.attributes().value(XML_ATTR_POS).toString();
                    QString val = reader.readElementText();
                    int idx = val.toInt();
                    if (idx<=MAX_SINGLELOOPFREE_POINTS)
                    {
                        m_poscount = idx;
                        m_pos[idx-1] = strpos.toInt();
                        UpdateBaseMember();
                    }
                    if (reader.isEndElement())
                        reader.readNext();
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
    }
    else
		XmlSkipUnknownElement(reader);
	return true;
}
bool CodeSingleLoopFree::XmlRead(QXmlStreamReader &reader)
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
bool CodeSingleLoopFree::XmlWrite(QXmlStreamWriter &writer)
{
    int i;
	writer.writeStartElement(XML_ELEMENT_CODE);
    writer.writeAttribute(XML_ATTR_NAME, XML_CNAME_SINGLE_LOOP_FREE);
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
    writer.writeCharacters(QString("%1").arg(m_dspeed));
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA7);
    writer.writeCharacters(QString("%1").arg(m_dlen));
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA8);
    for (i=0; i<m_poscount; i++)
    {
        writer.writeStartElement(XML_ELEMENT_VALUE);
        writer.writeAttribute(XML_ATTR_POS, QString("%1").arg(m_pos[i]));
            writer.writeCharacters(QString("%1").arg(i+1));
        writer.writeEndElement();
    }
    writer.writeEndElement();

    writer.writeEndElement();
	return true;
}
void CodeSingleLoopFree::UpdateBaseMember()
{
    m_name = tr("单轴循环自由定位") + tr("[%1] [%2]点 速度 %3").arg(GetServoName(m_axes)).arg(m_poscount).arg(m_speed);
    m_codes = 3 + m_poscount;
}
bool CodeSingleLoopFree::Update(bool bSaveAndValidate)
{
	if (m_form)
	{
		if (bSaveAndValidate)
		{
			bool change=false;
            int i;
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
            for (i=0; i<m_poscount; i++)
            {
                if (m_pos[i] != m_form->GetPos(i))
                {
                    m_pos[i] = m_form->GetPos(i);
                    change=true;
                }
            }
            if (change) UpdateBaseMember();
			return change;
		}
		else
		{
            int i;
            for (i=0; i<m_poscount; i++)
            {
                m_form->SetPos(i, m_pos[i]);
            }
            m_form->SetPosCount(m_poscount);
			m_form->SetSpeed(m_speed);
            m_form->SetAxes(m_axes);
            m_form->SetTimes(m_times);
            m_form->SetVar(m_counter);
            m_form->SetDSpeed(m_dspeed);
            m_form->SetDLen(m_dlen);
			m_form->UpdateWidgetState();
        }
	}
	return false;
}

bool CodeSingleLoopFree::GenerateCode(quint16* code, quint32 *para, quint8 other)
{
    int idx = 0;
    quint32 relSpd = CMBProtocol::GetSrvSpeed();
    relSpd = qRound((double)(m_speed * relSpd) / 100.0);
    relSpd = (relSpd == 0 ? 1 : relSpd);

    code[0] = CODE_LOOPFREE | (((quint16)m_flag) << 8);
    para[0] = relSpd;
    para[0] |= m_axes << 8;
    para[0] |= m_counter << 16;

    code[1] = CODE_CONST | (((quint16)m_flag) << 8);
    para[1] = m_poscount;

    code[2] = CODE_CONST | (((quint16)m_flag) << 8);
    para[2] = m_dspeed;
    para[2] |= m_times<<8;
    para[2] |= m_dlen<<16;

    idx = 3;
    for (int i =0; i < m_poscount; i++)
    {
        code[idx] = CODE_CONST | (((quint16)m_flag) << 8);
        para[idx] = m_pos[i];
        idx++;
    }

    return true;
}

bool CodeSingleLoopFree::IsModified()
{
    int i;
	if (m_form)
	{
		if ((m_speed != m_form->GetSpeed())||
            (m_times != m_form->GetTimes())||
            (m_axes != m_form->GetAxes())||
            (m_poscount != (m_form->GetPosCount()))||
            (m_dspeed != (m_form->GetDSpeed()))||
            (m_dlen != (m_form->GetDLen()))||
            (m_counter != m_form->GetVar()))
			 return true;
        for (i=0; i<m_poscount; i++)
        {
            if (m_pos[i]!=m_form->GetPos(i))
                return true;
        }
    }
	return XmlModelItem::IsModified();
}

void CodeSingleLoopFree::SetUserVar(quint16 var, int idx)
{
    m_counter = var;
}

quint16 CodeSingleLoopFree::GetUserVar(int idx)
{
    if ((m_counter &MASK_VAR_TYPE) == VAR_TYPE_USR)
        return m_counter;
    return 0;
}
