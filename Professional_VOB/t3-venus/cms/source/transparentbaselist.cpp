/*****************************************************************************
模块名      : 通用竖排列表
文件名      : transparentbaselist.cpp
相关文件    : transparentbaselist.h
文件实现功能: 通用列表相关功能，列表第一级子条目竖排
作者        : 肖楚然
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
  日  期      版本        修改人      修改内容
2012/04/01    1.0         肖楚然        创建
******************************************************************************/

#include "stdafx.h"
#include "AddrList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransparentBaseList

#define  TIMER_HANDLE_MOVING  100 
const CString CTransparentBaseList::strTopLeft = "topleft.png";
const CString CTransparentBaseList::strTopCenter = "topcenter.png";
const CString CTransparentBaseList::strTopRight = "topright.png";
const CString CTransparentBaseList::strCenterLeft = "centerleft.png";
const CString CTransparentBaseList::strCenterRight = "centerright.png";
const CString CTransparentBaseList::strBottomLeft = "bottomleft.png";
const CString CTransparentBaseList::strBottomCenter = "bottomcenter.png";
const CString CTransparentBaseList::strBottomRight = "bottomright.png";
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CTransparentBaseList, CDlgChild)
//{{AFX_MSG_MAP(CTransparentList)
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_MOUSEMOVE()
ON_WM_SIZE()
ON_WM_TIMER()
ON_MESSAGE( WM_REDRAW_UI, OnRedrawUI )
ON_MESSAGE( WM_MOUSEWHEEL, OnMouseWheels )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTest message handlers

CTransparentBaseList::CTransparentBaseList(CString strName, CRect rcWnd, CWnd* pWnd) 
: IList( rcWnd.Width(), rcWnd.Height() ) , CDlgChild( pWnd )
{
	m_nTotalYOffset = 0;
	m_nTotalXOffset = 0;
	m_nMoveSpeed = 0;
	m_bLBtnDown = FALSE;
	m_bDragEnable = TRUE;
	m_bClickNoSel = FALSE;
	m_bClickFocus = TRUE;
	m_pSelItem = NULL;
	m_pLastItem = NULL;
	m_dwSelDataKey = -1;

	m_pImgTopLeft = NULL;
    m_pImgTopCenter = NULL;
    m_pImgTopRight = NULL;	
    m_pImgCenterLeft = NULL;
	m_pImgCenterRight = NULL;
    m_pImgBottomLeft = NULL;
    m_pImgBottomCenter = NULL;
	m_pImgBottomRight = NULL;
}

CTransparentBaseList::~CTransparentBaseList()
{
	
}


LRESULT CTransparentBaseList::OnRedrawUI( WPARAM wParam, LPARAM lParam )
{  
	if ( IsWindowVisible() == FALSE )
	{
		return S_FALSE;
	}
	Graphics* pGraphics = (Graphics*)wParam;
	if ( pGraphics == NULL )
	{
		GetParent()->SendMessage( WM_REDRAW_UI, wParam, lParam );
		return S_OK;
	}

    HWND hGraphWnd = (HWND )lParam;
    CWnd * pGraphWnd = FromHandle(hGraphWnd);
    if ( hGraphWnd == NULL )
    {
        return S_FALSE;
    }
	
	DrawUI( pGraphics, /*GetParent()*/ pGraphWnd );
	return S_OK;
}

