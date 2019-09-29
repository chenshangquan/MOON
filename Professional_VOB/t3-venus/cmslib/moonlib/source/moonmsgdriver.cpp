/*=======================================================================
ģ����      : MOON90���������
�ļ���      : MoonMsgDriver.cpp
����ļ�    : 
�ļ�ʵ�ֹ���: ��Ϣ������
����        : 
�汾        : V3.0  Copyright(C) 1997-2003 KDC, All rights reserved.
-------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2014/12/2   1.0         ���`�`        ����
=======================================================================*/
#include "StdAfx.h"
#include "moonmsgdriver.h"
#include "moonmsgrecver.h"
#include "moonlib.h"

////////////////////////////////////////////////////////////////////////////
// CMsgDriver

CMoonMsgDriver* CMoonMsgDriver::s_pMsgDriver = NULL;

CMoonMsgDriver::CMoonMsgDriver()
{
    // �����¼����Ʊ�
    MappingEventName();
    // ������Ϣ���մ���
    m_hWndOsp = ::CreateWindowEx(0, _T("Static"), _T("MoonMsgDriver"), WS_DISABLED,
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
    m_byTransferStatus = FREE;
    m_pbyFile = NULL;
    m_dwFileLength = 0;         // �ļ�����
    m_dwFileFragIndex = 0;      // �ļ������
    m_dwFileCurPos = 0;
	m_wInsID = 0;
    m_wAppID = 0;
    m_dwDesIID = MAKEIID(AID_MOON_UE, 1);
}

CMoonMsgDriver::~CMoonMsgDriver()
{
    if (m_pbyFile != NULL)
    {
        free(m_pbyFile);
        m_pbyFile = NULL;
    }
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
CTpMsg* CMoonMsgDriver::GetKdvMsgPtr(BOOL32 bClear)
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
CMessage* CMoonMsgDriver::GetCMsgPtr(BOOL32 bClear /* = TRUE */)
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
u16 CMoonMsgDriver::PostMsg(u32 dwType)
{  
    u32 dwDesIID = GetDesIID();//MAKEIID(AID_CN_UE, 1/*m_wInsID*/);	 // Ŀ�ģ�MOON
	u32 dwSrcIID = MAKEIID(GetAppID());	         // Դ  ��MOON����̨
	
	u16 wRet = NO_ERROR;
	u16 wEvent = 0;
	if (TYPE_TPMSG == dwType) 
	{  
		//����CMtMsg��Ϣ��
		{
			wRet = m_cTpMsg.Post(dwDesIID, g_MoonApp.GetNodeId(), dwSrcIID);
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
        g_MoonApp.GetNodeId(), dwSrcIID);

		wEvent = m_cMsg.event;
	}
	//��ӡ���   
// 	if(wRet == NO_ERROR)
// 	{  
// 		if( IS_PRINT_OUT_MSG )
// 		{
// 			CString strEvent = CPrintCtrl::GetPrintCtrl()->GetEventDescribe(wEvent);
// 	        PrtMsg( "[CncLib]: ������Ϣ:%s(%u).\n", strEvent,wEvent);
// 		}
// 	}
// 	else
// 	{   
// 		CString strEvent = CPrintCtrl::GetPrintCtrl()->GetEventDescribe(wEvent);
// 	    PrtMsg( "[CncLib]: ������Ϣ:%s(%u)ʧ��,�����룺%d\n", strEvent, wEvent, wRet ); 
// 	}
	
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
u16 CMoonMsgDriver::PostCommand(CKdvDispEvent *pDispEvent, u16 *pwWaitEvent,
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
u16 CMoonMsgDriver::PostCommand(CKdvDispEvent *pDispEvent, u16 wWaitEvent, u32 dwType, u32 dwTimeOut)
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
void CMoonMsgDriver::RegHandler(CKdvDispEvent* const pDispEvnet)
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
void CMoonMsgDriver::UnregHandler(CKdvDispEvent* const pDispEvnet)
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
void CMoonMsgDriver::ClearHandler()
{
    m_vpDispEvent.clear();
}

void CMoonMsgDriver::ClearAllCommand()
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
void CMoonMsgDriver::OnOspMessageComing(WPARAM wParam, LPARAM lParam)
{
    // ��OSP�ص��߳���ȡ��Ϣ
    CMoonMsgHandler *pHandler = CMoonMsgHandler::GetMsgHandler();
    if (!pHandler) 
    {
        return;
    }
    CMoonMsgQueue cMsgQue;
    pHandler->PopAllMsg(cMsgQue);
    // �ַ���Ϣ
    while(!cMsgQue.IsEmpty())
    {
        const CMessage &cMsg = cMsgQue.Front();

		//��ӡ���
		CString strEvent = CPrintCtrl::GetPrintCtrl()->GetEventDescribe(cMsg.event);
		if( IS_PRINT_OUT_MSG )
		{   	 
			PrtMsg( "[MoonLib]: �յ���Ϣ:%s(%u).\n", strEvent,cMsg.event);
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
			PrtMsg( "[MoonLib]: ��Ϣ:%s(%d)������,��Ϊû���ҵ�ƥ�����Ϣ������.\n", strEvent, cMsg.event);		
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
void CMoonMsgDriver::OnOspSyncMsgComing(WPARAM wParam, LPARAM lParam)
{    
    CMessage *pMsg = (CMessage *)wParam;
   
	//��ӡ���
	CString strEvent = CPrintCtrl::GetPrintCtrl()->GetEventDescribe(pMsg->event);
	if( IS_PRINT_OUT_MSG )
	{   	 
		PrtMsg( "[MoonLib]: �յ���Ϣ:%s(%u).\n", strEvent, pMsg->event);
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
        // û��ע�ᴦ��������Ϣ
//         map<u16, CString>::iterator itrName = m_mapEventsName.find(pMsg->event);
//         if(itrName != m_mapEventsName.end())
//         {
//             OspLog(1, "[CncLib]: ��Ϣ:%s(%d)������,��Ϊû���ҵ�ƥ�����Ϣ������.\n",
//                 (LPCTSTR)((*itrName).second), pMsg->event);
//         }
//         else
//         {
//             OspLog(1, "[CncLib]: ��Ϣ:%d������,��Ϊû���ҵ�ƥ�����Ϣ������.\n",
//                 pMsg->event);
//         }
		PrtMsg( "[MoonLib]: ��Ϣ:%s(%d)������,��Ϊû���ҵ�ƥ�����Ϣ������.\n", strEvent, pMsg->event);
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
void CMoonMsgDriver::OnTimer(WPARAM wParam, LPARAM lParam)
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
	//�����ļ���ʱ,��λ,����ͷ��ʼ���·���
    else if (wParam == m_nFileTransferTimer)
    {
        if (m_pbyFile == NULL)
        {
            EndTransFile();
            ::KillTimer(m_hWndOsp, m_nFileTransferTimer);
            return;
        }
        if (m_dwFileCurPos < m_dwFileLength)
        //δ�������ļ����������ͣ�ÿ��30K�ֽ�
        {
            u32 dwLeft = m_dwFileLength - m_dwFileCurPos;
            if (dwLeft > 1024*30)
            {
                dwLeft = 1024*30;
            }
            PostFile(&m_pbyFile[m_dwFileCurPos], dwLeft, m_dwFileFragIndex);
            m_dwFileCurPos = m_dwFileCurPos + 1024 * 30;
            m_dwFileFragIndex++;
        }
        //�������ļ�������ֹͣ��������
        else
        {
            if (m_pbyFile != NULL)
            {
                free(m_pbyFile);
                m_pbyFile = NULL;
            }
            m_dwFileCurPos = 0;
            m_dwFileFragIndex = 0;
            EndTransFile();
            ::KillTimer(m_hWndOsp, m_nFileTransferTimer);
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
LRESULT CALLBACK CMoonMsgDriver::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // ����OSP��Ϣ�ͳ�ʱ��ʱ����Ϣ
    if (CMoonMsgDriver::s_pMsgDriver) 
    {
        if (uMsg == CMoonMsgHandler::WM_OSPMESSAGECOMING) 
        {
            CMoonMsgDriver::s_pMsgDriver->OnOspMessageComing(wParam, lParam);
        }
        else if (uMsg == CMoonMsgHandler::WM_OSPSYNCMSGCOMING)
        {
            CMoonMsgDriver::s_pMsgDriver->OnOspSyncMsgComing(wParam, lParam);            
        }
        else if (uMsg == WM_TIMER) 
        {
            CMoonMsgDriver::s_pMsgDriver->OnTimer(wParam, lParam);
        }
        else if (uMsg == CMoonMsgHandler::WM_REQMTCSTATUS)
        {
            CMoonMsgDriver::s_pMsgDriver->Dump();
        }
		else if (uMsg == CMoonMsgHandler::WM_REQIKEY)
		{
			CMoonMsgDriver::s_pMsgDriver->ReqIKey(wParam);
		}
        else
        {
			if ( CMoonMsgDriver::s_pMsgDriver->m_wndprocOld != NULL )
			{
				return CallWindowProc(CMoonMsgDriver::s_pMsgDriver->m_wndprocOld,
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
void CMoonMsgDriver::ClearWaiting()
{
    m_vWaitingEvents.clear();
    m_pCurDispEvent = NULL;
    m_wCurSendEvent = 0;
}

void CMoonMsgDriver::PostNextCommand()
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

/*=============================================================================
  �� �� ���� CanBeTraceOut
  ��    �ܣ� ��Ϣ������У��жϸ��¼��Ƿ���Ҫ�����ӡ
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� u16 wEvent  ��Ҫ�жϵ��¼�ID
  �� �� ֵ�� BOOL        TRUE��Ҫ�����ӡ
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2004/10/13     3.5		�����                  �淶��
=============================================================================*/
BOOL CMoonMsgDriver::CanBeTraceOut(u16 wEvent) const
{
//    static u32 dwSN = 0;
//    static u32 dwCatalog[MTC_MSGCATALOG_COUNT];
//   //yjj CMtcLib::GetTraceStatus(dwSN, dwCatalog);
//    
//    map<u16, u32>::const_iterator itr = m_mapEventType.find(wEvent);
//    if(itr != m_mapEventType.end())
//    {
//        return dwCatalog[itr->second];
//    }
//    else
//    {
//        return dwCatalog[0];
//    }

	return TRUE;
}

/*=============================================================================
  �� �� ���� TransferFile
  ��    �ܣ� �������Ͷ�ʱ��
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� 
  �� �� ֵ�� u16 
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2004/12/27     3.5		    �����                   ����
=============================================================================*/
u16 CMoonMsgDriver::TransferFile()
{
    if (m_pbyFile == NULL) return 1;
    //�ȷ��͵�һ��
    m_dwFileCurPos = 0;
    m_dwFileFragIndex = 0;
	u16 wResult = 0;
    if (m_dwFileCurPos < m_dwFileLength)
    {
        u32 dwLeft = m_dwFileLength - m_dwFileCurPos;
        if (dwLeft > m_wMaxPackageLen)
        {
            dwLeft = m_wMaxPackageLen;
        }
		TRACE("\n��ʼ�����ļ�");
        wResult = PostFile(&m_pbyFile[m_dwFileCurPos], dwLeft, m_dwFileFragIndex);
        m_dwFileCurPos = m_dwFileCurPos + m_wMaxPackageLen;
        m_dwFileFragIndex++;
    }

	return wResult;
}

void CMoonMsgDriver::StopTransferFile()
{
    m_byTransferStatus = FREE;
	if (m_pbyFile != NULL)
    {
        free(m_pbyFile);
        m_pbyFile = NULL;
    }
    
}

/*�������� PostFile
��    �ܣ� �����ļ���
��    ���� u8 *pbyBuf      �ļ���ָ��
           u32 dwBufLenth  �ļ��γ���
           u32 nIndex      �ļ������
�� �� ֵ�� u16 
˵    ���� */
u16 CMoonMsgDriver::PostFile(u8 *pbyBuf, u32 dwBufLenth, u32 nIndex)
{
/*    //��ͷ���븽��������Э��汾�ţ��ļ���ʶ�����ļ����ͣ��ļ���Ƭ�ţ������ȡ�
	//���壺�ļ�����
    ZeroMemory(&m_cTpMsg, sizeof(CTpMsg));
    //�����ļ�
    TFileTransfer tMsgHead;
    memset( &tMsgHead, 0, sizeof (tMsgHead) );
	tMsgHead.wProtocolIdentifer = MTC_MT_FILE_VER;
	tMsgHead.wFileSliceNo = MTC_MT_MSG_BGN + nIndex;
	tMsgHead.byType = m_wFileType;
	tMsgHead.wDataLen = dwBufLenth + sizeof(TFileTransfer);

	//������Ϣ��
//	m_cKdvMsg.SetEvent(ev_FTSendFileCmd);
	m_cTpMsg.SetBody(&tMsgHead, sizeof( TFileTransfer ));
	m_cTpMsg.CatBody( pbyBuf, dwBufLenth );
 
//	OspPrintf(TRUE, FALSE, "���͵����ݳ���%d\n", dwBufLenth);
	TRACE("���͵����ݳ���%d\n", dwBufLenth);
*/
    u16 wResult = PostMsg(TYPE_TPMSG);
    
    return wResult;
}

/*=============================================================================
  �� �� ���� MappingHelper
  ��    �ܣ� ӳ���¼����ƣ�ͬʱע�ᵽ�¼������������
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� u16 wEvent                 �¼�ID
             const CString& strName     �¼�����
             CATALOG catalog            ���
  �� �� ֵ�� void 
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2004/10/13     3.5		�����                  �淶��
=============================================================================*/
void CMoonMsgDriver::MappingHelper(u16 wEvent, const CString& strName, CATALOG catalog)
{
    m_mapEventsName[wEvent] = strName;
    m_mapEventType[wEvent] = catalog;
}

/*=============================================================================
  �� �� ���� MappingEventName
  ��    �ܣ� ע���¼�
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� 
  �� �� ֵ�� void 
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
 2011/05/10     1.0		    Ф��Ȼ                  ����
=============================================================================*/
void CMoonMsgDriver::MappingEventName()
{
    //��½
	MAPPING_HELPER( OSP_DISCONNECT, _T("OSP_DISCONNECT") );
	MAPPING_HELPER( ev_TpMoonLogin_Req, _T("ev_TpMoonLogin_Req") );
	MAPPING_HELPER( ev_TpMoonLogin_Rsp, _T("ev_TpMoonLogin_Rsp") );
	//�����
	MAPPING_HELPER( ev_TpMoonCamInfo_Nty, _T("ev_TpMoonCamInfo_Nty"));
	MAPPING_HELPER( ev_TpCamSelect_Cmd, _T("ev_TpCamSelect_Cmd"));
	MAPPING_HELPER( ev_TpCamSelect_Ind, _T("ev_TpCamSelect_Ind"));
	MAPPING_HELPER( ev_TpCamSelect_Nty, _T("ev_TpCamSelect_Nty"));
	MAPPING_HELPER( ev_CamParaSynchronize_Cmd, _T("ev_CamParaSynchronize_Cmd"));
	MAPPING_HELPER( ev_CamParaSynchronize_Ind, _T("ev_CamParaSynchronize_Ind"));
	MAPPING_HELPER( ev_TpMechanismSelect_Nty, _T("ev_TpMechanismSelect_Nty"));
	MAPPING_HELPER( ev_TpMechVer_Nty, _T("ev_TpMechVer_Nty"));
	MAPPING_HELPER( ev_TpMechanismSelect_Cmd, _T("ev_TpMechanismSelect_Cmd"));
	MAPPING_HELPER( ev_TpMechanismSelect_Ind, _T("ev_TpMechanismSelect_Ind"));
	MAPPING_HELPER( ev_TpCamSetZoonStart_Cmd, _T("ev_TpCamSetZoonStart_Cmd"));
	MAPPING_HELPER( ev_TpCamSetZoonStart_Ind, _T("ev_TpCamSetZoonStart_Ind"));
	MAPPING_HELPER( ev_TpCamSetZoonStop_Cmd, _T("ev_TpCamSetZoonStop_Cmd"));	
	MAPPING_HELPER( ev_TpCamSetZoonStop_Ind, _T("ev_TpCamSetZoonStop_Ind"));
	MAPPING_HELPER( ev_TpCamSetDrectZoon_Cmd, _T("ev_TpCamSetDrectZoon_Cmd"));	
	MAPPING_HELPER( ev_TpCamSetDrectZoon_Ind, _T("ev_TpCamSetDrectZoon_Ind"));	
	MAPPING_HELPER( ev_TpCamFocusMode_Cmd, _T("ev_TpCamFocusMode_Cmd"));
	MAPPING_HELPER( ev_TpCamFocusMode_Ind, _T("ev_TpCamFocusMode_Ind"));
	MAPPING_HELPER( ev_TpCamFocusNear_Cmd, _T("ev_TpCamFocusNear_Cmd"));
	MAPPING_HELPER( ev_TpCamFocusStop_Cmd, _T("ev_TpCamFocusStop_Cmd"));
	MAPPING_HELPER( ev_TpCamFocusFar_Cmd, _T("ev_TpCamFocusFar_Cmd"));
	MAPPING_HELPER( ev_TpCamFocusNear_Ind, _T("ev_TpCamFocusNear_Ind"));
	MAPPING_HELPER( ev_TpCamFocusStop_Ind, _T("ev_TpCamFocusStop_Ind"));
	MAPPING_HELPER( ev_TpCamFocusFar_Ind, _T("ev_TpCamFocusFar_Ind"));
	MAPPING_HELPER( ev_TpCamExpMode_Cmd, _T("ev_TpCamExpMode_Cmd"));
	MAPPING_HELPER( ev_TpCamExpMode_Ind, _T("ev_TpCamExpMode_Ind"));
	MAPPING_HELPER( ev_TpCamExpAperture_Cmd, _T("ev_TpCamExpAperture_Cmd"));
	MAPPING_HELPER( ev_TpCamExpAperture_Ind, _T("ev_TpCamExpAperture_Ind"));
	MAPPING_HELPER( ev_TpCamExpSOrThShutter_Cmd, _T("ev_TpCamExpSOrThShutter_Cmd"));
	MAPPING_HELPER( ev_TpCamExpSOrThShutter_Ind, _T("ev_TpCamExpSOrThShutter_Ind"));
	MAPPING_HELPER( ev_TpCamExpGain_Cmd, _T("ev_TpCamExpGain_Cmd"));
	MAPPING_HELPER( ev_TpCamExpGain_Ind, _T("ev_TpCamExpGain_Ind"));
	MAPPING_HELPER( ev_TpCamWhiteBalanceMode_Cmd, _T("ev_TpCamWhiteBalanceMode_Cmd"));
	MAPPING_HELPER( ev_TpCamWhiteBalanceMode_Ind, _T("ev_TpCamWhiteBalanceMode_Ind"));
	MAPPING_HELPER( ev_TpCamWhiteBalanceRGain_Cmd, _T("ev_TpCamWhiteBalanceRGain_Cmd"));
	MAPPING_HELPER( ev_TpCamWhiteBalanceRGain_Ind, _T("ev_TpCamWhiteBalanceRGain_Ind"));
	MAPPING_HELPER( ev_TpCamWhiteBalanceBGain_Cmd, _T("ev_TpCamWhiteBalanceBGain_Cmd"));
	MAPPING_HELPER( ev_TpCamWhiteBalanceBGain_Ind, _T("ev_TpCamWhiteBalanceBGain_Ind"));
	MAPPING_HELPER( ev_TpCamImagePara_Cmd, _T("ev_TpCamImagePara_Cmd"));
	MAPPING_HELPER( ev_TpCamImagePara_Ind, _T("ev_TpCamImagePara_Ind"));
	MAPPING_HELPER( ev_TpCamSetGamma_Cmd, _T("ev_TpCamSetGamma_Cmd"));
	MAPPING_HELPER( ev_TpCamSetGamma_Ind, _T("ev_TpCamSetGamma_Ind"));
	MAPPING_HELPER( ev_TpCamBackLight_Cmd, _T("ev_TpCamBackLight_Cmd"));
	MAPPING_HELPER( ev_TpCamBackLight_Ind, _T("ev_TpCamBackLight_Ind"));
	MAPPING_HELPER( ev_TpImageDistortCorrect_Cmd, _T("ev_TpImageDistortCorrect_Cmd"));
	MAPPING_HELPER( ev_TpImageDistortCorrect_Ind, _T("ev_TpImageDistortCorrect_Ind"));	
	MAPPING_HELPER( ev_TpCamReduNoise_Cmd, _T("ev_TpCamReduNoise_Cmd"));
	MAPPING_HELPER( ev_TpCamReduNoise_Ind, _T("ev_TpCamReduNoise_Ind"));
	MAPPING_HELPER( ev_TpSetCam2DNoiseLevle_Cmd, _T("ev_TpSetCam2DNoiseLevle_cmd"));
	MAPPING_HELPER( ev_TpSetCam2DNoiseLevle_Ind, _T("ev_TpSetCam2DNoiseLevle_Ind"));	
	MAPPING_HELPER( ev_TpSetCam3DNoiseLevle_Cmd, _T("ev_TpSetCam3DNoiseLevle_cmd"));
	MAPPING_HELPER( ev_TpSetCam3DNoiseLevle_Ind, _T("ev_TpSetCam3DNoiseLevle_Ind"));
	MAPPING_HELPER( ev_TpCamInitPreset_Cmd, _T("ev_TpCamInitPreset_Cmd"));
	MAPPING_HELPER( ev_TpCamInitPreset_Ind, _T("ev_TpCamInitPreset_Ind"));
	MAPPING_HELPER( ev_tpMoonReboot_Cmd, _T("ev_tpMoonReboot_Cmd"));
	MAPPING_HELPER( ev_TpCamPreSet_Nty, _T("ev_TpCamPreSet_Nty"));
	MAPPING_HELPER( ev_TpCamPreSet_Cmd, _T("ev_TpCamPreSet_Cmd"));
	MAPPING_HELPER( ev_TpCamPreSet_Ind, _T("ev_TpCamPreSet_Ind"));
	MAPPING_HELPER( ev_TpCamPreReset_Cmd, _T("ev_TpCamPreReset_Cmd"));
	MAPPING_HELPER( ev_TpCamPreReset_Ind, _T("ev_TpCamPreReset_Ind"));
	MAPPING_HELPER( ev_TpCamPreModify_Cmd, _T("ev_TpCamPreModify_Cmd"));
	MAPPING_HELPER( ev_TpCamPreModify_Ind, _T("ev_TpCamPreModify_Ind"));
	MAPPING_HELPER( ev_TpCamPreRecall_Cmd, _T("ev_TpCamPreRecall_Cmd"));
	MAPPING_HELPER( ev_TpCamPreRecall_Ind, _T("ev_TpCamPreRecall_Ind"));
	MAPPING_HELPER( ev_TpCamParamUpload_Cmd, _T("ev_TpCamParamUpload_Cmd"));
	MAPPING_HELPER( ev_TpCamParamUpload_Ind, _T("ev_TpCamParamUpload_Ind"));
	MAPPING_HELPER( ev_TpCamParamUpload_Nty, _T("ev_TpCamParamUpload_Nty"));
	MAPPING_HELPER( ev_TpMoonUpgrade_Ind, _T("ev_TpMoonUpgrade_Ind"));
	MAPPING_HELPER( ev_TpMoonUpgrade_Cmd, _T("ev_TpMoonUpgrade_Cmd"));	
	MAPPING_HELPER( ev_CamUpgrade_Cmd, _T("ev_CamUpgrade_Cmd"));	
	MAPPING_HELPER( ev_CamUpgrade_Ind, _T("ev_CamUpgrade_Ind"));
	MAPPING_HELPER( ev_TpCamParamDefault_Cmd, _T("ev_TpCamParamDefault_Cmd"));
	MAPPING_HELPER( ev_TpCamParamDefault_Ind, _T("ev_TpCamParamDefault_Ind"));	
	MAPPING_HELPER( ev_TpSetRefer_Cmd, _T("ev_TpSetRefer_Cmd"));	
	MAPPING_HELPER( ev_TpSetRefer_Ind, _T("ev_TpSetRefer_Ind"));
	MAPPING_HELPER( ev_TpSetRefer_Nty, _T("ev_TpSetRefer_Nty"));	
	MAPPING_HELPER( ev_TpFlatTurn_Cmd, _T("ev_TpFlatTurn_Cmd"));	
	MAPPING_HELPER( ev_TpFlatTurn_Ind, _T("ev_TpFlatTurn_Ind"));
	MAPPING_HELPER( ev_TpFlatTurn_Nty, _T("ev_TpFlatTurn_Nty"));
	MAPPING_HELPER( ev_TpDisortSwitch_Cmd, _T("ev_TpDisortSwitch_Cmd"));
	MAPPING_HELPER( ev_TpDisortSwitch_Ind, _T("ev_TpDisortSwitch_Ind"));
	MAPPING_HELPER( ev_TpSetDisort_Cmd, _T("ev_TpSetDisort_Cmd"));
	MAPPING_HELPER( ev_TpSetDisort_Ind, _T("ev_TpSetDisort_Ind"));
	MAPPING_HELPER( ev_TpCamSnapshot_Cmd, _T("ev_TpCamSnapshot_Cmd"));
	MAPPING_HELPER( ev_TpCamSnapshot_Ind, _T("ev_TpCamSnapshot_Ind"));
	MAPPING_HELPER( ev_TPSetColorRGB_Cmd, _T("ev_TPSetColorRGB_Cmd"));
	MAPPING_HELPER( ev_TPSetColorRGB_Ind, _T("ev_TPSetColorRGB_Ind"));
	MAPPING_HELPER( ev_TPAutoSetColorConstancy_Cmd, _T("ev_TPAutoSetColorConstancy_Cmd"));
	MAPPING_HELPER( ev_TPAutoSetColorConstancy_Ind, _T("ev_TPAutoSetColorConstancy_Ind"));	
	MAPPING_HELPER( ev_TPDirectSetColorRGB_Cmd, _T("ev_TPDirectSetColorRGB_Cmd"));
	MAPPING_HELPER( ev_TPDirectSetColorRGB_Ind, _T("ev_TPDirectSetColorRGB_Ind"));
	MAPPING_HELPER( ev_TPChangeSideRGB_Nty, _T("ev_TPChangeSideRGB_Nty"));
//	MAPPING_HELPER( ev_TPRectInfo_Nty, _T("ev_TPRectInfo_Nty"));
	MAPPING_HELPER( ev_TPChooseRectangle_Cmd, _T("ev_TPChooseRectangle_Cmd"));
	MAPPING_HELPER( ev_TPChooseRectangle_Ind, _T("ev_TPChooseRectangle_Ind"));
	MAPPING_HELPER( ev_TPChangeDistor_Cmd, _T("ev_TPChangeDistor_Cmd"));
	MAPPING_HELPER( ev_TPChangeDistor_Ind, _T("ev_TPChangeDistor_Ind"));
	MAPPING_HELPER( ev_TPDirectSetDistor_Cmd, _T("ev_TPDirectSetDistor_Cmd"));
	MAPPING_HELPER( ev_TPDirectSetDistor_Ind, _T("ev_TPDirectSetDistor_Ind"));	
	MAPPING_HELPER( ev_TPMoonShowRectRegion_Cmd, _T("ev_TPMoonShowRectRegion_Cmd"));
	MAPPING_HELPER( ev_TPMoonShowRectRegion_Ind, _T("ev_TPMoonShowRectRegion_Ind"));
	MAPPING_HELPER( ev_TpColorSwich_Cmd, _T("ev_TpColorSwich_Cmd"));
	MAPPING_HELPER( ev_TpColorSwich_Ind, _T("ev_TpColorSwich_Ind"));
//	MAPPING_HELPER( ev_TPMoonShowRectRegion_Nty, _T("ev_TPMoonShowRectRegion_Nty"));
	MAPPING_HELPER( ev_TpSecDefault_Nty, _T("ev_TpSecDefault_Nty"));
	MAPPING_HELPER( ev_TpSecBoundary_Nty, _T("ev_TpSecBoundary_Nty"));
    MAPPING_HELPER( ev_TpFpgaDelayCorrect_Cmd, _T("ev_TpFpgaDelayCorrect_Cmd"));
    MAPPING_HELPER( ev_TpFpgaDelayCorrect_Ind, _T("ev_TpFpgaDelayCorrect_Ind"));
    MAPPING_HELPER( ev_TpFpgaDelayCorrect_Nty, _T("ev_TpFpgaDelayCorrect_Nty"));

	//ϵͳ����
	MAPPING_HELPER( ev_TpMoonVerInfo_Nty, _T("ev_TpMoonVerInfo_Nty"));
	MAPPING_HELPER( ev_TpCamOutPortInfo_Nty, _T("ev_TpCamOutPortInfo_Nty"));
	MAPPING_HELPER( ev_TpCamImageAdjust_Nty, _T("ev_TpCamImageAdjust_Nty"));
	MAPPING_HELPER( ev_TpMoonCfgEthnet_Ind, _T("ev_TpMoonCfgEthnet_Ind"));
	MAPPING_HELPER( ev_TpCamOutPortInfo_Cmd, _T("ev_TpCamOutPortInfo_Cmd"));
	MAPPING_HELPER( ev_TpCamOutPortInfo_Ind, _T("ev_TpCamOutPortInfo_Ind"));
	MAPPING_HELPER( ev_TpCamImageAdjust_Cmd, _T("ev_TpCamImageAdjust_Cmd"));
	MAPPING_HELPER( ev_TpCamImageAdjust_Ind, _T("ev_TpCamImageAdjust_Ind"));	
	MAPPING_HELPER( ev_TpMoonCfgEthnet_Cmd, _T("ev_TpMoonCfgEthnet_Cmd"));	
	MAPPING_HELPER( ev_TpSetLVDSBaud_Ind, _T("ev_TpSetLVDSBaud_Ind"));
	MAPPING_HELPER( ev_TpSetLVDSBaud_Nty, _T("ev_TpSetLVDSBaud_Nty"));
}

void CMoonMsgDriver::SetInsID( u16 wDstInsID )
{
	m_wInsID = wDstInsID;
}
u16  CMoonMsgDriver::GetInsID()
{
	return m_wInsID;
}

void CMoonMsgDriver::SetAppID( u16 wAppID )
{
	m_wAppID = wAppID;
}

u16 CMoonMsgDriver::GetAppID()
{
	return m_wAppID;
}


void CMoonMsgDriver::SetDesIID( u32 dwDesID )
{
    m_dwDesIID = dwDesID;
}

u32 CMoonMsgDriver::GetDesIID()
{
    return m_dwDesIID;
}


