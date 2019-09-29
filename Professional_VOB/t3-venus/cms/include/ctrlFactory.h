
/*****************************************************************************
ģ����      : CMS����̨
�ļ���      : ctrlFactory.h
����ļ�    : 
�ļ�ʵ�ֹ���: cms����ؼ���
����        : �����
�汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2011/5/24  1.0          �����      ����
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

//�����ؼ�
#define DECLARE_CTRL_FACTORY( CtrlName ) \
class CtrlName##Factory : public IWindowFactory \
{ \
public: \
CtrlName##Factory(){} \
virtual ~CtrlName##Factory(){} \
	virtual Window* Create( IArgs& iAgrs  ); \
}; 

//ע��ؼ�
void RegCtrls();

 
DECLARE_CTRL_FACTORY( CListCtrl ) 
//DECLARE_CTRL_FACTORY( CAddrList )
DECLARE_CTRL_FACTORY( CTransparentAddrList )
DECLARE_CTRL_FACTORY( CHoriList )

//dlg ģ��
DECLARE_CTRL_FACTORY(CTransparentBaseDlg)
DECLARE_CTRL_FACTORY( CDlgOverLapped)
DECLARE_CTRL_FACTORY( CDlgPopup)
DECLARE_CTRL_FACTORY( CDlgChild)
DECLARE_CTRL_FACTORY( CDlgModal)
DECLARE_CTRL_FACTORY( CPopupDlg)



 
#endif // !defined(AFX_CTRLFACTORY_H__BE6E09DB_79F2_442C_8BBD_37E307F33743__INCLUDED_)
