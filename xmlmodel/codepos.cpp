#include <QSettings>
#include "formactpos.h"
#include "codepos.h"
#include "cmbprotocol.h"
#include "servoalias.h"
#include "xstringresource.h"

CodePos::CodePos(QWidget *form) : XmlModelItem(QIcon(), form)
{
	m_code = CODE_POS;
	m_form = (FormActPos*)form;
	m_axes = 1;
	m_speed = 50;
    m_x_type = POS_TYPE_POINT;
    m_y_type = POS_TYPE_POINT;
    m_z_type = POS_TYPE_POINT;
    m_a_type = POS_TYPE_POINT;
    m_b_type = POS_TYPE_POINT;
    m_c_type = POS_TYPE_POINT;
	m_x = 0;
	m_y = 0;
	m_z = 0;
	m_a = 0;
	m_b = 0;
	m_c = 0;
	m_type = SERVO_POS_ABS;
    m_codes = 2;
    m_delay = 0;
    UpdateBaseMember();
}
bool CodePos::XmlReadPara(QXmlStreamReader &reader)
{
	QString name = reader.attributes().value(XML_ATTR_NAME).toString();
    int type = reader.attributes().value(XML_ATTR_TYPE).toString().toInt();
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
		if (name==XML_PNAME_PARA1)
			m_speed = val.toInt();
		else
		if (name==XML_PNAME_PARA2)
		{
			m_x = val.toInt();
			m_x_type = type;
		}
		else
		if (name==XML_PNAME_PARA3)
		{
			m_y = val.toInt();
			m_y_type = type;
		}
		else
		if (name==XML_PNAME_PARA4)
		{
			m_z = val.toInt();
			m_z_type = type;
		}
		else
		if (name==XML_PNAME_PARA5)
		{
			m_a = val.toInt();
			m_a_type = type;
		}
		else
		if (name==XML_PNAME_PARA6)
		{
			m_b = val.toInt();
			m_b_type = type;
		}
		else
		if (name==XML_PNAME_PARA7)
		{
			m_c = val.toInt();
			m_c_type = type;
		}
        else
        if (name==XML_PNAME_PARA8)
        {
            m_delay = val.toInt();
        }
		UpdateBaseMember();
		if (reader.isEndElement())
			reader.readNext();
	}
	else
		XmlSkipUnknownElement(reader);
	return true;
}
bool CodePos::XmlRead(QXmlStreamReader &reader)
{
	m_type = reader.attributes().value(XML_ATTR_TYPE).toString().toInt();
	m_axes = reader.attributes().value(XML_ATTR_AXES).toString().toInt();
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
bool CodePos::XmlWrite(QXmlStreamWriter &writer)
{
	writer.writeStartElement(XML_ELEMENT_CODE);
	writer.writeAttribute(XML_ATTR_NAME, XML_CNAME_POS);
	writer.writeAttribute(XML_ATTR_TYPE, QString("%1").arg(m_type));
	writer.writeAttribute(XML_ATTR_AXES, QString("%1").arg(m_axes));
    writer.writeAttribute(XML_ATTR_NOTE, m_note);
    writer.writeAttribute(XML_ATTR_FLAG, QString("%1").arg(m_flag));


		writer.writeStartElement(XML_ELEMENT_PARA);
		writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA1);
			writer.writeCharacters(QString("%1").arg(m_speed));
		writer.writeEndElement();

		if (m_axes & SRV_PAHOR)
		{
			writer.writeStartElement(XML_ELEMENT_PARA);
			writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA2);
            writer.writeAttribute(XML_ATTR_TYPE, QString("%1").arg(m_x_type));
			writer.writeCharacters(QString("%1").arg(m_x));
			writer.writeEndElement();
		}
		if (m_axes & SRV_PAVER)
		{
			writer.writeStartElement(XML_ELEMENT_PARA);
			writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA3);
            writer.writeAttribute(XML_ATTR_TYPE, QString("%1").arg(m_y_type));
			writer.writeCharacters(QString("%1").arg(m_y));
			writer.writeEndElement();
		}
		if (m_axes & SRV_TRV)
		{
			writer.writeStartElement(XML_ELEMENT_PARA);
			writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA4);
            writer.writeAttribute(XML_ATTR_TYPE, QString("%1").arg(m_z_type));
			writer.writeCharacters(QString("%1").arg(m_z));
			writer.writeEndElement();
		}
		if (m_axes & SRV_RAVER)
		{
			writer.writeStartElement(XML_ELEMENT_PARA);
			writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA5);
            writer.writeAttribute(XML_ATTR_TYPE, QString("%1").arg(m_a_type));
			writer.writeCharacters(QString("%1").arg(m_a));
			writer.writeEndElement();
		}
		if (m_axes & SRV_RAHOR)
		{
			writer.writeStartElement(XML_ELEMENT_PARA);
			writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA6);
            writer.writeAttribute(XML_ATTR_TYPE, QString("%1").arg(m_b_type));
			writer.writeCharacters(QString("%1").arg(m_b));
			writer.writeEndElement();
		}
		if (m_axes & SRV_EXT)
		{
			writer.writeStartElement(XML_ELEMENT_PARA);
			writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA7);
            writer.writeAttribute(XML_ATTR_TYPE, QString("%1").arg(m_c_type));
			writer.writeCharacters(QString("%1").arg(m_c));
			writer.writeEndElement();
		}

        writer.writeStartElement(XML_ELEMENT_PARA);
        writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA8);
            writer.writeCharacters(QString("%1").arg(m_delay));
        writer.writeEndElement();

	writer.writeEndElement();
	return true;
}
bool CodePos::Update(bool bSaveAndValidate)
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
			if (m_type != m_form->GetType())
			{
				m_type = m_form->GetType();
				change=true;
			}
			if (m_x != m_form->GetX())
			{
				m_x = m_form->GetX();
				change=true;
			}
			if (m_y != m_form->GetY())
			{
				m_y = m_form->GetY();
				change=true;
			}
			if (m_z != m_form->GetZ())
			{
				m_z = m_form->GetZ();
				change=true;
			}
			if (m_a != m_form->GetA())
			{
				m_a = m_form->GetA();
				change=true;
			}
			if (m_b != m_form->GetB())
			{
				m_b = m_form->GetB();
				change=true;
			}
			if (m_c != m_form->GetC())
			{
				m_c = m_form->GetC();
				change=true;
			}
			if (m_x_type != m_form->GetXType())
			{
				m_x_type = m_form->GetXType();
				change=true;
			}
			if (m_y_type != m_form->GetYType())
			{
				m_y_type = m_form->GetYType();
				change=true;
			}
			if (m_z_type != m_form->GetZType())
			{
				m_z_type = m_form->GetZType();
				change=true;
			}
			if (m_a_type != m_form->GetAType())
			{
				m_a_type = m_form->GetAType();
				change=true;
			}
			if (m_b_type != m_form->GetBType())
			{
				m_b_type = m_form->GetBType();
				change=true;
			}
			if (m_c_type != m_form->GetCType())
			{
				m_c_type = m_form->GetCType();
				change=true;
			}
            if (m_delay != m_form->GetDelay())
            {
                m_delay = m_form->GetDelay();
                change=true;
            }
			if (change) UpdateBaseMember();
			return change;
		}
		else
		{
			m_form->SetSpeed(m_speed);
			m_form->SetAxes(m_axes);
			m_form->SetType(m_type);
			m_form->SetX(m_x, m_x_type);
			m_form->SetY(m_y, m_y_type);
			m_form->SetZ(m_z, m_z_type);
			m_form->SetA(m_a, m_a_type);
			m_form->SetB(m_b, m_b_type);
			m_form->SetC(m_c, m_c_type);
            m_form->SetDelay(m_delay);
            m_form->UpdateWidgetState();
		}
	}
	return false;
}

