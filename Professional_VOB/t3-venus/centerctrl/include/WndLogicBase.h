// WndLogicBase.h: interface for the CWndLogicBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WNDLOGICBASE_H__C7EF446E_24BE_46AF_9307_4206EE6A8EAA__INCLUDED_)
#define AFX_WNDLOGICBASE_H__C7EF446E_24BE_46AF_9307_4206EE6A8EAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

const String g_stcStrCenterCtrlDlg = "CenterCtrlDlg";
const String g_stcStrMainMenuDlg = "MainMenuDlg"; 
const String g_stcStrAirConditionDlg = "AirConditionDlg";
const String g_stcStrCameraDlg = "CameraDlg"; 
const String g_stcStrMonitorDlg = "MonitorDlg";
const String g_stcStrTouchPadDlg = "TouchPadDlg"; 
const String g_stcStrWaitingDlg = "WaitingDlg";
const String g_stcStrCurtainCfgDlg = "CurtainCfgDlg";
const String g_stcStrBtnCurtainCfg = "MainMenuDlg/BtnCurtainCfg";

class CWndLogicBase  
{
public:
    CWndLogicBase();   
	virtual ~CWndLogicBase();

	/**	 
	* 功能:  初始化
	* @return   
	* @remarks	 
	*/
	void InitLogic()
	{    
		RegCBFun();
        RegMsg();
	};

    /**	 
	* 功能:  清空所有状态和数据
	* @return   
	* @remarks	 
	*/
    virtual void Clear() = 0;

	/**	 
	* 功能:  注册该logic中所有的回调函数
	* @return  void
	* @remarks	在此注册的回调函数主要是控件的响应事件，多为成员回调函数,也可注册其他的回调函数
	                    注册时，应注意回调函数对应名子的命名规则：“类名::函数名”
	*/
	virtual bool RegCBFun(){ return true; }

    /**	 
	* 功能:  注销某回调函数
	* @return  void
	* @remarks	 
	*/
	virtual bool UnRegFunc(){ return true; }

    	/**	 
	* 功能:  初始化窗口数据,
	* @return  void
	* @remarks	由于该功能被归属到控件属性并在xml中与控件绑定，
	                    需要在RegCBFun（）中注册到回调函数管理模块 
	*/
	 virtual bool InitWnd(  const IArgs  & arg ) 
     { 
		 Args_WindowTree argTree = *dynamic_cast< Args_WindowTree *>( const_cast<IArgs*>( &arg ));
		 m_pWndTree = argTree.m_piTree; 
		 return true;
	 }
    
     IWndTree * GetWndTree(){ return m_pWndTree; }

protected: 
   /**	 
	* 功能:  注册要处理的消息
	* @return  void
	* @remarks	 注册后该消息才能发送到本逻辑模块，否则，接收不到该消息
	*/
    virtual void RegMsg(){};

	virtual void UnRegMsg(){};

protected:
	IWndTree * m_pWndTree; 
};

#endif // !defined(AFX_WNDLOGICBASE_H__C7EF446E_24BE_46AF_9307_4206EE6A8EAA__INCLUDED_)
