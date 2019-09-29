// addrbooklogic.cpp: implementation of the CAddrBookLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cms.h"
#include "addrbooklogic.h"
#include "TouchListProperty.h"
#include "AddrList.h"
#include <algorithm>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CAddrBookLogic * CAddrBookLogic::m_pAddrBookLogic = NULL;
const String CAddrBookLogic::m_strDlgNormal = "DlgNormal";
const String CAddrBookLogic::m_strListLocalAddr = "DlgNormal/LocalAddrList"; 
const String CAddrBookLogic::m_strListGlobalAddr = "DlgNormal/GlobalAddrList";  

const String CAddrBookLogic::m_strBtnBack = "DlgNormal/BtnBack";
const String CAddrBookLogic::m_strStcTitle = "DlgNormal/StTitle";
const String CAddrBookLogic::m_strEdtSearch = "DlgNormal/EdtSearch";
const String CAddrBookLogic::m_strBtnLocalAddr = "DlgNormal/BtnLocalAddr";
const String CAddrBookLogic::m_strBtnGlobalAddr = "DlgNormal/BtnGlobalAddr";
const String CAddrBookLogic::m_strBtnMultiCall = "DlgNormal/BtnMultiCall";
const String CAddrBookLogic::m_strDlgMultiCall = "DlgMultiCall";
const String CAddrBookLogic::m_strListMultiCall = "DlgMultiCall/MultiCallList";
const String CAddrBookLogic::m_strBtnCall = "DlgMultiCall/BtnCall";
const String CAddrBookLogic::m_strLetterIndex = "DlgNormal/IndexList";
const String CAddrBookLogic::m_strBtnRefresh = "DlgNormal/BtnRefresh";
const String CAddrBookLogic::m_strBtnAddrShowEx = "DlgNormal/BtnAddrShowEx";
const String CAddrBookLogic::m_strBtnAllSel = "DlgNormal/BtnAllSel";
const String CAddrBookLogic::m_strLstAddrShowOptn = "AddrShowOptnDlg/LstAddrMenu";
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CAddrBookLogic::CAddrBookLogic()
{
	m_bGlobalAddr = FALSE;
	m_bInConf = FALSE;
	m_bMultiCall = FALSE;
    m_bSearchEdit = FALSE;
    m_emAddrShowState = emShowAllAddr;
}

CAddrBookLogic::~CAddrBookLogic()
{
	if ( m_pAddrBookLogic != NULL )
	{   
		UnRegMsg();
		UnRegFunc();
		delete m_pAddrBookLogic;
		m_pAddrBookLogic = NULL;
	}
}


bool CAddrBookLogic::RegCBFun()
{
	REG_GOBAL_MEMBER_FUNC( "CAddrBookLogic::InitWnd", CAddrBookLogic::InitWnd, m_pAddrBookLogic, CAddrBookLogic );
	REG_GOBAL_MEMBER_FUNC( "CAddrBookLogic::OnBtnLocalAddr", CAddrBookLogic::OnBtnLocalAddr, m_pAddrBookLogic, CAddrBookLogic );
	REG_GOBAL_MEMBER_FUNC( "CAddrBookLogic::OnBtnGlobalAddr", CAddrBookLogic::OnBtnGlobalAddr, m_pAddrBookLogic, CAddrBookLogic );
	
	REG_GOBAL_MEMBER_FUNC( "CAddrBookLogic::OnSelAddrItem", CAddrBookLogic::OnSelAddrItem, m_pAddrBookLogic, CAddrBookLogic );
	REG_GOBAL_MEMBER_FUNC( "CAddrBookLogic::OnUnSelAddrItem", CAddrBookLogic::OnUnSelAddrItem, m_pAddrBookLogic, CAddrBookLogic );
	
	REG_GOBAL_MEMBER_FUNC( "CAddrBookLogic::OnClickAddrItem", CAddrBookLogic::OnClickAddrItem, m_pAddrBookLogic, CAddrBookLogic );
	//REG_GOBAL_MEMBER_FUNC( "CAddrBookLogic::OnClickAddrGroup", CAddrBookLogic::OnClickAddrGroup, m_pAddrBookLogic, CAddrBookLogic );
	REG_GOBAL_MEMBER_FUNC( "CAddrBookLogic::OnBtnBack", CAddrBookLogic::OnBtnBack, m_pAddrBookLogic, CAddrBookLogic );

	REG_GOBAL_MEMBER_FUNC( "CAddrBookLogic::OnMultiCall", CAddrBookLogic::OnMultiCall, m_pAddrBookLogic, CAddrBookLogic );
	REG_GOBAL_MEMBER_FUNC( "CAddrBookLogic::OnCancelMulti", CAddrBookLogic::OnCancelMulti, m_pAddrBookLogic, CAddrBookLogic );
	
	REG_GOBAL_MEMBER_FUNC( "CAddrBookLogic::OnCallMultiCn", CAddrBookLogic::OnCallMultiCn, m_pAddrBookLogic, CAddrBookLogic );
	REG_GOBAL_MEMBER_FUNC( "CAddrBookLogic::OnAddToMultiList", CAddrBookLogic::OnAddToMultiList, m_pAddrBookLogic, CAddrBookLogic );
	REG_GOBAL_MEMBER_FUNC( "CAddrBookLogic::OnDelFromMultiList", CAddrBookLogic::OnDelFromMultiList, m_pAddrBookLogic, CAddrBookLogic );
    REG_GOBAL_MEMBER_FUNC( "CAddrBookLogic::OnEnterAddrGroup", CAddrBookLogic::OnEnterAddrGroup, m_pAddrBookLogic, CAddrBookLogic );
	
	REG_GOBAL_MEMBER_FUNC( "CAddrBookLogic::OnSearchEditChange", CAddrBookLogic::OnSearchEditChange, m_pAddrBookLogic, CAddrBookLogic );
	REG_GOBAL_MEMBER_FUNC( "CAddrBookLogic::OnDragEnd", CAddrBookLogic::OnDragEnd, m_pAddrBookLogic, CAddrBookLogic );
	REG_GOBAL_MEMBER_FUNC( "CAddrBookLogic::OnDragItemOut", CAddrBookLogic::OnDragItemOut, m_pAddrBookLogic, CAddrBookLogic );

    REG_GOBAL_MEMBER_FUNC( "CAddrBookLogic::OnBtnRefresh", CAddrBookLogic::OnBtnRefresh, m_pAddrBookLogic, CAddrBookLogic );
    REG_GOBAL_MEMBER_FUNC( "CAddrBookLogic::OnBtnSelectAll", CAddrBookLogic::OnBtnSelectAll, m_pAddrBookLogic, CAddrBookLogic );
    REG_GOBAL_MEMBER_FUNC( "CAddrBookLogic::OnBtnUnSelectAll", CAddrBookLogic::OnBtnUnSelectAll, m_pAddrBookLogic, CAddrBookLogic );  
    REG_GOBAL_MEMBER_FUNC( "CAddrBookLogic::OnBtnAddrShowOptn", CAddrBookLogic::OnBtnAddrShowOptn, m_pAddrBookLogic, CAddrBookLogic );

    REG_GOBAL_MEMBER_FUNC( "CAddrBookLogic::OnAddrOptnShowAll", CAddrBookLogic::OnAddrOptnShowAll, m_pAddrBookLogic, CAddrBookLogic );
	REG_GOBAL_MEMBER_FUNC( "CAddrBookLogic::OnAddrOptnShowGroup", CAddrBookLogic::OnAddrOptnShowGroup, m_pAddrBookLogic, CAddrBookLogic );
    REG_GOBAL_MEMBER_FUNC( "CAddrBookLogic::OnAddrOptnShowOnline", CAddrBookLogic::OnAddrOptnShowOnline, m_pAddrBookLogic, CAddrBookLogic );
    REG_GOBAL_MEMBER_FUNC( "CAddrBookLogic::OnAddrOptnShowOffline", CAddrBookLogic::OnAddrOptnShowOffline, m_pAddrBookLogic, CAddrBookLogic );
	return true;
}

