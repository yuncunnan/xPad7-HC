#include "xconfig.h"
#include "xpermissions.h"
#include "forminformation.h"
#include "ui_forminformation.h"
#if defined(Q_WS_QWS)
#include <sys/utsname.h>
#endif
#include <QDebug>

extern BoardType BoardType_T;

Forminformation::Forminformation(CMBProtocol *modbus, QWidget *parent) : QWidget(parent), ui(new Ui::Forminformation)
{
	ui->setupUi(this);
    retranslateUi();
	pModbus = modbus;
}

Forminformation::~Forminformation()
{
	delete ui;
}

void Forminformation::changeEvent(QEvent *e)
{
	QWidget::changeEvent(e);
	switch (e->type()) {
	case QEvent::LanguageChange:
		ui->retranslateUi(this);
        retranslateUi();
		break;
	default:
		break;
	}
}
void Forminformation::retranslateUi(void)
{
}

bool Forminformation::EnterForm(void)
{
    // Set the frame background image
    ui->frameInformation->setStyleSheet(QString::null);
    ui->frameInformation->setStyleSheet("QFrame#frameInformation { border-image: url(\"img/Information.png\"); }");
    // Set the vertion string background color
    setStyleSheet("QLabel" \
                "{" \
                    "color: white;" \
                    "background-color: rgba(0, 0, 0, 180);" \
				  "font-size:28px;"\
                "}");
    // Set the system version information
    QString strArm;
    if(pModbus->GetSysTypeHigh() == BOARD_VERSION_ECAT)
    {
        if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4)
            strArm = tr("ECat单臂");
        if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E3)
            strArm = tr("ECat双臂");
        if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_YZ)
            strArm = tr("ECat压铸");
        if ((((pModbus->GetServoNotExist() >> AXES_IDX_A) & 1) == 1) && (((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 1) && (((pModbus->GetServoNotExist() >> AXES_IDX_C) & 1) == 1))
            strArm = tr("ECat新三轴");
        if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)
            strArm = tr("ECat高速三轴");
        if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F3)
            strArm = tr("ECat高速六轴双臂");
        if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4)
            strArm = tr("ECat高速六轴单臂");
        if (pModbus->GetFunctions(SUB_FUN_EUROMAP))
            strArm += tr("ECat-欧规");
    }
    else if(pModbus->GetSysTypeHigh() == BOARD_VERSION_H750_5AXIS)
    {
        if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4)
            strArm = tr("单臂");
        if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E3)
            strArm = tr("双臂");
        if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_YZ)
            strArm = tr("压铸");
        if ((((pModbus->GetServoNotExist() >> AXES_IDX_A) & 1) == 1) && (((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 1) && (((pModbus->GetServoNotExist() >> AXES_IDX_C) & 1) == 1))
            strArm = tr("新三轴");
        if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)
            strArm = tr("高速三轴");
        if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F3)
            strArm = tr("高速五轴双臂");
        if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4)
            strArm = tr("高速五轴单臂");
        if (pModbus->GetFunctions(SUB_FUN_EUROMAP))
            strArm += tr("-欧规");
    }
    else if(pModbus->GetSysTypeHigh() == BOARD_VERSION_H750_6AXIS)
    {
        if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4)
            strArm = tr("单臂");
        if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E3)
            strArm = tr("双臂");
        if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_YZ)
            strArm = tr("压铸");
        if ((((pModbus->GetServoNotExist() >> AXES_IDX_A) & 1) == 1) && (((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 1) && (((pModbus->GetServoNotExist() >> AXES_IDX_C) & 1) == 1))
            strArm = tr("新三轴");
        if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)
            strArm = tr("高速三轴");
        if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F3)
            strArm = tr("高速六轴双臂");
        if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4)
            strArm = tr("高速六轴单臂");
        if (pModbus->GetFunctions(SUB_FUN_EUROMAP))
            strArm += tr("-欧规");
    }
    else if(pModbus->GetSysTypeHigh() == BOARD_VERSION_ECAT_CANOPEN)
    {
        if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4)
            strArm = tr("双总线单臂");
        if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E3)
            strArm = tr("双总线双臂");
        if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_YZ)
            strArm = tr("双总线压铸");
        if ((((pModbus->GetServoNotExist() >> AXES_IDX_A) & 1) == 1) && (((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 1) && (((pModbus->GetServoNotExist() >> AXES_IDX_C) & 1) == 1))
            strArm = tr("双总线新三轴");
        if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)
            strArm = tr("双总线高速三轴");
        if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F3)
            strArm = tr("双总线高速六轴双臂");
        if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4)
            strArm = tr("双总线高速六轴单臂");
        if (pModbus->GetFunctions(SUB_FUN_EUROMAP))
            strArm += tr("双总线-欧规");
    }
    else if(pModbus->GetSysTypeHigh() == BOARD_VERSION_H750_DVS)
    {
        if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4)
            strArm = tr("驱控一体单臂");
        if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E3)
            strArm = tr("驱控一体双臂");
        if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_YZ)
            strArm = tr("驱控一体压铸");
        if ((((pModbus->GetServoNotExist() >> AXES_IDX_A) & 1) == 1) && (((pModbus->GetServoNotExist() >> AXES_IDX_B) & 1) == 1) && (((pModbus->GetServoNotExist() >> AXES_IDX_C) & 1) == 1))
            strArm = tr("驱控一体新三轴");
        if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0)
            strArm = tr("驱控一体高速三轴");
        if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F3)
            strArm = tr("驱控一体高速六轴双臂");
        if (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4)
            strArm = tr("驱控一体高速六轴单臂");
        if (pModbus->GetFunctions(SUB_FUN_EUROMAP))
            strArm += tr("驱控一体-欧规");
    }
	QString strVer, verTemp;
