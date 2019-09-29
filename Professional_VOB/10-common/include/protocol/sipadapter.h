
#ifndef _SIPADAPTER_
#define _SIPADAPTER_

#ifdef _LINUX_
#include "osp.h"
// #include <stdarg.h>
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <netinet/tcp.h>
// #include <netdb.h>
// #include <arpa/inet.h>
// #include <sys/ioctl.h>
// #include <stdio.h>
// #include <unistd.h>
// 
#ifndef min
#define min(a,b) ((a)>(b)?(b):(a))
#endif
#ifndef max
#define max(a,b) ((a)>(b)?(a):(b))
#endif

#endif

#include "rvsipstack.h"
#include "rvsdpmsg.h"
#include "kdvtype.h"

#define LEN_MAXMT_NUM   	(u16)193				//ÿ�������е���������
#define LEN_MTNUM_PERCONF	(u16)193				//ÿ�������е���������
#define LEN_USERNAME    	(u16)64			    	//�û�������
#define LEN_PASSWORD		(u16)16					//���볤��
#define LEN_DOMAINNAME    	(u16)64			    	//��������
#define LEN_ENCKEY_MAX		(u16)64					//(1-65535) 
#define SIP_CHAN_SPAN  10
#define SESSION_NAME_LEN     64
#define SESSION_ID_LEN       64
#define SESSION_USERNAME_LEN 64
#define SESSION_VERSION_LEN  64
#define SESSION_INFO_LEN     128

#define MAX_LEN_SESSION_DESCRIPTION 1024*10

#define MAX_LEN_LANGUAGE_HEADER 32
#define MAX_LEN_ENCODE_TYPE_HEADER 32
#define MAX_LEN_HEADER_NAME 64

#define MAX_NUM_TRANC_PERCALL 64
#define MAX_NUM_CALLID        128

#define MAX_NUM_CONTACT_ADDR  5
#define MAX_NUM_REGCLIENT     128
#define MAX_NUM_REGNAME_SIZE 64
#define MAX_NUM_CHAN	     20
#define MAX_NUM_LEN_VERSION			 256
#define MAX_XML_LEN			 65536
#define DEFAULT_BUFF_LEN     1024
#define MAX_AAC_CAP_NUM      2
#define MAX_SIP_REG_INFO_NUM	2
#define MAX_FLOOR_NUM  5
#define MAX_MEDIA_NUM_PER_FLOOR  5
#define MAX_CONF_NUM		(u16)32                 //��������
#define LEN_GUID			(u8)16					//GIUD����
#define LEN_1				(u16)1
#define LEN_TERID			(u16)128				//�ն�������󳤶�
#define MAX_H264CAP_NUM     (u8)10                  //H.264��������
#define LEN_ALIAS			(u16)64				    //����������h323-id
#define MAX_TERMINAL_NUM 32
#define MAX_SIP_REG_INFO_NUM_UMS	3
#define MAX_SIP_REG_INFO_NUM_CNS	20
#define SIP_CALL_ID_SIZE		128
#define MAX_NUM_REGNAME_SIZE_CNS 2
#define MAX_SIP_CONF_ID_LEN	16
#define MAX_SIP_CONF_NAME_LEN 96
#define MAX_SIP_CONF_E164_LEN 16
#define MAX_SIP_PASSWORD_LEN 32
#define MAX_SIP_TERMINAL_NUM 32
#define MAX_SIP_CONF_AUDMIX_NUM_TP	4			//��������������
#define SIP_INVALID_INDEX_TP	0xFFFF

extern u32 g_dwLogOn;

typedef struct tagSipAdapterCfg
{
	BOOL    m_bIfRegister;
	u32     m_dwMaxCalls;      //��������
    u32     m_dwLocalIP;             //���˵�ַ.������
    u16     m_wLocalUdpPort;  //����udp������ַ
    u16     m_wLocalTcpPort;  //����tcp������ַ
	BOOL    m_bManualAck;
	u16     m_wRegClientNum;
	u32     m_dwMaxSendReciveBufferSize;

	s8      m_achProduct[64];  //��Ʒ��Ϣ
	s8      m_achTerVer[128];  //�汾��Ϣ
public:
	tagSipAdapterCfg()
	{
		Clear();
	}
	void Clear()
	{
		memset(this , 0 , sizeof(tagSipAdapterCfg) );
		m_wRegClientNum = 2;
		m_dwMaxSendReciveBufferSize = 20480;
	}
}TSipAdapterCfg;


enum EmDualFailReason
{
    emMsgBodyLenError, 
    emMsgCapsetError,
	emNoSendingDual,
	emNoRecvingDual,
	emNoOpeningRequest,
	emNoClosingRequest,
	emPrevOperProcessing,

};


enum EmRegFailReason
{
    emSendFail, 
    emUnImplement,
	emExist,
};

//������Ϣ
enum EmSipCallMsgType 
{
	h_call_invalidInterface = 0,
    h_call_make,		            //�������	      [outgoing]: TCALLPARAM + CSipCapSet(optional)
	h_call_incoming,		        //���е���		  [incoming]: TCALLPARAM + VendorProductId		  	  	
	h_call_answer,		            //����(�ܾ�)����  [outgoing]: TNODEINFO + CSipCapSet
	h_call_bye,                    //��������		  [outgoing]: 1 byte,reason
	h_call_connected,               //���н���		  [incoming]: TNODEINFO	
	h_call_disconnected,            //���жϿ�		  [incoming]: 1 byte,reason	
	h_call_capsetnotify,            //����������      [incoming]: 
	h_dual_open,                    //��˫��
	h_dual_open_accept,
	h_dual_close,                   //�ر�˫��
	h_dual_close_accept,                   
	h_dual_ack,
	h_dual_reject,
	h_dual_connected,
	h_dual_disconnected,
    h_dual_failed,
	h_call_roundtripdelay,          //roundtrip implemented by options method
	h_call_ack,
};


//�ŵ�������Ϣ
enum EmSipChanCtrlMsgType 
{
	h_chan_invalidInterface = 0,
  	h_chan_videofastupdate,
	h_chan_flowControlCmd,
	h_chan_flowControlInd,
	h_chan_fastupdatewithoutid,
};
//���������Ϣ
enum EmSipConfCtrlMsgType
{
	h_conf_invalidInterface = 0,
	h_conf_optionsrequest,//options method request
	h_conf_optionsresponse, //options method response
	h_conf_nonstandard,
	h_conf_Multiple,
};
enum EmSipRegCtrlMsgType
{
	h_sip_registration   = 0, 
	h_sip_unregistration = 1,
	h_sip_online         = 2,
	h_sip_offline        = 3,
	h_sip_state2registered,
	h_sip_state2failed,
	h_sip_state2terminated,
	h_sip_state2redirected,
	h_sip_state2sendmsgfailed,
	
	h_sip_getreginfo,       //���regserver�ϵ�����ע����Ϣ����
	h_sip_getreginfoack,    //regserver��ע����Ϣ����Ļ�Ӧ
	h_sip_getreginfoack_B2,    //regserver��ע����Ϣ����Ļ�Ӧ
};
enum EmSipUMSCtrlMsgType
{
	h_ums_invalidInterface = 0,
	h_ums_registrationcmd, //RegisterRequest ע������ 
	h_ums_registrationind, //ע��ɹ���EmRegisterReason+TRegisterResponse��ע��ʧ�ܣ�EmRegisterReason (emRegFail); ע������ EmRegisterReason(emRegNameDup)+sizeof(s32)+TSipRegName ע����Ӧ
	h_ums_unregistrationcmd,//RegisterRequest+bool(if expire all) ȡ��ע������
	h_ums_unregistrationind,//EmRegisterReason ȡ��ע����Ӧ,ԭ��Ϊȡ���ɹ���ʧ��
	h_ums_query,       //char(����) ��ѯ
	h_ums_answer,      //EmRegisterReason+RegisterResponse ��Ӧ��ѯ
	h_ums_option,      //��������ע���ն˷��Ͳ�ѯָ� ��option��Ϣ�� �ص�Ҳ��option��Ϣ,����regserver��ѯע���Ƿ�����

	h_ums_getregreq,          //ums��cns��regserver�����õ�ǰ�ı���, buf������Ϊ��s32 nAppid, EmSipGetRegInfoType
	h_ums_getregack,          //regserver��Ӧ��, buf������Ϊ��s32 nAppid, TSipRegPackXml
	h_ums_getregack_B2,          //regserver��Ӧ��, buf������Ϊ��s32 nAppid, TSipRegPackXmlB2, TSipRegInfoUms/TSipRegInfoCns


};

enum EmSipChannelReason
{
	emSipChannelReasonBegin,
	emSipChannelDisconnectNormal,
	emSipDualOffLine, 
	emSipChannelDisconnectForce,	//����˫����˫�������ͳɹ������յ��Զ˷�200Ok������Ӧ��
	emSipDualNotSend,	//˫��δ��Э��ջ���ͳ�ȥ����ǰ״̬����ȷ������Э��ջδ���ͣ�
};

//���йҶ�ԭ��
enum EmSipCallDisconReason
{
	emSipDiscon_Busy = 1   ,//�Զ�æ
	emSipDiscon_Normal     ,//�����Ҷ�
	emSipDiscon_Rejected   ,//�Զ˾ܾ�
	emSipDiscon_Unreachable,//�Զ˲��ɴ�
	emSipDiscon_Local      ,//����ԭ��
	emSipDiscon_unknown    ,//δ֪ԭ��

	//TP
	emSipDiscon_AlredayInDualStream, //����˫���У��޷���������˫��
	emSipDiscon_Normal_Peer,         //�Է��Ҷ�
	emSipDiscon_Abnormal,            //���˵��߹Ҷ�
	emSipDiscon_Abnormal_Peer,       //�Զ˵��߹Ҷ�
	emSipDiscon_MultiConfOver,       //���������
	emSipDiscon_ConfAlredayExit,      //�����Ѿ�����
	emSipDiscon_InvalidDestAddr,		//��Ч��Ŀ�ĵ�ַ

	emSipDiscon_CallFull,//���о������(���ܴ��ں��о��δ�ͷŵ�����)
};

typedef struct tagRegOptionData  //regserver���͵Ĳ�ѯָ��
{
	u32 dwtime;      //ע����
	u32 ip;			 //�ն˵�ip	
	u16 port;        //�ն˵�port
	tagRegOptionData()
	{
		memset(this, 0, sizeof(tagRegOptionData));
	}
}TRegOptionData;

enum EmRegState
{
   emRegIdle,
   emRegRegistering,
   emRegRegistered,
   emRegFailed,
   emUnReg,
};

enum EmSipCallType
{
    emDirect = 0,         //ֱ�Ӻ���
	emByRedirect,         //ͨ���ض������������
	emByPxy,              //ͨ���������������
};

//�������:����-Ӧ��ʽ���ؽ��
enum CtrlResult 
{
	ctrl_err = -1,
	ctrl_granted,		//�ɹ�
	ctrl_denied			//�ܾ�
};

//����������
enum EmHostNameType
{
	emUrlIpv4,
	emUrlIpv6,
	emUrlDomain,
	emUrlAlias,
	emUrlE164Num,
    emUrlNone,
};

enum EmSipMediaType
{
	emSipMediaNone,
    emSipMediaAudio,
	emSipMediaVideo,
	emSipMediaH224,
	emSipMediaT120,
	emSipMediaBfcp,

};
enum  EmSipPayloadType 
{
	emSipPayloadTypeBegin = 0,
    //��Ƶ��ʽ
     emAudioTypeBegin,
     emG711a,
     emG711u,
     emG722,
     emG7231,
     emG728,
     emG729,
     emMp3,  
     emG723,
     emG7221,
     emMpegaaclc,
     emMpegaacld,
	 emG719,
     emAudioTypeEnd = 49,
          
    //��Ƶ��ʽ
     emVideoTypeBegin = 50,	
     emH261,
     emH263,
     emH263plus,
     emH264,
	 emH262,
	 emMpeg4,
     emVideoTypeEnd = 99,
        
	 emDataTypeBegin = 100,	
     emT120,
     emH224,
     emSipDataTypeEnd = 149,
                
    emSipPayloadTypeEnd = 255
};


//�ֱ���
//sipadapterĿǰ֧�ֵ���Ч�ֱ������£��Ӹߵ���˳��
//emSipHD1080��emSipUXGA��emSipSXGA��emSip1280x800��emSip1366x768��emSipHD720��emSipXGA��emSipSVGA��emSipCIF4��emSipSIF4��emSipVGA��emSipCIF��emSipSIF��emSipQCIF��emSipSQCIF
enum EmSipResolution
{
	emSipResolutionBegin = 0,
	emSipSQCIF,
	emSipQCIF,
	emSipCIF,
	emSipCIF2,
	emSipCIF4,
	emSipCIF16,
		
	emSipSIF,
	emSipSIF4,
	emSipVGA,
	emSipSVGA,
	emSipXGA,
	
	emSipWCIF4,  //1024*576
	emSipHD720,  //1280*720
	emSip1280x768, //1280*768
	emSip1366x768, //1366*768
	emSip1280x800, //1280*800
	emSipSXGA,   //1280*1024
    emSipUXGA,   //1600*1200
    emSipHD1080, //1920*1080
	emSipAuto,
	emSipResolutionEnd
};



enum EmSipG7221Rate
{
	emG7221Rate24   =  0x01,
	emG7221Rate32   =  0x02,
	emG7221Rate48   =  0x04
};


//��������
enum EmSipEncryptType
{
    emSipEncryptTypeNone = 1,//00000001
    emSipEncryptTypeDES  = 2,//00000010
    emSipEncryptTypeAES  = 4,//00000100
};


//�豸���̱�ʶ��Ϣ
enum EmSipVendorId
{
	emVendorUnknow = 0,
	emMicrosoftNetmeeting = 1,
	emKeda,
	emHuaWei,
	emPolycom,
    emTandberg,
	emRadvision,
	emVcon,
	emSony,
	emVtel,
	emZTE,
	emCodian,
};

enum EmRegisterReason
{
	emRegNone = 0,
		emRegSuc,          // ע��ɹ�
		emRegFail,         //ע��ʧ��
		emRegNotFound,
		emRegNameDup,      //ע�����������ʱ������������������Ϣ
		emRegTimeOut,      //ע����������ɴ��ʱ
};

typedef enum 
{
	emSendRecvBegin = 0,
		emSendOnly = 1,
		emRecvOnly = 2,
		emSendRecv = 3
}emSendRecvAttr;


enum EmSipConnection
{
	emSipConnectionType = 0,
		emSipTcpConnection,
		emSipUdpConnection,
		emSipSCTPConnection,
		emSipTLSConnection,
};
enum EmSipTerminalType
{
	emSipTerUnknown,
		emSipTerMCU,
		emSipTerMT,
		emSipTerRegister,
};
enum EmSipLevel
{
	emSipCounty,
	emSipCity,
	emSipProvince,
	emSipUnKnown = 255,
};

