// TransparentSwitchButton.cpp : implementation file
//

#include "stdafx.h"
#include "button.h"
#include "srcManage.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransparentSwitchButton

const CString CTransparentSwitchButton::strOnNormal = "OnNormal.png";
const CString CTransparentSwitchButton::strOnPress = "OnPress.png";
const CString CTransparentSwitchButton::strOnDisable = "OnDisable.png";
const CString CTransparentSwitchButton::strOnOver = "OnOver.png";
const CString CTransparentSwitchButton::strOnSel = "OnSel.png";
const CString CTransparentSwitchButton::strOffNormal = "OffNormal.png";
const CString CTransparentSwitchButton::strOffPress = "OffPress.png";
const CString CTransparentSwitchButton::strOffDisable = "OffDisable.png";
const CString CTransparentSwitchButton::strOffOver = "OffOver.png";
const CString CTransparentSwitchButton::strOffSel = "OffSel.png";

//template<> WNDPROC TransparentAssist<CTransparentSwitchButton>::m_pWndProc = NULL;
CTransparentSwitchButton::CTransparentSwitchButton()
{
	//RegsiterWndProc();
    m_emStatus = emStatusNormal;
	m_bOn = FALSE;
    m_pImgOnNormal = NULL;
    m_pImgOnPress = NULL;
    m_pImgOnDiable = NULL;
	m_pImgOnOver = NULL;

    m_pImgOffNormal = NULL;
    m_pImgOffPress = NULL;
    m_pImgOffDiable = NULL;
	m_pImgOffOver = NULL;
    m_hBindWnd = 0;

	m_bStretch = TRUE;
    m_bShowText = FALSE;

    m_cTextColor = Color( 232, 238, 244 );  
    m_pFont = CSrcManage::GetFont( "΢���ź�", 14 ); 
    m_cStringFormat.SetAlignment( StringAlignmentNear );
    m_cStringFormat.SetLineAlignment( StringAlignmentCenter );
	m_bMouseTrack = TRUE;
}

CTransparentSwitchButton::~CTransparentSwitchButton()
{

}


BEGIN_MESSAGE_MAP(CTransparentSwitchButton, CButton)
    //{{AFX_MSG_MAP(CTransparentCheckButton)
    ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
    
    //}}AFX_MSG_MAP
    ON_MESSAGE( WM_REDRAW_UI, OnRedrawUI )
    ON_MESSAGE( WM_BIND_WND_HIDE, OnBindWndHide )
	ON_MESSAGE( WM_MOUSELEAVE, OnMouseLeave )
	ON_MESSAGE( WM_MOUSEHOVER, OnMouseHover )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransparentCheckButton message handlers
LRESULT CTransparentSwitchButton::OnBindWndHide( WPARAM wParam, LPARAM lParam )
{
    // if ( m_hBindWnd != 0 )   2011-10-14,��ֹ��Ϣ����ʱ����Щwnd�İ󶨴����ѷ����ı�

//     CString str;
//     str.Format( "OnBindWndHide, m_emStatus: %d, m_bOn: %d \n", m_emStatus, m_bOn );
//     OutputDebugString(str);
	if( m_emStatus != emStatusPress )
    {
        m_emStatus = emStatusNormal;
        m_bOn = FALSE;
        NOTIF_PARENT_WND 
    }
  
    return S_OK;
}


LRESULT CTransparentSwitchButton::OnRedrawUI( WPARAM wParam, LPARAM lParam )
{
    m_hParent = (HWND)lParam;
    if ( IsWindowVisible() == FALSE || GetParent() == NULL || m_pImgOnNormal == NULL )
    {
        return S_FALSE;
    }

    Graphics *pGraphics = (Graphics*)wParam;
    HWND hGraphWnd = (HWND )lParam;
    CWnd * pGraphWnd = FromHandle(hGraphWnd);
    
    if ( pGraphics == NULL || pGraphWnd == NULL )
    {
        return S_FALSE;
    }
	

    CRect cRect;
    GetWindowRect( &cRect );
    POINT point = cRect.TopLeft();

    //GetParent()->ScreenToClient( &point );
    pGraphWnd->ScreenToClient( &point );
     
    if ( FALSE == m_bStretch && m_pImgOnNormal->GetWidth() != 0 && ( cRect.Width() != m_pImgOnNormal->GetWidth()
		|| cRect.Height() != m_pImgOnNormal->GetHeight() ) )
    {
        SetWindowPos( NULL, 0, 0, m_pImgOnNormal->GetWidth(), m_pImgOnNormal->GetHeight(), SWP_NOMOVE|SWP_NOACTIVATE );
    }

    Image *pImage = NULL;
    switch ( m_emStatus )
    {
    case emStatusNormal:
        pImage = ( m_bOn == TRUE ? m_pImgOnNormal : m_pImgOffNormal );
        break;
    case emStatusPress:
        pImage = ( m_bOn == TRUE ? m_pImgOnPress : m_pImgOffPress );
        break;
    case emStatusOver:
        pImage = ( m_bOn == TRUE ? m_pImgOnOver : m_pImgOffOver );
        break;
    }

    if ( FALSE == IsWindowEnabled() )
    {
        pImage = ( m_bOn == TRUE ? m_pImgOnDiable : m_pImgOffDiable );
    }

    if ( NULL != pImage && pImage->GetWidth() != 0 )
    {
        pGraphics->DrawImage( pImage, point.x, point.y, cRect.Width()/*pImage->GetWidth()*/,cRect.Height() /*pImage->GetHeight()*/ );
    }

    if ( m_bShowText )
    {
        SolidBrush brush( m_cTextColor );
        pGraphics->SetTextRenderingHint( TextRenderingHint( TextRenderingHintAntiAlias ) );
      
        CString strText;
        GetWindowText( strText );   
        BSTR bstr = strText.AllocSysString();
        pGraphics->DrawString( bstr, -1, m_pFont, RectF( (float)point.x + 36, (float)point.y, cRect.Width() - 36, cRect.Height() ), &m_cStringFormat, &brush );	
        SysFreeString( bstr );
	}  

    return S_OK;  
}


