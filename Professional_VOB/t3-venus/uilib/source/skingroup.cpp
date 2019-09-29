/********************************************************************
	ģ����:      UILib
	�ļ���:      skingroup.cpp
	����ļ�:    UILibHead.h
	�ļ�ʵ�ֹ��� 
    ���ߣ�       ������
	�汾��       1.0
------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��		�汾		�޸���		�߶���    �޸�����
	2004/07/30	1.0			������                  ����

*********************************************************************/

#include "stdafx.h"
#include "UILibHead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkinGroup
COLORREF CSkinGroup::m_s_crText[2] = { RGB(80, 114, 170), RGB(172, 172, 172)};
COLORREF CSkinGroup::m_s_crLine[2] = { RGB(80, 114, 170), RGB(172, 172, 172)};
CSkinGroup::CSkinGroup()
{
    m_crText[0] = m_s_crText[0];
    m_crText[1] = m_s_crText[1];
    m_crLine[0] = m_s_crLine[0];
    m_crLine[1] = m_s_crLine[1];

    m_penLine[0].CreatePen(PS_SOLID , 1, m_crLine[0]);
    m_penLine[1].CreatePen(PS_SOLID , 1, m_crLine[1]);

    m_nLMetric = 7;
}
CSkinGroup::~CSkinGroup()
{
    m_penLine[0].DeleteObject();
    m_penLine[1].DeleteObject();
}


BEGIN_MESSAGE_MAP(CSkinGroup, CButton)
	//{{AFX_MSG_MAP(CSkinGroup)
	ON_WM_PAINT()
	ON_WM_ENABLE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinGroup message handlers

void CSkinGroup::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	dc.SelectObject(GetFont());
	// Do not call CButton::OnPaint() for painting messages
    CString strText;
    CRect rect;
    
    GetClientRect(rect);
    GetWindowText(strText);
    if (m_strTitle != strText)
    {
        m_strTitle = strText;
        CWnd* pParent = GetParent();
        if (pParent != NULL)
        {
            CRect rect;
            GetClientRect(rect);

            MapWindowPoints(pParent, rect);
            pParent->InvalidateRect(rect);
        }
        return;
    }

    int nIndex = IsWindowEnabled()? 0:1;

    //û�б��⣬ֱ�ӻ������򣬽�����   [zhuyr][7/30/2004]
    if (strText.IsEmpty()) 
    {
        dc.FrameRect(rect, &CBrush(m_crLine[nIndex]));
        return;
    }

    CSize size = dc.GetTextExtent(strText);
    rect.left += m_nLMetric;
    
    dc.SetBkMode(TRANSPARENT);

    CPen* pOld;
    dc.SetTextColor(m_crText[nIndex]);

    dc.DrawText(strText, rect, DT_LEFT|DT_SINGLELINE|DT_TOP);

    pOld = dc.SelectObject(&m_penLine[nIndex]);

    rect.top += size.cy / 2;
    dc.MoveTo(rect.left - 2, rect.top);
    dc.LineTo(rect.left - m_nLMetric, rect.top);
    //  wanghao 2006/12/26 HIDE֮�󣬱߿����
//    dc.LineTo(rect.left - m_nLMetric, rect.bottom);
//    dc.LineTo(rect.right, rect.bottom);
//    dc.LineTo(rect.right, rect.top);
    dc.LineTo( rect.left - m_nLMetric, rect.bottom - 1 );
    dc.LineTo( rect.right - 1, rect.bottom - 1 );
    dc.LineTo( rect.right - 1, rect.top );
    dc.LineTo(rect.left + size.cx + 2, rect.top);

    dc.SelectObject(pOld);    
}

void CSkinGroup::OnEnable(BOOL bEnable) 
{
	CButton::OnEnable(bEnable);
	
	// TODO: Add your message handler code here
	CWnd* pParent = GetParent();
    if (pParent != NULL)
    {
        CRect rect;
        GetClientRect(rect);

        MapWindowPoints(pParent, rect);
        pParent->InvalidateRect(rect);
    }
}

