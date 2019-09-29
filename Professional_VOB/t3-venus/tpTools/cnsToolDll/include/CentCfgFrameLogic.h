// CentCfgFrameLogic.h: interface for the CCentCfgFrameLogic class.
//
//////////////////////////////////////////////////////////////////////
/*****************************************************************************
 模块名      : cnsTool配置框架
 文件名      : CentCfgFrameLogic.h
 相关文件    : 
 文件实现功能:  
 说明        : 中控配置界面中:环境灯光、摄像机、新风由于界面过于简单将消息响应放在CCentCfgFrameLogic中
			   后续这3个配置项若添加重大更新版本,则各自添加新类来处理
 作者        : 景洋洋
 版本        : 
 -----------------------------------------------------------------------------
 修改记录:
 日  期         版本        修改人      修改内容
 2014/05/12     1.0                       创建
******************************************************************************/

#if !defined(AFX_CENTCFGFRAMELOGIC_H__F0748436_1FCC_4573_842C_9AF1991CD365__INCLUDED_)
#define AFX_CENTCFGFRAMELOGIC_H__F0748436_1FCC_4573_842C_9AF1991CD365__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CCentCfgFrameLogic : public CLogicBase, public ISingleTon<CCentCfgFrameLogic>   
{
public:
	CCentCfgFrameLogic();
	virtual ~CCentCfgFrameLogic();

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
	/** 功能:  隐藏所有窗口
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void HideAllWnd();
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
	/** 功能:  初始化配置菜单
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void InitCfgFuncMenu();	

	/** 功能:  点击cns配置按钮的响应事件
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnClickXinFengCfg( const IArgs& args );

	/** 功能:  点击音频配置配置按钮的响应事件
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnClickCameraCfg( const IArgs& args );

	/** 功能:  点击网管配置按钮的响应事件
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnClickLightCfg( const IArgs& args );

	/** 功能:  点击混音配置按钮的响应事件
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnClickDisplayCfg( const IArgs& args );

	/** 功能:  Table页切换窗口
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void SwitchCfgTabWnd( string strWnd );
	
	/** 功能:  接收服务器端发过来的消息然后更新摄像机状态
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnCameraInfoNty( WPARAM wParam, LPARAM lParam );
	
	/** 功能:  将摄像机的开关状态转换为string类型
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	String CamStateToString( EmCamPowerMode& emSwitchState );

	/** 功能:  接收服务器端发过来的消息然后更新文档摄像机状态
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnDocCamInfoNty( WPARAM wParam, LPARAM lParam );

	/** 功能:  接收服务器端发过来的消息然后更新空调状态
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnAirInfoNty( WPARAM wParam, LPARAM lParam );

	/** 功能:  接收服务器端发过来的消息然后更新新风状态
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnXinFengInfoNty( WPARAM wParam, LPARAM lParam );

	/** 功能:  接收服务器端发过来的消息然后更新灯光状态
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnLightInfoNty( WPARAM wParam, LPARAM lParam );

	/** 功能:  接收服务器端发过来的待机消息然后注销回到登陆界面
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnCentSleepNty( WPARAM wParam, LPARAM lParam );

public:
	string m_strCfgCurWnd;//当前显示的窗口
private:
	string m_strLstFunMenu;//功能列表 

};

#endif // !defined(AFX_CENTCFGFRAMELOGIC_H__F0748436_1FCC_4573_842C_9AF1991CD365__INCLUDED_)
