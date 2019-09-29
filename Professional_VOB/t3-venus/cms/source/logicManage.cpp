// logicManage.cpp: implementation of the CLogicManage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cms.h"
#include "logicManage.h" 

#include "msgBoxLogic.h"
#include "loginLogic.h"
#include "mainFrameLogic.h"
#include "toolMenuLogic.h" 
#include "conftempLstLogic.h"
#include "lockScreenLogic.h"
#include "audmixLogic.h"
#include "confCtrlLogic.h"
#include "addrbooklogic.h"
#include "addreditlogic.h"
//#include "ConftempEdtLogic.h"
#include "confInfoLogic.h"
#include "simulateCnsLogic.h"
#include "volumCtrlLogic.h"
#include "syscfglogic.h"
#include "ethnetcfglogic.h"
#include "cnscfglogic.h"
#include "regservicelogic.h"
#include "userManageLogic.h"
#include "userDefinedLogic.h"
#include "tvwLogic.h"
#include "callingLogic.h"
#include "alarminfologic.h"
//#include "IpCfgLogic.h"
#include "mainmenulogic.h"
#include "connectcnslogic.h"
#include "VideoLogic.h"
#include "scrnDisplayMenuLogic.h"
#include "regGklogic.h"
#include "timeSetLogic.h"
#include "SaveLogLogic.h"
#include "WaitingRefreshLogic.h"
#include "dualSrcLogic.h"
#include "dualSrcManageLogic.h"
#include "SysStandByLogic.h"
#include "NetManageCfgLogic.h"
#include "updservicelogic.h"
#include "callservercfglogic.h"
#include "callservercfgmodechooselogic.h"
#include "callservercfgshowmodechooselogic.h"
#include "callSerCfgAudioModeLogic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLogicManage*CLogicManage::m_pLogicManage = NULL;

CLogicManage::CLogicManage() :m_tplLogicList()
{

}

CLogicManage::~CLogicManage()
{

}


CLogicManage *CLogicManage::GetLogicManagePtr()
{
	if ( NULL == m_pLogicManage ) 
	{
		m_pLogicManage = new CLogicManage();

        //REG_MSG_HANDLER( UI_UMS_DISCONNECTED, CLogicManage::OnDisConnect, m_pLogicManage, CLogicManage );
        REG_MSG_HANDLER( UI_CNS_DISCONNECTED, CLogicManage::OnDisConnect, m_pLogicManage, CLogicManage );
	} 

	return m_pLogicManage;
}

HRESULT CLogicManage::OnDisConnect( WPARAM wparam, LPARAM lparam ) 
{
    CLoginLogic::GetLogicPtr()->Clear();
	CConnectCnsLogic::GetLogicPtr()->Clear();
    CTitleBarLogic::GetLogicPtr()->Clear();
	CCallingLogic::GetLogicPtr()->Clear();
    CMainFrameLogic::GetLogicPtr()->Clear();  
	CMainMenuLogic::GetLogicPtr()->Clear(); 
    CToolMenuLogic::GetLogicPtr()->Clear();
    CConftempLstLogic::GetLogicPtr()->Clear(); 
    CLockScreenLogic::GetLogicPtr()->Clear(); 
    CConfCnsLstLogic::GetLogicPtr()->Clear();
    CAudmixLogic::GetLogicPtr()->Clear();
    CConfCtrlLogic::GetLogicPtr()->Clear();
    CAddrBookLogic::GetLogicPtr()->Clear();
    CAddrEditLogic::GetLogicPtr()->Clear();
    //CConftempEdtLogic::GetLogicPtr()->Clear();
    //CConfInfoLogic::GetLogicPtr()->Clear();
    CMsgBoxLogic::GetLogicPtr()->Clear();
    CSysCfgLogic::GetLogicPtr()->Clear();
    //CEthnetCfgLogic::GetLogicPtr()->Clear();
    CRegServiceLogic::GetLogicPtr()->Clear();
    CCnsCfgLogic::GetLogicPtr()->Clear();
    CSimulateCnsLogic::GetLogicPtr()->Clear();
    CVolumCtrlLogic::GetLogicPtr()->Clear();
    CUserManageLogic::GetLogicPtr()->Clear();
    //CTvwLogic::GetLogicPtr()->Clear();
    CUserDefinedLogic::GetLogicPtr()->Clear();		
	CAlarmInfoLogic::GetLogicPtr()->Clear();
    CVideoLogic::GetLogicPtr()->Clear();
    CScrnDisplayMenuLogic::GetLogicPtr()->Clear();
    //CRegGkLogic::GetLogicPtr()->Clear();
    CTimeSetLogic::GetLogicPtr()->Clear();
    CSaveLog::GetLogicPtr()->Clear();
	CWaitingRefreshLogic::GetLogicPtr()->Clear();
	CDualSrcManageLogic::GetLogicPtr()->Clear();
	CDualSrcLogic::GetLogicPtr()->Clear();
	CSysStandByLogic::GetLogicPtr()->Clear();
	CNetManageCfgLogic::GetLogicPtr()->Clear();
	//CUpdServiceLogic::GetLogicPtr()->Clear();
	CCallServerCfgLogic::GetLogicPtr()->Clear();
	CCallServerCfgModeChooseLogic::GetLogicPtr()->Clear();
	CCallServerCfgShowModeChooseLogic::GetLogicPtr()->Clear();
	CCallSerCfgAudioModeLogic::GetLogicPtr()->Clear();

    return NO_ERROR;
}

