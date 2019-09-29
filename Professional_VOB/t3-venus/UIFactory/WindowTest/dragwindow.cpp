// dragwindow.cpp : implementation file
//

#include "stdafx.h"
#include "windowtest.h"
#include "dragwindow.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDragWindow dialog
CDragWindow* CDragWindow::m_pcDragWindow = NULL;


CDragWindow::CDragWindow(CWnd* pParent /*=NULL*/)
	: CDialog(CDragWindow::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDragWindow)
		// NOTE: the ClassWizard will add member initialization here
	m_pParentWnd = NULL;
	m_pLastWnd = NULL;
//	m_pItemInfo = NULL;
	//}}AFX_DATA_INIT
}

// CDragWindow::CDragWindow( CRect rcList, CWnd* pWnd ) : 
// 	CBmpWnd( 0, "DragWindow", rcList, pWnd, WS_VISIBLE|WS_CHILD, "", GETUNIQID )
// {
// 	m_pParentWnd = NULL;
// 	m_pLastWnd = NULL;
// }


BEGIN_MESSAGE_MAP(CDragWindow, CDialog)
	//{{AFX_MSG_MAP(CDragWindow)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDragWindow message handlers
CDragWindow* CDragWindow::GetDragWindow()
{
	if (m_pcDragWindow == NULL) 
	{
		m_pcDragWindow = new CDragWindow();
		m_pcDragWindow->Create( IDD_DRAG_WINDOW, AfxGetMainWnd() );
	}
	return m_pcDragWindow;
}

void CDragWindow::SetParentWindow( CWnd* parent )
{

	try
	{
		if ( parent != NULL )
		{
			//CTouchList* pcTouchList = reinterpret_cast<CTouchList*>(parent);
			m_pParentWnd = parent;
		}
	}
	catch (...)
	{
	}
}


BOOL CDragWindow::BeginDrag( CPoint point, Bitmap* pBitmap )
{
	CDragWindow* pWnd = CDragWindow::GetDragWindow();
	   
	if (m_pParentWnd != NULL)
	{
		::ClientToScreen( m_pParentWnd->m_hWnd, &point ); 
	}
	
	if ( pBitmap != NULL )
	{
		DrawUI( pBitmap );
		
		pWnd->SetWindowPos( NULL, 0, 0, pBitmap->GetWidth(), pBitmap->GetHeight(), SWP_NOMOVE );
	}
	
	CRect rcWindow;
	pWnd->GetWindowRect(&rcWindow);
	
	pWnd->ShowWindow(SW_SHOW);
	
	pWnd->SetWindowPos( &wndTopMost, point.x - rcWindow.Width()/2, point.y - rcWindow.Height()/2, 
		0, 0, SWP_NOSIZE | SWP_SHOWWINDOW  );
	
	return TRUE;
}

BOOL CDragWindow::BeginDrag(CPoint point, IItemList* pItemList )
{		
	CDragWindow* pWnd = CDragWindow::GetDragWindow();
				
//	ReportMsg( WM_DRAG_BEGIN, pt );
	   
	if (m_pParentWnd != NULL)
	{
		::ClientToScreen( m_pParentWnd->m_hWnd, &point ); 
	}

	if ( pItemList != NULL )
	{
		m_pItemList = pItemList;
		DrawUI( pItemList );
	}

	CRect rcWindow;
	pWnd->GetWindowRect(&rcWindow);

	pWnd->ShowWindow(SW_SHOW);

	pWnd->SetWindowPos( &wndTopMost, point.x - rcWindow.Width()/2, point.y - rcWindow.Height()/2, 
		0, 0, SWP_NOSIZE | SWP_SHOWWINDOW  );

	return TRUE;
}


BOOL CDragWindow::Draging( CPoint point )
{
	::ClientToScreen( m_pParentWnd->m_hWnd, &point ); 

	ReportDragOver( point );

	CDragWindow* pWnd = CDragWindow::GetDragWindow();
	CRect rcWindow;
	pWnd->GetWindowRect(&rcWindow);	
	
	return 	pWnd->SetWindowPos( &wndTopMost, point.x - rcWindow.Width()/2, point.y - rcWindow.Height()/2,
		0, 0, SWP_NOSIZE | SWP_SHOWWINDOW  );
}


