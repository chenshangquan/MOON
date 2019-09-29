// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__43F77A7E_BC8C_4452_A4A1_581BCF01EFFC__INCLUDED_)
#define AFX_STDAFX_H__43F77A7E_BC8C_4452_A4A1_581BCF01EFFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

// #ifndef ULONG_PTR
// 
// #define ULONG_PTR unsigned long*
// 
// #endif
// 
// #include <GdiPlus.h>
// using namespace Gdiplus;
// 
// #pragma comment(lib,"gdiplus.lib")

#include <wingdi.h> //头文件
#pragma comment (lib,"msimg32.lib") //连接库

#pragma warning( disable : 4786 )
#include "uilibhead.h"
#include "UifactoryHeader.h"

#include "uiexhead.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__43F77A7E_BC8C_4452_A4A1_581BCF01EFFC__INCLUDED_)
