
/*****************************************************************************
模块名      : CMS控制台
文件名      : commoninterface.cpp
相关文件    : 
文件实现功能: 封装了umclib和cnclib接口，UI与cns和ums的通信统一经过该接口处理,本文件主要封装ums和cns session相关部分
作者        : 俞锦锦
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2011/4/28  1.0          俞锦锦      创建
******************************************************************************/


#include "stdafx.h"
#include "cms.h"
#include "commoninterface.h"
#include "cmsConst.h"
#include "evcmslib.h"
#include "tpmsginit.h"
#include "printCtrl.h"
#include "nmscommon.h"
#include "direct.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
////////////////////////////////////////////////////////////////////// 


 
//线程控制函数
UINT ThreadConnectUms(LPVOID lpParam)
{   
    u16 re= NO_ERROR;
    re = ComInterface->LinkUms() ;
    if ( NO_ERROR != re )
    {    
        if ( ERR_UMC_ACTIVE_CONNECTION ==  re )
        {
            SendMessage( ComInterface->GetRecvWnd() ,UI_UMS_CONNECTED, TRUE, NO_ERROR);
        }
        else
        {
           SendMessage( ComInterface->GetRecvWnd() ,UI_UMS_CONNECTED, FALSE, ERR_UMC_CREATE_TCP_FAIL);
        }
       
    }
   
    return re;
} 


UINT ThreadConnectCns(LPVOID lpParam)
{   
    u16 re= NO_ERROR;
    re = ComInterface->LinkCns();
    if ( re != NO_ERROR )
    {   
        if ( ERR_CNC_ACTIVE_CONNECT ==  re )
        {
            SendMessage( ComInterface->GetRecvWnd() ,UI_CNS_CONNECTED, TRUE, NO_ERROR);
        }
        else
        {
            SendMessage( ComInterface->GetRecvWnd() ,UI_CNS_CONNECTED, FALSE, ERR_CNC_TCPCONNECT);
        }
	}
    
    return re;
} 


CCommonInterface* CCommonInterface::m_pMySelf = NULL;

CCommonInterface::CCommonInterface() :
               //m_pUmsSessionCtrl(NULL),
				 m_pCnsSession(NULL),
			   //m_pConfTemplateCtrl(NULL),
				 m_pUmsConfCtrl(NULL),
			   //m_pTvwCtrl(NULL),
               //m_pUmsConfigCtrl(NULL),
               //m_pUserCtrl(NULL),
				 m_pCnsConfigCtrl(NULL),
				 m_pCnsConfCtrl(NULL),
				 m_pAddrBookCtrl(NULL),
				 m_pCnsUserCtrl(NULL),
				 m_pSipInfoCtrl(NULL),
				 m_pNetMngCtrl(NULL),
				 m_pPortDiagCtrl(NULL),
				 m_pCenterCtrlIF(NULL),
				 //m_tplConfTempList(),
				 m_tplUserList(),
				 m_tConfInfo(),
				 m_tSipRegCfg(),
				 m_emConnectState( emConnectNotStart ),
                 m_tServEthnetInfo(),
                 m_tCurConfTemplate()
                 //m_pNetCfg(NULL)
{ 
//      CNetworkAdapter::InitCriticalSection();
//     	CNetworkAdapter::CreateCurNetCardName();
}

CCommonInterface::~CCommonInterface()
{ 	
	//m_pUmsSessionCtrl = NULL;
	m_pCnsSession = NULL;
	//m_pConfTemplateCtrl = NULL;
	m_pUmsConfCtrl = NULL; 
	//m_pTvwCtrl = NULL; 
	//m_pUmsConfigCtrl = NULL; 
	//m_pUserCtrl = NULL; 
	m_pCnsConfigCtrl = NULL; 
	m_pCnsConfCtrl = NULL;
	m_pAddrBookCtrl = NULL;
	m_pCnsUserCtrl = NULL;
	m_pSipInfoCtrl = NULL;
	m_pNetMngCtrl = NULL;
	m_pPortDiagCtrl = NULL;
	m_pCenterCtrlIF = NULL;
	DestroyCommIF();
    //CNetworkAdapter::DelCriticalSection();
}



