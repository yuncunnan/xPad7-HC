#include "xioport.h"
#include "SignalNum.h"
#include "cmbprotocol.h"
#include <QDebug>

quint8 xIoPort::m_in2fun[MAX_IN_BMP*2];
quint8 xIoPort::m_out2fun[MAX_OUT_BMP*2];
QMap<quint32, quint32> xIoPort::m_fun2in;
QMap<quint32, quint32> xIoPort::m_fun2out;

void xIoPort::UpdateIn2Fun(qint8 * tab)
{
    int i;
    for (i=0; i<MAX_IN_BMP*2; i++)
        m_in2fun[i] = tab[i];
    m_fun2in.clear();
    for (i=0; i<MAX_IN_BMP*2; i++)
    {
        switch(m_in2fun[i])
        {
            case InSignalNum_MOP:       m_fun2in[IMM_VAR_IN_MOP] = i;       break;
            case InSignalNum_MCP:       m_fun2in[IMM_VAR_IN_MCP] = i;       break;
            case InSignalNum_DOOR:      m_fun2in[IMM_VAR_IN_SAFE] = i;      break;
            case InSignalNum_AUTO:      m_fun2in[IMM_VAR_IN_AUTO] = i;      break;
            case InSignalNum_REJECT:    m_fun2in[IMM_VAR_IN_REJECT] = i;    break;
            case InSignalNum_IMMEMG:    m_fun2in[IMM_VAR_IN_STOP] = i;      break;
            case InSignalNum_IMOP:      m_fun2in[IMM_VAR_IN_IMOP] = i;      break;
            case InSignalNum_EEF:       m_fun2in[IMM_VAR_IN_EFP] = i;       break;
            case InSignalNum_EEB:       m_fun2in[IMM_VAR_IN_EBP] = i;       break;
            case InSignalNum_C1P1:      m_fun2in[IMM_VAR_IN_C1P1] = i;      break;
            case InSignalNum_C1P2:      m_fun2in[IMM_VAR_IN_C1P2] = i;      break;
            case InSignalNum_C2P1:      m_fun2in[IMM_VAR_IN_C2P1] = i;      break;
            case InSignalNum_C2P2:      m_fun2in[IMM_VAR_IN_C2P2] = i;      break;
            case InSignalNum_MID:       m_fun2in[IMM_VAR_IN_MID] = i;       break;
            case InSignalNum_XALM:      m_fun2in[SV_VAR_IN_XALM] = i;       break;
            case InSignalNum_XCWL:      m_fun2in[SV_VAR_IN_XCWL] = i;       break;
            case InSignalNum_XCCWL:     m_fun2in[SV_VAR_IN_XCCWL] = i;      break;
            case InSignalNum_XORG:      m_fun2in[SV_VAR_IN_XHOME] = i;      break;
            case InSignalNum_YALM:      m_fun2in[SV_VAR_IN_YALM] = i;       break;
            case InSignalNum_YCWL:      m_fun2in[SV_VAR_IN_YCWL] = i;       break;
            case InSignalNum_YCCWL:     m_fun2in[SV_VAR_IN_YCCWL] = i;      break;
            case InSignalNum_YORG:      m_fun2in[SV_VAR_IN_YHOME] = i;m_fun2in[SV_VAR_IN_YWPOS] = i;break;
            case InSignalNum_ZALM:      m_fun2in[SV_VAR_IN_ZALM] = i;       break;
            case InSignalNum_ZCWL:      m_fun2in[SV_VAR_IN_ZCWL] = i;       break;
            case InSignalNum_ZCCWL:     m_fun2in[SV_VAR_IN_ZCCWL] = i;      break;
            case InSignalNum_ZORG:      m_fun2in[SV_VAR_IN_ZHOME] = i;      break;
            case InSignalNum_AALM:      m_fun2in[SV_VAR_IN_AALM] = i;       break;
            case InSignalNum_ACWL:      m_fun2in[SV_VAR_IN_ACWL] = i;       break;
            case InSignalNum_ACCWL:     m_fun2in[SV_VAR_IN_ACCWL] = i;      break;
			case InSignalNum_AORG:      m_fun2in[SV_VAR_IN_AHOME] = i;m_fun2in[SV_VAR_IN_AWPOS] = i;break;
            case InSignalNum_BALM:      m_fun2in[SV_VAR_IN_BALM] = i;       break;
            case InSignalNum_BCWL:      m_fun2in[SV_VAR_IN_BCWL] = i;       break;
            case InSignalNum_BCCWL:     m_fun2in[SV_VAR_IN_BCCWL] = i;      break;
            case InSignalNum_BORG:      m_fun2in[SV_VAR_IN_BHOME] = i;      break;
            case InSignalNum_CALM:      m_fun2in[SV_VAR_IN_CALM] = i;       break;
            case InSignalNum_CCWL:      m_fun2in[SV_VAR_IN_CCWL] = i;       break;
            case InSignalNum_CCCWL:     m_fun2in[SV_VAR_IN_CCCWL] = i;      break;
            case InSignalNum_CORG:      m_fun2in[SV_VAR_IN_CHOME] = i;      break;
            case InSignalNum_YSAFE:     m_fun2in[SV_VAR_IN_YWPOS] = i;      break;
            case InSignalNum_ASAFE:     m_fun2in[SV_VAR_IN_AWPOS] = i;      break;
            case InSignalNum_ZSAFE:     m_fun2in[SV_VAR_IN_OUTMOLD] = i;m_fun2in[SV_VAR_IN_INMOLD] = i;break;
            case InSignalNum_PHOR:      m_fun2in[RBT_VAR_IN_PRO_HOR] = i;   break;
            case InSignalNum_PVER:      m_fun2in[RBT_VAR_IN_PRO_VER] = i;   break;
            case InSignalNum_RHOR:      m_fun2in[RBT_VAR_IN_RUN_HOR] = i;   break;
            case InSignalNum_RVER:      m_fun2in[RBT_VAR_IN_RUN_VER] = i;   break;
            case InSignalNum_RASC:      m_fun2in[RBT_VAR_IN_RUN_ASC] = i;   break;
            case InSignalNum_RDES:      m_fun2in[RBT_VAR_IN_RUN_DES] = i;   break;
            case InSignalNum_RADV:      m_fun2in[RBT_VAR_IN_RUN_ADV] = i;   break;
            case InSignalNum_RRET:      m_fun2in[RBT_VAR_IN_RUN_RET] = i;   break;
            case InSignalNum_LOW:       m_fun2in[RBT_VAR_IN_LOW_AIR] = i;   break;
            case InSignalNum_ADVSAFE:   m_fun2in[RBT_VAR_IN_ARM_SAF] = i;   break;
            case InSignalNum_DESSAFE:   m_fun2in[RBT_VAR_IN_DWN_SAF] = i;   break;
            case InSignalNum_NotSignal: break;
            case InSignalNum_Null:      break;
        }
        if (m_in2fun[i] != InSignalNum_NotSignal)
            {
                int idx = i;
            if (i<16)//主板 *主板变量添加进来，只加前16个
                {
                m_fun2in[MAIN_VAR_X00+idx] = i;
                }
                else if (i<(16+16))//主板2
                {
                    idx -= 16;
                    m_fun2in[MAIN_VAR_X16+idx] = i;
                }
                else if (i<(16+16+16))//主板3
                {
                    idx -= (16+16);
                    m_fun2in[MAIN_VAR_X32+idx] = i;
                }
                else if (i<(16+16+16+16))//主板4
                {
                    idx -= (16+16+16);
                    m_fun2in[MAIN_VAR_X48+idx] = i;
                }
                else if (i<(16+16+16+16+16))//IO板1
                {
                    idx -= (16+16+16+16);
                    m_fun2in[EM1_VAR_X00+idx] = i;
                }
                else if (i<(16+16+16+16+16+16))//IO板2
                {
                    idx -= (16+16+16+16+16);
                    m_fun2in[EM2_VAR_X00+idx] = i;
                }
                else if (i<(16+16+16+16+16+16+16))//IO板3
                {
                    idx -= (16+16+16+16+16+16);
                    m_fun2in[EM3_VAR_X00+idx] = i;
                }
                else if (i<(16+16+16+16+16+16+16+16))//IO板4
                {
                    idx -= (16+16+16+16+16+16+16);
                    m_fun2in[EM4_VAR_X00+idx] = i;
                }
            }
    }
}

