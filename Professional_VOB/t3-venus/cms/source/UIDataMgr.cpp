// UIDataMgr.cpp: implementation of the CUIDataMgr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cms.h"
#include "UIDataMgr.h"
#include "hzpysearch.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


const String g_stcStrLoginDlg = "LoginDlg";										   ///<登录界面
const String g_stcStrMsgBox = "MsgBox";						  ///<用户交互界面
const String g_stcStrMainFrameDlg = "TPDlg"; 
const String g_stcStrMainMenuDlg = "MainMenu";
const String g_stcStrToolMenuDlg  = "ToolMenuDlg";
const String g_stcStrSimulateCns1Dlg = "SimulateCns1Dlg";			///<一屏模拟会场
const String g_stcStrSimulateCns3Dlg = "SimulateCns3Dlg";		   	///<三屏模拟会场
const String g_stcStrSimulateCns5Dlg = "SimulateCns5Dlg";		 	///<五屏模拟会场  
const String g_stcStrLockScreenDlg = "LockScreenDlg";					 ///<锁屏界面
const String g_stcStrAddrbookDlg = "AddrBookDlg";						 ///<地址簿
const String g_stcStrAddrEditDlg = "AddrEditDlg";
const String g_stcStrConftempDlg = "ConftempDlg";						 ///<会议模板列表
const String g_stcStrCnsLstDlg = "CnsLstDlg";
const String g_stcStrConfCnsCtrlDlg = "ConfCnsCtrlDlg";            ///会议中cns的控制界面
const String g_stcStrVolumCtrlDlg = "VolumCtrlDlg";              //音量控制界面
const String g_stcStrConftempEdtDlg = "ConftempEdtDlg" ;           ///<会议模板编辑界面
const String g_stcStrAudMixDlg = "AudMixDlg";								///<混音界面
const String g_stcStrTvwDlg = "TvwDlg";										 	///<电视墙界面
const String g_stcStrCallDlg = "CallDlg";                                           ///<呼叫
const String g_stcStrConfInfoDlg  = "ConfLstDlg" ;                    ///<会议信息界面
const String g_stcStrTitleBarDlg  = "TitleBar" ;                    ///<标题栏
const String g_stcStrUserManageDlg = "UserManageDlg" ;                ///<用户管理界面
const String g_stcStrUserdefinedDlg = "UserdefinedDlg" ;                ///<用户自定义界面
const String g_stcStrCallingBox = "CallingDlg";                   //呼叫过程中的动画dlg
const String g_stcStrHungupConfPopDlg = "PopDlgHungupConf" ;      //会议列表中挂断会议弹出框
const String g_stcStrAlarmInfoDlg = "AlarmInfoDlg";               //告警消息弹出框
const String g_stcStrConnectCnsDlg = "ConnectCnsDlg";  
const String g_stcStrIpCfgDlg = "IpCfgDlg";                       //配置本机IP
const String g_stcStrVideoDlg = "MediaDlg";                       //video界面
const String g_strSaveLogDlg = "SaveLogDlg";                       //Log download 界面
const String g_strWaitingRefreshDlg = "WaitingRefreshDlg";
const String g_strDualSrcDlg = "DualSrcDlg";
const String g_strSysStandBy = "SysStandByDlg";
const String g_strNetManageCfg = "NetManageCfgDlg";
const String g_strAddrShowOptnDlg = "AddrShowOptnDlg";

const String g_stcStrFuncLstManageMenu = "FuncLstManageMenu";            //菜单列表管理的菜单
const String g_stcStrScrnDisplayMenu = "ScrnDspMenu";            //屏选看菜单
// scheme
const String g_schmMainMenuConfManage = "SchmMainMenuConfManage";   //mainMenu 的会议管理对应的菜单项
const String g_schmMainMenuCnsManageInconfBase = "SchmMainMenuCnsManageInconfBase";   //mainMenu 的会议中会场的基本操作
const String g_schmMainMenuCnsManageInconf = "SchmMainMenuCnsManageInConf";   //mainMenu 的会议中会场的所有会控操作

const string g_schmSimScrPtpConf = "SchmInPtpConf";                   //模拟屏点对点会议方案
const string g_schmSimScrMiltConf = "SchmInMuilPConf";                   //模拟屏多点会议方案

const String g_schmMainMenuSysManage = "SchmMainMenuSysManage";   //mainMenu 的系统管理对应的菜单项
const String g_schmMainMenuCnsManage = "SchmMainMenuCnsManage";                          //mainMenu 的会场管理菜单

const String g_schmMainFrameCnsBkg = "SchmSimulateCnsBkg";                      //模拟会场背景
const String g_schmMainFrameBlankBkg = "SchmBlankBkg";                          //空白背景
const String g_strMainFrameSimulateBkg = "mainFrameimulateCnsBkg.png";          //模拟会场背景
const String g_strMainFrameLoginBkg = "loginDialog.png";                 

const String g_schmMainMenuDisableVideoBtn = "SchmMainMenuDisableVideoBtn" ;                //mainMenu  禁用videobutton
const String g_schmMainMenuEnableVideoBtn = "SchmMainMenuEnableVideoBtn" ;                //mainMenu 用videobutton

const String g_strMainFrameSysCfgBkg = "mainFrameSysCfgBkg.png";                        //系统配置的背景
const String g_strMainFrameConfManageBkg = "mainFrameConfManageBkg.png";                    //会议管理的背景

const String g_strFuncLstData = "FuncLst";                      //功能列表对应的数据 xml


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CUIDataMgr *CUIDataMgr::m_pThis = NULL;
CUIDataMgr::CUIDataMgr():
                        m_strSimulateCnsDlgName(""),
                        m_strSchmMainMenuShow(""),
                        m_tLockScreenInfo(),
                        m_emLocalCnsState (emLocalCnsIdle),    ///<本地cns的当前状态
                        m_bUILockScreen( FALSE ) 

{
    memset( m_achCurConfName, 0, sizeof(m_achCurConfName) );
}

CUIDataMgr::~CUIDataMgr()
{

}


CUIDataMgr* CUIDataMgr::GetSingleTon()
{
    if ( m_pThis == NULL )
    {
        m_pThis = new CUIDataMgr();
    }
    return m_pThis;
}

void CUIDataMgr::SetLockScreenInfo( TLockScreenInfo tInfo )
{
    m_tLockScreenInfo = tInfo;
}

TLockScreenInfo& CUIDataMgr::GetLockScreenInfo()
{
    return m_tLockScreenInfo;
}



BOOL CUIDataMgr::HZPYMatchList( const CString strTextInput,  const CString strTextSrc )
{
	// TODO: Add your control notification handler code here	
	if ( strTextInput.IsEmpty() )
	{
		return TRUE;
	}

	if ( strTextSrc.IsEmpty() )
	{
		return FALSE;
	}
	
	if ( strTextInput.GetLength() > MAX_FIND_HANZI_LEN )
	{
		return FALSE;
	}
		
    char hzstr[ MAX_FIND_HANZI_LEN + 1] = {0};
	
    strcpy( hzstr, strTextSrc );
		
	CHZPYSearch hzpy;
	
	char arrDest[ MAX_FIND_HANZI_LEN + 1 ] = {0};	
    strcpy( arrDest, strTextInput );   //检索内容
	
	BOOL bFind = FALSE;	
	bFind = hzpy.HZPYMatchList(arrDest, hzstr);
	
	return bFind;
}

bool CUIDataMgr::IsPcVersion()
{
	string strVer  = UIFACTORYMGR_PTR->GetVersion();
	int  index = strVer.find("PC",0);
	return index >=0;
}