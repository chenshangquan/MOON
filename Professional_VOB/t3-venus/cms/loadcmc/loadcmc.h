// loadcmc.h : main header file for the LOADCMC application
//

#if !defined(AFX_LOADCMC_H__294E2BBE_88B9_4F96_8BE6_5B00FF8FD656__INCLUDED_)
#define AFX_LOADCMC_H__294E2BBE_88B9_4F96_8BE6_5B00FF8FD656__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CLoadcmcApp:
// See loadcmc.cpp for the implementation of this class
//

class CLoadcmcApp : public CWinApp
{
public:
	CLoadcmcApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoadcmcApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CLoadcmcApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOADCMC_H__294E2BBE_88B9_4F96_8BE6_5B00FF8FD656__INCLUDED_)
