// TransparentBaseDlg.cpp : implementation file
//

#include "stdafx.h"
 
#include "TransparentDlgBase.h"
 
//#include "Utility.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransparentBaseDlg dialog
const CString CTransparentDlgBase::strLeft = "Left.png";
const CString CTransparentDlgBase::strMid = "Middle.png";
const CString CTransparentDlgBase::strRight = "Right.png";
const CString CTransparentDlgBase::strTop = "Top.png";
const CString CTransparentDlgBase::strBottom = "Bottom.png";

std::vector<CWnd*> CTransparentDlgBase::m_vctIgnoreWnd;


PFN_SetLayeredWindowAttributes CTransparentDlgBase::m_s_pfnSetLayeredWindowAttributes = NULL;
PFN_UpdateLayeredWindow CTransparentDlgBase::m_s_pfnUpdateLayeredWindow = NULL;

 


CTransparentDlgBase::CTransparentDlgBase(UINT nIDTemplate, CWnd* pParent /*=NULL*/)
	: CDialog(nIDTemplate, pParent)
{
	//{{AFX_DATA_INIT(CTransparentBaseDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_bNeedDeleteImg = false;
    m_pImageBK = NULL;
	m_bIsBkStretch = FALSE;
    m_bTransparentWithoutBK = FALSE;
    m_bReadyToRedrawUI = FALSE;
    m_bRedrawUIImediately = FALSE;
	m_byteSourceConstantAlpha = 255;
 
    m_bCanMove = FALSE;
    m_bAutoHide = FALSE;
    m_hBindWnd = 0;
    m_strImgPath.Empty();
	m_hDcMem = NULL;
	m_hBtMap = NULL;
    m_bChildDlg = TRUE;
}


void CTransparentDlgBase::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTransparentBaseDlg)
	//}}AFX_DATA_MAP
}

CTransparentDlgBase::~CTransparentDlgBase()
{
	if ( m_bNeedDeleteImg && m_pImageBK != NULL )
	{
		delete m_pImageBK;
	}

	if ( NULL != m_hDcMem )
	{
		::DeleteDC ( m_hDcMem ); 
	}
	
	if ( NULL != m_hBtMap )
	{
		::DeleteObject( m_hBtMap )  ; 
	}

 
}

BEGIN_MESSAGE_MAP(CTransparentDlgBase, CDialog)
	//{{AFX_MSG_MAP(CTransparentBaseDlg)
    ON_WM_TIMER()
    ON_WM_SHOWWINDOW()
    ON_WM_ERASEBKGND()
    ON_WM_ACTIVATE()
    ON_WM_LBUTTONDOWN()
    ON_WM_WINDOWPOSCHANGING()
	ON_WM_SIZE()
    //ON_WM_WINDOWPOSCHANGED()
	//ON_WM_PAINT()
    //}}AFX_MSG_MAP
    ON_MESSAGE( WM_REDRAW_UI, OnRedrawUI )
    ON_MESSAGE( WM_BIND_WND, OnBindWnd )
	ON_MESSAGE( WM_HIDE_WND, OnHideWnd )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransparentBaseDlg message handlers

