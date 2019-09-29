// tvwLogic.cpp: implementation of the CTvwLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cms.h"
#include "tvwLogic.h"
#include "TouchListHelp.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const String CTvwLogic::m_stcStrDlgTvwSet = "DlgTvwSet";
const String CTvwLogic::m_stcStrLstTvw = "LstTvw";
const String CTvwLogic::m_stcStrBtnDelete = "BtnDelete";

const String CTvwLogic::m_stcStrDlgCnsLst = "DlgCnsLst";
const String CTvwLogic::m_stcStrLstCns = "LstCns";

 
CTvwLogic *CTvwLogic::m_pLogic = NULL;
CTvwLogic::CTvwLogic():m_tSelTvwInfo()
{
    const_cast<String&>(m_stcStrLstTvw) = m_stcStrDlgTvwSet + "/" + m_stcStrLstTvw;
	const_cast<String&>(m_stcStrBtnDelete) = m_stcStrDlgTvwSet + "/" + m_stcStrBtnDelete;
	const_cast<String&>(m_stcStrLstCns) = m_stcStrDlgCnsLst + "/" + m_stcStrLstCns;
	
	m_tTvwCtrlArray[0].strBtnTvw = m_stcStrDlgTvwSet + "/" + "BtnTvw1";
	m_tTvwCtrlArray[1].strBtnTvw = m_stcStrDlgTvwSet + "/" + "BtnTvw2";
	m_tTvwCtrlArray[2].strBtnTvw = m_stcStrDlgTvwSet + "/" + "BtnTvw3";
	m_tTvwCtrlArray[3].strBtnTvw = m_stcStrDlgTvwSet + "/" + "BtnTvw4";
	m_tTvwCtrlArray[4].strBtnTvw = m_stcStrDlgTvwSet + "/" + "BtnTvw5";

	m_wSelChannel = INVALID_WORD;
}

CTvwLogic::~CTvwLogic()
{
    if ( m_pLogic != NULL )
    {   
        UnRegMsg();
        UnRegFunc();
        delete m_pLogic;
        m_pLogic = NULL; 
    }
}


CTvwLogic* CTvwLogic::GetLogicPtr()
{
    if ( m_pLogic == NULL )
    {  
        m_pLogic = new CTvwLogic();   
    }
    
    return m_pLogic;
}

void CTvwLogic::RegMsg()
{   
    //会议的cns列表更新 
    REG_MSG_HANDLER( UI_UMS_REFRESH_CONFCNS_LIST, CTvwLogic::OnRefreshCnsLstNotify, m_pLogic, CTvwLogic );
	REG_MSG_HANDLER( UI_CNS_CONFSTATE_NOTIFY, CTvwLogic::OnRefreshCnsLstNotify, m_pLogic, CTvwLogic );
    
    //离开会议通知
    REG_MSG_HANDLER( UI_UMS_HANGUP_CONF_RSP, CTvwLogic::OnHungupConfRsp, m_pLogic, CTvwLogic );
  
    //REG_MSG_HANDLER( UI_UMS_HANGUP_CONF_RSP, CTvwLogic::OnRefreshTvw, m_pLogic, CTvwLogic );

    //刷新电视墙
    REG_MSG_HANDLER( UI_UMS_REFRESH_TVW_LIST_NOTITFY, CTvwLogic::OnRefreshTvw, m_pLogic, CTvwLogic );

    REG_MSG_HANDLER( UI_UMS_PLAY_HDU_RSP, CTvwLogic::OnPlayRsp, m_pLogic, CTvwLogic );

    REG_MSG_HANDLER( UI_UMS_STOP_PLAY_HDU_RSP, CTvwLogic::OnStopRsp, m_pLogic, CTvwLogic );

    //REG_MSG_HANDLER( UI_UMS_HDU_CODE_STREAM_NOTIFY, CTvwLogic::OnRefreshTvw, m_pLogic, CTvwLogic ); 
}

void CTvwLogic::UnRegMsg()
{
    
}

