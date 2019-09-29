#ifndef SIPMODULE_H
#define SIPMODULE_H

#include "kdvtype.h"
#include "modulecallstruct.h"
#include "modulemananger.h"
#include "tpmodulestruct.h"

#define  S2H_DEFAULT_MAXSENDRECVBUFFERSIZE  20480       //Ĭ���׽��ַ��ͽ��ջ����С
#define  MAX_INSTANCE_PROTOCAL              192
#define  SIPSERVPRINT_BUFFERSIZE            1024

#ifndef  DECLARE_MODULE_HANDLE
#define  DECLARE_MODULE_HANDLE(name)    typedef struct { int unused; } name##__ ; \
										typedef const name##__ * name; \
										typedef name*  LP##name;
#endif


template < class T >
T SIP_SAFE_CAST( T &t, u8 *p )
{
	if (NULL == p) return t;
	memcpy( &t, p, sizeof( T ) );
	return t;
}

#ifdef WIN32
#define SIPCALLBACK __cdecl
#else
#define SIPCALLBACK
#endif


enum EmSipModRegState
{
	    emSipModSateNone,
		emSipModState2Idle,
		emSipModState2Registered,
		emSipModSate2Failed,
		emSipModState2Terminated,
		emSipModSate2Redirected,
		emSipModState2SendMsgFailed,
};

typedef struct tagTSipModRegResult
{
	BOOL32 bRegistered;
	EmSipModRegState emRegState;
	tagTSipModRegResult()
	{
		bRegistered = FALSE;
		emRegState = emSipModSateNone;
	}
}TSipModRegResult, *PTSipModRegResult;

class CConfig
{
public:
	CConfig()
		:m_emEndpointType(emModuletypeBegin),
		m_wCallingPort(5060),
		m_wMaxCallNum(MAX_INSTANCE_PROTOCAL),
		m_wIfProxy(FALSE),
		m_wReserved(0),
		m_dwKeepAliveTime(30),
		m_nProductIdSize(0),
		m_nVerIdSize(0),
		m_wRegClientNum(MAX_INSTANCE_PROTOCAL),
		m_dwMaxSendRecvBufferSize(S2H_DEFAULT_MAXSENDRECVBUFFERSIZE)
	{
		memset( m_abyProductId, 0, MAX_LEN_PRODUCT_ID );
		memset( m_abyVersionId, 0, MAX_LEN_VERSION_ID );
	}
	emModuleEndpointType m_emEndpointType;
	u16  m_wCallingPort; //���ж˿�
	u16  m_wMaxCallNum;  //��������
	u16  m_wIfProxy;     //��Ϊע������������0 ������0
	u16  m_wReserved;
	u32  m_dwKeepAliveTime;        //second
	u16  m_wRegClientNum;          //֧��CNS���ע�������
	u32  m_dwMaxSendRecvBufferSize;//�׽��ַ��ͽ��ջ����С(��ʱʹ��Ĭ��ֵ)
	s32					  m_nProductIdSize;
	u8					  m_abyProductId[MAX_LEN_PRODUCT_ID];				//��Ʒ��
	s32					  m_nVerIdSize;
	u8					  m_abyVersionId[MAX_LEN_VERSION_ID];				//�汾��
	
};

//TPΪ�������
typedef BOOL32 (SIPCALLBACK* CBNewCallIncoming)( HMDLCALL hCall, TModuleCallInfo *ptModParam, TCallCapbility *ptSndCap , TCallCapbility *ptRcvCap,
	                                            TCallInfoTP *ptCallTP , TCallDescriptTP* ptSndTP , TCallDescriptTP* ptRcvTP ); //
typedef BOOL32 (SIPCALLBACK* CBCallConnected)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TModuleCallInfo *ptModParam,TCallCapbility *ptSndCap, TCallCapbility *ptRcvCap,
										        TCallInfoTP *ptCallTP , TCallDescriptTP *ptSndTP , TCallDescriptTP *ptRcvTP );
