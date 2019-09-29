#ifndef _h_tpcommonstruct_h__
#define _h_tpcommonstruct_h__
#include "tpsys.h"
#include <time.h>
#include "mtmacro.h"
#include "tphdu2.h"

//MTStruct begin.
#include "kdvtype.h"
#include "mtmacro.h"
#include "tpcommontype.h"
#include "osp.h"
#include "moonconst.h"

/////////////��������������///////////////////////
//FTP�ļ���Ϣ
typedef struct tagTTPFTPFileInfo
{
	u32_ip	dwSerIP;
	u16		wSerPort;
	u8		byUserNameLen;
	s8		achUserName[MAX_FTP_NAME_LEN];
	u8		byPasswordLen;
	s8		achPassword[MAX_FTP_NAME_LEN];
	u8		byFilePathLen;
	s8		achFilePath[TP_MAX_FILESRV_FILENAME_LEN];
	public:
		tagTTPFTPFileInfo(){ memset( this, 0, sizeof( struct tagTTPFTPFileInfo ) ); };
}TTPFTPFileInfo;

typedef struct tagTTPDev
{
	EmTPDevRegUpdateSer    m_emDevRegUpdateSer; //�����豸���豸����
	s8                     m_achDevVersion[MAX_DEVICEVER_LEN];
	TTPFTPFileInfo         m_tDevVerFileInfo;
	EmTPUpdateType         m_emTPUpdateType;
public:
	tagTTPDev()
	{ 
		memset( this, 0, sizeof(struct tagTTPDev) ); 
		m_emDevRegUpdateSer = emDevInvalid; 
	}
}TTPDev;

//�豸��Ϣ
typedef struct tagTTPDevVerInfo
{
	TTPDev	m_atDev[MAX_REG_DEVICE_NUM]; //cns�����ļ�Ϊ��һ��Ԫ�أ�TPad�����ļ�Ϊ�ڶ���Ԫ��
	public:
		tagTTPDevVerInfo(){ memset( this, 0, sizeof(struct tagTTPDevVerInfo) ); }
}TTPDevVerInfo;

typedef struct tagTTPLocalVerInfo
{
	EmTPDevRegUpdateSer    m_emDevRegUpdateSer; //�����豸���豸����
	s8                     m_achDevVersion[MAX_DEVICEVER_LEN];
public:
	tagTTPLocalVerInfo()
	{
		memset( this, 0, sizeof(tagTTPLocalVerInfo) );
		m_emDevRegUpdateSer = emDevInvalid;
	}
}TTPLocalVerInfo;

//�豸�ı�����Ϣ
typedef struct tagTTPLocalDevVerInfo
{
	EmTPDevRegUpdateSer    m_emDevRegUpdateSer; //����˵��豸����
	TTPLocalVerInfo        m_atLocalVerInfo[MAX_DEVICE_NUM]; 
public:
	tagTTPLocalDevVerInfo()
	{
		m_emDevRegUpdateSer = emDevInvalid;
	}
}TTPLocalDevVerInfo;

//TPad�����ļ���Ϣ
typedef struct tagTTPTPadVerInfo
{
	EmTPUpdateType         m_emTPUpdateType;
	TTPFTPFileInfo         m_tPadVerFileInfo;
	s8                     m_achTPadVersion[MAX_DEVICEVER_LEN];
	public:
		tagTTPTPadVerInfo(){ memset( this, 0, sizeof( struct tagTTPTPadVerInfo ) ); }
}TTPTPadVerInfo;




/*************************add struct begin********************************/



/************************************************************************/
/* ���������Ϣ���ݽṹ���忪ʼ                                         */
/************************************************************************/
/************************************************************************/
/* H323��Ϣ���ݽṹ����                                                 */
/************************************************************************/
typedef struct tagTH323Cfg
{
    s8   achMtAlias[MT_MAX_H323ALIAS_LEN+1]; //����
    s8   achE164[MT_MAX_E164NUM_LEN+1];      //E164����
    BOOL bIsUseGk;                  // �Ƿ�ʹ��GK
	s8   achGKPwd[MT_MAX_PASSWORD_LEN+1];//GK����
    u32_ip  dwGkIp;                     // GK ��ַ
    s8   achGkIpName[MT_MAX_H323GKSERVER_NAME_LEN]; //Gk������ַ
    BOOL bIsH239Enable;                  // H239��ʽ
    BOOL bIsEnctyptEnable;          // �Ƿ�ʹ�ü���
    EmEncryptArithmetic emEncrptMode;      //���ܷ�ʽ
    u16  wRoundTrip;                //��·���ʱ��
public:
	tagTH323Cfg(){memset(this , 0 ,sizeof( struct tagTH323Cfg) );	}
}TH323Cfg,*PTH323Cfg;

/************************************************************************/
/* ������Ϣ���ݽṹ����                                               */
/************************************************************************/
typedef struct tagTGuideCfg
{
    EmLanguage  emLanguage;         //����ѡ��
    BOOL  bIsDHCPEnable;            //�Ƿ�ʹ��DHCP
    u32_ip  dwIp;                      //�ն�IP��ַ    
    u32_ip  dwMask;                     //��������
	u32_ip  dwGateWay;                  //���ص�ַ
    BOOL bH323Enable;              //�Ƿ�ʹ��H323
	BOOL bH320Enable;              //�Ƿ�ʹ��H320
	BOOL bSIPEnable;                //�Ƿ�ʹ��SIP
	BOOL bSATEnable;                //�Ƿ�ʹ������
    TH323Cfg tH323Info;             //H323����
    BOOL bUserCfgPwdEnable;         //�Ƿ�������������
    s8  achUserCfgPwd[MT_MAX_PASSWORD_LEN+1]; //�Ƿ�������������
    BOOL bNetCfgPwdEnable;         //�Ƿ�����������������
    s8  achNetCfgPwd[MT_MAX_PASSWORD_LEN+1]; //������������
public:
	tagTGuideCfg(){ memset ( this ,0 ,sizeof( struct tagTGuideCfg) );}
}TGuideCfg, *PTGuideCfg;
// TsymboPoint̨��λ�ýṹ
typedef struct tagTSymboPoint
{
	u16 X;
	u16 Y;
public:
	tagTSymboPoint(){ memset( this ,0 ,sizeof( struct  tagTSymboPoint ) );}
}TSymboPoint;
/************************************************************************/
/* ��ʾ������Ϣ���ݽṹ����                                               */
/************************************************************************/
typedef struct tagTOsdCfg
{
    BOOL  bIsAutoPip;            //�Ƿ������Զ����л�
    BOOL  bIsShowConfLapse;      //�Ƿ���ʾ����ʱ��
    BOOL  bIsShowSysTime;        //�Ƿ���ʾϵͳʱ��
    BOOL  bIsShowState;          //�Ƿ���ʾ״̬��־
    EmLabelType  emLabelType;    //̨������
	TSymboPoint  tLableCoordinate; // �Զ���̨��λ��
	EmLabelPosType emLabelPosType; //�ն˱���̨��λ��
    EmDualVideoShowMode emDualMode;//˫����ʾ��ʽ
	EmDisplayRatio  emPrimaryDisplayRatio;//��һ·��ʾ����ģʽ
	EmDisplayRatio  emSecondDisplayRatio;//�ڶ�·��ʾ����ģʽ
public:
	tagTOsdCfg(){ memset( this ,0 ,sizeof( struct  tagTOsdCfg ) );}
}TOsdCfg, *PTOsdCfg;

//ʱ��ṹ���¶���
typedef struct tagTMtKdvTime
{
    u16 		m_wYear;//��
    u8  		m_byMonth;//��
    u8  		m_byMDay;//��
    u8  		m_byHour;//ʱ
	u8  		m_byMinute;//��
	u8  		m_bySecond;//��
public:
    tagTMtKdvTime(){ memset ( this ,0 ,sizeof( struct tagTMtKdvTime) );}
}TMtKdvTime, *PTMtKdvTime;

/************************************************************************/
/* �û�������Ϣ���ݽṹ����                                               */
/************************************************************************/
typedef struct tagTUserCfg
{
    EmTripMode emAnswerMode;   //Ӧ��ʽ
    BOOL  bIsAutoCallEnable;    //�Ƿ������Զ�����
    s8  achTerminal[MT_MAX_H323ALIAS_LEN+1]; //�Զ����е��ն���
    u16  wCallRate;               //�Զ���������
    BOOL  bIsRmtCtrlEnbale;      //�Ƿ�����Զ�˿���
    BOOL  bIsSleepEnable;        //�Ƿ�����������
    u16  wSleepTime;            //����ʱ��
	BOOL  bDisableTelephone;       // �Ƿ���õ绰����
public:
    tagTUserCfg(){ memset ( this ,0 ,sizeof( struct tagTUserCfg) );}
}TUserCfg, *PTUserCfg;

/************************************************************************/
/*8010c����vga�������                                               */
/************************************************************************/
typedef struct tagTVgaOutCfg
{
	BOOL bVgaOut; //8010c�Ƿ���vga�����
	u16  wRefreshRate; //vga��ˢ����
 public:
 	tagTVgaOutCfg(){memset(this , 0 ,sizeof( struct tagTVgaOutCfg) );	}
	tagTVgaOutCfg( BOOL bOut, u16 wRate ){ bVgaOut = bOut; wRefreshRate = wRate; }
}TVgaOutCfg, *PTVgaOutCfg;

typedef struct tagTMtEquipmentCapset
{
    BOOL bMicAdjustSupport;
	BOOL bMcSupport;
public:
	tagTMtEquipmentCapset(){memset(this , 0 ,sizeof( struct tagTMtEquipmentCapset) );	}
}TMtEquipmentCapset, *PTMtEquipmentCapset;


/************************************************************************/
/*��Ƕmc����                                                            */
/************************************************************************/
//[xujinxing-2006-10-17]
typedef struct tagTInnerMcCfg
{
	BOOL bUseMc;
	EmMCMode emMode;
	BOOL bAutoVMP;
	tagTInnerMcCfg()
	{
		bUseMc = FALSE;
		emMode = emMcModeEnd;
		bAutoVMP = FALSE;
	}
}TInnerMcCfg,*PTInnerMcCfg;



/************************************************************************/
/* ��̫����Ϣ���ݽṹ����                                               */
/************************************************************************/
typedef struct tagTEthnetInfo
{
    BOOL bEnable;
    u32_ip  dwIP;
    u32_ip  dwMask;
    BOOL bIsUserAssignBandWidth;
    u32  dwUpBandWidth;
    u32  dwDownBandWidth;
public:
	tagTEthnetInfo(){ memset( this ,0 ,sizeof( struct  tagTEthnetInfo ) );}
}TEthnetInfo, *PTEthnetInfo;



typedef struct tagTE1Unit                                                                                     
{                                                                                                              
    BOOL bUsed;        //ʹ�ñ�־,��1ʹ�ã�0��ʹ��  
    u32   dwE1TSMask;        // E1ʱ϶����˵�� 
    EmDLProtocol emProtocol; //�ӿ�Э���װ����,����ǵ�E1���ӿ���ָ��PPP/HDLC��
    //����Ƕ�E1�������ӱ�����PPPЭ��
    u32 dwEchoInterval; // ��Ӧserialͬ���ӿڵ�echo����ʱ��������Ϊ��λ����Ч��Χ0-256��Ĭ����2
    u32 dwEchoMaxRetry;// ��Ӧserialͬ���ӿڵ�echo����ط���������Ч��Χ0-256��Ĭ����2 
public:
	tagTE1Unit(){ memset( this ,0 ,sizeof( struct  tagTE1Unit ) );}
}TE1Unit,*PTE1Unit;

/************************************************************************/
/* E1��Ϣ���ݽṹ����                                               */
/************************************************************************/
typedef struct tagTE1Config
{                                                                                                            
// Single & Multi Chan param.                                                                                  

	u8  byUnitNum;                 //ʹ��E1��Ԫ����
    BOOL  bIsBind;                  //  �Ƿ��                                                                    
    u32_ip  dwIP;                      //  ip��ַ                                                                          
    u32_ip  dwIPMask;                  //  ���룬                                                                          
	// ��ͨ������
    EmAuthenticationType emAuthenticationType;//PPP���ӵ���֤����PAP/CHAP,Ĭ����emPAP 
    u32  dwFragMinPackageLen;       //  ��С��Ƭ�������ֽ�Ϊ��λ����Χ20~1500��Ĭ����20                                 
    s8   achSvrUsrName[MT_MAX_E1_NAME_LEN+1]; 	/* ������û����ƣ�������֤�Զ˵����� */                                       
    s8   achSvrUsrPwd[MT_MAX_E1_NAME_LEN+1];   	/* ������û����룬������֤�Զ˵����� */                               
    s8   achSentUsrName[MT_MAX_E1_NAME_LEN+1];	/* �ͻ����û����ƣ��������Զ���֤ */                                           
    s8   achSentUsrPwd[MT_MAX_E1_NAME_LEN+1]; 	/* �ͻ����û����룬�������Զ���֤ */                                           
	// E1 Module Param.                                                                                            
    TE1Unit atE1Unit[ MT_MAX_E1UNIT_NUM ];//E1_SINGLE_LINK_CHAN_MT_MAX_NUM];/* ÿ���������serialͬ���ӿڲ��� */
public:
	tagTE1Config(){ memset( this ,0 ,sizeof( struct  tagTE1Config ) );}	
}TE1Config, *PTE1Config;



/************************************************************************/
/* ������Ϣ���ݽṹ����                                               */
/***********************************************************************/

typedef struct tagTSerialCfg
{
    u32  dwBaudRate; //�����ʵ�λkbps
    u8   byByteSize;   //����λ���� 5,6,7,8
    EmParityCheck emCheck; //У���㷨
    EmStopBits emStopBits; //ֹͣλ
public:
 	tagTSerialCfg(){memset(this , 0 ,sizeof( struct tagTSerialCfg) );	}
}TSerialCfg, *PTSerialCfg;


/************************************************************************/
/* ·����Ϣ���ݽṹ����                                               */
/************************************************************************/
typedef struct tagTRouteCfg
{
    BOOL bUsed;
    u32_ip dwDstNet; //Ŀ������
    u32_ip dwDstNetMask; //Ŀ����������
    u32_ip dwNextIP; //��һ��IP��ַ  
    u32 dwPri;  //·�����ȼ�
public:
  	tagTRouteCfg(){memset(this , 0 ,sizeof( struct tagTRouteCfg) );	}
}TRouteCfg, *PTRouteCfg;

/************************************************************************/
/* PPPOE��Ϣ���ݽṹ����                                               */
/************************************************************************/

/*��ʼ��PPPOEģ��ʱʹ�õĽṹ��*/
typedef struct  tagTPPPOECfg
{
	BOOL    bUsed;   //�Ƿ�ʹ��PPPoE
    s8      abyUserName [MT_PPPoE_MAX_USENAME_LEN];/*����ʱʹ�õ��û���,������*/
    s8      abyPassword [MT_PPPoE_MAX_PASSWORD_LEN]; /*����ʱʹ�õ�����,������*/
    s8      abyServerName[MT_PPPoE_MAX_SERVERNAME_LEN];/*ָ�����ŷ����̵�����*/
    BOOL  bAutoDialEnable;/*�Ƿ�����������Զ�����,Ĭ�ϲ��Զ�����*/
    BOOL  bDefaultRouteEnable;/*�Ƿ������Զ˵ĵ�ַ��ΪĬ�����أ�Ĭ�ϲ���Ϊ����*/
    BOOL  bDebug;/*�Ƿ���debugģʽ����pppoe��Ĭ�ϲ�������debugģʽ*/
    u32     dwAutoDialInterval;/*�������ٴ��Զ�������Ҫ�ȴ���ʱ�䣨�������ó�0s��*/
    u16     wDialRetryTimes;/*���ų��ԵĴ���������ﵽ�ô�����û����Ӧ�򲦺�ʧ��*/
    u16     wLcpEchoSendInterval;/*���ӽ����󣬷���LCP-ECHO����ʱ����*/
    u16     wLcpEchoRetryTimes;/* ���ͼ���LCP-ECHO��û�еõ���Ӧ����Ϊ���ӶϿ�*/
    u8      byEthID;/*PPPOE������Ҫ�󶨵���̫����ID�ţ���0��ʼ��*/
public:
 	tagTPPPOECfg(){ memset( this ,0 ,sizeof( struct  tagTPPPOECfg ) );}
}TPPPOECfg, *PTPPPOECfg;


/*�й�PPPOEģ�����ͳ����Ϣ�Ľṹ��*/
typedef struct tagTPPPoEStates
{
    BOOL    bPppoeRunning;/*PPPOE�Ƿ����У�TRUR�����У�FALSE��û������*/
    u32     dwLocalIpAddr;/*����IP��ַ,������*/
    u32     dwPeerIpAddr;/*�Զ�IP��ַ,������*/
    s8      abyServerName[MT_PPPoE_MAX_SERVERNAME_LEN];/*ISP Server������*/
    u32     dwLinkKeepTimes;/*��·������ʱ��*/
    u32     dwLinkDownTimes;/*��·�����Ĵ���ͳ��*/
    u32     dwPktsSend;/*�ܹ����͵����ݰ���--��������Э����Լ��ϲ�ҵ���������ݰ�*/
    u32     dwPktsRecv;/*�ܹ����յ����ݰ���*/
    u32     dwBytesSend;/*�ܹ����͵��ֽ���*/
    u32     dwBytesRecv;/*�ܹ����յ��ֽ���*/
public:
	tagTPPPoEStates(){ memset( this ,0 ,sizeof( struct  tagTPPPoEStates ) );}
}TPPPoEStates,*PTPPPoEStates;

/*�����ϲ�ҵ�����ע��Ļص�����������֤ʧ��ʱ��Ϣ�����ݽṹ��*/
typedef struct tagTPPPoEAuthFailed
{
    s8      abyUserName [MT_PPPoE_MAX_USENAME_LEN];/*ҵ�������Ĳ���ʱʹ�õ��û���*/
    s8      abyPassword [MT_PPPoE_MAX_PASSWORD_LEN]; /*ҵ�������Ĳ���ʱʹ�õ����� */
public:
 	tagTPPPoEAuthFailed(){ memset( this ,0 ,sizeof( struct  tagTPPPoEAuthFailed ) );}
}TPPPoEAuthFailed,*PTPPPoEAuthFailed;

/*�����ϲ�ҵ�����ע��Ļص��������ͽ���֪ͨ��Ϣ�Ľṹ��*/
typedef struct tagTPPPoEConnNotify
{
    u32     dwOurIpAddr;/*���ϻ�õ�IP��ַ,������*/
    u32     dwPeerIpAddr;/*�Զ˵�IP��ַ*/
    u32     dwDnsServer1;/*DNS Server1,������*/
    u32     dwDnsServer2;/*DNS Server1,������*/ 
public:
 	tagTPPPoEConnNotify(){ memset( this ,0 ,sizeof( struct  tagTPPPoEConnNotify ) );}
}TPPPoEConnNotify,*PTPPPoEConnNotify;

/*֪ͨҵ������Ҳ���ָ����ISP Server����Ϣ�ṹ��*/
typedef struct tagTPPPoENoServer
{
    s8      abyServerName[MT_PPPoE_MAX_SERVERNAME_LEN];/*ISP Server������*/
public:
  tagTPPPoENoServer(){ memset( this ,0 ,sizeof( struct  tagTPPPoENoServer ) );}
}TPPPoENoServer,*PTPPPoENoServer;

/************************************************************************/
/* SNMP��Ϣ���ݽṹ����                                               */
/************************************************************************/
typedef struct tagTSNMPCfg
{
    s8    achUserName[MT_MAX_COMM_LEN+1];//��ͬ����
    u32_ip   dwTrapServerIp;//�澯������ַ
public:
	tagTSNMPCfg(){ memset( this ,0 ,sizeof( struct  tagTSNMPCfg ) );}
}TSNMPCfg, *PTSNMPCfg;


/************************************************************************/
/* QOS��Ϣ���ݽṹ����                                               */
/************************************************************************/
typedef struct tagTIPQoS
{
	//QoS��������
    EmQoS    emType;
	//����QOSֵ ��Χ
    u8       abySignalling[2];
	//�����ŵ�����������ͷԶҡ��QOSֵ ��Χ
    u8       abyData[2];
	//����QOSֵ ��Χ
    u8       abyAudio[2];
	//��ƵQOSֵ ��Χ
    u8       abyVideo[2];
	//������֤����
    EmTOS    emTOS;
public:
	tagTIPQoS(){ memset( this ,0 ,sizeof( struct  tagTIPQoS ) );}
}TIPQoS, *PTIPQoS;




/************************************************************************/
/* ��ý����Ϣ���ݽṹ����                                               */
/************************************************************************/
typedef struct tagTStreamMedia
{
    BOOL bUse;
    BOOL bForwardLocalVideo; //�Ƿ�ת��������Ƶ
    u32_ip  dwMCIP;    //�鲥IP��ַ
    u16  wPort;     //�˿ں�
	u8   byTTL;     //TTLֵ
    s8   achChannelName[MT_MAX_CHANNEL_NAME_LEN+1];//Ƶ������
    s8   achPassword[MT_MAX_PASSWORD_LEN+1];//����
public:
	tagTStreamMedia(){ memset( this ,0 ,sizeof( struct  tagTStreamMedia ) );}
}TStreamMedia, *PTStreamMedia;


/************************************************************************/
/*��Ƶ��������Ϣ���ݽṹ����                                               */
/************************************************************************/
typedef struct tagTVideoParam 
{
    BOOL  bUseFixedFrame;    //ʹ�ù̶�֡ 
    u8 byFrameRate;	///֡��
    EmFrameUnitType  emFrameUnit;	//֡�ʵ�λ
    u8 byQualMaxValue;	//��С��������
    u8 byQualMinValue;	//�����������
    u16 wIKeyRate;	//�ؼ�֡���
    EmEncodeMode emEncodeMode;     //���뷽ʽ
    EmLostPackageRestore emRestoreType; //�����ָ���ʽ
    u16 wH264IKeyRate;		//H264�ؼ�֡���
    u8  byH264QualMaxValue;	//H264�����������
    u8  byH264QualMinValue;	//H264��С��������
//���²���ֻ����windows�²�����
//��Ӳɼ�ͼ����
	u16	wWidth; //��Ƶ����ͼ���� ��Windows��Ч(default:640)
	u16	wHeight;//��Ƶ����ͼ��߶� ��Windows��Ч(default:480)
	EmMediaType   emCapType;    //�ɼ�����   (default:emMediaAV)
	EmPCCapFormat emPCCapFormat;//��Ƶ����֡��ʽ ��Windows��Ч(default:emCapPCFrameBMP)
//���²�������Ը����ն�, 
	u8 by720pFrameRate; //720p�ֱ�����֡��
	u8 byVgaFrameRate;  //˫��vga��֡��
	//xjx_080612
	u8 byD1FrameRate; //D1�ֱ�����֡��
public:
	tagTVideoParam(){ memset( this ,0 ,sizeof( struct  tagTVideoParam ) );}	
}TVideoParam, *PTVideoParam;


/************************************************************************/
/*��ѡЭ����Ϣ���ݽṹ����                                               */
/************************************************************************/
typedef struct tagTAVPriorStrategy 
{
    EmVideoFormat  emVideoFormat;  //��Ƶ��ѡЭ��
    EmAudioFormat  emAudioFormat;    //��Ƶ��ѡЭ��
    EmVideoResolution emVideoResolution; //�ֱ�����ѡЭ��
public:
	tagTAVPriorStrategy(){ memset( this ,0 ,sizeof( struct  tagTAVPriorStrategy ) );}	
}TAVPriorStrategy, *PTAVPriorStrategy;
/************************************************************************/
/* �����ش���Ϣ���ݽṹ����                                               */
/************************************************************************/
typedef struct tagTLostPackResend
{
	BOOL bUse;             //�Ƿ�����
	EmNetType emNetType;   //��������
	u8   byResendLevel;    //�ش��ȼ� 0<��,�ش�һ��> 1<��,�ش�����> 2<��,�ش�����>
	u16  wFirstTimeSpan;   //��һ���ش�����   default 40
	u16  wSecondTimeSpan;  //�ڶ����ش�����   default 80
	u16  wThirdTimeSpan;   //�������ش�����   default 160
	u16  wRejectTimeSpan;  //���ڶ�����ʱ���� default 200
	u16  wSendBufTimeSpan; //���ͻ���           default 1000
	BOOL bUseSmoothSend;   //����ƽ������
	BOOL bUseAdaptSend;  //˫����Ƶ���������ش�
public:
	tagTLostPackResend(){ memset( this ,0 ,sizeof( struct  tagTLostPackResend ) );}
}TLostPackResend,*PTLostPackResend;


/************************************************************************/
/*�������Ϣ���ݽṹ����                                               */
/************************************************************************/


//����ͷ��������
typedef struct tagTCameraTypeInfo
{
	s8 achName[MT_MAXLEN_CAMERA_TYPE_NAME];
	u8 byMaxAddr; //����ͷ����ֵַ
	u8 byMaxSpeedLevel;//����ͷ����ٶȼ��� 
public:
	tagTCameraTypeInfo(){ memset( this ,0 ,sizeof( struct  tagTCameraTypeInfo ) );}
}TCameraTypeInfo ,*PTCameraTypeInfo;


//����ͷ����
typedef struct tagTCameraCfg
{
    BOOL  bUse;
    s8  achCamera[MT_MAX_CAMERA_NAME_LEN+1];//����ͷ��
    u8  byAddr;  //����ͷ��ַ
    u8  bySpeedLevel; //����ͷ�����ٶ�
    EmSerialType emSerialType;
    u32_ip dwSerialServerIP; //���ڷ�����IP ,����ֵΪ0ʱ��ʾʹ�ñ��ش���
    u16 wSerialServerPort; //���ڷ������˿ں�    
public:
	tagTCameraCfg(){ memset( this ,0 ,sizeof( struct  tagTCameraCfg ) );}	
}TCameraCfg, *PTCameraCfg;

typedef struct tagTVideoStandard
{
	EmVideoType     emVideoType;
	BOOL            bIsInPort;    //�Ƿ�Ϊ����˿�
	EmVideoStandard emStandard;
public:
	tagTVideoStandard(){ memset( this ,0 ,sizeof( struct  tagTVideoStandard ) );}	
}TVideoStandard ,*PTVideoStandard;

/************************************************************************/
/*��ƵԴ��Ϣ���ݽṹ����                                               */
/************************************************************************/
typedef struct tagTVideoSource
{
    EmVideoInterface emMainCam;
    u8 byCPortIndex ;//C��������ʱ��������˿ںţ�0��ַ
    EmVideoInterface emVideoOut;
    u8  byFrequency; //VGAʱΪˢ����
public:
	tagTVideoSource(){ memset( this ,0 ,sizeof( struct  tagTVideoSource ) );}
}TVideoSource, *PTVideoSource;


//������Ϣ
typedef struct tagTSnapInfo
{
	BOOL bResult;		// ��ȡ���(�ɹ�TRUE /ʧ��FALSE)
	u32  dwMaxSize;		// ���ռ��С(�ֽ�)
	u32  dwUsedSize;		// ���ÿռ��С(�ֽ�)
	u32	 dwPicNum;	// ����ͼƬ����(��)
public:
	tagTSnapInfo(){ memset( this ,0 ,sizeof( struct  tagTSnapInfo ) );}
} TSnapInfo,*PTSnapInfo;

typedef struct tagTBannerInfo
{
	BOOL        bEnable;			// ʹ��(MT_ENABLE/MT_DISABLE)
	u32		    dwTextClr;			// ������ɫ
	u32		    dwBkgClr;			// ����ɫ
	EmTextAlign	emTextAlign;	// ���ֶ���ģʽ(TEXT_ALIGN_LEFT/TEXT_ALIGN_CENTER/TEXT_ALIGN_RIGHT)
	EmRollMode	emRollMode;		// ����ģʽ(ROLL_NOT_ROLL/ROLL_RIGHT_LEFT/ROLL_DOWN_UP)
	u8 	        byTransParent;		// ͸����
	EmRollSpeed	emRollSpeed;		// �����ٶ�(ROLL_SPEED_SLOW/ROLL_SPEED_NORMAL/ROLL_SPEED_FAST/ROLL_SPEED_FASTER)
	u8		    byRollNum;			// ��������(0:��ʾ�����ƹ���,1~255:��ʾ�û�ָ���Ĺ�������)
	u8		    byStayTime;			// ͣ��ʱ��(0:��ʾ��ͣ��,1~255:��ʾ�û�ָ����ʱ��,��λ��)
	u32		    dwStartXPos;		// ��Ļ��ʾ����ʼX����
	u32		    dwStartYPos;		// ��Ļ��ʾ����ʼY����
	u32		    dwDisplayWidth;		// ��Ļ��ʾ����Ŀ�(������Ϊ��λ)
	u32		    dwDisplayHeight;	// ��Ļ��ʾ����ĸ�(ָ�и�,������Ϊ��λ)
	u8	        achWinInfo[ 256 ];	// ���ڴ��Windows�������Ϣ(��\0����)
	s8          achBannerText[1024];//��ź������
public:
	tagTBannerInfo(){ memset( this ,0 ,sizeof( struct tagTBannerInfo ) );	}
} TBannerInfo, *PTBannerInfo;


/************************************************************************/
/*     ��������                                                         */
/************************************************************************/

/************************************************************************/
/* ���������Ϣ���ݽṹ�������                                         */
/************************************************************************/



/************************************************************************/
/* ���������Ϣ���ݽṹ���忪ʼ                                         */
/************************************************************************/

//�ն˱��
typedef struct tagTMtId
{
	u8 byMcuNo;
	u8 byTerNo;
	
public:
	tagTMtId(){ memset( this ,0 ,sizeof( struct tagTMtId ) );	}
	
}TMtId ,*PTMtId;

//����������Ϣ
typedef struct tagTConfBaseInfo
{
	s8	 achConfId[MT_MAX_CONF_ID_LEN + 1 ];			// ����ID
	s8	 achConfName[MT_MAX_CONF_NAME_LEN + 1 ];		// ������
	s8	 achConfNumber[ MT_MAX_CONF_E164_LEN + 1 ];	    // �������
	s8	 achConfPwd[ MT_MAXLEN_PASSWORD + 1 ];			// ��������
	BOOL bNeedPassword;                         //�Ƿ���Ҫ����
	u16  wConfDuration;							// �������ʱ��		
	EmVideoFormat   emVideoFormat;							// ������Ƶ��ʽ(VIDEO_H261��)
	EmAudioFormat   emAudioFormat;							// ������Ƶ��ʽ(AUDIO_MP3��)
	EmVideoResolution  emResolution;							// ������Ƶ�ֱ���(VIDEO_CIF��)
	BOOL  bIsAutoVMP;								// �Ƿ��Զ�����ϳ�
	BOOL  bIsMix;	    							// �Ƿ����
	u8				  bySecVideoFormat;				// ˫����ʽ
	EmVideoResolution emSecVidRes;					// ˫���ֱ���
	u8				  bySecVidFps;					// ˫��֡��

public:
	tagTConfBaseInfo(){ memset( this ,0 ,sizeof( struct tagTConfBaseInfo ) );	}
}TConfBaseInfo ,*PTConfBaseInfo;

//�����б���Ϣ
typedef struct tagTConfListInfo
{
	u8			  byConfNum;
	TConfBaseInfo atConfInfo[MT_MAX_CONF_NUM];
public:
	tagTConfListInfo(){ memset( this ,0 ,sizeof( struct tagTConfListInfo ) );	}
}TConfListInfo ,*PTConfListInfo;

//�ն���Ϣ
typedef struct tagTMtInfo
{
	TMtId tLabel;
	s8     achAlias[MT_MAX_NAME_LEN+1];

public:
	tagTMtInfo(){memset( this ,0 ,sizeof( struct tagTMtInfo) );}
}TMtInfo ,*PTMtInfo;

//��Ƶ�����״̬
typedef struct tagTMtVideoCodecStatus
{
	BOOL                bRuning;           //�Ƿ��ڹ���
	EmVideoFormat       emFormat;          //��Ƶ�����ʽ
	EmVideoResolution   emRes;             //��Ƶ�����ʽ
	u16                 wBitrate;          //��Ƶ��������(��λ:kbps)
	u16                 wAverageBitrate;   //����Ƶ��ƽ��������(��λ:kbps)
	BOOL                IsEncrypt;         //����Ƶ�����Ƿ����
	EmEncryptArithmetic emArithmetic;	   //���ӱ���ʹ�õļ����㷨	

public:
	tagTMtVideoCodecStatus()
	{ 
		memset ( this ,0 ,sizeof( struct tagTMtVideoCodecStatus) );
	}
}TMtVideoCodecStatus ,*PTMtVideoCodecStatus;

