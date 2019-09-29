/*=============================================================================
ģ   ��   ��: USB-KEY����
��   ��   ��: UsbKey.cpp
�� ��  �� ��: UsbKey.h
�ļ�ʵ�ֹ���: USB��������
��        ��: ���
��        ��: V4.0  Copyright(C) 2006-2006 Kedacom, All rights reserved.
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���      �޸�����
2006/10/11  1.0     ���        ����
=============================================================================*/

// UsbKey.cpp: implementation of the CUsbKey class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "UsbKey.h"
#include "hkerror.h"
#include "kdvencrypt.h"

#define USB_RIGHT_VER           (LPCSTR)"40.30.01.01.20061013"

#ifndef DEL_PTR
#define DEL_PTR(p)          if ( p != NULL ) { delete p; p = NULL; }
#endif

#ifndef DEL_PTR_ARRAY
#define DEL_PTR_ARRAY(p)    if ( p != NULL ) { delete [] p; p = NULL; }
#endif

#pragma comment(lib, "hkapi.lib")

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUsbKey::CUsbKey()
{

}

CUsbKey::~CUsbKey()
{

}

/*=============================================================================
�� �� ��:EnumReaders
��    ��:ö�����ж�������
��    ��:OUT s8 aaszAllReaders[][]                  [out]   ���ж�������, ��0x00�ָ�
         OUT s32 &nReaderNum                        [out]   ����������
ע    ��:��������GetErrorDescription����
�� �� ֵ:��ȡ�ɹ�: 0; ��ȡʧ��: ������
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2006/10/11  1.0     ���    ����
=============================================================================*/
u32 CUsbKey::EnumReaders(OUT s8 aaszAllReaders[MAXLEN_USBKEY_READER_NUM][MAXLEN_USBKEY_READER_NAME],
                         OUT s32 &nReaderNum)
{
    u32 dwReadersNameLen = 0;
    u32 dwReaderNum = 0;
    //��ȡ���ж��������ֳ���
    u32 dwRet = HK_ListReaders( NULL, &dwReadersNameLen, &dwReaderNum );
    if ( dwRet != 0 )
    {
        return dwRet;
    }

    LPSTR lptrReadersName = new s8 [dwReadersNameLen];
    memset( lptrReadersName, 0, dwReadersNameLen * sizeof (s8) );

    //��ȡ���ж�������
    dwRet = HK_ListReaders( lptrReadersName, &dwReadersNameLen, &dwReaderNum );
    if ( dwRet != 0 )
    {
        DEL_PTR_ARRAY(lptrReadersName);
        return dwRet;
    }

    s32 nIndex = 0;
    nReaderNum = 0;
    while ( 0x00 != lptrReadersName[nIndex]
            && nReaderNum < MAXLEN_USBKEY_READER_NUM )
    {
        strncpy( aaszAllReaders[nReaderNum], &lptrReadersName[nIndex],
                 MAXLEN_USBKEY_READER_NAME - 1 );
        aaszAllReaders[nReaderNum ++][MAXLEN_USBKEY_READER_NAME - 1] = '\0';
        nIndex += _tcslen( &lptrReadersName[nIndex] ) + 1;
    }

    DEL_PTR_ARRAY(lptrReadersName);
    return 0;
}

