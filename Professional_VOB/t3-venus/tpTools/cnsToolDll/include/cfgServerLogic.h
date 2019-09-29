// cfgServerLogic.h: interface for the CCfgServerLogic class.
//
//////////////////////////////////////////////////////////////////////
/*****************************************************************************
文件名      : CfgServerLogic.h
相关文件    : 
文件实现功能: 相关配置中的均衡器配置界面
作者        : 景洋洋
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/02/20     1.0         景洋洋      创建
******************************************************************************/
#if !defined(AFX_CFGSERVERLOGIC_H__B06B345C_CF30_42B5_9B64_5F72C61D6269__INCLUDED_)
#define AFX_CFGSERVERLOGIC_H__B06B345C_CF30_42B5_9B64_5F72C61D6269__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CCfgServerLogic : public CLogicBase, public ISingleTon<CCfgServerLogic> 
{
public:
	CCfgServerLogic();
	virtual ~CCfgServerLogic();
	
	//CLogicBase
public:	 
	/** 功能:  注册回调函数
	*  @param[in] 
	*  @return 
	*  @remarks  在读取xml文件时候,会调用其中注册的函数
	*/
	virtual void RegCBFun();

	/** 功能:  反注册回调函数
	*  @param[in] 
	*  @return 
	*  @remarks  与上面函数相反,注销注册的函数
	*/
	virtual void UnRegFunc( );

	/** 功能:  初始化窗口
	*  @param[in] 
	*  @return 
	*  @remarks  在读取xml文件时候调用,根据里面的内容初始化窗口
	*/	
    virtual bool InitWnd( const IArgs & arg ); 

	/** 功能:  清理窗口
	*  @param[in] 
	*  @return 
	*  @remarks  在窗口关闭的时候调用,清空窗口数据
	*/
    virtual void Clear() ;

	/** 功能:  判断cns配置页面的消息是否改变
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	bool IsCfgSerChange();

	/**	 
	* 功能: 获取界面上数据变化控件的数目
	* @return   bool
	* @remarks  
	*/
	s32 GetCtrlChangeNum() { return m_vctWndName.size(); }
protected:	
	/** 功能: 注册消息,接收来自lib库中发送来的消息
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/	
	virtual void RegMsg(); 
		
	/** 功能: 反注册消息,与上面函数相反,注销注册的消息
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/	
	virtual void UnRegMsg();
private:	
	/** 功能:  保存配置的按钮
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnBtnSave( const IArgs& args );

	/** 功能:  还原配置的按钮
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnCancel( const IArgs& args );

	/** 功能:  开启GK设置的按钮
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	bool OnBtnSwitchGK( const IArgs& args );

	/** 功能:  接收服务器端发过来的消息然后更新GK状态
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnUpdateGkNty( WPARAM wParam, LPARAM lParam );

	/** 功能:  接收服务器端发过来的消息然后更新SIP信息
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnUpdateSipNty( WPARAM wParam, LPARAM lParam );

	/** 功能:  接收服务器端发过来的注册SIP重名消息
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnRegSIPAliasRepeatNty( WPARAM wParam, LPARAM lParam );

	/** 功能:  接收服务器端发过来的注册SIP的结果
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnRegSIPResultNty( WPARAM wParam, LPARAM lParam );

	/** 功能:  接收服务器端发过来的注册GK的结果
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnRegGKRsp( WPARAM wParam, LPARAM lParam );

	/** 功能:  接收服务器端发过来的呼叫服务器的通知
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnCallSerNty( WPARAM wParam, LPARAM lParam );

	/** 功能:  接收服务器端发过来的呼叫服务器的回复
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnCallSerInd( WPARAM wParam, LPARAM lParam );

	/** 功能:  接收服务器端发过来的呼叫服务器的通知
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnUpgradeSerNty( WPARAM wParam, LPARAM lParam );

	/** 功能:  接收服务器端发过来的呼叫服务器的回复
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnUpgradeSerInd( WPARAM wParam, LPARAM lParam );

	/** 功能:  保存注册网呈服务器部分	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	bool SaveSip();

	/** 功能:  保存GK设置
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveGk();

	/** 功能:  保存呼叫服务器设置
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveCallSer();

	/** 功能:  保存升级服务器地址
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveUpgradeSer();

	/** 功能:  保存配置时聚焦在出错的窗口	
	*  @param[in] strWindow   窗口名称
	*  @return 
	*  @remarks   
	*/	
	void FocusWindow(String strWindow);	

	/** 功能:  切换到其他界面时提醒是否保存的窗口	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveMsgBox();
	
	/** 功能:  改变注册服务器控件时的响应函数	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnChangedSIp( const IArgs& args );	
	
	/** 功能:  改变GK服务器控件时的响应函数	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnChangedGKIp( const IArgs& args );	
			
	/** 功能:  改变呼叫服务器控件时的响应函数	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnChangedCallSerIp( const IArgs& args );	
					
	/** 功能:  改变升级服务器控件时的响应函数	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnChangedUpSerIp( const IArgs& args );	

	/** 功能:  设置GK地址
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/	
	void SetGKData();
														
	/** 功能:  设置Sip地址
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	void SetSipData();
															
	/** 功能:  设置呼叫服务器地址和会议、演示格式
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	void SetCallSerData();
																
	/** 功能:  设置升级服务器地址
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	void SetUpgradeSerData();

	/** 功能:  收到会议状态的信息
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	LRESULT OnConfStateNty( WPARAM wparam, LPARAM lparam);

	/** 功能:  转换edit框里的ip地址为dw格式	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	DWORD StrToDWIp( String strName );
											
private:

	const String m_strEdtSIp;					//网呈服务器地址
	const String m_strBtnGKSwitch;				//GK开关
	const String m_strEdtGKIP;					//GK地址
	const String m_strEdtCSIP;					//呼叫服务器地址
	const String m_strEdtUGIP;					//升级服务器地址

};

#endif // !defined(AFX_CFGSERVERLOGIC_H__B06B345C_CF30_42B5_9B64_5F72C61D6269__INCLUDED_)
