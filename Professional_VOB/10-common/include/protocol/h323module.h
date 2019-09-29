#ifndef H323MODULE_H
#define H323MODULE_H

#include "kdvtype.h"
#include "modulecallstruct.h"

#ifdef WIN32
#define H323CALLBACK __cdecl
#else
#define H323CALLBACK
#endif

extern BOOL32 g_bIsStackNull; 

typedef BOOL (H323CALLBACK* H323CBNewCallIncoming)( HMDLCALL hCall , TModuleCallInfo* pcCallInfo );
typedef BOOL (H323CALLBACK* H323CBCallDisconnected)( HMDLCALL hCall , HMDLAPPCALL hAppCall , EmModuleCallDisconnectReason emReason );
typedef BOOL (H323CALLBACK* H323CBCallConnected)( HMDLCALL hCall , HMDLAPPCALL hAppCall , TModuleCallInfo* pcCallInfo );
//added by sna for interworking [20140217]
typedef BOOL (H323CALLBACK* H323CBPeerRecvCapbility)( HMDLCALL hCall, HMDLAPPCALL hAppCall,  TCallCapbility* ptPeerRecvCapbility );
//added end

typedef struct tagH323CallCBFunction
{
	H323CBNewCallIncoming m_cbNewCallIncoming;
	H323CBCallDisconnected m_cbCallDisconnected;
	H323CBCallConnected m_cbCallConnected;
	H323CBPeerRecvCapbility m_cbPeerRecvCapbility;//added by sna for interworking [20170217]

	tagH323CallCBFunction()
	{
		m_cbNewCallIncoming = NULL;
		m_cbCallConnected = NULL;
		m_cbCallConnected = NULL;
		m_cbPeerRecvCapbility = NULL;
	}
}TH323CallCBFunction;


typedef BOOL (H323CALLBACK* H323CBChannelConnected)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TChanConnectedInfo* atChanConnectInfo, u8 bySize );
typedef BOOL (H323CALLBACK* H323CBChannelDisconnected)( HMDLCALL hCall , HMDLAPPCALL hAppCall , HMDLAPPCHANNEL hAppChan , HMDLCHANNEL hChan , u8 byReason );
typedef BOOL (H323CALLBACK* H323CBChannelFlowCtrl)( HMDLCALL hCall , HMDLAPPCALL hAppCall , HMDLAPPCHANNEL hAppChan , HMDLCHANNEL hChan , u16 wBitrate );
typedef BOOL (H323CALLBACK* H323CBChannelFastUpdate)( HMDLCALL hCall , HMDLAPPCALL hAppCall , HMDLAPPCHANNEL hAppChan , HMDLCHANNEL hChan );
typedef BOOL (H323CALLBACK* H323CBDualStreamIncoming)( HMDLCALL hCall, HMDLAPPCALL hAppCall, HMDLAPPCHANNEL hAppChan, HMDLCHANNEL hChan, TCallCapbility* ptDualCap );
typedef BOOL (H323CALLBACK* H323CBDualStreamConnected)( HMDLCALL hCall, HMDLAPPCALL hAppCall, HMDLAPPCHANNEL hAppChan, HMDLCHANNEL hChan, TChanConnectedInfo* ptChanInfo );
typedef BOOL (H323CALLBACK* H323CBDualStreamReject)( HMDLCALL hCall, HMDLAPPCALL hAppCall, HMDLAPPCHANNEL hAppChan, HMDLCHANNEL hChan );
typedef BOOL (H323CALLBACK* H323CBDualStreamStop)( HMDLCALL hCall, HMDLAPPCALL hAppCall, HMDLAPPCHANNEL hAppChan, HMDLCHANNEL hChan );
//added by sna for interworking's reopen [20140217]
typedef BOOL (H323CALLBACK* H323CBChanDisconnectedEx)( HMDLCALL hCall , HMDLAPPCALL hAppCall , HMDLAPPCHANNEL hAppChan , HMDLCHANNEL hChan , TChanConnectedInfo* ptChanDisconnectInfo);
//added end 

