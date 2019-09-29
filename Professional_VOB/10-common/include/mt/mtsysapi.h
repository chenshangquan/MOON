/*******************************************************************************
 *  ģ����   : �ն�ҵ��                                                        *
 *  �ļ���   : mtsysapi.h                                                      *
 *  ����ļ� :                                                                 *
 *  ʵ�ֹ��� : �ṩ�ն�ҵ��ϵ�����ӿں���                                      *
 *  ����     : ������                                                          *
 *  �汾     : V3.0  Copyright(c) 1997-2005 KDC, All rights reserved.          *
 *                                                                             *
 *    =======================================================================  *
 *  �޸ļ�¼:                                                                  *
 *    ��  ��      �汾        �޸���      �޸�����                             *
 *  2005/7/20     4.0         ������      ����                                 *
 *                                                                             *
 *******************************************************************************/

#include "osp.h"
#include "tptype.h"
#include "tpstruct.h"
#include "mthint.h"
#ifndef _MT_SYS_API_H_
#define _MT_SYS_API_H_

#ifdef WIN32
#define MTAPI   extern "C"			__declspec(dllexport)
#else //#ifdef ( _VXWORKS_ || _LINUX_ )
#define MTAPI   extern "C"		
#endif

typedef void ( *FIPCONFLICT )( u8*pbyMacAddr, u32 dwIpAdrs);

typedef void (*FIPCONFLICT_d6446)(const u8* mac_addr, const struct in_addr* addr);


//�ն˴�ӡ����
extern "C" void cnPrintf( char *szFormat, ... );

typedef struct tagTPingRtn
{
	s32 nTimeOut;
    s32 nReachable;  //�Ƿ񵽴�
    s32 nTTL;
    s32 nTripTime;
}TPingRtn;

//ϵͳ����״̬
enum EmMtSysUpdateStatus
{
	emSysUpdateInit = 0,
	emSysUpdateProcessing,
	emSysUpdateSucceed,
	emSysUpdateFail	
};

typedef struct tagTModuleInit
{
	void (  *install   ) ( void );
	BOOL (  *startapp  ) ( void );
	void (  *stopapp   ) ( void );
	void (  *uninstall ) ( void );
}TModuleInit, *PTModuleInit;

API BOOL mtInitCfg();
API void mtDestoryCfg();
API void mtRegConfig( BOOL ( *startapp ) ( void ) ,void ( *stopapp ) ( void ) );



API void mtStartCodec();
API void mtStopCodec();
API void mtRegCodec( BOOL ( *startapp ) ( void ) ,void ( *stopapp ) ( void ) );

API void mtStartService();
API void mtStopService();
API void mtRegService( BOOL ( *startapp ) ( void ) ,void ( *stopapp ) ( void ) );



API void mtStartUE();
API void mtStopUE();
API void mtRegUE( BOOL ( *startapp ) ( void ) ,void ( *stopapp ) ( void ) );

API void mtStartTPReg();
API void mtStopTPReg();
API void mtRegTPReg( BOOL ( *startapp ) ( void ) ,void ( *stopapp ) ( void ) );



MTAPI BOOL  InstallSystemPath(); //����ϵͳ·����Ϣ
MTAPI void  UninstallSystemPath();//ж��ϵͳ·����Ϣ

//���������ļ�·�����ú���������ϵͳ����ʱ���ã�����ʧ��
MTAPI BOOL mtSetConfPath( s8* path );

MTAPI EmMtModel GetMtModel();//��ȡ�ն��ͺ�

//[xujinxing]
MTAPI void GetTVgaOutCfg(TVgaOutCfg &tVgaOutCfg);//��ȡvga�������
API void SetTVgaOutCfg(TVgaOutCfg &tVgaOutCfg); //����vga�������

MTAPI BOOL mtIsSupportDVB();

MTAPI EmFileSys GetFileSys();//��ȡ�ն��ļ�ϵͳ
MTAPI BOOL mtIsFileExist( char *pcFileName );

void UnstallMtFile();	
void InstallMtFile();
s8* mtGetFileName(EmMtFile emFile );

