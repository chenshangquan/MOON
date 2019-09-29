/*****************************************************************************
模块名      : CCallServerCfgmodechooseLogic
文件名      : CCallServerCfgmodechooseLogic.h
相关文件    : 
文件实现功能: 呼叫服务器配置会议格式选择
作者        : 石城
版本        : V1.0  Copyright(C) 2013-2014 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/3/19      1.0         石城			创建
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
	* 功能:  清空所有状态和数据
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
