/*=======================================================================
ģ����      : CNC����̨
�ļ���      : addrmsgdriver.cpp
����ļ�    : 
�ļ�ʵ�ֹ���: ��ַ����Ϣ������
����        : 
�汾        : V3.0  Copyright(C) 1997-2003 KDC, All rights reserved.
-------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2012/7/25   1.0         Ф��Ȼ        ����
=======================================================================*/
#include "StdAfx.h"
#include "addrmsgdriver.h"
#include "cncmsgrecver.h"

////////////////////////////////////////////////////////////////////////////
// CMsgDriver

CAddrMsgDriver* CAddrMsgDriver::s_pMsgDriver = NULL;

CAddrMsgDriver::CAddrMsgDriver()
{
    // �����¼����Ʊ�
    //MappingEventName();
    // ������Ϣ���մ���
    m_hWndOsp = ::CreateWindowEx(0, _T("Static"), _T("AddrMsgDriver"), WS_DISABLED,
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
    s_pMsgDriver = this;
}

CAddrMsgDriver::~CAddrMsgDriver()
{
    ::KillTimer(m_hWndOsp, m_nTimer);
    // �ر���Ϣ���մ���

	::DestroyWindow( m_hWndOsp );
	m_hWndOsp = NULL;
	s_pMsgDriver = NULL;
}


/*=======================================================================
�� �� ��:   GetMtMsgPtr
��    ��:   �õ�������Ϣָ��(����TKdvMsg)
��    ��:   BOOL bClear = TRUE         [in]������Ϣָ��ʱ�Ƿ������Ϣ��
�� �� ֵ:   ������Ϣ����Ϣָ��
�����Ϣ:
-------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾  �޸���  �޸�����
2004/09/30  4.0   liuruifei  ����
=======================================================================*/
CTpMsg* CAddrMsgDriver::GetKdvMsgPtr(BOOL32 bClear)
{
    if (bClear) 
    {
        ZeroMemory(&m_cTpMsg, sizeof(CTpMsg));
    }

    return &m_cTpMsg;
}
/*=======================================================================
�� �� ��:   GetCMsgPtr
��    ��:   �õ�������Ϣָ��(����TMtMsg)
��    ��:   BOOL bClear = TRUE         [in]������Ϣָ��ʱ�Ƿ������Ϣ��
�� �� ֵ:   ������Ϣ����Ϣָ��
�����Ϣ:
-------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾  �޸���  �޸�����
2004/09/30  4.0   liuruifei  �޸�
=======================================================================*/
CMessage* CAddrMsgDriver::GetCMsgPtr(BOOL32 bClear /* = TRUE */)
{
	if (bClear)
	{
		ZeroMemory(&m_cMsg, sizeof(CMessage));
	}

	return &m_cMsg;
}

/*=======================================================================
�� �� ��:   PostMsg
��    ��:   ������������Ϣ������Ҫ�ն��л�Ӧ�����ýӿ�ǰҪҪͨ��GetPostMsgPtr
            ��������Ϣ��
��    ��:   u32 dwType = TYPE_CMESSAGE   [in]��Ϣ����TYPE_CMESSAGE��TYPE_MTMSG
�� �� ֵ:
�����Ϣ:
-------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾  �޸���  �޸�����
2004/08/25  3.5   ���ǿ  ����
=======================================================================*/
u16 CAddrMsgDriver::PostMsg(u32 dwType)
{  
    u32 dwDesIID = MAKEIID(AID_CN_UE, 1/*m_wInsID*/);	 // Ŀ�ģ�CNS
	u32 dwSrcIID = MAKEIID(AID_CNCADDRBOOK_APP);	         // Դ  ��CNS����̨
	
	u16 wRet = NO_ERROR;
	u16 wEvent = 0;
	if (TYPE_TPMSG == dwType) 
	{  
		//����CMtMsg��Ϣ��
		{
			wRet = m_cTpMsg.Post(dwDesIID, g_AddrBookApp.GetNodeId(), dwSrcIID);
		}
		wEvent = m_cTpMsg.GetEvent();
    }
	else
	{
		//����Osp CMessage��Ϣ
		if(m_cMsg.dstid != INVALID_NODE)
		{
			dwDesIID = m_cMsg.dstid;
		}
		if(m_cMsg.srcid != INVALID_NODE)
		{
			dwSrcIID = m_cMsg.srcid;
		}

		wRet = OspPost(dwDesIID, m_cMsg.event, m_cMsg.content, m_cMsg.length,
        g_AddrBookApp.GetNodeId(), dwSrcIID);

		wEvent = m_cMsg.event;
	}
	//��ӡ���   
	if(wRet == NO_ERROR)
	{  
		if( IS_PRINT_OUT_MSG )
		{
			CString strEvent = CPrintCtrl::GetPrintCtrl()->GetEventDescribe(wEvent);
	        PrtMsg( "[CncLib]: ������Ϣ:%s(%u).\n", strEvent,wEvent);
		}
	}
	else
	{   
		CString strEvent = CPrintCtrl::GetPrintCtrl()->GetEventDescribe(wEvent);
	    PrtMsg( "[CncLib]: ������Ϣ:%s(%u)ʧ��,�����룺%d\n", strEvent, wEvent, wRet ); 
	}
	
    return wRet;
}



/*=======================================================================
�� �� ��:   PostCommand
��    ��:   ������������Ϣ��һ�����Ҫ�ն��л�Ӧ�����޻�Ӧ�򱨳�ʱ�����ýӿ�ǰ
Ҫͨ��GetPostMsgPtr��������Ϣ��
��    ��:   CDispEvent *pDispEvent     [in]��Ӧ��Ϣ�Ĵ���ָ��
u16 *pwWaitEvent           [in]�ڴ���Ӧ����Ϣ����
s32 nEventNum = 1          [in]�ڴ���Ӧ����Ϣ����
u32 dwTimeOut = 1000       [in]�ڴ���Ӧ����Ϣ��ʱʱ��
�� �� ֵ:
�����Ϣ:
-------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾  �޸���  �޸�����
2004/08/25  3.5   ���ǿ  ����
=======================================================================*/
u16 CAddrMsgDriver::PostCommand(CKdvDispEvent *pDispEvent, u16 *pwWaitEvent,
                            s32 nEventNum, u32 dwType, u32 dwTimeOut)
{
    // ����Ƿ���ǰһ����������ִ����
    if(IsHandleCmd())
    {
        m_cCommandQueue.PushCommand(m_cMsg, m_cTpMsg, pDispEvent, pwWaitEvent,
                                    nEventNum, dwType, dwTimeOut);

        return ERR_CNC_WAIT_FOR_SEND_CMD;
    }
    // ���浱ǰ�������
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
    // ��ʱ��ʱ��
    m_nTimer = SetTimer(m_hWndOsp, 1, dwTimeOut, NULL);
    // ����
    u16 wRet = PostMsg(dwType);
    if(wRet != NO_ERROR)
    {
        // ����ʧ��
        ::KillTimer(m_hWndOsp, m_nTimer);
        ClearWaiting();
        PostNextCommand();
    }
    return wRet;
}

/*=======================================================================
�� �� ��:   PostCommand
��    ��:   ������������Ϣ��һ�����Ҫ�ն��л�Ӧ�����޻�Ӧ�򱨳�ʱ�����ýӿ�ǰ
            ҪҪͨ��GetPostMsgPtr��������Ϣ�壨�����ȴ���Ϣ��
��    ��:   CDispEvent *pDispEvent     [in]��Ӧ��Ϣ�Ĵ���ָ��
            u16 wWaitEvent             [in]�ڴ���Ӧ����Ϣ
            u32 dwTimeOut = 1000       [in]�ڴ���Ӧ����Ϣ��ʱʱ��
�� �� ֵ:
�����Ϣ:
-------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾  �޸���  �޸�����
2004/08/25  3.5   ���ǿ  ����
2004/10/28  3.5   �����   �޸�
=======================================================================*/
u16 CAddrMsgDriver::PostCommand(CKdvDispEvent *pDispEvent, u16 wWaitEvent, u32 dwType, u32 dwTimeOut)
{
    return PostCommand(pDispEvent, &wWaitEvent, 1, dwType, dwTimeOut);
}


/*=======================================================================
�� �� ��:   RegHandler
��    ��:   ע��һ��������Ϣ�����ָ��
��    ��:   CDispEvent* const pDispEvnet       [in]������Ϣ����ָ��
�� �� ֵ:
�����Ϣ:
-------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾  �޸���  �޸�����
2004/08/23  3.5   ���ǿ  ����
=======================================================================*/
void CAddrMsgDriver::RegHandler(CKdvDispEvent* const pDispEvnet)
{
    m_vpDispEvent.push_back(pDispEvnet);
}

/*=======================================================================
�� �� ��:   RegHandler
��    ��:   ע��һ��������Ϣ�����ָ��
��    ��:   CDispEvent* const pDispEvnet       [in]������Ϣ����ָ��
�� �� ֵ:
�����Ϣ:
-------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾  �޸���  �޸�����
2004/08/23  3.5   ���ǿ  ����
=======================================================================*/
void CAddrMsgDriver::UnregHandler(CKdvDispEvent* const pDispEvnet)
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

/*=======================================================================
�� �� ��:   ClearHandler
��    ��:   �������ע������ָ��
��    ��:
�� �� ֵ:
�����Ϣ:
-------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾  �޸���  �޸�����
2004/08/23  3.5   ���ǿ  ����
=======================================================================*/
void CAddrMsgDriver::ClearHandler()
{
    m_vpDispEvent.clear();
}

void CAddrMsgDriver::ClearAllCommand()
{
    m_cCommandQueue.ClearCommand();
}

/*=============================================================================
  �� �� ���� OnOspMessageComing
  ��    �ܣ� ��OSP�ص��߳���ȡ��Ϣ����ӡ��Ϣ�ַ���Ϣ
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� WPARAM wParam  0
             LPARAM lParam  0
  �� �� ֵ�� void 
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2004/10/13     3.5		�����                  �淶��
=============================================================================*/
void CAddrMsgDriver::OnOspMessageComing(WPARAM wParam, LPARAM lParam)
{
    // ��OSP�ص��߳���ȡ��Ϣ
    CAddrMsgHandler *pHandler = CAddrMsgHandler::GetMsgHandler();
    if (!pHandler) 
    {
        return;
    }
    CCncMsgQueue cMsgQue;
    pHandler->PopAllMsg(cMsgQue);
    // �ַ���Ϣ
    while(!cMsgQue.IsEmpty())
    {
        const CMessage &cMsg = cMsgQue.Front();

		//��ӡ���
		CString strEvent = CPrintCtrl::GetPrintCtrl()->GetEventDescribe(cMsg.event);
		if( IS_PRINT_OUT_MSG )
		{   	 
			PrtMsg( "[CncLib]: �յ���Ϣ:%s(%u).\n", strEvent,cMsg.event);
		}

        // ��������Ӧ����Ϣ
        if(IsHandleCmd())
        {	
            vector<u16>::iterator itr = m_vWaitingEvents.begin();
            for(; itr != m_vWaitingEvents.end(); itr++)
            {
                if(*itr == cMsg.event)
                {
                    // 2004/08/24 ���ǿ �õ���Ӧ�������ʱ��
                    ::KillTimer(m_hWndOsp, m_nTimer);
                    ClearWaiting();
                    PostNextCommand();
                    break;
                }
            }
        }
        // ������Ϣ�ַ���
        vector<CKdvDispEvent*>::iterator itr = m_vpDispEvent.begin();
        BOOL bFind = FALSE;
        for(; itr != m_vpDispEvent.end(); itr++)
        {
            if ((*itr)->HasRegEvent(cMsg.event)) 
            {
                (*itr)->DispEvent(cMsg);
                bFind = TRUE;
            }
        }
        if (!bFind) 
        {	  	 
			PrtMsg( "[CncLib]: ��Ϣ:%s(%d)������,��Ϊû���ҵ�ƥ�����Ϣ������.\n", strEvent, cMsg.event);		
        }

        cMsgQue.Pop();
    }
}

/*=============================================================================
  �� �� ���� OnOspSyncMsgComing
  ��    �ܣ� ͬ����Ϣ����
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� WPARAM wParam ��Ϣָ��
             LPARAM lParam 0
  �� �� ֵ�� void 
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2004/11/30     3.5		    �����                   ����
=============================================================================*/
void CAddrMsgDriver::OnOspSyncMsgComing(WPARAM wParam, LPARAM lParam)
{    
    CMessage *pMsg = (CMessage *)wParam;
   
	//��ӡ���
	CString strEvent = CPrintCtrl::GetPrintCtrl()->GetEventDescribe(pMsg->event);
	if( IS_PRINT_OUT_MSG )
	{   	 
		PrtMsg( "[CncLib]: �յ���Ϣ:%s(%u).\n", strEvent, pMsg->event);
	}

    // ������Ϣ�ַ���
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
		PrtMsg( "[CncLib]: ��Ϣ:%s(%d)������,��Ϊû���ҵ�ƥ�����Ϣ������.\n", strEvent, pMsg->event);
    }

}

