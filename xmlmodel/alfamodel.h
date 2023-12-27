#ifndef ALFAMODEL_H
#define ALFAMODEL_H

#include <QObject>
#include "teachtablemodel.h"

/////////////////////////////////////////////////////////////
#define MAX_AXIS_NUMBER     6

/////////////////////////////////////////////////////////////
#define PRO_MODE_NONE       0
#define PRO_MODE_L_POINT    1
#define PRO_MODE_L_MATRIX   2

#define RUN_MODE_NONE       0
#define RUN_MODE_L          1

/////////////////////////////////////////////////////////////
class AlfaModel : public QObject
{
    Q_OBJECT
public:
    explicit AlfaModel(QObject *parent = 0);

    //////////////////////////////////////////////////////////////
    // 文件接口
    //////////////////////////////////////////////////////////////
    bool LoadProgram(const QString &filename);
    bool SaveProgram(void);		// 保存程序到文件
    bool SaveAs(const QString &filename);		// 保存程序到文件
    bool NewProgram(const QString &filename);                          // 建立一个新程序，即清除所有列表中的指令,加入一条END语句
    int CreateRunPgm(void);
    QString GetRunPgmName(void);

    //////////////////////////////////////////////////////////////
    // 参数接口
    //////////////////////////////////////////////////////////////
    quint8 GetProMode(void){return m_pro_mode;}
    quint8 GetRunMode(void){return m_run_mode;}
//    quint8 GetProReleaseMode(void){return m_pro_release_mode;}

    //////////////////////////////////////////////////////////////
    quint16 GetProVacBmp(void){return m_pro_vacbmp;}
    quint16 GetProVacChk(void){return m_pro_vacchk;}
    quint16 GetProVacDelay(void){return m_pro_vacdelay;}

    quint16 GetRunVacBmp(void){return m_run_vacbmp;}
    quint16 GetRunVacChk(void){return m_run_vacchk;}
    quint16 GetRunVacDelay(void){return m_run_vacdelay;}

    //////////////////////////////////////////////////////////////
    quint16 GetRotateDelay(void){return m_rotate_delay;}

    //////////////////////////////////////////////////////////////
    bool UseEjectorFront(void){return m_ejectorfront;}
    quint16 GetEjectorFrontDelay(void){return m_ejectorfrontdelay;}
    bool UseEjectorBack(void){return m_ejectorback;}
    quint16 GetEjectorBackDelay(void){return m_ejectorbackdelay;}

    bool UseC1Front(void){return m_c1front;}
    quint16 GetC1FrontDelay(void){return m_c1frontdelay;}
    bool UseC1Back(void){return m_c1back;}
    quint16 GetC1BackDelay(void){return m_c1backdelay;}

    bool UseC2Front(void){return m_c2front;}
    quint16 GetC2FrontDelay(void){return m_c2frontdelay;}
    bool UseC2Back(void){return m_c2back;}
    quint16 GetC2BackDelay(void){return m_c2backdelay;}

    quint16 GetMOPTimeout(void){return m_mop_timeout;}
    quint16 GetEMCDelay(void){return m_emc_delay;}

    //////////////////////////////////////////////////////////////
    bool UseConveyor(void){return m_conveyor;}
    quint16 GetConveyorOut(void){return m_conveyorout;}
    quint16 GetConveyorDelay(void){return m_conveyordelay;}
    quint16 GetConveyorInterval(void){return m_conveyorinterval;}

    //////////////////////////////////////////////////////////////
    qint32 GetZProReleasePos(void){return m_z_pro_release_pos;}     //横行轴置物点
    qint32 GetZRunReleasePos(void){return m_z_run_release_pos;}     //横行轴料物点
    qint32 GetZCatchPos(void){return m_z_catch_pos;}           //横行轴模内取物点

    qint32 GetXProDownPos(void){return m_x_pro_down_pos;}        //模内主臂引拔轴下行点
    qint32 GetBRunDownPos(void){return m_b_run_down_pos;}        //模内副臂引拔轴下行点

    qint32 GetXProUpPos(void){return m_x_pro_up_pos;}        //模内主臂引拔轴上行点
    qint32 GetBRunUpPos(void){return m_b_run_up_pos;}        //模内副臂引拔轴上行点

    qint32 GetXProCatchPos(void){return m_x_pro_catch_pos;}       //模内主臂引拔轴取物点
    qint32 GetBRunCatchPos(void){return m_b_run_catch_pos;}       //模内副臂引拔轴取物点

