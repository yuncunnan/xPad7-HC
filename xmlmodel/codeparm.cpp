#include "xconfig.h"
#include "formactpro.h"
#include "codeparm.h"

CodePArm::CodePArm(QWidget *form) : XmlModelItem(QIcon(":/img/action/PaRotate.png"), form)
{
	m_form = (FormActPro*)form;
	m_type = PRO_ACT_HOZIONTAL;
	m_delay = 5;
    m_code = CODE_PROARM;
    UpdateBaseMember();
}
bool CodePArm::XmlReadPara(QXmlStreamReader &reader)
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
bool CodePArm::XmlRead(QXmlStreamReader &reader)
{
	QString type = reader.attributes().value(XML_ATTR_TYPE).toString();
    m_note = reader.attributes().value(XML_ATTR_NOTE).toString();
    m_flag = reader.attributes().value(XML_ATTR_FLAG).toString().toUShort();
	m_type=PRO_ACT_HOZIONTAL;
	if (type==XML_TYPE_VER)
		m_type=PRO_ACT_VERTIACL;
	if (type==XML_TYPE_JIGB)
		m_type=PRO_ACT_JIG_BIND;
	if (type==XML_TYPE_JIGR)
		m_type=PRO_ACT_JIG_RELEASE;
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
bool CodePArm::XmlWrite(QXmlStreamWriter &writer)
{
	writer.writeStartElement(XML_ELEMENT_CODE);
	writer.writeAttribute(XML_ATTR_NAME, XML_CNAME_PARM);
	if (m_type==PRO_ACT_VERTIACL)
		writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_VER);
	else if (m_type==PRO_ACT_JIG_BIND)
		writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_JIGB);
	else if (m_type==PRO_ACT_JIG_RELEASE)
		writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_JIGR);
	else
		writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_HOR);
    writer.writeAttribute(XML_ATTR_NOTE, m_note);
    writer.writeAttribute(XML_ATTR_FLAG, QString("%1").arg(m_flag));


		writer.writeStartElement(XML_ELEMENT_PARA);
		writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA1);
			writer.writeCharacters(QString("%1").arg(m_delay));
		writer.writeEndElement();

	writer.writeEndElement();
	return true;
}
bool CodePArm::Update(bool bSaveAndValidate)
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

bool CodePArm::GenerateCode(quint16* code, quint32 *para, quint8 other)
{
    code[0] = CODE_PROARM | (((quint16)m_flag) << 8);
    para[0] = m_type;
    para[0] |= m_delay<< 16;
	return true;
}

void CodePArm::UpdateBaseMember()
{
    if (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_YZ)
    {
        if (m_type==PRO_ACT_HOZIONTAL)
            m_name = QString(tr("取件臂[倒平] 时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
        else if (m_type==PRO_ACT_JIG_BIND)
            m_name = QString(tr("治具[夹紧] 时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
        else if (m_type==PRO_ACT_JIG_RELEASE)
            m_name = QString(tr("治具[松开] 时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
        else
            m_name = QString(tr("取件臂[倒直] 时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    }
    else
    {
        if (m_type==PRO_ACT_HOZIONTAL)
    #if FACTORY == FA_WEILIHE
            m_name = QString(tr("正臂[水平] 时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #elif FACTORY == FA_VICTOR_SPECIAL
            m_name = QString(tr("正臂[成品旋转] 时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #else
            m_name = QString(tr("正臂[倒平] 时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #endif
        else if (m_type==PRO_ACT_JIG_BIND)
            m_name = QString(tr("治具[夹紧] 时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
        else if (m_type==PRO_ACT_JIG_RELEASE)
            m_name = QString(tr("治具[松开] 时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
        else
    #if FACTORY == FA_WEILIHE
            m_name = QString(tr("正臂[垂直] 时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #elif FACTORY == FA_VICTOR_SPECIAL
            m_name = QString(tr("正臂[毛坯旋转] 时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #else
            m_name = QString(tr("正臂[倒直] 时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #endif
    }
}

bool CodePArm::IsModified()
{
	if (m_form)
	{
		if ((m_type != m_form->GetType())||
			(m_delay != m_form->GetDelay()))
			return true;
	}
	return XmlModelItem::IsModified();
}
