/*=============================================================================
模   块   名: USB-KEY操作
文   件   名: UsbKey.cpp
相 关  文 件: UsbKey.h
文件实现功能: USB基本操作
作        者: 王昊
版        本: V4.0  Copyright(C) 2006-2006 Kedacom, All rights reserved.
-------------------------------------------------------------------------------
修改记录:
日      期  版本    修改人      修改内容
2006/10/11  1.0     王昊        创建
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
函 数 名:EnumReaders
功    能:枚举所有读卡器名
参    数:OUT s8 aaszAllReaders[][]                  [out]   所有读卡器名, 用0x00分隔
         OUT s32 &nReaderNum                        [out]   读卡器个数
注    意:错误码用GetErrorDescription解释
返 回 值:读取成功: 0; 读取失败: 错误码
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2006/10/11  1.0     王昊    创建
=============================================================================*/
u32 CUsbKey::EnumReaders(OUT s8 aaszAllReaders[MAXLEN_USBKEY_READER_NUM][MAXLEN_USBKEY_READER_NAME],
                         OUT s32 &nReaderNum)
{
    u32 dwReadersNameLen = 0;
    u32 dwReaderNum = 0;
    //获取所有读卡器名字长度
    u32 dwRet = HK_ListReaders( NULL, &dwReadersNameLen, &dwReaderNum );
    if ( dwRet != 0 )
    {
        return dwRet;
    }

    LPSTR lptrReadersName = new s8 [dwReadersNameLen];
    memset( lptrReadersName, 0, dwReadersNameLen * sizeof (s8) );

    //获取所有读卡器名
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
函 数 名:SaveData
功    能:保存数据
参    数:IN HKHANDLE hCard                      [in]    读卡器句柄
         IN EMUsbRight emRight                  [in]    模块
         IN const u8 *pbyBuf                    [in]    保存数据
         IN s32 nBufLen                         [in]    数据长度
注    意:错误码用GetErrorDescription解释; 调用前请打开读卡器, 并独占设备
         调用后, 请解除独占, 并关闭设备
返 回 值:保存成功: 0; 保存失败: 错误码
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2006/10/12  1.0     王昊    创建
=============================================================================*/
u32 CUsbKey::SaveData(IN HKHANDLE hCard, IN EMUsbRight emRight,
                      IN const u8 *pbyBuf, IN s32 nBufLen)
{
    u8 abyData[DEFAULT_USBKEY_FILESIZE] = {0};
    u8 abyBuf[DEFAULT_USBKEY_FILESIZE] = {0};

    memset( abyBuf, 0, sizeof (abyBuf) );
    memcpy( abyBuf, pbyBuf, nBufLen );
    //数据加密
    KdvAES( DEFAULT_USBKEY_AES_KEY, strlen( DEFAULT_USBKEY_AES_KEY ),
            DEFAULT_USBKEY_AES_MODE, qfDES_encrypt, DEFAULT_USBKEY_AES_INITKEY,
            abyBuf, DEFAULT_USBKEY_FILESIZE, abyData );

    //返回根目录
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

    //打开父目录
    dwRet = HK_OpenDir( hCard, DEFAULT_USBKEY_DIRID );
    if ( dwRet != 0 )   //打开失败, 创建父目录
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

    //删除文件，然后创建新数据
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

    //创建文件
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

    //打开文件
    dwRet = HK_OpenFile( hCard, dwFileID );
    if ( dwRet != 0 )
    {
        return dwRet;
    }

    //写入数据
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
函 数 名:ReadData
功    能:读取数据
参    数:IN HKHANDLE hCard                      [in]    读卡器句柄
         IN EMUsbRight emRight                  [in]    模块
         OUT const u8 *pbyBuf                   [out]   数据
         IN OUT s32 nBufLen                     [in]    数据最大长度
注    意:错误码用GetErrorDescription解释; 调用前请打开读卡器, 并独占设备
         调用后, 请解除独占, 并关闭设备
返 回 值:读取成功: 0; 读取失败: 错误码
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2006/10/12  1.0     王昊    创建
=============================================================================*/
u32 CUsbKey::ReadData(IN HKHANDLE hCard, IN EMUsbRight emRight,
                      OUT u8 *pbyBuf, IN OUT s32 nBufLen)
{
    u8 abyData[DEFAULT_USBKEY_FILESIZE] = {0};
    u32 dwDataLen = DEFAULT_USBKEY_FILESIZE;

    //返回根目录
    u32 dwRet = HK_BacktoMDir( hCard );
    if ( dwRet != 0 )
    {
        return dwRet;
    }

    //打开父目录
    dwRet = HK_OpenDir( hCard, DEFAULT_USBKEY_DIRID );
    if ( dwRet != 0 )   //打开失败, 创建父目录
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

    //打开文件
    dwRet = HK_OpenFile( hCard, dwFileID );
    if ( dwRet != 0 )
    {
        return dwRet;
    }

    //读取文件
    u32 dwReadLen = DEFAULT_USBKEY_FILESIZE;
    dwRet = HK_ReadFile( hCard, 0x0000, abyData, dwDataLen, &dwReadLen );
    if ( dwRet != 0 )
    {
        return dwRet;
    }


    //数据解密
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
函 数 名:SaveVersion
功    能:保存版本号
参    数:IN HKHANDLE hCard                      [in]    读卡器句柄
注    意:错误码用GetErrorDescription解释; 调用前请打开读卡器, 并独占设备
         调用后, 请解除独占, 并关闭设备
返 回 值:保存成功: 0; 保存失败: 错误码
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2006/10/12  1.0     王昊    创建
=============================================================================*/
u32 CUsbKey::SaveVersion(IN HKHANDLE hCard)
{
    //返回根目录
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

    //打开父目录
    dwRet = HK_OpenDir( hCard, DEFAULT_USBKEY_DIRID );
    if ( dwRet != 0 )   //打开失败, 创建父目录
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

    //删除文件，然后创建新数据
    HK_DeleteFile( hCard, USBKEY_VERSION_FILEID );

    //创建文件
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

    //打开文件
    dwRet = HK_OpenFile( hCard, USBKEY_VERSION_FILEID );
    if ( dwRet != 0 )
    {
        return dwRet;
    }

    //写入数据
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
函 数 名:ReadVersion
功    能:读取版本号
参    数:IN HKHANDLE hCard                      [in]    读卡器句柄
         OUT LPSTR lptrVersion                  [out]   版本号
注    意:错误码用GetErrorDescription解释; 调用前请打开读卡器, 并独占设备
         调用后, 请解除独占, 并关闭设备
返 回 值:读取成功: 0; 读取失败: 错误码
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2006/10/12  1.0     王昊    创建
=============================================================================*/
u32 CUsbKey::ReadVersion(IN HKHANDLE hCard, OUT LPSTR lptrVersion)
{
    u8 abyData[DEFAULT_USBKEY_FILESIZE] = {0};
    u32 dwDataLen = DEFAULT_USBKEY_FILESIZE;

    //返回根目录
    u32 dwRet = HK_BacktoMDir( hCard );
    if ( dwRet != 0 )
    {
        return dwRet;
    }

    //打开父目录
    dwRet = HK_OpenDir( hCard, DEFAULT_USBKEY_DIRID );
    if ( dwRet != 0 )   //打开失败, 创建父目录
    {
        return dwRet;
    }

    //打开文件
    dwRet = HK_OpenFile( hCard, USBKEY_VERSION_FILEID );
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
    strcpy( lptrVersion, reinterpret_cast<s8*>(abyData) );

    return dwRet;
}

/*=============================================================================
函 数 名:GetWorkingReaders
功    能:获取当前所有可用读卡器
参    数:OUT s8 aaszReaders[][]                         [out]   当前所有可用读卡器名
         OUT s32 &nReaderNum                            [out]   可用读卡器个数
注    意:错误码用GetErrorDescription解释
返 回 值:读取成功: 0; 读取失败: 错误码
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2006/10/11  1.0     王昊    创建
=============================================================================*/
u32 CUsbKey::GetWorkingReaders(OUT s8 aaszReaders[MAXLEN_USBKEY_READER_NUM][MAXLEN_USBKEY_READER_NAME],
                               OUT s32 &nReaderNum)
{
    s8 aaszAllReaders[MAXLEN_USBKEY_READER_NUM][MAXLEN_USBKEY_READER_NAME];
    s32 nAllReaders = MAXLEN_USBKEY_READER_NUM;
    memset( aaszAllReaders, 0, sizeof (aaszAllReaders) );

    //枚举所有设备
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
函 数 名:GetErrorDescription
功    能:获取错误描述
参    数:IN TUsbVerifyCallBack pFuncCallBack    [in]    回调函数
         IN u8 byLanguage                       [in]    语言类型(0: 中文; 1: 英文)
注    意:现在只有中文
返 回 值:错误描述
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2006/10/11  1.0     王昊    创建
=============================================================================*/
LPCTSTR CUsbKey::GetErrorDescription(IN u32 dwErrCode, IN u8 byLanguage /* = 0 */)
{
    switch ( dwErrCode )
    {
    case 0:
        return _T("成功");
    case HKI_ERR_DEV_INDEX:
        return _T("设备索引号超界");
    case HKI_ERR_DEV_INUSE:
        return _T("该设备已处于连接状态，请等待并重新尝试连接");
    case HKI_ERR_DEV_READERLEN:
        return _T("取设备个数时发现设备名超长");
    case HKI_ERR_DEV_INVALIDCTX:
        return _T("释放设备时，指定的设备句柄无效，您可能已调用过HKDisconnectDev函数");
    case HKI_ERR_DEV_BYNAME:
        return _T("找不到指定的设备名或该设备不可用");
    case HKI_ERR_DEV_INVALIDINDEX:
        return _T("无效的设备索引号");
    case HKI_ERR_DEV_NOTFOUND:
        return _T("未发现该设备");
    case HKI_ERR_DEV_ATR_LENGTH:
        return _T("取序列号时，所得ATR的长度有误。应为2-32字节。");
    case HKI_ERR_DEV_ATR_FLAG:
        return _T("取序列号时，所得ATR的首字节标志不正确。应为3B或3F");
    case HKI_ERR_DEV_ATR_VALUE:
        return _T("取序列号时，不能识别ATR内容的格式。可能没有找到0x8888标志");
    case HKI_ERR_DEV_HID_CRC:
        return _T("HID设备通信时发生奇偶校验错误");
    case HKI_ERR_DEV_HID_TIMEOUT:
        return _T("HID设备通信时发生超时错误");
    case HKI_ERR_DEV_HID_RESET:
        return _T("HID设备通信时发生卡片复位信息TS或BCC错误");
    case HKI_ERR_DEV_HID_LEN:
        return _T("HID设备通信时发生长度错误");
    case HKI_ERR_DEV_HID_BCC:
        return _T("HID设备通信中，计算机发送的命令系列校验码错");
    case HKI_ERR_DEV_HID_WRITE:
        return _T("HID设备写操作错误");
    case HKI_ERR_DEV_HID_READ:
        return _T("HID设备读操作错误");
    case HKI_ERR_CRYPT_INVALIDPARAM:
        return _T("给定的函数参数在无效值域");
    case HKI_ERR_MEM_NULLPTR:
        return _T("作为参数的指针为空");
    case HKI_ERR_MEM_BUFTOOSMALL:
        return _T("分配的内存空间不够");
    case HKI_ERR_EVT_INVALID:
        return _T("无效的设备插拔处理事件句柄");
    case HKI_ERR_MUTEX_OBJHOST:
        return _T("当前申请服务的对象过多，已无剩余资源可用");
    case HKI_PIN_LEN_ERROR:
        return _T("口令长度错误");
    case HKI_PIN_RETRY_NUM_ERROR:
        return _T("口令错误计数次数错误");
    case HKI_DEVICE_NAME_LEN_ERROR:
        return _T("设备名字长度错误");
    case HKI_FILE_TYPE_ERROR:
        return _T("文件类型错误");
    case HKI_WRITE_DATA_LEN_ERROR:
        return _T("写入的数据长度错误");
    case HKI_READ_DATA_LEN_ERROR:
        return _T("读出的数据长度错误");
    case HKI_RSA_PADDING_TYPE_ERROR:
        return _T("RSA补码类型错误");
    case HKI_RSA_DATA_LEN_ERROR:
        return _T("RSA数据长度错误");
    case HKI_ACCESS_TYPE_ERROR:
        return _T("权限类型错误");
    case HKI_INPUT_DATA_LEN_ERROR:
        return _T("SSF33/DES算法输入的数据长度错误，必须为16/8的倍数");
    case HKI_DEVICE_CMS_DIFFER_ERROR:
        return _T("设备缓冲区的大小和设备类型不符");
    case HKI_KEY_LEN_ERROR:
        return _T("SSF33密钥长度错误");
    case HKI_KEY_ID_ERROR:
        return _T("SSF33密钥ID错误");
    case HKI_INVALID_PARAM_TYPE:
        return _T("非法的参数类型");
    case HKI_RET_DATA_LEN_ERROR:
        return _T("设备返回的数据长度错误");
    case HKI_ERROR_NOT_ENOUGH_MEMORY:
        return _T("内存不足");
    case HKI_ENCRYPT_DECRYPT_MODE_ERROR:
        return _T("加解密模式错误");
    case HKI_STRTOHEX_INPUT_DATA_ERROR:
        return _T("字符转换数据错误");
    case HKI_NOT_SUPPORT_ERROR:
        return _T("功能不支持");
    case HKI_FILE_ID_INVALID_ERROR:
        return _T("文件ID取值范围不合法");
    case HKI_PADDING_INVALID_ERROR:
        return _T("数据的补码有误");
    case HKI_NOT_SUPPORT_SYM:
        return _T("不支持该算法");
    case HK_LENGTH_INVALID_ERROR:
        return _T("写入数据的长度错误");
    case HK_ID_EXIST_ERROR:
        return _T("标识符已存在");
    case HK_NOT_SUPPORT_ERROR:
        return _T("功能不支持");
    case HK_ID_NOT_FOUND_ERROR:
        return _T("未找到文件");
    case HK_NOT_ENOUGH_SIZE:
        return _T("空间不够");
//    case HK_X_TIMES_LEFT:
    case HKI_ERRCODE_BASE + 0x000063C1:
        return _T("校验口令错误，还有1次机会");
    case HKI_ERRCODE_BASE + 0x000063C2:
        return _T("校验口令错误，还有2次机会");
    case HKI_ERRCODE_BASE + 0x000063C3:
        return _T("校验口令错误，还有3次机会");
    case HKI_ERRCODE_BASE + 0x000063C4:
        return _T("校验口令错误，还有4次机会");
    case HKI_ERRCODE_BASE + 0x000063C5:
        return _T("校验口令错误，还有5次机会");
    case HKI_ERRCODE_BASE + 0x000063C6:
        return _T("校验口令错误，还有6次机会");
    case HKI_ERRCODE_BASE + 0x000063C7:
        return _T("校验口令错误，还有7次机会");
    case HKI_ERRCODE_BASE + 0x000063C8:
        return _T("校验口令错误，还有8次机会");
    case HKI_ERRCODE_BASE + 0x000063C9:
        return _T("校验口令错误，还有9次机会");
    case HKI_ERRCODE_BASE + 0x000063CA:
        return _T("校验口令错误，还有10次机会");
    case HKI_ERRCODE_BASE + 0x000063CB:
        return _T("校验口令错误，还有11次机会");
    case HKI_ERRCODE_BASE + 0x000063CC:
        return _T("校验口令错误，还有12次机会");
    case HKI_ERRCODE_BASE + 0x000063CD:
        return _T("校验口令错误，还有13次机会");
    case HKI_ERRCODE_BASE + 0x000063CE:
        return _T("校验口令错误，还有14次机会");
    case HKI_ERRCODE_BASE + 0x000063CF:
        return _T("校验口令错误，还有15次机会");
    case HK_NOT_ACCESS_ERROR:
        return _T("安全条件不满足");
    case HK_PIN_LOCKED_ERROR:
        return _T("口令被锁死");
    case HKI_ERR_UNKOWN:
    default:
        return _T("未知错误");
    }
}
