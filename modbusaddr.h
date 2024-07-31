#include "xconfig.h"

#ifndef __MODBUSADDR_H__
#define __MODBUSADDR_H__

////////////////////////////////////////////////////////////////////////////
//Manual
////////////////////////////////////////////////////////////////////////////
#define MANUAL_CODE1               				0x0000
#define MANUAL_CODEPARA1						0x0001
#define MANUAL_CODE2               				0x0002
#define MANUAL_CODEPARA2						0x0003
#define MANUAL_CODE3               				0x0004
#define MANUAL_CODEPARA3						0x0005
#define MANUAL_CODE4               				0x0006
#define MANUAL_CODEPARA4						0x0007
#define MANUAL_CODE5               				0x0008
#define MANUAL_CODEPARA5						0x0009
#define MANUAL_CODE6               				0x000A
#define MANUAL_CODEPARA6						0x000B
#define MANUAL_CODE7               				0x000C
#define MANUAL_CODEPARA7						0x000D
#define MANUAL_CODE8               				0x000E
#define MANUAL_CODEPARA8						0x000F
#define MANUAL_CODE9               				0x0010
#define MANUAL_CODEPARA9						0x0011
#define MANUAL_CODE10							0x0012
#define MANUAL_CODEPARA10						0x0013
#define MANUAL_CODE11							0x0014
#define MANUAL_CODEPARA11						0x0015
#define MANUAL_CODE12							0x0016
#define MANUAL_CODEPARA12						0x0017
#define MANUAL_CODE13							0x0018
#define MANUAL_CODEPARA13						0x0019
#define MANUAL_CODE14							0x001A
#define MANUAL_CODEPARA14						0x001B
#define MANUAL_CODE15							0x001C
#define MANUAL_CODEPARA15						0x001D
#define MANUAL_CODE16							0x001E
#define MANUAL_CODEPARA16						0x001F
#define MANUAL_CODE17							0x0020
#define MANUAL_CODEPARA17						0x0021
#define MANUAL_CODE18							0x0022
#define MANUAL_CODEPARA18						0x0023
#define MANUAL_CODE19							0x0024
#define MANUAL_CODEPARA19						0x0025
#define MANUAL_CODE20							0x0026
#define MANUAL_CODEPARA20						0x0027
#define COMMAND_PARA11							0x0028
#define COMMAND_PARA10							0x0029
#define COMMAND_PARA9							0x002A
#define COMMAND_PARA8							0x002B
#define COMMAND_PARA7							0x002C
#define COMMAND_PARA6							0x002D
#define COMMAND_PARA5							0x002E
#define COMMAND_PARA4							0x002F
#define COMMAND_PARA3							0x0030
#define COMMAND_PARA2							0x0031
#define COMMAND_PARA1							0x0032
#define COMMAND									0x0033
#define COMMAND_SDO_RDDATA                      0X0034//SDO读取的数据
#define COMMAND_SDO_RDOK                        0X0035//主板SDO读取成功标志

////////////////////////////////////////////////////////////////////////////
//Version
////////////////////////////////////////////////////////////////////////////
#define VERSION_HARD_MAJOR						0x0130
#define VERSION_HARD_MINOR						0x0131
#define VERSION_SOFT_MAJOR						0x0132
#define VERSION_SOFT_MINOR						0x0133
#define VERSION_SOFT_EXTRA						0x0134
#define VERSION_PIRATE							0x0135
#define VERSION_SUB_FUN							0x0136
#define VERSION_SOFT_EXTRA_NEW                  0x0137
#define VERSION_M0SOFT_MAJOR                    0x0138
#define VERSION_M0SOFT_MINOR                    0x0139
#define SERVO_DEV_NOT_EXIST						0x013A
#define VERSION_SUB_FUN2						0x013B
#define VERSION_SUB_FUN3						0x013C

#define SYSTEM_UID1								0x0140
#define SYSTEM_UID2								0x0141
#define SYSTEM_UID3								0x0142
#define SYSTEM_UID4								0x0143
#define SYSTEM_UID5								0x0144
#define SYSTEM_UID6								0x0145
#define SYSTEM_UID7								0x0146
#define SYSTEM_UID8								0x0147
#define ACTIVATION1								0x0150
#define ACTIVATION2								0x0151
#define ACTIVATION3								0x0152
#define ACTIVATION4								0x0153
#define ACTIVATION5								0x0154
#define ACTIVATION6								0x0155
#define ACTIVATION7								0x0156
#define ACTIVATION8								0x0157
#define PRODUCT_ID1								0x0160
#define PRODUCT_ID2								0x0161
#define PRODUCT_ID3								0x0162
#define PRODUCT_ID4								0x0163
#define PRODUCT_ID5								0x0164