enum EmSipCapSign
{
	emSipCapBig,  
	emSipCapLeft,
	emSipCapRight,
	emSipCapEnd,
};

enum EmSipMsgType
{
	emSipNone,
	emSipInvite,  
	emSip200OK,
	emSipAck,
};

//�ն˱�Ų���
typedef struct tagTerminalLabel 
{
	u8 m_byMcuNo;
	u8 m_byTerNo;
	
	tagTerminalLabel()
	{
		Clear();		
	}
	
	void Clear()
	{
		m_byMcuNo = 0xff;
		m_byTerNo = 0xff;
	}
	
	bool operator ==(tagTerminalLabel& tLabel)
	{
		if (m_byMcuNo == tLabel.m_byMcuNo && m_byTerNo == tLabel.m_byTerNo)
			return true;
		else
			return false;
	}
	
	bool operator !=(tagTerminalLabel& tLabel)
	{
		if (m_byMcuNo != tLabel.m_byMcuNo || m_byTerNo != tLabel.m_byTerNo)
			return true;
		else
			return false;
	}
    //��Ч�Լ��
	bool IsValid()
	{
		return ( m_byMcuNo < LEN_MTNUM_PERCONF && m_byTerNo < LEN_MTNUM_PERCONF);
	}
    
    //����TerminalLabel
	BOOL SetTerminalLabel( u8 byMcuNo, u8 byTerNo )
	{
		if( byMcuNo < LEN_MTNUM_PERCONF && byTerNo < LEN_MTNUM_PERCONF )
		{
			m_byMcuNo = byMcuNo;
			m_byTerNo = byTerNo;
            return TRUE;
		}
        return FALSE;
	}
    //��ȡTerminalLabel
	void GetTerminalLabel( u8 *pMcuNo, u8 *pTerNo )
	{
		*pMcuNo = m_byMcuNo;
		*pTerNo = m_byTerNo;
	}
    //��ȡmcu���
	u8 GetMcuNo()
	{
		return m_byMcuNo;
	}
    //��ȡ�ն˱��
	u8 GetTerNo()
	{
		return  m_byTerNo;
	}
}TTERLABEL,*PTTERLABEL;

//�ն���Ϣ����
typedef struct tagTerminalInformation 
{
	TTERLABEL	m_tTerLabel;
	s8			m_achTerID[LEN_TERID + 1];

	tagTerminalInformation()
	{
		Clear();
	}

	void Clear()
	{
		m_tTerLabel.Clear();
        memset( m_achTerID, 0, sizeof(m_achTerID) );        
	}	
	
	//�����ն˱��
	void SetLabel(const PTTERLABEL ptLabel)
	{
		if (ptLabel != NULL)
		{
			memcpy( &m_tTerLabel, ptLabel, sizeof(m_tTerLabel) );
		}		
	}
	void SetLabel(u8 byMcuNo, u8 byTerNo)
	{
		if (byMcuNo < 193 && byTerNo <193)
		{
			m_tTerLabel.SetTerminalLabel(byMcuNo, byTerNo);
		}
	}
	//����ն˱��
	TTERLABEL& GetTerlabel()
	{
		return m_tTerLabel;
	}
	void GetLabel(u8& byMcuNo, u8& byTerNo)
	{
		m_tTerLabel.GetTerminalLabel( &byMcuNo, &byTerNo );
	}
	//���Mcu��
	u8 GetMcuNo() 
	{ 
		return m_tTerLabel.GetMcuNo();	
	}
	//����ն˺�
	u8 GetTerNo() 
	{ 
		return m_tTerLabel.GetTerNo();	
	}

	//�����ն�����
	BOOL SetName(const s8* pchName)
	{
		if (pchName != NULL)
		{
			strncpy( m_achTerID, pchName, LEN_TERID + 1 );
			m_achTerID[LEN_TERID] = '\0';
			return TRUE;
		}
		return FALSE;
	}
	//����ն�����
	s8* GetName()
	{
		return m_achTerID;
	}

	void operator = (tagTerminalInformation& tTerInfo)
	{
		m_tTerLabel.SetTerminalLabel( tTerInfo.m_tTerLabel.GetMcuNo(), 
									  tTerInfo.m_tTerLabel.GetTerNo() );

		strncpy( m_achTerID,tTerInfo.GetName(), LEN_TERID + 1);
	}

	bool operator != (tagTerminalInformation& tTerInfo)
	{
		if ( m_tTerLabel.GetMcuNo() == tTerInfo.m_tTerLabel.GetMcuNo() && 
			 m_tTerLabel.GetTerNo() == tTerInfo.m_tTerLabel.GetTerNo() &&
			 strcmp( m_achTerID, tTerInfo.m_achTerID ) == 0 )
		{
			return false;
		}
		return true;
	}

	bool operator == (tagTerminalInformation& tTerInfo)
	{
		if ( m_tTerLabel.GetMcuNo() == tTerInfo.m_tTerLabel.GetMcuNo() && 
			 m_tTerLabel.GetTerNo() == tTerInfo.m_tTerLabel.GetTerNo() &&
			 strcmp( m_achTerID, tTerInfo.m_achTerID ) == 0 )
		{
			return true;
		}
		return false;
	}
}TTERINFO,*PTTERINFO;

//defined in rfc4796
enum EmSipContentAttr
{
	emSipContentNone = 0,
	emSipContentSlides,
	emSipContentSpeaker,
	emSipContentSl,
	emSipContentMain,
	emSipContentAlt,

};

//defined in rfc4145
enum EmSipSetupAttr
{
	emSipSetupBegin = 0,
	emSipActive = 1,
	emSipPassive = 2,
	emSipActpass = 3,
	emSipHoldconn = 4
};

//defined in rfc4145
enum EmSipConnectionAttr
{
	emSipConnectionBegin = 0,
	emSipNew = 1,
	emSipExisting = 2,
};

//defined in rfc4583
enum EmSipFloorcontrolAttr
{
	emSipFloorcontrolBegin = 0,
	emSipClientOnly = 1,
	emSipServerOnly = 2,
	emSipClientServer = 3
};

// enum EmMediaDualState
// {
// 	emDualNone,         //����˫��
// 	emDualStart,		//��˫������ʼ״̬
// 	emDualSuc,			//˫������ƥ��״��
// 	emDualFail,			//˫��������ƥ��
// };

//����ͬ���ṹ  
typedef struct tagSipEncryptSync
{
	s32			  m_nSynchFlag;			         //shall be the Dynamic PayloadType for H.323
	u8			  m_abyKey[LEN_ENCKEY_MAX+1]; //H.235 encoded value(1-65535)
	s32           m_nKeyLen;

    
	void clear()
	{
        m_nSynchFlag = 0;
		m_nKeyLen = 0;
		memset( m_abyKey, 0, sizeof( m_abyKey ) );
	}
    //����SynchFlag
	void SetSynchFlag(s32 nFlag)
	{ 
		m_nSynchFlag = nFlag; 
	}
    //��ȡSynchFlag
	s32  GetSynchFlag() 
	{
		return m_nSynchFlag; 
	}

    //����H235Key
	s32 SetKey(u8 *pBuf, s32 nLen)
	{
		m_nKeyLen = min(max(0, nLen), LEN_ENCKEY_MAX);
		memcpy(m_abyKey, pBuf, m_nKeyLen);
		return m_nKeyLen;
	}	
    //��ȡH235Key�ĳ���
	s32 GetKeyLen() 
	{
		return m_nKeyLen; 
	}
    //��ȡH235Key
	u8* GetKey()
	{
		return m_abyKey;
	}
}TSipEncryptSync;

//IP�����ַ
typedef struct tagTransAddress
{
	u32 m_dwIP ;//������
	u16 m_wPort;//������
public:
	void Clear()
	{
		m_dwIP = 0;
		m_wPort = 0;
	}
}TIPTransAddress;


struct TSipCap
{
    u32  m_dwSampleRate;
    EmSipPayloadType m_emPayloadType;
    u16              m_wStaticPayload;
    u16 m_wDynamicPayload;    
public:
	TSipCap()
	{
		Clear();
	}

	void Clear()
	{
		m_emPayloadType = emSipPayloadTypeBegin;
		m_dwSampleRate = 8000;
		m_wDynamicPayload = 0;
	}
	
	void SetPayloadType( EmSipPayloadType emPt )
	{
        m_emPayloadType = emPt;
	}
	
	EmSipPayloadType GetPayloadType()
	{
		return m_emPayloadType;
	}
	
	void SetSampleRate( u32 dwSampleRate )
	{
        m_dwSampleRate = dwSampleRate;
	}
	
	u32 GetSampleRate()
	{
		return m_dwSampleRate;
	}
	
	void SetStaticPayload( u16 wPt )
	{
		m_wStaticPayload = wPt;
	}
	u16 GetStaticPayload()
	{
		return m_wStaticPayload;
	}
	
	void SetDynamicPayload( u16 wDPt )
	{
		m_wDynamicPayload = wDPt;
	}
	u16 GetDynamicPayload()
	{
		return m_wDynamicPayload;
	}
};
//��Ƶ��������������G.7231
struct TSipAudioCap : public TSipCap
{
	u8   m_byPackTime;     //ÿһRTP�������ʱ��,��λms(1-256); 

public:
	TSipAudioCap()
		:TSipCap()
	{
		m_byPackTime = 30;
	}

	void Clear()
	{
		m_byPackTime = 30;
		TSipCap::Clear();
	};

    //���ô��ʱ��
	void SetPackTime(u8 byPackTime)
	{
		m_byPackTime = byPackTime;
	}
    //��ȡ���ʱ��
	u8  GetPackTime()
	{
		return m_byPackTime;
	}	

};

//G7231��������
struct TSipG7231Cap : public TSipAudioCap
{
	u8				m_byMaxFrameNum;		//��������֡��
	BOOL			m_bSilenceSuppression;	//�Ƿ�������
public:
	TSipG7231Cap()
		:TSipAudioCap()
	{
		m_byMaxFrameNum  = 1;			    //Ŀǰ����ֻ֧�ֵ�֡
		m_bSilenceSuppression = TRUE;
	}

	void Clear()
	{
		m_byMaxFrameNum  = 1;			    //Ŀǰ����ֻ֧�ֵ�֡
		m_bSilenceSuppression = TRUE;	    //����Ĭ��֧�־�������
		TSipAudioCap::Clear();
	}

    //�����Ƿ�֧�־���
    void SetIsSilenceSuppression(BOOL bSilenceSuppression)
    {
        m_bSilenceSuppression = bSilenceSuppression;
    }
    //�Ƿ�֧�־���
	BOOL IsSilenceSuppression()
	{
		return m_bSilenceSuppression;
	}
    
    //����ÿ�������֡��
	void SetMaxFrameNumPerPack(u8 byMaxFrameNum)
	{
		m_byMaxFrameNum = byMaxFrameNum;
	}
    //��ȡÿ�������֡��
	u8 GetMaxFrameNumPerPack()
	{
		return m_byMaxFrameNum;
	}
};

struct TSipG7221Cap: public TSipAudioCap
{
	u8  m_byBitRateType;         //encode bitrate
public:
	TSipG7221Cap()
		:TSipAudioCap()
	{
		m_byBitRateType = emG7221Rate24;
	}
	
	void Clear()
	{
		TSipAudioCap::Clear();
    	m_byBitRateType = emG7221Rate24;
	};
	
    //����rate
	void SetRateType( u8 byRateType )
	{
		m_byBitRateType = byRateType;
	}
	void OrRateType( EmSipG7221Rate emRateType )
	{
	    m_byBitRateType = (m_byBitRateType | emRateType);
	}

	//��ȡrate
	u8 GetRateType()
	{
		return m_byBitRateType;
	}


	void SetBitRate( u32 dwBitRate )
	{
		m_byBitRateType = 0;
		if ( dwBitRate == 48000 )
			m_byBitRateType |= emG7221Rate48;
        else if ( dwBitRate == 32000 )
			m_byBitRateType |= emG7221Rate32;
        else
			m_byBitRateType |= emG7221Rate24;
	}

	u16 GetBitRate()
	{
		if( m_byBitRateType & emG7221Rate48 )
			return 48000;
		else if ( m_byBitRateType & emG7221Rate32 )
			return 32000;
		else 
			return 24000;
	}

};

//MPEG AAC������
struct TAacCap : public TSipAudioCap
{
    enum emAACSampleFreq                    //sampling frequency
    {
        emFs96000 = 0,
        emFs88200 = 1,
        emFs64000 = 2,
        emFs48000 = 3,
        emFs44100 = 4,
        emFs32000 = 5,
        emFs24000 = 6,
        emFs22050 = 7,
        emFs16000 = 8,
        emFs12000 = 9,
        emFs11025 = 10,
        emFs8000  = 11
    };
    
    enum emAACChnlCfg                       //channel config
    {
        emChnlCust   = 0,
        emChnl1      = 1,                   //������
        emChnl2      = 2,                   //˫����
        emChnl3      = 3,
        emChnl4      = 4,
        emChnl5      = 5,
        emChnl5dot1  = 6,                   //5.1����
        emChnl7dot1  = 7                    //7.1����
    };

    emAACSampleFreq m_emSampleFreq;
    emAACChnlCfg    m_emChnlCfg;
    u16             m_wBitrate;
    u8              m_byMaxFrameNum;

public:
    TAacCap()
    {
        Clear();
    }
    
    void Clear()
    {
        m_emSampleFreq = emFs32000;
        m_emChnlCfg = emChnl2;
        m_byMaxFrameNum  = 1;			    //Ŀǰ����ֻ֧�ֵ�֡
        m_wBitrate = 96;                    //kbps
		TSipAudioCap::Clear();
    }
    
    void SetSampleFreq(emAACSampleFreq emFs)
    {
        m_emSampleFreq= emFs;
    }

    emAACSampleFreq GetSampleFreq() const
    {
        return m_emSampleFreq;
    }

    void SetChnl(emAACChnlCfg emChnl)
    {
        m_emChnlCfg = emChnl;
    }

    emAACChnlCfg GetChnl() const
    {
        return m_emChnlCfg;
    }

    void SetBitrate(u16 wBitrate) 
    {
        m_wBitrate = wBitrate;
    }

    u16 GetBitrate() const
    {
        return m_wBitrate;
    }
};

/*********************����֡�ʵ�����******************
*1��ʾ29.97, 2��ʾ29.97/2, 3��ʾ29.97/3,.....
*H261��cif(1-4) qcif(1-4)
*H263  sqcif,qcif,cif,4cif,16cif  (1-32)
*****************************************************/
//��Ƶ������
struct TSipVideoCap : public TSipCap
{
	u16              m_wMaxBitRate;						//��λkbps
	u8               m_abyResolution[emSipResolutionEnd];	//֡�� 
    EmSipPayloadType m_emPayloadType;
	u16              m_wStaticPayload;
	u16              m_wDynamicPayload;

public:
	TSipVideoCap()
	{
	    Clear();
	}
	void Clear()
	{
		TSipCap::Clear();

		m_wMaxBitRate = 0;
		memset( m_abyResolution, 0, sizeof( m_abyResolution ) );
		m_dwSampleRate   = 90000;
	}

