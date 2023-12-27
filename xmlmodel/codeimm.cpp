#include "xconfig.h"
#include "formactimm.h"
#include "codeimm.h"

CodeImm::CodeImm(QWidget *form) : XmlModelItem(QIcon(":/img/action/Imm.png"), form)
{
	m_code = CODE_IMM;
	m_form = (FormActIMM*)form;
	m_delay = 0;
	m_type = IMMOUT_EMO;
	UpdateBaseMember();
}
bool CodeImm::XmlReadPara(QXmlStreamReader &reader)
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
bool CodeImm::XmlRead(QXmlStreamReader &reader)
{
	QString type = reader.attributes().value(XML_ATTR_TYPE).toString();
	m_type = IMMOUT_EMO;
	if (type==XML_TYPE_EMC)
		m_type = IMMOUT_EMC;
	if (type==XML_TYPE_EEF)
		m_type = IMMOUT_EEF;
	if (type==XML_TYPE_EEB)
		m_type = IMMOUT_EEB;
	if (type==XML_TYPE_C1P1)
		m_type = IMMOUT_C1P1;
	if (type==XML_TYPE_C1P2)
		m_type = IMMOUT_C1P2;
	if (type==XML_TYPE_C2P1)
		m_type = IMMOUT_C2P1;
	if (type==XML_TYPE_C2P2)
		m_type = IMMOUT_C2P2;
 	if (type==XML_TYPE_EEF_OFF)
		m_type = IMMOUT_EEF_OFF;
	if (type==XML_TYPE_EEB_OFF)
		m_type = IMMOUT_EEB_OFF;
	if (type==XML_TYPE_C1P1_OFF)
		m_type = IMMOUT_C1P1_OFF;
	if (type==XML_TYPE_C1P2_OFF)
		m_type = IMMOUT_C1P2_OFF;
	if (type==XML_TYPE_C2P1_OFF)
		m_type = IMMOUT_C2P1_OFF;
	if (type==XML_TYPE_C2P2_OFF)
		m_type = IMMOUT_C2P2_OFF;
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
bool CodeImm::XmlWrite(QXmlStreamWriter &writer)
{
	writer.writeStartElement(XML_ELEMENT_CODE);
	writer.writeAttribute(XML_ATTR_NAME, XML_CNAME_IMM);
	switch(m_type)
	{
	case IMMOUT_EMO:
		writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_EMO);
		break;
	case IMMOUT_EMC:
		writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_EMC);
		break;
	case IMMOUT_EEF:
		writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_EEF);
		break;
	case IMMOUT_EEB:
		writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_EEB);
		break;
	case IMMOUT_C1P1:
		writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_C1P1);
		break;
	case IMMOUT_C1P2:
		writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_C1P2);
		break;
	case IMMOUT_C2P1:
		writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_C2P1);
		break;
	case IMMOUT_EEF_OFF:
		writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_EEF_OFF);
		break;
	case IMMOUT_EEB_OFF:
		writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_EEB_OFF);
		break;
	case IMMOUT_C1P1_OFF:
		writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_C1P1_OFF);
		break;
	case IMMOUT_C1P2_OFF:
		writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_C1P2_OFF);
		break;
	case IMMOUT_C2P1_OFF:
		writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_C2P1_OFF);
		break;
	case IMMOUT_C2P2_OFF:
		writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_C2P2_OFF);
		break;
	default:
		writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_C2P2);
		break;
	}
    writer.writeAttribute(XML_ATTR_NOTE, m_note);
    writer.writeAttribute(XML_ATTR_FLAG, QString("%1").arg(m_flag));


		writer.writeStartElement(XML_ELEMENT_PARA);
		writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA1);
			writer.writeCharacters(QString("%1").arg(m_delay));
		writer.writeEndElement();
	writer.writeEndElement();
	return true;
}
bool CodeImm::Update(bool bSaveAndValidate)
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
bool CodeImm::GenerateCode(quint16* code, quint32 *para, quint8 other)
{
    code[0] = CODE_IMM | (((quint16)m_flag) << 8);
	para[0] = m_type;
    para[0] |= m_delay<< 16;
	return true;
}