bool CTvwLogic::RegCBFun()
{   	 
    REG_GOBAL_MEMBER_FUNC( "CTvwLogic::InitWnd", CTvwLogic::InitWnd, m_pLogic, CTvwLogic);
    REG_GOBAL_MEMBER_FUNC( "CTvwLogic::BtnSaveToFileClick", CTvwLogic::BtnSaveToFileClick, m_pLogic, CTvwLogic ) ; 
    REG_GOBAL_MEMBER_FUNC( "CTvwLogic::ClearHudClick", CTvwLogic::ClearHudClick, m_pLogic, CTvwLogic ) ;

    //drag end
    REG_GOBAL_MEMBER_FUNC( "CTvwLogic::OnEndDragToTvw", CTvwLogic::OnEndDragToTvw, m_pLogic, CTvwLogic ) ; 
    REG_GOBAL_MEMBER_FUNC( "CTvwLogic::OnEndDragFrmTvw", CTvwLogic::OnEndDragFrmTvw, m_pLogic, CTvwLogic ) ; 

	REG_GOBAL_MEMBER_FUNC( "CTvwLogic::OnDragOverTvw", CTvwLogic::OnDragOverTvw, m_pLogic, CTvwLogic );
	REG_GOBAL_MEMBER_FUNC( "CTvwLogic::OnDragLeaveTvw", CTvwLogic::OnDragLeaveTvw, m_pLogic, CTvwLogic );

    REG_GOBAL_MEMBER_FUNC( "CTvwLogic::OnCnsItemClick", CTvwLogic::OnCnsItemClick, m_pLogic, CTvwLogic ) ; 
    REG_GOBAL_MEMBER_FUNC( "CTvwLogic::OnTvwItemClick", CTvwLogic::OnTvwItemClick, m_pLogic, CTvwLogic ) ; 
    REG_GOBAL_MEMBER_FUNC( "CTvwLogic::OnTvwBtnKillFocus", CTvwLogic::OnTvwBtnKillFocus, m_pLogic, CTvwLogic ) ; 

    REG_GOBAL_MEMBER_FUNC( "CTvwLogic::OnIconCnsLstAddClick", CTvwLogic::OnIconCnsLstAddClick, m_pLogic, CTvwLogic ) ;  
 
    return true;
}

bool CTvwLogic::UnRegFunc()
{
    return true;
}


bool CTvwLogic::InitWnd( const IArgs & arg )
{   
    CWndLogicBase::InitWnd( arg ); 

    //注册可拖拽窗口 
	CDragWindow* p = CDragWindow::GetDragWindow();
	for ( int i = 0; i < MAX_TVW_COUNT; i++ )
	{
		Window* pBtn = UIManagePtr->GetWindowPtr( m_tTvwCtrlArray[i].strBtnTvw, m_pWndTree );		
		if ( p != NULL && pBtn != NULL )
		{   
			p->RegisterDropWindow( pBtn );
		}
	}
	
    UpdateCnsLst();    
    UpdateTvwLst(); 

    return true;
}


bool CTvwLogic::BtnSaveToFileClick( const IArgs & arg )
{
    return UIManagePtr->SaveToFile(  g_stcStrTvwDlg  );   
}


void CTvwLogic::UpdateTvwLst()
{
    if ( m_pWndTree == NULL )
    {
        return;
    }
     
    TplArray<TCmsTvwInfo>* pTvwList = BusinessManagePtr->GetTvwList();  
	
	int nCount = pTvwList->Size();	
	int i = 0;

	for ( i = 0; i < nCount && i < MAX_TVW_COUNT; i++ )
    {
		TCmsTvwInfo tTvw = pTvwList->GetAt(i);

		u16 wHandle = tTvw.m_dwChannelHandle;
		if ( wHandle < 0 || wHandle >= MAX_TVW_COUNT )
		{
			continue;
		}

		if ( !tTvw.m_bIsOnline )
		{
			//in_addr adr;
            //adr.S_un.S_addr = tTvw.m_dwIpAddr;
			//UIManagePtr->SetCaption( m_tTvwCtrlArray[wHandle].strBtnTvw, inet_ntoa(adr), m_pWndTree );
			//UIManagePtr->EnableWindow( m_tTvwCtrlArray[wHandle].strBtnTvw, false, m_pWndTree );

			UIManagePtr->SetDragBtnOnline( m_tTvwCtrlArray[wHandle].strBtnTvw, false, m_pWndTree );
		}
		else
		{
			UIManagePtr->SetDragBtnOnline( m_tTvwCtrlArray[wHandle].strBtnTvw, true, m_pWndTree );
		}

		CString str = "";
		//CString strEx = "";
		//if ( !tTvw.bCodeStream )
		//{
		//	strEx = "\n当前无码流";
		//}

		TTPHduPlayReq  tTvwInfo;
		tTvwInfo.SetAlias( tTvw.m_achAlias );
		tTvwInfo.m_nChannelHandle = wHandle;
		tTvwInfo.m_wScreenNum = tTvw.m_wScreenNum;
		m_tTvwCtrlArray[wHandle].tTvwData.SetData( tTvwInfo );

		Value_DragButtonData valueData;
		valueData.pData = NULL;

		if ( strlen( tTvw.m_achAlias ) != 0 )
		{
			str.Format( "%s", tTvw.m_achAlias );
			valueData.pData = &(m_tTvwCtrlArray[wHandle].tTvwData);
		}
		else
		{
			str.Format( "%d", wHandle + 1 );
		}

		UIManagePtr->SetCaption( m_tTvwCtrlArray[wHandle].strBtnTvw, (LPCTSTR)str, m_pWndTree );
		UIManagePtr->SetPropertyValue( valueData, m_tTvwCtrlArray[wHandle].strBtnTvw, m_pWndTree );		

	}

	if ( nCount < MAX_TVW_COUNT  )
    {  		
        for ( ; i < MAX_TVW_COUNT; i++ )
        { 
            UIManagePtr->SetDragBtnOnline( m_tTvwCtrlArray[i].strBtnTvw, false, m_pWndTree );
        } 
    }

}


