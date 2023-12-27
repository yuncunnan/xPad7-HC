#include <QSettings>
#include "xconfig.h"
#include "cmbprotocol.h"

#include "codeimm.h"
#include "codepos.h"
#include "codeextpos.h"
#include "codeend.h"
#include "codeparm.h"
#include "codevacuum.h"
#include "codeextout.h"
#include "codeloopmatrix.h"

#include "alfamodel.h"

#define INI_ALFA_MODE_PRO                 "mode/pro"
#define INI_ALFA_MODE_RUN                 "mode/run"
//#define INI_ALFA_MODE_PRO_REL             "mode/pro_release"

#define INI_ALFA_VAC_PRO_BMP              "vac/probmp"
#define INI_ALFA_VAC_PRO_CHK              "vac/prochk"
#define INI_ALFA_VAC_PRO_DELAY            "vac/prodelay"

#define INI_ALFA_VAC_RUN_BMP              "vac/runbmp"
#define INI_ALFA_VAC_RUN_CHK              "vac/runchk"
#define INI_ALFA_VAC_RUN_DELAY            "vac/rundelay"

#define INI_ALFA_OTHER_ROTATE_DELAY       "other/rotatedelay"

#define INI_ALFA_IMM_EJECTORFRONT         "imm/ejectorfront"
#define INI_ALFA_IMM_EJECTORFRONTDELAY    "imm/ejectorfrontdelay"
#define INI_ALFA_IMM_EJECTORBACK          "imm/ejectorback"
#define INI_ALFA_IMM_EJECTORBACKDELAY     "imm/ejectorbackdelay"
#define INI_ALFA_IMM_C1FRONT              "imm/c1front"
#define INI_ALFA_IMM_C1FRONTDELAY         "imm/c1frontdelay"
#define INI_ALFA_IMM_C1BACK               "imm/c1back"
#define INI_ALFA_IMM_C1BACKDELAY          "imm/c1backdelay"
#define INI_ALFA_IMM_C2FRONT              "imm/c2front"
#define INI_ALFA_IMM_C2FRONTDELAY         "imm/c2frontdelay"
#define INI_ALFA_IMM_C2BACK               "imm/c2back"
#define INI_ALFA_IMM_C2BACKDELAY          "imm/c2backdelay"
#define INI_ALFA_IMM_MOP_TIMEOUT          "imm/MOPtimeout"
#define INI_ALFA_IMM_EMC_DELAY            "imm/EMCdelay"

#define INI_ALFA_CONVEYOR_USE             "conveyor/use"
#define INI_ALFA_CONVEYOR_OUT             "conveyor/out"
#define INI_ALFA_CONVEYOR_DELAY           "conveyor/delay"
#define INI_ALFA_CONVEYOR_INTERVAL        "conveyor/interval"

#define INI_ALFA_POS_ZPRO_RELEASE         "pos/zprorelease"
#define INI_ALFA_POS_ZRUN_RELEASE         "pos/zrunrelease"
#define INI_ALFA_POS_ZPRO_CATCH           "pos/zprocatch"

#define INI_ALFA_POS_XPRO_DOWN            "pos/xprodown"
#define INI_ALFA_POS_BRUN_DOWN            "pos/brundown"

#define INI_ALFA_POS_XPRO_UP              "pos/xproup"
#define INI_ALFA_POS_BRUN_UP              "pos/brunup"

#define INI_ALFA_POS_XPRO_CATCH           "pos/xprocatch"
#define INI_ALFA_POS_BRUN_CATCH           "pos/bruncatch"

#define INI_ALFA_POS_XPRO_RELEASE         "pos/xprorelease"
#define INI_ALFA_POS_BRUN_RELEASE         "pos/brunrelease"

#define INI_ALFA_POS_YPRO_CATCH           "pos/yprocatch"
#define INI_ALFA_POS_ARUN_CATCH           "pos/aruncatch"

#define INI_ALFA_POS_YPRO_RELEASE         "pos/yprorelease"
#define INI_ALFA_POS_ARUN_RELEASE         "pos/arunrelease"

#define INI_ALFA_POS_YPRO_WAIT            "pos/yprowait"
#define INI_ALFA_POS_ARUN_WAIT            "pos/arunwait"
#define INI_ALFA_POS_PRO_RELEASE          "pos/proreleaseuse"

#define INI_ALFA_SPEED_X                  "speed/x"
#define INI_ALFA_SPEED_Y                  "speed/y"
#define INI_ALFA_SPEED_Y_OUT              "speed/yout"
#define INI_ALFA_SPEED_Z                  "speed/z"
#define INI_ALFA_SPEED_A                  "speed/a"
#define INI_ALFA_SPEED_A_OUT              "speed/aout"
#define INI_ALFA_SPEED_B                  "speed/b"
#define INI_ALFA_SPEED_C                  "speed/c"

#define INI_ALFA_MATRIX_SPEED             "matrix/speed"
#define INI_ALFA_MATRIX_DSPEED            "matrix/dspeed"
#define INI_ALFA_MATRIX_DLEN              "matrix/dlen"
#define INI_ALFA_MATRIX_ISRUNNER          "matrix/isrunner"
#define INI_ALFA_MATRIX_TRVROT            "matrix/trvrot"
#define INI_ALFA_MATRIX_DEC               "matrix/dec"
#define INI_ALFA_MATRIX_HORIZONTAL        "matrix/horizontal"
#define INI_ALFA_MATRIX_DEC_PRIOR         "matrix/decprior"
#define INI_ALFA_MATRIX_REL_X             "matrix/relx"
#define INI_ALFA_MATRIX_REL_Y             "matrix/rely"
#define INI_ALFA_MATRIX_REL_Z             "matrix/relz"
#define INI_ALFA_MATRIX_XS                "matrix/xs"
#define INI_ALFA_MATRIX_YS                "matrix/ys"
#define INI_ALFA_MATRIX_ZS                "matrix/zs"
#define INI_ALFA_MATRIX_XINTERVAL         "matrix/xinterval"
#define INI_ALFA_MATRIX_YINTERVAL         "matrix/yinterval"
#define INI_ALFA_MATRIX_ZINTERVAL         "matrix/zinterval"
#define INI_ALFA_MATRIX_POS_X             "matrix/posx"
#define INI_ALFA_MATRIX_POS_Y             "matrix/posy"
#define INI_ALFA_MATRIX_POS_Z             "matrix/posz"

