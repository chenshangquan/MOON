// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__02F16DE6_1433_4A93_B4B8_020599AEB6CE__INCLUDED_)
#define AFX_STDAFX_H__02F16DE6_1433_4A93_B4B8_020599AEB6CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#pragma warning( disable : 4786 )	// 标识符名称超过255字节

#include <afx.h>
#include <afxwin.h>

//cms内部共用头文件
#include "cmsConst.h"
#include "evCmsLib.h"

// tp 共用头文件
#include "tpsys.h"

#endif // !defined(AFX_STDAFX_H__02F16DE6_1433_4A93_B4B8_020599AEB6CE__INCLUDED_)
