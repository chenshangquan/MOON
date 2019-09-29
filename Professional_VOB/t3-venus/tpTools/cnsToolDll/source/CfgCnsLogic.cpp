// CfgCnsLogic.cpp: implementation of the CCfgCnsLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CfgCnsLogic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
						

CCfgCnsLogic::CCfgCnsLogic()
: m_strEdtSubMask("CfgCnsDlg/IPCtrlSubMask")				
, m_strNameEdit("CfgCnsDlg/StcNameEdit")
, m_strEdtGateWay("CfgCnsDlg/IPCtrlGateway")
, m_strBtnNATSwitch("CfgCnsDlg/BtnNATSwitch")
, m_strEdtNatIP("CfgCnsDlg/IPCtrlNATIp")
, m_strName164Edit("CfgCnsDlg/StcName164Edit")
, m_strEdtIp("CfgCnsDlg/IPCtrlAddress")						
{
	m_vctWndName.clear();
	m_bNameChange = FALSE;
	m_bCnsIp = FALSE;
	m_bSubMask = FALSE;
	m_bGateWay = FALSE;
}

CCfgCnsLogic::~CCfgCnsLogic()
{

}

void CCfgCnsLogic::RegMsg()
{
	CCfgCnsLogic* pThis = GetSingletonPtr();
	REG_MSG_HANDLER( UI_CNS_REG_NAT_NTY, CCfgCnsLogic::OnUpdateNATNty, pThis, CCfgCnsLogic ); 
	REG_MSG_HANDLER( UI_CNS_ETHNETINFO_NOTIFY, CCfgCnsLogic::OnUpdateEthnetNty, pThis, CCfgCnsLogic );
	REG_MSG_HANDLER( UI_CNS_CNSINFO_NOTIFY, CCfgCnsLogic::OnUpdateCnsInfoNty, pThis, CCfgCnsLogic );
	//����T300֮��Ļظ�
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_UpgradeCns_NTY, CCfgCnsLogic::OnUpgradeCnsNty, pThis, CCfgCnsLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_CONF_NTY, CCfgCnsLogic::OnConfStateNty, pThis, CCfgCnsLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_VERINFO_NTY, CCfgCnsLogic::OnVerInfoNty, pThis, CCfgCnsLogic );	
}

void CCfgCnsLogic::RegCBFun()
{
	CCfgCnsLogic* pThis = GetSingletonPtr();
	REG_DEFAULT_WINDOW_MSG( WM_CNSTOOL_FTPCONFSIGNPROGRESS );
	REG_GOBAL_MEMBER_FUNC( "CCfgCnsLogic::OnUploadProgress", CCfgCnsLogic::OnUploadProgress, pThis, CCfgCnsLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCnsLogic::InitWnd", CCfgCnsLogic::InitWnd, pThis, CCfgCnsLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCnsLogic::OnBtnSave", CCfgCnsLogic::OnBtnSave, pThis, CCfgCnsLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCnsLogic::OnBtnCancel", CCfgCnsLogic::OnBtnCancel, pThis, CCfgCnsLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCnsLogic::OnBtnUpgrade", CCfgCnsLogic::OnBtnUpgrade, pThis, CCfgCnsLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCnsLogic::OnBtnExport", CCfgCnsLogic::OnBtnExport, pThis, CCfgCnsLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCnsLogic::OnBtnSwitchNAT", CCfgCnsLogic::OnBtnSwitchNAT, pThis, CCfgCnsLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCnsLogic::OnChangedName", CCfgCnsLogic::OnChangedName, pThis, CCfgCnsLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCnsLogic::OnChangedE164", CCfgCnsLogic::OnChangedE164, pThis, CCfgCnsLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCnsLogic::OnChangedCnsIp", CCfgCnsLogic::OnChangedCnsIp, pThis, CCfgCnsLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCnsLogic::OnChangedGatewayIp", CCfgCnsLogic::OnChangedGatewayIp, pThis, CCfgCnsLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCnsLogic::OnChangedSubMaskIp", CCfgCnsLogic::OnChangedSubMaskIp, pThis, CCfgCnsLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgCnsLogic::OnChangedNATIp", CCfgCnsLogic::OnChangedNATIp, pThis, CCfgCnsLogic );
}

void CCfgCnsLogic::UnRegFunc()
{
	UN_REG_GOBAL_FUNC( "CCfgCnsLogic::InitWnd" );	
}

bool CCfgCnsLogic::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );	
//	SetCnsInfoData();
//	SetEthnetCfgData();
//	SetNATData();
	UpBtnState();
	
	m_pWnd = UIFACTORYMGR_PTR->GetWindowPtr( g_strCfgCnsDlg );
	if ( NULL != m_pWnd )
	{
		return false;
	}

	return true;
}

void CCfgCnsLogic::Clear()
{
	if ( emFtpEnd != m_emFileFtpStatus )
	{
		m_cFtp.EndFtpFile();
	}
	m_vecConfFile.clear();
	m_vctWndName.clear();
	UpBtnState();
	m_bNameChange = FALSE;
	m_bCnsIp = FALSE;
	m_bSubMask = FALSE;
	m_bGateWay = FALSE;
}

void CCfgCnsLogic::UnRegMsg()
{
	
}

