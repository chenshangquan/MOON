/*=============================================================================
ģ   ��   ��: USB-KEY����
��   ��   ��: UsbVerify.cpp
�� ��  �� ��: UsbVerify.h
�ļ�ʵ�ֹ���: USB��֤
��        ��: ���
��        ��: V4.0  Copyright(C) 2006-2006 Kedacom, All rights reserved.
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���      �޸�����
2006/10/11  1.0     ���        ����
=============================================================================*/

// UsbVerify.cpp: implementation of the CUsbVerify class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UsbVerify.h"
#include "hkerror.h"
#include "kdvencrypt.h"


#define MAX_KEY_VALUE_NUM						100							// �ɶ�ȡ��Key-Value�������
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUsbVerify::CUsbVerify()
{
}

CUsbVerify::~CUsbVerify()
{

}
/*==============================================================================
������    :  GenEncodeData
����      :  ����
�㷨ʵ��  :  
����˵��  :  pOutBuf		���ܺ���ַ���
			 wInBufLen      ���뻺��Ĵ�С
			 pInBuf			�����δ���ܵ��ַ�
			 bDirect        ���� || ����
����ֵ˵��:  
-------------------------------------------------------------------------------
�޸ļ�¼  :  
��  ��       �汾          �޸���          �߶���          �޸ļ�¼
2008-8-18				   ����                             ����
==============================================================================*/

void GenEncodeData(s8 *pOutBuf, u16 wInBufLen, s8 *pInBuf, BOOL32 bDirect)
{
    s8 achIV[MAX_IV_SIZE] = {0};
	
    s8 achKey[32] = {0};
    memset( achKey, 0, sizeof (achKey) );
	strncpy( achKey, KEDA_AES_KEY, strlen(KEDA_AES_KEY) );// ����keyΪ16�ı���
    u16 wKeyLen = strlen(achKey);

    s32 nRet = -1;
	if( bDirect ) // eccrypt 
	{
		nRet = KdvAES( achKey, wKeyLen, MODE_CBC, DIR_ENCRYPT, achIV,
			(u8*)pInBuf, wInBufLen, (u8*)pOutBuf );
	}
	else  // decrypt
	{
		nRet = KdvAES( achKey, wKeyLen, MODE_CBC, DIR_DECRYPT, achIV,
			(u8*)pInBuf, wInBufLen, (u8*)pOutBuf );
	}

	return;
}
/*==============================================================================
������    :  GetKeyValue
����      :  ���Ӵ��л�ȡKey��Value
�㷨ʵ��  :  
����˵��  :  pchBuf          �����ַ���[IN]
			 pchKey          �õ���KEY[OUT]
			 nKeyLen         KEY�ĳ���[OUT]
			 pchValue        Key��ֵ[OUT]
			 nValueLen       Keyֵ�ĳ���[OUT]
����ֵ˵��:  
-------------------------------------------------------------------------------
�޸ļ�¼  :  
��  ��       �汾          �޸���          �߶���          �޸ļ�¼
2008-8-18
==============================================================================*/
u16 GetKeyValue(s8 *pchBuf, s8 *pchKey, s32 &nKeyLen, s8 *pchValue, s32 &nValueLen)
{
	if(NULL == pchBuf || NULL == pchKey || NULL == pchValue) 
	{
		return ERR_LICENSE_INVALID_PARAM;
	}
	u16 wBufLen = strlen(pchBuf);
	if(wBufLen < 3) 
	{
		return ERR_LICENSE_INVALID_PARAM;
	}

	s8 *pchPos = pchBuf;
	s8 *pchToken = NULL;
	s8 achSep[5] = {0};
	memcpy( achSep, (s8*)KEY_VALUE_CONNECTOR,
            strlen(KEY_VALUE_CONNECTOR) + 1 );	// Key��Value�ķָ���

	//key
	pchToken = strtok(pchPos, achSep);
	if(NULL == pchToken) 
	{
		return ERR_LICENSE_INVALID_PARAM;
	}

	u16 wLenKey = strlen(pchToken);
	if(nKeyLen < wLenKey) 
	{
		return ERR_LICENSE_LONG_STRING;
	}
	memcpy(pchKey, pchToken, wLenKey);
	pchKey[wLenKey] = '\0';

	//value
	if(wBufLen - wLenKey - 1 < 1) 
	{
		return ERR_LICENSE_INVALID_PARAM;
	}

	pchPos += wLenKey + 1;
	u16 wLenValue = strlen(pchPos);
	if(nValueLen < wLenValue) 
	{
		return ERR_LICENSE_LONG_STRING;
	}
	memcpy(pchValue, pchPos, wLenValue);
	pchValue[wLenValue] = '\0';

	return SUCCESS_LICENSE;
}


