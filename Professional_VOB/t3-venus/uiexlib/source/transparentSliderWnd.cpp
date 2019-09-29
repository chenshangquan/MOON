// transparentSliderWnd.cpp: implementation of the CTransparentSliderWnd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "slider.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


const CString CTransparentSliderWnd::strNormalLeft = "NormalLeft.png";
const CString CTransparentSliderWnd::strNormalMid = "NormalMid.png";
const CString CTransparentSliderWnd::strNormalRight = "NormalRight.png";
const CString CTransparentSliderWnd::strHighLightLeft = "HighLightLeft.png";
const CString CTransparentSliderWnd::strHighLightMid = "HighLightMid.png";
const CString CTransparentSliderWnd::strHighLightRight = "HighLightRight.png";
const CString CTransparentSliderWnd::strThumbNormal = "ThumbNormal.png";
const CString CTransparentSliderWnd::strThumbPress = "ThumbPress.png";
/*template<> WNDPROC TransparentAssist<CTransparentSliderWnd>::m_pWndProc = NULL;*/

//disable ͼ��
const CString CTransparentSliderWnd::strDisableLeft = "DisableLeft.png";
const CString CTransparentSliderWnd::strDisableMid = "DisableMid.png";
const CString CTransparentSliderWnd::strDisableRight = "DisableRight.png";
const CString CTransparentSliderWnd::strDisableHighLightLeft = "DisableHighLightLeft.png";
const CString CTransparentSliderWnd::strDisableHighLightMid = "DisableHighLightMid.png";
const CString CTransparentSliderWnd::strDisableHighLightRight = "DisableHighLightRight.png";
const CString CTransparentSliderWnd::strThumbDisable = "ThumbDisable.png";

const CString CTransparentSliderWnd::strBubble = "Bubble.png";
static UINT g_wTimer = 0;

CTransparentSliderWnd::CTransparentSliderWnd(CString strName, CString strUI, CRect rcWnd, CWnd* pWnd, UINT nID, DWORD dStyle, DWORD dwExStyle) 
: CTransparentBaseWnd( rcWnd, pWnd, dStyle, strUI, nID ),m_rectfThumbRect()
{
    m_pImgNormalLeft = NULL;
    m_pImgNormalMiddle = NULL;
    m_pImgNormalRight = NULL;
    
    m_pImgHighLightLeft = NULL;
    m_pImgHighLightMiddle = NULL;
    m_pImgHighLightRight = NULL;
    
    m_pImgThumbNormal = NULL;
    m_pImgThumbPress = NULL;
    
    
    //disable
    m_pImgDisableLeft = NULL;
    m_pImgDisableMid  = NULL ;
    m_pImgDisableRight = NULL ;
    
    m_pImgDisableHighLightLeft = NULL ;
    m_pImgDisableHighLightMid = NULL ;
    m_pImgDisableHighLightRight = NULL ;
    
    m_pImgThumbDisable = NULL ;
	m_pImgBubble = NULL;

    m_emStyle =   emStyleHorz  ;
    
    m_nMaxOffset = 0;
 
    m_nMax = 0; 
    m_nMin = 0;
    m_nPos = 0;
    m_ptMouseLast.x = 0 ;
    m_ptMouseLast.y = 0 ;
    m_ptMouseNow.x = 0 ;
    m_ptMouseNow.y = 0 ;
    
    m_bLBtnDown = FALSE;
	m_bDownInThumb = TRUE;
}

CTransparentSliderWnd::~CTransparentSliderWnd()
{

}


BEGIN_MESSAGE_MAP(CTransparentSliderWnd, CTransparentBaseWnd)
//{{AFX_MSG_MAP(CTransparentCheckButton)
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_MOUSEMOVE()
ON_WM_SIZE()
ON_WM_TIMER()
ON_MESSAGE( WM_REDRAW_UI, OnRedrawUI )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

    

void CTransparentSliderWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{  
    if (  !IsWindowVisible()  )
    {
       return ;
    }
	//���ý���
	HWND hFocusWnd = ::GetFocus();
	if ( hFocusWnd != m_hWnd )
	{   
		this->SetFocus();
	}	

	CRect rect;
    GetClientRect( &rect );
	if ( !rect.PtInRect( point) )
	{
		return;
	}

	m_bLBtnDown = TRUE;
	
	PointF pointf;
	pointf.X = (float)point.x;
	pointf.Y = (float)point.y;
	if ( !m_rectfThumbRect.Contains( pointf) )   //��ӻ�����rect����㵽������ƶ�����----JYY
	{   
// 		TRACE("\nm_rectfThumbRect=(%d %d %d %d)  mouse=(%d,%d)\n", 
// 			m_rectfThumbRect.X, m_rectfThumbRect.Y,m_rectfThumbRect.X+m_rectfThumbRect.Width,
// 			m_rectfThumbRect.Y+m_rectfThumbRect.Height,point.x,point.y);

		m_bDownInThumb = FALSE;
		CRect rect;
		GetClientRect( &rect );
		if ( point.x > rect.right )
		{
			point.x  =  rect.right ; 
		}
		
		if ( point.x < rect.left )
		{
			point.x = rect.left;
		}
		
		if ( point.y > rect.bottom )
		{
			point.y = rect.bottom  ;
		}
		
		if ( point.y < rect.top )
		{
			point.y = rect.top ; 
		}
		m_ptMouseLast = m_ptMouseNow;
		m_ptMouseNow = point;
		UpdateThumbPos(); 
		SetCapture();
		//PostMessage( SLIDER_CHANGED,  m_nPos);
		NOTIF_PARENT_WND
		return;
	}
//    m_bLBtnDown = TRUE; 

//    m_ptMouseLast = m_ptMouseNow;
//    m_ptMouseNow = point;

    SetTimer( g_wTimer, 200 ,NULL ) ; 
    NOTIF_PARENT_WND
    SetCapture();	
}