////////////////////////////////////////////////////////////////////////////
//System
////////////////////////////////////////////////////////////////////////////
#define SYS_ALARM_TIMES           				0x0200
#define SYS_ALARM_INTERVAL						0x0201
#define SYS_SERVICE_MOLDINGS_LOW				0x0202
#define SYS_SERVICE_MOLDINGS_HIGH				0x0203
#define SYS_LANGUAGE							0x0204
#define SYS_ROTATE_OUT_AT_ORIGIN				0x0206
#define SYS_PAUSE_OPEN_DOOR						0x0207
#define SYS_PLAN_MOLDING_LOW					0x0208
#define SYS_PLAN_MOLDING_HIGH					0x0209
#define SYS_PLAN_ALARM_LOW                      0x020A
#define SYS_PLAN_ALARM_HIGH                     0x020B
#define SYS_REJECT_ALARM						0x020C
#define SYS_MOLD_CLOSED_USE						0x020D
#define SYS_EXT_SERVO_USE						0x020E
#define SYS_RHOR_SERVO_USE                      0x020F
#define SYS_RVER_SERVO_USE                      0x0210
#define SYS_RUN_ADVANCE_USE                     0x0211
#define SYS_RUN_RETURN_USE                      0x0212
#define SYS_ROTATE_USE                         	0x0213  // 气动正臂倒角使用
#define SYS_RUN_ROTATE_USE                      0x0214  // 气动副臂倒角使用
#define SYS_DOOR_RESET_USE                      0x0215
#define SYS_EXTRA_CTRL_BIT_USE					0x0216 // 扩展控制位: 0位表示模外安全区2使用；1位表示模外安全区信号不使用
#define SYS_ROTATE_INMOLD_USE					0x021A
#define SYS_MAIN1_POLARY                        0x021B
#define SYS_EXT1_POLARY							0x021C
#define SYS_EXT2_POLARY							0x021D
#define SYS_EXT3_POLARY							0x021E
#define SYS_EXT4_POLARY							0x021F
#define SYS_MAIN1_IGNORE                        0x0220
#define SYS_EXT1_IGNORE							0x0221
#define SYS_EXT2_IGNORE							0x0222
#define SYS_EXT3_IGNORE							0x0223
#define SYS_EXT4_IGNORE							0x0224
#define SYS_INTERMOLD_DOWN_USE					0x0225
#define SYS_MID_OPEN_USE						0x0226
#define SYS_WAIT_OUTMOULD						0x0227
#define SYS_MAIN1_INMOLD_NOALM					0x0228
#define SYS_EXT1_INMOLD_NOALM					0x0229
#define SYS_AUTO_RETURN							0x022A
#define SYS_EXT2_INMOLD_NOALM					0x0230
#define SYS_EXT3_INMOLD_NOALM					0x0231
#define SYS_EXT4_INMOLD_NOALM					0x0232
#define SYS_JIG_USE								0x0233
#define SYS_RUNNER_USE                         	0x0234//气动副臂使用
#define SYS_RUN_DOWN_USE                        0x0235//气动副臂下位电眼使用
#define SYS_ADJUST_USE                         	0x0236//调位使用
#define SYS_HOME_INMOLD                        	0x0237
#define SYS_PROC2_USE                        	0x0238
#define SYS_PROC3_USE                        	0x0239
#define SYS_MAX_CODES	                        0x023A
#define SYS_IO_CLR								0x023B//退出自动时清除IO口
#define SYS_NET_IP_ADDR_LOW						0x0240
#define SYS_NET_IP_ADDR_HIGH					0x0241
#define SYS_NET_IP_MASK_LOW						0x0242
#define SYS_NET_IP_MASK_HIGH					0x0243
#define SYS_NET_IP_GATE_LOW						0x0244
#define SYS_NET_IP_GATE_HIGH					0x0245
#define SYS_OIL_USE								0x0246			//
#define SYS_OIL_INTERVAL_LOW					0x0247			//打油间隔，以分钟为单位 2000-01-01 00:00:00
#define SYS_OIL_INTERVAL_HIGH					0x0248
#define SYS_OIL_TIME_LOW						0x0249			//打油时间，以10ms为单位
#define SYS_OIL_TIME_HIGH						0x024A
#define SYS_OIL_USE_CTRL                        0x024B
#define SYS_PROC_USE                        	0x024C          //bie0:进程4使用
#define SYS_MAIN1_OUTPOLARY                     0x0250
#define SYS_EXT1_OUTPOLARY                      0x0251  // 输出极性
#define SYS_EXT2_OUTPOLARY                      0x0252
#define SYS_EXT3_OUTPOLARY                      0x0253
#define SYS_EXT4_OUTPOLARY                      0x0254
//捷嘉
#define SYS_MOP_ABD_TIME_LOW                    0x0256 //开模完成上升沿是不是来得太早需要丢弃的判断时间
#define SYS_MOP_ABD_TIME_HIGH                   0x0257
//布鲁艾诺
#define SYS_Y09_TIME_LOW                        0x0256 //Y09脉冲时间
#define SYS_Y09_TIME_HIGH                       0x0257
////////////////////////////////////////////////////////////////////////////
//Vision
////////////////////////////////////////////////////////////////////////////
#define SYS_VISION0_IP_LOW						0x0260
#define SYS_VISION0_IP_HIGH						0x0261
#define SYS_VISION1_IP_LOW						0x0262
#define SYS_VISION1_IP_HIGH						0x0263
#define SYS_VISION2_IP_LOW						0x0264
#define SYS_VISION2_IP_HIGH						0x0265
#define SYS_VISION3_IP_LOW						0x0266
#define SYS_VISION3_IP_HIGH						0x0267
#define SYS_VISION4_IP_LOW						0x0268
#define SYS_VISION4_IP_HIGH						0x0269
#define SYS_VISION5_IP_LOW						0x026A
#define SYS_VISION5_IP_HIGH						0x026B
#define SYS_VISION6_IP_LOW						0x026C
#define SYS_VISION6_IP_HIGH						0x026D
#define SYS_VISION7_IP_LOW						0x026E
#define SYS_VISION7_IP_HIGH						0x026F
#define SYS_VISION0_PORT						0x0270
#define SYS_VISION1_PORT						0x0271
#define SYS_VISION2_PORT						0x0272
#define SYS_VISION3_PORT						0x0273
#define SYS_VISION4_PORT						0x0274
#define SYS_VISION5_PORT						0x0275
#define SYS_VISION6_PORT						0x0276
#define SYS_VISION7_PORT						0x0277
#define SYS_VISION0_TYPE_TRIGGER				0x0278	//高8位表示类型(相机类型 0表示没有选择 1表示cognex) 低8位表示触发方式(触发方式:0表示协议触发;1表示端口触发(教导时指定输出端口))
#define SYS_VISION1_TYPE_TRIGGER				0x0279
#define SYS_VISION2_TYPE_TRIGGER				0x027A
#define SYS_VISION3_TYPE_TRIGGER				0x027B
#define SYS_VISION4_TYPE_TRIGGER				0x027C
#define SYS_VISION5_TYPE_TRIGGER				0x027D
#define SYS_VISION6_TYPE_TRIGGER				0x027E
#define SYS_VISION7_TYPE_TRIGGER				0x027F
#define SYS_VISION0_OUTVAR                      0x0280
#define SYS_VISION1_OUTVAR                      0x0281
#define SYS_VISION2_OUTVAR                      0x0282
#define SYS_VISION3_OUTVAR                      0x0283
#define SYS_VISION4_OUTVAR                      0x0284
#define SYS_VISION5_OUTVAR                      0x0285
#define SYS_VISION6_OUTVAR                      0x0286
#define SYS_VISION7_OUTVAR                      0x0287