BEGIN_MESSAGE_MAP(CCommonInterface, CWnd)
 
  
ON_MESSAGE( UI_CNS_REFRESH_CONFTEMPLATE_LIST, OnRefreshConfTemplateLst )  
ON_MESSAGE( UI_UMS_REFRESH_USER_LIST, OnRefreshUserLst )  

//ums  会议相关
ON_MESSAGE( UI_UMS_UPDATE_CONFINFO ,  OnRefreshConf ) 
ON_MESSAGE( UI_UMS_HANGUP_CONF_RSP ,  OnRefreshConf )   
ON_MESSAGE( UI_UMS_REFRESH_CONFCNS_LIST ,  OnRefreshConfCnsLst )  
ON_MESSAGE( UI_UMS_REFRESH_CONFAUDMIX_LIST ,  OnRefreshConfAudMixLst )  
ON_MESSAGE( UI_UMS_REFRESH_CONFPOLL_LIST ,  OnRefreshConfPollLst ) 
ON_MESSAGE(UI_UMS_CHANGE_SPEAKER_NOTIFY,  OnSpeakerNotify ) 

ON_MESSAGE( UI_UMS_SET_SPEAKER_RSP ,  OnSetSpeakerRsp ) 
ON_MESSAGE( UI_UMS_SET_MUTE_CNS_RSP ,  OnSetMuteCnsRsp ) 
ON_MESSAGE( UI_UMS_SET_QUIET_CNS_RSP ,  OnSetSlienceCnsRsp ) 
ON_MESSAGE( UI_UMS_SET_DUAL_CNS_RSP ,  OnSetDaulCnsRsp ) 
ON_MESSAGE( UI_UMS_DUAL_CNS_NOTIFY ,  OnDaulCnsUpdateNotify )

  
ON_MESSAGE( UI_CNS_REGSIP_NOTIFY ,  OnCnsRegSigServNotify )  
 
ON_MESSAGE( UI_CNS_ETHNETINFO_NOTIFY ,  OnCnsEthnetInfoNotify )  

ON_MESSAGE( UI_CNS_CONNECTED,  OnConnectCns ) 
ON_MESSAGE( UI_CNS_CNSINFO_NOTIFY, OnCnsInfoNotify ) 

ON_MESSAGE( UI_CNS_ADDRBOOK_CHANGED, UpdateAddrBook ) 
ON_MESSAGE( UI_CNS_REFRESH_GLOBAL_ADDRBOOK, OnRefreshGlobalAddrBook )


ON_MESSAGE( UI_TPAD_LOGINUSER_NOTIFY, OnTPadLoginUserNty )
//电视墙
//ON_MESSAGE( UI_UMS_REFRESH_TVW_LIST_NOTITFY, OnRefreshTvw ) 
//ON_MESSAGE( UI_UMS_PLAY_HDU_RSP, OnPlayHduRsp  ) 
//ON_MESSAGE( UI_UMS_STOP_PLAY_HCODE_STREAM_NOTIFY, OnHduCodeStreamNotify) 


END_MESSAGE_MAP()


CCommonInterface* CCommonInterface::GetCommIF()
{
	if ( NULL != m_pMySelf )
	{
		return m_pMySelf ;
	}
	
	m_pMySelf = new CCommonInterface;
	
	if ( NULL != m_pMySelf )
	{
		VERIFY( m_pMySelf->CreateEx( 0, AfxRegisterWndClass(CS_DBLCLKS), _T("CMSVeiw"),
			WS_OVERLAPPEDWINDOW, CRect(10, 10, 10, 10), NULL, NULL, NULL ) );
    } 

	return m_pMySelf;

}


void CCommonInterface::DestroyCommIF()
{   
	m_tplUserList.Clear();           ///<用户列表
	m_tplConfList.clear();           ///<会议列表  解决： Bug00073719:同一个会场开多点会议6个后，无法再挂断该会场。 
	
	m_vctLocalAddrList.clear();       //本地地址簿
	m_vctGlobalAddrList.clear();      //全局地址簿
	m_vctGroupList.clear();
	
	m_vctConfTempList.clear();        //会议模板列表

    if ( NULL != m_pMySelf )
    {
        m_pMySelf->DestroyWindow();
		
        delete m_pMySelf;
        m_pMySelf = NULL;
    }

	DesdroySession();
}
 

 


