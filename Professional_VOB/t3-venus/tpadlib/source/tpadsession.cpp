// tpadsession.cpp: implementation of the CTPadSession class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "tpadsession.h"
#include "tpadinstance.h"
#include "msgtransinstance.h"
#include "addrinstance.h"

#include "cnsinnerstruct.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTPadSession::CTPadSession()
{
    m_bInitOsp = FALSE;
    m_dwCnsIp = 0;
    m_dwLocalIP = 0;
	m_bRecvDual = FALSE;
	m_nVideoNode = TP_INVALID_INDEX;
	m_nAudioNode = TP_INVALID_INDEX;

	m_pTpadSession = this;

    RegHandler(this);
}

CTPadSession::~CTPadSession()
{
    ClearDisp();
	UnregHandler(this);

    // 强制断开连接 清空静态变量
    if(IsConnectedCns())
    {
        DisconnectCns();
    }

    SetNodeId(INVALID_NODE);
    MsgTransDriver->ClearOspMsg();

    // 如果OSP是自己初始化的，则需要退出OSP
    if(!m_bInitOsp)
    {
        OspQuit();
    }
}

void CTPadSession::InitEnv( u32 dwAppID )
{
    SetAppId( dwAppID );
    // 初始化Osp
    u16 wRet = InitializeOsp();
    ASSERT(wRet == NO_ERROR);
}



void CTPadSession::DispEvent(const CMessage &cMsg)
{
    DISP_FUN(CTPadSession, cMsg);
}

void CTPadSession::BuildEventsMap()
{
    REG_PFUN( OSP_DISCONNECT, OnLinkBreak );
    REG_PFUN( ev_CnLogin_Rsp, OnCnsLoginRsp );

    REG_PFUN( ev_CNSLoginByOther_Notify, OnLoginByOtherNotify );
    REG_PFUN( ev_TpadUpdateSystem_Cmd, OnTpadUpdateCmd );
    REG_PFUN( ev_Cn_CentreSleepNty, OnCentreSleepNty );  
    
    REG_PFUN( ev_TPadSetSysName_Nty, OnCncSetSystemName );
	REG_PFUN( ev_TpadDisconnectCns_Nty, DisConnectTpad );
	REG_PFUN( ev_TppIsRcvDual_Nty, OnRecvDualNty );

	REG_PFUN( ev_TppAddDualRcvAddr_Ind, OnStartDualCdStrmRsp );
    REG_PFUN( ev_TppDelDualRcvAddr_Ind, OnStopDualCdStrmRsp );

	//	REG_PFUN( ev_TppTPadDualRcvAddr_Ind, OnFileDualRcvAddrInd );
	REG_PFUN( ev_TppTPadDualVideo_Ind, OnFileDualInd );
	REG_PFUN( ev_TppTPadDualRcvAddr_Cmd, OnFileDualRcvInd );
	REG_PFUN( ev_tppSndKeyFrame_Req, OnFileDualKeyFrame );
	
	//	REG_PFUN( ev_TppTPadDualVideoRes_Ind, OnFileDualEmResInd );
	//	REG_PFUN( ev_TppCodecVidEncParam_Cmd, OnFileDualEncParamInd );
	//	REG_PFUN( ev_TppCodecEncryptKey_Cmd, OnFileDualKeyInd );
	REG_PFUN( ev_tppCodecDynamicPayloadCmd, OnFileDualPayloadInd );
	REG_PFUN( ev_CnConfState_Nty, OnConfStateNty );	
}


void CTPadSession::OnTimeOut(u16 wEvent)
{ 
    //处理超时消息
    if( wEvent == ev_CnLogin_Req )
    {
        // OSP通道建立成功,但ACK NACK都没有收到
        OspDisconnectTcpNode( GetNodeId() );
        SetNodeId(INVALID_NODE);

        PostEvent( UI_CNS_LOGIN_TIMEOUT, wEvent );
    }
}


