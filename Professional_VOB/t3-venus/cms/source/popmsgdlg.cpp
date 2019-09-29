// popmsgdlg.cpp : implementation file
//

#include "stdafx.h" 
#include "popmsgdlg.h"
#include "GdiplusGraphics.h"
#include "GdiPlusHeaders.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPopMsgDlg dialog

CPopMsgDlg* CPopMsgDlg::m_pPopMsgInstance = NULL; 

CPopMsgDlg::CPopMsgDlg(CWnd* pParent /*=NULL*/)
		: CDialog(CPopMsgDlg::IDD, pParent) 
{
	//{{AFX_DATA_INIT(CPopMsgDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPopMsgDlg* CPopMsgDlg::Instance()
{
	if ( NULL == CPopMsgDlg::m_pPopMsgInstance )
	{
		CPopMsgDlg::m_pPopMsgInstance = new CPopMsgDlg( AfxGetApp()->GetMainWnd() );
		CPopMsgDlg::m_pPopMsgInstance->Create( CPopMsgDlg::IDD , AfxGetApp()->GetMainWnd() );	
		CPopMsgDlg::m_pPopMsgInstance->ShowWindow( SW_HIDE );
	}

	return CPopMsgDlg::m_pPopMsgInstance;
}

void CPopMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPopMsgDlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPopMsgDlg, CDialog)
	//{{AFX_MSG_MAP(CPopMsgDlg)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPopMsgDlg message handlers


CPopMsgDlg::~CPopMsgDlg()
{
	m_cTextBitmap.DeleteObject();
	m_MemeryTextDc.DeleteDC();

	m_cBitmap.DeleteObject();
	m_MemeryDc.DeleteDC();

	CPopMsgDlg::m_pPopMsgInstance = NULL;
}


void CPopMsgDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CRect rect;
	GetClientRect(&rect);
	
	ReDrawMsgText();
	
	m_MemeryDc.BitBlt(m_rectMsgText.left, m_rectMsgText.top, 
		m_rectMsgText.Width(), m_rectMsgText.Height(),&m_MemeryTextDc, 0, 0, SRCCOPY  );
	

	dc.BitBlt( 0, 0, rect.Width(), rect.Height(), &m_MemeryDc, 0, 0, SRCCOPY );	 

	POINT ptIcon;
	ptIcon.x = m_rectCloseBtn.left;
	ptIcon.y = m_rectCloseBtn.top;
	
	dc.DrawIcon( ptIcon, m_hCurCloseIcon );
}


