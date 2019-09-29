// addreditlogic.cpp: implementation of the CAddrEditLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "addreditlogic.h"
#include "TouchListProperty.h"
#include "msgBoxLogic.h"
#include "AddrList.h"
#include <algorithm>

CAddrEditLogic * CAddrEditLogic::m_pAddrEditLogic = NULL;

const String CAddrEditLogic::m_strDlgAddrEdit = "DlgAddrEdit";   
const String CAddrEditLogic::m_strEdtEntryName = "DlgAddrEdit/EntryName";
const String CAddrEditLogic::m_strEdtEntryNumber = "DlgAddrEdit/EntryNumber";
const String CAddrEditLogic::m_strBtnEdit = "DlgAddrEdit/BtnEdit";
const String CAddrEditLogic::m_strListMultiSel = "DlgAddrEdit/SelectList";

const String CAddrEditLogic::m_strListLocalAddr = "DlgLst/LocalAddrList";
const String CAddrEditLogic::m_strListGlobalAddr = "DlgLst/GlobalAddrList";
const String CAddrEditLogic::m_strEdtSearch = "DlgLst/EdtSearch";
const String CAddrEditLogic::m_strBtnBack = "DlgLst/BtnBack";
const String CAddrEditLogic::m_strStcTitle = "DlgLst/StTitle";
const String CAddrEditLogic::m_strBtnCopy = "DlgAddrEdit/BtnCopy";
const String CAddrEditLogic::m_strBtnCut = "DlgAddrEdit/BtnCut";
const String CAddrEditLogic::m_strBtnPaste = "DlgAddrEdit/BtnPaste";
const String CAddrEditLogic::m_strBtnRefresh = "DlgLst/BtnRefresh";
const String CAddrEditLogic::m_strBtnAllSel = "DlgLst/BtnAllSel";
const String CAddrEditLogic::m_strBtnLoadToLocal = "DlgAddrEdit/BtnLoadToLocal";

const String CAddrEditLogic::m_strAddrEditOptnDlg = "AddrEditShowOptnDlg";
const String CAddrEditLogic::m_strLstAddrShowOptn = "AddrEditShowOptnDlg/LstAddrMenu";
const String CAddrEditLogic::m_strBtnAddrShowEx = "DlgLst/BtnAddrShowEx";

