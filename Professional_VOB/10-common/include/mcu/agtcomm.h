/*****************************************************************************
   ģ����      : 
   �ļ���      : agtcomm.h
   ����ļ�    : 
   �ļ�ʵ�ֹ���: MCU MT ����궨��
   ����        : 
   �汾        : V4.0  Copyright( C) 2006-2008 KDC, All rights reserved.
-----------------------------------------------------------------------------
   �޸ļ�¼:
   ��  ��      �汾        �޸���        �޸�����
   2006/11/16  4.0         �ű���        ��������
******************************************************************************/
#if !defined( _AGENT_COMMON_H_ )
#define _AGENT_COMMON_H_ 

#include "kdvsys.h"

//�����ð汾�ŵĶ�����汾�����������
#define MCUAGT_SYS_CFGVER               "20080701-4.0R5"

/*MT��Ӳ������*/
enum  
{
	TYPE_PC		= 1,
	TYPE_EMBED	= 2
};

/*�ն�����*/
enum
{
	TYPE_RECV_AND_SND,
	TYPE_RECV_ONLY,
	TYPE_SND_ONLY
};

/*�ն˵�λ*/
enum
{
	POSITION_MASTER		=1,
	POSITION_SLARE		=2,
	POSITION_AUDIT		=3
};

/*���������뷽ʽ*/
enum
{
	MODE_SOFTWARE_DECODE		=1,
	MODE_HARDWARE_DECODE		=2,
	MODE_SOFTWARE_AND_HARDWARE	=3
};

/*�������ɼ���ʽ*/
enum
{
	MODE_SOFTWARE		=1,
	MODE_HARDWARE		=2
};


/*����ɼ����ݸ�ʽ*/
enum
{
	FORMAT_RGB		=1,
	FORMAT_Yuv422	=2
};

/*��Ƶ�����Ƿ�ʹ��Overlay*/
enum
{
	OVERLAY_ENABLE	=1,
	OVERLAY_DISABLE =2,
};

/*������������*/
enum
{
	AEC_ENABLE		=1,
	AEC_DISABLE		=2
};

/*����״̬*/
enum
{
	TASK_NORMAL		=0,
	TASK_BUSY		=1
};

/*��ƵԴ״̬*/
enum
{
	VIDEOSOURCE_NORMAL		=0,
	VIDEOSOURCE_ABNORMAL    =1,
};

/*ͬ��Դ״̬*/
enum
{
	SYNCSOURCE_NORMAL		=0,
	SYNCSOURCE_ABNORMAL     =1,
};

/*ͬ��Դ����״̬*/
enum
{
	SYNC_FREERUN	= 1,
	SYNC_TRACE_2M	= 2,
};

enum
{
	APP_TYPE_CONF  =1,
	APP_TYPE_APPLY =2
};

#define SYNCMODE_LIBERAL						(u8)1   /* ������ģʽ */
#define SYNCMODE_EXTERNAL						(u8)2   /* �ⲿʱ��Դģʽ */

#define MAX_BOARD_COUNT							60
#define RESET_BRD								2       /* nms reboot board */

#define MAX_BRD_NUM								16
#define MCU_SLOT_NUM                        	17      /* mcu����Ŀ */

#define CONF_STATE_START		            	1       /*���鿪ʼ*/
#define CONF_STATE_STOP			            	2       /*�������*/

#define CONF_ADD_TERMINAL		            	1       /*���������ն�*/
#define CONF_DEL_TERMINAL		            	2       /*����ɾ���ն�*/

// ����״̬(�����ڲ�)
#define BOARD_STATUS_INLINE                 	(u8)0   /* 0������ */
#define BOARD_STATUS_DISCONNECT             	(u8)1   /* 1������ */
#define BOARD_STATUS_CFGCONFLICT            	(u8)2   /* 2�����ó�ͻ */
#define BOARD_STATUS_UNKNOW                 	(u8)3   /* 3������δ֪(��ʼ״̬) */

#define KDV_READ_COMMUNITYSTRING            	(LPCSTR)"public"
#define KDV_WRITE_COMMUNITYSTRING           	(LPCSTR)"kdv123"

/*MPC ��״̬*/
#define  MCU_STATE_RUNNING                  	(u8)1   /* ����״̬ */
#define  MCU_STATE_REBOOT                   	(u8)2   /* ����״̬ */
#define  MCU_STATE_STANDY                   	(u8)3   /* ����״̬ */
#define  MPC_COLD_START                     	(u8)4   /* Mpc �������� */
#define  MPC_POWER_OFF                      	(u8)5   /* Mpc ��ػ� */
#define  MCU_STATE_UNKNOW                   	(u8)10  /* δ֪״̬  */

#define NMS_TEST_START                      	(u8)1   /* test */
#define NMS_TEST_STOP                       	(u8)2

/* ���ܻ���һ������ϴ��ļ��� */
#define MAXNUM_FILE_UPDATE						(u8)16	

//����BoardWrapper.h��brddrvlib.h����������ͻ�����������ﵥ�����壬����Ҫ��BoardWrapper.h�б���һ��
#define DSL8000_BRD_HDSC                    	0x14     /* HDSC�� */

/*------------------------------------------------------------- 
/*define max table items
*-------------------------------------------------------------*/
#define MAX_mcunetTrapRcvEntry_NUM          	10
#define MAX_mcunetPeriEqpEntry_NUM          	16
#define MAX_mcunetSubMcuEntry_NUM           	32
#define MAX_mcunetMp4SubMcuEntry_NUM        	32
#define MAX_mcunetSubMtEntry_NUM            	128
#define MAX_mcunetMp4SubMtEntry_NUM         	128
#define MAX_mcueqpDtiEntry_NUM              	16
#define MAX_mcueqpE1Entry_NUM               	MAX_mcueqpDtiEntry_NUM * 8
#define MAX_mcueqpTsEntry_NUM               	MAX_mcueqpE1Entry_NUM * 32
#define MAX_mcueqpNscuEntry_NUM             	2
#define MAX_mcueqpSwitchEntry_NUM           	16

/*------------------------------------------------------------- 
/* ����������ת������ֵ������2000תΪ������С��2000�����澯
*-------------------------------------------------------------*/
#define MIN_MCU8000ABOXFAN_SPEED                2000

/*------------------------------------------------------------- 
/* ����MCU8000A������ȸ���
*-------------------------------------------------------------*/
#define MCU8000ABOXFAN_NUM                      8    

/*------------------------------------------------------------- 
*VCS�鳣�� 
*-------------------------------------------------------------*/
#define SECTION_mcuVCS                       (const s8*)"mcuVCS"
#define KEY_mcuVCSSoftName                   (const s8*)"mcuVCSSoftName"

/*------------------------------------------------------------- 
*ϵͳ�鳣�� 
*-------------------------------------------------------------*/
#define SECTION_mcuSystem                       (const s8*)"mcuSystem"
#define KEY_mcusysConfigVersion                 (const s8*)"mcusysConfigVersion"
#define KEY_mcuIsConfiged                       (const s8*)"mcuIsConfiged"