//�ն�״̬
typedef struct tagTTerStatus
{
	EmMtModel  emMtModel;				    //�ն��ͺ�
	EmFileSys  emFileSys;                   //�ļ�ϵͳ����

	u8		byEncVol;					//��ǰ��������(��λ:�ȼ�)
	u8		byDecVol;					//��ǰ��������(��λ:�ȼ�)
	BOOL	bIsMute;					//�Ƿ�����	
	BOOL	bIsQuiet;					//�Ƿ���			
	BOOL	bIsLoopBack;				//�Ƿ��Ի�
	BOOL    bIsInMixing;                //�Ƿ�μӻ���
	BOOL    bRegGkStat;			    	//GKע����	1 �ɹ� 0 ʧ��
	EmAction   emPollStat;				//��ѯ״̬		emStart ,emPause ,emStop /��ʼ/��ͣ/ֹͣ
	EmSite	emCamCtrlSrc;				    //��ǰ��������ͷԴ���� emLocal, emRemote
	u8		byLocalCamCtrlNo;			    //��ǰ���Ƶı�������ͷ��(1-6������ͷ)
	u8		byRemoteCamCtrlNo;			    //��ǰ���Ƶ�Զ������ͷ��(1-6������ͷ)
	u8      byE1UnitNum ;                   //�ն�E1ģ��ĵ�E1����
	BOOL	bFECCEnalbe;				//�Ƿ�����Զң
	BOOL    bLocalIsVAG;                //���صڶ�·����������Ƿ�VGA
	BOOL    bPVHasVideo;                //��һ·�Ƿ�����ƵԴ
	BOOL    bSVHasVideo;                //�ڶ�·�Ƿ�����ƵԴ
//һ�²��ֲ�����ʹ��
	BOOL	bIsAudioPowerTest;			//�Ƿ��ڲ�����Ƶ	
	BOOL	bIsLocalImageTest;			//�Ƿ񱾵�ͼ�����
	BOOL	bIsRemoteImageTest;			//�Ƿ�Զ��ͼ����� 
//	///////����״̬///////
	BOOL       bIsInConf;				//�Ƿ��ڻ�����	
	EmConfMode emConfMode;				//����ģʽ		1 ���� 2 ���		
    BOOL       bCallByGK;				//�Ƿ�ͨ��GK���� TRUE GK·�� FALSEֱ�Ӻ���
//	
//	///////�豸״̬///////
	BOOL	bMatrixStatus;				    //���þ���״̬		(TRUE ok FALSE err)
	u8		byCamNum;					    //����ͷ����	(0~6)
	BOOL	bCamStatus[MT_MAX_CAMERA_NUM];	//����ͷ״̬ (TRUE ok FALSE err)
	EmMtVideoPort emVideoSrc;					//��ǰ������ƵԴ(0:S����,1-6:C����)

	BOOL    bIsEncrypt;
//	//�������״̬
	EmAudioFormat	    emADecFormat;	//��Ƶ�����ʽ
	EmAudioFormat	    emAEncFormat;	//��Ƶ�����ʽ
	TMtVideoCodecStatus  tPVEncStatus;   //����Ƶ������
	TMtVideoCodecStatus  tSVEncStatus;   //����Ƶ������
	TMtVideoCodecStatus  tPVDecStatus;   //����Ƶ������
	TMtVideoCodecStatus  tSVDecStatus;   //����Ƶ������
//	
	u16		wSysSleep;					//����ʱ��(0x0��ʾ������)
//VOD states
	BOOL bIsInVOD;
	EmUIPosion   byVodUser;
	//////����״̬///////
public:
   tagTTerStatus(){ memset ( this ,0 ,sizeof( struct tagTTerStatus) );}
}TTerStatus ,*PTTerStatus;

typedef struct tagTMtMixParam
{
	u8 byMixNum;
	u8 byDIscussMode;
	TMtId atMtMixItem[MT_MAXNUM_MIX_MEMBER];
public:
	tagTMtMixParam()
	{
		memset( this, 0, sizeof( struct tagTMtMixParam) );
	}
}TMtMixParam, *PTMtMixParam;

// ��չ����ϳɲ���
typedef struct tagTMtVmpItem
{
	TMtId        tMt;       //����ϳɳ�Ա
	EmVMPMmbType emMmbType; //����Ա������
	u32          adwReserved[8];
public:
	tagTMtVmpItem(){ memset ( this ,0 ,sizeof( struct tagTMtVmpItem) );}
}TMtVmpItem, *PTMtVmpItem;
//����ϳɲ���
typedef struct tagTMtVMPParam
{
	BOOL    bIsCustomVMP;  //�Ƿ��Զ��廭��ϳ�
	BOOL    bIsAutoVMP;    //�Ƿ��Զ�����ϳ�
	BOOL    bIsBroadcast;
	EmVMPStyle emStyle;       //����ϳɷ��
	TMtVmpItem atMtVmpItem[MT_MAXNUM_VMP_MEMBER];
public:
	tagTMtVMPParam(){ memset ( this ,0 ,sizeof( struct tagTMtVMPParam) );}
}TMtVMPParam ,*PTMtVMPParam;



//��ѯ��Ϣ
typedef struct tagTMtPollInfo
{
	EmMediaType emMode;      //��ѯģʽ emMediaVide /emMediaAV 
	EmAction    emStat;      //    emStart/  emStop/  emPause ��ѯ״̬
	u16         wKeepTime;   //�ն���ѯ�ı���ʱ�� ��λ:��(s)
	u8			byMtNum;			// �μ���ѯ���ն˸���,0��ʾ��������ն�(��λ��,���CTRL_POLL_MAXNUM)
	TMtInfo	    atMtInfo[ MT_MAX_POLL_NUM ]; // �μ���ѯ���ն�<m,t>
public:
	tagTMtPollInfo(){ memset ( this ,0 ,sizeof( struct tagTMtPollInfo) );}
}TMtPollInfo ,*PTMtPollInfo;

//��ѯ����������
typedef struct tagTMtPollSchemeNameSet
{
	s8      achMtPollSchemeName[MAX_CHAIR_POLLSCHEME_NUM][MT_MAX_NAME_LEN + 1];
public:
	tagTMtPollSchemeNameSet(){ 
		memset ( this ,0 ,sizeof( struct tagTMtPollSchemeNameSet) );
	}
}TMtPollSchemeNameSet, *PTMtPollSchemeNameSet;

typedef struct tagTMtViewPollInfo
{
	EmMediaType emMode;      //��ѯģʽ emMediaVide /emMediaAV 
	EmAction    emStat;      //    emStart/  emStop/  emPause ��ѯ״̬
	u16         wKeepTime;   //�ն���ѯ�ı���ʱ�� ��λ:��(s)
	u8			byMtNum;			// �μ���ѯ���ն˸���,0��ʾ��������ն�(��λ��,���CTRL_POLL_MAXNUM)
	TMtInfo	    atMtInfo[ MT_MAX_POLL_NUM ]; // �μ���ѯ���ն�<m,t>
public:
	tagTMtViewPollInfo(){ memset ( this ,0 ,sizeof( struct tagTMtViewPollInfo) );}
}TMtViewPollInfo ,*PTMtViewPollInfo;
 
typedef struct tagTMtSimpConfInfo 
{
	TMtId tSpeaker;
	TMtId tChairMan;
	BOOL  bIsVAC;
	BOOL  bIsDisc;
	BOOL  bIsAutoVMP;
	BOOL  bIsCustomVMP;
public:
	tagTMtSimpConfInfo(){ memset( this, 0, sizeof( struct tagTMtSimpConfInfo ) ); }
}TMtSimpConfInfo, *PTMtSimpConfInfo;
  
//���������Ϣ
typedef struct tagTMtConfInfo
{
	s8          chConfId[MT_MAXLEN_CONFGUID+1];
	TMtKdvTime    tStartTime;//��ʼʱ�䣬����̨��0Ϊ������ʼ
	u16           wDuration;   //����ʱ��(����)��0��ʾ���Զ�ֹͣ
    u16           wBitRate;        //��������(��λ:Kbps,1K=1024)
    u16           wSecBitRate;     //˫�ٻ���ĵ�2����(��λ:Kbps,Ϊ0��ʾ�ǵ��ٻ���)
    EmVideoResolution emMainVideoResolution;  //����Ƶ��ʽ
    EmVideoResolution emSecondVideoResolution; //����Ƶ��ʽ
    EmVideoResolution emDoubleVideoResolution;   //�ڶ�·��Ƶ��ʽ,
    u8            byTalkHoldTime;                 //��С���Գ���ʱ��(��λ:��)

	s8            achConfPwd[MT_MAXLEN_PASSWORD+1];    //��������
    s8            achConfName[MT_MAX_CONF_NAME_LEN+1]; //������
    s8            achConfE164[MT_MAX_CONF_E164_LEN+1]; //�����E164����
	
	BOOL          bIsAudioPowerSel;   //�Ƿ���������
	BOOL          bIsDiscussMode;     //�Ƿ�����ģʽ
    BOOL          bIsAutoVMP;            //�Ƿ��Զ��໭��ϳ�
	BOOL          bIsCustomVMP;        //�Ƿ��Զ���໭��ϳ�
	BOOL          bIsForceBroadcast;//ǿ�ƹ㲥

    TMtId 	      tChairman;	   //��ϯ�նˣ�MCU��Ϊ0��ʾ����ϯ
    TMtId		  tSpeaker;		  //�����նˣ�MCU��Ϊ0��ʾ�޷�����
    TMtPollInfo   tPollInfo;        //������ѯ����,����ѯʱ�н�
    TMtVMPParam   tVMPParam;        //��ǰ��Ƶ���ϲ���������Ƶ����ʱ��Ч
  
public:
	tagTMtConfInfo(){ memset ( this ,0 ,sizeof( struct tagTMtConfInfo) );}
}TMtConfInfo ,*PTMtConfInfo;

//IP�����ַ
typedef struct tagTIPTransAddr
{
	u32_ip dwIP ;
	u16 wPort;
public:
	tagTIPTransAddr(){ memset( this, 0, sizeof( struct tagTIPTransAddr));}
}TIPTransAddr,*PTIPTransAddr;

//�ն˵�ַ
typedef struct tagTMtAddr
{
	EmMtAddrType emType;							//��ַ����
	u32_ip			 dwIP;						//�ն�IP��ַ
	s8			 achAlias[MT_MAX_H323ALIAS_LEN+1];		//(����)
public:
	tagTMtAddr(){memset( this ,0 ,sizeof( struct tagTMtAddr));	}
}TMtAddr,*PTMtAddr;




//�����ʶ
typedef struct tagTConfId
{
	u8  byGuid[MT_MAXLEN_CONFGUID];//����Id
	TMtAddr   tAlias;    //�������
public:
	tagTConfId(){ memset( this ,0 ,sizeof( struct tagTConfId)) ;	}
}TConfId ,PTConfId ;

//���в���
typedef struct tagTDialParam
{
	EmCallMode   emCallType;			// ��������:JOIN|CREATE|INVITE
	EmConfProtocol emProtocol;          // ͨ��Э��Э��
	u16			 wCallRate;			    // ��������(kbps)	
	TMtAddr	     tCallingAddr;		    // ���е�ַ(����ʱ�ɲ���)
	TMtAddr	     tCalledAddr;			// ���е�ַ		

	//////////////////////////////////////////////////////////////////////////
	//���½����ڴ�������
	BOOL		bCreateConf;		//�Ƿ��Ǵ�������
	TConfBaseInfo   tConfInfo;			//������Ϣ
	u8			byTerNum;			//�����ն˸���
	TMtAddr 	atList[MT_MAXNUM_INVITEMT];	//�����ն��б�
public:
	tagTDialParam(){ memset( this ,0 ,sizeof( struct tagTDialParam ) );}
}TDialParam,*PTDialParam;

// ������·״̬�ṹ
typedef struct tagTLinkState
{
	EmCallState emCallState; //�Ự״̬
	u32_ip			dwIpAddr;					  // �Զ�IP��ַ(������)
	s8  		achAlias[ MT_MAX_NAME_LEN + 1 ];  // �Զ˱���
	BOOL        bCalling;                         // TRUE = ����  FALSE=����
	EmCallDisconnectReason	emReason;   // ���йҶ�ԭ��
	BOOL        bGetChairToken;                   //�����ϯ����
	BOOL        bSeenByAll;                       //���㲥
	u16         wCallRate;                        //��������
	EmMtModel   emPeerMtModel;                    //add by xujinxing,07/07/26,�Զ��ͺ�
public:
	tagTLinkState(){ memset( this ,0 ,sizeof( struct tagTLinkState ) );}
}TLinkState,*PTLinkState;


//TEmbedFwNatProxy ��Ƕ����ǽ�������ýṹ
typedef struct tagTEmbedFwNatProxy
{
    BOOL   bUsed;
    u32_ip dwFwNatProxyServIP;
	s8     achPrxySrvName[MT_MAX_PROXYSERVER_NAME_LEN];
    u16    wFwNatProxyServListenPort;
    u16    wStreamBasePort;//ý����������ʼ�˿ں�
public:
	tagTEmbedFwNatProxy(){ memset( this ,0 ,sizeof( struct tagTEmbedFwNatProxy ) );}
}TEmbedFwNatProxy,*PTEmbedFwNatProxy;


//��̬NATӳ���ַ
typedef struct tagTNATMapAddr
{
	BOOL bUsed; //�Ƿ����þ�̬ӳ���ַ
	u32_ip  dwIP;  //ӳ���ַ
public:
	tagTNATMapAddr(){ memset( this ,0 ,sizeof( struct  tagTNATMapAddr ) );}
}TNATMapAddr,*PTNATMapAddr;

//SIP Register����
typedef struct tagTSipRegistrarCfg
{
	BOOL   bUsed;   //�Ƿ�ע��
	u32_ip dwRegIP; //ע�������IP��ַ
	u16    wRegPort;//ע��������˿�
	s8     achRegDomain[MT_MAX_PROXYSERVER_NAME_LEN];
	u16    wExpire;

	s8     achDisplayName[MT_MAX_NAME_LEN+1];  //����
    s8     achUserName[MT_MAX_NAME_LEN+1];     //ע����
	s8     achPassword[MT_MAX_PASSWORD_LEN+1]; //ע������
	s8     achHostDomain[MT_MAX_PROXYSERVER_NAME_LEN];//��������
	u32_ip dwHostIP;
	u16    wHostPort;      
public:
	tagTSipRegistrarCfg(){ memset( this, 0, sizeof(struct tagTSipRegistrarCfg) ); }
}TSipRegistrarCfg,*PTSipRegistrarCfg;

//GK����
typedef struct tagTGKCfg
{
	BOOL bUsed; //�Ƿ�ʹ��GK
	u32_ip  dwGKIP; //GK IP��ַ
    s8   achGkIpName[MT_MAX_H323GKSERVER_NAME_LEN]; //Gk������ַ
	s8   achGKPasswd[MT_MAX_PASSWORD_LEN + 1]; //Gk����
public:
	tagTGKCfg(){ memset( this ,0 ,sizeof( struct  tagTGKCfg ) );}
}TGKCfg,*PTGKCfg;

/************************************************************************/
/* ����GK��Ϣ���ݽṹ����                                               */
/************************************************************************/
typedef struct tagTInnerGKCfg
{
    BOOL bGKUsed; //�Ƿ���������GK
    u32_ip dwIp; //ip��ַ
    u32_ip dwMask; //��������
    u32_ip dwGateWay; //����
public:
    tagTInnerGKCfg(){ memset( this, 0, sizeof(struct tagTInnerGKCfg ) ); }   
}TInnerGKCfg, *PTInnerGKCfg;

/************************************************************************/
/* ����Proxy��Ϣ���ݽṹ����                                               */
/************************************************************************/
typedef struct tagTInnerProxyCfg
{
    BOOL bInnerProxyUsed; //�Ƿ����ô��������
    u32_ip dwIp; //ip��ַ
    u32_ip dwMask; //��������
    u32_ip dwGateWay; //����
public:
    tagTInnerProxyCfg(){ memset( this, 0, sizeof(struct tagTInnerProxyCfg ) ); }  
}TInnerProxyCfg, *PTInnerProxyCfg;

/************************************************************************/
/* WiFi����������Ϣ���ݽṹ����                                         */
/************************************************************************/
typedef struct tagTWiFiNetCfg
{
    BOOL   bWiFiUsed;  //�Ƿ�����WiFi 
    BOOL   bDHCP;      //�Ƿ�����DHCP
    u32_ip dwIp;       //ip��ַ
    u32_ip dwMask;     //��������
    u32_ip dwGateWay;  //����
public:
    tagTWiFiNetCfg(){ memset( this, 0, sizeof(struct tagTWiFiNetCfg ) ); }  
}TWiFiNetCfg, *PTWiFiNetCfg;

// TMonitorService������л�ҵ�����ݽṹ�� 
typedef struct tagTMonitorService
{
	BOOL bSwitchEnable;
	//����ʱ�л������ҵ���ʱ����
	u32   dwSwitchTimeout;
public:
	tagTMonitorService(){ memset( this ,0 ,sizeof( struct  tagTMonitorService ) );}
}TMonitorService,*PTMonitorService;

//���νṹ����
typedef struct  tagTRect
{
    u16  wLeft;
    u16  wTop;
    u16  wWidth;
    u16  wHeight;
public:
 	tagTRect(){ memset( this ,0 ,sizeof( struct  tagTRect ) );}
}TRect;

//˫�����ʱ�������
typedef struct tagTDualRation
{
    BOOL bSecondSendRateType;   //TRUE auto
    BOOL bSecondRecvRateType;   //������������
    u8 bySecondSendRate;  //��������Զ�ʱ˫���������ʵı���ֵ
    u8 bySecondRecvRate;  //˫���������ʵı���ֵ
    u8 byPrimaryRecvRate; //�����������ʵı���ֵ
    tagTDualRation(){ memset( this ,0 ,sizeof( struct  tagTDualRation ) );}
}TDualRation, *PTDualRation;

//	ͼ���������
typedef struct tagTImageAdjustParam
{	 
	u8  wBrightness;//����  	 
	u8  wContrast;   //�Աȶ�  	
	u8  wSaturation; //ɫ�ʱ��Ͷ� 
public:
	tagTImageAdjustParam(){ memset( this ,0 ,sizeof( struct  tagTImageAdjustParam ) );}
	
}TImageAdjustParam,*PTImageAdjustParam;


//��Ƶ�������
typedef struct tagTVideoEncodeParameter    
{
	EmVideoFormat      emVideoFormat; 
	u16                byMaxKeyFrameInterval; // I֡�����P֡��Ŀ
    u8                 byMaxQuant;  //�����������
	u8                 byMinQuant;  //��С��������
    BOOL               bUseFixedFrame; //�Ƿ�ʹ�ù̶�֡��
	u8	               byFrameRate;  //֡��
	BOOL               bFramePerSecond;  //֡�ʵ�λ TRUE�� ֡/��  FALSE����/֡ 

    EmEncodeMode emEncodeMode;     //���뷽ʽ
	EmVideoResolution  emVideoResolution;
	u32                wChanMaxBitrate; // ��λ Kbps
//��������ֻ����windowsƽ̨������
//��Ӳɼ�ͼ����
	u16	m_wWidth; //��Ƶ����ͼ���� ��Windows��Ч(default:640)
	u16	m_wHeight;//��Ƶ����ͼ��߶� ��Windows��Ч(default:480)
	EmMediaType   emCapType;    //�ɼ�����   (default:emMediaAV)
	EmPCCapFormat emPCCapFormat;//��Ƶ����֡��ʽ ��Windows��Ч(default:emCapPCFrameBMP)
public:
	tagTVideoEncodeParameter(){ memset( this ,0 ,sizeof( struct  tagTVideoEncodeParameter ) );}	
}TVideoEncodeParameter ,*PTVideoEncodeParameter;

typedef struct tagTEncryptKey
{
	u8 byLen;   //��Կ����
	u8 byKey[MT_MAXLEN_ENCRYPTKEY]; //��Կ����
public:
	tagTEncryptKey(){ memset( this ,0 ,sizeof( struct  tagTEncryptKey ) );}	
}TEncryptKey,*PTEncryptKey;

//��Ƶͨ������
typedef struct tagTVideoChanParam
{
	EmVideoFormat     emVideoFormat;
	EmVideoResolution emVideoResolution;
	u32                wChanMaxBitrate; // ��λ Kbps
	u8                 byPayload;       //��̬�غ�
	TEncryptKey        tKey;            //��tKey.byLen=0 ��ʾ������
	BOOL               bIsH239;
	u8                 byFrameRate;          //֡��
 // 	u8                 byFrameRate;     2005-12-19 ������ί���ŷ����
public:
	tagTVideoChanParam()
	{ 
		emVideoFormat = emVEnd;
		emVideoResolution = emVResEnd;
		wChanMaxBitrate   = 0;
		byPayload         = 0;
		memset( &tKey ,0 ,sizeof(tKey) );
		bIsH239  = FALSE;
		byFrameRate = 25;
	}	
}TVideoChanParam ,*PTVideoChanParam;

//��Ƶͨ������
typedef struct tagTAudioChanParam
{
	EmAudioFormat   emAudioFormat;
  
	u8               byPayload;     //��̬�غ�
	TEncryptKey      tKey;          //��tKey.byLen=0 ��ʾ������
public:
	tagTAudioChanParam()
	{
		emAudioFormat = emAEnd;
		byPayload     = 0;
		memset( &tKey ,0 ,sizeof(tKey));
	}
}TAudioChanParam ,*PtagTAudioChanParam;

//***************************** VOD *************************************
//
//��½VOD�������û���Ϣ
//
typedef struct tagTVODUserInfo
{
	TIPTransAddr m_tIp;  //VOD��������ַ
	s8   m_achUserName[VOD_MAX_USER_NAME_LENGTH + 1];//�û���
	s8   m_achUserPass[VOD_MAX_PASSWORD_LENGTH + 1];//�û�����
	BOOL m_bRecordNamePass; //�´ε�¼�Ƿ���ʾ�û���������
public:
	tagTVODUserInfo()
	{
		memset(this,0,sizeof(tagTVODUserInfo));
	}
}TVODUserInfo,*PTVODUserInfo;


//
// vod �ļ���Ϣ ���ṹȡ�� TVODFileNameInfo+TVODFileInfo 
//
typedef struct tagTVODFile
{
	s8   achName[ MT_MAX_NAME_LEN + 1 ]; // �ļ���
    BOOL bIsFile;     // TRUE =file FALSE= folder
    u32  dwFileSize;  // �ļ�����
	//-- �ļ���Ϣ--
	BOOL bIsInfoValid;       //�ļ���Ϣ�Ƿ���Ч
	u32 dwRecordTime;        //¼��ʱ�䣬
    u32 dwDuration;          //������ʱ��������
    EmAudioFormat emAudio;          //��Ƶ�� emAEnd��ʾû�и�·���� 
    EmVideoFormat emPrimoVideo;     //��Ƶ1��emVEnd��ʾû�и�·���� 
    EmVideoFormat emSecondVideo;    //��Ƶ2��emVEnd��ʾû�и�·����
public:
	tagTVODFile(){ memset( this ,0 ,sizeof( struct  tagTVODFile ) );}
}TVODFile;
//
// Files from VODServer Directory 
//
 
typedef struct tagTE1Group
{                                                                                                            
	u8  byGroupIndex;              // E1�������
    u32 dwE1Mask;                 // ʹ�õ�E1������                                                                    
    u32_ip  dwIP;                  //  ip��ַ                                                                          
	u32_ip  dwIPMask;             //  ����       
	EmDLProtocol emProtocol;       //�ӿ�Э���װ����,����ǵ�E1���ӿ���ָ��PPP/HDLC                                                                   
	BOOL  bEnable;               //�Ƿ�����        
	// ��ͨ������
    EmAuthenticationType emAuthenticationType;//PPP���ӵ���֤����PAP/CHAP,Ĭ����emPAP 
    u32  dwFragMinPackageLen;       //  ��С��Ƭ�������ֽ�Ϊ��λ����Χ20~1500��Ĭ����20                                 
	s8   achSvrUsrName[MT_MAX_E1_NAME_LEN+1]; 	/* ������û�����  */                                  
	s8   achSvrUsrPwd[MT_MAX_E1_NAME_LEN+1];   	/* ������û�����  */                         
	s8   achSentUsrName[MT_MAX_E1_NAME_LEN+1];	/* �ͻ����û����ƣ��������Զ���֤ */                                           
	s8   achSentUsrPwd[MT_MAX_E1_NAME_LEN+1]; 	/* �ͻ����û����룬�������Զ���֤ */  
	u32  dwVal;                   //����
public:
	tagTE1Group(){ memset( this ,0 ,sizeof( struct  tagTE1Group ) );}
}TE1Group, *PTE1Group;

//
// File Info from VODServer
//

//
// Request Play Info from UI
//

typedef struct tagTVideoSourceInfo
{
	EmMtVideoPort  emVideoPort;
	s8  achPortName[MT_MAX_PORTNAME_LEN +1];
public:
	tagTVideoSourceInfo( ) { memset( this, 0, sizeof ( *this ) );	}
}TVideoSourceInfo,*PTVideoSourceInfo;


//�ⲿ������Ϣ
typedef struct tagTExternalMatrixInfo 
{
	s8 TypeName[ MT_MAX_AVMATRIX_MODEL_NAME ]; //�����ͺ�
	u8 OutPort; //ָ��������Ͽں�
	u8 InPortTotal; //����˿����� 
public:
	tagTExternalMatrixInfo( ) { memset( this, 0, sizeof ( *this ) );	}

} TExternalMatrixInfo, *PTExternalMatrixInfo;


//�ڲ����󷽰��ṹ
typedef struct tagTAVInnerMatrixScheme
{
	  EmMatrixType  emType; //��������
		s8 achName[ MT_MAXLEN_AVMATRIX_SCHEMENAME + 1 ]; 
		u8 byIndex; 
		//
		// ����˿ں�( 1 - 6 )
		// ��������˿����ӵ�����˿�
		//
		u8 abyOutPort2InPort[ 6 ]; 
		//
		// �˿�( 1- 6 )����
		//
		s8 achOutPortName[6][ MT_MAXLEN_AVMATRIX_SCHEMENAME + 1 ];
		s8 achInPortName [6][ MT_MAXLEN_AVMATRIX_SCHEMENAME + 1 ];
public:
	tagTAVInnerMatrixScheme( )
	{
		memset( this, 0, sizeof ( struct tagTAVInnerMatrixScheme ) );
	}
}TAVInnerMatrixScheme,*PTAVInnerMatrixScheme;

//
//    ����֪ͨ���ݽṹ
//

/************************************************************************/
/* ���������Ϣ���ݽṹ�������                                         */
/************************************************************************/

//////////////////////////////////////////////////////////////////////////
//����ʱ�Զ�������������
typedef struct tagTBitRateAdjust
{
	BOOL bEnable;   //�Ƿ�����
	u16  wInterval;  //ʱ����
	u16  wLostTimes; //��������
	u16  wDescRatio; //���ٱ���
	u16  wLowDescRatio; //���ٽ�������
	u16  wDelayInterval;  //�ӳ�ʱ��
public:
	tagTBitRateAdjust(){ memset( this ,0 ,sizeof( struct  tagTBitRateAdjust ) );}
}TBitRateAdjust,*PTBitRateAdjust;

//////////////////////////////////////////
//������ͳ����Ϣ
typedef struct tagTCodecPackStat
{
	u16    wBitrate;       //ʵʱ����
	u16    wAvrBitrate;    //ƽ������
	u32    dwLostPacks;    //������
	u32    dwTotalPacks;   //�շ�����
	u32    dwFrames;       //�շ�֡��
	u8     byLostFrameRate;//��֡��(2��)%d   
public:
	tagTCodecPackStat(){ memset( this ,0 ,sizeof( struct  tagTCodecPackStat ) );}
}TCodecPackStat,*PTCodecPackStat;

//��Ƶͳ����Ϣ
typedef struct tagTVideoStatistics
{
	BOOL             bH239;	
	EmVideoFormat     emFormat;      //��ʽ
	EmVideoResolution emRes;
	TCodecPackStat    tPack;
public:
	tagTVideoStatistics(){ memset( this ,0 ,sizeof( struct  tagTVideoStatistics ) );}
}TVideoStatistics ,*PTVideoStatistics;

//��Ƶͳ����Ϣ
typedef struct tagTAudioStatistics
{
	EmAudioFormat     emFormat;      //��ʽ
	TCodecPackStat    tPack;
public:
	tagTAudioStatistics(){ memset( this ,0 ,sizeof( struct  tagTAudioStatistics ) );}
}TAudioStatistics ,*PTAudioStatistics;

/************************************************************************/
/* PCMT��ƵԴ��Ϣ Add by FangTao                                                       */
/************************************************************************/
typedef struct tagTCapType
{
	s8 m_achCapFileName[MT_MAX_FULLFILENAME_LEN+1];
	EmCapType emCapType;
public:
	tagTCapType(){ memset(this ,0 ,sizeof( tagTCapType)); }
}TCapType ,*PTCapType;

//����ͳ����Ϣ
typedef struct tagTCallInfoStatistics
{
	u16               wCallBitrate;//��������
	EmEncryptArithmetic emRecvEncrypt; //������ռ�������
	EmEncryptArithmetic emSendEncrypt; //���鷢�ͼ�������
	TAudioStatistics  tRecvAudio;//��Ƶ���ո�ʽ
	TAudioStatistics  tSendAudio;//��Ƶ���͸�ʽ

	TVideoStatistics tPrimoRecvVideo;  //����Ƶ����ͳ����Ϣ 
	TVideoStatistics tPrimoSendVideo;  //����Ƶ����ͳ����Ϣ 
	TVideoStatistics tSencodRecvVideo; //�ڶ�·��Ƶ����ͳ����Ϣ 
	TVideoStatistics tSecondSendVideo; //�ڶ�·��Ƶ����ͳ����Ϣ 
public:
	tagTCallInfoStatistics()
	{
		wCallBitrate = 0;
		emRecvEncrypt = emEncryptNone;
		emSendEncrypt = emEncryptNone;
		tRecvAudio.emFormat = emAEnd;
		memset(&tRecvAudio.tPack,0,sizeof(tRecvAudio.tPack));
		memcpy(&tSendAudio,&tRecvAudio,sizeof(tSendAudio));

		tPrimoRecvVideo.bH239 = FALSE;
		tPrimoRecvVideo.emFormat = emVEnd;
		tPrimoRecvVideo.emRes = emVResEnd;
		memset(&tPrimoRecvVideo.tPack,0,sizeof(tPrimoRecvVideo.tPack));

		memcpy(&tPrimoSendVideo,&tPrimoRecvVideo,sizeof(tPrimoRecvVideo));
		memcpy(&tSencodRecvVideo,&tPrimoRecvVideo,sizeof(tPrimoRecvVideo));
		memcpy(&tSecondSendVideo,&tPrimoRecvVideo,sizeof(tPrimoRecvVideo));
	}

}TCallInfoStatistics,*PTCallInfoStatistics;


/************************************************************************/
/* ˫������Ϣ                                                           */
/************************************************************************/
typedef struct tagTDualStreamBoxInfo
{
	BOOL   m_bUsed;
	u32_ip m_dwIp;
	u16    m_wPort;
public:
	tagTDualStreamBoxInfo(){ memset( this ,0 ,sizeof( struct  tagTDualStreamBoxInfo ) );}
}TDualStreamBoxInfo,*PTDualStreamBoxInfo;


/************************************************************************/
/* ������ͳ����Ϣ                                                       */
/************************************************************************/

typedef  struct tagTFileTransfer 
{
public:
	//�汾��		0x0100
	u16 wProtocolIdentifer;

	// �ļ����䵱ǰ��Ƭ��ţ�0��ʼ��ţ�ѭ�����
	u16 wFileSliceNo;


	//�ļ�����		̨��,������Ϣ,��Ļ
	u8 byType;

	//ԭ��
	u8 byRspInfo;
	
	//�ļ���ʶ��
	u16 wFileIdentifer;

	//��Ϣ����󳤶�
	u16 wPakageMaxLen;

	//�û����ݳ��ȣ�ֵ=��Ϣͷ+�ļ���Ƭ����
	u16 wDataLen;
public:
	tagTFileTransfer(){ memset( this ,0 ,sizeof( struct  tagTFileTransfer ) );}
}TFileTransfer,*PTFileTransfer;

/************************************************************************/
/* ˫���нṹ����
/************************************************************************/
typedef struct tagTDVBNetSession
{
	 //[xujinxing]
	 u32_ip   m_dwRTPAddr; /*RTP��ַ*/
	 u16    m_wRTPPort;  /*RTP�˿�*/
	 u32_ip   m_dwRTCPAddr;/*RTCP��ַ*/
	 u16    m_wRTCPPort; /*RTCP�˿�*/
public:
	tagTDVBNetSession(){ memset( this ,0 ,sizeof( struct  tagTDVBNetSession ) );}
}TDVBNetSession,*PTDVBNetSession;

typedef struct tagTDVBNetSndParam
{
	 u8 m_byNum;
	 TDVBNetSession m_tLocalNet;
	 TDVBNetSession m_tRemoteNet[MT_MAX_NETSND_DEST_NUM];
public:
	tagTDVBNetSndParam(){ memset( this ,0 ,sizeof( struct  tagTDVBNetSndParam ) );}
}TDVBNetSndParam,*PTDVBNetSndParam;

typedef struct tagTDVBLocalNetParam
{
	 TDVBNetSession  m_tLocalNet;
	 u32_ip        m_dwRtcpBackAddr;/*RTCP�ط���ַ*/
	 u16         m_wRtcpBackPort; /*RTCP�ط��˿�*/ 
public:
	tagTDVBLocalNetParam(){ memset( this ,0 ,sizeof( struct  tagTDVBLocalNetParam ) );}
}TDVBLocalNetParam,*PTDVBLocalNetParam;