bool CAddrBookLogic::UnRegFunc()
{
	return true;
}

void CAddrBookLogic::RegMsg()
{
	REG_MSG_HANDLER( UI_CNS_ADDRBOOK_CHANGED, CAddrBookLogic::UpdateLocalAddrBook, m_pAddrBookLogic, CAddrBookLogic );
	REG_MSG_HANDLER( UI_CNS_REFRESH_GLOBAL_ADDRBOOK, CAddrBookLogic::UpdateGlobalAddrBook, m_pAddrBookLogic, CAddrBookLogic );
	
	//REG_MSG_HANDLER( UI_CNS_CONFSTATE_NOTIFY, CAddrBookLogic::OnConfStateNotify, m_pAddrBookLogic, CAddrBookLogic );

	REG_MSG_HANDLER( UI_CNC_WAITINGREFRESH_OVERTIME, CAddrBookLogic::OnWaitRefreshOverTime, m_pAddrBookLogic, CAddrBookLogic );
}


CAddrBookLogic* CAddrBookLogic::GetLogicPtr()
{
	if ( m_pAddrBookLogic == NULL )
	{  
		m_pAddrBookLogic = new CAddrBookLogic();  
	}

	return m_pAddrBookLogic;
}


bool CAddrBookLogic::InitWnd( const IArgs & args )
{
	CWndLogicBase::InitWnd( args );

	UpdateLocalAddrList();
	//UpdateGlobalAddrList();
    UpdateShowOption();
	
	CWnd * pList = UIManagePtr->GetWindowPtr( m_strListMultiCall, m_pWndTree );
	CDragWindow* p = CDragWindow::GetDragWindow();
	if ( p != NULL )
	{   
		p->RegisterDropWindow( pList );
	}

	return true;
}


bool CAddrBookLogic::OnBtnLocalAddr( const IArgs& args )
{
	m_bGlobalAddr = FALSE;
    
	UIManagePtr->SetCaption( m_strEdtSearch, "", m_pWndTree );

	m_SelGroup.SetNull();
	UpdateLocalAddrList();
	
	UIManagePtr->ShowWindow( m_strListGlobalAddr, false, m_pWndTree );
	UIManagePtr->ShowWindow( m_strListLocalAddr, true, m_pWndTree );
	UIManagePtr->ShowWindow( m_strBtnBack, false, m_pWndTree );
    UIManagePtr->ShowWindow( m_strBtnRefresh, false, m_pWndTree );
	
	UIManagePtr->EnableWindow( m_strBtnGlobalAddr, true, m_pWndTree );
	UIManagePtr->EnableWindow( m_strBtnLocalAddr, false, m_pWndTree );	

	Value_BindList bindListVal;
	bindListVal.strListName = m_strListLocalAddr;
	UIManagePtr->SetPropertyValue( bindListVal, m_strLetterIndex, m_pWndTree );

	UpdateAddrTitle();

	return true;
}

//点击全局地址簿
bool CAddrBookLogic::OnBtnGlobalAddr( const IArgs& args )
{
	m_bGlobalAddr = TRUE;

	UIManagePtr->SetCaption( m_strEdtSearch, "", m_pWndTree );

    m_SelGroup.SetNull();
	UpdateGlobalAddrList();

	UIManagePtr->ShowWindow( m_strListLocalAddr, false, m_pWndTree );
	UIManagePtr->ShowWindow( m_strListGlobalAddr, true, m_pWndTree );
	UIManagePtr->ShowWindow( m_strBtnRefresh, true, m_pWndTree );

	UIManagePtr->EnableWindow( m_strBtnLocalAddr, true, m_pWndTree );
	UIManagePtr->EnableWindow( m_strBtnGlobalAddr, false, m_pWndTree );

	Value_BindList bindListVal;
	bindListVal.strListName = m_strListGlobalAddr;
	UIManagePtr->SetPropertyValue( bindListVal, m_strLetterIndex, m_pWndTree );

	UpdateAddrTitle();
	
	return true;
}

bool CAddrBookLogic::OnDragEnd( const IArgs& args )
{
	Args_WindowMsg WinMsg = *dynamic_cast<const Args_WindowMsg*>(&args);
 	WindowMsg msg = WinMsg.m_Msg;
	
	s32 x = LOWORD(msg.lParam);
	s32 y = HIWORD(msg.lParam);
	CPoint point(x, y);
	
	Window* pWnd = UIManagePtr->GetWindowPtr( m_strListMultiCall, m_pWndTree );
	if ( pWnd->IsWindowVisible() )
	{
		Data_AddrItemInfo *pItemInfo = dynamic_cast<Data_AddrItemInfo*>( (IData*)msg.wParam );
		TAddrItem tAddrItem = pItemInfo->m_tAddrItem;

		for ( int i = 0; i < m_vctMultiCallList.size(); i++ )
		{
			TAddrItem tItem = m_vctMultiCallList[i];
			if( tAddrItem.IsSameName( tItem ) )
			{
				return true;
			}
		}		
		tAddrItem.strImg.Empty();
		//m_vctMultiCallList.push_back( tAddrItem );

		AddGroupToMultiList( tAddrItem );

//         if ( tAddrItem.emItemType == emGroupItem )
//         {
//             m_vctSelGroupList.push_back( tAddrItem );
//         }

        UpdateMultiCallList();

		UpdateShowList();
		
		//列表显示到最后添加的
		if ( CTransparentAddrList* pList = dynamic_cast<CTransparentAddrList*>( UIManagePtr->GetWindowPtr( m_strListMultiCall, m_pWndTree ) ) )
		{
			pList->SetBottomOffset();
		}
	}
	return true;
}

bool CAddrBookLogic::OnDragItemOut( const IArgs& args )
{
	Args_WindowMsg WinMsg = *dynamic_cast<const Args_WindowMsg*>(&args);
	WindowMsg msg = WinMsg.m_Msg;
	
	s32 x = LOWORD(msg.lParam);
	s32 y = HIWORD(msg.lParam);
	CPoint point(x, y);

	if ( Data_AddrItemInfo *pItemInfo = dynamic_cast<Data_AddrItemInfo*>( (IData*)msg.wParam ) )
	{	
        TAddrItem tAddrItem = pItemInfo->m_tAddrItem;
		
		Window* pWnd = UIManagePtr->GetWindowPtr( m_strListMultiCall, m_pWndTree );
		if ( pWnd->GetSafeHwnd() == msg.hwnd )//左边拖拽不删除，右边拖出才删除 dyy
		{
 			CRect rect;
 			pWnd->GetWindowRect(&rect);

			if ( !rect.PtInRect( point ) )
			{ 		
				vector<TAddrItem>::iterator iter = m_vctMultiCallList.begin();
				while( iter != m_vctMultiCallList.end() )
				{					  
					if ( tAddrItem.IsSameName( *iter ) )
					{
						m_vctMultiCallList.erase(iter);  
						break;
					}		
					iter++;
				}

                if ( tAddrItem.emItemType == emGroupItem )
                {
                    vector<TAddrItem>::iterator iter = m_vctSelGroupList.begin();
                    while( iter != m_vctSelGroupList.end() )
                    {					  
                        if ( tAddrItem.IsSameName( *iter ) )
                        {
                            m_vctSelGroupList.erase(iter);
                            break;
                        }		
                        iter++;
                    }
                }
			}
        }
        else if ( !m_bMultiCall )
        {
            CRect rect;
            pWnd->GetWindowRect(&rect);
            if ( rect.PtInRect(point) )
            {
                SetAddrbookPosByVersion("SchmMultiCall");     
  
                for ( int i = 0; i < m_vctMultiCallList.size(); i++ )
                {
                    TAddrItem tItem = m_vctMultiCallList[i];
                    if( tAddrItem.IsSameName( tItem ) )
                    {
                       return true;
                    }
                }		
                tAddrItem.strImg.Empty();
                //m_vctMultiCallList.push_back( tAddrItem );
				
				AddGroupToMultiList( tAddrItem );

//                 if ( tAddrItem.emItemType == emGroupItem )
//                 {
//                     m_vctSelGroupList.push_back( tAddrItem );
//                 }
 
                //列表显示到最后添加的
                if ( CTransparentAddrList* pList = dynamic_cast<CTransparentAddrList*>( UIManagePtr->GetWindowPtr( m_strListMultiCall, m_pWndTree ) ) )
                {
                    pList->SetBottomOffset();
                }

                m_bMultiCall = TRUE;
            }
        }
        UpdateMultiCallList();

        UpdateShowList();
	}
	return true;
}