#if defined(Q_WS_QWS)
    struct utsname sysInfo;
    uname(&sysInfo);
    QString strBuild(sysInfo.version);
    QString strNodename(sysInfo.nodename);
    QString strPlatform = "";
	if(BoardType_T == BoardT113)
	{
		strPlatform = "[T113]-";
	}
	else if(BoardType_T == BoardA40i_II)
	{
		strPlatform = "[A40-II]-";
	}
	else
	{
		if (strNodename == "dragonboard")
			strPlatform = "[A20]-";
		if (strNodename == "Sanyou")
			strPlatform = "[A40]-";
	}
    strBuild.remove(0, 17);
	if ((pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0) || (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F3) || (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4)
			 || (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F5) || (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F6) || (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F7)
			 || (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F8))
    {
        if(pModbus->GetSysTypeHigh() != 0)
		{
			strVer.sprintf("%s %s  / %s VH%X.%02X /%s-%s %s / %d-%d / LIB V%s / Build ",
						   qPrintable(tr("手控器：")), XPAD_SVER, qPrintable(tr("主板版本：")),pModbus->GetSverMajor(), pModbus->GetSverMinor(),qPrintable(strPlatform),qPrintable(strArm),
						   qPrintable(xStringResource::GetType(pModbus->GetSverExtra())),
						   FACTORY, pModbus->GetFactoryId(), qVersion());
		}
		else
		{
			strVer.sprintf("%s %s  / %s V%X.%02X /%s-%s %s / %d-%d / LIB V%s / Build ",
						   qPrintable(tr("手控器：")), XPAD_SVER, qPrintable(tr("主板版本：")),pModbus->GetSverMajor(), pModbus->GetSverMinor(),qPrintable(strPlatform),qPrintable(strArm),
						   qPrintable(xStringResource::GetType(pModbus->GetSverExtra())),
						   FACTORY, pModbus->GetFactoryId(), qVersion());
		}
	}
    else
    {
        strVer.sprintf("UI %s%s-%s  / SYSTEM V%X.%02X_%X.%02X / %s / %d-%d / LIB V%s / Build ",
                       qPrintable(strPlatform), XPAD_SVER, qPrintable(strArm), pModbus->GetSverMajor(), pModbus->GetSverMinor(), pModbus->GetM0Major(), pModbus->GetM0Minor(),
                       qPrintable(xStringResource::GetType(pModbus->GetSverExtra())),
                       FACTORY, pModbus->GetFactoryId(), qVersion());
    }
    strVer += strBuild;
#else
    if ((pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E0) || (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F3) || (pModbus->GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4))
    {
        if(pModbus->GetSysTypeHigh() != 0)
		{
			strVer.sprintf("UI %s-%s / SYSTEM VH%X.%02X / %s / %d-%d / LIB V%s",
						   XPAD_SVER, qPrintable(strArm), pModbus->GetSverMajor(), pModbus->GetSverMinor(),
						   qPrintable(xStringResource::GetType(pModbus->GetSverExtra())),
						   FACTORY, pModbus->GetFactoryId(), qVersion());
		}
		else
		{
			strVer.sprintf("UI %s-%s / SYSTEM V%X.%02X / %s / %d-%d / LIB V%s",
						   XPAD_SVER, qPrintable(strArm), pModbus->GetSverMajor(), pModbus->GetSverMinor(),
						   qPrintable(xStringResource::GetType(pModbus->GetSverExtra())),
						   FACTORY, pModbus->GetFactoryId(), qVersion());
		}
	}
    else
    {
    strVer.sprintf("UI %s-%s / SYSTEM V%X.%02X_%X.%02X / %s / %d-%d / LIB V%s",
                   XPAD_SVER, qPrintable(strArm), pModbus->GetSverMajor(), pModbus->GetSverMinor(), pModbus->GetM0Major(), pModbus->GetM0Minor(),
                   qPrintable(xStringResource::GetType(pModbus->GetSverExtra())),
                   FACTORY, pModbus->GetFactoryId(), qVersion());
    }
#endif
    ui->labelVertion->setText(strVer);
    if (pModbus->GetPirate() == LICENSE_LEGAL)
        ui->labelIcon->setPixmap(QPixmap(":/img/32X32/License.png"));
    else
        ui->labelIcon->setPixmap(QPixmap());
//	show();
//    qDebug() << "Forminformation::EnterForm";
    return true;
}

bool Forminformation::ExitForm(void)
{
//	hide();
	return true;
}
