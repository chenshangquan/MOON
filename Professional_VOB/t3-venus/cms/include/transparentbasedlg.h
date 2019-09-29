#if !defined(AFX_TRANSPARENTBASEDLG_H__BCB28327_5163_451D_AE72_6DCD487821DA__INCLUDED_)
#define AFX_TRANSPARENTBASEDLG_H__BCB28327_5163_451D_AE72_6DCD487821DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TransparentBaseDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTransparentBaseDlg dialog

typedef BOOL(WINAPI *PFN_SetLayeredWindowAttributes)(
                                                     HWND hwnd,
                                                     COLORREF crKey,
                                                     BYTE bAlpha,
                                                     DWORD dwFlags);

typedef BOOL(WINAPI *PFN_UpdateLayeredWindow)( 
                                              HWND hWnd,
                                              HDC hdcDst,
                                              POINT *pptDst,
                                              SIZE *psize,
                                              HDC hdcSrc,
                                              POINT *pptSrc,
                                              COLORREF crKey,
                                              BLENDFUNCTION *pblend,
											  DWORD dwFlags);

#ifndef WS_EX_LAYERED
#	define WS_EX_LAYERED			0x00080000
#endif

#ifndef LWA_ALPHA
#	define LWA_ALPHA				0x00000002
#endif

#ifndef ULW_ALPHA
#	define ULW_ALPHA				0x00000002
#endif

#ifndef AC_SRC_ALPHA
#	define AC_SRC_ALPHA				0x01
#endif
class CTransparentBaseDlg : public CDialog
{
// Construction
public:
	CTransparentBaseDlg(UINT nIDTemplate, CWnd* pParent = NULL);   // standard constructor
	virtual ~CTransparentBaseDlg();
// Dialog Data
	//{{AFX_DATA(CTransparentBaseDlg)
	enum { IDD = 0 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransparentBaseDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTransparentBaseDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
    afx_msg void OnWindowPosChanging(WINDOWPOS   FAR*   lpwndpos); 
    afx_msg void OnSize(UINT nType, int cx, int cy) ;
	afx_msg void   OnSysCommand(UINT   nID,   LPARAM   lParam);
   // afx_msg void OnWindowPosChanged( WINDOWPOS* lpwndpos );
    


    //}}AFX_MSG
    afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnBindWnd( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnHideWnd( WPARAM wParam, LPARAM lParam );
	DECLARE_MESSAGE_MAP()

public:

    void SetAutoHideStatus( BOOL bStatus ){ m_bAutoHide = bStatus; } 
 
    void SetImage( CString strPath, BOOL bInvalidate = FALSE );
	void SetImage( Image* pImage, BOOL bInvalidate = FALSE );
    
    void SetMoveStatus( bool bMove ){ m_bCanMove = bMove; }
    BOOL GetMoveStatus() { return m_bCanMove; }

    BOOL ShowWindow(int nCmdShow)
    {
        BOOL bRet = CWnd::ShowWindow( nCmdShow );

        if ( SW_SHOW == nCmdShow )
        {
            SendMessage( WM_REDRAW_UI, NULL, NULL );
        }

        return bRet;
    }

    BOOL UpdateData(BOOL bSaveAndValidate = TRUE)
    {
        BOOL bRet = CDialog::UpdateData( bSaveAndValidate );

        if ( FALSE == bSaveAndValidate )
        {
            PostMessage( WM_REDRAW_UI, NULL, NULL );
        }

        return bRet;
    }

	void SetBindWnd( HWND hdl );
protected:
    virtual void RedrawUI();

    virtual void DrawChildWnd( Graphics *pGraphics, HWND hParentWnd );
    
	void InitMemDC(); //2012-7-2 避免每次绘制都创建memeryDc  yjj
public:
    
    BOOL32  m_bTransparentWithoutBK;    // 在无背景图的情况下是否透明显示
    BOOL32  m_bRedrawUIImediately;      // 是否立即刷新，用来控制刷新频率的

	virtual s32		GetWindowWidth();
	virtual s32		GetWindowHeight();
	virtual BYTE	GetSourceConstantAlpha(){ return m_byteSourceConstantAlpha; }
	virtual void	SetSourceConstantAlpha(BYTE byteSCA){ m_byteSourceConstantAlpha = byteSCA; }

    static void AddIgnoreWnd( CWnd* pWnd );
protected:
    static PFN_SetLayeredWindowAttributes   m_s_pfnSetLayeredWindowAttributes;
	static PFN_UpdateLayeredWindow          m_s_pfnUpdateLayeredWindow;
   
    static vector<CWnd*> m_vctIgnoreWnd;   //失去焦点隐藏窗口时 忽略的窗口
    HWND    m_hBindWnd;        //绑定的wnd
    Image   *m_pImageBK;
    BOOL32  m_bReadyToRedrawUI; // 避免刷新太频繁，导致效率降低
	BYTE	m_byteSourceConstantAlpha; //透明度 
   
    BOOL32 m_bCanMove;
    BOOL32 m_bAutoHide;  //失去焦点自动隐藏

//如果使用图片文件夹，由三张图拼接 
    Image   *m_pImgLeft;           
    Image   *m_pImgMiddle;
    Image   *m_pImgRight;
    HDC      m_hDcMem;
	HBITMAP  m_hBtMap;
    
    const static CString strTop;
	const static CString strBottom; 
    const static CString strLeft;
    const static CString strMid;
	const static CString strRight;

    CString m_strImgPath;

	bool m_bNeedDeleteImg;//是否需要清除图片
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSPARENTBASEDLG_H__BCB28327_5163_451D_AE72_6DCD487821DA__INCLUDED_)
