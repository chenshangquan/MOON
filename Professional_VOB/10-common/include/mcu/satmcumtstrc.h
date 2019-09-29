/*****************************************************************************
   ģ����      : ���ǳ�������
   �ļ���      : satmtstrc.h
   ����ļ�    : satconst.h
   �ļ�����    : 
   ����        : ��˹��
   �汾        : V1.0  Copyright(C) 2001-2002 KDC, All rights reserved.
-----------------------------------------------------------------------------
   �޸ļ�¼:
   ��  ��      �汾        �޸���      �޸�����
   2004/11/02  1.0         ������      
******************************************************************************/

#ifndef _SAT_MCU_MT_STRUCT_H_
#define _SAT_MCU_MT_STRUCT_H_

#include "osp.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#ifndef WIN32
#include <netinet/in.h>
#endif
#include "kdvsys.h"
#include "satconst.h"


#ifdef WIN32
#pragma comment( lib, "ws2_32.lib" ) 
#pragma pack( push )
#pragma pack( 1 )
#endif

#ifdef WIN32
#define PACKED 
#else
#define PACKED __attribute__((__packed__))	// ȡ�����������Ż�����
#endif // WIN32

#ifdef WIN32
	#define window( x )	x
#else
	#define window( x )
#endif
//��Ϣ��װ
typedef struct tagITSatMessageHeader
{
	enum{
		emMCUID = 0x0000,
		emNMSID = 0xFFF0,
		emBROADCAST = 0xFFFF
	};
	protected:
		u16 m_wEventId; //��ϢID
		u16 m_wMsgSN;   //��Ϣ��ˮ��(1-65535)
		u8  m_byConfIdx; //��������(0xFF ��ʾ�����еĻ���㲥��Ϣ)
		u16 m_wSrcId;   //��Ϣ������ID MCUӦ����0 ,��������ϵͳӦ���� 0xFFF0 ,�ն�����Ӧ��ID
		u16 m_wDstId;   //��Ϣ����Ŀ��ID MCUӦ����0 ,
		                //��������ϵͳӦ���� 0xFFF0 ,�ն�����Ӧ��ID
		                //0xFFFF ��ʾ�㲥��Ϣ 
		u8  m_byReserve;//�����̶ֹ�Ϊ��
	public:
		tagITSatMessageHeader()
		{
			m_wEventId = ntohs(0);
			m_wMsgSN   = ntohs(1);
			m_byConfIdx = 0xFF;
			m_wSrcId   = ntohs(emMCUID);
			m_wSrcId   = ntohs(emBROADCAST);
			m_byReserve = 0;
		}

		//��ȡ��ϢID
		u16 GetEventId()
		{
			return ntohs(m_wEventId);
		}
		//������ϢID
		void SetEventId( u16 wEventId )
		{
			m_wEventId = htons(wEventId);
		}
		//��ȡ��Ϣ��ˮ��
		u16 GetMsgSN()
		{
			return ntohs(m_wMsgSN );
		}
		//������Ϣ��ˮ��
		void SetMsgSN( u16 wMsgSN )
		{
			m_wMsgSN = ntohs(wMsgSN);
		}

		//��ȡ����������
		u8 GetConfIdx()
		{
			return m_byConfIdx;
		}
		//���û���������
		void SetConfIdx( u8 byConfIdx)
		{
			m_byConfIdx = byConfIdx;
		}

		//��ȡ��Ϣ����ԴID��
		u16 GetSrcId()
		{
			return ntohs(m_wSrcId);
		}
		//������Ϣ����ԴID��
		void SetSrcId( u16 wSrcId)
		{
			m_wSrcId = htons(wSrcId);
		}
        //��ȡ��Ϣ����Ŀ��ID��
		u16 GetDstId()
		{
			return ntohs(m_wDstId);
		}
        //������Ϣ����Ŀ��ID��
		void SetDstId( u16 wDstId)
		{
			m_wDstId = htons(wDstId);
		}
}PACKED ITSatMsgHdr;


