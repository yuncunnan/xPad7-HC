#include "isp_thread.h"
#include "ispdialog.h"
#include "ui_ispdialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>
#include "qextserialport.h"
#include "xconfig.h"
#include "xusb.h"
#include <QDebug>
#include <QApplication>
#include <QProcess>
#include <QTimer>
#include "HalBoard.h"


ispDialog *pIspDialog = 0;
extern HardwareInterface *board;
ispDialog::ispDialog(QWidget *parent) : QDialog(parent), ui(new Ui::ispDialog)
{
    DetectType = 0;
#if defined(Q_WS_QWS)
	setWindowFlags(Qt::FramelessWindowHint);
	//setAttribute(Qt::WA_TranslucentBackground, true);
#endif
	ui->setupUi(this);
	ui->progressBar->setValue(0);
	pDirModel = NULL;
    connect(&programmer,SIGNAL(ChangePercent(int)),this,SLOT(ChangePercent(int)),Qt::QueuedConnection);
    connect(&programmer,SIGNAL(EnableControl(bool)),this,SLOT(EnableControl(bool)),Qt::QueuedConnection);
    connect(&programmer,SIGNAL(FindDevice(QString)),this,SLOT(FindDevice(QString)),Qt::QueuedConnection);
	connect(&programmer,SIGNAL(UpdateTime(unsigned int)),this,SLOT(UpdateTime(unsigned int)),Qt::QueuedConnection);
    connect(&programmer,SIGNAL(DialogMessage(QString)),this,SLOT(DialogMessage(QString)),Qt::QueuedConnection);
    connect(&programmer, SIGNAL(ProgramFinished(bool)), this, SLOT(ProgramFinished(bool)), Qt::QueuedConnection);

//	ui->comboBox_baud->setEnabled(ui->check_FAST->isChecked());

	pIspDialog = this;
}

void ispDialog::ReceiveComPort(QextSerialPort *pSerial, const char *Answer, unsigned long MaxSize, unsigned long *RealSize, unsigned long WantedNr0x0A)
{
	unsigned long start;
	unsigned long nr_of_0x0A = 0;

	(*RealSize) = 0;
    start = programmer.GetTick();
	do
	{
		if (pSerial->read((char*)(Answer+(*RealSize)), 1))
		{
			if (Answer[(*RealSize)] == 0x0a)
			{
				nr_of_0x0A++;
			}
			(*RealSize)++;
		}
		//qDebug() << ISP_thread::GetTick();

    } while (((*RealSize) < MaxSize) && (nr_of_0x0A < WantedNr0x0A) && ((start+2000)>programmer.GetTick()));

	((char*)Answer)[(*RealSize)] = 0;
//	qDebug()<<Answer<<"|| start:"<<start<<"last:"<<ISP_thread::GetTick();
}

bool ispDialog::checkIsp(bool &isH750)
{
	QextSerialPort serial;
	char Answer[128];
	unsigned long realsize;
	char *strippedAnswer;
	int  strippedsize;
#if defined(Q_WS_QWS)
	serial.setPortName(board->get_MB_PORT());
#else
	serial.setPortName(MB_PORT);
#endif
	serial.setBaudRate(BAUD38400);
	serial.setFlowControl(FLOW_OFF);
	serial.setParity(PAR_NONE);
	serial.setDataBits(DATA_8);
	serial.setStopBits(STOP_1);
	serial.setQueryMode(QextSerialPort::Polling);
	serial.setTimeout(1);
	if (!serial.open(QIODevice::ReadWrite))
		return false;

    serial.write("?", 1);

    memset(Answer,0,sizeof(Answer));
    ReceiveComPort(&serial, Answer, sizeof(Answer)-1, &realsize, 1);

    strippedAnswer = Answer;
    strippedsize = realsize;

    while ((strippedsize > 0) && ((*strippedAnswer == '?') || (*strippedAnswer == 0)))
    {
        strippedAnswer++;
        strippedsize--;
    }
    if (strcmp(strippedAnswer, "Synchronized\r\n")==0)
        DetectType = 1;
    if (strcmp(strippedAnswer, "Synchronized-Sinrobot\r\n")==0)
        DetectType = 2;
    if ((strcmp(strippedAnswer, "Synchronized\r\n")!=0)&&
        (strcmp(strippedAnswer, "Synchronized-Sinrobot\r\n")!=0))
    {
        //DebugPrintf(1, "No answer on 'Synchronized'\n --%s", Answer);
        serial.close();
        return false;
    }
#if 0
	//DebugPrintf(2, "Synchronizing (ESC to abort)");

	serial.write("Synchronized\r\n", strlen("Synchronized\r\n"));

	ReceiveComPort(&serial, Answer, sizeof(Answer) - 1, &realsize, 2);

	if (strcmp(Answer, "Synchronized\r\nOK\r\n") != 0)
	{
		//DebugPrintf(1, "No answer on 'Synchronized'\n --%s", Answer);
		serial.close();
		return false;
	}

	//DebugPrintf(3, "Synchronized 1\n");

	//DebugPrintf(3, "Setting oscillator\n");

	serial.write("12000\r\n", strlen("12000\r\n"));

	ReceiveComPort(&serial, Answer, sizeof(Answer)-1, &realsize, 2);

	if (strcmp(Answer, "12000\r\nOK\r\n") != 0)
	{
		//DebugPrintf(1, "No answer on Oscillator-Command --%s\n", Answer);
		serial.close();
		return false;
	}
#endif
    serial.write("WhoAreYou\r\n", 13);
    memset(Answer,0,sizeof(Answer));
    ReceiveComPort(&serial, Answer, sizeof(Answer)-1, &realsize, 1);

    strippedAnswer = Answer;
    while ((strippedsize > 0) && ((*strippedAnswer == '?') || (*strippedAnswer == 0)))
    {
        strippedAnswer++;
        strippedsize--;
    }
    if(strippedAnswer == QString("STM32H750VB\r\n"))
        isH750 = true;
	serial.close();
	return true;
}

