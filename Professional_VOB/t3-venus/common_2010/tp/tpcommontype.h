#ifndef _h_tpcommontype_h__
#define _h_tpcommontype_h__

//MTType begin.
#include "osp.h"

enum EmTPDevRegUpdateSer
{
	emDevInvalid = -1,
		emTPTPad_Win7,
		emTPTPad_Android,
		emTPTPad_IOS,
		emTPCns_T300A,
		emTPCns_T300B,
};

//��������
enum EmTPUpdateType  
{
	emTPUpdateForced,  //ǿ������
		emTPUpdateSelected  //ѡ������
};


/**********************************add enum begin**********************************/

enum EmWiFiLinkStat
{
	emWiFiIdle = 0,
	emWiFiConnecting,
    emWiFiConnectFailed,
    emWiFiConnected,
    emWiFiDisconnecting,
    emWiFiDisconnected
};

// enum EmWiFiLinkStatus
// {
// 	emWiFiIdle = 0,
//     emWiFiConnected,
//     emWiFiConnecting,
//     emWiFiConnectFailed,
//     emWiFiDisconnected,
//     emWiFiDisconnectFailed,
//     emWiFiDevicePullIn,
//     emWiFiDevicePullOut
// };

enum EmWiFiSelType
{
    emWiFiCfgSel = 0,
    emWiFiScanSel
};

enum EmWiFiNetType
{
    emWiFiAdHoc = 0,
    emWiFiInfra
};

enum EmWiFiEncryptType
{
    emWiFiEncryptNone = 0,
    emWiFiEncryptWep,
    emWiFiEncryptWpa,
    emWiFiEncryptWpa2
};

enum EmWiFiEncryptArithmetic
{
	emWiFiArithNone = 0,
	emWiFiArithWep40,
	emWiFiArithTkip ,
	emWiFiArithWrap,
	emWiFiArithAes,						/* aes */
	emWiFiArithWep104	
};

// VOD REJ Code 
//------------------------��Ϣ��REJ��-------------------------------------------
enum EmVODRejCode 
{	
	emVODNoReason = 0, // δ֪����
	emVODFileNotFound = 1, // �ļ�δ�ҵ�
	emVODPalyNotStarted = 2, //����δ��ʼ
	emVODMaxUser = 3, // �����û��Ѵﵽ�����������
	emVODUserNotExist = 4, // �û���������	
	emVODUserLogined = 5, // ���û��Ѿ���¼
	emVODInvalidedPassword = 6, // �������
	emVODMEDIAVODInvalidedFileNameType = 7, // Client <-- Server ,�ļ���Ϊ�ջ���ASF�ļ�
	emVODPlayBusy = 9, // Client <-- Server ,���ڷ�����һ�ε���������
	emConnectFailed = 10,
	emDisconnect = 11 ,// �����ж�
	emVODNoError      //�����ɹ�
};

//VOD ״̬
enum EmVODState
{
	emVODIdle         ,//����
	emVODLogin        ,//���ڵ�½
	emVODFileListQuery,//���ڻ�ȡ�ļ��б�
	emVODFileInfoQuery ,//���ڲ�ѯ�����ļ���Ϣ
	emVODPlay  ,//���ڲ���
	emVODPause    ,//��ͣ
	emVODStop  ,   //ֹͣ
	emVODSeek  ,   //ָ��λ�ò���
	emVODActiveEnd
};

//���
enum EmTextAlign
{
	emAlignLeft = 0,//����
	emAlignCenter,//����
	emAlignRight//����
};

enum EmRollMode
{
	emStatic = 0,
	emRight2Left,
	emDown2Up
};

enum EmRollSpeed
{
	emSlower = 0,
	emSlow,
	emNormal,
	emFast,
	emFaster
};

//����ֹͣλ����
enum EmStopBits
{
    em1StopBit =0,
    em1HalfStopBits=1,
    em2StopBits = 2
};



//����У��λ����
enum EmParityCheck
{
    emNoCheck = 0 ,//��У��
    emOddCheck =1 ,//��У��
    emEvenCheck =2,//żУ��
};

//��������
enum EmSerialType
{
    emRS232 = 0,
    emRS422 = 1,
    emRS485 = 2,
	emSerialTcpip =3,
	emRS422_1 = 4,
	emRS422_2 = 5,
	emRS422_3 = 6,
	emRSCom_1 = 7,
	emRSCom_2 = 8,
	emRSCom_3 = 9,
	emRSCom_4 = 10,
	emRSCom_5 = 11,
	emRSCom_6 = 12
};

//��������
enum EmLanguage
{
    emEnglish  = 0,
    emChineseSB = 1,
	emLangeEnd
};




//Э������
enum EmConfProtocol
{
	emH323  = 0, 
	emH320  = 1,
	emSIP   = 2,
	emSat   = 3, 
	emInvalidConfProtocel
};

//���뷽ʽ
enum EmEncodeMode
{
    emQualityFirst  = 0, 
    emSpeedFirst    = 1,
    
};

//�����ָ�����
enum EmLostPackageRestore
{
    emLPQualityFirst  = 0, 
    emLPSpeedSlow     = 1,
    emLPSpeedNormal   = 2,
    emLPSpeedFast     = 3,
};

//��������
enum EmMatrixType
{
	emMatrixInner   = 0, 
	emMatrixOuter   = 1,
	emMatrixVas     = 2,
};

//˫����ʾģʽ
enum EmDualVideoShowMode
{
    emDualVideoOnSigleScreen  =0,//����˫��
    emEachVideoOwnScreen      =1,//˫��˫��
	emTripleVideoOnSingleScn  =2 //��������
};

//��ʾ����
enum EmDisplayRatio
{
	emDR4to3      = 0, //4:3
	emDR16to9     = 1, //16:9
	emDRAuto      = 2, //0:0
};

//��Ƶ����
enum EmVideoType
{
   emPriomVideo = 0 ,//����Ƶ
   emSecondVideo = 1//�ڶ�·��Ƶ
};


//��Ƶ��ʽ����
enum EmVideoStandard
{
    emPAL  =0 ,
    emNTSC = 1 ,
//    emSECAM = 2
};

//��ƵԴ����
enum EmVideoInterface
{
    emVGA    = 0, 
    emSVideo = 1,
    emCVideo = 2,
};

//�ն���Ƶ�˿�
enum EmMtVideoPort
{
	//hd2.0��ƵԴ����
	emMtVGA   =0 , //VGA 
	emMtSVid    , //S ����
	emMtPC      , //PC
	emMtC1Vid   ,  //C1����   DVI 1
	emMtC2Vid   ,  //C2����   DVI 2
	emMtC3Vid   ,  //C3����   DVI 3
	emMtC4Vid   ,  //C4����   c
	emMtC5Vid   ,  //C5����   sdi 1
	emMtC6Vid   ,  //C6����   sdi 2

	emMtExternalVid = 10,//���þ���ӳ���ʼֵ
	emMtVideoMaxCount = 74, //���֧����ƵԴ����
	emMtVidInvalid = 255 
};

//Ӧ��ʽ����
enum EmTripMode
{
    emTripModeAuto      =0,  //�Զ�
    emTripModeManu      =1,  //�ֶ� 
	emTripModeNegative  =2,   //�ܾ����ر�
};

//̨������
enum EmLabelType
{
    emLabelAuto    =0,   //�Զ�
    emLabelUserDef =1,  //�Զ���
    emLabelOff     =2  //�ر�
};

//E1��·�������
enum EmDLProtocol
{
    emPPP   = 0, 
    emHDLC  = 1,
    emPPPOE = 2,
    emMP    = 3
};

//E1��֤����
enum EmAuthenticationType
{
    emPAP  = 0,
    emCHAP = 1
};

//֡�ʵ�λ����
enum EmFrameUnitType
{
    emFrameSecond =0,
    emSecondFrame =1
};

// ý������
enum EmMediaType
{
	emMediaVideo = 1, //��Ƶ
	emMediaAudio = 2, //��Ƶ
	emMediaAV    = 3, //��Ƶ����Ƶ
};


//��ƵЭ������
enum EmVideoFormat
{
    emVH261     = 0,
    emVH262     = 1,//MPEG2
    emVH263     = 2,
    emVH263plus = 3,
    emVH264     = 4,
    emVMPEG4    = 5,

	emVEnd		
};

//��ƵЭ������
enum EmAudioFormat
{
    emAG711a  = 0,
    emAG711u  = 1,
    emAG722   = 2,
    emAG7231  = 3,
    emAG728   = 4,
    emAG729   = 5,
    emAMP3    = 6,
	emAG721   = 7,
	emAG7221  = 8,
	emAG719   = 9,
	emAMpegAACLC =10,
	emAMpegAACLD = 11,

	emAEnd	 
};


//�ֱ�������
enum EmVideoResolution
{
    emVResolutionAuto     = 0,   //�Զ�
    emVSQCIF              = 1,   //SQCIF88x72
	emVQCIF               = 2,   //QCIF176x144
    emVCIF                = 3,   //CIF352x288
    emV2CIF               = 4,   //2CIF352x576
    emV4CIF               = 5,   //4CIF704x576
    emV16CIF              = 6,   //16CIF1408x1152

	emVHD480i720x480      = 7,   //480i720x480
	emVHD480p720x480      = 8,   //480p720x480
	emVHD576i720x576      = 9,   //576i720x576
	emVHD576p720x576      = 10,  //576p720x576

	emVHD720p1280x720     = 11,  //720p1280x720
	emVHD1080i1920x1080   = 12,  //1080i1920x1080
	emVHD1080p1920x1080   = 13,  //1080p1920x1080
	
		
	emVGA352x240          = 14,  //352x240
	emVGA704x480          = 15,  //704x480
	emVGA640x480          = 16,  //VGA640x480
	emVGA800x600          = 17,  //SVGA800x600
	emVGA1024x768         = 18,  //XGA1024x768
	emVGA1280x768         = 19,  //WXGA1280x768
	emVGA1280x800         = 20,  //WXGA1280x800
	emVGA1366x768         = 21,  //WXGA1366x768
	emVGA1280x854         = 22,  //WSXGA1280x854
	emVGA1440x900         = 23,  //WSXGA1440x900
	emVGA1280x1024        = 24,  //SXGA1280x1024
	emVGA1680x1050        = 25,  //SXGA+1680x1050
	emVGA1600x1200        = 26,  //UXGA1600x1200
	emVGA1920x1200        = 27,  //WUXGA1920x1200

	emVSQCIF112x96        = 28,
	emVSQCIF96x80         = 29,
	emV320x192            = 30,
	emV432x240            = 31,
	emV480x272            = 32,
	emV640x368            = 33,
	emV864x480            = 34,
	emV960x544            = 35,
	emV1440x816           = 36,

	emVResEnd = 50,
};

//QOS���ͷ���
enum EmQoS
{
   emDiffServ  = 0,      //���ַ���
   emIPPrecedence  = 1  //IP����
};

//TOS ����
enum EmTOS
{
	emTOSNone        = 0,//��ʹ��
	emTOSMinCost     = 1,//��С����
	emTOSMaxReliable = 2,//��߿ɿ���
	emTOSMaxThruput  = 3,//���������
	emTOSMinDelay    = 4,//��С�ӳ�
};


//λ��
enum EmSite
{
    emLocal = 0,  //����
    emRemote    //Զ��
};

//����10��ͨ��
enum EmChanType
{
	emChanSendAudio,
	emChanSendPrimoVideo,
	emChanSendSecondVideo,
	emChanSendFecc,
	emChanSendT120,

	//����ͨ��
	emChanRecvAudio,
	emChanRecvPrimoVideo,
	emChanRecvSecondVideo,
	emChanRecvFecc,
	emChanRecvT120,

	emChanTypeEnd	
};

//���������������
enum EmCodecComponent
{
	emPriomVideoEncoder  =0,
	emPriomVideoDecoder  ,

	emSecondVideoEncoder ,
	emSecondVideoDecoder ,

	emAudioEncoder ,
	emAudioDecoder ,
	emCodecComponentEnd,
};

//�ն��ͺ�
enum EmMtModel
{
	emUnknownMtModel=0,
	emPCMT  =1    ,//�����ն�
	em8010      ,
	em8010A     ,
	em8010Aplus ,//8010A+
	em8010C     ,
	em8010C1    ,//8010C1
	emIMT       ,
	em8220A     ,
	em8220B     ,
	em8220C     ,
	em8620A     ,
	emTS6610E   ,
	emTS6210    ,
	em8010A_2   ,
	em8010A_4   ,
	em8010A_8   ,
	em7210      ,
	em7610      ,
	emTS5610    ,
	emTS6610    ,
	em7810      ,
	em7910      ,
	em7620_A    ,
	em7620_B    ,
	em7820_A	,
	em7820_B	,
	em7920_A	,
	em7920_B	

};
// << �ļ�ϵͳ���� >>
enum EmFileSys
{
	emRAWFS=1,//raw file system [ramdisk + rawblock + tffs]
	emTFFS  //tffs
};
//�����㷨
enum EmEncryptArithmetic
{
	emEncryptNone = 0,
	emDES         = 1,
	emAES         = 2,
	emEncryptAuto = 3,

	emEncryptEnd
	
};

//����
enum EmAction
{
    emActStart,
    emActStop,
    emActPause,
    emActResume,
};

//�ն�ʹ�ܲ���
enum EmOptRet
{
	emEnable,
	emDisable,
};


//����ģʽ
enum EmConfMode
{
	emP2PConf = 0,//��Ե����
	emMCCConf = 1 //������
};


//��ַ����
enum EmMtAddrType
{
	emIPAddr =0,
	emE164   ,
	emH323id ,
	emDialNum,
	emSipAddr	
};

//����ģʽ
enum EmCallMode
{
	emJoin,
	emCreate,
	emInvite
};


