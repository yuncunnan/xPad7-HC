#ifndef DIALOGSELECTACTION_H
#define DIALOGSELECTACTION_H

#include <QDialog>

class QButtonGroup;
namespace Ui {
class DialogSelectAction;
}

class DialogSelectAction : public QDialog
{
	Q_OBJECT
	
public:
	explicit DialogSelectAction(QWidget *parent = 0);
	~DialogSelectAction();
	int GetCode(){ return m_code; }
    int exec(int curProc);
protected:
	void changeEvent(QEvent *e);
	
private:
	Ui::DialogSelectAction *ui;
    int m_code;
    QButtonGroup *pCodeBtn;

private slots:
    void SelectCode(int code);
};

#endif // DIALOGSELECTACTION_H
