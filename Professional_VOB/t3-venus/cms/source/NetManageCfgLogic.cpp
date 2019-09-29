// NetManageCfgLogic.cpp: implementation of the CNetManageCfgLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NetManageCfgLogic.h"
#include "msgBoxLogic.h"
#include "commoninterface.h"

const String CNetManageCfgLogic::m_strListNetMng = "ListNetManage";
const String CNetManageCfgLogic::m_strNMServerIp = "DlgNetManageInfo/IPSvrAddr";
const String CNetManageCfgLogic::m_strNMReadCommunity = "DlgNetManageInfo/EdtRdComName";
const String CNetManageCfgLogic::m_strNMWriteCommunity = "DlgNetManageInfo/EdtWrtComName";
const String CNetManageCfgLogic::m_strNMGetSetPort= "DlgNetManageInfo/EdtRdWrtPort";
const String CNetManageCfgLogic::m_strNMTrapPort = "DlgNetManageInfo/EdtWarnPort";
const String CNetManageCfgLogic::m_strBtnAdd = "BtnAddNetManage";
const String CNetManageCfgLogic::m_strBtnDel = "BtnDelete";
const String CNetManageCfgLogic::m_strBtnModify = "BtnEdit";
const String CNetManageCfgLogic::m_strSchmEdit = "SchmEdit";

CNetManageCfgLogic * CNetManageCfgLogic::m_pLogic = NULL;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNetManageCfgLogic::CNetManageCfgLogic()
{
	m_emNMType = em_NETMNGOPT_IDLE;
}

CNetManageCfgLogic::~CNetManageCfgLogic()
{
	if ( m_pLogic != NULL )
	{   
		UnRegMsg();
		UnRegFunc();
		delete m_pLogic;
		m_pLogic = NULL; 
	}
}


CNetManageCfgLogic* CNetManageCfgLogic::GetLogicPtr()
{
	if ( m_pLogic == NULL )
	{  
		m_pLogic = new CNetManageCfgLogic();   
	}
	
	return m_pLogic;
}

void CNetManageCfgLogic::RegMsg()
{
	REG_MSG_HANDLER( UI_CNSTOOL_ADD_NETMNG_IND, CNetManageCfgLogic::OnAddNetMngRsp, m_pLogic, CNetManageCfgLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_NETMNG_NTY, CNetManageCfgLogic::OnNetMngNty, m_pLogic, CNetManageCfgLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_MODIFY_NETMNG_IND, CNetManageCfgLogic::OnModifyNetMngRsp, m_pLogic, CNetManageCfgLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_DEL_NETMNG_IND, CNetManageCfgLogic::OnDelNetMngRsp, m_pLogic, CNetManageCfgLogic );
}

void CNetManageCfgLogic::UnRegMsg()
{

}

bool CNetManageCfgLogic::RegCBFun()
{  
	REG_GOBAL_MEMBER_FUNC( "CNetManageCfgLogic::InitWnd", CNetManageCfgLogic::InitWnd, m_pLogic, CNetManageCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CNetManageCfgLogic::OnBtnSysCfg", CNetManageCfgLogic::OnBtnSysCfg, m_pLogic, CNetManageCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CNetManageCfgLogic::OnBtnNetManageCfg", CNetManageCfgLogic::OnBtnNetManageCfg, m_pLogic, CNetManageCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CNetManageCfgLogic::OnBtnAddNetManage", CNetManageCfgLogic::OnBtnAddNetManage, m_pLogic, CNetManageCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CNetManageCfgLogic::OnBtnDelete", CNetManageCfgLogic::OnBtnDelete, m_pLogic, CNetManageCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CNetManageCfgLogic::OnClickWebManageItem", CNetManageCfgLogic::OnClickWebManageItem, m_pLogic, CNetManageCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CNetManageCfgLogic::OnBtnEdit", CNetManageCfgLogic::OnBtnEdit, m_pLogic, CNetManageCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CNetManageCfgLogic::OnBtnSave", CNetManageCfgLogic::OnBtnSave, m_pLogic, CNetManageCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CNetManageCfgLogic::OnBtnCancel", CNetManageCfgLogic::OnBtnCancel, m_pLogic, CNetManageCfgLogic );
    
	return true;
}

