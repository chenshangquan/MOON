// addrinstance.cpp: implementation of the CAddrInstance class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "addrinstance.h"
#include "tpadmsgdriver.h"
#include "msgtransdriver.h"
#include "cnconst.h"

zTemplate<CAddrInstance, 1> g_AddrBookApp;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAddrInstance::CAddrInstance()
{

}

CAddrInstance::~CAddrInstance()
{

}

void CAddrInstance::InstanceEntry(CMessage *const pMsg)
{
    u32 dwSrcIID = MAKEIID(AID_ADDRBOOK, 1);	 //本源 
    
    u32 dwSrcId = pMsg->srcid; 
        
    if ( dwSrcId == MAKEIID(AID_CNCADDRBOOK_APP) )
    {
        //从cnc发过来的消息，转发给cns
        u32 dwNodeId = 0;
        if ( CTPadMsgDriver::s_pMsgDriver != NULL )
        {
            dwNodeId = CTPadMsgDriver::s_pMsgDriver->GetNodeId();  
        }
        u16 wRet = OspPost( pMsg->dstid, pMsg->event, pMsg->content, pMsg->length,
        dwNodeId, dwSrcIID );
    }
    else if ( dwSrcId == dwSrcIID )
    {
        //从cns发过来的消息，转发给cnc
        MsgTransDriver->TransAddrMsg( pMsg );
    }

    
}
