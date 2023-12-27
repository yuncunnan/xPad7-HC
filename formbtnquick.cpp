#include <QButtonGroup>
#include "teachtablemodel.h"
#include "dialognumberpad.h"
#include "formbtnquick.h"
#include "cmbprotocol.h"
#include "ui_formbtnquick.h"
#include "servoalias.h"
#include "xstringresource.h"
#include "xmessagebox.h"
#include "codepos.h"
#include "xioport.h"
#include <QDebug>

FormBtnQuick::FormBtnQuick(CMBProtocol* modbus, QWidget *parent) : QWidget(parent), ui(new Ui::FormBtnQuick), m_teachmodel(new TeachTableModel(false))
{
    pModbus = modbus;
    // 初始化界面
    ui->setupUi(this);
    retranslateUi();
    // 设置对话框显示效果
    setWindowFlags(Qt::FramelessWindowHint);
    //setAttribute(Qt::WA_TranslucentBackground, true);

    m_wait_xtype = POS_TYPE_POINT;
    m_wait_ytype = POS_TYPE_POINT;
    m_wait_ztype = POS_TYPE_POINT;
    m_wait_atype = POS_TYPE_POINT;
    m_wait_btype = POS_TYPE_POINT;
    m_wait_xpos = 0;
    m_wait_ypos = 0;
    m_wait_zpos = 0;
    m_wait_apos = 0;
    m_wait_bpos = 0;

    m_fetch_xtype = POS_TYPE_POINT;
    m_fetch_ytype = POS_TYPE_POINT;
    m_fetch_ztype = POS_TYPE_POINT;
    m_fetch_atype = POS_TYPE_POINT;
    m_fetch_btype = POS_TYPE_POINT;
    m_fetch_xpos = 0;
    m_fetch_ypos = 0;
    m_fetch_zpos = 0;
    m_fetch_apos = 0;
    m_fetch_bpos = 0;

    m_product_xtype = POS_TYPE_POINT;
    m_product_ytype = POS_TYPE_POINT;
    m_product_ztype = POS_TYPE_POINT;
    m_product_xpos = 0;
    m_product_ypos = 0;
    m_product_zpos = 0;

    m_waste_ztype = POS_TYPE_POINT;
    m_waste_atype = POS_TYPE_POINT;
    m_waste_btype = POS_TYPE_POINT;
    m_waste_zpos = 0;
    m_waste_apos = 0;
    m_waste_bpos = 0;

    m_current_page = 0;
    connect(pModbus, SIGNAL(signal_OutputChange()), this, SLOT(OutputIO()));

//    ui->checkBoxProductRotate->setChecked(true);
//    ui->checkBoxWasteRotate->setChecked(true);

}

FormBtnQuick::~FormBtnQuick()
{
    disconnect(pModbus, SIGNAL(signal_OutputChange()), this, SLOT(OutputIO()));
    delete ui;
}

void FormBtnQuick::changeEvent(QEvent *e)
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

bool FormBtnQuick::EnterForm(bool newprogram)
{
    if (newprogram)
    {
        qDebug() << "new program!!!!!!!!!!";
        ui->checkBoxPA->setChecked(true);
        ui->checkBoxRA->setChecked(false);
        ui->cBoxFetchPro->setCurrentIndex(0);
        ui->cBoxFetchRun->setCurrentIndex(4);
        ui->checkBoxFetchPro->setChecked(false);
        ui->checkBoxFetchRun->setChecked(false);

        ui->checkBoxWaitRotate->setChecked(false);
        ui->BoxWaitTrv->setText("0.00");
        ui->BoxWaitPHor->setText("0.00");
        ui->BoxWaitPVer->setText("0.00");
        ui->BoxWaitRHor->setText("0.00");
        ui->BoxWaitRVer->setText("0.00");

//        ui->BoxFetchTrv->setText("");
        ui->BoxFetchPHor->setText("0.00");
        ui->BoxFetchRHor->setText("0.00");
        ui->BoxFetchPVer->setText("0.00");
        ui->BoxFetchRVer->setText("0.00");

        ui->checkBoxProductRotate->setChecked(true);
        ui->BoxProductTrv->setText("0.00");
        ui->BoxProductPHor->setText("0.00");
        ui->BoxProductPVer->setText("0.00");

        ui->checkBoxWasteRotate->setChecked(true);
        ui->BoxWasteTrv->setText("0.00");
        ui->BoxWasteRHor->setText("0.00");
        ui->BoxWasteRVer->setText("0.00");
        ui->checkBoxWasteRotateFirst->setChecked(false);
        ui->checkBoxMatrix->setChecked(false);

        m_wait_xtype = POS_TYPE_POINT;
        m_wait_ytype = POS_TYPE_POINT;
        m_wait_ztype = POS_TYPE_POINT;
        m_wait_atype = POS_TYPE_POINT;
        m_wait_btype = POS_TYPE_POINT;
        m_wait_xpos = 0;
        m_wait_ypos = 0;
        m_wait_zpos = 0;
        m_wait_apos = 0;
        m_wait_bpos = 0;
        ui->BoxWaitPHor->setText("");
        ui->BoxWaitPVer->setText("");
        ui->BoxWaitTrv->setText("");
        ui->BoxWaitRVer->setText("");
        ui->BoxWaitRHor->setText("");

        m_fetch_xtype = POS_TYPE_POINT;
        m_fetch_ytype = POS_TYPE_POINT;
        m_fetch_ztype = POS_TYPE_POINT;
        m_fetch_atype = POS_TYPE_POINT;
        m_fetch_btype = POS_TYPE_POINT;
        m_fetch_xpos = 0;
        m_fetch_ypos = 0;
        m_fetch_zpos = 0;
        m_fetch_apos = 0;
        m_fetch_bpos = 0;
        ui->BoxFetchPHor->setText("");
        ui->BoxFetchPVer->setText("");
        ui->BoxFetchRHor->setText("");
        ui->BoxFetchRVer->setText("");
    //    ui->BoxFetchTrv->setText("");

        m_product_xtype = POS_TYPE_POINT;
        m_product_ytype = POS_TYPE_POINT;
        m_product_ztype = POS_TYPE_POINT;
        m_product_xpos = 0;
        m_product_ypos = 0;
        m_product_zpos = 0;
        ui->BoxProductPHor->setText("");
        ui->BoxProductPVer->setText("");
        ui->BoxProductTrv->setText("");

        m_waste_ztype = POS_TYPE_POINT;
        m_waste_atype = POS_TYPE_POINT;
        m_waste_btype = POS_TYPE_POINT;
        m_waste_zpos = 0;
        m_waste_apos = 0;
        m_waste_bpos = 0;
        ui->BoxWasteRHor->setText("");
        ui->BoxWasteRVer->setText("");
        ui->BoxWasteTrv->setText("");
        ui->checkBoxProductRotate->setChecked(true);
        ui->labelWaitRarmState->setText(tr("前进"));
        ui->labelFetchRarmState->setText(tr("后退"));
        ui->labelWasteState->setText(tr("上升"));
    }
    init();
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget_fetch->setCurrentIndex(0);
    ui->checkBoxWasteRotate->setVisible(false);
    ui->labelWasteRotate->setVisible(false);
    UpdateWidgetState();
    show();
    return true;
}
void FormBtnQuick::init(void)
{
    ui->labelWaitRarmState->setEnabled(pModbus->GetRunnerUse());
    ui->labelWasteState->setEnabled(pModbus->GetRunnerUse());
    ui->labelWaste_2->setEnabled(pModbus->GetRunnerUse());
    ui->labelWasteTrv->setEnabled(pModbus->GetRunnerUse());
    ui->BtnWasteSync->setEnabled((pModbus->GetRunnerUse())||(ui->checkBoxRA->isChecked()));
    ui->BtnWaitSync->setEnabled((ui->checkBoxPA->isChecked())||(ui->checkBoxRA->isChecked())||(pModbus->GetRunnerUse()));
    ui->BtnProductSync->setEnabled(ui->checkBoxPA->isChecked());
    ui->BtnFetchSync->setEnabled((ui->checkBoxPA->isChecked())||(ui->checkBoxRA->isChecked()));
}