/*------------------------------------------------------------- 
*������Ϣ���� 
*-------------------------------------------------------------*/
#define SECTION_mcuLocalInfo	                (const s8*)"mcuLocalInfo"
#define KEY_mucId				                (const s8*)"mcuId"
#define KEY_mcuAlias			                (const s8*)"mcuAlias"
#define KEY_mcuE164Number		                (const s8*)"mcuE164Number"
#define KEY_mcuMmcuNeedBAS		                (const s8*)"mcuMmcuNeedBAS"
#define KEY_mcuCheckMtLinkTimes                 (const s8*)"mcuCheckLinkTimes"
#define Key_mcuCheckLinkTime                    (const s8*)"mcuCheckLinkTime"
#define Key_mcuRefreshListTime                  (const s8*)"mcuRefreshListTime"
#define Key_mcuAudioRefreshTime                 (const s8*)"mcuAudioRefreshTime"
#define Key_mcuVideoRefreshTime                 (const s8*)"mcuVideoRefreshTime"
#define Key_mcuIsSaveBand                       (const s8*)"mcuIsSaveBand"
#define Key_mcuIsNPlusMode                      (const s8*)"mcuIsNPlusMode"
#define Key_mcuIsNPlusBackupMode                (const s8*)"mcuIsNPlusBackupMode"
#define Key_mcuNPlusMcuIp                       (const s8*)"mcuNPlusMcuIp"
#define Key_mcuNPlusRtdTime                     (const s8*)"mcuNPlusRtdTime"
#define Key_mcuNPlusRtdNum                      (const s8*)"mcuNPlusRtdNum"
#define Key_mcuIsNPlusRollBack                  (const s8*)"mcuIsNPlusRollBack"
#define Key_mcuMsSynTime						(const s8*)"mcuMsSynTime"
#define key_mcuIsHoldDefaultConf				(const s8*)"mcuIsHoldDefaultConf"
#define key_mcuIsShowMMcuMtList					(const s8*)"mcuIsShowMMcuMtList"
#define key_mcuMaxMcsOnGoingConfNum				(const s8*)"mcuMaxMcsOnGoingConfNum"
#define key_mcuAdminLevel						(const s8*)"mcuAdminLevel"
#define key_mcuLocalConfNameShowType			(const s8*)"mcuLocalConfNameShowType"
#define key_mcuIsMMcuSpeaker					(const s8*)"mcuIsMMcuSpeaker"

/*------------------------------------------------------------- 
*����ʱȱʡ���ն��б��� 
*-------------------------------------------------------------*/
#define SECTION_mcuTerminalIpTable		        (const s8*)"mcuTerminalIpTable"
#define FIELD_mcuTerminalIpEntIpAddr	        (const s8*)"mcuTerminalIpEntIpAddr"


/*------------------------------------------------------------- 
*�����鳣�� 
*-------------------------------------------------------------*/
#define SECTION_mcuNetwork			            (const s8*)"mcuNetwork"
#define KEY_mcunetGKIpAddr			            (const s8*)"mcunetGKIpAddr"
#define KEY_mcunetGKCharge                      (const s8*)"mcunetGKCharge"
#define KEY_mcunetRRQMtadpIp                    (const s8*)"mcunetRRQMtadpIp"
#define KEY_mcunetMulticastIpAddr	            (const s8*)"mcunetMulticastIpAddr"
#define KEY_mcunetMulticastPort		            (const s8*)"mcunetMulticastPort"
#define KEY_mcunetRecvStartPort		            (const s8*)"mcunetRecvStartPort"
#define KEY_mcunet225245StartPort               (const s8*)"mcunet225245StartPort"
#define KEY_mcunet225245MtNum                   (const s8*)"mcunet225245MtNum"
#define KEY_mcunetMTUSize						(const s8*)"mcunetMTUSize"
#define KEY_mcunetMTUSetupMode					(const s8*)"mcunetMTUSetupMode"
#define KEY_mcunetUseMPCTransData               (const s8*)"mcunetUseMPCTransData"
#define KEY_mcunetUseMPCStack	                (const s8*)"mcunetUseMPCStack"
	
/*------------------------------------------------------------- 
*GK/Proxy���ñ���		 
*-------------------------------------------------------------*/
#define SECTION_mcuGkProxyCfg					(const s8*)"mcuGkProxyCfg"
#define KEY_mcuGkUsed							(const s8*)"GkUsed"
#define KEY_mcuProxyUsed						(const s8*)"ProxyUsed"
#define KEY_mcuGkIpAddr							(const s8*)"GkIpAddr"
#define KEY_mcuProxyIpAddr						(const s8*)"ProxyIpAddr"
#define	KEY_mcuProxyPort						(const s8*)"ProxyPort"


/*------------------------------------------------------------- 
*prs time span����		 
*-------------------------------------------------------------*/
#define SECTION_mcuPrsTimeSpan					(const s8*)"mcuPrsTimeSpan"
#define KEY_mcuPrsSpan1							(const s8*)"span1"
#define KEY_mcuPrsSpan2							(const s8*)"span2"
#define KEY_mcuPrsSpan3							(const s8*)"span3"
#define KEY_mcuPrsSpan4							(const s8*)"span4"

/*------------------------------------------------------------- 
*TRAP���������� 
*-------------------------------------------------------------*/
#define SECTION_mcunetTrapRcvTable              (const s8*)"mcunetTrapRcvTable"
#define FIELD_mcunetTrapRcvEntIpAddr            (const s8*)"mcunetTrapRcvEntIpAddr"
#define FIELD_mcunetTrapRcvEntRCommunity        (const s8*)"mcunetTrapRcvRCommunity"
#define FIELD_mcunetTrapRevEntWCommunity        (const s8*)"mcunetTrapRcvWCommunity"
#define FIELD_mcunetTrapGetSetPort              (const s8*)"mcunetTrapRcvGetSetPort"   
#define FIELD_mcunetTrapSendTrapPort            (const s8*)"mcunetTrapRcvSendTrapPort"

/*------------------------------------------------------------- 
*������� 
*-------------------------------------------------------------*/
#define SECTION_mcueqpBoardConfig		        (const s8*)"mcueqpBoardConfig"
#define FIELD_mcueqpBoardId				        (const s8*)"mcueqpBoardId"
#define FIELD_mcueqpBoardLayer			        (const s8*)"mcueqpBoardLayer"
#define FIELD_mcueqpBoardSlot			        (const s8*)"mcueqpBoardSlot"
#define FIELD_mcueqpBoardType			        (const s8*)"mcueqpBoardType"
#define FIELD_mcueqpBoardIpAddr			        (const s8*)"mcueqpBoardIpAddr"
#define FIELD_mcueqpBoardPortChoice             (const s8*)"mcueqpBoardPortChoice"
#define FIELD_mcueqpBoardCastChoice             (const s8*)"mcueqpBoardCastChoice"

// ��ͬ������ 
#define SECTION_mcueqpNetSync				    (const s8*)"mcueqpNetSync"
#define KEY_mcueqpNetSyncMode				    (const s8*)"mcueqpNetSyncMode"
#define KEY_mcueqpNetSyncDTSlot				    (const s8*)"mcueqpNetSyncDTSlot"
#define KEY_mcueqpNetSyncE1Index			    (const s8*)"mcueqpNetSyncE1Index"
#define KEY_mcueqpNetSyncSource				    (const s8*)"mcueqpNetSyncSource"
#define KEY_mcueqpNetSyncClock				    (const s8*)"mcueqpNetSyncClock"
	

// ���������� 
#define SECTION_mcueqpMixerTable			    (const s8*)"mcueqpMixerTable"
#define FIELD_mcueqpMixerEntId				    (const s8*)"mcueqpMixerEntId"
#define FIELD_mcueqpMixerEntPort			    (const s8*)"mcueqpMixerEntPort"
#define FIELD_mcueqpMixerEntSwitchBrdId		    (const s8*)"mcueqpMixerEntSwitchBrdId"
#define FIELD_mcueqpMixerEntAlias			    (const s8*)"mcueqpMixerEntAlias"
#define FIELD_mcueqpMixerEntRunningBrdId	    (const s8*)"mcueqpMixerEntRunningBrdId"
#define FIELD_mcueqpMixerEntMixStartPort	    (const s8*)"mcueqpMixerEntMixStartPort"
#define FIELD_mcueqpMixerEntMaxMixGroupNum      (const s8*)"mcueqpMixerEntMaxMixGroupNum"
#define FIELD_mcueqpMixerEntMaxChannelInGrp     (const s8*)"mcueqpMixerEntMaxChannelInGrp"
#define FIELD_mcueqpMixerEntMapId			    (const s8*)"mcueqpMixerEntMapId"
#define FIELD_mcueqpMixerEntMixSendRedundancy	(const s8*)"mcueqpMixerEntMixSendRedundancy"

