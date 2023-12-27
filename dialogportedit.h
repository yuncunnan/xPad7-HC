#ifndef DIALOGPORTEDIT_H
#define DIALOGPORTEDIT_H

#include <QDialog>
#include "dialogkeyboard.h"

// 主板扩展输入
#define MAIN_X00                 0
#define MAIN_X01                 1
#define MAIN_X02                 2
#define MAIN_X03                 3
#define MAIN_X04                 4
#define MAIN_X05                 5
#define MAIN_X06                 6
#define MAIN_X07                 7
#define MAIN_X08                 8
#define MAIN_X09                 9
#define MAIN_X10                 10
#define MAIN_X11                 11
#define MAIN_X12                 12
#define MAIN_X13                 13
#define MAIN_X14                 14
#define MAIN_X15                 15

// 扩展模块1扩展输入
#define EM1_X00                 16
#define EM1_X01					17
#define EM1_X02					18
#define EM1_X03					19
#define EM1_X04					20
#define EM1_X05					21
#define EM1_X06					22
#define EM1_X07					23
#define EM1_X08					24
#define EM1_X09					25
#define EM1_X10					26
#define EM1_X11					27
#define EM1_X12					28
#define EM1_X13					29
#define EM1_X14					30
#define EM1_X15					31

// 扩展模块2扩展输入
#define EM2_X00					32
#define EM2_X01					33
#define EM2_X02					34
#define EM2_X03					35
#define EM2_X04					36
#define EM2_X05					37
#define EM2_X06					38
#define EM2_X07					39
#define EM2_X08					40
#define EM2_X09					41
#define EM2_X10					42
#define EM2_X11					43
#define EM2_X12					44
#define EM2_X13					45
#define EM2_X14					46
#define EM2_X15					47
// 扩展模块3扩展输入
#define EM3_X00					48
#define EM3_X01					49
#define EM3_X02					50
#define EM3_X03					51
#define EM3_X04					52
#define EM3_X05					53
#define EM3_X06					54
#define EM3_X07					55
#define EM3_X08					56
#define EM3_X09					57
#define EM3_X10					58
#define EM3_X11					59
#define EM3_X12					60
#define EM3_X13					61
#define EM3_X14					62
#define EM3_X15					63
// 扩展模块4扩展输入
#define EM4_X00					64
#define EM4_X01					65
#define EM4_X02					66
#define EM4_X03					67
#define EM4_X04					68
#define EM4_X05					69
#define EM4_X06					70
#define EM4_X07					71
#define EM4_X08					72
#define EM4_X09					73
#define EM4_X10					74
#define EM4_X11					75
#define EM4_X12					76
#define EM4_X13					77
#define EM4_X14					78
#define EM4_X15					79
#define MAX_INPORT_NUM           80


//pyq
#define MAIN_X16                 80
#define MAIN_X17                 81
#define MAIN_X18                 82
#define MAIN_X19                 83
#define MAIN_X20                 84
#define MAIN_X21                 85
#define MAIN_X22                 86
#define MAIN_X23                 87
#define MAIN_X24                 88
#define MAIN_X25                 89
#define MAIN_X26                 90
#define MAIN_X27                 91
#define MAIN_X28                 92
#define MAIN_X29                 93
#define MAIN_X30                 94
#define MAIN_X31                 95

#define MAX_INPORT_NUM2          96
#define MAX_INPORT_NUM3          92     //BOARD_VERSION_H750_5AXIS版

//// 注塑机输入
//#define IMM_IN_STOP				80
//#define IMM_IN_SAFE				81
//#define IMM_IN_REJECT             82
//#define IMM_IN_MCP				83
//#define IMM_IN_MOP				84
//#define IMM_IN_IMOP				85
//#define IMM_IN_AUTO				86
//#define IMM_IN_EBP				87
//#define IMM_IN_EFP				88
//#define IMM_IN_MID				89
//#define IMM_IN_C1P1				90
//#define IMM_IN_C1P2				91
//#define IMM_IN_C2P1				92
//#define IMM_IN_C2P2				93
//// 机械手输入
//#define RBT_IN_LOW_AIR			94
//#define RBT_IN_DWN_SAF			95
//#define RBT_IN_PRO_HOR			96
//#define RBT_IN_PRO_VER			97
//#define RBT_IN_ARM_SAF			98
//#define RBT_IN_RUN_ASC			99
//#define RBT_IN_RUN_DES			100
//#define RBT_IN_PRO_ADV			101
//#define RBT_IN_PRO_RET			102
//#define RBT_IN_RUN_ADV			103
//#define RBT_IN_RUN_RET			104
//#define RBT_IN_RUN_HOR			105
//#define RBT_IN_RUN_VER			106

//#define MAX_INPORT_NUM          107
//---------------------------------------------------------

// 主板扩展输出
#define MAIN_Y00                 0
#define MAIN_Y01                 1
#define MAIN_Y02                 2
#define MAIN_Y03                 3
#define MAIN_Y04                 4
#define MAIN_Y05                 5
#define MAIN_Y06                 6
#define MAIN_Y07                 7
#define MAIN_Y08                 8
#define MAIN_Y09                 9
#define MAIN_Y10                 10
#define MAIN_Y11                 11
#define MAIN_Y12                 12
#define MAIN_Y13                 13
#define MAIN_Y14                 14
#define MAIN_Y15                 15