#define SYS_MAIN2_POLARY                        0x0288
#define SYS_MAIN3_POLARY                        0x0289
#define SYS_MAIN4_POLARY                        0x028A
#define SYS_MAIN2_OUTPOLARY                     0x028B
#define SYS_MAIN3_OUTPOLARY                     0x028C
#define SYS_MAIN4_OUTPOLARY                     0x028D
#define SYS_MAIN2_IGNORE                        0x028E
#define SYS_MAIN3_IGNORE                        0x028F
#define SYS_MAIN4_IGNORE                        0x0290
#define SYS_MAIN2_INMOLD_NOALM					0x0291
#define SYS_MAIN3_INMOLD_NOALM					0x0292
#define SYS_MAIN4_INMOLD_NOALM					0x0293

////////////////////////////////////////////////////////////////////////////
//Servo
////////////////////////////////////////////////////////////////////////////
#define SERVO_MACHINE_MAX_LEN_X					0x0300
//#define SERVO_MACHINE_MAX_LEN_Y				0x0301
//#define SERVO_MACHINE_MAX_LEN_Z				0x0302
//#define SERVO_MACHINE_MAX_LEN_A				0x0303
//#define SERVO_MACHINE_MAX_LEN_B				0x0304
//#define SERVO_MACHINE_MAX_LEN_C				0x0305
#define SERVO_SOFTWARE_MAX_LEN_X				0x0306
#define SERVO_SOFTWARE_MAX_LEN_Y				0x0307
#define SERVO_SOFTWARE_MAX_LEN_Z				0x0308
#define SERVO_SOFTWARE_MAX_LEN_A				0x0309
#define SERVO_SOFTWARE_MAX_LEN_B				0x030A
#define SERVO_SOFTWARE_MAX_LEN_C				0x030B
#define SERVO_ORIGIN_OFFSET_X					0x030C
#define SERVO_ORIGIN_OFFSET_Y					0x030D
#define SERVO_ORIGIN_OFFSET_Z					0x030E
#define SERVO_ORIGIN_OFFSET_A					0x030F
#define SERVO_ORIGIN_OFFSET_B					0x0310
#define SERVO_ORIGIN_OFFSET_C					0x0311
#define SERVO_MAX_WAIT_POS_INMOLD_Y				0x0312
#define SERVO_MAX_WAIT_POS_INMOLD_A				0x0313
#define SERVO_MIN_SAFE_POS_OUTMOLD_Z			0x0314
#define SERVO_MAX_SAFE_POS_OUTMOLD_Z			0x0315
#define SERVO_MIN_SAFE_POS_INMOLD_Z				0x0316
#define SERVO_MAX_SAFE_POS_INMOLD_Z				0x0317
#define SERVO_MIN_SAFE_DIS_X_B					0x0318
#define SERVO_MIN_SAFE_POS_INMOLD_X				0x0319
#define SERVO_MAX_SAFE_POS_INMOLD_X				0x031A
#define SERVO_MIN_SAFE_POS_INMOLD_B				0x031B
#define SERVO_MAX_SAFE_POS_INMOLD_B				0x031C
#define SERVO_XMAX_SPEED						0x031D
#define SERVO_XMAX_ACCELERATION					0x031E
#define SERVO_XMAX_JERK                         0x031F
#define SERVO_YMAX_SPEED						0x0320
#define SERVO_YMAX_ACCELERATION					0x0321
#define SERVO_YMAX_JERK                         0x0322
#define SERVO_ZMAX_SPEED						0x0323
#define SERVO_ZMAX_ACCELERATION					0x0324
#define SERVO_ZMAX_JERK 						0x0325
#define SERVO_AMAX_SPEED						0x0326
#define SERVO_AMAX_ACCELERATION					0x0327
#define SERVO_AMAX_JERK 						0x0328
#define SERVO_BMAX_SPEED						0x0329
#define SERVO_BMAX_ACCELERATION					0x032A
#define SERVO_BMAX_JERK 						0x032B
#define SERVO_CMAX_SPEED						0x032C
#define SERVO_CMAX_ACCELERATION					0x032D
#define SERVO_CMAX_JERK     					0x032E
#define SERVO_MIN_A_TRAVE                       0x032F  // 横行时最小A(倒角)轴位置
#define SERVO_MAX_A_TRAVE                       0x0330  // 横行时最大A(倒角)轴位置
#define SERVO_MIN_A_INMOLD                      0x0331  // 模内最小A(倒角)轴位置
#define SERVO_MAX_A_INMOLD                      0x0332  // 模内最大A(倒角)轴位置
#define SERVO_MIN_SAFE_POS_OUTMOLD2_Z			0x0333
#define SERVO_MAX_SAFE_POS_OUTMOLD2_Z			0x0334
#define SERVO_HOME_VEL  						0x0335
#define SERVO_X_REV_UNITS						0x0336
#define SERVO_X_REV_PULSES						0x0337
#define SERVO_Y_REV_UNITS						0x0338
#define SERVO_Y_REV_PULSES						0x0339
#define SERVO_Z_REV_UNITS						0x033A
#define SERVO_Z_REV_PULSES						0x033B
#define SERVO_A_REV_UNITS						0x033C
#define SERVO_A_REV_PULSES						0x033D
#define SERVO_B_REV_UNITS						0x033E
#define SERVO_B_REV_PULSES						0x033F
#define SERVO_C_REV_UNITS						0x0340
#define SERVO_C_REV_PULSES						0x0341
#define SERVO_ANGLE_BMP							0x0342
#define SERVO_HOME_MODE							0x0343
#define SERVO_RAMP_BMP_HOME_TAIL                0x0344
#define SERVO_ENCODER_X                         0x0345
#define SERVO_ENCODER_Y                         0x0346
#define SERVO_ENCODER_Z                         0x0347
#define SERVO_ENCODER_A                         0x0348
#define SERVO_ENCODER_B                         0x0349
#define SERVO_ENCODER_C                         0x034A
#define SERVO_HOME_POS_X                        0x0351
#define SERVO_HOME_POS_Y                        0x0352
#define SERVO_HOME_POS_Z                        0x0353
#define SERVO_HOME_POS_A                        0x0354
#define SERVO_HOME_POS_B                        0x0355
#define SERVO_HOME_POS_C                        0x0356
#define SERVO_MOD_X                             0x0357
#define SERVO_MOD_Y                             0x0358
#define SERVO_MOD_Z                             0x0359
#define SERVO_MOD_A                             0x035A
#define SERVO_MOD_B                             0x035B
#define SERVO_MOD_C                             0x035C
#define SERVO_MIN_SAFE_POS_INMOLD_Z_A			0x035D	//压铸的副臂横行模内最小安全区域
#define SERVO_MAX_SAFE_POS_INMOLD_Z_A			0x035E	//压铸的副臂横行模内最小安全区域
#define SERVO_HOME_LOWVEL						0x035F
#define SERVO_MIN_B_TRAVE                       0x0360  //横行时最小B(单臂扩展)轴位置
#define SERVO_MAX_B_TRAVE                       0x0361  //横行时最大B(单臂扩展)轴位置

