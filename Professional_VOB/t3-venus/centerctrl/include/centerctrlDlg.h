// centerctrlDlg.h : header file
//

#if !defined(AFX_CENTERCTRLDLG_H__633BD037_59E9_480E_9FF4_2D649E6F36C6__INCLUDED_)
#define AFX_CENTERCTRLDLG_H__633BD037_59E9_480E_9FF4_2D649E6F36C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCenterCtrlDlg dialog

class CCenterCtrlDlg : public CDialog
{
// Construction
public:
	CCenterCtrlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCenterCtrlDlg)
	enum { IDD = IDD_CENTERCTRL_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCenterCtrlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCenterCtrlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CENTERCTRLDLG_H__633BD037_59E9_480E_9FF4_2D649E6F36C6__INCLUDED_)
