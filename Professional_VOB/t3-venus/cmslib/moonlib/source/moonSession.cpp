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
//在该类中，new出所有的功能类，外部通过接口GetInterface()获取
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
	//如果未断开连接，则需要先断开
	if( IsConnectedMoon() )
    {
        DisconnectMoon();
        /* 已没有机会收到OSP断链通知了
        所以伪造一个,以触发断链动作*/
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

//释放空间
#define DEL_UNREG(pCtrlIF, clsName)           \
	UnregHandler(pCtrlIF);					  \
	if(NULL != pCtrlIF)                       \
	delete dynamic_cast<clsName*>(pCtrlIF);   \
	pCtrlIF = NULL;

 	DEL_UNREG( m_pCamConfigIF, CCamConfig );
 	DEL_UNREG( m_pSysConfigIF, CSysConfig );

#undef DEL_UNREG

	// 强制断开连接 清空静态变量
    if(IsConnectedMoon())
    {
        DisconnectMoon();
    }
	// 置OSP通知目的窗口为空
    g_MoonApp.SetNotifyWindow(NULL);
    g_MoonApp.SetNodeId(INVALID_NODE);
    g_MoonApp.ClearOspMsg();
	// 如果OSP是自己初始化的，则需要退出OSP
    if(!m_bInitOsp)
    {
        OspQuit();
    }
}



u16 CMoonSession::PostMsg( u32 dwType /* = TYPE_CMESSAGE */)
{
	//判断当前是否满足向cns发送消息的条件，不满足的话就直接返回
	
	return CMoonMsgDriver::PostMsg( dwType );
}

/*=============================================================================
  函 数 名： DispEvent
  功    能： 分发消息处理
  算法实现： 
  全局变量： 
  参    数： const CMessage &cMsg
  返 回 值： void 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2011/04/28    1.0		    肖楚然                  创建
=============================================================================*/
void CMoonSession::DispEvent(const CMessage &cMsg)
{
    DISP_FUN(CMoonSession, cMsg);
}

/*=============================================================================
  函 数 名： OnTimeOut
  功    能： 超时消息处理
  算法实现： 
  全局变量： 
  参    数： u16 wEvent
  返 回 值： void 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2011/04/28    1.0		    肖楚然                  创建
=============================================================================*/
void CMoonSession::OnTimeOut(u16 wEvent)
{ 
    //处理超时消息
    if(wEvent == ev_TpMoonLogin_Req/*ev_CnLogin_Rsp*/)
    {
        // OSP通道建立成功,但ACK NACK都没有收到
        OspDisconnectTcpNode(g_MoonApp.GetNodeId());
        g_MoonApp.SetNodeId(INVALID_NODE);

		PostEvent(UI_CNS_LOGIN_TIMEOUT, wEvent);
    }

	// 发送超时事件通知
	//PostEvent(UI_UMS_CMD_TIMEOUT, wEvent);    
}

/*===========================================================================
  函 数 名： CncGetInterface
  功    能： 获取接口指针
  算法实现： 
  全局变量： 
  参    数： 
  返 回 值： 
 ----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2011/04/28    1.0		    肖楚然                  创建
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
  函 数 名： CncGetInterface
  功    能： 获取接口指针
  算法实现： 
  全局变量： 
  参    数： 
  返 回 值： 
 ----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2011/04/28    1.0		    肖楚然                  创建
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
  函 数 名： IsConnectedCns
  功    能： 是否已和CNS建立了连接
  算法实现： 
  全局变量： 
  参    数： 
  返 回 值： BOOL32
 ----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2011/04/28    1.0		    肖楚然                  创建
===========================================================================*/
BOOL CMoonSession::IsConnectedMoon()
{
	return g_MoonApp.GetNodeId() != INVALID_NODE;
}