bool CCfgCnsLogic::OnBtnSave( const IArgs& args )
{	
	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{		
		MSG_BOX_OK( _T("�л�������У���������") );
		SetNATData();
		SetCnsInfoData();
		SetEthnetCfgData();
		m_vctWndName.clear();
		UpBtnState();
		OnConfStateNty(0,0);
		return false;	
	}

	bool bSucceed = true;
	bSucceed = SaveNameAndE164();
	if (false == bSucceed)
	{
		return false;
	}
	bSucceed = SaveNet(  );
	if (false == bSucceed)
	{
		return false;
	}
	bSucceed = SaveNAT();
	if (false == bSucceed)
	{
		return false;
	}
	m_vctWndName.clear();
	UpBtnState();
	return true;
}

bool CCfgCnsLogic::OnBtnCancel( const IArgs& args )
{
	SetCnsInfoData();
	SetEthnetCfgData();
	SetNATData();	
	m_vctWndName.clear();
	UpBtnState();

	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{		
		OnConfStateNty(0,0);
		return false;	
	}
	return true;	
}

/*---------------------------------------------------------------------
* �������ƣ�IsCfgCnsChange
* ��    �ܣ��ж�cfgcns�������Ϣ�Ƿ��޸�
* ����˵��������logic֮���ͨ��
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2012/12/29	v1.0		������		����
----------------------------------------------------------------------*/
bool CCfgCnsLogic::IsCfgCnsChange()
{
	s32 n = m_vctWndName.size();
	if ( n > 0 )
	{
		return SaveMsgBox();
	}
  	return true;
}

/*---------------------------------------------------------------------
* �������ƣ�SaveMsgBox
* ��    �ܣ������Ƿ񱣴����Ϣ��
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2012/12/29	v1.0		������		����
----------------------------------------------------------------------*/
bool CCfgCnsLogic::SaveMsgBox()
{
	IArgs args("");
	MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
	MSG_BOX( nMsgBoxRet, "���������޸ģ��Ƿ񱣴����ã�" );	
	if ( MSGBOX_OK == nMsgBoxRet )
	{
		return OnBtnSave(args);		 
	}
	else
	{
		OnBtnCancel(args);
	}
	return true;
}

/*---------------------------------------------------------------------
* �������ƣ�FocusWindow
* ��    �ܣ�������ʾ���λ�����崰��λ��
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2012/12/29	v1.0		������		����
----------------------------------------------------------------------*/
void CCfgCnsLogic::FocusWindow(String strWindow)
{
	UIFACTORYMGR_PTR->SetFocus( strWindow, m_pWndTree );
}

/*---------------------------------------------------------------------
* �������ƣ�SaveNameAndE164
* ��    �ܣ�����᳡���ƺ�E164�Ų���
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2012/12/29	v1.0		������		����
----------------------------------------------------------------------*/
bool CCfgCnsLogic::SaveNameAndE164( /*const IArgs& args*/ )
{
	if ( m_pWndTree == NULL)
	{
		return S_FALSE;
	}
	TTPCnsInfo tCnsInfo;
	LIBDATAMGRPTR->GetLocalCnsInfo( tCnsInfo );
	
	bool bChange = false;
	String strCnsName;
	UIFACTORYMGR_PTR->GetCaption( m_strNameEdit, strCnsName, m_pWndTree );
	if ( strcmp( tCnsInfo.m_achRoomName, strCnsName.c_str() ) != 0 )
	{
		if ( strCnsName.length() <= 0 )
		{
			MSG_BOX_OK("�᳡���Ʋ���Ϊ��");
			FocusWindow(m_strNameEdit);
			return false;
		}
		if ( IsAllE164Number( strCnsName ) )
		{
			MSG_BOX_OK("�᳡���Ʋ���ȫΪ���ּ�*#,��");
			FocusWindow(m_strNameEdit);
			return false;
		}
		if ( !IsValidTPStr( strCnsName ) )
		{ 
			CString cstr; 
			cstr.Format( "�᳡���Ʋ����԰����ո������е������ַ� [ %s ]", INVALID_ALIAS_FOR_SHOW );			
			MSG_BOX_OK( (String)cstr );
			FocusWindow(m_strNameEdit);
			return false;
		}
		bChange = true;
		m_bNameChange = TRUE;
	}
	
	String strCnsNumber;
	UIFACTORYMGR_PTR->GetCaption( m_strName164Edit, strCnsNumber, m_pWndTree );	
	if ( strcmp( tCnsInfo.m_achE164, strCnsNumber.c_str() ) != 0 )
	{
		CString cstrE164 = "";
		cstrE164.Format( "%s", strCnsNumber.c_str() );
		if ( !cstrE164.IsEmpty() && !CCallAddr::IsValidE164(cstrE164) )
		{
			MSG_BOX_OK("�᳡���벻�Ϸ���E164��ֻ�ܰ������ּ�*#,��");
			FocusWindow(m_strName164Edit);
			return false;
		}
		bChange = true;
	}
	
	if ( bChange )
	{		
		TTPCnsInfo tUpCnsInfo;
		strncpy( tUpCnsInfo.m_achRoomName, strCnsName.c_str(), sizeof( tUpCnsInfo.m_achRoomName ) );
		strncpy( tUpCnsInfo.m_achE164, strCnsNumber.c_str(), sizeof( tUpCnsInfo.m_achE164 ) );
 
// 		//����̨��ͼƬ���ϴ�
// 		if ( strcmp( tCnsInfo.m_achRoomName, strCnsName.c_str() ) != 0 )		//����E164�Ÿı���᳡���Ʋ�������
// 		{
// 			CString strFullPath = GetModuleFullPath();
// 			
// 			CString str1080Path = strFullPath + "confname1080.bmp";
// 			BOOL bSuccess1 = ConfSign->MakeImgByChar( strCnsName.c_str(), "����", FontStyleBold, Color(255,235,0), Color(0,0,0), 
// 				Color(255,255,255), 48, 2, (LPCSTR)str1080Path );
// 			
// 			CString str720Path = strFullPath + "confname720.bmp";
// 			BOOL bSuccess2 = ConfSign->MakeImgByChar( strCnsName.c_str(), "����", FontStyleBold, Color(255,235,0), Color(0,0,0), 
// 				Color(255,255,255), 32, 2, (LPCSTR)str720Path );
// 			
// 			if ( bSuccess1 && bSuccess2 )
// 			{	
// 				m_vecConfFile.clear();
// 				m_vecConfFile.push_back("confname1080.bmp");
// 				m_vecConfFile.push_back("confname720.bmp");
// 				if ( !UploadCore("/usr/conf/", (String)GetModuleFullPath()+m_vecConfFile.at(0), m_vecConfFile.at(0)) )
// 				{
// 					//OspPrintf( TRUE, FALSE, "\nδ��ʼftp������ϴ�ͼƬʧ��\n" );
// 					PrtMsg( 0, emEventTypeCmsWindow, "%s��û��ʼ����ftp�����ʧ�ܣ�", m_vecConfFile.at(0).c_str() );
// 				}		
// 			} 
// 			else if ( !bSuccess1 && bSuccess2 )
// 			{
// 				MSG_BOX_OK( "1080P̨��ͼƬ����ʧ��" );
// 			}
// 			else if ( bSuccess1 && !bSuccess2 )
// 			{
// 				MSG_BOX_OK( "720P̨��ͼƬ����ʧ��" );
// 			}
// 		}

		u16 wRet = COMIFMGRPTR->UpdateCnsInfo( tUpCnsInfo, 1 );
		if (wRet != NO_ERROR)
		{
			WARNMESSAGE( "����᳡����������ʧ��" );
			return false;
		}
	}
	return true;
}

