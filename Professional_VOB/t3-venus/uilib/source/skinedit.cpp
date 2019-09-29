/********************************************************************
	ģ����:      UILib
	�ļ���:      skinedit.cpp
	����ļ�:    UILibHead.h
	�ļ�ʵ�ֹ��� 
    ���ߣ�       ������
	�汾��       1.0
--------------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��		�汾		�޸���		�߶���    �޸�����
	2004/4/8	1.0			������                  ����

*********************************************************************/

#include "stdafx.h"
#include "UILibHead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkinEdit
UINT CSkinEdit::m_s_nType = TYPE_NORMAL;
COLORREF CSkinEdit::m_s_crBk[2] = {RGB(241, 242, 244), RGB(233,233,233)};
COLORREF CSkinEdit::m_s_crText[2] = {RGB(80, 114, 170), RGB(80, 114, 170)};
COLORREF CSkinEdit::m_s_crFrame = RGB(80, 114, 170);

CSkinEdit::CSkinEdit()
{
    if (m_s_nType == TYPE_NORMAL) 
    {
        m_crBk[0] = m_s_crBk[0];
        m_crBk[1] = m_s_crBk[1];

        m_crText[0] = m_s_crText[0];
        m_crText[1] = m_s_crText[1];
        m_crFrame = m_s_crFrame;
        m_bCustomMenu = TRUE;
    }
    else
    {
        m_crBk[0] = RGB(0xeb, 0xf6, 0xe8);
        m_crBk[1] = RGB(0xeb, 0xf6, 0xe8);

        m_crText[0] = RGB(0, 0, 0);
        m_crText[1] = RGB(128, 128, 128);
        m_crFrame = RGB(0, 0, 0);
        m_bCustomMenu = FALSE;
    }
    
    m_brushBk[0].CreateSolidBrush(m_crBk[0]);
    m_brushBk[1].CreateSolidBrush(m_crBk[1]);
}

CSkinEdit::~CSkinEdit()
{
    if (m_brushBk[0].m_hObject != NULL) 
    {
        m_brushBk[0].DeleteObject();
    }
    if (m_brushBk[1].m_hObject != NULL) 
    {
        m_brushBk[1].DeleteObject();
    }
}


BEGIN_MESSAGE_MAP(CSkinEdit, CEdit)
	//{{AFX_MSG_MAP(CSkinEdit)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR_REFLECT()
    ON_WM_SHOWWINDOW()
	ON_WM_CONTEXTMENU()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinEdit message handlers

void CSkinEdit::OnPaint() 
{
	
	// TODO: Add your message handler code here
	// Do not call CEdit::OnPaint() for painting messages
	CPaintDC dc(this); // device context for painting
    CRect rect;
    GetWindowRect(rect);
    ScreenToClient(rect);
    dc.FrameRect(rect, &CBrush(m_crFrame));

  //   DefWindowProc(WM_PRINTCLIENT, (WPARAM)dc.m_hDC, PRF_CLIENT);
    DefWindowProc(WM_PRINT, (WPARAM)dc.m_hDC, PRF_CLIENT);
}

HBRUSH CSkinEdit::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a non-NULL brush if the parent's handler should not be called
    if (IsWindowEnabled())
    {
        pDC->SetTextColor(m_crText[0]);
        pDC->SetBkColor(m_crBk[0]);
        return (HBRUSH)m_brushBk[0];
    }
    else
    {
        pDC->SetTextColor(m_crText[1]);
        pDC->SetBkColor(m_crBk[1]);
        return (HBRUSH)m_brushBk[1];
    }
	return NULL;
}


#define SKINEDIT_TRANSLATE(text, langID)            \
            langID == 0x0804 ? text##CHN : text ##ENG

    #define MES_UNDO_CHN            _T("����(&U)")
    #define MES_UNDO_ENG            _T("&Undo")
#define MES_UNDO(langID)        SKINEDIT_TRANSLATE(MES_UNDO_, langID)
    #define MES_COPY_CHN            _T("����(&C)")
    #define MES_COPY_ENG            _T("&Copy")
#define MES_COPY(langID)        SKINEDIT_TRANSLATE(MES_COPY_, langID)
    #define MES_CUT_CHN             _T("����(&T)")
    #define MES_CUT_ENG             _T("Cu&t")
#define MES_CUT(langID)         SKINEDIT_TRANSLATE(MES_CUT_, langID)
    #define MES_PASTE_CHN           _T("ճ��(&P)")
    #define MES_PASTE_ENG           _T("&Paste")
