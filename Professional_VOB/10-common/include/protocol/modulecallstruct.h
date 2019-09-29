#ifndef MODULECALLSTRUCT_H
#define MODULECALLSTRUCT_H

#define MAX_LEN_CALLID       32
#define MAX_LEN_CALL_ALIAS   64
#define MAX_LEN_PRODUCT_ID   128
#define MAX_LEN_VERSION_ID   128
#define MAX_AUDIO_NUM        5
#define MAX_VIDEO_NUM        5
#define MAX_TP_STREAM_NUM		3
#define MAX_ENCRYPT_KEY_LEN  128
#define MAX_LEN_EPID		 64
#define MAX_ALIAS_NUM        64
#define MAX_E164_NUM         64
#define MAX_CONFMT_NUM       192
#define MAX_TERMINALID_LEN   128
#define MAX_PASSWD_LEN       128
#define MAX_ONLINE_LIST_NUM  64

#define MAX_FLOOR_NUM  5
#define MAX_MEDIA_NUM_PER_FLOOR  5
#define MAX_MEDIA_CAP_NUM		12
#define MAX_CONF_ID_LEN	16
#define MAX_CONF_NAME_LEN 96
#define MAX_CONF_E164_LEN 16
#define MAX_PASSWORD_LEN 16
#define MAX_TERMINAL_NUM 32

#define MAX_MTCAMERA_NUM 7       // ����ͷ������ (���ն˶���MT_MAX_CAMERA_NUMͳһ)
#define MAX_CONF_AUDMIX_NUM_TP	4			//��������������
#define INVALID_INDEX_TP	0xFFFF

#ifndef DECLARE_MODULE_HANDLE
#define DECLARE_MODULE_HANDLE(name)    typedef struct { int unused; } name##__ ; \
	typedef const name##__ * name; \
typedef name*  LP##name;
#endif


DECLARE_MODULE_HANDLE(HMDLAPPCALL)
DECLARE_MODULE_HANDLE(HMDLCALL)
DECLARE_MODULE_HANDLE(HMDLAPPCHANNEL)
DECLARE_MODULE_HANDLE(HMDLCHANNEL)
DECLARE_MODULE_HANDLE(HMDLREG)
DECLARE_MODULE_HANDLE(HMDLAPPREG)
DECLARE_MODULE_HANDLE(HMDLAPPCONFID)


template < class T >
T SAFE_COPY( T &t, u8 *p )
{
	if (NULL == p) return t;
	memcpy( &t, p, sizeof( T ) );
	return t;
}


enum emModuleEndpointType
{
	emModuletypeBegin = 0,
	emModuleEndpointMcu,
	emModuleEndpointMT ,
	emModuleEndpointGk , 
	emModuleEndpointGateway,
	emModuleEndpointCNS,
	emModuleEndpointUMS,
};

enum emModuleAliasType
{
	emModuleType_aliastype,
		emModuleType_e164 = 0x1,
		emModuleType_h323ID,
		emModuleType_email,
		emModuleType_epID,
		emModuleType_GKID,
		emModuleType_partyNumber,
	emModuleType_others
};

enum emModuleIpType
{
	emModuleIPV4,
		emModuleIPV6,
};

enum emModuleCallType
{
	emModuleIPCall,
	emModuleAliasCall,
	emModuleE164Call,
};

//���йҶ�ԭ��
enum EmModuleCallDisconnectReason
{
	emModuleDisconnect_Busy = 1   ,//�Զ�æ
	emModuleDisconnect_Normal     ,//�����Ҷ�
	emModuleDisconnect_Rejected   ,//�Զ˾ܾ�
	emModuleDisconnect_Unreachable ,//�Զ˲��ɴ�
	emModuleDisconnect_Local       ,//����ԭ��
	emModuleDisconnect_unknown     ,//δ֪ԭ��

	//TP
	emModuleDisconnect_AlredayInDualStream, //����˫���У��޷���������˫��
	emModuleDisconnect_Normal_Peer,         //�Է��Ҷ�
	emModuleDisconnect_Abnormal,            //���˵��߹Ҷ�
	emModuleDisconnect_Abnormal_Peer,       //�Զ˵��߹Ҷ�
	emModuleDisconnect_MultiConfOver,       //���������
	emModuleDisconnect_ConfAlredayExit,      //�����Ѿ�����
	emModuleDisconnect_InvalidDestAddr,	//��Ч��Ŀ�ĵ�ַ

	emModuleDisconnect_CallFull   ,//���о������(���ܴ��ں��о��δ�ͷŵ�����)
};


enum EmModuleVendorID
{
	emModule_vendor_MICROSOFT_NETMEETING = 1,
		emModule_vendor_KEDA,
		emModule_vendor_HUAWEI,
		emModule_vendor_POLYCOM,
		emModule_vendor_POLYCOM_MCU,
		emModule_vendor_TANDBERG,
		emModule_vendor_RADVISION,
		emModule_vendor_VCON,
		emModule_vendor_SONY,
		emModule_vendor_VTEL,
		emModule_vendor_ZTE,
		emModule_vendor_ZTE_MCU,
		emModule_vendor_CODIAN,
		emModule_vendor_AETHRA,
		emModule_vendor_CHAORAN,
		emModule_vendor_UNKNOWN,
		emModule_vendor_END
};

enum EmModuleConnection
{
	emModuleConnectionType = 0,
	emModuleTcpConnection,
	emModuleUdpConnection,
	emModuleSCTPConnection,
	emModuleTLSConnection,
};

typedef struct tagCallIpAddr
{
	emModuleIpType m_emIpType;
	u32 m_dwIp;
	u8  m_abyIp[16];
public:
	tagCallIpAddr()
	{
		memset( this , 0 , sizeof(tagCallIpAddr) );
	}

	void SetIpAddr( u32 dwIp ) 
	{
		m_emIpType = emModuleIPV4;
		m_dwIp = dwIp;
	}
	u32 GetIpAddr()
	{
		if ( emModuleIPV4 == m_emIpType )
		{
			return m_dwIp;
		}
		else
			return 0;
	}
	void SetIpv6Addr( u8 abyIpv6[] )
	{
		if ( NULL == abyIpv6 )
		{
			return;
		}
		m_emIpType = emModuleIPV6;
		memcpy( m_abyIp , abyIpv6 , 16 );
	}

	void GetIpv6Addr( u8* pbyIpv6 )
	{
		if ( NULL == pbyIpv6 )
		{
			return;
		}
		if ( emModuleIPV6 == m_emIpType )
		{
			memcpy( pbyIpv6 , m_abyIp , 16 );
		}
		else
			return;
	}


}TCallIpAddr;

typedef struct tagCallAliasAddr
{
	u8 m_abyCallAliasAddr[MAX_LEN_CALL_ALIAS+1];
public:
	tagCallAliasAddr()
	{
		Clear();
	}

	void Clear()
	{
		memset( m_abyCallAliasAddr , 0 , sizeof(m_abyCallAliasAddr) );
	}

	void SetCallAliasAddr( u8* pbyAlias , u16 wLen )
	{
		if ( NULL == pbyAlias || 0 == wLen )
		{
			return;
		}
		strncpy( (s8*)m_abyCallAliasAddr , (s8*)pbyAlias ,  MAX_LEN_CALL_ALIAS );
	}

	void GetAliasAddr( u8* pbyAlias , u16 wLen )
	{
		if ( NULL == pbyAlias || 0 == wLen )
		{
			return;
		}
		strncpy( (s8*)pbyAlias , (s8*)m_abyCallAliasAddr, wLen ); 
	}
}TCallAliasAddr;