    qint32 GetXProReleasePos(void){return m_x_pro_release_pos;}       //模外主臂引拔轴置物点
    qint32 GetBRunReleasePos(void){return m_b_run_release_pos;}        //模外副臂引拔轴置物点

    qint32 GetYProCatchPos(void){return m_y_pro_catch_pos;}       //模内主臂上下轴取物点
    qint32 GetARunCatchPos(void){return m_a_run_catch_pos;}       //模内副臂上下轴取物点

    qint32 GetYProReleasePos(void){return m_y_pro_release_pos;}     //模外主臂上下轴置物点
    qint32 GetARunReleasePos(void){return m_a_run_release_pos;}     //模外副臂上下轴置物点

    qint32 GetYProWaitPos(void){return m_y_pro_wait_pos;}     //模内主臂上下轴等待开模点
    qint32 GetARunWaitPos(void){return m_a_run_wait_pos;}     //模内副臂上下轴等待开模点

    //////////////////////////////////////////////////////////////
    quint8 GetXSpeed(void){return m_x_speed;}
    quint8 GetYSpeed(void){return m_y_speed;}
    quint8 GetYSpeedOut(void){return m_y_speed_outmold;}
    quint8 GetZSpeed(void){return m_z_speed;}
    quint8 GetASpeed(void){return m_a_speed;}
    quint8 GetASpeedOut(void){return m_a_speed_outmold;}
    quint8 GetBSpeed(void){return m_b_speed;}
    quint8 GetCSpeed(void){return m_c_speed;}

    //////////////////////////////////////////////////////////////
    quint8 GetMatrixSpeed(void){return m_matrix_speed;}          //运行速度
    quint8 GetMatrixdSpeed(void){return m_matrix_dspeed;}         //减速速度
    quint16 GetMatrixdlen(void){return m_matrix_dlen;}          //减速距离
    bool GetMatrixIsRunner(void){return m_matrix_isrunner;}         //副臂
    bool GetMatrixTrvrot(void){return m_matrix_trvrot;}         //横行自动倒角
    bool GetMatrixDecAxis(void){return m_matrix_dec_axes;}         //减速轴	0:表示上下轴 1:表示引拨轴
    bool GetMatrixHor(void){return m_matrix_horizontal;}       //倒角方式	0:表示回正 1:表示侧姿
    quint8 GetMatrixDecPrior(void){return m_matrix_dec_axes_prior;} //减速轴优先放 1:表示减速轴优先 0:表示减速轴最后
    bool GetMatrixRelx(void){return m_matrix_rel_posx;}         //引拨轴第一点位置是相对位置
    bool GetMatrixRely(void){return m_matrix_rel_posy;}         //上下轴第一点位置是相对位置
    bool GetMatrixRelz(void){return m_matrix_rel_posz;}         //横行轴第一点位置是相对位置

    quint16 GetMatrixXS(void){return m_matrix_xs;}			//引拨轴数量
    qint16 GetMatrixXInterval(void){return m_matrix_x_interval;}	//引拨轴间隔

    quint16 GetMatrixYS(void){return m_matrix_ys;}			//上下轴数量
    qint16 GetMatrixYInterval(void){return m_matrix_y_interval;}	//上下轴间隔

    quint16 GetMatrixZS(void){return m_matrix_zs;}			//横行轴数量
    qint16 GetMatrixZInterval(void){return m_matrix_z_interval;} 	//横行轴间隔

    qint32 GetMatrixPosx(void){return m_matrix_posx;}			//引拨轴第一点位置
    qint32 GetMatrixPosy(void){return m_matrix_posy;}			//上下轴第一点位置
    qint32 GetMatrixPosz(void){return m_matrix_posz;}			//横行轴第一点位置

    //////////////////////////////////////////////////////////////
    quint8 GetTrvInRotate(void) {return m_rotate_trvin;}          // 横入横出置物都默认水平，取物默认倒直
    quint8 GetTrvOutRotate(void) {return m_rotate_trvout;}
    quint8 GetReleaseRotate(void) {return m_rotate_release;}
    quint8 GetFetchRotate(void) {return m_rotate_fetch;}
    quint8 GetProReleaseUse(void) {return m_pro_release_use;}
    //////////////////////////////////////////////////////////////
    void SetProMode(quint8 mode){m_pro_mode = mode;}
    void SetRunMode(quint8 mode){m_run_mode = mode;}
//    void SetProReleaseMode(quint8 mode){m_pro_release_mode = mode;}

