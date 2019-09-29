#ifndef MTCONFIGEX_H
#define MTCONFIGEX_H
#include "osp.h"
#include "tptype.h"
#include "tpstruct.h"

#define H323_RAS_PORT 1719
#define H323_CALL_PORT 1720
#define SIP_CALL_PORT 5060
#define DUALPRIORITY  10
//windows������Ϣ����
typedef struct tagTWDebugInfo
{
	//�ն�����
	EmMtModel m_emMTTYpe;
	//�Ƿ�ʵʱ����
	BOOL m_bIsRealTimeCodec;
	//����֡��
	u8   m_byEncodePerSecond;
	public:
		tagTWDebugInfo()
		{
			m_emMTTYpe = emUnknownMtModel;
			m_bIsRealTimeCodec = TRUE;
			m_byEncodePerSecond = 25;
		}
}TWDebugInfo,*PTWDebugInfo;

class CVideoEx
{
public:
	enum {MAX_ITERM_COUNT = 8,MAX_RATION_STEP = 4};
	typedef struct tagTVideoSettingInfo
	{
		EmVideoFormat     emVideoForamt;
		EmVideoResolution emVideoResolution;
		u16               wVideoBitRate;
		tagTVideoSettingInfo()
		{
			emVideoForamt = emVEnd;
			emVideoResolution = emVResEnd;
			wVideoBitRate = 768;
		}
	}TVideoSettingInfo,*PTVideoSettingInfo;
	typedef struct tagTVideoDisplayInfo
	{
		EmVideoFormat     emVideoForamt;
		u16               wVideoBitRateUnit;
		EmVideoResolution aemVideoResolution[MAX_RATION_STEP];
		tagTVideoDisplayInfo()
		{
			emVideoForamt = emVEnd;
			wVideoBitRateUnit = 768;
			memset(aemVideoResolution,emVResEnd,sizeof(aemVideoResolution));
		}
	}TVideoDisplayInfo,*PTVideoDisplayInfo;

    typedef struct tagTCodecItermInfo
	{
		TVideoSettingInfo tUserSetting;
		TVideoSettingInfo tEncodeSetting;
		TVideoDisplayInfo tDisplaySetting; 
	}TCodecItermInfo,*PTCodecItermInfo;
public:
	u8   GetItermCount(){return m_byCount;}
	BOOL GetDisplayIterm(u8 byIndex , TCodecItermInfo& tInfo);
protected:
	BOOL ReadFromFile();
	BOOL SaveToFile();		
protected:
	BOOL SetDisplayIterm(u8 byIndex , const TCodecItermInfo& tInfo);
	void CountIterm();
protected:
	CVideoEx(){m_byCount = 0;}
	virtual ~CVideoEx(){}
private:
    TCodecItermInfo m_atCodecInfo[MAX_ITERM_COUNT];
	u8 m_byCount;
};

class CConfigEx;
class CSerialsEx
{
	friend class CConfigEx;
private:
	BOOL m_bRS232Send;
	BOOL m_bRS422Send;
	BOOL m_bRS485Send;
	u32  m_dwRsInterval;
	u8 m_byRS232;
	u8 m_byRS422;
	u8 m_byRS485;
protected:
	CSerialsEx()
	{
		m_bRS232Send = FALSE;
		m_bRS422Send = FALSE;
		m_bRS485Send = FALSE;
		m_dwRsInterval = 2000;
		m_byRS232 = 0;
		m_byRS422 = 1;
		m_byRS485 = 2;
	}
	~CSerialsEx(){}
protected:
	BOOL ReadFromFile();
	BOOL SaveToFile();
public:
	u8 GetRs232Dypass(){return (m_byRS232 > 3) ? 0:m_byRS232;};
	u8 GetRs422Dypass(){return (m_byRS422 > 3) ? 1:m_byRS422;};
	u8 GetRs485Dypass(){return (m_byRS485 > 3) ? 2:m_byRS485;};
	u8 GetSerialDypass(EmSerialType emType)
	{
		switch(emType)
		{
		case emRS422: return GetRs422Dypass();
		case emRS232: return GetRs232Dypass();
		case emRS485: return GetRs485Dypass();
		default:
			break;
		}
		return 0;
	}
	u32 GetRSInterval(){return m_dwRsInterval;}
	BOOL IsUsed232(){return m_bRS232Send;};
	BOOL IsUsed422(){return m_bRS422Send;};
	BOOL IsUsed485(){return m_bRS485Send;};
	//huzhiding,2010-09-13
	void ShowAll(void);
};


