/*=======================================================================
ģ����      : CNC����̨
�ļ���      : addrmsgdriver.h
����ļ�    : 
�ļ�ʵ�ֹ���: ��ַ����Ϣ������
����        : 
�汾        : V3.0  Copyright(C) 1997-2003 KDC, All rights reserved.
-------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����

=======================================================================*/
#ifndef ADDRMSGDRIVER_H
#define ADDRMSGDRIVER_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <map>
#include "kdvdispevent.h"
#include "tpmsg.h"                       //������Ϣ����Ϣ�ṹ
#include "CommandQueue.h"

using namespace std;


class CAddrMsgDriver
{
public:
    CAddrMsgDriver();
    ~CAddrMsgDriver();
    // ��ȡ��Ƕ�Ĵ��ھ��
    HWND GetOspRecvWindow(){ return m_hWndOsp;};
    // �õ�������Ϣָ��
    CMessage* GetCMsgPtr(BOOL32 bClear = TRUE);
	// �õ������ն���Ϣ��ָ��
	CTpMsg* GetKdvMsgPtr(BOOL32 bClear = TRUE);
    // ������������Ϣ �ɷ�����ͨCMessage��CMtMsg���͵���Ϣ
    virtual u16 PostMsg(u32 dwType = TYPE_CMESSAGE);
    // ������������Ϣ, �ڴ������Ӧ
    u16 PostCommand(CKdvDispEvent *pDispEvent, u16 *pwWaitEvent, s32 nEventNum = 1, 
        u32 dwType = TYPE_CMESSAGE, u32 dwTimeOut = 1500);
    // ������������Ϣ���ڴ�������Ӧ
    u16 PostCommand(CKdvDispEvent *pDispEvent, u16 wWaitEvent, u32 dwType = TYPE_CMESSAGE, u32 dwTimeOut = 1500);
    // ע��һ��������Ϣ�����ָ��
    void RegHandler(CKdvDispEvent* const pDispEvnet);
    // ע��һ��������Ϣ�����ָ��
    void UnregHandler(CKdvDispEvent* const pDispEvnet);
    // �������ע������ָ��
    void ClearHandler();
    // �������������Ϣ����
    void ClearAllCommand();

public:
    static CAddrMsgDriver *s_pMsgDriver;

	// ��ӦWM_OSPMESSAGECOMING��Ϣ
    void OnOspMessageComing(WPARAM wParam, LPARAM lParam);

protected:

    // ��ӦWM_OSPSYNCMSGCOMING��Ϣ
	void OnOspSyncMsgComing(WPARAM wParam, LPARAM lParam);
    // ��ӦWM_TIMER��Ϣ
    void OnTimer(WPARAM wParam, LPARAM lParam);
    // ��յȴ�����Ϣ
    void ClearWaiting();
    // ȱʡ��ʱ��Ϣ������
    virtual void OnTimeOut(u16 wEvent){ return; }
    // ��һ���������ɺ󣬷�����һ������
    void PostNextCommand();

    CTpMsg       m_cTpMsg;              //���ڷ���TP��Ϣ����Ϣ�ṹ
	CMessage	 m_cMsg;				//���ڷ���������Ϣ����Ϣ�ṹ

private:
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    // �Ƿ����ڴ�������
    BOOL IsHandleCmd() const { return !m_vWaitingEvents.empty(); }
    HWND            m_hWndOsp;          // ��Ƕ������Ϣ�Ĵ���
    WNDPROC         m_wndprocOld;       // ϵͳ���ڹ���
    vector<CKdvDispEvent*> m_vpDispEvent;  // ��Ϣ�ַ���
    vector<u16>     m_vWaitingEvents;	// ���ڵȴ�Ӧ�����Ϣ
    CKdvDispEvent  *m_pCurDispEvent;    // ���ڴ������Ϣ��Ӧ����Ӧ���ָ��
    u16             m_wCurSendEvent;    // ��ǰ���ͳ�ȥ����Ϣ
    s32             m_nTimer;

protected:
    CCommandQueue       m_cCommandQueue;        // ��������
};


#endif //ADDRMSGDRIVER_H