typedef struct tagModuleTransportAddress
{
	emModuleIpType m_emIpType;
	u32 m_dwIp;
	u8  m_abyIp[16];
	u16 m_wPort;
	
public:
	tagModuleTransportAddress()
	{
		Clear();
	}
	
	void Clear()
	{
		m_emIpType = emModuleIPV4;
		m_dwIp = 0;
		memset( m_abyIp , 0 , 16 );
		m_wPort = 0;
	}
	
	void SetIpAddr( u32 dwIp , u16 wPort ) 
	{
		m_emIpType = emModuleIPV4;
		m_dwIp = dwIp;
		m_wPort = wPort;
	}
	void GetIpAddr( u32* dwIp , u16* wpPort )
	{
		if ( NULL == dwIp && NULL == wpPort )
		{
			return;
		}
		if ( emModuleIPV4 == m_emIpType )
		{
			*dwIp = m_dwIp;
			*wpPort = m_wPort;
		}
		else
			return;
	}
	void SetIpv6Addr( u8 abyIpv6[] , u16 wPort )
	{
		if ( NULL == abyIpv6 )
		{
			return;
		}
		m_emIpType = emModuleIPV6;
		memcpy( m_abyIp , abyIpv6 , 16 );
	}
	
	void GetIpv6Addr( u8* pbyIpv6 , u16* wpPort )
	{
		if ( NULL != pbyIpv6 && NULL != wpPort )
		{
			return;
		}
		if ( emModuleIPV6 == m_emIpType )
		{
			memcpy( pbyIpv6 , m_abyIp , 16 );
		}
		return;
	}
}TModuleTransportAddress;

enum EmModuleProfileMask
{
	emModuleProfileBaseline = 64,
        emModuleProfileMain = 32,
        emModuleProfileExtend = 16,
        emModuleProfileHigh = 8
};

//��ƵЭ������
enum EmModuleVideoFormat
{
    emModuleVH261     = 0,
		emModuleVH262     = 1,
		emModuleVH263     = 2,
		emModuleVH263plus = 3,
		emModuleVH264     = 4,
		emModuleVMPEG4    = 5,
		
		emModuleVEnd		
};

//��ƵЭ������
enum EmModuleAudioFormat
{
    emModuleAG711a  = 0,
		emModuleAG711u  = 1,
		emModuleAG722   = 2,
		emModuleAG7231  = 3,
		emModuleAG728   = 4,
		emModuleAG729   = 5,
		emModuleAMP3    = 6,
		emModuleAG721   = 7,
		emModuleAG7221  = 8,
		emModuleAG719   = 9,
		emModuleAMpegAACLC =10,
		emModuleAMpegAACLD = 11,
		
		emModuleAMpegAACLCDual = 12,
		emModuleAMpegAACLDDual = 13,

		emModuleAEnd	 
};

enum EmModuleAudioSampleFreq                    //sampling frequency
{
	emModuleFs96000 = 0,
        emModuleFs88200 = 1,
        emModuleFs64000 = 2,
        emModuleFs48000 = 3,
        emModuleFs44100 = 4,
        emModuleFs32000 = 5,
        emModuleFs24000 = 6,
        emModuleFs22050 = 7,
        emModuleFs16000 = 8,
        emModuleFs12000 = 9,
        emModuleFs11025 = 10,
        emModuleFs8000  = 11
    };

enum EmModuleAudioChnlCfg
{
	emModuleChnlCust   = 0,
        emModuleChnl1      = 1,                   //������
        emModuleChnl2      = 2,                   //˫����
        emModuleChnl3      = 3,
        emModuleChnl4      = 4,
        emModuleChnl5      = 5,
        emModuleChnl5dot1  = 6,                   //5.1����
        emModuleChnl7dot1  = 7                    //7.1����
};

//�ֱ�������
enum EmModuleVideoResolution
{
    emModuleVResolutionAuto     = 0,   //�Զ�
		emModuleVSQCIF              = 1,   //SQCIF128x96
		emModuleVQCIF               = 2,   //QCIF176x144
		emModuleVCIF                = 3,   //CIF352x288
		emModuleV2CIF               = 4,   //2CIF352x576
		emModuleV4CIF               = 5,   //4CIF704x576
		emModuleV16CIF              = 6,   //16CIF1408x1152
		
		emModuleVHD480i720x480      = 7,   //480i720x480
		emModuleVHD480p720x480      = 8,   //480p720x480
		emModuleVHD576i720x576      = 9,   //576i720x576
		emModuleVHD576p720x576      = 10,  //576p720x576
		
		emModuleVHD720p1280x720     = 11,  //720p1280x720
		emModuleVHD1080i1920x1080   = 12,  //1080i1920x1080
		emModuleVHD1080p1920x1080   = 13,  //1080p1920x1080
		
		
		emModuleVGA352x240          = 14,  //352x240
		emModuleVGA704x480          = 15,  //704x480
		emModuleVGA640x480          = 16,  //VGA640x480
		emModuleVGA800x600          = 17,  //SVGA800x600
		emModuleVGA1024x768         = 18,  //XGA1024x768
		emModuleVGA1280x768         = 19,  //WXGA1280x768
		emModuleVGA1280x800         = 20,  //WXGA1280x800
		emModuleVGA1366x768         = 21,  //WXGA1366x768
		emModuleVGA1280x854         = 22,  //WSXGA1280x854
		emModuleVGA1440x900         = 23,  //WSXGA1440x900
		emModuleVGA1280x1024        = 24,  //SXGA1280x1024
		emModuleVGA1680x1050        = 25,  //SXGA+1680x1050
		emModuleVGA1600x1200        = 26,  //UXGA1600x1200
		emModuleVGA1920x1200        = 27,  //WUXGA1920x1200
		
		emModuleVResEnd ,
};

enum EmModuleConfMsgType
{
	emModuleConfMsgTypeBegin = 500,  //���Ҫ��TP����Ϣ����ͻ
		
		emModuleMultipleConference,   //NULL
		emModuleCancelMultipleConference, //NULL
		emModuleTerminalNumberAssign, //TMDLTERLABEL
		emModuleTerminalYouAreSeeing, //TMDLTERMINALINFO + BOOL32 + TYouAreSeeing
		emModuleSeenByAll,  //NULL
		emModuleCancelSeenByAll,  //NULL

		emModuleTerminalListRequest, //NULL
		emModuleTerminalListResponce, //TMDLTERLABELLIST
		emModuleTerminalIDListRequest, //NULL
		emModuleTerminalIDListResponse, //TMDLTERINFOLIST + BOOL32 + TConfCnsList

		emModuleTerminalJoinConf,  //TMDLTERMINALINFO
		emModuleterminalLeftConf,  //TMDLTERMINALINFO

		emModuleRequestTerminalID, //TMDLTERLABEL
		emModuleMcTerminalIDResponse, //TMDLTERMINALINFO

		emModuleMakeTerQuietCmd, //TMDLTERLABEL(dst) + BOOL32(����/�ر�)
		emModuleMakeTerMuteCmd, //TMDLTERLABEL(dst) + BOOL32(t����/�ر�)
		emModuleChgSecVidSendCmd, //BOOL32(����/�ر�)

		//add by yj for confMSG [20130726]
		emModulevideoFpsChangeCmd,		//u32(emModuleChannelType) + u8(֡��)


		emModulevideoFormatChangeCmd,	//���ͣ�emModuleVideoType + u8(����vccommon.h�����Ƶ��ʽ) ( ��߿���ѡ������˳��With(u32)+Height(u32) )
										//���գ�emModuleVideoType + u32 + u32 (�����նˣ������Ǳ�����ֻ���������ȷ���ֱ���)
		
