#ifndef FORMACTDELAY_H
#define FORMACTDELAY_H

#include <QWidget>

namespace Ui {
class FormActDelay;
}

class FormActDelay : public QWidget
{
    Q_OBJECT
    
public:
    explicit FormActDelay(QWidget *parent = 0);
    ~FormActDelay();
    void SetDelay(int delay);
    int GetDelay();

protected:
	void changeEvent(QEvent *e);

private:
    Ui::FormActDelay *ui;

private slots:
	void inputDelay(void);
};

#endif // FORMACTDELAY_H
