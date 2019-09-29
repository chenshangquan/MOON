/*****************************************************************************
ģ����      : CCallServerCfgmodechooseLogic
�ļ���      : CCallServerCfgmodechooseLogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: ���з��������û����ʽѡ��
����        : ʯ��
�汾        : V1.0  Copyright(C) 2013-2014 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/3/19      1.0         ʯ��			����
******************************************************************************/
#if !defined(UMC_CALLSERVERCFGMODECHOOSELOGIC_H)
#define UMC_CALLSERVERCFGMODECHOOSELOGIC_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"


class CCallServerCfgModeChooseLogic : public CWndLogicBase 
{
public:
	CCallServerCfgModeChooseLogic();
	virtual ~CCallServerCfgModeChooseLogic();
	static CCallServerCfgModeChooseLogic* GetLogicPtr();
	
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

	bool OnBtnBack( const IArgs & args );

	bool OnSelectH264HP( const IArgs & args );

	bool OnSelectH264BP( const IArgs & args );

	bool OnNoSelect4CIF( const IArgs & args );
	
	bool OnSelect4CIF( const IArgs & args );

	LRESULT OnCallService2ModeChooseModeNty( WPARAM wParam, LPARAM lParam );
	

private:
	static CCallServerCfgModeChooseLogic *m_pLogic;
	TTPVidForamt m_tVidForamt;
};

#endif // !defined(UMC_CALLSERVERCFGMODECHOOSELOGIC_H)
