/********************************************************************
	ģ����:      UILib
	�ļ���:      checkbutton.cpp
	����ļ�:    UILibHead.h
	�ļ�ʵ�ֹ��� 
    ���ߣ�       ������
	�汾��       1.0
-----------------------------------------------------------------------
	�޸ļ�¼:
	��  ��		�汾		�޸���		�߶���    �޸�����
	2004/4/8	1.0			������                 ����

*********************************************************************/


#include "stdafx.h"
#include "UILibHead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCheckButton

COLORREF CCheckButton::m_s_crFrame[2] = {RGB(80, 114, 170), RGB(80, 114, 170)};
COLORREF CCheckButton::m_s_crText[2]  = {RGB(80, 114, 170), -1};
COLORREF CCheckButton::m_s_crCheck[2] = {RGB(0,0,0),::GetSysColor(COLOR_3DSHADOW)};
COLORREF CCheckButton::m_s_crBk       = RGB(241, 242, 244);

CCheckButton::CCheckButton()
{
    //������״̬ʱ��ͼƬ���
    for (int i = 0; i < STATE_MAX; i++)
    {
        m_hBitmap[i] = NULL;
    }

    for (i = 0; i < 2; i++)
    {
        m_crFrame[i] = m_s_crFrame[i];
        m_crCheck[i] = m_s_crCheck[i];
        m_crText[i] = m_s_crText[i];
    }


    m_crBk = m_s_crBk;//::GetSysColor(COLOR_3DFACE);
    m_crFocus = RGB(0, 0, 0);

    m_bDisable = FALSE;
    m_bIsFocussed = FALSE;
    m_bMouseIn = FALSE;

    m_nFrameSize = 15;

    m_bChecked = FALSE;
    m_bTrans = FALSE;
    m_bDown = FALSE;

    //��ť��ͼƬ��С��Ӧ��ϵ,Ĭ�ϰ�ť��ӦͼƬ��
    m_bSizeToContent = FALSE;

    m_pbmpOldBk = NULL;
    m_dcBk.m_hDC = NULL;

    m_pParent = NULL;

    m_bNeedFree = FALSE;
}

CCheckButton::~CCheckButton()
{
    if (m_bNeedFree) 
    {
        FreeResource();
    }
    	// Restore old bitmap (if any)
    if (m_dcBk.m_hDC != NULL) 
    {
        if (m_pbmpOldBk != NULL)
        {
            ::SelectObject(m_dcBk.m_hDC,m_pbmpOldBk);
        }
        ::DeleteObject(m_dcBk.m_hDC);
    }
}


BEGIN_MESSAGE_MAP(CCheckButton, CButton)
	//{{AFX_MSG_MAP(CCheckButton)
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_CONTROL_REFLECT_EX(BN_CLICKED, OnClicked)
	//}}AFX_MSG_MAP
    ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(WM_CXSHADE_RADIO , OnRadioInfo)
	ON_MESSAGE(BM_SETCHECK , OnBMSetCheck)
	ON_MESSAGE(BM_GETCHECK , OnBMGetCheck)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCheckButton message handlers