typedef struct tagH323ChannelCBFunction
{
	H323CBChannelConnected m_cbChannelConnected;
	H323CBChannelDisconnected m_cbChannelDisconnected;
	H323CBChannelFlowCtrl m_cbChannelFlowCtrl;
	H323CBChannelFastUpdate m_cbChannelFastUpdate;
	H323CBDualStreamIncoming m_cbDualStreamIncoming;
	H323CBDualStreamConnected m_cbDualStreamConnected;
	H323CBDualStreamReject m_cbDualStreamReject;
	H323CBDualStreamStop m_cbDualStreamStop;

	H323CBChanDisconnectedEx m_cbChanDisconnectedEx; //added by sna for interworking's reopen [20140217] 

	tagH323ChannelCBFunction()
	{
		memset( this , 0 , sizeof(tagH323ChannelCBFunction) );
	}
}TH323ChannelCBFunction;


typedef BOOL (H323CALLBACK* CBRegResult)( HMDLREG hReg , HMDLAPPREG hAppReg , u8* pbuf , u16 wLen );
typedef BOOL (H323CALLBACK* CBOnlineList)( HMDLREG hReg , HMDLAPPREG hAppReg , u32 dwAppId, u8* pbuf , u16 wLen );
typedef BOOL (H323CALLBACK* H323CBConfEvent)( HMDLCALL hCall, HMDLAPPCALL hAppCall, u16 wEvent, u8* pBuf, u16 wLen );
typedef BOOL (H323CALLBACK* H323CBFeccMsg)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMdlFeccStruct tFeccStruct );

//conf
// typedef BOOL (H323CALLBACK* H323CBMultipleConf)( HMDLCALL hCall, HMDLAPPCALL hAppCall ); //֪ͨ��ʼ������
// typedef BOOL (H323CALLBACK* H323CBConfList)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERINFOLIST tTerInfoList );  //�ص�����б�
// typedef BOOL (H323CALLBACK* H323CBTerLabel)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERLABEL tTerLabel );   //�ص�MC�����TerLabel
// typedef BOOL (H323CALLBACK* H323CBConfYouAreSee)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERLABEL tTerLabel); //�ص���ǰ������(YouAreSeeing)
// typedef BOOL (H323CALLBACK* H323CBSeeByAll )( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERLABEL tTerLabel );  //�ص�����ָʾ
// typedef BOOL (H323CALLBACK* H323CBConfTerJoin)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERLABEL tTerLabel ); //�ص����������ն�
// typedef BOOL (H323CALLBACK* H323CBConfTerLeft)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERLABEL tTerLabel ); //�ص��뿪������ն�
// typedef BOOL (H323CALLBACK* H323CBConfTerIDListRequest)( HMDLCALL hCall, HMDLAPPCALL hAppCall );   //�ص��ն�ID�б�����
// typedef BOOL (H323CALLBACK* H323CBConfTerLabelListRequest)( HMDLCALL hCall, HMDLAPPCALL hAppCall );  //�ص��ն�List�б�����



//�»�ؽӿ�ǰ��Ĳ���
typedef BOOL32 (H323CALLBACK* H323CBTerFloorReqToMc)( HMDLAPPCONFID hAppConfId, TMDLTERLABEL tTerLabel );
typedef BOOL32 (H323CALLBACK* H323CBTerChairReqToMc)( HMDLAPPCONFID hAppConfId, TMDLTERLABEL tTerLabel );
typedef BOOL32 (H323CALLBACK* H323CBTer239TokenReqToMc)( HMDLAPPCONFID hAppConfId, TMDLTERLABEL tTerLabel );
typedef BOOL32 (H323CALLBACK* H323CB239TokenOwnerToMc)( HMDLAPPCONFID hAppConfId, TMDLTERLABEL tTerLabel );


//chiar����Ļص�
typedef BOOL32 (H323CALLBACK* H323CBChairSendThisSource)( HMDLAPPCONFID hAppConfId, TMDLTERLABEL Viewer, TMDLTERLABEL Viewed );
typedef BOOL32 (H323CALLBACK* H323CBChairBroadcastTerminal)( HMDLAPPCONFID hAppConfId, TMDLTERLABEL tTerLabel );
typedef BOOL32 (H323CALLBACK* H323CBChairCancelBroadcastTerminal)( HMDLAPPCONFID hAppConfId, TMDLTERLABEL tTerLabel );
typedef BOOL32 (H323CALLBACK* H323CBSendThisSourceRsp)( HMDLCALL hCall, HMDLAPPCALL hAppCall, BOOL32 bIsSuccess );

