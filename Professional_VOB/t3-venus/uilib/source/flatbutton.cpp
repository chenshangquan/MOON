/********************************************************************
	ģ����:      UILib
	�ļ���:      flatbutton.cpp
	����ļ�:    UILibHead.h
	�ļ�ʵ�ֹ��� 
    ���ߣ�       ������
	�汾��       1.0
---------------------------------------------------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��		�汾		�޸���		�߶���    �޸�����
	3/24/2004	1.0         ������               ------------

*********************************************************************/

#include "stdafx.h"
#include "UILibHead.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFlatButton

UINT CFlatButton::m_s_nType = TYPE_NORMAL;

COLORREF CFlatButton::m_s_crFrame[STATE_MAX] = {RGB(158,160,161),
                     RGB(248,138,8), RGB(248,138,8), RGB(158,160,161)};
COLORREF CFlatButton::m_s_crText[STATE_MAX] = {RGB(66,94,145),
                     RGB(66,94,145), RGB(66,94,145), RGB(128,128,128)};
COLORREF CFlatButton::m_s_crBk[STATE_MAX] = {RGB(234,236,239),
                     RGB(234,236,239), RGB(234,236,239), RGB(234,236,239)};

RECT CFlatButton::m_s_rcTextPtOff = {-3, -1, -3, -1};

IMPLEMENT_DYNAMIC(CFlatButton, CButton)
CFlatButton::CFlatButton()
{

    if (TYPE_NORMAL == m_s_nType) 
    {
        //����״̬ʱ��ͼƬ���
        for (int i = 0; i < STATE_MAX; i++)
        {
            m_hBitmap[i] = NULL;
            m_crFrame[i] = m_s_crFrame[i];
            m_crText[i] = m_s_crText[i];
            m_crBk[i] = m_s_crBk[i];//::GetSysColor(COLOR_3DFACE);
        }
        //���ְ�ť��Բ�ǰ뾶
        m_ptRectRound = CPoint(5, 5);
    }
    else
    {
        //����״̬ʱ��ͼƬ���
        for (int i = 0; i < STATE_MAX; i++)
        {
            m_hBitmap[i] = NULL;
            m_crFrame[i] = RGB(0,0,0);
            m_crText[i] = RGB(0,0,0);
            m_crBk[i] = RGB(0xc2, 0xca, 0xd8);//::GetSysColor(COLOR_3DFACE);
        }
        m_crBk[0] = RGB(0x96, 0xa2, 0xb9);
        m_crText[3] = -1;//RGB(128,128,128);
        //���ְ�ť��Բ�ǰ뾶
        m_ptRectRound = CPoint(0, 0);
        
    }
    
    m_crRoundBk = RGB(234,236,239);

    m_crFocus = RGB(0, 0, 0);

    //��ť��ͼƬ��С��Ӧ��ϵ,Ĭ��ͼƬ��Ӧ��ť��
    m_bSizeToContent = FALSE;

    //��ť״̬
    m_bDown = FALSE;
    m_bDisable = FALSE;
    m_bFocus = FALSE;
    m_bMouseIn = FALSE;

    m_bNeedFocus = TRUE;

    m_bNeedFree = FALSE;

    //��ť��ѹʱ��ͼ������ֵ�ƫ��
    m_ptPressStyle = CPoint(1, 1);

    //��ť�˵����
    m_hParentWndMenu = NULL;
	m_bMenuDisplayed = FALSE;
    m_csCallbacks.hWnd = NULL;

    m_bChecked = FALSE;

    m_Menu.m_hMenu = NULL;

    //ͼƬ��ť����  [zhuyr][3/28/2005]
    m_bShowText = FALSE;
    m_enPosType = TEXT_POS_CENTER;
    m_ptRealTextPos = CPoint(1, 1);

    m_rcTextPtOff = m_s_rcTextPtOff;
}

CFlatButton::~CFlatButton()
{
    if (m_bNeedFree) 
    {
        FreeResource();
    }

    if (m_Menu.m_hMenu != NULL)
    {
        m_Menu.DestroyMenu();
    }
}

void CFlatButton::FreeResource()
{
    for (INT i = 0; i < STATE_MAX; i++)
    {
        if (NULL != m_hBitmap[i])
        {
            ::DeleteObject(m_hBitmap[i]);
            m_hBitmap[i] = NULL;
        }
    }
}

BEGIN_MESSAGE_MAP(CFlatButton, CButton)
	//{{AFX_MSG_MAP(CFlatButton)
	ON_WM_ACTIVATE()
	ON_WM_CANCELMODE()
	ON_WM_ENABLE()
	ON_WM_KILLFOCUS()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_CONTROL_REFLECT_EX(BN_CLICKED, OnClicked)
    ON_WM_MEASUREITEM()
    ON_WM_MENUCHAR()
	//}}AFX_MSG_MAP
    
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlatButton message handlers
//�趨��ť�Ի����
void CFlatButton::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	CButton::PreSubclassWindow();
	ModifyStyle(0, BS_OWNERDRAW);
}