	//��λkbps
	void SetBitRate(u16 wBitRate)
	{
		m_wMaxBitRate = wBitRate;		
	}
	u16 GetBitRate() const
	{
        return m_wMaxBitRate;
	}
	/*
	 *function: ����֧�ֵķֱ��ʡ�֡��
	 *param:	emRes ��ʾ�ֱ��� byMPI��ʾ֡��,�μ��ṹͷ˵��
     *return:   TRUE or FALSE 
	 */
	BOOL SetResolution( EmSipResolution emRes, u8 byMPI )
	{
		if(emRes <= emSipResolutionBegin || emRes >= emSipResolutionEnd)
		{
			return FALSE;
		}
		m_abyResolution[emRes] = byMPI;
	    return TRUE;
	}
    /*
	 *function: �õ�֧�ֵķֱ��ʡ�֡��
	 *param:	emRes ��ʾ�ֱ��� byMPI��ʾ֡��,�μ��ṹͷ˵��
     *return:   ֡��(0 ��ʾ��֧�ָķֱ���)  
	 */
	u8 GetResolution( EmSipResolution emRes ) const
	{
		if(emRes <= emSipResolutionBegin || emRes >= emSipResolutionEnd)
		{
			return 0;
		}
		return m_abyResolution[emRes];
	}
};

//H.264��Ƶ������
/*********************����֡�ʵ�����******************
*1��ʾ1fps, 60����60fps���������֡�ʿ��Դﵽ����ֵ255
*****************************************************/
struct TSipH264VideoCap:public TSipVideoCap
{
public:
    // Э�� 
    enum  emH264ProfileMask
    {
        emProfileBaseline = 64,
        emProfileMain = 32,
        emProfileExtend = 16,
        emProfileHigh = 8
    };

    TSipH264VideoCap();  
    void Clear();
        
	// Э��: ֧�� emH264ProfileMask �������������ǵ��߼���
    void SetSupportProfile(u8 byProfile)
	{
		m_byProfile = byProfile;
// 		if(m_byProfile < 64)
// 			m_byProfile = 64;
	}
	BOOL IsSupportProfile(u8 byReqProfile) const
	{
		return ((m_byProfile&byReqProfile) == byReqProfile);
	}
	
    u8   GetProfileValue() const
    {
        return m_byProfile;
    }
    
    // ����������

     /*
	 *function: ��ȡ�ض��ֱ����µ�֡��
	 *param:	u8 byRes                    �ֱ��ʣ�emResolution ���� emResolutionHD
     *return:   u8 ֡�� frame/s
	 */
    u8   GetResolution(EmSipResolution emRes) const;
    u8   GetResolution(u16 wWidth, u16 wHeight) const;

	/*
	 *function: �ض��ֱ����£��ض�֡��(���ڳ�ģʽ����Ҫ�ϲ�ת��Ϊ֡�ʴ���)�Ƿ�֧��
                ���ڶԶ��Ƿ�֧�ֳ���ʽ��Ҫҵ����� IsSupportProfile �����ж� 
	 *param:	u8 byRes                    �ֱ��ʣ�emResolution ���� emResolutionHD
                u8 byFps                    ֡��frame/s
     *return:   TRUE/FALSE
	 */
    BOOL IsSupport(EmSipResolution emRes, u8 byFps) const;
    BOOL IsSupport(u16 wWidth, u16 wHeight, u8 byFps) const;

	/*
	 *function: ����֧��ĳ�ֱַ��ʺ�֡��(���ڳ�ģʽ����Ҫ�ϲ�ת��Ϊ֡�ʴ���)�����ֱַ��ʿ��Ե�������
	 *param:	u8 byRes                    �ֱ��ʣ�emResolution ���� emResolutionHD
                u8 byFps                    ֡��frame/s
	 */
    void  SetResolution(EmSipResolution emRes, u8 byFps) ;
    void  SetResolution(u16 wWidth, u16 wHeight, u8 byFps) ;

    // �ڲ�ʹ�ú���
    void  SetMaxMBPS(s32 nMax)
    {
        m_nMaxMBPS = nMax;
    }
    s32   GetMaxMBPS() const
    {
        return m_nMaxMBPS;
    }
    void  SetMaxFS(s32 nMax)
    {
        m_nMaxFS = nMax;
    }
    s32   GetMaxFS() const
    {
        return m_nMaxFS;
    }
	void  SetMaxBRandCPB(s32 nMaxBRandCPB)
	{
		m_nMaxBRandCPB = nMaxBRandCPB;
	}
	s32   GetMaxBRandCPB() const
	{
		return m_nMaxBRandCPB;
	}

    //  Level���ⲿ������Ч
    void SetLevel(u8 byLevel)
    {
        m_byLevel = byLevel;
    }
    u8 GetLevel() const
    {
        return m_byLevel;
    }

	s32 GetParaFlag()
	{
		return m_nParaFlag;
	}
    void SetParaFlag(s32 nParaFlag)
    {
        m_nParaFlag = nParaFlag;
    }

    // toolkit: Res enum to width*height
    BOOL  Res2WxH( EmSipResolution emRes, u16 &wWidth, u16 &wHeight) const;

	BOOL operator <= (const TSipH264VideoCap& tH264VideoCap);
	void operator = (const TSipH264VideoCap& tH264VideoCap);
	BOOL operator == (const TSipH264VideoCap& tH264VideoCap);


protected:

    // H.264 �������壬�μ� ITU H.241�ĵ�
    u8              m_byProfile;
    u8              m_byLevel;
    // ����2���ֶΣ�ȡ Custom ��LevelֵĬ�ϵ� max(��λ��Ϊ���)
    s32             m_nMaxMBPS;
    s32             m_nMaxFS;
    // ���±�����Ǿ��� Custom ���ֶΣ���ʱ��֧�����ã�
    s32             m_nMaxDPB;
    s32             m_nMaxBRandCPB;
    s32             m_nMaxStaticMBPS;

	// �����Ǳ�־�ֶ�,�������ƫ����Ӧλ��λ
	s32             m_nParaFlag;
public:
	BOOL32          m_bOld264Level;
	BOOL			m_bUsed;

};


struct TSipDataCap : public TSipCap
{
	u32   m_dwMaxBitRate;					//��λkbps; 

public:
	TSipDataCap()
	{
		Clear();
	}

	void Clear()
	{
		TSipCap::Clear();
		m_dwMaxBitRate = 64;
		m_dwSampleRate = 0;
	}

	//��λkbps
	void SetBitRate(u32 dwBitRate)
	{
		m_dwMaxBitRate = dwBitRate;		
	}
	u32 GetBitRate()
	{
        return m_dwMaxBitRate;
	}		

};

class CBfcpMediaStream
{
public:
	CBfcpMediaStream();
	
	void Clear();

	void operator = (const CBfcpMediaStream& cCopyMedia);
	
	void SetMediaType( EmSipMediaType emMediaType )
	{
		m_emMediaType = emMediaType;
	}

	EmSipMediaType GetMediaType()
	{
		return m_emMediaType;
	}

	void SetBfcpMediaPort( u16 wPort )
	{
		m_wPort = wPort;
	}
	
	u16 GetBfcpMediaPort()
	{
		return m_wPort;
	}

	void SetBfcpFloorcontrolAttr( EmSipFloorcontrolAttr emFloorcontrolAttr )
	{
		m_emFloorcontrolAttr = emFloorcontrolAttr;
	}
	
	EmSipFloorcontrolAttr GetBfcpFloorcontrolAttr()
	{
		return m_emFloorcontrolAttr;
	}

	void SetBfcpSetupAttr( EmSipSetupAttr emSetupAttr )
	{
		m_emSetupAttr = emSetupAttr;
	}

	EmSipSetupAttr GetBfcpSetupAttr()
	{
		return m_emSetupAttr;
	}

	void SetBfcpConnectionAttr( EmSipConnectionAttr emConnectionAttr )
	{
		m_emConnectionAttr = emConnectionAttr;
	}
	
	EmSipConnectionAttr GetBfcpConnectionAttr()
	{
		return m_emConnectionAttr;
	}

	void SetHaveFloorFlag( BOOL bFlag )
	{
		m_bHaveFloor = bFlag;
	}

	s32 GetHaveFloorFlag()
	{
		return m_bHaveFloor;
	}
	
	void SetConfId( s32 nConfId )
	{
		m_nConfId = nConfId;
	}

	s32 GetConfId()
	{
		return m_nConfId;
	}

	void SetUserId( s32 nUserId )
	{
		m_nUserId = nUserId;
	}

	s32 GetUserId()
	{
		return m_nUserId;
	}

	void SetFloorId( s32 nIndex, s32 nFloorId )
	{
		m_anFloorId[nIndex] = nFloorId;
	}

	s32 GetFloorId( s32 nIndex )
	{
		return m_anFloorId[nIndex];
	}

	void SetFloorMedia( s32 nRow, s32 nCol, s32 nMediaId )
	{
		m_anFloorMedia[nRow][nCol] = nMediaId;
	}

	s32 GetFloorMedia( s32 nRow, s32 nCol )
	{
		return m_anFloorMedia[nRow][nCol];
	}

	s32 GetIdleArrayIndex()
	{
		s32 nIndex = -1;
		for ( s32 i = 0; i < MAX_FLOOR_NUM; i++ )
		{
			if ( m_anFloorMedia[i][0] == -1)
			{
				nIndex = i;
				break;
			}
		}

		return nIndex;
	}

	s32 GetArrayIndexAccordFloorId( s32 nFloorId )
	{
		s32 nIndex = -1;
		for ( s32 i = 0; i < MAX_FLOOR_NUM; i++ )
		{
			if ( m_anFloorId[i] == nFloorId )
			{
				nIndex = i;
				break;
			}
		}

		return nIndex;
	}

	s32 GetIdleFloorId()
	{
		s32 j = 0;
		s32 nFloorId = 0;
		for ( s32 i = 0; i < MAX_FLOOR_NUM; i++ )
		{
			for ( j = 0; j < MAX_FLOOR_NUM; j++ )
			{
				if ( m_anFloorId[j] == i + 1 )
				{
					break;
				}
			}
			if ( j == MAX_FLOOR_NUM )
			{
				nFloorId = i + 1;
				break;
			}
		}

		return nFloorId;
	}
	
private:
	EmSipMediaType m_emMediaType;
		
	u16 m_wPort;
	EmSipFloorcontrolAttr m_emFloorcontrolAttr;
	EmSipSetupAttr m_emSetupAttr;
	EmSipConnectionAttr m_emConnectionAttr;
	
	BOOL m_bHaveFloor;
	s32 m_nConfId;
	s32 m_nUserId;
	s32 m_anFloorId[MAX_FLOOR_NUM];
	s32 m_anFloorMedia[MAX_FLOOR_NUM][MAX_MEDIA_NUM_PER_FLOOR];
	
};

class CFeccMediaStream
{
public:
	CFeccMediaStream();
	
	void Clear();

	void operator = (const CFeccMediaStream& cCopyMedia);
	
	void SetMediaType( EmSipMediaType emMediaType )
	{
		m_emMediaType = emMediaType;
	}

	EmSipMediaType GetMediaType()
	{
		return m_emMediaType;
	}
    
	void SetConnectAttribute( emSendRecvAttr emConnectAttr )
	{
		m_emSendRecvAttr = emConnectAttr;
	}

	emSendRecvAttr GetConnectAttribute()
	{
		return m_emSendRecvAttr;
	}
	
	void SetLocalIp( u32 dwIp )
	{
		m_dwLocalIp = dwIp;
	}

	u32 GetLocalIp()
	{
		return m_dwLocalIp;
	}

	void SetLocalSendAddress( u16 wPort )
	{
		m_tLocalSendAddress.m_dwIP = m_dwLocalIp;
		m_tLocalSendAddress.m_wPort = wPort;
	}

	TIPTransAddress* GetLocalSendAddress()
	{
		return &m_tLocalSendAddress;
	}
	
	void SetLocalRecvAddress( u16 wPort )
	{
		m_tLocalRecvAddress.m_dwIP = m_dwLocalIp;
		m_tLocalRecvAddress.m_wPort = wPort;
	}
	
	TIPTransAddress* GetLocalRecvAddress()
	{
		return &m_tLocalRecvAddress;
	}

	void SetRemoteIp( u32 dwIp )
	{
		m_dwRemoteIp = dwIp;
	}
	
	u32 GetRemoteIp()
	{
		return m_dwRemoteIp;
	}

	void SetRemotePort( u16 wPort )
	{
		m_wRemotePort = wPort;
	}
	
	u16 GetRemotePort()
	{
		return m_wRemotePort;
	}

	void SetFeccSampleRate( u16 wSampleRate )
	{
		m_wSampleRate = wSampleRate;
	}
	
	u16 GetFeccSampleRate()
	{
		return m_wSampleRate;
	}

private:
	EmSipMediaType m_emMediaType;
	emSendRecvAttr m_emSendRecvAttr;
	u32 m_dwLocalIp;
	u32 m_dwRemoteIp;
	u16 m_wRemotePort;
	TIPTransAddress	m_tLocalSendAddress;
	TIPTransAddress	m_tLocalRecvAddress;
	u16 m_wSampleRate;
};

//�ŵ�����
class CSipMediaStream 
{       
public:
    enum { emAVCapNum = 20 };

	CSipMediaStream();
	CSipMediaStream( EmSipMediaType emMediaType );

	void operator = (const CSipMediaStream& cCopyMedia);

	void Clear();
	void ClearCapset();

    //����RTP����
	void SetLocalRtp( u16 wPort ) 
	{ 
		m_tLocalRtp.m_dwIP   = m_dwLocalIp;
		m_tLocalRtp.m_wPort  = wPort;
	}
    //�õ�RTP����
	TIPTransAddress& GetLocalRtp() 
	{
		return m_tLocalRtp; 
	}

	void SetRemoteRtp( u32 dwIp, u16 wPort ) 
	{ 
		m_tRemoteRtp.m_dwIP =  dwIp;
		m_tRemoteRtp.m_wPort  =  wPort;
	}

	//�õ�RTP����
	TIPTransAddress& GetRemoteRtp() 
	{
		return m_tRemoteRtp; 
	};

    //����RTCP����
	void SetRecvRtcp( u16 wPort ) 
	{
		m_tRecvRtcp.m_dwIP = m_dwLocalIp;
		m_tRecvRtcp.m_wPort = wPort;
	}
    //�õ�RTCP����
	TIPTransAddress& GetRecvRtcp() 
	{
		return m_tRecvRtcp; 
	}
	
	 //����RTCP����
	void SetSendRtcp( u32 dwIp, u16 wPort ) 
	{
		m_tSendRtcp.m_dwIP = dwIp; 
        m_tSendRtcp.m_wPort = wPort;
	}
    //�õ�RTCP����
	TIPTransAddress& GetSendRtcp() 
	{
		return m_tSendRtcp; 
	}