/*=============================================================================
�� �� ��:SaveData
��    ��:��������
��    ��:IN HKHANDLE hCard                      [in]    ���������
         IN EMUsbRight emRight                  [in]    ģ��
         IN const u8 *pbyBuf                    [in]    ��������
         IN s32 nBufLen                         [in]    ���ݳ���
ע    ��:��������GetErrorDescription����; ����ǰ��򿪶�����, ����ռ�豸
         ���ú�, ������ռ, ���ر��豸
�� �� ֵ:����ɹ�: 0; ����ʧ��: ������
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2006/10/12  1.0     ���    ����
=============================================================================*/
u32 CUsbKey::SaveData(IN HKHANDLE hCard, IN EMUsbRight emRight,
                      IN const u8 *pbyBuf, IN s32 nBufLen)
{
    u8 abyData[DEFAULT_USBKEY_FILESIZE] = {0};
    u8 abyBuf[DEFAULT_USBKEY_FILESIZE] = {0};

    memset( abyBuf, 0, sizeof (abyBuf) );
    memcpy( abyBuf, pbyBuf, nBufLen );
    //���ݼ���
    KdvAES( DEFAULT_USBKEY_AES_KEY, strlen( DEFAULT_USBKEY_AES_KEY ),
            DEFAULT_USBKEY_AES_MODE, qfDES_encrypt, DEFAULT_USBKEY_AES_INITKEY,
            abyBuf, DEFAULT_USBKEY_FILESIZE, abyData );

    //���ظ�Ŀ¼
    u32 dwRet = HK_BacktoMDir( hCard );
    if ( dwRet != 0 )
    {
        return dwRet;
    }

    HK_DIRINFO tDir = {0};
    tDir.ucCreateAccess = HK_SUPER_PIN_ACCESS;
    tDir.ucDeleteAccess = HK_SUPER_PIN_ACCESS;
    tDir.ucReserved1 = 0;
    tDir.ucReserved2 = 0;

    //�򿪸�Ŀ¼
    dwRet = HK_OpenDir( hCard, DEFAULT_USBKEY_DIRID );
    if ( dwRet != 0 )   //��ʧ��, ������Ŀ¼
    {
        tDir.ulID = DEFAULT_USBKEY_DIRID;
        dwRet = HK_CreateDir( hCard, &tDir );
        if ( dwRet != 0 )
        {
            return dwRet;
        }

        dwRet = HK_OpenDir( hCard, DEFAULT_USBKEY_DIRID );
        if ( dwRet != 0 )
        {
            return dwRet;
        }
    }

    //ɾ���ļ���Ȼ�󴴽�������
    u32 dwFileID = 0;
    switch ( emRight )
    {
    case enumUsbRightMCS:
        dwFileID = USBKEY_MCS_FILEID;
        break;
    case enumUsbRightNMS:
        dwFileID = USBKEY_NMS_FILEID;
        break;
    case enumUsbRightPCMT:
        dwFileID = USBKEY_PCMT_FILEID;
        break;
    case enumUsbRightVOS:
    default:
        dwFileID = USBKEY_VOS_FILEID;
        break;
    }
    HK_DeleteFile( hCard, dwFileID );

    //�����ļ�
    HK_FILEINFO tFile = {0};
    tFile.ucFileType = HK_FILETYPE_BINARY;
    tFile.ucReadAccess = HK_SUPER_PIN_ACCESS;
    tFile.ucReserved1 = 0;
    tFile.ucReserved2 = 0;
    tFile.ucWriteAccess = HK_SUPER_PIN_ACCESS;
    tFile.ulFileSize = DEFAULT_USBKEY_FILESIZE;
    tFile.ulID = dwFileID;
    dwRet = HK_CreateFile( hCard, &tFile );
    if ( dwRet != 0 )
    {
        return dwRet;
    }

    //���ļ�
    dwRet = HK_OpenFile( hCard, dwFileID );
    if ( dwRet != 0 )
    {
        return dwRet;
    }

    //д������
    u32 dwBufLen = DEFAULT_USBKEY_FILESIZE;
    u32 dwWriteLen = DEFAULT_USBKEY_FILESIZE;
    dwRet = HK_WriteFile( hCard, 0x0000, abyData, dwBufLen, &dwWriteLen );
    if ( dwRet != 0 )
    {
        return dwRet;
    }
    else if ( dwWriteLen != dwBufLen )
    {
        return HKI_WRITE_DATA_LEN_ERROR;
    }

    return dwRet;
}