void CTransparentSwitchButton::OnLButtonDown(UINT nFlags, CPoint point) 
{   	
	m_emStatus = emStatusPress;

	NOTIF_PARENT_WND
    CButton::OnLButtonDown(nFlags, point);

	SetCapture();
}

void CTransparentSwitchButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	ReleaseCapture();  

	if ( m_emStatus != emStatusPress )
	{
		return;
	}
	m_emStatus = emStatusNormal;
	m_bOn = !m_bOn;
    NOTIF_PARENT_WND
	PostMessage( WM_BUTTON_CLICK, (WPARAM)GetSafeHwnd() );
    //20120712  SXC
    GetParent()->PostMessage( WM_BUTTON_CLICK, (WPARAM)GetSafeHwnd() );
    CButton::OnLButtonUp(nFlags, point);
}

//���bug��˫��ɸѡ�ؼ���ɸѡ��δ��������ɸѡ�ؼ�״̬����  20131107  by xhx
void CTransparentSwitchButton::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	m_emStatus = emStatusPress;
	
	NOTIF_PARENT_WND
	CButton::OnLButtonDblClk(nFlags, point);
	
	SetCapture();
}

void CTransparentSwitchButton::OnMouseMove(UINT nFlags, CPoint point)
{
	if ( !IsWindowEnabled() || !IsWindowVisible() )
	{
		return;
	}

    CRect rect;    
    GetClientRect( &rect );

	if ( m_pImgOnOver != NULL && m_pImgOffOver !=NULL )
	{
		if ( m_bMouseTrack )     //2013.5.21  ---�ҵ�������ͣ���Ĵ���,����л����򴰿�ʧȥ��꽹����over��������
		{
			TRACKMOUSEEVENT csTME;
			csTME.cbSize = sizeof (csTME);
			csTME.dwFlags = TME_LEAVE|TME_HOVER; //�����¼�
			csTME.hwndTrack = GetSafeHwnd() ;// ָ��Ҫ ׷�� �Ĵ��� 
			csTME.dwHoverTime = 10;  // ����ڰ�ť��ͣ������ 10ms ������Ϊ״̬Ϊ HOVER
			::_TrackMouseEvent (&csTME); // ���� Windows �� WM_MOUSELEAVE|WM_MOUSEHOVER�¼�֧�� 
			
			m_bMouseTrack = FALSE;   // ���Ѿ� ׷�� ����ֹͣ ׷�� 
		}
	}

	//�����Down�º�,�ƶ����,������겻��button��(û��WM_MOUSELEAVE��Ϣ),��button��Ϊnormal״̬
    if ( !rect.PtInRect( point) && m_emStatus == emStatusPress )
    {   
        ReleaseCapture();
        m_emStatus = emStatusNormal;		
		if ( m_hBindWnd != NULL && ( FALSE == ::IsWindowVisible(m_hBindWnd) ) )
		{
			m_bOn = FALSE;
		}		
        NOTIF_PARENT_WND 
    }
    
}

void CTransparentSwitchButton::SetSwitchState( BOOL bOn )
{
	m_bOn = bOn; 
	NOTIF_PARENT_WND
}

