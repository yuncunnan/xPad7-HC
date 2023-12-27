#ifndef DIALOGDATETIME_H
#define DIALOGDATETIME_H

#include <QDialog>
#include <QDateEdit>

namespace Ui {
class DialogDateTime;
}

class DialogDateTime : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogDateTime(QWidget *parent = 0);
    ~DialogDateTime();
    
	int DoForm(void);

protected:
    void changeEvent(QEvent *e);
private:
    Ui::DialogDateTime *ui;
    void retranslateUi(void);				// 更新界面字符串翻译

private slots:
	void dateClicked(QDateEdit::Section sec);
	void timeClicked(QTimeEdit::Section sec);
	void SaveExit(void);
};

#endif // DIALOGDATETIME_H