u16 CTPadSession::ConnectCns(u32 dwIP, u32 dwPort, const CString &strUser, 
							 const CString &strPwd, s8* achVersion, BOOL32 bConnect /* = TRUE */)
{
    // 建立TCP连接
    if( IsConnectedCns() )
    { 
        //如何已经登录了该IP，则直接返回，否则断开重连
        if ( dwIP == m_dwCnsIp )
        {
            return ERR_TPAD_ACTIVE_CONNECT;
        }
        else
        {
            DisconnectCns();
			return ERR_TPAD_ACTIVE_CONNECT;
        }      
    }
    
    //建立Osp的TCP连接,得到本地机器的IP地址
	u32 dwCnNodeId = 0;
	if ( bConnect )
	{
		dwCnNodeId = OspConnectTcpNode( htonl(dwIP), static_cast<u16>(dwPort), /*5*/10  
			, 3, 5000/*30000*/, &m_dwLocalIP );
		//保留登陆Cns的ip
		m_dwCnsIp = dwIP;
		m_dwLocalIP = ntohl( m_dwLocalIP );
		if( dwCnNodeId == INVALID_NODE )
		{
			return ERR_TPAD_TCPCONNECT;
		}		
	}

    SetNodeId( dwCnNodeId );
    //设置在node连接中断时需通知的appid和InstId
    ::OspNodeDiscCBReg( dwCnNodeId, GetAppId(), 1 );

	m_cUser.Empty();
    m_cUser.SetName((s8*)(LPCTSTR)strUser);
    m_cUser.SetPassword((s8*)(LPCTSTR)strPwd);

    TTPTPadLoginRequest tLoginRequest;
    tLoginRequest.cLoginRequest = m_cUser;
    memcpy( tLoginRequest.achTPadVersion, achVersion, MAX_DEVICEVER_LEN );

    // 向CNS发送登录请求
    u8 abyTemp[sizeof(TTPTPadLoginRequest) + 1] = {0};
    ZeroMemory(&m_cMsg, sizeof(CMessage));
    m_cMsg.event = ev_CnLogin_Req;
    m_cMsg.length = sizeof(TTPTPadLoginRequest);
	memcpy( abyTemp, &tLoginRequest, sizeof(TTPTPadLoginRequest) );

    m_cMsg.content = abyTemp;

    u16 awEvent[1];
    awEvent[0] = ev_CnLogin_Rsp;
	u16 wRet = PostCommand(this, awEvent, 1, TYPE_CMESSAGE, 3000);

	PrtMsg( ev_CnLogin_Req,emEventTypeCnsSend, "UserName=%s, Version=%s", m_cUser.GetName(), achVersion );

	return wRet;
}


BOOL CTPadSession::IsConnectedCns()
{
    return ( GetNodeId() != INVALID_NODE );
}


u16 CTPadSession::DisconnectCns()
{
    if( !IsConnectedCns() )
    {
        return NO_ERROR;
    }
    
    OspDisconnectTcpNode( GetNodeId() );
    m_dwCnsIp = 0;
    
    return NO_ERROR;
}


void CTPadSession::OnLinkBreak(const CMessage& cMsg)
{
    // OSP断链通知
    u32 u32NodeId = *(u32*)(cMsg.content);
    
    PrtMsg( OSP_DISCONNECT, emEventTypeCnsRecv, "Link Break (NodeID: %d)", u32NodeId );
    
    ClearWaiting();	// OSP断链后,尚未执行完的命令中断执行 
    ClearAllCommand(); // 清空所有在队列中等待执行的命令
    MsgTransDriver->ClearOspMsg();
    
    m_cUser.SetName("");
    m_cUser.SetPassword("");
    SetNodeId(INVALID_NODE);
    m_dwCnsIp = 0;
	m_bRecvDual = FALSE;
    
    PostEvent(UI_CNS_DISCONNECTED);
}


void CTPadSession::OnCnsLoginRsp(const CMessage& cMsg)
{
    // 	CTpMsg cTpMsg(&cMsg);
    // 	TLoginRet tLogRe = *reinterpret_cast<TLoginRet *>(cTpMsg.GetBody());
    
    TLoginRet tLogRe = *reinterpret_cast<TLoginRet *>( cMsg.content );

    EmTpLoginUmsRet emRet = tLogRe.GetRet();
    
    PrtMsg( ev_CnLogin_Rsp, emEventTypeCnsRecv,"EmTpLoginUmsRet: %d, ErrorCode: %d ", emRet, tLogRe.m_dwErrorCode );
    
    BOOL bLogin = FALSE;
    u32 dwErrCode = NO_ERROR;
    if ( emRet == tp_LoginUms_sucess )
    {
         bLogin = TRUE;
    }
    
    // 通知界面
    PostEvent( UI_CNS_CONNECTED, bLogin, emRet );
    
    if ( bLogin )
    {
        //通知登录用户信息
        NotifyLoginUser();
    }
    else
    {
        DisconnectCns();
    }
    
}


