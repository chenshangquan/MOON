// tpadmsgdriver.h: interface for the CTpadMsgDriver class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TPADMSGDRIVER_H__DA72E4C3_F117_459E_9B19_9BDEF898E374__INCLUDED_)
#define AFX_TPADMSGDRIVER_H__DA72E4C3_F117_459E_9B19_9BDEF898E374__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tpmsg.h"  
#include "commandqueue.h" 
#include "eventoutcnsallmsg.h"
#include "tpstruct.h"

#define TYPE_CMESSAGE  0         //һ���CMessage��Ϣ
#define TYPE_TPMSG     1         //�շ�����ϢΪCTPMSG ,��Ҫ������Ϣ���͵�ת��

class CTPadMsgDriver  
{
public:
	CTPadMsgDriver();
	virtual ~CTPadMsgDriver();

    //��ȡ�ӿ�ָ��
	static CTPadMsgDriver* GetMsgDriverPtr();

	// �õ������ն���Ϣ��ָ��
	CTpMsg* GetKdvMsgPtr(BOOL32 bClear = TRUE);

    virtual u16 PostMsg(u32 dwType = TYPE_CMESSAGE);

    // ������������Ϣ, �ڴ������Ӧ
    u16 PostCommand(CKdvDispEvent *pDispEvent, u16 *pwWaitEvent, s32 nEventNum = 1, 
        u32 dwType = TYPE_CMESSAGE, u32 dwTimeOut = 1500);
    // ������������Ϣ���ڴ�������Ӧ
    u16 PostCommand(CKdvDispEvent *pDispEvent, u16 wWaitEvent, u32 dwType = TYPE_CMESSAGE, u32 dwTimeOut = 1500);

    //����Ϣת����cns
    u16 TransMsg( const CMessage* pMsg );

    //��Ӧ�յ���Osp��Ϣ
    void OnOspMessageComing( CMessage *const pMsg );

    // ע��һ��������Ϣ�����ָ��
    void RegHandler(CKdvDispEvent* const pDispEvnet);
    // ע��һ��������Ϣ�����ָ��
    void UnregHandler(CKdvDispEvent* const pDispEvnet);
    // �������ע������ָ��
    void ClearHandler();
    // �������������Ϣ����
    void ClearAllCommand();

    //���õ�ǰ���ӽڵ�
    void SetNodeId(u32 dwId) { m_dwNodeId = dwId; }
    u32 GetNodeId(){ return m_dwNodeId;}
    
    // ����TPadʹ�õ�APPID��
    void SetAppId( u16 wAppID ){ m_wAppID = wAppID; } 
    u16  GetAppId(){ return m_wAppID; }

protected:
    // �Ƿ����ڴ�������
    BOOL IsHandleCmd() const { return !m_vWaitingEvents.empty(); }
    // ��յȴ�����Ϣ
    void ClearWaiting();
    // ȱʡ��ʱ��Ϣ������
    virtual void OnTimeOut(u16 wEvent){ return; }
    // ��һ���������ɺ󣬷�����һ������
    void PostNextCommand();

    void MappingEventName();

    // ��ӦWM_TIMER��Ϣ
    void OnTimer(WPARAM wParam, LPARAM lParam);
    
public:
    static CTPadMsgDriver *s_pMsgDriver;

protected:
    CCommandQueue  m_cCommandQueue;     //��������
    
    CTpMsg         m_cTpMsg;            //���ڷ���TP��Ϣ����Ϣ�ṹ
	CMessage	   m_cMsg;			    //���ڷ���������Ϣ����Ϣ�ṹ

private:
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    HWND            m_hWndOsp;           // ��Ƕ������Ϣ�Ĵ���
    WNDPROC         m_wndprocOld;       // ϵͳ���ڹ���
    vector<CKdvDispEvent*> m_vpDispEvent;// ��Ϣ�ַ���
    vector<u16>     m_vWaitingEvents;    // ���ڵȴ�Ӧ�����Ϣ
    CKdvDispEvent  *m_pCurDispEvent;     // ���ڴ������Ϣ��Ӧ����Ӧ���ָ��
    u16             m_wCurSendEvent;     // ��ǰ���ͳ�ȥ����Ϣ
    s32             m_nTimer;

    u32  m_dwNodeId;        // ��ǰ���ӵĽڵ�
    u16  m_wAppID;			// ���ӵ�APPID��
};

#endif // !defined(AFX_TPADMSGDRIVER_H__DA72E4C3_F117_459E_9B19_9BDEF898E374__INCLUDED_)
