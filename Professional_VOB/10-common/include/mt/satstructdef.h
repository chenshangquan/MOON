#ifndef SAT_STRUCT_H
#define SAT_STRUCT_H
#include "satmcumtstrc.h"
// �궨��
//////////////////////////////////////////////////////////////////////////



// �ṹ����
//////////////////////////////////////////////////////////////////////////
#ifdef WIN32
#pragma pack( push )
#pragma pack(1)
#define PACKED 
#else
#define PACKED __attribute__((__packed__))	// ȡ�����������Ż�����
#endif // WIN32


//typedef struct tagTest
//{
//}PACKED TEST,*PTEST;


#define SAT_DES_KEY_LEN  16
// Զң�궨��
// cmd
#define		SAT_CAMERA_PAN_LEFT         1
#define		SAT_CAMERA_PAN_RIGHT        2
#define		SAT_CAMERA_TILT_UP          3
#define		SAT_CAMERA_TILT_DOWN        4
#define		SAT_CAMERA_FOCUS_AUTO       5
#define		SAT_CAMERA_FOCUS_FAR		6
#define		SAT_CAMERA_FOCUS_NEAR		7
#define		SAT_CAMERA_ZOOM_IN			8
#define		SAT_CAMERA_ZOOM_OUT			9
#define		SAT_CAMERA_BRIGHT_UP		10
#define		SAT_CAMERA_BRIGHT_DOWN		11
#define		SAT_CAMERA_PRESET_SAVE		12
#define		SAT_CAMERA_PRESET_MOVE		13
#define		SAT_CAMERA_VSRC_SELECT		14

// action
#define		SAT_START			1			//��ʼ
#define		SAT_STOP				2			//ֹͣ
#define		SAT_CONTINUE			3			//����




//////////////////////////////////////////////////////


typedef ITSatMtList     TSatMtList ;//�ն�λ�б�
typedef ITSatBitrate    TSatBitrate;//����
typedef ITSatVmpParam   TSatVMPStatus;

//�ն�ID �ṹ
struct TSatMtId :public ITSatMtId
{
public:
	u8 GetMtNo()
	{
		u16 wHostMtId = ntohs(m_wMtId);
		return (u8)(wHostMtId&0xFF);
	}

	void SetMtNo( u8 byMtNo )
	{
		u16 wHostMtId = ntohs(m_wMtId);
		wHostMtId &= 0xFF00;
		wHostMtId |= byMtNo;
		m_wMtId = htons(wHostMtId);
	}


	u8 GetMcuNo()
	{
		u16 wHostMtId = ntohs(m_wMtId);
		return (u8)((wHostMtId>>8)&0xFF);
	}

	void SetMcuNo(u8 byMcuNo )
	{
		u16 wHostMtId = ntohs(m_wMtId);
		wHostMtId &= 0x00FF;
		wHostMtId |= (byMcuNo<<8);
		m_wMtId    = htons(wHostMtId);
	}

};

//////////////////////////////////////////////////////
// �ն���Ϣ
typedef struct tagTSatMtInfo
{
	char m_achAlias[MAXLEN_SATMTALIAS];	//��MT����      
	TSatMtId  m_tMtId;					//MT��(1-1024)
	u8   m_byUpLoadChn;             //�Ƿ�ӵ�лش�ͨ��
public:
	tagTSatMtInfo() {memset(this,0,sizeof(tagTSatMtInfo));}
	
	char* GetAlias(){ return m_achAlias;	}
	void  SetAlias( char* achAlias )
	{
		strncpy( m_achAlias ,achAlias,sizeof(m_achAlias) );
		m_achAlias[sizeof(m_achAlias)-1 ]=0;
	}

	u16  GetMtId(){return m_tMtId.Get();	}
	void SetMtId( u16 wMtId ) 
	{
		m_tMtId.Set(wMtId);
	}


	void SetMtNo( u8 byMtNo )
	{
		m_tMtId.SetMtNo(byMtNo);
	}
	u8 GetMtNo()
	{
		return m_tMtId.GetMtNo();
	}

	u8 GetMcuNo()
	{
		return m_tMtId.GetMcuNo();
	}
	void SetMcuNo(u8 byMcuNo )
	{
		m_tMtId.SetMcuNo(byMcuNo);
	}

	//�Ƿ�ӵ�лش�ͨ��
	BOOL IsUpLoad()
	{
		return m_byUpLoadChn==0 ? FALSE:TRUE;
	}

	void AddUpLoadChn()
	{
		m_byUpLoadChn |=0x01;
	}

	void RemoveLoadChn()
	{
		m_byUpLoadChn &=~0x01;
	}

	//����Ϊֱ���ն�
	void SetConnectType( BOOL bConnected)
	{
		if( bConnected )
			m_byUpLoadChn |=0x80;
		else
			m_byUpLoadChn &=0x80;
	}
	//�Ƿ�Ϊֱ���ն�
	BOOL IsConnected()
	{
		return m_byUpLoadChn&0x80;
	}
}PACKED TSatMtInfo ,*PTSatMtInfo;