u32 CUsbVerify::ReadVersion(IN HKHANDLE hCard, OUT LPSTR lptrVersion)
{
    u8 abyData[DEFAULT_USBKEY_FILESIZE] = {0};
    u32 dwDataLen						= DEFAULT_USBKEY_FILESIZE;
	s8 achKeyValueContent[512]			= {0};
	s8 achContentBuf[512]				= {0};
	u16 wRet							= SUCCESS_LICENSE;
  	
	s32 nCharPos						= 0;
	s8 *pchToken2						= "NULL";
	s8 *pBuf							= achKeyValueContent;
	s8 achKey[1024]						= {0};
	s8 achValue[1024]					= {0};
	s32 nKeyBuflen						= 1024;
	s32 nValueBuflen					= 1024;

	//���ظ�Ŀ¼
    u32 dwRet = HK_BacktoMDir( hCard );
    if ( dwRet != 0 )
    {
        return dwRet;
    }

    //���ļ�
    dwRet = HK_OpenFile( hCard, 0xEF01 );
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
	strcpy( achContentBuf, reinterpret_cast<s8*>(abyData) );
	u16 wKeyValueLen = ( u16 )dwDataLen;
	GenEncodeData( achKeyValueContent, wKeyValueLen, achContentBuf, FALSE );
	

	//������ֵ

	nCharPos = strcspn(pBuf, "&");
	pchToken2 = strtok(pBuf, "&");

	while (NULL != pchToken2)
	{
		wRet = GetKeyValue(pchToken2, achKey, nKeyBuflen,						// ��ȡKey-Value����Ϣ
					achValue, nValueBuflen);
		if(SUCCESS_LICENSE == wRet) 
		{
			if ( 0 == strcmp( "KEY_LICENSE_TYPE", achKey) )
			{
				strcpy( lptrVersion, achValue );
				break;
			}
		}
 
		pBuf += nCharPos + 1;
 		nCharPos = strcspn(pBuf, "&");
 		pchToken2 = strtok(pBuf, "&");
	}

    return dwRet;
}
BOOL32 CUsbVerify::VerifyPCMT()
{

    s8 aaszReaders[MAXLEN_USBKEY_READER_NUM][MAXLEN_USBKEY_READER_NAME];
    s32 nReaders = MAXLEN_USBKEY_READER_NUM;

    memset( aaszReaders, 0, sizeof (aaszReaders) );
    //��ȡ�������ڹ������豸
    u32 dwRet = GetWorkingReaders( aaszReaders, nReaders );
    if ( dwRet != 0 || nReaders == 0 )
    {
        return FALSE;
    }

    //ѭ�����
    for ( s32 nIndex = 0; nIndex < nReaders; nIndex ++ )
    {
        HKHANDLE    hCard = NULL;
        BOOL32      bOK = FALSE;
        s8          szVersion[64] = {0};
        u8          abyData[DEFAULT_USBKEY_FILESIZE] = {0};
        s32         nDataLen = static_cast<s32>(DEFAULT_USBKEY_FILESIZE);
	

        //���豸
        dwRet = HK_ConnectDev( aaszReaders[nIndex], &hCard );
        if ( dwRet != 0 )
        {
            continue;
        }

        do
        {
            //��ռ
            dwRet = HK_BeginTransaction( hCard );
            if ( dwRet != 0 )
            {
                break;
            }

            //Ȩ��У��
            dwRet = HK_VerifyOfficerPIN( hCard, DEFAULT_USBKEY_SO_PIN );
            if ( dwRet != 0 )
            {
                break;
            }

            //��ȡ����
            dwRet =  ReadVersion( hCard, szVersion );
			if ( dwRet != 0 )
            {
                break;
            }

			s8 szBaseVersion[5] = { 0 };
			s32 nTmep;
			for ( nTmep = 0; nTmep < (s32)strlen(szVersion); nTmep++)
			{
				if ( !isspace( szVersion[nTmep] ) && (strlen( szVersion ) - nTmep) >= 4 )
				{
					strncpy(szBaseVersion, szVersion, 4);	
					break;
				}
			}
			for ( nTmep = 0; nTmep < (s32)strlen(szVersion); nTmep++)
			{
				szBaseVersion[ nTmep ] = toupper(szBaseVersion[ nTmep ]);
			}

			//У��
			if (0 == strcmp(szBaseVersion, "PCMT") )
			{
				bOK = TRUE;
			}
			
        } while ( FALSE );

        //�����ռ
        HK_EndTransaction( hCard );
        //�Ͽ�����
        HK_DisconnectDev( hCard );
        if ( bOK )  //��֤��ȷ
        {
            strncpy( m_szCurReader, aaszReaders[nIndex],
                     MAXLEN_USBKEY_READER_NAME - 1 );
            m_szCurReader[MAXLEN_USBKEY_READER_NAME - 1] = '\0';
            return TRUE;
        }
    }

	return FALSE;
}

