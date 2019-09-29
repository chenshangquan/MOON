/*****************************************************************************
   ģ����      : MTCONTROL
   �ļ���      : MtCtrlLib.h
   ����ļ�    : 
   �ļ�ʵ�ֹ���: MTҵ�����3.0�ӿ��ļ�
   ����        : �˻�
   �汾        : V3.0  Copyright(C) 2003-2005 KDC, All rights reserved.
-----------------------------------------------------------------------------
   �޸ļ�¼:
   ��  ��      �汾        �޸���      �޸�����
   2003/08/20  3.0         �˻�        ����
******************************************************************************/
#ifndef _MT_CORE_H
#define _MT_CORE_H

#include "kdvtype.h"
//#include "kdvdef.h"
#include "mteventdef.h"
#include "mtconstdef.h"
#include "vccommon.h"
#include "time.h"


//������Ϣ������
enum ReturnMsgType
{
	Ret_DevInit,
	Ret_CamCtrl,
	Ret_MatrixCtrl,
	Ret_GkRegister,
	Ret_MakeCall,
	Ret_AnswerCall,
	Ret_HangUp,
	Ret_DropTer,
	Ret_ApplySpeak,
	Ret_BroadCastTer,
	Ret_ViewThisTer,
	Ret_StartPoll,
	Ret_StopPoll,
	Ret_MakeMeChair,
	Ret_ReleaseChair,
	Ret_ConfEnd,
	Ret_SelfTest,
};

typedef enum
{
	ITT_MT_ConfState = 1,		//����״̬			| IT_CONFSTAT
	ITT_MT_PollState,			//��ѭ״̬			| IT_POLLSTAT
	ITT_MT_EncodeStat,			//����״̬			| IT_ENCSTAT
	ITT_MT_DecodeStat,			//����״̬			| IT_DECSTAT
	ITT_MT_CameraStat,			//����ͷ״̬		| IT_CAMERASTAT
	ITT_MT_MatrixStat,			//����״̬			| IT_MATRIXSTAT
	ITT_MT_TerCfg,				//������Ϣ����		| _TTERCFG
	ITT_MT_NetCfg,				//��������			| _TNETCFG
	ITT_MT_CallCfg,				//��������			| _TCALLCFG
	ITT_MT_AudioCfg,			//��Ƶ����			| _TAENCPARAM + _TADECPARAM
	ITT_MT_VideoCfg,			//��Ƶ����			| _TVENCPARAM + _TVDECPARAM
	ITT_MT_CameraCfg,			//����ͷ����		| _TDEVCFG+�豸��(1u8:1-4)
	ITT_MT_MatrixCfg,			//��������			| _TDEVCFG
	ITT_MT_OsdCfg,				//��ʾ����			| _TOSDCFG	
	ITT_MT_LastSms,				//���һ�ζ���Ϣ����| �ַ���
	ITT_MT_CODECSTATE,			//Codec״̬			| IT_CODECSTATE
	ITT_MT_Reboot,				//�������ն�
	ITT_MT_ADDRBOOK_NUM,		//��ַ����Ŀ����ĸ���	| IT_ADDRBOOK
	ITT_MT_ADDRBOOK_FIND_ENTRY,	//���ҵ�ַ����Ŀ		| IT_ADDRBOOK + TADDRENTRY	
	ITT_MT_ADDRBOOK_FIND_GROUP,	//���ҵ�ַ����			| IT_ADDRBOOK + TADDRMULTISETENTRY

		
	ITT_MC_GetState,			//��ȡMC״̬				|��
	ITT_MC_IsInConf,			//�ж���ĳ�ն˷��ڻ�����	|u32(ip) 
	ITT_MC_IsLableInConf,		//ָ�����ն˱���Ƿ��ڻ�����
	ITT_MC_GetFloorer,			//��ȡ��ǰ������
	ITT_MC_GetChair,			//��ȡ��ǰ��ϯ
	IIT_MC_GetConfInfo,			//��ȡ��ǰ������Ϣ
	ITT_MC_GetConfMode,			//��õ�ǰ����ģʽ
	ITT_MC_GetApplyingChair,	//�������������ϯ���ն�
	ITT_MC_GetApplyingFloorer,	//����������뷢�Ե��ն�
	ITT_MC_GetToBeFloorer,		//��ý���Ϊ�����˵��ն�
	ITT_MC_GetSrcLabel,			//�����ƵԴ�ն˱��

}InterTestType;

enum NodeType
{
	node_all,
	node_ui,
	node_mtc,
	node_mcu,
};

enum AddrType
{
	addr_ip = 1,
	addr_e164,
	addr_h323id,
	addr_email
};

enum AddrMissType
{
	miss_ipandmask = 1,
	miss_mac = 2,
	miss_all = 3,
};
//==================================================================================
//									�����ӿ�
//==================================================================================


API void mtctrlhelp();
API void mtctrlver();

extern "C" 
{

/*====================================================================
    ������      : InitMt
    ����        : ��ʼ��MtCtrlLib
    �������˵��: wGuiAppId		- �ϲ�GUI APP��
				  dwCodecAppId	- Codec APP��
				  configDir		- �����ļ�·��(��������"/"����!)
    ����ֵ˵��  : 0 - �ɹ� 1 - �����ļ���ʼ��ʧ�� 2 - ����MTC�����ڵ�ʧ��				
====================================================================*/
s32 InitMt(u16 wGuiAppId,u32 dwCodecAppId,const char* configDir = "./conf/",
		   const u16 listenPort = MT_CONNECT_PORT, const u16 wCallingPort = 1720 );

/*====================================================================
    ������      : CloseMt
    ����        : �ͷ�MtCtrlLib
    �������˵��: ��
    ����ֵ˵��  : ��
====================================================================*/
void CloseMt();

#ifdef WIN32
#define KDV8010_BOARD               100    /* KDV8010�ն� */
#define KDV8018_BOARD               101    /* KDV8018�ն� */
#define KDV8010A_BOARD              102    /* KDV8010A�ն� */
#define KDV8010B_BOARD              103    /* KDV8010B�ն� */
#define KDV8010C_BOARD              104    /* KDV8010C�ն� */
#define KDV8010D_BOARD              105    /* KDV8010D�ն� */
#define KDV8010E_BOARD              106    /* KDV8010E�ն� */
#define DSL8000_BRD_IMT				7       /* IMT�� */

u8 BrdGetBoardID();

#endif // WIN32

BOOL GetMtFilePath(const s8* sFileName/*IN*/,s8* sPath /*OUT*/);

BOOL AddrIsMca(u32 dwIp);
BOOL AddrIsBca(u32 dwIp);
}

//==================================================================================
//									��Ϣ�ṹ����
//==================================================================================
#ifdef WIN32
#pragma pack(1)
#define PACKED 
#else
#define PACKED __attribute__((__packed__))	// ȡ�����������Ż�����
#endif // WIN32

//Э���ַ
typedef struct tagIpAddr
{
	u32 ip;					//������
	u16 port;				
	u8  type;
}PACKED TIPADDR,*PTIPADDR;

//����������Ϣ
typedef struct tagConferenceInfo
{
	s8	 achConfId[CONF_ID_LEN + 1 ];			// ����ID
	s8	 achConfName[CONF_NAME_LEN + 1 ];		// ������
	s8	 achConfNumber[ CONF_E164_LEN + 1 ];	// �������
	s8	 achConfPwd[ MAX_PWD_LEN + 1 ];			// ��������
	u16  wConfDuration;							// �������ʱ��		
	u8   byVideoFormat;							// ������Ƶ��ʽ(VIDEO_H261��)
	u8	 byAudioFormat;							// ������Ƶ��ʽ(AUDIO_MP3��)
	u8   byResolution;							// ������Ƶ�ֱ���(VIDEO_CIF��)
	u8   byAutoVMP;								// �Ƿ��Զ�����ϳ�(MT_ENABLE/MT_DISABLE)
	u8   byAutoMix;								// �Ƿ����(MT_ENABLE/MT_DISABLE)
}PACKED _TCONFINFO,*_PTCONFINFO;


//������Ϣ����
typedef struct  tagTerCfg
{
	s8	achTerName[MT_NAME_LEN+1];			//�ն˱���
	s8	achE164Name[MT_E164_LEN+1];			//�ն�E164����
	u8	byProType;							//�ն�Э������
}PACKED _TTERCFG,*_PTTERCFG;

//Ethernet��ַ
typedef struct tagLanAddr
{
	u8  byIndex;	//������(win32��0,vxWorks��0-3)
	u32 dwIP;		//IP��ַ(������)
	u32 dwMask;		//��������(������)
	u8  byMacAddr[6];//MAC��ַ
}PACKED _TLANADDR,*_PTLANADDR;

// Qos
typedef struct tagQosInfo
{
	u8  byQosType;   //Service or IP first
	// Service first param.
	u8  bySrvAudio;
	u8  bySrvVideo;
	u8  bySrvData;
	u8  bySrvSignaling;
	// Ip first param.
	u8  byIpAudio;
	u8  byIpVideo;
	u8  byIpData;
	u8  byIpSignaling;
	u8  byTos;
}PACKED TQosInfo,*PTQosInfo;

//������Ϣ����
typedef struct  tagNetCfg
{
	_TLANADDR	tLocalAddr;	//���ص�ַ 
	u32		dwGWAddr;			//���ص�ַ
	u16		wSendInitPort;		//������ʼ�˿�
	u16		wRecvInitPort;		//������ʼ�˿�
	u8		byNetType;			//��������(������,������,ADSL,ISDN)
	u32		dwUpBandWidth;		//���д���(kbps)
	u32		dwDownBandWidth;	//���д���(kbps)
	TQosInfo tQosInfo;
}PACKED _TNETCFG,*_PTNETCFG;

// ���������Ϣ����
typedef struct tagSnmpCfg
{
	u32 dwTrapAddr;		// ����TRAP�ĵ�ַ(������)
	s8  achCommunity[ MT_COMM_LEN + 1 ];// ��ͬ����
}PACKED _TSNMPCFG,*_PTSNMPCFG;