void FormBtnQuick::retranslateUi(void)
{
    if(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_5AXIS)
    {
        ui->cBoxFetchPro->setItemText(0, xStringResource::GetVarName(MAIN_VAR_Y11));
        ui->cBoxFetchPro->setItemText(1, xStringResource::GetVarName(MAIN_VAR_Y12));
        ui->cBoxFetchPro->setItemText(2, xStringResource::GetVarName(MAIN_VAR_Y13));
        ui->cBoxFetchPro->setItemText(3, xStringResource::GetVarName(MAIN_VAR_Y14));
        ui->cBoxFetchPro->setItemText(4, xStringResource::GetVarName(MAIN_VAR_Y15));
        ui->cBoxFetchPro->setItemText(5, xStringResource::GetVarName(MAIN_VAR_Y16));
        ui->cBoxFetchPro->setItemText(6, xStringResource::GetVarName(MAIN_VAR_Y17));
        ui->cBoxFetchPro->setItemText(7, xStringResource::GetVarName(MAIN_VAR_Y18));
        ui->cBoxFetchPro->setItemText(8, xStringResource::GetVarName(MAIN_VAR_Y19));
        ui->cBoxFetchPro->setItemText(9, xStringResource::GetVarName(MAIN_VAR_Y20));
        ui->cBoxFetchPro->setItemText(10, xStringResource::GetVarName(MAIN_VAR_Y21));
        ui->cBoxFetchPro->setItemText(11, xStringResource::GetVarName(MAIN_VAR_Y22));
        ui->cBoxFetchPro->setItemText(12, xStringResource::GetVarName(MAIN_VAR_Y23));
        ui->cBoxFetchPro->setItemText(13, xStringResource::GetVarName(MAIN_VAR_Y24));

    }
    else if (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)
    {
        ui->cBoxFetchPro->setItemText(0, xStringResource::GetVarName(MAIN_VAR_Y12));
        ui->cBoxFetchPro->setItemText(1, xStringResource::GetVarName(MAIN_VAR_Y13));
        ui->cBoxFetchPro->setItemText(2, xStringResource::GetVarName(MAIN_VAR_Y14));
        ui->cBoxFetchPro->setItemText(3, xStringResource::GetVarName(MAIN_VAR_Y01));
        ui->cBoxFetchPro->setItemText(4, xStringResource::GetVarName(MAIN_VAR_Y02));
        ui->cBoxFetchPro->setItemText(5, xStringResource::GetVarName(MAIN_VAR_Y03));
        ui->cBoxFetchPro->setItemText(6, xStringResource::GetVarName(MAIN_VAR_Y04));
        ui->cBoxFetchPro->setItemText(7, xStringResource::GetVarName(MAIN_VAR_Y05));
        ui->cBoxFetchPro->setItemText(8, xStringResource::GetVarName(MAIN_VAR_Y08));
        ui->cBoxFetchPro->setItemText(9, xStringResource::GetVarName(MAIN_VAR_Y09));
        ui->cBoxFetchPro->setItemText(10, xStringResource::GetVarName(MAIN_VAR_Y10));
        ui->cBoxFetchPro->setItemText(11, xStringResource::GetVarName(MAIN_VAR_Y11));
        ui->cBoxFetchPro->setItemText(12, xStringResource::GetVarName(MAIN_VAR_Y15));
        ui->cBoxFetchPro->setMaxCount(13);
    }
    else if (CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_DVS)
    {
        ui->cBoxFetchPro->setItemText(0, xStringResource::GetVarName(MAIN_VAR_Y08));
        ui->cBoxFetchPro->setItemText(1, xStringResource::GetVarName(MAIN_VAR_Y09));
        ui->cBoxFetchPro->setItemText(2, xStringResource::GetVarName(MAIN_VAR_Y10));
        ui->cBoxFetchPro->setItemText(3, xStringResource::GetVarName(MAIN_VAR_Y11));
        ui->cBoxFetchPro->setItemText(4, xStringResource::GetVarName(MAIN_VAR_Y12));
        ui->cBoxFetchPro->setItemText(5, xStringResource::GetVarName(MAIN_VAR_Y13));
        ui->cBoxFetchPro->setItemText(6, xStringResource::GetVarName(MAIN_VAR_Y14));
        ui->cBoxFetchPro->setItemText(7, xStringResource::GetVarName(MAIN_VAR_Y15));
        ui->cBoxFetchPro->setItemText(8, xStringResource::GetVarName(MAIN_VAR_Y16));
        ui->cBoxFetchPro->setItemText(9, xStringResource::GetVarName(MAIN_VAR_Y17));
        ui->cBoxFetchPro->setItemText(10, xStringResource::GetVarName(MAIN_VAR_Y18));
        ui->cBoxFetchPro->setItemText(11, xStringResource::GetVarName(MAIN_VAR_Y19));
        ui->cBoxFetchPro->setItemText(12, xStringResource::GetVarName(MAIN_VAR_Y20));
        ui->cBoxFetchPro->setItemText(13, xStringResource::GetVarName(MAIN_VAR_Y22));
    }
    else
    {
        ui->cBoxFetchPro->setItemText(0, xStringResource::GetVarName(EM1_VAR_Y02));
        ui->cBoxFetchPro->setItemText(1, xStringResource::GetVarName(EM1_VAR_Y03));
        ui->cBoxFetchPro->setItemText(2, xStringResource::GetVarName(EM1_VAR_Y04));
        ui->cBoxFetchPro->setItemText(3, xStringResource::GetVarName(EM1_VAR_Y05));
        ui->cBoxFetchPro->setItemText(4, xStringResource::GetVarName(EM1_VAR_Y06));
        ui->cBoxFetchPro->setItemText(5, xStringResource::GetVarName(EM1_VAR_Y07));
        ui->cBoxFetchPro->setItemText(6, xStringResource::GetVarName(EM1_VAR_Y08));
        ui->cBoxFetchPro->setItemText(7, xStringResource::GetVarName(EM1_VAR_Y09));
        ui->cBoxFetchPro->setItemText(8, xStringResource::GetVarName(EM1_VAR_Y10));
        ui->cBoxFetchPro->setItemText(9, xStringResource::GetVarName(EM1_VAR_Y11));
        ui->cBoxFetchPro->setItemText(10, xStringResource::GetVarName(EM1_VAR_Y12));
        ui->cBoxFetchPro->setItemText(11, xStringResource::GetVarName(EM1_VAR_Y13));
        ui->cBoxFetchPro->setItemText(12, xStringResource::GetVarName(EM1_VAR_Y14));
        ui->cBoxFetchPro->setItemText(13, xStringResource::GetVarName(EM1_VAR_Y15));
    }
    if(CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_5AXIS)
    {
        ui->cBoxFetchRun->setItemText(0, xStringResource::GetVarName(MAIN_VAR_Y11));
        ui->cBoxFetchRun->setItemText(1, xStringResource::GetVarName(MAIN_VAR_Y12));
        ui->cBoxFetchRun->setItemText(2, xStringResource::GetVarName(MAIN_VAR_Y13));
        ui->cBoxFetchRun->setItemText(3, xStringResource::GetVarName(MAIN_VAR_Y14));
        ui->cBoxFetchRun->setItemText(4, xStringResource::GetVarName(MAIN_VAR_Y15));
        ui->cBoxFetchRun->setItemText(5, xStringResource::GetVarName(MAIN_VAR_Y16));
        ui->cBoxFetchRun->setItemText(6, xStringResource::GetVarName(MAIN_VAR_Y17));
        ui->cBoxFetchRun->setItemText(7, xStringResource::GetVarName(MAIN_VAR_Y18));
        ui->cBoxFetchRun->setItemText(8, xStringResource::GetVarName(MAIN_VAR_Y19));
        ui->cBoxFetchRun->setItemText(9, xStringResource::GetVarName(MAIN_VAR_Y20));
        ui->cBoxFetchRun->setItemText(10, xStringResource::GetVarName(MAIN_VAR_Y21));
        ui->cBoxFetchRun->setItemText(11, xStringResource::GetVarName(MAIN_VAR_Y22));
        ui->cBoxFetchRun->setItemText(12, xStringResource::GetVarName(MAIN_VAR_Y23));
        ui->cBoxFetchRun->setItemText(13, xStringResource::GetVarName(MAIN_VAR_Y24));
    }
    else if (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)
    {
        ui->cBoxFetchRun->setItemText(0, xStringResource::GetVarName(MAIN_VAR_Y12));
        ui->cBoxFetchRun->setItemText(1, xStringResource::GetVarName(MAIN_VAR_Y13));
        ui->cBoxFetchRun->setItemText(2, xStringResource::GetVarName(MAIN_VAR_Y14));
        ui->cBoxFetchRun->setItemText(3, xStringResource::GetVarName(MAIN_VAR_Y01));
        ui->cBoxFetchRun->setItemText(4, xStringResource::GetVarName(MAIN_VAR_Y02));
        ui->cBoxFetchRun->setItemText(5, xStringResource::GetVarName(MAIN_VAR_Y03));
        ui->cBoxFetchRun->setItemText(6, xStringResource::GetVarName(MAIN_VAR_Y04));
        ui->cBoxFetchRun->setItemText(7, xStringResource::GetVarName(MAIN_VAR_Y05));
        ui->cBoxFetchRun->setItemText(8, xStringResource::GetVarName(MAIN_VAR_Y08));
        ui->cBoxFetchRun->setItemText(9, xStringResource::GetVarName(MAIN_VAR_Y09));
        ui->cBoxFetchRun->setItemText(10, xStringResource::GetVarName(MAIN_VAR_Y10));
        ui->cBoxFetchRun->setItemText(11, xStringResource::GetVarName(MAIN_VAR_Y11));
        ui->cBoxFetchRun->setItemText(12, xStringResource::GetVarName(MAIN_VAR_Y15));
        ui->cBoxFetchRun->setMaxCount(13);
    }
    else if (CMBProtocol::GetSysTypeHigh() == BOARD_VERSION_H750_DVS)
    {
        ui->cBoxFetchRun->setItemText(0, xStringResource::GetVarName(MAIN_VAR_Y08));
        ui->cBoxFetchRun->setItemText(1, xStringResource::GetVarName(MAIN_VAR_Y09));
        ui->cBoxFetchRun->setItemText(2, xStringResource::GetVarName(MAIN_VAR_Y10));
        ui->cBoxFetchRun->setItemText(3, xStringResource::GetVarName(MAIN_VAR_Y11));
        ui->cBoxFetchRun->setItemText(4, xStringResource::GetVarName(MAIN_VAR_Y12));
        ui->cBoxFetchRun->setItemText(5, xStringResource::GetVarName(MAIN_VAR_Y13));
        ui->cBoxFetchRun->setItemText(6, xStringResource::GetVarName(MAIN_VAR_Y14));
        ui->cBoxFetchRun->setItemText(7, xStringResource::GetVarName(MAIN_VAR_Y15));
        ui->cBoxFetchRun->setItemText(8, xStringResource::GetVarName(MAIN_VAR_Y16));
        ui->cBoxFetchRun->setItemText(9, xStringResource::GetVarName(MAIN_VAR_Y17));
        ui->cBoxFetchRun->setItemText(10, xStringResource::GetVarName(MAIN_VAR_Y18));
        ui->cBoxFetchRun->setItemText(11, xStringResource::GetVarName(MAIN_VAR_Y19));
        ui->cBoxFetchRun->setItemText(12, xStringResource::GetVarName(MAIN_VAR_Y20));
        ui->cBoxFetchRun->setItemText(13, xStringResource::GetVarName(MAIN_VAR_Y22));
    }
    else
    {
        ui->cBoxFetchRun->setItemText(0, xStringResource::GetVarName(EM1_VAR_Y02));
        ui->cBoxFetchRun->setItemText(1, xStringResource::GetVarName(EM1_VAR_Y03));
        ui->cBoxFetchRun->setItemText(2, xStringResource::GetVarName(EM1_VAR_Y04));
        ui->cBoxFetchRun->setItemText(3, xStringResource::GetVarName(EM1_VAR_Y05));
        ui->cBoxFetchRun->setItemText(4, xStringResource::GetVarName(EM1_VAR_Y06));
        ui->cBoxFetchRun->setItemText(5, xStringResource::GetVarName(EM1_VAR_Y07));
        ui->cBoxFetchRun->setItemText(6, xStringResource::GetVarName(EM1_VAR_Y08));
        ui->cBoxFetchRun->setItemText(7, xStringResource::GetVarName(EM1_VAR_Y09));
        ui->cBoxFetchRun->setItemText(8, xStringResource::GetVarName(EM1_VAR_Y10));
        ui->cBoxFetchRun->setItemText(9, xStringResource::GetVarName(EM1_VAR_Y11));
        ui->cBoxFetchRun->setItemText(10, xStringResource::GetVarName(EM1_VAR_Y12));
        ui->cBoxFetchRun->setItemText(11, xStringResource::GetVarName(EM1_VAR_Y13));
        ui->cBoxFetchRun->setItemText(12, xStringResource::GetVarName(EM1_VAR_Y14));
        ui->cBoxFetchRun->setItemText(13, xStringResource::GetVarName(EM1_VAR_Y15));
    }

    ui->labelWaitPHor->setText(GetServoName(AXIS_IDX_PHOR) + tr("轴:"));
    ui->labelWaitPVer->setText(GetServoName(AXIS_IDX_PVER) + tr("轴:"));
    ui->labelWaitTrv->setText(GetServoName(AXIS_IDX_TRV) + tr("轴:"));
    ui->labelWaitRHor->setText(GetServoName(AXIS_IDX_RHOR) + tr("轴:"));
    ui->labelWaitRVer->setText(GetServoName(AXIS_IDX_RVER) + tr("轴:"));

    ui->labelFetchPHor->setText(GetServoName(AXIS_IDX_PHOR) + tr("轴:"));
    ui->labelFetchPVer->setText(GetServoName(AXIS_IDX_PVER) + tr("轴:"));
    ui->labelFetchRHor->setText(GetServoName(AXIS_IDX_RHOR) + tr("轴:"));
    ui->labelFetchRVer->setText(GetServoName(AXIS_IDX_RVER) + tr("轴:"));

    ui->labelProductPHor->setText(GetServoName(AXIS_IDX_PHOR) + tr("轴:"));
    ui->labelProductPVer->setText(GetServoName(AXIS_IDX_PVER) + tr("轴:"));
    ui->labelProductTrv->setText(GetServoName(AXIS_IDX_TRV) + tr("轴:"));

    ui->labelWasteRHor->setText(GetServoName(AXIS_IDX_RHOR) + tr("轴:"));
    ui->labelWasteRVer->setText(GetServoName(AXIS_IDX_RVER) + tr("轴:"));
    ui->labelWasteTrv->setText(GetServoName(AXIS_IDX_TRV) + tr("轴:"));


    UpdateWidgetState();
}

