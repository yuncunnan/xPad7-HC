#ifndef FORMACTPATH_H
#define FORMACTPATH_H

#include <QtGlobal>
#include <QWidget>

namespace Ui {
class FormActPath;
}

class FormActPath : public QWidget
{
	Q_OBJECT

public:
	explicit FormActPath(QWidget *parent = 0);
	~FormActPath();
	int GetTrajTime();
	void SetTrajTime(int trajtime);

private:
	Ui::FormActPath *ui;

private slots:
	void inputPath(void);
};
#endif // FORMACTPATH_H
