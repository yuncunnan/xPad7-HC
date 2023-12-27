#include <QButtonGroup>
#include <QKeyEvent>
#include "xconfig.h"
#include "dialogkeyboard.h"
#include "ui_dialogkeyboard.h"
#include <QDebug>
#include "pinyng/PyinMap.h"

DialogKeyboard *xKbd = 0;
#define KEY_PAGE        0
#define TEXT_PAGE       1
DialogKeyboard::DialogKeyboard(QWidget *parent) : QDialog(parent), ui(new Ui::DialogKeyboard)
{
    ui->setupUi(this);
//    pFileV = new QRegExpValidator(QRegExp("[A-Za-z0-9()]{0,16}"), this);
    pFileV = new QRegExpValidator(QRegExp("[^*]{0,16}"), this);
    xKbd = this;
#if defined(Q_WS_QWS)
	// 设置对话框显示效果
	setWindowFlags(Qt::FramelessWindowHint);
	//setAttribute(Qt::WA_TranslucentBackground, true);
#endif
	// 组织字母按键
	pKeyChar = new QButtonGroup;
	pKeyChar->addButton(ui->KeyChA, Qt::Key_A);
	pKeyChar->addButton(ui->KeyChB, Qt::Key_B);
	pKeyChar->addButton(ui->KeyChC, Qt::Key_C);
	pKeyChar->addButton(ui->KeyChD, Qt::Key_D);
	pKeyChar->addButton(ui->KeyChE, Qt::Key_E);
	pKeyChar->addButton(ui->KeyChF, Qt::Key_F);
	pKeyChar->addButton(ui->KeyChG, Qt::Key_G);
	pKeyChar->addButton(ui->KeyChH, Qt::Key_H);
	pKeyChar->addButton(ui->KeyChI, Qt::Key_I);
	pKeyChar->addButton(ui->KeyChJ, Qt::Key_J);
	pKeyChar->addButton(ui->KeyChK, Qt::Key_K);
	pKeyChar->addButton(ui->KeyChL, Qt::Key_L);
	pKeyChar->addButton(ui->KeyChM, Qt::Key_M);
	pKeyChar->addButton(ui->KeyChN, Qt::Key_N);
	pKeyChar->addButton(ui->KeyChO, Qt::Key_O);
	pKeyChar->addButton(ui->KeyChP, Qt::Key_P);
	pKeyChar->addButton(ui->KeyChQ, Qt::Key_Q);
	pKeyChar->addButton(ui->KeyChR, Qt::Key_R);
	pKeyChar->addButton(ui->KeyChS, Qt::Key_S);
	pKeyChar->addButton(ui->KeyChT, Qt::Key_T);
	pKeyChar->addButton(ui->KeyChU, Qt::Key_U);
	pKeyChar->addButton(ui->KeyChV, Qt::Key_V);
	pKeyChar->addButton(ui->KeyChW, Qt::Key_W);
	pKeyChar->addButton(ui->KeyChX, Qt::Key_X);
    pKeyChar->addButton(ui->KeyChY, Qt::Key_Y);
	pKeyChar->addButton(ui->KeyChZ, Qt::Key_Z);
	// 组织其他按键
	pKeyOther = new QButtonGroup;
	pKeyOther->addButton(ui->KeyNu1, Qt::Key_1);
	pKeyOther->addButton(ui->KeyNu2, Qt::Key_2);
	pKeyOther->addButton(ui->KeyNu3, Qt::Key_3);
	pKeyOther->addButton(ui->KeyNu4, Qt::Key_4);
	pKeyOther->addButton(ui->KeyNu5, Qt::Key_5);
	pKeyOther->addButton(ui->KeyNu6, Qt::Key_6);
	pKeyOther->addButton(ui->KeyNu7, Qt::Key_7);
	pKeyOther->addButton(ui->KeyNu8, Qt::Key_8);
	pKeyOther->addButton(ui->KeyNu9, Qt::Key_9);
	pKeyOther->addButton(ui->KeyNu0, Qt::Key_0);
	pKeyOther->addButton(ui->KeyPlu, Qt::Key_Plus);
	pKeyOther->addButton(ui->KeyChSub, Qt::Key_Minus);
	pKeyOther->addButton(ui->KeyChMul, Qt::Key_Asterisk);
	pKeyOther->addButton(ui->KeyChDiv, Qt::Key_Slash);
    pKeyOther->addButton(ui->KeyLbr, Qt::Key_ParenLeft);
    pKeyOther->addButton(ui->KeyRbr, Qt::Key_ParenRight);
//	pKeyOther->addButton(ui->KeySim, Qt::Key_Semicolon);
	pKeyOther->addButton(ui->KeyDot, Qt::Key_Period);
//	pKeyOther->addButton(ui->KeyExc, Qt::Key_Exclam);
    pKeyOther->addButton(ui->KeySpace, Qt::Key_Space);
    pKeyOther->addButton(ui->KeyBks, Qt::Key_Backspace);
	// 连接信号槽
	connect(pKeyChar, SIGNAL(buttonClicked(int)), this, SLOT(charsClick(int)));
	connect(pKeyOther, SIGNAL(buttonClicked(int)), this, SLOT(otherClick(int)));
    ui->tableWidget->verticalHeader()->setVisible(false); //隐藏列表头
    ui->tableWidget->horizontalHeader()->setVisible(false); //隐藏行表头
    ui->tableWidget_2->verticalHeader()->setVisible(false); //隐藏列表头
    ui->tableWidget_2->horizontalHeader()->setVisible(false); //隐藏行表头

	ui->tableWidget->horizontalHeader()->setFont(QFont("Microsoft YaHei", 28));
	ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView {font-size: 28px;}");
	ui->tableWidget_2->verticalHeader()->setFont(QFont("Microsoft YaHei", 28));
	ui->tableWidget_2->verticalHeader()->setStyleSheet("QHeaderView {font-size: 28px;}");
    //设置行列宽高
    ui->tableWidget->setRowHeight(0,70);
    ui->tableWidget->setColumnWidth(0,67);
    ui->tableWidget->setColumnWidth(1,67);
    ui->tableWidget->setColumnWidth(2,67);
    ui->tableWidget->setColumnWidth(3,67);
    ui->tableWidget->setColumnWidth(4,67);
    ui->tableWidget->setColumnWidth(5,67);
    ui->tableWidget->setColumnWidth(6,67);
    ui->tableWidget->setColumnWidth(7,67);
    ui->tableWidget->setColumnWidth(8,67);
    quint8 i;
    for(i = 0;i <14;i++)
    {
        ui->tableWidget_2->setRowHeight(i,70);
    }
    for(i = 0;i < 9;i++)
    {
        ui->tableWidget_2->setColumnWidth(i,67);
    }
}

