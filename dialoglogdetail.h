#ifndef DIALOGLOGDETAIL_H
#define DIALOGLOGDETAIL_H

#include <QDialog>

namespace Ui {
class DialogLogDetail;
}

class DialogLogDetail : public QDialog
{
	Q_OBJECT
	
public:
	explicit DialogLogDetail(QWidget *parent = 0);
	~DialogLogDetail();
	
	int DoForm(const QString &time, const QIcon &type, const QString &user, const QString &detail);

protected:
	void changeEvent(QEvent *e);
	
private:
	Ui::DialogLogDetail *ui;
};

#endif // DIALOGLOGDETAIL_H
