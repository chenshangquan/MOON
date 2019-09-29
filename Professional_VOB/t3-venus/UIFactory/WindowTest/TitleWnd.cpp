// TitleWnd.cpp : implementation file
//

#include "stdafx.h"
#include "TitleWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTitleWnd
/************************************************************************/
/*
 Load picture from folder 
                                                                     */
/************************************************************************/
CTitleWnd::CTitleWnd(CString folder,int height)
{
	CString str;
	str = folder + "\\" + "left.png";
	LoadImage(str,m_hLeftBitmap,m_nLeftWidth);
	str = folder + "\\" + "right.png";
	LoadImage(str,m_hRightBitmap,m_nRightWidth);
	str = folder + "\\" + "mid.png";
	LoadImage(str,m_hMidBitmap,m_nMidWidth);
	m_nHeight = height;
}

/************************************************************************/
/*     
 load picture from picture path                                                                 
*/
/************************************************************************/
CTitleWnd::CTitleWnd(CString left,CString mid,CString right,int height)
{
	LoadImage(left,m_hLeftBitmap,m_nLeftWidth);
	LoadImage(right,m_hRightBitmap,m_nRightWidth);
	LoadImage(mid,m_hMidBitmap,m_nMidWidth);
	m_nHeight = height;
}

/************************************************************************/
/*              
 windows heigh defined by left image                                                        
*/
/************************************************************************/
CTitleWnd::CTitleWnd(CString left,CString mid,CString right)
{
	LoadImage(right,m_hRightBitmap,m_nRightWidth);
	LoadImage(mid,m_hMidBitmap,m_nMidWidth);
	LoadImage(left,m_hLeftBitmap,m_nLeftWidth);	
}
CTitleWnd::~CTitleWnd()
{
}


BEGIN_MESSAGE_MAP(CTitleWnd, CWnd)
	//{{AFX_MSG_MAP(CTitleWnd)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTitleWnd message handlers
/************************************************************************/
/*             
 Draw bitmap with dc                                                         
*/
/************************************************************************/
void CTitleWnd::DrawBitmap(CDC* pDC)
{
	// load IDB_BITMAP1 from our resources
	
	// Get the size of the bitmap

	// Select the bitmap into the in-memory DC
	//	CBitmap* bmp = CBitmap::FromHandle(hBitmap);
	CRect rect;

	this->GetWindowRect(&rect);
	m_nHeight = rect.Height();

	this->GetParent()->GetWindowRect(&rect);
	this->SetWindowPos(NULL,0,0,rect.Width(),m_nHeight,SWP_SHOWWINDOW);
	
	CDC dcMemory;
	dcMemory.CreateCompatibleDC(pDC);
	
	HBITMAP pOldBitmap = (HBITMAP)dcMemory.SelectObject(m_hLeftBitmap);
	
	// Find a centerpoint for the bitmap in the client area


	pDC->StretchBlt(0,0,m_nLeftWidth,m_nHeight,&dcMemory, 
		0,0,m_nLeftWidth,m_nHeight, SRCCOPY);

	pOldBitmap = (HBITMAP)dcMemory.SelectObject(m_hRightBitmap);
	pDC->StretchBlt(rect.Width() - m_nRightWidth,0,m_nRightWidth,m_nHeight,&dcMemory, 
		0, 0, m_nRightWidth, m_nHeight, SRCCOPY);

	pOldBitmap = (HBITMAP)dcMemory.SelectObject(m_hMidBitmap);
	pDC->StretchBlt(m_nLeftWidth,0,rect.Width() - m_nRightWidth - m_nLeftWidth,m_nHeight,&dcMemory, 
		0,0,m_nMidWidth,m_nHeight, SRCCOPY);
	

	dcMemory.SelectObject(pOldBitmap);
}

BOOL CTitleWnd::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	DrawBitmap(pDC);
	return TRUE;
//	return CWnd::OnEraseBkgnd(pDC);
}

void CTitleWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	GetForegroundWindow()->PostMessage(WM_NCLBUTTONDOWN,
		HTCAPTION,MAKELPARAM(point.x,point.y));

	// TODO: Add your message handler code here and/or call default

		// TODO: Add your message handler code here and/or call default
	
	CWnd::OnLButtonDown(nFlags, point);
}

void CTitleWnd::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	RECT   rcMax;  
	SystemParametersInfo(SPI_GETWORKAREA,   NULL,   (PVOID)&rcMax,   0);  
	WINDOWPLACEMENT   wp;  
	wp.length   =   sizeof(WINDOWPLACEMENT);  
	wp.flags   =   0;  
	wp.rcNormalPosition   =   rcMax;  
	wp.showCmd   =   SW_SHOWNORMAL;  
	GetForegroundWindow()->SetWindowPlacement(&wp);   
	CWnd::OnLButtonDblClk(nFlags, point);
}

/************************************************************************/
/*             
 Load image                                                         
*/
/************************************************************************/
BOOL CTitleWnd::LoadImage(CString strPath,HBITMAP& bitmap,int& width)
{
	Bitmap bmp(strPath.AllocSysString());
	width = bmp.GetWidth();
	bmp.GetHBITMAP(Color::White,&bitmap);
	m_nHeight = bmp.GetHeight();
	return TRUE;
}

void CTitleWnd::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
//	ModifyStyle( SS_BLACKFRAME, WS_CLIPCHILDREN );
	
	CWnd::PreSubclassWindow();
}

// BOOL CTitleWnd::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
// {
// 	// TODO: Add your specialized code here and/or call the base class
// //	return CreateEx()
// 	CString szClassName = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW);
// 	
// 	BOOL bRet = CWnd::CreateEx(WS_EX_CLIENTEDGE, lpszClassName,lpszWindowName,
// 		dwStyle, rect, pParentWnd, nID,pContext);
// 	
// 	if (!bRet)
// 		return FALSE;
// 	return bRet;
// 	//return CDialog::Create(IDD, pParentWnd);
// }
