/*****************************************************************************
ģ����      : CCorrelativeCfgLogic
�ļ���      : correlativecfglogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: logic�������ҳ��
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/12/07     1.0         ����ӡ      ����
******************************************************************************/
#if !defined(AFX_CORRELATIVECFGLOGIC_H__48C10C74_39FD_4237_B8A0_129393B3BBD1__INCLUDED_)
#define AFX_CORRELATIVECFGLOGIC_H__48C10C74_39FD_4237_B8A0_129393B3BBD1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CCorrelativeCfgLogic :public CWndLogicBase, public ISingleTon<CCorrelativeCfgLogic>  
{
public:  
    CCorrelativeCfgLogic();
	virtual ~CCorrelativeCfgLogic();

public:  
	virtual bool RegCBFun();
	virtual bool UnRegFunc( );
    virtual bool InitWnd( const IArgs & arg );

	/**	 
	* ����:  ��ʾ�����ش���
	* @return  bool ��ʾ�Ƿ����ʾ
	* @remarks
	*/
	virtual bool ShowWindow( BOOL32 bShow );

   /**	 
	* ����:  �������״̬������
	* @return   
	* @remarks	 
	*/
    virtual void Clear();

	void InitCfgFuncMenu();			//��ʼ�����ò˵�

	/**	 
	* ����:  �л�����
	* @return   void
	* Param : [in] strItemName ������ʾ������
	*/
	void SwitchConfigTabWnd(CString strItemName);

public:
	bool OnMenuLstItem( const IArgs & arg );

protected: 
	virtual void RegMsg(); 
	virtual void UnRegMsg();

	
private:
	//�л������б�ؼ���
	const String m_strLstCfgFunMenu;

	//��ǰ��ʾ������ҳ��
	CString m_strCurPage;
};

#define CORRELATIVECFGLOGICRPTR    CCorrelativeCfgLogic::GetSingletonPtr()               //����logicָ��

#endif // !defined(AFX_CORRELATIVECFGLOGIC_H__48C10C74_39FD_4237_B8A0_129393B3BBD1__INCLUDED_)