BOOL CPopMsgDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_nMsgTextTransparentValue = MSG_TEXT_TRANSPARENT_MAX_VALUE;
	m_nEadgeWidth     = 2;
	m_nTriangleWidth  = 21;
	m_nTriangleHeight = 14;
	m_nRoundRectWidth = 16;
	m_nRoundRectHeight= 16;
	m_cColorBk = RGB(6, 6, 6);
	m_cColorLine = RGB(23, 157, 214);

	m_vctPopMsg.clear();
	
	int nDlgWidth  = 354 + m_nEadgeWidth * 2;
	int nDlgHeight = 135 + m_nEadgeWidth * 2 + m_nTriangleHeight;
	
	
	const char* achFontFamlyName = ("黑体");//("微软雅黑"); 
	m_dwFontSize = 12;
	
	ZeroMemory( m_awszFontName, sizeof(m_awszFontName) );
	MultiByteToWideChar(CP_ACP, 0, achFontFamlyName, -1, m_awszFontName, strlen(achFontFamlyName) );
	
	
	CRect rect;
	GetClientRect(&rect);	

	rect.right  = rect.left + nDlgWidth;
	rect.bottom = rect.top  + nDlgHeight;
	
	MoveWindow( &rect );


	CreateDlgRegion();
	


	
	m_rectMsgText.left = rect.left + 72;
	m_rectMsgText.top  = rect.top + 6;
	m_rectMsgText.right= rect.right - 30;
	m_rectMsgText.bottom = rect.bottom - m_nTriangleHeight - 10;//16;
	
	
	m_nCurMsgTextTop1 = MSG_TEXT_HEIGHT;
	m_nCurMsgTextTop2 = m_rectMsgText.bottom;
	
	m_nStrMsgText1 = "";
	m_nStrMsgText2 = "";
	
	//close btn init
	m_rectCloseBtn.left  = rect.right - 40;
	m_rectCloseBtn.right = m_rectCloseBtn.left + 25;
	m_rectCloseBtn.top   = rect.top + 4;
	m_rectCloseBtn.bottom = m_rectCloseBtn.top + 22;
 

	int nScreenWidth  = GetSystemMetrics(SM_CXSCREEN); //屏幕宽度   
	int nScreenHeight = GetSystemMetrics(SM_CYSCREEN); //屏幕高度
	rect.left  = nScreenWidth - nDlgWidth;
	rect.right = rect.left + nDlgWidth - 2;
	rect.top   = nScreenHeight - nDlgHeight ;
	rect.bottom = rect.top + nDlgHeight;
	MoveWindow( &rect );
	
	CreateMemoryDC();
	CreateTextMemoryDC();
	

	m_hCloseIconNormal = AfxGetApp()->LoadIcon( IDI_POPMSG_CLOSE_NORMAL );
	m_hCloseIconPress  = AfxGetApp()->LoadIcon( IDI_POPMSG_CLOSE_PRESS );

	m_hCurCloseIcon = m_hCloseIconNormal;
 

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPopMsgDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	switch ( nIDEvent )
	{
	case WM_TIMER_DLGSHOW:
		{
		//	if ( m_nDlgTransparentValue >= DLG_TRANSPARENT_MAXVALUE )
			{
				KillTimer(nIDEvent);
		//		m_nDlgTransparentValue = DLG_TRANSPARENT_DEFVALUE;
				
				SetTimer( WM_TIMER_DLGHIDE, WM_TIMER_DLGHIDE_INTVAL, NULL );
			}
// 			else
// 			{
// 				m_nDlgTransparentValue += 10;
// 			}
// 			SetDlgTransparent( m_nDlgTransparentValue );
        }
		break;
	case WM_TIMER_DLGHIDE:
		{
			KillTimer( nIDEvent );
			this->ShowWindow( SW_HIDE );
		}
		break;
	case WM_TIMER_MOVEMSG:
		{
			UpdateMsgPosition();
		}
		break; 
	default:
		break;
	}
	
	CDialog::OnTimer(nIDEvent);
}

/*
int CRgn::CombineRgn( CRgn* pRgn1, CRgn* pRgn2, int nCombineMode );　　
其中pRgn1,pRgn2为要合并的两个“region”，nCombineMode为合并的方式，
此应用中取RGN_OR，即两”region”全部合并去处重复部分
*/
void CPopMsgDlg::CreateDlgRegion()
{
	CRgn cDlgRgn;         
	CRgn cTriangleRgn;
	CRgn cRgnCombResult;
	CRect rectDlg;
	
	int nPointStartX = 88;
	GetWindowRect(&rectDlg);

 
/* w:21*h:16

    1-------2
	  -   -
   	    -
		3
*/
    
	m_trianglePoint[0].x = nPointStartX;
	m_trianglePoint[0].y = rectDlg.bottom - m_nTriangleHeight;

	m_trianglePoint[1].x = nPointStartX + m_nTriangleWidth;
	m_trianglePoint[1].y = rectDlg.bottom - m_nTriangleHeight;

	m_trianglePoint[2].x = nPointStartX + (m_nTriangleWidth / 2);
	m_trianglePoint[2].y = rectDlg.bottom;

	rectDlg.bottom -= (m_nTriangleHeight - m_nEadgeWidth);

	cDlgRgn.CreateRoundRectRgn( rectDlg.left, rectDlg.top, rectDlg.right, rectDlg.bottom, m_nRoundRectWidth, m_nRoundRectHeight);

	cTriangleRgn.CreatePolygonRgn( m_trianglePoint, TRIANGLE_POINT_NUM,  WINDING);  //ALTERNATE|WINDING
	
	cTriangleRgn.CombineRgn(&cDlgRgn, &cTriangleRgn, RGN_OR);

	SetWindowRgn(cTriangleRgn, TRUE);

	
	cDlgRgn.DeleteObject();
	cTriangleRgn.DeleteObject();
	cTriangleRgn.DeleteObject();
	
}



