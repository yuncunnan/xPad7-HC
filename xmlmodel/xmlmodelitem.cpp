#include "xconfig.h"
#include "xmlmodelitem.h"

XmlModelItem::XmlModelItem(QIcon icon, QWidget *widget, QString name, QString note, int codes, QObject *parent) :
    QObject(parent)
{
    m_code = -1;
    m_icon = icon;
    m_name = name;
    m_note = note;
    m_widget = widget;
    m_codes = codes;
    m_enable = true;
    m_flag = 0;
    m_linenum = 0;
}

bool XmlModelItem::XmlRead(QXmlStreamReader &reader)
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
        else
            XmlSkipUnknownElement(reader);
    }
    return true;
}

void XmlModelItem::XmlSkipUnknownElement(QXmlStreamReader &reader)
{
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
            XmlSkipUnknownElement(reader);
        }
        else
        {
            reader.readNext();
        }
    }
}

bool XmlModelItem::GenerateCode(quint16 *code, quint32* para, quint8 other)//生成最终的执行码（在MODBUS空间）
{
    code[0] = m_code;
    para[0] = 0;
    return true;
}

void XmlModelItem::ShowUI(bool show)
{
    if (m_widget)
    {
        if (show)
        {
            m_widget->show();
        }
        else
        {
            m_widget->hide();
        }
    }
}
//数据源别名接口
bool XmlModelItem::SetNote(QString note)
{
	if (m_note != note)
	{
		m_note = note;
		return true;
	}
	return false;
}

void XmlModelItem::SetUserVar(quint16 var, int idx)
{
}

quint16 XmlModelItem::GetUserVar(int idx)
{
    return 0;
}
