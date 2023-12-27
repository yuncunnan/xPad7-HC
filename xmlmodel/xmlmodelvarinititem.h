#ifndef XMLMODELVARINITITEM_H
#define XMLMODELVARINITITEM_H

#include <QObject>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#define TYPE_AUTO       0
#define TYPE_INQUIRE    1
#define TYPE_NEVER      2
class XmlModelVarInitItem : public QObject
{
    Q_OBJECT
    quint16 m_var;
    quint32 m_val;
    quint8 m_type;
public:
    explicit XmlModelVarInitItem(QObject *parent = 0);
    bool XmlRead(QXmlStreamReader &reader);                 //XML文件读取
    bool XmlWrite(QXmlStreamWriter &writer);			//XML文件写入
    void XmlSkipUnknownElement(QXmlStreamReader &reader);//跳过不能识别的XML Element

    QString GetVarName();
    quint16 GetVar(){return m_var;}
    quint32 GetVarValue(){return m_val;}
    quint8 GetType();
    void SetVar(quint16 var){m_var = var;}
    void SetValue(quint32 value){m_val = value;}
    void SetType(quint8 type){m_type = type;}
    QString GetTypeName();
signals:
    
public slots:
    
};

#endif // XMLMODELVARINITITEM_H