typedef BOOL32 (SIPCALLBACK* CBCallDisconnected)(HMDLCALL hCall, HMDLAPPCALL hAppCall, const EmModuleCallDisconnectReason EmReason ); //sip�Ҷϻ�ܾ�


//�ص��ɹ���ͨ��
typedef BOOL32 (SIPCALLBACK* CBChannelConnected)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TChanConnectedInfo *pTConnectedInfo, s32 nSize, TChanDescriptTP *pTDesTP );       
//�ص�ʧ�ܵ�ͨ��
typedef BOOL32 (SIPCALLBACK* CBChannelDisconnected)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TChanDisConnectedInfo *pTDisConInfo, s32 nSize );
//�ص���ǰ���е�˫��
typedef BOOL32 (SIPCALLBACK* CBSipDualIncoming)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TDualCapList *tDual);


typedef BOOL32 (SIPCALLBACK* CBFastUpdapte)( HMDLCALL hCall, HMDLAPPCALL hAppCall, HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan );
typedef BOOL32 (SIPCALLBACK* CBFlowControl)( HMDLCALL hCall, HMDLAPPCALL hAppCall, HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan, u16 wBitRate);


typedef BOOL32 (SIPCALLBACK* CBSipRegister)( HMDLREG hReg, HMDLAPPREG hAppReg, EmRegResult emPARegResult, const u8 *pBuf, const s32 nLen );
typedef BOOL32 (SIPCALLBACK* CBSipUnRegister)( HMDLAPPREG hAppReg, EmRegResult emPARegResult, const u8 *pBuf, const s32 nLen);
//����ӷ������յ�ע��ʧ�ܻ�Ӧ�������������pbuf�����η���emPARegisterNameDup��nsize,TPARegName�� 
//����ǳ�������֮���ʧ�ܣ� pBuf�з���emPARegisterFailed
//������������ɴ�, pbuf�з���emPARegistrarUnReachable
//��������� pbuf�з��� emPAUnknownReason 

typedef BOOL32 (SIPCALLBACK* CBSipNonStaTP)( HMDLCALL hCall, HMDLAPPCALL hAppCall, const u8 *pBuf, const s32 nBufLen );
typedef BOOL32 (SIPCALLBACK* CBGetRegInfoAck)(const s32 nAppId, const u8 *pBuf, const s32 nLen, const u8  byVersion );
//��ȡȫ����CNS��ȫ��ע����Ϣ�ص��� pBuf������Ϊ�� TPARegPackInfo ��EmPAGetRegInfoType,  TPARegInfo


 
//�ݲ�ʹ��
typedef BOOL32 (SIPCALLBACK* CBSipDualAnswer)(HMDLCALL hCall, HMDLAPPCALL hAppCall, HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan,  BOOL32 bSuc, TChanConnectedInfo* tDual);     //sipӦ��h323
typedef BOOL32 (SIPCALLBACK* CBSipDualStop)(HMDLCALL hCall, HMDLAPPCALL hAppCall, HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan);

typedef BOOL32 (SIPCALLBACK* CBFeccChannelConnected)(HMDLCALL hCall, HMDLAPPCALL hAppCall, TFeccCapbility *ptFeccCap);
typedef BOOL32 (SIPCALLBACK* CBFeccMsg)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMdlFeccStruct tFeccStruct );

typedef BOOL32 (SIPCALLBACK* CBMultipleConference)( HMDLCALL hCall, HMDLAPPCALL hAppCall, BOOL32 bFlag );

