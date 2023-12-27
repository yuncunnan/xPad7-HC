#include <QObject>
#include "cmbprotocol.h"
#include "servoalias.h"
#include <QSettings>

QString GetServoName(unsigned char srvIdx, bool isDefault)
{
    //isDefault为true时直接读取默认名称
    if(isDefault == false)
	{
        QString axisKey = NULL;
        if(srvIdx == AXIS_IDX_PHOR)
        {
            axisKey = "AXIS_NAME_X";
        }
        else if(srvIdx == AXIS_IDX_PVER)
        {
            axisKey = "AXIS_NAME_Y";
        }
        else if(srvIdx == AXIS_IDX_TRV)
        {
            axisKey = "AXIS_NAME_Z";
        }
        else if(srvIdx == AXIS_IDX_RHOR)
        {
            axisKey = "AXIS_NAME_B";
        }
        else if(srvIdx == AXIS_IDX_RVER)
        {
            axisKey = "AXIS_NAME_A";
        }
        else if(srvIdx == AXIS_IDX_EXT)
        {
            axisKey = "AXIS_NAME_C";
        }

        if(axisKey!=NULL)
        {
//           quint8 lan = CMBProtocol::GetLanguage();
//           QString curLan;
//           curLan.clear();
//           switch (lan)
//		{
//              case LAN_ENGLISH:
//                  curLan.append("chineses");
//                  break;
//              default:
//                  curLan.append("chineses");
//                  break;
//		}
        QSettings settings(XPAD_SETTING_FILE, QSettings::IniFormat);
        settings.beginGroup("chineses");
        if((settings.value(axisKey).toString()!=""))
        {
          return  QString(settings.value(axisKey).toString());
        }
      }
    }

#if ((FACTORY == FA_GH) || (FACTORY == FA_HAMO))
{
		if ((CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4))
    {
        if (srvIdx == AXIS_IDX_PHOR)
            return QString("Y");
        else if (srvIdx == AXIS_IDX_PVER)
            return QString("Z");
        else if (srvIdx == AXIS_IDX_TRV)
            return QString("X");
        else if (srvIdx == AXIS_IDX_RHOR)
            return QString("B");
        else if (srvIdx == AXIS_IDX_RVER)
            return QString("C");
        else if (srvIdx == AXIS_IDX_EXT)
            return QString("A");
        else
            return QString("RES");
    }
    else
    {
        // 双臂
	if (srvIdx == AXIS_IDX_PHOR)		// 正臂引拔轴
		return QString("Y");
	else if (srvIdx == AXIS_IDX_PVER)	// 正臂上下轴
		return QString("Z");
	else if (srvIdx == AXIS_IDX_TRV)	// 横行轴
		return QString("X");
	else if (srvIdx == AXIS_IDX_RHOR)	// 副臂引拔轴
		return QString("Y2");
	else if (srvIdx == AXIS_IDX_RVER)	// 副臂上下轴
		return QString("Z2");
	else if (srvIdx == AXIS_IDX_EXT)	// 扩展轴
		return QString("A");
	else								// 保留
		return QString("RES");
    }
}
#elif ((FACTORY == FA_XIONGCHUANG) || (FACTORY == FA_VICTOR) || (FACTORY == FA_KEHUI) || (FACTORY == FA_WEILIHE) || (FACTORY == FA_SIGMA) ||  (FACTORY == FA_SINROBOT_CN) || (FACTORY == FA_BEISHITE_CN) || (FACTORY == FA_FUSHITONG)|| (FACTORY == FA_BEISHITE_CN))
{
    if ((CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4))
    {
        if (srvIdx == AXIS_IDX_PHOR)
            return QObject::tr("引拔");
        else if (srvIdx == AXIS_IDX_PVER)
            return QObject::tr("上下");
        else if (srvIdx == AXIS_IDX_TRV)
        return QObject::tr("横行");
        else if (srvIdx == AXIS_IDX_RHOR)
            return QObject::tr("旋转");
        else if (srvIdx == AXIS_IDX_RVER)
            return QObject::tr("倒角");
        else if (srvIdx == AXIS_IDX_EXT)
        return QObject::tr("扩展");
        else
        return QObject::tr("保留");
    }
    else
    {
        // 双臂
    if (srvIdx == AXIS_IDX_PHOR)		// 正臂引拔轴
        return QObject::tr("正引拔");
    else if (srvIdx == AXIS_IDX_PVER)	// 正臂上下轴
        return QObject::tr("正上下");
    else if (srvIdx == AXIS_IDX_TRV)	// 横行轴
        return QObject::tr("横行");
    else if (srvIdx == AXIS_IDX_RHOR)	// 副臂引拔轴
        return QObject::tr("副引拔");
    else if (srvIdx == AXIS_IDX_RVER)	// 副臂上下轴
        return QObject::tr("副上下");
    else if (srvIdx == AXIS_IDX_EXT)	// 扩展轴
        return QObject::tr("扩展");
    else								// 保留
        return QObject::tr("保留");
    }
}
#elif ((FACTORY == FA_SINROBOT_SIDE) || FACTORY == FA_JIEJIA_SIDE)
    if ((CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4))
    {
        if (srvIdx == AXIS_IDX_PHOR)
            return QObject::tr("引拔");
        else if (srvIdx == AXIS_IDX_PVER)
            return QObject::tr("上下");
        else if (srvIdx == AXIS_IDX_TRV)
        return QObject::tr("横行");
        else if (srvIdx == AXIS_IDX_RHOR)
            return QObject::tr("旋转");
        else if (srvIdx == AXIS_IDX_RVER)
            return QObject::tr("倒角");
        else if (srvIdx == AXIS_IDX_EXT)
        return QObject::tr("扩展");
        else
        return QObject::tr("保留");
    }
    else
    {
        // 双臂
    if (srvIdx == AXIS_IDX_PHOR)		// 正臂引拔轴
        return QObject::tr("正引拔");
    else if (srvIdx == AXIS_IDX_PVER)	// 正臂上下轴
        return QObject::tr("出入模");
    else if (srvIdx == AXIS_IDX_TRV)	// 横行轴
        return QObject::tr("上下");
    else if (srvIdx == AXIS_IDX_RHOR)	// 副臂引拔轴
        return QObject::tr("副引拔");
    else if (srvIdx == AXIS_IDX_RVER)	// 副臂上下轴
        return QObject::tr("副上下");
    else if (srvIdx == AXIS_IDX_EXT)	// 扩展轴
        return QObject::tr("扩展");
    else								// 保留
        return QObject::tr("保留");
    }

#elif ((FACTORY == FA_KINGROBOT) || (FACTORY == FA_BEISHITE) || (FACTORY == FA_TUOMU))
{
		if ((CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4))
    {
        if (srvIdx == AXIS_IDX_PHOR)
            return QString("X");
        else if (srvIdx == AXIS_IDX_PVER)
            return QString("Z");
        else if (srvIdx == AXIS_IDX_TRV)
            return QString("Y");
        else if (srvIdx == AXIS_IDX_RHOR)
            return QString("B");
        else if (srvIdx == AXIS_IDX_RVER)
            return QString("C");
        else if (srvIdx == AXIS_IDX_EXT)
            return QString("A");
        else
            return QString("RES");
    }
    else
    {
        // 双臂
	if (srvIdx == AXIS_IDX_PHOR)		// 正臂引拔轴
		return QString("X");
	else if (srvIdx == AXIS_IDX_PVER)	// 正臂上下轴
		return QString("Z");
	else if (srvIdx == AXIS_IDX_TRV)	// 横行轴
		return QString("Y");
	else if (srvIdx == AXIS_IDX_RHOR)	// 副臂引拔轴
		return QString("X2");
	else if (srvIdx == AXIS_IDX_RVER)	// 副臂上下轴
		return QString("Z2");
	else if (srvIdx == AXIS_IDX_EXT)	// 扩展轴
		return QString("A");
	else								// 保留
		return QString("RES");
    }
}
#elif ((FACTORY == FA_RUIBEI) || (FACTORY == FA_NEWPARTNER))
{
    if ((CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4))
    {
        if (srvIdx == AXIS_IDX_PHOR)
            return QString("Y");
        else if (srvIdx == AXIS_IDX_PVER)
            return QString("Z");
        else if (srvIdx == AXIS_IDX_TRV)
            return QString("X");
        else if (srvIdx == AXIS_IDX_RHOR)
            return QString("B");
        else if (srvIdx == AXIS_IDX_RVER)
            return QString("C");
        else if (srvIdx == AXIS_IDX_EXT)
            return QString("A");
        else
            return QString("RES");
    }
    else
    {
        // 双臂
    if (srvIdx == AXIS_IDX_PHOR)		// 正臂引拔轴
        return QObject::("Y");
    else if (srvIdx == AXIS_IDX_PVER)	// 正臂上下轴
        return QObject::("Z");
    else if (srvIdx == AXIS_IDX_TRV)	// 横行轴
        return QObject::("X");
    else if (srvIdx == AXIS_IDX_RHOR)	// 副臂引拔轴
        return QObject::("Y2");
    else if (srvIdx == AXIS_IDX_RVER)	// 副臂上下轴
            return QObject::("Z2");
    else if (srvIdx == AXIS_IDX_EXT)	// 扩展轴
        return QObject::("A");
    else								// 保留
        return QObject::tr("保留");
    }
}
#elif ((FACTORY == FA_KEWEI) || (FACTORY == FA_KEHAO) || (FACTORY == FA_WOERDA) || (FACTORY == FA_ZHENJIE))
    if (srvIdx == AXIS_IDX_PHOR)		// 正臂引拔轴
        return QObject::tr("前后Y1");
    else if (srvIdx == AXIS_IDX_PVER)	// 正臂上下轴
        return QObject::tr("取件Z1");
    else if (srvIdx == AXIS_IDX_TRV)	// 横行轴
        return QObject::tr("横行X1");
    else if (srvIdx == AXIS_IDX_RHOR)	// 副臂引拔轴
        return QObject::tr("保留");
    else if (srvIdx == AXIS_IDX_RVER)	// 副臂上下轴
        return QObject::tr("喷雾Z2");
    else if (srvIdx == AXIS_IDX_EXT)	// 扩展轴
        return QObject::tr("扩展");
    else								// 保留
        return QObject::("RES");
#elif (FACTORY == FA_YIDAO)
    if (srvIdx == AXIS_IDX_PHOR)		// 正臂引拔轴
        return QObject::tr("引拔");
    else if (srvIdx == AXIS_IDX_PVER)	// 正臂上下轴
        return QObject::tr("上下");
    else if (srvIdx == AXIS_IDX_TRV)	// 横行轴
        return QObject::tr("横行");
    else if (srvIdx == AXIS_IDX_RHOR)	// 副臂引拔轴
        return QObject::tr("引拔2");
    else if (srvIdx == AXIS_IDX_RVER)	// 副臂上下轴
        return QObject::tr("上下2");
    else if (srvIdx == AXIS_IDX_EXT)	// 扩展轴
        return QObject::tr("扩展");
    else								// 保留
        return QObject::tr("RES");
/*#elif (FACTORY == FA_BOAO)
    if (srvIdx == AXIS_IDX_PHOR)		// 正臂引拔轴
        return QObject::("Y");
    else if (srvIdx == AXIS_IDX_PVER)	// 正臂上下轴
        return QObject::("Z");
    else if (srvIdx == AXIS_IDX_TRV)	// 横行轴
        return QObject::("X");
    else if (srvIdx == AXIS_IDX_RHOR)	// 副臂引拔轴
        return QObject::("Y2");
    else if (srvIdx == AXIS_IDX_RVER)	// 副臂上下轴
        return QObject::("Z2");
    else if (srvIdx == AXIS_IDX_EXT)	// 扩展轴
        return QObject::("A");
    else								// 保留
        return QObject::("RES");*/
#elif (FACTORY == FA_CHAOQUN)
    {
    if (srvIdx == AXIS_IDX_PHOR)		// 正臂引拔轴
        return QString("MY");
    else if (srvIdx == AXIS_IDX_PVER)	// 正臂上下轴
        return QString("MZ");
    else if (srvIdx == AXIS_IDX_TRV)	// 横行轴
        return QString("X");
    else if (srvIdx == AXIS_IDX_RHOR)	// 副臂引拔轴
        return QString("SY");
    else if (srvIdx == AXIS_IDX_RVER)	// 副臂上下轴
        return QString("SZ");
    else if (srvIdx == AXIS_IDX_EXT)	// 扩展轴
        return QString("A");
    else								// 保留
        return QString("RES");
    }
#elif (FACTORY == FA_AIERFA)
{
    if ((CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4))
    {
        if (srvIdx == AXIS_IDX_PHOR)
            return QString("MX");
        else if (srvIdx == AXIS_IDX_PVER)
            return QString("MZ");
        else if (srvIdx == AXIS_IDX_TRV)
            return QString("Y");
        else if (srvIdx == AXIS_IDX_RHOR)
            return QString("B");
        else if (srvIdx == AXIS_IDX_RVER)
            return QString("C");
        else if (srvIdx == AXIS_IDX_EXT)
            return QString("A");
        else
            return QString("RES");
    }
    else
    {
        // 双臂
    if (srvIdx == AXIS_IDX_PHOR)		// 正臂引拔轴
        return QObject::tr("MX");
    else if (srvIdx == AXIS_IDX_PVER)	// 正臂上下轴
        return QObject::tr("MZ");
    else if (srvIdx == AXIS_IDX_TRV)	// 横行轴
        return QObject::tr("Y");
    else if (srvIdx == AXIS_IDX_RHOR)	// 副臂引拔轴
        return QObject::tr("SX");
    else if (srvIdx == AXIS_IDX_RVER)	// 副臂上下轴
            return QObject::tr("SZ");
    else if (srvIdx == AXIS_IDX_EXT)	// 扩展轴
        return QObject::tr("A");
    else								// 保留
        return QObject::tr("保留");
    }
}
#elif (FACTORY == FA_VICTOR_SPECIAL)
{
    // 单臂
    if ((CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4))
    {
        if (srvIdx == AXIS_IDX_PHOR)		// 正臂引拔轴
            return QString("X");
        else if (srvIdx == AXIS_IDX_PVER)	// 正臂上下轴
            return QString("Y");
        else if (srvIdx == AXIS_IDX_TRV)	// 横行轴
            return QString("Z");
        else if (srvIdx == AXIS_IDX_RHOR)	// 旋转
            return QString("B");
        else if (srvIdx == AXIS_IDX_RVER)	// 倒角
            return QString("C");
        else if (srvIdx == AXIS_IDX_EXT)	// 扩展轴
            return QString("A");
        else								// 保留
            return QString("RES");
    }
    else
    {
        // 双臂
        if (srvIdx == AXIS_IDX_PHOR)		// 正臂引拔轴
			return QString("Y");
        else if (srvIdx == AXIS_IDX_PVER)	// 正臂上下轴
            return QString("Z");
        else if (srvIdx == AXIS_IDX_TRV)	// 横行轴
            return QString("X");
        else if (srvIdx == AXIS_IDX_RHOR)	// 副臂引拔轴
			return QString("A");
        else if (srvIdx == AXIS_IDX_RVER)	// 副臂上下轴
            return QString("Y2");
        else if (srvIdx == AXIS_IDX_EXT)	// 扩展轴
            return QString("C");
        else								// 保留
            return QString("RES");
    }
}
#else
	// 单臂
    if ((CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_E4) || (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_F4))
	{
        if (srvIdx == AXIS_IDX_PHOR)		// 正臂引拔轴
            return QString("X");
        else if (srvIdx == AXIS_IDX_PVER)	// 正臂上下轴
            return QString("Y");
        else if (srvIdx == AXIS_IDX_TRV)	// 横行轴
            return QString("Z");
        else if (srvIdx == AXIS_IDX_RHOR)	// 旋转
            return QString("B");
        else if (srvIdx == AXIS_IDX_RVER)	// 倒角
            return QString("C");
        else if (srvIdx == AXIS_IDX_EXT)	// 扩展轴
            return QString("A");
        else								// 保留
            return QString("RES");
	}
    else if (CMBProtocol::GetSysType() == ROBOTARM_TYPE_SIXSV_PAD_YZ)
    {
        if (srvIdx == AXIS_IDX_PHOR)		// 正臂引拔轴
            return QObject::tr("前后Y1");
        else if (srvIdx == AXIS_IDX_PVER)	// 正臂上下轴
            return QObject::tr("取件Z1");
        else if (srvIdx == AXIS_IDX_TRV)	// 横行轴
            return QObject::tr("横行X1");
        else if (srvIdx == AXIS_IDX_RHOR)	// 副臂引拔轴
            return QObject::tr("保留");
        else if (srvIdx == AXIS_IDX_RVER)	// 副臂上下轴
            return QObject::tr("喷雾Z2");
        else if (srvIdx == AXIS_IDX_EXT)	// 扩展轴
            return QObject::tr("扩展");
        else								// 保留
            return QObject::tr("RES");
    }
	else
	{
            // 双臂
        if (srvIdx == AXIS_IDX_PHOR)		// 正臂引拔轴
            return QString("X");
        else if (srvIdx == AXIS_IDX_PVER)	// 正臂上下轴
            return QString("Y");
        else if (srvIdx == AXIS_IDX_TRV)	// 横行轴
            return QString("Z");
        else if (srvIdx == AXIS_IDX_RHOR)	// 副臂引拔轴
            return QString("X2");
        else if (srvIdx == AXIS_IDX_RVER)	// 副臂上下轴
            return QString("Y2");
        else if (srvIdx == AXIS_IDX_EXT)	// 扩展轴
            return QString("A");
        else								// 保留
            return QString("RES");
	}
#endif
}
