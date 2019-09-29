// TransparentCheckButton.cpp : implementation file
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
// CTransparentCheckButton
#define CHECKBUTTON_INTERVAL  17   //ͼ�������ֵļ��

const CString CTransparentCheckButton::strCheckNormal = "CheckNormal.png";
const CString CTransparentCheckButton::strCheckPress = "CheckPress.png";
const CString CTransparentCheckButton::strCheckDisable = "CheckDisable.png";
const CString CTransparentCheckButton::strCheckOver = "CheckOver.png";
const CString CTransparentCheckButton::strUnCheckNormal = "UnCheckNormal.png";
const CString CTransparentCheckButton::strUnCheckPress = "UnCheckPress.png";
const CString CTransparentCheckButton::strUnCheckDisable = "UnCheckDisable.png";
const CString CTransparentCheckButton::strUnCheckOver = "UnCheckOver.png";
template<> WNDPROC TransparentAssist<CTransparentCheckButton>::m_pWndProc = NULL;
CTransparentCheckButton::CTransparentCheckButton()
{
	RegsiterWndProc();
    m_emStatus = emStatusNormal;
    m_pImgCheckNormal = NULL;
    m_pImgCheckPress = NULL;
    m_pImgCheckDiable = NULL;
	m_pImgCheckOver = NULL;

    m_pImgUnCheckNormal = NULL;
    m_pImgUnCheckPress = NULL;
    m_pImgUnCheckDiable = NULL;
	m_pImgUnCheckOver = NULL;

	m_bShowText = TRUE;

	m_cStringFormat.SetFormatFlags( StringFormatFlagsNoWrap | StringFormatFlagsMeasureTrailingSpaces );   
	m_cStringFormat.SetLineAlignment( StringAlignmentCenter );
	m_cStringFormat.SetAlignment( StringAlignmentNear );

	m_pFont = CSrcManage::GetFont( "΢���ź�", 13 );
	m_coText = Color( 146, 157, 183 );

	m_hBindWnd = 0;
	m_nFontSpan = CHECKBUTTON_INTERVAL;
    m_bMouseTrack = TRUE;
	m_strFontName = "΢���ź�";
	m_bTouchUp = FALSE;
}

CTransparentCheckButton::~CTransparentCheckButton()
{
}


BEGIN_MESSAGE_MAP(CTransparentCheckButton, CButton)
    //{{AFX_MSG_MAP(CTransparentCheckButton)
    ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
    //}}AFX_MSG_MAP
    ON_MESSAGE( WM_REDRAW_UI, OnRedrawUI )
    ON_MESSAGE(BM_SETCHECK , OnBMSetCheck)
	ON_MESSAGE( WM_BIND_WND_HIDE, OnBindWndHide )
	ON_MESSAGE( WM_MOUSELEAVE, OnMouseLeave )
	ON_MESSAGE( WM_MOUSEHOVER, OnMouseHover )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransparentCheckButton message handlers

LRESULT CTransparentCheckButton::OnBindWndHide( WPARAM wParam, LPARAM lParam )
{ 
	if ( m_hBindWnd != 0 )
	{
		SetCheck( BST_UNCHECKED ); 
		NOTIF_PARENT_WND  
	}
	
	return S_OK;
}

void CTransparentCheckButton::OnMouseMove(UINT nFlags, CPoint point)
{
	if ( !IsWindowEnabled() || !IsWindowVisible() )
	{
		return;
	}

    CRect rect;    
    GetClientRect( &rect );

	if ( m_pImgCheckOver != NULL && m_pImgUnCheckOver != NULL )
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
		
        NOTIF_PARENT_WND 
    }
}

