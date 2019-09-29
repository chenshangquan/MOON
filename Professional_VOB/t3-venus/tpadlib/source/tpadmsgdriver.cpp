// tpadmsgdriver.cpp: implementation of the CTpadMsgDriver class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "tpadmsgdriver.h"


CTPadMsgDriver* CTPadMsgDriver::s_pMsgDriver = NULL;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CTPadMsgDriver::CTPadMsgDriver()
{
    // 构造事件名称表
    MappingEventName();
    // 创建消息接收窗口
    m_hWndOsp = ::CreateWindowEx(0, _T("Static"), _T("TPadMsgDriver"), WS_DISABLED,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, 0, 0);
    
    if ( m_hWndOsp != NULL )
    {
        m_wndprocOld = reinterpret_cast<WNDPROC>(GetWindowLong(m_hWndOsp, GWL_WNDPROC));
        SetWindowLong(m_hWndOsp, GWL_WNDPROC, reinterpret_cast<s32>(WndProc));
    } 
    else
    {
        m_wndprocOld = NULL;
	}

    m_nTimer = 0;
    m_pCurDispEvent = NULL;
    m_wCurSendEvent = 0;   
    m_dwNodeId = 0;
    m_wAppID = 0;
    
    s_pMsgDriver = this;
}

CTPadMsgDriver::~CTPadMsgDriver()
{
    ::KillTimer(m_hWndOsp, m_nTimer);
    ::DestroyWindow( m_hWndOsp );
	m_hWndOsp = NULL;
    s_pMsgDriver = NULL;
}

CTpMsg* CTPadMsgDriver::GetKdvMsgPtr(BOOL32 bClear)
{
    if (bClear) 
    {
        ZeroMemory(&m_cTpMsg, sizeof(CTpMsg));
    }
    
    return &m_cTpMsg;
}

CTPadMsgDriver* CTPadMsgDriver::GetMsgDriverPtr()
{
    return s_pMsgDriver;
}


u16 CTPadMsgDriver::TransMsg( const CMessage* pMsg )
{
    u32 dwDesIID = MAKEIID(AID_CN_UE, 1);	 //目的：CNS
    u32 dwSrcIID = MAKEIID(GetAppId());	     //源 

    u16 wRet = NO_ERROR;

    wRet = OspPost( dwDesIID, pMsg->event, pMsg->content, pMsg->length,
            GetNodeId(), dwSrcIID );
    return wRet;
}


u16 CTPadMsgDriver::PostMsg(u32 dwType)
{  
    u32 dwDesIID = MAKEIID(AID_CN_UE, 1);	 //目的：CNS
    u32 dwSrcIID = MAKEIID(GetAppId());	     //源  
    
    u16 wRet = NO_ERROR;
    u16 wEvent = 0;
    if (TYPE_TPMSG == dwType) 
    {  
        //发送CMtMsg消息体
        {
            wRet = m_cTpMsg.Post(dwDesIID, GetNodeId(), dwSrcIID);
        }
        wEvent = m_cTpMsg.GetEvent();
    }
    else
    {
        //发送Osp CMessage消息
        if(m_cMsg.dstid != INVALID_NODE)
        {
            dwDesIID = m_cMsg.dstid;
        }
        if(m_cMsg.srcid != INVALID_NODE)
        {
            dwSrcIID = m_cMsg.srcid;
        }
        
        wRet = OspPost(dwDesIID, m_cMsg.event, m_cMsg.content, m_cMsg.length,
            GetNodeId(), dwSrcIID);
        
        wEvent = m_cMsg.event;
    }
    
    return wRet;
}

u16 CTPadMsgDriver::PostCommand(CKdvDispEvent *pDispEvent, u16 *pwWaitEvent,
                               s32 nEventNum, u32 dwType, u32 dwTimeOut)
{
    // 检测是否有前一个命令正在执行中
    if(IsHandleCmd())
    {
        m_cCommandQueue.PushCommand(m_cMsg, m_cTpMsg, pDispEvent, pwWaitEvent,
            nEventNum, dwType, dwTimeOut);
        
        return ERR_TPAD_WAIT_FOR_SEND_CMD;
    }
    // 保存当前命令参数
    if(TYPE_CMESSAGE == dwType)
    {
        m_wCurSendEvent = m_cMsg.event;
    }
    else
    {
        m_wCurSendEvent = m_cTpMsg.GetEvent();
    }
    m_pCurDispEvent = pDispEvent;
    
    for(s32 nIndex = 0; nIndex < nEventNum; nIndex++)
    {
        m_vWaitingEvents.push_back(pwWaitEvent[nIndex]);
    }
    // 超时计时器
    m_nTimer = SetTimer(m_hWndOsp, 1, dwTimeOut, NULL);
    // 发送
    u16 wRet = PostMsg(dwType);
    if(wRet != NO_ERROR)
    {
        // 发送失败
        ::KillTimer(m_hWndOsp, m_nTimer);
        ClearWaiting();
        PostNextCommand();
    }
    return wRet;
}