#define INI_ALFA_ROTATE_TRVIN             "rotate/trvin"
#define INI_ALFA_ROTATE_TRVOUT            "rotate/trvout"
#define INI_ALFA_ROTATE_FETCH             "rotate/fetch"
#define INI_ALFA_ROTATE_RELEASE           "rotate/release"

AlfaModel::AlfaModel(QObject *parent) :
    QObject(parent)
{
    m_pro_mode = PRO_MODE_NONE;
    m_run_mode = RUN_MODE_NONE;
}

bool AlfaModel::NewProgram(const QString & filename)                    // 建立一个新程序，即清除所有列表中的指令,加入一条END语句
{
    m_filename = filename;

    m_pro_mode = PRO_MODE_NONE;
    m_run_mode = RUN_MODE_NONE;
//    m_pro_release_mode = 0;      //主臂置物模式：0表示用横行置物点置物；1表示用矩阵特点置物

    m_pro_vacbmp = 0;           //主臂冶具映像
    m_pro_vacchk = 0;           //主臂冶具检测映像
    m_pro_vacdelay = 0;         //主臂冶具延时

    m_run_vacbmp = 0;           //副臂冶具映像
    m_run_vacchk = 0;           //副臂冶具检测映像
    m_run_vacdelay = 0;         //副臂冶具延时

    //动作延时
    m_rotate_delay = 0;             //倒角延时

    //塑机控制
    m_ejectorfront = 0;                 //顶针进控制
    m_ejectorfrontdelay = 0;            //顶针进延时
    m_ejectorback = 0;                  //顶针退控制
    m_ejectorbackdelay = 0;             //顶针退延时
    m_c1front = 0;                      //抽芯1进控制
    m_c1frontdelay = 0;                 //抽芯1进延时
    m_c1back = 0;                       //抽芯1退控制
    m_c1backdelay = 0;                  //抽芯1退延时
    m_c2front = 0;                      //抽芯2进控制
    m_c2frontdelay = 0;                 //抽芯2进延时
    m_c2back = 0;                       //抽芯2退控制
    m_c2backdelay = 0;                  //抽芯2退延时
    m_mop_timeout = 0;                  //开模超时
    m_emc_delay = 0;                    //关模延时

    //传送带控制
    m_conveyor = 0;                       //传送带控制
    m_conveyorout = EM1_VAR_Y15;          //传送带输出
    m_conveyordelay = 100;                //传送带时间
    m_conveyorinterval = 0;               //传送带间隔

    //各轴运行速度
    m_x_speed = 10;
    m_y_speed = 10;
    m_y_speed_outmold = 10;
    m_z_speed = 10;
    m_a_speed = 10;
    m_a_speed_outmold = 10;
    m_b_speed = 10;
    m_c_speed = 10;

    //位置
    m_z_pro_release_pos = 0;     //横行轴置物点
    m_z_run_release_pos = 0;     //横行轴料物点
    m_z_catch_pos = 100000;           //横行轴模内取物点

    m_x_pro_down_pos = 0;        //模内主臂引拔轴下行点
    m_b_run_down_pos = 0;        //模内副臂引拔轴下行点

    m_x_pro_up_pos = 0;        //模内主臂引拔轴上行点
    m_b_run_up_pos = 0;        //模内副臂引拔轴上行点

    m_x_pro_catch_pos = 10000;       //模内主臂引拔轴取物点
    m_b_run_catch_pos = 10000;       //模内副臂引拔轴取物点

    m_x_pro_release_pos = 0;       //模外主臂引拔轴置物点
    m_b_run_release_pos = 0;       //模外副臂引拔轴置物点

    m_y_pro_catch_pos = 20000;       //模内主臂上下轴取物点
    m_a_run_catch_pos = 20000;       //模内副臂上下轴取物点

    m_y_pro_release_pos = 20000;     //模外主臂上下轴置物点
    m_a_run_release_pos = 20000;     //模外副臂上下轴置物点

    m_y_pro_wait_pos = 0;     //模内主臂上下轴等待开模点
    m_a_run_wait_pos = 0;     //模内副臂上下轴等待开模点

    //矩阵
    m_matrix_speed = 50;          //运行速度
    m_matrix_dspeed = 10;         //减速速度
    m_matrix_dlen = 0;          //减速距离
    m_matrix_isrunner = 0;         //副臂
    m_matrix_trvrot = 0;
    m_matrix_dec_axes = 0;         //减速轴	0:表示上下轴 1:表示引拨轴
    m_matrix_horizontal = 0;       //倒角方式	0:表示回正 1:表示侧姿
    m_matrix_dec_axes_prior = 0x80;
    m_matrix_rel_posx = 0;         //引拨轴第一点位置是相对位置
    m_matrix_rel_posy = 0;         //上下轴第一点位置是相对位置
    m_matrix_rel_posz = 0;         //横行轴第一点位置是相对位置

    m_matrix_xs = 1;			//引拨轴数量
    m_matrix_x_interval = 0;	//引拨轴间隔

    m_matrix_ys = 1;			//上下轴数量
    m_matrix_y_interval = 0;	//上下轴间隔

    m_matrix_zs = 1;			//横行轴数量
    m_matrix_z_interval = 0; 	//横行轴间隔

    m_matrix_posx = 0;			//引拨轴第一点位置
    m_matrix_posy = 0;			//上下轴第一点位置
    m_matrix_posz = 0;			//横行轴第一点位置

    m_rotate_trvin = 1;         // 横入横出置物都默认水平，取物默认倒直
    m_rotate_trvout = 1;
    m_rotate_release = 1;
    m_rotate_fetch = 0;
    m_pro_release_use = 0;      // 主臂置料使用

    return true;
}

bool AlfaModel::SaveProgram(void)		// 保存程序到文件
{
    return SaveAs(m_filename);
}

QString AlfaModel::GetRunPgmName(void)
{
    QString ret;
    if (m_filename.length()>5)
    {
        ret = m_filename.left(m_filename.length()-5)+PGM_FILE_EXT;
    }
    return ret;
}

