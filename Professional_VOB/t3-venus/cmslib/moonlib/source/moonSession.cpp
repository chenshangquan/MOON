// cnsSession.cpp: implementation of the CCnsSession class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "moonSession.h"
#include "moonmsgrecver.h"
#include "cmsConst.h"
#include "tpcommontype.h"
#include "camconfig.h"
#include "sysconfig.h"
// #include "eventoutcnsallmsg.h"


u8 g_abyTemp[sizeof(CLoginRequest) + 1] = { 0 };

UINT g_wTimerID = 0;
void CALLBACK TimerProc(HWND hWnd,UINT nMsg,UINT nTimerid,DWORD dwTime);
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMoonSession* CMoonSession::s_pMoonSession = NULL;

CMoonSession::CMoonSession()
            :m_bInitOsp(FALSE)
{
	m_pCamConfigIF = NULL;
	m_pSysConfigIF = NULL;
	m_dwLocalIP = 0;
	m_dwMoonIp = 0;
	m_uInst = 0;

	g_MoonApp.SetNotifyWindow( GetOspRecvWindow() );

    s_pMoonSession = this;
    
	RegHandler(this);
//�ڸ����У�new�����еĹ����࣬�ⲿͨ���ӿ�GetInterface()��ȡ
#define NEW_REG(pCtrlIF, clsName)         \
		pCtrlIF = new clsName(*this);     \
		RegHandler(pCtrlIF);

	//NEW_REG( m_pAddrBookIF, CCncAddrbook );
 	NEW_REG( m_pCamConfigIF, CCamConfig );
 	NEW_REG( m_pSysConfigIF, CSysConfig );

#undef NEW_REG

}

CMoonSession::~CMoonSession()
{
	//���δ�Ͽ����ӣ�����Ҫ�ȶϿ�
	if( IsConnectedMoon() )
    {
        DisconnectMoon();
        /* ��û�л����յ�OSP����֪ͨ��
        ����α��һ��,�Դ�����������*/
        u32 dwNode = g_MoonApp.GetNodeId();
        CMessage msg;
        msg.event = OSP_DISCONNECT;
        msg.length = sizeof(u32);
        msg.content = (u8*)&dwNode;
        OnLinkBreak(msg);
    }

    if (g_wTimerID != 0)
    {
        KillTimer( NULL, g_wTimerID );
        g_wTimerID = 0;
    }

	ClearDisp();
	UnregHandler(this);

    s_pMoonSession = NULL;

//�ͷſռ�
#define DEL_UNREG(pCtrlIF, clsName)           \
	UnregHandler(pCtrlIF);					  \
	if(NULL != pCtrlIF)                       \
	delete dynamic_cast<clsName*>(pCtrlIF);   \
	pCtrlIF = NULL;

 	DEL_UNREG( m_pCamConfigIF, CCamConfig );
 	DEL_UNREG( m_pSysConfigIF, CSysConfig );

#undef DEL_UNREG

	// ǿ�ƶϿ����� ��վ�̬����
    if(IsConnectedMoon())
    {
        DisconnectMoon();
    }
	// ��OSP֪ͨĿ�Ĵ���Ϊ��
    g_MoonApp.SetNotifyWindow(NULL);
    g_MoonApp.SetNodeId(INVALID_NODE);
    g_MoonApp.ClearOspMsg();
	// ���OSP���Լ���ʼ���ģ�����Ҫ�˳�OSP
    if(!m_bInitOsp)
    {
        OspQuit();
    }
}



u16 CMoonSession::PostMsg( u32 dwType /* = TYPE_CMESSAGE */)
{
	//�жϵ�ǰ�Ƿ�������cns������Ϣ��������������Ļ���ֱ�ӷ���
	
	return CMoonMsgDriver::PostMsg( dwType );
}

/*=============================================================================
  �� �� ���� DispEvent
  ��    �ܣ� �ַ���Ϣ����
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� const CMessage &cMsg
  �� �� ֵ�� void 
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2011/04/28    1.0		    Ф��Ȼ                  ����
=============================================================================*/
void CMoonSession::DispEvent(const CMessage &cMsg)
{
    DISP_FUN(CMoonSession, cMsg);
}

