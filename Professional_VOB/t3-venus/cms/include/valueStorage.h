// valueStorage.h: interface for the CValueStorage class.
/*****************************************************************************
模块名      : CMS控制台
文件名      : valueStorage.h:
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

#if !defined(AFX_VALUESTORAGE_H__53667E18_E994_4818_99E9_8B0974B7930D__INCLUDED_)
#define AFX_VALUESTORAGE_H__53667E18_E994_4818_99E9_8B0974B7930D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "IValue.h"

#include "templateClass.h"
//msgBox的参数
class Args_MsgBox : public IArgs
{
public:
   Window* pOwnerWnd;   //弹出msgBox的窗口 
   IArgs* pIargs;       //msgBox 要调用的函数的参数
  
   Args_MsgBox( ):IArgs("MSG_BOX" )
   {
      pOwnerWnd = NULL;
      pIargs = NULL;
   }

};





#endif // !defined(AFX_VALUESTORAGE_H__53667E18_E994_4818_99E9_8B0974B7930D__INCLUDED_)