typedef struct tagTDVBVideoEncParam
{
	u8  m_byEncType;   /*ͼ���������*/
    u8  m_byRcMode;    /*ͼ��ѹ�����ʿ��Ʋ���*/
    u16  m_byMaxKeyFrameInterval;/*I֡�����P֡��Ŀ*/
    u8  m_byMaxQuant;  /*�����������(1-31)*/
    u8  m_byMinQuant;  /*��С��������(1-31)*/
    u8  m_byReserved1; /*����*/
    u8  m_byReserved2; /*����*/
    u8  m_byReserved3; /*����*/
    u16  m_wBitRate;    /*���������(Kbps)*/
    u16  m_wReserved4;  /*����*/		
	u32 m_dwSndNetBand;/*���緢�ʹ���(��λ:Kbps,1K=1024)*/   
    u32 m_dwReserved5; /*����*/

	u8    m_byPalNtsc;    /*ͼ����ʽ(PAL��NTSC)*/	
	u8    m_byCapPort;    /*�ɼ��˿ں�: 1~7��Ч����KDV8010�ϣ�S���Ӷ˿ں�Ϊ7��C���Ӷ˿ں�ȱʡΪ2*/
	u8	m_byFrameRate;  /*֡��(default:25)*/	
	u8    m_byImageQulity;/*ͼ��ѹ������,0:�ٶ�����;1:��������*/
	u8    m_byReserved6;  /*����*/
	u16	m_wVideoWidth;  /*ͼ����(default:640)*/
	u16	m_wVideoHeight; /*ͼ��߶�(default:480)*/


	u8  m_byFrameFmt; // �ֱ��� 0:���̶�����, 1: half cif, 2: 1 cif, 3: 2 cif,  4: 4 cif,  5: ����ͼ��ϳɱ���  
	u8	m_byFrmRateCanSet; //֡���Ƿ�������趨 ?
	u8  m_byFrmRateLittleThanOne; // ֡���Ƿ�С��1 ?
public:
	tagTDVBVideoEncParam(){ memset( this ,0 ,sizeof( struct  tagTDVBVideoEncParam ) );}
}TDVBVideoEncParam,*PTDVBVideoEncParam;

typedef struct tagTSitecallInformation
{
	BOOL m_bIsCustomConf;
	s8 m_achConfName[MT_MAX_CONF_NAME_LEN+1];
	s8 m_achConfPwd[MT_MAXLEN_PASSWORD+1];
	BOOL m_bLocalPay;	
	s8 m_achConfCard[MT_MAX_CONF_NAME_LEN+1];
	s8 m_achConfCardPwd[MT_MAXLEN_PASSWORD+1];
	u8 m_byMultiPicCount;
	EmCallRate        m_emRate;
	EmVideoFormat     m_emVideoType;
	EmVideoResolution m_emVideoFormat;
	EmAudioFormat     m_emAudioFormat;
	u8   m_byTerninalCount;
	TMtAddr m_atTerminalE164Info[MT_MAX_CALLSITE_TERNINAL];
	TMtAddr m_atTerminalH323Info[MT_MAX_CALLSITE_TERNINAL];
public:
	tagTSitecallInformation()
	{
		memset(this,0,sizeof(tagTSitecallInformation));
		m_emRate = emRaten64;
		m_emVideoType = emVH263;
		m_emVideoFormat = emVCIF;
		m_emAudioFormat = emAG711a;
		m_bLocalPay = TRUE;
	}
}TSitecallInformation,*PTSitecallInformation;

typedef struct tagTTransparentSerial
{
    EmSerialType  m_emComType;
	u32           m_nDataLen;
    s8            m_achData[128];
public:
	tagTTransparentSerial(){ memset( this ,0 ,sizeof( struct  tagTTransparentSerial ) );}
}TTransparentSerial,*PTTransparentSerial;

typedef struct tagTPeerCapabilityInfo
{
    BOOL m_bMix;                        //����
    BOOL m_bVAC;                        //��������
    BOOL m_bCustomVMP;                  //���ƻ���ϳ�
    BOOL m_bAutoVMP;                    //�Զ�����ϳ�
    BOOL m_bEndConf;                    //��������
    BOOL m_bInvateMt;                   //�����ն�
    BOOL m_bDropMt;                     //ɾ���ն�
    BOOL m_bSelSpeaker;                 //ָ��/ȡ��������
    BOOL m_bSelChair;                   //ָ��/������ϯ
    BOOL m_bSelSource;                  //ѡ���ն�
    BOOL m_bFECC;                       //Զ������ͷң��
    BOOL m_bQuiet;                      //Զ�˾���
    BOOL m_bMute;                       //Զ������
    BOOL m_bConfReq;                    //�������봦��
    BOOL m_bOnlineList;                 //�����ն��б�
    BOOL m_bOfflineList;                //�����ն��б�
	BOOL m_bPicSwitch;                  //�����л�
	BOOL m_bSelSpeakingUser;            //���� 
	BOOL m_bForceBroadcast;             //ǿ�ƹ㲥
public:
	tagTPeerCapabilityInfo(){ memset( this ,0 ,sizeof( struct  tagTPeerCapabilityInfo ) );}
}TPeerCapabilityInfo,*PTPeerCapabilityInfo;


/************************************************************************/
/*              ��ݼ��ṹ��                                            */
/************************************************************************/
typedef struct tagTRapidKey 
{
	EmMtVideoPort emMainVidSrcBtn;
	EmHotKeyType emRedBtn;
	EmHotKeyType emYellowBtn;
	EmHotKeyType emGreenBtn;
public:
	tagTRapidKey(){ memset( this ,0 ,sizeof( struct  tagTRapidKey ) );}
}TRapidKey, *PTRapidKey;

/************************************************************************/
/*              �ն����������ṹ��                                      */
/************************************************************************/
//�����汾�е��ļ���Ϣ
typedef struct tagTVerFileInfo
{
    EmMtOSType   m_emFileType;       //�ļ�����(Linux,Vxworks)
    u32          m_dwFileSize;       //�ļ���С(���ֽڼ���)
    s8           m_szFileName[MT_MAX_FILESRV_FILENAME_LEN];//�ļ���
public:
	tagTVerFileInfo(){ memset( this ,0 ,sizeof( struct  tagTVerFileInfo ) );}
}TVerFileInfo, *PTVerFileInfo;

//�����汾����Ϣ
typedef struct tagTVerInfo
{ 
    u8 m_byFileNum;
    s8 m_achBugReport[MT_MAX_FILESRV_BUG_REPORT_LEN];
    s8 m_achSoftVer[MT_MAX_FILESRV_SOFTWARE_VER_LEN];
    TVerFileInfo m_atVerFile[MT_MAX_FILESRV_DEVFILE_NUM];
public:
	tagTVerInfo(){ memset( this ,0 ,sizeof( struct  tagTVerInfo ) );}
}TVerInfo,*PTVerInfo;


// FEC������Ϣ�ṹ
typedef struct tagTFecInfo
{
	BOOL   m_bEnableFec;   //��Ƶ�Ƿ�ʹ��ǰ�����
	u8     m_byAlgorithm;  //����fec�㷨 0:NONE 1:RAID5 2:RAID6
	u16    m_wPackLen;     //����fec���а�����
	BOOL   m_bIntraFrame;  //�Ƿ�֡��fec
	u32    m_dwDataPackNum; //����fec��x�����ݰ�
	u32    m_dwCrcPackNum;  //����fec��y�������
public:
	tagTFecInfo(){ memset( this, 0, sizeof( struct tagTFecInfo ) ); }
}TFecInfo,*PTFecInfo;

//ruiyigen 091216
typedef struct tagTVInnerMatrixScheme
{
	u8 byIndex;
	s8 achName[MT_MAXLEN_AVMATRIX_SCHEMENAME + 1];
	u8 abyOutPort2InPort[MT_HD_MAX_AV_OUTPORT_NUM]; //����ΪDVI1,DVI2,DVI3,SDI���
	u8 abyDVIMode[MT_DVI_PORT_NUM];//����ΪDVI1,DVI2,DVI3����,DVI1,DVI2,DVI3���
	s8 achOutPortName[6][ MT_MAXLEN_AVMATRIX_SCHEMENAME + 1 ];
	s8 achInPortName [6][ MT_MAXLEN_AVMATRIX_SCHEMENAME + 1 ];
public:
	tagTVInnerMatrixScheme()
	{
		memset( this, 0, sizeof(struct tagTVInnerMatrixScheme) );
		memset( abyOutPort2InPort, HD2G_VIDEO_IN_INVALID, sizeof(abyOutPort2InPort) );
	}
}TVInnerMatrixScheme,*PTVInnerMatrixScheme;


template < class T >
T SAFE_CAST( T &t, u8 *p )
{
	if (NULL == p) return t;
	memcpy( &t, p, sizeof( T ) );
	return t;
}



//char* GetStructVersion();

// ��ַ����Ŀ��Ϣ
typedef struct tagTAddrEntry
{
    s8      m_achEntryName[ MT_MAX_NAME_LEN + 1 ];		// ��Ŀ����
    s8      m_achIpaddr[ MT_MAX_H323ALIAS_LEN + 1 ];	// ���е�ַ
    u32     m_dwCallTime;                               // ����ʱ��
    u16	    m_wCallRate;								// ��������
	BOOL    m_bTeleCall;
public:
	tagTAddrEntry(){ memset( this ,0 ,sizeof( struct  tagTAddrEntry ) );}
}TAddrEntry,*PTAddrEntry;


/************************************************************************/
/* ���ô��������ν��������                                           */
/************************************************************************/
typedef struct tagTPxyIPCfg
{
    BOOL bUsed;
    u32_ip dwIP;         //IP��ַ
    u32_ip dwMask;       //��������
    u32_ip dwGateway;    //���ص�ַ
public:
	tagTPxyIPCfg(){ memset( this ,0 ,sizeof( struct  tagTPxyIPCfg ) );}
}TPxyIPCfg, *PTPxyIPCfg;

typedef struct tagTWifiLinkInfo
{
    s8       achSSID[MT_MAX_NAME_LEN];            /* WiFi network name */
	s8       achBssMacAddr[MT_MAX_NAME_LEN];      /* Bss Mac Address*/
    u32      dwSignalLevel;                         /*Signal level : 0-100*/
    u32      dwLinkRate;				 	        /* Rate, unit: mpbs */
    u32      dwChannel;                             /* Wireless channel number*/
    u8       byAuthType;                            /*Authentication method*/
    u8       byEncrytoType;                         /*Encryto method*/
	u8       byNetType;                             /*ad-hoc or infra*/
public:
	tagTWifiLinkInfo(){ memset( this ,0 ,sizeof( struct  tagTWifiLinkInfo ) );}
}TWifiLinkInfo, *PTWifiLinkInfo;

typedef struct tagTWifiScanResult
{
    u32 dwBssNum;   /*Number of Link info, 0 -- WIFI_MAX_BSS_NUM*/
    TWifiLinkInfo tLinkInfo[WIFI_MAX_BSS_NUM];
public:
	tagTWifiScanResult(){ memset( this ,0 ,sizeof( struct  tagTWifiScanResult ) );}
} TWifiScanResult, *PTWifiScanResult;

typedef struct tagTWifiLinkCfgItem
{
	u32  dwId;
    s8   achCfgName[WIFI_MAX_NAME_LEN]; /*Configure name, shall not be empty when need save */
    TWifiLinkInfo tWifiLinkInfo;           /* Wifi link basic info*/

    s8   achWepKey1[WIFI_MAX_KEY_LEN];     /*Web key, shall not be null when byAuthType is Web*/
    s8   achWepKey2[WIFI_MAX_KEY_LEN];
    s8   achWepKey3[WIFI_MAX_KEY_LEN];
    s8   achWepKey4[WIFI_MAX_KEY_LEN];
    s8   achWpaPasswd[WIFI_MAX_KEY_LEN];  /*Wpa key, shall not be null when byAuthType is wpa or wpa2*/
public:
	tagTWifiLinkCfgItem(){ memset( this ,0 ,sizeof( struct  tagTWifiLinkCfgItem ) );}
}TWifiLinkCfgItem, *PTWifiLinkCfgItem;


//ɨ��SSID��Ϣ
typedef struct tagTWiFiBSSIDInfo
{
    u8                      byPSKOFF;                              //PSK or enterprise
    EmWiFiNetType           emNetType;                             //��������
    EmWiFiEncryptType       emEncryptType;                         //��������
    EmWiFiEncryptArithmetic emArithType;                           //�����㷨
    BOOL                    bEncrypt;                              //�Ƿ����
    u32                     dwChannel;                             //Wireless channel number
    u32                     dwBeaconInterval;                      //BCN��ʡ�������
    u32                     dwLinkRate;				 	           //Rate, unit: mpbs 
    u32                     dwSignalLevel;                         //�ź�ǿ��
    s8                      achBSSMacAddr[MT_WIFI_MAX_NAME_LEN];   // Bss Mac Address
    s8                      achSSID[MT_WIFI_MAX_NAME_LEN];         //WiFi network name
    s8                      achPasswd[MT_WIFI_MAX_PASSWORD_LEN];   //��������
public:
    tagTWiFiBSSIDInfo()
    {
        memset( this, 0, sizeof( struct tagTWiFiBSSIDInfo ) );
    }
}TWiFiBSSIDInfo, *PTWiFiBSSIDInfo;

//����SSID��Ϣ,�Ƿ���Ҫ����������������Ϣ��ʡ��ģʽ,��ȷ��?
typedef struct tagTWiFiBSSIDCfg
{
    u8                      byPSKOFF;                              //PSK or enterprise
    EmWiFiNetType           emNetType;                             //��������
    EmWiFiEncryptType       emEncryptType;                         //��������
    EmWiFiEncryptArithmetic emArithType;                           //�����㷨
    BOOL                    bEncrypt;                              //�Ƿ����
	u32                     dwCfgPri;                              //�����������ȼ�
    u32                     dwChannel;                             //Wireless channel number
    s8                      achSSID[MT_WIFI_MAX_NAME_LEN];           //WiFi network name
    s8                      achPassword[MT_WIFI_MAX_PASSWORD_LEN];   //��������
    //u8                      byCfgType;                             //ɨ���������
    //s8                      achBSSMacAddr[MT_WIFI_MAX_NAME_LEN];   // Bss Mac Address
    //u32                     dwBeaconInterval;                      //BCN��ʡ�������
    //u32                     dwLinkRate;				 	           //Rate, unit: mpbs
    //u32                     dwSignalLevel;                         //�ź�ǿ��
public:
    tagTWiFiBSSIDCfg()
    {
        memset( this, 0, sizeof( struct tagTWiFiBSSIDCfg ) );
    }
}TWiFiBSSIDCfg, *PTWiFiBSSIDCfg;

typedef struct tagTGkRegInfo
{
	BOOL bRegisted;
	EmGKRegFailedReason emReason;
public:
	tagTGkRegInfo(){ memset( this ,0 ,sizeof( struct  tagTGkRegInfo ) );}
}TGkRegInfo, *PTGkRegInfo;

typedef struct tagTSipRegResult
{
	BOOL bRegistered;
	EmSipRegFailedReason emReason;
}TSipRegResult, *PTSipRegResult;

typedef struct tagTHdAudioPort
{
	u8 abHdAudPortIn[MT_MAX_HDAUDIOPORT_LEN];
	u8 abHdAudPortOut[MT_MAX_HDAUDIOPORT_LEN];
public:
	tagTHdAudioPort(){ memset( this ,0 ,sizeof( struct  tagTHdAudioPort ) );}
}THdAudioPort, *PTHdAudioPort;

typedef struct tagTMiscCfg
{
	BOOL bUseSlice; //�����а�����
public:
	tagTMiscCfg(){ memset( this ,0 ,sizeof( struct  tagTMiscCfg ) );}
}TMiscCfg, *PTMiscCfg;

typedef struct tagTVideoDisplayFrm
{
    u32 m_dw1080PFrm;
    u32 m_dw1080IFrm;
    u32 m_dwVGAFrm;
    u32 m_dw720PFrm;
    u32 m_dwSDFrm;
public:
		tagTVideoDisplayFrm()
		{
			memset( this, 0, sizeof( struct tagTVideoDisplayFrm ) );
    }
}TVideoDisplayFrm,*PTVideoDisplayFrm;


typedef struct tagTDownLoadPara
{
public:
	u8	byFileType;			//�ļ�����
	u8	byFileCount;		//�ļ�����
	s8  m_achFileName[255];	//�ļ���
	
public:
	tagTDownLoadPara()
	{
		byFileType = emMtFileBegin;
		byFileCount = 0;
		memset(m_achFileName, 0, sizeof(m_achFileName));
	}
	
	void SetFileType(u8 byType)	{ byFileType = byType; }
	u8	 GetFileType()			{ return byFileType; }
	u8	 GetFileCount()			{ return byFileCount; }
	
	BOOL AddFile(const s8* pszFileName)
	{
		if (!pszFileName)
		{
			return FALSE;
		}
		u8 byIndex;
		u8 byNameLen = strlen(pszFileName);
		u8 byCurBufIndex = 0;
		for (byIndex = 0; byIndex < byFileCount; ++byIndex)
		{
			byCurBufIndex += m_achFileName[byCurBufIndex];
			byCurBufIndex += sizeof(u8);
		}
		
		if ( (byCurBufIndex + byNameLen + 1) >= 255)
		{
			return FALSE;
		}
		m_achFileName[byCurBufIndex] = byNameLen;
		++byCurBufIndex;
		memcpy(&m_achFileName[byCurBufIndex], pszFileName, byNameLen);
		
		++byFileCount;
		return TRUE;
	}
	BOOL GetFileName(s8* pDestBuf, u8 byBufLen, u8 byNameIndex)
	{
		if (!pDestBuf)
		{
			return FALSE;
		}
		
		if ( byNameIndex >= byFileCount)
		{
			return FALSE;
		}
		
		u8 byIndex = 0;
		u8 byCurBufIndex = 0;
		for (byIndex = 0; byIndex < byNameIndex; ++byIndex)
		{
			byCurBufIndex += (m_achFileName[byCurBufIndex] + 1);
		}
		
		u8 byNameLen = m_achFileName[byCurBufIndex];
		if ( byNameLen + 1 > byBufLen)
		{
			return FALSE;
		}
		
		memcpy(pDestBuf, &m_achFileName[byCurBufIndex+1], byNameLen);
		pDestBuf[byCurBufIndex+byNameLen+1] = '\0' ;
		return TRUE;
	}
	
}TDownLoadPara,*PTDownLoadPara;


typedef struct tagTSecurePwd
{
	BOOL bUserCfgPwd;
	s8  achUserCfgPwd[MT_MAX_PASSWORD_LEN+1]; //�Ƿ�������������
public:
	tagTSecurePwd()
	{
		bUserCfgPwd = FALSE;
		memset( achUserCfgPwd, 0, sizeof( achUserCfgPwd ) );
	}
}TSecurePwd,*PTSecurePwd;
typedef struct tagTMtBackBGDColor
{
public:
	u8 RColor;    //R����
	u8 GColor;    //G����
	u8 BColor;    //B����
	u8 u8Transparency;
	tagTMtBackBGDColor()
	{
		RColor = 0;
		GColor = 0;
	    BColor = 0;
		u8Transparency = 0;
	}
}TMtBackBGDColor,*PTMtBackBGDColor;
/* SIP��Ϣ���ݽṹ����                                                 */
/************************************************************************/
typedef struct tagTSipCfg
{
    s8     achDisplayName[MT_MAX_NAME_LEN+1];  //����
    s8     achUserName[MT_MAX_NAME_LEN+1];     //ע����
	s8     achPassword[MT_MAX_PASSWORD_LEN+1]; //ע������
	s8     achHostDomain[MT_MAX_PROXYSERVER_NAME_LEN];//��������
	u16    wHostPort;                          //����˿�
    
	BOOL   bUseRegistrar;                      //�Ƿ�Register
    u32_ip dwRegistrarIp;                      //Registrar IP
	u16    wRegistrarPort;                     //Registrar�˿�
    s8     achRegistrarDomain[MT_MAX_PROXYSERVER_NAME_LEN]; //Registrar����
	u16    wExpire; 

    BOOL   bUseProxy;                          //�Ƿ�����Proxy
	u32_ip dwProxyIp;                          //Proxy IP
	u16    wProxyPort;                         //Proxy�˿�
	s8     achProxyDomain[MT_MAX_PROXYSERVER_NAME_LEN]; //Proxy����
public:
	tagTSipCfg(){memset(this , 0 ,sizeof( struct tagTSipCfg) );	}
}TSipCfg,*PTSipCfg;


/************************************************************************/
/*�������Ϣ���ݽṹ����                                               */
/************************************************************************/


/************************************************************************/
/*     ��������                                                         */
/************************************************************************/

/************************************************************************/
/* ���������Ϣ���ݽṹ�������                                         */
/************************************************************************/



/************************************************************************/
/* ���������Ϣ���ݽṹ���忪ʼ                                         */
/************************************************************************/


/************************************************************************/
/* ������ͳ����Ϣ                                                       */
/************************************************************************/



/************************************************************************/
/* �ļ�����ģ�鿪ʼ
/************************************************************************/






//char* GetStructVersion();

typedef struct tagTMtAddBannerParam
{
public:
	u32 dwXPos;
    u32 dwYPos;//��ʾ�����Y����
    u32 dwWidth;//��ʾ����Ŀ�
    u32 dwHeight;//��ʾ����ĸ�
    u32 dwBMPWight;//BMPͼ���
    u32 dwBMPHeight;//BMPͼ���
    u32 dwBannerCharHeight;//����߶ȣ�����Ҫ�������¹���ʱ��ȷ��ͣ�ٵ�λ��
    TMtBackBGDColor tBackBGDColor;//����ɫ 
    u32 dwBGDClarity;//������ɫ͸����
    u32 dwPicClarity;//����ͼƬ͸����
    u32 dwRunMode;//����ģʽ������or����or��ֹ���궨�����ϣ�
    u32 dwRunSpeed;//�����ٶ� �ĸ��ȼ����궨�����ϣ�
    u32 dwRunTimes;//�������� 0Ϊ�����ƹ���
	u32 bRunForever;//�����ƹ���
	u32 dwHaltTime;//ͣ��ʱ��(��)�����¹���ʱ��ÿ����һ���ֵ�ͣ�ټ����0ʼ��ͣ�����뾲ֹ��ͬ�� 
	tagTMtAddBannerParam()
	{
		dwXPos = 0;
		dwYPos = 0;
		dwWidth = 0;
		dwHeight = 0;
		dwBMPWight = 0;
		dwBMPHeight = 0;
		dwBannerCharHeight = 0;
		dwBGDClarity = 0;
		dwPicClarity = 0;
		dwRunMode = 0;
		dwRunSpeed = 0;
		dwRunTimes = 0;
		bRunForever = 0;
		dwHaltTime = 0;
	}
}TMtAddBannerParam;
typedef struct tagTMtBmpInfo
{
public:
    u32 dwWidth;    //ͼƬ����Ӧ����ƵԴ��ʽ���
    u32 dwHeight;  //ͼƬ����Ӧ����ƵԴ��ʽ�߶�
//     u8 *pBMP;
//     u32 dwBmpLen;
	tagTMtBmpInfo()
	{
		dwWidth = 0;
		dwHeight = 0;
	}
}TMtBmpInfo;

typedef struct tagTMtFullBannerParam
{
public:
    TMtBmpInfo tBmpInfo[3];//576i,720p,1080p������ʽ
    TMtAddBannerParam tBannerParam[3];//576i,720p,1080p������ʽ
    u32 Reserver;
	tagTMtFullBannerParam()
	{
		Reserver = 0;
	}
}TMtFullBannerParam;

// Region ��ӦSymbol̨����ʾ�ӿڱ仯
/*
Ops: Add
Signature: liujian - 6/4/2010
Other: ̨�����������������Ϣ����
*/
#ifndef MAX_LOGO_NAME_LEN
#define  MAX_LOGO_NAME_LEN (u8)32
#endif

typedef struct tagTMTBmpInfo
{
    u32 dwWidth;    //ͼƬ����Ӧ����ƵԴ��ʽ���
    u32 dwHeight;  //ͼƬ����Ӧ����ƵԴ��ʽ�߶�
}TMTBmpInfo;

typedef struct tagTMTAddLogoParam
{
    u32 dwXPos;
    u32 dwYPos;
    u32 dwLogoWidth;//logo��
    u32 dwLogoHeight;//logo��
    TMtBackBGDColor tBackBGDColor;    
}TMTAddLogoParam;

typedef struct tagTMTFullLogoParam
{
    TMTBmpInfo tBmpInfo[3];
    TMTAddLogoParam tLogoParam[3];
}TMTFullLogoParam;
// End Region
typedef struct tagTMtcBoxCallCfg
{
	u8		byUseIndex;							//��ǰʹ����һ�����к��� 0:ip  1:E164 2:����
	u32_ip  dwIp;								//IP ��ַ
	s8		achE164[MT_MAX_E164NUM_LEN+1];      //E164����
	s8		achMtAlias[MT_MAX_H323ALIAS_LEN+1]; //����
	u16		wCallRate;							//����
	
public:
	tagTMtcBoxCallCfg()
	{
		memset( this, 0, sizeof( tagTMtcBoxCallCfg ) );
	}
}TMtcBoxCallCfg,*PTMtcBoxCallCfg;

typedef struct tagTMTRSParam
{
    u16  m_wFirstTimeSpan;	 //��һ���ش�����(ms)
	u16  m_wSecondTimeSpan;  //�ڶ����ش�����(ms)
	u16  m_wThirdTimeSpan;   //�������ش�����(ms)
	u16  m_wRejectTimeSpan;  //���ڶ�����ʱ����(ms)
public:
	tagTMTRSParam()
	{
		m_wFirstTimeSpan = 40;
		m_wSecondTimeSpan = 2000;
		m_wThirdTimeSpan = 0;
		m_wRejectTimeSpan = 0;
	}
} TMTRSParam;

typedef struct tagTMtRecStartParam
{
public:
	
	EmSite			emSite;
	BOOL			bIsRecSecVideo;				//�Ƿ�¼˫��
	u8				m_byPublishMode;     //����ģʽ//�йط�����ʽ���� 0:������ 1:�������� 2:¼�����֮�󷢲�
	s8				achFileName[MT_MAX_REC_NAME+1];//¼����ļ���
public:
    tagTMtRecStartParam()
    {
        memset( this, 0, sizeof(tagTMtRecStartParam) );
    };
}TMtRecStartParam,*PTMtRecStartParam;

typedef struct tagTMtRecRegParam{
	u32_ip	  dwRecIp;
	u32_ip	  dwHostIp;
	s8        achDirName[MT_MAX_H323ALIAS_LEN + 1];
	public:
	tagTMtRecRegParam()
    {
        memset( this, 0, sizeof(tagTMtRecRegParam) );
    };
}TMtRecRegParam;

typedef struct tagTMtRecParam{
	u8					byState;//0:δ����,1:����,2:recording,3:pause
	TMtRecRegParam		tMtRecRegParam;
	TMtRecStartParam	tMtRecStartParam;
	public:
	tagTMtRecParam()
    {
        memset( this, 0, sizeof(tagTMtRecParam) );
    };
}TMtRecParam;

typedef struct tagTMtCnsParam{
	u32_ip	dwCnsIp;
	s8		achRoomName[MT_MAX_CNS_NAME_LEN+1];
	u16		wPos;
	u16		wPosCount;	
	BOOL    bIsDual;//�Ƿ���˫��Դ
	public:
		tagTMtCnsParam()
		{
			memset( this, 0, sizeof(tagTMtCnsParam) );
		};
}TMtCnsParam;

//MTStruct end.

typedef struct tagTLoginRet 
{
public:
	void SetRet( EmTpLoginUmsRet emRet )
	{
		m_emRet = (EmTpLoginUmsRet)htonl( emRet );
	}

	EmTpLoginUmsRet GetRet( )
	{
		return (EmTpLoginUmsRet)ntohl( m_emRet );
	}
public:
	EmTpLoginUmsRet m_emRet;
	u32		m_dwUserID;
	u32		m_dwErrorCode;	
	
	tagTLoginRet()
	{
		m_emRet = tp_LoginUms_sucess;
		m_dwUserID = 0;
		m_dwErrorCode = 0;
	}
}TLoginRet;


typedef struct tagTTPTransAddr
{
public:
	u32_ip	m_dwIP;		//������
	u16 m_wPort;	//������

public:
	tagTTPTransAddr()
		:m_dwIP(0)
		,m_wPort(0)
	{
	}

	u32 GetIP()	{ return m_dwIP; }
	u16 GetPort()	{ return m_wPort; }	

	
	void SetIP(u32 dwIP)
	{
		m_dwIP = dwIP;
	}
	void SetAddr(u32 dwIP, u16 wPort)
	{
		m_dwIP = dwIP;
		m_wPort = wPort;
	}
	void Clear()
	{
		m_wPort = 0;
		m_dwIP = 0;
	}
	tagTTPTransAddr& operator = (const tagTTPTransAddr& tRhs)
	{
		if (this == &tRhs)
		{
			return *this;
		}
		this->m_dwIP = tRhs.m_dwIP;
		this->m_wPort = tRhs.m_wPort;
		return *this;
	}

	BOOL operator == (const tagTTPTransAddr& tRhs)
	{
		if ( this->m_dwIP == tRhs.m_dwIP
			&&this->m_wPort == tRhs.m_wPort )
		{
			return TRUE;
		}
		return FALSE;
	}
}TTPTransAddr, *PTTPTransAddr;


typedef struct tagTTPName
{
	s8				m_abyAlias[TP_MAX_ALIAS_LEN + 1];
	tagTTPName()
	{
		Clear();
	}
	void Clear()
	{
		m_abyAlias[0]	= '\0';
	}
	
	void SetAlias(const s8* alias)
	{
		strncpy(m_abyAlias, alias, TP_MAX_ALIAS_LEN);
		m_abyAlias[TP_MAX_ALIAS_LEN] = '\0';
	}
	BOOL32 IsEmpty()
	{
		return '\0' == m_abyAlias[0];
	}
}TTPName;

//��������
typedef struct tagTTPAlias
{
	EmTpAliasType	m_byType;
	s8				m_abyAlias[TP_MAX_ALIAS_LEN + 1];
	tagTTPAlias()
	{
		Clear();
	}
	void Clear()
	{
		m_byType = tp_Alias_Unknow;
		m_abyAlias[0]	= '\0';
	}
	
	BOOL32 IsInValid()
	{
		return m_byType == tp_Alias_Unknow || strlen(m_abyAlias) == 0;
	}

	void SetAlias(EmTpAliasType type, const s8* alias)
	{
		if (NULL == alias)
		{
			return;
		}
		m_byType = type;
		strncpy(m_abyAlias, alias, TP_MAX_ALIAS_LEN);
		m_abyAlias[TP_MAX_ALIAS_LEN] = '\0';
	}

	void SetAlias(const s8* alias)
	{
		if (NULL == alias)
		{
			return;
		}
		m_byType = tp_Alias_h323;
		strncpy(m_abyAlias, alias, TP_MAX_ALIAS_LEN);
		m_abyAlias[TP_MAX_ALIAS_LEN] = '\0';
	}

	BOOL32 operator == (const tagTTPAlias& tRhs)
	{
		return (0 == strcmp(m_abyAlias, tRhs.m_abyAlias));
	}

	tagTTPAlias& operator = (const tagTTPAlias& tRhs)
	{
		if (this == &tRhs)
		{
			return *this;
		}
		m_byType = tRhs.m_byType;
		strncpy(m_abyAlias, tRhs.m_abyAlias, sizeof(m_abyAlias));
		return *this;
	}
}TTPAlias, *PTTPAlias;

typedef struct tagTTpEncryptKey
{
	u8 byLen;   //��Կ����
	u8 byKey[TP_MAXLEN_ENCRYPTKEY]; //��Կ����
public:
	tagTTpEncryptKey(){ memset( this ,0 ,sizeof( struct  tagTTpEncryptKey ) );}	
}TTpEncryptKey,*PTTpEncryptKey;


typedef struct tagTTPMediaTransAddr
{
	TTPTransAddr m_tRtpAddr;
	TTPTransAddr m_tRtcpAddr;	
	TTPTransAddr m_tBackRtcpAddr;
	tagTTPMediaTransAddr()
	{
	}
	void Clear()
	{
		m_tRtpAddr.Clear();
		m_tRtcpAddr.Clear();
		m_tBackRtcpAddr.Clear();
	}
	void SetIP(u32 dwIP)
	{
		m_tRtpAddr.SetIP(dwIP);
		m_tRtcpAddr.SetIP(dwIP);
		m_tBackRtcpAddr.SetIP(dwIP);
	}
}TTPMediaTransAddr;

