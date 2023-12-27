#include "formvarinit.h"
#include "ui_formvarinit.h"
#include "dialogframe.h"
#include "xmessagebox.h"
#include "dialogselectvariable.h"
#include "xstringresource.h"
#include "dialognumberpad.h"
#include "cmbprotocol.h"
#include "xmessagebox.h"

extern DialogFrame *pDialogMain;

FormVarInit::FormVarInit(CMBProtocol *modbus, QWidget *parent):  QWidget(parent), ui(new Ui::FormVarInit), m_varModel(false, true)
{
    ui->setupUi(this);
    retranslateUi();
    pModbus = modbus;
    posBak = 0;
    m_userVar = VAR_TYPE_USR;
    m_value = 0;
    m_type = TYPE_AUTO;

    ui->BtnAdd->setEnabled(false);
    ui->BtnDel->setEnabled(false);

    pVar = new QButtonGroup;
    pVar->addButton(ui->radioButtonAuto, TYPE_AUTO);
    pVar->addButton(ui->radioButtonInquire, TYPE_INQUIRE);
    pVar->addButton(ui->radioButtonNever, TYPE_NEVER);
    pVar->button(TYPE_AUTO)->setChecked(true);
    // 设置数据源
    ui->tableViewVar->setModel(&m_varModel);
    ui->tableViewVar->setColumnWidth(0, 100);
    ui->tableViewVar->setColumnWidth(1, 300);
    ui->tableViewVar->setColumnWidth(2, 220);
    ui->tableViewVar->setColumnWidth(3, 130);
#if SIMULATOR
    ui->tableViewVar->horizontalHeader()->setFont(QFont("Microsoft YaHei", 8));
    ui->tableViewVar->horizontalHeader()->setStyleSheet("QHeaderView {font-size: 10pt;}");
#else
	ui->tableViewVar->horizontalHeader()->setFont(QFont("Microsoft YaHei", 28));
	ui->tableViewVar->horizontalHeader()->setStyleSheet("QHeaderView {font-size: 28px;}");
#endif

     // 安装事件过滤器
    QObjectList list = ui->tableViewVar->children();
    for (int i = 0; i < list.count(); i ++)
    {
        if (list.at(i)->objectName() == QString("qt_scrollarea_viewport"))
        {
            list.at(i)->installEventFilter(this);
        }
    }
    connect(ui->tableViewVar->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(selectionChanged(QItemSelection,QItemSelection)));
    connect(pVar, SIGNAL(buttonClicked(int)), this, SLOT(TypeChanged(int)));
}

FormVarInit::~FormVarInit()
{
    delete ui;
    delete pVar;
}
void FormVarInit::retranslateUi(void)
{
}
void FormVarInit::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type())
    {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        retranslateUi();
        break;
    default:
        break;
    }
}

void FormVarInit::ChangeSelect(int pos)
{
    if (pos<m_varModel.GetVarItemCount())
        ui->tableViewVar->selectRow(pos);
}

void FormVarInit::addVar(void)
{
    quint32 ret;
//    int bakpos = 0;
    int pos = ui->tableViewVar->currentIndex().row();
    if (pos < 0)
    {
//        pos = posBak;
//		ChangeSelect(pos);
//		ui->tableViewVar->scrollTo(ui->tableViewVar->currentIndex());
    }
    else
        m_varModel.SetVar(pos, m_userVar, m_value, m_type);

    if (xSelVar->DoForm(VARSEL_MASK_USER, ret) == QDialog::Accepted)
    {
        if (m_varModel.IshaveValue(ret))
        {
            xMessageBox::DoWarning(tr("系统提示"), tr("已包含所选变量，请重新选择！"));
            return;
        }
        m_userVar = ret;
        m_value = 0;
        m_type = TYPE_AUTO;
        ui->lineEditVarName->setText(xStringResource::GetVarName(m_userVar));
        ui->dSBoxVarValue->setValue(m_value);
        pVar->button(m_type)->setChecked(true);

//            m_teachmodel->ShowUI(pos, false);
        if (m_varModel.GetVarItemCount()>(pos+1))
        {
            pos ++;
        }
        if (m_varModel.InsertVar(pos, m_userVar, m_value, m_type)==false)
        {
            xMessageBox::DoWarning(tr("系统提示"), tr("已包含所选变量，插入失败！"));
            return;
        }
//        bakpos = pos;
        ChangeSelect(pos);

        if (m_varModel.GetItemCount()>0)
        {
            ui->BtnDel->setEnabled(true);
        }
        ui->tableViewVar->scrollTo(ui->tableViewVar->currentIndex());
    }
}

