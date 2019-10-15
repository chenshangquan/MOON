#pragma once
#include "stdafx.h"
#include "rkcSessionCtrlIF.h"
#include "rkcmsgdriver.h"

class CRkcSession : public CRkcSessionCtrlIF,
                    public CRkcMsgDriver
{
public:
    CRkcSession();
    ~CRkcSession();

    //��ȡ�ӿ� 
    virtual u16 RkcGetInterface(CRkcSysCtrlIF **ppCtrl);
    virtual u16 RkcGetInterface(CCamConfigIF **ppCtrl);
    virtual u16 RkcGetInterface(CSysConfigIF **ppCtrl);

protected:
    // ��ʼ��OSP 
    u16 InitializeOsp();

    virtual void DispEvent(const CMessage &cMsg);
    virtual void OnTimeOut(u16 wEvent);

private:
    BOOL32 m_bInitOsp;

    // ����������ӿ���
    CRkcSysCtrlIF  *m_pSysCtrlIf;
    CCamConfigIF  *m_pCamConfigIf;
    CSysConfigIF  *m_pSysConfigIf;

};