LRESULT CTransparentCheckButton::OnRedrawUI( WPARAM wParam, LPARAM lParam )
{  
    Graphics *pGraphics = (Graphics*)wParam;

    HWND hGraphWnd = (HWND )lParam;
    CWnd * pGraphWnd = FromHandle(hGraphWnd);


    m_hParent = (HWND)lParam;
    if ( IsWindowVisible() == FALSE || GetParent() == NULL || pGraphics == NULL  || pGraphWnd == NULL )
    {
        return S_FALSE;
    }

	if (  m_pImgCheckNormal == NULL &&  m_pImgUnCheckNormal == NULL )
	{
		 return S_FALSE;
	}
 
    

    CRect cRect;
    GetWindowRect( &cRect );
    POINT point = cRect.TopLeft();

   // GetParent()->ScreenToClient( &point );
    pGraphWnd->ScreenToClient( &point );

    Image *pImage = NULL;
    switch ( m_emStatus )
    {
    case emStatusNormal:
        pImage = GetCheck() == BST_CHECKED ? m_pImgCheckNormal : m_pImgUnCheckNormal;
        break;
    case emStatusPress:
        pImage = GetCheck() == BST_CHECKED ? m_pImgCheckPress : m_pImgUnCheckPress;
        break;
	case emStatusOver:
		pImage = GetCheck() == BST_CHECKED ? m_pImgCheckOver : m_pImgUnCheckOver;
    }

    if ( FALSE == IsWindowEnabled() )
    {
        pImage = GetCheck() == BST_CHECKED ? m_pImgCheckDiable : m_pImgUnCheckDiable;
    }

    if ( NULL != pImage )
    {
        pGraphics->DrawImage( pImage, point.x, point.y, cRect.Width()/*pImage->GetWidth()*/, cRect.Height()/*pImage->GetHeight() */);

         if ( TRUE == m_bShowText )
         {
             SolidBrush brush( m_coText ); 
			 //�����ֲ���ƽ������ȥë��
			 if ( m_strFontName != _T("����") )
			 {
				 pGraphics->SetTextRenderingHint(TextRenderingHint(TextRenderingHintAntiAlias));
			 }


             CString strText = "";
             GetWindowText( strText );
          
			 float fLeft = point.x + pImage->GetWidth() + m_nFontSpan;
			 int nWidth = cRect.Width() - pImage->GetWidth() - m_nFontSpan;
				
			 BSTR bstr = strText.AllocSysString();

			 pGraphics->DrawString( bstr, -1, m_pFont, RectF( fLeft, (float)point.y, 300, cRect.Height() ), &m_cStringFormat, &brush );

			 if ( m_strFontName != _T("����") )
			 {
				 pGraphics->SetTextRenderingHint(TextRenderingHint(TextRenderingHintSystemDefault));
			 }
			 
			 SysFreeString( bstr );
         }
    }
	
//     if ( cRect.Width() != m_pImgCheckNormal->GetWidth()
//          || cRect.Height() != m_pImgCheckNormal->GetHeight() )
//     {
//         SetWindowPos( NULL, 0, 0, m_pImgCheckNormal->GetWidth(), m_pImgCheckNormal->GetHeight(), SWP_NOMOVE|SWP_NOACTIVATE );
//     }

    return S_OK;  
}

LRESULT CTransparentCheckButton::OnBMSetCheck(WPARAM wparam, LPARAM lParam)
{
    DefWindowProc( BM_SETCHECK, wparam, lParam );

    NOTIF_PARENT_WND

    return 0;
}

void CTransparentCheckButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_emStatus = emStatusPress;
	NOTIF_PARENT_WND
    CButton::OnLButtonDown(nFlags, point);
}

void CTransparentCheckButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
    if ( m_emStatus != emStatusPress )
    {
		CButton::OnLButtonUp(nFlags, point); 
        ReleaseCapture();
        return;
    }

	m_emStatus = emStatusNormal;
    NOTIF_PARENT_WND
    PostMessage( WM_BUTTON_CLICK );	 

    CButton::OnLButtonUp(nFlags, point);
}

//���bug��˫��ɸѡ�ؼ���ɸѡ��δ��������ɸѡ�ؼ�״̬����  20131111  by xhx
void CTransparentCheckButton::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	m_emStatus = emStatusPress;
	NOTIF_PARENT_WND
    CButton::OnLButtonDblClk(nFlags, point);
}

void CTransparentCheckButton::OnTouchButtonDown( CPoint pt )
{	
	m_bTouchUp = FALSE;
    m_emStatus = emStatusPress;	

	SetCapture();
    NOTIF_PARENT_WND 
}
void CTransparentCheckButton::OnTouchButtonUp()
{
    if ( m_emStatus != emStatusPress  )
    {
        ReleaseCapture();   
        return;
    } 
    
    m_emStatus = emStatusNormal;
	
    NOTIF_PARENT_WND
    
    ReleaseCapture();	
}

LRESULT CTransparentCheckButton::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
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
        }  
    }
	if ( message == WM_LBUTTONUP )
	{
		m_emStatus = emStatusNormal;
	}
    else if ( message == WM_TOUCH )
    {
        if ( m_bTouchUp )
        {
            return CButton::DefWindowProc(message, wParam, lParam);
        }
		
        WINSDK_GetTouchInputInfo _WINSDK_GetTouchInputInfo;
        
        UINT cInputs = LOWORD(wParam);
        TOUCHINPUT tInput;
		
        HINSTANCE hInstLibrary = LoadLibrary("windowsexsdk.dll");
        if (hInstLibrary != NULL)
        {
            _WINSDK_GetTouchInputInfo = (WINSDK_GetTouchInputInfo)GetProcAddress( hInstLibrary, "WINSDK_GetTouchInputInfo" );
            if ( _WINSDK_GetTouchInputInfo != NULL )
            {
                _WINSDK_GetTouchInputInfo( lParam, cInputs, tInput );
				
                if ( tInput.dwFlags & TOUCHEVENTF_DOWN )
                {
                    m_bTouchUp = FALSE;
                    //��ʱ�Ѿ���Ӧ��WM_TOUCH_BUTTONDOWN
                    //OnTouchButtonDown( CPoint( 0, 0 ) );
                }
                if ( tInput.dwFlags & TOUCHEVENTF_UP )
                {
                    //��Ӧ�����ſ�����Ϣ����ֹ��ťһֱ����
                    //CString msg;
                    //msg.Format( _T("\nCTransparentBtn WM_TOUCH,TOUCHEVENTF_UP.dwFlags: %d \n"), tInput.dwFlags );
					//AfxOutputDebugString( msg );
					
                    m_bTouchUp = TRUE;
					
                    //OnLButtonUp( 0, CPoint( 0, 0 ) );  
					OnTouchButtonUp();
                }
				
            }
        }    
    }
    return CButton::DefWindowProc(message, wParam, lParam);
}
void CTransparentCheckButton::SetShowText( BOOL bShow /* = FALSE  */)
{
	m_bShowText = bShow;
}