int FormBtnQuick::GetWaitX()
{
    if (m_wait_xtype==POS_TYPE_POINT)
        return m_wait_xpos;
    if (m_wait_xtype==POS_TYPE_VAR)
        return (VAR_TYPE_USR | m_wait_xpos);
    return 0;
}
int FormBtnQuick::GetWaitY()
{
    if (m_wait_ytype==POS_TYPE_POINT)
        return m_wait_ypos;
    if (m_wait_ytype==POS_TYPE_VAR)
        return (VAR_TYPE_USR | m_wait_ypos);
    return 0;
}
int FormBtnQuick::GetWaitZ()
{
    if (m_wait_ztype==POS_TYPE_POINT)
        return m_wait_zpos;
    if (m_wait_ztype==POS_TYPE_VAR)
        return (VAR_TYPE_USR | m_wait_zpos);
    return 0;
}
int FormBtnQuick::GetWaitA()
{
    if (m_wait_atype==POS_TYPE_POINT)
        return m_wait_apos;
    if (m_wait_atype==POS_TYPE_VAR)
        return (VAR_TYPE_USR | m_wait_apos);
    return 0;
}
int FormBtnQuick::GetWaitB()
{
    if (m_wait_btype==POS_TYPE_POINT)
        return m_wait_bpos;
    if (m_wait_btype==POS_TYPE_VAR)
        return (VAR_TYPE_USR | m_wait_bpos);
    return 0;
}

int FormBtnQuick::GetFetchX()
{
    if (m_fetch_xtype==POS_TYPE_POINT)
        return m_fetch_xpos;
    if (m_fetch_xtype==POS_TYPE_VAR)
        return (VAR_TYPE_USR | m_fetch_xpos);
    return 0;
}
int FormBtnQuick::GetFetchY()
{
    if (m_fetch_ytype==POS_TYPE_POINT)
        return m_fetch_ypos;
    if (m_fetch_ytype==POS_TYPE_VAR)
        return (VAR_TYPE_USR | m_fetch_ypos);
    return 0;
}
//int FormBtnQuick::GetFetchZ()
//{
//    if (m_fetch_ztype==POS_TYPE_POINT)
//        return m_fetch_zpos;
//    if (m_fetch_ztype==POS_TYPE_VAR)
//        return (VAR_TYPE_USR | m_fetch_zpos);
//    return 0;
//}
int FormBtnQuick::GetFetchA()
{
    if (m_fetch_atype==POS_TYPE_POINT)
        return m_fetch_apos;
    if (m_fetch_atype==POS_TYPE_VAR)
        return (VAR_TYPE_USR | m_fetch_apos);
    return 0;
}
int FormBtnQuick::GetFetchB()
{
    if (m_fetch_btype==POS_TYPE_POINT)
        return m_fetch_bpos;
    if (m_fetch_btype==POS_TYPE_VAR)
        return (VAR_TYPE_USR | m_fetch_bpos);
    return 0;
}

int FormBtnQuick::GetProductX()
{
    if (m_product_xtype==POS_TYPE_POINT)
        return m_product_xpos;
    if (m_product_xtype==POS_TYPE_VAR)
        return (VAR_TYPE_USR | m_product_xpos);
    return 0;
}
int FormBtnQuick::GetProductY()
{
    if (m_product_ytype==POS_TYPE_POINT)
        return m_product_ypos;
    if (m_product_ytype==POS_TYPE_VAR)
        return (VAR_TYPE_USR | m_product_ypos);
    return 0;
}
int FormBtnQuick::GetProductZ()
{
    if (m_product_ztype==POS_TYPE_POINT)
        return m_product_zpos;
    if (m_product_ztype==POS_TYPE_VAR)
        return (VAR_TYPE_USR | m_product_zpos);
    return 0;
}

int FormBtnQuick::GetWasteZ()
{
    if (m_waste_ztype==POS_TYPE_POINT)
        return m_waste_zpos;
    if (m_waste_ztype==POS_TYPE_VAR)
        return (VAR_TYPE_USR | m_waste_zpos);
    return 0;
}
int FormBtnQuick::GetWasteA()
{
    if (m_waste_atype==POS_TYPE_POINT)
        return m_waste_apos;
    if (m_waste_atype==POS_TYPE_VAR)
        return (VAR_TYPE_USR | m_waste_apos);
    return 0;
}
int FormBtnQuick::GetWasteB()
{
    if (m_waste_btype==POS_TYPE_POINT)
        return m_waste_bpos;
    if (m_waste_btype==POS_TYPE_VAR)
        return (VAR_TYPE_USR | m_waste_bpos);
    return 0;
}
quint16 FormBtnQuick::GetCheckBoxState()
{
    rotbmp  = ((quint16)(ui->checkBoxPA->isChecked()?1:0)) << 0;                // 使用正臂
    rotbmp |= ((quint16)(ui->checkBoxRA->isChecked()?1:0)) << 1;                // 使用副臂
    rotbmp |= ((quint16)(ui->checkBoxFetchPro->isChecked()?1:0)) << 2;          // 成品治具检测
    rotbmp |= ((quint16)(ui->checkBoxFetchRun->isChecked()?1:0)) << 3;          // 水口治具检测
    rotbmp |= ((quint16)(ui->checkBoxWaitRotate->isChecked()?1:0)) << 4;        // 待机倒角状态
//    rotbmp |= ((quint16)(ui->checkBoxFetchRotate->isChecked()?1:0)) << 5;       // 取物倒角状态
    rotbmp |= ((quint16)(ui->checkBoxProductRotate->isChecked()?1:0)) << 6;     // 放成品倒角状态
    rotbmp |= ((quint16)(ui->checkBoxWasteRotate->isChecked()?1:0)) << 7;       // 放水口倒角状态
//    rotbmp |= ((quint16)(ui->checkBoxTrvOut->isChecked()?1:0)) << 8;            // 横出倒角状态
    rotbmp |= ((quint16)(ui->checkBoxMatrix->isChecked()?1:0)) << 10;           // 使用矩阵
    rotbmp |= ((quint16)(ui->checkBoxWasteRotateFirst->isChecked()?1:0)) << 11; // 先放水口
    return rotbmp;
}
bool FormBtnQuick::CheckBoxWasteRotateFirstState()
{
    bool state = ui->checkBoxWasteRotateFirst->isChecked();
    return state;
}

quint32 FormBtnQuick::GetVacuumBmp(void)
{
    if(pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)
    {
        vacbmp  = ((quint16)((ui->cBoxFetchPro->currentIndex()==0)?1:0)) << 12;
        vacbmp |= ((quint16)((ui->cBoxFetchPro->currentIndex()==1)?1:0)) << 13;
        vacbmp |= ((quint16)((ui->cBoxFetchPro->currentIndex()==2)?1:0)) << 14;
        vacbmp |= ((quint16)((ui->cBoxFetchPro->currentIndex()==3)?1:0)) << 1;
        vacbmp |= ((quint16)((ui->cBoxFetchPro->currentIndex()==4)?1:0)) << 2;
        vacbmp |= ((quint16)((ui->cBoxFetchPro->currentIndex()==5)?1:0)) << 3;
        vacbmp |= ((quint16)((ui->cBoxFetchPro->currentIndex()==6)?1:0)) << 4;
        vacbmp |= ((quint16)((ui->cBoxFetchPro->currentIndex()==7)?1:0)) << 5;
        vacbmp |= ((quint16)((ui->cBoxFetchPro->currentIndex()==8)?1:0)) << 8;
        vacbmp |= ((quint16)((ui->cBoxFetchPro->currentIndex()==9)?1:0)) << 9;
        vacbmp |= ((quint16)((ui->cBoxFetchPro->currentIndex()==10)?1:0)) << 10;
        vacbmp |= ((quint16)((ui->cBoxFetchPro->currentIndex()==11)?1:0)) << 11;
        vacbmp |= ((quint16)((ui->cBoxFetchPro->currentIndex()==12)?1:0)) << 15;

        vacbmp |= ((quint16)((ui->cBoxFetchRun->currentIndex()==0)?1:0)) << 28;
        vacbmp |= ((quint16)((ui->cBoxFetchRun->currentIndex()==1)?1:0)) << 29;
        vacbmp |= ((quint16)((ui->cBoxFetchRun->currentIndex()==2)?1:0)) << 30;
        vacbmp |= ((quint16)((ui->cBoxFetchRun->currentIndex()==3)?1:0)) << 17;
        vacbmp |= ((quint16)((ui->cBoxFetchRun->currentIndex()==4)?1:0)) << 18;
        vacbmp |= ((quint16)((ui->cBoxFetchRun->currentIndex()==5)?1:0)) << 19;
        vacbmp |= ((quint16)((ui->cBoxFetchRun->currentIndex()==6)?1:0)) << 20;
        vacbmp |= ((quint16)((ui->cBoxFetchRun->currentIndex()==7)?1:0)) << 21;
        vacbmp |= ((quint16)((ui->cBoxFetchRun->currentIndex()==8)?1:0)) << 24;
        vacbmp |= ((quint16)((ui->cBoxFetchRun->currentIndex()==9)?1:0)) << 25;
        vacbmp |= ((quint16)((ui->cBoxFetchRun->currentIndex()==10)?1:0)) << 26;
        vacbmp |= ((quint16)((ui->cBoxFetchRun->currentIndex()==11)?1:0)) << 27;
        vacbmp |= ((quint16)((ui->cBoxFetchRun->currentIndex()==12)?1:0)) << 31;
    }
    else
    {
        vacbmp  = ((quint16)((ui->cBoxFetchPro->currentIndex()==0)?1:0)) << 0;
        vacbmp |= ((quint16)((ui->cBoxFetchPro->currentIndex()==1)?1:0)) << 1;
        vacbmp |= ((quint16)((ui->cBoxFetchPro->currentIndex()==2)?1:0)) << 2;
        vacbmp |= ((quint16)((ui->cBoxFetchPro->currentIndex()==3)?1:0)) << 3;
        vacbmp |= ((quint16)((ui->cBoxFetchPro->currentIndex()==4)?1:0)) << 4;
        vacbmp |= ((quint16)((ui->cBoxFetchPro->currentIndex()==5)?1:0)) << 5;
        vacbmp |= ((quint16)((ui->cBoxFetchPro->currentIndex()==6)?1:0)) << 6;
        vacbmp |= ((quint16)((ui->cBoxFetchPro->currentIndex()==7)?1:0)) << 7;
        vacbmp |= ((quint16)((ui->cBoxFetchPro->currentIndex()==8)?1:0)) << 8;
        vacbmp |= ((quint16)((ui->cBoxFetchPro->currentIndex()==9)?1:0)) << 9;
        vacbmp |= ((quint16)((ui->cBoxFetchPro->currentIndex()==10)?1:0)) << 10;
        vacbmp |= ((quint16)((ui->cBoxFetchPro->currentIndex()==11)?1:0)) << 11;
        vacbmp |= ((quint16)((ui->cBoxFetchPro->currentIndex()==12)?1:0)) << 12;
        vacbmp |= ((quint16)((ui->cBoxFetchPro->currentIndex()==13)?1:0)) << 13;

        vacbmp |= ((quint16)((ui->cBoxFetchRun->currentIndex()==0)?1:0)) << 16;
        vacbmp |= ((quint16)((ui->cBoxFetchRun->currentIndex()==1)?1:0)) << 17;
        vacbmp |= ((quint16)((ui->cBoxFetchRun->currentIndex()==2)?1:0)) << 18;
        vacbmp |= ((quint16)((ui->cBoxFetchRun->currentIndex()==3)?1:0)) << 19;
        vacbmp |= ((quint16)((ui->cBoxFetchRun->currentIndex()==4)?1:0)) << 20;
        vacbmp |= ((quint16)((ui->cBoxFetchRun->currentIndex()==5)?1:0)) << 21;
        vacbmp |= ((quint16)((ui->cBoxFetchRun->currentIndex()==6)?1:0)) << 22;
        vacbmp |= ((quint16)((ui->cBoxFetchRun->currentIndex()==7)?1:0)) << 23;
        vacbmp |= ((quint16)((ui->cBoxFetchRun->currentIndex()==8)?1:0)) << 24;
        vacbmp |= ((quint16)((ui->cBoxFetchRun->currentIndex()==9)?1:0)) << 25;
        vacbmp |= ((quint16)((ui->cBoxFetchRun->currentIndex()==10)?1:0)) << 26;
        vacbmp |= ((quint16)((ui->cBoxFetchRun->currentIndex()==11)?1:0)) << 27;
        vacbmp |= ((quint16)((ui->cBoxFetchRun->currentIndex()==12)?1:0)) << 28;
        vacbmp |= ((quint16)((ui->cBoxFetchRun->currentIndex()==13)?1:0)) << 29;
    }
    return vacbmp;
}