void CCommonInterface::CreateSession()
{
	InitTpEvent();
 	
	//创建cnssession
	CCncLib::CreateSession( &m_pCnsSession );
	if ( NULL == m_pCnsSession )
	{
		return;
	}

    if ( UIDATAMGR->IsPcVersion() )
    {
        m_pCnsSession->InitEnv( AID_CNC2CNS_APP );
    }
    else
    {
        m_pCnsSession->InitEnv( AID_TPAD_CNC, MAKEIID( AID_TPAD_MSGTRANS, 1 ) );
    }	
	m_pCnsSession->SetNotifyWnd( GetRecvWnd() ) ;

	m_pCnsSession->CncGetInterface( &m_pCnsConfigCtrl );
	if ( m_pCnsConfigCtrl != NULL ) 
	{
		m_pCnsConfigCtrl->SetNotifyWnd( GetRecvWnd() );
	}

	m_pCnsSession->CncGetInterface( &m_pCnsConfCtrl );
	if ( m_pCnsConfCtrl != NULL )
	{
		m_pCnsConfCtrl->SetNotifyWnd( GetRecvWnd() );
	}
     
	m_pCnsSession->CncGetInterface( &m_pUmsConfCtrl ) ;
    if ( m_pCnsConfCtrl != NULL )
    {
        m_pUmsConfCtrl->SetNotifyWnd( GetRecvWnd() );
    }
	
	m_pCnsSession->CncGetInterface( &m_pAddrBookCtrl );
	if ( m_pAddrBookCtrl != NULL )
	{
		m_pAddrBookCtrl->SetNotifyWnd( GetRecvWnd() );
	}

	m_pCnsSession->CncGetInterface( &m_pCnsUserCtrl );
	if ( m_pCnsUserCtrl != NULL )
	{
		m_pCnsUserCtrl->SetNotifyWnd( GetRecvWnd() );
	}
 
	m_pCnsSession->CncGetInterface( &m_pSipInfoCtrl );
	if ( m_pSipInfoCtrl != NULL )
	{
		m_pSipInfoCtrl->SetNotifyWnd( GetRecvWnd() );
	}
	
	m_pCnsSession->CncGetInterface( &m_pNetMngCtrl );
	if ( m_pNetMngCtrl != NULL )
	{
		m_pNetMngCtrl->SetNotifyWnd( GetRecvWnd() );
	}

	m_pCnsSession->CncGetInterface( &m_pPortDiagCtrl );
	if ( m_pPortDiagCtrl != NULL )
	{
		m_pPortDiagCtrl->SetNotifyWnd( GetRecvWnd() );
	}

	m_pCnsSession->CncGetInterface( &m_pCenterCtrlIF );
	if ( m_pCenterCtrlIF != NULL )
	{
		m_pCenterCtrlIF->SetNotifyWnd( GetRecvWnd() );
	}

}


void CCommonInterface::DesdroySession()
{   	
//	DesdoryUmsSession(&m_pUmsSessionCtrl);
    
	CCncLib::DestroySession( &m_pCnsSession );
}