//ter��ص�
typedef BOOL32 (H323CALLBACK* H323CBMultipleConf)( HMDLCALL hCall, HMDLAPPCALL hAppCall );
typedef BOOL32 (H323CALLBACK* H323CBSelfTerLabel)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERLABEL tTerLabel );
typedef BOOL32 (H323CALLBACK* H323CBChairTokenOwner)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERMINALINFO tTerInfo );
typedef BOOL32 (H323CALLBACK* H323CBTerList )( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERINFOLIST tTerList );
typedef BOOL32 (H323CALLBACK* H323CBYouAreSeeing)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERMINALINFO tTerInfo );
typedef BOOL32 (H323CALLBACK* H323CBSeeByAll)( HMDLCALL hCall, HMDLAPPCALL hAppCall );


typedef BOOL32 (H323CALLBACK* H323CBTerFloorReqToChair)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERMINALINFO tTerInfo );

typedef struct tagH323ConfCallBack
{
//ter��ص�
	H323CBMultipleConf m_cbMultipleConf;
	H323CBSelfTerLabel m_cbSelfTerLabel;
	H323CBChairTokenOwner m_cbChairTokenOwner;
	H323CBTerList m_cbTerList;
	H323CBYouAreSeeing m_cbYouAreSeeing;
	H323CBSeeByAll m_cbSeeByAll;
	//chair�ص�
	H323CBTerFloorReqToChair m_cbTerFloorReqToChair;
	H323CBSendThisSourceRsp m_cbSendThisSouceRsp;
	
	//mc��ص�
	H323CBTerFloorReqToMc m_cbTerFloorReqToMc;
	H323CBTerChairReqToMc m_cbTerChairReqToMc;
	H323CBChairSendThisSource m_cbChairSendThisSource;
	H323CBChairBroadcastTerminal m_cbChairBroadcastTerminal;
	H323CBChairCancelBroadcastTerminal m_cbChairCancelBroadcastTerminal;
	H323CBTer239TokenReqToMc m_cbTer239TokenReqToMc;
	H323CB239TokenOwnerToMc m_cb239TokenOwnerToMc;
	
	tagH323ConfCallBack()
	{
		memset( this , 0 , sizeof(tagH323ConfCallBack) );
	}
}TH323ConfCallBack;


typedef struct tagH323Cfg
{
	s32 m_nh323ServiceAppId;
	s32 m_nh323StackinAppid;
	s32 m_nh323StackoutAppid;

	u32 m_dwh323StackIp;
	u8  m_abyh323StackIp_ipv6[16];

	u16 m_wh225port;
	u16 m_dwh323StackPortStart;
	u16 m_dwh323StackPortEnd;

	u16 m_wTotalCallNum;
	u16 m_wTotalRegNum;

	emModuleEndpointType m_emEndpointType;

	TH323CallCBFunction m_tCallCBFuntion;
	TH323ChannelCBFunction m_tChannelCBFuntion;
	TH323ConfCallBack m_cbConfCallBack;
	CBRegResult     m_cbRegResult;
	H323CBConfEvent m_cbConfEvent;
	CBOnlineList    m_cbOnlineList;

	tagH323Cfg()
	{
		m_nh323ServiceAppId = -1;
		m_nh323StackinAppid = -1;
		m_nh323StackoutAppid = -1;

		m_wh225port = 1720;
		m_dwh323StackIp = 0;

		memset(m_abyh323StackIp_ipv6 , 0 , sizeof(m_abyh323StackIp_ipv6) );

		m_wTotalCallNum = 10;
		m_wTotalRegNum = 10;
		m_dwh323StackPortStart = 60000;
		m_dwh323StackPortEnd = 60000+4*10;

		m_emEndpointType = emModuleEndpointMT;

		m_cbRegResult = NULL;
		m_cbConfEvent = NULL;
		m_cbOnlineList = NULL;
	}

}TH323Cfg;

class H323Module
{
	//Call API:
public:
	
