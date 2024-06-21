include(widget/xindicator.pri)
include(widget/xpixmapbutton.pri)
include(widget/xindicatorbutton.pri)

QT += core gui
QT += sql
QT += network

TARGET = xPad7-6as-hc.upg2
CONFIG += exceptions

DEFINES += HAVE_CONFIG_H IS_CSOFTTECK

TEMPLATE = app

linux-arm-gnueabi-gcc|linux-arm-gnueabi-g++ {
        QTPLUGIN += xpad2encoder
        LIBS += -L$$PWD/plugins/ -lxpad2encoder
}
QMAKE_CFLAGS += -Wno-unused-parameter -Wno-psabi
QMAKE_CXXFLAGS += -Wno-unused-parameter -Wno-psabi

SOURCES += \
	main.cpp \
	formmanual.cpp \
	formsystem.cpp \
	formmenu.cpp \
	forminformation.cpp \
	formservo.cpp \
	formuisetup.cpp \
	formmanufacturer.cpp \
	dialogdatetime.cpp \
	dialogservocontrol.cpp \
	dialogkeyboard.cpp \
	dialogselectaction.cpp \
	dialognumberpad.cpp \
	dialogusermanager.cpp \
	formalarm.cpp \
	dialogframe.cpp \
	formpgmexplorer.cpp \
	formauto.cpp \
	formadjust.cpp \
	modbus/qextserialport.cpp \
	modbus/modbus-tcp.c \
	modbus/modbus-rtu.c \
	modbus/modbus-data.c \
	modbus/modbus.c \
	cmbprotocol.cpp \
	xmessagebox.cpp \
	driver/xioport.cpp \
	xstringresource.cpp \
	widget/xdoublespinbox.cpp \
	widget/xspinbox.cpp \
	widget/xpushbutton.cpp \
	widget/xlineedit.cpp \
	widget/xclock.cpp \
	widget/xsplashscreen.cpp \
	formteach.cpp \
	xmlmodel/xmlmodelitem.cpp \
	xmlmodel/teachtablemodel.cpp \
	xmlmodel/codewait.cpp \
	xmlmodel/codepos.cpp \
	xmlmodel/codeparm.cpp \
	xmlmodel/codepaper.cpp \
	xmlmodel/codeoperator.cpp \
	xmlmodel/codeloopmatrix.cpp \
	xmlmodel/codeloopfree.cpp \
	xmlmodel/codeimm.cpp \
	xmlmodel/codeif.cpp \
	xmlmodel/codefor.cpp \
	xmlmodel/codeextout.cpp \
	xmlmodel/codeextin.cpp \
	xmlmodel/codeendif.cpp \
	xmlmodel/codeendfor.cpp \
	xmlmodel/codeend.cpp \
	xmlmodel/codeelse.cpp \
	xmlmodel/codedelay.cpp \
	xmlmodel/codebreak.cpp \
	formactpos.cpp \
	formactextout.cpp \
	formactextin.cpp \
	formactpro.cpp \
	formactimm.cpp \
	formactpaper.cpp \
	formactloopmatrix.cpp \
	formactloopfree.cpp \
	formactdelay.cpp \
	formactfor.cpp \
	formactif.cpp \
	formactnull.cpp \
	formactwait.cpp \
	formactoperate.cpp \
	dialogselectvariable.cpp \
	xpermissions.cpp \
	widget/xfilesystemmodel.cpp \
	screensaver.cpp \
	widget/xtoolbutton.cpp \
	driver/motor.cpp \
	driver/indicatorled.cpp \
	xtranslator.cpp \
	xmlmodel/codespeed.cpp \
	widget/xradiobutton.cpp \
	widget/xcheckbox.cpp \
	xtopinfo.cpp \
	driver/xusb.cpp \
	utility/elccalc.cpp \
	widget/xspeedometer.cpp \
	dialogspeed.cpp \
	formsyslog.cpp \
	xsystemlog.cpp \
	dialoglogio.cpp \
	dialoglogpar.cpp \
	dialoglogdetail.cpp \
	dialoglogquery.cpp \
    servoalias.cpp \
    widget/xtimeedit.cpp \
    widget/xdatetimeedit.cpp \
    widget/xdateedit.cpp \
    formoption.cpp \
    xmlmodel/xmlmodelitemoption.cpp \
    xmlmodel/codevacuum.cpp \
    formactvacuum.cpp \
    xdelaymessagebox.cpp \
    xmlmodel/coderarm.cpp \
    formactrun.cpp \
    formeditoption.cpp \
    dialogoption.cpp \
    dialogedit.cpp \
    formactpath.cpp \
    xmlmodel/codetbegin.cpp \
    xmlmodel/codetend.cpp \
    qrencode/split.c \
    qrencode/rscode.c \
    qrencode/qrspec.c \
    qrencode/qrinput.c \
    qrencode/qrencode.c \
    qrencode/mqrspec.c \
    qrencode/mmask.c \
    qrencode/mask.c \
    qrencode/bitstream.c \
    widget/qrwidget.cpp \
    xmlmodel/xmlmodelvarinititem.cpp \
    formvarinit.cpp \
    formactspeed.cpp \
    formactsingleloop.cpp \
    xmlmodel/codesingleloop.cpp \
    xmessageboxIP.cpp \
	driver/xKeypad.cpp \
    driver/SafeSwitch.cpp \
    driver/Buzzer.cpp \
    formio.cpp \
    formactinterp.cpp \
    xmlmodel/codeinterp.cpp \
    formwallpaper.cpp \
    formactpower.cpp \
    xmlmodel/codepower.cpp \
    formvactvacuum.cpp \
    formalfapgmexplorer.cpp \
    formalfaoption.cpp \
    xmlmodel/alfamodel.cpp \
    xmlmodel/vcodevacuum.cpp \
    formactcircle.cpp \
    xmlmodel/codecircle.cpp \
    formactsingleloopfree.cpp \
    xmlmodel/codesingleloopfree.cpp \
    utility/isp/ispdialog.cpp \
    utility/isp/stm32_crc32/stm32_crc32.cpp \
    utility/isp/thread/isp_thread.cpp \
    utility/isp/thread/iap_program.cpp \
    utility/isp/lpcisp/lpcprog.c \
    utility/isp/ihexmaster/kk_ihex_write.c \
    utility/isp/ihexmaster/kk_ihex_read.c \
    utility/isp/ihexmaster/chexbin.cpp \
    utility/isp/crc16/crc16.cpp \
    formactextpos.cpp \
    xmlmodel/codeextpos.cpp \
    xmessageboxactive.cpp \
    formbacklight.cpp \
    formactvision.cpp \
    xmlmodel/codevision.cpp \
    xmlmodel/codemextout.cpp \
    formactmextout.cpp \
    dialogparaedit.cpp \
    formactassist.cpp \
    formbtnwait.cpp \
    formbtnvacuum.cpp \
    formbtnpos.cpp \
    formbtnmextout.cpp \
    formbtnimm.cpp \
    formbtnextpos.cpp \
    formbtnassist.cpp \
    xmlmodel/codeassist.cpp \
    formbtnpro.cpp \
    formbtnrun.cpp \
    utility/base32.c \
    formbtnquick.cpp \
    pinyng/PyinMap.c \
    dialogportedit.cpp