typedef struct tagTSatBitrate
{

	tagTSatBitrate(){memset(this,0,sizeof(tagTSatBitrate));	}
	protected:
		u8 m_byBitrate;
	public:
		//��ȡ���� (��λ:Kbps)
		u16 Get()
		{
			return m_byBitrate*32;
		}

		//�������� (��λ:Kbps )
		void Set( u16 wBitrate )
		{
			if( wBitrate >= 255*32 )
			{
				m_byBitrate = 255;
			}
			else
			{
				m_byBitrate = (u8)(wBitrate/32);
			}
		}
}PACKED ITSatBitrate;

//�ն���Ϣ
typedef struct tagTInterfaceMtTopo
{
	enum EMMtType
	{
		emFULL    = 1,//ȫ˫�� ֱ���ն�
		emUPALLOC = 2,//�ش�ͨ�����䣨�����նˣ�
	};
	enum EMModemType
	{
		emMODEM_70M_LBAND     = 1,            
		emMODEM_LBAND_70M     = 2,            
		emMODEM_LBAND_LBAND   = 3 
	};
	tagTInterfaceMtTopo(){memset(this,0,sizeof(tagTInterfaceMtTopo));}
protected:
	u16 m_wMtId;
	u8  m_byConnectType;
	char m_achAlias[MAXLEN_SATMTALIAS];
	u32 m_dwMtIp;
	u32  m_dwModemIp;
	u16  m_wModemPort;
	u8   m_byModemType;
	

	
public:
	void SetMtId( u16 wMtId )
	{
		m_wMtId = htons(wMtId);
	}
	u16 GetMtId(void)
	{
		return ntohs(m_wMtId);
	}
	
	void SetMtConnectType( u8 byMode )
	{
		m_byConnectType = byMode;
	}
	u8 GetMtConnectType(void)
	{
		return m_byConnectType;
	}
	
	void SetMtModemIp( u32 dwIp )
	{
		m_dwModemIp = dwIp;
	}
	u32 GetMtModemIp( void )
	{
		return m_dwModemIp;
	}
	
	void SetMtModemPort( u16 wPort )
	{
		m_wModemPort = htons(wPort);
	}
	u16 GetMtModemPort(void)
	{
		return ntohs(m_wModemPort);
	}
	
	void SetMtModemType( u8 byType )
	{
		m_byModemType = byType;
	}
	u8 GetMtModemType()
	{
		return m_byModemType;
	}
	
	void SetMtAlias( LPCSTR lpszAlias )
	{
		if( lpszAlias != NULL )
		{
			strncpy( m_achAlias, lpszAlias, sizeof( m_achAlias ) );
			m_achAlias[sizeof( m_achAlias ) - 1] = '\0';
		}
		else
		{
			memset( m_achAlias, 0, sizeof( m_achAlias ) );
		}
	}
	char* GetMtAlias()
	{
		return m_achAlias;
	}
	
	void SetMtIp( u32 dwIp )
	{
		m_dwMtIp = dwIp;
	}
	
	u32 GetMtIp()
	{
		return m_dwMtIp;
	}
}PACKED TInterfaceMtTopo ,ITSatMtInfo;

typedef struct tagTInterfaceConfList
{
	u8 m_byConfIdx;
	char m_achName[16];
	tagTInterfaceConfList()
	{
		memset(this,0,sizeof(tagTInterfaceConfList));
	}
public:
	void SetConfIdx( u8 byIndex )
	{
		m_byConfIdx = byIndex;
	}
	u8 GetConfIdx(void)
	{
		return m_byConfIdx;
	}
	
	void SetConfName( LPCSTR lpszAlias )
	{
		if( lpszAlias != NULL )
		{
			strncpy( m_achName, lpszAlias, sizeof( m_achName ) );
			m_achName[sizeof( m_achName ) - 1] = '\0';
		}
		else
		{
			memset( m_achName, 0, sizeof( m_achName ) );
		}
	}
	char* GetConfName()
	{
		return m_achName;
	}
	
}PACKED TInterfaceConfList ,ITSatConfList;

