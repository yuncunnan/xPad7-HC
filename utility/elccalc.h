#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class ElcCalc;
}

class ElcCalc : public QDialog
{
    Q_OBJECT
    
public:
	explicit ElcCalc(QWidget *parent = 0);
	~ElcCalc();
    
protected:
	void changeEvent(QEvent *e);

private:
	Ui::ElcCalc *ui;

private slots:
	void inputResolution(void);
	void inputPerimeter(void);
	void inputNumerator(void);
	void inputDenomintor(void);
    void press(void);
};

#endif // DIALOG_H
