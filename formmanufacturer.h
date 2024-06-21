#ifndef FORMMANUFACTURER_H
#define FORMMANUFACTURER_H

#include <QWidget>
#include "xfilesystemmodel.h"
#include "cmbprotocol.h"
#include "dialogportedit.h"
#include "dialogaxisedit.h"
#include "form.h"

class QButtonGroup;

namespace Ui {
class FormManufacturer;
}

class FormManufacturer : public QWidget
{
    Q_OBJECT
    
public:
	explicit FormManufacturer(CMBProtocol *modbus, QWidget *parent = 0);
    ~FormManufacturer();
    
	bool EnterForm(void);
	bool ExitForm(void);

signals:
	void LogModelUpdate(void);

protected:
	void changeEvent(QEvent *e);

private:
    Ui::FormManufacturer *ui;
	xFileSystemModel *pDirModel;			// 文件系统数据源
	CMBProtocol *pModbus;					// Modbus协议对象
	QButtonGroup *pTab;						// 页面选择按钮
	bool hasSplash;
	bool hasWallpaper;
	bool hasInformation;
	bool hasSoftware;
	quint32 trvRelPos;
	quint32 trvCatPos;
	quint32 trvWaitPos;
	quint32 paVerCatPos;
	quint32 paVerRelPos;
	quint32 paVerWaitPos;
	quint32 paHorCatPos;
	quint32 paHorWaitPos;
	quint32 paHorRelPos;
	quint32 raVerCatPos;
	quint32 raVerRelPos;
	quint32 raVerWaitPos;
	quint32 raHorCatPos;
	quint32 raHorRelPos;
	quint32 raHorWaitPos;
	quint32 extCatPos;
	quint32 extRelPos;
	quint32 extWaitPos;
	void setPermissions(void);				// 根据当前用户权限设置界面
	void setFileFilter(void);
	bool readSrvPar(ServoParameter &par);
    DialogPortEdit *m_PortEdit;
	DialogAxisEdit *m_AxisEdit;

private slots:
	void setCurrentPage(void);				// 设置当前页面槽
	void userChange(void);					// 当前登录用户更改槽
	void refreshUsb(void);					// 刷新U盘
	void popupUsb(void);					// 弹出U盘
	void loadSplash(void);					// 导入开机画面
	void loadWallpaper(void);				// 导入主画面
	void loadInformation(void);				// 导入厂商信息
	void loadIoNames(void);					// 导入端口名称
	void resetIoNames(void);				// 重置端口名称
	void updateSoftware(void);				// 升级软件
	void restoreSoftware(void);				// 恢复备份的软件
	void setFactoryId(void);				// 写入厂商 ID
	void restartApp(void);					// 重新启动软件
	void cfgExport(void);					// 导出机械手配置
	void cfgImport(void);					// 导入机械手配置
	void logExport(void);					// 导出系统日志
	void logClear(void);					// 清除系统日志
	void enterIsp(void);
    void on_fileView_clicked(const QModelIndex &index);
    void changeFont(QString msg);
    void portEdit(void);                    //进入端口编辑
    void axisEdit(void);                   //进入轴编辑
};

#endif // FORMMANUFACTURER_H
