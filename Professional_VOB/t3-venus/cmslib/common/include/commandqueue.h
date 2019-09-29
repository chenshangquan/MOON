/*=======================================================================
ģ����      : MTCLib
�ļ���      : CommandQueue.h
����ļ�    : 
�ļ�ʵ�ֹ���: ��������Ϣ�Ķ��л���
����        : ������
�汾        : V4.0  Copyright(C) 2003-2006 KDC, All rights reserved.
-------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾  �޸���  �޸�����
2006/08/22  4.0   ������    ����
=======================================================================*/

#ifndef COMMANDQUEUE_H
#define COMMANDQUEUE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "kdvdispevent.h"
#include "tpmsg.h"

#include <queue>
using namespace std;

typedef struct tagCommand
{
    CMessage        m_cMsg;
    CTpMsg          m_cMtMsg;
    CKdvDispEvent*     m_pCDispEvent;
    vector<u16>     m_vctWaitEvent;
    u32             m_nEventNum;
    u32             m_dwType;
    u32             m_dwTimeout;
}TCOMMAND;

class CCommandQueue  
{
public:
    // ����һ��������������
	void PushCommand(CMessage& cMsg, CTpMsg& cMtMsg, CKdvDispEvent *pDispEvent,
                     u16 *pwWaitEvent, s32 nEventNum, u32 dwType, u32 dwTimeOut);
    
    // ��ȡ��������е�һ���������������Ϣ�Ӷ�����ɾ��
    BOOL32 GetNextCommand(TCOMMAND& tCommand);

    // ��ջ�����е���Ϣ
	void ClearCommand();
    // ���ػ�����е���Ϣ����
	u32 GetCommandCount();
    // �ж϶����Ƿ�Ϊ��
    BOOL32 IsEmpty(){   return m_vctCommandQueue.empty();  }

	CCommandQueue();
	virtual ~CCommandQueue();

private:
    // ����һ��������������
	void PushCommand(TCOMMAND& tCommand);
    // ɾ����������е�һ������
    void PopCommand();
    // ȡ�û�������еĵ�һ������
    void FrontCommand(TCOMMAND& tCommand);

    queue<TCOMMAND>     m_vctCommandQueue;
};

#endif