										//*    +   u8  ͨ������   LOGCHL_VIDEO      (Ĭ������Ƶͨ��)
										//*    +   u8  �ֱ������� VIDEO_FORMAT_QCIF (176*144)
										//ע���µ�MCU���������¿�Ⱥ͸߶��ֶΣ��ϵ�MCUû�������ֶ�(PA������ֱ�Ӱѿ�ߴ���)
										//*    +   u32  �ֱ��ʿ�� 
										//*    +   u32  �ֱ��ʸ߶�
		
		emModuleterStatusInd,			//TModuleTerStatus ter->Mc
		emModulesetAudioVolumeCmd,		// ��������(u8) + ����(u8)
		//end [20130726]

		//added by sna for dual channel on/off [20140107]
		emModuleStartRcvDualInd, //NULL
		emModuleStopRcvDualInd, //NULL
		//added end [20140107]
};

//����ģʽ
enum EmCallModeType
{
	emModeJoin,
	emModeCreate,
	emModeInvite
};

typedef struct tagTMdlPollInfoTP
{
	BOOL bIsPoll;
	u16  wPollExpire;
	
	void Clear()
	{
		memset( this, 0, sizeof(tagTMdlPollInfoTP) );
	}
	tagTMdlPollInfoTP()
	{
		Clear();
	}
}TMdlPollInfoTP;

typedef struct tagTMdlConfAuxMixInfoTP
{
	BOOL bStart;
	u16	wConfID;
	u16 wSpeakerIndex;					//�������������
	u16	awList[MAX_CONF_AUDMIX_NUM_TP];	//����ID

	void Clear()
	{
		memset( this, 0, sizeof(tagTMdlConfAuxMixInfoTP) );
		wConfID = INVALID_INDEX_TP;
		bStart = FALSE;
	}
	tagTMdlConfAuxMixInfoTP()
	{
		Clear();
	}
}TMdlConfAuxMixInfoTP;

//����������Ϣ
typedef struct tagTMdlConfInfo
{
	s8	 achConfId[MAX_CONF_ID_LEN + 1];			// ����ID
	s8	 achConfName[MAX_CONF_NAME_LEN + 1];		// ������
	s8	 achConfNumber[MAX_CONF_E164_LEN + 1];	    // �������
	s8	 achConfPwd[MAX_PASSWORD_LEN + 1];			// ��������
	BOOL bNeedPassword;                             // �Ƿ���Ҫ����
	u16  wConfDuration;							    // �������ʱ��		
	EmModuleVideoFormat   emVideoFormat;			// ������Ƶ��ʽ(VIDEO_H261��)
	EmModuleAudioFormat   emAudioFormat;			// ������Ƶ��ʽ(AUDIO_MP3��)
	EmModuleVideoResolution  emResolution;			// ������Ƶ�ֱ���(VIDEO_CIF��)
	EmModuleProfileMask emProfile;					// ����profile
	u8 byVidMPI;					                // ����֡��
	BOOL bIsAutoVMP;								// �Ƿ��Զ�����ϳ�
	BOOL bIsMix;	    							// �Ƿ����
	EmModuleVideoFormat	emSecVideoFormat;			// ˫����ʽ
	EmModuleVideoResolution emSecVidRes;			// ˫���ֱ���
	EmModuleProfileMask emSecProfile;				// ˫��profile
	u8 bySecVidMPI;					                // ˫��֡��
	u16 wCallRate;									// ��������(kbps)
	u16	wDualCallRate;								// ˫����������(kbps)
	TMdlPollInfoTP  tPollInfo;
	TMdlConfAuxMixInfoTP tConfAudMixInfo;

public:
	tagTMdlConfInfo()
	{ 
		Clear();	
	}
	void Clear()
	{
		memset( this, 0, sizeof(tagTMdlConfInfo) );
		tPollInfo.Clear();
		tConfAudMixInfo.Clear();
	}

}TMdlConfInfo ,*PTMdlConfInfo;

//�ն˵�ַ
typedef struct tagTerminalAddress
{
	emModuleCallType	emCallType;
	s8	achAlias[MAX_LEN_CALL_ALIAS + 1];	//�ն˱�����E164��
	TModuleTransportAddress	tModuleAddress;	//�ն�IP��ַ

public:
	tagTerminalAddress()
	{
		Clear();
	}
	void Clear()
	{
		memset( this ,0 ,sizeof( tagTerminalAddress ) );
		emCallType = emModuleAliasCall;
	}
}TerminalAddress,*PTerminalAddress;

typedef struct tagModuleCallInfo
{
	u8 m_abyCallId[MAX_LEN_CALLID+1];
	
	u16 m_wBitrate;
	emModuleEndpointType m_emEndpointType;
	
	emModuleCallType m_emCallType;
	
	TModuleTransportAddress m_emCallerIp;
	TModuleTransportAddress m_emCalleeIp;
	
	TCallAliasAddr m_emCallerAlias;
	TCallAliasAddr m_emCalleeAlias;
	
	TCallAliasAddr m_emCallerE164;
	TCallAliasAddr m_emCalleeE164;
	
	u8 m_abyLocalProductId[MAX_LEN_PRODUCT_ID+1];
	u8 m_abyLocalVersionId[MAX_LEN_VERSION_ID+1];
	
	u8 m_abyPeerProductId[MAX_LEN_PRODUCT_ID+1];
	u8 m_abyPeerVersionId[MAX_LEN_VERSION_ID+1];
	
	EmModuleVendorID m_emVendorId;
	EmCallModeType   m_emCallMode;			// ��������:JOIN|CREATE|INVITE

	BOOL m_bIsInterworking;				//added by sna for interworking [20140214]
	//////////////////////////////////////////////////////////////////////////
	//���½����ڴ�������
	BOOL m_bCreateConf;		//�Ƿ��Ǵ�������
	u8 m_byTerNum;			//�����ն˸���
	TerminalAddress m_atList[MAX_TERMINAL_NUM];	//�����ն��б�
	TMdlConfInfo m_tConfInfo;			//������Ϣ
	
	BOOL m_bNatCall;	//�����Ƿ��nat
public:
	tagModuleCallInfo()
	{
		Clear();
	}
	
	void Clear()
	{
		m_emVendorId = emModule_vendor_KEDA;
		m_emEndpointType = emModuleEndpointMT;
		m_emCallType = emModuleIPCall;
		memset( m_abyLocalProductId , 0 , sizeof(m_abyLocalProductId) );
		memset( m_abyLocalVersionId , 0 , sizeof(m_abyLocalVersionId) );
		memset( m_abyPeerProductId , 0 , sizeof(m_abyPeerProductId) );
		memset( m_abyPeerVersionId , 0 , sizeof(m_abyPeerVersionId) );
		memcpy( m_abyLocalProductId, "kedacom", sizeof("kedacom") );
		memcpy( m_abyLocalVersionId, "unknown", sizeof("unknown") );
		memset( m_abyCallId , 0 , sizeof(m_abyCallId) );
		m_wBitrate = 768;
		m_emCallMode = emModeCreate;
		m_bCreateConf = FALSE;
		m_byTerNum = 0;
		m_tConfInfo.Clear();
		m_bNatCall = FALSE;
		m_bIsInterworking = FALSE;
		for ( u8 i = 0; i < MAX_TERMINAL_NUM; i++ )
		{
			m_atList[i].Clear();
		}
	}
	
}TModuleCallInfo;

//��Ƶ������
struct TVideoDescript
{
	EmModuleVideoResolution m_emRes; //�ֱ���
	u8                m_byMPI;       //֡�� 1=30 2=15 ...
	u16               m_wMaxBitrate; //֧���������
public:
	TVideoDescript()
	{
		Clear();
	}

	void Clear()
	{
		m_emRes = emModuleVResEnd;
		m_byMPI = 1;
		m_wMaxBitrate = 768;
	}
};