//���Ʒ���
enum EmDirection
{
	emUP   =0,
	emDown   ,
	emLeft   ,
	emRight 
};

//����״̬
enum EmCallState
{
	emCS_Idle  ,
	emCS_Calling ,      //���ڷ������
	emCS_P2P ,      //��Ե����
	emCS_MCC ,      //������
	emCS_Hanup        //�Ҷ�
};


//����״̬
enum EmCallSiteState
{
	emCSS_IDLE,
	emCSS_Init ,
	emCSS_Waiting ,      //���ڷ������
	emCSS_Connected ,      //��Ե����
	emCSS_Failed
};

//����ģʽ
enum EmTransMode
{
	emUnicast,  //����
	emBroadcast, //�㲥
	emMulticast //�鲥
};

//˫��Դ����
enum EmDualSrcType
{
    emDualVGA = 0,
	emDualVideo = 1,
	emDualPC = 2
};



enum EmMtInstType
{
	emMtService = 0 ,
	emMtUI          ,
	emMtConsole     ,
	emMtH323Service ,
	emMtH320Service ,
	emMtSipService  ,
	emMtH323StackIn ,
	emMtH323StackOut,
	emMtMP          ,
	emMtDevice      ,
	emMtAgent       ,
	emMtSipStackIn  ,
	emMtSipStackOut ,
};

//����ϳɷ����
enum EmVMPStyle
{
    emVMPDynamic       =   0 ,  //��̬����(���Զ��ϳ�ʱ��Ч)
    emVMPOne         =   1 ,  //һ����
    emVMPVTwo        =   2 ,  //�����棺���ҷ� 
    emVMPHTwo        =   3 ,  //������: һ��һС
    emVMPThree       =   4 ,  //������
    emVMPFour        =   5 ,  //�Ļ���
    emVMPSix         =   6 , //������ 
    emVMPEight       =   7 ,  //�˻���
    emVMPNine        =   8 ,  //�Ż���
    emVMPTen         =   9 ,  //ʮ����
    emVMPThirteen    =   10,  //ʮ������
    emVMPSixteen     =   11,  //ʮ������
    emVMPSpecFour    =   12,  //�����Ļ��� 
    emVMPSeven       =   13,  //�߻���
	emVMPSpecThirteen  =   14,  //����ʮ�����棨���ڻ�ΪMCU��
	emVMPTwenty      =   15,  //����MPU�Ķ�ʮ���棨ֻ���ڸ���MPU��
};


//����ϳɳ�Ա���Ͷ���
enum EmVMPMmbType
{
    emVMPMmbMCSspec    = 1,  //���ָ�� 
    emVMPMmbSpeaker    = 2,  //�����˸���
    emVMPMmbChairman   = 3,  //��ϯ����
    emVMPMmbPoll       = 4,  //��ѯ��Ƶ����
    emVMPMmbVAC        = 5,	//��������(��ز�Ҫ�ô�����)
};

//����Ϣҵ������
enum EmSMSType//MS
{
	emSMSSingleLine  = 0,  //����Ϣ
	emSMSPageTitle   = 1,  // ��ҳ��Ļ
	emSMSRollTitle   = 2,  // ������Ļ
	emSMSStaticTitle = 3,  // ��̬��Ļ
};


enum EmMtFile
{
    emMtFileBegin  = 0,//�ն��ļ����Ϳ�ʼ
	emMtConfigFile   =1,//�����ļ�
	emMtOldConfigBakFile     ,//�������ļ�����
	emMtDebugConfiFile, //���������ļ�
	emMtCameraCommandFile,//����ͷ�����ļ�
	emMtCameraPresetPostionFile,//����ͷԤ��λ�����ļ�
	emMtExternMaxtrixCommandFile,//���þ����������ļ�
	emMtExternMaxtrixPortNameFile,//���þ���˿����ļ�
	emMtInnerMaxtrixSchemeFile,//���þ��󷽰��ļ�
	emMtStreamMediaHtmlFile,//��ý����ҳ�ļ�
	emMtResourceFile,//�ն���Դ�ļ�
	emMtZipResourceFile,//ѹ���ն���Դ�ļ�
	emMtSymbolFile,//�ն�̨��ͼƬ�ļ�
	emMtBannerFile,//�ն˺���ļ�
	emMtStaticPicFile,//�ն˾�̬ͼƬ�ļ�
	emMtResInBin,//Bin�ļ��е���Դ�ļ�
	emMtAddressBookEx,//��չ��ַ���ļ�
	emMtUpdateSysFile,//�汾�����ļ�
	emMtMinitorFile, //�����ļ�
	emMtZipFile,//Ӧ�ó���
	emMtHintFile,//������ʾ��Դ�ļ�
	emMtKeyFile, //mclicense�ļ�
    emMtInnerPxyFile,//���ô�������������ļ�
	emMtThreadBlockFile,//�߳�������Ϣ�ļ�
	emMtLogFile,//��־�ļ�
	emMtUserWordFile,//�û��ʿ��ļ�
	emMtKdvLog, //��־�����ļ�
	emMtFileEnd //�ն��ļ����ͽ���
};
typedef u32   u32_ip;

enum EmCallRate
{
	emRaten64 = 0,							/*(0)64kbps*/
	emRaten2m64,							/*(1)2��64kbps*/
	emRaten3m64,							/*(2)3��64kbps*/
	emRaten4m64,							/*(3)4��64kbps*/
	emRaten5m64,							/*(4)5��64kbps*/
	emRaten6m64,							/*(5)6��64kbps*/
	emRater384,							/*(6)384kbps*/
	emRater1536,							/*(7)1536kbps*/
	emRater1920,							/*(8)1920kbps*/
	emRater128,							/*(9)128kbps*/
	emRater192,							/*(10)192kbps*/
	emRater256,							/*(11)256kbps*/
	emRater320,							/*(12)320kbps*/
	emRater512,							/*(13)512kbps*/
	emRater768,							/*(14)768kbps*/
	emRater1152,							/*(15)1152kbps*/
	emRater1472,							/*(16)1472kbps*/
	/*(ע��V2.0�汾������3M��4M��6M��8M����)*/
	emRater3M,							/*(17)3M(2880kbps)*/
	emRater4M,							/*(18)4M(3840kbps)*/
	emRater6M,							/*(19)6M(5760kbps)*/
	emRater8M,							/*(20)8M(7680kbps)*/
	emRaterLastOne
};


//PC windows �ɼ���ʽ
enum EmPCCapFormat
{
	emCapPCFrameBMP  = 0,//RGB24λͼ;
	emCapPCFrameUYUY = 1,//yuv4:2:2��ʽ
	emCapPCFrameI420 = 2,//yuv4:2:0��ʽ
};

//���л���ʾģʽ
enum EmPiPMode
{
	emPiPClose   = 0,//���л��ر�
	emPiPRightBottom ,//���л�С������ʾ�����½�
	emPiPLeftBottom  ,//���л�С������ʾ�����½�
	emPiPLeftTop     ,//���л�С������ʾ�����Ͻ�
	emPiPRightTop    ,//���л�С������ʾ�����Ͻ�
};
// DVB Component
enum EmDVBComponent
{
	emDVBEncoder = 0,
	emDVBPriomVideoDecoder,
	emDVBSecondVideoDecoder
};
enum EmUIPosion
{
	emMT = 0,
	emMTC = 1
};
//���йҶ�ԭ��
enum EmCallDisconnectReason
{
	emDisconnect_Busy = 1   ,//�Զ�æ
	emDisconnect_Normal     ,//�����Ҷ�
	emDisconnect_Rejected   ,//�Զ˾ܾ�
	emDisconnect_Unreachable ,//�Զ˲��ɴ�
	emDisconnect_Local       ,//����ԭ��
	emDisconnect_Nnknown      //δ֪ԭ��
};


//MC ��ģʽ
enum EmMCMode
{
	emMcSpeech  ,//�ݽ�ģʽ
	emMcDiscuss ,//����ģʽ
	emMcModeEnd
};


//��Ƕmc�Ļ���ϳɷ��
enum EmInnerVMPStyle
{
    emInnerVMPAuto = 0,
	emInnerVMPOne,
	emInnerVMPTwo,
	emInnerVMPThree,
	emInnerVMPFour,
	emInnerVMPFive,
	emInnerVMPSix,
	emInnerVMPTwoBigLittle,
	emInnerVMPThreeBigLittle,
	emInnerVMPFourBigLittle,
	emInnerVMPEnd
};

//��Ƕmc�Ľ����������
enum EmVMPComponent
{
	emVMPDecNull = 0,
	emVMPDec1th,
	emVMPDec2th,
	emVMPDec3th,
	emVMPDec4th,
	emVMPDec5th,
	emVMPDecLocal,
	emVMPEnd
};


//pcmt��ƵԴ����
enum EmCapType
{
   emAudioOnly = 1, //
   emCameraOnly,
   emACBoth,
   emDesktopOnly,
   emADBoth,
   emFileAVBoth  
};
//pppoe״̬
enum EmPPPoEState
{
	emFree,
	emLinking,
	emLinkup,
	emLinkdown,
	emUserError,
	emTimeOut,
	emAgentError
};

enum EmDhcpState
{
	emDhcpFree,
	emDhcpLinkup,
	emDhcpLinkdown,
};

enum EmAddrGroupOptType
{
    emCallIn,
	emCallOut,
	emUserDef,
	emTemplate,
	emSiteCall,
	emMissed,
	emUserDefExt0,
	emUserDefExt1,
	emUserDefExt2,
	emUserDefExt3,
	emUserDefExt4,
	emUserDefExt5,
	emInvalid
};

enum EmHotKeyType
{
	emApplySpeak,
	emApplyChair,
	emPrevPage,
	emNextPage,
	emBack,
	emLoop,
	emHotkeyEnd,
	emAEC,
	emDial,
};

enum EmMtOSType
{
	emWindows,
    emVxworks,
	emLinux
};

enum EmFxoState
{
    emFxoIdle,
    emFxoCalling, 
    emFxoConnect,
};

// ������������С����
enum EmMtLoudspeakerVal
{
	emLoudspeakerLow = 0,
	emLoudspeakerMiddle,
	emLoudspeakerHigh,
};

// �ش�ʱ��ѡ�����������
enum EmNetType
{
	emInternet = 0,
	emSpecial,
	emVPN,
};

//T2�ն�ϵͳ����״̬��־
enum EmSysRunSuccessFlag
{	
	emSysNoUpdateOperation = 0,
	emSysUpdateVersionRollBack,
	emSysUpdateVersionSuccess,
	emSysSetUpdateFlagFailed,
};

//mcu֪ͨ�ն˵���Ϣ����  
enum EmMcuNtfMsgType
{
	emMsgNoneNtf =0,
	emMsgBePolledNextNtf,
	
};




struct TDATAINFO
{
	//��������
	int type ;
	//�������ʹ�С
	int size ;
	//���ݸ���
	int arraysize;
	//���ݵ�ַƫ����
	int offset;
	//��Ա��������
	char* member;
};

struct TENUMINFO
{
	char* descrip;
	int   val;
};

// �ն�Ӳ���Զ����������� add by wangliang 2007/02/05
enum EmAutoTestType 
{
    emAutoTestTypeBegin,            //�������Ϳ�ʼ
        
    emAutoTestEth0Func,             //����0���ܲ���
	emAutoTestEth1Func,             //����1���ܲ���
	emAutoTestE1Func,               //E1���ܲ���
    emAutoTestAudioLoopBackFunc,    //��Ƶ���ع��ܲ���
    emAutoTestVideoLoopBackFunc,    //��Ƶ���ع��ܲ��� - C����  
	emAutoTestSDI1InAllOutFunc,     //����������ԣ�SDI1����
	emAutoTestSDI2InAllOutFunc,     //����������ԣ�SDI2����
	emAutoTestDVI1InAllOutFunc,     //����������ԣ�DVI1����
	emAutoTestDVI2InAllOutFunc,     //����������ԣ�DVI2����
	emAutoTestDVI3InAllOutFunc,     //����������ԣ�DVI3����
	emAuotTestCInAllOutFunc,        //����������ԣ�C��������
	emAutoTestDVI1InAllOutFunc_YPbPr,    //����������ԣ�DVI1��������
	emAutoTestDVI1InAllOutFunc_OSDYPbPr, //����OSD����������DVI1
	emAutoTestBluerayHDMIFunc,		//����DVD������ӿڽ��ն�HDMI-1�������
	emAutoTestBluerayHDMI2Func,     //����DVD������ӿڽ��ն�HDMI-2�������
	emAutoTestBluerayHDMI3Func,     //����DVD������ӿڽ��ն�HDMI-3�������
	emAutoTestBluerayRCAFunc,       //����DVD������ӿڽ��ն�RCA���������������
	emAutoTestCanonMICFunc,			//��ũMIC����
	emAutoTestDigMICFunc,			//����MIC����
    emAutoTestLoudspeakerFunc,      //���������ܲ���
    emAutoTestCameraRotaFor232Func, //232����ͷת������
	emAutoTestCameraRotaFor485Func, //485����ͷ����
    emAutoTestRTCFunc,              //RTC���ܲ���
    emAutoTestLightFunc,            //ָʾ�Ʋ���
    emAutoTestRemoteCtrlFunc,       //����ӿڹ��ܲ���
    emAutoTestSetDefault,           //�ָ����Ա�־Ĭ��ֵ
	emAutoTestRebootSysFunc,		//�����ն˲���

    emAutoTestTypeEnd               //�������ͽ���
};

enum EmGKRegFailedReason
{
	emNone,
	emGKUnReachable,
	emInvalidAliase,
	emDupAlias,
	emInvalidCallAddress,
	emResourceUnavailable,
	emUnknown
};

