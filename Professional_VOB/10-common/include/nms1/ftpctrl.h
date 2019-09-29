/*=============================================================================
模   块   名: 网管公用模块库
文   件   名: ftpctrl.h
相 关  文 件: ftpctrl.cpp
文件实现功能: FTP上传下载控制
作        者: 王昊
版        本: V4.0  Copyright(C) 2003-2005 KDC, All rights reserved.
说        明: 需要使用MFC, 使用者需要包含wininet.lib库
-------------------------------------------------------------------------------
修改记录:
日      期  版本    修改人      修改内容
2005/09/29  4.0     王昊        创建
=============================================================================*/

#ifndef _FTPCTRL_20050929_H_
#define _FTPCTRL_20050929_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <wininet.h>
#include "kdvtype.h"

#define IP_LEN                  (s32)16     //  IP地址字符串长度
#define FTP_USER_LEN            (s32)32     //  FTP用户名长度
#define FTP_PWD_LEN             (s32)32     //  FTP密码长度
#define PROXY_NAME_LEN          (s32)64     //  代理名称长度
#define PROXY_PWD_LEN           (s32)32     //  代理密码长度

#define FTP_TIMEOUT             (u32)20 * 1000  //  FTP线程超时时间, 20秒

#define FTP_AGENT               _T("Ftp_Ctrl")  //  InternetOpen第一个参数

//  FTP传输方向
enum EmFtpDirect
{
    emFtpUpload     = (u8)0,    //  上传
    emFtpDownload   = (u8)1     //  下载
};

//  FTP传输状态
enum EmFtpStatus
{
    emFtpBegin      = (u32)0,   //开始传输, WPARAM = emFtpBegin, LPARAM表示要传输的文件大小
    emFtpTransfer   = (u32)1,   //正在传输, WPARAM = emFtpTransfer, LPARAM表示本次发送大小
    emFtpEnd        = (u32)2,   //停止传输, WPARAM = emFtpEnd, LPARAM表示结果, 0--成功, !0--错误码
};

class CFtpCtrl
{
public:
    /*=============================================================================
    函 数 名:CFtpCtrl
    功    能:构造函数
    参    数:无
    注    意:无
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/09/29  4.0     王昊    创建
    =============================================================================*/
    CFtpCtrl();

    /*=============================================================================
    函 数 名:~CFtpCtrl
    功    能:析构函数
    参    数:无
    注    意:无
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/09/29  4.0     王昊    创建
    =============================================================================*/
    virtual ~CFtpCtrl();

public:
    /*=============================================================================
    函 数 名:SetServerParam
    功    能:设置FTP服务器的连接参数
    参    数:LPCTSTR pszIpAddr                  [in]    服务器IP地址
             LPCTSTR pszUser                    [in]    登录用户名称
             LPCTSTR pszPwd                     [in]    登录口令
             u16 wPort                          [in]    FTP服务器端口
             LPCTSTR pszProxyName               [in]    代理名称
             LPCTSTR pszProxyPwd                [in]    代理口令
    注    意:无
    返 回 值:是否成功
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/09/29  4.0     王昊    创建
    =============================================================================*/
    BOOL32 SetServerParam(LPCTSTR pszIpAddr, LPCTSTR pszUser, LPCTSTR pszPwd,
                          u16 wPort = INTERNET_DEFAULT_FTP_PORT,
                          LPCTSTR pszProxyName = NULL,
                          LPCTSTR pszProxyPwd = NULL);

