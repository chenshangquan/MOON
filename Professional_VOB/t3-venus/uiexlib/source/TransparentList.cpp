/*****************************************************************************
ģ����      : ͨ�������б�
�ļ���      : transparentlist.cpp
����ļ�    : transparentlist.h
�ļ�ʵ�ֹ���: ͨ���б���ع��ܣ��б��һ������Ŀ����
����        : Ф��Ȼ
�汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
  ��  ��      �汾        �޸���      �޸�����
2012/04/01    1.0         Ф��Ȼ        ����
2012/12/05    2.0         Ф��Ȼ      ���ϵ���¼�ע�����ĸ������Ӧ
******************************************************************************/

#include "stdafx.h"
#include "list.h"
#include "algorithm.h"
#include "dragWindow.h"
#include "bitmapHelp.h"
#include "item.h"
#include "listfuncmanage.h"
#include "chartoPY.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransparentList

#define  TIMER_HANDLE_MOVING  100 
const CString CTransparentList::strTopLeft = "topleft.png";
const CString CTransparentList::strTopCenter = "topcenter.png";
const CString CTransparentList::strTopRight = "topright.png";
const CString CTransparentList::strCenterLeft = "centerleft.png";
const CString CTransparentList::strCenterRight = "centerright.png";
const CString CTransparentList::strBottomLeft = "bottomleft.png";
const CString CTransparentList::strBottomCenter = "bottomcenter.png";
const CString CTransparentList::strBottomRight = "bottomright.png";
const CString CTransparentList::strSliderTop = "slider_top.png";
const CString CTransparentList::strSliderMiddle = "slider_middle.png";
const CString CTransparentList::strSliderBottom = "slider_bottom.png";
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CTransparentList, CTransparentBaseWnd)
//{{AFX_MSG_MAP(CTransparentList)
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_MOUSEMOVE()
ON_WM_SHOWWINDOW()
ON_WM_SIZE()
ON_WM_TIMER()
ON_WM_KEYDOWN()
ON_MESSAGE( WM_REDRAW_UI, OnRedrawUI )
ON_MESSAGE( WM_MOUSEWHEEL, OnMouseWheels )
ON_MESSAGE( WM_LIST_UPDATEPROGRESS, OnUpdateProgress )
ON_MESSAGE( UI_LETTERINDEX_CLICK, OnLetterClick )
//}}AFX_MSG_MAP
ON_MESSAGE( WM_MOUSELEAVE, OnMouseLeave )
ON_MESSAGE( WM_MOUSEHOVER, OnMouseHover )
ON_MESSAGE( WM_BIND_LIST, OnBindList )
ON_MESSAGE( WM_ENABLE, OnEnableWindow )
END_MESSAGE_MAP()


BOOL CTransparentList::m_bInitList = FALSE;
/////////////////////////////////////////////////////////////////////////////
// CTransparentList message handlers
CTransparentList::CTransparentList(CString strName, CRect rcWnd, CWnd* pWnd, CString strUI, UINT nID, DWORD dStyle, DWORD dwExStyle) 
: IList( rcWnd.Width(), rcWnd.Height() ) , 
CTransparentBaseWnd( rcWnd, pWnd, dStyle, strUI, nID, dwExStyle ,255,FALSE,TRUE,strName )
{
	m_nTotalYOffset = 0;
	m_nTotalXOffset = 0;
	m_nMoveSpeed = 0;
	m_bLBtnDown = FALSE;
	m_bDragEnable = FALSE;
	m_bClickNoSel = FALSE;
	m_bClickFocus = TRUE;
	m_bMultiSel = FALSE;
    m_bAlwaysShowSlider = FALSE;
    m_bNeedSlider = FALSE;
	m_pSelItem = NULL;
	m_pLastItem = NULL;
	m_dwSelDataKey = -1;

	m_cBkgColor = Color( 213, 228, 250 );
	m_pImgTopLeft = NULL;
    m_pImgTopCenter = NULL;
    m_pImgTopRight = NULL;	
    m_pImgCenterLeft = NULL;
	m_pImgCenterRight = NULL;
    m_pImgBottomLeft = NULL;
    m_pImgBottomCenter = NULL;
	m_pImgBottomRight = NULL;

    m_pSlider = NULL;
    m_pSlider = new CTransparentListSlider( "", CRect(0,0,0,0), GetParent(), 0, WS_CHILD );
	
	if ( m_pSlider != NULL )
    {
        m_pSlider->SetListWnd( this );
    }

	m_pLetterIndex = NULL;

    if ( !m_bInitList )
    {
        InitList();
        m_bInitList = TRUE;
    }
	m_pMouseHoverItem = NULL;

	m_bRedrawBk = FALSE;
	m_bNeedOver = FALSE;
	m_bMouseTrack = TRUE;
}

CTransparentList::~CTransparentList()
{
	if ( NULL != m_pImageBK )
	{
		delete m_pImageBK;
		m_pImageBK = NULL;
	}

    Clear();

    if ( m_pSlider != NULL )
    {
        m_pSlider->DestroyWindow();
        delete m_pSlider;
        m_pSlider = NULL;
    }

    m_pImgTopLeft = NULL;
    m_pImgTopCenter = NULL;
    m_pImgTopRight = NULL;	
    m_pImgCenterLeft = NULL;
    m_pImgCenterRight = NULL;
    m_pImgBottomLeft = NULL;
    m_pImgBottomCenter = NULL;
	m_pImgBottomRight = NULL;

	m_pLetterIndex = NULL;
}

 
LRESULT CTransparentList::OnRedrawUI( WPARAM wParam, LPARAM lParam )
{  	 
	if ( IsWindowVisible() == FALSE )
	{
		return S_FALSE;
	}

	Graphics* pGraphics = (Graphics*)wParam;
	if ( pGraphics == NULL )
	{
        if ( GetParent() != NULL )
        {
		    GetParent()->SendMessage( WM_REDRAW_UI, wParam, lParam );
        }
		return S_OK;
	}

    HWND hGraphWnd = (HWND )lParam;
    CWnd * pGraphWnd = FromHandle(hGraphWnd);
    if ( hGraphWnd == NULL )
    {
        return S_FALSE;
    }
	
	DrawUI( pGraphics, /*GetParent()*/ pGraphWnd ); 

    if ( m_pSlider != NULL && m_bNeedSlider )
    {
        m_pSlider->SetListYOffset( -m_nTotalYOffset );
		m_pSlider->SendMessage( WM_REDRAW_UI, wParam, lParam );
	}
 
	return S_OK;
}