void CTransparentCheckButton::SetImage( CString strFolder, BOOL bInvalidate /* = FALSE */ )
{
	String strFile = strFolder + "//" + CTransparentCheckButton::strCheckNormal;
	m_pImgCheckNormal = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CTransparentCheckButton::strCheckPress;
	m_pImgCheckPress = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CTransparentCheckButton::strCheckDisable;
	m_pImgCheckDiable = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CTransparentCheckButton::strCheckOver;
	m_pImgCheckOver = CSrcManage::GetImage( strFile.c_str() );

	strFile = strFolder + "//" + CTransparentCheckButton::strUnCheckNormal;
	m_pImgUnCheckNormal = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CTransparentCheckButton::strUnCheckPress;
	m_pImgUnCheckPress = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CTransparentCheckButton::strUnCheckDisable;
	m_pImgUnCheckDiable = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CTransparentCheckButton::strUnCheckOver;
	m_pImgUnCheckOver = CSrcManage::GetImage( strFile.c_str() );
	if ( bInvalidate )
	{
		NOTIF_PARENT_WND
	}	
}

void CTransparentCheckButton::SetImage( UINT nImgCheckNormal, UINT nImgCheckPress, UINT nImgCheckDiable, UINT nImgUnCheckNormal, UINT nImgUnCheckPress, UINT nImgUnCheckDiable, UINT nImgCheckOver, UINT nImgUnCheckOver, BOOL bInvalidate /* = FALSE */ )
{
	m_pImgCheckNormal = CSrcManage::GetImage( nImgCheckNormal, "PNG"  );
	m_pImgCheckPress = CSrcManage::GetImage( nImgCheckPress, "PNG"  );
	m_pImgCheckDiable = CSrcManage::GetImage( nImgCheckDiable, "PNG"  );
	m_pImgCheckOver = CSrcManage::GetImage( nImgCheckOver, "PNG"  );
	m_pImgUnCheckNormal = CSrcManage::GetImage( nImgUnCheckNormal, "PNG"  );
	m_pImgUnCheckPress = CSrcManage::GetImage( nImgUnCheckPress, "PNG"  );
	m_pImgUnCheckDiable = CSrcManage::GetImage( nImgUnCheckDiable, "PNG" );
	m_pImgUnCheckOver = CSrcManage::GetImage( nImgUnCheckOver, "PNG"  );
	if ( bInvalidate )
	{
		NOTIF_PARENT_WND
	}	
}

CSize CTransparentCheckButton::GetImageSize()
{
    CSize sz(0);
    if ( m_pImgCheckNormal != NULL )
    {
        sz.cx = m_pImgCheckNormal->GetWidth();
        sz.cy = m_pImgCheckNormal->GetHeight();
    }
	else if ( m_pImgUnCheckNormal != NULL )
	{
        sz.cx = m_pImgUnCheckNormal->GetWidth();
        sz.cy = m_pImgUnCheckNormal->GetHeight();
	}
    
    return sz;
}

void CTransparentCheckButton::SetBindWnd( HWND hdl )
{
    m_hBindWnd = hdl;
    ::SendMessage( hdl, WM_BIND_WND, (WPARAM)this->GetSafeHwnd(), 0 );
}

HWND CTransparentCheckButton::GetBindWnd()
{
    return m_hBindWnd;
}

void CTransparentCheckButton::SetFont( unsigned int dwFontSize, CString strFontFamily,BOOL bInvalidate )
{
	m_strFontName = strFontFamily;
	m_pFont = CSrcManage::GetFont( strFontFamily, dwFontSize );
	if ( bInvalidate )
	{
		NOTIF_PARENT_WND
	}
}

LRESULT CTransparentCheckButton::OnMouseLeave( WPARAM wParam, LPARAM lParam ) 
{	
	if( IsWindowEnabled() && m_emStatus != emStatusNormal )
    {
		m_emStatus = emStatusNormal;
		NOTIF_PARENT_WND
    }
	m_bMouseTrack = TRUE;
	return S_OK;
}

LRESULT CTransparentCheckButton::OnMouseHover( WPARAM wParam, LPARAM lParam ) 
{	
	if ( IsWindowEnabled() && m_emStatus == emStatusNormal )
	{
		m_emStatus = emStatusOver;					
		NOTIF_PARENT_WND			
	}
	return S_OK;
}