    /*=============================================================================
    函 数 名:BeginDownload
    功    能:开始下载文件
    参    数:HWND hWnd                          [in]    接收消息的窗口句柄
             LPCTSTR pszRemoteFile              [in]    远端文件名称
             LPCTSTR pszLocalFile               [in]    保存本地的文件名称
             u32 dwFileType                     [in]    文件传输类型
             LPCTSTR pszAgent                   [in]    InternetOpen第一个参数
             BOOL32 bDeleteRemoteFile           [in]    下载完毕后是否删除远端文件
    注    意:无
    返 回 值:是否成功
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/09/29  4.0     王昊    创建
    =============================================================================*/
    BOOL32 BeginDownload(HWND hWnd, LPCTSTR pszRemoteFile,
                         LPCTSTR pszLocalFile,
                         u32 dwFileType = FTP_TRANSFER_TYPE_UNKNOWN,
                         LPCTSTR pszAgent = FTP_AGENT,
                         BOOL32 bDeleteRemoteFile = TRUE);

    /*=============================================================================
    函 数 名:BeginUpload
    功    能:开始上传文件
    参    数:HWND hWnd                          [in]    接收消息的窗口句柄
             LPCTSTR pszRemoteFile              [in]    远端文件名称
             LPCTSTR pszLocalFile               [in]    保存本地的文件名称
             u32 dwFileType                     [in]    文件传输类型
             LPCTSTR pszAgent                   [in]    InternetOpen第一个参数
    注    意:无
    返 回 值:是否成功
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/09/29  4.0     王昊    创建
    =============================================================================*/
    BOOL32 BeginUpload(HWND hWnd, LPCTSTR pszRemoteFile,
                       LPCTSTR pszLocalFile,
                       u32 dwFileType = FTP_TRANSFER_TYPE_UNKNOWN,
                       LPCTSTR pszAgent = FTP_AGENT);

	/*=============================================================================
    函 数 名:EndFtpFile
    功    能:停止FTP传输
    参    数:无
    注    意:无
    返 回 值:是否成功
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/10/08  4.0     王昊    创建
    =============================================================================*/
    BOOL32 EndFtpFile(void);

    /*=============================================================================
    函 数 名:GetCurrentSession
    功    能:得到当前FTP的会话句柄
    参    数:无
    注    意:无
    返 回 值:当前FTP的会话句柄
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/10/08  4.0     王昊    创建
    =============================================================================*/
    HINTERNET GetCurrentSession(void) const { return m_hSession; }

    /*=============================================================================
    函 数 名:GetCurrentConnect
    功    能:得到当前的连接句柄
    参    数:无
    注    意:无
    返 回 值:当前连接句柄
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/10/08  4.0     王昊    创建
    =============================================================================*/
    HINTERNET GetCurrentConnect(void) const { return m_hConnect; }

    /*=============================================================================
    函 数 名:GetCurrentRemoteFile
    功    能:获取远程文件名称
    参    数:无
    注    意:无
    返 回 值:远程文件名称
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/10/08  4.0     王昊    创建
    =============================================================================*/
    LPCTSTR GetCurrentRemoteFile(void) const { return m_aszRemoteFile; }

    /*=============================================================================
    函 数 名:GetCurrentLocalFile
    功    能:获取本地文件名称
    参    数:无
    注    意:无
    返 回 值:本地文件名称
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/10/08  4.0     王昊    创建
    =============================================================================*/
    LPCTSTR GetCurrentLocalFile(void) const { return m_aszLocalFile; }

    /*=============================================================================
    函 数 名:GetFtpSvrIP
    功    能:获取FTP服务器IP
    参    数:无
    注    意:无
    返 回 值:服务器IP
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/10/08  4.0     王昊    创建
    =============================================================================*/
    LPCTSTR GetFtpSvrIP(void) const { return m_aszFtpSrvIp; }

    /*=============================================================================
    函 数 名:GetFtpSvrPort
    功    能:获取FTP服务器端口
    参    数:无
    注    意:无
    返 回 值:服务器端口
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/10/08  4.0     王昊    创建
    =============================================================================*/
    u16 GetFtpSvrPort(void) const { return m_wFtpSrvPort; }

    /*=============================================================================
    函 数 名:GetFtpUser
    功    能:获取FTP用户名
    参    数:无
    注    意:无
    返 回 值:FTP用户名
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/10/08  4.0     王昊    创建
    =============================================================================*/
    LPCTSTR GetFtpUser(void) const { return m_aszFtpSrvUser; }

