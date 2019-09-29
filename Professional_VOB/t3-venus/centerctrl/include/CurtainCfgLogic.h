// CurtainCfgLogic.h: interface for the CCurtainCfgLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CURTAINCFGLOGIC_H__5D0C4DC0_A18B_461B_B316_B04A49A4173C__INCLUDED_)
#define AFX_CURTAINCFGLOGIC_H__5D0C4DC0_A18B_461B_B316_B04A49A4173C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WndLogicBase.h"

class CCurtainCfgLogic : public CWndLogicBase 
{
public:
	virtual ~CCurtainCfgLogic();

	static CCurtainCfgLogic* GetLogicPtr();

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
	* 功能:  注册要处理的消息
	* @return  void
	* @remarks	 注册后该消息才能发送到本逻辑模块，否则，接收不到该消息
	*/
    virtual void RegMsg();

	/**	 
	* 功能:  注销某回调函数
	* @return  void
	* @remarks	 
	*/
	virtual void UnRegMsg();
	
    /**	 
	* 功能:  初始化窗口数据,
	* @return  void
	* @remarks	由于该功能被归属到控件属性并在xml中与控件绑定，
	                    需要在RegCBFun()中注册到回调函数管理模块 
	*/
    virtual bool InitWnd( const IArgs& args );
    
	/**	 
	* 功能:  清空所有状态和数据
	* @return    
	*/
    virtual void Clear(); 

protected:

    bool OnClickSwitchBtn1( const IArgs& args );
	bool OnClickBtnStop1( const IArgs& args );
	bool OnClickBtnUp1( const IArgs& args );
	bool OnClickBtnDown1( const IArgs& args );
	bool OnClickSwitchBtn2( const IArgs& args );
	bool OnClickBtnStop2( const IArgs& args );
	bool OnClickBtnUp2( const IArgs& args );
	bool OnClickBtnDown2( const IArgs& args );
	bool OnClickSwitchBtn3( const IArgs& args );
	bool OnClickBtnStop3( const IArgs& args );
	bool OnClickBtnUp3( const IArgs& args );
	bool OnClickBtnDown3( const IArgs& args );
	bool OnClickSwitchBtn4( const IArgs& args );
	bool OnClickBtnStop4( const IArgs& args );
	bool OnClickBtnUp4( const IArgs& args );
	bool OnClickBtnDown4( const IArgs& args );
	bool OnClickSwitchBtn5( const IArgs& args );
	bool OnClickBtnStop5( const IArgs& args );
	bool OnClickBtnUp5( const IArgs& args );
	bool OnClickBtnDown5( const IArgs& args );
	bool OnClickSwitchBtn6( const IArgs& args );
	bool OnClickBtnStop6( const IArgs& args );
	bool OnClickBtnUp6( const IArgs& args );
	bool OnClickBtnDown6( const IArgs& args );
	bool OnClickSwitchBtn( const IArgs& args );
	bool OnClickBtnStop( const IArgs& args );
	bool OnClickBtnUp( const IArgs& args );
	bool OnClickBtnDown( const IArgs& args );

protected:

	CCurtainCfgLogic();

	HRESULT OnCurtainStateNty( WPARAM wparam, LPARAM lparam );

    //操作按钮状态控制
	void BtnStateCtrl();

	//数组数据清除处理
	void DataClear();

	BOOL m_bCheck;  //是否有选中

private:

	static CCurtainCfgLogic *m_pLogic;

	static const String m_strSwitchBtn;

	static const String m_strSwitchBtn1;

	static const String m_strSwitchBtn2;

	static const String m_strSwitchBtn3;

	static const String m_strSwitchBtn4;

	static const String m_strSwitchBtn5;

	static const String m_strSwitchBtn6;

	BOOL m_bIsCheck[MAX_CURTAIN_NUM];

    u8 m_nCurNum;    //底层发过来的实际窗帘个数

};

#endif // !defined(AFX_CURTAINCFGLOGIC_H__5D0C4DC0_A18B_461B_B316_B04A49A4173C__INCLUDED_)