/*---------------------------------------------------------------------
* �������ƣ�SaveNet
* ��    �ܣ�������������
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2012/12/29	v1.0		������		����
----------------------------------------------------------------------*/
bool CCfgCnsLogic::SaveNet()
{
	//�������ú�NAT����
	Value_IpEditData valCNSIp;
    UIFACTORYMGR_PTR->GetPropertyValue(valCNSIp, m_strEdtIp, m_pWndTree); 
	
	Value_IpEditData valSubMask;
    UIFACTORYMGR_PTR->GetPropertyValue(valSubMask, m_strEdtSubMask, m_pWndTree); 

	Value_IpEditData valGateway;
    UIFACTORYMGR_PTR->GetPropertyValue(valGateway, m_strEdtGateWay, m_pWndTree); 

	TTPEthnetInfo tOldEthnetInfo;
	LIBDATAMGRPTR->GetEthnetCfg( tOldEthnetInfo );	

	if ( htonl( valCNSIp.dwIP ) != tOldEthnetInfo.dwIP || htonl( valSubMask.dwIP ) != tOldEthnetInfo.dwMask
		|| htonl( valGateway.dwIP ) != tOldEthnetInfo.dwGateWay || m_bCnsIp || m_bGateWay || m_bSubMask )
	{
		//Ч��IP
		String strCaption;
		UIFACTORYMGR_PTR->GetCaption( m_strEdtIp, strCaption, m_pWndTree );
		if ( strCaption.empty() )
		{  
			MSG_BOX_OK( "CNS IP��ַ����Ϊ��" );
			FocusWindow(m_strEdtIp);
			return false;
		}		
		if ( !CCallAddr::IsValidIpV4( valCNSIp.dwIP ) )
        {		
			MSG_BOX_OK( "CNS IP��ַ�Ƿ�" );
			FocusWindow(m_strEdtIp);
			return false;
		}
		CString str;		
		if ( !CCallAddr::IsValidCallIP( valCNSIp.dwIP, str, 0 ) ) 
		{			
			MSG_BOX_OK( (String)str );
			FocusWindow(m_strEdtIp);
			return false;
		}
		//Ч����������
		UIFACTORYMGR_PTR->GetCaption( m_strEdtSubMask, strCaption, m_pWndTree );
		if ( strCaption.empty() )
		{  
			MSG_BOX_OK( "�������벻��Ϊ��" );
			FocusWindow(m_strEdtSubMask);
			return false;
		}
		if ( !CCallAddr::IsValidIpMask(valSubMask.dwIP) )
		{
			MSG_BOX_OK( "����������Ч������������������ڵģ���������Ч������" );
			FocusWindow(m_strEdtSubMask);
			return false;
		}
		if ( !CCallAddr::IsValidDevIP( valCNSIp.dwIP, valSubMask.dwIP, str, 0 ) )
		{

			MSG_BOX_OK( (String)str );
			FocusWindow(m_strEdtSubMask);
			return false;
		}		
		//Ч������
		UIFACTORYMGR_PTR->GetCaption( m_strEdtGateWay, strCaption, m_pWndTree );
		if ( !strCaption.empty() && !CCallAddr::IsValidIpV4( valGateway.dwIP ) )
		{
			MSG_BOX_OK( "����IP��ַ�Ƿ�" );
			FocusWindow(m_strEdtGateWay);
			return false;
		}
		if ( !strCaption.empty() )
		{
			DWORD dwNetID = valCNSIp.dwIP & valSubMask.dwIP;
			DWORD dwNetGate = valGateway.dwIP & valSubMask.dwIP;
			if ( dwNetGate != dwNetID )
			{
				MSG_BOX_OK( "���ز�����IP��ַ���������붨���ͬһ�������" );
				FocusWindow(m_strEdtGateWay);
				return false; 
			}
		}
//		MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
//		MSG_BOX( nMsgBoxRet,"�޸��������ú��������������������ȷ�Ϻ���ȷ��" );
//		if ( MSGBOX_OK == nMsgBoxRet )
//		{
//			return SaveEthnetCfg();
//		}
//		else
//		{
//			SetEthnetCfgData();
//		}
		SaveEthnetCfg();
	}
	return true;
}