    //���ü�������
    void SetEncryptType(EmSipEncryptType emType)
	{
		m_emEncryptType = emType; 
	}
    //�õ���������
	EmSipEncryptType GetEncryptType()
	{
		return m_emEncryptType;
	}

	void SetActivePT( EmSipPayloadType  emActivePT )
	{
		m_emActivePT = emActivePT;
	}

	EmSipPayloadType GetActivePT()
	{
		return m_emActivePT;
	}

	void SetMediaType( EmSipMediaType emMediaType )
	{
		m_emMediaType = emMediaType;
	}

	EmSipMediaType GetMediaType()
	{
		return m_emMediaType;
	}
     //��������Ƶ������������
	BOOL AddMedia( EmSipPayloadType emPayloadType, TSipCap *ptCap );
    //��������Ƶ������������
    BOOL GetMedia( EmSipPayloadType emPayloadType, TSipCap **ptCap, u8 byIndex = 0);
	void RemoveAllMedia();

    BOOL IsSupport( EmSipPayloadType emPayloadType, TSipCap *ptCap, s32 nIndex = -1 );

	EmSipPayloadType GetMediaPT( u8 byIndex )
	{
        if ( byIndex < m_byMediaCount )
			return m_aemMediaPT[byIndex];
		else
			return emSipPayloadTypeEnd;
	}

	u8 GetMediaCount() 
	{
		return m_byMediaCount;
	}
    //���ü���ͬ����Ϣ
	void SetEncryptSync( TSipEncryptSync &tSync)
	{ 
		m_tEncryptSync = tSync; 
	}
    //�õ�����ͬ����Ϣ
	TSipEncryptSync &GetEncryptSync() 
	{ 
		return m_tEncryptSync; 
	} 

	void SetBitRate( s32 nRate )
	{
		m_nBitRate = nRate;
		m_tH261Cap.SetBitRate( nRate );
		m_tH263Cap.SetBitRate( nRate );
		m_tH263plusCap.SetBitRate( nRate );
		m_tMpeg4Cap.SetBitRate( nRate );
		m_tH262Cap.SetBitRate( nRate ); 
		for ( s32 i = 0; i < MAX_H264CAP_NUM; i++ )
		{
			if ( m_atH264Cap[i].GetBitRate() == 0 )
			{
				m_atH264Cap[i].SetBitRate( nRate );
			}
		}
	}

	s32 GetBitRate()
	{
		return m_nBitRate;
	}

	void SetLocalIp( u32 dwIp )
	{
		m_dwLocalIp = dwIp;
	}
	u32 GetLocalIp()
	{
		return m_dwLocalIp;
	}

	BOOL IsActive()
	{
        return m_bActive;
	}

	void SetActive( BOOL bActive )
	{
		m_bActive = bActive;
	}
	void SetMediaPTArray( s32 nPos, EmSipPayloadType emSipPT )
	{
		if ( nPos < m_byMediaCount )
		{
			BOOL bFind = FALSE;
			for ( int i = 0; i< emAVCapNum; ++i )
			{
				if( m_aemMediaPT[i] == emSipPT && emSipPT != emH264 )
				{
					bFind = TRUE;
				}
				else
					continue;
			}
			if ( !bFind )
			{
				m_aemMediaPT[nPos] = emSipPT;
			}
		}
	}
	void SetMediaCount( s32 nCount )
	{
		m_byMediaCount = nCount;
	}
	
	s32 GetScreenNo()
	{
		return m_nScreenNum;
	}
	void SetScreenNo( s32 nScreenNo )
	{
		m_nScreenNum = nScreenNo;
	}
	s32 GetCapSignNum()
	{
		return m_nCapSignNum;
	}
	void SetCapSignNum( s32 nCapSignNum )
	{
		m_nCapSignNum = nCapSignNum;
	}
	EmSipCapSign GetCapSign( s32 nIndex = 0 )
	{
		return m_emSipCapSign[nIndex];
	}
	void SetCapSign( EmSipCapSign emCapSign, s32 nIndex = 0 )
	{
		m_emSipCapSign[nIndex] = emCapSign;
	}
	void SetAudMix(BOOL32 bAudMix)
	{
		m_bAudMix = bAudMix;
	}
	BOOL32 IsAudMix()
	{
		return m_bAudMix;
	}
	void SetTpRtpAddress( s32 nIndex, u32 dwIP, u16 wPort ) 
	{ 
		m_tTpRtpAddr[nIndex].m_dwIP = dwIP;
		m_tTpRtpAddr[nIndex].m_wPort = wPort;
	}
	TIPTransAddress& GetTpRtpAddress( s32 nIndex ) 
	{
		return m_tTpRtpAddr[nIndex]; 
	}
	void SetTpRtcpAddress( s32 nIndex, u32 dwIP, u16 wPort ) 
	{ 
		m_tTpRtcpAddr[nIndex].m_dwIP = dwIP;
		m_tTpRtcpAddr[nIndex].m_wPort = wPort;
	}
	TIPTransAddress& GetTpRtcpAddress( s32 nIndex ) 
	{
		return m_tTpRtcpAddr[nIndex]; 
	}

	void SetSipContentAttr( EmSipContentAttr emSipContentAttr)
	{
		m_emSipContent = emSipContentAttr;
	}

	EmSipContentAttr GetSipContentAttr()
	{
		return m_emSipContent;
	}

	void SetSipMediaLabel( s32 nSipMediaLabel )
	{
		m_nSipMediaLabel = nSipMediaLabel;
	}

	s32 GetSipMediaLabel()
	{
		return m_nSipMediaLabel;
	}
	
	void SetH264CapsetNumber( u8 byNum )
	{
		m_byH264CapNum = byNum;
	}
	
	u8 GetH264CapsetNumber()
	{
		return m_byH264CapNum;
	}

	void AddH264CapsetNumber()
	{
		m_byH264CapNum++;
	}

	void SetH264CapsetOrder( s32 nIndex, u8 byOrder )
	{
		m_abyH264CapOrder[nIndex] = byOrder;
	}
	
	u8 GetH264CapsetOrder( s32 nIndex )
	{
		return m_abyH264CapOrder[nIndex];
	}
private:

	BOOL m_bActive;
	EmSipMediaType    m_emMediaType;
  
	TIPTransAddress	  m_tLocalRtp;			
	TIPTransAddress	  m_tRemoteRtp;			
	
	TIPTransAddress	  m_tSendRtcp;   	
	TIPTransAddress   m_tRecvRtcp;

	EmSipPayloadType m_aemMediaPT[emAVCapNum];
	u8 m_byMediaCount;
	u8 m_byH264CapNum;	
	u8 m_abyH264CapOrder[MAX_H264CAP_NUM];

	TSipVideoCap m_tH261Cap;
	TSipVideoCap m_tH263Cap;
	TSipVideoCap m_tH263plusCap;
	TSipVideoCap m_tMpeg4Cap;
    TSipVideoCap m_tH262Cap;    
    TSipH264VideoCap m_atH264Cap[MAX_H264CAP_NUM];

	TSipAudioCap m_tG711u;   
	TSipAudioCap m_tG711a;   
	TSipAudioCap m_tG722;    
	TSipAudioCap m_tG728;	   
	TSipAudioCap m_tG729;
	TSipAudioCap m_tMP3;
	TSipAudioCap m_tG723;


	TAacCap m_taaclc[MAX_AAC_CAP_NUM];     //aaclc����
	u8 m_bylcNum;                          //�����С
	u8 m_bylcMediaToCap[emAVCapNum];	   //�ǵ�ǰm_byMediaCount������ ��Ӧ��aaclc���������
	TAacCap m_taacld[MAX_AAC_CAP_NUM];
	u8 m_byldNum;
	u8 m_byldMediaToCap[emAVCapNum];


	TSipAudioCap m_tG719;
     
	TSipG7231Cap  m_tG7231;
	TSipG7221Cap  m_tG7221;

	TSipDataCap  m_tT120;
	TSipDataCap  m_tH224;

	EmSipPayloadType  m_emActivePT;
        
	EmSipEncryptType m_emEncryptType;	   //��������
	TSipEncryptSync  m_tEncryptSync;       //master�����ô˽ṹ         
	s32 m_nBitRate;
	u32 m_dwLocalIp;
	
	//��������
	s32			 m_nScreenNum;
	s32			 m_nCapSignNum;
	BOOL32       m_bAudMix;        //�Ƿ����
	EmSipCapSign m_emSipCapSign[emSipCapEnd];
	TIPTransAddress	  m_tTpRtpAddr[emSipCapEnd];			
	TIPTransAddress	  m_tTpRtcpAddr[emSipCapEnd];

	//����BFCP�����content��label����
	EmSipContentAttr    m_emSipContent;
	s32                 m_nSipMediaLabel;
};

typedef struct tagMediaLine
{
	emSendRecvAttr emAttr;
	u8			   bySndPos;
	u8             byRcvPos;
}tMediaLine; 

/************************************
* �������ṹ
* Ŀǰ����Ƶ֧��:G711u(64k),G711a(64k),G722(64k),G7231,G728,G729.
* Ŀǰ����Ƶ��һ·֧��:h261,h263,h264,mpeg4,h262
* ��һ·֧��:,h264,h263+  
* 
 *************************************/
class CSipCapSet
{
public:
	enum {  
		MAX_AUDIO_STREAM_COUNT = 6,
		MAX_VIDEO_STREAM_COUNT = 10,
	};
	
	CSipCapSet();

	void Clear( BOOL bOnlyComCap = FALSE );

	/*whether media support some format*/
    BOOL IsSupportCapset( EmSipPayloadType emPayloadType, TSipCap *ptSupportCapset, BOOL bRecv, s32 nVideoSequence=0 );
    
	/*add one format to a media*/
	void AddCapSetToMedia( EmSipPayloadType emPayloadType, TSipCap *ptCap, BOOL bRecv, int nVideoSequence = 0 );
	/*determine which payload to be transmitted*/
	void SetMediaActivePT( EmSipPayloadType emPayloadType, BOOL bRecv, int nVideoSequence = 0  );

	s32 GetVideoSendStreamCount(){ return m_nVideoSendStreamCount;	}
	s32 GetVideoRecvStreamCount(){ return m_nVideoRecvStreamCount;	}

	void SetVideoRecvStreamCount( s32 nCount )
	{
		if ( nCount > MAX_VIDEO_STREAM_COUNT )
		{
			m_nVideoRecvStreamCount = MAX_VIDEO_STREAM_COUNT;
			return;
		}
		m_nVideoRecvStreamCount = nCount;
	}

	void SetVideoSendStreamCount( s32 nCount )
	{
		if ( nCount > MAX_VIDEO_STREAM_COUNT )
		{
			m_nVideoSendStreamCount = MAX_VIDEO_STREAM_COUNT;
			return;
		}
		m_nVideoSendStreamCount = nCount;
	}

	void IncreasingSendVideoStream()
	{ 
		if ( m_nVideoSendStreamCount+1 <= MAX_VIDEO_STREAM_COUNT )
		{
			m_nVideoSendStreamCount++; 
		}
	}
	void IncreasingRecvVideoStream()
	{ 
		if ( m_nVideoRecvStreamCount+1 <= MAX_VIDEO_STREAM_COUNT )
		{
			m_nVideoRecvStreamCount++; 
		}
	}

	s32 GetAudioSendStreamCount(){ return m_nAudioSendStreamCount;	}

	s32 GetAudioRecvStreamCount(){ return m_nAudioRecvStreamCount;	}

	void SetAudioRecvStreamCount( s32 nCount )
	{
		if ( nCount > MAX_AUDIO_STREAM_COUNT )
		{
			m_nAudioRecvStreamCount = MAX_AUDIO_STREAM_COUNT;
			return;
		}
		m_nAudioRecvStreamCount = nCount;
	}
	
	void SetAudioSendStreamCount( s32 nCount )
	{
		if ( nCount > MAX_AUDIO_STREAM_COUNT )
		{
			m_nAudioSendStreamCount = MAX_AUDIO_STREAM_COUNT;
			return;
		}
		m_nAudioSendStreamCount = nCount;
	}

	void IncreasingSendAudioStream()
	{ 
		if ( m_nAudioSendStreamCount+1 <= MAX_AUDIO_STREAM_COUNT )
		{
			m_nAudioSendStreamCount++; 
		}
	}
	void IncreasingRecvAudioStream()
	{ 
		if ( m_nAudioRecvStreamCount+1 <= MAX_AUDIO_STREAM_COUNT )
		{
			m_nAudioRecvStreamCount++; 
		}
	}
	
	u32 GetMediaLinePosbySendPos(u8 bySndPos, BOOL bVideo = TRUE)
	{
		if(bVideo)
		{
			for(u32 dwIndex = 0; dwIndex< m_dwVideoNum; dwIndex++)
			{
				if(m_atVidSndRcv[dwIndex].emAttr == emSendOnly || m_atVidSndRcv[dwIndex].emAttr == emSendRecv)
				{
					if(bySndPos == m_atVidSndRcv[dwIndex].bySndPos )
						return dwIndex;	
				}
			}
		}
		else
		{
			for(u32 dwIndex = 0; dwIndex< m_dwAudioNum; dwIndex++)
			{
				if(m_atAudSndRcv[dwIndex].emAttr == emSendOnly || m_atAudSndRcv[dwIndex].emAttr == emSendRecv)
				{
					if(bySndPos == m_atAudSndRcv[dwIndex].bySndPos )
						return dwIndex;	
				}
			}
		}

		return -1;
	}

	u32 GetMediaLinePosbyRecvPos(u8 byRecvPos, BOOL bVideo = TRUE)
	{
		if(bVideo)
		{
			for(u32 dwIndex = 0; dwIndex< m_dwVideoNum; dwIndex++)
			{
				if(m_atVidSndRcv[dwIndex].emAttr == emRecvOnly || m_atVidSndRcv[dwIndex].emAttr == emSendRecv)
				{
					if(byRecvPos == m_atVidSndRcv[dwIndex].byRcvPos )
						return dwIndex;	
				}
			}
		}
		else 
		{
			for(u32 dwIndex = 0; dwIndex< m_dwAudioNum; dwIndex++)
			{
				if(m_atAudSndRcv[dwIndex].emAttr == emRecvOnly || m_atAudSndRcv[dwIndex].emAttr == emSendRecv)
				{
					if(byRecvPos == m_atAudSndRcv[dwIndex].byRcvPos )
						return dwIndex;	
				}
			}
		}

		
		return -1;
	}

	tMediaLine* GetMediaLine( u32 dwCount , BOOL bIfVideo = FALSE )
	{
		if ( bIfVideo)
		{
			if ( dwCount >= MAX_VIDEO_STREAM_COUNT*2 || dwCount < 0 )
				return NULL;
			else
				return &(m_atVidSndRcv[dwCount]);
		}
		else
		{
			if ( dwCount >= MAX_AUDIO_STREAM_COUNT*2 || dwCount < 0 )
				return NULL;
			else
				return &(m_atAudSndRcv[dwCount]);
		}
	
	}