u16 CTPadMsgDriver::PostCommand(CKdvDispEvent *pDispEvent, u16 wWaitEvent, u32 dwType, u32 dwTimeOut)
{
    return PostCommand(pDispEvent, &wWaitEvent, 1, dwType, dwTimeOut);
}

void CTPadMsgDriver::ClearWaiting()
{
    m_vWaitingEvents.clear();
    m_pCurDispEvent = NULL;
    m_wCurSendEvent = 0;
}

void CTPadMsgDriver::PostNextCommand()
{
    ClearWaiting();
    
    // 没有待发送消息时直接返回
    if(TRUE == m_cCommandQueue.IsEmpty())
    {
        return;
    }
    
    // 取出下一条待发送的命令
    TCOMMAND tCommand;
    BOOL32 bSucess = m_cCommandQueue.GetNextCommand(tCommand);
    if(FALSE == bSucess)
    {
        return;
    }
    
    u16* pwWaitEvent = new u16[tCommand.m_nEventNum];
    
    ASSERT(tCommand.m_nEventNum == tCommand.m_vctWaitEvent.size());
    
    for(u32 nIndex = 0; nIndex < tCommand.m_nEventNum; nIndex++)
    {
        pwWaitEvent[nIndex] = tCommand.m_vctWaitEvent[nIndex];
    }
    
    if(TYPE_CMESSAGE == tCommand.m_dwType)
    {
        m_cMsg = tCommand.m_cMsg;
    }
    else
    {
        m_cTpMsg = tCommand.m_cMtMsg;
    }
    
    // 将该条命令发送出去
    PostCommand(tCommand.m_pCDispEvent, pwWaitEvent, tCommand.m_nEventNum,
        tCommand.m_dwType, tCommand.m_dwTimeout);
    
    delete []pwWaitEvent;
}


LRESULT CALLBACK CTPadMsgDriver::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (CTPadMsgDriver::s_pMsgDriver) 
    {
        if (uMsg == WM_TIMER) 
        {
            CTPadMsgDriver::s_pMsgDriver->OnTimer(wParam, lParam);
        }
    }

    return 0;
}


void CTPadMsgDriver::OnTimer(WPARAM wParam, LPARAM lParam)
{
    if (wParam == m_nTimer)
    {
        // 超时计时器消息
        ::KillTimer(m_hWndOsp, m_nTimer);
        if(IsHandleCmd())
        {
            if (m_pCurDispEvent) 
            {
                m_pCurDispEvent->OnTimeOut(m_wCurSendEvent);
            }
            ClearWaiting();
            PostNextCommand();
        }
    }
}

void CTPadMsgDriver::RegHandler(CKdvDispEvent* const pDispEvnet)
{
    m_vpDispEvent.push_back(pDispEvnet);
}


void CTPadMsgDriver::UnregHandler(CKdvDispEvent* const pDispEvnet)
{
    vector<CKdvDispEvent*>::iterator itr = m_vpDispEvent.begin();
    for(; itr != m_vpDispEvent.end(); itr++)
    {
        if (*itr == pDispEvnet) 
        {
            m_vpDispEvent.erase(itr);
            break;
        }
    }
}

void CTPadMsgDriver::ClearHandler()
{
    m_vpDispEvent.clear();
}

void CTPadMsgDriver::ClearAllCommand()
{
    m_cCommandQueue.ClearCommand();
}


