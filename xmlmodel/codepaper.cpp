#include "xconfig.h"
#include "formactpaper.h"
#include "codepaper.h"
#include "cmbprotocol.h"
#include "servoalias.h"


CodePaper::CodePaper(QWidget *form) : XmlModelItem(QIcon(":/img/action/Paper.png"), form, QString(tr("搜索指令")))
{
	m_form = (FormActPaper*)form;
    m_pos = 0;
	m_speed = 50;
	m_dspeed = 10;
	m_dvar = EM1_VAR_X02;
	m_invar = EM1_VAR_X02;
    m_code = CODE_PAPER;
    m_codes = 3;
    m_axes = 0;
    UpdateBaseMember();
}

CodePaper::~CodePaper()
{
}

bool CodePaper::XmlReadPara(QXmlStreamReader &reader)
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
        if (name==XML_PNAME_PARA1) m_axes = val.toInt();
        if (name==XML_PNAME_PARA2) m_pos = val.toInt();
        if (name==XML_PNAME_PARA3) m_speed = val.toInt();
        if (name==XML_PNAME_PARA4) m_dspeed = val.toInt();
        if (name==XML_PNAME_PARA5) m_dvar = val.toInt();
        if (name==XML_PNAME_PARA6) m_invar = val.toInt();
		UpdateBaseMember();
		if (reader.isEndElement())
			reader.readNext();    }
	else
		XmlSkipUnknownElement(reader);
	return true;
}
bool CodePaper::XmlRead(QXmlStreamReader &reader)
{
	QString type = reader.attributes().value(XML_ATTR_TYPE).toString();
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
bool CodePaper::XmlWrite(QXmlStreamWriter &writer)
{
	writer.writeStartElement(XML_ELEMENT_CODE);
	writer.writeAttribute(XML_ATTR_NAME, XML_CNAME_PAPER);
    writer.writeAttribute(XML_ATTR_NOTE, m_note);
    writer.writeAttribute(XML_ATTR_FLAG, QString("%1").arg(m_flag));


	writer.writeStartElement(XML_ELEMENT_PARA);
	writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA1);
    writer.writeCharacters(QString("%1").arg(m_axes));
	writer.writeEndElement();

	writer.writeStartElement(XML_ELEMENT_PARA);
	writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA2);
    writer.writeCharacters(QString("%1").arg(m_pos));
	writer.writeEndElement();

	writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA3);
    writer.writeCharacters(QString("%1").arg(m_speed));
	writer.writeEndElement();

	writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA4);
    writer.writeCharacters(QString("%1").arg(m_dspeed));
	writer.writeEndElement();

	writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA5);
    writer.writeCharacters(QString("%1").arg(m_dvar));
	writer.writeEndElement();

	writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA6);
    writer.writeCharacters(QString("%1").arg(m_invar));
	writer.writeEndElement();

	writer.writeEndElement();
	return true;
}
bool CodePaper::Update(bool bSaveAndValidate)
{
	if (m_form)
	{
		if (bSaveAndValidate)
		{
			bool change=false;
            if (m_axes != m_form->GetAxes())
			{
                m_axes = m_form->GetAxes();
				change=true;
			}
            if (m_pos != m_form->GetY())
			{
                m_pos = m_form->GetY();
				change=true;
			}
			if (m_speed != m_form->GetSpeed())
			{
				m_speed = m_form->GetSpeed();
				change=true;
			}
			if (m_dspeed != m_form->GetDSpeed())
			{
				m_dspeed = m_form->GetDSpeed();
				change=true;
			}
			if (m_dvar != m_form->GetDecVar())
			{
				m_dvar = m_form->GetDecVar();
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
            m_form->SetAxes(m_axes);
            m_form->SetY(m_pos);
			m_form->SetSpeed(m_speed);
			m_form->SetDSpeed(m_dspeed);
			m_form->SetDecVar(m_dvar);
			m_form->SetInVar(m_invar);
			m_form->UpdateWidgetState();
		}
	}
	return false;
}
void CodePaper::UpdateBaseMember()
{
    m_name = tr("搜索指令") + tr("[%1]").arg(GetServoName(m_axes));
}

bool CodePaper::GenerateCode(quint16* code, quint32 *para, quint8 other)
{
    quint32 relSpd = CMBProtocol::GetSrvSpeed();
    relSpd = qRound((double)(m_speed * relSpd) / 100.0);
    relSpd = (relSpd == 0 ? 1 : relSpd);

    quint32 decSpd = CMBProtocol::GetSrvSpeed();
    decSpd = qRound((double)(m_dspeed * decSpd) / 100.0);
    decSpd = (decSpd == 0 ? 1 : decSpd);

    code[0] = CODE_PAPER | (((quint16)m_flag) << 8);
    para[0] = (m_dvar&0xFFFF) | ((m_invar&0xFFFF)<<16);

    code[1] = CODE_CONST | (((quint16)m_flag) << 8);
    para[1] = m_pos;

    code[2] = CODE_CONST | (((quint16)m_flag) << 8);
    para[2] = (relSpd&0x7F) | ((decSpd&0x7F)<<8) | (((int)m_axes)<< 16);
    return true;
}

bool CodePaper::IsModified()
{
	if (m_form)
	{
        if ((m_axes != m_form->GetAxes())||
            (m_pos != m_form->GetY())||
			(m_speed != m_form->GetSpeed())||
			(m_dspeed != m_form->GetDSpeed())||
			(m_dvar != m_form->GetDecVar())||
            (m_invar != m_form->GetInVar()))
			return true;
	}
	return XmlModelItem::IsModified();
}