/*=============================================================================
�� �� ��:ReadData
��    ��:��ȡ����
��    ��:IN HKHANDLE hCard                      [in]    ���������
         IN EMUsbRight emRight                  [in]    ģ��
         OUT const u8 *pbyBuf                   [out]   ����
         IN OUT s32 nBufLen                     [in]    ������󳤶�
ע    ��:��������GetErrorDescription����; ����ǰ��򿪶�����, ����ռ�豸
         ���ú�, ������ռ, ���ر��豸
�� �� ֵ:��ȡ�ɹ�: 0; ��ȡʧ��: ������
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2006/10/12  1.0     ���    ����
=============================================================================*/
u32 CUsbKey::ReadData(IN HKHANDLE hCard, IN EMUsbRight emRight,
                      OUT u8 *pbyBuf, IN OUT s32 nBufLen)
{
    u8 abyData[DEFAULT_USBKEY_FILESIZE] = {0};
    u32 dwDataLen = DEFAULT_USBKEY_FILESIZE;

    //���ظ�Ŀ¼
    u32 dwRet = HK_BacktoMDir( hCard );
    if ( dwRet != 0 )
    {
        return dwRet;
    }

    //�򿪸�Ŀ¼
    dwRet = HK_OpenDir( hCard, DEFAULT_USBKEY_DIRID );
    if ( dwRet != 0 )   //��ʧ��, ������Ŀ¼
    {
        return dwRet;
    }


    u32 dwFileID = 0;
    switch ( emRight )
    {
    case enumUsbRightMCS:
        dwFileID = USBKEY_MCS_FILEID;
        break;
    case enumUsbRightNMS:
        dwFileID = USBKEY_NMS_FILEID;
        break;
    case enumUsbRightPCMT:
        dwFileID = USBKEY_PCMT_FILEID;
        break;
    case enumUsbRightVOS:
    default:
        dwFileID = USBKEY_VOS_FILEID;
        break;
    }

    //���ļ�
    dwRet = HK_OpenFile( hCard, dwFileID );
    if ( dwRet != 0 )
    {
        return dwRet;
    }

    //��ȡ�ļ�
    u32 dwReadLen = DEFAULT_USBKEY_FILESIZE;
    dwRet = HK_ReadFile( hCard, 0x0000, abyData, dwDataLen, &dwReadLen );
    if ( dwRet != 0 )
    {
        return dwRet;
    }


    //���ݽ���
    u8 abyBuf[DEFAULT_USBKEY_FILESIZE] = {0};
    memset( abyBuf, 0, sizeof (abyBuf) );
    memcpy( abyBuf, abyData, dwReadLen );
    u8 abyOutData[DEFAULT_USBKEY_FILESIZE] = {0};

    KdvAES( DEFAULT_USBKEY_AES_KEY, strlen( DEFAULT_USBKEY_AES_KEY ),
            DEFAULT_USBKEY_AES_MODE, qfDES_decrypt, DEFAULT_USBKEY_AES_INITKEY,
            abyBuf, DEFAULT_USBKEY_FILESIZE, abyOutData );
    memcpy( pbyBuf, abyOutData, nBufLen );

    return dwRet;
}

/*=============================================================================
�� �� ��:SaveVersion
��    ��:����汾��
��    ��:IN HKHANDLE hCard                      [in]    ���������
ע    ��:��������GetErrorDescription����; ����ǰ��򿪶�����, ����ռ�豸
         ���ú�, ������ռ, ���ر��豸
�� �� ֵ:����ɹ�: 0; ����ʧ��: ������
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2006/10/12  1.0     ���    ����
=============================================================================*/
u32 CUsbKey::SaveVersion(IN HKHANDLE hCard)
{
    //���ظ�Ŀ¼
    u32 dwRet = HK_BacktoMDir( hCard );
    if ( dwRet != 0 )
    {
        return dwRet;
    }

    HK_DIRINFO tDir = {0};
    tDir.ucCreateAccess = HK_SUPER_PIN_ACCESS;
    tDir.ucDeleteAccess = HK_SUPER_PIN_ACCESS;
    tDir.ucReserved1 = 0;
    tDir.ucReserved2 = 0;

    //�򿪸�Ŀ¼
    dwRet = HK_OpenDir( hCard, DEFAULT_USBKEY_DIRID );
    if ( dwRet != 0 )   //��ʧ��, ������Ŀ¼
    {
        tDir.ulID = DEFAULT_USBKEY_DIRID;
        dwRet = HK_CreateDir( hCard, &tDir );
        if ( dwRet != 0 )
        {
            return dwRet;
        }

        dwRet = HK_OpenDir( hCard, DEFAULT_USBKEY_DIRID );
        if ( dwRet != 0 )
        {
            return dwRet;
        }
    }

    //ɾ���ļ���Ȼ�󴴽�������
    HK_DeleteFile( hCard, USBKEY_VERSION_FILEID );

    //�����ļ�
    HK_FILEINFO tFile = {0};
    tFile.ucFileType = HK_FILETYPE_BINARY;
    tFile.ucReadAccess = HK_SUPER_PIN_ACCESS;
    tFile.ucReserved1 = 0;
    tFile.ucReserved2 = 0;
    tFile.ucWriteAccess = HK_SUPER_PIN_ACCESS;
    tFile.ulFileSize = DEFAULT_USBKEY_FILESIZE;
    tFile.ulID = USBKEY_VERSION_FILEID;
    dwRet = HK_CreateFile( hCard, &tFile );
    if ( dwRet != 0 )
    {
        return dwRet;
    }

    //���ļ�
    dwRet = HK_OpenFile( hCard, USBKEY_VERSION_FILEID );
    if ( dwRet != 0 )
    {
        return dwRet;
    }

    //д������
    u32 dwBufLen = strlen(CURRENT_VERSION) + 1;
    u32 dwWriteLen = dwBufLen;
    dwRet = HK_WriteFile( hCard, 0x0000,
                          reinterpret_cast<u8*>(const_cast<s8*>(CURRENT_VERSION)),
                          dwBufLen, &dwWriteLen );
    if ( dwRet != 0 )
    {
        return dwRet;
    }
    else if ( dwWriteLen != dwBufLen )
    {
        return HKI_WRITE_DATA_LEN_ERROR;
    }

    return dwRet;
}