void CTransparentBaseList::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default  

	if ( m_bClickFocus )
	{
		//解决当点击列表时 edit框仍然有焦点的问题  2011-12-7 by yjj
		HWND hFocusWnd = ::GetFocus();
		if ( hFocusWnd != m_hWnd )
		{   
			this->SetFocus();
		}
	}

	m_bLBtnDown = FALSE;

	if ( m_pItemList == NULL )
	{
		return;
	}

	if ( m_nMoveSpeed != 0 )
	{   		
		m_nMoveSpeed = 0;
		KillTimer(TIMER_HANDLE_MOVING);	
	} 

	m_bLBtnDown = TRUE;
	m_ptMouseNow = point;
	m_ptMouseLast = point;
	m_ptMouseDown = point;


	IItemList* pSelList = NULL;
	IsClick( m_pItemList, point, &pSelList );

	if ( m_pSelItem != NULL )
	{
		SetSelItemStatus( emItemStatusNormal );
		
		m_pSelItem = NULL;
		m_pLastItem = NULL;
		m_dwSelDataKey = -1;
	}

	if ( pSelList != NULL )
	{
		m_pSelItem = pSelList;

		while( pSelList != NULL && pSelList->GetParentItem() != NULL )
		{
			IBaseItem* pBaseItem = pSelList->GetItemData();

			if ( pBaseItem->GetItemStatus() == emItemStatusDisable )
			{    
				m_pSelItem = NULL;         
				return;
			}
			pBaseItem->SetItemStatus( emItemStatusSel );

			if ( pBaseItem->GetUserData() != NULL )
			{
				IData* pData = const_cast<IData*>( pBaseItem->GetUserData() );
				m_dwSelDataKey = pData->GetDataKey();
			}
			//如果点击条目有响应事件，不再将父条目设为选中
			if ( pBaseItem->GetFunc() != IBaseItem::strDefaultFunc )
			{
				break;
			}
			pSelList = pSelList->GetParentItem();
		}
			
		m_pLastItem = m_pSelItem;
	}

	GetParent()->SendMessage( WM_REDRAW_UI, 0, (LPARAM)m_hWnd );
	
	SetCapture();
//	CTransparentWnd::OnLButtonDown(nFlags, point);
}

void CTransparentBaseList::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if ( !m_bLBtnDown )
	{   
		return;
	} 	
	
	m_bLBtnDown = FALSE;	
	
	if ( m_pSelItem != NULL )
	{
		if ( point == m_ptMouseDown )
		{
			IBaseItem* pItem = m_pSelItem->GetItemData();
			if ( CImageItem* pImageItem = dynamic_cast<CImageItem*>( pItem ) )
			{
				if ( pItem->GetItemStatus() != emItemStatusDisable )
				{
					pItem->SetItemStatus( emItemStatusNormal );
				}
			}
			
			Clicked( nFlags, point );
			
			if ( m_bClickNoSel )
			{
				SetSelItemStatus( emItemStatusNormal );
				m_pSelItem = NULL;
				m_dwSelDataKey = -1;
			}
		}
		else
		{
			SetSelItemStatus( emItemStatusNormal );
			m_pSelItem = NULL;
			m_dwSelDataKey = -1;     
			
			//通知外部当前没有选中项
			PostMessage(WM_LST_UN_SELECT_ITEM);
		}		
	}

 
	if ( abs(m_ptMouseLast.y - m_ptMouseNow.y) > 6 ) //产生惯性运动
    {
		m_nMoveSpeed = (m_ptMouseNow.y - m_ptMouseLast.y) / 5;
		SetTimer( TIMER_HANDLE_MOVING, 20, NULL );	   
    }

	if ( GetCapture() == this )
	{
		ReleaseCapture();
	}

	if ( m_pSelItem == m_pItemList )
	{
		m_dwSelDataKey = -1; 
		//通知外部当前没有选中项
		PostMessage(WM_LST_UN_SELECT_ITEM);
	}
   
	GetParent()->SendMessage( WM_REDRAW_UI, 0, (LPARAM)m_hWnd );

//	CTransparentWnd::OnLButtonUp(nFlags, point);
}

void CTransparentBaseList::SetSelItemStatus( EmItemStatus emStatus )
{	
	if ( m_pSelItem != NULL )
	{
		IItemList* pList = m_pSelItem;
		while( pList != NULL && pList->GetParentItem() != NULL )
		{
			IBaseItem* pItem = pList->GetItemData();
			if ( pItem != NULL && pItem->GetItemStatus() != emItemStatusDisable )
			{
				pItem->SetItemStatus( emStatus );
			}
			pList = pList->GetParentItem();
		}
	}
}


void CTransparentBaseList::Clicked( UINT nFlags, CPoint point )
{

}

CRect CTransparentBaseList::GetFrameInScreen( IItemList* pList )
{
	ASSERT( pList );
	IItemList* pTemp = pList;
	IBaseItem* pData = pTemp->GetItemData();
	CRect rcChild = pData->GetItemRect();
	while ( pTemp != 0 && pTemp->GetParentItem() != 0 && pTemp->GetParentItem()->GetParentItem() != 0 )
	{		
		pTemp = pTemp->GetParentItem();
		pData = pTemp->GetItemData();
		rcChild = pData->GetItemRect();
	}
	pData = m_pItemList->GetItemData();
	CPoint ptOffset = pData->GetOffset();
	rcChild.OffsetRect( ptOffset );
	ClientToScreen( &rcChild );
	return rcChild;
}


