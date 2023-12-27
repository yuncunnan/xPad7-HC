#include "formactoperate.h"
#include "codeoperator.h"
#include "xstringresource.h"

CodeOperator::CodeOperator(QWidget *form, int type) : XmlModelItem(QIcon(), form)
{
	m_form = (FormActOperate*)form;
	m_var1 = VAR_TYPE_USR;
	m_type = type;
	m_para = 1;
	m_para_type = CODE_CONST;
    m_codes = 2;
    m_code = CODE_OPR;
    UpdateBaseMember();
}

bool CodeOperator::XmlReadPara(QXmlStreamReader &reader)
{
	QString name = reader.attributes().value(XML_ATTR_NAME).toString();
	if (name==XML_PNAME_PARA2)
	{
		QString type = reader.attributes().value(XML_ATTR_TYPE).toString();
		m_para_type = CODE_CONST;
		if (type==XML_TYPE_VAR)
			m_para_type = CODE_VAR;
	}
	if ((name==XML_PNAME_PARA1)||
        (name==XML_PNAME_PARA2))
    {
		QString val = reader.readElementText();
		if (name==XML_PNAME_PARA1) m_var1 = val.toInt();
        if (name==XML_PNAME_PARA2) m_para = val.toInt();
        UpdateBaseMember();
		if (reader.isEndElement())
			reader.readNext();
	}
	else
		XmlSkipUnknownElement(reader);
	return true;
}

bool CodeOperator::XmlRead(QXmlStreamReader &reader)
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
bool CodeOperator::XmlWrite(QXmlStreamWriter &writer)
{
	writer.writeStartElement(XML_ELEMENT_CODE);
	writer.writeAttribute(XML_ATTR_NAME, XML_CNAME_OPR);
	writer.writeAttribute(XML_ATTR_TYPE, QString("%1").arg(m_type));
    writer.writeAttribute(XML_ATTR_NOTE, m_note);
    writer.writeAttribute(XML_ATTR_FLAG, QString("%1").arg(m_flag));


		writer.writeStartElement(XML_ELEMENT_PARA);
		writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA1);
			writer.writeCharacters(QString("%1").arg(m_var1));
		writer.writeEndElement();

		writer.writeStartElement(XML_ELEMENT_PARA);
		writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA2);
		if (m_para_type==CODE_CONST)
			writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_CONST);
		else
			writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_VAR);
			writer.writeCharacters(QString("%1").arg(m_para));
        writer.writeEndElement();

	writer.writeEndElement();
	return true;
}
bool CodeOperator::Update(bool bSaveAndValidate)
{
	bool change = false;
	if (m_form)
	{
		if (bSaveAndValidate)
		{
			if (m_var1 != m_form->GetVar())
			{
				m_var1 = m_form->GetVar();
				change = true;
			}
			if (m_type != m_form->GetType())
			{
				m_type = m_form->GetType();
				change = true;
			}
			if (m_para != m_form->GetPara())
			{
				m_para = m_form->GetPara();
				change = true;
			}
			if (change) UpdateBaseMember();
			return change;
		}
		else
		{
			m_form->SetVar(m_var1);
			m_form->SetType(m_type);
			m_form->SetPara(m_para);
			m_form->UpdateWidgetState();
		}
	}
	return false;
}

void CodeOperator::UpdateBaseMember()
{
	QString opr;
	QString para;
    if (m_type==OPR_TYPE_ADD)
	{
		m_icon = QIcon(":/img/action/VarPlus.png");
		opr = QString(tr(" ＋ "));
	}
    else if (m_type==OPR_TYPE_SUB)
	{
		m_icon = QIcon(":/img/action/VarSub.png");
		opr = QString(tr(" － "));
	}
    else if (m_type==OPR_TYPE_MUL)
    {
        m_icon = QIcon(":/img/action/VarMul.png");
		opr = QString(tr(" × "));
    }
    else if (m_type==OPR_TYPE_MOD)
    {
        m_icon = QIcon(":/img/action/VarDiv.png");
		opr = QString(tr(" % "));
    }
    else if (m_type==OPR_TYPE_ASSIGN)
    {
        m_icon = QIcon(":/img/action/VarAssign.png");
		opr = QString(tr(" = "));
    }
    else
	{
		m_icon = QIcon(":/img/action/VarDiv.png");
		opr = QString(tr(" ÷ "));
	}
	if (m_para_type==CODE_CONST)
	{
		para = QString("%1").arg(m_para);
	}
	else
	{
        para = QString(tr("变量[")) + xStringResource::GetVarName(m_para) + QString(("]"));
	}
	m_name = QString(tr("用户变量[")) + xStringResource::GetVarName(m_var1) + QString(("]")) + (opr) + para;
}

bool CodeOperator::IsModified()
{
	if (m_form)
	{
		if ((m_var1 != m_form->GetVar())||
			(m_type != m_form->GetType())||
			(m_para != m_form->GetPara()))
			return true;
	}
	return XmlModelItem::IsModified();
}

bool CodeOperator::GenerateCode(quint16* code, quint32 *para, quint8 other)
{
    code[0] = m_code | (((quint16)m_flag) << 8);
    para[0] = m_var1 | (m_type<<16);
    code[1] = m_para_type | (((quint16)m_flag) << 8);//也可以是变量，界面上要修改
    para[1] = m_para;
	return true;
}
void CodeOperator::SetUserVar(quint16 var, int idx)
{
    m_var1 = var;
}

quint16 CodeOperator::GetUserVar(int idx)
{
    if ((m_var1 &MASK_VAR_TYPE) == VAR_TYPE_USR)
        return m_var1;
    return 0;
}