BOOL CDragWindow::EndDrag( CPoint point )
{
	::ClientToScreen( m_pParentWnd->m_hWnd, &point );

	CWnd* pWindow= GetActiveWindow(point);   
	if ( pWindow != NULL )
	{
//		CMsgDispatch::SendMessage( UI_DRAG_END, WPARAM(m_pItemInfo), MAKELPARAM( point.x, point.y ) );
	}

	CDragWindow* pWnd = CDragWindow::GetDragWindow();
	pWnd->ShowWindow( SW_HIDE );  
	return TRUE; 
}


void CDragWindow::ReportDragOver( CPoint point )
{
	CWnd* pWnd = GetActiveWindow(point);

	if ( m_pLastWnd != NULL && m_pLastWnd != pWnd )
	{    
//		CMsgDispatch::SendMessage( UI_DRAG_LEAVE, 0, MAKELPARAM( point.x, point.y ) );
		if ( NULL == pWnd)
		{
			m_pLastWnd = NULL;
		}			
	}
	
	if (pWnd != NULL)
	{	
		if ( m_pLastWnd == pWnd )
		{
			return ;
		}
		m_pLastWnd = pWnd;
//		CMsgDispatch::SendMessage( UI_DRAG_OVER, WPARAM(m_pItemInfo), MAKELPARAM( point.x, point.y ) );
	}
}


BOOL CDragWindow::RegisterDropWindow(CWnd* pWnd)
{
	vector<CWnd*>::iterator begin = m_vctWnd.begin();
	for (; begin != m_vctWnd.end(); begin++) 
	{
		if (*begin == pWnd) 
		{
			return FALSE;
		}
	}
	m_vctWnd.push_back(pWnd);
	return TRUE;
}


BOOL CDragWindow::UnRegisterDropWindow(CWnd* pWnd)
{
    vector<CWnd*>::iterator begin = m_vctWnd.begin();
	for (; begin != m_vctWnd.end(); begin++) 
	{
		if (*begin == pWnd) 
		{   
			m_vctWnd.erase(begin);
			return TRUE;
		}
	}
	
	return FALSE;
}

void CDragWindow::ReportMsg( UINT msg, CPoint point )
{
	vector<CWnd*>::iterator begin = m_vctWnd.begin();
	for ( ; begin != m_vctWnd.end(); begin++ ) 
	{
		CWnd* pWnd = *begin;
		pWnd->SendMessage( msg, 0, MAKELPARAM( point.x, point.y ) );
	}	
}


CWnd* CDragWindow::GetActiveWindow( CPoint point )
{
	vector<CWnd*>::iterator begin = m_vctWnd.begin();
	for (; begin != m_vctWnd.end(); begin++) 
	{
		CWnd* pWnd = *begin;
		if (pWnd->IsWindowVisible()) 
		{
			CRect rcWindow;
			pWnd->GetWindowRect(&rcWindow);
			if ( rcWindow.PtInRect(point) )
			{   
				return pWnd;
			}
		}
	}
	return NULL;
}

void CDragWindow::CreateDC()
{
	CDC *pDc= this->GetDC();
	pDc->SetBkMode(TRANSPARENT);    
  	CDragWindow* pWnd = CDragWindow::GetDragWindow();
    CRect rect;
	pWnd->GetClientRect( &rect );
	  
	m_dcMemDC.DeleteDC();
    m_cBitMap.DeleteObject();

	m_dcMemDC.CreateCompatibleDC( pDc );
	m_cBitMap.CreateCompatibleBitmap( pDc, rect.Width(), rect.Height() );	
	
	m_dcMemDC.SelectObject( m_cBitMap );	
	
    ReleaseDC(pDc);  
}


void CDragWindow::DrawUI( Bitmap* pBitmap )
{
	CDC *pDc= this->GetDC();
	
	if (m_pParentWnd == NULL)
	{
		return;
	}
	
	CDragWindow* pWnd = CDragWindow::GetDragWindow();
	if ( pWnd == NULL )
	{
		return;
	}	
	CRect rect;
	pWnd->GetClientRect( &rect );

	Graphics graph( m_dcMemDC.GetSafeHdc() );
    graph.Clear( Color( 0, 0, 0, 0 ) );	
    graph.SetSmoothingMode( SmoothingModeHighQuality );

	graph.DrawImage( pBitmap, rect.left, rect.top );

	ReleaseDC(pDc); 
}