enum EmSleepState
{
	emSleepFail, 
	emWaitSleeping,
	emSleeping, 
	emSleeped, 
	emWaking, 
	emWakeup, 
	emWaitWaking
};

enum EmMtAppName
{
	emMtAgentApp = 0,
	emMtServiceApp,
	emMtGuardApp,
	emMtUEApp,
	emMtStackInApp,
	emMtStackOutApp,
	emMtRcpApp,
	emMtH320StackApp,
	emMtRcSimApp,
	emMtMcApp,
	emMtSnmpApp,
	emMtConfigApp,
	emMtUIApp,
	emMtDeviceApp,
	emMtCodecApp,
	emMtConsoleApp,
	emMtSysApp,
	emMtH323ServiceApp,
	emMtH320ServiceApp,
	emMtSipServiceApp,
	emMtDvbApp,
	emMtDvbssnApp,
	emMtVodClientApp,
	emMtPcdualvideoApp,
	emMtUpgradeApp,
	emMtbApp,
	emMtAutotestApp,
	emMtAutotestClientApp,
	emMtRemoteSimApp,
	emMtThreadDetectApp,
	emMtLogRecvApp,
	emMtLogIOApp,
	emMtProxyClientApp,
	emMtSipStackInApp,
	emMtSipStackOutApp,
	emMtSatServiceApp,
	emMtTpRegApp,
	emMtAppEnd = 49,
};

enum HD_PORT_MASK
{
	//PORT_HDMI =  0x01,
	//PORT_SDI =   0x02,
	PORT_SDI =  0x01,
	PORT_HDMI =   0x02,	
	PORT_YPrPb1 = 0x04,
	PORT_YPrPb2 = 0x08,	
	PORT_VGA = 0x10,
	PORT_C0 = 0x20,
};

enum EmHDAudPortIn
{
	emAudInCL  = 0,
	emAudInCR,
	emAudInCanonL,
	emAudInCanonR,
	emAudInHDMI1,
	emAudInHDMI2,
	emAudInHDMI3,
	emAudInMic1,
	emAudInMic2,
};
enum EmHDAudPortOut
{
	emAudOutCCanon  = 0,
	emAudOutHDMI1,
	emAudOutHDMI2,
	emAudOutHDMI3,
	emAudOutReproducer,
};

//��־�Ƿ��
enum EmLogStatus
{
	emLogClose = 0,
		emLogOpen,
};

//��־�������
enum EmLogExportResult
{
	emLogExportFailed = 0,	//ʧ��
	emLogExportSuccess,     //�ɹ�
	emLogExportNoDisk,		//û�в���"U"��
	emLogExportNoFile,		//û����־�ļ�
	emLogExportTransing,	//���豸���ڽ����ļ�����
};

enum EmFecModeType
{
	 emMTFECTYPENONE  =				0x00,
	 emMTFECTYPERAID5 =				0x01,
	 emMTFECTYPERAID5INTERLEAVE =	0x02,
	 emMTFECTYPERAID6 =				0x03,			//������ʱ�������������
};

enum EmLabelPosType
{ 
	emTopLeft      = 0,
	emTopRight     = 1,
	emBottomLeft   = 2,
	emBottomRight  = 3
};

enum EmMtcBoxCallIndex
{
    emShortCutCall1 = 0,
	emShortCutCall2 = 1,
	emShortCutCall3 = 2,
	emShortCutCall4 = 3 
};

enum EmSipRegFailedReason
{
	emLocalNormalUnreg = 0,
	emInvalidUserNameAndPassword,
	emRegistrarUnReachable,
	emInvalidAlias,
	emUnknownReason
};
/*ͨ����״̬*/
enum EMtRecChnnlState
{
	STATE_IDLE       = 0,	  /*������һ��δ��ͨ��*/
		
		STATE_RECREADY   = 11,	  /*׼��¼��״̬  */
		STATE_RECORDING  = 12,	  /*����¼��  */
		STATE_RECPAUSE   = 13,	  /*��ͣ¼��״̬*/
		
		STATE_PLAYREADY  = 21,	  /*׼������״̬ */
		STATE_PLAYREADYPLAY = 22,   /*���ò���׼��״̬*/
		STATE_PLAYING    = 23,	  /*���ڻ򲥷�*/
		STATE_PLAYPAUSE  = 24,	  /*��ͣ����*/
		STATE_FF         = 25,	  /*���(������ͨ����Ч)*/
		STATE_FB         = 26	  /*����(������ͨ����Ч)*/
};

/*ͨ�����Ͷ���*/
enum EMtRecChnnlType
{
	TYPE_UNUSE      =  0,	/*δʼ�õ�ͨ��*/
		TYPE_RECORD     =  1,	/*¼��ͨ��  */   
		TYPE_PLAY       =  2	/*����ͨ��  */
};

//¼��ʽ
enum EMtRecMode
{
	MODE_SKIPFRAME = 0,//��֡¼��
		MODE_REALTIME  = 1  //ʵʱ¼��
};

enum EMtRecEnum{
	MT_MAXNUM_RECORDER_CHNNL = 32,
		MT_MAXLEN_RECORD_NAME = 64,
		MT_MAXLEN_CONFNAME = 64,
		MT_RECLIST_PACKSIZE =16,
		MT_MAX_REC_NAME = 128
};
enum EmMtRegResult
{
	emMtRegSuccess = 1,
	emMtRegPosError,
	emMtRegTimeOut
};
//MTType end.

enum EmTpRet
{
	tp_Ret_FAILED,
	tp_Ret_Success
};


//HDU PLAY NACK�Ĵ���ԭ��
enum EmTpHduPlayNackReason
{
	em_hdu_play_success,
	em_Hdu_Invalid_Index,	//��Ч��λ������
	em_Hdu_Invalid_ID,		//��Ч��ID
	em_Hdu_No_Reged,		//HDUδע��

	em_Hdu_Illegal,			//��Ч��hdu
	em_Alias_Illegal,		//��Ч�ı���
	em_Monitor_Fial,		//��ǽʧ��
	em_Hdu_PlayNack,		//����ǽ�������ܾ�
	em_Same_Alias,			//����
	em_unknown,				//δ֪�Ĵ���


};

//��¼��Ϣ
enum EmTpLoginUmsRet
{
	tp_LoginUms_sucess,
	tp_LoginUms_NameError,	//�û�������
	tp_LoginUms_PwdError,	//�������
	tp_LoginUms_MaxLogin,	//�ﵽ�û���¼����
	tp_LoginUms_Logged,		//�û��Ѿ���¼
	tp_LoginUms_SysIniting,	//ϵͳ���ڳ�ʼ��
	tp_LoginUms_steals_sucess, //���ϳɹ�
	tp_LoginUms_steals_quit,    //��������
};

//��������
enum EmTpAliasType
{
	tp_Alias_Unknow,
	tp_Alias_e164,
	tp_Alias_h323,
	tp_Alias_IP,
};

//��������
enum EmTpOprType
{
	tp_OprType_Add,			//����
	tp_OprType_Del,			//ɾ��
	tp_OprType_Update,		//�޸�
	tp_OprType_NULL,		//���
};

//��ӻ���Ļ᳡
enum EmConfAddEpRet
{
	TP_ConfAddEpRet_Unknow,
	TP_ConfAddEpRet_Success,
	TP_ConfAddEpRet_MaxNum,
	TP_ConfAddEpRet_AliasReapeat,
	TP_ConfAddEpRet_ParamError,
	
};

//�ؼ�֡���
enum EmTpIFrameCheckType
{
    TP_IFrameCheck_Speaker,				//��ⷢ����
	TP_IFrameCheck_SingleSpeaker,		//
	TP_IFrameCheck_Poll,				//��ѯ����
	TP_IFrameCheck_ChairWait,			//��ϯ����ʱ���л������������ˣ���ϯ�ļ��
};

//��������
enum EmTPEncryptType
{
    emTPEncryptTypeNone = 0,
	emTPEncryptTypeDES  = 1,
	emTPEncryptTypeAES  = 2,
};

//�ǶԳ���ʱ�����ն˽��շ���
enum EmTPRcvAlignType
{
	emTPRcvAlignTypeMidAlign,	//�м����
};
//���н��
enum EmCnsCallReason	
{
	EmCnsCallReason_success,
	EmCnsCallReason_hungup,			//���عҶ�
	EmCnsCallReason_Unreachable,	//�Զ˲����ߣ��޷�����
	EmCnsCallReason_resourcefull,	//�Զ��޿�����Դ
	EmCnsCallReason_dstnotfind,		//Ŀ�겻����
	EmCnsCallReason_Busy,			//�Զ�æ
	EmCnsCallReason_Local,			//����ԭ��
	EmCnsCallReason_NoConf,			//���鲻����
	EmCnsCallReason_Exist,			//�Զ����ڱ�������
	EmCnsCallReason_Rejected,		//�Զ˾ܾ�
	EmCnsCallReason_peerhungup,		//�Զ˹Ҷ�
//	EmCnsCallReason_AlreadyDual,    //�Զ���˫��
	EmCnsCallReason_Abnormal,       //���ص��߹Ҷ�
	EmCnsCallReason_PeerAbnormal,   //�Զ˵��߹Ҷ�
	EmCnsCallReason_ConfOver,	//�������
	EmCnsCallReason_cncallexception,	//����ģ��(cncall)����
	EmCnsCallReason_ConfExist,		//�����Ѵ���
	EmCnsCallReason_unknown,  


};

enum EmTPChannelReason
{
	emTPChannelReasonBegin,
	emTPChannelDisconnectNormal,
	emTPDualOffLine,
	emTPForceStop,  //����˫��
	emTPDualNotSend
};


//CNS���ͣ�
enum EmTpCnsType
{
	tp_CnsType_Unkonw,
	tp_CnsType_FiveScreen_FiveSpeeker,
	tp_CnsType_FiveScreen_ThreeSpeeker,
	tp_CnsType_ThreeScreen_ThreeSpeeker,
	tp_CnsType_OneScreen_OneSpeeker,
};


//CNSע��UMSʧ������
enum EmTpCnsRegUms
{
	tp_CnsRegRet_Unknow,
	tp_CnsRegRet_Success,		//�ɹ�
	tp_CnsRegRet_MaxRegNum,		//ע����
	tp_CnsRegRet_MaxAliasNum,	//ע����
	tp_CnsRegRet_MsgError,		//ע����Ϣ����
	tp_CnsRegRet_AliasRepeat,	//�����ظ�
	tp_CnsRegRet_UnReg,			//ɾ��ʱ��δ�ҵ�ɾ����¼
	tp_CnsRegRet_SysError,		//APP����
	tp_CnsRegRet_NotFind,		//����ʧ��
	tp_CnsRegRet_Fail,          //����ʧ��
	tp_CnsRegRet_Unreachable,   //���������ɴ�
	tp_CnsRegRet_UnRegister,    //δע��
	tp_CnsRegRet_E164Repeat,    //E164���ظ�
	tp_CnsRegRet_NameDup,       //������E164�����ظ� 
};



//����ģ��������
enum EmTpConfTemplateRet
{
	TP_ConfTemplate_UnKonw,
	TP_ConfTemplate_AddSuccess,
	TP_ConfTemplate_DelSuccess,
	TP_ConfTemplate_UpdateSuccess,
	TP_ConfTemplate_MaxNum,				//ģ��������������
	TP_ConfTemplate_E164Repeat,			//e164�����ظ�
	TP_ConfTemplate_UnFindConf,			//δ�ҵ���Ŀ
	TP_ConfTemplate_ParamInValid,		//��������
};


//��ʼ������
enum EmTpStartConfRet
{
	TP_StartConf_UnKonw,
	TP_StartConf_Success,
	TP_StartConf_ConfTemplateUnExist,	//����ģ�岻����
	TP_StartConf_ConfFull,				//UMS������
	TP_StartConf_ConfExist,
	TP_StartConf_SipUnReg,				//δע��SIP������
	TP_StartConf_ResourceFull,          //�޿�����Դ
};

enum EmTpApplySpeakerRet
{
	TP_ApplySpeaker_Success,		
	TP_ApplySpeaker_ConfUnExist,		//���鲻����
	TP_ApplySpeaker_EpIDError,			//�᳡������
	TP_ApplySpeaker_EpStateError,		//�᳡δ���߻�ͨ����δ����
};

//�Ҷϻ�����
enum EmTpDropConfRet
{
	TP_DropConf_Success,
	TP_DropConf_ConfUnExit,	//����ģ�岻����
};

//ָ�������˽��
enum EmTpApplySpeakRet
{
	TP_ApplySpeak_UnKonw,
	TP_ApplySpeak_Success,
};

//�����к��н�������״̬
enum EmUmsConfNodeState
{
	ums_UmsConfNodeState_unused,		//δ��
	ums_UmsConfNodeState_uncall,		//������У���δ��ʼ����
	ums_UmsConfNodeState_calling,		//���ں�����...
	ums_UmsConfNodeState_callfailed,	//����ʧ��
	ums_UmsConfNodeState_online,		//����
	ums_UmsConfNodeState_stopcall,		//ֹͣ����
};


enum EmFlowCtrlOpr	//flowctrl�Ĳ���
{
	emFlowCtrl_Speaker  = 1	,
	emFlowCtrl_Chair	= 2	,
	emFlowCtrl_Poll		= 4	,
	emFlowCtrl_TvWall	= 8	,
	emFlowCtrl_View		= 16,
};

//��������
enum EMBrdType
{
	em_unknow_brd,
	em_eapu_brd,
	em_mpc_brd,
	em_mpu2ecard_brd,
	em_hdu2_brd,
	em_is22_brd,
	em_cri2_brd,
};