bool CCfgCnsLogic::SaveNAT()
{	
	bool bUseNAT = false;
    UIFACTORYMGR_PTR->GetSwitchState( m_strBtnNATSwitch, bUseNAT, m_pWndTree );
	
	Value_IpEditData valNatIp;
	UIFACTORYMGR_PTR->GetPropertyValue(valNatIp, m_strEdtNatIP, m_pWndTree); 
	
	TTPNatCfg tOldNatInfo;
	LIBDATAMGRPTR->GetNATCfg(tOldNatInfo);

	//У��NATIP
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtNatIP, strCaption, m_pWndTree );

	if ( !CCallAddr::IsValidCallIP( valNatIp.dwIP ) && !strCaption.empty() ) 
	{
		MSG_BOX_OK( "NAT��ַ�Ƿ�" );
		FocusWindow(m_strEdtNatIP);
		return false;
	}

	if ( htonl(valNatIp.dwIP) != tOldNatInfo.dwNatIP || bUseNAT != (bool)tOldNatInfo.bUsed )
	{
		TTPNatCfg tNatInfo;
		tNatInfo.bUsed = bUseNAT;
		tNatInfo.dwNatIP = htonl(valNatIp.dwIP);
		
		u16 wRet = COMIFMGRPTR->UpdateNATCfg(tNatInfo);
		if (wRet != NO_ERROR)
		{
			WARNMESSAGE( "����NAT����������ʧ��" );
			return false;
		}		
	}
	return true;
}

bool CCfgCnsLogic::OnBtnUpgrade( const IArgs& args )
{	
	UIFACTORYMGR_PTR->LoadScheme( "SchmImpCommonClean", NULL, g_stcStrImpCommonDlg );
	UIFACTORYMGR_PTR->LoadScheme( "SchUpgradeCns", NULL, g_stcStrImpCommonDlg );
	s32 nDodalResult = UIFACTORYMGR_PTR->Domodal( g_stcStrImpCommonDlg );	
	
	return true;	
}

bool CCfgCnsLogic::OnBtnExport( const IArgs& args )
{
	UIFACTORYMGR_PTR->LoadScheme( "SchmExpCommonClean", NULL, g_stcStrExpCommonDlg );
	UIFACTORYMGR_PTR->LoadScheme( "SchExportConfig", NULL, g_stcStrExpCommonDlg );
	s32 nDodalResult = UIFACTORYMGR_PTR->Domodal( g_stcStrExpCommonDlg );	
	
	return true;
}

bool CCfgCnsLogic::OnBtnSwitchNAT( const IArgs& args )
{
	TTPNatCfg tOldNatInfo;
	LIBDATAMGRPTR->GetNATCfg(tOldNatInfo);

	bool bUseNAT = false;
    UIFACTORYMGR_PTR->GetSwitchState( m_strBtnNATSwitch, bUseNAT, m_pWndTree );
    if ( bUseNAT )
    {
        UIFACTORYMGR_PTR->LoadScheme( "SchmEdit", m_pWndTree, m_strEdtNatIP);  
    }
    else
    {   
        UIFACTORYMGR_PTR->LoadScheme( "SchmNormal", m_pWndTree,m_strEdtNatIP);
    }

	bool bChange = false;
	if ( (BOOL)bUseNAT != tOldNatInfo.bUsed )
	{
		bChange = true;
	}
	CheckData(m_strBtnNATSwitch,bChange);
	return true;	
}

LRESULT CCfgCnsLogic::OnUpdateNATNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_vctWndName.size() > 0 )
	{
		return S_FALSE;
	}
	SetNATData();
	return S_OK;
}

LRESULT CCfgCnsLogic::OnUpdateEthnetNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_vctWndName.size() > 0 )
	{
		return S_FALSE;
	}
	SetEthnetCfgData();
	m_bCnsIp = FALSE;
	m_bSubMask = FALSE;
	m_bGateWay = FALSE;
	return S_OK;
}

