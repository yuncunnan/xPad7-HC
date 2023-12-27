#include "xconfig.h"
#include "xmlmodelvarinititem.h"
#include "xstringresource.h"

XmlModelVarInitItem::XmlModelVarInitItem(QObject *parent) :
    QObject(parent)
{
}

bool XmlModelVarInitItem::XmlRead(QXmlStreamReader &reader)
{

    if (reader.name()==XML_ELEMENT_VAR)
    {
        m_val = reader.attributes().value(XML_ATTR_VAL).toString().toUShort();
        m_type = reader.attributes().value(XML_ATTR_INQ).toString().toUShort();
        QString val = reader.readElementText();
        m_var = val.toUShort();
    }
    return true;
}

bool XmlModelVarInitItem::XmlWrite(QXmlStreamWriter &writer)
{
    writer.writeStartElement(XML_ELEMENT_VAR);
    writer.writeAttribute(XML_ATTR_VAL, QString("%1").arg(m_val));
    writer.writeAttribute(XML_ATTR_INQ, QString("%1").arg(m_type));
        writer.writeCharacters(QString("%1").arg(m_var));
    writer.writeEndElement();
    return true;
}

void XmlModelVarInitItem::XmlSkipUnknownElement(QXmlStreamReader &reader)
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

QString XmlModelVarInitItem::GetVarName()
{
    QString ret = xStringResource::GetVarName(m_var);
    return ret;
}
QString XmlModelVarInitItem::GetTypeName()
{
    if (m_type == 0)
        return tr("自动");
    if (m_type == 1)
        return tr("询问");
    return tr("从不");
}
quint8 XmlModelVarInitItem::GetType()
{
    if (m_type > TYPE_NEVER)
        m_type = TYPE_AUTO;
    return m_type;
}