//ָ����Ƶ��ʽ�����б�
struct TVideoFormatCapbility
{
	u8      byNum;
	u8     m_wDynamicPayload;
	EmModuleVideoFormat m_emFormat;
	EmModuleProfileMask m_emProfile; //h264��
	TVideoDescript m_atItem[emModuleVResEnd];
	
	TVideoFormatCapbility()
	{
		Clear();
	}

	void Clear()
	{
		byNum = 0;
		m_emFormat = emModuleVEnd;
		m_wDynamicPayload = 0;
		m_emProfile = emModuleProfileBaseline;
		for ( u8 i=0; i<emModuleVResEnd; i++ )
		{
			m_atItem[i].Clear();
		}
	}
};

//��Ƶ������
struct TVideoCapbilityList
{	
	u8 m_byNum;
	TVideoFormatCapbility m_atList[emModuleVEnd];
	
	HMDLAPPCHANNEL m_hAppChan;
	TModuleTransportAddress m_tRtpAddr;
	TModuleTransportAddress m_tRtcpAddr;
	BOOL32 m_bActive;
public:
	TVideoCapbilityList()
	{
		Clear();
	}

	void Clear()
	{
		m_byNum = 0;
		m_hAppChan = NULL;

		for ( u8 i=0; i<emModuleVEnd; i++ )
		{
			m_atList[i].Clear();
		}
		m_tRtpAddr.Clear();
		m_tRtcpAddr.Clear();
		m_bActive = TRUE;
	}
};
//��Ƶ������
struct TAudioDescript
{
	EmModuleAudioFormat m_emFormat;
	u8            m_byPackTime;
	u8           m_wDynamicPayload;

	//AAC ��
	EmModuleAudioSampleFreq m_emSampleFreq;
	EmModuleAudioChnlCfg m_emChnlCfg;

	//g7231��
	u8				m_byMaxFrameNum;		//��������֡��
	BOOL			m_bSilenceSuppression;	//�Ƿ�������
public: 
	TAudioDescript()
	{
		Clear();
	}

	void Clear()
	{
		m_emFormat = emModuleAEnd;
		m_byPackTime = 20;
		m_wDynamicPayload = 0;
		m_emChnlCfg = emModuleChnl1;
		m_emSampleFreq = emModuleFs32000;
		m_byMaxFrameNum = 1;
		m_bSilenceSuppression = FALSE;
	}
};

//��Ƶ������
struct TAudioCapbilityList
{
	u8 m_byNum;
	TAudioDescript m_atItem[emModuleAEnd];

	HMDLAPPCHANNEL m_hAppChan;
	TModuleTransportAddress m_tRtpAddr;
	TModuleTransportAddress m_tRtcpAddr;
	BOOL32  m_bActive;

public:
	TAudioCapbilityList()
	{
		Clear();
	}

	void Clear()
	{
		m_hAppChan = NULL;
		m_byNum = 0;
		
		for ( u8 i=0; i<emModuleAEnd; i++ )
		{
			m_atItem[i].Clear();
		}

		m_tRtpAddr.Clear();
		m_tRtcpAddr.Clear();
		m_bActive = TRUE;
	}
};

typedef enum 
{
	emDualAttribueBegin = 0,
	emDualSendOnly = 1,
	emDualSendRecv = 2,
	emDualSendOnlyAndRecvOnly = 3,
}EmDualAttribue;

typedef struct tagDualCapList
{
	EmDualAttribue m_emDualAttribue;

	u16 m_wSndVidNum;
	u16 m_wRcvVidNum;

	u16 m_wSndAudNum;
	u16 m_wRcvAudNum; 
	
	TVideoCapbilityList m_tSndVidCap[MAX_VIDEO_NUM];
	TVideoCapbilityList m_tRcvVidCap[MAX_VIDEO_NUM];
	
	TAudioCapbilityList m_tSndAudCap[MAX_AUDIO_NUM];
	TAudioCapbilityList m_tRcvAudCap[MAX_AUDIO_NUM];
	
	void Clear()
	{
		m_emDualAttribue = emDualSendOnlyAndRecvOnly;

		u8 index = 0;
		m_wSndAudNum = 0;
		m_wRcvAudNum = 0;
		m_wSndVidNum = 0;
		m_wRcvVidNum = 0;
		for ( index=0; index<MAX_VIDEO_NUM; index++)
		{
			m_tSndVidCap[index].Clear();
		}
			
		for ( index=0; index<MAX_VIDEO_NUM; index++)
		{
			m_tRcvVidCap[index].Clear();
		}
		for ( index=0; index< MAX_AUDIO_NUM; index++)
		{
			m_tSndAudCap[index].Clear();
		}
		for ( index=0; index< MAX_AUDIO_NUM; index++)
		{
			m_tRcvAudCap[index].Clear();
		}
	}
	tagDualCapList()
	{
		Clear();
	}
	
}TDualCapList;

typedef struct tagCallCapbility
{
	u16 m_wAudioNum;
	TAudioCapbilityList m_tAudioCapList[MAX_AUDIO_NUM];     //ÿһ��ͨ��
	u16 m_wVideoNum;
	TVideoCapbilityList m_tVideoCapList[MAX_VIDEO_NUM];
	
	TVideoCapbilityList m_tDualCapList;						//��Ƶ˫��������Ĭ��Ϊ1·

	tagCallCapbility()
	{
		Clear();
	}

	void Clear()
	{
		m_wAudioNum = 0;
		m_wVideoNum = 0;

		u8 i=0;
		for ( i=0; i<MAX_AUDIO_NUM; i++)
		{
			m_tAudioCapList[i].Clear();
		}

		for ( i=0; i<MAX_VIDEO_NUM; i++)
		{
			m_tVideoCapList[i].Clear();
		}
		m_tDualCapList.Clear();
	}

}TCallCapbility;

//defined in rfc4145
typedef enum 
{
	emSetupBegin = 0,
	emActive = 1,	//The endpoint will initiate an outgoing connection.
	emPassive = 2,	//The endpoint will accept an incoming connection.
	emActpass = 3,	//The endpoint is willing to accept an incoming connection or to initiate an outgoing connection.
	emHoldconn = 4,	//The endpoint does not want the connection to be established for the time being.
}EmSetupAttr;

//defined in rfc4145
typedef enum 
{
	emConnectionBegin = 0,
	emNew = 1,
	emExisting = 2,
}EmConnectionAttr;

//defined in rfc4583
typedef enum 
{
	emFloorcontrolBegin = 0,
	emClientOnly = 1,	//The answerer will act as a floor control client. Consequently, the offerer will act as a floor control server.
	emServerOnly = 2,	//The answerer will act as a floor control server. Consequently, the offerer will act as a floor control client.
	emClientServer = 3,	//The answerer will act both as a floor control client and as a floor control server. Consequently, the offerer will also act
						//both as a floor control client and as a floor control server.
}EmFloorcontrolAttr;

typedef struct tagBfcpCapSet
{	
	u16 m_wPort;	//BFCP���ն˶˿�
	
	EmFloorcontrolAttr m_emFloorcontrolAttr;	//BFCPʵ�壨Floorcontrol���ԣ�
	EmSetupAttr m_emSetupAttr;	//BFCP������������Setup���ԣ�
	EmConnectionAttr m_emConnectionAttr;	//�������ԣ�Ĭ��new��
	
	s32 m_nConfId;	//����ID
	s32 m_nUserId;	//�û�ID
	s32 m_anFloorId[MAX_FLOOR_NUM];	//��ID
	s32 m_anFloorMedia[MAX_FLOOR_NUM][MAX_MEDIA_NUM_PER_FLOOR];	//�����ID����Ӧ��ͨ��Label

	void Clear()
	{
		m_wPort = 0;

		m_emFloorcontrolAttr = emFloorcontrolBegin;
		m_emSetupAttr = emSetupBegin;
		m_emConnectionAttr = emConnectionBegin;

		m_nConfId = -1;
		m_nUserId = -1;
		
		for ( s32 i =0; i < MAX_FLOOR_NUM; i++ )
		{
			m_anFloorId[i] = -1;
			for ( s32 j = 0; j < MAX_MEDIA_NUM_PER_FLOOR; j++ )
			{
				m_anFloorMedia[i][j] = -1;
			}
		}
	}
	
	tagBfcpCapSet()
	{
		Clear();
	}
	
}TBfcpCapSet;