static UINT g_nTmHandleNtyLoadNum;
//֪ͨ�����ַ��ʱʣ�����Ŀ����  by xhx
VOID  CALLBACK  CNtyLoadNumTimerFun( HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime )
{   
    if ( idEvent == g_nTmHandleNtyLoadNum )
    {
		Window* pWnd = UIManagePtr->GetWindowPtr( g_stcStrAddrEditDlg );
		u32 dwLoadAddrNum = CAddrEditLogic::GetLogicPtr()->GetLoadAddrNum();
		CMsgDispatch::SendMessage( UI_CNC_LOADADDRNUM_NTY, (WPARAM)pWnd, (LPARAM)dwLoadAddrNum );
    } 
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CAddrEditLogic::CAddrEditLogic()
{
	m_emEditType = emEntryItem;
	m_emAddrBookType = em_AddrBook_Normal;
	m_bWaitAddEntry = FALSE;
	m_bWaitAddGroup = FALSE;
	m_bGlobalAddr = FALSE;
    m_bSearchEdit = FALSE;
    m_SelGroup.SetNull();
    m_emShowState = emShowAllAddr;
	m_bLoadToLocal = FALSE;
	m_dwGlobalAddrIndex = 0;
	g_nTmHandleNtyLoadNum = 1;
}

CAddrEditLogic::~CAddrEditLogic()
{
	if ( m_pAddrEditLogic != NULL )
	{   
		UnRegMsg();
		UnRegFunc();
		delete m_pAddrEditLogic;
		m_pAddrEditLogic = NULL;
	}
}


CAddrEditLogic* CAddrEditLogic::GetLogicPtr()
{
	if ( m_pAddrEditLogic == NULL )
	{  
		m_pAddrEditLogic = new CAddrEditLogic();  
	}
	
	return m_pAddrEditLogic;
}


bool CAddrEditLogic::RegCBFun()
{			
    REG_GOBAL_MEMBER_FUNC( "CAddrEditLogic::InitWnd", CAddrEditLogic::InitWnd, m_pAddrEditLogic, CAddrEditLogic ) ;
    REG_GOBAL_MEMBER_FUNC( "CAddrEditLogic::OnBtnLocalAddr", CAddrEditLogic::OnBtnLocalAddr, m_pAddrEditLogic, CAddrEditLogic );
    REG_GOBAL_MEMBER_FUNC( "CAddrEditLogic::OnBtnGlobalAddr", CAddrEditLogic::OnBtnGlobalAddr, m_pAddrEditLogic, CAddrEditLogic );
    REG_GOBAL_MEMBER_FUNC( "CAddrEditLogic::OnAddEntry", CAddrEditLogic::OnAddEntry, m_pAddrEditLogic, CAddrEditLogic );
    REG_GOBAL_MEMBER_FUNC( "CAddrEditLogic::OnAddGroup", CAddrEditLogic::OnAddGroup, m_pAddrEditLogic, CAddrEditLogic );
    REG_GOBAL_MEMBER_FUNC( "CAddrEditLogic::OnSave", CAddrEditLogic::OnSave, m_pAddrEditLogic, CAddrEditLogic );
    REG_GOBAL_MEMBER_FUNC( "CAddrEditLogic::OnCancel", CAddrEditLogic::OnCancel, m_pAddrEditLogic, CAddrEditLogic );
    REG_GOBAL_MEMBER_FUNC( "CAddrEditLogic::OnEdit", CAddrEditLogic::OnEdit, m_pAddrEditLogic, CAddrEditLogic );

    REG_GOBAL_MEMBER_FUNC( "CAddrEditLogic::OnSearchEditChange", CAddrEditLogic::OnSearchEditChange, m_pAddrEditLogic, CAddrEditLogic );
    REG_GOBAL_MEMBER_FUNC( "CAddrEditLogic::OnBtnCopy", CAddrEditLogic::OnBtnCopy, m_pAddrEditLogic, CAddrEditLogic );
    REG_GOBAL_MEMBER_FUNC( "CAddrEditLogic::OnBtnCut", CAddrEditLogic::OnBtnCut, m_pAddrEditLogic, CAddrEditLogic );
    REG_GOBAL_MEMBER_FUNC( "CAddrEditLogic::OnBtnPaste", CAddrEditLogic::OnBtnPaste, m_pAddrEditLogic, CAddrEditLogic );
    REG_GOBAL_MEMBER_FUNC( "CAddrEditLogic::OnBtnRevoke", CAddrEditLogic::OnBtnRevoke, m_pAddrEditLogic, CAddrEditLogic );
    REG_GOBAL_MEMBER_FUNC( "CAddrEditLogic::OnBtnDelete", CAddrEditLogic::OnBtnDelete, m_pAddrEditLogic, CAddrEditLogic );
    REG_GOBAL_MEMBER_FUNC( "CAddrEditLogic::OnBtnDeleteItem", CAddrEditLogic::OnBtnDeleteItem, m_pAddrEditLogic, CAddrEditLogic );
    
    REG_GOBAL_MEMBER_FUNC( "CAddrEditLogic::OnBtnBack", CAddrEditLogic::OnBtnBack, m_pAddrEditLogic, CAddrEditLogic );
    REG_GOBAL_MEMBER_FUNC( "CAddrEditLogic::OnClickAddrItem", CAddrEditLogic::OnClickAddrItem, m_pAddrEditLogic, CAddrEditLogic );
    REG_GOBAL_MEMBER_FUNC( "CAddrEditLogic::OnClickGlobalAddrItem", CAddrEditLogic::OnClickGlobalAddrItem, m_pAddrEditLogic, CAddrEditLogic );
    REG_GOBAL_MEMBER_FUNC( "CAddrEditLogic::OnEnterAddrGroup", CAddrEditLogic::OnEnterAddrGroup, m_pAddrEditLogic, CAddrEditLogic );

    REG_GOBAL_MEMBER_FUNC( "CAddrEditLogic::OnBtnRefreshGlobalAddr", CAddrEditLogic::OnBtnRefreshGlobalAddr, m_pAddrEditLogic, CAddrEditLogic );
    REG_GOBAL_MEMBER_FUNC( "CAddrEditLogic::OnBtnSelectAll", CAddrEditLogic::OnBtnSelectAll, m_pAddrEditLogic, CAddrEditLogic );
    REG_GOBAL_MEMBER_FUNC( "CAddrEditLogic::OnBtnUnSelectAll", CAddrEditLogic::OnBtnUnSelectAll, m_pAddrEditLogic, CAddrEditLogic );
    REG_GOBAL_MEMBER_FUNC( "CAddrEditLogic::OnBtnLoadToLocal", CAddrEditLogic::OnBtnLoadToLocal, m_pAddrEditLogic, CAddrEditLogic );

    REG_GOBAL_MEMBER_FUNC( "CAddrEditLogic::OnSelAddrItem", CAddrEditLogic::OnSelAddrItem, m_pAddrEditLogic, CAddrEditLogic );
    REG_GOBAL_MEMBER_FUNC( "CAddrEditLogic::OnUnSelAddrItem", CAddrEditLogic::OnUnSelAddrItem, m_pAddrEditLogic, CAddrEditLogic );
    REG_GOBAL_MEMBER_FUNC( "CAddrEditLogic::OnBtnDelItem", CAddrEditLogic::OnBtnDelItem, m_pAddrEditLogic, CAddrEditLogic );	
    REG_GOBAL_MEMBER_FUNC( "CAddrEditLogic::UnSelAddrList", CAddrEditLogic::UnSelAddrList, m_pAddrEditLogic, CAddrEditLogic );

    REG_GOBAL_MEMBER_FUNC( "CAddrEditLogic::OnBtnAddrShowOptn", CAddrEditLogic::OnBtnAddrShowOptn, m_pAddrEditLogic, CAddrEditLogic );   
    REG_GOBAL_MEMBER_FUNC( "CAddrEditLogic::OnAddrOptnShowAll", CAddrEditLogic::OnAddrOptnShowAll, m_pAddrEditLogic, CAddrEditLogic );
    REG_GOBAL_MEMBER_FUNC( "CAddrEditLogic::OnAddrOptnShowGroup", CAddrEditLogic::OnAddrOptnShowGroup, m_pAddrEditLogic, CAddrEditLogic );
    REG_GOBAL_MEMBER_FUNC( "CAddrEditLogic::OnAddrOptnShowOnline", CAddrEditLogic::OnAddrOptnShowOnline, m_pAddrEditLogic, CAddrEditLogic );
    REG_GOBAL_MEMBER_FUNC( "CAddrEditLogic::OnAddrOptnShowOffline", CAddrEditLogic::OnAddrOptnShowOffline, m_pAddrEditLogic, CAddrEditLogic );

	return true;
}

bool CAddrEditLogic::UnRegFunc()
{

	return true;
}

void CAddrEditLogic::RegMsg()
{
	REG_MSG_HANDLER( UI_CNS_ADDRBOOK_CHANGED, CAddrEditLogic::UpdateAddrBook, m_pAddrEditLogic, CAddrEditLogic );
	REG_MSG_HANDLER( UI_CNS_ADDRBOOK_ADDENTRY, CAddrEditLogic::OnAddEntryNty, m_pAddrEditLogic, CAddrEditLogic );
	REG_MSG_HANDLER( UI_CNS_ADDRBOOK_ADDGROUP, CAddrEditLogic::OnAddGroupNty, m_pAddrEditLogic, CAddrEditLogic );
	REG_MSG_HANDLER( UI_CNS_ADDRBOOK_MODIFY, CAddrEditLogic::OnAddrModifyNty, m_pAddrEditLogic, CAddrEditLogic );

    REG_MSG_HANDLER( UI_CNS_ADDRBOOKOPT_FAILED, CAddrEditLogic::OnAddrOptFailed, m_pAddrEditLogic, CAddrEditLogic );

	REG_MSG_HANDLER( UI_CNS_REFRESH_GLOBAL_ADDRBOOK, CAddrEditLogic::UpdateGlobalAddrBook, m_pAddrEditLogic, CAddrEditLogic );

	REG_MSG_HANDLER( UI_CNC_WAITINGREFRESH_OVERTIME, CAddrEditLogic::OnWaitRefreshOverTime, m_pAddrEditLogic, CAddrEditLogic );
}


bool CAddrEditLogic::InitWnd( const IArgs & args )
{
	CWndLogicBase::InitWnd( args );

	UpdateLocalAddrList();
	UpdateGlobalAddrList();
    UpdateShowOption();

	UpdateUIState();

	return true;
}


bool CAddrEditLogic::OnBtnLocalAddr( const IArgs& args )
{
	m_bGlobalAddr = FALSE;
	m_vctSelectList.clear();

    UIManagePtr->SetCaption( m_strEdtSearch, "", m_pWndTree );

	UpdateLocalAddrList();
	UpdateUIState();

	UIManagePtr->LoadScheme( "SchmLocalAddr", m_pWndTree );

	UpdateAddrTitle();

	return true;
}


bool CAddrEditLogic::OnBtnGlobalAddr( const IArgs& args )
{
	m_bGlobalAddr = TRUE;
	m_vctSelectList.clear();
	m_vctOperateList.clear();

    UIManagePtr->SetCaption( m_strEdtSearch, "", m_pWndTree );

	UpdateGlobalAddrList();
	UpdateUIState();

	UIManagePtr->LoadScheme( "SchmGlobalAddr", m_pWndTree );

	UpdateAddrTitle();

    UIManagePtr->ShowWindow( m_strAddrEditOptnDlg, false );

	return true;
}


bool CAddrEditLogic::OnAddEntry( const IArgs& args )
{
	m_emAddrBookType = em_AddrBook_Add;
	m_emEditType = emEntryItem;
		
	if ( !m_vctSelectList.empty() )
	{
		m_vctSelectList.clear();
		UpdateShowList();
	}
	m_vctOperateList.clear();
	
	//UpdateUIState();

	UIManagePtr->SetCaption( m_strEdtEntryName, "", m_pWndTree );
	UIManagePtr->SetCaption( m_strEdtEntryNumber, "", m_pWndTree );

	UIManagePtr->LoadScheme( "SchmEditEntry", m_pWndTree );
	UIManagePtr->SetFocus( m_strEdtEntryName, m_pWndTree );
	return true;
}


bool CAddrEditLogic::OnAddGroup( const IArgs& args )
{
	m_emAddrBookType = em_AddrBook_Add;
	m_emEditType = emGroupItem;

	if ( !m_vctSelectList.empty() )
	{
		m_vctSelectList.clear();
		UpdateShowList();
	}	
	m_vctOperateList.clear();

	//UpdateUIState();

	UIManagePtr->SetCaption( m_strEdtEntryName, "", m_pWndTree );
	UIManagePtr->SetCaption( m_strEdtEntryNumber, "", m_pWndTree );	

	UIManagePtr->LoadScheme( "SchmEditGroup", m_pWndTree );
	UIManagePtr->SetFocus( m_strEdtEntryName, m_pWndTree );
	return true;
}


bool CAddrEditLogic::OnSave( const IArgs& args )
{
    if ( m_emAddrBookType == em_AddrBook_Normal )
    {
        return false;
    }

	if ( m_emEditType == emEntryItem )
	{
		if ( SaveAddrEntry() )
		{
			UIManagePtr->LoadScheme( "SchmShowEntry", m_pWndTree );

            m_emAddrBookType = em_AddrBook_Normal;
		}	
	}
	else
	{
		if ( SaveAddrGroup() )
		{
			UIManagePtr->LoadScheme( "SchmShowGroup", m_pWndTree );

            //�༭��������ȫѡ��ť�仯�����
            if ( m_vctShowList.empty() )
            {
                UIManagePtr->EnableWindow( m_strBtnAllSel, false, m_pWndTree );
            }
            else
            {
                UIManagePtr->EnableWindow( m_strBtnAllSel, true, m_pWndTree );
		    }

            m_emAddrBookType = em_AddrBook_Normal;
		}	
	}
	
	return true;
}


bool CAddrEditLogic::SaveAddrEntry()
{
	String strEntryName;
	UIManagePtr->GetCaption( m_strEdtEntryName, strEntryName, m_pWndTree );

	String strE164 = "";
	UIManagePtr->GetCaption( m_strEdtEntryNumber, strE164, m_pWndTree );

	Args_MsgBox msgArg;
	//msgArg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;
	//������ʾ�󽹵��赽Edit��
	Window* pNameWnd = UIManagePtr->GetWindowPtr( m_strEdtEntryName, m_pWndTree );
	Window* pE164Wnd = UIManagePtr->GetWindowPtr( m_strEdtEntryNumber, m_pWndTree );
	msgArg.pOwnerWnd = pNameWnd;

	if ( strEntryName.empty() && strE164.empty() )
	{
		MSG_BOX( "�᳡���ƺͻ᳡���벻��ȫΪ��", FALSE,  &msgArg );
		pNameWnd->SetFocus();
		return false;
	}

	if ( !strEntryName.empty() )
	{
		if ( IsAllE164Number( strEntryName ) )
		{
			MSG_BOX( "�᳡���Ʋ���ȫΪ���ּ�*#,��", FALSE, &msgArg );
			pNameWnd->SetFocus();
			return false;
		}
		if ( !IsValidTPStr( strEntryName ) )
		{   
			CString str; 
			str.Format("�᳡���Ʋ����԰����ո������е������ַ� [ %s ]",INVALID_ALIAS_FOR_SHOW);
			MSG_BOX( str, FALSE ,&msgArg ); 
			pNameWnd->SetFocus();
			return false;
		}
	}
		
	CString cstrE164 = "";
	cstrE164.Format( "%s", strE164.c_str() );

	if ( !cstrE164.IsEmpty() && !CCallAddr::IsValidE164(cstrE164))
	{
		MSG_BOX( "�᳡���벻�Ϸ���E164��ֻ�ܰ������ּ�*#,��", FALSE, &msgArg );
		pE164Wnd->SetFocus();
		return false;
	}

	CAddrBook cAddrBook = ComInterface->GetAddrBook();

	CAddrEntry cAddrEntry;

	if ( m_emAddrBookType == em_AddrBook_Add )
	{
		u32 dwNum = 0;
		if ( !strEntryName.empty() )
		{
			dwNum = cAddrBook.GetAddrEntryByName( const_cast<char*>(strEntryName.c_str()), &cAddrEntry );
			if ( dwNum > 0 )
			{
				MSG_BOX( "�᳡�����Ѵ���", FALSE, &msgArg );
				pNameWnd->SetFocus();
				return false;
			}
		}
		
		if ( !strE164.empty() )
		{
			dwNum = cAddrBook.GetAddrEntryByNumber( const_cast<char*>(strE164.c_str()), &cAddrEntry );
			if ( dwNum > 0 )
			{
				MSG_BOX( "�᳡�����Ѵ���", FALSE, &msgArg );
				pE164Wnd->SetFocus();
				return false;
			}
		}

		u32 dwSize = cAddrBook.GetAddrEntryUsedSize();
		if ( dwSize >= MAX_ADDRENTRY /*MAX_ADDRENTRY_COUNT*/ )
		{
			CString strErr;
            strErr.Format( "�᳡��Ŀ�Ѵﵽ���ֵ%d��", MAX_ADDRENTRY );
			MSG_BOX( strErr, FALSE, &msgArg );
			pNameWnd->SetFocus();
			return false;
		}
		
		cAddrEntry.SetEntryName( strEntryName.c_str() );
		cAddrEntry.SetMtNumber( strE164.c_str() );
		
		u16 wRe = ComInterface->AddEntry( cAddrEntry );
	
		m_bWaitAddEntry = TRUE;
	}
	else
	{
		if ( m_SelItem.emItemType != emEntryItem )
		{
			return false;
		}
		bool bChange = false;
		if ( strcmp( m_SelItem.tAddrInfo.achEntryName, strEntryName.c_str() ) != 0 )
		{
            if ( !strEntryName.empty() )
            {
			    u32 dwNum = cAddrBook.GetAddrEntryByName( const_cast<char*>(strEntryName.c_str()), &cAddrEntry );
			    if ( dwNum > 0 )
			    {
				    MSG_BOX( "�᳡�����Ѵ���", FALSE, &msgArg );
					pNameWnd->SetFocus();
				    return false;
			    }
            }
			bChange = true;
		}

		if ( strcmp( m_SelItem.tAddrInfo.achE164, strE164.c_str() ) != 0 )
		{
			if ( !strE164.empty() )
			{
				u32 dwNum = cAddrBook.GetAddrEntryByNumber( const_cast<char*>(strE164.c_str()), &cAddrEntry );
				if ( dwNum > 0 )
				{
					MSG_BOX( "�᳡�����Ѵ���", FALSE, &msgArg );
					pE164Wnd->SetFocus();
					return false;
				}
			}		
			bChange = true;
		}

		u32 dwEntryIndex = m_SelItem.tAddrInfo.dwEntryIdx;
		if ( bChange )
		{		
			cAddrBook.GetAddrEntry( &cAddrEntry, dwEntryIndex );
			cAddrEntry.SetEntryName( strEntryName.c_str() );
			cAddrEntry.SetMtNumber( strE164.c_str() );

			u16 wRe = ComInterface->ModifyEntry( cAddrEntry );
		}
	}

	return true;
}


bool CAddrEditLogic::SaveAddrGroup()
{	
	String strName;
	UIManagePtr->GetCaption( m_strEdtEntryName, strName, m_pWndTree );

	Args_MsgBox msgArg;
	msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( m_strEdtEntryName, m_pWndTree );

	CString cstrName;
	cstrName.Format( "%s", strName.c_str() );
	cstrName.TrimLeft();
	cstrName.TrimRight();
    if ( cstrName.IsEmpty() )
    {
        MSG_BOX( "�������Ʋ���Ϊ��", FALSE, &msgArg );
		msgArg.pOwnerWnd->SetFocus();
        return false;
	}
	
	CAddrBook cAddrBook = ComInterface->GetAddrBook();
	CAddrMultiSetEntry cAddrGroup;
	
	if ( m_emAddrBookType == em_AddrBook_Add )
	{
		u32 dwNum = cAddrBook.GetAddrMultiSetEntry( (LPSTR)(LPCTSTR)cstrName, &cAddrGroup );
		if ( dwNum > 0 )
		{	
			MSG_BOX( "���������Ѵ���", FALSE, &msgArg );
			msgArg.pOwnerWnd->SetFocus();
 			return false;
		}	

		u32 dwSize = cAddrBook.GetAddrGroupUsedSize();
		if ( dwSize >= MAX_ADDRGROUP )
		{
			CString strErr;
            strErr.Format( "�᳡�����Ѵﵽ���ֵ%d��", MAX_ADDRGROUP );
			MSG_BOX( strErr, FALSE, &msgArg );
			msgArg.pOwnerWnd->SetFocus();
			return false;
		}

		cAddrGroup.SetGroupName( (LPCTSTR)cstrName );

		u16 wRe = ComInterface->AddGroup( cAddrGroup );

		m_bWaitAddGroup = TRUE;
	}
	else
	{
		if ( m_SelItem.emItemType != emGroupItem )
		{
			return false;
		}

		u32 dwGroupIndex = m_SelItem.tGroupInfo.dwGroupIdx;

		cAddrBook.GetAddrMultiSetEntry( &cAddrGroup, dwGroupIndex );
		
		if ( cstrName.Compare( m_SelItem.tGroupInfo.achGroupName ) != 0 )
		{
			u32 dwNum = cAddrBook.GetAddrMultiSetEntry( (LPSTR)(LPCTSTR)cstrName, &cAddrGroup );
			if ( dwNum > 0 )
			{	
				MSG_BOX( "���������Ѵ���", FALSE, &msgArg );
				msgArg.pOwnerWnd->SetFocus();
				return false;
			}

			cAddrGroup.SetGroupName( (LPCTSTR)cstrName );	
			u16 wRe = ComInterface->ModifyGroup( cAddrGroup );
		}		
	}

    //������һ�����ƣ�ȥ��ǰ��ո�
    UIManagePtr->SetCaption( m_strEdtEntryName, (LPCTSTR)cstrName, m_pWndTree );

	return true;
}


bool CAddrEditLogic::OnEdit( const IArgs& args )
{
	if ( m_SelItem.emItemType == emEntryItem )
	{		
		m_emEditType = emEntryItem;	

		UIManagePtr->LoadScheme( "SchmEditEntry", m_pWndTree );
	}
	else
	{				
		m_emEditType = emGroupItem;
		
		UIManagePtr->LoadScheme( "SchmEditGroup", m_pWndTree );
	}

	//�༭ʱ�����赽Edit��
	UIManagePtr->SetFocus( m_strEdtEntryName, m_pWndTree );

	m_emAddrBookType = em_AddrBook_Modify;

	return true;
}

bool CAddrEditLogic::OnCancel( const IArgs& args )
{
	UpdateUIState();
	m_emAddrBookType = em_AddrBook_Normal;

	return true;
}

//�����ַ����Ŀ
bool CAddrEditLogic::OnClickAddrItem( const IArgs& args )
{
	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast<const Args_ClickItemInfo*>(&args) )
    {
		IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetItemData();
		if ( const Data_AddrItemInfo *pItemInfo = dynamic_cast<const Data_AddrItemInfo*>( pBaseItem->GetUserData() ) )
		{
			m_SelItem = pItemInfo->m_tAddrItem;
			
			if ( m_SelItem.emItemType == emGroupItem )
			{
                /*
				m_vctSelectList.clear();
				UIManagePtr->SetCaption( m_strEdtSearch, "", m_pWndTree );
				
				//��¼�µ�ǰ�б�ƫ����
				Value_TransparentListOffset valueOffset;
				UIManagePtr->GetPropertyValue( valueOffset, m_strListLocalAddr, m_pWndTree );
				m_vctListOffset.push_back( valueOffset.nOffset );

				//������
				m_SelGroup = m_SelItem.tGroupInfo;
				GetAddrGroupMember( m_SelGroup.dwGroupIdx );

				//������֮��ƫ������Ϊ0
				valueOffset.nOffset = 0;
				UIManagePtr->SetPropertyValue( valueOffset, m_strListLocalAddr, m_pWndTree );

				//���±���
				UpdateAddrTitle();
                */
                UpdateUIState();                
			}
			else
			{				
				if ( m_vctSelectList.empty() && m_vctOperateList.empty() )
				{
 					TAddrInfo tAddrInfo = m_SelItem.tAddrInfo;
 					UIManagePtr->SetCaption( m_strEdtEntryName, tAddrInfo.achEntryName, m_pWndTree );
 					UIManagePtr->SetCaption( m_strEdtEntryNumber, tAddrInfo.achE164, m_pWndTree );				
					UIManagePtr->LoadScheme( "SchmShowEntry", m_pWndTree );
				}
			}				
		}
    } 
	return true;
}