    /*=============================================================================
    函 数 名:GetFtpPwd
    功    能:获取FTP密码
    参    数:无
    注    意:无
    返 回 值:FTP密码
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/10/08  4.0     王昊    创建
    =============================================================================*/
    LPCTSTR GetFtpPwd(void) const { return m_aszFtpSrvPwd; }

    /*=============================================================================
    函 数 名:GetFtpProxyName
    功    能:获取代理名称
    参    数:无
    注    意:无
    返 回 值:代理名称
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/10/08  4.0     王昊    创建
    =============================================================================*/
    LPCTSTR GetFtpProxyName(void) const { return m_aszProxyName; }

    /*=============================================================================
    函 数 名:GetFtpProxyPwd
    功    能:获取代理密码
    参    数:无
    注    意:无
    返 回 值:代理密码
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/10/08  4.0     王昊    创建
    =============================================================================*/
    LPCTSTR GetFtpProxyPwd(void) const { return m_aszProxyPwd; }

    /*=============================================================================
    函 数 名:GetCurrentFileType
    功    能:获取当前传输的文件类型
    参    数:无
    注    意:无
    返 回 值:文件类型
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/10/08  4.0     王昊    创建
    =============================================================================*/
    u32 GetCurrentFileType(void) const { return m_dwFileType; }

    /*=============================================================================
    函 数 名:SetFileSize
    功    能:设置FTP文件总长度
    参    数:u32 dwFileSize             [in]    FTP文件总长度
    注    意:无
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/10/08  4.0     王昊    创建
    =============================================================================*/
    void SetFileSize(u32 dwFileSize) { m_dwTotalFileSize = dwFileSize; }

    /*=============================================================================
    函 数 名:GetTotalFileSize
    功    能:获取文件总长度
    参    数:无
    注    意:无
    返 回 值:文件总长度
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/10/08  4.0     王昊    创建
    =============================================================================*/
    u32 GetTotalFileSize(void) const { return m_dwTotalFileSize; }

    /*=============================================================================
    函 数 名:GetCurrentFtpSize
    功    能:获取当前已经传输的大小
    参    数:无
    注    意:无
    返 回 值:已经传输的大小
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/10/08  4.0     王昊    创建
    =============================================================================*/
    u32 GetCurrentFtpSize(void) const { return m_dwCurrentFtpSize; }

    /*=============================================================================
    函 数 名:IncreaseFtpSize
    功    能:在文件传输过程中, 设置实际已经传输的文件大小
    参    数:u32 dwProcSize             [in]    新完成大小
    注    意:无
    返 回 值:已完成大小
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/10/08  4.0     王昊    创建
    =============================================================================*/
    u32 IncreaseFtpSize(u32 dwProcSize);

    /*=============================================================================
    函 数 名:GetCurProcSize
    功    能:获取当前文件进行的大小
    参    数:无
    注    意:无
    返 回 值:当前文件进行的大小
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/10/08  4.0     王昊    创建
    =============================================================================*/
    u32 GetCurProcSize(void) const { return m_dwCurrentFtpSize; }

    /*=============================================================================
    函 数 名:RegisterMsgHandle
    功    能:注册一个消息
    参    数:u32 dwEventId              [in]    消息号
    注    意:无
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/10/08  4.0     王昊    创建
    =============================================================================*/
    void RegisterMsgHandle(u32 dwEventId) { m_dwEventId = dwEventId; }

    /*=============================================================================
    函 数 名:GetRegisterMsgHandle
    功    能:获取已经注册的消息号
    参    数:无
    注    意:无
    返 回 值:已经注册的消息号
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/10/08  4.0     王昊    创建
    =============================================================================*/
    u32 GetRegisterMsgHandle(void) const { return m_dwEventId; }