bool CAddrBookLogic::OnSelAddrItem( const IArgs& args )
{
	if ( Args_ClickItemInfo *pclickInfo = dynamic_cast<Args_ClickItemInfo*>( const_cast<IArgs*>(&args)) )
	{ 
		IBaseItem* pBaseItem = pclickInfo->m_pClickList->GetParentItem()->GetItemData();
		if ( pBaseItem != NULL )
		{
			Data_AddrItemInfo ItemInfo = *dynamic_cast<const Data_AddrItemInfo*>( pBaseItem->GetUserData() );
			TAddrItem tAddrItem = ItemInfo.m_tAddrItem;
			tAddrItem.strImg.Empty();

			m_vctMultiCallList.push_back( tAddrItem );

            if ( tAddrItem.emItemType == emGroupItem )
            {
                m_vctSelGroupList.push_back( tAddrItem );
            }
			
            UpdateMultiCallList();
            
            //UpdateShowList();
            //不再刷新整个列表，提高效率 -xcr
            SetAddrListSelValue( ItemInfo, m_strListLocalAddr, m_pWndTree );

			//列表显示到最后添加的
			if ( CTransparentAddrList* pList = dynamic_cast<CTransparentAddrList*>( UIManagePtr->GetWindowPtr( m_strListMultiCall, m_pWndTree ) ) )
			{
				pList->SetBottomOffset();
			}

            if ( !m_bMultiCall )
            {
                m_bMultiCall = TRUE;
                SetAddrbookPosByVersion("SchmMultiCall");
                //UIManagePtr->LoadScheme( "SchmMultiCall", m_pWndTree );
			}
		}
	}
	return true;
}

bool CAddrBookLogic::OnUnSelAddrItem( const IArgs& args )
{
	if ( Args_ClickItemInfo *pclickInfo = dynamic_cast<Args_ClickItemInfo*>( const_cast<IArgs*>(&args)) )
	{ 
		IBaseItem* pBaseItem = pclickInfo->m_pClickList->GetParentItem()->GetItemData();
		if ( pBaseItem != NULL )
		{
			Data_AddrItemInfo ItemInfo = *dynamic_cast<const Data_AddrItemInfo*>( pBaseItem->GetUserData() );
			TAddrItem tAddrItem = ItemInfo.m_tAddrItem;
			tAddrItem.strImg.Empty();
			
			vector<TAddrItem>::iterator iter = m_vctMultiCallList.begin();
			while( iter != m_vctMultiCallList.end() )
			{					  
				//if ( *iter == tAddrItem )
				if ( tAddrItem.IsSameName( *iter ) )
				{
					m_vctMultiCallList.erase(iter);
					break;
				}		
				iter++;
			}

            if ( tAddrItem.emItemType == emGroupItem )
            {
                vector<TAddrItem>::iterator iter = m_vctSelGroupList.begin();
                while( iter != m_vctSelGroupList.end() )
                {					  
                    if ( tAddrItem.IsSameName( *iter ) )
                    {
                        m_vctSelGroupList.erase(iter);
                        break;
                    }		
                    iter++;
			    }
            }
			
            UpdateMultiCallList();
            
            //UpdateShowList();
            SetAddrListSelValue( ItemInfo, m_strListLocalAddr, m_pWndTree );
		}
	}
	return true;
}


bool CAddrBookLogic::OnMultiCall( const IArgs& args )
{
	bool bOn = false;
    UIManagePtr->GetSwitchState( m_strBtnMultiCall, bOn , m_pWndTree );
    if ( bOn == true )
    { 
		m_bMultiCall = TRUE;
        SetAddrbookPosByVersion("SchmMultiCall");
		//UIManagePtr->LoadScheme( "SchmMultiCall", m_pWndTree );
	}
	else
	{
		m_bMultiCall = FALSE;
        SetAddrbookPosByVersion("SchmNormal");
		//UIManagePtr->LoadScheme( "SchmNormal", m_pWndTree );
	}
	return true;
}

bool CAddrBookLogic::OnCancelMulti( const IArgs& args )
{
    if ( m_bMultiCall )
    {
	    m_bMultiCall = FALSE;
	   // UIManagePtr->LoadScheme( "SchmNormal", m_pWndTree );
    }
       
    SetAddrbookPosByVersion("SchmNormal");

    m_vctMultiCallList.clear();
    m_vctSelGroupList.clear();
    UIManagePtr->LoadScheme( "SchmNoAllSel", m_pWndTree );
    
    UpdateMultiCallList();
         
    UpdateShowList();

	return true;
}


bool CAddrBookLogic::OnBtnBack( const IArgs& args )
{
	UIManagePtr->SetCaption( m_strEdtSearch, "", m_pWndTree );

    //清空多会场列表中的数据  ---2013.10.18  jyy进入组或者返回上一层不在清除多会场中的条目
// 	if ( !m_vctMultiCallList.empty()  )   
// 	{
// 		m_vctMultiCallList.clear();
//         m_vctSelGroupList.clear();
// 		UpdateMultiCallList();
// 	}

	if ( m_SelGroup.dwInGroupIdx == INVALID_INDEX )
	{
		m_SelGroup.SetNull();
		UpdateShowList();
	}
	else
	{
		ComInterface->GetAddrGroupInfo( m_SelGroup.dwInGroupIdx, m_SelGroup );

		UpdateGroupMemberList( m_SelGroup.dwGroupIdx );
	}

	//设置列表之前的偏移量
	int nSize = m_vctListOffset.size();
	if ( nSize > 0 )
	{
		s32 nOffset = m_vctListOffset.at( nSize - 1 );
		Value_TransparentListOffset val;
		val.nOffset = nOffset;
		UIManagePtr->SetPropertyValue( val, m_strListLocalAddr, m_pWndTree );
		m_vctListOffset.pop_back();
	}

//     m_emAddrShowState = emShowAllAddr;//点击返回，显示所有列表 dyy
// 
//     UpdateShowList();//更新 dyy

	UpdateAddrTitle();
    
    UpdateShowOption();
	
	return true;
}