bool CodePos::IsModified()
{
	if (m_form)
	{
		if ((m_speed != m_form->GetSpeed())||
            (m_delay != m_form->GetDelay())||
			(m_axes != m_form->GetAxes())||
			(m_x != m_form->GetX())||
			(m_y != m_form->GetY())||
			(m_z != m_form->GetZ())||
			(m_a != m_form->GetA())||
			(m_b != m_form->GetB())||
			(m_c != m_form->GetC())||
			(m_x_type != m_form->GetXType())||
			(m_y_type != m_form->GetYType())||
			(m_z_type != m_form->GetZType())||
			(m_a_type != m_form->GetAType())||
			(m_b_type != m_form->GetBType())||
			(m_c_type != m_form->GetCType()))
			return true;
	}
    return XmlModelItem::IsModified();
}


bool CodePos::GenerateCode(quint16* code, quint32 *para, quint8 other)
{
	int x = m_x, y = m_y, z = m_z, a = m_a, b = m_b, c = m_c;
	QSettings settings(XPAD_SETTING_FILE, QSettings::IniFormat);
	switch (m_x_type)
	{
	case POS_TYPE_CAT:
		x = settings.value(XPAD_SET_PAHORCAT, 0).toDouble();
		break;
	case POS_TYPE_REL:
		x = settings.value(XPAD_SET_PAHORREL, 0).toDouble();
		break;
	case POS_TYPE_WAIT:
		x = settings.value(XPAD_SET_PAHORWAIT, 0).toDouble();
		break;
	}
	switch (m_y_type)
	{
	case POS_TYPE_CAT:
		y = settings.value(XPAD_SET_PAVERCAT, 0).toDouble();
		break;
	case POS_TYPE_REL:
		y = settings.value(XPAD_SET_PAVERREL, 0).toDouble();
		break;
	case POS_TYPE_WAIT:
		y = settings.value(XPAD_SET_PAVERWAIT, 0).toDouble();
		break;
	}
	switch (m_z_type)
	{
	case POS_TYPE_CAT:
		z = settings.value(XPAD_SET_TRVCATPOS, 0).toDouble();
		break;
	case POS_TYPE_REL:
		z = settings.value(XPAD_SET_TRVRELPOS, 0).toDouble();
		break;
	case POS_TYPE_WAIT:
		z = settings.value(XPAD_SET_TRVWAIT, 0).toDouble();
		break;
	}
	switch (m_b_type)
	{
	case POS_TYPE_CAT:
		b = settings.value(XPAD_SET_RAHORCAT, 0).toDouble();
		break;
	case POS_TYPE_REL:
		b = settings.value(XPAD_SET_RAHORREL, 0).toDouble();
		break;
	case POS_TYPE_WAIT:
		b = settings.value(XPAD_SET_RAHORWAIT, 0).toDouble();
		break;
	}
	switch (m_a_type)
	{
	case POS_TYPE_CAT:
		a = settings.value(XPAD_SET_RAVERCAT, 0).toDouble();
		break;
	case POS_TYPE_REL:
		a = settings.value(XPAD_SET_RAVERREL, 0).toDouble();
		break;
	case POS_TYPE_WAIT:
		a = settings.value(XPAD_SET_RAVERWAIT, 0).toDouble();
		break;
	}
	switch (m_c_type)
	{
	case POS_TYPE_CAT:
		c = settings.value(XPAD_SET_EXTCAT, 0).toDouble();
		break;
	case POS_TYPE_REL:
		c = settings.value(XPAD_SET_EXTREL, 0).toDouble();
		break;
	case POS_TYPE_WAIT:
		c = settings.value(XPAD_SET_EXTWAIT, 0).toDouble();
		break;
	}

	quint32 relSpd = CMBProtocol::GetSrvSpeed();
	relSpd = qRound((double)(m_speed * relSpd) / 100.0);
	relSpd = (relSpd == 0 ? 1 : relSpd);
    code[0] = CODE_POS | (((quint16)m_flag) << 8);
	para[0] = (m_axes & 0x3F);
	para[0] <<= 1;
	para[0] |= (m_type & 1);
	para[0] <<= 7;
	para[0] |= (relSpd & 0x7F);
    para[0] |= ((quint32)(m_delay&0x3FF) << 16);
    if ((m_x_type == POS_TYPE_VAR) || (m_y_type == POS_TYPE_VAR) || (m_z_type == POS_TYPE_VAR) || (m_a_type == POS_TYPE_VAR) || (m_b_type == POS_TYPE_VAR) || (m_c_type == POS_TYPE_VAR))
        code[1] = CODE_VAR | (((quint16)m_flag) << 8);
    else
    code[1] = CODE_CONST | (((quint16)m_flag) << 8);
    if (m_axes&(1<<AXES_IDX_Y))
	{
		para[1] = y;
	}
	else
    if (m_axes&(1<<AXES_IDX_Z))
	{
		para[1] = z;
	}
	else
    if (m_axes&(1<<AXES_IDX_X))
	{
		para[1] = x;
	}
	else
    if (m_axes&(1<<AXES_IDX_A))
	{
		para[1] = a;
	}
	else
    if (m_axes&(1<<AXES_IDX_B))
	{
		para[1] = b;
	}
	else
    //if (m_axes&(1<<AXES_IDX_C))
	{
		para[1] = c;
	}
	return true;
}