//�豸��Ϣ����
typedef struct tagDeviceCfg
{
	u8  byDevNo;	//�豸��(���BIT(no.7)1:��ʹ��,0:ʹ��,ʣ��BITΪ�豸ID)
	u8  byType;		//�豸����
	u32 dwIpAddr;	//�豸IP(������)
	u16 wPort;		//�豸�˿�(��Ϊ�����豸,��ʾ���ں�)
	u8  byCameraAddr;	// ����ͷ��ַ
	u8  byCameraSpeed;	// ����ͷ�ٶ�
}PACKED _TDEVCFG,*_PTDEVCFG;

//������Ϣ����
typedef struct tagSeriesCfg
{
	u8  byType;  // ����Э��
	u32 dwBaudRate;	//������
	u8  byByteSize;	//����λ
	u8  byParity;		//��ż����
	u8  byStopBits;	//ֹͣλ
}PACKED _TSERCFG, *_PTSERCFG;

//��ʾ��Ϣ����
typedef struct tagOsdCfg
{
	u8	byShowLabel;		// �Ƿ���ʾ̨��		MT_ENABLE:����    MT_DISABLE: �ر�
	u8  byLabelType;		// ̨������ :		MT_LABEL_DEF:ϵͳĬ��  MT_LABEL_USER: �û��Զ���
	u8	byEncLabel;			// �Ƿ���ʾ״̬		MT_ENABLE:����	  MT_DISABLE: �ر�
	u8	byPIPMode;			// ���л�ģʽ		MT_AUTO:�Զ�����  MT_MANUAL: �ֶ�����
}PACKED _TOSDCFG,*_PTOSDCFG;

//������Ϣ����
typedef struct tagCallCfg
{
	u8	byAnswerMode;		//Ӧ��ʽ(MT_AUTO/MT_MANUAL/MT_REJECT)
	u8	byCallMode;			//���з�ʽ(MT_AUTO/MT_MANUAL)
	u8	byAdHocMode;		//��������չ��ʽ(MT_AUTO/MT_MANUAL/MT_REJECT)
	u16	wTtl;				//roundtripʱ����
	u8  byUseGk;			//�Ƿ�ʹ��GK(MT_ENABLE/MT_DISABLE)
	u32	dwGKAddr;			//���ص�ַ(������)
	u32	dwAutoCallIpAddr;	//�Զ����е�IP(������)	
	u16 wAutoCallRate;		//�Զ���������
	u8  byIsEncrypt;		//�Ƿ����(ENCRYPT_NONE/ENCRYPT_AUTO)
	u8	byEncryptMode;		//����ģʽ(ENCRYPT_AUTO/ENCRYPT_DES/ENCRYPT_AES)
	u8  byIsH239;			//�Ƿ�ʹ��H239(DUAL_H239_NONE/DUAL_H239_AUTO)
}PACKED _TCALLCFG,*_PTCALLCFG;

// ��Ƶ���
typedef struct tagVideoOut
{
	u8	byOutType;		//�������(VIDEO_S|VIDEO_VGA)
	u16 wVgaFs;			//VGAƵ��
	u8	byDvSource;		//˫�����Դ(MT_LOCAL:����|MT_REMOTE:����)
}PACKED _TVOUT,*_PTVOUT;

//��Ƶ�������
typedef struct tagVideoEncParam
{
	u8	vSource;			//��ƵԴ(VIDEO_COMP3��)
	u8	vFormat;			//��Ƶ��ʽ(VIDEO_H261��)
	u8	vSystem;			//��Ƶ��ʽ(VIDEO_PAL/VIDEO_NTSC)
	u8	vResolution;		//��Ƶ�ֱ���(VIDEO_CIF��)
	u8  vAutoFrame;			//�Ƿ����Զ�֡��(MT_ENALBE/MT_DISABLE)
	u8	vFrameRate;			//��Ƶ֡��
	u8	vFrameRateUnit;		//֡�ʵ�λ(VIDEO_FPS:֡/ÿ�� VIDEO_SPF:��/ÿ֡)
	u16	vBitRate;			//��Ƶ����(kbps)
	u16 vBandWidth;			//����������(kbps)
	u8	vCompress;			//ͼ��ѹ������(IMAGE_QUALITY_PRI/IMAGE_SPEED_PRI)
	u16	vIKeyRate;			//���ؼ�֡���
	u8	vQualMaxValue;		//ͼ��ѹ�������������
	u8	vQualMinValue;		//ͼ��ѹ����С��������
	u16 wH264IKeyRate;		//h264�Ĺؼ�֡���
	u8  byH264QualMaxValue;	//h264�����������
	u8  byH264QualMinValue;	//h264��С��������
}PACKED _TVENCPARAM,*_PTVENCPARAM;

//��Ƶ�������
typedef struct tagAudioEncParam
{
	u8	aSource;		//��ƵԴ(LINE/MIC)
	u8  aFormat;		//��Ƶ��ʽ(g711-56k/g711-64k/g723.1/g728/g729/mp3)
	u16 aBitRate;		//��Ƶ����(kbps)
	u8  aSampleRate;	//��Ƶ������(kbps)
	u8	aVolumn;		//��������
}PACKED _TAENCPARAM,*_PTAENCPARAM;

//��Ƶ�������
typedef struct tatVideoDecParam
{
	u8  byDecompress;		//ͼ���������(IMAGE_QUALITY_BETTER��)
	u8	vFormat;		//��Ƶ��ʽ
	u8	vOverlay;		//�Ƿ�ʹ��Overlay
	u8	vMpeg4BPV;		//Mpeg4����ֵ(0-4)
	u16 vBitRate;		//��Ƶ����(kbps)
}PACKED _TVDECPARAM,*_PTVDECPARAM;

//��Ƶ�������
typedef struct tagAudioDecParam
{
	u8  aFormat;		//��Ƶ��ʽ
	u8	aVolumn;		//��������
}PACKED _TADECPARAM,*_PTADECPARAM;

//AEC����
typedef struct tagAec
{
	u8	bAecEnable;		//�Ƿ�ʹ��AEC(MT_ENABLE|MT_DISABLE)
	u8	bAGC;			//�Ƿ��Զ�����(MT_ENABLE|MT_DISABLE)
	u8	byPolicy;		//����(1��2)
}PACKED _TAEC,*_PTAEC;

// ͼ����������
typedef struct tagImageQuality
{
	u8 byType;			// ͼ����������(���Ͷ�,����,�Աȶ�,����)
	u8 byBright;		// ���Ȳ���ֵ(0~255)
	u8 byContrast;		// �ԱȶȲ���ֵ(0~127)
	u8 bySaturation;	// ���ͶȲ���ֵ(0~127)
}PACKED _TIMAGEQUAL,*_PTIMAGEQUAL;

//�����ش�����
typedef struct tagSendRtCfg
{
	u8	bRetransmit;	//�Ƿ��ش�(MT_ENABLE|MT_DISABLE)
	u16 wTimeOut;		//����ʱ��(ms)
}PACKED _TSENDRTCFG,*_PTSENDRTCFG;

//�����ش�����
typedef struct tagRecvCfg
{
	u8	bRetransmit;	//�Ƿ��ش�(MT_ENABLE|MT_DISABLE)
	u16 wCheckPoint1;	//����1(ms)
	u16 wCheckPoint2;	//����2(ms)
	u16 wCheckPoint3;	//����3(ms)
	u16 wTimeOut;		//������ʱʱ��(ms)	
}PACKED _TRECVRTCFG,*_PTRECVRTCFG;

//����˿���Ϣ
typedef struct tagMatrixPort
{
	u8 byPort;							//�˿ں�
	u8 byImageId;						//ͼƬ���
	s8 achName[MATRIX_PORTNAME_LEN+1];	//�˿�����
}PACKED _TMATRIXPORT,*_PTMATRIXPORT;

//������Ϣ
typedef struct tagMatrixInfo
{
	u8  byPortNum;								//�˿ڸ���
	_TMATRIXPORT atInPort[MATRIX_MAX_PORT];		//����˿�
	_TMATRIXPORT atOutPort[MATRIX_MAX_PORT];	//����˿�
	u8  abyConfig[MATRIX_MAX_PORT];				//�������ù�ϵ(����Ϊ����˿�)
}PACKED _TMATRIXINFO,*_PTMATRIXINFO;

//�������÷���
typedef struct tagMtMatrixScheme
{
	u8	byType;										// ��������	
	u8	bySchemeId;									// ������
	s8	achVideoSchName[ MATRIX_SCHNAME_LEN + 1 ];	// ��Ƶ���󷽰�����
	_TMATRIXINFO atVideo;							// ��Ƶ���󷽰�����
	s8  achAudioSchName[ MATRIX_SCHNAME_LEN + 1 ];	// ��Ƶ���󷽰�����
	_TMATRIXINFO atAudio;							// ��Ƶ���󷽰�����
}PACKED _TMATRIXSCHEME,*_PTMATRIXSCHEME;

// ������Ϣ
typedef struct tagSnapInfo
{
	u8	byState;		// ��ȡ���(�ɹ�MT_OK/ʧ��MT_ERR)
	u32 dwMaxSize;		// ���ռ��С(�ֽ�)
	u32 dwUsedSize;		// ���ÿռ��С(�ֽ�)
	u32	dwSnapPicNum;	// ����ͼƬ����(��)
}PACKED _TSNAPINFO,*_PTSNAPINFO;


//�ն˵�ַ
typedef struct tagTerAddr
{
	u8			type;							//��ַ����
	u32			int_addr;						//(IP,������)
	s8			str_addr[MT_NAME_LEN+1];		//(����)
}PACKED _TERADDR,*_PTERADDR;

//���в���
typedef struct tagDialParam
{
	u8			byCallType;			//��������:JOIN|CREATE|INVITE
	u8			byWorkMode;			//����ģʽ(����/�ಥ,H320)
	u16			wCallRate;			//��������(kbps)
	_TERADDR	callingAddr;		//���е�ַ(����ʱ�ɲ���)
	_TERADDR	calledAddr;			//���е�ַ

	//////////////////////////////////////////////////////////////////////////
	//���½����ڴ�������
	u8			byCreateConf;		//�Ƿ��Ǵ�������(MT_ENABLE/MT_DISABLE)
	_TCONFINFO  tConfInfo;			//������Ϣ
	u8			byTerNum;			//�����ն˸���
	_TERADDR	atList[CONF_MT_CAPACITY/4];	//�����ն��б�,Ŀǰ���Ϊ32	
}PACKED _TDIALPARAM,*_PTDIALPARAM;