void xIoPort::UpdateOut2Fun(qint8 * tab)
{
    int i;
    for (i=0; i<MAX_OUT_BMP*2; i++)
        m_out2fun[i] = tab[i];
    m_fun2out.clear();
    for (i=0; i<MAX_OUT_BMP*2; i++)
    {
        switch(m_out2fun[i])
        {
            case OutSignalNum_EMO:      m_fun2out[IMM_VAR_OUT_EMO] = i;        break;
            case OutSignalNum_EMC:      m_fun2out[IMM_VAR_OUT_EMC] = i;        break;
            case OutSignalNum_MAF:      m_fun2out[IMM_VAR_OUT_MAF] = i;        break;
            case OutSignalNum_EEF:      m_fun2out[IMM_VAR_OUT_EEF] = i;        break;
            case OutSignalNum_EEB:      m_fun2out[IMM_VAR_OUT_EEB] = i;        break;
            case OutSignalNum_ROB:      m_fun2out[IMM_VAR_OUT_RBT] = i;        break;
            case OutSignalNum_C1P1:     m_fun2out[IMM_VAR_OUT_C1P1] = i;       break;
            case OutSignalNum_C1P2:     m_fun2out[IMM_VAR_OUT_C1P2] = i;       break;
            case OutSignalNum_C2P1:     m_fun2out[IMM_VAR_OUT_C2P1] = i;       break;
            case OutSignalNum_C2P2:     m_fun2out[IMM_VAR_OUT_C2P2] = i;       break;
            case OutSignalNum_HMAF:     m_fun2out[IMM_VAR_OUT_HMAF] = i;       break;
            case OutSignalNum_HEMC:     m_fun2out[IMM_VAR_OUT_HEMC] = i;       break;
            case OutSignalNum_BEEP:     m_fun2out[RBT_VAR_OUT_ALM_BEEP] = i;   break;
            case OutSignalNum_ALM:      m_fun2out[RBT_VAR_OUT_ALM_LAMP] = i;   break;
            case OutSignalNum_XON:      m_fun2out[SV_VAR_OUT_XSON] = i;        break;
            case OutSignalNum_YON:      m_fun2out[SV_VAR_OUT_YSON] = i;        break;
            case OutSignalNum_ZON:      m_fun2out[SV_VAR_OUT_ZSON] = i;        break;
            case OutSignalNum_AON:      m_fun2out[SV_VAR_OUT_ASON] = i;        break;
            case OutSignalNum_BON:      m_fun2out[SV_VAR_OUT_BSON] = i;        break;
            case OutSignalNum_CON:      m_fun2out[SV_VAR_OUT_CSON] = i;        break;
            case OutSignalNum_PHOR:     m_fun2out[RBT_VAR_OUT_PRO_HOR] = i;    break;
            case OutSignalNum_PVER:     m_fun2out[RBT_VAR_OUT_PRO_VER] = i;    break;
            case OutSignalNum_RHOR:     m_fun2out[RBT_VAR_OUT_RUN_HOR] = i;    break;
            case OutSignalNum_RVER:     m_fun2out[RBT_VAR_OUT_RUN_VER] = i;    break;
            case OutSignalNum_RDES:     m_fun2out[RBT_VAR_OUT_RUN_DES] = i;    break;
            case OutSignalNum_RADV:     m_fun2out[RBT_VAR_OUT_RUN_ADV] = i;    break;
            case OutSignalNum_RRET:     m_fun2out[RBT_VAR_OUT_RUN_RET] = i;    break;
            case OutSignalNum_RSPEED:   m_fun2out[RBT_VAR_OUT_RUN_SPEED] = i;  break;
            case OutSignalNum_OIL:      m_fun2out[RBT_VAR_OUT_OIL] = i;        break;
            case OutSignalNum_AUTOLED:  m_fun2out[RBT_VAR_OUT_LAMP] = i;        break;
            case OutSignalNum_STOP:     m_fun2out[RBT_VAR_OUT_ALM_LAMP] = i;        break;
		case OutSignalNum_CONV:      m_fun2out[OUT_VAR_CONV] = i;        break;
		case OutSignalNum_CUT:      m_fun2out[OUT_VAR_CUT] = i;        break;
		case OutSignalNum_NoSignal: break;
		case OutSignalNum_Null:     break;
		}
        if (m_out2fun[i] != OutSignalNum_NoSignal)
            {
                int idx = i;
                if (i<16)//主板1
                {
                m_fun2out[MAIN_VAR_Y00+idx] = i;
                }
                else if (i<(16+16))//主板2
                {
                    idx -= 16;
                    m_fun2out[MAIN_VAR_Y16+idx] = i;
                }
                else if (i<(16+16+16))//主板3
                {
                    idx -= (16+16);
                    m_fun2out[MAIN_VAR_Y32+idx] = i;
                }
                else if (i<(16+16+16+16))//主板4
                {
                    idx -= (16+16+16);
                    m_fun2out[MAIN_VAR_Y48+idx] = i;
                }
                else if (i<(16+16+16+16+16))//IO板1
                {
                    idx -= (16+16+16+16);
                    m_fun2out[EM1_VAR_Y00+idx] = i;
                }
                else if (i<(16+16+16+16+16+16))///IO板2
                {
                    idx -= (16+16+16+16+16);
                    m_fun2out[EM2_VAR_Y00+idx] = i;
                }
                else if (i<(16+16+16+16+16+16+16))//IO板3
                {
                    idx -= (16+16+16+16+16+16);
                    m_fun2out[EM3_VAR_Y00+idx] = i;
                }
                else if (i<(16+16+16+16+16+16+16+16))//IO板4
                {
                    idx -= (16+16+16+16+16+16+16);
                    m_fun2out[EM4_VAR_Y00+idx] = i;
                }
            }
        }
}
// 判断输入能不能作为扩展用
bool xIoPort::IsVisibleExtIn(quint32 varidx)
{
    if (m_fun2in.contains(varidx))
    {
        quint32 ioidx = m_fun2in[varidx];
        switch(m_in2fun[ioidx])
        {
            case InSignalNum_Null:      return true;
            case InSignalNum_MOP:
            case InSignalNum_MCP:
            case InSignalNum_DOOR:
            case InSignalNum_AUTO:
            case InSignalNum_REJECT:
            case InSignalNum_IMMEMG:
            case InSignalNum_IMOP:
            case InSignalNum_EEF:
            case InSignalNum_EEB:
            case InSignalNum_C1P1:
            case InSignalNum_C1P2:
            case InSignalNum_C2P1:
            case InSignalNum_C2P2:
            case InSignalNum_MID:
            case InSignalNum_XALM:
            case InSignalNum_XCWL:
            case InSignalNum_XCCWL:     return false;
            case InSignalNum_XORG:
            if(CMBProtocol::GetPaHorNotUse())
                return true;
            else
                return false;
            case InSignalNum_YALM:
            case InSignalNum_YCWL:
            case InSignalNum_YCCWL:
            case InSignalNum_YORG:
            case InSignalNum_ZALM:
            case InSignalNum_ZCWL:
            case InSignalNum_ZCCWL:
            case InSignalNum_ZORG:
            case InSignalNum_AALM:
            case InSignalNum_ACWL:
            case InSignalNum_ACCWL:     return false;
            case InSignalNum_AORG:
            if(CMBProtocol::GetRverSrvUse())
                return false;
            else
                return true;
            case InSignalNum_BALM:
            case InSignalNum_BCWL:
            case InSignalNum_BCCWL:     return false;
            case InSignalNum_BORG:
            if(CMBProtocol::GetRhorSrvUse())
                return false;
            else
                return true;
            case InSignalNum_CALM:
            case InSignalNum_CCWL:
            case InSignalNum_CCCWL:     return false;
            case InSignalNum_CORG:
            if(CMBProtocol::GetExtSrvUse())
                return false;
            else
                return true;
            case InSignalNum_XSAFE:
            case InSignalNum_YSAFE:
            case InSignalNum_ZSAFE:
            case InSignalNum_ASAFE:
            case InSignalNum_BSAFE:
            case InSignalNum_CSAFE:     return false;
            case InSignalNum_PHOR:
            if (CMBProtocol::GetRotateUse())
                return false;
            else
                return true;
            case InSignalNum_PVER:
            if (CMBProtocol::GetRotateUse())
                return false;
            else
                return true;
            case InSignalNum_RHOR:
            if (CMBProtocol::GetRunRotateUse())
                return false;
            else
                return true;
            case InSignalNum_RVER:
            if (CMBProtocol::GetRunRotateUse())
                return false;
            else
                return true;
            case InSignalNum_RASC:
            if (CMBProtocol::GetRunnerUse())
                return false;
            else
                return true;
            case InSignalNum_RDES:
            if (CMBProtocol::GetRunnerUse())
                return false;
            else
                return true;
            case InSignalNum_RADV:
            if (CMBProtocol::GetRunnerUse())
                return false;
            else
                return true;
            case InSignalNum_RRET:
            if (CMBProtocol::GetRunnerUse())
                return false;
            else
                return true;
            case InSignalNum_OIL:
            if (CMBProtocol::GetOilUse())
                return false;
            else
                return true;
            case InSignalNum_KEYRUN:
            if (CMBProtocol::GetExtraControl())
                return false;
            else
                return true;
            case InSignalNum_KEYSTOP:
            if (CMBProtocol::GetExtraControl())
                return false;
            else
                return true;
            case InSignalNum_KEYHOME:
            if (CMBProtocol::GetExtraControl())
                return false;
            else
                return true;
            case InSignalNum_ADVSAFE:
            case InSignalNum_DESSAFE:
            case InSignalNum_LOW:
            case InSignalNum_EMG:
            case InSignalNum_PWROFF:        return false;
            case InSignalNum_VAC1:
            case InSignalNum_VAC2:
            case InSignalNum_GRIP1:
            case InSignalNum_GRIP2:
            case InSignalNum_GRIP3:
            case InSignalNum_GRIP4:         return true;
            case InSignalNum_NotSignal:     return false;
        }
    }
    return false;
}