/*=============================================================================
�� �� ��:ReadVersion
��    ��:��ȡ�汾��
��    ��:IN HKHANDLE hCard                      [in]    ���������
         OUT LPSTR lptrVersion                  [out]   �汾��
ע    ��:��������GetErrorDescription����; ����ǰ��򿪶�����, ����ռ�豸
         ���ú�, ������ռ, ���ر��豸
�� �� ֵ:��ȡ�ɹ�: 0; ��ȡʧ��: ������
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2006/10/12  1.0     ���    ����
=============================================================================*/
u32 CUsbKey::ReadVersion(IN HKHANDLE hCard, OUT LPSTR lptrVersion)
{
    u8 abyData[DEFAULT_USBKEY_FILESIZE] = {0};
    u32 dwDataLen = DEFAULT_USBKEY_FILESIZE;

    //���ظ�Ŀ¼
    u32 dwRet = HK_BacktoMDir( hCard );
    if ( dwRet != 0 )
    {
        return dwRet;
    }

    //�򿪸�Ŀ¼
    dwRet = HK_OpenDir( hCard, DEFAULT_USBKEY_DIRID );
    if ( dwRet != 0 )   //��ʧ��, ������Ŀ¼
    {
        return dwRet;
    }

    //���ļ�
    dwRet = HK_OpenFile( hCard, USBKEY_VERSION_FILEID );
    if ( dwRet != 0 )
    {
        return dwRet;
    }

    //��ȡ�ļ�
    u32 dwReadLen = dwDataLen;
    dwRet = HK_ReadFile( hCard, 0x0000, abyData, dwDataLen, &dwReadLen );
    if ( dwRet != 0 )
    {
        return dwRet;
    }

    //���ݽ���
    strcpy( lptrVersion, reinterpret_cast<s8*>(abyData) );

    return dwRet;
}

/*=============================================================================
�� �� ��:GetWorkingReaders
��    ��:��ȡ��ǰ���п��ö�����
��    ��:OUT s8 aaszReaders[][]                         [out]   ��ǰ���п��ö�������
         OUT s32 &nReaderNum                            [out]   ���ö���������
ע    ��:��������GetErrorDescription����
�� �� ֵ:��ȡ�ɹ�: 0; ��ȡʧ��: ������
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2006/10/11  1.0     ���    ����
=============================================================================*/
u32 CUsbKey::GetWorkingReaders(OUT s8 aaszReaders[MAXLEN_USBKEY_READER_NUM][MAXLEN_USBKEY_READER_NAME],
                               OUT s32 &nReaderNum)
{
    s8 aaszAllReaders[MAXLEN_USBKEY_READER_NUM][MAXLEN_USBKEY_READER_NAME];
    s32 nAllReaders = MAXLEN_USBKEY_READER_NUM;
    memset( aaszAllReaders, 0, sizeof (aaszAllReaders) );

    //ö�������豸
    u32 dwRet = EnumReaders( aaszAllReaders, nAllReaders );
    if ( dwRet != 0 )
    {
        return dwRet;
    }

    nReaderNum = 0;
    for ( s32 nIndex = 0; nIndex < nAllReaders; nIndex ++ )
    {
        u32 dwDeviceStatus = 0;
        dwRet = HK_GetDevState( aaszAllReaders[nIndex], &dwDeviceStatus );
        if ( dwRet != 0 )
        {
            return dwRet;
        }

        if ( HGS_STATE_PRESENT == dwDeviceStatus )
        {
            memcpy( aaszReaders[nReaderNum ++], aaszAllReaders[nIndex],
                    MAXLEN_USBKEY_READER_NAME );
        }
    }

    return nReaderNum > 0 ? 0 : HKI_ERR_DEV_BYNAME;
}