// ���ֻ���������������� 
#define SECTION_mcueqpDataConfServer		    (const s8*)"mcueqpDataConfServer"
#define KEY_mcueqpDcsIp						    (const s8*)"mcueqpDcsIp"
#define KEY_mcueqpDcsId                         (const s8*)"mcueqpDcsId"


// �š�¼������� 
#define SECTION_mcueqpRecorderTable				(const s8*)"mcueqpRecorderTable"
#define FIELD_mcueqpRecorderEntId				(const s8*)"mcueqpRecorderEntId"
#define FIELD_mcueqpRecorderEntPort				(const s8*)"mcueqpRecorderEntPort"
#define FIELD_mcueqpRecorderEntSwitchBrdId		(const s8*)"mcueqpRecorderEntSwitchBrdId"
#define FIELD_mcueqpRecorderEntAlias			(const s8*)"mcueqpRecorderEntAlias"
#define FIELD_mcueqpRecorderEntIpAddr			(const s8*)"mcueqpRecorderEntIpAddr"
#define FIELD_mcueqpRecorderEntRecvStartPort	(const s8*)"mcueqpRecorderEntRecvStartPort"
#define FIELD_mcueqpRecorderEntRecChannelNum	(const s8*)"mcueqpRecorderEntRecChannelNum"
#define FIELD_mcueqpRecorderEntPlayChannelNum	(const s8*)"mcueqpRecorderEntPlayChannelNum"


// ����ǽ���� 
#define SECTION_mcueqpTVWallTable			    (const s8*)"mcueqpTVWallTable"
#define FIELD_mcueqpTVWallEntId				    (const s8*)"mcueqpTVWallEntId"
#define FIELD_mcueqpTVWallEntAlias			    (const s8*)"mcueqpTVWallEntAlias"
#define FIELD_mcueqpTVWallEntRunningBrdId       (const s8*)"mcueqpTVWallEntRunningBrdId"
#define FIELD_mcueqpTVWallEntRecvStartPort      (const s8*)"mcueqpTVWallEntRecvStartPort"
#define FIELD_mcueqpTVWallEntDivStyle		    (const s8*)"mcueqpTVWallEntDivStyle"
#define FIELD_mcueqpTVWallEntDivNum			    (const s8*)"mcueqpTVWallEntDivNum"
#define FIELD_mcueqpTVWallEntMapId			    (const s8*)"mcueqpTVWallEntMapId"

// �������������� 
#define SECTION_mcueqpBasTable			        (const s8*)"mcueqpBasTable"
#define SECTION_mcueqpBasHDTable			    (const s8*)"mcueqpBasHDTable"
#define FIELD_mcueqpBasEntId			        (const s8*)"mcueqpBasEntId"
#define FIELD_mcueqpBasEntPort			        (const s8*)"mcueqpBasEntPort"
#define FIELD_mcueqpBasEntSwitchBrdId	        (const s8*)"mcueqpBasEntSwitchBrdId"
#define FIELD_mcueqpBasEntAlias			        (const s8*)"mcueqpBasEntAlias"
#define FIELD_mcueqpBasEntRunningBrdId	        (const s8*)"mcueqpBasEntRunningBrdId"
#define FIELD_mcueqpBasEntRecvStartPort	        (const s8*)"mcueqpBasEntRecvStartPort"
#define FIELD_mcueqpBasEntMaxAdpChannel         (const s8*)"mcueqpBasEntMaxAdpChannel"
#define FIELD_mcueqpBasEntMapId			        (const s8*)"mcueqpBasEntMapId"
#define FIELD_mcueqpBasEntIpAddr                (const s8*)"mcueqpBasEntIpAddr"

// ͼ��ϳ������� 
#define SECTION_mcueqpVMPTable			        (const s8*)"mcueqpVMPTable"
#define FIELD_mcueqpVMPEntId			        (const s8*)"mcueqpVMPEntId"
#define FIELD_mcueqpVMPEntPort			        (const s8*)"mcueqpVMPEntPort"
#define FIELD_mcueqpVMPEntSwitchBrdId	        (const s8*)"mcueqpVMPEntSwitchBrdId"
#define FIELD_mcueqpVMPEntAlias			        (const s8*)"mcueqpVMPEntAlias"
#define FIELD_mcueqpVMPEntRunningBrdId	        (const s8*)"mcueqpVMPEntRunningBrdId"
#define FIELD_mcueqpVMPEntRecvStartPort	        (const s8*)"mcueqpVMPEntRecvStartPort"
#define FIELD_mcueqpVMPEntMapId			        (const s8*)"mcueqpVMPEntMapId"
#define FIELD_mcueqpVMPEntEncNumber		        (const s8*)"mcueqpVMPEntEncNumber"

// ͼ��ϳ�����������
#define SECTION_mcuVmpAttachTable               (const s8*)"mcuVmpAttachTable"
#define FIELD_mcueqpVmpAttachIndex              (const s8*)"mcueqpVmpAttachIndex"
#define FIELD_mcueqpBlackGroudColor             (const s8*)"mcueqpBlackGroudColor"
#define FIELD_mcueqpFrameColer                  (const s8*)"mcueqpFrameColor"
#define FIELD_mcueqpSpeakerFrameColor           (const s8*)"mcueqpSpeakerFrameColor"
#define FIELD_mcueqpChairColor                  (const s8*)"mcueqpChairColor"


// ���ϵ���ǽ���� 
#define SECTION_mcueqpMpwTable			        (const s8*)"mcueqpMpwTable"
#define FIELD_mcueqpMpwEntId			        (const s8*)"mcueqpMpwEntId"
#define FIELD_mcueqpMpwEntPort			        (const s8*)"mcueqpMpwEntPort"
#define FIELD_mcueqpMpwEntSwitchBrdId	        (const s8*)"mcueqpMpwEntSwitchBrdId"
#define FIELD_mcueqpMpwEntAlias			        (const s8*)"mcueqpMpwEntAlias"
#define FIELD_mcueqpMpwEntRunningBrdId	        (const s8*)"mcueqpMpwEntRunningBrdId"
#define FIELD_mcueqpMpwEntRecvStartPort	        (const s8*)"mcueqpMpwEntRecvStartPort"
#define FIELD_mcueqpMpwEntMapId			        (const s8*)"mcueqpMpwEntMapId"

// ���ش������� 
#define SECTION_mcueqpPrsTable			        (const s8*)"mcueqpPrsTable"
#define FIELD_mcueqpPrsId				        (const s8*)"mcueqpPrsId"
#define FIELD_mcueqpPrsMCUStartPort		        (const s8*)"mcueqpPrsMCUStartPort"
#define FIELD_mcueqpPrsSwitchBrdId		        (const s8*)"mcueqpPrsSwitchBrdId"
#define FIELD_mcueqpPrsAlias			        (const s8*)"mcueqpPrsAlias"
#define FIELD_mcueqpPrsRunningBrdId		        (const s8*)"mcueqpPrsRunningBrdId"
#define FIELD_mcueqpPrsStartPort		        (const s8*)"mcueqpPrsStartPort"
#define FIELD_mcueqpPrsFirstTimeSpan	        (const s8*)"mcueqpPrsFirstTimeSpan"
#define FIELD_mcueqpPrsSecondTimeSpan	        (const s8*)"mcueqpPrsSecondTimeSpan"
#define FIELD_mcueqpPrsThirdTimeSpan            (const s8*)"mcueqpPrsThirdTimeSpan"
#define FIELD_mcueqpPrsRejectTimeSpan	        (const s8*)"mcueqpPrsRejectTimeSpan"