u16 CCommonInterface::Connect( u32 dwIp, u16 nPort, LPCTSTR pStrUserName, LPCTSTR pStrPswd )
{   
	u16 nReCon = NO_ERROR; 

// 	if( NULL == m_pUmsSessionCtrl )
// 	{
// 		return ERR_CMS;
// 	}

    m_tLoginInfo.dwIp = dwIp;
    m_tLoginInfo.nPort = nPort;
    m_tLoginInfo.strName = pStrUserName;
	m_tLoginInfo.strPswd = pStrPswd;
	
	//连接cns
	u16 reConCns = CCommonInterface::ConnectCns( /*dwIp, nPort + 1, pStrUserName, pStrPswd */);
	
// 	if ( NO_ERROR == reConCns )
// 	{
//  		nReCon = NO_ERROR;
// 		m_tLoginInfo.dwIp = dwIp;
// 		m_tLoginInfo.nPort = nPort;
// 		m_tLoginInfo.strName = pStrUserName;
// 		m_tLoginInfo.strPswd = pStrPswd;
// 	}
// 	else
// 	{
// 		//nReCon = ERR_CMS_UI_UMS_LOGIN;
// 		nReCon = ERR_CMS_UI_CNS_LOGIN;
// 	}


	//连接cns
//    u16 reConCns = CCommonInterface::ConnectCns( dwIp, nPort + 1, pStrUserName, pStrPswd );
   
	//当ums和cns都连接成功时，才算连接成功，否则连接失败，返回失败的错误码
// 	if ( NO_ERROR == reConUms && NO_ERROR == reConCns)
// 	{
// 		nReCon =  NO_ERROR;
// 	}
// 	else
// 	{
// 		//nReCon = (reConUms != NO_ERROR? reConUms : reConCns);
//         TRACE("\n[CCommonInterface::Connect] error: reConnectUms=%d, reConnectCns=%d\n",reConUms,reConCns);
//         if ( reConUms != NO_ERROR )
//         {
//             nReCon = ERR_CMS_UI_UMS_LOGIN;
//         }
//         else
//         {
//             nReCon = ERR_CMS_UI_CNS_LOGIN;
//         }
//     }
	
	return nReCon;
} 

 
u16 CCommonInterface::ConnectUms( /*u32 dwIp, u16 nPort, LPCTSTR pStrUserName, LPCTSTR pStrPswd*/ )
{   
    //if( NULL == m_pUmsSessionCtrl )
	//{
    //   return ERR_CMS;
	//}
 
    AfxBeginThread( ThreadConnectUms , NULL );
//	u16 re  = m_pUmsSessionCtrl->ConnectUms( dwIp, nPort, pStrUserName, pStrPswd );

    return 	NO_ERROR;
 
}

u16 CCommonInterface::ConnectCns( /*u32 dwIp, u16 nPort, CString strUserName, CString strPswd*/ )
{   
    if( NULL == m_pCnsSession )
	{
		return ERR_CMS;
    } 
   
    AfxBeginThread( ThreadConnectCns , NULL );
	//u16 re  = m_pCnsSession->ConnectCns( dwIp, nPort, strUserName, strPswd );
	
	return NO_ERROR;
}



u16 CCommonInterface::LinkUms()
{   
    u16 re = ERR_CMS;
    /*
    if ( m_pCnsSession )
    {
        re = m_pUmsSessionCtrl->ConnectUms( m_tLoginInfo.dwIp,  m_tLoginInfo.nPort,
            m_tLoginInfo.strName,  m_tLoginInfo.strPswd );
    }
    */
    return re;
}


u16 CCommonInterface::LinkCns()
{
    u16 re =  ERR_CMS;
    if ( m_pCnsSession )
    {
        re = m_pCnsSession->ConnectCns( m_tLoginInfo.dwIp,  m_tLoginInfo.nPort + 1,
            m_tLoginInfo.strName,  m_tLoginInfo.strPswd );
    }
    return re;
}

//修改系统名称 dyy 2013年8月29日
u16 CCommonInterface::SetTpadSysName( string strSysName )
{
    u16 re = m_pCnsSession->SetTpadSysName( strSysName );
    
    return re;
}

u16 CCommonInterface::ConnectTPad()
{
    if( NULL == m_pCnsSession )
    {
        return ERR_CMS;
    } 

    u32 dwIp = ntohl( inet_addr( "127.0.0.1" ) );

    TTPadSubInfo tTPadSubInfo;
    tTPadSubInfo.dwIp = dwIp;
    tTPadSubInfo.dwPort = TPAD_LISTEN_PORT;
    tTPadSubInfo.emType = emTPad_cnc;

    u16 re = m_pCnsSession->ConnectTPad( tTPadSubInfo );

    return re;
}


 
BOOL CCommonInterface::IsManagerUser()
{
// 	if( NULL == m_pUmsSessionCtrl )
//     {  
// 		return FALSE;
// 	}
// 	
// 	return m_pUmsSessionCtrl->IsManagerUser( );

	if ( m_tLoginInfo.strName.Compare( MANAGER_USER ) == 0 )
	{
		return TRUE;
	}

	return FALSE;
}
 
