/********************************************************************
	ģ����:      UILib
	�ļ���:      TextButton30.cpp
	����ļ�:    UILibHead.h
	�ļ�ʵ�ֹ��� 3.0���ְ�ť��
    ���ߣ�       ������
	�汾��       1.0
---------------------------------------------------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��		�汾		�޸���		�߶���    �޸�����
	7/20/2004	1.0         ������               ------------

*********************************************************************/

#include "stdafx.h"
#include "UIlibHead.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//CTextButton30::m_s_bSetStatic = FALSE;
CTextButton30::CTextButton30()
{
    m_bMouseIn = FALSE;

    m_crFrame[0] = RGB(63,92,160);
    m_crFrame[1] = RGB(109,109,109);
    m_crText = RGB(234,236,239);
    m_crBk[0] = RGB(115,144,196);//::GetSysColor(COLOR_3DFACE);
    m_crBk[1] = RGB(172,172,172);
}

CTextButton30::~CTextButton30()
{
    
}

BEGIN_MESSAGE_MAP(CTextButton30, CButton)
	//{{AFX_MSG_MAP(CTextButton30)
    ON_WM_ACTIVATE()
	ON_WM_CANCELMODE()
	ON_WM_ENABLE()
	ON_WM_KILLFOCUS()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTextButton30 message handlers
//�趨��ť�Ի����
void CTextButton30::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	CButton::PreSubclassWindow();
	ModifyStyle(0, BS_OWNERDRAW);
}

//����뿪ʱ�ػ���ť��
void CTextButton30::CancelHover()
{
    if (m_bMouseIn)
    {
        m_bMouseIn = FALSE;
        Invalidate();
    }
}

void CTextButton30::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CButton::OnActivate(nState, pWndOther, bMinimized);
	
	// TODO: Add your message handler code here
	if (nState == WA_INACTIVE)
    {
        CancelHover();
    }
}


void CTextButton30::OnCancelMode() 
{
	CButton::OnCancelMode();
	
	// TODO: Add your message handler code here
	CancelHover();
}

void CTextButton30::OnEnable(BOOL bEnable) 
{
	CButton::OnEnable(bEnable);
	
	// TODO: Add your message handler code here
	if (!bEnable)	
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

void CTextButton30::OnKillFocus(CWnd* pNewWnd) 
{
	CButton::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
	CancelHover();
}

void CTextButton30::OnMouseMove(UINT nFlags, CPoint point) 
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
LRESULT CTextButton30::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	CancelHover();
	return 0;
} 


//�Ի���ť
void CTextButton30::DrawItem(LPDRAWITEMSTRUCT lpDS) 
{
	// TODO: Add your code to draw the specified item
    m_bDown = (lpDS->itemState & ODS_SELECTED);
    m_bDisable = (lpDS->itemState & ODS_DISABLED);
    m_bFocus = (lpDS->itemState & ODS_FOCUS);

    CDC* pDC = CDC::FromHandle(lpDS->hDC);
    CRect rcFull(lpDS->rcItem);
    
    if (m_bDisable) 
    {
        pDC->FrameRect(rcFull, &CBrush(m_crFrame[1]));
        rcFull.DeflateRect(1, 1);
        pDC->FrameRect(rcFull, &CBrush(m_crText));
        rcFull.DeflateRect(1, 1);
        pDC->FillSolidRect(rcFull, m_crBk[1]);
        pDC->SetBkColor(m_crBk[1]);
        pDC->SetTextColor(m_crText);
    }
    else if (m_bDown)
    {
        pDC->SetBkColor(m_crText);
        pDC->SetTextColor(m_crBk[0]);
        pDC->FillSolidRect(rcFull, m_crText);
        pDC->FrameRect(rcFull, &CBrush(m_crFrame[0]));
        rcFull.DeflateRect(1,1);
        pDC->Draw3dRect(rcFull, m_crFrame[0], m_crText);
        rcFull.OffsetRect(1,1);
    }
    else if (m_bMouseIn) 
    {
        pDC->SetBkColor(m_crText);
        pDC->SetTextColor(m_crBk[0]);
        pDC->FillSolidRect(rcFull, m_crText);
        pDC->FrameRect(rcFull, &CBrush(m_crFrame[0]));
    }
    else
    {
        pDC->FrameRect(rcFull, &CBrush(m_crFrame[0]));
        rcFull.DeflateRect(1, 1);
        pDC->FrameRect(rcFull, &CBrush(m_crText));
        rcFull.DeflateRect(1, 1);
        pDC->FillSolidRect(rcFull, m_crBk[0]);
        pDC->SetBkColor(m_crBk[0]);
        pDC->SetTextColor(m_crText);
    }

    pDC->SetBkMode(TRANSPARENT);

    CString strText;
    GetWindowText(strText);
    pDC->DrawText(strText, rcFull, DT_SINGLELINE|DT_CENTER|DT_VCENTER);

    if (m_bFocus) 
    {
        CRect rect(lpDS->rcItem);
        rect.DeflateRect(3,3);
        pDC->DrawFocusRect(rect);
    }
}

BOOL CTextButton30::PreTranslateMessage(MSG* pMsg) 
{
    InitTooltip();
	m_ToolTip.RelayEvent(pMsg);

	// TODO: Add your specialized code here and/or call the base class
    if (pMsg->message == WM_LBUTTONDBLCLK)
    {
        pMsg->message = WM_LBUTTONDOWN;
    }

	return CButton::PreTranslateMessage(pMsg);
}

LRESULT CTextButton30::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
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

	if (message == BM_SETSTYLE) 
	{
        wParam |= BS_OWNERDRAW;
	}
	return CButton::DefWindowProc(message, wParam, lParam);
}

/*====================================================================
������  ��SetTooltipText
��  ��  ������Tooltip�ı�
ȫ�ֱ�������
���������lpszText: �ı����ݣ�
          bActivate:�Ƿ�����Tooltip���ܡ�
����ֵ  ����
====================================================================*/
void CTextButton30::SetTooltipText(LPCTSTR lpszText, BOOL bActivate)
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
������  ��InitTooltip
��  ��  ����ʼ��Tooltip����
ȫ�ֱ�������
�����������
����ֵ  ����
====================================================================*/
void CTextButton30::InitTooltip()
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
������  ��EnableTooltipText
��  ��  ������Tooltip���ܡ�
ȫ�ֱ�������
���������bActivate:�Ƿ�����Tooltip���ܡ�
����ֵ  ����
====================================================================*/
void CTextButton30::EnableTooltipText(BOOL bActivate)
{
    if (m_ToolTip.GetToolCount() == 0)
    {
        return;
    }

    m_ToolTip.Activate(bActivate);
}
