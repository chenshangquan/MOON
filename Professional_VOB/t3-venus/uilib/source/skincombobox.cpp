/********************************************************************
	ģ����:      UILib.lib
	�ļ���:      SkinComboBox.cpp
	����ļ�:    UILIbHead.h
	�ļ�ʵ�ֹ��� 
    ���ߣ�       ������
	�汾��       1.0
--------------------------------------------------------------------
	�޸ļ�¼:
	��  ��		�汾		�޸���		�߶���    �޸�����
	2004/4/8	1.0	        ������               ------------

*********************************************************************/

#include "stdafx.h"
#include "UILibHead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkinComboBox
COLORREF CSkinComboBox::m_s_crBk[3] = {RGB(241, 242, 244), GetSysColor(COLOR_HIGHLIGHT),
                                        RGB(233, 233, 233)};
COLORREF CSkinComboBox::m_s_crButton[4] = {RGB(80, 114, 170), RGB(241, 242, 244),
                                        RGB(80, 114, 170), RGB(233, 233, 233)};
COLORREF CSkinComboBox::m_s_crText[2] = {RGB(80, 114, 170), RGB(255,255,255)};
COLORREF CSkinComboBox::m_s_crFrame = RGB(80, 114, 170);

CSkinComboBox::CSkinComboBox()
{
    m_crText[0] = m_s_crText[0];          //normal
    m_crText[1] = m_s_crText[1];           //highlight
    m_crBk[0] = m_s_crBk[0];                //normal
    m_crBk[1] = m_s_crBk[1];      //highlight
    m_crBk[2] = m_s_crBk[2];                //disable
    m_brushBk[0].CreateSolidBrush(m_crBk[0]);
    m_brushBk[1].CreateSolidBrush(m_crBk[2]);

    m_crFrame = m_s_crFrame;

    m_crButton[0] = m_s_crButton[0]; //enable arrow
    m_crButton[1] = m_s_crButton[1]; // enable background
    m_crButton[2] = m_s_crButton[2];  // disable arrow
    m_crButton[3] = m_s_crButton[3]; // disable background
    m_bDrop = FALSE;
    m_bEnable = TRUE;

    m_hBitmap[0] = NULL;
    m_hBitmap[1] = NULL;

    m_bNeedFree = FALSE;
}

CSkinComboBox::~CSkinComboBox()
{
    if (m_bNeedFree) 
    {
        if (m_hBitmap[0] != NULL) 
        {
            ::DeleteObject(m_hBitmap[0]);
            m_hBitmap[0] = NULL;
        }
        if (m_hBitmap[1] != NULL) 
        {
            ::DeleteObject(m_hBitmap[1]);
            m_hBitmap[1] = NULL;
        }
        m_bNeedFree = FALSE;
    }
    m_brushBk[0].DeleteObject();
    m_brushBk[1].DeleteObject();
}


BEGIN_MESSAGE_MAP(CSkinComboBox, CComboBox)
	//{{AFX_MSG_MAP(CSkinComboBox)
	ON_WM_PAINT()
	ON_CONTROL_REFLECT_EX(CBN_DROPDOWN, OnDropdown)
	ON_WM_LBUTTONUP()
 	ON_WM_CTLCOLOR()
    ON_WM_CTLCOLOR_REFLECT()
    ON_WM_ERASEBKGND()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinComboBox message handlers