void CCheckButton::DrawItem(LPDRAWITEMSTRUCT lpDS) 
{
	// TODO: Add your code to draw the specified item
    CDC* pDC = CDC::FromHandle(lpDS->hDC);

    pDC->SetBkMode(TRANSPARENT);
    m_bDisable = (lpDS->itemState & ODS_DISABLED);
    m_bIsFocussed = (lpDS->itemState & ODS_FOCUS);
    m_bDown = (lpDS->itemState & ODS_SELECTED);

    CRect rcFull(lpDS->rcItem);
    CRect rcCheckFrame;
    //Draw background
    if (m_bTrans)
    {
        PaintBk(pDC);
    }
    else
    {
        pDC->FillRect(rcFull, &CBrush(m_crBk));
    }

    if (m_hBitmap[0] != NULL)
    {
        if (m_bSizeToContent)
        {
            GetClientRect(rcCheckFrame);
            DrawBitmap(pDC, rcCheckFrame);
            return;
        }
        rcCheckFrame.left = rcFull.left + 1;
        BITMAP bit;
        GetObject(m_hBitmap[0], sizeof(bit), &bit);
        rcCheckFrame.right = rcCheckFrame.left + bit.bmWidth;
        rcCheckFrame.bottom = (rcFull.top + rcFull.bottom + bit.bmHeight) / 2;
        rcCheckFrame.top = rcCheckFrame.bottom - m_nFrameSize;
        DrawBitmap(pDC, rcCheckFrame);
    }
    else
    {
        rcCheckFrame.left = rcFull.left + 1;
        rcCheckFrame.right = rcCheckFrame.left + m_nFrameSize;
        rcCheckFrame.bottom = (rcFull.top + rcFull.bottom + m_nFrameSize) / 2;
        rcCheckFrame.top = rcCheckFrame.bottom - m_nFrameSize;
        DrawTextCheck(pDC, rcCheckFrame);
    }

    //Draw the text
    CRect rcText(rcFull);
    rcText.left = rcCheckFrame.right + 3;
 
    CString strText;
    GetWindowText(strText);

    if (m_bDisable)
    {
        if (m_crText[1] == (DWORD)-1)
        {
            rcText.OffsetRect(1,1);
            pDC->SetTextColor(RGB(255,255,255));
            pDC->DrawText(strText, rcText, DT_VCENTER|DT_LEFT|DT_SINGLELINE);
            rcText.OffsetRect(-1,-1);
            pDC->SetTextColor(RGB(128,128,128));
        }
        else
        {
             pDC->SetTextColor(m_crText[1]);
        }
    }
    else
    {
        pDC->SetTextColor(m_crText[0]);
    }
    pDC->DrawText(strText, rcText, DT_VCENTER|DT_LEFT|DT_SINGLELINE);

}

BOOL CCheckButton::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
}

void CCheckButton::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	m_Style=GetButtonStyle();	///get specific BS_ styles
	if ((m_Style & BS_AUTOCHECKBOX)==BS_AUTOCHECKBOX)
//		||((m_Style & BS_CHECKBOX)==BS_CHECKBOX))
    {
		m_Style=BS_CHECKBOX;
    }
	else if ((m_Style & BS_AUTORADIOBUTTON)==BS_AUTORADIOBUTTON)
//			||((m_Style & BS_RADIOBUTTON)==BS_RADIOBUTTON))
    {
        m_Style=BS_RADIOBUTTON;
    }
	else 
    {
       m_Style=BS_PUSHBUTTON; 
    }

	CButton::PreSubclassWindow();
	ModifyStyle(0, BS_OWNERDRAW);
}

void CCheckButton::CancelHover()
{
    if (m_bMouseIn)
    {
        m_bMouseIn = FALSE;
        Invalidate();
    }
}

void CCheckButton::OnMouseMove(UINT nFlags, CPoint point) 
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
	
	CButton::OnMouseMove(nFlags, point);
}

LRESULT CCheckButton::OnMouseLeave(WPARAM, LPARAM)
{
    CancelHover();
	return 0;
}

void CCheckButton::DrawTextCheck(CDC* pDC, CRect rcCheckFrame)
{

    if (m_Style == BS_RADIOBUTTON)
    {
        CRgn rgn;
        rgn.CreateEllipticRgn(rcCheckFrame.left, rcCheckFrame.top, rcCheckFrame.right, rcCheckFrame.bottom);
        if (!m_bDisable)
        {
            pDC->FillRgn(&rgn, &CBrush(RGB(255,255,255)));
            pDC->FrameRgn(&rgn, &CBrush(m_crFrame[0]), 1, 1);
        }
        else
        {
            pDC->FrameRgn(&rgn, &CBrush(m_crFrame[1]), 1, 1);
        }
    }
    else
    {
            //Draw Frame
        rcCheckFrame.DeflateRect(1,1);
        if (!m_bDisable)
        {
            pDC->FillRect(rcCheckFrame, &CBrush(RGB(255,255,255)));
            pDC->FrameRect(rcCheckFrame, &CBrush(m_crFrame[0])); 
        }
        else
        {
            pDC->FrameRect(rcCheckFrame, &CBrush(m_crFrame[1])); 
        }
    }


    //Draw Check
    if (m_bChecked)
    {
        DrawCheck(pDC, rcCheckFrame, m_crCheck[m_bDisable? 1 : 0]);
    }
}