bool CAddrEditLogic::OnEnterAddrGroup( const IArgs& args )
{
    if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast<const Args_ClickItemInfo*>(&args) )
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetParentItem()->GetItemData();
        if ( const Data_AddrItemInfo *pItemInfo = dynamic_cast<const Data_AddrItemInfo*>( pBaseItem->GetUserData() ) )
        {
            TAddrItem tSelItem = pItemInfo->m_tAddrItem;
            
            if ( tSelItem.emItemType == emGroupItem )
            {
                m_vctSelectList.clear();
                UIManagePtr->SetCaption( m_strEdtSearch, "", m_pWndTree );

				//����Ŀ����ʱ�����뵽������Ŀ������ʱ������ѡ��
				if ( !m_vctOperateList.empty() )
				{
					TAddrItem tItem = m_vctOperateList.at(0);
					if( tItem.emItemType == emEntryItem )
					{
						if ( tSelItem.tGroupInfo.dwGroupIdx == tItem.tAddrInfo.dwInGroupIdx )
						{
							m_vctSelectList = m_vctOperateList;
						}
					}
				}
             
                //��¼�µ�ǰ�б�ƫ����
                Value_TransparentListOffset valueOffset;
                UIManagePtr->GetPropertyValue( valueOffset, m_strListLocalAddr, m_pWndTree );
                m_vctListOffset.push_back( valueOffset.nOffset );     
                
                if ( m_emShowState == emShowGroup )
                {
                    m_emShowState = emShowAllAddr;//������� ��ʾ����ȫ�� dyy
                    UpdateShowOption();
                }  
                
                //������
                m_SelGroup = tSelItem.tGroupInfo;
                GetAddrGroupMember( m_SelGroup.dwGroupIdx );
                
                //������֮��ƫ������Ϊ0
                valueOffset.nOffset = 0;
                UIManagePtr->SetPropertyValue( valueOffset, m_strListLocalAddr, m_pWndTree );
                
                //���±���
                UpdateAddrTitle();
                
                UpdateUIState();                
			}
        }
    }
    return true;
}


//���ȫ�ֵ�ַ����Ŀ
bool CAddrEditLogic::OnClickGlobalAddrItem( const IArgs& args )
{
	return true;
}



bool CAddrEditLogic::OnSelAddrItem( const IArgs& args )
{
	if ( Args_ClickItemInfo *pclickInfo = dynamic_cast<Args_ClickItemInfo*>( const_cast<IArgs*>(&args)) )
	{ 
		IBaseItem* pBaseItem = pclickInfo->m_pClickList->GetParentItem()->GetItemData();
		if ( pBaseItem != NULL )
		{
			Data_AddrItemInfo ItemInfo = *dynamic_cast<const Data_AddrItemInfo*>( pBaseItem->GetUserData() );
			TAddrItem tAddrItem = ItemInfo.m_tAddrItem;
			tAddrItem.strImg.Empty();
			
			m_vctSelectList.push_back( tAddrItem );

			//��ѡ�����²�������ղ����б�
			m_vctOperateList.clear();
			m_SelItem.SetNull();
			//m_SelItem = tAddrItem;			
			
			//UpdateShowList();
            //����ˢ�������б����Ч�� -xcr
            if ( m_bGlobalAddr )
            {
                SetAddrListSelValue( ItemInfo, m_strListGlobalAddr, m_pWndTree );
            }
            else
            {		
                SetAddrListSelValue( ItemInfo, m_strListLocalAddr, m_pWndTree );		
	        }

			UpdateUIState();

			//�б���ʾ������ӵ�,ȫѡʱ��ѡ�б���ʾ������
            if ( m_vctSelectList.size() != m_vctShowList.size() )
            {
			    if ( CTransparentAddrList* pList = dynamic_cast<CTransparentAddrList*>( UIManagePtr->GetWindowPtr( m_strListMultiSel, m_pWndTree ) ) )
			    {
				    pList->SetBottomOffset();
			    }
            }
            else
            {
                Value_TransparentListOffset valueOffset;
                valueOffset.nOffset = 0;
	            UIManagePtr->SetPropertyValue( valueOffset, m_strListMultiSel, m_pWndTree );
            }
		}
	}
	return true;
}

bool CAddrEditLogic::OnUnSelAddrItem( const IArgs& args )
{
	if ( Args_ClickItemInfo *pclickInfo = dynamic_cast<Args_ClickItemInfo*>( const_cast<IArgs*>(&args)) )
	{ 
		IBaseItem* pBaseItem = pclickInfo->m_pClickList->GetParentItem()->GetItemData();
		if ( pBaseItem != NULL )
		{
			Data_AddrItemInfo ItemInfo = *dynamic_cast<const Data_AddrItemInfo*>( pBaseItem->GetUserData() );
			TAddrItem tAddrItem = ItemInfo.m_tAddrItem;
			tAddrItem.strImg.Empty();
			
			vector<TAddrItem>::iterator iter = m_vctSelectList.begin();
			while( iter != m_vctSelectList.end() )
			{					  
				if ( *iter == tAddrItem )
				{
					m_vctSelectList.erase(iter);
					break;
				}		
				iter++;
			}

			m_vctOperateList.clear();

			m_SelItem.SetNull();
			//m_SelItem = tAddrItem;
			
			//UpdateShowList();
            //����ˢ�������б����Ч�� -xcr
            if ( m_bGlobalAddr )
            {
                SetAddrListSelValue( ItemInfo, m_strListGlobalAddr, m_pWndTree );
            }
            else
            {		
                SetAddrListSelValue( ItemInfo, m_strListLocalAddr, m_pWndTree );		
	        }

			UpdateUIState();
		}
	}
	return true;
}


bool CAddrEditLogic::OnBtnDelItem( const IArgs& args )
{
	if ( Args_ClickItemInfo *pclickInfo = dynamic_cast<Args_ClickItemInfo*>( const_cast<IArgs*>(&args)) )
	{ 
		IBaseItem* pBaseItem = pclickInfo->m_pClickList->GetParentItem()->GetItemData();
		if ( pBaseItem != NULL )
		{
			Data_AddrItemInfo ItemInfo = *dynamic_cast<const Data_AddrItemInfo*>( pBaseItem->GetUserData() );
			TAddrItem tAddrItem = ItemInfo.m_tAddrItem;
			
			vector<TAddrItem>::iterator iter = m_vctSelectList.begin();
			while( iter != m_vctSelectList.end() )
			{					  
				if ( *iter == tAddrItem )
				{
					m_vctSelectList.erase(iter);
					break;
				}		
				iter++;
			}			

			m_vctOperateList.clear();
			
			UpdateShowList();

			UpdateUIState();
		}
	}
	return true;
}


bool CAddrEditLogic::OnBtnBack( const IArgs& args )
{
	m_vctSelectList.clear();
	UIManagePtr->SetCaption( m_strEdtSearch, "", m_pWndTree );

	//����Ŀ����ʱ�����ص�������Ŀ������ʱ������ѡ��
	if ( !m_vctOperateList.empty() )
	{
		TAddrItem tItem = m_vctOperateList.at(0);
		if( tItem.emItemType == emEntryItem )
		{
			if ( m_SelGroup.dwInGroupIdx == tItem.tAddrInfo.dwInGroupIdx )
			{
				m_vctSelectList = m_vctOperateList;
			}
		}
	}

	//���ѡ����Ŀ���ڵ�ǰҳ�棬���ѡ����
	if ( !m_SelItem.IsNull() )
	{
		if ( m_SelItem.emItemType == emGroupItem )
		{
			if ( m_SelItem.tGroupInfo.dwInGroupIdx == m_SelGroup.dwGroupIdx )
			{
				m_SelItem.SetNull();
			}
		}
		else
		{
			m_SelItem.SetNull();
		}
	}

	if ( m_SelGroup.dwInGroupIdx == INVALID_INDEX )
	{
		m_SelGroup.SetNull();
		UpdateShowList();
	}
	else
	{
		ComInterface->GetAddrGroupInfo( m_SelGroup.dwInGroupIdx, m_SelGroup );

		GetAddrGroupMember( m_SelGroup.dwGroupIdx );
	}

	//�����б�֮ǰ��ƫ����
	int nSize = m_vctListOffset.size();
	if ( nSize > 0 )
	{
		s32 nOffset = m_vctListOffset.at( nSize - 1 );
		Value_TransparentListOffset val;
		val.nOffset = nOffset;
		UIManagePtr->SetPropertyValue( val, m_strListLocalAddr, m_pWndTree );
		m_vctListOffset.pop_back();
	}	
	
	UpdateAddrTitle();
        
    UpdateShowOption();
	
    UpdateUIState();
	
	return true;
}


void CAddrEditLogic::UpdateAddrTitle()
{
	if ( m_bGlobalAddr )
	{
		UIManagePtr->SetCaption( m_strStcTitle, "�����ַ��", m_pWndTree );
		
		UIManagePtr->LoadScheme( "SchmNotInGroup", m_pWndTree, m_strStcTitle );
		
		UIManagePtr->ShowWindow( m_strBtnBack, false, m_pWndTree );
	}
	else
	{
		if ( m_SelGroup.IsNull() )
		{
			UIManagePtr->SetCaption( m_strStcTitle, "��ַ��", m_pWndTree );
			
			UIManagePtr->LoadScheme( "SchmNotInGroup", m_pWndTree, m_strStcTitle );
			
			UIManagePtr->ShowWindow( m_strBtnBack, false, m_pWndTree );
		}
		else
		{
			CString strTitle;
			strTitle =  ComInterface->GetAddrGroupPath( m_SelGroup.dwGroupIdx );
			strTitle = "��ַ��" + strTitle;
			UIManagePtr->SetCaption( m_strStcTitle, (LPCTSTR)strTitle, m_pWndTree );
			
			UIManagePtr->LoadScheme( "SchmInGroup", m_pWndTree, m_strStcTitle );
			
			UIManagePtr->ShowWindow( m_strBtnBack, true, m_pWndTree );
		}
	}
	
}


