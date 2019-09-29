/*****************************************************************************
ģ����      : CBoardOptDlgLogic
�ļ���      : boardoptdlglogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: logic��������޸�ҳ��
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/12/24     1.0         ����ӡ      ����
******************************************************************************/
#if !defined(AFX_BOARDOPTDLGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
#define AFX_BOARDOPTDLGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CBoardOptDlgLogic :public CWndLogicBase, public ISingleTon<CBoardOptDlgLogic>  
{
public:  
    CBoardOptDlgLogic();
	virtual ~CBoardOptDlgLogic();

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

protected:
	bool OnBtnOptBoardOk( const IArgs & arg );
	bool OnBtnOptBoardCancel( const IArgs & arg );

	bool OnBtnOptTvwBoardOk( const IArgs & arg );
	bool OnBtnOptTvwBoardCancel( const IArgs & arg );
	
	HRESULT OnBoardSelData( WPARAM wparam, LPARAM lparam );
	HRESULT OnTvwBoardSelData( WPARAM wparam, LPARAM lparam );

		/**	 
	* ����: ����IP�ı�
	* @return   bool
	* @remarks  
	*/
	bool OnBoardOptIpChange( const IArgs & arg );

protected: 
	virtual void RegMsg(); 
	virtual void UnRegMsg();
	
private:
	const String  m_strComboboxBoardType;
	const String  m_strEdtIpAddr;
	const String  m_strStcBoardTypeShow; 
	const String  m_strStcShowLayarNo;     
	const String  m_strStcShowSlotNo;   
	const String  m_strBtnBoardOptOk;
	const String  m_strBtnTvwBoardOptOk;

	TTPBrdInfo m_tBoardInfoSel;
	THduCfg m_tHduCfgSel;
	EM_BOARDOPT_TYPE m_emBoardType;

};

#define BOARDOPTLOGICRPTR    CBoardOptDlgLogic::GetSingletonPtr()               //�������logicָ��

#endif // !defined(AFX_BOARDOPTDLGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
