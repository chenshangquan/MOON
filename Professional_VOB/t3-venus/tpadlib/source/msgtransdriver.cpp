// msgtransdriver.cpp: implementation of the CMsgTransDriver class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "msgtransdriver.h"
#include "msgtransinstance.h"
#include "tpadmsgdriver.h"

CMsgTransDriver* CMsgTransDriver::m_pTransDriver = NULL;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMsgTransDriver::CMsgTransDriver()
{

}

CMsgTransDriver::~CMsgTransDriver()
{

}

CMsgTransDriver* CMsgTransDriver::GetMsgDriverPtr()
{
    if ( NULL != m_pTransDriver )
    {
        return m_pTransDriver ;
	}

    m_pTransDriver = new CMsgTransDriver;

    return m_pTransDriver;
}

void CMsgTransDriver::RegTransNode( TNodeInfo tNodeInfo )
{
    vector<TNodeInfo>::iterator itr = m_vctNodeList.begin();
    while( itr != m_vctNodeList.end() )
    {
        if ( *itr == tNodeInfo )
        {  
            return;
        }
        itr ++;
    }
    m_vctNodeList.push_back( tNodeInfo );
}

void CMsgTransDriver::DelTransNode( u32 dwNodeId )
{
    vector<TNodeInfo>::iterator itr = m_vctNodeList.begin();
    while( itr != m_vctNodeList.end() )
    {
        if ( itr->dwNodeId == dwNodeId )
        {
            m_vctNodeList.erase( itr );
            return;
        }
    }
}


void CMsgTransDriver::DispatchMsg( CMessage *const pMsg )
{
    u32 dwSrcIID = MAKEIID(AID_TPAD_MSGTRANS);	 //源 

    for ( int i = 0; i < m_vctNodeList.size(); i++ )
    {
        TNodeInfo tNodeInfo = m_vctNodeList.at(i);

        u16 wRet = OspPost( tNodeInfo.dwInstId, pMsg->event, pMsg->content, pMsg->length,
            tNodeInfo.dwNodeId, dwSrcIID );
    }

}


void CMsgTransDriver::TransMsg( emTPadSubType emType, CMessage *const pMsg )
{
    for( int i = 0; i < m_vctNodeList.size(); i++ )
    {
        TNodeInfo tNodeInfo = m_vctNodeList.at(i);
        if ( tNodeInfo.emSubType == emType )
        {
            u16 wRet = OspPost( tNodeInfo.dwInstId, pMsg->event, pMsg->content, pMsg->length,
            tNodeInfo.dwNodeId, pMsg->srcid );

            break;
        }
    }
}


void CMsgTransDriver::TransAddrMsg( CMessage *const pMsg )
{
    u32 dwInstID = MAKEIID(AID_CNCADDRBOOK_APP);

    for( int i = 0; i < m_vctNodeList.size(); i++ )
    {
        TNodeInfo tNodeInfo = m_vctNodeList.at(i);
        if ( tNodeInfo.emSubType == emTPad_cnc )
        {
            u16 wRet = OspPost( dwInstID, pMsg->event, pMsg->content, pMsg->length,
                tNodeInfo.dwNodeId, pMsg->srcid );
            
            break;
        }
    }
}


void CMsgTransDriver::OnOspMessageComing()
{
    // 从OSP回调线程提取消息
    CMsgTransInstance *pHandler = CMsgTransInstance::GetMsgTransInst();
    if (!pHandler) 
    {
        return;
    }
    CMsgQueue cMsgQue;
    pHandler->PopAllMsg(cMsgQue);
    // 处理消息
    while(!cMsgQue.IsEmpty())
    {
        const CMessage &cMsg = cMsgQue.Front();
        
        u16 wEvent = cMsg.event;

        switch( wEvent ) 
        {
	    case ev_CnLogin_Req:
            {
                TNodeInfo tNodeInfo;
                tNodeInfo.dwNodeId = cMsg.srcnode;
                tNodeInfo.dwInstId = cMsg.srcid;
                tNodeInfo.emSubType = *(emTPadSubType*)cMsg.content;

                RegTransNode( tNodeInfo );

                //断链检测
		        ::OspNodeDiscCBRegQ( tNodeInfo.dwNodeId, pHandler->GetAppID(), pHandler->GetInsID() );
            }
            break;
        case ev_TPadSetSysName_Nty://dyy 
            {
                CTPadMsgDriver::s_pMsgDriver->OnOspMessageComing( (CMessage *const) &cMsg );
            }
            break;
		case ev_TpadDisconnectCns_Nty:
			{
				CTPadMsgDriver::s_pMsgDriver->OnOspMessageComing( (CMessage *const) &cMsg );
			}
			break;
        case OSP_DISCONNECT:
            {
                // OSP断链通知
                u32 dwNodeId = *(u32*)(cMsg.content);
                
                DelTransNode( dwNodeId );
            }
            break;
        default:
            //将消息转发给cns
            if ( CTPadMsgDriver::s_pMsgDriver != NULL )
            {
                u16 wRet = CTPadMsgDriver::s_pMsgDriver->TransMsg( &cMsg );  
            }
            break;
        }
    
        cMsgQue.Pop();
    }
}


void CMsgTransDriver::ClearOspMsg()
{
    CMsgTransInstance *pHandler = CMsgTransInstance::GetMsgTransInst();
    if (pHandler) 
    {
        pHandler->ClearQueue();
    }
}

BOOL CMsgTransDriver::IsAlreadyReg( vector<TNodeInfo>&vctNodeList )
{
    vctNodeList = m_vctNodeList;
    vector<TNodeInfo>::iterator itr = m_vctNodeList.begin();
    BOOL bIsCncReg = FALSE;
    BOOL bIsCenterltrlReg = FALSE;
    while( itr != m_vctNodeList.end() )
    {
        if ( itr->emSubType == emTPad_cnc )
        {
            bIsCncReg = TRUE;
        }
        else if ( itr->emSubType == emTPad_centerctrl )
        {
            bIsCenterltrlReg = TRUE;
        }

        itr++;
    }

    if ( bIsCncReg && bIsCenterltrlReg )
    {
        return TRUE;
    }

    return FALSE;
}
