/*****************************************************************************
模块名      : CCallServerCfgshowmodechooseLogic
文件名      : CCallServerCfgshowmodechooseLogic.h
相关文件    : 
文件实现功能: 呼叫服务器配置演示格式选择
作者        : 石城
版本        : V1.0  Copyright(C) 2013-2014 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/3/19      1.0         石城			创建
******************************************************************************/
#if !defined(UMC_CALLSERVERCFGSHOWMODECHOOSELOGIC_H)
#define UMC_CALLSERVERCFGSHOWMODECHOOSELOGIC_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"


class CCallServerCfgShowModeChooseLogic : public CWndLogicBase 
{
public:
	CCallServerCfgShowModeChooseLogic();
	virtual ~CCallServerCfgShowModeChooseLogic();
	static CCallServerCfgShowModeChooseLogic* GetLogicPtr();
	
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
	
	bool On1080and720P( const IArgs & args );
	
	bool OnSelect4CIF( const IArgs & args );
	
	bool OnSelectXGA( const IArgs & args );
	
	bool OnSelectSXGA( const IArgs & args );
	
	bool OnSelectWXGA( const IArgs & args );
	
	bool OnSelectUXGA( const IArgs & args );
	
	LRESULT OnCallService2ShowModeChooseModeNty( WPARAM wParam, LPARAM lParam );
	

private:
	static CCallServerCfgShowModeChooseLogic *m_pLogic;
	TTPVidForamt m_tVidForamt;
};

#endif // !defined(UMC_CALLSERVERCFGSHOWMODECHOOSELOGIC_H)
