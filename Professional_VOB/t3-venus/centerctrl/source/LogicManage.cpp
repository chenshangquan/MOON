// LogicManage.cpp: implementation of the CLogicManage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "centerctrl.h"
#include "LogicManage.h"

#include "centerctrllogic.h"
#include "mainmenulogic.h"
#include "airconditionlogic.h"
#include "monitorlogic.h"
#include "touchpadlogic.h"
#include "CameraLogic.h"
#include "CurtainCfgLogic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CLogicManage::CLogicManage()
{

}

CLogicManage::~CLogicManage()
{

}


void CLogicManage::CreateLogic()
{  
    REG_MSG_HANDLER( UI_CNS_DISCONNECTED, CLogicManage::OnDisConnect, LogicManagePtr, CLogicManage );

    CCenterCtrlLogic::GetLogicPtr()->InitLogic();
    CMainMenuLogic::GetLogicPtr()->InitLogic();
    CAirConditionLogic::GetLogicPtr()->InitLogic();
    CMonitorLogic::GetLogicPtr()->InitLogic();
    CTouchPadLogic::GetLogicPtr()->InitLogic();
	CCameraLogic::GetLogicPtr()->InitLogic();
	CCurtainCfgLogic::GetLogicPtr()->InitLogic();
} 

HRESULT CLogicManage::OnDisConnect( WPARAM wparam, LPARAM lparam ) 
{
    CCenterCtrlLogic::GetLogicPtr()->Clear();
    CMainMenuLogic::GetLogicPtr()->Clear();
    CAirConditionLogic::GetLogicPtr()->Clear();
    CMonitorLogic::GetLogicPtr()->Clear();
    CTouchPadLogic::GetLogicPtr()->Clear();
	CCameraLogic::GetLogicPtr()->Clear();
	CCurtainCfgLogic::GetLogicPtr()->Clear();

    return NO_ERROR;
}