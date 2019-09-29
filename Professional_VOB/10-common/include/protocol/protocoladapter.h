#ifndef _PROTOCALADAPTER_H
#define _PROTOCALADAPTER_H


#include "osp.h"
#include "modulecallstruct.h"
#include "tpmodulestruct.h"


#ifdef WIN32
#define PACALLBACK __cdecl
#else
#define PACALLBACK
#endif


#define PA_INVALID_INDEX         -1
#define MAX_PROTOCOL_NUMBER       5
#define PA_IPV6_ADDR_SIZE         16

#define DEFAULT_CALL_NUMBER       128
#define DEFAULT_H225_PORT         1720
#define DEFAULT_H323_PORT_FROM    60000
#define DEFAULT_H323_PORT_TO      60040

#define DEFAULT_SIP_CALLING_PORT  5060
#define DEFAULT_SIP_ALIVE_TIME    30

#define MAX_SENDRECV_BUF_SIZE     20480       //默认套接字发送接收缓冲大小

extern u16 g_aProtocolList[MAX_PROTOCOL_NUMBER+1];


//协议类型
enum EmPAConfProtocol
{
	emPATypeInvalid = 0,
	emPATypeH323  = 1, 
	emPATypeSip   = 2, 
	emPATypeAll   = 3,
};




typedef BOOL (PACALLBACK* PACBNewCallIncoming)(
	EmPAConfProtocol emPAType,
    HMDLCALL         hPACall, 
	TModuleCallInfo *ptCallInfo, 
	TCallCapbility  *ptSndCap, 
	TCallCapbility  *ptRcvCap,
	TCallInfoTP     *ptCallTP, 
	TCallDescriptTP *ptSndTP,
	TCallDescriptTP *ptRcvTP);

typedef BOOL (PACALLBACK* PACBCallConnected)( 
	HMDLCALL    hPACall, 
	HMDLAPPCALL hAppCall,
	TModuleCallInfo *ptCallInfo, 
	TCallInfoTP     *ptCallTP,
	EmPAConfProtocol emPAType );

typedef BOOL (PACALLBACK* PACBCallDisconnected)( 
	HMDLCALL    hPACall,
	HMDLAPPCALL hAppCall,
	EmModuleCallDisconnectReason emReason );

typedef struct tagPACallCBFunction
{
	PACBNewCallIncoming    m_fpNewCallIncoming;
	PACBCallConnected      m_fpCallConnected;
	PACBCallDisconnected   m_fpCallDisconnected;

	tagPACallCBFunction()
	{
		memset( this, 0, sizeof(tagPACallCBFunction) );
	}
}TPACallCBFunction;



typedef BOOL (PACALLBACK* PACBChannelConnected)(
	HMDLCALL hPACall, 
	HMDLAPPCALL hAppCall, 
	TChanConnectedInfo* ptChanConnectInfo,
	s32 nSize, 
	TChanDescriptTP *ptDesTP);

typedef BOOL (PACALLBACK* PACBChannelDisconnected)(
	HMDLCALL hPACall, 
	HMDLAPPCALL hAppCall, 
	TChanDisConnectedInfo *ptDisConInfo, 
	s32 nSize);

typedef BOOL (PACALLBACK* PACBChannelFlowCtrl)( 
	HMDLCALL       hPACall, 
	HMDLAPPCALL    hAppCall,
	HMDLCHANNEL    hPAChan,
	HMDLAPPCHANNEL hAppChan, 
	u16 wBitrate );

typedef BOOL (PACALLBACK* PACBChannelFastUpdate)( 
	HMDLCALL       hPACall, 
	HMDLAPPCALL    hAppCall,
	HMDLCHANNEL    hPAChan,
	HMDLAPPCHANNEL hAppChan );

typedef BOOL (PACALLBACK* PACBDualStreamIncoming)( 
	HMDLCALL       hPACall, 
	HMDLAPPCALL    hAppCall,
	TDualCapList   *ptDual );

typedef BOOL (PACALLBACK* PACBFeccChanConnected)(
    HMDLCALL hCall, 
    HMDLAPPCALL hAppCall, 
    TFeccCapbility *ptFeccCap);

// typedef BOOL (PACALLBACK* PACBDualStreamConnected)( 
// 	HMDLCALL       hPACall, 
// 	HMDLAPPCALL    hAppCall,
// 	HMDLCHANNEL    hPAChan,
// 	HMDLAPPCHANNEL hAppChan, 
// 	TChanConnectedInfo *ptChanInfo );
// 
// typedef BOOL (PACALLBACK* PACBDualStreamReject)( 
// 	HMDLCALL       hPACall, 
// 	HMDLAPPCALL    hAppCall,
// 	HMDLCHANNEL    hPAChan,
// 	HMDLAPPCHANNEL hAppChan );
// 
// typedef BOOL (PACALLBACK* PACBDualStreamStop)( 
// 	HMDLCALL       hPACall, 
// 	HMDLAPPCALL    hAppCall,
// 	HMDLCHANNEL    hPAChan,
// 	HMDLAPPCHANNEL hAppChan );

typedef BOOL (PA_CALLBACK* PACBChanCtrlTP)(
	HMDLCALL hPACall ,
	HMDLAPPCALL hAppCall, 
	HMDLCHANNEL hChan, 
	s32 nMsgType, 
	u8 *pBuf, 
	s32 nSize );

