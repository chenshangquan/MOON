// centCtrlLogic.h: interface for the CCentCtrlLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CENTCTRLLOGIC_H__777D44E7_A11A_4507_AA4E_F26B05745548__INCLUDED_)
#define AFX_CENTCTRLLOGIC_H__777D44E7_A11A_4507_AA4E_F26B05745548__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CCentCtrlLogic : public CLogicBase, public ISingleTon<CCentCtrlLogic>    
{
public:
	CCentCtrlLogic();
	virtual ~CCentCtrlLogic();

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
	virtual void UnRegFunc();
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
    virtual void Clear();

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

	/** 功能:  接收服务器端发过来的消息然后更新显示器状态
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnDisplayInfoNty( WPARAM wParam, LPARAM lParam );

	/** 功能:  接收服务器端发过来的消息然后更新摄像机状态
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnCameraInfoNty( WPARAM wParam, LPARAM lParam );

	/** 功能:  接收服务器端发过来的消息然后更新文档摄像机状态
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnDocCamInfoNty( WPARAM wParam, LPARAM lParam );

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

	/** 功能:  将显示器的开关状态转换为string类型
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	String StateToString( EmTvPowerMode& emSwitchState );

	/** 功能:  将摄像机的开关状态转换为string类型
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	String CamStateToString( EmCamPowerMode& emSwitchState );
private:
	const String m_strAirInfo;							//空调
	const String m_strXinFengInfo;						//新风
	const String m_strDisPlay1Info;						//显示器一
	const String m_strDisPlay2Info;						//显示器二
	const String m_strDisPlay3Info;						//显示器三
	const String m_strCamera1Info;						//摄像机一
	const String m_strCamera2Info;						//摄像机二
	const String m_strCamera3Info;						//摄像机三
	const String m_strDocCameraInfo;					//文档摄像机

};

#endif // !defined(AFX_CENTCTRLLOGIC_H__777D44E7_A11A_4507_AA4E_F26B05745548__INCLUDED_)