    //////////////////////////////////////////////////////////////
    void SetProVacBmp(quint16 bmp){m_pro_vacbmp = bmp;}
    void SetProVacChk(quint16 chk){m_pro_vacchk = chk;}
    void SetProVacDelay(quint16 delay){m_pro_vacdelay = delay;}

    //////////////////////////////////////////////////////////////
    void SetRunVacBmp(quint16 bmp){m_run_vacbmp = bmp;}
    void SetRunVacChk(quint16 chk){m_run_vacchk = chk;}
    void SetRunVacDelay(quint16 delay){m_run_vacdelay = delay;}

    //////////////////////////////////////////////////////////////
    void SetRotateDelay(quint16 delay){m_rotate_delay = delay;}

    //////////////////////////////////////////////////////////////
    void SetEjectorFront(bool use){m_ejectorfront = use;}
    void setEjectorFrontDelay(quint16 delay){m_ejectorfrontdelay = delay;}
    void SetEjectorBack(bool use){m_ejectorback = use;}
    void setEjectorBackDelay(quint16 delay){m_ejectorbackdelay = delay;}

    void SetC1Front(bool use){m_c1front = use;}
    void setC1FrontDelay(quint16 delay){m_c1frontdelay = delay;}
    void SetC1Back(bool use){m_c1back = use;}
    void setC1BackDelay(quint16 delay){m_c1backdelay = delay;}

    void SetC2Front(bool use){m_c2front = use;}
    void setC2FrontDelay(quint16 delay){m_c2frontdelay = delay;}
    void SetC2Back(bool use){m_c2back = use;}
    void setC2BackDelay(quint16 delay){m_c2backdelay = delay;}

    void SetMOPTimeout(quint16 timeout){m_mop_timeout = timeout;}
    void SetEMCDelay(quint16 delay){m_emc_delay = delay;}

    //////////////////////////////////////////////////////////////
    void SetConveyor(bool use){m_conveyor = use;}
    void SetConveyorOut(quint16 out){m_conveyorout = out;}
    void SetConveyorDelay(quint16 delay){m_conveyordelay = delay;}
    void SetConveyorInterval(quint16 delay){m_conveyorinterval = delay;}

    //////////////////////////////////////////////////////////////
    void SetZProReleasePos(qint32 pos){m_z_pro_release_pos = pos;}     //横行轴置物点
    void SetZRunReleasePos(qint32 pos){m_z_run_release_pos = pos;}     //横行轴料物点
    void SetZCatchPos(qint32 pos){m_z_catch_pos = pos;}           //横行轴模内取物点

    void SetXProDownPos(qint32 pos){m_x_pro_down_pos = pos;}        //模内主臂引拔轴下行点
    void SetBRunDownPos(qint32 pos){m_b_run_down_pos = pos;}        //模内副臂引拔轴下行点

    void SetXProUpPos(qint32 pos){m_x_pro_up_pos = pos;}        //模内主臂引拔轴上行点
    void SetBRunUpPos(qint32 pos){m_b_run_up_pos = pos;}        //模内副臂引拔轴上行点

    void SetXProCatchPos(qint32 pos){m_x_pro_catch_pos = pos;}       //模内主臂引拔轴取物点
    void SetBRunCatchPos(qint32 pos){m_b_run_catch_pos = pos;}       //模内副臂引拔轴取物点

    void SetXProReleasePos(qint32 pos){m_x_pro_release_pos = pos;}       //模外主臂引拔轴置物点
    void SetBRunReleasePos(qint32 pos){m_b_run_release_pos = pos;}       //模外副臂引拔轴置物点

    void SetYProCatchPos(qint32 pos){m_y_pro_catch_pos = pos;}       //模内主臂上下轴取物点
    void SetARunCatchPos(qint32 pos){m_a_run_catch_pos = pos;}       //模内副臂上下轴取物点

    void SetYProReleasePos(qint32 pos){m_y_pro_release_pos = pos;}     //模外主臂上下轴置物点
    void SetARunReleasePos(qint32 pos){m_a_run_release_pos = pos;}     //模外副臂上下轴置物点

    void SetYProWaitPos(qint32 pos){m_y_pro_wait_pos = pos;}     //模内主臂上下轴等待开模点
    void SetARunWaitPos(qint32 pos){m_a_run_wait_pos = pos;}     //模内副臂上下轴等待开模点

