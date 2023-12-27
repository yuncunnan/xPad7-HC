#include "xconfig.h"
#include "formactvision.h"
#include "codevision.h"
#include "xstringresource.h"

CodeVision::CodeVision(QWidget *form) :	XmlModelItem(QIcon(":/img/action/Wait.png"), form)
{
    m_code = CODE_VISION;
    m_form = (FormActVision*)form;
    m_timeout = 50;
    m_codes = 7;
    m_matchbmp = 7;
    m_vision = 0;
    m_uservar[0][0] = 0;
    m_uservar[0][1] = 0;
    m_uservar[0][2] = 0;
    m_uservar[0][3] = 0;
    m_uservar[1][0] = 0;
    m_uservar[1][1] = 0;
    m_uservar[1][2] = 0;
    m_uservar[1][3] = 0;
    m_uservar[2][0] = 0;
    m_uservar[2][1] = 0;
    m_uservar[2][2] = 0;
    m_uservar[2][3] = 0;
    UpdateBaseMember();
}
bool CodeVision::XmlReadPara(QXmlStreamReader &reader)
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
        (name==XML_PNAME_PARA9)||
        (name==XML_PNAME_PARA10)||
        (name==XML_PNAME_PARA11)||
        (name==XML_PNAME_PARA12)||
        (name==XML_PNAME_PARA13)||
        (name==XML_PNAME_PARA14)||
        (name==XML_PNAME_PARA15))
	{
		QString val = reader.readElementText();
        if (name==XML_PNAME_PARA1) m_vision = val.toInt();
        if (name==XML_PNAME_PARA2) m_timeout = val.toInt();
        if (name==XML_PNAME_PARA3) m_matchbmp = val.toInt();
        if (name==XML_PNAME_PARA4) m_uservar[0][0] = val.toInt();
        if (name==XML_PNAME_PARA5) m_uservar[0][1] = val.toInt();
        if (name==XML_PNAME_PARA6) m_uservar[0][2] = val.toInt();
        if (name==XML_PNAME_PARA7) m_uservar[0][3] = val.toInt();
        if (name==XML_PNAME_PARA8) m_uservar[1][0] = val.toInt();
        if (name==XML_PNAME_PARA9) m_uservar[1][1] = val.toInt();
        if (name==XML_PNAME_PARA10) m_uservar[1][2] = val.toInt();
        if (name==XML_PNAME_PARA11) m_uservar[1][3] = val.toInt();
        if (name==XML_PNAME_PARA12) m_uservar[2][0] = val.toInt();
        if (name==XML_PNAME_PARA13) m_uservar[2][1] = val.toInt();
        if (name==XML_PNAME_PARA14) m_uservar[2][2] = val.toInt();
        if (name==XML_PNAME_PARA15) m_uservar[2][3] = val.toInt();
        UpdateBaseMember();
		if (reader.isEndElement())
			reader.readNext();
	}
	else
		XmlSkipUnknownElement(reader);
	return true;
}
bool CodeVision::XmlRead(QXmlStreamReader &reader)
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
bool CodeVision::XmlWrite(QXmlStreamWriter &writer)
{
	writer.writeStartElement(XML_ELEMENT_CODE);
    writer.writeAttribute(XML_ATTR_NAME, XML_CNAME_VISION);
    writer.writeAttribute(XML_ATTR_NOTE, m_note);
    writer.writeAttribute(XML_ATTR_FLAG, QString("%1").arg(m_flag));

		writer.writeStartElement(XML_ELEMENT_PARA);
		writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA1);
            writer.writeCharacters(QString("%1").arg(m_vision));
		writer.writeEndElement();

        writer.writeStartElement(XML_ELEMENT_PARA);
        writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA2);
            writer.writeCharacters(QString("%1").arg(m_timeout));
        writer.writeEndElement();

        writer.writeStartElement(XML_ELEMENT_PARA);
        writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA3);
            writer.writeCharacters(QString("%1").arg(m_matchbmp));
        writer.writeEndElement();

        writer.writeStartElement(XML_ELEMENT_PARA);
        writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA4);
            writer.writeCharacters(QString("%1").arg(m_uservar[0][0]));
        writer.writeEndElement();

        writer.writeStartElement(XML_ELEMENT_PARA);
        writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA5);
            writer.writeCharacters(QString("%1").arg(m_uservar[0][1]));
        writer.writeEndElement();

        writer.writeStartElement(XML_ELEMENT_PARA);
        writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA6);
            writer.writeCharacters(QString("%1").arg(m_uservar[0][2]));
        writer.writeEndElement();

        writer.writeStartElement(XML_ELEMENT_PARA);
        writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA7);
            writer.writeCharacters(QString("%1").arg(m_uservar[0][3]));
        writer.writeEndElement();

        writer.writeStartElement(XML_ELEMENT_PARA);
        writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA8);
            writer.writeCharacters(QString("%1").arg(m_uservar[1][0]));
        writer.writeEndElement();

        writer.writeStartElement(XML_ELEMENT_PARA);
        writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA9);
            writer.writeCharacters(QString("%1").arg(m_uservar[1][1]));
        writer.writeEndElement();

        writer.writeStartElement(XML_ELEMENT_PARA);
        writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA10);
            writer.writeCharacters(QString("%1").arg(m_uservar[1][2]));
        writer.writeEndElement();

        writer.writeStartElement(XML_ELEMENT_PARA);
        writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA11);
            writer.writeCharacters(QString("%1").arg(m_uservar[1][3]));
        writer.writeEndElement();

        writer.writeStartElement(XML_ELEMENT_PARA);
        writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA12);
            writer.writeCharacters(QString("%1").arg(m_uservar[2][0]));
        writer.writeEndElement();

        writer.writeStartElement(XML_ELEMENT_PARA);
        writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA13);
            writer.writeCharacters(QString("%1").arg(m_uservar[2][1]));
        writer.writeEndElement();

        writer.writeStartElement(XML_ELEMENT_PARA);
        writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA14);
            writer.writeCharacters(QString("%1").arg(m_uservar[2][2]));
        writer.writeEndElement();

        writer.writeStartElement(XML_ELEMENT_PARA);
        writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA15);
            writer.writeCharacters(QString("%1").arg(m_uservar[2][3]));
        writer.writeEndElement();

    writer.writeEndElement();
	return true;
}
bool CodeVision::Update(bool bSaveAndValidate)
{
	if (m_form)
	{
		if (bSaveAndValidate)
		{
			bool change=false;
            if (m_vision != m_form->GetVision())
			{
                m_vision = m_form->GetVision();
				change=true;
			}
			if (m_timeout != m_form->GetTimeout())
			{
				m_timeout = m_form->GetTimeout();
				change=true;
			}
            if (m_matchbmp != m_form->GetMatch())
			{
                m_matchbmp = m_form->GetMatch();
				change=true;
			}
            if (m_uservar[0][0] != m_form->GetData(0, 0))
            {
                m_uservar[0][0] = m_form->GetData(0, 0);
                change=true;
            }
            if (m_uservar[0][1] != m_form->GetData(0, 1))
            {
                m_uservar[0][1] = m_form->GetData(0, 1);
                change=true;
            }
            if (m_uservar[0][2] != m_form->GetData(0, 2))
            {
                m_uservar[0][2] = m_form->GetData(0, 2);
                change=true;
            }
            if (m_uservar[0][3] != m_form->GetData(0, 3))
            {
                m_uservar[0][3] = m_form->GetData(0, 3);
                change=true;
            }
            if (m_uservar[1][0] != m_form->GetData(1, 0))
            {
                m_uservar[1][0] = m_form->GetData(1, 0);
                change=true;
            }
            if (m_uservar[1][1] != m_form->GetData(1, 1))
            {
                m_uservar[1][1] = m_form->GetData(1, 1);
                change=true;
            }
            if (m_uservar[1][2] != m_form->GetData(1, 2))
            {
                m_uservar[1][2] = m_form->GetData(1, 2);
                change=true;
            }
            if (m_uservar[1][3] != m_form->GetData(1, 3))
            {
                m_uservar[1][3] = m_form->GetData(1, 3);
                change=true;
            }
            if (m_uservar[2][0] != m_form->GetData(2, 0))
            {
                m_uservar[2][0] = m_form->GetData(2, 0);
                change=true;
            }
            if (m_uservar[2][1] != m_form->GetData(2, 1))
            {
                m_uservar[2][1] = m_form->GetData(2, 1);
                change=true;
            }
            if (m_uservar[2][2] != m_form->GetData(2, 2))
            {
                m_uservar[2][2] = m_form->GetData(2, 2);
                change=true;
            }
            if (m_uservar[2][3] != m_form->GetData(2, 3))
            {
                m_uservar[2][3] = m_form->GetData(2, 3);
                change=true;
            }
            if (change) UpdateBaseMember();
			return change;
		}
		else
		{
            m_form->SetVision(m_vision);
            m_form->SetTimeOut(m_timeout);
            m_form->SetMatch(m_matchbmp);
            m_form->SetData(0, 0, m_uservar[0][0]);
            m_form->SetData(0, 1, m_uservar[0][1]);
            m_form->SetData(0, 2, m_uservar[0][2]);
            m_form->SetData(0, 3, m_uservar[0][3]);
            m_form->SetData(1, 0, m_uservar[1][0]);
            m_form->SetData(1, 1, m_uservar[1][1]);
            m_form->SetData(1, 2, m_uservar[1][2]);
            m_form->SetData(1, 3, m_uservar[1][3]);
            m_form->SetData(2, 0, m_uservar[2][0]);
            m_form->SetData(2, 1, m_uservar[2][1]);
            m_form->SetData(2, 2, m_uservar[2][2]);
            m_form->SetData(2, 3, m_uservar[2][3]);
            m_form->UpdateWidgetState();
		}
	}
	return false;
}
bool CodeVision::GenerateCode(quint16* code, quint32 *para, quint8 other)
{
    code[0] = CODE_VISION | (((quint16)m_flag) << 8);
    para[0] = m_matchbmp&7;
    para[0] <<= 4;
    para[0] |= m_vision&7;
    para[0] <<= 12;
    para[0] |= m_timeout&0xFFF;

    code[1] = CODE_CONST | (((quint16)m_flag) << 8);
    para[1] = m_uservar[0][1];
    para[1] <<= 16;
    para[1] |= m_uservar[0][0];    
    code[2] = CODE_CONST | (((quint16)m_flag) << 8);
    para[2] = m_uservar[0][3];
    para[2] <<= 16;
    para[2] |= m_uservar[0][2];

    code[3] = CODE_CONST | (((quint16)m_flag) << 8);
    para[3] = m_uservar[1][1];
    para[3] <<= 16;
    para[3] |= m_uservar[1][0];
    code[4] = CODE_CONST | (((quint16)m_flag) << 8);
    para[4] = m_uservar[1][3];
    para[4] <<= 16;
    para[4] |= m_uservar[1][2];

    code[5] = CODE_CONST | (((quint16)m_flag) << 8);
    para[5] = m_uservar[2][1];
    para[5] <<= 16;
    para[5] |= m_uservar[2][0];
    code[6] = CODE_CONST | (((quint16)m_flag) << 8);
    para[6] = m_uservar[2][3];
    para[6] <<= 16;
    para[6] |= m_uservar[2][2];

    return true;
}