//4.6�汾 �¼� jlb
//hdu
#define SECTION_mcueqpHduTable			        (const s8*)"mcueqpHduTable"
#define FIELD_mcueqpHduEntId				    (const s8*)"mcueqpHduEntId"
#define FIELD_mcueqpHduEntAlias					(const s8*)"mcueqpHduEntAlias"
#define FIELD_mcueqpHduEntRunningBrdId			(const s8*)"mcueqpHduEntRunningBrdId"
#define FIELD_mcueqpHduEntRecvStartPort			(const s8*)"mcueqpHduEntRecvStartPort"
#define FIELD_mcueqpHduEntDivStyle				(const s8*)"mcueqpHduEntDivStyle"
#define FIELD_mcueqpHduEntDivNum			    (const s8*)"mcueqpHduEntDivNum"
#define FIELD_mcueqpHduEntMapId					(const s8*)"mcueqpHduEntMapId"
#define FIELD_mcueqpHduEntOutModeType1			(const s8*)"mcueqpHduEntOutModeType1"
#define FIELD_mcueqpHduEntOutPortType1			(const s8*)"mcueqpHduEntOutPortType1"
#define FIELD_mcueqpHduEntOutModeType2			(const s8*)"mcueqpHduEntOutModeType2"
#define FIELD_mcueqpHduEntOutPortType2			(const s8*)"mcueqpHduEntOutPortType2"
#define FIELD_mcueqpHduEntZoomRate1			    (const s8*)"mcueqpHduEntZoomRate1"
#define FIELD_mcueqpHduEntZoomRate2			    (const s8*)"mcueqpHduEntZoomRate2"



//svmp
#define SECTION_mcueqpSvmpTable			        (const s8*)"mcueqpSvmpTable"
#define FIELD_mcueqpSvmpEntId			        (const s8*)"mcueqpSvmpEntId"
#define FIELD_mcueqpSvmpEntPort			        (const s8*)"mcueqpSvmpEntPort"
#define FIELD_mcueqpSvmpEntSwitchBrdId	        (const s8*)"mcueqpSvmpEntSwitchBrdId"
#define FIELD_mcueqpSvmpEntAlias			    (const s8*)"mcueqpSvmpPEntAlias"
#define FIELD_mcueqpSvmpEntRunningBrdId	        (const s8*)"mcueqpSvmpEntRunningBrdId"
#define FIELD_mcueqpSvmpEntRecvStartPort	    (const s8*)"mcueqpSvmpEntRecvStartPort"
#define FIELD_mcueqpSvmpEntMapId			    (const s8*)"mcueqpSvmpEntMapId"

//dvmp
#define SECTION_mcueqpDvmpTable			        (const s8*)"mcueqpDvmpTable"
#define FIELD_mcueqpDvmpEntId			        (const s8*)"mcueqpDvmpEntId"
#define FIELD_mcueqpDvmpEntPort			        (const s8*)"mcueqpDvmpEntPort"
#define FIELD_mcueqpDvmpEntSwitchBrdId	        (const s8*)"mcueqpDvmpEntSwitchBrdId"
#define FIELD_mcueqpDvmpEntAlias			    (const s8*)"mcueqpDvmpPEntAlias"
#define FIELD_mcueqpDvmpEntRunningBrdId	        (const s8*)"mcueqpDvmpEntRunningBrdId"
#define FIELD_mcueqpDvmpEntRecvStartPort	    (const s8*)"mcueqpDvmpEntRecvStartPort"
#define FIELD_mcueqpDvmpEntMapId			    (const s8*)"mcueqpDvmpEntMapId"

//MpuBas
#define SECTION_mcueqpMpuBasTable			    (const s8*)"mcueqpMpuBasTable"
#define SECTION_mcueqpMpuBasHDTable			    (const s8*)"mcueqpMpuBasHDTable"
#define FIELD_mcueqpMpuBasEntId			        (const s8*)"mcueqpMpuBasEntId"
#define FIELD_mcueqpMpuBasEntPort			    (const s8*)"mcueqpMpuBasEntPort"
#define FIELD_mcueqpMpuBasEntSwitchBrdId	    (const s8*)"mcueqpMpuBasEntSwitchBrdId"
#define FIELD_mcueqpMpuBasEntAlias			    (const s8*)"mcueqpMpuBasEntAlias"
#define FIELD_mcueqpMpuBasEntRunningBrdId	    (const s8*)"mcueqpMpuBasEntRunningBrdId"
#define FIELD_mcueqpMpuBasEntRecvStartPort	    (const s8*)"mcueqpMpuBasEntRecvStartPort"
#define FIELD_mcueqpMpuBasEntMaxAdpChannel      (const s8*)"mcueqpMpuBasEntMaxAdpChannel"
#define FIELD_mcueqpMpuBasEntMapId			    (const s8*)"mcueqpMpuBasEntMapId"
#define FIELD_mcueqpMpuBasEntIpAddr             (const s8*)"mcueqpMpuBasEntIpAddr"

//Ebap
#define SECTION_mcueqpEbapTable			        (const s8*)"mcueqpEbapTable"
#define SECTION_mcueqpEbapHDTable			    (const s8*)"mcueqpEbapHDTable"
#define FIELD_mcueqpEbapEntId			        (const s8*)"mcueqpEbapEntId"
#define FIELD_mcueqpEbapEntPort			        (const s8*)"mcueqpEbapEntPort"
#define FIELD_mcueqpEbapEntSwitchBrdId	        (const s8*)"mcueqpEbapEntSwitchBrdId"
#define FIELD_mcueqpEbapEntAlias			    (const s8*)"mcueqpEbapEntAlias"
#define FIELD_mcueqpEbapEntRunningBrdId	        (const s8*)"mcueqpEbapEntRunningBrdId"
#define FIELD_mcueqpEbapEntRecvStartPort	    (const s8*)"mcueqpEbapEntRecvStartPort"
#define FIELD_mcueqpEbapEntMaxAdpChannel        (const s8*)"mcueqpEbapEntMaxAdpChannel"
#define FIELD_mcueqpEbapEntMapId			    (const s8*)"mcueqpEbapntMapId"
#define FIELD_mcueqpEbapEntIpAddr               (const s8*)"mcueqpEbapEntIpAddr"

//Evpu
#define SECTION_mcueqpEvpuTable			        (const s8*)"mcueqpEvpuTable"
#define FIELD_mcueqpEvpuEntId			        (const s8*)"mcueqpEvpuEntId"
#define FIELD_mcueqpEvpuEntPort			        (const s8*)"mcueqpEvpuEntPort"
#define FIELD_mcueqpEvpuEntSwitchBrdId	        (const s8*)"mcueqpEvpuEntSwitchBrdId"
#define FIELD_mcueqpEvpuEntAlias			    (const s8*)"mcueqpEvpuPEntAlias"
#define FIELD_mcueqpEvpuEntRunningBrdId	        (const s8*)"mcueqpEvpuEntRunningBrdId"
#define FIELD_mcueqpEvpuEntRecvStartPort	    (const s8*)"mcueqpEvpuEntRecvStartPort"
#define FIELD_mcueqpEvpuEntMapId			    (const s8*)"mcueqpEvpuEntMapId"

//Hdu Scheme
#define SECTION_mcuHduSchemeTable			    (const s8*)"mcuHduSchemeTable"
#define SECTION_mcuHduSchemeChnTable1           (const s8*)"HduSchemeChnTable1"
#define SECTION_mcuHduSchemeChnTable2           (const s8*)"HduSchemeChnTable2"
#define SECTION_mcuHduSchemeChnTable3           (const s8*)"HduSchemeChnTable3"
#define SECTION_mcuHduSchemeChnTable4           (const s8*)"HduSchemeChnTable4"
#define SECTION_mcuHduSchemeChnTable5           (const s8*)"HduSchemeChnTable5"
#define SECTION_mcuHduSchemeChnTable6           (const s8*)"HduSchemeChnTable6"
#define SECTION_mcuHduSchemeChnTable7           (const s8*)"HduSchemeChnTable7"
#define SECTION_mcuHduSchemeChnTable8           (const s8*)"HduSchemeChnTable8"
#define SECTION_mcuHduSchemeChnTable9           (const s8*)"HduSchemeChnTable9"
#define SECTION_mcuHduSchemeChnTable10          (const s8*)"HduSchemeChnTable10"
#define SECTION_mcuHduSchemeChnTable11          (const s8*)"HduSchemeChnTable11"
#define SECTION_mcuHduSchemeChnTable12          (const s8*)"HduSchemeChnTable12"
#define SECTION_mcuHduSchemeChnTable13          (const s8*)"HduSchemeChnTable13"
#define SECTION_mcuHduSchemeChnTable14          (const s8*)"HduSchemeChnTable14"
#define SECTION_mcuHduSchemeChnTable15          (const s8*)"HduSchemeChnTable15"
#define SECTION_mcuHduSchemeChnTable16          (const s8*)"HduSchemeChnTable16"