void FormBtnQuick::UpdateWidgetState()
{

    ui->cBoxFetchPro->setEnabled(ui->checkBoxPA->isChecked());
    ui->checkBoxFetchPro->setEnabled(ui->checkBoxPA->isChecked());
    ui->checkBoxWaitRotate->setEnabled(ui->checkBoxPA->isChecked());
    ui->BoxWaitPHor->setEnabled(ui->checkBoxPA->isChecked());
    ui->BoxWaitPVer->setEnabled(ui->checkBoxPA->isChecked());
    ui->BoxFetchPHor->setEnabled(ui->checkBoxPA->isChecked());
    ui->BoxFetchPVer->setEnabled(ui->checkBoxPA->isChecked());
    ui->checkBoxProductRotate->setEnabled(ui->checkBoxPA->isChecked());
    ui->BoxProductTrv->setEnabled(ui->checkBoxPA->isChecked());
    ui->BtnProductSync->setEnabled(ui->checkBoxPA->isChecked());
    ui->BtnFetchSync->setEnabled((ui->checkBoxPA->isChecked())||(ui->checkBoxRA->isChecked()));
    ui->BoxProductPHor->setEnabled(ui->checkBoxPA->isChecked());
    ui->BoxProductPVer->setEnabled(ui->checkBoxPA->isChecked());

    ui->cBoxFetchRun->setEnabled(ui->checkBoxRA->isEnabled() && (ui->checkBoxRA->isChecked()));
    ui->labelFetchRun->setEnabled(ui->checkBoxRA->isEnabled() && (ui->checkBoxRA->isChecked()));
    ui->checkBoxFetchRun->setEnabled(ui->checkBoxRA->isEnabled() && (ui->checkBoxRA->isChecked()));
    ui->BoxWaitRHor->setEnabled(ui->checkBoxRA->isEnabled() && (ui->checkBoxRA->isChecked()));
    ui->BoxWaitRVer->setEnabled(ui->checkBoxRA->isEnabled() && (ui->checkBoxRA->isChecked()));
    ui->labelWaitRHor->setEnabled(ui->checkBoxRA->isEnabled() && (ui->checkBoxRA->isChecked()));
    ui->labelWaitRVer->setEnabled(ui->checkBoxRA->isEnabled() && (ui->checkBoxRA->isChecked()));
    ui->BoxFetchRHor->setEnabled(ui->checkBoxRA->isEnabled() && (ui->checkBoxRA->isChecked()));
    ui->BoxFetchRVer->setEnabled(ui->checkBoxRA->isEnabled() && (ui->checkBoxRA->isChecked()));
    ui->labelFetchRHor->setEnabled(ui->checkBoxRA->isEnabled() && (ui->checkBoxRA->isChecked()));
    ui->labelFetchRVer->setEnabled(ui->checkBoxRA->isEnabled() && (ui->checkBoxRA->isChecked()));
    ui->checkBoxWasteRotate->setEnabled(ui->checkBoxRA->isEnabled() && (ui->checkBoxRA->isChecked()));
    ui->BoxWasteTrv->setEnabled(ui->checkBoxRA->isEnabled() && (ui->checkBoxRA->isChecked()));
    ui->checkBoxWasteRotateFirst->setEnabled(ui->checkBoxRA->isEnabled() && (ui->checkBoxRA->isChecked()));
    ui->BoxWasteRVer->setEnabled(ui->checkBoxRA->isEnabled() && (ui->checkBoxRA->isChecked()));
    ui->BoxWasteRHor->setEnabled(ui->checkBoxRA->isEnabled() && (ui->checkBoxRA->isChecked()));
    ui->labelWasteRVer->setEnabled(ui->checkBoxRA->isEnabled() && (ui->checkBoxRA->isChecked()));
    ui->labelWasteRHor->setEnabled(ui->checkBoxRA->isEnabled() && (ui->checkBoxRA->isChecked()));
    ui->labelWaitRarm->setEnabled(pModbus->GetRunnerUse()&&ui->checkBoxRA->isChecked());
    ui->btnAdv->setEnabled(pModbus->GetRunnerUse()&&ui->checkBoxRA->isChecked());
    ui->btnRet->setEnabled(pModbus->GetRunnerUse()&&ui->checkBoxRA->isChecked());
    ui->btnAdv_2->setEnabled(pModbus->GetRunnerUse()&&ui->checkBoxRA->isChecked());
    ui->btnRet_2->setEnabled(pModbus->GetRunnerUse()&&ui->checkBoxRA->isChecked());
    ui->btnAsc->setEnabled(pModbus->GetRunnerUse()&&ui->checkBoxRA->isChecked());
    ui->btnAsc_2->setEnabled(pModbus->GetRunnerUse()&&ui->checkBoxRA->isChecked());
    ui->btnDec->setEnabled(pModbus->GetRunnerUse()&&ui->checkBoxRA->isChecked());
    ui->btnDec_2->setEnabled(pModbus->GetRunnerUse()&&ui->checkBoxRA->isChecked());
    ui->labelWaitRarm->setEnabled(pModbus->GetRunnerUse()&&ui->checkBoxRA->isChecked());

    ui->btnRet->setOn(xIoPort::GetOut(RBT_VAR_OUT_RUN_RET));
    ui->btnAdv->setOn(!xIoPort::GetOut(RBT_VAR_OUT_RUN_RET));
    ui->btnRet_2->setOn(xIoPort::GetOut(RBT_VAR_OUT_RUN_RET));
    ui->btnAdv_2->setOn(!xIoPort::GetOut(RBT_VAR_OUT_RUN_RET));
    ui->btnAsc->setOn(!xIoPort::GetOut(RBT_VAR_OUT_RUN_DES));
    ui->btnAsc_2->setOn(!xIoPort::GetOut(RBT_VAR_OUT_RUN_DES));
    ui->btnDec->setOn(xIoPort::GetOut(RBT_VAR_OUT_RUN_DES));
    ui->btnDec_2->setOn(xIoPort::GetOut(RBT_VAR_OUT_RUN_DES));
    checkRAStateChanged(0);
}
void FormBtnQuick::syncWaitPos(void)
{
    m_wait_xpos = CMBProtocol::GetPaHorPos();
    ui->BoxWaitPHor->setText(QString::number((double)m_wait_xpos / 100.00));
    m_wait_ypos = CMBProtocol::GetPaVerPos();
    ui->BoxWaitPVer->setText(QString::number((double)m_wait_ypos / 100.00));
    m_wait_zpos = CMBProtocol::GetTravelPos();
    ui->BoxWaitTrv->setText(QString::number((double)m_wait_zpos / 100.00));
    m_wait_bpos = CMBProtocol::GetRaHorPos();
    ui->BoxWaitRHor->setText(QString::number((double)m_wait_bpos / 100.00));
    m_wait_apos = CMBProtocol::GetRaVerPos();
    ui->BoxWaitRVer->setText(QString::number((double)m_wait_apos / 100.00));
}
void FormBtnQuick::syncFetchPos(void)
{
    m_fetch_xpos = CMBProtocol::GetPaHorPos();
    ui->BoxFetchPHor->setText(QString::number((double)m_fetch_xpos / 100.00));
    m_fetch_ypos = CMBProtocol::GetPaVerPos();
    ui->BoxFetchPVer->setText(QString::number((double)m_fetch_ypos / 100.00));
//    m_fetch_zpos = CMBProtocol::GetTravelPos();
//    ui->BoxFetchTrv->setText(QString::number((double)m_fetch_zpos / 100.00));
    m_fetch_bpos = CMBProtocol::GetRaHorPos();
    ui->BoxFetchRHor->setText(QString::number((double)m_fetch_bpos / 100.00));
    m_fetch_apos = CMBProtocol::GetRaVerPos();
    ui->BoxFetchRVer->setText(QString::number((double)m_fetch_apos / 100.00));
}
void FormBtnQuick::syncProductPos(void)
{
    m_product_xpos = CMBProtocol::GetPaHorPos();
    ui->BoxProductPHor->setText(QString::number((double)m_product_xpos / 100.00));
    m_product_ypos = CMBProtocol::GetPaVerPos();
    ui->BoxProductPVer->setText(QString::number((double)m_product_ypos / 100.00));
    m_product_zpos = CMBProtocol::GetTravelPos();
    ui->BoxProductTrv->setText(QString::number((double)m_product_zpos / 100.00));
}
void FormBtnQuick::syncWastePos(void)
{
    m_waste_zpos = CMBProtocol::GetTravelPos();
    ui->BoxWasteTrv->setText(QString::number((double)m_waste_zpos / 100.00));
    m_waste_bpos = CMBProtocol::GetRaHorPos();
    ui->BoxWasteRHor->setText(QString::number((double)m_waste_bpos / 100.00));
    m_waste_apos = CMBProtocol::GetRaVerPos();
    ui->BoxWasteRVer->setText(QString::number((double)m_waste_apos / 100.00));
}
void FormBtnQuick::inputWaitPaHor(void)
{
    int type = POS_TYPE_POINT;
    DialogNumberPad numberPad;
    double value;
#if PENDANT_PROTOCOL
    if ((CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4) || (!CMBProtocol::GetRhorSrvUse()))
    {
        if (numberPad.DoForm(type, value, 0.00, CMBProtocol::GetHorLen() / 100.00) != QDialog::Accepted)
            return;
    }
    else
    {
        if (numberPad.DoForm(type, value, 0.00, (CMBProtocol::GetHorLen()-CMBProtocol::GetHorInt()) / 100.00) != QDialog::Accepted)
            return;
    }
#else
    if (numberPad.DoForm(type, value, 0.00, MAX_DISTANCE / 100.00) != QDialog::Accepted)
        return;
#endif
    if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
    {
        m_wait_xtype = type;
        switch(type)
        {
        case POS_TYPE_CAT:
            ui->BoxWaitPHor->setText(tr("取物点"));
            break;
        case POS_TYPE_REL:
            ui->BoxWaitPHor->setText(tr("置物点"));
            break;
        case POS_TYPE_WAIT:
            ui->BoxWaitPHor->setText(tr("待机点"));
            break;
        case POS_TYPE_POINT:
            m_wait_xpos = value * 100;
            ui->BoxWaitPHor->setText(QString::number((double)m_wait_xpos / 100.00));
            break;
        case POS_TYPE_VAR:
            m_wait_xpos = value;
            ui->BoxWaitPHor->setText(xStringResource::GetVarName(VAR_TYPE_USR | m_wait_xpos));
            break;
        }
    }
    else
    {
        if ((m_wait_xtype==POS_TYPE_POINT)&&(type==POS_TYPE_POINT))
        {
            int pos = value * 100;
            int diff = pos - m_wait_xpos;
            if (diff < -500)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
                diff = -500;
            }
            else if (diff > 500)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
                diff = 500;
            }
            m_wait_xpos += diff;
            ui->BoxWaitPHor->setText(QString::number((double)m_wait_xpos / 100.00));
        }
    }
}
void FormBtnQuick::inputWaitPaVer(void)
{
    int type = POS_TYPE_POINT;
    DialogNumberPad numberPad;
    double value;
#if PENDANT_PROTOCOL
    if (numberPad.DoForm(type, value, 0.00, CMBProtocol::GetPaVerLen() / 100.00) != QDialog::Accepted)
#else
    if (numberPad.DoForm(type, value, 0.00, MAX_DISTANCE / 100.00) != QDialog::Accepted)
#endif
        return;
    if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
    {
        m_wait_ytype = type;
        switch(type)
        {
        case POS_TYPE_CAT:
            ui->BoxWaitPVer->setText(tr("取物点"));
            break;
        case POS_TYPE_REL:
            ui->BoxWaitPVer->setText(tr("置物点"));
            break;
        case POS_TYPE_WAIT:
            ui->BoxWaitPVer->setText(tr("待机点"));
            break;
        case POS_TYPE_POINT:
            m_wait_ypos = value * 100;
            ui->BoxWaitPVer->setText(QString::number((double)m_wait_ypos / 100.00));
            break;
        case POS_TYPE_VAR:
            m_wait_ypos = value;
            ui->BoxWaitPVer->setText(xStringResource::GetVarName(VAR_TYPE_USR | m_wait_ypos));
            break;
        }
    }
    else
    {
        if ((m_wait_ytype==POS_TYPE_POINT)&&(type==POS_TYPE_POINT))
        {
            int pos = value * 100;
            int diff = pos - m_wait_ypos;
            if (diff < -500)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
                diff = -500;
            }
            else if (diff > 500)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
                diff = 500;
            }
            m_wait_ypos += diff;
            ui->BoxWaitPVer->setText(QString::number((double)m_wait_ypos / 100.00));
        }
    }
}
void FormBtnQuick::inputWaitTrv(void)
{
    int type = POS_TYPE_POINT;
    DialogNumberPad numberPad;
    double value;
#if PENDANT_PROTOCOL
    if (numberPad.DoForm(type, value, 0.00, CMBProtocol::GetTravLen() / 100.00) != QDialog::Accepted)
#else
    if (numberPad.DoForm(type, value, 0.00, MAX_DISTANCE / 100.00) != QDialog::Accepted)
#endif
        return;
    if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
    {
        m_wait_ztype = type;
        switch(type)
        {
        case POS_TYPE_CAT:
            ui->BoxWaitTrv->setText(tr("取物点"));
            break;
        case POS_TYPE_REL:
            ui->BoxWaitTrv->setText(tr("置物点"));
            break;
        case POS_TYPE_WAIT:
            ui->BoxWaitTrv->setText(tr("待机点"));
            break;
        case POS_TYPE_POINT:
            m_wait_zpos = value * 100;
            ui->BoxWaitTrv->setText(QString::number((double)m_wait_zpos / 100.00));
            break;
        case POS_TYPE_VAR:
            m_wait_zpos = value;
            ui->BoxWaitTrv->setText(xStringResource::GetVarName(VAR_TYPE_USR | m_wait_zpos));
            break;
        }
    }
    else
    {
        if ((m_wait_ztype==POS_TYPE_POINT)&&(type==POS_TYPE_POINT))
        {
            int pos = value * 100;
            int diff = pos - m_wait_zpos;
            if (diff < -500)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
                diff = -500;
            }
            else if (diff > 500)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
                diff = 500;
            }
            m_wait_zpos += diff;
            ui->BoxWaitTrv->setText(QString::number((double)m_wait_zpos / 100.00));
        }
    }
}
void FormBtnQuick::inputWaitRaHor(void)
{
    int type = POS_TYPE_POINT;
    DialogNumberPad numberPad;
    double value;
#if PENDANT_PROTOCOL
    if ((CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4))
    {
        if (numberPad.DoForm(type, value, 0.00, CMBProtocol::GetHorInt() / 100.00) != QDialog::Accepted)
            return;
    }
    else
    {
        if (numberPad.DoForm(type, value, 0.00, CMBProtocol::GetHorLen() / 100.00) != QDialog::Accepted)
            return;
    }
#else
    if (numberPad.DoForm(type, value, 0.00, MAX_DISTANCE / 100.00) != QDialog::Accepted)
        return;
#endif
    if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
    {
        m_wait_btype = type;
        switch(type)
        {
        case POS_TYPE_CAT:
            ui->BoxWaitRHor->setText(tr("取物点"));
            break;
        case POS_TYPE_REL:
            ui->BoxWaitRHor->setText(tr("置物点"));
            break;
        case POS_TYPE_WAIT:
            ui->BoxWaitRHor->setText(tr("待机点"));
            break;
        case POS_TYPE_POINT:
            m_wait_bpos = value * 100;
            ui->BoxWaitRHor->setText(QString::number((double)m_wait_bpos / 100.00));
            break;
        case POS_TYPE_VAR:
            m_wait_bpos = value;
            ui->BoxWaitRHor->setText(xStringResource::GetVarName(VAR_TYPE_USR | m_wait_bpos));
            break;
        }
    }
    else
    {
        if ((m_wait_btype==POS_TYPE_POINT)&&(type==POS_TYPE_POINT))
        {
            int pos = value * 100;
            int diff = pos - m_wait_bpos;
            if (diff < -500)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
                diff = -500;
            }
            else if (diff > 500)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
                diff = 500;
            }
            m_wait_bpos += diff;
            ui->BoxWaitRHor->setText(QString::number((double)m_wait_bpos / 100.00));
        }
    }
}
void FormBtnQuick::inputWaitRaVer(void)
{
    int type = POS_TYPE_POINT;
    DialogNumberPad numberPad;
    double value;
#if PENDANT_PROTOCOL
    if (numberPad.DoForm(type, value, 0.00, CMBProtocol::GetRaVerLen() / 100.00) != QDialog::Accepted)
#else
    if (numberPad.DoForm(type, value, 0.00, MAX_DISTANCE / 100.00) != QDialog::Accepted)
#endif
        return;
    if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
    {
        m_wait_atype = type;
        switch(type)
        {
        case POS_TYPE_CAT:
            ui->BoxWaitRVer->setText(tr("取物点"));
            break;
        case POS_TYPE_REL:
            ui->BoxWaitRVer->setText(tr("置物点"));
            break;
        case POS_TYPE_WAIT:
            ui->BoxWaitRVer->setText(tr("待机点"));
            break;
        case POS_TYPE_POINT:
            m_wait_apos = value * 100;
            ui->BoxWaitRVer->setText(QString::number((double)m_wait_apos / 100.00));
            break;
        case POS_TYPE_VAR:
            m_wait_apos = value;
            ui->BoxWaitRVer->setText(xStringResource::GetVarName(VAR_TYPE_USR | m_wait_apos));
            break;
        }
    }
    else
    {
        if ((m_wait_atype==POS_TYPE_POINT)&&(type==POS_TYPE_POINT))
        {
            int pos = value * 100;
            int diff = pos - m_wait_apos;
            if (diff < -500)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
                diff = -500;
            }
            else if (diff > 500)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
                diff = 500;
            }
            m_wait_apos += diff;
            ui->BoxWaitRVer->setText(QString::number((double)m_wait_apos / 100.00));
        }
    }
}
void FormBtnQuick::inputFetchPaHor(void)
{
    int type = POS_TYPE_POINT;
    DialogNumberPad numberPad;
    double value;
#if PENDANT_PROTOCOL
    if ((CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4) || (!CMBProtocol::GetRhorSrvUse()))
    {
        if (numberPad.DoForm(type, value, 0.00, CMBProtocol::GetHorLen() / 100.00) != QDialog::Accepted)
            return;
    }
    else
    {
        if (numberPad.DoForm(type, value, 0.00, (CMBProtocol::GetHorLen()-CMBProtocol::GetHorInt()) / 100.00) != QDialog::Accepted)
            return;
    }
#else
    if (numberPad.DoForm(type, value, 0.00, MAX_DISTANCE / 100.00) != QDialog::Accepted)
        return;
#endif
    if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
    {
        m_fetch_xtype = type;
        switch(type)
        {
        case POS_TYPE_CAT:
            ui->BoxFetchPHor->setText(tr("取物点"));
            break;
        case POS_TYPE_REL:
            ui->BoxFetchPHor->setText(tr("置物点"));
            break;
        case POS_TYPE_WAIT:
            ui->BoxFetchPHor->setText(tr("待机点"));
            break;
        case POS_TYPE_POINT:
            m_fetch_xpos = value * 100;
            ui->BoxFetchPHor->setText(QString::number((double)m_fetch_xpos / 100.00));
            break;
        case POS_TYPE_VAR:
            m_fetch_xpos = value;
            ui->BoxFetchPHor->setText(xStringResource::GetVarName(VAR_TYPE_USR | m_fetch_xpos));
            break;
        }
    }
    else
    {
        if ((m_fetch_xtype==POS_TYPE_POINT)&&(type==POS_TYPE_POINT))
        {
            int pos = value * 100;
            int diff = pos - m_fetch_xpos;
            if (diff < -500)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
                diff = -500;
            }
            else if (diff > 500)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
                diff = 500;
            }
            m_fetch_xpos += diff;
            ui->BoxFetchPHor->setText(QString::number((double)m_fetch_xpos / 100.00));
        }
    }
}
void FormBtnQuick::inputFetchPaVer(void)
{
    int type = POS_TYPE_POINT;
    DialogNumberPad numberPad;
    double value;
#if PENDANT_PROTOCOL
    if (numberPad.DoForm(type, value, 0.00, CMBProtocol::GetPaVerLen() / 100.00) != QDialog::Accepted)
#else
    if (numberPad.DoForm(type, value, 0.00, MAX_DISTANCE / 100.00) != QDialog::Accepted)
#endif
        return;
    if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
    {
        m_fetch_ytype = type;
        switch(type)
        {
        case POS_TYPE_CAT:
            ui->BoxFetchPVer->setText(tr("取物点"));
            break;
        case POS_TYPE_REL:
            ui->BoxFetchPVer->setText(tr("置物点"));
            break;
        case POS_TYPE_WAIT:
            ui->BoxFetchPVer->setText(tr("待机点"));
            break;
        case POS_TYPE_POINT:
            m_fetch_ypos = value * 100;
            ui->BoxFetchPVer->setText(QString::number((double)m_fetch_ypos / 100.00));
            break;
        case POS_TYPE_VAR:
            m_fetch_ypos = value;
            ui->BoxFetchPVer->setText(xStringResource::GetVarName(VAR_TYPE_USR | m_fetch_ypos));
            break;
        }
    }
    else
    {
        if ((m_fetch_ytype==POS_TYPE_POINT)&&(type==POS_TYPE_POINT))
        {
            int pos = value * 100;
            int diff = pos - m_fetch_ypos;
            if (diff < -500)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
                diff = -500;
            }
            else if (diff > 500)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
                diff = 500;
            }
            m_fetch_ypos += diff;
            ui->BoxFetchPVer->setText(QString::number((double)m_fetch_ypos / 100.00));
        }
    }
}
void FormBtnQuick::inputFetchRaHor(void)
{
    int type = POS_TYPE_POINT;
    DialogNumberPad numberPad;
    double value;
#if PENDANT_PROTOCOL
    if ((CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4))
    {
        if (numberPad.DoForm(type, value, 0.00, CMBProtocol::GetHorInt() / 100.00) != QDialog::Accepted)
            return;
    }
    else
    {
        if (numberPad.DoForm(type, value, 0.00, CMBProtocol::GetHorLen() / 100.00) != QDialog::Accepted)
            return;
    }
#else
    if (numberPad.DoForm(type, value, 0.00, MAX_DISTANCE / 100.00) != QDialog::Accepted)
        return;
#endif
    if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
    {
        m_fetch_btype = type;
        switch(type)
        {
        case POS_TYPE_CAT:
            ui->BoxFetchRHor->setText(tr("取物点"));
            break;
        case POS_TYPE_REL:
            ui->BoxFetchRHor->setText(tr("置物点"));
            break;
        case POS_TYPE_WAIT:
            ui->BoxFetchRHor->setText(tr("待机点"));
            break;
        case POS_TYPE_POINT:
            m_fetch_bpos = value * 100;
            ui->BoxFetchRHor->setText(QString::number((double)m_fetch_bpos / 100.00));
            break;
        case POS_TYPE_VAR:
            m_fetch_bpos = value;
            ui->BoxFetchRHor->setText(xStringResource::GetVarName(VAR_TYPE_USR | m_fetch_bpos));
            break;
        }
    }
    else
    {
        if ((m_fetch_btype==POS_TYPE_POINT)&&(type==POS_TYPE_POINT))
        {
            int pos = value * 100;
            int diff = pos - m_fetch_bpos;
            if (diff < -500)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
                diff = -500;
            }
            else if (diff > 500)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
                diff = 500;
            }
            m_fetch_bpos += diff;
            ui->BoxFetchRHor->setText(QString::number((double)m_fetch_bpos / 100.00));
        }
    }
}
void FormBtnQuick::inputFetchRaVer(void)
{
    int type = POS_TYPE_POINT;
    DialogNumberPad numberPad;
    double value;
#if PENDANT_PROTOCOL
    if (numberPad.DoForm(type, value, 0.00, CMBProtocol::GetRaVerLen() / 100.00) != QDialog::Accepted)
#else
    if (numberPad.DoForm(type, value, 0.00, MAX_DISTANCE / 100.00) != QDialog::Accepted)
#endif
        return;
    if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
    {
        m_fetch_atype = type;
        switch(type)
        {
        case POS_TYPE_CAT:
            ui->BoxFetchRVer->setText(tr("取物点"));
            break;
        case POS_TYPE_REL:
            ui->BoxFetchRVer->setText(tr("置物点"));
            break;
        case POS_TYPE_WAIT:
            ui->BoxFetchRVer->setText(tr("待机点"));
            break;
        case POS_TYPE_POINT:
            m_fetch_apos = value * 100;
            ui->BoxFetchRVer->setText(QString::number((double)m_fetch_apos / 100.00));
            break;
        case POS_TYPE_VAR:
            m_fetch_apos = value;
            ui->BoxFetchRVer->setText(xStringResource::GetVarName(VAR_TYPE_USR | m_fetch_apos));
            break;
        }
    }
    else
    {
        if ((m_fetch_atype==POS_TYPE_POINT)&&(type==POS_TYPE_POINT))
        {
            int pos = value * 100;
            int diff = pos - m_fetch_apos;
            if (diff < -500)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
                diff = -500;
            }
            else if (diff > 500)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
                diff = 500;
            }
            m_fetch_apos += diff;
            ui->BoxFetchRVer->setText(QString::number((double)m_fetch_apos / 100.00));
        }
    }
}
void FormBtnQuick::inputProductPaHor(void)
{
    int type = POS_TYPE_POINT;
    DialogNumberPad numberPad;
    double value;
#if PENDANT_PROTOCOL
    if ((CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4) || (!CMBProtocol::GetRhorSrvUse()))
    {
        if (numberPad.DoForm(type, value, 0.00, CMBProtocol::GetHorLen() / 100.00) != QDialog::Accepted)
            return;
    }
    else
    {
        if (numberPad.DoForm(type, value, 0.00, (CMBProtocol::GetHorLen()-CMBProtocol::GetHorInt()) / 100.00) != QDialog::Accepted)
            return;
    }
#else
    if (numberPad.DoForm(type, value, 0.00, MAX_DISTANCE / 100.00) != QDialog::Accepted)
        return;
#endif
    if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
    {
        m_product_xtype = type;
        switch(type)
        {
        case POS_TYPE_CAT:
            ui->BoxProductPHor->setText(tr("取物点"));
            break;
        case POS_TYPE_REL:
            ui->BoxProductPHor->setText(tr("置物点"));
            break;
        case POS_TYPE_WAIT:
            ui->BoxProductPHor->setText(tr("待机点"));
            break;
        case POS_TYPE_POINT:
            m_product_xpos = value * 100;
            ui->BoxProductPHor->setText(QString::number((double)m_product_xpos / 100.00));
            break;
        case POS_TYPE_VAR:
            m_product_xpos = value;
            ui->BoxProductPHor->setText(xStringResource::GetVarName(VAR_TYPE_USR | m_product_xpos));
            break;
        }
    }
    else
    {
        if ((m_product_xtype==POS_TYPE_POINT)&&(type==POS_TYPE_POINT))
        {
            int pos = value * 100;
            int diff = pos - m_product_xpos;
            if (diff < -500)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
                diff = -500;
            }
            else if (diff > 500)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
                diff = 500;
            }
            m_product_xpos += diff;
            ui->BoxProductPHor->setText(QString::number((double)m_product_xpos / 100.00));
        }
    }
}
void FormBtnQuick::inputProductPaVer(void)
{
    int type = POS_TYPE_POINT;
    DialogNumberPad numberPad;
    double value;
#if PENDANT_PROTOCOL
    if (numberPad.DoForm(type, value, 0.00, CMBProtocol::GetPaVerLen() / 100.00) != QDialog::Accepted)
#else
    if (numberPad.DoForm(type, value, 0.00, MAX_DISTANCE / 100.00) != QDialog::Accepted)
#endif
        return;
    if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
    {
        m_product_ytype = type;
        switch(type)
        {
        case POS_TYPE_CAT:
            ui->BoxProductPVer->setText(tr("取物点"));
            break;
        case POS_TYPE_REL:
            ui->BoxProductPVer->setText(tr("置物点"));
            break;
        case POS_TYPE_WAIT:
            ui->BoxProductPVer->setText(tr("待机点"));
            break;
        case POS_TYPE_POINT:
            m_product_ypos = value * 100;
            ui->BoxProductPVer->setText(QString::number((double)m_product_ypos / 100.00));
            break;
        case POS_TYPE_VAR:
            m_product_ypos = value;
            ui->BoxProductPVer->setText(xStringResource::GetVarName(VAR_TYPE_USR | m_product_ypos));
            break;
        }
    }
    else
    {
        if ((m_product_ytype==POS_TYPE_POINT)&&(type==POS_TYPE_POINT))
        {
            int pos = value * 100;
            int diff = pos - m_product_ypos;
            if (diff < -500)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
                diff = -500;
            }
            else if (diff > 500)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
                diff = 500;
            }
            m_product_ypos += diff;
            ui->BoxProductPVer->setText(QString::number((double)m_product_ypos / 100.00));
        }
    }
}
void FormBtnQuick::inputProductTrv(void)
{
    int type = POS_TYPE_POINT;
    DialogNumberPad numberPad;
    double value;
#if PENDANT_PROTOCOL
    if (numberPad.DoForm(type, value, 0.00, CMBProtocol::GetTravLen() / 100.00) != QDialog::Accepted)
#else
    if (numberPad.DoForm(type, value, 0.00, MAX_DISTANCE / 100.00) != QDialog::Accepted)
#endif
        return;
    if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
    {
        m_product_ztype = type;
        switch(type)
        {
        case POS_TYPE_CAT:
            ui->BoxProductTrv->setText(tr("取物点"));
            break;
        case POS_TYPE_REL:
            ui->BoxProductTrv->setText(tr("置物点"));
            break;
        case POS_TYPE_WAIT:
            ui->BoxProductTrv->setText(tr("待机点"));
            break;
        case POS_TYPE_POINT:
            m_product_zpos = value * 100;
            ui->BoxProductTrv->setText(QString::number((double)m_product_zpos / 100.00));
            break;
        case POS_TYPE_VAR:
            m_product_zpos = value;
            ui->BoxProductTrv->setText(xStringResource::GetVarName(VAR_TYPE_USR | m_product_zpos));
            break;
        }
    }
    else
    {
        if ((m_product_ztype==POS_TYPE_POINT)&&(type==POS_TYPE_POINT))
        {
            int pos = value * 100;
            int diff = pos - m_product_zpos;
            if (diff < -500)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
                diff = -500;
            }
            else if (diff > 500)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
                diff = 500;
            }
            m_product_zpos += diff;
            ui->BoxProductTrv->setText(QString::number((double)m_product_zpos / 100.00));
        }
    }
}
void FormBtnQuick::inputWasteTrv(void)
{
    int type = POS_TYPE_POINT;
    DialogNumberPad numberPad;
    double value;
#if PENDANT_PROTOCOL
    if (numberPad.DoForm(type, value, 0.00, CMBProtocol::GetTravLen() / 100.00) != QDialog::Accepted)
#else
    if (numberPad.DoForm(type, value, 0.00, MAX_DISTANCE / 100.00) != QDialog::Accepted)
#endif
        return;
    if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
    {
        m_waste_ztype = type;
        switch(type)
        {
        case POS_TYPE_CAT:
            ui->BoxWasteTrv->setText(tr("取物点"));
            break;
        case POS_TYPE_REL:
            ui->BoxWasteTrv->setText(tr("置物点"));
            break;
        case POS_TYPE_WAIT:
            ui->BoxWasteTrv->setText(tr("待机点"));
            break;
        case POS_TYPE_POINT:
            m_waste_zpos = value * 100;
            ui->BoxWasteTrv->setText(QString::number((double)m_waste_zpos / 100.00));
            break;
        case POS_TYPE_VAR:
            m_waste_zpos = value;
            ui->BoxWasteTrv->setText(xStringResource::GetVarName(VAR_TYPE_USR | m_waste_zpos));
            break;
        }
    }
    else
    {
        if ((m_waste_ztype==POS_TYPE_POINT)&&(type==POS_TYPE_POINT))
        {
            int pos = value * 100;
            int diff = pos - m_waste_zpos;
            if (diff < -500)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
                diff = -500;
            }
            else if (diff > 500)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
                diff = 500;
            }
            m_waste_zpos += diff;
            ui->BoxWasteTrv->setText(QString::number((double)m_waste_zpos / 100.00));
        }
    }
}
void FormBtnQuick::inputWasteRaHor(void)
{
    int type = POS_TYPE_POINT;
    DialogNumberPad numberPad;
    double value;
#if PENDANT_PROTOCOL
    if ((CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4))
    {
        if (numberPad.DoForm(type, value, 0.00, CMBProtocol::GetHorInt() / 100.00) != QDialog::Accepted)
            return;
    }
    else
    {
        if (numberPad.DoForm(type, value, 0.00, CMBProtocol::GetHorLen() / 100.00) != QDialog::Accepted)
            return;
    }
#else
    if (numberPad.DoForm(type, value, 0.00, MAX_DISTANCE / 100.00) != QDialog::Accepted)
        return;
#endif
    if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
    {
        m_waste_btype = type;
        switch(type)
        {
        case POS_TYPE_CAT:
            ui->BoxWasteRHor->setText(tr("取物点"));
            break;
        case POS_TYPE_REL:
            ui->BoxWasteRHor->setText(tr("置物点"));
            break;
        case POS_TYPE_WAIT:
            ui->BoxWasteRHor->setText(tr("待机点"));
            break;
        case POS_TYPE_POINT:
            m_waste_bpos = value * 100;
            ui->BoxWasteRHor->setText(QString::number((double)m_waste_bpos / 100.00));
            break;
        case POS_TYPE_VAR:
            m_waste_bpos = value;
            ui->BoxWasteRHor->setText(xStringResource::GetVarName(VAR_TYPE_USR | m_waste_bpos));
            break;
        }
    }
    else
    {
        if ((m_waste_btype==POS_TYPE_POINT)&&(type==POS_TYPE_POINT))
        {
            int pos = value * 100;
            int diff = pos - m_waste_bpos;
            if (diff < -500)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
                diff = -500;
            }
            else if (diff > 500)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
                diff = 500;
            }
            m_waste_bpos += diff;
            ui->BoxWasteRHor->setText(QString::number((double)m_waste_bpos / 100.00));
        }
    }
}
void FormBtnQuick::inputWasteRaVer(void)
{
    int type = POS_TYPE_POINT;
    DialogNumberPad numberPad;
    double value;
#if PENDANT_PROTOCOL
    if (numberPad.DoForm(type, value, 0.00, CMBProtocol::GetRaVerLen() / 100.00) != QDialog::Accepted)
#else
    if (numberPad.DoForm(type, value, 0.00, MAX_DISTANCE / 100.00) != QDialog::Accepted)
#endif
        return;
    if (CMBProtocol::GetSysState() == SYS_STATE_MANUAL)
    {
        m_waste_atype = type;
        switch(type)
        {
        case POS_TYPE_CAT:
            ui->BoxWasteRVer->setText(tr("取物点"));
            break;
        case POS_TYPE_REL:
            ui->BoxWasteRVer->setText(tr("置物点"));
            break;
        case POS_TYPE_WAIT:
            ui->BoxWasteRVer->setText(tr("待机点"));
            break;
        case POS_TYPE_POINT:
            m_waste_apos = value * 100;
            ui->BoxWasteRVer->setText(QString::number((double)m_waste_apos / 100.00));
            break;
        case POS_TYPE_VAR:
            m_waste_apos = value;
            ui->BoxWasteRVer->setText(xStringResource::GetVarName(VAR_TYPE_USR | m_waste_apos));
            break;
        }
    }
    else
    {
        if ((m_waste_atype==POS_TYPE_POINT)&&(type==POS_TYPE_POINT))
        {
            int pos = value * 100;
            int diff = pos - m_waste_apos;
            if (diff < -500)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
                diff = -500;
            }
            else if (diff > 500)
            {
                xMessageBox::DoWarning(tr("输入有误"), tr("自动时修改位置很危险，每次修改值只能小于+-5mm"));
                diff = 500;
            }
            m_waste_apos += diff;
            ui->BoxWasteRVer->setText(QString::number((double)m_waste_apos / 100.00));
        }
    }
}