void CodePos::UpdateBaseMember()
{
	QString type;

	if (m_type)
		type = QString(tr("相对定位"));
	else
		type = QString(tr("绝对定位"));
    if (m_axes&(1<<AXIS_IDX_PVER))
	{
		if (m_type)
			m_icon = QIcon(":/img/action/PaVerRel.png");
		else
			m_icon = QIcon(":/img/action/PaVerAbs.png");
		switch(m_y_type)
		{
		case POS_TYPE_CAT:
            m_name = type + QString("[") + GetServoName(AXIS_IDX_PVER) + QString("]") + QString(tr(" 取物点，速度")) + QString("%1%").arg(m_speed) + QString(tr("  时间")) + QString("%1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
			break;
		case POS_TYPE_REL:
            m_name = type + QString("[") + GetServoName(AXIS_IDX_PVER) + QString("]") + QString(tr(" 置物点，速度")) + QString("%1%").arg(m_speed) + QString(tr("  时间")) + QString("%1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
			break;
		case POS_TYPE_WAIT:
            m_name = type + QString("[") + GetServoName(AXIS_IDX_PVER) + QString("]") + QString(tr(" 待机点，速度")) + QString("%1%").arg(m_speed) + QString(tr("  时间")) + QString("%1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
			break;
        case POS_TYPE_POINT:
            m_name = type + tr("[%1] %2mm 速度%3%").arg(GetServoName(AXIS_IDX_PVER)).arg(m_y / 100.0).arg(m_speed) + QString(tr("  时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
            break;
        case POS_TYPE_VAR:
            m_name = type + tr("[%1] %2 速度%3%").arg(GetServoName(AXIS_IDX_PVER)).arg(xStringResource::GetVarName(VAR_TYPE_USR | m_y)).arg(m_speed) + QString(tr("  时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
			break;
		}
	}
    else if (m_axes&(1<<AXIS_IDX_TRV))
	{
		if (m_type)
			m_icon = QIcon(":/img/action/TrvRel.png");
		else
			m_icon = QIcon(":/img/action/TrvAbs.png");
		switch(m_z_type)
		{
		case POS_TYPE_CAT:
            m_name = type + QString("[") + GetServoName(AXIS_IDX_TRV) + QString("]") + QString(tr(" 取物点，速度")) + QString("%1%").arg(m_speed) + QString(tr("  时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
			break;
		case POS_TYPE_REL:
            m_name = type + QString("[") + GetServoName(AXIS_IDX_TRV) + QString("]") + QString(tr(" 置物点，速度")) + QString("%1%").arg(m_speed) + QString(tr("  时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
			break;
		case POS_TYPE_WAIT:
            m_name = type + QString("[") + GetServoName(AXIS_IDX_TRV) + QString("]") + QString(tr(" 待机点，速度")) + QString("%1%").arg(m_speed) + QString(tr("  时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
			break;
        case POS_TYPE_POINT:
            m_name = type + tr("[%1] %2mm 速度%3%").arg(GetServoName(AXIS_IDX_TRV)).arg(m_z / 100.0).arg(m_speed) + QString(tr("  时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
			break;
        case POS_TYPE_VAR:
            m_name = type + tr("[%1] %2 速度%3%").arg(GetServoName(AXIS_IDX_TRV)).arg(xStringResource::GetVarName(VAR_TYPE_USR | m_z)).arg(m_speed) + QString(tr("  时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
            break;
		}
	}
    else if (m_axes&(1<<AXIS_IDX_PHOR))
	{
		if (m_type)
			m_icon = QIcon(":/img/action/PaHorRel.png");
		else
			m_icon = QIcon(":/img/action/PaHorAbs.png");
//		m_name = type + QString("["SRV_ALIAS_PHOR"]") + QString(" %1").arg(((double)m_x)/(1000.0/TIME_BASE)) + QString(tr("mm ")) + QString(tr("速度")) + QString(" %1%").arg(m_speed);
		switch(m_x_type)
		{
		case POS_TYPE_CAT:
            m_name = type + QString("[") + GetServoName(AXIS_IDX_PHOR) + QString("]") + QString(tr(" 取物点，速度")) + QString("%1%").arg(m_speed) + QString(tr("  时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
			break;
		case POS_TYPE_REL:
            m_name = type + QString("[") + GetServoName(AXIS_IDX_PHOR) + QString("]") + QString(tr(" 置物点，速度")) + QString("%1%").arg(m_speed) + QString(tr("  时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
			break;
		case POS_TYPE_WAIT:
            m_name = type + QString("[") + GetServoName(AXIS_IDX_PHOR) + QString("]") + QString(tr(" 待机点，速度")) + QString("%1%").arg(m_speed) + QString(tr("  时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
			break;
        case POS_TYPE_POINT:
            m_name = type + tr("[%1] %2mm 速度%3%").arg(GetServoName(AXIS_IDX_PHOR)).arg(m_x / 100.0).arg(m_speed) + QString(tr("  时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
			break;
        case POS_TYPE_VAR:
            m_name = type + tr("[%1] %2 速度%3%").arg(GetServoName(AXIS_IDX_PHOR)).arg(xStringResource::GetVarName(VAR_TYPE_USR | m_x)).arg(m_speed) + QString(tr("  时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
            break;
		}
	}
    else if (m_axes&(1<<AXIS_IDX_RVER))
	{
		if (m_type)
			m_icon = QIcon(":/img/action/RaVerRel.png");
		else
			m_icon = QIcon(":/img/action/RaVerAbs.png");
//		m_name = type + QString("["SRV_ALIAS_RVER"]") + QString(" %1").arg(((double)m_a)/(1000.0/TIME_BASE)) + QString(tr("mm ")) + QString(tr("速度")) + QString(" %1%").arg(m_speed);
		switch(m_a_type)
		{
		case POS_TYPE_CAT:
            m_name = type + QString("[") + GetServoName(AXIS_IDX_RVER) + QString("]") + QString(tr(" 取物点，速度")) + QString("%1%").arg(m_speed) + QString(tr("  时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
			break;
		case POS_TYPE_REL:
            m_name = type + QString("[") + GetServoName(AXIS_IDX_RVER) + QString("]") + QString(tr(" 置物点，速度")) + QString("%1%").arg(m_speed) + QString(tr("  时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
			break;
		case POS_TYPE_WAIT:
            m_name = type + QString("[") + GetServoName(AXIS_IDX_RVER) + QString("]") + QString(tr(" 待机点，速度")) + QString("%1%").arg(m_speed) + QString(tr("  时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
			break;
        case POS_TYPE_POINT:
            m_name = type + tr("[%1] %2mm 速度%3%").arg(GetServoName(AXIS_IDX_RVER)).arg(m_a / 100.0).arg(m_speed) + QString(tr("  时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
			break;
        case POS_TYPE_VAR:
            m_name = type + tr("[%1] %2 速度%3%").arg(GetServoName(AXIS_IDX_RVER)).arg(xStringResource::GetVarName(VAR_TYPE_USR | m_a)).arg(m_speed) + QString(tr("  时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
            break;
		}
	}
    else if (m_axes&(1<<AXIS_IDX_RHOR))
	{
		if (m_type)
			m_icon = QIcon(":/img/action/RaHorRel.png");
		else
			m_icon = QIcon(":/img/action/RaHorAbs.png");
//		m_name = type + QString("["SRV_ALIAS_RHOR"]") + QString(" %1").arg(((double)m_b)/(1000.0/TIME_BASE)) + QString(tr("mm ")) + QString(tr("速度")) + QString(" %1%").arg(m_speed);
		switch(m_b_type)
		{
		case POS_TYPE_CAT:
            m_name = type + QString("[") + GetServoName(AXIS_IDX_RHOR) + QString("]") + QString(tr(" 取物点，速度")) + QString("%1%").arg(m_speed) + QString(tr("  时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
			break;
		case POS_TYPE_REL:
            m_name = type + QString("[") + GetServoName(AXIS_IDX_RHOR) + QString("]") + QString(tr(" 置物点，速度")) + QString("%1%").arg(m_speed) + QString(tr("  时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
			break;
		case POS_TYPE_WAIT:
            m_name = type + QString("[") + GetServoName(AXIS_IDX_RHOR) + QString("]") + QString(tr(" 待机点，速度")) + QString("%1%").arg(m_speed) + QString(tr("  时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
			break;
        case POS_TYPE_POINT:
            m_name = type + tr("[%1] %2mm 速度%3%").arg(GetServoName(AXIS_IDX_RHOR)).arg(m_b / 100.0).arg(m_speed) + QString(tr("  时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
			break;
        case POS_TYPE_VAR:
            m_name = type + tr("[%1] %2 速度%3%").arg(GetServoName(AXIS_IDX_RHOR)).arg(xStringResource::GetVarName(VAR_TYPE_USR | m_b)).arg(m_speed) + QString(tr("  时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
            break;
		}
	}
	else
	{
		if (m_type)
			m_icon = QIcon(":/img/action/ExtRel.png");
		else
			m_icon = QIcon(":/img/action/ExtAbs.png");
//		m_name = type + QString("["SRV_ALIAS_EXTE"]") + QString(" %1").arg(((double)m_c)/(1000.0/TIME_BASE)) + QString(tr("mm ")) + QString(tr("速度")) + QString(" %1%").arg(m_speed);
		switch(m_c_type)
		{
		case POS_TYPE_CAT:
            m_name = type + QString("[") + GetServoName(AXIS_IDX_EXT) + QString("]") + QString(tr(" 取物点，速度")) + QString("%1%").arg(m_speed) + QString(tr("  时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
			break;
		case POS_TYPE_REL:
            m_name = type + QString("[") + GetServoName(AXIS_IDX_EXT) + QString("]") + QString(tr(" 置物点，速度")) + QString("%1%").arg(m_speed) + QString(tr("  时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
			break;
		case POS_TYPE_WAIT:
            m_name = type + QString("[") + GetServoName(AXIS_IDX_EXT) + QString("]") + QString(tr(" 待机点，速度")) + QString("%1%").arg(m_speed) + QString(tr("  时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
			break;
        case POS_TYPE_POINT:
            m_name = type + tr("[%1] %2mm 速度%3%").arg(GetServoName(AXIS_IDX_EXT)).arg(m_c / 100.0).arg(m_speed) + QString(tr("  时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
			break;
        case POS_TYPE_VAR:
            m_name = type + tr("[%1] %2 速度%3%").arg(GetServoName(AXIS_IDX_EXT)).arg(xStringResource::GetVarName(VAR_TYPE_USR | m_c)).arg(m_speed) + QString(tr("  时间")) + QString(" %1").arg(((double)m_delay)/(1000.0/TIME_BASE)) + QString(tr("秒"));
            break;
		}
	}
}