typedef struct tagTTPVideoCap
{
	EmTpVideoFormat			m_emFormat;
	EmTpVideoResolution		m_emRes;
	u16		m_byMaxFrameRate;				//���֡��
	u16             m_wBitrate;

	TTpEncryptKey m_tEnc;

	u16     m_wStaticPayload;				
	u16     m_wDynamicPayload;

	EmTpVideoQualityLevel emTpVideoQualityLevel; //HP,BP

	tagTTPVideoCap()
	{
		m_emFormat = emTPVH264;
		m_emRes = emTPVHD1080p1920x1080;
		m_byMaxFrameRate = 50;

		m_wStaticPayload = MEDIA_TYPE_H264;
		m_wDynamicPayload = MEDIA_TYPE_H264;
		
		emTpVideoQualityLevel = emTPH264HP;
	}
	void Clear()
	{
		m_emFormat = emTPVH264;
		m_emRes = emTPVHD1080p1920x1080;
		m_byMaxFrameRate = 50;
		
		memset( &m_tEnc, 0, sizeof(m_tEnc) );

		m_wStaticPayload = MEDIA_TYPE_H264;
		m_wDynamicPayload = MEDIA_TYPE_H264;
		
		emTpVideoQualityLevel = emTPH264HP;
	}
}TTPVideoCap, *PTTPVideoCap;


typedef struct tagTTPAudCap
{
	EmTpAudioFormat		m_emFormat;
	u16     m_wStaticPayload;				
	u16     m_wDynamicPayload;

	u16             m_wBitrate;

	TTpEncryptKey m_tEnc;

	tagTTPAudCap()
	{
		m_emFormat = emTPAMpegAACLD;
	}

	void Clear()
	{
		m_emFormat = emTPAMpegAACLD;
		m_wStaticPayload = MEDIA_TYPE_AACLD;
		m_wDynamicPayload = MEDIA_TYPE_AACLD;
		
		memset( &m_tEnc, 0, sizeof(m_tEnc) );	
	}
}TTPAudCap, *PTTPAudCap;

//������Ƶ��ʽ
typedef struct tagTUmsVidFormat
{
	EmTpVideoFormat		  m_emFormat; //��Ƶ��ʽ
	EmTpVideoResolution	  m_emRes;    //��Ƶ�ֱ���
	u16					  m_wFrameRate;	//֡��
	u16					  m_wBitrate;       //��Ƶ����
	EmTpVideoQualityLevel m_emQualityLvl;  //H.264���ʼ���

	tagTUmsVidFormat()
	{
		Clear();
	}
	void Clear()
	{
		m_emFormat = emTPVH264;
		m_emRes = emTPVHD1080p1920x1080;
		m_wFrameRate = 60;
		m_wBitrate = 3072;
		m_emQualityLvl = emTPH264HP;
	}

	tagTUmsVidFormat& operator=(const tagTUmsVidFormat& tInfo)
	{
		if (this == &tInfo)
		{
			return *this;
		}
		
		m_emFormat = tInfo.m_emFormat;
		m_emQualityLvl = tInfo.m_emQualityLvl;
		m_emRes = tInfo.m_emRes;
		m_wBitrate = tInfo.m_wBitrate;
		m_wFrameRate = tInfo.m_wFrameRate;
		
		return *this;
	}
	BOOL32 IsValid() const	{ return emTPVResEnd != m_emRes; }
}TUmsVidFormat;

//�ش��趨
typedef struct tagTUmsRSParam
{
    u16  m_wFirstTimeSpan;	 //��һ���ش�����(ms)
	u16  m_wSecondTimeSpan;  //�ڶ����ش�����(ms)
	u16  m_wThirdTimeSpan;   //�������ش�����(ms)
	u16  m_wRejectTimeSpan;  //���ڶ�����ʱ����(ms)

	tagTUmsRSParam()
	{
		m_wFirstTimeSpan = 40;
		m_wSecondTimeSpan = 80;
		m_wThirdTimeSpan = 120;
		m_wRejectTimeSpan = 2000;
	}
}TUmsRSParam;


//ConfEp : 
typedef struct tagTEpAddr
{
	TTPAlias	m_tAlias;//����
	TTPAlias	m_tE164;//E164
	u32_ip		m_dwIP;//IP
	u16			m_wEpID;
	tagTEpAddr()
	{
		m_tAlias.Clear();
		m_tE164.Clear();
		m_dwIP = 0;
		m_wEpID = TP_INVALID_INDEX;
	}
}TEpAddr, *PTEpAddr;

//�����б�
typedef struct tagTAuxMixList
{
	u16 m_wSpeakerIndex;					//�������������
	u16	m_awList[TP_CONF_MAX_AUDMIXNUM];	//����ID
	
	BOOL32 m_bAudMixOn;                     //���ۿ��أ�Ĭ�Ϲر�
	tagTAuxMixList()
	{
		Clear();
	}
	
	BOOL32 operator == (const tagTAuxMixList& tRhs)
	{
		if (m_wSpeakerIndex != tRhs.m_wSpeakerIndex)
		{
			return FALSE;
		}
		for (u16 wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; ++wIndex)
		{
			if (m_awList[wIndex] != tRhs.m_awList[wIndex])
			{
				return FALSE;
			}
		}
		return TRUE;
	}

	void Clear()
	{
		m_wSpeakerIndex = TP_INVALID_INDEX;
		for (u16 wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; ++wIndex)
		{
			m_awList[wIndex] = TP_INVALID_INDEX;
		}
		m_bAudMixOn = FALSE;
	}
	BOOL32 SetSpeakerIndex(u16 wSpeakerIndex)
	{
		if (wSpeakerIndex >= TP_CONF_MAX_AUDMIXNUM)
		{
			return FALSE;
		}
		
		//���������ã�����ô�����
		if (TP_VALID_HANDLE(m_awList[wSpeakerIndex]))
		{
			m_wSpeakerIndex = wSpeakerIndex;
			return TRUE;
		}
		
		//���û�з����ˣ���Ĭ��ȡ��һ��
		for (u16 wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; ++wIndex)
		{
			if (TP_VALID_HANDLE(m_awList[wIndex]))
			{
				m_wSpeakerIndex = wIndex;
				return TRUE;
			}
		}
		return FALSE;
	}

	BOOL32 AddMixID(u16 wEpID)
	{		
		u16 wIndex = 0;
		for (wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; ++wIndex)
		{
			if (m_awList[wIndex] == wEpID)
			{
				return FALSE;
			}
		}
		for (wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; ++wIndex)
		{
			if (!TP_VALID_HANDLE(m_awList[wIndex]))
			{
				m_awList[wIndex] = wEpID;
				return TRUE;
			}
		}
		return FALSE;
	}

	u16 GetMixNum() const
	{
		u16 wMixNum = 0;
		for (u16 wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; ++wIndex)
		{
			if (!TP_VALID_HANDLE(m_awList[wIndex]))
			{
				continue;
			}
			wMixNum++;
		}
		return wMixNum;
	}
	
	BOOL32 IsValid() const
	{
		if (GetMixNum() < 1)
		{
			return FALSE;
		}
		if (m_wSpeakerIndex >= TP_CONF_MAX_AUDMIXNUM)
		{
			return FALSE;
		}

		if (!TP_VALID_HANDLE(m_awList[m_wSpeakerIndex]))
		{
			return FALSE;
		}
		return TRUE;
	}

	u16 FindIndexByEp(u16 wEpID) const
	{
		for (u16 wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; ++wIndex)
		{
			if (m_awList[wIndex] == wEpID)
			{
				return wIndex;
			}
		}
		return TP_INVALID_INDEX;
	}
	u16 GetSpeakerEpID( u16 wSpeaker = TP_INVALID_INDEX ) const
	{
		if (TP_VALID_HANDLE(m_wSpeakerIndex) && TP_VALID_HANDLE(m_awList[m_wSpeakerIndex]))
		{
			return m_awList[m_wSpeakerIndex];
		}
		u16 wIndex = 0;
		//�Ȳ��ҵ�ǰ�������Ƿ���������
		for ( wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; ++wIndex)
		{
			if (m_awList[wIndex] == wSpeaker)
			{
				return wSpeaker;
			}
		}

		for ( wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; ++wIndex)
		{
			if (TP_VALID_HANDLE(wIndex) && TP_VALID_HANDLE(m_awList[wIndex]))
			{
				return m_awList[wIndex];
			}
		}
		
		return TP_INVALID_INDEX;
	}
	BOOL32 SetSpeakerEpID(u16 wEpID) 
	{
		m_wSpeakerIndex = TP_INVALID_INDEX;
		u16 wSpeakerIndex = FindIndexByEp(wEpID);
		if (!TP_VALID_HANDLE(wSpeakerIndex))
		{
			for (u16 wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; ++wIndex)
			{
				if (TP_VALID_HANDLE(m_awList[wIndex]))
				{
					wSpeakerIndex = wIndex;
					break;
				}
			}
		}
		if (!TP_VALID_HANDLE(wSpeakerIndex))
		{
			return FALSE;
		}
		
		return SetSpeakerIndex(wSpeakerIndex);
	}
}TAuxMixList, *PTAuxMixList;

//��������б�
typedef struct tagTConfAuxMixInfo
{
	u16			m_wConfID;
	BOOL32		m_bStart;
	TAuxMixList	m_atAuxMixList;
	tagTConfAuxMixInfo()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_bStart = FALSE;
	}
}TConfAuxMixInfo;

typedef struct tagTTPPollInfo
{
	BOOL bIsPoll;
	u16  wPollExpire;
	
	tagTTPPollInfo()
	{
		memset( this, 0, sizeof(struct tagTTPPollInfo) );
	}
}TTPPollInfo;

//����������Ϣ
typedef struct tagTTPConfBaseInfo
{
	s8	 achConfId[TP_MAX_CONF_ID_LEN + 1 ];			// ����ID
	s8	 achConfName[TP_MAX_NAME_LEN + 1 ];		// ������
	s8	 achConfNumber[ TP_MAX_CONF_E164_LEN + 1 ];	    // �������
	s8	 achConfPwd[ TP_MAXLEN_PASSWORD + 1 ];			// ��������
	BOOL32 bNeedPassword;                         //�Ƿ���Ҫ����
	u16  wConfDuration;							// �������ʱ��		
	EmTpVideoFormat   emTpVideoFormat;							// ������Ƶ��ʽ(VIDEO_H261��)
	EmTpAudioFormat   emTpAudioFormat;							// ������Ƶ��ʽ(AUDIO_MP3��)
	EmTpVideoResolution  emTpResolution;							// ������Ƶ�ֱ���(VIDEO_CIF��)
	BOOL32  bIsAutoVMP;								// �Ƿ��Զ�����ϳ�
	BOOL32  bIsMix;	    							// �Ƿ����
	u8				  bySecVideoFormat;				// ˫����ʽ
	EmTpVideoResolution emTpSecVidRes;					// ˫���ֱ���
	u8				  bySecVidFps;					// ˫��֡��
	//Add by tanxiaodong 2013-06-21.
	EmTpVideoQualityLevel emPriVideoQualityLevel;  // ����profile
	EmTpVideoQualityLevel emDualVideoQualityLevel;  // ˫��profile
    u8 byPriVidFps;									// ����֡��
	//End to add.
	u16			 wCallRate;			        // ��������(kbps)
	u16			 wDualCallRate;			    // ˫������(kbps)
	TTPPollInfo  tPollInfo;
	TConfAuxMixInfo tConfAudMixInfo;
	
public:
	tagTTPConfBaseInfo(){ memset( this ,0 ,sizeof( struct tagTTPConfBaseInfo ) );	}
	void Clear(){ memset( this ,0 ,sizeof( struct tagTTPConfBaseInfo ) );};
}TTPConfBaseInfo ,*PTTPConfBaseInfo;


//���������Ϣ
typedef struct tagTUmsConfBase
{
	s8  m_achConfName[TP_MAX_ALIAS_LEN+1];	//��������
	s8  m_achConfE164[TP_MAX_ALIAS_LEN+1];	//����e164
	u16	m_wConfBitRate;						//��������(HP����)
	u16	m_wBpConfBitRate;					//��������(BP����)
	u16 m_wHpDualBitRate;					//˫������(HP����)
	u16 m_wBpDualBitRate;					//˫������(BP����)
	u32	m_dwPersistenceTime;				//�������ʱ�䣬��λΪ�룬Ϊ0��ʾ�ֶ�����
	time_t m_tStartTime;					//���鿪ʼʱ��, Ϊ0��ʾ�ֶ���ʼ
	
// 	EmTpVideoFormat		m_emTpVideoFormat;							// ������Ƶ��ʽ(VIDEO_H261��)
// 	EmTpVideoResolution m_emTpResolution;						// ������Ƶ�ֱ���(VIDEO_CIF��)
	EmTpAudioFormat		m_emTpAudioFormat;							// ��������Ƶ��ʽ(AUDIO_MP3��)
	EmTpAudioFormat		m_emSecAudFormat;                        // ��ѡ�������Ƶ��ʽ

	TUmsRSParam m_tRsParam;					//�ش�����
	
	EmTPEncryptType	m_byEncryptModel;		//����ģʽ: none, aes, des
	
	u16	m_wDefaultChairMan;					//Ĭ����ϯ	

	u16 m_wMainNum;  //����ʽ����
	TUmsVidFormat m_atTpMainVideoRes[TP_CONF_MAX_MAIN_VIDEO_RES_NUM];  //��������Ƶ�ֱ���

	u16 m_wMinorNum; //˫����ʽ����
	TUmsVidFormat m_atTpMinorVideoRes[TP_CONF_MAX_MINOR_VIDEO_RES_NUM]; //���鸨��Ƶ�ֱ���

	tagTUmsConfBase()
	{
		Clear();
	}
	
	tagTUmsConfBase& operator = (const tagTUmsConfBase& tRhs)
	{
		if(this == &tRhs)
			return *this;
		
		memcpy(m_achConfName, tRhs.m_achConfName, TP_MAX_ALIAS_LEN+1);
		memcpy(m_achConfE164, tRhs.m_achConfE164, TP_MAX_ALIAS_LEN+1);

		m_wConfBitRate = tRhs.m_wConfBitRate;
		m_wBpConfBitRate = tRhs.m_wBpConfBitRate;
		m_wHpDualBitRate = tRhs.m_wHpDualBitRate;
		m_wBpDualBitRate = tRhs.m_wBpDualBitRate;
		m_dwPersistenceTime = tRhs.m_dwPersistenceTime;
		m_tStartTime = tRhs.m_tStartTime;

// 		m_emTpVideoFormat = tRhs.m_emTpVideoFormat;
// 		m_emTpResolution = tRhs.m_emTpResolution;
		m_emTpAudioFormat = tRhs.m_emTpAudioFormat;

		memcpy(&m_tRsParam, &tRhs.m_tRsParam, sizeof(m_tRsParam));

		m_byEncryptModel = tRhs.m_byEncryptModel;
		m_wDefaultChairMan = tRhs.m_wDefaultChairMan;	

		m_wMainNum = tRhs.m_wMainNum;
		m_wMinorNum = tRhs.m_wMinorNum;
		memcpy(m_atTpMainVideoRes, tRhs.m_atTpMainVideoRes, sizeof(m_atTpMainVideoRes));
		memcpy(m_atTpMinorVideoRes, tRhs.m_atTpMinorVideoRes, sizeof(m_atTpMinorVideoRes));

		return *this;
	}
	
	void Clear()
	{
		m_wConfBitRate = CONF_HP_BITRATE;		//Ĭ��ֵȫ���ĳ�2M
		m_wBpConfBitRate = CONF_HP_BITRATE;
		m_wHpDualBitRate = CONF_HP_BITRATE;
		m_wBpDualBitRate = CONF_HP_BITRATE;
		m_dwPersistenceTime = 0;
		m_tStartTime = 0;
		m_byEncryptModel = emTPEncryptTypeNone;

// 		m_emTpVideoFormat = emTPVH264;
// 		m_emTpResolution = emTPVHD1080p1920x1080;

		m_emTpAudioFormat = emTPAMpegAACLD;
		m_emSecAudFormat = emTPAEnd;

		m_wDefaultChairMan = 0;
		
		m_achConfName[0] = '\0';
		m_achConfE164[0] = '\0';
		m_wMainNum = 1;
		m_wMinorNum = 1;

		u16 wIndex = 0;
		for (wIndex = 0; wIndex < TP_CONF_MAX_MAIN_VIDEO_RES_NUM; ++wIndex)
		{
			m_atTpMainVideoRes[wIndex].Clear();
		}
		for (wIndex = 0; wIndex < TP_CONF_MAX_MINOR_VIDEO_RES_NUM; ++wIndex)
		{
			m_atTpMinorVideoRes[wIndex].Clear();
		}
	}
	
}TUmsConfBase;


//�ϼ�������Ϣ
typedef struct tagTChairConfInfo
{
	u16			m_wConfID;
	time_t		m_tBeginTime;		//���鿪ʼʱ��
	TTPAlias	m_tConfName;		//��������
	TTPAlias	m_tChairName;		//��ϯ����
	tagTChairConfInfo()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_tBeginTime = 0;
	}
	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_tBeginTime = 0;
		m_tConfName.Clear();
		m_tChairName.Clear();
	}
}TChairConfInfo;


//�᳡�б�
typedef struct tagTEpAddrList
{
	u16	m_wNum;									
	TEpAddr	m_tCnsList[TP_CONF_MAX_EPNUM];		//���˵�
	tagTEpAddrList()
	{
		m_wNum = 0;
	}

	BOOL32 IsRepeat(EmTpAliasType emType, s8* pszEpAlias)
	{
		if (NULL == pszEpAlias)
		{
			return FALSE;
		}
		if (0 == strlen(pszEpAlias))
		{
			return FALSE;
		}
		if (tp_Alias_h323 == emType)
		{
 		for (u16 wIndex = 0; wIndex < m_wNum; ++wIndex)
 		{
			if (emType == m_tCnsList[wIndex].m_tAlias.m_byType 
					&& 0 == strcmp(pszEpAlias, m_tCnsList[wIndex].m_tAlias.m_abyAlias) )
			{
				return TRUE;
				}				
			}
		}
		else if (tp_Alias_e164 == emType)
		{
			for (u16 wIndex = 0; wIndex < m_wNum; ++wIndex)
			{
				if (emType == m_tCnsList[wIndex].m_tE164.m_byType 
					&& 0 == strcmp(pszEpAlias, m_tCnsList[wIndex].m_tE164.m_abyAlias) )
				{
					return TRUE;
				}				
 		}
		}
		else
		{
			return FALSE;
		}
		return FALSE;
	}
	EmConfAddEpRet Add(s8*pszEp323Alias, s8* pszEpE164Alias)
	{//����ӵĻ᳡����323��������164�ű���
		if (NULL == pszEp323Alias && NULL == pszEpE164Alias)
		{
			return TP_ConfAddEpRet_ParamError;
		}
		if (m_wNum >= TP_CONF_MAX_EPNUM)
		{
			return TP_ConfAddEpRet_MaxNum;
		}
		if (IsRepeat(tp_Alias_h323, pszEp323Alias) || IsRepeat(tp_Alias_e164, pszEpE164Alias))
		{
			return TP_ConfAddEpRet_AliasReapeat;
		}
		m_tCnsList[m_wNum].m_wEpID = m_wNum;
		m_tCnsList[m_wNum].m_tAlias.SetAlias(tp_Alias_h323, pszEp323Alias);
		m_tCnsList[m_wNum].m_tE164.SetAlias(tp_Alias_e164, pszEpE164Alias);
		++m_wNum;
		return TP_ConfAddEpRet_Success;
	}
	EmConfAddEpRet Add(EmTpAliasType emType, s8* pszEpAlias)
	{
		if (pszEpAlias ==NULL)
		{
			return TP_ConfAddEpRet_ParamError;
		}
		if (m_wNum >= TP_CONF_MAX_EPNUM)
		{
			return TP_ConfAddEpRet_MaxNum;
		}
		
		if (emType != tp_Alias_h323 && emType != tp_Alias_e164)
		{
			return TP_ConfAddEpRet_ParamError;
		}
		if (IsRepeat(emType, pszEpAlias))
		{
			return TP_ConfAddEpRet_AliasReapeat;
		}

		m_tCnsList[m_wNum].m_wEpID = m_wNum;
		if (emType == tp_Alias_h323)
		{
		m_tCnsList[m_wNum].m_tAlias.SetAlias(emType, pszEpAlias);
		}
		else
		{
			m_tCnsList[m_wNum].m_tE164.SetAlias(emType, pszEpAlias);
		}
		++m_wNum;

		return TP_ConfAddEpRet_Success;
	}
	
	TEpAddr* FindEp(TTPAlias& tAlias)
	{
		if (tp_Alias_h323 == tAlias.m_byType)
	{
		for (u16 wIndex = 0; wIndex < m_wNum; ++wIndex)
		{
			if (tAlias.m_byType == m_tCnsList[wIndex].m_tAlias.m_byType 
				&& 0 == strcmp(tAlias.m_abyAlias, m_tCnsList[wIndex].m_tAlias.m_abyAlias) )
			{
				return &m_tCnsList[wIndex];
			}
			}
		}
		else if (tp_Alias_e164 == tAlias.m_byType)
		{
			for (u16 wIndex = 0; wIndex < m_wNum; ++wIndex)
			{
				if (tAlias.m_byType == m_tCnsList[wIndex].m_tE164.m_byType 
					&& 0 == strcmp(tAlias.m_abyAlias, m_tCnsList[wIndex].m_tE164.m_abyAlias) )
				{
					return &m_tCnsList[wIndex];
				}
			}
		}
		else
		{
			return NULL;
		}
		return NULL;
	}
}TEpAddrList, *PTEpAddrList;

//��ѯ�б�
typedef struct tagTConfTurnList
{
	u16 m_wInterval;						//��ѯ�������λ��
	u16	m_wNum;								//������ѯ����
	u16	m_awList[TP_CONF_MAX_TURNNUM];
	
	BOOL32 m_bPollOn;                      //��ѯ����״̬��Ĭ�Ͽ���
	tagTConfTurnList()
	{
		Clear();
	}
	void SetInterval(u16 interval)	
	{
		if (interval < TP_CONF_TURN_MIN_INTERVAL)
		{
			interval = TP_CONF_TURN_MIN_INTERVAL;
		}
		m_wInterval = interval; 
	}
	void Clear()
	{
		m_wInterval = 20;
		m_wNum = 0;
		m_bPollOn = TRUE;
		for (u16 wIndex = 0; wIndex < TP_CONF_MAX_TURNNUM; wIndex++)
		{
			m_awList[wIndex] = TP_INVALID_INDEX;
		}
	}
}TConfTurnList, *PTConfTurnList;


//ConfTemplate : ����ģ��
typedef struct tagTTPConfTemplate : public TUmsConfBase
{
	u16				m_wID;					//ģ��ID
	u32				m_dwTimeID;				//ģ���ʱ��ָ��

	TEpAddrList		m_atEpList;
	TAuxMixList		m_atAuxMixList;
	TConfTurnList	m_tTurnList;

	tagTTPConfTemplate()
	{
		m_wID = TP_INVALID_INDEX;
		m_dwTimeID = 0;
	}

	tagTTPConfTemplate& operator = (const tagTTPConfTemplate& tRhs)
	{
		if(this == &tRhs)
            return *this;
        
		memcpy(&m_atEpList, &tRhs.m_atEpList, sizeof(m_atEpList));
		memcpy(&m_atAuxMixList, &tRhs.m_atAuxMixList, sizeof(m_atAuxMixList));
		memcpy(&m_tTurnList, &tRhs.m_tTurnList, sizeof(m_tTurnList));
         
		TUmsConfBase::operator = (tRhs);
		//static_cast<TTPConfBaseInfo&>(*this) = tRhs;
		return *this;
	}

	BOOL32 Invalid()	{ return !TP_VALID_HANDLE(m_wID); }
	BOOL32 operator == (const tagTTPConfTemplate& tRhs)
	{	
		return m_wID == tRhs.m_wID;
	}

	void Clear()
	{
		m_dwTimeID = 0;
		memset(&m_atEpList, 0, sizeof(m_atEpList));
		m_atAuxMixList.Clear();
		m_tTurnList.Clear();
		TUmsConfBase::Clear();
	}

}TTPConfTemplate;


//����ģ��������
typedef struct tagTOprConfTmpResult
{
	u16					m_wID;
	EmTpConfTemplateRet m_emReason;
	tagTOprConfTmpResult()
	{
		m_emReason = TP_ConfTemplate_UnKonw;
	}
}TOprConfTmpResult, *PTOprConfTmpResult;


//ɾ������ģ��
typedef struct tagTDelRefreshConfTemplate
{
	u16 m_wRefreshNum;
	u16	m_awTmpList[TP_REFRESH_LIST_THREE];
	tagTDelRefreshConfTemplate()
	{
		m_wRefreshNum = 0;
	}
}TDelRefreshConfTemplate;

//ConfEpID : 
typedef struct tagTConfEpID
{
	u16	m_wConfID;
	u16	m_wEpID;
	tagTConfEpID()
	{
		Clear();
	}
	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_wEpID = TP_INVALID_INDEX;
	}
}TConfEpID;


typedef struct tagTConfEpIDInfo
{
	u16	m_wConfID;
	u16	m_wEpID;
	TTPAlias	m_tAlias;
	tagTConfEpIDInfo()
	{
		Clear();
	}
	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_wEpID = TP_INVALID_INDEX;
	}
}TConfEpIDInfo;

//�����к���EP : 
typedef struct tagTConfCallEpAddr
{
	u16	m_wConfID;
	TTPAlias	m_tAlias;
	tagTConfCallEpAddr()
	{
		m_wConfID = TP_INVALID_INDEX;
	}
}TConfCallEpAddr;


//RoomInfo : CNS
typedef struct tagTCnsInfo
{
	u16	m_wEpID;							//�᳡ID
	u16	m_wParentEpID;						//���᳡ID
	u16 m_wChildEpID;
	u16 m_wBrotherEpID;

	EmTPEndpointType m_emEpType;			//�������
	TTPAlias m_tCalledAddr;

	BOOL32	m_bOnline;			//����״̬
	EmCnsCallReason m_emCallReason; 
	s8	m_achRoomName[TP_MAX_ALIAS_LEN+1];	//�᳡��
	u16	m_wLevel;							//�᳡�ȼ�	����

	BOOL32 m_bMute;
	BOOL32 m_bQuiet;
	
	BOOL32 m_bIsSpeaker;					//�Ƿ����� ����
	BOOL32 m_bIsChair;						//�Ƿ���ϯ   ����

	u16 m_wSpeakerNum;						//�᳡����	
	s8	m_achSpeakerName[TP_MAX_STREAMNUM][TP_MAX_ALIAS_LEN+1];
	
	tagTCnsInfo()
	{	
		Clear();
	}

	void Clear()
	{
		m_wEpID = TP_INVALID_INDEX;
		m_wParentEpID = TP_INVALID_INDEX;
		m_wChildEpID = TP_INVALID_INDEX;
		m_wBrotherEpID = TP_INVALID_INDEX;
		m_tCalledAddr.Clear();
		m_emEpType = emTPEndpointTypeUMS;

		m_bOnline = FALSE;
		m_achRoomName[0] = '\0';
		m_wLevel = TP_INVALID_INDEX;
		
		m_bMute = FALSE;
		m_bQuiet = FALSE;
		m_wSpeakerNum = TP_INVALID_INDEX;
		m_emCallReason = EmCnsCallReason_Local;
	}

	BOOL32 operator == (const tagTCnsInfo& tRhs)
	{
		return this->m_wEpID == tRhs.m_wEpID;
	}
}TCnsInfo, *PTCnsInfo;

//������Ϣ
typedef struct tagTTPConfInfo : public TUmsConfBase
{
	u16	m_wConfID;
	u16	m_wSpeaker;		//���鷢����ID
	u16	m_wDual;		//����˫��ID
	tagTTPConfInfo()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_wSpeaker = TP_INVALID_INDEX;
		m_wDual = TP_INVALID_INDEX;
	}
	
	void SetBaseInfo(TUmsConfBase* ptBase)
	{
		*(TUmsConfBase*)this = *ptBase;
	}

	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_wSpeaker = TP_INVALID_INDEX;
		m_wDual = TP_INVALID_INDEX;
		TUmsConfBase::Clear();
	}

}TTPConfInfo, *PTTPConfInfo;

//�����б�����
typedef struct tagTAddConfList
{
	u16 m_wRefreshNum;
	TTPConfInfo	m_atTmpList[TP_REFRESH_LIST_THREE];
	tagTAddConfList()
	{
		m_wRefreshNum = 0;
	}
}TAddConfList;

//�����б�ɾ��
typedef struct tagTDelConfList
{
	u16 m_wRefreshNum;
	u16	m_awConfIDList[TP_REFRESH_LIST_THREE];
	tagTDelConfList()
	{
		m_wRefreshNum = 0;
	}
}TDelConfList;

//�����ٿ����
typedef struct tagTStartConfResult
{
	EmTpStartConfRet m_emReason;
	u16	m_wConfTemplateID;
	u16	m_wConfID;
	tagTStartConfResult()
	{
		m_emReason = TP_StartConf_UnKonw;
		m_wConfTemplateID = TP_INVALID_INDEX;
		m_wConfID = TP_INVALID_INDEX;
	}
}TStartConfResult, *PTStartConfResult;


//����᳡�б�
typedef struct tagTConfCnsInfo
{
	EmTpOprType	m_emOpr;	
	BOOL32		m_bLastPack;
	u16			m_wConfID;

	u16			m_wNum;
	TCnsInfo	m_tConfCnsList[TP_REFRESH_LIST_THREE];
	tagTConfCnsInfo()
	{
		m_emOpr = tp_OprType_Add;
		m_wConfID = TP_INVALID_INDEX;
		m_wNum = 0;
		m_bLastPack = TRUE;
	}
}TConfCnsInfo;

//������ѯ�б�
typedef struct tagTConfTurnInfo
{
	u16				m_wConfID;
	TConfTurnList	m_atTurnList;
	tagTConfTurnInfo()
	{
		m_wConfID = TP_INVALID_INDEX;
	}
}TConfTurnInfo;


//ָ�������˽��
typedef struct tagTApplaySpeakRet
{
	TConfEpID	m_tID;
	EmTpApplySpeakRet	m_emReason;
	tagTApplaySpeakRet()
	{
		m_emReason = TP_ApplySpeak_UnKonw;
	}
}TApplaySpeakRet;

typedef struct tagTUmsConfStatus
{
	BOOL32	m_bIsStartAudMix;
	tagTUmsConfStatus()
	{
		m_bIsStartAudMix = FALSE;
	}
}TUmsConfStatus;

typedef struct tagTTPUmsReasonInd
{
	u16	m_wConfID;
	u16 m_wEpID;
	u32 m_dwReason;//tperror.h�е�ԭ��
	
	u32 m_dwReserve1;//����
	u32 m_dwReserve2;
	u32 m_dwReserve3;
	
	tagTTPUmsReasonInd()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_wEpID = TP_INVALID_INDEX;

		m_dwReason = 0;

		m_dwReserve1 = 0;
		m_dwReserve2 = 0;
		m_dwReserve3 = 0;
	}
}TTPUmsReasonInd;

//============================����ΪCNSʹ�ýṹ��===================//
//��Ƶ�������
typedef struct tagTTPMtVideoEncodeParameter    
{
	EmTpVideoFormat      emVideoFormat; 
	u16                byMaxKeyFrameInterval; // I֡�����P֡��Ŀ
    u8                 byMaxQuant;  //�����������
	u8                 byMinQuant;  //��С��������
    BOOL               bUseFixedFrame; //�Ƿ�ʹ�ù̶�֡��
	u8	               byFrameRate;  //֡��
	BOOL               bFramePerSecond;  //֡�ʵ�λ TRUE�� ֡/��  FALSE����/֡ 
	
    EmTpEncodeMode emEncodeMode;     //���뷽ʽ
	EmTpVideoResolution  emVideoResolution;
	u32                wChanMaxBitrate; // ��λ Kbps
	//��������ֻ����windowsƽ̨������
	//��Ӳɼ�ͼ����
	u16	m_wWidth; //��Ƶ����ͼ���� ��Windows��Ч(default:640)
	u16	m_wHeight;//��Ƶ����ͼ��߶� ��Windows��Ч(default:480)
	EmTpMediaType   emCapType;    //�ɼ�����   (default:emMediaAV)
	EmTpPCCapFormat emPCCapFormat;//��Ƶ����֡��ʽ ��Windows��Ч(default:emCapPCFrameBMP)
	
	u32 m_dwAvgQpI;					/* ƽ��qp Ĭ��0- 28*/
	u32 m_dwAvgQpP;
	u8  m_byLoopFilterMask;		    /*������·�˲� Ĭ��Ϊ0 ������*/
	u32  m_dwProfile;				// 0 BaseLine | 1 HighProfile
	//׷�ӱ���������
	u32  m_dwCabacDisable;			/*�Ƿ���CABAC*/
	u32  m_dwSilceMbCont;           /*slice�ĺ��������������Ϊ��slice*/
	u32  m_dwRateControlAlg;        /*���ʿ����㷨������m_byRcMode == 1 ʱ��Ч*/
public:
	tagTTPMtVideoEncodeParameter(){ memset( this ,0 ,sizeof( struct  tagTTPMtVideoEncodeParameter ) );}	
}TTPMtVideoEncodeParameter ,*PTTPMtVideoEncodeParameter;