bool CNetManageCfgLogic::UnRegFunc()
{	
	return true;
}

bool CNetManageCfgLogic::InitWnd( const IArgs & args )
{
	CWndLogicBase::InitWnd( args );	
	if (m_pWndTree == NULL)
	{
		return true;
	}
	vector<TTPNMServerCfg> vecTTPNMServerCfg;
	ComInterface->GetNetMngData( vecTTPNMServerCfg );
	Value_ListNetManage ListNetManage( &vecTTPNMServerCfg, "CNetManageCfgLogic::OnClickWebManageItem" );
	UIManagePtr->SetPropertyValue( ListNetManage, m_strListNetMng, m_pWndTree );
	return true;
}



bool CNetManageCfgLogic::OnBtnSysCfg( const IArgs & args )
{
	UIManagePtr->LoadScheme( "SchmSysCfg", NULL, "SysCfgDlg" );
	return true;
}


bool CNetManageCfgLogic::OnBtnNetManageCfg( const IArgs & args )
{
	if (m_pWndTree == NULL)
	{
		return true;
	}
    if ( ! UIManagePtr->IsVisible( "NetManageCfgDlg/BtnEdit" ) )
    {        
        String strCaption;
        GetCurrentCtrl();

        Args_MsgBox msgArg;
        if (( em_NETMNGOPT_MODIFY == m_emNMType &&  m_tTPNMServerCfgSel.dwNMServerIP != m_tTPNMServerCfgCur.dwNMServerIP ) 
            || ( em_NETMNGOPT_ADD == m_emNMType &&  m_tTPNMServerCfgCur.dwNMServerIP != NULL )  
            || m_tTPNMServerCfgSel.achNMReadCommunity != m_tTPNMServerCfgCur.achNMReadCommunity 
            || m_tTPNMServerCfgSel.achNMWriteCommunity != m_tTPNMServerCfgCur.achNMWriteCommunity 
            || m_tTPNMServerCfgSel.wNMGetSetPort != m_tTPNMServerCfgCur.wNMGetSetPort 
            || m_tTPNMServerCfgSel.WNMTrapPort != m_tTPNMServerCfgCur.WNMTrapPort )
        {
            CString strMsg = "是否对编辑进行保存?";
            msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( "NetManageCfgDlg" );
            int nResul = MSG_BOX( strMsg, TRUE, &msgArg);
            if ( IDOK == nResul )
            {
                if ( !OnBtnSave(args) )
                {
                    return false;
                }
            }
        }
    }

	vector<TTPNMServerCfg> vecTTPNMServerCfg;
	ComInterface->GetNetMngData( vecTTPNMServerCfg );
    memset( &m_tTPNMServerCfgCur, 0, sizeof(TTPNMServerCfg) );
    m_emNMType = em_NETMNGOPT_IDLE;
	UIManagePtr->LoadScheme( "SchmShowNetManageLst", m_pWndTree );

	return true;
}

bool CNetManageCfgLogic::OnClickWebManageItem( const IArgs & args )
{
     if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast<const Args_ClickItemInfo*>(&args) )
     {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetItemData();
        if ( const Data_NetManage *pItemInfo = dynamic_cast<const Data_NetManage*>( pBaseItem->GetUserData() ) )
        {
			m_tTPNMServerCfgSel = pItemInfo->m_tNetListInfo;

		    UIManagePtr->LoadScheme( "SchmShowNetManageInfo", m_pWndTree );

			SetAllCtrl( m_tTPNMServerCfgSel );
        }
	 }
     return true;
}

bool CNetManageCfgLogic::OnBtnEdit( const IArgs & args )
{
	TTPNMServerCfg tTPNMServerCfg;
	GetCurrentCtrl();
    UIManagePtr->LoadScheme( "SchmEdit", m_pWndTree );
	m_emNMType = em_NETMNGOPT_MODIFY;

    return true;
}