bool CCfgCnsLogic::SaveEthnetCfg( )
{
	if ( m_pWndTree == NULL)
	{
		return S_FALSE;
	}
	Value_IpEditData valIp;
    UIFACTORYMGR_PTR->GetPropertyValue(valIp, m_strEdtIp, m_pWndTree); 
	
	Value_IpEditData valSubMask;
    UIFACTORYMGR_PTR->GetPropertyValue(valSubMask, m_strEdtSubMask, m_pWndTree); 
	
	Value_IpEditData valGateway;
    UIFACTORYMGR_PTR->GetPropertyValue(valGateway, m_strEdtGateWay, m_pWndTree); 
		
	TTPEthnetInfo tEthnetInfo;
	tEthnetInfo.bEnable = TRUE;
	tEthnetInfo.dwIP = htonl( valIp.dwIP );
	tEthnetInfo.dwMask = htonl( valSubMask.dwIP );
	tEthnetInfo.dwGateWay = htonl( valGateway.dwIP );
	
	u16 wRet = COMIFMGRPTR->UpdateEthnetCfg( tEthnetInfo );
	if (wRet != NO_ERROR)
	{
		WARNMESSAGE( "������������������ʧ��" );
		return false;
	}	
	return true;
}

LRESULT CCfgCnsLogic::OnUpdateCnsInfoNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_vctWndName.size() > 0 )
	{
		return S_FALSE;
	}
	if ( 0 != wParam )
	{
		TTPCnsInfo tCnsInfo = *(TTPCnsInfo*)wParam;
		EmTPCNSInfoRst emRst = (EmTPCNSInfoRst)lParam;
		
		if ( emRst == emTPCNSInfoSuccess )
		{
			if ( m_bNameChange )
			{
				//����̨��ͼƬ���ϴ�
				CString strFullPath = GetModuleFullPath();
				
				CString str1080Path = strFullPath + "confname1080.bmp";
				BOOL bSuccess1 = ConfSign->MakeImgByChar( tCnsInfo.m_achRoomName, "����", FontStyleBold, Color(255,235,0), Color(0,0,0), 
					Color(255,255,255), 48, 2, (LPCSTR)str1080Path );
				
				CString str720Path = strFullPath + "confname720.bmp";
				BOOL bSuccess2 = ConfSign->MakeImgByChar( tCnsInfo.m_achRoomName, "����", FontStyleBold, Color(255,235,0), Color(0,0,0), 
					Color(255,255,255), 32, 2, (LPCSTR)str720Path );
				
				if ( bSuccess1 && bSuccess2 )
				{	
					m_vecConfFile.clear();
					m_vecConfFile.push_back("confname1080.bmp");
					m_vecConfFile.push_back("confname720.bmp");
					if ( !UploadCore( CNSCONFIG_FILE_PATH, (String)GetModuleFullPath()+m_vecConfFile.at(0), m_vecConfFile.at(0)) )
					{
						COMIFMGRPTR->ConfSignCmd( FALSE, 1 );
						PrtMsg( 0, emEventTypeCmsWindow, "%s��û��ʼ����ftp�����ʧ�ܣ�", m_vecConfFile.at(0).c_str() );
					}		
				} 
				else if ( !bSuccess1 && bSuccess2 )
				{
					MSG_BOX_OK( "1080P̨��ͼƬ����ʧ��" );
				}
				else if ( bSuccess1 && !bSuccess2 )
				{
					MSG_BOX_OK( "720P̨��ͼƬ����ʧ��" );
				}
				m_bNameChange = FALSE;
			}
		}
		else
		{
			CString strName;
			strName.Format( "�᳡%sע��ʧ��:", tCnsInfo.m_achRoomName );
			
			CString strTemp = "�����ظ�";
			
			if ( emRst == emTPCNSRepeatAliasName )
			{
				strTemp = "�����ظ�";
				
				strName = strName + strTemp;			
				//MSG_BOX_OK((String)strName);
				WARNMESSAGE(strName);
				FocusWindow(m_strNameEdit);
				return S_OK;
			}
			else if ( emRst == emTPCNSRepeatE164 )
			{
				strTemp = "E164�����ظ�";
				
				strName = strName + strTemp;			
				//MSG_BOX_OK((String)strName);
				WARNMESSAGE(strName);
				FocusWindow(m_strName164Edit);
				return S_OK;
			}
		}
	}
	SetCnsInfoData();
	return S_OK;
}

