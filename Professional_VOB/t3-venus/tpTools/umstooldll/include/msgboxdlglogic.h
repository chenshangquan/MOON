/*****************************************************************************
ģ����      : CMsgboxDlgLogic
�ļ���      : msgboxdlglogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: logic Msgbox������ʾ��
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/12/07     1.0         ����ӡ      ����
******************************************************************************/
#if !defined(AFX_MSGBOXDLGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
#define AFX_MSGBOXDLGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

typedef LONG MSGBOX_RET;
#define MSGBOX_OK     0
#define MSGBOX_CANCEL -1

class CMsgboxDlgLogic :public CWndLogicBase, public ISingleTon<CMsgboxDlgLogic> 
{
public:  
    CMsgboxDlgLogic();
	virtual ~CMsgboxDlgLogic();

public:  
	
	virtual bool RegCBFun();
	
	virtual bool UnRegFunc( );
	
    virtual bool InitWnd( const IArgs & arg );

   /**	 
	* ����:  �������״̬������
	* @return   
	* @remarks	 
	*/
    virtual void Clear();

public:
	bool OnBtnOk( const IArgs & arg );
	bool OnBtnCancel( const IArgs & arg );

	void ShowMsgBox( MSGBOX_RET& nResult, const String& strText = ""  );
	void ShowMsgBoxNoBtn( const String& strText = ""  );
	void ShowMsgBoxOk( const String& strText = ""  );
protected: 
	virtual void RegMsg(); 
	virtual void UnRegMsg();
	
private:
	const String m_strStcMsgboxShowText;    

	MSGBOX_RET m_nMsgBoxRet; 

};

#define MSGBOXLOGICRPTR    CMsgboxDlgLogic::GetSingletonPtr()               //msgbox logicָ��

#ifndef MSG_BOX
#define MSG_BOX( nResult, strText  ) \
MSGBOXLOGICRPTR->ShowMsgBox( nResult, strText );
#endif

#ifndef MSG_BOX_NOBTN
#define MSG_BOX_NOBTN( strText ) \
MSGBOXLOGICRPTR->ShowMsgBoxNoBtn( strText );
#endif

#ifndef MSG_BOX_OK
#define MSG_BOX_OK( strText ) \
MSGBOXLOGICRPTR->ShowMsgBoxOk( strText );
#endif

#endif // !defined(AFX_MSGBOXDLGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
