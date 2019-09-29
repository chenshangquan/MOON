// valueStorage.h: interface for the CValueStorage class.
/*****************************************************************************
ģ����      : CMS����̨
�ļ���      : valueStorage.h:
����ļ�    : 
�ļ�ʵ�ֹ���: ������������ĸ�����������
˵��       ��  
����        : �����
�汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2011/5/27  1.0          �����      ����
******************************************************************************/

#if !defined(AFX_VALUESTORAGE_H__53667E18_E994_4818_99E9_8B0974B7930D__INCLUDED_)
#define AFX_VALUESTORAGE_H__53667E18_E994_4818_99E9_8B0974B7930D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "IValue.h"

#include "templateClass.h"
//msgBox�Ĳ���
class Args_MsgBox : public IArgs
{
public:
   Window* pOwnerWnd;   //����msgBox�Ĵ��� 
   IArgs* pIargs;       //msgBox Ҫ���õĺ����Ĳ���
  
   Args_MsgBox( ):IArgs("MSG_BOX" )
   {
      pOwnerWnd = NULL;
      pIargs = NULL;
   }

};





#endif // !defined(AFX_VALUESTORAGE_H__53667E18_E994_4818_99E9_8B0974B7930D__INCLUDED_)