typedef BOOL (PA_CALLBACK* PACBConfCtrlTP)(
	 HMDLCALL hPACall ,
	 HMDLAPPCALL hAppCall,  
	 s32 nMsgType, 
	 u8 *pBuf, 
	 s32 nSize,
	 EmPAConfProtocol emPAType );

typedef BOOL (PA_CALLBACK* PACBConfCtrl)(
     HMDLCALL hPACall ,
     HMDLAPPCALL hAppCall,  
     s32 nMsgType, 
     u8 *pBuf, 
	 s32 nSize,
	 EmPAConfProtocol emPAType );

typedef struct tagPAChannelCBFunction
{
	PACBChannelConnected     m_fpChannelConnected;
	PACBChannelDisconnected  m_fpChannelDisconnected;

	PACBChannelFlowCtrl      m_fpChannelFlowCtrl;
	PACBChannelFastUpdate    m_fpChannelFastUpdate;
	PACBDualStreamIncoming   m_fpDualStreamIncoming;
    PACBFeccChanConnected    m_fpFeccChanConnected;
	PACBChanCtrlTP           m_fpChanCtrlTP;
	PACBConfCtrlTP           m_fpConfCtrlTP;
	PACBConfCtrl             m_fpConfCtrl;

// 	PACBDualStreamConnected  m_fpDualStreamConnected;
// 	PACBDualStreamReject     m_fpDualStreamReject;
// 	PACBDualStreamStop       m_fpDualStreamStop;
	
	tagPAChannelCBFunction()
	{
		memset( this , 0 , sizeof(tagPAChannelCBFunction) );
	}
}TPAChannelCBFunction;


/*====================================================================
函 数 名： PACBRegResult
功    能： 注册结果的回调函数
算法实现： 
全局变量： 
参    数： EmPAConfProtocol emPAType : 协议类型
           HMDLREG          hReg     : 协议栈句柄
           HMDLAPPREG       hAppReg  : 应用层句柄
           BOOL32     bRegistered : 是否注册成功
           u8* pAppendData    : 如果注册成功，则pBuf = NULL; 否则指向 EmPARegFailedReason
           u16 wAppendDataLen : 如果注册成功，则wLen = 0;    否则为 EmPARegFailedReason 的长度
备注：     针对网真项目，当注册失败，并且失败原因为emPARegisterNameDup时，
           pAppendData指向的内存结构为：EmPARegFailedReason + nSize + nSize*TPARegName
======================================================================*/
typedef BOOL (PACALLBACK* PACBRegResult)( 
	EmPAConfProtocol emPAType,										 
	HMDLREG          hReg, 
	HMDLAPPREG       hAppReg,
	BOOL32           bRegistered,
	u8              *pAppendData,
	u16              wAppendDataLen );

/*====================================================================
函 数 名： PACBUnRegResult
功    能： 取消注册结果的回调函数
算法实现： 
全局变量： 
参    数： EmPAConfProtocol emPAType : 协议类型
           HMDLREG          hReg     : 协议栈句柄
           HMDLAPPREG       hAppReg  : 应用层句柄
           u8* pBuf : 指向 EmPARegFailedReason
           u16 wLen : EmPARegFailedReason 的长度
备注: 取消注册的结果不再回调, 有协议栈来确保取消注册成功.
======================================================================*/
// typedef BOOL (PACALLBACK* PACBUnRegResult)( 
// 	EmPAConfProtocol emPAType,
// 	HMDLREG    hReg, 
// 	HMDLAPPREG hAppReg,
// 	s8 *pBuf, 
// 	s32 nLen );


/*====================================================================
函 数 名： PACBUnRegResult
功    能： 获取全域内CNS的全部注册信息的回调函数
算法实现： 
全局变量： 
参    数： s32  nAppId : 应用层句柄
           u8  *pBuf   : 依次为TPARegPackInfo, EmPAGetRegInfoType, TPARegInfo
           u16  wLen   : 内容长度
备注    :  
======================================================================*/
typedef BOOL (PACALLBACK* PACBGetRegInfoAckTP)(
	const EmPAConfProtocol protocolType,
    const s32 nAppId, 
	const u8 *pBuf, 
	const s32 nLen,
	const u8  byVersion);


typedef struct tagPARegistCBFunction
{
	PACBRegResult        m_cbRegistResult;
 //	PACBUnRegResult      m_cbUnRegistResult;
	PACBGetRegInfoAckTP  m_cbGetRegInfoAckTP;
	tagPARegistCBFunction()
	{
		memset( this , 0 , sizeof(tagPARegistCBFunction) );
	}

}TPARegistCBFunction;



//#define USE_NEW_CONF

#ifdef USE_NEW_CONF
/*====================================================================
函 数 名： PACBMultipleConf
功    能： [会控回调接口] 终端侧回调，多点会议开启
算法实现： 
全局变量： 
参    数： HMDLCALL          hPACall      : 协议栈呼叫句柄
           HMDLAPPCALL       HMDLAPPCALL  : 应用层呼叫句柄
备注: 
======================================================================*/
typedef BOOL32 (PACALLBACK* PACBMultipleConf)( HMDLCALL hPACall, HMDLAPPCALL hAppCall );

