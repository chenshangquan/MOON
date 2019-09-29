/*=============================================================================
模   块   名: USB-KEY操作
文   件   名: UsbVerify.cpp
相 关  文 件: UsbVerify.h
文件实现功能: USB验证
作        者: 王昊
版        本: V4.0  Copyright(C) 2006-2006 Kedacom, All rights reserved.
-------------------------------------------------------------------------------
修改记录:
日      期  版本    修改人      修改内容
2006/10/11  1.0     王昊        创建
=============================================================================*/

// UsbVerify.cpp: implementation of the CUsbVerify class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UsbVerify.h"
#include "hkerror.h"
#include "kdvencrypt.h"


#define MAX_KEY_VALUE_NUM						100							// 可读取的Key-Value对最大数
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
函数名    :  GenEncodeData
功能      :  解密
算法实现  :  
参数说明  :  pOutBuf		解密后的字符串
			 wInBufLen      输入缓冲的大小
			 pInBuf			输入的未解密的字符
			 bDirect        加密 || 解密
返回值说明:  
-------------------------------------------------------------------------------
修改记录  :  
日  期       版本          修改人          走读人          修改记录
2008-8-18				   王雄                             引用
==============================================================================*/

void GenEncodeData(s8 *pOutBuf, u16 wInBufLen, s8 *pInBuf, BOOL32 bDirect)
{
    s8 achIV[MAX_IV_SIZE] = {0};
	
    s8 achKey[32] = {0};
    memset( achKey, 0, sizeof (achKey) );
	strncpy( achKey, KEDA_AES_KEY, strlen(KEDA_AES_KEY) );// 保持key为16的倍数
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
函数名    :  GetKeyValue
功能      :  从子串中获取Key和Value
算法实现  :  
参数说明  :  pchBuf          输入字符串[IN]
			 pchKey          得到的KEY[OUT]
			 nKeyLen         KEY的长度[OUT]
			 pchValue        Key的值[OUT]
			 nValueLen       Key值的长度[OUT]
返回值说明:  
-------------------------------------------------------------------------------
修改记录  :  
日  期       版本          修改人          走读人          修改记录
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
            strlen(KEY_VALUE_CONNECTOR) + 1 );	// Key与Value的分隔符

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

	//返回根目录
    u32 dwRet = HK_BacktoMDir( hCard );
    if ( dwRet != 0 )
    {
        return dwRet;
    }

    //打开文件
    dwRet = HK_OpenFile( hCard, 0xEF01 );
    if ( dwRet != 0 )
    {
        return dwRet;
    }

    //读取文件
    u32 dwReadLen = dwDataLen;
    dwRet = HK_ReadFile( hCard, 0x0000, abyData, dwDataLen, &dwReadLen );
    if ( dwRet != 0 )
    {
        return dwRet;
    }

    //数据解密
	strcpy( achContentBuf, reinterpret_cast<s8*>(abyData) );
	u16 wKeyValueLen = ( u16 )dwDataLen;
	GenEncodeData( achKeyValueContent, wKeyValueLen, achContentBuf, FALSE );
	

	//解析键值

	nCharPos = strcspn(pBuf, "&");
	pchToken2 = strtok(pBuf, "&");

	while (NULL != pchToken2)
	{
		wRet = GetKeyValue(pchToken2, achKey, nKeyBuflen,						// 获取Key-Value对信息
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
    //读取所有正在工作的设备
    u32 dwRet = GetWorkingReaders( aaszReaders, nReaders );
    if ( dwRet != 0 || nReaders == 0 )
    {
        return FALSE;
    }

    //循环检查
    for ( s32 nIndex = 0; nIndex < nReaders; nIndex ++ )
    {
        HKHANDLE    hCard = NULL;
        BOOL32      bOK = FALSE;
        s8          szVersion[64] = {0};
        u8          abyData[DEFAULT_USBKEY_FILESIZE] = {0};
        s32         nDataLen = static_cast<s32>(DEFAULT_USBKEY_FILESIZE);
	

        //打开设备
        dwRet = HK_ConnectDev( aaszReaders[nIndex], &hCard );
        if ( dwRet != 0 )
        {
            continue;
        }

        do
        {
            //独占
            dwRet = HK_BeginTransaction( hCard );
            if ( dwRet != 0 )
            {
                break;
            }

            //权限校验
            dwRet = HK_VerifyOfficerPIN( hCard, DEFAULT_USBKEY_SO_PIN );
            if ( dwRet != 0 )
            {
                break;
            }

            //读取数据
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

			//校验
			if (0 == strcmp(szBaseVersion, "PCMT") )
			{
				bOK = TRUE;
			}
			
        } while ( FALSE );

        //解除独占
        HK_EndTransaction( hCard );
        //断开连接
        HK_DisconnectDev( hCard );
        if ( bOK )  //验证正确
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
函 数 名:Verify
功    能:验证模块授权信息
参    数:EMUsbRight emUsbRight              [in]    模块
注    意:DEBUG下不检验授权
返 回 值:授权正确: TRUE; 无授权或授权错误: FALSE
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2006/10/11  1.0     王昊    创建
=============================================================================*/
BOOL32 CUsbVerify::Verify(EMUsbRight emUsbRight)
{
#ifdef _DEBUG
    return TRUE;    //DEBUG下不检验授权
#endif

    s8 aaszReaders[MAXLEN_USBKEY_READER_NUM][MAXLEN_USBKEY_READER_NAME];
    s32 nReaders = MAXLEN_USBKEY_READER_NUM;

    memset( aaszReaders, 0, sizeof (aaszReaders) );
    //读取所有正在工作的设备
    u32 dwRet = GetWorkingReaders( aaszReaders, nReaders );
    if ( dwRet != 0 || nReaders == 0 )
    {
        return FALSE;
    }

    //循环检查
    for ( s32 nIndex = 0; nIndex < nReaders; nIndex ++ )
    {
        HKHANDLE    hCard = NULL;
        BOOL32      bOK = FALSE;
        s8          szVersion[64] = {0};
        u8          abyData[DEFAULT_USBKEY_FILESIZE] = {0};
        s32         nDataLen = static_cast<s32>(DEFAULT_USBKEY_FILESIZE);

        //打开设备
        dwRet = HK_ConnectDev( aaszReaders[nIndex], &hCard );
        if ( dwRet != 0 )
        {
            continue;
        }

        do
        {
            //独占
            dwRet = HK_BeginTransaction( hCard );
            if ( dwRet != 0 )
            {
                break;
            }

            //权限校验
            dwRet = HK_VerifyOfficerPIN( hCard, DEFAULT_USBKEY_SO_PIN );
            if ( dwRet != 0 )
            {
                break;
            }

            //读取数据
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

            //验证
            bOK = VerifyData( szVersion, emUsbRight, abyData, nDataLen );

        } while ( FALSE );

        //解除独占
        HK_EndTransaction( hCard );
        //断开连接
        HK_DisconnectDev( hCard );
        if ( bOK )  //验证正确
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
函 数 名:SetDeviceCallBack
功    能:设置设备状态回调函数
参    数:IN TUsbVerifyCallBack pFuncOnCallBack  [in]    插入回调函数
         IN TUsbVerifyCallBack pFuncOffCallBack [in]    拔出回调函数
         IN void *pCBData                       [in]    回调数据
注    意:错误码用GetErrorDescription解释，请在Verify之后调用
返 回 值:设置成功: 0; 设置失败: 错误码
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2006/10/11  1.0     王昊    创建
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
函 数 名:VerifyData
功    能:验证数据
参    数:IN LPSTR lptrVersion                   [in]    版本号
         IN EMUsbRight emRight                  [in]    模块
         IN const u8 *pbyBuf                    [in]    数据内容
         IN s32 nBufLen                         [in]    数据长度
注    意:调用前请打开读卡器, 并独占设备; 调用后, 请解除独占, 并关闭设备
返 回 值:授权正确: TRUE; 授权错误: FALSE
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2006/10/12  1.0     王昊    创建
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
函 数 名:VerifyVersion40R31
功    能:验证4.0 R3 第一版数据
参    数:IN EMUsbRight emRight                  [in]    模块
         IN const u8 *pbyBuf                    [in]    数据内容
         IN s32 nBufLen                         [in]    数据长度
注    意:调用前请打开读卡器, 并独占设备; 调用后, 请解除独占, 并关闭设备
返 回 值:授权正确: TRUE; 授权错误: FALSE
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2006/10/12  1.0     王昊    创建
=============================================================================*/
BOOL32 CUsbVerify::VerifyVersion40R31(IN EMUsbRight emRight, IN const u8 *pbyBuf,
                                      IN s32 nBufLen)
{
    switch ( emRight )
    {
    case enumUsbRightMCS:
        {
            if ( nBufLen < sizeof (TUsbMcsSaveInfo) )  //数据长度检验
            {
                return FALSE;
            }

            const TUsbMcsSaveInfo *ptInfo
                        = reinterpret_cast<const TUsbMcsSaveInfo*>(pbyBuf);
            return ( ptInfo->m_emUsbRight == emRight && ptInfo->m_bEnable );
        }
    case enumUsbRightNMS:
        {
            if ( nBufLen < sizeof (TUsbNmsSaveInfo) )  //数据长度检验
            {
                return FALSE;
            }

            const TUsbNmsSaveInfo *ptInfo
                        = reinterpret_cast<const TUsbNmsSaveInfo*>(pbyBuf);
            return ( ptInfo->m_emUsbRight == emRight && ptInfo->m_bEnable );
        }
    case enumUsbRightPCMT:
        {
            if ( nBufLen < sizeof (TUsbPcmtSaveInfo) )  //数据长度检验
            {
                return FALSE;
            }

            const TUsbPcmtSaveInfo *ptInfo
                        = reinterpret_cast<const TUsbPcmtSaveInfo*>(pbyBuf);
            return ( ptInfo->m_emUsbRight == emRight && ptInfo->m_bEnable );
        }
    case enumUsbRightVOS:
        {
            if ( nBufLen < sizeof (TUsbVosSaveInfo) )  //数据长度检验
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