void CTransparentList::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_bLBtnDown = FALSE;
   
	//2013.5.3 yjj
	if( NULL != m_pMouseHoverItem )
	{
		IBaseItem* pItemLastHover = m_pMouseHoverItem->GetItemData();
		if( NULL != pItemLastHover )
			pItemLastHover->SetItemStatus(emItemStatusNormal);

		m_pMouseHoverItem = NULL;
	}


	if ( m_bClickFocus )
	{
		HWND hFocusWnd = ::GetFocus();
		if ( hFocusWnd != m_hWnd )
		{   
			this->SetFocus();
		}
	}

	if ( m_pItemList == NULL )
	{
		return;
	}

	if ( m_nMoveSpeed != 0 )
	{   		
		m_nMoveSpeed = 0;
		KillTimer(TIMER_HANDLE_MOVING);	
	} 

	//���ж��ѡ����ڵ��ʱ��ո���
	if ( m_bMultiSel )
	{
		ClearAllSel();
	}

	m_bLBtnDown = TRUE;
	m_ptMouseNow = point;
	m_ptMouseLast = point;
	m_ptMouseDown = point;

	IItemList* pSelList = NULL;
	IsClick( m_pItemList, point, &pSelList );

    //�������Disable��Ŀ��ֱ�ӷ���
    IItemList* pCheckList = pSelList;
    while ( pCheckList != NULL && pCheckList->GetParentItem() != NULL )
    {
        IBaseItem* pItem = pCheckList->GetItemData();
        if ( pItem == NULL )
        {
            return;
        }
        if ( pItem->GetItemStatus() == emItemStatusDisable )
        {   
            return;
	    }
        pCheckList = pCheckList->GetParentItem();
    }

	if ( m_bNeedOver && pSelList == m_pItemList )
	{
		//Tab�б��㵽�հ״�ֱ�ӷ���  ----2013.5.22   JYY
		return;
	}

	if ( m_pSelItem != NULL )
	{
		SetSelItemStatus( emItemStatusNormal );
				
		m_pSelItem = NULL;
		m_pLastItem = NULL;	        
    }
    m_dwSelDataKey = -1;   
    
	if ( pSelList != NULL )
	{
		m_pSelItem = pSelList;

		while( pSelList != NULL && pSelList->GetParentItem() != NULL )
		{
			IBaseItem* pBaseItem = pSelList->GetItemData();
            if ( pBaseItem == NULL )
            {
                return;
            }

            pBaseItem->OnItemDown();
			//pBaseItem->SetItemStatus( emItemStatusDown );
			
			if ( pBaseItem->GetUserData() != NULL )
			{
				IData* pData = const_cast<IData*>( pBaseItem->GetUserData() );
				m_dwSelDataKey = pData->GetDataKey();
			}

			if ( m_bNeedOver )		//2013.5.22  Tab�б�ֱ����ӦDown�¼�  ----JYY
			{
				if ( CButtonItem* pButtonItem = dynamic_cast<CButtonItem*>(pBaseItem) )
				{
					pButtonItem->SetItemStatus( emItemStatusSel );
					Clicked( nFlags, point );
					m_bLBtnDown = FALSE;
					return;
				}
			}

			//��������Ŀ����Ӧ�¼������ٽ�����Ŀ��Ϊѡ��
			if ( pBaseItem->GetFunc() != IBaseItem::strDefaultFunc )
			{
				break;
			}
			pSelList = pSelList->GetParentItem();
		}
			
		m_pLastItem = m_pSelItem;
	}

	SendMessage( WM_REDRAW_UI, 0, TRUE );
 
 	SetCapture();
//	CTransparentWnd::OnLButtonDown(nFlags, point);
}

void CTransparentList::OnLButtonUp(UINT nFlags, CPoint point) 
{
	//2013.5.3 jyy
	if( NULL != m_pMouseHoverItem )
	{
		IBaseItem* pItemLastHover = m_pMouseHoverItem->GetItemData();
		if( NULL != pItemLastHover )
			pItemLastHover->SetItemStatus(emItemStatusNormal);

		m_pMouseHoverItem = NULL;
	}

	if ( GetCapture() == this )
	{
		ReleaseCapture();
	} 
	 
	if ( !m_bLBtnDown )
	{   
		return;
	} 	
	
	m_bLBtnDown = FALSE;
			
	if ( m_pSelItem != NULL )
	{
        IBaseItem* pItem = m_pSelItem->GetItemData();
        if ( pItem == NULL )
        {   
            return;
        }

		if ( point == m_ptMouseDown )
		{
            SetSelItemStatus( emItemStatusSel );
			
            pItem->Click();


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

			//֪ͨ�ⲿ��ǰû��ѡ����
			PostMessage(WM_LST_UN_SELECT_ITEM);
			//��������������Umcweb
			GetParent()->PostMessage( WM_LST_UN_SELECT_ITEM, (WPARAM)GetSafeHwnd(), 0 );
		}
        
        //CPoint pt = TransChildPoint( m_pSelItem, point );
        //pItem->OnItemUp( pt );
	}

	if ( abs(m_ptMouseLast.y - m_ptMouseNow.y) > 4/*6*/ ) //���������˶�
    {
		m_nMoveSpeed = (m_ptMouseNow.y - m_ptMouseLast.y) / 3/*5*/;
		SetTimer( TIMER_HANDLE_MOVING, 20, NULL );	   
    }
    else
    {
        //û�й����˶�ʱ������slider
        if ( !m_bAlwaysShowSlider && m_bNeedSlider )
        {
            if ( m_pSlider != NULL && m_pSlider->IsWindowVisible() )
            {
                m_pSlider->ShowWindow( SW_HIDE );
            }
        }
    }
 
	
	if ( m_pSelItem == m_pItemList  )
    {
		m_dwSelDataKey = -1;
        //֪ͨ�ⲿ��ǰû��ѡ����
		PostMessage(WM_LST_UN_SELECT_ITEM);
		//��������������Umcweb
		GetParent()->PostMessage( WM_LST_UN_SELECT_ITEM, (WPARAM)GetSafeHwnd(), 0 );
    }

	SendMessage( WM_REDRAW_UI, 0, (LPARAM)m_hWnd );

//	CTransparentWnd::OnLButtonUp(nFlags, point);
}