void CTransparentSliderWnd::OnMouseMove(UINT nFlags, CPoint point)
{
    if (  !IsWindowVisible()  )
    {
        return ;
    }


    if ( !m_bLBtnDown )
    {
        return;
    }

	PointF pointf;
	pointf.X = (float)point.x;
	pointf.Y = (float)point.y;

	CRect rect;
	GetClientRect( &rect );

	if ( !rect.PtInRect( point) )		//����ڿؼ���Χ����
	{
//		KillTimer( g_wTimer );
//      ��ֹ����ֵ��ק�������޷�������
// 		if ( GetCapture() == this )
// 		{
// 			ReleaseCapture();
// 		}
//		m_bLBtnDown = FALSE;
		if ( point.x > rect.right )
		{
			point.x  =  rect.right ; 
		}
		
		if ( point.x < rect.left )
		{
			point.x = rect.left;
		}
		
		if ( point.y > rect.bottom )
		{
			point.y = rect.bottom  ;
		}
		
		if ( point.y < rect.top )
		{
			point.y = rect.top ; 
		}
		m_ptMouseLast = m_ptMouseNow;
		m_ptMouseNow = point;
		
		UpdateThumbPos();  
		
	    NOTIF_PARENT_WND 
		//PostMessage( SLIDER_CHANGED,  m_nPos);

		return;
	}

	if ( point.x > rect.right )
	{
		point.x  =  rect.right ; 
	}
	
	if ( point.x < rect.left )
	{
		point.x = rect.left;
	}
	
	if ( point.y > rect.bottom )
	{
		point.y = rect.bottom  ;
	}
	
	if ( point.y < rect.top )
	{
		point.y = rect.top ; 
	}
	
	m_ptMouseLast = m_ptMouseNow;
	m_ptMouseNow = point;

    UpdateThumbPos();  

    NOTIF_PARENT_WND 
}

void CTransparentSliderWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{  
    KillTimer( g_wTimer ); 
	if ( m_bDownInThumb )
	{
		int nLastPos = m_nPos;
		m_nPos = GetPos();
		if ( nLastPos != m_nPos )
		{
			PostMessage( SLIDER_CHANGED, m_nPos );
		}
	}

    if ( GetCapture() == this )
    {
        ReleaseCapture();
	}
 
    if ( !IsWindowVisible() )
    {   
        m_bLBtnDown = FALSE;
        return ;
    } 

    if ( !m_bLBtnDown )
	{
		return;
    }   
   
    m_bLBtnDown = FALSE; 

    
	if (!m_bDownInThumb)
	{    
		m_nPos = GetPos();
		PostMessage( SLIDER_CHANGED,  m_nPos);
		m_bDownInThumb = TRUE;
	}
	
	NOTIF_PARENT_WND    
}

LRESULT  CTransparentSliderWnd::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    /*
    if ( message == WM_TOUCH_BUTTONDOWN )
    {
        int nX = LOWORD( lParam );
        int nY = HIWORD( lParam );
        CPoint point( nX, nY );
        if ( !m_rectThumbRect.PtInRect( point ) )
        {    
            //	m_emThumbStatus = emThumbStatusSetFocus;
            return;
        }
        
        m_bLBtnDown = TRUE; 
        
        m_ptMouseLast = m_ptMouseNow;
        m_ptMouseNow = point;
        
        SetTimer( g_wTimer, 200 ,NULL ) ; 
        NOTIF_PARENT_WND
	    SetCapture();  
    }
    
    */
    return CWnd::DefWindowProc(message, wParam, lParam);
}


void CTransparentSliderWnd::OnTimer(UINT nIDEvent) 
{  
    if ( g_wTimer == nIDEvent )
    {
        int nLastPos = m_nPos  ; 
        m_nPos = GetPos();

// 		if ( m_nPos > m_nMax )
// 		{
// 			m_nPos = m_nMax;
// 		}
// 
// 		if ( m_nPos < m_nMin )
// 		{
// 			m_nPos = m_nMin;
// 		}

        if ( m_nPos != nLastPos )
        { 
            PostMessage( SLIDER_CHANGED,  m_nPos); 
        }

    } 
    
	CTransparentBaseWnd::OnTimer(nIDEvent);

   
}


 

void CTransparentSliderWnd::SetThumbPos( /*int*/float nOffset  )
{  
   UINT nHeight = 0;
   UINT nWidth = 0;

   Image * pImage = NULL; 
   if ( m_bLBtnDown )
   {
        pImage =  m_pImgThumbPress;
   }
   else
   {
        pImage =  m_pImgThumbNormal;
   }


   if ( NULL == pImage  || NULL == m_pImgThumbNormal  )
   {
      return; 
   }

   nHeight = pImage->GetHeight();
   nWidth = pImage->GetWidth();

   m_rectfThumbRect.Width =  m_pImgThumbNormal->GetWidth() ;
   m_rectfThumbRect.Height = m_pImgThumbNormal->GetHeight();
  
   CRect rectWnd;
   GetClientRect( &rectWnd ); 

   if ( emStyleHorz == m_emStyle )
   {
	   m_rectfThumbRect.X = nOffset - rectWnd.left;
	    
	   if ( m_rectfThumbRect.X < rectWnd.left )
	   {
		   m_rectfThumbRect.X = rectWnd.left ;
	   }

	   
	   if ( m_rectfThumbRect.X+m_rectfThumbRect.Width > rectWnd.right )
	   { 
		   m_rectfThumbRect.X = rectWnd.right -  m_pImgThumbNormal->GetWidth() ;
	   }
	   
	   
	   m_rectfThumbRect.Y =  ( rectWnd.Height() - nHeight )/2;
   
   }
   else
   {//�����ֱ���� 2013.1.24 yjj
	   m_rectfThumbRect.Y = nOffset - rectWnd.top;
	   if ( m_rectfThumbRect.Y < rectWnd.top )
	   {
		   m_rectfThumbRect.Y = rectWnd.top ;
	   } 
	   
	   if ( m_rectfThumbRect.Y + m_rectfThumbRect.Height > rectWnd.bottom )
	   {
		   m_rectfThumbRect.Y  = rectWnd.bottom - m_rectfThumbRect.Height;
	   } 
	  
	   m_rectfThumbRect.X =  ( rectWnd.Width() - nWidth )/2; 
	    
   }
  
   
  
}

