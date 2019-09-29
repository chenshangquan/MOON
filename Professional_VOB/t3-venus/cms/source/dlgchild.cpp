// dlgchild.cpp : implementation file
//

#include "stdafx.h"
#include "cms.h"
#include "dlgchild.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgChild dialog


CDlgChild::CDlgChild(CWnd* pParent /*=NULL*/)
	: CTransparentBaseDlg(CDlgChild::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgChild)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgChild::DoDataExchange(CDataExchange* pDX)
{
	CTransparentBaseDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgChild)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgChild, CTransparentBaseDlg)
	//{{AFX_MSG_MAP(CDlgChild)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP

    ON_MESSAGE( WM_REDRAW_UI, OnRedrawUI )

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgChild message handlers


LRESULT CDlgChild::OnRedrawUI( WPARAM wParam, LPARAM lParam )
{ 
	if ( !IsWindowVisible() )
	{
		return S_OK;
	}

    Graphics *pGraphics = (Graphics*)wParam;
    
    if ( pGraphics == NULL )
    {
        // 为空的话，则是由子控件发来的，需要再向父窗口转发
        CWnd* pParent = GetParent();
        if ( pParent != NULL )
        {
            pParent->SendMessage( WM_REDRAW_UI, wParam, lParam );
        } 
        return S_FALSE;
    }
    
    if ( 0 != m_pImageBK )
    {   
        CRect cRect;
        GetWindowRect( &cRect );
        POINT point = cRect.TopLeft(); 

		HWND hGraphWnd = (HWND )lParam;
        ::ScreenToClient( hGraphWnd, &point );
        //GetParent()->ScreenToClient( &point ); 

//         PrtMsg("\n[CDlgChild::OnRedrawUI]handle=%p, left:%d  top:%d  width:%d  height:%d\n",
//         m_hWnd,  point.x,point.y,cRect.right - cRect.left, cRect.bottom - cRect.top );
        
        pGraphics->DrawImage( m_pImageBK, point.x, point.y,/* m_pImageBK->GetWidth()*/cRect.Width(), /*m_pImageBK->GetHeight()*/cRect.Height() );
        
    }
    
    return S_OK;
}