//��listbox�����
void CSkinComboBox::DrawItem(LPDRAWITEMSTRUCT lpDS) 
{
	// TODO: Add your code to draw the specified item
    CDC* pDC = CDC::FromHandle(lpDS->hDC);
    CRect rect(lpDS->rcItem);

    int nState = lpDS->itemState;

    if (lpDS->itemID == -1)
    {
        return;
    }

    pDC->SetBkMode(TRANSPARENT);

    if ((nState & ODS_COMBOBOXEDIT) != ODS_COMBOBOXEDIT)
    {
//        rect.DeflateRect(0,-1);
    }

    if ((nState & ODS_SELECTED) == ODS_SELECTED)
    {
        pDC->SetTextColor(m_crText[1]);
        pDC->SetBkColor(m_crBk[1]);
        pDC->FillSolidRect(rect, m_crBk[1]);
    }
    else
    {
        CRect rcFull(rect);
  //      rcFull.bottom = rcFull.top + 16;
        pDC->SetTextColor(m_crText[0]);
        pDC->SetBkColor(m_crBk[0]);
        pDC->FillSolidRect(rcFull, m_crBk[0]);
    }

    if ((nState & ODS_FOCUS) == ODS_FOCUS)
    {
        pDC->DrawFocusRect(rect);
    }

    CString str;
    GetLBText(lpDS->itemID, str);
    pDC->DrawText(str, rect, DT_VCENTER|DT_LEFT|DT_SINGLELINE);
}

void CSkinComboBox::DrawImageButton(CDC *pDC, CRect rect)
{
    CDC MemDC;
    MemDC.CreateCompatibleDC(pDC);

    MemDC.SelectObject(m_hBitmap[m_bEnable? 0:1]);
    
    pDC->StretchBlt(rect.left, rect.top, rect.Width(), rect.Height(), &MemDC,
         0, 0, m_sizeButton.cx, m_sizeButton.cy,SRCCOPY);
    MemDC.DeleteDC();
}

//��Combobox�߿�Ͱ�ť
void CSkinComboBox::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	
	// Do not call CComboBox::OnPaint() for painting messages
    m_bEnable = IsWindowEnabled();
    int nIndex = m_bEnable ? 0 : 2;
       
    dc.SetTextColor(m_crText[0]);
    dc.SetBkColor(m_crBk[nIndex]);

    CRect rect;
    GetClientRect(&rect);
    
    dc.FrameRect(rect, &CBrush(m_crFrame));
    rect.DeflateRect(1,1);

    dc.FillRect(rect, &m_brushBk[nIndex/2]);
    if (m_bDrawList)
    {
        int nSel = GetCurSel();
        if (nSel != -1)
        {
            SetCurSel(nSel);
        }
    }
 
    int cxHThumb     = ::GetSystemMetrics(SM_CXHTHUMB);
    int cyHThumb     = ::GetSystemMetrics(SM_CYVTHUMB);
    int nMetric = (rect.Height() - cyHThumb)/2;
    CRect rcButton(rect);
    rcButton.left = rcButton.right - cxHThumb;
    rcButton.bottom--;
    rcButton.top++;

    //����ť 
    if (m_hBitmap[0] != NULL)
    {
        DrawImageButton(&dc, rcButton);
        return;
    }


    CPoint pt[3];
    CRgn rgn;

    pt[0].x = rcButton.left + rcButton.Width()/5;
    pt[0].y = rcButton.top + rcButton.Height()/3;
    pt[1].x = rcButton.right - rcButton.Width()/5;
    pt[1].y = pt[0].y;
    pt[2].x = (rcButton.left + rcButton.right)/2;
    pt[2].y = rcButton.bottom - rcButton.Height()/3;
    rgn.CreatePolygonRgn(pt, 3, WINDING);

    if (m_bEnable)
    {
        dc.FillRect(rcButton, &CBrush(m_crButton[m_bDrop? 0:1]));
        dc.FillRgn(&rgn, &CBrush(m_crButton[m_bDrop? 1:0]));
    }
    else
    {
        dc.FillRect(rcButton, &CBrush(m_crButton[3]));
        dc.FillRgn(&rgn, &CBrush(m_crButton[2]));
    }
    dc.FrameRect(rcButton, &CBrush(m_crButton[m_bDrop? 1:0]));
    rgn.DeleteObject();

    if (m_bDrop)
    {
        m_bDrop = FALSE;
    }
}

BOOL CSkinComboBox::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
//	return CComboBox::OnEraseBkgnd(pDC);
}

HBRUSH CSkinComboBox::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// TODO: Change any attributes of the DC here
    int nIndex = m_bEnable ? 0 : 2;
	pDC->SetBkColor(m_crBk[nIndex]);
    pDC->SetTextColor(m_crText[nIndex]);
	// TODO: Return a non-NULL brush if the parent's handler should not be called
	return m_brushBk[nIndex/2];
}