class CNetEx: public CVideoEx
{
protected:
	CNetEx()
	{
		m_wReserveBandWidth = 256;
		m_byIncreaseRation = 50;
		m_bUsedIncrease = FALSE;
		m_wIncreaseInterval = 60;
		m_wDelayDynameter = 1;
		m_wDiagnoseVideoRation = 100;
		m_wDiagnoseVideoAddtion = 0;
	}
	virtual ~CNetEx(){}
protected:
	BOOL ReadFromFile();
	BOOL SaveToFile();	
public:
	u16  GetReserveBandWidth();
	u8   GetIncreaseRation();
	u16  GetIncreaseInterval();
	BOOL IsUsedIncrease();
	u16  GetDelayDynameter();
	u16  GetDiagnoseVideoRation();
	u16  GetDiagnoseVideoAddtion();
	
	//xjx_080131
	void ShowAll(void);
private:
	BOOL  m_bUsedIncrease;
	u16   m_wReserveBandWidth;
	u16   m_wIncreaseInterval;
	u16   m_wDelayDynameter;
	u16   m_wDiagnoseVideoRation;
	u16   m_wDiagnoseVideoAddtion;
	u8    m_byIncreaseRation;
};
class CCameraEx: public CNetEx
{
protected:
	CCameraEx(){memset(m_atCameraInfo,0,sizeof(m_atCameraInfo));}
	virtual ~CCameraEx(){}
protected:
	enum {emCameraCount = MT_MAX_CAMERA_NAME_LEN};
	BOOL ReadFromFile();
	BOOL SaveToFile();	
	BOOL SaveToFile(const TCameraCfg& tInfo , u8 byIndex);
	BOOL SetCameraInfo(const TCameraCfg*const atInfo,u16 wValSize);
	BOOL SetCameraInfo(const TCameraCfg& tInfo , u8 byIndex);
public:
	BOOL GetCameraInfo(TCameraCfg*const atInfo,u16 wBufSize);
	BOOL GetCameraInfo(TCameraCfg& tInfo,u8 byIndex);
    void ShowAll(void);
private:
	TCameraCfg m_atCameraInfo[emCameraCount];
};
class CConfigEx: public CCameraEx
{
private:
	TBitRateAdjust m_tBitRateAdjust;
	TWDebugInfo m_tWDebugInfo;
	BOOL m_bIsInited;
	BOOL m_bIsCallingOnTime;
	u16  m_wCallInterval;

	//xjx_080510, ����ʱ���Զ����е��߼�
	BOOL m_bUnlinkIsCallingOnTime;
	u16  m_wUnlinkCallInterval;

	u16 m_wH225ListenPort;
	u16 m_wMTCListenPort;
	u16 m_wRemoteControlPort;
	u16 m_wRasPort;

	BOOL m_bIsUseIRay;
	u8 m_byTRayAddr;

	//qianshufeng add 08.08.11
	u8 m_byHDPatchVer;
	
	BOOL m_bPcmtNoVidDec;
	
	BOOL m_bShowPicEnable;

	u8   m_byBitRateDecsRatio;	//ֱ�ӽ��ͱ�������	
	u8   m_byBitRateDecsRatioForIPHead; //����ipͷ��������Ϣ����Ҫ���ͱ�������,	���������  
	
	BOOL m_bUseFcNet;
	u32  m_dwFcDecRate;
	u32  m_dwManuAdjRes;
	BOOL m_bPCMTNoGkNoConf;
	
	//��Ƶ,�ſ�buf,����Ƶͬ������
	u32 m_dwStartRcvBufs;
	u32 m_dwFastRcvBufs;

	BOOL m_bUseNoVideoOsdDisplay;
	
	//�����ش�����
	u32 m_dwResendInterval;
	u32 m_dwResendRatio;

	BOOL m_bIs4CIFPlusEnable;
	u8   m_byAacChanType;
	BOOL m_bUseAA;

	//�����ȴ�ʱ��
	u32 m_dwBluewaittime;
	
	//ι��ʱ��
	u32 m_dwWatchdogTime;

	u32 m_dwFrequence;
	u32 m_dwDspDDRFrequence;
	u32 m_dwIncRatio;

	u32 m_dwDecErrCount;

	BOOL m_bNeedThreadDetect;
	BOOL m_bSpecial1080p;
	BOOL m_bDeinterlace;
	
	BOOL m_bFrameRequest;   
	u32 m_dwFrameRequestTimer;
    BOOL m_bKeyFrameQuickResponse;
	
	//Tandberg˫������һ·��h264ʱ���ڶ�·����h264����
	BOOL m_bSkipH264Cap; //[yupeifei, 2009-08-27]