/*====================================================================
函 数 名： PACBSelfTerLabel
功    能： [会控回调接口] 终端侧回调，终端LABEL信息
算法实现： 
全局变量： 
参    数： HMDLCALL          hPACall      : 协议栈呼叫句柄
           HMDLAPPCALL       HMDLAPPCALL  : 应用层呼叫句柄
		   TMDLTERLABEL      tTerLabel    : 终端LABEL
备注: 
======================================================================*/
typedef BOOL32 (PACALLBACK* PACBSelfTerLabel)( HMDLCALL hPACall, 
											  HMDLAPPCALL hAppCall, 
											  TMDLTERLABEL tTerLabel );

/*====================================================================
函 数 名： PACBChairTokenOwner
功    能： [会控回调接口] 终端侧回调，主席终端信息
算法实现： 
全局变量： 
参    数： HMDLCALL          hPACall      : 协议栈呼叫句柄
           HMDLAPPCALL       HMDLAPPCALL  : 应用层呼叫句柄
		   TMDLTERMINALINFO  tTerInfo     : 主席终端信息
备注: 
======================================================================*/
typedef BOOL32 (PACALLBACK* PACBChairTokenOwner)( HMDLCALL hPACall, 
												 HMDLAPPCALL hAppCall, 
												 TMDLTERMINALINFO tTerInfo );

/*====================================================================
函 数 名： PACBTerList
功    能： [会控回调接口] 终端侧回调，与会终端信息
算法实现： 
全局变量： 
参    数： HMDLCALL          hPACall       : 协议栈呼叫句柄
           HMDLAPPCALL       HMDLAPPCALL   : 应用层呼叫句柄
		   TMDLTERINFOLIST   tTerList      : 与会终端列表信息
		   BOOL32            bHaveTPParam  : 是否携带网真参数
		   TConfCnsList     *ptConfCnsList : 网真参数
备注: 
======================================================================*/
typedef BOOL32 (PACALLBACK* PACBTerList )( HMDLCALL hPACall, 
										  HMDLAPPCALL hAppCall, 
										  TMDLTERINFOLIST tTerList,
										  BOOL32       bHaveTPParam,
										  TConfCnsList *ptConfCnsList );

/*====================================================================
函 数 名： PACBYouAreSeeing
功    能： [会控回调接口] 终端侧回调，终端当前的选看对象
算法实现： 
全局变量： 
参    数： HMDLCALL          hPACall        : 协议栈呼叫句柄
           HMDLAPPCALL       HMDLAPPCALL    : 应用层呼叫句柄
		   TMDLTERMINALINFO  tTerInfo       : 被看终端的信息
		   BOOL32            bHaveTPParam   : 是否携带网真参数
		   TYouAreSeeing    *ptYouAreSeeing : 网真参数
备注: 
======================================================================*/
typedef BOOL32 (PACALLBACK* PACBYouAreSeeing)( HMDLCALL hPACall, 
											  HMDLAPPCALL hAppCall, 
											  TMDLTERMINALINFO tTerInfo, 
											  BOOL32 bHaveTPParam, 
											  TYouAreSeeing *ptYouAreSeeing);

/*====================================================================
函 数 名： PACBSeeByAll
功    能： [会控回调接口] 终端侧回调，广播源指示
算法实现： 
全局变量： 
参    数： HMDLCALL          hPACall        : 协议栈呼叫句柄
           HMDLAPPCALL       HMDLAPPCALL    : 应用层呼叫句柄
备注: 
======================================================================*/
typedef BOOL32 (PACALLBACK* PACBSeeByAll)( HMDLCALL hPACall, HMDLAPPCALL hAppCall );


/*====================================================================
函 数 名： PACBTerFloorReqToChair
功    能： [会控回调接口] 终端侧回调(主席)，终端请求发言
算法实现： 
全局变量： 
参    数： HMDLCALL          hPACall        : 协议栈呼叫句柄
           HMDLAPPCALL       HMDLAPPCALL    : 应用层呼叫句柄
		   TMDLTERLABEL      tTerLabel    : 终端LABEL
备注: 
======================================================================*/
typedef BOOL32 (PACALLBACK* PACBTerFloorReqToChair)( HMDLCALL hPACall, 
													HMDLAPPCALL hAppCall, 
													TMDLTERMINALINFO tTerInfo );

/*====================================================================
函 数 名： PACBTerFloorReqToChair
功    能： [会控回调接口] 终端侧回调(主席)，主席选看回复
算法实现： 
全局变量： 
参    数： HMDLCALL          hPACall        : 协议栈呼叫句柄
           HMDLAPPCALL       HMDLAPPCALL    : 应用层呼叫句柄
		   TMDLTERLABEL      tTerLabel    : 终端LABEL
备注: 
======================================================================*/
typedef BOOL32 (PACALLBACK* PACBSendThisSourceRsp)( HMDLCALL hCall,
                                                   HMDLAPPCALL hAppCall,
                                                   BOOL32 bIsSuccess );


/*====================================================================
函 数 名： PACBChairSendThisSource
功    能： [会控回调接口] MC侧回调，收到主席选看指示
算法实现： 
全局变量： 
参    数： HMDLAPPCONFID   hAppConfId   : 应用层会议句柄 
           HMDLCALL        hViewer      : 协议栈呼叫句柄(选看方)
           HMDLAPPCALL     hAppViewer   : 应用层呼叫句柄(选看方)
           HMDLCALL        hViewed      : 协议栈呼叫句柄(被选看方)
           HMDLAPPCALL     hAppViewed   : 应用层呼叫句柄(被选看方)
备注: 
======================================================================*/
typedef BOOL32 (PACALLBACK* PACBChairSendThisSource)( HMDLAPPCONFID hAppConfId, 
													 HMDLCALL hViewer, 
													 HMDLAPPCALL hAppViewer, 
													 HMDLCALL hViewed, 
													 HMDLAPPCALL hAppViewed );
