#ifndef FORMOPTION_H
#define FORMOPTION_H

#include <QWidget>
#include <QButtonGroup>
#include "cmbprotocol.h"
#include "teachtablemodel.h"
#include "safeswitch.h"

namespace Ui {
class FormOption;
}

class FormOption : public QWidget
{
	Q_OBJECT
	
public:
	explicit FormOption(CMBProtocol *modbus, QWidget *parent = 0);
	~FormOption();

	bool EnterForm(void);
	bool ExitForm(void);

protected:
    void changeEvent(QEvent *e);
private:
	Ui::FormOption *ui;
    CMBProtocol *m_pModbus;					// Modbus协议对象
    TeachTableModel m_pgmModel;
    QButtonGroup *m_OptBtnGroup;            // 所有按钮组
    //bool QueryPara(void);					// 查询命令设置
    //void LoadPara(void);					// 从界面得到设置
    //bool isModified(void);					// 检查是否修改
    //void SavePara(void);					// 保存设置
	void setPermissions(void);				// 根据当前用户权限设置界面
    void retranslateUi(void);				// 更新界面字符串翻译

private slots :
    void userChange(void);
    void BtnGroupHandle(int id);
    void on_pushButtonOK_clicked();
};

#endif // FORMOPTION_H
