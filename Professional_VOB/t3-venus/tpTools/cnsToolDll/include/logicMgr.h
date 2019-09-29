// logicMgr.h: interface for the CLogicMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGICMGR_H__7B7DC23D_9E73_4096_8042_79ED81C7A199__INCLUDED_)
#define AFX_LOGICMGR_H__7B7DC23D_9E73_4096_8042_79ED81C7A199__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "templateClass.h"
#include "logicbase.h"
#include "mainFrameLogic.h"
#include "basicInfoLogic.h"
#include "cfgFrameLogic.h"
#include "CfgCnsLogic.h"
#include "cfgAudioPortLogic.h"
#include "diagInfoLogic.h"
#include "centCtrlLogic.h"
#include "diagTestFrameLogic.h"
#include "diagTestInfoLogic.h"
#include "netmngoptdlgLogic.h"
#include "cfgnetmngLogic.h"
#include "cameraLogic.h"
#include "addrbookExpLogic.h"
#include "cfgMixLogic.h"
#include "cfgEqLogic.h"
#include "cfgServerLogic.h"
#include "expcommonLogic.h"
#include "impcommonLogic.h"
#include "warningLogic.h"
#include "cfgCallSerLogic.h"
#include "CentCfgFrameLogic.h"
#include "centCfgDisplayDlg.h"

class CLogicMgr: public ISingleTon<CLogicMgr>
{
public: 
	virtual ~CLogicMgr();

    CLogicMgr();
 /**	 
	* ����:  ��������logic 
	* @return   
	* @remarks	   
	*/ 
   void CreateLogic();
 

   	/**	 
	* ����:  ��������logic 
	* @return   
	* @remarks	   
	*/ 
   void DestroyLogic();
 
   /**	 
	* ����:  ��ȡlogicָ��
	* @return   
	* @remarks	   
	*/ 
   void GetLogic( CCfgCnsLogic **pLogic );
 
   void GetLogic( CCfgAudioPortLogic **pLogic );
private:
 
};



#define  LOGICMGR_PTR CLogicMgr::GetSingletonPtr()



#endif // !defined(AFX_LOGICMGR_H__7B7DC23D_9E73_4096_8042_79ED81C7A199__INCLUDED_)