//��������
enum EMEqpType
{
	em_unknow_mdl,
		em_adapter_mdl,
		em_dataswitch_mdl,
		em_netbuf_mdl,
		em_audmix_mdl,
		em_mpc_mdl,
		em_bas_mdl,
		em_vmp_mdl,
		em_hdu_mdl,
		em_regserver_mdl,
		em_recorder_mdl,

		em_max_mdl = 15,
};

//����ģʽ
enum EMEqpModleType
{
	em_unknow_eqp_mdl,
	em_bas_basic_eqp_mdl,
	em_bas_enhanced_eqp_mdl,
	em_vmp_basic_eqp_mdl,
	em_vmp_enhanced_eqp_mdl,
};

//ϵͳ����
enum EMOsType
{
	em_unknow_OsType,
	em_Win32_OsType,
	em_Linux_OsType,
	em_82xx_OsType,
	em_85xx_OsType,
};

enum EMVmpStyle
{
	tp_VmpStyle_DYNAMIC = 0,	//��̬����(���Զ��ϳ�ʱ��Ч)	0
	tp_VmpStyle_ONE,			//һ����						1
	tp_VmpStyle_VTWO,			//�����棺���ҷ�				2
	tp_VmpStyle_HTWO,			//������: һ��һС				3
	tp_VmpStyle_THREE,			//������						4
	tp_VmpStyle_FOUR,			//�Ļ���						5
	tp_VmpStyle_SIX,			//������						6
	tp_VmpStyle_EIGHT,			//�˻���						7
	tp_VmpStyle_NINE,			//�Ż���						8
	tp_VmpStyle_TEN,			//ʮ����						9
	tp_VmpStyle_THIRTEEN,		//ʮ������						10
	tp_VmpStyle_SIXTEEN,		//ʮ������						11
	tp_VmpStyle_SPECFOUR,		//�����Ļ���					12
	tp_VmpStyle_SEVEN,			//�߻���						13
	tp_VmpStyle_TWENTY,			//��ʮ����						14
	tp_VmpStyle_TEN_H,			//ˮƽ�ָ��ʮ����(��2��8)		15
	tp_VmpStyle_SIX_L2UP_S4DOWN,	//����������(��2��4)		16
	tp_VmpStyle_FOURTEEN,			//ʮ�Ļ���					17
	tp_VmpStyle_TEN_M,				//ʮ����(��4��2��4)			18
	tp_VmpStyle_THIRTEEN_M,			//ʮ������(һ�����м�)		19
	tp_VmpStyle_FIFTEEN,			//ʮ�廭��					20
	tp_VmpStyle_SIX_DIVIDE,			//������(�ȷ�)				21
	tp_VmpStyle_leftBig,			//�����棬2��С���ڵײ�����	22
	tp_VmpStyle_MidBig,				//�����棬2��С���ڵײ�����	23
	tp_VmpStyle_RightBig,			//�����棬2��С���ڵײ�����	24
	tp_VmpStyle_3VERTICAL,			//�����棬��ֱ�ȴ�			25
	tp_VmpStyle_FOUR_3BOTTOMMIDDLE,	//�Ļ��棬3���ڵײ�����		26
	tp_VmpStyle_TWENTYFIVE,			//��ʮ�廭��				27
};


//==============����ΪCNSʹ��type==============//


//��ƵЭ������
enum EmTpVideoFormat
{
    emTPVH261     = 0,
		emTPVH262     = 1,//MPEG2
		emTPVH263     = 2,
		emTPVH263plus = 3,
		emTPVH264     = 4,
		emTPVMPEG4    = 5,
		
		emTPVEnd		
};
//���뷽ʽ
enum EmTpEncodeMode
{
    emTPQualityFirst  = 0, 
		emTPSpeedFirst    = 1,
		
};

//H.264��ʽ���ʼ���
enum EmTpVideoQualityLevel
{
	emTPH264BP = 0,  //BP����
	emTPH264HP = 1,  //HP����
};

//�ֱ�������
enum EmTpVideoResolution
{
    emTPVResolutionAuto     = 0,   //�Զ�
		emTPVSQCIF              = 1,   //SQCIF88x72
		emTPVQCIF               = 2,   //QCIF176x144
		emTPVCIF                = 3,   //CIF352x288
		emTPV2CIF               = 4,   //2CIF352x576
		emTPV4CIF               = 5,   //4CIF704x576
		emTPV16CIF              = 6,   //16CIF1408x1152
		
		emTPVHD480i720x480      = 7,   //480i720x480
		emTPVHD480p720x480      = 8,   //480p720x480
		emTPVHD576i720x576      = 9,   //576i720x576
		emTPVHD576p720x576      = 10,  //576p720x576
		
		emTPVHD720p1280x720     = 11,  //720p1280x720
		emTPVHD1080i1920x1080   = 12,  //1080i1920x1080
		emTPVHD1080p1920x1080   = 13,  //1080p1920x1080
		
		
		emTPVGA352x240          = 14,  //352x240
		emTPVGA704x480          = 15,  //704x480
		emTPVGA640x480          = 16,  //VGA640x480
		emTPVGA800x600          = 17,  //SVGA800x600
		emTPVGA1024x768         = 18,  //XGA1024x768
		emTPVGA1280x768         = 19,  //WXGA1280x768
		emTPVGA1280x800         = 20,  //WXGA1280x800
		emTPVGA1366x768         = 21,  //WXGA1366x768
		emTPVGA1280x854         = 22,  //WSXGA1280x854
		emTPVGA1440x900         = 23,  //WSXGA1440x900
		emTPVGA1280x1024        = 24,  //SXGA1280x1024
		emTPVGA1680x1050        = 25,  //SXGA+1680x1050
		emTPVGA1600x1200        = 26,  //UXGA1600x1200
		emTPVGA1920x1200        = 27,  //WUXGA1920x1200
		
		emTPVSQCIF112x96        = 28,
		emTPVSQCIF96x80         = 29,
		emTPV320x192            = 30,
		emTPV432x240            = 31,
		emTPV480x272            = 32,
		emTPV640x368            = 33,
		emTPV864x480            = 34,
		emTPV960x544            = 35,
		emTPV1440x816           = 36,
		
		emTPVResEnd = 50,
};

// ý������
enum EmTpMediaType
{
	emTPMediaVideo = 1, //��Ƶ
	emTPMediaAudio = 2, //��Ƶ
	emTPMediaAV    = 3 //��Ƶ����Ƶ
};

//PC windows �ɼ���ʽ
enum EmTpPCCapFormat
{
	emTPCapPCFrameBMP  = 0,//RGB24λͼ;
		emTPCapPCFrameUYUY = 1,//yuv4:2:2��ʽ
		emTPCapPCFrameI420 = 2,//yuv4:2:0��ʽ
};

//���������������
enum EmTpCodecComponent
{
	emTPPriomVideoEncoder  =0,
		emTPPriomVideoDecoder  ,
		
		emTPSecondVideoEncoder ,
		emTPSecondVideoDecoder ,
		
		emTPAudioEncoder ,
		emTPAudioDecoder ,

		emTPSecondAudioEncoder ,
		emTPSecondAudioDecoder ,

		emTPPriomLeftVideoDecoder,
		emTPPriomRightVideoDecoder,

		emTPCodecComponentEnd,

};

//��ƵЭ������
enum EmTpAudioFormat
{
    emTPAG711a  = 0,
		emTPAG711u  = 1,
		emTPAG722   = 2,
		emTPAG7231  = 3,
		emTPAG728   = 4,
		emTPAG729   = 5,
		emTPAMP3    = 6,
		emTPAG721   = 7,
		emTPAG7221  = 8,
		emTPAG719   = 9,
		emTPAMpegAACLC =10,
		emTPAMpegAACLD = 11,
		
		emTPAEnd	 
};
//�����ָ�����
enum EmTpLostPackageRestore
{
    emTPLPQualityFirst  = 0, 
		emTPLPSpeedSlow     = 1,
		emTPLPSpeedNormal   = 2,
		emTPLPSpeedFast     = 3,
};
enum EmTpCallMode
{
	emTpJoin,
		emTpCreate,
		emTpInvite
};
enum EmTpConnectionType
{
	emTPConnectionBegin = 0,
	emTPTCPConnection,
	emTPUDPConnection,
};
enum EmTpConfProtocol
{
	emTpInvalidConfProtocel = 0,
	emTpH323, 
	emTpH320,
	emTpSIP,
	emTpSat
};


enum EmTPAddrType
{
	emTpUnknown =0,
	emTpIPAddr, 
	emTpDomain,
	emTpAlias,
	emTpE164Num,
	emTpIP6Addr,
};
enum EmTPEndpointType
{
	emTPEndpointTypeUnknown  = 0,
	emTPEndpointTypeCNS	     = 0x01,
	emTPEndpointTypeUMS		 = 0x02,
	emTPEndpointTypeRegister,
	emTPEndpointH323MT,
	emTPEndpointH323MCU,
	emTPEndpointH323SingleMCU,
	emTPEndpointH323G400,
};
enum EmTPSipLevel
{
	emTPSipCounty,
	emTPSipCity,
	emTPSipProvince,
	emTPSipUnKnown = 255,
};

//����״̬
enum EmCALLSTATE
{
	em_CALL_IDLE    = 0,  
	em_CALL_CALLING,
	em_CALL_CONNECTED
};

//�������ͣ�CNS֪ͨCMC
enum EmCallType
{
	emCallType_Invalid = 0,
	emCallType_P2P,
	emCallType_Conf
};

enum EmTPVideoType
{
	emTpPriomVideo = 0 ,//����Ƶ
	emTpMiniVideo = 1 //С����
};


//�ն���Ƶ�˿�
enum EmTPVideoPort
{
	//hd2.0��ƵԴ����
	emTpVGA   =0 , //VGA 
	emTpSVid    , //S ����
	emTpPC      , //PC
	emTpC1Vid   ,  //C1����   DVI 1
	emTpC2Vid   ,  //C2����   DVI 2
	emTpC3Vid   ,  //C3����   DVI 3
	emTpC4Vid   ,  //C4����   c
	emTpC5Vid   ,  //C5����   sdi 1
	emTpC6Vid   ,  //C6����   sdi 2
		
	emTpExternalVid = 10,//���þ���ӳ���ʼֵ
	emTpVideoMaxCount = 74, //���֧����ƵԴ����
	emTpVidInvalid = 255 
};

enum EmTPCNSInfoRst
{
	emTPCNSInfoSuccess = 1,			//�ɹ�
	emTPCNSRepeatE164,				//E164����
	emTPCNSRepeatAliasName,			//�᳡���ظ�

};


enum EmTPRegResult
{
	emTPRegResultBegin = 0,
	emTPRegResultReg,
	emTPRegResultUnReg
};

enum EmCnMtRegResult
{
	emCnMtSuccess = 1,
	emCnMtPosError,
	emCnMtTimeOut
};

//Add��������type
//�ն��ͺ�
enum EmCnModel
{
	emUnknownCnModel=0,
	em7920,	
	T300,
	Moon90	
};

//�۽�ģʽ
enum EmFocusMode
{
	emFocusAuto,
	emFocusManuel
};

//�۽�
enum EmFocus
{
	emFar ,
    emNear
};

//��Ұ
enum EmZoom
{
	emTele,
    emWide
};

//����
enum EmCnAction
{
    emCnStart,
	emCnStop,
};

//����� OSD ��ʾ
enum EmOSDShow
{
	emOSDOff = 0x00,
	emOSDOn ,
};

//��ƽ��ģʽ
enum EmWBMode
{
	emWBAuto = 0x00,
	emWBManual,
	emOnePush
};

//�ع�ģʽ
enum EmExpMode
{
	emExpAuto = 0x00,
	emExpManuel
};

//����� �ع�--����
enum EmGain
{
	em0dB = 0x00,
	em3dB = 0x01,
	em6dB = 0x02,
	em9dB  ,
	em12dB ,
	em15dB ,
	em18dB ,
	em21dB ,
	em24dB ,
	em27dB ,
	em30dB ,
	em33dB ,
	em36dB ,
	em39dB ,
	em42dB = 0x0e,
};

//�����  �ع�--����
enum EmShutSpd
{
	emShutSpd0  = 0x00,  // 1/60
	emShutSpd1  = 0x01,  // 1/120
	emShutSpd2  = 0x02,  // 1/250
	emShutSpd3 ,         // 1/500
	emShutSpd4 ,         // 1/1000
	emShutSpd5 ,         // 1/2000
	emShutSpd6 ,         // 1/4000
	emShutSpd7 ,         // 1/10000
};

//����� �ع�--����
enum EmBackLightType
{
	emBLOff    = 0x00,
	emBLmulti,
	emBLcenter,
	emBLfacedetect,
		
	emBLAuto,
};

//����� ����ģʽ
enum EmPicSceMode
{
	emLamp   = 0x00,  
	emSun    = 0x01,  
	emManuel = 0x02,
};

//����� �ֶ�ģʽ GAMMA
enum EmGamma
{
	emGammaOff  = 0x00,
	emGammaOn   = 0x01,
	emSmart1,
	emSmart2,
};

//���� ���������� ��Χ
enum EmStmClean
{
    emNRoff  = 0x00,
	emNRlow  ,
	emNRmid  ,
	emNRhigh
};

enum Em3DNR
{
	em3DNROff  = 0x00,
	em3DNROn
};

enum EmCamPowerMode
{
	emCamPowerOn,   //�ϵ�
	emCamPowerOff,  //����
	emCamPowerDowm, //�ϵ�
};

enum EmCenSchMode
{
	emSchSleep,   //����
	emSchWakeup,  //����
};

//end


//�п�ģ��
//���ӻ���Դģʽ
enum EmTvPowerMode
{
	emTVPowerOFF,
	emTVPowerON,
	emTVPowerDown
};