void CTransparentList::SetSelItemStatus( EmItemStatus emStatus )
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


void CTransparentList::Clicked( UINT nFlags, CPoint point )
{
    if ( m_pSelItem == 0 )
    {
        return;
    }
    IBaseItem* pBaseItem = m_pSelItem->GetItemData();
    if ( pBaseItem == 0 )
    {
        return;
    }
    
    bool bFind = false;
    String strFunc = pBaseItem->GetFunc();
    IItemList* pList = m_pSelItem;
    while( pList != 0 && pList->GetParentItem() != 0 )
    {		
        pBaseItem = pList->GetItemData();
        strFunc = pBaseItem->GetFunc();
        if ( strFunc != IBaseItem::strDefaultFunc )
        {
            bFind = true;
            break;
        }
        pList = pList->GetParentItem();
    }
    if ( bFind == true )
    {
        CRect rcFrame = GetFrameInScreen( pList );
        Args_ClickItemInfo clickInfo( this, pList, rcFrame );
        
        CListFuncManage::GetSingletonPtr()->ExeFunc( strFunc, clickInfo );
    }	
    else
    {
        //LOGEVENT( "��Ŀ���������û���ҵ��κ�ע����¼�" );
	}
}

CRect CTransparentList::GetFrameInScreen( IItemList* pList )
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



void CTransparentList::Draw( IArgs* pArgs )
{
	IList::Draw( pArgs, -m_nTotalYOffset, m_rctDlg.Height() );
}

void CTransparentList::DrawUI( Graphics* pGraphics, CWnd* pParent )
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
	
	if ( NULL != m_pImageBK )
	{
		pGraph->DrawImage( m_pImageBK, 0, 0, rc.Width(), rc.Height() );
	} 

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

CRect CTransparentList::GetListRect()
{
	this->GetClientRect( m_rctDlg );

	return m_rctDlg;
}

void CTransparentList::OnMouseMove(UINT nFlags, CPoint point) 
{
	if ( !IsWindowEnabled() || !IsWindowVisible() )
	{
		return;
	}
	// TODO: Add your message handler code here and/or call default
	if ( m_bNeedOver && !m_bLBtnDown )
	{	
		if ( m_bMouseTrack )     //2013.5.21  ---�ҵ�������ͣ���Ĵ���,����л����򴰿�ʧȥ��꽹����over��������
		{
			TRACKMOUSEEVENT csTME;
			csTME.cbSize = sizeof (csTME);
			csTME.dwFlags = TME_LEAVE|TME_HOVER; //�����¼�
			csTME.hwndTrack = GetSafeHwnd() ;// ָ��Ҫ ׷�� �Ĵ��� 
			csTME.dwHoverTime = 10;  // ����ڰ�ť��ͣ������ 10ms ������Ϊ״̬Ϊ HOVER
			::_TrackMouseEvent (&csTME); // ���� Windows �� WM_MOUSELEAVE�¼�֧�� 
			
			m_bMouseTrack = FALSE;   // ���Ѿ� ׷�� ����ֹͣ ׷�� 
		}
		else
		{
			ListMouseMove(nFlags,point);
		}
	}
    
	if ( nFlags != MK_LBUTTON || !m_bLBtnDown  )
    {   
		return;
    }
	
	m_ptMouseLast = m_ptMouseNow;
	m_ptMouseNow = point;

	if( m_ptMouseNow == m_ptMouseLast )
	{
		return;
	}

    BOOL bCanMove = ListMove();
    //���ܻ������б�����������
    if ( !bCanMove )
    {
        return;
    }

	//�϶������ѡ����
	if ( m_pSelItem != NULL )
	{
		SetSelItemStatus( emItemStatusNormal );
		m_pSelItem = NULL;
		m_dwSelDataKey = -1;     
		
		//֪ͨ�ⲿ��ǰû��ѡ����
		PostMessage(WM_LST_UN_SELECT_ITEM);
		GetParent()->PostMessage( WM_LST_UN_SELECT_ITEM, (WPARAM)GetSafeHwnd(), 0 );
	}	
		
	//�Ƴ��Ի�����ק��ʼ		
	if ( m_bDragEnable && m_pLastItem != NULL && IsReadyForDrag() )
	{    				
		IItemList* pDragItem = m_pLastItem; /*m_pSelItem;*/
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

	SendMessage( WM_REDRAW_UI, 0, (LPARAM)m_hWnd );
//	CTransparentWnd::OnMouseMove(nFlags, point);
}

void CTransparentList::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if ( !IsWindowEnabled() || !IsWindowVisible() )
	{
		return;
	}

	if (( nChar == VK_UP )||( nChar == VK_DOWN ))
	{
		ListKeyDown(nChar, nRepCnt,nFlags);
	}
	else if ( nChar == VK_RETURN  )
	{
		onReturnKey();
	}
}

void CTransparentList::ListKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	return ;
}

void CTransparentList::onReturnKey()
{
	return ;
}

void CTransparentList::ListMouseMove(UINT nFlags, CPoint point)
{				
	//�ж�point���ĸ�Item��,��Ϊѡ��״̬�򲻽���over����
	IItemList* item = NULL;
	bool bClick = IsClick( m_pItemList, point, &item , FALSE );
	if ( NULL != item && m_pMouseHoverItem != item)
	{			
		if( NULL != m_pMouseHoverItem )
		{
			IBaseItem* pItemLastHover = m_pMouseHoverItem->GetItemData();
			if ( CTextItem* pTextItem = dynamic_cast<CTextItem*>(pItemLastHover) )
			{
				IItemList* pParentItem = m_pMouseHoverItem->GetParentItem();
				if ( pParentItem != NULL )
				{
					pItemLastHover = pParentItem->GetItemData();
				}
			}
			if( NULL != pItemLastHover )
				pItemLastHover->SetItemStatus(emItemStatusNormal);
			m_pMouseHoverItem = NULL;
		}

		IBaseItem* pItem = item->GetItemData();
	
		if ( CTextItem* pTextItem = dynamic_cast<CTextItem*>(pItem) )
		{
			pItem = item->GetParentItem()->GetItemData();
		}

		if ( pItem->GetItemStatus() != emItemStatusSel )
		{		
			m_pMouseHoverItem = item;
			pItem->SetItemStatus( emItemStatusOver );
		} 
		SendMessage( WM_REDRAW_UI, 0, (LPARAM)m_hWnd );
	}
}

