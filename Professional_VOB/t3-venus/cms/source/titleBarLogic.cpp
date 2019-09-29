// titleBarLogic.cpp: implementation of the CTitleBarLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cms.h"
#include "titleBarLogic.h"
#include "sysTime.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
u16   g_wConfTimerID;                      //会议计时的timer 的handle
u16   g_wLocalTimerID;                      //本地时间的timer 的handle

const String CTitleBarLogic::m_stcStrCnsName = "StcTitle";

const String CTitleBarLogic::m_stcStrMuteIcon = "StcMute";
const String CTitleBarLogic::m_stcStrQuietIcon = "StcQuiet";
const String CTitleBarLogic::m_stcStrDualIcon = "StcDaul";
const String CTitleBarLogic::m_stcStrSpeakerIcon = "StcSpoksPerson";

const String CTitleBarLogic::m_stcStrConfTime = "StcConfTime";
const String CTitleBarLogic::m_stcStrDate = "StcDate";      //系统日期
const String CTitleBarLogic::m_stcStrTime = "StcTime";      //系统时间 
 
CTitleBarLogic *CTitleBarLogic::m_pLogic = NULL;


 

VOID   CALLBACK   CBTimerFun(  HWND   hwnd,   UINT   uMsg, UINT_PTR  idEvent, DWORD   dwTime  )
{  
    
    if ( idEvent == g_wConfTimerID)
    {
        CTitleBarLogic::GetLogicPtr()->UpdateConfTime();
    }
    else if ( idEvent == g_wLocalTimerID )
    {
        CTitleBarLogic::GetLogicPtr()->UpdateSysTime();
    } 
     
}


CTitleBarLogic::CTitleBarLogic():
                      m_dwConfStartTime(0),
                      m_nElapse( 1000 ),
                      m_tCurConf()
{
    g_wConfTimerID = 0;
    g_wLocalTimerID = 0;
}

CTitleBarLogic::~CTitleBarLogic()
{
    if ( m_pLogic != NULL )
    {   
        UnRegMsg();
        UnRegFunc();
        delete m_pLogic;
        m_pLogic = NULL; 
    }
}


CTitleBarLogic* CTitleBarLogic::GetLogicPtr()
{
    if ( m_pLogic == NULL )
    {  
        m_pLogic = new CTitleBarLogic();   
    }
    
    return m_pLogic;
}

void CTitleBarLogic::RegMsg()
{
    //cns 信息
    REG_MSG_HANDLER( UI_CNS_CNSINFO_NOTIFY, CTitleBarLogic::OnCnsInfoNotify, m_pLogic, CTitleBarLogic );
	REG_MSG_HANDLER( UI_CNS_ROOMOFFLINE, CTitleBarLogic::OnCnsInfoNotify, m_pLogic, CTitleBarLogic );
  
    //会议状态
    REG_MSG_HANDLER( UI_CNS_CONFSTATE_NOTIFY,CTitleBarLogic::OnConfStateNotify , m_pLogic, CTitleBarLogic  );
    REG_MSG_HANDLER( UI_UMS_UPDATE_CONFINFO, CTitleBarLogic::OnConfStateNotify, m_pLogic, CTitleBarLogic  );
    REG_MSG_HANDLER( UI_UMS_REFRESH_CONFCNS_LIST, CTitleBarLogic::OnConfStateNotify, m_pLogic, CTitleBarLogic  );
    
    //静音 哑音通知
    REG_MSG_HANDLER( UI_CNS_QUITE_MUTE, CTitleBarLogic::OnVoiceNotify, m_pLogic, CTitleBarLogic  );

    //双流通知
    REG_MSG_HANDLER( UI_UMS_DUAL_CNS_NOTIFY, CTitleBarLogic::OnDualNotify, m_pLogic, CTitleBarLogic  );
	REG_MSG_HANDLER( UI_CNS_DUAL_STATE_NOTIFY, CTitleBarLogic::OnDualNotify, m_pLogic, CTitleBarLogic  );
  
	//发言人更新
	REG_MSG_HANDLER( UI_UMS_CHANGE_SPEAKER_NOTIFY, CTitleBarLogic::OnChangeSpeakerNotify, m_pLogic, CTitleBarLogic  );  

	//修改时间通知
	REG_MSG_HANDLER( UI_CMS_MODIFY_SYSTEM_TIME,CTitleBarLogic::OnModifySysTimeNotify, m_pLogic, CTitleBarLogic  );  
}

void CTitleBarLogic::UnRegMsg()
{
    
}

bool CTitleBarLogic::RegCBFun()
{   	 
    REG_GOBAL_MEMBER_FUNC( "CTitleBarLogic::InitWnd", CTitleBarLogic::InitWnd, m_pLogic, CTitleBarLogic);
    REG_GOBAL_MEMBER_FUNC( "CTitleBarLogic::BtnSaveToFileClick", CTitleBarLogic::BtnSaveToFileClick, m_pLogic, CTitleBarLogic ) ; 
    
    return true;
}