typedef struct tagCallCBFunction
{
	CBNewCallIncoming      m_cbNewCallIncoming;
	CBCallDisconnected     m_cbCallDisconnected;
	CBCallConnected        m_cbCallConnected;
	CBChannelConnected     m_cbChannelConnected;
	CBChannelDisconnected  m_cbChannelDisconnected;
	CBFastUpdapte          m_cbFastUpdate;
	CBFlowControl          m_cbFlowControl;
	CBSipDualIncoming      m_cbDualIncoming;
	CBSipRegister          m_cbSipReg;
	CBSipUnRegister        m_cbSipUnReg;
	CBSipNonStaTP          m_cbSipNonStaTP;
	CBGetRegInfoAck        m_cbSipGetRegInfoAck;
	CBFeccChannelConnected	m_cbFeccChannelConnected;
	CBFeccMsg				m_cbFeccMsg;
	CBMultipleConference	m_cbMultipleConf;

	tagCallCBFunction()
	{
		m_cbNewCallIncoming = NULL;
		m_cbCallConnected = NULL;
		m_cbCallDisconnected = NULL;
		m_cbChannelConnected = NULL;
		m_cbChannelDisconnected = NULL;
		m_cbFastUpdate = NULL;
		m_cbFlowControl = NULL;
		m_cbDualIncoming = NULL;
		m_cbSipReg = NULL;
		m_cbSipUnReg   = NULL;
		m_cbSipNonStaTP = NULL;
		m_cbSipGetRegInfoAck = NULL;
		m_cbFeccChannelConnected = NULL;
		m_cbFeccMsg = NULL;
		m_cbMultipleConf = NULL;
	}
}TCallCBFunction;


typedef struct tagSipModuleCfg
{
	s32 m_nsipServiceAppId;
	s32 m_nsipStackinAppId;
	s32 m_nsipStackoutAppId;
	
	u16 m_wTotalCallNum;
	u16 m_wTotalRegNum;
	TCallCBFunction m_tCallCBFuntion;
	BOOL32  m_bSendRecv;
	BOOL32	m_bSendRecvWithCommonCap;

	CConfig  m_cConfig;
	tagSipModuleCfg()
	{
		m_nsipServiceAppId = -1;
		m_nsipStackinAppId = -1;
		m_nsipStackoutAppId = -1;
		m_wTotalCallNum = 10;
		m_wTotalRegNum = 10;
		m_bSendRecv = FALSE;
		m_bSendRecvWithCommonCap = FALSE;
	}
	
}TSipModuleCfg;



class SipModule
{
	//Call API:
public:
	
	//H323 module init function
	static BOOL32 SipModuleInit( TSipModuleCfg &tCfg );   
	//H323 module start recv
	static BOOL32 SipModuleStart();
	//H323 module stop recv
	static BOOL32 SipModuleStop();
	//H323 module exit function
	static BOOL32 SipModuleExit();
	
	
	static BOOL32 SipModuleMakeOutgoingCall(
				HMDLAPPCALL hAppCall, 
				TModuleCallInfo *ptModParam = NULL, 
				TCallCapbility *ptSndCap = NULL, 
				TCallCapbility *ptRcvCap = NULL,
				TCallInfoTP *ptCallInfoTP = NULL, 
				TCallDescriptTP *ptSndTP = NULL, 
				TCallDescriptTP *ptRcvTP = NULL, 
				BOOL32 bInviteWithSDP = TRUE, 
				TDualCapList *pTDual = NULL, 
				HMDLAPPCONFID hAppConfId = NULL, 
				TMDLTERLABEL* pTerLabel = NULL, 
				TBfcpCapSet *ptBfcp = NULL, 
				TFeccCapbility *ptFeccCap = NULL,
				BOOL32 bAutoGetRegSrvIP = FALSE );
	//���makeCallʱtdual�������� ����Ϊ˫��������tdual, ���Ǻ���ʱ˫������������ȥ���ϲ����sendual�ŷ�˫����ȥ�� �Ͳ��ص�dualincoming, ֻ�ص�channelconnected,��disconnected
	
	static BOOL32 SipModuleCallAnswer(
				HMDLCALL hCall, 
				HMDLAPPCALL hAppCall, 
				TModuleCallInfo *ptModParam, 
				TCallCapbility *tSndCap, 
				TCallCapbility *tRcvCap,  
				TCallInfoTP *ptCallInfoTP = NULL, 
				TCallDescriptTP *ptSndTP = NULL, 
				TCallDescriptTP *tRcvTP = NULL, 
				TDualCapList *pTDual = NULL, 
				HMDLAPPCONFID hAppConfId = NULL, 
				TMDLTERLABEL* pTerLabel = NULL, 
				TBfcpCapSet *ptBfcp = NULL, 
				TFeccCapbility *ptFeccCap = NULL );                           
	//Ӧ��call ����ͬ��������


