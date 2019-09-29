// SysStandByLogic.h: interface for the CSysStandByLogic class.
//
//////////////////////////////////////////////////////////////////////

/*****************************************************************************
模块名      : CSysStandByLogic
文件名      : SysStandByLogic.h
相关文件    : 
文件实现功能: 系统待机设置页面
作者        : 吴蒨蒨
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/12/5      1.0         吴蒨蒨		创建
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
	* 功能:  注册该logic中所有的回调函数
	* @return  void
	* @remarks	在此注册的回调函数主要是控件的响应事件，多为成员回调函数,也可注册其他的回调函数
	                    注册时，应注意回调函数对应名子的命名规则：“类名::函数名”
	*/
	virtual bool RegCBFun();

	/**	 
	* 功能:  注销某回调函数
	* @return  void
	* @remarks	 
	*/
	virtual bool UnRegFunc();

	/**	 
	* 功能：更新系统待机界面
	* @return  bool
	* @remarks	 
	*/

	virtual bool UpdateDlg();

	/**	 
	* 功能：注册消息函数
	* @return  void
	* @remarks	 注册后该消息才能发送到本逻辑模块，否则，接收不到该消息
	*/
	virtual void RegMsg();

    /**	 
	* 功能:  清空所有状态和数据
	* @return   
	* @remarks	 
	*/
    virtual void Clear();

protected:
	/**	 
	* 功能:  初始化窗口数据,
	* @return  void
	* @remarks	由于该功能被归属到控件属性并在xml中与控件绑定，
	                    需要在RegCBFun()中注册到回调函数管理模块 
	*/
	bool InitWnd( const IArgs & args );

	/**
	* 功能:  点击保存
	* @return  bool
	* @remarks  
	*/
	bool OnSave( const IArgs& args );

	/**	 
	* 功能:  点击取消
	* @return  bool
	* @remarks  
	*/
	bool OnCancel( const IArgs& args );

	/**	 
	* 功能:  点击编辑
	* @return  bool
	* @remarks  
	*/
	bool OnEdit( const IArgs& args );

// 	/**	 
// 	* 功能:  点击系统待机设置按钮
// 	* @return  bool
// 	* @remarks  
// 	*/
//     bool BtnSysStandByClick( const IArgs& args );

	/**	 
	* 功能:  点击系统设置按钮
	* @return  bool
	* @remarks  
	*/
	bool OnSysCfg( const IArgs& args );

	/**	 
	* 功能:  点击减少按钮响应函数
	* @return  bool
	* @remarks  
	*/
	bool OnPlus( const IArgs& args );

	/**	 
	* 功能:  点击添加按钮响应函数
	* @return  bool
	* @remarks  
	*/
	bool OnAdd( const IArgs& args );
	/**	 
	* 功能:  结束长按按钮响应函数
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
	BOOL           m_bOpen;  //是否开启系统待机

};

#endif // !defined(AFX_SYSSTANDBYLOGIC_H__92DF6A8B_CB04_458B_A3C6_D1CAA7A383FF__INCLUDED_)