//����뿪ʱ�ػ���ť��
void CFlatButton::CancelHover()
{
    if (m_bMouseIn)
    {
        m_bMouseIn = FALSE;
        Invalidate();
    }
}

void CFlatButton::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CButton::OnActivate(nState, pWndOther, bMinimized);
	
	// TODO: Add your message handler code here
	if (nState == WA_INACTIVE)
    {
        CancelHover();
    }
}

BOOL CFlatButton::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return CButton::OnEraseBkgnd(pDC);
}

void CFlatButton::OnCancelMode() 
{
	CButton::OnCancelMode();
	
	// TODO: Add your message handler code here
	CancelHover();
}

void CFlatButton::OnEnable(BOOL bEnable) 
{
	CButton::OnEnable(bEnable);
	
	// TODO: Add your message handler code here
	if (!bEnable)	
	{
        if (GetFocus() == this)
        {
		    CWnd*	pWnd = GetParent()->GetNextDlgTabItem(this);
		    if (pWnd == NULL)
            {
                pWnd = GetParent();
            }
		    
		    if (pWnd != NULL)
            {
			    pWnd->SetFocus();
            }

		    CancelHover();
        }
	}
}

void CFlatButton::OnKillFocus(CWnd* pNewWnd) 
{
	CButton::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
	CancelHover();
}

void CFlatButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CWnd*				wndUnderMouse = NULL;
	CWnd*				wndActive = this;
	CButton::OnMouseMove(nFlags, point);

    ClientToScreen(&point);
	wndUnderMouse = WindowFromPoint(point);

    if ((nFlags & MK_LBUTTON) && !m_bMouseIn)
    {
        return;
    }

    if (NULL == wndUnderMouse)
    {
        return;
    }
    if ((wndUnderMouse->m_hWnd == m_hWnd) && (wndActive != NULL))
    {
        if (!m_bMouseIn)
        {
            m_bMouseIn = TRUE;
            Invalidate();

	        TRACKMOUSEEVENT		csTME;
            csTME.cbSize = sizeof(csTME);
			csTME.dwFlags = TME_LEAVE;
			csTME.hwndTrack = m_hWnd;
			::_TrackMouseEvent(&csTME);
        }
    }
    else
    {
        CancelHover();
    }
}

// Handler for WM_MOUSELEAVE
LRESULT CFlatButton::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	CancelHover();
	return 0;
} 

//Ϊ���趨POP���͵Ĳ˵���С��
void CFlatButton::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	if (lpMeasureItemStruct->CtlType == ODT_MENU)
	{
		if (IsMenu((HMENU)lpMeasureItemStruct->itemID)
            && CSkinMenu::IsMenu((HMENU)lpMeasureItemStruct->itemID))
		{
			m_Menu.MeasureItem(lpMeasureItemStruct);
			return;
		} // if
	} // if
        
    CButton::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}


LRESULT CFlatButton::OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu) 
{
	// TODO: Add your message handler code here and/or call default
    if (CSkinMenu::IsMenu(pMenu->m_hMenu)) 
	{
        return ((CSkinMenu*)pMenu)->OnSkinMenuChar(nChar, nFlags, pMenu);
	}
	return CButton::OnMenuChar(nChar, nFlags, pMenu);
}

//�Ի���ť
void CFlatButton::DrawItem(LPDRAWITEMSTRUCT lpDS) 
{
	// TODO: Add your code to draw the specified item
    m_bDown = (lpDS->itemState & ODS_SELECTED);
    m_bDisable = (lpDS->itemState & ODS_DISABLED);
    m_bFocus = (lpDS->itemState & ODS_FOCUS);

    BOOL bDrawMenu = FALSE;

    if (m_Menu.m_hMenu != NULL)
    {
        if (m_bMenuDisplayed)
        {
            m_bDown = TRUE;
        }
        else if (m_bDown)
        {
            bDrawMenu = TRUE;
        }
    }

    if (NULL == m_hBitmap[STATE_OUT])
    {
        DrawTexT(lpDS);
        if (bDrawMenu) 
        {
            OnPopupMenu(CRect(lpDS->rcItem));
        }
        return;
    }

    CDC* pDC = CDC::FromHandle(lpDS->hDC);
    CBrush br(RGB(0, 0, 0));

    pDC->SetBkMode(TRANSPARENT);
    DrawBitmap(pDC, lpDS->rcItem);

    if (m_bShowText)
    {
        DrawTextAtPt(pDC, lpDS->rcItem);
    }

    CRect rect(lpDS->rcItem);
    
    if (m_bFocus && m_bNeedFocus)
    {
        rect.DeflateRect(3, 3);
        pDC->DrawFocusRect(rect);
    }
    if (bDrawMenu) 
    {
        OnPopupMenu(CRect(lpDS->rcItem));
    }
}