void CTransparentSliderWnd::UpdateThumbPos()
{   
    UINT nHeight = 0;
    UINT nWidth = 0;
    if ( m_pImgThumbNormal == NULL )
    {
		return;
       
    }

	nHeight = m_pImgThumbNormal->GetHeight();
    nWidth = m_pImgThumbNormal->GetWidth();
    
	m_rectfThumbRect.Width =  nWidth ;
    m_rectfThumbRect.Height = nHeight;


    CRect rectWnd;
    GetClientRect( &rectWnd );
    
	if ( emStyleHorz == m_emStyle )
	{
	
		m_rectfThumbRect.X   =  m_ptMouseNow.x -  rectWnd.left - nWidth/2   ;

		if ( m_ptMouseNow.x < rectWnd.left + nWidth/2 )
		{
			m_rectfThumbRect.X = 0;
		}

		m_rectfThumbRect.Y  =  ( rectWnd.Height() - nHeight )/2;
		
		
		if (  m_rectfThumbRect.X  < rectWnd.left )
		{
		     m_rectfThumbRect.X  = rectWnd.left ; 
		} 
		if (  m_rectfThumbRect.X  + nWidth > rectWnd.right )
		{      
			m_rectfThumbRect.X =  rectWnd.right - nWidth;
		} 
	}
	else
	{//�����ֱ���� 2013.1.24 yjj
		m_rectfThumbRect.X = ( rectWnd.Width() - nWidth )/2;
		m_rectfThumbRect.Y =   m_ptMouseNow.y -  rectWnd.top - nHeight/2 ;
		
		//�жϵ����黬�������ϱ�ʱ��,�������ƫ������Ϊ0 ---2013.3.7 JYY
		if ( m_ptMouseNow.y < rectWnd.top + nHeight/2 )
		{
			m_rectfThumbRect.Y = 0;
		}
		
		
//		if ( m_rectfThumbRect.Y < rectWnd.top )
//		{
//			m_rectfThumbRect.Y = rectWnd.top ; 
//		} 
		 
		
		if ( m_rectfThumbRect.Y + nHeight  > rectWnd.bottom )
		{      
			m_rectfThumbRect.Y = rectWnd.bottom - nHeight;		 
		}
	}

   
}

//���ݵ�ǰ��ƫ�������� slider��Ӧ��ֵ����ֵ�������Range��Χ����
float CTransparentSliderWnd::CalculatePos( /*int*/float nOffSet )
{ 
	int nRange = m_nMax - m_nMin;

	UINT nWidth = 0;
	if ( m_pImgThumbNormal != NULL )
	{ 
	   if ( emStyleHorz == m_emStyle )
	   {
		    nWidth = m_pImgThumbNormal->GetWidth();
		    float nPos =  m_nMin + ( (float)nOffSet/((float)m_nMaxOffset - (float)nWidth) * nRange ) ;//�����̶ȴӷ�0��ʼ���������ֱ����δ���� 20140213 ������
			TRACE("\n[CTransparentSliderWnd::CalculatePos] range=%d maxoffset=%d offset=%f  return=%f\n",nRange,m_nMaxOffset,nOffSet,nPos);
			return nPos;
	   }
	   else
	   {//�����ֱ���� 2013.1.24 yjj    -----jyy  ��������
			nWidth = m_pImgThumbNormal->GetHeight();	
// 			if ( nOffSet <= nWidth/2 )
// 			{
// 			   nOffSet = 0;
// 			}
// 
// 			if ( nOffSet >= m_nMaxOffset - nWidth/3 )
// 			{
// 			   nOffSet = m_nMaxOffset;
// 			}
	   }      
	}

	float nPos  = 0;
	if ( 0 != m_nMaxOffset )
	{
	    nPos =  (float)nOffSet/((float)m_nMaxOffset-nWidth/* - (float)nWidth/2*/) * nRange ;
	}
    
	//���ָ������ȡ����ֵһ��,��������������������
 	nPos =  m_nMax - nPos;
// 	if ( nPos > m_nMax )
// 	{
// 		nPos = m_nMax;
// 	}
// 	
// 	if ( nPos < m_nMin )
// 	{
// 		nPos = m_nMin;
// 	}
    TRACE("\n[CTransparentSliderWnd::CalculatePos] range=%d maxoffset=%d offset=%f  return=%f\n",nRange,m_nMaxOffset,nOffSet,nPos);
	return nPos;
}

