/*****************************************************************************
模块名      : StdAfx
文件名      : StdAfx.h
相关文件    : 
文件实现功能: 程序测试基本控件（auto ui）
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/6/22       1.0         刘德印      创建
******************************************************************************/
#if !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
#define AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_

#pragma once

#define WIN32_LEAN_AND_MEAN	
#define _CRT_SECURE_NO_DEPRECATE

#include "UIlib.h"
#pragma comment(lib, "duiexlib.lib")

#define MESSAGEWND(x) MessageBox(NULL, x, L"TITLE", MB_OK )     //MessageBox弹出框



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