u8 mtGetExtraVidModuleType();
void mtSetExtraVidModuleType( const u32 dwType );
//void mtResetInnerMatrixCfg();

void mtSetDefaultVInnerMatrixCfg( TVInnerMatrixScheme &tVInnerMatrixScheme, u8 byVInnerMatrixSchemeIndex, u8 byExtraVideModuleType );
void mtSetIndex0MatrixScheme( TVInnerMatrixScheme &tVInnerMatrixScheme, u8 byExtraVideModuleType );

#ifdef WIN32
void mtSetWindowWorkPath(s8* path );
#endif

MTAPI BOOL HardwareInit();//Ӳ����ʼ��



#if defined(_VXWORKS_) || defined(_LINUX_)

API BOOL InitDSP();
API u32  mtGetDspMemSize( u16 wDspId );
API u32  mtGetDspSpeed( u16 wDspId );
API u32  mtGetDspMemSpeed( u16 wDspId );
API void mtPing( s8* pchHost, s32 nPacketSize, s32 nTTL, s32 nTimeout, TPingRtn* ptReturn );

#endif//

    /*********************************************/
    /*                �弶���ú���               */
    /*********************************************/

s32 mtGetOsTime();

//��ȡϵͳʱ��
BOOL mtBrdGetTime( struct tm& time );

//����ϵͳʱ��
BOOL mtBrdSetTime( struct tm& time );

//��ȡ��E1ģ���ϵ�E1����
u8 mtBrdGetE1UnitNum();

//��ѯ�Ƿ�����IP��ͻ
BOOL mtBrdIpOnceConflicted();

//ע��IP��ͻ�ص�����
void mtRegIPConflictCallBack( FIPCONFLICT pfFunc );
//davinci�µ�ip��ͻ���
void mtRegIPConflictCallBack_d6446( FIPCONFLICT_d6446 pfFunc );

	
//���ý���ͨ�ž��
MTAPI BOOL  mtSetUIHandle( u32 hWnd);
MTAPI u32   mtGetUIHandle();

//���ý����¼�����
BOOL mtSetUIEventCb( void* callback );

//������Ϣ������
BOOL mtPostMsgToUI( u16 wEventId, void* lpData = NULL , int nSize = 0 );


BOOL mtSetUIInstallFunction( void* f );
BOOL mtInstallUI();
BOOL mtUninstallUI();

//����
BOOL  mtSetKeyboardNotifyFunction(void* pf);
void* mtGetKeyboardNotifyFunction();


API void mtstart();
API void mtquit();

//������ƵԴ�˿ڻ�ȡ����ͷ����
u8   mtGetCameraIndex( EmMtVideoPort emPort );

//��������ͷ������ƵԴ�˿ڻ�ȡ
EmMtVideoPort mtGetVideoPort( u8 byCamIndex );

u32_ip mtGetHostIP();//��ȡ����IP��ַ



//�ն˶˿�

struct TMtIPPortRange
{
	//UDP

	u16 wMtBasePort;
	u16 wMtEndPort;
	u16 wMcBasePort;
	u16 wMcEndPort;
	u16 wInnerBasePort;
	u16 wInnerEndPort;

	//TCP
	u16 wMtcPort;
	u16 wOtherTCPBase;
	u16 wOtherTCPEnd;

	//not use ,only reserve
	u16 wMtH245Port;
	u16 wMcH245BasePort;
	u16 wMcH245EndPort;
};
//�����ն˶˿�
void mtCalcMtIPort( u16 wUDPPort ,u16 wTCPPort ,TMtIPPortRange& tRange ,u16 wMtcPort=60000);

//�������֡���˿�
u16  mtGetKeyboardPort();
u16 mtGetMaxCallNum();


/*
   
	 �˿ڹ���   


*/

//�����ն�ͨ�Ŷ˿ں�
void InstallCommPort( u16 wMTCPort ,u16 wTCPBasePort ,u16 wUDPBasePort );


//��ȡTCP H245ͨ�Ŷ˿ڷ�Χ
void mtGetH245PortRange(u16& wBase ,u16& wEnd);
//��ȡ�ն˿���̨�����˿ں�
u16 mtGetMtcListenPort();