bool CNetManageCfgLogic::OnBtnSave( const IArgs & args )
{
	Args_MsgBox msgArg;
	TTPNMServerCfg tTPNMServerCfg;
	bool bGet = GetAllCtrl(tTPNMServerCfg);
	if ( bGet == true )
	{
		if( em_NETMNGOPT_ADD == m_emNMType )	//添加
		{
			tTPNMServerCfg.wNMServerNO = m_wCurretNO;
			u16 nRet = BusinessManagePtr->NetMngAddCmd( tTPNMServerCfg );
            m_tTPNMServerCfgSel = tTPNMServerCfg;
			if ( nRet != NO_ERROR )
			{
				MSG_BOX( "添加网管请求发送失败", FALSE, &msgArg );
				return false; 
			}
		}
		else //修改
		{
			if ( m_tTPNMServerCfgSel.dwNMServerIP != tTPNMServerCfg.dwNMServerIP || m_tTPNMServerCfgSel.achNMReadCommunity != tTPNMServerCfg.achNMReadCommunity || m_tTPNMServerCfgSel.achNMWriteCommunity != tTPNMServerCfg.achNMWriteCommunity 
				|| m_tTPNMServerCfgSel.wNMGetSetPort != tTPNMServerCfg.wNMGetSetPort || m_tTPNMServerCfgSel.WNMTrapPort != tTPNMServerCfg.WNMTrapPort )
			{
				tTPNMServerCfg.wNMServerNO = m_tTPNMServerCfgSel.wNMServerNO;
				u16 nRet = BusinessManagePtr->NetMngModifyCmd( tTPNMServerCfg );
				if ( nRet != NO_ERROR )
				{
					MSG_BOX( "修改网管请求发送失败", FALSE, &msgArg );
					return false;
				}
			}
		}		
		
		UIManagePtr->LoadScheme( "SchmShowNetManageInfo", m_pWndTree );
	}
    else
    {
        return false;
    }
 
    return true; 
}

bool CNetManageCfgLogic::OnBtnCancel( const IArgs & args )
{
    if ( m_emNMType == em_NETMNGOPT_ADD )
    {
        UIManagePtr->LoadScheme( "SchmShowNetManageLst", m_pWndTree );
        //OnBtnAddNetManage( args );
    }
    else
    {
        SetAllCtrl( m_tTPNMServerCfgSel );
        UIManagePtr->LoadScheme( "SchmShowNetManageInfo", m_pWndTree );
        m_emNMType = em_NETMNGOPT_IDLE;
    }

    return true;
}

bool CNetManageCfgLogic::OnBtnAddNetManage( const IArgs & args )
{
    memset( &m_tTPNMServerCfgSel, 0, sizeof(TTPNMServerCfg) );
	u16 wNMServerNo = 0;
    vector<TTPNMServerCfg> vecTTPNMServerCfg;
	ComInterface->GetNetMngData( vecTTPNMServerCfg );
	m_emNMType = em_NETMNGOPT_ADD;
	int n = vecTTPNMServerCfg.size();
	switch( n )
	{
	case 0:
		{
			m_wCurretNO = MIN_NMSERVER_NO;
			break;
		}
	case 1:
		{
			if ( vecTTPNMServerCfg[0].wNMServerNO == MAX_NMSERVER_NO )
			{
				m_wCurretNO = MIN_NMSERVER_NO;
			}
			else
			{
				m_wCurretNO = MAX_NMSERVER_NO;
			}
			break;
		}
	case TP_MAX_NMSERVER:
		{
			return true;
		}
	default:
		break;
	}
	
	UIManagePtr->LoadScheme( "SchmShowNetManageInfo", m_pWndTree );
	UIManagePtr->LoadScheme( m_strSchmEdit, m_pWndTree );
	SetAllInitCtrl();
	return true;
}

bool CNetManageCfgLogic::OnBtnDelete( const IArgs & args )
{
    CString strMsg = "是否删除此网管?";
    Args_MsgBox argMsg;
    argMsg.pOwnerWnd = UIManagePtr->GetWindowPtr( "RegServiceDlg" );
    int nResult = MSG_BOX( strMsg, TRUE, &argMsg);
    if ( nResult == IDOK )
    {
        u16 wRe = ComInterface->NetMngDeleteCmd( m_tTPNMServerCfgSel );
        if ( wRe != NO_ERROR )
        {
            Args_MsgBox argMsg;
            argMsg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;
            CString strErr = GET_ERR_STRING ( wRe );
            MSG_BOX( strErr, FALSE, &argMsg);
            argMsg.pOwnerWnd->SetFocus();
            return false;
        }

        UIManagePtr->LoadScheme( "SchmShowNetManageLst", m_pWndTree );
        return true;
    }
    else
    {
        return false;
    }
}

