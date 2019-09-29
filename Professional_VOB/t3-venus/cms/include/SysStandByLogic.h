// SysStandByLogic.h: interface for the CSysStandByLogic class.
//
//////////////////////////////////////////////////////////////////////

/*****************************************************************************
ģ����      : CSysStandByLogic
�ļ���      : SysStandByLogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: ϵͳ��������ҳ��
����        : ���`�`
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/12/5      1.0         ���`�`		����
******************************************************************************/

#if !defined(AFX_SYSSTANDBYLOGIC_H__92DF6A8B_CB04_458B_A3C6_D1CAA7A383FF__INCLUDED_)
#define AFX_SYSSTANDBYLOGIC_H__92DF6A8B_CB04_458B_A3C6_D1CAA7A383FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CSysStandByLogic : public CWndLogicBase 
{
public:
	CSysStandByLogic();
	virtual ~CSysStandByLogic();
	static CSysStandByLogic* GetLogicPtr();

		
public:
	/**	 
	* ����:  ע���logic�����еĻص�����
	* @return  void
	* @remarks	�ڴ�ע��Ļص�������Ҫ�ǿؼ�����Ӧ�¼�����Ϊ��Ա�ص�����,Ҳ��ע�������Ļص�����
	                    ע��ʱ��Ӧע��ص�������Ӧ���ӵ��������򣺡�����::��������
	*/
	virtual bool RegCBFun();

	/**	 
	* ����:  ע��ĳ�ص�����
	* @return  void
	* @remarks	 
	*/
	virtual bool UnRegFunc();

	/**	 
	* ���ܣ�����ϵͳ��������
	* @return  bool
	* @remarks	 
	*/

	virtual bool UpdateDlg();

	/**	 
	* ���ܣ�ע����Ϣ����
	* @return  void
	* @remarks	 ע������Ϣ���ܷ��͵����߼�ģ�飬���򣬽��ղ�������Ϣ
	*/
	virtual void RegMsg();

    /**	 
	* ����:  �������״̬������
	* @return   
	* @remarks	 
	*/
    virtual void Clear();

protected:
	/**	 
	* ����:  ��ʼ����������,
	* @return  void
	* @remarks	���ڸù��ܱ��������ؼ����Բ���xml����ؼ��󶨣�
	                    ��Ҫ��RegCBFun()��ע�ᵽ�ص���������ģ�� 
	*/
	bool InitWnd( const IArgs & args );

	/**
	* ����:  �������
	* @return  bool
	* @remarks  
	*/
	bool OnSave( const IArgs& args );

	/**	 
	* ����:  ���ȡ��
	* @return  bool
	* @remarks  
	*/
	bool OnCancel( const IArgs& args );

	/**	 
	* ����:  ����༭
	* @return  bool
	* @remarks  
	*/
	bool OnEdit( const IArgs& args );

// 	/**	 
// 	* ����:  ���ϵͳ�������ð�ť
// 	* @return  bool
// 	* @remarks  
// 	*/
//     bool BtnSysStandByClick( const IArgs& args );

	/**	 
	* ����:  ���ϵͳ���ð�ť
	* @return  bool
	* @remarks  
	*/
	bool OnSysCfg( const IArgs& args );

	/**	 
	* ����:  ������ٰ�ť��Ӧ����
	* @return  bool
	* @remarks  
	*/
	bool OnPlus( const IArgs& args );

	/**	 
	* ����:  �����Ӱ�ť��Ӧ����
	* @return  bool
	* @remarks  
	*/
	bool OnAdd( const IArgs& args );
	/**	 
	* ����:  ����������ť��Ӧ����
	* @return  bool
	* @remarks  
	*/
	bool OnBtnHoldEnd( const IArgs & arg ); 

	bool BtnSwitchStandByClick( const IArgs & arg ); 

	bool OnStandByTimeNoFocus( const IArgs & arg );
	
	void AddTime();

	LRESULT OnRegRsp( WPARAM wParam, LPARAM lParam );

    LRESULT OnSleepInfoNotify( WPARAM wParam, LPARAM lParam );
private:
	static CSysStandByLogic *m_pLogic;
    static String m_strBtnSysStandBySwitch;
	static String m_strEdtStandByTime;
	static String m_strBtnTimeDel;
	static String m_strBtnTimeAdd;
	TCenDevSleepInfo  m_tCenDevSleepInfo;
	BOOL           m_bOpen;  //�Ƿ���ϵͳ����

};

#endif // !defined(AFX_SYSSTANDBYLOGIC_H__92DF6A8B_CB04_458B_A3C6_D1CAA7A383FF__INCLUDED_)
