#include "stdafx.h"
#include <string>
#include "rkcsession.h"
#include "rkcmsgrecver.h"
#include "rkcprintctrl.h"

#include "rkcsysctrl.h"

#include "tpcommontype.h"
#include "camconfig.h"
#include "sysconfig.h"

//�̺߳���
DWORD WINAPI GetConfTempThread(LPVOID pParam);

CRkcSession::CRkcSession():m_bInitOsp(FALSE)
{
    InitializeOsp();

    m_pSysCtrlIf = NULL;
    m_pCamConfigIf = NULL;
    m_pSysConfigIf = NULL;
   
    //�ڸ����У�new�����еĹ����࣬�ⲿͨ���ӿ�GetInterface()��ȡ
    #define NEW_REG(pCtrlIF, clsName)         \
    pCtrlIF = new clsName(*this);     \
    RegHandler(pCtrlIF);

    NEW_REG( m_pSysCtrlIf, CRkcSysCtrl );
    NEW_REG( m_pCamConfigIf, CCamConfig );
    NEW_REG( m_pSysConfigIf, CSysConfig );
}

CRkcSession::~CRkcSession()
{

}

u16 CRkcSession::InitializeOsp()
{
    // ��ʼ��OSP
    const u32 dwTelnetPort = 0;
    if( !IsOspInitd() )
    {

        BOOL bTelnet  = TRUE ;//FALSE

#ifdef _DEBUG
        bTelnet = TRUE;
#endif

        if(!OspInit( bTelnet, dwTelnetPort))
        {
            return ERR_OSP_Init;
        }
        else
        {
            m_bInitOsp = FALSE;
        }
    }
    else
    {
        m_bInitOsp = TRUE;
    }

    char szOspApp[] = "RkcLib";
    const u32 dwPrior = 80;
    int nRet = g_RckApp.CreateApp(&szOspApp[0], AID_RKC_APP, dwPrior, 300, 200);
    ASSERT(nRet == 0);

    PrtRkcMsg( "RkcLib osp�����ɹ�\n" );

    return NO_ERROR;
}

/*��ȡ�ӿ�ָ��*/
u16 CRkcSession::RkcGetInterface(CRkcSysCtrlIF **ppCtrl)
{
    if( m_pSysCtrlIf != NULL)
    {
        *ppCtrl = m_pSysCtrlIf;
        return NO_ERROR;
    }
    else
    {
        *ppCtrl = NULL;
        return ERR_RKC;
    }
}
u16 CRkcSession::RkcGetInterface(CCamConfigIF **ppCtrl)
{
    if( m_pCamConfigIf != NULL)
    {
        *ppCtrl = m_pCamConfigIf;
        return NO_ERROR;
    }
    else
    {
        *ppCtrl = NULL;
        return ERR_RKC;
    }
}
u16 CRkcSession::RkcGetInterface(CSysConfigIF **ppCtrl)
{
    if( m_pSysConfigIf != NULL)
    {
        *ppCtrl = m_pSysConfigIf;
        return NO_ERROR;
    }
    else
    {
        *ppCtrl = NULL;
        return ERR_RKC;
    }
}


void CRkcSession::DispEvent(const CMessage &cMsg)
{
    DISP_FUN(CRkcSession, cMsg);
}

void CRkcSession::OnTimeOut(u16 wEvent)
{ 
}