void CTPadSession::NotifyLoginUser()
{
    CMessage cMsg;
    u8 abyTemp[sizeof(TPadLoginInfo) + 1] = {0};
    ZeroMemory(&cMsg, sizeof(CMessage));

    TPadLoginInfo tLoginInfo;
    tLoginInfo.dwCnsIp = m_dwCnsIp;
    tLoginInfo.dwLocalIp = m_dwLocalIP;
    tLoginInfo.cUserInfo = m_cUser;

    cMsg.event = ev_TPadLoginInfo_Nty;
    cMsg.length = sizeof(TPadLoginInfo);
    memcpy( abyTemp, &tLoginInfo, sizeof(TPadLoginInfo) );
    cMsg.content = abyTemp;

    MsgTransDriver->DispatchMsg( &cMsg );
}


//被抢断
void CTPadSession::OnLoginByOtherNotify(const CMessage& cMsg)
{
    u32 dwIP = *reinterpret_cast<u32*>( cMsg.content );
    
    in_addr tAddr;
    tAddr.S_un.S_addr = dwIP ;   
    PrtMsg( ev_CNSLoginByOther_Notify, emEventTypeCnsRecv, "抢登通知(抢占方IP: %s)", inet_ntoa(tAddr) );
    
    PostEvent( UI_UMS_GRAB_LOGIN_NOTIFY, (WPARAM)dwIP );
}


void CTPadSession::OnTpadUpdateCmd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    TTPTPadVerInfo tVerInfo = *(TTPTPadVerInfo*)(cTpMsg.GetBody());

    PrtMsg( ev_TpadUpdateSystem_Cmd, emEventTypeCnsRecv, "EmTPUpdateType: %d, TPadVersion: %s, FilePath: %s",
		tVerInfo.m_emTPUpdateType, tVerInfo.m_achTPadVersion, tVerInfo.m_tPadVerFileInfo.achFilePath );

    PostEvent( UI_TPAD_UPDATESYS_CMD, (WPARAM)&tVerInfo );
}


void CTPadSession::OnCentreSleepNty(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    PrtMsg( ev_Cn_CentreSleepNty, emEventTypeCnsRecv, "" );
    
    PostEvent( UI_TPAD_CENTRESLEEP_NTY );
}



