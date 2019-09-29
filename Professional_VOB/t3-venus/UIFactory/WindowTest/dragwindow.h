#if !defined(AFX_DRAGWINDOW_H__439058DE_E20C_452E_9D6A_12E009FD50E7__INCLUDED_)
#define AFX_DRAGWINDOW_H__439058DE_E20C_452E_9D6A_12E009FD50E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dragwindow.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDragWindow dialog

class CDragWindow : public CDialog
{
// Construction
	typedef IItem< IBaseItem, int > IItemList;
public:
	//CDragWindow( CRect rcList, CWnd* pWnd = NULL );
	CDragWindow(CWnd* pParent = NULL);   // standard constructor
	
	// Dialog Data
	//{{AFX_DATA(CDragWindow)
	enum { IDD = IDD_DRAG_WINDOW };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

protected:
	//{{AFX_MSG(CDragWindow)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	static CDragWindow* GetDragWindow();

	// 注册需要处理事件的窗口
	BOOL RegisterDropWindow( CWnd* pWnd );
	// 取消已注册的窗口
    BOOL UnRegisterDropWindow(CWnd* pWnd);

	void SetParentWindow( CWnd* parent );

	CWnd* GetActiveWindow(CPoint point);

	void ReportMsg( UINT msg, CPoint point );
	void ReportDragOver( CPoint point );

	BOOL BeginDrag( CPoint point, Bitmap* pBitmap );
	BOOL BeginDrag(CPoint point, IItemList* pItemList );
	BOOL Draging( CPoint point );
	BOOL EndDrag( CPoint point );

protected:
	void CreateDC();
	void DrawUI( Bitmap* pBitmap );
	void DrawUI( IItemList* pItemList );
	void DrawItem( IItemList* pItemList, IArgs* pArgs );

private:
	CDC     m_dcMemDC;
	CBitmap m_cBitMap;

	CWnd*   m_pParentWnd;                   //父列表窗口
	CWnd*   m_pLastWnd;                     //上次经过的窗口
//	CBaseItem*  m_pItemInfo;                //拖拽信息
	IItemList* m_pItemList;                    
	
	vector<CWnd*> m_vctWnd;                 // 注册的窗口

	static CDragWindow* m_pcDragWindow;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAGWINDOW_H__439058DE_E20C_452E_9D6A_12E009FD50E7__INCLUDED_)