void CNetManageCfgLogic::Clear()
{ 
	if ( m_pWndTree != NULL )
	{
		UIManagePtr->LoadScheme( "", m_pWndTree, "", false );
        UIManagePtr->ShowWindow( "", false, m_pWndTree );
	}
}

void CNetManageCfgLogic::UpdateBtnState()
{
	if (m_pWndTree == NULL)
	{
		return;
	}
	vector<TTPNMServerCfg> vecTTPNMServerCfg;
	ComInterface->GetNetMngData( vecTTPNMServerCfg );

	int nNum = vecTTPNMServerCfg.size();
	if ( nNum == TP_MAX_NMSERVER )
	{
		UIManagePtr->LoadScheme( "SchmDisable", m_pWndTree );
	}
	else
	{
		UIManagePtr->LoadScheme( "SchmEnable", m_pWndTree );
	}
}

HRESULT CNetManageCfgLogic::OnAddNetMngRsp( WPARAM wparam, LPARAM lparam )
{
	Args_MsgBox msgArg;
	if (m_pWndTree == NULL)
	{
		return NO_ERROR;
	}
	
	EmModifyNMServerRet emRes = static_cast<EmModifyNMServerRet>(wparam);
	
	switch( emRes )
	{
	case em_nmserver_modify_success:
		{
			vector<TTPNMServerCfg> vecTTPNMServerCfg;
			ComInterface->GetNetMngData( vecTTPNMServerCfg );
			Value_ListNetManage ListNetManage( &vecTTPNMServerCfg, "CNetManageCfgLogic::OnClickWebManageItem" );
			UIManagePtr->SetPropertyValue( ListNetManage, m_strListNetMng, m_pWndTree );
			//memset( &m_tTPNMServerCfgSel, 0, sizeof(TTPNMServerCfg) ); dyy bug
			UpdateBtnState();			
			break;
		}
	case em_nmserver_resource_full:
		{
			//Bug00185760 cns回复的错误 均在右下角显示
			//MSG_BOX( "添加失败，服务器已满", FALSE, &msgArg );
			ShowPopMsg("添加失败，服务器已满");
			break;
		}
	case em_nmserver_invalid_handle:
		{
			//MSG_BOX( "添加失败，数据无效", FALSE, &msgArg );
			ShowPopMsg("添加失败，数据无效");
			break;
		}
	default:
		break;
	}
	
	return S_OK;
}

HRESULT CNetManageCfgLogic::OnModifyNetMngRsp( WPARAM wparam, LPARAM lparam )
 {
	Args_MsgBox msgArg;
	if (m_pWndTree == NULL)
	{
		return NO_ERROR;
	}
	
	EmModifyNMServerRet emRes = static_cast<EmModifyNMServerRet>(wparam);
	
	switch( emRes )
	{
	case em_nmserver_modify_success:
		{
			vector<TTPNMServerCfg> vecTTPNMServerCfg;
			ComInterface->GetNetMngData( vecTTPNMServerCfg );

			Value_ListNetManage ListNetManage( &vecTTPNMServerCfg, "CNetManageCfgLogic::OnClickWebManageItem" );
 			UIManagePtr->SetPropertyValue( ListNetManage, m_strListNetMng, m_pWndTree);
			UpdateBtnState();
			break;
		}
	case em_nmserver_resource_full:
		{
			//MSG_BOX( "修改失败，服务器已满", FALSE, &msgArg );
			ShowPopMsg("修改失败，服务器已满");
			break;
		}
	case em_nmserver_invalid_handle:
		{
			//MSG_BOX( "修改失败，数据无效", FALSE, &msgArg );
			ShowPopMsg("修改失败，数据无效");
			break;
		}
	default:
		break;
	}
	
	return true;
}