/*=============================================================================
  �� �� ���� OnTimeOut
  ��    �ܣ� ��ʱ��Ϣ����
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� u16 wEvent
  �� �� ֵ�� void 
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2011/04/28    1.0		    Ф��Ȼ                  ����
=============================================================================*/
void CMoonSession::OnTimeOut(u16 wEvent)
{ 
    //����ʱ��Ϣ
    if(wEvent == ev_TpMoonLogin_Req/*ev_CnLogin_Rsp*/)
    {
        // OSPͨ�������ɹ�,��ACK NACK��û���յ�
        OspDisconnectTcpNode(g_MoonApp.GetNodeId());
        g_MoonApp.SetNodeId(INVALID_NODE);

		PostEvent(UI_CNS_LOGIN_TIMEOUT, wEvent);
    }

	// ���ͳ�ʱ�¼�֪ͨ
	//PostEvent(UI_UMS_CMD_TIMEOUT, wEvent);    
}

/*===========================================================================
  �� �� ���� CncGetInterface
  ��    �ܣ� ��ȡ�ӿ�ָ��
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� 
  �� �� ֵ�� 
 ----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2011/04/28    1.0		    Ф��Ȼ                  ����
===========================================================================*/
u16 CMoonSession::MoonGetInterface(CCamConfigIF **ppCtrl)
{
    if( m_pCamConfigIF != NULL)
    {
        *ppCtrl = m_pCamConfigIF;
        return NO_ERROR;
    }
    else
    {
        *ppCtrl = NULL;
        return ERR_CNC;
    }
}

/*===========================================================================
  �� �� ���� CncGetInterface
  ��    �ܣ� ��ȡ�ӿ�ָ��
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� 
  �� �� ֵ�� 
 ----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2011/04/28    1.0		    Ф��Ȼ                  ����
===========================================================================*/
u16 CMoonSession::MoonGetInterface(CSysConfigIF **ppCtrl)
{
    if( m_pSysConfigIF != NULL)
    {
        *ppCtrl = m_pSysConfigIF;
        return NO_ERROR;
    }
    else
    {
        *ppCtrl = NULL;
        return ERR_CNC;
    }
}

/*===========================================================================
  �� �� ���� IsConnectedCns
  ��    �ܣ� �Ƿ��Ѻ�CNS����������
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� 
  �� �� ֵ�� BOOL32
 ----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2011/04/28    1.0		    Ф��Ȼ                  ����
===========================================================================*/
BOOL CMoonSession::IsConnectedMoon()
{
	return g_MoonApp.GetNodeId() != INVALID_NODE;
}

/*===========================================================================
  �� �� ���� ConnectMoon
  ��    �ܣ� ����Moon90
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� u32 dwIP    Ҫ���ӵ��ն�IP ������
             u32 dwPort  ���Ӷ˿�
  �� �� ֵ�� u16 
 ----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2014/11/27    1.0		    ���`�`                  ����
===========================================================================*/
u16 CMoonSession::ConnectMoon(u32 dwIP, u32 dwPort, BOOL32 bConnect /* = TRUE */)
{
    // ����TCP����
    if( IsConnectedMoon() )
    { 
        //����Ѿ���¼�˸�IP����ֱ�ӷ��أ�����Ͽ�����
        if ( dwIP == m_dwMoonIp )
        {
             return ERR_CNC_ACTIVE_CONNECT;
        }
        else
        {
            DisconnectMoon();
			return ERR_CNC_ACTIVE_CONNECT;
        }
        
    }
    
    //ClearDisp();
    // �ع���Ϣ�ַ���
    //BuildEventsMap();
    
    //����Osp��TCP����,�õ����ػ�����IP��ַ
	u32 dwCnNodeId = 0;
	if ( bConnect )
	{
		dwCnNodeId = OspConnectTcpNode( htonl(dwIP), static_cast<u16>(dwPort), /*5*/10   
			, 3, 5000/*30000*/, &m_dwLocalIP );
		//������½Moon90��ip
		m_dwMoonIp = dwIP;
		m_dwLocalIP = ntohl( m_dwLocalIP );
		if( dwCnNodeId == INVALID_NODE )
		{
			return ERR_CNC_TCPCONNECT;
		}		
	}
	else
	{
		dwCnNodeId = 0;
	}

    g_MoonApp.SetNodeId( dwCnNodeId );
    //������node�����ж�ʱ��֪ͨ��appid��InstId
    ::OspNodeDiscCBReg( dwCnNodeId, /*AID_CNC2CNS_APP*/GetAppID(), 1);

	// ��MOON90���͵�¼����
	memset( g_abyTemp,0, sizeof( g_abyTemp ));
    ZeroMemory(&m_cMsg, sizeof(CMessage));
    m_cMsg.event = ev_TpMoonLogin_Req;
//    m_cMsg.length = sizeof(CLoginRequest);
// 	  memcpy( g_abyTemp, &m_cUser, sizeof(CLoginRequest) );
//    m_cMsg.content = g_abyTemp;

    u16 awEvent[1];
    awEvent[0] = ev_TpMoonLogin_Rsp;
	u16 wRet = PostCommand(this, awEvent, 1, TYPE_CMESSAGE, 3000);

	PrtMsg( ev_TpMoonLogin_Req, emEventTypeCnsSend, "userName:%s pswd:%s", m_cUser.GetName(), m_cUser.GetPassword() );

	return wRet;
}