BOOL CTransparentList::ListMove()
{
	if ( m_pLastItem == NULL )
	{
		return FALSE;
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
		return FALSE;
	}
	
	m_nTotalYOffset += ( m_ptMouseNow.y - m_ptMouseLast.y );
	//m_nTotalXOffset += ( m_ptMouseNow.x - m_ptMouseLast.x );

	//CRect retList = GetFrame( pSelList );

    CheckYOffset();
    
    IBaseItem* pItem = pSelList->GetItemData();
    if ( pItem != NULL )
    {
        pItem->SetOffset( CPoint(0, m_nTotalYOffset) );
    }
    
    if ( !m_bAlwaysShowSlider && m_bNeedSlider )
    {
        if ( m_pSlider != NULL && !m_pSlider->IsWindowVisible() )
        {
            m_pSlider->ShowWindow( SW_SHOW );
        }
    }

    return TRUE;
}

void CTransparentList::ListAutoMove()
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
	
    CheckYOffset();  
        
    IBaseItem* pItem = pSelList->GetItemData();
    if ( pItem != NULL )
    {
        pItem->SetOffset( CPoint(0, m_nTotalYOffset) );
    }
    
    if ( 0 == m_nMoveSpeed )
    { 
        KillTimer(TIMER_HANDLE_MOVING);  

        //û�й����˶�ʱ������slider
        if ( !m_bAlwaysShowSlider && m_bNeedSlider )
        {
            if ( m_pSlider != NULL && m_pSlider->IsWindowVisible() )
            {
                m_pSlider->ShowWindow( SW_HIDE );
            }
        }
    } 
    
    SendMessage( WM_REDRAW_UI, 0, (LPARAM)m_hWnd );
}


CPoint CTransparentList::TransChildPoint( IItemList* pList, CPoint point )
{
    CPoint pt(0, 0);
    if ( pList != NULL && pList->GetParentItem() != NULL )
    {
        CRect rcParent;

        IItemList* pParentList = pList->GetParentItem();
        IBaseItem* pParentItem = pParentList->GetItemData();
        if ( pParentItem != 0 )
        {
            rcParent = pParentItem->GetItemRect();			
        }
          
        IBaseItem* pBaseItem = pList->GetItemData();
        if ( pBaseItem != NULL )
        {
            CRect rcRect = pBaseItem->GetItemRect();		
            pt = TransPoint( rcParent.TopLeft(), rcRect.TopLeft(), point );
	        pt -= pBaseItem->GetOffset();
        }
    }
    return pt;
}

void CTransparentList::OnSize(UINT nType, int cx, int cy) 
{
	CTransparentBaseWnd::OnSize(nType, cx, cy);
    // TODO: Add your message handler code here	
	
	CRect rc;
//	this->GetClientRect( rc );
	this->GetWindowRect(rc);
	//�ײ��߿�-2����
	int nHeight = 0;
	if ( NULL == m_pImgTopLeft )
	{
		nHeight = rc.Height();
	}
	else
	{
		nHeight = rc.Height() - 2;
	}
	SetListSize( rc.Width(), nHeight );   //�����б�ˮƽ��2px�߶�  by ldy 130424
	
    //���û�����Ĭ��λ��
    CRect rectDlg = rc;
    GetParent()->ScreenToClient( rectDlg );
    if ( m_pSlider != NULL )
    {
        m_pSlider->SetListWnd( this );        
        
        CRect rectSlider = rectDlg;
        rectSlider.right = rectDlg.right - 5;
        rectSlider.left = rectSlider.right - 18;
        m_pSlider->MoveWindow( &rectSlider );   
    }

	if ( m_bRedrawBk )
	{
		if ( m_pImageBK != NULL )
		{
			delete m_pImageBK;
			m_pImageBK = NULL;
		}
		m_pImageBK = MosaicListImage();
		SendMessage( WM_REDRAW_UI, 0, 0 );
	}
}

void CTransparentList::OnTimer(UINT nIDEvent) 
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
	
	CTransparentBaseWnd::OnTimer(nIDEvent);
}


void CTransparentList::SetDragEnable( BOOL bDrag )
{
	m_bDragEnable = bDrag;
}

void CTransparentList::SetClickNoSel( BOOL bSel )
{
	m_bClickNoSel = bSel;
}

void CTransparentList::SetClickFocus( BOOL bFocus )
{
	m_bClickFocus = bFocus;
}

void CTransparentList::SetMultiSel( BOOL bMulti )
{
	m_bMultiSel = bMulti;
}

/*=============================================================================
�� �� ��:ResetSelItem
��    ��:����ѡ����
��    ��:bResetOffset  �Ƿ�����λ��
ע    ��:�б�ˢ�º�����ô˺���������ԭ��ѡ�������ʧ
�� �� ֵ:��
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���   �޸�����
2012/04/01  1.0     Ф��Ȼ     ����
=============================================================================*/
void CTransparentList::ResetSelItem( BOOL bResetOffset )
{
	if ( m_nMoveSpeed != 0 )
	{   		
		m_nMoveSpeed = 0;
		KillTimer(TIMER_HANDLE_MOVING);	
	} 

	int nItemCount = m_pItemList->GetItemCount();
    if ( nItemCount <= 0)
    {
		m_nTotalYOffset = 0;
    }
 
	
	m_rctList = GetFrame( m_pItemList );

    //���û���������
    GetListRect();
    if ( m_pSlider != NULL )
    {
        if ( m_rctList.Height() <= m_rctDlg.Height() )
        {
            m_bNeedSlider = FALSE;
            m_pSlider->ShowWindow( SW_HIDE );
        }
        else
        {
            m_bNeedSlider = TRUE;
            m_pSlider->SetListTotalHeight( m_rctList.Height() );

            BOOL bVis = GetStyle() & WS_VISIBLE;
            if ( m_bAlwaysShowSlider && bVis )
            {
                m_pSlider->ShowWindow( SW_SHOW );
            }
            else
            {
                m_pSlider->ShowWindow( SW_HIDE );
            }
        }       
    }
	
 
	//��λ������һ�Σ���ֹˢ�º������ʾ��Ŀ���������
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

					SendMessage( WM_REDRAW_UI, 0, (LPARAM)m_hWnd );
					return;
				}
			}		
		}
	}

}

