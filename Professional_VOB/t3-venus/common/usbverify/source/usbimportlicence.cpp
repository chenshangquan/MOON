/*=============================================================================
ģ   ��   ��: USB-KEY����
��   ��   ��: UsbImportLicence.cpp
�� ��  �� ��: UsbImportLicence.h
�ļ�ʵ�ֹ���: USB��Ȩ����
��        ��: ���
��        ��: V4.0  Copyright(C) 2006-2006 Kedacom, All rights reserved.
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���      �޸�����
2006/10/11  1.0     ���        ����
=============================================================================*/

// UsbImportLicence.cpp: implementation of the CUsbImportLicence class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UsbImportLicence.h"
#include "hkerror.h"
#include <stdio.h>

/*=============================================================================
�� �� ��:SetTag
��    ��:���ñ�ǩ��
��    ��:IN LPCSTR lptrTag                      [in]    ��ǩ��
ע    ��:��
�� �� ֵ:��
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2006/10/11  1.0     ���    ����
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
�� �� ��:SetSerialNo
��    ��:�������к�
��    ��:IN u8 *pbySerialNo                     [in]    ���к�
ע    ��:�������к�Ϊ16�����ڴ�
�� �� ֵ:��
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2006/10/11  1.0     ���    ����
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
�� �� ��:SetDeviceCallBack
��    ��:�����豸״̬�ص�����
��    ��:IN LPCSTR lptrReaderName               [in]    ��������
         IN TUsbVerifyCallBack pFuncOnCallBack  [in]    ����ص�����
         IN TUsbVerifyCallBack pFuncOffCallBack [in]    �γ��ص�����
         IN void *pCBData                       [in]    �ص�����
ע    ��:��������GetErrorDescription����
�� �� ֵ:���óɹ�: 0; ����ʧ��: ������
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2006/10/11  1.0     ���    ����
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
�� �� ��:FormatDevice
��    ��:��ʽ���豸
��    ��:IN LPCSTR lptrReaderName               [in]    ��������
ע    ��:��������GetErrorDescription����
�� �� ֵ:��ʽ���ɹ�: 0; ��ʽ��ʧ��: ������
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2006/10/11  1.0     ���    ����
=============================================================================*/
u32 CUsbImportLicence::FormatDevice(IN LPCSTR lptrReaderName)
{
    HKHANDLE hCard = NULL;
    u32 dwStatus = 0;

    //���״̬
    u32 dwRet = HK_GetDevState( lptrReaderName, &dwStatus );
    if ( dwRet != 0 )
    {
        return dwRet;
    }
    else if ( dwStatus != HGS_STATE_PRESENT )
    {
        return HKI_ERR_DEV_NOTFOUND;
    }

    //����
    dwRet = HK_ConnectDev( const_cast<s8*>(lptrReaderName), &hCard );
    if ( dwRet != 0 )
    {
        return dwRet;
    }

    //��ռ
    dwRet = HK_BeginTransaction( hCard );
    if ( dwRet != 0 )
    {
        HK_DisconnectDev( hCard );
        return dwRet;
    }

    do
    {
        //����ԭ������
        dwRet = HK_Erase( hCard, DEFAULT_USBKEY_SO_PIN );
//        if ( dwRet != 0 )
//        {
//            break;
//        }

        //��ʽ��
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

    //�����ռ
    u32 dwEnd = HK_EndTransaction( hCard );
    if ( dwEnd != 0 && dwRet == 0 )
    {
        dwRet = dwEnd;
    }
    //�Ͽ�����
    u32 dwDisconnect = HK_DisconnectDev( hCard );
    hCard = NULL;
    if ( dwDisconnect != 0 && dwRet == 0 )
    {
        dwRet = dwDisconnect;
    }

    return dwRet;
}

/*=============================================================================
�� �� ��:GetDeviceInfo
��    ��:��ȡ�豸��Ϣ
��    ��:IN LPCSTR lptrReaderName               [in]    ��������
         OUT TUsbDeviceInfo &tInfo              [out]   �豸��Ϣ
ע    ��:��������GetErrorDescription����
�� �� ֵ:��ȡ�ɹ�: 0; ��ȡʧ��: ������
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2006/10/11  1.0     ���    ����
=============================================================================*/
u32 CUsbImportLicence::GetDeviceInfo(IN LPCSTR lptrReaderName,
                                     OUT TUsbDeviceInfo &tInfo)
{
    HKHANDLE hCard = NULL;
    u32 dwStatus = 0;

    tInfo.Clear();

    //���״̬
    u32 dwRet = HK_GetDevState( lptrReaderName, &dwStatus );
    if ( dwRet != 0 )
    {
        return dwRet;
    }
    else if ( dwStatus != HGS_STATE_PRESENT )
    {
        return HKI_ERR_DEV_NOTFOUND;
    }

    //����
    dwRet = HK_ConnectDev( const_cast<s8*>(lptrReaderName), &hCard );
    if ( dwRet != 0 )
    {
        return dwRet;
    }

    //��ռ
    dwRet = HK_BeginTransaction( hCard );
    if ( dwRet != 0 )
    {
        HK_DisconnectDev( hCard );
        return dwRet;
    }

    do
    {
        s8 szTag[MAXLEN_USBKEY_DEVICE_TAG] = {0};   //�豸��ǩ��
        u8 abySerialNo[HK_SERIAL_NUM_LEN] = {0};    //�豸���к�
        u32 dwFreeSpace = 0;                        //ʣ��ռ�

        //��ȡ��ǩ��
        dwRet = HK_GetDeviceTag( hCard, szTag );
        if ( dwRet != 0 )
        {
            break;
        }

        //��ȡ���к�
        dwRet = HK_GetSerialNum( hCard, abySerialNo );
        if ( dwRet != 0 )
        {
            break;
        }

        //��ȡʣ��ռ�
        dwRet = HK_GetFreeSize( hCard, &dwFreeSpace );
        if ( dwRet != 0 )
        {
            break;
        }

        //�����������
        tInfo.SetTag( szTag );
        tInfo.SetSerialNo( abySerialNo );
        tInfo.SetUsbFreeSpace( dwFreeSpace );

    } while ( FALSE );

    //�����ռ
    u32 dwEnd = HK_EndTransaction( hCard );
    if ( dwEnd != 0 && dwRet == 0 )
    {
        dwRet = dwEnd;
    }
    //�Ͽ�����
    u32 dwDisconnect = HK_DisconnectDev( hCard );
    hCard = NULL;
    if ( dwDisconnect != 0 && dwRet == 0 )
    {
        dwRet = dwDisconnect;
    }

    return dwRet;
}

/*=============================================================================
�� �� ��:SaveRight
��    ��:������Ȩ��Ϣ
��    ��:IN LPCSTR lptrReaderName               [in]    ��������
         IN const TUsbMcsSaveInfo &tMcsInfo     [in]    MCS������Ϣ
         IN const TUsbNmsSaveInfo &tNmsInfo     [in]    NMS������Ϣ
         IN const TUsbPcmtSaveInfo &tPcmtInfo   [in]    PCMT������Ϣ
         IN const TUsbVosSaveInfo &tVosInfo     [in]    VOS������Ϣ
ע    ��:��������GetErrorDescription����
�� �� ֵ:����ɹ�: 0; ����ʧ��: ������
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2006/10/12  1.0     ���    ����
=============================================================================*/
u32 CUsbImportLicence::SaveRight(IN LPCSTR lptrReaderName,
                                 IN const TUsbMcsSaveInfo &tMcsInfo,
                                 IN const TUsbNmsSaveInfo &tNmsInfo,
                                 IN const TUsbPcmtSaveInfo &tPcmtInfo,
                                 IN const TUsbVosSaveInfo &tVosInfo)
{
    HKHANDLE hCard = NULL;
    u32 dwStatus = 0;

    //���״̬
    u32 dwRet = HK_GetDevState( lptrReaderName, &dwStatus );
    if ( dwRet != 0 )
    {
        return dwRet;
    }
    else if ( dwStatus != HGS_STATE_PRESENT )
    {
        return HKI_ERR_DEV_NOTFOUND;
    }

    //����
    dwRet = HK_ConnectDev( const_cast<s8*>(lptrReaderName), &hCard );
    if ( dwRet != 0 )
    {
        return dwRet;
    }

    //��ռ
    dwRet = HK_BeginTransaction( hCard );
    if ( dwRet != 0 )
    {
        HK_DisconnectDev( hCard );
        return dwRet;
    }

    do
    {
        //Ȩ��У��
        dwRet = HK_VerifyOfficerPIN( hCard, DEFAULT_USBKEY_SO_PIN );
        if ( dwRet != 0 )
        {
            break;
        }

        //����汾
        dwRet = SaveVersion( hCard );
        if ( dwRet != 0 )
        {
            break;
        }

        //������Ϣ
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

    //�����ռ
    u32 dwEnd = HK_EndTransaction( hCard );
    if ( dwEnd != 0 && dwRet == 0 )
    {
        dwRet = dwEnd;
    }
    //�Ͽ�����
    u32 dwDisconnect = HK_DisconnectDev( hCard );
    hCard = NULL;
    if ( dwDisconnect != 0 && dwRet == 0 )
    {
        dwRet = dwDisconnect;
    }

    return dwRet;
}

/*=============================================================================
�� �� ��:ReadRight
��    ��:��ȡ��Ȩ��Ϣ
��    ��:IN LPCSTR lptrReaderName               [in]    ��������
         OUT LPSTR lptrVersion                  [out]   �汾��Ϣ
         OUT TUsbMcsSaveInfo &tMcsInfo          [out]   MCS��Ȩ��Ϣ
         OUT TUsbNmsSaveInfo &tNmsInfo          [out]   NMS��Ȩ��Ϣ
         OUT TUsbPcmtSaveInfo &tPcmtInfo        [out]   PCMT��Ȩ��Ϣ
         OUT TUsbVosSaveInfo &tVosInfo          [out]   VOS��Ȩ��Ϣ
ע    ��:��������GetErrorDescription����
�� �� ֵ:��ȡ�ɹ�: 0; ��ȡʧ��: ������
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2006/10/12  1.0     ���    ����
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

    //���״̬
    u32 dwRet = HK_GetDevState( lptrReaderName, &dwStatus );
    if ( dwRet != 0 )
    {
        return dwRet;
    }
    else if ( dwStatus != HGS_STATE_PRESENT )
    {
        return HKI_ERR_DEV_NOTFOUND;
    }

    //����
    dwRet = HK_ConnectDev( const_cast<s8*>(lptrReaderName), &hCard );
    if ( dwRet != 0 )
    {
        return dwRet;
    }

    //��ռ
    dwRet = HK_BeginTransaction( hCard );
    if ( dwRet != 0 )
    {
        HK_DisconnectDev( hCard );
        return dwRet;
    }

    do
    {
        //Ȩ��У��
        dwRet = HK_VerifyOfficerPIN( hCard, DEFAULT_USBKEY_SO_PIN );
        if ( dwRet != 0 )
        {
            break;
        }

        //�汾
        dwRet = ReadVersion( hCard, lptrVersion );
        if ( dwRet != 0 )
        {
            break;
        }

        //����
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

    //�����ռ
    u32 dwEnd = HK_EndTransaction( hCard );
    if ( dwEnd != 0 && dwRet == 0 )
    {
        dwRet = dwEnd;
    }
    //�Ͽ�����
    u32 dwDisconnect = HK_DisconnectDev( hCard );
    hCard = NULL;
    if ( dwDisconnect != 0 && dwRet == 0 )
    {
        dwRet = dwDisconnect;
    }

    return dwRet;
}