    /*=============================================================================
    函 数 名:GethWnd
    功    能:获取当前传输接收消息窗口句柄
    参    数:无
    注    意:无
    返 回 值:窗口句柄
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/10/08  4.0     王昊    创建
    =============================================================================*/
    HWND GethWnd(void) const { return m_hWnd; }

    /*=============================================================================
    函 数 名:SetFtpDirect
    功    能:设置FTP传输方向
    参    数:EmFtpDirect byFtpDirect            [in]    传输方向
    注    意:无
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/10/08  4.0     王昊    创建
    =============================================================================*/
    void SetFtpDirect(EmFtpDirect byFtpDirect) { m_byFtpDirect = byFtpDirect; }

    /*=============================================================================
    函 数 名:GetFtpDirect
    功    能:获取FTP传输方向
    参    数:无
    注    意:无
    返 回 值:FTP传输方向
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/10/08  4.0     王昊    创建
    =============================================================================*/
    EmFtpDirect GetFtpDirect(void) const { return m_byFtpDirect; }

    /*=============================================================================
    函 数 名:IsDelRemoteFileAfterDownload
    功    能:判断文件下载结束后是否删除远端文件
    参    数:无
    注    意:无
    返 回 值:是否删除远端文件
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/10/08  4.0     王昊    创建
    =============================================================================*/
    BOOL32 IsDelRemoteFileAfterDownload(void) const { return m_bDelRemoteFile; }

    /*=============================================================================
    函 数 名:PostMsg
    功    能:消息发送
    参    数:WPARAM wParam                  [in]    消息子类型
             LPARAM lParam                  [in]    消息参数
    注    意:无
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/10/08  4.0     王昊    创建
    =============================================================================*/
    virtual void PostMsg(WPARAM wParam, LPARAM lParam = 0);

    /*=============================================================================
    函 数 名:IsFileAscii
    功    能:判断一个要进行文件传输的文件是否是ASCII方式的
    参    数:LPCTSTR pszFileName                [in]    文件名
    注    意:无
    返 回 值:是否ASCII方式
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/09/29  4.0     王昊    创建
    =============================================================================*/
    static BOOL32 IsFileAscii(LPCTSTR pszFileName);

    /*=============================================================================
    函 数 名:FormatFtpError
    功    能:获取系统的错误描述
    参    数:u32 dwErrorCode                    [in]    错误码
             LPTSTR *ppszMsg                    [out]   描述信息
    注    意:ppszMsg使用结束后，请调用LocalFree来释放该空间
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/09/29  4.0     王昊    创建
    =============================================================================*/
    static void FormatFtpError(u32 dwErrorCode, LPTSTR *ppszMsg);

	/*=============================================================================
	函 数 名:DeleteFile
	功    能:消息发送
	参    数:LPCSTR lpszFileName                 [in]    文件名字
	注    意:无
	返 回 值:TRUE:文件删除成功	FALSE:文件删除失败
	-------------------------------------------------------------------------------
	修改纪录:
	日      期  版本    修改人  修改内容
	2011/03/21  5.0     王永波    创建
	=============================================================================*/
	BOOL32 DeleteFile(LPCSTR lpszFileName);

	/*=============================================================================
    函 数 名:CreateDir
    功    能:创建目录
    参    数:LPCTSTR strDir  目录名    使用范围：上级目录存在
    注    意:无
    返 回 值:是否成功
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2013/01/26  4.0     刘德印    创建
    =============================================================================*/
    BOOL32 CreateDir( LPCTSTR strDir );

	/*=============================================================================
    函 数 名:SetIsRenameTransFile
    功    能:是否重命名传输文件   是：则传输结束不自动关闭服务器   等待Rename后关闭服务器
    参    数:BOOL32 bIsRename
    注    意:无
    返 回 值:是否成功
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2013/01/26  4.0     刘德印    创建
    =============================================================================*/
    void SetIsRenameTransFile( BOOL32 bIsRename ){ m_bIsRenameTransFile = bIsRename;};
    BOOL32 GetIsRenameTransFile(){ return m_bIsRenameTransFile;};