void CTvwLogic::UpdateCnsLst()
{
    if ( m_pWndTree == NULL )
    {
        return ;
    }

    TCMSConf tConfInfo;
    BOOL32 bRe = BusinessManagePtr->IsInConf( &tConfInfo );
    if ( bRe )
    {
		Value_TouchListConfInfo val( tConfInfo );
		val.m_bDrag = TRUE;
		val.m_lstType = em_ConfLstTypeTvw;
		UIManagePtr->SetPropertyValue( val, m_stcStrLstCns, m_pWndTree );
    }
	else
	{
		Value_TransparentListOffset val;
		val.nOffset = 0;
		UIManagePtr->SetPropertyValue( val, m_stcStrLstCns, m_pWndTree );

		Value_TransparentListSelItem valSel;
		valSel.dwDataKey = -1;
		UIManagePtr->SetPropertyValue( valSel, m_stcStrLstCns, m_pWndTree );
		
        UIManagePtr->ShowWindow( g_stcStrTvwDlg, false );
	}
}



//获取将要操作的hdu
u16 CTvwLogic::GetFirstAddHdu()
{  
	if ( m_wSelChannel != INVALID_WORD )
	{
		return m_wSelChannel;
	}

	for ( int i = 0; i < MAX_TVW_COUNT; i++ )
    {
		TTPHduPlayReq tTvwInfo = m_tTvwCtrlArray[i].tTvwData.m_tTvwInfo;

		if ( strlen( tTvwInfo.m_achAlias ) == 0 )
		{
			return i;
		}
	}

	return INVALID_WORD; 
}

HRESULT CTvwLogic::OnRefreshCnsLstNotify( WPARAM wparam, LPARAM lparam)
{ 
    if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }

    UpdateCnsLst();   

	return NO_ERROR;
}


HRESULT CTvwLogic::OnHungupConfRsp( WPARAM wparam, LPARAM lparam)
{
	if ( m_pWndTree != NULL )
	{
		UIManagePtr->ShowWindow( g_stcStrTvwDlg, false );
	}
	return NO_ERROR;
}

 
bool CTvwLogic::OnEndDragToTvw( const IArgs& arg )  
{
    if ( m_pWndTree == NULL )
    {
        return true;
    }

    Args_WindowMsg WinMsg = *dynamic_cast<const Args_WindowMsg*>(&arg);
    WindowMsg msg = WinMsg.m_Msg;  
	
	s32 x = LOWORD(msg.lParam);
	s32 y = HIWORD(msg.lParam);
	CPoint point(x, y);
    
    CRect rect;
    
    for ( int i = 0; i < MAX_TVW_COUNT; i++ )
    {
        Window* pBtn = UIManagePtr->GetWindowPtr( m_tTvwCtrlArray[i].strBtnTvw, m_pWndTree );
        pBtn->GetWindowRect(&rect);
        if ( rect.PtInRect(point) )
        {
			if ( Data_ConfCns *pData =  dynamic_cast<Data_ConfCns*>( (IData*)msg.wParam ))
			{
				TCnsInfo tCnsInfo = pData->m_tConfCns;
				if ( tCnsInfo.m_wEpID == TP_INVALID_INDEX )
				{
					return false;
				}

				SetCnsInTvw( i, tCnsInfo );
				return true;
			} 
		}
	}

    return true;
}
 

