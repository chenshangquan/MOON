// loadcmcDlg.h : header file
//

#if !defined(AFX_LOADCMCDLG_H__57450882_61FE_4624_A0C5_7E5CF134E76F__INCLUDED_)
#define AFX_LOADCMCDLG_H__57450882_61FE_4624_A0C5_7E5CF134E76F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CLoadcmcDlg dialog

class CLoadcmcDlg : public CDialog
{
// Construction
public:
	CLoadcmcDlg(CWnd* pParent = NULL);	// standard constructor
	~CLoadcmcDlg();

// Dialog Data
	//{{AFX_DATA(CLoadcmcDlg)
	enum { IDD = IDD_LOADCMC_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoadcmcDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CLoadcmcDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnUpdateOver(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRebootCmc(WPARAM wParam, LPARAM lParam);
		
	void InitializeOsp();
	BOOL InitFtpServer();

	void CopyFiles();

	BOOL ExistDir( const CString strDir );
	BOOL CreateDir( CString strDir );
	BOOL MoveFile( char *pFrom, char *pTo );

	void CloseCmc();
	void ReBootCmc();
private:
	BOOL m_bInitOsp;

	CString m_strFileStorePath;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOADCMCDLG_H__57450882_61FE_4624_A0C5_7E5CF134E76F__INCLUDED_)