#define MES_PASTE(langID)       SKINEDIT_TRANSLATE(MES_PASTE_, langID)
    #define MES_DELETE_CHN          _T("ɾ��(&D)")
    #define MES_DELETE_ENG          _T("&Del")
#define MES_DELETE(langID)      SKINEDIT_TRANSLATE(MES_DELETE_, langID)
    #define MES_SELECTALL_CHN       _T("ȫѡ(&A)")
    #define MES_SELECTALL_ENG       _T("&All")
#define MES_SELECTALL(langID)   SKINEDIT_TRANSLATE(MES_SELECTALL_, langID)


void CSkinEdit::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
    if (!m_bCustomMenu) 
    {
        CEdit::OnContextMenu(pWnd, point);
        return;
    }

    LANGID langID = GetSystemDefaultLangID();
	SetFocus();
    CSkinMenu menu;
    menu.CreatePopupMenu();
    BOOL bReadOnly = GetStyle() & ES_READONLY;
    DWORD dwFlags = CanUndo() && !bReadOnly ? 0 : MF_GRAYED;
    menu.InsertMenu( 0, MF_BYPOSITION | dwFlags, EM_UNDO,
                     MES_UNDO(langID) );

    menu.InsertMenu( 1, MF_BYPOSITION | MF_SEPARATOR, 0 );

    DWORD dwSel = GetSel();
    dwFlags = (LOWORD(dwSel) == HIWORD(dwSel)) ? MF_GRAYED : 0;
    menu.InsertMenu( 2, MF_BYPOSITION | dwFlags, WM_COPY,
                     MES_COPY(langID) );

    dwFlags = (dwFlags == MF_GRAYED || bReadOnly) ? MF_GRAYED : 0;
    menu.InsertMenu( 2, MF_BYPOSITION | dwFlags, WM_CUT,
                     MES_CUT(langID) );
    menu.InsertMenu( 4, MF_BYPOSITION | dwFlags, WM_CLEAR,
                     MES_DELETE(langID) );

    dwFlags = IsClipboardFormatAvailable(CF_TEXT) &&
        !bReadOnly ? 0 : MF_GRAYED;
    menu.InsertMenu( 4, MF_BYPOSITION | dwFlags, WM_PASTE,
                     MES_PASTE(langID) );

    menu.InsertMenu( 6, MF_BYPOSITION | MF_SEPARATOR, 0 );

    int nLen = GetWindowTextLength();
    dwFlags = (!nLen || (LOWORD(dwSel) == 0 && HIWORD(dwSel) ==
        nLen)) ? MF_GRAYED : 0;
    menu.InsertMenu( 7, MF_BYPOSITION | dwFlags, ME_SELECTALL,
                     MES_SELECTALL(langID) );
    
    menu.InsertSpaces();

    menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON |
        TPM_RIGHTBUTTON, point.x, point.y, this);
}



BOOL CSkinEdit::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (!m_bCustomMenu)
	{
        return CEdit::OnCommand(wParam, lParam);
	}

    switch (LOWORD(wParam))
    {
    case EM_UNDO:
    case WM_CUT:
    case WM_COPY:
    case WM_CLEAR:
    case WM_PASTE:
        return SendMessage( LOWORD(wParam) );
    case ME_SELECTALL:
        return SendMessage( EM_SETSEL, 0, -1 );
    default:
        return CEdit::OnCommand(wParam, lParam);
    }
}

void CSkinEdit::PreSubclassWindow()
{
    CEdit::PreSubclassWindow();

    DWORD dwStyle = GetStyle();
    if (!(dwStyle & ES_MULTILINE)) 
    {
        CRect rect;
        GetWindowRect(rect);
        rect.bottom -= 3;
        GetParent()->ScreenToClient(rect);
        MoveWindow(rect);
    } 

    DWORD dwData = ::GetWindowLong(m_hWnd, GWL_USERDATA);
    ::SetWindowLong(m_hWnd, GWL_USERDATA, dwData | 0x00000001);   
}

void CSkinEdit::OnShowWindow(BOOL bShow, UINT nStatus) 
{
    CEdit::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	// TODO: Add your message handler code here
	if (!bShow) 
	{  
        CRect rect;
        GetClientRect(rect);
        rect.InflateRect(1,1);
        CWnd* pWnd = GetParent();
        if (NULL == pWnd) 
        {
            return;
        }
        MapWindowPoints(pWnd, rect);
        pWnd->InvalidateRect(rect);
	}
}

