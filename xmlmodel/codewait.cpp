#include "xconfig.h"
#include "formactwait.h"
#include "codewait.h"
#include "xstringresource.h"
#include "cmbprotocol.h"

#define WAIT_TYPE_VALID		0//有效
#define WAIT_TYPE_INVALID	1//无效
#define WAIT_TYPE_GT		2//>
#define WAIT_TYPE_LT		3//<
#define WAIT_TYPE_NE		4//!=
#define WAIT_TYPE_EQ		5//==

CodeWait::CodeWait(QWidget *form) :	XmlModelItem(QIcon(":/img/action/Wait.png"), form)
{
	m_code = CODE_WAIT;
	m_form = (FormActWait*)form;
	m_var1 = EM1_VAR_X06;
    m_var2 = EM1_VAR_X06;
	m_timeout = 0;
	m_timeout_type = CODE_CONST;
    m_var2_isconst = 0;
    m_isoff = 0;
    m_validtime = 0;
    UpdateBaseMember();
}
bool CodeWait::XmlReadPara(QXmlStreamReader &reader)
{
	QString name = reader.attributes().value(XML_ATTR_NAME).toString();
    if (name==XML_PNAME_PARA2)
	{
		QString type = reader.attributes().value(XML_ATTR_TYPE).toString();
		m_timeout_type = CODE_CONST;
		if (type==XML_TYPE_VAR)
			m_timeout_type = CODE_VAR;
	}
    if (name==XML_PNAME_PARA3)
    {
        QString type = reader.attributes().value(XML_ATTR_TYPE).toString();
        m_var2_isconst = 1;
        if (type==XML_TYPE_VAR)
            m_var2_isconst = 0;
    }
	if ((name==XML_PNAME_PARA1)||
        (name==XML_PNAME_PARA2)||
        (name==XML_PNAME_PARA3)||
        (name==XML_PNAME_PARA4))
	{
		QString val = reader.readElementText();
		if (name==XML_PNAME_PARA1) m_var1 = val.toInt();
		if (name==XML_PNAME_PARA2) m_timeout = val.toInt();
        if (name==XML_PNAME_PARA3) m_var2 = val.toInt();
        if (name==XML_PNAME_PARA4) m_validtime = val.toInt();
		UpdateBaseMember();
		if (reader.isEndElement())
			reader.readNext();
	}
	else
		XmlSkipUnknownElement(reader);
	return true;
}
bool CodeWait::XmlRead(QXmlStreamReader &reader)
{
	m_isoff = reader.attributes().value(XML_ATTR_TYPE).toString().toInt();
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
bool CodeWait::XmlWrite(QXmlStreamWriter &writer)
{
	writer.writeStartElement(XML_ELEMENT_CODE);
	writer.writeAttribute(XML_ATTR_NAME, XML_CNAME_WAIT);
	writer.writeAttribute(XML_ATTR_TYPE, QString("%1").arg(m_isoff));
    writer.writeAttribute(XML_ATTR_NOTE, m_note);
    writer.writeAttribute(XML_ATTR_FLAG, QString("%1").arg(m_flag));

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA1);
        writer.writeCharacters(QString("%1").arg(m_var1));
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA2);
    if (m_timeout_type==CODE_CONST)
        writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_CONST);
    else
        writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_VAR);
        writer.writeCharacters(QString("%1").arg(m_timeout));
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA3);
    if (m_var2_isconst)
        writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_CONST);
    else
        writer.writeAttribute(XML_ATTR_TYPE, XML_TYPE_VAR);
        writer.writeCharacters(QString("%1").arg(m_var2));
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_PNAME_PARA4);
    writer.writeCharacters(QString("%1").arg(m_validtime));
    writer.writeEndElement();

	writer.writeEndElement();
	return true;
}
bool CodeWait::Update(bool bSaveAndValidate)
{
	if (m_form)
	{
		if (bSaveAndValidate)
		{
			bool change=false;
			if (m_var1 != m_form->GetVar())
			{
				m_var1 = m_form->GetVar();
				change=true;
			}
            bool isconst;
            if (m_var2 != m_form->GetVar2(isconst))
            {
                m_var2 = m_form->GetVar2(isconst);
                change=true;
            }
            if ((m_var2_isconst) != isconst)
            {
                if (isconst)
                    m_var2_isconst = 1;
                else
                    m_var2_isconst = 0;

                change = true;
            }
			if (m_timeout != m_form->GetTimeout())
			{
				m_timeout = m_form->GetTimeout();
				change=true;
			}
			if (m_isoff != m_form->GetInvalidSet())
			{
				m_isoff = m_form->GetInvalidSet();
				change=true;
			}
            if (m_validtime != m_form->GetTimevalid())
            {
                m_validtime = m_form->GetTimevalid();
                change = true;
            }
			if (change) UpdateBaseMember();
			return change;
		}
		else
		{
			m_form->SetVar(m_var1);
            m_form->SetVar2(m_var2, (m_var2_isconst));
			m_form->SetInvalidSet(m_isoff);
			m_form->SetTimeOut(m_timeout);
            m_form->SetTimevalid(m_validtime);
            m_form->UpdateWidgetState();
		}
	}
	return false;
}
//#if FACTORY == FA_GH
//bool CodeWait::GenerateCode(quint16* code, quint32 *para, quint8 other)
//{
//    code[0] = CODE_WAIT | (((quint16)m_flag) << 8);
//    para[0] = m_var1&0xFFF;
//    if (m_isoff)
//        para[0] |= 0x1000;
//    para[0] |= m_timeout<<16;
//    return true;
//}
//#else
bool CodeWait::GenerateCode(quint16* code, quint32 *para, quint8 other)
{
//    m_codes = 1;
    if(CMBProtocol::GetFunctions(SUB_FUN2_WAIT_VAR2))
    {
        code[0] = CODE_WAIT | (((quint16)m_flag) << 8);
        para[0] = m_var1&0xFFF;
        para[0] |= ((m_isoff&0xf)<<12);
        para[0] |= m_timeout<<16;
        if((m_isoff == WAIT_TYPE_GT)||(m_isoff == WAIT_TYPE_LT)||(m_isoff == WAIT_TYPE_NE)||(m_isoff == WAIT_TYPE_EQ))
        {
//            m_codes = 2;
            if(m_var2_isconst)
                code[1] = CODE_CONST;
            else
                code[1] = CODE_VAR;
            para[1] = m_var2;
        }
        else//有效。無效
        {
//            m_codes = 2;
            code[1] = CODE_CONST;
            para[1] = m_validtime;
        }
    }
    else
    {
        code[0] = CODE_WAIT | (((quint16)m_flag) << 8);
        para[0] = m_var1&0xFFF;
        if (m_isoff)
            para[0] |= 0x1000;
        para[0] |= m_timeout<<16;
    }
	return true;
}
//#endif