bool xIoPort::IsVisibleExtOut(quint32 varidx)
{
    if (m_fun2out.contains(varidx))
    {
        quint32 ioidx = m_fun2out[varidx];
        switch (m_out2fun[ioidx])
        {
            case OutSignalNum_Null:      return true;
            case OutSignalNum_EMO:
            case OutSignalNum_EMC:
            case OutSignalNum_MAF:
            case OutSignalNum_EEF:
            case OutSignalNum_EEB:
            case OutSignalNum_ROB:
            case OutSignalNum_C1P1:
            case OutSignalNum_C1P2:
            case OutSignalNum_C2P1:
            case OutSignalNum_C2P2:
            case OutSignalNum_HMAF:
            case OutSignalNum_HEMC:
            case OutSignalNum_BEEP:
            case OutSignalNum_ALM:
            case OutSignalNum_MANLED:
            case OutSignalNum_AUTOLED:
            case OutSignalNum_XON:
            case OutSignalNum_YON:
            case OutSignalNum_ZON:
            case OutSignalNum_AON:
            case OutSignalNum_BON:
            case OutSignalNum_CON:       return false;

            case OutSignalNum_PHOR:
            if (CMBProtocol::GetRotateUse())
                return false;
            else
                return true;
            case OutSignalNum_PVER:
            if (CMBProtocol::GetRotateUse())
                return false;
            else
                return true;
            case OutSignalNum_RHOR:
            if (CMBProtocol::GetRunRotateUse())
                return false;
            else
                return true;
            case OutSignalNum_RVER:
            if (CMBProtocol::GetRunRotateUse())
                return false;
            else
                return true;
            case OutSignalNum_RASC:
            if (CMBProtocol::GetRunnerUse())
                return false;
            else
                return true;
            case OutSignalNum_RDES:
            if (CMBProtocol::GetRunnerUse())
                return false;
            else
                return true;
            case OutSignalNum_RADV:
            if (CMBProtocol::GetRunnerUse())
                return false;
            else
                return true;
            case OutSignalNum_RRET:
            if (CMBProtocol::GetRunnerUse())
                return false;
            else
                return true;
            case OutSignalNum_RSPEED:    return true;
            case OutSignalNum_OIL:
            if (CMBProtocol::GetOilUse())
                return false;
            else
                return true;
            case OutSignalNum_RADJASC:
            if (CMBProtocol::GetAdjustUse())
                return false;
            else
                return true;
            case OutSignalNum_RADJADV:
            if (CMBProtocol::GetAdjustUse())
                return false;
            else
                return true;
            case OutSignalNum_VAC1:
			case OutSignalNum_VAC2:
            case OutSignalNum_GRIP1:
            case OutSignalNum_GRIP2:
            case OutSignalNum_GRIP3:
            case OutSignalNum_GRIP4:
			case OutSignalNum_CONV:
            case OutSignalNum_CUT:          return true;
            case OutSignalNum_NoSignal:     return false;
        }
    }
    return false;
}