    //////////////////////////////////////////////////////////////
    void SetXSpeed(quint8 spd){m_x_speed = spd;}
    void SetYSpeed(quint8 spd){m_y_speed = spd;}
    void SetYSpeedOut(quint8 spd){m_y_speed_outmold = spd;}
    void SetZSpeed(quint8 spd){m_z_speed = spd;}
    void SetASpeed(quint8 spd){m_a_speed = spd;}
    void SetASpeedOut(quint8 spd){m_a_speed_outmold = spd;}
    void SetBSpeed(quint8 spd){m_b_speed = spd;}
    void SetCSpeed(quint8 spd){m_c_speed = spd;}

    //////////////////////////////////////////////////////////////
    void SetMatrixSpeed(quint8 spd){m_matrix_speed = spd;}          //运行速度
    void SetMatrixdSpeed(quint8 spd){m_matrix_dspeed = spd;}         //减速速度
    void SetMatrixdlen(quint16 len){m_matrix_dlen = len;}          //减速距离
    void SetMatrixIsRunner(bool isrun){m_matrix_isrunner = isrun;}         //副臂
    void SetMatrixTrvrot(bool isrot){m_matrix_trvrot = isrot;}         //横行自动倒角
    void SetMatrixDecAxis(bool isdec){m_matrix_dec_axes = isdec;}         //减速轴	0:表示上下轴 1:表示引拨轴
    void SetMatrixHor(bool hor){m_matrix_horizontal = hor;}       //倒角方式	0:表示回正 1:表示侧姿
    void SetMatrixDecPrior(quint8 prior){m_matrix_dec_axes_prior = prior;} //减速轴优先放 1:表示减速轴优先 0:表示减速轴最后
    void SetMatrixRelx(bool rel){m_matrix_rel_posx = rel;}         //引拨轴第一点位置是相对位置
    void SetMatrixRely(bool rel){m_matrix_rel_posy = rel;}         //上下轴第一点位置是相对位置
    void SetMatrixRelz(bool rel){m_matrix_rel_posz = rel;}         //横行轴第一点位置是相对位置

    void SetMatrixXS(quint16 num){m_matrix_xs = num;}			//引拨轴数量
    void SetMatrixXInterval(qint16 interval){m_matrix_x_interval = interval;}	//引拨轴间隔

    void SetMatrixYS(quint16 num){m_matrix_ys = num;}			//上下轴数量
    void SetMatrixYInterval(qint16 interval){m_matrix_y_interval = interval;}	//上下轴间隔

    void SetMatrixZS(quint16 num){m_matrix_zs = num;}			//横行轴数量
    void SetMatrixZInterval(qint16 interval){m_matrix_z_interval = interval;} 	//横行轴间隔

    void SetMatrixPosx(qint32 pos){m_matrix_posx = pos;}			//引拨轴第一点位置
    void SetMatrixPosy(qint32 pos){m_matrix_posy = pos;}			//上下轴第一点位置
    void SetMatrixPosz(qint32 pos){m_matrix_posz = pos;}			//横行轴第一点位置

    void SetTrvInRotate(quint8 isrot){m_rotate_trvin = isrot;}
    void SetTrvOutRotate(quint8 isrot){m_rotate_trvout = isrot;}
    void SetFetchRotate(quint8 isrot){m_rotate_fetch = isrot;}
    void SetReleaseRotate(quint8 isrot){m_rotate_release = isrot;}
    void SetProReleaseUse(quint8 isuse) {m_pro_release_use = isuse;}

signals:
    
public slots:
    
private:
    QString m_filename;
    //模式
    quint8 m_pro_mode;
    quint8 m_run_mode;
//    quint8 m_pro_release_mode;      //主臂置物模式：0表示用横行置物点置物；1表示用矩阵特点置物

    quint16 m_pro_vacbmp;           //主臂冶具映像
    quint16 m_pro_vacchk;           //主臂冶具检测映像
    quint16 m_pro_vacdelay;         //主臂冶具延时

    quint16 m_run_vacbmp;           //副臂冶具映像
    quint16 m_run_vacchk;           //副臂冶具检测映像
    quint16 m_run_vacdelay;         //副臂冶具延时

    //动作延时
    int m_rotate_delay;             //倒角延时

    //传送带控制
    bool m_conveyor;                //传送带控制
    quint16 m_conveyorout;          //传送带输出
    quint16 m_conveyordelay;        //传送带时间
    quint16 m_conveyorinterval;     //传送带间隔

