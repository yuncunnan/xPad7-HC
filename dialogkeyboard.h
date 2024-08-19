#ifndef DIALOGKEYBOARD_H
#define DIALOGKEYBOARD_H

#include <QDialog>
#include <QRegExpValidator>
#include "xstringresource.h"

class QButtonGroup;

#define MAX_INPUT_NUM				20
#define KEYBOARD_TYPE_STR			0
#define KEYBOARD_TYPE_PWD			1
#define KEYBOARD_TYPE_FILENAME		2

namespace Ui {
class DialogKeyboard;
}

class DialogKeyboard : public QDialog
{
    Q_OBJECT
    
public:
	explicit DialogKeyboard(QWidget *parent = 0);
    ~DialogKeyboard();

	int DoForm(QString &str, quint8 type = KEYBOARD_TYPE_STR);
private:
    Ui::DialogKeyboard *ui;
	QRegExpValidator *pFileV;
	QButtonGroup *pKeyChar;
	QButtonGroup *pKeyOther;
//    char  *py_list_26Key[50];
    char  *ch_charlist_26Key;
    quint8 get_pymb_26Key(quint8* str);
	static char InputNum[MAX_INPUT_NUM];//字母输入
	static quint8 n ;//输入了几个
    QString list;//匹配的中文串  输入的拼音

private slots:
	void charsClick(int id);				// 字母按键信号槽
	void otherClick(int id);				// 其他按键信号槽
	void capsClick(void);					// 大小写切换信号槽
	void acceptInput(void);				// 确定按钮槽
	void clearClick(void);					// 清除按钮
    void clearClickTableWidget(void);		// 清除汉字选择框
    void changeEnglishChinese(void);        //中英文切换
    void showMore(void);                    //显示更多中文
    void tableWidgeClick(int row, int column);          //备选表格被点击
    void tableWidge2Click(int row, int column);         //备选大表格被点击
};

extern DialogKeyboard *xKbd;

#endif // DIALOGKEYBOARD_H