bool CTvwLogic::OnEndDragFrmTvw( const IArgs & arg  ) 
{
    if ( m_pWndTree == NULL )
    {
        return true;
    }

    Args_WindowMsg WinMsg = *dynamic_cast<const Args_WindowMsg*>(&arg);
    WindowMsg msg = WinMsg.m_Msg;  

	s32 x = LOWORD(msg.lParam);
	s32 y = HIWORD(msg.lParam);
	CPoint point(x, y);

    if ( Data_TvwInfo *pData = dynamic_cast<Data_TvwInfo*>( (IData*)msg.wParam ) )
    {
        if ( pData->m_tTvwInfo.m_nChannelHandle == INVALID_WORD )
        {
            return false;
        }  

        TTPHduPlayReq  tTvwInfo;
		tTvwInfo = pData->m_tTvwInfo;

		Window* pWnd = UIManagePtr->GetWindowPtr( m_tTvwCtrlArray[tTvwInfo.m_nChannelHandle].strBtnTvw, m_pWndTree );
		CRect rect;
		pWnd->GetWindowRect(&rect);
		if ( !rect.PtInRect(point) )
		{ 	
			u16 re = BusinessManagePtr->DeleteTvw( tTvwInfo );
			if ( re != NO_ERROR )
			{
				HANDLE_ERROR( re );
			}
			else
			{
				UIManagePtr->LoadScheme( "SchmHideDelete", m_pWndTree, m_stcStrBtnDelete );
			}
		}
    }  
    
	return true;
} 


bool CTvwLogic::OnDragOverTvw( const IArgs & args )
{
	if ( m_pWndTree == NULL )
    {
        return true;
    }
	
    Args_WindowMsg WinMsg = *dynamic_cast<const Args_WindowMsg*>(&args);
    WindowMsg msg = WinMsg.m_Msg;  
	
	s32 x = LOWORD(msg.lParam);
	s32 y = HIWORD(msg.lParam);
	CPoint point(x, y);
    
    CRect rect;
    
    for ( int i = 0; i < MAX_TVW_COUNT; i++ )
    {
        Window* pBtn = UIManagePtr->GetWindowPtr( m_tTvwCtrlArray[i].strBtnTvw, m_pWndTree );
        pBtn->GetWindowRect(&rect);
        if ( rect.PtInRect(point) )
        {
			if ( Data_ConfCns *pData = dynamic_cast<Data_ConfCns*>( (IData*)msg.wParam ) )
			{
				TCnsInfo tCnsInfo = pData->m_tConfCns;
				if ( tCnsInfo.m_wEpID == INVALID_WORD )
				{
					return false;
				}

				SetCnsInTvw( i, tCnsInfo, TRUE );
				return true;
			}
		}
	}
	return true;
}

bool CTvwLogic::OnDragLeaveTvw( const IArgs & args )
{
	if ( m_pWndTree == NULL )
    {
        return true;
    }

	for ( int i = 0; i < MAX_TVW_COUNT; i++ )
	{
		UIManagePtr->SetSelState( m_tTvwCtrlArray[i].strBtnTvw, false, m_pWndTree );
	}
	return true;
}


bool CTvwLogic::ClearHudClick( const IArgs & arg )
{
	u16 re = BusinessManagePtr->DeleteTvw( m_tSelTvwInfo );
    if ( re != NO_ERROR )
    {
        HANDLE_ERROR( re );
    }
    else
    {
		if ( m_wSelChannel != INVALID_WORD )
		{
			m_wSelChannel = INVALID_WORD;
		}
        UIManagePtr->LoadScheme("SchmHideDelete" , m_pWndTree, m_stcStrBtnDelete);
    }
	return true;
}