bool AlfaModel::SaveAs(const QString &filename)		//保存到INI文件
{
    if (filename.isEmpty()) return false;

    QSettings alfa(filename, QSettings::IniFormat);
    //////////////////////////////////////////////////////////////
    alfa.setValue(INI_ALFA_MODE_PRO, m_pro_mode);
    alfa.setValue(INI_ALFA_MODE_RUN, m_run_mode);
//    alfa.setValue(INI_ALFA_MODE_PRO_REL, m_pro_release_mode);

    //////////////////////////////////////////////////////////////
    alfa.setValue(INI_ALFA_VAC_PRO_BMP, m_pro_vacbmp);
    alfa.setValue(INI_ALFA_VAC_PRO_CHK, m_pro_vacchk);
    alfa.setValue(INI_ALFA_VAC_PRO_DELAY, m_pro_vacdelay);

    //////////////////////////////////////////////////////////////
    alfa.setValue(INI_ALFA_VAC_RUN_BMP, m_run_vacbmp);
    alfa.setValue(INI_ALFA_VAC_RUN_CHK, m_run_vacchk);
    alfa.setValue(INI_ALFA_VAC_RUN_DELAY, m_run_vacdelay);

    //////////////////////////////////////////////////////////////
    alfa.setValue(INI_ALFA_OTHER_ROTATE_DELAY, m_rotate_delay);

    //////////////////////////////////////////////////////////////
    alfa.setValue(INI_ALFA_IMM_EJECTORFRONT, m_ejectorfront);
    alfa.setValue(INI_ALFA_IMM_EJECTORFRONTDELAY, m_ejectorfrontdelay);
    alfa.setValue(INI_ALFA_IMM_EJECTORBACK, m_ejectorback);
    alfa.setValue(INI_ALFA_IMM_EJECTORBACKDELAY, m_ejectorbackdelay);

    alfa.setValue(INI_ALFA_IMM_C1FRONT, m_c1front);
    alfa.setValue(INI_ALFA_IMM_C1FRONTDELAY, m_c1frontdelay);
    alfa.setValue(INI_ALFA_IMM_C1BACK, m_c1back);
    alfa.setValue(INI_ALFA_IMM_C1BACKDELAY, m_c1backdelay);

    alfa.setValue(INI_ALFA_IMM_C2FRONT, m_c2front);
    alfa.setValue(INI_ALFA_IMM_C2FRONTDELAY, m_c2frontdelay);
    alfa.setValue(INI_ALFA_IMM_C2BACK, m_c2back);
    alfa.setValue(INI_ALFA_IMM_C2BACKDELAY, m_c2backdelay);

    alfa.setValue(INI_ALFA_IMM_MOP_TIMEOUT, m_mop_timeout);
    alfa.setValue(INI_ALFA_IMM_EMC_DELAY, m_emc_delay);

    //////////////////////////////////////////////////////////////
    alfa.setValue(INI_ALFA_CONVEYOR_USE, m_conveyor);
    alfa.setValue(INI_ALFA_CONVEYOR_OUT, m_conveyorout);
    alfa.setValue(INI_ALFA_CONVEYOR_DELAY, m_conveyordelay);
    alfa.setValue(INI_ALFA_CONVEYOR_INTERVAL, m_conveyorinterval);

    //////////////////////////////////////////////////////////////
    alfa.setValue(INI_ALFA_POS_ZPRO_RELEASE, m_z_pro_release_pos);
    alfa.setValue(INI_ALFA_POS_ZRUN_RELEASE, m_z_run_release_pos);
    alfa.setValue(INI_ALFA_POS_ZPRO_CATCH, m_z_catch_pos);

    alfa.setValue(INI_ALFA_POS_XPRO_DOWN, m_x_pro_down_pos);
    alfa.setValue(INI_ALFA_POS_BRUN_DOWN, m_b_run_down_pos);

    alfa.setValue(INI_ALFA_POS_XPRO_UP, m_x_pro_up_pos);
    alfa.setValue(INI_ALFA_POS_BRUN_UP, m_b_run_up_pos);

    alfa.setValue(INI_ALFA_POS_XPRO_CATCH, m_x_pro_catch_pos);
    alfa.setValue(INI_ALFA_POS_BRUN_CATCH, m_b_run_catch_pos);

    alfa.setValue(INI_ALFA_POS_XPRO_RELEASE, m_x_pro_release_pos);
    alfa.setValue(INI_ALFA_POS_BRUN_RELEASE, m_b_run_release_pos);

    alfa.setValue(INI_ALFA_POS_YPRO_CATCH, m_y_pro_catch_pos);
    alfa.setValue(INI_ALFA_POS_ARUN_CATCH, m_a_run_catch_pos);

    alfa.setValue(INI_ALFA_POS_YPRO_RELEASE, m_y_pro_release_pos);
    alfa.setValue(INI_ALFA_POS_ARUN_RELEASE, m_a_run_release_pos);

    alfa.setValue(INI_ALFA_POS_YPRO_WAIT, m_y_pro_wait_pos);
    alfa.setValue(INI_ALFA_POS_ARUN_WAIT, m_a_run_wait_pos);

    //////////////////////////////////////////////////////////////
    alfa.setValue(INI_ALFA_SPEED_X, m_x_speed);
    alfa.setValue(INI_ALFA_SPEED_Y, m_y_speed);
    alfa.setValue(INI_ALFA_SPEED_Y_OUT, m_y_speed_outmold);
    alfa.setValue(INI_ALFA_SPEED_Z, m_z_speed);
    alfa.setValue(INI_ALFA_SPEED_A, m_a_speed);
    alfa.setValue(INI_ALFA_SPEED_A_OUT, m_a_speed_outmold);
    alfa.setValue(INI_ALFA_SPEED_B, m_b_speed);
    alfa.setValue(INI_ALFA_SPEED_C, m_c_speed);

    //////////////////////////////////////////////////////////////
    alfa.setValue(INI_ALFA_MATRIX_SPEED, m_matrix_speed);
    alfa.setValue(INI_ALFA_MATRIX_DSPEED, m_matrix_dspeed);
    alfa.setValue(INI_ALFA_MATRIX_DLEN, m_matrix_dlen);
    alfa.setValue(INI_ALFA_MATRIX_ISRUNNER, m_matrix_isrunner);
    alfa.setValue(INI_ALFA_MATRIX_TRVROT, m_matrix_trvrot);
    alfa.setValue(INI_ALFA_MATRIX_DEC, m_matrix_dec_axes);
    alfa.setValue(INI_ALFA_MATRIX_HORIZONTAL, m_matrix_horizontal);
    alfa.setValue(INI_ALFA_MATRIX_DEC_PRIOR, m_matrix_dec_axes_prior);
    alfa.setValue(INI_ALFA_MATRIX_REL_X, m_matrix_rel_posx);
    alfa.setValue(INI_ALFA_MATRIX_REL_Y, m_matrix_rel_posy);
    alfa.setValue(INI_ALFA_MATRIX_REL_Z, m_matrix_rel_posz);
    alfa.setValue(INI_ALFA_MATRIX_XS, m_matrix_xs);
    alfa.setValue(INI_ALFA_MATRIX_XINTERVAL, m_matrix_x_interval);
    alfa.setValue(INI_ALFA_MATRIX_YS, m_matrix_ys);
    alfa.setValue(INI_ALFA_MATRIX_YINTERVAL, m_matrix_y_interval);
    alfa.setValue(INI_ALFA_MATRIX_ZS, m_matrix_zs);
    alfa.setValue(INI_ALFA_MATRIX_ZINTERVAL, m_matrix_z_interval);
    alfa.setValue(INI_ALFA_MATRIX_POS_X, m_matrix_posx);
    alfa.setValue(INI_ALFA_MATRIX_POS_Y, m_matrix_posy);
    alfa.setValue(INI_ALFA_MATRIX_POS_Z, m_matrix_posz);

    alfa.setValue(INI_ALFA_ROTATE_TRVIN, m_rotate_trvin);
    alfa.setValue(INI_ALFA_ROTATE_TRVOUT, m_rotate_trvout);
    alfa.setValue(INI_ALFA_ROTATE_FETCH, m_rotate_fetch);
    alfa.setValue(INI_ALFA_ROTATE_RELEASE, m_rotate_release);
    alfa.setValue(INI_ALFA_POS_PRO_RELEASE, m_pro_release_use);

    alfa.sync();
#if defined(Q_OS_LINUX)
    sync();
#endif
    return true;
}