//���ݵ�ǰ�����range��ֵ��������thumb ��ƫ����
/*int*/float CTransparentSliderWnd::CalculateOffset( /*int*/float nPos )
{ 
    int nRange = m_nMax - m_nMin;
    UINT nWidth = 0;
    if ( m_pImgThumbNormal != NULL )
    { 
		if ( emStyleHorz == m_emStyle )
		{
			nWidth = m_pImgThumbNormal->GetWidth();
			
			int nPosOffset = nPos - m_nMin;	//�����̶ȴӷ�0��ʼ���������ֱ����δ���� 20140213 ������
			if ( nPosOffset < 0 )
			{
				nPosOffset = 0;
			}

			float nOffset = (float)nPosOffset /nRange *  ( m_nMaxOffset - nWidth );			
			return nOffset;		
		}
		else
		{//�����ֱ����Ļ��� 2013.1.24 yjj
			nWidth = m_pImgThumbNormal->GetHeight();
			nPos = m_nMax - nPos;
		}
    }
	//���պ���CalculatePos(��ƫ������rangeֵ)��Ӧ����,ԭ���㷽ʽΪˮƽ����ļ��㹫ʽ
    float nOffset = (float)nPos /nRange *  ( m_nMaxOffset - nWidth );	
    return nOffset;
}

void CTransparentSliderWnd::OnSize(UINT nType, int cx, int cy)
{ 
    //���thumb�ĸ߶ȴ��ڵ�ǰ����slider�ĸ߶ȣ���� sliderWnd�ĸ߶ȵ���Ϊthumb�ĸ߶�,������ʾ��ȫthumb 
	if ( emStyleHorz == m_emStyle )
	{
		if ( m_pImgThumbNormal != NULL &&  m_pImgThumbNormal->GetHeight() >cy )
		{
			cy =  m_pImgThumbNormal->GetHeight();
			
			if ( m_pImgThumbPress != NULL && m_pImgThumbPress->GetHeight() > cy )
			{
				cy = m_pImgThumbPress->GetHeight();
			}
		}
	}
	else
	{//�����ֱ����Ļ��� 2013.1.24 yjj
		if ( m_pImgThumbNormal != NULL &&  m_pImgThumbNormal->GetWidth() >cx )
		{
			cx =  m_pImgThumbNormal->GetWidth();
			
			if ( m_pImgThumbPress != NULL && m_pImgThumbPress->GetWidth() > cx )
			{
				cx = m_pImgThumbPress->GetWidth();
			}
		}
	}
    

    CWnd::OnSize( nType, cx, cy );  

    UpdateMaxOffSet();
    SetThumbPos( 0 );
}

void CTransparentSliderWnd::UpdateMaxOffSet()
{
    CRect rect;
    GetClientRect( & rect );
	if ( emStyleHorz == m_emStyle )
	{
	   m_nMaxOffset = rect.Width();  
	}
	else
	{
	   m_nMaxOffset = rect.Height(); 
	}

}

LRESULT CTransparentSliderWnd::OnRedrawUI( WPARAM wParam, LPARAM lParam )
{
    if ( IsWindowVisible() == FALSE )
    {
        return S_FALSE;
    }
    
    Graphics *pGraphics = (Graphics*)wParam;
    HWND hGraphWnd = (HWND )lParam;
    //  CWnd * pGraphWnd = FromHandle(hGraphWnd);
    if ( pGraphics == NULL || hGraphWnd == 0 )
    {
        return S_FALSE;
    } 
  

  //��ȡslider�ķ��  
	if (  emStyleVert == m_emStyle )
	{
		//��ֱ����
		DrawVertSlider( pGraphics, hGraphWnd );
	}
	else
	{
		//ˮƽ����
		DrawHorizSlider( pGraphics, hGraphWnd);
    } 

  
    return S_OK;
}


BOOL CTransparentSliderWnd::GetDrawImg( Image ** pImgThumb, Image ** pImgNormalLeft, Image ** pImgNormalMiddle, 
										Image ** pImgNormalRight, Image ** pImgHighLightLeft, Image ** pImgHighLightMiddle, 
										Image ** pImgHighLightRight )
{
	if ( IsWindowEnabled() )
    {
        if ( m_bLBtnDown )
        {
            *pImgThumb = m_pImgThumbPress;
        }
        else
        {
            *pImgThumb = m_pImgThumbNormal;
        }
		
		
        *pImgNormalLeft = m_pImgNormalLeft;
        *pImgNormalMiddle = m_pImgNormalMiddle;
        *pImgNormalRight = m_pImgNormalRight;
        
        *pImgHighLightLeft = m_pImgHighLightLeft;
        *pImgHighLightMiddle = m_pImgHighLightMiddle;
        *pImgHighLightRight = m_pImgHighLightRight;
		
    }
    else
    {
        *pImgThumb = m_pImgThumbDisable;
		
        *pImgNormalLeft = m_pImgDisableLeft;
        *pImgNormalMiddle = m_pImgDisableMid;
        *pImgNormalRight = m_pImgDisableRight;
        
        *pImgHighLightLeft = m_pImgDisableHighLightLeft;
        *pImgHighLightMiddle = m_pImgDisableHighLightMid;
        *pImgHighLightRight = m_pImgDisableHighLightRight;
    }

    if (  pImgThumb == NULL || pImgNormalLeft == NULL || pImgNormalMiddle == NULL || pImgNormalRight == NULL
		|| pImgHighLightLeft == NULL || pImgHighLightMiddle == NULL || pImgHighLightRight == NULL )
    {
        return S_FALSE;
    }

	return TRUE;
}
    