void CTransparentBaseList::Draw( IArgs* pArgs )
{
	IList::Draw( pArgs, -m_nTotalYOffset, m_rctDlg.Height() );
}

void CTransparentBaseList::DrawUI( Graphics* pGraphics, CWnd* pParent )
{   
    if ( pGraphics == NULL  || pParent == NULL )
    {
        return ;
    }

// 	delete m_pCacheAllImage1;	
// 	m_pCacheAllImage1 = new Bitmap( m_BakWidth, m_BakHeight );
// 	Graphics g( m_pCacheAllImage1 );
// 	g.DrawImage( m_pCacheBkImage, 0, 0, m_BakWidth, m_BakHeight );

	CRect rc = GetListRect();

	Bitmap* pSubBitmap = new Bitmap( rc.Width(), rc.Height() ); 
	Graphics* pGraph = Graphics::FromImage( pSubBitmap );
	
	pGraph->DrawImage( m_pImageBK, 0, 0, rc.Width(), rc.Height() );
	
	Args_Graphics args_Graphics( pGraph, Rect( rc.left, rc.top, rc.Width(), rc.Height() ) );
	Draw( &args_Graphics );	

	CRect rcWnd;
	this->GetWindowRect( rcWnd );
	pParent->ScreenToClient( rcWnd );
	pGraphics->DrawImage( pSubBitmap, rcWnd.left, rcWnd.top );

	delete pSubBitmap;
 	pSubBitmap = 0;
	delete pGraph;
	pGraph = 0;
//	CTransparentWnd::DrawUI( pGraphics, pParent );
} 

CRect CTransparentBaseList::GetListRect()
{
	this->GetClientRect( m_rctDlg );

	return m_rctDlg;
}


void CTransparentBaseList::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if ( nFlags != MK_LBUTTON || !m_bLBtnDown  )
    {   
		return;
    }
	
	m_ptMouseLast = m_ptMouseNow;
	m_ptMouseNow = point;

	ListMove();
		
	//移出对话框，拖拽开始		
	if ( m_bDragEnable && m_pSelItem != NULL && IsReadyForDrag() )
	{    				
		IItemList* pDragItem = m_pSelItem ;
		while( pDragItem != NULL && pDragItem != m_pItemList )
		{
			IBaseItem* pItem = pDragItem->GetItemData();
			if ( pItem == NULL )
			{
				break;
			}
			if ( pItem->GetDragStatus() )
			{
				if ( GetCapture() == this )
				{
					ReleaseCapture();
				}
				CDragWindow * pDragWnd = CDragWindow::GetDragWindow(); 	
				pDragWnd->SetWindowText( "DragWnd" );
				if ( pDragWnd != NULL )
				{			
					Bitmap* pBitmap = CBitmapHelp::CreateBitmap( pDragItem );
					IData *pData = const_cast<IData*>( pItem->GetUserData() );
					CPoint pt;
					GetCursorPos( &pt );
					pDragWnd->BeginDrag( this, pt, pBitmap, pData );
					break;
				}
			}
			pDragItem = pDragItem->GetParentItem();
		}		
	} 	

	GetParent()->SendMessage( WM_REDRAW_UI, 0, (LPARAM)m_hWnd );
//	CTransparentWnd::OnMouseMove(nFlags, point);
}

