/*=======================================================================
ģ����      : �ն˿���̨
�ļ���      : moonmsgrecver.h
����ļ�    : 
�ļ�ʵ�ֹ���: ��������OSP��Ϣ�����CInstance������
����        : �ܹ㻯
�汾        : V3.0  Copyright(C) 1997-2003 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2003/12/16  3.0         �ܹ㻯      ����
2003/03/02	3.0			�ܹ㻯		����
2004/08/23  3.5         ���ǿ      �淶���룬�޸Ľṹ
2005/03/16  3.6         ���ҳ�      ���״̬��ӡ
=======================================================================*/

#if !defined(AFX_OSPMSGRECVER_H__3FB841FA_784C_41CD_AFF4_A6DC381619A8__INCLUDED_)
#define AFX_OSPMSGRECVER_H__3FB841FA_784C_41CD_AFF4_A6DC381619A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define INSTANCE_COUNT	1	// ������Ϣ��ʵ������Ŀ

#include <queue>
#include <vector>
#include "kdvtype.h"                                                                                            
#include "kdvdef.h" 
#include "osp.h"
//#include "MtConst.h"

using namespace std;

/************************************************************************/
/*                        ��Ϣ���ж���                                  */
/************************************************************************/
class CMoonMsgQueue
{
public:
    CMoonMsgQueue();
    ~CMoonMsgQueue();
    // ��һ����Ϣѹ�������
    void PushMsg(CMessage* const pMsg);
    // �Ӷ�����ȡ��һ����Ϣ
    void PopMsg(CMoonMsgQueue &cOutQue);
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

/************************************************************************/
/*                        OSPʵ������                                  */
/************************************************************************/
class CMoonMsgHandler : public CInstance  
{
public:
    CMoonMsgHandler();
    ~CMoonMsgHandler();

    // ʵ��CInstance�еĴ��鷽��(�̰߳�ȫ)
    virtual void InstanceEntry(CMessage *const pMsg);
    // ��ȡ�������Ϣ����(�̰߳�ȫ)
    void PopAllMsg(CMoonMsgQueue &cMsgQue);
    // �����Ϣ����
    void ClearQueue();
    // ͬ����Ϣ����
    u32 PutSyncAck(const void* pAckBuf=NULL, u16 u16AckSize=0);
public:
    static u32 WM_OSPMESSAGECOMING;
    static u32 WM_OSPSYNCMSGCOMING;
    static u32 WM_REQMTCSTATUS;
	static u32 WM_REQIKEY;
    static CMoonMsgHandler* GetMsgHandler() { return s_pMsgHandler; }
protected:
    // ��Ϣ������м��䱣���ؼ���
    CMoonMsgQueue       m_cMsgQue;
    CRITICAL_SECTION m_csQueueOspMsg;
private:
    static CMoonMsgHandler *s_pMsgHandler;
};

class CMoonAppBase
{
public:
    CMoonAppBase();
    ~CMoonAppBase();
    // ��ȡ��ǰ���ӽڵ�ı�ʶ(�̰߳�ȫ)
    u32 GetNodeId(){ return m_dwNodeId;}
    // ���õ�ǰ���ӽڵ�ı�ʶ(�̰߳�ȫ)
    void SetNodeId(u32 dwId) { m_dwNodeId = dwId; }
    // ��ȡ��ǰOsp��Ϣ���洰��
    HWND GetNotifyWindow() { return m_hWndTarget;}
    // ���õ�ǰOsp��Ϣ���洰��
    void SetNotifyWindow(HWND hWnd) { m_hWndTarget = hWnd; }
    //�����Ϣ����
    void ClearOspMsg();
protected:
    u32                     m_dwNodeId;     // ��ǰ�������ӵĽڵ��ʶ
    HWND                    m_hWndTarget;   // �յ�Osp��Ϣ����˴��ڱ���
};

//extern zTemplate<CMsgHandler, INSTANCE_COUNT, COspAppBase> g_OspApp;
extern zTemplate<CMoonMsgHandler, INSTANCE_COUNT, CMoonAppBase> g_MoonApp;

#endif // !defined(AFX_OSPMSGRECVER_H__3FB841FA_784C_41CD_AFF4_A6DC381619A8__INCLUDED_)