int FormBtnQuick::clickPagePrev(void)
{
    m_current_page = ui->stackedWidget->currentIndex();
    if(ui->checkBoxWasteRotateFirst->isChecked() == false)
    {
        //5,4,3,1,2,0
        ui->label_3->setText("5/6");
        ui->label_4->setText("6/6");
        ui->labelPage_2->setText("3/6");
        ui->labelPage_3->setText("2/6");
        if(m_current_page == 5)
        {
            m_current_page = 4;
        }
        else if((!ui->checkBoxPA->isChecked())&&(m_current_page == 4))//5,4, ,1,2,0
        {
            m_current_page = 1;
        }
        else if((ui->checkBoxPA->isChecked())&&(m_current_page == 4))//5,4,3,1,2
        {
            m_current_page = 3;
        }
        else if(m_current_page == 3)
        {
            m_current_page = 1;
        }
        else if(m_current_page == 1)
        {
            m_current_page = 2;
        }
        else if(m_current_page == 2)
        {
            m_current_page = 0;
        }
    }
    else
    {
        //4,5,3,1,2,0
        ui->label_4->setText("5/6");
        ui->label_3->setText("6/6");
        ui->labelPage_2->setText("3/6");
        ui->labelPage_3->setText("2/6");
        if(m_current_page == 4)
        {
            m_current_page  = 5;
        }
        else if((!ui->checkBoxPA->isChecked())&&(m_current_page == 5))//4,5, ,1,2,0
        {
            m_current_page = 1;
        }
        else if((ui->checkBoxPA->isChecked())&&(m_current_page == 5))
        {
            m_current_page = 3;
        }
        else if (m_current_page == 3)
        {
            m_current_page = 1;
        }
        else if (m_current_page == 1)
        {
            m_current_page = 2;
        }
        else if (m_current_page = 2)
        {
            m_current_page = 0;
        }
    }
    ui->stackedWidget->setCurrentIndex(m_current_page);
    return m_current_page;
}
int FormBtnQuick::clickPageNext(void)
{
    m_current_page = ui->stackedWidget->currentIndex();
    if(ui->checkBoxWasteRotateFirst->isChecked() == false)//先放成品
    {
        //0,2,1,3,4,5
        ui->label_3->setText("5/6");
        ui->label_4->setText("6/6");
        ui->labelPage_2->setText("3/6");
        ui->labelPage_3->setText("2/6");
        if(m_current_page == 0)
        {
            m_current_page = 2;
        }
        else if(!ui->checkBoxPA->isChecked() && (m_current_page == 1))//0,2,1,(),4,5
        {
            m_current_page = 4;
        }
        else if(ui->checkBoxPA->isChecked() && (m_current_page == 1))
        {
            m_current_page = 3;
        }
        else if (m_current_page == 3)
        {
            m_current_page = 4;
        }
        else if(m_current_page == 2)
        {
            m_current_page = 1;
        }
        else if (m_current_page == 4)
        {
            m_current_page = 5;
        }
    }
    else    //先放水口
    {
        ui->label_4->setText("5/6");
        ui->label_3->setText("6/6");
        ui->labelPage_2->setText("3/6");
        ui->labelPage_3->setText("2/6");
        //0,2,1,3,5,4
        if(m_current_page == 0)
        {
            m_current_page = 2;
        }
        else if(m_current_page == 2)
        {
            m_current_page = 1;
        }
        else if(m_current_page == 3)
        {
            m_current_page = 5;
        }
        else if(m_current_page == 5)
        {
            m_current_page = 4;
        }
        else if((!ui->checkBoxPA->isChecked())&&(m_current_page == 1))//0,2,1,(),5,4
        {
             m_current_page = 5;
        }
        else if((ui->checkBoxPA->isChecked())&&(m_current_page == 1))
        {
            m_current_page = 3;
        }
    }
    ui->stackedWidget->setCurrentIndex(m_current_page);
    return m_current_page;
}