	/*=============================================================================
    函 数 名:RenameFtpFile
    功    能:重名名FTP文件
    参    数:LPCTSTR pszRemoteTempFile  传输中的源文件, LPCTSTR pszRemoteFile  传输中将源文件替换为目标文件
    注    意:无
    返 回 值:是否成功
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2013/01/26  4.0     刘德印    创建
    =============================================================================*/
    BOOL32 RenameFtpFile( LPCTSTR pszRemoteTempFile, LPCTSTR pszRemoteFile );

	/*=============================================================================
    函 数 名:ConnectServer
    功    能:连接FTP服务器
    参    数:无
    注    意:由外面调用连接服务器
    返 回 值:是否成功
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2013/08/06  4.0     景洋洋    创建
    =============================================================================*/
	BOOL32 ConnectServer();

	/*=============================================================================
    函 数 名:FindfFtpFile
    功    能:查找FTP文件
    参    数: LPCTSTR pszRemotePath  文件路径, LPCTSTR pstrRemoteName 文件名字
    注    意:无
    返 回 值:是否成功
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2013/08/06  4.0     景洋洋    创建
    =============================================================================*/
	BOOL32 FindfFtpFile( LPCTSTR pszRemotePath, LPCTSTR pstrRemoteName );
	
	/*=============================================================================
    函 数 名:SetIsRenameTransFile
    功    能:是否关闭ftp设置   默认由内部控制关闭 
    参    数:BOOL32 bAutoEnd
    注    意:多文件上传由外部控制ftp关闭
    返 回 值:是否成功
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2013/12/11  4.0     景洋洋    创建
    =============================================================================*/
    void SetAutoEndFtpFile( BOOL32 bAutoEnd ){ m_bAutoEndFtpFile = bAutoEnd;};
    BOOL32 GetAutoEndFtpFile(){ return m_bAutoEndFtpFile;};

protected:
    /*=============================================================================
    函 数 名:CheckParam
    功    能:检查开始上传或下载时传入的参数是否正确
    参    数:LPCTSTR pszRemoteFile              [in]    远端文件名称
             LPCTSTR pszLocalFile               [in]    保存本地的文件名称
             u32 dwFileType                     [in]    文件传输类型
    注    意:无
    返 回 值:参数是否正确
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/09/29  4.0     王昊    创建
    =============================================================================*/
    BOOL32 CheckParam(LPCTSTR pszRemoteFile, LPCTSTR pszLocalFile, u32 dwFileType);

    /*=============================================================================
    函 数 名:DownloadFile
    功    能:下载文件
    参    数:LPCTSTR pszRemoteFile              [in]    远端文件名称
             LPCTSTR pszLocalFile               [in]    保存本地的文件名称
             u32 dwFileType                     [in]    文件传输类型
             LPCTSTR pszAgent                   [in]    InternetOpen第一个参数
    注    意:无
    返 回 值:下载是否成功
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/09/29  4.0     王昊    创建
    =============================================================================*/
    virtual BOOL32 DownloadFile(LPCTSTR pszRemoteFile, LPCTSTR pszLocalFile,
                                u32 dwFileType, LPCTSTR pszAgent);

    /*=============================================================================
    函 数 名:UploadFile
    功    能:上传文件
    参    数:LPCTSTR pszRemoteFile              [in]    远端文件名称
             LPCTSTR pszLocalFile               [in]    保存本地的文件名称
             u32 dwFileType                     [in]    文件传输类型
             LPCTSTR pszAgent                   [in]    InternetOpen第一个参数
    注    意:无
    返 回 值:上传是否成功
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/09/29  4.0     王昊    创建
    =============================================================================*/
    virtual BOOL32 UploadFile(LPCTSTR pszRemoteFile, LPCTSTR pszLocalFile,
                              u32 dwFileType, LPCTSTR pszAgent);