//��ͼƬ
void CFlatButton::DrawBitmap(CDC *pDC, RECT rect)
{
    int nState = GetCurState();
    HBITMAP hBitmap = m_hBitmap[nState];
    BOOL bDisable = FALSE;

    if (m_bDisable)   //��ʧЧʱ��ͼƬ
    {
        if (NULL == m_hBitmap[STATE_DISABLE])
        {
            hBitmap = m_hBitmap[STATE_OUT];
            bDisable = TRUE;
        }
    }
    //ͼƬ��������Ч��  [zhuyr][9/19/2005]
//    else if (m_bDown) //��ť������
//    {
//        ::OffsetRect(&rect, m_ptPressStyle.x, m_ptPressStyle.y);
//    }

    int cx = rect.right - rect.left;
    int cy = rect.bottom - rect.top;
    BITMAP bmp;
    GetObject(hBitmap, sizeof(BITMAP), &bmp);

    CDC dcMem;
    dcMem.CreateCompatibleDC(pDC);
    HBITMAP hOldBitmap = (HBITMAP)dcMem.SelectObject(hBitmap);

    if (!bDisable)
    {
        if (m_bSizeToContent)
        {
            pDC->BitBlt(rect.left, rect.top, cx, cy, &dcMem, 0, 0, SRCCOPY);
        }
        else
        {  
            pDC->StretchBlt(rect.left, rect.top, cx, cy, &dcMem, 0, 0, bmp.bmWidth,
                bmp.bmHeight, SRCCOPY);
        }
    }
    else
    {
        CDC dcDis;
        CBitmap BMP;
        dcDis.CreateCompatibleDC(pDC);
        if (m_bSizeToContent)
        {
            BMP.CreateCompatibleBitmap(pDC,  bmp.bmWidth, bmp.bmHeight);
            dcDis.SelectObject(BMP);
            dcDis.BitBlt(rect.left, rect.top, cx, cy, &dcMem, 0, 0, SRCCOPY);

            DeleteDC(dcDis);
            pDC->DrawState(CPoint(rect.left,rect.top),
                CSize(bmp.bmWidth,bmp.bmHeight), 
                &BMP , DST_BITMAP | DSS_DISABLED); 
        }
        else
        { 
            BMP.CreateCompatibleBitmap(pDC,  cx, cy);
            dcDis.SelectObject(BMP);
            dcDis.StretchBlt(rect.left, rect.top, cx, cy, &dcMem, 0, 0, bmp.bmWidth,
                bmp.bmHeight, SRCCOPY);

            DeleteDC(dcDis);
            pDC->DrawState(CPoint(rect.left,rect.top),
                CSize(cx,cy), &BMP, DST_BITMAP | DSS_DISABLED); 
        }
    }

    dcMem.SelectObject(hOldBitmap);
	DeleteDC(dcMem);
}

//�жϵ�ǰ��ť��״̬��
int CFlatButton::GetCurState()
{
    if (m_bDisable)   //��ʧЧʱ��ͼƬ
    {
       return STATE_DISABLE;
    }
    else if (m_bDown) //��ť������
    {
        return STATE_DOWN;
    }
    else if (m_bMouseIn)  //����ڰ�ť�ϣ�����û�б����¡� || (!m_bNeedFocus && m_bFocus)
    {
        return STATE_IN;
    }

    return STATE_OUT;
}

//�����ְ�ť
void CFlatButton::DrawTexT(LPDRAWITEMSTRUCT lpDS)
{
    CDC* pDC = CDC::FromHandle(lpDS->hDC);
    CRect rect(lpDS->rcItem);
    COLORREF crBk, crText;
    int nStateValue = GetCurState();

    crBk = m_crBk[nStateValue];
    crText = m_crText[nStateValue];
    if (crBk == (unsigned long)-1)
    {
        crBk = RGB(200, 208, 212);//0xc8d0d4; GetSysColor(COLOR_3DFACE);
 
    }

    pDC->SetBkMode(TRANSPARENT);

    if (CPoint(0,0) == m_ptRectRound) 
    {
        pDC->FillSolidRect(rect, crBk);
        pDC->FrameRect(rect, &CBrush(m_crFrame[nStateValue]));
    }
    else
    {
        pDC->FillSolidRect(rect, m_crRoundBk);
        CRgn rgn;
        GetOwnRgn(rect, rgn);
        if (m_crRoundBk != crBk) 
        {
            pDC->FillRgn(&rgn, &CBrush(crBk));
        }
        pDC->FrameRgn(&rgn, &CBrush(m_crFrame[nStateValue]), 1, 1);
    }
    rect.InflateRect(1,1);

    if (STATE_DOWN == nStateValue)
    {
        rect.OffsetRect(m_ptPressStyle);
    }

    CString strTitle;
    GetWindowText(strTitle);

    if (crText == (unsigned long)-1)
    {
        rect.OffsetRect(1,1);
        pDC->SetTextColor(RGB(255,255,255));
        pDC->DrawText(strTitle, rect, DT_VCENTER|DT_CENTER|DT_SINGLELINE);
        rect.OffsetRect(-1,-1);
        pDC->SetTextColor(RGB(128,128,128));
        pDC->DrawText(strTitle, rect, DT_VCENTER|DT_CENTER|DT_SINGLELINE);
    }
    else
    {
        pDC->SetTextColor(crText);
        pDC->DrawText(strTitle, rect, DT_VCENTER|DT_CENTER|DT_SINGLELINE);
    }
    
    if (m_bFocus && m_bNeedFocus)
    {
        CRect temp(lpDS->rcItem);
        temp.DeflateRect(3, 2, 4, 4);
        pDC->DrawFocusRect(temp);
    }
  
}