bool CAddrBookLogic::OnClickAddrItem( const IArgs& args )
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
				UIManagePtr->SetCaption( m_strEdtSearch, "", m_pWndTree );

				//记录下当前列表偏移量
				Value_TransparentListOffset valueOffset;
				UIManagePtr->GetPropertyValue( valueOffset, m_strListLocalAddr, m_pWndTree );
				m_vctListOffset.push_back( valueOffset.nOffset );

				//进入组
				m_SelGroup = m_SelItem.tGroupInfo;
				UpdateGroupMemberList( m_SelGroup.dwGroupIdx );

				//进入组之后将偏移量设为0
				valueOffset.nOffset = 0;
				UIManagePtr->SetPropertyValue( valueOffset, m_strListLocalAddr, m_pWndTree );

				UpdateAddrTitle();
                */
                //弹出添加框
                Value_WindowOwer owerVal;
                owerVal.pWnd = UIManagePtr->GetWindowPtr( g_stcStrAddrbookDlg );//pClickInfo->m_pSrcWnd; dyy 2013.8.8
                UIManagePtr->SetPropertyValue( owerVal, "AddrAddDlg" );
                
                CRect rect = pClickInfo->m_rcFrame;	
                Value_WindowPos posVal;
                posVal.nX = rect.right;
                posVal.nY = rect.top;
                UIManagePtr->SetPropertyValue( posVal, "AddrAddDlg" );
				UIManagePtr->ShowWindow( "AddrAddDlg", true );
			}
			else
			{
				if( !m_bMultiCall )
				{
					//弹出呼叫框
					CMsgDispatch::SendMessage( UI_ADDR_ITEM_CALL_CLICK, (WPARAM)(&args), 0 );
				}
			}				
		}
    } 
	return true;
}


bool CAddrBookLogic::OnEnterAddrGroup( const IArgs& args )
{
    if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast<const Args_ClickItemInfo*>(&args) )
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetParentItem()->GetItemData();
        if ( const Data_AddrItemInfo *pItemInfo = dynamic_cast<const Data_AddrItemInfo*>( pBaseItem->GetUserData() ) )
        {
            TAddrItem tSelItem = pItemInfo->m_tAddrItem;
            
            if ( tSelItem.emItemType == emGroupItem )
			{
                UIManagePtr->SetCaption( m_strEdtSearch, "", m_pWndTree );

                //清空多会场列表中的数据   jyy---2013.10.18  进入组或者返回上一层不在清除多会场中的条目
// 				if ( !m_vctMultiCallList.empty() )    
// 				{
// 					m_vctMultiCallList.clear();
//                     m_vctSelGroupList.clear();
// 					UpdateMultiCallList();
// 				}

                if ( m_emAddrShowState = emShowGroup )
                {
                    m_emAddrShowState = emShowAllAddr;// 进入组后，显示组内全部 dyy
                    UpdateShowOption();
                }   

	            //记录下当前列表偏移量
	            Value_TransparentListOffset valueOffset;
                UIManagePtr->GetPropertyValue( valueOffset, m_strListLocalAddr, m_pWndTree );
                m_vctListOffset.push_back( valueOffset.nOffset );
    				
                //进入组
                m_SelGroup = tSelItem.tGroupInfo;
                UpdateGroupMemberList( m_SelGroup.dwGroupIdx );
    
                //进入组之后将偏移量设为0
                valueOffset.nOffset = 0;
                UIManagePtr->SetPropertyValue( valueOffset, m_strListLocalAddr, m_pWndTree );

	            UpdateAddrTitle();
            }
        }
    }

    return true;
}

bool CAddrBookLogic::OnClickAddrGroup( const IArgs& args )
{
	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast<const Args_ClickItemInfo*>(&args) )
    {
		IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetItemData();
		if ( const Data_AddrItemInfo *pItemInfo = dynamic_cast<const Data_AddrItemInfo*>( pBaseItem->GetUserData() ) )
		{
			m_SelItem = pItemInfo->m_tAddrItem;
			if( !m_bMultiCall )
			{
				CMsgDispatch::SendMessage( UI_ADDR_ITEM_CALL_CLICK, (WPARAM)(&args), (LPARAM)0 );
			}
			else
			{
				/*
				//多会场呼叫弹出添加框
				Value_WindowOwer owerVal;
				owerVal.pWnd = pClickInfo->m_pSrcWnd;
				UIManagePtr->SetPropertyValue( owerVal, "AddrAddDlg");

				CRect rect = pClickInfo->m_rcFrame;	
				Value_WindowPos posVal;
				posVal.nX = rect.right;
				posVal.nY = rect.top;
				UIManagePtr->SetPropertyValue( posVal, "AddrAddDlg" );
				UIManagePtr->ShowWindow( "AddrAddDlg", true );
				*/
			}
		}
    } 
	return true;
}

bool CAddrBookLogic::OnAddToMultiList( const IArgs& args )
{
/*	for ( int i = 0; i < m_vctMultiCallList.size(); i++ )
	{
		if ( m_SelItem.emItemType == emEntryItem )
		{
			TAddrItem tItem = m_vctMultiCallList[i];
			if( m_SelItem == tItem )
			{
				UIManagePtr->ShowWindow( "AddrAddDlg", false );
				return true;
			}
		} 
// 		else
// 		{
// 			vector<TAddrItem>::iterator iter = m_vctSelGroupList.begin();
// 			while( iter != m_vctSelGroupList.end() )
// 			{
// 				if ( m_SelItem.IsSameName(*iter) )
// 				{
// 					UIManagePtr->ShowWindow( "AddrAddDlg", false );
// 					break;
// 				}
// 				iter++;
// 			}
// 		}
	}*/
	
    m_SelItem.strImg.Empty();
	//m_vctMultiCallList.push_back( m_SelItem );
 
	AddGroupToMultiList( m_SelItem );
		
//     if ( m_SelItem.emItemType == emGroupItem )
//     {
//         m_vctSelGroupList.push_back( m_SelItem );
//     }
	
    UpdateMultiCallList();

	UpdateShowList();

    UIManagePtr->ShowWindow( "AddrAddDlg", false );

    if ( !m_bMultiCall )
    {
        m_bMultiCall = TRUE;
        SetAddrbookPosByVersion("SchmMultiCall");
        //UIManagePtr->LoadScheme( "SchmMultiCall", m_pWndTree );
	}
    
	//列表显示到最后添加的
// 	if ( CTransparentAddrList* pList = dynamic_cast<CTransparentAddrList*>( UIManagePtr->GetWindowPtr( m_strListMultiCall, m_pWndTree ) ) )
// 	{
// 		pList->SetBottomOffset();
// 	}

	return true;
}

bool CAddrBookLogic::OnDelFromMultiList( const IArgs& args )
{
	if ( Args_ClickItemInfo *pclickInfo = dynamic_cast<Args_ClickItemInfo*>( const_cast<IArgs*>(&args)) )
	{ 
		IBaseItem* pBaseItem = pclickInfo->m_pClickList->GetParentItem()->GetItemData();
		if ( pBaseItem != NULL )
		{
			Data_AddrItemInfo ItemInfo = *dynamic_cast<const Data_AddrItemInfo*>( pBaseItem->GetUserData() );
			TAddrItem tAddrItem = ItemInfo.m_tAddrItem;

			vector<TAddrItem>::iterator iter = m_vctMultiCallList.begin();
			while( iter != m_vctMultiCallList.end() )
			{					  
				if ( tAddrItem.IsSameName( *iter ) )
				{
					m_vctMultiCallList.erase(iter);
					break;
				}		
				iter++;
			}

            if ( tAddrItem.emItemType == emGroupItem )
            {
                vector<TAddrItem>::iterator iter = m_vctSelGroupList.begin();
                while( iter != m_vctSelGroupList.end() )
                {					  
                    if ( tAddrItem.IsSameName( *iter ) )
                    {
                        m_vctSelGroupList.erase(iter);
                        break;
                    }		
                    iter++;
                }
            }
			
            UpdateMultiCallList();
            
            UpdateShowList();
		}
	}
	return true;
}