BOOL32 CCommonInterface::IsConnect( EM_EqType emConnEq /*= emEqUmsCns*/)
{
   BOOL32 re = TRUE;
 
   switch( emConnEq ) 
   {
   case emEqUmsCns:
	   {
		   //if ( NULL == m_pCnsSession  || NULL == m_pUmsSessionCtrl ) 
		   //{
		   //	   return FALSE;
		   //}

           //re = ( m_pCnsSession->IsConnectedCns() && m_pUmsSessionCtrl->IsConnectedUms() );
	   }	   
	   break;
   case emEqUms:
	   {
		   //if ( NULL == m_pUmsSessionCtrl ) 
		   //{
		   //	   return FALSE;
		   //}
		   
           //re = m_pUmsSessionCtrl->IsConnectedUms() ;
	   }
	   break;
   case emEqCns:
	   {
		   if ( NULL == m_pCnsSession ) 
		   {
			   return FALSE;
		   }
		   
           re = m_pCnsSession->IsConnectedCns() ;
	   }
	   break;
   default:
	   re = FALSE;
   }
   
   return re;
}

u16 CCommonInterface::DisConnect( EM_EqType emConnEq /*= emEqUmsCns*/ )
{
   u16 wRe = NO_ERROR;
   if ( NULL == m_pCnsSession ) 
   {
       return FALSE;
   }
   
   BOOL32 bCon = IsConnect( emEqCns );
   if ( bCon )
   {
       wRe = m_pCnsSession->DisconnectCns();
   }

   return wRe;

   /*
   switch( emConnEq ) 
   {
   case emEqUmsCns:
	   {
		   if ( NULL == m_pCnsSession  || NULL == m_pUmsSessionCtrl ) 
		   {
			   return FALSE;
		   }
		   
           BOOL32 bCon = IsConnect( emEqCns );
           if ( bCon )
           {
               wRe = m_pCnsSession->DisconnectCns();
           }
		   
           bCon = IsConnect( emEqUms );
           u16 wRe2 = NO_ERROR;
           if ( bCon )
           {
               wRe2 = m_pUmsSessionCtrl->DisconnectUms(); 
           } 
		   
		   wRe = ( wRe == NO_ERROR ? wRe2:wRe);
	   }
	   
	   break;
   case emEqCns:
	   {
		   if ( NULL == m_pUmsSessionCtrl ) 
		   {
			   return FALSE;
		   }
		   
           BOOL32 bCon = IsConnect( emEqCns );
           if ( bCon )
           {
               wRe = m_pCnsSession->DisconnectCns();
           }
		    
	   }
	   break;
   case emEqUms:
	   {
		   if ( NULL == m_pCnsSession ) 
		   {
			   return FALSE;
		   }
		   
           BOOL32 bCon = IsConnect( emEqUms );
           
           if ( bCon )
           {
               wRe = m_pUmsSessionCtrl->DisconnectUms(); 
           } 
	   }
	   break;
   default:
	   wRe = ERR_CMS;
   }
   
   return wRe;
   */
}
   
u16  CCommonInterface::GetLocalIP( u32 &dwIP )
{ 

	if( NULL == m_pCnsSession )
	{
		return ERR_CMS;
	}
	
	dwIP  =  m_pCnsSession->GetLocalHostIP();
	return NO_ERROR;
}

u16  CCommonInterface::GetLoginIp( u32 &dwIP )
{ 
	
	if( NULL == m_pCnsSession )
	{
		return ERR_CMS;
	}
	
	dwIP  =  m_pCnsSession->GetLoginIp();
	return NO_ERROR;
}

//u16 CCommonInterface::GetConnectedUser( CLoginRequest&  user)
//{  
// 	if( NULL == m_pUmsSessionCtrl )
// 	{
// 		return ERR_CMS;
// 	}
// 	
// 	user= m_pUmsSessionCtrl->GetConnectedUser(); 

//	return NO_ERROR;
//}

u16 CCommonInterface::GetConnectCnsList( TTPCnList& tCnList )
{
	if ( NULL == m_pCnsSession )
	{
		return ERR_CMS;
	}

	tCnList = m_pCnsSession->GetConnectCnsList();

	return NO_ERROR;
}

