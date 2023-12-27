#include "xconfig.h"
#include "formactif.h"
#include "codeif.h"
#include "xstringresource.h"

CodeIf::CodeIf(QWidget *form, int type) : XmlModelItem(QIcon(":/img/action/If.png"), form)
{
	m_timeout = 0;
	m_code = CODE_IF;
	m_form = (FormActIf*)form;
	m_var1 = VAR_TYPE_USR;
	m_para1 = 0;
	m_para1_type = CODE_CONST;
	m_type = type;
    UpdateBaseMember();
}

bool CodeIf::XmlReadPara(QXmlStreamReader &reader)
{
	QString name = reader.attributes().value(XML_ATTR_NAME).toString();
	if (name==XML_PNAME_PARA1)
	{
		QString val = reader.readElementText();
		m_var1 = val.toInt();
		UpdateBaseMember();
		if (reader.isEndElement())
			reader.readNext();
	}
	else
	if (name==XML_PNAME_PARA2)
	{
		QString type = reader.attributes().value(XML_ATTR_TYPE).toString();
		m_para1_type = CODE_CONST;
		if (type==XML_TYPE_VAR)
			m_para1_type = CODE_VAR;
		QString val = reader.readElementText();
		m_para1 = val.toInt();
		UpdateBaseMember();
		if (reader.isEndElement())
			reader.readNext();
	}
	else
    if (name==XML_PNAME_PARA3)
    {
        QString val = reader.readElementText();
        m_timeout = val.toInt();
        UpdateBaseMember();
        if (reader.isEndElement())
            reader.readNext();
    }
	else
		XmlSkipUnknownElement(reader);
	return true;
}
bool CodeIf::XmlRead(QXmlStreamReader &reader)
{
	m_type = reader.attributes().value(XML_ATTR_TYPE).toString().toInt();
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
bool CodeIf::XmlWrite(QXmlStreamWriter &writer)
{
	writer.writeStartElement(XML_ELEMENT_CODE);
	writer.writeAttribute(XML_ATTR_NAME, XML_CNAME_IF);
	writer.writeAttribute(XML_ATTR_TYPE, QString("%1").arg(m_type));
    writer.writeAttribute(XML_ATTR_NOTE, m_note);
    writer.writeAttribute(XML_ATTR_FLAG, QString("%1").arg(m_flag));

		writer.writeStartElement(XML_ELEMENT_PARA);
		writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA1);
			writer.writeCharacters(QString("%1").arg(m_var1));
		writer.writeEndElement();

		if (m_type!=IF_TYPE_DIR)
		{
			writer.writeStartElement(XML_ELEMENT_PARA);
			writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA2);
			if (m_para1_type==CODE_CONST)
				writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_CONST);
			else
				writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_VAR);
				writer.writeCharacters(QString("%1").arg(m_para1));
			writer.writeEndElement();
		}

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA3);
    writer.writeCharacters(QString("%1").arg(m_timeout));
    writer.writeEndElement();

	writer.writeEndElement();
	return true;
}
bool CodeIf::Update(bool bSaveAndValidate)
{
	if (m_form)
	{
		if (bSaveAndValidate)
		{
			bool change = false;
			if (m_var1!=m_form->GetVar())
			{
				m_var1 = m_form->GetVar();
				change = true;
			}
			if (m_type != m_form->GetType())
			{
				m_type = m_form->GetType();
				change = true;
			}
			if (m_timeout != m_form->GetTimeout())
			{
				m_timeout = m_form->GetTimeout();
				change = true;
			}
            bool isconst;
            if (m_para1!=m_form->GetPara(isconst))
			{
                m_para1 = m_form->GetPara(isconst);
				change = true;
			}
            if ((m_para1_type==CODE_CONST) != isconst)
			{
                if (isconst)
                    m_para1_type = CODE_CONST;
                else
                    m_para1_type = CODE_VAR;

				change = true;
			}
			if (change) UpdateBaseMember();
			return change;
		}
		else
		{
			m_form->SetTimeout(m_timeout);
			m_form->SetType(m_type);
            //m_form->SetParaType(m_para1_type);
            m_form->SetPara(m_para1, (m_para1_type==CODE_CONST));
			m_form->SetVar(m_var1);
			m_form->UpdateWidgetState();
		}
	}
	return false;
}
bool CodeIf::GenerateCode(quint16* code, quint32 *para, quint8 other)
{
    code[0] = CODE_IF | (((quint16)m_flag) << 8);
	para[0] = m_timeout;
	para[0] <<= 16;
    para[0] |= ((m_type<<12)&0xF000);
	para[0] |= m_var1&0xFFF;
	if ((m_type&(0xF))!=IF_TYPE_DIR)
	{
		code[1] = m_para1_type;
		para[1] = m_para1;
	}
	return true;
}
void CodeIf::UpdateBaseMember()
{
	m_codes = 2;
	QString para;
	if (m_para1_type==CODE_CONST)
		para = QString("%1").arg(m_para1);
	else
        para = QString(tr("变量[")) + xStringResource::GetVarName(m_para1) + QString(("]"));
	switch(m_type)
	{
	case IF_TYPE_GT://		0x20	//>
		m_name = QString(tr("如果变量[")) + xStringResource::GetVarName(m_var1) + QString(tr("] ＞ ")) + para;
		break;
	case IF_TYPE_LT://		0x21	//<
		m_name = QString(tr("如果变量[")) + xStringResource::GetVarName(m_var1) + QString(tr("] ＜ ")) + para;
		break;
	case IF_TYPE_GE://		0x22	//>=
		m_name = QString(tr("如果变量[")) + xStringResource::GetVarName(m_var1) + QString(tr("] ≥ ")) + para;
		break;
	case IF_TYPE_LE://		0x23	//<=
		m_name = QString(tr("如果变量[")) + xStringResource::GetVarName(m_var1) + QString(tr("] ≤ ")) + para;
		break;
	case IF_TYPE_EQ://		0x24	//==
		m_name = QString(tr("如果变量[")) + xStringResource::GetVarName(m_var1) + QString(tr("] ＝ ")) + para;
		break;
	case IF_TYPE_NE://		0x25	//!=
		m_name = QString(tr("如果变量[")) + xStringResource::GetVarName(m_var1) + QString(tr("] ≠ ")) + para;
		break;
	default:// IF_TYPE_DIR		0x26	//直接
		m_codes = 1;
		m_name = QString(tr("如果变量[")) + xStringResource::GetVarName(m_var1) + QString(tr("] 有效"));
		break;
	}
	if (m_timeout)
		m_name += QString(tr("  超时")) + QString(" %1").arg(((double)m_timeout)/(1000.0/TIME_BASE)) + QString(tr("秒"));
}
bool CodeIf::IsModified()
{
	if (m_form)
	{
        bool isconst;
        int para = m_form->GetPara(isconst);
		if ((m_var1 != m_form->GetVar())||
			(m_type != m_form->GetType())||
			(m_timeout != m_form->GetTimeout())||
            (m_para1 != para)||
            ((m_para1_type==CODE_CONST) != isconst))
			return true;
	}
	return XmlModelItem::IsModified();
}
void CodeIf::SetUserVar(quint16 var, int idx)
{
    if (idx == 1)
    {
        if (m_para1_type == CODE_VAR)
            m_para1 = var;
    }
    else
        m_var1 = var;
}

quint16 CodeIf::GetUserVar(int idx)
{
    if (idx == 1)
    {
        if (m_para1_type == CODE_VAR)
        {
            if ((m_para1&MASK_VAR_TYPE) == VAR_TYPE_USR)
                return m_para1;
            else
                return 0;
        }
        else
            return 0;
    }
    else
    {
        if ((m_var1&MASK_VAR_TYPE) == VAR_TYPE_USR)
            return m_var1;
        else
            return 0;
    }
}