// �ն˱��������
typedef struct tagBitRate
{
	u8 byId;
	// ʵʱ���������
	u16 wSendBitRate;
	u16 wRecvBitRate;
	// һ����֮�ڵ�ƽ������
	u16 wSendAVBitRate;
	u16 wRecvAVBitRate;
}PACKED _TBITRATE,*_PTBITRATE;

// codec����ͳ����Ϣ
typedef struct tagCodecStatistic
{
	u8  byDecoderId;
	u16 wVideoBitRate;		// ��Ƶ��������
	u16 wAudioBitRate;		// ��Ƶ��������
	u32 dwVideoRecvFrm;		// �յ�����Ƶ֡��
	u32 dwAudioRecvFrm;		// �յ�����Ƶ֡��
	u16 wVideoLoseRatio;	// ��Ƶ������
	u16 wAudioLoseRatio;	// ��Ƶ������
	u32 dwVideoLoseFrm;		// ��Ƶ�ܶ�����
	u32 dwAudioLoseFrm;		// ��Ƶ�ܶ�����
}PACKED _TCODECSTATISTIC,*_PTCODECSTATISTIC;

// codec������Ϣ
typedef struct tagDecodeInfo
{
	u8 byDecoderId;			// ������ID
	u8 byVideoType;			// ��Ƶ��������
	u8 byVideoRes;			// ��Ƶ����ֱ���
	u8 byAudioType;			// ��Ƶ��������
}PACKED _TDECODEINFO,*_PTDECODEINFO;

// ��Ƶ����
typedef struct tagAudioPower
{
	u8	byDecoderId;
	u32 dwOutputPower;
	u32 dwInputPower;
}PACKED _TAUDIOPOWER,*_PTAUDIOPOWER;

// MAP״̬
typedef struct tagMapStatus
{
	u8	byId;		// MAP No.
	u8	byStatus;	// 0(����)/1(�쳣)
	u16	wDownNum;	// �쳣����
}PACKED _TMAPSTATUS,*_PTMAPSTATUS;

// ͼ�����
typedef struct tagImageTest
{
	u8 bySrc;		// ͼ��Դ(����MT_LOCAL/Զ��MT_REMOTE)
	u8 byType;		// ��������(�ֱ���RESOLUTION_TEST/ɫ��COLOR_TEST/�Ҷ�GRAY_TEST)
	u8 byOnOff;		// ����(MT_ENABLE/MT_DISABLE)
}PACKED _TIMAGETEST,*_PTIMAGETEST;

// ���ģʽ�л�
typedef struct tagMonitorSwitch
{
	u8  byOnOff;		// ����(MT_ENABLE/MT_DISABLE)
	u16 wTimeOut;		// �л�ʱ��(��λ:����)
}PACKED _TMONITORSWITCH,*_PTMONITORSWITCH;

// ��̬�غ����ýṹ
typedef struct tagDynamicPT
{
	u8 byMediaType;				// ý������(MT_AUDIO/MT_VIDEO)
	u8 byPayloadType;			// ý���ʽ
	u8 byDynamicPayloadType;	// ��̬�غ�ֵ
	u8 byDecoderId;				// ������ID
}PACKED _TDYNAMICPT,*_PTDYNAMICPT;

// ����/���ܽṹ
typedef struct tagEncrypt
{
	u8	byIndex;					// �豸ID
	u8	byMediaType;				// ý������(MT_AUDIO/MT_VIDEO)
	u8  byDynamicPayloadType;		// ��̬�غ�ֵ
	u8	byMode;						// ����ģʽ(ENCRYPT_DES/ENCRYPT_AES)
	u8  abyKey[ MAX_H235KEY_LEN ];	// ��Կ����
	int nKeyLen;					// ��Կ����(���ֽ�Ϊ��λ)
}PACKED _TENDECRYPT,*_PTENDECRYPT;

// ˫�������ṹ
typedef struct tagDualStream
{
	u8		bySource;		// [REQ]		˫��Դ(DUAL_VGA/DUAL_PC)
	u8		byOnOff;		// [REQ/RSP]	����(MT_START/MT_STOP)
	u8		byResult;		// [RSP]		�������(MT_OK/MT_ERR)
	TIPADDR tRecvAddr;		// [RSP]		�ն˽��յ�ַ(����PCԴ)
	u8		byReason;		// [RSP]		˫������ʧ�ܵ�ԭ��
}PACKED _TDUALSTREAM,*_PTDUALSTREAM;

// �ն�״̬
typedef struct tagTerStatus
{
	///////����״̬///////
	u8		bOnline;					//�Ƿ��ڻ�����	1 yes 0 no
	u8		byConfMode;					//����ģʽ		1 ���� 2 ���		
	u8		byPollStat;					//��ѯ״̬		1 ��ʼ 2 ��ͣ 3 ֹͣ
	u8		byCallMode;					//���з�ʽ		1 GK·�� 0 ֱ�Ӻ���
	u8		bRegGkStat;					//GKע����	1 �ɹ� 0 ʧ��
	u8		byEncryptConf;				//����״̬		1 ���� 0 ������(ֻ�Ǳ�ʾ���˷����Ƿ����)
	
	///////�豸״̬///////
	u8		byMtBoardType;				//�ն˰忨����	0: WIN,1:8010,2:8010a,3:8018,4:IMT,5:8010C
	u8		bMatrixStatus;				//����״̬		(1 ok 0 err)
	u8		byCamCtrlSrc;				//��ǰ��������ͷԴ����(0:����,1:Զ��)
	u8		byLocalCamCtrlNo;			//��ǰ���Ƶı�������ͷ��(1-6������ͷ)
	u8		byRemoteCamCtrlNo;			//��ǰ���Ƶ�Զ������ͷ��(1-6������ͷ)
	u8		byCamNum;					//����ͷ����	(0~6)
	u8		bCamStatus[CAMERA_MAX_NUM];	//����ͷ״̬ (1 ok 0 err)
	u8		byVideoSrc;					//��ǰ������ƵԴ(0:S����,1-6:C����)
	u8		bRemoteCtrl;				//�Ƿ�����Զң	1 yes 0 no

	//////�����״̬////////
	u8		byAEncFormat;				//��Ƶ�����ʽ(AUDIO_G711A,AUDIO_MP3...)
	u8		byVEncFormat;				//��Ƶ�����ʽ(VIDEO_H261,VIDEO_H263...)
	u8		byVEncRes;					//��Ƶ����ֱ���(VIDEO_QCIF,VIDEO_CIF...)
	u8      byEncryptMode;				//����ʹ�õļ����㷨(ENCRYPT_AES/ENCRYPT_DES/ENCRYPT_NONE)
	u8		byADecFormat;				//��Ƶ�����ʽ(AUDIO_G711A,AUDIO_MP3...)
	u8		byVDecFormat;				//��Ƶ�����ʽ(VIDEO_H261,VIDEO_H263...)
	u8		byVDecRes;					//��Ƶ����ֱ���(VIDEO_QCIF,VIDEO_CIF...)
	u8		byDecryptMode;				//����ʹ�õļ����㷨(ENCRYPT_AES/ENCRYPT_DES/ENCRYPT_NONE)
	u16		wSendBitRate[2];			//��Ƶ��������(��λ:kbps)
	u16		wRecvBitRate[2];			//��Ƶ��������(��λ:kbps)
	u16		wSendAVBitRate;				//ƽ����������(��λ:kbps)
	u16		wRecvAVBitRate;				//ƽ����������(��λ:kbps)
	u8		byEncVol;					//��ǰ��������(��λ:�ȼ�)
	u8		bMute;						//�Ƿ�����			1 yes 0 no
	u8		byDecVol;					//��ǰ��������(��λ:�ȼ�)
	u8		bQuiet;						//�Ƿ���			1 yes 0 no
	u8		bLocalLoop;					//�Ƿ��Ի�			1 yes 0 no
	u8		byAudioPower;				//�Ƿ��ڲ�����Ƶ	1 yes 0 no
	u8		byLocalImageTest;			//�Ƿ񱾵�ͼ�����1 yes 0 no
	u8		byRmtImageTest;				//�Ƿ�Զ��ͼ����� 1 yes 0 no
	u16		wSysSleep;					//����ʱ��(0xFFFF��ʾ������)

	//////����״̬///////

}PACKED _TTERSTATUS,*_PTTERSTATUS;

//UI������ʾ
typedef struct tagMtNote
{
	u8	byMsgId;			//��ϢID (ReturnMsgType)
	s8	achNote[64];		//����
}PACKED _TMTNOTE,*_PTMTNOTE;


//broadcast panel config
typedef struct tagPanelCfg
{
	u8	 byEnable;			// ��������MT_ENABLE/MT_DISABLE
	char achName[ MT_PATH_LEN ];	// Ƶ������
	u32	 dwIp;				// �鲥��ַ��������
	u16  wPort;				// �鲥�˿ں�
	char achPwd[ MT_PATH_LEN ];		// ��ý������
}PACKED _TPANELCFG,*_PTPANELCFG;

// ��ַ�ṹ
typedef struct tagProtocolAddr 
{
	TIPADDR  tLocalAddr;	//���˵�ַ
	TIPADDR  tRemoteAddr;	//�Զ˵�ַ
}PACKED TPROADDR,*PTPROADDR;

// �Ի��ṹ
typedef struct tagSelfTest
{
	u8	byMediaType;	// ý������(MT_VIDEO/MT_AUDIO/MT_AV)
	u8	byOnOff;		// ����(MT_START/MT_STOP)
	u32 dwIp;			// Ĭ��0:��ʾ127.0.0.1,����ָ��IP
}PACKED _TSELFTEST,*_PTSELFTEST;

