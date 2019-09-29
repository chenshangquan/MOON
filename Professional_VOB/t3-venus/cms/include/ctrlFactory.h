
/*****************************************************************************
模块名      : CMS控制台
文件名      : ctrlFactory.h
相关文件    : 
文件实现功能: cms所需控件库
作者        : 俞锦锦
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2011/5/24  1.0          俞锦锦      创建
******************************************************************************/

#if !defined(AFX_CTRLFACTORY_H__BE6E09DB_79F2_442C_8BBD_37E307F33743__INCLUDED_)
#define AFX_CTRLFACTORY_H__BE6E09DB_79F2_442C_8BBD_37E307F33743__INCLUDED_

#include "uiManage.h"
#include "MfcDefaultArgs.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

using namespace AutoUIFactory;

#define REG_ALL_CTRLS   RegCtrls();

//声明控件
#define DECLARE_CTRL_FACTORY( CtrlName ) \
class CtrlName##Factory : public IWindowFactory \
{ \
public: \
CtrlName##Factory(){} \
virtual ~CtrlName##Factory(){} \
	virtual Window* Create( IArgs& iAgrs  ); \
}; 

//注册控件
void RegCtrls();

 
DECLARE_CTRL_FACTORY( CListCtrl ) 
//DECLARE_CTRL_FACTORY( CAddrList )
DECLARE_CTRL_FACTORY( CTransparentAddrList )
DECLARE_CTRL_FACTORY( CHoriList )

//dlg 模板
DECLARE_CTRL_FACTORY(CTransparentBaseDlg)
DECLARE_CTRL_FACTORY( CDlgOverLapped)
DECLARE_CTRL_FACTORY( CDlgPopup)
DECLARE_CTRL_FACTORY( CDlgChild)
DECLARE_CTRL_FACTORY( CDlgModal)
DECLARE_CTRL_FACTORY( CPopupDlg)



 
#endif // !defined(AFX_CTRLFACTORY_H__BE6E09DB_79F2_442C_8BBD_37E307F33743__INCLUDED_)