// 判断输入信号可见
bool xIoPort::IsVisibleInSignal(quint32 varidx)
{
    if (m_fun2in.contains(varidx))
    {
        if (IsVisibleExtIn(varidx))
            return false;
        else
            return true;
    }
    return false;
}
bool xIoPort::IsVisibleOutSignal(quint32 varidx)
{
    if (m_fun2out.contains(varidx))
    {
        if (IsVisibleExtOut(varidx))
            return false;
        else
            return true;
    }
    return false;
}

//
bool xIoPort::GetIn(quint32 idx, quint16 * inbuf)
{
    bool ret = false;
    quint64 mainin = CMBProtocol::GetInMain();
    quint16 ioin[4];
    ioin[0] = CMBProtocol::GetInEm1();
    ioin[1] = CMBProtocol::GetInEm2();
    ioin[2] = CMBProtocol::GetInEm3();
    ioin[3] = CMBProtocol::GetInEm4();
    if (inbuf)
    {
        mainin = ((quint64)inbuf[0]) | (((quint64)inbuf[1]) << 16) | (((quint64)inbuf[2]) << 32) | (((quint64)inbuf[3]) << 48);
        ioin[0] = inbuf[4];
        ioin[1] = inbuf[5];
        ioin[2] = inbuf[6];
        ioin[3] = inbuf[7];
    }

    if (idx == SV_VAR_IN_OUTMOLD)
    {
        if (!CMBProtocol::GetHomeInmold())
            idx = SV_VAR_IN_ZHOME;
    }
    if (idx == SV_VAR_IN_INMOLD)
    {
        if (CMBProtocol::GetHomeInmold())
            idx = SV_VAR_IN_ZHOME;
    }

    if (m_fun2in.contains(idx))
    {
        quint32 ioidx = m_fun2in[idx];
        if (ioidx<64)//主板
        {
            ret = (mainin>>ioidx)&1;
        }
        else
        if (ioidx<(64+16))//IO板1
        {
            ioidx -= 64;
            ret =  (ioin[0]>>ioidx)&1;
        }
        else
        if (ioidx<(64+16+16))//IO板2
        {
            ioidx -= (64+16);
            ret =  (ioin[1]>>ioidx)&1;
        }
        else
        if (ioidx<(64+16+16+16))//IO板3
        {
            ioidx -= (64+16+16);
            ret =  (ioin[2]>>ioidx)&1;
        }
        else
        if (ioidx<(64+16+16+16+16))//IO板4
        {
            ioidx -= (64+16+16+16);
            ret =  (ioin[3]>>ioidx)&1;
    }
    }
    return ret;
}
// 得到扩展端口后缀
QString xIoPort::GetInSuffix(quint32 idx)
{
    QString ret = "";
    if (m_fun2in.contains(idx))
    {
        quint32 ioidx = m_fun2in[idx];
        if (ioidx<64)//主板
        {
            ret = (ioidx < 10) ? ("-X0" + QString::number(ioidx)) : ("-X" + QString::number(ioidx));
        }
        else
        if (ioidx<(64+16))//IO板1
        {
            ioidx -= 64;
            ret = (ioidx < 9) ? ("-E1X0" + QString::number(ioidx+1)) : ("-E1X" + QString::number(ioidx+1));
        }
        else
        if (ioidx<(64+16+16))//IO板2
        {
            ioidx -= (64+16);
            ret = (ioidx < 9) ? ("-E2X0" + QString::number(ioidx+1)) : ("-E2X" + QString::number(ioidx+1));
        }
        else
        if (ioidx<(64+16+16+16))//IO板3
        {
            ioidx -= (64+16+16);
            ret = (ioidx < 9) ? ("-E3X0" + QString::number(ioidx+1)) : ("-E3X" + QString::number(ioidx+1));
        }
        else
        if (ioidx<(64+16+16+16+16))//IO板4
        {
            ioidx -= (64+16+16+16);
            ret = (ioidx < 9) ? ("-E4X0" + QString::number(ioidx+1)) : ("-E4X" + QString::number(ioidx+1));
        }
    }
    return ret;
}