BOOL CTransparentDlgBase::OnInitDialog() 
{
	CDialog::OnInitDialog(); 

	//2012.11.28 by yjj
	LONG lStyle = ::GetWindowLong(m_hWnd, GWL_STYLE);
	if( lStyle & WS_CHILDWINDOW  )
	{
		m_bChildDlg = TRUE;
	 	return TRUE;
	}
	else
	{
		m_bChildDlg = FALSE; 
	} 
 
	// TODO: Add extra initialization here
    HMODULE hUser32Dll = ::GetModuleHandle( _T("user32.dll") );
    ASSERT(hUser32Dll);

    if( NULL == m_s_pfnSetLayeredWindowAttributes )
    {
        m_s_pfnSetLayeredWindowAttributes = (PFN_SetLayeredWindowAttributes)::GetProcAddress( hUser32Dll, "SetLayeredWindowAttributes" );
        ASSERT(m_s_pfnSetLayeredWindowAttributes);
    }

    if( NULL == m_s_pfnUpdateLayeredWindow )
    {
        m_s_pfnUpdateLayeredWindow = (PFN_UpdateLayeredWindow)::GetProcAddress( hUser32Dll, "UpdateLayeredWindow" );
        ASSERT(m_s_pfnUpdateLayeredWindow);
	}


	//2012-7-10 by yjj
	if ( hUser32Dll )
	{
		FreeLibrary( hUser32Dll );
	}




	InitMemDC();

	::SetWindowLong( m_hWnd, GWL_EXSTYLE, GetWindowLong( m_hWnd, GWL_EXSTYLE) | WS_EX_LAYERED );
    if ( m_pImageBK != NULL  )
    {  
        RedrawUI();
    }
   
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTransparentDlgBase::OnTimer(UINT nIDEvent) 
{
	if ( nIDEvent == 1 )
	{
		m_bReadyToRedrawUI = FALSE;
		KillTimer( 1 );
		
		RedrawUI();
	}

    CDialog::OnTimer( nIDEvent );
}

BOOL CTransparentDlgBase::OnEraseBkgnd(CDC* pDC) 
{
    PostMessage( WM_REDRAW_UI, NULL, NULL );

    return CDialog::OnEraseBkgnd(pDC);
}

void CTransparentDlgBase::OnPaint() 
{
    
}

LRESULT CTransparentDlgBase::OnRedrawUI( WPARAM wParam, LPARAM lParam )
{  

	if ( m_pImageBK == NULL && FALSE == m_bTransparentWithoutBK )
	{
		return S_FALSE;
	}
	
	bool bHandle = ChildDlgRedrawUI( wParam, lParam );
	if ( bHandle )
	{//˵����ǰ����Ϊchild���ڣ��һ�����Ϣ�ѵõ�����
	   return S_OK;
	}

//----------------------��child����--------------------------


//2011-9-16 ���ص�ʱ��Ҳ���ƣ���ֹ�ٴ���ʾ��ʱ����˸��ԭ����
//     if ( IsWindowVisible() == FALSE )
//     {
//         return S_FALSE;
//     }

    //lParamΪTRUEʱǿ��ˢ��
    m_bRedrawUIImediately = (BOOL)lParam;
    if ( TRUE == m_bRedrawUIImediately )
    {
        RedrawUI();

        return S_OK;
    }

    // ����ˢ�£����Ч��
    if ( TRUE == m_bReadyToRedrawUI )
    {
     //   TRACE( "[CTransparentBaseDlg::OnRedrawUI] m_bReadyToRedrawUI = TRUE\n" );

        return S_OK;
    }

    m_bReadyToRedrawUI = TRUE;
    SetTimer( 1, 20, NULL );

    return S_OK;    
}
 
bool CTransparentDlgBase::ChildDlgRedrawUI( WPARAM wParam, LPARAM lParam )
{
	bool bHandle = false;
	if ( m_bChildDlg )
	{
		bHandle = true;
	} 
	 
	if ( m_bChildDlg && IsWindowVisible() )  
    {
		Graphics *pGraphics = (Graphics*)wParam;
		
		if ( pGraphics == NULL )
		{
			// Ϊ�յĻ����������ӿؼ������ģ���Ҫ���򸸴���ת��
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
			
			if ( !m_bIsBkStretch )
			{
				pGraphics->DrawImage( m_pImageBK, point.x, point.y,/* m_pImageBK->GetWidth()*/cRect.Width(), /*m_pImageBK->GetHeight()*/cRect.Height() );
			}
			else
			{
				pGraphics->DrawImage( m_pImageBK, point.x, point.y, m_pImageBK->GetWidth(), m_pImageBK->GetHeight() );
			}
		
		}
		
    }

	return bHandle;
}

void CTransparentDlgBase::RedrawUI()
{        
    if ( m_pImageBK == NULL && FALSE == m_bTransparentWithoutBK )
    {  
        //PrtMsg("\n[CTransparentBaseDlg::RedrawUI]: return: m_pImageBK == NULL && FALSE == m_bTransparentWithoutBK   handle=%d \n ", m_hWnd);
        return;
    } 
 
    
    RECT rc;
    ::GetWindowRect( m_hWnd, &rc );
    POINT ptSrc = { 0, 0 };
    POINT ptWinPos = { rc.left, rc.top };
    SIZE szWin; 
    {
        szWin.cx = rc.right - rc.left;
        szWin.cy = rc.bottom - rc.top;
    }

//     PrtMsg("\n[CTransparentBaseDlg::RedrawUI]handle=%p,isVisible=%d,left:%d  top:%d  width:%d  height:%d\n",
//         m_hWnd,IsWindowVisible() , ptWinPos.x,ptWinPos.y,rc.right - rc.left, rc.bottom - rc.top );


    BLENDFUNCTION stBlend = { AC_SRC_OVER, 0, m_byteSourceConstantAlpha, AC_SRC_ALPHA };

    //HDC hDC = ::GetDC(NULL);  2012-7-2 by yjj
	HDC hDC =  ::GetDC(  GetSafeHwnd()  );
    
    if( NULL != m_hDcMem )   
    {   
         
        Graphics graph( m_hDcMem );
        graph.Clear( Color( 0, 0, 0, 0 ) );

        graph.SetSmoothingMode( SmoothingModeHighQuality );
        
       
        //������ؽ���������ʾ���� �ٴ���ʾ��������˸������
        if ( IsWindowVisible() )
        { 
            if ( NULL != m_pImageBK )
            {
                graph.DrawImage( m_pImageBK, 0, 0, szWin.cx, szWin.cy );
                // PrtMsg("\n[CTransparentBaseDlg::RedrawUI]graph.DrawImage:width:%d  height:%d\n",szWin.cx, szWin.cy  );
            }
            
            
            // ���������Ӵ���
            DrawChildWnd( &graph, GetSafeHwnd() );
        }
        
	/*	
	
	    static nStatic = 1;
		if ( nStatic == 100 )
		{
			nStatic = 1 ;
		} 
   
		
		 // �ѻ��Ƶ�ͼƬ��ӡ���ļ������ҿ���͸��������
	    if ( IsWindowVisible() && m_pImageBK != NULL )
	    {
			char abyText[128] = { 0 };
			::GetWindowText( GetSafeHwnd(), abyText, 128 );
			CString strFileName;
			strFileName.Format("c:\\cncMap\\cncMap%d_%s.bmp", nStatic,abyText );
			nStatic++;
            SaveBmp(  m_hBtMap ,  strFileName);
	    }
       
	  */

	 

        m_s_pfnUpdateLayeredWindow( m_hWnd,
                                    hDC,
                                    &ptWinPos,
                                    &szWin,
                                    m_hDcMem,
                                    &ptSrc,
                                    0,
                                    &stBlend,
                                    ULW_ALPHA
                                   );

         
    } 
   
    //::DeleteDC( hDC ); 2012-7-2 by yjj
    ::ReleaseDC( GetSafeHwnd(), hDC );
}

void CTransparentDlgBase::DrawChildWnd( Graphics *pGraphics, HWND hParentWnd )
{
    HWND hwndChild = ::GetWindow( hParentWnd, GW_CHILD ); 
     

    while( hwndChild != NULL )
    {   
//          RECT rc ;
//         ::GetWindowRect( hwndChild , &rc );
//         PrtMsg("\n  [CTransparentBaseDlg::DrawChildWnd] ParentHandle= %p , childHandle=%p top:%d left:%d width:%d heigth:%d ",
//             hParentWnd, hwndChild, rc.top, rc.left, rc.right - rc.left,rc.bottom - rc.top );
        
        // ֪ͨ�Ӵ��ڽ��л���
        ::SendMessage( hwndChild, WM_REDRAW_UI, (WPARAM)pGraphics, (LPARAM)m_hWnd );
         

        DrawChildWnd( pGraphics, hwndChild );
// #ifdef _DEBUG
//         CString strWindowText;
//         char abyText[128] = { 0 };
//         ::GetWindowText( hwndChild, abyText, 128 );
//         strWindowText = abyText;
//         TRACE( strWindowText );
// #endif // _DEBUG

        hwndChild = ::GetWindow( hwndChild, GW_HWNDNEXT );
    }
}

void CTransparentDlgBase::OnShowWindow(BOOL bShow, UINT nStatus) 
{   
    if ( m_hBindWnd != 0 && !bShow )
    {
        // ����а󶨵Ĵ��ڣ���֪ͨ�󶨴����󶨴��� 
        CPoint   mousepos; 
        ::GetCursorPos(&mousepos); 
        CPoint   CurPos(mousepos);

        ::ScreenToClient(m_hBindWnd, &mousepos );

        CRect rect;
        ::GetClientRect(m_hBindWnd, &rect );
		//�������أ��粻���ڴ����ϻ�󶨴��������أ���֪ͨ�󶨴��� dyy �����������Ŀ��ֱ�ӵ����ַ�� ѡ��״̬����
        if (  !rect.PtInRect( mousepos ) ||!::IsWindowVisible( m_hBindWnd )  )
        {     
            ::SendMessage/*PostMessage*/(m_hBindWnd, WM_BIND_WND_HIDE, 0, 0 );  
        }  
    }

    CDialog::OnShowWindow(bShow, nStatus); 
    
  
    // TODO: Add your message handler code here
   // if ( TRUE == bShow )  2011-9-16 ���ص�ʱ��Ҳ���ƣ���ֹ�ٴ���ʾ��ʱ����˸��ԭ����
    {
        PostMessage( WM_REDRAW_UI, NULL, NULL );
    }

}

s32 CTransparentDlgBase::GetWindowWidth()
{
	if ( m_pImageBK == NULL )
	{
		return 0;
	}
	return m_pImageBK->GetWidth();
}

s32 CTransparentDlgBase::GetWindowHeight()
{
	if ( m_pImageBK == NULL )
	{
		return 0;
	}
	return m_pImageBK->GetHeight();
}



void CTransparentDlgBase::SetImage( CString strPath, BOOL bInvalidate /* = FALSE */ )
{
   	
    //	if ( strPath.IsEmpty() || strPath.Find( '.' ) >= 0 )
    // 	{
    // 		m_pImage = CSrcManage::GetImage( strPath );		
    // 	}
   
    //����Ѿ����ع���ͬ·����ͼƬ��ֱ�ӷ���  2011-10-11 by yjj 
    if ( !m_strImgPath.IsEmpty() && strPath == m_strImgPath && m_pImageBK != NULL )
    {
        return;
    }
    m_strImgPath = strPath;

	if ( m_pImageBK != NULL && m_bNeedDeleteImg )
	{ 
		delete m_pImageBK  ;
		m_pImageBK = NULL; 
		
    }
   
    if ( strPath.Find( "windowBkg" ) >= 0 )
    {   
        String strFile = strPath + "\\" + strLeft;
        m_pImgLeft = CSrcManage::GetImage( strFile.c_str() );
        strFile = strPath + "\\" +  strMid;
        m_pImgMiddle = CSrcManage::GetImage( strFile.c_str() );
        strFile = strPath + "\\" +  strRight;
        m_pImgRight = CSrcManage::GetImage( strFile.c_str() );
        
        CRect cRect;
        this->GetWindowRect( &cRect );
        
      
        if ( m_pImageBK == NULL )
        {
			m_bNeedDeleteImg = true;
            m_pImageBK = CSrcManage::MosaicHoriImage( cRect,m_pImgLeft, m_pImgRight, m_pImgMiddle );
        }
        
    }
    else if ( strPath.Find( "callDlgBkg" ) >= 0  || strPath.Find( "callDlgBkgEx" ) >= 0)
    {   
        
        String strFile = strPath + "\\" +  strTop;
        m_pImgLeft = CSrcManage::GetImage( strFile.c_str() );
        strFile = strPath + "\\" +  strMid;
        m_pImgMiddle = CSrcManage::GetImage( strFile.c_str() );
        strFile = strPath + "\\" +  strBottom;
        m_pImgRight = CSrcManage::GetImage( strFile.c_str() );
        
        CRect cRect;
        this->GetWindowRect( &cRect );        
       
        m_bNeedDeleteImg = true;
        m_pImageBK = CSrcManage::MosaicVertImage( cRect,m_pImgLeft, m_pImgRight, m_pImgMiddle );
     
    }
    else
    {
		m_bNeedDeleteImg = false;
        m_pImageBK = CSrcManage::GetImage( strPath );      
    }
    SetImage( m_pImageBK, bInvalidate );
}

void CTransparentDlgBase::SetImage( Image* pImage, BOOL bInvalidate /* = FALSE */ )
{   
    m_pImageBK = pImage;
   
	
    if ( bInvalidate  )
    {
        PostMessage( WM_REDRAW_UI, 0, 0 );
    }
}

void CTransparentDlgBase::OnLButtonDown(UINT nFlags, CPoint point) 
{
    // TODO: Add your message handler code here and/or call default
    if (m_bCanMove)
    {
        //��ֹ��ʾ�ƶ����δ����
        ::SystemParametersInfo(SPI_SETDRAGFULLWINDOWS,TRUE,NULL,0);
        //�Ǳ������ƶ���������
        PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y)); 
    }
	else
    {
        //��סtitlebar�����϶������ƶ�
		if ( GetStyle() & WS_CHILD )
        {
            CWnd* pWnd = GetParent();
            if ( pWnd != NULL )
            {
                if ( CTransparentDlgBase* pDlg = dynamic_cast<CTransparentDlgBase*>( pWnd ) )
                {
                    if ( pDlg->GetMoveStatus() )
                    {
                        pWnd->SendMessage( WM_LBUTTONDOWN, nFlags, MAKELPARAM(point.x,point.y) );
                    }                    
                }            
            }
        }     
    }

    CDialog::OnLButtonDown(nFlags, point);
}