void FormVarInit::delVar(void)
{
    int pos = ui->tableViewVar->currentIndex().row();
    if (pos < 0)
    {
//        pos = posBak;
//        ChangeSelect(pos);
//        ui->tableViewVar->scrollTo(ui->tableViewVar->currentIndex());
        return;
    }
    m_varModel.RemoveVar(pos);
    if (pos<m_varModel.GetVarItemCount())
    {
        ChangeSelect(pos);
    }
    else
    {
        ChangeSelect(m_varModel.GetVarItemCount()-1);
    }
    if (m_varModel.GetVarItemCount()<1)
    {
        ui->BtnDel->setEnabled(false);
    }
}

void FormVarInit::TypeChanged(int type)
{
    m_type = type;
}

bool FormVarInit::EnterForm(void)
{
    // 检查用户权限
    if (xPermissions::GetPermissions(PER_SYS_OPTION) == false)
    {
//        xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_NO_PERMISSIONS));
        if (pDialogMain)
            if (pDialogMain->ScreenSaverUserManager() == 0)
        return false;
    }
    // 自动状态不能进入
    if (pModbus->GetSysState() == SYS_STATE_AUTO)
    {
        xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), tr("自动状态不能进入！"));
        return false;
    }
    if (CMBProtocol::GetCurPgmName().isEmpty())
    {
        xMessageBox::DoWarning(tr("系统警告"), tr("没有载入当前程序文件，不能进入查看！"));
        return false;
    }
    if (m_varModel.LoadProgram(CMBProtocol::GetCurPgmName(true)) == false)
    {
        if (m_varModel.GetLastError() == LOADERROR_VERSION)
        {
            xMessageBox::DoWarning(tr("系统警告"), tr("读取程序版本出错，无法装载程序文件！"));
            return false;
        }
        if (m_varModel.GetLastError() == LOADERROR_FORMAT)
        {
            xMessageBox::DoWarning(tr("系统警告"), tr("读取文件格式出错，无法装载程序文件！"));
            return false;
        }
        if (m_varModel.GetLastError() == LOADERROR_FILE)
        {
            xMessageBox::DoWarning(tr("系统警告"), tr("读取程序文件出错，无法装载程序文件！"));
            return false;
        }
    }
    if (m_varModel.GetVarItemCount() > 0)
    {
        ui->dSBoxVarValue->setEnabled(true);
        ui->radioButtonAuto->setEnabled(true);
        ui->radioButtonInquire->setEnabled(true);
        ui->radioButtonNever->setEnabled(true);
        ui->BtnRead->setEnabled(true);
        ui->BtnWrite->setEnabled(true);
    }
    else
    {
        ui->dSBoxVarValue->setEnabled(false);
        ui->radioButtonAuto->setEnabled(false);
        ui->radioButtonInquire->setEnabled(false);
        ui->radioButtonNever->setEnabled(false);
        ui->BtnRead->setEnabled(false);
        ui->BtnWrite->setEnabled(false);
    }
    ChangeSelect(0);
    connect(this->parent(), SIGNAL(userChange()), this, SLOT(userChange()));
    // 显示界面
//    setPermissions();
    show();
    return true;
}
// 当前登录用户更改槽
void FormVarInit::userChange(void)
{
    if (xPermissions::GetPermissions(PER_TEACH) == false)
        xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_USRCHG_DENY));
    setPermissions();
}
// 根据当前用户权限设置界面
void FormVarInit::setPermissions(void)
{
//    ui->BtnAdd->setEnabled(xPermissions::GetPermissions(PER_TEACH));
//    ui->BtnDel->setEnabled(xPermissions::GetPermissions(PER_TEACH));
//    ui->BtnSave->setEnabled(xPermissions::GetPermissions(PER_TEACH));
    ui->frameVar->setEnabled(xPermissions::GetPermissions(PER_TEACH));
}