/*====================================================================
������	��    SetGroupColor
����		�����ÿؼ���ɫ
�㷨ʵ��	������ѡ�
����ȫ�ֱ�������
�������˵����crNormal: ����ʱ��ʾ����ɫ, -1ʱ����ԭ������ɫ��
              crDisable:ʧЧʱ��ʾ����ɫ, -1ʱ����ԭ������ɫ��
              bRepaint:�Ƿ������ػ��ؼ���
����ֵ˵����  ��
----------------------------------------------------------------------
�޸ļ�¼:
��  ��		�汾		�޸���		�߶���    �޸�����
2004/07/30	1.0			������                  ����
====================================================================*/
void CSkinGroup::SetGroupColor(COLORREF crNormal, COLORREF crDisable,
                               BOOL bRepaint, int nType)
{
    if (-1 != crNormal)
    {
         if (nType & COLTYPE_TEXT)
         {
            m_crText[0] = crNormal;
         }

         if (nType & COLTYPE_LINE)
         {
            m_crLine[0] = crNormal;
            m_penLine[0].DeleteObject();
            m_penLine[0].CreatePen(PS_SOLID , 1, m_crLine[0]);
         }
    }
    
    if (-1 != crDisable)
    {
         if (nType & COLTYPE_TEXT)
         {
            m_crText[1] = crNormal;
         }

         if (nType & COLTYPE_LINE)
         {
            m_crLine[1] = crNormal;
            m_penLine[1].DeleteObject();
            m_penLine[1].CreatePen(PS_SOLID , 1, m_crLine[1]);
         }
    }

    if (bRepaint) 
    {
        Invalidate();
    }
}

/*====================================================================
������	��    SetLMetric
����		���������ֵ���߿�ľ���
�㷨ʵ��	������ѡ�
����ȫ�ֱ�������
�������˵����nMetric������
����ֵ˵����  ��
----------------------------------------------------------------------
�޸ļ�¼:
��  ��		�汾		�޸���		�߶���    �޸�����
2004/07/30	1.0			������                  ����
====================================================================*/
void CSkinGroup::SetLMetric(UINT nMetric)
{
    m_nLMetric = nMetric;
}

void CSkinGroup::staticSetGroupColor(COLORREF crNormal, COLORREF crDisable, int nType)
{
    if (nType & COLTYPE_TEXT)
    {
        m_s_crText[0] = crNormal;
        m_s_crText[1] = crDisable;
    }

    if (nType & COLTYPE_LINE)
    {
        m_s_crLine[0] = crNormal;
        m_s_crLine[1] = crDisable;
    }
}

/*=============================================================================
�� �� ��:SetWindowText
��    ��:���ñ�������
��    ��:LPCTSTR lpszString         [in]    ��������
ע    ��:ר�����ڴ�����Ӱ����
�� �� ֵ:��
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2006/12/26  4.0     ���    ����
=============================================================================*/
void CSkinGroup::SetWindowText(LPCTSTR lpszString)
{
    CWnd::SetWindowText( lpszString );
    if ( IsWindowVisible() )
    {
        ShowWindow( SW_HIDE );
        ShowWindow( SW_SHOW );
    }
    return;
}

/*=============================================================================
�� �� ��:DefWindowProc
��    ��:���˰�tab����vista��xp_sp3ϵͳ�ϵ���Ӱ����Ϣ��WM_UPDATEUISTATE 0x0128
��    ��:
ע    ��:
�� �� ֵ:��
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2009/03/26  4.0     �½���    ����
=============================================================================*/
LRESULT CSkinGroup::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    switch( message )
    {
    case 0x0128:
    	return S_OK;
    default:
        break;
    }
    return CWnd::DefWindowProc( message, wParam, lParam );
}