bool  CTvwLogic::OnCnsItemClick( const IArgs & arg  ) 
{
    if ( const Args_ClickItemInfo *pClickInfo = dynamic_cast<const Args_ClickItemInfo*>(&arg) )
    {
        const IData *pIData = pClickInfo->m_pClickList->GetItemData()->GetUserData();
        if ( const Data_ConfCns * pDataTemp = dynamic_cast< const Data_ConfCns*>(pIData) )
        {    
            // pDataTemp->m_tConfCns.m_achRoomName ; 
        }
    } 

    return true;
}



bool CTvwLogic::OnTvwItemClick( const IArgs& arg  ) 
{
	if ( const Args_WindowMsg* pWinMsg = dynamic_cast<const Args_WindowMsg*>(&arg) )
	{
		WindowMsg msg = pWinMsg->m_Msg;  

		s32 x = LOWORD(msg.lParam);
		s32 y = HIWORD(msg.lParam);
		CPoint point(x, y);
		
		CRect rect;
		
		for ( int i = 0; i < MAX_TVW_COUNT; i++ )
		{
			Window* pBtn = UIManagePtr->GetWindowPtr( m_tTvwCtrlArray[i].strBtnTvw, m_pWndTree );
			pBtn->GetWindowRect(&rect);
			if ( rect.PtInRect(point) )
			{
				m_wSelChannel = i;

				if ( Data_TvwInfo *pData = dynamic_cast<Data_TvwInfo*>( (IData*)msg.wParam ) )
				{
					m_tSelTvwInfo = pData->m_tTvwInfo;
					if ( strlen( m_tSelTvwInfo.m_achAlias ) > 0 )
					{
						UIManagePtr->LoadScheme( "SchmShowDelete", m_pWndTree, m_stcStrBtnDelete );
					}
					else
					{
						UIManagePtr->LoadScheme( "SchmHideDelete", m_pWndTree, m_stcStrBtnDelete );
					}
				}
				else
				{
					UIManagePtr->LoadScheme( "SchmHideDelete", m_pWndTree, m_stcStrBtnDelete );
				}

				return true;
			}
		}
		
	}
    
    return true;   
}

bool CTvwLogic::OnIconCnsLstAddClick( const IArgs & arg  ) 
{
    if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast<const Args_ClickItemInfo*>(&arg) )
    {
        const IData *pIData = pClickInfo->m_pClickList->GetParentItem()->GetItemData()->GetUserData();
        if ( const Data_ConfCns* pData = dynamic_cast< const Data_ConfCns*>(pIData) )
        {   
			u16 wChannel = GetFirstAddHdu();
            if ( wChannel == TP_INVALID_INDEX )
			{
				PrtMsgForce( 0, emEventTypeCmsWindow, "[CTvwLogic::OnIconCnsLstAddClick]:获取当前可操作的HDU为空" );
				return false;
			}

			TCnsInfo tCnsInfo = pData->m_tConfCns;
			SetCnsInTvw( wChannel, tCnsInfo );
        }
    } 
    
    return true;    
}

bool CTvwLogic::OnTvwBtnKillFocus( const IArgs& args )
{
	if ( m_wSelChannel != INVALID_WORD )
	{
		m_wSelChannel = INVALID_WORD;
		UIManagePtr->LoadScheme( "SchmHideDelete", m_pWndTree, m_stcStrBtnDelete );
	}
	
	return true;
}