/*=============================================================================
�� �� ��:Verify
��    ��:��֤ģ����Ȩ��Ϣ
��    ��:EMUsbRight emUsbRight              [in]    ģ��
ע    ��:DEBUG�²�������Ȩ
�� �� ֵ:��Ȩ��ȷ: TRUE; ����Ȩ����Ȩ����: FALSE
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2006/10/11  1.0     ���    ����
=============================================================================*/
BOOL32 CUsbVerify::Verify(EMUsbRight emUsbRight)
{
#ifdef _DEBUG
    return TRUE;    //DEBUG�²�������Ȩ
#endif

    s8 aaszReaders[MAXLEN_USBKEY_READER_NUM][MAXLEN_USBKEY_READER_NAME];
    s32 nReaders = MAXLEN_USBKEY_READER_NUM;

    memset( aaszReaders, 0, sizeof (aaszReaders) );
    //��ȡ�������ڹ������豸
    u32 dwRet = GetWorkingReaders( aaszReaders, nReaders );
    if ( dwRet != 0 || nReaders == 0 )
    {
        return FALSE;
    }

    //ѭ�����
    for ( s32 nIndex = 0; nIndex < nReaders; nIndex ++ )
    {
        HKHANDLE    hCard = NULL;
        BOOL32      bOK = FALSE;
        s8          szVersion[64] = {0};
        u8          abyData[DEFAULT_USBKEY_FILESIZE] = {0};
        s32         nDataLen = static_cast<s32>(DEFAULT_USBKEY_FILESIZE);

        //���豸
        dwRet = HK_ConnectDev( aaszReaders[nIndex], &hCard );
        if ( dwRet != 0 )
        {
            continue;
        }

        do
        {
            //��ռ
            dwRet = HK_BeginTransaction( hCard );
            if ( dwRet != 0 )
            {
                break;
            }

            //Ȩ��У��
            dwRet = HK_VerifyOfficerPIN( hCard, DEFAULT_USBKEY_SO_PIN );
            if ( dwRet != 0 )
            {
                break;
            }

            //��ȡ����
            dwRet = ReadVersion( hCard, szVersion );
            if ( dwRet != 0 )
            {
                break;
            }
            dwRet = ReadData( hCard, emUsbRight, abyData, nDataLen );
            if ( dwRet != 0 )
            {
                break;
            }

            //��֤
            bOK = VerifyData( szVersion, emUsbRight, abyData, nDataLen );

        } while ( FALSE );

        //�����ռ
        HK_EndTransaction( hCard );
        //�Ͽ�����
        HK_DisconnectDev( hCard );
        if ( bOK )  //��֤��ȷ
        {
            strncpy( m_szCurReader, aaszReaders[nIndex],
                     MAXLEN_USBKEY_READER_NAME - 1 );
            m_szCurReader[MAXLEN_USBKEY_READER_NAME - 1] = '\0';
            return TRUE;
        }
    }

    return FALSE;
}