void CFlatButton::DrawTextAtPt(CDC *pDC, RECT rect)
{
    COLORREF crText;
    int nStateValue = GetCurState();

    crText = m_crText[nStateValue];
    pDC->SetBkMode(TRANSPARENT);
    pDC->SetTextColor(crText);

    CString strTitle;
    GetWindowText(strTitle);
    UINT nType = DT_SINGLELINE;
    
    switch (m_enPosType) 
    {
    case TEXT_POS_CUSTOM:
        rect.left = m_ptRealTextPos.x + (m_bDown ? m_ptPressStyle.x : 0);
        rect.top = m_ptRealTextPos.y + (m_bDown ? m_ptPressStyle.y : 0);
        pDC->DrawText(strTitle, &rect, DT_LEFT|DT_SINGLELINE|DT_TOP);
        return;
    case TEXT_POS_LEFT:
        nType |= DT_LEFT|DT_VCENTER;
    	break;
    case TEXT_POS_LEFTTOP:
    	break;
    case TEXT_POS_LEFTBOTTOM:
        nType |= DT_LEFT|DT_BOTTOM;
    	break;
    case TEXT_POS_RIGHT:
        nType |= DT_RIGHT|DT_VCENTER;
    	break;
    case TEXT_POS_RIGHTTOP:
        nType |= DT_RIGHT|DT_TOP;
    	break;
    case TEXT_POS_RIGHTBOTTOM:
        nType |= DT_RIGHT|DT_BOTTOM;
    	break;
    case TEXT_POS_TOP:
        nType |= DT_CENTER|DT_TOP;
        break;
    case TEXT_POS_BOTTOM:
        nType |= DT_CENTER|DT_BOTTOM;
        break;
    case TEXT_POS_CENTER:
    default:
        nType |= DT_CENTER|DT_VCENTER;
        ::OffsetRect(&rect, 0, -1);
    	break;
    }

    if (m_bDown)
    {
        ::OffsetRect(&rect, m_ptPressStyle.x, m_ptPressStyle.y);
    }

    rect.left += m_rcTextPtOff.left;
    rect.right += m_rcTextPtOff.right;
    rect.top += m_rcTextPtOff.top;
    rect.bottom += m_rcTextPtOff.bottom;
        
    pDC->DrawText(strTitle, &rect, nType);
}

//�õ�Բ������
void CFlatButton::GetOwnRgn(CRect rect, CRgn &rgn)
{
    rgn.CreateRoundRectRgn(rect.left, rect.top, rect.right, rect.bottom, m_ptRectRound.x, m_ptRectRound.y);
}


BOOL CFlatButton::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
    InitTooltip();
	m_ToolTip.RelayEvent(pMsg);

    if (pMsg->message == WM_LBUTTONDBLCLK)
    {
        pMsg->message = WM_LBUTTONDOWN;
    }

	return CButton::PreTranslateMessage(pMsg);
}

LRESULT CFlatButton::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// ��ȡToolTip����������Ϣ
	if (m_ToolTip.GetSafeHwnd () != NULL)
	{
		if (message == WM_LBUTTONDOWN ||
			message == WM_LBUTTONUP ||
			message == WM_MOUSEMOVE)
		{
			MSG msg;
			ZeroMemory(&msg, sizeof(MSG));
			msg.message = message;
			msg.hwnd = m_hWnd;
			msg.wParam = wParam;
			msg.lParam = lParam;
			GetCursorPos(&msg.pt);
			msg.time = 0;
			m_ToolTip.RelayEvent(&msg);
		}
	}
	
	return CButton::DefWindowProc(message, wParam, lParam);
}