LRESULT CCfgCnsLogic::OnUpgradeCnsNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}

    BOOL bSuccess = *(BOOL*)wParam;
	if ( TRUE != bSuccess )
	{
		WARNMESSAGE("����T300ʧ��");
		UIFACTORYMGR_PTR->LoadScheme( "SchmImpCommonClean", NULL, g_stcStrImpCommonDlg );	//����ʧ��,�ָ�����Ϊ��ʼ״̬
	} 
	else
	{
		BOOL bInConf = LIBDATAMGRPTR->IsInConf();
		if ( bInConf )
		{
			MSG_BOX_OK("�����ɹ�����ǰ�᳡���ڿ��ᣬ���Ժ��ֶ�����");
			UIFACTORYMGR_PTR->LoadScheme( "SchmImpCommonClean", NULL, g_stcStrImpCommonDlg );
			s32 nResult = 0;
			UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrImpCommonDlg );
		}
		else
		{
			MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
			MSG_BOX( nMsgBoxRet, "����T300�ɹ����Ƿ�����������" );	
			if ( MSGBOX_OK == nMsgBoxRet )
			{
				if ( bInConf )
				{
					MSG_BOX_OK("�����ɹ�����ǰ�᳡���ڿ��ᣬ���Ժ��ֶ�����");
					UIFACTORYMGR_PTR->LoadScheme( "SchmImpCommonClean", NULL, g_stcStrImpCommonDlg );
					s32 nResult = 0;
					UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrImpCommonDlg );
					return S_OK;
				}
				u16 wRet = COMIFMGRPTR->RebootCns();
				if ( wRet != NO_ERROR )
				{
					WARNMESSAGE( "����cns������ʧ��" );
				}
			}
			else
			{
				UIFACTORYMGR_PTR->LoadScheme( "SchmImpCommonClean", NULL, g_stcStrImpCommonDlg );
				s32 nResult = 0;
				UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrImpCommonDlg );
			}
		}
	}
	return S_OK;
}

bool CCfgCnsLogic::OnChangedName( const IArgs& args )
{
	if (m_pWndTree == NULL)
	{
		return false;
	}
	TTPCnsInfo tCnsInfo;
	LIBDATAMGRPTR->GetLocalCnsInfo( tCnsInfo );

	bool bChange = false;
	String strRoomName;
	UIFACTORYMGR_PTR->GetCaption( m_strNameEdit, strRoomName, m_pWndTree);
	if ( 0 != strcmp( tCnsInfo.m_achRoomName, strRoomName.c_str() ) )
	{
		bChange = true;
	}
	CheckData(m_strNameEdit,bChange);
	return true;	
}

bool CCfgCnsLogic::OnChangedE164( const IArgs& args )
{
	if (m_pWndTree == NULL)
	{
		return false;
	}
	TTPCnsInfo tCnsInfo;
	LIBDATAMGRPTR->GetLocalCnsInfo( tCnsInfo );

	bool bChange = false;
	String strE164Num;
	UIFACTORYMGR_PTR->GetCaption( m_strName164Edit, strE164Num, m_pWndTree);
	if ( 0 != strcmp( tCnsInfo.m_achE164, strE164Num.c_str() ) )
	{
		bChange = true;
	}

	CheckData(m_strName164Edit,bChange);
	return true;	
}

bool CCfgCnsLogic::OnChangedCnsIp( const IArgs& args )
{
	if (m_pWndTree == NULL)
	{
		return false;
	}
	TTPEthnetInfo tOldEthnetInfo;
	LIBDATAMGRPTR->GetEthnetCfg( tOldEthnetInfo );
	in_addr tAddr;
	tAddr.S_un.S_addr = tOldEthnetInfo.dwIP;
	String strOldEthnetInfo = inet_ntoa(tAddr);
	if ( "0.0.0.0" == strOldEthnetInfo )
	{
		strOldEthnetInfo = "";
	}

	bool bChange = false;
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtIp, strCaption, m_pWndTree);
// 	DWORD dwIP = inet_addr(strCaption.c_str());
// 	if ( "" == strCaption )
// 	{
// 		dwIP = 0;
// 	}
// 	if ( strCaption == "0." || strCaption == "00." || strCaption == "000." )
// 	{
// 		MSG_BOX_OK( "0������Ч��.��ָ��һ������1��223���ֵ." );
// 		UIFACTORYMGR_PTR->SetCaption( m_strEdtIp, "1.", m_pWndTree);
// 		Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( strCaption, m_pWndTree );
// 		if ( pWnd )
// 		{
// 			(( CEdit *) pWnd)->SetSel( -1 );
// 		}
// 	}			
	if ( /*dwIP != tOldEthnetInfo.dwIP || */strCaption != strOldEthnetInfo )
	{						
		bChange = true;
		m_bCnsIp = TRUE;
	}

	CheckData(m_strEdtIp,bChange);
	return true;	
}

bool CCfgCnsLogic::OnChangedGatewayIp( const IArgs& args )
{
	if (m_pWndTree == NULL)
	{
		return false;
	}
	TTPEthnetInfo tOldEthnetInfo;
	LIBDATAMGRPTR->GetEthnetCfg( tOldEthnetInfo );
	in_addr tAddr;
	tAddr.S_un.S_addr = tOldEthnetInfo.dwGateWay;
	String strOldEthnetInfo = inet_ntoa(tAddr);
	if ( "0.0.0.0" == strOldEthnetInfo )
	{
		strOldEthnetInfo = "";
	}

	bool bChange = false;
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtGateWay, strCaption, m_pWndTree);	
// 	DWORD dwIP = inet_addr(strCaption.c_str());
// 	if ( "" == strCaption )
// 	{
// 		dwIP = 0;
// 	}
	