/*=============================================================================
�� �� ��:SetDeviceCallBack
��    ��:�����豸״̬�ص�����
��    ��:IN TUsbVerifyCallBack pFuncOnCallBack  [in]    ����ص�����
         IN TUsbVerifyCallBack pFuncOffCallBack [in]    �γ��ص�����
         IN void *pCBData                       [in]    �ص�����
ע    ��:��������GetErrorDescription���ͣ�����Verify֮�����
�� �� ֵ:���óɹ�: 0; ����ʧ��: ������
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2006/10/11  1.0     ���    ����
=============================================================================*/
u32 CUsbVerify::SetDeviceCallBack(IN TUsbVerifyCallBack pFuncOnCallBack,
                                  IN TUsbVerifyCallBack pFuncOffCallBack,
                                  IN void *pCBData)
{
#ifdef _DEBUG
    return 0;
#endif

    if ( m_szCurReader[0] == '\0' )
    {
        return HKI_ERR_DEV_BYNAME;
    }

    u32 dwRet = HK_SetDevChgFunc( m_szCurReader, pFuncOnCallBack,
                                  pFuncOffCallBack, pCBData, NULL );
    return dwRet;
}

/*=============================================================================
�� �� ��:VerifyData
��    ��:��֤����
��    ��:IN LPSTR lptrVersion                   [in]    �汾��
         IN EMUsbRight emRight                  [in]    ģ��
         IN const u8 *pbyBuf                    [in]    ��������
         IN s32 nBufLen                         [in]    ���ݳ���
ע    ��:����ǰ��򿪶�����, ����ռ�豸; ���ú�, ������ռ, ���ر��豸
�� �� ֵ:��Ȩ��ȷ: TRUE; ��Ȩ����: FALSE
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2006/10/12  1.0     ���    ����
=============================================================================*/
BOOL32 CUsbVerify::VerifyData(IN LPSTR lptrVersion, IN EMUsbRight emRight,
                              IN const u8 *pbyBuf, IN s32 nBufLen)
{
    if ( strcmp( lptrVersion, VERSION_40_R3_1 ) == 0 )
    {
        return VerifyVersion40R31( emRight, pbyBuf, nBufLen );
    }

    return FALSE;
}

/*=============================================================================
�� �� ��:VerifyVersion40R31
��    ��:��֤4.0 R3 ��һ������
��    ��:IN EMUsbRight emRight                  [in]    ģ��
         IN const u8 *pbyBuf                    [in]    ��������
         IN s32 nBufLen                         [in]    ���ݳ���
ע    ��:����ǰ��򿪶�����, ����ռ�豸; ���ú�, ������ռ, ���ر��豸
�� �� ֵ:��Ȩ��ȷ: TRUE; ��Ȩ����: FALSE
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2006/10/12  1.0     ���    ����
=============================================================================*/
BOOL32 CUsbVerify::VerifyVersion40R31(IN EMUsbRight emRight, IN const u8 *pbyBuf,
                                      IN s32 nBufLen)
{
    switch ( emRight )
    {
    case enumUsbRightMCS:
        {
            if ( nBufLen < sizeof (TUsbMcsSaveInfo) )  //���ݳ��ȼ���
            {
                return FALSE;
            }

            const TUsbMcsSaveInfo *ptInfo
                        = reinterpret_cast<const TUsbMcsSaveInfo*>(pbyBuf);
            return ( ptInfo->m_emUsbRight == emRight && ptInfo->m_bEnable );
        }
    case enumUsbRightNMS:
        {
            if ( nBufLen < sizeof (TUsbNmsSaveInfo) )  //���ݳ��ȼ���
            {
                return FALSE;
            }

            const TUsbNmsSaveInfo *ptInfo
                        = reinterpret_cast<const TUsbNmsSaveInfo*>(pbyBuf);
            return ( ptInfo->m_emUsbRight == emRight && ptInfo->m_bEnable );
        }
    case enumUsbRightPCMT:
        {
            if ( nBufLen < sizeof (TUsbPcmtSaveInfo) )  //���ݳ��ȼ���
            {
                return FALSE;
            }

            const TUsbPcmtSaveInfo *ptInfo
                        = reinterpret_cast<const TUsbPcmtSaveInfo*>(pbyBuf);
            return ( ptInfo->m_emUsbRight == emRight && ptInfo->m_bEnable );
        }
    case enumUsbRightVOS:
        {
            if ( nBufLen < sizeof (TUsbVosSaveInfo) )  //���ݳ��ȼ���
            {
                return FALSE;
            }

            const TUsbVosSaveInfo *ptInfo
                        = reinterpret_cast<const TUsbVosSaveInfo*>(pbyBuf);
            return ( ptInfo->m_emUsbRight == emRight && ptInfo->m_bEnable );
        }
    default:
        return FALSE;
    }
}