// TODO:
/*====================================================================
函 数 名： PACBChairCancelSendThisSource
功    能： [会控回调接口] MC侧回调，收到主席取消选看指示
算法实现： 
全局变量： 
参    数： HMDLAPPCONFID   hAppConfId   : 应用层会议句柄 
           HMDLCALL        hViewer      : 协议栈呼叫句柄(选看方)
           HMDLAPPCALL     hAppViewer   : 应用层呼叫句柄(选看方)
           HMDLCALL        hViewed      : 协议栈呼叫句柄(被选看方)
           HMDLAPPCALL     hAppViewed   : 应用层呼叫句柄(被选看方)
备注: 
======================================================================*/

/*====================================================================
函 数 名： PACBChairBroadcastTerminal
功    能： [会控回调接口] MC侧回调，收到主席指示发言终端
算法实现： 
全局变量： 
参    数： HMDLAPPCONFID   hAppConfId   : 应用层会议句柄 
           HMDLCALL        hPACall      : 协议栈呼叫句柄
           HMDLAPPCALL     hAppCall     : 应用层呼叫句柄
备注: 
======================================================================*/
typedef BOOL32 (PACALLBACK* PACBChairBroadcastTerminal)( HMDLAPPCONFID hAppConfId,
														HMDLCALL hPACall, 
														HMDLAPPCALL hAppCall);

/*====================================================================
函 数 名： PACBChairCancelBroadcastTerminal
功    能： [会控回调接口] MC侧回调，收到主席取消发言终端
算法实现： 
全局变量： 
参    数： HMDLAPPCONFID   hAppConfId   : 应用层会议句柄 
           HMDLCALL        hPACall      : 协议栈呼叫句柄
           HMDLAPPCALL     hAppCall     : 应用层呼叫句柄
备注: 
======================================================================*/
typedef BOOL32 (PACALLBACK* PACBChairCancelBroadcastTerminal)( HMDLAPPCONFID hAppConfId,
															  HMDLCALL hPACall, 
															  HMDLAPPCALL hAppCall );

/*====================================================================
函 数 名： PACBTerFloorReqToMc
功    能： [会控回调接口] MC侧回调，收到终端申请发言
算法实现： 
全局变量： 
参    数： HMDLAPPCONFID   hAppConfId   : 应用层会议句柄 
           HMDLCALL        hPACall      : 协议栈呼叫句柄
           HMDLAPPCALL     hAppCall     : 应用层呼叫句柄
备注: 
======================================================================*/
typedef BOOL32 (PACALLBACK* PACBTerFloorReqToMc)( HMDLAPPCONFID hAppConfId, 
												 HMDLCALL hPACall, 
												 HMDLAPPCALL hAppCall );
/*====================================================================
函 数 名： PACBTerChairReqToMc
功    能： [会控回调接口] MC侧回调，收到终端申请主席
算法实现： 
全局变量： 
参    数： HMDLAPPCONFID   hAppConfId   : 应用层会议句柄 
           HMDLCALL        hPACall      : 协议栈呼叫句柄
           HMDLAPPCALL     hAppCall     : 应用层呼叫句柄
备注: 
======================================================================*/
typedef BOOL32 (PACALLBACK* PACBTerChairReqToMc)( HMDLAPPCONFID hAppConfId, 
												 HMDLCALL hPACall, 
												 HMDLAPPCALL hAppCall );


typedef struct tagPAConfCallBack
{
	// MC侧回调，收到chair的请求
	PACBChairSendThisSource          m_fpChairSendThisSource;
	PACBChairBroadcastTerminal       m_fpChairBroadcastTerminal;
	PACBChairCancelBroadcastTerminal m_fpChairCancelBroadcastTerminal;
	
	// MC侧回调，收到Terminal的请求
	PACBTerFloorReqToMc m_fpTerFloorReqToMc;
	PACBTerChairReqToMc m_fpTerChairReqToMc;

	//terminal侧回调
	PACBMultipleConf    m_fpMultipleConf;
	PACBSelfTerLabel    m_fpSelfTerLabel;
	PACBChairTokenOwner m_fpChairTokenOwner;
	PACBTerList         m_fpTerList;
	PACBYouAreSeeing    m_fpYouAreSeeing;
	PACBSeeByAll        m_fpSeeByAll;
	
	//terminal侧回调(chair)
	PACBTerFloorReqToChair m_fpTerFloorReqToChair;
    PACBSendThisSourceRsp  m_fpSendThisSouceRsp;

    tagPAConfCallBack()
    {
        memset( this , 0 , sizeof(tagPAConfCallBack) );
	}
	
}TPAConfCBFunction;

#endif