//������Ϣ�ṹ��
typedef struct tagTSatConfInfo
{
protected:	
	u8	m_byConfId;
	char m_achConfName[MAXLEN_SATMTALIAS];

public:
	//����ID
//	TSatConfInfo(){ memset( this,0,sizeof(TSatConfInfo)); }
	u8	 GetConfId(){ return m_byConfId; };
	void SetConfId( u8 byConfId ){ m_byConfId = byConfId;}

	//������
	char*	GetConfName( void ){ return m_achConfName;}
	void	SetConfName( const char* lpszBuf )
	{ 
		strncpy( m_achConfName ,lpszBuf ,sizeof(m_achConfName)-1 );
		m_achConfName[sizeof(m_achConfName)-1] = 0;
	}
}PACKED TSatConfInfo,*PTSatConfInfo ;


//Э��ջ��ʼ�������ṹ
typedef struct tagTSatInitParam
{
	u32 m_dwLocalIP;	//����IP��ַ
	u32 m_dwMcuIP;		// MCU��ַ
	u16 m_wMcuPort;
	u32 m_dwRcvMCIP;	//����������鲥IP��ַ
	u16 m_wRcvMCPort;   //��������˿ں�
	u16 m_wMtId;

	u32 m_dwAudSendIP;
	u16 m_wAudSendPort;
	u32 m_dwAudRecvIP;
	u16 m_wAudRecvPort;
	u32 m_dwVidSendIP;
	u16 m_wVidSendPort;
	u32 m_dwVidRecvIP;
	u16 m_wVidRecvPort;

	u32 m_dwMcuComIfIP; //��MCUͨ�ŵĽӿ�IP
public:
	tagTSatInitParam()
	{
		m_dwLocalIP = 0;
		m_dwMcuIP = 0;
		m_wMcuPort = 0;
		m_dwRcvMCIP = 0;
		m_wRcvMCPort = 0;
		m_wMtId = 0;

		m_dwAudSendIP = 0;
		m_wAudSendPort = 0;
		m_dwAudRecvIP = 0;
		m_wAudRecvPort = 0;
		m_dwVidSendIP = 0;
		m_wVidSendPort = 0;
		m_dwVidRecvIP = 0;
		m_wVidRecvPort = 0;
		m_dwMcuComIfIP = 0;
	}

	void SetMtId( u16 wMtId ){ m_wMtId = wMtId ;}
	void SetLocalIP( u32 dwIP ){ m_dwLocalIP = dwIP;	}
	void SetSignalMCIP( u32 dwIP ){ m_dwRcvMCIP = dwIP;}
	void SetSignalMCPort( u16 wPort ){ m_wRcvMCPort = wPort;}
	void SetMcuIP( u32 dwIP ) { m_dwMcuIP = dwIP; }
	void SetMcuPort( u16 wPort ) { m_wMcuPort = wPort; }
	void SetMcuComIfIP( u32 dwIP ) { m_dwMcuComIfIP = dwIP; }

	void SetSendAddr( BOOL bAudio, u32 dwIp, u16 wPort )
	{
		if ( bAudio )
		{
			m_dwAudSendIP = dwIp;
			m_wAudSendPort = wPort;
		}
		else
		{
			m_dwVidSendIP = dwIp;
			m_wVidSendPort = wPort;
		}
	}

	void SetRecvAddr( BOOL bAudio, u32 dwIp, u16 wPort )
	{
		if ( bAudio )
		{
			m_dwAudRecvIP = dwIp;
			m_wAudRecvPort = wPort;
		}
		else
		{
			m_dwVidRecvIP = dwIp;
			m_wVidRecvPort = wPort;
		}
	}

////////////////////
	u16 GetMtId(){ return m_wMtId;}
	u32 GetLocalIP(){ return m_dwLocalIP;	}
	u32 GetSignalMCIP(){ return m_dwRcvMCIP;}
	u16 GetSignalMCPort(){ return m_wRcvMCPort;}
	u32 GetMcuIP( void ) { return m_dwMcuIP; }
	u16	GetMcuPort( void ) { return m_wMcuPort; }
	u32 GetMcuComIfIP( void ) { return m_dwMcuComIfIP; }

	u32 GetSendIP( BOOL bAudio )
	{
		if ( bAudio )
			return m_dwAudSendIP;
		else
			return m_dwVidSendIP;
	}

	u32 GetRecvIP( BOOL bAudio )
	{
		if ( bAudio )
			return m_dwAudRecvIP;
		else
			return m_dwVidRecvIP;
	}

	u16 GetSendPort( BOOL bAudio )
	{
		if ( bAudio )
			return m_wAudSendPort;
		else
			return m_wVidSendPort;
	}

	u16 GetRecvPort( BOOL bAudio )
	{
		if ( bAudio )
			return m_wAudRecvPort;
		else
			return m_wVidRecvPort;
	}

	void Clear() { tagTSatInitParam(); }
}PACKED TSatInitParam ,*PTSatInitParam;