	BOOL SetMediaLine( u32 dwCount , emSendRecvAttr emAttr , u8 bySndPos , u8 byRcvPos , BOOL bIfVideo = FALSE )
	{
		if ( bIfVideo)
		{
			if ( dwCount >= MAX_VIDEO_STREAM_COUNT*2 || dwCount < 0 )
				return FALSE;
			else{
					m_atVidSndRcv[dwCount].emAttr = emAttr;
					m_atVidSndRcv[dwCount].bySndPos = bySndPos;
					m_atVidSndRcv[dwCount].byRcvPos = byRcvPos;

				}
		}
		else
		{
			if ( dwCount >= MAX_AUDIO_STREAM_COUNT*2 || dwCount < 0 )
				return FALSE;
			else{
					m_atAudSndRcv[dwCount].emAttr = emAttr;
					m_atAudSndRcv[dwCount].bySndPos = bySndPos;
					m_atAudSndRcv[dwCount].byRcvPos = byRcvPos;
				}
		}
		return TRUE;
	}

	BOOL SetAudioNum(u32 AudioNum)
	{
		if ( AudioNum > MAX_AUDIO_STREAM_COUNT*2 || AudioNum < 0 )
			return FALSE;
		m_dwAudioNum = AudioNum;
		return TRUE;
	}
	u32 GetAudioNum()
	{
		return m_dwAudioNum;
	}
	BOOL SetVideoNum(u32 VideoNum)
	{
		if ( VideoNum > MAX_VIDEO_STREAM_COUNT*2 || VideoNum < 0 )
			return FALSE;
		m_dwVideoNum = VideoNum;
		return TRUE;
	}
	u32 GetVideoNum()
	{
		return m_dwVideoNum;
	}

	/*set dialog bandwidth*/
	void SetBandwidth( s32 nBandWidth );
    s32  GetBandwidth();

	void SetLocalIp( u32 dwIp );
	u32  GetLocalIp();

	void SetMediaLocalRtp( EmSipMediaType emMediaType, u16 wRtpPort, BOOL bRecv, int nSequence = 0 );
	TIPTransAddress GetMediaLocalRtp( EmSipMediaType emMediaType, BOOL bRecv, int nSequence=0 );

	void SetMediaRemoteRtp( EmSipMediaType emMediaType, u32 dwIp, u16 wRtpPort, BOOL bRecv, int nSequence = 0 );
	TIPTransAddress GetMediaRemoteRtp( EmSipMediaType emMediaType, BOOL bRecv, int nSequence = 0 );

	void SetMediaSendRtcp( EmSipMediaType emMediaType, u32 dwIp, u16 wPort, BOOL bRecv, int nSequence = 0 );
    TIPTransAddress GetMediaSendRtcp( EmSipMediaType emMediaType, BOOL bRecv, int nSequence = 0 );

	void SetMediaRecvRtcp( EmSipMediaType emMediaType, u16 wRtcpPort, BOOL bRecv, int nSequence = 0 );
	TIPTransAddress GetMediaRecvRtcp( EmSipMediaType emMediaType, BOOL bRecv, int nSequence = 0 );


	/*get some media stream of a dialog*/
	CSipMediaStream* GetSendMediaStream( EmSipMediaType emMediaType, int nSequence = 0 );
	CSipMediaStream* GetRecvMediaStream( EmSipMediaType emMediaType, int nSequence = 0 );
	BOOL SetLocalVedioIP( u32 dwIp, s32 nSequence );
	BOOL SetLocalAudioIP( u32 dwIp, s32 nSequence );

	void SetBfcpMedia( CBfcpMediaStream& tBfcpMedia );
	CBfcpMediaStream* GetBfcpMedia();

	void SetFeccMedia( CFeccMediaStream& tFeccMedia );
	CFeccMediaStream GetFeccMedia();

	void SetSipMsgType( EmSipMsgType emType );
	EmSipMsgType GetSipMsgType();
 
private:

// 	void BuildSendStream( EmSipMediaType emMediaType, CSipMediaStream *pcLocalSendStream, 
// 						 CSipMediaStream *pcPeerRecvStream, CSipMediaStream &cCommonStream );
// 	
//     void BuildRecvStream( EmSipMediaType emMediaType, CSipMediaStream *pcLocalRecvStream, 
// 						 CSipMediaStream *pcPeerSendStream, CSipMediaStream &cCommonStream );

	CSipMediaStream m_atAudioSendStream[MAX_AUDIO_STREAM_COUNT];
	int m_nAudioSendStreamCount;
    CSipMediaStream m_atAudioRecvStream[MAX_AUDIO_STREAM_COUNT];
	int m_nAudioRecvStreamCount;

	tMediaLine m_atAudSndRcv[MAX_AUDIO_STREAM_COUNT*2];
	u32 m_dwAudioNum;

	CSipMediaStream m_atVideoSendStream[MAX_VIDEO_STREAM_COUNT];
	int m_nVideoSendStreamCount;
	CSipMediaStream m_atVideoRecvStream[MAX_VIDEO_STREAM_COUNT];
	int m_nVideoRecvStreamCount;

	tMediaLine m_atVidSndRcv[MAX_VIDEO_STREAM_COUNT*2];
	u32 m_dwVideoNum;
	
	CSipMediaStream m_tFeccSendStream;
	CSipMediaStream m_tFeccRecvStream;

	CBfcpMediaStream m_tBfcpMediaStream;
	CFeccMediaStream m_tFeccMediaStream;

	s32 m_nBandWidth;
	u32 m_dwLocalIp;

	EmSipMsgType m_emSipType;

};

typedef struct tagHostName
{
	EmHostNameType   m_emType;                   //����������
	char             m_achDomainName[LEN_DOMAINNAME+1];//����
	u32              m_dwIpAddr;                   //IP��ַ
}THostName;


#define IsValidHostNameAddr( hostname ) \
( ( hostname.m_emType == emUrlIpv4 && hostname.m_dwIpAddr ) \
	|| ( hostname.m_emType == emUrlDomain && strlen( hostname.m_achDomainName ) ) ) \
	?TRUE:FALSE \
   

typedef struct tagSipUrl
{
	char             m_achDisplayName[LEN_USERNAME+1]; 
	char			 m_achUserName[LEN_USERNAME+1];      //�û���   
	char             m_achPassword[LEN_PASSWORD+1];      //����
    THostName        m_tHostName;                        //������
	u16              m_wPort;                            //�˿�    
public:
	tagSipUrl()
	{
		memset( this, 0, sizeof( tagSipUrl ) );
	}
}TSipUrl;

typedef enum
{
    cmCreate,
    cmJoin,
    cmInvite,
    cmCapabilityNegotiation,
    cmCallIndependentSupplementaryService,
    cmLastCG
} EmConfGoalType;

// ���е�ַ����
enum EmSipCallAddrType
{
	cat_err	= -1,
	cat_ip	= 1,	//IP����
	cat_alias	= 2,	//��������
	cat_e164	= 3,	//E164����
};

//������ַ
typedef struct tagAliasTransAddress
{
	s8  m_achAlias[LEN_ALIAS + 1];			//h323-Id ��������λΪ��
	
	tagAliasTransAddress()
	{
		Clear();
	}
	
	void Clear()
	{
		memset( m_achAlias, 0, sizeof(m_achAlias) );
	}
	
	//���ñ���
	BOOL SetAliasAddr( const s8* pAlias )
	{
		memset( m_achAlias, 0, sizeof(m_achAlias) );
		u16 nLen = min( strlen(pAlias), LEN_ALIAS );
		strncpy( m_achAlias, pAlias, nLen );
		m_achAlias[nLen] = '\0';
		return TRUE;
	}	
	
	//��ñ���
	s8* GetAliasName()  
	{
		return m_achAlias;	
	}
}TAliasTransAddress,*PTAliasTransAddress;

//����ʱ�ı�����ַ
typedef struct tagSipTransAddress
{
	EmSipCallAddrType    m_emType;		//��������
	TIPTransAddress		m_tNetAddr;		//IP����ʱʹ��		
	TAliasTransAddress		m_tAlias;		//��������ʹ��

	tagSipTransAddress()
	{
		Clear();
	}
	void Clear()
	{
		m_emType = cat_err;
		m_tNetAddr.Clear();
		m_tAlias.Clear();
	}

}TSipTransAddress,*PTSipTransAddress;

typedef struct tagTSipPollInfoTP
{
	BOOL bIsPoll;
	u16  wPollExpire;
	
	void Clear()
	{
		memset( this, 0, sizeof(tagTSipPollInfoTP) );
	}
	tagTSipPollInfoTP()
	{
		Clear();
	}
}TSipPollInfoTP;

typedef struct tagTSipConfAuxMixInfoTP
{
	BOOL bStart;
	u16	wConfID;
	u16 wSpeakerIndex;					//�������������
	u16	awList[MAX_SIP_CONF_AUDMIX_NUM_TP];	//����ID
	
	void Clear()
	{
		memset( this, 0, sizeof(tagTSipConfAuxMixInfoTP) );
		wConfID = SIP_INVALID_INDEX_TP;
		bStart = FALSE;
	}
	tagTSipConfAuxMixInfoTP()
	{
		Clear();
	}
}TSipConfAuxMixInfoTP;

//����������Ϣ
typedef struct tagTSipConfInfo
{
	s8	 achConfId[MAX_SIP_CONF_ID_LEN + 1];			// ����ID
	s8	 achConfName[MAX_SIP_CONF_NAME_LEN + 1];		// ������
	s8	 achConfNumber[MAX_SIP_CONF_E164_LEN + 1];	    // �������
	s8	 achConfPwd[MAX_SIP_PASSWORD_LEN + 1];			// ��������
	BOOL bNeedPassword;                             // �Ƿ���Ҫ����
	u16  wConfDuration;							    // �������ʱ��		
	EmSipPayloadType   emVideoFormat;				// ������Ƶ��ʽ(VIDEO_H261��)
	EmSipPayloadType   emAudioFormat;				// ������Ƶ��ʽ(AUDIO_MP3��)
	EmSipResolution  emResolution;					// ������Ƶ�ֱ���(VIDEO_CIF��)
	u8 byProfile;									// ����profile
	u8 byVidMPI;					                // ����֡��
	BOOL bIsAutoVMP;								// �Ƿ��Զ�����ϳ�
	BOOL bIsMix;	    							// �Ƿ����
	EmSipPayloadType	emSecVideoFormat;			// ˫����ʽ
	EmSipResolution emSecVidRes;					// ˫���ֱ���
	u8 bySecProfile;								// ˫��profile
	u8 bySecVidMPI;					                // ˫��֡��
	u16 wCallRate;									// ��������(kbps)
	u16	wDualCallRate;								// ˫����������(kbps)
	TSipPollInfoTP  tPollInfo;
	TSipConfAuxMixInfoTP tConfAudMixInfo;

public:
	tagTSipConfInfo()
	{ 
		Clear();	
	}
	void Clear()
	{
		memset( this, 0, sizeof(tagTSipConfInfo) );
		tPollInfo.Clear();
		tConfAudMixInfo.Clear();
	}

}TSipConfInfo ,*PTSipConfInfo;

//������в���
typedef struct tagSipCallParam 
{
	BOOL	m_bCreateConf;
	EmConfGoalType  m_emConfGoalType;  				  //�����Ŀ������
	u32				 m_dwCallRate;                    //��������	(kbps)
	TSipUrl          m_tCalledAddress;                //���е�ַ
	TSipUrl          m_tCallingAddress;               //���е�ַ
	EmSipCallType    m_emCallType;                    //�������� (direct|by pxy|by redirect)
    THostName        m_tServerAddr;                    //pxy server| redirect server    
	u16              m_wServerPort;
	EmSipConnection  m_emSipConnection;               //������������ tcp udp default tcp
	s32					  m_nProductIdSize;
	u8					  m_abyProductId[MAX_NUM_LEN_VERSION];				//��Ʒ��
	s32					  m_nVerIdSize;
	u8					  m_abyVersionId[MAX_NUM_LEN_VERSION];				//�汾��
	EmSipTerminalType     m_emSipTerType;
	
	//��������
	EmSipLevel	m_emSipLevel;                       //����
	s32	m_nScreenNum;                               //����
	u8	m_abyConfId[LEN_GUID];		                //�����,����16 octet
	u16	m_wConfId;
	u8	m_byTerNum;			//�����ն˸���
	TSipTransAddress	m_atList[MAX_TERMINAL_NUM];	//�����ն��б�
	TSipConfInfo	m_tConfInfo;			        //������Ϣ
	
	BOOL m_bNatCall;	//�����Ƿ��nat
	BOOL m_bAddTpAttr;	//�Ƿ����TP���ԣ�sip��ͷ��sdp��������TP�Ǳ����ԣ�

public:
	tagSipCallParam()
	{
		memset( this, 0, sizeof( tagSipCallParam ) );
		m_emSipConnection = emSipTcpConnection;
	}

	//���û����
	void SetConfId(const u8* pchConfId,u8 byLen)
	{
		if( pchConfId == NULL || byLen <= 0 )
		{
			return;
		}
		
		s32 nReal = min(max(LEN_1, byLen), LEN_GUID);
		memcpy(m_abyConfId, pchConfId, nReal);
	}

}TSipCallParam;

typedef struct tagSipNodeInfo
{
    EmSipVendorId m_emVendorId;
	BOOL       m_bMt;
	char       m_achProductId[SESSION_USERNAME_LEN+1];
	char       m_achVersion[SESSION_VERSION_LEN+1];

	public:	    
	tagSipNodeInfo()
	{ 
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagSipNodeInfo));
	}
}TSipNodeInfo;

typedef struct tagSdpSessionInfo
{
    s8      m_achSessionName[SESSION_NAME_LEN+1];
    //origin
    s8      m_achOriginSID[SESSION_ID_LEN+1];         //SessionId
    s8      m_achOriginUserName[SESSION_USERNAME_LEN+1];    //User name
    //s8      m_achOriginVer[SESSION_VERSION_LEN+1];          //session Version
	int     m_nOriginVer;
    s8      m_achOriginAddress[128];    //Address-url

    s8      m_achTerVer[SESSION_INFO_LEN+1];
    
    u32     m_dwBandWidth;
    u32     m_dwStartTime;
    u32     m_dwEndTime;
    u32     m_dwIP;
public:	    
	tagSdpSessionInfo(){ memset(this, 0, sizeof(tagSdpSessionInfo));}
} TSdpSessionInfo;

enum EmSipEndpointType
{
	emSipEndpointTypeUnknown  = 0, 
		emSipEndpointTypeCNS	     = 0x01,
		emSipEndpointTypeUMS		 = 0x02,
		emSipEndpointTypeRegister = 0x04
};

typedef struct tagSipRegistLocalInfo
{
	EmSipEndpointType  m_emEndpointType;   //������ums��cns
	u32 m_locolIP;                         //����IP��ַ
	s8  m_softversion[LEN_USERNAME+1];     //����汾��
	s8  m_compileTime[LEN_USERNAME+1];     //����ʱ�� 
public:
    tagSipRegistLocalInfo() {memset(this, 0, sizeof(tagSipRegistLocalInfo));}
}TSipRegistLocalInfo, *PTSipRegistLocalInfo;