HEADERS += \
	formmanual.h \
	formsystem.h \
	formmenu.h \
	forminformation.h \
	formservo.h \
	formuisetup.h \
	formmanufacturer.h \
	dialogdatetime.h \
	dialogservocontrol.h \
	dialogkeyboard.h \
	dialogselectaction.h \
	dialognumberpad.h \
	dialogusermanager.h \
	formalarm.h \
	dialogframe.h \
	formpgmexplorer.h \
	formauto.h \
	formadjust.h \
	modbus/qextserialport.h \
	modbus/modbus-version.h \
	modbus/modbus-tcp-private.h \
	modbus/modbus-tcp.h \
	modbus/modbus-rtu-private.h \
	modbus/modbus-rtu.h \
	modbus/modbus-private.h \
	modbus/modbus.h \
	modbus/config.h \
	modbusaddr.h \
	cmbprotocol.h \
	xmessagebox.h \
	driver/xioport.h \
	xstringresource.h \
	widget/xdoublespinbox.h \
	widget/xspinbox.h \
	widget/xpushbutton.h \
	widget/xlineedit.h \
	widget/xclock.h \
	widget/xsplashscreen.h \
	xconfig.h \
	formteach.h \
	xmlmodel/xmlmodelitem.h \
	xmlmodel/teachtablemodel.h \
	xmlmodel/codewait.h \
	xmlmodel/codepos.h \
	xmlmodel/codeparm.h \
	xmlmodel/codepaper.h \
	xmlmodel/codeoperator.h \
	xmlmodel/codeloopmatrix.h \
	xmlmodel/codeloopfree.h \
	xmlmodel/codeimm.h \
	xmlmodel/codeif.h \
	xmlmodel/codefor.h \
	xmlmodel/codeextout.h \
	xmlmodel/codeextin.h \
	xmlmodel/codeendif.h \
	xmlmodel/codeendfor.h \
	xmlmodel/codeend.h \
	xmlmodel/codeelse.h \
	xmlmodel/codedelay.h \
	xmlmodel/codebreak.h \
	formactpos.h \
	formactextout.h \
	formactextin.h \
	formactpro.h \
	formactimm.h \
	formactpaper.h \
	formactloopmatrix.h \
	formactloopfree.h \
	formactdelay.h \
	formactfor.h \
	formactif.h \
	formactnull.h \
	formactwait.h \
	formactoperate.h \
	dialogselectvariable.h \
	xpermissions.h \
	screensaver.h \
	driver/xioport.h \
	widget/xtoolbutton.h \
	driver/motor.h \
	driver/indicatorled.h \
	widget/xfilesystemmodel.h \
	xtranslator.h \
	xmlmodel/codespeed.h \
	widget/xradiobutton.h \
	widget/xcheckbox.h \
	xtopinfo.h \
	driver/xusb.h \
	utility/elccalc.h \
	widget/xspeedometer.h \
	dialogspeed.h \
	formsyslog.h \
	xsystemlog.h \
	dialoglogio.h \
	dialoglogpar.h \
	dialoglogdetail.h \
	dialoglogquery.h \
    servoalias.h \
    widget/xtimeedit.h \
    widget/xdatetimeedit.h \
    widget/xdateedit.h \
    formoption.h \
    xmlmodel/xmlmodelitemoption.h \
    formactvacuum.h \
    xmlmodel/codevacuum.h \
    xdelaymessagebox.h \
    xmlmodel/coderarm.h \
    formactrun.h \
    formeditoption.h \
    dialogoption.h \
    dialogedit.h \
    formactpath.h \
    xmlmodel/codetbegin.h \
    xmlmodel/codetend.h \
    qrencode/split.h \
    qrencode/rscode.h \
    qrencode/qrspec.h \
    qrencode/qrinput.h \
    qrencode/qrencode.h \
    qrencode/mqrspec.h \
    qrencode/mmask.h \
    qrencode/mask.h \
    qrencode/config.h \
    qrencode/bitstream.h \
    widget/qrwidget.h \
    xmlmodel/xmlmodelvarinititem.h \
    formvarinit.h \
    formactspeed.h \
    formactsingleloop.h \
    xmlmodel/codesingleloop.h \
    xmessageboxIP.h \
    driver/xKeypad.h \
    driver/SafeSwitch.h \
    driver/Buzzer.h \
    formio.h \
    formactinterp.h \
    xmlmodel/codeinterp.h \
    formwallpaper.h \
    formactpower.h \
    xmlmodel/codepower.h \
    formvactvacuum.h \
    formalfapgmexplorer.h \
    formalfaoption.h \
    xmlmodel/alfamodel.h \
    xmlmodel/vcodevacuum.h \
    formactcircle.h \
    xmlmodel/codecircle.h \
    formactsingleloopfree.h \
    xmlmodel/codesingleloopfree.h \
    utility/isp/ispdialog.h \
    utility/isp/stm32_crc32/stm32_crc32.h \
    utility/isp/thread/isp_thread.h \
    utility/isp/lpcisp/lpcprog.h \
    utility/isp/ihexmaster/kk_ihex_write.h \
    utility/isp/ihexmaster/kk_ihex_read.h \
    utility/isp/ihexmaster/kk_ihex.h \
    utility/isp/ihexmaster/chexbin.h \
    utility/isp/crc16/crc16.h \
    formactextpos.h \
    xmlmodel/codeextpos.h \
    xmessageboxactive.h \
    formbacklight.h \
    formactvision.h \
    xmlmodel/codevision.h \
    xmlmodel/codemextout.h \
    formactmextout.h \
    dialogparaedit.h \
    formactassist.h \
    formbtnwait.h \
    formbtnvacuum.h \
    formbtnpos.h \
    formbtnmextout.h \
    formbtnimm.h \
    formbtnextpos.h \
    formbtnassist.h \
    xmlmodel/codeassist.h \
    formbtnpro.h \
    formbtnrun.h \
    utility/base32.h \
    formbtnquick.h \
    pinyng/PyinMap.h \
    dialogportedit.h \
    plugins/a40i_7.h \
    plugins/HalBoard.h \
    plugins/t113.h \
    plugins/HardwareInterface.h \
    plugins/a40i.h


