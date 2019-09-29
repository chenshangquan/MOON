/*****************************************************************************
模块名      : CMS控制台
文件名      : valueSet.h
相关文件    : 
文件实现功能: 设置属性所需的各种数据类型
说明       ：  
作者        : 俞锦锦
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2011/5/27  1.0          俞锦锦      创建
******************************************************************************/

#if !defined(AFX_VALUESET_H__C328EB95_FB1E_4F7B_B2D6_17FAC1B75D68__INCLUDED_)
#define AFX_VALUESET_H__C328EB95_FB1E_4F7B_B2D6_17FAC1B75D68__INCLUDED_
#include "IValue.h"
#include "MfcDefaultWndProperty.h" 
#include "ctrlFactory.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
using namespace  AutoUIFactory;

void RegWindowProperty();

 /*
 * @name WindowEnable 窗口是否可用属性
 * @{
 */

DECLARE_VALUE_BEGIN( TransparentDlgMoveStatus,"Property to get/set TransparentDlg move status", "" )
bool bMove; //status 
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentDlgAutoHideStatus,"Property to get/set TransparentDlg lost focus hide status", "" )
bool bHide; //文件夹 
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentDlgImage,"Property to get/set TransparentDlg Image", "" )
String strImage; //文件夹 
DECLARE_VALUE_END
/*
DECLARE_VALUE_BEGIN( TransparentBaseListImage,"Property to get/set TransparentBaseList Image", "" )
String strImage; //文件夹 
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentBaseListDrag,"Property to get/set TransparentBaseList Drag status", "" )
bool bCanDrag; // name
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentBaseListClickNoSel,"Property to get/set TransparentBaseList ClickNoSel status", "" )
bool bNoSel; 
DECLARE_VALUE_END


DECLARE_VALUE_BEGIN( TransparentBaseListItemSizeSame,"Property to get/set TransparentBaseList EveryItemSizeSame", "" )
bool bAllItemsSizeSame; 
DECLARE_VALUE_END
 

DECLARE_VALUE_BEGIN( TransparentBaseListSelItem,"Property to get/set TransparentBaseList select item", "" )
unsigned long dwDataKey;  //设置时使用
IBaseItem* pSelItem;      //获取时使用
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentBaseListOffset,"Property to get/set TransparentBaseList offset", "" )
int nOffset;  
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentBaseListClickFocus,"Property to get/set TransparentBaseList clickfoucs status", "" )
bool bFocus;  
DECLARE_VALUE_END
*/
DECLARE_VALUE_BEGIN( HoriListOffsetIndex,"Property to get/set TransparenthoriList offsetindex", "" )
int nIndex;   
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( HoriListClickNoSel,"Property to get/set TransparenthoriList ClickNoSel", "" )
bool bNoSel;   
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( HoriListItemCount,"Property to get/set TransparenthoriList ItemCount", "" )
int nCount;   
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( HoriListBindWnd,"Property to get/set TransparenthoriList BindWnd", "" )
String strWndName; //窗口名 
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( HoriListOffset,"Property to get/set TransparenthoriList Offset", "" )
int nOffset;  
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( HoriListSelItem,"Property to get/set TransparenthoriList SelItem", "" )
unsigned long dwDataKey;  //设置时使用
IBaseItem* pSelItem;      //获取时使用 
DECLARE_VALUE_END

#endif // !defined(AFX_VALUESET_H__C328EB95_FB1E_4F7B_B2D6_17FAC1B75D68__INCLUDED_)