void CFlatButton::OnPopupMenu(CRect rect)
{
    if (m_Menu.m_hMenu != NULL)
    {        
        if (m_bChecked)
        {
            m_bChecked = FALSE;
            return;
        }
 
		m_bMenuDisplayed = TRUE;
        CSkinMenu* pSubMenu = (CSkinMenu*)m_Menu.GetSubMenu(0);
		if (m_csCallbacks.hWnd != NULL)
        {
            ::SendMessage(m_csCallbacks.hWnd, m_csCallbacks.nMessage, (WPARAM)pSubMenu, m_csCallbacks.lParam);
        }
        
        ClientToScreen(rect);
        int xMax = ::GetSystemMetrics(SM_CXSCREEN);
        int yMax = ::GetSystemMetrics(SM_CYSCREEN);
        CSize size = pSubMenu->GetMenuSize();
        if (rect.left < 0) 
        {
            rect.left = 0;
        }
        int x = (rect.left + size.cx > xMax- 17) ? rect.right : rect.left;
        int y = (rect.bottom + size.cy > yMax-3) ? rect.top : rect.bottom;
		DWORD dwRetValue = pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON 
            | TPM_RIGHTBUTTON | TPM_NONOTIFY | TPM_RETURNCMD, 
            x, y, this, NULL);

        m_bMenuDisplayed = FALSE;

        if (dwRetValue == 0)
        {
            CPoint pt;
            ::GetCursorPos(&pt);
            
            if (rect.PtInRect(pt))
            {
                m_bChecked = TRUE;
                return;
            }
            if (NULL != m_hParentWndMenu)
            {
                 ::SetFocus(m_hParentWndMenu);  //Ϊ�˿���ֱ���ü��̲�����
                 SetFocus();
            }
        }
		else
        {
            if (NULL != m_hParentWndMenu)
            {
                ::PostMessage(m_hParentWndMenu, WM_COMMAND, MAKEWPARAM(dwRetValue, 0), (LPARAM)NULL);
                ::SetFocus(m_hParentWndMenu);  //Ϊ�˿���ֱ���ü��̲�����
                SetFocus();
            }
        }
        Invalidate();  
    }
}

//�ɲ˵�ʱ�����ΰ�ťclick��Ϣ��
BOOL CFlatButton::OnClicked() 
{
	// TODO: Add your control notification handler code here
	return (NULL != m_Menu.m_hMenu);
}

//�ӿں���


/*====================================================================
������  ��InitTooltip
��  ��  ����ʼ��Tooltip����
ȫ�ֱ�������
�����������
����ֵ  ����
====================================================================*/
void CFlatButton::InitTooltip()
{
    if (NULL == m_ToolTip.m_hWnd)
    {
        m_ToolTip.Create(this);
        m_ToolTip.Activate(FALSE);
        m_ToolTip.SendMessage(TTM_SETMAXTIPWIDTH, 0, 400);
        m_ToolTip.SetDelayTime( TTDT_AUTOPOP, TOOLTIP_SHOWTIME );
    }
}

/*====================================================================
������  ��SetTooltipText
��  ��  ������Tooltip�ı�
ȫ�ֱ�������
���������lpszText: �ı����ݣ�
          bActivate:�Ƿ�����Tooltip���ܡ�
����ֵ  ����
====================================================================*/
void CFlatButton::SetTooltipText(LPCTSTR lpszText, BOOL bActivate)
{
    if (NULL == lpszText)
    {
        return;
    }

    InitTooltip();

    if (m_ToolTip.GetToolCount() == 0)
    {
        CRect rcBtn;
        GetClientRect(&rcBtn);
        m_ToolTip.AddTool(this, lpszText, rcBtn, 1);
    }

    m_ToolTip.UpdateTipText(lpszText, this, 1);
    m_ToolTip.Activate(bActivate);
}

/*====================================================================
������  ��SetTooltipText
��  ��  ������Tooltip�ı�
ȫ�ֱ�������
���������nText: �ı���������Դ�����ID�ţ�
          bActivate:�Ƿ�����Tooltip���ܡ�
����ֵ  ����
====================================================================*/
void CFlatButton::SetTooltipText(UINT nText, BOOL bActivate)
{
    CString strText;
    strText.LoadString(nText);

    if (!strText.IsEmpty())
    {
        SetTooltipText(strText, bActivate);
    }
}

/*====================================================================
������  ��EnableTooltipText
��  ��  ������Tooltip���ܡ�
ȫ�ֱ�������
���������bActivate:�Ƿ�����Tooltip���ܡ�
����ֵ  ����
====================================================================*/
void CFlatButton::EnableTooltipText(BOOL bActivate)
{
    if (m_ToolTip.GetToolCount() == 0)
    {
        return;
    }

    m_ToolTip.Activate(bActivate);
}


/*====================================================================
������  ��SetBitmaps
��  ��  ���趨��ť��ͼƬ
ȫ�ֱ�������
���������hBitmapNormal: ��ť����ʱ����ťͼƬ�ľ����
          hBitmapOver:   ��ť�������ʱ����ťͼƬ�ľ����
	      hBitmapDown:   ��ť������ʱ����ťͼƬ�ľ����
	      hBitmapDisable:��ťʧЧʱ����ťͼƬ�ľ����
����ֵ  ����
====================================================================*/
void CFlatButton::SetBitmaps(HBITMAP hBitmapNormal, HBITMAP hBitmapOver, HBITMAP hBitmapDown, HBITMAP hBitmapDisable)
{
    int nRetValue = 0;
    BITMAP csBMP;

    if (m_bNeedFree) 
    {
        FreeResource();
        m_bNeedFree = FALSE;
    }

    if (NULL != hBitmapNormal)
    {
        m_hBitmap[STATE_OUT] = hBitmapNormal;
        
        nRetValue = ::GetObject(hBitmapNormal, sizeof(csBMP), &csBMP);
        if (0 == nRetValue)
        {
            FreeResource();
            return;
        }
        m_sizeBitmap.cx = csBMP.bmWidth;
        m_sizeBitmap.cy = csBMP.bmHeight;
        CRect rect;
        GetWindowRect(rect);
        m_sizeButton = rect.Size();
        if (m_bSizeToContent)
        {
            SetWindowPos(NULL, -1, -1, csBMP.bmWidth, csBMP.bmHeight,
						SWP_NOMOVE | SWP_NOZORDER | SWP_NOREDRAW | SWP_NOACTIVATE);
        }
    }

    if (NULL == hBitmapOver)
    {
        m_hBitmap[STATE_IN] = hBitmapNormal;
    }
    else
    {
        m_hBitmap[STATE_IN] = hBitmapOver;
    }

    if (NULL == hBitmapDown)
    {
        m_hBitmap[STATE_DOWN] = hBitmapOver;
    }
    else
    {
        m_hBitmap[STATE_DOWN] = hBitmapDown;
    }
    
    m_hBitmap[STATE_DISABLE] = hBitmapDisable;

    // ����ť����ˢ�³������õ�ͼƬ
    if ( NULL != m_hWnd )
    {
        Invalidate();
    }
}

