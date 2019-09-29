// AddrList.h: interface for the CAddrList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADDRLIST_H__C45DDBBA_9C1D_4D14_8907_6277EC712F2E__INCLUDED_)
#define AFX_ADDRLIST_H__C45DDBBA_9C1D_4D14_8907_6277EC712F2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dlgchild.h"

class CTransparentBaseList : public CDlgChild, public IList
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
	
	CTransparentBaseList( CString strName = "", CRect rcWnd = CRect(0,0,0,0), CWnd* pWnd = 0 );
	
	virtual ~CTransparentBaseList();
	void Draw( IArgs* pArgs );
	void DrawUI( Graphics* pGraphics, CWnd* pParent );
	virtual void Clicked( UINT nFlags, CPoint point );
	void SetDragEnable( BOOL bDrag );
	BOOL GetDragEnable() { return m_bDragEnable; }
	
	void SetYOffset( int nOffset );
	int  GetYOffset();
	void SetBottomOffset();
	
	void SetClickNoSel( BOOL bSel );
	BOOL IsClickNoSel() { return m_bClickNoSel; }
	void SetClickFocus( BOOL bFocus );
	BOOL IsClickFocus() { return m_bClickFocus; }
	
	void SetSelItem( unsigned long dwDataKey );
	void ResetSelItem( BOOL bResetOffset = FALSE );
	IBaseItem* GetSelItem();
	
	void SetImage( CString strImageFolder, BOOL bInvalidate = FALSE );
	Image* MosaicListImage();

    void Clear(); //清空所有成员变量
	
protected:
	CRect GetFrameInScreen( IItemList* pList );
	void  UpdateTotalHeight();
	CRect GetListRect();
	BOOL IsReadyForDrag();
	void SetSelItemStatus( EmItemStatus emStatus );
	int  GetOffsetHeight( int nIndex );
	
	void ListMove();
	void ListAutoMove();
protected:
	CRect   m_rctDlg;                      //列表框Rect
	CRect   m_rctList;	                   //整个列表数据Rect
	int     m_nTotalYOffset;               //当前总的Y轴偏移量
	int     m_nTotalXOffset;
	CPoint  m_ptMouseLast;
	CPoint  m_ptMouseNow;
	CPoint  m_ptMouseDown;
	int     m_nMoveSpeed;
	BOOL    m_bLBtnDown;
	IItemList*  m_pSelItem;               //当前选中
	IItemList*   m_pLastItem;
	unsigned long m_dwSelDataKey;          //选中Item的数据索引
	
	BOOL    m_bDragEnable;                 //是否允许拖拽
	BOOL    m_bClickNoSel;                 //点击后是否将条目设为不选中
	BOOL    m_bClickFocus;                 //点击后是否设置焦点
	
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
	afx_msg LRESULT	OnMouseWheels( WPARAM wParam, LPARAM lParam );	
	afx_msg void OnSize(UINT nType, int cx, int cy);	
	LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//用于获取二级汉字首字母拼音
class CPYChar  
{
public:
    CPYChar();
    virtual ~CPYChar();
    static BOOL In(int Lp, int Hp,int Value);
    char GetPYChar(CString HZ) ;
    static char GetPYChar(TCHAR c1,TCHAR c2); 
    static CString m_ArrQWSecond[32];   //区位码字母头: 56区~87区对应0~30
};


class CTransparentAddrList : public CTransparentList //CTransparentBaseList
{
public:
	CTransparentAddrList( CString strName = "", CString strUI = "", CRect rcWnd = CRect(0,0,0,0), CWnd* pWnd = 0, UINT nID = 0, 
		DWORD dStyle = 0, DWORD dwExStyle = 0 );
	virtual ~CTransparentAddrList();
	virtual void Clicked( UINT nFlags, CPoint point );

	static CString FirstLetter( int nCode );
	static void GetFirstLetter(CString strName, CString& strFirstLetter);

	//排序算法
	static bool AddrItemCompare(TAddrItem& tItem1, TAddrItem& tItem2);
	static bool CnsInfoCompare(TCnsInfo& tInfo1, TCnsInfo& tInfo2);
	static bool TPCnsInfoCompare(TTPCnsInfo& tInfo1, TTPCnsInfo& tInfo2);
    static bool TempCnsCompare( TEpAddr& tCns1, TEpAddr& tCns2 );
    static bool ConfTempCompare( TTPAlias& tAlias1, TTPAlias& tAlias2 );

    static bool UserItemCompare(CUserFullInfo& tItem1, CUserFullInfo& tItem2);
    static bool ConfMenuCompare(TConfMenuInfo& tItem1, TConfMenuInfo& tItem2);
protected:
	LRESULT OnLetterClick( WPARAM wParam, LPARAM lParam );

	DECLARE_MESSAGE_MAP()
};

 
#endif // !defined(AFX_ADDRLIST_H__C45DDBBA_9C1D_4D14_8907_6277EC712F2E__INCLUDED_)