#define SERVO_MIN_C_TRAVE                       0x0362  //横行时最小C(扩展)轴位置
#define SERVO_MAX_C_TRAVE                       0x0363  //横行时最大C(扩展)轴位置
#define SERVO_MIN_C_INMOLD                      0x0364  //模内最小C(扩展)轴位置
#define SERVO_MAX_C_INMOLD                      0x0365  //模内最大C(扩展)轴位置
#define SERVO_MIN_X_TRAVE                       0x0366  //横行时最小(双臂模式)主臂引拔轴位置
#define SERVO_MAX_X_TRAVE                       0x0367  //横行时最大(双臂模式)主臂引拔轴位置

#define SERVO_PA5_X         0x036C//速度环比例增益 5-2000
#define SERVO_PA5_Y         0x036D//
#define SERVO_PA5_Z         0x036E//
#define SERVO_PA5_A         0x036F//
#define SERVO_PA5_B         0x0370//

#define SERVO_PA6_X         0x0371// 速度积分常数 1-1000
#define SERVO_PA6_Y         0x0372//
#define SERVO_PA6_Z         0x0373//
#define SERVO_PA6_A         0x0374//
#define SERVO_PA6_B         0x0375//

#define SERVO_PA7_X         0x0376// 转矩滤波器 20-500
#define SERVO_PA7_Y         0x0377//
#define SERVO_PA7_Z         0x0378//
#define SERVO_PA7_A         0x0379//
#define SERVO_PA7_B         0x037A//

