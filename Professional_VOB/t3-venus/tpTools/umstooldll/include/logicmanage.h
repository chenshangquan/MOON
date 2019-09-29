/*****************************************************************************
ģ����      : CLogicManage
�ļ���      : logicmanage.h
����ļ�    : 
�ļ�ʵ�ֹ���: logic������
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/12/04     1.0         ����ӡ      ����
******************************************************************************/
#if !defined(AFX_LOGICMANAGE_H__12E93E38_C38D_47CB_897A_CCE0522BEDD8__INCLUDED_)
#define AFX_LOGICMANAGE_H__12E93E38_C38D_47CB_897A_CCE0522BEDD8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndlogicbase.h"
#include "mainFrameLogic.h"
#include "sysinfologic.h"
#include "correlativecfglogic.h"
#include "addrbookexplogic.h"
#include "templateexplogic.h"
#include "boardcfglogic.h"
#include "umscfglogic.h"
#include "boardoptdlglogic.h"
#include "msgboxdlglogic.h"
#include "tvwboardcfglogic.h"
#include "netmngcfglogic.h"
#include "netmngoptdlglogic.h"
#include "tvwstylecfglogic.h"
#include "tvwstyleoptdlglogic.h"
#include "impcommondlglogic.h"
#include "expcommondlglogic.h"
#include "vtrcfglogic.h"
#include "vtroptdlglogic.h"
#include "warninglogic.h"
#include "backupcfglogic.h"

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



protected:
   void OnNotify( WPARAM wparam ,LPARAM lparam );

  /**	 
	* ����:  ��ȡlogic�б�
	* @return   
	* @remarks	   
	*/ 
   const  TplArray<CWndLogicBase*>* GetLogicList() const;

  /**	 
	* ����:  ����������
	* @return   
	* @remarks	   
	*/ 
   HRESULT OnDisConnect( WPARAM wparam, LPARAM lparam );

  /**	 
	* ����:  ��������ռ
	* @return   
	* @remarks	   
	*/ 
   HRESULT OnLoginGrab( WPARAM wparam, LPARAM lparam );

private:
  /**	 
	* ����:  �������logic
	* @return   
	* @remarks	   
	*/
	void ClearAllLogic();

private:
    CLogicManage();
  
	TplArray<CWndLogicBase*> m_tplLogicList; //<logic�б�
    static CLogicManage *m_pLogicManage;

};

#define LogicManagePtr  CLogicManage::GetLogicManagePtr()

#endif // !defined(AFX_LOGICMANAGE_H__12E93E38_C38D_47CB_897A_CCE0522BEDD8__INCLUDED_)