u16 CCommonInterface::LoginCnsIns( u8 byIns )
{
	if ( NULL == m_pCnsSession )
	{
		return ERR_CMS;
	}
	
	u16 wRe = m_pCnsSession->LoginCnsIns( byIns );
	
	return wRe;
}

BOOL CCommonInterface::PreCreateWindow( CREATESTRUCT& cs )
{
    cs.style &= ~WS_SYSMENU; 
    return CWnd::PreCreateWindow(cs);
}

LRESULT CCommonInterface::DefWindowProc( UINT message, WPARAM wParam, LPARAM lParam )
{
	if ( message > CMS_MSG_BEGIN ) 
	{
	   CMsgDispatch::SendMessage(message,wParam,lParam);
	}

    return CWnd::DefWindowProc( message, wParam, lParam );
}




LRESULT CCommonInterface::OnConnectCns(  WPARAM wParam, LPARAM lParam ) 
{   
	BOOL32 bRe = (BOOL32)wParam;
	if ( bRe )
	{   
		m_emConnectState = emConnectCnsSuc;
		//u16 reConUms = CCommonInterface::ConnectUms(/* m_tLoginInfo.dwIp, m_tLoginInfo.nPort, m_tLoginInfo.strName, m_tLoginInfo.strPswd*/ );
		
		CMsgDispatch::SendMessage( UI_CONNECT_RSP, NO_ERROR, lParam );
	} 
	else
	{
		m_emConnectState = emConnectCnsFail;
		CMsgDispatch::SendMessage( UI_CONNECT_RSP, ERR_CNC_LOGIN_FAIL, lParam) ;
	}
	return NO_ERROR;
}
 


u16 CCommonInterface::GetSipCfg( TTPSipRegistrarCfg& tSipCfg )
{ 
    tSipCfg = m_tSipRegCfg;
    return NO_ERROR;
}

 
u16 CCommonInterface::GetGkCfg( TTPGKCfg& tGkCfg )
{
   if ( m_pCnsConfigCtrl != NULL )
   {
      tGkCfg = m_pCnsConfigCtrl->GetGkCfg();
   }
   
   return NO_ERROR;
}

//get CNS Configure
u16 CCommonInterface::GetLoginInfo( TLoginInfo& tLonginInfo )
{
    tLonginInfo = m_tLoginInfo;

    return NO_ERROR;
}


void CCommonInterface::ClearSipRegInfo( EmGetRegInfoType emType )
{
	if ( emType == emGetRegInfoType_CNS )
	{
		m_vctGlobalAddrList.clear();
	}
	else if ( emType == emGetRegInfoType_UMS )
	{
		m_vctConfTempList.clear();
	}
	else
	{
		m_vctGlobalAddrList.clear();
		m_vctConfTempList.clear();
	}
}


void CCommonInterface::ShutDownOS(BOOL bRestart)
{   
    PrtMsg( 0, emEventTypeCmsWindow, "[CCommonInterface::ShutDownOS]" );
	//DisableTaskMgr( FALSE );
 
#ifndef _DEBUG
    
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;
    
    //   Get   a   token   for   this   process.
    if ( TRUE == OpenProcessToken( GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken ) )
    {
        // Get   the   LUID   for   the   shutdown   privilege.
        LookupPrivilegeValue( NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid );
        
        tkp.PrivilegeCount = 1;     //   one   privilege   to   set
        tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
        
        // Get   the   shutdown   privilege   for   this   process.
        AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0 );
        
        if ( GetLastError() == ERROR_SUCCESS )
        {   
            //   Shut   down   the   system   and   force   all   applications   to   close.
            if( !bRestart )
            {
                if ( TRUE == ExitWindowsEx( EWX_POWEROFF | EWX_FORCE, 0 ) )
                {
                    ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, 0); //关机
                }
            }
            else
            {
                if ( TRUE == ExitWindowsEx( EWX_REBOOT | EWX_FORCE, 0 ) )
                {
                    ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, 0); //关机
                }
            }				
        }
    }
    
#else

   //UINT uExitCode = 0;
   //ExitProcess( uExitCode );
   TerminateProcess(GetCurrentProcess(), 0); 

#endif
    
}