bool FormBtnQuick::GetRarmWaitState_ADV()
{
    if(ui->labelWaitRarmState->text() == tr("前进"))
        return true;
    else
        return false;
}

bool FormBtnQuick::GetRarmFetch_adv()
{
	if(ui->labelFetchRarmState->text() == tr("前进"))
		return true;
	else
		return false;
}

bool FormBtnQuick::GetRunnerWasterState()
{
	if(ui->labelWasteState->text() == tr("下降"))
		return true;
	else
		return false;
}

void FormBtnQuick::checkPAStateChanged(int idx)
{
    if (ui->checkBoxPA->isChecked())
    {
        ui->checkBoxWaitRotate->setEnabled(true);
        ui->BoxWaitPHor->setEnabled(true);
        ui->BoxWaitPVer->setEnabled(true);
        ui->BoxFetchPHor->setEnabled(true);
        ui->BoxFetchPVer->setEnabled(true);
        ui->checkBoxProductRotate->setEnabled(true);
        ui->BoxProductTrv->setEnabled(true);
        ui->BoxProductPHor->setEnabled(true);
        ui->BoxProductPVer->setEnabled(true);
        ui->cBoxFetchPro->setEnabled(true);
        ui->checkBoxFetchPro->setEnabled(true);
    }
    else
    {
        ui->checkBoxWaitRotate->setEnabled(false);
        ui->BoxWaitPHor->setEnabled(false);
        ui->BoxWaitPVer->setEnabled(false);
        ui->BoxFetchPHor->setEnabled(false);
        ui->BoxFetchPVer->setEnabled(false);
        ui->checkBoxProductRotate->setEnabled(false);
        ui->BoxProductTrv->setEnabled(false);
        ui->BoxProductPHor->setEnabled(false);
        ui->BoxProductPVer->setEnabled(false);
        ui->cBoxFetchPro->setEnabled(false);
        ui->checkBoxFetchPro->setEnabled(false);
    }
    ui->BtnWaitSync->setEnabled((ui->checkBoxPA->isChecked())||(ui->checkBoxRA->isChecked()));
    ui->BtnProductSync->setEnabled(ui->checkBoxPA->isChecked());
    ui->BtnFetchSync->setEnabled((ui->checkBoxPA->isChecked())||(ui->checkBoxRA->isChecked()));

}
void FormBtnQuick::checkRAStateChanged(int idx)
{
    if (ui->checkBoxRA->isChecked())
    {
        ui->BoxWaitRHor->setEnabled(true);
        ui->BoxWaitRVer->setEnabled(true);
        ui->BoxFetchRVer->setEnabled(true);
        ui->BoxFetchRHor->setEnabled(true);
        ui->checkBoxWasteRotate->setEnabled(true);
        ui->BoxWasteTrv->setEnabled(true);
        ui->BoxWasteRHor->setEnabled(true);
        ui->BoxWasteRVer->setEnabled(true);
        ui->cBoxFetchRun->setEnabled(true);
        ui->checkBoxFetchRun->setEnabled(true);
        ui->checkBoxWasteRotateFirst->setEnabled(true);

        ui->labelWaitRHor->setEnabled(true);
        ui->labelWaitRVer->setEnabled(true);
        ui->labelWasteRHor->setEnabled(true);
        ui->labelWasteRVer->setEnabled(true);
        ui->labelFetchRun->setEnabled(true);
        ui->labelFetchRHor->setEnabled(true);
        ui->labelFetchRVer->setEnabled(true);
        ui->labelWasteTrv->setEnabled(true);

        if(pModbus->GetRunnerUse())
        {
            ui->btnAdv->setEnabled(true);
            ui->btnRet->setEnabled(true);
            ui->btnAdv_2->setEnabled(true);
            ui->btnRet_2->setEnabled(true);
            ui->btnAsc->setEnabled(true);
            ui->btnAsc_2->setEnabled(true);
            ui->btnDec->setEnabled(true);
            ui->btnDec_2->setEnabled(true);
            ui->labelWaitRarm->setEnabled(true);
            ui->labelWaitRarmState->setEnabled(true);
            ui->labelWasteState->setEnabled(true);
            ui->labelWaste_2->setEnabled(true);
            ui->labelFetchRarmState->setEnabled(true);
            ui->labelFetchRarm->setEnabled(true);
            ui->stackedWidget_fetch->setCurrentIndex(1);
            ui->BoxWaitRHor->setEnabled(false);
            ui->BoxWaitRVer->setEnabled(false);
            ui->labelWaitRHor->setEnabled(false);
            ui->labelWaitRVer->setEnabled(false);
            ui->BoxWasteRHor->setEnabled(false);
            ui->BoxWasteRVer->setEnabled(false);
            ui->labelWasteRHor->setEnabled(false);
            ui->labelWasteRVer->setEnabled(false);
        }
        else
        {
            ui->btnAdv->setEnabled(false);
            ui->btnRet->setEnabled(false);
            ui->btnAdv_2->setEnabled(false);
            ui->btnRet_2->setEnabled(false);
            ui->btnAsc->setEnabled(false);
            ui->btnAsc_2->setEnabled(false);
            ui->btnDec->setEnabled(false);
            ui->btnDec_2->setEnabled(false);
            ui->labelWaitRarm->setEnabled(false);
            ui->labelWaitRarmState->setEnabled(false);
            ui->labelWasteState->setEnabled(false);
            ui->labelWaste_2->setEnabled(false);
            ui->labelFetchRarmState->setEnabled(false);
            ui->labelFetchRarm->setEnabled(false);
            ui->stackedWidget_fetch->setCurrentIndex(0);
            ui->BoxWaitRHor->setEnabled(true);
            ui->BoxWaitRVer->setEnabled(true);
            ui->labelWaitRHor->setEnabled(true);
            ui->labelWaitRVer->setEnabled(true);
            ui->BoxWasteRHor->setEnabled(true);
            ui->BoxWasteRVer->setEnabled(true);
            ui->labelWasteRHor->setEnabled(true);
            ui->labelWasteRVer->setEnabled(true);
        }
    }
    else
    {
        ui->BoxWaitRHor->setEnabled(false);
        ui->BoxWaitRVer->setEnabled(false);
        ui->BoxFetchRVer->setEnabled(false);
        ui->BoxFetchRHor->setEnabled(false);
        ui->checkBoxWasteRotate->setEnabled(false);
        ui->BoxWasteTrv->setEnabled(false);
        ui->BoxWasteRHor->setEnabled(false);
        ui->BoxWasteRVer->setEnabled(false);
        ui->cBoxFetchRun->setEnabled(false);
        ui->checkBoxFetchRun->setEnabled(false);
        ui->checkBoxWasteRotateFirst->setEnabled(false);
        ui->labelWaitRHor->setEnabled(false);
        ui->labelWaitRVer->setEnabled(false);
        ui->labelWasteRHor->setEnabled(false);
        ui->labelWasteRVer->setEnabled(false);
        ui->labelFetchRun->setEnabled(false);
        ui->labelFetchRHor->setEnabled(false);
        ui->labelFetchRVer->setEnabled(false);
        ui->labelWasteTrv->setEnabled(false);
        ui->btnAdv->setEnabled(false);
        ui->btnRet->setEnabled(false);
        ui->btnAdv_2->setEnabled(false);
        ui->btnRet_2->setEnabled(false);
        ui->btnAsc->setEnabled(false);
        ui->btnAsc_2->setEnabled(false);
        ui->btnDec->setEnabled(false);
        ui->btnDec_2->setEnabled(false);
        ui->labelWaitRarm->setEnabled(false);
        ui->labelWaitRarmState->setEnabled(false);
        ui->labelWasteState->setEnabled(false);
        ui->labelWaste_2->setEnabled(false);
        ui->labelFetchRarmState->setEnabled(false);
        ui->labelFetchRarm->setEnabled(false);
    }
    ui->BtnWaitSync->setEnabled((ui->checkBoxPA->isChecked())||(ui->checkBoxRA->isChecked()));
    ui->BtnWasteSync->setEnabled((ui->checkBoxRA->isChecked()));
    ui->BtnFetchSync->setEnabled((ui->checkBoxPA->isChecked())||(ui->checkBoxRA->isChecked()));


    {
//        ui->cBoxFetchRun->setEnabled(ischecked);
//        ui->checkBoxFetchRun->setEnabled(ischecked);
//        ui->labelFetchRun->setEnabled(ischecked);
//        ui->checkBoxWasteRotateFirst->setEnabled(ischecked);
//        ui->BoxWasteTrv->setEnabled(ischecked);
//        ui->labelWasteTrv->setEnabled(ischecked);
//        ui->BtnWasteSync->setEnabled((ui->checkBoxRunnerUse->isChecked())||(ui->checkBoxRA->isChecked()));
//        ui->BoxWaitRHor->setEnabled(!ischecked);
//        ui->BoxWaitRVer->setEnabled(!ischecked);
//        ui->BoxFetchRHor->setEnabled(!ischecked);
//        ui->BoxFetchRVer->setEnabled(!ischecked);
//        ui->BoxWasteRHor->setEnabled(!ischecked);
//        ui->BoxWasteRVer->setEnabled(!ischecked);
//        ui->labelWaitRHor->setEnabled(!ischecked);
//        ui->labelWaitRVer->setEnabled(!ischecked);
//        ui->labelWasteRHor->setEnabled(!ischecked);
//        ui->labelWasteRVer->setEnabled(!ischecked);
    }
}
void FormBtnQuick::checkMatrixChanged(int idx)
{
    if (ui->checkBoxMatrix->isChecked())
    {
        ui->checkBoxProductRotate->setEnabled(false);
        ui->BoxProductTrv->setEnabled(false);
        ui->BoxProductPHor->setEnabled(false);
        ui->BoxProductPVer->setEnabled(false);
        ui->BtnProductSync->setEnabled(false);
    }
    else
    {
        ui->checkBoxProductRotate->setEnabled(true);
        ui->BoxProductTrv->setEnabled(true);
        ui->BoxProductPHor->setEnabled(true);
        ui->BoxProductPVer->setEnabled(true);
        ui->BtnProductSync->setEnabled(true);
    }
}

