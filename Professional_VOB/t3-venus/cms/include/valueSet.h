/*****************************************************************************
ģ����      : CMS����̨
�ļ���      : valueSet.h
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
 * @name WindowEnable �����Ƿ��������
 * @{
 */

DECLARE_VALUE_BEGIN( TransparentDlgMoveStatus,"Property to get/set TransparentDlg move status", "" )
bool bMove; //status 
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentDlgAutoHideStatus,"Property to get/set TransparentDlg lost focus hide status", "" )
bool bHide; //�ļ��� 
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentDlgImage,"Property to get/set TransparentDlg Image", "" )
String strImage; //�ļ��� 
DECLARE_VALUE_END
/*
DECLARE_VALUE_BEGIN( TransparentBaseListImage,"Property to get/set TransparentBaseList Image", "" )
String strImage; //�ļ��� 
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
unsigned long dwDataKey;  //����ʱʹ��
IBaseItem* pSelItem;      //��ȡʱʹ��
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
String strWndName; //������ 
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( HoriListOffset,"Property to get/set TransparenthoriList Offset", "" )
int nOffset;  
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( HoriListSelItem,"Property to get/set TransparenthoriList SelItem", "" )
unsigned long dwDataKey;  //����ʱʹ��
IBaseItem* pSelItem;      //��ȡʱʹ�� 
DECLARE_VALUE_END

#endif // !defined(AFX_VALUESET_H__C328EB95_FB1E_4F7B_B2D6_17FAC1B75D68__INCLUDED_)
