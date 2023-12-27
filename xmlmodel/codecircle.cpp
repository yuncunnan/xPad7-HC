#include "xconfig.h"
#include "formactcircle.h"
#include "codecircle.h"
#include "xstringresource.h"

CodeCircle::CodeCircle(QWidget *form) : XmlModelItem(QIcon(":/img/action/Circle.png"), form)
{
    m_form = (FormActCircle*)form;
    m_code = CODE_CIRCLE;
    m_codes = 3;
    m_dir = CIRCLE_CLOCKWIDE;
    m_radius = 100;
    m_speed = 50;
    m_begin = 0;
    m_end = 0;
    m_z = 0;
    m_y2 = 0;
    UpdateBaseMember();
}
bool CodeCircle::XmlReadPara(QXmlStreamReader &reader)
{
    QString name = reader.attributes().value(XML_ATTR_NAME).toString();
    if ((name==XML_ATTR_DIR)||
        (name==XML_ATTR_RADIUS)||
        (name==XML_ATTR_SPEED)||
        (name==XML_ATTR_BEGIN)||
        (name==XML_ATTR_ZPOINT)||
        (name==XML_ATTR_Y2POINT)||
        (name==XML_ATTR_END))
    {
        QString val = reader.readElementText();
        if (name==XML_ATTR_DIR) m_dir = val.toInt();
        if (name==XML_ATTR_RADIUS) m_radius = val.toInt();
        if (name==XML_ATTR_SPEED) m_speed = val.toInt();
        if (name==XML_ATTR_BEGIN) m_begin = val.toInt();
        if (name==XML_ATTR_END) m_end = val.toInt();
        if (name==XML_ATTR_ZPOINT) m_z = val.toInt();
        if (name==XML_ATTR_Y2POINT) m_y2 = val.toInt();
        UpdateBaseMember();
        if (reader.isEndElement())
            reader.readNext();    }
    else
        XmlSkipUnknownElement(reader);
    return true;
}

bool CodeCircle::XmlRead(QXmlStreamReader &reader)
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
bool CodeCircle::XmlWrite(QXmlStreamWriter &writer)
{
    writer.writeStartElement(XML_ELEMENT_CODE);
    writer.writeAttribute(XML_ATTR_NAME, XML_CNAME_CIRCLE);
    writer.writeAttribute(XML_ATTR_NOTE, m_note);
    writer.writeAttribute(XML_ATTR_FLAG, QString("%1").arg(m_flag));

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_ATTR_DIR);
    writer.writeCharacters(QString("%1").arg(m_dir));
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_ATTR_RADIUS);
    writer.writeCharacters(QString("%1").arg(m_radius));
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_ATTR_SPEED);
    writer.writeCharacters(QString("%1").arg(m_speed));
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_ATTR_BEGIN);
    writer.writeCharacters(QString("%1").arg(m_begin));
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_ATTR_END);
    writer.writeCharacters(QString("%1").arg(m_end));
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_ATTR_ZPOINT);
    writer.writeCharacters(QString("%1").arg(m_z));
    writer.writeEndElement();

    writer.writeStartElement(XML_ELEMENT_PARA);
    writer.writeAttribute(XML_ATTR_NAME, XML_ATTR_Y2POINT);
    writer.writeCharacters(QString("%1").arg(m_y2));
    writer.writeEndElement();

    writer.writeEndElement();
    return true;
}

bool CodeCircle::Update(bool bSaveAndValidate)
{
    if (m_form)
    {
        if (bSaveAndValidate)
        {
            bool change=false;
            if (m_dir != m_form->GetDir())
            {
                m_dir = m_form->GetDir();
                change=true;
            }
            if (m_radius != m_form->GetRadius())
            {
                m_radius = m_form->GetRadius();
                change=true;
            }
            if (m_speed != m_form->GetSpeed())
            {
                m_speed = m_form->GetSpeed();
                change=true;
            }
            if (m_begin != m_form->GetBegin())
            {
                m_begin = m_form->GetBegin();
                change=true;
            }
            if (m_end != m_form->GetEnd())
            {
                m_end = m_form->GetEnd();
                change=true;
            }
            if (m_z != m_form->GetZ())
            {
                m_z = m_form->GetZ();
                change=true;
            }
            if (m_y2 != m_form->GetY2())
            {
                m_y2 = m_form->GetY2();
                change=true;
            }
            if (change) UpdateBaseMember();
            return change;
        }
        else
        {
            m_form->SetDir(m_dir);
            m_form->SetRadius(m_radius);
            m_form->SetSpeed(m_speed);
            m_form->SetBegin(m_begin);
            m_form->SetEnd(m_end);
            m_form->SetZ(m_z);
            m_form->SetY2(m_y2);
            m_form->UpdateWidgetState();
        }
    }
    return false;
}

bool CodeCircle::GenerateCode(quint16* code, quint32 *para, quint8 other)
{
    code[0] = CODE_CIRCLE | (((quint16)m_flag) << 8);
    para[0] = m_radius;
    para[0] <<= 1;
    para[0] |= (m_dir & 1);
    para[0] <<= 7;
    para[0] |= (m_speed & 0x7F);
    para[0] <<= 4;
    para[0] |= (m_begin & 0x0F);
    para[0] <<= 4;
    para[0] |= (m_end & 0x0F);

    code[1] = CODE_CONST | (((quint16)m_flag) << 8);
    para[1] = m_z;
    code[2] = CODE_CONST | (((quint16)m_flag) << 8);
    para[2] = m_y2;

    return true;
}

void CodeCircle::UpdateBaseMember()
{
    QString para;
    if (m_dir)
        para = QString(tr("顺时针"));
    else
        para = QString(tr("逆时针"));

    m_name = para + QString(tr("喷雾")) + QString(tr(" 半径")) + QString(" %1").arg(m_radius/100.0) + QString(tr("mm 速度")) + QString(" %1%").arg((double)m_speed);
}

bool CodeCircle::IsModified()
{
    if (m_form)
    {
        if ((m_dir != m_form->GetDir())||
            (m_radius != m_form->GetRadius())||
            (m_speed != m_form->GetSpeed())||
            (m_begin != m_form->GetBegin())||
            (m_z != m_form->GetZ())||
            (m_y2 != m_form->GetY2())||
            (m_end != m_form->GetEnd()))
            return true;
    }
    return XmlModelItem::IsModified();
}