/*====================================================================
������  ��SetBitmaps
��  ��  ���趨��ť��ͼƬ
ȫ�ֱ�������
���������nBitmapNormal: ��ť����״̬ʱ����ťͼƬ����Դ�š�
          nBitmapOver:   ��ť�������ʱ����ťͼƬ����Դ�š�
	      nBitmapDown:   ��ť������ʱ����ťͼƬ����Դ�š�
	      hBitmapDisable:��ťʧЧʱ����ťͼƬ����Դ�š�
����ֵ  ����
====================================================================*/
void CFlatButton::SetBitmaps(UINT nBitmapNormal, UINT nBitmapOver, UINT nBitmapDown, UINT nBitmapDisable)
{
    if (0 == nBitmapNormal)
    {
        m_hBitmap[STATE_OUT] = NULL;
        return;
    }
    
    SetBitmaps(CUITools::CreateImage(nBitmapNormal), CUITools::CreateImage(nBitmapOver),
        CUITools::CreateImage(nBitmapDown), CUITools::CreateImage(nBitmapDisable));
  
    m_bNeedFree = TRUE;

}

/*====================================================================
������  ��SizeToContent
��  ��  ���趨��ť��ͼƬ��С����Ӧ��ϵ��
ȫ�ֱ�������
���������bActivate:TRUEʱ��ť��ӦͼƬ��FALSEͼƬ��Ӧ��ť��
����ֵ  ����
====================================================================*/
void CFlatButton::SizeToContent(BOOL bEnable)
{
    m_bSizeToContent = bEnable;

    if (NULL != m_hBitmap[STATE_OUT])
    {
        if (bEnable)
        {
            SetWindowPos(NULL, -1, -1, m_sizeBitmap.cx, m_sizeBitmap.cy,
						SWP_NOMOVE | SWP_NOZORDER | SWP_NOREDRAW | SWP_NOACTIVATE);
        }
        else
        {
            SetWindowPos(NULL, -1, -1, m_sizeButton.cx, m_sizeButton.cy,
						SWP_NOMOVE | SWP_NOZORDER | SWP_NOREDRAW | SWP_NOACTIVATE);
        }
    }
}

/*====================================================================
������  ��SetFrameColor
��  ��  ���趨��ť�߿����ɫ
ȫ�ֱ�������
���������crFrameOut	��겻�ڰ�ť��ʱ����ť�߿����ɫ��
	      crFrameIn	����ڰ�ť��ʱ����ť�߿����ɫ��
    	  crFrameDown	��ť������ʱ����ť�߿����ɫ��
	      crFrameDisable	��ťʧЧʱ����ť�߿����ɫ��
          bRepaint	����ֵΪTRUEʱ����ť�����ػ�������ֵΪFALSEʱ����ť���´�ˢ��ʱ�ػ���
����ֵ  ����
====================================================================*/
void CFlatButton::SetFrameColor(COLORREF crFrameOut, COLORREF crFrameIn, COLORREF crFrameDown, COLORREF crFrameDisable, BOOL bRepaint)
{
    m_crFrame[STATE_OUT] = crFrameOut;
    m_crFrame[STATE_IN] = crFrameIn;
    m_crFrame[STATE_DOWN] = crFrameDown;
    m_crFrame[STATE_DISABLE] = crFrameDisable;

    if (bRepaint)
    {
        Invalidate();
    }
}

/*====================================================================
������  ��SetTextColor
��  ��  ���趨��ť�ı�����ɫ
ȫ�ֱ�������
���������crTextOut	��겻�ڰ�ť��ʱ����ť�ı�����ɫ��
	      crTextIn	����ڰ�ť��ʱ����ť�ı�����ɫ��
    	  crTextDown	��ť������ʱ����ť�ı�����ɫ��
	      crTextDisable	��ťʧЧʱ����ť�ı�����ɫ��
          bRepaint	����ֵΪTRUEʱ����ť�����ػ�������ֵΪFALSEʱ����ť���´�ˢ��ʱ�ػ���
����ֵ  ����
====================================================================*/
void CFlatButton::SetTextColor(COLORREF crTextOut, COLORREF crTextIn, COLORREF crTextDown, COLORREF crTextDisable, BOOL bRepaint)
{
    m_crText[STATE_OUT] = crTextOut;
    m_crText[STATE_IN] = crTextIn;
    m_crText[STATE_DOWN] = crTextDown;
    m_crText[STATE_DISABLE] = crTextDisable;

    if (bRepaint)
    {
        Invalidate();
    }
}