// Qos
#define SECTION_mcuQosInfo                      (const s8*)"mcuQosConfigure"
#define KEY_mcuQosType                          (const s8*)"mcuQosType"
#define KEY_mcuAudioLevel                       (const s8*)"mcuAudioLevel"
#define KEY_mcuVideoLevel                       (const s8*)"mcuVideoLevel"
#define KEY_mcuDataLevel                        (const s8*)"mcuDataLevel"
#define KEY_mcuSignalLevel                      (const s8*)"mcuSignalLevel"
#define KEY_mcuIpServiceType                    (const s8*)"mcuIpServiceType"

// DSC����MCU8000B�µ��������ô���
#define SECTION_DscModule                       (const s8*)"DSCModule"
#define KEY_DscInnerIp                          (const s8*)"DscInnerIp"
#define KEY_DscMp                               (const s8*)"Mp"
#define KEY_DscMtAdp                            (const s8*)"MtAdp"
#define KEY_DscGk                               (const s8*)"Gk"
#define KEY_DscProxy                            (const s8*)"Proxy"
#define KEY_DscDcs                              (const s8*)"Dcs"
#define KEY_NetType								(const s8*)"NetType"
#define KEY_LanMtProxyIpPos						(const s8*)"LanMtProxyIpPos"
#define KEY_CallAddrNum							(const s8*)"CallAddrNum"
#define ENTRY_CallAddr							(const s8*)"CallAddr"
#define KEY_MCSAccessAddrNum					(const s8*)"MCSAccessAddrNum"
#define ENTRY_MCSAccessAddr						(const s8*)"MCSAccessAddr"

// ������չ����
#define SECTION_EqpExCfgInfo                    (const s8*)"EqpExCfgInfo"
#define KEY_HduIdleChlShowMode                  (const s8*)"HduIdleChlShowMode"
#define KEY_VmpIdleChlShowMode                  (const s8*)"VmpIdleChlShowMode"
#define KEY_HduShowPictureIndx                  (const s8*)"HduShowPictureIndx"
#define KEY_VmpShowPictureIndx                  (const s8*)"VmpShowPictureIndx"
#define KEY_VmpIsDisplayMmbAlias				(const s8*)"VmpIsDisplayMmbAlias"
// VCS
#define VCS_DEFAULTSOFTNAME                     (const s8*)"�ƴ����ָ�ӵ���ϵͳ" 







#define ALARM_RESTART							1000L       /*�豸�������澯*/ //���ϸ澯����ʹ��

//����һ���¸澯ʱ ��Ҫ���ӱ�ʶ�� ��������ӱ�ʶ��������һ���澯�꣨���ֵ����͸澯֪ʶ��һһ��Ӧ��
/////////////////////////////////////////////////�ϸ澯����//////////////////////////////////////////////////////////////////
////////////////////////////////////mpc���ӡ���8000A���и澯mcu ///////////////////////////////////////////
/*����澯����*/
#define ALARM_MCU_MEMORYERROR					1001L       /*�ڴ����*/
#define ALARM_MCU_FILESYSTEMERROR				1002L       /*�ļ�ϵͳ����*/
#define ALARM_MCU_TASK_BUSY						1101L       /*����æ ����5.0δ��*/

/*������Ӳ���澯����*/
/*��ͬ������*/
#define ALARM_MCU_SYNCSRC_ABNORMAL				2101L       /*ͬ��Դ�쳣*/
#define ALARM_MCU_SYNCSRC_SPARE_ABNORMAL		2102L       /*����ͬ��Դ�쳣*/
#define ALARM_MCU_SYNCSRC_BOTH_ABNORMAL			2103L       /*������ͬ��Դͬʱ�쳣 ����5.0δ��*/
/*��Դ���*/
#define ALARM_MCU_POWER_ABNORMAL				2201L       /*��Դ�쳣*/
#define ALARM_MCU_POWER_FAN_ABNORMAL			2202L       /*��Դ�����쳣*/

/*ģ�����*/
#define ALARM_MCU_MODULE_OFFLINE				2301L       /*ģ������ ����5.0δ��*/
#define ALARM_MCU_MODULE_CONFLICT				2302L       /*ģ���ͻ ����5.0δ��*/
#define ALARM_MCU_MODULE_ERROR					2303L       /*ģ����� ����5.0δ��*/

/*�������*/
#define ALARM_MCU_BOARD_DISCONNECT				2401L       /*�����쳣*/
#define ALARM_MCU_BOARD_CFGCONFLICT				2402L       /*�������ó�ͻ*/
#define ALARM_MCU_BOARD_FAN_STOP				2410L       /*��������쳣 ����5.0δ��*/


/*���������� miaoqingsong add */
#define ALARM_MCU_BOX_FAN_ABNORMAL              2411L       /*��������쳣*/
/*MPC���ڴ�ʹ������� miaoqingsong add */
#define ALARM_MCU_MPC_MEMORY_ABNORMAL           2412L       /*MPC��Memoryʹ���ʳ���85%*/
/*MPC��Cpuʹ������� miaoqingsong add */
#define ALARM_MCU_MPC_CPU_ABNORMAL              2413L       /*MPC��Cpuʹ���ʳ���85%*/
/*��Դ���¶���� miaoqingsong add */
#define ALARM_MCU_POWER_TEMP_ABNORMAL           2414L       /*��Դ���¶��쳣*/
/*MPC���¶���� miaoqingsong add */
#define ALARM_MCU_MPC_TEMP_ABNORMAL             2415L       /*MPC���¶ȹ���*/        
//												2416L		/*2416 ����*/

/*E1���*/
#define ALARM_MCU_E1_RUA1						2501L       /*E1ȫ1*/
#define ALARM_MCU_E1_RLOS						2502L       /*E1ʧͬ��*/
#define ALARM_MCU_E1_RRA						2503L       /*E1Զ�˸澯*/
#define ALARM_MCU_E1_LOC						2504L       /*E1ʧ�ز�*/
#define ALARM_MCU_E1_RMF						2505L       /*CRC��֡����*/
#define ALARM_MCU_E1_RCMF						2506L       /*��·��֡����*/
/////////////////////////////////////////////////�ϸ澯����end//////////////////////////////////////////////////////////////////


///////////////////////////////////////// �µ���澯���� begin  /////////////////////////////////
//// �ȱ����µĸ澯�룬Ȼ��ͨ�������ֶλ�ȡ�������ͺͲ�ۺ�/////////////////////////////////////////////
////Ϊ�˼��ݳ�"�ϸ澯����"֮��ȫ�������ַ�ʽ�澯/////////////////////////////////////////
//�澯�����ϸ�ַ�����ʶ���  �㣨�ֽ�0���ۣ��ֽ�1�����ͣ��ֽ�2���������ֽ�3-n��

//���� ������Ҫ�ϱ���
#define ALARM_MCU_FRM_POWER_ABNORMAL				3000L//��Դ���쳣                    2201
#define ALARM_MCU_FRM_FAN_ABNORMAL					3001L//��������쳣                  2411
#define ALARM_MCU_FRM_LEFTPOWER_TEMP_ABNORMAL		3002L//���Դ���¶ȸ澯              2414
#define ALARM_MCU_FRM_RIGHTPOWER_TEMP_ABNORMAL		3003L//�ҵ�Դ���¶ȸ澯              2416
#define ALARM_MCU_FRM_POWERFAN_ABNORMAL				3004L//��Դ�����쳣					 2202

