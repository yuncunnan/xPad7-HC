#include "xconfig.h"
#include "formactloopfree.h"
#include "codeloopfree.h"

CodeLoopFree::CodeLoopFree(QWidget *form) :	XmlModelItem(QIcon(":/img/action/Loop.png"), form, QString(tr("调用循环定位子程序")))
{
	m_form = (FormActLoopFree*)form;
	m_speed = 50;
	m_dspeed = 10;
    m_rotate = false;
    m_xdec = false;
	m_dlen = 0;
    m_poscount = 1;
    m_isrunner = false;
    m_trvrot = false;
    m_counter = 0;
    for (int i = 0; i < MAX_LOOP_POINTS; i ++)
	{
        m_pos[AXES_IDX_X][i] = 0;
        m_pos[AXES_IDX_Y][i] = 0;
        m_pos[AXES_IDX_Z][i] = 0;
	}
    m_code = CODE_FREEPOS;
}
CodeLoopFree::~CodeLoopFree()
{
}

void CodeLoopFree::UpdateBaseMember()
{
    m_codes = 2+m_poscount*3;
}

bool CodeLoopFree::XmlReadPara(QXmlStreamReader &reader)
{
	QString name = reader.attributes().value(XML_ATTR_NAME).toString();
	if ((name==XML_PNAME_PARA1)||
		(name==XML_PNAME_PARA2)||
		(name==XML_PNAME_PARA3)||
        (name==XML_PNAME_PARA4)||
        (name==XML_PNAME_PARA5)||
        (name==XML_PNAME_PARA6)||
        (name==XML_PNAME_PARA7)||
        (name==XML_PNAME_PARA8))
	{
		QString val = reader.readElementText();
		if (name==XML_PNAME_PARA1) m_speed = val.toInt();
		if (name==XML_PNAME_PARA2) m_dspeed = val.toInt();
		if (name==XML_PNAME_PARA3) m_dlen = val.toInt();
		if (name==XML_PNAME_PARA4) m_rotate = val.toInt();
        if (name==XML_PNAME_PARA5) m_xdec = val.toInt();
        if (name==XML_PNAME_PARA6) m_isrunner = val.toInt();
        if (name==XML_PNAME_PARA7) m_counter = val.toInt();
        if (name==XML_PNAME_PARA8) m_trvrot = val.toInt();
        UpdateBaseMember();
		if (reader.isEndElement())
			reader.readNext();
	}
	else
    if (name==XML_PNAME_PARA9)
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
					QString strx = reader.attributes().value(XML_ATTR_X).toString();
					QString stry = reader.attributes().value(XML_ATTR_Y).toString();
					QString strz = reader.attributes().value(XML_ATTR_Z).toString();
					QString val = reader.readElementText();
					int idx = val.toInt();
                    if (idx<=MAX_LOOP_POINTS)
					{
                        m_poscount = idx;
                        m_pos[AXES_IDX_X][idx-1] = strx.toInt();
                        m_pos[AXES_IDX_Y][idx-1] = stry.toInt();
                        m_pos[AXES_IDX_Z][idx-1] = strz.toInt();
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
bool CodeLoopFree::XmlRead(QXmlStreamReader &reader)
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
bool CodeLoopFree::XmlWrite(QXmlStreamWriter &writer)
{
	int i;
	writer.writeStartElement(XML_ELEMENT_CODE);
    writer.writeAttribute(XML_ATTR_NAME, XML_CNAME_LOOP);
    writer.writeAttribute(XML_ATTR_NOTE, m_note);
    writer.writeAttribute(XML_ATTR_FLAG, QString("%1").arg(m_flag));


	writer.writeStartElement(XML_ELEMENT_PARA);
	writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA1);
    writer.writeCharacters(QString("%1").arg(m_speed));
	writer.writeEndElement();

	writer.writeStartElement(XML_ELEMENT_PARA);
	writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA2);
    writer.writeCharacters(QString("%1").arg(m_dspeed));
	writer.writeEndElement();

	writer.writeStartElement(XML_ELEMENT_PARA);
	writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA3);
    writer.writeCharacters(QString("%1").arg(m_dlen));
	writer.writeEndElement();

	writer.writeStartElement(XML_ELEMENT_PARA);
	writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA4);
    writer.writeCharacters(QString("%1").arg(m_rotate));
	writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA5);
    writer.writeCharacters(QString("%1").arg(m_xdec));
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA6);
    writer.writeCharacters(QString("%1").arg(m_isrunner));
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA7);
    writer.writeCharacters(QString("%1").arg(m_counter));
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA8);
    writer.writeCharacters(QString("%1").arg(m_trvrot));
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA9);
    for (i=0; i<m_poscount; i++)
	{
		writer.writeStartElement(XML_ELEMENT_VALUE);
        writer.writeAttribute(XML_ATTR_X, QString("%1").arg(m_pos[AXES_IDX_X][i]));
        writer.writeAttribute(XML_ATTR_Y, QString("%1").arg(m_pos[AXES_IDX_Y][i]));
        writer.writeAttribute(XML_ATTR_Z, QString("%1").arg(m_pos[AXES_IDX_Z][i]));
            writer.writeCharacters(QString("%1").arg(i+1));
		writer.writeEndElement();
	}
	writer.writeEndElement();

	writer.writeEndElement();
	return true;
}
bool CodeLoopFree::Update(bool bSaveAndValidate)
{
	if (m_form)
	{
		if (bSaveAndValidate)
		{
			bool change=false;
			int i;
            if (m_poscount != m_form->GetPosCount())
            {
                m_poscount = m_form->GetPosCount();
                change = true;
            }
            for (i=0; i<m_poscount; i++)
			{
                if (m_pos[AXES_IDX_X][i] != m_form->GetPos(AXES_IDX_X, i))
				{
                    m_pos[AXES_IDX_X][i] = m_form->GetPos(AXES_IDX_X, i);
					change=true;
				}
                if (m_pos[AXES_IDX_Y][i] != m_form->GetPos(AXES_IDX_Y, i))
				{
                    m_pos[AXES_IDX_Y][i] = m_form->GetPos(AXES_IDX_Y, i);
					change=true;
				}
                if (m_pos[AXES_IDX_Z][i] != m_form->GetPos(AXES_IDX_Z, i))
				{
                    m_pos[AXES_IDX_Z][i] = m_form->GetPos(AXES_IDX_Z, i);
					change=true;
				}
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
			if (m_xdec != m_form->GetXDec())
			{
				m_xdec = m_form->GetXDec();
				change=true;
			}
			if (m_rotate != m_form->GetRotate())
			{
				m_rotate = m_form->GetRotate();
				change=true;
			}
            if (m_dlen != m_form->GetDLen())
            {
                m_dlen = m_form->GetDLen();
                change=true;
            }
            if (m_isrunner != m_form->GetIsRunner())
            {
                m_isrunner = m_form->GetIsRunner();
                change=true;
            }
            if (m_trvrot != m_form->GetTrvRot())
            {
                m_trvrot = m_form->GetTrvRot();
                change=true;
            }
            if (m_counter != m_form->GetVar())
            {
                m_counter = m_form->GetVar();
                change=true;
            }
            if (change) UpdateBaseMember();
			return change;
		}
		else
		{
			int i;
            for (i=0; i<m_poscount; i++)
			{
                m_form->SetPos(AXES_IDX_X, i, m_pos[AXES_IDX_X][i]);
                m_form->SetPos(AXES_IDX_Y, i, m_pos[AXES_IDX_Y][i]);
                m_form->SetPos(AXES_IDX_Z, i, m_pos[AXES_IDX_Z][i]);
			}

            m_form->SetPosCount(m_poscount);
			m_form->SetSpeed(m_speed);
			m_form->SetDSpeed(m_dspeed);
			m_form->SetRotate(m_rotate);
			m_form->SetXDec(m_xdec);
			m_form->SetDLen(m_dlen);
            m_form->SetIsRunner(m_isrunner);
            m_form->SetVar(m_counter);
            m_form->SetTrvRot(m_trvrot);
			m_form->UpdateWidgetState();
		}
	}
	return false;
}

bool CodeLoopFree::GenerateCode(quint16* code, quint32 *para, quint8 other)
{
    int idx = 0;
    quint32 relSpd = CMBProtocol::GetSrvSpeed();
    relSpd = qRound((double)(m_speed * relSpd) / 100.0);
    relSpd = (relSpd == 0 ? 1 : relSpd);

    quint32 decSpd = CMBProtocol::GetSrvSpeed();
    decSpd = qRound((double)(m_dspeed * decSpd) / 100.0);
    decSpd = (decSpd == 0 ? 1 : decSpd);

    code[0] = CODE_FREEPOS | (((quint16)m_flag) << 8);
    para[0] = 0;
    if (m_isrunner)para[0] = 0x1;
    if (m_xdec)para[0] |= 0x02;
    if (m_rotate)para[0] |= 0x04;
    if (m_trvrot)para[0] |= 0x10;
    para[0] |= (m_poscount<<8)&0xFF00;
    para[0] |= m_counter << 16;

    code[1] = CODE_CONST | (((quint16)m_flag) << 8);
    para[1] = relSpd;
    para[1] |= decSpd<<8;
    para[1] |= m_dlen << 16;

    idx = 2;
    for (int i =0; i < m_poscount; i++)
    {
        code[idx] = CODE_CONST | (((quint16)m_flag) << 8);
        para[idx] = m_pos[AXES_IDX_X][i];
        idx++;

        code[idx] = CODE_CONST | (((quint16)m_flag) << 8);
        para[idx] = m_pos[AXES_IDX_Y][i];
        idx++;

        code[idx] = CODE_CONST | (((quint16)m_flag) << 8);
        para[idx] = m_pos[AXES_IDX_Z][i];
        idx++;
    }

    return true;
}

bool CodeLoopFree::IsModified()
{
	int i;
	if (m_form)
	{
		if ((m_speed != m_form->GetSpeed())||
			(m_dspeed != m_form->GetDSpeed())||
			(m_rotate != m_form->GetRotate())||
			(m_xdec != m_form->GetXDec())||
            (m_dlen != m_form->GetDLen())||
            (m_isrunner != m_form->GetIsRunner())||
            (m_trvrot != m_form->GetTrvRot())||
            (m_poscount != (m_form->GetPosCount()))||
            (m_counter != m_form->GetVar()))
			 return true;
        for (i=0; i<m_poscount; i++)
		{
            if ((m_pos[AXES_IDX_X][i]!=m_form->GetPos(AXES_IDX_X ,i))||
                (m_pos[AXES_IDX_Y][i]!=m_form->GetPos(AXES_IDX_Y ,i))||
                (m_pos[AXES_IDX_Z][i]!=m_form->GetPos(AXES_IDX_Z ,i)))
				return true;
		}
	}
	return XmlModelItem::IsModified();
}

void CodeLoopFree::SetUserVar(quint16 var, int idx)
{
    m_counter = var;
}

quint16 CodeLoopFree::GetUserVar(int idx)
{
    if ((m_counter &MASK_VAR_TYPE) == VAR_TYPE_USR)
        return m_counter;
    return 0;
}
