/*=======================================================================
ģ����      : �ն˿���̨
�ļ���      : cncmsgrecver.cpp
����ļ�    : 
�ļ�ʵ�ֹ���: ʵ�ֽ���OSP��Ϣ�����CInstance�����࣬��Ϣ������ж��壬
����        : �ܹ㻯
�汾        : V3.0  Copyright(C) 1997-2003 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2003/12/16  3.0         �ܹ㻯      ����
2003/03/02	3.0			�ܹ㻯		����
2004/08/23  3.5         ���ǿ      �淶���룬�޸Ľṹ
2004/10/11  3.5         �����      ������룬���ע��
=======================================================================*/

#include "stdafx.h"
#include "moonmsgrecver.h"
using namespace std;

//////////////////////////////////////////////////////////////////////////
// CMsgQueue
// 
CMoonMsgQueue::CMoonMsgQueue()
{
}
CMoonMsgQueue::~CMoonMsgQueue()
{
    Clear();
}

/*=============================================================================
  �� �� ���� PushMsg
  ��    �ܣ� ���һ����Ϣ����Ϣ����
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� CMessage* const pMsg  ��Ϣָ��
  �� �� ֵ�� void 
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2004/10/12     3.5		�����                  �淶��
=============================================================================*/
void CMoonMsgQueue::PushMsg(CMessage* const pMsg)
{
    CMessage cMsg;
    cMsg = *pMsg;
    cMsg.content = new u8[pMsg->length];
    memcpy(cMsg.content, pMsg->content, pMsg->length);
    m_queMsg.push(cMsg);
}

/*=============================================================================
  �� �� ���� PopMsg
  ��    �ܣ� ����Ϣ�����ﵯ��һ����Ϣ������ӵ�Ŀ�������
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� CMsgQueue &cOutQue Ŀ�����
  �� �� ֵ�� void 
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2004/10/12     3.5		�����                  �淶��
=============================================================================*/
void CMoonMsgQueue::PopMsg(CMoonMsgQueue &cOutQue)
{
    CMessage *pMsg = &m_queMsg.front(); 
    cOutQue.PushMsg(pMsg);
    delete []pMsg->content;
    m_queMsg.pop();
}

/*=============================================================================
  �� �� ���� Clear
  ��    �ܣ� ��ն���
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� 
  �� �� ֵ�� void 
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2004/10/12     3.5		�����                  �淶��
=============================================================================*/
void CMoonMsgQueue::Clear()
{
    while (!m_queMsg.empty()) 
    {
        CMessage *pMsg = &m_queMsg.front();
        delete []pMsg->content;
        m_queMsg.pop();
    }
}

/*=============================================================================
  �� �� ���� IsEmpty
  ��    �ܣ� �ж���Ϣ�����Ƿ�Ϊ��
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� 
  �� �� ֵ�� BOOL 
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2004/10/12     3.5		�����                  �淶��
=============================================================================*/
BOOL CMoonMsgQueue::IsEmpty()
{
    return m_queMsg.empty();
}


////////////////////////////////////////////////////////////////////////////////
// ȫ��OspӦ�ó������
zTemplate<CMoonMsgHandler, INSTANCE_COUNT, CMoonAppBase> g_MoonApp;

////////////////////////////////////////////////////////////////////////////////
// CMsgHandler
u32 CMoonMsgHandler::WM_OSPMESSAGECOMING = WM_USER + 5;
u32 CMoonMsgHandler::WM_OSPSYNCMSGCOMING = WM_USER + 6;
u32 CMoonMsgHandler::WM_REQMTCSTATUS     = WM_USER + 7;
u32 CMoonMsgHandler::WM_REQIKEY			= WM_USER + 8;

CMoonMsgHandler* CMoonMsgHandler::s_pMsgHandler = NULL;

CMoonMsgHandler::CMoonMsgHandler()
{
    InitializeCriticalSection(&m_csQueueOspMsg);
    // 2004/08/24 ���ǿ Ŀǰֻ֧��һ��ʵ���Ϳ�����
    s_pMsgHandler = this;
}

CMoonMsgHandler::~CMoonMsgHandler()
{
    s_pMsgHandler = NULL;
    DeleteCriticalSection(&m_csQueueOspMsg);
}

