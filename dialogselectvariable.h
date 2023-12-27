#ifndef DIALOGSELECTVARIABLE_H
#define DIALOGSELECTVARIABLE_H

#include <QDialog>
#include <QVector>
#include "xconfig.h"

#define VARSEL_MASK_USER			(1 << 0)
#define VARSEL_MASK_COUNTER         (1 << 1)
#define VARSEL_MASK_EIN				(1 << 2)
#define VARSEL_MASK_EOUT			(1 << 3)
#define VARSEL_MASK_SYS				(1 << 4)
#define VARSEL_MASK_SYSIN			(1 << 5)
#define VARSEL_MASK_SYSOUT			(1 << 6)
#define VARSEL_MASK_CONST			(1 << 7)

class QButtonGroup;

namespace Ui {
class DialogSelectVariable;
}

class DialogSelectVariable : public QDialog
{
	Q_OBJECT
	
public:
	explicit DialogSelectVariable(QWidget *parent = 0);
	~DialogSelectVariable();
	
    int DoForm(quint16 mask, quint32 &var, bool * isconst = NULL);

protected:
	void changeEvent(QEvent *e);
	
private:
	Ui::DialogSelectVariable *ui;
    static const quint16 extInputVar[8][16];
    static const quint16 extOutputVar[8][16];
    static const quint16 systemVar[24];
	static const quint16 systemIo[6][12];
	QButtonGroup *pInModule;			// 输入选择按钮组
	QButtonGroup *pOutModule;			// 输出选择按钮组
	QButtonGroup *pSysIo;				// 系统IO按钮组
    quint16 m_mask;

	static quint32 returnValue;			// 返回的变量/常量
    static bool m_isconst;

    void setExtIn(void);			// 设置扩展输入端口
    void setExtOut(void);			// 设置扩展输出端口
    void setSysIo(void);			// 设置系统IO端口
    void setPort(void);             // 设置端口名称资源

private slots:
	void inputModuleChanged(int);
	void outputModuleChanged(int);
	void systemIoChanged(int);
	void inputUserVariable(void);		// 输入用户变量信号槽
	void inputConst(void);				// 输入常量信号槽
	void btnOkClick(void);
};

extern DialogSelectVariable *xSelVar;

#endif // DIALOGSELECTVARIABLE_H