void CTransparentDlgBase::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
     
    if ( !m_bChildDlg   && nState == WA_INACTIVE )
    {
		if(m_bAutoHide)
		{
			bool bChildActivate = false;
			//�����Owner���ڣ�������
			CWnd* pWndTemp = pWndOther;
			while ( pWndTemp != NULL )
			{
				if ( pWndTemp == this )
				{
				  bChildActivate = true;
				  break;
				}
				pWndTemp = pWndTemp->GetOwner();	
			}
			if ( bChildActivate )
			{
				return;
			} 
  

			//����ǿ��Ժ��ԵĴ��ڣ�Ҳ������
			vector<CWnd*>::iterator iter = m_vctIgnoreWnd.begin();
			while( iter != m_vctIgnoreWnd.end() )
			{
				if ( *iter == pWndOther )
				{
				  return;
				}
				iter++;
			}  
		    //ʹ��WM_SHOWWINDOW�������صĴ��ڣ��ڵ��������ͼ����Ի���ʾ������ֱ�ӵ���showWindow���У�����ԭ��δ�鵽���鵽��ɲ����ڴ� 2013.1.8  yjj
		    this->PostMessage(/*WM_SHOWWINDOW*/WM_HIDE_WND,FALSE, SW_OTHERUNZOOM );
  
		    //���غ󣬽��㻹��Owner���� 
		    HWND hOwner = this->m_hWndOwner;
		    pWndTemp  = FromHandle(hOwner);
			if (  pWndTemp != NULL  )
			{
				// pWndTemp->SetFocus(); 
				pWndTemp->PostMessage( WM_SETFOCUS, 0, 0 );
			}
		}  
    }
    CDialog::OnActivate(nState, pWndOther, bMinimized); 
}

 
LRESULT CTransparentDlgBase::OnHideWnd( WPARAM wParam, LPARAM lParam )
{
	ShowWindow(SW_HIDE);
	return S_OK;
}