/*====================================================================
������  ��SetBkColor
��  ��  ���趨��ť��������ɫ
ȫ�ֱ�������
���������crBkOut	��겻�ڰ�ť��ʱ����ť��������ɫ��
	      crBkIn	����ڰ�ť��ʱ����ť��������ɫ��
    	  crBkDown	��ť������ʱ����ť��������ɫ��
	      crBkDisable	��ťʧЧʱ����ť��������ɫ��
          bRepaint	����ֵΪTRUEʱ����ť�����ػ�������ֵΪFALSEʱ����ť���´�ˢ��ʱ�ػ���
����ֵ  ����
====================================================================*/
void CFlatButton::SetBkColor(COLORREF crBkOut, COLORREF crBkIn, COLORREF crBkDown, COLORREF crBkDisable, BOOL bRepaint)
{
    m_crBk[STATE_OUT] = crBkOut;
    m_crBk[STATE_IN] = crBkIn;
    m_crBk[STATE_DOWN] = crBkDown;
    m_crBk[STATE_DISABLE] = crBkDisable;

    if (bRepaint)
    {
        Invalidate();
    }
}


/*====================================================================
������  ��SetPressStyle
��  ��  ���趨��ť��ѹʱ����ť��ͼ��������ƶ��ķ���;��롣
ȫ�ֱ�������
���������ptPress: ����������λ����ɵ�ʸ������
����ֵ  ����
====================================================================*/
void CFlatButton::SetPressStyle(CPoint ptPress)
{
    m_ptPressStyle = ptPress;
}

/*====================================================================
������  ��SetPressStyle
��  ��  ���趨��ť��ѹʱ����ť��ͼ��������ƶ��ķ���;��롣
ȫ�ֱ�������
���������x: ˮƽ�����ϵ�λ�ơ�
          y: ��ֱ�����ϵ�λ�ơ�
����ֵ  ����
====================================================================*/
void CFlatButton::SetPressStyle(int x, int y)
{
    SetPressStyle(CPoint(x, y));
}

/*====================================================================
������  ��SetMenuEx
��  ��  ���趨�˵���ť��
ȫ�ֱ�������
���������nMenu: �˵�����ԴID�š�
          hParentWnd: �����ھ�������ղ˵�Commad��Ϣ��
          bRepaint	����ֵΪTRUEʱ����ť�����ػ�������ֵΪFALSEʱ����ť���´�ˢ��ʱ�ػ���
����ֵ  ����
====================================================================*/
void CFlatButton::SetMenuEx(UINT nMenu, HWND hParentWnd, BOOL bRepaint)
{
    HINSTANCE	hInstResource	= NULL;

	if (m_Menu.m_hMenu)
	{
		m_Menu.DestroyMenu();
		m_Menu.m_hMenu = NULL;
		m_hParentWndMenu = NULL;
		m_bMenuDisplayed = FALSE;
	} 

	// Load menu
	if (nMenu)
	{
		// Find correct resource handle
		//hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(nMenu), RT_MENU);
		// Load menu resource
		//m_hMenu = ::LoadMenu(hInstResource, MAKEINTRESOURCE(nMenu));
        m_Menu.LoadMenu(nMenu);
		m_hParentWndMenu = hParentWnd;
        if (NULL == m_hParentWndMenu)
        {
            m_hParentWndMenu = ::GetParent(m_hWnd);
        }
		// If something wrong
		if (NULL == m_Menu.m_hMenu || NULL == m_hParentWndMenu)
        {
            return;
        }
	} // if
    
	// Repaint the button
	if (bRepaint)
    {
        Invalidate();
    }
}

/*====================================================================
������  ��SetMenuCallBack
��  ��  ���趨�˵��ص���Ϣ��
ȫ�ֱ�������
���������hWnd:     ��Ϣ�����ߵľ����
          nMessage: ��Ϣ��ID�š�
          lParam:	���õĲ�����������Ϣ���ء�
����ֵ  ����
====================================================================*/
void CFlatButton::SetMenuCallBack(HWND hWnd, UINT nMessage, LPARAM lParam)
{
    m_csCallbacks.hWnd = hWnd;
	m_csCallbacks.nMessage = nMessage;
	m_csCallbacks.lParam = lParam;
    
}

/*====================================================================
������  ��SetRectRound
��  ��  ���趨��ť��Բ�ǰ뾶��
ȫ�ֱ�������
���������x: ˮƽ�����ϵ�Բ�ǰ뾶��
          y: ��ֱ�����ϵ�Բ�ǰ뾶��
����ֵ  ����
====================================================================*/
void CFlatButton::SetRectRound(int x, int y)
{
    m_ptRectRound.x = x;
    m_ptRectRound.y = y;
}