typedef struct tagPACallBackFunc
{
	TPACallCBFunction      m_tPACallCBFunction;
	TPAChannelCBFunction   m_tPAChannelCBFunction;
	TPARegistCBFunction    m_tPARegistCBFunction;

#ifdef USE_NEW_CONF
	TPAConfCBFunction      m_tPAConfCBFunction;
#endif

	
	tagPACallBackFunc()
	{
		memset( this, 0, sizeof(tagPACallBackFunc) );
	}
	
}TPACallBackFunc, *PTPACallBackFunc;


typedef struct tagPAH323Cfg
{
	u32 m_dwh323StackIp;
	u8  m_abyh323StackIp_ipv6[PA_IPV6_ADDR_SIZE];
	
	u16 m_wh225port;
	u16 m_dwh323StackPortStart;
	u16 m_dwh323StackPortEnd;
	
	u16 m_wH323TotalCallNum;
	
	emModuleEndpointType m_emEndpointType;

	tagPAH323Cfg()
	{		
		m_wh225port = DEFAULT_H225_PORT;
		m_dwh323StackIp = 0;
		
		memset(m_abyh323StackIp_ipv6 , 0 , sizeof(m_abyh323StackIp_ipv6) );
		
		m_wH323TotalCallNum = DEFAULT_CALL_NUMBER;
		m_dwh323StackPortStart = DEFAULT_H323_PORT_FROM;
		m_dwh323StackPortEnd   = DEFAULT_H323_PORT_TO;

		m_emEndpointType = emModuleEndpointMT;
	}
	
}TPAH323Cfg;


typedef struct tagPASipCfg
{
	u16  m_wCallingPort;            //呼叫端口
	u16  m_wSipTotalCallNum;
	u16  m_wIfProxy;                //若为注册服务器则大于0 否则填0
	u32  m_dwKeepAliveTime;         //单位: 秒
	u16  m_wRegClientNum;           //支持CNS最大注册的数量
	u32  m_dwMaxSendRecvBufferSize; //套接字发送接收缓冲大小(暂时使用默认值)
	BOOL32  m_bSendRecv;            //标示sip主流属性(sendrecv还是sendonly和recvonly)

	s32					  m_nProductIdSize;
	u8					  m_abyProductId[MAX_LEN_PRODUCT_ID];				//产品号
	s32					  m_nVerIdSize;
	u8					  m_abyVersionId[MAX_LEN_VERSION_ID];				//版本号
	
	tagPASipCfg()
	{		
		m_wCallingPort = DEFAULT_SIP_CALLING_PORT;
		m_wSipTotalCallNum = DEFAULT_CALL_NUMBER;
		m_wIfProxy = FALSE;
		m_dwKeepAliveTime = DEFAULT_SIP_ALIVE_TIME;
		m_nProductIdSize = 0;
		m_nVerIdSize = 0;
		m_wRegClientNum = MAX_INSTANCE_PROTOCAL;
		m_dwMaxSendRecvBufferSize = MAX_SENDRECV_BUF_SIZE;
		m_bSendRecv = FALSE;
		memset( m_abyProductId, 0, MAX_LEN_PRODUCT_ID );
		memset( m_abyVersionId, 0, MAX_LEN_VERSION_ID );
	}
	
}TPASipCfg;


typedef struct tagPAConfig
{
	TPAH323Cfg m_tH323Config;
	TPASipCfg  m_tSipConfig;

	tagPAConfig(){ }

	void SetH323Config( TPAH323Cfg & tH323Config )
	{
		memcpy( &m_tH323Config , &tH323Config, sizeof(TPAH323Cfg));
	}

	TPAH323Cfg & GetH323Config()
	{
		return m_tH323Config;
	}

	void SetSipConfig( TPASipCfg & tSipConfig )
	{
		memcpy( &m_tSipConfig , &tSipConfig, sizeof(TPASipCfg));
	}
	
	TPASipCfg & GetSipConfig()
	{
		return m_tSipConfig;
	}

}TPAConfig,*PTPAConfig;



/*-------------------------------------------------
 *     Main API
 *-----------------------------------------------*/
BOOL PA_Init( TPAConfig &tPAConfig );

void PA_Quit();

BOOL PA_SetCallBackFunc( TPACallBackFunc &tPACallBackFunc );


/*-------------------------------------------------
 *     Call API
 *-----------------------------------------------*/


/*如果makeCall时tdual传下来， 就认为双流能力是tdual, 但是呼叫时双流能力不带过去
上层调用sendual才发双流过去， 就不回调dualincoming, 只回调channelconnected,和disconnected*/

BOOL PA_MakeCall( 
    EmPAConfProtocol emPAType,
	HMDLCALL        *phCall,
	HMDLAPPCALL      hAppCall,
	TModuleCallInfo *ptCallInfo = NULL ,
	TCallCapbility  *ptSndCap = NULL, 
	TCallCapbility  *ptRcvCap = NULL,
	TCallInfoTP     *ptCallInfoTP = NULL,
	TCallDescriptTP *ptSndTP = NULL, 
	TCallDescriptTP *ptRcvTP = NULL,
	TDualCapList    *ptDualCapList = NULL,
    HMDLAPPCONFID    hAppConfId = 0, 
    TMDLTERLABEL    *ptTerLabel = NULL,
    TBfcpCapSet     *ptBfcp = NULL,
    TFeccCapbility  *ptFeccCap = NULL);