typedef struct tagTTpCodecComponent
{
	u16 wPos;
	EmTpCodecComponent emCope;
	tagTTpCodecComponent()
	{
		wPos = 0;
		emCope = emTPCodecComponentEnd;
	};

}TTpCodecComponent;

typedef struct tagTTPCnMediaTransPort
{
	//	NODEHANDLE	m_handle;
	TTPTransAddr m_tRtpPort;
	TTPTransAddr m_tRtcpPort;	
	TTPTransAddr m_tBackRtcpPort;
	
	void clear()
	{
		memset(this, 0, sizeof(tagTTPCnMediaTransPort));
	}
	tagTTPCnMediaTransPort()
	{
		clear();
	}
	tagTTPCnMediaTransPort& operator = (const tagTTPCnMediaTransPort& tRhs)
	{
		if (this == &tRhs)
		{
			return *this;
		}
		//	this->m_handle = tRhs.m_handle;
		this->m_tRtpPort = tRhs.m_tRtpPort;
		this->m_tRtcpPort = tRhs.m_tRtcpPort;
		this->m_tBackRtcpPort = tRhs.m_tBackRtcpPort;
		return *this;
	}
}TTPCnMediaTransPort;

typedef struct tagTMtMPAddr
{
	u16 wPos;
	EmTpCodecComponent emCope;
	TTPCnMediaTransPort m_tAddr;
	tagTMtMPAddr()
	{
		wPos = 0;
		emCope = emTPCodecComponentEnd;
	};
}TMtMPAddr;

typedef struct tagTMtMPParam
{
	u16 m_wMpType;	//�˱���������    1�������ˣ�2��ȫ���������4��˫����8��Ƶ 0x0000Ϊ��Ч  ע��1 2 4ָ��Ƶ
	TTPCnMediaTransPort m_tAddr;
	tagTMtMPParam()
	{
		m_wMpType = 0;
	};
}TMtMPParam;
typedef struct tagTMtTPEpParam
{
	u16					wLen;					//��ǰ�ṹ�峤�ȣ������汾����ʹ�ã�
	TMtMPParam m_tSndPrimarAddr;		//��һ·����
	TMtMPParam m_tRcvPrimarAddr;		//��һ·����
	
	TMtMPParam m_tSndSecondAddr;		//�ڶ�·����
	TMtMPParam m_tRcvSecondAddr;		//�ڶ�·����
	
	TMtMPParam m_tSndAudioAddr;		//��Ƶ����
	TMtMPParam m_tRcvAudioAddr;		//��Ƶ����

	TMtMPParam m_tRcvPrimarLeftAddr;
	TMtMPParam m_tRcvPrimarRightAddr;
	
	u16	m_wPosCount; //λ������
	u16 m_wPos;		//�ն��ڻ᳡�е�����λ��	1��2��3��4��5
	s8  achRoomName[TP_MAX_ALIAS_LEN + 1];	//�ն����ڻ᳡������
	EmTPMtModel m_emTPMtModel;                //�ն��ͺ�
	tagTMtTPEpParam()
	{
		wLen = 0;
		m_wPos = 0;
		m_wPosCount = 0;
		m_emTPMtModel = emTPUnknownMtModel;
		memset( this->achRoomName, 0, sizeof(this->achRoomName) );
	};
}TMtTPEpParam;


typedef struct tagTMtVDecParam
{
	EmTpCodecComponent		emComp;
	TTPCnMediaTransPort		tAddr;
	EmTpLostPackageRestore	emLost;
	EmTpVideoFormat			emFormat;
	EmTpVideoResolution		emRes;
	u8						byPayload;
	TTpEncryptKey				tEncryptKey;
	u16                     wPos;

	tagTMtVDecParam()
	{
		memset( this, 0, sizeof(tagTMtVDecParam) );
	};
}TMtVDecParam;

typedef struct tagTMtVEncParam
{
	EmTpCodecComponent	emComp;
	TTPCnMediaTransPort tAddr;
	
	TTPMtVideoEncodeParameter tVideoEncodeParameter;
	u8					byPayload;
	TTpEncryptKey			tEncryptKey;
	u16                 wPos;
	tagTMtVEncParam()
	{
		memset( this, 0, sizeof(tagTMtVEncParam) );
	};
}TMtVEncParam;

typedef struct tagTCnVideoParam
{
	EmTpCodecComponent	emComp;
	TTPCnMediaTransPort tAddr;
	
	EmTpVideoFormat			emFormat;
	EmTpVideoResolution		emRes;
	u8					byPayload;
	u32                wChanMaxBitrate; // ��λ Kbps
	u8				    byFrameRate;
	TTpEncryptKey			tEncryptKey;
	u32                 m_dwProfile;
	tagTCnVideoParam()
	{
		memset( this, 0, sizeof(tagTCnVideoParam) );
	};
}TCnVideoParam;

typedef struct tagTEpId
{
	u8 byCnNo;
	u8 byEpNo;
	
public:
	tagTEpId(){ memset( this ,0 ,sizeof( struct tagTEpId ) );	}
	
}TEpId ,*PTEpId;

//============================����ΪCNSʹ�ýṹ��===================//

typedef struct tagTTPRegName
{
	EmTPAddrType emPAAddrType;
	s8     achUserName[TP_MAX_H323ALIAS_LEN+1];     //ע����
	s8     achPassword[TP_MAX_PASSWORD_LEN+1]; //ע������
	s8     achDisplayName[TP_MAX_H323ALIAS_LEN+1];  //��ʾ����
	tagTTPRegName()
	{
		memset( this, 0, sizeof(tagTTPRegName) );
	}
}TTPRegName,*PTTPRegName;

typedef struct tagTTPRegNameRepeatInfo
{
	u32 dwsize;
	TTPRegName atTPRegName[2];
	tagTTPRegNameRepeatInfo()
	{
		memset( this, 0, sizeof(tagTTPRegNameRepeatInfo) );
	}
}TTPRegNameRepeatInfo;

//SIP Register����
typedef struct tagTTPSipRegistrarCfg
{
	BOOL   bUsed;   //�Ƿ�ע��
	u32_ip dwRegIP; //ע�������IP��ַ
	u16    wRegPort;//ע��������˿�
	s8     achRegDomain[TP_MAX_PROXYSERVER_NAME_LEN];
	u16    wExpire;
	BOOL   bRegistered;//ע��������Ƿ�ɹ�
	
	TTPRegName atTPRegName[TP_REGNAME_SIZE];//ע�����֧�ֶ��
	s32		   nTPRegNameSize;//ʵ�ʱ�������
	s8     achHostDomain[TP_MAX_PROXYSERVER_NAME_LEN];//��������
	u32_ip dwHostIP;
	u16    wHostPort;      
	EmTPEndpointType m_emEndType;  
	u32_ip		m_locolIP;                            //����IP                   
	s8			m_softversion[TP_MAX_VERSION_LEN+1];  //����汾��
	s8			m_compileTime[TP_MAX_VERSION_LEN+1];  //����ʱ��

public:
	tagTTPSipRegistrarCfg(){ memset( this, 0, sizeof(struct tagTTPSipRegistrarCfg) ); }

}TTPSipRegistrarCfg,*PTTPSipRegistrarCfg;

//Gk Register����
typedef struct tagTTPGkRegistrarCfg
{
	BOOL   bUsed;   //�Ƿ�ע��
	u32_ip dwRegIP; //ע�������IP��ַ
	u16    wRegPort;//ע��������˿�
	s8     achRegDomain[TP_MAX_PROXYSERVER_NAME_LEN];
	u16    wExpire;
	BOOL   bRegistered;//ע��������Ƿ�ɹ�
	
	TTPRegName atTPRegName[TP_REGNAME_SIZE];//ע�����֧�ֶ��
	s32		   nTPRegNameSize;//ʵ�ʱ�������
	s8     achHostDomain[TP_MAX_PROXYSERVER_NAME_LEN];//��������
	u32_ip dwHostIP;
	u16    wHostPort;      
public:
	tagTTPGkRegistrarCfg(){ memset( this, 0, sizeof(struct tagTTPGkRegistrarCfg) ); }
}TTPGkRegistrarCfg;

typedef struct tagTTPGKCfg
{
	BOOL bUsed; //�Ƿ�ʹ��GK
	u32_ip  dwGKIP; //GK IP��ַ
	u16    wRegPort;//GK �˿�
	u16	 wExpire;
	BOOL bRegistered;//ע��������Ƿ�ɹ�
    s8   achGkIpName[TP_MAX_H323ALIAS_LEN + 1]; //Gk������ַ	��������
	s8   achGKPasswd[TP_MAX_PASSWORD_LEN + 1]; //Gk����		��������
public:
	tagTTPGKCfg(){ memset( this ,0 ,sizeof( struct  tagTTPGKCfg ) );}
}TTPGKCfg;



typedef struct tagTTPSipRegPackInfo
{
	u16 m_wPackSeq;       //����ţ���1��ʼ��0Ϊ��Чֵ
	u16 m_wTotalPackNum;  //������
	tagTTPSipRegPackInfo()
	{
		m_wPackSeq = 0;
		m_wTotalPackNum = 0;
	}
	tagTTPSipRegPackInfo& operator = ( const tagTTPSipRegPackInfo &tSipRegPackInfo )
	{
		if( this == &tSipRegPackInfo )
		{
			return *this;
		}
		m_wPackSeq = tSipRegPackInfo.m_wPackSeq;
		m_wTotalPackNum = tSipRegPackInfo.m_wTotalPackNum;

		return *this;

	}

	tagTTPSipRegPackInfo( const tagTTPSipRegPackInfo &tSipRegPackInfo )
	{
		if( this == &tSipRegPackInfo )
		{
			return;
		}

		m_wPackSeq = tSipRegPackInfo.m_wPackSeq;
		m_wTotalPackNum = tSipRegPackInfo.m_wTotalPackNum;
		
	}
}TTPSipRegPackInfo, *PTTPSipRegPackInfo;

//��SIPע��������õ�ȫ����Ϣ
typedef struct tagTTPSipRegInfo
{
	u16				m_wAliasNum;
	TTPAlias		m_atAlias[TP_REGNAME_SIZE];                 //��ʱ��Ϊ���ֵΪ64������Ϊһ������
	
	EmTPEndpointType	m_emSelfType;//ע�᷽ ��ϵͳ����(UMS��CNS)				

	tagTTPSipRegInfo()
	{
		m_wAliasNum = 0;
		memset( m_atAlias, 0, sizeof( m_atAlias ) );
		m_emSelfType = emTPEndpointTypeUnknown;
	}

	tagTTPSipRegInfo& operator = ( const tagTTPSipRegInfo &tSipRegInfo )
	{
		if( this == &tSipRegInfo )
		{
			return *this;
		}
		m_wAliasNum = tSipRegInfo.m_wAliasNum;
		m_emSelfType = tSipRegInfo.m_emSelfType;
		memcpy( m_atAlias, tSipRegInfo.m_atAlias, sizeof( m_atAlias ) );
		
		return *this;
		
	}
	
	tagTTPSipRegInfo( const tagTTPSipRegInfo &tSipRegInfo )
	{
		if( this == &tSipRegInfo )
		{
			return;
		}
		m_wAliasNum = tSipRegInfo.m_wAliasNum;
		m_emSelfType = tSipRegInfo.m_emSelfType;
		memcpy( m_atAlias, tSipRegInfo.m_atAlias, sizeof( m_atAlias ) );
	}
}TTPSipRegInfo;


//CNS�洢ע����Ľṹ��
typedef struct tagTTPSipPack
{
	TTPSipRegPackInfo m_tSipRegPackInfo;
	TTPSipRegInfo m_tSipRegInfo;

	tagTTPSipPack()
	{
		memset( this, 0, sizeof( tagTTPSipPack ) );
	}
	
	tagTTPSipPack &operator=( const tagTTPSipPack &tSipPack )
	{
		if( this == &tSipPack )
		{
			return *this;
		}
		m_tSipRegPackInfo = tSipPack.m_tSipRegPackInfo;
		m_tSipRegInfo = tSipPack.m_tSipRegInfo;

		return *this;
	}

	tagTTPSipPack( const tagTTPSipPack &tSipPack )
	{
		if( this == &tSipPack )
		{
			return;
		}
		m_tSipRegPackInfo = tSipPack.m_tSipRegPackInfo;
		m_tSipRegInfo = tSipPack.m_tSipRegInfo;
		
	}
	
}TTPSipPack;


//ȫ�ֵ�ַ֪ͨ�û��б���
typedef struct tagTTPAddrNtyUser
{
	u32 m_dwIID;               //APP+INS ID					   UMSʱ��ʾTLogUser Node
	u32 m_wUserData;           //USERDATA2  ���߶��������0    UMSʱ��ʾTLogUser inst
	EmGetRegInfoType m_emType;
	
	tagTTPAddrNtyUser( u32 dwIID, u16 wUserData, EmGetRegInfoType emType)
	{
		if( 0 == dwIID || 0 == wUserData )
		{
			return;
		}
		m_dwIID = dwIID;
		m_wUserData = wUserData;
		m_emType = emType;
	}
	
	tagTTPAddrNtyUser( const tagTTPAddrNtyUser &tNtyUser )
	{
		if( this == &tNtyUser )
		{
			return;
		}

		m_dwIID = tNtyUser.m_dwIID;
		m_wUserData = tNtyUser.m_wUserData;
		m_emType = tNtyUser.m_emType;
	}

	tagTTPAddrNtyUser& operator = (const tagTTPAddrNtyUser &tNtyUser )
	{
		if( this == &tNtyUser )
		{
			return *this;
		}
		m_dwIID = tNtyUser.m_dwIID;
		m_wUserData = tNtyUser.m_wUserData;
		m_emType = tNtyUser.m_emType;
		return *this;
	}
	tagTTPAddrNtyUser()
	{
	}
	u16 GetInstID()
	{
		return (u16)m_dwIID;
	}
}TTPAddrNtyUser;







//UMS,CNS����Э��ջע������Ϣ
typedef struct tagTUCSipRegResult
{
	EmTpCnsRegUms m_emTpCnsRegUms;        //ע����
	TTPAlias m_atTPAlias[TP_CONFTEMPGROUP_MAXNUM];
	s32 m_nAliasNum;                     //ʵ�ʱ�������

}TUCSipRegResult;


//�ն˵�ַ
typedef struct tagTCnAddr
{
	EmTPAddrType	emType;							//��ַ����
	u32_ip			 dwIP;						//�ն�IP��ַ
	u16          wPort;						//�˿�
	s8			 achAlias[TP_MAX_H323ALIAS_LEN+1];		//(����)
	s8			 achE164[TP_MAX_H323ALIAS_LEN+1];		//(164��)
public:
	tagTCnAddr(){memset( this ,0 ,sizeof( struct tagTCnAddr));	}
}TCnAddr;
//���в���
typedef struct tagTTPDialParam
{
	EmTpConnectionType emTpConnectionType;  //�������ӷ�ʽ tcp udp default tcp
	EmTpCallMode   emCallType;			// ��������:JOIN|CREATE|INVITE
	EmTpConfProtocol emProtocol;          // ͨ��Э��Э��
	u16			 wCallRate;			    // ��������(kbps)	
	TCnAddr	     tCallingAddr;		    // ���е�ַ(����ʱ�ɲ���)
	TCnAddr	     tCalledAddr;			// ���е�ַ		
	
	EmTPEndpointType      m_emEndpointType;					  //�ն�����  ��ʾ�����ն˵�����
	BOOL32			      m_bIsEncrypt;						//�Ƿ�֧�ּ���
	   
	s32					  m_nProductIdSize;
	u8					  m_abyProductId[TP_NAME_LEN_256];				//��Ʒ��
	s32					  m_nVerIdSize;
	u8					  m_abyVersionId[TP_NAME_LEN_256];				//�汾��
	
	u32_ip		dwRegIP; //ע�������IP��ַ
	u16		wRegPort;//ע��������˿�
	s8		achRegDomain[TP_MAX_PROXYSERVER_NAME_LEN];
	s8     achDisplayName[TP_MAX_NAME_LEN+1];  //����
    s8     achUserName[TP_MAX_NAME_LEN+1];     //ע����
	s8     achPassword[TP_MAX_PASSWORD_LEN+1]; //ע������
	s8     achHostDomain[TP_MAX_PROXYSERVER_NAME_LEN];//��������
	//////////////////////////////////////////////////////////////////////////
	//���½����ڴ�������
	BOOL		bCreateConf;		//�Ƿ��Ǵ�������
	TTPConfBaseInfo   tConfInfo;			//������Ϣ
	u8			byTerNum;			//�����ն˸���
	TCnAddr 	atList[TP_CONF_INVITE_MAX_CNS];	//�����ն��б�

	EmTPSipLevel m_emSipLevel;
	s32          m_nScreenNum;	

public:
	tagTTPDialParam(){ memset( this ,0 ,sizeof( struct tagTTPDialParam ) );}
}TTPDialParam,*PTTPDialParam;

typedef struct tagTTPCnsInfo
{		
	s8	m_achRoomName[TP_MAX_ALIAS_LEN+1];	//�᳡��	
	s8	m_achE164[TP_MAX_ALIAS_LEN+1];	    //E164��	
	u16 m_wScreenNum;						//�᳡����
	EmTPSipLevel	m_emLevel;							//�᳡�ȼ�
	u8  m_byDualPos;                       //�Ƿ���˫��Դ 0xffΪû��˫��
	u32_ip m_adwIP[CNS_MAX_TER_NODE_NUM];        //�᳡ip
	//Add by tanxiaodong 2012-12-07.
	//B2�汾��CNCϵͳ����-�᳡������Ҫ�Ƿ���ʾ�᳡���Ĺ���
	BOOL m_bIsShowRoomName;
	//End to add.
	public:
	tagTTPCnsInfo(){ memset( this ,0 ,sizeof( struct tagTTPCnsInfo ) );}
}TTPCnsInfo;

//ʱ��ṹ���¶���
typedef struct tagTTPTime
{
    u16 		m_wYear;//��
    u8  		m_byMonth;//��
    u8  		m_byMDay;//��
    u8  		m_byHour;//ʱ
	u8  		m_byMinute;//��
	u8  		m_bySecond;//��
public:
    tagTTPTime(){ memset ( this ,0 ,sizeof( struct tagTTPTime) );}
	BOOL32 IsValid()	{ return m_wYear != 0 && m_byMonth != 0 && m_byMDay != 0;}
	BOOL32 operator < (const tagTTPTime& tRhs)
	{
		if (m_wYear < tRhs.m_wYear)	return TRUE;
		else if (m_wYear > tRhs.m_wYear)	return FALSE;
		else
		{
			if (m_byMonth < tRhs.m_byMonth) return TRUE;			
			if (m_byMonth > tRhs.m_byMonth) return FALSE;
			else
			{
				if (m_byMDay < tRhs.m_byMDay) return TRUE;			
				if (m_byMDay > tRhs.m_byMDay) return FALSE;
				else
				{
					if (m_byHour < tRhs.m_byHour) return TRUE;			
					if (m_byHour > tRhs.m_byHour) return FALSE;
					else
					{
						if (m_byMinute < tRhs.m_byMinute) return TRUE;			
						if (m_byMinute > tRhs.m_byMinute) return FALSE;
						else
						{
							if (m_bySecond < tRhs.m_bySecond) return TRUE;			
							if (m_bySecond > tRhs.m_bySecond) return FALSE;
							else
							{
								return FALSE;
							}		
						}	
					}	
				}
			}
		}
	}
}TTPTime, *PTTPTime;

typedef struct tagTTPCnsConfStatus
{		
	 EmCALLSTATE	emState;
	 u16			wConfID;//
	 s8				achConfName[TP_MAX_ALIAS_LEN+1];
	 time_t         m_tmStartTime;    //���鿪ʼʱ��
	 EmCallType     m_emCallType;     //��������
	 BOOL32         m_bMixMotive;     //�Ƿ������������
	 //Add by tanxiaodong 2012-12-03.
	 EmTpConfProtocol m_emConfProtocal;//����Э������
	 //End to add.
	public:
	tagTTPCnsConfStatus(){ clear() ;};
	void clear()
	{ 
		memset( this ,0 ,sizeof( struct tagTTPCnsConfStatus ) ); 
		m_bMixMotive = 1;
		wConfID = 0xffff;

	};
}TTPCnsConfStatus;


typedef struct tagTTPDualInfo
{
	EmTPPayloadType m_emPayload;
	EmTpVideoResolution  m_emReslution;
	u16				m_wFrameRate;
	u16             m_wBitRate;
	s32 m_nScreenNo;
	s32 m_nEpId;
	s8  m_achCascade[TP_MAX_ALIAS_LEN+1];
	TTPTransAddr m_tRtp;
	TTPTransAddr m_tRtcp;
	TTPTransAddr m_tBackRtp;
	
	tagTTPDualInfo()
	{
		memset( this, 0, sizeof(tagTTPDualInfo) );
	}
	
}TTPDualInfo;

typedef struct tagTTPDualRequest
{
	s8 m_achCascade[ TP_MAX_ALIAS_LEN + 1 ];
	s32 m_nEpId;
	tagTTPDualRequest()
	{
		memset( this, 0, sizeof(tagTTPDualRequest) );
	}
}TTPDualRequest;

typedef struct tagTTPDualInfoAck
{
	BOOL    m_bAccept;
	TTPDualInfo m_tDualInfo;
	tagTTPDualInfoAck()
	{
		memset( this, 0, sizeof(tagTTPDualInfoAck) );
	}
}TTPDualInfoAck;

typedef struct tagTTPAudioInfo
{
	u8     m_byInputVolume;  //��������������������
	u8     m_byOutputVolume; //�������������������

	public:
	tagTTPAudioInfo()
	{
		memset( this, 0, sizeof(tagTTPAudioInfo) );
	}
}TTPAudioInfo;

typedef struct tagTTPHduRegInfo
{
	BOOL32		m_bIsOnline;	//HDU�Ƿ�ע��
	u32_ip   		m_dwIpAddr;		//����IP��ַ	,   ������
	u16 		m_wStartPort;	//������ʼ���ն˿�, ������

	s8          m_achAlias[TP_MAX_ALIAS_LEN + 1];	//�᳡����
	u16			m_dwChannelHandle;					//ͨ����

	u16         m_wScreenNum;      //����
	tagTTPHduRegInfo()
	{
		m_bIsOnline = FALSE;
		m_dwIpAddr = 0;
		m_wStartPort = 0;
		m_achAlias[0] = '\0';
		m_dwChannelHandle = TP_INVALID_INDEX;
		m_wScreenNum = TP_INVALID_INDEX;
	}
	void SetAlias(const s8* alias)
	{
		strncpy(m_achAlias, alias, TP_MAX_ALIAS_LEN);
		m_achAlias[TP_MAX_ALIAS_LEN] = '\0';
	}
}TTPHduRegInfo;

typedef struct tagTTPHduPlayReq
{
	u16		m_wIndex;	//����

	s8		m_achAlias[TP_MAX_ALIAS_LEN + 1];
	u16		m_wScreenNum;
	u16		m_nChannelHandle;

	tagTTPHduPlayReq()
	{
		m_wIndex = 0;
		m_wScreenNum = TP_INVALID_INDEX;
		m_nChannelHandle = TP_INVALID_INDEX;

		m_achAlias[0] = '\0';
	}
	void SetAlias(const s8* alias)
	{
		strncpy(m_achAlias, alias, TP_MAX_ALIAS_LEN);
		m_achAlias[TP_MAX_ALIAS_LEN] = '\0';
	}
}TTPHduPlayReq;




typedef struct tagTTPCnLoginfo
{
	s32	nVersion;
public:
    tagTTPCnLoginfo(){ memset ( this ,0 ,sizeof( struct tagTTPCnLoginfo) );}
}TTPCnLoginfo;
//cns sp1 �½ṹ����
typedef struct tagTTPCn
{
	u8	byInsId;
	s8  achName[TP_MAX_ALIAS_LEN+1];
public:
    tagTTPCn(){ memset ( this ,0 ,sizeof( struct tagTTPCn) );}
}TTPCn;

typedef struct tagTTPCnList
{
	u16		wNum;
	TTPCn	tCn[MOON_MAX_NODE_NUM];
public:
    tagTTPCnList(){ memset ( this ,0 ,sizeof( struct tagTTPCnList) );}
}TTPCnList;
//end cns sp1
typedef struct tagTAudMixStat
{
	u16		m_wConfID;
	u16		m_wEpID;
	BOOL32	m_bIsStart;
	EmTpMixStatus	m_emMixStatus;
	tagTAudMixStat()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_wEpID = TP_INVALID_INDEX;
		m_bIsStart = FALSE;
		m_emMixStatus = emAudMixIdle;
	}
}TAudMixStat;

typedef struct tagTTPDisScreenStat
{
	BOOL32 m_bInDiscard;	//�û᳡�Ƿ���������
	u16 m_wEpIDDst;			//UMS������
	
	u16 m_awScreenNum[TP_MAX_STREAMNUM]; //��������Ӧ�᳡������
	u16 m_awSpeakerIndx[TP_MAX_STREAMNUM];//��������Ӧ�᳡�Ķ�Ӧ�ķ�����ϯ����
	TTPAlias m_atAlias[TP_MAX_STREAMNUM];//��������Ӧ�Ļ᳡��������Чֵ����˴��᳡Ϊ���迴��̬ͼƬ������Ϊ�м�
	EmTPDisOprType	m_emOprType;//��������
	
	tagTTPDisScreenStat()
	{
		memset( this, 0, sizeof(tagTTPDisScreenStat) );
	}
	
}TTPDisScreenStat;

typedef struct tagTTPGetRegInfo
{
	EmGetRegInfoType emType;
	u32    dwRegIP;         //ע�������IP��ַ
	u16    wRegPort;        //ע��������˿�
	u32    dwLocalIP;       //����ip
	u16    wLocalPort;           //���ض˿�
	
	tagTTPGetRegInfo()
	{
		memset( this, 0, sizeof(tagTTPGetRegInfo) );
	}
}TTPGetRegInfo;

typedef struct tagTTPAacCap : public TTPAudCap
{
	EmTPAACSampleFreq emPASampleFreq;
    EmTPAACChnlCfg    emPAChnlCfg;
public:
    tagTTPAacCap(){ memset ( this, 0, sizeof( struct tagTTPAacCap) );}
	
}TTPAacCap;

typedef struct tagTTPG7221Cap : public TTPAudCap
{
	u8  byBitRateType;         //encode bitrate
public:
	tagTTPG7221Cap()
		:TTPAudCap()
	{
		byBitRateType = emTPG7221Rate24;
	}
	
	void Clear()
	{
		TTPAudCap::Clear();
		byBitRateType = emTPG7221Rate24;
	};
	
    //����rate
	void SetRateType( u8 byRateType )
	{
		byBitRateType = byRateType;
	}
	void OrRateType( EmTPG7221Rate emPARateType )
	{
		byBitRateType = (byBitRateType | emPARateType);
	}
	
	//��ȡrate
	u8 GetRateType()
	{
		return byBitRateType;
	}
	
	
	void SetBitRate( u32 dwBitRate )
	{
		byBitRateType = 0;
		if ( dwBitRate == 48000 )
			byBitRateType |= emTPG7221Rate48;
        else if ( dwBitRate == 32000 )
			byBitRateType |= emTPG7221Rate32;
        else
			byBitRateType |= emTPG7221Rate24;
	}
	
	u16 GetBitRate()
	{
		if( byBitRateType & emTPG7221Rate48 )
			return 48000;
		else if ( byBitRateType & emTPG7221Rate32 )
			return 32000;
		else 
			return 24000;
	}
	
}TTPG7221Cap;

typedef struct tagTTPMediaStream
{	
	BOOL32 bActive;
	EmTpMediaType emTPMediaType;
	
	TTPTransAddr	tLocalRtp[TP_MAX_STREAMNUM];
	TTPTransAddr	tRemPAoteRtp;			
	
	TTPTransAddr	tSendRtcp[TP_MAX_STREAMNUM]; //  	
	TTPTransAddr	tRecvRtcp[TP_MAX_STREAMNUM]; //
	
	EmTPPayloadType aemTPMediaPT[20];
	u8 byMediaCount;
	
	
	//CPAH264VideoCap tH264Cap;
	TTPAudCap			tACap;
	TTPG7221Cap			tG7221;
	TTPAacCap		tAacCap;
	//��Ƶ����
	TTPVideoCap tVidCap;
	
	EmTPPayloadType  emTPActivePT;
	
	EmTPEncryptType emTPEncryptType;	  //��������
	//TPAEncryptSync  m_tEncryptSync;       //master�����ô˽ṹ         
	s32 nBitRate;
	u32 dwLocalIp;
	
	s32 nScreenNo;                      //�������ţ� ���
	s32 nPeerScreenNo;				  //�Զ����ţ� ���	
	EmTPCapSign m_emTPCapSign[TP_MAX_CAP_SIGN_NUM];            //��ʶ��С����, ����������ʱһ��Ҫ����˳�� ���У��� 
	
	BOOL32 bDual;                       //˫���� 
	EmTPChanType emTPChanType;

	BOOL32 m_bAudMix;				//����
	
public:
    tagTTPMediaStream(){ memset ( this ,0 ,sizeof( struct tagTTPMediaStream) );}
	
}TTPMediaStream;

typedef struct tagTTPCapMap 
{
	TTPMediaStream cMeadiaStream;
	s32 nChannelId;
public:
    tagTTPCapMap(){ memset ( this, 0, sizeof( struct tagTTPCapMap) );}
	
}TTPCapMap;

typedef struct tagTTPCapPack 
{
	u16		  wTotalPackNum;
	u16		  wCurPackIndex;
	u16		  wValidCapNum;
	TTPCapMap atTPCapMap[4];
public:
    tagTTPCapPack(){ memset ( this, 0, sizeof( struct tagTTPCapPack) );}
	
}TTPCapPack;

typedef struct tagTTPCnStream
{	
	u16 wIndex;
	s32 nScreenNo;
	EmTPChanType   emChanType;
	EmTpMediaType  emMediaType;
	EmTPChanSubType	emChanSubType;
	
	TTPMediaTransAddr tTPMediaTransAddr[TP_MAX_CAP_SIGN_NUM];

	EmTPCapSign m_emTPCapSign[TP_MAX_CAP_SIGN_NUM];            //��ʶ��С����, ����������ʱһ��Ҫ����˳�� ���У��� 

public:
	tagTTPCnStream(){ memset ( this, 0, sizeof( struct tagTTPCnStream) );}

}TTPCnStream;

typedef struct tagTTPCnUnpackStream
{
	u16 wIndex;
	s32 nScreenNo;
	EmTPChanType   emChanType;
	EmTpMediaType  emMediaType;
	EmTPChanSubType	emChanSubType;
	
	TTPMediaTransAddr tTPMediaTransAddr;
	
	EmTPCapSign m_emTPCapSign[TP_MAX_CAP_SIGN_NUM];            //��ʶ��С����, ����������ʱһ��Ҫ����˳�� ���У���
	
	u8 byMediaTransAddrIndex;//ý����ת����ַ����������Ϊ0��1��2
	
public:
	tagTTPCnUnpackStream(){ memset ( this, 0, sizeof( struct tagTTPCnUnpackStream) );}
	
}TTPCnUnpackStream;

typedef struct tagTTPDualCap 
{
	u16                 wDualVidCapNum;                 //˫����Ƶ��������
	TTPVideoCap			tVidCap[MAX__TP_MEDIA_CAP_NUM];						//��Ƶ����
	TTPAacCap			tAacCap;						//aacld��Ƶ����
	TTPAudCap			tG711a; 
	TTPAudCap			tG711u;  
	TTPAudCap			tG719;
	TTPG7221Cap			tG7221;
	TTPAudCap			tMP3;
	TTPAacCap			taaclc;
	EmTPPayloadType		aemTPMediaPT[20];				//�������Ƚ�������
	TTPCnStream			tCnDualStream[CNS_Dual_MAX_CHANNEL];
public:
    tagTTPDualCap(){ memset ( this, 0, sizeof( struct tagTTPDualCap) );}
	
}TTPDualCap;


typedef struct tagTCnsCapset 
{	
	EmTPEncryptType		emEncryptBits;			//��������
 	u16					wFECBits;							//FEC����
 	u16					wMaxBitRate;							//kbps�� Node֧�ֵ��ܴ���
 	
 	TTPVideoCap			tVidCap;						//��Ƶ����
 	TTPAacCap			tAacCap;						//aacld��Ƶ����
 	TTPAudCap			tG711a; 
 	TTPAudCap			tG711u;  
 	TTPAudCap			tG719;
 	TTPG7221Cap			tG7221;
 	TTPAudCap			tMP3;
 	TTPAacCap			taaclc;
	EmTPPayloadType		aemTPMediaPT[20];				//�������Ƚ�������

 	TTPCnStream			tCnStream[CNS_CALL_MAX_CHANNEL];
	u16					wChannelCount;
	u32					dwCnsIp;
public:
    tagTCnsCapset(){ memset ( this ,0 ,sizeof( struct tagTCnsCapset) );}

}TCnsCapset;