void FormBtnQuick::btnAdvClick()
{
    QObject *btnadv = (QObject *)sender();
    if (pModbus->GetSysState() != SYS_STATE_MANUAL)
        return;
    // 执行手动指令
    if(pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)
    {
        if (xIoPort::GetOut(RBT_VAR_OUT_RUN_ADV))
        {
            pModbus->ManualRun(RUN_ACT_RETURN);
            ui->btnAdv->setOn(false);
            ui->btnRet->setOn(true);
            ui->btnAdv_2->setOn(false);
            ui->btnRet_2->setOn(true);
        }
        else
        {
            pModbus->ManualRun(RUN_ACT_ADVANCE);
            ui->btnAdv->setOn(true);
            ui->btnRet->setOn(false);
            ui->btnAdv_2->setOn(true);
            ui->btnRet_2->setOn(false);
        }
    }
    else
    {
        if (xIoPort::GetOut(RBT_VAR_OUT_RUN_RET) == true)//xIoPort::GetIn(RBT_VAR_IN_RUN_RET)
        {
            pModbus->ManualRun(RUN_ACT_ADVANCE);
            ui->btnAdv->setOn(true);
            ui->btnRet->setOn(false);
            ui->btnAdv_2->setOn(true);
            ui->btnRet_2->setOn(false);
        }
        else
        {
            pModbus->ManualRun(RUN_ACT_RETURN);
            ui->btnAdv->setOn(false);
            ui->btnRet->setOn(true);
            ui->btnAdv_2->setOn(false);
            ui->btnRet_2->setOn(true);
        }
    }
	if(btnadv == ui->btnAdv_2)
	{
		ui->labelFetchRarmState->setText(tr("前进"));
	}
	else if(btnadv == ui->btnAdv)
	{
		ui->labelWaitRarmState->setText(tr("前进"));
	}
	else if(btnadv == ui->btnRet_2)
	{
		ui->labelFetchRarmState->setText(tr("后退"));
	}
	else if(btnadv == ui->btnRet)
	{
		ui->labelWaitRarmState->setText(tr("后退"));
	}

}