void CCommonInterface::ShutDownCmc( BOOL bRestart /*= FALSE */)
{
    PrtMsg( 0, emEventTypeCmsWindow, "[CCommonInterface::ShutDownCmc]" );
    //UINT uExitCode = 0;
    //ExitProcess( uExitCode );

    //使用ExitProcess在xp中会产生崩溃，改用TerminateProcess
    TerminateProcess(GetCurrentProcess(), 0);   
}

//是否禁用任务管理器
void CCommonInterface::DisableTaskMgr( BOOL bDisable )
{ 
    CString KEY_DisableTaskMgr = "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System";
    CString VAL_DisableTaskMgr = "DisableTaskMgr";
	
    HKEY hk;
    BOOL32 bEnableTaskMgr = FALSE;
    if (  RegOpenKey(HKEY_CURRENT_USER, KEY_DisableTaskMgr, &hk)!=ERROR_SUCCESS )
    {
		//  没有此键，未禁用
        bEnableTaskMgr = FALSE;
    }
    else
    {   
        DWORD val=0;
        DWORD len=4;
        bEnableTaskMgr =  ( RegQueryValueEx(hk, VAL_DisableTaskMgr, NULL, NULL, (BYTE*)&val, &len)==ERROR_SUCCESS && val==1 );
		
    }  
	
    if ( bEnableTaskMgr  !=   bDisable )
    {
        if ( bDisable )
        {
            // 用于禁用任务管理器策略的注册表键值对 
            if (RegOpenKey(HKEY_CURRENT_USER, KEY_DisableTaskMgr,&hk)!=ERROR_SUCCESS)
            {
                RegCreateKey(HKEY_CURRENT_USER, KEY_DisableTaskMgr, &hk);
            }
            
            // 禁用任务管理器（disable TM）： set policy = 1
            DWORD val=1;
            RegSetValueEx(hk, VAL_DisableTaskMgr, NULL, REG_DWORD, (BYTE*)&val, sizeof(val));
        }
        else
        {
            // 启用任务管理器（enable TM）
            RegDeleteValue(hk,VAL_DisableTaskMgr);
        }
    } 
	
}


LRESULT CCommonInterface::OnTPadLoginUserNty( WPARAM wParam, LPARAM lParam )
{
	TPadLoginInfo tLoginInfo = *(TPadLoginInfo*)wParam;
    m_tLoginInfo.strName = tLoginInfo.cUserInfo.GetName();
	m_tLoginInfo.dwIp = tLoginInfo.dwCnsIp;
    return NO_ERROR;
}

u16 CCommonInterface::ConfSignCmd( const BOOL& bOk, u8 byIndex )
{
	u16 re = m_pPortDiagCtrl->ConfSignCmd( bOk, byIndex );
	return re;
}

BOOL CCommonInterface::ExistDir(const CString strDir)
{
	CFileStatus fs;
	return CFile::GetStatus(strDir, fs);
}

BOOL CCommonInterface::CreateDir(CString strDir)
{
	if (ExistDir(strDir))
		return TRUE;
	if (strDir.Right(1) != _T("\\"))
		strDir += _T("\\");
	
	// can not create network directory
	int nPos = strDir.Find(_T(":"));
	if (nPos == -1)
		return FALSE;
	// no need to create drive
	nPos = strDir.Find(_T("\\"), nPos + 1);
	if (nPos + 1 == strDir.GetLength())
		return TRUE;
	
	CFileStatus fs;
	while (nPos < strDir.GetLength() - 1)
	{
		nPos = strDir.Find(_T("\\"), nPos + 1);
		if (!CFile::GetStatus(strDir.Left(nPos), fs))
		{
			if (/*_tmkdir*/_mkdir(strDir.Left(nPos)) == -1)
				return FALSE;
		}
	}
	return TRUE;
}

u16 CCommonInterface::VideoFormatCmd( const TTPVidForamt& tVidForamt )
{
	if ( NULL == m_pPortDiagCtrl )
    {
        return ERR_CMS;
    }
	return m_pPortDiagCtrl->VideoFormatCmd( tVidForamt );
}