u16 CTPadSession::InitializeOsp()
{
    // 初始化OSP
    const u32 dwTelnetPort = 0;
    if( !IsOspInitd() )
    {
        
        BOOL bTelnet  = FALSE ;
        
#ifdef _DEBUG
        bTelnet = TRUE;
#endif
        
        if( !OspInit( bTelnet, dwTelnetPort) )
        {
            return ERR_TPAD_OSPINIT;
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
       
    //启动tpad连接cns App
    char szOspApp[] = "TPadLib1.0";
    const u32 dwPrior = 80;
    int nRet = g_tPadApp.CreateApp( &szOspApp[0], /*AID_CNC2CNS_APP*/GetAppId(), dwPrior, 300, 200 );
    ASSERT(nRet == 0);

    // 构造事件映射表
	BuildEventsMap(); 

    //创建本地监听节点
    nRet = ::OspCreateTcpNode( 0, TPAD_LISTEN_PORT );
    if (INVALID_SOCKET == nRet)
    {
        return ERR_TPAD_CREAT_TCPNODE;
	}

    //启动消息转发App
    nRet = g_MsgTransApp.CreateApp( "MsgTrans", AID_TPAD_MSGTRANS, dwPrior, 300, 200 );
    ASSERT(nRet == 0);

    //启动地址簿App
    nRet = g_AddrBookApp.CreateApp( "Addrbook", AID_ADDRBOOK, dwPrior, 300, 1024);
	ASSERT(nRet == 0);

    PrtMsg( "TPadLib osp启动成功\n" );
    
    return NO_ERROR;
}



void CTPadSession::OnCncSetSystemName(const CMessage& cMsg)//dyy
{   
    u8 achName[TP_MAX_ALIAS_LEN] = {0};
    memcpy( achName, cMsg.content, sizeof(achName) );

    PrtMsg( ev_TPadSetSysName_Nty, emEventTypeCnsRecv, "cnc系统名称: %s", achName );
    
    PostEvent( UI_TPAD_SETSYSNAME, (WPARAM)achName ); 
}


u16 CTPadSession::StartDualCodeStream( const TTPCnMediaTransPort  &tVideoTransAddr , const TTPCnMediaTransPort  &tAudioTransAddr ) const
{ 	
    CTpMsg *pcTpMsg = m_pTpadSession->GetKdvMsgPtr();
	
	pcTpMsg->SetUserData(1);
    pcTpMsg->SetEvent( ev_TppAddDualRcvAddr_Cmd ); 
    pcTpMsg->SetBody( &tVideoTransAddr, sizeof(TTPCnMediaTransPort) );  
    pcTpMsg->CatBody( &tAudioTransAddr, sizeof(TTPCnMediaTransPort) );
	
    u16 wRet = m_pTpadSession->PostMsg(TYPE_TPMSG);
    
    in_addr tAddr;
    tAddr.S_un.S_addr = tVideoTransAddr.m_tRtpPort.m_dwIP;
	
    PrtMsg( ev_TppAddDualRcvAddr_Cmd, emEventTypeCnsSend, "VideoAddr: %s, Port: %d", inet_ntoa(tAddr), tVideoTransAddr.m_tRtpPort.m_wPort );
	return wRet;
	
}


u16 CTPadSession::StopDualCodeStream() const 
{   
    CTpMsg *pcTpMsg = m_pTpadSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData(1);
    pcTpMsg->SetEvent( ev_TppDelDualRcvAddr_Cmd );  
    pcTpMsg->SetBody( &m_nVideoNode, sizeof(u16) );
    
	
    u16 wRet = m_pTpadSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_TppDelDualRcvAddr_Cmd, emEventTypeCnsSend,"" ); 
	
	
    pcTpMsg->SetBody( &m_nAudioNode, sizeof(u16)  );
    wRet = m_pTpadSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_TppDelDualRcvAddr_Cmd, emEventTypeCnsSend,"" );
	
	
	return wRet;
}

u16 CTPadSession::ReqKeyFrame( BOOL32 bForce ) const 
{
    CTpMsg *pcTpMsg = m_pTpadSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData(1);
    pcTpMsg->SetEvent( ev_TppPadDualKeyFrame_Req  );  
    pcTpMsg->SetBody( &m_nVideoNode, sizeof(u16) );
	pcTpMsg->CatBody( &bForce, sizeof(BOOL32) );
    
    u16 wRet = m_pTpadSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_TppPadDualKeyFrame_Req , emEventTypeCnsSend ,"");
	return wRet;
}

void CTPadSession::OnRecvDualNty( const CMessage &cMsg )
{
    CTpMsg cTpMsg(&cMsg); 
    
    u8 uInst = cTpMsg.GetHomeplace();
    
    BOOL bDual = *(BOOL*)(cTpMsg.GetBody());
    PrtMsg( ev_TppIsRcvDual_Nty, emEventTypeCnsRecv, "bRcvDual: %d, Inst: %d ", bDual, uInst );
    
    if ( m_bRecvDual!= bDual )
    {
        m_bRecvDual = bDual;
        PostEvent( UI_CNS_RECV_DUAL_NOTIFY, m_bRecvDual, 0 ); 
    }		
}