/*=============================================================================
�� �� ��:SetSelItem
��    ��:�����б�ѡ����Ŀ
��    ��:dwDataKey  ѡ����Ŀ��Key  
ע    ��:
�� �� ֵ:��
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���   �޸�����
2012/04/01  1.0     Ф��Ȼ     ����
=============================================================================*/
void CTransparentList::SetSelItem( unsigned long dwDataKey, BOOL bResetOffset )
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
	ResetSelItem( bResetOffset );
}

IBaseItem* CTransparentList::GetSelItem()
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


int CTransparentList::GetOffsetHeight( int nIndex )
{
	CRect rcResult = CRect(0,0,0,0);
	int nCounts = nIndex ;
	
	//�������������Ŀ��С��һ������Ҫ�������
	if ( !m_bItemSizeSame )
	{
		for ( int i = 0; i < nCounts; i++ )
		{
			IItemList* pSub = m_pItemList->GetItemByIndex( i );
			if ( pSub != 0 )
			{
				IBaseItem* pBaseItem = pSub->GetItemData();
				if ( pBaseItem != 0 )
				{
					CRect rcItem = pBaseItem->GetItemRect();
					rcItem.NormalizeRect();
					rcResult.UnionRect( rcItem, rcResult );
				}			
			}
		}
	}
	else
	{	//������Ŀ��С��һ��
		if ( nCounts > 0 )
		{
			IBaseItem* pBaseItem = m_pItemList->GetItemData();
			
			IItemList* pSub = m_pItemList->GetItemByIndex( 0 );
			if ( pSub != 0 )
			{
				IBaseItem* pSubItem = pSub->GetItemData();
				if ( pSubItem != 0 )
				{
					CRect rcItem = pSubItem->GetItemRect();
					rcItem.NormalizeRect();
					if ( pBaseItem->GetLayoutAlgorithm() == IAlgorithm::strVert )
					{
						rcResult.top = rcItem.top;
						rcResult.left = rcItem.left;
						rcResult.right = rcItem.right;
						rcResult.bottom = rcItem.top + ( rcItem.Height() + CLayoutAlgorithm_Vert::nYSpace ) * nCounts;
					}					
				}				
			}
		}
	}
	
	return rcResult.Height();
}


BOOL CTransparentList::IsReadyForDrag()
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
�� �� ��:SetYOffset
��    ��:�����б�ƫ����
��    ��:nOffset ƫ��λ��  
ע    ��:
�� �� ֵ:��
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���   �޸�����
2012/04/01  1.0     Ф��Ȼ     ����
=============================================================================*/
void CTransparentList::SetYOffset( int nOffset )
{
	if ( m_nMoveSpeed != 0 )
	{   		
		m_nMoveSpeed = 0;
		KillTimer(TIMER_HANDLE_MOVING);	
	}

	m_nTotalYOffset = -nOffset;

	//CRect retList = GetFrame( m_pItemList );
	
    CheckYOffset();
        
    IBaseItem* pItem = m_pItemList->GetItemData();
    if ( pItem != NULL )
    {
        pItem->SetOffset( CPoint(0, m_nTotalYOffset) );
    }
    
    SendMessage( WM_REDRAW_UI, 0, (LPARAM)m_hWnd );

}


int CTransparentList::GetYOffset()
{
	return -m_nTotalYOffset;
}

void CTransparentList::CheckYOffset()
{
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
}


/*=============================================================================
�� �� ��:SetBottomOffset
��    ��:�����б��ײ�λ��
��    ��:
ע    ��:
�� �� ֵ:��
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���   �޸�����
2012/04/01  1.0     Ф��Ȼ     ����
=============================================================================*/
void CTransparentList::SetBottomOffset()
{
	if ( m_pItemList == NULL )
	{
		return;
	}

	this->GetClientRect( m_rctDlg );

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
	
	SendMessage( WM_REDRAW_UI, 0, (LPARAM)m_hWnd );
}



LRESULT CTransparentList::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
    // TODO: Add your specialized code here and/or call the base class
    /*WM_TOUCH_BUTTONDOWN����λ�ò�׼��������Ӧ
    if ( message == WM_TOUCH_BUTTONDOWN )
    {
        int nX = LOWORD( lParam );
        int nY = HIWORD( lParam );
        //��Ļ�����
        if ( !m_bLBtnDown )
        {
			CPoint point( nX, nY );
			this->ScreenToClient( &point );
            OnLButtonDown( MK_LBUTTON, point );  
        }     
    }*/
    //ͨ��win7 Dll��ע�ᴰ����ӦWM_TOUCH �����¼� -2014.5.7 xcr
    if ( message == WM_TOUCH )
    {
        if ( m_bLBtnDown )
        {
            return CTransparentBaseWnd::DefWindowProc(message, wParam, lParam);
        }
        m_bLBtnDown = TRUE;
        
        WINSDK_GetTouchInputPoint _WINSDK_GetTouchInputPoint;
        
        UINT cInputs = LOWORD(wParam);
        POINT ptInput;
        
        HINSTANCE hInstLibrary = LoadLibrary("windowsexsdk.dll");
        if (hInstLibrary != NULL)
        {
            _WINSDK_GetTouchInputPoint = (WINSDK_GetTouchInputPoint)GetProcAddress( hInstLibrary, "WINSDK_GetTouchInputPoint" );
            if ( _WINSDK_GetTouchInputPoint != NULL )
            {
                _WINSDK_GetTouchInputPoint( lParam, cInputs, ptInput );
                
                this->ScreenToClient( &ptInput );
                
                OnLButtonDown( MK_LBUTTON, ptInput );
            }
            FreeLibrary( hInstLibrary );
        }    
    }
	
    return CTransparentBaseWnd::DefWindowProc(message, wParam, lParam);
}


