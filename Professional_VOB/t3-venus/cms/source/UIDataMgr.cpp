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


const String g_stcStrLoginDlg = "LoginDlg";										   ///<��¼����
const String g_stcStrMsgBox = "MsgBox";						  ///<�û���������
const String g_stcStrMainFrameDlg = "TPDlg"; 
const String g_stcStrMainMenuDlg = "MainMenu";
const String g_stcStrToolMenuDlg  = "ToolMenuDlg";
const String g_stcStrSimulateCns1Dlg = "SimulateCns1Dlg";			///<һ��ģ��᳡
const String g_stcStrSimulateCns3Dlg = "SimulateCns3Dlg";		   	///<����ģ��᳡
const String g_stcStrSimulateCns5Dlg = "SimulateCns5Dlg";		 	///<����ģ��᳡  
const String g_stcStrLockScreenDlg = "LockScreenDlg";					 ///<��������
const String g_stcStrAddrbookDlg = "AddrBookDlg";						 ///<��ַ��
const String g_stcStrAddrEditDlg = "AddrEditDlg";
const String g_stcStrConftempDlg = "ConftempDlg";						 ///<����ģ���б�
const String g_stcStrCnsLstDlg = "CnsLstDlg";
const String g_stcStrConfCnsCtrlDlg = "ConfCnsCtrlDlg";            ///������cns�Ŀ��ƽ���
const String g_stcStrVolumCtrlDlg = "VolumCtrlDlg";              //�������ƽ���
const String g_stcStrConftempEdtDlg = "ConftempEdtDlg" ;           ///<����ģ��༭����
const String g_stcStrAudMixDlg = "AudMixDlg";								///<��������
const String g_stcStrTvwDlg = "TvwDlg";										 	///<����ǽ����
const String g_stcStrCallDlg = "CallDlg";                                           ///<����
const String g_stcStrConfInfoDlg  = "ConfLstDlg" ;                    ///<������Ϣ����
const String g_stcStrTitleBarDlg  = "TitleBar" ;                    ///<������
const String g_stcStrUserManageDlg = "UserManageDlg" ;                ///<�û��������
const String g_stcStrUserdefinedDlg = "UserdefinedDlg" ;                ///<�û��Զ������
const String g_stcStrCallingBox = "CallingDlg";                   //���й����еĶ���dlg
const String g_stcStrHungupConfPopDlg = "PopDlgHungupConf" ;      //�����б��йҶϻ��鵯����
const String g_stcStrAlarmInfoDlg = "AlarmInfoDlg";               //�澯��Ϣ������
const String g_stcStrConnectCnsDlg = "ConnectCnsDlg";  
const String g_stcStrIpCfgDlg = "IpCfgDlg";                       //���ñ���IP
const String g_stcStrVideoDlg = "MediaDlg";                       //video����
const String g_strSaveLogDlg = "SaveLogDlg";                       //Log download ����
const String g_strWaitingRefreshDlg = "WaitingRefreshDlg";
const String g_strDualSrcDlg = "DualSrcDlg";
const String g_strSysStandBy = "SysStandByDlg";
const String g_strNetManageCfg = "NetManageCfgDlg";
const String g_strAddrShowOptnDlg = "AddrShowOptnDlg";

const String g_stcStrFuncLstManageMenu = "FuncLstManageMenu";            //�˵��б����Ĳ˵�
const String g_stcStrScrnDisplayMenu = "ScrnDspMenu";            //��ѡ���˵�
// scheme
const String g_schmMainMenuConfManage = "SchmMainMenuConfManage";   //mainMenu �Ļ�������Ӧ�Ĳ˵���
const String g_schmMainMenuCnsManageInconfBase = "SchmMainMenuCnsManageInconfBase";   //mainMenu �Ļ����л᳡�Ļ�������
const String g_schmMainMenuCnsManageInconf = "SchmMainMenuCnsManageInConf";   //mainMenu �Ļ����л᳡�����л�ز���

const string g_schmSimScrPtpConf = "SchmInPtpConf";                   //ģ������Ե���鷽��
const string g_schmSimScrMiltConf = "SchmInMuilPConf";                   //ģ���������鷽��

const String g_schmMainMenuSysManage = "SchmMainMenuSysManage";   //mainMenu ��ϵͳ�����Ӧ�Ĳ˵���
const String g_schmMainMenuCnsManage = "SchmMainMenuCnsManage";                          //mainMenu �Ļ᳡����˵�

const String g_schmMainFrameCnsBkg = "SchmSimulateCnsBkg";                      //ģ��᳡����
const String g_schmMainFrameBlankBkg = "SchmBlankBkg";                          //�հױ���
const String g_strMainFrameSimulateBkg = "mainFrameimulateCnsBkg.png";          //ģ��᳡����
const String g_strMainFrameLoginBkg = "loginDialog.png";                 

const String g_schmMainMenuDisableVideoBtn = "SchmMainMenuDisableVideoBtn" ;                //mainMenu  ����videobutton
const String g_schmMainMenuEnableVideoBtn = "SchmMainMenuEnableVideoBtn" ;                //mainMenu ��videobutton

const String g_strMainFrameSysCfgBkg = "mainFrameSysCfgBkg.png";                        //ϵͳ���õı���
const String g_strMainFrameConfManageBkg = "mainFrameConfManageBkg.png";                    //�������ı���

const String g_strFuncLstData = "FuncLst";                      //�����б��Ӧ������ xml


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CUIDataMgr *CUIDataMgr::m_pThis = NULL;
CUIDataMgr::CUIDataMgr():
                        m_strSimulateCnsDlgName(""),
                        m_strSchmMainMenuShow(""),
                        m_tLockScreenInfo(),
                        m_emLocalCnsState (emLocalCnsIdle),    ///<����cns�ĵ�ǰ״̬
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
    strcpy( arrDest, strTextInput );   //��������
	
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