/*===========================================================================
  �� �� ���� DisconnectMoon
  ��    �ܣ� �Ͽ�Moon90���������
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� 
  �� �� ֵ�� u16 
 ----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2014/11/27    1.0		    ���`�`                  ����
===========================================================================*/
u16 CMoonSession::DisconnectMoon()
{
    if( !IsConnectedMoon() )
    {
        return NO_ERROR;
    }
 
    OspDisconnectTcpNode(g_MoonApp.GetNodeId()); 
	m_dwMoonIp = 0;
    
    return NO_ERROR;
}


u16 CMoonSession::LoginMoonIns( u8 byIns )
{	
	CTpMsg *pcTpMsg = GetKdvMsgPtr();
	
	pcTpMsg->SetUserData( byIns );
	pcTpMsg->SetEvent( ev_TpMoonLogin_Req );

	m_uInst = byIns;
	
	u16 wRet = PostMsg(TYPE_TPMSG);
//	PrtMsg( ev_CnLoginIns_Req, emEventTypeCnsSend, "Inst: %d", m_uInst );
    return wRet;
}
/*===========================================================================
  �� �� ���� BuildEventsMap
  ��    �ܣ� ������Ϣӳ���
  �㷨ʵ�֣� REG_PFUN():��70/common/kdvdispevent.h��ʵ�֣���һ������ΪҪ�������Ϣ�ţ��ڶ�������Ϊex_XXX��Ӧ�Ĵ�����
  ȫ�ֱ����� 
  ��    ���� 
  �� �� ֵ�� u16 
 ----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2011/04/28    1.0		    Ф��Ȼ                  ����
===========================================================================*/
void CMoonSession::BuildEventsMap()
{
	REG_PFUN( OSP_DISCONNECT, OnLinkBreak );
	REG_PFUN( ev_TpMoonLogin_Rsp, OnMoonLoginRsp );
//	REG_PFUN( ev_CnLoginIns_Rsp, OnLoginCnsInsRsp );
	REG_PFUN( ev_TpMoonLoginByOther_Nty, OnLoginByOtherNotify );
}

void CMoonSession::OnLinkBreak(const CMessage& cMsg)
{
	// OSP����֪ͨ
    u32 dwNodeId = *(u32*)(cMsg.content);

    PrtMsg( OSP_DISCONNECT, emEventTypeCnsRecv, "Link Break (NodeID: %d)", dwNodeId );

    ClearWaiting();	// OSP������,��δִ����������ж�ִ�� 
	ClearAllCommand(); // ��������ڶ����еȴ�ִ�е�����
    g_MoonApp.ClearOspMsg(); //2012-7-12

    //��cns����������tpadδ����������NodeId�ÿ�
    if ( dwNodeId == g_MoonApp.GetNodeId() )
    {
        g_MoonApp.SetNodeId(INVALID_NODE);
    }

    m_cUser.SetName("");
	m_cUser.SetPassword(""); 
	m_dwMoonIp = 0;
	m_uInst = 0;

    PostEvent(UI_MOONTOOL_DISCONNECTED);
}