void CTvwLogic::SetCnsInTvw( u16 wHandle, TCnsInfo tCnsInfo, BOOL bSel /* = FALSE */ )
{
	if ( wHandle < 0 || wHandle >= MAX_TVW_COUNT )
	{
		return;
	}
	if ( tCnsInfo.m_wEpID == TP_INVALID_INDEX || m_pWndTree == NULL )
	{
		return;
	}
	
	if ( tCnsInfo.m_wLevel == emTPSipCounty )
	{
		if ( bSel )
		{
			UIManagePtr->SetSelState( m_tTvwCtrlArray[wHandle].strBtnTvw, true, m_pWndTree );
		}
		else
		{
			TTPHduPlayReq  tTvwInfo;
			tTvwInfo.SetAlias( tCnsInfo.m_achRoomName );
			tTvwInfo.m_nChannelHandle = wHandle;
			tTvwInfo.m_wScreenNum = 1;
			u16 re = BusinessManagePtr->PlayTvw( tTvwInfo );
			if ( re != NO_ERROR )
			{
				HANDLE_ERROR( re );
			}
			UIManagePtr->SetSelState( m_tTvwCtrlArray[wHandle].strBtnTvw, false, m_pWndTree );
			if ( wHandle == m_wSelChannel )
			{
				m_wSelChannel = INVALID_WORD;
				UIManagePtr->LoadScheme( "SchmHideDelete", m_pWndTree, m_stcStrBtnDelete );
			}
		}		
	}
	else if ( tCnsInfo.m_wLevel == emTPSipCity || tCnsInfo.m_wLevel == emTPSipProvince )
	{
		int anChannel[3] = { 0 };
		switch( wHandle )
		{
		case 0:
			anChannel[0] = wHandle;
			anChannel[1] = wHandle + 1;
			anChannel[2] = wHandle + 2;
			break;
		case 1:
		case 2:
		case 3:
			anChannel[0] = wHandle - 1;
			anChannel[1] = wHandle;
			anChannel[2] = wHandle + 1;
			break;
		case 4:
			anChannel[0] = wHandle - 2;
			anChannel[1] = wHandle - 1;
			anChannel[2] = wHandle;
			break;
		default:
			return;
		}
		
		for ( int i = 0; i < 3; i++ )
		{
			int nChannel = anChannel[i];
			if ( bSel )
			{
				UIManagePtr->SetSelState( m_tTvwCtrlArray[nChannel].strBtnTvw, true, m_pWndTree );
			}
			else
			{	
				TTPHduPlayReq tTvwInfo;
				tTvwInfo.SetAlias( tCnsInfo.m_achRoomName );
				tTvwInfo.m_nChannelHandle = nChannel;
				tTvwInfo.m_wScreenNum = i;
				u16 re = BusinessManagePtr->PlayTvw( tTvwInfo );
				if ( re != NO_ERROR )
				{
					HANDLE_ERROR( re );
				}

				UIManagePtr->SetSelState( m_tTvwCtrlArray[nChannel].strBtnTvw, false, m_pWndTree );
				if ( nChannel == m_wSelChannel )
				{
					m_wSelChannel = INVALID_WORD;
					UIManagePtr->LoadScheme( "SchmHideDelete", m_pWndTree, m_stcStrBtnDelete );
				}
			}
		}
	}

}

HRESULT CTvwLogic::OnRefreshTvw( WPARAM wparam, LPARAM lparam)
{   
	if ( m_pWndTree == NULL )
	{
		return NO_ERROR;
	}

	UpdateTvwLst();
	UpdateCnsLst();   
	return NO_ERROR;
}

/*
em_Hdu_Illegal,
	em_Alias_Illegal,
	em_Monitor_Fial,
	em_Hdu_PlayNack,
    em_Same_Alias,
	em_unknown,
*/
HRESULT CTvwLogic::OnPlayRsp( WPARAM wparam, LPARAM lparam) 
{   
    if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }

    if ( !BusinessManagePtr->IsInConf())
    {
       return NO_ERROR;
    }

    BOOL32 bSucsess = (BOOL32)wparam;
    if ( !bSucsess )
    {
        EmTpHduPlayNackReason emReason = (EmTpHduPlayNackReason)lparam;
        switch( emReason )
        {
        case em_Alias_Illegal:
            ShowPopMsg("会场显示到电视墙失败：会场名非法");
            break;    
        case em_Hdu_Illegal:
            ShowPopMsg("会场显示到电视墙失败：电视墙非法");
            break;
        case em_Monitor_Fial:
            ShowPopMsg("会场显示到电视墙失败：监控失败");
            break;
        case em_Hdu_PlayNack:
            ShowPopMsg("会场显示到电视墙失败： 播放失败");
            break;
        case em_Same_Alias:
            ShowPopMsg("会场已经显示在该电视墙中");
            break;    
        default:
            ShowPopMsg("会场显示到电视墙失败： 未知错误");
            break;
        }      
    }
    else
    {
		UpdateTvwLst();
		UpdateCnsLst();   
    }
        
    return NO_ERROR;
}

HRESULT CTvwLogic::OnStopRsp( WPARAM wparam, LPARAM lparam)
{
    if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }

	UpdateTvwLst();
	UpdateCnsLst();   
	return NO_ERROR;
}

void CTvwLogic::Clear()
{  
    if ( m_pWndTree )
    {
        UIManagePtr->LoadScheme( "", m_pWndTree, "", false ); 
		UIManagePtr->ShowWindow( g_stcStrTvwDlg, false );
    } 
}