void CPopMsgDlg::AddMsg(CString strMsgText, BOOL bImeShow/* =FALSE */)
{
	for( int i = 0; i < m_vctPopMsg.size(); i++ )
	{
		if( strMsgText == m_vctPopMsg[i] )
		{
			return ;
		}
	}

	if ( bImeShow )
	{
		m_vctPopMsg.clear();
	}
 
	if (m_vctPopMsg.size() == 0 )
	{
		m_nStrMsgText1 = "";
	}
	else
	{
		m_nStrMsgText1 = m_vctPopMsg[m_vctPopMsg.size()-1];
	}
	
	if ( m_vctPopMsg.size() > 0)
	{
		m_vctPopMsg.pop_back();
	}

	m_vctPopMsg.push_back(strMsgText);

	if (m_vctPopMsg.size() == 0 )
	{
		m_nStrMsgText2 = "";
	}
	else
	{
		if (m_vctPopMsg.size() == 1 )
		{
			m_nStrMsgText2 = m_vctPopMsg[m_vctPopMsg.size()-1];
		}
	}

	//已经显示msg的情况下,需要重新设置定时器
	KillTimer( WM_TIMER_DLGHIDE );
	SetTimer( WM_TIMER_DLGHIDE, WM_TIMER_DLGHIDE_INTVAL, NULL );
	
	SetTimer( WM_TIMER_MOVEMSG, WM_TIMER_MOVEMSG_INTVAL, NULL);

	m_nCurMsgTextTop1 = MSG_TEXT_HEIGHT;

	m_nCurMsgTextTop2 = m_rectMsgText.bottom;
}

void CPopMsgDlg::UpdateMsgPosition()
{
	if ( m_nCurMsgTextTop1 <= MSG_MOVE_STOP_VALUE )
	{
		KillTimer(WM_TIMER_MOVEMSG);
		m_nMsgTextTransparentValue = MSG_TEXT_TRANSPARENT_MIN_VALUE;		
	}
	else
	{
		m_nCurMsgTextTop1 -= MSG_MOVE_STEP;
		m_nCurMsgTextTop2 -= MSG_MOVE_STEP;
		m_nMsgTextTransparentValue -= MSG_TRANSPARENT_CHANGE_STEP;

		if ( m_nMsgTextTransparentValue < MSG_TEXT_TRANSPARENT_MIN_VALUE )
		{
			m_nMsgTextTransparentValue = MSG_TEXT_TRANSPARENT_MAX_VALUE;
		}
	}

	Invalidate();
}