void CAddrEditLogic::UpdateUIState()
{
	if ( m_bGlobalAddr )
	{
		UpdateGlobalUIState();
	}
	else
	{	
        if ( m_SelGroup.IsNull() )//�������ճ�� dyy 2013-9-24 
        {
            UIManagePtr->EnableWindow( m_strBtnPaste, false, m_pWndTree );
            UIManagePtr->EnableWindow( m_strBtnCut, false, m_pWndTree );
        }
        else
        {
            UIManagePtr->EnableWindow( m_strBtnPaste, true, m_pWndTree );
            UIManagePtr->EnableWindow( m_strBtnCut, true, m_pWndTree );
        }

		int nSelSize = m_vctSelectList.size();
		if ( nSelSize > 0 )
		{
// 			BOOL bAllSel = FALSE;
// 			if ( nSelSize == m_vctShowList.size() )
// 			{
// 				bAllSel = TRUE;
// 				UIManagePtr->LoadScheme( "SchmAllSel", m_pWndTree );
// 			}
// 			else
// 			{
// 				UIManagePtr->LoadScheme( "SchmNoAllSel", m_pWndTree );
// 			}

			if ( m_vctOperateList.empty() )
			{
				UIManagePtr->LoadScheme( "SchmLocalSelect", m_pWndTree );
			
				//����ֻ�ܼ��У���ѡ����ȫ����ʱ�����ø���
				BOOL bCanCopy = FALSE;
				for ( int i = 0; i< nSelSize; i++ )
				{
					if ( m_vctSelectList.at(i).emItemType == emEntryItem )
					{
						bCanCopy = TRUE;
						break;
					}
				}
				if ( bCanCopy )
				{
					UIManagePtr->EnableWindow( m_strBtnCopy, true, m_pWndTree );
				}
				else
				{
					UIManagePtr->EnableWindow( m_strBtnCopy, false, m_pWndTree );
				}
				
				//ȫѡʱ����ѡ�б�����
				ARRAY<String> vctSubItem;
				vctSubItem.push_back( "AddrDelItem" );
				Value_TouchListAddr touchListAddr( &m_vctSelectList, &vctSubItem, "", TRUE/*bAllSel*/, m_bGlobalAddr );
				UIManagePtr->SetPropertyValue( touchListAddr, m_strListMultiSel, m_pWndTree );
				
				UIManagePtr->LoadScheme( "SchmMultiSel", m_pWndTree );
			}
		}
		else
		{
			//UIManagePtr->LoadScheme( "SchmNoAllSel", m_pWndTree );

			if ( m_vctOperateList.empty() )
			{
				UIManagePtr->LoadScheme( "SchmNoSelect", m_pWndTree );

				if ( m_SelItem.IsNull() )
				{
					UIManagePtr->LoadScheme( "SchmNoShow", m_pWndTree );
				}
				else
				{
					if ( m_SelItem.emItemType == emEntryItem )
					{
						TAddrInfo tAddrInfo = m_SelItem.tAddrInfo;
						UIManagePtr->SetCaption( m_strEdtEntryName, tAddrInfo.achEntryName, m_pWndTree );
						UIManagePtr->SetCaption( m_strEdtEntryNumber, tAddrInfo.achE164, m_pWndTree );
						
						UIManagePtr->LoadScheme( "SchmShowEntry", m_pWndTree );
					}
					else
					{
						UIManagePtr->SetCaption( m_strEdtEntryName, m_SelItem.tGroupInfo.achGroupName, m_pWndTree );
						UIManagePtr->LoadScheme( "SchmShowGroup", m_pWndTree );
					}
				}
			}

		}
	}
    //����ȫѡ��ť
    UpdateAllSelButton();
}


void CAddrEditLogic::UpdateGlobalUIState()
{
	int nSelSize = m_vctSelectList.size();
	if ( nSelSize > 0 )
	{
		UIManagePtr->ShowWindow( m_strBtnLoadToLocal, true, m_pWndTree );

// 		BOOL bAllSel = FALSE;
// 		if ( nSelSize == m_vctShowList.size() )
// 		{
// 			bAllSel = TRUE;
// 			UIManagePtr->LoadScheme( "SchmAllSel", m_pWndTree );
// 		}
// 		else
// 		{
// 			UIManagePtr->LoadScheme( "SchmNoAllSel", m_pWndTree );
// 		}

		ARRAY<String> vctSubItem;
		vctSubItem.push_back( "AddrDelItem" );
		Value_TouchListAddr touchListAddr( &m_vctSelectList, &vctSubItem, "", TRUE/*bAllSel*/, m_bGlobalAddr );
		UIManagePtr->SetPropertyValue( touchListAddr, m_strListMultiSel, m_pWndTree );
		
		UIManagePtr->LoadScheme( "SchmMultiSel", m_pWndTree );

	}
	else
	{
		UIManagePtr->ShowWindow( m_strBtnLoadToLocal, false, m_pWndTree );

		UIManagePtr->LoadScheme( "SchmNoAllSel", m_pWndTree );

		UIManagePtr->LoadScheme( "SchmNoShow", m_pWndTree );
	}
}


bool CAddrEditLogic::OnSearchEditChange( const IArgs& args )
{
	String strCaption;
	UIManagePtr->GetCaption( m_strEdtSearch, strCaption, m_pWndTree );
	if ( strCaption.empty() )
	{
        m_bSearchEdit = FALSE;
		UpdateShowList();
        UpdateAllSelButton();

		//��ѡ������ʾ����
		if ( !m_SelItem.IsNull() )
		{
			if ( m_SelItem.emItemType == emEntryItem )
			{
				Value_TransparentListSelItem valSel;
				valSel.dwDataKey = m_SelItem.tAddrInfo.dwEntryIdx;
				UIManagePtr->SetPropertyValue( valSel, m_strListLocalAddr, m_pWndTree );
			}
			else
			{
				Value_TransparentListSelItem valSel;
				valSel.dwDataKey = m_SelItem.tGroupInfo.dwGroupIdx + MAX_ADDRENTRY;
				UIManagePtr->SetPropertyValue( valSel, m_strListLocalAddr, m_pWndTree );
			}		
		}
		return false;
	}
	
    m_bSearchEdit = TRUE;
	CString strSearchName;
	strSearchName.Format( "%s", strCaption.c_str() );
	
	m_vctSearchList.clear();
	Value_TransparentListOffset val;
	val.nOffset = 0; 

	vector<TAddrItem> vctShowList;
	if ( m_bGlobalAddr )
	{
		vctShowList = m_vctGlobalList;

		UIManagePtr->SetPropertyValue( val, m_strListGlobalAddr, m_pWndTree );
	}
	else
	{
		if ( m_SelGroup.IsNull() )
		{
			vctShowList = m_vctLocalList;
		}
		else
		{
			vctShowList = m_vctGroupMemberList;
		}
		
		UIManagePtr->SetPropertyValue( val, m_strListLocalAddr, m_pWndTree );
	}
	
	for ( int i = 0; i < vctShowList.size(); i++ )
	{
        BOOL bMatchNum = FALSE;
		CString strItemName;
		TAddrItem tAddrItem = vctShowList.at(i);
		if ( tAddrItem.emItemType == emEntryItem )
		{
			//����Ϊ����E164��ƥ��
			if ( strcmp( tAddrItem.tAddrInfo.achEntryName, "" ) == 0 )
			{
				strItemName = tAddrItem.tAddrInfo.achE164;
			}
			else
			{
				strItemName = tAddrItem.tAddrInfo.achEntryName;
                bMatchNum = TRUE;
			}		
		}
		else
		{
			strItemName = tAddrItem.tGroupInfo.achGroupName;
		}
		BOOL bFind = FALSE;			
		bFind = UIDATAMGR->HZPYMatchList( strSearchName, strItemName );
		if ( bFind )
		{		
			m_vctSearchList.push_back( tAddrItem );
		}
        else if ( bMatchNum )
        {
            //����û��ƥ�䵽
            strItemName = tAddrItem.tAddrInfo.achE164;
            bFind = UIDATAMGR->HZPYMatchList( strSearchName, strItemName );
            if ( bFind )
            {		
                m_vctSearchList.push_back( tAddrItem );
            }
        }
		
        if ( !bFind )
		{
			//ѡ������˵�ʱ�����ѡ����
			if ( !m_SelItem.IsNull() && m_SelItem == tAddrItem )
			{
				m_SelItem.SetNull();
				UpdateUIState();
				Value_TransparentListSelItem val;
				val.dwDataKey = -1;
				UIManagePtr->SetPropertyValue( val, m_strListLocalAddr, m_pWndTree );
			}
		}
	}
	
	UpdateShowList();
    UpdateAllSelButton();
	
	return true;
}


bool CAddrEditLogic::OnBtnCopy( const IArgs& args )
{
	m_emOperateType = em_AddrBook_Copy;
	m_vctOperateList = m_vctSelectList;

	UIManagePtr->LoadScheme( "SchmCopy", m_pWndTree );

	return true;
}


bool CAddrEditLogic::OnBtnCut( const IArgs& args )
{
	m_emOperateType = em_AddrBook_Cut;
	m_vctOperateList = m_vctSelectList;

	UIManagePtr->LoadScheme( "SchmCopy", m_pWndTree );

	return true;
}