typedef struct tagTInterfaceList
{
	tagTInterfaceList()
	{
		memset(this,0,sizeof(tagTInterfaceList));
	}
public:
	u8 m_abyMemberList[MAXNUM_SATMT/8];
public:
	void SetMember( u16 wWhoId )
	{
		if( wWhoId > MAXNUM_SATMT || wWhoId==0 )
		{
			OspPrintf( TRUE,FALSE, "Mt Id out of range %d", wWhoId );
			return ;
		}
		wWhoId -=1;
		m_abyMemberList[wWhoId / 8] |= 1 << ( wWhoId % 8 );
		return;
	}
	void RemoveMember( u16 wWhoId )
	{
		if( wWhoId > MAXNUM_SATMT || wWhoId==0 )
		{
			OspPrintf(TRUE,FALSE,"Mt Id out of range %d", wWhoId );
			return ;
		}
		wWhoId -=1;
		m_abyMemberList[wWhoId / 8] &= ~( 1 << ( wWhoId % 8 ) );
		return;
	}

	BOOL IsInList( u16 wWhoId ) const
	{
		if( wWhoId > MAXNUM_SATMT || wWhoId==0 )
		{
			OspPrintf(TRUE,FALSE,"Mt Id out of range %d", wWhoId );
			return FALSE;
		}
		wWhoId -=1;
		return ( ( m_abyMemberList[wWhoId / 8] & ( 1 << ( wWhoId % 8 ) ) ) != 0 );
	}
}PACKED TInterfaceList ,ITSatMtList;

typedef TInterfaceList TMtList;
//���廭�渴��
typedef struct tagTVMPParam
{
protected:
    u8      m_byVmpStyle;			//�ϳɷ��
    u8		m_byBrdcst;			//�Ƿ�㲥
    u16    	m_wMt[16];        		//��ԱID
public:
	inline u8 GetVmpStyle( void ) const
	{
		return( m_byVmpStyle );
	}
	
	inline void SetVmpStyle( u8 byStyle )
	{
		m_byVmpStyle = byStyle;
	}
	
	inline void SetVmpBrd( BOOL bBroad )
	{
		if ( bBroad == TRUE )
			m_byBrdcst = 1;
		else
			m_byBrdcst = 0;
	}
	
	inline BOOL IsVmpBrd( ) const
	{
		return ( m_byBrdcst == 1 );
	}

	inline void SetMtId( u8 byPos , u16 wMtId )
	{
		if( byPos >16 )
			return;
		m_wMt[ byPos-1] = htons( wMtId );
	}

	inline u16 GetMtId( u8 byPos ) const
	{
		if ( byPos == 0 || byPos > 16 )
			return 0;
		return ntohs( m_wMt[byPos-1] );
	}

}PACKED ITSatVmpParam;


