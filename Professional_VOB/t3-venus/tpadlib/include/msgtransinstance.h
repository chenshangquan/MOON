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
/*                        ��Ϣ���ж���                                  */
/************************************************************************/
class CMsgQueue
{
public:
    CMsgQueue();
    ~CMsgQueue();
    // ��һ����Ϣѹ�������
    void PushMsg(CMessage* const pMsg);
    // �Ӷ�����ȡ��һ����Ϣ
    void PopMsg(CMsgQueue &cOutQue);
    // �Ӷ����е���һ����Ϣ
    void Pop() 
    { 
        CMessage *pMsg = &m_queMsg.front(); 
        delete []pMsg->content;
        m_queMsg.pop(); 
    }
    // �����Ƿ�Ϊ��
    BOOL IsEmpty();
    // ��ն���
    void Clear();
    // �õ�������ǰ��Ԫ��
    CMessage& Front() { return m_queMsg.front();}
    // �õ����еĴ�С
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

    // ��ȡ�������Ϣ����(�̰߳�ȫ)
    void PopAllMsg(CMsgQueue &cMsgQue);
    // �����Ϣ����
    void ClearQueue();

    static CMsgTransInstance* GetMsgTransInst() { return s_pMsgTransInst; }

protected:
    // ��Ϣ������м��䱣���ؼ���
    CMsgQueue       m_cMsgQue;
    CRITICAL_SECTION   m_csQueueOspMsg;

private:
    static CMsgTransInstance *s_pMsgTransInst;
};

extern zTemplate<CMsgTransInstance, 1> g_MsgTransApp;

#endif // !defined(AFX_MSGTRANSINSTANCE_H__D5CAA31C_68AA_494C_A20E_3BF57F5840A7__INCLUDED_)