// typedef struct tagRegisterInfo
// {
// 	u32			dwHostIP;			
// 	u16			wHostPort;  
// 	u32			m_dwExpires;                    
// 	THostName	m_tRegistrar;		  //ע��������Ϣ
// 									  //��ʱʱ��,��λ��
// 	TSipRegistLocalInfo			m_tSipRegLocalInfo;
// };


typedef struct tagRegisterInfo
{
	TSipUrl m_tFromUrl;			//From �ֶ�URL
	TSipUrl m_tToUrl;			//To �ֶ�URL
	THostName m_tRegistrar;		//ע��������Ϣ
	u32 m_dwExpires;			//��ʱʱ��,��λ��
    TSipRegistLocalInfo			m_tSipRegLocalInfo;
	EmSipConnection	m_emConnection;	//ע���ַ����
public:	
	tagRegisterInfo()
	{ 
		memset(this, 0, sizeof(tagRegisterInfo));
		m_emConnection = emSipUdpConnection;
	}
}TRegisterInfo;


typedef struct tagSipRegName
{
	EmHostNameType m_emSipAddrType;
	s8     m_achUserName[LEN_USERNAME+1];     //ע����
	s8     m_achPassword[LEN_PASSWORD+1];	  //ע������
	s8     m_achDisplayName[LEN_USERNAME+1];  //��ʾ����
	
	tagSipRegName()
	{
		memset( this, 0, sizeof(tagSipRegName) );
	}
}TSipRegName,*PTSipRegName;

typedef struct tagRegisterRequest
{
	TSipRegName      m_atSipRegName[MAX_NUM_REGNAME_SIZE];
	s32				 m_nSipRegArraySize;
	
	TIPTransAddress  m_atContactAddr[MAX_NUM_CONTACT_ADDR];//ע���ַ
	
	u32 m_dwExpires;//��ʱʱ��,��λ��
	char m_aCallId[MAX_NUM_CALLID];//����ID
	s32 m_nCSqence;//���к� //m_tRegistrar m_dwExpires m_aCallId m_nCSqence ��Ҫҵ��㱣�棬�Ա��ѯ
	EmSipConnection emSipConnection;
    TSipRegistLocalInfo  m_tLocalInfo; 

public:
	tagRegisterRequest()
	{ 
		memset(this , 0 , sizeof(tagRegisterRequest));
		emSipConnection = emSipTcpConnection;
	}
}RegisterRequest;

typedef struct tagRegisterResponse
{
	TIPTransAddress  m_tContactAddr;
	EmSipConnection emSipConnection;
	BOOL32 bSerchPrefix;        //�ж�regserver�Ƿ�����ǰ׺���ң������ǰ׺���ң��ظ���300�оͽ�achAliasд�뵽contact��ַ��
	s8 achAlias[LEN_USERNAME+1];
public:
	tagRegisterResponse()
	{
		memset(this , 0 , sizeof(tagRegisterResponse));
		emSipConnection = emSipTcpConnection;
	}
}RegisterResponse;

typedef struct tagRegClient
{
	RvSipRegClientHandle   m_hRegClient;
	EmRegState             m_emRegState;
	s32					   m_nAppHandle;
}TRegClient,*PTRegClient;
/*   
 *   h.281 encoded in host bit order:
 *   +-------+---------+--------+---------+--------+---------+--------+---------+
 *   +   P   | R=1/L=0 |    T   | U=1/D=0 |    Z   | I=1/O=0 |    F   | I=1/O=0 |
 *   +-------+---------+--------+---------+--------+---------+--------+---------+
 */
enum EmFeccAction
{
	emActionInvalid				    = 0,  
	emActionStart					= 0x01,  //��ʼ
	emActionContinue				= 0x02,  //����
	emActionStop					= 0x03,  //ֹͣ
	emActionSelectVideoSource		= 0x04,  //ѡ����ƵԴ
	emActionVideoSourceSwitched	    = 0x05,  //�л���ƵԴ
	emActionStoreAsPreset			= 0x06,  //�洢Ԥ��λ
	emActionActivatePreset	    	= 0x07,  //�ָ���Ԥ��λ
	emActionAutoFocus				= 0x11,  //�Զ�����
};


//PTFZ codes, parameters for action Start, continue and stop.
enum EmFeccPTFZRequest
{
	emRequestInvalid				= 0,
	emRequestPanLeft				= 0x80,	//�����ƶ�
	emRequestPanRight				= 0xc0,	//�����ƶ�
	emRequestTiltUp			    	= 0x30,	//�����ƶ�
	emRequestTiltDown				= 0x20,	//�����ƶ�
	emRequestFocusIn				= 0x03,	//����
	emRequestFocusOut				= 0x02,	//Զ��
	
	emRequestZoomIn				    = 0x0c,	//��Ұ��С
	emRequestZoomOut				= 0x08,	//��Ұ���

	emRequestBrightnessUp			= 0x01,	//���ȼ�(nonstandard)
	emRequestBrightnessDown		    = 0x04  //���ȼ�(nonstandard)
};



//for tanderg
enum EmFeccVideoSourceNumber
{
    emVideoSourceDefault               = 0,    //��ǰ��ƵԴ
    emVideoSourceMainCamera            = 1,    //����ƵԴ
    emVideoSourceAuxCamera             = 2,    //������ƵԴ
    emVideoSourceDocCamera             = 3,    //�ļ�չʾ̨
    emVideoSourceAuxDocCamera          = 4,    //�����ļ�չʾ̨������̩��Ϊvcr
    emVideoSourceVideoPlaybackSource   = 5,    //vcr������̩��ΪPC
};

enum EmSipLogModule
{
	emSipMdlBegin,
	emSipMdlNone = emSipMdlBegin,
	emSipMdlAll,
	emSipMdlAllExceptFrequent,
	emSipMdlCall,
	emSipMdlCap,
	emSipMdlChannel,
	emSipMdlConf,
	emSipMdlRegister,
	emSipMdlFrequent,
	emSipMdlEnd = 30,
};
enum EmSipLogType
{
	emSipLogBegin,
		emSipLogNormal,
		emSipLogWarning,
		emSipLogError,
};

//�ն˱�Ų���
typedef struct tagTerLabel 
{
	u8 m_byMcuNo;
	u8 m_byTerNo;

	tagTerLabel()
	{
		Clear();		
	}

	void Clear()
	{
		m_byMcuNo = 0xff;
		m_byTerNo = 0xff;
	}

    //��Ч�Լ��
	bool IsValid()
	{
		return ( m_byMcuNo < LEN_MAXMT_NUM && m_byTerNo < LEN_MAXMT_NUM);
	}
    
    //����TerminalLabel
	BOOL SetTerLabel( u8 byMcuNo, u8 byTerNo )
	{
		if( byMcuNo < LEN_MAXMT_NUM && byTerNo < LEN_MAXMT_NUM )
		{
			m_byMcuNo = byMcuNo;
			m_byTerNo = byTerNo;
            return TRUE;
		}
        return FALSE;
	}
    //��ȡTerminalLabel
	void GetTerLabel( u8 *pMcuNo, u8 *pTerNo )
	{
		*pMcuNo = m_byMcuNo;
		*pTerNo = m_byTerNo;
	}
    //��ȡmcu���
	u8 GetMcuNo()
	{
		return m_byMcuNo;
	}
    //��ȡ�ն˱��
	u8 GetTerNo()
	{
		return  m_byTerNo;
	}
}TTerLabel,*PTTerLabel;

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
}TFeccInfo, *PTFeccInfo;

typedef struct tagSipFlowCtrl
{
	s32   m_nChannelId;
	u16   m_wBitRate;
	tagSipFlowCtrl()
	{
		m_nChannelId = -1;
		m_wBitRate = 0;
	}
}TSipFlowCtrl,*PTSipFlowCtrl;

enum EmSipAliasType
{
	sip_Alias_Unknow,
		sip_Alias_e164,
		sip_Alias_h323,
		sip_Alias_IP,
};

typedef struct tagTSipAlias
{
	EmSipAliasType	m_byType;
	s8				m_abyAlias[LEN_USERNAME + 1];
    tagTSipAlias()
	{
		memset( this, 0, sizeof(tagTSipAlias) );
	}
}TSipAlias;

enum EmSipGetRegInfoType
{
	emSipGetRegInfoType_CNS = 0,
		emSipGetRegInfoType_UMS,
		emSipGetRegInfoType_ALL
};

typedef struct tagSipGetRegInfo
{
	EmSipGetRegInfoType emType;
	u32    dwRegIP;         //ע�������IP��ַ
	u16    wRegPort;        //ע��������˿�
	u32    dwLocalIP;       //����ip��ַ  
	u16    wLocalPort;     //���ض˿�
	tagSipGetRegInfo()
	{
		memset( this, 0, sizeof(tagSipGetRegInfo) );
	}
}TSipGetRegInfo;



typedef struct tagTSipRegPackInfo
{
	u16 m_wPackSeq;       //����ţ���1��ʼ��0Ϊ��Чֵ
	u16 m_wTotalPackNum;  //������
	tagTSipRegPackInfo()
	{
		m_wPackSeq = 0;
		m_wTotalPackNum = 0;
	}
	
}TSipRegPackInfo, *PTSipRegPackInfo;

typedef struct tagTSipRegInfo
{
	u16		   m_wAliasNum;
	TSipAlias  m_atAlias[MAX_NUM_REGNAME_SIZE];       //��ʱ��Ϊ���ֵΪ64������Ϊһ������
	EmSipEndpointType m_emSelfType;                   //ע�᷽ ��ϵͳ����(UMS��CNS)    

	tagTSipRegInfo()
	{
		m_wAliasNum = 0;
		memset( m_atAlias, 0, sizeof( m_atAlias ) );
		m_emSelfType = emSipEndpointTypeUnknown;
	}
	
}TSipRegInfo;

typedef struct tagTSipRegPackXml
{
	TSipRegPackInfo tPackInfo;
	EmSipGetRegInfoType emType;
	TSipRegInfo  tRegInfo;

	tagTSipRegPackXml()
	{
		emType = emSipGetRegInfoType_ALL;
	}
}TSipRegPackXml;

typedef struct tagTSipRegInfoUms
{
	u16		   m_wAliasNum;
	TSipAlias  m_atAlias[MAX_NUM_REGNAME_SIZE];       //��ʱ��Ϊ���ֵΪ64������Ϊһ������
	TIPTransAddress  m_atContactAddr[MAX_NUM_CONTACT_ADDR];//ע���ַ
	u32 m_dwExpires;//��ʱʱ��,��λ��
	EmSipConnection emSipConnection;
	TSipRegistLocalInfo m_tSipRegistLocalInfo;
	
	tagTSipRegInfoUms()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTSipRegInfoUms));
	}
	
}TSipRegInfoUms;

typedef struct tagTSipRegInfoCns
{
	u16		   m_wAliasNum;
	TSipAlias  m_atAlias[MAX_NUM_REGNAME_SIZE_CNS];       //��ʱ��Ϊ���ֵΪ64������Ϊһ������
	TIPTransAddress  m_atContactAddr[MAX_NUM_CONTACT_ADDR];//ע���ַ
	u32 m_dwExpires;//��ʱʱ��,��λ��
	EmSipConnection emSipConnection;
	TSipRegistLocalInfo m_tSipRegistLocalInfo;
	
	tagTSipRegInfoCns()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTSipRegInfoCns));
	}
	
}TSipRegInfoCns;

typedef struct tagTSipRegPackXmlB2
{
	TSipRegPackInfo tPackInfo;
	EmSipGetRegInfoType emType;
	EmSipEndpointType  emEndpointType;
	u16	wTotalRegInfo;
	tagTSipRegPackXmlB2()
	{
		emType = emSipGetRegInfoType_ALL;
		wTotalRegInfo = 0;
	}
}TSipRegPackXmlB2;


// typedef struct tagUMSRegistration
// {
// // 	BOOL          m_bRegistration;//TRUE ע�� FALSEȡ��ע��
// // 	BOOL		  m_bExpireAll;//ȡ��ע��ʱ��������ƥ���������Ŀȫ������
// 	RegisterRequest m_tRegReq;//ע����Ϣ
// 	CSipCapSet	  m_tTPCNSCapSet;//ע��������
// 	tagUMSRegistration()
// 	{
// 		Clear();
// 	}
// 	void Clear()
// 	{
// 		memset(this , 0 , sizeof(this));
// 	}
// }TUMSRegistration,*PTUMSRegistration;

RV_DECLARE_HANDLE(RvSipAppChanHandle);
RV_DECLARE_HANDLE(RvSipChanHandle);
RV_DECLARE_HANDLE(RvSipAppRASHandle);
RV_DECLARE_HANDLE(RvSipRASHandle);


/*====================================================================
������      : NotifyNewCallT
����        : �������о��
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: hsCall   - Э��ջ���о��
    		  lphaCall - Ӧ�ó�����о��
����ֵ˵��  : �ɹ� - cb_ok
              ʧ�� - cb_err
====================================================================*/
typedef s32 (RVCALLCONV* NotifyNewCallT)( RvSipCallLegHandle hsCall, LPRvSipAppCallLegHandle lphaCall, const void* pBuf,u16 nBufLen);


/*====================================================================
������      : NotifyCallCtrlMsgT
����        : ���п���֪ͨ����
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: haCall  - Ӧ�ó�����о��
			  hsCall  - Э��ջ���о��
			  msgType - ��Ϣ����
			  pBuf    - ����������
			  nBufLen - ��������
����ֵ˵��  : �ɹ� - cb_ok
              ʧ�� - cb_err
====================================================================*/
typedef s32 (RVCALLCONV* NotifyCallCtrlMsgT)(RvSipAppCallLegHandle haCall,RvSipCallLegHandle hsCall,u16 msgType,
											  const void* pBuf,u16 nBufLen);

/*====================================================================
������      : NotifyChanCtrlMsgT
����        : �ŵ�����֪ͨ����
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: haCall  - Ӧ�ó�����о��
              hsCall  - Э��ջ���о��
              haChan  - Ӧ�ó����ŵ����
			  hsChan  - Э��ջ�ŵ����
			  msgType - ��Ϣ����
			  pBuf    - ����������
			  nBufLen - ��������
����ֵ˵��  : �ɹ� - cb_ok
              ʧ�� - cb_err
====================================================================*/
typedef s32 (RVCALLCONV* NotifyChanCtrlMsgT)(RvSipAppCallLegHandle haCall,RvSipCallLegHandle hsCall,
											 RvSipAppChanHandle haChan,RvSipChanHandle hsChan,
											 u16 msgType,const void* pBuf,u16 nBufLen);

