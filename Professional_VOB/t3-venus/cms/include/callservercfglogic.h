/*****************************************************************************
模块名      : CCallServerCfgLogic
文件名      : callservercfglogic.h
相关文件    : 
文件实现功能: 呼叫服务器配置
作者        : 石城
版本        : V1.0  Copyright(C) 2013-2014 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/3/19      1.0         石城			创建
******************************************************************************/
#if !defined(UMC_CALLSERVERCFGLOGIC_H)
#define UMC_CALLSERVERCFGLOGIC_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CCallServerCfgLogic : public CWndLogicBase 
{
public:
	CCallServerCfgLogic();
	virtual ~CCallServerCfgLogic();
	static CCallServerCfgLogic* GetLogicPtr();
	
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

	/**	 
	* 功能:  点击系统设置
	* @return  bool
	* @remarks  
	*/
	bool OnSysCfg( const IArgs& args );
	
	bool IsAudioFormatChange();
		
	bool IsConfPollChange();
		
	bool IsConfDisChange();	
	
	bool IsDualCallRateChange();	
	
	bool IsCallRateChange();	
	
	bool IsDualVideoFomatChange();
	
	bool IsVideoFomatChange();

	/**	 
	* 功能:  点击编辑
	* @return  bool
	* @remarks  
	*/
	bool OnEdit( const IArgs& args );

	/**	 
	* 功能:  点击取消
	* @return  bool
	* @remarks  
	*/
	bool OnCancel( const IArgs& args );

	/**
	* 功能:  点击保存
	* @return  bool
	* @remarks  
	*/
	bool OnSave( const IArgs& args );

	bool OnCloseDlg( const IArgs & arg );

	bool OnBtnCallMode( const IArgs & arg );
	bool OnBtnCallShowMode( const IArgs & arg );
	bool OnBtnAudioMode( const IArgs & arg );

	LRESULT OnCallServiceInfoNty( WPARAM wParam, LPARAM lParam );
	LRESULT OnCallServerInfoInd( WPARAM wParam, LPARAM lParam );
	LRESULT OnModeChoose2CallServerModeNty( WPARAM wParam, LPARAM lParam );
	LRESULT OnShowModeChoose2CallServerModeNty( WPARAM wParam, LPARAM lParam );
	LRESULT OnAudioMode2CallSerNty( WPARAM wParam, LPARAM lParam );

	/** 功能:  根据服务器接收音频格式的反馈消息并更新界面
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	HRESULT OnUpdateAudioFormat( WPARAM wparam, LPARAM lparam );

	/** 功能:  根据服务器接收会议优选格式的反馈消息并更新界面
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	HRESULT OnUpdateVideoFormat( WPARAM wparam, LPARAM lparam );
						
	/** 功能:  根据服务器接收演示优选格式的反馈消息并更新界面
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	HRESULT OnUpdateDualVideoFormat( WPARAM wparam, LPARAM lparam );
						
	/** 功能:  根据服务器接收单屏码率的反馈消息并更新界面
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	HRESULT OnUpdateCallRate( WPARAM wparam, LPARAM lparam );
						
	/** 功能:  根据服务器接收演示码率的反馈消息并更新界面
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	HRESULT OnUpdateDualCallRate( WPARAM wparam, LPARAM lparam );
						
	/** 功能:  根据服务器接收会议讨论的反馈消息并更新界面
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	HRESULT OnUpdateConfDis( WPARAM wparam, LPARAM lparam );
						
	/** 功能:  根据服务器接收会议轮询的反馈消息并更新界面
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	HRESULT OnUpdateConfPoll( WPARAM wparam, LPARAM lparam );
					
	/**	 
	* 功能:  点击单屏码率减少按钮响应函数
	* @return  bool
	* @remarks  
	*/
	bool OnConfMinus( const IArgs& args );

	/**	 
	* 功能:  点击单屏码率添加按钮响应函数
	* @return  bool
	* @remarks  
	*/
	bool OnConfAdd( const IArgs& args );			
	
	//码率失去焦点后判断是否为64的倍数  利用WM_KILL_FOCUS消息
	bool OnConfRateNoFocus( const IArgs& args );
	
	bool OnShowRateNoFocus( const IArgs& args );

	bool RateIsDividedBy64();
	/**	 
	* 功能:  点击演示码率减少按钮响应函数
	* @return  bool
	* @remarks  
	*/
	bool OnShowMinus( const IArgs& args );

	/**	 
	* 功能:  点击演示码率添加按钮响应函数
	* @return  bool
	* @remarks  
	*/
	bool OnShowAdd( const IArgs& args );			

	/**	 
	* 功能:  点击轮询间隔减少按钮响应函数
	* @return  bool
	* @remarks  
	*/
	bool OnPollMinus( const IArgs& args );

	/**	 
	* 功能:  点击轮询间隔添加按钮响应函数
	* @return  bool
	* @remarks  
	*/
	bool OnPollAdd( const IArgs& args );			
											
	/** 功能:  会议轮询的按钮
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnBtnSwitchPolling( const IArgs& args );

	/**	 
	* 功能:  结束轮询长按按钮响应函数
	* @return  bool
	* @remarks  
	*/
	bool OnBtnHoldEnd( const IArgs& args );

	/**	 
	* 功能:  结束单屏码率长按按钮响应函数
	* @return  bool
	* @remarks  
	*/
	bool OnConfHoldEnd( const IArgs& args );

	/**	 
	* 功能:  结束演示码率长按按钮响应函数
	* @return  bool
	* @remarks  
	*/
	bool OnShowHoldEnd( const IArgs& args );
											
	/** 功能:  改变轮询时间控件时的响应函数
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnPollTimeChange( const IArgs& args );	
											
	/** 功能:  改变单屏码率控件时的响应函数
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnConfRateChange( const IArgs& args );	

	/** 功能:  改变演示码率控件时的响应函数
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnShowRateChange( const IArgs& args );	

	bool SaveConfRate();
	bool SaveShowRate();
	bool SaveVideoFormat();
	bool SaveDualVideoFormat();
	bool SaveConfDis();
	bool SaveConfPoll();
	bool SaveAudioFormat();
	
private:
	void SetCallServerMode();
	void SetCallServerShowMode();
	void SetAudioFormat();
private:
	static CCallServerCfgLogic *m_pLogic;
	TTPVidForamt m_tVidForamt;
	TTPVidForamt m_tDualVidForamt;
	EmTpAudioFormat m_emAudioFormat;
};

#endif // !defined(UMC_CALLSERVERCFGLOGIC_H)