void CTPadMsgDriver::OnOspMessageComing( CMessage *const pMsg )
{
    CString strEvent = CPrintCtrl::GetPrintCtrl()->GetEventDescribe(pMsg->event);

    // 检索命令应答消息
    if(IsHandleCmd())
    {	
        vector<u16>::iterator itr = m_vWaitingEvents.begin();
        for(; itr != m_vWaitingEvents.end(); itr++)
        {
            if(*itr == pMsg->event)
            {
                ::KillTimer(m_hWndOsp, m_nTimer);
                ClearWaiting();
                PostNextCommand();
                break;
            }
        }
    }
    // 检索消息分发表
    vector<CKdvDispEvent*>::iterator itr = m_vpDispEvent.begin();
    BOOL bFind = FALSE;
    for(; itr != m_vpDispEvent.end(); itr++)
    {
        if ((*itr)->HasRegEvent(pMsg->event)) 
        {
            (*itr)->DispEvent(*pMsg);
            bFind = TRUE;
        }
    }
    if (!bFind) 
    {	  	 
        PrtMsg( "[CncLib]: 消息:%s(%d)被抛弃,因为没有找到匹配的消息处理器.\n", strEvent, pMsg->event);		
    }
}



void CTPadMsgDriver::MappingEventName()
{
    MAPPING_HELPER( OSP_DISCONNECT, _T("OSP_DISCONNECT") );
    MAPPING_HELPER( ev_CnLogin_Req, _T("ev_CnLogin_Req") );
	MAPPING_HELPER( ev_CnLogin_Rsp, _T("ev_CnLogin_Rsp") );
    MAPPING_HELPER( ev_TpadUpdateSystem_Cmd, _T("ev_TpadUpdateSystem_Cmd") );
    MAPPING_HELPER( ev_CNSLoginByOther_Notify, _T("ev_CNSLoginByOther_Notify") );
    MAPPING_HELPER( ev_Cn_CentreSleepNty, _T("ev_Cn_CentreSleepNty") );

    //修改系统名称 dyy 2013年8月29日
    MAPPING_HELPER( ev_TPadSetSysName_Nty, _T("ev_TPadLoginInfo_Nty") );
	//577
	MAPPING_HELPER( ev_TppIsRcvDual_Nty, _T("ev_TppIsRcvDual_Nty") );
	MAPPING_HELPER( ev_TppAddDualRcvAddr_Cmd, _T("ev_TppAddDualRcvAddr_Cmd") );
	MAPPING_HELPER( ev_TppDelDualRcvAddr_Cmd, _T("ev_TppDelDualRcvAddr_Cmd") );
	MAPPING_HELPER( ev_TppPadDualKeyFrame_Req, _T("ev_TppPadDualKeyFrame_Req") );
	MAPPING_HELPER( ev_TppAddDualRcvAddr_Ind, _T("ev_TppAddDualRcvAddr_Ind") );
    MAPPING_HELPER( ev_TppDelDualRcvAddr_Ind, _T("ev_TppDelDualRcvAddr_Ind") );

	MAPPING_HELPER( ev_TppTPadDualVideo_Cmd, _T("ev_TppTPadDualVideo_Cmd") );
	MAPPING_HELPER( ev_TppTPadDualRcvAddr_Cmd, _T("ev_TppTPadDualRcvAddr_Cmd") );
	MAPPING_HELPER( ev_TppTPadDualRcvAddr_Ind, _T("ev_TppTPadDualRcvAddr_Ind") );
	MAPPING_HELPER( ev_TppTPadDualVideo_Ind, _T("ev_TppTPadDualVideo_Ind") );
	//	MAPPING_HELPER( ev_TppTPadDualVideoRes_Ind, _T("ev_TppTPadDualVideoRes_Ind") );
	//	MAPPING_HELPER( ev_TppCodecVidEncParam_Cmd, _T("ev_TppCodecVidEncParam_Cmd") );
	//	MAPPING_HELPER( ev_TppCodecEncryptKey_Cmd, _T("ev_TppCodecEncryptKey_Cmd") );
	MAPPING_HELPER( ev_tppCodecDynamicPayloadCmd, _T("ev_tppCodecDynamicPayloadCmd") );
	MAPPING_HELPER( ev_tppCodecStartCmd, _T("ev_tppCodecStartCmd") );  
	MAPPING_HELPER( ev_tppSndKeyFrame_Req, _T("ev_tppSndKeyFrame_Req"), 3 ); 
	MAPPING_HELPER( ev_CnConfState_Nty, _T("ev_CnConfState_Nty") );   
}