// ��Ļ�ṹ
typedef struct tagTitleCfg
{
	u8		byEnable;			// ʹ��(MT_ENABLE/MT_DISABLE)
	u32		dwTextClr;			// ������ɫ
	u32		dwBkgClr;			// ����ɫ
	u8		byTextAlign;		// ���ֶ���ģʽ(TEXT_ALIGN_LEFT/TEXT_ALIGN_CENTER/TEXT_ALIGN_RIGHT)
	u8		byRollMode;			// ����ģʽ(ROLL_NOT_ROLL/ROLL_RIGHT_LEFT/ROLL_DOWN_UP)
	u8		byTransParent;		// �Ƿ�͸����ʾ(MT_ENABLE/MT_DISABLE)
	u8		byRollSpeed;		// �����ٶ�(ROLL_SPEED_SLOW/ROLL_SPEED_NORMAL/ROLL_SPEED_FAST/ROLL_SPEED_FASTER)
	u8		byRollNum;			// ��������(0:��ʾ�����ƹ���,1~255:��ʾ�û�ָ���Ĺ�������)
	u8		byStayTime;			// ͣ��ʱ��(0:��ʾ��ͣ��,1~255:��ʾ�û�ָ����ʱ��,��λ��)
	u32		dwStartXPos;		// ��Ļ��ʾ����ʼX����
	u32		dwStartYPos;		// ��Ļ��ʾ����ʼY����
	u32		dwDisplayWidth;		// ��Ļ��ʾ����Ŀ�(������Ϊ��λ)
	u32		dwDisplayHeight;	// ��Ļ��ʾ����ĸ�(ָ�и�,������Ϊ��λ)
	char	achWinInfo[ 256 ];	// ���ڴ��Windows�������Ϣ(��\0����)
}PACKED _TTITLECFG,*_PTTITLECFG;

// ��ѯ�ṹ
typedef struct tagMtPoll
{
	u8			byMediaType;		// ��ѯý���ʽ( MT_AUDIO/MT_VIDEO/MT_AV )
	u8			byIntTime;			// ��ѯ���ʱ��(��λ��)
	u8			byMtNum;			// �μ���ѯ���ն˸���,0��ʾ��������ն�(��λ��,���CTRL_POLL_MAXNUM)
	TMTLABEL	atMtLabel[ CTRL_POLL_MAXNUM ]; // �μ���ѯ���ն�<m,t>
}PACKED _TMTPOLL,*_PTMTPOLL;

// ������·״̬�ṹ
typedef struct tagLinkState
{
	u8			byLinkState;					// ��·״̬(CALL_LINKING,CALL_LINKED,CALL_UNLINK)
	u32			dwIpAddr;						// �Զ�IP��ַ(������)
	char		achAlias[ MT_DISPLAY_LEN + 1 ]; // �Զ˱���
	u8			byOtherInfo;					// ������Ϣ:
												// ����LINKING��ʾ���л��Ǳ���(MT_CALLING/MT_CALLED
												// ����UNLINK,��ʾ����ԭ��(DISCONNECT_REASON_BUSY/..)
}PACKED _TLINKSTATE,*_PTLINKSTATE;

// �ն˷�����Ϣ�ṹ
typedef struct tagMtDiskInfo
{
	char		achSysName[ MT_PATH_LEN + 1 ];		// ϵͳ��������
	char		achDataName[ MT_PATH_LEN + 1 ];		// ���ݷ�������
}PACKED _TMTDISKINFO,*_PTMTDISKINFO;

// ������ת���ṹ
typedef struct tagStreamForward
{
	u8			byDecoderId;			// ������ID
	u8			byMediaType;			// ý������(MT_VIDEO/MT_AUDIO)
	u16			wBitRate;				// ת����������
	TPROADDR	tRtpAddr;				// ת��Ŀ��RTP��ַ
	TPROADDR	tRtcpAddr;				// ת��Ŀ��RTCP��ַ
}PACKED _TSTREAMFWD,*_PTSTREAMFWD;

// ��ǰ��½�û���Ϣ
typedef struct tagLoginUserInfo
{
	char		achUserName[ MT_COMM_LEN + 1 ];	// ��½�û���
	u32			dwUserIp;						// ��½�û�IP(������)
}PACKED _TLOGINUSERINFO,*_PTLOGINUSERINFO;

/////////////////////Tony For Net Manager//////////////////////
typedef struct tagNetModule
{
	u8  byEthNum;
	u8  byE1Num;
}PACKED TNetModuleInfo, *PTNetModuleInfo;

/* ·�ɲ����ṹ */
typedef struct tagIpRouteParam{
	u8  byUsed;          // ����Ŀ�Ƿ�ʹ��
    u32 dwDesIpNet;      /* Ŀ������	*/
    u32 dwDesIpMask;     /* ����		*/
    u32 dwGwIpAdrs;      /* ����ip��ַ */
    u32 dwRoutePri;		 /* ·�����ȼ���0ΪĬ�� */
}PACKED TIpRouteParam, *PTIpRouteParam;

typedef struct tagAllRouteInfo{
    u32 dwIpRouteNum;    /* �õ���ʵ��·�ɸ��� */
    TIpRouteParam tIpRouteParam[ROUTE_MAX_NUM];//IP_ROUTE_MAX_NUM];
}PACKED TAllIpRouteInfo, *PTAllIpRouteInfo;

// E1ģ�����
typedef struct tagE1Module
{
  u32 dwUsedFlag;        /*ʹ�ñ�־,��1ʹ�ã�0��ʹ�� */
  u32 dwE1TSMask;        /* E1ʱ϶����˵�� */
  u32 dwProtocolType;    /* �ӿ�Э���װ����,����ǵ�E1���ӿ���ָ��PPP/HDLC������Ƕ�E1�������ӱ�����PPPЭ�� */
  u32 dwEchoInterval;    /* ��Ӧserialͬ���ӿڵ�echo����ʱ��������Ϊ��λ����Ч��Χ0-256��Ĭ����2 */
  u32 dwEchoMaxRetry;    /* ��Ӧserialͬ���ӿڵ�echo����ط���������Ч��Χ0-256��Ĭ����2 */
}PACKED TE1ModuleInfo, *PTE1ModuleInfo;

// E1ͨ������
typedef struct tagE1ChanInfo
{

	// Single & Multi Chan param.
    u8  byNumModuleUsed;           //  E1 Num Use By User.
	u8  byIsBind;                  //  �Ƿ��
    u32 dwIpAdrs;                  //  ip��ַ
    u32 dwIpMask;                  //  ���룬

	// Multi Chan param.
    u32 dwAuthenticationType;      //  PPP���ӵ���֤����PAP/CHAP,Ĭ����MP_AUTHENTICATION_PAP */
    u32 dwFragMinPackageLen;       //  ��С��Ƭ�������ֽ�Ϊ��λ����Χ20~1500��Ĭ����20 
    u8   chSvrUsrName[E1_NAME_MAXLEN]; 	/* ������û����ƣ�������֤�Զ˵����� */
    u8   chSvrUsrPwd[E1_NAME_MAXLEN];   	/* ������û����룬������֤�Զ˵����� */
    u8   chSentUsrName[E1_NAME_MAXLEN];	/* �ͻ����û����ƣ��������Զ���֤ */
    u8   chSentUsrPwd[E1_NAME_MAXLEN]; 	/* �ͻ����û����룬�������Զ���֤ */

	// E1 Module Param.
    TE1ModuleInfo tE1ModuleInfo[ E1_MODULE_MAXNUM ];//E1_SINGLE_LINK_CHAN_MAX_NUM];/* ÿ���������serialͬ���ӿڲ��� */

}PACKED TE1ChanInfo, *PTE1ChanInfo;

// Embeded Pxy Sys
typedef struct tagPxyInfo
{
	 u8   byPxyUsed;         //  ����ǽʹ�ñ�־
     u32  dwPxySrvIp;        //  ��������Ip
     u16  wPxySrvPort;       //  ��������Port
     u16  wMediaPort;        //  �����˿�
     u8   byPPPoeUsed;       //  PPPoe���ñ�־

}PACKED TPxyInfo, *PTPxyInfo;

typedef struct tagVideoParam // notify video param.
{
	u8	bIsEncrypt;		  //�Ƿ����
	u8	byVLocalMode;	  //��Ƶ�����㷨(����)
	u8  byVLocalKeyLen;   //
	u8  byVLocalKey[LEN_H235KEY_MAX];
	u8	byVRemoteMode;	  //��Ƶ�����㷨(����)
	u8  byVRemoteKeyLen;  //
	u8  byVRemoteKey[LEN_H235KEY_MAX];

	u8	byALocalMode;	  //��Ƶ�����㷨(����)
	u8  byALocalKeyLen;   //
	u8  byALocalKey[LEN_H235KEY_MAX];
	u8	byARemoteMode;	  //��Ƶ�����㷨(����)
	u8  byARemoteKeyLen;  //
	u8  byARemoteKey[LEN_H235KEY_MAX];
	
	u8  byVLocalType;     //������Ƶ���� 
	u8  byVLocalRealType; //������Ƶʵ������
	u8  byVRemoteType;    //Զ����Ƶ����
	u8  byVRemoteRealType;//Զ����Ƶʵ������

}PACKED TVideoParam, *PTVideoParam;

/////////////////////just use for windows////////////////////

//windows�µĲɼ�����
typedef struct
{
	u8	byCaptureType;	//�ɼ�����
	u8	byCaptFormat;	//�ɼ���ʽ
	u8	bOverlay;		//�Ƿ�ʹ��overlay MT_ENABLE | MT_DISABLE
	s8	sCaptFileName[MT_PATH_LEN+1];
}_TPCCODEC,*_PTPCCODEC;

typedef struct {
	s8	name[MT_NAME_LEN + 1];		//�û���
	s8	password[MT_PWD_LEN+1];	//����
}_TUSERREG,*_PTUSERREG;

#ifdef WIN32
#pragma pack()
#endif


//==================================================================================
//									�ඨ��
//==================================================================================
//����ṹ
typedef struct tagHandle
{
	u32		dwHsCall;				//���о��
	u32		dwHsChanOrRas;			//�ŵ�����RAS���
	void*	pAppCall;				//Ӧ�ú���ָ��
	void*	pAppChanOrRas;			//Ӧ���ŵ���RASָ��
	tagHandle():dwHsCall(NULL),dwHsChanOrRas(NULL),pAppCall(NULL),pAppChanOrRas(NULL) {}
}PACKED THANDLE,*PTHANDLE;


//ҵ����Ϣ�ṹ
typedef struct tagMtMsg 
{
	u32 dwHeader;				//��Ϣͷ��ʶ
	u16	wMsgLen;				//������Ϣ����
	u16 wBodyLen;				//���ݳ���
	u8  byMsgType;				//��Ϣ����
	u8  bySubType;				//������
	u8	byDirection;			//��Ϣ����
	u8  byNodeType;				//����ָ������ĳ�����͵�UI(node_all,node_ui,node_mtc)
	u16 wSrcId;					//��ϢԴID
	u16	wMsgId;					//��ϢID
	THANDLE tHandle;				//�ڲ���Ϣʹ��
	s8	achBody[MTMSG_CONTENT_LEN];	//��Ϣ����
}PACKED TMTMSG,*PTMTMSG;



