#ifndef DIALOGAXISEDIT_H
#define DIALOGAXISEDIT_H

#include <QDialog>
#include "dialogkeyboard.h"

#define AXIS_NAME_X 0
#define AXIS_NAME_Y 1
#define AXIS_NAME_Z 2
#define AXIS_NAME_A 3
#define AXIS_NAME_B 4
#define AXIS_NAME_C 5

#define MAX_AXIS_NUM 6

namespace Ui {
class DialogAxisEdit;
}

class DialogAxisEdit : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogAxisEdit(QWidget *parent = 0);
    ~DialogAxisEdit();

    int DoForm(void);
    
private:
    Ui::DialogAxisEdit *ui;
    void InitInAxisName(void);
    void changeEvent(QEvent *e);
    void retranslateUI();

private slots:
    void tableWidgeCellClicked(int row,int column);//修改轴名称
    void NewPortFile(void);
};

#endif // DIALOGAXISEDIT_H