LRESULT CTransparentList::OnMouseWheels( WPARAM wParam, LPARAM lParam )
{
	short zDelta = (short) HIWORD(wParam);    
	int xPos = (int) LOWORD(lParam);    
	int yPos = (int) HIWORD(lParam);

	m_nTotalYOffset += zDelta/120 * 50;
	
    CheckYOffset();
    
    if ( m_pItemList != NULL )
    {
        IBaseItem* pItem = m_pItemList->GetItemData();
        if ( pItem != NULL )
        {
            pItem->SetOffset( CPoint(0, m_nTotalYOffset) );
        }
    }	
    
    SendMessage( WM_REDRAW_UI, 0, 0 );
    
	return NO_ERROR;
}


LRESULT CTransparentList::OnUpdateProgress( WPARAM wParam, LPARAM lParam )
{
    CPoint pointOffset = *(CPoint*)wParam;
    
    //�����������������б��ƶ������෴�����-=
    if ( pointOffset.y != 0 )
    {
        m_nTotalYOffset -= pointOffset.y;
        SetYOffset( -m_nTotalYOffset );
    }
    return NO_ERROR;
}

void CTransparentList::SetSliderRect( CRect rectSlider )
{
    if ( m_pSlider != NULL )
    {
        m_pSlider->MoveWindow( &rectSlider );
		m_pSlider->SetWindowPos( NULL, 0,0,0,0, SWP_NOMOVE|SWP_NOSIZE);
    }
}


void CTransparentList::SetImage( UINT nImgTopLeft, UINT nImgTopCenter, UINT nImgTopRight, 
						 UINT nImgCenterLeft, UINT nImgCenterRight, UINT nImgBottomLeft, UINT nImgBottomCenter,
						 UINT nImgBottomRight, UINT nImageBK, const CString& strImgType)
{
	m_pImgTopLeft = CSrcManage::GetImage( nImgTopLeft, strImgType );
	m_pImgTopCenter = CSrcManage::GetImage( nImgTopCenter, strImgType );
	m_pImgTopRight = CSrcManage::GetImage( nImgTopRight, strImgType );
	m_pImgCenterLeft = CSrcManage::GetImage( nImgCenterLeft, strImgType );
	m_pImgCenterRight = CSrcManage::GetImage( nImgCenterRight, strImgType );
	m_pImgBottomLeft = CSrcManage::GetImage( nImgBottomLeft, strImgType );
	m_pImgBottomCenter = CSrcManage::GetImage( nImgBottomCenter, strImgType );
	m_pImgBottomRight = CSrcManage::GetImage( nImgBottomRight, strImgType );

	m_pImageBK = MosaicListImage();
	
	//�ײ��߿�-2����
	if ( NULL != m_pImgTopLeft )
	{
		CRect rc;
		this->GetWindowRect(rc);
		int nHeight = rc.Height() - 2;
		SetListSize( rc.Width(), nHeight );
	}

	CTransparentBaseWnd::SetImage( m_pImageBK );
}

void CTransparentList::SetSliderImage( UINT nImgNormalUp, UINT nImgNormalCenter, UINT nImgNormalDown, UINT nImgHilightUp, UINT nImgHilightCenter, 
        UINT nImgHilightDown, UINT nImgBkUp, UINT nImgBkCenter, UINT nImgBkDown,  const CString& strImgType )
{
    if ( m_pSlider != NULL )
    {
        m_pSlider->SetImage( nImgNormalUp, nImgNormalCenter, nImgNormalDown, nImgHilightUp, 
            nImgHilightCenter, nImgHilightDown, nImgBkUp, nImgBkCenter, nImgBkDown, strImgType );
    }
}

void CTransparentList::SetSliderImage( CString strImageFolder )
{
    if ( m_pSlider != NULL )
    {
        m_pSlider->SetImage( strImageFolder );
    }
}

void CTransparentList::SetImage( CString strImageFolder , BOOL bInvalidate /* = FALSE */,EmImgCompType emImgType /*= emImgTypeMasic*/)
{	
	if ( "" == strImageFolder )
	{
		return;
	}

	if ( -1 != strImageFolder.Find(".png")  )
	{
		emImgType = emImgCompSingle;
	}

    if ( emImgType == emImgCompMasic )
    {
		String strFile = strImageFolder + "\\" + CTransparentList::strTopLeft;
		m_pImgTopLeft = CSrcManage::GetImage( strFile.c_str() );
		strFile = strImageFolder + "\\" + CTransparentList::strTopCenter;
		m_pImgTopCenter = CSrcManage::GetImage( strFile.c_str() );
		strFile = strImageFolder + "\\" + CTransparentList::strTopRight;
		m_pImgTopRight = CSrcManage::GetImage( strFile.c_str() );
		strFile = strImageFolder + "\\" + CTransparentList::strCenterLeft;
		m_pImgCenterLeft = CSrcManage::GetImage( strFile.c_str() );
		strFile = strImageFolder + "\\" + CTransparentList::strCenterRight;
		m_pImgCenterRight = CSrcManage::GetImage( strFile.c_str() );
		strFile = strImageFolder + "\\" + CTransparentList::strBottomLeft;
		m_pImgBottomLeft = CSrcManage::GetImage( strFile.c_str() );
		strFile = strImageFolder + "\\" + CTransparentList::strBottomCenter;
		m_pImgBottomCenter = CSrcManage::GetImage( strFile.c_str() );
		strFile = strImageFolder + "\\" + CTransparentList::strBottomRight;
		m_pImgBottomRight = CSrcManage::GetImage( strFile.c_str() );
		
		m_pImageBK = MosaicListImage();

        //����sliderͼƬ
        CString cstrSliderTop = strImageFolder + "\\" + CTransparentList::strSliderTop;
        CString cstrSliderMiddle = strImageFolder + "\\" + CTransparentList::strSliderMiddle;
        CString cstrSliderBottom = strImageFolder + "\\" + CTransparentList::strSliderBottom;
        if ( m_pSlider != NULL )
        {
            m_pSlider->SetImage( cstrSliderTop, cstrSliderMiddle, cstrSliderBottom );
        }
    }
	else
	{ 
		m_pImageBK = CSrcManage::GetImage( strImageFolder );
	}
	
	CTransparentBaseWnd::SetImage( m_pImageBK, bInvalidate );  
}