#define SERVO_PA8_X         0x037B// 速度检测滤波器 20-500
#define SERVO_PA8_Y         0x037C//
#define SERVO_PA8_Z         0x037D//
#define SERVO_PA8_A         0x037E//
#define SERVO_PA8_B         0x037F//

#define SERVO_PA9_X         0x0380// 位置比例增益 0-1000
#define SERVO_PA9_Y         0x0381//
#define SERVO_PA9_Z         0x0382//
#define SERVO_PA9_A         0x0383//
#define SERVO_PA9_B         0x0384//

#define SERVO_PA19_X        0x0385 // 位置平滑滤波 0-1000
#define SERVO_PA19_Y        0x0386 //
#define SERVO_PA19_Z        0x0387 //
#define SERVO_PA19_A        0x0388 //
#define SERVO_PA19_B        0x0389 //

#define SERVO_PA63_X        0x038A// 负载惯量比 1-500
#define SERVO_PA63_Y        0x038B//
#define SERVO_PA63_Z        0x038C//
#define SERVO_PA63_A        0x038D//
#define SERVO_PA63_B        0x038E//
////////////////////////////////////////////////////////////////////////////
//User
////////////////////////////////////////////////////////////////////////////
#define USER_DATA_00_               			0x0400

#define USER_DATA_99_               			0x0463
// 原点复归定义
#define HOME_DEF_00                             (USER_DATA_00_+16)
#define HOME_DEF_01                             (USER_DATA_00_+17)
#define HOME_DEF_02                             (USER_DATA_00_+18)
#define HOME_DEF_03                             (USER_DATA_00_+19)
#define HOME_DEF_04                             (USER_DATA_00_+20)
#define HOME_DEF_05                             (USER_DATA_00_+21)
#define HOME_DEF_06                             (USER_DATA_00_+22)
#define HOME_DEF_07                             (USER_DATA_00_+23)
#define HOME_DEF_08                             (USER_DATA_00_+24)
#define HOME_DEF_09                             (USER_DATA_00_+25)
#define HOME_DEF_10                             (USER_DATA_00_+26)
#define HOME_DEF_11                             (USER_DATA_00_+27)
#define HOME_DEF_12                             (USER_DATA_00_+28)
#define HOME_DEF_13                             (USER_DATA_00_+29)
#define HOME_DEF_14                             (USER_DATA_00_+30)
#define HOME_DEF_15                             (USER_DATA_00_+31)
#define HOME_DEF_16                             (USER_DATA_00_+32)
#define HOME_DEF_17                             (USER_DATA_00_+33)
#define HOME_DEF_18                             (USER_DATA_00_+34)
#define HOME_DEF_19                             (USER_DATA_00_+35)

