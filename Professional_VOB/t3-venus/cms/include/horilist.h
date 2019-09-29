// transparenthorilist.h: interface for the CTransparentHoriList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSPARENTHORILIST_H__0F6A8CB5_DF2A_4759_8ADA_EA9E0BD8C519__INCLUDED_)
#define AFX_TRANSPARENTHORILIST_H__0F6A8CB5_DF2A_4759_8ADA_EA9E0BD8C519__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TransparentHoriList.h"
/*
class CTransparentHoriList : public CDlgChild, public IList  
{
public:
	const static CString strTopLeft;
	const static CString strTopCenter;
	const static CString strTopRight;
	const static CString strCenterLeft;
	const static CString strCenterRight;
	const static CString strBottomLeft;
	const static CString strBottomCenter;
	const static CString strBottomRight;
	
	CTransparentHoriList( CString strName = "", CRect rcWnd = CRect(0,0,0,0), CWnd* pWnd = 0 );
	
	virtual ~CTransparentHoriList();
	void Draw( IArgs* pArgs );
	void DrawUI( Graphics* pGraphics, CWnd* pParent );
	virtual void Clicked( UINT nFlags, CPoint point );
	void SetDragEnable( BOOL bDrag );
	BOOL GetDragEnable() { return m_bDragEnable; }
	
	int  GetItemCount();
	void SetOffsetIndex( int nIndex );
	int  GetOffsetIndex();
	void SetTotalOffset( int nOffset ); 
	
	void SetClickNoSel( BOOL bSel );
	BOOL IsClickNoSel() { return m_bClickNoSel; }
	
	void SetSelItem( unsigned long dwDataKey );
	void ResetSelItem( BOOL bResetOffset = FALSE );
	IBaseItem* GetSelItem();
	
	void SetImage( CString strImageFolder, BOOL bInvalidate = FALSE );
	Image* MosaicListImage();
	
    void Clear();

protected:
	CRect GetFrameInScreen( IItemList* pList );
	void  UpdateTotalHeight();
	CRect GetListRect();
	BOOL IsReadyForDrag();
	void SetSelItemStatus( EmItemStatus emStatus );
	int  GetOffSetWidth( int nIndex );

	int  GetNextPageOffset( BOOL bNext ); //自动翻页
	int  GetBackPageOffset();             //自动退回    
	void CheckTotalOffset();
	
	void ListMove();
	void ListAutoMove();
protected:
	CRect   m_rctDlg;                      //列表框Rect
	CRect   m_rctList;	                   //整个列表数据Rect
	int     m_nTotalXOffset;               //当前总的X轴偏移量
	int     m_nNextXOffset;                //要移动到的偏移量
	CPoint  m_ptMouseLast;
	CPoint  m_ptMouseNow;
	CPoint  m_ptMouseDown;
	int     m_nMoveSpeed;
	BOOL    m_bLBtnDown;
	IItemList*   m_pSelItem;               //当前选中
	IItemList*   m_pLastItem;
	unsigned long m_dwSelDataKey;          //选中Item的数据索引
	
	BOOL    m_bDragEnable;
	BOOL    m_bClickNoSel;
	
	//背景图片
	Image   *m_pImgTopLeft;
    Image   *m_pImgTopCenter;
    Image   *m_pImgTopRight;	
    Image   *m_pImgCenterLeft;
	Image   *m_pImgCenterRight;
    Image   *m_pImgBottomLeft;
    Image   *m_pImgBottomCenter;
	Image   *m_pImgBottomRight;
	
protected:
	//{{AFX_MSG(CTouchList)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );
	afx_msg void OnSize(UINT nType, int cx, int cy);
	LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnBindWndHide( WPARAM wParam, LPARAM lParam );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
*/

class CHoriList : public CTransparentHoriList
{
public:
    CHoriList( CString strName = "", CRect rcWnd = CRect(0,0,0,0), CWnd* pWnd = 0, UINT nID = 0, 
			   DWORD dwStyle = 0, DWORD dwExStyle = 0 );
	virtual ~CHoriList();
	virtual void Clicked( UINT nFlags, CPoint point );
};

#endif // !defined(AFX_TRANSPARENTHORILIST_H__0F6A8CB5_DF2A_4759_8ADA_EA9E0BD8C519__INCLUDED_)
