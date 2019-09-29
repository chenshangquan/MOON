// tpadinstance.cpp: implementation of the CTPadInstance class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "tpadinstance.h"
#include "tpadmsgdriver.h"
#include "msgtransdriver.h"

zTemplate<CTPadInstance, INSTANCE_COUNT> g_tPadApp;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTPadInstance::CTPadInstance()
{

}

CTPadInstance::~CTPadInstance()
{

}


void CTPadInstance::InstanceEntry(CMessage *const pMsg)
{
    //分发消息
    MsgTransDriver->DispatchMsg( pMsg );

    //处理TPad自身注册的消息
    CString strEvent = CPrintCtrl::GetPrintCtrl()->GetEventDescribe(pMsg->event);
    if( !strEvent.IsEmpty() )
    {   	 
        //PrtMsg( " 收到消息:%s(%u).\n", strEvent, cMsg.event );
        CTPadMsgDriver::s_pMsgDriver->OnOspMessageComing( pMsg );
       
	}

}
