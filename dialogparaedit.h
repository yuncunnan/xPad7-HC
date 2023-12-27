#ifndef DIALOGPARAEDIT_H
#define DIALOGPARAEDIT_H

#include <QDialog>

namespace Ui {
class DialogParaEdit;
}

class DialogParaEdit : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogParaEdit(QWidget *parent = 0);
    ~DialogParaEdit();
    
    void changeEvent(QEvent *e);
private:
    Ui::DialogParaEdit *ui;
};

#endif // DIALOGPARAEDIT_H