DialogKeyboard::~DialogKeyboard()
{
    delete ui;
	delete pFileV;
	delete pKeyChar;
	delete pKeyOther;
}
static char InputNum[10];//字母输入
static quint8 n ;//输入了几个
QString list,listPY;//匹配的中文串  输入的拼音

int DialogKeyboard::DoForm(QString &str, quint8 type)
{
	int ret;
	// 设置显示状态
	ui->lineEdit->clear();
	if (type == KEYBOARD_TYPE_STR)
	{
		// 输入字符串
		ui->labelTitle->setText(tr("字符键盘"));
        ui->lineEdit->setMaxLength(16);
		ui->lineEdit->setEchoMode(QLineEdit::Normal);
		ui->lineEdit->setValidator(0);
        ui->KeyENCH->setEnabled(true);
	}
	else if (type == KEYBOARD_TYPE_PWD)
	{
		// 输入密码
		ui->labelTitle->setText(tr("输入密码"));
		ui->lineEdit->setMaxLength(8);
		ui->lineEdit->setEchoMode(QLineEdit::Password);
		ui->lineEdit->setValidator(0);
        ui->KeyENCH->setEnabled(false);
        ui->KeyENCH->setText("EN");
	}
	else
	{
		ui->lineEdit->setMaxLength(120);
		ui->labelTitle->setText(tr("输入文件名"));
		ui->lineEdit->setEchoMode(QLineEdit::Normal);
        ui->lineEdit->setValidator(pFileV);
		ui->lineEdit->setText(str);
        ui->KeyENCH->setEnabled(true);
		ui->KeyChDiv->setEnabled(false);
	}
    n = 0;
    memset(InputNum,0,sizeof(char)*10);
    ui->stackedWidget->setCurrentIndex(KEY_PAGE);
    ui->lineEditPY->setText((" "));
    quint8 i;
    for(i = 0;i < 9;i++)
    {
        ui->tableWidget->setItem(0,i,new QTableWidgetItem(" "));
	}
    ui->btnMore->setEnabled(false);
	// 显示对话框
	ret = exec();
	// 返回输入的字符串
	if (ret == QDialog::Accepted)
		str = ui->lineEdit->text();
	else
		str.clear();
	return ret;
}