#define HOME_DEF_MAX                            20
// 厂商ID
#define FACTORY_ID_L							(USER_DATA_00_+98)
#define FACTORY_ID_H							USER_DATA_99_
////////////////////////////////////////////////////////////////////////////
//Vision test data
////////////////////////////////////////////////////////////////////////////
#define VISION1_MATCH1_DATA1                    0x500
#define VISION1_MATCH1_DATA2                    0x501
#define VISION1_MATCH1_DATA3                    0x502
#define VISION1_MATCH1_DATA4                    0x503
#define VISION1_MATCH2_DATA1                    0x504
#define VISION1_MATCH2_DATA2                    0x505
#define VISION1_MATCH2_DATA3                    0x506
#define VISION1_MATCH2_DATA4                    0x507
#define VISION1_MATCH3_DATA1                    0x508
#define VISION1_MATCH3_DATA2                    0x509
#define VISION1_MATCH3_DATA3                    0x50A
#define VISION1_MATCH3_DATA4                    0x50B
#define VISION2_MATCH1_DATA1                    0x510
#define VISION2_MATCH1_DATA2                    0x511
#define VISION2_MATCH1_DATA3                    0x512
#define VISION2_MATCH1_DATA4                    0x513
#define VISION2_MATCH2_DATA1                    0x514
#define VISION2_MATCH2_DATA2                    0x515
#define VISION2_MATCH2_DATA3                    0x516
#define VISION2_MATCH2_DATA4                    0x517
#define VISION2_MATCH3_DATA1                    0x518
#define VISION2_MATCH3_DATA2                    0x519
#define VISION2_MATCH3_DATA3                    0x51A
#define VISION2_MATCH3_DATA4                    0x51B
#define VISION3_MATCH1_DATA1                    0x520
#define VISION3_MATCH1_DATA2                    0x521
#define VISION3_MATCH1_DATA3                    0x522
#define VISION3_MATCH1_DATA4                    0x523
#define VISION3_MATCH2_DATA1                    0x524
#define VISION3_MATCH2_DATA2                    0x525
#define VISION3_MATCH2_DATA3                    0x526
#define VISION3_MATCH2_DATA4                    0x527
#define VISION3_MATCH3_DATA1                    0x528
#define VISION3_MATCH3_DATA2                    0x529
#define VISION3_MATCH3_DATA3                    0x52A
#define VISION3_MATCH3_DATA4                    0x52B
#define VISION4_MATCH1_DATA1                    0x530
#define VISION4_MATCH1_DATA2                    0x531
#define VISION4_MATCH1_DATA3                    0x532
#define VISION4_MATCH1_DATA4                    0x533
#define VISION4_MATCH2_DATA1                    0x534
#define VISION4_MATCH2_DATA2                    0x535
#define VISION4_MATCH2_DATA3                    0x536
#define VISION4_MATCH2_DATA4                    0x537
#define VISION4_MATCH3_DATA1                    0x538
#define VISION4_MATCH3_DATA2                    0x539
#define VISION4_MATCH3_DATA3                    0x53A
#define VISION4_MATCH3_DATA4                    0x53B
#define VISION5_MATCH1_DATA1                    0x540
#define VISION5_MATCH1_DATA2                    0x541
#define VISION5_MATCH1_DATA3                    0x542
#define VISION5_MATCH1_DATA4                    0x543
#define VISION5_MATCH2_DATA1                    0x544
#define VISION5_MATCH2_DATA2                    0x545
#define VISION5_MATCH2_DATA3                    0x546
#define VISION5_MATCH2_DATA4                    0x547
#define VISION5_MATCH3_DATA1                    0x548
#define VISION5_MATCH3_DATA2                    0x549
#define VISION5_MATCH3_DATA3                    0x54A
#define VISION5_MATCH3_DATA4                    0x54B
#define VISION6_MATCH1_DATA1                    0x550
#define VISION6_MATCH1_DATA2                    0x551
#define VISION6_MATCH1_DATA3                    0x552
#define VISION6_MATCH1_DATA4                    0x553
#define VISION6_MATCH2_DATA1                    0x554
#define VISION6_MATCH2_DATA2                    0x555
#define VISION6_MATCH2_DATA3                    0x556
#define VISION6_MATCH2_DATA4                    0x557
#define VISION6_MATCH3_DATA1                    0x558
#define VISION6_MATCH3_DATA2                    0x559
#define VISION6_MATCH3_DATA3                    0x55A
#define VISION6_MATCH3_DATA4                    0x55B
#define VISION7_MATCH1_DATA1                    0x560
#define VISION7_MATCH1_DATA2                    0x561
#define VISION7_MATCH1_DATA3                    0x562
#define VISION7_MATCH1_DATA4                    0x563
#define VISION7_MATCH2_DATA1                    0x564
#define VISION7_MATCH2_DATA2                    0x565
#define VISION7_MATCH2_DATA3                    0x566
#define VISION7_MATCH2_DATA4                    0x567
#define VISION7_MATCH3_DATA1                    0x568
#define VISION7_MATCH3_DATA2                    0x569
#define VISION7_MATCH3_DATA3                    0x56A
#define VISION7_MATCH3_DATA4                    0x56B
#define VISION8_MATCH1_DATA1                    0x570
#define VISION8_MATCH1_DATA2                    0x571
#define VISION8_MATCH1_DATA3                    0x572
#define VISION8_MATCH1_DATA4                    0x573
#define VISION8_MATCH2_DATA1                    0x574
#define VISION8_MATCH2_DATA2                    0x575
#define VISION8_MATCH2_DATA3                    0x576
#define VISION8_MATCH2_DATA4                    0x577
#define VISION8_MATCH3_DATA1                    0x578
#define VISION8_MATCH3_DATA2                    0x579
#define VISION8_MATCH3_DATA3                    0x57A
#define VISION8_MATCH3_DATA4                    0x57B