////////////////�ն�ҵ����Ϣ///////////////////
class CMtMsg
{
public:
	CMtMsg()
	{ 
		memset(&m_tMsg,0,sizeof(TMTMSG)); 
		m_tMsg.dwHeader = htonl(MTMSG_HEADER);
		m_tMsg.wMsgLen  = htons(MTMSG_HEADER_LEN);
	}
	CMtMsg(PTMTMSG ptMsg,BOOL bNetOrder)
	{
		memset(&m_tMsg,0,sizeof(TMTMSG));
		if (ptMsg != NULL)
		{
			if (bNetOrder)
			{
				//������ת��Ϊ������
				u16 wMsgLen;
				wMsgLen = ntohs(ptMsg->wMsgLen);
				if (wMsgLen < sizeof(TMTMSG))
					memcpy(&m_tMsg,ptMsg,wMsgLen);
			}
			else
			{
				memcpy(&m_tMsg,ptMsg,ptMsg->wMsgLen);
				HostToNet();
			}
		}
	}
	//��д�ڲ���Ϣ���
	void SetHandle(PTHANDLE ptHandle)
	{
		if (ptHandle != NULL)
		{
			m_tMsg.tHandle.dwHsCall = htonl(ptHandle->dwHsCall);
			m_tMsg.tHandle.dwHsChanOrRas = htonl(ptHandle->dwHsChanOrRas);
			m_tMsg.tHandle.pAppCall = (void*)htonl((u32)ptHandle->pAppCall);
			m_tMsg.tHandle.pAppChanOrRas = (void*)htonl((u32)ptHandle->pAppChanOrRas);
		}
		//memcpy(&m_tMsg.tHandle,ptHandle,sizeof(THANDLE));
	}
	//��д��Ϣ����
	void SetBody(const void* pBody,u16 wLen)
	{
		if (pBody != NULL && wLen <= MTMSG_CONTENT_LEN)	
		{
			memcpy(m_tMsg.achBody,pBody,wLen);
			m_tMsg.wBodyLen = htons(wLen);
			m_tMsg.wMsgLen = htons(MTMSG_HEADER_LEN + wLen);
		}
	}
	void SetDirection(u8 byDirect) { m_tMsg.byDirection = byDirect; }
	void SetNodeType( NodeType node ) { m_tMsg.byNodeType = node; }
	void SetEvent(u16 wEvent)
	{
		//ϵͳ��Ϣ
		if (wEvent > EV_MTSYS_BGN && wEvent < EV_MTSYS_END)
		{
			m_tMsg.byMsgType = MT_SYS;
		}
		//�ڲ���Ϣ
		if (wEvent > EV_INNER_BGN && wEvent < EV_INNER_END)
		{
			m_tMsg.byMsgType = MT_INNER;
			if (wEvent > INNER_CALL_ENTRY && wEvent < INNER_CHAN_ENTRY)	//����
				m_tMsg.bySubType = INNER_CALL;
			if (wEvent > INNER_CHAN_ENTRY && wEvent < INNER_CTRL_ENTRY) //�ŵ�
				m_tMsg.bySubType = INNER_CHAN;
			if (wEvent > INNER_CTRL_ENTRY && wEvent < INNER_RAS_ENTRY)  //�������
				m_tMsg.bySubType = INNER_CTRL;
			if (wEvent > INNER_RAS_ENTRY && wEvent < INNER_MISC_ENTRY)  //RAS
				m_tMsg.bySubType = INNER_RAS;
			if (wEvent > INNER_MISC_ENTRY && wEvent < INNER_MC_ENTRY)	//�ڲ�MISC��Ϣ
				m_tMsg.bySubType = INNER_MISC;
			if (wEvent > INNER_MC_ENTRY && wEvent < INNER_H320_ENTRY)	//�ڲ�MC��Ϣ
				m_tMsg.bySubType = INNER_MC;
			if ( wEvent > INNER_H320_ENTRY &&wEvent < EV_INNER_END )	//H320��Ϣ
				m_tMsg.bySubType = INNER_H320;

		}
		//�ⲿ��Ϣ
		if (wEvent > EV_OUTER_BGN && wEvent < EV_OUTER_END)
		{
			m_tMsg.byMsgType = MT_OUTER;
			if (wEvent > OUTER_CONF_ENTRY && wEvent < OUTER_MATR_ENTRY) //���������Ϣ
				m_tMsg.bySubType = OUTER_CONFCTRL;
			if (wEvent > OUTER_MATR_ENTRY && wEvent < OUTER_CAM_ENTRY)	//��Ƶ�л�����
				m_tMsg.bySubType = OUTER_MATRIX;
			if (wEvent > OUTER_CAM_ENTRY && wEvent < OUTER_CODEC_ENTRY)	//����ͷ
				m_tMsg.bySubType = OUTER_CAMERA;
			if (wEvent > OUTER_CODEC_ENTRY && wEvent < OUTER_CFG_ENTRY)	//�����
				m_tMsg.bySubType = OUTER_CODEC;
			if (wEvent > OUTER_CFG_ENTRY && wEvent < OUTER_MISC_ENTRY)	//OSD
				m_tMsg.bySubType = OUTER_CFG;
			if (wEvent > OUTER_MISC_ENTRY && wEvent < EV_OUTER_END)		//�ⲿMISC��Ϣ
				m_tMsg.bySubType = OUTER_MISC;
		}
		m_tMsg.wMsgId = htons(wEvent);
	}
	//�����ϢID
	u16	GetMsgId()	{ 	return ntohs(m_tMsg.wMsgId); 	}	
	//�����Ϣ����
	u8	GetMsgDirect()	{	return m_tMsg.byDirection;	}
	//�����Ϣ����
	u8	GetMsgType()	{   return m_tMsg.byMsgType;	}
	//�����Ϣ������
	u8	GetMsgSubType() {   return m_tMsg.bySubType;	}
	// ��ȡ��Ϣ��Դ
	NodeType GetNodeType() { return (NodeType)m_tMsg.byNodeType; }
	//���������Ϣ(������)
	PTMTMSG GetMsg() 
	{
		return &m_tMsg; 
	}
	//���������Ϣ(������)
	void FetchHostMsg(TMTMSG &tMsg)
	{
		memset(&tMsg,0,sizeof(tMsg));
		u16 wMsgLen = ntohs(m_tMsg.wMsgLen);
		memcpy(&tMsg,&m_tMsg,sizeof(tMsg));
		tMsg.wMsgLen = wMsgLen;
		tMsg.dwHeader = ntohl(tMsg.dwHeader);
		tMsg.wMsgId = ntohs(tMsg.wMsgId);
		tMsg.wBodyLen = ntohs(tMsg.wBodyLen);
		tMsg.wSrcId = ntohs(tMsg.wSrcId);
		tMsg.tHandle.dwHsCall = ntohl(tMsg.tHandle.dwHsCall);
		tMsg.tHandle.dwHsChanOrRas = ntohl(tMsg.tHandle.dwHsChanOrRas);
		tMsg.tHandle.pAppCall = (void*)ntohl((u32)tMsg.tHandle.pAppCall);
		tMsg.tHandle.pAppChanOrRas = (void*)ntohl((u32)tMsg.tHandle.pAppChanOrRas);
	}

	//���������Ϣ����
	u16    GetMsgLen() 
	{ 
		return ntohs(m_tMsg.wMsgLen); 
	}
	//�����Ϣ��
	s8*	GetBody()	
	{ 
		return m_tMsg.achBody;
	}
	//�����Ϣ�峤��
	u16	GetBodyLen() 
	{ 
		return ntohs(m_tMsg.wBodyLen); 
	}

	//��Ϣͷ����ת��Ϊ������
	void    NetToHost()
	{
		m_tMsg.dwHeader = ntohl(m_tMsg.dwHeader);
		m_tMsg.wMsgId = ntohs(m_tMsg.wMsgId);
		m_tMsg.wMsgLen = ntohs(m_tMsg.wMsgLen);
		m_tMsg.wBodyLen = ntohs(m_tMsg.wBodyLen);
		m_tMsg.wSrcId = ntohs(m_tMsg.wSrcId);
		m_tMsg.tHandle.dwHsCall = ntohl(m_tMsg.tHandle.dwHsCall);
		m_tMsg.tHandle.dwHsChanOrRas = ntohl(m_tMsg.tHandle.dwHsChanOrRas);
		m_tMsg.tHandle.pAppCall = (void*)ntohl((u32)m_tMsg.tHandle.pAppCall);
		m_tMsg.tHandle.pAppChanOrRas = (void*)ntohl((u32)m_tMsg.tHandle.pAppChanOrRas);
	}
	//��Ϣͷ����ת��Ϊ������
	void	HostToNet()
	{
		m_tMsg.dwHeader = htonl(m_tMsg.dwHeader);
		m_tMsg.wMsgId = htons(m_tMsg.wMsgId);
		m_tMsg.wMsgLen = htons(m_tMsg.wMsgLen);
		m_tMsg.wBodyLen = htons(m_tMsg.wBodyLen);
		m_tMsg.wSrcId = htons(m_tMsg.wSrcId);
		m_tMsg.tHandle.dwHsCall = htonl(m_tMsg.tHandle.dwHsCall);
		m_tMsg.tHandle.dwHsChanOrRas = htonl(m_tMsg.tHandle.dwHsChanOrRas);
		m_tMsg.tHandle.pAppCall = (void*)htonl((u32)m_tMsg.tHandle.pAppCall);
		m_tMsg.tHandle.pAppChanOrRas = (void*)htonl((u32)m_tMsg.tHandle.pAppChanOrRas);
	}
protected:
	TMTMSG	m_tMsg;			//��Ϣ����
};