// 刷新U盘
void ispDialog::refreshUsb(void)
{
#if defined(Q_WS_QWS)
	ui->fileView->setRootIndex(pDirModel->setRootPath("/root/"));
	if (xUsb::CheckInsert())
		ui->fileView->setRootIndex(pDirModel->setRootPath(XPAD_USB_PATH));
#else
    ui->fileView->setRootIndex(pDirModel->setRootPath(QDir::currentPath().append(XPAD_USB_PATH)));
#endif
}

void ispDialog::ShowIsp(bool isH750)
{
	if (pDirModel == NULL)
		pDirModel = new xFileSystemModel(this);
	pDirModel->setNameFilterDisables(false);
	pDirModel->setFilter(QDir::Files);
	pDirModel->setReadOnly(true);
	// 设置数据源
	ui->fileView->setModel(pDirModel);
	// 设置表头字体
#if SIMULATOR
    ui->fileView->horizontalHeader()->setFont(QFont("Microsoft YaHei", 8));
    ui->fileView->horizontalHeader()->setStyleSheet("QHeaderView {font-size: 8pt;}");
    ui->fileView->verticalHeader()->setFont(QFont("Microsoft YaHei", 8));
    ui->fileView->verticalHeader()->setStyleSheet("QHeaderView {font-size: 8pt;}");
#else
	ui->fileView->horizontalHeader()->setFont(QFont("Microsoft YaHei", 28));
	ui->fileView->horizontalHeader()->setStyleSheet("QHeaderView {font-size: 28px;}");
	ui->fileView->verticalHeader()->setFont(QFont("Microsoft YaHei", 28));
	ui->fileView->verticalHeader()->setStyleSheet("QHeaderView {font-size: 28px;}");
#endif
    // 设置表头尺寸模式
	ui->fileView->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
	ui->fileView->horizontalHeader()->setResizeMode(1, QHeaderView::Fixed);
	ui->fileView->horizontalHeader()->setResizeMode(3, QHeaderView::Fixed);
	ui->fileView->verticalHeader()->setResizeMode(QHeaderView::Fixed);
	// 隐藏文件类型列
    ui->fileView->setColumnHidden(1, true);
    ui->fileView->setColumnHidden(2, true);
    // 设置列宽度
    ui->fileView->setColumnWidth(3, 260);
    if(isH750)
        pDirModel->setNameFilters(QStringList() << "*"RCM_UPG_EXT_H75);
    else
        pDirModel->setNameFilters(QStringList() << "*"RCM_UPG_EXT);
	ui->labelVersion->setText(tr("软件版本：") + SOFT_VERSION);
	refreshUsb();
	return show();
}

