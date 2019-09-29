// WindowTest.h : main header file for the WINDOWTEST application
//

#if !defined(AFX_WINDOWTEST_H__BF128FFD_BDCE_4E3D_AA71_BDBBA5D25011__INCLUDED_)
#define AFX_WINDOWTEST_H__BF128FFD_BDCE_4E3D_AA71_BDBBA5D25011__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWindowTestApp:
// See WindowTest.cpp for the implementation of this class
//

class CWindowTestApp : public CWinApp
{
public:
	CWindowTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWindowTestApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWindowTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINDOWTEST_H__BF128FFD_BDCE_4E3D_AA71_BDBBA5D25011__INCLUDED_)