/*=============================================================================
�� �� ��:MosaicListImage
��    ��:�ϳɱ���ͼƬ
��    ��:
ע    ��:
�� �� ֵ:��
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���   �޸�����
2012/04/01  1.0     Ф��Ȼ     ����
=============================================================================*/
Image* CTransparentList::MosaicListImage()
{
    if ( m_pImageBK != NULL )
    {
        return m_pImageBK;
    }

	CRect cRect;
	this->GetWindowRect( &cRect );

	if ( m_pImageBK == NULL )
	{
		m_pImageBK = new Bitmap( cRect.Width(), cRect.Height() );
	}	
	//m_pImage = new Bitmap( cRect.Width(), cRect.Height() );
	
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
		
        // ����
        pGraphics->DrawImage( m_pImgTopLeft, 0, 0, m_pImgTopLeft->GetWidth(), m_pImgTopLeft->GetHeight() );
        // ����
        pGraphics->DrawImage( m_pImgTopRight, cRect.Width() - m_pImgTopRight->GetWidth(), 0, m_pImgTopRight->GetWidth(), m_pImgTopRight->GetHeight() );		
        // ����
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
		//����  
		pGraphics->DrawImage( m_pImgBottomLeft, 0, cRect.Height() - m_pImgBottomLeft->GetHeight(), m_pImgTopLeft->GetWidth(), m_pImgTopLeft->GetHeight() );
		//����
		pGraphics->DrawImage( m_pImgBottomRight, cRect.Width() - m_pImgBottomRight->GetWidth(), nPosBottomY, m_pImgBottomRight->GetWidth(), m_pImgBottomRight->GetHeight() );
		//����
		nPosBottomY = cRect.Height() - m_pImgBottomCenter->GetHeight();
		for ( nIndex = 0; nIndex < ( dwBottomCenterWidth / m_pImgBottomCenter->GetWidth() ); nIndex++ )
        {
            pGraphics->DrawImage( m_pImgBottomCenter, nPosBottomX, nPosBottomY, m_pImgBottomCenter->GetWidth(), m_pImgBottomCenter->GetHeight() );
            nPosBottomX += m_pImgBottomCenter->GetWidth();
        }
        pGraphics->DrawImage( m_pImgBottomCenter, nPosBottomX, nPosBottomY, dwBottomCenterWidth % m_pImgBottomCenter->GetWidth(), m_pImgBottomCenter->GetHeight() );

		//���
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

		//�ұ�
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

		SolidBrush cBrush ( m_cBkgColor );		
		pGraphics->FillRectangle( &cBrush, m_pImgCenterLeft->GetWidth(), m_pImgTopLeft->GetHeight(), (int)dwTopCenterWidth, (int)dwLeftHeight );
    }

	if( pGraphics != NULL )
	{
		delete pGraphics;
		pGraphics = NULL;
	}

	return m_pImageBK;
}

void CTransparentList::SetBkgColor( Color colorBkg, BOOL bInvalidate /* = FALSE */ )
{
	m_cBkgColor = colorBkg;
	
	if ( bInvalidate )
	{
		NOTIF_PARENT_WND
	}
}


void  CTransparentList::Clear()
{   
	m_pSelItem = NULL;
	m_pLastItem = NULL;  
	m_pMouseHoverItem = NULL;
    if ( m_pItemList != NULL )
    {
        m_pItemList->DeleteAllItem();
    }
}


void CTransparentList::ClearAllSel()
{
	int nCount = m_pItemList->GetItemCount();
	
	for ( int i = 0; i < nCount; i++ )
	{
		IItemList* pSubList = m_pItemList->GetItemByIndex( i );
		if ( pSubList != NULL )
		{
			IBaseItem* pItem = pSubList->GetItemData();
			if ( pItem != NULL )
			{
				if ( pItem->GetItemStatus() == emItemStatusSel )
				{
					pItem->SetItemStatus( emItemStatusNormal );
				}
			}
		}
	}
}


/*=============================================================================
�� �� ��:OnLetterClick
��    ��:��Ӧ��ĸ�����¼�
��    ��:
ע    ��:ͨ��ѡ�е���ĸʹ�б�������Ӧλ�ã������LetterIndex�ſ���Ӧ��
�� �� ֵ:��
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���   �޸�����
2012/12/05  1.0     Ф��Ȼ     ����
=============================================================================*/
LRESULT CTransparentList::OnLetterClick( WPARAM wParam, LPARAM lParam )
{   
	int nLetterIndex = (int)wParam;
	CString strIndex;
	nLetterIndex = 'A' + nLetterIndex;
	strIndex.Format( "%c", (char)nLetterIndex );
	int nYOffset = 0;
	int nItemCount = m_pItemList->GetItemCount();

	//�����Ŀ����ʱ�������ĸ�Ῠ������ ��ʹ�ö��ַ� by yjj
	int swLowIndex = 0;
	int swHighIndex = nItemCount;
	int swMidIndex = 0;   //�õ�ǰ���������ϡ��½�ĳ�ֵ 

	while( swLowIndex < swHighIndex )
	{   
		int nMidIndex = swMidIndex;
		//��ǰ��������R[low..high]�ǿ� 
		swMidIndex =( swLowIndex + swHighIndex )/2; 
		if ( nMidIndex == swMidIndex )
		{
			break;
		}

		IItemList* pList = m_pItemList->GetItemByIndex( swMidIndex );
		if ( pList == NULL )
		{
			break;
		}	 
		IItemList* pSubList = pList->GetItemByIndex( 0 );
		if ( pSubList == NULL )
		{
			break;
		}

		IBaseItem* pItem = pSubList->GetItemData();
		if ( CTextItem* pTextItem = dynamic_cast<CTextItem*>(pItem) )
		{
			CString cStr = "";
			CString strLetter = "";
			cStr.Format( "%s", pTextItem->GetText().c_str() );
            CCharToPY::GetFirstLetter( cStr, strLetter ); 

			int nRe = strIndex.Compare( strLetter );
			if(  nRe == 0 )  
			{                                            
				break;                                   
			} 
			else if ( nRe < 0 )
			{   
				swHighIndex = swMidIndex;  //��ǰ��������R[low..mid]  
			}
			else
			{   
				swLowIndex = swMidIndex + 1;//��ǰ��������R[mid..heith] 
			}						 
		}               
	} 

	//swLowIndex��swHighIndex���ʱ����swMidIndex�Ƚ�
	if ( swLowIndex == swHighIndex )
	{
		if ( swMidIndex < swHighIndex )
		{
			swHighIndex = swMidIndex;
		}
		else
		{
			swLowIndex = swMidIndex;
		}
	}

	//ȡswLowIndex��swHighIndex�е�һ����strIndex��ķ���
	if ( swLowIndex > swHighIndex )
	{
		IItemList* pList = m_pItemList->GetItemByIndex( swHighIndex );
		if ( pList == NULL )
		{
			return S_OK;
		}		
		IItemList* pSubList = pList->GetItemByIndex( 0 );
		if ( pSubList == NULL )
		{
			return S_OK;
		}		
		IBaseItem* pItem = pSubList->GetItemData();
		if ( CTextItem* pTextItem = dynamic_cast<CTextItem*>(pItem) )
		{
			CString cStr = "";
			CString strLetter = "";
			cStr.Format( "%s", pTextItem->GetText().c_str() );
			CCharToPY::GetFirstLetter( cStr, strLetter ); 

			int nRe = strIndex.Compare( strLetter );
			if( nRe > 0 )		 
			{
				swMidIndex = swLowIndex;
			}
			else
			{
				swMidIndex = swHighIndex;
			}
		}		
	}

	nYOffset = GetOffsetHeight( swMidIndex );
	 
	SetYOffset( nYOffset );

	return S_OK;
}



