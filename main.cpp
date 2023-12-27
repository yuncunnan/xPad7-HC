#include <QApplication>
#include <QtPlugin>
#include <QCleanlooksStyle>
#include <QTextCodec>
#include <QProcess>
#include <QDir>
#include <QDebug>
#include "xconfig.h"
#include "cmbprotocol.h"
#include "xstringresource.h"
#include "xsplashscreen.h"
#include "screensaver.h"
#include "buzzer.h"
#include "safeswitch.h"
#include "motor.h"
#include "indicatorled.h"
#include "xtranslator.h"
#include "xsystemlog.h"
#include "dialogselectvariable.h"
#include "dialogframe.h"
#include "dialogkeyboard.h"
#include "xtopinfo.h"
#include "ispdialog.h"
#include "HalBoard.h"
#include "xKeypad.h"
#include "formbacklight.h"
#if defined(Q_WS_QWS)
#include <sys/utsname.h>
#endif

#if defined(Q_WS_QWS)
Q_IMPORT_PLUGIN(xpad2encoder)
#endif
bool gnewVersion = false;				// 新版核心版程序

HardwareInterface *board;
enum BoardType
{
	BoardOther = 0,
	BoardA40i_I,
	BoardT113,
	BoardA40i_II
};

void WaitMethod(int ms)
{
	Q_ASSERT(QCoreApplication::instance());
	QTime timer;
	timer.start();
	do
	{
		QCoreApplication::processEvents(QEventLoop::AllEvents, ms);
#if defined(Q_OS_WIN)
		// window system funciton
		Sleep(uint(ms));
#endif
#if defined(Q_OS_LINUX)
		// linux system function
		struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
		nanosleep(&ts, NULL);
#endif
	} while (timer.elapsed() < ms);
}

///////////////////////////////////////////////////////////////////////////////////////
// 计算文件MD5值
QString CalcMd5(const QString &SrcFilePath)
{
    QFile srcFile(SrcFilePath);
    srcFile.open(QIODevice::ReadOnly);
    QByteArray md5 = QCryptographicHash::hash(srcFile.readAll(), QCryptographicHash::Md5);
    srcFile.close();

    return md5.toHex();
}
void updateTouchDriver(void)
{
#if defined(Q_WS_QWS)
	struct utsname sysInfo;
	uname(&sysInfo);
	QString strNodename(sysInfo.nodename);
	if (strNodename == "Sanyou")
	{
		QFile srcFile("/home/touch/ads7846_spi_soft.ko");
		if (srcFile.exists())
		{
			qDebug() << "file exist";
			QString DriverMD5;
			DriverMD5 =  CalcMd5("/home/touch/ads7846_spi_soft.ko");
			qDebug() << "DriverMD5" << DriverMD5;
			if ((DriverMD5 == "067c114b79afea1b3bc589e0d66a24e4")|| //100%
				(DriverMD5 == "067c114b79afea1b3bc589e0d66a24e4"))	//57%
			{
				srcFile.remove();
				qDebug() << "remove";
				QFile::copy(":/driver/driver/ads7846_spi_soft.ko", "/home/touch/ads7846_spi_soft.ko");
				qDebug() << "copy";
				system("reboot");
			}
		}
		else
		{
			QFile::copy(":/driver/driver/ads7846_spi_soft.ko", "/home/touch/ads7846_spi_soft.ko");
			system("reboot");
		}
	}

#endif
}
//////////////////////////////////////////////////////////////////////////////////////
DialogFrame *pDialogMain = NULL;
class MyApplication : public QApplication
{
    QVector<quint32> keyVector;				// 键盘按键数组
public:
     MyApplication(int&argc,char **argv);
     bool notify(QObject*, QEvent *);
};

MyApplication::MyApplication(int &argc,char **argv):QApplication(argc,argv)
{
    keyVector.clear();
    keyVector << ENCODER_CW << ENCODER_CCW;
	QFont font;
	int fontSizePixel = 40;
	font.setPixelSize(fontSizePixel);
	this->setFont(font);
}

bool MyApplication::notify(QObject *obj, QEvent *event)
{
     if (pDialogMain)
     {
         if((event->type() == QEvent::KeyPress)||(event->type() == QEvent::KeyRelease))
         {
             QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
             if (keyVector.contains(keyEvent->key()) == true)
             {
                 pDialogMain->CWCCWKeyHandler(keyEvent->key());
             }
         }
     }
     return QApplication::notify(obj, event);
}

