/********************************************************************
	ģ����:      UILib
	�ļ���:      skinheaderctrl.cpp
	����ļ�:    UILibHead.h
	�ļ�ʵ�ֹ��� 
    ���ߣ�       ������
	�汾��       1.0
--------------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��		�汾		�޸���		�߶���    �޸�����
	2004/4/8	1.0			������               

*********************************************************************/

#include "stdafx.h"
#include "UILibHead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

COLORREF CSkinHeaderCtrl::m_s_crText  = RGB(0,0,0);
COLORREF CSkinHeaderCtrl::m_s_crBk    = RGB(115,144,196);
COLORREF CSkinHeaderCtrl::m_s_crFrame = -1;

/////////////////////////////////////////////////////////////////////////////
// CSkinHeaderCtrl

CSkinHeaderCtrl::CSkinHeaderCtrl()
{
    m_crBk = m_s_crBk;
    m_crText = m_s_crText;
    m_crFrame = m_s_crFrame;

    m_nSortCol = -1;
    m_bSortAscending = TRUE;
    m_penDivide.m_hObject = NULL;
	m_bShow3D=FALSE;
}

CSkinHeaderCtrl::~CSkinHeaderCtrl()
{
    if (m_penDivide.m_hObject != NULL) 
    {
        m_penDivide.DeleteObject();
    }
}


BEGIN_MESSAGE_MAP(CSkinHeaderCtrl, CHeaderCtrl)
	//{{AFX_MSG_MAP(CSkinHeaderCtrl)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinHeaderCtrl message handlers

void CSkinHeaderCtrl::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	CHeaderCtrl::PreSubclassWindow();
}

void CSkinHeaderCtrl::DrawItem(LPDRAWITEMSTRUCT lpDS)
{
    CDC* pDC = CDC::FromHandle(lpDS->hDC);
    CRect rect = lpDS->rcItem;

    if (m_penDivide.GetSafeHandle() != NULL) 
    {
        CPen* pOld = pDC->SelectObject(&m_penDivide);
 //       pDC->FillSolidRect(rect.right, rect.top, 1, rect.Height(), m_crFrame);
        pDC->MoveTo(rect.right, rect.top);
        pDC->LineTo(rect.right, rect.bottom);
        pDC->SelectObject(pOld);
    }
    else
    {
       pDC->DrawEdge(rect, BDR_SUNKENOUTER, BF_RIGHT);	
		
    }


	if (m_bShow3D)  //zhaofajie 20070410  �б�ͷͻ����ʾ
	{
		rect.DeflateRect(1,1,1,1);
		pDC->DrawEdge(rect, EDGE_RAISED, BF_RECT);
	}

	HD_ITEM hditem;
    TCHAR buf[256];
	
	hditem.mask = HDI_TEXT | HDI_FORMAT | HDI_ORDER;
	hditem.pszText = buf;
	hditem.cchTextMax = 255;
    GetItem(lpDS->itemID, &hditem);
    
    UINT uFormat = DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER | DT_END_ELLIPSIS ;

	switch (hditem.fmt & HDF_JUSTIFYMASK)
    {
    case HDF_CENTER:
    	uFormat |= DT_CENTER;
        break;
    case HDF_RIGHT:
		uFormat |= DT_RIGHT;
        break;
    case HDF_LEFT:
		uFormat |= DT_LEFT;
        break;
    default:
        break;
    }

    CFont* pFont;
    pFont = pDC->SelectObject(GetFont());
    pDC->SetTextColor(m_crText);

    const int nOffset = rect.Height()/4;
    if (lpDS->itemID == m_nSortCol)
    {
        DrawArrow(pDC, rect);
        rect.right -= 3*nOffset;
    }
    rect.DeflateRect(nOffset, 0);
    pDC->DrawText(buf, rect, uFormat);
    pDC->SelectObject(pFont);
}

void CSkinHeaderCtrl::SetTextColor(COLORREF crText, BOOL bRepaint)
{
    m_crText = crText;

    if (bRepaint)
    {
        Invalidate();
    }
}

void CSkinHeaderCtrl::SetBkColor(COLORREF crBk, BOOL bRepaint)
{
    m_crBk = crBk;

    if (bRepaint)
    {
        Invalidate();
    }
}

BOOL CSkinHeaderCtrl::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return false;
	return CHeaderCtrl::OnEraseBkgnd(pDC);
}

void CSkinHeaderCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CHeaderCtrl::OnPaint() for painting messages
    CRect rect;
    GetClientRect(rect);

    if (m_crFrame != -1) 
    {
        dc.FrameRect(rect, &CBrush(m_crFrame));
        rect.DeflateRect(0,1,0,1);
    }
    dc.FillRect(rect, &CBrush(m_crBk));
    dc.SetBkMode(TRANSPARENT);

    CRect rectItem;
    for (int i = 0; i < GetItemCount(); i++)
    {
        DRAWITEMSTRUCT	DrawItemStruct;
		GetItemRect(i, &rectItem);
		rectItem.InflateRect(1, 0);
		
		DrawItemStruct.CtlType		= 100;
		DrawItemStruct.hDC			= dc.GetSafeHdc();
		DrawItemStruct.itemAction	= ODA_DRAWENTIRE; 
		DrawItemStruct.hwndItem 	= GetSafeHwnd(); 
		DrawItemStruct.rcItem	= rectItem;
		DrawItemStruct.itemID	= i;
		DrawItem(&DrawItemStruct);
    }
    
  
}

BOOL CSkinHeaderCtrl::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_LBUTTONDBLCLK)
    {
        pMsg->message = WM_LBUTTONDOWN;
    }
	return CHeaderCtrl::PreTranslateMessage(pMsg);
}

void CSkinHeaderCtrl::SetSortArrow(int nSortCol, BOOL bSortAscending)
{
    m_nSortCol = nSortCol;
    m_bSortAscending = bSortAscending;
    Invalidate();
}

void CSkinHeaderCtrl::DrawArrow(CDC *pDC, CRect rect)
{
    CPen penLight( PS_SOLID, 1, GetSysColor( COLOR_3DHILIGHT ) );
	CPen penShadow( PS_SOLID, 1,  RGB(100,100,100)); //GetSysColor( COLOR_3DSHADOW )
	CPen* pOldPen = pDC->SelectObject( &penLight );
    int iOffset = rect.Height() /4;
	if( m_bSortAscending )
	{
		// draw the arrow pointing upwards.
		pDC->MoveTo( rect.right - 2 * iOffset, iOffset);
		pDC->LineTo( rect.right - iOffset, rect.bottom - iOffset - 1 );
		pDC->LineTo( rect.right - 3 * iOffset - 2, rect.bottom - iOffset - 1 );
		pDC->SelectObject( &penShadow );
		pDC->MoveTo( rect.right - 3 * iOffset - 1, rect.bottom - iOffset - 1 );
		pDC->LineTo( rect.right - 2 * iOffset, iOffset - 1);		
	}
	else
	{
		// draw the arrow pointing downwards.
		pDC->MoveTo( rect.right - iOffset - 1, iOffset );
		pDC->LineTo( rect.right - 2 * iOffset - 1, rect.bottom - iOffset );
		pDC->SelectObject( &penShadow );
		pDC->MoveTo( rect.right - 2 * iOffset - 2, rect.bottom - iOffset );
		pDC->LineTo( rect.right - 3 * iOffset - 1, iOffset );
		pDC->LineTo( rect.right - iOffset - 1, iOffset );		
	}

    pDC->SelectObject(pOldPen);
}


CString CSkinHeaderCtrl::GetItemText(int nItem) const
{
    HD_ITEM hditem;
    TCHAR buf[256];
	
	hditem.mask = HDI_TEXT | HDI_ORDER;
	hditem.pszText = buf;
	hditem.cchTextMax = 255;
    GetItem(nItem, &hditem);
    return buf;
}

void CSkinHeaderCtrl::SetFrameColor(COLORREF crFrame, BOOL bRepaint)
{
    m_crFrame = crFrame;

    if (bRepaint) 
    {
        Invalidate();
    }
}

void CSkinHeaderCtrl::SetDivideColor(COLORREF crDivide, int npenStyle, BOOL bRepaint)
{

    if (m_penDivide.m_hObject != NULL) 
    {
        m_penDivide.DeleteObject();
    }
    m_penDivide.CreatePen(npenStyle, 1, crDivide);

    if (bRepaint) 
    {
        Invalidate();
    }

}


/*=============================================================================
�� �� ���� staticSetColors
��    �ܣ� 
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� COLORREF crText
           COLORREF crBk
           COLORREF crFrame
           COLORREF crDivide
�� �� ֵ�� void 
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��		�汾		�޸���		�߶���    �޸�����
2005/03/29  1.0			������                  ����
=============================================================================*/
void CSkinHeaderCtrl::staticSetColors(COLORREF crText,
                                      COLORREF crBk,
                                      COLORREF crFrame)
{
    m_s_crText   = crText;
    m_s_crBk     = crBk;
    m_s_crFrame  = crFrame;
}

/*=============================================================================
�� �� ���� Set3DShow
��    �ܣ� ���ñ�ͷ3dͻ����ʾ
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� BOOL bShow3D          [in]   �Ƿ�3d��ʾ
�� �� ֵ�� void 
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��		�汾		�޸���		�߶���    �޸�����
2007/04/10  1.0			�Է���                ����
=============================================================================*/
void CSkinHeaderCtrl::Set3DShow(BOOL bShow3D)
{
	m_bShow3D=bShow3D;
}