//H323 Annex Q
/*   
 *   h.281 encoded in host bit order:
 *   +-------+---------+--------+---------+--------+---------+--------+---------+
 *   +   P   | R=1/L=0 |    T   | U=1/D=0 |    Z   | I=1/O=0 |    F   | I=1/O=0 |
 *   +-------+---------+--------+---------+--------+---------+--------+---------+
 */
enum emModulefeccAction
{
	emModuleactionInvalid				= 0,  
	emModuleactionStart					= 0x01,  //��ʼ
	emModuleactionContinue				= 0x02,  //����
	emModuleactionStop					= 0x03,  //ֹͣ
	emModuleactionSelectVideoSource		= 0x04,  //ѡ����ƵԴ
	emModuleactionVideoSourceSwitched	= 0x05,  //�л���ƵԴ
	emModuleactionStoreAsPreset			= 0x06,  //�洢Ԥ��λ
	emModuleactionActivatePreset		= 0x07,  //�ָ���Ԥ��λ
	emModuleactionAutoFocus				= 0x11,  //�Զ�����
};

//PTFZ codes, parameters for action Start, continue and stop.
enum emModulefeccPTFZRequest
{
	emModulerequestInvalid				= 0,
	emModulerequestPanLeft				= 0x80,	//�����ƶ�
	emModulerequestPanRight				= 0xc0,	//�����ƶ�
	emModulerequestTiltUp				= 0x30,	//�����ƶ�
	emModulerequestTiltDown				= 0x20,	//�����ƶ�
	emModulerequestFocusIn				= 0x03,	//����
	emModulerequestFocusOut				= 0x02,	//Զ��
	
	emModulerequestZoomIn				= 0x0c,	//��Ұ��С
	emModulerequestZoomOut				= 0x08,	//��Ұ���

	emModulerequestBrightnessUp			= 0x01,	//���ȼ�(nonstandard)
	emModulerequestBrightnessDown		= 0x04  //���ȼ�(nonstandard)
};

//H323 Annex Q
typedef struct
{
	u8 m_byAction;			  //start, continue, stop, video source, preset
	
	union 
	{
		u8 m_byRequest;		  //for PTFZ operations
		u8 m_bySourceNo;      //for VIDEO SOURCE operations
		u8 m_byPresetNo;      //for PRESET operations
	}arguments;
	
	u8 m_byTimeout;			  //for start action only ,unit 50ms, 0��ʾ800ms	
}TMdlFeccStruct, *PTMdlFeccStruct;

typedef struct tagFeccCapbility
{	
	TModuleTransportAddress m_tSendAddress;	//FECC���͵�ַ
	TModuleTransportAddress m_tRecvAddress;	//FECC���յ�ַ
	u16 m_wSampleRate;
	
	void Clear()
	{
		m_tSendAddress.Clear();
		m_tRecvAddress.Clear();
		m_wSampleRate = 0;
	}
	
	tagFeccCapbility()
	{
		Clear();
	}
	
}TFeccCapbility;


typedef struct tagModuleTEncryptKey
{
	u8 byLen;   //��Կ����
	u8 byKey[MAX_ENCRYPT_KEY_LEN]; //��Կ����
public:
	tagModuleTEncryptKey(){ memset( this ,0 ,sizeof( struct  tagModuleTEncryptKey ) );}	
}TModuleEncryptKey;

//��Ƶͨ������
typedef struct tagTModuleVideoChanParam
{
	EmModuleVideoFormat     m_emVideoFormat;
	EmModuleVideoResolution m_emVideoResolution;
	u16                m_wChanMaxBitrate; // ��λ Kbps
	u8                 m_byPayload;       //��̬�غ�
	TModuleEncryptKey        m_tKey;            //��tKey.byLen=0 ��ʾ������
	u8                 m_byFrameRate;          //֡��
public:
	tagTModuleVideoChanParam()
	{ 
		Clear();
	}	

	void Clear()
	{
		m_emVideoFormat = emModuleVEnd;
		m_emVideoResolution = emModuleVResEnd;
		m_wChanMaxBitrate   = 0;
		m_byPayload         = 0;
		memset( &m_tKey ,0 ,sizeof(m_tKey) );
		m_byFrameRate = 30;
	}
}TModuleVideoChanParam ,*PTModuleVideoChanParam;

//��Ƶͨ������ 
typedef struct tagTModuleAudioChanParam
{
	EmModuleAudioFormat   m_emAudioFormat;
	u8               m_byPayload;     //��̬�غ�
	TModuleEncryptKey      m_tKey;          //��tKey.byLen=0 ��ʾ������
public:
	tagTModuleAudioChanParam()
	{
		Clear();
	}

	void Clear()
	{
		m_emAudioFormat = emModuleAEnd;
		m_byPayload     = 0;
		memset( &m_tKey ,0 ,sizeof(m_tKey));
	}
}TModuleAudioChanParam;

typedef struct tagModuleVideoChannelParam
{
	TModuleVideoChanParam m_tParam;
	TModuleTransportAddress m_tRtpAddr;
	TModuleTransportAddress m_tRtcpAddr;

}TModuleVideoChannelParam;

typedef struct tagModuleAudioChannelParam
{
	TModuleVideoChannelParam m_tParam;
	TModuleTransportAddress m_tRtpAddr;
	TModuleTransportAddress m_tRtcpAddr;
	
}TModuleAudioChannelParam;

enum emChanType
{
	emModuleChanTypeBegin,
	emModuleSndAud,
	emModuleSndVid,
	emModuleRcvAud,  
	emModuleRcvVid,
};

enum emAVType
{
	emModuleTypeBegin,
	emModuleAudioType,
	emModuleVideoType,

	emModuleAudioSecondType,
	emModuleVideoSecondType,

	//data type
	emModuleH224Type,
	emModuleT120Type
};
//add by yj for conf MSG [20130726]
//���ڵ���֡��ʱ��дͨ������
//����10��ͨ��
enum emModuleChannelType
{
	emModuleChanSendAudio,
	emModuleChanSendPrimoVideo,
	emModuleChanSendSecondVideo,
	emModuleChanSendFecc,
	emModuleChanSendT120,
	
	//����ͨ��
	emModuleChanRecvAudio,
	emModuleChanRecvPrimoVideo,
	emModuleChanRecvSecondVideo,
	emModuleChanRecvFecc,
	emModuleChanRecvT120,
	
	emModuleChanTypeEnd	
};

//��Ƶ����
enum emModVideoType
{
	emModulePriomVideo = 0 ,//����Ƶ
	emModuleSecondVideo = 1//�ڶ�·��Ƶ
};

