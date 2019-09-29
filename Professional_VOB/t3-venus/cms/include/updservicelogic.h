/*****************************************************************************
ģ����      : CUpdServiceLogic
�ļ���      : updservicelogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: ������������ַ
����        : ʯ��
�汾        : V1.0  Copyright(C) 2013-2014 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/3/18      1.0         ʯ��			����
******************************************************************************/
#if !defined(UMC_UPDSERVICELOGIC_H)
#define UMC_UPDSERVICELOGIC_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CUpdServiceLogic : public CWndLogicBase 
{
public:
	CUpdServiceLogic();
	virtual ~CUpdServiceLogic();
	static CUpdServiceLogic* GetLogicPtr();
	
public:
	virtual bool RegCBFun();
	virtual bool UnRegFunc();
	virtual void RegMsg();

    /**	 
	* ����:  �������״̬������
	* @return   
	* @remarks	 
	*/
    virtual void Clear();

protected:
	bool InitWnd( const IArgs & args );

	/**	 
	* ����:  ���ϵͳ����
	* @return  bool
	* @remarks  
	*/
	bool OnSysCfg( const IArgs& args );

	/**	 
	* ����:  ����༭
	* @return  bool
	* @remarks  
	*/
	bool OnEdit( const IArgs& args );

	/**	 
	* ����:  ���ȡ��
	* @return  bool
	* @remarks  
	*/
	bool OnCancel( const IArgs& args );

	/**
	* ����:  �������
	* @return  bool
	* @remarks  
	*/
	bool OnSave( const IArgs& args );

	bool OnCloseDlg( const IArgs & arg );

	LRESULT OnUpdServiceIPNty( WPARAM wParam, LPARAM lParam );
	LRESULT OnUpdServiceIPInd( WPARAM wParam, LPARAM lParam );

private:
	String GetServiceIP();
	void SetServiceIP();
	bool CheckServiceIP( String strServiceIP );

private:
	static CUpdServiceLogic *m_pLogic;
};

#endif // !defined(UMC_UPDSERVICELOGIC_H)