/*---------------------------------------------------------------------
* ��    �ܣ�����ˮƽ�����slider
* ��    ע�� 
* ����			�汾		�޸���		�޸ļ�¼
* 2013.1.23    1.0         �����        ����
----------------------------------------------------------------------*/
void CTransparentSliderWnd::DrawHorizSlider( Graphics *pGraphics, HWND hGraphWnd)
{
	Image * pImgNormalLeft = NULL;
    Image * pImgNormalMiddle = NULL;
    Image * pImgNormalRight = NULL;
	
    Image * pImgHighLightLeft = NULL;
    Image * pImgHighLightMiddle = NULL;
    Image * pImgHighLightRight = NULL;
	
    Image *pImgThumb = NULL;
	
	BOOL bSucess = GetDrawImg( &pImgThumb, &pImgNormalLeft, &pImgNormalMiddle, 
		&pImgNormalRight, &pImgHighLightLeft, &pImgHighLightMiddle,  &pImgHighLightRight );
	if ( !bSucess )
	{ 
		AfxOutputDebugString( "\n[CTransparentSliderWnd::DrawHorizSlider]GetDrawImg false \n" );
		return ;
	}
	
    CRect cRect;
    GetClientRect( &cRect );
    POINT point = cRect.TopLeft();
    if ( pImgNormalLeft != NULL )
    {
        point.y = (cRect.Height() - pImgNormalLeft->GetHeight() )/2;
    }
	::ClientToScreen( GetSafeHwnd(), &point  );
	::ScreenToClient( hGraphWnd, &point );
	
 
	
	POINT tumbPos;
	tumbPos.x = (long)m_rectfThumbRect.X;  
	tumbPos.y  = ( cRect.Height() - pImgThumb->GetHeight()) /2;  
	::ClientToScreen( GetSafeHwnd(), &tumbPos  );
    ::ScreenToClient( hGraphWnd, &tumbPos);
    PointF thumPosF;
	thumPosF.X = tumbPos.x; 
    thumPosF.Y = tumbPos.y;
 
	
	// ���Ƶ�ͼ
	int nPosX = point.x  +  pImgNormalLeft->GetWidth();
	int nPosY = point.y ; 
	int nMiddleWidth = cRect.Width() -  pImgNormalLeft->GetWidth() -  pImgNormalRight->GetWidth();
	// ��
	pGraphics->DrawImage( pImgNormalLeft, point.x, nPosY,  pImgNormalLeft->GetWidth(), pImgNormalLeft->GetHeight() );
	// ��
	pGraphics->DrawImage( pImgNormalRight, point.x + cRect.Width() - pImgNormalRight->GetWidth(), nPosY, pImgNormalRight->GetWidth(), pImgNormalRight->GetHeight() );
	
	if ( nMiddleWidth <= 0 )
	{
		return ;
	}
	
	for ( unsigned int nIndex = 0; nIndex < ( nMiddleWidth / m_pImgNormalMiddle->GetWidth() ); nIndex++ )
	{
		pGraphics->DrawImage( pImgNormalMiddle, nPosX, nPosY, pImgNormalMiddle->GetWidth(), pImgNormalMiddle->GetHeight() );
		nPosX += pImgNormalMiddle->GetWidth();
	}
	pGraphics->DrawImage( pImgNormalMiddle, nPosX, nPosY, nMiddleWidth % pImgNormalMiddle->GetWidth(), pImgNormalMiddle->GetHeight() );
	
	// ���Ƹ����ĵط� 
	if ( thumPosF.X > point.x )
	{
		// ��
		pGraphics->DrawImage( pImgHighLightLeft, point.x, nPosY, pImgHighLightLeft->GetWidth(), pImgHighLightLeft->GetHeight() );
		
		float tempX = thumPosF.X  + pImgThumb->GetWidth()/2 - pImgHighLightRight->GetWidth(); 
		if ( tempX < point.x )
		{
			tempX = point.x;
		}
		// ��
		pGraphics->DrawImage( pImgHighLightRight, tempX, (float)nPosY, pImgHighLightRight->GetWidth(), pImgHighLightRight->GetHeight() );
		
		nPosX = point.x + pImgHighLightLeft->GetWidth();
		nMiddleWidth = ( tempX - point.x );
		// �У������������죬��Ϊ����ı������˻ᵼ�±�Ե��ģ��������
		for ( nIndex = 0; nMiddleWidth > 0 && nIndex < ( nMiddleWidth / pImgHighLightMiddle->GetWidth() ); nIndex++ )
		{
			pGraphics->DrawImage( pImgHighLightMiddle, nPosX, nPosY, pImgHighLightMiddle->GetWidth(), m_pImgHighLightMiddle->GetHeight() );
			nPosX += m_pImgHighLightMiddle->GetWidth();
		}
		if ( nMiddleWidth > 0 )
		{
			pGraphics->DrawImage( pImgHighLightMiddle, nPosX, nPosY, nMiddleWidth % pImgHighLightMiddle->GetWidth(), pImgHighLightMiddle->GetHeight() );
		} 
	} 
	
   
	// ����Thumb  
	pGraphics->DrawImage( pImgThumb,  thumPosF.X ,  thumPosF.Y , pImgThumb->GetWidth(), pImgThumb->GetHeight() );
}