//���� ���㡢�ۡ�������Ҫ�ϱ���
#define ALARM_MCU_BRD_ACCESSMEMERROR				3010L//�豸���ϣ��ڴ���ʴ���        1001
#define ALARM_MCU_BRD_FILESYSTEMERROR				3011L//�ļ�ϵͳ����                  1002
#define ALARM_MCU_BRD_SYNCSRC_ABNORMAL				3012L//ͬ��Դ�쳣����                2101
#define ALARM_MCU_BRD_SYNCSRC_SPARE_ABNORMAL		3013L//����ͬ��Դ�쳣����            2102
#define ALARM_MCU_BRD_BOARD_DISCONNECT				3014L//����δע��	                 2401
#define ALARM_MCU_BRD_BOARD_CFGCONFLICT				3015L//�������ó�ͻ                  2402
#define ALARM_MCU_BRD_CPU_ABNORMAL					3016L//CPUʹ���ʸ���ָ����ֵ�澯     2413
#define ALARM_MCU_BRD_MEMORY_ABNORMAL				3017L//�ڴ�ʹ�ó���ָ����ֵ�澯      2412
#define ALARM_MCU_BRD_TEMP_ABNORMAL					3018L//�����¶ȹ���                  2415

//E1	���㡢�ۡ�������Ҫ�ϱ���
#define ALARM_MCU_BRD_E1_RUA1						3030L//E1ȫ1                         2501
#define ALARM_MCU_BRD_E1_RLOS						3031L//E1ʧͬ��                      2502
#define ALARM_MCU_BRD_E1_RRA						3032L//E1Զ�˸澯                    2503
#define ALARM_MCU_BRD_E1_LOC						3033L//E1ʧ�ز�                      2504
#define ALARM_MCU_BRD_E1_RMF						3034L//E1 CRC��֡����                2505
#define ALARM_MCU_BRD_E1_RCMF						3035L//E1 ��·��֡����               2506

//#define ALARM_MCU_BRD_END							3059L//���ӵ����澯ֵ 3059-3010+1=50

#define ALARM_MCU_BASE							20000L  //mcu�澯����ʼ
#define ALARM_ONEBRD_RANGE						50L		//ÿ��������50�澯��
//�����¸澯�뷶Χ
#define ALARM_MCU_RANGE_START					ALARM_MCU_BASE + ALARM_ONEBRD_RANGE*0   + 3010 //23010
#define ALARM_MCU_RANGE_END						ALARM_MCU_BASE + ALARM_ONEBRD_RANGE*255 + 3059 //32750 + 3059 

/*sdh ����4001-4018 ����5.0δ�� miaoqingsong*/
#define ALARM_MCU_SDH_LOS						4001L       /*���źŶ�ʧ*/
#define ALARM_MCU_SDH_LOF						4002L       /*֡��ʧ*/
#define ALARM_MCU_SDH_OOF						4003L       /*֡ʧ��*/
#define ALARM_MCU_SDH_LOM						4004L       /*��֡��ʧ*/
#define ALARM_MCU_SDH_LOP						4005L       /*����Ԫָ�붪ʧ*/
#define ALARM_MCU_SDH_MS_RDI					4006L       /*���ö�Զ��ȱ��ָʾ*/
#define ALARM_MCU_SDH_MS_AIS					4007L       /*���öα���ָʾ*/
#define ALARM_MCU_SDH_HP_RDI					4008L       /*�߽�ͨ��Զ��ȱ��ָʾ*/
#define ALARM_MCU_SDH_HP_AIS					4009L       /*�߽�ͨ������ָʾ*/
#define ALARM_MCU_SDH_RS_TIM					4010L       /*������ͨ���ټ��ֽڲ�ƥ��*/
#define ALARM_MCU_SDH_HP_TIM					4011L       /*�߽�ͨ���ټ��ֽڲ�ƥ��*/
#define ALARM_MCU_SDH_HP_UNEQ					4012L       /*�߽�ͨ���źű���ֽ�δװ��*/
#define ALARM_MCU_SDH_HP_PSLM					4013L       /*�߽�ͨ���źű���ֽڲ�ƥ��*/
#define ALARM_MCU_SDH_TU_LOP					4014L       /*֧·��Ԫָ�붪ʧ*/
#define ALARM_MCU_SDH_LP_RDI					4015L       /*�ͽ�ͨ��Զ��ȱ��ָʾ*/
#define ALARM_MCU_SDH_LP_AIS					4016L       /*�ͽ�ͨ������ָʾ*/
#define ALARM_MCU_SDH_LP_TIM					4017L       /*�ͽ�ͨ���ټ��ֽڲ�ƥ��*/
#define ALARM_MCU_SDH_LP_PSLM					4018L       /*�ͽ�ͨ���źű���ֽڲ�ƥ��*/



//#define ALARM_MCU_BASE							20000L  //mcu�澯����ʼ
//#define ALARM_ONEBRD_RANGE						50L

//#define ALARM_MCU_RANGE_END						ALARM_MCU_BASE + ALARM_ONEBRD_RANGE*255 //32750
///////////////////////////////////////// �µ���澯���� end  /////////////////////////////////







////////////////////////////////////////	�ն˸澯��		//////////////////////////////////
/* MT�澯�볣������ ���밴�ո澯�������ͷ���*/
#define ALARM_MT_BASE							10000L

/*����澯����*/
/*MT�ն�ϵͳ�ڴ���� miaoqingsong add*/
#define ALARM_MT_MEMORYERROR                    (ALARM_MT_BASE+1001L)   /*�ڴ����*/
#define ALARM_MT_FILESYSTEMERROR                (ALARM_MT_BASE+1002L)   /*�ļ�ϵͳ����*/

/*MT�ն�ϵͳCPU��� miaoqingsong add*/
#define ALARM_MT_CPUERROR						(ALARM_MT_BASE+1003L)   /*cpu����*/
#define ALARM_MT_TASK_BUSY				        (ALARM_MT_BASE+1101L)   /*����æ*/

/*������Ӳ���澯����*/

/*E1���*/
#define ALARM_MT_E1_RUA1                        (ALARM_MT_BASE+2001L)   /*E1ȫ1*/
#define ALARM_MT_E1_RLOS                        (ALARM_MT_BASE+2002L)   /*E1ʧͬ��*/
#define ALARM_MT_E1_RRA                         (ALARM_MT_BASE+2003L)   /*E1Զ�˸澯*/
#define ALARM_MT_E1_LOC                         (ALARM_MT_BASE+2004L)   /*E1ʧ�ز�*/

/*MAP���*/
#define ALARM_MT_MAP_DIE				        (ALARM_MT_BASE+2101L)   /*MAP����   δ��*/

/*CCI���*/
#define ALARM_MT_CCI_QUEUE_FULL			        (ALARM_MT_BASE+2201L)   /*CCI������  δ��*/

/*�������*/
/*����5.0�ı䣺�ն˽��ն������綪��������2301L�澯�� miaoqingsong*/
#define ALARM_MT_NO_BIT_STREAM			        (ALARM_MT_BASE+2301L)   /*����������*/
#define ALARM_MT_SEND_LOST_FRAME		        (ALARM_MT_BASE+2302L)   /*���Ͷ���   δ��*/
//(�붨��ʱ�� ALARM_MT_BASE+2305L��ʼ  ��ΪALARM_MT_BASE+2301+2������ն�������%5  ALARM_MT_BASE+2301+3������ն�������%8 )

/*��ƵԴ���*/
#define ALARM_MT_VIDEOSOURCE_ERROR		        (ALARM_MT_BASE+2403L)   /*����ƵԴ*/

/*��̫�����*/
#define ALARM_MT_ETHERNET_DISCONNECT	        (ALARM_MT_BASE+2501L)   /*��̫���Ͽ� ����5.0δ��*/

