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
  函 数 名： PushMsg
  功    能： 添加一条消息到消息队列
  算法实现： 
  全局变量： 
  参    数： CMessage* const pMsg  消息指针
  返 回 值： void 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2004/10/12     3.5		王慧琛                  规范化
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
  函 数 名： PopMsg
  功    能： 从消息队列里弹出一条消息，并添加到目标队列里
  算法实现： 
  全局变量： 
  参    数： CMsgQueue &cOutQue 目标队列
  返 回 值： void 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2004/10/12     3.5		王慧琛                  规范化
=============================================================================*/
void CMsgQueue::PopMsg(CMsgQueue &cOutQue)
{
    CMessage *pMsg = &m_queMsg.front(); 
    cOutQue.PushMsg(pMsg);
    delete []pMsg->content;
    m_queMsg.pop();
}

/*=============================================================================
  函 数 名： Clear
  功    能： 清空队列
  算法实现： 
  全局变量： 
  参    数： 
  返 回 值： void 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2004/10/12     3.5		王慧琛                  规范化
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
  函 数 名： IsEmpty
  功    能： 判断消息队列是否为空
  算法实现： 
  全局变量： 
  参    数： 
  返 回 值： BOOL 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2004/10/12     3.5		王慧琛                  规范化
=============================================================================*/
BOOL CMsgQueue::IsEmpty()
{
    return m_queMsg.empty();
}


////////////////////////////////////////////////////////////////////////////////
// 全局Osp应用程序对象
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
        //本地消息队列正在取消息时，不立即处理－－此步不可省，在同时收到多个OSP消息时，
        //有可能会走到这一步
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