void CTransparentBaseList::ListMove()
{
	if ( m_pSelItem == NULL )
	{
		return;
	}
	
	IItemList* pSelList = m_pSelItem;
	while( pSelList != NULL )
	{
		IBaseItem* pItem = pSelList->GetItemData();
		if ( pItem != NULL && pItem->GetMoveStatus() )
		{
			break;
		}
		pSelList = pSelList->GetParentItem();
	}

	if ( pSelList == NULL )
	{
		return;
	}

	m_nTotalYOffset += ( m_ptMouseNow.y - m_ptMouseLast.y );
	//m_nTotalXOffset += ( m_ptMouseNow.x - m_ptMouseLast.x );

	//CRect retList = GetFrame( pSelList );

	if ( m_nTotalYOffset > 0 )
	{
		m_nTotalYOffset = 0;  	
	}	
	if ( m_nTotalYOffset < m_rctDlg.Height() - m_rctList.Height() )
	{
		m_nTotalYOffset = m_rctDlg.Height() - m_rctList.Height();	
		if ( m_nTotalYOffset > 0 )
		{	
			m_nTotalYOffset = 0;
		}	
	}
						
	IBaseItem* pItem = pSelList->GetItemData();
	if ( pItem != NULL )
	{
		pItem->SetOffset( CPoint(0, m_nTotalYOffset) );
	}
}

void CTransparentBaseList::ListAutoMove()
{	
	if ( m_pLastItem == NULL )
	{
		m_nMoveSpeed = 0;
		return;
	}

	IItemList* pSelList = m_pLastItem;      
	while( pSelList != NULL )
	{
		IBaseItem* pItem = pSelList->GetItemData();
		if ( pItem != NULL && pItem->GetMoveStatus() )
		{
			break;
		}
		pSelList = pSelList->GetParentItem();
	}
	
	if ( pSelList == NULL )
	{
		return;
	}

	m_nTotalYOffset += m_nMoveSpeed;
	m_nMoveSpeed *= 0.96;

	//CRect retList = GetFrame( pSelList );
	
	if ( m_nTotalYOffset > 0 )
	{    
		m_nMoveSpeed = 0; 
		m_nTotalYOffset = 0;  	 
	}
	
	if ( m_nTotalYOffset < m_rctDlg.Height() - m_rctList.Height() )
	{
		m_nTotalYOffset = m_rctDlg.Height() - m_rctList.Height();	
		if ( m_nTotalYOffset > 0 )
		{	 
			m_nMoveSpeed = 0;
			m_nTotalYOffset = 0; 
		} 
	}  

	IBaseItem* pItem = pSelList->GetItemData();
	if ( pItem != NULL )
	{
		pItem->SetOffset( CPoint(0, m_nTotalYOffset) );
	}
	
	if ( 0 == m_nMoveSpeed )
	{ 
		KillTimer(TIMER_HANDLE_MOVING);  
	} 

	GetParent()->SendMessage( WM_REDRAW_UI, 0, (LPARAM)m_hWnd );
}


void CTransparentBaseList::OnSize(UINT nType, int cx, int cy) 
{
	CDlgChild::OnSize(nType, cx, cy);
	
	CRect rc;
//	this->GetClientRect( rc );
	this->GetWindowRect(rc);
	SetListSize( rc.Width(), rc.Height() );
	// TODO: Add your message handler code here	
}

void CTransparentBaseList::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if ( nIDEvent == TIMER_HANDLE_MOVING )
	{
		if ( m_nMoveSpeed == 0 )
		{   
			KillTimer(TIMER_HANDLE_MOVING);
		} 
		
		ListAutoMove();
	}
	
	CDlgChild::OnTimer(nIDEvent);
}


void CTransparentBaseList::SetDragEnable( BOOL bDrag )
{
	m_bDragEnable = bDrag;
}

/*=============================================================================
函 数 名:SetClickNoSel
功    能:设置列表点击后是否将条目不选中
参    数:bSel  
注    意:
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人   修改内容
2012/04/01  1.0     肖楚然     创建
=============================================================================*/
void CTransparentBaseList::SetClickNoSel( BOOL bSel )
{
	m_bClickNoSel = bSel;
}

/*=============================================================================
函 数 名:SetClickFocus
功    能:设置列表点击后是否要得到焦点
参    数:bFocus  
注    意:
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人   修改内容
2012/04/01  1.0     肖楚然     创建
=============================================================================*/
void CTransparentBaseList::SetClickFocus( BOOL bFocus )
{
	m_bClickFocus = bFocus;
}