//点击多会场呼叫
bool CAddrBookLogic::OnCallMultiCn( const IArgs& args )
{
	if ( m_vctMultiCallList.size() == 0 )
	{
		return false;
	}

    CString strErr;
    TTPCallSerInfo tCallSerInfo;
    ComInterface->GetCallServerInfo(tCallSerInfo);
    if ( tCallSerInfo.dwCallServiceIP == NULL ) //dyy 未注册呼叫服务器提示 2013年8月2日
    {
        strErr.Format( "呼叫失败：未配置呼叫服务器" );
        ShowPopMsg( strErr );
        return false;
    }

	TConfCallEpAddrList tConfAddrList;
	TEpAddrList tAddrList;
    vector<TCnAddr> tCnAddrList;

	TTPCnsInfo tCnsInfo;
	ComInterface->GetLocalCnsInfo( tCnsInfo );

	TCMSConf tConf;
	BOOL32 bInconf = BusinessManagePtr->IsInConf( &tConf );
	if ( bInconf  )
	{
		tConfAddrList.m_wConfID = tConf.m_wConfID;
		if ( tConf.m_emConfType == emCallType_P2P )
		{
			tAddrList.Add( tp_Alias_h323, tCnsInfo.m_achRoomName );

            TCnAddr tCnAddr;
            tCnAddr.emType = emTpAlias;
            strncpy( tCnAddr.achAlias, tCnsInfo.m_achRoomName, TP_MAX_H323ALIAS_LEN+1 );
            strncpy( tCnAddr.achE164, tCnsInfo.m_achE164, TP_MAX_H323ALIAS_LEN+1 );
            tCnAddrList.push_back( tCnAddr );
		}
	}
	else
	{	
		tAddrList.Add( tp_Alias_h323, tCnsInfo.m_achRoomName );

        TCnAddr tCnAddr;
        tCnAddr.emType = emTpAlias;
        strncpy( tCnAddr.achAlias, tCnsInfo.m_achRoomName, TP_MAX_H323ALIAS_LEN+1 );
        strncpy( tCnAddr.achE164, tCnsInfo.m_achE164, TP_MAX_H323ALIAS_LEN+1 );
        tCnAddrList.push_back( tCnAddr );
	}
	
	for ( int nIndex = 0; nIndex < m_vctMultiCallList.size(); nIndex++ )
	{
		TAddrItem tItem = m_vctMultiCallList.at(nIndex);

        TCnAddr tCnAddr;
		if( tItem.emItemType == emEntryItem )
		{						
			EmConfAddEpRet emRet = TP_ConfAddEpRet_Unknow;		
			if ( strlen( tItem.tAddrInfo.achE164 ) > 0 )
			{
				if( strcmp( tItem.tAddrInfo.achE164, tCnsInfo.m_achE164 ) == 0 )
				{
					//多会场呼叫列表中本地会场可以跟自身开会，取消弹窗提示 JYY
					//strErr.Format( "不能呼叫本地会场: %s", tItem.tAddrInfo.achE164 );
					//ShowPopMsg( strErr );
					continue;
				}

				emRet = tAddrList.Add( tp_Alias_e164, tItem.tAddrInfo.achE164 );

                tCnAddr.emType = emTpE164Num;
                strncpy( tCnAddr.achAlias, tItem.tAddrInfo.achEntryName, TP_MAX_H323ALIAS_LEN+1 );
                strncpy( tCnAddr.achE164, tItem.tAddrInfo.achE164, TP_MAX_H323ALIAS_LEN+1 );
                tCnAddrList.push_back( tCnAddr );
			}
			else
			{
				if ( strcmp( tItem.tAddrInfo.achEntryName, tCnsInfo.m_achRoomName ) == 0  ) 
				{
					//多会场呼叫列表中本地会场可以跟自身开会，取消弹窗提示 JYY
					//strErr.Format( "不能呼叫本地会场: %s", tItem.tAddrInfo.achEntryName );
					//ShowPopMsg( strErr );
					continue;
				}
				
				if ( bInconf && tConf.IsCnsInConf( tItem.tAddrInfo.achEntryName ) )
				{				
					strErr.Format( "会场 %s 已在本会议中", tItem.tAddrInfo.achEntryName );
					ShowPopMsg( strErr );
					continue;
				}
				
				emRet = tAddrList.Add( tp_Alias_h323, tItem.tAddrInfo.achEntryName );
				
                tCnAddr.emType = emTpAlias;
                strncpy( tCnAddr.achAlias, tItem.tAddrInfo.achEntryName, TP_MAX_H323ALIAS_LEN+1 );
                strncpy( tCnAddr.achE164, tItem.tAddrInfo.achE164, TP_MAX_H323ALIAS_LEN+1 );
                tCnAddrList.push_back( tCnAddr );
			}
			if ( emRet != TP_ConfAddEpRet_Success )
			{
				if ( emRet == TP_ConfAddEpRet_MaxNum )
				{
					strErr.Format( "会场达到最大呼叫数量: %d个", TP_CONF_MAX_EPNUM );
					ShowPopMsg( strErr );
					break;
				}
				continue;
			}
            if ( tCnAddrList.size() == TP_CONF_MAX_EPNUM )
            {
                strErr.Format( "会场达到最大呼叫数量: %d个", TP_CONF_MAX_EPNUM );
                ShowPopMsg( strErr );
			    break;
            }
		}
		/* 现在多会场呼叫中不会有组条目 -2014.6.3 xcr
        else
		{
			TGroupInfo tGroupInfo = tItem.tGroupInfo;
			vector<TAddrInfo> vctAddrInfo;
			ComInterface->GetGroupAddrInfo( tGroupInfo, vctAddrInfo );

			for( int i = 0; i < vctAddrInfo.size(); i++ )
			{				
				EmConfAddEpRet emRet = TP_ConfAddEpRet_Unknow;	

				if ( strlen( vctAddrInfo[i].achEntryName ) > 0  )
				{
					if ( strcmp( vctAddrInfo[i].achEntryName, tCnsInfo.m_achRoomName ) == 0  ) 
					{
						strErr.Format( "不能呼叫本地会场: %s", vctAddrInfo[i].achEntryName );
						ShowPopMsg( strErr );
						continue;
					}

					if ( bInconf && tConf.IsCnsInConf( vctAddrInfo[i].achEntryName ) )
					{
						strErr.Format( "会场 %s 已在本会议中", vctAddrInfo[i].achEntryName );
						ShowPopMsg( strErr );
						continue;
					}

					emRet = tAddrList.Add( tp_Alias_h323, vctAddrInfo[i].achEntryName );
				}
				else
				{
					if( strcmp( vctAddrInfo[i].achE164, tCnsInfo.m_achE164 ) == 0 )
					{
						strErr.Format( "不能呼叫本地会场: %s", vctAddrInfo[i].achE164 );
						ShowPopMsg( strErr );
						continue;		
					}

					emRet = tAddrList.Add( tp_Alias_e164, vctAddrInfo[i].achE164 );
				}
				if ( emRet != TP_ConfAddEpRet_Success )
				{
					if ( emRet == TP_ConfAddEpRet_MaxNum )
					{
						strErr.Format( "会场达到最大呼叫数量: %d个", TP_CONF_MAX_EPNUM );
						ShowPopMsg( strErr );
						break;
					}
					continue;
				}
			}
		}*/
	}

	if ( bInconf )
	{
		if ( tConf.m_emConfType == emCallType_P2P )
		{
			//点对点会议变多点会议,添加点对点会议对端会场
			TTPCnsConfStatus status = ComInterface->GetLocalCnsConfState();
			if ( strlen( status.achConfName ) > 0  )
			{
				//tAddrList.Add( tp_Alias_h323, status.achConfName );

                TCnAddr tCnAddr;
                tCnAddr.emType = emTpAlias;
                strncpy( tCnAddr.achAlias, status.achConfName, TP_MAX_H323ALIAS_LEN+1 );
                tCnAddrList.push_back( tCnAddr );
			}
			else
			{
				//tEqAddrLst.Add( tp_Alias_e164, m_tCallAddr.achE164 );
			}
			ComInterface->StartInstantConf( tCnAddrList );		
			CMsgDispatch::SendMessage( UI_UMS_SHOW_CALLING_DLG, 0, 0 );
		}
		else
		{
			tConfAddrList.m_tEpAdrLst = tAddrList;
			ComInterface->InviteCns( tConfAddrList ); 
		}
	}
	else
	{	
		ComInterface->StartInstantConf( tCnAddrList );
 
		CMsgDispatch::SendMessage( UI_UMS_SHOW_CALLING_DLG, 0, 0 ); 
	}

	m_vctMultiCallList.clear();
    m_vctSelGroupList.clear();
    UpdateMultiCallList();
    
    UpdateShowList();
	
	return true;
}