void CCheckButton::DrawCheck(CDC *pDC, CRect rect, COLORREF crCheck)
{
    rect.DeflateRect(2, 2);
    if (m_Style == BS_RADIOBUTTON)
    {
        CRgn rgn;
        rgn.CreateEllipticRgn(rect.left, rect.top, rect.right, rect.bottom);
        pDC->FillRgn(&rgn, &CBrush(crCheck));
        return;
    }

    CPen checkPen;
    CPen *pOldPen;

    int nSize = rect.Width()/2;
    checkPen.CreatePen(PS_SOLID , 2, crCheck);
    pOldPen = pDC->SelectObject(&checkPen);

    pDC->MoveTo(rect.left, rect.bottom - nSize);
    pDC->LineTo(rect.left + nSize, rect.bottom);
    pDC->LineTo(rect.right, rect.top);

    checkPen.DeleteObject();
    pDC->SelectObject(pOldPen);
}

void CCheckButton::PaintBk(CDC *pDC)
{
	CRect rect;
	GetClientRect(rect);

    if (NULL == m_pParent) 
    {
        m_pParent = GetParent();
    }

	if (m_dcBk.m_hDC == NULL)
	{
        CClientDC clDC(m_pParent);
	    CRect rect1;

	    GetWindowRect(rect1);
	    m_pParent->ScreenToClient(rect1);

		m_dcBk.CreateCompatibleDC(&clDC);
		m_bmpBk.CreateCompatibleBitmap(&clDC, rect.Width(), rect.Height());
		m_pbmpOldBk = m_dcBk.SelectObject(&m_bmpBk);
		m_dcBk.BitBlt(0, 0, rect.Width(), rect.Height(), &clDC, rect1.left, rect1.top, SRCCOPY);
	} // if

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &m_dcBk, 0, 0, SRCCOPY);
}

BOOL CCheckButton::OnClicked() 
{
	// TODO: Add your control notification handler code here
    if (m_Style == BS_RADIOBUTTON)
    {
        SetCheck(1);
    }
    else
    {
        SetCheck(m_bChecked ? 0 : 1);
    }
//	m_bChecked = !m_bChecked;
    Invalidate();
    return FALSE;
}

BOOL CCheckButton::PreTranslateMessage(MSG* pMsg) 
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

LRESULT CCheckButton::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
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

LRESULT CCheckButton::OnBMSetCheck(WPARAM wparam, LPARAM)
{
	BOOL bChecked = (wparam != 0);

    if (bChecked && m_bChecked)
    {
        return 0;
    }
    else
    {
        m_bChecked = bChecked;
    }

    if (m_Style == BS_RADIOBUTTON && m_bChecked)
    {
		HWND hthis,hwnd2,hpwnd;
        HWND hFirstFindWnd = NULL;
		hpwnd = GetParent()->GetSafeHwnd(); //get button parent handle
		hwnd2 = hthis = GetSafeHwnd();      //get this button handle
		if ( hthis != NULL && hpwnd != NULL )
        {				//consistency check
			while ( true )
            {
                //  wanghao 2006/04/12 GetNextDlgGroupItemֻ��ȡEnable�Ŀؼ�, 
                //      �����ʱ��Disable��Radio, ��������ѭ��
                //scan the buttons within the group
				hwnd2=::GetNextDlgGroupItem(hpwnd,hwnd2,0);
				//until we reach again this button or finnished finding
				if ( (hwnd2 == hthis) || (hwnd2 == NULL)
                     || ( hFirstFindWnd != NULL && hFirstFindWnd == hwnd2 ) )
                {
                    break;
                }

                if ( hFirstFindWnd == NULL )
                {
                    hFirstFindWnd = hwnd2;
                }
				//post the uncheck message
                CButton* pRadio = (CButton*)FromHandle(hwnd2);
                if (NULL == pRadio)
                {
                    return 0;
                }
                if ( pRadio->IsWindowEnabled() )//&& pRadio->IsWindowVisible())
                {
                    pRadio->SetCheck(0);
                }
			}
		}
	}

	Invalidate();
	return 0;
}