/*=============================================================================
  �� �� ���� OnTimer
  ��    �ܣ� ��ʱ��ʱ����Ϣ���ȴ�����Ϣ��ʱ��Ӧ����յȴ���Ϣ����
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� WPARAM wParam
             LPARAM lParam
  �� �� ֵ�� void 
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2004/10/13     3.5		�����                  �淶��
=============================================================================*/
void CAddrMsgDriver::OnTimer(WPARAM wParam, LPARAM lParam)
{
    if (wParam == m_nTimer)
    {
        // ��ʱ��ʱ����Ϣ
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

/*=============================================================================
  �� �� ���� WndProc
  ��    �ܣ� �Զ���Ĵ��ڴ�������������windows��Ϣ��OSP��Ϣ�Լ���ʱ��Ϣ
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� HWND hWnd
             UINT uMsg
             WPARAM wParam
             LPARAM lParam
  �� �� ֵ�� LRESULT CALLBACK 
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2004/10/13     3.5		�����                  �淶��
=============================================================================*/
LRESULT CALLBACK CAddrMsgDriver::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // ����OSP��Ϣ�ͳ�ʱ��ʱ����Ϣ
    if (CAddrMsgDriver::s_pMsgDriver) 
    {
        if (uMsg == CCncMsgHandler::WM_OSPMESSAGECOMING) 
        {
            CAddrMsgDriver::s_pMsgDriver->OnOspMessageComing(wParam, lParam);
        }
        else if (uMsg == CCncMsgHandler::WM_OSPSYNCMSGCOMING)
        {
            CAddrMsgDriver::s_pMsgDriver->OnOspSyncMsgComing(wParam, lParam);            
        }
        else if (uMsg == WM_TIMER) 
        {
            CAddrMsgDriver::s_pMsgDriver->OnTimer(wParam, lParam);
        }
        else
        {
			if ( CAddrMsgDriver::s_pMsgDriver->m_wndprocOld != NULL )
			{
				return CallWindowProc(CAddrMsgDriver::s_pMsgDriver->m_wndprocOld,
                                hWnd, uMsg, wParam, lParam);
			}
            
        }
    }
    return 0;
}

/*=============================================================================
  �� �� ���� ClearWaiting
  ��    �ܣ� ��յȴ���Ϣ���飬�Ա����IsHandleCmdʱΪFALSE��ʹ��Ϣ���Լ�������
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� 
  �� �� ֵ�� void 
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2004/10/13     3.5		�����                  �淶��
=============================================================================*/
void CAddrMsgDriver::ClearWaiting()
{
    m_vWaitingEvents.clear();
    m_pCurDispEvent = NULL;
    m_wCurSendEvent = 0;
}

void CAddrMsgDriver::PostNextCommand()
{
    ClearWaiting();

    // û�д�������Ϣʱֱ�ӷ���
    if(TRUE == m_cCommandQueue.IsEmpty())
    {
        return;
    }

    // ȡ����һ�������͵�����
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

    // ����������ͳ�ȥ
    PostCommand(tCommand.m_pCDispEvent, pwWaitEvent, tCommand.m_nEventNum,
                tCommand.m_dwType, tCommand.m_dwTimeout);

    delete []pwWaitEvent;
}