//��ȡ�ն�TCPͨ����ʼ�˿ں�
u16 mtGetCommPort();

//���ݱ�������齨���ͻ�ñ���RTP�˿ں�
u16	mtGetLocalRtpPort( EmCodecComponent emComp   );


// ���ݱ�������齨���ͻ�ñ���RTCP�˿ں�
u16	mtGetLocalRtcpPort( EmCodecComponent emComp   );


//�����߼�ͨ�����ͻ�ñ���RTP�˿ں�
u16	mtGetLocalRtpPort( EmChanType emChan   );


//���ݱ�������齨���ͻ�ñ���RTCP�˿ں�
u16	mtGetLocalRtcpPort( EmChanType emChan   );

//��ȡ�ն˿���̨����˫��ʱ��ת��RTP��RTCP���ؽ��ܶ˿ں� 
void mtGetMtcVideoForwardLocalPort(u16& wRtp  ,u16& wRtcp );


//��Ƶ����ת��
void mtGetAudioDecForwardLocalPort(u16& wRtp  ,u16& wRtcp );

// ��ȡ˫���з���˫��ʱ���ؽ���RTP��RTCP�˿ں�
void	mtGetDVBVideoForwardLocalPort(u16& wRtp  ,u16& wRtcp );

//��ȡ������1�ı���RTP��RTCP�˿ں�
void mtGet1thVidDecForwardLocalPort( u16& wRtp ,u16& wRtcp );

//��ȡ������3�ı���RTP��RTCP�˿ں�
void mtGet2thVidDecForwardLocalPort( u16& wRtp ,u16& wRtcp );

//��ȡ������3�ı���RTP��RTCP�˿ں�
void mtGet3thVidDecForwardLocalPort( u16& wRtp ,u16& wRtcp );

//��ȡ������3�ı���RTP��RTCP�˿ں�
void mtGet4thVidDecForwardLocalPort( u16& wRtp ,u16& wRtcp );

//��ȡ��Ƶ�Ի����յ�RTP��RTCP�˿�
void mtGetAudioLoopbackLocalPort( u16& wRtp ,u16& wRtcp );
void mtGetAudioLoopbackLocalPortByIndex( u8& byIndex, u16& wRtp ,u16& wRtcp );

//��Ƶ�Ի����ն˿ں�
void	mtGetVideoLoopbackLocalPort( u16& wRtp ,u16& wRtcp   );
void	mtGetVideoLoopbackLocalPortSV( u16& wRtp ,u16& wRtcp   );
void	mtGetVideoLoopbackLocalPortByIndex( u8& byIndex, u16& wRtp ,u16& wRtcp   );
//��ȡ�������˿�
void  mtGetMixerLocalPort( u8 byIndex ,u16& wRtp ,u16& wRtcp   );

//VMP ���ն˿�
void  mtGetVMPLocalPort( u8 byIndex ,u16& wRtp ,u16& wRtcp   );

//MC ����Nͨ�������˿�
void  mtGetMcMixerNChanRcvPort(u16& wRtp ,u16& wRtcp   );
//MC ����VMP �ϳ����ݶ˿�
void  mtGetMcVMPRcvPort(u16& wRtp ,u16& wRtcp   );

void  mtGetMcMixerChanRcvPort( u8 byIndex ,u16& wRtp ,u16& wRtcp   );
//�����ն�ID��ȡ���ؽ���RTP�˿�
u16 mtGetMCLocalRtpPort( u8 byMtId , EmChanType emType );

//�����ն�ID��ȡ���ؽ���RTCP�˿�
u16 mtGetMCLocalRtcpPort( u8 byMtId , EmChanType emType );

//���ݱ�����������ȡMCʱ�˿�
void mtGetActiveMcLocalPort( EmCodecComponent emType ,u16& wRtp ,u16& wRtcp ,u16& wBackRtcp );

//����ͨ����ȡ�˿ڻ�ȡMCʱ�˿�
void mtGetActiveMcLocalPort( EmChanType emType ,u16& wRtp ,u16& wRtcp ,u16& wBackRtcp );

//��ȡH245�˿ڸ���
u16 mtGetH245PortSize();

