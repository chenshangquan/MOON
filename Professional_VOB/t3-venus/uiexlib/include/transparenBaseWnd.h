#ifndef TRANSPARENTBASEWND_HEAD_H
#define TRANSPARENTBASEWND_HEAD_H

#include "baseWnd.h"
#include "uiexBaseData.h"
#include "srcManage.h"
class CTransparentBaseWnd : public CBaseWnd
{
	// Construction
public:
	const static CString strLeft;
	const static CString strMid;
	const static CString strRight;
	const static CString strTop;
	const static CString strBottom;
	
	CTransparentBaseWnd(CRect rcWnd, CWnd* pWnd,DWORD dStyle,
		CString strUI,UINT nID, DWORD dwExStyle = 0,int nTrans = 255,BOOL bCanMove = FALSE, BOOL bStretchImage = TRUE ,CString strName = "");

	virtual ~CTransparentBaseWnd();
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransparentBaseWnd)
	protected:
    virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTransparentBaseWnd)
    afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnSize(UINT nType, int cx, int cy) ;
    BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
    //}}AFX_MSG
    afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnBindWnd( WPARAM wParam, LPARAM lParam );
	DECLARE_MESSAGE_MAP()

public:
    void SetAutoHideStatus( BOOL bStatus ){ m_bAutoHide = bStatus; } 
 
    void SetImage( CString strPath, BOOL bInvalidate = FALSE );
	void SetImage( Image* pImage, BOOL bInvalidate = FALSE );
    
    void SetMoveStatus( bool bMove ){ m_bCanMove = bMove; }

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
        BOOL bRet = CWnd::UpdateData( bSaveAndValidate );

        if ( FALSE == bSaveAndValidate )
        {
            PostMessage( WM_REDRAW_UI, NULL, NULL );
        }

        return bRet;
    }

protected:
    virtual void RedrawUI();
    virtual void DrawChildWnd( Graphics *pGraphics, HWND hParentWnd );

	void InitMemDC(); 
public:  
    BOOL  m_bTransparentWithoutBK;    // ���ޱ���ͼ��������Ƿ�͸����ʾ
    BOOL  m_bRedrawUIImediately;      // �Ƿ�����ˢ�£���������ˢ��Ƶ�ʵ�

	virtual int		GetWindowWidth();
	virtual int		GetWindowHeight();
	virtual BYTE	GetSourceConstantAlpha(){ return m_byteSourceConstantAlpha; }
	virtual void	SetSourceConstantAlpha(BYTE byteSCA){ m_byteSourceConstantAlpha = byteSCA; }

    static void AddIgnoreWnd( CWnd* pWnd );
protected:
	static PFN_UpdateLayeredWindow          m_s_pfnUpdateLayeredWindow;
   
    static vector<CWnd*> m_vctIgnoreWnd;   //ʧȥ�������ش���ʱ ���ԵĴ���
    HWND    m_hBindWnd;        //�󶨵�wnd
    Image   *m_pImageBK;
    BOOL    m_bReadyToRedrawUI; // ����ˢ��̫Ƶ��������Ч�ʽ���
	BYTE	m_byteSourceConstantAlpha; //͸���� 
   
    BOOL m_bCanMove;
    BOOL m_bAutoHide;  //ʧȥ�����Զ�����

	//���ʹ��ͼƬ�ļ��У�������ͼƴ�� 
    Image   *m_pImgLeft;           
    Image   *m_pImgMiddle;
    Image   *m_pImgRight;

	HDC      m_hDcMem;
	HBITMAP  m_hBtMap;

    CString m_strImgPath;
	bool    m_bDeleteImg;  //�Ƿ���Ҫ���ͼƬ
};

#endif