void CTransparentDlgBase::AddIgnoreWnd( CWnd* pWnd )
{
    vector<CWnd*>::iterator iter = m_vctIgnoreWnd.begin();
    while( iter != m_vctIgnoreWnd.end() )
    {
        if ( *iter == pWnd )
        {
            return;
        }
        iter++;
    }
    m_vctIgnoreWnd.push_back( pWnd );
}

 
LRESULT CTransparentDlgBase::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
    // TODO: Add your specialized code here and/or call the base class
    
    return CDialog::DefWindowProc(message, wParam, lParam);
}

LRESULT CTransparentDlgBase::OnBindWnd( WPARAM wParam, LPARAM lParam )
{
	HWND bindWnd = (HWND)wParam;
	if ( m_hBindWnd != NULL && m_hBindWnd != bindWnd )
	{
		::SendMessage(m_hBindWnd, WM_BIND_WND_HIDE, 0, 0 ); 
	}
    
    m_hBindWnd = bindWnd;
    return S_OK;
}

void CTransparentDlgBase::SetBindWnd( HWND hdl )
{
	//�󶨴��ڸı䣬֪ͨԭ�󶨴��ڲ�ѡ��
	if ( m_hBindWnd != NULL && m_hBindWnd != hdl )
	{
		::SendMessage(m_hBindWnd, WM_BIND_WND_HIDE, 0, 0 ); 
	}
	
    m_hBindWnd = hdl;
}