bool FormVarInit::ExitForm()
{
    int pos = ui->tableViewVar->currentIndex().row();
    if (pos < 0)
    {
    }
    else
        m_varModel.SetVar(pos, m_userVar, m_value, m_type);
    if (m_varModel.IsModified())
    {
        quint8 ret = xMessageBox::DoQuestion(tr("系统提示"), tr("当前参数已经修改，是否要更新？"));
        if (ret == XMSG_RET_YES)
        {
            m_varModel.SaveProgram(CMBProtocol::GetCurPgmName(true));
        }
    }
    // 隐藏界面
    hide();
    return true;
}
// 选择变量
void FormVarInit::selectVar(void)
{
    quint32 ret;
    if (xSelVar->DoForm(VARSEL_MASK_USER, ret) != QDialog::Accepted)
        return;
    if (m_varModel.IshaveValue(ret))
    {
        xMessageBox::DoWarning(tr("系统提示"), tr("已包含所选变量，请重新选择！"));
        return;
    }

    m_userVar = ret;
    ui->lineEditVarName->setText(xStringResource::GetVarName(m_userVar));
}

void FormVarInit::selectValue(void)
{
    DialogNumberPad numberPad;
    int value;
    if (numberPad.DoForm(value, 0, 2147483647) != QDialog::Accepted)
        return;
    ui->dSBoxVarValue->setValue(value);
}

void FormVarInit::SaveVar(void)
{
    int pos = ui->tableViewVar->currentIndex().row();
    if (pos < 0)
    {
//        pos = posBak;
//		ChangeSelect(pos);
//		ui->tableViewVar->scrollTo(ui->tableViewVar->currentIndex());
    }
    else
        m_varModel.SetVar(pos, m_userVar, m_value, m_type);

    if (m_varModel.IsModified())
    {
        ChangeSelect(pos);
        m_varModel.SaveProgram(CMBProtocol::GetCurPgmName(true));
        // 显示保存成功信息
    }
#if UI_SAVED_TIP
    xMessageBox::DoInformation(tr("保存参数"), xStringResource::GetString(STRRES_HAS_SAVED));
#endif
}
void FormVarInit::SaveVarSlot()
{
    SaveVar();
}

void FormVarInit::dsBoxValueChanged(double value)
{
    m_value = value;
}

void FormVarInit::selectionChanged(const QItemSelection & selected, const QItemSelection & deselected)
{
//	bool reselect = false;
    QModelIndexList slist = selected.indexes();
    QModelIndexList dlist = deselected.indexes();

    int pos = -1;
    if (dlist.count())  pos = dlist.at(0).row();
    if (pos < 0)
    {
    }
    else
    {
        if (m_varModel.SetVar(pos, m_userVar, m_value, m_type))
        {
//			reselect = true;
        }
    }
    pos = -1;
    if (slist.count())  pos = slist.at(0).row();
    if (pos<m_varModel.GetVarItemCount()&&(pos>=0))
    {
        if (m_varModel.GetVarItem(pos, m_userVar, m_value, m_type))
        {
            ui->lineEditVarName->setText(xStringResource::GetVarName(m_userVar));
            ui->dSBoxVarValue->setValue(m_value);
            pVar->button(m_type)->setChecked(true);
        }
    }
    ChangeSelect(pos);
}

void FormVarInit::WriteVarInit(void)
{
    if (pModbus->WriteUserVar(&m_value, m_userVar&MASK_VAR_VAL, 1) != SENDMSG_RET_ACK)
    {
        xMessageBox::DoWarning(tr("系统提示"), tr("写变量初始值错误！"));
    }
}

void FormVarInit::ReadVar(void)
{
    if (pModbus->ReadUserVar(m_userVar&MASK_VAR_VAL, 1) != SENDMSG_RET_ACK)
    {
        xMessageBox::DoWarning(tr("系统提示"), tr("读变量当前值错误！"));
    }
    else
    {
        ui->dSBoxCurValue->setValue(pModbus->ReadReg32_MB2((m_userVar&MASK_VAR_VAL)+INIT_USER_BEG));
    }
}