	//H323 module init function
	static BOOL H323ModuleInit( TH323Cfg &tCfg );
	//H323 module start recv
	static BOOL H323ModuleStart();
	//H323 module stop recv
	static BOOL H323ModuleStop();
	//H323 module exit function
	static BOOL H323ModuleExit();
	//H323 module create a new outgoing call
	static BOOL H323ModuleMakeOutgoingCall( HMDLAPPCALL hAppCall, TModuleCallInfo* ptModuleCallInfo, TCallCapbility* ptSendCapbility, TCallCapbility* ptRecvCapbility, HMDLAPPCONFID hAppConfId = 0, TMDLTERLABEL* pTerLabel = NULL, TFeccCapbility* ptFeccCap = NULL );
	
	static BOOL H323ModuleCallAnswer( HMDLCALL hCall, HMDLAPPCALL hAppCall, TModuleCallInfo* ptModuleCallInfo, TCallCapbility* ptSendCapbility, TCallCapbility* ptRecvCapbility, HMDLAPPCONFID hAppConfId = 0, TMDLTERLABEL* pTerLabel = NULL, TFeccCapbility* ptFeccCap = NULL );
	
	static BOOL H323ModuleCallReject( HMDLCALL hCall, HMDLAPPCALL hAppCall, EmModuleCallDisconnectReason emReason );
	
	static BOOL H323ModuleCallHangup( HMDLCALL hCall, HMDLAPPCALL hAppCall, EmModuleCallDisconnectReason emReason );

	//added by sna for interworking [20140214]
	static BOOL H323LocalSendCapSet( HMDLCALL hCall, HMDLAPPCALL hAppCall , TCallCapbility* ptSendCapbility);
	static BOOL H323IWReopenChannel( HMDLCALL hCall , HMDLAPPCALL hAppCall , HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan  , TChanConnectedInfo * ptReopenChanInfo);
	//Channel API:
public:
	static BOOL CloseChannel( HMDLCALL hCall, HMDLAPPCALL hAppCall, HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan );
	static BOOL FlowCtrl( HMDLCALL hCall , HMDLAPPCALL hAppCall , HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan , u16 wBitrate );
    static BOOL FastUpdate( HMDLCALL hCall , HMDLAPPCALL hAppCall , HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan  );
	static BOOL DualSteam( HMDLCALL hCall , HMDLAPPCALL hAppCall , HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan, TCallCapbility* ptDualCap );
	
	/*=============================================================================
	�� �� ����DualStreamAnswer
	��	  �ܣ�answer dual or stop dual(only interworking used)
	��	  ����TChanConnectedInfo* ptDualInfo : [in] the capbility of answer dual
			  BOOL bIsSuc: TRUE is answer,FALSE is stop and ptDualInfo is null
	�� �� ֵ��send message succeed return TRUE,otherwise return FALSE
	=============================================================================*/
	static BOOL DualStreamAnswer( HMDLCALL hCall, HMDLAPPCALL hAppCall, HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan, BOOL bIsSuc, TChanConnectedInfo* ptDualInfo );
	static BOOL DualStreamStop( HMDLCALL hCall, HMDLAPPCALL hAppCall, HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan );

    //added by jacky for manual channel on/off
    static BOOL ChannelSwitch( HMDLCALL hCall, HMDLAPPCALL hAppCall, HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan, BOOL32 bActive);
    //end of added by jacky for manual channel on/off 
    
	//added by sna for dual channel on/off[20130107]
	static BOOL H323ModuleChanEvent( HMDLCALL hCall, HMDLAPPCALL hAppCall, HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan, u16 wEvent, u8* pBuf, u16 wLen);
	//end of added by sna[20130107]

	// REG API
public:
	static BOOL Regist( HMDLREG hReg , HMDLAPPREG hAppReg , TRegistReq* ptRegInfo );
	static BOOL UnRegist( HMDLREG hReg , HMDLAPPREG hAppReg );
	static BOOL RegistUpdate( HMDLREG hReg, HMDLAPPREG hAppReg, TRegistReq* ptRegInfo );

public:
	// CONFERENCE
	static BOOL H323ModuleConfEvent( HMDLCALL hCall, HMDLAPPCALL hAppCall, u16 wEvent, u8* pBuf, u16 wLen );