bool CAddrEditLogic::OnBtnPaste( const IArgs& args )
{   
    //������Ŀ���ڷ���
    u32 dwInGroupIdx = INVALID_INDEX;
    if ( !m_vctOperateList.empty() )
    {
        TAddrItem tAddrItem = m_vctOperateList.at(0);
        if ( tAddrItem.emItemType == emEntryItem )
        {
            dwInGroupIdx = tAddrItem.tAddrInfo.dwInGroupIdx;
        }
        else
        {
            dwInGroupIdx = tAddrItem.tGroupInfo.dwInGroupIdx;
        }
    }
    else
    {
        return false;
    }
   
    if ( m_SelGroup.dwGroupIdx == dwInGroupIdx )
    {
        m_vctOperateList.clear();
        m_vctSelectList.clear();       
        UpdateShowList();
	    UpdateUIState();
        return true;
    }

    u32 adwEntryTable[MAXNUM_ENTRY_TABLE] = {0};
    
    s32 nCount = 0; //��������Ŀ����
    s32 nMaxOptCount = MAXNUM_ENTRY_TABLE; //�ɲ������������

    if ( !m_SelGroup.IsNull() )
    {
        nMaxOptCount -= m_SelGroup.nEntryNum;
    }
    
    for ( int i = 0; i < m_vctOperateList.size(); i++ )
	{
        TAddrItem tAddrItem = m_vctOperateList.at(i);
        if ( tAddrItem.emItemType == emEntryItem )
        {
            TAddrInfo tAddrInfo = tAddrItem.tAddrInfo;
                                    
            if ( nCount >= nMaxOptCount )
            {
                CString strErr;
                strErr.Format( "�����еĻ᳡���%d��", MAXNUM_ENTRY_TABLE );
				ShowPopMsg( strErr );
                break;
            }  
            
            adwEntryTable[nCount] = tAddrInfo.dwEntryIdx;	
            nCount++;
        }
        else
        {
            //����ֻ�м��в���
            if ( m_emOperateType == em_AddrBook_Copy )
            {
                continue;
            }
            
            TGroupInfo tGroupInfo = tAddrItem.tGroupInfo;
            if ( !m_SelGroup.IsNull() )
            {
                if ( tGroupInfo.dwGroupIdx == m_SelGroup.dwGroupIdx )
                {
                    continue;
                }
                u16 wRe = ComInterface->AddGroupToGroup( tGroupInfo.dwGroupIdx, m_SelGroup.dwGroupIdx );
            }
            else
            {
                //�����м��е���һ��
                if ( tGroupInfo.dwInGroupIdx != INVALID_INDEX )
                {
                    u16 wRe = ComInterface->DelGroupFromGroup( tGroupInfo.dwGroupIdx, tGroupInfo.dwInGroupIdx );
                }
            }
        }
    }

    if ( nCount > 0 )
    {      
        //���в�����ɾ��ԭ������Ŀ
        if ( m_emOperateType == em_AddrBook_Cut && dwInGroupIdx != INVALID_INDEX )           
        {
            TADDRMULTISETENTRY tDelEntry;
		    tDelEntry.SetEntryIndex( dwInGroupIdx );
            tDelEntry.SetListEntryIndex( adwEntryTable, nCount );
            tDelEntry.SetListEntryNum( nCount );

            u16 wRe = ComInterface->DelEntryFromGroup(tDelEntry);
        }

        if ( !m_SelGroup.IsNull() )
        {
            //���ƽ��·�����Ŀ
            TADDRMULTISETENTRY tEntry;
            tEntry.SetEntryIndex( m_SelGroup.dwGroupIdx );
            tEntry.SetListEntryIndex( adwEntryTable, nCount );
            tEntry.SetListEntryNum( nCount );
            u16 wRe = ComInterface->AddEntryToGroup(tEntry);
        }
    }

    /*
	for ( int i = 0; i < m_vctOperateList.size(); i++ )
	{
		TAddrItem tAddrItem = m_vctOperateList.at(i);
		if ( tAddrItem.emItemType == emEntryItem )
		{
			TAddrInfo tAddrInfo = tAddrItem.tAddrInfo;
			if ( tAddrInfo.dwInGroupIdx == INVALID_INDEX )
			{
				//�ӵ�һ������/���е�����
				if ( !m_SelGroup.IsNull() )
				{				
					TADDRMULTISETENTRY tEntry;
					tEntry.SetEntryIndex( m_SelGroup.dwGroupIdx );
					u32 adwEntryTable[1] = {0};
					adwEntryTable[0] = tAddrInfo.dwEntryIdx;	
					tEntry.SetListEntryIndex(adwEntryTable, 1);
					tEntry.SetListEntryNum(1);
					u16 wRe = ComInterface->AddEntryToGroup(tEntry);
				}
			}
			else
			{
				if ( m_SelGroup.dwGroupIdx == tAddrInfo.dwInGroupIdx )
				{
					continue;
				}
				//�����и���/����
				if ( m_emOperateType == em_AddrBook_Cut )
				{
					TADDRMULTISETENTRY tEntry;
					tEntry.SetEntryIndex( tAddrInfo.dwInGroupIdx );
					u32 adwEntryTable[1] = {0};
					adwEntryTable[0] = tAddrInfo.dwEntryIdx;	
					tEntry.SetListEntryIndex(adwEntryTable, 1);
					tEntry.SetListEntryNum(1);
					u16 wRe = ComInterface->DelEntryFromGroup(tEntry);
				}

				if ( !m_SelGroup.IsNull() )
				{				
					TADDRMULTISETENTRY tEntry;
					tEntry.SetEntryIndex( m_SelGroup.dwGroupIdx );
					u32 adwEntryTable[1] = {0};
					adwEntryTable[0] = tAddrInfo.dwEntryIdx;	
					tEntry.SetListEntryIndex(adwEntryTable, 1);
					tEntry.SetListEntryNum(1);
					u16 wRe = ComInterface->AddEntryToGroup(tEntry);
				}
			}
		}
		else
		{
			//����ֻ�м��в���
			if ( m_emOperateType == em_AddrBook_Copy )
			{
				continue;
			}
			
			TGroupInfo tGroupInfo = tAddrItem.tGroupInfo;
			if ( tGroupInfo.dwInGroupIdx == INVALID_INDEX )
			{
				//�ӵ�һ�����е�����
				if ( !m_SelGroup.IsNull() )
				{
					u16 wRe = ComInterface->AddGroupToGroup( tGroupInfo.dwGroupIdx, m_SelGroup.dwGroupIdx );
				}
			}
			else
			{
				if ( m_SelGroup.dwGroupIdx == tGroupInfo.dwInGroupIdx )
				{
					continue;
				}
				//�����м��г���
				if ( !m_SelGroup.IsNull() )
				{	
					u16 wRe = ComInterface->AddGroupToGroup( tGroupInfo.dwGroupIdx, m_SelGroup.dwGroupIdx );
				}
				else
				{
					u16 wRe = ComInterface->DelGroupFromGroup( tGroupInfo.dwGroupIdx, tGroupInfo.dwInGroupIdx );
				}
			}
		}
	}
    */

	m_vctOperateList.clear();
	m_vctSelectList.clear();

	UpdateShowList();
	UpdateUIState();

	return true;
}

bool CAddrEditLogic::OnBtnRevoke( const IArgs& args )
{
	//�ֵ�ȡ�������ѡ����
	//m_vctSelectList.clear();
	//m_nSelGroupNum = 0;
	//UpdateShowList();
	m_vctOperateList.clear();
	UpdateUIState();
	return true;
}


bool CAddrEditLogic::OnBtnDelete( const IArgs& args )
{
	CString strMsg = "�Ƿ���ѡ��Ŀ�ӵ�ַ����ɾ��?";
	Args_MsgBox argMsg;
	argMsg.pOwnerWnd = UIManagePtr->GetWindowPtr( "AddrEditDlg" );
	int nResult = MSG_BOX( strMsg, TRUE, &argMsg);
	if ( IDOK == nResult )
	{
		IArgs args("");
		DelAddrEntry(args);
	}
	return true;
}


bool CAddrEditLogic::DelAddrEntry( const IArgs& args )
{
	if ( m_vctSelectList.empty() )
	{
		return false;
	}

    vector<u32> vctDelGroup;

    //�����ǰ��ѡ������ѡ�����Ƿ�ɾ��
    BOOL bNeedCheckSel = FALSE;
    if ( !m_SelItem.IsNull() )
    {
        if ( m_SelItem.emItemType == emEntryItem )
        {
            bNeedCheckSel = TRUE;
        }
    }

	if ( m_SelGroup.IsNull() )
	{
        //ɾ����һ��Ŀ¼�е���Ŀ
        vector<u32> vctDelEntry;

		for ( int i = 0; i < m_vctSelectList.size(); i++ )
		{
			TAddrItem tAddrItem = m_vctSelectList.at(i);
			if ( tAddrItem.emItemType == emEntryItem )
			{
				TAddrInfo tAddrInfo = tAddrItem.tAddrInfo;
				if ( tAddrInfo.dwInGroupIdx == INVALID_INDEX )
				{
					vctDelEntry.push_back( tAddrInfo.dwEntryIdx );
                    //һ�����ɾ��MAX_DELENTRY_NUM��
                    if ( vctDelEntry.size() == MAX_DELENTRY_NUM )
                    {
                        u16 wRe = ComInterface->DeleteMultiEntry( vctDelEntry );
                        vctDelEntry.clear();
                    }

                    if ( bNeedCheckSel )
                    {
                        if ( m_SelItem.tAddrInfo.dwEntryIdx == tAddrInfo.dwEntryIdx )
                        {
                            m_SelItem.SetNull();
                            bNeedCheckSel = FALSE;
                        }
                    }
				}
			}
            else
            {
                //�鼰���¼��鶼ɾ��
			    GetGroupAndLowGroup( tAddrItem.tGroupInfo.dwGroupIdx, vctDelGroup );
            }
		}

		if ( !vctDelEntry.empty() )
		{
			if ( vctDelEntry.size() == 1 )
			{
				u16 wRe = ComInterface->DeleteEntry( vctDelEntry.at(0) );
			}
			else
			{
				u16 wRe = ComInterface->DeleteMultiEntry( vctDelEntry );
			}
		}      
	}
    else
    {   //ɾ�����е���Ŀ
        int nIndex = 0;
        u32 adwEntryTable[MAXNUM_ENTRY_TABLE] = {0};

        for ( int i = 0; i < m_vctSelectList.size(); i++ )
        {
            TAddrItem tAddrItem = m_vctSelectList.at(i);
            if ( tAddrItem.emItemType == emEntryItem )
			{
                TAddrInfo tAddrInfo = tAddrItem.tAddrInfo;
                if ( tAddrInfo.dwInGroupIdx != INVALID_INDEX )
				{
                    if ( nIndex >= MAXNUM_ENTRY_TABLE )
                    {
                        return false;
                    }
                    adwEntryTable[nIndex] = tAddrInfo.dwEntryIdx;
                    nIndex++;
                }

                if ( bNeedCheckSel )
                {
                    if ( m_SelItem.tAddrInfo == tAddrInfo )
                    {
                        m_SelItem.SetNull();
                        bNeedCheckSel = FALSE;
                    }
                }
            }
            else
            {
                GetGroupAndLowGroup( tAddrItem.tGroupInfo.dwGroupIdx, vctDelGroup );
            }
        }

        if ( nIndex > 0 )
        {
            TADDRMULTISETENTRY tEntry;
            tEntry.SetEntryIndex( m_SelGroup.dwGroupIdx );
      	
            tEntry.SetListEntryIndex(adwEntryTable, nIndex);
            tEntry.SetListEntryNum(nIndex);
		    u16 wRe = ComInterface->DelEntryFromGroup(tEntry);
        }
        
    }

    if ( !vctDelGroup.empty() )
    {
        if ( vctDelGroup.size() == 1 )
        {
            u16 wRe = ComInterface->DeleteGroup( vctDelGroup.at(0) );
        }
        else
        {
            u16 wRe = ComInterface->DeleteMultiGroup( vctDelGroup );
        }
    }

	m_vctSelectList.clear();
	//m_SelItem.SetNull();
	UpdateUIState();

	return true;
}


bool CAddrEditLogic::OnBtnDeleteItem( const IArgs& args )
{
    if ( m_SelItem.IsNull() )
    {
        return false;
	}

    CString strMsg = "�Ƿ���ѡ��Ŀ�ӵ�ַ����ɾ��?";
    Args_MsgBox argMsg;
    argMsg.pOwnerWnd = UIManagePtr->GetWindowPtr( "AddrEditDlg" );
    int nResult = MSG_BOX( strMsg, TRUE, &argMsg);
    if ( IDOK == nResult )
    {
        if ( m_SelItem.emItemType == emEntryItem )
        {
            u16 wRe = ComInterface->DeleteEntry( m_SelItem.tAddrInfo.dwEntryIdx );
        }
        else
        {
            u16 wRe = ComInterface->DeleteGroup( m_SelItem.tGroupInfo.dwGroupIdx );
        }
        
        m_SelItem.SetNull();
        UIManagePtr->LoadScheme( "SchmNoShow", m_pWndTree );
    }
    
    
    return true;
}


bool CAddrEditLogic::OnBtnRefreshGlobalAddr( const IArgs& args )
{
	if ( m_vctSelectList.size() > 0 )
	{
		Args_MsgBox arg;
        arg.pOwnerWnd = UIManagePtr->GetWindowPtr( g_stcStrAddrEditDlg ); 
		int nResult = MSG_BOX( "ˢ�º������ѡ��Ŀ���Ƿ�����ˢ��?", TRUE, &arg );
		if ( IDOK == nResult )
		{
			IArgs args("");
			SureRefreshGlobalAddr(args);
		}
	}
	else
	{
		UIManagePtr->EnableWindow( m_strBtnRefresh, false, m_pWndTree ); 
				
		u16 re = BusinessManagePtr->UpdateGlobalAddrbook();
		if ( re != NO_ERROR )
		{
			return false;
		}

        Window* pWnd = UIManagePtr->GetWindowPtr( g_stcStrAddrEditDlg );	
		CMsgDispatch::SendMessage( UI_CNC_BEGINWAITING_REFRESH, (WPARAM)pWnd, /*emGetRegInfoType_CNS*/emWaitRegInfo );
	}
	
	return true;
}


bool CAddrEditLogic::SureRefreshGlobalAddr( const IArgs& args )
{
	m_vctSelectList.clear();
	UpdateUIState();

	UIManagePtr->EnableWindow( m_strBtnRefresh, false, m_pWndTree ); 
		
	u16 re = BusinessManagePtr->UpdateGlobalAddrbook();
	if ( re != NO_ERROR )
	{
		return false;
	}

    Window* pWnd = UIManagePtr->GetWindowPtr( g_stcStrAddrEditDlg );	
	CMsgDispatch::SendMessage( UI_CNC_BEGINWAITING_REFRESH, (WPARAM)pWnd, /*emGetRegInfoType_CNS*/emWaitRegInfo );

	return true;
}