/*---------------------------------------------------------------------
* ��    �ܣ�������ֱ�����slider
* ��    ע�� 
* ����			�汾		�޸���		�޸ļ�¼
* 2013.1.23    1.0         �����        ����
----------------------------------------------------------------------*/
void CTransparentSliderWnd::DrawVertSlider( Graphics *pGraphics, HWND hGraphWnd)
{
	Image * pImgNormalLeft = NULL;
    Image * pImgNormalMiddle = NULL;
    Image * pImgNormalRight = NULL;
	
    Image * pImgHighLightLeft = NULL;
    Image * pImgHighLightMiddle = NULL;
    Image * pImgHighLightRight = NULL;
	
    Image *pImgThumb = NULL;
	
	BOOL bSucess = GetDrawImg( &pImgThumb, &pImgNormalLeft, &pImgNormalMiddle, 
		&pImgNormalRight, &pImgHighLightLeft, &pImgHighLightMiddle,  &pImgHighLightRight );
	if ( !bSucess )
	{ 
		AfxOutputDebugString( "\n[CTransparentSliderWnd::DrawVertSlider]GetDrawImg false \n" );
		return ;
	}
	
    CRect cRect;
    GetClientRect( &cRect );
    POINT point = cRect.TopLeft();
    
	::ClientToScreen( GetSafeHwnd(), &point  );
	::ScreenToClient( hGraphWnd, &point );
 
	
	// ���Ƶ�ͼ 
	float nPosX = point.x + (cRect.Width() - pImgNormalLeft->GetWidth() )/2;  
	int nMiddleWidth = cRect.Height() -  pImgNormalLeft->GetHeight() -  pImgNormalRight->GetHeight();
	//��ͼ��
	pGraphics->DrawImage( pImgNormalLeft,nPosX, (float)point.y,  pImgNormalLeft->GetWidth(), pImgNormalLeft->GetHeight() );
	// ��ͼ��
	pGraphics->DrawImage( pImgNormalRight, nPosX, (float)(point.y + cRect.Height() - pImgNormalLeft->GetHeight() ) , pImgNormalRight->GetWidth(), pImgNormalRight->GetHeight() );
	
	if ( nMiddleWidth <= 0 )
	{
		return ;
	}
	//��ͼ�м䲿��
	float nPosY = point.y + pImgNormalLeft->GetHeight(); 
	for ( unsigned int nIndex = 0; nIndex < ( nMiddleWidth / m_pImgNormalMiddle->GetHeight() ); nIndex++ )
	{
		pGraphics->DrawImage( pImgNormalMiddle, nPosX, nPosY, pImgNormalMiddle->GetWidth(), pImgNormalMiddle->GetHeight() );
		nPosY += pImgNormalMiddle->GetHeight();
	}
	pGraphics->DrawImage( pImgNormalMiddle, nPosX, nPosY, pImgNormalMiddle->GetWidth(), nMiddleWidth % pImgNormalMiddle->GetHeight() );
	

	// ���Ƹ����ĵط� 
	POINT tumbPos;
	// 2013.3.7 ������ֱ�������ʱ��ťƫ�� ----JYY
	tumbPos.x = ( cRect.Width() - pImgThumb->GetWidth() )/2;
	tumbPos.y = (long)m_rectfThumbRect.Y;
//	tumbPos.x = (long)m_rectfThumbRect.X;  
//	tumbPos.y  = ( cRect.Height() - pImgThumb->GetHeight()) /2;  
	::ClientToScreen( GetSafeHwnd(), &tumbPos  );
    ::ScreenToClient( hGraphWnd, &tumbPos);
   
	PointF thumPosF;
	thumPosF.X = tumbPos.x; 
    thumPosF.Y = tumbPos.y; 

	nPosX = point.x + (cRect.Width() - pImgHighLightLeft->GetWidth() )/2; 


	if ( NULL !=  pImgHighLightLeft &&  /*tumbPos.y > point.y*/tumbPos.y + pImgThumb->GetHeight() < point.y + cRect.bottom )
	{
		// ��
//		pGraphics->DrawImage( pImgHighLightLeft, nPosX, (float)point.y, pImgHighLightLeft->GetWidth(), pImgHighLightLeft->GetHeight() );
		
//		float tempy = tumbPos.y + pImgThumb->GetHeight()/2 - pImgHighLightRight->GetHeight() ; 
//		if ( tempy < point.y )
		{
//			tempy = point.y;
		}
		// ��
//		pGraphics->DrawImage( pImgHighLightRight, nPosX, tempy, pImgHighLightRight->GetWidth(), pImgHighLightRight->GetHeight() );
// 		float tempy = tumbPos.y - pImgThumb->GetHeight()/2 - pImgHighLightLeft->GetHeight() ; 
//		pGraphics->DrawImage( pImgHighLightLeft, nPosX, tempy, pImgHighLightLeft->GetWidth(), pImgHighLightLeft->GetHeight() );
// 
// 		nPosY = point.y + pImgHighLightLeft->GetHeight();
// 		nMiddleWidth = ( tempy - point.y );
// 		// �У������������죬��Ϊ����ı������˻ᵼ�±�Ե��ģ��������
// 		for ( nIndex = 0; nMiddleWidth > 0 && nIndex < ( nMiddleWidth / pImgHighLightMiddle->GetHeight() ); nIndex++ )
// 		{
// 			pGraphics->DrawImage( pImgHighLightMiddle, nPosX, nPosY, pImgHighLightMiddle->GetWidth(), m_pImgHighLightMiddle->GetHeight() );
// 			nPosY += m_pImgHighLightMiddle->GetHeight();
// 		}
// 		if ( nMiddleWidth > 0 )
// 		{
// 			pGraphics->DrawImage( pImgHighLightMiddle, nPosX, nPosY, pImgHighLightMiddle->GetWidth(), nMiddleWidth % pImgHighLightMiddle->GetHeight() );
// 		} 		
		//��     --2013.4.18 �޸�slider�ĸ�����ʾ��ʽ��������   JYY
		pGraphics->DrawImage( pImgHighLightRight, nPosX, point.y + cRect.Height() - pImgHighLightRight->GetHeight(), pImgHighLightRight->GetWidth(), pImgHighLightRight->GetHeight() );		
		float tempy = tumbPos.y + pImgThumb->GetHeight() - pImgHighLightLeft->GetHeight() ; 
		if ( tempy < point.y )
		{
			tempy = point.y;
		}
		//��
		pGraphics->DrawImage( pImgHighLightLeft, nPosX, tempy, pImgHighLightLeft->GetWidth(), pImgHighLightLeft->GetHeight() );

		nPosY = point.y + cRect.Height() - pImgHighLightRight->GetHeight() - m_pImgHighLightMiddle->GetHeight();
		nMiddleWidth = point.y + cRect.bottom - tumbPos.y - pImgThumb->GetHeight()/* - pImgHighLightRight->GetHeight()*/;
		// �У������������죬��Ϊ����ı������˻ᵼ�±�Ե��ģ��������
		for ( nIndex = 0; nMiddleWidth > 0 && nIndex < ( nMiddleWidth / pImgHighLightMiddle->GetHeight() ); nIndex++ )
		{
			pGraphics->DrawImage( pImgHighLightMiddle, nPosX, nPosY, pImgHighLightMiddle->GetWidth(), m_pImgHighLightMiddle->GetHeight() );
			nPosY -= m_pImgHighLightMiddle->GetHeight();
		}
		if ( nMiddleWidth > 0 )
		{
			pGraphics->DrawImage( pImgHighLightMiddle, nPosX, nPosY, pImgHighLightMiddle->GetWidth(), nMiddleWidth % pImgHighLightMiddle->GetHeight() );
 		} 
	} 
	// ����Thumb  
	pGraphics->DrawImage( pImgThumb, thumPosF.X, thumPosF.Y, pImgThumb->GetWidth(), pImgThumb->GetHeight() );
	if ( TRUE == m_bLBtnDown && NULL != m_pImgBubble )
	{
		// ����������ʾ��
		pGraphics->DrawImage( m_pImgBubble, thumPosF.X + pImgThumb->GetWidth(), thumPosF.Y-7, m_pImgBubble->GetWidth(), m_pImgBubble->GetHeight() );
		// ���Ƶ����ťʱ������
		CString strText;
		int i = GetPos();
		strText.Format("%i",i);
		BSTR bstrText = strText.AllocSysString();
		Font* pFont = CSrcManage::GetFont( "����", 9 );
		StringFormat cStringFormat;
		cStringFormat.SetAlignment( StringAlignmentCenter );
		SolidBrush brush( Color( 254, 15, 79, 81 )  );
		pGraphics->DrawString( bstrText, -1, pFont, RectF( (float)(thumPosF.X+18), (float)(thumPosF.Y+4), 46, 33 ), &cStringFormat, &brush );
		SysFreeString( bstrText );
	}
}