void CPopMsgDlg::CreateMemoryDC()
{
	static BOOL32 bIsInitMemoryDC = FALSE;

	if ( bIsInitMemoryDC )
	{
		//背景只需要创建一次即可
		bIsInitMemoryDC = TRUE;
		return;
	}

	CDC *pDc = GetDC();
	pDc->SetBkMode( TRANSPARENT );
	CRect rect;
	GetClientRect(&rect);

	m_MemeryDc.CreateCompatibleDC(pDc);

	m_cBitmap.CreateCompatibleBitmap( pDc, rect.Width(), rect.Height());
	
	m_MemeryDc.SelectObject( &m_cBitmap );
	
	Graphics graph( m_MemeryDc.GetSafeHdc() );
	
    graph.SetSmoothingMode( SmoothingModeHighQuality );

	//画背景 RGB(6, 6, 6); m_cColorBk
	CBrush cBrush;
	cBrush.CreateSolidBrush( m_cColorBk );

	CPen *pOldPen = NULL;
	CPen pen(PS_SOLID, m_nEadgeWidth, m_cColorLine);
	pOldPen = m_MemeryDc.SelectObject(&pen);
	m_MemeryDc.FillRect( &rect, &cBrush );
	/*
	1--------2
	 -      -
	 -      -
	7--6 4---3
		5 

	*/
	//1->2
	m_MemeryDc.MoveTo(rect.left,  rect.top + m_nEadgeWidth/2);
	m_MemeryDc.LineTo(rect.right,  rect.top + m_nEadgeWidth/2);

	//2->3
	m_MemeryDc.MoveTo(rect.right-m_nEadgeWidth, rect.top);
	m_MemeryDc.LineTo(rect.right-m_nEadgeWidth, rect.bottom - m_nTriangleHeight);

	//3->4
	m_MemeryDc.MoveTo(rect.right, rect.bottom - m_nTriangleHeight);
	m_MemeryDc.LineTo(m_trianglePoint[1].x, m_trianglePoint[1].y - m_nEadgeWidth/2);

	//4->5
	m_MemeryDc.LineTo(m_trianglePoint[2].x , m_trianglePoint[2].y - m_nEadgeWidth/2);

	//5->6
	m_MemeryDc.LineTo(m_trianglePoint[0].x, m_trianglePoint[0].y - m_nEadgeWidth/2);

	//6->7
	m_MemeryDc.LineTo(rect.left, rect.bottom - m_nTriangleHeight);

	//7->1
	m_MemeryDc.MoveTo( rect.left + m_nEadgeWidth/2, rect.bottom);
	m_MemeryDc.LineTo( rect.left + m_nEadgeWidth/2, rect.top);

	CRect rectArc;
	POINT ptStart;
	POINT ptEnd;

	//arc left up
	rectArc.left = rect.left ;
	rectArc.top  = rect.top ;
	rectArc.right= rectArc.left + m_nRoundRectWidth;
	rectArc.bottom=rectArc.top  + m_nRoundRectHeight;

	ptStart.x = rectArc.right;
	ptStart.y = rectArc.top-m_nRoundRectHeight;

	ptEnd.x = rectArc.left-m_nRoundRectWidth;
	ptEnd.y = rectArc.bottom;
	m_MemeryDc.Arc(&rectArc,  ptStart, ptEnd);

	//arc right up
	rectArc.left = rect.right - m_nRoundRectWidth-m_nEadgeWidth;
	rectArc.right= rectArc.left+m_nRoundRectWidth;
	rectArc.top  = rect.top;
	rectArc.bottom = rectArc.top + m_nRoundRectHeight;
	
	ptStart.x = rectArc.right+m_nRoundRectWidth;
	ptStart.y = rectArc.bottom-m_nRoundRectHeight;

	ptEnd.x = rectArc.left;
	ptEnd.y = rectArc.top-m_nRoundRectHeight ;
	m_MemeryDc.Arc(&rectArc,  ptStart, ptEnd);

	//arc right down
	rectArc.left = rect.right - m_nRoundRectWidth-m_nEadgeWidth;
	rectArc.right= rectArc.left + m_nRoundRectWidth+m_nEadgeWidth;
	rectArc.bottom = rect.bottom - m_nTriangleHeight;
	rectArc.top = rectArc.bottom - m_nRoundRectHeight;
	
	ptStart.x = rectArc.left+m_nRoundRectWidth;
	ptStart.y = rectArc.bottom+m_nTriangleHeight;
	
	ptEnd.x = rectArc.right;
	ptEnd.y = rectArc.bottom-m_nTriangleHeight+m_nEadgeWidth;
	m_MemeryDc.Arc(&rectArc,  ptStart, ptEnd);

	//arc left down
	rectArc.left = rect.left ;
	rectArc.bottom  = rect.bottom-m_nTriangleHeight ;
	rectArc.right= rectArc.left + m_nRoundRectWidth;
	rectArc.top=rectArc.bottom  - m_nRoundRectHeight;
	
	ptStart.x = rectArc.left-m_nRoundRectWidth;
	ptStart.y = rectArc.bottom-m_nRoundRectHeight;
	
	ptEnd.x = rectArc.right-m_nTriangleHeight+m_nEadgeWidth;
	ptEnd.y = rectArc.bottom;
	m_MemeryDc.Arc(&rectArc,  ptStart, ptEnd);


	//画icon
	HICON hAlertIcon = AfxGetApp()->LoadIcon(IDI_POPMSG_ALERT);

	POINT ptIcon;
	ptIcon.x = 28;
	ptIcon.y = 56;

	m_MemeryDc.DrawIcon( ptIcon, hAlertIcon);

	cBrush.DeleteObject();
	m_MemeryDc.SelectObject(pOldPen);
}

void CPopMsgDlg::CreateTextMemoryDC()
{
	CDC *pDc = GetDC();

	m_MemeryTextDc.CreateCompatibleDC(pDc);
	
	m_cTextBitmap.CreateCompatibleBitmap( pDc, m_rectMsgText.Width(), m_rectMsgText.Height());

	CBitmap* pOldBitmap = NULL;
	pOldBitmap = m_MemeryTextDc.SelectObject( &m_cTextBitmap );

	m_MemeryTextDc.SetBkMode( TRANSPARENT );

}