    //塑机控制
    bool m_ejectorfront;                //顶针进控制
    quint16 m_ejectorfrontdelay;        //顶针进延时
    bool m_ejectorback;                 //顶针退控制
    quint16 m_ejectorbackdelay;         //顶针退延时
    bool m_c1front;                     //抽芯1进控制
    quint16 m_c1frontdelay;             //抽芯1进延时
    bool m_c1back;                      //抽芯1退控制
    quint16 m_c1backdelay;              //抽芯1退延时
    bool m_c2front;                     //抽芯2进控制
    quint16 m_c2frontdelay;             //抽芯2进延时
    bool m_c2back;                      //抽芯2退控制
    quint16 m_c2backdelay;              //抽芯2退延时
    quint16 m_mop_timeout;              //开模超时
    quint16 m_emc_delay;                //关模延时

    //各轴运行速度
    quint8 m_x_speed;
    quint8 m_y_speed;
    quint8 m_y_speed_outmold;
    quint8 m_z_speed;
    quint8 m_a_speed;
    quint8 m_a_speed_outmold;
    quint8 m_b_speed;
    quint8 m_c_speed;

    //位置
    qint32 m_z_pro_release_pos;     //横行轴置物点
    qint32 m_z_run_release_pos;     //横行轴料物点
    qint32 m_z_catch_pos;           //横行轴模内取物点

    qint32 m_x_pro_down_pos;        //模内主臂引拔轴下行点
    qint32 m_b_run_down_pos;        //模内副臂引拔轴下行点

    qint32 m_x_pro_up_pos;          //模内主臂引拔轴上行点
    qint32 m_b_run_up_pos;          //模内副臂引拔轴上行点

    qint32 m_x_pro_catch_pos;       //模内主臂引拔轴取物点
    qint32 m_b_run_catch_pos;       //模内副臂引拔轴取物点

    qint32 m_x_pro_release_pos;      //模外主臂引拔轴置物点
    qint32 m_b_run_release_pos;      //模外副臂引拔轴置物点

    qint32 m_y_pro_catch_pos;       //模内主臂上下轴取物点
    qint32 m_a_run_catch_pos;       //模内副臂上下轴取物点

    qint32 m_y_pro_release_pos;     //模外主臂上下轴置物点
    qint32 m_a_run_release_pos;     //模外副臂上下轴置物点

    qint32 m_y_pro_wait_pos;        //模内主臂上下轴等待开模点
    qint32 m_a_run_wait_pos;        //模内副臂上下轴等待开模点

    //矩阵
    quint8 m_matrix_speed;          //运行速度
    quint8 m_matrix_dspeed;         //减速速度
    quint16 m_matrix_dlen;          //减速距离
    bool m_matrix_isrunner;         //副臂
    bool m_matrix_trvrot;
    bool m_matrix_dec_axes;         //垂直基准面
    bool m_matrix_horizontal;       //倒角方式	0:表示回正 1:表示侧姿
    quint8 m_matrix_dec_axes_prior; //定位顺序
    bool m_matrix_rel_posx;         //引拨轴第一点位置是相对位置
    bool m_matrix_rel_posy;         //上下轴第一点位置是相对位置
    bool m_matrix_rel_posz;         //横行轴第一点位置是相对位置

    quint16 m_matrix_xs;			//引拨轴数量
    qint16 m_matrix_x_interval;	//引拨轴间隔

    quint16 m_matrix_ys;			//上下轴数量
    qint16 m_matrix_y_interval;	//上下轴间隔

    quint16 m_matrix_zs;			//横行轴数量
    qint16 m_matrix_z_interval; 	//横行轴间隔

    qint32 m_matrix_posx;			//引拨轴第一点位置
    qint32 m_matrix_posy;			//上下轴第一点位置
    qint32 m_matrix_posz;			//横行轴第一点位置

    quint8 m_rotate_trvin;             // 横入倒角姿态
    quint8 m_rotate_trvout;            // 横出倒角姿态
    quint8 m_rotate_release;           // 置物倒角姿态
    quint8 m_rotate_fetch;             // 取物倒角姿态

    quint8 m_pro_release_use;         // 主臂置物使用

    //指令插入
    bool InsertExt(TeachTableModel& model, int out, int type, int interval, int delay);
    bool InsertIMM(TeachTableModel& model, int act, int delay);
    bool InsertVacuum(TeachTableModel& model, bool ison, qint16 vacbmp, qint16 vacchk, qint16 delay);
    bool InsertMatrix(TeachTableModel& model);
    bool InsertParm(TeachTableModel& model, int act, int delay);
    bool InsertPEnd(TeachTableModel& model);
    bool InsertPos(TeachTableModel& model, qint8 axis, qint32 pos, qint8 speed, qint16 delay = 0);

};

#endif // ALFAMODEL_H
