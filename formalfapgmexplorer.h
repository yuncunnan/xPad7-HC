#ifndef FORMALFAPGMEXPLORER_H
#define FORMALFAPGMEXPLORER_H

#include <QWidget>
#include <QValidator>
#include "xfilesystemmodel.h"
#include "cmbprotocol.h"

class QFileSystemModel;

namespace Ui {
class FormAlfaPgmExplorer;
}

class FormAlfaPgmExplorer : public QWidget
{
	Q_OBJECT
	
public:
    explicit FormAlfaPgmExplorer(CMBProtocol *modbus, QWidget *parent);
    ~FormAlfaPgmExplorer();
	
	bool EnterForm(void);
	bool ExitForm(void);

protected:
	void changeEvent(QEvent *e);
	
private:
    Ui::FormAlfaPgmExplorer *ui;
	CMBProtocol *pModbus;					// Modbus协议对象
	xFileSystemModel *pDirModel;			// 程序文件数据源
	xFileSystemModel *uDirModel;			// USB数据源

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
	void popupUsb(void);					// 弹出USB存储器
};

#endif // FORMALFAPGMEXPLORER_H