typedef struct tagTTPYouAreSeeing
{
	u32 m_dwVideoNum;	//��Ƶ��������
	u32 m_dwAudioNum;	//��Ƶ��������
	u16 m_CNSId;		//CNSID
	BOOL32 m_bExist;	//�Ƿ����
	s8  m_achMeetingName[TP_MAX_ALIAS_LEN + 1];	//�����˻᳡��
	u16 m_wSpeakerIndex;
	tagTTPYouAreSeeing()
	{
		memset( this, 0, sizeof(tagTTPYouAreSeeing) );
	}
	
}TTPYouAreSeeing;

//�ն˱�Ų���
typedef struct tagTTPTerLabel
{
	u8 m_byMcuNo;
	u8 m_byTerNo;
	tagTTPTerLabel()
	{
		memset( this, 0, sizeof(tagTTPTerLabel) );
	}
	
}TTPTerLabel;

typedef struct tagTPModuleTerminalInfo
{
	u8 m_byMcuNo;   
	u8 m_byTerNo;
	u8 m_byConfNo;   //�������
	s8 m_achTerminalId[TP_MAX_NUM_CALLID+1];    //TerminalID
	BOOL32 m_bIsChair;   //�Ƿ�����ϯ
	BOOL32 m_bIsFloor;   //�Ƿ��Ƿ�����
	
	BOOL32 m_bLastPack;  // �Ƿ������һ��
	BOOL32 m_bOnline;    // �Ƿ�����
	
	tagTPModuleTerminalInfo()
	{
		memset( this, 0, sizeof(tagTPModuleTerminalInfo) );
	}
	

}TPModuleTerminalInfo;

typedef struct tagTTPPollDstName
{
	s8				m_abyAlias[TP_MAX_ALIAS_LEN + 1];
	u32             m_nScreenNum;
	tagTTPPollDstName()
	{
		memset( this, 0, sizeof(tagTTPPollDstName) );
	}
}TTPPollDstName;


typedef struct tagTMtADecParam
{
	EmTpCodecComponent emComp;
	TTPCnMediaTransPort tAddr;
	EmTpAudioFormat	emAudioFormat;
	u8				byPayload;
	TTpEncryptKey		tEncryptKey;
	
	TTPG7221Cap			tG7221;
	TTPAacCap			tAaclc;
	u16                 wPos;
	tagTMtADecParam()
	{
		emComp = emTPAudioDecoder;
		emAudioFormat = emTPAG711a;
		byPayload = 0;
	};
}TMtADecParam;

typedef struct tagTMtAEncParam
{
	EmTpCodecComponent	emComp;
	TTPCnMediaTransPort tAddr;
	EmTpAudioFormat		emAudioFormat;
	u8					byPayload;
	TTpEncryptKey			tEncryptKey;
	
	TTPG7221Cap			tG7221;
	TTPAacCap			tAaclc;
	u16                 wPos;
	tagTMtAEncParam()
	{
		emComp = emTPAudioEncoder;
		emAudioFormat = emTPAG711a;
		byPayload = 0;
	};
}TMtAEncParam;

typedef struct tagTTPChanSelecteCascadRes
{
    u32 nRes;
	s8  achName[TP_MAX_ALIAS_LEN+1];
	tagTTPChanSelecteCascadRes()
	{
		memset(this, 0, sizeof(tagTTPChanSelecteCascadRes));
	}
}TTPChanSelecteCascadRes;

typedef struct tagTTPChanSelecteCascadCancelRes
{
	s32 nPeerID;
    u32 nRes;
	tagTTPChanSelecteCascadCancelRes()
	{
		memset(this, 0, sizeof(tagTTPChanSelecteCascadCancelRes));
	}
}TTPChanSelecteCascadCancelRes;

typedef struct tagTTerminalLabel 
{
	u8 m_byMcuNo;
	u8 m_byTerNo;
}TTerminalLabel;

typedef struct tagTTPDisListOpr
{
	u16 m_wConfID;
    u16 m_wEpID;
	u16 m_wIndex;//��CNC�����λ�� 0-3
	EmDisListOprType m_emOprType;
	EmDisListOprReslt m_emOprReslt; //�ظ�CNCʱʹ��
	tagTTPDisListOpr()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_wEpID = TP_INVALID_INDEX;
		m_wIndex = TP_INVALID_INDEX;
		m_emOprType = em_DisListOpr_Add;
		m_emOprReslt = em_DisListOpr_Sucess;
	}
}TTPDisListOpr;


typedef struct tagTTPRegistReq
{
	s8 m_atH323Alias[TP_MAX_ALIAS_LEN+1];
	s8 m_atE164[TP_MAX_ALIAS_LEN+1];
	
	
	TTPTransAddr m_tLocalAddress;    //��Ҫע��ĵ�ַ
	TTPTransAddr m_tGKAddress;
	TTPTransAddr m_tRegAddress;      //sip regserver��ַ
	
	s32			m_nTimeToLive;      //��
public:
	tagTTPRegistReq()
	{
		Clear();
	}
	void Clear()
	{
		memset( m_atE164 , 0 , sizeof(m_atE164) );
		memset( m_atH323Alias , 0 , sizeof(m_atH323Alias) );
		m_tLocalAddress.Clear();
		m_tGKAddress.Clear();
		m_tRegAddress.Clear();
		m_nTimeToLive = 60;
	}
}TTPRegistReq;

typedef struct tagTCnsAVCapset 
{	
	EmTPEncryptType		emEncryptBits;			//��������
	u16					wFECBits;							//FEC����
	u16					wMaxBitRate;							//kbps�� Node֧�ֵ��ܴ���
	
	u16 wVidCapNum;                                     //��Ƶ��������
	TTPVideoCap			atVidCap[MAX__TP_MEDIA_CAP_NUM];						//��Ƶ����
	TTPAacCap			tAacCap;						//aacld��Ƶ����
	TTPAudCap			tG711a; 
	TTPAudCap			tG711u;  
	TTPAudCap			tG719;
	TTPG7221Cap			tG7221;
	TTPAudCap			tMP3;
	TTPAacCap			taaclc;
	EmTPPayloadType		aemTPMediaPT[20];				//�������Ƚ�������
	u32					dwCnsIp;
public:
    tagTCnsAVCapset(){ memset ( this ,0 ,sizeof( struct tagTCnsAVCapset) );}
	
}TCnsAVCapset;

typedef struct tagTCnsAddrCapset 
{		
	TTPCnStream			tCnStream[CNS_CALL_MAX_CHANNEL];
	u16					wChannelCount;
	u32					dwCnsIp;
public:
    tagTCnsAddrCapset(){ memset ( this ,0 ,sizeof( struct tagTCnsAddrCapset) );}
	
}TCnsAddrCapset;

 //Add by tanxiaodong 2012-07-17.
//VGA�豸��Ϣ�ṹ��
typedef struct tagTVgaInfo
{
	EmVgaType m_emVgaType;              //VGA�豸����
	s8 m_achAlias[TP_MAX_ALIAS_LEN + 1];//��Ӧ���豸����
	tagTVgaInfo()
	{
		memset( this, 0, sizeof(tagTVgaInfo) );
	}

}TVgaInfo;

typedef struct tagTTPNatCfg
{
	BOOL bUsed; //�Ƿ�ʹ�þ�̬NAT
	u32_ip  dwNatIP; //��̬NAT IP��ַ
public:
	tagTTPNatCfg(){ memset( this ,0 ,sizeof( struct  tagTTPNatCfg ) );}
}TTPNatCfg;

typedef struct tagTUmsVersion
{
	s8		m_abSoftVersion[TP_TOOL_VERSION_LEN + 1];	//����汾
	s8		m_abHardVersion[TP_TOOL_VERSION_LEN + 1];	//Ӳ���汾

	public:
	tagTUmsVersion()
	{ 
		memset( this ,0 ,sizeof( struct  tagTUmsVersion ) );
	}

	void SetSoftVersion(s8* bVer)
	{
		if(bVer == NULL) 
		{
			return;
		}

        memset(m_abSoftVersion, 0, TP_TOOL_VERSION_LEN + 1);
        int length = (strlen(bVer) >= TP_TOOL_VERSION_LEN ? TP_TOOL_VERSION_LEN : strlen(bVer));
        memcpy(m_abSoftVersion, bVer, length);
        m_abSoftVersion[length] = '\0';
	}

	void SetHardVersion(s8* bVer)
	{
		if(bVer == NULL) 
		{
			return;
		}
		
        memset(m_abHardVersion, 0, TP_TOOL_VERSION_LEN + 1);
        int length = (strlen(bVer) >= TP_TOOL_VERSION_LEN ? TP_TOOL_VERSION_LEN : strlen(bVer));
        memcpy(m_abHardVersion, bVer, length);
        m_abHardVersion[length] = '\0';
	}
}TUmsVersion;


typedef struct tagTToolSysInfo
{
	u32			m_dwCpuRate;	//CPUʹ����
	u32			m_dwMemRate;	//�ڴ�ʹ����
	public:
	tagTToolSysInfo()
	{ 
		memset( this ,0 ,sizeof(struct  tagTToolSysInfo));
	}
}TToolSysInfo;

typedef struct tagTHduChanInfo
{
	EmHduOutPort	m_emOutPortType;	//�ӿ�����
    EmHduOutMode	m_emOutModeType;	//�����ʽ
	EmHduZoomRate	m_emZoomRate;		//���ű���
	EmHduShowMode	m_emShowMode;		//�������

	tagTHduChanInfo()
	{
		Clear();
	}
	
	void Clear()
	{
		m_emOutPortType = em_hdu_outport_unknow;
		m_emOutModeType = em_hdu_outmode_unknow;
		m_emZoomRate    = em_hdu_zoomrate_unknow;
		m_emShowMode    = em_hdu_showmode_unknow;
	}

	tagTHduChanInfo& operator = (const tagTHduChanInfo& tChan)
	{
		if (this == &tChan)
		{
			return *this;
		}

		m_emOutPortType = tChan.m_emOutPortType;
		m_emOutModeType = tChan.m_emOutModeType;
		m_emShowMode = tChan.m_emShowMode;
		m_emZoomRate = tChan.m_emZoomRate;

		return *this;
	}

	BOOL32	IsValid()
	{
		return (m_emOutPortType != em_hdu_outport_unknow  &&
				m_emOutModeType != em_hdu_outmode_unknow  &&
				m_emZoomRate    != em_hdu_zoomrate_unknow &&
				m_emShowMode    != em_hdu_showmode_unknow
				);
	}

	void SetOutType(const EmHduOutPort& emType)
	{
		m_emOutPortType = emType;
	}

	EmHduOutPort GetOutType()
	{
		return m_emOutPortType;
	}

	void SetOutMode(const EmHduOutMode& emType)
	{
		m_emOutModeType = emType;
	}

	EmHduOutMode GetOutMode()
	{
		return m_emOutModeType;
	}

	void SetZoomRate(const EmHduZoomRate& emRate)
	{
		m_emZoomRate = emRate;
	}

	EmHduZoomRate GetZoomRate()
	{
		return m_emZoomRate;
	}

	void SetShowMode(const EmHduShowMode& emMode)
	{
		m_emShowMode = emMode;
	}

	EmHduShowMode GetShowMode()
	{
		return m_emShowMode;
	}

}THduChanInfo;

//����ǽ��Ϣ
typedef struct tagTHduInfo
{
	u8			m_byLayer;		//���
	u8			m_bySlot;		//�ۺ�

	EMBrdType		m_emBrdType;
	THduChanInfo	m_atChanInfo[HDU_MAX_CHANNEL_NUM];
	TTPName			m_tName;

	tagTHduInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_byLayer = 0;
		m_bySlot  = 0;

		for (u16 wIndex = 0; wIndex < HDU_MAX_CHANNEL_NUM; ++wIndex)
		{
			m_atChanInfo[wIndex].Clear();
		}

		m_emBrdType = em_hdu2_brd;
	}
}THduInfo;

//����ǽ������Ϣ
typedef struct tagTHduCfg
{	
	u8		m_byLayer;		//���
	u8		m_bySlot;		//�ۺ�
	u32_ip	m_dwIP;			//IP

	u8		m_byChanNum;	//���õ�ͨ������
	THduChanInfo	m_atChanInfo[HDU_MAX_CHANNEL_NUM];
	TTPName			m_tName;

	BOOL32			m_bReg;	//�����Ƿ�ע��
	BOOL32			m_bServiceReg;	//ҵ���Ƿ�ע��

	tagTHduCfg()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTHduCfg));

		m_byLayer = (u8)TP_INVALID_INDEX;
		m_bySlot = (u8)TP_INVALID_INDEX;
		for (u8 byIndex = 0; byIndex < HDU_MAX_CHANNEL_NUM; ++byIndex)
		{
			m_atChanInfo[byIndex].Clear();
		}
	}

	tagTHduCfg& operator =(const tagTHduCfg& tCfg)
	{
		if( this == &tCfg )
		{
			return *this;
		}

		m_byLayer = tCfg.m_byLayer;
		m_bySlot = tCfg.m_bySlot;
		m_dwIP = tCfg.m_dwIP;
		m_byChanNum = tCfg.m_byChanNum;

		for (u8 byIndex = 0; byIndex < HDU_MAX_CHANNEL_NUM; ++byIndex)
		{
			m_atChanInfo[byIndex] = tCfg.m_atChanInfo[byIndex];
		}
		m_tName.SetAlias(tCfg.m_tName.m_abyAlias);
		m_bReg = tCfg.m_bReg;
		m_bServiceReg = tCfg.m_bServiceReg;

		return *this;
	}

}THduCfg;

//����ǽ���Ԫ����Ϣ�����ά������
typedef struct tagTHduStyleUnit
{
	u8		m_byLayer;		//���
	u8		m_bySlot;		//�ۺ�
	u8		m_byChanIndex;	//ͨ����
	TTPName m_tName;        //������

	tagTHduStyleUnit()
	{
		Clear();
	}

	void Clear()
	{
		m_byLayer = HDU_MAX_LAYER;
		m_bySlot  = HDU_MAX_SLOT;
		m_byChanIndex = HDU_MAX_CHANNEL_NUM;
		m_tName.Clear();
	}
}THduStyleUnit;

typedef struct tagTHduStyleData
{
	u8		m_byRow;
	u8		m_byCol;
	
	THduStyleUnit m_atUnits[HDU_STYLE_MAX_NUM];

	tagTHduStyleData()
	{
		Clear();
	}

	void Clear()
	{
		m_byRow = 0;
		m_byCol = 0;

		for (u16 wIndex = 0; wIndex < HDU_STYLE_MAX_NUM; ++wIndex)
		{
			m_atUnits[wIndex].Clear();
		}
	}

}THduStyleData;

//����ǽԤ�������UMC
typedef struct tagTHduPlanUnit
{	
	BOOL32	m_bReged;		//����״̬
	TTPName	m_tName;		//�᳡����
	u16		m_wConfID;		//����ID
	u16		m_wScreenNum;	//����
	BOOL32	m_bValid;		//�Ƿ���Ч
	u16		m_wIndex;		//����
	EmTPHduRunStatus m_emStatus;
	TTPName	m_tHduName;	//HDU ������
	u16		m_wChannel;	//ͨ����
	
	tagTHduPlanUnit()
	{
		Clear();
	}
	
	void Clear()
	{
		memset(this, 0, sizeof(tagTHduPlanUnit));
	}
}THduPlanUnit;

typedef struct tagTHduPlanData
{
	u8		m_byRow;
	u8		m_byCol;
	
	THduPlanUnit m_atUnits[HDU_STYLE_MAX_NUM];
	
	tagTHduPlanData()
	{
		Clear();
	}
	
	void Clear()
	{
		memset(this, 0, sizeof(tagTHduPlanData));
	}

}THduPlanData;

typedef struct tagTHduStyleInfo
{


	u8		m_byLayer;			//��Ӧ�Ĳ��
	u8		m_bySlot;			//��Ӧ�Ĳۺ�
	u8		m_byChanIndex;		//ͨ����
	TTPName	m_tName;			//����

	tagTHduStyleInfo()
	{
		Clear();
	}

	void Clear()
	{


		m_byLayer = HDU_MAX_LAYER;
		m_bySlot  = HDU_MAX_SLOT;
		m_byChanIndex = HDU_MAX_CHANNEL_NUM;
		
		m_tName.Clear();
	}
}THduStyleInfo;

//End to add.

//Added by meifang
//���ܷ�����������Ϣ
typedef struct tagTTPNMServerCfg
{
	u32_ip dwNMServerIP;   //�澯������ַ
	u16    wNMGetSetPort;  //��д�˿ڣ�Ĭ��Ϊ161
	u16    WNMTrapPort;    //������˿ڣ�Ĭ��Ϊ162
 	s8     achNMReadCommunity[MAX_COMMUNITY_LENGTH];  //Ĭ��Ϊpublic
 	s8     achNMWriteCommunity[MAX_COMMUNITY_LENGTH];//Ĭ��Ϊkdv123 
	u16    wNMServerNO;

	public:
	tagTTPNMServerCfg()
	{
		memset( this, 0, sizeof(struct tagTTPNMServerCfg) );
	}

}TTPNMServerCfg;
//End to add

//Add by tanxiaodong 2012-11-19.
//ϵͳʹ����Ϣ
typedef struct tagTTPSysInfo
{
	u8 m_byCpuRate;    //CPUʹ����
	u32 m_dwTotalByte; //�ڴ�����
	u32 m_dwAllocByte; //��ʹ���ڴ�

public:
	tagTTPSysInfo()
	{ 
		memset( this, 0, sizeof(struct  tagTTPSysInfo));
	}
}TTPSysInfo;

//TPad�б���Ϣ
typedef struct tagTTPTPadList
{
	u32_ip m_adwTPadIP[TPAD_MAX_NUM];
	u8  m_byTPadNum;
	u8  m_byUserId[TPAD_MAX_NUM];
	u32 m_dwTPadNode[TPAD_MAX_NUM];
	s8  m_aachTPadVersion[TPAD_MAX_NUM][MAX_DEVICEVER_LEN];

public:
	tagTTPTPadList()
	{ 
		memset( this, 0, sizeof(struct  tagTTPTPadList));
	}
}TTPTPadList;

//��ũ���������Ϣ
typedef struct tagTTPSingleAudioPortCfg
{
	u8               byMicVolume;//����
	BOOL             bIsSimplexPoweringOpened; //��ũ��˻��󹩵翪��
	u8               byAudioBNA;//��������
	tagTTPSingleAudioPortCfg()
	{
		memset( this, 0, sizeof(struct tagTTPSingleAudioPortCfg) );
	}
}TTPSingleAudioPortCfg;

//��Ƶ�ӿ�������Ϣ
typedef struct tagTTpAudioPortInfo
{
	u8 m_byGroupIndex;   //��Ƶ�ӿڵ���������
	BOOL m_abAudioPort[AUDIO_PORT_NUM]; //�Ƿ�ѡ����Ƶ�ӿ�
	u8 m_abyVolume[AUDIO_PORT_NUM];     //ѡ�нӿڵ�����
	TTPSingleAudioPortCfg m_atSingleAudioPortCfg[AUDIO_PORT_NUM];
public:
	tagTTpAudioPortInfo()
	{ 
		memset( this, 0, sizeof(struct  tagTTpAudioPortInfo));
	}
}TTpAudioPortInfo;


//��Ƶ�ӿ�������Ϣ
typedef struct tagTTPVideoPortInfo
{
	EmSwitchState emVideoState;   //��Ƶ״̬
	EmTpVideoResolution m_emRes;  //�ֱ���
	u8 m_byFrameRate;             //֡��
	BOOL m_bIsHaveVideoSrcOutput; //�Ƿ�����Ƶ���(������Ƶ����ӿڵĲ���)
	u8 m_byVolum;                 //������С(������ʾԴ�е���Ƶ����)

public:
	tagTTPVideoPortInfo()
	{ 
		memset( this, 0, sizeof(struct  tagTTPVideoPortInfo));
	}
}TTPVideoPortInfo;

//��Ƶ��Ͻӿڽṹ�壺
typedef struct tagTTPVideoDiagInfo
{
	//�����1,2,3��Ƶ�ӿ�������Ϣ
	TTPVideoPortInfo m_atPrimVideoInputPort[MAX_PRIM_VIDEO_INPUT_PORT_NUM];	

	//�����1,2,3��Ƶ�ӿ������Ϣ
	TTPVideoPortInfo m_atPrimVideoOutputPort[MAX_PRIM_VIDEO_OUTPUT_PORT_NUM];

	u8 m_byInputDemoIndex;//ѡ��������ʾԴ����
	TTPVideoPortInfo m_tDemoVideoInputPort;//��ʾԴ����ӿ���Ϣ

	u8 m_byOutputDemoIndex;//ѡ�������ʾԴ����
	TTPVideoPortInfo m_tDemoVideoOutputPort;//��ʾԴ����ӿ���Ϣ

public:
	tagTTPVideoDiagInfo()
	{ 
		memset( this, 0, sizeof(struct  tagTTPVideoDiagInfo));
	}
}TTPVideoDiagInfo;

//��Ƶ��Ͻӿڽṹ�壺
typedef struct tagTTPAudioDiagInfo
{
	//3����Ƶ����ӿ���Ϣ
	TTpAudioPortInfo m_atPrimAudioInputPort[MAX_PRIM_AUDIO_INPUT_PORT_NUM];
	
	//3����Ƶ����ӿ���Ϣ
	TTpAudioPortInfo m_atPrimAudioOutputPort[MAX_PRIM_AUDIO_OUTPUT_PORT_NUM];

	//�����ʾ��Ƶ����ӿ�
	BOOL m_abDemoAudioPort[MAX_DEMO_AUDIO_PORT_NUM];
	
public:
	tagTTPAudioDiagInfo()
	{ 
		memset( this, 0, sizeof(struct  tagTTPAudioDiagInfo));
	}
}TTPAudioDiagInfo;

//����������������Ϣ�ṹ��
typedef struct tagTTPUpDownNetSpeedInfo
{
	u32 m_dwInputByteDvalue;//����������ֽ���
    u32 m_dwOutputByteDvalue;//�����������ֽ���
	
public:
	tagTTPUpDownNetSpeedInfo()
	{ 
		memset( this, 0, sizeof(struct  tagTTPUpDownNetSpeedInfo));
	}
}TTPUpDownNetSpeedInfo;

//�������������ʽṹ��
typedef struct tagTTPUpDownSpeedInfo
{
	u16 m_wUpSpeed;  //��������
	u16 m_wDownSpeed;//��������

public:
	tagTTPUpDownSpeedInfo()
	{ 
		memset( this, 0, sizeof(struct  tagTTPUpDownSpeedInfo));
	}
}TTPUpDownSpeedInfo;

typedef struct tagTTPVgaMixInfo
{
	//��ǰѡ����ʾԴ����ӿ�
	EmVgaType m_emCurrentType;

	//��ǰѡ����ʾԴ����ӿ�
	EmDualOutputType m_emDualOutputType;

	//��ʾԴ����ӿ�����
	s8 m_achVgaOutputFstName[MAX_ALIAS_LEN];
	s8 m_achVgaOutputSndName[MAX_ALIAS_LEN];

public:
	tagTTPVgaMixInfo()
	{ 
		memset( this, 0, sizeof(struct  tagTTPVgaMixInfo));
	}
}TTPVgaMixInfo;
//End to add.

//Add by zhangapei
//�����������Ϣ
typedef struct tagTCnCameraCfg
{
	//��������Ԥ��λ1
	BOOL         bUsed; 
	s8           achCamera[MAX_CAMERA_NAME_LEN + 1]; //����ͷ��
	u8           byAddr;        //�������ַ
	EmSerialType emSerialType;
	u32_ip       dwSerialServerIP; //���ڷ�����IP ,����ֵΪ0ʱ��ʾʹ�ñ��ش���
    u16          wSerialServerPort; //���ڷ������˿ں�  0

	//��Ұ��С
 	u16             wZoom; 
//  EmFocusMode     emFocusMode;//�۽�ģʽ
	//��OSD����ʾ��Ұ����
    EmOSDShow       emOSDShow;
	//�ع�ģʽ
	EmExpMode       emExpMode;
	//�ֶ��ع�
	EmGain          emGain;//���� 
	EmShutSpd       emShutSpd; //����
	EmBackLightType emBackLightType; //���ⲹ��
	u8              byMulti; //��㱳��ǿ������
	u8              byApt;//�ع��Ȧֵ
	//��ƽ��ģʽ
	EmWBMode        emWBMode;
	//�ֶ���ƽ�� 
	u16             wRGain; //��ɫR ֵ
    u16             wBGain; //��ɫB ֵ
	//����ģʽ
	EmPicSceMode    emPicMode; 
	//�ֶ�����ģʽ
	EmGamma         emGamma; //����Gammaֵ
	u8              byPicApt;//������Ȧֵ
	//ͼƬ����
	u16             wContrast; //�Աȶ�
	u16             wHue;      //ɫ��
	u16             wSaturat;  //���Ͷ�
	u16             wBright;   //����
    EmStmClean      emStmClean; //����
	Em3DNR          em3DNR;     //��о3D��������
    
	public:
		tagTCnCameraCfg()
		{
			memset( this, 0, sizeof(struct tagTCnCameraCfg) );
		}
		
}TCnCameraCfg;

//�пص��ӻ�������Ϣ
typedef struct tagTCentreTVCfg
{
	EmSerialType           emSerialType;  //���ӻ����Ӵ�������
	EmTvPowerMode          emTvPowerMode; //���ӻ�����״̬ 
	EmTVAudVisMode         emAudVisMode; //���ӻ�����ģʽ
	EmTVDisplayMode        emDisMode;    //���ӻ���ʾģʽ
	EmTVInputSelect        emInpSelect;  //��������ѡ��
	EmTvSrcPowerMode	   emTvSrcPowerMode;//���ӻ��ϵ�ǰ����״̬
    
	public:
		tagTCentreTVCfg()
		{
			memset( this, 0, sizeof(struct tagTCentreTVCfg) );
		}
		
}TCentreTVCfg;

typedef struct tagTTVAct
{
	u16         wEvent;   //���ӻ���������������Ϣ
	u8          byemType; //��������
	u8          byTVIndx;
	time_t      ttime;    //
    
	public:
		tagTTVAct()
		{
			memset( this, 0, sizeof(struct tagTTVAct) );
		}
		
}TTVAct;

typedef struct tagTCenDevSleepInfo
{
	BOOL   bSleepUsed;      // �Ƿ������Զ�����
	u32    wSleepWaitTime;  // �����ȴ�ʱ�� (s)     
	public:
		tagTCenDevSleepInfo()
		{
			memset( this, 0, sizeof(struct tagTCenDevSleepInfo) );
		}
}TCenDevSleepInfo;

//��������
typedef struct tagTCentreCurName
{
    s8  achCurName[MAX_CURNAME_LEN];
	public:
		tagTCentreCurName()
		{
			memset( this, 0, sizeof(struct tagTCentreCurName) );
		}
		
}TCentreCurName;

//end to add

//Add by panhaiyang�п��ĵ�����ͷ��ʩ�͵µ���������Ϣ
typedef struct tagTCentreDCamCfg
{
	EmSerialType      emSerialType;        //�ĵ���������Ӵ�������
	EmDCamPower       emDCamPowerMode;     //�ĵ�����ͷ����״̬ 
	EmDCamAFMode      emDCamAFMode;        //�ĵ�����ͷ�Զ��۽�״̬
	EmDCamWBMode      emDCamWBMode;        //�ĵ�����ͷ��ƽ��ģʽ
	EmDCamRecallNum   emDCamRecallNum;     //�ĵ�����ͷԤ��λ���ȱ��
	BOOL              bRecallPresetOne;    //�����Ƿ��Զ�����Ԥ��λ1
    
	public:
		tagTCentreDCamCfg()
		{
			memset( this, 0, sizeof(struct tagTCentreDCamCfg) );
		}
		
}TCentreDCamCfg;

typedef struct tagTCentreSchCfg
{
	EmSchGatewayType  emCenSchGateType;    //ʩ�͵���������
	EmSerialType      emSerialType;        //ʩ�͵´�������
	EmSchPower        emSchPower;          //������ϵͳ��Դ����״̬ 
	EmSchLight        emSchLight;          //�����ҵƹ��Դ����״̬
	EmSchMidLight     emSchMidLight;       //�����Ҷ��ϵƹ��Դ����״̬
    EmSchScrLight     emSchScrLight;       //�����һ������Ƶ�Դ����״̬
	u16               wSchTem;             //�����������¶�
    
	public:
		tagTCentreSchCfg()
		{
			memset( this, 0, sizeof(struct tagTCentreSchCfg) );
		}
		
}TCentreSchCfg;

//End Add

//�յ���Ϣ add by zhangapei
typedef struct tagTCentreACCfg
{
	u8                byID;          //�յ�
	EmSerialType      emSerType;
	EmCentreACPower   emACPower;     //�յ�����
	u8                bySetTemp;     //�յ��¶�
	u8				  byCurTemp;     //ʵʱ�¶�
	EmCentreACAirVol  emACAirVol;    //�·����
	EmCentreACMode    emACMode;      //�յ�ģʽ
	
	public:
		tagTCentreACCfg()
		{
			memset( this, 0, sizeof(struct tagTCentreACCfg) );
		}
}TCentreACCfg;

//end add


//����������
typedef struct tagTOprBoardResult
{
	u8					m_byBrdLayer; //������
	u8                  m_byBrdSlot;  //�����λ��
	EmTpBoardRet        m_emReason;
public:	
	tagTOprBoardResult()
	{
		memset(this, 0, sizeof(tagTOprBoardResult));
	}
}TOprBoardResult;
typedef struct tagTTPBrdPos
{
    EMBrdType	m_emBrdType;            /* �������� */
    u8			m_byBrdLayer;           /* �������ڲ�� */
    u8			m_byBrdSlot;            /* �������ڲ�λ�� */
	u32_ip		m_dwBrdIP;				/* ����IP */
public:	
	tagTTPBrdPos(){Clear();}
	
	void Clear()
	{
		memset(this, 0, sizeof(tagTTPBrdPos));
		m_byBrdLayer = (u8)TP_INVALID_INDEX;
		m_byBrdSlot = (u8)TP_INVALID_INDEX;
	}
	
	BOOL32 operator == (const tagTTPBrdPos& tBrdPos)
	{
		return ( (m_emBrdType == tBrdPos.m_emBrdType) && (m_byBrdLayer == tBrdPos.m_byBrdLayer)
			&& (m_byBrdSlot == tBrdPos.m_byBrdSlot) && (m_dwBrdIP == tBrdPos.m_dwBrdIP) );
	}
	
}TTPBrdPos;

typedef struct tagTTPBrdCfg
{
	u8			m_byBrdID;				/*����ID*/
	TTPBrdPos	m_tBrdPos;				/*����λ��*/
	
	tagTTPBrdCfg(){Clear();}
public:	
	tagTTPBrdCfg& operator = ( const tagTTPBrdCfg& tBrdCfg)
	{
		if ( &tBrdCfg == this )
		{
			return *this;
		}
		
		memcpy(this, &tBrdCfg, sizeof(tBrdCfg));
		
		return *this;
	}
	
	void Clear()
	{
		memset(this, 0, sizeof(tagTTPBrdCfg));
		m_tBrdPos.Clear();
	}
	
}TTPBrdCfg;

//����ģʽ��Ϣ
typedef struct tagTTPEqpCfg
{
	u8				m_byEqpID;			//ums���� ������mcu������ͨ���� ��������������Ҫһ��ͳһ�ķ����㷨
	EMEqpType		m_emEqpType;		// ��������
	EMEqpModleType	m_emEqpMdlType;		//����ģʽ basic*2 ���� ehance
	s8				m_szEqpAlias[MAXLEN_EQP_ALIAS];//�������
	
	u8				m_byBrdID;			//brdID
	u8              m_byBrdLayer;
	u8              m_byBrdSlot;
	//���²������APU2��
	u8				m_byAudmixNum;      //��¼������·��
	tagTTPEqpCfg(){Clear();}
	
	tagTTPEqpCfg& operator = ( const tagTTPEqpCfg& tEqpCfg)
	{
		if ( &tEqpCfg == this )
		{
			return *this;
		}
		
		memcpy(this, &tEqpCfg, sizeof(tEqpCfg));
		
		return *this;
	}
	
	void Clear()
	{
		memset(this, 0, sizeof(tagTTPEqpCfg));
	}
	
}TTPEqpCfg;

//����ģʽ����
typedef struct tagTTPMdlCfg
{
	EMEqpType		m_emEqpType;		// ��������
	EMEqpModleType	m_emEqpMdlType;		//����ģʽ basic*2 ���� ehance
	s8				m_szEqpAlias[MAXLEN_EQP_ALIAS];//�������
	u16				m_wEqpId;
	
	//���²������APU2����ģʽ
	u8				m_byAudmixNum;      //ÿ��������������·��
public:	
	tagTTPMdlCfg(){Clear();}
	
	void Clear()
	{
		memset(this, 0, sizeof(tagTTPMdlCfg));
	}
}TTPMdlCfg;

//������Ϣ
typedef struct tagTTPBrdInfo
{
	TTPBrdCfg m_tBrdCfg;  //������Ϣ
	TTPMdlCfg m_tBrdMode[TP_UMS_BRD_MAXNUM_EQP]; //����ģʽ��Ϣ
	BOOL32    m_bReg;     //�����Ƿ�ע��
	BOOL32	  m_abEqpReg[TP_UMS_BRD_MAXNUM_EQP]; //�����Ƿ�ע��
	BOOL32    m_bBrdUsed; //�����Ƿ����ʹ��
public:
	tagTTPBrdInfo(){Clear();}
	void Clear()
	{
		memset(this, 0, sizeof(tagTTPBrdInfo));	
		m_tBrdCfg.Clear();
	}
	
}TTPBrdInfo;

