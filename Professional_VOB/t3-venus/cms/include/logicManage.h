 
/*****************************************************************************
ģ����      : CMS����̨
�ļ���      : logicManage.h
����ļ�    : 
�ļ�ʵ�ֹ���: logic���� 
����        : �����
�汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2011/5/24  1.0          �����      ����
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
	* ����:  ��ȡ����ָ��
	* @return    CLogicManageָ��
	* @remarks	   
	*/ 
   static CLogicManage *GetLogicManagePtr();
   
    /**	 
	* ����:  ��������logic 
	* @return   
	* @remarks	   
	*/ 
   void CreateLogic();

   /**	 
	* ����:  ���� logic 
	* @param [in]  pLogic Ҫ���ٵ�logicָ��
	* @return   
	* @remarks	   
	*/ 
   void DestroyLogic( CWndLogicBase *pLogic );

   	/**	 
	* ����:  ��������logic 
	* @return   
	* @remarks	   
	*/ 
   void DestroyLogic();


   void OnNotify( WPARAM wparam ,LPARAM lparam );

   void GetLogic( CConfCnsLstLogic **pLogic );
  /**	 
	* ����:  ��ȡlogic�б�
	* @return   
	* @remarks	   
	*/ 
   const  TplArray<CWndLogicBase*>* GetLogicList() const;

   	HRESULT OnDisConnect( WPARAM wparam, LPARAM lparam );
private:
    CLogicManage();
  
	TplArray<CWndLogicBase*> m_tplLogicList; //<logic�б�
    static CLogicManage *m_pLogicManage;
};

#define LogicManagePtr  CLogicManage::GetLogicManagePtr()
#endif // !defined(AFX_LOGICMANAGE_H__24865BD6_4753_4C5F_9854_280C1F1F7DB0__INCLUDED_)