//�ֽ�����ת���ṹ,��MTMSG����Ϣ����Ϊ�ṹ����ʱ,CStructAdapter�ṩ�ֽ�
//���е�ת������
class CStructAdapter
{
public:
	enum StructType
	{
		ST_NONE,		//��Ч�ṹ����
		ST_TERCFG,		//������Ϣ����
		ST_NETCFG,		//��������
		ST_DEVCFG,		//�豸����
		ST_OSDCFG,		//��ʾ����
		ST_CALLCFG,		//��������
		ST_VIDEOENC,	//��Ƶ����	
		ST_AUDIOENC,	//��Ƶ����
		ST_VIDEODEC,	//��Ƶ����
		ST_AUDIODEC,	//��Ƶ����	
		ST_DIALPARAM,	//���в���
		ST_TERSTATUS,	//�ն�״̬
		ST_NETADDR,		//�����ַ
		ST_VIDEOOUT,	//��Ƶ���	
		ST_SENDRT,		//�����ش�
		ST_RECVRT,		//�����ش�
		ST_SNAPINFO,	//������Ϣ
		ST_BITRATE,		//����������ϱ�
		ST_STATISTIC,	//�����ͳ���ϱ�
		ST_PANEL,		//��ý��
		ST_MNTSWT,		//����л�ģʽ
		ST_AUDIOPOWER,	//��Ƶ�����ϱ�
		ST_SERIAL,		// ����
		ST_DUALSTREAM,	// ˫��
		ST_TITLE,		// ��Ļ

		ST_ROUTE,       // ��Route 
		ST_ROUTE_TABLE, // ����Route��
		ST_E1,
		ST_PXY,
		ST_VIDEOPARAM

	};
public:
	CStructAdapter() 
	{
		m_pStruct = NULL;
		m_eType = ST_NONE;
	}
	CStructAdapter(void* pStruct,StructType eType) 
	{
		m_pStruct = pStruct;
		m_eType = eType;
	}

	//������ڲ���
	void SetStruct(void* pStruct,StructType eType)
	{
		m_pStruct = pStruct;
		m_eType = eType;
	}
	//������->������
	void HostToNet()
	{
		if (m_pStruct!=NULL && m_eType!=ST_NONE)
		{
			switch(m_eType) 
			{
			case ST_CALLCFG:		//��������
				{
					_PTCALLCFG ptCall = (_PTCALLCFG)m_pStruct;
					ptCall->wTtl = htons(ptCall->wTtl);
					ptCall->wAutoCallRate = htons( ptCall->wAutoCallRate );
				}
				break;

			case ST_NETCFG:			//��������
				{
					_PTNETCFG ptNet = (_PTNETCFG)m_pStruct;
					ptNet->wSendInitPort = htons(ptNet->wSendInitPort);
					ptNet->wRecvInitPort = htons(ptNet->wRecvInitPort);
					ptNet->dwUpBandWidth = htonl(ptNet->dwUpBandWidth);
					ptNet->dwDownBandWidth = htonl(ptNet->dwDownBandWidth);
				}
				break;

			case ST_DEVCFG:			//�豸����
				{
					_PTDEVCFG ptDev = (_PTDEVCFG)m_pStruct;
					//ptDev->dwIpAddr = htonl(ptDev->dwIpAddr);
					ptDev->wPort = htons(ptDev->wPort);
				}
				break;
			
			case ST_VIDEOENC:		//��Ƶ����
				{
					_PTVENCPARAM ptVEnc = (_PTVENCPARAM)m_pStruct;
					ptVEnc->vBitRate = htons(ptVEnc->vBitRate);
					ptVEnc->vBandWidth = htons(ptVEnc->vBandWidth);
					ptVEnc->vIKeyRate = htons( ptVEnc->vIKeyRate );
					ptVEnc->wH264IKeyRate = htons( ptVEnc->wH264IKeyRate );
				}
				break;

			case ST_AUDIOENC:		//��Ƶ����
				{
					_PTAENCPARAM ptAEnc = (_PTAENCPARAM)m_pStruct;
					ptAEnc->aBitRate = htons(ptAEnc->aBitRate );
				}
				break;

			case ST_VIDEODEC :		// ��Ƶ����
				{
					_PTVDECPARAM ptVDec = ( _PTVDECPARAM )m_pStruct;
					ptVDec->vBitRate = htons( ptVDec->vBitRate );
				}
				break;

			case ST_TERSTATUS:
				{
					_PTTERSTATUS ptStatus = (_PTTERSTATUS)m_pStruct;
					ptStatus->wSendBitRate[0] = htons(ptStatus->wSendBitRate[0]);
					ptStatus->wRecvBitRate[0] = htons(ptStatus->wRecvBitRate[0]);
					ptStatus->wSendBitRate[1] = htons(ptStatus->wSendBitRate[1]);
					ptStatus->wRecvBitRate[1] = htons(ptStatus->wRecvBitRate[1]);
					ptStatus->wSendAVBitRate = htons( ptStatus->wSendAVBitRate );
					ptStatus->wRecvAVBitRate = htons( ptStatus->wRecvAVBitRate );
					ptStatus->wSysSleep = htons( ptStatus->wSysSleep );
				}
				break;

			case ST_NETADDR:		//�����ַ
				{
					PTIPADDR pAddr = (PTIPADDR)m_pStruct;
					pAddr->port = htons(pAddr->port);
				}
				break;

			case ST_VIDEOOUT:		//��Ƶ���
				{
					_PTVOUT ptVout = (_PTVOUT)m_pStruct;
					ptVout->wVgaFs = htons(ptVout->wVgaFs);
				}
				break;

			case ST_SENDRT:		//�����ش�	
				{
					_PTSENDRTCFG ptSrt = (_PTSENDRTCFG)m_pStruct;
					ptSrt->wTimeOut = htons(ptSrt->wTimeOut);
				}
				break;

			case ST_RECVRT:		//�����ش�
				{
					_PTRECVRTCFG ptRrt = (_PTRECVRTCFG)m_pStruct;
					ptRrt->wCheckPoint1 = htons(ptRrt->wCheckPoint1);
					ptRrt->wCheckPoint2 = htons(ptRrt->wCheckPoint2);
					ptRrt->wCheckPoint3 = htons(ptRrt->wCheckPoint3);
					ptRrt->wTimeOut = htons(ptRrt->wTimeOut);
				}
				break;

			case ST_DIALPARAM :	// ���в���
				{
					_PTDIALPARAM ptDialParam = ( _PTDIALPARAM )m_pStruct;
					ptDialParam->wCallRate = htons( ptDialParam->wCallRate );
					ptDialParam->tConfInfo.wConfDuration = htons( ptDialParam->tConfInfo.wConfDuration );
				}
				break;

			case ST_SNAPINFO : // ������Ϣ
				{
					_PTSNAPINFO ptSnapInfo = ( _PTSNAPINFO )m_pStruct;
					ptSnapInfo->dwMaxSize = htonl( ptSnapInfo->dwMaxSize );
					ptSnapInfo->dwUsedSize = htonl( ptSnapInfo->dwUsedSize );
					ptSnapInfo->dwSnapPicNum = htonl( ptSnapInfo->dwSnapPicNum );
				}
				break;

			case ST_BITRATE : // ����������ϱ�
				{
					_PTBITRATE ptBitRate = ( _PTBITRATE )m_pStruct;
					ptBitRate->wSendBitRate = htons( ptBitRate->wSendBitRate );
					ptBitRate->wRecvBitRate = htons( ptBitRate->wRecvBitRate );
					ptBitRate->wSendAVBitRate = htons( ptBitRate->wSendAVBitRate );
					ptBitRate->wRecvAVBitRate = htons( ptBitRate->wRecvAVBitRate );
				}
				break;

			case ST_PANEL :		// ��ý��
				{
					_PTPANELCFG ptPanelCfg = ( _PTPANELCFG )m_pStruct;
					ptPanelCfg->wPort = htons( ptPanelCfg->wPort );

				}
				break;

			case ST_STATISTIC :			// codecͳ����Ϣ�ϱ�
				{
					_PTCODECSTATISTIC ptCodecStat = ( _PTCODECSTATISTIC )m_pStruct;
					ptCodecStat->wVideoBitRate = htons( ptCodecStat->wVideoBitRate );
					ptCodecStat->wAudioBitRate = htons( ptCodecStat->wAudioBitRate );
					ptCodecStat->wVideoLoseRatio = htons( ptCodecStat->wVideoLoseRatio );
					ptCodecStat->wAudioLoseRatio = htons( ptCodecStat->wAudioLoseRatio );
					ptCodecStat->dwVideoRecvFrm = htonl( ptCodecStat->dwVideoRecvFrm );
					ptCodecStat->dwAudioRecvFrm = htonl( ptCodecStat->dwAudioRecvFrm );
					ptCodecStat->dwVideoLoseFrm = htonl( ptCodecStat->dwVideoLoseFrm );
					ptCodecStat->dwAudioLoseFrm = htonl( ptCodecStat->dwAudioLoseFrm );
				}
				break;

			case ST_AUDIOPOWER :		// ��Ƶ�����ϱ�
				{
					_PTAUDIOPOWER ptAudioPwr = ( _PTAUDIOPOWER )m_pStruct;
					ptAudioPwr->dwOutputPower = htonl( ptAudioPwr->dwOutputPower );
					ptAudioPwr->dwInputPower = htonl( ptAudioPwr->dwInputPower );
				}
				break;

			case ST_MNTSWT :	// ����л�ģʽ
				{
					_PTMONITORSWITCH ptMntSwt = ( _PTMONITORSWITCH )m_pStruct;
					ptMntSwt->wTimeOut = htons( ptMntSwt->wTimeOut );
				}
				break;

			case ST_SERIAL :		// ����
				{
					_PTSERCFG ptSerialCfg = ( _PTSERCFG )m_pStruct;
					ptSerialCfg->dwBaudRate = htonl( ptSerialCfg->dwBaudRate );
				}
				break;

			case ST_DUALSTREAM :	// ˫������
				{
					_PTDUALSTREAM ptDualStr = ( _PTDUALSTREAM )m_pStruct;
					ptDualStr->tRecvAddr.port = htons( ptDualStr->tRecvAddr.port );
				}
				break;

			case ST_TITLE :		// ��Ļ
				{
					_PTTITLECFG ptTitleCfg = ( _PTTITLECFG )m_pStruct;
					ptTitleCfg->dwBkgClr = htonl( ptTitleCfg->dwBkgClr );
					ptTitleCfg->dwTextClr = htonl( ptTitleCfg->dwTextClr );
					ptTitleCfg->dwStartXPos = htonl( ptTitleCfg->dwStartXPos );
					ptTitleCfg->dwStartYPos = htonl( ptTitleCfg->dwStartYPos );
					ptTitleCfg->dwDisplayHeight = htonl( ptTitleCfg->dwDisplayHeight );
					ptTitleCfg->dwDisplayWidth = htonl( ptTitleCfg->dwDisplayWidth );
				}
				break;

			case ST_ROUTE:
				{
					PTIpRouteParam ptIpRoute = (PTIpRouteParam)m_pStruct;
					ptIpRoute->dwDesIpMask = htonl(ptIpRoute->dwDesIpMask);
					ptIpRoute->dwDesIpNet  = htonl(ptIpRoute->dwDesIpNet);
					ptIpRoute->dwGwIpAdrs  = htonl(ptIpRoute->dwGwIpAdrs);
					ptIpRoute->dwRoutePri  = htonl(ptIpRoute->dwRoutePri);

				}
				break;

			case ST_ROUTE_TABLE:
				{
					PTAllIpRouteInfo ptRoute = ( PTAllIpRouteInfo )m_pStruct;
					ptRoute->dwIpRouteNum = htonl(ptRoute->dwIpRouteNum);

					PTIpRouteParam ptRouteParam = NULL;
					for ( u8 byIndex = 0; byIndex < ROUTE_MAX_NUM; byIndex++ )
					{
						ptRouteParam = &ptRoute->tIpRouteParam[byIndex];
						if (ptRouteParam->byUsed)
						{
							ptRouteParam->dwDesIpMask = htonl(ptRouteParam->dwDesIpMask);
							ptRouteParam->dwDesIpNet  = htonl(ptRouteParam->dwDesIpNet);
							ptRouteParam->dwGwIpAdrs  = htonl(ptRouteParam->dwGwIpAdrs);
							ptRouteParam->dwRoutePri  = htonl(ptRouteParam->dwRoutePri);
						}
					}
				}

				break;
			case ST_E1:
				{
					PTE1ChanInfo ptE1Chan = (PTE1ChanInfo)m_pStruct;
					ptE1Chan->dwAuthenticationType = htonl(ptE1Chan->dwAuthenticationType);
					ptE1Chan->dwFragMinPackageLen  = htonl(ptE1Chan->dwFragMinPackageLen);
					ptE1Chan->dwIpAdrs             = htonl(ptE1Chan->dwIpAdrs);
					ptE1Chan->dwIpMask             = htonl(ptE1Chan->dwIpMask);

					PTE1ModuleInfo ptE1Module = NULL;
					for ( u8 byIndex = 0; byIndex < E1_MODULE_MAXNUM; byIndex++)
					{
						ptE1Module = &ptE1Chan->tE1ModuleInfo[byIndex];
						ptE1Module->dwE1TSMask = htonl(ptE1Module->dwE1TSMask);
						ptE1Module->dwEchoInterval = htonl(ptE1Module->dwEchoInterval);
						ptE1Module->dwEchoMaxRetry = htonl(ptE1Module->dwEchoMaxRetry);
						ptE1Module->dwProtocolType = htonl(ptE1Module->dwProtocolType);
						ptE1Module->dwUsedFlag = htonl(ptE1Module->dwUsedFlag);
					}

				}
				break;

			case ST_PXY:
				{
					PTPxyInfo ptPxy = (PTPxyInfo)m_pStruct;
					ptPxy->dwPxySrvIp = htonl(ptPxy->dwPxySrvIp);
					ptPxy->wPxySrvPort= htons(ptPxy->wPxySrvPort);
					ptPxy->wMediaPort = htons(ptPxy->wMediaPort);
				}
			default:
				break;
			}
		}
		m_eType = ST_NONE;
		m_pStruct = NULL;
	}