void CTransparentSwitchButton::SetImage( CString strFolder, BOOL bInvalidate /* = FALSE */ )
{
	String strFile = strFolder + "//" + CTransparentSwitchButton::strOnNormal;
	m_pImgOnNormal = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CTransparentSwitchButton::strOnPress;
	m_pImgOnPress = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CTransparentSwitchButton::strOnDisable;
	m_pImgOnDiable = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CTransparentSwitchButton::strOnOver;
	m_pImgOnOver = CSrcManage::GetImage( strFile.c_str() );
		
	strFile = strFolder + "//" + CTransparentSwitchButton::strOffNormal;
	m_pImgOffNormal = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CTransparentSwitchButton::strOffPress;
	m_pImgOffPress = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CTransparentSwitchButton::strOffDisable;
	m_pImgOffDiable = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CTransparentSwitchButton::strOffOver;
	m_pImgOffOver = CSrcManage::GetImage( strFile.c_str() );
		
	if ( bInvalidate )
	{
		NOTIF_PARENT_WND
	}	
}

void CTransparentSwitchButton::SetImage( UINT nImgCheckNormal, UINT nImgCheckPress, UINT nImgCheckDiable,UINT nImgUnCheckNormal, UINT nImgUnCheckPress, UINT nImgUnCheckDiable, BOOL bInvalidate /* = FALSE */ )
{
    m_pImgOnNormal = CSrcManage::GetImage( nImgCheckNormal, "PNG"  );
    m_pImgOnPress = CSrcManage::GetImage( nImgCheckPress, "PNG"  );
    m_pImgOnDiable = CSrcManage::GetImage( nImgCheckDiable, "PNG"  );

    m_pImgOffNormal = CSrcManage::GetImage( nImgUnCheckNormal, "PNG"  );
    m_pImgOffPress = CSrcManage::GetImage( nImgUnCheckPress, "PNG"  );
    m_pImgOffDiable = CSrcManage::GetImage( nImgUnCheckDiable, "PNG" );
    if ( bInvalidate )
    {
        NOTIF_PARENT_WND
    }	
}

void CTransparentSwitchButton::SetBindWnd( HWND hdl )
{
    m_hBindWnd = hdl;
    ::SendMessage( hdl, WM_BIND_WND, (WPARAM)this->GetSafeHwnd(), 0 );   
}

HWND CTransparentSwitchButton::GetBindWnd()
{
    return m_hBindWnd;
}

void CTransparentSwitchButton::OnTouchButtonDown( CPoint pt )
{	
 	this->SetFocus();
                    /*��������Ե�������˫���������᳡����ѡ����ʾ��ģ���������������ص��ʱ�ɿ���ģ�����ؼ������ϴε�״̬�ٳ����µ�״̬
					  reason������downʱ��ԭ�ؼ�δʧȥ���㣬����upʱԭ�ؼ��Ż�ʧȥ���㣬��������򲻴��ڸ�����
					  2012-6-20 by yjj
	                  */
    SetCapture();
    m_emStatus = emStatusPress;		

//     CString str;
//     str.Format( "OnTouchButtonDown, m_emStatus: %d, m_bOn: %d \n", m_emStatus, m_bOn );
//     OutputDebugString(str);

    NOTIF_PARENT_WND_IMMEDIATLY_DRAW 
}


//#define WM_GESTURE                      0x0119
//#define WM_GESTURENOTIFY                0x011A
LRESULT CTransparentSwitchButton::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
    // TODO: Add your specialized code here and/or call the base class
    if ( message == WM_TOUCH_BUTTONDOWN )
    {
        int nX = LOWORD( lParam );
        int nY = HIWORD( lParam );
        //��Ļ�����
        if ( m_emStatus != emStatusPress )
        {
            OnTouchButtonDown( CPoint( nX, nY ) );  
          //  TRACE("\n---touchButtown ----\n");
        }       
    }
    else if ( message == WM_LBUTTONUP )
    {
        m_emStatus  = emStatusNormal;
    }
    /* else if ( message == WM_GESTURENOTIFY )
    {
        CString str;
        str.Format( "WM_GESTURENOTIFY, m_emStatus: %d, m_bOn: %d \n", m_emStatus, m_bOn );
        OutputDebugString(str);
    }
    else if ( message == WM_MOUSEACTIVATE )
    {   
        CString str;
        str.Format( "WM_MOUSEACTIVATE, m_emStatus: %d, m_bOn: %d \n", m_emStatus, m_bOn );
        OutputDebugString(str);
    } ������*/  
    return CButton::DefWindowProc(message, wParam, lParam);
}

LRESULT CTransparentSwitchButton::OnMouseLeave( WPARAM wParam, LPARAM lParam ) 
{	
	if( IsWindowEnabled() && emStatusNormal != m_emStatus )
    {
		m_emStatus = emStatusNormal;
		NOTIF_PARENT_WND
    }
	m_bMouseTrack = TRUE;
	return S_OK;
}

LRESULT CTransparentSwitchButton::OnMouseHover( WPARAM wParam, LPARAM lParam )
{	
	if ( IsWindowEnabled() && emStatusNormal == m_emStatus )
	{
		m_emStatus = emStatusOver;					
		NOTIF_PARENT_WND			
	}
	return S_OK;
}
