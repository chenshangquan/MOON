// msgtransinstance.h: interface for the CMsgTransInstance class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGTRANSINSTANCE_H__D5CAA31C_68AA_494C_A20E_3BF57F5840A7__INCLUDED_)
#define AFX_MSGTRANSINSTANCE_H__D5CAA31C_68AA_494C_A20E_3BF57F5840A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <queue>
/************************************************************************/
/*                        消息队列定义                                  */
/************************************************************************/
class CMsgQueue
{
public:
    CMsgQueue();
    ~CMsgQueue();
    // 将一条消息压入队列中
    void PushMsg(CMessage* const pMsg);
    // 从队列中取出一条消息
    void PopMsg(CMsgQueue &cOutQue);
    // 从队列中弹出一条消息
    void Pop() 
    { 
        CMessage *pMsg = &m_queMsg.front(); 
        delete []pMsg->content;
        m_queMsg.pop(); 
    }
    // 队列是否为空
    BOOL IsEmpty();
    // 清空队列
    void Clear();
    // 得到队列最前面元素
    CMessage& Front() { return m_queMsg.front();}
    // 得到队列的大小
    s32 Size() { return m_queMsg.size(); }
private:
    queue<CMessage> m_queMsg;
};


class CMsgTransInstance : public CInstance 
{
public:
	CMsgTransInstance();
	virtual ~CMsgTransInstance();

    virtual void InstanceEntry(CMessage *const pMsg);

    // 提取缓冲的消息队列(线程安全)
    void PopAllMsg(CMsgQueue &cMsgQue);
    // 清空消息队列
    void ClearQueue();

    static CMsgTransInstance* GetMsgTransInst() { return s_pMsgTransInst; }

protected:
    // 消息缓冲队列及其保护关键区
    CMsgQueue       m_cMsgQue;
    CRITICAL_SECTION   m_csQueueOspMsg;

private:
    static CMsgTransInstance *s_pMsgTransInst;
};

extern zTemplate<CMsgTransInstance, 1> g_MsgTransApp;

#endif // !defined(AFX_MSGTRANSINSTANCE_H__D5CAA31C_68AA_494C_A20E_3BF57F5840A7__INCLUDED_)