/*===========================================================================
  函 数 名： ConnectMoon
  功    能： 连接Moon90
  算法实现： 
  全局变量： 
  参    数： u32 dwIP    要连接的终端IP 本机序
             u32 dwPort  连接端口
  返 回 值： u16 
 ----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2014/11/27    1.0		    吴蒨蒨                  创建
===========================================================================*/
u16 CMoonSession::ConnectMoon(u32 dwIP, u32 dwPort, BOOL32 bConnect /* = TRUE */)
{
    // 建立TCP连接
    if( IsConnectedMoon() )
    { 
        //如何已经登录了该IP，则直接返回，否则断开重连
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
    // 重构消息分发表
    //BuildEventsMap();
    
    //建立Osp的TCP连接,得到本地机器的IP地址
	u32 dwCnNodeId = 0;
	if ( bConnect )
	{
		dwCnNodeId = OspConnectTcpNode( htonl(dwIP), static_cast<u16>(dwPort), /*5*/10   
			, 3, 5000/*30000*/, &m_dwLocalIP );
		//保留登陆Moon90的ip
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
    //设置在node连接中断时需通知的appid和InstId
    ::OspNodeDiscCBReg( dwCnNodeId, /*AID_CNC2CNS_APP*/GetAppID(), 1);

	// 向MOON90发送登录请求
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
  函 数 名： DisconnectMoon
  功    能： 断开Moon90三眼摄像机
  算法实现： 
  全局变量： 
  参    数： 
  返 回 值： u16 
 ----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2014/11/27    1.0		    吴蒨蒨                  创建
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
  函 数 名： BuildEventsMap
  功    能： 构建消息映射表
  算法实现： REG_PFUN():在70/common/kdvdispevent.h中实现，第一个参数为要处理的消息号，第二个参数为ex_XXX对应的处理函数
  全局变量： 
  参    数： 
  返 回 值： u16 
 ----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2011/04/28    1.0		    肖楚然                  创建
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
	// OSP断链通知
    u32 dwNodeId = *(u32*)(cMsg.content);

    PrtMsg( OSP_DISCONNECT, emEventTypeCnsRecv, "Link Break (NodeID: %d)", dwNodeId );

    ClearWaiting();	// OSP断链后,尚未执行完的命令中断执行 
	ClearAllCommand(); // 清空所有在队列中等待执行的命令
    g_MoonApp.ClearOspMsg(); //2012-7-12

    //与cns断链，但与tpad未断链，不将NodeId置空
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
	case tp_LoginUms_NameError: //用户名错误
		bLogin = FALSE;
		dwErrCode = ERR_UMC_LOGIN_UMS_USER_ERR;
		break;
	case tp_LoginUms_PwdError:	//密码错误
		bLogin = FALSE;
		dwErrCode = ERR_UMC_LOGIN_UMS_PSWD_ERR;
		break;
	case tp_LoginUms_MaxLogin:	//达到用户登录上限
		bLogin = FALSE;
		dwErrCode = ERR_UMC_LOGIN_UMS_MAX_LOGIN;
		break;
	case tp_LoginUms_Logged:	//用户已经登录
		bLogin = FALSE;
		dwErrCode = ERR_UMC_LOGIN_UMS_LOGED;
		break;
    case tp_LoginUms_SysIniting: //系统正在初始化
        bLogin = FALSE;
        dwErrCode = ERR_UMC_LOGIN_UMS_SYSINITING;
		break;
	default:
		bLogin = FALSE;
		dwErrCode = ERR_UMC_LOGIN_FAIL;
		break;
	} 
	
	// 通知界面
	PostEvent(UI_MOONTOOL_CONNECTED, bLogin, dwErrCode);

}

void CMoonSession::OnLoginCnsInsRsp(const CMessage& cMsg)
{

}

void CMoonSession::InitEnv( u16 wAppID, u32 dwDesIID )
{
	SetAppID( wAppID );
    SetDesIID( dwDesIID );
	// 初始化Osp
    u16 wRet = InitializeOsp();
    ASSERT(wRet == NO_ERROR);	
}

u16 CMoonSession::InitializeOsp()
{
	// 初始化OSP
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
    
    // 构造事件映射表
	BuildEventsMap(); 
	
	char szOspApp[] = "MoonLib1.0";
	const u32 dwPrior = 80;
	int nRet = g_MoonApp.CreateApp(&szOspApp[0], GetAppID(), dwPrior, 300, 200);
	ASSERT(nRet == 0);
    
	PrtMsg( "MoonLib osp启动成功\n" );
	
    return NO_ERROR;
}

void CMoonSession::OnLoginByOtherNotify( const CMessage& cMsg )
{
	u32 dwIP = *reinterpret_cast<u32*>( cMsg.content );
	
	in_addr tAddr;
	tAddr.S_un.S_addr = dwIP ;   
	PrtMsg( ev_TpMoonLoginByOther_Nty, emEventTypeCnsRecv, "抢登通知(抢占方 IP:  %s ；dwIP=%d )", inet_ntoa(tAddr), dwIP );
	
	PostEvent( UI_UMS_GRAB_LOGIN_NOTIFY, (WPARAM)dwIP );
}