/*=============================================================================
  �� �� ���� PutSyncAck
  ��    �ܣ� ͬ����Ϣ������Ŀǰȫ�����ڼ��ɲ�����Ϣ�Ļ�Ӧ
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� const void* pAckBuf ��Ϣʵ������ָ��
             u16 u16AckSize      ��Ϣ����
  �� �� ֵ�� u32                 �ɹ����
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2004/10/12     3.5		�����                  �淶��
=============================================================================*/
u32 CMoonMsgHandler::PutSyncAck(const void* pAckBuf, u16 u16AckSize)
{
    return SetSyncAck(pAckBuf, u16AckSize);
}


/*=============================================================================
  �� �� ���� InstanceEntry
  ��    �ܣ� OSP��Ϣ��ڣ�ת����Ϣ���е�����
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� CMessage *const pMsg   ��Ϣָ��
  �� �� ֵ�� void 
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2004/10/12     3.5		�����                  �淶��
=============================================================================*/
void CMoonMsgHandler::InstanceEntry(CMessage *const pMsg)
{
    if (pMsg->type !=3) //�첽��Ϣ
    {
        EnterCriticalSection(&m_csQueueOspMsg);
        if(m_cMsgQue.Size() == 0)
            //ԭOSP��Ϣ����Ϊ��ʱ��֪ͨ������Ϣ�����ٴ���ȡ��Ϣ
        {
            m_cMsgQue.PushMsg(pMsg);
            ::PostMessage(g_MoonApp.GetNotifyWindow(), WM_OSPMESSAGECOMING, 0, 0);        
        }
        else
            //������Ϣ��������ȡ��Ϣʱ������֪ͨ�����˲�����ʡ����ͬʱ�յ����OSP��Ϣʱ��
            //�п��ܻ��ߵ���һ��
        {
            m_cMsgQue.PushMsg(pMsg);
        }
        LeaveCriticalSection(&m_csQueueOspMsg);
    }
    else
    {
        // ͬ����Ϣ
        SendMessage(g_MoonApp.GetNotifyWindow(), WM_OSPSYNCMSGCOMING,
             reinterpret_cast<WPARAM>(pMsg), 0);
    }    
}

/*=============================================================================
  �� �� ���� PopAllMsg
  ��    �ܣ� ���OSP��Ϣ���У�������ת�빤����Ϣ����
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� CMsgQueue &cMsgQue
  �� �� ֵ�� void 
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2004/10/12     3.5		�����                  �淶��
=============================================================================*/
void CMoonMsgHandler::PopAllMsg(CMoonMsgQueue &cMsgQue)
{
    EnterCriticalSection(&m_csQueueOspMsg);
    while (!m_cMsgQue.IsEmpty()) 
    {
        m_cMsgQue.PopMsg(cMsgQue);
    }
    LeaveCriticalSection(&m_csQueueOspMsg);
}

/*=============================================================================
  �� �� ���� ClearQueue
  ��    �ܣ� ���OSP��Ϣ���У���Ҫ����ϵͳ�˳�ʱ
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� 
  �� �� ֵ�� void 
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2004/10/12     3.5		�����                  �淶��
=============================================================================*/
void CMoonMsgHandler::ClearQueue()
{
    EnterCriticalSection(&m_csQueueOspMsg);
    m_cMsgQue.Clear();
    LeaveCriticalSection(&m_csQueueOspMsg);
}

//////////////////////////////////////////////////////////////////////////
//  COspAppBase
//

CMoonAppBase::CMoonAppBase()
{
    m_dwNodeId = INVALID_NODE;
    m_hWndTarget = NULL;
}

CMoonAppBase::~CMoonAppBase()
{
}

/*=============================================================================
  �� �� ���� ClearOspMsg
  ��    �ܣ� ϵͳ�˳�ʱ���OSP��Ϣ���У���ֹ����ˢ��IEʱ�Ĺ���OSP��Ϣ
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� 
  �� �� ֵ�� void 
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2004/10/12     3.5		�����                  �淶��
=============================================================================*/
void CMoonAppBase::ClearOspMsg()
{
    CMoonMsgHandler *pHandler = CMoonMsgHandler::GetMsgHandler();
    if (pHandler) 
    {
        pHandler->ClearQueue();
    }
}