BOOL PA_AnwserCall( 
	HMDLCALL         hPACall, 
	HMDLAPPCALL      hAppCall,
	TModuleCallInfo *ptCallInfo = NULL ,
	TCallCapbility  *ptSndCap = NULL, 
	TCallCapbility  *ptRcvCap = NULL,
	TCallInfoTP     *ptCallInfoTP = NULL,
	TCallDescriptTP *ptSndTP = NULL, 
	TCallDescriptTP *ptRcvTP = NULL,
	TDualCapList    *ptDualCapList = NULL,
    HMDLAPPCONFID    hAppConfId = 0, 
    TMDLTERLABEL    *ptTerLabel = NULL,
    TBfcpCapSet     *ptBfcp = NULL,
    TFeccCapbility  *ptFeccCap = NULL);    


BOOL PA_RejectCall( 
	HMDLCALL      hPACall, 
	HMDLAPPCALL   hAppCall, 
	EmModuleCallDisconnectReason emReason );

BOOL PA_HangupCall( 
	HMDLCALL      hPACall, 
	HMDLAPPCALL   hAppCall,  
	EmModuleCallDisconnectReason emReason );


/*-------------------------------------------------
 *     Channel API
 *-----------------------------------------------*/
//added by jacky for Channel On/Off switch
BOOL PA_ChannelSwitch( HMDLCALL hPACall , HMDLAPPCALL hAppCall , HMDLCHANNEL ahChan[], HMDLAPPCHANNEL ahAppChan[], u8 bySize, BOOL32 bOn);

BOOL PA_CloseChannel( HMDLCALL hPACall , HMDLAPPCALL hAppCall , HMDLCHANNEL hChan[], HMDLAPPCHANNEL hAppChan[], u8 bySize );

//发送双流, 如果makecall时双流能力带下来，sendDual发送的是makecall带下来的双流能力
BOOL PA_SendDualSteam(HMDLCALL hPACall , HMDLAPPCALL hAppCall, TDualCapList *ptDualCapList = NULL);    

//bSuc为TRUE, 有双流， bSuc为False, 拒绝双流, answerDual是对所有双流的应答
BOOL PA_AnswerDualStream(HMDLCALL hPACall , HMDLAPPCALL hAppCall, BOOL32 bSuc, TDualCapList *ptDualCapList = NULL);  

BOOL PA_StopDualStream(HMDLCALL hPACall , HMDLAPPCALL hAppCall, EmChannelReason emReason = emModuleChannelDisconnectNormal ); 



BOOL PA_FlowControl( HMDLCALL hPACall , HMDLAPPCALL hAppCall , HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan, u16 wBitrate );

BOOL PA_FastUpdate( HMDLCALL hPACall , HMDLAPPCALL hAppCall , HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan );


//网真通道控制用PA_SendChanCtrlTP
BOOL PA_SendChanCtrlTP(HMDLCALL hPACall , HMDLAPPCALL hAppCall, HMDLCHANNEL hChan, s32 nMsgType,u8 *pBuf, s32 nSize );
BOOL PA_SendChanCtrl(HMDLCALL hPACall , HMDLAPPCALL hAppCall, HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan, s32 nMsgType,u8 *pBuf, s32 nSize );


//每个通道只携带一种能力
BOOL PA_ChangeChannel(HMDLCALL hPACall, HMDLAPPCALL hAppCall, TChanConnectedInfo *ptConnectedInfo, s32 nSize); 

/*-------------------------------------------------
 *     Conf API
 *-----------------------------------------------*/

//h323标准会控PA_SendConfCtrl
BOOL PA_SendConfCtrl( HMDLCALL hPACall , HMDLAPPCALL hAppCall, s32 nMsgType, u8 *pBuf, s32 nSize); 


//网真会控用PA_SendConfCtrlTP,sip用
BOOL PA_SendConfCtrlTP( HMDLCALL hPACall , HMDLAPPCALL hAppCall, s32 nMsgType, u8 *pBuf, s32 nSize);

// 结束会议, 供MC使用
BOOL PA_MCStopConference( HMDLAPPCONFID hAppConfId );




/*-------------------------------------------------
 *     Regist API
 *-----------------------------------------------*/

/*====================================================================
函 数 名： PA_Register
功    能： 向服务器进行注册操作，为H323和SIP的标准接口
算法实现： 
参    数： EmPAConfProtocol emPAType  : 协议类型
           HMDLREG         *phReg     : 指向PA句柄的指针
           HMDLAPPREG       hAppReg   : 应用层句柄
           TRegistReq      *ptRegInfo : 指向注册信息结构体的指针
返回值  ： 成功，返回TRUE；失败，返回FALSE
备注    ： 1. H323终端向GK进行注册，SIP终端向注册服务器进行注册
		   2. 接口同时处理首次注册和更新注册两种操作，
		      首次注册时phReg指向的句柄值应为0，如果接口调用失败，句柄值设置为-1
			  更新注册时phReg指向的句柄值应为PA层句柄，如果调用失败，句柄值不变
		   3. 更新注册操作，必须在回调注册成功后才可以进行.
======================================================================*/
BOOL PA_Register( EmPAConfProtocol emPAType, HMDLREG *phPAReg , HMDLAPPREG hAppReg, TRegistReq *ptRegInfo );