// 扩展模块1扩展输出
#define EM1_Y00                 16
#define EM1_Y01					17
#define EM1_Y02					18
#define EM1_Y03					19
#define EM1_Y04					20
#define EM1_Y05					21
#define EM1_Y06					22
#define EM1_Y07					23
#define EM1_Y08					24
#define EM1_Y09					25
#define EM1_Y10					26
#define EM1_Y11					27
#define EM1_Y12					28
#define EM1_Y13					29
#define EM1_Y14					30
#define EM1_Y15					31

// 扩展模块2扩展输出
#define EM2_Y00					32
#define EM2_Y01					33
#define EM2_Y02					34
#define EM2_Y03					35
#define EM2_Y04					36
#define EM2_Y05					37
#define EM2_Y06					38
#define EM2_Y07					39
#define EM2_Y08					40
#define EM2_Y09					41
#define EM2_Y10					42
#define EM2_Y11					43
#define EM2_Y12					44
#define EM2_Y13					45
#define EM2_Y14					46
#define EM2_Y15					47
// 扩展模块3扩展输出
#define EM3_Y00					48
#define EM3_Y01					49
#define EM3_Y02					50
#define EM3_Y03					51
#define EM3_Y04					52
#define EM3_Y05					53
#define EM3_Y06					54
#define EM3_Y07					55
#define EM3_Y08					56
#define EM3_Y09					57
#define EM3_Y10					58
#define EM3_Y11					59
#define EM3_Y12					60
#define EM3_Y13					61
#define EM3_Y14					62
#define EM3_Y15					63
// 扩展模块4扩展输出
#define EM4_Y00					64
#define EM4_Y01					65
#define EM4_Y02					66
#define EM4_Y03					67
#define EM4_Y04					68
#define EM4_Y05					69
#define EM4_Y06					70
#define EM4_Y07					71
#define EM4_Y08					72
#define EM4_Y09					73
#define EM4_Y10					74
#define EM4_Y11					75
#define EM4_Y12					76
#define EM4_Y13					77
#define EM4_Y14					78
#define EM4_Y15					79
#define MAX_OUTPORT_NUM          80

//pyq
#define MAIN_Y16                 80
#define MAIN_Y17                 81
#define MAIN_Y18                 82
#define MAIN_Y19                 83
#define MAIN_Y20                 84
#define MAIN_Y21                 85
#define MAIN_Y22                 86
#define MAIN_Y23                 87
#define MAIN_Y24                 88
#define MAIN_Y25                 89
#define MAIN_Y26                 90
#define MAIN_Y27                 91
#define MAIN_Y28                 92

#define MAX_OUTPORT_NUM3         93     //BOARD_VERSION_H750_5AXIS版

#define MAIN_Y29                 93
#define MAIN_Y30                 94
#define MAIN_Y31                 95
#define MAX_OUTPORT_NUM2          96

//// 注塑机输出
//#define IMM_OUT_MAF				80
//#define IMM_OUT_EMC				81
//#define IMM_OUT_EMO				82
//#define IMM_OUT_RBT				83
//#define IMM_OUT_EEB				84
//#define IMM_OUT_EEF				85
//#define IMM_OUT_C1P1			86
//#define IMM_OUT_C1P2			87
//#define IMM_OUT_C2P1			88
//#define IMM_OUT_C2P2			89
//#define IMM_OUT_HMAF			90
//#define IMM_OUT_HEMC			91
//// 机械手输出
//#define RBT_OUT_PRO_HOR			92
//#define RBT_OUT_PRO_VER			93
//#define RBT_OUT_ALM_BEEP		94
//#define RBT_OUT_ALM_LAMP		95
//#define RBT_OUT_LAMP			96
//#define RBT_OUT_RUN_DES			97
//#define RBT_OUT_RUN_SPEED		98
//#define RBT_OUT_PRO_ADV			99
//#define RBT_OUT_PRO_RET			100
//#define RBT_OUT_RUN_ADV			101
//#define RBT_OUT_RUN_RET			102
//#define RBT_OUT_OIL				103
//#define RBT_OUT_RUN_HOR			104
//#define RBT_OUT_RUN_VER			105

//#define MAX_OUTPORT_NUM         106

namespace Ui {
class DialogPortEdit;
}

class DialogPortEdit : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogPortEdit(QWidget *parent = 0);
    ~DialogPortEdit();
    
    int DoForm(void);

private:
    Ui::DialogPortEdit *ui;
    void InitInPortName(void);
    void InitOutPortName(void);
    void setIOVisible(void);//设置io显示状态
    void retranslateUi(void);				// 更新界面字符串翻译
private slots:
    void tableWidgeCellClicked(int row,int column);//输入端口修改名称
    void tableWidgeOutCellClicked(int row,int column);//输出端口修改名称
   void NewPortFile(void);
};


#endif // DIALOGPORTEDIT_H
