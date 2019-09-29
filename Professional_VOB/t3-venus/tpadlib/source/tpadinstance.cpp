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
    //�ַ���Ϣ
    MsgTransDriver->DispatchMsg( pMsg );

    //����TPad����ע�����Ϣ
    CString strEvent = CPrintCtrl::GetPrintCtrl()->GetEventDescribe(pMsg->event);
    if( !strEvent.IsEmpty() )
    {   	 
        //PrtMsg( " �յ���Ϣ:%s(%u).\n", strEvent, cMsg.event );
        CTPadMsgDriver::s_pMsgDriver->OnOspMessageComing( pMsg );
       
	}

}
