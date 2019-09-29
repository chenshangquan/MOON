// dualSrcLogic.cpp: implementation of the CDualSrcLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dualSrcLogic.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDualSrcLogic * CDualSrcLogic::m_pLogic = NULL;

CDualSrcLogic::CDualSrcLogic()
{

}

CDualSrcLogic::~CDualSrcLogic()
{
	if ( m_pLogic != NULL )
	{   
		UnRegMsg();
		UnRegFunc();
		delete m_pLogic;
		m_pLogic = NULL; 
	}
}

CDualSrcLogic* CDualSrcLogic::GetLogicPtr()
{
	if ( m_pLogic == NULL )
	{  
		m_pLogic = new CDualSrcLogic();   
	}
	
	return m_pLogic;
}

void CDualSrcLogic::RegMsg()
{
    REG_MSG_HANDLER( UI_CNS_VGAINFO_NOTIFY, CDualSrcLogic::OnVgaInfoNotify, m_pLogic, CDualSrcLogic ); 	
    REG_MSG_HANDLER( UI_CNS_CONFVGAINFO_NOTIFY, CDualSrcLogic::OnVgaInfoNotify, m_pLogic, CDualSrcLogic ); 
    REG_MSG_HANDLER( UI_CNS_SELDUALPORT_IND, CDualSrcLogic::OnSelDualPortInd, m_pLogic, CDualSrcLogic ); 
}

void CDualSrcLogic::UnRegMsg()
{
}

bool CDualSrcLogic::RegCBFun()
{  
	REG_GOBAL_MEMBER_FUNC( "CDualSrcLogic::InitWnd", CDualSrcLogic::InitWnd, m_pLogic, CDualSrcLogic );
    REG_GOBAL_MEMBER_FUNC( "CDualSrcLogic::OnCnsLstItem", CDualSrcLogic::OnCnsLstItem, m_pLogic, CDualSrcLogic );
    
	return true;
}

bool CDualSrcLogic::UnRegFunc()
{	
	return true;
}

bool CDualSrcLogic::InitWnd( const IArgs & args )
{
	CWndLogicBase::InitWnd( args );
	
	return true;
}


void CDualSrcLogic::Clear()
{ 
	if ( m_pWndTree != NULL )
	{
	    m_tDualSrcInfo.Clear();
	}
    UIManagePtr->ShowWindow( g_strDualSrcDlg, false );
}


bool CDualSrcLogic::OnCnsLstItem( const IArgs & args )
{
    if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast<const Args_ClickItemInfo*>(&args) )
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetItemData();
        if ( const Data_DualSrc *pItemInfo = dynamic_cast<const Data_DualSrc*>( pBaseItem->GetUserData() ) )
        {
            TVgaInfo tVgaInfo = pItemInfo->m_tVgaInfo;
            
            if ( tVgaInfo.m_emVgaType != m_tDualSrcInfo.emCurrentType )
            {
                ComInterface->SelDualInputPort( tVgaInfo.m_emVgaType );
            }
        }
    }

    return true;
}


LRESULT CDualSrcLogic::OnVgaInfoNotify( WPARAM wParam, LPARAM lParam )
{
    if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }
    
	ComInterface->GetDualSrcInfo( m_tDualSrcInfo );

    Value_ListDualSrc listDualSrc( m_tDualSrcInfo, "CDualSrcLogic::OnCnsLstItem", FALSE );
	UIManagePtr->SetPropertyValue( listDualSrc, "LstDualSrc", m_pWndTree );

    return NO_ERROR;
}

LRESULT CDualSrcLogic::OnSelDualPortInd( WPARAM wParam, LPARAM lParam )
{
    if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }

    BOOL bOk = (BOOL)wParam;
    EmVgaSwitchResult emResult = (EmVgaSwitchResult)lParam;
    
    if ( emResult == em_CurVgaNoSignal )
    {
        ShowPopMsg( "当前演示源无输入" );
    }
    else if ( emResult == em_TpNoDual )
    {
        ShowPopMsg( "当前演示源无双流终端" );
    }
	else if ( emResult == em_VgaBusying )
	{
		ShowPopMsg( "当前演示源正忙，拒绝切换" );
	}
	else if ( emResult == em_VgaSwitchInvalid )
	{
		ShowPopMsg( "当前演示源无效" );
	}
    else
    {
        ShowPopMsg( "切换演示源失败" );
    }

    return NO_ERROR;
}