/*====================================================================
������      : NotifyConfCtrlMsgT
����        : �������֪ͨ����
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: haCall  - Ӧ�ó�����о��
              hsCall  - Э��ջ���о��
			  msgType - ��Ϣ����
			  pBuf    - ����������
			  nBufLen - ��������
����ֵ˵��  : �ɹ� - cb_ok
              ʧ�� - cb_err
====================================================================*/
typedef s32 (RVCALLCONV* NotifyConfCtrlMsgT)(RvSipAppCallLegHandle haCall,RvSipCallLegHandle hsCall,
											 RvSipTranscHandle hTransc,u16 msgType,const void* pBuf,u16 nBufLen);
/*====================================================================
������      : NotifyRasCtrlMsgT
����        : RAS��Ϣ֪ͨ����
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: haCall  - Ӧ�ó�����о��
              hsCall  - Э��ջ���о��
              haRas   - Ӧ�ó���RAS���
			  hsRas   - Э��ջRAS���
			  msgType - ��Ϣ����
			  pBuf    - ����������
			  nBufLen - ��������
����ֵ˵��  : �ɹ� - cb_ok
              ʧ�� - cb_err
====================================================================*/
typedef s32 (RVCALLCONV* NotifyRegCtrlMsgT)(IN  RvSipAppRegClientHandle         hAppRegClient,
											IN  RvSipRegClientHandle            hRegClient,
                                            u16 msgType, const void* pBuf,u16 nBufLen);

/*====================================================================
������      : NotifyFeccMsgT
����        : H.224, H.281���ܻص�����
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: hsCall     - Э��ջ���о��
              hsChan     - Э��ջ�ŵ����
			  feccStruct - Զң����(TFeccStruct)
			  terSrc     - Դ���ն��б�
			  terDst     - Դ���ն��б�
����ֵ˵��  : �ɹ� - cb_ok
              ʧ�� - cb_err
====================================================================*/
typedef s32 (RVCALLCONV *NotifyFeccMsgT)( RvSipCallLegHandle hsCall, TFeccInfo feccStruct, TTerLabel terSrc, TTerLabel terDst);

/*====================================================================
������      : NotifyUMSCtrlMsgT
����        : UMS��Ϣ֪ͨ����
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: RvSipTranscHandle  - Ӧ�ó�����о��
              hsCall  - Э��ջ���о��
              haRas   - Ӧ�ó���RAS���
			  hsRas   - Э��ջRAS���
			  msgType - ��Ϣ����
			  pBuf    - ����������
			  nBufLen - ��������
����ֵ˵��  : �ɹ� - cb_ok
              ʧ�� - cb_err
====================================================================*/
typedef s32 (RVCALLCONV* NotifyUMSCtrlMsgT)(IN RvSipTranscHandle hTransc, u16 msgType, const void* pBuf, u16 nBufLen);
//�ص�����ָ��ṹ
typedef struct 
{
	NotifyRegCtrlMsgT	fpRegCtrlMsg;
    NotifyNewCallT		fpNewCall;
	NotifyCallCtrlMsgT  fpCallCtrlMsg;
    NotifyChanCtrlMsgT  fpChanCtrlMsg;
	NotifyFeccMsgT      fpFeccCtrlMsg;
	NotifyConfCtrlMsgT  fpConfCtrlMsg;
	NotifyUMSCtrlMsgT   fpUMSCtrlMsg;
}SIPEVENT,*LPSIPEVENT;

class CMediaStreamCtrl;

class CSipInterface
{
public:
   /*====================================================================
   ��	 ��   ��: SipAdapterInit
   ��	      ��: ��ʼ��Sip����ģ��
   �� �� ʵ  ��: 
   ����ȫ�ֱ���: 
   �������˵��: tSipAdapterCfg 

   ��   ��   ֵ: �ɹ� - &g_hApp
   ʧ�� - NULL		
	====================================================================*/
    static RvStatus AdapterInit( TSipAdapterCfg tSipAdapterCfg );
	
	/*====================================================================
	��	 ��   ��: SipAdapterQuit
	��	      ��: �˳�SIP����ģ��
	�� �� ʵ  ��: 
	����ȫ�ֱ���: ��
	�������˵��: ��
	��   ��   ֵ: ��
	====================================================================*/
    static void AdapterQuit();

	/*====================================================================
	��	 ��   ��: SetSipAppCallBack
	��	      ��: ע��Ӧ�ûص�����
	�� �� ʵ  ��: 
	����ȫ�ֱ���: ��
	�������˵��: lpEvent - �ص������ṹָ��
	��   ��   ֵ: �ɹ� - act_ok
	ʧ�� - act_err
	====================================================================*/
	static void  SetAppCallBack(IN LPSIPEVENT lpEvent);

	/*====================================================================
	��	 ��   ��: SipCheckMessage
	��	      ��: �����Ϣ
	�� �� ʵ  ��: 
	����ȫ�ֱ���: ��
	�������˵��: u32 - ����ʱ��(����)
	��   ��   ֵ: �ɹ� - act_ok
	ʧ�� - act_err
	====================================================================*/
	static void CheckMessage( u32 dwMiliSecond );



	/*====================================================================
	��	 ��   ��: CreateNewCall
	��	      ��: �����µĺ��У������ڷ��ͺ�����Ϣǰ����,�����ȴ����ٺ���
	�� �� ʵ  ��: 
	����ȫ�ֱ���: ��
	�������˵��: lpEvent - �ص������ṹָ��
	��   ��   ֵ: �ɹ� - act_ok
	ʧ�� - act_err
	====================================================================*/
	static RvStatus CreateNewCall(IN RvSipAppCallLegHandle haCall, OUT LPRvSipCallLegHandle lphsCall );

	/*====================================================================
	��	 ��   ��: CreateNewChan
	��	      ��: �����µ�ͨ�������߼�ǰ�ȴ���
	�� �� ʵ  ��: 
	����ȫ�ֱ���: ��
	�������˵��: lpEvent - �ص������ṹָ��
	��   ��   ֵ: �ɹ� - act_ok
	ʧ�� - act_err
	====================================================================*/
	static RvStatus CreateNewChan( IN RvSipCallLegHandle hsCall, IN RvSipAppChanHandle haChan, 
	 	                      IN EmSipMediaType emMediaType, IN BOOL bSend, OUT LPRvSipChanHandle lphsChan );
	
	
	/*====================================================================
	��	 ��   ��: ReleaseChan
	��	      ��: �ͷ�һ��ͨ��
	�� �� ʵ  ��: 
	����ȫ�ֱ���: ��
	�������˵��: lpEvent - �ص������ṹָ��
	��   ��   ֵ: �ɹ� - act_ok
	ʧ�� - act_err
	====================================================================*/
	static RvStatus ReleaseChan(IN RvSipCallLegHandle hsCall, IN RvSipChanHandle hsChan );
	
	/*====================================================================
	��	 ��   ��: SendCallCtrlMsg
	��	      ��: ���ͺ��п�����Ϣ
	�� �� ʵ  ��: 
	����ȫ�ֱ���: ��
	�������˵��: hsCall  - ���о��
	msgType - ��Ϣ����
	pBuf    - ����������
	nBufLen - ��������
	��   ��   ֵ: �ɹ� - act_ok
	ʧ�� - act_err
	====================================================================*/
	static RvStatus SendCallCtrlMsg( RvSipCallLegHandle hsCall, u16 msgType, const u8* pBuf, u16 nBufLen );
	

	/*====================================================================
	��	 ��   ��: SendChanCtrlMsg
	��	      ��: �����ŵ�������Ϣ
	�� �� ʵ  ��: 
	����ȫ�ֱ���: ��
	�������˵��: hsChan  - �ŵ����
	msgType - ��Ϣ����
	pBuf    - ����������
	nBufLen - ��������
	��   ��   ֵ: �ɹ� - act_ok
	ʧ�� - act_err
	====================================================================*/
	static RvStatus SendChanCtrlMsg( RvSipCallLegHandle hsCall, IN RvSipChanHandle hsChan, 
		                        IN EmSipChanCtrlMsgType emMsgType, IN const u8* pBuf,IN u16 nBufLen );

	/*====================================================================
	��	 ��   ��: SetSdpSession
	��	      ��: sdp session info
	�� �� ʵ  ��: 
	����ȫ�ֱ���: ��
	�������˵��: hsCall  - ���о��
	              msgType - ��Ϣ����
	              pBuf    - ����������
	              nBufLen - ��������
	��   ��   ֵ: �ɹ� - act_ok
	ʧ�� - act_err
	====================================================================*/
	static void SetSdpSession( RvSipCallLegHandle hsCall, char* pchSessionName, 
					           u32 dwStartTime, u32 dwStopTime );

	/*====================================================================
	��	 ��   ��: SendRegCtrlMsg
	��	      ��: �����ŵ�������Ϣ
	�� �� ʵ  ��: 
	����ȫ�ֱ���: ��
	�������˵��: hsChan  - �ŵ����
	msgType - ��Ϣ����
	pBuf    - ����������
	nBufLen - ��������
	��   ��   ֵ: �ɹ� - act_ok
	ʧ�� - act_err
	====================================================================*/
	static RvStatus SendRegCtrlMsg( IN EmSipRegCtrlMsgType emMsgType, IN const u8* pBuf,IN u16 nBufLen );
	


	/*====================================================================
	��	 ��   ��: OpenFeccChannel
	��	      ��: ��h224ͨ��
	�� �� ʵ  ��: 
	����ȫ�ֱ���: 
	�������˵��: hsCall - �Ի����
                  bSend  - ����/����
	��   ��   ֵ: �ɹ� - 
	ʧ�� - С��0
	====================================================================*/
	static RvStatus OpenFeccChannel(IN RvSipCallLegHandle hsCall, const void* pBuf, u16 nBufLen);

	/*====================================================================
	��	 ��   ��: CloseFeccChannel
	��	      ��: �ر�h224ͨ��
	�� �� ʵ  ��: 
	����ȫ�ֱ���: 
	�������˵��: hsCall - �Ի����
                  bSend  - ����/����
	��   ��   ֵ: �ɹ� - 
	ʧ�� - С��0
	====================================================================*/
	static RvStatus CloseFeccChannel(IN RvSipCallLegHandle hsCall, BOOL bSend  );

	/*====================================================================
	��	 ��   ��: FeccBind
	��	      ��: �������а�Զң���󣬵�Ե����ʱ�����
	�� �� ʵ  ��: 
	����ȫ�ֱ���: ��
	�������˵��: hsChan	 - h224ͨ�����
	localTer   - �����ն��б�(TTERLABEL)
	remoteTer  - Զ���ն��б�(TTERLABEL)
	��   ��   ֵ: �ɹ� - 
	ʧ�� - С��0
	====================================================================*/
	static RvStatus FeccBind( IN RvSipCallLegHandle hsCall, IN TTerLabel tSrcLabel, IN TTerLabel tDstLabel );
		
	/*====================================================================
	��	 ��   ��: SendFeccMsg
	��	      ��: ����Զң��Ϣ
	�� �� ʵ  ��: 
	����ȫ�ֱ���: ��
	�������˵��: hsChan  - �ŵ����
	msgType - ��Ϣ����
	pBuf    - ����������
	nBufLen - ��������
	��   ��   ֵ: �ɹ� - act_ok
	ʧ�� - act_err
	====================================================================*/
	static RvStatus SendFeccMsg( IN RvSipCallLegHandle hsCall, IN TFeccInfo feccStruct );

	/*====================================================================
	��	 ��   ��: NotifyFeccMsg
	��	      ��: Զң��Ϣ���
	�� �� ʵ  ��: 
	����ȫ�ֱ���: ��
	�������˵��: hsCall  - �ŵ����
	              feccStruct - ��Ϣ����
	              terSrc    - ����������
	              terDst - ��������
	��   ��   ֵ: �ɹ� - act_ok
	ʧ�� - act_err
	====================================================================*/
	static RvStatus RVCALLCONV NotifyFeccMsg( RvSipCallLegHandle hsCall, TFeccInfo feccStruct, TTerLabel terSrc, TTerLabel terDst); 



	static u16 GetPayload( EmSipPayloadType emPt );

	static RvStatus SendConfCtrlMsg( IN RvSipCallLegHandle hsCall, IN RvSipTranscHandle hTransc, IN EmSipConfCtrlMsgType emMsgType, IN const u8* pBuf,IN u16 nBufLen );

	static RvStatus SendUMSCtrlMsg( IN RvSipTranscHandle hTransc, IN EmSipUMSCtrlMsgType emMsgType, IN const u8* pBuf,IN u16 nBufLen );

	static RvStatus SetAppHanleToUMS( void *pAppHandle );

	static RvStatus SetAppHanleToCall(IN  RvSipCallLegHandle     hCallLeg,
                                      IN  RvSipAppCallLegHandle  hAppCallLeg);

	static void SetInterworking(BOOL32 bInter); //sipadapter�Ƿ�����interworking�У����򲻷���option��ѯע������

	static s32 OnCreateSipRegister(IN  RvSipAppRegClientHandle hAppRegClient, OUT LPRvSipRegClientHandle lphRegClient);

	static char* GetMediaName( EmSipPayloadType emPayLoadType );
	static char* GetResolutionName( EmSipResolution emResType );
	static EmSipPayloadType GetPayloadByName( char *pchName );
	static EmSipResolution GetResolutionByName( char *pchName );
private:

		/*set stack callback*/
    static void SipAppSetCallBack();
	 //callback  function
	static SIPEVENT    m_tEventProcess;

   /*Handle to the stack manager. This parameter is returned when calling
    RvSipStackConstruct. You should supply this handle when using the stack
	manager API functions.*/
	static RvSipStackHandle      m_hStackMgr;
	
	/*Handle to the call-leg manager. You can get this handle by calling
	RvSipStackGetCallLegMgrHandle. You should supply this handle when
	using the call-leg manager API functions.*/
	static RvSipCallLegMgrHandle m_hCallLegMgr;
	
	/*Handle to the log-module. You can get this handle by calling
	RvSipStackGetLogHandle. You need this value in order to construct the application
	memory pool.*/
    static RV_LOG_Handle         m_hLog;;
	
	/*Handle to the application memory pool. The application should construct its own
	memory using rpool API. The pool is needed for encoding messages or message
	parts. (See AppPrintMessage() )*/
	static HRPOOL                m_appPool;

	/*Handle to the Authenticator manager. This value is returned when calling
  RvSipStackGetAuthenticationHandle. You should supply this handle when using the
  Authenticator manager API functions.*/
   static RvSipAuthenticatorHandle m_hAuthenticatorMgr;
   static s8 	 m_achAuthenUserName[LEN_USERNAME+1];      //��֤�û���
   static s8     m_achAuthenPassword[LEN_PASSWORD+1];      //��֤����

    //call operation
    static s32 OnMakeCall( RvSipCallLegHandle hsCall, const void* pBuf,u16 nBufLen );
    static s32 OnAcceptCall( RvSipCallLegHandle hsCall, const void* pBuf,u16 nBufLen );
	static s32 OnCallDisConnect( RvSipCallLegHandle hsCall, const void* pBuf,u16 nBufLen );

// 	//call ctrl 
//     static int OnSendConfCtrlMsg( IN RvSipCallLegHandle hsCall, SipChanCtrlMsgType emMsgType );