void CTPadSession::OnStartDualCdStrmRsp( const CMessage &cMsg )
{
    CTpMsg cTpMsg(&cMsg);    

    EmTPAddDualRcvResult emReVideo = *(EmTPAddDualRcvResult*)(cTpMsg.GetBody()); 
   
    if ( emReVideo == emAddDualRcvSucceed )
    {
        m_tVideoTranAddr = *(TTPCnMediaTransPort*)(cTpMsg.GetBody() + sizeof( EmTPAddDualRcvResult )*2 );
        
        m_nVideoNode = *(u16*)(cTpMsg.GetBody() + 
                                    sizeof( EmTPAddDualRcvResult ) * 2 +
                                    sizeof(TTPCnMediaTransPort ) * 2  );

        
    }
    

    EmTPAddDualRcvResult emReAudio = *(EmTPAddDualRcvResult*)(cTpMsg.GetBody() + sizeof( EmTPAddDualRcvResult ) ); 
    if ( emReAudio == emAddDualRcvSucceed )
    {
        m_tAudioTranAddr = *(TTPCnMediaTransPort*)(cTpMsg.GetBody() + sizeof( EmTPAddDualRcvResult )*2 + 
                                 sizeof(TTPCnMediaTransPort ) );
        
        m_nAudioNode = *(u16*)(cTpMsg.GetBody() +  sizeof( EmTPAddDualRcvResult )*2 + 
                                  sizeof(TTPCnMediaTransPort )*2 + sizeof(u16 ) );
    }

    u8 uInst = cTpMsg.GetHomeplace();     
    
    PrtMsg( ev_TppAddDualRcvAddr_Ind, emEventTypeCnsRecv, "Inst: %d, emVideoReason:%d , emAudioReaso=%d  \
( %d:emAddDualRcvSucceed,%d:emAddDualRcvFailNoDual,%d:emAddDualRcvFailIllegalPos，%d:emAddDualRcvFailNoPos, \
%d:emAddDualRcvFailUnKown)",uInst, emReVideo,emReAudio, emAddDualRcvSucceed,emAddDualRcvFailNoDual,
emAddDualRcvFailIllegalPos,emAddDualRcvFailNoPos,emAddDualRcvFailUnKown );
     
    
    
    PostEvent( UI_CNSINS_START_DUALCODESTREAM_RSP,  emReVideo , emReAudio ); 
}

void CTPadSession::OnStopDualCdStrmRsp( const CMessage &cMsg )
{
    CTpMsg cTpMsg(&cMsg); 
	
    m_nVideoNode = TP_INVALID_INDEX;
    m_nAudioNode = TP_INVALID_INDEX;
	
	EmTPDeleteDualRcvResult emReVideo = *(EmTPDeleteDualRcvResult*)(cTpMsg.GetBody());
	
	PrtMsg( ev_TppDelDualRcvAddr_Ind, emEventTypeCnsRecv, "" );
}


BOOL CTPadSession::IsReadyLogin( vector<TNodeInfo>&vctNodeList )//dyy
{
    return MsgTransDriver->IsAlreadyReg( vctNodeList );
}

//文件共享
u16 CTPadSession::FileDualCmd( BOOL bStart )
{
    CTpMsg *pcTpMsg = m_pTpadSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( 1 );
    
    pcTpMsg->SetEvent( ev_TppTPadDualVideo_Cmd );
    pcTpMsg->SetBody( &bStart, sizeof(BOOL) );
  
    u16 wRet = m_pTpadSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_TppTPadDualVideo_Cmd, emEventTypeCnsSend, "bStart:%d", bStart );
    return wRet;
}

u16 CTPadSession::FileDualRcvAddrCmd( EmTPAddDualRcvResult emAddDualRcvRes, TTPCnMediaTransPort &tVideoTransAddr, u16 nVideoNode )
{    
	CTpMsg *pcTpMsg = m_pTpadSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( 1 );
    
    pcTpMsg->SetEvent( ev_TppTPadDualRcvAddr_Ind );
    pcTpMsg->SetBody( &emAddDualRcvRes, sizeof(EmTPAddDualRcvResult) );
	pcTpMsg->CatBody( &tVideoTransAddr, sizeof(TTPCnMediaTransPort) );
	pcTpMsg->CatBody( &nVideoNode, sizeof(u16) );
	
	m_tVideoTransAddr = tVideoTransAddr;
    in_addr tAddr;
    tAddr.S_un.S_addr = tVideoTransAddr.m_tBackRtcpPort.m_dwIP;
	
    PrtMsg( ev_TppTPadDualRcvAddr_Ind, emEventTypeCnsSend, "emVideoReason:%d, FileVideoAddr: %s, Port: %d, nVideoNode:%d \
		( %d:emAddDualRcvSucceed,%d:emAddDualRcvFailNoDual,%d:emAddDualRcvFailIllegalPos，%d:emAddDualRcvFailNoPos, %d:emAddDualRcvFailUnKown)", 
		emAddDualRcvRes, inet_ntoa(tAddr), tVideoTransAddr.m_tBackRtcpPort.m_wPort, nVideoNode,emAddDualRcvSucceed,emAddDualRcvFailNoDual,emAddDualRcvFailIllegalPos,emAddDualRcvFailNoPos,emAddDualRcvFailUnKown );
	
    u16 wRet = m_pTpadSession->PostMsg(TYPE_TPMSG);
    return wRet;
}

