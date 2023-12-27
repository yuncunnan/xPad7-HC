#ifndef FORMEDITOPTION_H
#define FORMEDITOPTION_H

#include <QWidget>
#include <QTableWidgetItem>
#include "cmbprotocol.h"
#include "teachtablemodel.h"

class xStringResource;

namespace Ui {
class FormEditOption;
}

class FormEditOption : public QWidget
{
	Q_OBJECT
	
public:
	explicit FormEditOption(CMBProtocol *modbus, QWidget *parent = 0);
	~FormEditOption();
	
	bool EnterForm(void);
	bool ExitForm(void);

public slots:
	void InsertOption();						// 插入指令配置
	void RemoveOption();						// 删除指令配置
//	void BtnAccept(void);						// 保存按钮

protected:

signals:

private:
	Ui::FormEditOption *ui;
	CMBProtocol *pModbus;					// Modbus协议对象
	TeachTableModel pgmModel;
    bool m_IsItemChanged;

private slots:
    void itemChanged(QTableWidgetItem * item );
    void selectionChanged();
    void on_BtnSave_clicked();
};

#endif // FORMEDITOPTION_H
