// callingDlg.h: interface for the CCallingDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALLINGDLG_H__9FA87D50_6D38_481B_879C_6078F6CA8CFA__INCLUDED_)
#define AFX_CALLINGDLG_H__9FA87D50_6D38_481B_879C_6078F6CA8CFA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "msgbox.h"
#include "uiexhead.h"
class CCallingDlg:public CMsgBox 
{
public:
	CCallingDlg( Window * pParent = NULL );
	virtual ~CCallingDlg();
protected:
    
    // Generated message map functions
    //{{AFX_MSG(CCallingDlg)
    virtual BOOL OnInitDialog();
    virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
    afx_msg void OnTimer(UINT nIDEvent);

    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
public:
    void CCallingDlg::HideCallingBox( );

 
    //¸ü»»ºô½ÐÍ¼Æ¬
    void  UpdateCallingImg();
public:
    CTransparentBtn m_btnHungup;
    CTransparentStatic m_stcImg;
    CTransparentStatic m_stcMsg; 

    CString m_strImgArray[4];

    int m_nNowImgIndex;

};

#endif // !defined(AFX_CALLINGDLG_H__9FA87D50_6D38_481B_879C_6078F6CA8CFA__INCLUDED_)