void CodeWait::UpdateBaseMember()
{
    if(CMBProtocol::GetFunctions(SUB_FUN2_WAIT_VAR2))
    {
            m_codes = 2;
    }
    else
        m_codes = 1;

//	if (m_isoff)
//		m_name = QString(tr("等待[")) + xStringResource::GetVarName(m_var1) + QString(tr("] 信号无效"));
//	else
//		m_name = QString(tr("等待[")) + xStringResource::GetVarName(m_var1) + QString(tr("] 信号有效"));
    QString para;
    if (m_var2_isconst)
        para = QString("%1").arg(m_var2);
    else
        para = QString(tr("[")) + xStringResource::GetVarName(m_var2) + QString(("]"));
    if(m_isoff==0)
        m_name = QString(tr("等待[")) + xStringResource::GetVarName(m_var1) + QString(tr("] 信号有效"));
    else if(m_isoff==1)
        m_name = QString(tr("等待[")) + xStringResource::GetVarName(m_var1) + QString(tr("] 信号无效"));
    else if(m_isoff==2)
        m_name = QString(tr("等待[")) + xStringResource::GetVarName(m_var1) + QString(tr("]>"))+ para;
    else if(m_isoff==3)
        m_name = QString(tr("等待[")) + xStringResource::GetVarName(m_var1) + QString(tr("]<"))+ para;
    else if(m_isoff==4)
        m_name = QString(tr("等待[")) + xStringResource::GetVarName(m_var1) + QString(tr("]!="))+ para;
    else if(m_isoff==5)
        m_name = QString(tr("等待[")) + xStringResource::GetVarName(m_var1) + QString(tr("]="))+ para;
    //if((m_isoff == WAIT_TYPE_GT)||(m_isoff == WAIT_TYPE_LT)||(m_isoff == WAIT_TYPE_NE)||(m_isoff == WAIT_TYPE_EQ))
    if(m_validtime)
    {
        m_name += QString("%1").arg(((double)m_validtime)/(1000.0/TIME_BASE)) + QString(tr("秒"));
    }
	if (m_timeout)
	{
		if (m_timeout_type==CODE_CONST)
            m_name += QString(tr(" 超时")) + QString("%1").arg(((double)m_timeout)/(1000.0/TIME_BASE)) + QString(tr("秒"));
		else
            m_name += QString(tr(" 超时变量[")) + xStringResource::GetVarName(m_var1) + QString(("]"));
	}   
}

bool CodeWait::IsModified()
{
	if (m_form)
	{
        if ((m_var1 != m_form->GetVar())||(m_timeout != m_form->GetTimeout())||(m_isoff != m_form->GetInvalidSet()) || m_validtime != m_form->GetTimevalid())
			return true;
	}
	return XmlModelItem::IsModified();
}