bool CTitleBarLogic::UnRegFunc()
{
    //	UN_REG_GOBAL_FUNC( "CConftempEdtLogic::InitWnd" );
    return true;
}

 
bool CTitleBarLogic::InitWnd(  const IArgs & arg )
{   
    CWndLogicBase::InitWnd( arg );
    //Init();   
    
    return true;
}

bool CTitleBarLogic::ShowWindow( BOOL32 bShow )
{
    if ( bShow )
    {       
        Init();
        UIManagePtr->ShowWindow( g_stcStrTitleBarDlg );      
    }
    else
    {
        UnInit();
        UIManagePtr->ShowWindow( "", false, m_pWndTree );
    }

    return true;
}

void CTitleBarLogic::Init()
{
    UpdateSysTime();
    g_wLocalTimerID = SetTimer( NULL, 0, 1000, CBTimerFun );
    
    OnCnsInfoNotify( 0 , 0 );  
    OnConfStateNotify( 0 , 0  );
}


void CTitleBarLogic::UnInit()
{
    KillTimer( NULL, g_wLocalTimerID );
    g_wLocalTimerID = 0;
    
    KillTimer( NULL, g_wConfTimerID );
    g_wConfTimerID = 0;
    
    m_tmConfDuration = 0;

    UIManagePtr->ShowWindow("", false, m_pWndTree );
    UIManagePtr->SetCaption( m_stcStrCnsName, "", m_pWndTree ); 
    UIManagePtr->LoadScheme("", m_pWndTree, "" );  
    m_tCurConf.Clear();  
}

bool CTitleBarLogic::BtnSaveToFileClick( const IArgs & arg )
{
    return  UIManagePtr->SaveToFile( g_stcStrTitleBarDlg  );  
}

void CTitleBarLogic::Clear()
{
	if ( m_pWndTree != NULL )
    { 
        ShowWindow( FALSE );
        
	}	
}


HRESULT CTitleBarLogic::OnCnsInfoNotify( WPARAM wparam, LPARAM lparam )
{  
	if ( m_pWndTree != NULL )
	{   
		TTPCnsInfo tCnsInfo;
		BusinessManagePtr->GetLocalCnsInfo( tCnsInfo );
     
		UIManagePtr->SetCaption( m_stcStrCnsName, tCnsInfo.m_achRoomName, m_pWndTree, TRUE );
	}
	return NO_ERROR;
}

/* 静音哑音通知  
	wparam = bQuite 	是静音还是哑音.TRUE 静音， FALSE 哑音
	lparam = bOn		是开启还是关闭.开启静音使当前没有音频输出,反之是关闭静音*/
HRESULT CTitleBarLogic::OnVoiceNotify( WPARAM wparam, LPARAM lparam)
{   
    if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }
    BOOL32 bInConf = BusinessManagePtr->IsInConf( NULL );

    BOOL32 bQuite =  BusinessManagePtr->IsLocalCnsQuite(); 
    if ( bInConf && bQuite ) 
    {
        UIManagePtr->LoadScheme( "SchmShowQuietIcon", m_pWndTree, m_stcStrQuietIcon );
    }
    else
    {
        UIManagePtr->LoadScheme( "", m_pWndTree, m_stcStrQuietIcon );
    }


    BOOL32 bMute = BusinessManagePtr->IsLocalCnsMute();
    if ( bInConf && bMute )
    {
        UIManagePtr->LoadScheme( "SchmShowMuteIcon", m_pWndTree, m_stcStrMuteIcon );
    }
    else
    {
        UIManagePtr->LoadScheme( "", m_pWndTree, m_stcStrMuteIcon );
    }
    return NO_ERROR;
}

HRESULT CTitleBarLogic::OnDualNotify( WPARAM wparam, LPARAM lparam) 
{   
	if ( m_pWndTree == NULL )
	{
		return NO_ERROR;
	}

	TCMSConf tConfInfo;
	BOOL32 bRe = BusinessManagePtr->IsInConf( &tConfInfo );
	if ( bRe )
	{   
		BOOL32 bIsLocalCnsDual = BusinessManagePtr->IsLocalCnsDual();
		if ( bIsLocalCnsDual ) 
		{           
			UIManagePtr->LoadScheme( "SchmShowDaulIcon", m_pWndTree, m_stcStrDualIcon );
			return NO_ERROR;
		}
	}

	UIManagePtr->LoadScheme( "", m_pWndTree, m_stcStrDualIcon );
	return NO_ERROR;
}