HRESULT CNetManageCfgLogic::OnDelNetMngRsp( WPARAM wparam, LPARAM lparam )
{
	Args_MsgBox msgArg;
	if (m_pWndTree == NULL)
	{
		return NO_ERROR;
	}
	
	EmModifyNMServerRet emRes = static_cast<EmModifyNMServerRet>(wparam);
	
	switch( emRes )
	{
	case em_nmserver_modify_success:
		{
			vector<TTPNMServerCfg> vecTTPNMServerCfg;
			ComInterface->GetNetMngData( vecTTPNMServerCfg );

			Value_ListNetManage ListNetManage( &vecTTPNMServerCfg, "CNetManageCfgLogic::OnClickWebManageItem" );
 			UIManagePtr->SetPropertyValue( ListNetManage, m_strListNetMng, m_pWndTree);
			
			memset( &m_tTPNMServerCfgSel, 0, sizeof(TTPNMServerCfg) );
			UpdateBtnState();
			
			UIManagePtr->LoadScheme( "SchmShowNetManageLst", m_pWndTree );
			
			break;
		}
	case em_nmserver_resource_full:
		{
			//MSG_BOX( "删除失败，服务器已满", FALSE, &msgArg );
			ShowPopMsg("删除失败，服务器已满");
			break;
		}
	case em_nmserver_invalid_handle:
		{
			//MSG_BOX( "删除失败，数据无效", FALSE, &msgArg );
			ShowPopMsg("删除失败，数据无效");
			break;
		}
	default:
		break;
	}

	return true;
}

HRESULT CNetManageCfgLogic::OnNetMngNty( WPARAM wparam, LPARAM lparam )
{
	if (m_pWndTree == NULL)
	{
		return NO_ERROR;
	}
	
	vector<TTPNMServerCfg> vecTTPNMServerCfg;
	ComInterface->GetNetMngData( vecTTPNMServerCfg );
	
	Value_ListNetManage ListNetManage( &vecTTPNMServerCfg, "CNetManageCfgLogic::OnClickWebManageItem" );
	UIManagePtr->SetPropertyValue( ListNetManage, m_strListNetMng, m_pWndTree );
	UpdateBtnState();

	return NO_ERROR;
}

bool CNetManageCfgLogic::GetAllCtrl( TTPNMServerCfg &tTPNMServerCfg )
{
	if ( m_pWndTree == NULL )
	{
		return NO_ERROR;
	}

    GetCurrentCtrl();
	Args_MsgBox msgArg;
	String strCaption;
	UIManagePtr->GetCaption( m_strNMServerIp, strCaption, m_pWndTree );
	if ( strCaption.empty() )
	{  
		msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( m_strNMServerIp, m_pWndTree );
		//msgArg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;
		MSG_BOX( "网管服务器地址不能为空", FALSE, &msgArg );
		msgArg.pOwnerWnd->SetFocus();
		return false;
	}
	u32_ip dwNMSververIp = inet_addr(strCaption.c_str());

    Value_IpEditData valIp;
	UIManagePtr->GetPropertyValue(valIp, m_strNMServerIp, m_pWndTree);
    if (!CCallAddr::IsValidIpV4( valIp.dwIP ))
    {
        msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( m_strNMServerIp, m_pWndTree );
        MSG_BOX( "网管服务器地址非法", FALSE, &msgArg );
		msgArg.pOwnerWnd->SetFocus();
        return false;
    }
    
    vector<TTPNMServerCfg> vecTTPNMServerCfg;
	ComInterface->GetNetMngData( vecTTPNMServerCfg );
         
    if ( m_tTPNMServerCfgSel.dwNMServerIP != m_tTPNMServerCfgCur.dwNMServerIP || m_tTPNMServerCfgSel.dwNMServerIP == NULL)
    {
        for ( int i=0; i<vecTTPNMServerCfg.size(); i++)
        {
            if ( vecTTPNMServerCfg[i].dwNMServerIP == dwNMSververIp )
            {
                msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( m_strNMServerIp, m_pWndTree );
                MSG_BOX( "网管服务器地址已存在", FALSE, &msgArg );
                msgArg.pOwnerWnd->SetFocus();
                return false;                
            }                                  
        }
    }
    
	tTPNMServerCfg.dwNMServerIP = dwNMSververIp;

	UIManagePtr->GetCaption( m_strNMReadCommunity, strCaption, m_pWndTree );
	strncpy( tTPNMServerCfg.achNMReadCommunity, strCaption.c_str(), MAX_COMMUNITY_LENGTH );
	
	UIManagePtr->GetCaption( m_strNMWriteCommunity, strCaption, m_pWndTree );
	strncpy( tTPNMServerCfg.achNMWriteCommunity, strCaption.c_str(), MAX_COMMUNITY_LENGTH );

	UIManagePtr->GetCaption( m_strNMGetSetPort, strCaption, m_pWndTree );
	if ( strCaption.empty() )
	{  
		//msgArg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;
		msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( m_strNMGetSetPort, m_pWndTree );
		MSG_BOX( "读写端口不能为空", FALSE, &msgArg );
		msgArg.pOwnerWnd->SetFocus();
		return false;
	}
	tTPNMServerCfg.wNMGetSetPort = _ttoi(strCaption.c_str());

	UIManagePtr->GetCaption( m_strNMTrapPort, strCaption, m_pWndTree );
	if ( strCaption.empty() )
	{  
		//msgArg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;
		msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( m_strNMTrapPort, m_pWndTree );
		MSG_BOX( "发警告端口不能为空", FALSE, &msgArg );
		msgArg.pOwnerWnd->SetFocus();
		return false;
	}
	tTPNMServerCfg.WNMTrapPort = _ttoi(strCaption.c_str());
	
	return true;
}

