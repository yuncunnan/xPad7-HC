#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QTableWidget>
#include "dialogkeyboard.h"
#include "dialogportedit.h"
#define AXIS_NAME_X 0
#define AXIS_NAME_Y 1
#define AXIS_NAME_Z 2
#define AXIS_NAME_A 3
#define AXIS_NAME_B 4
#define AXIS_NAME_C 5

#define MAX_AXIS_NUM 6

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT
    
public:
    explicit Form(QWidget *parent = 0);
    ~Form();
    void InitInShaftName(void);
private slots:
    void on_tableWidget_in_cellClicked(int row, int column);
    void NewPortFileq(void);
private:
    Ui::Form *ui;
};

#endif // FORM_H
