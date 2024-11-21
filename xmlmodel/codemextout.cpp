#include "xconfig.h"
#include "formactmextout.h"
#include "codemextout.h"
#include "xstringresource.h"
#include "qdebug.h"
/******************************pyq***************************************/
#include "cmbprotocol.h"
/******************************pyq end***************************************/
CodeMExtOut::CodeMExtOut(QWidget *form) :	XmlModelItem(QIcon(":/img/action/ExtOutput.png"), form)
{
    m_form = (FormActMExtOut*)form;
    m_code = CODE_MEXTOUT;
    m_delay = 5;
    m_outbmp = 0;
    m_type = 0;
    m_counter = 0;
    UpdateBaseMember();
}
bool CodeMExtOut::XmlReadPara(QXmlStreamReader &reader)
{
	QString name = reader.attributes().value(XML_ATTR_NAME).toString();
	if ((name==XML_PNAME_PARA1)||
        (name==XML_PNAME_PARA2)||
        (name==XML_PNAME_PARA3))
	{
		QString val = reader.readElementText();
        if (name==XML_PNAME_PARA1) m_outbmp = val.toInt();
		if (name==XML_PNAME_PARA2) m_delay = val.toInt();
        if (name==XML_PNAME_PARA3) m_counter = val.toInt();
		UpdateBaseMember();
		if (reader.isEndElement())
			reader.readNext();
	}
	else
		XmlSkipUnknownElement(reader);
	return true;
}
bool CodeMExtOut::XmlRead(QXmlStreamReader &reader)
{
	QString type = reader.attributes().value(XML_ATTR_TYPE).toString();
	m_type=0;
	if (type==XML_TYPE_ON)
		m_type=1;
    else if(type==XML_TYPE_PULSE)
        m_type = 2;
    m_note = reader.attributes().value(XML_ATTR_NOTE).toString();
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
bool CodeMExtOut::XmlWrite(QXmlStreamWriter &writer)
{
	writer.writeStartElement(XML_ELEMENT_CODE);
    writer.writeAttribute(XML_ATTR_NAME, XML_CNAME_MEXTOUT);
	if (m_type==1)
		writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_ON);
    else if (m_type==2)
        writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_PULSE);
    else
        writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_OFF);
    writer.writeAttribute(XML_ATTR_NOTE, m_note);

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
    writer.writeCharacters(QString("%1").arg(m_counter));
    writer.writeEndElement();

	writer.writeEndElement();
	return true;
}
bool CodeMExtOut::Update(bool bSaveAndValidate)
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
			if (m_type != m_form->GetType())
			{
				m_type = m_form->GetType();
				change=true;
			}
            if (m_counter != m_form->GetCounter())
            {
                m_counter = m_form->GetCounter();
                change=true;
            }
            if (m_outbmp != m_form->GetOutBmp())
			{
                m_outbmp = m_form->GetOutBmp();
				change=true;
			}
			if (change) UpdateBaseMember();
			return change;
		}
		else
		{
			m_form->SetDelay(m_delay);
			m_form->SetType(m_type);
            m_form->SetOutBmp(m_outbmp);
            m_form->SetCounter(m_counter);
			m_form->UpdateWidgetState();
		}
	}
	return false;
}

bool CodeMExtOut::GenerateCode(quint16* code, quint32 *para, quint8 other)
{
    code[0] = CODE_MEXTOUT;
    para[0] = m_outbmp;
    para[0] <<= 1;
    para[0] |= (m_type&0x1);
    para[0] <<= 10;
    para[0] |= (m_delay&0x3FF);
    if (m_type==2)
    {
        para[0] |= (1<<31);
    }
	return true;
}

void CodeMExtOut::UpdateBaseMember()
{
    /*************************pyq*不同主板时多扩展输出显示不同***************************************************************************/
    QString outName = "";
    if((CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_5AXIS)||(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H730_5AXIS))
    {
        for(int i=0 ;i<12 ;i++)
        {
            if((m_outbmp >> i)&1)
                outName += (" Y" + QString::number(i+17));
        }
    }
    else if(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_DVS)
    {
        for(int i= 0 ;i<9 ;i++)
        {
            if((m_outbmp >> i)&1)
                outName += ("Y" + QString::number(i+17));
        }
    }
    else
    {
        for(int i= 3 ;i<16 ;i++)
        {
            if((m_outbmp >> i)&1)
                outName += (" Y" + QString::number(i+1));
        }
    }
    if (m_type==1)
        m_name = QString(tr("开启多扩展输出[")) + outName + QString(tr("] 时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    else if(m_type==0)
        m_name = QString(tr("关闭多扩展输出[")) + outName + QString(tr("] 时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    else
        m_name = QString(tr("多扩展脉冲输出[")) + outName + QString(tr("] 时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
/*************************pyq end*************************************************************************************/
//	if (m_type==1)
//        m_name = QString(tr("开启多扩展输出[")) + QString::number((uint)(m_outbmp>>8), 2) + QString(tr("] 时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
//    else if(m_type==0)
//        m_name = QString(tr("关闭多扩展输出[")) + QString::number((uint)(m_outbmp>>8), 2) + QString(tr("] 时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
//    else
//        m_name = QString(tr("多扩展脉冲输出[")) + QString::number((uint)(m_outbmp>>8), 2) + QString(tr("] 时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
}

bool CodeMExtOut::IsModified()
{
	if (m_form)
	{
        if ((m_outbmp != m_form->GetOutBmp())||
            (m_counter != m_form->GetCounter())||
			(m_type != m_form->GetType())||
            (m_delay != m_form->GetDelay()))
			return true;
	}
	return XmlModelItem::IsModified();
}
void CodeMExtOut::SetUserVar(quint16 var, int idx)
{
    m_counter = var;
}

quint16 CodeMExtOut::GetUserVar(int idx)
{
    if ((m_counter &MASK_VAR_TYPE) == VAR_TYPE_USR)
        return m_counter;
    return 0;
}
