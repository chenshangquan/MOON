// logicMgr.cpp: implementation of the CLogicMgr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cnsToolDll.h"
#include "logicMgr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//template<> CLogicMgr* ISingleTon<CLogicMgr>::ms_pSingleton = 0;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLogicMgr::CLogicMgr()
{

}

CLogicMgr::~CLogicMgr()
{

}

 
void CLogicMgr::CreateLogic()
{
	CMainFrameLogic::GetSingletonPtr()->InitLogic();
	CBasicInfoLogic::GetSingletonPtr()->InitLogic();
	CCfgFrameLogic::GetSingletonPtr()->InitLogic();
	CCfgCnsLogic::GetSingletonPtr()->InitLogic();
	CCfgAudioPortLogic::GetSingletonPtr()->InitLogic();
	CMsgboxDlgLogic::GetSingletonPtr()->InitLogic();
	CDiagInfoLogic::GetSingletonPtr()->InitLogic();
	CCentCtrlLogic::GetSingletonPtr()->InitLogic();
	CDiagTestInfoLogic::GetSingletonPtr()->InitLogic();
	CDiagTestFrameLogic::GetSingletonPtr()->InitLogic();
	CCfgNetMngLogic::GetSingletonPtr()->InitLogic();
	CNetMngOptDlgLogic::GetSingletonPtr()->InitLogic();
	CCameraCtrlLogic::GetSingletonPtr()->InitLogic();
	CAddrbookExpLogic::GetSingletonPtr()->InitLogic();
	CCfgMixLogic::GetSingletonPtr()->InitLogic();
	CCfgServerLogic::GetSingletonPtr()->InitLogic();
	CCfgEqLogic::GetSingletonPtr()->InitLogic();
	CExpCommonDlgLogic::GetSingletonPtr()->InitLogic();
	CImpCommonDlgLogic::GetSingletonPtr()->InitLogic();
	CWarningLogic::GetSingletonPtr()->InitLogic();
	CCfgCallSerLogic::GetSingletonPtr()->InitLogic();
	CCentCfgFrameLogic::GetSingletonPtr()->InitLogic();
	CCentCfgDisplayDlg::GetSingletonPtr()->InitLogic();
}
 

void CLogicMgr::DestroyLogic()
{
	CMsgboxDlgLogic::GetSingletonPtr()->Clear();
	CDiagTestInfoLogic::GetSingletonPtr()->Clear();
	CDiagTestFrameLogic::GetSingletonPtr()->Clear();
	CExpCommonDlgLogic::GetSingletonPtr()->Clear();
	CImpCommonDlgLogic::GetSingletonPtr()->Clear();
	CMainFrameLogic::GetSingletonPtr()->Clear();
	CBasicInfoLogic::GetSingletonPtr()->Clear();
	CCfgFrameLogic::GetSingletonPtr()->Clear();
	CCfgCnsLogic::GetSingletonPtr()->Clear();
	CCfgAudioPortLogic::GetSingletonPtr()->Clear();
	CDiagInfoLogic::GetSingletonPtr()->Clear();
	CCentCtrlLogic::GetSingletonPtr()->Clear();
	CCfgNetMngLogic::GetSingletonPtr()->Clear();
	CNetMngOptDlgLogic::GetSingletonPtr()->Clear();
	CCameraCtrlLogic::GetSingletonPtr()->Clear();
	CAddrbookExpLogic::GetSingletonPtr()->Clear();
	CCfgMixLogic::GetSingletonPtr()->Clear();
	CCfgServerLogic::GetSingletonPtr()->Clear();
	CCfgEqLogic::GetSingletonPtr()->Clear();
	CWarningLogic::GetSingletonPtr()->Clear();
	CCfgCallSerLogic::GetSingletonPtr()->Clear();
	CCentCfgFrameLogic::GetSingletonPtr()->Clear();
	CCentCfgDisplayDlg::GetSingletonPtr()->Clear();
}

void CLogicMgr::GetLogic( CCfgCnsLogic **pLogic )
{
    *pLogic = CCfgCnsLogic::GetSingletonPtr();	
}

void CLogicMgr::GetLogic( CCfgAudioPortLogic **pLogic )
{
    *pLogic = CCfgAudioPortLogic::GetSingletonPtr();	
}

 