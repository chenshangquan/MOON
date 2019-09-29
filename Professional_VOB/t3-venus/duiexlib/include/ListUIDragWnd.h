/*****************************************************************************
ģ����      : CListUIDragWnd
�ļ���      : ListUIDragWnd.h
����ļ�    : 
�ļ�ʵ�ֹ���: �б�ؼ���ק����  ��Ӱ����(WS_POPUP)
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/5/16     1.0         ����ӡ      ����
******************************************************************************/
#ifndef LISTUIDRAGWND_H
#define LISTUIDRAGWND_H

class UILIB_API CListUIDragWnd : public CWindowWnd
{
public:
	CListUIDragWnd( HWND wndMain,CPaintManagerUI& cPaintManager );

	~CListUIDragWnd();

	LPCTSTR GetWindowClassName() const;

	 /*****************************************************************************
	* ����:			��ʾdrag����
	* @param		[in]	TRUE����ʾ     FALSE������
	* @return		�� 
	* @remarks		��
	-----------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��         �汾        �޸���      �޸�����
	2013/5/3       1.0         ����ӡ      ����
    ******************************************************************************/
	void ShowWnd(bool bShow = true);	

	 /*****************************************************************************
	* ����:			�ƶ�drag����λ��
	* @param		[in]	Ŀ�괰��λ��POINT
	* @return		�� 
	* @remarks		��
	-----------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��         �汾        �޸���      �޸�����
	2013/5/3       1.0         ����ӡ      ����
    ******************************************************************************/
	void MoveWnd(POINT pt,CListContainerElementUI* pLsElem);

	void SetThisRect(CRect rcThis){m_rcThis = rcThis;};

	CRect GetMainFrameRect();
	void SetListItemHeight( int nListItemHeight );

	void ResetDraw();
	void Draw(CListContainerElementUI* pLsElem);


private:
	RECT m_rcParentRect;
	HWND m_hWndMain;

	int m_nListItemHeight;

	CRect m_rcThis;
	CRect m_rcMainFrame;

	HDC m_hdc;
	HDC m_mdc;
	HBITMAP m_bmpItem;

	CPaintManagerUI m_cPaintManager;
};

#endif // LISTUIDRAGWND_H