// 	if ( strCaption == "0." || strCaption == "00." || strCaption == "000." )
// 	{
// 		MSG_BOX_OK( "0������Ч��.��ָ��һ������1��223���ֵ." );
// 		UIFACTORYMGR_PTR->SetCaption( m_strEdtGateWay, "1.", m_pWndTree);
// 		Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( strCaption, m_pWndTree );
// 		if ( pWnd )
// 		{
// 			(( CEdit *) pWnd)->SetSel( -1 );
// 		}
// 	}		
	if ( /*dwIP != tOldEthnetInfo.dwGateWay || */strCaption != strOldEthnetInfo )
	{
		bChange = true;
		m_bGateWay = TRUE;
	}

	CheckData(m_strEdtGateWay,bChange);
	return true;	
}

bool CCfgCnsLogic::OnChangedSubMaskIp( const IArgs& args )
{
	if (m_pWndTree == NULL)
	{
		return false;
	}
	TTPEthnetInfo tOldEthnetInfo;
	LIBDATAMGRPTR->GetEthnetCfg( tOldEthnetInfo );
	in_addr tAddr;
	tAddr.S_un.S_addr = tOldEthnetInfo.dwMask;
	String strOldEthnetInfo = inet_ntoa(tAddr);
	if ( "0.0.0.0" == strOldEthnetInfo )
	{
		strOldEthnetInfo = "";
	}

	bool bChange = false;
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtSubMask, strCaption, m_pWndTree);
// 	DWORD dwIP = inet_addr(strCaption.c_str());
// 	if ( "" == strCaption )
// 	{
// 		dwIP = 0;
// 	}
			
	if ( /*dwIP != tOldEthnetInfo.dwMask || */strCaption != strOldEthnetInfo )
	{
		bChange = true;
		m_bSubMask = TRUE;
	}

	CheckData(m_strEdtSubMask,bChange);
	return true;	
}

bool CCfgCnsLogic::OnChangedNATIp( const IArgs& args )
{
	if (m_pWndTree == NULL)
	{
		return false;
	}	
	TTPNatCfg tOldNatInfo;
	LIBDATAMGRPTR->GetNATCfg(tOldNatInfo);
	in_addr tAddr;
	tAddr.S_un.S_addr = tOldNatInfo.dwNatIP;
	String strOldNatInfo = inet_ntoa(tAddr);
	if ( "0.0.0.0" == strOldNatInfo )
	{
		strOldNatInfo = "";
	}
	
	bool bChange = false;
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtNatIP, strCaption, m_pWndTree);
// 	DWORD dwIP = inet_addr(strCaption.c_str());
// 	if ( "" == strCaption )
// 	{
// 		dwIP = 0;
// 	}
// 	if ( strCaption == "0." || strCaption == "00." || strCaption == "000." )
// 	{
// 		MSG_BOX_OK( "0������Ч��.��ָ��һ������1��223���ֵ." );
// 		UIFACTORYMGR_PTR->SetCaption( m_strEdtNatIP, "1.", m_pWndTree);
// 		Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( strCaption, m_pWndTree );
// 		if ( pWnd )
// 		{
// 			(( CEdit *) pWnd)->SetSel( -1 );
// 		}
// 	}

	if ( /*dwIP != tOldNatInfo.dwNatIP || */strCaption != strOldNatInfo )
	{
		bChange = true;
	}

	CheckData(m_strEdtNatIP,bChange);
	return true;	
}

void CCfgCnsLogic::SetNATData()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}
	TTPNatCfg tNatInfo;
	LIBDATAMGRPTR->GetNATCfg( tNatInfo );

	Value_IpEditData valIp;
	valIp.dwIP = ntohl(tNatInfo.dwNatIP);
	UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtNatIP, m_pWndTree ); 

	UIFACTORYMGR_PTR->SetSwitchState( m_strBtnNATSwitch, tNatInfo.bUsed, m_pWndTree );
    if ( tNatInfo.bUsed )
    {
		BOOL bInConf = LIBDATAMGRPTR->IsInConf();
		if ( !bInConf )
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmEdit", m_pWndTree, m_strEdtNatIP); 
		}
    }
    else
    {   
        UIFACTORYMGR_PTR->LoadScheme( "SchmNormal",  m_pWndTree ,m_strEdtNatIP);
    }
}

void CCfgCnsLogic::SetCnsInfoData()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}
	TTPCnsInfo tCnsInfo;
	LIBDATAMGRPTR->GetLocalCnsInfo( tCnsInfo );
	
	String strRoomName(tCnsInfo.m_achRoomName);
	UIFACTORYMGR_PTR->SetCaption( m_strNameEdit, strRoomName, m_pWndTree);
	
	String strE164Num(tCnsInfo.m_achE164);
	UIFACTORYMGR_PTR->SetCaption( m_strName164Edit, strE164Num, m_pWndTree);
}

void CCfgCnsLogic::SetEthnetCfgData()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}
	TTPEthnetInfo tEthnetInfo;
	LIBDATAMGRPTR->GetEthnetCfg( tEthnetInfo );
	
	Value_IpEditData valIp;
	valIp.dwIP = ntohl(tEthnetInfo.dwIP);
    UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtIp, m_pWndTree ); 
	
	valIp.dwIP = ntohl(tEthnetInfo.dwMask);
    UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtSubMask, m_pWndTree ); 
	
	valIp.dwIP = ntohl(tEthnetInfo.dwGateWay);
    UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtGateWay, m_pWndTree ); 	
}

