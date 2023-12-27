#include "formoption.h"
#include "cmbprotocol.h"
#include "dialogframe.h"
#include "ui_formoption.h"
#include "xmessagebox.h"
#include "xstringresource.h"

extern DialogFrame *pDialogMain;

FormOption::FormOption(CMBProtocol *modbus, QWidget *parent) : QWidget(parent),	ui(new Ui::FormOption), m_pgmModel(false)
{
	ui->setupUi(this);
    retranslateUi();
    m_pModbus = modbus;
    m_OptBtnGroup = new QButtonGroup;
    m_OptBtnGroup->addButton(ui->BtnOption00, 0);
    m_OptBtnGroup->addButton(ui->BtnOption01, 1);
    m_OptBtnGroup->addButton(ui->BtnOption02, 2);
    m_OptBtnGroup->addButton(ui->BtnOption03, 3);
    m_OptBtnGroup->addButton(ui->BtnOption04, 4);
    m_OptBtnGroup->addButton(ui->BtnOption05, 5);
    m_OptBtnGroup->addButton(ui->BtnOption06, 6);
    m_OptBtnGroup->addButton(ui->BtnOption07, 7);
    m_OptBtnGroup->addButton(ui->BtnOption08, 8);
    m_OptBtnGroup->addButton(ui->BtnOption09, 9);
    m_OptBtnGroup->addButton(ui->BtnOption10, 10);
    m_OptBtnGroup->addButton(ui->BtnOption11, 11);
    m_OptBtnGroup->addButton(ui->BtnOption12, 12);
    m_OptBtnGroup->addButton(ui->BtnOption13, 13);
    m_OptBtnGroup->addButton(ui->BtnOption14, 14);
    m_OptBtnGroup->addButton(ui->BtnOption15, 15);
    m_OptBtnGroup->addButton(ui->BtnOption16, 16);
    m_OptBtnGroup->addButton(ui->BtnOption17, 17);
    m_OptBtnGroup->addButton(ui->BtnOption18, 18);
    m_OptBtnGroup->addButton(ui->BtnOption19, 19);
    m_OptBtnGroup->addButton(ui->BtnOption20, 20);
    m_OptBtnGroup->addButton(ui->BtnOption21, 21);
    m_OptBtnGroup->addButton(ui->BtnOption22, 22);
    // 连接信号槽
    connect(m_OptBtnGroup, SIGNAL(buttonClicked(int)), this, SLOT(BtnGroupHandle(int)));
}

FormOption::~FormOption()
{
	delete ui;
    delete m_OptBtnGroup;
}
void FormOption::retranslateUi(void)
{
}
void FormOption::changeEvent(QEvent *e)
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

