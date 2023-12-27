#ifndef DIALOGOPTION_H
#define DIALOGOPTION_H

#include <QDialog>

namespace Ui {
class DialogOption;
}

class DialogOption : public QDialog
{
	Q_OBJECT
	
public:
    explicit DialogOption(QString nameen="", QString namedis="", QWidget *parent = 0);
	~DialogOption();
    QString GetNameEn(){return m_nameen;}
    QString GetNameDis(){return m_namedis;}
private slots:
    void on_pushButtonOK_clicked();

private:
	Ui::DialogOption *ui;
    QString m_nameen;
    QString m_namedis;
};

#endif // DIALOGOPTION_H
