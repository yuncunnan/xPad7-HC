#ifndef XMLMODELITEM_H
#define XMLMODELITEM_H

#include <QObject>
#include <QIcon>
#include <QWidget>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

class XmlModelItem : public QObject
{
	Q_OBJECT
public:
	explicit XmlModelItem(QIcon icon, QWidget *widget=NULL, QString name=QString(" "), QString note=QString(" "), int codes=1, QObject *parent=0);
	//XML读写接口
	virtual bool XmlRead(QXmlStreamReader &reader);                 //XML文件读取
	virtual bool XmlWrite(QXmlStreamWriter &writer) = 0;			//XML文件写入
	//UI接口
	virtual QIcon GetIcon(){return m_icon;}     //数据源图标接口
	virtual QString GetName(){return m_name;}   //数据源名称接口
    virtual QString GetNote(){return m_note;}   //数据源别名接口
	virtual bool SetNote(QString note);			//数据源别名接口
	virtual void ShowUI(bool show = true);      //对应Widget的显示和隐藏
	virtual bool Update(bool bSaveAndValidate = true){return false;}    //保持和对应Widget数据的同步，参数为true表示从数据源到Widget，为false表示从Widget到数据源，返回为false表示数据源的内容没有改变。
    //指令生成接口
	virtual int GetCodes(void){return m_codes;} //返回指令的条数（包括后面的参数指令）
	virtual int GetCode(void){return m_code;}   //返回指令码
    virtual int GetFlag(void){return m_flag;}   //返回指令控制字
    virtual void SetFlag(quint8 flag){m_flag |= flag;}
    virtual void ClrFlag(quint8 flag){m_flag &= ~flag;}

    virtual bool GenerateCode(quint16 *code, quint32 *para, quint8 other = 0);//生成最终的执行码（在MODBUS空间）
	virtual void GetExtData(void* ptr){;}
	virtual bool IsModified(){return false;}
	// 参数接口
    virtual void SetUserVar(quint16 var, int idx = 0);
    virtual quint16 GetUserVar(int idx = 0);
    virtual void SetLineNum(int line){m_linenum = line;}
    virtual int GetLineNum(void){return m_linenum;}
signals:

public slots:

protected:
    int m_linenum;
    bool m_enable;          //指令使能
	QIcon m_icon;			//指令图标
	QString m_name;			//指令名称&参数
    QString m_note;			//指令别名
	QWidget *m_widget;		//指令相关widget
    quint8 m_code;				//指令码
    quint8 m_flag;          //指令控制字
	int m_codes;			//指令条数
	void XmlSkipUnknownElement(QXmlStreamReader &reader);//跳过不能识别的XML Element
	virtual void UpdateBaseMember(){}   //基类成员更新接口，子类在这个接口中修改基类成员，一般在XmlRead和Update(false)中调用。
};

#endif // XMLMODELITEM_H