bool xIoPort::GetOut(quint32 idx, quint16 *outbuf)
{
    bool ret = false;
    quint32 mainout = CMBProtocol::GetOutMain();
    quint16 ioout[4];
    ioout[0] = CMBProtocol::GetOutEm1();
    ioout[1] = CMBProtocol::GetOutEm2();
    ioout[2] = CMBProtocol::GetOutEm3();
    ioout[3] = CMBProtocol::GetOutEm4();
    if (outbuf)
    {
        mainout = ((quint32)outbuf[0]) | (((quint32)outbuf[1]) << 16);
        ioout[0] = outbuf[2];
        ioout[1] = outbuf[3];
        ioout[2] = outbuf[4];
        ioout[3] = outbuf[5];
    }

    if (m_fun2out.contains(idx))
    {
        quint32 ioidx = m_fun2out[idx];
        if (ioidx < 64)
        {
            ret =  (mainout>>ioidx)&1;
        }
        else
        if(ioidx < (64+16))
        {
            ioidx -= 64;
            ret =  (ioout[0] >> ioidx) & 1;
        }
        else
        if(ioidx < (64+16+16))
        {
            ioidx -= (64+16);
            ret =  (ioout[1] >> ioidx) & 1;
        }
        else
        if(ioidx < (64+16+16+16))
        {
            ioidx -= (64+16+16);
            ret =  (ioout[2] >> ioidx) & 1;
        }
        else
        if(ioidx < (64+16+16+16+16))
        {
            ioidx -= (64+16+16+16);
            ret =  (ioout[3] >> ioidx) & 1;
        }
    }
    return ret;
}

