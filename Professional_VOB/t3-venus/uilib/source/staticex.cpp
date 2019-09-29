/********************************************************************
	ģ����:      UILib
	�ļ���:      staticex.cpp
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
// CStaticEx
COLORREF CStaticEx::m_s_crBk[2] = {RGB(100,0,0), RGB(0,0,0)};
COLORREF CStaticEx::m_s_crText[2] = {RGB(80, 114, 170), RGB(128,128,128)};

CStaticEx::CStaticEx()
{
    m_bTrans = TRUE;
    m_crBk[0] = m_s_crBk[0];
    m_crBk[1] = m_s_crBk[0];
    m_crText[0] = m_s_crText[0];
    m_crText[1] = m_s_crText[1];

    m_bSingleLine = TRUE;

	m_pFont = NULL;
}

CStaticEx::~CStaticEx()
{
	if ( NULL !=  m_pFont )
	{
		m_pFont->DeleteObject();
		m_pFont = NULL;
	}
}


BEGIN_MESSAGE_MAP(CStaticEx, CStatic)
	//{{AFX_MSG_MAP(CStaticEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStaticEx message handlers

//�ػ��ؼ�
void CStaticEx::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	// TODO: Add your message handler code here
	// Do not call CStatic::OnPaint() for painting messages
    dc.SetBkMode(TRANSPARENT);
    dc.SelectObject(GetFont());

    CRect rect;
    GetClientRect(rect);

    if (!m_bTrans)
    {
        dc.FillRect(rect, &CBrush(m_crBk[IsWindowEnabled()? 0:1]));
    }

    CString str;
    GetWindowText(str);

    CFont* pFont = m_pFont;
	if ( pFont == NULL)
	{
		 pFont = GetFont();
	}
    CFont* pOld = dc.SelectObject(pFont);
    dc.SetTextColor(m_crText[IsWindowEnabled()? 0:1]);

    int nLine = str.Find('\n', 0);
    if (nLine >= 0 || !m_bSingleLine) 
    {
        dc.DrawText(str, rect, DT_LEFT);
        EnableTooltip(FALSE);
        return;
    }

    CSize size = dc.GetTextExtent(str);
    if (size.cx < rect.Width())
    {
       // dc.DrawText(str, rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
        DWORD dwStyle = GetStyle();
        if (dwStyle & SS_RIGHT)
        {
            dc.DrawText(str, rect, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
        }
        else if (dwStyle & SS_CENTER)
        {
            dc.DrawText(str, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        }
        else
        {
            dc.TextOut(rect.left, rect.top, str);
        }
        EnableTooltip(FALSE);
    }
    else
    {
        int xPoints = dc.GetTextExtent("...").cx;
        rect.right -= xPoints;

        dc.ExtTextOut(0, 0, ETO_CLIPPED, rect, str, NULL);
        rect.left = rect.right;
        rect.right += xPoints;
        dc.DrawText("...", rect, DT_LEFT|DT_VCENTER|DT_SINGLELINE);
        EnableTooltip(TRUE);
        if (m_toolTip.GetToolCount() != 0)
        {
            m_toolTip.UpdateTipText(str, this, 1);
        }
    }
    dc.SelectObject(pOld);
}

/*
    �ڿؼ�ʧЧʱ���ؼ������Զ�����OnPaint�������ػ��������Լ��û�ɫ�ı����ػ�
����������Ϊ���ڿؼ�ʧЧʱ���Ե���OnPaint���ػ������޲�͸��Ч������ֻ�ǲ��ȴ�ʩ��
ϣ���ҵ����õķ�����
*/
HBRUSH CStaticEx::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a non-NULL brush if the parent's handler should not be called
	// TODO: Return a different brush if the default is not desired
    CWnd* pParent = GetParent();
    if (pParent != NULL)
    {
        CRect rect;
        GetClientRect(rect);

        MapWindowPoints(pParent, rect);
        pParent->InvalidateRect(rect);
    }

    return NULL;
}

void CStaticEx::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	ModifyStyle(0, SS_NOTIFY);
	CStatic::PreSubclassWindow();
}

BOOL CStaticEx::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
    if (m_toolTip.m_hWnd != NULL)
    {
	    m_toolTip.RelayEvent( pMsg );
    }
	
	return CStatic::PreTranslateMessage(pMsg);
}

//��ʼ��ToolTip
void CStaticEx::InitToolTip()
{
    if (m_toolTip.m_hWnd != NULL)
    {
        return;
    }

    m_toolTip.Create(this);
    CString str;
    GetWindowText(str);
    CRect rcBtn;
    GetClientRect(&rcBtn);
    m_toolTip.AddTool( this,  str, rcBtn, 1);
    m_toolTip.SetDelayTime( 0 );
    m_toolTip.SendMessage(TTM_SETMAXTIPWIDTH, 0, 400);
    m_toolTip.SetDelayTime( TTDT_AUTOPOP, TOOLTIP_SHOWTIME );
}


//�趨Tooltip�����Ƿ�ʼ��
void CStaticEx::EnableTooltip(BOOL bActive)
{
    InitToolTip();
    m_toolTip.Activate(bActive);
}

//�ӿں���

/*====================================================================
������  ��SetBkColor
��  ��  �����ñ�����ɫ������������Ϊ͸��ʱ���ú�����Ч��
ȫ�ֱ�������
���������crBk: ����ʱ�ı���ɫ��
          crDisable:ʧЧʱ�ı���ɫ��
          bRepaint: �Ƿ������ػ���
����ֵ  ����
====================================================================*/
void CStaticEx::SetBkColor(COLORREF crBk, COLORREF crDisable, BOOL bRepaint)
{
    m_crBk[0] = crBk;

    if (crDisable == -1)
    {
        m_crBk[1] = crBk;
    }
    else
    {
        m_crBk[1] = crDisable;
    }

    if (bRepaint)
    {
        Invalidate();
    }
}

/*====================================================================
������  ��SetBkTransparent
��  ��  �����ñ��������Ƿ�͸����
ȫ�ֱ�������
���������bTrans: �Ƿ�͸����
����ֵ  ����
====================================================================*/
void CStaticEx::SetBkTransparent(BOOL bTrans)
{
    m_bTrans = bTrans;
}

/*====================================================================
������  ��SetTextColor
��  ��  ������������ɫ��
ȫ�ֱ�������
���������crText: ����ʱ������ɫ��
          crDisable:ʧЧʱ������ɫ��
          bRepaint: �Ƿ������ػ���
����ֵ  ����
====================================================================*/
void CStaticEx::SetTextColor(COLORREF crText, COLORREF crDisable, BOOL bRepaint)
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

void CStaticEx::SetSingleLine(BOOL bSingleLine)
{
    m_bSingleLine = bSingleLine;
}

void CStaticEx::staticSetBkColor(COLORREF crBk, COLORREF crDisable)
{
    m_s_crBk[0] = crBk;
    m_s_crBk[1] = crDisable;
}

void CStaticEx::staticSetTextColor(COLORREF crText, COLORREF crDisable)
{
    m_s_crText[0] = crText;
    m_s_crText[1] = crDisable;
}


void CStaticEx::SetFontSize( int nFontSize )
{ 
   if ( NULL != m_pFont )
   {
	   m_pFont->DeleteObject();
	   m_pFont = NULL;
   }

   m_pFont = new CFont();
   m_pFont->CreatePointFont( nFontSize, _T("΢���ź�"));
  
   UpdateWindow();
 
}