bool AlfaModel::LoadProgram(const QString &filename)//装载INI文件
{
    QSettings alfa(filename, QSettings::IniFormat);
    //////////////////////////////////////////////////////////////
    m_pro_mode = alfa.value(INI_ALFA_MODE_PRO, 0).toUInt();
    m_run_mode = alfa.value(INI_ALFA_MODE_RUN, 0).toUInt();
//    m_pro_release_mode = alfa.value(INI_ALFA_MODE_PRO_REL, 0).toUInt();

    //////////////////////////////////////////////////////////////
    m_pro_vacbmp = alfa.value(INI_ALFA_VAC_PRO_BMP, 0).toUInt();
    m_pro_vacchk = alfa.value(INI_ALFA_VAC_PRO_CHK, 0).toUInt();
    m_pro_vacdelay = alfa.value(INI_ALFA_VAC_PRO_DELAY, 0).toUInt();

    //////////////////////////////////////////////////////////////
    m_run_vacbmp = alfa.value(INI_ALFA_VAC_RUN_BMP, 0).toUInt();
    m_run_vacchk = alfa.value(INI_ALFA_VAC_RUN_CHK, 0).toUInt();
    m_run_vacdelay = alfa.value(INI_ALFA_VAC_RUN_DELAY, 0).toUInt();

    //////////////////////////////////////////////////////////////
    m_rotate_delay = alfa.value(INI_ALFA_OTHER_ROTATE_DELAY, 0).toUInt();

    //////////////////////////////////////////////////////////////
    m_ejectorfront = alfa.value(INI_ALFA_IMM_EJECTORFRONT, false).toBool();
    m_ejectorfrontdelay = alfa.value(INI_ALFA_IMM_EJECTORFRONTDELAY, 0).toUInt();
    m_ejectorback = alfa.value(INI_ALFA_IMM_EJECTORBACK, false).toBool();
    m_ejectorbackdelay = alfa.value(INI_ALFA_IMM_EJECTORBACKDELAY, 0).toUInt();

    m_c1front = alfa.value(INI_ALFA_IMM_C1FRONT, false).toBool();
    m_c1frontdelay = alfa.value(INI_ALFA_IMM_C1FRONTDELAY, 0).toUInt();
    m_c1back = alfa.value(INI_ALFA_IMM_C1BACK, false).toBool();
    m_c1backdelay = alfa.value(INI_ALFA_IMM_C1BACKDELAY, 0).toUInt();

    m_c2front = alfa.value(INI_ALFA_IMM_C2FRONT, false).toBool();
    m_c2frontdelay = alfa.value(INI_ALFA_IMM_C2FRONTDELAY, 0).toUInt();
    m_c2back = alfa.value(INI_ALFA_IMM_C2BACK, false).toBool();
    m_c2backdelay = alfa.value(INI_ALFA_IMM_C2BACKDELAY, 0).toUInt();

    m_mop_timeout = alfa.value(INI_ALFA_IMM_MOP_TIMEOUT, 0).toUInt();
    m_emc_delay = alfa.value(INI_ALFA_IMM_EMC_DELAY, 0).toUInt();

    //////////////////////////////////////////////////////////////
    m_conveyor = alfa.value(INI_ALFA_CONVEYOR_USE, false).toBool();
    m_conveyorout = alfa.value(INI_ALFA_CONVEYOR_OUT, EM1_VAR_Y15).toUInt();
    m_conveyordelay = alfa.value(INI_ALFA_CONVEYOR_DELAY, 100).toUInt();
    m_conveyorinterval = alfa.value(INI_ALFA_CONVEYOR_INTERVAL, 0).toUInt();

    //////////////////////////////////////////////////////////////
    m_z_pro_release_pos = alfa.value(INI_ALFA_POS_ZPRO_RELEASE, 0).toInt();
    m_z_run_release_pos = alfa.value(INI_ALFA_POS_ZRUN_RELEASE, 0).toInt();
    m_z_catch_pos = alfa.value(INI_ALFA_POS_ZPRO_CATCH, 100000).toInt();

    m_x_pro_down_pos = alfa.value(INI_ALFA_POS_XPRO_DOWN, 0).toInt();
    m_b_run_down_pos = alfa.value(INI_ALFA_POS_BRUN_DOWN, 0).toInt();

    m_x_pro_up_pos = alfa.value(INI_ALFA_POS_XPRO_UP, 0).toInt();
    m_b_run_up_pos = alfa.value(INI_ALFA_POS_BRUN_UP, 0).toInt();

    m_x_pro_catch_pos = alfa.value(INI_ALFA_POS_XPRO_CATCH, 10000).toInt();
    m_b_run_catch_pos = alfa.value(INI_ALFA_POS_BRUN_CATCH, 10000).toInt();

    m_x_pro_release_pos = alfa.value(INI_ALFA_POS_XPRO_RELEASE, 0).toInt();
    m_b_run_release_pos = alfa.value(INI_ALFA_POS_BRUN_RELEASE, 0).toInt();

    m_y_pro_catch_pos = alfa.value(INI_ALFA_POS_YPRO_CATCH, 20000).toInt();
    m_a_run_catch_pos = alfa.value(INI_ALFA_POS_ARUN_CATCH, 20000).toInt();

    m_y_pro_release_pos = alfa.value(INI_ALFA_POS_YPRO_RELEASE, 20000).toInt();
    m_a_run_release_pos = alfa.value(INI_ALFA_POS_ARUN_RELEASE, 20000).toInt();

    m_y_pro_wait_pos = alfa.value(INI_ALFA_POS_YPRO_WAIT, 0).toInt();
    m_a_run_wait_pos = alfa.value(INI_ALFA_POS_ARUN_WAIT, 0).toInt();

    //////////////////////////////////////////////////////////////
    m_x_speed = alfa.value(INI_ALFA_SPEED_X, 10).toInt();
    m_y_speed = alfa.value(INI_ALFA_SPEED_Y, 10).toInt();
    m_y_speed_outmold = alfa.value(INI_ALFA_SPEED_Y_OUT, 10).toInt();
    m_z_speed = alfa.value(INI_ALFA_SPEED_Z, 10).toInt();
    m_a_speed = alfa.value(INI_ALFA_SPEED_A, 10).toInt();
    m_a_speed_outmold = alfa.value(INI_ALFA_SPEED_A_OUT, 10).toInt();
    m_b_speed = alfa.value(INI_ALFA_SPEED_B, 10).toInt();
    m_c_speed = alfa.value(INI_ALFA_SPEED_C, 10).toInt();

    //////////////////////////////////////////////////////////////
    m_matrix_speed = alfa.value(INI_ALFA_MATRIX_SPEED, 10).toInt();
    m_matrix_dspeed = alfa.value(INI_ALFA_MATRIX_DSPEED, 1).toInt();
    m_matrix_dlen = alfa.value(INI_ALFA_MATRIX_DLEN, 1000).toInt();
    m_matrix_isrunner = alfa.value(INI_ALFA_MATRIX_ISRUNNER, false).toBool();
    m_matrix_trvrot = alfa.value(INI_ALFA_MATRIX_TRVROT, false).toBool();
    m_matrix_dec_axes = alfa.value(INI_ALFA_MATRIX_DEC, false).toBool();
    m_matrix_horizontal = alfa.value(INI_ALFA_MATRIX_HORIZONTAL, false).toBool();
    m_matrix_dec_axes_prior = alfa.value(INI_ALFA_MATRIX_DEC_PRIOR, false).toInt();
    m_matrix_rel_posx = alfa.value(INI_ALFA_MATRIX_REL_X, false).toBool();
    m_matrix_rel_posy = alfa.value(INI_ALFA_MATRIX_REL_Y, false).toBool();
    m_matrix_rel_posz = alfa.value(INI_ALFA_MATRIX_REL_Z, false).toBool();
    m_matrix_xs = alfa.value(INI_ALFA_MATRIX_XS, 1).toInt();
    m_matrix_x_interval = alfa.value(INI_ALFA_MATRIX_XINTERVAL, 0).toInt();
    m_matrix_ys = alfa.value(INI_ALFA_MATRIX_YS, 1).toInt();
    m_matrix_y_interval = alfa.value(INI_ALFA_MATRIX_YINTERVAL, 0).toInt();
    m_matrix_zs = alfa.value(INI_ALFA_MATRIX_ZS, 1).toInt();
    m_matrix_z_interval = alfa.value(INI_ALFA_MATRIX_ZINTERVAL, 0).toInt();
    m_matrix_posx = alfa.value(INI_ALFA_MATRIX_POS_X, 0).toInt();
    m_matrix_posy = alfa.value(INI_ALFA_MATRIX_POS_Y, 0).toInt();
    m_matrix_posz = alfa.value(INI_ALFA_MATRIX_POS_Z, 0).toInt();

    //////////////////////////////////////////////////////////////
    m_rotate_trvin = alfa.value(INI_ALFA_ROTATE_TRVIN, 1).toInt();
    m_rotate_trvout = alfa.value(INI_ALFA_ROTATE_TRVOUT, 1).toInt();
    m_rotate_release = alfa.value(INI_ALFA_ROTATE_RELEASE, 1).toInt();
    m_rotate_fetch = alfa.value(INI_ALFA_ROTATE_FETCH, 0).toInt();

    m_pro_release_use = alfa.value(INI_ALFA_POS_PRO_RELEASE, 0).toInt();

    m_filename = filename;
    return true;
}

