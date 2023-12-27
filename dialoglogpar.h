#ifndef DIALOGLOGPAR_H
#define DIALOGLOGPAR_H

#include <QDialog>
#include <QDateTime>

namespace Ui {
class DialogLogPar;
}

class DialogLogPar : public QDialog
{
	Q_OBJECT
	
public:
	explicit DialogLogPar(QWidget *parent = 0);
	~DialogLogPar();
	
	int DoForm(const QDateTime &time, const QByteArray &par, const quint8 type);

protected:
	void changeEvent(QEvent *e);
	
private:
	Ui::DialogLogPar *ui;

};

#endif // DIALOGLOGPAR_H