/*=============================================================================
函 数 名:ResetSelItem
功    能:重设选中项
参    数:bResetOffset  是否重设位置
注    意:列表刷新后需调用此函数，否则原有选中项会消失
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人   修改内容
2012/04/01  1.0     肖楚然     创建
=============================================================================*/
void CTransparentBaseList::ResetSelItem( BOOL bResetOffset )
{
	if ( m_nMoveSpeed != 0 )
	{   		
		m_nMoveSpeed = 0;
		KillTimer(TIMER_HANDLE_MOVING);	
	} 
 
    int nItemCount = m_pItemList->GetItemCount();
    if ( nItemCount <= 0 )
    {
		m_nTotalYOffset = 0;
    }

	m_rctList = GetFrame( m_pItemList );

	//将位置重设一次，防止刷新后界面显示条目不够的情况
	if ( !bResetOffset )
	{
		SetYOffset( -m_nTotalYOffset );
	}

	if ( m_dwSelDataKey == -1 )
	{
		return;
	}		
	
	for ( int nIndex = 0; nIndex < nItemCount; nIndex++ )
	{
		IItemList* pSubList = m_pItemList->GetItemByIndex( nIndex );
		if ( pSubList != NULL )
		{
			IBaseItem* pSubItem = pSubList->GetItemData();
			if ( pSubItem != NULL && pSubItem->GetUserData() != NULL )
			{		
				IData* pData = const_cast<IData*>( pSubItem->GetUserData() );
				if ( pData->GetDataKey() == m_dwSelDataKey )
				{
					m_pSelItem = pSubList;
					pSubItem->SetItemStatus( emItemStatusSel );
					if ( bResetOffset )
					{
						int nYOffset = GetOffsetHeight( nIndex );
						SetYOffset( nYOffset );
					}					
					return;
				}
			}		
		}
	}

}

/*=============================================================================
函 数 名:SetSelItem
功    能:设置列表选中条目
参    数:dwDataKey  选中条目的Key  
注    意:
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人   修改内容
2012/04/01  1.0     肖楚然     创建
=============================================================================*/
void CTransparentBaseList::SetSelItem( unsigned long dwDataKey )
{
	if ( m_pSelItem != NULL )
	{
		SetSelItemStatus( emItemStatusNormal );
		m_pSelItem = NULL;
	}

	if ( dwDataKey == -1 )
	{
		m_dwSelDataKey = -1;
		return;
	}

	m_dwSelDataKey = dwDataKey;
	ResetSelItem( TRUE );
}

IBaseItem* CTransparentBaseList::GetSelItem()
{
	if ( m_pSelItem == NULL || m_dwSelDataKey == -1 )
	{
		return NULL;
	}

	int nItemCount = m_pItemList->GetItemCount();
	for ( int nIndex = 0; nIndex < nItemCount; nIndex++ )
	{
		IItemList* pSubList = m_pItemList->GetItemByIndex( nIndex );
		if ( pSubList != NULL )
		{
			IBaseItem* pSubItem = pSubList->GetItemData();
			if ( pSubItem != NULL && pSubItem->GetUserData() != NULL )
			{		
				IData* pData = const_cast<IData*>( pSubItem->GetUserData() );
				if ( pData->GetDataKey() == m_dwSelDataKey )
				{
					return pSubItem;
				}
			}		
		}
	}
	return NULL;
}


int CTransparentBaseList::GetOffsetHeight( int nIndex )
{
	int nHeight = 0;
	for ( int i = 0; i < nIndex; i++ )
	{
		IItemList* pSubList = m_pItemList->GetItemByIndex( i );
		if ( pSubList != NULL )
		{
			IBaseItem* pItem = pSubList->GetItemData();
			if ( pItem != NULL )
			{
				nHeight += pItem->GetItemHeight() + 2;
			}			
		}		
	}
	return nHeight;
}


BOOL CTransparentBaseList::IsReadyForDrag()
{
	BOOL bDrag = FALSE;
	IBaseItem* pRootItem = m_pItemList->GetItemData();
	if ( pRootItem != NULL )
	{
		String strLayout = pRootItem->GetLayoutAlgorithm();
		if ( strLayout == IAlgorithm::strHori )
		{
			if ( m_rctDlg.top > m_ptMouseNow.y || m_rctDlg.bottom < m_ptMouseNow.y )
			{
				bDrag = TRUE;
			}
		}
		else
		{
			if ( m_rctDlg.left > m_ptMouseNow.x || m_rctDlg.right < m_ptMouseNow.x )
			{
				bDrag = TRUE;
			}
		}
	}
	return bDrag;
}

