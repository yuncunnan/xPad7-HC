#ifndef XTOPINFO_H
#define XTOPINFO_H

#include <QDialog>

namespace Ui {
class xTopInfo;
}

class xTopInfo : public QDialog
{
	Q_OBJECT
	
public:
	explicit xTopInfo(QWidget *parent = 0);
	~xTopInfo();

	bool ShowInformation(const QPixmap &pixmap, const QString &title, const QString &info, bool canClose);
	
private:
	Ui::xTopInfo *ui;
};

extern xTopInfo *pTopInfo;

#endif // XTOPINFO_H