// 字母按键信号槽
void DialogKeyboard::charsClick(int id)
{
    if(ui->KeyENCH->text() == (tr("中文")))
    {
        uint16_t j;
        switch(id)
        {
        case Qt::Key_A:
            if(n > 9)
                return;
            InputNum[n] = 'a';
            n++;
            break;
        case Qt::Key_B:
            if(n > 9)
                return;
            InputNum[n] = 'b';
            n++;
            break;
        case Qt::Key_C:
            if(n > 9)
                return;
            InputNum[n] = 'c';
            n++;
            break;
        case Qt::Key_D:
            if(n > 9)
                return;
            InputNum[n] = 'd';
            n++;
            break;
        case Qt::Key_E:
            if(n > 9)
                return;
            InputNum[n] = 'e';
            n++;
            break;
        case Qt::Key_F:
            if(n > 9)
                return;
            InputNum[n] = 'f';
            n++;
            break;
        case Qt::Key_G:
            if(n > 9)
                return;
            InputNum[n] = 'g';
            n++;
            break;
        case Qt::Key_H:
            if(n > 9)
                return;
            InputNum[n] = 'h';
            n++;
            break;
        case Qt::Key_I:
            if(n > 9)
                return;
            InputNum[n] = 'i';
            n++;
            break;
        case Qt::Key_J:
            if(n > 9)
                return;
            InputNum[n] = 'j';
            n++;
            break;
        case Qt::Key_K:
            if(n > 9)
                return;
            InputNum[n] = 'k';
            n++;
            break;
        case Qt::Key_L:
            if(n > 9)
                return;
            InputNum[n] = 'l';
            n++;
            break;
        case Qt::Key_M:
            if(n > 9)
                return;
            InputNum[n] = 'm';
            n++;
            break;
        case Qt::Key_N:
            if(n > 9)
                return;
            InputNum[n] = 'n';
            n++;
            break;
        case Qt::Key_O:
            if(n > 9)
                return;
            InputNum[n] = 'o';
            n++;
            break;
        case Qt::Key_P:
            if(n > 9)
                return;
            InputNum[n] = 'p';
            n++;
            break;
        case Qt::Key_Q:
            if(n > 9)
                return;
            InputNum[n] = 'q';
            n++;
            break;
        case Qt::Key_R:
            if(n > 9)
                return;
            InputNum[n] = 'r';
            n++;
            break;
        case Qt::Key_S:
            if(n > 9)
                return;
            InputNum[n] = 's';
            n++;
            break;
        case Qt::Key_T:
            if(n > 9)
                return;
            InputNum[n] = 't';
            n++;
            break;
        case Qt::Key_U:
            if(n > 9)
                return;
            InputNum[n] = 'u';
            n++;
            break;
        case Qt::Key_V:
            if(n > 9)
                return;
            InputNum[n] = 'v';
            n++;
            break;
        case Qt::Key_W:
            if(n > 9)
                return;
            InputNum[n] = 'w';
            n++;
            break;
        case Qt::Key_X:
            if(n > 9)
                return;
            InputNum[n] = 'x';
            n++;
            break;
        case Qt::Key_Y:
            if(n > 9)
                return;
            InputNum[n] = 'y';
            n++;
            break;
        case Qt::Key_Z:
            if(n > 9)
                return;
            InputNum[n] = 'z';
            n++;
            break;

        }
        if(get_pymb_26Key((uint8_t *)InputNum))
        {
            list = QString::fromUtf8(ch_charlist_26Key[0]);
            listPY = QString::fromUtf8(py_list_26Key[0]);
            ui->lineEditPY->setText(listPY);
            ui->tableWidget->setCurrentCell(0,0);
            if(list.count() > 9)
                ui->btnMore->setEnabled(true);
            else
                ui->btnMore->setEnabled(false);
            for(j = 0;j<9; j++)
            {
                if(j <= list.count())
                    ui->tableWidget->setItem(0,j,new QTableWidgetItem(list.mid(j,1)));//(list.mid(j,1)第几个开始，打印几个)
                else
                    ui->tableWidget->setItem(0,j,new QTableWidgetItem(" "));//(list.mid(j,1)第几个开始，打印几个)
            }
//            qDebug()<<"ch_charlist_26Key"<<(list);//QString::fromUtf8
        }
        else
        {
            InputNum[n-1] = 0;
            n--;
            return;
        }
    }
    else
    {
	QKeyEvent event(QEvent::KeyPress, id, Qt::NoModifier, pKeyChar->button(id)->text());
	QApplication::sendEvent(ui->lineEdit, &event);
    }
}
// 其他按键信号槽
void DialogKeyboard::otherClick(int id)
{
    uint16_t j,tmpstr_n;
    QString tmpstr;
	QKeyEvent event(QEvent::KeyPress, id, Qt::NoModifier, pKeyOther->button(id)->text());
    if((id == Qt::Key_Backspace) && (ui->KeyENCH->text() == tr("中文")))//回退键特殊处理
    {
        if(ui->lineEditPY->text() ==  "")
    {
            QApplication::sendEvent(ui->lineEdit, &event);
//            qDebug()<<"fuck1";
        }
        else
        {
//            qDebug()<<"fuck2";
            if(n > 0)
            {
                InputNum[n-1] = 0;
                n--;
            }
            get_pymb_26Key((uint8_t *)InputNum);
            list = QString::fromUtf8(ch_charlist_26Key[0]);
            listPY = QString::fromUtf8(py_list_26Key[0]);
            ui->lineEditPY->setText(listPY);
            for(j = 0;j<9; j++)//打印匹配的字)
            {
                if(j <= list.count())
                    ui->tableWidget->setItem(0,j,new QTableWidgetItem(list.mid(j,1)));
                else
                    ui->tableWidget->setItem(0,j,new QTableWidgetItem(" "));
            }
        }
    }
    else
    {
        if(id == Qt::Key_Space)
        {
            tmpstr = ui->lineEdit->text();
            tmpstr_n = tmpstr.length();
            tmpstr.insert(tmpstr_n," ");
            ui->lineEdit->setText(tmpstr);
        }
        else
            QApplication::sendEvent(ui->lineEdit, &event);
//        qDebug()<<"fuck3";
    }
}