/*=============================================================================
函 数 名:SetYOffset
功    能:设置列表偏移量
参    数:nOffset 偏移位置  
注    意:
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人   修改内容
2012/04/01  1.0     肖楚然     创建
=============================================================================*/
void CTransparentBaseList::SetYOffset( int nOffset )
{
	if ( m_nMoveSpeed != 0 )
	{   		
		m_nMoveSpeed = 0;
		KillTimer(TIMER_HANDLE_MOVING);	
	}

	m_nTotalYOffset = -nOffset;
	
	//CRect retList = GetFrame( m_pItemList );
	if ( m_nTotalYOffset > 0 )
	{
		m_nTotalYOffset = 0;  	
	}	
	if ( m_nTotalYOffset < m_rctDlg.Height() - m_rctList.Height() )
	{
		m_nTotalYOffset = m_rctDlg.Height() - m_rctList.Height();	
		if ( m_nTotalYOffset > 0 )
		{	
			m_nTotalYOffset = 0;
		}	
	}

	IBaseItem* pItem = m_pItemList->GetItemData();
	if ( pItem != NULL )
	{
		pItem->SetOffset( CPoint(0, m_nTotalYOffset) );
	}

	GetParent()->SendMessage( WM_REDRAW_UI, 0, (LPARAM)m_hWnd );
}


int CTransparentBaseList::GetYOffset()
{
	return -m_nTotalYOffset;
}


/*=============================================================================
函 数 名:SetBottomOffset
功    能:设置列表到底部位置
参    数:
注    意:
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人   修改内容
2012/04/01  1.0     肖楚然     创建
=============================================================================*/
void CTransparentBaseList::SetBottomOffset()
{
	if ( m_pItemList == NULL )
	{
		return;
	}
	//CRect retList = GetFrame( m_pItemList );
	m_nTotalYOffset = m_rctDlg.Height() - m_rctList.Height();	
	if ( m_nTotalYOffset > 0 )
	{	
		m_nTotalYOffset = 0;
	}

	IBaseItem* pItem = m_pItemList->GetItemData();
	if ( pItem != NULL )
	{
		pItem->SetOffset( CPoint(0, m_nTotalYOffset) );
	}
	
	GetParent()->SendMessage( WM_REDRAW_UI, 0, (LPARAM)m_hWnd );
}


LRESULT CTransparentBaseList::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
    // TODO: Add your specialized code here and/or call the base class
    if ( message == WM_TOUCH_BUTTONDOWN )
    {
        int nX = LOWORD( lParam );
        int nY = HIWORD( lParam );
        //屏幕坐标点
        if ( !m_bLBtnDown )
        {
			CPoint point( nX, nY );
			this->ScreenToClient( &point );
            OnLButtonDown( MK_LBUTTON, point );  
        }     
    }

    return CDlgChild::DefWindowProc(message, wParam, lParam);
}


LRESULT CTransparentBaseList::OnMouseWheels( WPARAM wParam, LPARAM lParam )
{
	short zDelta = (short) HIWORD(wParam);    
	int xPos = (int) LOWORD(lParam);    
	int yPos = (int) HIWORD(lParam);

	m_nTotalYOffset += zDelta/120 * 50;
	
	//CRect retList = GetFrame( m_pItemList );
	if ( m_nTotalYOffset > 0 )
	{
		m_nTotalYOffset = 0;  	
	}	
	if ( m_nTotalYOffset < m_rctDlg.Height() - m_rctList.Height() )
	{
		m_nTotalYOffset = m_rctDlg.Height() - m_rctList.Height();	
		if ( m_nTotalYOffset > 0 )
		{	
			m_nTotalYOffset = 0;
		}	
	}

	if ( m_pItemList != NULL )
	{
		IBaseItem* pItem = m_pItemList->GetItemData();
		if ( pItem != NULL )
		{
			pItem->SetOffset( CPoint(0, m_nTotalYOffset) );
		}
	}	

	GetParent()->SendMessage( WM_REDRAW_UI, 0, (LPARAM)m_hWnd );

	return NO_ERROR;
}


