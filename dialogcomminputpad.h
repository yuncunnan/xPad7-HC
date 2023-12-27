#ifndef DIALOGCOMMINPUTPAD_H
#define DIALOGCOMMINPUTPAD_H

#include <QDialog>

namespace Ui {
class DialogCommInputPad;
}

class DialogCommInputPad : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogCommInputPad(QWidget *parent = 0);
    ~DialogCommInputPad();
    
private:
    Ui::DialogCommInputPad *ui;
};

#endif // DIALOGCOMMINPUTPAD_H