/*=============================================================================
�� �� ��:GetErrorDescription
��    ��:��ȡ��������
��    ��:IN TUsbVerifyCallBack pFuncCallBack    [in]    �ص�����
         IN u8 byLanguage                       [in]    ��������(0: ����; 1: Ӣ��)
ע    ��:����ֻ������
�� �� ֵ:��������
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2006/10/11  1.0     ���    ����
=============================================================================*/
LPCTSTR CUsbKey::GetErrorDescription(IN u32 dwErrCode, IN u8 byLanguage /* = 0 */)
{
    switch ( dwErrCode )
    {
    case 0:
        return _T("�ɹ�");
    case HKI_ERR_DEV_INDEX:
        return _T("�豸�����ų���");
    case HKI_ERR_DEV_INUSE:
        return _T("���豸�Ѵ�������״̬����ȴ������³�������");
    case HKI_ERR_DEV_READERLEN:
        return _T("ȡ�豸����ʱ�����豸������");
    case HKI_ERR_DEV_INVALIDCTX:
        return _T("�ͷ��豸ʱ��ָ�����豸�����Ч���������ѵ��ù�HKDisconnectDev����");
    case HKI_ERR_DEV_BYNAME:
        return _T("�Ҳ���ָ�����豸������豸������");
    case HKI_ERR_DEV_INVALIDINDEX:
        return _T("��Ч���豸������");
    case HKI_ERR_DEV_NOTFOUND:
        return _T("δ���ָ��豸");
    case HKI_ERR_DEV_ATR_LENGTH:
        return _T("ȡ���к�ʱ������ATR�ĳ�������ӦΪ2-32�ֽڡ�");
    case HKI_ERR_DEV_ATR_FLAG:
        return _T("ȡ���к�ʱ������ATR�����ֽڱ�־����ȷ��ӦΪ3B��3F");
    case HKI_ERR_DEV_ATR_VALUE:
        return _T("ȡ���к�ʱ������ʶ��ATR���ݵĸ�ʽ������û���ҵ�0x8888��־");
    case HKI_ERR_DEV_HID_CRC:
        return _T("HID�豸ͨ��ʱ������żУ�����");
    case HKI_ERR_DEV_HID_TIMEOUT:
        return _T("HID�豸ͨ��ʱ������ʱ����");
    case HKI_ERR_DEV_HID_RESET:
        return _T("HID�豸ͨ��ʱ������Ƭ��λ��ϢTS��BCC����");
    case HKI_ERR_DEV_HID_LEN:
        return _T("HID�豸ͨ��ʱ�������ȴ���");
    case HKI_ERR_DEV_HID_BCC:
        return _T("HID�豸ͨ���У���������͵�����ϵ��У�����");
    case HKI_ERR_DEV_HID_WRITE:
        return _T("HID�豸д��������");
    case HKI_ERR_DEV_HID_READ:
        return _T("HID�豸����������");
    case HKI_ERR_CRYPT_INVALIDPARAM:
        return _T("�����ĺ�����������Чֵ��");
    case HKI_ERR_MEM_NULLPTR:
        return _T("��Ϊ������ָ��Ϊ��");
    case HKI_ERR_MEM_BUFTOOSMALL:
        return _T("������ڴ�ռ䲻��");
    case HKI_ERR_EVT_INVALID:
        return _T("��Ч���豸��δ����¼����");
    case HKI_ERR_MUTEX_OBJHOST:
        return _T("��ǰ�������Ķ�����࣬����ʣ����Դ����");
    case HKI_PIN_LEN_ERROR:
        return _T("����ȴ���");
    case HKI_PIN_RETRY_NUM_ERROR:
        return _T("������������������");
    case HKI_DEVICE_NAME_LEN_ERROR:
        return _T("�豸���ֳ��ȴ���");
    case HKI_FILE_TYPE_ERROR:
        return _T("�ļ����ʹ���");
    case HKI_WRITE_DATA_LEN_ERROR:
        return _T("д������ݳ��ȴ���");
    case HKI_READ_DATA_LEN_ERROR:
        return _T("���������ݳ��ȴ���");
    case HKI_RSA_PADDING_TYPE_ERROR:
        return _T("RSA�������ʹ���");
    case HKI_RSA_DATA_LEN_ERROR:
        return _T("RSA���ݳ��ȴ���");
    case HKI_ACCESS_TYPE_ERROR:
        return _T("Ȩ�����ʹ���");
    case HKI_INPUT_DATA_LEN_ERROR:
        return _T("SSF33/DES�㷨��������ݳ��ȴ��󣬱���Ϊ16/8�ı���");
    case HKI_DEVICE_CMS_DIFFER_ERROR:
        return _T("�豸�������Ĵ�С���豸���Ͳ���");
    case HKI_KEY_LEN_ERROR:
        return _T("SSF33��Կ���ȴ���");
    case HKI_KEY_ID_ERROR:
        return _T("SSF33��ԿID����");
    case HKI_INVALID_PARAM_TYPE:
        return _T("�Ƿ��Ĳ�������");
    case HKI_RET_DATA_LEN_ERROR:
        return _T("�豸���ص����ݳ��ȴ���");
    case HKI_ERROR_NOT_ENOUGH_MEMORY:
        return _T("�ڴ治��");
    case HKI_ENCRYPT_DECRYPT_MODE_ERROR:
        return _T("�ӽ���ģʽ����");
    case HKI_STRTOHEX_INPUT_DATA_ERROR:
        return _T("�ַ�ת�����ݴ���");
    case HKI_NOT_SUPPORT_ERROR:
        return _T("���ܲ�֧��");
    case HKI_FILE_ID_INVALID_ERROR:
        return _T("�ļ�IDȡֵ��Χ���Ϸ�");
    case HKI_PADDING_INVALID_ERROR:
        return _T("���ݵĲ�������");
    case HKI_NOT_SUPPORT_SYM:
        return _T("��֧�ָ��㷨");
    case HK_LENGTH_INVALID_ERROR:
        return _T("д�����ݵĳ��ȴ���");
    case HK_ID_EXIST_ERROR:
        return _T("��ʶ���Ѵ���");
    case HK_NOT_SUPPORT_ERROR:
        return _T("���ܲ�֧��");
    case HK_ID_NOT_FOUND_ERROR:
        return _T("δ�ҵ��ļ�");
    case HK_NOT_ENOUGH_SIZE:
        return _T("�ռ䲻��");
//    case HK_X_TIMES_LEFT:
    case HKI_ERRCODE_BASE + 0x000063C1:
        return _T("У�������󣬻���1�λ���");
    case HKI_ERRCODE_BASE + 0x000063C2:
        return _T("У�������󣬻���2�λ���");
    case HKI_ERRCODE_BASE + 0x000063C3:
        return _T("У�������󣬻���3�λ���");
    case HKI_ERRCODE_BASE + 0x000063C4:
        return _T("У�������󣬻���4�λ���");
    case HKI_ERRCODE_BASE + 0x000063C5:
        return _T("У�������󣬻���5�λ���");
    case HKI_ERRCODE_BASE + 0x000063C6:
        return _T("У�������󣬻���6�λ���");
    case HKI_ERRCODE_BASE + 0x000063C7:
        return _T("У�������󣬻���7�λ���");
    case HKI_ERRCODE_BASE + 0x000063C8:
        return _T("У�������󣬻���8�λ���");
    case HKI_ERRCODE_BASE + 0x000063C9:
        return _T("У�������󣬻���9�λ���");
    case HKI_ERRCODE_BASE + 0x000063CA:
        return _T("У�������󣬻���10�λ���");
    case HKI_ERRCODE_BASE + 0x000063CB:
        return _T("У�������󣬻���11�λ���");
    case HKI_ERRCODE_BASE + 0x000063CC:
        return _T("У�������󣬻���12�λ���");
    case HKI_ERRCODE_BASE + 0x000063CD:
        return _T("У�������󣬻���13�λ���");
    case HKI_ERRCODE_BASE + 0x000063CE:
        return _T("У�������󣬻���14�λ���");
    case HKI_ERRCODE_BASE + 0x000063CF:
        return _T("У�������󣬻���15�λ���");
    case HK_NOT_ACCESS_ERROR:
        return _T("��ȫ����������");
    case HK_PIN_LOCKED_ERROR:
        return _T("�������");
    case HKI_ERR_UNKOWN:
    default:
        return _T("δ֪����");
    }
}