	//������->������
	void NetToHost()
	{
		if (m_pStruct!=NULL && m_eType!=ST_NONE)
		{
			switch(m_eType) 
			{
			case ST_CALLCFG:		//��������
				{
					_PTCALLCFG ptCall = (_PTCALLCFG)m_pStruct;
					ptCall->wTtl = ntohs(ptCall->wTtl);
					ptCall->wAutoCallRate = ntohs( ptCall->wAutoCallRate );
				}
				break;

			case ST_NETCFG:			//��������
				{
					_PTNETCFG ptNet = (_PTNETCFG)m_pStruct;
					ptNet->wSendInitPort = ntohs(ptNet->wSendInitPort);
					ptNet->wRecvInitPort = ntohs(ptNet->wRecvInitPort);
					ptNet->dwUpBandWidth = ntohl(ptNet->dwUpBandWidth);
					ptNet->dwDownBandWidth = ntohl(ptNet->dwDownBandWidth);
				}
				break;

			case ST_DEVCFG:			//�豸����
				{
					_PTDEVCFG ptDev = (_PTDEVCFG)m_pStruct;
					//ptDev->dwIpAddr = ntohl(ptDev->dwIpAddr);
					ptDev->wPort = ntohs(ptDev->wPort);
				}
				break;


			case ST_VIDEOENC:		//��Ƶ����
				{
					_PTVENCPARAM ptVEnc = (_PTVENCPARAM)m_pStruct;
					ptVEnc->vBitRate = ntohs(ptVEnc->vBitRate);
					ptVEnc->vBandWidth = ntohs(ptVEnc->vBandWidth);
					ptVEnc->vIKeyRate = ntohs( ptVEnc->vIKeyRate );
					ptVEnc->wH264IKeyRate = ntohs( ptVEnc->wH264IKeyRate );
				}
				break;

			case ST_AUDIOENC:		//��Ƶ����
				{
					_PTAENCPARAM ptAEnc = (_PTAENCPARAM)m_pStruct;
					ptAEnc->aBitRate = ntohs(ptAEnc->aBitRate );
				}
				break;

			case ST_VIDEODEC :		// ��Ƶ����
				{
					_PTVDECPARAM ptVDec = ( _PTVDECPARAM )m_pStruct;
					ptVDec->vBitRate = ntohs( ptVDec->vBitRate );
				}
				break;


			case ST_TERSTATUS:
				{
					_PTTERSTATUS ptStatus = (_PTTERSTATUS)m_pStruct;
					ptStatus->wSendBitRate[0] = ntohs(ptStatus->wSendBitRate[0]);
					ptStatus->wRecvBitRate[0] = ntohs(ptStatus->wRecvBitRate[0]);
					ptStatus->wSendBitRate[1] = ntohs(ptStatus->wSendBitRate[1]);
					ptStatus->wRecvBitRate[1] = ntohs(ptStatus->wRecvBitRate[1]);
					ptStatus->wSendAVBitRate = ntohs( ptStatus->wSendAVBitRate );
					ptStatus->wRecvAVBitRate = ntohs( ptStatus->wRecvAVBitRate );
					ptStatus->wSysSleep = ntohs( ptStatus->wSysSleep );
				}
				break;

			case ST_NETADDR:		//�����ַ
				{
					PTIPADDR pAddr = (PTIPADDR)m_pStruct;
					pAddr->port = ntohs(pAddr->port);
				}
				break;
				
			case ST_VIDEOOUT:		//��Ƶ���
				{
					_PTVOUT ptVout = (_PTVOUT)m_pStruct;
					ptVout->wVgaFs = ntohs(ptVout->wVgaFs);
				}
				break;

			case ST_SENDRT:		//�����ش�	
				{
					_PTSENDRTCFG ptSrt = (_PTSENDRTCFG)m_pStruct;
					ptSrt->wTimeOut = ntohs(ptSrt->wTimeOut);
				}
				break;

			case ST_RECVRT:		//�����ش�
				{
					_PTRECVRTCFG ptRrt = (_PTRECVRTCFG)m_pStruct;
					ptRrt->wCheckPoint1 = ntohs(ptRrt->wCheckPoint1);
					ptRrt->wCheckPoint2 = ntohs(ptRrt->wCheckPoint2);
					ptRrt->wCheckPoint3 = ntohs(ptRrt->wCheckPoint3);
					ptRrt->wTimeOut = ntohs(ptRrt->wTimeOut);
				}
				break;

			case ST_DIALPARAM :	// ���в���
				{
					_PTDIALPARAM ptDialParam = ( _PTDIALPARAM )m_pStruct;
					ptDialParam->wCallRate = ntohs( ptDialParam->wCallRate );
					ptDialParam->tConfInfo.wConfDuration = ntohs( ptDialParam->tConfInfo.wConfDuration );
				}
				break;

			case ST_SNAPINFO : // ������Ϣ
				{
					_PTSNAPINFO ptSnapInfo = ( _PTSNAPINFO )m_pStruct;
					ptSnapInfo->dwMaxSize = ntohl( ptSnapInfo->dwMaxSize );
					ptSnapInfo->dwUsedSize = ntohl( ptSnapInfo->dwUsedSize );
					ptSnapInfo->dwSnapPicNum = ntohl( ptSnapInfo->dwSnapPicNum );
				}
				break;

			case ST_BITRATE : // ����������ϱ�
				{
					_PTBITRATE ptBitRate = ( _PTBITRATE )m_pStruct;
					ptBitRate->wSendBitRate = ntohs( ptBitRate->wSendBitRate );
					ptBitRate->wRecvBitRate = ntohs( ptBitRate->wRecvBitRate );
					ptBitRate->wSendAVBitRate = ntohs( ptBitRate->wSendAVBitRate );
					ptBitRate->wRecvAVBitRate = ntohs( ptBitRate->wRecvAVBitRate );
				}
				break;

			case ST_PANEL :		// ��ý��
				{
					_PTPANELCFG ptPanelCfg = ( _PTPANELCFG )m_pStruct;
					ptPanelCfg->wPort = ntohs( ptPanelCfg->wPort );
				}
				break;

			case ST_STATISTIC :			// codecͳ����Ϣ�ϱ�
				{
					_PTCODECSTATISTIC ptCodecStat = ( _PTCODECSTATISTIC )m_pStruct;
					ptCodecStat->wVideoBitRate = ntohs( ptCodecStat->wVideoBitRate );
					ptCodecStat->wAudioBitRate = ntohs( ptCodecStat->wAudioBitRate );
					ptCodecStat->wVideoLoseRatio = ntohs( ptCodecStat->wVideoLoseRatio );
					ptCodecStat->wAudioLoseRatio = ntohs( ptCodecStat->wAudioLoseRatio );
					ptCodecStat->dwVideoRecvFrm = ntohl( ptCodecStat->dwVideoRecvFrm );
					ptCodecStat->dwAudioRecvFrm = ntohl( ptCodecStat->dwAudioRecvFrm );
					ptCodecStat->dwVideoLoseFrm = ntohl( ptCodecStat->dwVideoLoseFrm );
					ptCodecStat->dwAudioLoseFrm = ntohl( ptCodecStat->dwAudioLoseFrm );
				}
				break;
				
			case ST_AUDIOPOWER :		// ��Ƶ�����ϱ�
				{
					_PTAUDIOPOWER ptAudioPwr = ( _PTAUDIOPOWER )m_pStruct;
					ptAudioPwr->dwOutputPower = ntohl( ptAudioPwr->dwOutputPower );
					ptAudioPwr->dwInputPower = ntohl( ptAudioPwr->dwInputPower );
				}
				break;

			case ST_MNTSWT :	// ����л�ģʽ
				{
					_PTMONITORSWITCH ptMntSwt = ( _PTMONITORSWITCH )m_pStruct;
					ptMntSwt->wTimeOut = ntohs( ptMntSwt->wTimeOut );
				}
				break;

			case ST_SERIAL :	// ����
				{
					_PTSERCFG ptSerialCfg = ( _PTSERCFG )m_pStruct;
					ptSerialCfg->dwBaudRate = ntohl( ptSerialCfg->dwBaudRate );
				}
				break;

			case ST_DUALSTREAM :	// ˫������
				{
					_PTDUALSTREAM ptDualStr = ( _PTDUALSTREAM )m_pStruct;
					ptDualStr->tRecvAddr.port = ntohs( ptDualStr->tRecvAddr.port );
				}
				break;

			case ST_TITLE :			// ��Ļ
				{
					_PTTITLECFG ptTitleCfg = ( _PTTITLECFG )m_pStruct;
					ptTitleCfg->dwBkgClr = ntohl( ptTitleCfg->dwBkgClr );
					ptTitleCfg->dwTextClr = ntohl( ptTitleCfg->dwTextClr );
					ptTitleCfg->dwStartXPos = ntohl( ptTitleCfg->dwStartXPos );
					ptTitleCfg->dwStartYPos = ntohl( ptTitleCfg->dwStartYPos );
					ptTitleCfg->dwDisplayHeight = ntohl( ptTitleCfg->dwDisplayHeight );
					ptTitleCfg->dwDisplayWidth = ntohl( ptTitleCfg->dwDisplayWidth );
				}
				break;

			case ST_E1:
				{
					PTE1ChanInfo ptE1Chan = (PTE1ChanInfo)m_pStruct;
					ptE1Chan->dwAuthenticationType = ntohl(ptE1Chan->dwAuthenticationType);
					ptE1Chan->dwFragMinPackageLen  = ntohl(ptE1Chan->dwFragMinPackageLen);
					ptE1Chan->dwIpAdrs             = ntohl(ptE1Chan->dwIpAdrs);
					ptE1Chan->dwIpMask             = ntohl(ptE1Chan->dwIpMask);

					PTE1ModuleInfo ptE1Module = NULL;
					for ( u8 byIndex = 0; byIndex < E1_MODULE_MAXNUM; byIndex++)
					{
						ptE1Module = &ptE1Chan->tE1ModuleInfo[byIndex];
						ptE1Module->dwE1TSMask = ntohl(ptE1Module->dwE1TSMask);
						ptE1Module->dwEchoInterval = ntohl(ptE1Module->dwEchoInterval);
						ptE1Module->dwEchoMaxRetry = ntohl(ptE1Module->dwEchoMaxRetry);
						ptE1Module->dwProtocolType = ntohl(ptE1Module->dwProtocolType);
						ptE1Module->dwUsedFlag = ntohl(ptE1Module->dwUsedFlag);
					}
					
				}
				break;
			case ST_ROUTE:
				{
					PTIpRouteParam ptRouteParam = ( PTIpRouteParam )m_pStruct;
					ptRouteParam->dwDesIpMask = ntohl(ptRouteParam->dwDesIpMask);
					ptRouteParam->dwDesIpNet  = ntohl(ptRouteParam->dwDesIpNet);
					ptRouteParam->dwGwIpAdrs  = ntohl(ptRouteParam->dwGwIpAdrs);
					ptRouteParam->dwRoutePri  = ntohl(ptRouteParam->dwRoutePri);
				}
				break;

			case ST_ROUTE_TABLE:
				{
					PTAllIpRouteInfo ptRoute = ( PTAllIpRouteInfo )m_pStruct;
					ptRoute->dwIpRouteNum = ntohl(ptRoute->dwIpRouteNum);

					PTIpRouteParam ptRouteParam = NULL;
					for ( u8 byIndex = 0; byIndex < ROUTE_MAX_NUM; byIndex++ )
					{
						ptRouteParam = &ptRoute->tIpRouteParam[byIndex];
						if (ptRouteParam->byUsed)
						{
							ptRouteParam->dwDesIpMask = ntohl(ptRouteParam->dwDesIpMask);
							ptRouteParam->dwDesIpNet  = ntohl(ptRouteParam->dwDesIpNet);
							ptRouteParam->dwGwIpAdrs  = ntohl(ptRouteParam->dwGwIpAdrs);
							ptRouteParam->dwRoutePri  = ntohl(ptRouteParam->dwRoutePri);
						}
					}
				}
				break;

			case ST_PXY:
				{
					PTPxyInfo ptPxy = (PTPxyInfo)m_pStruct;
					ptPxy->dwPxySrvIp = ntohl(ptPxy->dwPxySrvIp);
					ptPxy->wPxySrvPort= ntohs(ptPxy->wPxySrvPort);
					ptPxy->wMediaPort = ntohs(ptPxy->wMediaPort);
				}
			default:
				break;
			}
		}
		m_eType = ST_NONE;
		m_pStruct = NULL;
	}

protected:
	void*		m_pStruct;
	StructType  m_eType;
};