    /*=============================================================================
    函 数 名:ConnectSrv
    功    能:连接服务器
    参    数:无
    注    意:无
    返 回 值:连接是否成功
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/09/29  4.0     王昊    创建
    =============================================================================*/
    virtual BOOL32 ConnectSrv(void);

    /*=============================================================================
    函 数 名:GetRemoteFileSize
    功    能:获取远端文件的大小
    参    数:无
    注    意:无
    返 回 值:远端文件的大小
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/09/29  4.0     王昊    创建
    =============================================================================*/
    virtual u32	GetRemoteFileSize(void);

    /*=============================================================================
    函 数 名:GetLocalFileSize
    功    能:获取本地文件的大小
    参    数:无
    注    意:无
    返 回 值:本地文件的大小
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/09/29  4.0     王昊    创建
    =============================================================================*/
    u32	GetLocalFileSize(void);

    /*=============================================================================
    函 数 名:GetWinRemoteFileSize
    功    能:获取远端windows文件大小
    参    数:无
    注    意:无
    返 回 值:远端windows文件大小
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/09/29  4.0     王昊    创建
    =============================================================================*/
    u32 GetWinRemoteFileSize(void);

    /*=============================================================================
    函 数 名:GetVaxRemoteFileSize
    功    能:获取远端VAX文件大小
    参    数:无
    注    意:无
    返 回 值:远端VAX文件大小
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/09/29  4.0     王昊    创建
    =============================================================================*/
    u32 GetVaxRemoteFileSize(void);

public:
    u32         m_dwFtpHead;                    //  FTP传输头--自从InternetConnect之后发送的次数
	BOOL        m_bIsConnect;					//  判断是否已经连接ftp服务器(外部获取)
protected:
    HINTERNET   m_hSession;                     //  应用于InternetOpen
    HINTERNET   m_hConnect;                     //  应用于InternetConnect

    TCHAR       m_aszFtpSrvIp[IP_LEN];          //  FTP服务器的IP地址
    TCHAR       m_aszFtpSrvUser[FTP_USER_LEN];  //  FTP服务器的登录用户
    TCHAR       m_aszFtpSrvPwd[FTP_PWD_LEN];    //  FTP服务器的登录口令
    TCHAR       m_aszProxyName[PROXY_NAME_LEN]; //  代理的名称
    TCHAR       m_aszProxyPwd[PROXY_PWD_LEN];   //  代理的口令
    TCHAR       m_aszRemoteFile[MAX_PATH];      //  远程文件名
    TCHAR       m_aszLocalFile[MAX_PATH];       //  本地文件名
    u16         m_wFtpSrvPort;                  //  FTP服务器的监听端口

    HANDLE      m_hFtpThread;                   //  FTP传输的线程句柄
    LPTSTR      m_pszAgent;                     //  InternetOpen第一个参数
    u32         m_dwFtpThreadId;                //  FTP传输的线程编号
    HWND        m_hWnd;                         //  接收传输进度消息的窗口
    u32         m_dwFileType;		            //  传输的文件类型
    u32         m_dwCurrentFtpSize;             //  当前传输的大小
    u32         m_dwTotalFileSize;              //  文件总大小
    u32         m_dwEventId;                    //  消息号, 由外界定义
    BOOL32      m_bTransfering;                 //  是否正在传输
    BOOL32      m_bDelRemoteFile;               //  FTP下载完毕后是否删除远端文件

    EmFtpDirect m_byFtpDirect;                  //  传输方向, 默认为下载
	BOOL32		m_bIsRenameTransFile;			//  传输过程中有重名名操作   则由重命名后再关闭FTP   by ldy 2013.01.22
	BOOL32		m_bAutoEndFtpFile;				//  多文件传输由外部控制关闭ftp
};

#endif  //  _FTPCTRL_20050929_H_