/*�������*/
#define ALARM_MT_FAN_SPEED_LOW			        (ALARM_MT_BASE+2601L)   /*����ת�ٵ�*/

/*V35��� ����2701L-2705L����5.0δ�� miaoqingsong*/
#define ALARM_MT_V35_CD_DOWN			        (ALARM_MT_BASE+2701L)   /*v35�ز����ʧ��    δ��*/
#define ALARM_MT_V35_CTS_DOWN			        (ALARM_MT_BASE+2702L)   /*v35�������ʧ��    δ��*/
#define ALARM_MT_V35_RTS_DOWN			        (ALARM_MT_BASE+2703L)   /*v35������ʧ��    δ��*/
#define ALARM_MT_V35_DTR_DOWN			        (ALARM_MT_BASE+2704L)   /*v35�����ն�δ����  δ��*/
#define ALARM_MT_V35_DSR_DOWN			        (ALARM_MT_BASE+2705L)	/*v35����δ׼����    δ��*/

/*��ȫ���*/
#define ALARM_MT_TEMP_HIGH					    (ALARM_MT_BASE+2801L)   /*�����ն��¶ȹ���*/
#define ALARM_MT_VOLT_ERROR		                (ALARM_MT_BASE+2802L)	/*�����ն˵�ѹ�澯*/




////////////////////////////////////////	Cps�澯��		//////////////////////////////////
#define ALARM_CPS_BASE							13000L
#define ALARM_CPS_CPURATE						(ALARM_CPS_BASE + 1)   //CPU����
#define ALARM_CPS_AUTHUSBSTATE					(ALARM_CPS_BASE + 2)   //USB��֤


////////////////////////////////////////	Mps�澯��		//////////////////////////////////
#define ALARM_MPS_BASE							13100L
#define ALARM_MPS_CPURATE						(ALARM_MPS_BASE + 1)   //CPU����


////////////////////////////////////////	Aps�澯��		//////////////////////////////////
#define ALARM_APS_BASE							13200L
#define ALARM_APS_CPURATE						(ALARM_APS_BASE + 1)   //CPU����

////////////////////////////////////////	Caps�澯��		//////////////////////////////////
#define ALARM_CAPS_BASE							13300L
#define ALARM_CAPS_CPURATE						(ALARM_CAPS_BASE + 1)   //CPU����


/* MCU�澯�������� */
#define ALARMOBJ_MCU						    (u8)1
#define ALARMOBJ_MCU_BOARD					    (u8)11
#define ALARMOBJ_MCU_LINK					    (u8)12
#define ALARMOBJ_MCU_TASK					    (u8)13
#define ALARMOBJ_MCU_SDH					    (u8)14
#define ALARMOBJ_MCU_POWER					    (u8)15
#define ALARMOBJ_MCU_MODULE					    (u8)16
#define ALARMOBJ_MCU_SOFTWARE				    (u8)17
#define ALARMOBJ_MCU_BRD_FAN				    (u8)18
#define ALARMOBJ_MCU_BOX_FAN                    (u8)19              // miaoqingsong add
#define ALARMOBJ_MCU_MPC_CPU                    (u8)20              // miaoqingsong add 
#define ALARMOBJ_MCU_MPC_MEMORY                 (u8)21              // miaoqingsong add
#define ALARMOBJ_MCU_POWER_TEMP                 (u8)22              // miaoqingsong add
#define ALARMOBJ_MCU_MPC_TEMP                   (u8)23              // miaoqingsong add

/* MT�澯�������� */
#define ALARMOBJ_MT_BASE				        (u8)128
#define ALARMOBJ_MT                             (u8)(ALARMOBJ_MT_BASE + 1)
#define ALARMOBJ_MT_E1                          (u8)(ALARMOBJ_MT_BASE + 11)
#define ALARMOBJ_MT_MAP					        (u8)(ALARMOBJ_MT_BASE + 12)
#define ALARMOBJ_MT_CCI					        (u8)(ALARMOBJ_MT_BASE + 13)
#define ALARMOBJ_MT_STREAM				        (u8)(ALARMOBJ_MT_BASE + 14)
#define ALARMOBJ_MT_ETHERNET			        (u8)(ALARMOBJ_MT_BASE + 15)
#define ALARMOBJ_MT_TASK				        (u8)(ALARMOBJ_MT_BASE + 16)
#define ALARMOBJ_MT_FAN					        (u8)(ALARMOBJ_MT_BASE + 17)
#define ALARMOBJ_MT_V35					        (u8)(ALARMOBJ_MT_BASE + 18)
#define ALARMOBJ_MT_TEMP			            (u8)(ALARMOBJ_MT_BASE + 20)   
#define ALARMOBJ_MT_VOLT			            (u8)(ALARMOBJ_MT_BASE + 21)

/*MPC���ڴ��CPU�쳣�澯ʹ��*/
#define  MEMORY_MCU_OBJECT              (u8)1         // MCU�豸MPC���ڴ�澯�����ʶ�������ڴ��쳣�澯ʱʹ�� mqs 2010/12/22
#define  CPU_MCU_OBJECT                 (u8)2         // MCU�豸MPC��CPU�澯�����ʶ������CPU�쳣�澯ʹ�� mqs 2010/12/22
#define  TEMP_MCU_OBJECT                (u8)3         // MCU�豸MPC���¶��쳣�澯�����ʶ������MPC2���¶ȹ����쳣�澯ʹ�� mqs 2011/01/13

/*���̸澯��������*/  //��ӦNODE_XXXPFMALARMOBJTYPE
#define ALARMOBJTYPE_CONSULTATION_BASE				(u8)160
#define ALARMOBJTYPE_CPS							(u8)(ALARMOBJ_CONSULTATION_BASE + 0)
#define ALARMOBJTYPE_MPS							(u8)(ALARMOBJ_CONSULTATION_BASE + 1)
#define ALARMOBJTYPE_APS							(u8)(ALARMOBJ_CONSULTATION_BASE + 2)
#define ALARMOBJTYPE_CAPS							(u8)(ALARMOBJ_CONSULTATION_BASE + 3)

//����ʹ����ͳ��buffer����
const u8 AGENT_MAX_EQPNODEBUFF_LEN  = 128;

enum Pfm_eTypeKind
{
	Pfm_eType_MtNum = 0,
	Pfm_eType_ConfNum,
	Pfm_eType_Eqp,
	Pfm_eType_Auth
};

/*���ܸı�֪ͨ*/
struct TPfmNotify
{
	u8 m_byPfmType; //Pfm_eTypeKind
	u8 m_byEqpType; //���������
	u16 m_wValue;
}

#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