	// �½ӿ�  ����Ĳ���
	// mc��
	static BOOL H323MCStopConference( HMDLAPPCONFID hAppConfId );
	static BOOL H323MCMakeSpeaker( HMDLAPPCONFID hAppConfId, TMDLTERLABEL tTerLabel );
	static BOOL H323MCWithdrawSpeaker( HMDLAPPCONFID hAppConfId, TMDLTERLABEL tTerLabel );
	static BOOL H323MCMakeChair( HMDLAPPCONFID hAppConfId, TMDLTERLABEL tTerLabel );
	static BOOL H323MCWithdrawChair( HMDLAPPCONFID hAppConfId, TMDLTERLABEL tTerLabel );
	static BOOL H323MCSendThisSource( HMDLAPPCONFID hAppConfId, TMDLTERLABEL Viewer, TMDLTERLABEL Viewed );
	static BOOL H323MCCancelSendThisSource( HMDLAPPCONFID hAppConfId, TMDLTERLABEL Viewer, TMDLTERLABEL Viewed );
	static BOOL H323MCAddTer( HMDLAPPCONFID hAppConfId, TMDLTERMINALINFO* ptTerInfoList, u8 byNum );
	static BOOL H323MCDelTer( HMDLAPPCONFID hAppConfId, TMDLTERMINALINFO* ptTerInfoList, u8 byNum );

	// chair��
	static BOOL H323ChairCancelMakeMeChair( HMDLCALL hCall, HMDLAPPCALL hAppCall );
	static BOOL H323ChairSendThisSourceCmd( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERLABEL tTerlabel );
	static BOOL H323ChairCancelSendThisSource( HMDLCALL hCall, HMDLAPPCALL hAppCall );
	static BOOL H323ChairBroadcastTerminalReq( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERLABEL tTerLabel );
	static BOOL H323ChairBroadcastTerminalCmd( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERLABEL tTerLabel );
	static BOOL H323ChairCancelBroadcastTerminal( HMDLCALL hCall, HMDLAPPCALL hAppCall );

	// ter��
	static BOOL H323TerMakeMeSpeaker( HMDLCALL hCall, HMDLAPPCALL hAppCall );
	static BOOL H323TerMakeMeChair( HMDLCALL hCall, HMDLAPPCALL hAppCall );
	
public:
	static BOOL H323SendFeccMsg( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMdlFeccStruct tFeccAction, TMDLTERLABEL tDstLabel );
	
public:
	static BOOL H323OnlineListReq( EmModuleGetGKInfoType emType, HMDLREG hReg, HMDLAPPREG hAppReg, u32 dwAppId );

private:
	//added by sna for print capbility form upper level [20140219]
	//bIsOnlyDual������DualStream��ʱ��ֻ��ӡ˫������������
	static void H323PrintCapbility( TCallCapbility* ptSendCapbility, TCallCapbility* ptRecvCapbility, BOOL bIsOnlyDual=FALSE );
	//added end

public:
	static u16 m_wh323serviceAppId;
	static TH323ChannelCBFunction m_tCHannelCBFuntion;
	static TH323CallCBFunction m_tCallCBFunction;
//	static TH323ConfCBFunction m_tConfCBFunction;
	static TH323ConfCallBack m_tConfCallBack;
	static CBRegResult     m_CbRegResult;
	static H323CBConfEvent m_CbConfEvent;
	static H323CBFeccMsg   m_CbFeccMsg;
	static CBOnlineList    m_CbOnlineList;
};

//��ӡ
static u8 g_byMDLLogLevel = 0;
static s8 g_achCallerAlias[MAX_ALIAS_LEN]  = "all";
static u8 g_byModuleType = (int)emModuleAll;
static u16 g_wCallNum = 0;
static emCallBy g_emCallBy = emModuleCallByNum;

#define IS_LOG(n)  (n <= g_byMDLLogLevel)
#define MODULE_PRINT_BUFFERSIZE  1024

API void h323setlog( u8 byLevel );
API void h323setcallbyname( s8* pchCallerAlias );
API void h323setcallbynum( u8 wCallNum );
API void h323setlogtype( u8 byModuel );
API void h323setcallby( u8 byCallBy );
API void h323help();
API void h323showreg();
API void h323showcall( u8 i );
API void h323showconf();
API void h323ver();

void ModulePrintf( emModuleType ModuleType, u16 byLogLevel, s8* pchCallerAlias, u16 byCallNum, const char* pFormat, ... );

#endif

