#ifndef FORMINFORMATION_H
#define FORMINFORMATION_H

#include <QWidget>
#include "cmbprotocol.h"
#include "xstringresource.h"

namespace Ui {
class Forminformation;
}

class Forminformation : public QWidget
{
	Q_OBJECT
	
public:
	explicit Forminformation(CMBProtocol *modbus, QWidget *parent = 0);
	~Forminformation();
	
	bool EnterForm(void);
	bool ExitForm(void);

protected:
	void changeEvent(QEvent *e);
	
private:
	Ui::Forminformation *ui;
	CMBProtocol *pModbus;					// Modbus协议对象
    void retranslateUi(void);				// 更新界面字符串翻译
};

#endif // FORMINFORMATION_H