bool FormOption::EnterForm(void)
{
    if (m_pModbus->IsALFAMode())
    {
        xMessageBox::DoWarning(tr("系统警告"), tr("系统为简易模式，不能进入！"));
        return false;
    }
    // 检查用户权限
    if (xPermissions::GetPermissions(PER_SYS_OPTION) == false)
    {
//        xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), xStringResource::GetString(STRRES_NO_PERMISSIONS));
        if (pDialogMain)
            if (pDialogMain->ScreenSaverUserManager() == 0)
        return false;
    }
    // 自动状态不能进入
    if (CMBProtocol::GetSysState() == SYS_STATE_AUTO)
    {
        xMessageBox::DoWarning(xStringResource::GetString(STRRES_WARN_TITLE), tr("自动状态不能进入！"));
        return false;
    }
    int i;
	setPermissions();
	// 连接信号槽
    connect(this->parent(), SIGNAL(userChange()), this, SLOT(userChange()));
    // 如果没有载入程序文件则警告并退出
    if (m_pModbus->GetCurPgmName().isEmpty())
    {
		xMessageBox::DoWarning(tr("系统警告"), tr("没有载入程序文件，不能选项编辑！"));
        return false;
    }
    // 如果加载程序文件出错则警告并退出
    if (m_pgmModel.LoadProgram(m_pModbus->GetCurPgmName(true)) == false)
    {
        if (m_pgmModel.GetLastError() == LOADERROR_VERSION)
        {
            xMessageBox::DoWarning(tr("系统警告"), tr("读取程序版本出错，无法装载程序文件！"));
            return false;
        }
        if (m_pgmModel.GetLastError() == LOADERROR_FORMAT)
        {
            xMessageBox::DoWarning(tr("系统警告"), tr("读取文件格式出错，无法装载程序文件！"));
            return false;
        }
        if (m_pgmModel.GetLastError() == LOADERROR_FILE)
        {
            xMessageBox::DoWarning(tr("系统警告"), tr("读取程序文件出错，无法装载程序文件！"));
            return false;
        }
    }
    if (m_pgmModel.CheckProgram() == false)
    {
        xMessageBox::DoWarning(tr("检查程序"), m_pgmModel.GetErrString()+tr(",\n请联系服务检查模板程序！"));
        return false;
    }
    // 设置端口名称
    for (i=0; i<m_OptBtnGroup->buttons().count(); i++)
    {
        xPixmapButton * btn = static_cast<xPixmapButton *>(m_OptBtnGroup->button(i));
        XmlModelItemOption* opt = m_pgmModel.GetItemOpt(i);
        if (opt)
        {
            btn->setVisible(true);
            btn->setStateOn(opt->IsEnable());
            if (opt->IsEnable())
            {
                btn->setText(opt->GetNameDis());
            }
            else
            {
                btn->setText(opt->GetNameEn());
            }
        }
        else
        {
            btn->setVisible(false);
        }
    }
    // 显示界面
//	show();
	return true;
}

void FormOption::BtnGroupHandle(int id)
{
    // 检查安全开关
    // if (xSafeSw->GetSafeSwState() != SAFE_SWITCH_ON)
     //   return;
    xPixmapButton * btn = static_cast<xPixmapButton *>(m_OptBtnGroup->button(id));
    XmlModelItemOption* opt = m_pgmModel.GetItemOpt(id);
    if (opt)
    {
        m_pgmModel.EnableOption(id, !opt->IsEnable());
        btn->setStateOn(opt->IsEnable());
        if (opt->IsEnable())
        {
            btn->setText(opt->GetNameDis());
        }
        else
        {
            btn->setText(opt->GetNameEn());
        }
    }
}

bool FormOption::ExitForm(void)
{
	// 取消信号槽连接
    disconnect(this->parent(), SIGNAL(userChange()), this, SLOT(userChange()));
    if (m_pgmModel.IsModified())
    {
        quint8 ret = xMessageBox::DoSaveTip(tr("系统提示"), tr("当前选项已经修改，是否保存？\n点击[保存]将会写入程序文件并退出；\n点击[不保存]将会放弃当前程序修改并退出；\n点击[取消]将会放弃退出操作继续选项编辑。"));
        if (ret == XMSG_RET_SAVE)
        {
            m_pgmModel.SaveProgram(m_pModbus->GetCurPgmName(true));
        }
        else if (ret != XMSG_RET_NOSAVE)
            return false;
    }
    // 隐藏界面
//	hide();
	return true;
}

void FormOption::userChange(void)
{
	setPermissions();
}
// 根据当前用户权限设置界面
void FormOption::setPermissions(void)
{
	// 检查用户权限
	if (xPermissions::GetPermissions(PER_SYS_OPTION) == false)
	{
		ui->frameoption->setEnabled(false);
	}
	else
	ui->frameoption->setEnabled(true);
}

/*bool FormOption::QueryPara(void)
{
	return true;
}

void FormOption::LoadPara(void)
{
	return;
}

bool FormOption::isModified(void)
{
	return false;
}

void FormOption::SavePara(void)
{
	return;
}*/

void FormOption::on_pushButtonOK_clicked()
{
    if (m_pgmModel.IsModified())
    {
        m_pgmModel.SaveProgram(m_pModbus->GetCurPgmName(true));
    }
	// 显示保存成功信息
#if UI_SAVED_TIP
	xMessageBox::DoInformation(tr("保存参数"), xStringResource::GetString(STRRES_HAS_SAVED));
#endif
}