void CTransparentBaseList::SetImage( CString strImageFolder, BOOL bInvalidate /* = FALSE */ )
{	
	if ( "" == strImageFolder )
	{
		return;
	}
	String strFile = strImageFolder + "\\" + CTransparentBaseList::strTopLeft;
	m_pImgTopLeft = CSrcManage::GetImage( strFile.c_str() );
	strFile = strImageFolder + "\\" + CTransparentBaseList::strTopCenter;
	m_pImgTopCenter = CSrcManage::GetImage( strFile.c_str() );
	strFile = strImageFolder + "\\" + CTransparentBaseList::strTopRight;
	m_pImgTopRight = CSrcManage::GetImage( strFile.c_str() );
	strFile = strImageFolder + "\\" + CTransparentBaseList::strCenterLeft;
	m_pImgCenterLeft = CSrcManage::GetImage( strFile.c_str() );
	strFile = strImageFolder + "\\" + CTransparentBaseList::strCenterRight;
	m_pImgCenterRight = CSrcManage::GetImage( strFile.c_str() );
	strFile = strImageFolder + "\\" + CTransparentBaseList::strBottomLeft;
	m_pImgBottomLeft = CSrcManage::GetImage( strFile.c_str() );
	strFile = strImageFolder + "\\" + CTransparentBaseList::strBottomCenter;
	m_pImgBottomCenter = CSrcManage::GetImage( strFile.c_str() );
	strFile = strImageFolder + "\\" + CTransparentBaseList::strBottomRight;
	m_pImgBottomRight = CSrcManage::GetImage( strFile.c_str() );
	
	m_pImageBK = MosaicListImage();

	CTransparentBaseDlg::SetImage( m_pImageBK, bInvalidate );
}