void CTPadSession::OnFileDualRcvInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg); 
	
    TTPCnMediaTransPort tVideoTransAddr = *(TTPCnMediaTransPort*)(cTpMsg.GetBody()); 
	
	m_tVideoTransAddr = tVideoTransAddr;
    in_addr tAddr;
    tAddr.S_un.S_addr = tVideoTransAddr.m_tRtpPort.m_dwIP;
	
    PrtMsg( ev_TppTPadDualRcvAddr_Cmd, emEventTypeCnsRecv, "FileVideoAddr: %s, Port: %d", inet_ntoa(tAddr), tVideoTransAddr.m_tRtpPort.m_wPort );

	PostEvent( UI_FILE_DUAL_RCVADDR, 0, 0 );
}

TTPCnMediaTransPort& CTPadSession::GetFileDualTransPort()
{
	return m_tVideoTransAddr;
}

void CTPadSession::OnFileDualInd( const CMessage &cMsg )
{    
    CTpMsg cTpMsg(&cMsg); 
	
    BOOL bPCDual = *(BOOL*)( cTpMsg.GetBody() ); 
	BOOL bStart = *(BOOL*)( cTpMsg.GetBody() + sizeof(BOOL) ); 
	
    PrtMsg( ev_TppTPadDualVideo_Ind, emEventTypeCnsRecv, "bPCDual: %d, bStart: %d", bPCDual, bStart );
    
    PostEvent( UI_FILE_DUAL_RESULT, (WPARAM)bPCDual, (LPARAM)bStart );
}

void CTPadSession::OnFileDualRcvAddrInd( const CMessage &cMsg )
{    
    CTpMsg cTpMsg(&cMsg); 
	
	EmTPAddDualRcvResult emAddDualRcvRes = *(EmTPAddDualRcvResult*)(cTpMsg.GetBody()); 
    TTPCnMediaTransPort tVideoTransAddr = *(TTPCnMediaTransPort*)(cTpMsg.GetBody() + sizeof(EmTPAddDualRcvResult) ); 
	u16 nVideoNode = *(u16*)(cTpMsg.GetBody() + sizeof(EmTPAddDualRcvResult) + sizeof(TTPCnMediaTransPort) ); 
	
	m_tVideoTransAddr = tVideoTransAddr;
    in_addr tAddr;
    tAddr.S_un.S_addr = tVideoTransAddr.m_tRtpPort.m_dwIP;

    PrtMsg( ev_TppTPadDualRcvAddr_Ind, emEventTypeCnsRecv, "emVideoReason:%d, FileVideoAddr: %s, Port: %d, nVideoNode:%d \
		( %d:emAddDualRcvSucceed,%d:emAddDualRcvFailNoDual,%d:emAddDualRcvFailIllegalPos，%d:emAddDualRcvFailNoPos, %d:emAddDualRcvFailUnKown)", 
		emAddDualRcvRes, inet_ntoa(tAddr), tVideoTransAddr.m_tRtpPort.m_wPort, nVideoNode,emAddDualRcvSucceed,emAddDualRcvFailNoDual,emAddDualRcvFailIllegalPos,emAddDualRcvFailNoPos,emAddDualRcvFailUnKown );

    //PostEvent( UI_RECV_DUAL_INTERRUPT, emReason, 0 ); 
}

void CTPadSession::OnFileDualEmResInd( const CMessage &cMsg )
{    
    CTpMsg cTpMsg(&cMsg); 
	
    EmVideoResolution emRes = *(EmVideoResolution*)( cTpMsg.GetBody() ); 
	
//    PrtMsg( ev_TppTPadDualVideoRes_Ind, emEventTypeCnsRecv, "EmVideoResolution: %d", emRes );
    
    //PostEvent( UI_RECV_DUAL_INTERRUPT, emReason, 0 ); 
}

void CTPadSession::OnFileDualEncParamInd( const CMessage &cMsg )
{    
    CTpMsg cTpMsg(&cMsg); 
	memset( &m_tVideoEncodeParam, 0, sizeof(m_tVideoEncodeParam) );
    EmCodecComponent emCode = *(EmCodecComponent*)( cTpMsg.GetBody() );
	m_tVideoEncodeParam = *(TTPMtVideoEncodeParameter*)( cTpMsg.GetBody() + sizeof(EmCodecComponent) );
	
//    PrtMsg( ev_TppCodecVidEncParam_Cmd, emEventTypeCnsRecv, "EmCodecComponent: %d", emCode );
    
    //PostEvent( UI_FILE_DUAL_EncParam, 0, 0 ); 
}