int ispDialog::DoIsp(bool isH750)
{
	if (pDirModel == NULL)
		pDirModel = new xFileSystemModel(this);
	pDirModel->setNameFilterDisables(false);
	pDirModel->setFilter(QDir::Files);
	pDirModel->setReadOnly(true);
	// 设置数据源
	ui->fileView->setModel(pDirModel);
	// 设置表头字体
    ui->fileView->horizontalHeader()->setFont(QFont("Microsoft YaHei", 20));
    ui->fileView->horizontalHeader()->setStyleSheet("QHeaderView {font-size: 20pt;}");
    ui->fileView->verticalHeader()->setFont(QFont("Microsoft YaHei", 20));
    ui->fileView->verticalHeader()->setStyleSheet("QHeaderView {font-size: 20pt;}");
    // 设置表头尺寸模式
	ui->fileView->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
	ui->fileView->horizontalHeader()->setResizeMode(1, QHeaderView::Fixed);
	ui->fileView->horizontalHeader()->setResizeMode(3, QHeaderView::Fixed);
	ui->fileView->verticalHeader()->setResizeMode(QHeaderView::Fixed);
	// 隐藏文件类型列
    ui->fileView->setColumnHidden(1, true);
    ui->fileView->setColumnHidden(2, true);
    // 设置列宽度
    ui->fileView->setColumnWidth(3, 260);
    if(isH750)
        pDirModel->setNameFilters(QStringList() << "*"RCM_UPG_EXT_H75);
    else
    pDirModel->setNameFilters(QStringList() << "*"RCM_UPG_EXT);
    ui->labelVersion->setText(tr("软件版本：") + SOFT_VERSION);
	refreshUsb();
    bool ish750;
    checkIsp(ish750);
	return exec();
}

ispDialog::~ispDialog()
{
	if (pDirModel != NULL)
		delete pDirModel;
	delete ui;
}

void ispDialog::ChangePercent(int percent)
{
	ui->progressBar->setValue(percent);
}
void ispDialog::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type())
    {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void ispDialog::EnableControl(bool enable)
{
	ui->Button_Browse->setEnabled(enable);
	ui->Button_PROGRAM->setEnabled(enable);
	ui->progressBar->setValue(0);
	ui->comboBox_baud->setEnabled(enable);
}

void ispDialog::FindDevice(QString dev)
{
    ui->label_CPU->setText(dev);
}

void ispDialog::UpdateTime(unsigned int t)
{
	ui->label_TIME->setText(QString("Time: %1s").arg(t));
}

void ispDialog::DialogMessage(QString msg)
{
	ui->groupBox->setEnabled(false);
    ChangeFont(tr("错误: ") + (msg));
}

void ispDialog::ProgramFinished(bool fail)
{
//	ui->groupBox->setEnabled(false);
//	ui->BtnRestart->setEnabled(true);
    if (fail)
        ChangeFont(tr("编程失败，请关闭系统电源然后重新启动系统后重试。"));
    else
        ChangeFont(tr("编程完成，请关闭系统电源然后重新启动系统。"));
}

void ispDialog::clickProgram()
{
	ui->progressBar->setValue(0);
	QFile fileSrc(pDirModel->filePath(ui->fileView->currentIndex()));
	// 检查开机画面文件是否存在
	if (fileSrc.exists() == false)
	{
        ChangeFont(tr("请先选择主控模块升级文件包！"));
		return;
	}
#if defined(Q_WS_QWS)
	programmer.InitISP_Serial(board->get_MB_PORT(), BAUD38400, pDirModel->filePath(ui->fileView->currentIndex()), DetectType);
#else
    programmer.InitISP_Serial(MB_PORT, BAUD38400, pDirModel->filePath(ui->fileView->currentIndex()), DetectType);
#endif
	programmer.start();
}

void ispDialog::clickBrowse()
{
	refreshUsb();
}

void ispDialog::reject()
{
	if (!programmer.isRunning())
		QDialog::reject();
}

void ispDialog::clickRestart(void)
{
	qApp->exit(773);
}

void ispDialog::on_fileView_clicked(const QModelIndex &index)
{
    if(pDirModel)
    {
        QModelIndex qn=pDirModel->index(index.row(),0,index.parent());
        QString name=qn.data().toString();
		QFont font_("Microsoft YaHei",16);
        ui->labelMessage->setFont(font_);
        ui->labelMessage->setText(name);    }
}
void ispDialog::ChangeFont(QString msg)
{
	 QFont font("Microsoft YaHei",20);
     ui->labelMessage->setFont(font);
     ui->labelMessage->setText(msg);
}