//////////////////////////////////////////////////////////////////////////
// �����ļ�����Э����Ϣͷ����
typedef struct tagFileTransfer
{
public :
	// ���ð汾��
	void SetVersion( u16 wVer ) { wVersion = htons( wVer ) ; }
	u16	 GetVersion()	{ return ntohs( wVersion ); }
	
	// ����Э����
	void SetProtocolNo( u16 wNo ) { wProtocolNo = htons( wNo ); }
	u16  GetProtocolNo()	{ return ntohs( wProtocolNo ); }
	
	// ������Ϣ����
	void SetMsgType( u8 byMsgType ) { byType = byMsgType; }
	u8	 GetMsgType()	{ return byType; }

	// ����ԭ��
	void SetReason( u8 byReason ) { byNackReason = byReason; }
	u8   GetReason() { return byNackReason; }

	// �����û�����������
	void SetDataLen( u16 wLen ) { wDataLen = htons( wLen ); }
	u16  GetDataLen() { return ntohs( wDataLen ); }

	void Reset()
	{
		SetVersion( MTC_MT_FILE_VER );
		SetProtocolNo( MTC_MT_MSG_BGN );
		byType = 0;
		byNackReason = 0;
		wDataLen = 0;
	}

private :
	u16		wVersion;			// �汾��		0x0100
	u16		wProtocolNo;		// Э����		0��ʼ���
	u8		byType;				// ��Ϣ����		̨��,������Ϣ,��Ļ
	u8		byNackReason;		// ԭ��
	u16		wDataLen;			// �û����ݳ���
}PACKED _TFILETRANSFER,*_PTFILETRANSFER;

// MT��ӡ
API void MtPrintf( BOOL bScreen, BOOL bFile, char* format, ... );

//==================================================================================
//									���Ժ궨��
//==================================================================================
#define TRACE_CALLIN( lev, fun, str ) \
	if ( lev > 0 ) \
	MtPrintf( TRUE, FALSE, "[TRACE]Calling \"%s\" in file \"%s\"on Ln%d(%s)\n", fun, __FILE__, __LINE__, str );

#define TRACE_CALLOUT( lev, fun, str ) \
	if ( lev > 0 ) \
	MtPrintf( TRUE, FALSE, "[TRACE]Leaving \"%s\" in file \"%s\"on Ln%d(%s)\n", fun, __FILE__, __LINE__, str );

// ָ���ж�
#define MT_ASSERT( p ) if ( p == NULL ) { MtPrintf( TRUE, FALSE, "[SYSTEM]Invalid Pointer(%s:(%d))!\n", __FILE__, __LINE__ ); return; }
#define MT_ASSERT_RET( p, ret ) if ( p == NULL ) { MtPrintf( TRUE, FALSE, "[SYSTEM]Invalid Pointer(%s:(%d))!\n", __FILE__, __LINE__ ); return ret; }

// �ͷ��ڴ�
#define MT_SAFE_DELETE( p ) if ( p != NULL ) { delete p; p = NULL; }
#define MT_SAFE_DELETE_ARRAY( p ) if ( p != NULL ) { delete []p; p = NULL; }

// ��Ч���ж�
#define MT_MAXVALUE_INVALID( val, maxVal ) if ( val > maxVal ) { MtPrintf( TRUE, FALSE, "[SYSTEM]Invalid value(%s:(%d))!\n", __FILE__, __LINE__ ); return; } 
#define MT_MAXVALUE_INVALID_RET( val, maxVal, ret ) if ( val > maxVal ) { MtPrintf( TRUE, FALSE, "[SYSTEM]Invalid value(%s:(%d))!\n", __FILE__, __LINE__ ); return ret; } 

#define MT_MINVALUE_INVALID( val, minVal ) if ( val < minVal ) { MtPrintf( TRUE, FALSE, "[SYSTEM]Invalid value(%s:(%d))!\n", __FILE__, __LINE__ ); return; } 
#define MT_MINVALUE_INVALID_RET( val, minVal, ret ) if ( val < minVal ) { MtPrintf( TRUE, FALSE, "[SYSTEM]Invalid value(%s:(%d))!\n", __FILE__, __LINE__ ); return ret; } 

// length check(������Ϣ���г��ȵļ��)
#define MT_LEN_CHECK( actLen, expLen ) if ( actLen != expLen ) { MtPrintf( TRUE, FALSE, "[SYSTEM]Len Mismatch(%s:(%d))!\n", __FILE__, __LINE__ ); return; }

// ������Ϣ��ӡ
#define MT_ERROR_PRT( actVal, expVal, hint, errorno ) if ( actVal != expVal ) { MtPrintf( TRUE, FALSE, hint, errorno ); return FALSE; }




#endif