/*=============================================================================
模   块   名: USB-KEY操作
文   件   名: UsbImportLicence.cpp
相 关  文 件: UsbImportLicence.h
文件实现功能: USB授权操作
作        者: 王昊
版        本: V4.0  Copyright(C) 2006-2006 Kedacom, All rights reserved.
-------------------------------------------------------------------------------
修改记录:
日      期  版本    修改人      修改内容
2006/10/11  1.0     王昊        创建
=============================================================================*/

// UsbImportLicence.cpp: implementation of the CUsbImportLicence class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UsbImportLicence.h"
#include "hkerror.h"
#include <stdio.h>

/*=============================================================================
函 数 名:SetTag
功    能:设置标签名
参    数:IN LPCSTR lptrTag                      [in]    标签名
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2006/10/11  1.0     王昊    创建
=============================================================================*/
void TUsbDeviceInfo::SetTag(IN LPCSTR lptrTag)
{
    if ( lptrTag != NULL )
    {
        memset( m_szTag, 0, sizeof (m_szTag) );
        strncpy( m_szTag, lptrTag, sizeof (m_szTag) - 1 );
    }
    return;
}

/*=============================================================================
函 数 名:SetSerialNo
功    能:设置序列号
参    数:IN u8 *pbySerialNo                     [in]    序列号
注    意:输入序列号为16进制内存
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2006/10/11  1.0     王昊    创建
=============================================================================*/
void TUsbDeviceInfo::SetSerialNo(IN u8 *pbySerialNo)
{
    if ( pbySerialNo != NULL )
    {
        memset( m_szSerialNo, 0, sizeof (m_szSerialNo) );
        HK_HexToStr( pbySerialNo, HK_SERIAL_NUM_LEN,
                     reinterpret_cast<u8*>(m_szSerialNo) );
    }
    return;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUsbImportLicence::CUsbImportLicence()
{

}

CUsbImportLicence::~CUsbImportLicence()
{
}

/*=============================================================================
函 数 名:SetDeviceCallBack
功    能:设置设备状态回调函数
参    数:IN LPCSTR lptrReaderName               [in]    读卡器名
         IN TUsbVerifyCallBack pFuncOnCallBack  [in]    插入回调函数
         IN TUsbVerifyCallBack pFuncOffCallBack [in]    拔出回调函数
         IN void *pCBData                       [in]    回调数据
注    意:错误码用GetErrorDescription解释
返 回 值:设置成功: 0; 设置失败: 错误码
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2006/10/11  1.0     王昊    创建
=============================================================================*/
u32 CUsbImportLicence::SetDeviceCallBack(IN LPCSTR lptrReaderName,
                                         IN TUsbVerifyCallBack pFuncOnCallBack,
                                         IN TUsbVerifyCallBack pFuncOffCallBack,
                                         IN void *pCBData)
{
    u32 dwRet = HK_SetDevChgFunc( lptrReaderName, pFuncOnCallBack,
                                  pFuncOffCallBack, pCBData, NULL );
    return dwRet;
}

/*=============================================================================
函 数 名:FormatDevice
功    能:格式化设备
参    数:IN LPCSTR lptrReaderName               [in]    读卡器名
注    意:错误码用GetErrorDescription解释
返 回 值:格式化成功: 0; 格式化失败: 错误码
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2006/10/11  1.0     王昊    创建
=============================================================================*/
u32 CUsbImportLicence::FormatDevice(IN LPCSTR lptrReaderName)
{
    HKHANDLE hCard = NULL;
    u32 dwStatus = 0;

    //检测状态
    u32 dwRet = HK_GetDevState( lptrReaderName, &dwStatus );
    if ( dwRet != 0 )
    {
        return dwRet;
    }
    else if ( dwStatus != HGS_STATE_PRESENT )
    {
        return HKI_ERR_DEV_NOTFOUND;
    }

    //连接
    dwRet = HK_ConnectDev( const_cast<s8*>(lptrReaderName), &hCard );
    if ( dwRet != 0 )
    {
        return dwRet;
    }

    //独占
    dwRet = HK_BeginTransaction( hCard );
    if ( dwRet != 0 )
    {
        HK_DisconnectDev( hCard );
        return dwRet;
    }

    do
    {
        //擦除原有数据
        dwRet = HK_Erase( hCard, DEFAULT_USBKEY_SO_PIN );
//        if ( dwRet != 0 )
//        {
//            break;
//        }

        //格式化
        SYSTEMTIME tSysTime;
        GetLocalTime( &tSysTime );
        s8 szTag[MAXLEN_USBKEY_DEVICE_TAG] = {0};
        sprintf( szTag, _T("%s %.4d-%.2d-%.2d %.2d:%.2d:%.2d"),
                 DEFAULT_USBKEY_TAG_PREFIX,
                 tSysTime.wYear, tSysTime.wMonth, tSysTime.wDay,
                 tSysTime.wHour, tSysTime.wMinute, tSysTime.wSecond );

        dwRet = HK_Format( hCard, szTag, DEFAULT_USBKEY_SO_PIN,
                           DEFAULT_USBKEY_USER_PIN, HK_ANYONE_ACCESS,
                           HK_ANYONE_ACCESS );
        if ( dwRet != 0 )
        {
            break;
        }

    } while ( FALSE );

    //解除独占
    u32 dwEnd = HK_EndTransaction( hCard );
    if ( dwEnd != 0 && dwRet == 0 )
    {
        dwRet = dwEnd;
    }
    //断开连接
    u32 dwDisconnect = HK_DisconnectDev( hCard );
    hCard = NULL;
    if ( dwDisconnect != 0 && dwRet == 0 )
    {
        dwRet = dwDisconnect;
    }

    return dwRet;
}

/*=============================================================================
函 数 名:GetDeviceInfo
功    能:获取设备信息
参    数:IN LPCSTR lptrReaderName               [in]    读卡器名
         OUT TUsbDeviceInfo &tInfo              [out]   设备信息
注    意:错误码用GetErrorDescription解释
返 回 值:获取成功: 0; 获取失败: 错误码
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2006/10/11  1.0     王昊    创建
=============================================================================*/
u32 CUsbImportLicence::GetDeviceInfo(IN LPCSTR lptrReaderName,
                                     OUT TUsbDeviceInfo &tInfo)
{
    HKHANDLE hCard = NULL;
    u32 dwStatus = 0;

    tInfo.Clear();

    //检测状态
    u32 dwRet = HK_GetDevState( lptrReaderName, &dwStatus );
    if ( dwRet != 0 )
    {
        return dwRet;
    }
    else if ( dwStatus != HGS_STATE_PRESENT )
    {
        return HKI_ERR_DEV_NOTFOUND;
    }

    //连接
    dwRet = HK_ConnectDev( const_cast<s8*>(lptrReaderName), &hCard );
    if ( dwRet != 0 )
    {
        return dwRet;
    }

    //独占
    dwRet = HK_BeginTransaction( hCard );
    if ( dwRet != 0 )
    {
        HK_DisconnectDev( hCard );
        return dwRet;
    }

    do
    {
        s8 szTag[MAXLEN_USBKEY_DEVICE_TAG] = {0};   //设备标签名
        u8 abySerialNo[HK_SERIAL_NUM_LEN] = {0};    //设备序列号
        u32 dwFreeSpace = 0;                        //剩余空间

        //获取标签名
        dwRet = HK_GetDeviceTag( hCard, szTag );
        if ( dwRet != 0 )
        {
            break;
        }

        //获取序列号
        dwRet = HK_GetSerialNum( hCard, abySerialNo );
        if ( dwRet != 0 )
        {
            break;
        }

        //获取剩余空间
        dwRet = HK_GetFreeSize( hCard, &dwFreeSpace );
        if ( dwRet != 0 )
        {
            break;
        }

        //设置输出参数
        tInfo.SetTag( szTag );
        tInfo.SetSerialNo( abySerialNo );
        tInfo.SetUsbFreeSpace( dwFreeSpace );

    } while ( FALSE );

    //解除独占
    u32 dwEnd = HK_EndTransaction( hCard );
    if ( dwEnd != 0 && dwRet == 0 )
    {
        dwRet = dwEnd;
    }
    //断开连接
    u32 dwDisconnect = HK_DisconnectDev( hCard );
    hCard = NULL;
    if ( dwDisconnect != 0 && dwRet == 0 )
    {
        dwRet = dwDisconnect;
    }

    return dwRet;
}

/*=============================================================================
函 数 名:SaveRight
功    能:保存授权信息
参    数:IN LPCSTR lptrReaderName               [in]    读卡器名
         IN const TUsbMcsSaveInfo &tMcsInfo     [in]    MCS保存信息
         IN const TUsbNmsSaveInfo &tNmsInfo     [in]    NMS保存信息
         IN const TUsbPcmtSaveInfo &tPcmtInfo   [in]    PCMT保存信息
         IN const TUsbVosSaveInfo &tVosInfo     [in]    VOS保存信息
注    意:错误码用GetErrorDescription解释
返 回 值:保存成功: 0; 保存失败: 错误码
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2006/10/12  1.0     王昊    创建
=============================================================================*/
u32 CUsbImportLicence::SaveRight(IN LPCSTR lptrReaderName,
                                 IN const TUsbMcsSaveInfo &tMcsInfo,
                                 IN const TUsbNmsSaveInfo &tNmsInfo,
                                 IN const TUsbPcmtSaveInfo &tPcmtInfo,
                                 IN const TUsbVosSaveInfo &tVosInfo)
{
    HKHANDLE hCard = NULL;
    u32 dwStatus = 0;

    //检测状态
    u32 dwRet = HK_GetDevState( lptrReaderName, &dwStatus );
    if ( dwRet != 0 )
    {
        return dwRet;
    }
    else if ( dwStatus != HGS_STATE_PRESENT )
    {
        return HKI_ERR_DEV_NOTFOUND;
    }

    //连接
    dwRet = HK_ConnectDev( const_cast<s8*>(lptrReaderName), &hCard );
    if ( dwRet != 0 )
    {
        return dwRet;
    }

    //独占
    dwRet = HK_BeginTransaction( hCard );
    if ( dwRet != 0 )
    {
        HK_DisconnectDev( hCard );
        return dwRet;
    }

    do
    {
        //权限校验
        dwRet = HK_VerifyOfficerPIN( hCard, DEFAULT_USBKEY_SO_PIN );
        if ( dwRet != 0 )
        {
            break;
        }

        //保存版本
        dwRet = SaveVersion( hCard );
        if ( dwRet != 0 )
        {
            break;
        }

        //保存信息
        dwRet = SaveData( hCard, enumUsbRightMCS,
                          reinterpret_cast<const u8*>(&tMcsInfo),
                          sizeof (tMcsInfo) );
        if ( dwRet != 0 )
        {
            break;
        }
        dwRet = SaveData( hCard, enumUsbRightPCMT,
                          reinterpret_cast<const u8*>(&tPcmtInfo),
                          sizeof (tPcmtInfo) );
        if ( dwRet != 0 )
        {
            break;
        }
        dwRet = SaveData( hCard, enumUsbRightNMS,
                          reinterpret_cast<const u8*>(&tNmsInfo),
                          sizeof (tNmsInfo) );
        if ( dwRet != 0 )
        {
            break;
        }
        dwRet = SaveData( hCard, enumUsbRightVOS,
                          reinterpret_cast<const u8*>(&tVosInfo),
                          sizeof (tVosInfo) );
        if ( dwRet != 0 )
        {
            break;
        }

    } while ( FALSE );

    //解除独占
    u32 dwEnd = HK_EndTransaction( hCard );
    if ( dwEnd != 0 && dwRet == 0 )
    {
        dwRet = dwEnd;
    }
    //断开连接
    u32 dwDisconnect = HK_DisconnectDev( hCard );
    hCard = NULL;
    if ( dwDisconnect != 0 && dwRet == 0 )
    {
        dwRet = dwDisconnect;
    }

    return dwRet;
}

/*=============================================================================
函 数 名:ReadRight
功    能:读取授权信息
参    数:IN LPCSTR lptrReaderName               [in]    读卡器名
         OUT LPSTR lptrVersion                  [out]   版本信息
         OUT TUsbMcsSaveInfo &tMcsInfo          [out]   MCS授权信息
         OUT TUsbNmsSaveInfo &tNmsInfo          [out]   NMS授权信息
         OUT TUsbPcmtSaveInfo &tPcmtInfo        [out]   PCMT授权信息
         OUT TUsbVosSaveInfo &tVosInfo          [out]   VOS授权信息
注    意:错误码用GetErrorDescription解释
返 回 值:读取成功: 0; 读取失败: 错误码
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2006/10/12  1.0     王昊    创建
=============================================================================*/
u32 CUsbImportLicence::ReadRight(IN LPCSTR lptrReaderName,
                                 OUT LPSTR lptrVersion,
                                 OUT TUsbMcsSaveInfo &tMcsInfo,
                                 OUT TUsbNmsSaveInfo &tNmsInfo,
                                 OUT TUsbPcmtSaveInfo &tPcmtInfo,
                                 OUT TUsbVosSaveInfo &tVosInfo)
{
    HKHANDLE hCard = NULL;
    u32 dwStatus = 0;

    //检测状态
    u32 dwRet = HK_GetDevState( lptrReaderName, &dwStatus );
    if ( dwRet != 0 )
    {
        return dwRet;
    }
    else if ( dwStatus != HGS_STATE_PRESENT )
    {
        return HKI_ERR_DEV_NOTFOUND;
    }

    //连接
    dwRet = HK_ConnectDev( const_cast<s8*>(lptrReaderName), &hCard );
    if ( dwRet != 0 )
    {
        return dwRet;
    }

    //独占
    dwRet = HK_BeginTransaction( hCard );
    if ( dwRet != 0 )
    {
        HK_DisconnectDev( hCard );
        return dwRet;
    }

    do
    {
        //权限校验
        dwRet = HK_VerifyOfficerPIN( hCard, DEFAULT_USBKEY_SO_PIN );
        if ( dwRet != 0 )
        {
            break;
        }

        //版本
        dwRet = ReadVersion( hCard, lptrVersion );
        if ( dwRet != 0 )
        {
            break;
        }

        //数据
        s32 nBufLen = sizeof (tMcsInfo);
        dwRet = ReadData( hCard, enumUsbRightMCS,
                          reinterpret_cast<u8*>(&tMcsInfo),
                          nBufLen );
        if ( dwRet != 0 )
        {
            break;
        }
        nBufLen = sizeof (tPcmtInfo);
        dwRet = ReadData( hCard, enumUsbRightPCMT,
                          reinterpret_cast<u8*>(&tPcmtInfo),
                          nBufLen );
        if ( dwRet != 0 )
        {
            break;
        }
        nBufLen = sizeof (tNmsInfo);
        dwRet = ReadData( hCard, enumUsbRightNMS,
                          reinterpret_cast<u8*>(&tNmsInfo),
                          nBufLen );
        if ( dwRet != 0 )
        {
            break;
        }
        nBufLen = sizeof (tVosInfo);
        dwRet = ReadData( hCard, enumUsbRightVOS,
                          reinterpret_cast<u8*>(&tVosInfo),
                          nBufLen );
        if ( dwRet != 0 )
        {
            break;
        }

    } while ( FALSE );

    //解除独占
    u32 dwEnd = HK_EndTransaction( hCard );
    if ( dwEnd != 0 && dwRet == 0 )
    {
        dwRet = dwEnd;
    }
    //断开连接
    u32 dwDisconnect = HK_DisconnectDev( hCard );
    hCard = NULL;
    if ( dwDisconnect != 0 && dwRet == 0 )
    {
        dwRet = dwDisconnect;
    }

    return dwRet;
}