bool CAddrEditLogic::OnBtnSelectAll( const IArgs& args )
{
	m_vctOperateList.clear();

    if ( m_bGlobalAddr )
    {
        if ( !m_bSearchEdit )
        {
            m_vctSelectList = m_vctGlobalList;
        }
        else
        {
            m_vctSelectList = m_vctSearchList;
        }
    }
    else
    {
        if ( !m_bSearchEdit && m_SelGroup.IsNull() && (m_emShowState == emShowAllAddr) )
        {
            m_vctSelectList = *ComInterface->GetAddrEntryList();   
        }
        else
        {
            //��û��ѡ�е��ѡ��
            for ( int i = 0; i < m_vctShowList.size(); i++ )
            {
                TAddrItem tItem = m_vctShowList.at(i);
                if ( tItem.emItemType == emEntryItem && tItem.strImg == "AddrEditSelItem" )
                {
                    tItem.strImg.Empty();
                    m_vctSelectList.push_back( tItem );
                }
            }        
        }
    } 

    //ȫѡʱ��ѡ�б�λ���ö�
    Value_TransparentListOffset valueOffset;
    valueOffset.nOffset = 0;
	UIManagePtr->SetPropertyValue( valueOffset, m_strListMultiSel, m_pWndTree );

	UpdateShowList();

	UpdateUIState();
	return true;
}

bool CAddrEditLogic::OnBtnUnSelectAll( const IArgs& args )
{	
	m_vctOperateList.clear();

    if ( !m_bSearchEdit && ( m_bGlobalAddr || m_emShowState == emShowAllAddr ) )
    {
        m_vctSelectList.clear();
    }
    else
    {
        for ( int i = 0; i < m_vctShowList.size(); i++ )
        {
            TAddrItem tShowItem = m_vctShowList.at(i);
            if ( tShowItem.emItemType != emEntryItem )
            {
                continue;
            }
            vector<TAddrItem>::iterator itfind = find( m_vctSelectList.begin(), m_vctSelectList.end(), tShowItem );
        
            if ( itfind != m_vctSelectList.end() )
            {
                m_vctSelectList.erase( itfind );
            }
        }     
    }

    Value_TransparentListOffset valueOffset;
    valueOffset.nOffset = 0;
	UIManagePtr->SetPropertyValue( valueOffset, m_strListMultiSel, m_pWndTree );

	UpdateShowList();

	UpdateUIState();
	return true;
}

void CAddrEditLogic::LoadToLocal()
{
	BOOL bFindSame = FALSE;
	CAddrBook cAddrBook = ComInterface->GetAddrBook();
	TAddrItem tAddrItem = m_vctSelectList.at(m_dwGlobalAddrIndex);

    CAddrEntry cAddrEntry;
	
	if ( tAddrItem.emItemType == emEntryItem )
	{
		u32 dwSize = cAddrBook.GetAddrEntryUsedSize();
		if ( dwSize >= MAX_ADDRENTRY )
		{
			CString strErr;
			strErr.Format( "�᳡��Ŀ�Ѵﵽ���ֵ%d��", MAX_ADDRENTRY );
			Args_MsgBox msgArg;
			msgArg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;
			MSG_BOX( strErr, FALSE, &msgArg );
			return;
		}

        /*
		if ( strcmp( tAddrItem.tAddrInfo.achEntryName, "" ) != 0 )
		{
			u32 dwNum = cAddrBook.GetAddrEntryByName( tAddrItem.tAddrInfo.achEntryName, &cAddrEntry );
			if ( dwNum > 0 )
			{             
                s8 aszE164[MAX_E164NUM_LEN + 1] = _T("");       //E164��                 
	            cAddrEntry.GetMtNumber( aszE164, cAddrEntry.GetMtNumberLen() + 1 );
				continue;
			}				
		}

		if ( strcmp( tAddrItem.tAddrInfo.achE164, "" ) != 0 )
		{
			u32 dwNum = cAddrBook.GetAddrEntryByNumber( tAddrItem.tAddrInfo.achE164, &cAddrEntry );
			if ( dwNum > 0 )
			{
                s8 aszEntryName[MAX_NAME_LEN + 1] = _T("");     //��Ŀ����
                cAddrEntry.GetEntryName( aszEntryName, cAddrEntry.GetEntryNameLen() + 1 );
                continue;
            }
        }
        
        for ( int i = 0; i < m_vctLocalList.size(); i++ )
        {
            TAddrItem tItem = m_vctLocalList.at(i);
            if ( tItem.emItemType != emEntryItem )
            {
                continue;
            }
            if ( strcmp( tAddrItem.tAddrInfo.achEntryName, tItem.tAddrInfo.achEntryName ) == 0 &&
                strcmp( tAddrItem.tAddrInfo.achE164, tItem.tAddrInfo.achE164 ) == 0 )
            {
                bFindSame = TRUE;
                break;
            }
        }*/

        cAddrEntry.SetEntryName( tAddrItem.tAddrInfo.achEntryName );
        cAddrEntry.SetMtNumber( tAddrItem.tAddrInfo.achE164 );
        
        TADDRENTRY tentry;
        ZeroMemory(&tentry, sizeof(TADDRENTRY));
        tentry.SetEntryIndex(cAddrEntry.GetEntryIndex());
        TADDRENTRYINFO info;
        ZeroMemory(&info, sizeof(TADDRENTRYINFO));
        cAddrEntry.GetEntryInfo(&info);
        tentry.SetEntryInfo(&info);
        
        BOOL32 bExist = (cAddrBook.IsAddrEntryExist(info) == INVALID_INDEX) ? FALSE : TRUE; 
        if (bExist)
        {
            bFindSame = TRUE;
		}
    }

	m_dwGlobalAddrIndex++;
	
	if ( !bFindSame )
	{
		m_bLoadToLocal = TRUE;
		//CAddrEntry cAddrEntry;
		//cAddrEntry.SetEntryName( tAddrItem.tAddrInfo.achEntryName );
		//cAddrEntry.SetMtNumber( tAddrItem.tAddrInfo.achE164 );
		
        u16 wRe = ComInterface->AddEntry( cAddrEntry );
	} 
	else
	{
		if ( m_dwGlobalAddrIndex < m_vctSelectList.size() )
		{
			LoadToLocal();
			return;
		}
	}

	if ( m_dwGlobalAddrIndex == m_vctSelectList.size() )
	{
		m_dwGlobalAddrIndex = 0;
		ComInterface->SetAddrLoadingState(FALSE);

		m_vctSelectList.clear();
		UpdateShowList();
		UpdateUIState();

		if ( m_bLoadToLocal )
		{
			m_bLoadToLocal = FALSE;
			KillTimer( NULL, g_nTmHandleNtyLoadNum );
			CMsgDispatch::SendMessage( UI_CNC_ENDWAITING_REFRESH, 0, 0 );
		}
	}
}

bool CAddrEditLogic::OnBtnLoadToLocal( const IArgs& args )
{
	m_dwGlobalAddrIndex = 0;
	ComInterface->SetAddrLoadingState(TRUE);
	m_bLoadToLocal = FALSE;

	LoadToLocal();

	if ( m_bLoadToLocal )
	{
		g_nTmHandleNtyLoadNum = SetTimer( NULL, 0, 1000, CNtyLoadNumTimerFun );

		Window* pWnd = UIManagePtr->GetWindowPtr( g_stcStrAddrEditDlg );
		CMsgDispatch::SendMessage( UI_CNC_BEGINWAITING_REFRESH, (WPARAM)pWnd, emWaitLoadAddr );
	}

	return true;
}


/*=============================================================================
�� �� ��:UpdateAddrBook
��    ��:��Ӧ���±��ص�ַ����Ϣ
��    ��:��
ע    ��:ͬʱ���µ�ǰ��ʾ�б�
�� �� ֵ:��
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���   �޸�����
2012/04/01  1.0     Ф��Ȼ     ����
=============================================================================*/
LRESULT CAddrEditLogic::UpdateAddrBook(WPARAM wParam, LPARAM lParam)
{
	if ( ComInterface->GetAddrLoadingState() )
	{
		LoadToLocal();

		return NO_ERROR;
	}

	if( m_pWndTree == NULL )
	{
		return NO_ERROR;
	}
		
	UpdateLocalAddrList();

	if ( !m_SelGroup.IsNull() )	
	{
		GetAddrGroupMember( m_SelGroup.dwGroupIdx );
	}
	
	if ( m_bSearchEdit )
	{
		IArgs args( "NULL" );
		OnSearchEditChange( args );
	}

	if ( !m_SelItem.IsNull() )
	{
		if ( m_bWaitAddEntry )
		{
			Value_TransparentListSelItem valSel;
			valSel.dwDataKey = m_SelItem.tAddrInfo.dwEntryIdx;
			UIManagePtr->SetPropertyValue( valSel, m_strListLocalAddr, m_pWndTree );
			
			m_bWaitAddEntry = FALSE;
		}		

		if ( m_bWaitAddGroup )
		{
			Value_TransparentListSelItem valSel;
			valSel.dwDataKey = m_SelItem.tGroupInfo.dwGroupIdx + MAX_ADDRENTRY;
			UIManagePtr->SetPropertyValue( valSel, m_strListLocalAddr, m_pWndTree );
			
			m_bWaitAddGroup = FALSE;
		}
	}	

    UpdateUIState();

	return NO_ERROR;
}


LRESULT CAddrEditLogic::UpdateGlobalAddrBook( WPARAM wParam, LPARAM lParam )
{
	if( m_pWndTree == NULL )
	{
		return NO_ERROR;
	}
		
	UpdateGlobalAddrList();

// 	if ( m_bSearchEdit )
// 	{
// 		IArgs args( "NULL" );
// 		OnSearchEditChange( args );
// 	}

//  CMsgDispatch::SendMessage( UI_CNC_ENDWAITING_REFRESH, 0, 0 );
// 	UIManagePtr->EnableWindow( m_strBtnRefresh, true, m_pWndTree );

	return NO_ERROR;
}


void CAddrEditLogic::UpdateLocalAddrList()
{
	m_vctLocalList.clear();
	m_vctLocalList = *ComInterface->GetLocalAddrList();

	UpdateShowList();
}

void CAddrEditLogic::UpdateGlobalAddrList()
{
	m_vctGlobalList.clear();
	m_vctGlobalList = *ComInterface->GetGlobalAddrList();

    //��ʱ��ˢ�£���UpdateAddrbookʱһ��ˢ�� -xcr
	//UpdateShowList();
}


LRESULT CAddrEditLogic::OnAddEntryNty( WPARAM wParam, LPARAM lParam )
{
	if ( !m_bWaitAddEntry )
	{
		return NO_ERROR;
	}

	u32 dwEntryIndex = (u32)wParam;

    CAddrBook cAddrBook = ComInterface->GetAddrBook();
    CAddrEntry cEntry;
    cAddrBook.GetAddrEntry( &cEntry, dwEntryIndex );
    
    TAddrInfo tAddrInfo;
    SetAddrItemInfo( tAddrInfo, cEntry );

	if ( !m_SelGroup.IsNull() )
	{
		TADDRMULTISETENTRY tEntry;
		
		u32 adwEntryTable[1] = {0};
		tEntry.SetEntryIndex( m_SelGroup.dwGroupIdx );
		adwEntryTable[0] = dwEntryIndex;
		tEntry.SetListEntryIndex(adwEntryTable, 1);
		tEntry.SetListEntryNum(1);
		u16 wRe = ComInterface->AddEntryToGroup(tEntry);		
	}

	m_SelItem.emItemType = emEntryItem;
	m_SelItem.tAddrInfo = tAddrInfo;

	return NO_ERROR;
}

LRESULT CAddrEditLogic::OnAddGroupNty( WPARAM wParam, LPARAM lParam )
{
	if ( !m_bWaitAddGroup )
	{
		return NO_ERROR;
	}
	
	TGroupInfo tGroupInfo;
	u32 dwGroupIndex = (u32)wParam;
	tGroupInfo.dwGroupIdx = dwGroupIndex;
	strncpy( tGroupInfo.achGroupName, (s8*)lParam, TP_MAX_ALIAS_LEN_CNC+1 ); 

	if ( !m_SelGroup.IsNull() )
	{
		u16 wRe = ComInterface->AddGroupToGroup( dwGroupIndex, m_SelGroup.dwGroupIdx );
	}

	m_SelItem.emItemType = emGroupItem;
	m_SelItem.tGroupInfo = tGroupInfo;

	return NO_ERROR;
}