HBRUSH CSkinComboBox::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{      
    HBRUSH hbr = CComboBox::OnCtlColor(pDC, pWnd, nCtlColor);
    int nIndex = m_bEnable ? 0 : 2;
    pDC->SetTextColor(m_crText[nIndex]);
    pDC->SetBkColor(m_crBk[nIndex]);
    return m_brushBk[nIndex/2];
}

void CSkinComboBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// TODO: Add your code to determine the size of specified item
   if (lpMeasureItemStruct->itemID != (UINT) -1)
   {
      LPCTSTR lpszText = (LPCTSTR) lpMeasureItemStruct->itemData;
      ASSERT(lpszText != NULL);
      CSize   sz;
      CDC*    pDC = GetDC();

      sz = pDC->GetTextExtent(lpszText);

      ReleaseDC(pDC);

      lpMeasureItemStruct->itemHeight = sz.cy;
   }
}

//����ʱ����ť����ѹ״̬
BOOL CSkinComboBox::OnDropdown() 
{
	// TODO: Add your control notification handler code here
    m_bDrop = TRUE;
    return FALSE;
}

//��ť������ѹ
void CSkinComboBox::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_bDrop = FALSE;
    Invalidate();
	CComboBox::OnLButtonUp(nFlags, point);
}

void CSkinComboBox::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
//	ModifyStyleEx(0, CBS_HASSTRINGS |CBS_OWNERDRAWVARIABLE);
	CComboBox::PreSubclassWindow();
    m_bDrawList = (BOOL)((GetStyle() & CBS_DROPDOWNLIST) == CBS_DROPDOWNLIST);
}

//�ӿں���

/*====================================================================
������  ��SetTextColor
��  ��  �������ı���ɫ��
ȫ�ֱ�������
���������crText: ����ʱ���ı�ɫ��
          crHighlight:������ʾʱ�ı���ɫ��
          bRepaint: �Ƿ������ػ���
����ֵ  ����
====================================================================*/
void CSkinComboBox::SetTextColor(COLORREF crText, COLORREF crHighlight, BOOL bRepaint)
{
    m_crText[0] = crText;
    m_crText[1] = crHighlight;

    if (bRepaint)
    {
        Invalidate();
    }
}

/*====================================================================
������  ��SetBkColor
��  ��  �������ı�������ɫ��
ȫ�ֱ�������
���������crBk: ����ʱ���ı�����ɫ��
          crHighlight:������ʾʱ���ı�����ɫ��
          bRepaint: �Ƿ������ػ���
����ֵ  ����
====================================================================*/
void CSkinComboBox::SetBkColor(COLORREF crBk, COLORREF crHighlight, BOOL bRepaint)
{
    m_crBk[0] = crBk;
    m_crBk[1] = crHighlight;

    if (m_brushBk[0].GetSafeHandle() != NULL)
    {
        m_brushBk[0].DeleteObject();
        m_brushBk[0].CreateSolidBrush(m_crBk[0]);
    }
    if (bRepaint)
    {
        Invalidate();
    }
}

/*====================================================================
������  ��SetFrameColor
��  ��  �����ÿؼ��߿���ɫ��
ȫ�ֱ�������
���������crFrame: �߿���ɫ��
          bRepaint: �Ƿ������ػ���
����ֵ  ����
====================================================================*/
void CSkinComboBox::SetFrameColor(COLORREF crFrame, BOOL bRepaint)
{
    m_crFrame = crFrame;

    if (bRepaint)
    {
        Invalidate();
    }
}