/*====================================================================
函 数 名： PA_UnRegister
功    能： 向服务器进行取消注册操作，为H323和SIP的标准接口
算法实现： 
参    数： EmPAConfProtocol emPAType  : 协议类型
           HMDLREG          hPAReg    : PA句柄
           HMDLAPPREG       hAppReg   : 应用层句柄
返回值  ： 成功，返回TRUE；失败，返回FALSE
备注    ： 
======================================================================*/
BOOL PA_UnRegister( EmPAConfProtocol emPAType, HMDLREG hPAReg , HMDLAPPREG hAppReg );


/*====================================================================
函 数 名： PA_RegisterTP
功    能： [网真接口]向注册服务器进行注册操作
算法实现： 
参    数： EmPAConfProtocol emPAType  : 协议类型
           HMDLREG         *phReg     : 指向PA句柄的指针
           HMDLAPPREG       hAppReg   : 应用层句柄
返回值  ： 成功，返回TRUE；失败，返回FALSE
备注    ： 非标注册，通过XML注册，可以注册多个别名
======================================================================*/
BOOL PA_RegisterTP( HMDLREG *phPAReg, HMDLAPPREG hAppReg, TPARegCfg *ptPARegCfg ); 


/*====================================================================
函 数 名： PA_GetRegInfoReqTP
功    能： [网真接口]获取注册服务器上的注册信息
算法实现： 
参    数： s32 nAppId                   : 应用层的标识
           TPAGetRegInfo tPAGetRegInfo  : 注册信息结构体
返回值  ： 成功，返回TRUE；失败，返回FALSE
备注    ： 
======================================================================*/
BOOL PA_GetRegInfoReq( const s32 nAppId, HMDLREG hSipReg, HMDLREG h323Reg, TPAGetRegInfo tPAGetRegInfo );






/*-------------------------------------------------
 *     Conf API
 *-----------------------------------------------*/

#ifdef USE_NEW_CONF
/*====================================================================
函 数 名： PA_MCMakeSpeaker
功    能： [会控接口] MC指定发言人
算法实现： 
全局变量： 
参    数： HMDLAPPCONFID   hAppConfId : 应用层会议句柄
           HMDLCALL        hPACall    : 协议栈呼叫句柄
           HMDLAPPCALL     hAppCall   : 应用层呼叫句柄
返回值  ： 成功，返回TRUE；失败，返回FALSE
======================================================================*/
BOOL PA_MCMakeSpeaker( HMDLAPPCONFID hAppConfId, HMDLCALL hPACall, HMDLAPPCALL hAppCall );

/*====================================================================
函 数 名： PA_MCWithdrawSpeaker
功    能： [会控接口] MC撤销发言人
算法实现： 
全局变量： 
参    数： HMDLAPPCONFID   hAppConfId : 应用层会议句柄
           HMDLCALL        hPACall    : 协议栈呼叫句柄
           HMDLAPPCALL     hAppCall   : 应用层呼叫句柄
返回值  ： 成功，返回TRUE；失败，返回FALSE
======================================================================*/
BOOL PA_MCWithdrawSpeaker( HMDLAPPCONFID hAppConfId, HMDLCALL hPACall, HMDLAPPCALL hAppCall );

/*====================================================================
函 数 名： PA_MCMakeChair
功    能： [会控接口] MC指定主席
算法实现： 
全局变量： 
参    数： HMDLAPPCONFID   hAppConfId : 应用层会议句柄
           HMDLCALL        hPACall    : 协议栈呼叫句柄
           HMDLAPPCALL     hAppCall   : 应用层呼叫句柄
返回值  ： 成功，返回TRUE；失败，返回FALSE
======================================================================*/
BOOL PA_MCMakeChair( HMDLAPPCONFID hAppConfId, HMDLCALL hPACall, HMDLAPPCALL hAppCall );

/*====================================================================
函 数 名： PA_MCWithdrawChair
功    能： [会控接口] MC撤销主席
算法实现： 
全局变量： 
参    数： HMDLAPPCONFID   hAppConfId : 应用层会议句柄
           HMDLCALL        hPACall    : 协议栈呼叫句柄
           HMDLAPPCALL     hAppCall   : 应用层呼叫句柄
返回值  ： 成功，返回TRUE；失败，返回FALSE
======================================================================*/
BOOL PA_MCWithdrawChair( HMDLAPPCONFID hAppConfId, HMDLCALL hPACall, HMDLAPPCALL hAppCall );

/*====================================================================
函 数 名： PA_MCSendThisSource
功    能： [会控接口] MC指定选看
算法实现： 
全局变量： 
参    数： HMDLAPPCONFID   hAppConfId   : 应用层会议句柄
           HMDLCALL        hViewer      : 协议栈呼叫句柄(选看方)
           HMDLAPPCALL     hAppViewer   : 应用层呼叫句柄(选看方)
           HMDLCALL        hViewed      : 协议栈呼叫句柄(被选看方)
           HMDLAPPCALL     hAppViewed   : 应用层呼叫句柄(被选看方)
返回值  ： 成功，返回TRUE；失败，返回FALSE
======================================================================*/
BOOL PA_MCSendThisSource( HMDLAPPCONFID hAppConfId, HMDLCALL hViewer, HMDLAPPCALL hAppViewer, HMDLCALL hViewed, HMDLAPPCALL hAppViewed );