void FormBtnQuick::btnAscClick()
{
	QObject *asc = (QObject*)sender();
    if (pModbus->GetSysState() != SYS_STATE_MANUAL)
        return;
    if (xIoPort::GetOut(RBT_VAR_OUT_RUN_DES) == true)
    {
        pModbus->ManualRun(RUN_ACT_ASCENT);
        ui->btnAsc->setOn(true);
        ui->btnAsc_2->setOn(true);
        ui->btnDec->setOn(false);
        ui->btnDec_2->setOn(false);
    }
    else
    {
        pModbus->ManualRun(RUN_ACT_DESCENT);
        ui->btnAsc->setOn(false);
        ui->btnAsc_2->setOn(false);
        ui->btnDec->setOn(true);
        ui->btnDec_2->setOn(true);
    }
	if(asc == ui->btnAsc_2)
	{
		ui->labelWasteState->setText(tr("上升"));
	}
    else if(asc == ui->btnDec_2)
	{
		ui->labelWasteState->setText(tr("下降"));
	}
}

void FormBtnQuick::checkBoxRunnerUseStateChanged(int ischecked)
{
}

void FormBtnQuick::OutputIO()
{
    if(!pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)
    {
        ui->btnAsc->setOn(!xIoPort::GetOut(RBT_VAR_OUT_RUN_DES));
        ui->btnAsc_2->setOn(!xIoPort::GetOut(RBT_VAR_OUT_RUN_DES));
        ui->btnDec->setOn(xIoPort::GetOut(RBT_VAR_OUT_RUN_DES));
        ui->btnDec_2->setOn(xIoPort::GetOut(RBT_VAR_OUT_RUN_DES));
        ui->btnAdv->setOn(!xIoPort::GetOut(RBT_VAR_OUT_RUN_RET));
        ui->btnAdv_2->setOn(!xIoPort::GetOut(RBT_VAR_OUT_RUN_RET));
        ui->btnRet->setOn(xIoPort::GetOut(RBT_VAR_OUT_RUN_RET));
        ui->btnRet_2->setOn(xIoPort::GetOut(RBT_VAR_OUT_RUN_RET));
    }
}