typedef struct tagTInterfaceConfInfo
{
	tagTInterfaceConfInfo()
	{
		memset(this,0,sizeof(tagTInterfaceConfInfo));
	}

protected:
	u16 m_wSpeakerId;
	u16 m_wChairId;
	u8  m_byLineNum;
	u8  m_bySwitchTime;
	char m_achName[32];
	u8  m_byAudioType;
	u8  m_byVideoType;   //��ƵƵ����
	u8  m_byVidResolution;//��Ƶ�ֱ���
    ITSatBitrate m_tConfBitrate;
	/*--------------------------------*/
	u8  m_byState;//������
	/* 0x 0 0 0 0 0 x x x
		      |    | |_____����״̬
		      |    |_______���渴��״̬
		      |____________������Ϣ
	*/
	u8  m_achKey[9];
public:
	TMtList m_tNonActiveMt;//����
	TMtList m_tActiveMt;//ǩ��
	TMtList m_tCanSendMt;//�ɷ��ͣ��ϴ�(ֱ����ռ�ϴ�ͨ·)
	
	TMtList m_tNearMuteMt; //����
	TMtList m_tFarMuteMt; //����
	ITSatVmpParam m_tVmpMt; //���渴��

public:
	//��ȡ������Ƶ��ʽ
	u8 GetVideoType()
	{
		return m_byVideoType;
	}
	//���û�����Ƶ��ʽ
	void SetVideoType( u8 byType)
	{
		m_byVideoType = byType;
	}
	//��ȡ������Ƶ�ֱ���
	u8 GetResolution()
	{
		return m_byVidResolution;
	}
	//���û�����Ƶ�ֱ���
	void SetResolution( u8 byResolution)
	{
		m_byVidResolution = byResolution;
	}

	//���û�����Ƶ�ֱ���
	void SetAudioType( u8 byType )
	{
		m_byAudioType = byType;
	}

	//���û�����Ƶ�ֱ���
	u8 GetAudioType()
	{
		return m_byAudioType;
	}
	
	//���û������� (��λ64K)
	void SetBitrate( u16 wBitrate )
	{
		m_tConfBitrate.Set( wBitrate );
	}
	
	//��ȡ����������� (��λ64K)
	u16 GetBitrate()
	{
		return m_tConfBitrate.Get();
	}


	//������
	void SetSpeakerId( u16 wSpeakerId )
	{
		m_wSpeakerId = htons(wSpeakerId);
	}
	u16 GetSpeakerId(void)
	{
		return ntohs(m_wSpeakerId);
	}
	//��ϯ
	void SetChairId( u16 wChairId )
	{
		m_wChairId = htons(wChairId);
	}
	u16 GetChairId(void)
	{
		return ntohs(m_wChairId);
	}
	//����״̬
	void SetMixing(void)
	{
		m_byState |= 1;
	}
	void SetNoMixing(void)
	{
		m_byState &=~1;
	}
	BOOL IsMixing(void)
	{
		return ( (m_byState & 1 ) != 0 );
	}
	//���渴��״̬
	void SetVmping(void)
	{
		m_byState |= 0x2;
	}
	void SetNoVmping(void)
	{
		m_byState &= ~0x2;
	}
	BOOL IsVmping(void)
	{
		return ( (m_byState & 0x2 ) != 0 );
	}
	//���渴�Ϲ㲥״̬
/*	void SetVmpBrdst(void)
	{
		m_byState |= 0x4;
	}
	void SetVmpNoBrdst(void)
	{
		m_byState &= ~0x4;
	}
	BOOL IsVmpBrdst(void)
	{
		return ( (m_byState & 0x4 ) != 0 );
	}*/
	/*�����Ƿ����,�ն˴�������Ҫ��������
	*/
	void SetConfEncrypted( BOOL bEncrypt )
	{
		if ( bEncrypt )
			m_byState |= 0x08;
		else
			m_byState &= ~0x08;
	}
	
	BOOL IsConfEncrypted()
	{
		return ( (m_byState & 0x08 ) != 0 );
	}
	/*�������룬�ն˴�������ʱ��д*/
	void SetConfKey( u8* buf, u8 len)
	{
		memcpy( m_achKey,buf,len);
		m_achKey[8] = '\0';
	}
	u8* GetConfKey( )
	{
		return m_achKey;
	}
	//������·
	void SetConfLineNum( u8 byNum )
	{
		m_byLineNum = byNum;
	}
	u8 GetConfLineNum(void) const
	{
		return m_byLineNum;
	}
	//�л����
	void SetConfSwitchTime( u8 byTime )
	{
		m_bySwitchTime = byTime;	
	}
	u8 GetConfSwitchTime(void) const
	{
		return m_bySwitchTime;
	}
	LPCSTR GetConfName( void ) const
	{
		return( ( LPCSTR )m_achName );
	}

	void SetConfName( LPCSTR lpszBuf )
	{
		strncpy( m_achName, lpszBuf, sizeof( m_achName ) );
		m_achName[ sizeof( m_achName ) - 1] = '\0';
	}
	
}PACKED TInterfaceConfInfo ,ITSatConfInfo;

