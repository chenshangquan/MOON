/*=======================================================================
ģ����      : CNS����̨
�ļ���      : CncMsgDriver.cpp
����ļ�    : 
�ļ�ʵ�ֹ���: ��Ϣ������
����        : 
�汾        : V3.0  Copyright(C) 1997-2003 KDC, All rights reserved.
-------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2011/4/30   1.0         Ф��Ȼ        ����
=======================================================================*/
#include "StdAfx.h"
#include "cncmsgdriver.h"
#include "cncmsgrecver.h"
#include "cnclib.h"

////////////////////////////////////////////////////////////////////////////
// CMsgDriver

CCncMsgDriver* CCncMsgDriver::s_pMsgDriver = NULL;

CCncMsgDriver::CCncMsgDriver()
{
    // �����¼����Ʊ�
    MappingEventName();
    // ������Ϣ���մ���
    m_hWndOsp = ::CreateWindowEx(0, _T("Static"), _T("CncMsgDriver"), WS_DISABLED,
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
    m_dwDesIID = MAKEIID(AID_CN_UE, 1);
}

CCncMsgDriver::~CCncMsgDriver()
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
CTpMsg* CCncMsgDriver::GetKdvMsgPtr(BOOL32 bClear)
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
CMessage* CCncMsgDriver::GetCMsgPtr(BOOL32 bClear /* = TRUE */)
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
u16 CCncMsgDriver::PostMsg(u32 dwType)
{  
    u32 dwDesIID = GetDesIID();//MAKEIID(AID_CN_UE, 1/*m_wInsID*/);	 // Ŀ�ģ�CNS
	u32 dwSrcIID = MAKEIID(GetAppID());	         // Դ  ��CNS����̨
	
	u16 wRet = NO_ERROR;
	u16 wEvent = 0;
	if (TYPE_TPMSG == dwType) 
	{  
		//����CMtMsg��Ϣ��
		{
			wRet = m_cTpMsg.Post(dwDesIID, g_CncApp.GetNodeId(), dwSrcIID);
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
        g_CncApp.GetNodeId(), dwSrcIID);

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
u16 CCncMsgDriver::PostCommand(CKdvDispEvent *pDispEvent, u16 *pwWaitEvent,
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
u16 CCncMsgDriver::PostCommand(CKdvDispEvent *pDispEvent, u16 wWaitEvent, u32 dwType, u32 dwTimeOut)
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
void CCncMsgDriver::RegHandler(CKdvDispEvent* const pDispEvnet)
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
void CCncMsgDriver::UnregHandler(CKdvDispEvent* const pDispEvnet)
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
void CCncMsgDriver::ClearHandler()
{
    m_vpDispEvent.clear();
}

void CCncMsgDriver::ClearAllCommand()
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
void CCncMsgDriver::OnOspMessageComing(WPARAM wParam, LPARAM lParam)
{
    // ��OSP�ص��߳���ȡ��Ϣ
    CCncMsgHandler *pHandler = CCncMsgHandler::GetMsgHandler();
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
void CCncMsgDriver::OnOspSyncMsgComing(WPARAM wParam, LPARAM lParam)
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
void CCncMsgDriver::OnTimer(WPARAM wParam, LPARAM lParam)
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
LRESULT CALLBACK CCncMsgDriver::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // ����OSP��Ϣ�ͳ�ʱ��ʱ����Ϣ
    if (CCncMsgDriver::s_pMsgDriver) 
    {
        if (uMsg == CCncMsgHandler::WM_OSPMESSAGECOMING) 
        {
            CCncMsgDriver::s_pMsgDriver->OnOspMessageComing(wParam, lParam);
        }
        else if (uMsg == CCncMsgHandler::WM_OSPSYNCMSGCOMING)
        {
            CCncMsgDriver::s_pMsgDriver->OnOspSyncMsgComing(wParam, lParam);            
        }
        else if (uMsg == WM_TIMER) 
        {
            CCncMsgDriver::s_pMsgDriver->OnTimer(wParam, lParam);
        }
        else if (uMsg == CCncMsgHandler::WM_REQMTCSTATUS)
        {
            CCncMsgDriver::s_pMsgDriver->Dump();
        }
		else if (uMsg == CCncMsgHandler::WM_REQIKEY)
		{
			CCncMsgDriver::s_pMsgDriver->ReqIKey(wParam);
		}
        else
        {
			if ( CCncMsgDriver::s_pMsgDriver->m_wndprocOld != NULL )
			{
				return CallWindowProc(CCncMsgDriver::s_pMsgDriver->m_wndprocOld,
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
void CCncMsgDriver::ClearWaiting()
{
    m_vWaitingEvents.clear();
    m_pCurDispEvent = NULL;
    m_wCurSendEvent = 0;
}

void CCncMsgDriver::PostNextCommand()
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
BOOL CCncMsgDriver::CanBeTraceOut(u16 wEvent) const
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
u16 CCncMsgDriver::TransferFile()
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

void CCncMsgDriver::StopTransferFile()
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
u16 CCncMsgDriver::PostFile(u8 *pbyBuf, u32 dwBufLenth, u32 nIndex)
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
void CCncMsgDriver::MappingHelper(u16 wEvent, const CString& strName, CATALOG catalog)
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
void CCncMsgDriver::MappingEventName()
{
    //��½
	MAPPING_HELPER( OSP_DISCONNECT, _T("OSP_DISCONNECT") );
	MAPPING_HELPER( ev_CnLogin_Req, _T("ev_CnLogin_Req") );
	MAPPING_HELPER( ev_CnLogin_Rsp, _T("ev_CnLogin_Rsp") );
	MAPPING_HELPER( ev_CnList_Nty, _T("ev_CnList_Nty") );
	MAPPING_HELPER( ev_CnLoginIns_Req, _T("ev_CnLoginIns_Req") );
	MAPPING_HELPER( ev_CnLoginIns_Rsp, _T("ev_CnLoginIns_Rsp") );
	MAPPING_HELPER( ev_CNSLoginByOther_Notify, _T("ev_CNSLoginByOther_Notify") );
		
	//����
	MAPPING_HELPER( ev_tppRegisterRs_Req, _T("ev_tppRegisterRs_Req") );
	MAPPING_HELPER( ev_tppRegisterRs_Rsp, _T("ev_tppRegisterRs_Rsp") );
	MAPPING_HELPER( ev_tpRegisterResult_Nty, _T("ev_tpRegisterResult_Nty") );
	MAPPING_HELPER( ev_tpRegisterResultFail_Nty, _T("ev_tpRegisterResultFail_Nty") );	
	MAPPING_HELPER( ev_CnCfgCnsInfo_Cmd, _T("ev_CnCfgCnsInfo_Cmd") );
	MAPPING_HELPER( ev_CnCfgCnsInfo_Ind, _T("ev_CnCfgCnsInfo_Ind") );
	MAPPING_HELPER( ev_CnCfgEthnet_Cmd, _T("ev_CnCfgEthnet_Cmd") );
	MAPPING_HELPER( ev_CnCfgEthnet_Ind, _T("ev_CnCfgEthnet_Ind") );
	MAPPING_HELPER( ev_CnSetMainRoom_Cmd, _T("ev_CnSetMainRoom_Cmd") );
	MAPPING_HELPER( ev_CnSetMainRoom_Ind, _T("ev_CnSetMainRoom_Ind") );
	//NAT����
	MAPPING_HELPER( ev_tppNatReg_Nty, _T("ev_tppNatReg_Nty"));
	MAPPING_HELPER( ev_tppNatReg_Cmd, _T("ev_tppNatReg_Cmd"));
	//ע����Ϣ
	MAPPING_HELPER( ev_tppGetRegInfo_Req, _T("ev_tppGetRegInfo_Req") );
	MAPPING_HELPER( ev_tppGetRegInfo_Rsp, _T("ev_tppGetRegInfo_Rsp") );
	MAPPING_HELPER( ev_tppGetRegInfo_Nty, _T("ev_tppGetRegInfo_Nty") );
    MAPPING_HELPER( ev_tppGetRegGKInfo_Nty, _T("ev_tppGetRegGKInfo_Nty") );
    MAPPING_HELPER( ev_tppGetRegInfoCNS_Rsp, _T("ev_tppGetRegInfoCNS_Rsp") );
    MAPPING_HELPER( ev_tppGetRegInfoUMS_Rsp, _T("ev_tppGetRegInfoUMS_Rsp") );
	
	MAPPING_HELPER( ev_CnsGKReg_Cmd, _T("ev_CnsGKReg_Cmd") );
	MAPPING_HELPER( ev_CnsGKReg_Nty, _T("ev_CnsGKReg_Nty") );
	MAPPING_HELPER( ev_CnsGKReg_Ret, _T("ev_CnsGKReg_Ret") );
		
	//���
	MAPPING_HELPER( ev_CnConfState_Nty, _T("ev_CnConfState_Nty") );

    MAPPING_HELPER( ev_TppHangupConf_Cmd, _T("ev_TppHangupConf_Cmd") );

    MAPPING_HELPER( ev_TppConfApplySpeaker_Cmd, _T("ev_TppConfApplySpeaker_Cmd") );

    MAPPING_HELPER( ev_TppConfApplySpeaker_Nty, _T("ev_TppConfApplySpeaker_Nty") );

    MAPPING_HELPER( ev_TppChairConfInfo_Nty, _T("ev_TppChairConfInfo_Nty") );

    MAPPING_HELPER( ev_TppAudMixStatus_Nty, _T("ev_TppAudMixStatus_Nty") );

    MAPPING_HELPER( ev_TppHangupCns_Ind, _T("ev_TppHangupCns_Ind") );
    
    MAPPING_HELPER( ev_TppHangupCns_Cmd, _T("ev_TppHangupCns_Cmd") );

    MAPPING_HELPER( ev_TppInviteCnsByEpId_Ind, _T("ev_TppInviteCnsByEpId_Ind") );

    MAPPING_HELPER( ev_TppInviteCnsByEpId_Cmd, _T("ev_TppInviteCnsByEpId_Cmd") );

    MAPPING_HELPER( ev_TppInviteCnsByAlias_Ind, _T("ev_TppInviteCnsByAlias_Ind") );

    MAPPING_HELPER( ev_TppInviteCnsByAlias_Cmd, _T("ev_TppInviteCnsByAlias_Cmd") );

    MAPPING_HELPER( ev_TppConfQuiet_Nty, _T("ev_TppConfQuiet_Nty") );

    MAPPING_HELPER( ev_TppConfQuiet_Ind, _T("ev_TppConfQuiet_Ind") );

    MAPPING_HELPER( ev_TppConfMute_Nty, _T("ev_TppConfMute_Nty") );

    MAPPING_HELPER( ev_TppConfMute_Ind, _T("ev_TppConfMute_Ind") );

    MAPPING_HELPER( ev_TppConfMute_Cmd, _T("ev_TppConfMute_Cmd") );
    
    MAPPING_HELPER( ev_TppConfApplySpeaker_Ind, _T("ev_TppConfApplySpeaker_Ind") );
    
	MAPPING_HELPER( ev_TppModuleterminalLeftConf, _T("ev_TppModuleterminalLeftConf") );
	MAPPING_HELPER( ev_TppModuleTerminalJoinConf, _T("ev_TppModuleTerminalJoinConf") );

    MAPPING_HELPER( ev_TppConfApplySpeaker_Cmd, _T("ev_TppConfApplySpeaker_Cmd") );

    MAPPING_HELPER( ev_TppConfStopDual_Cmd, _T("ev_TppConfStopDual_Cmd") );

    MAPPING_HELPER( ev_TppConfStartDual_Cmd, _T("ev_TppConfStartDual_Cmd") );

    MAPPING_HELPER( ev_TppConfStartDual_Ind, _T("ev_TppConfStartDual_Ind") );

    MAPPING_HELPER( ev_TppConfStopDual_Ind, _T("ev_TppConfStopDual_Ind") );

    MAPPING_HELPER( ev_TppConfDualEp_Nty, _T("ev_TppConfDualEp_Nty") );
 
    MAPPING_HELPER( ev_TppUmsCommonReasonToUI_Ind, _T("ev_TppUmsCommonReasonToUI_Ind") );  

	MAPPING_HELPER( ev_tppInputVolumeCmd , _T("ev_tppInputVolumeCmd ") );
	MAPPING_HELPER( ev_tppOutputVolumeCmd , _T("ev_tppOutputVolumeCmd ") );
	MAPPING_HELPER( ev_tppInputVolumeInd, _T("ev_tppInputVolumeInd") );
	MAPPING_HELPER( ev_tppOutputVolumeInd, _T("ev_tppOutputVolumeInd") );
	MAPPING_HELPER( ev_tppMute_Cmd , _T("ev_tppMute_Cmd ") );
	MAPPING_HELPER( ev_tppQuiet_Cmd , _T("ev_tppQuiet_Cmd ") );
	MAPPING_HELPER( ev_tppQuietInd, _T("ev_tppQuietInd") );
	MAPPING_HELPER( ev_tppMuteInd, _T("ev_tppMuteInd") );
	MAPPING_HELPER( ev_CnSetInnerSpeaker_Cmd, _T("ev_CnSetInnerSpeaker_Cmd") );
	MAPPING_HELPER( ev_CnSetInnerSpeaker_Ind, _T("ev_CnSetInnerSpeaker_Ind") );
	MAPPING_HELPER( ev_CnYouAreSeeing_Ind, _T("ev_CnYouAreSeeing_Ind"), 3 );
	MAPPING_HELPER( ev_tpRoomOnline_Nty, _T("ev_tpRoomOnline_Nty") );
	MAPPING_HELPER( ev_tpRoomOffline_Nty, _T("ev_tpRoomOffline_Nty") );
	
	MAPPING_HELPER( ev_CnStartPoll_Cmd, _T("ev_CnStartPoll_Cmd") );
	MAPPING_HELPER( ev_CnStartPoll_Ind, _T("ev_CnStartPoll_Ind") );	
	MAPPING_HELPER( ev_CnStopPoll_Cmd, _T("ev_CnStopPoll_Cmd") );
	MAPPING_HELPER( ev_CnStopPoll_Ind, _T("ev_CnStopPoll_Ind") ); 
	MAPPING_HELPER( ev_CnPollStatus_Nty, _T("ev_CnPollStatus_Nty") ); 
	MAPPING_HELPER( ev_CnSingleView_Cmd, _T("ev_CnSingleView_Cmd") );
	MAPPING_HELPER( ev_CnSingleView_Ind, _T("ev_CnSingleView_Ind") );
	MAPPING_HELPER( ev_CnCancelSingleView_Cmd, _T("ev_CnCancelSingleView_Cmd") );
	MAPPING_HELPER( ev_CnCancelSingleView_Ind, _T("ev_CnCancelSingleView_Ind") );
	MAPPING_HELPER( ev_TppStartDual_Cmd, _T("ev_TppStartDual_Cmd") );
	MAPPING_HELPER( ev_TppStartDual_Ind, _T("ev_TppStartDual_Ind") );
	MAPPING_HELPER( ev_TppStopDual_Cmd, _T("ev_TppStopDual_Cmd") );
	MAPPING_HELPER( ev_TppStopDual_Ind, _T("ev_TppStopDual_Ind") );
	MAPPING_HELPER( ev_TppIsDual_Nty, _T("ev_TppIsDual_Nty") );	
    MAPPING_HELPER( ev_TppIsRcvDual_Nty, _T("ev_TppIsRcvDual_Nty") );
	MAPPING_HELPER( ev_CnActivePos_Nty, _T("ev_CnActivePos_Nty") );
	MAPPING_HELPER( ev_tpCnRoomDualOffline_Nty, _T("ev_tpCnRoomDualOffline_Nty") );

	MAPPING_HELPER( ev_TppMakeCall_Cmd, _T("ev_TppMakeCall_Cmd") );
	MAPPING_HELPER( ev_TppHangUp_Cmd, _T("ev_TppHangUp_Cmd") );
	MAPPING_HELPER( ev_TppHangUp_Ind, _T("ev_TppHangUp_Ind") );
	MAPPING_HELPER( ev_CnConfEpList_Nty, _T("ev_CnConfEpList_Nty") );

    MAPPING_HELPER( ev_CnPosAllStatus_Nty, _T("ev_CnPosAllStatus_Nty"), 3 );

    MAPPING_HELPER( ev_TppConfApplySpeaker_Cmd, _T("ev_TppConfApplySpeaker_Cmd") );  

    MAPPING_HELPER( ev_TppDualRcvInterrupt_Nty, _T("ev_TppDualRcvInterrupt_Nty") );
    

	//˫��
	MAPPING_HELPER( ev_TppAddDualRcvAddr_Cmd, _T("ev_TppAddDualRcvAddr_Cmd") );
    MAPPING_HELPER( ev_TppDelDualRcvAddr_Cmd, _T("ev_TppDelDualRcvAddr_Cmd") );
    MAPPING_HELPER( ev_TppPadDualKeyFrame_Req, _T("ev_TppPadDualKeyFrame_Req") );
    MAPPING_HELPER( ev_TppAddDualRcvAddr_Ind, _T("ev_TppAddDualRcvAddr_Ind") );
    MAPPING_HELPER( ev_TppDelDualRcvAddr_Ind, _T("ev_TppDelDualRcvAddr_Ind") );
	
    MAPPING_HELPER( ev_TppSelDualView_Cmd, _T("ev_TppSelDualView_Cmd") );
    MAPPING_HELPER( ev_TppSelDualView_Ind, _T("ev_TppSelDualView_Ind") );
	MAPPING_HELPER( ev_TppCancelSelDualView_Cmd, _T("ev_TppCancelSelDualView_Cmd") );
    MAPPING_HELPER( ev_TppCancelSelDualView_Ind, _T("ev_TppCancelSelDualView_Ind") );
    	
    MAPPING_HELPER( ev_CnViewLocal_Cmd, _T("ev_CnViewLocal_Cmd") );
    MAPPING_HELPER( ev_CnViewLocal_Ind, _T("ev_CnViewLocal_Ind") );
	
    MAPPING_HELPER( ev_CnCancelViewLocal_Cmd, _T("ev_CnCancelViewLocal_Cmd") );
    MAPPING_HELPER( ev_CnCancelViewLocal_Ind, _T("ev_CnCancelViewLocal_Ind") );

    //˫��Դ����	
    MAPPING_HELPER( ev_TppSetDualInputPortName_Cmd, _T("ev_TppSetDualInputPortName_Cmd") );
    MAPPING_HELPER( ev_TppSetDualInputPortName_Ind, _T("ev_TppSetDualInputPortName_Ind") );
    MAPPING_HELPER( ev_TppSelDualInputPort_Cmd, _T("ev_TppSelDualInputPort_Cmd") );
    MAPPING_HELPER( ev_TppSelDualInputPort_Ind, _T("ev_TppSelDualInputPort_Ind") );
    MAPPING_HELPER( ev_TppCurrentVgaInfo_Nty, _T("ev_TppCurrentVgaInfo_Nty") );
    MAPPING_HELPER( ev_TppConfVgaInfo_Nty, _T("ev_TppConfVgaInfo_Nty") );

	//ϵͳ��������
	MAPPING_HELPER( ev_Cn_SetSleepInfoCmd, _T("ev_Cn_SetSleepInfoCmd") );
	MAPPING_HELPER( ev_Cn_SetSleepInfoInd, _T("ev_Cn_SetSleepInfoInd") );
	MAPPING_HELPER( ev_TppSetDualInputPortName_Cmd, _T("ev_TppSetDualInputPortName_Cmd") );

	//����
	MAPPING_HELPER( ev_TppConfAMixUpdate_Cmd, _T("ev_TppConfAMixUpdate_Cmd") );
	MAPPING_HELPER( ev_TppConfAMixUpdate_Ind, _T("ev_TppConfAMixUpdate_Ind") );	
	MAPPING_HELPER( ev_TppConfAMixUpdate_Nty, _T("ev_TppConfAMixUpdate_Nty") );
	MAPPING_HELPER( ev_TppAudMixDisListOpr_Cmd, _T("ev_TppAudMixDisListOpr_Cmd") );
    MAPPING_HELPER( ev_TppAudMixDisListOpr_Ind, _T("ev_TppAudMixDisListOpr_Ind") );

    //����ϵͳʱ��
    MAPPING_HELPER( ev_CnSetSysTime_Cmd, _T("ev_CnSetSysTime_Cmd") );
    MAPPING_HELPER( ev_CnGetSysTime_Req, _T("ev_CnGetSysTime_Req") );
    MAPPING_HELPER( ev_CnGetSysTime_Rsp, _T("ev_CnGetSysTime_Rsp") );  

	//��ַ��
	MAPPING_HELPER( ADDRBOOK_REGISTER_REQ, _T("ADDRBOOK_REGISTER_REQ") );
    MAPPING_HELPER( ADDRBOOK_REGISTER_ACK, _T("ADDRBOOK_REGISTER_ACK") );
    MAPPING_HELPER( ADDRBOOK_REGISTER_NACK, _T("ADDRBOOK_REGISTER_NACK"));
    MAPPING_HELPER( ADDRBOOK_UNREG_REQ, _T("ADDRBOOK_UNREG_REQ") );
	MAPPING_HELPER( ADDRBOOK_UNREG_CMD, _T("ADDRBOOK_UNREG_CMD") );
    MAPPING_HELPER( ADDRBOOK_SAVE_ACK, _T("ADDRBOOK_SAVE_ACK") );
    MAPPING_HELPER( ADDRBOOK_SAVE_NACK, _T("ADDRBOOK_SAVE_NACK") );
    MAPPING_HELPER( ADDRBOOK_ADD_ENTRY_REQ, _T("ADDRBOOK_ADD_ENTRY_REQ") );
    MAPPING_HELPER( ADDRBOOK_ADD_ENTRY_ACK, _T("ADDRBOOK_ADD_ENTRY_ACK") );
    MAPPING_HELPER( ADDRBOOK_ADD_ENTRY_NACK, _T("ADDRBOOK_ADD_ENTRY_NACK") );
    MAPPING_HELPER( ADDRBOOK_ADD_MULSETENTRY_REQ, _T("ADDRBOOK_ADD_MULSETENTRY_REQ") );
    MAPPING_HELPER( ADDRBOOK_ADD_MULSETENTRY_ACK, _T("ADDRBOOK_ADD_MULSETENTRY_ACK") );
    MAPPING_HELPER( ADDRBOOK_ADD_MULSETENTRY_NACK, _T("ADDRBOOK_ADD_MULSETENTRY_NACK") );
    MAPPING_HELPER( ADDRBOOK_DEL_ENTRY_REQ, _T("ADDRBOOK_DEL_ENTRY_REQ") );
    MAPPING_HELPER( ADDRBOOK_DEL_ENTRY_ACK, _T("ADDRBOOK_DEL_ENTRY_ACK") );
    MAPPING_HELPER( ADDRBOOK_DEL_ENTRY_NACK, _T("ADDRBOOK_DEL_ENTRY_NACK") );
    MAPPING_HELPER( ADDRBOOK_DEL_MULSETENTRY_REQ, _T("ADDRBOOK_DEL_MULSETENTRY_REQ") );
    MAPPING_HELPER( ADDRBOOK_DEL_MULSETENTRY_ACK, _T("ADDRBOOK_DEL_MULSETENTRY_ACK") );
    MAPPING_HELPER( ADDRBOOK_DEL_MULSETENTRY_NACK, _T("ADDRBOOK_DEL_MULSETENTRY_NACK") );
    MAPPING_HELPER( ADDRBOOK_ADD_ENTRYTOMULSET_REQ, _T("ADDRBOOK_ADD_ENTRYTOMULSET_REQ") );
    MAPPING_HELPER( ADDRBOOK_ADD_ENTRYTOMULSET_ACK, _T("ADDRBOOK_ADD_ENTRYTOMULSET_ACK") );
    MAPPING_HELPER( ADDRBOOK_ADD_ENTRYTOMULSET_NACK, _T("ADDRBOOK_ADD_ENTRYTOMULSET_NACK") );
    MAPPING_HELPER( ADDRBOOK_DEL_ENTRYFRMULSET_REQ, _T("ADDRBOOK_DEL_ENTRYFRMULSET_REQ") );
    MAPPING_HELPER( ADDRBOOK_DEL_ENTRYFRMULSET_ACK, _T("ADDRBOOK_DEL_ENTRYFRMULSET_ACK") );
    MAPPING_HELPER( ADDRBOOK_DEL_ENTRYFRMULSET_NACK, _T("ADDRBOOK_DEL_ENTRYFRMULSET_NACK") );
    MAPPING_HELPER( ADDRBOOK_MODIFYENTRY_REQ, _T("ADDRBOOK_MODIFYENTRY_REQ") );
    MAPPING_HELPER( ADDRBOOK_MODIFYENTRY_ACK, _T("ADDRBOOK_MODIFYENTRY_ACK") );
    MAPPING_HELPER( ADDRBOOK_MODIFYENTRY_NACK, _T("ADDRBOOK_MODIFYENTRY_NACK") );
    MAPPING_HELPER( ADDRBOOK_MODIFYMULSETENTRY_REQ, _T("ADDRBOOK_MODIFYMULSETENTRY_REQ") );
    MAPPING_HELPER( ADDRBOOK_MODIFYMULSETENTRY_ACK, _T("ADDRBOOK_MODIFYMULSETENTRY_ACK") );
    MAPPING_HELPER( ADDRBOOK_MODIFYMULSETENTRY_NACK, _T("ADDRBOOK_MODIFYMULSETENTRY_NACK") );
	MAPPING_HELPER( ADDRBOOK_ADD_MULSETTOMULSET_REQ, _T("ADDRBOOK_ADD_MULSETTOMULSET_REQ") );
	MAPPING_HELPER( ADDRBOOK_ADD_MULSETTOMULSET_ACK, _T("ADDRBOOK_ADD_MULSETTOMULSET_ACK") );
	MAPPING_HELPER( ADDRBOOK_ADD_MULSETTOMULSET_NACK, _T("ADDRBOOK_ADD_MULSETTOMULSET_NACK") );
	MAPPING_HELPER( ADDRBOOK_DEL_MULSETFROMMULSET_REQ, _T("ADDRBOOK_DEL_MULSETFROMMULSET_REQ") );
	MAPPING_HELPER( ADDRBOOK_DEL_MULSETFROMMULSET_ACK, _T("ADDRBOOK_DEL_MULSETFROMMULSET_ACK") );
	MAPPING_HELPER( ADDRBOOK_DEL_MULSETFROMMULSET_NACK, _T("ADDRBOOK_DEL_MULSETFROMMULSET_NACK") );
	
    MAPPING_HELPER( ADDRBOOK_GETENTRYNUM_REQ, _T("ADDRBOOK_GETENTRYNUM_REQ") );
    MAPPING_HELPER( ADDRBOOK_GETENTRYNUM_ACK, _T("ADDRBOOK_GETENTRYNUM_ACK") );
    MAPPING_HELPER( ADDRBOOK_GETENTRYNUM_NACK, _T("ADDRBOOK_GETENTRYNUM_NACK") );
    MAPPING_HELPER( ADDRBOOK_GETENTRY_REQ, _T("ADDRBOOK_GETENTRY_REQ"), 3 );
    MAPPING_HELPER( ADDRBOOK_GETENTRY_ACK, _T("ADDRBOOK_GETENTRY_ACK"), 3 );
    MAPPING_HELPER( ADDRBOOK_GETENTRY_NACK, _T("ADDRBOOK_GETENTRY_NACK") );
    MAPPING_HELPER( ADDRBOOK_GETMULSETENTRYNUM_REQ, _T("ADDRBOOK_GETMULSETENTRYNUM_REQ") );
    MAPPING_HELPER( ADDRBOOK_GETMULSETENTRYNUM_ACK, _T("ADDRBOOK_GETMULSETENTRYNUM_ACK") );
    MAPPING_HELPER( ADDRBOOK_GETMULSETENTRYNUM_NACK, _T("ADDRBOOK_GETMULSETENTRYNUM_NACK") );
    MAPPING_HELPER( ADDRBOOK_GETMULSETENTRY_REQ, _T("ADDRBOOK_GETMULSETENTRY_REQ") );
    MAPPING_HELPER( ADDRBOOK_GETMULSETENTRY_ACK, _T("ADDRBOOK_GETMULSETENTRY_ACK") );
    MAPPING_HELPER( ADDRBOOK_GETMULSETENTRY_NACK, _T("ADDRBOOK_GETMULSETENTRY_NACK") );
	MAPPING_HELPER( ADDRBOOK_GETMULSETRELATIONNUM_REQ, _T("ADDRBOOK_GETMULSETRELATIONNUM_REQ") );
	MAPPING_HELPER( ADDRBOOK_GETMULSETRELATIONNUM_ACK, _T("ADDRBOOK_GETMULSETRELATIONNUM_ACK") );
	MAPPING_HELPER( ADDRBOOK_GETMULSETRELATIONNUM_NACK, _T("ADDRBOOK_GETMULSETRELATIONNUM_NACK") );
	MAPPING_HELPER( ADDRBOOK_GETMULSETRELATION_REQ, _T("ADDRBOOK_GETMULSETRELATION_REQ") );
	MAPPING_HELPER( ADDRBOOK_GETMULSETRELATION_ACK, _T("ADDRBOOK_GETMULSETRELATION_ACK") );
	MAPPING_HELPER( ADDRBOOK_GETMULSETRELATION_NACK, _T("ADDRBOOK_GETMULSETRELATION_NACK") );
    MAPPING_HELPER( ADDRBOOK_REFRESHENTRY_NOTIF, _T("ADDRBOOK_REFRESHENTRY_NOTIF") );
    MAPPING_HELPER( ADDRBOOK_DELENTRY_NOTIF, _T("ADDRBOOK_DELENTRY_NOTIF") );
    MAPPING_HELPER( ADDRBOOK_REFRESHMULSETENTRY_NOTIF, _T("ADDRBOOK_REFRESHMULSETENTRY_NOTIF") );
    MAPPING_HELPER( ADDRBOOK_DELMULSETENTRY_NOTIF, _T("ADDRBOOK_DELMULSETENTRY_NOTIF") );
	MAPPING_HELPER( ADDRBOOK_REFRESHMULSETRELATION_NOTIF, _T("ADDRBOOK_REFRESHMULSETRELATION_NOTIF") );	
    MAPPING_HELPER( ADDRBOOK_UPDATEINMT_CMD, _T("ADDRBOOK_UPDATEINMT_CMD") );
    MAPPING_HELPER( ADDRBOOK_UPDATEOUTMT_CMD, _T("ADDRBOOK_UPDATEOUTMT_CMD") );
	MAPPING_HELPER( ev_cns_cncAddrBookNty, _T("ev_cns_cncAddrBookNty") );

  
	//�û�����
	MAPPING_HELPER( ev_CNSAddUserReq, _T("ev_CNSAddUserReq") );
	MAPPING_HELPER( ev_CNSAddUserRet, _T("ev_CNSAddUserRet") );
	MAPPING_HELPER( ev_CNSDelUserReq, _T("ev_CNSDelUserReq") );
	MAPPING_HELPER( ev_CNSDelUserRet, _T("ev_CNSDelUserRet") );
	MAPPING_HELPER( ev_CNSChangePWDReq, _T("ev_CNSChangePWDReq") );
	MAPPING_HELPER( ev_CNSChangePWDRet, _T("ev_CNSChangePWDRet") );
	MAPPING_HELPER( ev_CNSAddUser_Notify, _T("ev_CNSAddUser_Notify") );
	MAPPING_HELPER( ev_CNSDelUser_Notify, _T("ev_CNSDelUser_Notify") );
	MAPPING_HELPER( ev_CNSUpdateUser_Notify, _T("ev_CNSUpdateUser_Notify") );

	//�п�
    MAPPING_HELPER( ev_Cn_Sch_Power_Cmd, _T("ev_Cn_Sch_Power_Cmd") );
    MAPPING_HELPER( ev_Cn_Sch_Power_Ind, _T("ev_Cn_Sch_Power_Ind") );
    MAPPING_HELPER( ev_Cn_Sch_Power_FB_Notify, _T("ev_Cn_Sch_Power_FB_Notify") );
    MAPPING_HELPER( ev_Cn_Sch_Light_Cmd, _T("ev_Cn_Sch_Light_Cmd") );
    MAPPING_HELPER( ev_Cn_Sch_Light_Ind, _T("ev_Cn_Sch_Light_Ind") ); 
    MAPPING_HELPER( ev_Cn_Sch_Light_FB_Notify, _T("ev_Cn_Sch_Light_FB_Notify") );
    MAPPING_HELPER( ev_Cn_Sch_MidLight_Cmd, _T("ev_Cn_Sch_MidLight_Cmd") );
    MAPPING_HELPER( ev_Cn_Sch_MidLight_Ind, _T("ev_Cn_Sch_MidLight_Ind") );
    MAPPING_HELPER( ev_Cn_Sch_ScrLight_Cmd, _T("ev_Cn_Sch_ScrLight_Cmd") ); 
    MAPPING_HELPER( ev_Cn_Sch_ScrLight_Ind, _T("ev_Cn_Sch_ScrLight_Ind") );
    MAPPING_HELPER( ev_Cn_Sch_Temp_FB_Notify, _T("ev_Cn_Sch_Temp_FB_Notify") );
    MAPPING_HELPER( ev_cns_centreSchStateNty, _T("ev_cns_centreSchStateNty") ); 
    
    MAPPING_HELPER( ev_cns_centreselectTV_cmd, _T("ev_cns_centreselectTV_cmd") );
    MAPPING_HELPER( ev_cns_centreselectTV_Ind, _T("ev_cns_centreselectTV_Ind") );
    MAPPING_HELPER( ev_cns_centreTVMode_cmd, _T("ev_cns_centreTVMode_cmd") ); 
    MAPPING_HELPER( ev_cns_centreTVMode_Ind, _T("ev_cns_centreTVMode_Ind") );   
    MAPPING_HELPER( ev_cns_centreTVAudVisMode_cmd, _T("ev_cns_centreTVAudVisMode_cmd") );
    MAPPING_HELPER( ev_cns_centreTVAudVisMode_Ind, _T("ev_cns_centreTVAudVisMode_Ind") );
    MAPPING_HELPER( ev_cns_centreTVDisMode_cmd, _T("ev_cns_centreTVDisMode_cmd") );
    MAPPING_HELPER( ev_cns_centreTVDisMode_Ind, _T("ev_cns_centreTVDisMode_Ind") );
    MAPPING_HELPER( ev_cns_centreTVInpSelect_cmd, _T("ev_cns_centreTVInpSelect_cmd") );
    MAPPING_HELPER( ev_cns_centreTVInpSelect_Ind, _T("ev_cns_centreTVInpSelect_Ind") );
    MAPPING_HELPER( ev_cns_centreTVStateNty, _T("ev_cns_centreTVStateNty") );

    MAPPING_HELPER( ev_Cn_DCamPower_Cmd, _T("ev_Cn_DCamPower_Cmd") );
    MAPPING_HELPER( ev_Cn_DCamAFMode_Cmd, _T("ev_Cn_DCamAFMode_Cmd") );
    MAPPING_HELPER( ev_Cn_DCamWBMode_Cmd, _T("ev_Cn_DCamWBMode_Cmd") );
    MAPPING_HELPER( ev_Cn_DCamZoom_Cmd, _T("ev_Cn_DCamZoom_Cmd") );
    MAPPING_HELPER( ev_Cn_DCamPreset_Cmd, _T("ev_Cn_DCamPreset_Cmd") );
    MAPPING_HELPER( ev_Cn_DCamRecall_Cmd, _T("ev_Cn_DCamRecall_Cmd") );
    MAPPING_HELPER( ev_Cn_DCamPower_Ind, _T("ev_Cn_DCamPower_Ind") );
    MAPPING_HELPER( ev_Cn_DCamAFMode_Ind, _T("ev_Cn_DCamAFMode_Ind") );
    MAPPING_HELPER( ev_Cn_DCamWBMode_Ind, _T("ev_Cn_DCamWBMode_Ind") );
    MAPPING_HELPER( ev_Cn_DCamZoom_Ind, _T("ev_Cn_DCamZoom_Ind") );
    MAPPING_HELPER( ev_Cn_DCamPreset_Ind, _T("ev_Cn_DCamPreset_Ind") );
    MAPPING_HELPER( ev_Cn_DCamRecall_Ind, _T("ev_Cn_DCamRecall_Ind") );
    MAPPING_HELPER( ev_cns_centreDCamStateNty, _T("ev_cns_centreDCamStateNty") );

    MAPPING_HELPER( ev_cns_centreACStateNty, _T("ev_cns_centreACStateNty") );
    MAPPING_HELPER( ev_Cn_CentreSetACTempCmd, _T("ev_Cn_CentreSetACTempCmd") );
    MAPPING_HELPER( ev_Cn_CentreSetACTempInd, _T("ev_Cn_CentreSetACTempInd") );
    MAPPING_HELPER( ev_Cn_CentreSetACModeCmd, _T("ev_Cn_CentreSetACModeCmd") );
    MAPPING_HELPER( ev_Cn_CentreSetACModeInd, _T("ev_Cn_CentreSetACModeInd") );
    MAPPING_HELPER( ev_Cn_CentreSetACAirVolCmd, _T("ev_Cn_CentreSetACAirVolCmd") );
    MAPPING_HELPER( ev_Cn_CentreSetAirVolInd, _T("ev_Cn_CentreSetAirVolInd") );
	MAPPING_HELPER( ev_Cn_CentreSetACPowerCmd, _T("ev_Cn_CentreSetACPowerCmd") );
	MAPPING_HELPER( ev_Cn_CentreSetACPowerInd, _T("ev_Cn_CentreSetACPowerInd") );
	MAPPING_HELPER( ev_cns_centreSelectAC_Cmd, _T("ev_cns_centreSelectAC_Cmd"));
	MAPPING_HELPER( ev_cns_centreSelectAC_Ind, _T("ev_cns_centreSelectAC_Ind"));
	MAPPING_HELPER( ev_cns_centreACCopyCmd, _T("ev_cns_centreACCopyCmd"));
	MAPPING_HELPER( ev_cns_centreACCopyInd, _T("ev_cns_centreACCopyInd"));
	MAPPING_HELPER( ev_Cn_CamPowerStateNty, _T("ev_Cn_CamPowerStateNty") );
	MAPPING_HELPER( ev_CnCfgDisplay_Cmd, _T("ev_CnCfgDisplay_Cmd") );
	MAPPING_HELPER( ev_CnCfgDisplay_Ind, _T("ev_CnCfgDisplay_Ind") );

	//ϵͳ��Ϣ
	MAPPING_HELPER( ev_tppGetSysInfo_Req, _T("ev_tppGetSysInfo_Req") );
	MAPPING_HELPER( ev_tppGetSysInfo_Rsp, _T("ev_tppGetSysInfo_Rsp") );
	MAPPING_HELPER( ev_tppGetSysInfo_Nty, _T("ev_tppGetSysInfo_Nty"), 3 );	

	//TPad�б�
	MAPPING_HELPER( ev_tppGetTPadIpList_Req, _T("ev_tppGetTPadIpList_Req") );
	MAPPING_HELPER( ev_tppGetTPadIpList_Rsp, _T("ev_tppGetTPadIpList_Rsp") );
	MAPPING_HELPER( ev_tppGetTPadIpList_Nty, _T("ev_tppGetTPadIpList_Nty") );

	//������Ϣ֪ͨ
	MAPPING_HELPER( ev_tppCnConfInfo_Nty, _T("ev_tppCnConfInfo_Nty") );

	//T300����
	MAPPING_HELPER( ev_tppUpdate_Cmd, _T("ev_tppUpdate_Cmd") );
	MAPPING_HELPER( ev_tppUpdate_Ind, _T("ev_tppUpdate_Ind") );

	//��Ƶ�ӿ�����
	MAPPING_HELPER( ev_tppSetAudioPort_Cmd, _T("ev_tppSetAudioPort_Cmd") );
	MAPPING_HELPER( ev_tppSetAudioPort_Ind, _T("ev_tppSetAudioPort_Ind") );
	MAPPING_HELPER( ev_tppAudioRestoreDefaults_Cmd, _T("ev_tppAudioRestoreDefaults_Cmd") );
	MAPPING_HELPER( ev_tppAudioRestoreDefaults_Ind, _T("ev_tppAudioRestoreDefaults_Ind") );

	//����Ƶѡ����󷽰�
	MAPPING_HELPER( ev_tppSelAVMatrixProject_Cmd, _T("ev_tppSelAVMatrixProject_Cmd") );
	MAPPING_HELPER( ev_tppSelAVMatrixProject_Ind, _T("ev_tppSelAVMatrixProject_Ind"), 3 );

	//ֹͣ��ϲ���
	MAPPING_HELPER( ev_tppStopAVMatrixProject_Req, _T("ev_tppStopAVMatrixProject_Req") );
	MAPPING_HELPER( ev_tppStopAVMatrixProject_Rsp, _T("ev_tppStopAVMatrixProject_Rsp") );

	//������Ϣ(�������и��Ļ������)
	MAPPING_HELPER( ev_tppGetLostPacketInfo_Req, _T("ev_tppGetLostPacketInfo_Req") );
	MAPPING_HELPER( ev_tppGetLostPacketInfo_Rsp, _T("ev_tppGetLostPacketInfo_Rsp"), 3 );

	//����������
	MAPPING_HELPER( ev_tppGetUpDownstreamRate_Nty, _T("ev_tppGetUpDownstreamRate_Nty"), 3 );

	//��ʾԴ����ӿڼ�����ӿ�
	MAPPING_HELPER( ev_tppAVInfo_Nty, _T("ev_tppAVInfo_Nty") );

	//����CNS
	MAPPING_HELPER( ev_tppReboot_Nty, _T("ev_tppReboot_Nty") );
	
	//̨���ϴ��ɹ�֪ͨ
	MAPPING_HELPER( ev_tppSetBannerLogo_Cmd, _T("ev_tppSetBannerLogo_Cmd") );
	
	//������Ϣ����ˢ������
	MAPPING_HELPER( ev_tppRefresh_Req, _T("ev_tppRefresh_Req") );

	//�����ַ��
	MAPPING_HELPER( ev_tppImportAddr_Req, _T("ev_tppImportAddr_Req") );
	MAPPING_HELPER( ev_tppImportAddr_Rsp, _T("ev_tppImportAddr_Rsp") );

	//��Ƶ�����������������
	MAPPING_HELPER( ev_tppSetAudiotMixer_Cmd, _T("ev_tppSetAudiotMixer_Cmd") );
	MAPPING_HELPER( ev_tppSetAudioEqualizer_Cmd, _T("ev_tppSetAudioEqualizer_Cmd") );
	MAPPING_HELPER( ev_tppSetAudiotMixer_Ind, _T("ev_tppSetAudiotMixer_Ind") );
	MAPPING_HELPER( ev_tppSetAudioEqualizer_Ind, _T("ev_tppSetAudioEqualizer_Ind") );
	MAPPING_HELPER( ev_tppMixRestoreDefaults_Cmd, _T("ev_tppMixRestoreDefaults_Cmd") );
	MAPPING_HELPER( ev_tppMixRestoreDefaults_Ind, _T("ev_tppMixRestoreDefaults_Ind") );
	MAPPING_HELPER( ev_tppEqualizerReDefaults_Cmd, _T("ev_tppEqualizerReDefaults_Cmd") );
	MAPPING_HELPER( ev_tppEqualizerReDefaults_Ind, _T("ev_tppEqualizerReDefaults_Ind") );

	//���з�����
	MAPPING_HELPER( ev_tppSetCallServerInfo_Cmd, _T("ev_tppSetCallServerInfo_Cmd") );
	MAPPING_HELPER( ev_tppSetCallServerInfo_Ind, _T("ev_tppSetCallServerInfo_Ind") );
	MAPPING_HELPER( ev_tppSetCallServerInfo_Nty, _T("ev_tppSetCallServerInfo_Nty") );
	
	//����������
	MAPPING_HELPER( ev_tppSetUpgradeServerInfo_Cmd, _T("ev_tppSetUpgradeServerInfo_Cmd") );
	MAPPING_HELPER( ev_tppSetUpgradeServerInfo_Ind, _T("ev_tppSetUpgradeServerInfo_Ind") );
	MAPPING_HELPER( ev_tppSetUpgradeServerInfo_Nty, _T("ev_tppSetUpgradeServerInfo_Nty") );

	//����
	MAPPING_HELPER( ev_CnAgtAddNMServerCmd, _T("ev_CnAgtAddNMServerCmd") );
	MAPPING_HELPER( ev_CnAgtDelNMServerCmd, _T("ev_CnAgtDelNMServerCmd") );
	MAPPING_HELPER( ev_CnAgtModifyNMServerCmd, _T("ev_CnAgtModifyNMServerCmd") );
	MAPPING_HELPER( ev_tppCnAgtAddNMServer_Ind, _T("ev_tppCnAgtAddNMServer_Ind") );
	MAPPING_HELPER( ev_tppCnAgtDelNMServer_Ind, _T("ev_tppCnAgtDelNMServer_Ind") );
	MAPPING_HELPER( ev_tppCnAgtModifyNMServer_Ind, _T("ev_tppCnAgtModifyNMServer_Ind") );
	MAPPING_HELPER( ev_tppCurAgtNMServerInfo_Nty, _T("ev_tppCurAgtNMServerInfo_Nty") );

	//�����
	MAPPING_HELPER( ev_Cn_CameraCfgNty, _T("ev_Cn_CameraCfgNty") );
	MAPPING_HELPER( ev_Cn_CameraSelectCmd, _T("ev_Cn_CameraSelectCmd") );
	MAPPING_HELPER( ev_Cn_CameraSelectInd, _T("ev_Cn_CameraSelectInd") );
	//MAPPING_HELPER( ev_Cn_CameraListCmd, _T("ev_Cn_CameraListCmd") );
	//MAPPING_HELPER( ev_Cn_CameraListInd, _T("ev_Cn_CameraListInd") );
	//MAPPING_HELPER( ev_Cn_SetCameraFileCmd, _T("ev_Cn_SetCameraFileCmd") );//shi
	//MAPPING_HELPER( ev_Cn_SetCameraFileInd, _T("ev_Cn_SetCameraFileInd") );//shi
	MAPPING_HELPER( ev_Cn_CameraFocusCmd, _T("ev_Cn_CameraFocusCmd") );
	MAPPING_HELPER( ev_Cn_CameraFocusInd, _T("ev_Cn_CameraFocusInd") );
	MAPPING_HELPER( ev_Cn_CameraAutoFocusCmd, _T("ev_Cn_CameraAutoFocusCmd") );
	MAPPING_HELPER( ev_Cn_CameraAutoFocusInd, _T("ev_Cn_CameraAutoFocusInd") );
	MAPPING_HELPER( ev_Cn_CameraPresetCmd, _T("ev_Cn_CameraPresetCmd") );
	MAPPING_HELPER( ev_Cn_CameraPresetInd, _T("ev_Cn_CameraPresetInd") );
	MAPPING_HELPER( ev_Cn_CameraPersetSaveCmd, _T("ev_Cn_CameraPersetSaveCmd") );
	MAPPING_HELPER( ev_Cn_CameraPersetSaveInd, _T("ev_Cn_CameraPersetSaveInd") );


	MAPPING_HELPER( ev_Cn_CameraZoomCmd, _T("ev_Cn_CameraZoomCmd") );
	MAPPING_HELPER( ev_Cn_CameraZoomInd, _T("ev_Cn_CameraZoomInd") );
	MAPPING_HELPER( ev_Cn_CameraPersetSaveCmd, _T("ev_Cn_CameraPersetSaveCmd") );
	MAPPING_HELPER( ev_Cn_CameraPersetSaveInd, _T("ev_Cn_CameraPersetSaveInd") );


	MAPPING_HELPER( ev_Cn_CameraResetCmd, _T("ev_Cn_CameraResetCmd") );
	MAPPING_HELPER( ev_Cn_CameraResetInd, _T("ev_Cn_CameraResetInd") );
	MAPPING_HELPER( ev_Cn_CameraOSDShowCmd, _T("ev_Cn_CameraOSDShowCmd") );
	MAPPING_HELPER( ev_Cn_CameraOSDShowInd, _T("ev_Cn_CameraOSDShowInd") );
	MAPPING_HELPER( ev_Cn_CameraAutoExposureCmd, _T("ev_Cn_CameraAutoExposureCmd") );
	MAPPING_HELPER( ev_Cn_CameraAutoExposureInd, _T("ev_Cn_CameraAutoExposureInd") );
	MAPPING_HELPER( ev_Cn_CameraGainCmd, _T("ev_Cn_CameraGainCmd") );
	MAPPING_HELPER( ev_Cn_CameraGainInd, _T("ev_Cn_CameraGainInd") );


	MAPPING_HELPER( ev_Cn_CameraShutSpdCmd, _T("ev_Cn_CameraShutSpdCmd") );
	MAPPING_HELPER( ev_Cn_CameraShutSpdInd, _T("ev_Cn_CameraShutSpdInd") );
	MAPPING_HELPER( ev_Cn_CameraBackLightCmd, _T("ev_Cn_CameraBackLightCmd") );
	MAPPING_HELPER( ev_Cn_CameraBackLightInd, _T("ev_Cn_CameraBackLightInd") );
	MAPPING_HELPER( ev_Cn_CameraApertureCmd, _T("ev_Cn_CameraApertureCmd") );
	MAPPING_HELPER( ev_Cn_CameraApertureInd, _T("ev_Cn_CameraApertureInd") );
	MAPPING_HELPER( ev_Cn_CameraAutoWBCmd, _T("ev_Cn_CameraAutoWBCmd") );
	MAPPING_HELPER( ev_Cn_CameraAutoWBInd, _T("ev_Cn_CameraAutoWBInd") );
	MAPPING_HELPER( ev_Cn_CameraRGainCmd, _T("ev_Cn_CameraRGainCmd") );
	MAPPING_HELPER( ev_Cn_CameraRGainInd, _T("ev_Cn_CameraRGainInd") );
	MAPPING_HELPER( ev_Cn_CameraBGainCmd, _T("ev_Cn_CameraBGainCmd") );
	MAPPING_HELPER( ev_Cn_CameraBGainInd, _T("ev_Cn_CameraBGainInd") );


	MAPPING_HELPER( ev_Cn_CameraPicSceneModeCmd, _T("ev_Cn_CameraPicSceneModeCmd") );
	MAPPING_HELPER( ev_Cn_CameraPicSceneModeInd, _T("ev_Cn_CameraPicSceneModeInd") );

	MAPPING_HELPER( ev_Cn_CameraGammaCmd, _T("ev_Cn_CameraGammaCmd") );
	MAPPING_HELPER( ev_Cn_CameraGammaInd, _T("ev_Cn_CameraGammaInd") );

	MAPPING_HELPER( ev_Cn_CameraPicSceAptCmd, _T("ev_Cn_CameraPicSceAptCmd") );
	MAPPING_HELPER( ev_Cn_CameraPicSceAptInd, _T("ev_Cn_CameraPicSceAptInd") );

	MAPPING_HELPER( ev_Cn_CameraContrastCmd, _T("ev_Cn_CameraContrastCmd") );
	MAPPING_HELPER( ev_Cn_CameraContrastInd, _T("ev_Cn_CameraContrastInd") );

	MAPPING_HELPER( ev_Cn_CameraHueCmd, _T("ev_Cn_CameraHueCmd") );
	MAPPING_HELPER( ev_Cn_CameraHueInd, _T("ev_Cn_CameraHueInd") );
	MAPPING_HELPER( ev_Cn_CameraSaturatCmd, _T("ev_Cn_CameraSaturatCmd") );
	MAPPING_HELPER( ev_Cn_CameraSaturatInd, _T("ev_Cn_CameraSaturatInd") );
	MAPPING_HELPER( ev_Cn_CameraBrightCmd, _T("ev_Cn_CameraBrightCmd") );
	MAPPING_HELPER( ev_Cn_CameraBrightInd, _T("ev_Cn_CameraBrightInd") );
	MAPPING_HELPER( ev_Cn_CameraNRStmCleanCmd, _T("ev_Cn_CameraNRStmCleanCmd") );
	MAPPING_HELPER( ev_Cn_CameraNRStmCleanInd, _T("ev_Cn_CameraNRStmCleanInd") );
	MAPPING_HELPER( ev_Cn_Camera3DNRCmd, _T("ev_Cn_Camera3DNRCmd") );
	MAPPING_HELPER( ev_Cn_Camera3DNRInd, _T("ev_Cn_Camera3DNRInd") );
	MAPPING_HELPER( ev_Cn_SetCameraZoomCmd, _T("ev_Cn_SetCameraZoomCmd") );
	MAPPING_HELPER( ev_Cn_SetCameraZoomInd, _T("ev_Cn_SetCameraZoomInd") );

	MAPPING_HELPER( ev_Cn_LoadCameraFileNty, _T("ev_Cn_LoadCameraFileNty") );

    MAPPING_HELPER( ev_TPadLoginInfo_Nty, _T("ev_TPadLoginInfo_Nty") );
    MAPPING_HELPER( ev_TPadHomeKey_Nty, _T("ev_TPadHomeKey_Nty") );

    //�пش��� dyy 2013-9-23 
    MAPPING_HELPER( ev_Cn_CentreSleepNty, _T("ev_Cn_CentreSleepNty") );

	MAPPING_HELPER( ev_Cn_CameraPowerOnNty, _T("ev_Cn_CameraPowerOnNty") );

	//B3�汾
	MAPPING_HELPER( ev_CnCfgVideoFormat_Cmd, _T("ev_CnCfgVideoFormat_Cmd") );
	MAPPING_HELPER( ev_CnCfgVideoFormat_Ind, _T("ev_CnCfgVideoFormat_Ind") );
	MAPPING_HELPER( ev_CnCfgDualVideoFormat_Cmd, _T("ev_CnCfgDualVideoFormat_Cmd") );
	MAPPING_HELPER( ev_CnCfgDualVideoFormat_Ind, _T("ev_CnCfgDualVideoFormat_Ind") );
	MAPPING_HELPER( ev_CnCfgCallRate_Cmd, _T("ev_CnCfgCallRate_Cmd") );
	MAPPING_HELPER( ev_CnCfgCallRate_Ind, _T("ev_CnCfgCallRate_Ind") );
	MAPPING_HELPER( ev_CnCfgDualCallRate_Cmd, _T("ev_CnCfgDualCallRate_Cmd") );
	MAPPING_HELPER( ev_CnCfgDualCallRate_Ind, _T("ev_CnCfgDualCallRate_Ind") );
	MAPPING_HELPER( ev_CnVerInfo_Nty, _T("ev_CnVerInfo_Nty") );
	MAPPING_HELPER( ev_CnCfgConfDis_Cmd, _T("ev_CnCfgConfDis_Cmd") );
	MAPPING_HELPER( ev_CnCfgConfDis_Ind, _T("ev_CnCfgConfDis_Ind") );
	MAPPING_HELPER( ev_CnCfgConfPoll_Cmd, _T("ev_CnCfgConfPoll_Cmd") );
	MAPPING_HELPER( ev_CnCfgConfPoll_Ind, _T("ev_CnCfgConfPoll_Ind") );
	MAPPING_HELPER( ev_CnCfgAudioFormat_Cmd, _T("ev_CnCfgAudioFormat_Cmd") );
	MAPPING_HELPER( ev_CnCfgAudioFormat_Ind, _T("ev_CnCfgAudioFormat_Ind") );
	MAPPING_HELPER( ev_CnViewLocalPIP_Cmd, _T("ev_CnViewLocalPIP_Cmd") );
	MAPPING_HELPER( ev_CnViewLocalPIP_Ind, _T("ev_CnViewLocalPIP_Ind") );
	MAPPING_HELPER( ev_CnViewLocalPIP_Nty, _T("ev_CnViewLocalPIP_Nty") );

	//ѡ������ǽ	
	MAPPING_HELPER( ev_CnSelTVSView_Cmd, _T("ev_CnSelTVSView_Cmd") );	
	MAPPING_HELPER( ev_CnSelTVSView_Ind, _T("ev_CnSelTVSView_Ind") );	
	MAPPING_HELPER( ev_CnCancelSelTVSView_Cmd, _T("ev_CnCancelSelTVSView_Cmd") );	
	MAPPING_HELPER( ev_CnCancelSelTVSView_Ind, _T("ev_CnCancelSelTVSView_Ind") );
}

void CCncMsgDriver::SetInsID( u16 wDstInsID )
{
	m_wInsID = wDstInsID;
}
u16  CCncMsgDriver::GetInsID()
{
	return m_wInsID;
}

void CCncMsgDriver::SetAppID( u16 wAppID )
{
	m_wAppID = wAppID;
}

u16 CCncMsgDriver::GetAppID()
{
	return m_wAppID;
}


void CCncMsgDriver::SetDesIID( u32 dwDesID )
{
    m_dwDesIID = dwDesID;
}

u32 CCncMsgDriver::GetDesIID()
{
    return m_dwDesIID;
}