bool AlfaModel::InsertPos(TeachTableModel& model, qint8 axis, qint32 pos, qint8 speed, qint16 delay)
{
    if (CMBProtocol::GetFunctions(SUB_FUN2_EXT_POS))
    {
        CodeExtPos *pitem = new CodeExtPos(NULL);
		pitem->SetParas(axis, speed, pos, 0,delay);
        model.InsertCode(pitem);
        return true;
    }
    else
    {
    CodePos *pitem = new CodePos(NULL);
        pitem->SetParas(axis, speed, pos, delay);
    model.InsertCode(pitem);
    return true;
    }
}

bool AlfaModel::InsertParm(TeachTableModel& model, int act, int delay)
{
    CodePArm *pitem = new CodePArm(NULL);
    pitem->SetParas(act, delay);
    model.InsertCode(pitem);
    return true;
}

bool AlfaModel::InsertExt(TeachTableModel& model, int out, int type, int interval, int delay)
{
    CodeExtOut *pitem = new CodeExtOut(NULL);
    pitem->SetParas(out, type, interval, delay);
    model.InsertCode(pitem);
    return true;
}

bool AlfaModel::InsertIMM(TeachTableModel& model, int act, int delay)
{
    CodeImm *pitem = new CodeImm(NULL);
    pitem->SetParas(act, delay);
    model.InsertCode(pitem);
    return true;
}

bool AlfaModel::InsertVacuum(TeachTableModel& model, bool ison, qint16 vacbmp, qint16 vacchk, qint16 delay)
{
    CodeVacuum *pitem = new CodeVacuum(NULL);
    pitem->SetParas(ison, delay, vacbmp, vacchk);
    model.InsertCode(pitem);
    return true;
}

bool AlfaModel::InsertPEnd(TeachTableModel& model)
{
    CodeEnd *pitem = new CodeEnd(NULL);
    model.InsertCode(pitem);
    return true;
}

