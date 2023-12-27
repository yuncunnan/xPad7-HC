#include "xconfig.h"
#include "formactrun.h"
#include "coderarm.h"

CodeRArm::CodeRArm(QWidget *form) : XmlModelItem(QIcon(), form)
{
	m_form = (FormActRun*)form;
	m_type = RUN_ACT_ASCENT;
	m_delay = 5;
    m_code = CODE_RUNARM;
    UpdateBaseMember();
}
bool CodeRArm::XmlReadPara(QXmlStreamReader &reader)
{
	QString name = reader.attributes().value(XML_ATTR_NAME).toString();
	if (name==XML_PNAME_PARA1)
	{
		QString val = reader.readElementText();
		m_delay = val.toInt();
		UpdateBaseMember();
		if (reader.isEndElement())
			reader.readNext();
	}
	else
		XmlSkipUnknownElement(reader);
	return true;
}
bool CodeRArm::XmlRead(QXmlStreamReader &reader)
{
	QString type = reader.attributes().value(XML_ATTR_TYPE).toString();
	m_note = reader.attributes().value(XML_ATTR_NOTE).toString();
    m_flag = reader.attributes().value(XML_ATTR_FLAG).toString().toUShort();
	if (type==XML_TYPE_ADV)
		m_type=RUN_ACT_ADVANCE;
	else
	if (type==XML_TYPE_RET)
		m_type=RUN_ACT_RETURN;
	else
	if (type==XML_TYPE_ASC)
		m_type=RUN_ACT_ASCENT;
	else
    if (type == XML_TYPE_DES)
		m_type=RUN_ACT_DESCENT;
    else
    if (type == XML_TYPE_HOR)
        m_type = RUN_ACT_HORIZONTAL;
    else
        m_type = RUN_ACT_VERTIACL;
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
bool CodeRArm::XmlWrite(QXmlStreamWriter &writer)
{
	writer.writeStartElement(XML_ELEMENT_CODE);
	writer.writeAttribute(XML_ATTR_NAME, XML_CNAME_RARM);
	if (m_type==RUN_ACT_ADVANCE)
		writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_ADV);
	else
	if (m_type==RUN_ACT_RETURN)
		writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_RET);
	else
	if (m_type==RUN_ACT_ASCENT)
		writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_ASC);
	else
    if (m_type==RUN_ACT_DESCENT)
		writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_DES);
    else
    if (m_type==RUN_ACT_HORIZONTAL)
        writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_HOR);
    else
        writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_VER);


	writer.writeAttribute(XML_ATTR_NOTE, m_note);
    writer.writeAttribute(XML_ATTR_FLAG, QString("%1").arg(m_flag));


		writer.writeStartElement(XML_ELEMENT_PARA);
		writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA1);
			writer.writeCharacters(QString("%1").arg(m_delay));
		writer.writeEndElement();

	writer.writeEndElement();
	return true;
}
bool CodeRArm::Update(bool bSaveAndValidate)
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
			if (change) UpdateBaseMember();
			return change;
		}
		else
		{
			m_form->SetDelay(m_delay);
			m_form->SetType(m_type);
			m_form->UpdateWidgetState();
		}
	}
	return false;
}

bool CodeRArm::GenerateCode(quint16* code, quint32 *para, quint8 other)
{
    code[0] = CODE_RUNARM | (((quint16)m_flag) << 8);
    para[0] = m_type;
    para[0] |= m_delay<< 16;
    return true;
}

void CodeRArm::UpdateBaseMember()
{
	if (m_type==RUN_ACT_ASCENT)
	{
		m_icon = QIcon(":/img/action/RaAsc.png");
        m_name = QString(tr("副臂[上升] 时间")) + QString(" %1").arg(((qreal)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
	}
	else if (m_type == RUN_ACT_DESCENT)
	{
		m_icon = QIcon(":/img/action/RaDes.png");
        m_name = QString(tr("副臂[下降] 时间")) + QString(" %1").arg(((qreal)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
	}
	else if (m_type == RUN_ACT_ADVANCE)
	{
		m_icon = QIcon(":/img/action/RaAdv.png");
#if (FACTORY == FA_KAIBOER)
        m_name = QString(tr("副臂[引拔退] 时间")) + QString(" %1").arg(((qreal)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
#else
        m_name = QString(tr("副臂[引拔进] 时间")) + QString(" %1").arg(((qreal)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
#endif
	}
    else if (m_type == RUN_ACT_RETURN)
	{
		m_icon = QIcon(":/img/action/RaRet.png");
#if (FACTORY == FA_KAIBOER)
        m_name = QString(tr("副臂[引拔进] 时间")) + QString(" %1").arg(((qreal)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
#else
        m_name = QString(tr("副臂[引拔退] 时间")) + QString(" %1").arg(((qreal)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
#endif
	}
    else if (m_type == RUN_ACT_HORIZONTAL)
    {
        m_icon = QIcon(":/img/action/Rotate.png");
#if FACTORY == FA_WEILIHE
        m_name = QString(tr("副臂[水平] 时间")) + QString(" %1").arg(((qreal)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
#elif FACTORY == FA_VICTOR_SPECIAL
        m_name = QString(tr("副臂[成品旋转] 时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
#else
        m_name = QString(tr("副臂[倒平] 时间")) + QString(" %1").arg(((qreal)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
#endif
    }
    else
    {
        m_icon = QIcon(":/img/action/Rotate.png");
#if FACTORY == FA_WEILIHE
        m_name = QString(tr("副臂[垂直] 时间")) + QString(" %1").arg(((qreal)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
#elif FACTORY == FA_VICTOR_SPECIAL
        m_name = QString(tr("副臂[毛坯旋转] 时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
#else
        m_name = QString(tr("副臂[倒直] 时间")) + QString(" %1").arg(((qreal)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
#endif
    }
}

bool CodeRArm::IsModified()
{
	if (m_form)
	{
		if ((m_type != m_form->GetType())||
			(m_delay != m_form->GetDelay()))
			return true;
	}
	return false;
}