	//dual operation
	static int OnOpenDual( IN RvSipCallLegHandle hsCall, const void* pBuf, u16 wBufLen );
	static int OnAcceptOpenDual( IN RvSipCallLegHandle hsCall, const void* pBuf, u16 wBufLen );
    static int OnRejectOpenDual( IN RvSipCallLegHandle hsCall, const void* pBuf, u16 wBufLen );
    static int OnCloseDual( IN RvSipCallLegHandle hsCall, const void* pBuf, u16 wBufLen );
    static int OnAcceptCloseDual( IN RvSipCallLegHandle hsCall, const void* pBuf, u16 wBufLen );	
	
	/*incoming call callback*/
    static void RVCALLCONV AppCallLegCreatedEvHandler(IN  RvSipCallLegHandle     hCallLeg,
		                                              OUT RvSipAppCallLegHandle  *phAppCallLeg);
	
	/*call status change callback*/
	static void RVCALLCONV AppCallLegStateChangedEvHandler( IN  RvSipCallLegHandle hCallLeg,
		                                                    IN  RvSipAppCallLegHandle  hAppCallLeg,
		                                                    IN  RvSipCallLegState      eState,
		                                                    IN  RvSipCallLegStateChangeReason eReason);
	
	/*dual status change callback*/
	static void RVCALLCONV AppCallLegModifyStateChangedEvHandler( IN  RvSipCallLegHandle hCallLeg,
		                                                          IN  RvSipAppCallLegHandle   hAppCallLeg,
		                                                          IN  RvSipCallLegModifyState eState,
		                                                          IN  RvSipCallLegStateChangeReason eReason);
	
	static RvStatus RVCALLCONV AppCallLegMsgToSendEvHandler( IN  RvSipCallLegHandle          hCallLeg,
		                                          IN  RvSipAppCallLegHandle       hAppCallLeg,
 		                                          IN  RvSipMsgHandle              hMsg);
	
	static RvStatus RVCALLCONV AppCallLegMsgReceivedEvHandler( IN  RvSipCallLegHandle       hCallLeg,
		                                                       IN  RvSipAppCallLegHandle    hAppCallLeg,
		                                                       IN  RvSipMsgHandle           hMsg);

	/*call ctrl incoming callback*/
	static void  RVCALLCONV AppCallLegTranscCreatedEvHandler( IN  RvSipCallLegHandle            hCallLeg,
                                                              IN  RvSipAppCallLegHandle         hAppCallLeg,
                                                              IN  RvSipTranscHandle             hTransc,
                                                              OUT RvSipAppTranscHandle          *hAppTransc,
                                                              OUT RvBool                       *bAppHandleTransc);

	static void RVCALLCONV AppCallLegTranscStateChangedEvHandler(	IN  RvSipCallLegHandle    hCallLeg,
		                                                IN  RvSipAppCallLegHandle hAppCallLeg,
		                                                IN  RvSipTranscHandle     hTransc,
		                                                IN  RvSipAppTranscHandle  hAppTransc,
		                                                IN  RvSipCallLegTranscState  eTranscState,
		                                                IN  RvSipTransactionStateChangeReason eReason);
/*register status change callback */
    static void RVCALLCONV AppRegClientStateChangedEvHandler(
                           IN  RvSipRegClientHandle            hRegClient,
                           IN  RvSipAppRegClientHandle         hAppRegClient,
                           IN  RvSipRegClientState             eState,
                           IN  RvSipRegClientStateChangeReason eReason);

    static RvStatus RVCALLCONV AppRegClientMsgReceivedEvHandler(
                           IN  RvSipRegClientHandle          hRegClient,
                           IN  RvSipAppRegClientHandle       hAppRegClient,
                           IN  RvSipMsgHandle                hMsg);

	static void RVCALLCONV AppAuthenticationMD5Ev(IN  RvSipAuthenticatorHandle  hAuthenticator,
                                              IN  RvSipAppAuthenticatorHandle    hAppAuthenticator,
                                              IN  RPOOL_Ptr                     *pRpoolMD5Input,
                                              IN  RvUint32                     length,
                                              OUT RPOOL_Ptr                     *pRpoolMD5Output);


	static void RVCALLCONV AppAuthenticationGetSharedSecretEv(
                                   IN  RvSipAuthenticatorHandle       hAuthenticator,
                                   IN  RvSipAppAuthenticatorHandle    hAppAuthenticator,
                                   IN  void*                          hObject,
                                   IN  void*                          peObjectType,
                                   IN  RPOOL_Ptr                     *pRpoolRealm,
                                   OUT RPOOL_Ptr                     *pRpoolUserName,
                                   OUT RPOOL_Ptr                     *pRpoolPassword);

	static void RVCALLCONV StackLog(IN void* context , IN RvSipLogFilters filter , IN const RvChar   *formattedText);

	static void OnGetRegInfo(s32 nAppId, TSipGetRegInfo tSipGetRegInfo, void *pHandle);  
	
	static void OnRegister( TRegisterInfo *ptRegInfo, s32 nSameReg, void *pHandle, TSipRegName *patSipRegName, s32 nArraySize );

	static void OnUnregister( const s32 nAppId, void *pHandle );

//     static RvStatus RVCALLCONV AppRegClientMsgToSendEvHandler(
//                            IN  RvSipRegClientHandle          hRegClient,
//                            IN  RvSipAppRegClientHandle       hAppRegClient,
//                            IN  RvSipMsgHandle                hMsg);

	static const RvChar* AppGetRegClientStateName(IN  RvSipRegClientState  eState);
    //other
	static void ConstructURI( TSipUrl tUrlAddr, char *achOut, EmSipConnection emSipConnection = emSipTcpConnection, BOOL32 bAddPasswd = FALSE , BOOL bTo = FALSE );

    static void AppPrintMessage(IN RvSipMsgHandle hMsg);
	static void RVCALLCONV   AppSipTransactionStateChangedEv(	IN RvSipTranscHandle                 hTransc,
																IN RvSipTranscOwnerHandle            hTranscOwner,
																IN RvSipTransactionState             eState,
																IN RvSipTransactionStateChangeReason eReason);
	static void RVCALLCONV  AppSipTransactionCreatedEv(	IN    RvSipTranscHandle        hTransc,
														IN    void                     *pAppContext,
														OUT   RvSipTranscOwnerHandle   *hAppTransc,
														OUT   RvBool                  *b_handleTransc);
	static s32 OnSendAck( RvSipCallLegHandle hsCall, const void* pBuf,u16 nBufLen );
	static RvStatus RVCALLCONV AppRegserverMsgReceivedEvHandler( 
												IN RvSipTranscHandle      hTransc,
												IN RvSipTranscOwnerHandle hTranscOwner,
												IN RvSipMsgHandle         hMsgReceived );
	static RvStatus RVCALLCONV AppRegserverMsgToSendEvHandler(  
												IN RvSipTranscHandle       hTransc,
												IN RvSipTranscOwnerHandle  hTranscOwner,
												IN RvSipMsgHandle          hMsgToSend );
private:
	//begin sdp part
	//���̺�
	static s8 m_achVendorId[SESSION_USERNAME_LEN+1]; 
	//��Ʒ�ͺ�
	static s8  m_achProductId[SESSION_USERNAME_LEN+1]; 
	//�汾��
	static s8  m_achVersion[SESSION_INFO_LEN+1];
	//���ó��̺źͰ汾��Ϣ
    static void SetSdpInfo( s8* pchProductId, s8* pchVersionId );

	static  RvStatus AddDisConnectReason(IN RvSipCallLegHandle hsCall,IN RvSipMsgHandle hMsg, u8 byReason);

	static RvStatus AddScreenNum( IN RvSipCallLegHandle hsCall,IN RvSipMsgHandle hMsg, TSipCallParam &tSipCallParam );

	static RvStatus AddLevelHeader( IN RvSipCallLegHandle hsCall, IN RvSipMsgHandle hMsg, TSipCallParam &tSipCallParam );
	//����User-Agent
	static RvStatus AddUserAgent( IN RvSipMsgHandle hMsg );

	static RvStatus AddUserAgent( IN RvSipCallLegHandle hsCall, IN RvSipMsgHandle hMsg, TSipCallParam &tSipCallParam );
	//����allow header
	static RvStatus AddAllowHeader( IN RvSipMsgHandle hMsg );
	//����supported header
	static RvStatus AddSupportedHeader( IN RvSipMsgHandle hMsg );
	//����require header
	static RvStatus AddRequireHeader( IN RvSipMsgHandle hMsg );
	//�����Զ���sip��ͷ����֧���Զ����ַ�����
	static RvStatus AddCustomHeader( IN RvSipCallLegHandle hsCall, IN RvSipMsgHandle hMsg, IN s8 *pchHeadName, IN s8 *pchHeadValue );
	//add sdp msg to invite transaction
    static  RvStatus AddSdpBodyToMsg( IN RvSipCallLegHandle hCallLeg, CSipCapSet *pcCapSet, TSipCallParam *ptSipParam, BOOL bSave, BOOL bAddTpAttr );
// 	//add sdp msg to re-invite transaction
// 	static  RvStatus AddSdpBodyToReInvite(IN RvSipCallLegHandle hCallLeg, BOOL bOffer, CSipCapSet *pcCapSet );
	//uas retrieve call parameter from incoming invite transaction
	
	static  RvStatus RetrieveDisReason(IN RvSipCallLegHandle hCallLeg, OUT u8& byReason);
	
	static  RvStatus RetrieveParamFromCall( IN RvSipCallLegHandle hCallLeg, IN BOOL bCaller, OUT BOOL& bOldMt, OUT TSipCallParam& tCallParam );
	//uas retrieve sdp msg from incoming invite transaction
    static  RvStatus RetrieveSDPBodyFromMsg( IN RvSipCallLegHandle hCallLeg, OUT CSipCapSet& tCapSet, INOUT TSipCallParam *ptSipParam = NULL );
	//uac retrieve sdp msg from outcoming invite 200 ok transaction
//	static  RvStatus RetrieveSDPBodyFromInvite2xxOk( IN RvSipCallLegHandle hCallLeg, OUT CSipCapSet& tCapSet );
	//uas retrieve sdp msg from incoming re-invite  transaction
//	static  RvStatus RetrieveSDPBodyFromReInvite( IN RvSipCallLegHandle hCallLeg, OUT CSipCapSet& tCapSet );
	//uac retrieve sdp msg from outcoming re-invite 200ok  transaction
//	static  RvStatus RetrieveSDPBodyFromReInvite2xxOk( IN RvSipCallLegHandle hCallLeg, OUT CSipCapSet& tCapSet );
	static BOOL BuildSdpBfcpFromCapset( IN RvSdpMsg* pSdpMsg, IN CBfcpMediaStream *pcMediaStream );
	
	static BOOL BuildSdpFeccFromCapset( IN RvSdpMsg* pSdpMsg, IN RvSdpConnectionMode rvMode, IN CFeccMediaStream *pcMediaStream );

    //sdp offer-answer mode build offer sdp msg
	static BOOL BuildSdpFromCapset( IN RvSdpMsg* pSdpMsg, BOOL bOffer, IN RvSdpConnectionMode rvMode, 
		                       IN CSipMediaStream *ptMediaStream, u16 wRecvRtcpPort, BOOL bTP = TRUE );

	static BOOL BuildCapsetFromSdpBfcp( CBfcpMediaStream *pcStream, RvSdpMediaDescr *pMediaDesc );

	static BOOL BuildCapsetFromSdpFecc( CFeccMediaStream *pcStream, RvSdpMediaDescr *pMediaDesc );
    //build audio video capset according sdp msg
	static BOOL BuildCapsetFromSdp( CSipMediaStream *pcStream, RvSdpMediaDescr *pMediaDesc , u32 dwConnectionAddr );

	//build H264 capset
	static void BuildH264Capset( RvSdpRtpMap* pSdpRtpMap, TSipH264VideoCap &tH264Cap, 
		                         char *achAttr =NULL );
	//build video capset except h264 
	static void BuildCommonVideoCapset( RvSdpRtpMap* pSdpRtpMap, TSipVideoCap &tHCommonCap,
		                                char *achAttr =NULL );

	
	static u16 GetDynamicPayloadType( EmSipPayloadType emPt );
	static BOOL GetValueByFieldIds( char *pchString, char *pchField, int &nValue );
	static BOOL GetValueByFieldIds( char *pchString, char *pchField, char *pValue );
	static EmSipPayloadType GetFormat( u16 wPayload );
	static char*  GetFmtp( int nPayload, RvSdpMediaDescr *pMediaDesc, s32 nlcCap = 0, s32 nldCap = 0  );
	static s8*  GetFmtpH264( s32 nPayload, RvSdpMediaDescr *pMediaDesc, s32 nIndex );
	static s32 GetH264Bitrate( RvSdpMediaDescr *pMediaDesc, s8 *pchAttr );
	static RvStatus AppViewSDPMessage(IN RvSdpMsg* pSdpMsg );
	static s8*  GetProductName( EmSipVendorId emProductId );

	static BOOL CheckRequestUri( RvSipCallLegHandle hCall , RvSipAppCallLegHandle haCall );
	static BOOL CheckContentAndResponse( RvSipCallLegHandle hCallLeg , RvSipMsgHandle hMsg );
	static BOOL CheckExpiresAndResponse( RvSipCallLegHandle hCallLeg , RvSipMsgHandle hMsg );
	static BOOL SendRoundTrip( RvSipCallLegHandle hsCall  );
	static s32 GetFormatInRtpmaplistPosition( u16 wPayload, RvSdpMediaDescr *pMediaDesc );

	static s8*  GetContentAttrName( EmSipContentAttr emSipcontentAttr );
	static s8*  GetFloorControlAttrName( EmSipFloorcontrolAttr emFloorcontrolAttr );
	static s8*  GetSetupAttrName( EmSipSetupAttr emSetupAttr );
	static s8*  GetConnectionAttrName( EmSipConnectionAttr emConnectionAttr );
	static EmSipContentAttr  GetContentAttrValue( const s8 *pContentName );
	static EmSipFloorcontrolAttr  GetFloorControlAttrValue( const s8 *pFloorcontrolName );
	static EmSipSetupAttr  GetSetupAttrValue( const s8 *pSetupName );
	static EmSipConnectionAttr  GetConnectionAttrValue( const s8 *pConnectionName );
	static s8* GetTpCapsignName( EmSipCapSign emTpCapSign );
	static EmSipCapSign GetTpCapsignValue(  const s8 *pTpCapsign );
	
private:
   //ͨ������
	static CMediaStreamCtrl *m_pcStreamCtrl;
}; 
  
void Sip_Printf( EmSipLogModule emPAModule, EmSipLogType emPALogType, const char* pFormat, ... );

void StringToUpperCase( IN s8* pchInput, OUT s8* pchOutput );
#endif