bool CAddrBookLogic::OnSearchEditChange( const IArgs& args )
{
	String strCaption;
	UIManagePtr->GetCaption( m_strEdtSearch, strCaption, m_pWndTree );
	if ( strCaption.empty() )
	{
        m_bSearchEdit = FALSE;
		UpdateShowList();
		return false;
	}

    m_bSearchEdit = TRUE;
	CString strSearchName;
	strSearchName.Format( "%s", strCaption.c_str() );

	Value_TransparentListOffset val;
	val.nOffset = 0;    

	m_vctSearchList.clear();
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
			//名称为空用E164号匹配
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
            //名字没有匹配到
            strItemName = tAddrItem.tAddrInfo.achE164;
            bFind = UIDATAMGR->HZPYMatchList( strSearchName, strItemName );
            if ( bFind )
            {		
                m_vctSearchList.push_back( tAddrItem );
		    }
        }
	}

	UpdateShowList();

	return true;
}


LRESULT CAddrBookLogic::UpdateLocalAddrBook( WPARAM wParam, LPARAM lParam )
{
	if( m_pWndTree == NULL )
	{
		return 0;
	}
	
	UpdateLocalAddrList();

	if ( !m_SelGroup.IsNull() )
	{
		UpdateGroupMemberList( m_SelGroup.dwGroupIdx );
	}

	if ( m_bSearchEdit )
	{
		IArgs args( "NULL" );
		OnSearchEditChange( args );
	}
	
	return 0;
}


void CAddrBookLogic::UpdateLocalAddrList()
{
	m_vctLocalList.clear();	
	m_vctLocalList = *ComInterface->GetLocalAddrList();

	m_vctEntryList.clear();
	m_vctEntryList = *ComInterface->GetAddrEntryList();

	UpdateShowList();
}


void CAddrBookLogic::UpdateGlobalAddrList()
{
	m_vctGlobalList.clear();
	m_vctGlobalList = *ComInterface->GetGlobalAddrList();

    //此时不刷新，在UpdateAddrbook时一起刷新 -xcr
	//UpdateShowList();
}


LRESULT CAddrBookLogic::UpdateGlobalAddrBook( WPARAM wParam, LPARAM lParam )
{
	if( m_pWndTree == NULL )
	{
		return NO_ERROR;
	}

	UIManagePtr->EnableWindow( m_strBtnRefresh, true, m_pWndTree ); 

    CMsgDispatch::SendMessage( UI_CNC_ENDWAITING_REFRESH, 0, 0 );
	
	UpdateGlobalAddrList();

	if ( m_bSearchEdit )
	{
		IArgs args( "NULL" );
		OnSearchEditChange( args );
	}
		
	return NO_ERROR;
}


void CAddrBookLogic::UpdateGroupMemberList( u32 dwGroupIndex )
{

	ComInterface->GetAddrGroupMember( dwGroupIndex, m_vctGroupMemberList );

	UpdateShowList();
}


void CAddrBookLogic::UpdateShowList()
{
// 	if ( m_bMultiCall && m_vctMultiCallList.empty() )
// 	{
// 		m_bMultiCall = FALSE;
//      SetAddrbookPosByVersion("SchmNormal");
// 		//UIManagePtr->LoadScheme( "SchmNormal", m_pWndTree );
// 	}
	
    BOOL bInLocalList = FALSE; //当前是否在地址簿第一级无筛选目录

	String strCaption;
	UIManagePtr->GetCaption( m_strEdtSearch, strCaption, m_pWndTree );
	if ( strCaption.empty() )
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
                bInLocalList = TRUE;
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

    //获得条件筛选后的条目
    GetOptnShowList( m_vctShowList );

	//if ( m_bInConf )
	{
		for ( int i = 0; i < m_vctShowList.size(); i++ )
		{
            TAddrItem tShowItem = m_vctShowList.at(i);
            if ( tShowItem.emItemType != emEntryItem )
            {
                m_vctShowList.at(i).strImg = "AddrEnterGroupItem";
                continue;
            }
			BOOL bFind = FALSE;
			for ( int j = 0; j < m_vctMultiCallList.size(); j++ )
			{
				TAddrItem tItem = m_vctMultiCallList.at(j);
				//if ( m_vctShowList.at(i) == tItem )
				if ( tItem.emItemType != emEntryItem )
				{
					if ( tShowItem.tAddrInfo.dwInGroupIdx == tItem.tGroupInfo.dwGroupIdx )
					{
						m_vctShowList.at(i).strImg = "AddrUnSelItem";
						bFind = TRUE;
						break;
					}
				}
				//只比较名字
				if ( tItem.IsSameName( tShowItem ) )
				{
					m_vctShowList.at(i).strImg = "AddrUnSelItem";
					bFind = TRUE;
					break;
				}
			}
			if ( !bFind )
			{
				m_vctShowList.at(i).strImg = "AddrSelItem";
			}
		}
	}
	
	Value_TouchListAddr touchListAddr( &m_vctShowList, NULL, "CAddrBookLogic::OnClickAddrItem" );

	if ( m_bGlobalAddr )
	{
		UIManagePtr->SetPropertyValue( touchListAddr, m_strListGlobalAddr, m_pWndTree );
	}
	else
	{
		UIManagePtr->SetPropertyValue( touchListAddr, m_strListLocalAddr, m_pWndTree );
	}

    //更新全选button
    UpdateAllSelButton( bInLocalList );
		
}