	static BOOL32 SipModuleCallAck(HMDLCALL hCall, HMDLAPPCALL hAppCall, TCallCapbility *tSndCap = NULL , TCallCapbility *tRcvCap = NULL, TBfcpCapSet *ptBfcp = NULL, TDualCapList *ptDual = NULL );                               //call ACK, ����ͬ�������� 
	
	static BOOL32 SipModuleCallReject(HMDLCALL hCall, HMDLAPPCALL hAppCall, EmModuleCallDisconnectReason emReason);   //�ܾ�call
	
	static BOOL32 SipModuleCallHangup(HMDLCALL hCall, HMDLAPPCALL hAppCall, EmModuleCallDisconnectReason emReason);   //�Ҷ�call
	

public:

	static BOOL32 CloseChannel(HMDLCALL hCall , HMDLAPPCALL hAppCall,  HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan, EmChannelReason emReason = emModuleChannelDisconnectNormal );   
	//�رյ���ͨ�� 
	
	static BOOL32 SipModuleChangeChannel(HMDLCALL hCall, HMDLAPPCALL hAppCall, TChanConnectedInfo *ptConnectedInfo, s32 nSize, BOOL bChangeAddress = FALSE ); 
	//ÿ��ͨ��Я��ָ��������

	static BOOL32 SipModuleRegister(HMDLREG hReg, HMDLAPPREG hAppReg, TRegistReq* tRegInfo);     //ÿ��ֻ��ע��һ����������׼ע��
	
	static BOOL32 SipModuleUnregister(HMDLREG hReg, HMDLAPPREG hAppReg);
	
	static BOOL32 FlowCtrl(HMDLCALL hCall , HMDLAPPCALL hAppCall , HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan, u16 wBitrate);
	
	static BOOL32 FastUpdate(HMDLCALL hCall , HMDLAPPCALL hAppCall , HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan);

	static BOOL32 FastUpdateWithoutID(HMDLCALL hCall , HMDLAPPCALL hAppCall);             //����fastupdate����ID

	static BOOL32 SipModuleSendFeccMsg( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMdlFeccStruct tFeccAction, TMDLTERLABEL tDstLabel );
	
	static BOOL32 SipModuleConfEvent( HMDLCALL hCall, HMDLAPPCALL hAppCall, u16 wEvent, u8* pBuf, u16 wLen );	//HD3��MCU��ͨ�����Ϣ

	//˫��API

	static BOOL32 SipModuleSendDual(HMDLCALL hCall , HMDLAPPCALL hAppCall, TDualCapList *ptDual = NULL);    
	//����˫��,���ͨ�����ϲ�ҵ�����, ���makecallʱ˫��������������sendDual���͵���makecall��������˫������

	static BOOL32 SipModuleAnswerDual(HMDLCALL hCall , HMDLAPPCALL hAppCall, BOOL32 bSuc, TDualCapList *ptDual = NULL);  
	//bSucΪTRUE, ��˫���� bSucΪFalse, �ܾ�˫��, answerDual�Ƕ�����˫����Ӧ��

	static BOOL32 SipModuleStopDual(HMDLCALL hCall , HMDLAPPCALL hAppCall, EmChannelReason emReason = emModuleChannelDisconnectNormal ); 
	//stopdualֹͣȫ��˫��,  ��˫������ȥ��medialine, ��������Ϊinactive


public:         //��������� API
			
	static BOOL32 SipModuleRegisterTP(HMDLREG hReg, HMDLAPPREG hAppReg, TPARegCfg tPARegCfg ); //ע�����������Ǳ�ע�ᣬͨ��xmlע��
	
