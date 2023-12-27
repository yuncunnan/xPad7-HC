#ifndef FORMVARINIT_H
#define FORMVARINIT_H

#include <QWidget>
#include <QItemSelection>
#include "cmbprotocol.h"
#include "teachtablemodel.h"

class xStringResource;
class QButtonGroup;

namespace Ui {
class FormVarInit;
}

class FormVarInit : public QWidget
{
    Q_OBJECT
    
public:
    explicit FormVarInit(CMBProtocol *modbus, QWidget *parent = 0);
    ~FormVarInit();
    bool EnterForm(void);
    bool ExitForm();

protected:
    void changeEvent(QEvent *e);

private:
    int posBak;
    CMBProtocol *pModbus;					// Modbus协议对象
    QButtonGroup *pVar;
    Ui::FormVarInit *ui;
    TeachTableModel m_varModel;
    quint16 m_userVar;
    quint32 m_value;
    quint8 m_type;
    void ChangeSelect(int pos);
    void setPermissions(void);
    void SaveVar(void);
    void retranslateUi(void);				// 更新界面字符串翻译

public slots:
    void selectionChanged(const QItemSelection & selected, const QItemSelection & deselected);

private slots:
    void addVar(void);
    void delVar(void);
    void TypeChanged(int type);
    void selectVar(void);
    void selectValue(void);
    void userChange(void);
    void SaveVarSlot();
    void dsBoxValueChanged(double value);
    void WriteVarInit(void);
    void ReadVar(void);
};

#endif // FORMVARINIT_H