HRESULT CTitleBarLogic::OnConfStateNotify( WPARAM wparam, LPARAM lparam)
{
    if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }

    TCMSConf tonfInfo;
    BOOL32 bInCf = BusinessManagePtr->IsInConf( &tonfInfo ); 

    if ( bInCf && tonfInfo.m_tStartTime != m_tCurConf.m_tStartTime )
    {   
        m_tCurConf = tonfInfo;
        m_dwConfStartTime = tonfInfo.m_tStartTime; 
        AdjustTime( m_dwConfStartTime );
        CTime tmStart( m_dwConfStartTime );
        m_tmConfDuration = 0;
        PrtMsg( 0, emEventTypeCmsWindow, "会议( %s ) 开始时间：%.4d-%.2d-%.2d %.2d:%.2d:%.2d", 
                        tonfInfo.m_achConfName,tmStart.GetYear(), tmStart.GetMonth(),tmStart.GetDay(), tmStart.GetHour(),tmStart.GetMinute(),tmStart.GetSecond() );
        //开始计时
        KillTimer( NULL, g_wConfTimerID );

        UpdateConfTime();
        g_wConfTimerID = SetTimer(NULL,NULL,m_nElapse,CBTimerFun);
        UIManagePtr->LoadScheme( "SchmShowConfTimeIcon", m_pWndTree, m_stcStrConfTime );  
    } 
    
	if( bInCf )
    {   
		m_tCurConf = tonfInfo; 
    }
	else
	{
		//杀掉计时器，并隐藏时间文本
        KillTimer( NULL, g_wConfTimerID );

        UIManagePtr->LoadScheme( "", m_pWndTree, m_stcStrConfTime ); 
        m_tCurConf.Clear(); 
	}
 

    OnChangeSpeakerNotify( tonfInfo.m_wConfID , 0 );
    OnVoiceNotify( 0 , 0 );
    OnDualNotify( 0 , 0 );
    return  NO_ERROR;
}

HRESULT CTitleBarLogic::OnChangeSpeakerNotify( WPARAM wparam, LPARAM lparam)
{
    if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }

    TCMSConf tonfInfo;
    BOOL32 bInCf = BusinessManagePtr->IsInConf( &tonfInfo ); 
    if ( bInCf )
    { 
        bool re = BusinessManagePtr->IsLocalCnsSpeaker( );
        if( re )
        {
			UIManagePtr->LoadScheme( "SchmShowSpoksPersonIcon", m_pWndTree, m_stcStrSpeakerIcon);
        }
        else
        {
            UIManagePtr->LoadScheme( "", m_pWndTree, m_stcStrSpeakerIcon);
        }            
    }
	else
	{
		UIManagePtr->LoadScheme( "", m_pWndTree, m_stcStrSpeakerIcon);
	}
    return  NO_ERROR;
}

HRESULT CTitleBarLogic::OnModifySysTimeNotify( WPARAM wparam, LPARAM lparam)
{
    CString strDate = CSysTime::GetSysDate();
    UIManagePtr->SetCaption( m_stcStrDate, (LPCSTR)strDate, m_pWndTree, TRUE );
    
    CString strTime;
    CSysTime::GetSysTime( strTime );
    UIManagePtr->SetCaption( m_stcStrTime, (LPCSTR)strTime, m_pWndTree, TRUE );

   return  NO_ERROR;

}

void CTitleBarLogic::UpdateSysTime()
{
    CString strDate = CSysTime::GetSysDate();
    UIManagePtr->SetCaption( m_stcStrDate, (LPCSTR)strDate, m_pWndTree );

    CString strTime;
    CSysTime::GetSysTime( strTime );
    UIManagePtr->SetCaption( m_stcStrTime, (LPCSTR)strTime, m_pWndTree, TRUE );

	if ( UIManagePtr->IsVisible( "SysCfgDlg" ) )
	{
		SYSTEMTIME tTime = CSysTime::GetSysTime();
		CMsgDispatch::SendMessage( UI_CMS_UPDATE_SYSTEM_TIME, (WPARAM)&tTime, 0 );
	}
}


void CTitleBarLogic::UpdateConfTime()
{    
    if ( 0 == m_tmConfDuration.GetTotalSeconds() )
    {
        CTime tmStart( m_dwConfStartTime );
        m_tmConfDuration = CTime::GetCurrentTime() - tmStart ;  
        if ( m_tmConfDuration < 0 )
        {
            m_tmConfDuration = 0;
        }
    }
    else
    {  
       m_tmConfDuration += 1;
    } 

    s8 strTime[64] = {0};
    sprintf( strTime, "%.2d:%.2d:%.2d", m_tmConfDuration.GetTotalHours(), m_tmConfDuration.GetTotalMinutes() - m_tmConfDuration.GetTotalHours()*60, m_tmConfDuration.GetTotalSeconds() - m_tmConfDuration.GetTotalMinutes()*60 );

    UIManagePtr->SetCaption( m_stcStrConfTime, strTime, m_pWndTree,TRUE );
     

}


void CTitleBarLogic::AdjustTime( s64 &time )
{
     CTime tmAdust( time );
     CTime tmCur( CTime::GetCurrentTime() );
     if (  tmCur < tmAdust )
     {    
         time = tmCur.GetTime(); 
     }
        
}