void CodeVision::UpdateBaseMember()
{
    m_name = QString(tr("视觉")) + QString("%1").arg(m_vision+1) + QString(tr("匹配1["))
                                    + xStringResource::GetUserVarName(m_uservar[0][0]) + QString((","))
                                    + xStringResource::GetUserVarName(m_uservar[0][1]) + QString((","))
                                    + xStringResource::GetUserVarName(m_uservar[0][2]) + QString((","))
                                    + xStringResource::GetUserVarName(m_uservar[0][3]) + QString((","))
                                    + xStringResource::GetUserVarName(m_uservar[1][0]) + QString((","))
                                    + xStringResource::GetUserVarName(m_uservar[1][1]) + QString((","))
                                    + xStringResource::GetUserVarName(m_uservar[1][2]) + QString((","))
                                    + xStringResource::GetUserVarName(m_uservar[1][3]) + QString((","))
                                    + xStringResource::GetUserVarName(m_uservar[2][0]) + QString((","))
                                    + xStringResource::GetUserVarName(m_uservar[2][1]) + QString((","))
                                    + xStringResource::GetUserVarName(m_uservar[2][2]) + QString((","))
                                    + xStringResource::GetUserVarName(m_uservar[2][3])
                                    + QString(("]"));
}

bool CodeVision::IsModified()
{
	if (m_form)
	{
        if ((m_vision != m_form->GetVision())||
            (m_timeout != m_form->GetTimeout())||
            (m_matchbmp != m_form->GetMatch())||
            (m_uservar[0][0] != m_form->GetData(0, 0))||
            (m_uservar[0][1] != m_form->GetData(0, 1))||
            (m_uservar[0][2] != m_form->GetData(0, 2))||
            (m_uservar[0][3] != m_form->GetData(0, 3))||
            (m_uservar[1][0] != m_form->GetData(1, 0))||
            (m_uservar[1][1] != m_form->GetData(1, 1))||
            (m_uservar[1][2] != m_form->GetData(1, 2))||
            (m_uservar[1][3] != m_form->GetData(1, 3))||
            (m_uservar[2][0] != m_form->GetData(2, 0))||
            (m_uservar[2][1] != m_form->GetData(2, 1))||
            (m_uservar[2][2] != m_form->GetData(2, 2))||
            (m_uservar[2][3] != m_form->GetData(2, 3)))
            return true;
	}
	return XmlModelItem::IsModified();
}