//�ն��ͺ�
enum EmModuleMtModel
{
	emModuleUnknownMtModel = 0,
	emModulePCMT  = 1 ,//�����ն�
	emModule8010      ,
	emModule8010A     ,
	emModule8010Aplus ,//8010A+
	emModule8010C     ,
	emModule8010C1    ,//8010C1
	emModuleIMT       ,
	emModule8220A     ,
	emModule8220B     ,
	emModule8220C     ,
	emModule8620A     ,
	emModuleTS6610E   ,
	emModuleTS6210    ,
	emModule8010A_2   ,
	emModule8010A_4   ,
	emModule8010A_8   ,
	emModule7210      ,
	emModule7610      ,
	emModuleTS5610    ,
	emModuleTS6610    ,
	emModule7810      ,
	emModule7910      ,
	emModule7620_A    ,
	emModule7620_B    ,
	emModule7820_A	,
	emModule7820_B	,
	emModule7920_A	,
	emModule7920_B	,
	emModuleKDV1000   ,
	emModule7921_L    ,
	emModule7921_H    ,
	emModuleH600_LB    ,
	emModuleH600_B    ,
	emModuleH600_C    ,
	emModuleH700_A    ,
	emModuleH700_B    ,
	emModuleH700_C    ,
	emModuleH900_A    ,
	emModuleH900_B    ,
	emModuleH900_C    ,
	emModuleH600_LC   ,
	emModuleH800_A    ,
	emModuleH800_B    ,
	emModuleH800_C    ,
};

// << �ļ�ϵͳ���� >>
enum EmModuleFileSys
{
	emModuleRAWFS=1,//raw file system [ramdisk + rawblock + tffs]
	emModuleTFFS  //tffs
};

//����
enum EmModuleAction
{
    emModuleStart,
	emModuleStop,
	emModulePause,
	emModuleResume,
};

//λ��
enum EmModuleSite
{
    emModuleLocal = 0,  //����
	emModuleRemote    //Զ��
};

//����ģʽ
enum EmModuleConfMode
{
	emModuleP2PConf = 0,//��Ե����
	emModuleMCCConf = 1 //������
};

//�ն���Ƶ�˿�
enum EmModuleMtVideoPort
{
	emModuleMtVidPort1 = 0,  
	emModuleMtVidPort2    ,  
	emModuleMtVidPort3    ,  
	emModuleMtVidPort4    ,  
	emModuleMtVidPort5    ,  
	emModuleMtVidPort6    ,  
	emModuleMtVidPort7	, 
	emModuleMtVidPort8    ,
	emModuleMtVidPort9    ,
	emModuleMtVidPort10   ,
	
	emModuleMtExternalVid,
	emModuleMtVidPortMaxCount = 40, //���֧����ƵԴ����
	emModuleMtVidInvalid = 255 
};

//�����㷨
enum EmModuleEncryptArithmetic
{
	emModuleEncryptNone = 0,
	emModuleDES         = 1,
	emModuleAES         = 2,
	emModuleEncryptAuto = 3,
	
	emModuleEncryptEnd		
};

enum EmModuleUIPosion
{
	emModuleMT = 0,
	emModuleMTC = 1
};

//��Ƶ�����״̬
typedef struct tagTModuleMtVideoCodecStatus
{
	BOOL                bRuning;           //�Ƿ��ڹ���
	EmModuleVideoFormat       emFormat;          //��Ƶ�����ʽ
	EmModuleVideoResolution   emRes;             //��Ƶ�����ʽ
	u16                 wBitrate;          //��Ƶ��������(��λ:kbps)
	u16                 wAverageBitrate;   //����Ƶ��ƽ��������(��λ:kbps)
	BOOL                IsEncrypt;         //����Ƶ�����Ƿ����
	EmModuleEncryptArithmetic emArithmetic;	   //���ӱ���ʹ�õļ����㷨	
	
public:
	tagTModuleMtVideoCodecStatus()
	{ 
		memset ( this ,0 ,sizeof( struct tagTModuleMtVideoCodecStatus) );
	}
}TModuleMtVideoCodecStatus ,*PTModuleMtVideoCodecStatus;

//�ն�״̬
typedef struct tagTModuleTerStatus
{
	EmModuleMtModel  emMtModel;				    //�ն��ͺ�
	EmModuleFileSys  emFileSys;                 //�ļ�ϵͳ����
	
	u8		byEncVol;					//��ǰ��������(��λ:�ȼ�)
	u8		byDecVol;					//��ǰ��������(��λ:�ȼ�)
	BOOL	bIsMute;					//�Ƿ�����	
	BOOL	bIsQuiet;					//�Ƿ���			
	BOOL	bIsLoopBack;				//�Ƿ��Ի�
	BOOL    bIsInMixing;                //�Ƿ�μӻ���
	BOOL    bRegGkStat;			    	//GKע����	1 �ɹ� 0 ʧ��
	EmModuleAction   emPollStat;		//��ѯ״̬		emStart ,emPause ,emStop /��ʼ/��ͣ/ֹͣ
	EmModuleSite	emCamCtrlSrc;		//��ǰ��������ͷԴ���� emLocal, emRemote
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
	EmModuleConfMode emConfMode;				//����ģʽ		1 ���� 2 ���		
    BOOL       bCallByGK;				//�Ƿ�ͨ��GK���� TRUE GK·�� FALSEֱ�Ӻ���
	//	
	//	///////�豸״̬///////
	BOOL	bMatrixStatus;				    //���þ���״̬		(TRUE ok FALSE err)
	u8		byCamNum;					    //����ͷ����	(0~6)
	BOOL	bCamStatus[MAX_MTCAMERA_NUM];					//����ͷ״̬ (TRUE ok FALSE err)
	EmModuleMtVideoPort emVideoSrc;					//��ǰ������ƵԴ(0:S����,1-6:C����)
	
	BOOL    bIsEncrypt;
	//	//�������״̬
	EmModuleAudioFormat	    emADecFormat;	//��Ƶ�����ʽ
	EmModuleAudioFormat	    emAEncFormat;	//��Ƶ�����ʽ
	TModuleMtVideoCodecStatus  tPVEncStatus;   //����Ƶ������
	TModuleMtVideoCodecStatus  tSVEncStatus;   //����Ƶ������
	TModuleMtVideoCodecStatus  tPVDecStatus;   //����Ƶ������
	TModuleMtVideoCodecStatus  tSVDecStatus;   //����Ƶ������
	//	
	u16		wSysSleep;					//����ʱ��(0x0��ʾ������)
	//VOD states
	BOOL bIsInVOD;
	EmModuleUIPosion   byVodUser;
	//////����״̬///////
public:
	tagTModuleTerStatus(){ memset ( this ,0 ,sizeof( struct tagTModuleTerStatus) );}
}TModuleTerStatus ,*PTModuleTerStatus;
//end [20130726]

enum emModuleChannelDirection
{
	emModuleChannelDirectionBegin,
	emModuleChannelSend,
	emModuleChannelRecv,
	emModuleChannelBidirectional,
};

enum EmChannelReason
{
	emModuleChannelReasonBegin,
	emModuleChannelDisconnectNormal,
	emModuleDualOffLine, 
	emModuleChannelDisconnectForce,        //����˫����˫�������ͳɹ������յ��Զ˷�200Ok������Ӧ��
	emModuleDualNotSend,	//��adapter�㷢��Э��ջ״̬���ԣ�˫��δ��Э��ջ���ͳ�ȥ����ǰ״̬����ȷ������Э��ջδ���ͣ�
	emModuleDualNotSendMdl,	//��module�㷢������״̬����ֱ�ӻص������ҵ�񣨽�Э��ջ�ڲ�ʹ�ã�ҵ��ص��޴�ԭ��
};

typedef struct tagModuleChannelType
{
	emAVType m_emAVType;
	emModuleChannelDirection m_emDirection;
public:
	tagModuleChannelType()
	{
		Clear();
	}
	void Clear()
	{
		m_emAVType = emModuleTypeBegin;
		m_emDirection = emModuleChannelDirectionBegin;
	}
}TModuleChannelType;