//����Ϣ
typedef struct tagTSatSMS
{
	u8  m_byTimes;
	char m_achSms[2048];
public:
	TSatMtId m_tMtId;
public:
	tagTSatSMS() : m_byTimes(0)
	{
		m_tMtId.Set(0);
		memset( m_achSms, 0, sizeof( m_achSms ) );
	}
	
	u8  GetTimes(){ return m_byTimes;}
	void  SetTimes( u8 byTimes ){ m_byTimes = byTimes;}

//	u16 GetSrcMtId(){ return m_wMtId ;	}
//	void SetSrcMtId( u16 wMtId ){ m_wMtId = wMtId;	}

	char* GetMsg()
	{
		m_achSms[sizeof(m_achSms) -1]=0;
		return m_achSms;
	}

	void SetMsg( char* msg )
	{
		strncpy( m_achSms ,msg ,sizeof(m_achSms));
		m_achSms[sizeof(m_achSms) -1]=0;
	}

	void Clear( void ) 
	{
		m_byTimes = 0;
		m_tMtId.Set(0);
		memset( m_achSms, 0, sizeof( m_achSms ) );
	}

}PACKED TSatSMS ,*PTSatSMS;

// Զң����
typedef struct tagFeccCmd
{
	u8 m_byCmd;
	u8 m_byAction;

public :
	tagFeccCmd() : m_byCmd(0),m_byAction(0) {}

	void SetCmd( u8 byCmd ) { m_byCmd = byCmd; }
	u8 GetCmd( void ) { return m_byCmd; }
	void SetAction( u8 byAct ) { m_byAction = byAct; }
	u8 GetAction( void ) { return m_byAction; }
	void Clear( void ) { m_byAction = 0; m_byCmd = 0; }
}PACKED TFeccCmd,*PTFeccCmd;

// MCU������Ϣ
typedef struct tagSatConfStatus
{
//	u16 m_wSpeaking;
//	u16 m_wChairman;
//	u16 m_wViewing;
//	u16 m_wListening;
	TSatMtId m_tSpeaking;
	TSatMtId m_tChairman;
	TSatMtId m_tViewing;
	TSatMtId m_tListening;
public:
	tagSatConfStatus() {Clear();}
	void Clear()
	{
		m_tSpeaking.Set(0);
		m_tChairman.Set(0);
		m_tViewing.Set(0);
		m_tListening.Set(0);
	}
/*
public :
	tagSatConfStatus() : m_wSpeaking(0),m_wChairman(0),m_wViewing(0),m_wListening(0)
	{}

	void SetSpeaking( u16 wMtId ) { m_wSpeaking = wMtId; }
	u16 GetSpeaking( void ) { return m_wSpeaking; }
	void SetChairman( u16 wMtId ) { m_wChairman = wMtId; }
	u16 GetChairman( void ) { return m_wChairman; }
	void SetViewing( u16 wMtId ) { m_wViewing = wMtId; }
	u16 GetViewing( void ) { return m_wViewing; }
	void SetListening( u16 wMtId ) { m_wListening = wMtId; }
	u16 GetListening( void ) { return m_wListening; }
	
	void Clear()
	{
		m_wSpeaking = 0;
		m_wChairman = 0;
		m_wViewing = 0;
		m_wListening = 0;
	}*/
}PACKED TSatConfStatus, *PTSatConfStatus;

typedef struct tagMediaAddr
{
	enum EMMeidaType{
		emAUDIO,
		emVIDEO
	};
	protected:
		u8  m_byType;
		u32 m_dwIP;
		u16 m_wPort;
	public:
		EMMeidaType GetType()
		{
			return (EMMeidaType)m_byType;
		}

		void SetType(EMMeidaType emType )
		{
			m_byType = emType;
		}

		u32  GetIPAddr()
		{
			return m_dwIP;
		}

		void SetIPAddr( u32 dwIP )
		{
			m_dwIP = dwIP;
		}

		u16 GetPort()
		{
			return ntohs(m_wPort);
		}

		void SetPort( u16 wPort )
		{
			m_wPort = ntohs( wPort);
		}
}PACKED TMediaAddr, *PMediaAddr;


//�����ʽ
typedef struct tagConfFormat
{
protected:
	ITSatBitrate m_tBitrate;
	u8  m_byConfType;
	u8  m_byAudioType;
	u8  m_byVideoType;
	u8  m_byVidResoluteion;
public:
	void SetBitrate(u16 wBitrate )
	{
		m_tBitrate.Set(wBitrate);
	}
	
	u16 GetBitrate()
	{
		return m_tBitrate.Get();
	}

	u8 GetConfType()
	{
		return m_byConfType;
	}
	void SetConfType(u8 byType )
	{
		m_byConfType = byType;
	}

	u8 GetAudioType()
	{
		return m_byAudioType;
	}
	void SetAudioType(u8 byType )
	{
		m_byAudioType = byType;
	}

	u8 GetVideoType()
	{
		return m_byVideoType;
	}
	void SetVideoType(u8 byType )
	{
		m_byVideoType = byType;
	}

	u8 GetResolution()
	{
		return m_byVidResoluteion;
	}

	void SetResolution( u8 byResolution )
	{
		m_byVidResoluteion =byResolution;

	}
}PACKED TSatConfFormat;




#ifdef WIN32
#pragma pack( pop )
#endif // WIN32



#endif // SAT_STRUCT_H