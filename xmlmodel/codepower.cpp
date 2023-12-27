#include <QSettings>
#include "formactpower.h"
#include "codepower.h"
#include "cmbprotocol.h"
#include "servoalias.h"

CodePower::CodePower(QWidget *form) :	XmlModelItem(QIcon(), form)
{
    m_code = CODE_POWER;
    m_form = (FormActPower*)form;
	m_axes = 7;
    m_poweroff = false;
    m_codes = 1;
	UpdateBaseMember();
}

bool CodePower::XmlReadPara(QXmlStreamReader &reader)
{
	QString name = reader.attributes().value(XML_ATTR_NAME).toString();
    if (name==XML_PNAME_PARA1)
	{
		QString val = reader.readElementText();
		if (name==XML_PNAME_PARA1)
		{
            m_poweroff = val.toInt();
		}

		UpdateBaseMember();
		if (reader.isEndElement())
			reader.readNext();
	}
	else
		XmlSkipUnknownElement(reader);
	return true;
}
bool CodePower::XmlRead(QXmlStreamReader &reader)
{
    m_note = reader.attributes().value(XML_ATTR_NOTE).toString();
    m_flag = reader.attributes().value(XML_ATTR_FLAG).toString().toUShort();
    m_axes = reader.attributes().value(XML_ATTR_AXES).toString().toInt();
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
bool CodePower::XmlWrite(QXmlStreamWriter &writer)
{
	writer.writeStartElement(XML_ELEMENT_CODE);
    writer.writeAttribute(XML_ATTR_NAME, XML_CNAME_POWER);
	writer.writeAttribute(XML_ATTR_AXES, QString("%1").arg(m_axes));
    writer.writeAttribute(XML_ATTR_NOTE, m_note);
    writer.writeAttribute(XML_ATTR_FLAG, QString("%1").arg(m_flag));


		writer.writeStartElement(XML_ELEMENT_PARA);
        writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA1);
            writer.writeCharacters(QString("%1").arg(m_poweroff));
		writer.writeEndElement();
	writer.writeEndElement();
	return true;
}
bool CodePower::Update(bool bSaveAndValidate)
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
            if (m_poweroff != m_form->GetPoweroff())
            {
                m_poweroff = m_form->GetPoweroff();
                change = true;
            }
			if (change) UpdateBaseMember();
			return change;
		}
		else
		{
			m_form->SetAxes(m_axes);
            m_form->SetPoweroff(m_poweroff);
			m_form->UpdateWidgetState();
		}
    }
	return false;
}

bool CodePower::GenerateCode(quint16* code, quint32 *para, quint8 other)
{
    code[0] = CODE_POWER | (((quint16)m_flag) << 8);
	para[0] = (m_axes & 0x3F);
    para[0] <<= 8;
    para[0] |= m_poweroff;
	return true;
}

void CodePower::UpdateBaseMember()
{
    QString type;
    QString straxis;

    if ((m_axes>>AXIS_IDX_PHOR)&1)
        straxis = QString(GetServoName(AXIS_IDX_PHOR));
    else
        straxis = ("");

    if ((m_axes>>AXIS_IDX_PVER)&1)
        straxis += (straxis == ("")) ? QString(GetServoName(AXIS_IDX_PVER)) : QString("_" + GetServoName(AXIS_IDX_PVER));
    else
        straxis += ("");

    if ((m_axes>>AXIS_IDX_TRV)&1)
        straxis += (straxis == ("")) ? QString(GetServoName(AXIS_IDX_TRV)) : QString("_" + GetServoName(AXIS_IDX_TRV));
    else
        straxis += ("");

    if ((m_axes>>AXIS_IDX_RVER)&1)
        straxis += (straxis == ("")) ? QString(GetServoName(AXIS_IDX_RVER)) : QString("_" + GetServoName(AXIS_IDX_RVER));
    else
        straxis += ("");

    if ((m_axes>>AXIS_IDX_RHOR)&1)
        straxis += (straxis == ("")) ? QString(GetServoName(AXIS_IDX_RHOR)) : QString("_" + GetServoName(AXIS_IDX_RHOR));
    else
        straxis += ("");

    if ((m_axes>>AXIS_IDX_EXT)&1)
        straxis += (straxis == ("")) ? QString(GetServoName(AXIS_IDX_EXT)) : QString("_" + GetServoName(AXIS_IDX_EXT));
    else
        straxis += ("");

    if (straxis == (""))
        straxis = tr("未勾选任何轴");


    if (m_poweroff)
    {
        type = QString(tr("伺服电源关闭 [")) + straxis + QString(("]"));
        m_icon = QIcon(":/img/action/SrvOff.png");
    }
    else
    {
        type = QString(tr("伺服电源打开 [")) + straxis + QString(("]"));
        m_icon = QIcon(":/img/action/SrvOn.png");
    }
    m_name = type;
}

bool CodePower::IsModified()
{
	if (m_form)
	{
        if ((m_axes != m_form->GetAxes())|| (m_poweroff != m_form->GetPoweroff()))
            return true;
	}
	return XmlModelItem::IsModified();
}