//���ӻ��ϵ�ǰ��Դģʽ
enum EmTvSrcPowerMode
{
	emTVSrcPowerOFF,
		emTVSrcPowerON,
};

//���ӻ�����ģʽ
enum EmTVAudVisMode
{
	emTVAVStandardMode = 0,   //��׼
		emTVAVMovieMode,          //��Ӱ
		emTVAVUserMode,           //�û�
		emTVAVComputerMode        //����
};


//���ӻ���ʾģʽ
enum EmTVDisplayMode
{
	emTVDisFullScrMode  = 0,  //ȫ��
		emTVDisPanoramaMode,      //ȫ��
		emTVDisPointMode,         //���
		emTVDisStandardMode       //��׼
};

//���ӻ�����ѡ�� 
enum EmTVInputSelect
{
	emTVHDMI1  = 0,
		emTVHDMI2,
		emTVHDMI3,
		emTVHDMI4,
		emTVYpbPr,
		emTVCVBS1,
		emTVCVBS2,
		emTVComputer
};

//�ĵ�����ͷ��ƽ��ģʽ 
enum EmDCamWBMode
{
	emDcamWBAuto = 0x00,
	emDCamWBManual,
	emDCamOnePush,
	emDCamWBInvalid
};

//�ĵ�����ͷ�Զ��۽�ģʽ
enum EmDCamAFMode
{
	emDcamAFOff = 0x00,
	emDCamAFOn,
	emDCamAFToggle,
	emDCamAFInvalid
};

//�ĵ�����ͷ��������
enum EmDCamPower
{
	emDCamPowerOff = 0x00,
	emDCamPowerOn,
	emDCamPowerToggle,
	emDCamPowerDown,
	emDCamPowerInvalid
};

//�ĵ�����ͷ��Ұ����
enum EmDCamZoom
{
    emDCamZoomWide = 0x00,
	emDCamZoomTele,
	emDCamZoomInvalid
};

//�����ĵ�����ͷԤ��λ���
enum EmDCamPresetNum
{
	emDCamPresetOne = 0x00,
	emDCamPresetTwo,
	emDCamPresetThree,
	emDCamPresetInvalid
};

//�����ĵ�����ͷԤ��λ���
enum EmDCamRecallNum
{
	emDCamRecallOne = 0x00,
	emDCamRecallTwo,
	emDCamRecallThree,
	emDCamRecallInvalid
};

//������ϵͳ��Դ����
enum EmSchPower
{
	emSchPowerOff = 0x00,
	emSchPowerOn,
	emSchPowerToggle,
	emSchPowerInvalid
};

//�����ҵƹ��Դ����
enum EmSchLight
{
	emSchLightOff = 0x00,
	emSchLightOn,
	emSchLightInvalid
};

//�����Ҷ��ϵƹ��Դ����
enum EmSchMidLight
{
	emSchMidLightOff = 0x00,
	emSchMidLightOn,
	emSchMidLightInvalid
};

//�����һ���ƹ��Դ����
enum EmSchScrLight
{
	emSchScrLightOff = 0x00,
	emSchScrLightOn,
	emSchScrLightInvalid
};



//�����������Ӧ�����������
enum EmSchArgus
{
	emSchArgusUnlock = 0x00,
	emSchArgusLock,
	emSchArgusInvalid
};

//�пؿյ�ģʽ add by zhangapei
enum EmCentreACPower
{
	emCenACPowerOff,
	emCenACPowerOn,
};

//�յ��·����
enum EmCentreACAirVol
{
	emCenACVolAuto,  //�Զ�
	emCenACVol1,    
	emCenACVol2,     
	emCenACVol3,    
	emCenACVol4,  
	emCenACVol5,     
};

//�յ�ģʽ
enum EmCentreACMode
{
	emCenACBlowIn,  //�ͷ�
	emCenACheat,    //����
	emCenAcref,     //����
	emCenACAuto,    //�Զ�
	emCenACChaAir,  //����
	emCenACdeh,     //��ʪ
};


//������������
enum EmCurAction
{
	emCurUp,
	emCurDown,
	emCurStop,
};

//��������ͨ·ģʽ
enum EmCurChannelMode
{
	emCurChanFirst = 1,
	emCurChanSecond,
	emCurChanFirASec,
	emCurChanThird,
	emCurChanFirAThi,
	emCurChanSecAThi,
};

enum EmSchGatewayType
{
	emGatewayOld,
	emGatewayNew,
};

//end add

//�п� end

//==============����ΪCNSʹ��type==============//

enum EmTpMixStatus
{
	emAudMixIdle,
	emAudOpenChan_Fail,		//������ͨ��ʧ��
	emAudOpenChan_Success    //������ͨ���ɹ�
};

enum EmTPDualReason
{
	emTpDualAccept,
		emTpDualBusy,
		emTpDualPreemptive,
		emTpDualPeerReject,
		emTpDualPeerStop,
		emTpDualNoVideo,
		emTpDualLocalStop,
		emTpDualSndFail,       //����˫��ʧ��
		emTpDualInit           //˫����ʼ����
};

enum  EmTPPayloadType 
{
	emTpPayloadTypeBegin = 0,
		//��Ƶ��ʽ
		emTpAudioTypeBegin,
		emTpG711a,
		emTpG711u,
		emTpG722,
		emTpG7231,
		emTpG728,
		emTpG729,
		emTpMp3,  
		emTpG723,
		emTpG7221,
		emTpMpegaaclc,
		emTpMpegaacld,
		emTpG719,
		emTpAudioTypeEnd = 49,
		
		//��Ƶ��ʽ
		emTpVideoTypeBegin = 50,	
		emTpH261,
		emTpH263,
		emTpH263plus,
		emTpH264,
		emTpH262,
		emTpMpeg4,
		emTpVideoTypeEnd = 99,
        
		emTpDataTypeBegin = 100,	
		emTpT120,
		emTpH224,
		emTpDataTypeEnd = 149,
		
		emTpPayloadTypeEnd = 255
};

enum EmTPPosStatus
{
	emPosInAcitve = 0,
	emPosAcitve
};

enum EmTPPollResult
{
	emPollSucceed = 0,
	emPollFailUnKown = 1,
	emPollInvalidEp = 2,	//����Ч��ѵ�᳡
};

enum EmTPViewResult
{
	emViewSucceed = 0,
	emViewFailUnKown,
	emViewFailStatusError,
	emViewFailOffline,			//�Զ˲�����
	emViewFailNotChair,			//�����ⲻ�����᳡
	emViewFailNoResource,		//û����Դ
	emViewFailDstNoVid,			//Ŀ������Ƶ
	emViewRequesting,			//�����У���ȴ�
};


enum EmTPViewLocalResult
{
	emViewLocalSucceed = 0,
	emViewLocalFailUnKown,
	emViewLocalFailStatusError,       //״̬����ȡ��ʱ��ʾ��ǰ������VIEW LOCAL��ѡ��ʱ��ʾ���ڿ�����״̬
	emViewLocalFailOffline,
	emViewLocalFailIllegalPos
};

enum EmTPDisOprType
{
	emDisOprType_Idle,
	emDisOprType_StartAll,
	emDisOprType_AddChnl,
	emDisOprType_ChangeSeat,
	emDisOprType_RemoveChnl,
	emDisOprType_DisConnectChnl
};

enum EMPosPic
{
	emPic_Invalid = 0,
		emPic_Local,				//����
		emPic_Static,				//��̬ͼƬ
		emPic_Speaker,				//������
		emPic_Dual,					//˫��
		emPic_Poll,					//��ѯ
		emPic_SelView,              //ѡ��Զ�� 
		emPic_SelDual,              //ѡ��˫��
		emPic_SelLocal,             //ѡ������
		emPic_Discuss,             //����
		emPic_SelTVS               //ѡ������ǽ
};

enum EMDSCREATETYPE
{
	emDS_CreateType_Invalid = 0,
	emDS_CreateType_SndBoundary,
	emDS_CreateType_RcvBoundary,
	emDS_CreateType_SndAndRcvBoundary,
	emDS_CreateType_NotBoundary,
};

enum EmTPAddDualRcvResult
{
	emAddDualRcvSucceed = 0,
	emAddDualRcvFailNoDual,       //û����˫��
	emAddDualRcvFailIllegalPos,   //�Ƿ�λ��
	emAddDualRcvFailNoPos,        //û�п���λ����
	emAddDualRcvFailStatusError,  //��ǰ�Ѿ���˫��״̬��
	emAddDualRcvFailUnKown,
};

enum EmTPDeleteDualRcvResult
{
	emDeleteDualRcvSucceed = 0,
	emDeleteDualRcvFailNoDual,       //û����˫��
	emDeleteDualRcvFailIllegalPos,   //�Ƿ�λ��
	emDeleteDualRcvFailUnKown,
};

enum EmTPMtModel
{
	emTPUnknownMtModel=0,
		emTPPCMT  =1    ,//�����ն�
		emTP8010      ,
		emTP8010A     ,
		emTP8010Aplus ,//8010A+
		emTP8010C     ,
		emTP8010C1    ,//8010C1
		emTPIMT       ,
		emTP8220A     ,
		emTP8220B     ,
		emTP8220C     ,
		emTP8620A     ,
		emTPTS6610E   ,
		emTPTS6210    ,
		emTP8010A_2   ,
		emTP8010A_4   ,
		emTP8010A_8   ,
		emTP7210      ,
		emTP7610      ,
		emTPTS5610    ,
		emTPTS6610    ,
		emTP7810      ,
		emTP7910      ,
		emTP7620_A    ,
		emTP7620_B    ,
		emTP7820_A	,
		emTP7820_B	,
		emTP7920_A	,
		emTP7920_B	
		
};

enum EmDsType
{
	em_DsType_Invalid = 0,

		
		//Э�� �ⲿ�˿�
		em_Ds_Remote_ASnd_0 ,
		em_Ds_Remote_ASnd_1,
		em_Ds_Remote_ASnd_2,
		
		em_Ds_Remote_ARcv_0,
		em_Ds_Remote_ARcv_1,
		em_Ds_Remote_ARcv_2,
		
		em_Ds_Remote_VSnd_0,
		em_Ds_Remote_VSnd_1,
		em_Ds_Remote_VSnd_2,
		
		em_Ds_Remote_VRcv_0,
		em_Ds_Remote_VRcv_1,
		em_Ds_Remote_VRcv_2,
		
		em_Ds_Remote_VSnd_0_Mini_0,
		em_Ds_Remote_VSnd_1_Mini_0,
		em_Ds_Remote_VSnd_2_Mini_0,
		
		em_Ds_Remote_VRcv_0_Mini_0,
		em_Ds_Remote_VRcv_0_Mini_1,
		em_Ds_Remote_VRcv_1_Mini_0,
		em_Ds_Remote_VRcv_1_Mini_1,
		em_Ds_Remote_VRcv_2_Mini_0,
		em_Ds_Remote_VRcv_2_Mini_1,
		
		
		em_Ds_Remote_Mix_Snd,
		em_Ds_Remote_Mix_Rcv,

		em_Ds_RemoteDual_ASnd,
		em_Ds_RemoteDual_VSnd,
		
		em_Ds_RemoteDual_ARcv,
		em_Ds_RemoteDual_VRcv,


		//������Э��ջ����
		em_Ds_VirRemote_ASnd_0 ,
		em_Ds_VirRemote_ASnd_1,
		em_Ds_VirRemote_ASnd_2,
		
		em_Ds_VirRemote_ARcv_0,
		em_Ds_VirRemote_ARcv_1,
		em_Ds_VirRemote_ARcv_2,
		
		em_Ds_VirRemote_VSnd_0,
		em_Ds_VirRemote_VSnd_1,
		em_Ds_VirRemote_VSnd_2,
		
		em_Ds_VirRemote_VRcv_0,
		em_Ds_VirRemote_VRcv_1,
		em_Ds_VirRemote_VRcv_2,

		em_Ds_VirRemote_VSnd_0_Mini_0,
		em_Ds_VirRemote_VSnd_1_Mini_0,
		em_Ds_VirRemote_VSnd_2_Mini_0,
		
		em_Ds_VirRemote_VRcv_0_Mini_0,
		em_Ds_VirRemote_VRcv_0_Mini_1,
		em_Ds_VirRemote_VRcv_1_Mini_0,
		em_Ds_VirRemote_VRcv_1_Mini_1,
		em_Ds_VirRemote_VRcv_2_Mini_0,
		em_Ds_VirRemote_VRcv_2_Mini_1,

		
		em_Ds_VirRemote_Mix_Snd,
		em_Ds_VirRemote_Mix_Rcv,
		
		em_Ds_VirRemote_End = 100,

		em_Ds_MT_ASnd_0,
		em_Ds_MT_ASnd_1,
		em_Ds_MT_ASnd_2,
		em_Ds_MT_ASnd_3,
		
		em_Ds_MT_ARcv_0,
		em_Ds_MT_ARcv_1,
		em_Ds_MT_ARcv_2,
		em_Ds_MT_ARcv_3,
		
		em_Ds_MT_VSnd_0,
		em_Ds_MT_VSnd_1,
		em_Ds_MT_VSnd_2,
		em_Ds_MT_VSnd_3,
		
		em_Ds_MT_VRcv_0,
		em_Ds_MT_VRcv_1,
		em_Ds_MT_VRcv_2,
		em_Ds_MT_VRcv_3,
		
		em_Ds_MT_VSnd_0_Mini_0,
		em_Ds_MT_VSnd_1_Mini_0,
		em_Ds_MT_VSnd_2_Mini_0,
		
		em_Ds_MT_VRcv_0_Mini_0,
		em_Ds_MT_VRcv_0_Mini_1,
		em_Ds_MT_VRcv_1_Mini_0,
		em_Ds_MT_VRcv_1_Mini_1,
		em_Ds_MT_VRcv_2_Mini_0,
		em_Ds_MT_VRcv_2_Mini_1,
		