typedef struct tagTTPBrdMdlInfo
{
	u8			m_byLayer;
	u8			m_bySlot;
	
	u8			m_byIndex;//����������������
	TTPMdlCfg	m_atMdlCfg[TP_UMS_BRD_MAXNUM_EQP];
public:
	tagTTPBrdMdlInfo(){Clear();}
	
	void Clear()
	{
		m_byLayer = (u8)TP_INVALID_INDEX;
		m_bySlot = (u8)TP_INVALID_INDEX;
		for (u8 byIndex = 0; byIndex < TP_UMS_BRD_MAXNUM_EQP; byIndex++)
		{
			m_atMdlCfg[byIndex].Clear();
		}
	}
}TTPBrdMdlInfo;

//����ռ�����
typedef struct tagTTPBrdUsedInfo
{
	EMEqpType	m_emType;
	u16			m_wRegNum;  //ע����
	u16			m_wUsedNum; //ʹ����
public:
	tagTTPBrdUsedInfo(){Clear();}

	void Clear()
	{
		memset(this, 0, sizeof(tagTTPBrdUsedInfo));
	}
}TTPBrdUsedInfo;

//��������
typedef struct tagTTPBrdUpGrade
{
	u8 m_byLayer;
	u8 m_bySlot;
	s8 m_szFileName[TP_UPGRADE_FILENAME_LENGTH];
	tagTTPBrdUpGrade(){Clear();}
	void Clear()
	{
		m_byLayer = (u8)TP_INVALID_INDEX;
		m_bySlot = (u8)TP_INVALID_INDEX;
		memset(m_szFileName, 0, sizeof(TP_UPGRADE_FILENAME_LENGTH));
	}
}TTPBrdUpGrade;

//
typedef struct tagTTPAudPower
{
	u8 abyInput[emTPAudInDigit0];
	u32 adwOutput[TP_AUDIO_CODEC_NUM];
	tagTTPAudPower()
	{
		memset(this, 0, sizeof(tagTTPAudPower));
	}

}TTPAudPower;

typedef struct tagTTPHdAudioPort
{
	u8 abHdAudPortIn[emTPAudInEnd];
	u8 byPos;
public:
	tagTTPHdAudioPort(){ memset( this ,0 ,sizeof( struct  tagTTPHdAudioPort ) );}
	
}TTPHdAudioPort;

typedef struct tagTTPHdAudioOutPort
{
	u8 abHdAudPortOut[emTPAudOutEnd];
	u8 byPos;
public:
	tagTTPHdAudioOutPort(){ memset( this ,0 ,sizeof( struct  tagTTPHdAudioOutPort ) );}
	
}TTPHdAudioOutPort;

typedef struct tagTTPHdDualAudioPort
{
	u8 abHdAudPortIn[emTPDualAudInEnd];
	u8 byPos;
public:
	tagTTPHdDualAudioPort(){ memset( this ,0 ,sizeof( struct  tagTTPHdDualAudioPort ) );}
}TTPHdDualAudioPort;

//���������Ƶ��Ϣ
typedef struct tagTTPMPAudioInfo
{
	BOOL                 m_bIsAECEnable;//�Ƿ����û�������
	BOOL                 m_bIsAGCEnable;//�Ƿ������Զ�����
	BOOL                 m_bIsANSEnable; //�Ƿ������Զ���������
	EmTpAudioFormat      m_emAudioFormatPriorStrategy;//��Ƶ�������Ȳ���
	u8                   m_byInputVolume;//��������������������
	u8                   m_byOutputVolume;//�������������������
	EmTPLoudspeakerVal   m_emLoudspeakerVal; //����������ֵ��T2�汾��
	
	public:
		tagTTPMPAudioInfo()
		{
			memset( this, 0, sizeof(tagTTPMPAudioInfo) );
		}
}TTPMPAudioInfo;

//�������ģʽ֡��
typedef struct tagTTPVideoDisplayFrm
{
    u32 m_dw1080PFrm;
    u32 m_dw1080IFrm;
    u32 m_dwVGAFrm;
    u32 m_dw720PFrm;
    u32 m_dwSDFrm;
public:
	tagTTPVideoDisplayFrm()
	{
		memset( this, 0, sizeof( struct tagTTPVideoDisplayFrm ) );
    }
}TTPVideoDisplayFrm, *PTTPVideoDisplayFrm;

/************************************************************************/
/*��Ƶ��������Ϣ���ݽṹ����                                            */
/************************************************************************/
typedef struct tagTTPVideoParam 
{
    BOOL  bUseFixedFrame;    //ʹ�ù̶�֡ 
    u8 byFrameRate;	///֡��
    EmTPFrameUnitType  emFrameUnit;	//֡�ʵ�λ
    u8 byQualMaxValue;	//��С��������
    u8 byQualMinValue;	//�����������
    u16 wIKeyRate;	//�ؼ�֡���
    EmTpEncodeMode emEncodeMode;     //���뷽ʽ
    EmTpLostPackageRestore emRestoreType; //�����ָ���ʽ
    u16 wH264IKeyRate;		//H264�ؼ�֡���
    u8  byH264QualMaxValue;	//H264�����������
    u8  byH264QualMinValue;	//H264��С��������
	//���²���ֻ����windows�²�����
	//��Ӳɼ�ͼ����
	u16	wWidth; //��Ƶ����ͼ���� ��Windows��Ч(default:640)
	u16	wHeight;//��Ƶ����ͼ��߶� ��Windows��Ч(default:480)
	EmTpMediaType   emCapType;    //�ɼ�����   (default:emMediaAV)
	EmTpPCCapFormat emPCCapFormat;//��Ƶ����֡��ʽ ��Windows��Ч(default:emCapPCFrameBMP)
	//���²�������Ը����ն�, 
	u8 by720pFrameRate; //720p�ֱ�����֡��
	u8 byVgaFrameRate;  //˫��vga��֡��
	//xjx_080612
	u8 byD1FrameRate; //D1�ֱ�����֡��
	
	//����ӳ�Ա
	u32 dwProfile;
	u32	dwAvgQpI;
	u32	dwAvgQpP;
	u16 wChanMaxBitrate; 
public:
	tagTTPVideoParam(){ memset( this ,0 ,sizeof( struct  tagTTPVideoParam ) );}	
}TTPVideoParam, *PTTPVideoParam;

//	ͼ���������
typedef struct tagTTPImageAdjustParam
{	 
	u8  wBrightness;//����  	 
	u8  wContrast;   //�Աȶ�  	
	u8  wSaturation; //ɫ�ʱ��Ͷ� 
public:
	tagTTPImageAdjustParam(){ memset( this ,0 ,sizeof( struct  tagTTPImageAdjustParam ) );}
	
}TTPImageAdjustParam, *PTTPImageAdjustParam;

//��Ƶ��Ϣ
typedef struct tagTTPVideoInfo
{
	TTPImageAdjustParam   m_tImageAdjustParam;//��Ƶͼ���������
	EmTpVideoFormat        m_emVideoFormatPriorStrategy;//��Ƶ�������Ȳ���
	EmTpVideoResolution    m_emVideoResolvePriorStrategy;//��Ƶ�ֱ������Ȳ���
	EmTPVideoStandard      m_emOutVideoStandard;//��Ƶ�����׼
	EmTPVideoStandard      m_emInVideoStandard;//��Ƶ�����׼
	EmTPVideoPort         m_emVideoSource;//��ƵԴ
	public:
		tagTTPVideoInfo(){memset(this,0,sizeof(struct tagTTPVideoInfo));}
}TTPVideoInfo, *PTTPVideoInfo;

// TsymboPoint̨��λ�ýṹ
typedef struct tagTTPSymboPoint
{
	u16 X;
	u16 Y;
public:
	tagTTPSymboPoint(){ memset( this, 0, sizeof( struct  tagTTPSymboPoint ) );}
}TTPSymboPoint;

/************************************************************************/
/*8010c����vga�������                                               */
/************************************************************************/
typedef struct tagTTPVgaOutCfg
{
	BOOL bVgaOut; //8010c�Ƿ���vga�����
	u16  wRefreshRate; //vga��ˢ����
 public:
	 tagTTPVgaOutCfg(){memset(this, 0, sizeof( struct tagTTPVgaOutCfg) );	}
	 tagTTPVgaOutCfg( BOOL bOut, u16 wRate ){ bVgaOut = bOut; wRefreshRate = wRate; }
}TTPVgaOutCfg;

// FEC������Ϣ�ṹ
typedef struct tagTTPFecInfo
{
	BOOL   m_bEnableFec;   //��Ƶ�Ƿ�ʹ��ǰ�����
	u8     m_byAlgorithm;  //����fec�㷨 0:NONE 1:RAID5 2:RAID6
	u16    m_wPackLen;     //����fec���а�����
	BOOL   m_bIntraFrame;  //�Ƿ�֡��fec
	u32    m_dwDataPackNum; //����fec��x�����ݰ�
	u32    m_dwCrcPackNum;  //����fec��y�������
public:
	tagTTPFecInfo(){ memset( this, 0, sizeof( struct tagTTPFecInfo ) ); }
}TTPFecInfo, *PTTPFecInfo;

/************************************************************************/
/* �����ش���Ϣ���ݽṹ����                                               */
/************************************************************************/
typedef struct tagTTPLostPackResend
{
	BOOL bUse;             //�Ƿ�����
	EmTPNetType emNetType;   //��������
	u8   byResendLevel;    //�ش��ȼ� 0<��,�ش�һ��> 1<��,�ش�����> 2<��,�ش�����>
	u16  wFirstTimeSpan;   //��һ���ش�����   default 40
	u16  wSecondTimeSpan;  //�ڶ����ش�����   default 80
	u16  wThirdTimeSpan;   //�������ش�����   default 160
	u16  wRejectTimeSpan;  //���ڶ�����ʱ���� default 200
	u16  wSendBufTimeSpan; //���ͻ���           default 1000
	BOOL bUseSmoothSend;   //����ƽ������
	BOOL bUseAdaptSend;  //˫����Ƶ�����Ƿ������ش�����
public:
	tagTTPLostPackResend(){ memset( this, 0, sizeof( struct  tagTTPLostPackResend ) );}
}TTPLostPackResend, *PTPTLostPackResend;

//����ʱ�Զ�������������
typedef struct tagTTPBitRateAdjust
{
	BOOL bEnable;   //�Ƿ�����
	u16  wInterval;  //ʱ����
	u16  wLostTimes; //��������
	u16  wDescRatio; //���ٱ���
	u16  wLowDescRatio; //���ٽ�������
	u16  wDelayInterval;  //�ӳ�ʱ��
public:
	tagTTPBitRateAdjust(){ memset( this ,0 ,sizeof( struct  tagTTPBitRateAdjust ) );}
}TTPBitRateAdjust,*PTTPBitRateAdjust;


typedef struct tagTTPVideoStandard
{
	EmTPVideoType     emVideoType;
	BOOL            bIsInPort;    //�Ƿ�Ϊ����˿�
	EmTPVideoStandard emStandard;
public:
	tagTTPVideoStandard(){ memset( this ,0 ,sizeof( struct  tagTTPVideoStandard ) );}	
}TTPVideoStandard ,*PTTPVideoStandard;

//��Ƶ�˿�
typedef struct tagTTPVideoPort
{
	u8 byIndex;
	EmTPMtVideoPort emTPMtVideoPort;//��Ƶ����˿�
	EmTPMtVideoOutPort emTPMtVideoOutPort; //��Ƶ����˿�
	EmTPDVIMode emTPDVIInMode;//������Ƶ����
	EmTPDVIMode emTPDVIOutMode;//�����Ƶ����
public:
	tagTTPVideoPort()
	{
		emTPDVIInMode = TP_DVI_MODE_DVI;
		emTPDVIOutMode = TP_DVI_MODE_INVALID;
		emTPMtVideoOutPort = emTPVidOutEnd;
		emTPMtVideoPort = emTPVidEnd;
	}
}TTPVideoPort;

// �ӿڲ��Խṹ
typedef struct tagTTPAutoTestMsg
{	
    // �������
    EmTPAutoTestType m_emAutoTestType;
    // ��ʼ���Ա�־λ��TRUE����ʼ���ԣ�FALSE��ֹͣ����
    BOOL m_bAutoTestStart;
    // ��Ƶ����
    EmTPVideoType m_emVideoType;
    // ��Ƶ�˿�	
	TTPVideoPort tTPVideoPort;

	TTPHdAudioPort tTPHdAudioPort;
	//˫����Ƶ
	TTPHdDualAudioPort tTPHdDualAudioPort;
	
	//��Ƶ���
	TTPHdAudioOutPort tTPHdAudioOutPort;

	u8 byIndex;
	//��������ܸ���
	u8 byMPCodecNum; 
	
public:
	tagTTPAutoTestMsg(){ memset( this ,0 ,sizeof( struct  tagTTPAutoTestMsg ) );}
}TTPAutoTestMsg;

//����������
typedef struct tagTTPEqualizer
{	
//    EmTPEqualizerRate emTPEqualizerRate; //������Ƶ�ʵ�
	s32 anEqualizerGain[EQUQLIZER_FREQUENCY_NUM]; //���������� 
	BOOL bEqualizer;  //����/�رվ�����	
	u8 byIndex;
	
public:
	tagTTPEqualizer(){ memset( this ,0 ,sizeof( struct  tagTTPEqualizer ) );}
}TTPEqualizer;

//���л�����
typedef struct tagTTPPIPMod
{	
    EmTPPIPMode emTPPIPMode;
	u8 byIndex;
	
public:
	tagTTPPIPMod()
	{
		Clear();		
	}

	void Clear()
	{
		byIndex = emEndMPCodec;
		emTPPIPMode = TP_VIDEO_PIPMODE_IDLE;
	}

}TTPPIPMod;


typedef struct tagTTPLostFrameRate
{
	u8 byLostFrameRate;//������
	TTpCodecComponent tTpCodc;
	BOOL bvalid;//�Ƿ���Ч
public:
	tagTTPLostFrameRate()
	{
		memset( this ,0 ,sizeof( struct  tagTTPLostFrameRate ) );
		bvalid = FALSE;
	}
}TTPLostFrameRate;


typedef struct tagTTPVideoRecv
{
	u8  abyVEncRecv[emEndMPCodec]; //��������û����ƵԴ����
	u8  abyVDecRecv[emEndMPCodec]; 

public:
	tagTTPVideoRecv()
	{
		memset( this ,0 ,sizeof( struct  tagTTPVideoRecv ) );		 
	}
}TTPVideoRecv;


typedef struct tagTTPVideoEncDecRes
{
	EmTpVideoResolution enRes;//�ֱ���
	TTpCodecComponent tTpCodc;
	BOOL bvalid;//�Ƿ���Ч
public:
	tagTTPVideoEncDecRes()
	{
		memset( this ,0 ,sizeof( struct  tagTTPVideoEncDecRes ) );
		bvalid = FALSE;
	}
}TTPVideoEncDecRes;

//�ӱ��������ȡʵ�ʷֱ���
typedef struct tagTTPVideoEncDecResPack
{
	TTPVideoEncDecRes  atVideoRes[TP_MAX_VIDEO_RES_NUM];
	u8 byNum;
	
public:
	tagTTPVideoEncDecResPack()
	{
		memset( this ,0 ,sizeof( struct  tagTTPVideoEncDecResPack ) );		 
	}
}TTPVideoEncDecResPack;


typedef struct tagTTPVideoFrameRate
{
	u16 wFrameRate;//��Ƶ֡��
	TTpCodecComponent tTpCodc;
	BOOL bvalid;//�Ƿ���Ч
public:
	tagTTPVideoFrameRate()
	{
		memset( this ,0 ,sizeof( struct  tagTTPVideoFrameRate ) );
		bvalid = FALSE;
	}
}TTPVideoFrameRate;

//�ӱ��������ȡʵ��֡��
typedef struct tagTTPVideoFrameRatePack
{
	TTPVideoFrameRate  atVideoFrameRate[TP_MAX_VIDEO_RES_NUM];
	u8 byNum;
	
public:
	tagTTPVideoFrameRatePack()
	{
		memset( this ,0 ,sizeof( struct  tagTTPVideoFrameRatePack ) );		 
	}
}TTPVideoFrameRatePack;



typedef struct tagTTPCodecPackStat
{
	TTPVideoFrameRatePack  tTPVideoFrameRatePack;//�ӱ��������ȡʵ��֡��
	TTPVideoEncDecResPack  tTPVideoEncDecResPack;//�ӱ��������ȡʵ�ʷֱ���
	TTPVideoRecv           tTPVideoRecv;  //��������û����ƵԴ����
	TTPAudPower            tTPAudPower; //��Ƶ����
	
public:
	tagTTPCodecPackStat()
	{
		memset( this ,0 ,sizeof( struct  tagTTPCodecPackStat ) );		 
	}
}TTPCodecPackStat;


typedef struct tagTTPCnDsData
{
	TTPTransAddr m_tRcvFromAddr;
	TTPTransAddr m_tSndToAddr;
	TTPTransAddr m_tMapedAddr;

	void clear()
	{
		memset(this, 0, sizeof(tagTTPCnDsData));
	}
	tagTTPCnDsData()
	{
		clear();
	}
	tagTTPCnDsData& operator = (const tagTTPCnDsData& tRhs)
	{
		if (this == &tRhs)
		{
			return *this;
		}
		this->m_tRcvFromAddr = tRhs.m_tRcvFromAddr;
		this->m_tSndToAddr = tRhs.m_tSndToAddr;
		this->m_tMapedAddr = tRhs.m_tMapedAddr;
		return *this;
	}
	BOOL operator == (const tagTTPCnDsData& tRhs)
	{
		if ( this->m_tSndToAddr.m_dwIP == tRhs.m_tSndToAddr.m_dwIP
			&&this->m_tRcvFromAddr.m_dwIP == tRhs.m_tRcvFromAddr.m_dwIP
			&&this->m_tSndToAddr.m_wPort == tRhs.m_tSndToAddr.m_wPort
			&&this->m_tRcvFromAddr.m_wPort == tRhs.m_tRcvFromAddr.m_wPort)
		{
			return TRUE;
		}
		return FALSE;
	}
}TTPCnDsData;

typedef struct tagTTPCnNetBufPara
{
	TTPTransAddr m_wSndAddr;			//����RTP�����ն˺ͷ���RTCP�����Ͷ˵ķ��Ͷ˿�
	TTPTransAddr m_tRcvRtpAddr;			//netbuf����RTP�Ķ˿�
	TTPTransAddr m_tRcvRtcpAddr;		//netbuf����RTCP�Ķ˿�
	TTPTransAddr m_tRmtRtcpAddr;		//netbuf����RTCP��Զ�˶˿�
	TTPTransAddr m_tRmtRtpAddr;			//��netbuf����rtp����Զ�˶˿�
	
	u32	 m_Handle;
	
	tagTTPCnNetBufPara()
	{
		memset(this, 0, sizeof(tagTTPCnNetBufPara));
	}
}TTPCnNetBufPara;
//�ش��趨
typedef struct tagTTPCnRSParam
{
    u16  m_wFirstTimeSpan;	 //��һ���ش�����(ms)
	u16  m_wSecondTimeSpan;  //�ڶ����ش�����(ms)
	u16  m_wThirdTimeSpan;   //�������ش�����(ms)
	u16  m_wRejectTimeSpan;  //���ڶ�����ʱ����(ms)
	
	tagTTPCnRSParam()
	{
		m_wFirstTimeSpan = 40;
		m_wSecondTimeSpan = 80;
		m_wThirdTimeSpan = 120;
		m_wRejectTimeSpan = 2000;
	}
}TTPCnRSParam;



typedef struct tagTTPAllConfCnsInfo
{
	TCnsInfo m_tCnsInfo[TP_CONF_MAX_CNSNUM];     //����ӦEPID�Ŵ洢��������ұ������
	u16 m_wNum;     //��Ч����
	
	tagTTPAllConfCnsInfo()
	{
		Clear();
	}
	
	void Clear()
	{
		for(u16 wIndex = 0; wIndex < TP_CONF_MAX_CNSNUM; ++wIndex)
		{
			m_tCnsInfo[wIndex].Clear();
		}
		
		m_wNum = 0;
	}
	
	//UMS���ƣ�ADD��UPDATE������
	BOOL Add(TCnsInfo &tCnsInfo)
	{
		if( tCnsInfo.m_wEpID>=TP_CONF_MAX_CNSNUM )
		{
			return FALSE;
		}
		if( TP_INVALID_INDEX == m_tCnsInfo[tCnsInfo.m_wEpID].m_wEpID )
		{
			++m_wNum;
		}
		memcpy(&m_tCnsInfo[tCnsInfo.m_wEpID], &tCnsInfo, sizeof(TCnsInfo));

		return TRUE;
	}
	
	BOOL Update(TCnsInfo &tCnsInfo)
	{
		if( tCnsInfo.m_wEpID>=TP_CONF_MAX_CNSNUM )
		{
			return FALSE;
		}
		if( TP_INVALID_INDEX == m_tCnsInfo[tCnsInfo.m_wEpID].m_wEpID )
		{
			++m_wNum;
		}
		memcpy(&m_tCnsInfo[tCnsInfo.m_wEpID], &tCnsInfo, sizeof(TCnsInfo));

		return TRUE;
	}
	
	BOOL Del(TCnsInfo &tCnsInfo)
	{
		if(TP_INVALID_INDEX == m_tCnsInfo[tCnsInfo.m_wEpID].m_wEpID||tCnsInfo.m_wEpID>=TP_CONF_MAX_CNSNUM)
		{
			return FALSE;
		}
		else
		{
			m_tCnsInfo[tCnsInfo.m_wEpID].Clear();
			--m_wNum;
			return TRUE;
		}
	}

	BOOL UpdateOffline(TCnsInfo &tCnsInfo)
	{
		u32 dwIndex = 0;
		for (dwIndex = 0; dwIndex < TP_CONF_MAX_CNSNUM; dwIndex ++)
		{
			if ( m_tCnsInfo[dwIndex] == tCnsInfo)
			{
				m_tCnsInfo[dwIndex].m_bOnline = FALSE;
				return TRUE;
			}
		}
		return FALSE;
	}
}TTPAllConfCnsInfo, *PTTPAllConfCnsInfo;

typedef struct tagTCnDsType
{
	u32  dwHandle;
	u16  wDsType;
	u16  wSubDsType;
}TCnDsType;


//�������ĵ�ַ---huzilong
typedef struct tagTTPCnMixAddr
{
	TTPMediaTransAddr m_tRcv;		//���յ�ַ
	TTPMediaTransAddr m_tSnd;		//���͵�ַ(N-1)ģʽ��CNS��ʱ����

	tagTTPCnMixAddr()
	{
		memset( this, 0, sizeof( tagTTPCnMixAddr ) );
	}
}TTPCnMixAddr;





//����ͨ���ṹ��---huzilong
typedef struct tagTTPCnMixChan
{
	u16				m_wIndex;			//�����е�����
	
	TTPCnMixAddr		m_tMixAddr;			//�������ĵ�ַ
	
	tagTTPCnMixChan()
	{
		memset( this, 0, sizeof( tagTTPCnMixChan ) );
		m_wIndex = INVALID_MIX_INDEX;
	}
	
}TTPCnMixChan;

//����������----huzilong
typedef struct tagTTPCnMixParam
{

	u16             m_wCurSpeaker;                      //������������ǰ�ķ�����ͨ����
	TTPCnMixChan		m_atAudMix[TP_CONF_MAX_AUDMIXNUM];	//�����б�,����˫����4·
	
	TTPTransAddr	m_tNSndRtpAddr;			//Nģʽ�»������ķ���RTP��ַ
	TTPTransAddr	m_tNSndMixBackRtcpAddr;	//Nģʽ��������BACKRTCP��ַ
	
	TTPTransAddr	m_tNRcvRtpAddr;			//����NģʽRTP��ַ
	TTPTransAddr	m_tNRcvBackRtcpAddr;	//����NģʽRTCP��ַ
	
	tagTTPCnMixParam()
	{
		memset( this, 0, sizeof( tagTTPCnMixParam ) );
		m_wCurSpeaker = INVALID_MIX_INDEX;
	}

}TTPCnMixParam;

typedef struct tagTTPNetAddress
{
    u32   dwIp;     //Ip��ַ(������) 
	u16    wPort;    //�˿ں�(������) 
}TTPNetAddress;

//����ͨ��
typedef struct tagTTPMixerChannelParam
{    
    TTPNetAddress m_tSrcNetAddr;     //ͨ��Դ��ַ(���ն���)
    //ͨ��ԴRTCP��ַ����ͨ��Դ��ַ�Ķ˿ڼ�һ(���ն���)
    TTPNetAddress m_tRtcpBackAddr;   //ͨ��RTCP������ַ(���ն���)
	TTPNetAddress m_tRtcpLocalAddr;
    TTPNetAddress m_tLocalNetAddr;   //ͨ�����ص�ַ(���Ͷ���)
    //ͨ������RTCP��ַ����ͨ�����ص�ַ�Ķ˿ڼ�һ(���Ͷ���)
    TTPNetAddress m_tLocalNetRtcpAddr;//���ط���
    TTPNetAddress m_tDstNetAddr;     //ͨ��Ŀ�ĵ�ַ(���Ͷ���)
}TTPMixerChannelParam;

// ��������
// typedef struct tagTTPSleepInfo
// {
// 	BOOL        m_bIsSleepEnable;//�Ƿ��������
// 	u32         m_dwSleepTimes;//����ʱ��
// public:
// 	tagTTPSleepInfo(){memset(this,0,sizeof(tagTTPSleepInfo));}
// }TTPSleepInfo,*PTTPSleepInfo;

//���з���������
typedef struct tagTTPCallSerInfo
{
	u32_ip		dwCallServiceIP; //���з�����IP��ַ

	public:
	tagTTPCallSerInfo()
	{ 
		memset( this ,0 ,sizeof( struct  tagTTPCallSerInfo ) );
	}

}TTPCallSerInfo;

//ͼ�����Ҳñ�
typedef struct tagTTPVidSrcCutLines
{
	u32 dwLCutLine; 
	u32 dwRCutline;
	u8  byPos;
	public:
		tagTTPVidSrcCutLines(){ memset( this ,0 ,sizeof( struct  tagTTPVidSrcCutLines ) );}
		
}TTPVidSrcCutLines;

typedef struct tagTVcrCfg
{
	s8		m_achName[MAX_VTR_NAME_LENGTH];  //VTR����
	u8		m_byEqpID;	//���
	u32_ip	m_dwIP;		//IP

	tagTVcrCfg()
	{
		Clear();
	}

	tagTVcrCfg& operator=(const tagTVcrCfg& tCfg)
	{
		if (this == &tCfg)
		{
			return *this;
		}

		memcpy(m_achName, tCfg.m_achName, MAX_VTR_NAME_LENGTH);
		m_byEqpID = tCfg.m_byEqpID;
		m_dwIP = tCfg.m_dwIP;

		return *this;
	}

	void Clear()
	{
		memset(m_achName, 0, MAX_VTR_NAME_LENGTH);
		m_byEqpID = 0;
		m_dwIP = 0;
	}

}TVcrCfg;

typedef struct tagTAdjustFrameRate
{
	u16  m_wEpID;
	u16	 m_wFrameRate;
	tagTAdjustFrameRate()
	{
		m_wEpID = TP_INVALID_INDEX;
		m_wFrameRate = 0;
	}
}TAdjustFrameRate;

typedef struct tagTAdjustVidRes
{
	u16  m_wEpID;
	u32	 m_dwVidRes;
	tagTAdjustVidRes()
	{
		m_wEpID = TP_INVALID_INDEX;
		m_dwVidRes = 0;
	}
}TAdjustVidRes;

//���˲�״̬����λʱ�ӡ�����һά��,16��ʾVGA�ֱ���,��ʾĬ��ֵ
typedef struct tagTTPVGAInfo
{
	u32	 m_adwVGA_DF_PC[16];
	u32	m_adwVGA_DF_FS[16];
	public:
		tagTTPVGAInfo(){ memset( this, 0, sizeof(struct tagTTPVGAInfo) ); }
}TTPVGAInfo;

//Add by tanxiaodong 2013-03-15.
//̨��Logo�ṹ�嶨�壬��ý��codecwrapperdef_hd.h��ת��
typedef struct tagTTPBmpInfo
{
    u32 m_dwWidth;    //ͼƬ����Ӧ����ƵԴ��ʽ���
    u32 m_dwHeight;  //ͼƬ����Ӧ����ƵԴ��ʽ�߶�
    u8  m_achBMP[CNMP_LOGO_MAX_LENGTH]; 
    u32 m_dwBmpLen;
	public:
        tagTTPBmpInfo()
		{
			memset(this, 0, sizeof(struct tagTTPBmpInfo));
		}
}TTPBmpInfo;


typedef struct tagTTPAddLogoPos
{
    u32 m_dwXPos;
    u32 m_dwYPos;
    public:
		tagTTPAddLogoPos()
		{
			memset(this, 0, sizeof(struct tagTTPAddLogoPos));
		}
}TTPAddLogoPos;

typedef struct tagTTPTranspDColor
{
	u8 m_byRColor;          //R����
	u8 m_byGColor;          //G����
	u8 m_byBColor;          //B����	
	u8 m_byTransparency;    //͸����(0��ʾȫ͸����255��ʾ��͸����1~254��ʾ����͸��)
	public:
		tagTTPTranspDColor()
		{
			memset(this, 0, sizeof(struct tagTTPTranspDColor));
		}
}TTPTranspDColor;

typedef struct tagTTPAddLogoParam
{
    u32 m_dwXPos;
    u32 m_dwYPos;
    u32 m_dwLogoWidth;//logo��
    u32 m_dwLogoHeight;//logo��
    TTPTranspDColor m_tBackBGDColor;
    public:
		tagTTPAddLogoParam()
		{
		  memset(this, 0, sizeof(struct tagTTPAddLogoParam));
		}
}TTPAddLogoParam;

typedef struct tagTTPFullLogoParam
{
    TTPBmpInfo m_tBmpInfo[3];
    TTPAddLogoParam m_tLogoParam[3];
	public:
		tagTTPFullLogoParam()
		{
			memset( this, 0, sizeof(struct tagTTPFullLogoParam) );
		}
}TTPFullLogoParam;
//End to add.

//add by niulifu
typedef struct tagTCnProduceTestMsg
{	
	// �汾�� 
	u16  m_wVersionNum;
	// �������
	EmProducetestType  m_emProduceTestType;
	// ��ʼ���Ա�־λ��TRUE����ʼ���ԣ�FALSE��ֹͣ����
	BOOL  m_bProduceTestStart;
	// ���Խ��: 0��ʧ��; 1���ɹ���
	BOOL  m_bProduceTestReult; 
	// ����ʧ��ԭ��:1, Ӳ�����Խ��ʧ��; 2, �������ڽ���;  
	// 3, ��֧�ָ������; 4,�ն�״̬����;5, ��������汾�Ŵ���; 
	// �������ӷ�����Ϣ
	u16  m_byErrorReason;
	
	//E1 ������ַ
    u32_ip m_adwLocalIp[MT_MAX_E1UNIT_NUM];
    //E1 ping��ַ
    u32_ip m_adwDstIp[MT_MAX_E1UNIT_NUM];

	tagTCnProduceTestMsg ()
	{ 
		memset( this ,0 ,sizeof( struct  tagTCnProduceTestMsg) );
	}
}TCnProduceTestMsg, *PTCnProduceTestMsg;

typedef struct tagTRecBaseInfo
{
	s8		m_achName[MAX_VTR_NAME_LENGTH];	//����
	u32		m_dwFreeSize;	//���пռ�
	u32		m_dwTotalSize;	//�ܿռ�
	
	tagTRecBaseInfo()
	{
		Clear();
	}

	void Clear()
	{
		memset(m_achName, 0, MAX_VTR_NAME_LENGTH);
		m_dwTotalSize = 0;
		m_dwFreeSize = 0;
	}
}TRecBaseInfo;

//¼���������ļ��б�
typedef struct tagTRecFileListInfo
{	
	u8		m_byEqpID;	//�豸ID
	u16		m_wTotalSize;	//����
	u16		m_wCurSize;	//��ǰ������
	s8		m_achFileName[TP_MAX_RECORDER_PACK_NUM][TP_REC_FILE_LEN];

	tagTRecFileListInfo()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTRecFileListInfo));
	}
}TRecFileListInfo;

typedef struct tagTRecFileInfo
{
	u8	m_byEqpID;	//�豸ID
	s8	m_szFilelName[TP_REC_FILE_LEN];	//�ļ���

	tagTRecFileInfo()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTRecFileInfo));
	}
}TRecFileInfo;

//����¼����Ϣ
typedef struct tagTRecorderConfInfo
{
	TUmsVidFormat	m_tConfFormat;	//�����ʽ

	tagTRecorderConfInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_tConfFormat.Clear();
	}

}TRecorderConfInfo;

