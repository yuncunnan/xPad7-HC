#ifndef XMLMODELITEMOPTION_H
#define XMLMODELITEMOPTION_H

#include <QObject>
#include <QIcon>
#include <QWidget>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

class XmlModelItemOption : public QObject
{
	Q_OBJECT
public:
    explicit XmlModelItemOption(QString nameen=QString("参数有效名称"), QString namedis=QString("参数无效名称"), QObject *parent = 0);
    //~XmlModelItemOption();
    //XML读写接口
	virtual bool XmlRead(QXmlStreamReader &reader);                 //XML文件读取
    virtual bool XmlWrite(QXmlStreamWriter &writer);			//XML文件写入
    //参数接口
    //virtual QIcon GetIconEn(){return m_icon_enable;}
    //virtual QIcon GetIconDis(){return m_icon_disable;}
    virtual QString GetNameEn(){return m_name_enable;}
    virtual QString GetNameDis(){return m_name_disable;}
    //virtual void SetIconEn(QIcon icon){m_icon_enable = icon;}
    //virtual void SetIconDis(QIcon icon){m_icon_enable = icon;}
    virtual void SetNameEn(QString name){m_name_enable = name;}
    virtual void SetNameDis(QString name){m_name_disable = name;}
    virtual void Enable(bool enable){m_enable = enable;}
    virtual bool IsEnable(void){return m_enable;}
    virtual bool IsInclude(int line);//查询是否包含本行号
    virtual void InsertLine(int line);
    virtual void RemoveLine(int line);
    virtual void RemoveAll(void);
    void RemoveCodeAdjust(int codepos);//删除前指令的位置
    void InsertCodeAdjust(int codepos);//插入后指令的位置
    void MoveCodeAdjust(int from, int to);
    //virtual bool IsModified(){return false;}

private:
    QList<int> m_linelist;
    bool m_enable;          //选项有效状态
    //QIcon m_icon_enable;	//选项有效图标
    //QIcon m_icon_disable;	//选项无效图标
    QString m_name_enable;	//选项有效名称
    QString m_name_disable;	//选项无效名称
	void XmlSkipUnknownElement(QXmlStreamReader &reader);//跳过不能识别的XML Element
};

#endif // XMLMODELITEMOPTION_H
