// centerctrl.h : main header file for the CENTERCTRL application
//

#if !defined(AFX_CENTERCTRL_H__6182AB4A_192F_4640_A210_0F367C4E00F2__INCLUDED_)
#define AFX_CENTERCTRL_H__6182AB4A_192F_4640_A210_0F367C4E00F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCenterCtrlApp:
// See centerctrl.cpp for the implementation of this class
//

class CCenterCtrlApp : public CWinApp
{
public:
	CCenterCtrlApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCenterCtrlApp)
	public:
	virtual BOOL InitInstance();
    virtual int ExitInstance();
    virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCenterCtrlApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
    bool IsHasStart();
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CENTERCTRL_H__6182AB4A_192F_4640_A210_0F367C4E00F2__INCLUDED_)