		em_Ds_Mt_Mix_ASnd,//mt�����˿�

		//���ں��ն˽���  Ŀǰ��ʹ��
		em_Ds_VirMt_ASnd_0,
		em_Ds_VirMt_ASnd_1,
		em_Ds_VirMt_ASnd_2,
		
		em_Ds_VirMt_ARcv_0,
		em_Ds_VirMt_ARcv_1,
		em_Ds_VirMt_ARcv_2,
		
		em_Ds_VirMt_VSnd_0,
		em_Ds_VirMt_VSnd_1,
		em_Ds_VirMt_VSnd_2,
		
		em_Ds_VirMt_VRcv_0,
		em_Ds_VirMt_VRcv_1,
		em_Ds_VirMt_VRcv_2,

		em_Ds_VirMt_VSnd_0_Mini_0,
		em_Ds_VirMt_VSnd_0_Mini_1,
		em_Ds_VirMt_VSnd_1_Mini_0,
		em_Ds_VirMt_VSnd_1_Mini_1,
		em_Ds_VirMt_VSnd_2_Mini_0,
		em_Ds_VirMt_VSnd_2_Mini_1,
		
		em_Ds_VirMt_VRcv_0_Mini_0,
		em_Ds_VirMt_VRcv_0_Mini_1,
		em_Ds_VirMt_VRcv_1_Mini_0,
		em_Ds_VirMt_VRcv_1_Mini_1,
		em_Ds_VirMt_VRcv_2_Mini_0,
		em_Ds_VirMt_VRcv_2_Mini_1,

		em_Ds_VirMt_Mix_ASnd,
	

		em_Ds_Mt_End = 200,


		em_Ds_Innerspeaker_ASnd,
		em_Ds_Innerspeaker_VSnd,
		
		em_Ds_Innerspeaker_End = 210 ,
		
		em_Ds_VirDual_ASnd,
		em_Ds_VirDual_VSnd,
		
		em_Ds_VirDual_ARcv,//˫����Ϊ�����ݲ�ʹ��
		em_Ds_VirDual_VRcv,//˫����Ϊ�����ݲ�ʹ��
		
		//�����ַ
		em_Ds_VirDual_Adapter_VSnd,
		em_Ds_MtDual_Adapter,		

		em_Ds_Dual_End = 250,

		em_Ds_Addr_Type_End = 300,


		//���²���Ҫ����˿�
		em_DsOtherType_Begin,
		
		em_Ds_VirMtToInnerspeaker_ASnd_0,
		em_Ds_VirMtToInnerspeaker_ASnd_1,
		em_Ds_VirMtToInnerspeaker_ASnd_2,
		
		em_Ds_VirMtToInnerspeaker_VSnd_0,
		em_Ds_VirMtToInnerspeaker_VSnd_1,
		em_Ds_VirMtToInnerspeaker_VSnd_2,
		
		em_Ds_DualRcvToVirMt_Rcv_0,
		em_Ds_DualRcvToVirMt_Rcv_1,
		em_Ds_DualRcvToVirMt_Rcv_2,

		em_Ds_VirRemoteToVirMt_ASnd_0,
		em_Ds_VirRemoteToVirMt_ASnd_1,
		em_Ds_VirRemoteToVirMt_ASnd_2,

		em_Ds_VirRemoteToVirMt_VSnd_0,
		em_Ds_VirRemoteToVirMt_VSnd_1,
		em_Ds_VirRemoteToVirMt_VSnd_2,

		em_Ds_VirRemoteToVirMt_ARcv_0,
		em_Ds_VirRemoteToVirMt_ARcv_1,
		em_Ds_VirRemoteToVirMt_ARcv_2,
		
		em_Ds_VirRemoteToVirMt_VRcv_0,
		em_Ds_VirRemoteToVirMt_VRcv_1,
		em_Ds_VirRemoteToVirMt_VRcv_2,

		em_Ds_VirDualNB_VRcv,
		em_Ds_VirDualNB_VSnd,

		em_Ds_VirDualNB_ARcv,
		em_Ds_VirDualNB_ASnd,

		em_Ds_VirRemoteToVirMt_VRcv_0_Mini_0,
		em_Ds_VirRemoteToVirMt_VRcv_0_Mini_1,
		em_Ds_VirRemoteToVirMt_VRcv_1_Mini_0,
		em_Ds_VirRemoteToVirMt_VRcv_1_Mini_1,
		em_Ds_VirRemoteToVirMt_VRcv_2_Mini_0,
		em_Ds_VirRemoteToVirMt_VRcv_2_Mini_1,

		em_Ds_VirRemoteToVirMt_Mix_ASnd,
		
		em_Ds_VirRemoteToPad_VSnd,
		em_Ds_VirRemoteToPad_ASnd,

		em_Ds_VirDual_ARcv_Pad_Begin = em_DsOtherType_Begin+1000,
		em_Ds_VirDual_ARcv_Pad_End = em_Ds_VirDual_ARcv_Pad_Begin+20,
		em_Ds_VirDual_VRcv_Pad_Begin,
		em_Ds_VirDual_VRcv_Pad_End = em_Ds_VirDual_VRcv_Pad_Begin+20,

		em_Ds_VirDual_VSnd_Pad,
		

		em_Ds_Debug = 1010,
		
};

enum EmCnAudioMixID
{
	emCnAMix_INVALID,
	emCnAMix_Speaker,    //3��1�������˻�����
	emCnAMix_Dual,       //˫��������
};

enum EmGetRegInfoType
{
	emGetRegInfoType_CNS = 0,
	emGetRegInfoType_UMS,
	emGetRegInfoType_ALL,
	emGetRegInfoType_MT,
	emGetRefInfoType_MCU,
};

enum EmGetRegInfoOpr
{
	emGetRegInfoOpr_Update = 0,//ˢ��
	emGetRegInfoOpr_Add,//����
};

enum EmTPChanType
{
	emTPChanNone,
	emTPChanRecv,
	emTPChanSend,
	emTPChanSendRecv,
	emTPChanTypeEnd = 10,
};

enum EmTPAACSampleFreq                    //sampling frequency
{
	emTPFs96000 = 0,
        emTPFs88200 = 1,
        emTPFs64000 = 2,
        emTPFs48000 = 3,
        emTPFs44100 = 4,
        emTPFs32000 = 5,
        emTPFs24000 = 6,
        emTPFs22050 = 7,
        emTPFs16000 = 8,
        emTPFs12000 = 9,
        emTPFs11025 = 10,
        emTPFs8000  = 11
};

enum EmTPG7221Rate
{
	emTPG7221Rate24   =  0x01,
	emTPG7221Rate32   =  0x02,
	emTPG7221Rate48   =  0x04
};


enum EmTPAACChnlCfg                       //channel config
{
	emTPChnlCust   = 0,
        emTPChnl1      = 1,                   //������
        emTPChnl2      = 2,                   //˫����
        emTPChnl3      = 3,
        emTPChnl4      = 4,
        emTPChnl5      = 5,
        emTPChnl5dot1  = 6,                   //5.1����
        emTPChnl7dot1  = 7                    //7.1����
};

enum EmTPTpApplySpeakerRet
{
	emTP_ApplySpeaker_Success,  
	emTP_ApplySpeaker_ConfUnExist,   //���鲻����
	emTP_ApplySpeaker_EpIDError,     //�᳡������
	emTP_ApplySpeaker_EpStateError,  //�᳡δ���߻�ͨ����δ����
};


enum EmTPChanSubType
{
	EmTPChanSubType_Normal, 
	EmTPChanSubType_Mini,
	EmTPChanSubType_Dual,   
	EmTPChanSubType_AMix,       
};

enum EmMakeCallType
{
	em_sip_call_type,
	em_323_call_type,
};

enum EmTpRegType
{
	em_sip_reg,
	em_323_reg,
};

enum EmDisListOprType
{
	em_DisListOpr_Add,
	em_DisListOpr_Del,
};

enum EmDisListOprReslt
{
	em_DisListOpr_Sucess,
	em_DisListOpr_Fail,
	em_DisListOpr_Reject,
};

//Add by tanxiaodong 2012-07-17.
//VGA����
enum EmVgaType
{
	//CNC˫����ʾԴ��ѡ������
	emVgaTypeDocCamera = 0,//�ĵ������
	emVgaType001,
	emVgaType002,
	emVgaType003,
	emVgaType004,
	emVgaType005,
	emVgaType006,
	emVgaTypeInValid//��Чֵ
};

//˫����ʾԴ����ӿ�����
enum EmDualInputType
{
   emDualInputDocCamera = 0,//�ĵ������
   emDualInput001,//��ʾԴ1
   emDualInput002,//��ʾԴ2
   emDualInput003,//��ʾԴ3
   emDualInput004,//��ʾԴ4
   emDualInput005,//��ʾԴ5
   emDualInput006,//��ʾԴ6
   emDualInputInvalid//��Чֵ

};

//˫����ʾԴ����ӿ�����
enum EmDualOutputType
{
	emDualOutputInvalid = 0,
	emDualOutput001,//��ʾ��1
    emDualOutput002 //��ʾ��2
};
//End to add.

//Added by meifang
enum EmVgaSwitchResult
{
	em_VgaSwitchInvalid,      //��Чֵ
	em_VgaSwitchFail = 1,     //�л�ʧ��
	em_VgaSwitchSucc,         //�л��ɹ�	
	em_CurVgaNoSignal,        //�л��ɹ�������ǰ��ʾԴ������
	em_TpNoDual,              //û�н�˫���ն�
	em_VgaBusying,            //��ʾԴ��æ���ܾ��л�
};

//��ʾԴ�л�ԭ��
enum EmVgaSwitchReason
{
	em_SwitchVgaInvalid,
		em_SwitchDemoVga = 1, //�������л�Ĭ����ʾԴ
		em_SwitchCurVga,      //�������л���ǰ��ʾԴ
		em_ResetVga,          //���ʱ����ΪĬ����ʾԴ
};

//�᳡״̬
enum EmCnState
{
	emCnsRunning, //��������
	emCnsSleep,   //����
	emCnsPoweroff, //�ػ�
};
//End to add

enum EmTPCapSign    //������ʶ�� ������
{
	emTPCapBig,  
	emTPCapLeft,
	emTPCapRight,
};

//Add by tanxiaodong 2012-11-22.
enum EmSwitchState
{
	emStateON = 1,   //����
	emStateOFF,      //�ػ�
	emStateStandby,  //����
};
//End to add.

//����������
enum EmTpBoardRet
{
	emTP_Board_UnKonw,                //����δ֪
	emTP_Board_AddSuccess,            //������ӳɹ�
	emTP_Board_DelSuccess,            //����ɾ���ɹ�
	emTP_Board_ModifySuccess,         //�����޸ĳɹ�
	emTP_Board_MaxNum,				  //���������ﵽ���ֵ
	emTP_Board_Mode_AddSuccess,       //����ģʽ��ӳɹ�
	emTP_Board_Mode_DelSuccess,       //����ģʽɾ���ɹ�
	emTP_Board_Mode_ModifySuccess,    //����ģʽ�޸ĳɹ�
	emTP_Board_UnFind,			      //δ�ҵ���Ŀ
	emTP_Board_UnKnowLoc,             //�����Ųۺ�δ֪
	emTP_Board_Repeat,                //�����ظ�
	emTP_BrdType_NotMatch_EqpType,    //�����������������Ͳ�ƥ��
	emTP_BrdMode_Repeat,              //Ҫ�޸ĵ�ģʽ��ԭģʽ��ͬ
	emTP_BrdMode_MaxNum,              //����ģʽ�ﵽ���ֵ
	emTP_BrdMode_NoConfig,			  //����δ����ģʽ
	emTp_BrdMode_Resource_Full,		  //ģʽ����eqpidʱ��Դռ��
	emTp_BrdMode_AudMix_MaxNum,       //�ﵽ������������·��
};

//hdu ����˿�����
enum EmHduOutPort
{
	em_hdu_outport_YPbPr = 0,
	em_hdu_outport_VGA   = 1,
	em_hdu_outport_DVI   = 2,
	em_hdu_outport_HDMI  = 3,

	em_hdu_outport_unknow,
};

//HDU ���ű���
enum EmHduZoomRate
{
	em_hdu_zoomrate_4_3  = 0,
	em_hdu_zoomrate_16_9 = 1,

	em_hdu_zoomrate_unknow,
};

//HDU �����ʽ
enum EmHduOutMode
{
	em_hdu_outmode_YPbPr_1080P_24fps = 0,
	em_hdu_outmode_YPbPr_1080P_25fps = 1,
	em_hdu_outmode_YPbPr_1080P_30fps = 2,
	em_hdu_outmode_YPbPr_1080P_50fps = 3,
	em_hdu_outmode_YPbPr_1080P_60fps = 4,
	em_hdu_outmode_YPbPr_1080i_50HZ  = 5,    //(Ĭ��)
	em_hdu_outmode_YPbPr_1080i_60HZ  = 6,
	em_hdu_outmode_YPbPr_720P_60fps  = 7,
	em_hdu_outmode_YPbPr_576i_50HZ   = 8,
	em_hdu_outmode_YPbPr_480i_60HZ   = 9,
		
	
	em_hdu_outmode_VGA_SXGA_60HZ     = 10,
	em_hdu_outmode_VGA_XGA_60HZ      = 11,     //(Ĭ��)
	em_hdu_outmode_VGA_XGA_75HZ      = 12,
	em_hdu_outmode_VGA_SVGA_60HZ     = 13,
	em_hdu_outmode_VGA_SVGA_75HZ     = 14,
	em_hdu_outmode_VGA_VGA_60HZ      = 15,
	em_hdu_outmode_VGA_VGA_75HZ      = 16,
	em_hdu_outmode_VGA_SXGA_75HZ     = 17,
	em_hdu_outmode_YPbPr_720P_50fps  = 18,  //zjl[20091216]�¼�hdu�����ʽ
	em_hdu_outmode_VGA_WXGA_1280_768_60HZ = 19,
	em_hdu_outmode_VGA_WXGA_1280_800_60HZ = 20,
	em_hdu_outmode_VGA_WSXGA_60HZ    = 21,
	em_hdu_outmode_VGA_SXGAPlus_60HZ = 22,
	em_hdu_outmode_VGA_UXGA_60HZ     = 23,
	em_hdu_outmode_YPbPr_1080P_29970HZ = 24,
	em_hdu_outmode_YPbPr_1080P_59940HZ = 25,
	em_hdu_outmode_WXGA_1280_800_75HZ  = 26,