LRESULT CAddrEditLogic::OnAddrModifyNty( WPARAM wParam, LPARAM lParam )
{
	BOOL bEntry = (BOOL)wParam;
	CAddrBook cAddrBook = ComInterface->GetAddrBook();

	if ( bEntry )
	{
		if ( m_SelItem.emItemType != emEntryItem || m_SelItem.tAddrInfo.dwEntryIdx != lParam )
		{
			return NO_ERROR;
		}
		
		CAddrEntry cEntry;
		cAddrBook.GetAddrEntry( &cEntry, m_SelItem.tAddrInfo.dwEntryIdx );
		
		TAddrInfo tAddrInfo;
		SetAddrItemInfo( tAddrInfo, cEntry );
		m_SelItem.tAddrInfo = tAddrInfo;	
		//m_bWaitAddEntry = TRUE;//�����޸ĺ��б��λ��
	}
	else
	{
		if ( m_SelItem.emItemType != emGroupItem || m_SelItem.tGroupInfo.dwGroupIdx != lParam )
		{
			return NO_ERROR;
		}
		
		TGroupInfo tGroupInfo;
		ComInterface->GetAddrGroupInfo( m_SelItem.tGroupInfo.dwGroupIdx, tGroupInfo );

		m_SelItem.tGroupInfo = tGroupInfo;
		//m_SelGroup = tGroupInfo;
		//m_bWaitAddGroup = TRUE;

		UpdateAddrTitle();	
	}
	return NO_ERROR;
}


LRESULT CAddrEditLogic::OnAddrOptFailed(WPARAM wParam, LPARAM lParam)
{
    u16 wCmd = wParam;
    switch( wCmd )
    {
    case ADDRBOOK_ADD_ENTRY_REQ:
        ShowPopMsg( "�½��᳡ʧ��");
        break;
    case ADDRBOOK_MODIFYENTRY_REQ:
        ShowPopMsg( "�޸Ļ᳡ʧ��");
        break;
    case ADDRBOOK_DEL_ENTRY_REQ:
        ShowPopMsg( "ɾ���᳡ʧ��");
        break;
    case ADDRBOOK_ADD_MULSETENTRY_REQ:
        ShowPopMsg( "�½�����ʧ��");
        break;
    case ADDRBOOK_MODIFYMULSETENTRY_REQ:
        ShowPopMsg( "�޸ķ���ʧ��");
        break;
    case ADDRBOOK_DEL_MULSETENTRY_REQ:
        ShowPopMsg( "ɾ������ʧ��");
        break;
    case ADDRBOOK_ADD_ENTRYTOMULSET_REQ:
        ShowPopMsg( "��ӻ᳡������ʧ��");
        break;
    case ADDRBOOK_DEL_ENTRYFRMULSET_REQ:
        ShowPopMsg( "�ӷ�����ɾ���᳡ʧ��");
        break;
    default:
        break;
    }
    UIManagePtr->LoadScheme( "SchmNoShow", m_pWndTree );
    return NO_ERROR;
}


/*=============================================================================
�� �� ��:UnSelAddrList
��    ��:��Ӧ�б�û��ѡ������Ϣ
��    ��:��
ע    ��:
�� �� ֵ:��
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���   �޸�����
2012/04/01  1.0     Ф��Ȼ     ����
=============================================================================*/
bool CAddrEditLogic::UnSelAddrList( const IArgs& args )
{
	m_SelItem.SetNull();
	if ( m_vctSelectList.empty() && m_vctOperateList.empty() )
	{
		UIManagePtr->LoadScheme( "SchmNoShow", m_pWndTree );
	}
	
	return true;
}


/*=============================================================================
�� �� ��:UpdateShowList
��    ��:���µ�ǰ��ʾ�б�
��    ��:��
ע    ��:
�� �� ֵ:��
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���   �޸�����
2012/04/01  1.0     Ф��Ȼ     ����
=============================================================================*/
void CAddrEditLogic::UpdateShowList()
{	
	//String strCaption;
	//UIManagePtr->GetCaption( m_strEdtSearch, strCaption, m_pWndTree );
	if ( !m_bSearchEdit )
	{
		if ( m_bGlobalAddr )
		{
			m_vctShowList = m_vctGlobalList;
		}
		else
		{
			if ( m_SelGroup.IsNull() )
			{
				m_vctShowList = m_vctLocalList;
			}
			else
			{
				m_vctShowList = m_vctGroupMemberList;
			}
		}		
	}
	else
	{
		m_vctShowList = m_vctSearchList;
	}

    if ( !m_bGlobalAddr )
    {
        //�������ɸѡ�����Ŀ
        GetOptnShowList( m_vctShowList );
    }   
	
	for ( int i = 0; i < m_vctShowList.size(); i++ )
	{
        TAddrItem tShowItem = m_vctShowList.at(i);
        if ( tShowItem.emItemType != emEntryItem )
        {
            m_vctShowList.at(i).strImg = "AddrEditEnterGroupItem";
            continue;
        }

		vector<TAddrItem>::iterator itfind = find( m_vctSelectList.begin(), m_vctSelectList.end(), tShowItem );
		
		if ( itfind == m_vctSelectList.end() )
		{
			m_vctShowList.at(i).strImg = "AddrEditSelItem";
		}
		else
		{
			m_vctShowList.at(i).strImg = "AddrEditUnSelItem";
		}
	}
	
	if ( m_bGlobalAddr )
	{
		Value_TouchListAddr touchListAddr( &m_vctShowList, NULL, "CAddrEditLogic::OnClickGlobalAddrItem", TRUE, m_bGlobalAddr );
		UIManagePtr->SetPropertyValue( touchListAddr , m_strListGlobalAddr, m_pWndTree );
	}
	else
	{		
		Value_TouchListAddr touchListAddr( &m_vctShowList, NULL, "CAddrEditLogic::OnClickAddrItem" );
		UIManagePtr->SetPropertyValue( touchListAddr , m_strListLocalAddr, m_pWndTree );		
	}
}


void CAddrEditLogic::UpdateAllSelButton()
{
    //ȫѡֻ��ѡ��᳡��Ŀ����ɸѡ���᳡��Ŀ
    vector<TAddrItem> vctShowEntryList;
    
    //�򵥱Ƚϣ���ͨ�������ж��Ƿ�ȫѡ
    BOOL bEasyCompare = FALSE;
    if ( m_bGlobalAddr )
    {
        if ( !m_bSearchEdit )
        {
            vctShowEntryList = m_vctGlobalList;
            bEasyCompare = TRUE;
        }       
    }
    else
    {
        if ( m_emShowState == emShowAllAddr )
        {
            if ( !m_bSearchEdit && m_SelGroup.IsNull() )
            {
                vctShowEntryList = *ComInterface->GetAddrEntryList();
                bEasyCompare = TRUE;
            }    
        }
        else if ( m_emShowState == emShowGroup )
        {
            vctShowEntryList.clear();
            bEasyCompare = TRUE;
        }
    }     
    
    if ( bEasyCompare )
    {
        if ( vctShowEntryList.empty() )
        {
            UIManagePtr->LoadScheme( "SchmNoAllSel", m_pWndTree );
            UIManagePtr->EnableWindow( m_strBtnAllSel, false, m_pWndTree );
        }
        else
        {
            UIManagePtr->EnableWindow( m_strBtnAllSel, true, m_pWndTree );
            
            //��᳡�����б��л᳡����Ŀ�뱾���б�᳡��Ŀһ��,ȫѡ��ť��Ϊȡ��ȫѡ
            if ( m_vctSelectList.size() != vctShowEntryList.size() )		
            {
                UIManagePtr->LoadScheme( "SchmNoAllSel", m_pWndTree );
            } 
            else
            {
                UIManagePtr->LoadScheme( "SchmAllSel", m_pWndTree );
            }
	    }
    }
    else
    {
        int nEntryNum = 0;
        BOOL bAllSel = TRUE;
        for ( int i = 0; i < m_vctShowList.size(); i++ )
        {
            TAddrItem tItem = m_vctShowList.at(i);
            if ( tItem.emItemType == emEntryItem )
            {
                nEntryNum++;
                if ( tItem.strImg == "AddrEditSelItem" )
                {
                    bAllSel = FALSE;
                    break;
                }
            }
        }

        if ( nEntryNum == 0 )
        { 
            UIManagePtr->LoadScheme( "SchmNoAllSel", m_pWndTree );
            UIManagePtr->EnableWindow( m_strBtnAllSel, false, m_pWndTree );
        }
        else
        {
            UIManagePtr->EnableWindow( m_strBtnAllSel, true, m_pWndTree );

            if ( bAllSel )
            {
                UIManagePtr->LoadScheme( "SchmAllSel", m_pWndTree );
            }
            else
            {
                UIManagePtr->LoadScheme( "SchmNoAllSel", m_pWndTree );
            }
        }       
    }
    
}


void CAddrEditLogic::SetAddrItemInfo( TAddrInfo& tAddrInfo, CAddrEntry& cAddrEntry )
{
	s8 aszEntryName[MAX_NAME_LEN + 1] = _T("");     //��Ŀ����
	s8 aszE164[MAX_E164NUM_LEN + 1] = _T("");       //E164��

	cAddrEntry.GetEntryName( aszEntryName, cAddrEntry.GetEntryNameLen() + 1 );
	cAddrEntry.GetMtNumber( aszE164, cAddrEntry.GetMtNumberLen() + 1 );
	
	tAddrInfo.dwEntryIdx = cAddrEntry.GetEntryIndex();
	strncpy( tAddrInfo.achEntryName, aszEntryName, TP_MAX_ALIAS_LEN_CNC+1 );
	strncpy( tAddrInfo.achE164, aszE164, MAX_E164NUM_LEN+1 );
}


/*=============================================================================
�� �� ��:GetAddrGroupMember
��    ��:��ȡ��ˢ�·����Ա�б�
��    ��:dwGroupIndex ������
ע    ��:
�� �� ֵ:��
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���   �޸�����
2012/04/01  1.0     Ф��Ȼ     ����
=============================================================================*/
void CAddrEditLogic::GetAddrGroupMember( u32 dwGroupIndex )
{
	ComInterface->GetAddrGroupMember( dwGroupIndex, m_vctGroupMemberList );

	UpdateShowList();
}

/*=============================================================================
�� �� ��:DelGroupAndLowGroup
��    ��:ɾ���鼰���¼�����
��    ��:dwGroupIndex ������
ע    ��:
�� �� ֵ:��
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���   �޸�����
2012/06/01  1.0     Ф��Ȼ     ����
=============================================================================*/
void CAddrEditLogic::DelGroupAndLowGroup( u32 dwGroupIndex )
{
	bool bValid = ComInterface->GetAddrBook().IsAddrMultiSetEntryValid( dwGroupIndex );
	if ( !bValid )
	{
		return;
	}

	//�¼�����
	u32 *pdwGroup = new u32[MAX_ADDRGROUP];
	u32 dwNum = ComInterface->GetAddrBook().FindLowGroupOfGroupByIndex( dwGroupIndex, pdwGroup );
	
	for ( int i = 0; i < dwNum; i++ )
	{
		u32 dwLowGroupIndex = *(pdwGroup + i);
			
		DelGroupAndLowGroup( dwLowGroupIndex );		
	}

	delete []pdwGroup;
	pdwGroup = NULL;

	u16 wRe = ComInterface->DeleteGroup( dwGroupIndex );
}


void CAddrEditLogic::GetGroupAndLowGroup( u32 dwGroupIndex, vector<u32>& vctGroup )
{
    bool bValid = ComInterface->GetAddrBook().IsAddrMultiSetEntryValid( dwGroupIndex );
    if ( !bValid )
    {
        return;
    }
    vctGroup.push_back( dwGroupIndex );
    
    //�¼�����
    u32 *pdwGroup = new u32[MAX_ADDRGROUP];
    u32 dwNum = ComInterface->GetAddrBook().FindLowGroupOfGroupByIndex( dwGroupIndex, pdwGroup );
    
    for ( int i = 0; i < dwNum; i++ )
    {
        u32 dwLowGroupIndex = *(pdwGroup + i);
     
        GetGroupAndLowGroup( dwLowGroupIndex, vctGroup );		
    }
    
    delete []pdwGroup;
    pdwGroup = NULL;
}