void CTransparentSliderWnd::SetImage( CString strFolder, BOOL bInvalidate /* = FALSE */ )
{
    String strFile = strFolder + "//" + CTransparentSliderWnd::strNormalLeft;
    m_pImgNormalLeft = CSrcManage::GetImage( strFile.c_str() );
    strFile = strFolder + "//" + CTransparentSliderWnd::strNormalMid;
    m_pImgNormalMiddle = CSrcManage::GetImage( strFile.c_str() );
    strFile = strFolder + "//" + CTransparentSliderWnd::strNormalRight;
    m_pImgNormalRight = CSrcManage::GetImage( strFile.c_str() );
    
    strFile = strFolder + "//" + CTransparentSliderWnd::strHighLightLeft;
    m_pImgHighLightLeft = CSrcManage::GetImage( strFile.c_str() );
    strFile = strFolder + "//" + CTransparentSliderWnd::strHighLightMid;
    m_pImgHighLightMiddle = CSrcManage::GetImage( strFile.c_str() );
    strFile = strFolder + "//" + CTransparentSliderWnd::strHighLightRight;
    m_pImgHighLightRight = CSrcManage::GetImage( strFile.c_str() );
    
    strFile = strFolder + "//" + CTransparentSliderWnd::strThumbNormal;
    m_pImgThumbNormal = CSrcManage::GetImage( strFile.c_str() );
    strFile = strFolder + "//" + CTransparentSliderWnd::strThumbPress;
    m_pImgThumbPress = CSrcManage::GetImage( strFile.c_str() );
    
    
    
    //disable
    strFile = strFolder + "//" + CTransparentSliderWnd::strDisableLeft;
    m_pImgDisableLeft = CSrcManage::GetImage( strFile.c_str() );
    strFile = strFolder + "//" + CTransparentSliderWnd::strDisableMid;
    m_pImgDisableMid  = CSrcManage::GetImage( strFile.c_str() );
    strFile = strFolder + "//" + CTransparentSliderWnd::strDisableRight;
    m_pImgDisableRight = CSrcManage::GetImage( strFile.c_str() );
    
    strFile = strFolder + "//" + CTransparentSliderWnd::strDisableHighLightLeft;
    m_pImgDisableHighLightLeft = CSrcManage::GetImage( strFile.c_str() );
    
    strFile = strFolder + "//" + CTransparentSliderWnd::strDisableHighLightMid;
    m_pImgDisableHighLightMid = CSrcManage::GetImage( strFile.c_str() );
    
    strFile = strFolder + "//" + CTransparentSliderWnd::strDisableHighLightRight;
    m_pImgDisableHighLightRight = CSrcManage::GetImage( strFile.c_str() );
    
    strFile = strFolder + "//" + CTransparentSliderWnd::strThumbDisable;
    m_pImgThumbDisable = CSrcManage::GetImage( strFile.c_str() );
    
    strFile = strFolder + "//" + CTransparentSliderWnd::strBubble;
    m_pImgBubble = CSrcManage::GetImage( strFile.c_str() );
        

    UpdateMaxOffSet();

    CRect rect;
    GetClientRect( & rect ); 

    if ( bInvalidate )
    {
        NOTIF_PARENT_WND
    } 
    
     
     AdjustSlider();

     SetThumbPos( 0 );
     //TRACE("\n[SetImage]thumbPos(x:%d  y:%d)\n",m_ptThumbPos.x,m_ptThumbPos.y);
}