void CLogicManage::DestroyLogic( CWndLogicBase *pLogic )
{
   	int nCnt = m_tplLogicList.Size();
	for ( int i = 0; i< nCnt; i++ ) 
	{  
		CWndLogicBase *p = m_tplLogicList.GetAt(i);
		if ( pLogic == p )
		{
			if ( NULL != p )
			{
				delete p;
				p = NULL;
			} 
         
			m_tplLogicList.Delete( i );
			break;
		} 
	}
}


void CLogicManage::DestroyLogic()
{
	int nCnt = m_tplLogicList.Size();
	for ( int i = 0; i< nCnt; i++ ) 
	{  
		CWndLogicBase *p = m_tplLogicList.GetAt(i);
		if ( NULL != p )
		{
			delete p;
			p = NULL;
		} 
	}

	m_tplLogicList.Clear();
}




const  TplArray<CWndLogicBase*>* CLogicManage::GetLogicList() const
{
	return &m_tplLogicList;
}


void CLogicManage::GetLogic( CConfCnsLstLogic  **pLogic )
{
    *pLogic = CConfCnsLstLogic::GetLogicPtr();
}

void CLogicManage::OnNotify( WPARAM wparam ,LPARAM lparam )
{
//	CMsgDispatch::SendMessage()
}

void CLogicManage::CreateLogic()
{  
	CConnectCnsLogic::GetLogicPtr()->InitLogic();
	CLoginLogic::GetLogicPtr()->InitLogic();
    //CIpCfgLogic::GetLogicPtr()->InitLogic();
	
    CTitleBarLogic::GetLogicPtr()->InitLogic();
	CMainFrameLogic::GetLogicPtr()->InitLogic();
	CMainMenuLogic::GetLogicPtr()->InitLogic(); 
    //CToolMenuLogic::GetLogicPtr()->InitLogic();
	CConftempLstLogic::GetLogicPtr()->InitLogic(); 
	CLockScreenLogic::GetLogicPtr()->InitLogic(); 
    CConfCtrlLogic::GetLogicPtr()->InitLogic();
	CConfCnsLstLogic::GetLogicPtr()->InitLogic();
	CAudmixLogic::GetLogicPtr()->InitLogic();
	
	CAddrBookLogic::GetLogicPtr()->InitLogic();
	CAddrEditLogic::GetLogicPtr()->InitLogic();
    //CConftempEdtLogic::GetLogicPtr()->InitLogic();
    //CConfInfoLogic::GetLogicPtr()->InitLogic();
    CMsgBoxLogic::GetLogicPtr()->InitLogic();
	CSysCfgLogic::GetLogicPtr()->InitLogic();
	//CEthnetCfgLogic::GetLogicPtr()->InitLogic();
	CRegServiceLogic::GetLogicPtr()->InitLogic();
	CCnsCfgLogic::GetLogicPtr()->InitLogic();
	CSimulateCnsLogic::GetLogicPtr()->InitLogic();
    CVolumCtrlLogic::GetLogicPtr()->InitLogic();
    CUserManageLogic::GetLogicPtr()->InitLogic();
	//CTvwLogic::GetLogicPtr()->InitLogic();
    CUserDefinedLogic::GetLogicPtr()->InitLogic();
    CCallingLogic::GetLogicPtr()->InitLogic();
	CAlarmInfoLogic::GetLogicPtr()->InitLogic();
    CVideoLogic::GetLogicPtr()->InitLogic();
    CScrnDisplayMenuLogic::GetLogicPtr()->InitLogic();

    //CRegGkLogic::GetLogicPtr()->InitLogic();
    CTimeSetLogic::GetLogicPtr()->InitLogic();
    CToolMenuLogic::GetLogicPtr()->InitLogic();
    CSaveLog::GetLogicPtr()->InitLogic();
	CWaitingRefreshLogic::GetLogicPtr()->InitLogic();
	CDualSrcManageLogic::GetLogicPtr()->InitLogic();
	CDualSrcLogic::GetLogicPtr()->InitLogic();
	CSysStandByLogic::GetLogicPtr()->InitLogic();
	CNetManageCfgLogic::GetLogicPtr()->InitLogic();
	//CUpdServiceLogic::GetLogicPtr()->InitLogic();
	CCallServerCfgLogic::GetLogicPtr()->InitLogic();
	CCallServerCfgModeChooseLogic::GetLogicPtr()->InitLogic();
	CCallServerCfgShowModeChooseLogic::GetLogicPtr()->InitLogic();
	CCallSerCfgAudioModeLogic::GetLogicPtr()->InitLogic();
} 