xPermissions UsrPerm;											// 构造用户权限管理对象
int main (int argv, char **args)
{
//	updateTouchDriver();
    uint8_t initRet;
	int appRet;
	BoardType BoardType_T;
    MyApplication app(argv, args);
#if defined(Q_WS_QWS)
	{
        QFile fileMouse("/dev/input/mouse0");
		QWSServer::setCursorVisible(fileMouse.exists());
	}

	// 构造系统的底层驱动接口对象
	QFile file("/proc/version");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "can’t open /proc/version";
	}
	QString version = file.readAll();// 读取文件中的内容
	qDebug() << "version:" << version;
	file.close();
	if(version.contains("A40i-7"))
	{
		board = new A40I_7();
		BoardType_T=BoardA40i_II;
        qDebug()<<"nain A40i-II*****************************";
	}
	else if (version.contains("T113-7"))/*version.contains("T113-7")*/
	{
		board = new T113();
		BoardType_T=BoardT113;
		qDebug()<<"main T113******************";
	}
	else
	{
		board = new A40i();
		BoardType_T=BoardA40i_I;
		qDebug()<<"main A40I******************";
	}
	//设置当前工作路径
	QDir::setCurrent(board->get_Current());
	qDebug() << "Current working directory: " << QDir::currentPath();					//返回工作路径
	qDebug() << "System library search paths: " << QCoreApplication::libraryPaths();	//返回库路径
#endif
	QFile nandf("/dev/nandf");
	gnewVersion = nandf.exists();
	// 显示启动画面
	xSplashScreen *pSplash = new xSplashScreen(QPixmap(XPAD_SPLASH_NAME));
	QFont font;
	font.setPixelSize(40);
	pSplash->setFont(font);
	pSplash->setEnabled(false);
	pSplash->show();
	// 设置字符串编码
//#if defined(Q_OS_WIN)
//    QTextCodec::setCodecForTr(QTextCodec::codecForName("SYSTEM"));
//    QTextCodec::setCodecForLocale(QTextCodec::codecForName("SYSTEM"));
//#else
	QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
//#endif
	// 设置系统软件信息
	QCoreApplication::setOrganizationName("SinRobot");
	QCoreApplication::setOrganizationDomain("www.sinrobot.com.cn");
	QCoreApplication::setApplicationName("xPad7000");
	// 设置界面风格
	{
		app.setStyle(new QCleanlooksStyle);
#if IS_XEDITOR
        QFile qssFile(":/style/xEditor.qss");
#else
        QFile qssFile(":/style/xPad-6as.qss");
#endif
        qssFile.open(QFile::ReadOnly);
        QTextStream txtStream(&qssFile);
        QString styleSheet = txtStream.readAll();
        app.setStyleSheet(styleSheet);
        qssFile.close();
	}

	Buzzer *pBuzzer = new Buzzer();									// 构造蜂鸣器对象
	SafeSwitch *pSwitch = new SafeSwitch();							// 构造安全开关对象