void CMoonSession::OnMoonLoginRsp(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	TLoginRet tLogRe = *reinterpret_cast<TLoginRet *>( cTpMsg.GetBody() );
	PrtMsg( ev_TpMoonLogin_Rsp, emEventTypemoontoolRecv,"EmTpLoginUmsRet: %d, ErrorCode: %d ", tLogRe.GetRet(), tLogRe.m_dwErrorCode );

	BOOL bLogin = FALSE;
	u32 dwErrCode = NO_ERROR;
	switch( tLogRe.GetRet() )
	{
	case tp_LoginUms_sucess:
		bLogin = TRUE;
		break;
	case tp_LoginUms_NameError: //�û�������
		bLogin = FALSE;
		dwErrCode = ERR_UMC_LOGIN_UMS_USER_ERR;
		break;
	case tp_LoginUms_PwdError:	//�������
		bLogin = FALSE;
		dwErrCode = ERR_UMC_LOGIN_UMS_PSWD_ERR;
		break;
	case tp_LoginUms_MaxLogin:	//�ﵽ�û���¼����
		bLogin = FALSE;
		dwErrCode = ERR_UMC_LOGIN_UMS_MAX_LOGIN;
		break;
	case tp_LoginUms_Logged:	//�û��Ѿ���¼
		bLogin = FALSE;
		dwErrCode = ERR_UMC_LOGIN_UMS_LOGED;
		break;
    case tp_LoginUms_SysIniting: //ϵͳ���ڳ�ʼ��
        bLogin = FALSE;
        dwErrCode = ERR_UMC_LOGIN_UMS_SYSINITING;
		break;
	default:
		bLogin = FALSE;
		dwErrCode = ERR_UMC_LOGIN_FAIL;
		break;
	} 
	
	// ֪ͨ����
	PostEvent(UI_MOONTOOL_CONNECTED, bLogin, dwErrCode);

}

void CMoonSession::OnLoginCnsInsRsp(const CMessage& cMsg)
{

}

void CMoonSession::InitEnv( u16 wAppID, u32 dwDesIID )
{
	SetAppID( wAppID );
    SetDesIID( dwDesIID );
	// ��ʼ��Osp
    u16 wRet = InitializeOsp();
    ASSERT(wRet == NO_ERROR);	
}

u16 CMoonSession::InitializeOsp()
{
	// ��ʼ��OSP
    const u32 dwTelnetPort = 0;
    if( !IsOspInitd() )
    {
		
        BOOL bTelnet  = FALSE ;
		
#ifdef _DEBUG
        bTelnet = TRUE;
#endif
		
        if(!OspInit( bTelnet, dwTelnetPort))
        {
            return ERR_CMS_OSP_Init;
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
    
    // �����¼�ӳ���
	BuildEventsMap(); 
	
	char szOspApp[] = "MoonLib1.0";
	const u32 dwPrior = 80;
	int nRet = g_MoonApp.CreateApp(&szOspApp[0], GetAppID(), dwPrior, 300, 200);
	ASSERT(nRet == 0);
    
	PrtMsg( "MoonLib osp�����ɹ�\n" );
	
    return NO_ERROR;
}

void CMoonSession::OnLoginByOtherNotify( const CMessage& cMsg )
{
	u32 dwIP = *reinterpret_cast<u32*>( cMsg.content );
	
	in_addr tAddr;
	tAddr.S_un.S_addr = dwIP ;   
	PrtMsg( ev_TpMoonLoginByOther_Nty, emEventTypeCnsRecv, "����֪ͨ(��ռ�� IP:  %s ��dwIP=%d )", inet_ntoa(tAddr), dwIP );
	
	PostEvent( UI_UMS_GRAB_LOGIN_NOTIFY, (WPARAM)dwIP );
}