	//begin with whether enable h263plus in the capset or not   added by wangxiaoyi June 11th, 2010
	BOOL m_bEnableh263Plus;
	//end with whether enable h263plus in the capset or not   added by wangxiaoyi June 11th, 2010
	
	//begin with first try when send dual stream added by wangxiaoyi Jun. 11th, 2010
	u32 m_bDualPriority;
	s8  m_achDualFormat[DUALPRIORITY];
	s8  m_achDualResolution[DUALPRIORITY];
    //end with first try when send dual stream added by wangxiaoyi Jun. 11th, 2010
	
	BOOL m_b1080pi;
	BOOL m_bShowCallStatistics;//�Ƿ��ں���ͳ��������
	BOOL m_bAdjustResRate;//�Ƿ�����֡�����ֱ��ʴ���

	u8   m_byCaptureStrategy;
	u8   m_byDecPlayCaptureStrategy;
	u8   m_bySVDecPlayCaptureStrategy;

	BOOL   m_bEnableFpsInEnc;		//�Ƿ�ʹ��ý��Fps
	u32 m_dwFirDecMaxBuf;//added by huzhiding,2010-08-28
	u32 m_dwSecDecMaxBuf;//added by huzhiding,2010-08-28
	u16 m_wMtcBoxInterval;

	BOOL m_bIgnoreSetBirateZero;
	
	//���뵭��
	BOOL m_bPlyTransOpen;
	u32 m_dwPlyClarity;
	u32 m_dwPlySpeed;
	
	u32 m_dwAecMuteCount; //Add by meifang 2012-08-16
	u32 m_dwVgaSwitchExpire; //û�������п�����ʱ���л���ʾԴʱ��mtdevice��cns�ظ���Ϣ��ʱ�� 

private:
	static CConfigEx *m_pcInstance;

protected:
	CConfigEx()
	{
		m_bIsInited = FALSE;
		m_wRasPort        = H323_RAS_PORT;
		m_wH225ListenPort = H323_CALL_PORT;
		m_wMTCListenPort = 60000;
		m_wRemoteControlPort = 60001;
		m_bIsCallingOnTime = FALSE;
		m_wCallInterval    = 1000;

		//xjx_080510, ����ʱ���غ��߼�
		m_bUnlinkIsCallingOnTime = FALSE;
		m_wUnlinkCallInterval    = 1000;

		m_bIsUseIRay = FALSE;
		m_byTRayAddr = 1;
		//qianshufeng add 08.08.11
		m_byHDPatchVer = HD_PATCH_VER_B;
		m_bPcmtNoVidDec = FALSE;
		m_bShowPicEnable = FALSE;
		m_byBitRateDecsRatio = 100; //Ĭ��100��������0	
		m_bUseFcNet = FALSE;
		m_dwFcDecRate = 30;
		//modidy by xujinxing,2007-6-5,����Զ���������
		//m_bUseFcNet = TRUE; 
		m_bPCMTNoGkNoConf = FALSE;  //pcmtû��ע��gkʱ,�޻��鹦��
		
		m_dwStartRcvBufs = 1;
		m_dwFastRcvBufs  = 5;

		m_bUseNoVideoOsdDisplay = TRUE;

		m_dwResendInterval = 1000;
	    m_dwResendRatio = 20;

		m_bIs4CIFPlusEnable = FALSE;
		m_byAacChanType = MT_MEPG4AAC_IDLE_CHAN_TYPE;
		m_bUseAA = FALSE;
		
		//���������ȴ�ʱ��
		m_dwBluewaittime = 5000;

		m_dwWatchdogTime = 60; //��λΪ��
		
		m_dwFrequence = 60;
		m_dwDspDDRFrequence = 162;
		m_dwIncRatio = 120;

		m_bNeedThreadDetect = FALSE;//�Ƿ������̼߳���
		m_bSpecial1080p = FALSE;
		m_bDeinterlace = FALSE;

		m_dwDecErrCount = 3;

		m_bSkipH264Cap = FALSE;

		m_bEnableh263Plus = FALSE;

		m_bDualPriority = FALSE;
		memset( m_achDualFormat, 0, sizeof( m_achDualFormat ) );
	    memset( m_achDualResolution, 0, sizeof( m_achDualResolution ) );

		memset(&m_tBitRateAdjust, 0, sizeof(TBitRateAdjust));

		m_b1080pi = FALSE;
		
		m_bShowCallStatistics = FALSE;
		m_bAdjustResRate = TRUE;

		m_byCaptureStrategy = 2;
		m_byDecPlayCaptureStrategy = 2;
		m_bySVDecPlayCaptureStrategy = 2;
		m_bEnableFpsInEnc = TRUE;

		m_bFrameRequest = FALSE;
		m_dwFrameRequestTimer = 3;
		m_bKeyFrameQuickResponse = FALSE;

		//following contents was added by huzhiding,2010-08-28
		m_dwFirDecMaxBuf= 2;
        m_dwSecDecMaxBuf= 2;

		m_wMtcBoxInterval = 0;

		m_bIgnoreSetBirateZero = TRUE;

		m_dwAecMuteCount = 1; //Add by meifang 2012-08-16
		m_dwVgaSwitchExpire = 500;
	}
	CConfigEx(CConfigEx&){}
protected:
	