////////////////////////////////////////////////////////////////////////////
//Miscellaneous
////////////////////////////////////////////////////////////////////////////
#define MAIN_BOARD_INPUT_LOW						0x0600
#define MAIN_BOARD_INPUT_HIGH						0x0601
#define MAIN_BOARD_INPUT_EXT_LOW					0x0602
#define MAIN_BOARD_INPUT_EXT_HIGH					0x0603
#define EXT1_BOARD_INPUT							0x0604
#define EXT2_BOARD_INPUT							0x0605
#define EXT3_BOARD_INPUT							0x0606
#define EXT4_BOARD_INPUT							0x0607
#define MAIN_BOARD_OUTPUT_LOW						0x0608
#define MAIN_BOARD_OUTPUT_HIGH						0x0609
#define EXT1_BOARD_OUTPUT							0x060A
#define EXT2_BOARD_OUTPUT							0x060B
#define EXT3_BOARD_OUTPUT							0x060C
#define EXT4_BOARD_OUTPUT							0x060D
#define SYSTEM_STATE            					0x060E
#define RUN_STATE               					0x060F
#define RUN_TYPE                					0x0610
#define HOME_STATE									0x0611
#define TOTAL_MOLDS_LOW								0x0612
#define TOTAL_MOLDS_HIGH	       					0x0613
#define TOTAL_PLAN_LOW								0x0614
#define TOTAL_PLAN_HIGH								0x0615
#define TOTAL_REJECT	                			0x0616
#define PC_POINTER              					0x0617
#define PERIOD_TIME									0x0618
#define MESSAGE                 					0x0619
#define IMM_SYS_ALARM           					0x061A
#define PRODUCTER_ALARM         					0x061B
#define EXT1_BOARD_EXT_ALARM    					0x061C
#define EXT2_BOARD_EXT_ALARM    					0x061D
#define EXT3_BOARD_EXT_ALARM    					0x061E
#define EXT4_BOARD_EXT_ALARM    					0x061F
#define SERVOX_ALARM            					0x0620
#define SERVOY_ALARM            					0x0621
#define SERVOZ_ALARM            					0x0622
#define SERVOA_ALARM            					0x0623
#define SERVOB_ALARM            					0x0624
#define SERVOC_ALARM            					0x0625
#define SERVO_X_POS									0x0626
#define SERVO_Y_POS									0x0627
#define SERVO_Z_POS									0x0628
#define SERVO_A_POS									0x0629
#define SERVO_B_POS									0x062A
#define SERVO_C_POS									0x062B
#define EXT_BOARD_STATE								0x062C
#define SERVO_X_POS_EXT								0x062D
#define SERVO_Y_POS_EXT								0x062E
#define SERVO_Z_POS_EXT								0x062F
#define SERVO_A_POS_EXT								0x0630
#define SERVO_B_POS_EXT								0x0631
#define SERVO_C_POS_EXT								0x0632
#define RUNNER_DES_ASC_ALARM    					0x0633//气动副臂上下报警
#define INMOLD_TIME									0x0634
#define PERIOD_TIME2								0x0635
#define PERIOD_TIME3								0x0636
#define INMOLD_TIME2                                0x0637
#define INMOLD_TIME3                                0x0638
#define PC_POINTER2              					0x0639
#define PC_POINTER3              					0x063A
#define SYS_SERVICE_TICK_LOW						0x063B
#define SYS_SERVICE_TICK_HIGH						0x063C
#define KEY_PRESSED                                 0x063D
#define INMOLD_TIME1_H                              0x063E
#define INMOLD_TIME2_H                              0x063F
#define INMOLD_TIME3_H                              0x0640
#define PERIOD_TIME1_H								0x0641
#define PERIOD_TIME2_H								0x0642
#define PERIOD_TIME3_H								0x0643
#define SERVOX_ALARM_H            					0x0644
#define SERVOY_ALARM_H            					0x0645
#define SERVOZ_ALARM_H            					0x0646
#define SERVOA_ALARM_H            					0x0647
#define SERVOB_ALARM_H            					0x0648
#define SERVOC_ALARM_H            					0x0649
#define MESSAGE_H                 					0x064A
#define PERIOD_TIME4                                0x064B
#define PERIOD_TIME4_H                              0x064C
#define INMOLD_TIME4                                0x064D
#define INMOLD_TIME4_H                              0x064E
#define PC_POINTER4                                 0x064F
#define MAIN_BOARD_OUTPUT_EXT_LOW                   0x0650
#define MAIN_BOARD_OUTPUT_EXT_HIGH                  0x0651
//pyq 五轴一体机实时扭矩，实时速度
#define ACTUAL_TRQ_X      0X0666
#define ACTUAL_TRQ_Y      0X0667
#define ACTUAL_TRQ_Z      0X0668
#define ACTUAL_TRQ_A      0X0669
#define ACTUAL_TRQ_B      0X066A
#define ACTUAL_TRQ_C      0X066B

