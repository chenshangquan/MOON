// msgtransinstance.cpp: implementation of the CMsgTransInstance class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "msgtransinstance.h"

#include "msgtransdriver.h"


//////////////////////////////////////////////////////////////////////////
// CMsgQueue
// 
CMsgQueue::CMsgQueue()
{
}
CMsgQueue::~CMsgQueue()
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
void CMsgQueue::PushMsg(CMessage* const pMsg)
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
void CMsgQueue::PopMsg(CMsgQueue &cOutQue)
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
void CMsgQueue::Clear()
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
BOOL CMsgQueue::IsEmpty()
{
    return m_queMsg.empty();
}


////////////////////////////////////////////////////////////////////////////////
// ȫ��OspӦ�ó������
zTemplate<CMsgTransInstance, 1> g_MsgTransApp;

CMsgTransInstance* CMsgTransInstance::s_pMsgTransInst = NULL;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMsgTransInstance::CMsgTransInstance()
{
    InitializeCriticalSection(&m_csQueueOspMsg);
    s_pMsgTransInst = this;
}

CMsgTransInstance::~CMsgTransInstance()
{
    s_pMsgTransInst = NULL;
    DeleteCriticalSection(&m_csQueueOspMsg);
}



void CMsgTransInstance::InstanceEntry(CMessage *const pMsg)
{

    EnterCriticalSection(&m_csQueueOspMsg);
    if(m_cMsgQue.Size() == 0)
    {
        m_cMsgQue.PushMsg(pMsg);

        MsgTransDriver->OnOspMessageComing();             
    }
    else
        //������Ϣ��������ȡ��Ϣʱ���������������˲�����ʡ����ͬʱ�յ����OSP��Ϣʱ��
        //�п��ܻ��ߵ���һ��
    {
        m_cMsgQue.PushMsg(pMsg);
    }
    LeaveCriticalSection(&m_csQueueOspMsg);

}


void CMsgTransInstance::PopAllMsg(CMsgQueue &cMsgQue)
{
    EnterCriticalSection(&m_csQueueOspMsg);
    while (!m_cMsgQue.IsEmpty()) 
    {
        m_cMsgQue.PopMsg(cMsgQue);
    }
    LeaveCriticalSection(&m_csQueueOspMsg);
}

void CMsgTransInstance::ClearQueue()
{
    EnterCriticalSection(&m_csQueueOspMsg);
    m_cMsgQue.Clear();
    LeaveCriticalSection(&m_csQueueOspMsg);
}