	static BOOL32 SipModuleSendNonStaTP(HMDLCALL hCall , HMDLAPPCALL hAppCall,  u8 *pBuf,  s32 nBufLen); //���淢��NonStandard-conf��Ϣ
	
	static BOOL32 SipModuleGetRegInfoReq( s32 nAppId, TPAGetRegInfo tPAGetRegInfo, HMDLREG hReg = (HMDLREG)-1 );	//��Ϊ�ϰ汾��hRegȡĬ��ֵ-1

	// CONFERENCE
	//static BOOL SipModuleConfEvent( HMDLCALL hCall, HMDLAPPCALL hAppCall, u16 wEvent, u8* pBuf, u16 wLen );
	
	// �½ӿ�  ����Ĳ���
	// mc��
	static BOOL SipMCStopConference( HMDLAPPCONFID hAppConfId );
	static BOOL SipMCMakeSpeaker( HMDLAPPCONFID hAppConfId, TMDLTERLABEL tTerLabel );
	static BOOL SipMCWithdrawSpeaker( HMDLAPPCONFID hAppConfId, TMDLTERLABEL tTerLabel );
	static BOOL SipMCMakeChair( HMDLAPPCONFID hAppConfId, TMDLTERLABEL tTerLabel );
	static BOOL SipMCWithdrawChair( HMDLAPPCONFID hAppConfId, TMDLTERLABEL tTerLabel );
	static BOOL SipMCSendThisSource( HMDLAPPCONFID hAppConfId, TMDLTERLABEL Viewer, TMDLTERLABEL Viewed );
	static BOOL SipMCCancelSendThisSource( HMDLAPPCONFID hAppConfId, TMDLTERLABEL Viewer, TMDLTERLABEL Viewed );
	static BOOL SipMCAddTer( HMDLAPPCONFID hAppConfId, TMDLTERMINALINFO* ptTerInfoList, u8 byNum );
	static BOOL SipMCDelTer( HMDLAPPCONFID hAppConfId, TMDLTERMINALINFO* ptTerInfoList, u8 byNum );
	
	// chair��
// 	static BOOL SipChairSendThisSource( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERLABEL tTerlabel, u8 ctrlMode );
// 	static BOOL SipChairCancelSendThisSource( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERLABEL tTerLabel );
	
	// ter��
// 	static BOOL SipTerMakeMeSpeaker( HMDLCALL hCall, HMDLAPPCALL hAppCall );
// 	static BOOL SipTerCancelMakeMeSpeaker( HMDLCALL hCall, HMDLAPPCALL hAppCall );
// 	static BOOL SipTerMakeMeChair( HMDLCALL hCall, HMDLAPPCALL hAppCall );
// 	static BOOL SipTerCancelMakeMeChair( HMDLCALL hCall, HMDLAPPCALL hAppCall );

private:
    
	static u16 m_wSipServiceAppId; 
	
	static BOOL32 Post( CModuleMsg &cMsg );
	
};

typedef struct tagTSipPrint
{
	emModuleType emSipModule;
	s32 nLevel;
	s8  pAlias[MAX_LEN_CALL_ALIAS+1];
	u16 wCallId;
	u8  byFlag;   //0, ����callid alias�� 1�� ��callid ��ӡ�� 2�� ��alias��ӡ
	tagTSipPrint()
	{
          emSipModule= emModuleService ;
		  nLevel = 1;							 //�쳣��ӡ
		  memset(pAlias, 0, sizeof(pAlias));
		  wCallId = 0;
		  byFlag = 0;
	}
}TSipPrint;

API void setsiplogalias(s8 *pAlias); 
API void setsiplogcallid(u16 wCallId);
API void sipservicelogon(s32 nModule, s32 nLevel);
API void sipservicelogoff();
API void sipmodulehelp();
API void sipshowcall();
API void sipshowcallid(u16 wCallid);
API void sipmoduleversion();
API void sipshowreg();
void SipServicePrintf( emModuleType emSipModule, s32 nLevel, s8 *pAlias, u16 wCallId, const char* pFormat, ... );

#endif
