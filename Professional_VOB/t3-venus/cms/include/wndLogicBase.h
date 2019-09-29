   
/*****************************************************************************
模块名      : CMS控制台
文件名      : wndLogicBase.h
相关文件    : 
文件实现功能: 逻辑管理基类
作者        : 俞锦锦
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2011/5/24  1.0          俞锦锦      创建
******************************************************************************/

#if !defined(AFX_WNDLOGIC_H__A66AA693_6ED0_4B3C_977E_1EC92248A074__INCLUDED_)
#define AFX_WNDLOGIC_H__A66AA693_6ED0_4B3C_977E_1EC92248A074__INCLUDED_

#pragma warning (disable: 4503)

#include "commoninterface.h" 
#include "UIDataMgr.h" 
#include "uiManage.h"
#include "processMsgBase.h"
#include "MfcDefaultArgs.h" 
#include "errCodeManage.h"

#include "TouchListProperty.h"
#include "PropertyHelp.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CWndLogicBase
{ 
public: 
   
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
//	virtual void UnRegFunc( u32 dwMsgID ); 


	 /**	 
	* 功能:  注销某回调函数
	* @return  void
	* @remarks	 
	*/
	 virtual bool UnRegFunc(){ return true;}

	/**	 
	* 功能:  初始化窗口数据,
	* @return  void
	* @remarks	由于该功能被归属到控件属性并在xml中与控件绑定，
	                    需要在RegCBFun（）中注册到回调函数管理模块 
	*/
	 virtual bool InitWnd(  const IArgs  & arg ) { 
		 Args_WindowTree argTree =* dynamic_cast< Args_WindowTree *>( const_cast<IArgs*>( &arg ));
		 m_pWndTree = argTree.m_piTree; 
		 return true;
	 }

     //显示窗口时有的状态需要初始化,此处应为纯虚函数，每个logic都应强制实现，外部显示对应界面时统一调用此处的showwindow
     virtual bool ShowWindow( BOOL32 bShow ){ return true; } 
  

	 bool IsAllE164Number( String strText );
	 
	 bool IsValidTPStr( String strText );
    
     IWndTree * GetWndTree(){ return m_pWndTree; }

protected:
   
   /**	 
	* 功能:  注册要处理的消息
	* @return  void
	* @remarks	 注册后该消息才能发送到本逻辑模块，否则，接收不到该消息
	*/
    virtual void RegMsg(){};

	virtual void UnRegMsg(){};
  
public:
	CWndLogicBase()
    {   
        m_pWndTree = NULL;
	  	RegMsg();  
	}
	
	virtual ~CWndLogicBase(){}

protected:
	IWndTree * m_pWndTree; 
     
};

 

#endif // !defined(AFX_WNDLOGIC_H__A66AA693_6ED0_4B3C_977E_1EC92248A074__INCLUDED_)
