#ifndef ISPDIALOG_H
#define ISPDIALOG_H

#include <QDialog>
#include "xfilesystemmodel.h"
#include "isp_thread.h"

namespace Ui {
class ispDialog;
}

class ispDialog : public QDialog
{
    Q_OBJECT
    
public:
	explicit ispDialog(QWidget *parent = 0);
	~ispDialog();
    bool checkIsp(bool &isH750);
    void ShowIsp(bool isH750 = false);
    int DoIsp(bool isH750 = false);
    
protected:
    void changeEvent(QEvent *e);

private:
    unsigned char DetectType;
	Ui::ispDialog *ui;
    ISP_thread programmer;
	xFileSystemModel *pDirModel;			// 文件系统数据源
	void refreshUsb(void);					// 刷新U盘

	void ReceiveComPort(QextSerialPort *pSerial, const char *Answer, unsigned long MaxSize, unsigned long *RealSize, unsigned long WantedNr0x0A);

public slots:
    virtual void reject();

private slots:
    void ChangePercent(int percent);
    void EnableControl(bool enable);
    void FindDevice(QString dev);
    void UpdateTime(unsigned int t);
    void DialogMessage(QString msg);
    void ProgramFinished(bool fail);

    void clickProgram();
    void clickBrowse();
	void clickRestart(void);
    void on_fileView_clicked(const QModelIndex &index);
    void ChangeFont(QString msg);
};

extern ispDialog *pIspDialog;

#endif