/*====================================================================
函 数 名： PA_MCCancelSendThisSource
功    能： [会控接口] MC取消选看
算法实现： 
全局变量： 
参    数： HMDLAPPCONFID   hAppConfId   : 应用层会议句柄
           HMDLCALL        hViewer      : 协议栈呼叫句柄(选看方)
           HMDLAPPCALL     hAppViewer   : 应用层呼叫句柄(选看方)
           HMDLCALL        hViewed      : 协议栈呼叫句柄(被选看方)
           HMDLAPPCALL     hAppViewed   : 应用层呼叫句柄(被选看方)
返回值  ： 成功，返回TRUE；失败，返回FALSE
======================================================================*/
BOOL PA_MCCancelSendThisSource( HMDLAPPCONFID hAppConfId,  HMDLCALL hViewer, HMDLAPPCALL hAppViewer, HMDLCALL hViewed, HMDLAPPCALL hAppViewed );



/*====================================================================
函 数 名： PA_TerMakeMeSpeaker
功    能： [会控接口] 终端申请发言
算法实现： 
全局变量： 
参    数： HMDLCALL        hPACall    : 协议栈呼叫句柄
           HMDLAPPCALL     hAppCall   : 应用层呼叫句柄
返回值  ： 成功，返回TRUE；失败，返回FALSE
======================================================================*/
BOOL PA_TerMakeMeSpeaker( HMDLCALL hPACall, HMDLAPPCALL hAppCall );

/*====================================================================
函 数 名： PA_TerMakeMeChair
功    能： [会控接口] 终端申请主席
算法实现： 
全局变量： 
参    数： HMDLCALL        hPACall    : 协议栈呼叫句柄
           HMDLAPPCALL     hAppCall   : 应用层呼叫句柄
返回值  ： 成功，返回TRUE；失败，返回FALSE
======================================================================*/
BOOL PA_TerMakeMeChair( HMDLCALL hPACall, HMDLAPPCALL hAppCall );


/*====================================================================
函 数 名： PA_ChairCancelMakeMeChair
功    能： [会控接口] 主席释放主席令牌
算法实现： 
全局变量： 
参    数： HMDLCALL        hPACall    : 协议栈呼叫句柄
           HMDLAPPCALL     hAppCall   : 应用层呼叫句柄
返回值  ： 成功，返回TRUE；失败，返回FALSE
======================================================================*/
BOOL PA_ChairCancelMakeMeChair( HMDLCALL hPACall, HMDLAPPCALL hAppCall );

/*====================================================================
函 数 名： PA_ChairSendThisSourceCmd
功    能： [会控接口] 主席选看终端
算法实现： 
全局变量： 
参    数： HMDLCALL        hPACall    : 协议栈呼叫句柄
           HMDLAPPCALL     hAppCall   : 应用层呼叫句柄
		   TMDLTERLABEL    tTerLabel  : 终端LABEL
返回值  ： 成功，返回TRUE；失败，返回FALSE
======================================================================*/
BOOL PA_ChairSendThisSourceCmd( HMDLCALL hPACall, HMDLAPPCALL hAppCall, TMDLTERLABEL tTerLabel );

/*====================================================================
函 数 名： PA_ChairCancelSendThisSource
功    能： [会控接口] 主席取消选看终端
算法实现： 
全局变量： 
参    数： HMDLCALL        hPACall    : 协议栈呼叫句柄
           HMDLAPPCALL     hAppCall   : 应用层呼叫句柄
返回值  ： 成功，返回TRUE；失败，返回FALSE
======================================================================*/
BOOL PA_ChairCancelSendThisSource( HMDLCALL hPACall, HMDLAPPCALL hAppCall );

/*====================================================================
函 数 名： PA_ChairBroadcastTerminalReq
功    能： [会控接口] 主席向MC提交发言终端的请求
算法实现： 
全局变量： 
参    数： HMDLCALL        hPACall    : 协议栈呼叫句柄
           HMDLAPPCALL     hAppCall   : 应用层呼叫句柄
		   TMDLTERLABEL    tTerLabel  : 终端LABEL
返回值  ： 成功，返回TRUE；失败，返回FALSE
======================================================================*/
BOOL PA_ChairBroadcastTerminalReq( HMDLCALL hPACall, HMDLAPPCALL hAppCall, TMDLTERLABEL tTerLabel );

/*====================================================================
函 数 名： PA_ChairBroadcastTerminalCmd
功    能： [会控接口] 主席向MC提交发言终端的命令
算法实现： 
全局变量： 
参    数： HMDLCALL        hPACall    : 协议栈呼叫句柄
           HMDLAPPCALL     hAppCall   : 应用层呼叫句柄
		   TMDLTERLABEL    tTerLabel  : 终端LABEL
返回值  ： 成功，返回TRUE；失败，返回FALSE
======================================================================*/
BOOL PA_ChairBroadcastTerminalCmd( HMDLCALL hPACall, HMDLAPPCALL hAppCall, TMDLTERLABEL tTerLabel );

/*====================================================================
函 数 名： PA_ChairCancelBroadcastTerminal
功    能： [会控接口] 主席取消发言终端
算法实现： 
全局变量： 
参    数： HMDLCALL        hPACall    : 协议栈呼叫句柄
           HMDLAPPCALL     hAppCall   : 应用层呼叫句柄
返回值  ： 成功，返回TRUE；失败，返回FALSE
======================================================================*/
BOOL PA_ChairCancelBroadcastTerminal( HMDLCALL hPACall, HMDLAPPCALL hAppCall );

#endif


#endif