void CFlatButton::SetRectRound(CPoint ptRound)
{
    m_ptRectRound = ptRound;
}

/*====================================================================
������	��    ShowFocus
����		���Ƿ���ʾ�����
�㷨ʵ��	������ѡ�
����ȫ�ֱ�������
�������˵����bShow���Ƿ���ʾ�ı�־��
����ֵ˵����  ��
----------------------------------------------------------------------
�޸ļ�¼:
��  ��		�汾		�޸���		�߶���    �޸�����
2004/05/13	1.0			������                  ����
====================================================================*/
void CFlatButton::ShowFocus(BOOL bShow)
{
    m_bNeedFocus = bShow;
}



/*=============================================================================
�� �� ���� SetShowText
��    �ܣ� �Ƿ���ͼƬ��ť����ʾ��ť����
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� BOOL bShow: �Ƿ���ʾ�ı�־��
           CPoint ptPos: ��ʾ����λ�õ����Ͻǣ��ڰ�ť�ϵ�λ�ã�TEXT_POS_CUSTOM����
           enTextPos TextPos: ������ʾ��λ�ã���Ҫ�õ�һ���ӿ���ΪTEXT_POS_CUSTOM����
�� �� ֵ�� void 
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��		�汾		�޸���		�߶���    �޸�����
2005/03/28  3.6			������                  ����
=============================================================================*/
void CFlatButton::SetShowText(BOOL bShow, CPoint ptPos)
{
    m_bShowText = bShow;
    m_enPosType = TEXT_POS_CUSTOM;
    m_ptRealTextPos = ptPos;
}

void CFlatButton::SetShowText(BOOL bShow, enTextPos TextPos /* = TEXT_POS_CENTER */)
{
    m_bShowText = bShow;
    m_enPosType = TextPos;
}


/*=============================================================================
�� �� ���� SetTextPtOff
��    �ܣ� 
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� CRect rcOff
�� �� ֵ�� void 
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��		�汾		�޸���		�߶���    �޸�����
2005/10/18  4.0			������                  ����
=============================================================================*/
void CFlatButton::SetTextPtOff(CRect rcOff)
{
    m_rcTextPtOff = rcOff;
}


/*=============================================================================
�� �� ���� staticSetBkColor
��    �ܣ� 
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� COLORREF crBkOut
           COLORREF crBkIn
           COLORREF crBkDown
           COLORREF crBkDisable 
�� �� ֵ�� void 
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��		�汾		�޸���		�߶���    �޸�����
2005/03/29  1.0			������                  ����
=============================================================================*/
void CFlatButton::staticSetBkColor(COLORREF crBkOut, COLORREF crBkIn, COLORREF crBkDown,
                                   COLORREF crBkDisable /* = -1 */)
{
    m_s_crBk[0] = crBkOut;
    m_s_crBk[1] = crBkIn;
    m_s_crBk[2] = crBkDown;
    m_s_crBk[3] = crBkDisable;
}


/*=============================================================================
�� �� ���� staticSetFrameColor
��    �ܣ� 
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� COLORREF crFrameOut
           COLORREF crFrameIn
           COLORREF crFrameDown
           COLORREF crFrameDisable
�� �� ֵ�� void 
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��		�汾		�޸���		�߶���    �޸�����
2005/03/29  3.6			������                  ����
=============================================================================*/
void CFlatButton::staticSetFrameColor(COLORREF crFrameOut, COLORREF crFrameIn,
                                      COLORREF crFrameDown, COLORREF crFrameDisable)
{
    m_s_crFrame[0] = crFrameOut;
    m_s_crFrame[1] = crFrameIn;
    m_s_crFrame[2] = crFrameDown;
    m_s_crFrame[3] = crFrameDisable;
}


/*=============================================================================
�� �� ���� staticSetTextColor
��    �ܣ� 
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� COLORREF crTextOut
           COLORREF crTextIn
           COLORREF crTextDown
           COLORREF crTextDisable 
�� �� ֵ�� void 
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��		�汾		�޸���		�߶���    �޸�����
2005/03/29  3.6			������                  ����
=============================================================================*/
void CFlatButton::staticSetTextColor(COLORREF crTextOut, COLORREF crTextIn, 
                                     COLORREF crTextDown, COLORREF crTextDisable /* = -1 */)
{
    m_s_crText[0] = crTextOut;
    m_s_crText[1] = crTextIn;
    m_s_crText[2] = crTextDown;
    m_s_crText[3] = crTextDisable;
}


/*=============================================================================
�� �� ���� static_SetTextPtOff
��    �ܣ� 
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� RECT rcOff
�� �� ֵ�� void 
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��		�汾		�޸���		�߶���    �޸�����
2005/10/18  4.0			������                  ����
=============================================================================*/
void CFlatButton::static_SetTextPtOff(RECT rcOff)
{
    m_s_rcTextPtOff = rcOff;
}