typedef struct tagTInterfaceMtKey
{
	tagTInterfaceMtKey()
	{
		memset(this,0,sizeof(tagTInterfaceMtKey));
	}
protected:
	u16 m_wMtId;
	char szDesKey[16];
public:
	void SetMtKey( u16 MtId,  char* key )
	{
		m_wMtId = htons( MtId );
		for ( u8 byLoop = 0 ; byLoop < 16 ; byLoop ++)
			szDesKey[byLoop] = key[byLoop];
	}
	//���ܲ�������������ֱ�ӿ���16���ֽ�
	char* GetMtKey()
	{
		return szDesKey;
	}
	//��ȡ��Կ��MT ID
	u16 GetMtId()
	{
		return ntohs(m_wMtId);
	}
	//������Կ��MT ID
	void SetMtId( u16 wMtId )
	{
		m_wMtId = ntohs(wMtId);
	}
}PACKED TInterfaceMtKey,ITSatMtKey;

typedef struct tagTInterfaceMtCamera
{
	u8 m_byCmd;
	u8 m_byCmdVal;
public:
	void SetCameraCmd( u8 byNewCmd )
	{
		m_byCmd = byNewCmd;
	}
	u8 GetCameraCmd(void)
	{
		return m_byCmd;
	}
	
	void SetCmdVal( u8 byNewVal )
	{
		m_byCmdVal = byNewVal;
	}
	u8 GetCmdVal(void)
	{
		return m_byCmdVal;
	}
}PACKED ITSatCamCmd;

typedef struct tagTInterfaceMtAddr
{
	tagTInterfaceMtAddr(){memset(this,0,sizeof(tagTInterfaceMtAddr));}
protected:
	u32 m_dwIpAddr;
	u16 m_wPort;
public:
	void SetIpAddr( u32 dwIp )
	{
		m_dwIpAddr =  htonl(dwIp) ;
	}
	u32 GetIpAddr(void)
	{
		return ntohl(m_dwIpAddr);
	}
	
	void SetPort( u16 wPort )
	{
		m_wPort = htons( wPort );
	}
	u16 GetPort(void)
	{
		return ntohs( m_wPort );
	}
}PACKED TInterfaceMtAddr,ITSatTransAddr;


typedef struct tagTSatMtBitrateList
{
	
protected:
	ITSatBitrate m_atBitrate[MAXNUM_SATMT];
public:
	
	u16 GetBitrate( u16 wMtId )
	{
		if( wMtId == 0 || wMtId > MAXNUM_SATMT )
		{
			OspPrintf(TRUE,FALSE,"Get Mt.%d bitrate out of range!\n",wMtId );
			return 0;
		}
		return m_atBitrate[wMtId-1].Get();
	}

	void SetBitrate( u16 wMtId ,u16 wBitrate )
	{
		if( wMtId == 0 || wMtId > MAXNUM_SATMT )
		{
			OspPrintf(TRUE,FALSE,"Set Mt.%d bitrate out of range!\n",wMtId );
			return ;
		}
		m_atBitrate[wMtId-1].Set(wBitrate);
	}

}PACKED ITSatMtBitrateList;

typedef struct tagTSatMtId
{
protected:
	u16 m_wMtId;
public:
	
	void Set( u16 wMtId )
	{
		m_wMtId = htons( wMtId );
	}
	u16 Get(void)
	{
		return ntohs( m_wMtId );
	}
}PACKED ITSatMtId;

