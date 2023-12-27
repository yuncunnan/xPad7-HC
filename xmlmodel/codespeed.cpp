#include "formactspeed.h"
#include "codespeed.h"
#include "cmbprotocol.h"
#include "servoalias.h"

CodeSpeed::CodeSpeed(QWidget *form) :
    XmlModelItem(QIcon(":/img/action/ChangeSpd.png"), form, QObject::tr("伺服速度调整")),
    m_form((FormActSpeed*)form)
{
	m_code = CODE_SPEED;
	m_speed = 0;
    m_axes = 0;
    UpdateBaseMember();
}
bool CodeSpeed::XmlReadPara(QXmlStreamReader &reader)
{
	QString name = reader.attributes().value(XML_ATTR_NAME).toString();
    if ((name==XML_PNAME_PARA1)||
       (name==XML_PNAME_PARA2))
    {
		QString val = reader.readElementText();
        if (name==XML_PNAME_PARA1) m_speed = val.toInt();
        if (name==XML_PNAME_PARA2) m_axes = val.toInt();
        UpdateBaseMember();
		if (reader.isEndElement())
			reader.readNext();
	}
	else
		XmlSkipUnknownElement(reader);
	return true;
}
bool CodeSpeed::XmlRead(QXmlStreamReader &reader)
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
bool CodeSpeed::XmlWrite(QXmlStreamWriter &writer)
{
	writer.writeStartElement(XML_ELEMENT_CODE);
	writer.writeAttribute(XML_ATTR_NAME, XML_CNAME_SPEED);
    writer.writeAttribute(XML_ATTR_NOTE, m_note);
    writer.writeAttribute(XML_ATTR_FLAG, QString("%1").arg(m_flag));


		writer.writeStartElement(XML_ELEMENT_PARA);
        writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA1);
        writer.writeCharacters(QString("%1").arg(m_speed));
        writer.writeEndElement();

        writer.writeStartElement(XML_ELEMENT_PARA);
        writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA2);
        writer.writeCharacters(QString("%1").arg(m_axes));
        writer.writeEndElement();

    writer.writeEndElement();
	return true;
}

bool CodeSpeed::GenerateCode(quint16* code, quint32 *para, quint8 other)
{
    quint32 relSpd = 0;
    if (m_speed)
    {
        relSpd = CMBProtocol::GetSrvSpeed();
        relSpd = qRound((double)(m_speed * relSpd) / 100.0);
        relSpd = (relSpd == 0 ? 1 : relSpd);
    }

    code[0] = m_code | (((quint16)m_flag) << 8);
    para[0] = relSpd;
    para[0] |= m_axes << 8;
	return true;
}
bool CodeSpeed::Update(bool bSaveAndValidate)
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
            if (m_axes != m_form->GetAxes())
            {
                m_axes = m_form->GetAxes();
                change=true;
            }
            if (change) UpdateBaseMember();
            return change;
        }
        else
        {
            m_form->SetSpeed(m_speed);
            m_form->SetAxes(m_axes);
            m_form->UpdateWidgetState();
        }
    }
    return false;
}
void CodeSpeed::UpdateBaseMember()
{
/*    QString axesName = "";
    axesName += ((m_axes&SRV_PAHOR)!= 0) ? tr("正引拔 ") : "";
    axesName += ((m_axes&SRV_PAVER)!= 0) ? tr("正上下 ") : "";
    axesName += ((m_axes&SRV_RAHOR)!= 0) ? tr("副引拔 ") : "";
    axesName += ((m_axes&SRV_RAVER)!= 0) ? tr("副上下 ") : "";
    axesName += ((m_axes&SRV_EXT)!= 0) ? tr("扩展 ") : "";
    axesName += ((m_axes&SRV_TRV)!= 0) ? tr("横行 ") : "";
    m_name = QString(tr("伺服速度"))  + axesName + QString(" %1 ").arg((m_speed));
    */
    if ((m_axes&SRV_PAHOR)!= 0)
        m_name = tr("伺服速度") + tr("[%1]  速度 %2").arg(GetServoName(AXIS_IDX_PHOR)).arg(m_speed);
    if ((m_axes&SRV_PAVER)!= 0)
        m_name = tr("伺服速度") + tr("[%1]  速度 %2").arg(GetServoName(AXIS_IDX_PVER)).arg(m_speed);
    if ((m_axes&SRV_RAHOR)!= 0)
        m_name = tr("伺服速度") + tr("[%1]  速度 %2").arg(GetServoName(AXIS_IDX_RHOR)).arg(m_speed);
    if ((m_axes&SRV_RAVER)!= 0)
        m_name = tr("伺服速度") + tr("[%1]  速度 %2").arg(GetServoName(AXIS_IDX_RVER)).arg(m_speed);
    if ((m_axes&SRV_EXT)!= 0)
        m_name = tr("伺服速度") + tr("[%1]  速度 %2").arg(GetServoName(AXIS_IDX_EXT)).arg(m_speed);
    if ((m_axes&SRV_TRV)!= 0)
        m_name = tr("伺服速度") + tr("[%1]  速度 %2").arg(GetServoName(AXIS_IDX_TRV)).arg(m_speed);
}
bool CodeSpeed::IsModified()
{
    if (m_form)
    {
        if ((m_speed != m_form->GetSpeed())||
            (m_axes != (m_form->GetAxes())))
             return true;
    }
    return XmlModelItem::IsModified();
}