bool AlfaModel::InsertMatrix(TeachTableModel& model)
{
    bool rel[] = {m_matrix_rel_posx, m_matrix_rel_posy, m_matrix_rel_posz};
    quint16 num[] = {m_matrix_xs, m_matrix_ys, m_matrix_zs};
    qint16 interval[] = {m_matrix_x_interval, m_matrix_y_interval, m_matrix_z_interval};
    qint32 pos[] = {m_matrix_posx, m_matrix_posy, m_matrix_posz};

    CodeLoopMatrix *pitem = new CodeLoopMatrix(NULL);
    pitem->SetParas(m_matrix_speed, m_matrix_dspeed, m_matrix_dlen, m_matrix_dec_axes_prior, m_matrix_isrunner, m_matrix_trvrot, m_matrix_dec_axes, m_matrix_horizontal, rel, num, interval, pos,0,0,0);
    model.InsertCode(pitem);
    return true;
}

int AlfaModel::CreateRunPgm(void)//生成xpgm文件
{
    bool needcombine = false;
    int act = 0;

    if ((m_pro_mode==PRO_MODE_NONE)&&(m_run_mode==RUN_MODE_NONE)) return -1;
    QString runpgmname = GetRunPgmName();
    if (runpgmname.isEmpty()) return -2;
    //头痛
    TeachTableModel pgmModel(false);

    //传送带控制
    if (m_conveyor)
    {
        if (InsertExt(pgmModel, m_conveyorout, 2, m_conveyorinterval, m_conveyordelay)==false) return -16;
    }
//前期到待机位置
    //--上下轴到上位
    needcombine = false;
    if (m_pro_mode!=PRO_MODE_NONE)
    {
        if (InsertPos(pgmModel, AXES_IDX_Y, 0, m_y_speed_outmold)==false) return -10;
        needcombine = true;
    }
    if (m_run_mode!=RUN_MODE_NONE)
    {
        if (needcombine) pgmModel.SetFlag(FLAG_COMBINE);    //上条指令打上组合标志
        if (InsertPos(pgmModel, AXES_IDX_A, 0, m_a_speed_outmold)==false) return -10;
    }
    //--倒角到待机位置
    if (m_pro_mode!=PRO_MODE_NONE)
    {
//        act = PRO_ACT_VERTIACL;
//        if (CMBProtocol::GetRotateAtOrigin())   act = PRO_ACT_HOZIONTAL;
//#if (FACTORY == FA_SHINI)
        act = m_rotate_trvin;
//#endif
        if (InsertParm(pgmModel, act, m_rotate_delay)==false) return -11;
    }

//横入到模内&
    //--横入到模内&引拔轴同时调整&倒角调整
    if (InsertPos(pgmModel, AXES_IDX_Z, m_z_catch_pos, m_z_speed)==false) return -10;
    needcombine = true;
    if (m_pro_mode!=PRO_MODE_NONE)
    {
        if (needcombine) pgmModel.SetFlag(FLAG_COMBINE);    //上条指令打上组合标志
        if (InsertPos(pgmModel, AXES_IDX_X, m_x_pro_down_pos, m_x_speed)==false) return -10;
    }
    if (m_run_mode!=RUN_MODE_NONE)
    {
        if (needcombine) pgmModel.SetFlag(FLAG_COMBINE);    //上条指令打上组合标志
        if (InsertPos(pgmModel, AXES_IDX_B, m_b_run_down_pos, m_b_speed)==false) return -10;
    }

    //--倒角到待机位置
    if ((m_pro_mode!=PRO_MODE_NONE)&&(CMBProtocol::GetRotateAtOrigin()))
    {
        if (InsertParm(pgmModel, PRO_ACT_VERTIACL, m_rotate_delay)==false) return -11;
    }

    needcombine = false;
    if (m_pro_mode!=PRO_MODE_NONE)
    {
        needcombine = true;
        if (InsertPos(pgmModel, AXES_IDX_Y, m_y_pro_wait_pos, m_y_speed)==false) return -10;
    }
    if (m_run_mode!=RUN_MODE_NONE)
    {
        if (needcombine) pgmModel.SetFlag(FLAG_COMBINE);    //上条指令打上组合标志
        if (InsertPos(pgmModel, AXES_IDX_A, m_a_run_wait_pos, m_a_speed)==false) return -10;
    }
//#if (FACTORY == FA_SHINI)
    if (m_pro_mode!=PRO_MODE_NONE)
    {
        act = m_rotate_fetch;
        if (InsertParm(pgmModel, act, m_rotate_delay)==false) return -11;
    }
//#endif

//等待开模&模内动作下行
    //--抽芯退1控制
    if (m_c1back)
    {
        if (InsertIMM(pgmModel, IMMOUT_C1P2_OFF, 0)==false) return -12;
    }
    if (m_c1front)
    {
        if (InsertIMM(pgmModel, IMMOUT_C1P1, m_c1frontdelay)==false) return -12;
    }
    //--抽芯退2控制
    if (m_c2back)
    {
        if (InsertIMM(pgmModel, IMMOUT_C2P2_OFF, 0)==false) return -12;
    }
    if (m_c2front)
    {
        if (InsertIMM(pgmModel, IMMOUT_C2P1, m_c2frontdelay)==false) return -12;
    }
    //--等待开模
    if (InsertIMM(pgmModel, IMMOUT_EMO, m_mop_timeout)==false) return -12;

    //--手臂下行
    needcombine = false;
    if (m_pro_mode!=PRO_MODE_NONE)
    {
        if (InsertPos(pgmModel, AXES_IDX_Y, m_y_pro_catch_pos, m_y_speed)==false) return -10;
        needcombine = true;
    }
    if (m_run_mode!=RUN_MODE_NONE)
    {
        if (needcombine) pgmModel.SetFlag(FLAG_COMBINE);    //上条指令打上组合标志
        if (InsertPos(pgmModel, AXES_IDX_A, m_a_run_catch_pos, m_a_speed)==false) return -10;
    }

//模内引拔&顶针&冶具
    //--顶针进控制
    if (m_ejectorback)
    {
        if (InsertIMM(pgmModel, IMMOUT_EEB_OFF, 0)==false) return -12;
    }
    if (m_ejectorfront)
    {
        if (InsertIMM(pgmModel, IMMOUT_EEF, m_ejectorfrontdelay)==false) return -12;
    }

    //--引拔轴同时到取物点
    needcombine = false;
    if (m_pro_mode!=PRO_MODE_NONE)
    {
        if (InsertPos(pgmModel, AXES_IDX_X, m_x_pro_catch_pos, m_x_speed)==false) return -10;
        needcombine = true;
    }
    if (m_run_mode!=RUN_MODE_NONE)
    {
        if (needcombine) pgmModel.SetFlag(FLAG_COMBINE);    //上条指令打上组合标志
        if (InsertPos(pgmModel, AXES_IDX_B, m_b_run_catch_pos, m_b_speed)==false) return -10;
        needcombine = false;
    }

    //--冶具控制(组合)
    if (m_pro_mode!=PRO_MODE_NONE)
    {
        if (needcombine) pgmModel.SetFlag(FLAG_COMBINE);    //上条指令打上组合标志
        if (InsertVacuum(pgmModel, true, m_pro_vacbmp, m_pro_vacchk, m_pro_vacdelay)==false) return -13;
        needcombine = true;
    }

    if (m_run_mode!=RUN_MODE_NONE)
    {
        if (needcombine) pgmModel.SetFlag(FLAG_COMBINE);    //上条指令打上组合标志
        if (InsertVacuum(pgmModel, true, m_run_vacbmp, m_run_vacchk, m_run_vacdelay)==false) return -13;
    }

//引拔退&上行&允许关模&倒角调整
    //--引拔轴同时回
    needcombine = false;
    if (m_pro_mode!=PRO_MODE_NONE)
    {
        if (InsertPos(pgmModel, AXES_IDX_X, m_x_pro_up_pos, m_x_speed)==false) return -10;
        needcombine = true;
    }
    if (m_run_mode!=RUN_MODE_NONE)
    {
        if (needcombine) pgmModel.SetFlag(FLAG_COMBINE);    //上条指令打上组合标志
        if (InsertPos(pgmModel, AXES_IDX_B, m_b_run_up_pos, m_b_speed)==false) return -10;
    }

    //--顶针退控制
    if (m_ejectorfront)
    {
        if (InsertIMM(pgmModel, IMMOUT_EEF_OFF, 0)==false) return -12;
    }
    if (m_ejectorback)
    {
        if (InsertIMM(pgmModel, IMMOUT_EEB, m_ejectorbackdelay)==false) return -12;
    }
    //--抽芯进1控制
    if (m_c1front)
    {
        if (InsertIMM(pgmModel, IMMOUT_C1P1_OFF, 0)==false) return -12;
    }
    if (m_c1back)
    {
        if (InsertIMM(pgmModel, IMMOUT_C1P2, m_c1backdelay)==false) return -12;
    }
    //--抽芯进2控制
    if (m_c2front)
    {
        if (InsertIMM(pgmModel, IMMOUT_C2P1_OFF, 0)==false) return -12;
    }
    if (m_c2back)
    {
        if (InsertIMM(pgmModel, IMMOUT_C2P2, m_c2backdelay)==false) return -12;
    }

    //--上下轴同时上
    needcombine = false;
    if (m_pro_mode!=PRO_MODE_NONE)
    {
        if (InsertPos(pgmModel, AXES_IDX_Y, 0, m_y_speed)==false) return -10;
        needcombine = true;
    }
    if (m_run_mode!=RUN_MODE_NONE)
    {
        if (needcombine) pgmModel.SetFlag(FLAG_COMBINE);    //上条指令打上组合标志
        if (InsertPos(pgmModel, AXES_IDX_A, 0, m_a_speed)==false) return -10;
    }

    //--允许关模(组合)
    if (InsertIMM(pgmModel, IMMOUT_EMC, m_emc_delay)==false) return -12;
    needcombine = true;

//#if (FACTORY == FA_SHINI)
    if (m_pro_mode!=PRO_MODE_NONE)
    {
        act = m_rotate_trvout;
        if (InsertParm(pgmModel, act, m_rotate_delay)==false) return -11;
    }
/*#else
    //--倒角到待机位置
    if ((m_pro_mode!=PRO_MODE_NONE)&&(CMBProtocol::GetRotateAtOrigin()))
    {
        if (needcombine) pgmModel.SetFlag(FLAG_COMBINE);    //上条指令打上组合标志
        if (InsertParm(pgmModel, PRO_ACT_HOZIONTAL, m_rotate_delay)==false) return -11;
    }
#endif*/

    //if (置料点>置物点)
    if ((m_z_run_release_pos > m_z_pro_release_pos)||(m_pro_mode==PRO_MODE_L_MATRIX))
    {
//横出到置料点&下行&冶具开&上行
        if (m_run_mode!=RUN_MODE_NONE)
        {
            //--横出到置料点
            if (InsertPos(pgmModel, AXES_IDX_B, m_b_run_release_pos, m_b_speed)==false) return -10;
            pgmModel.SetFlag(FLAG_COMBINE);    //上条指令打上组合标志
            if (InsertPos(pgmModel, AXES_IDX_Z, m_z_run_release_pos, m_z_speed)==false) return -10;
#if FACTORY == FA_SHINI
            pgmModel.SetFlag(FLAG_COMBINE);    //上条指令打上组合标志
            if (InsertPos(pgmModel, AXES_IDX_X, m_x_pro_release_pos, m_x_speed)==false) return -10;
#endif
            //--副臂下行
            if (InsertPos(pgmModel, AXES_IDX_A, m_a_run_release_pos, m_a_speed_outmold)==false) return -10;

            //--冶具控制
            if (InsertVacuum(pgmModel, false, m_run_vacbmp, m_run_vacchk, m_run_vacdelay)==false) return -13;

            //--副臂上行
            if (InsertPos(pgmModel, AXES_IDX_A, 0, m_a_speed_outmold)==false) return -10;
        }
        else
        ////主臂置物点////////////////////////////////////////////////////////////////
        if (m_pro_release_use)
        {
            if (InsertPos(pgmModel, AXES_IDX_Z, m_z_run_release_pos, m_z_speed)==false) return -10;
            //--冶具控制
            if (InsertVacuum(pgmModel, false, m_pro_vacbmp, m_pro_vacchk, m_pro_vacdelay)==false) return -13;
        }
        ////////////////////////////////////////////////////////////////////////////

//横出到置物点&下行&冶具开&上行
        if (m_pro_mode!=PRO_MODE_NONE)
        {
            if (m_pro_mode==PRO_MODE_L_MATRIX)
            {
                //矩阵置物
                if (InsertMatrix(pgmModel)==false) return -14;
            }
            else
            {
                //--横出到置物点
                if (InsertPos(pgmModel, AXES_IDX_X, m_x_pro_release_pos, m_x_speed)==false) return -10;
                pgmModel.SetFlag(FLAG_COMBINE);    //上条指令打上组合标志
                if (InsertPos(pgmModel, AXES_IDX_Z, m_z_pro_release_pos, m_z_speed)==false) return -10;

//#if (FACTORY == FA_SHINI)
    act = m_rotate_release;
    if (InsertParm(pgmModel, act, m_rotate_delay)==false) return -11;
//#endif
                //--主臂下行
                if (InsertPos(pgmModel, AXES_IDX_Y, m_y_pro_release_pos, m_y_speed_outmold)==false) return -10;
            }
            //--冶具控制
            if (InsertVacuum(pgmModel, false, m_pro_vacbmp, m_pro_vacchk, m_pro_vacdelay)==false) return -13;

            //--主臂上行
            if (InsertPos(pgmModel, AXES_IDX_Y, 0, m_y_speed_outmold)==false) return -10;
        }
    }
    else
    if (m_z_run_release_pos < m_z_pro_release_pos)
    {
//横出到置物点&下行&冶具关&上行
        if (m_pro_mode!=PRO_MODE_NONE)
        {
            if (m_pro_mode==PRO_MODE_L_MATRIX)
            {
                //矩阵置物
                if (InsertMatrix(pgmModel)==false) return -14;
            }
            else
            {
                //--横出到置物点
                if (InsertPos(pgmModel, AXES_IDX_X, m_x_pro_release_pos, m_x_speed)==false) return -10;
                pgmModel.SetFlag(FLAG_COMBINE);    //上条指令打上组合标志
                if (InsertPos(pgmModel, AXES_IDX_Z, m_z_pro_release_pos, m_z_speed)==false) return -10;

//#if (FACTORY == FA_SHINI)
    act = m_rotate_release;
    if (InsertParm(pgmModel, act, m_rotate_delay)==false) return -11;
//#endif
                //--主臂下行
                if (InsertPos(pgmModel, AXES_IDX_Y, m_y_pro_release_pos, m_y_speed_outmold)==false) return -10;
            }
            //--冶具控制
            if (InsertVacuum(pgmModel, false, m_pro_vacbmp, m_pro_vacchk, m_pro_vacdelay)==false) return -13;

            //--主臂上行
            if (InsertPos(pgmModel, AXES_IDX_Y, 0, m_y_speed_outmold)==false) return -10;
        }
//横出到置料点&下行&冶具关&上行
        if (m_run_mode!=RUN_MODE_NONE)
        {
            //--横出到置料点
            if (InsertPos(pgmModel, AXES_IDX_B, m_b_run_release_pos, m_b_speed)==false) return -10;
            pgmModel.SetFlag(FLAG_COMBINE);    //上条指令打上组合标志
            if (InsertPos(pgmModel, AXES_IDX_Z, m_z_run_release_pos, m_z_speed)==false) return -10;

            //--副臂下行
            if (InsertPos(pgmModel, AXES_IDX_A, m_a_run_release_pos, m_a_speed_outmold)==false) return -10;

            //--冶具控制
            if (InsertVacuum(pgmModel, false, m_run_vacbmp, m_run_vacchk, m_run_vacdelay)==false) return -13;

            //--副臂上行
            if (InsertPos(pgmModel, AXES_IDX_A, 0, m_a_speed_outmold)==false) return -10;
        }
        else
        ////主臂置物点////////////////////////////////////////////////////////////////
        if (m_pro_release_use)
        {
            if (InsertPos(pgmModel, AXES_IDX_Z, m_z_run_release_pos, m_z_speed)==false) return -10;
            //--冶具控制
            if (InsertVacuum(pgmModel, false, m_pro_vacbmp, m_pro_vacchk, m_pro_vacdelay)==false) return -13;
        }
        ////////////////////////////////////////////////////////////////////////////
    }
    else//m_z_run_release_pos == z_pro_release_pos)
    {
//横出到置物/置料点&下行&冶具关&上行
        //--横出到置物点
        if (InsertPos(pgmModel, AXES_IDX_X, m_x_pro_release_pos, m_x_speed)==false) return -10;
        pgmModel.SetFlag(FLAG_COMBINE);    //上条指令打上组合标志
        if (InsertPos(pgmModel, AXES_IDX_B, m_b_run_release_pos, m_b_speed)==false) return -10;
        pgmModel.SetFlag(FLAG_COMBINE);    //上条指令打上组合标志
        if (InsertPos(pgmModel, AXES_IDX_Z, m_z_pro_release_pos, m_z_speed)==false) return -10;

        needcombine = false;
        if (m_pro_mode!=PRO_MODE_NONE)
        {
//#if (FACTORY == FA_SHINI)
    act = m_rotate_release;
    if (InsertParm(pgmModel, act, m_rotate_delay)==false) return -11;
//#endif
            //--主臂下行
            if (InsertPos(pgmModel, AXES_IDX_Y, m_y_pro_release_pos, m_y_speed_outmold)==false) return -10;
            needcombine = true;
        }
        if (m_run_mode!=RUN_MODE_NONE)
        {
            //--副臂下行
            if (needcombine) pgmModel.SetFlag(FLAG_COMBINE);    //上条指令打上组合标志
            if (InsertPos(pgmModel, AXES_IDX_A, m_a_run_release_pos, m_a_speed_outmold)==false) return -10;
        }

        needcombine = false;
        if (m_pro_mode!=PRO_MODE_NONE)
        {
            //--冶具控制
            if (InsertVacuum(pgmModel, false, m_pro_vacbmp, m_pro_vacchk, m_pro_vacdelay)==false) return -13;
            needcombine = true;
        }
        if ((m_run_mode!=RUN_MODE_NONE)||m_pro_release_use)
        {
            //--冶具控制
            if (needcombine) pgmModel.SetFlag(FLAG_COMBINE);    //上条指令打上组合标志
            if (InsertVacuum(pgmModel, false, m_run_vacbmp, m_run_vacchk, m_run_vacdelay)==false) return -13;
        }

        needcombine = false;
        if (m_pro_mode!=PRO_MODE_NONE)
        {
            //--主臂上行
            if (InsertPos(pgmModel, AXES_IDX_Y, 0, m_y_speed_outmold)==false) return -10;
            needcombine = true;
        }
        if (m_run_mode!=RUN_MODE_NONE)
        {
            //--副臂上行
            if (needcombine) pgmModel.SetFlag(FLAG_COMBINE);    //上条指令打上组合标志
            if (InsertPos(pgmModel, AXES_IDX_A, 0, m_a_speed_outmold)==false) return -10;
        }
    }

//进程1程序结束
    if (InsertPEnd(pgmModel)==false) return -15;

//进程2程序结束
    pgmModel.SetCurProcess(1);
    if (InsertPEnd(pgmModel)==false) return -15;

//进程3程序结束
    pgmModel.SetCurProcess(2);
    if (InsertPEnd(pgmModel)==false) return -15;

    if (pgmModel.SaveProgram(runpgmname)==false)
        return -3;
    return 0;
}