//	Motor *pMotor = new Motor();									// 构造振动电机对象
	xKeypad *pKeypad = new xKeypad(&app);
	IndicatorLed *pLed = new IndicatorLed();						// 构造面板指示灯对象
	ispDialog *pIsp = new ispDialog();
    bool ish750 = false;
    if (pIsp->checkIsp(ish750))
	{
		// 进入ISP编程界面
        if(ish750)
            pIsp->ShowIsp(true);
        else
            pIsp->ShowIsp(false);
		qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
		// 隐藏启动画面
		pSplash->finish(pIsp);
		delete pSplash;
//		xMotor->StartMotor(2);
		// 进入系统事件循环
		appRet = app.exec();
	}
	else
	{
        int retry = 100;
		// 进入机械手控制系统界面
		// 构造并初始化 Modbus 协议对象
		pSplash->showMessage(QObject::tr("初始化通讯链路..."), Qt::AlignLeft | Qt::AlignVCenter);
        CMBProtocol *ModbusProtocol = new CMBProtocol;
        do
		{
			initRet = ModbusProtocol->InitSystemStatus();
			if (initRet == COM_INIT_COM_ERR)
            {
                if (retry<=0)
				pSplash->showMessage(QObject::tr("操作器与主控模块通讯错误！请关机检查通讯链路。"), Qt::AlignLeft | Qt::AlignVCenter);
            }
			else if (initRet == COM_INIT_MATE_ERR)
				pSplash->showMessage(QObject::tr("操作器和主控模块类型不匹配！请关机检查操作器和主控模块。"), Qt::AlignLeft | Qt::AlignVCenter);
			else if (initRet == COM_INIT_SVER_ERR)
				pSplash->showMessage(QObject::tr("主控模块软件版本太低！请升级主控模块软件。"), Qt::AlignLeft | Qt::AlignVCenter);
			WaitMethod(100);
            if (retry)
                retry --;
		} while (initRet != COM_INIT_OK);
        // 构造字符串和界面
//		xStringResource *StrResource = new xStringResource;
		xTranslator *pLan = new xTranslator();
		// 构造系统界面部件
		pSplash->showMessage(QObject::tr("初始化系统界面部件..."), Qt::AlignLeft | Qt::AlignVCenter);
#if defined(Q_WS_QWS)
		qDebug()<<"001-----------------------";
		FormBacklight Bklight(ModbusProtocol);
		qDebug()<<"002-----------------------";
		ScreenSaver *pScrSaver = new ScreenSaver(&UsrPerm, &Bklight);				// 构造屏保对象
		qDebug()<<"003-----------------------";
#endif
		// 构造系统UI对象
		DialogKeyboard *pKbd = new DialogKeyboard();					// 构造字符软键盘对象
		DialogSelectVariable *pSelVar = new DialogSelectVariable();		// 构造选择变量对话框对象
		qDebug()<<"004-----------------------";

		xTopInfo *pTopInformation = new xTopInfo();						// 构造顶层消息框
		xSysLog *pSysLog = new xSysLog();								// 构造系统日志对象
		qDebug()<<"005-----------------------";

		// 日志写入系统软件启动记录
        pSysLog->AddRecord(SYSLOG_TYPE_NOR, LOG_NOR_START);
        pSysLog->SaveChange();
		qDebug()<<"006-----------------------";

        // 定义主窗口
		pSplash->showMessage(QObject::tr("初始化系统图形界面..."), Qt::AlignLeft | Qt::AlignVCenter);
        pDialogMain = new DialogFrame(ModbusProtocol, &UsrPerm);
#if IS_XEDITOR
        pDialogMain->setWindowTitle(QObject::tr("新睿电子科技 xEditor"));
#else
		pDialogMain->setWindowTitle(QObject::tr("新睿电子科技"));
#endif
        // 启动 Modbus 周期轮询定时器
		ModbusProtocol->StartPeriodTimer();
		// 初始化屏保设置
#if defined(Q_WS_QWS)
		pScrSaver->InitScreenSaver();
#endif
		// 显示主窗口
		pSplash->showMessage(QObject::tr("进入系统主画面..."), Qt::AlignLeft | Qt::AlignVCenter);
		pDialogMain->show();
		qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
		// 隐藏启动画面
		pSplash->finish(pDialogMain);
		delete pSplash;
//		xMotor->StartMotor(2);
		// 进入系统事件循环
		appRet =  app.exec();
		// 应用程序退出清除对象
		delete pDialogMain;
		delete ModbusProtocol;
//		delete StrResource;
		delete pLan;
	#if defined(Q_WS_QWS)
		delete pScrSaver;
	#endif
		delete pSelVar;
		delete pKbd;
		delete pTopInformation;
		delete pSysLog;
	}
	// 应用程序退出清除驱动对象
	delete pBuzzer;
	delete pSwitch;
//	delete xMotor;
    delete pLed;
	delete pIsp;
	delete pKeypad;
	delete board;
	if (appRet == 773)
	{
		qDebug()<<"-----------------BoardType_T:"<<BoardType_T;
		if(BoardType_T==BoardA40i_I)
		{
			qDebug()<<"-------------qws001";
        system("cd /usr/xPad");
        system("./xPad -qws");
		}
		else if(BoardType_T==BoardA40i_II||BoardType_T==BoardT113)
		{
			qDebug()<<"-------------qws002";
			system("/bin/xPad -qws");
		}
		else
			system("reboot");
		appRet = 0;
	}
	return appRet;
}