void CDragWindow::DrawUI( IItemList* pItemList )
{
	CDC *pDc= this->GetDC();

	if (m_pParentWnd == NULL)
	{
		return;
	}

	CDragWindow* pWnd = CDragWindow::GetDragWindow();
	if ( pWnd == NULL )
	{
		return;
	}

	IBaseItem* pItem = pItemList->GetItemData();
	//CSize size = pItem->GetItemSize();

	pWnd->SetWindowPos( NULL, 0, 0, pItem->GetItemWidht(), pItem->GetItemHeight(), SWP_NOMOVE );
		
	CRect rect;
	pWnd->GetClientRect( &rect );

	Graphics graph( m_dcMemDC.GetSafeHdc() );
    graph.Clear( Color( 0, 0, 0, 0 ) );	
    graph.SetSmoothingMode( SmoothingModeHighQuality );
	
	CBrush cBrushBK(RGB( 255, 255, 255 ) ); 
	rect.SetRect( 0, 0, rect.Width(), 55 );
	m_dcMemDC.FillRect( rect, &cBrushBK );

	IBaseItem* pBaseItem = m_pItemList->GetItemData();
	CRect rc = pBaseItem->GetItemRect();
	graph.TranslateTransform( -rc.left, -rc.top );

	Args_Graphics args_Graphics( &graph, Rect( rect.left, rect.top, rect.Width(), rect.Height() ) );

	DrawItem( m_pItemList, &args_Graphics );
	//pItem->DrawItem( rect, &graph );

	graph.ResetTransform();

	pDc->BitBlt( rect.left, 0, rect.Width(), rect.Height(), &m_dcMemDC, 0, 0, SRCCOPY);	

    ReleaseDC(pDc);  
}

void CDragWindow::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CRect rect;
	GetClientRect( &rect );

	CDC* pDC = GetDC();		
	if ( NULL == pDC )
	{   
		return;
	}  
	//DrawUI( m_pItemList );	
	//Ìùitem		
	pDC->BitBlt( rect.left, 0, rect.Width(), rect.Height(), &m_dcMemDC, 0, 0, SRCCOPY);		
	
	ReleaseDC(pDC);
	// Do not call CDialog::OnPaint() for painting messages
}

BOOL CDragWindow::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CreateDC();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDragWindow::DrawItem( IItemList* pItemList, IArgs* pArgs )
{
	int nItemCount = pItemList->GetItemCount();
	IBaseItem* pBaseItem = pItemList->GetItemData();
	
	CSrotItemGroup<IBaseItem,int>* pSortItem = 0;
	
	Args_Graphics* p = 0;
	
	Args_Graphics pSubGraphics( 0, Rect(0,0,0,0) );
	Bitmap* pSubBitmap = 0;
	if ( p = dynamic_cast<Args_Graphics*>(pArgs) )
	{		
		if ( pBaseItem != 0 )
		{
			pBaseItem->Draw( pArgs );
			CRect rc = pBaseItem->GetItemRect();
			p->m_rc = Rect( Point(rc.left,rc.top), Size(rc.Width(),rc.Height()) );
			
			if ( nItemCount != 0 )
			{
				pSubBitmap = new Bitmap( rc.Width(), rc.Height(), p->m_pGraphics );
				pSubGraphics.m_pGraphics = Graphics::FromImage( pSubBitmap );
				pSubGraphics.m_rc = Rect( Point(rc.left,rc.top), Size(rc.Width(),rc.Height()) );
			}
		}		
	}
	else
	{
		return;
	}
	
	for ( int nIndex = 0; nIndex < nItemCount; nIndex++ )
	{
		IItemList* pSubList = pItemList->GetItemByIndex( nIndex );
		if ( pSubList != 0 )
		{
			DrawItem( pSubList, &pSubGraphics );
		}
	}
	
	
	if ( nItemCount != 0)
	{
		p->m_pGraphics->DrawImage( pSubBitmap, p->m_rc.GetLeft(), p->m_rc.GetTop() );
		delete pSubBitmap;
		pSubBitmap = 0;
	}	
	if ( pSortItem != 0 )
	{
		p->m_pGraphics->ResetTransform();
	}	
}