void CSkinEdit::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
    Invalidate();

	CEdit::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CSkinEdit::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
    Invalidate();

	CEdit::OnHScroll(nSBCode, nPos, pScrollBar);
}

//�ӿ�

/*====================================================================
	������	��    SetFrameColor
	����		�����ñ༭��ı߿���ɫ��
	�㷨ʵ��	������ѡ�
	����ȫ�ֱ�������
    �������˵����crFrame:�߿����ɫ��
                  bRepaint:�Ƿ������ػ���
	����ֵ˵����  ��
====================================================================*/
void CSkinEdit::SetFrameColor(COLORREF crFrame, BOOL bRepaint)
{
    m_crFrame = crFrame;

    if (bRepaint)
    {
        Invalidate();
    }
}

/*====================================================================
	������	��   SetTextColor
	����		�����ñ༭��������ɫ��
	�㷨ʵ��	������ѡ�
	����ȫ�ֱ�������
    �������˵����crText: ���ֵ���ɫ��
                  bRepaint:�Ƿ������ػ���
	����ֵ˵������
====================================================================*/
void CSkinEdit::SetTextColor(COLORREF crText, COLORREF crDisable, BOOL bRepaint)
{
    m_crText[0] = crText;
    if (crDisable == -1) 
    {
        m_crText[1] = crText;
    }
    else
    {
        m_crText[1] = crDisable;
    }

    if (bRepaint)
    {
        Invalidate();
    }
    
}

/*====================================================================
	������	��   SetBkColor
	����		�����ñ༭��ı���ɫ��
	�㷨ʵ��	������ѡ�
	����ȫ�ֱ�����
    �������˵����crBk:��Чʱ�ı���ɫ��
                  crDisable:ʧЧʱ�ı���ɫ��
                  bRepaint:�Ƿ������ػ���
	����ֵ˵����  ��
====================================================================*/
void CSkinEdit::SetBkColor(COLORREF crBk, COLORREF crDisable, BOOL bRepaint)
{
    m_crBk[0]= crBk;

    if (crDisable == DWORD(-1))
    {
        m_crBk[1] = m_crBk[0];
    }
    else
    {
        m_crBk[1] = crDisable;
    }

    if (m_brushBk[0].m_hObject != NULL)
    {
        m_brushBk[0].DeleteObject();
    }
    if (m_brushBk[1].m_hObject != NULL)
    {
        m_brushBk[1].DeleteObject();
    }
    m_brushBk[0].CreateSolidBrush(m_crBk[0]);
    m_brushBk[1].CreateSolidBrush(m_crBk[1]);

    if (bRepaint)
    {
        Invalidate();
    }

}

/*=============================================================================
�� �� ���� UseCustomMenu
��    �ܣ� �Ƿ�ʹ���Զ�����Ҽ��˵�
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� BOOL bUseCustomMenu������TRUE��ʹ�ã�FALSE����ʹ�á�
�� �� ֵ�� void 
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��		�汾		�޸���		�߶���    �޸�����
2004/8/26   1.0			������                  ����
=============================================================================*/
void CSkinEdit::UseCustomMenu(BOOL bUseCustomMenu)
{
    m_bCustomMenu = bUseCustomMenu;
}



/*=============================================================================
�� �� ���� staticSetBkColor
��    �ܣ� 
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� COLORREF crBk
           COLORREF crDisable
�� �� ֵ�� void 
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��		�汾		�޸���		�߶���    �޸�����
2005/03/29  3.6			������                  ����
=============================================================================*/
void CSkinEdit::staticSetBkColor(COLORREF crBk, COLORREF crDisable)
{
    m_s_crBk[0] = crBk;
    m_s_crBk[1] = crDisable;
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
2005/03/29  3.6			������                  ����
=============================================================================*/
void CSkinEdit::staticSetTextColor(COLORREF crText, COLORREF crDisable)
{
    m_s_crText[0] = crText;
    m_s_crText[1] = crDisable;
}


/*=============================================================================
�� �� ���� staticSetFrameColor
��    �ܣ� 
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� COLORREF crFrame
�� �� ֵ�� void 
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��		�汾		�޸���		�߶���    �޸�����
2005/03/29  3.6			������                  ����
=============================================================================*/
void CSkinEdit::staticSetFrameColor(COLORREF crFrame)
{
    m_s_crFrame = crFrame;
}