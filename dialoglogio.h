#ifndef DIALOGLOGIO_H
#define DIALOGLOGIO_H

#include <QDialog>
#include <QDateTime>
#include "xsystemlog.h"

namespace Ui {
class DialogLogIo;
}

class DialogLogIo : public QDialog
{
	Q_OBJECT
	
public:
	explicit DialogLogIo(QWidget *parent = 0);
	~DialogLogIo();
	
	int DoForm(const QDateTime &time, const quint16 (&input)[LOG_INPUT_SIZE], const quint16 (&output)[LOG_OUTPUT_SIZE]);

protected:
	void changeEvent(QEvent *e);
	
private:
	Ui::DialogLogIo *ui;
	void setPortNames(void);		// 设置端口名称
	void setPortStatus(const quint16 (&input)[LOG_INPUT_SIZE], const quint16 (&output)[LOG_OUTPUT_SIZE]);	// 设置端口状态
};

#endif // DIALOGLOGIO_H