//���ǻ����ַ��Ϣ
typedef struct tagTSatConfAddrInfo
{
	tagTSatConfAddrInfo(){ memset( this,0,sizeof(tagTSatConfAddrInfo));}
public:
	ITSatMtId      tAudMulticastSrcId;// ��Ƶ�鲥������ƵԴID
	ITSatMtId      tVidMulticastSrcId;// ��Ƶ�鲥������ƵԴID
	ITSatMtId      tAudUnitcastSrcId; // ��Ƶ����������ƵԴID
	ITSatMtId      tVidUnitcastSrcId; // ��Ƶ����������ƵԴID

	ITSatTransAddr tMcuRcvMediaAddr;     // MCU��������(������)��ַ ,��Ƶ��ʼ�˿ں�
    ITSatTransAddr tAudMulticastAddr;    // ��Ƶ�鲥��ַ��Ϣ 
    ITSatTransAddr tVidMulticastAddr;    // ��Ƶ�鲥��ַ��Ϣ 
	ITSatTransAddr tAudUnitcastAddr;     // ��Ƶ������ַ��Ϣ-�õ�ַ�����˿ں���Ч
	ITSatTransAddr tVidUnitcastAddr;     // ��Ƶ������ַ��Ϣ-�õ�ַ�����˿ں���Ч

	ITSatMtList    tAudMulticastMmbList; // ��Ƶ�鲥���ճ�Ա�б� 
	ITSatMtList    tVidMulticastMmbList; // ��Ƶ�鲥���ճ�Ա�б� 
	ITSatMtList    tAudUnitcastMmbList;  // ��Ƶ�������ճ�Ա�б� 
    ITSatMtList    tVidUnitcastMmbList;  // ��Ƶ�������ճ�Ա�б�

	//˫��֧�֣��ݲ�����˫����������˫��ѡ����
	ITSatMtId      tDSMulticastSrcId;	// ˫���鲥������ƵԴID
	ITSatTransAddr tDSMulticastAddr;	// ˫���鲥��ַ��Ϣ
	ITSatMtList    tDSMulticastMmbList; // ˫���鲥���ճ�Ա�б� 
}PACKED ITSatConfAddrInfo;

//�������Ϣ�ṹ
typedef struct tagTShortMessageInfo
{
protected:
    u8          m_byTimes;			//��ʾ����
    char        m_achMsgBuf[0x400];	//����ϢBUFFER�����1024�ַ�
public:
	tagTShortMessageInfo(){memset(this,0,sizeof(tagTShortMessageInfo));}
	
	inline LPCSTR GetMessage( void ) const
	{
		return( m_achMsgBuf );
	}

	inline void SetMessage( LPCSTR lpszMsg )
	{
		strncpy( m_achMsgBuf, lpszMsg, sizeof( m_achMsgBuf ) );
		m_achMsgBuf[ sizeof( m_achMsgBuf ) - 1] = '\0';
	}

	inline u8 GetTimes( void ) const
	{
		return( m_byTimes );
	}

	inline void SetTimes( u8 byTimes )
	{
		m_byTimes = byTimes;
	}
}PACKED ITSatShortMsg;

//�������Ϣ�ṹ
typedef struct tagTMultiPackHeader
{
protected:
    u8          m_byTotalNum;		//�����ܸ���
    u8        m_byCurrNum;	//��ǰ�������
    u8        m_byContentNum;   //��ǰ�����ݸ���
public:
	inline u8 GetTotalNum( void ) const
	{
		return m_byTotalNum;
	}

	inline void SetTotalNum( u8 byNum )
	{
		m_byTotalNum = byNum;
	}

	inline u8 GetCurrNum( void ) const
	{
		return m_byCurrNum;
	}

	inline void SetCurrNum( u8 byNum )
	{
		m_byCurrNum = byNum;
	}
	
	inline u8 GetContentNum( void ) const
	{
		return m_byContentNum;
	}

	inline void SetContentNum( u8 byNum )
	{
		m_byContentNum = byNum;
	}
}PACKED ITSatMultiPackHeader;

#ifdef WIN32
#pragma pack( pop )
#endif

#endif//!_SAT_MT_STRUCT_H_