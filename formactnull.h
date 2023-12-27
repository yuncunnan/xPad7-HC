#ifndef FORMACTNULL_H
#define FORMACTNULL_H

#include <QWidget>

namespace Ui {
class FormActNull;
}

class FormActNull : public QWidget
{
    Q_OBJECT
    
public:
    explicit FormActNull(QWidget *parent = 0);
    ~FormActNull();
    
protected:
	void changeEvent(QEvent *e);

private:
    Ui::FormActNull *ui;
};

#endif // FORMACTNULL_H