// 大小写切换信号槽
void DialogKeyboard::capsClick(void)
{
    if(ui->KeyENCH->text() == tr("中文"))
        return;
	if (ui->KeyCap->isChecked() == true)
	{
		// 转换成大写字母
		pKeyChar->button(Qt::Key_A)->setText(pKeyChar->button(Qt::Key_A)->text().toUpper());
		pKeyChar->button(Qt::Key_B)->setText(pKeyChar->button(Qt::Key_B)->text().toUpper());
		pKeyChar->button(Qt::Key_C)->setText(pKeyChar->button(Qt::Key_C)->text().toUpper());
		pKeyChar->button(Qt::Key_D)->setText(pKeyChar->button(Qt::Key_D)->text().toUpper());
		pKeyChar->button(Qt::Key_E)->setText(pKeyChar->button(Qt::Key_E)->text().toUpper());
		pKeyChar->button(Qt::Key_F)->setText(pKeyChar->button(Qt::Key_F)->text().toUpper());
		pKeyChar->button(Qt::Key_G)->setText(pKeyChar->button(Qt::Key_G)->text().toUpper());
		pKeyChar->button(Qt::Key_H)->setText(pKeyChar->button(Qt::Key_H)->text().toUpper());
		pKeyChar->button(Qt::Key_I)->setText(pKeyChar->button(Qt::Key_I)->text().toUpper());
		pKeyChar->button(Qt::Key_J)->setText(pKeyChar->button(Qt::Key_J)->text().toUpper());
		pKeyChar->button(Qt::Key_K)->setText(pKeyChar->button(Qt::Key_K)->text().toUpper());
		pKeyChar->button(Qt::Key_L)->setText(pKeyChar->button(Qt::Key_L)->text().toUpper());
		pKeyChar->button(Qt::Key_M)->setText(pKeyChar->button(Qt::Key_M)->text().toUpper());
		pKeyChar->button(Qt::Key_N)->setText(pKeyChar->button(Qt::Key_N)->text().toUpper());
		pKeyChar->button(Qt::Key_O)->setText(pKeyChar->button(Qt::Key_O)->text().toUpper());
		pKeyChar->button(Qt::Key_P)->setText(pKeyChar->button(Qt::Key_P)->text().toUpper());
		pKeyChar->button(Qt::Key_Q)->setText(pKeyChar->button(Qt::Key_Q)->text().toUpper());
		pKeyChar->button(Qt::Key_R)->setText(pKeyChar->button(Qt::Key_R)->text().toUpper());
		pKeyChar->button(Qt::Key_S)->setText(pKeyChar->button(Qt::Key_S)->text().toUpper());
		pKeyChar->button(Qt::Key_T)->setText(pKeyChar->button(Qt::Key_T)->text().toUpper());
		pKeyChar->button(Qt::Key_U)->setText(pKeyChar->button(Qt::Key_U)->text().toUpper());
		pKeyChar->button(Qt::Key_V)->setText(pKeyChar->button(Qt::Key_V)->text().toUpper());
		pKeyChar->button(Qt::Key_W)->setText(pKeyChar->button(Qt::Key_W)->text().toUpper());
		pKeyChar->button(Qt::Key_X)->setText(pKeyChar->button(Qt::Key_X)->text().toUpper());
		pKeyChar->button(Qt::Key_Y)->setText(pKeyChar->button(Qt::Key_Y)->text().toUpper());
		pKeyChar->button(Qt::Key_Z)->setText(pKeyChar->button(Qt::Key_Z)->text().toUpper());
	}
	else
	{
		// 转换成小写字母
		pKeyChar->button(Qt::Key_A)->setText(pKeyChar->button(Qt::Key_A)->text().toLower());
		pKeyChar->button(Qt::Key_B)->setText(pKeyChar->button(Qt::Key_B)->text().toLower());
		pKeyChar->button(Qt::Key_C)->setText(pKeyChar->button(Qt::Key_C)->text().toLower());
		pKeyChar->button(Qt::Key_D)->setText(pKeyChar->button(Qt::Key_D)->text().toLower());
		pKeyChar->button(Qt::Key_E)->setText(pKeyChar->button(Qt::Key_E)->text().toLower());
		pKeyChar->button(Qt::Key_F)->setText(pKeyChar->button(Qt::Key_F)->text().toLower());
		pKeyChar->button(Qt::Key_G)->setText(pKeyChar->button(Qt::Key_G)->text().toLower());
		pKeyChar->button(Qt::Key_H)->setText(pKeyChar->button(Qt::Key_H)->text().toLower());
		pKeyChar->button(Qt::Key_I)->setText(pKeyChar->button(Qt::Key_I)->text().toLower());
		pKeyChar->button(Qt::Key_J)->setText(pKeyChar->button(Qt::Key_J)->text().toLower());
		pKeyChar->button(Qt::Key_K)->setText(pKeyChar->button(Qt::Key_K)->text().toLower());
		pKeyChar->button(Qt::Key_L)->setText(pKeyChar->button(Qt::Key_L)->text().toLower());
		pKeyChar->button(Qt::Key_M)->setText(pKeyChar->button(Qt::Key_M)->text().toLower());
		pKeyChar->button(Qt::Key_N)->setText(pKeyChar->button(Qt::Key_N)->text().toLower());
		pKeyChar->button(Qt::Key_O)->setText(pKeyChar->button(Qt::Key_O)->text().toLower());
		pKeyChar->button(Qt::Key_P)->setText(pKeyChar->button(Qt::Key_P)->text().toLower());
		pKeyChar->button(Qt::Key_Q)->setText(pKeyChar->button(Qt::Key_Q)->text().toLower());
		pKeyChar->button(Qt::Key_R)->setText(pKeyChar->button(Qt::Key_R)->text().toLower());
		pKeyChar->button(Qt::Key_S)->setText(pKeyChar->button(Qt::Key_S)->text().toLower());
		pKeyChar->button(Qt::Key_T)->setText(pKeyChar->button(Qt::Key_T)->text().toLower());
		pKeyChar->button(Qt::Key_U)->setText(pKeyChar->button(Qt::Key_U)->text().toLower());
		pKeyChar->button(Qt::Key_V)->setText(pKeyChar->button(Qt::Key_V)->text().toLower());
		pKeyChar->button(Qt::Key_W)->setText(pKeyChar->button(Qt::Key_W)->text().toLower());
		pKeyChar->button(Qt::Key_X)->setText(pKeyChar->button(Qt::Key_X)->text().toLower());
		pKeyChar->button(Qt::Key_Y)->setText(pKeyChar->button(Qt::Key_Y)->text().toLower());
		pKeyChar->button(Qt::Key_Z)->setText(pKeyChar->button(Qt::Key_Z)->text().toLower());
	}
}