void CPopMsgDlg::ReDrawMsgText()
{
//	CRect rect;
//	GetClientRect(&rect);	
	Graphics graph( m_MemeryTextDc.GetSafeHdc() );
	
    graph.SetSmoothingMode( SmoothingModeHighQuality );
	graph.SetTextRenderingHint(TextRenderingHint(TextRenderingHintAntiAlias));
	
	StringFormat sf;
	sf.SetLineAlignment( StringAlignmentCenter );
	sf.SetAlignment( StringAlignmentNear );
	
	//画背景
	CBrush cBrush;
	cBrush.CreateSolidBrush( m_cColorBk );
	
	CPen *pOldPen = NULL;
	CPen pen(PS_SOLID, m_nEadgeWidth, m_cColorLine);
	pOldPen = m_MemeryTextDc.SelectObject(&pen);
	
	CRect rectText;
	rectText.left = 0;
	rectText.right= rectText.left + m_rectMsgText.Width();
	rectText.top = 0;
	rectText.bottom = rectText.top + m_rectMsgText.Height();
	m_MemeryTextDc.FillRect( &rectText, &cBrush );
	
	SolidBrush brush( Color(m_nMsgTextTransparentValue, 255, 255, 255 ) );
	
	FontFamily fontFamily( m_awszFontName );
	Font font( &fontFamily, m_dwFontSize, FontStyleBold);
	
	RectF rectString;
	
	//msgtext 1
	WCHAR *pwszText = NULL;
	pwszText = new WCHAR[m_nStrMsgText1.GetLength() + 1];
	int nLen = MultiByteToWideChar( CP_ACP, 0, m_nStrMsgText1, -1, NULL, NULL ); 
	MultiByteToWideChar(CP_ACP,   0,   m_nStrMsgText1,   -1,   pwszText,   nLen);
	
	graph.MeasureString( pwszText, -1, &font, PointF( (float)0, (float)0 ), &sf, &rectString );

	graph.DrawString( pwszText, -1, &font, RectF( (float)rectText.left, (float)m_nCurMsgTextTop1, 
		m_rectMsgText.Width()/*rectString.Width*/, m_rectMsgText.Height() /*rectString.Height*/), &sf, &brush );
	
	delete []pwszText;
	pwszText = NULL;
	
	SolidBrush brush2( Color(255-m_nMsgTextTransparentValue,255, 255, 255 ) );
	//msgtext 2
	pwszText = new WCHAR[m_nStrMsgText2.GetLength() + 1];
	nLen = MultiByteToWideChar( CP_ACP, 0, m_nStrMsgText2, -1, NULL, NULL ); 
	MultiByteToWideChar(CP_ACP,   0,   m_nStrMsgText2,   -1,   pwszText,   nLen);
	
	graph.MeasureString( pwszText, -1, &font, PointF( (float)0, (float)0 ), &sf, &rectString );
	
	graph.DrawString( pwszText, -1, &font, RectF( (float)rectText.left, (float)m_nCurMsgTextTop2, 
		m_rectMsgText.Width()/*rectString.Width*/, m_rectMsgText.Height() /*rectString.Height*/), &sf, &brush2 );
	
	delete []pwszText;
	pwszText = NULL;

	m_MemeryTextDc.SelectObject(pOldPen);
	cBrush.DeleteObject();
	
}


void CPopMsgDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	KillTimer( WM_TIMER_DLGSHOW );
	KillTimer( WM_TIMER_DLGHIDE );

	// TODO: Add your message handler code here
	if ( bShow )
	{
		//显示并置顶
		SetWindowPos(&wndNoTopMost, 0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);
		SetWindowPos(&wndTopMost, 0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);

		SetTimer( WM_TIMER_DLGSHOW, WM_TIMER_DLGSHOW_INTVAL, NULL );
	}
	else
	{
		//隐藏
		if ( m_vctPopMsg.size() > 0)
		{
			m_vctPopMsg.pop_back();
		}
		m_hCurCloseIcon = m_hCloseIconNormal;
	}
}

void CPopMsgDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	POINT pt;
	pt.x = point.x;
	pt.y = point.y;
	
	if ( m_rectCloseBtn.PtInRect( pt ) )
	{
		this->ShowWindow( SW_HIDE );
	}

	CDialog::OnLButtonDown(nFlags, point);
}

void CPopMsgDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnLButtonUp(nFlags, point);
}

void CPopMsgDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	POINT pt;
	pt.x = point.x;
	pt.y = point.y;

	if ( m_rectCloseBtn.PtInRect( pt ) )
	{
		m_hCurCloseIcon = m_hCloseIconPress;
	}
	else
	{
		m_hCurCloseIcon = m_hCloseIconNormal;
	}

	InvalidateRect( m_rectCloseBtn, TRUE );

	CDialog::OnMouseMove(nFlags, point);
}
