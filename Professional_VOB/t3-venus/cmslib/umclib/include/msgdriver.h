/*=======================================================================
ģ����      : �ն˿���̨
�ļ���      : MsgDriver.h
����ļ�    : 
�ļ�ʵ�ֹ���: ��Ϣ������
����        : �ܹ㻯
�汾        : V3.0  Copyright(C) 1997-2003 KDC, All rights reserved.
-------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2003/12/22  3.0         �ܹ㻯      ����
2003/03/02	3.0			�ܹ㻯		����
2004/08/23  3.5         ���ǿ      �淶���룬����CDispEvent��
=======================================================================*/
#ifndef MSGDRIVER_H
#define MSGDRIVER_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <map>
#include "kdvdispevent.h"
#include "tpmsg.h"                       //������Ϣ����Ϣ�ṹ
#include "CommandQueue.h"

using namespace std;

#define MTC_TRANSFILETIMER 99
#define MTC_TRANSFILE_INTERVAL 300
#define MTC_TRANSFILE_SIZE		16 * 1024


//#define ev_mcViewPollCmd	9999 //��ʱ������
//#define ev_mcViewPollInd	9998//��ʱ������
// #define ev_CodecVideoEncDecResInd 9997//��ʱ������
class CMsgDriver
{
public:
    CMsgDriver();
    ~CMsgDriver();
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

	void SetSndInstID( u32 dwDstInstID );
	u32  GetSndInstID();

	void SetAppID( u32 dwAppID ){ m_dwAppID = dwAppID;};
	u32  GetAppID(){ return m_dwAppID;};

public:
    static CMsgDriver *s_pMsgDriver;

protected:
    // ��ӦWM_OSPMESSAGECOMING��Ϣ
    void OnOspMessageComing(WPARAM wParam, LPARAM lParam);
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

    CTpMsg       m_cKdvMsg;             // ���ڷ��� tp��Ϣ����Ϣ�ṹ
	CMessage	 m_cMsg;				//���ڷ����������ն���Ϣ����Ϣ�ṹ
    //״̬��ӡ
    virtual void Dump() {return;};
	virtual void ReqIKey(u8 byLocal) {return;};
private:
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    // �Ƿ����ڴ�������
    BOOL IsHandleCmd() const { return !m_vWaitingEvents.empty(); }
    HWND            m_hWndOsp;          // ��Ƕ������Ϣ�Ĵ���
    WNDPROC         m_wndprocOld;       // ϵͳ���ڹ���
    vector<CKdvDispEvent*> m_vpDispEvent;  // ��Ϣ�ַ���
    vector<u16>     m_vWaitingEvents;	// ���ڵȴ�Ӧ�����Ϣ
    CKdvDispEvent      *m_pCurDispEvent;   // ���ڴ������Ϣ��Ӧ����Ӧ���ָ��
    u16             m_wCurSendEvent;       // ��ǰ���ͳ�ȥ����Ϣ
    s32             m_nTimer;
	u32             m_dwInstID;             //ʵ��ID
	u32             m_dwAppID;
    // ��Ϣ����ӳ���
    enum CATALOG{
        DEFAULT = 0,
        MULTI_CONF,
        P2P,
        AUD,
        VID,
        CAMERA,
        CFG,
        ADDR,
        MATRIX,
        REMOTECTRL,
        USERMANAGE,
        MISC,
		VOD,
		FXO,
		LOG
    };
    void MappingHelper(u16 wEvent, const CString& strName, CATALOG catalog = DEFAULT);
    void MappingEventName();
    BOOL CanBeTraceOut(u16 wEvent) const;       // ��Ϣ�������
protected:
    CCommandQueue       m_cCommandQueue;        // ��������
    map<u16, u32>       m_mapEventType;         // ��Ϣ����ӳ���
    map<u16, CString>   m_mapEventsName;        // ��Ϣ����ӳ���
    u8*                 m_pbyFile;              // �ļ��ڴ��ָ��
    u32                 m_dwFileLength;         // �ļ�����
    u32                 m_dwFileCurPos;         // �ļ���ǰλ�� 
    u32                 m_dwFileFragIndex;      // �ļ������
    u8                  m_byTransferStatus;     // �ļ�����״̬
    s32                 m_nFileTransferTimer;   // �ļ����䶨ʱ��
    u16                 m_wFileType;            // �ļ�����
    u32                 m_dwTimeOut;            // ��ʱʱ��
	u16					m_wMaxPackageLen;		// ����󳤶�
    //����״̬
    enum TRANSFERSTATUS{
        FREE = 0,   //����
        READY,      //׼��
        BUSY,       //������
    };
    
protected:
    // �����ļ�����ӿ�
    /*�������� TransferFile
    ��    �ܣ� �����ļ��ӿ�, ������ʱ��
    ��    ���� 
    �� �� ֵ�� u16 
    ˵    ���� */
    u16 TransferFile();
	
    void StopTransferFile();

    /*�������� PostFile
    ��    �ܣ� �����ļ���
    ��    ���� u8 *pbyBuf      �ļ���ָ��
               u32 dwBufLenth  �ļ��γ���
               u32 nIndex      �ļ������
    �� �� ֵ�� u16 
    ˵    ���� */
    u16 PostFile(u8 *pbyBuf, u32 dwBufLenth, u32 nIndex);
    virtual void EndTransFile(){return;}
};


#endif //MSGDRIVER_H