bool CCfgCnsLogic::OnUploadProgress( const IArgs & arg )
{
	Args_WindowMsg WinMsg = *dynamic_cast<const Args_WindowMsg*>(&arg);
	WindowMsg msg = WinMsg.m_Msg;
	
	m_emFileFtpStatus = static_cast<EmFtpStatus>(msg.wParam);
	
	switch( m_emFileFtpStatus )
	{
	case emFtpBegin:
		{
		}
		break;
	case emFtpTransfer:
		{
		}
		break;
	case emFtpEnd:
		{
			DWORD dwSuccess = static_cast<DWORD>(msg.lParam);     //FTP�ӿ�0Ϊ�ɹ�  Ĭ��ʧ��
			m_cFtp.EndFtpFile();	
			if ( 0 == dwSuccess )
			{
				if ( m_vecConfFile.size() > 0 )
				{
					vector<String>::iterator itr = m_vecConfFile.begin();
					m_vecConfFile.erase(itr);
					if ( m_vecConfFile.size() > 0 )
					{
						if ( !UploadCore( CNSCONFIG_FILE_PATH, (String)GetModuleFullPath()+m_vecConfFile.at(0), m_vecConfFile.at(0)) )
						{
							COMIFMGRPTR->ConfSignCmd( FALSE, 1 );
							PrtMsg( 0, emEventTypeCmsWindow, "%s��û��ʼ����ftp�����ʧ�ܣ�", m_vecConfFile.at(0).c_str() );
						}			
					}
					else
					{
						COMIFMGRPTR->ConfSignCmd( TRUE, 1 );
						PrtMsg( 0, emEventTypeCmsWindow, "2��̨��ͼƬ�ϴ���ϣ�" );
					}
				}
			}
			else
			{	
				COMIFMGRPTR->ConfSignCmd( FALSE, 1 );
				PrtMsg( 0, emEventTypeCmsWindow, "����ftp��%s����ʧ�ܣ�", m_vecConfFile.at(0).c_str() );
				LPTSTR pszMsg = NULL;
				m_cFtp.FormatFtpError( dwSuccess, &pszMsg );
				OspPrintf( TRUE, FALSE, "�����ļ���������ԭ��%s��", pszMsg );
				//MSG_BOX_OK(pszMsg);
				LocalFree( pszMsg );
			}		
		}
		break;
	default:
		{
		}
		break;
	}	
	return true;
}

BOOL CCfgCnsLogic::UploadCore( const String& strRemotePath, const String& strLocalFile, const String& strCheckFileName )
{
	CString strIpAddr;
	
	m_cFtp.RegisterMsgHandle( WM_CNSTOOL_FTPCONFSIGNPROGRESS );
	
	u32 dwIp;
	LIBDATAMGRPTR->GetLoginIp(dwIp);		
	struct in_addr addrIPAddr;
	addrIPAddr.S_un.S_addr = htonl(dwIp);
	strIpAddr = inet_ntoa(addrIPAddr);
	
	BOOL32 bRet = m_cFtp.SetServerParam( strIpAddr, "admin", "admin" );
	if ( !bRet )
	{	
		//MSG_BOX_OK("����FTP�ϴ�������ʧ��!");
		WARNMESSAGE("����FTP�ϴ�������ʧ��!");
		return FALSE;
	}
	
	String strRemoteFilePath = strRemotePath;
	strRemoteFilePath += strCheckFileName;
	
	if ( !m_cFtp.BeginUpload( m_pWnd->GetSafeHwnd(), strRemoteFilePath.c_str(), strLocalFile.c_str(), FTP_TRANSFER_TYPE_BINARY, FTP_AGENT ) )
	{
		//MSG_BOX_OK("�ϴ��ļ�ʧ�ܣ���������!");		
		return FALSE;		
	}
	return TRUE;
}

LRESULT CCfgCnsLogic::OnConfStateNty( WPARAM wparam, LPARAM lparam )
{
	if ( m_vctWndName.size() > 0 && m_pWndTree != NULL )
	{
// 		MSG_BOX_OK("���鿪�������ò����޸ģ�");
// 		SetNATData();
// 		SetCnsInfoData();
// 		SetEthnetCfgData();
// 		m_vctWndName.clear();
// 		UpBtnState();
		return S_FALSE;
	}
	bool bUseNAT = false;
    UIFACTORYMGR_PTR->GetSwitchState( m_strBtnNATSwitch, bUseNAT, m_pWndTree );

	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmConf", m_pWndTree );
		if ( bUseNAT )
		{
			UIFACTORYMGR_PTR->EnableWindow( m_strEdtNatIP, false, m_pWndTree );
		}
	} 
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmNoConf", m_pWndTree );
		if ( bUseNAT )
		{
			UIFACTORYMGR_PTR->EnableWindow( m_strEdtNatIP, true, m_pWndTree );
		}
		else
		{
			UIFACTORYMGR_PTR->EnableWindow( m_strEdtNatIP, false, m_pWndTree );
		}
	}
	return S_OK;
}

LRESULT CCfgCnsLogic::OnVerInfoNty( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	s8* chVerInfo = (s8*)wparam;

	UIFACTORYMGR_PTR->SetCaption( "StcVersionInfo", chVerInfo, m_pWndTree, true);
	return S_OK;
}