//�ն�¼����Ϣ
typedef struct tagTRecorderMTInfo
{
	u16		m_wMtID;	//�ն�ID

	tagTRecorderMTInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_wMtID = 0;
	}
}TRecorderMTInfo;

//¼�ƻ���
typedef struct tagTRecConfInfo
{
	u8				m_byEqpID;	//�豸ID
	u16				m_wConfID;	//����ID
	EmRecorderType	m_emType;	//¼������
	s8				m_achFileName[TP_REC_FILE_LEN];
	BOOL32			m_bRecDual;		//�Ƿ�¼��˫��
	TUmsVidFormat	m_tDualFormat;	//˫����ʽ

	TRecorderConfInfo	m_tConfRecInfo;	//����¼����Ϣ
	TRecorderMTInfo		m_tMtRecInfo;	//�ն�¼����Ϣ

	tagTRecConfInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_byEqpID = 0;
		m_wConfID = 0;
		m_emType = em_rec_recorder_unknow;
		m_bRecDual = FALSE;
		m_tDualFormat.Clear();
		memset(m_achFileName, 0, TP_REC_FILE_LEN);
		m_tConfRecInfo.Clear();
		m_tMtRecInfo.Clear();
	}
}TRecConfInfo;

typedef struct tagTConRecState
{
	TRecConfInfo	m_tInfo;
	EmConfRecState	m_emState;
	u32				m_dwRecTime;	//��¼��ʱ��  ��

	tagTConRecState()
	{
		Clear();
	}

	void Clear()
	{
		m_tInfo.Clear();
		m_emState = em_rec_unknow;
		m_dwRecTime = 0;
	}
}TConRecState;


typedef struct tagTRecConfRes
{
	u8		m_byEqpID;
	u16		m_wConfID;
	EmRecorderType	m_emType;	//¼������
	u16		m_wMtID;
	
	tagTRecConfRes()
	{
		Clear();
	}
	
	void Clear()
	{
		m_byEqpID = 0;
		m_wConfID = 0;
		m_emType = em_rec_recorder_unknow;
		m_wMtID = 0;
	}
}TRecConfRes;

//������Ϣ
typedef struct tagTRecPlayInfo
{
	u8				m_byEqpID;
	u16				m_wConfID;
	BOOL32			m_bPlayInDual;
	s8				m_szFileName[TP_REC_FILE_LEN];	//�ļ���

	TUmsVidFormat	m_tConfFormat;	//�����ʽ
	TUmsVidFormat	m_tDualFormat;	//˫����ʽ

	tagTRecPlayInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_byEqpID = 0;
		m_wConfID = 0;
		m_bPlayInDual = FALSE;
		memset(m_szFileName, 0, TP_REC_FILE_LEN);
	}
}TRecPlayInfo;

//�ı����״̬
typedef struct tagTPlayStatusMdyInfo
{
	u8		m_byEqpID;
	u16		m_wConfID;

	tagTPlayStatusMdyInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_byEqpID = 0;
		m_wConfID = 0;
	}
}TPlayStatusMdyInfo;

typedef struct tagTConfPlayStatus
{
	EmConfRecState	m_emState;
	TRecPlayInfo	m_tInfo;
	u32				m_dwTotalTime;	//�ܷ���ʱ��
	u32				m_dwCurTime;	//��ǰ�ѷ���ʱ��
	
	tagTConfPlayStatus()
	{
		Clear();
	}
	
	void Clear()
	{
		m_emState = em_rec_unknow;
		m_dwTotalTime = 0;
		m_dwCurTime = 0;
		m_tInfo.Clear();
	}
	
}TConfPlayStatus;

typedef struct tagTTPUpgradeSer
{
	u32_ip dwSerIP;
public:
	tagTTPUpgradeSer()
	{ 
		memset(this, 0, sizeof(struct tagTTPUpgradeSer)); 
	}
}TTPUpgradeSer;

typedef struct tagTTPSnapInfo
{
	u8  byPos;
	s8  achSnapName[MT_MAX_FULLFILENAME_LEN];
	BOOL bShow;  //�Ƿ���ʾ��̬ͼƬ
public:
	tagTTPSnapInfo()
	{ 
		memset(this, 0, sizeof(struct tagTTPSnapInfo)); 
	}
}TTPSnapInfo;

//��·�Ի���Ϣ
typedef struct tagTTPSingleLoopInfo
{
	EmTpMediaType emMediaType;//ý������
	BOOL bLoop;//�Ի�
	u8  byPos;
public:
	tagTTPSingleLoopInfo(){Clear();}
	
	void Clear()
	{
		emMediaType = emTPMediaAV;
		bLoop = FALSE;
		byPos = emEndMPCodec;
	}
	
}TTPSingleLoopInfo;

//�Ի���Ϣ
typedef struct tagTTPAllLoopInfo
{
	u8  byPos;
	TTPSingleLoopInfo tSingleLoopInfo[MEDIA_NUM];	
public:
	tagTTPAllLoopInfo(){Clear();}
	
	void Clear()
	{
		byPos = emEndMPCodec;
		tSingleLoopInfo[0].Clear();
		tSingleLoopInfo[1].Clear();
	}
}TTPAllLoopInfo;

typedef struct tagTTPMtTerminal
{
	u32_ip m_dwIp;
	TTPAlias m_atAlias[MAX_MT_ALIAS_NUM];
	EmTPEndpointType m_emType;

	tagTTPMtTerminal()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTTPMtTerminal));
	}

	tagTTPMtTerminal& operator=(const tagTTPMtTerminal& tInfo)
	{
		if (this == &tInfo)
		{
			return *this;
		}

		m_dwIp = tInfo.m_dwIp;
		for (u16 wIndex = 0; wIndex < MAX_MT_ALIAS_NUM; ++wIndex)
		{
			m_atAlias[wIndex] = tInfo.m_atAlias[wIndex];
		}
		m_emType = tInfo.m_emType;

		return *this;
	}
}TTPMtTerminal;

typedef struct tagTTPMtOnLineList
{
	u16 m_wListNum;
	TTPMtTerminal m_atTerminal[MAX_MT_ONLINE_LIST_NUM];
	BOOL32 m_bIsEnd;

	u32_ip	m_dwIP;	//MCU ʹ��

	tagTTPMtOnLineList()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTTPMtOnLineList));
	}
}TTPMtOnLineList;

typedef struct tagTTPMtRegInfo
{
	u16	m_wListNum;
	TTPMtTerminal m_atTerminal[MAX_MT_ONLINE_LIST_NUM];
	BOOL32 m_bIsEnd;

	tagTTPMtRegInfo()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTTPMtRegInfo));
	}

	tagTTPMtRegInfo& operator=(const tagTTPMtRegInfo& tInfo)
	{
		if (this == &tInfo)
		{
			return *this;
		}

		this->m_wListNum = tInfo.m_wListNum;
		this->m_bIsEnd = tInfo.m_bIsEnd;
		for (u16 wIndex = 0; wIndex < tInfo.m_wListNum; ++wIndex)
		{
			this->m_atTerminal[wIndex] = tInfo.m_atTerminal[wIndex];
		}

		return *this;
	}

}TTPMtRegInfo;

typedef struct tagTTPMcuRegInfo
{
	u16	m_wListNum;
	TTPAlias m_atAlias[MAX_MT_ALIAS_NUM];
	BOOL32 m_bIsEnd;
	u32_ip	m_dwIP;

	tagTTPMcuRegInfo()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTTPMcuRegInfo));
	}

	tagTTPMcuRegInfo& operator=(const tagTTPMcuRegInfo& tInfo)
	{
		if (this == &tInfo)
		{
			return *this;
		}

		this->m_wListNum = tInfo.m_wListNum;
		this->m_dwIP = tInfo.m_dwIP;
		this->m_bIsEnd = tInfo.m_bIsEnd;
		for (u16 wIndex = 0; wIndex < tInfo.m_wListNum; ++wIndex)
		{
			this->m_atAlias[wIndex] = tInfo.m_atAlias[wIndex];
		}

		return *this;
	}

}TTPMcuRegInfo;

typedef struct tagTRegPackInfoEx
{
	TTPSipRegPackInfo	m_tPackInfo;
	EmGetRegInfoType	m_emType;
	EmTPEndpointType	m_emEndpointType;

	tagTRegPackInfoEx()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTRegPackInfoEx));
	}
}TRegPackInfoEx;

typedef struct tagTUmsRegInfoEx
{
	u16					m_wAliasNum;
	TTPAlias			m_atAlias[TP_REGNAME_SIZE];					//��ʱ��Ϊ���ֵΪ64������Ϊһ������
	TTPTransAddr		m_atContactAddr[TP_MAX_NUM_CONTACT_ADDR];	//ע���ַ
	u32					m_dwExpires;//��ʱʱ��,��λ��
	EmTPEndpointType	m_emEndpointType;    
	u32_ip				m_locolIP;                         
	s8					m_softversion[TP_MAX_VERSION_LEN+1];  
	s8					m_compileTime[TP_MAX_VERSION_LEN+1];  

	tagTUmsRegInfoEx()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTUmsRegInfoEx));
	}

	tagTUmsRegInfoEx& operator=(const tagTUmsRegInfoEx& tInfo)
	{
		if (this == &tInfo)
		{
			return *this;
		}
		
		this->m_wAliasNum = tInfo.m_wAliasNum;
		u16 wIndex = 0;
		
		for (wIndex = 0; wIndex < tInfo.m_wAliasNum; ++wIndex)
		{
			this->m_atAlias[wIndex] = tInfo.m_atAlias[wIndex];
		}
		
		for (wIndex = 0; wIndex < TP_MAX_NUM_CONTACT_ADDR; ++wIndex)
		{
			this->m_atContactAddr[wIndex] = tInfo.m_atContactAddr[wIndex];
		}
		
		this->m_dwExpires = tInfo.m_dwExpires;
		this->m_emEndpointType = tInfo.m_emEndpointType;
		this->m_locolIP = tInfo.m_locolIP;
		memcpy(this->m_softversion, tInfo.m_softversion, TP_MAX_VERSION_LEN);
		memcpy(this->m_compileTime, tInfo.m_compileTime, TP_MAX_VERSION_LEN);
		
		return *this;
	}

}TUmsRegInfoEx;

typedef struct tagTUmsRegPackEx
{
	u16				m_wSize;
	TUmsRegInfoEx	m_atRegInfo[TP_UMS_MAX_REG_DATA];
	BOOL32			m_bIsEnd;

	tagTUmsRegPackEx()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTUmsRegPackEx));
	}

	tagTUmsRegPackEx& operator=(const tagTUmsRegPackEx& tInfo)
	{
		if (this == &tInfo)
		{
			return *this;
		}
		
		this->m_wSize = tInfo.m_wSize;
		for (u16 wIndex = 0; wIndex < tInfo.m_wSize; ++wIndex)
		{
			this->m_atRegInfo[wIndex] = tInfo.m_atRegInfo[wIndex];
		}
		this->m_bIsEnd = tInfo.m_bIsEnd;
		
		return *this;
	}

}TUmsRegPackEx;

typedef struct tagTCnsRegInfoEx
{
	u16					m_wAliasNum;
	TTPAlias			m_atAlias[TP_CNS_ALIAS_REG_NUM];
	TTPTransAddr		m_atContactAddr[TP_MAX_NUM_CONTACT_ADDR];	//ע���ַ
	u32					m_dwExpires;//��ʱʱ��,��λ��
	EmTPEndpointType	m_emEndpointType;    
	u32_ip				m_locolIP;                         
	s8					m_softversion[TP_MAX_VERSION_LEN+1];  
	s8					m_compileTime[TP_MAX_VERSION_LEN+1];  
	
	tagTCnsRegInfoEx()
	{
		Clear();
	}
	
	void Clear()
	{
		memset(this, 0, sizeof(tagTCnsRegInfoEx));
	}

	tagTCnsRegInfoEx& operator=(const tagTCnsRegInfoEx& tInfo)
	{
		if (this == &tInfo)
		{
			return *this;
		}
		
		this->m_wAliasNum = tInfo.m_wAliasNum;
		u16 wIndex = 0;
		
		for (wIndex = 0; wIndex < tInfo.m_wAliasNum; ++wIndex)
		{
			this->m_atAlias[wIndex] = tInfo.m_atAlias[wIndex];
		}
		
		for (wIndex = 0; wIndex < TP_MAX_NUM_CONTACT_ADDR; ++wIndex)
		{
			this->m_atContactAddr[wIndex] = tInfo.m_atContactAddr[wIndex];
		}
		
		this->m_dwExpires = tInfo.m_dwExpires;
		this->m_emEndpointType = tInfo.m_emEndpointType;
		this->m_locolIP = tInfo.m_locolIP;
		memcpy(this->m_softversion, tInfo.m_softversion, TP_MAX_VERSION_LEN);
		memcpy(this->m_compileTime, tInfo.m_compileTime, TP_MAX_VERSION_LEN);
		
		return *this;
	}
	
}TCnsRegInfoEx;

typedef struct tagTCnsRegPackEx
{
	u16				m_wSize;
	TCnsRegInfoEx	m_atRegInfo[TP_CNS_MAX_REG_DATA];
	BOOL32			m_bIsEnd;
	
	tagTCnsRegPackEx()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTCnsRegPackEx));
	}

	tagTCnsRegPackEx& operator=(const tagTCnsRegPackEx& tInfo)
	{
		if (this == &tInfo)
		{
			return *this;
		}
		
		this->m_wSize = tInfo.m_wSize;
		this->m_bIsEnd = tInfo.m_bIsEnd;
		for (u16 wIndex = 0; wIndex < tInfo.m_wSize; ++wIndex)
		{
			this->m_atRegInfo[wIndex] = tInfo.m_atRegInfo[wIndex];
		}
		
		return *this;
	}

}TCnsRegPackEx;

//��Ƶ����ģʽ
typedef struct tagTTPAudPlayMode
{
	u8 abChnID[emEndMPCodec];
	tagTTPAudPlayMode()
	{ 
		memset(this, 0, sizeof(struct tagTTPAudPlayMode)); 
	}
	
}TTPAudPlayMode;


//�����T300 abc���ַ��
typedef struct tagTTPSmallPicRectInfo
{
	BOOL32 bUsrCfg;		//�Ƿ�ʹ���û����岼��
	u32 dwMergeStyle;	//��Ӧ�Ļ����� T300����A,B,C
	u32 dwPosIndex;		//��ͼ��λ��
	u32 dwScaleX;		//X������ռ���� �ٷֱ�
	u32 dwScaleY;		//Y������ռ����
	u32 dwScaleW;		//�����ռ����
	u32 dwScaleH;		//�߶���ռ����

	tagTTPSmallPicRectInfo()
	{ 
		memset(this, 0, sizeof(struct tagTTPSmallPicRectInfo)); 
	}

}TTPSmallPicRectInfo;

//¼������Ļ᳡��ʽ��Ϣ
typedef struct tagTTPRecMtFormat
{
	u16 m_wConfID;
	u16 m_wMtID;
	BOOL32 m_bValid;		//��ʶ��ȡ�᳡��ʽ��Ϣ�Ƿ�ɹ�
	TUmsVidFormat m_tVidFormat;

	tagTTPRecMtFormat()
	{
		Clear();
	}

	void Clear()
	{
		m_wConfID = 0;
		m_wMtID = 0;
		m_bValid = FALSE;
		m_tVidFormat.Clear();
	}
}TTPRecMtFormat;

typedef struct tagTTPRebootTime
{
	BOOL bReboot;//�Ƿ�����
	u8   byHour;//ʱ
	
	tagTTPRebootTime()
	{ 
		memset(this, 0, sizeof(struct tagTTPRebootTime)); 
	}
	
}TTPRebootTime;

typedef struct tagTTPVidForamt
{
	EmTpVideoQualityLevel emTpVideoQualityLevel;
	EmTpVideoResolution   emTpVideoResolution;
	u16                   wVidFrameRate;

	tagTTPVidForamt()
	{
		memset( this, 0, sizeof(struct tagTTPVidForamt) );
	}
}TTPVidForamt;

typedef struct tagTTPVidOffsetParam // ����ͼ��ƫ�� 
{
	EmTPMtVideoPort emPort; //��Ƶ�˿�
	s32 nHoff;      // �����������ƶ��������������ƶ���0���ƶ��������ķ�ΧΪ��[-15, +15]��Ĭ��ֵ��0
	s32 nVoff;      // �����������ƶ��������������ƶ���0���ƶ�����ʱ��֧�ִ�ֱ����ĵ��ڡ�
	tagTTPVidOffsetParam()
	{ 
		memset(this, 0, sizeof(struct tagTTPVidOffsetParam)); 
	}
}TTPVidOffsetParam;

typedef struct tagTTPAllVidOffsetParam // ����ͼ��ƫ�� 
{
	TTPVidOffsetParam tVidOffsetParam[emTPVidEnd];
	tagTTPAllVidOffsetParam()
	{ 
		memset(this, 0, sizeof(struct tagTTPAllVidOffsetParam)); 
	}
}TTPAllVidOffsetParam;

typedef struct tagTTPCnConfInfo
{
	TCnVideoParam    tCnVideoParam;
	EmTpAudioFormat  emTpAudioFormat;
	u16              wDualCallBit;

}TTPCnConfInfo;

typedef struct tagTTPDisplayType
{	
	EmTVInputSelect   emTPT300Type; //�ն��ź�Դ����
	EmTVInputSelect   emTPHduType; //����ǽ�ź�Դ����	

	tagTTPDisplayType()
	{
		memset(this, 0, sizeof(struct tagTTPDisplayType));
	}

}TTPDisplayType;

//for umc
typedef struct tagTChairSingleStreenInfo
{
	EMScreenLooked emScreenInfo;   //��Ļ״̬
	u16  wEpId;  //��Ļ�����᳡id(ѡ��״̬ʱ�����)
	
	tagTChairSingleStreenInfo()
	{
		Clear();
	}
	
	void Clear()
	{
		memset(this, 0, sizeof(tagTChairSingleStreenInfo));
	}
	
}TChairSingleStreenInfo;


//ѡ�����
typedef struct tagTChanViewRes
{
    EmTPViewResult	 m_emRes;
	TTPAlias		 m_tAlias;
	tagTChanViewRes()
	{
		memset(this, 0, sizeof(tagTChanViewRes));
	}
}TChanViewRes;

//for umc
typedef struct tagTChairStreenInfo
{
	TConfEpID tConfID;
	u16 wStreenNum;  //��Ļ����
	TChairSingleStreenInfo  tChairStreenInfo[TP_MAX_STREAMNUM];  
	
	tagTChairStreenInfo()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTChairStreenInfo));
	}

}TChairStreenInfo;

//moon add
//������Ϣ���ݽṹ
typedef struct tagTTPEthnetInfo
{
    BOOL bEnable;
    u32_ip  dwIP;          //IP
    u32_ip  dwMask;        //��������
    u32_ip  dwGateWay;   //����
public:
	tagTTPEthnetInfo(){ memset( this ,0 ,sizeof( tagTTPEthnetInfo ) );}
}TTPEthnetInfo;

typedef struct tagTTPMoonCamInfo
{
	s8                 achDescription[MAX_THREECAMERA_LEN + 1];
	BOOL               bIsUsed; //Ԥ��λ���Ƿ�����
	BOOL               bIsPreUsed;//�����Ƿ����Ԥ��λ1
	u8                 byIndex;//�����ʶ��0��1��2
	u32                dwZoom; 
	EmTPMOOMMode       emFocusMode;//�۽�ģʽ
	u32                dwFocusValue;//�۽�ֵ
	EmTPMOOMMode       emExpMode;//�ع�ģʽ
	EmTPExpGain        emGain;//���� 
	EmTPSOrThShutter   emSOrThShutSpd; //�ع���ţ�60/30fps
	EmTPFOrTwShutter   emFOrTwShutSpd; //�ع���ţ�50/25fps
	EmTPAperture       emAper;//�ع��Ȧֵ
	EmTPMOOMMode       emWBMode;//��ƽ��ģʽ���ֶ����Զ�
	u32                dwRGain; //��ƽ���ֶ����棺��ɫ����
    u32                dwBGain; //��ɫB ֵ
    BOOL               bIsBLCSwitch;//���ⲹ�����أ��ء���
	u32                dwContrast; //�Աȶ�
	u32                dwSharp;   //���
	u32                dwSaturat;  //���Ͷ�
	u32                dwBright;   //����
	EmTPFpgaReduNoise  emReduNoise;//����ȼ�
	BOOL               bIsCorrect;//����У���Ƿ���

	u32                dwCorrectLevel;//[1500, 2048]��Ӧ���洫��ֵΪ[0, 548]
	u32                dwStretchRegion;//[0, 192]
	
	u32                dwHorizonCorrect;//ˮƽУ��
	u32                dwHorizonStretch;//ˮƽ����
	u32                dwVerticalCorrect;//��ֱУ��
	u32                dwVerticalStretch;//��ֱ����
    //add by youjx 2016.12.01
    EmH650Gamma        emGamma;           //gamma����
    EmTPReduNoise      em2DNoiseLevle;    //��о2D����ȼ�
    EmTPReduNoise      em3DNoiseLevle;    //��о3D����ȼ�
    u32                dwZoomPos;         //ʵ�����õ���о���zoom��ֵ
    //add end
    
	public:
		tagTTPMoonCamInfo()
		{
			memset( this, 0, sizeof(struct tagTTPMoonCamInfo) );
		}
		
}TTPMoonCamInfo;

typedef struct tagTTPCamPre
{
	u8 byIndex;//��ʶ���������
	u8 byPre;//Ԥ��λ����������0��ʼ
	BOOL bIsUsed;//�Ƿ�����ЧԤ��λ��
	s8 achachDescription[MAX_THREECAMERA_LEN + 1];//Ԥ��λ������
}TTPCamPre;

typedef struct tagTTPPreParam
{
    TTPCamPre atPreParam[MAX_CAMERA_Pre_NUM];//16��Ԥ��λ�ڴ�
}TTPPreParam;

typedef struct tagTTPOutModeInfo
{
	EmTPMOONOutMode emOutPortFormat;
	EmTPSOrThShutter emSOrThShutSpd;
	EmTPFOrTwShutter emFOrTwShutter;

	public:
		tagTTPOutModeInfo()
		{
			memset( this, 0, sizeof(struct tagTTPOutModeInfo) );
		}
}TTPOutModeInfo;

typedef struct tagTTPSnapshotInfo
{
	u8 byIndex;//��ʶ��������������հ�ťʱ����byIndex����Ϊ3��
	s8 achFileNme[ TP_MAX_FILENAME_LEN + 1];//�ļ���
	public:
		tagTTPSnapshotInfo()
		{
			memset( this, 0, sizeof(struct tagTTPSnapshotInfo) );
		}
}TTPSnapshotInfo;

typedef struct tagTTPMosaicInfo
{
    u16 m_wWidth;                     /* ��Ƶ������Ϊ��λ */
    u16 m_wHeight;                    /* ��Ƶ�ߣ�����Ϊ��λ */

	public:
		tagTTPMosaicInfo()
		{
			memset( this, 0, sizeof(struct tagTTPMosaicInfo) );
		}
}TTPMosaicInfo;

typedef struct tagTMoonSerialInfo
{
	u32   dwNo;       /* Input: 0 ~ serial_num-1 */
	u32   dwType;     /* see also: SERIAL_RS232 */
	u32   dwUsage;    /* see also: SERIAL_CONSOLE */
	u32   dwFixBaudrate; /* 0 = no limit; else fixed, such as 115200 */
	
	s8  achName[TTY_NAME_MAX_LEN]; /* name */
}TMoonSerialInfo;

/* video standard param */
typedef struct tagTMoonVidStd
{
	u32    dwWidth;      /* in pixel, 0 = no video */
	u32    dwHeight;     /* in line,  0 = no video */
	BOOL32 bProgressive; /* TRUE = progressive; FALSE = interleaved */
	u32    dwFrameRate;  /* frame rate: 0 = no video; progressive = Freq_VS;
	                                interleaved = Freq_VS/2, 60i=30P */
	u32    dwColorSpace; /* see also: VIDEO_COLORSPACE_YUV422 */
} TMoonVidStd;

typedef struct tagTTPNsfParam
{
	u32 dwNsfLevel;  /* see also: VIDNSF_OFF */
	u32 dwNsfType;   /* see also: VIDNSF_RNR */
} TTPNsfParam;

typedef struct tagTTPDistortParam
{
	u32 dwCorrectLevel;	/* fpga distortion correct level */
	u32 dwStretchRegion;/* fpga distortion correction stretch */
	u32 dwEnable;		/* 0:disable, 1:enable */
} TTPDistortParam;

typedef struct tagTMOONProduceTestMsg
{	
	// �汾�� 
	u16  m_wVersionNum;
	// �������
	EmMOONProductTestType  m_emProduceTestType;
	// ��ʼ���Ա�־λ��TRUE����ʼ���ԣ�FALSE��ֹͣ����
	BOOL  m_bProduceTestStart;
	// ���Խ��: 0��ʧ��; 1���ɹ���
	BOOL  m_bProduceTestReult; 
	// ����ʧ��ԭ��:1, Ӳ�����Խ��ʧ��; 2, �������ڽ���;  
	// 3, ��֧�ָ������; 4,�ն�״̬����;5, ��������汾�Ŵ���; 
	// �������ӷ�����Ϣ
	u16  m_byErrorReason;
	
	//E1 ������ַ
    u32_ip m_adwLocalIp[MT_MAX_E1UNIT_NUM];
    //E1 ping��ַ
    u32_ip m_adwDstIp[MT_MAX_E1UNIT_NUM];
	
	tagTMOONProduceTestMsg ()
	{ 
		memset( this ,0 ,sizeof( struct tagTMOONProduceTestMsg) );
	}
}TMOONProduceTestMsg, *PTMOONProduceTestMsg;

//add by youjx 2017.5.9
//���ڼ�����ɫһ���Եľ�������λ����Ϣ
typedef struct tagTTPMoonRectRegion
{
    u8  byIndex;         //��ʾ�ĸ���������0��1��2��3
    u32 dwXCoordinate;   //���ϽǶ���x����
    u32 dwYCoordinate;   //���ϽǶ���y����
    u32 dwLenth;         //���γ�
    u32 dwWidth;         //���ο�

    public:
        tagTTPMoonRectRegion()
        {
            memset(this, 0, sizeof(struct tagTTPMoonRectRegion));
        }
}TTPMoonRectRegion, *PTTPMoonRectRegion;

//��ɫһ����RGBϵ��
typedef struct tagTTPColorRGBCoeff
{
    u8 byIndex;                        //��ʾ���С���ͼ
    EmTPColorConsistency emColorType;  //��ʾRGB����
    u32 dwValue;                       //ϵ��ֵ

    public:
        tagTTPColorRGBCoeff()
        {
            memset(this, 0, sizeof(struct tagTTPColorRGBCoeff));
        }

}TTPColorRGBCoeff, *PTTPColorRGBCoeff;

//����У����Ϣ
typedef struct tagTTPDistortInfo
{
    u8 byIndex;                            //��ʾ���С���ͼ
    EmTPDistortPosition emDistortType;    //��ʾ����У������
    u32 dwValue;                           //����У����ֵ
    
    public:
        tagTTPDistortInfo()
        {
            memset(this, 0, sizeof(struct tagTTPDistortInfo));
        }
}TTPDistortInfo, *PTTPDistortInfo;

//����������RGB����Ϣ
typedef struct tagTMoonRectRGB
{
    u8  byIndex;
    u32 dwRed;
    u32 dwGreen;
    u32 dwBlue;

    public:
        tagTMoonRectRGB()
        {
            memset(this, 0, sizeof(struct tagTMoonRectRGB));
        }
}TMoonRectRGB, *PTMoonRectRGB;
//��ɫһ�������е�RGBϵ��
typedef struct tagTTPColorCoeff
{
    u8  byIndex;
    u32 dwRed;
    u32 dwGreen;
    u32 dwBlue;
    public:
        tagTTPColorCoeff()
        {
            memset(this, 0, sizeof(struct tagTTPColorCoeff));
        }
        
}TTPColorCoeff, *PTTPColorCoeff;
//����У�������
typedef struct tagTTPDistortPoint
{
    u32 dwX;
    u32 dwY;
    public:
        tagTTPDistortPoint()
        {
            memset(this, 0, sizeof(struct tagTTPDistortPoint));
        }
        
}TTPDistortPoint, *PTTPDistortPoint;
//����У����ת��Ϣ
typedef struct tagTTPDistortRoate
{
    u32 dwRoateAngle;
    u32 dwEnable;
    u32 dwDirection;
    public:
        tagTTPDistortRoate()
        {
            memset(this, 0, sizeof(struct tagTTPDistortRoate));
        }
        
}TTPDistortRoate, *PTTPDistortRoate;
//����У��
typedef struct tagTTPDistortCorrectInfo
{
    u32 dwWidth;
    u32 dwHeight;
    u32 dwEnable;
    TTPDistortPoint tDistortPoint[4];
    TTPDistortRoate tDistortRoate;
    public:
        tagTTPDistortCorrectInfo()
        {
            memset(this, 0, sizeof(struct tagTTPDistortCorrectInfo));
        }
        
}TTPDistortCorrectInfo, *PTTPDistortCorrectInfo;

typedef struct tagTTPAllDistortParam
{
    u8  byIndex;
    u32 dwUperLeftHorizon;       //���ϽǶ�����������
    u32 dwUperLeftVertical;      //���ϽǶ�����������
    u32 dwUperRightHorizon;      //���ϽǶ�����������
    u32 dwUperRightVertical;     //���ϽǶ�����������
    u32 dwLowerRightHorizon;     //���½Ƕ�����������
    u32 dwLowerRightVertical;    //���½Ƕ�����������
    u32 dwLowerLeftHorizon;      //���½Ƕ�����������
    u32 dwLowerLeftVertical;     //���½Ƕ�����������
    u32 dwLeftSide;              //�������
    u32 dwRightSide;             //�ұ�����
    u32 dwTopSide;               //�ϱ�����
    u32 dwBottomSide;            //�±�����
    u32 dwCenterRotate;          //������ת
    public:
        tagTTPAllDistortParam()
        {
            memset(this, 0, sizeof(struct tagTTPAllDistortParam));
        }
}TTPAllDistortParam, *PTTPAllDistortParam;
//tptool�ڶ�������������Ϣ��������ɫһ����RGBϵ��������У������������
typedef struct tagTTPSecBoundaryInfo
{
    TTPColorCoeff tColorCoeff[MAX_THREECAMERA_NUM];
    TTPMoonRectRegion tRectRegion[MOON_MAX_RECT_REGION_NUM];
    TTPAllDistortParam tAllDistortParam[MAX_THREECAMERA_NUM];
    BOOL bShowRectSwich;
    BOOL bDistortSwich;
    BOOL bColorSwitch;
    public:
        tagTTPSecBoundaryInfo()
        {
            memset(this, 0, sizeof(struct tagTTPSecBoundaryInfo));
        }
}TTPSecBoundaryInfo, *PTTPSecBoundaryInfo;
//add end
//Ԥ��λ��Ϣ
typedef struct tagTTPPreCamInfo
{
    TTPMoonCamInfo atPreCamInfo[MAX_THREECAMERA_NUM];
    //add by youjx 2017.5.23
    TTPColorCoeff atColorCoeff[MAX_THREECAMERA_NUM];
    TTPAllDistortParam atAllDistortParam[MAX_THREECAMERA_NUM];
        public:
            tagTTPPreCamInfo()
            {
                memset(this, 0, sizeof(struct tagTTPPreCamInfo));
            }
    //add end
}TTPPreCamInfo;

typedef struct tagTTPRectCoord
{
    u32 dwPosX;      /* horizontal offset base on active video, in pixel */
    u32 dwPosY;      /* vertical offset base on active video, in line */
    u32 dwWidth;      /* in pixel, 0 = no video */
    u32 dwHeight;	  /* in line, 0 = no video */
    u32 dwEnable;     /*rectangle coold right enable*/
    public:
        tagTTPRectCoord()
        {
            memset(this, 0, sizeof(struct tagTTPRectCoord));
        }
}TTPRectCoord, *PTTPRectCoord;

typedef struct tagTTPColorEn
{
    u32 dwindex;   //1:������� 2:����ͳ�� 3:ɫ��У��
    u32 dwenable;	//ʹ��
    public:
        tagTTPColorEn()
        {
            memset(this, 0, sizeof(struct tagTTPColorEn));
        }
}TTPColorEn, *PTTPColorEn;

typedef struct tagTTPMechVer
{
    u8 byIndex;
    s8 achMechHWVer[MOON_MAX_DEVICEVER_LEN];
    s8 achMechSWVer[MOON_MAX_DEVICEVER_LEN];
    public:
        tagTTPMechVer()
        {
            memset(this, 0, sizeof(struct tagTTPMechVer));
        }
}TTPMechVer, *PTTPMechVer;

typedef struct tagTTPFpgaDelay
{
	u8 byIndex;
	u32 dwDelay;
public:
	tagTTPFpgaDelay()
	{
		memset(this, 0, sizeof(struct tagTTPFpgaDelay));
	}
}TTPFpgaDelay, *PTTPFpgaDelay;
//moon end

#endif // _h_tpcommonstruct_h__