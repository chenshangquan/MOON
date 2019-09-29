/******************************************************************************
ģ����      ��CBMPDlg                        
�ļ���      ��BMPDlg.cpp
����ļ�	��UILibHead.h
�ļ�ʵ�ֹ��ܣ�ʵ��CBMPDlg��
����		��������
�汾		��1.0
---------------------------------------------------------------------------------------------------------------------
�޸ļ�¼:
��  ��		�汾		�޸���		�߶���    �޸�����
03/24/04    1.0         ������                  ����      
******************************************************************************/

#include "stdafx.h"
#include "UILibHead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBMPDlg dialog

CBMPDlg::CBMPDlg(UINT uResourceID, CWnd* pParent)
	: CDialog(uResourceID, pParent)
{
	//{{AFX_DATA_INIT(CBkDialogST)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	Init();
}

CBMPDlg::CBMPDlg(CWnd* pParent /*=NULL*/)
{
	//{{AFX_DATA_INIT(CBMPDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CBMPDlg::CBMPDlg(LPCTSTR pszResourceID, CWnd* pParent)
	: CDialog(pszResourceID, pParent)
{
	Init();
}

CBMPDlg::~CBMPDlg()
{
    FreeResources();
}

void CBMPDlg::FreeResources()
{
    if (m_hBitmap != NULL)
    {
        ::DeleteObject(m_hBitmap);
        m_hBitmap = NULL;
    }
    
    if (m_BkDC.m_hDC != NULL) 
    {
        if (m_OldBitmap != NULL)
        {
            ::SelectObject(m_BkDC.m_hDC,m_OldBitmap);
        }
        ::DeleteObject(m_BkDC.m_hDC);
    }
}

void CBMPDlg::Init()
{
    m_hBitmap = NULL;
    m_dwHeight = 0;
    m_dwWidth = 0;
    m_bSizeToContent = FALSE;

    m_crTop =RGB(105,146,214);
    m_crBottom = RGB(34,52,88);
    m_OldBitmap = NULL;
    if (m_BkDC.GetSafeHdc() != NULL)
    {
        m_BkDC.DeleteDC();
    }
}


void CBMPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBMPDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBMPDlg, CDialog)
	//{{AFX_MSG_MAP(CBMPDlg)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBMPDlg message handlers

BOOL CBMPDlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	BOOL	bRetValue = CDialog::OnEraseBkgnd(pDC);

    CRect rcDlg;
    GetClientRect(&rcDlg);
    if (m_hBitmap == NULL)
    {
        DrawBk(pDC);
        return bRetValue;
    }


    CDC			dcMemoryDC;
	CBitmap		bmpMemoryBitmap;
	CBitmap*	pbmpOldMemoryBitmap = NULL;

    dcMemoryDC.CreateCompatibleDC(pDC);
	bmpMemoryBitmap.CreateCompatibleBitmap(pDC, rcDlg.Width(), rcDlg.Height());
	pbmpOldMemoryBitmap = (CBitmap*)dcMemoryDC.SelectObject(&bmpMemoryBitmap);

	// Fill background 
	dcMemoryDC.FillSolidRect(rcDlg, pDC->GetBkColor());

	CDC			dcTempDC;
	HBITMAP		hbmpOldTempBitmap = NULL;

	dcTempDC.CreateCompatibleDC(pDC);
	hbmpOldTempBitmap = (HBITMAP)::SelectObject(dcTempDC.m_hDC, m_hBitmap);

    if (m_bSizeToContent)
    {
        dcMemoryDC.BitBlt(0, 0, m_dwWidth, m_dwHeight, &dcTempDC, 0, 0, SRCCOPY);
    }
    else
    {
        dcMemoryDC.StretchBlt(0, 0, rcDlg.Width(), rcDlg.Height(), &dcTempDC, 0, 0, m_dwWidth, m_dwHeight, SRCCOPY);
    }

    pDC->BitBlt(0, 0, rcDlg.Width(), rcDlg.Height(), &dcMemoryDC, 0, 0, SRCCOPY);

	::SelectObject(dcTempDC.m_hDC, hbmpOldTempBitmap);
	dcMemoryDC.SelectObject(pbmpOldMemoryBitmap);
    dcTempDC.DeleteDC();
    dcMemoryDC.DeleteDC();
	return bRetValue;
}

//�ӿ�

/*====================================================================
������  ��SetBkImage
��  ��  �����öԻ��򱳾�ͼ��
ȫ�ֱ�������
���������nBitmap: ����ͼ����ԴID�š�
����ֵ  ����
====================================================================*/
void CBMPDlg::SetBkImage(UINT nBitmap)
{
    HBITMAP		hBitmap			= NULL;
	HINSTANCE	hInstResource	= NULL;
    
    if (nBitmap == 0)
    {
        SetBkImage(hBitmap);
        return;
    }
	// Find correct resource handle
	hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(nBitmap), RT_BITMAP);

	// Load bitmap In
	hBitmap = (HBITMAP)::LoadImage(hInstResource, MAKEINTRESOURCE(nBitmap), IMAGE_BITMAP, 0, 0, 0);

	SetBkImage(hBitmap);
}

/*====================================================================
������  ��SetBkImage
��  ��  �����öԻ��򱳾�ͼ��
ȫ�ֱ�������
���������hBitmap: ����ͼ�ľ����
����ֵ  ����
====================================================================*/
void CBMPDlg::SetBkImage(HBITMAP hBitmap)
{
    int		nRetValue;
	BITMAP	csBitmapSize;

	// Free any loaded resource
	FreeResources();

	if (hBitmap)
	{
		m_hBitmap = hBitmap;

		// Get bitmap size
		nRetValue = ::GetObject(hBitmap, sizeof(csBitmapSize), &csBitmapSize);
		if (nRetValue == 0)
		{
			FreeResources();
			return;
		} // if
		m_dwWidth = (DWORD)csBitmapSize.bmWidth;
		m_dwHeight = (DWORD)csBitmapSize.bmHeight;
        if (m_bSizeToContent)
        {
            SizeToContent();
        }
    }
}

/*====================================================================
������  ��SizeToContent
��  ��  ���ı�Ի����С����ӦͼƬ��
ȫ�ֱ�������
�����������
����ֵ  ����
====================================================================*/
void CBMPDlg::SizeToContent()
{
    if (m_hBitmap != NULL)
    {
        SetWindowPos(NULL, -1, -1, m_dwWidth, m_dwHeight, 
            SWP_NOMOVE | SWP_NOZORDER | SWP_NOREDRAW | SWP_NOACTIVATE);
    }
    m_bSizeToContent = TRUE;
}

/*====================================================================
������  ��SetBkColor
��  ��  �����öԻ���ı���ɫ��������Ϊ����ɫ��
ȫ�ֱ�������
���������crTop:�Ի������϶˵���ɫ��
          crBottom:�Ի������¶˵���ɫ��
����ֵ  ����
====================================================================*/
void CBMPDlg::SetBkColor(COLORREF crTop, COLORREF crBottom, BOOL bRepaint)
{
    m_crTop = crTop;
    m_crBottom = crBottom;

    if (bRepaint)
    {
        Invalidate();
    }
}

void CBMPDlg::DrawBk(CDC *pDC)
{
    CRect rect;
    GetClientRect(rect);

    if (rect.Height() == 0)
    {
        return;
    }
    
    if (m_crBottom == -1 || m_crTop == m_crBottom)
    {
        pDC->FillSolidRect(rect, m_crTop);
        return;
    }

    CUITools::DrawStepBk(pDC, m_crTop, m_crBottom, rect, rect);   
}

