/*****************************************************************************
ģ����      : CMainFrameLogic
�ļ���      : mainFrameLogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: logic������
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/12/04     1.0         ����ӡ      ����
******************************************************************************/
#if !defined(AFX_MAINWNDLOGIC_H__336C3B31_4484_4F36_9B80_1BA09DB004FA__INCLUDED_)
#define AFX_MAINWNDLOGIC_H__336C3B31_4484_4F36_9B80_1BA09DB004FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CMainFrameLogic :public CWndLogicBase, public ISingleTon<CMainFrameLogic> 
{
public:   
     CMainFrameLogic();
	 virtual ~CMainFrameLogic();  

public:  
	virtual bool RegCBFun();
	virtual bool UnRegFunc( );
    virtual bool InitWnd( const IArgs & arg );
   
	/**	 
	* ����:  �������״̬������
	* @return   
	* @remarks	 
	*/
    virtual void Clear() ;

protected:
	/**	 
	* ����: ����������־
	* @return   bool
	* @remarks  
	*/
	bool OnBtnDownloadLog( const IArgs & arg );

	/**	 
	* ����: ����������
	* @return   bool
	* @remarks  
	*/
	bool OnBtnRebootUms( const IArgs & arg );

	/**	 
	* ����: ע����¼
	* @return   bool
	* @remarks  
	*/
	bool OnBtnLogoff( const IArgs & arg );

	/**	 
	* ����: ��С��
	* @return   bool
	* @remarks  
	*/
	bool OnBtnMinimize( const IArgs & arg );

	/**	 
	* ����: �ر�
	* @return   bool
	* @remarks  
	*/
	bool OnBtnClose( const IArgs & arg );

	/**	 
	* ����: ��Ӧtabҳ�б���
	* @return   bool
	* @remarks  
	*/
	bool OnMenuLstItem( const IArgs & arg );

	/**	 
	* ����: ��ʼ�������б�ҳ��
	* @return   bool
	* @remarks  
	*/
	void InitFunMenu();
	

protected:
	virtual void RegMsg(); 
	virtual void UnRegMsg();

	/**	 
	* ����: ��½��Ӧ
	* @return   bool
	* @remarks  
	*/
	HRESULT OnLoginRsp( WPARAM wparam, LPARAM lparam);

	/**	 
	* ����: ��½��ʱ
	* @return   bool
	* @remarks  
	*/
	HRESULT OnLoginTimeOut( WPARAM wparam, LPARAM lparam);

private:
   void  CreateWnd();

  	/**	 
	* ����: �л�����ҳ��
	* @return   bool
	* @remarks  
	*/
	void SwitchTabWnd(CString strItemName);

private:
	Window* m_pWndMain;
	const String m_strDlgMain;
	const String m_strLstFunMenu;
	const String m_strStcUmsIP;

	//��ǰ������ʾ��ҳ��
	CString m_strCurPage;
};

#define MAINFRMLOGICRPTR    CMainFrameLogic::GetSingletonPtr()               //��logicָ��

#endif // !defined(AFX_MAINWNDLOGIC_H__336C3B31_4484_4F36_9B80_1BA09DB004FA__INCLUDED_)