	BOOL ReadFromFile();
	BOOL SaveToFile();
	//����H225�����˿�
	BOOL  SetH225ListenPort(u16 wPort);
	//����Ras�����˿�
	BOOL  SetRasPort(u16 wPort);
	//�����ն˼����˿�
	BOOL  SetMTCListenPort(u16 wPort);
	//����ң�������ܶ˿ڶ˿�
	BOOL  SetRemoteControlPort(u16 wPort);
public:
	virtual ~CConfigEx()
	{
		if ( m_pcInstance != NULL )
		{
			delete m_pcInstance;
			m_pcInstance = NULL;
		}
	}
public:
	static CConfigEx* GetInstance();
	u32_ip GetCnIp( );
	//��ʾ����˽����Ϣ
    void ShowAll(void);
	//��ȡH225֡���˿�
	BOOL GetH225ListenPort(u16& wPort);
	//��ȡ�ն˼����˿�
	BOOL GetMTCListenPort(u16& wPort);
	//��ȡң�������ն˿ڶ˿�
	BOOL GetRemoteControlPort(u16& wPort);
	//���õ�����Ϣ
	BOOL  SetWDebugInfo(const TWDebugInfo& tInfo);
	//��ȡ������Ϣ
	BOOL  GetWDebugInfo(TWDebugInfo& tInfo);
	//��ȡRAS�˿���Ϣ
	BOOL  GetRasPort(u16& dwPort);
	//��ȡ�����������ʵ�����
	BOOL  GetBitRateAdjust(TBitRateAdjust &tAdjust);
	//�Ƿ�ʱ����
	BOOL IsCallingOnTime();
	//��ʱ����ʱ����
	u16  GetOnTimeCallingInterval();
	
	//xjx_080510, ����ʱ���Զ����й���
	//�Ƿ�ʱ����
	BOOL IsUnlinkCallingOnTime();
	//��ʱ����ʱ����
	u16  GetUnlinkOnTimeCallingInterval();
	
	//qianshufeng add 08.08.11
	//��ȡ���岹���汾
	u8   GetHDPatchVer();

	//ruiyigen 090608
	BOOL GetPcmtNoVidDec();
	BOOL GetUseAA(){ return m_bUseAA; }

	//����ƵԴ��ʾ��̬ͼƬ
	BOOL GetShowPicEnable(BOOL &bShowPicEnable);
	
	//��ȡֱ�ӽ��ͱ������ʵı���
	BOOL GetBitRateDecsRatio(u8 &byBitRateDecsRatio);
	//��ȡ������ipͷ���������Ҫ���͵ı������ʱ���
	BOOL GetBitRateDecsRatioForIPHead( u8 &byBitRateDecsRatioForIPHead );

	//�Ƿ���������
	BOOL GetUseFcNet( BOOL &bUseFcNet );
	BOOL GetFcDecRate(u32 &dwFcDecRate );
	BOOL GetManuAdjRes(u32 &dwManuAdjRes );

    //pcmtδע��gk,û�л��鹦��
	BOOL GetPCMTNoGkNoConf( BOOL &bPCMTNoGkNoConf);
	//

	//����ͬ������
	BOOL GetAudioStartRcvBufs( u32 &dwStartRcvBufs );
	BOOL GetAudioFastRcvBufs( u32 &dwFastRcvBufs );

	//����ƵԴ�Ƿ���ʾͼ��
	BOOL GetNoVideoOsdDisplay( BOOL &bNoVideoOsdDisplay );

	//�����ش���������
	BOOL GetResendInterval( u32 &dwInterval );
	BOOL GetResendRatio( u32 &dwRatio );

	//�����ȴ�ʱ��
	BOOL GetBlueWaitTime( u32 &dwBluewaittime );

	//ι��ʱ��
	BOOL GetWatchdogTime( u32 &dwWatchdogtime );

	BOOL GetSkipH264Cap(); //[yupeifei, 2009-08-27] for Tandberg˫��

	u32  GetHDFrequence();
	u32  GetHDIncRatio();
	u32  GetDspDDRFrequence();

	u32  GetDecErrCount();

	BOOL GetbNeedThreadDetect();
	BOOL IsSpecial1080p();
	BOOL IsDeinterlace();

	BOOL IsFrameRequestLonger();
	u32  GetFrameRequestTimer();
	BOOL IsKeyFrameQuickResponse();

	BOOL GetIs4CIFPlusEnable();
	u8  GetAacChanType();

	BOOL IsUseIRay();
	u8 GetIRayAddr();

	BOOL IsEnableH263Plus();

	BOOL IsEnableDualPriority();
	void GetDualPriority( s8 *pDualFormat, s8 *pDualRes );
    BOOL Is1080pi();
	BOOL IsShowCallStatistics();
	BOOL IsAdjustResRate();

	u8 GetCaptureStrategy();
	u8 GetDecPlayCaptureStrategy();
	u8 GetSVDecPlayCaptureStrategy();
	BOOL GetEnableFpsInEnc();
	//added by huzhiding,2010-08-28
	u32 GetDecMaxBuf(u32 dwDecoderNo);

	BOOL mtSetMtcBoxInterval( u16 wInterval );
	u16 mtGetMtcBoxInterval();
	BOOL IsIgnoreSetBitrateZero();

	BOOL IsPlyTransOpen();
	u32 mtGetPlyClarity();
	u32 mtGetPlySpeed();

	u32 mtGetAecMuteCout();//Add by meifang 2012-08-16
	u32 mtGetVgaSwitchExpire(); //û�������п�����ʱ���л���ʾԴʱ��mtdevice��cns�ظ���Ϣ��ʱ�� 


public:
	CSerialsEx  m_cSerialConfig;
};

//Proxy server
class CPxySrvCfgEx
{
private:    
    //[StarInfo]
    u8        m_byStartPxy;      //�Ƿ�����pxy
    u8        m_byStartMp;       //�Ƿ�����mp
    //[LocalInfo]
    u32_ip    m_dwLocalIpAddr;   //server��ַ
    u32       m_dwLocalRasPort;  //server H323������˿�
    u32       m_dwLocalH245Port; 
    u32       m_dwLocalOspPort;  
    //clinet��server֮��������˿�
    u32       m_dwLocalRtpPort;       
    u32       m_dwLocalRtcpPort;      
    u32       m_dwLocalMediaBasePort; 
    //[GKInfo]
    u32_ip    m_dwGKIpAddr;      //GK��ַ
    u32       m_dwGKRasPort;     //GK�˿�
    //[DefaultGW]
    u32_ip    m_dwGateWay;       //���ص�ַ
	TPxyIPCfg m_atAndvancePxyCfg[MT_MAX_PXYIP_NUM]; //�����ν�������
public:
    BOOL   m_bInit;
    static CPxySrvCfgEx* GetInstance();

protected:
    CPxySrvCfgEx()
    {
        m_bInit = FALSE;
        m_byStartPxy = 1;
        m_byStartMp  = 1;
        m_dwLocalIpAddr = inet_addr("127.0.0.1");  //Ӧ�û��г�ͻ��
		m_dwGateWay   = 0;
        m_dwLocalRasPort  = 1819;
        m_dwLocalH245Port = 1820;
        m_dwLocalOspPort  = 2776;
        m_dwLocalRtpPort  = 2776;
        m_dwLocalRtcpPort = 2777;
        m_dwLocalMediaBasePort = 48000;
        m_dwGKIpAddr = inet_addr("0.0.0.0");
        m_dwGKRasPort = 1719;
		memset( &m_atAndvancePxyCfg[0], 0, sizeof(m_atAndvancePxyCfg) );
    }
public:
    BOOL ReadFromFile();
    BOOL SaveToFile();	
    BOOL SetPxySrvInfo(u32_ip dwLocalIp, u32_ip dwGkIp, u32_ip dwGateway);

	//�����ν���
	BOOL SetPxyIPCfg( u32_ip dwGKIp, TPxyIPCfg tLocalPxyCfg, TPxyIPCfg atAdvanvePxyCfg[MT_MAX_PXYIP_NUM] );
	//���ô���ı���ip, Ҳ����Ҫ�������ص�
	BOOL SetPxyLocalIPCfg(TPxyIPCfg tPxy_old, TPxyIPCfg tPxy_new );
	//GK��ip������
	BOOL SetPxyGKCfg( u32_ip dwGKIP);

	void CommonSaveToFile();
	void PxyLocalIPSave();
	void PxyIPArraySave();
};

#endif






















