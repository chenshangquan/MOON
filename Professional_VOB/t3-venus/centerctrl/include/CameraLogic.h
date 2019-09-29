// CameraLogic.h: interface for the CCameraLogic class.
//
//////////////////////////////////////////////////////////////////////

/*****************************************************************************
模块名      : CCameraLogic
文件名      : CameraLogic.h
相关文件    : 
文件实现功能: 文档摄像机页面
作者        : 吴蒨蒨
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/1/7       1.0         吴蒨蒨			创建
******************************************************************************/
#if !defined(AFX_CAMERALOGIC_H__8B953119_C5EB_4FA6_908B_99481064F20A__INCLUDED_)
#define AFX_CAMERALOGIC_H__8B953119_C5EB_4FA6_908B_99481064F20A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WndLogicBase.h"

class CCameraLogic : public CWndLogicBase   
{
public:
	virtual ~CCameraLogic();

	static CCameraLogic* GetLogicPtr();

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

    bool OnBtnOpenCameraSwitch( const IArgs& args );

	/**	 
	* 功能:  点击预置位1的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnClickOrderPosition1( const IArgs& args );

	/**	 
	* 功能:  点击预置位2的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnClickOrderPosition2( const IArgs& args );

	/**	 
	* 功能:  点击预置位3的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnClickOrderPosition3( const IArgs& args );


    bool OnBeginReduce( const IArgs& args );
    bool OnBeginEnlarge( const IArgs& args );

    bool OnBtnReduce( const IArgs& args );

    bool OnBtnEnlarge( const IArgs& args );

    bool OnBtnFocus( const IArgs& args );

    bool OnBtnWhiteBalance( const IArgs& args );

    bool OnBtnSave( const IArgs& args );
	
	
protected:
    CCameraLogic();
	
	HRESULT OnDCamStateNty( WPARAM wparam, LPARAM lparam );
    HRESULT OnDCamPowerInd( WPARAM wparam, LPARAM lparam );

private:
	static CCameraLogic *m_pLogic;

    EmDCamRecallNum     m_emRecallNum;  //当前预置位


	static const String m_strBtnOpenCameraSwitch;
    static const String m_strBtnReduce;
    static const String m_strBtnEnlarge;
};

#endif // !defined(AFX_CAMERALOGIC_H__8B953119_C5EB_4FA6_908B_99481064F20A__INCLUDED_)