Image* CTransparentBaseList::MosaicListImage()
{
	CRect cRect;
	this->GetWindowRect( &cRect );

	if ( m_pImageBK == NULL )
	{
		m_pImageBK = new Bitmap( cRect.Width(), cRect.Height() );
	}	
	
	Graphics* pGraphics = Graphics::FromImage( m_pImageBK );
	
	if ( m_pImgTopLeft != NULL && m_pImgTopCenter != NULL && m_pImgTopRight != NULL && m_pImgBottomRight != NULL
		 && m_pImgCenterLeft != NULL && m_pImgCenterRight != NULL && m_pImgBottomLeft != NULL && m_pImgBottomCenter != NULL
		 && m_pImgTopLeft->GetWidth() != 0 && m_pImgTopCenter->GetWidth() != 0 && m_pImgBottomCenter->GetWidth() != 0
		 && m_pImgCenterLeft->GetHeight() != 0 && m_pImgCenterRight->GetHeight() != 0 )
    {
        unsigned int nPosTopX = m_pImgTopLeft->GetWidth();
		
        unsigned int dwTopCenterWidth = 0;
		if ( cRect.Width() > m_pImgTopLeft->GetWidth() + m_pImgTopRight->GetWidth() )
		{
			dwTopCenterWidth = cRect.Width() - m_pImgTopLeft->GetWidth() - m_pImgTopRight->GetWidth();
		}
		
        // 左上
        pGraphics->DrawImage( m_pImgTopLeft, 0, 0, m_pImgTopLeft->GetWidth(), m_pImgTopLeft->GetHeight() );
        // 右上
        pGraphics->DrawImage( m_pImgTopRight, cRect.Width() - m_pImgTopRight->GetWidth(), 0, m_pImgTopRight->GetWidth(), m_pImgTopRight->GetHeight() );		
        // 中上
        for ( unsigned int nIndex = 0; nIndex < ( dwTopCenterWidth / m_pImgTopCenter->GetWidth() ); nIndex++ )
        {
            pGraphics->DrawImage( m_pImgTopCenter, nPosTopX, 0, m_pImgTopCenter->GetWidth(), m_pImgTopCenter->GetHeight() );
            nPosTopX += m_pImgTopCenter->GetWidth();
        }
        pGraphics->DrawImage( m_pImgTopCenter, nPosTopX, 0, dwTopCenterWidth % m_pImgTopCenter->GetWidth(), m_pImgTopCenter->GetHeight() );

		unsigned int nPosBottomX = m_pImgBottomLeft->GetWidth();
		int nPosBottomY = cRect.Height() - m_pImgBottomRight->GetHeight();
        unsigned int dwBottomCenterWidth = 0;
		if ( cRect.Width() > m_pImgBottomLeft->GetWidth() + m_pImgBottomRight->GetWidth() )
		{
			dwBottomCenterWidth = cRect.Width() - m_pImgBottomLeft->GetWidth() - m_pImgBottomRight->GetWidth();
		}
		//左下  
		pGraphics->DrawImage( m_pImgBottomLeft, 0, cRect.Height() - m_pImgBottomLeft->GetHeight(), m_pImgTopLeft->GetWidth(), m_pImgTopLeft->GetHeight() );
		//右下
		pGraphics->DrawImage( m_pImgBottomRight, cRect.Width() - m_pImgBottomRight->GetWidth(), nPosBottomY, m_pImgBottomRight->GetWidth(), m_pImgBottomRight->GetHeight() );
		//中下
		nPosBottomY = cRect.Height() - m_pImgBottomCenter->GetHeight();
		for ( nIndex = 0; nIndex < ( dwBottomCenterWidth / m_pImgBottomCenter->GetWidth() ); nIndex++ )
        {
            pGraphics->DrawImage( m_pImgBottomCenter, nPosBottomX, nPosBottomY, m_pImgBottomCenter->GetWidth(), m_pImgBottomCenter->GetHeight() );
            nPosBottomX += m_pImgBottomCenter->GetWidth();
        }
        pGraphics->DrawImage( m_pImgBottomCenter, nPosBottomX, nPosBottomY, dwBottomCenterWidth % m_pImgBottomCenter->GetWidth(), m_pImgBottomCenter->GetHeight() );

		//左边
		unsigned int nPosLeftY = m_pImgTopLeft->GetHeight();
		unsigned int dwLeftHeight = 0;
		if ( cRect.Height() > m_pImgTopLeft->GetHeight() + m_pImgBottomLeft->GetHeight() )
		{
			dwLeftHeight = cRect.Height() - m_pImgTopLeft->GetHeight() - m_pImgBottomLeft->GetHeight();
		}
		for ( nIndex = 0; nIndex < ( dwLeftHeight / m_pImgCenterLeft->GetHeight() ); nIndex++ )
        {
            pGraphics->DrawImage( m_pImgCenterLeft, 0, nPosLeftY, m_pImgCenterLeft->GetWidth(), m_pImgCenterLeft->GetHeight() );
            nPosLeftY += m_pImgCenterLeft->GetHeight();
        }
        pGraphics->DrawImage( m_pImgCenterLeft, 0, nPosLeftY, m_pImgCenterLeft->GetWidth(), dwLeftHeight % m_pImgCenterLeft->GetHeight() );

		//右边
		unsigned int nPosRightY = m_pImgTopRight->GetHeight();
		int nPosRightX = cRect.Width() - m_pImgCenterRight->GetWidth();
		unsigned int dwRightHeight = 0;
		if ( cRect.Height() > m_pImgTopRight->GetHeight() + m_pImgBottomRight->GetHeight() )
		{
			dwRightHeight = cRect.Height() - m_pImgTopRight->GetHeight() - m_pImgBottomRight->GetHeight();
		}
		for ( nIndex = 0; nIndex < ( dwRightHeight / m_pImgCenterRight->GetHeight() ); nIndex++ )
        {
            pGraphics->DrawImage( m_pImgCenterRight, nPosRightX, nPosRightY, m_pImgCenterRight->GetWidth(), m_pImgCenterRight->GetHeight() );
            nPosRightY += m_pImgCenterRight->GetHeight();
        }
        pGraphics->DrawImage( m_pImgCenterRight, nPosRightX, nPosRightY, m_pImgCenterRight->GetWidth(), dwRightHeight % m_pImgCenterRight->GetHeight() );

		SolidBrush cBrush( Color(213,228,250) );	
		pGraphics->FillRectangle( &cBrush, m_pImgCenterLeft->GetWidth(), m_pImgTopLeft->GetHeight(), (int)dwTopCenterWidth, (int)dwLeftHeight );
    }
	if( pGraphics != NULL )
	{
		delete pGraphics;
		pGraphics = NULL;
	}
	return m_pImageBK;
}

void  CTransparentBaseList::Clear(  )
{   
     m_pSelItem = NULL;
     m_pLastItem = NULL;  
}