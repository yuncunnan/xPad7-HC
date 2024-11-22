#ifndef TEACHTABLEMODEL_H
#define TEACHTABLEMODEL_H

#include <QAbstractTableModel>
#include "xmlmodelitem.h"
#include "xmlmodelvarinititem.h"
#include "xmlmodelitemoption.h"
#include "cmbprotocol.h"

#define LOADERROR_VERSION   1
#define LOADERROR_FORMAT    2
#define LOADERROR_FILE      3

class TeachTableModel : public QAbstractTableModel
{
	Q_OBJECT
public:
    explicit TeachTableModel(bool optedit, bool varedit=false, QObject *parent = 0);
	~TeachTableModel();

	//数据源接口
	int rowCount(const QModelIndex &parent) const;
	int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
	virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole);
	//指令列表操作接口
	void InsertCode(XmlModelItem *item, int insertpos = -1);//在指定位置后插入一条指令，如果指定位置为-1则插在最后，如果指定位置是最后一个则插在指定位置前
	void RemoveCode(int pos);							// 删除指定位置的指令
	void MoveUp(int pos);								// 指定位置的指令向上移
	void MoveDown(int pos);								// 指定位置的指令向下移
    void CodeCombine(int pos);
    void CodeSeparate(int pos);
    void ShowUI(int pos, bool show=true);				// 显示指令对应的UI
    int GetItemCount(){return m_codelist[m_current_process].count();}		// 得到列表的条数
    XmlModelItem* GetItem(int pos);
    bool IsCodeDisable(int pos) const;                             // 判断指令是否无效
	//bool SetGlobalSpeed(quint32 pos, quint8 speed);

    //选项列表操作接口
    void InsertOpt(XmlModelItemOption *item, int inserpos = -1);
    void RemoveOpt(int pos);
    void EnableOption(int pos, bool enable);
    void SetOptNameEn(int pos, QString name);
    void SetOptNameDis(int pos, QString name);
    void SetCurrentOpt(int pos);
    //void MoveUpOpt(int pos);
    //void MoveDownOpt(int pos);
    int GetItemCountOpt(){return m_optlist[m_current_process].count();}
    int IsOptCheck(int code_pos, int current_opt) const;        // for editor
    bool OptCheck(int code_pos, int current_opt, int check);    // for editor;

    XmlModelItemOption* GetItemOpt(int pos);

	//程序装载和保存接口
	void SavePara(int pos, bool isReset = true);		// 将指令对应UI的数据更新到指令中
	bool LoadProgram(QString filename);					// 从文件装载程序，
	bool SaveProgram(QString filename);					// 保存程序到文件
	bool NewProgram(QWidget* form = NULL);				// 建立一个新程序，即清除所有列表中的指令,加入一条END语句

	// *** 数据接口 ***
	// 检查程序是不是有效
	bool CheckProgram();
	// 判断程序是否有被修改
	bool IsModified(){return m_ismodifed;}
    bool IsModified(int pos);
	// 通过主板返回的PC指针取得对应的指令列表位置
	int GetPosByPcPointer(int pc);
//	int GetCombineBeginPos(int endpos);
    int GetCombineEndPos(int beginpos);
    // 通过指令列表位置取得对应的主板PC指针
	int GetPcPointer(int pos);
	// 生成指定指令的机器代码
    int GenerateCode(int pos, quint16* code, quint32* para);
	// 生成所有的机器代码
    int GenerateCodes(uint8_t procid, quint16* code, quint32 *para);
    int GetCode(int pos);   //返回指令码
    int GetFlag(int pos);   //返回指令控制字
    int SetFlag(int flag, int pos=-1);  //设置指令控制字

    int GetLastError(void){return m_lasterror;}
signals:
	void GetWidget(int idx, QWidget*& widget);

public slots:

private:
    bool m_varedit;
    int m_lasterror;
	void ClearProgram();//清除所有列表中的指令
	bool m_ismodifed;   //文件修改标志
    int m_current_process;
//    QList<XmlModelItem *> m_codelist[MAX_PROCESS];
    QList<XmlModelItem *> m_codelist[8];
    QList<XmlModelVarInitItem *> m_varlist;
    bool m_optedit;
    int m_currentopt;
//    QList<XmlModelItemOption *> m_optlist[MAX_PROCESS];
    QList<XmlModelItemOption *> m_optlist[8];
	//XML读接口
    bool XmlReadSinRobotElement(QXmlStreamReader & reader);
    bool XmlReadProgramElement(QXmlStreamReader & reader, int procid);
    bool XmlReadCodeElement(QXmlStreamReader &reader, int procid);
    bool XmlReadOptionElement(QXmlStreamReader & reader, int procid);
    bool XmlReadItemElement(QXmlStreamReader &reader);
	void XmlSkipUnknownElement(QXmlStreamReader &reader);
    bool XmlReadVarInitElement(QXmlStreamReader &reader);
	///////////////////////////////////////////////////////////
	QMap<int, Qt::CheckState> rowCheckState;
	int m_check_idx;
	int m_infor;
	QString m_err_string;
	int m_cur_pos;       //当前if位置//for位置//组合位置
    bool Checkif(quint8 procid);
    bool CheckCombine(quint8 procid);
    bool CheckPath(quint8 procid);
    bool Checkfor(quint8 procid);

    void AddEndToProc(int procid);
    void UpdateLineNum(void);
    bool IsInCombine(int pos);
public:
	int GetJumpBackPos(){return m_cur_pos;}
	QString GetErrString(){return m_err_string;}
    int GetCurProcess(){return m_current_process;}
    void SetCurProcess(int procid);
    //////////////////////////////////////////////////////
    int GetVarItemCount(void){return m_varlist.count();}
    bool GetVarItem(int pos, quint16 &var, quint32 &value, quint8 &type);
    bool InsertVar(quint16 var, quint32 value, quint8 type, int insertpos = -1);//在指定位置后插入一条变量，如果指定位置为-1则插在最后，如果指定位置是最后一个则插在指定位置前
    void RemoveVar(int pos); // 删除指定位置的变量
    bool SetVar(int pos , quint16 var, quint32 value, quint8 type);
    bool Inquire(void);
    int GenerateVar(int &firstidx, quint32 *para, bool ClearInq);
    bool IshaveValue(quint16 var, QList <quint16> varlist);
    bool IshaveValue(quint16 var);
    quint16 GetMinCounter();
    void UpdateAllUsrVar(QList<quint16> varlist);
    void AddUsrVar(XmlModelItem *pitem, QList<quint16> & varlist);
};

#endif // TEACHTABLEMODEL_H