/*====================================================================
������  ��SetButtonColor
��  ��  �����ÿؼ�������ť����ɫ�������˰�ťͼƬʱ���ú�����Ч��
ȫ�ֱ�������
���������crFront: ��ťǰ�������ε���ɫ��
          crBk: ��ť�ı���ɫ��
          crDisableFt: ʧЧʱ�İ�ťǰ��ɫ��
          crDisableBk: ʧЧʱ�İ�ť����ɫ��
����ֵ  ����
====================================================================*/
void CSkinComboBox::SetButtonColor(COLORREF crFront, COLORREF crBk, COLORREF crDisableFt, COLORREF crDisableBk)
{
    m_crButton[0] = crFront;
    m_crButton[1] = crBk;
    m_crButton[2] = crDisableFt;
    m_crButton[3] = crDisableBk;
}

/*====================================================================
������  ��SetButtonImage
��  ��  �����ÿؼ�������ťͼƬ��
ȫ�ֱ�������
���������hBitmap: ����ʱ��ťͼƬ�����
          hDisableBitmap: ʧЧʱ�İ�ťͼƬ�����
����ֵ  ����
====================================================================*/
void CSkinComboBox::SetButtonImage(HBITMAP hBitmap, HBITMAP hDisableBitmap)
{
    if (m_bNeedFree) 
    {
        if (m_hBitmap[0] != NULL) 
        {
            ::DeleteObject(m_hBitmap[0]);
            m_hBitmap[0] = NULL;
        }
        if (m_hBitmap[1] != NULL) 
        {
            ::DeleteObject(m_hBitmap[1]);
            m_hBitmap[1] = NULL;
        }
        m_bNeedFree = FALSE;
    }

    m_hBitmap[0] = hBitmap;
    m_hBitmap[1] = hDisableBitmap;

    if (m_hBitmap == NULL)
    {
        m_sizeButton.cx = 0;
        m_sizeButton.cy = 0;
        return;
    }

    BITMAP bmp;
    GetObject(m_hBitmap[0], sizeof(bmp), &bmp);
    m_sizeButton.cx = bmp.bmWidth;
    m_sizeButton.cy = bmp.bmHeight;
}

/*====================================================================
������  ��SetButtonImage
��  ��  �����ÿؼ�������ťͼƬ��
ȫ�ֱ�������
���������nBitmap: ����ʱ��ťͼƬ��ԴID�ţ�
          nDisableBitmap: ʧЧʱ�İ�ťͼƬ��ԴID�š�
����ֵ  ����
====================================================================*/
void CSkinComboBox::SetButtonImage(UINT nBitmap, UINT nDisableBitmap)
{
    if (nBitmap == 0)
    {
        m_hBitmap[0] = NULL;
        return;
    }

    HBITMAP hBitmap = NULL;
    HBITMAP hDisable = NULL;
    HINSTANCE hInstance = NULL;

    hInstance = AfxFindResourceHandle(MAKEINTRESOURCE(nBitmap), RT_BITMAP);
    hBitmap = (HBITMAP)::LoadImage(hInstance, MAKEINTRESOURCE(nBitmap), 
        IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADMAP3DCOLORS);

    if (nDisableBitmap != 0)
    {
        hInstance = AfxFindResourceHandle(MAKEINTRESOURCE(nDisableBitmap), RT_BITMAP);
        hDisable = (HBITMAP)::LoadImage(hInstance, MAKEINTRESOURCE(nDisableBitmap), 
        IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADMAP3DCOLORS);
    }
    else
    {
        hDisable = hBitmap;
    }
    SetButtonImage(hBitmap, hDisable);

    m_bNeedFree = TRUE;
}

#define MES_UNDO        _T("����(&U)")
#define MES_CUT         _T("����(&T)")
#define MES_COPY        _T("����(&C)")
#define MES_PASTE       _T("ճ��(&P)")
#define MES_DELETE      _T("ɾ��(&D)")
#define MES_SELECTALL   _T("ȫѡ(&A)")

