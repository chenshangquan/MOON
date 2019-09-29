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

#include "LogicBase.h"

typedef LONG MSGBOX_RET;
#define MSGBOX_OK     0
#define MSGBOX_CANCEL 1

class CMsgboxDlgLogic : public CLogicBase, public ISingleTon<CMsgboxDlgLogic> 
{
public:  
    CMsgboxDlgLogic();
	virtual ~CMsgboxDlgLogic();

public:  
	/** ����:  ע��ص�����
	*  @param[in] 
	*  @return 
	*  @remarks  �ڶ�ȡxml�ļ�ʱ��,���������ע��ĺ���
	*/	
	virtual void RegCBFun();
	/** ����:  ��ע��ص�����
	*  @param[in] 
	*  @return 
	*  @remarks  �����溯���෴,ע��ע��ĺ���
	*/
	virtual void UnRegFunc( );
	/** ����:  ��ʼ������
	*  @param[in] 
	*  @return 
	*  @remarks  �ڶ�ȡxml�ļ�ʱ�����,������������ݳ�ʼ������
	*/	
    virtual bool InitWnd( const IArgs & arg );

   /**	 
	* ����:  �������״̬������
	* @return   
	* @remarks	 
	*/
    virtual void Clear();

public:
	/** ����:  ���ȷ���İ�ť
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnBtnOk( const IArgs & arg );
	/** ����:  ���ȡ���İ�ť
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnBtnCancel( const IArgs & arg );

   /**	 
	* ����:  ���ڵ���(����ȷ����ȡ����ť)
	* @return   
	* @remarks	 
	*/
	void ShowMsgBox( MSGBOX_RET& nResult, const String& strText = ""  );

   /**	 
	* ����:  ���ڵ���(�ް�ť)
	* @return   
	* @remarks	 
	*/
	void ShowMsgBoxNoBtn( const String& strText = ""  );

   /**	 
	* ����:  ���ڵ���(ֻ��ȷ����ť)
	* @return   
	* @remarks	 
	*/
	void ShowMsgBoxOk( const String& strText = ""  );

	/**	 
	* ����:  ���ڵ���(ֻ��)
	* @return   
	* @remarks	 
	*/
	void ShowMsgBoxOnlyRead( const String& strText = ""  );

protected: 
	/** ����: ע����Ϣ,��������lib���з���������Ϣ
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/	
	virtual void RegMsg();
		
	/** ����: ��ע����Ϣ,�����溯���෴,ע��ע�����Ϣ
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/	
	virtual void UnRegMsg();
	
private:
	const String m_strStcMsgboxShowText;    

	MSGBOX_RET m_nMsgBoxRet; 

};

#ifndef MSG_BOX
#define MSG_BOX( nResult, strText  ) \
CMsgboxDlgLogic::GetSingletonPtr()->ShowMsgBox( nResult, strText );
#endif

#ifndef MSG_BOX_NOBTN
#define MSG_BOX_NOBTN( strText ) \
CMsgboxDlgLogic::GetSingletonPtr()->ShowMsgBoxNoBtn( strText );
#endif

#ifndef MSG_BOX_OK
#define MSG_BOX_OK( strText ) \
CMsgboxDlgLogic::GetSingletonPtr()->ShowMsgBoxOk( strText );
#endif

#ifndef MSG_BOX_ONLY_READ
#define MSG_BOX_ONLY_READ( strText ) \
CMsgboxDlgLogic::GetSingletonPtr()->ShowMsgBoxOnlyRead( strText );
#endif

#endif // !defined(AFX_MSGBOXDLGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
