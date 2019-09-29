// dlgModal.h: interface for the CDlgModal class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DLGMODAL_H__B044C51A_725C_42AD_93E8_E6BF7913A916__INCLUDED_)
#define AFX_DLGMODAL_H__B044C51A_725C_42AD_93E8_E6BF7913A916__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
 
#include "dlgpopup.h"

class CDlgModal : public CDlgPopup  
{ 
 
public:
    CDlgModal( CWnd* pParent = NULL );   // standard constructor
    virtual ~CDlgModal();
   
  
protected: 
    // Generated message map functions
    //{{AFX_MSG(CTransparentBaseDlg)
    virtual BOOL OnInitDialog();
    
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    //}}AFX_MSG
    
    DECLARE_MESSAGE_MAP()
private:
    
};

#endif // !defined(AFX_DLGMODAL_H__B044C51A_725C_42AD_93E8_E6BF7913A916__INCLUDED_)