QString xIoPort::GetOutSuffix(quint32 idx)
{
    QString ret = "";
    if (m_fun2out.contains(idx))
    {
        quint32 ioidx = m_fun2out[idx];
        if (ioidx<64)//主板
        {
            ret = (ioidx < 10) ? ("-Y0" + QString::number(ioidx)) : ("-Y" + QString::number(ioidx));
        }
        else
        if (ioidx<(64+16))//IO板1
        {
            ioidx -= 64;
            ret = (ioidx < 9) ? ("-E1Y0" + QString::number(ioidx+1)) : ("-E1Y" + QString::number(ioidx+1));
        }
        else
        if (ioidx<(64+16+16))//IO板2
        {
            ioidx -= (64+16);
            ret = (ioidx < 9) ? ("-E2Y0" + QString::number(ioidx+1)) : ("-E2Y" + QString::number(ioidx+1));
        }
        else
        if (ioidx<(64+16+16+16))//IO板3
        {
            ioidx -= (64+16+16);
            ret = (ioidx < 9) ? ("-E3Y0" + QString::number(ioidx+1)) : ("-E3Y" + QString::number(ioidx+1));
        }
        else
        if (ioidx<(64+16+16+16+16))//IO板4
        {
            ioidx -= (64+16+16+16);
            ret = (ioidx < 9) ? ("-E4Y0" + QString::number(ioidx+1)) : ("-E4Y" + QString::number(ioidx+1));
        }
    }
    return ret;
}