void CTransparentSliderWnd::GetRange( int& nMin, int& nMax ) const
{
   nMin = m_nMin;
   nMax = m_nMax;

} 

void CTransparentSliderWnd::SetRange( int nMin, int nMax, BOOL bRedraw/* = FALSE */)
{
    m_nMin = nMin;
    m_nMax = nMax;
   
   //����slider����
    AdjustSlider();

    if ( bRedraw )
    {
       NOTIF_PARENT_WND;
    }
}


void CTransparentSliderWnd::AdjustSlider()
{  
    if ( m_nMax ==  m_nMin || m_pImgThumbNormal == NULL )
    {
        return;
    }

    CRect rect;
	GetClientRect( &rect );

	if ( m_pImgThumbNormal == NULL )
	{
		return;
	}

	int nThumbWidth = m_pImgThumbNormal->GetWidth(); 
    int nThumbHeight = m_pImgThumbNormal->GetHeight();


	if ( emStyleHorz == m_emStyle )
	{  
        //�����߶� 
        if ( m_pImgThumbPress != NULL && m_pImgThumbPress->GetHeight() > nThumbHeight )
        {
            nThumbHeight = m_pImgThumbPress->GetHeight();
        }
        
        if ( nThumbHeight > rect.Height() )
        {
            rect.bottom = rect.bottom +  nThumbHeight - rect.Height() + 6 ;
        }
		
        //�������
        int nSliderWidth = rect.Width();
 
        SetWindowPos(NULL, rect.left , rect.top, nSliderWidth , rect.Height() , SWP_NOMOVE ); 
	}
    else
	{
		//������� 
        if ( m_pImgThumbPress != NULL && m_pImgThumbPress->GetWidth() > nThumbWidth )
        {
            nThumbWidth = m_pImgThumbPress->GetWidth();
        }
        
        if ( nThumbWidth > rect.Width() )
        {
            rect.right = rect.right +  nThumbWidth - rect.Width() + 6 ;
        }
		
        //�����߶�
        int nSliderWidth = rect.Height(); 
        
        SetWindowPos(NULL, rect.left , rect.top, rect.Width() , nSliderWidth , SWP_NOMOVE ); 
	}
}

int  CTransparentSliderWnd::GetPos( )  
{  
    CRect rect;
    GetClientRect( &rect );
    int nWidth = 0;
    if ( m_pImgThumbNormal != NULL )
    {
        nWidth = m_pImgThumbNormal->GetWidth()/2;
    }

    int nOffset =  m_rectfThumbRect.X -  rect.left/* + nWidth*/;
	if ( emStyleHorz != m_emStyle )
	{//�����ֱ���� 2013.1.24 yjj
		nOffset = /*m_ptMouseNow.y -  rect.top;*/ m_rectfThumbRect.Y -  rect.top;
	}
    if ( nOffset > m_nMaxOffset )
    {
        nOffset = m_nMaxOffset;
    }

    if ( nOffset < 0 )
    {
        nOffset = 0;
    }

    return CalculatePos( nOffset );
}

void CTransparentSliderWnd::SetPos( int nPos )
{
    //��ֹ��קʱ�ж���������������קʱ����Ӧ�ⲿ������
	if ( m_bLBtnDown )
	{
	   return;
	}

//    CString str ;
//    str.Format("\n[setPos: getPos=%d  willSet=%d]\n",GetPos(),nPos );
//    AfxOutputDebugString( str );
	//��ƫ������С,����λ��֮��Ľ���ģ��---jyy
//	if ( GetPos() != nPos )
//	{
	if ( NULL == m_pImgThumbNormal )
	{
		return;	
	}
	m_nPos = nPos;
	UINT nWidth = m_pImgThumbNormal->GetWidth();
	CRect rect;
    GetClientRect( &rect );
	float fThumbRectX =  m_rectfThumbRect.X -  rect.left;		//��ȡ��ǰ��������λ�õ�ƫ����
	if ( emStyleHorz != m_emStyle )
	{
		fThumbRectX = m_rectfThumbRect.Y -  rect.top;
	}
	float nOffset  = CalculateOffset( nPos ) ;			//������Ҫ���û���λ�õ�ƫ����
	float fOffsetRange = (float)( m_nMaxOffset - nWidth ) / (float)(m_nMax - m_nMin);	//����1���̶ȵ�ƫ����
	float fsize = nOffset - fThumbRectX;
	if ( fsize <= 0 )
	{
		fsize = -fsize;	
		if ( fsize > fOffsetRange )		//��ƫ����С�ڿ̶�1ʱ,����,�������
		{
			SetThumbPos(  nOffset  ); 
			NOTIF_PARENT_WND; 
			return;
		}
		const float EPSINON = (const float)0.00001;	//�������Ƚϵ�ʱ�������,�Ƚ�"=="��ʱ��������ַ�ʽȷ�����Ƴɹ�
		float a = fsize - fOffsetRange;
		if ((a >= - EPSINON)&& (a <= EPSINON))
		{
			SetThumbPos(  nOffset  ); 
			NOTIF_PARENT_WND; 
		}
		return;
	
	}

	SetThumbPos(  nOffset  ); 
	NOTIF_PARENT_WND; 

//      str.Format("\n[setPos: nOffset=%d]\n",nOffset );
//      AfxOutputDebugString( str );
//	} 
  
}
 