//������غ�����ʾ����ˢ����������
void CTransparentDlgBase::OnWindowPosChanging(WINDOWPOS   FAR*   lpwndpos) 
{   
    if ( IsWindowVisible() )
    {
        PostMessage( WM_REDRAW_UI, 0, 0 );
    }
    
    CDialog::OnWindowPosChanging(lpwndpos); 
} 

// void CTransparentBaseDlg::OnWindowPosChanged( WINDOWPOS* lpwndpos )
// {
//     if ( IsWindowVisible() )
//     {
//         PostMessage( WM_REDRAW_UI, 0, 0 );
//     }
//     
//     CDialog::OnWindowPosChanged(lpwndpos); 
// }


void CTransparentDlgBase::InitMemDC()
{  
	if ( m_bChildDlg )
	{
		return;
	}
	
	if ( NULL != m_hDcMem )
	{
		::DeleteDC ( m_hDcMem ); 
	}

	if ( NULL != m_hBtMap )
	{
		::DeleteObject( m_hBtMap )  ; 
	}

	RECT rc;
    ::GetWindowRect( m_hWnd, &rc );
	SIZE szWin;
	szWin.cx = rc.right - rc.left;
	szWin.cy = rc.bottom - rc.top ; 
	if ( szWin.cy == 0 || szWin.cx == 0 )
	{
		return;
	}


	HDC hDc = ::GetDC( GetSafeHwnd() );
    m_hDcMem =  CreateCompatibleDC(hDc);
	
    BITMAPINFOHEADER stBmpInfoHeader = { 0 };   
    int nBytesPerLine = ((szWin.cx * 32 + 31) & (~31)) >> 3;
    stBmpInfoHeader.biSize = sizeof(BITMAPINFOHEADER);   
    stBmpInfoHeader.biWidth = szWin.cx;   
    stBmpInfoHeader.biHeight = szWin.cy;   
    stBmpInfoHeader.biPlanes = 1;
    stBmpInfoHeader.biBitCount = 32;   
    stBmpInfoHeader.biCompression = BI_RGB;   
    stBmpInfoHeader.biClrUsed = 0;   
    stBmpInfoHeader.biSizeImage = nBytesPerLine * szWin.cy;	
	
    PUINT32 pvBits = NULL;   
    m_hBtMap = ::CreateDIBSection(NULL, (PBITMAPINFO)&stBmpInfoHeader, DIB_RGB_COLORS, (LPVOID*)&pvBits, NULL, 0);
 
    ASSERT(m_hBtMap != NULL);
    if(m_hBtMap)   
    {   
       ::SelectObject( m_hDcMem, m_hBtMap); 
	}

	::ReleaseDC( GetSafeHwnd(), hDc );
   
}


void CTransparentDlgBase::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	InitMemDC();
	// TODO: Add your message handler code here
	
}


 