LRESULT CCheckButton::OnBMGetCheck(WPARAM wparam, LPARAM)
{
   return m_bChecked; 
}	//returns the state for check & radio buttons

LRESULT CCheckButton::OnRadioInfo(WPARAM wparam, LPARAM)
{
	if (m_bChecked)
    {	//only checked buttons need to be unchecked
		m_bChecked = FALSE;
		Invalidate();
	}
	return 0;
}

void CCheckButton::DrawBitmap(CDC *pDC, CRect rcBit)
{
    int nIndex = (m_bChecked ? 0 : 1);
    
    CDC dcMem;
    dcMem.CreateCompatibleDC(pDC);

    if (m_bDisable)
    {
        if (m_hBitmap[nIndex+STATE_DISCHECK] == NULL)
        {
            dcMem.SelectObject(m_hBitmap[nIndex]);
            CDC dcDis;
            CBitmap BMP;
            dcDis.CreateCompatibleDC(pDC);

            BMP.CreateCompatibleBitmap(pDC,  rcBit.Width(), rcBit.Height());
            dcDis.SelectObject(BMP);
            dcDis.BitBlt(rcBit.left, rcBit.top, rcBit.Width(), rcBit.Height(), &dcMem, 0, 0, SRCCOPY);

            DeleteDC(dcDis);
            DeleteDC(dcMem);
            pDC->DrawState(rcBit.TopLeft(), rcBit.Size(), 
                &BMP , DST_BITMAP | DSS_DISABLED);
            return;
        }
        else
        {
            nIndex += STATE_DISCHECK;
        }
    }
    else if (m_bDown)
    {
        if (m_hBitmap[nIndex + STATE_DOWNCHECK] != NULL)
        {
            nIndex += STATE_DOWNCHECK;
        }
    }
    else if (m_bMouseIn)
    {
        if (m_hBitmap[nIndex + STATE_HOTCHECK] != NULL)
        {
            nIndex += STATE_HOTCHECK;
        }
    }

    dcMem.SelectObject(m_hBitmap[nIndex]);
    pDC->BitBlt(rcBit.left, rcBit.top, rcBit.Width(), rcBit.Height(), &dcMem, 0, 0, SRCCOPY);
    dcMem.DeleteDC();
}

//�ӿں���

/*====================================================================
������  ��SetBitmaps
��  ��  ���趨��ť��������ɫ
ȫ�ֱ�������
���������hBMPCheck:         ��ť��Ч��ѡ��ʱ����ťCheckͼƬ�ľ����
          hBMPUncheck:       ��ť��Ч��δѡ��ʱ����ťCheckͼƬ�ľ����
	      hBMPDisableCheck:  ��ťʧЧ��ѡ��ʱ����ťCheckͼƬ�ľ����
	      hBMPDisableUncheck:��ťʧЧ��δѡ��ʱ����ťCheckͼƬ�ľ����
	      hBMPHotCheck:  ��ť���������ѡ��ʱ����ťCheckͼƬ�ľ����
	      hBMPHotUncheck:��ť���������δѡ��ʱ����ťCheckͼƬ�ľ����
����ֵ  ����
====================================================================*/
void CCheckButton::SetBitmaps(HBITMAP hBMPCheck, HBITMAP hBMPUncheck, 
                              HBITMAP hBMPDisableCheck, HBITMAP hBMPDisableUncheck,
                              HBITMAP hBMPHotCheck, HBITMAP hBMPHotUncheck,
                              HBITMAP hBMPDownCheck, HBITMAP hBMPDownUncheck)
{
    
    if (m_bNeedFree) 
    {
        FreeResource();
        m_bNeedFree = FALSE;
    }

    m_hBitmap[STATE_CHECK] = hBMPCheck;
    m_hBitmap[STATE_UNCHECK] = hBMPUncheck;
    m_hBitmap[STATE_DISCHECK] = hBMPDisableCheck;
    m_hBitmap[STATE_DISUNCHECK] = hBMPDisableUncheck;
    m_hBitmap[STATE_HOTCHECK] = hBMPHotCheck;
    m_hBitmap[STATE_HOTUNCHECK] = hBMPHotUncheck;
    m_hBitmap[STATE_DOWNCHECK] = hBMPDownCheck;
    m_hBitmap[STATE_DOWNUNCHECK] = hBMPDownUncheck;

    if (NULL != hBMPCheck)
    {        
        BITMAP csBMP;
        int nRetValue = ::GetObject(hBMPCheck, sizeof(csBMP), &csBMP);
        if (0 == nRetValue)
        {
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
}

/*====================================================================
������  ��SetBitmaps
��  ��  ���趨��ť��������ɫ
ȫ�ֱ�������
���������nBMPCheck:         ��ť��Ч��ѡ��ʱ����ťCheckͼƬ����Դ�š�
          nBMPUncheck:       ��ť��Ч��δѡ��ʱ����ťCheckͼƬ����Դ�š�
	      nBMPDisableCheck:  ��ťʧЧ��ѡ��ʱ����ťCheckͼƬ����Դ�š�
	      nBMPDisableUncheck:��ťʧЧ��δѡ��ʱ����ťCheckͼƬ����Դ�š�
	      nBMPHotCheck:  ��ť���������ѡ��ʱ����ťCheckͼƬ����Դ�š�
	      nBMPHotUncheck:��ť���������δѡ��ʱ����ťCheckͼƬ����Դ�š�
	      nBMPDownCheck:  ��갴����ѡ��ʱ����ťCheckͼƬ����Դ�š�
	      nBMPDownUncheck:��갴����δѡ��ʱ����ťCheckͼƬ����Դ�š�
����ֵ  ����
====================================================================*/
void CCheckButton::SetBitmaps(UINT nBMPCheck, UINT nBMPUncheck, 
                              UINT nBMPDisableCheck, UINT nBMPDisableUncheck,
                              UINT nBMPHotCheck, UINT nBMPHotUncheck,
                              UINT nBMPDownCheck, UINT nBMPDownUncheck)
{
    if (0 == nBMPCheck)
    {
        m_hBitmap[STATE_CHECK] = NULL;
        return;
    }
    
        
    SetBitmaps(CUITools::CreateImage(nBMPCheck), CUITools::CreateImage(nBMPUncheck), 
        CUITools::CreateImage(nBMPDisableCheck), CUITools::CreateImage(nBMPDisableUncheck), 
        CUITools::CreateImage(nBMPHotCheck), CUITools::CreateImage(nBMPHotUncheck),
        CUITools::CreateImage(nBMPDownCheck), CUITools::CreateImage(nBMPDownUncheck));

    m_bNeedFree = TRUE;
}

/*====================================================================
������  ��SetFrameSize
��  ��  ���趨Check��Ĵ�С
ȫ�ֱ�������
���������nSize:Check��ı߳�����ֱ����Ĭ��Ϊ15��
����ֵ  ����
====================================================================*/
void CCheckButton::SetFrameSize(int nSize)
{
    m_nFrameSize = nSize;
}

/*====================================================================
������  ��SetFrameColor
��  ��  ���趨Check�����ɫ
ȫ�ֱ�������
���������crFrame	��ť��Чʱ��Check�����ɫ��
	      crDisable	��ťʧЧʱ��Check�����ɫ��
          bRepaint	����ֵΪTRUEʱ����ť�����ػ�������ֵΪFALSEʱ����ť���´�ˢ��ʱ�ػ���
����ֵ  ����
====================================================================*/
void CCheckButton::SetFrameColor(COLORREF crFrame, COLORREF crDisable, BOOL bRepaint)
{
    m_crFrame[0] = crFrame;
    m_crFrame[1] = crDisable;
    if (bRepaint)
    {
        Invalidate();
    }
}

/*====================================================================
������  ��SetTextColor
��  ��  ���趨��ť��������ɫ
ȫ�ֱ�������
���������crText	��ť��Чʱ����ť���ֵ���ɫ��
	      crDisable	��ťʧЧʱ����ť���ֵ���ɫ��
          bRepaint	����ֵΪTRUEʱ����ť�����ػ�������ֵΪFALSEʱ����ť���´�ˢ��ʱ�ػ���
����ֵ  ����
====================================================================*/
void CCheckButton::SetTextColor(COLORREF crText, COLORREF crDisable, BOOL bRepaint)
{
    m_crText[0] = crText;
    m_crText[1] = crDisable;
    if (bRepaint)
    {
        Invalidate();
    }
}

/*====================================================================
������  ��SetCheckColor
��  ��  ���趨��ťѡ�б�ǵ���ɫ��С����Բ�㣩
ȫ�ֱ�������
���������crCheck	��ť��Чʱ��ѡ�б�ǵ���ɫ��
	      crDisable	��ťʧЧʱ��ѡ�б�ǵ���ɫ��
          bRepaint	����ֵΪTRUEʱ����ť�����ػ�������ֵΪFALSEʱ����ť���´�ˢ��ʱ�ػ���
����ֵ  ����
====================================================================*/
void CCheckButton::SetCheckColor(COLORREF crCheck, COLORREF crDisable, BOOL bRepaint)
{
    m_crCheck[0] = crCheck;
    m_crCheck[1] = crDisable;
    if (bRepaint)
    {
        Invalidate();
    }
}

/*====================================================================
������  ��SetBkColor
��  ��  ���趨��ť��������ɫ
ȫ�ֱ�������
���������crBk	��ť��������ɫ��
          bRepaint	����ֵΪTRUEʱ����ť�����ػ�������ֵΪFALSEʱ����ť���´�ˢ��ʱ�ػ���
����ֵ  ����
====================================================================*/
void CCheckButton::SetBkColor(COLORREF crBk, BOOL bRepaint)
{
    m_crBk = crBk;
    if (bRepaint)
    {
        Invalidate();
    }
}

/*====================================================================
������  ��SetBk
��  ��  ���������ڵı������Ƚϰ�ȫ����ʾ͸��Ч����
ȫ�ֱ�������
���������CDC* pDC	�����ڻ�������CDCָ�롣
����ֵ  ����
====================================================================*/
void CCheckButton::SetBk(CDC *pDC)
{
    if (m_bTrans && (pDC != NULL))
    {
        // Restore old bitmap (if any)
        if (m_dcBk.m_hDC != NULL && m_pbmpOldBk != NULL)
        {
	        m_dcBk.SelectObject(m_pbmpOldBk);
        } // if

        m_bmpBk.DeleteObject();
        m_dcBk.DeleteDC();
        m_dcBk.m_hDC = NULL;
        m_pbmpOldBk = NULL;

        CRect rect;
        CRect rect1;

        GetClientRect(rect);

        GetWindowRect(rect1);
        GetParent()->ScreenToClient(rect1);

        m_dcBk.CreateCompatibleDC(pDC);
        m_bmpBk.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
        m_pbmpOldBk = m_dcBk.SelectObject(&m_bmpBk);
        m_dcBk.BitBlt(0, 0, rect.Width(), rect.Height(), pDC, rect1.left, rect1.top, SRCCOPY);
	} // if
}

/*====================================================================
������  ��InitTooltip
��  ��  ����ʼ��Tooltip����
ȫ�ֱ�������
�����������
����ֵ  ����
====================================================================*/
void CCheckButton::InitTooltip()
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
void CCheckButton::SetTooltipText(LPCTSTR lpszText, BOOL bActivate)
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
void CCheckButton::SetTooltipText(UINT nText, BOOL bActivate)
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
void CCheckButton::EnableTooltipText(BOOL bActivate)
{
    if (m_ToolTip.GetToolCount() == 0)
    {
        return;
    }

    m_ToolTip.Activate(bActivate);
}

/*====================================================================
������  ��SizeToContent
��  ��  ���趨��ť��ͼƬ��С����Ӧ��ϵ��
ȫ�ֱ�������
���������bActivate:TRUEʱ��ť��ӦͼƬ��FALSEͼƬ��Ӧ��ť��
����ֵ  ����
====================================================================*/
void CCheckButton::SizeToContent(BOOL bEnable)
{
    m_bSizeToContent = bEnable;

    if (NULL != m_hBitmap[0])
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
������  ��SetBkTrans
��  ��  ���趨��ť�Ƿ�͸����
ȫ�ֱ�������
���������bTrans:TRUEʱ��ť͸��������ȡ�����ڣ�FALSE��ť��͸����
����ֵ  ����
====================================================================*/
void CCheckButton::SetBkTrans(BOOL bTrans)
{
    m_bTrans = bTrans;
}

/*====================================================================
������  ��SetBkParent
��  ��  ���趨��ť�ĸ����ڡ�
ȫ�ֱ�������
���������bTrans:TRUEʱ��ť͸��������ȡ�����ڣ�FALSE��ť��͸����
����ֵ  ����
====================================================================*/
void CCheckButton::SetBkParent(CWnd *pParent)
{
    if (pParent != NULL) 
    {
        m_pParent = pParent;
    }
    else
    {
        m_pParent = GetParent();
    }
}

void CCheckButton::FreeResource()
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



/*=============================================================================
�� �� ���� staticSetBkColor
��    �ܣ� 
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� COLORREF crBk
�� �� ֵ�� void 
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��		�汾		�޸���		�߶���    �޸�����
2005/03/29  1.0			������                  ����
=============================================================================*/
void CCheckButton::staticSetBkColor(COLORREF crBk)
{
    m_s_crBk = crBk;
}


/*=============================================================================
�� �� ���� staticSetCheckColor
��    �ܣ� 
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� COLORREF crCheck
           COLORREF crDisable
�� �� ֵ�� void 
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��		�汾		�޸���		�߶���    �޸�����
2005/03/29  1.0			������                  ����
=============================================================================*/
void CCheckButton::staticSetCheckColor(COLORREF crCheck, COLORREF crDisable)
{
    m_s_crCheck[0] = crCheck;
    m_s_crCheck[1] = crDisable;
}


/*=============================================================================
�� �� ���� staticSetFrameColor
��    �ܣ� 
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� COLORREF crFrame
           COLORREF crDisable
�� �� ֵ�� void 
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��		�汾		�޸���		�߶���    �޸�����
2005/03/29  1.0			������                  ����
=============================================================================*/
void CCheckButton::staticSetFrameColor(COLORREF crFrame, COLORREF crDisable)
{
    m_s_crFrame[0] = crFrame;
    m_s_crFrame[1] = crDisable;
}


/*=============================================================================
�� �� ���� staticSetTextColor
��    �ܣ� 
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� COLORREF crText
           COLORREF crDisable 
�� �� ֵ�� void 
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��		�汾		�޸���		�߶���    �޸�����
2005/03/29  1.0			������                  ����
=============================================================================*/
void CCheckButton::staticSetTextColor(COLORREF crText, COLORREF crDisable /* = -1 */)
{
    m_s_crText[0] = crText;
    m_s_crText[1] = crDisable;
}