FORMS += \
	formmanual.ui \
	formsystem.ui \
	formmenu.ui \
	forminformation.ui \
	formservo.ui \
	formuisetup.ui \
	formmanufacturer.ui \
	dialogdatetime.ui \
	dialogservocontrol.ui \
	dialogkeyboard.ui \
	dialogselectaction.ui \
	dialognumberpad.ui \
	dialogusermanager.ui \
	formalarm.ui \
	dialogframe.ui \
	formpgmexplorer.ui \
	formauto.ui \
	formadjust.ui \
	xmessagebox.ui \
	formteach.ui \
	formactpos.ui \
	formactextout.ui \
	formactextin.ui \
	formactpro.ui \
	formactimm.ui \
	formactpaper.ui \
	formactloopmatrix.ui \
	formactloopfree.ui \
	formactdelay.ui \
	formactfor.ui \
	formactif.ui \
	formactnull.ui \
	formactwait.ui \
	formactoperate.ui \
	dialogselectvariable.ui \
	xtopinfo.ui \
	utility/elccalc.ui \
	dialogspeed.ui \
	formsyslog.ui \
	dialoglogio.ui \
	dialoglogpar.ui \
	dialoglogdetail.ui \
	dialoglogquery.ui \
    formoption.ui \
    formactvacuum.ui \
    formactrun.ui \
    formeditoption.ui \
    dialogoption.ui \
    formactpath.ui \
    formvarinit.ui \
    formactspeed.ui \
    formactsingleloop.ui \
    xmessageboxIP.ui \
    formio.ui \
    formactinterp.ui \
    formwallpaper.ui \
    formactpower.ui \
    formvactvacuum.ui \
    formalfapgmexplorer.ui \
    formalfaoption.ui \
    formactcircle.ui \
    formactsingleloopfree.ui \
    utility/isp/ispdialog.ui \
    formactextpos.ui \
    xmessageboxactive.ui \
    formbacklight.ui \
    formactvision.ui \
    formactmextout.ui \
    dialogparaedit.ui \
    formactassist.ui \
    formbtnwait.ui \
    formbtnvacuum.ui \
    formbtnpos.ui \
    formbtnmextout.ui \
    formbtnimm.ui \
    formbtnextpos.ui \
    formbtnassist.ui \
    formbtnpro.ui \
    formbtnrun.ui \
    formbtnquick.ui \
    dialogportedit.ui


RESOURCES += \
		xPad.qrc


INCLUDEPATH += modbus/libmodbus modbus/ widget/ utility/ utility/isp utility/isp/thread utility/isp/stm32_crc32 utility/isp/lpcisp utility/isp/ihexmaster utility/isp/crc16 xmlmodel/ driver/ lib/ qrencode/ plugins/
unix:SOURCES += modbus/posix_qextserialport.cpp
unix:DEFINES += _TTY_POSIX_

win32:SOURCES += modbus/win_qextserialport.cpp
win32:DEFINES += _TTY_WIN_  WINVER=0x0501
win32:LIBS += -lsetupapi -lwsock32 -lws2_32 -lAdvAPI32 -lUser32

TRANSLATIONS =	xPad_chs.ts \
				xPad_cht.ts \
				xPad_en.ts  \
				xPad_rus.ts  \
				xPad_viet.ts

CODECFORTR = utf-8
