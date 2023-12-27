#ifndef FORMPGMEXPLORER_H
#define FORMPGMEXPLORER_H

#include <QWidget>
#include <QValidator>
#include "xfilesystemmodel.h"
#include "cmbprotocol.h"

class QFileSystemModel;

namespace Ui {
class FormPgmExplorer;
}

class FormPgmExplorer : public QWidget
{
	Q_OBJECT
	
public:
	explicit FormPgmExplorer(CMBProtocol *modbus, QWidget *parent);
	~FormPgmExplorer();
	
	bool EnterForm(void);
	bool ExitForm(void);

protected:
	void changeEvent(QEvent *e);
	
private:
	Ui::FormPgmExplorer *ui;
	CMBProtocol *pModbus;					// Modbus协议对象
	xFileSystemModel *pDirModel;			// 程序文件数据源
	xFileSystemModel *tDirModel;			// 模板数据源
	xFileSystemModel *uDirModel;			// USB数据源
//	QString lastname;						//最后创建的文件名
//    bool btnloadisclick;                    //载入按钮已经按过

	void setFormState();
	QString getFilePath();					// 得到文件路径
private slots:
	void userChange(void);					// 当前登录用户更改槽
	void refreshUsb(void);					// 刷新U盘

	void loadPgmFile(void);					// 载入
	void newPgmFile(void);					// 新建
	void renamePgmFile(void);				// 重命名
	void saveAsPgmFile(void);				// 另存为
	void deleteFile(void);					// 删除
	void exportToUsb(void);					// 导出

	void importUSBFileToPgm(void);				// 导入Usb文件
	void importUSBFileToTmp(void);				// 导入Usb文件
	void importTmpFile(void);				// 导入模板
	void popupUsb(void);					// 弹出USB存储器
};

#endif // FORMPGMEXPLORER_H
