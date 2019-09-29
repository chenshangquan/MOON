 
/*****************************************************************************
模块名      : CMS控制台
文件名      : logicManage.h
相关文件    : 
文件实现功能: logic管理 
作者        : 俞锦锦
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2011/5/24  1.0          俞锦锦      创建
******************************************************************************/

#if !defined(AFX_LOGICMANAGE_H__24865BD6_4753_4C5F_9854_280C1F1F7DB0__INCLUDED_)
#define AFX_LOGICMANAGE_H__24865BD6_4753_4C5F_9854_280C1F1F7DB0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndlogicbase.h"
#include "confCnsLstLogic.h"
#include "msgBoxLogic.h"
#include "loginLogic.h"
#include "mainFrameLogic.h"
#include "toolMenuLogic.h" 
#include "conftempLstLogic.h"
#include "lockScreenLogic.h"
#include "audmixLogic.h"
#include "confCtrlLogic.h"
#include "addrbooklogic.h"
#include "addreditlogic.h"
//#include "ConftempEdtLogic.h"
#include "confInfoLogic.h"
#include "simulateCnsLogic.h"
#include "volumCtrlLogic.h"
#include "syscfglogic.h"
#include "ethnetcfglogic.h"
#include "cnscfglogic.h"
#include "regservicelogic.h"
#include "userManageLogic.h"
#include "userDefinedLogic.h"
#include "tvwLogic.h"
#include "titleBarLogic.h"
#include "callingLogic.h"
#include "alarminfologic.h"
//#include "IpCfgLogic.h"
#include "mainmenulogic.h"
#include "connectcnslogic.h"
#include "VideoLogic.h"
#include "scrnDisplayMenuLogic.h"
#include "regGklogic.h"
#include "timeSetLogic.h"
#include "SaveLogLogic.h"
#include "WaitingRefreshLogic.h"
#include "dualSrcLogic.h"
#include "dualSrcManageLogic.h"

class CLogicManage  
{
public: 
	virtual ~CLogicManage();
    
public:
	 /**	 
	* 功能:  获取单例指针
	* @return    CLogicManage指针
	* @remarks	   
	*/ 
   static CLogicManage *GetLogicManagePtr();
   
    /**	 
	* 功能:  创建所有logic 
	* @return   
	* @remarks	   
	*/ 
   void CreateLogic();

   /**	 
	* 功能:  销毁 logic 
	* @param [in]  pLogic 要销毁的logic指针
	* @return   
	* @remarks	   
	*/ 
   void DestroyLogic( CWndLogicBase *pLogic );

   	/**	 
	* 功能:  销毁所有logic 
	* @return   
	* @remarks	   
	*/ 
   void DestroyLogic();


   void OnNotify( WPARAM wparam ,LPARAM lparam );

   void GetLogic( CConfCnsLstLogic **pLogic );
  /**	 
	* 功能:  获取logic列表
	* @return   
	* @remarks	   
	*/ 
   const  TplArray<CWndLogicBase*>* GetLogicList() const;

   	HRESULT OnDisConnect( WPARAM wparam, LPARAM lparam );
private:
    CLogicManage();
  
	TplArray<CWndLogicBase*> m_tplLogicList; //<logic列表
    static CLogicManage *m_pLogicManage;
};

#define LogicManagePtr  CLogicManage::GetLogicManagePtr()
#endif // !defined(AFX_LOGICMANAGE_H__24865BD6_4753_4C5F_9854_280C1F1F7DB0__INCLUDED_)