LRESULT CAddrEditLogic::OnWaitRefreshOverTime( WPARAM wParam, LPARAM lParam )
{
	if( m_pWndTree == NULL )
	{
		return NO_ERROR;
	}
	
	//2013.1.16 yjj 
	bool bVis = UIFACTORYMGR_PTR->IsVisible( g_stcStrAddrbookDlg );
	bool bVisSelf = UIFACTORYMGR_PTR->IsVisible( "", m_pWndTree );
	if ( !bVis && !bVisSelf )
	{
		return S_OK;
	}

	BusinessManagePtr->ClearSipRegInfo( emGetRegInfoType_CNS );

//	EmGetRegInfoType emType = (EmGetRegInfoType)wParam;
	
//	if ( emType == emGetRegInfoType_CNS )
	{
		UIManagePtr->EnableWindow( m_strBtnRefresh, true, m_pWndTree );	
		m_vctGlobalList.clear();
		UpdateShowList();
	}
	return NO_ERROR;
}



void CAddrEditLogic::Clear()
{
	m_SelItem.SetNull();
	m_SelGroup.SetNull();
	m_vctLocalList.clear();
	m_vctGlobalList.clear();
	m_vctGroupMemberList.clear();
	m_vctSelectList.clear();
	m_vctShowList.clear();
	m_vctSearchList.clear();
	m_vctOperateList.clear();
	m_vctListOffset.clear();
	m_bGlobalAddr = FALSE;
    m_bSearchEdit = FALSE;
	m_emAddrBookType = em_AddrBook_Normal;
    m_emShowState = emShowAllAddr;
	UpdateShowOption();
	m_bLoadToLocal = FALSE;
	KillTimer( NULL, g_nTmHandleNtyLoadNum );

    if( UIManagePtr->IsVisible( m_strAddrEditOptnDlg ) ) //dyy 2013��9��23�� 
    {
        UIManagePtr->ShowWindow( m_strAddrEditOptnDlg, false );
    }

	UIManagePtr->LoadScheme( "", m_pWndTree, "", false );
}


bool CAddrEditLogic::OnBtnAddrShowOptn( const IArgs & arg )
{ 
    bool bOn = false;
    UIManagePtr->GetSwitchState( m_strBtnAddrShowEx, bOn, m_pWndTree );
    if ( bOn )
    {   
        Value_WindowPos valPos;
        UIManagePtr->GetPropertyValue( valPos, m_strBtnAddrShowEx, m_pWndTree );
        
        valPos.nX = valPos.nX + 52;
        valPos.nY = valPos.nY - 7;
        UIManagePtr->SetPropertyValue( valPos, m_strAddrEditOptnDlg );

        Value_WindowOwer owerVal;
        owerVal.pWnd = UIManagePtr->GetWindowPtr( g_stcStrAddrEditDlg );
        UIManagePtr->SetPropertyValue( owerVal, m_strAddrEditOptnDlg );
        UIManagePtr->ShowWindow( m_strAddrEditOptnDlg );
    }
    else
    {
        UIManagePtr->ShowWindow( m_strAddrEditOptnDlg, false );
    }
    return true; 
}

//������ʾѡ����Ϣ
void CAddrEditLogic::UpdateShowOption()
{ 
    if ( m_pWndTree == NULL )
    {
        return;
    }
    
    vector<String> vcItem; 
    vcItem.push_back( "ImageItemSelected" );   
    
    ARRAY<TMenuItemInfo> menuLst;     
    TMenuItemInfo tMenu;
            
    tMenu.strTxt = _T("��ʾȫ��");
    tMenu.strItemFunc = "CAddrEditLogic::OnAddrOptnShowAll";
    tMenu.strImageItem = "TempListItem";  
    tMenu.strTxtItem = "TextItem"; 
    if ( m_emShowState == emShowAllAddr )
    { 
        tMenu.m_pVctSubItem = &vcItem;
    } 
    menuLst.push_back( tMenu );
    
    tMenu.Clear();
    tMenu.strTxt = _T("��ʾ��");
    tMenu.strImageItem = "TempListItem";  
    tMenu.strTxtItem = "TextItem";     
    tMenu.strItemFunc = "CAddrEditLogic::OnAddrOptnShowGroup";
    if ( m_emShowState == emShowGroup )
    {   
        tMenu.m_pVctSubItem = &vcItem;
    }  
    menuLst.push_back( tMenu );
    
    tMenu.Clear();
    tMenu.strTxt = _T("��ʾ����");
    tMenu.strImageItem = "TempListItem" ;  
    tMenu.strTxtItem = "TextItem";  
    tMenu.strItemFunc = "CAddrEditLogic::OnAddrOptnShowOnline";
    if ( m_emShowState == emShowOnline )
    {   
        tMenu.m_pVctSubItem = &vcItem;
    }     
    menuLst.push_back( tMenu );
    
    tMenu.Clear();
    tMenu.strTxt = _T("��ʾ������");
    tMenu.strImageItem = "TempListItem";  
    tMenu.strTxtItem = "TextItem";  
    tMenu.strItemFunc = "CAddrEditLogic::OnAddrOptnShowOffline";
    if ( m_emShowState == emShowOffline )
    {
        tMenu.m_pVctSubItem = &vcItem;
    }   
    menuLst.push_back( tMenu );

    tMenu.Clear();
    tMenu.strTxt = _T("�½���...");
    tMenu.strImageItem = "TempListItem";  
    tMenu.strTxtItem = "TextItem";  
    tMenu.strItemFunc = "CAddrEditLogic::OnAddGroup";
    vector<String> vctItem1; 
    vctItem1.push_back( "AddrAddGroupItem" );
    tMenu.m_pVctSubItem = &vctItem1;
    menuLst.push_back( tMenu );

    tMenu.Clear();
    tMenu.strTxt = _T("�����ַ��...");
    tMenu.strImageItem = "TempListItem";  
    tMenu.strTxtItem = "TextItem";  
    tMenu.strItemFunc = "CAddrEditLogic::OnBtnGlobalAddr";
    vector<String> vctItem2; 
    vctItem2.push_back( "AddrLoadItem" );
    tMenu.m_pVctSubItem = &vctItem2;
    menuLst.push_back( tMenu );
      
    Value_TouchListMenu val( &menuLst );  
    UIManagePtr->SetPropertyValue( val, m_strLstAddrShowOptn );
}

bool CAddrEditLogic::OnAddrOptnShowAll( const IArgs & arg )
{
    if ( m_emShowState == emShowAllAddr )
    {
        return true;
    }
    m_emShowState = emShowAllAddr;
    UpdateShowOption();
    UpdateShowList();
    UpdateAllSelButton();

    return true;
}

bool CAddrEditLogic::OnAddrOptnShowGroup( const IArgs & arg )
{   
    if ( m_emShowState == emShowGroup )
    {
        return true;
    }
    
    m_emShowState = emShowGroup;
    UpdateShowOption();
    UpdateShowList();
    UpdateAllSelButton();

    return true;
}

bool CAddrEditLogic::OnAddrOptnShowOnline( const IArgs & arg )
{
    if ( m_emShowState == emShowOnline )
    {
        return true;
    }
    m_emShowState = emShowOnline;
    UpdateShowOption();
    UpdateShowList();
    UpdateAllSelButton();

    return true;
}

bool CAddrEditLogic::OnAddrOptnShowOffline( const IArgs & arg )
{
    if ( m_emShowState == emShowOffline )
    {
        return true;
    }
    m_emShowState = emShowOffline;
    UpdateShowOption();
    UpdateShowList();
    UpdateAllSelButton();

    return true;
}

void CAddrEditLogic::GetOptnShowList( vector<TAddrItem>& vctCurrentList )
{
    if ( m_emShowState == emShowAllAddr )
    {
        return;
    }
    
    vector<TAddrItem> vctList = vctCurrentList;
    vctCurrentList.clear();
    if ( m_emShowState == emShowOnline )
    {
        for ( int i = 0; i < vctList.size(); i++ )
        {
            TAddrItem tAddrItem = vctList.at(i);
            if ( tAddrItem.emItemType == emGroupItem )
            {
                continue;
            }
            if ( tAddrItem.tAddrInfo.bOnLine )
            {
                vctCurrentList.push_back( tAddrItem );
            }
        }
    }
    else if ( m_emShowState == emShowOffline )
    {
        for ( int i = 0; i < vctList.size(); i++ )
        {
            TAddrItem tAddrItem = vctList.at(i);
            if ( tAddrItem.emItemType == emGroupItem )
            {
                continue;
            }
            if ( !tAddrItem.tAddrInfo.bOnLine )
            {
                vctCurrentList.push_back( tAddrItem );
            }
        }
    }
    else if ( m_emShowState == emShowGroup )
    {
        for ( int i = 0; i < vctList.size(); i++ )
        {
            TAddrItem tAddrItem = vctList.at(i);
            if ( tAddrItem.emItemType == emGroupItem )
            {
                vctCurrentList.push_back( tAddrItem );
            }

        }
    }
}

u32 CAddrEditLogic::GetLoadAddrNum()
{
	u32 dwLoadAddrNum = m_vctSelectList.size() - m_dwGlobalAddrIndex;
	return dwLoadAddrNum;
}



void CAddrEditLogic::SetAddrListSelValue( Data_AddrItemInfo& ItemInfo, String strWndName, const IWndTree* pWndTree )
{
    const IWndTree *pItem = UIManagePtr->GetWindow ( strWndName, pWndTree );
    if ( pItem == NULL )
    {
        return ;
    }
    int nDataKey = ItemInfo.GetDataKey();
    
    if ( CTransparentList* pList = dynamic_cast<CTransparentList*>(const_cast<Window*>(pItem->m_ptItemData->pWnd)) )
    {  
        IItemList* pItemList = pList->GetRoot();
        
        int nItemCount = pItemList->GetItemCount();
        
        for ( int nIndex = 0; nIndex < nItemCount; nIndex++ )
        {
            IItemList* pSubList = pItemList->GetItemByIndex( nIndex );
            if ( pSubList != NULL )
            {
                IBaseItem* pSubItem = pSubList->GetItemData();
                if ( pSubItem != NULL && pSubItem->GetUserData() != NULL )
                {		
                    IData* pData = const_cast<IData*>( pSubItem->GetUserData() );
                    if ( pData->GetDataKey() == nDataKey )
                    {
                        TAddrItem tAddrItem = ItemInfo.m_tAddrItem;
                        
                        if ( !tAddrItem.strImg.IsEmpty() )
                        {
                            String strImg;
                            
                            IItemList* pSubList2 = pSubList->GetItemByIndex( 1 );
                            if ( pSubList2 != NULL )
                            {
                                IBaseItem* pSubItem2 = pSubList2->GetItemData();
                                
                                String strPath = UIManagePtr->GetImagePath();
                                if ( tAddrItem.strImg == "AddrEditUnSelItem" )
                                {                                  
                                    pSubItem2->SetImageFolder( strPath + "addrbook/addrSelImg" );                                 
                                    pSubItem2->SetFunc( "CAddrEditLogic::OnSelAddrItem" );
                                    
                                    ItemInfo.m_tAddrItem.strImg = "AddrEditSelItem";
                                }
                                else
                                {
                                    pSubItem2->SetImageFolder( strPath + "addrbook/addrUnSelImg" );                                 
                                    pSubItem2->SetFunc( "CAddrEditLogic::OnUnSelAddrItem" );
                                    
                                    ItemInfo.m_tAddrItem.strImg = "AddrEditUnSelItem";
                                }                            
                                pSubItem->SetUserData( &ItemInfo );
                                pSubItem->SetItemStatus( emItemStatusNormal );
                                pSubItem2->SetItemStatus( emItemStatusNormal );
                            }
                        }
                        break;
                    }
                }		
            }
        }
        pList->SendMessage( WM_REDRAW_UI, 0, (LPARAM)0 );
    }
 
}