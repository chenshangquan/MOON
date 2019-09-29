#if !defined(AFX_TITLEWND_H__849D75C1_2F9C_4B0C_A793_F193D0BA6953__INCLUDED_)
#define AFX_TITLEWND_H__849D75C1_2F9C_4B0C_A793_F193D0BA6953__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TitleWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTitleWnd window

class CTitleWnd : public CWnd
{
// Construction
public:
	CTitleWnd(CString left,CString mid,CString right,int height);
	CTitleWnd(CString left,CString mid,CString right);
	CTitleWnd(CString folder,int height);
// Attributes
public:

// Operations
public:
//	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
protected:
	BOOL LoadImage(CString strPath,HBITMAP& bitmap,int& width);
	void DrawBitmap(CDC* pDC);

	HBITMAP m_hLeftBitmap;
	HBITMAP m_hMidBitmap;
	HBITMAP m_hRightBitmap;

	int m_nLeftWidth;
	int m_nRightWidth;
	int m_nMidWidth;
	int m_nHeight;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTitleWnd)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTitleWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTitleWnd)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TITLEWND_H__849D75C1_2F9C_4B0C_A793_F193D0BA6953__INCLUDED_)