/*���鿪ʼ�����ʱ֪ͨAGENT�Ľṹ*/
struct TConfNotify
{
	u8 m_abyConfId[16];
	u8 m_abyConfName[32];   /*������*/
	u8 m_byConfMtNum;       /*����ն���Ŀ*/
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

/*����������ɾ���ն�ʱ֪ͨAGENT�Ľṹ*/
struct TMtNotify
{
	u8 m_abyConfId[16];
	u8 m_abyMtAlias[128];
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

    
/*����ҵ�������ʱ�ϱ���E1��DTI״̬�ı�ṹ*/
struct CDevStatus
{
	u8 dti;					/*0-32*/
	u8 e1;					/*0-7*/
	u8 status;				/*����E1/DTI״̬��Ϣ���ֱ��ʾE1/DTI��״̬��DTIʱ�� 0 ����, 1 �쳣
							    e1ʱ:	bit0 E1ʧͬ��		bit1 E1ʧ�ز� 
									    bit2 E1Զ�˸澯		bit3 E1ȫ1*/
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;


/*������MPC����澯ʱʹ�õĽṹ*/
struct TBoardAlarmMsgInfo
{
	u16	wEventId;
	u8   abyAlarmContent[5];
};


/*����״̬*/
struct TBrdStatus
{
	u8	byLayer;	        /*���*/
	u8	bySlot;		        /*�ۺ�*/
	u8	byType;		        /*������*/
	u8	byStatus;	        /*״̬��0:����  1:�쳣  2:���ó�ͻ */
    u8  byOsType;           /*����ϵͳ����*/
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TBrdFanStatus
{
	u8  byLayer;
	u8  bySlot;
	u8  byType;
	u8  byFanId;
	u8  byStatus;
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

/*��·״̬*/
struct TLinkStatus
{
	u8	byLayer;	        /*���*/
	u8	bySlot;		        /*�ۺ�*/
	u8	byType;		        /*������*/
	u8	byE1Num;            /*E1��*/
	u8	byStatus;	        /*״̬  bit0 E1ʧͬ��     bit1 E1ʧ�ز�       bit2 E1Զ�˸澯	
						            bit3  E1ȫ1       bit4 CRC��֡����    bit5 ��·��֡����*/
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TPowerStatus
{
	u8 bySlot;              /*��Դ��*/
	u8 byType;              /*����(5v 48v)*/
	u8 byStatus;            /*״̬*/
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

enum
{
	POWER_LEFT = 1,
	POWER_RIGHT = 2
};

enum 
{
	POWER_5V =1,
	POWER_48V = 2
};

enum 
{
	FAN_LEFT  = 1,
	FAN_RIGHT = 2
};

struct TPowerFanStatus
{
	u8 bySlot;              /*��Դ��*/
	u8 byFanPos;            /**/
	u8 byStatus;            /*״̬*/
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// [2010/12/14 miaoqingsong add]  �������λ�ýṹ��
struct TBoxFanStatus
{
	u8 bySlot;              /*��Դ�� ��������ֱ�Ϊ��0 1 2 3 */
	u8 byFanPos;            /*1 2*/ 
	u8 byStatus;            /*״̬*/
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// [2010/12/15 miaoqingsong add] MPC��Cpu״̬��Ϣ�ṹ��
struct TMPCCpuStatus
{
	u8 byCpuAllocRate;    /*MPC��Cpuռ���� 0 - 100 */
	u8 byCpuStatus;       /*״̬*/
};

// [2010/12/15 miaoqingsong add] MPC���ڴ�״̬��Ϣ�ṹ��
struct TMPCMemoryStatus
{
	u8 byMemoryAllocRate;   /*MPC���ڴ�ʹ���� 0 - 100 */
	u8 byMemoryStatus;      /*״̬*/
};

// [2011/01/13 miaoqingsong add] MPC2���¶�״̬��Ϣ�ṹ��
struct TMPC2TempStatus
{
	u32 dwMpc2Temp;        /*MPC2��ʵʱ�¶�ֵ 0 - 100 */
	u8  byMpc2TempStatus;  /*״̬*/
};

// [2010/12/15 miaoqingsong add] ��Դ���¶���Ϣ�ṹ��
struct TPowerBrdTempStatus
{
	u8 bySlot;                   /*��Դ�� ���Դ:  POWER_LEFT(1); �ҵ�Դ: POWER_RIGHT(2)*/
	u8 byPowerBrdTempStatus;     /*��Դ���¶�״̬*/
};

struct TModuleStatus
{
	u8 byLayer;             /*���*/
	u8 bySlot;              /*�ۺ�*/
	u8 byType;              /*������*/
	u8 byModuleId;          /*ģ���*/
	u8 byStatus;            /*״̬  bit0 ģ������  bit1  ģ���ͻ bit2 ģ�����*/  
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

/*MCU���ڴ���ļ�ϵͳ״̬����ʹ�øýṹ*/
struct TSoftwareStatus
{
	u8 byLayer;             /*���*/
	u8 bySlot;              /*�ۺ�*/
	u8 byType;              /*������*/
	u8 byStatus;            /*״̬*/
};

/*MCU������״̬����ʹ�øýṹ*/
struct TMcuTaskStatus
{
	u8 byLayer;             /*���*/
	u8 bySlot;              /*�ۺ�*/
	u8 byType;              /*������*/
	u16  wAppId;	        /*APP��*/
	u8 byStatus;            /*״̬*/
};

/*SDH��״̬*/
struct TSDHStatus
{
	u32	dwStatus;/*״̬  bit0  ���źŶ�ʧ                    bit1  ֡��ʧ           
					         bit2  ֡ʧ��	                     bit3  ��֡��ʧ    
							 bit4  ����Ԫָ�붪ʧ              bit5  ���ö�Զ��ȱ��ָʾ
							 bit6  ���öα���ָʾ                bit7  �߽�ͨ��Զ��ȱ��ָʾ 
							 bit8  �߽�ͨ������ָʾ              bit9  ������ͨ���ټ��ֽڲ�ƥ�� 
							 bit10 �߽�ͨ���ټ��ֽڲ�ƥ��        bit11 �߽�ͨ���źű���ֽ�δװ�� 
							 bit12 �߽�ͨ���źű���ֽڲ�ƥ��    bit13 ֧·��Ԫָ�붪ʧ  
							 bit14 �ͽ�ͨ��Զ��ȱ��ָʾ          bit15 �ͽ�ͨ������ָʾ  
							 bit16 �ͽ�ͨ���ټ��ֽڲ�ƥ��        bit17 �ͽ�ͨ���źű���ֽڲ�ƥ��   */
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

/*����ҵ��������ϱ���ͬ��Դ״̬�ı�ṹ*/
struct CSyncSourceAlarm
{
	u8 masterstatus;		/*0: ok, 1: fail*/
	u8 slavestatus;			/*0: ok, 1: fail*/
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

/*����ҵ�������ʱ�ϱ���MT״̬�ı�ṹ*/
struct CMtConnectStatus
{
	u8 mt;					/*1-127*/
	u8 status;				/*����MT״̬��Ϣ���ֱ��ʾMT��״̬��0 ����, 1 �쳣*/
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;


/*����ҵ��������ϱ��ĵ�ǰͬ��Դ�ı��ϱ��ṹ*/
struct CCurrentMasterSync
{
	u8 dti;
	u8 e1;
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

/*����ҵ��������ϱ����豸������Ϣ�ṹ*/
struct CEqpConnStatus
{
	u8 eqptype;             /*�豸����*/
	u8 eqpid;	            /*�豸���*/
	u8 status;	            /*�豸״̬ 1 ���� 2������ 3��֪��*/	 	
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

/*����ҵ��������ϱ�������״̬�ṹ*/
struct CTaskStatus
{
	u16 appid;	            /*APP��*/
	u8  status;	            /*APP״̬ 0 ���� 1����æ*/	 	
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

/*����ҵ��������ϱ���MAP״̬�ṹ*/
struct CMapStatus
{
	u8 mapid;	            /*MAP��*/
	u8 status;	            /*MAP״̬ 0 ���� 1����*/
	u16 wDiedCount;         /*��MAP��������*/
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

/*����ҵ��������ϱ���CCI״̬�ṹ*/
struct CCCIStatus
{
	u8 mapid;	            /*MAP��*/
	u8 updown;              /*0 ���� 1 ����*/
	u8 queueid;             /*���к�*/
	u8 status;	            /*MAP����״̬  0 ����  1 ��	*/ 	
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

/*����ҵ��������ϱ�����̫��״̬�ṹ*/
struct CEthernetCardStatus
{
	u8 cardid;	            /*��̫������*/
	u8 status;	            /*��̫����״̬ 0 ���� 1���߶Ͽ�*/ 	
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

/*����ҵ��������ϱ���ý����״̬�ṹ*/
struct CMediaStreamStatus
{
	u8 mediatype;	        /*ý������*/
	u8 status;		        /*��״̬ bit0 ���������� bit1 ���́G��*/ 	 	
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

/*����ҵ��������ϱ��ķ���״̬�ṹ*/
struct CFanStatus
{
	u8 fanid;	            /*����ID��*/
	u8 status;		        /*����״̬ 0 ���� 1 �쳣*/ 	 	
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

#endif /*_AGENT_COMMON_H_*/