TTPMtVideoEncodeParameter& CTPadSession::GetFileDualEncParam()
{
	return m_tVideoEncodeParam;
}

void CTPadSession::OnFileDualKeyInd( const CMessage &cMsg )
{    
    CTpMsg cTpMsg(&cMsg); 
	memset( &m_tEncryptKey, 0, sizeof(m_tEncryptKey) );
    EmCodecComponent emCode = *(EmCodecComponent*)( cTpMsg.GetBody() );
	m_tEncryptKey = *(TEncryptKey*)( cTpMsg.GetBody() + sizeof(EmCodecComponent) );

//    PrtMsg( ev_TppCodecEncryptKey_Cmd, emEventTypeCnsRecv, "EmCodecComponent: %d , Len:%d , key:%s", emCode, m_tEncryptKey.byLen, m_tEncryptKey.byKey );
    
    PostEvent( UI_FILE_DUAL_KEY, 0, 0 ); 
}

TEncryptKey& CTPadSession::GetFileDualkey()
{
	return m_tEncryptKey;
}

void CTPadSession::OnFileDualPayloadInd( const CMessage &cMsg )
{    
    CTpMsg cTpMsg(&cMsg); 
	
    EmCodecComponent emCode = *(EmCodecComponent*)( cTpMsg.GetBody() );
	u8 byPayload1 = *(u8*)( cTpMsg.GetBody() + sizeof(EmCodecComponent) );
	u8 byPayload2 = *(u8*)( cTpMsg.GetBody() + sizeof(EmCodecComponent) + sizeof(u8) );

	m_byPayload = byPayload1;
    PrtMsg( ev_tppCodecDynamicPayloadCmd, emEventTypeCnsRecv, "EmCodecComponent: %d , byPayload1:%d , byPayload2:%d", emCode, byPayload1, byPayload2 );
    
    //PostEvent( UI_RECV_DUAL_INTERRUPT, emReason, 0 ); 
}

u8 CTPadSession::GetFileDualPayload()
{
	return m_byPayload;
}

void CTPadSession::OnConfStateNty( const CMessage &cMsg )
{    
    CTpMsg cTpMsg(&cMsg); 
			
    TTPCnsConfStatus tConfStatus = *reinterpret_cast<TTPCnsConfStatus*>(cTpMsg.GetBody());
	
	PrtMsg( ev_CnConfState_Nty, emEventTypeCnsRecv, "TTPCnsConfStatus: ConfName: %s, ConfID: %d, State: %d \
(%d:em_CALL_IDLE, %d:em_CALL_CALLING, %d:em_CALL_CONNECTED),\
ConfType: %d (%d:emCallType_P2P, %d:emCallType_Conf),  bMixMotive:%d  ", 
tConfStatus.achConfName, tConfStatus.wConfID, tConfStatus.emState, 
em_CALL_IDLE, em_CALL_CALLING, em_CALL_CONNECTED, tConfStatus.m_emCallType, emCallType_P2P, emCallType_Conf, tConfStatus.m_bMixMotive );
	
	m_tCnsConfStatus = tConfStatus;

    PostEvent( UI_CONFSTATE_NTY, 0, 0 ); 
}

TTPCnsConfStatus CTPadSession::GetCnsConfStatus() const
{
	return m_tCnsConfStatus;
}

void CTPadSession::OnFileDualKeyFrame( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg); 

    PrtMsg( ev_tppSndKeyFrame_Req, emEventTypeCnsRecv, "SndKeyFrame_Req" );
	
	PostEvent( UI_FILE_DUAL_KEYFRAME_REQ, 0, 0 );
}

void CTPadSession::TPadHomeKeyNty()
{
    CMessage cMsg;
    ZeroMemory(&cMsg, sizeof(CMessage));
      
    cMsg.event = ev_TPadHomeKey_Nty;
    
    MsgTransDriver->DispatchMsg( &cMsg );
}

void CTPadSession::DisConnectTpad( const CMessage& cMsg )
{
	DisconnectCns();
}