typedef struct tagTCapSetInfo
{
	u8   m_wDynamicPayload;
	EmModuleAudioFormat m_emAudioFormat;        //��Ƶ����
	u8                  m_byPackTime;           //��Ƶ����
	EmModuleAudioChnlCfg m_emAudioChnlCfg;      //��Ƶͨ����
	EmModuleAudioSampleFreq m_emAudioSampleFreq;//��Ƶ������
	//g7231��
	u8				m_byMaxFrameNum;		    //��Ƶ��������֡��
	BOOL			m_bSilenceSuppression;	    //��Ƶ�Ƿ�������
	
	EmModuleVideoFormat m_emVideoFormat;        //��Ƶ����
	TVideoDescript      m_atItem;               //��Ƶ����
	EmModuleProfileMask m_emProfile;

	public:
	tagTCapSetInfo()
	{
		Clear();
	}
	void Clear()
	{
		m_wDynamicPayload = 0;
		m_emAudioFormat = emModuleAEnd;
		m_byPackTime = 0;
		m_emAudioChnlCfg = emModuleChnlCust;
		m_emAudioSampleFreq = emModuleFs96000;
		m_byMaxFrameNum = 0;
		m_bSilenceSuppression = FALSE;
		m_emVideoFormat = emModuleVEnd;
		m_emProfile = emModuleProfileBaseline;
		m_atItem.Clear();
	}
}TCapSetInfo;

typedef struct tagTCapSetChanInfo
{
	TModuleTransportAddress		m_tLocalRtcpAddr;
	TModuleTransportAddress     m_tLocalRtpAddr;
	TModuleTransportAddress		m_tPeerRtcpAddr;
	TModuleTransportAddress     m_tPeerRtpAddr;
	
	u8	m_byMediaCount;
	TCapSetInfo	m_atCapSetInfo[MAX_MEDIA_CAP_NUM];
// 	u8                          m_wDynamicPayload;
// 	
// 	EmModuleAudioFormat m_emAudioFormat;        //��Ƶ����
// 	u8                  m_byPackTime;           //��Ƶ����
// 	EmModuleAudioChnlCfg m_emAudioChnlCfg;      //��Ƶͨ����
// 	EmModuleAudioSampleFreq m_emAudioSampleFreq;//��Ƶ������
// 	//g7231��
// 	u8				m_byMaxFrameNum;		    //��Ƶ��������֡��
// 	BOOL			m_bSilenceSuppression;	    //��Ƶ�Ƿ�������
// 	
// 	EmModuleVideoFormat m_emVideoFormat;        //��Ƶ����
// 	TVideoDescript      m_atItem;               //��Ƶ����
	
public:
    tagTCapSetChanInfo()
	{
		Clear();
	}
	void Clear()
	{
		m_tLocalRtcpAddr.Clear();
		m_tLocalRtpAddr.Clear();
		m_tPeerRtcpAddr.Clear();
		m_tPeerRtpAddr.Clear();
		m_byMediaCount = 0;
		for ( s32 i =0; i < MAX_MEDIA_CAP_NUM; i++ )
		{
			m_atCapSetInfo[i].Clear();
		}
	}
}TCapSetChanInfo;

typedef struct tagTChanConnectedInfo
{
	HMDLCHANNEL         m_hChan;
	HMDLAPPCHANNEL      m_hAppChan;
    TModuleChannelType  m_emChanType;
    TCapSetChanInfo     m_tCapsetInfo;
	
	tagTChanConnectedInfo()
	{
		Clear();
	}
	void Clear()
	{
		m_hChan = (HMDLCHANNEL)0;
		m_hAppChan = (HMDLAPPCHANNEL)0;
		m_emChanType.Clear();
		m_tCapsetInfo.Clear();
	}
}TChanConnectedInfo;


typedef struct tagTChanDisConnectedInfo
{
	HMDLCHANNEL         m_hChan;
	HMDLAPPCHANNEL      m_hAppChan; 
	
	EmChannelReason     m_emReason;

    tagTChanDisConnectedInfo()
	{
		Clear();
	}
	void Clear()
	{
		m_hChan = (HMDLCHANNEL)0;
		m_hAppChan = (HMDLAPPCHANNEL)0;
		m_emReason = emModuleChannelReasonBegin;
	}
}TChanDisConnectedInfo;


typedef struct tagRegistReq
{
	//  �ĳɶ����֧��
	TCallAliasAddr m_atH323Alias[MAX_ALIAS_NUM];
	TCallAliasAddr m_atE164[MAX_E164_NUM];
	
	s8 m_achEPID[MAX_LEN_EPID + 1];
	
	EmModuleConnection m_emConnection;	//ע���ַ����
	TModuleTransportAddress m_tLocalAddress;    //��Ҫע��ĵ�ַ
	TModuleTransportAddress m_tGKAddress;
	TModuleTransportAddress m_tRegAddress;      //sip regserver��ַ

	s32	m_nTimeToLive;      //��

	u8	m_abyProductId[MAX_LEN_PRODUCT_ID+1];
	u8	m_abyVersionId[MAX_LEN_VERSION_ID+1];
	
	s8	m_achPassword[MAX_PASSWORD_LEN+1]; //ע������

public:
	tagRegistReq()
	{
		Clear();
	}
	void Clear()
	{
		memset( m_atE164 , 0 , sizeof(m_atE164) );
		memset( m_atH323Alias , 0 , sizeof(m_atH323Alias) );
		memset( m_achEPID, 0, sizeof( m_achEPID) );
		memset( m_abyProductId, 0, sizeof( m_abyProductId) );
		memset( m_abyVersionId, 0, sizeof( m_abyVersionId) );
		memset( m_achPassword, 0, sizeof( m_achPassword) );
		m_tLocalAddress.Clear();
		m_tGKAddress.Clear();
		m_tRegAddress.Clear();
		m_nTimeToLive = 60;
		m_emConnection = emModuleUdpConnection;
	}
}TRegistReq;


//�ն˱�Ų���
typedef struct tagModuleTerminalLabel 
{
	u8 m_byMcuNo;
	u8 m_byTerNo;
	
	tagModuleTerminalLabel()
	{
		Clear();		
	}
	
	void Clear()
	{
		m_byMcuNo = 0xff;
		m_byTerNo = 0xff;
	}

	BOOL32 isValid()
	{
		return ( m_byTerNo <= MAX_CONFMT_NUM && m_byMcuNo != 0xff );
	}

	BOOL32 operator == (const tagModuleTerminalLabel& tTerLabel)
	{
        return !memcmp(this, (void*)&tTerLabel, sizeof(tTerLabel));
	}

}TMDLTERLABEL,*PMDLTTERLABEL;