//��ȡ����ǽ������ʼ�˿�
u16 mtGetProxyUDPBasePort();

//��ȡ���ص���ʼ�˿�
u16 mtGetFcnetUDPBasePort();

//xjx_080103, ��ȡnetbuf����ʼ�˿�
u16 mtGetNetBufBasePort();


//����ת��

u8 mtMapVideoType(EmVideoFormat format);//Mt������Ƶ��ʽת��ΪKdvDef�е���Ƶ����
u8 mtMapAudioType(EmAudioFormat format );//Mt������Ƶ��ʽת��ΪKdvDef�е���Ƶ����
EmAudioFormat mtMapAudioFormat(u8 type);//KdvDef�е���Ƶ����ת��ΪMt������Ƶ��ʽ
EmVideoFormat mtMapVideoFormat(u8 type);//KdvDef�е���Ƶ����ת��ΪMt������Ƶ��ʽ

const char *mtGetHintMsgDesc( u16 wId, EmLanguage emLanguage );


//�¼�����װ
BOOL mtInstallEvent();
//��ȡ�¼�����
//s8*   mtGetEventDescription(u16 wEvent );

#include "mttypeex.h"
//�������͸�������
char* GetEnumDescr(int type , int val);
#define GetEnumDescript( type ,val )   GetEnumDescr((int)em_##type ,val )