#define ACTUAL_SPEED_X     0X066C
#define ACTUAL_SPEED_Y     0X066D
#define ACTUAL_SPEED_Z     0X066E
#define ACTUAL_SPEED_A     0X066F
#define ACTUAL_SPEED_B     0X0670
#define ACTUAL_SPEED_C     0X0671
//pyq end
////////////////////////////////////////////////////////////////////////////
//IO映射表
////////////////////////////////////////////////////////////////////////////
//0-31是主板输入映射表	64字节对应主板上的64个输入
//32-39是第1块IO板输入映射表	16字节对应主板上的16个输入
//40-47是第2块IO板输入映射表	16字节对应主板上的16个输入
//48-55是第3块IO板输入映射表	16字节对应主板上的16个输入
//56-63是第4块IO板输入映射表	16字节对应主板上的16个输入
//64-127保留输入
#define MAX_IN_BMP                                  0x80
#define IN_BMP_BEG                                  0x0F00
#define IN_BMP_END                                  (IN_BMP_BEG+MAX_IN_BMP-1)

//0-31是主板输出映射表	64字节对应主板上的64个输出
//32-39是第1块IO板输出映射表	16字节对应主板上的16个输出
//40-47是第2块IO板输出映射表	16字节对应主板上的16个输出
//48-55是第3块IO板输出映射表	16字节对应主板上的16个输出
//56-63是第4块IO板输出映射表	16字节对应主板上的16个输出
//64-127保留输出
#define MAX_OUT_BMP                                 0x80
#define OUT_BMP_BEG                                 0x0F80
#define OUT_BMP_END                                 (OUT_BMP_BEG+MAX_OUT_BMP-1)

////////////////////////////////////////////////////////////////////////////
//用户变量初始化
////////////////////////////////////////////////////////////////////////////
#define INIT_USER_BEG								0x0700
#define INIT_USER_END                               (INIT_USER_BEG+MAX_USER_VARS-1)

////////////////////////////////////////////////////////////////////////////
//New Codes
////////////////////////////////////////////////////////////////////////////
#define NEW_CODE_BEG                                0x1000
#define NEW_CODE_END                                (NEW_CODE_BEG+MAX_CODES*MAX_PROCESS-1)

////////////////////////////////////////////////////////////////////////////
//New Paras
////////////////////////////////////////////////////////////////////////////
#define NEW_PARA_BEG                                0x5000
#define NEW_PARA_END                                (NEW_PARA_BEG+MAX_CODES*MAX_PROCESS-1)

#define MODBUS_ADDRESS_MAX              (NEW_PARA_END+1)

#endif