void CodeImm::UpdateBaseMember()
{
    if (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_YZ)
    {
        switch(m_type)
        {
        case IMMOUT_EMO:
            m_name = QString(tr("铸机[等待开模] 超时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
            break;
        case IMMOUT_EMC:
            m_name = QString(tr("铸机[允许关模] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
            break;
        case IMMOUT_EEF:
            m_name = QString(tr("铸机[允许顶针前进] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
            break;
        case IMMOUT_EEB:
            m_name = QString(tr("铸机[允许顶针后退] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
            break;
        case IMMOUT_EEF_OFF:
            m_name = QString(tr("铸机[禁止顶针前进] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
            break;
        case IMMOUT_EEB_OFF:
            m_name = QString(tr("铸机[禁止顶针后退] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
            break;
        case IMMOUT_C1P1:
            m_name = QString(tr("铸机[允许抽芯1位置1] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
            break;
        case IMMOUT_C1P2:
            m_name = QString(tr("铸机[允许抽芯1位置2] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
            break;
        case IMMOUT_C2P1:
            m_name = QString(tr("铸机[允许抽芯2位置1] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
            break;
        case IMMOUT_C1P1_OFF:
            m_name = QString(tr("铸机[禁止抽芯1位置1] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
            break;
        case IMMOUT_C1P2_OFF:
            m_name = QString(tr("铸机[禁止抽芯1位置2] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
            break;
        case IMMOUT_C2P1_OFF:
            m_name = QString(tr("铸机[禁止抽芯2位置1] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
            break;
        case IMMOUT_C2P2_OFF:
            m_name = QString(tr("铸机[禁止抽芯2位置2] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
            break;
        default:
            m_name = QString(tr("铸机[允许抽芯2位置2] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
            break;
        }
    }
    else
    {
        switch(m_type)
        {
        case IMMOUT_EMO:
    #if FACTORY == FA_SINROBOT_JC
            m_name = QString(tr("机床[等待加工完成] 超时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #elif FACTORY == FA_VICTOR_SPECIAL
            m_name = QString(tr("塑机[等待加工完成] 超时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #else
            m_name = QString(tr("塑机[等待开模] 超时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #endif
            break;
        case IMMOUT_EMC:
    #if FACTORY == FA_SINROBOT_JC
            m_name = QString(tr("机床[允许加工启动] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #elif FACTORY == FA_VICTOR_SPECIAL
            m_name = QString(tr("塑机[允许加工启动] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #else
            m_name = QString(tr("塑机[允许关模] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #endif
            break;
        case IMMOUT_EEF:
    #if FACTORY == FA_SINROBOT_JC
            m_name = QString(tr("机床[允许顶针前进] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #else
            m_name = QString(tr("塑机[允许顶针前进] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #endif
            break;
        case IMMOUT_EEB:
    #if FACTORY == FA_SINROBOT_JC
            m_name = QString(tr("机床[允许顶针后退] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #else
            m_name = QString(tr("塑机[允许顶针后退] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #endif
            break;
        case IMMOUT_EEF_OFF:
    #if FACTORY == FA_SINROBOT_JC
            m_name = QString(tr("机床[禁止顶针前进] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #else
            m_name = QString(tr("塑机[禁止顶针前进] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #endif
            break;
        case IMMOUT_EEB_OFF:
    #if FACTORY == FA_SINROBOT_JC
            m_name = QString(tr("机床[禁止顶针后退] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #else
            m_name = QString(tr("塑机[禁止顶针后退] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #endif
            break;
        case IMMOUT_C1P1:
    #if (FACTORY == FA_SHINI)
            m_name = QString(tr("塑机[允许中子1进] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #elif FACTORY == FA_SINROBOT_JC
            m_name = QString(tr("机床[允许抽芯1位置1] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #else
            m_name = QString(tr("塑机[允许抽芯1位置1] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #endif
            break;
        case IMMOUT_C1P2:
    #if (FACTORY == FA_SHINI)
            m_name = QString(tr("塑机[允许中子1退] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #elif FACTORY == FA_SINROBOT_JC
            m_name = QString(tr("机床[允许抽芯1位置2] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #else
            m_name = QString(tr("塑机[允许抽芯1位置2] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #endif
            break;
        case IMMOUT_C2P1:
    #if (FACTORY == FA_SHINI)
            m_name = QString(tr("塑机[允许中子2进] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #elif FACTORY == FA_SINROBOT_JC
            m_name = QString(tr("机床[允许抽芯2位置1] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #else
            m_name = QString(tr("塑机[允许抽芯2位置1] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #endif
            break;
        case IMMOUT_C1P1_OFF:
    #if (FACTORY == FA_SHINI)
            m_name = QString(tr("塑机[禁止中子1进] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #elif FACTORY == FA_SINROBOT_JC
            m_name = QString(tr("机床[禁止抽芯1位置1] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #else
            m_name = QString(tr("塑机[禁止抽芯1位置1] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #endif
            break;
        case IMMOUT_C1P2_OFF:
    #if (FACTORY == FA_SHINI)
            m_name = QString(tr("塑机[禁止中子1退] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #elif FACTORY == FA_SINROBOT_JC
            m_name = QString(tr("机床[禁止抽芯1位置2] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #else
            m_name = QString(tr("塑机[禁止抽芯1位置2] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #endif
            break;
        case IMMOUT_C2P1_OFF:
    #if (FACTORY == FA_SHINI)
            m_name = QString(tr("塑机[禁止中子2进] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #elif FACTORY == FA_SINROBOT_JC
            m_name = QString(tr("机床[禁止抽芯2位置1] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #else
            m_name = QString(tr("塑机[禁止抽芯2位置1] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #endif
            break;
        case IMMOUT_C2P2_OFF:
    #if (FACTORY == FA_SHINI)
            m_name = QString(tr("塑机[禁止中子2退] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #elif FACTORY == FA_SINROBOT_JC
            m_name = QString(tr("机床[禁止抽芯2位置2] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #else
            m_name = QString(tr("塑机[禁止抽芯2位置2] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #endif
            break;
        default:
    #if (FACTORY == FA_SHINI)
            m_name = QString(tr("塑机[允许中子2退] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #elif FACTORY == FA_SINROBOT_JC
            m_name = QString(tr("机床[允许抽芯2位置2] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #else
            m_name = QString(tr("塑机[允许抽芯2位置2] 延时")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    #endif
            break;
        }
    }
}

bool CodeImm::IsModified()
{
	if (m_form)
	{
		if ((m_delay != m_form->GetDelay())||
			(m_type != m_form->GetType()))
			return true;
	}
	return XmlModelItem::IsModified();
}

