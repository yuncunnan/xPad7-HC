#include "xconfig.h"
#include "xmlmodelitemoption.h"


XmlModelItemOption::XmlModelItemOption(QString nameen, QString namedis, QObject *parent) : QObject(parent)
{
    m_name_enable = nameen;
    m_name_disable = namedis;
    m_enable = true;
    RemoveAll();
}

bool XmlModelItemOption::XmlRead(QXmlStreamReader &reader)
{
    RemoveAll();
    m_name_enable = reader.attributes().value(XML_ATTR_NAMEEN).toString();
    m_name_disable = reader.attributes().value(XML_ATTR_NAMEDIS).toString();
    m_enable = reader.attributes().value(XML_ATTR_ENABLE).toString().toInt();
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
            if (reader.name()==XML_ELEMENT_LINE)
            {
                int line = reader.attributes().value(XML_ATTR_NUM).toString().toInt();
                m_linelist.append(line);
                while (!reader.isEndElement()) reader.readNext();
                reader.readNext();
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

bool XmlModelItemOption::XmlWrite(QXmlStreamWriter &writer)
{
    int i;
    writer.writeStartElement(XML_ELEMENT_ITEM);
    writer.writeAttribute(XML_ATTR_NAMEEN, m_name_enable);
    writer.writeAttribute(XML_ATTR_NAMEDIS, m_name_disable);
    writer.writeAttribute(XML_ATTR_ENABLE, QString("%1").arg(m_enable));

    for (i=0; i<m_linelist.count(); i++)
    {
        writer.writeStartElement(XML_ELEMENT_LINE);
        writer.writeAttribute(XML_ATTR_NUM, QString("%1").arg(m_linelist.at(i)));
        writer.writeEndElement();
    }

    writer.writeEndElement();
    return true;
}

void XmlModelItemOption::XmlSkipUnknownElement(QXmlStreamReader &reader)
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

bool XmlModelItemOption::IsInclude(int line)    //查询是否包含本行号
{
    int i;
    for (i=0; i<m_linelist.count(); i++)
    {
        if (m_linelist.at(i)==line) return true;
    }
    return false;
}

void XmlModelItemOption::InsertLine(int line)
{
    m_linelist.removeAll(line);
    m_linelist.append(line);
}

void XmlModelItemOption::RemoveLine(int line)
{
    m_linelist.removeAll(line);
}

void XmlModelItemOption::RemoveAll(void)
{
    m_linelist.erase(m_linelist.begin(), m_linelist.end());
}

void XmlModelItemOption::RemoveCodeAdjust(int codepos)
{
    int i;
    m_linelist.removeAll(codepos);
    for (i=0; i<m_linelist.count(); i++)
    {
        if (m_linelist.at(i)>codepos) m_linelist[i]--;
    }
}

void XmlModelItemOption::InsertCodeAdjust(int codepos)
{
    int i;
    for (i=0; i<m_linelist.count(); i++)
    {
        if (m_linelist.at(i)>=codepos) m_linelist[i]++;
    }
}

void XmlModelItemOption::MoveCodeAdjust(int from, int to)
{
    int i;
    for (i=0; i<m_linelist.count(); i++)
    {
        if (m_linelist.at(i)==from) m_linelist[i] = to;
        else
        if (m_linelist.at(i)==to) m_linelist[i] = from;
    }
}