void mtPrintData(char* title,u8* buf ,EmDataType type ,u8 level =0 ,int step= 0 );
#define MTPRINT( data ,type)\
	mtPrintData(#data ,(u8*)data ,em_##type,0,0)

#define MtPrint( level , title , data ,type   )\
	mtPrintData( title ,(u8*)data ,em_##type,level,0)

//��ȡָ������Marshal�����ݴ�С
int  mtGetMarshalSize(EmDataType type);
#define _marshal_size( type) mtGetMarshalSize(em_##type )

BOOL mtMarshal(u8*const pbyDstBuf ,
			   const u8* const pbySrcBuf ,
			   EmDataType type ,
			   int nMmbCount ,
			   int& nDstMarshalSize ,
			   int& nSrcMarshalSize );

inline static BOOL mtMarshal(u8*const pbyDstBuf ,
						const u8* const pbySrcBuf ,
						EmDataType type,
						int nMmbCount = 1)
{
	int nDstMarshalSize;
	int nSrcMarshalSize;
	return mtMarshal( pbyDstBuf ,pbySrcBuf ,type ,nMmbCount ,nDstMarshalSize,nSrcMarshalSize);
}

#define _marshal( pDst ,pSrc ,type ) mtMarshal( (u8*)pDst,(u8*)pSrc ,em_##type ,1)			   
			   
BOOL mtUnmarshal(u8*const pbyDstBuf ,
			   const u8* const pbySrcBuf ,
			   EmDataType type ,
			   int nMmbCount ,
			   int& nDstMarshlSize ,
			   int& nSrcMarshalSize );

inline static BOOL mtUnmarshal(u8*const pbyDstBuf ,
						const u8* const pbySrcBuf ,
						EmDataType type,
						int nMmbCount = 1)
{
	int nDstMarshalSize;
	int nSrcMarshalSize;
	return mtUnmarshal( pbyDstBuf ,pbySrcBuf ,type ,nMmbCount ,nDstMarshalSize,nSrcMarshalSize);
}
#define _unmarshal( pDst ,pSrc ,type ) mtUnmarshal( (u8*)pDst,(u8*)pSrc ,em_##type ,1)

//s8* mtGetAppName(u16 byAppId );

//mtsysapi��ʼ��
BOOL mtSysApiInit();
void mtSysApiExit();

//����MC�ź���
void mcInstallSemphore();

//ж��MC�ź���
void mcUninstallSemphore();

//����MC�Ƿ񼤻�
void mcSetActive(BOOL bActive );

//�ж�MC�Ƿ񼤻�
BOOL mcIsActive();

//�ж��Ƿ�������չ����
BOOL mcIsAdHocPermit();

//������չ�����Ƿ�����
void mcSetAdHocPermit(BOOL bPermit );

u8  mtGetFecCapacityType();
void mtSetFecCapacityType( u8 byFecCapType );

//�Ƿ����MCģ��
BOOL mtIsMcValid();
//��ȡ��������
u16 mtGetMaxCallNum();

//��¼��ǰ���������Ƿ��ʺ���չ������жϽ��
void mcSetCallRateValid( BOOL bValid );
//��ȡ��ǰ���������Ƿ��ʺ���չ������жϽ��,ֻ�ڵ�Ե�
BOOL mcIsCallRateVaild();

//����vmp�ķ�񣬻�ȡ������
u8 mcGetVMPNum( EmInnerVMPStyle emVMPStyle);

extern BOOL32 MtCheckLicense(void);  // New license api


#if 0  // Deleted by mengxiaofeng
void mcGenEncodeData(u8 *pOutBuf, u16 wInBufLen, u8 *pInBuf, BOOL32 bDirect);
BOOL mcGetLicenseDataFromFile();
BOOL mcGetLicenseFile();
BOOL mcCheckLicenseData();
#endif

s8 * mtGetMtModelName();

//����ģ��ķ�װ
BOOL mtInitFcNet();
BOOL mtQuitFcNet();

//T2�ն˵�����������api����
BOOL mtMSSystemSwitch();
BOOL mtSetSysRunSuccess();
EmSysRunSuccessFlag mtGetRunSuccessFlag();

//����Led��״̬
void mtSetLedStatus( u8 byLedType );
//xjx_080221,����LNK�Ƶ�״̬
void mtSetLNKLedStatus( BOOL bLedOn);
//ָʾ��״̬����
void mtHDSetLedStatus( u8 byLedId, u8 byState );

MTAPI BOOL IsT2Version();
MTAPI BOOL IsHDVersion();
MTAPI BOOL Is8010A();
MTAPI BOOL IsHangyeMT();
MTAPI BOOL IsQiyeMT();


//������Ƶ���ͻ�ȡ��������
u16 mtGetBitrate( EmAudioFormat emFormat );

#define MAXCALL_MT         16
#define INVALID_CALLID 0xff //��Ч��CallId
BOOL  InitCallIdManager();
u8    AllocateCallId(s8* holder );
void  FreeCallId(u8 byCallId );

//��̬�غ�
u8 mtGetDynamicPayload( EmTpVideoFormat emFormat );
u8 mtGetAudEncType(EmAudioFormat emAudioFormat);

//VOD ״̬�жϺ���
BOOL mtVODStatePermit( EmVODState emFrom ,EmVODState emTo);

//д�ļ��������
BOOL WriteFileToDisk(char* const pFileName, char* const pchOsName, char* const pchAppName);

//�ļ�����
BOOL mtAttribFile(const s8 *  filename ,BOOL bReadOnly =FALSE);
BOOL mtRenameFile(const s8 * oldpath,const s8 * newpath);
BOOL mtRemoveFile(const s8 *  filename );
BOOL mtMakeDir(const s8* path );
//
s8*  mtGetOsVer();
s8*  mtGetHardwareVer();
s8*  mtGetSoftwareVer();
s8*  mtGetSoftwareVer_Upgrade();

BOOL mtHasInnerMatrix();


BOOL mtBrdMicAdjustIsSupport();

u8    mtBrdMicVolumeGet( );
void  mtBrdMicVolumeSet(u8 byPlus );

//��ʼ��DHCP
BOOL mtInitDHCP();
BOOL mtOpenDHCP();
BOOL mtCloseDHCP();
BOOL mtUpdateDHCPdue();
s8* mtGetMacAddr();

enum EmPathList{
	emFtpPath = 0,
	emRamdiskConfPath,
	emConfPath,
	emUserInfoPath,
	emWebfilesPath,
	emWebDocPath,
	emDataPath,
	emResPath,
	emPathListEnd
};
char* GetSysPath(EmPathList emPath);

void InitSysUpdateSem();
void DelSysUpdateSem();
void mtSetUpdateStatus(EmMtSysUpdateStatus emVal);//����ϵͳ�ļ�����״̬����
void mtGetUpdateStatus(EmMtSysUpdateStatus &emVal);//��ȡϵͳ�ļ�����״̬����

//ϵͳ�����л�VGA/Videoʱ��ʾ
void mtSysHint(EmHintMsgNo emHintMsgNo ,u16 wAppId , u16 wInstId = 1 );
const char* mtGetEventCheckString();
const char* mtPcdvGetEventCheckString();

void mtStartSpeaker( BOOL bOpen ); // �����ر�������
u8   mtInterpretCallDisconnectReason( EmCallDisconnectReason emReason );

//����banner�ı���Ϣ���ļ�
BOOL mtSaveBannerToFile( TBannerInfo& tInfo );
BOOL mtLoadBannerInfo( s8* szBuf );

API void MsgFromSlave_d6446(u32 dwID, void* pBuf, u32 dwBufSize);
BOOL IsLegalIpAddr(char* pchString );
EmMtAddrType GetAddrType( const char* pchString, u32 dwLen );

//WiFi�ӿ�, add by wangliang 2007/12/03
s32 mtWiFiGetIf( s8* pchIfName );   
s32 mtWiFiScanBss( s8* pchIfName, void** pBssList );
s32 mtWiFiFreeBss( void* pBssList );    
s32 mtWiFiGetStat( s8* pchIfName, void* pStatus ); 
s32 mtWiFiGetMib( s8* pchIfName, void* pMib ); 
s32 mtWiFiJoin( s8* pchIfName, void* pItem ); 
s32 mtWiFiUnJoin( s8* pchIfName ); 

//8010�ն˵�ι������, xjx_080310
BOOL mtOpenWdGuard(u32 dwNoticeTimeout);
BOOL mtCloseWdGuard(void);
BOOL mtNoticeWdGuard(void);
BOOL mtWdGuardIsOpened(void);
s32 mtSetVidOffsetParam( u32 dwInterface, s32 dwHoff, s32 dwVoff );
void MtmpStartInstallSemphore();
void MtmpStartUninstallSemphore();

// ���ڸ���1.2.1�汾�Ķ��׷ֱ���̨�ꡢ�����
#define HD_MULTIRES_VER            "Hd.multi.res.ver"
extern void mtSysGetPriomDecSrcRes( u16& w, u16& h );
extern void mtSysGetPriomEncScale( u16& w, u16& h );
extern void mtSysGetBannerImageSrc( u32& w, u32& h);

enum EmHdMultiResFile
{
	emHdSymbolFile1 = 0,
	emHdSymbolFile2,
	emHdSymbolFile3,
	emHdBannerFile1,
	emHdBannerFile2,
	emHdBannerFile3,
	emHdMultiResFileEnd,
};
s8* mtGetHdMultiResFileName( EmHdMultiResFile emFileType );
u16 mtArchSwapLE16( u16 x);
u32 mtArchSwapLE32( u32 x);
u16 mtArchSwapBE16( u16 x);
u32 mtArchSwapBE32( u32 x);

API void mtSetHDBVersion( BOOL bBVersion);
API BOOL mtHDIsBVersion();

u8 mtGetSnapShotNum();
u8 mtGetSnapShotFileName(s8 achFileName[][128]);
s8* mtGetSnapShotPath();
BOOL mtGetEarlySnapShotPath(s8* pszBuf, s32 dwSize);
BOOL ClearAllSnapShot();
BOOL mtGetFileUpdateTime(const s8* pFileName, u32& dwTime);
BOOL mtPathExist(const s8* path);
void  mtGetSubHardwareVer( s8 *pSubVer, int nSize );

template<class T>
void Swap(T& val1, T& val2)
{
	T t;
	t = val1;
	val1 = val2;
	val2 = t;
}

BOOL32 mtIsLocalSupportXML ();
BOOL32 mtIsRemoteSupportXML();
void mtSetLocalSupportXML ( BOOL32 bSupport );
void mtSetRemoteSupportXML( BOOL32 bSupport );

u8 mtGetLocalHashType ();
u8 mtGetRemoteHashType();
void mtSetLocalHashType ( u8 byType );
void mtSetRemoteHashType( u8 byType );

#endif/*!_MT_SYS_API_H_*/
