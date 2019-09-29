/*****************************************************************************
ģ����      : CWarningLogic
�ļ���      : warninglogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: logic��Ϣ��ʾҳ��
����        : ʯ��
�汾        : V1.0  Copyright(C) 2013-2014 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/7/18      1.0         ʯ��        ����
******************************************************************************/
#if !defined(UMSTOOL_WARNINGLOGIC_H)
#define UMSTOOL_WARNINGLOGIC_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CWarningLogic :public CWndLogicBase, public ISingleTon<CWarningLogic>
{
public:
    CWarningLogic();
	virtual ~CWarningLogic();

public:  
	/**	 
	* ����:  ע���logic�����еĻص�����
	* @return  void
	* @remarks	�ڴ�ע��Ļص�������Ҫ�ǿؼ�����Ӧ�¼�����Ϊ��Ա�ص�����,Ҳ��ע�������Ļص�����
	                    ע��ʱ��Ӧע��ص�������Ӧ���ӵ��������򣺡�����::��������
	*/
	virtual bool RegCBFun();

	/**	 
	* ����:  ע��Ҫ�������Ϣ
	* @return  void
	* @remarks	 ע������Ϣ���ܷ��͵����߼�ģ�飬���򣬽��ղ�������Ϣ
	*/
	virtual void RegMsg(); 

	/**	 
	* ����:  ע��ĳ�ص�����
	* @return  void
	* @remarks	 
	*/
	virtual bool UnRegFunc( );

	/**	 
	* ����:  ע��ĳ�ص�����
	* @return  void
	* @remarks	 
	*/
	virtual void UnRegMsg();
	
	/**	 
	* ����:  ��ʼ����������,
	* @return  void
	* @remarks	���ڸù��ܱ��������ؼ����Բ���xml����ؼ��󶨣�
	                    ��Ҫ��RegCBFun������ע�ᵽ�ص���������ģ�� 
	*/
    virtual bool InitWnd( const IArgs & arg );

   /**	 
	* ����:  ����ʱ�������״̬������
	* @return   
	* @remarks	 
	*/
    virtual void Clear();

public:
	void MessageBoxWnd( const CString& strWaringText);

protected:	
	

protected:
	/**	 
	* ����: �����ʾ��Ϣ���ϰ�ť
	* @return   bool
	* @remarks  
	*/
	bool OnBtnWarningPre( const IArgs & arg );

	/**	 
	* ����: �����ʾ��Ϣ���°�ť
	* @return   bool
	* @remarks  
	*/
	bool OnBtnWarningNext( const IArgs & arg );
	
private:
	//������ʾ��Ϣ
	void UpdateItem();

	//���°�ť״̬
	void UpdateBtn();

	/*
	**�������ܣ���Ϣ��ʾҳ��ı�
	**���������BOOL ��ʾ�Ƿ�����
	*/
	void WarningChage( BOOL bPre );	

private:
	//���߼���Ԫ��Ӧ�����пؼ���
	const String  m_stcWarning;
	const String  m_btnWarningPre;
	const String  m_btnWarningNext;

	std::vector<CString> m_vecWarning;			//��ʾ��Ϣ
	int m_nIndex;								//��ǰ��ʾ��ʾ��Ϣ������
	std::vector<BOOL> m_vecIsShow;				//��ʾ��Ϣ�Ƿ��Ѿ���ʾ��
};

#define WARNINGLOGICRPTR    CWarningLogic::GetSingletonPtr()               //NetMngOptlogicָ��

//ϵͳ��Ϣ����
#define MESSAGEWND(p){ WARNINGLOGICRPTR->MessageBoxWnd(p ); }

#endif // !defined(UMSTOOL_WARNINGLOGIC_H)