//�ն���Ϣ(�����)
typedef struct tagModuleTerminalInfo
{
	u8 m_byMcuNo;   
	u8 m_byTerNo;
	u8 m_byConfNo;   //�������
	s8 m_achTerminalId[MAX_TERMINALID_LEN+1];    //TerminalID
	BOOL32 m_bIsChair;   //�Ƿ�����ϯ
	BOOL32 m_bIsFloor;   //�Ƿ��Ƿ�����

	BOOL32 m_bLastPack;  // �Ƿ������һ��
	BOOL32 m_bOnline;    // �Ƿ�����

	TMDLTERLABEL m_tTerYouAreView;    //����ѡ��˭
	u32 m_anSeenByOtherListMask[6];   //6��int��ʾ192��λ������ʾ192���նˣ�˭ѡ��������ն�

	tagModuleTerminalInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_byConfNo = 0xff;
		m_byMcuNo = 0xff;
		m_byTerNo = 0xff;
		memset( m_achTerminalId, 0, sizeof(m_achTerminalId) );
		m_bIsChair = FALSE;
		m_bIsFloor = FALSE;

		m_bLastPack = FALSE;
		m_bOnline   = FALSE;
		m_tTerYouAreView.Clear();
		
		memset( m_anSeenByOtherListMask, 0, sizeof(m_anSeenByOtherListMask) );
	}

	void AddSeenByOtherList( u8 terNo )
	{
		if( terNo >= 192 )
			return;

		u8 i = terNo/(sizeof(u32)*8);
		u8 j = terNo%(sizeof(u32)*8);
		
		u32 mask = 0x00000001;
		mask <<= j;
		
		m_anSeenByOtherListMask[i] |= mask;
	}

	void DelSeenByOtherList( u8 terNo )
	{
		if( terNo >= 192 )
			return;

		u8 i = terNo/(sizeof(u32)*8);
		u8 j = terNo%(sizeof(u32)*8);

		u32 mask = 0x00000001;
		mask <<= j;

		m_anSeenByOtherListMask[i] &= ~mask;
	}

	BOOL32 IsSeenByOtherListEmpty( )
	{
		u32 temp[6];
		memset( temp, 0, sizeof(temp) );
		return !memcmp( temp, m_anSeenByOtherListMask, sizeof(temp) );
	}

	void ResetSeenByOtherList( )
	{
		memset( m_anSeenByOtherListMask, 0, sizeof(m_anSeenByOtherListMask) );
	}

	u8 GetSeenByOtherList( u8* list )  //�������������192��u8
	{ 
		u8 count = 0;

		for( u8 i = 0; i < 6; i++ )
		{
			if( m_anSeenByOtherListMask[i] != 0 )
			{
				for( u8 j = 0; j < sizeof(u32)*8; j++ )
				{
					u32 mask = 0x00000001;
					mask <<= j;

					if( m_anSeenByOtherListMask[i] & mask )
					{
						list[count++] = (u8)(sizeof(u32)*8*i + j);
					}
				}
			}
		}
		return count;
	}

}TMDLTERMINALINFO,*PMDLTERMINALINFO;


enum EmModuleOperateType
{
	emModuleOperateType_NULL,       //�ղ���
	emModuleOperateType_Add,        //���Ӳ���
	emModuleOperateType_Del,        //ɾ������
	emModuleOperateType_Update      //�޸Ĳ���
};

typedef struct tagModuleTerInfoList
{
	EmModuleOperateType	    m_emOperateType;
	u8 m_byNum;
	TMDLTERMINALINFO m_atTerInfoList[MAX_CONFMT_NUM];
	
	tagModuleTerInfoList()
	{
		Clear();
	}

	void Clear()
	{
		m_emOperateType = emModuleOperateType_Add;
		m_byNum = 0;
		memset( m_atTerInfoList, 0, sizeof(m_atTerInfoList) );
		for( u8 index = 0; index < MAX_CONFMT_NUM; index++ )
		{
			m_atTerInfoList[index].Clear();
		}
	}
}TMDLTERINFOLIST,*PTMDLTERINFOLIST;



typedef struct tagModuleTerLabelList
{
	u8 m_byNum;
	TMDLTERLABEL m_atTerLabelList[MAX_CONFMT_NUM];
	
	tagModuleTerLabelList()
	{
		Clear();
	}
	
	void Clear()
	{
		m_byNum = 0;
		//memset( m_atTerLabelList, 0, sizeof(m_atTerLabelList) );
		for( u8 index = 0; index < MAX_CONFMT_NUM; index++ )
		{
			m_atTerLabelList[index].Clear();
		}
	}
}TMDLTERLABELLIST,*PTMDLTERLABELLIST;

typedef struct tagModuleConfList
{
	u8 m_byConfNo;  //�����
	u8 m_byTerCount;
	HMDLCALL m_ahCall[MAX_CONFMT_NUM];

	tagModuleConfList()
	{
		Clear();
	}

	void Clear()
	{
		m_byConfNo = 0xff;
		m_byTerCount = 0;
		memset( m_ahCall, 0, sizeof(m_ahCall) );
	}
}TMDLCONFLIST,*PTMDLCONFLIST;



typedef struct tagModuleAlias
{
	emModuleAliasType m_emAliasType;
	u8 m_abyCallAliasAddr[MAX_LEN_CALL_ALIAS+1];

	tagModuleAlias()
	{
		Clear();
	}
	void Clear()
	{
		m_emAliasType = emModuleType_aliastype;
		memset( m_abyCallAliasAddr, 0, sizeof(m_abyCallAliasAddr) );
	}
}TModuleAlias;

typedef struct tagModuleTerminal
{
	u32 m_dwIp;
	TModuleAlias m_atAlias[2];
	emModuleEndpointType m_emTerminalType;

	tagModuleTerminal()
	{
		Clear();
	}
	
	void Clear()
	{
		memset( m_atAlias, 0, sizeof(m_atAlias) );
		m_emTerminalType = emModuletypeBegin;
		m_dwIp = 0;
	}
}TModuleTerminal;

typedef struct tagModuleMtOnlineList
{
	u16 m_wListNum;
	TModuleTerminal m_atTerminal[MAX_ONLINE_LIST_NUM];
	BOOL32 m_bIsEnd;

	tagModuleMtOnlineList()
	{
		Clear();
	}

	void Clear()
	{
		m_wListNum = 0;
		memset( m_atTerminal, 0, sizeof(m_atTerminal) );
		m_bIsEnd = FALSE;
	}
}TModuleMtOnlineList;

typedef struct tagModuleMcuOnlineList
{
	u16 m_wAliasNum;
	TModuleAlias m_atAlias[MAX_ALIAS_NUM];
	u32 m_dwIp;
	BOOL32 m_bIsEnd;

	tagModuleMcuOnlineList()
	{
		Clear();
	}
	
	void Clear()
	{
		m_wAliasNum = 0;
		memset( m_atAlias, 0, sizeof(m_atAlias) );
		m_bIsEnd = FALSE;
		m_dwIp = 0;
	}
}TModuleMcuOnlineList;



//ע����
enum EmRegResult
{
	emModuleRegResultBegin = 0,
	emModuleRegResultReg,
	emModuleRegResultUnReg,
};

enum EmPARegFailedReason
{
	emPALocalNormalUnreg = 0,
	emPAInvalidUserNameAndPassword,
	emPARegistrarUnReachable,
	emPAInvalidAlias,
	emPAUnknownReason,
	emPARegisterFailed,
	emPARegisterNameDup,
	emPAUnRegistSuccess,
};

enum emModuleRasReason
{
	emModuleRasGKUnReachable,
	emModuleRasInvalidAlias,
	emModuleRasInvalidCallSignalAddress,
	emModuleRasInvalidTerminalType,
	emModuleRasFullRegistrationRequired,
	emModuleRasInvalidTerminalAliases,
	emModuleRasDuplicateAlias,
	emModuleRasUnknownReason
};

enum EmModuleGetGKInfoType
{
	emModuleGetGKInfoType_MT = 0,
		emModuleGetGKInfoType_MCU,
		emModuleGetGKInfoType_ALL
};

//��ӡ��ģ��
enum emModuleType 
{
	emModuleNon = 0,
		emModuleService,
		emModuleStackin,
		emModuleStackout,
		emModuleCapSet,
		emModule,
		emModuleAll,
		emModuleAllExceptCapSet,
};

enum emCallBy
{
	emModuleCallByNum = 0,
		emModuleCallByName,
};

//��־������
#define LOG_EXP			        (s32)0		//�쳣
#define LOG_IMT			        (s32)1		//��Ҫ��־
#define LOG_DEBUG		        (s32)2		//һ��������Ϣ
#define LOG_ALL                 (s32)3      //���е�����Ϣ 
#define LOG_CONF                (s32)4      //���������Ϣ����ء��ؼ�֡�ȣ� 

//int����ipת�����ַ���
#define IP2CHAR(ip)  ((u8 *)&(ip))[0], \
				     ((u8 *)&(ip))[1], \
					 ((u8 *)&(ip))[2], \
                     ((u8 *)&(ip))[3]

#endif