// 确定按钮槽
void DialogKeyboard::acceptInput(void)
{
	if (ui->lineEdit->text().isEmpty())
		return;
	accept();
}
void DialogKeyboard::clearClick(void)
{
    if(ui->KeyENCH->text() == tr("中文"))
    {
        memset(InputNum,0,sizeof(char)*10);
        n = 0;
        ui->tableWidget->clear();
        ui->lineEditPY->clear();
    }
    else
    {
	ui->lineEdit->setText("");
    }

}

void DialogKeyboard::changeEnglishChinese()
{
    if(ui->KeyENCH->text() == tr("EN"))
        ui->KeyENCH->setText(tr("中文"));
    else
        ui->KeyENCH->setText(tr("EN"));
}

void DialogKeyboard::showMore()
{
//    qDebug()<<list;
    uint8_t i,j,k;
    ui->stackedWidget->setCurrentIndex(TEXT_PAGE);
    ui->tableWidget_2->setCurrentCell(0,0);
    k = 0;
    for(i = 0; i < 14; i++)
    {
        for(j = 0; j < 9; j++)
        {
            ui->tableWidget_2->setItem(i,j,new QTableWidgetItem(list.mid(k,1)));//(list.mid(j,1)第几个开始，打印几个)
//            qDebug()<<list.mid(k,1);
            k++;
        }

    }
}