void CTransparentList::InitList()
{
    //ע�������㷨
    REG_ALGORITHM( IAlgorithm::strVert, CLayoutAlgorithm_Vert )
    REG_ALGORITHM( IAlgorithm::strVertNoSplit, CLayoutAlgorithm_VertNoSplit )
    REG_ALGORITHM( IAlgorithm::strHori, CLayoutAlgorithm_Hori )
    REG_ALGORITHM( IAlgorithm::strCharacter, CSortAlgorithm_Char )
    REG_ALGORITHM( IAlgorithm::strNormalItem, CLayoutAlgorithm_NormalItem )
    REG_ALGORITHM( IAlgorithm::strAddrGroupItem, CLayoutAlgorithm_AddrGroupItem )
    REG_ALGORITHM( IAlgorithm::strHoriConfLst, CLayoutAlgorithm_HoriConfLst )	
    REG_ALGORITHM( IAlgorithm::strTextOnly, CLayoutAlgorithm_TextOnly )
    REG_ALGORITHM( IAlgorithm::strDoubleColumn, CLayoutAlgorithm_DoubleColumn )
    REG_ALGORITHM( IAlgorithm::strTPadMainMenu, CLayoutAlgorithm_TPadMainMenu )
    REG_ALGORITHM( IAlgorithm::strTextBottom, CLayoutAlgorithm_TextBottom )
    REG_ALGORITHM( IAlgorithm::strWifiItem, CLayoutAlgorithm_WifiItem )
    //REG_ALGORITHM( IAlgorithm::strTvwView, CLayoutAlgorithm_TvwView )
    //REG_ALGORITHM( IAlgorithm::strTvwItem, CLayoutAlgorithm_TvwItem )
    REG_ALGORITHM( IAlgorithm::strBoardView, CLayoutAlgorithm_BoardView )
    REG_ALGORITHM( IAlgorithm::strBoardItem, CLayoutAlgorithm_BoardItem )
	REG_ALGORITHM( IAlgorithm::strTPadIpList, CLayoutAlgorithm_TPadIPList )
    REG_ALGORITHM( IAlgorithm::strMultiColumn, CLayoutAlgorithm_MultiColumn )
    REG_ALGORITHM( IAlgorithm::strFileManagerItem, CLayoutAlgorithm_FileManagerItem )//�ļ�����																					
	REG_ALGORITHM( IAlgorithm::strPreTextBottom, CLayoutAlgorithm_PreTextBottom)//Ԥ��λ�б�
}

void CTransparentList::OnShowWindow(BOOL bShow, UINT nStatus) 
{   
	if ( NULL != m_pSlider )
	{
		if ( bShow )
		{
			if ( m_rctList.Height() > m_rctDlg.Height() )
			{
				m_bNeedSlider = TRUE;
				m_pSlider->SetListTotalHeight( m_rctList.Height() );
				if ( m_bAlwaysShowSlider )
				{
					m_pSlider->ShowWindow( SW_SHOW );
				}
			}
		}
		else
		{            
			m_pSlider->ShowWindow(SW_HIDE);
		}
	}

    CTransparentBaseWnd::OnShowWindow( bShow, nStatus ); 
}

LRESULT CTransparentList::OnMouseLeave( WPARAM wParam, LPARAM lParam )
{	
	if( NULL != m_pMouseHoverItem )
	{
		IBaseItem* pItemLastHover = m_pMouseHoverItem->GetItemData();
		if ( CTextItem* pTextItem = dynamic_cast<CTextItem*>(pItemLastHover) )
		{
			IItemList* pParentItem = m_pMouseHoverItem->GetParentItem();
			if ( pParentItem != NULL )
			{
				pItemLastHover = pParentItem->GetItemData();
			}
		}
		if( NULL != pItemLastHover )
			pItemLastHover->SetItemStatus(emItemStatusNormal);
		
		m_pMouseHoverItem = NULL;
		
	}
	SendMessage( WM_REDRAW_UI, 0, (LPARAM)m_hWnd );
	m_bMouseTrack = TRUE;
	return S_OK;
}

LRESULT CTransparentList::OnMouseHover( WPARAM wParam, LPARAM lParam )
{	
	m_bMouseTrack = FALSE;
	return S_OK;
}

LRESULT CTransparentList::OnBindList( WPARAM wParam, LPARAM lParam )
{
	m_pLetterIndex = (CLetterIndex*)lParam;
	return S_OK;
}

LRESULT CTransparentList::OnEnableWindow( WPARAM wParam, LPARAM lParam )
{
	BOOL bEnable = (BOOL)wParam;
	if ( m_pSlider )
	{
		m_pSlider->EnableWindow(bEnable);
	}
	
	if ( m_pLetterIndex )
	{
		m_pLetterIndex->EnableWindow(bEnable);
	}
	

	return S_OK;
}