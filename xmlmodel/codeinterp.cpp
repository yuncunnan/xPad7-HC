#include <QSettings>
#include "formactinterp.h"
#include "codeinterp.h"
#include "cmbprotocol.h"
#include "servoalias.h"

CodeInterp::CodeInterp(QWidget *form) :	XmlModelItem(QIcon(), form)
{
	m_code = CODE_INTERP;
	m_form = (FormActInterp*)form;
	m_axes = 7;
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
	UpdateBaseMember();
}

bool CodeInterp::XmlReadPara(QXmlStreamReader &reader)
{
	QString name = reader.attributes().value(XML_ATTR_NAME).toString();
	int type = reader.attributes().value(XML_ATTR_TYPE).toString().toInt();
	if ((name==XML_PNAME_PARA1)||
		(name==XML_PNAME_PARA2)||
		(name==XML_PNAME_PARA3)||
		(name==XML_PNAME_PARA4)||
		(name==XML_PNAME_PARA5)||
		(name==XML_PNAME_PARA6)||
		(name==XML_PNAME_PARA7))
	{
		QString val = reader.readElementText();
		if (name==XML_PNAME_PARA1)
		{
			m_speed = val.toInt();
		}
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
		UpdateBaseMember();
		if (reader.isEndElement())
			reader.readNext();
	}
	else
		XmlSkipUnknownElement(reader);
	return true;
}
bool CodeInterp::XmlRead(QXmlStreamReader &reader)
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
bool CodeInterp::XmlWrite(QXmlStreamWriter &writer)
{
	writer.writeStartElement(XML_ELEMENT_CODE);
	writer.writeAttribute(XML_ATTR_NAME, XML_CNAME_INTERP);
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
	writer.writeEndElement();
	return true;
}
bool CodeInterp::Update(bool bSaveAndValidate)
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
			if (change) UpdateBaseMember();
			return change;
		}
		else
		{
			m_form->SetSpeed(m_speed);
			m_form->SetAxes(m_axes);
			m_form->SetX(m_x, m_x_type);
			m_form->SetY(m_y, m_y_type);
			m_form->SetZ(m_z, m_z_type);
			m_form->SetA(m_a, m_a_type);
			m_form->SetB(m_b, m_b_type);
			m_form->SetC(m_c, m_c_type);
			m_form->UpdateWidgetState();
		}
	}
	return false;
}

bool CodeInterp::GenerateCode(quint16* code, quint32 *para, quint8 other)
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
	int i;
    code[0] = CODE_INTERP | (((quint16)m_flag) << 8);
	para[0] = (m_axes & 0x3F);
	para[0] <<= 1;
	para[0] |= (m_type & 1);
	para[0] <<= 7;
	para[0] |= (relSpd & 0x7F);
	i = 1;
    if (m_axes&(1<<AXES_IDX_X))
	{
        para[i] = x;
        if (m_x_type == POS_TYPE_VAR)
            code[i] = CODE_VAR | (((quint16)m_flag) << 8);
        else
        code[i] = CODE_CONST | (((quint16)m_flag) << 8);
		i++;
	}
    if (m_axes&(1<<AXES_IDX_Y))
	{
		para[i] = y;
        if (m_y_type == POS_TYPE_VAR)
            code[i] = CODE_VAR | (((quint16)m_flag) << 8);
        else
        code[i] = CODE_CONST | (((quint16)m_flag) << 8);
		i++;
	}
    if (m_axes&(1<<AXES_IDX_Z))
	{
		para[i] = z;
        if (m_z_type == POS_TYPE_VAR)
            code[i] = CODE_VAR | (((quint16)m_flag) << 8);
        else
        code[i] = CODE_CONST | (((quint16)m_flag) << 8);
		i++;
	}
    if (m_axes&(1<<AXES_IDX_A))
	{
		para[i] = a;
        if (m_a_type == POS_TYPE_VAR)
            code[i] = CODE_VAR | (((quint16)m_flag) << 8);
        else
        code[i] = CODE_CONST | (((quint16)m_flag) << 8);
		i++;
	}
    if (m_axes&(1<<AXES_IDX_B))
	{
		para[i] = b;
        if (m_b_type == POS_TYPE_VAR)
            code[i] = CODE_VAR | (((quint16)m_flag) << 8);
        else
        code[i] = CODE_CONST | (((quint16)m_flag) << 8);
		i++;
	}
    if (m_axes&(1<<AXES_IDX_C))
	{
		para[i] = c;
        if (m_c_type == POS_TYPE_VAR)
            code[i] = CODE_VAR | (((quint16)m_flag) << 8);
        else
        code[i] = CODE_CONST | (((quint16)m_flag) << 8);
		i++;
	}
	return true;
}

void CodeInterp::UpdateBaseMember()
{
	int first = 1;
	m_codes = 1;
	if (m_type)
	{
		m_name = QString(tr("相对插补["));
		m_icon = QIcon(":/img/action/IntPosRel.png");
	}
	else
	{
		m_name = QString(tr("绝对插补["));
		m_icon = QIcon(":/img/action/IntPosAbs.png");
	}
    if (m_axes&(1<<AXIS_IDX_PVER))
	{
		m_name += GetServoName(AXIS_IDX_PVER);
		m_codes++;
		first = 0;
	}
    if (m_axes&(1<<AXIS_IDX_TRV))
	{
        if (first==0) m_name += QString(("-"));
		m_name += GetServoName(AXIS_IDX_TRV);
		m_codes++;
		first = 0;
	}
    if (m_axes&(1<<AXIS_IDX_PHOR))
	{
        if (first==0) m_name += QString(("-"));
		m_name += GetServoName(AXIS_IDX_PHOR);
		m_codes++;
		first = 0;
	}
    if (m_axes&(1<<AXIS_IDX_RVER))
	{
        if (first==0) m_name += QString(("-"));
		m_name += GetServoName(AXIS_IDX_RVER);
		m_codes++;
		first = 0;
	}
    if (m_axes&(1<<AXIS_IDX_RHOR))
	{
		if (first==0) m_name += QString(tr("-"));
		m_name += GetServoName(AXIS_IDX_RHOR);
		m_codes++;
		first = 0;
	}
    if (m_axes&(1<<AXIS_IDX_EXT))
	{
		if (first==0) m_name += QString(tr("-"));
		m_codes++;
		m_name += GetServoName(AXIS_IDX_EXT);
	}
   m_name += QString(tr("] 速度 %1%").arg(m_speed));
}

bool CodeInterp::IsModified()
{
	if (m_form)
	{
		if ((m_speed != m_form->GetSpeed())||
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