void DialogKeyboard::tableWidgeClick(int row, int column)
{
    quint8 i;
    /************************************pyq 解决输入中文时点击C清除键后再点击显示中文字的表格就会死机的问题*****************************************************/
//    if(ui->tableWidget->item(0,column)->text() == (" "))
    if(ui->tableWidget->item(0,column) == NULL || (ui->tableWidget->item(0,column) && ui->tableWidget->item(0,column)->text() == (" ")))
    /*************************************pyq end****************************************************/
        return;
    QString content;
    content = ui->lineEdit->text().append(ui->tableWidget->item(0,column)->text());
    ui->lineEdit->setText(content);
    n = 0;
    memset(InputNum,0,sizeof(char)*10);
    ui->lineEditPY->setText("");
    listPY = "";
    ui->btnMore->setEnabled(false);
    for(i = 0;i < 9;i++)
    {
        ui->tableWidget->setItem(0,i,new QTableWidgetItem(" "));
    }
}

void DialogKeyboard::tableWidge2Click(int row, int column)
{
    quint8 i;
    QString content;
    content = ui->lineEdit->text().append(ui->tableWidget_2->item(row,column)->text());
    ui->lineEdit->setText(content);
    ui->stackedWidget->setCurrentIndex(KEY_PAGE);
    n = 0;
    memset(InputNum,0,sizeof(char)*10);
    listPY = "";
    ui->btnMore->setEnabled(false);
    for(i = 0;i < 9;i++)
    {
        ui->tableWidget->setItem(0,i,new QTableWidgetItem(" "));
    }
}
uint8_t DialogKeyboard::get_pymb_26Key(uint8_t* str)
{
    return get_matched_pymb_26Key(str,py_list_26Key,ch_charlist_26Key);
}