void CAddrBookLogic::UpdateAllSelButton( BOOL bInLocalList )
{
    //全选只能选择会场条目，先筛选出会场条目
    vector<TAddrItem> vctShowEntryList;
    
    //简单比较，即通过数量判断是否全选
    BOOL bEasyCompare = FALSE;
    if ( m_emAddrShowState == emShowAllAddr )
    {
        if ( bInLocalList )
        {
            vctShowEntryList = m_vctEntryList;
            bEasyCompare = TRUE;
        }      
    }
    else if ( m_emAddrShowState == emShowGroup )
    {
        vctShowEntryList.clear();
        bEasyCompare = TRUE;
    }  
    
    if ( bEasyCompare )
    {
        if ( vctShowEntryList.empty() )
        {
            UIManagePtr->EnableWindow( m_strBtnAllSel, false, m_pWndTree );
        }
        else
        {
            UIManagePtr->EnableWindow( m_strBtnAllSel, true, m_pWndTree );
            
            //多会场呼叫列表中会场的数目与本地列表会场数目一致,全选按钮变为取消全选
            int nSelEntrySize = m_vctMultiCallList.size() - m_vctSelGroupList.size();
            if ( nSelEntrySize != vctShowEntryList.size() )		
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
                if ( tItem.strImg == "AddrSelItem" )
                {
                    bAllSel = FALSE;
                    break;
                }
            }
        }
        
        if ( nEntryNum == 0 )
        {
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



void CAddrBookLogic::UpdateAddrTitle()
{
	if ( m_bGlobalAddr )
	{
		UIManagePtr->SetCaption( m_strStcTitle, "全局地址簿", m_pWndTree );
		
		UIManagePtr->LoadScheme( "SchmNotInGroup", m_pWndTree, m_strStcTitle );
			
		UIManagePtr->ShowWindow( m_strBtnBack, false, m_pWndTree );
	}
	else
	{
		if ( m_SelGroup.IsNull() )
		{
			UIManagePtr->SetCaption( m_strStcTitle, "地址簿", m_pWndTree );
			
			UIManagePtr->LoadScheme( "SchmNotInGroup", m_pWndTree, m_strStcTitle );
			
			UIManagePtr->ShowWindow( m_strBtnBack, false, m_pWndTree );
		}
		else
		{
			CString strTitle;
			strTitle =  ComInterface->GetAddrGroupPath( m_SelGroup.dwGroupIdx );
			strTitle = "地址簿" + strTitle;

			UIManagePtr->SetCaption( m_strStcTitle, (LPCTSTR)strTitle, m_pWndTree );
			
			UIManagePtr->LoadScheme( "SchmInGroup", m_pWndTree, m_strStcTitle );
			
			UIManagePtr->ShowWindow( m_strBtnBack, true, m_pWndTree );
		}
	}

}


void CAddrBookLogic::UpdateMultiCallList()
{
    ARRAY<String> vctItem;
    vctItem.push_back( "AddrDelMultiItem" );
    Value_TouchListAddr touchListAddr( &m_vctMultiCallList, &vctItem, "", FALSE );
    UIManagePtr->SetPropertyValue( touchListAddr , m_strListMultiCall, m_pWndTree );
}


LRESULT CAddrBookLogic::OnConfStateNotify( WPARAM wParam, LPARAM lParam )
{
	if ( NULL == m_pWndTree )
    {  
        return NO_ERROR;
    }
		
	BOOL bInConf = BusinessManagePtr->IsInConf(); 
	if ( bInConf != m_bInConf )
	{
		m_bInConf = bInConf;

		//还原界面
		m_bGlobalAddr = FALSE;
		m_bMultiCall = FALSE;
        m_SelGroup.SetNull();
		if ( !m_vctMultiCallList.empty() )
		{
			m_vctMultiCallList.clear();
			Value_TouchListAddr touchListAddr( &m_vctMultiCallList );
			UIManagePtr->SetPropertyValue( touchListAddr, m_strListMultiCall, m_pWndTree );
		}		

		UIManagePtr->LoadScheme( "", m_pWndTree, "", false );

		if ( bInConf )
		{			
			UIManagePtr->LoadScheme( "SchmInConf", m_pWndTree );
		}
		else
		{
			UIManagePtr->LoadScheme( "SchmNotInConf", m_pWndTree );
		}
		UpdateShowList();
	}	

	return NO_ERROR;
}



void CAddrBookLogic::Clear()
{
	m_bGlobalAddr = FALSE;
	m_bInConf = FALSE;
	m_bMultiCall = FALSE;
    m_bSearchEdit = FALSE;
	m_vctLocalList.clear();
	m_vctEntryList.clear();
	m_vctGlobalList.clear();
	m_vctGroupMemberList.clear();
	m_vctSearchList.clear();
    m_vctShowList.clear();  
    m_SelItem.SetNull();
	m_SelGroup.SetNull();
	m_emAddrShowState = emShowAllAddr;
	UpdateShowOption();
	UIManagePtr->LoadScheme( "", m_pWndTree, "", false );

    if( UIManagePtr->IsVisible( g_strAddrShowOptnDlg ) ) //dyy 2013年9月23日 
    {
        UIManagePtr->ShowWindow( g_strAddrShowOptnDlg, false );
    }

	if ( !m_vctMultiCallList.empty() )
	{
		m_vctMultiCallList.clear();
        m_vctSelGroupList.clear();
		Value_TouchListAddr touchListAddr( &m_vctMultiCallList );
		UIManagePtr->SetPropertyValue( touchListAddr, m_strListMultiCall, m_pWndTree );
	}	
}

bool CAddrBookLogic::OnCloseDlg( const IArgs & arg )
{
    return UIManagePtr->ShowWindow( "AddrBookDlg", false );
}

bool CAddrBookLogic::OnBtnSelectAll( const IArgs & arg )
{

    if ( !m_bSearchEdit && m_SelGroup.IsNull() && (m_emAddrShowState == emShowAllAddr) )
    {
        m_vctMultiCallList = m_vctEntryList;    
    }
    else
    {
        //将没有选中的项都选中
        for ( int i = 0; i < m_vctShowList.size(); i++ )
        {
            TAddrItem tItem = m_vctShowList.at(i);
            if ( tItem.emItemType == emEntryItem && tItem.strImg == "AddrSelItem" )
            {
                tItem.strImg.Empty();
                m_vctMultiCallList.push_back( tItem );
            }
        }        
    }

    if ( !m_vctSelGroupList.empty() )
    {
        m_vctMultiCallList.insert( m_vctMultiCallList.begin(), m_vctSelGroupList.begin(), m_vctSelGroupList.end() );
    }
    
    if ( !m_bMultiCall )
    {
        m_bMultiCall = TRUE;
        SetAddrbookPosByVersion("SchmMultiCall");
        //UIManagePtr->LoadScheme( "SchmMultiCall", m_pWndTree );
	}

    UpdateMultiCallList();

    //全选时已选列表位置置顶
    Value_TransparentListOffset valueOffset;
    valueOffset.nOffset = 0;
	UIManagePtr->SetPropertyValue( valueOffset, m_strListLocalAddr, m_pWndTree );

    UpdateShowList(); 

    return true;
}

bool CAddrBookLogic::OnBtnUnSelectAll( const IArgs & arg )
{

    if ( !m_bSearchEdit && m_emAddrShowState == emShowAllAddr )
    {
        m_vctMultiCallList.clear();

        if ( !m_vctSelGroupList.empty() )
        {
            m_vctMultiCallList = m_vctSelGroupList;
        } 
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
            vector<TAddrItem>::iterator itfind = find( m_vctMultiCallList.begin(), m_vctMultiCallList.end(), tShowItem );
            
            if ( itfind != m_vctMultiCallList.end() )
            {
                m_vctMultiCallList.erase( itfind );
            }
        }     
    }


    UpdateMultiCallList();
   
    //Value_TransparentListOffset valueOffset;
    //valueOffset.nOffset = 0;
    //UIManagePtr->SetPropertyValue( valueOffset, m_strListLocalAddr, m_pWndTree );
    
    UpdateShowList();

    return true;
}

bool CAddrBookLogic::OnBtnRefresh( const IArgs & arg )
{
	UIManagePtr->EnableWindow( m_strBtnRefresh, false, m_pWndTree ); 
	
    u16 re = BusinessManagePtr->UpdateGlobalAddrbook();
    if ( re != NO_ERROR )
    {
        return false;
	}

    Window* pWnd = UIManagePtr->GetWindowPtr( g_stcStrAddrbookDlg );
    
	CMsgDispatch::SendMessage( UI_CNC_BEGINWAITING_REFRESH, (WPARAM)pWnd, /*emGetRegInfoType_CNS*/emWaitRegInfo );

    return true;
}


LRESULT CAddrBookLogic::OnWaitRefreshOverTime( WPARAM wParam, LPARAM lParam )
{
	if( m_pWndTree == NULL )
	{
		return NO_ERROR;
	}

	//2013.1.16 yjj 
	bool bVis = UIFACTORYMGR_PTR->IsVisible( g_stcStrAddrEditDlg );
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


bool CAddrBookLogic::OnBtnAddrShowOptn( const IArgs & arg )
{ 
    bool bOn = false;
    UIManagePtr->GetSwitchState( m_strBtnAddrShowEx, bOn , m_pWndTree );
    if ( bOn )
    {   
        Value_WindowPos valPos;
        UIManagePtr->GetPropertyValue( valPos, m_strBtnAddrShowEx, m_pWndTree );
        
        valPos.nX = valPos.nX + 52;
        valPos.nY = valPos.nY - 7;
        UIManagePtr->SetPropertyValue( valPos, g_strAddrShowOptnDlg );

        Value_WindowOwer owerVal;
        owerVal.pWnd = UIManagePtr->GetWindowPtr( g_stcStrAddrbookDlg );
        UIManagePtr->SetPropertyValue( owerVal, g_strAddrShowOptnDlg );
        UIManagePtr->ShowWindow( g_strAddrShowOptnDlg );
    }
    else
    {
        UIManagePtr->ShowWindow( g_strAddrShowOptnDlg, false );
    }
    return true; 
}


//更新显示选项信息
void CAddrBookLogic::UpdateShowOption()
{ 
    if ( m_pWndTree == NULL )
    {
        return;
    }
    
    ARRAY<String> vcItem; 
    vcItem.push_back( "ImageItemSelected" );   
    
    ARRAY<TMenuItemInfo> menuLst;     
    TMenuItemInfo tMenu;
            
    tMenu.strTxt = _T("显示全部");
    tMenu.strItemFunc = "CAddrBookLogic::OnAddrOptnShowAll";
    tMenu.strImageItem = "TempListItem";  
    tMenu.strTxtItem = "TextItem"; 
    if ( m_emAddrShowState == emShowAllAddr )
    { 
        tMenu.m_pVctSubItem = &vcItem;
    } 
    menuLst.push_back( tMenu );
    
    tMenu.Clear();
    tMenu.strTxt = _T("显示组");
    tMenu.strImageItem = "TempListItem";  
    tMenu.strTxtItem = "TextItem";     
    tMenu.strItemFunc = "CAddrBookLogic::OnAddrOptnShowGroup";
    if ( m_emAddrShowState == emShowGroup )
    {   
        tMenu.m_pVctSubItem = &vcItem;
    }  
    menuLst.push_back( tMenu );
    
    tMenu.Clear();
    tMenu.strTxt = _T("显示在线");
    tMenu.strImageItem = "TempListItem" ;  
    tMenu.strTxtItem = "TextItem";  
    tMenu.strItemFunc = "CAddrBookLogic::OnAddrOptnShowOnline";
    if ( m_emAddrShowState == emShowOnline )
    {   
        tMenu.m_pVctSubItem = &vcItem;
    }     
    menuLst.push_back( tMenu );
    
    tMenu.Clear();
    tMenu.strTxt = _T("显示不在线");
    tMenu.strImageItem = "TempListItem";  
    tMenu.strTxtItem = "TextItem";  
    tMenu.strItemFunc = "CAddrBookLogic::OnAddrOptnShowOffline";
    if ( m_emAddrShowState == emShowOffline )
    {
        tMenu.m_pVctSubItem = &vcItem;
    }   
    menuLst.push_back( tMenu );
      
    Value_TouchListMenu val( &menuLst );  
    UIManagePtr->SetPropertyValue( val, m_strLstAddrShowOptn );

}

bool CAddrBookLogic::OnAddrOptnShowAll( const IArgs & arg )
{
    if ( m_emAddrShowState == emShowAllAddr )
    {
        return true;
    }
    m_emAddrShowState = emShowAllAddr;
    UpdateShowOption();
    UpdateShowList();

    return true;
}

bool CAddrBookLogic::OnAddrOptnShowGroup( const IArgs & arg )
{   
    if ( m_emAddrShowState == emShowGroup )
    {
        return true;
    }
    
    m_emAddrShowState = emShowGroup;
    UpdateShowOption();
    UpdateShowList();

    return true;
}

bool CAddrBookLogic::OnAddrOptnShowOnline( const IArgs & arg )
{
    if ( m_emAddrShowState == emShowOnline )
    {
        return true;
    }
    m_emAddrShowState = emShowOnline;
    UpdateShowOption();
    UpdateShowList();

    return true;
}

bool CAddrBookLogic::OnAddrOptnShowOffline( const IArgs & arg )
{
    if ( m_emAddrShowState == emShowOffline )
    {
        return true;
    }
    m_emAddrShowState = emShowOffline;
    UpdateShowOption();
    UpdateShowList();

    return true;
}

void CAddrBookLogic::GetOptnShowList( vector<TAddrItem>& vctCurrentList )
{
    if ( m_emAddrShowState == emShowAllAddr )
    {
        return;
    }

    vector<TAddrItem> vctList = vctCurrentList;
    vctCurrentList.clear();
    if ( m_emAddrShowState == emShowOnline )
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
    else if ( m_emAddrShowState == emShowOffline )
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
    else if ( m_emAddrShowState == emShowGroup )
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



void CAddrBookLogic::SetAddrbookPosByVersion(String SchemeType)
{
    UIManagePtr->LoadScheme( SchemeType, m_pWndTree );
    //判断其是否为pc版本
//    if ( UIDATAMGR->IsPcVersion() )
    {
        POINT pt;
        Value_WindowSize val;
        UIManagePtr->GetPropertyValue( val, g_stcStrAddrbookDlg );
       
        Value_WindowSize valParent;
        UIManagePtr->GetPropertyValue( valParent, g_stcStrMainFrameDlg );
        
        pt.x = ( valParent.nWidth - val.nWidth ) / 2;
        pt.y = 53; 
        UIFACTORYMGR_PTR->SetWndPos( pt, g_stcStrAddrbookDlg, NULL, g_stcStrMainFrameDlg );
    }
}

void CAddrBookLogic::AddGroupToMultiList( TAddrItem tItem )
{
	if ( tItem.emItemType == emGroupItem )   //----2013.10.21  jyy  添加进多会场呼叫列表的组全部展开
	{
		vector<TAddrItem> vctGroupMemberList;
		ComInterface->GetAddrGroupMember( tItem.tGroupInfo.dwGroupIdx, vctGroupMemberList );
		for ( int i = 0; i < vctGroupMemberList.size(); i++ )
		{
			TAddrItem tItem = vctGroupMemberList[i];
			if( emEntryItem == tItem.emItemType )
			{
				vector<TAddrItem>::iterator iter = m_vctMultiCallList.begin();
				while( iter != m_vctMultiCallList.end() )
				{					  
					if ( tItem.IsSameName( *iter ) )
					{
						m_vctMultiCallList.erase(iter);
						break;
					}		
					iter++;
				}
				m_vctMultiCallList.push_back( tItem );	
			}
			else
			{
				AddGroupToMultiList(tItem);
			}
		}
		m_vctSelGroupList.push_back( tItem );
	}
	else
	{
		m_vctMultiCallList.push_back( tItem );
	}
}

void CAddrBookLogic::SetAddrListSelValue( Data_AddrItemInfo& ItemInfo, String strWndName, const IWndTree* pWndTree )
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
                                if ( tAddrItem.strImg == "AddrUnSelItem" )
                                {                                  
                                    pSubItem2->SetImageFolder( strPath + "addrbook/addrSelImg" );                                 
                                    pSubItem2->SetFunc( "CAddrBookLogic::OnSelAddrItem" );

                                    ItemInfo.m_tAddrItem.strImg = "AddrSelItem";
                                }
                                else
                                {
                                    pSubItem2->SetImageFolder( strPath + "addrbook/addrUnSelImg" );                                 
                                    pSubItem2->SetFunc( "CAddrBookLogic::OnUnSelAddrItem" );

                                    ItemInfo.m_tAddrItem.strImg = "AddrUnSelItem";
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