void CNetManageCfgLogic::SetAllCtrl( TTPNMServerCfg &tTPNMServerCfg )
{
	Value_IpEditData valIp;
	valIp.dwIP = ntohl(tTPNMServerCfg.dwNMServerIP);
    UIManagePtr->SetPropertyValue( valIp, m_strNMServerIp, m_pWndTree ); 

	String strCaption;
	strCaption = tTPNMServerCfg.achNMReadCommunity;
	UIManagePtr->SetCaption( m_strNMReadCommunity, strCaption, m_pWndTree );
	
	strCaption = tTPNMServerCfg.achNMWriteCommunity;
	UIManagePtr->SetCaption( m_strNMWriteCommunity, strCaption, m_pWndTree );

	char arrGetSetPort[10] = {0};
	_itot( tTPNMServerCfg.wNMGetSetPort, arrGetSetPort, 10 );
	strCaption = arrGetSetPort;
	UIManagePtr->SetCaption( m_strNMGetSetPort, strCaption, m_pWndTree );
	
	char arrTrapPort[5] = {0};
	_itot( tTPNMServerCfg.WNMTrapPort, arrTrapPort, 10 );
	strCaption = arrTrapPort;
	UIManagePtr->SetCaption( m_strNMTrapPort, strCaption, m_pWndTree );

	
}

void CNetManageCfgLogic::SetAllInitCtrl()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}

	UIManagePtr->SetCaption( m_strNMServerIp, "", m_pWndTree );
	UIManagePtr->SetCaption( m_strNMReadCommunity, "pubilc", m_pWndTree );
	UIManagePtr->SetCaption( m_strNMWriteCommunity, "kdv123", m_pWndTree );
	UIManagePtr->SetCaption( m_strNMGetSetPort, "161", m_pWndTree );
	UIManagePtr->SetCaption( m_strNMTrapPort, "162", m_pWndTree );
}

void CNetManageCfgLogic::GetCurrentCtrl()
{
    String strCaption;
    
    UIManagePtr->GetCaption( m_strNMServerIp, strCaption, m_pWndTree );
    u32_ip dwNMSververIp = inet_addr(strCaption.c_str());
    m_tTPNMServerCfgCur.dwNMServerIP = dwNMSververIp;        
    UIManagePtr->GetCaption( m_strNMReadCommunity, strCaption, m_pWndTree );
    strncpy( m_tTPNMServerCfgCur.achNMReadCommunity, strCaption.c_str(), MAX_COMMUNITY_LENGTH );        
    UIManagePtr->GetCaption( m_strNMWriteCommunity, strCaption, m_pWndTree );
    strncpy( m_tTPNMServerCfgCur.achNMWriteCommunity, strCaption.c_str(), MAX_COMMUNITY_LENGTH );       
    UIManagePtr->GetCaption( m_strNMGetSetPort, strCaption, m_pWndTree );
    m_tTPNMServerCfgCur.wNMGetSetPort = _ttoi(strCaption.c_str());       
    UIManagePtr->GetCaption( m_strNMTrapPort, strCaption, m_pWndTree );
    m_tTPNMServerCfgCur.WNMTrapPort = _ttoi(strCaption.c_str());

}