void CSkinComboBox::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
//	SetFocus();
//    CSkinMenu menu;
//    menu.CreatePopupMenu();
//
//    CWnd* pChild = GetWindow(GW_CHILD);
//    if (pChild == NULL) 
//    {
//        return;
//    }
//
//    CEdit* pEdit = NULL;
//    if (pChild->IsKindOf(RUNTIME_CLASS(CEdit))) 
//    {
//        pEdit = (CEdit*)pChild;
//    }
//    else
//    {
//        return;
//    }
//    BOOL bReadOnly = pEdit->GetStyle() & ES_READONLY;
//    DWORD dwFlags = pEdit->CanUndo() && !bReadOnly ? 0 : MF_GRAYED;
//    menu.InsertMenu(0, MF_BYPOSITION | dwFlags, EM_UNDO,
//        MES_UNDO);
//
//    menu.InsertMenu(1, MF_BYPOSITION | MF_SEPARATOR, 0);
//
//    DWORD dwSel = pEdit->GetSel();
//    dwFlags = (LOWORD(dwSel) == HIWORD(dwSel)) ? MF_GRAYED : 0;
//    menu.InsertMenu(2, MF_BYPOSITION | dwFlags, WM_COPY,
//        MES_COPY);
//
//    dwFlags = (dwFlags == MF_GRAYED || bReadOnly) ? MF_GRAYED : 0;
//    menu.InsertMenu(2, MF_BYPOSITION | dwFlags, WM_CUT,
//        MES_CUT);
//    menu.InsertMenu(4, MF_BYPOSITION | dwFlags, WM_CLEAR,
//        MES_DELETE);
//
//    dwFlags = IsClipboardFormatAvailable(CF_TEXT) &&
//        !bReadOnly ? 0 : MF_GRAYED;
//    menu.InsertMenu(4, MF_BYPOSITION | dwFlags, WM_PASTE,
//        MES_PASTE);
//
//    menu.InsertMenu(6, MF_BYPOSITION | MF_SEPARATOR, 0);
//
//    int nLen = GetWindowTextLength();
//    dwFlags = (!nLen || (LOWORD(dwSel) == 0 && HIWORD(dwSel) ==
//        nLen)) ? MF_GRAYED : 0;
//    menu.InsertMenu(7, MF_BYPOSITION | dwFlags, ME_SELECTALL,
//        MES_SELECTALL);
//    
//    menu.InsertSpaces();
//
//    menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON |
//        TPM_RIGHTBUTTON, point.x, point.y, this);
	
}


/*=============================================================================
�� �� ���� staticSetBkColor
��    �ܣ� 
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� COLORREF crBk
           COLORREF crHighlight
           COLORREF crDisable
�� �� ֵ�� void 
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��		�汾		�޸���		�߶���    �޸�����
2005/03/29  1.0			������                  ����
=============================================================================*/
void CSkinComboBox::staticSetBkColor(COLORREF crBk, COLORREF crHighlight, COLORREF crDisable)
{
    m_s_crBk[0] = crBk;
    m_s_crBk[1] = crHighlight;
    m_s_crBk[2] = crDisable;
}


/*=============================================================================
�� �� ���� staticSetButtonColor
��    �ܣ� 
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� COLORREF crFront
           COLORREF crBk
           COLORREF crDisableFt
           COLORREF crDisableBk
�� �� ֵ�� void 
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��		�汾		�޸���		�߶���    �޸�����
2005/03/29  1.0			������                  ����
=============================================================================*/
void CSkinComboBox::staticSetButtonColor(COLORREF crFront, COLORREF crBk,
                                         COLORREF crDisableFt, COLORREF crDisableBk)
{
    m_s_crButton[0] = crFront;
    m_s_crButton[1] = crBk;
    m_s_crButton[2] = crDisableFt;
    m_s_crButton[3] = crDisableBk;
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
2005/03/29  1.0			������                  ����
=============================================================================*/
void CSkinComboBox::staticSetFrameColor(COLORREF crFrame)
{
    m_s_crFrame = crFrame;
}


/*=============================================================================
�� �� ���� staticSetTextColor
��    �ܣ� 
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� COLORREF crText
           COLORREF crHighlight
�� �� ֵ�� void 
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��		�汾		�޸���		�߶���    �޸�����
2005/03/29  1.0			������                  ����
=============================================================================*/
void CSkinComboBox::staticSetTextColor(COLORREF crText, COLORREF crHighlight)
{
    m_s_crText[0] = crText;
    m_s_crText[1] = crHighlight;
}