u16 CCommonInterface::DualVideoFormatCmd( const TTPVidForamt& tVidForamt )
{
	if ( NULL == m_pPortDiagCtrl )
    {
        return ERR_CMS;
    }
	return m_pPortDiagCtrl->DualVideoFormatCmd( tVidForamt );
}

u16 CCommonInterface::CallRateCmd( const u16 wCallRate )
{
	if ( NULL == m_pPortDiagCtrl )
    {
        return ERR_CMS;
    }
	return m_pPortDiagCtrl->CallRateCmd( wCallRate );
}

u16 CCommonInterface::DualCallRateCmd( const u16 wDualCallRate )
{
	if ( NULL == m_pPortDiagCtrl )
    {
        return ERR_CMS;
    }
	return m_pPortDiagCtrl->DualCallRateCmd( wDualCallRate );
}

u16 CCommonInterface::ConfDisCmd( const BOOL& bDis )
{
	if ( NULL == m_pPortDiagCtrl )
    {
        return ERR_CMS;
    }
	return m_pPortDiagCtrl->ConfDisCmd( bDis );
}

u16 CCommonInterface::ConfPollCmd( const TTPPollInfo& tPollInfo )
{
	if ( NULL == m_pPortDiagCtrl )
    {
        return ERR_CMS;
    }
	return m_pPortDiagCtrl->ConfPollCmd( tPollInfo );
}

u16 CCommonInterface::GetVideoFormatInfo( TTPVidForamt& tVidForamt ) const
{
	if ( NULL == m_pPortDiagCtrl )
    {
        return ERR_CMS;
    }
	tVidForamt = m_pPortDiagCtrl->GetVideoFormatInfo();
	return NO_ERROR;
}

u16 CCommonInterface::GetDualVideoFormatInfo( TTPVidForamt& tVidForamt ) const
{
	if ( NULL == m_pPortDiagCtrl )
    {
        return ERR_CMS;
    }
	tVidForamt = m_pPortDiagCtrl->GetDualVideoFormatInfo();
	return NO_ERROR;
}

u16 CCommonInterface::GetCallRateInfo( u16& wCallRate ) const
{
	if ( NULL == m_pPortDiagCtrl )
    {
        return ERR_CMS;
    }
	wCallRate = m_pPortDiagCtrl->GetCallRate();
	return NO_ERROR;
}

u16 CCommonInterface::GetDualCallRateInfo( u16& wDualCallRate ) const
{
	if ( NULL == m_pPortDiagCtrl )
    {
        return ERR_CMS;
    }
	wDualCallRate = m_pPortDiagCtrl->GetDualCallRate();
	return NO_ERROR;
}

u16 CCommonInterface::GetConfPollInfo( TTPPollInfo& tPollInfo ) const
{
	if ( NULL == m_pPortDiagCtrl )
    {
        return ERR_CMS;
    }
	tPollInfo = m_pPortDiagCtrl->GetConfPollInfo();
	return NO_ERROR;
}

u16 CCommonInterface::GetConfDisInfo( BOOL& bDis ) const
{
	if ( NULL == m_pPortDiagCtrl )
    {
        return ERR_CMS;
    }
	bDis = m_pPortDiagCtrl->GetConfDisInfo();
	return NO_ERROR;
}

u16 CCommonInterface::AudioFormatCmd( const EmTpAudioFormat& emAudioFormat )
{
	if ( NULL == m_pPortDiagCtrl )
    {
        return ERR_CMS;
    }
	return m_pPortDiagCtrl->AudioFormatCmd( emAudioFormat );
}

EmTpAudioFormat CCommonInterface::GetAudioFormatInfo() const
{
	if ( NULL == m_pPortDiagCtrl )
    {
        return emTPAEnd;
    }
	return m_pPortDiagCtrl->GetAudioFormatInfo();
}

BOOL CCommonInterface::IsViewLocalPIP() const
{
	if ( NULL == m_pCnsConfCtrl )
    {
        return FALSE;
    }
	return m_pCnsConfCtrl->IsViewLocalPIP();
}

BOOL CCommonInterface::GetDisplayState() const
{
	if ( NULL == m_pCenterCtrlIF )
    {
        return FALSE;
    }
	return m_pCenterCtrlIF->GetDisplayState();
}