	em_hdu_outmode_unknow,
};

//�������
enum EmHduShowMode
{
	em_hdu_showmode_NONGEOMETRIC   = 1,      //���ȱ�����
	em_hdu_showmode_CUTEDGEGEOME   = 2,      //�ñߵȱ�����
	em_hdu_showmode_BLACKEDGEGEOME = 3,      //�Ӻڱߵȱ�����

	em_hdu_showmode_unknow,
};

enum EmModifyNMServerRet
{
	em_nmserver_modify_success,		//�޸�(��ӣ��޸ģ�ɾ��)�ɹ�
	em_nmserver_resource_full,		//����������
	em_nmserver_invalid_handle,		//��Ч�ľ��
};

enum EmModifyVcrRet
{
	em_vcr_modify_success,	//�޸ĳɹ�
	em_vcr_invalid,	//��Ч��¼���
	em_vcr_full,	//¼�������
	em_vcr_no_exist,	//������
	em_vcr_exist,		//¼����Ѵ���
};

enum EmModifyHduRet
{
	em_hdu_modify_success,	//�޸ĳɹ�
	em_hdu_invalid_index,	//��Ч������
	em_hdu_brd_no_cfg,		//����δ����
};

enum EmUpdateHduRet
{
	em_hdu_update_success,	//�����ɹ�
	em_hdu_update_ing,		//��������
	em_hdu_update_unreg,	//����δע��
	em_hdu_update_unknow,	//δ֪ԭ��
};

enum EmMPCodec
{
	emMPCodec1,
	emMPCodec2,
	emMPCodec3,
	emMPDualCodec,
	emEndMPCodec
};

enum EmTPHDAudPortIn
{
	emTPAudInCanon1,
	emTPAudInCanon2,
	emTPAudInCanon3,
	emTPAudInCanon4,
	emTPAudInCanon5,
	emTPAudInCanon6,
	emTPAudInCanon7,
	emTPAudInCanon8,
	emTPAudInCanon9,
	emTPAudInCanon10,
	emTPAudInDigit0,
	emTPAudInDigit1,
	emTPAudInDigit2,
	emTPAudInEnd
};

enum EmTPHDDualAudPortIn
{	
	emTPAudInTrs1, //TRS��3.5mm���������루˫��PC���룩
	emTPAudInTrs2,
	emTPAudInTrs3,
	emTPAudInTrs4,
	emTPAudInRcaL,// RCA��L/R) �������루˫��DVD���룩
	emTPAudInRcaR,
	emTPDualAudInEnd
};

enum EmTPHDAudPortOut
{
	emTPAudOutCCanon1  ,
	emTPAudOutCCanon2,
	emTPAudOutCCanon3,
	emTPAudOutCCanon4,
	emTPAudOutCCanon5,
	emTPAudOutReproducer,//����������
	emTPAudOutEnd
};

//�ն���Ƶ����˿�
enum EmTPMtVideoPort
{
	emTPC1Vid   ,  //C1����   DVI 1
	emTPC2Vid   ,  //C2����   DVI 2
	emTPC3Vid   ,  //C3����   DVI 3
	emTPC4Vid   ,  //C4����   SUB IN 1
	emTPC5Vid   ,  //C5����   SUB IN 2
	emTPC6Vid   ,  //C6����   AUX IN 1
	emTPC7Vid   ,  //C7����	  AUX IN 2
	emTPC8Vid   ,  //C8����	  AUX IN 3
	emTPC9Vid   ,  //C9����   AUX IN 4
	emTPC10Vid   ,  //C10���� AUX IN 5
	emTPC11Vid   ,  //C11���� AUX IN 6  
	emTPVidEnd
};


enum EmTPMtVideoOutPort
{
	emTPC1OutVid   ,  //C1����   DVI 1
		emTPC2OutVid   ,  //C2����   DVI 2
		emTPC3OutVid   ,  //C3����   DVI 3
		emTPC4OutVid   ,  //C4����   
		emTPC5OutVid   ,  //C5����   
		emTPVidOutEnd
};

enum EmTPAutoTestType // �������
{
    emTPAutoTestBegin,            //���Կ�ʼ
	emTPAutoTestAudioLoopBackFunc,    //��Ƶ���ع��ܲ���
	emTPAutoTestPriomVideoLoopBackFunc,    //����Ƶ���ع��ܲ��ԣ���������
	emTPAutoTestSecondVideoLoopBackFunc, //˫��
	emTPAutoTestEnd               //���Խ���
};

enum EmTPHduRunStatus
{
	emTPHduIdle,		//����״̬
	emTPHduWaiting,		//�ȴ�
	emTPHduPlaying,		//����״̬
	emTPHduUnknow,		//δ֪״̬
};

// ������������С����
enum EmTPLoudspeakerVal
{
	emTPLoudspeakerLow = 0,
		emTPLoudspeakerMiddle,
		emTPLoudspeakerHigh,
};
//֡�ʵ�λ����
enum EmTPFrameUnitType
{
    emTPFrameSecond =0,
		emTPSecondFrame =1
};

//��Ƶ��ʽ����
enum EmTPVideoStandard
{
    emTPPAL  =0 ,
		emTPNTSC = 1 ,
		//    emTPSECAM = 2
};

//̨������
enum EmTPLabelType
{
    emTPLabelAuto    =0,   //�Զ�
		emTPLabelUserDef =1,  //�Զ���
		emTPLabelOff     =2  //�ر�
};

//̨��λ������
enum EmTPLabelPosType
{ 
	emTPTopLeft      = 0,
		emTPTopRight     = 1,
		emTPBottomLeft   = 2,
		emTPBottomRight  = 3
};

//˫����ʾģʽ
enum EmTPDualVideoShowMode
{
    emTPDualVideoOnSigleScreen  =0,//����˫��
		emTPEachVideoOwnScreen      =1,//˫��˫��
		emTPTripleVideoOnSingleScn  =2 //��������
};

//��ʾ����
enum EmTPDisplayRatio
{
	emTPDR4to3      = 0, //4:3
		emTPDR16to9     = 1, //16:9
		emTPDRAuto      = 2, //0:0
};

//FEC�㷨����
enum EmTPFecModeType
{
	emTPFECTYPENONE  =				0x00,
		emTPFECTYPERAID5 =				0x01,
		emTPFECTYPERAID5INTERLEAVE =	0x02,
		emTPFECTYPERAID6 =				0x03,			//������ʱ�������������
};

// �ش�ʱ��ѡ�����������
enum EmTPNetType
{
	emTPInternet = 0,
		emTPSpecial,
		emTPVPN,
};

//������Ƶ�ʵ�
enum EmTPEqualizerRate
{
	emTPRate100,
	emTPRate200,
	emTPRate400,
	emTPRate600,
	emTPRate1k,
	emTPRate3k,
	emTPRate6k,
	emTPRate12k,
	emTPRate14k,
	emTPRate16k,
	emTPRateend
};

enum  EmTPPIPMode
{
	TP_VIDEO_PIPMODE_IDLE = 0,              //����
	TP_VIDEO_PIPMODE_LOOP,                 //�Ի�
	TP_VIDEO_PIPMODE_ONE_LOCAL,             //�����濴����
	TP_VIDEO_PIPMODE_ONE_OTHER,             //�����濴Զ��
	TP_VIDEO_PIPMODE_THREE_L_ONEBIG,         //�����棬��ߴ��С
	TP_VIDEO_PIPMODE_THREE_M_ONEBIG,         //�����棬�м���С
	TP_VIDEO_PIPMODE_THREE_R_ONEBIG,         //�����棬�ұߴ��С
	TP_VIDEO_PIPMODE_ONE_AUX_LOCAL         //�����濴����˫��        
};

enum EmTPDVIMode
{
	TP_DVI_MODE_HDMI,
	TP_DVI_MODE_VGA,
	TP_DVI_MODE_DVI,
	TP_DVI_MODE_Ypbpr,
	TP_DVI_MODE_INVALID
};	

//MC ��ģʽ
enum EmTPMCMode
{
	emTPMcSpeech  ,//�ݽ�ģʽ
		emTPMcDiscuss ,//����ģʽ
		emTPMcModeEnd
};

//cns����״̬
enum EmCnsUpdateState
{
	emCnsIdle,
		emCnsDownloading,
		emCnsDownloaded,
		emCnsUpdating,
};

//cn��¼�����������Ľ��
enum EmTPCnLoginUpdateRet
{
	emTPCnLoginUpdateInvalid,
	emTPCnLoginUpdateFail,
	emTPCnLoginUpdateSuccess,
};

//������ʹ�ù������а汾��
enum EmTPFileSrvUsedVersion
{
    emTPFileSrvUsedVersion1     = 1,
		emTPFileSrvUsedVersion2     = 2
};

//�ļ�����
enum EmTPFileSrvFileType
{
    emTPFileSrvFileTypeUnknown      = 0,//δ֪
		emTPFileSrvFileTypeService      = 1,//ҵ���ļ�
		emTPFileSrvFileTypeConsole      = 2//����̨�ļ�
};

enum EmTPOSType
{
	emTPWindows,
	emTPLinux
};

enum EmMPAudEncCodec
{
	emMPAudEncCodec1,
	emMPAudEncCodec2,
	emMPAudEncCodec3,
	emMPAudEncDualCodec,
	emMPAudEncMixCodec,
	emEndMPAudEncCodec
};

enum EmToolType
{
	emMainTerabceTool,//ά������
	emProTestTool  //�������Թ���
};

//add by niulifu
enum EmProducetestType
{
	emProducetestTypeBegin,
	emTestVideoMAIN1InOut,
	emTestVideoMAIN2InOut,
	emTestVideoMAIN3InOut,
	emTestVideoSUB1InMAIN3AUX12Out,
	emTestDualSUB2InTurnHDMIAUX1Out,
	emTestDualAUX1InTurnHDMIAUX1Out,
	emTestDualAUX2InTurnHDMIAUX1Out,
	emTestDualAUX3InTurnHDMIAUX1Out,
	emTestDualAUX4InTurnHDMIAUX2Out,
	emTestDualAUX5InTurnHDMIAUX2Out,
	emTestDualAUX6InTurnHDMIAUX2Out,
	emTestDualSUB2InTurnVGAAUX1Out,
	emTestDualAUX1InTurnVGAAUX1Out,
	emTestDualAUX2InTurnVGAAUX1Out,
	emTestDualAUX3InTurnVGAAUX1Out,
	emTestDualAUX4InTurnVGAAUX2Out,
	emTestDualAUX5InTurnVGAAUX2Out,
	emTestDualAUX6InTurnVGAAUX2Out,
	emTestAudioMIC1InMAIN1Out,
	emTestAudioMIC2InMAIN2Out,
	emTestAudioMIC3InMAIN3Out,
	emTestAudioCANNON1InMAIN1Out,
	emTestAudioCANNON2InMAIN1Out,
	emTestAudioCANNON3InMAIN1Out,
	emTestAudioCANNON4InMAIN2Out,
	emTestAudioCANNON5InMAIN2Out,
	emTestAudioCANNON6InMAIN2Out,
	emTestAudioCANNON7InMAIN3Out,
	emTestAudioCANNON8InMAIN3Out,
	emTestAudioCANNON9InMAIN3Out,
	emTestAudioCANNON10InMAIN2Out,
	emTestAudioAUX1InAUX1Out,
	emTestAudioAUX2InAUX1Out,
	emTestAudioAUX3InAUX1Out,
	emTestAudioAUX4InAUX2Out,
	emTestAudioAUX5InAUX2Out,
	emTestAudioAUX6InAUX2Out,
	emTestUSB1Func,
	emTestUSB2Func,
	emTestRTCFunc,
	emTestLightFunc,
	emTestLAN1Func,
	emTestLAN2Func,
	emTestRS232LoopbackFunc,
	emTestRS422LoopbackFunc,
	emTestRS485LoopbackFunc,
	emTestRS232ANDCOM1LoopbackFunc,
	emTestRS422ANDCOM2LoopbackFunc,
	emTestCOM3ANDCOM4LoopbackFunc,
	emTestCOM5ANDCOM6LoopbackFunc,
	emTestInfraredRecFunc,
	emTestInfraredSendFunc,
	emTestALMLoopBackFunc,
	
	//����Ƶ����һ���Բ������ͬһ������ӿ��벻ͬ����ӿڻ���
    emTestAudioInMain1OutCannon1In,
	emTestAudioInMain1OutCannon2In,
	emTestAudioInMain1OutCannon3In,
	emTestAudioInMain1OutCannon4In,
	emTestAudioInMain1OutCannon5In,
	emTestAudioInMain1OutCannon6In,
	emTestAudioInMain1OutCannon7In,
	emTestAudioInMain1OutCannon8In,
	emTestAudioInMain1OutCannon9In,
	emTestAudioInMain1OutCannon10In, //����10��Ϊһ��������

	//���һ���Բ��������ͬ����ӿ���ͬһ������ӿڻ���
	emTestAudioOutMainL1OutCannon1In,
	emTestAudioOutMainR1OutCannon1In,
	emTestAudioOutMainL2OutCannon1In,
	emTestAudioOutMainR2OutCannon1In,
	emTestAudioOutMainL3OutCannon1In,
	emTestAudioOutMainR3OutCannon1In, //����6��Ϊһ��������
	emProducetestTypeEnd
};


//���¼����ļ������Ľ��
enum EmMdyRecFileRes
{
	em_rec_file_unknow,
	em_rec_file_success,
	em_rec_file_longnamesize,	//�������ļ���
	em_rec_file_inuse,			//�ļ����ڱ�����
	em_rec_file_nameexist,		//�ļ����Ѵ���
	em_rec_file_invalidrecorder,	//��Ч��¼���
	em_rec_file_noregisted,		//δע��
	em_rec_file_invalid_info,	
};


//��ʼ¼��Ľ��
enum EmUseReccorderRes
{
	em_rec_success,				//�ɹ�
	em_rec_invalid,				//��Ч��¼���
	em_rec_unregisted,			//δע��
	em_rec_no_resource,			//�޿�����Դ
	em_rec_invalid_conf,		//��Ч�Ļ���
	em_rec_invalid_format,		//��Ч�ĸ�ʽ
	em_rec_unknow_rectype,		//δ֪��¼������
	em_rec_invalid_mt,			//��Ч�Ļ᳡
	em_rec_recordering,			//����¼��
	em_rec_playing,				//���ڷ���
	em_rec_chair_playing,		//�ϼ����ڽ��з���
	em_rec_server_reject,		//¼���������ܾ�
	em_rec_invalid_rec_info,	//δ�ҵ���Ӧ��¼����Ϣ
	em_rec_invalid_play_info,	//δ�ҵ���Ӧ�Ĳ�����Ϣ
	em_rec_no_in_pause,			//���鲻������ͣ״̬
	em_rec_mt_offline,			//�᳡����
	em_rec_name_hasunderline,	//�����а����»���
	em_rec_longnamesize,		//�������ļ���
	em_rec_fileexist,			//�ļ��Ѿ�����
	em_rec_fileinuse,			//�ļ����ڱ�����
	em_rec_loadlib_failed,		//¼������������lib��ʧ��
	em_rec_setrecmode_failed,	//����¼��ʽʧ��
	em_rec_publicfailed,		//����ʧ��
	em_rec_inrequesting,		//��������
	em_rec_req_failed,			//����ʧ��
	em_rec_norecord,			//δ¼��
	em_rec_file_damange,		//�ļ���
	em_rec_in_stopping,			//¼�����ڱ�ֹͣ
	em_rec_in_pausing,			//¼���ڴ�����ͣ״̬
	em_rec_no_in_working,		//�����ڹ���״̬
	em_rec_invalid_channel,		//��Ч��ͨ��
	em_rec_unmatch_format,		//��ʽδƥ��
	em_rec_unknow_reason,				//δ֪����
};

//¼������
enum EmRecorderType
{
	em_rec_recorder_unknow,
	em_rec_recorder_conf,	//¼�ƻ���
	em_rec_recorder_mt,		//¼���ն�
};

//¼��״̬
enum EmConfRecState
{
	em_rec_unknow,
	em_rec_init,		//��ʼ��
	em_rec_working,		//����¼��
	em_rec_pause,		//������ͣ״̬
	em_rec_finish,		//���
};

//End Add


//add
//add
enum EmTpProfile
{
	emTpProfileBaseline = 64,
	emTpProfileMain = 32,
	emTpProfileExtend = 16,
	emTpProfileHigh = 8
};

enum EmTPHandleCfgType
{
	emTPShowCfg, //��ʾ������Ϣ
	emTPSetCfg,  //����������Ϣ
	emTPPostCfg  //����������Ϣ
};

//���������
enum EmTpCodecType
{
	emTpVEnc = 0,
		emTpVDec,
		emTpAEnc,
		emTpADec,
};

//ά������״̬
enum EmToolState
{
	em_Tool_IDLE = 0,
	em_Tool_READY
};

//��Ƶ����ģʽ
enum EmTPAudPlayMode
{
    emTP_PLAY_FULL = 0,     //3·����
    emTP_PLAY_SINGLE        //��·����	
};

//˫����Ƶ����˿�ģʽ
enum EmTPAudDualInMode
{
    emTP_AUD_DUAL_AUTO = 0,     //�Զ�     
	emTP_AUD_DUAL_HDMI,        //����hdmi
    emTP_AUD_DUAL_LINEIN,      //����RCA��TRS
};

enum EmTPDualType
{
	emTP_TPad_DUAL_VEDIO = 0,  // pc daul vedio from TPad
	emTP_DV_DUAL_VEDIO,   
	emTP_NONE_DUAL_VEDIO
};


enum EmTPDsNode
{
	emTp_Ds = 0,
	emTp_Node = 1
};

enum EMScreenLooked
{
	emScreenInvalid	=	0,		//��Ч��Ļ
	emScreenSelf	=	1,		//����
	emScreenSpeaker =	2,		//��������
	emScreenPoll	=	3,		//����ѯ
	emScreenView	=   4,		//ѡ��
	emScreenDiscard	=   5,		//������ͼ��
	emScreenRecPlay =   6,		//������
		
	emScreenLookedEnd = 7,		//��ϯ��״̬��������Ŀ
};

//moon add
//dvi ֧������
enum EmTPDVIOutPortType
{
	TPMOON_DVI_MODE_HDMI,
	TPMOON_DVI_MODE_DVI,
	TPMOON_DVI_MODE_INVALID
};

//Moon ֧���л��������ʽ
enum EmTPMOONOutMode
{
	em_MoonOutMode_720P_60fps,
	em_MoonOutMode_720P_50fps,
	em_MoonOutMode_1080P_25fps,
    em_MoonOutMode_1080P_30fps,
    em_MoonOutMode_1080P_50fps,
	em_MoonOutMode_1080P_60fps,//(Ĭ��)
	em_MoonOutMode_Unknown
};

//ͼ�����
enum EmTPImageAdjust
{
	emClosed,
	emVertTurn,
	emflatTurn
};
//�۽����ع⡢��ƽ��ģʽ
enum EmTPMOOMMode
{
	emAuto,
	emManual
};

//�ֶ��۽�
enum EmTPManualMode
{
	emFarth,
	emNearth
};

//��Ұ
enum EmTPZOOM
{
	emEnlarge,
	emReduce
};

//����� �ع�--����
enum EmTPExpGain
{
	em_Gain_Nega10_5dB = 0x00,
	em_Gain_Nega9dB          ,
	em_Gain_Nega7_5dB        ,
	em_Gain_Nega6dB          ,
	em_Gain_Nega4_5dB        ,
	em_Gain_Nega3dB          ,
	em_Gain_Nega1_5dB        ,
	em_Gain_ZerodB               ,
	em_Gain_Posi1_5dB        ,
	em_Gain_Posi3dB          ,
	em_Gain_Posi4_5dB        ,
	em_Gain_Posi6dB          ,
	em_Gain_Posi7_5dB        ,
	em_Gain_Posi9dB          ,
	em_Gain_Posi10_5dB 
};

//��������60/30fps  �ع�--����
enum EmTPSOrThShutter
{
	em_Shutter_1Sp  = 0x00,   // 1/1
	em_Shutter_2Sp ,          // 1/12
	em_Shutter_4Sp ,          // 1/4
	em_Shutter_8Sp ,          // 1/8
	em_Shutter_15Sp ,         // 1/15
	em_Shutter_30Sp ,         // 1/30
	em_Shutter_60Sp ,         // 1/60
	em_Shutter_90Sp ,         // 1/90
	em_Shutter_100Sp,         // 1/100(Ĭ��)
	em_Shutter_125Sp,         // 1/125
	em_Shutter_180Sp,         // 1/180
	em_Shutter_250Sp,         // 1/250
	em_Shutter_350Sp,         // 1/350
	em_Shutter_500Sp,         // 1/500
	em_Shutter_725Sp,         // 1/725
	em_Shutter_1000Sp,        // 1/1000
	em_Shutter_1500Sp,        // 1/1500
	em_Shutter_2000Sp,        // 1/2000
	em_Shutter_3000Sp,        // 1/3000
	em_Shutter_4000Sp,        // 1/4000
	em_Shutter_6000Sp,        // 1/6000
	em_Shutter_10000Sp        // 1/10000
};

//��������50/25fps  �ع�--����
enum EmTPFOrTwShutter
{
	em_Shutter_1Spd  = 0x00,   // 1/1
	em_Shutter_2Spd ,          // 1/12
	em_Shutter_3Spd ,          // 1/3
	em_Shutter_6Spd ,          // 1/6
	em_Shutter_12Spd ,         // 1/12
	em_Shutter_25Spd ,         // 1/25
	em_Shutter_50Spd ,         // 1/50
	em_Shutter_75Spd ,         // 1/75
	em_Shutter_100Spd,         // 1/100(Ĭ��)
	em_Shutter_120Spd,         // 1/120
	em_Shutter_150Spd,         // 1/150
	em_Shutter_215Spd,         // 1/215
	em_Shutter_300Spd,         // 1/300
	em_Shutter_425Spd,         // 1/425
	em_Shutter_600Spd,         // 1/600
	em_Shutter_1000Spd,        // 1/1000
	em_Shutter_1250Spd,        // 1/1250
	em_Shutter_1750Spd,        // 1/1750
	em_Shutter_2500Spd,        // 1/2500
	em_Shutter_3500Spd,        // 1/3500
	em_Shutter_6000Spd,        // 1/6000
	em_Shutter_10000Spd        // 1/10000
};

//����� �ع�--��Ȧ
enum EmTPAperture
{
	em_Aperture_OFF  = 0x00,
    em_Aperture_F14 = 0x05,
    em_Aperture_F11,
	em_Aperture_F9_6,
	em_Aperture_F8,
	em_Aperture_F6_8,
	em_Aperture_F5_6,
	em_Aperture_F4_8,
	em_Aperture_F4,
	em_Aperture_F3_4,
	em_Aperture_F2_8,
	em_Aperture_F2_4,
	em_Aperture_F2,
	em_Aperture_F1_8 //(Ĭ��)
};

enum EmTPReduNoise
{
	emClose,
	emLevelFist,
	emLevelSecond,
	emLevelThird,
	emLevelFourth,
	emLeVelFifth
};

enum EmTPImagePara
{
	emBlight,  //����
	emContrast,//�Աȶ�
	emSharp,  //���
	emSaturat    //���Ͷ�
};

//ͼ��ƴ��
enum EmImageMosaicType
{
    em_Mosaic_Cut,           //�ü�
	em_Mosaic_Stretch,       //����
	em_Mosaic_Adjust,        //����У������
	em_Mosaic_Redunoise      //����
};
//����
enum EmTPFpgaReduNoise
{
	emFpgaClose,
	emFpgaLow,
	emFpgaMid,
	emFpgaHight
};

enum EmMOONProductTestType
{
	emProducetestBegin,
	emTestDVI1_HDMI,
	emTestDVI2_HDMI,
	emTestDVI3_HDMI,
	emTestEth,
	emTestRS232,
	emTestGreenRedLight,
	emTestGreenLight,
	emTestZoom_DVI1_HDMI,
	emTestZoom_DVI2_HDMI,
	emTestZoom_DVI3_HDMI,
	emTestThreeSnapShot,
	emTestCAM1_LvdsBaud,
	emTestCAM2_LvdsBaud,
	emTestCAM3_LvdsBaud,
	emProducetestEnd
};
//LVDS ������
enum EmTPLVDSBaud
{
	em_LVDSBaud_9600bps,//(Ĭ��)
	em_LVDSBaud_19200bps,
	em_LVDSBaud_38400bps,
	em_LVDSBaud_115200bps,
	em_LVDSBaud_Unknown
};
//����У��
enum EmTPCorrect
{
	em_HorizonCorrect,
	em_HorizonStretch,
	em_VerticalCorrect,
	em_VerticalStretch
};

//�汾��
enum EmTpVer
{
	tp_Ver_MOON90,
	tp_Ver_MOON90H
};


enum EmTPCorrectChange
{
	emCorrectEnlarge,//����
	emCorrectReduce//��С
};

enum EmTPCamNoiseLevel
{
	emNoiseClose,
	emNoiseLevel1,
	emNoiseLevel2,
	emNoiseLevel3,
	emNoiseLevel4,
	emNoiseLevel5
};

//add by youjx 2016.11.21
enum EmTPMechanism
{
    emH650 = 0,
    emSony = 1,
    emSonyFCBCS8230 = 2
};

enum EmH650Gamma
{
    emGamma1 = 0x00,
    emGamma2,
    emGamma3,
    emGamma4
};
//��ɫһ����RGB����
enum EmTPColorConsistency
{
    emColorRed,
    emColorBlue,
    emColorGreen
};
//����У����λ��
enum EmTPDistortPosition
{
    emUperLeftHorizon,       //���ϽǶ�����������
    emUperLeftVertical,      //���ϽǶ�����������
    emUperRightHorizon,      //���ϽǶ�����������
    emUperRightVertical,     //���ϽǶ�����������
    emLowerRightHorizon,     //���½Ƕ�����������
    emLowerRightVertical,    //���½Ƕ�����������
    emLowerLeftHorizon,      //���½Ƕ�����������
    emLowerLeftVertical,     //���½Ƕ�����������
    emLeftSide,              //�������
    emRightSide,             //�ұ�����
    emTopSide,               //�ϱ�����
    emBottomSide,            //�±�����
    emCenterRotate,          //������ת
};

//add end

//moon end
#endif // _h_tpcommontype_h__