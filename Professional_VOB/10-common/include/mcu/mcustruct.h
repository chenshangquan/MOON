/*****************************************************************************
   ģ����      : mcu
   �ļ���      : mcustruct.h
   ����ļ�    : 
   �ļ�ʵ�ֹ���: MCU�ṹ
   ����        : ������
   �汾        : V3.0  Copyright(C) 2001-2002 KDC, All rights reserved.
-----------------------------------------------------------------------------
   �޸ļ�¼:
   ��  ��      �汾        �޸���      �޸�����
   2004/09/16  3.5         ������      ����
   2005/02/19  3.6         ����      �����޸ġ���3.5�汾�ϲ�
******************************************************************************/
#ifndef __MCUSTRUCT_H_
#define __MCUSTRUCT_H_

#include "osp.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "kdvsys.h"
#include "mcuconst.h"
#include "kdvdef.h"
#include "vccommon.h"
#include "ummessagestruct.h"
#include "vcsstruct.h"

#ifdef WIN32
    #pragma comment( lib, "ws2_32.lib" ) 
    #pragma pack( push )
    #pragma pack( 1 )
    #define window( x )	x
#else
    #include <netinet/in.h>
    #define window( x )
#endif

#ifdef _LINUX_

#ifndef min
#define min(a,b) ((a)>(b)?(b):(a))
#endif
#ifndef max
#define max(a,b) ((a)>(b)?(a):(b))
#endif

#ifndef VOID
#define VOID void 
#endif

#endif  /* end _LINUX_ */

//����MCU�ṹ
typedef TMt TMcu;

//�ն���չ�ṹ (len:34)
struct TMtExt : public TMt
{
protected:
	u8    m_byManuId;          //���̱��,�μ����̱�Ŷ���
	u8    m_byCallMode;        //�����ն˷�ʽ��0-�������նˣ��ֶ����� 1-����һ�� 2-��ʱ����
	u16   m_wDialBitRate;      //�����ն����ʣ������򣩵�λKBPS
	u32   m_dwCallLeftTimes;   //��ʱ�����ն˵�ʣ����д���
	u32   m_dwIPAddr;          //IP��ַ��������
	char  m_achAlias[VALIDLEN_ALIAS];	//MCU���ն˻��������
    u8    m_byProtocolType;         // �ն˵�Э������
public:
    TMtExt() : m_byManuId(0),
               m_byCallMode(0),
               m_wDialBitRate(0),
               m_dwCallLeftTimes(0),
               m_dwIPAddr(0),
               m_byProtocolType(0)
    {
        memset( m_achAlias, 0, sizeof(m_achAlias) );
    }
    void   SetManuId(u8   byManuId){ m_byManuId = byManuId;} 
    u8     GetManuId( void ) const { return m_byManuId; }
    void   SetCallMode(u8   byCallMode){ m_byCallMode = byCallMode;} 
    u8     GetCallMode( void ) const { return m_byCallMode; }
    void   SetDialBitRate(u16 wDialBitRate ){ m_wDialBitRate = htons(wDialBitRate);} 
    u16    GetDialBitRate( void ) const { return ntohs(m_wDialBitRate); }
    void   SetCallLeftTimes( u32 dwCallLeftTimes){ m_dwCallLeftTimes = dwCallLeftTimes;} 
    u32    GetCallLeftTimes( void ) const { return m_dwCallLeftTimes; }
    void   SetIPAddr(u32    dwIPAddr){ m_dwIPAddr = htonl(dwIPAddr); } 
    u32    GetIPAddr( void ) const { return ntohl(m_dwIPAddr); }
    void   SetProtocolType(u8 byProtocolType) { m_byProtocolType = byProtocolType;}
    u8     GetProtocolType(void) const { return m_byProtocolType;}
	char*  GetAlias( void ) const{ return (s8 *)m_achAlias; }
	void   SetAlias( char* pszAlias )
	{
        memset( m_achAlias, 0, sizeof( m_achAlias ) );
		if( pszAlias != NULL )
		{
			strncpy( m_achAlias, pszAlias, sizeof( m_achAlias ) - 1);
		}
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//�ն���Ϣ������չ�ṹ len:38
struct TMtExt2 : public TMt
{
public:
    TMtExt2():m_byHWVerId(0)
    {
        memset(m_achSWVerId, 0, sizeof(m_achSWVerId));
    }
    void SetMt(TMt &tMt)
    {
        memcpy(this, &tMt, sizeof(TMt));
    }
    void SetHWVerId( u8 byVerId ) { m_byHWVerId = byVerId;    }
    u8   GetHWVerId( void ) const { return m_byHWVerId;    }
    void SetSWVerId( LPCSTR lpszSWVerId )
    {
        if ( lpszSWVerId == NULL )
        {
            return;
        }
        u16 wLen = min(strlen(lpszSWVerId), sizeof(m_achSWVerId)-1);
        strncpy(m_achSWVerId, lpszSWVerId, wLen);
        m_achSWVerId[sizeof(m_achSWVerId)-1] = '\0';
    }
    LPCSTR GetSWVerId( void ) const { return m_achSWVerId;    }

protected:
    u8  m_byHWVerId;                    //�ն�Ӳ���汾��
    s8  m_achSWVerId[MAXLEN_SW_VER-1];  //�ն�����汾��
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

#ifndef SETBITSTATUS
#define SETBITSTATUS(StatusValue, StatusMask, bStatus)  \
    if (bStatus)    StatusValue |= StatusMask;          \
    else            StatusValue &= ~StatusMask;

#define GETBITSTATUS(StatusValue, StatusMask)  (0 != (StatusValue&StatusMask))   
#endif
    
//���ϼ�mcu�ϱ����˵��ն�״̬ʱ���õĽṹ (len:10)
struct TSMcuMtStatus : public TMt
{
    enum TSMcuMtStatusMask
    {
        Mask_Fecc    =  0x01,
        Mask_Mixing  =  0x02,
        Mask_VidLose  =  0x04,
		Mask_CallMode =  0x08,
        Mask_SendingVideo = 0x10,
        Mask_SendingAudio = 0x20,
        Mask_RcvingVideo = 0x40,
        Mask_RecvingAudio = 0x80		
    };

protected:
	u8  m_byIsStatus;     //0-bit�Ƿ���ң������ͷ,1-bit�Ƿ��ڻ���,2-bit�Ƿ���ƵԴ��ʧ
	u8  m_byCurVideo;     //��ǰ��ƵԴ(1)
	u8  m_byCurAudio;     //��ǰ��ƵԴ(1)
	u8  m_byMtBoardType;  //�ն˵İ忨����(MT_BOARD_WIN-0, MT_BOARD_8010-1, MT_BOARD_8010A-2, MT_BOARD_8018-3, MT_BOARD_IMT-4,MT_BOARD_8010C-5)

public:
	TSMcuMtStatus( void )
	{ 
		memset( this, 0, sizeof(TSMcuMtStatus));
		SetIsEnableFECC(FALSE);
		SetCurVideo(1);
		SetCurAudio(1);
		SetIsAutoCallMode(FALSE);
	}
	void SetIsEnableFECC(BOOL bCamRCEnable){ SETBITSTATUS(m_byIsStatus, Mask_Fecc, bCamRCEnable) } 
	BOOL IsEnableFECC( void ) const { return GETBITSTATUS(m_byIsStatus, Mask_Fecc); }
    void SetIsMixing(BOOL bMixing) { SETBITSTATUS(m_byIsStatus, Mask_Mixing, bMixing) } 
    BOOL IsMixing(void) const { return GETBITSTATUS(m_byIsStatus, Mask_Mixing); }
    void SetVideoLose(BOOL bVidLose){ SETBITSTATUS(m_byIsStatus, Mask_VidLose, bVidLose) }
    BOOL IsVideoLose( void ) const { return GETBITSTATUS(m_byIsStatus, Mask_VidLose);    }
	void SetCurVideo(u8 byCurVideo){ m_byCurVideo = byCurVideo;} 
	u8   GetCurVideo( void ) const { return m_byCurVideo; }
	void SetCurAudio(u8 byCurAudio){ m_byCurAudio = byCurAudio;} 
	u8   GetCurAudio( void ) const { return m_byCurAudio; }
	void SetMtBoardType(u8 byType) { m_byMtBoardType = byType; }
	u8   GetMtBoardType() const {return m_byMtBoardType; }
	void SetIsAutoCallMode( BOOL byAutoMode )   { SETBITSTATUS(m_byIsStatus, Mask_CallMode, byAutoMode); }
	BOOL IsAutoCallMode( void )                 { return GETBITSTATUS(m_byIsStatus, Mask_CallMode); }
    void SetSendVideo(BOOL bSend) { SETBITSTATUS(m_byIsStatus, Mask_SendingVideo, bSend) } 
    BOOL IsSendVideo( void ) const { return GETBITSTATUS(m_byIsStatus, Mask_SendingVideo); }
    void SetSendAudio(BOOL bSend) { SETBITSTATUS(m_byIsStatus, Mask_SendingAudio, bSend) } 
    BOOL IsSendAudio( void ) const { return GETBITSTATUS(m_byIsStatus, Mask_SendingAudio); }
    void SetRecvVideo(BOOL bRecv) { SETBITSTATUS(m_byIsStatus, Mask_RcvingVideo, bRecv) } 
    BOOL IsRecvVideo( void ) const { return GETBITSTATUS(m_byIsStatus, Mask_RcvingVideo); }
    void SetRecvAudio(BOOL bRecv) { SETBITSTATUS(m_byIsStatus, Mask_RecvingAudio, bRecv) } 
    BOOL IsRecvAudio( void ) const { return GETBITSTATUS(m_byIsStatus, Mask_RecvingAudio); }	
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//���ϼ�mcu�ϱ����˵��ն�״̬ʱ���õĽṹ (len:8)
struct TMcuToMcuMtStatus
{
    enum TMcuToMcuMtStatusMask
    {
        Mask_Fecc   =   0x01,
        Mask_Mixing =   0x02,
        Mask_VideoLose = 0x04,
		Mask_CallMode =  0x08,
        Mask_SendingVideo = 0x10,
        Mask_SendingAudio = 0x20,
        Mask_RcvingVideo = 0x40,
        Mask_RecvingAudio = 0x80
    };

protected:
	u8  m_byIsStatus;     //0-bit�Ƿ���ң������ͷ,1-bit�Ƿ��ڻ���,2-bit�Ƿ���ƵԴ��ʧ
	u8  m_byCurVideo;     //��ǰ��ƵԴ(1)
	u8  m_byCurAudio;     //��ǰ��ƵԴ(1)
	u8  m_byMtBoardType;  //�ն˵İ忨����(MT_BOARD_WIN-0, MT_BOARD_8010-1, MT_BOARD_8010A-2, MT_BOARD_8018-3, MT_BOARD_IMT-4,MT_BOARD_8010C-5)
	u32 m_dwPartId;       //������
public:
	TMcuToMcuMtStatus( void )
	{ 
		memset( this, 0, sizeof(TMcuToMcuMtStatus));
		SetIsEnableFECC(FALSE);
        SetIsMixing(FALSE);
        SetIsVideoLose(FALSE);
		SetCurVideo(1);
		SetCurAudio(1);
		SetIsAutoCallMode(FALSE);
	}
	void SetIsEnableFECC(BOOL bCamRCEnable){ SETBITSTATUS(m_byIsStatus, Mask_Fecc, bCamRCEnable) } 
	BOOL IsEnableFECC( void ) const { return GETBITSTATUS(m_byIsStatus, Mask_Fecc); }
    void SetIsMixing(BOOL bMixing) { SETBITSTATUS(m_byIsStatus, Mask_Mixing, bMixing) } 
    BOOL IsMixing(void) const { return GETBITSTATUS(m_byIsStatus, Mask_Mixing); }
    void SetIsVideoLose(BOOL bVideoLose) { SETBITSTATUS(m_byIsStatus, Mask_VideoLose, bVideoLose) }
    BOOL IsVideoLose(void) const { return GETBITSTATUS(m_byIsStatus, Mask_VideoLose);    }
	void SetCurVideo(u8 byCurVideo){ m_byCurVideo = byCurVideo;} 
	u8   GetCurVideo( void ) const { return m_byCurVideo; }
	void SetCurAudio(u8 byCurAudio){ m_byCurAudio = byCurAudio;} 
	u8   GetCurAudio( void ) const { return m_byCurAudio; }
	void SetMtBoardType(u8 byType) { m_byMtBoardType = byType; }
	u8   GetMtBoardType() const {return m_byMtBoardType; }
	void SetPartId(u32 dwPartId){ m_dwPartId = htonl(dwPartId);} 
	u32  GetPartId( void ) const { return ntohl(m_dwPartId); }
	void SetIsAutoCallMode( BOOL byAutoMode )   { SETBITSTATUS(m_byIsStatus, Mask_CallMode, byAutoMode); }
	BOOL IsAutoCallMode( void )                 { return GETBITSTATUS(m_byIsStatus, Mask_CallMode); }
    void SetSendVideo(BOOL bSend) { SETBITSTATUS(m_byIsStatus, Mask_SendingVideo, bSend) } 
    BOOL IsSendVideo( void ) const { return GETBITSTATUS(m_byIsStatus, Mask_SendingVideo); }
    void SetSendAudio(BOOL bSend) { SETBITSTATUS(m_byIsStatus, Mask_SendingAudio, bSend) } 
    BOOL IsSendAudio( void ) const { return GETBITSTATUS(m_byIsStatus, Mask_SendingAudio); }
    void SetRecvVideo(BOOL bRecv) { SETBITSTATUS(m_byIsStatus, Mask_RcvingVideo, bRecv) } 
    BOOL IsRecvVideo( void ) const { return GETBITSTATUS(m_byIsStatus, Mask_RcvingVideo); }
    void SetRecvAudio(BOOL bRecv) { SETBITSTATUS(m_byIsStatus, Mask_RecvingAudio, bRecv) } 
    BOOL IsRecvAudio( void ) const { return GETBITSTATUS(m_byIsStatus, Mask_RecvingAudio); }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//����������������RRQʱ����֤��Ϣ��¼ GatekeeperID/EndpointID
//TH323TransportAddress�ṹӦ��radstackЭ��ջ��Ӧ�ṹ cmTransportAddress һ�� (len:44)
struct TH323TransportAddress
{
    u16  m_wlength; /* length in bytes of route */
    u32  m_dwip;
    u16  m_wport;
    int  m_ntype;
    u32  m_adwroute[7];
    int  m_ndistribution;
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//(len:310)
struct TH323EPGKIDAlias
{
protected:
	int  m_ntype;        //������
    u16  m_wlength;      //������
    char m_szAlias[256];
    int  m_npnType;      //������ 
    TH323TransportAddress m_transport;
public:
	void SetIDtype( int ntype ){ m_ntype = htonl(ntype); }
	int  GetIDtype( void ){ return ntohl(m_ntype); }
	void SetIDlength( u16 wlength ){ m_wlength = htons(wlength); }
	u16  GetIDlength( void ){ return ntohs(m_wlength); }
	void SetIDpnType( int npnType ){ m_npnType = htonl(npnType); }
	int  GetIDpnType( void ){ return ntohl(m_npnType); }
	void SetIDAlias( char *pszAlias ){ memcpy( m_szAlias, pszAlias, 256 ); }
	char*  GetIDAlias( void ){ return m_szAlias; }
	void SetIDtransport( TH323TransportAddress *ptransport ){ memcpy( (void*)&m_transport, (void*)ptransport, sizeof(TH323TransportAddress) ); }
	TH323TransportAddress*  GetIDtransport( void ){ return &m_transport; }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//TRASInfo����N+1���ݣ������RAS��Ϣͬ��������(len:622)
struct TRASInfo 
{
protected:
    u32 m_dwGKIp;                   // �����gk��ַ��������
    u32 m_dwRRQIp;                  // ����ĺ��з����ַ��calladdress��������
    TH323EPGKIDAlias m_tGKIDAlias;  // �����GKID
    TH323EPGKIDAlias m_tEPIDAlias;  // �����EPID
    s8  m_achE164Num[MAXLEN_E164+1];// �����E164

public:
    TRASInfo() : m_dwGKIp(0),
                 m_dwRRQIp(0)
    {
        memset( &m_tGKIDAlias, 0, sizeof(m_tGKIDAlias) );
        memset( &m_tEPIDAlias, 0, sizeof(m_tEPIDAlias) );
        memset( &m_achE164Num, 0, sizeof(m_achE164Num) );
    }
    void SetGKIp(u32 dwIp){ m_dwGKIp = htonl(dwIp);    }
    u32  GetGKIp(void) { return ntohl(m_dwGKIp);    }
    void SetRRQIp(u32 dwIp){ m_dwRRQIp = htonl(dwIp);    }
    u32  GetRRQIp(void) { return ntohl(m_dwRRQIp);    }
    TH323EPGKIDAlias *GetGKID(void) { return &m_tGKIDAlias;    }
    void SetGKID(TH323EPGKIDAlias *ptH323GKID){ memcpy( &m_tGKIDAlias, ptH323GKID, sizeof(TH323EPGKIDAlias));    }
    TH323EPGKIDAlias *GetEPID(void) { return &m_tEPIDAlias;    }
    void SetEPID(TH323EPGKIDAlias *ptH323EPID){ memcpy( &m_tEPIDAlias, ptH323EPID, sizeof(TH323EPGKIDAlias));    }
    LPCSTR GetMcuE164(void) { return m_achE164Num; }
    void SetMcuE164(LPCSTR lpszE164Alias) 
    {
        if ( NULL != lpszE164Alias )
        {
            memcpy( m_achE164Num, lpszE164Alias, sizeof(m_achE164Num));    
            m_achE164Num[sizeof(m_achE164Num)-1] = '\0';
        }
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//ҵ����Ϣ�࣬�����28K������Ϣ
class CServMsg
{
protected:
	u16     m_wSerialNO;            //��ˮ��
	u8      m_bySrcDriId;           //ԴDRI���
	u8      m_bySrcMtId;            //Դ�ն˺�
	u8      m_bySrcSsnId;           //Դ�Ự��
	u8      m_byDstDriId;           //Ŀ��DRI���
    u8      m_byDstMtId;            //Ŀ���ն˺�
	u8      m_byMcuId;              //MCU��
	u8      m_byChnIndex;           //ͨ��������
    u8      m_byConfIdx;            //����������
	CConfId m_cConfId;              //�����
	u16		m_wEventId;             //�¼���
	u16		m_wTimer;               //��ʱ
	u16		m_wErrorCode;           //������
	u16		m_wMsgBodyLen;          //��Ϣ�峤��
    u8      m_byTotalPktNum;        //�ܰ�����������Ҫ�а����͵���Ϣ��
    u8      m_byCurPktIdx;          //��ǰ����������0��ʼ��
	u8      m_abyReserverd[12];     //�����ֽ�
	u8      m_abyMsgBody[SERV_MSG_LEN-SERV_MSGHEAD_LEN];    //��Ϣ��
public:
	void  SetSerialNO(u16  wSerialNO){ m_wSerialNO = htons(wSerialNO);} 
    u16   GetSerialNO( void ) const { return ntohs(m_wSerialNO); }
    void  SetSrcDriId(u8   bySrcDriId){ m_bySrcDriId = bySrcDriId;} 
    u8    GetSrcDriId( void ) const { return m_bySrcDriId; }
    void  SetSrcMtId(u8   bySrcMtId){ m_bySrcMtId = bySrcMtId;} 
    u8    GetSrcMtId( void ) const { return m_bySrcMtId; }
    void  SetSrcSsnId(u8   bySrcSsnId){ m_bySrcSsnId = bySrcSsnId;} 
    u8    GetSrcSsnId( void ) const { return m_bySrcSsnId; }
    void  SetDstDriId(u8   byDstDriId){ m_byDstDriId = byDstDriId;} 
    u8    GetDstDriId( void ) const { return m_byDstDriId; }  
    void  SetDstMtId(u8   byDstMtId){ m_byDstMtId = byDstMtId;} 
    u8    GetDstMtId( void ) const { return m_byDstMtId; }
    void  SetMcuId(u8   byMcuId){ m_byMcuId = byMcuId;} 
    u8    GetMcuId( void ) const { return m_byMcuId; }
    void  SetChnIndex(u8   byChnIndex){ m_byChnIndex = byChnIndex;} 
    u8    GetChnIndex( void ) const { return m_byChnIndex; }
    void  SetConfIdx(u8   byConfIdx){ m_byConfIdx = byConfIdx;} 
    u8    GetConfIdx( void ) const { return m_byConfIdx; } 
    void  SetEventId(u16  wEventId){ m_wEventId = htons(wEventId);} 
    u16   GetEventId( void ) const { return ntohs(m_wEventId); }
    void  SetTimer(u16  wTimer){ m_wTimer = htons(wTimer);} 
    u16   GetTimer( void ) const { return ntohs(m_wTimer); }
    void  SetErrorCode(u16  wErrorCode){ m_wErrorCode = htons(wErrorCode);} 
    u16   GetErrorCode( void ) const { return ntohs(m_wErrorCode); }
    void  SetTotalPktNum(u8 byPktNum) { m_byTotalPktNum = byPktNum; }
    u8    GetTotalPktNum( void ) { return m_byTotalPktNum; }
    void  SetCurPktIdx(u8 byPktIdx) { m_byCurPktIdx = byPktIdx; }
    u8    GetCurPktIdx( void ) { return m_byCurPktIdx; }

	void Init( void );
	void SetNoSrc(){ SetSrcSsnId( 0 ); }
	void SetMsgBodyLen( u16  wMsgBodyLen );
	CServMsg( void );//constructor
	CServMsg( u8   * const pbyMsg, u16  wMsgLen );//constructor
	~CServMsg( void );//distructor
	void ClearHdr( void );//��Ϣͷ����
	CConfId GetConfId( void ) const;//��ȡ�������Ϣ
	void SetConfId( const CConfId & cConfId );//���û������Ϣ
	void SetNullConfId( void );//���û������ϢΪ��
	u16  GetMsgBodyLen( void ) const;//��ȡ��Ϣ�峤����Ϣ
	u16  GetMsgBody( u8   * pbyMsgBodyBuf, u16  wBufLen ) const;//��ȡ��Ϣ�壬���û�����BUFFER�������С���ضϴ���
	u8   * const GetMsgBody( void ) const;//��ȡ��Ϣ��ָ�룬�û������ṩBUFFER
	void SetMsgBody( u8   * const pbyMsgBody = NULL, u16  wLen = 0 );//������Ϣ��
	void CatMsgBody( u8   * const pbyMsgBody, u16  wLen );//�����Ϣ��
	u16  GetServMsgLen( void ) const;//��ȡ������Ϣ����
	u16  GetServMsg( u8   * pbyMsgBuf, u16  wBufLen ) const;//��ȡ������Ϣ�����û�����BUFFER�������С���ضϴ���
	u8   * const GetServMsg( void ) const;//��ȡ������Ϣָ�룬�û������ṩBUFFER
	void SetServMsg( u8   * const pbyMsg, u16  wLen );//����������Ϣ
	const CServMsg & operator= ( const CServMsg & cServMsg );//����������
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//�ش��ṹ (len:12)
struct TPrsParam
{
public:
	TTransportAddr   m_tLocalAddr;		//Ϊ���ؽ���RTP��ַ
	TTransportAddr	 m_tRemoteAddr;		//ΪԶ�˽���RTCP��ַ
public:
    void   SetLocalAddr(TTransportAddr tLocalAddr){ memcpy(&m_tLocalAddr,&tLocalAddr,sizeof(TTransportAddr)); } 
    TTransportAddr GetLocalAddr( void ) const { return m_tLocalAddr; }
    void   SetRemoteAddr(TTransportAddr tRemoteAddr){ memcpy(&m_tRemoteAddr,&tRemoteAddr,sizeof(TTransportAddr)); } 
    TTransportAddr GetRemoteAddr( void ) const { return m_tRemoteAddr; }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//�ش�ʱ���Ƚṹ (len:16)
struct TPrsTimeSpan
{
    TPrsTimeSpan()
    {
        memset(this, 0, sizeof(TPrsTimeSpan));
    }
    u16  m_wFirstTimeSpan;	  //��һ���ش�����
	u16  m_wSecondTimeSpan;   //�ڶ����ش�����
	u16  m_wThirdTimeSpan;    //�������ش�����
	u16  m_wRejectTimeSpan;   //���ڶ�����ʱ����
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//�ش��豸״̬ (len:3)
struct TPrsPerChStatus
{
public:
	u8  byUsed;         //0--δ������1--����
	u8	byCount;	    //���ٸ�������
	u8  byChlReserved;  //�Ƿ�Ϊ����ͨ��
	u8  byConfIndex;		//��¼ͨ������Ļ���Idx, zgc, 2007/04/24
public:
    void   SetUsed( void ){ byUsed = 1; }
    void   SetIdle( void ){ byUsed = 0; }
    BOOL   IsUsed( void ){ return byUsed; }
    
    u8     GetFeedNum( void ){ return byCount; }
    void   FeedNumAdd( void ){ byCount++; }
    void   FeedNumDec( void ){ byCount--; }

	void   SetReserved( BOOL bReserved ){ byChlReserved = bReserved; }
	BOOL   IsReserved( void ){ return byChlReserved; }

	//��¼ͨ������Ļ���Idx, zgc, 2007/04/24
	void   SetConfIdx( u8 byConfIdx )
	{
		if( byConfIdx > MAXNUM_MCU_CONF )
		{
			OspPrintf( TRUE, FALSE, "The conf idx %d is error!\n", byConfIdx );
			return;
		}
		byConfIndex = byConfIdx; 
	}
	u8	   GetConfIdx( void ){ return byConfIndex; }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//�ش��ṹ
struct TPrsStatus
{
public:
	TPrsPerChStatus   m_tPerChStatus[MAXNUM_PRS_CHNNL];		//���ؽ���RTP/RTCP���ĵ�ַ
	u8 GetIdleChlNum(void)
	{
		u8 nSum = 0;
		for(u8 byLp = 0; byLp < MAXNUM_PRS_CHNNL; byLp++)
		{
			if( !m_tPerChStatus[byLp].IsReserved() )
			{
				nSum++;
			}
		}
		return nSum;
	}

	//��¼ͨ������Ļ���Idx, zgc, 2007/04/24
	void SetChnConfIdx( u8 byChnIdx, u8 byConfIdx )
	{ 
		if( byChnIdx > MAXNUM_PRS_CHNNL || byConfIdx > MAXNUM_MCU_CONF )
		{
			OspPrintf( TRUE, FALSE, "The chn idx %d or conf idx %d is error!\n", byChnIdx, byConfIdx );
			return;
		}
		m_tPerChStatus[byChnIdx].SetConfIdx(byConfIdx); 
	}
	u8   GetChnConfIdx( u8 byChnIdx ){ return m_tPerChStatus[byChnIdx].GetConfIdx(); }
	
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//���������£����˺ͶԶ��ⲿģ������ͬ�����(len: 2)
struct TMSSynState  
{
    //��ͻ����
    enum EntityType
    {
        emNone      = 0,
        emMC        = 1,
        emMp        = 2,
        emMtAdp     = 3,
        emPeriEqp   = 4,
        emDcs       = 5,
        emMpc       = 0xFF
    };
    
protected:
    u8  m_byEntityType;       //δͬ����ʵ������
    u8  m_byEntityId;         //δͬ����ʵ���ID
    
public:
    TMSSynState(void){ SetNull(); }
    
    void SetNull(void){ memset( this, 0, sizeof(TMSSynState) ); }
    
    void SetEntityType(u8 byEntityType){ m_byEntityType = byEntityType; }
    u8   GetEntityType( void ) const{ return m_byEntityType; }
    void SetEntityId(u8 byEntityId){ m_byEntityId = byEntityId; }
    u8   GetEntityId( void ) const { return m_byEntityId; }
    
    BOOL32 IsSynSucceed(void) const { return m_byEntityType == emNone ? TRUE : FALSE; }    
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//����MCU״̬�ṹ (len: 6+1 + 128*11 + 1+1*11 + 4 + 5 + 2 + 7 + 4 = 1449 )
struct TMcuStatus: public TMcu
{
	enum eMcuRunningStatusMask
    {
        Mask_Mp				=  0x00000004,
        Mask_Mtadp			=  0x00000008,
		Mask_HDSC			=  0x00000020,
		Mask_MDSC			=  0x00000040,
		Mask_DSC			=  0x00000080,
		Mask_McuRunOk		=  0x80000000
    };
	
	u8		m_byPeriEqpNum;	                        //������Ŀ
	TEqp	m_atPeriEqp[MAXNUM_MCU_PERIEQP];	    //��������
	u8      m_byEqpOnline[MAXNUM_MCU_PERIEQP];      //�����Ƿ�����
	u32     m_dwPeriEqpIpAddr[MAXNUM_MCU_PERIEQP];  //����Ip��ַ
    
    u8      m_byPeriDcsNum;                         //DCS��Ŀ
    TEqp    m_atPeriDcs[MAXNUM_MCU_DCS];            //DCS����
    u8      m_byDcsOnline[MAXNUM_MCU_DCS];          //DCS�Ƿ�����
    u32     m_dwPeriDcsIpAddr[MAXNUM_MCU_DCS];      //DCS ip��ַ

    // xsl [8/26/2005] 
    u8      m_byOngoingConfNum;                     //mcu�ϼ�ʱ�������
    u8      m_byScheduleConfNum;                    //mcu��ԤԼ�������
    u16     m_wAllJoinedMtNum;                      //mcu����������ն˸���
    
    // ���� [5/29/2006]
    u8      m_byRegedGk;                            //�Ƿ�ɹ�ע��GK�����δ���û���ע��ʧ�ܣ���Ϊ0
	u16     m_wLicenseNum;							//��ǰLicense��
    TMSSynState m_tMSSynState;                      //��ǰ�������(������������Ч)
    
    // guzh [9/4/2006] 
    u8      m_byRegedMpNum;                         //��ǰ��ע���Mp����
    u8      m_byRegedMtAdpNum;                      //��ǰ��ע���H323 MtAdp����

    // guzh  [12/15/2006]
    u8      m_byNPlusState;                         //���ݷ���������״̬(mcuconst.h NPLUS_BAKSERVER_IDLE ��)
    u32     m_dwNPlusReplacedMcuIp;                 //������ݷ��������ڽ��湤���������ķ�����IP

	//zgc [12/21/2006]
	u8      m_byMcuIsConfiged;						//MCU�Ƿ����ù��ı�ʶ
	//zgc [07/26/2007]
	u8		m_byMcuCfgLevel;						// MCU������Ϣ�Ŀɿ�����
	
	//zgc [07/25/2007]
	//[31��24 23��16 15��8 7��0]
	//bit 2: no mp? ([0]no; [1]yes)
	//bit 3: no mtadp? ([0]no; [1]yes)
	//bit 4: no HDCS module?  ([0]no; [1]yes)
	//bit 5: no MDCS module?  ([0]no; [1]yes)
	//bit 7: no DSC module? ([0]no; [1]yes)
	//bit 31: MCU��ǰ�Ƿ���������? ([0]no; [1]yes)
	u32		m_dwMcuRunningState;					// MCU����״̬
	

protected:
    u32     m_dwPersistantRunningTime;              // MCU����ʱ�䣨��λ:s, linux����:497day��vx����:828day��
public:
	// xliang [11/20/2008] 
	u16		m_wAllHdiAccessMtNum;					// HDI��Ȩ����MT��������
	u16		m_wStdCriAccessMtNum;					// ��������������ݲ�֧�֣�Ԥ����
public:
	void SetIsExistMp( BOOL32 IsExistMp ) 
	{ 
		m_dwMcuRunningState = ntohl(m_dwMcuRunningState);
		SETBITSTATUS(m_dwMcuRunningState, Mask_Mp, IsExistMp) 
		m_dwMcuRunningState = htonl(m_dwMcuRunningState);
	}
	BOOL32 IsExistMp(void) const 
	{ 
		u32 dwMcuRunningState = ntohl(m_dwMcuRunningState);
		return GETBITSTATUS( dwMcuRunningState, Mask_Mp);
	}
	void SetIsExistMtadp( BOOL32 IsExistMtadp ) 
	{ 
		m_dwMcuRunningState = ntohl(m_dwMcuRunningState);
		SETBITSTATUS(m_dwMcuRunningState, Mask_Mtadp, IsExistMtadp)
		m_dwMcuRunningState = htonl(m_dwMcuRunningState);
	}
	BOOL32 IsExistMtadp(void) const 
	{ 
		u32 dwMcuRunningState = ntohl(m_dwMcuRunningState);
		return GETBITSTATUS( dwMcuRunningState, Mask_Mtadp);
	}
	void SetIsExistDSC( BOOL32 IsExistDSC ) 
	{
		m_dwMcuRunningState = ntohl(m_dwMcuRunningState);
		SETBITSTATUS(m_dwMcuRunningState, Mask_DSC, IsExistDSC)
		m_dwMcuRunningState = htonl(m_dwMcuRunningState);
	}
	BOOL32 IsExistDSC(void) const 
	{ 
		u32 dwMcuRunningState = ntohl(m_dwMcuRunningState);
		return GETBITSTATUS( dwMcuRunningState, Mask_DSC); 
	}
	void SetIsExistMDSC( BOOL32 IsExistDSC ) 
	{
		m_dwMcuRunningState = ntohl(m_dwMcuRunningState);
		SETBITSTATUS(m_dwMcuRunningState, Mask_MDSC, IsExistDSC)
		m_dwMcuRunningState = htonl(m_dwMcuRunningState);
	}
	BOOL32 IsExistMDSC(void) const 
	{ 
		u32 dwMcuRunningState = ntohl(m_dwMcuRunningState);
		return GETBITSTATUS( dwMcuRunningState, Mask_MDSC); 
	}
	void SetIsExistHDSC( BOOL32 IsExistDSC ) 
	{
		m_dwMcuRunningState = ntohl(m_dwMcuRunningState);
		SETBITSTATUS(m_dwMcuRunningState, Mask_HDSC, IsExistDSC)
		m_dwMcuRunningState = htonl(m_dwMcuRunningState);
	}
	BOOL32 IsExistHDSC(void) const 
	{ 
		u32 dwMcuRunningState = ntohl(m_dwMcuRunningState);
		return GETBITSTATUS( dwMcuRunningState, Mask_HDSC); 
	}
	void SetIsMcuRunOk( BOOL32 IsMcuRunOk ) 
	{
		m_dwMcuRunningState = ntohl(m_dwMcuRunningState);
		SETBITSTATUS(m_dwMcuRunningState, Mask_McuRunOk, IsMcuRunOk)
		m_dwMcuRunningState = htonl(m_dwMcuRunningState);
	}
	BOOL32 IsMcuRunOk(void) const 
	{ 
		u32 dwMcuRunningState = ntohl(m_dwMcuRunningState);
		return GETBITSTATUS( dwMcuRunningState, Mask_McuRunOk);
	}
    void SetPersistantRunningTime(u32 dwTime) { m_dwPersistantRunningTime = htonl(dwTime);    }
    u32  GetPersistantRunningTime(void) const { return ntohl(m_dwPersistantRunningTime);    }

    void Print(void) const
    {
        OspPrintf(TRUE, FALSE, "MCU Current Status: \n" );
        OspPrintf(TRUE, FALSE, "\tIs Run OK:%d\n", IsMcuRunOk() );
        OspPrintf(TRUE, FALSE, "\tExist mp: %d, Exist mtadp: %d, Exist dsc module<DSC.%d, MDSC.%d, HDSC.%d>\n",
				IsExistMp(), IsExistMtadp(), IsExistDSC(), IsExistMDSC(), IsExistHDSC());

        OspPrintf(TRUE, FALSE, "\tConfig file state: ");
        switch(m_byMcuCfgLevel) 
        {
        case MCUCFGINFO_LEVEL_NEWEST:
            OspPrintf(TRUE, FALSE, "Success\n");
            break;
        case MCUCFGINFO_LEVEL_PARTNEWEST:
            OspPrintf(TRUE, FALSE, "Partly success\n");
            break;
        case MCUCFGINFO_LEVEL_LAST:
            OspPrintf(TRUE, FALSE, "Read fail\n");
            break;
        case MCUCFGINFO_LEVEL_DEFAULT:
            OspPrintf(TRUE, FALSE, "No cfg file\n");
            break;
        default:
            OspPrintf(TRUE, FALSE, "level error!\n");
            break;
		}
        OspPrintf(TRUE, FALSE, "\tIs Mcu Configed: %d\n", m_byMcuIsConfiged);

        OspPrintf(TRUE, FALSE, "\tIsReggedGk:%d, Mp Num:%d, H323MtAdp Num:%d, PeirEqpNum:%d, DcsNum:%d\n", 
                  m_byRegedGk, m_byRegedMpNum, m_byRegedMtAdpNum, m_byPeriEqpNum, m_byPeriDcsNum);
        
        OspPrintf(TRUE, FALSE, "\tOngoingConf:%d, ScheduleConf:%d, AllJoinedMt:%d\n", 
                  m_byOngoingConfNum, m_byScheduleConfNum, ntohs(m_wAllJoinedMtNum));

        if ( m_byNPlusState != NPLUS_NONE )
        {
            OspPrintf(TRUE, FALSE, "\tNPlusState:%d, NPlus Replaced Mcu:0x%x\n", 
                m_byNPlusState, ntohl(m_dwNPlusReplacedMcuIp));
        }
        
        if (!m_tMSSynState.IsSynSucceed() )
        {
            OspPrintf(TRUE, FALSE, "\tMS conflict entity ID:%d, Type:%d\n", 
                      m_tMSSynState.GetEntityId(), m_tMSSynState.GetEntityType() );
        }
        {
            u32 dwPersistantTime = GetPersistantRunningTime();

            u32 dwCutOffTime = 0;
            u32 dwDay = dwPersistantTime/(3600*24);
            dwCutOffTime += (3600*24) * dwDay;
            u32 dwHour = (dwPersistantTime - dwCutOffTime)/3600;
            dwCutOffTime += 3600 * dwHour;
            u32 dwMinute = (dwPersistantTime - dwCutOffTime)/60;
            dwCutOffTime += 60 * dwMinute;
            u32 dwSecond = dwPersistantTime - dwCutOffTime;
            if ( 0 == dwDay )
            {
                OspPrintf(TRUE, FALSE, "\tPersistant running time: %d.h %d.m %d.s\n",
                                         dwHour, dwMinute, dwSecond );                
            }
            else
            {
                OspPrintf(TRUE, FALSE, "\tPersistant running time: %d.day %d.h %d.m %d.s\n",
                                         dwDay, dwHour, dwMinute, dwSecond );                
            }
        }
		// xliang [11/20/2008] HDI �����ն�����
		OspPrintf(TRUE, FALSE, "\tHDI access Mt Num: %d\n", m_wAllJoinedMtNum);
	
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TRecState 
{
protected:	
	u8      m_byRecState;  //��ǰ�ն�¼��״̬
							//bit3-4: 00:��¼�� 01:¼�� 10:¼����ͣ
							//bit0:   0:ʵʱ¼�� 1:��֡¼��
public:	
	BOOL IsNoRecording( void ) const	{ return( ( m_byRecState & 0x18 ) == 0x00 ? TRUE : FALSE ); }
	void SetNoRecording( void )	{ m_byRecState &= ~0x18; }
	BOOL IsRecording( void ) const	{ return( ( m_byRecState & 0x18 ) == 0x08 ? TRUE : FALSE ); }
	void SetRecording( void )	{ SetNoRecording(); m_byRecState |= 0x08; }
	BOOL IsRecPause( void ) const	{ return( ( m_byRecState & 0x18 ) == 0x10 ? TRUE : FALSE ); }
	void SetRecPause( void )	{ SetNoRecording(); m_byRecState |= 0x10; }
	//�Ƿ��ڳ�֡¼��״̬
	BOOL IsRecSkipFrame() const { return ( !IsNoRecording() && ( ( m_byRecState & 0x01 ) == 0x01 ) ); }
	void SetRecSkipFrame( BOOL bSkipFrame )      { if( bSkipFrame ) m_byRecState |= 0x01;else m_byRecState &= ~0x01;};
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//�ն����ʽṹ len: 14
struct TMtBitrate : public TMt
{
protected:
    u16     m_wSendBitRate;              //�ն˷�������(��λ:Kbps,1K=1024)
    u16     m_wRecvBitRate;              //�ն˽�������(��λ:Kbps,1K=1024)
    u16     m_wH239SendBitRate;          //�ն˵ڶ�·��Ƶ��������(��λ:Kbps,1K=1024)
    u16     m_wH239RecvBitRate;          //�ն˵ڶ�·��Ƶ��������(��λ:Kbps,1K=1024)
    
public:
    TMtBitrate(void) { memset(this, 0, sizeof(TMtBitrate)); }
    void   SetSendBitRate(u16  wSendBitRate){ m_wSendBitRate = htons(wSendBitRate);} 
    u16    GetSendBitRate( void ) const { return ntohs(m_wSendBitRate); }
    void   SetRecvBitRate(u16  wRecvBitRate){ m_wRecvBitRate = htons(wRecvBitRate);} 
    u16    GetRecvBitRate( void ) const { return ntohs(m_wRecvBitRate); }
    void   SetH239SendBitRate(u16  wH239SendBitRate){ m_wH239SendBitRate = htons(wH239SendBitRate);} 
    u16    GetH239SendBitRate( void ) const { return ntohs(m_wH239SendBitRate); }
    void   SetH239RecvBitRate(u16  wH239RecvBitRate){ m_wH239RecvBitRate = htons(wH239RecvBitRate);} 
    u16    GetH239RecvBitRate( void ) const { return ntohs(m_wH239RecvBitRate); }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//�ն�״̬�ṹ(len:64)
struct TMtStatus : public TMtBitrate
{
protected:
    u8      m_byDecoderMute;             //�Ƿ���뾲��
	u8      m_byCaptureMute;             //�Ƿ�ɼ�����
    u8      m_byHasMatrix;               //�Ƿ��о���
	u8      m_byIsEnableFECC;            //�Ƿ���ң������ͷ
	u8      m_bySendAudio;               //�Ƿ����ڴ�����Ƶ
	u8      m_bySendVideo;               //�Ƿ����ڴ�����Ƶ
	u8      m_byReceiveVideo;            //�Ƿ����ڽ�����Ƶ
	u8      m_byReceiveAudio;            //�Ƿ����ڽ�����Ƶ
	u8      m_byRcvVideo2;				 //�Ƿ��ڽ��յڶ���Ƶ
	u8      m_bySndVideo2;               //�Ƿ��ڷ��͵ڶ���Ƶ
	u8      m_byInMixing;                //�Ƿ����ڲμӻ���
	u8      m_byVideoFreeze;             //�Ƿ񶳽�ͼ��
    // guzh [3/7/2007] ���ֶδ�4.0R4��ʼȡ��������Ϊ�Ƿ���ƵԴ��ʧ
	//u8      m_bySelPolling;              //�Ƿ�������ѯѡ��
    u8      m_byVideoLose;               //�Ƿ���ƵԴ��ʧ
	u8      m_bySelByMcsDrag;            //�Ƿ��ǻ������ѡ��
    u8      m_byDecoderVolume;           //��������
	u8      m_byCaptureVolume;           //�ɼ�����
	u8  	m_byCurVideo;	             //��ǰ��ƵԴ(1)
	u8  	m_byCurAudio;	             //��ǰ��ƵԴ(1)    
	u8      m_byH239VideoFormat;         //�ն˵ڶ�·��Ƶ�ֱ���
	u8      m_byMtBoardType;             //�ն˵İ忨����(MT_BOARD_WIN, MT_BOARD_8010 ��)
    u8      m_byInTvWall;                //�ն��Ƿ����ڵ���ǽ��
    u8      m_byInHdu;                   //�ն��Ƿ�����HDU��   4.6 �¼�   jlb
    u8      m_byExVideoSourceNum;        //�ն���չ��ƵԴ����
	u8		m_byVideoMediaLoop;			 //�ն�Զ�˻���״̬
	u8		m_byAudioMediaLoop;			 //�ն�Զ�˻���״̬
    u8      m_byIsInMixGrp;              //�Ƿ��ڻ�������
public:
	TMt		m_tVideoMt;		             //��ǰ���յ���Ƶ�ն�
	TMt		m_tAudioMt;		             //��ǰ���յ���Ƶ�ն�
	TRecState m_tRecState;               //�ն�¼��״̬
protected:
    TMt     m_tLastSelectVidMt;          //ѡ������Ƶ�ն�
	TMt	    m_tLastSelectAudMt;          //ѡ������Ƶ�ն�
public:
	TMtStatus( void )
	{
        Clear();
    }

    void Clear()
    {
		memset( this,0,sizeof(TMtStatus));
		SetDecoderMute(FALSE);
		SetCaptureMute(FALSE);
		SetHasMatrix(TRUE);
		SetIsEnableFECC(FALSE);
		SetSendAudio(FALSE);
		SetSendVideo(FALSE);
		SetInMixing(FALSE);
		SetReceiveVideo(FALSE);
        SetReceiveAudio(FALSE);
		SetVideoFreeze(FALSE);
		//SetSelPolling(FALSE);
        SetVideoLose(FALSE);
		SetSelByMcsDrag(FALSE);
		SetDecoderVolume(16);
		SetCaptureVolume(16);
		SetCurVideo(1);
		SetCurAudio(1);		
		SetRcvVideo2(FALSE);
		SetSndVideo2(FALSE);
        SetInTvWall(FALSE);
        SetIsInMixGrp(FALSE);
        SetMtBoardType(MT_BOARD_UNKNOW);
	}

    void   SetDecoderMute(BOOL bDecoderMute){ m_byDecoderMute = GETBBYTE(bDecoderMute);} 
    BOOL   IsDecoderMute( void ) const { return ISTRUE(m_byDecoderMute); }
    void   SetCaptureMute(BOOL bCaptureMute){ m_byCaptureMute = GETBBYTE(bCaptureMute);} 
    BOOL   IsCaptureMute( void ) const { return ISTRUE(m_byCaptureMute); }
    void   SetHasMatrix(BOOL bHasMatrix){ m_byHasMatrix = GETBBYTE(bHasMatrix);} 
    BOOL   IsHasMatrix( void ) const { return ISTRUE(m_byHasMatrix); }
    void   SetIsEnableFECC(BOOL bCamRCEnable){ m_byIsEnableFECC = GETBBYTE(bCamRCEnable);} 
    BOOL   IsEnableFECC( void ) const { return ISTRUE(m_byIsEnableFECC); }
    void   SetSendAudio(BOOL bSendAudio){ m_bySendAudio = GETBBYTE(bSendAudio);} 
    BOOL   IsSendAudio( void ) const { return ISTRUE(m_bySendAudio); }
    void   SetSendVideo(BOOL bSendVideo){ m_bySendVideo = GETBBYTE(bSendVideo);} 
    BOOL   IsSendVideo( void ) const { return ISTRUE(m_bySendVideo); }
    void   SetInMixing(BOOL bInMixing){ m_byInMixing = GETBBYTE(bInMixing);} 
    BOOL   IsInMixing( void ) const { return ISTRUE(m_byInMixing); }
    void   SetReceiveAudio(BOOL bRcv) { m_byReceiveAudio = GETBBYTE(bRcv); }
    BOOL   IsReceiveAudio() const { return ISTRUE(m_byReceiveAudio); }
	void   SetReceiveVideo(BOOL bReceiveVideo){ m_byReceiveVideo = GETBBYTE(bReceiveVideo);} 
    BOOL   IsReceiveVideo( void ) const { return ISTRUE(m_byReceiveVideo); }
    void   SetVideoFreeze(BOOL bVideoFreeze){ m_byVideoFreeze = GETBBYTE(bVideoFreeze);} 
    BOOL   IsVideoFreeze( void ) const { return ISTRUE(m_byVideoFreeze); }
    /*
    void   SetSelPolling(BOOL bSelPolling){ m_bySelPolling = GETBBYTE(bSelPolling);} 
    BOOL   IsSelPolling( void ) const { return ISTRUE(m_bySelPolling); }
    */
    void   SetVideoLose(BOOL bIsLose){ m_byVideoLose = GETBBYTE(bIsLose);} 
    BOOL   IsVideoLose( void ) const { return ISTRUE(m_byVideoLose); }

    void   SetIsInMixGrp(BOOL bDiscuss) { m_byIsInMixGrp = GETBBYTE(bDiscuss); }
    BOOL   IsInMixGrp(void) const { return ISTRUE(m_byIsInMixGrp); }    
    void   SetSelByMcsDrag( u8 bySelMediaMode ){ m_bySelByMcsDrag = bySelMediaMode;} 
    u8     GetSelByMcsDragMode( void ) const { return m_bySelByMcsDrag; }
    void   SetDecoderVolume(u8   byDecoderVolume){ m_byDecoderVolume = byDecoderVolume;} 
    u8     GetDecoderVolume( void ) const { return m_byDecoderVolume; }
    void   SetCaptureVolume(u8   byCaptureVolume){ m_byCaptureVolume = byCaptureVolume;} 
    u8     GetCaptureVolume( void ) const { return m_byCaptureVolume; }
    void   SetCurVideo(u8   byCurVideo){ m_byCurVideo = byCurVideo;} 
    u8     GetCurVideo( void ) const { return m_byCurVideo; }
    void   SetCurAudio(u8   byCurAudio){ m_byCurAudio = byCurAudio;} 
    u8     GetCurAudio( void ) const { return m_byCurAudio; }    
    void   SetH239VideoFormat(u8 byH239VideoFormat){ m_byH239VideoFormat = byH239VideoFormat;} 
    u8     GetH239VideoFormat( void ) const { return m_byH239VideoFormat; }
    void   SetMtBoardType(u8 byType) { m_byMtBoardType = byType; }
	u8     GetMtBoardType() const {return m_byMtBoardType; }
	void   SetVideoMt(TMt tVideoMt){ m_tVideoMt = tVideoMt;} 
    TMt    GetVideoMt( void ) const { return m_tVideoMt; }
    void   SetAudioMt(TMt tAudioMt){ m_tAudioMt = tAudioMt;} 
    TMt    GetAudioMt( void ) const { return m_tAudioMt; }

    void	SetMediaLoop(u8 byMode, BOOL32 bOn) 
    { 
        if (MODE_VIDEO == byMode)
        {
            m_byVideoMediaLoop = GETBBYTE(bOn);
        }
        else if (MODE_AUDIO == byMode)
        {
            m_byAudioMediaLoop = GETBBYTE(bOn);
        }
    }
    BOOL    IsMediaLoop(u8 byMode)
    {
        if (MODE_VIDEO == byMode)
        {
            return ISTRUE(m_byVideoMediaLoop); 
        }
        else if (MODE_AUDIO == byMode)
        {
            return ISTRUE(m_byAudioMediaLoop); 
        }

        return FALSE;
    }
    // guzh [2/28/2007] ������Ϊѡ���б�ͻָ�ʹ�ã������ʹ��
	void   SetSelectMt(TMt tSeleteMt, u8 byMode ) 
    {
        if ( byMode == MODE_AUDIO || byMode == MODE_BOTH )
        {
            m_tLastSelectAudMt = tSeleteMt;
        }
        if ( byMode == MODE_VIDEO || byMode == MODE_BOTH )
        {
            m_tLastSelectVidMt = tSeleteMt;
        }        
    }
	TMt    GetSelectMt( u8 byMode ) const 
    { 
        if ( byMode == MODE_AUDIO )
        {
            return m_tLastSelectAudMt;
        }
        else if ( byMode == MODE_VIDEO )
        {
            return m_tLastSelectVidMt;
        }    
        else 
        {
            TMt tNullMt;
            tNullMt.SetNull();
            return tNullMt;
        }
    }

	void   SetRcvVideo2(BOOL bRcv) { m_byRcvVideo2 = GETBBYTE(bRcv);}
    BOOL   IsRcvVideo2() const {return ISTRUE(m_byRcvVideo2);}
    void   SetSndVideo2(BOOL bSend) { m_bySndVideo2 = GETBBYTE(bSend); }
	BOOL   IsSndVideo2() const { return ISTRUE(m_bySndVideo2); }
    void   SetExVideoSrcNum(u8 byNum) { m_byExVideoSourceNum = byNum; }
    u8     GetExVideoSrcNum(void) const { return m_byExVideoSourceNum; }

    void   SetInTvWall(BOOL bInTvWall){ m_byInTvWall = GETBBYTE(bInTvWall);} 
    BOOL   IsInTvWall( void ) const { return ISTRUE(m_byInTvWall); }
	//4.6 �¼� jlb
	void   SetInHdu(BOOL bInHdu){ m_byInHdu = GETBBYTE(bInHdu);} 
    BOOL   IsInHdu( void ) const { return ISTRUE(m_byInHdu); }

	void  SetTMt( TMt tMt ){ memcpy( this, &tMt, sizeof(tMt) ); }
	const TMt & GetMt( void ) const; //��ȡ�ն˽ṹ
	void  AddSelByMcsMode( u8 byMode )
	{
		if( ( m_bySelByMcsDrag == MODE_VIDEO && byMode == MODE_AUDIO ) || 
			( m_bySelByMcsDrag == MODE_AUDIO && byMode == MODE_VIDEO ) || 
			m_bySelByMcsDrag == MODE_BOTH )
		{
			m_bySelByMcsDrag = MODE_BOTH;
		}
		else
		{
			m_bySelByMcsDrag = byMode;
		}
	}
	
	void RemoveSelByMcsMode( u8 byMode )
	{
		if( byMode == MODE_BOTH )
		{
			m_bySelByMcsDrag = MODE_NONE;
		}
		else if( byMode == MODE_AUDIO )
		{
			if( m_bySelByMcsDrag == MODE_BOTH )
			{
				m_bySelByMcsDrag = MODE_VIDEO;
			}
			else if( m_bySelByMcsDrag == MODE_AUDIO )
			{
				m_bySelByMcsDrag = MODE_NONE;
			}
		}
		else if( byMode == MODE_VIDEO )
		{
			if( m_bySelByMcsDrag == MODE_BOTH )
			{
				m_bySelByMcsDrag = MODE_AUDIO;
			}
			else if( m_bySelByMcsDrag == MODE_VIDEO )
			{
				m_bySelByMcsDrag = MODE_NONE;
			}
		}
	}

	void Print( void ) const
	{
		OspPrintf( TRUE, FALSE, "Mcu%dMt%d status:\n", GetMcuId(), GetMtId() ); 
        OspPrintf( TRUE, FALSE, "	m_byMtBoardType = %d\n", m_byMtBoardType ); 
		OspPrintf( TRUE, FALSE, "	m_byDecoderMute = %d\n", m_byDecoderMute ); 
		OspPrintf( TRUE, FALSE, "	m_byCaptureMute = %d\n", m_byCaptureMute );
		OspPrintf( TRUE, FALSE, "	m_byHasMatrix = %d\n", m_byHasMatrix );
        OspPrintf( TRUE, FALSE, "	m_byExVideoSourceNum = %d\n", m_byExVideoSourceNum );
		OspPrintf( TRUE, FALSE, "	m_byIsEnableFECC = %d\n", m_byIsEnableFECC );
		OspPrintf( TRUE, FALSE, "	m_bySendAudio = %d\n", m_bySendAudio );
		OspPrintf( TRUE, FALSE, "	m_bySendVideo = %d\n", m_bySendVideo );
        OspPrintf( TRUE, FALSE, "   m_byRecvAudio = %d\n", m_byReceiveAudio );
        OspPrintf( TRUE, FALSE, "   m_byRecvVideo = %d\n", m_byReceiveVideo );
		OspPrintf( TRUE, FALSE, "	m_byInMixing = %d\n", m_byInMixing );
        OspPrintf( TRUE, FALSE, "	m_byIsInMixGrp = %d\n", m_byIsInMixGrp );
		OspPrintf( TRUE, FALSE, "	m_byVideoLose = %d\n", m_byVideoLose );
		OspPrintf( TRUE, FALSE, "	m_bySelByMcsDrag = %d\n", m_bySelByMcsDrag );
		OspPrintf( TRUE, FALSE, "	m_byDecoderVolume = %d\n", m_byDecoderVolume );
		OspPrintf( TRUE, FALSE, "	m_byCurVideo = %d\n", m_byCurVideo );
        OspPrintf( TRUE, FALSE, "	m_byCurAudio = %d\n", m_byCurAudio );
		OspPrintf( TRUE, FALSE, "	m_wSendBitRate = %d\n", ntohs(m_wSendBitRate) );
		OspPrintf( TRUE, FALSE, "	m_wRecvBitRate = %d\n", ntohs(m_wRecvBitRate) );
		OspPrintf( TRUE, FALSE, "	m_wH239SendBitRate = %d\n", ntohs(m_wH239SendBitRate) );
		OspPrintf( TRUE, FALSE, "	m_wH239RecvBitRate = %d\n", ntohs(m_wH239RecvBitRate) );
		OspPrintf( TRUE, FALSE, "	m_byH239VideoFormat = %d\n", m_byH239VideoFormat );
        OspPrintf( TRUE, FALSE, "	m_byVideoMediaLoop = %d\n", m_byVideoMediaLoop );
        OspPrintf( TRUE, FALSE, "	m_byAudioMediaLoop = %d\n", m_byAudioMediaLoop );
		if( m_tVideoMt.GetType() == TYPE_MT )
		{
			OspPrintf( TRUE, FALSE, "	SrcVideo: mcu%dmt%d\n", m_tVideoMt.GetMcuId(), m_tVideoMt.GetMtId() );
		}
		else
		{
            if (m_tVideoMt.GetEqpId() != 0)
            {
                OspPrintf( TRUE, FALSE, "	SrcVideo: eqp%d\n", m_tVideoMt.GetEqpId() );
            }
            else
            {
                OspPrintf( TRUE, FALSE, "	SrcVideo: NULL\n" );
            }
			
		}

		if( m_tAudioMt.GetType() == TYPE_MT )
		{
			OspPrintf( TRUE, FALSE, "	SrcAudio: mcu%dmt%d\n", m_tAudioMt.GetMcuId(), m_tAudioMt.GetMtId() );
		}
		else
		{
            if (m_tAudioMt.GetEqpId() != 0)
            {
                OspPrintf( TRUE, FALSE, "	SrcAudio: eqp%d\n", m_tAudioMt.GetEqpId() );
            }
            else
            {
                OspPrintf( TRUE, FALSE, "	SrcAudio: NULL\n" );
            }			
		}

        if (!m_tLastSelectVidMt.IsNull())
        {   
            OspPrintf( TRUE, FALSE, "	Select Video MT: mcu%dmt%d\n", 
                m_tLastSelectVidMt.GetMcuId(), m_tLastSelectVidMt.GetMtId() );
        }
        else
        {
            OspPrintf( TRUE, FALSE, "	Select Video MT: NULL\n" );
        }
        if (!m_tLastSelectAudMt.IsNull())
        {   
            OspPrintf( TRUE, FALSE, "	Select Audio MT: mcu%dmt%d\n", 
                   m_tLastSelectAudMt.GetMcuId(), m_tLastSelectAudMt.GetMtId() );
        }
        else
        {
            OspPrintf( TRUE, FALSE, "	Select Audio MT: NULL\n" );
        }      
	}

}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TTWMember : public TMt
{
    u8  byMemberType;     //��Ա����
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//HDU�ն˳�Ա
struct THduMember:public TMt
{
    u8 byMemberType;
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;


//�������ֵ���ǽ״̬�ṹ
struct TTvWallStatus
{
    u8        byOutputMode;  //TW_OUTPUTMODE_AUDIO : ֻ�����Ƶ
                             //TW_OUTPUTMODE_VIDEO : ֻ�����Ƶ
                             //TW_OUTPUTMODE_BOTH  : ͬʱ�������Ƶ
    u8        byChnnlNum;    //�ŵ���
    TTWMember atVideoMt[MAXNUM_PERIEQP_CHNNL]; //ÿ���ŵ���Ӧ�նˣ�MCU��Ϊ0��ʾ��
}
#ifndef WIN32
__attribute__((packed))
#endif
;

/*----------------------------------------------------------------------
�ṹ����THduChnStatus
��;  ��
----------------------------------------------------------------------*/
struct THduChnStatus
{
    enum EHduChnStatus
    {
        eIDLE   = 0, //����
        eREADY  = 1, //׼��
        eNORMAL = 2  //����
    };

public:

    void   SetStatus( u8 byStatus ) { m_byStatus = byStatus; };
    u8     GetStatus( void ) { return m_byStatus; }
    
    BOOL32 IsNull( void ) const { return m_tHdu.IsNull(); }
    void   SetNull( void ) { m_tHdu.SetNull(); }
        
    void   SetChnIdx( u8 byChnIdx ) { m_byChnIdx = byChnIdx; }
    u8     GetChnIdx( void ) const { return m_byChnIdx; }
    
    void   SetEqp( TEqp tHdu ) { m_tHdu = tHdu; }
    TEqp   GetEqp( void ) const { return m_tHdu; }
    u8     GetEqpId( void ) const { return m_tHdu.GetEqpId(); }	

    void   SetSchemeIdx( u8 bySchemeIdx ) { m_bySchemeIdx = bySchemeIdx; };
    u8     GetSchemeIdx( void ) { return m_bySchemeIdx; }

	u8     GetVolume( void ){ return m_byVolume; }
	void   SetVolume( u8 byVolume ){ m_byVolume = byVolume; }

	BOOL32   GetIsMute( void ){ return m_byMute; }
	void   SetIsMute( BOOL32 byIsMute ){ m_byMute = GETBBYTE(byIsMute); }

private:
	u8 m_byStatus;	  // HduChnStatus
	u8 m_byChnIdx;
    u8 m_bySchemeIdx; // ���ڱ�ʹ��Ԥ���������� 
    u8 m_byVolume;
	u8 m_byMute;      // �Ƿ���
    TEqp m_tHdu;

} 
#ifndef WIN32
__attribute__ ((packed)) 
#endif
;


//HDU״̬�ṹ
struct THduStatus
{
    u8        byOutputMode;  //HDU_OUTPUTMODE_AUDIO : ֻ�����Ƶ
	                         //HDU_OUTPUTMODE_VIDEO : ֻ�����Ƶ
	                         //HDU_OUTPUTMODE_BOTH  : ͬʱ�������Ƶ
    u8        byChnnlNum;    //�ŵ���

    THduMember atVideoMt[MAXNUM_HDU_CHANNEL]; //ÿ���ŵ���Ӧ�նˣ�MCU��Ϊ0��ʾ�� //???

	THduChnStatus atHduChnStatus[MAXNUM_HDU_CHANNEL];
}
#ifndef WIN32
__attribute__((packed))
#endif
;



//˫�غ�
struct TDoublePayload
{
protected:
	u8  m_byRealPayload;    //ԭý���ʽ
	u8  m_byActivePayload;  //�ý���ʽ
public:
    TDoublePayload()
	{
		Reset();
	}
	void Reset()
	{
		m_byRealPayload = MEDIA_TYPE_NULL;
		m_byActivePayload = MEDIA_TYPE_NULL;
	}
	void SetRealPayLoad(u8 byRealPayload)
	{
		m_byRealPayload = byRealPayload;
	}
	u8 GetRealPayLoad()
	{
		return m_byRealPayload;
	}

	void SetActivePayload(u8 byActivePayload)
	{
		m_byActivePayload = byActivePayload;
	}

	u8 GetActivePayload()
	{
		return m_byActivePayload;
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TTvWallStartPlay
{
protected:
    TMt m_tMt;
    TTransportAddr m_tRtcpBackAddr; //RTCP������ַ
    u8  m_byNeedPrs;
    TMediaEncrypt m_tVideoEncrypt;

public:
    TTvWallStartPlay(void)
    {
        Reset();
    }

    void Reset(void)
    {
		m_byNeedPrs = 0;
		m_tRtcpBackAddr.SetNull();
        m_tMt.SetNull();
        m_tVideoEncrypt.Reset();
    }

    void SetMt(const TMt &tMt)
    {
        m_tMt  = tMt;
    }

    TMt& GetMt(void)
    {
        return m_tMt;
    }

    TMediaEncrypt& GetVideoEncrypt(void)
    {
        return m_tVideoEncrypt;
    }

    void SetVideoEncrypt(TMediaEncrypt& tMediaEncrypt)
    {
        memcpy(&m_tVideoEncrypt, &tMediaEncrypt, sizeof(tMediaEncrypt));
    }

    void SetIsNeedByPrs(BOOL bNeedPrs)
    {
        m_byNeedPrs = bNeedPrs==TRUE?1:0;
    }

    BOOL IsNeedByPrs(void)
    {
        return (m_byNeedPrs != 0);
    }

    void GetRtcpBackAddr(u32 & dwRtcpBackIp, u16 & wRtcpBackPort)
    {
        dwRtcpBackIp = m_tRtcpBackAddr.GetIpAddr();
        wRtcpBackPort = m_tRtcpBackAddr.GetPort();
        return;
    }

    void SetRtcpBackAddr(u32 dwRtcpBackIp, u16 wRtcpBackPort)
    {
        m_tRtcpBackAddr.SetIpAddr(dwRtcpBackIp);
        m_tRtcpBackAddr.SetPort(wRtcpBackPort);
    }
}
#ifndef WIN32
__attribute__ ((packed))
#endif
;

//4.6�¼� �汾 jlb
struct THduStartPlay: public TTvWallStartPlay
{
protected:
	u8 m_byMode;   // MODE_AUDIO, MODE_VIDEO, MODE_BOTH
	u8 m_byReserved;
public:
	THduStartPlay()
	{
		m_byMode = 0;
		m_byReserved = 0;
	}

	void SetMode( u8 byMode ){ m_byMode = byMode; }
    u8   GetMode( void ){ return m_byMode; }

}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TMixerStart
{
protected:
    u8 m_byMixGroupId; //������Id
    u8 m_byMixDepth;   //�������
    u8 m_byAudioMode;  //������ʽ
    u8 m_byAudioMode2; //�ڶ�������ʽ(����Ϊ����Ϊ˫������ʽ)
    u8 m_byIsAllMix;   //ȫ�����
    TMediaEncrypt m_tAudioEncrypt;	//���ܲ���
    u8 m_byNeedPrs;
public:
    TMixerStart(void)
    {
        Reset();
    }
    void Reset(void)
    {
        m_byMixGroupId = MIXER_INVALID_GRPID;
        m_byMixDepth = 0;
        m_byAudioMode = MEDIA_TYPE_NULL;
        m_byAudioMode2 = MEDIA_TYPE_NULL;
        m_byIsAllMix = 0;
        m_byNeedPrs = 0;
        m_tAudioEncrypt.Reset();
    }

    void SetMixGroupId(u8 byGroupID)
    {
        m_byMixGroupId = byGroupID;
    }
    u8 GetMixGroupId()
    {
        return m_byMixGroupId;
    }
    void SetMixDepth(u8 byDepth)
    {
        m_byMixDepth = byDepth;
    }
    u8 GetMixDepth()
    {
        return m_byMixDepth;
    }
    void SetAudioMode(u8 byAudioMode)
    {
        m_byAudioMode = byAudioMode;
    }
    u8  GetAudioMode()
    {
        return m_byAudioMode;
    }
    void SetSecAudioMode(u8 byAudioMode)
    {
        m_byAudioMode2 = byAudioMode;
    }
    u8  GetSecAudioMode()
    {
        return m_byAudioMode2;
    }

    void SetIsAllMix(BOOL32 bIsAllMix)
    {
        m_byIsAllMix = (bIsAllMix ? 1:0 );
    }
    BOOL32 IsAllMix()
    {
        return (m_byIsAllMix != 0);
    }
    TMediaEncrypt& GetAudioEncrypt()
    {
        return m_tAudioEncrypt;
    }

    void SetAudioEncrypt(TMediaEncrypt& tMediaEncrypt)
    {
        memcpy(&m_tAudioEncrypt, &tMediaEncrypt, sizeof(tMediaEncrypt));
    }

    void SetIsNeedByPrs(BOOL32 bNeedPrs)
    {
        m_byNeedPrs = (TRUE == bNeedPrs) ? 1 : 0;
    }

    BOOL32 IsNeedByPrs(void)
    {
        return (m_byNeedPrs != 0);
    }
}
#ifndef WIN32
__attribute__((packed))
#endif
;

//������Ա�ṹ
struct TMixMember
{
    TMt m_tMember;
    u8  m_byVolume;                 //��Ա����
    u8  m_byAudioType;              //ý������
    TTransportAddr m_tAddr;         //��Ա�Ĵ����ַ
    TTransportAddr m_tRtcpBackAddr; //RTCP������ַ
}
#ifndef WIN32
__attribute__((packed)) 
#endif
;

//������״̬
struct TMixerGrpStatus
{
	enum EState 
	{ 
		IDLE   = 0,		//�û�����δʹ�� 
		READY  = 1,		//���鴴��,��δ��ʼ����
		MIXING = 2,		//���ڻ���
        WAIT_BEGIN = 200,
        WAIT_START_SPECMIX = 201,   //�ȴ���Ӧ״̬
        WAIT_START_AUTOMIX = 202,
        WAIT_START_VAC = 203,
        WAIT_STOP = 204,
	};

	u8       m_byGrpId;		  //������ID(0-4)
	u8       m_byGrpState;	  //��״̬
	u8       m_byGrpMixDepth; //�������
    u8       m_byConfId;      //����ID
protected:
    u8       m_abyMixMmb[MAXNUM_CONF_MT>>3];//���뾺��������Ա�б�
    u8       m_abyActiveMmb[MAXNUM_MIXER_DEPTH];//��ѡ�еĻ�����Ա�б�,0��ʾ��Ч��Ա
public:
	//����״̬��λ
	void Reset()
	{
		m_byGrpId       = 0xff;
		m_byGrpState    = IDLE;
		m_byGrpMixDepth = 0;
		memset( m_abyMixMmb ,0 ,sizeof(m_abyMixMmb) );
		memset( m_abyActiveMmb ,0 ,sizeof(m_abyActiveMmb) );
	}
    //��Ӳ��뾺���Ļ�����Ա
	// ���ó�ԱID�Ϸ�����TRUE,���򷵻�FALSE
    BOOL  AddMmb( u8   byMmbId)
	{
		u8   byByteIdx ,byBitIdx,byMask;
		if( byMmbId > MAXNUM_CONF_MT ||byMmbId==0)
			return FALSE;
		byMmbId--;
		byByteIdx = byMmbId>>3;
		byBitIdx  = byMmbId%8;
		byMask    = 1<<byBitIdx;

		m_abyMixMmb[byByteIdx] |= byMask;

		return TRUE;
	}

	//ɾ�����뾺���Ļ�����Ա
	// ���ó�ԱID�Ϸ�����TRUE,���򷵻�FALSE
	BOOL  RemoveMmb( u8   byMmbId)
	{

		u8   byByteIdx ,byBitIdx,byMask;
		if( byMmbId > MAXNUM_CONF_MT ||byMmbId==0)
			return FALSE;
		byMmbId--;
		byByteIdx = byMmbId>>3;
		byBitIdx  = byMmbId%8;
		byMask    = 1<<byBitIdx;

		m_abyMixMmb[byByteIdx] &= ~byMask;

		return TRUE;
	}

	//���ĳ��Ա�Ƿ�����ڲ��뾺���ı��У�
	//������ڷ���TRUE ,���򷵻�FALSE
	BOOL  IsContain( u8   byMmbId )
	{
		
		u8   byByteIdx ,byBitIdx,byMask;
		if( byMmbId > MAXNUM_CONF_MT ||byMmbId==0)
			return FALSE;
		byMmbId--;
		byByteIdx = byMmbId>>3;
		byBitIdx  = byMmbId%8;
		byMask    = 1<<byBitIdx;
		
		return (m_abyMixMmb[byByteIdx]&byMask)==0 ? FALSE:TRUE;
	}

	//������ڲ��뾺����������ĳ�Ա����
	u8    GetMmbNum()
	{
		u8   byNum=0;
		for( u8   byByteIdx=0 ;byByteIdx<(MAXNUM_CONF_MT>>3) ;byByteIdx++ )
		{
			for( u8   byBitIdx =0 ;byBitIdx<8 ;byBitIdx++ )
			{
				byNum += (m_abyMixMmb[byByteIdx]>>byBitIdx)&0x1;
			}
		}
		return byNum;
	}

	//������ڲ��뾺���Ļ�����ԱID
	//��� - abyMmb[] ���ڴ洢�μӻ����ĳ�ԱID
	//���� - bySize abyMmb[] �Ĵ�С
	//���� �μӻ����ĳ�Ա��
	u8    GetMixMmb( u8   abyMmb[] ,u8   bySize)
	{
		u8   byNum=0;
		for( u8   byByteIdx=0 ;byByteIdx<(MAXNUM_CONF_MT>>3) ;byByteIdx++ )
		{
			for( u8   byBitIdx =0 ;byBitIdx<8 ;byBitIdx++ )
			{
				if((m_abyMixMmb[byByteIdx]>>byBitIdx)&0x1 )
				{
					if( bySize <= byNum )
						return bySize;
					abyMmb[byNum]= byByteIdx*8+byBitIdx+1;
					byNum++;
				}
			}
		}
		return byNum;
	}
	
	//�ж�ָ����Ա�Ƿ�ѡ�л���
	BOOL IsActive( u8   byMmbId )
	{
		if( byMmbId ==0 )return FALSE;
		for( u8   byIdx =0 ;byIdx< MAXNUM_MIXER_DEPTH ;byIdx++ )
		{
			if( m_abyActiveMmb[byIdx]== byMmbId )
				return TRUE;
		}
		return FALSE;
	}
	
	//��ñ�ѡ�л�����Ա����
	u8   GetActiveMmbNum()
	{
		u8   byCount=0;
		for( u8   byIdx =0 ;byIdx< MAXNUM_MIXER_DEPTH ;byIdx++ )
			if( m_abyActiveMmb[byIdx] )byCount++;
		return byCount;
	}
	
	//��ñ�ѡ�л�����Ա
	//���: abyMmb[] - �洢��ѡ�л�����ԱID
	//����: bySize   - abyMmb ��С
	//����: abyMmb����Ч��Ա����
	u8   GetActiveMmb( u8   abyMmb[] ,u8   bySize )
	{
		u8   byCnt=0;
    	for( u8   byIdx =0 ;byIdx< min(bySize ,MAXNUM_MIXER_DEPTH) ;byIdx++ )
			if( m_abyActiveMmb[byIdx] )
			{
				abyMmb[byIdx] = m_abyActiveMmb[byIdx];
				byCnt++;
			}
			return byCnt;		
	}

	BOOL UpdateActiveMmb( u8   abyMmb[MAXNUM_MIXER_DEPTH] )
	{
		memcpy( m_abyActiveMmb ,abyMmb ,MAXNUM_MIXER_DEPTH);
		return TRUE;
	}
	
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;


//������״̬
struct TMixerStatus
{
	u8 m_byGrpNum; //����������
	TMixerGrpStatus	m_atGrpStatus[MAXNUM_MIXER_GROUP];
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//����ϳ���״̬
struct TVmpStatus
{
	enum EnumUseState 
	{ 
		IDLE,		//δ��ռ��
	    RESERVE,    //Ԥ��
        WAIT_START, //�ȴ���ʼ��Ӧ
		START,      //�����л���ϳ�
		WAIT_STOP,  //�ȴ�������Ӧ
	};
public:	
	u8        m_byUseState;	    //ʹ��״̬ 0-δʹ�� 1-ʹ��
	u8        m_byChlNum;       //ͨ����
#ifdef _ZGCDEBUG_
	u8		  m_byEncodeNum;	//����·��, zgc, 2007-06-20
#endif
    TVMPParam m_tVMPParam;      //�ϳɲ���
	u8		  m_bySubType;		//vmp�����ͣ����mcuconst.h�еĶ���// xliang [12/29/2008] 
	u8		  m_byBoardVer;		//����MPU A��/B��
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// ����ϳɳ�Ա�ṹ(Mcu -- Vmp)
struct TVMPMemberEx : public TVMPMember
{
public:
	void  SetMember( TVMPMember& tMember )
	{
		memcpy(this, &tMember, sizeof(tMember));
	}

	BOOL  SetMbAlias( const s8 *pAlias ) 
    { 
        BOOL bRet = FALSE;
        if( NULL != pAlias )
        {
            memcpy(achMbAlias, pAlias, sizeof(achMbAlias));
            achMbAlias[VALIDLEN_ALIAS] = '\0';
            bRet = TRUE;
        }
        return bRet; 
    }
	const s8* GetMbAlias(void) { return achMbAlias; }

protected:
	s8   achMbAlias[VALIDLEN_ALIAS+1];
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//����ϳɲ���(MCU��VMPͨѶ��)
class CKDVVMPParam
{
public:
	u8              m_byVMPStyle;      //����ϳɷ��,�μ�mcuconst.h�л���ϳɷ����
	u8    	        m_byEncType;       //ͼ���������
	u16             m_wBitRate;        //���������(Kbps)
	u16   	        m_wVideoWidth;     //ͼ����(default:720)
	u16   		    m_wVideoHeight;    //ͼ��߶�(default:576)
  	u8      	    m_byMemberNum;     //�μ���Ƶ���ϵĳ�Ա����
	TVMPMemberEx    m_atMtMember[MAXNUM_VMP_MEMBER];    //��Ƶ���ϳ�Ա�����ո��Ϸ�ʽ���߼����˳��
	TMediaEncrypt   m_tVideoEncrypt[MAXNUM_VMP_MEMBER];     //��Ƶ���ܲ���
	TDoublePayload  m_tDoublePayload[MAXNUM_VMP_MEMBER];

public:
    void Print(void)
    {
        OspPrintf(TRUE, FALSE, "VmpStyle:%d, EncType:%d, Bitrate:0x%x, VidWidth:%d, VidHeight:%d, MemNum:%d\n",
                  m_byVMPStyle, m_byEncType, ntohs(m_wBitRate), m_wVideoWidth, m_wVideoHeight, m_byMemberNum);
        for(u8 byIndex = 0; byIndex < MAXNUM_VMP_MEMBER; byIndex++)
        {
            if(0 != m_atMtMember[byIndex].GetMcuId() && 0 != m_atMtMember[byIndex].GetMtId())
            {
                OspPrintf(TRUE, FALSE, "McuId:%d, MtId:%d, MemType:%d, MemStatus:%d, RealPayLoad:%d, ActPayLoad:%d, EncrptMode:%d\n", 
                        m_atMtMember[byIndex].GetMcuId(), m_atMtMember[byIndex].GetMtId(), 
                        m_atMtMember[byIndex].GetMemberType(), m_atMtMember[byIndex].GetMemStatus(),
                        m_tDoublePayload[byIndex].GetRealPayLoad(), m_tDoublePayload[byIndex].GetActivePayload(),
                        m_tVideoEncrypt[byIndex].GetEncryptMode());
            }            
        }        
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//����ϳɲ���(MCU��VMPͨѶ��)
class CKDVNewVMPParam
{
public:
	u8              m_byVMPStyle;      //����ϳɷ��,�μ�mcuconst.h�л���ϳɷ����
	u8    	        m_byEncType;       //ͼ���������
	u8      	    m_byMemberNum;     //�μ���Ƶ���ϵĳ�Ա����
	TVMPMemberEx    m_atMtMember[MAXNUM_MPUSVMP_MEMBER];    //��Ƶ���ϳ�Ա�����ո��Ϸ�ʽ���߼����˳��
	TMediaEncrypt   m_tVideoEncrypt[MAXNUM_MPUSVMP_MEMBER];     //��Ƶ���ܲ���
	TDoublePayload  m_tDoublePayload[MAXNUM_MPUSVMP_MEMBER];

private:
	u16             m_wBitRate;        //���������(Kbps)
	u16   	        m_wVideoWidth;     //ͼ����(default:720)
	u16   		    m_wVideoHeight;    //ͼ��߶�(default:576)

public:
	void SetBitRate( u16 wBitRate ) { m_wBitRate = htons( wBitRate); }
	u16  GetBitRate() { return ntohs(m_wBitRate); }
	void SetVideoWidth( u16 wVidWidth ) { m_wVideoWidth = htons(wVidWidth); }
	u16  GetVideoWidth() { return ntohs(m_wVideoWidth); }
	void SetVideoHeight( u16 wVidHeight ) { m_wVideoHeight = htons(wVidHeight); }
	u16	 GetVideoHeight() { return ntohs(m_wVideoHeight); }

    void Print(void)
    {
        OspPrintf(TRUE, FALSE, "\tVmpStyle:\t%d\n\tEncType:\t%d\n\tBitrate:\t%d\n\tVidWidth:\t%d\n\tVidHeight:\t%d\n\tMemNum:\t\t%d\n",
			m_byVMPStyle, m_byEncType, GetBitRate(), GetVideoWidth(), GetVideoHeight(), m_byMemberNum);

        OspPrintf(TRUE, FALSE, "\nMem as follows:\n");

        for(u8 byIndex = 0; byIndex < MAXNUM_MPUSVMP_MEMBER; byIndex++)
        {
            if(0 != m_atMtMember[byIndex].GetMcuId() && 0 != m_atMtMember[byIndex].GetMtId())
            {
                OspPrintf(TRUE, FALSE, "\tMemIdx[%d]:\n", byIndex);
                OspPrintf(TRUE, FALSE, "\t\tMcuId:\t\t%d\n\t\tMtId:\t\t%d\n\t\tMemType:\t%d\n\t\tMemStatus:\t%d\n\t\tRealPayLoad:\t%d\n\t\tActPayLoad:\t%d\n\t\tEncrptMode:\t%d\n", 
					m_atMtMember[byIndex].GetMcuId(), m_atMtMember[byIndex].GetMtId(), 
					m_atMtMember[byIndex].GetMemberType(), m_atMtMember[byIndex].GetMemStatus(),
					m_tDoublePayload[byIndex].GetRealPayLoad(), m_tDoublePayload[byIndex].GetActivePayload(),
					m_tVideoEncrypt[byIndex].GetEncryptMode());
            }            
        }        
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TRecRtcpBack
{
protected:
    u32  m_tVideoIp;      //��ƵRTCP������ַ
    u16  m_tVideoPort;    //��ƵRTCP�����˿�
    u32  m_tAudioIp;      //��ƵRTCP������ַ
    u16  m_tAudioPort;    //��ƵRTCP�����˿�
    u32  m_tDStreamIp;    //˫��RTCP������ַ
    u16  m_tDStreamPort;  //˫��RTCP�����˿�

public:
    TRecRtcpBack(void)
	{
		Reset();
	}
	void Reset(void)
	{
		m_tVideoIp = 0xFFFFFFFF;
        m_tVideoPort = 0xFFFF;
        m_tAudioIp = 0xFFFFFFFF;
        m_tAudioPort = 0xFFFF;
        m_tDStreamIp = 0xFFFFFFFF;
        m_tDStreamPort = 0xFFFF;
	}

    void SetVideoAddr(u32 dwVideoIp, u16 wVideoPort)
    {
        m_tVideoIp = htonl(dwVideoIp);
        m_tVideoPort = htons(wVideoPort);
    }

    void GetVideoAddr(u32 &dwVideoIp, u16 &wVideoPort)
    {
        dwVideoIp = ntohl(m_tVideoIp);
        wVideoPort = ntohs(m_tVideoPort);
    }

    
    void SetAudioAddr(u32 dwAudioIp, u16 wAudioPort)
    {
        m_tAudioIp = htonl(dwAudioIp);
        m_tAudioPort = htons(wAudioPort);
    }

    void GetAudioAddr(u32 &dwAudioIp, u16 &wAudioPort)
    {
        dwAudioIp = ntohl(m_tAudioIp);
        wAudioPort = ntohs(m_tAudioPort);
    }

    
    void SetDStreamAddr(u32 dwDStreamIp, u16 wDStreamPort)
    {
        m_tDStreamIp = htonl(dwDStreamIp);
        m_tDStreamPort = htons(wDStreamPort);
    }

    void GetDStreamAddr(u32 &dwDStreamIp, u16 &wDStreamPort)
    {
        dwDStreamIp = ntohl(m_tDStreamIp);
        wDStreamPort = ntohs(m_tDStreamPort);
    }
}
#ifndef WIN32
__attribute__((packed))
#endif
;

//¼����ŵ�״̬
struct TRecChnnlStatus
{
	/*ͨ����״̬*/
	enum ERecChnnlState
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
	enum ERecChnnlType
	{
		TYPE_UNUSE      =  0,	/*δʼ�õ�ͨ��*/
		TYPE_RECORD     =  1,	/*¼��ͨ��  */   
		TYPE_PLAY       =  2	/*����ͨ��  */
	};

	//¼��ʽ
	enum ERecMode
	{
		MODE_SKIPFRAME = 0,//��֡¼��
		MODE_REALTIME  = 1  //ʵʱ¼��
	};
public:
	u8  		m_byType;		//ͨ�����ͣ�ERecChnnlType
	u8  		m_byState;		//ͨ��״̬��ERecChnnlState
	u8          m_byRecMode;    //¼��ʽ:
	TRecProg	m_tProg;	//��ǰ¼���������
protected:
	char	m_achRecordName[MAXLEN_RECORD_NAME];//��¼��
	
public:
	//��ȡ��¼��
	LPCSTR GetRecordName( void ) const	{ return m_achRecordName; }
	//���ü�¼��
	void SetRecordName( LPCSTR lpszName ) 
	{
		strncpy( m_achRecordName, lpszName, sizeof( m_achRecordName ) );
		m_achRecordName[sizeof( m_achRecordName ) - 1] ='\0';
	}
	
	LPCSTR GetStatusStr( u8 eStatus )
	{
		switch(eStatus) 
		{
		case STATE_IDLE:
			return "IDLE";
			break;
		case STATE_RECREADY:
			return "REC Ready";
			break;
		case STATE_RECORDING:
			return "Recording";
			break;
		case STATE_RECPAUSE:
			return "REC Pause";
			break;
		case STATE_PLAYREADY:
			return "PLAY Ready";
			break;
		case STATE_PLAYING:
			return "Playing";
			break;
		case STATE_PLAYPAUSE:
			return "Play Pause";
			break;
		case STATE_FF:
			return "Play FF";
			break;
		case STATE_FB:
			return "Play FB";
		default:
			return "UNKOWN";
		}
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//¼���״̬, size = 2412
struct TRecStatus
{
protected:
	u8  	m_byRecChnnlNum;		//¼���ŵ�������
	u8  	m_byPlayChnnlNum;		//�����ŵ�������
	u8      m_bSupportPublic;       // �Ƿ�֧�ַ���(TRUE: ֧��, FALSE:��֧��)
	u8      m_byRemain;             // ����
 	u32   	m_dwFreeSpace;        //¼���ʣ����̿ռ�(��λΪMB)
	u32   	m_dwTotalSpace;		//¼����ܴ��̿ռ�(��λΪMB)
	TRecChnnlStatus m_tChnnlStatus[MAXNUM_RECORDER_CHNNL];	//��¼���ŵ�������ŵ�

public:
	//��ȡ¼��ͨ������
	u8   GetRecChnnlNum( void ) const	{ return( m_byRecChnnlNum ); }
	//��ȡ����ͨ������
	u8   GetPlayChnnlNum( void ) const	{ return( m_byPlayChnnlNum ); }
	//����ͨ������¼��ͷ���ͨ���������벻����MAXNUM_RECORDER_CHNNL
	//ʧ�ܷ���FALSE
	BOOL SetChnnlNum( u8   byRecChnnlNum, u8   byPlayChnnlNum )
	{
		if( byRecChnnlNum + byPlayChnnlNum <= MAXNUM_RECORDER_CHNNL )
		{
			m_byRecChnnlNum = byRecChnnlNum;
			m_byPlayChnnlNum = byPlayChnnlNum;
			return( TRUE );
		}
		else
		{
			OspPrintf( TRUE, FALSE, "TRecStatus: Exception - Wrong recorder and play channel number: %u and %u!\n", 
				byRecChnnlNum, byPlayChnnlNum );
			return( FALSE );
		}
	}
		/*====================================================================
    ����        ������¼���ʣ����̿ռ�
    �������˵����u32    dwFreeSpace  - ʣ��ռ��С(��λ Mb)
    ����ֵ˵��  ����
	====================================================================*/
	void SetFreeSpaceSize( u32    dwFreeSpace )
	{
		m_dwFreeSpace  = htonl(dwFreeSpace);
	}
	
	/*====================================================================
    ����        ����ȡ¼���ʣ����̿ռ�
    �������˵������
    ����ֵ˵��  ��ʣ��ռ��С(��λ MB)
	====================================================================*/
	u32    GetFreeSpaceSize( void ) const	{ return ntohl( m_dwFreeSpace ); }

		/*====================================================================
    ����        ������¼����ܴ��̿ռ�
    �������˵����u32    dwTotalSpace  - �ܿռ��С(��λ MB)
    ����ֵ˵��  ����
	====================================================================*/
	void SetTotalSpaceSize( u32    dwTotalSpace )
	{
		m_dwTotalSpace  = htonl( dwTotalSpace );
	}
	// �Ƿ�֧�ַ���
	BOOL IsSupportPublic() const { return m_bSupportPublic;}
    // �����Ƿ�֧�ַ���
	void SetPublicAttribute(BOOL bSupportPublic ) { m_bSupportPublic = bSupportPublic;}

	/*====================================================================
    ����        ����ȡ¼����ܴ��̿ռ�
    �������˵������
    ����ֵ˵��  ���ܿռ��С(��λ MB)
	====================================================================*/
	u32    GetTotalSpaceSize( void ) const	{ return ntohl( m_dwTotalSpace ); }

	//����¼����ŵ�״̬��Ϣ������������¼�����ŵ����ٵ��ô˺���
	BOOL SetChnnlStatus( u8   byChnnlIndex, u8   byChnnlType, const TRecChnnlStatus * ptStatus );
	//����¼����ŵ�״̬��Ϣ������������¼�����ŵ����ٵ��ô˺���
	BOOL GetChnnlStatus( u8   byChnnlIndex, u8   byChnnlType, TRecChnnlStatus * ptStatus ) const;
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// �����Ӧ�Ƚ�С�������������
#define RECLIST_PACKSIZE    (u8)16
struct TRecFileListNotify
{
	u16 wListSize;//¼������ļ�����
	u16 wStartIdx;//��֪ͨ����ʼ�ļ����
	u16 wEndIdx;  //��֪ͨ�н����ļ����
    
	s8 achFileName[RECLIST_PACKSIZE][MAXLEN_CONFNAME+MAXLEN_RECORD_NAME+1];
	u8 abyStatus[RECLIST_PACKSIZE];
public:
	TRecFileListNotify()
	{
		wListSize = 0;
		wStartIdx = 0;
		wEndIdx   = 0;
		memset ( achFileName ,0,sizeof(achFileName) );
		memset( abyStatus ,0 ,sizeof(abyStatus) );
	}

	//��ȡ¼�����¼����
	u16 GetListSize()
	{
		return ntohs(wListSize);
	}
	
	//��ȡ��֪ͨ����ʼ�ļ����
	u16 GetStartIdx()
	{
		return ntohs(wStartIdx);
	}

	//��ȡ��֪ͨ����ʼ�ļ����
	u16 GetEndIdx()
	{
		return ntohs(wEndIdx);
	}

	//���ָ����ŵ��ļ���,�粻���ڷ���NULL
	char* GetFileName(u16 wIdx )
	{
		if( wIdx < GetStartIdx() || wIdx > GetEndIdx() )
			return NULL;
		return achFileName[wIdx - GetStartIdx()];
	}

	//�ж�ָ����ŵ��ļ��Ƿ񷢲�
	BOOL IsPublic(u16 wIdx)
	{
		if( wIdx < GetStartIdx() || wIdx > GetEndIdx() )
			return FALSE;
		return abyStatus[wIdx - GetStartIdx()]&0x1 ? TRUE:FALSE;
	}

	//����ָ����ŵ��ļ�����
	BOOL Public(u16 wIdx)
	{
		if( wIdx < GetStartIdx() || wIdx > GetEndIdx() )
			return FALSE;

		abyStatus[wIdx - GetStartIdx()] |=0x1;
		return TRUE;
	}

	/////////////////////////////////////////////
	//����¼�����¼����
	void Reset()
	{
		wListSize = 0;
	    wStartIdx =0;
	    wEndIdx =0;
	    memset( achFileName,0,sizeof(achFileName) );
		memset( abyStatus , 0,sizeof(abyStatus) );
	}
	void SetListSize( u16 wSize)
	{
		wListSize = htons(wSize);
	}
	
	//���ñ�֪ͨ����ʼ�ļ����
	void SetStartIdx( u16 wIdx)
	{
		wStartIdx = htons(wIdx);
	}

	//���ñ�֪ͨ����ʼ�ļ����
	void SetEndIdx( u16 wIdx)
	{
		wEndIdx = htons(wIdx);
	}

	// ����ļ�
	BOOL AddFile(char* filename ,BOOL bPublic = FALSE )
	{
		if ( IsFull() )
			return FALSE;

        u16 wIdx = GetEndIdx() - GetStartIdx();

		strncpy( achFileName[wIdx], filename ,sizeof(achFileName[wIdx]) - 1);
		achFileName[wIdx][sizeof(achFileName)-1]='\0';

		if ( bPublic ) 
        {
            abyStatus[wIdx] |=0x1;
        }
		else 
        {
            abyStatus[wIdx] &=~0x01;
        }

        // ����Զ�����
        SetEndIdx( GetEndIdx() + 1 );
		return TRUE;
	}

	//�жϻ����Ƿ�����
	BOOL32 IsFull()
	{
		u16 wSize = GetEndIdx() - GetStartIdx();
		if( wSize >= RECLIST_PACKSIZE )
			return TRUE;
		return FALSE;
	}

    BOOL32 IsEmpty()
    {
        return (GetEndIdx() == GetStartIdx());
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TPlayFileAttrib
{
protected:
    u8 m_byFileType;
    u8 m_byAudioType;
    u8 m_byVideoType;
    u8 m_byDVideoType;

public:
    TPlayFileAttrib(void)
    {
        m_byFileType = RECFILE_NORMAL;
        m_byAudioType = MEDIA_TYPE_NULL;
        m_byVideoType = MEDIA_TYPE_NULL;
        m_byDVideoType = MEDIA_TYPE_NULL;
    }

    BOOL32 IsDStreamFile(void) const
    {
        return (RECFILE_DSTREAM == m_byFileType) ? TRUE : FALSE;
    }
    u8 GetFileType(void) const
    {
        return m_byFileType;
    }
    void SetFileType(u8 byFileType)
    {
        m_byFileType = byFileType;
    }

    u8 GetAudioType(void) const
    {
        return m_byAudioType;
    }
    void SetAudioType(u8 byAudioType)
    {
        m_byAudioType = byAudioType;
    }

    u8 GetVideoType(void) const
    {
        return m_byVideoType;
    }
    void SetVideoType(u8 byVideoType)
    {
        m_byVideoType = byVideoType;
    }

    u8 GetDVideoType(void) const
    {
        return m_byDVideoType;
    }
    void SetDVideoType(u8 byDVideoType)
    {
        m_byDVideoType = byDVideoType;
    }
    
    void Print() const
    {
        OspPrintf(TRUE, FALSE, "m_byFileType: %d\n", m_byFileType);
        OspPrintf(TRUE, FALSE, "m_byAudioType: %d\n", m_byAudioType);
        OspPrintf(TRUE, FALSE, "m_byVideoType: %d\n", m_byVideoType);
        OspPrintf(TRUE, FALSE, "m_byDVideoType: %d\n", m_byDVideoType);
    }
}
#ifndef WIN32
__attribute__ ((packed))
#endif
;

// zgc, 2008-08-02, MCU�ķ����ļ�ý����Ϣ
struct TPlayFileMediaInfo
{
    enum emStreamType
    {
        emAudio = 0,
        emVideo,
        emDVideo,
        emEnd
    };

private:
    //���ĸ���
    u8 m_byNum;
    //��������
    u8 m_abyMediaType[emEnd];
    u16	m_awWidth[emEnd];
	u16 m_awHeight[emEnd];

public:
    void clear( void )
    {
        m_byNum = 0;
        for ( u8 byLop = 0; byLop < emEnd; byLop++ )
        {
            m_abyMediaType[byLop] = MEDIA_TYPE_NULL;
            m_awWidth[byLop] = 0;
            m_awHeight[byLop] = 0;
        }
    }
    void SetStreamNum( u8 byNum ) { m_byNum = byNum; }
    u8   GetStreamNum( void ) const { return m_byNum; }
    void SetAudio( u8 byAudioType ) { m_abyMediaType[emAudio] = byAudioType; }
    u8   GetAudio( void ) const { return m_abyMediaType[emAudio]; }
    void SetVideo( u8 byVideoType, u16 wWidth, u16 wHeight ) 
    { 
        m_abyMediaType[emVideo] = byVideoType; 
        m_awWidth[emVideo] = htons(wWidth);
        m_awHeight[emVideo] = htons(wHeight);
        return;
    }
    void GetVideo( u8 &byVideoType, u16 &wWidth, u16 &wHeight ) const 
    { 
        byVideoType = m_abyMediaType[emVideo]; 
        wWidth = ntohs(m_awWidth[emVideo]);
        wHeight = ntohs(m_awHeight[emVideo]);
        return;
    }
    void SetDVideo( u8 byDVideoType, u16 wWidth, u16 wHeight ) 
    { 
        m_abyMediaType[emDVideo] = byDVideoType; 
        m_awWidth[emDVideo] = htons(wWidth);
        m_awHeight[emDVideo] = htons(wHeight);
        return;
    }
    void GetDVideo( u8 &byDVideoType, u16 &wWidth, u16 &wHeight ) const 
    { 
        byDVideoType = m_abyMediaType[emDVideo]; 
        wWidth = ntohs(m_awWidth[emDVideo]);
        wHeight = ntohs(m_awHeight[emDVideo]);
        return;
    }
}
#ifndef WIN32
__attribute__ ((packed))
#endif
;

struct TPlayEqpAttrib : public TPlayFileAttrib
{
protected:
    u8 m_byIsDStreamPlay;

public:
    TPlayEqpAttrib(void)
    {
        m_byIsDStreamPlay = 0;
    }

    void Reset()
    {
        m_byFileType = RECFILE_NORMAL;
        m_byAudioType = MEDIA_TYPE_NULL;
        m_byVideoType = MEDIA_TYPE_NULL;
        m_byDVideoType = MEDIA_TYPE_NULL;
        m_byIsDStreamPlay = 0;
    }

    BOOL32 IsDStreamPlay(void) const
    {
        return (m_byIsDStreamPlay == 1) ? TRUE : FALSE;
    }
    void SetDStreamPlay(u8 byIsDStreamPlay)
    {
        m_byIsDStreamPlay = byIsDStreamPlay;
    }

    void Print() const
    {
        TPlayFileAttrib::Print();
        OspPrintf(TRUE, FALSE, "m_byIsDStreamPlay: %d\n", m_byIsDStreamPlay);
    }    
}
#ifndef WIN32
__attribute__ ((packed))
#endif
;

/*----------------------------------------------------------------------
�ṹ����CConfVidTypeMgr
��;  �������������͹���
˵��  �����ն���Ŀǰ�������ն˺�¼���
----------------------------------------------------------------------*/
/*
class CConfVidTypeMgr
{  
public:
    enum emMediaType
    {        
        emH264_1080 = 0,
        emH264_720,
        emH264_4CIF,
        emH264_CIF,
        emOther, // ����Ƶ��ʽ/˫��ͬ����Ƶ��ʽ

		emH239H264_UXGA,
        emH239H264_SXGA,
        emH239H264_XGA,
        emH239H264_SVGA,
        emH239H264_VGA,
        emDVidOther // ˫����ʽ
    };
    
public:
    u8 m_abyMediaType[emOther+1];
    u8 m_abyDualMediaType[emDVidOther+1];     // ˫��������H264�����ʽ��Other��������
    
public:
    CConfVidTypeMgr () 
    { 
        memset( m_abyMediaType, 0, sizeof(m_abyMediaType) ); 
        memset( m_abyDualMediaType, 0, sizeof(m_abyDualMediaType) );
    }

    void ConvertIn2Out( u8 emType, u8 &byOutType, u8 &byOutRes )
    {
        emMediaType emIntype = (emMediaType)emType;
        if ( emIntype == emOther ||
             emIntype == emDVidOther )
        {
            byOutType = MEDIA_TYPE_NULL;
            byOutRes = 0;
            return;
        }
        else
        {
            byOutType = MEDIA_TYPE_H264;
        }

        switch( emIntype )
        {
        case emH264_1080:
            byOutRes = VIDEO_FORMAT_HD1080;
            break;
        case emH264_720:
            byOutRes = VIDEO_FORMAT_HD720;
            break;
        case emH264_4CIF:
            byOutRes = VIDEO_FORMAT_4CIF;
            break;
        case emH264_CIF:
            byOutRes = VIDEO_FORMAT_CIF;
            break;
        case emH239H264_VGA:
            byOutRes = VIDEO_FORMAT_VGA;
            break;
        case emH239H264_SVGA:
            byOutRes = VIDEO_FORMAT_SVGA;
            break;
        case emH239H264_XGA:
            byOutRes = VIDEO_FORMAT_XGA;
            break;
        case emH239H264_SXGA:
            byOutRes = VIDEO_FORMAT_SXGA;
            break;
		case emH239H264_UXGA:
			byOutRes = VIDEO_FORMAT_UXGA;
			break;
        default:
            byOutType = MEDIA_TYPE_NULL;
            byOutRes = 0;
            break;
        }
        return;
    }
    
    u8 ConvertOut2In( u8 byOutType, u8 byOutRes, BOOL32 bDVid = FALSE )
    {
        emMediaType emIntype;
        switch( byOutType )
        {
        case MEDIA_TYPE_H264:
            {
                switch( byOutRes )
                {
                case VIDEO_FORMAT_CIF:
                    emIntype = emH264_CIF;
                    break;
                case VIDEO_FORMAT_4CIF:
                    emIntype = emH264_4CIF;
                    break;
                case VIDEO_FORMAT_HD720:
                    emIntype = emH264_720;
                    break;
                case VIDEO_FORMAT_HD1080:
                    emIntype = emH264_1080;
                    break;
                case VIDEO_FORMAT_VGA:
                    emIntype = emH239H264_VGA;
                    break;
                case VIDEO_FORMAT_SVGA:
                    emIntype = emH239H264_SVGA;
                    break;
                case VIDEO_FORMAT_XGA:
                    emIntype = emH239H264_XGA;
                    break;
                case VIDEO_FORMAT_SXGA:
                    emIntype = emH239H264_SXGA;
                    break;
				case VIDEO_FORMAT_UXGA:
					emIntype = emH239H264_UXGA;
					break;
                default:
                    emIntype = bDVid ? emDVidOther : emOther;
                    break;
                }
            }
            break;
        default:
            emIntype = bDVid ? emDVidOther : emOther;
            break;
        }
        return (u8)emIntype;
    }
    
    BOOL32 IsTypeExist( u8 emType, BOOL32 bDVid = FALSE )
    {
        if ( !bDVid )
        {
            if ( !IsVGAType(emType) )
            {
                return ( m_abyMediaType[(emMediaType)emType] > 0 );
            }
            else
            {
                return FALSE;
            }
        }
        else
        {
            return ( m_abyDualMediaType[(emMediaType)emType] > 0 );
        }
    }

    void AddType( u8 emType, BOOL32 bDVid = FALSE )
    {
        if ( !bDVid )
        {
            if ( !IsVGAType(emType) )
            {
                m_abyMediaType[(emMediaType)emType]++;
            }
        }
        else
        {
            m_abyDualMediaType[(emMediaType)emType]++;
        }
        return;
    }

    void DelType( u8 emType, BOOL32 bDVid = FALSE )
    {
        if ( IsTypeExist(emType, bDVid) )
        {
            if ( !bDVid )
            {
                m_abyMediaType[(emMediaType)emType]--;
            }
            else
            {
                m_abyDualMediaType[(emMediaType)emType]--;
            }
        }
        return;
    }
    
    u8 GetTypeNum(BOOL32 bDVid = FALSE)
    {
        u8 byNum = 0;
        if ( !bDVid )
        {          
            for( u8 byLop = 0; byLop < sizeof(m_abyMediaType); byLop++ )
            {
                if ( m_abyMediaType[(emMediaType)byLop] > 0 )
                {
                    byNum++;
                }
            }
        }
        else
        {
            for( u8 byLop = 0; byLop < sizeof(m_abyDualMediaType); byLop++ )
            {
                if ( m_abyDualMediaType[(emMediaType)byLop] > 0 )
                {
                    byNum++;
                }
            }
        }
        return byNum;
    }
    
    u8 GetH264TypeNum(BOOL32 bDVid = FALSE)
    {
        u8 byNum = 0;
        if ( !bDVid )
        {          
            for( u8 byLop = 0; byLop < sizeof(m_abyMediaType); byLop++ )
            {
                if ( m_abyMediaType[(emMediaType)byLop] > 0 && (emMediaType)byLop != emOther )
                {
                    byNum++;
                }
            }
        }
        else
        {
            for( u8 byLop = 0; byLop < sizeof(m_abyDualMediaType); byLop++ )
            {
                if ( m_abyDualMediaType[(emMediaType)byLop] > 0 &&
                     (emMediaType)byLop != emOther &&
                     (emMediaType)byLop != emDVidOther )
                {
                    byNum++;
                }
            }
        }
        return byNum;
    }

    u8 GetAdaptTypeNum( u8 bySrcOutType, u8 bySrcOutRes, BOOL32 bDVid = FALSE )
    {
        u8 emType = ConvertOut2In( bySrcOutType, bySrcOutRes, bDVid );
        u8 byRecvTypeNum = GetAdaptTypeNum( emType, bDVid );
        return byRecvTypeNum;
    }

    u8 GetAdaptTypeNum( u8 emSrcType, BOOL32 bDVid = FALSE )
    {
        u8 byRecvTypeNum = 0;
        if ( !bDVid )
        {
            for ( u8 byLop = (emMediaType)emSrcType+1; byLop < sizeof(m_abyMediaType); byLop++ )
            {
                if ( IsTypeExist(byLop, bDVid) )
                {
                    byRecvTypeNum++;
                }
            }
        }
        else
        {
            for ( u8 byLop = (emMediaType)emSrcType+1; byLop < sizeof(m_abyDualMediaType); byLop++ )
            {
                if ( IsTypeExist(byLop, bDVid) &&
                     // ����Ŀ��Ӧ�ú�Դ��˫��������ͬ
                     IsVGAType(emSrcType) == IsVGAType(byLop) &&
                     byLop != emOther && byLop != emDVidOther )
                {
                    byRecvTypeNum++;
                }
                if ( IsVGAType(emSrcType) != IsVGAType(byLop) )
                {
                    break;
                }
            }
        }
        return byRecvTypeNum;
    }

    BOOL32 IsVGAType( u8 emType )
    {
        emMediaType emInType = (emMediaType)emType;
        return ( emInType <= emOther ) ? FALSE : TRUE;
    }

    u8  GetMinH264AdaptType( u8 emSrcType, BOOL32 bDVid = FALSE )
    {
        emMediaType emIntype = (emMediaType)emSrcType;
        emMediaType emMinType = emIntype;
        if ( !bDVid )
        {
            for ( u8 byLop = emIntype+1; byLop < emOther; byLop++ )
            {
                if ( IsTypeExist(byLop, bDVid) )
                {
                    emMinType = (emMediaType)byLop;
                }
            }
        }
        else
        {
            for ( u8 byLop = emIntype+1; byLop < emDVidOther; byLop++ )
            {
                if ( IsTypeExist(byLop, bDVid) && byLop != emOther )
                {
                    emMinType = (emMediaType)byLop;
                }
            }
        }

        return (u8)emMinType;
    }
	void Print( void )
	{
		u8 byType = 0;

		OspPrintf( TRUE, FALSE, "�����������Ⱥ��Ϊ��\n" );
		for(byType = emH264_1080; byType <= emOther; byType ++)
		{
			if (m_abyMediaType[byType] != 0)
			{
				OspPrintf( TRUE, FALSE, "\tType.%d, num.%d\n", byType, m_abyMediaType[byType] );
			}
		}
		OspPrintf( TRUE, FALSE, "\n" );

		OspPrintf( TRUE, FALSE, "˫���������Ⱥ��Ϊ��\n" );
		for(byType = emH239H264_UXGA; byType <= emDVidOther; byType ++)
		{
			if (m_abyDualMediaType[byType] != 0)
			{
				OspPrintf( TRUE, FALSE, "\tType.%d, num.%d\n", byType, m_abyDualMediaType[byType] );
			}
		}
		OspPrintf( TRUE, FALSE, "\n" );
	}
}
#ifndef WIN32
__attribute__ ((packed))
#endif
;*/

//modify bas 2
//���������������ṹ
struct TAdaptParam
{
    enum EVideoType
    {
        vNONE  = MEDIA_TYPE_NULL,//��Ƶ����������
        vMPEG4 = MEDIA_TYPE_MP4,
        vH261  = MEDIA_TYPE_H261,
        vH263  = MEDIA_TYPE_H263,
        vH264  = MEDIA_TYPE_H264,
    };
    enum EAudioType
    {
        aNONE  = MEDIA_TYPE_NULL,//��Ƶ����������
        aMP3   = MEDIA_TYPE_MP3,
        aPCMA  = MEDIA_TYPE_PCMA,
        aPCMU  = MEDIA_TYPE_PCMU,
        aG7231 = MEDIA_TYPE_G7231,
        aG728  = MEDIA_TYPE_G728,
        aG729  = MEDIA_TYPE_G729,
    };

public:
    u16  GetWidth(void) const	{ return (ntohs(m_wWidth)); };
    u16  GetHeight(void) const	{ return (ntohs(m_wHeight)); };
    u16  GetBitrate(void) const { return (ntohs(m_wBitRate));};

    void SetResolution(u16 wWidth, u16 wHeight)
    {
        m_wWidth = htons(wWidth);
        m_wHeight = htons(wHeight);
    }
	
	void SetBitRate(u16 wBitrate)
	{
	    m_wBitRate = htons(wBitrate);
	}
	
	void SetVidType(u8 eType)
	{
		m_byVidCodeType = (u8)eType;
	}
	u8 GetVidType(void){ return m_byVidCodeType ;}
	
	void SetAudType(u8 eType)
	{
		m_byAudCodeType = (u8)eType;
	}
	u8 GetAudType(void){ return m_byAudCodeType; }

	void SetVidActiveType(u8 eType)
	{
		m_byVidActiveType = (u8)eType;
	}
	u8 GetVidActiveType(void){ return m_byVidActiveType; }
	
	void SetAudActiveType(u8 eType)
	{
		m_byAudActiveType = (u8)eType;
	}
	u8 GetAudActiveType(void){ return m_byAudActiveType; }

	void SetIsNeedByPrs(BOOL32 bNeedPrs)
	{
		m_byNeedPrs = (TRUE == bNeedPrs) ? 1 : 0;
	}

	BOOL32 IsNeedbyPrs(void)
	{
		return (0 != m_byNeedPrs);
	}

    BOOL32 IsNull(void) const
    {
        return (MEDIA_TYPE_NULL == m_byAudCodeType || 0 == m_byAudCodeType ) &&
               (MEDIA_TYPE_NULL == m_byVidCodeType || 0 == m_byVidCodeType );
    }
    void Clear(void)
    {
        m_byAudCodeType = MEDIA_TYPE_NULL;
        m_byVidCodeType = MEDIA_TYPE_NULL;
        m_byAudActiveType = MEDIA_TYPE_NULL;
        m_byVidActiveType = MEDIA_TYPE_NULL;
        m_wBitRate = 0;
        m_wWidth = 0;
        m_wHeight = 0;
        m_byNeedPrs = 0;
    }
    void Print(void) const
    {
        OspPrintf(TRUE, FALSE, "TAdpParam:\n");
        OspPrintf(TRUE, FALSE, "\tm_byAudCodeType:\t%d\n", m_byAudCodeType);
        OspPrintf(TRUE, FALSE, "\tm_byVidCodeType:\t%d\n", m_byVidCodeType);
        OspPrintf(TRUE, FALSE, "\tm_byAudActiveType:\t%d\n", m_byAudActiveType);
        OspPrintf(TRUE, FALSE, "\tm_byVidActiveType:\t%d\n", m_byVidActiveType);

        OspPrintf(TRUE, FALSE, "\tm_wBitRate:\t\t%d\n", GetBitrate());
        OspPrintf(TRUE, FALSE, "\tm_wWidth:\t\t%d\n", GetWidth());
        OspPrintf(TRUE, FALSE, "\tm_wHeight:\t\t%d\n", GetHeight());
        OspPrintf(TRUE, FALSE, "\tm_byNeedPrs:\t\t%d\n", m_byNeedPrs);
    }

private:
    u8         m_byAudCodeType;  //������Ƶ�������
    u8         m_byVidCodeType;  //������Ƶ�������
    u8         m_byAudActiveType;//������Ƶ�����̬�غ�����
    u8         m_byVidActiveType;//������Ƶ�����̬�غ�����
    
    u16 	   m_wBitRate;//��������
    u16 	   m_wWidth; //ͼ����
    u16 	   m_wHeight;//ͼ����
    
    u8         m_byNeedPrs;
}
#ifndef WIN32
__attribute__ ((packed)) 
#endif
;

/*----------------------------------------------------------------------
�ṹ����THDAdaptParam
��;  ��HD�������
----------------------------------------------------------------------*/
struct THDAdaptParam : public TAdaptParam
{
public:
    u8 GetFrameRate( void ) { return m_byFrameRate; }
    void SetFrameRate(u8 byFrameRate) { m_byFrameRate = byFrameRate; }

    void Reset(void)
    {
        Clear();
        m_byFrameRate = 0;
        m_byReserve1 = 0;
        m_byReserve2 = 0;
        m_byReserve3 = 0;
    }
    void PrintHd(void) const
    {
        //this->Print();
        OspPrintf(TRUE, FALSE, "\tm_byFrameRate:\t\t%d\n", m_byFrameRate);
    }
private:
    u8 m_byFrameRate;
    u8 m_byReserve1;
    u8 m_byReserve2;
    u8 m_byReserve3;
}
#ifndef WIN32
__attribute__ ((packed)) 
#endif
;

/*----------------------------------------------------------------------
�ṹ����THDBasChnStatus
��;  ��HDBas����ͨ��
----------------------------------------------------------------------*/
struct THDBasChnStatus
{
    enum EBasStatus
    {
        IDLE   = 0, //����
        READY  = 1, //׼������
        RUNING = 2  //��������
    };

public:
    void   SetStatus( u8 byStatus ) { m_byStatus = byStatus; };
    u8     GetStatus( void ) { return m_byStatus; }
    
    BOOL32 IsNull( void ) const { return m_tBas.IsNull(); }
    void   SetNull( void ) { m_tBas.SetNull(); }
    
    u8     GetReservedType( void ) { return m_byIsReserved; }
    BOOL32 IsReserved ( void ) const { return ( 1 == m_byIsReserved ); }
    void   SetIsReserved ( BOOL32 bIsReserved ) { m_byIsReserved = bIsReserved ? 1 : 0; }
    BOOL32 IsTempReserved ( void ) const { return ( 2 == m_byIsReserved ); }
    void   SetIsTempReserved ( BOOL32 bIsTempReserved ) { m_byIsReserved = bIsTempReserved ? 2 : 0; } 
    void   UnReserved( void ) { m_byIsReserved = 0; }
    
    void   SetChnIdx( u8 byChnIdx ) { m_byChnIdx = byChnIdx; }
    u8     GetChnIdx( void ) const { return m_byChnIdx; }
    
    void   SetEqp( TEqp tBas ) { m_tBas = tBas; }
    TEqp   GetEqp( void ) const { return m_tBas; }
    u8     GetEqpId( void ) const { return m_tBas.GetEqpId(); }	
    void   SetType( u8 byType ) { m_byType = byType; };
    u8     GetType( void ) { return m_byType; }

    void   Print() const
    {
        OspPrintf(TRUE, FALSE, "TEqp:\n");
        OspPrintf(TRUE, FALSE, "\tMcuId:\t\t%d\n", m_tBas.GetMcuId());
        OspPrintf(TRUE, FALSE, "\tEqpId:\t\t%d\n", m_tBas.GetMtId());
        OspPrintf(TRUE, FALSE, "\tMainType:\t%d\n", m_tBas.GetType());
        OspPrintf(TRUE, FALSE, "\tSubType:\t%d\n", m_tBas.GetEqpType());
        OspPrintf(TRUE, FALSE, "\tConfIdx:\t%d\n", m_tBas.GetConfIdx());
        OspPrintf(TRUE, FALSE, "\tDriId:\t\t%d\n", m_tBas.GetDriId());

        OspPrintf(TRUE, FALSE, "Status:\n");
        OspPrintf(TRUE, FALSE, "\tStatus:\t\t%d\n", m_byStatus);
        OspPrintf(TRUE, FALSE, "\tReserved:\t%d\n", m_byIsReserved);
        OspPrintf(TRUE, FALSE, "\tChnIdx:\t\t%d\n", m_byChnIdx);
        OspPrintf(TRUE, FALSE, "\tType:\t\t%d\n", m_byType);
    }
private:
    TEqp m_tBas;
    u8 m_byStatus;	// EBasStatus
    u8 m_byIsReserved; // 0 -- not reserve, 1 -- reserve, 2 -- temply reserve
	u8 m_byChnIdx;
    u8 m_byType; // zw 20081114
}
#ifndef WIN32
__attribute__ ((packed)) 
#endif
;

/*----------------------------------------------------------------------
�ṹ����THDBasVidChnStatus
��;  ��HDBas��Ƶͨ����¼״̬
----------------------------------------------------------------------*/
struct THDBasVidChnStatus : public THDBasChnStatus //len:39
{
private:
	THDAdaptParam m_atOutputVidParam[MAXNUM_VOUTPUT];

public:	
    THDAdaptParam * GetOutputVidParam( u8 byChnIdx )
    {
        if ( byChnIdx < MAXNUM_VOUTPUT )
        {
            return &m_atOutputVidParam[byChnIdx]; 
        }
        else
        {
            return NULL;
        }
    }
    void SetOutputVidParam(THDAdaptParam &tVidParam, u8 byChnIdx )
    {
        if ( byChnIdx < MAXNUM_VOUTPUT )
        {
            m_atOutputVidParam[byChnIdx] = tVidParam;
        }
        return;
    }

	void ClrOutputVidParam()
	{
 		THDAdaptParam tNullAdpParam;
		tNullAdpParam.Reset();  
		for (u8 byChnlIdx = 0; byChnlIdx < MAXNUM_VOUTPUT; byChnlIdx++)
		{
			m_atOutputVidParam[byChnlIdx] = tNullAdpParam;
		}
	}
    void PrintInfo() const
    {
        OspPrintf(TRUE, FALSE, "\nHDBasVidChnStatus info as follows:\n\n");
        Print();
        for(u8 byIdx = 0; byIdx < MAXNUM_VOUTPUT; byIdx ++)
        {
            m_atOutputVidParam[byIdx].Print();
            m_atOutputVidParam[byIdx].PrintHd();
        }
    }
}
#ifndef WIN32
__attribute__ ((packed)) 
#endif
;

typedef THDBasVidChnStatus THDBasDVidChnStatus;

/*----------------------------------------------------------------------
�ṹ����TMauBasStatus
��;  ��MauBas״̬�࣬�ӽ�TPeriEqpStatus
----------------------------------------------------------------------*/
class TMauBasStatus
{
public:
    void SetVidChnStatus (THDBasVidChnStatus &tVidChnStatus, u8 byChnIdx = 0)
    {
        if ( byChnIdx < MAXNUM_MAU_VCHN )
        {
            m_atVidChnStatus[byChnIdx] = tVidChnStatus;
        }
        return;
    }
	void SetDVidChnStatus (THDBasDVidChnStatus &tDVidChnStatus, u8 byChnIdx = 0)
    {
        if ( byChnIdx < MAXNUM_MAU_DVCHN )
        {
            m_atDVidChnStatus[byChnIdx] = tDVidChnStatus;
        }
        return;
    }
	THDBasVidChnStatus * GetVidChnStatus(u8 byChnIdx = 0)
    {
        if ( byChnIdx < MAXNUM_MAU_VCHN )
        {
            return &m_atVidChnStatus[byChnIdx];
        }
        else
        {
            return NULL;
        }
    }
	THDBasDVidChnStatus * GetDVidChnStatus(u8 byChnIdx = 0)
    {
        if ( byChnIdx < MAXNUM_MAU_DVCHN )
        {
            return &m_atDVidChnStatus[byChnIdx];
        }
        else
        {
            return NULL;
        }
    }
    void Print() const
    {
        OspPrintf(TRUE, FALSE, "TMauBasStatus is as follows:\n");
        u8 byIdx = 0;
        for(byIdx = 0; byIdx < MAXNUM_MAU_VCHN; byIdx++)
        {
            m_atVidChnStatus[byIdx].PrintInfo();
        }
        for(byIdx = 0; byIdx < MAXNUM_MAU_DVCHN; byIdx++)
        {
            m_atDVidChnStatus[byIdx].PrintInfo();
        }
    }
private:
    THDBasVidChnStatus m_atVidChnStatus[MAXNUM_MAU_VCHN];	
    THDBasDVidChnStatus m_atDVidChnStatus[MAXNUM_MAU_DVCHN];
}
#ifndef WIN32
__attribute__ ((packed)) 
#endif
;

/*----------------------------------------------------------------------
�ṹ����TMpuBasStatus
��;  ��MpuBas״̬�࣬�ӽ�TPeriEqpStatus
----------------------------------------------------------------------*/
class TMpuBasStatus
{
public:
    void SetVidChnStatus (THDBasVidChnStatus &tVidChnStatus, u8 byChnIdx)
    {
        if ( byChnIdx < MAXNUM_MPU_CHN )
        {
            m_atVidChnStatus[byChnIdx] = tVidChnStatus;
        }
        return;
    }
	THDBasVidChnStatus * GetVidChnStatus(u8 byChnIdx)
    {
        if ( byChnIdx < MAXNUM_MPU_CHN )
        {
            return &m_atVidChnStatus[byChnIdx];
        }
        else
        {
            return NULL;
        }
    }
    void Print() const
    {
        OspPrintf(TRUE, FALSE, "TMpuBasStatus is as follows:\n");
        u8 byIdx = 0;
        for(byIdx = 0; byIdx < MAXNUM_MPU_VCHN; byIdx++)
        {
            m_atVidChnStatus[byIdx].PrintInfo();
        }
    }
private:
    THDBasVidChnStatus m_atVidChnStatus[MAXNUM_MPU_VCHN];
}
#ifndef WIN32
__attribute__ ((packed)) 
#endif
;


/*----------------------------------------------------------------------
�ṹ����TMpuBasStatus
��;  ��MpuBas״̬�࣬�ӽ�TPeriEqpStatus
----------------------------------------------------------------------*/
class THdBasStatus
{
public:
    union
    {
        TMauBasStatus tMauBas;
        TMpuBasStatus tMpuBas;
    }tStatus;

public:
    void SetEqpType(u8 byType)
    {
        if (byType != TYPE_MPU &&
            byType != TYPE_MAU_NORMAL &&
            byType != TYPE_MAU_H263PLUS)
        {
            OspPrintf(TRUE, FALSE, "[THdBasStatus][SetType] unexpected type.%d\n", m_byType);
            return;
        }
        m_byType = byType;
        return;
    }
    u8   GetEqpType(void) const { return m_byType; }

public:
    u8 m_byType;
}
#ifndef WIN32
__attribute__ ((packed)) 
#endif
;

//������ͨ��״̬�ṹ
struct TBasChnStatus : TAdaptParam
{
    enum EBasStatus
    {
        IDLE   = 0, //����
        READY  = 1, //׼������
        RUNING = 2  //��������
    };

protected:
    u8 m_byStatus;
	u8 m_byReserved;    //�Ƿ�Ϊ����ͨ��
    u8 m_byChanType;    //��Ƶͨ��: 1(BAS_CHAN_AUDIO)  ��Ƶͨ��: 2(BAS_CHAN_VIDEO)

public:

    void SetStatus(u8 byStatus)
    {
        m_byStatus = byStatus;
    }

    u8 GetStatus(void)
    {
        return m_byStatus;
    }

    void SetReserved(BOOL32 bReserved)
    {
        m_byReserved = (TRUE == bReserved) ? 1 : 0;
    }

    BOOL32 IsReserved(void)
    {
        return (0 != m_byReserved);
    }

    u8 GetChannelType(void)
    {
        return m_byChanType;
    }

    void SetChannelType(u8 byBasChanType)
    {
        m_byChanType = byBasChanType;
    }
}
#ifndef WIN32
__attribute__ ((packed))
#endif
;

//������������ģ��
struct TBasCapSet
{
public:
    u8 m_bySupportAudio;
    u8 m_bySupportVideo;
    u8 m_bySupportBitrate;

public:
    void SetAudioCapSet(BOOL32 bSupportAudio)
    {
        if (TRUE == bSupportAudio)
        {
            m_bySupportAudio = 1;
        }
        else
        {
            m_bySupportAudio = 0;
        }
    }

    BOOL32 IsSupportAudio(void)
    {
        if (0 == m_bySupportAudio)
        {
            return FALSE;
        }
        return TRUE;
    }

    void SetVideoCapSet(BOOL32 bSupportVideo)
    {
        if (TRUE == bSupportVideo)
        {
            m_bySupportVideo = 1;
        }
        else
        {
            m_bySupportVideo = 0;
        }
    }

    BOOL32 IsSupportVideo(void)
    {
        if (0 == m_bySupportVideo)
        {
            return FALSE;
        }
        return TRUE;
    }

    void SetBitrateCapSet(BOOL32 bSupportBitrate)
    {
        if (TRUE == bSupportBitrate)
        {
            m_bySupportBitrate = 1;
        }
        else
        {
            m_bySupportBitrate = 0;
        }
    }

    BOOL32 IsSupportBitrate(void)
    {
        if (0 == m_bySupportBitrate)
        {
            return FALSE;
        }
        return TRUE;
    }
}
#ifndef WIN32
__attribute__((packed))
#endif
;

//������ͨ��״̬�ṹ
struct TBasStatus
{
	u8            byChnNum;
    TBasCapSet    tBasCapSet;
    TBasChnStatus tChnnl[MAXNUM_BAS_CHNNL];
}
#ifndef WIN32
__attribute__((packed))
#endif
;


//����DCS״̬�ṹ
struct TPeriDcsStatus : public TEqp
{
public:
	u8	m_byOnline;			//�Ƿ�����
protected:
	s8	m_achDcsAlias[MAXLEN_EQP_ALIAS];
public:
	TPeriDcsStatus()
	{
		memset( this, 0, sizeof(TPeriDcsStatus) );
	}

	//��ȡDCS����
	const s8 * GetDcsAlias() const
	{
		return m_achDcsAlias;
	}
	//�����������
	void SetDcsAlias( const s8 * lpszAlias )
	{
		strncpy( m_achDcsAlias, lpszAlias, sizeof(m_achDcsAlias) );
		m_achDcsAlias[MAXLEN_EQP_ALIAS - 1] = '\0';
	}
	//�ÿ�
	void SetNull()
	{
		memset( this, 0, sizeof(TPeriDcsStatus) );
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//��������״̬�ṹ, size = 2435(TRecStatus = 2412)
struct TPeriEqpStatus : public TEqp
{
public:
	u8  	m_byOnline;		//�Ƿ�����
	union UStatus
	{
		TTvWallStatus	tTvWall;
		TMixerStatus	tMixer;
		TVmpStatus      tVmp;
		TRecStatus		tRecorder;
		TBasStatus		tBas;
		TPrsStatus		tPrs;
        THdBasStatus    tHdBas;
		THduStatus      tHdu;

	} m_tStatus;
	
protected:
	char    m_achAlias[MAXLEN_EQP_ALIAS];
public:
	//constructor
	TPeriEqpStatus( void )
	{
		memset(this, 0, sizeof(TPeriEqpStatus));
	}

	//��ȡ�������
	const s8 * GetAlias() const 
	{ 
		return m_achAlias;
	}

	//�����������
	void SetAlias(const s8 * lpszAlias)
	{ 
		strncpy(m_achAlias, lpszAlias, sizeof(m_achAlias));
		m_achAlias[MAXLEN_EQP_ALIAS-1] = '\0';
	}

}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//����Ҫ���ӵ��ն���Ϣ
struct TAddMtInfo: public TMtAlias
{
	u8   m_byCallMode;
	u16  m_wDialBitRate;//��������//��λKbps
public:
	u16  GetCallBitRate() { return ntohs(m_wDialBitRate); }
	void SetCallBitRate(u16 wDialBitRate) { m_wDialBitRate = htons(wDialBitRate); }

    u8   GetCallMode() { return m_byCallMode; }
    void SetCallMode(u8 byCallMode) { m_byCallMode = byCallMode; }

}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//���԰棬�����ն�ʱmcsָ������������Ϣ
struct TAddMtCapInfo
{
private:
	TVideoStreamCap  m_tMainVideoCap;
	TVideoStreamCap  m_tDStreamVideoCap;
public:
	TAddMtCapInfo()	{ clear(); }
	void clear()
	{
		m_tMainVideoCap.Clear();
		m_tDStreamVideoCap.Clear();		
	}
	const TVideoStreamCap& GetMainVideoCap() const    { return m_tMainVideoCap; }
	void SetMainVideoCap(TVideoStreamCap& tVideoSteamCap) 
	{
		memcpy( &m_tMainVideoCap, &tVideoSteamCap, sizeof(TVideoStreamCap) );
	}

	const TVideoStreamCap& GetDStreamVideoCap() const { return m_tDStreamVideoCap; }
	void SetDStreamVideoCap(TVideoStreamCap& tVideoSteamCap) 
	{
		memcpy( &m_tDStreamVideoCap, &tVideoSteamCap, sizeof(TVideoStreamCap) );
	}
	
	// ����Ƶ����
    void	SetMainMaxBitRate(u16 wMaxRate)  {  m_tMainVideoCap.SetMaxBitRate(wMaxRate); }	
    u16		GetMainMaxBitRate() const { return m_tMainVideoCap.GetMaxBitRate(); }
	
    void	SetMainMediaType(u8 byMediaType)  {  m_tMainVideoCap.SetMediaType(byMediaType); }	
    u8		GetMainMediaType() const { return m_tMainVideoCap.GetMediaType(); }
    
    void    SetMainResolution(u8 byRes) {   m_tMainVideoCap.SetResolution(byRes);    }
    u8      GetMainResolution(void) const   {   return m_tMainVideoCap.GetResolution();    }

    void    SetMainFrameRate(u8 byFrameRate)
    {
        if ( MEDIA_TYPE_H264 == m_tMainVideoCap.GetMediaType() )
        {
            OspPrintf( TRUE, FALSE, "Function has been preciated, try SetUserDefFrameRate\n" );
            return;
        }
        m_tMainVideoCap.SetFrameRate(byFrameRate);
		return;
    }
    u8      GetMainFrameRate(void) const
    {
        if ( MEDIA_TYPE_H264 == m_tMainVideoCap.GetMediaType() )
        {
            OspPrintf( TRUE, FALSE, "Function has been preciated, try GetUserDefFrameRate\n" );
            return 0;
        }
        return m_tMainVideoCap.GetFrameRate();
    }

    // �Զ���֡��
    void    SetUserDefMainFrameRate(u8 byActFrameRate) { m_tMainVideoCap.SetUserDefFrameRate(byActFrameRate); }
    BOOL32  IsMainFrameRateUserDefined() const {return m_tMainVideoCap.IsFrameRateUserDefined(); }
    u8      GetUserDefMainFrameRate(void) const { return m_tMainVideoCap.GetUserDefFrameRate(); }

	// ˫������
    void	SetDstreamMaxBitRate(u16 wMaxRate)  {  m_tDStreamVideoCap.SetMaxBitRate(wMaxRate); }	
    u16		GetDstreamMaxBitRate() const { return m_tDStreamVideoCap.GetMaxBitRate(); }

    void	SetDstreamMediaType(u8 byMediaType)  {  m_tDStreamVideoCap.SetMediaType(byMediaType); }	
    u8		GetDstreamMediaType() const { return m_tDStreamVideoCap.GetMediaType(); }
    
    void    SetDstreamResolution(u8 byRes) {   m_tDStreamVideoCap.SetResolution(byRes);    }
    u8      GetDstreamResolution(void) const   {   return m_tDStreamVideoCap.GetResolution();    }

    void    SetDstreamFrameRate(u8 byFrameRate)
    {
        if ( MEDIA_TYPE_H264 == m_tDStreamVideoCap.GetMediaType() )
        {
            OspPrintf( TRUE, FALSE, "Function has been preciated, try SetUserDefFrameRate\n" );
            return;
        }
        m_tDStreamVideoCap.SetFrameRate(byFrameRate);
		return;
    }
    u8      GetDstreamFrameRate(void) const
    {
        if ( MEDIA_TYPE_H264 == m_tDStreamVideoCap.GetMediaType() )
        {
            OspPrintf( TRUE, FALSE, "Function has been preciated, try GetUserDefFrameRate\n" );
            return 0;
        }
        return m_tDStreamVideoCap.GetFrameRate();
    }

    // �Զ���֡��
    void    SetUserDefDstreamFrameRate(u8 byActFrameRate) { m_tDStreamVideoCap.SetUserDefFrameRate(byActFrameRate); }
    BOOL32  IsDstreamFrameRateUserDefined() const {return m_tDStreamVideoCap.IsFrameRateUserDefined(); }
    u8      GetUserDefDstreamFrameRate(void) const { return m_tDStreamVideoCap.GetUserDefFrameRate(); }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//���԰������ն˵���Ϣ������MCSָ���Ĳ����ն�������
struct TAddMtInfoEx: public TAddMtInfo
{
private:
	TAddMtCapInfo m_tMtCapInfo;

public:
	TAddMtInfoEx()	{ clear(); }
	void clear()
	{
		m_tMtCapInfo.clear();
	}

	const TAddMtCapInfo& GetMtCapInfo() const    { return m_tMtCapInfo; }
	void SetMtCapInfo(TAddMtCapInfo& tMtCapInfo) 
	{
		memcpy( &m_tMtCapInfo, &tMtCapInfo, sizeof(TAddMtCapInfo) );
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;



//��������ն˽ṹ���ýṹ�����˲μӻ����MCU�������ն��б������ն��б��ʵ��
//����ն��б������߱�����ǰ�ߵ��Ӽ� 
struct TConfMtInfo
{
protected:   
	u8      m_byMcuId;          //��MC���ڵ�Mcu��Id��
    u8      m_byConfIdx;        //���������� 
	u8  	m_abyMt[MAXNUM_CONF_MT/8];	        //�����ն��б�
	u8  	m_abyJoinedMt[MAXNUM_CONF_MT/8];	//����ն��б�

public:
    void  SetMcuId(u8   byMcuId){ m_byMcuId = byMcuId; } 
    u8    GetMcuId( void ) const { return m_byMcuId; }
    void  SetConfIdx(u8   byConfIdx){ m_byConfIdx = byConfIdx; } 
    u8    GetConfIdx( void ) const { return m_byConfIdx; }

	TConfMtInfo( void );//constructor
	BOOL MtInConf( u8 byMtId ) const;//�жϸ�MCU��ĳ�ն��Ƿ��������ն��б���
	BOOL MtJoinedConf( u8 byMtId ) const;//�жϸ�MCU��ĳ�ն��Ƿ�������ն��б���
	void AddMt( u8 byMtId );//���Ӹ�MCU���ն��ڻ����ն��б���
	void AddJoinedMt( u8 byMtId );//���Ӹ�MCU���ն�������ն��б��У��ú����Զ������ն�Ҳ
	void RemoveMt( u8 byMtId );//ɾ����MCU���ն��������ն��б��У��ú����Զ������ն�Ҳ
	void RemoveJoinedMt( u8 byMtId );//ɾ����MCU���ն�������ն��б���
	void RemoveAllMt( void );//ɾ����MCU�������ն��������ն��б��У��ú����Զ��������ն�Ҳ
	void RemoveAllJoinedMt( void );//ɾ����MCU�������ն�������ն��б���
	u8   GetAllMtNum( void ) const;//�õ�һ���ṹ�����������ն˸���
	u8   GetAllJoinedMtNum( void ) const;//�õ�һ���ṹ����������ն˸���
	u8   GetAllUnjoinedMtNum( void ) const;//�õ�һ���ṹ������δ����ն˸���
	u8	 GetMaxMtIdInConf( void ) const;	//�õ�һ���ṹ�������ն���MtId����ֵ// xliang [12/24/2008] 

	void SetNull( void )
	{
		m_byMcuId = 0;
		m_byConfIdx = 0;
	}
	BOOL IsNull( void ) const
	{
		if( m_byMcuId == 0 && m_byConfIdx == 0 )
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//���������ն���Ϣ (len:3256)
struct TConfAllMtInfo
{
public:
	TConfMtInfo	m_tLocalMtInfo;
	TConfMtInfo	m_atOtherMcMtInfo[MAXNUM_SUB_MCU];
	TMt         m_tMMCU; //�������ϼ�MCU 

public:
    TConfAllMtInfo( void ){ Clear(); }

	void Clear() { memset( this, 0, sizeof(TConfAllMtInfo) ); }

    void   SetLocalMtInfo(TConfMtInfo tLocalMtInfo){ m_tLocalMtInfo = tLocalMtInfo; } 
    TConfMtInfo  GetLocalMtInfo( void ) const { return m_tLocalMtInfo; }

	BOOL AddMt( u8  byMtId );//����������һ�������ն�  
	BOOL AddJoinedMt( u8  byMtId );//����������һ������նˣ��ú����Զ������ն�Ҳ
	void RemoveMt( u8  byMtId );//������ɾ��һ���ն� 
	void RemoveJoinedMt( u8  byMtId );//������ɾ��һ������ն�
	void RemoveAllMt( void );//������ɾ��һ��MCU�����������նˣ���ɾ��MCU�����ú���
	void RemoveAllJoinedMt( void );//������ɾ��һ��MCU����������նˣ���ɾ��MCU��
	BOOL MtInConf( u8  byMtId ) const;//�ж��ն��Ƿ��������ն��б���
	BOOL MtJoinedConf( u8  byMtId ) const;//�ж��ն��Ƿ�������ն��б���
	// xliang [9/9/2009] FIXME
	BOOL MtJoinedConf( TMt tMt) const;	//�ɷ�ӳ����mcu�µ�mt�Ƿ����
	u8   GetLocalMtNum( void ) const;//�õ��������������ն˸��� 
	u8   GetLocalJoinedMtNum( void ) const;//�õ�������������ն˸���
	u8   GetLocalUnjoinedMtNum( void ) const;//�õ���������δ����ն˸���

    void   SetMtInfo(TConfMtInfo tConfMtInfo );
    TConfMtInfo  GetMtInfo( u8 byMcuId ) const;
	TConfMtInfo* GetMtInfoPtr( u8 byMcuId);

	BOOL MtInConf( u8  byMcuId, u8  byMtId ) const;//�ж��ն��Ƿ��������ն��б���
	BOOL MtJoinedConf( u8  byMcuId, u8  byMtId ) const;//�ж��ն��Ƿ�������ն��б���

	u16   GetAllMtNum( void ) const;//�õ����������ṹ�����������ն˸��� 
	u16   GetAllJoinedMtNum( void ) const;//�õ����������ṹ����������ն˸���
	u8	GetMaxMtIdInConf( void )const;// xliang [12/24/2008]

	u8	GetCascadeMcuNum( void) const;

	BOOL AddMcuInfo( u8 byMcuId, u8 m_byConfIdx );   //����������һ��mcu��Ϣ��������ʱû���ն�
	BOOL RemoveMcuInfo( u8 byMcuId, u8 m_byConfIdx );//�������Ƴ�һ��mcu��Ϣ��ͬʱ������������ն���Ϣ

}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;


//�������ǽ���ýṹ��ÿ���ṹ��ӳ��һ���ն˺Ż�MCU����ź���Ƶ����˿ںŵĶ�Ӧ��ϵ
struct TTVWallSetting
{
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//�����߼�ͨ���ṹ(len:47)
struct TLogicalChannel
{  
public:
	u8  m_byMediaType;      //ý�����ͣ�MODE_VIDEO��MODE_AUDIO
	u8  m_byChannelType;    //�ŵ����ͣ�AUDIO_G711A��VIDEO_H261��
	u8  m_byVideoFormat;    //��Ƶ�ŵ��ķֱ���
	u8  m_byH239DStream;    //�ŵ������Ƿ���H239�غ�
	u16 m_wFlowControl;     //�ŵ�����(��λ:Kbps,1K=1024)
    u16 m_wCurrFlowControl; //��ǰ�ŵ�����ֵ
	TTransportAddr m_tRcvMediaChannel;     //���ն�ý���ŵ�
	TTransportAddr m_tRcvMediaCtrlChannel; //���ն�ý������ŵ�
	TTransportAddr m_tSndMediaCtrlChannel; //���Ͷ�ý������ŵ�

	TMediaEncrypt  m_tMediaEncrypt;   //������Ϣ
	u8             m_byActivePayload; //��̬�غ�
	u8			   m_byFECType;		  //MCUǰ���������, zgc, 2007-10-10
    u8             m_byVidFPS;        //��ͨ��������֡�� MODE_VIDEO��
public:
	TLogicalChannel(void)
	{ 
		Clear();
	}
    void Clear(void)
    {
        memset( this, 0, sizeof(TLogicalChannel));
		m_tMediaEncrypt.Reset();
		m_byChannelType = MEDIA_TYPE_NULL;
        m_wCurrFlowControl = 0xFFFF;
    }
    void SetMediaType(u8 byMediaType){ m_byMediaType = byMediaType;} 
    u8   GetMediaType( void ) const { return m_byMediaType; }
    void SetChannelType(u8 byChannelType){ m_byChannelType = byChannelType;} 
    u8   GetChannelType( void ) const { return m_byChannelType; }
    void SetSupportH239(BOOL32 bH239DStream){ m_byH239DStream = (bH239DStream ? 1:0);} 
    BOOL32   IsSupportH239( void ) const { return (m_byH239DStream == 0 ? FALSE : TRUE); }
    void SetVideoFormat(u8 byVideoFormat){ m_byVideoFormat = byVideoFormat;} 
    u8   GetVideoFormat( void ) const { return m_byVideoFormat; }
    void SetFlowControl(u16  wFlowControl){ m_wFlowControl = htons(wFlowControl);} 
    u16  GetFlowControl( void ) const { return ntohs(m_wFlowControl); }
    void SetCurrFlowControl(u16  wFlowControl){ m_wCurrFlowControl = htons(wFlowControl);} 
    u16  GetCurrFlowControl( void ) const { return ntohs(m_wCurrFlowControl); }
    void SetRcvMediaChannel(TTransportAddr tRcvMediaChannel){ m_tRcvMediaChannel = tRcvMediaChannel;} 
    TTransportAddr  GetRcvMediaChannel( void ) const { return m_tRcvMediaChannel; }
    void SetRcvMediaCtrlChannel(TTransportAddr tRcvMediaCtrlChannel){ m_tRcvMediaCtrlChannel = tRcvMediaCtrlChannel;} 
    TTransportAddr  GetRcvMediaCtrlChannel( void ) const { return m_tRcvMediaCtrlChannel; }
    void SetSndMediaCtrlChannel(TTransportAddr tSndMediaCtrlChannel){ m_tSndMediaCtrlChannel = tSndMediaCtrlChannel;} 
    TTransportAddr  GetSndMediaCtrlChannel( void ) const { return m_tSndMediaCtrlChannel; }
    BOOL IsOpened( void ) const { return m_byMediaType == 0 ? FALSE : TRUE; }

	void SetMediaEncrypt(TMediaEncrypt& tMediaEncrypt)
	{
		m_tMediaEncrypt = tMediaEncrypt;
	}
	TMediaEncrypt &GetMediaEncrypt()
	{
		return m_tMediaEncrypt;
	}

	void SetActivePayload(u8 byActivePayload)
	{
		m_byActivePayload = byActivePayload;
	}
	u8 GetActivePayload()
	{
		return m_byActivePayload;
	}

	void SetFECType( u8 byFECType ) { m_byFECType = byFECType; }
	u8	 GetFECType( void ) const { return m_byFECType; }
    void SetChanVidFPS( u8 byFPS ) { m_byVidFPS = byFPS;    }
    u8   GetChanVidFPS( void ) const { return m_byVidFPS;    }

}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//H239˫������ӵ���ն���Ϣ (len:15)
typedef struct tagH239TokenInfo
{
    s32  m_nChannelId;   
    
    u8   m_bySymmetryBreaking;
	BOOL m_bIsResponseAck;

	//H239˫������ӵ���ն�
	TMt  m_tH239TokenMt;   
    
    tagH239TokenInfo()
    {
        Clear();
    }

    void Clear()
    {
        m_nChannelId         = 0;
        m_bySymmetryBreaking = 0;
		m_bIsResponseAck     = FALSE;
        m_tH239TokenMt.SetNull();
    }

    void SetSymmetryBreaking(u8 bySymmetryBreaking)
    {
        m_bySymmetryBreaking = bySymmetryBreaking;
    }
    u8 GetSymmetryBreaking()
    {
        return m_bySymmetryBreaking;
    }

	void SetResponseAck(BOOL bIsResponseAck)
    {
        m_bIsResponseAck = bIsResponseAck;
    }
    BOOL IsResponseAck()
    {
        return m_bIsResponseAck;
    }

    void SetChannelId(s32 nChannelId)
    {
        m_nChannelId = nChannelId;
    }   
    s32 GetChannelId()
    {
        return m_nChannelId;
    }

	void SetTokenMt(TMt tH239TokenMt)
    {
        m_tH239TokenMt = tH239TokenMt;
    }   
    TMt GetTokenMt()
    {
        return m_tH239TokenMt;
    }
    
}TH239TokenInfo,*PTH239TokenInfo;
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif


//���彻���ṹ
struct TSwitchInfo
{
protected:
	TMt	  m_tDstMt;		  //����Ŀ���ն�
	TMt   m_tSrcMt;		  //����Դ�ն�
	u8    m_byMode;		  //����ģʽ��MODE_VIDEO, MODE_AUDIO, MODE_BOTH
	u8    m_byDstChlIdx;  //Ŀ��ͨ������
	u8    m_bySrcChlIdx;  //Դͨ��������
public:
    void  SetDstMt(TMt tDstMt){ m_tDstMt = tDstMt;} 
    TMt   GetDstMt( void ) const { return m_tDstMt; }
    void  SetSrcMt(TMt tSrcMt){ m_tSrcMt = tSrcMt;} 
    TMt   GetSrcMt( void ) const { return m_tSrcMt; }
    void  SetMode(u8   byMode){ m_byMode = byMode;} 
    u8    GetMode( void ) const { return m_byMode; }
    void  SetDstChlIdx(u8   byDstChlIdx){ m_byDstChlIdx = byDstChlIdx;} 
    u8    GetDstChlIdx( void ) const { return m_byDstChlIdx; }
    void  SetSrcChlIdx(u8   bySrcChlIdx){ m_bySrcChlIdx = bySrcChlIdx;} 
    u8    GetSrcChlIdx( void ) const { return m_bySrcChlIdx; }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//�������ǽ�����ṹ
struct TTWSwitchInfo : public TSwitchInfo
{
protected:
	u8    m_bySrcMtType;  //����ǽԴͨ����Ա����,�μ�mcuconst.h�е���ǽ��Ա���Ͷ���
	u8    m_bySchemeIdx;  // Ԥ��������
	u8    m_byReserved[3];
public:
    TTWSwitchInfo()
	{
		memset( this, 0x0, sizeof(TTWSwitchInfo) );
	}

	void  SetMemberType(u8   bySrcMtType ){ m_bySrcMtType = bySrcMtType; } 
    u8    GetMemberType( void ) const { return m_bySrcMtType; }

	void  SetSchemeIdx(u8   bySchemeIdx ){ m_bySchemeIdx = bySchemeIdx; } 
    u8    GetSchemeIdx( void ) const { return m_bySchemeIdx; }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//����HDU�����ṹ
typedef TTWSwitchInfo THduSwitchInfo;   //4.6.1 �¼�  jlb

//����hdu�����ṹ��  ��Χ 0 -- 31
struct THduVolumeInfo:public TEqp
{
protected:
	u8  m_byChnlIdx;    // ͨ��������
	u8  m_byVolume;     // ������С
	u8  m_byIsMute;  // �Ƿ���  
	u8  m_byReserved[5];

public:
    THduVolumeInfo()
	{
        memset(this, 0x0, sizeof(THduVolumeInfo));
		m_byVolume = HDU_VOLUME_DEFAULT;
	}

	u8   GetChnlIdx( void ){ return m_byChnlIdx; }
	void SetChnlIdx( u8 byChnlIdx ){ m_byChnlIdx = byChnlIdx; }

	u8   GetVolume( void ){ return m_byVolume; }
	void SetVolume( u8 byVolume ){ m_byVolume = byVolume; }

	BOOL32   GetIsMute( void ){ return m_byIsMute; }
	void SetIsMute( BOOL32 byIsMute ){ m_byIsMute = GETBBYTE(byIsMute); }

}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//������󲻶Գƽṹ
struct TMaxSkew
{
	u8    byChan1;	//�ŵ�1��MODE_VIDEO, MODE_AUDIO
	u8    byChan2;	//�ŵ�2��MODE_VIDEO, MODE_AUDIO
protected:
	u16 	wMaxSkew;	//��󲻶Գ�ֵ���ŵ�2���ŵ�1���ӳٴ���������λ��ms��

public:
	u16  GetMaxSkew( void ) const;//�õ���󲻶Գ�ֵ
	void SetMaxSkew( u16  wNewMaxSkew );//������󲻶Գ�ֵ
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//����ע��������Ϣ��
struct TPeriEqpRegReq : public TEqp
{
protected:
	u32   		m_dwIpAddr;		//����IP��ַ
	u16 		m_wStartPort;	//������ʼ���ն˿�
	u8  		m_byChannlNum;	//��������ŵ���
	s8          m_achAlias[MAXLEN_EQP_ALIAS];
    //4.0R3��չ�ֶ�
    u16         m_wVersion;     //�汾��Ϣ
    //4.5������չ�ֶ�
    BOOL        m_bHDEqp;       //�Ƿ��������

public:
    TPeriEqpRegReq(void) { memset(this, 0, sizeof(TPeriEqpRegReq)); }
    //��������IP��ַ
    //���룺IP��ַ(������)
	void SetPeriEqpIpAddr( const u32    &dwIpAddr )	{ m_dwIpAddr = dwIpAddr; }
    //�������IP��ַ
    //����ֵ��IP��ַ(������)
	u32    GetPeriEqpIpAddr() const	{ return m_dwIpAddr; }
	//�������������ʼ�˿�
	void SetStartPort( const u16  & wStartPort )	{ m_wStartPort = htons(wStartPort); }
	//������������ʼ�˿�
	u16  GetStartPort() const	{ return ntohs( m_wStartPort ); }
	//������������ŵ���Ŀ
	void SetChnnlNum( const u8   & byChannlNum )	{ m_byChannlNum = byChannlNum; }
	//�����������ŵ���Ŀ
	u8   GetChnnlNum() const	{ return m_byChannlNum; }

	void SetEqpAlias(char* szAlias)
	{
		strncpy( m_achAlias ,szAlias ,sizeof(m_achAlias) );
		m_achAlias[MAXLEN_EQP_ALIAS-1] ='\0';
	}

	LPCSTR GetEqpAlias()
	{
		return m_achAlias;
	}

    void SetVersion(u16 wVersion)
    {
        m_wVersion = htons(wVersion);
    }
    u16 GetVersion() const
    {
        return ntohs(m_wVersion);
    }
    void SetHDEqp(BOOL bHD)
    {
        m_bHDEqp = bHD;
    }

    BOOL IsHDEqp() const
    {
        return m_bHDEqp;
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//��������Ǽǳɹ���Ϣ�ṹ
struct TPeriEqpRegAck
{
protected:
	u32   		m_dwIpAddr;			//MCU���յ�ַ
	u16 		m_wStartPort;		//MCU������ʼ�˿ں�
    u32         m_dwAnotherMpcIp;   //����ʱ������һ��mpc���ַ���������������õı���mpc��ַ����У�飩
	u32         m_dwMsSSrc;         //����ʱ�����ڱ�עһ��ϵͳ���У�ֻҪ��ֵ�仯��˵������������ͬʱ����

public:
	//�õ��ϼ�MCU������������IP��ַ
    u32    GetMcuIpAddr( void ) const { return ntohl(m_dwIpAddr); }

	//�����ϼ�MCU������������IP��ַ
    void SetMcuIpAddr( u32    dwIpAddr ) { m_dwIpAddr = htonl(dwIpAddr); }

	//�õ��ϼ�MCU�����������ݶ˿ں�
    u16  GetMcuStartPort( void ) const { return ntohs(m_wStartPort); }

    //�����ϼ�MCU�����������ݶ˿ں�
    void SetMcuStartPort( u16  wPort ) { m_wStartPort = htons(wPort); }

    //����һ��mpc���ַ
    u32  GetAnotherMpcIp( void ) const { return ntohl(m_dwAnotherMpcIp); }
    void SetAnotherMpcIp( u32 dwIpAddr ) { m_dwAnotherMpcIp = htonl(dwIpAddr); }

	void SetMSSsrc(u32 dwSSrc)
    {
        m_dwMsSSrc = htonl(dwSSrc);
    }
    u32 GetMSSsrc(void) const
    {
        return ntohl(m_dwMsSSrc);
    }

}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//�������̨ע����Ϣ(len:77)
struct TMcsRegInfo
{
public:
	u32   		m_dwMcsIpAddr;	      //�������̨��Ip��ַ��������
	u8  		m_byVideoChnNum;	  //ͨ����Ŀ
	u16 		m_wStartPort;		  //��Ƶͨ������ʼ�˿ںţ�������
	s8          m_achUser[MAXLEN_PWD];//�û���
	s8          m_achPwd[MAXLEN_PWD]; //�û�����
	u32   		m_dwMcsSSRC;	      //�������̨���������ֵ����������
	                                  //Ӧ����ͬһmcs����ͬһmcu������mpc����ͬһֵ��
	                                  //      ��ͬmcs����ͬһmcu���ò�ֵͬ
    u16         m_wMcuMcsVer;         //mcu��mcs�Ự�汾
public:
	TMcsRegInfo( void )
    { 
        memset( this, 0, sizeof(TMcsRegInfo) );
        SetMcuMcsVer();
    }
    void  SetMcsIpAddr(u32 dwMcsIpAddr){ m_dwMcsIpAddr = htonl(dwMcsIpAddr);}
    u32   GetMcsIpAddr( void ) const { return ntohl(m_dwMcsIpAddr); }
    void  SetVideoChnNum(u8 byVideoChnNum){ m_byVideoChnNum = byVideoChnNum;}
    u8    GetVideoChnNum( void ) const { return m_byVideoChnNum; }
    void  SetStartPort(u16 wStartPort){ m_wStartPort = htons(wStartPort);}
    u16   GetStartPort( void ) const { return ntohs(m_wStartPort); }
    void  SetMcsSSRC(u32 dwMcsSSRC){ m_dwMcsSSRC = htonl(dwMcsSSRC);} 
    u32   GetMcsSSRC( void ) const { return ntohl(m_dwMcsSSRC); }
    void  SetMcuMcsVer(void) { m_wMcuMcsVer = htons(MCUMCS_VER); }
    u16   GetMcuMcsVer(void) const { return ntohs(m_wMcuMcsVer); }
    void  SetUser( LPCSTR lpszUser )
	{
		memset(m_achUser, 0, sizeof(m_achUser));
		if (NULL != lpszUser)
		{
			strncpy(m_achUser, lpszUser, sizeof(m_achUser));
			m_achUser[sizeof(m_achUser)-1] = '\0';
		}
	}
	LPCSTR GetUser( void ) const{ return m_achUser; }
	BOOL IsEqualUser( LPCSTR lpszUser ) const
	{
		s8 achBuf[MAXLEN_PWD+1] = {0};
		strncpy( achBuf, lpszUser, sizeof( achBuf ) );
		achBuf[sizeof(achBuf)-1] = '\0';
		
		if(0 == strncmp(achBuf, lpszUser, MAXLEN_PWD))
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	void SetPwd( LPCSTR lpszPwd )
	{
		memset(m_achPwd, 0, sizeof(m_achPwd));
		if (NULL != lpszPwd)
		{
			strncpy(m_achPwd, lpszPwd, sizeof(m_achPwd));
			m_achPwd[sizeof(m_achPwd)-1] = '\0';
            // guzh [10/11/2007] �򵥼��ܡ���GetPwd֮ǰҪ�ֶ�����
            EncPwd();
		}
	}

	LPCSTR GetPwd( void ) const{ return m_achPwd; }
    
    // guzh [10/11/2007] 
    /*
	BOOL IsEqualPwd( LPCSTR lpszPwd ) const
	{
		s8 achBuf[MAXLEN_PWD+1] = {0};
		strncpy( achBuf, lpszPwd, sizeof( achBuf ) );
		achBuf[sizeof(achBuf)-1] = '\0';
		
		if(0 == strncmp(achBuf, lpszPwd, MAXLEN_PWD))
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
    */
	
	BOOL operator ==( TMcsRegInfo &tObj ) const
	{
		if (tObj.m_dwMcsIpAddr == m_dwMcsIpAddr && 
			tObj.m_dwMcsSSRC == m_dwMcsSSRC && 
			tObj.m_byVideoChnNum == m_byVideoChnNum && 
			IsEqualUser(tObj.m_achUser) && 
			/*IsEqualPwd(tObj.m_achPwd)&&*/ 
            tObj.m_wMcuMcsVer == m_wMcuMcsVer)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
        
    void DecPwd()
    {
        EncPwd();
    }
private:
    void EncPwd()
    {
        for (u8 byLoop=0; byLoop<strlen(m_achPwd); byLoop++)
        {
            m_achPwd[byLoop] ^= 0xa7;
        }
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//�������̨ע���Ӧ(len:157)
struct TMcsRegRsp
{
protected:
    TMcu                m_tMcu;             // MCU �ṹ
    TMtAlias            m_tMcuAlias;        // MCU ����
    u32                 m_dwRemoteMpcIp;    // ����ʱ�Զ˵�IP
    u8                  m_byLocalActive;    // ��ǰ��MPC�Ƿ�Ϊ���ð�
    u8                  m_byUsrGrpId;       // ��½�û�����ID
    u8                  m_byMcuOsType;      // MCU�Ĳ���ϵͳ����
	u32					m_dwSysSSrc;		// ������ʶ
public:
    void   SetMcu(u8 byMcuType, u8 byMcuId)
    {
        m_tMcu.SetMcu(byMcuId);
        m_tMcu.SetMcuType(byMcuType);
    }
    TMcu   GetMcu() const
    {
        return m_tMcu;
    }
    void   SetMcuAlias(const TMtAlias &tAlias)
    {
        m_tMcuAlias = tAlias;
    }
    TMtAlias GetMcuAlias() const
    {
        return m_tMcuAlias;
    }
    void   SetRemoteMpcIp(u32 dwIp)
    {
        m_dwRemoteMpcIp = htonl(dwIp);
    }
    u32    GetRemoteMpcIp() const
    {
        return ntohl(m_dwRemoteMpcIp);
    }
    void   SetLocalActive(BOOL32 bActive)
    {
        m_byLocalActive = GETBBYTE(bActive);
    }
    BOOL32 IsLocalActive() const
    {
        return ISTRUE(m_byLocalActive);
    }
    void   SetUsrGrpId(u8 byGrpId)
    {
        m_byUsrGrpId = byGrpId;
    }
    u8     GetUsrGrpId() const
    {
        return m_byUsrGrpId;
    }
    void   SetMcuOsType(u8 byOsType)
    {
        m_byMcuOsType = byOsType;
    }
    u8     GetMcuOsType() const
    {
        return m_byMcuOsType;
    }
	void   SetSysSSrc(u32 dwSysSSrc)
	{
		m_dwSysSSrc = htonl(dwSysSSrc);
	}
	u32    GetSysSSrc() const
	{
		return ntohl(m_dwSysSSrc);
	}

    void Print() const
    {
        OspPrintf(TRUE, FALSE, "Mcu: (%d, %d)\n", m_tMcu.GetMcuId(), m_tMcu.GetMcuType());
        OspPrintf(TRUE, FALSE, "Alias: %s, 0x%x\n", m_tMcuAlias.m_achAlias, m_tMcuAlias.m_tTransportAddr.GetIpAddr());
        OspPrintf(TRUE, FALSE, "Remote MpcIP: 0x%x\n", GetRemoteMpcIp());
        OspPrintf(TRUE, FALSE, "Local Active: %d\n", IsLocalActive());
        OspPrintf(TRUE, FALSE, "User Group Id: %d\n", GetUsrGrpId());
        OspPrintf(TRUE, FALSE, "OS Type: %d\n", GetMcuOsType());
		OspPrintf(TRUE, FALSE, "Local SSRC: %d\n", GetSysSSrc());
    }
    
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//�������Ϣ
struct TConfNameInfo
{
	CConfId		m_cConfId;          //�����
	char		achConfName[MAXLEN_CONFNAME];   //������
public:
	TConfNameInfo( void )
	{
		m_cConfId.SetNull();
		memset( achConfName, 0, sizeof( achConfName ) );
	};
	void   SetConfName( LPCSTR lpszConfName )
	{
		if( lpszConfName != NULL )
		{
			strncpy( achConfName, lpszConfName, MAXLEN_CONFNAME );
		    achConfName[MAXLEN_CONFNAME - 1] = '\0';
		}
		else
		{
			memset(achConfName,0,sizeof(achConfName));
		}
	}
	LPCSTR GetConfName( void ) const { return achConfName; }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;



//���彻��ͨ���ṹ SrcIp->DisIp->RcvIp->DstIp, size=34
struct TSwitchChannel
{
    TSwitchChannel()
    {
        memset(this, 0, sizeof(TSwitchChannel));
    }
protected:
	TMt  m_tSrcMt;         //����Դ�ն�
	u32  m_dwSrcIp;        //����ԴIp��ַ
	u32  m_dwDisIp;        //���ݷַ�Ip��ַ
	u32  m_dwRcvIP;        //���ؽ��յ�IP��ַ(������),�������鲥(��㲥)��ַ
	u16  m_wRcvPort;       //���ؽ��յĶ˿� (������)
	u32  m_dwRcvBindIP;    //���ؽ���bind IP��ַ(������),���ص�ַ
	u32  m_dwDstIP;        //��Ҫ���͵�Ŀ��IP��ַ(������),�������鲥(��㲥)��ַ
	u16  m_wDstPort;       //��Ҫ���͵�Ŀ��˿� (������)
	u32  m_dwSndBindIP;    //����Ŀ��ӿ�IP��ַ.(������),���ص�ַ

public:
	void SetSrcMt( TMt tMt ){ m_tSrcMt = tMt; }
	TMt  GetSrcMt( void ){ return m_tSrcMt; }
    void SetSrcIp(u32    dwSrcIp){ m_dwSrcIp = htonl(dwSrcIp);} 
    u32  GetSrcIp( void ) const { return ntohl(m_dwSrcIp); }
    void SetDisIp(u32    dwDisIp){ m_dwDisIp = htonl(dwDisIp);} 
    u32  GetDisIp( void ) const { return ntohl(m_dwDisIp); }
    void SetRcvIP(u32    dwRcvIP){ m_dwRcvIP = htonl(dwRcvIP);} 
    u32  GetRcvIP( void ) const { return ntohl(m_dwRcvIP); }
    void SetRcvPort(u16  wRcvPort){ m_wRcvPort = htons(wRcvPort);} 
    u16  GetRcvPort( void ) const { return ntohs(m_wRcvPort); }
    void SetRcvBindIP(u32    dwRcvBindIP){ m_dwRcvBindIP = htonl(dwRcvBindIP);} 
    u32  GetRcvBindIP( void ) const { return ntohl(m_dwRcvBindIP); }
    void SetDstIP(u32    dwDstIP){ m_dwDstIP = htonl(dwDstIP);} 
    u32  GetDstIP( void ) const { return ntohl(m_dwDstIP); }
    void SetDstPort(u16  wDstPort){ m_wDstPort = htons(wDstPort);} 
    u16  GetDstPort( void ) const { return ntohs(m_wDstPort); }
    void SetSndBindIP(u32    dwSndBindIP){ m_dwSndBindIP = htonl(dwSndBindIP);} 
    u32  GetSndBindIP( void ) const { return ntohl(m_dwSndBindIP); }
	BOOL IsNull( void ) const { return m_dwDstIP == 0 ? TRUE : FALSE; }
    BOOL IsSrcNull( void ) const { return m_dwSrcIp == 0 ? TRUE : FALSE; }
    BOOL IsRcvNull( void ) const { return m_dwRcvIP == 0 ? TRUE : FALSE; }
	void SetNull( ){ memset( this, 0, sizeof(TSwitchChannel) ); }
	BOOL operator ==( TSwitchChannel &tObj ) const
	{
		if( tObj.GetDstIP() == GetDstIP() && tObj.GetDstPort() == GetDstPort() )
		{
			return TRUE;
		}
        else
		{
			return FALSE;
		}
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//Mp��Ϣ
struct TMp
{
protected:
    u8   m_byMcuId;                   //MCU��
    u8   m_byMpId;                    //��Mp���
    u8   m_byAttachMode;              //MP�ĸ�����ʽ
    u32  m_dwIpAddr;                  //Ip��ַ
    u8   m_byDoubleLink;              //˫��
    u8   m_byIsMulticast;             //�Ƿ��鲥 0: ���鲥 1���鲥
    s8   m_abyMpAlias[MAXLEN_ALIAS];  //Mp����	
	//4.0R4��չ�ֶ�
    u16  m_wVersion;			     //�汾��Ϣ	ZGC	2007-10-10
public:
    void SetMcuId(u8 byMcuId) { m_byMcuId = byMcuId; }
    u8   GetMcuId(void) const { return m_byMcuId; }
    void SetMpId(u8 byMpId){ m_byMpId = byMpId; }
    u8   GetMpId(void) const { return m_byMpId; }
    void SetAttachMode(u8 byAttachMode) { m_byAttachMode = byAttachMode; }
    u8   GetAttachMode(void) const { return m_byAttachMode; }
    void SetIpAddr(u32 dwIP){ m_dwIpAddr = htonl(dwIP); }
    u32  GetIpAddr(void) { return ntohl(m_dwIpAddr); }
    void SetDoubleLink(u8 byDoubleLink) { m_byDoubleLink = byDoubleLink; }
    u8   GetDoubleLink(void) const { return m_byDoubleLink; }
    void SetMulticast(u8 byIsMulticast) { m_byIsMulticast = byIsMulticast; }
    u8   GetMulticast(void) const { return m_byIsMulticast; }
    const s8 * GetAlias(void) const { return m_abyMpAlias; }
    void SetAlias(s8 * pchAlias)
    {
        if (pchAlias != NULL)
        {
            strncpy(m_abyMpAlias, pchAlias, sizeof(m_abyMpAlias));
            m_abyMpAlias[sizeof(m_abyMpAlias) - 1] = '\0';
        }
        else
        {
            memset(m_abyMpAlias, 0, sizeof(m_abyMpAlias));
        }
    }
	u16 GetVersion(void) const { return ntohs(m_wVersion); }
	void SetVersion(u16 wVersion) { m_wVersion = htons(wVersion); }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//MtAdpע����Ϣ
struct TMtAdpReg
{
protected:    
	u8      m_byDriId;         //��MtAdp���
	u8      m_byAttachMode;    //MtAdp�ĸ�����ʽ
	u8      m_byProtocolType;  //�����Э������//H323��H320��SIP
	u8      m_byMaxMtNum;      //�����֧������ն���
	u32     m_dwIpAddr;        //Ip��ַ��������
	s8      m_achMtAdpAlias[MAXLEN_ALIAS];  //MtAdp����
    u16     m_wQ931Port;
    u16     m_wRasPort;
	//4.0R4��չ�ֶ�
    u16     m_wVersion;     //�汾��Ϣ	ZGC	2007-09-28
    //4.0R5
    u8      m_byIsSupportHD;  //�Ƿ�֧�ָ������

public:
	TMtAdpReg()
	{
		memset(this, 0, sizeof(TMtAdpReg)); 
		m_byProtocolType = PROTOCOL_TYPE_H323;
		m_byMaxMtNum = MAXNUM_DRI_MT;
	}
	
	VOID	SetDriId(u8 byDriId){ m_byDriId = byDriId;}
	u8  	GetDriId() const { return m_byDriId;}
	VOID	SetAttachMode(u8 byAttachMode){ m_byAttachMode = byAttachMode;} 
	u8  	GetAttachMode( void ) const { return m_byAttachMode; }
	VOID	SetIpAddr(u32 dwIp){m_dwIpAddr = htonl(dwIp);}
	u32   	GetIpAddr() const { return ntohl(m_dwIpAddr);}
	VOID	SetProtocolType(u8 byProtocolType){ m_byProtocolType = byProtocolType;}
	u8  	GetProtocolType() const { return m_byProtocolType;}
	VOID	SetMaxMtNum(u8 byMaxMtNum){ m_byMaxMtNum = byMaxMtNum;}
	u8  	GetMaxMtNum() const { return m_byMaxMtNum;}
    void    SetQ931Port(u16 wQ931Port){ m_wQ931Port = htons(wQ931Port);} 
    u16     GetQ931Port( void ) const { return ntohs(m_wQ931Port); }
    void    SetRasPort(u16 wRasPort){ m_wRasPort = htons(wRasPort);} 
    u16     GetRasPort( void ) const { return ntohs(m_wRasPort); }	

	VOID SetAlias(LPCSTR lpszAlias)
	{
		if(lpszAlias != NULL)
			strncpy(m_achMtAdpAlias, lpszAlias, MAXLEN_ALIAS - 1);
	}

	VOID GetAlias(s8 *pchBuf, u16  wBufLen)
	{
		if(pchBuf != NULL)
			strncpy(pchBuf, m_achMtAdpAlias, wBufLen);
	}

	u16 GetVersion(void) const { return ntohs(m_wVersion); }
	void SetVersion(u16 wVersion) { m_wVersion = htons(wVersion); }

    void SetSupportHD(BOOL bSupport = TRUE)
    {
        m_byIsSupportHD = bSupport ? 1 : 0;
    }

    BOOL IsSupportHD() const
    {
        return ISTRUE(m_byIsSupportHD);
    }

}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//MtAdpע����Ӧ��Ϣ(len:148)
struct TMtAdpRegRsp 
{
protected:
	u32  m_dwVcIpAddr;                      //ҵ��IP��ַ��������
	u32  m_dwGkIpAddr;                      //GK IP��ַ��������
	s8   m_achMcuAlias[MAXLEN_ALIAS];       //MCU����
	u8   m_byMcuNetId;
	u16  m_wHeartBeatInterval;              //����ն˶���ʱ����(sec)
	u8   m_byHeartBeatFailTimes;            //�ն˶�������
	u8	 m_byMtAdpMaster;					//�Ƿ�Ϊ������ 1:��, 0:����
//	u16  m_wQ931Port;
//	u16  m_wRasPort;
	u16  m_wH225H245Port;                   //H225H245 �Ľ�����ʼ�˿�
	u16  m_wH225H245MtNum;                  //H225H245 �Ľ����ն���
    u8   m_byGkCharge;                      //�Ƿ����GK�Ʒ�
	u8	 m_byMcuType;						//Mcu����, zgc, 2007-04-03
    u8   m_byCascadeAliasType;              //����ʱMCU�ڻ����б�������ʾ��ʽ
    u8   m_byUseCallingMatch;               //������ѭƥ��Լ��

	u32  m_dwMsSSrc;                        //����ʱ�����ڱ�עһ��ϵͳ���У�ֻҪ��ֵ�仯��˵������������ͬʱ����
    s8   m_achMcuVersion[MAXLEN_ALIAS];     //MCU �汾�ţ����ڳ�ʼ��Э��ջ

public:
	TMtAdpRegRsp()
    {
        memset(this, 0, sizeof(TMtAdpRegRsp));
    }

	VOID	SetVcIp(u32    dwIp){m_dwVcIpAddr = htonl(dwIp);}
	u32   	GetVcIp() const {return ntohl(m_dwVcIpAddr);}

	VOID	SetGkIp(u32    dwIp){m_dwGkIpAddr = htonl(dwIp);}
	u32   	GetGkIp() const {return ntohl(m_dwGkIpAddr);}

	VOID	SetAlias(LPCSTR lpszAlias)
	{
		if(lpszAlias != NULL)
			strncpy(m_achMcuAlias, lpszAlias, MAXLEN_ALIAS - 1);
	}

	VOID	GetAlias(char *pchBuf, u16  wBufLen) const
	{
		if(pchBuf != NULL)
			strncpy(pchBuf, m_achMcuAlias, wBufLen);
	}

    // guzh [9/3/2007] MCU �汾�ţ����H323Config
    VOID	SetMcuVersion(LPCSTR lpszAlias)
    {
        if(lpszAlias != NULL)
            strncpy(m_achMcuVersion, lpszAlias, MAXLEN_ALIAS - 1);
    }
    
    LPCSTR	GetMcuVersion() const
    {
        return m_achMcuVersion;
	}
	
    void   SetMcuNetId(u8 byMcuId)	{ m_byMcuNetId = byMcuId; }	
    u8     GetMcuNetId() const	{ return m_byMcuNetId; }    
	
	void   SetHeartBeatInterval( u16 wHeartBeatInterval ){ m_wHeartBeatInterval = htons(wHeartBeatInterval); } 
	u16     GetHeartBeatInterval( void ) const { return ntohs(m_wHeartBeatInterval); }
	void   SetHeartBeatFailTimes(u8 byHeartBeatFailTimes){ m_byHeartBeatFailTimes = byHeartBeatFailTimes; } 
	u8     GetHeartBeatFailTimes( void ) const { return m_byHeartBeatFailTimes; }
//	void   SetQ931Port(u16 wQ931Port){ m_wQ931Port = htons(wQ931Port);} 
//	u16    GetQ931Port( void ) const { return ntohs(m_wQ931Port); }
//	void   SetRasPort(u16 wRasPort){ m_wRasPort = htons(wRasPort);} 
//	u16    GetRasPort( void ) const { return ntohs(m_wRasPort); }
	void   SetH225H245Port(u16 wH225H245Port){ m_wH225H245Port = htons(wH225H245Port);} 
	u16    GetH225H245Port( void ) const { return ntohs(m_wH225H245Port); }
	void   SetH225H245MtNum(u16 wH225H245MtNum){ m_wH225H245MtNum = htons(wH225H245MtNum);} 
	u16    GetH225H245MtNum( void ) const { return ntohs(m_wH225H245MtNum); }
    void   SetMtAdpMaster( BOOL32 bMtAdpMaster ){ m_byMtAdpMaster = (bMtAdpMaster ? 1:0);}
    BOOL32 IsMtAdpMaster() const { return (1 == m_byMtAdpMaster) ? TRUE:FALSE;}
    void   SetIsGKCharge(BOOL32 bCharge) { m_byGkCharge = bCharge ? 1 : 0;    }
    BOOL32 GetIsGKCharge( void ) { return m_byGkCharge == 1 ? TRUE : FALSE;   }
	
	//Mcu����, zgc, 2007-04-03
	void	SetMcuType( u8 byMcuType ) { m_byMcuType = byMcuType; }
	u8		GetMcuType( void ) { return m_byMcuType; }

    //MCU����������ʾ��ʽ
    void    SetCasAliasType(u8 byType) { m_byCascadeAliasType = byType; }
    u8      GetCasAliasType() const {return m_byCascadeAliasType;}

    void    SetUseCallingMatch(u8 byUseMatch) { m_byUseCallingMatch = byUseMatch; }
    u8      GetUseCallingMatch( void ) const { return m_byUseCallingMatch;    }

	void SetMSSsrc(u32 dwSSrc)
    {
        m_dwMsSSrc = htonl(dwSSrc);
    }
    u32 GetMSSsrc(void) const
    {
        return ntohl(m_dwMsSSrc);
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//Э�������������Ϣ(h323)
struct TMtAdpCfg 
{
protected:
    u16 m_wPartlistRefreshTime;             //����ʱ�ն��б�ˢ��ʱ����(s)
    u16 m_wAudInfoRefreshTime;              //����ʱ��Ƶ��Ϣˢ��ʱ����(s)
    u16 m_wVidInfoRefreshTime;              //����ʱ��Ƶ��Ϣˢ��ʱ����(s)

public:
    TMtAdpCfg(void) 
    {             
        SetPartListRefreshTime(PARTLIST_REFRESHTIME);  
        SetAudInfoRefreshTime(AUDINFO_REFRESHTIME);
        SetVidInfoRefreshTime(VIDINFO_REFRESHTIME);
    }    
    
    void    SetPartListRefreshTime(u16 wTime) { m_wPartlistRefreshTime = htons(wTime); }
    u16     GetPartListRefreshTime(void) { return ntohs(m_wPartlistRefreshTime); }
    void    SetAudInfoRefreshTime(u16 wTime) { m_wAudInfoRefreshTime = htons(wTime); }
    u16     GetAudInfoRefreshTime(void) { return ntohs(m_wAudInfoRefreshTime); }
    void    SetVidInfoRefreshTime(u16 wTime) { m_wVidInfoRefreshTime = htons(wTime); }
    u16     GetVidInfoRefreshTime(void) { return ntohs(m_wVidInfoRefreshTime); }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;


//////////////////////////////////////////////////
//      ������Ϣ�õ��Ľṹ
//////////////////////////////////////////////////

struct TMcuMcuReq
{
	s8 m_szUserName[MAXLEN_PWD];
	s8 m_szUserPwd[MAXLEN_PWD];
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TMtViewPos
{
    s32  m_nViewID;
    u8   m_bySubframeIndex;    
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TMtVideoInfo
{
    s32			m_nViewCount;                   
    TMtViewPos  m_atViewPos[MAXNUM_VIEWINCONF]; //�ն�����Щ��ͼ��
    s32			m_nOutputLID;                   //�ն˽����ĸ���ͼ
    s32			m_nOutVideoSchemeID;           //���뵽�ն˵���Ƶ����ID(��һ������֧�����ֻ����ʽ)                        
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TMcuMcuMtInfo
{
    TMcuMcuMtInfo()
    {
        memset(this, 0, sizeof(TMcuMcuMtInfo));
    }
    TMt         m_tMt;
    s8 			m_szMtName[VALIDLEN_ALIAS];     
    u32			m_dwMtIp; 
    s8          m_szMtDesc[VALIDLEN_ALIAS];
    u8			m_byMtType;          // �ϼ����¼�Mcu ��Mt 
    u8          m_byManuId;          //���̱��,�μ����̱�Ŷ���
	u8			m_byVideoIn;       
    u8			m_byVideoOut;      
    u8			m_byVideo2In;     
    u8			m_byVideo2Out;     
    u8			m_byAudioIn;       
    u8			m_byAudioOut;      
    u8		    m_byIsDataMeeting;    
    u8		    m_byIsVideoMuteIn;    
    u8			m_byIsVideoMuteOut;   
    u8			m_byIsAudioMuteIn;    
    u8			m_byIsAudioMuteOut;   
    u8          m_byIsConnected;     
    u8			m_byIsFECCEnable;     
    u8          m_byProtocolType;
    TMtVideoInfo m_tPartVideoInfo;   
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TCSchemeInfo
{
    s32		m_nVideoSchemeID;   //��Ƶ�������ID
    u32		m_dwMaxRate;        //max rate (kbps)
    u32		m_dwMinRate;        //min rate (kbps)
    BOOL	m_bCanUpdateRate;   // whether or not enable update rate
    s32     m_nFrameRate;       // frame rate (30��25)
    u8		m_byMediaType;      //
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TCViewInfo
{
    s32				m_nViewId;							//������ͼ ID
    u8              m_byRes;							//������ͼͼ��ķֱ���
    u8              m_byCurGeoIndex;					//������ͼ��ǰ����ʹ��(���)�ļ��β���,���ڼ��β����б��е�����������
    u8              m_byGeoCount;						//���β��ֵ���Ŀ
    u8              m_abyGeoInfo[MAXNUM_GEOINVIEW];		//���β����б�
    u8              m_byMtCount;						//������ͼ����ƵԴ����Ŀ
    TMt             m_atMts[MAXNUM_SUBFRAMEINGEO];		//��ƵԴ�б�
    u8              m_byVSchemeCount;					//��ѡ����Ƶ���������Ŀ
    TCSchemeInfo    m_atVSchemes[MAXNUM_VSCHEMEINVIEW]; //��Ƶ��������б�

    // guzh [7/19/2007]
    u8              m_byAutoSwitchStatus;               //�Զ���ѯ�ش�
    u8              m_byDynamic;
    s32             m_nAutoSwitchTime;                  //��ѯ�ش�ʱ����
    s32             m_nVideoRole;
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TCConfViewInfo
{
	u8          m_byDefViewIndex;			//Ĭ�ϻ�����ͼ����
    u8          m_byViewCount;					//������ͼ����Ŀ
    TCViewInfo	m_atViewInfo[MAXNUM_VIEWINCONF];//������ͼ�б�
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//��������Ϣ�����ܻ��ж��speaker������ֻ���ƶ�һ��
struct TCMixerInfo
{
    s32    m_nMixerID;					//mixer ID
    TMt    m_tSpeaker;					//speaker Pid
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//MCU�Ļ���������Ϣ
struct TCConfAudioInfo
{
    u8				m_byMixerCount;						//��������Ŀ
    u8				m_byDefMixerIndex;					//ȱʡ����������������ʾ,��Ҳ�ǵ�ǰ���ڲ����Ļ�����
    TCMixerInfo     m_tMixerList[MAXNUM_MIXERINCONF];	//�������б�
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TCConfViewChangeNtf
{
	s32  m_nViewID;
    u8   m_bySubframeCount;    
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TMtMediaChanStatus
{
	TMt		m_tMt;
    u8		m_byMediaMode;        //ý��ģʽ��MODE_VIDEO,MODE_AUDIO��
    u8		m_byIsDirectionIn;      //ý������������
    BOOL	m_bMute;              //true:�жϸ÷����������false:�򿪸÷����ý������
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TCAutoSwitchReq
{
    TCAutoSwitchReq(){ memset(this, 0, sizeof(TCAutoSwitchReq)); }

    s32     m_nSwitchLayerId;              
    s32     m_nSwitchSpaceTime;     //��ѵʱ����
    s32     m_nAutoSwitchLevel;     //��ѯ����,��ϸ����δ֪,1��������0��ֹͣ
    BOOL32  m_bSwitchOn;            //��ѯ��ͣ
    
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TSetInParam
{
	TMt m_tMt;
	s32 m_nViewId;
	u8  m_bySubFrameIndex;
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TCConfViewOutInfo
{    
	TMt m_tMt;
    s32 m_nOutViewID;         
    s32 m_nOutVideoSchemeID;  
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TSetOutParam 
{
    s32					m_nMtCount;           
    TCConfViewOutInfo   m_atConfViewOutInfo[MAXNUM_CONF_MT];
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;


//////////////////////////////////////////////////////////////////////////
//						���ý��滯���ýṹ
//////////////////////////////////////////////////////////////////////////

//mcu IP��ַ���������롢����IP����š��ۺ�
struct TMcuEqpCfg
{
protected:
    u32 m_dwMcuIpAddr;          //mcu Ip��ַ
    u32 m_dwMcuSubnetMask;      //mcu ��������
    u32 m_dwGWIpAddr;           //���� Ip��ַ
    u8	m_byLayer;              //���
    u8  m_bySlotId;             //��id
    u8  m_byInterface;          //ǰ������
	u8  m_byRemain;				// save
public:
    TMcuEqpCfg(void) { memset(this, 0, sizeof(TMcuEqpCfg)); }
    
    void    SetMcuIpAddr(u32 dwIpAddr) { m_dwMcuIpAddr = htonl(dwIpAddr); }     //host order
    u32     GetMcuIpAddr(void)  { return ntohl(m_dwMcuIpAddr); }
    void    SetMcuSubNetMask(u32 dwMask) { m_dwMcuSubnetMask = htonl(dwMask); }
    u32     GetMcuSubNetMask(void) { return ntohl(m_dwMcuSubnetMask); }
    void    SetGWIpAddr(u32 dwGWIpAddr) { m_dwGWIpAddr = htonl(dwGWIpAddr); }   //host order
    u32     GetGWIpAddr(void) { return ntohl(m_dwGWIpAddr); }
    void    SetLayer(u8 byLayer) { m_byLayer = byLayer; }
    u8      GetLayer(void) { return m_byLayer; }   
    void    SetSlot(u8 bySlotId) { m_bySlotId = bySlotId; }
    u8      GetSlot(void) { return m_bySlotId; }   
	void    SetInterface(u8 byInterface){ m_byInterface = byInterface;}
	u8      GetInterface(void) const { return m_byInterface;}
	
    void    Print(void)
    {
        OspPrintf(TRUE, FALSE, "McuIpAddr:0x%x, McuSubnetMask:0x%x, GWIpAddr:0x%x, Layer:%d, SlotId:%d, Interface: %d\n",
                  GetMcuIpAddr(), GetMcuSubNetMask(), GetGWIpAddr(), GetLayer(), GetSlot(), GetInterface());
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//����ϳ�������Ϣ
struct TVmpStyleCfgInfo
{    
protected:
    u8  m_bySchemeId;                   //����id��1��5
	u8	m_byRimEnabled;					//�Ƿ�ʹ�ñ߿�: 0-��ʹ��(Ĭ��) 1-ʹ��;
										//���ֶ�Ŀǰֻ�Է���0��Ч, ���������ݲ��漰���ֶε����ú��ж�
	u8	m_byReserved1;					//�����ֶ�1
	u8	m_byReserved2;					//�����ֶ�2
    u32 m_dwBackgroundColor;            //ͼ�񱳾�ɫ
    u32 m_dwFrameColor;                 //ͼ��߿�ɫ
    u32 m_dwSpeakerFrameColor;          //�����˱߿�ɫ
    u32 m_dwChairFrameColor;            //��ϯ�߿�ɫ 
	u8  m_byFontType;                   // �ϳ���������
	u8  m_byFontSize;					// �ϳ������ֺ�
	u8  m_byAlignment;                  // ���뷽ʽ
	u32  m_dwTextColor;                  // �ϳ�����������ɫ
	u32  m_dwTopicBkColor;               // �ϳ����ⱳ��ɫ
	u32  m_dwDiaphaneity;                // �ϳ�����͸����
    s8  m_achSchemeAlias[MAX_VMPSTYLE_ALIASLEN];  // ����ϳɷ�������

public:
    TVmpStyleCfgInfo(void) { Clear();   }

	void	Clear(void)  { memset(this, 0, sizeof(TVmpStyleCfgInfo)); }
	void	SetNull(void) { Clear(); }
	BOOL32  IsNull(void) 
    { 
        TVmpStyleCfgInfo tInfo;
        return (0 == memcmp(this, &tInfo, sizeof(TVmpStyleCfgInfo)));
    }
    void    SetSchemeId(u8 bySchemeId) { m_bySchemeId = bySchemeId; }
    u8      GetSchemeId(void) { return m_bySchemeId; }    
    void    SetBackgroundColor(u32 dwColor) { m_dwBackgroundColor = htonl(dwColor); }
    u32     GetBackgroundColor(void) { return ntohl(m_dwBackgroundColor); }
    void    SetFrameColor(u32 dwColor) { m_dwFrameColor = htonl(dwColor); }
    u32     GetFrameColor(void) { return ntohl(m_dwFrameColor); }
    void    SetSpeakerFrameColor(u32 dwColor) { m_dwSpeakerFrameColor = htonl(dwColor); }
    u32     GetSpeakerFrameColor(void) { return ntohl(m_dwSpeakerFrameColor); }
    void    SetChairFrameColor(u32 dwColor) { m_dwChairFrameColor = htonl(dwColor); }
    u32     GetChairFrameColor(void) { return ntohl(m_dwChairFrameColor); }
	void	SetIsRimEnabled(BOOL32 bEnabled){ m_byRimEnabled = GETBBYTE(bEnabled); }
	BOOL32	GetIsRimEnabled(void) const { return m_byRimEnabled == 1 ? TRUE : FALSE; }
	void    SetFontType(u8 byFontType) { m_byFontType = byFontType;}
	u8      GetFontType(void) { return m_byFontType;}
	void    SetFontSize(u8 byFontSize ) { m_byFontSize = byFontSize;}
	u8      GetFontSize(void) { return m_byFontSize;}
	void    SetAlignment(u8 byValue ) { m_byAlignment = byValue;}
	u8      GetAlignment(void) { return m_byAlignment;}
	void    SetTextColor(u32 dwTextColor ) { m_dwTextColor = htonl(dwTextColor);}
	u32     GetTextColor(void) { return ntohl(m_dwTextColor);}
	void    SetTopicBkColor(u32 dwBkColor) { m_dwTopicBkColor = htonl(dwBkColor);}
	u32     GetTopicBkColor(void) { return ntohl(m_dwTopicBkColor);}
	void    SetDiaphaneity(u32 dwDiaphaneity ) { m_dwDiaphaneity = htonl(dwDiaphaneity); }
	u32     GetDiaphaneity(void) { return ntohl(m_dwDiaphaneity);}

    void    SetSchemeAlias(s8* pchSchemeAlias)
    {
        memcpy(m_achSchemeAlias, pchSchemeAlias, sizeof(m_achSchemeAlias));
        m_achSchemeAlias[MAX_VMPSTYLE_ALIASLEN-1] = '\0';
    }
    
    void    GetSchemeAlias(s8* pchSchemeAlias, u8 byBufferLen)
    {
        u8 byAliasLen = (byBufferLen < sizeof(m_achSchemeAlias) ) ? byBufferLen : sizeof(m_achSchemeAlias);
        memcpy(pchSchemeAlias, m_achSchemeAlias, byAliasLen);
    }
    
    void    ResetDefaultColor(void)
    {
        SetBackgroundColor(VMPSTYLE_DEFCOLOR);
        SetSpeakerFrameColor(VMPSTYLE_DEFCOLOR);
        SetChairFrameColor(VMPSTYLE_DEFCOLOR);
        SetFrameColor(VMPSTYLE_DEFCOLOR);
		SetFontType(FONT_SONG);
		SetFontSize(FONT_SIZE_24);
		SetAlignment(MIDDLE_ALIGN);
		SetTextColor(DEFAULT_TEXT_COLOR);
		SetTopicBkColor(DEFAULT_BACKGROUND_COLOR);
		SetDiaphaneity(DEFAULT_DIAPHANEITY);
    }

	inline BOOL operator == (const TVmpStyleCfgInfo& tVmpStyle )
	{
		BOOL bRet = TRUE;
		if( this == &tVmpStyle )
		{
			return bRet;
		}
		
		if ( 0 != memcmp(this, &tVmpStyle, sizeof(TVmpStyleCfgInfo)) )
		{
			bRet = FALSE;
		}
		return bRet;
	}

    void    Print(void)
    {	
		OspPrintf(TRUE, FALSE, "VmpStyleInfo(SchemeId:%d)\n BackColor:0x%x, AudienceColor:0x%x, SpeakerColor:0x%x, ChairColor:0x%x, IsRimEnabled:%d\n",
			GetSchemeId(), GetBackgroundColor(), GetFrameColor(), GetSpeakerFrameColor(), GetChairFrameColor(), GetIsRimEnabled() );
		OspPrintf(TRUE, FALSE, "VmpStyleInfo: \n FontType:%d, FontSize:%d, TextColor:0x%x, BkColor:0x%x, Diaphaneity:0x%x\n",
			GetFontType(), GetFontSize(), GetTextColor(), GetTopicBkColor(), GetDiaphaneity() );
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;
//Ԥ������ͨ������������Դ�ṹ   jlb
struct THduChnlCfgInfo
{
protected:
	u8   m_byChnlIdx;               //ͨ��������
	u8   m_byEqpId;					//�豸ID
	u8   m_byChnlVolumn;            //ͨ������
	BOOL m_bIsChnlBeQuiet;          //ͨ������
	s8   m_achEqpAlias[MAXLEN_EQP_ALIAS];   //�������
public:
	THduChnlCfgInfo(){ SetNull(); }
    void SetNull(void)
	{
        memset( this, 0, sizeof(THduChnlCfgInfo) );
	    return;
	}

	u8   GetChnlIdx(void) const { return m_byChnlIdx; }
	void SetChnlIdx(u8 val) { m_byChnlIdx = val; }

	u8   GetEqpId(void) const { return m_byEqpId; }
	void SetEqpId(u8 val) { m_byEqpId = val; }

	u8   GetChnlVolumn(void) const { return m_byChnlVolumn; }
	void SetChnlVolumn(u8 val) { m_byChnlVolumn = val; }

	BOOL GetIsChnlBeQuiet(void) const { return m_bIsChnlBeQuiet; }
	void SetIsChnlBeQuiet(BOOL val) { m_bIsChnlBeQuiet = val; }

	void SetEqpAlias(LPCSTR pchEqpAlias)
    {
		//fixme
        memcpy(m_achEqpAlias, pchEqpAlias, MAXLEN_EQP_ALIAS);
        m_achEqpAlias[sizeof(m_achEqpAlias) - 1] = '\0';
    }
	
	LPCSTR GetEqpAlias(void){ return m_achEqpAlias; }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
; 

//HDUԤ�跽���ṹ   jlb
struct THduStyleCfgInfo 
{
protected:
	u8   m_byStyleIdx;          //����Id��

	u8   m_byTotalChnlNum;      //������Ҫ��ͨ�������������п����õ����ͨ����
                                //���ݲ�ͬ�ķ�����Ϊ1��2��4������56�����56��
	THduChnlCfgInfo m_atHduChnlCfgTable[MAXNUM_HDUCFG_CHNLNUM];  //��ͨ����Ҫ��������Դ
	//m_bywidth * m_byHeight <= 56
	u8   m_byWidth;             //�������õĿ��
	u8   m_byHeight;            //�������õĸ߶�
    u8   m_byVolumn;            //����ͨ��ͳһ������С
	BOOL m_bIsBeQuiet;          //����ͨ���Ƿ�ͳһ����
	s8  m_achSchemeAlias[MAX_HDUSTYLE_ALIASLEN];   //Ԥ��������
	
public:
    THduStyleCfgInfo(void) { SetNull(); }
	void	SetNull(void)  { memset(this, 0, sizeof(THduStyleCfgInfo)); }
	BOOL32  IsNull(void) 
    { 
        THduStyleCfgInfo tInfo;
        return (0 == memcmp(this, &tInfo, sizeof(THduStyleCfgInfo)));
    }
    
	//patHduChnlCfgTable  Ϊ����ָ�룬Ԫ�ظ���ΪMAXNUM_HDUCFG_CHNLNUM
	void GetHduChnlCfgTable(THduChnlCfgInfo *patHduChnlCfgTable)
	{
		memcpy(patHduChnlCfgTable, m_atHduChnlCfgTable, MAXNUM_HDUCFG_CHNLNUM*sizeof(THduChnlCfgInfo));
        return;
	}
	//patHduChnlCfgTable  Ϊ����ָ�룬Ԫ�ظ���ΪMAXNUM_HDUCFG_CHNLNUM
	BOOL32 SetHduChnlCfgTable(THduChnlCfgInfo *patHduChnlCfgTable)
	{
		BOOL32 bRet = TRUE;
		if (NULL == patHduChnlCfgTable)
		{
			bRet = FALSE;
			OspPrintf(TRUE, FALSE, "[mcustruct.h]:SetHduChnlCfgTable()-->patHduChnlCfgTable is NULL\n");
		}

		memcpy(m_atHduChnlCfgTable, patHduChnlCfgTable, MAXNUM_HDUCFG_CHNLNUM*sizeof(THduChnlCfgInfo));
		return bRet;
	}

	u8   GetStyleIdx(void) const { return m_byStyleIdx; }
	void SetStyleIdx(u8 val) { m_byStyleIdx = val; }

	u8   GetTotalChnlNum(void) const { return m_byTotalChnlNum; }
	void SetTotalChnlNum(u8 val) { m_byTotalChnlNum = val; }

	u8   GetWidth(void) const { return m_byWidth; }
	void SetWidth(u8 val) { m_byWidth = val; }

	u8   GetHeight(void) const { return m_byHeight; }
	void SetHeight(u8 val) { m_byHeight = val; }

	u8   GetVolumn(void) const { return m_byVolumn; }
	void SetVolumn(u8 val) { m_byVolumn = val; }

	BOOL GetIsBeQuiet(void) const { return m_bIsBeQuiet; }
	void SetIsBeQuiet(BOOL val) { m_bIsBeQuiet = val; }

	void SetSchemeAlias(LPCSTR pchSchemeAlias)
    {
        memcpy(m_achSchemeAlias, pchSchemeAlias, sizeof(m_achSchemeAlias));
        m_achSchemeAlias[MAX_HDUSTYLE_ALIASLEN-1] = '\0';
    }
    
	LPCSTR GetSchemeAlias(void){ return m_achSchemeAlias; }

	inline BOOL operator == (const THduStyleCfgInfo& tHduStyle )
	{
		BOOL bRet = TRUE;
		if( this == &tHduStyle )
		{
			return bRet;
		}
		
		if ( 0 != memcmp(this, &tHduStyle, sizeof(THduStyleCfgInfo)) )
		{
			bRet = FALSE;
		}
		return bRet;
	}

    void Print(void)
	{
		OspPrintf(TRUE, FALSE, "[THduStyleCfgInfo]: StyleIdx:%d, TotalChnlNum:%d, Width:%d, Height:%d, Volumn:%d, IsBeQuiet:%d\n",
			      GetStyleIdx(), GetTotalChnlNum(), GetWidth(), GetHeight(), GetVolumn(), GetIsBeQuiet());
		OspPrintf(TRUE, FALSE, "[THduStyleCfgInfo]: Hdu Scheme Alias is:%s \n",m_achSchemeAlias);
	    
		OspPrintf(TRUE, FALSE, "[THduStyleCfgInfo]:\n");
		u16 wIndex;
		for ( wIndex=0; wIndex<GetTotalChnlNum(); wIndex++)
	    {
			OspPrintf(TRUE, FALSE, "[%d]:  ChnlIdx:%d, EqpId:%d, ChnlVolumn:%d, IsChnlBeQuiet:%d\n",
				       m_atHduChnlCfgTable[wIndex].GetChnlIdx(),
					   m_atHduChnlCfgTable[wIndex].GetEqpId(),
					   m_atHduChnlCfgTable[wIndex].GetChnlVolumn(),
    				   m_atHduChnlCfgTable[wIndex].GetIsChnlBeQuiet());
	    }

		return;
	}

}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// hdu������ѯԤ����Ϣ
struct THduPollSchemeInfo 
{
protected:
	u32  m_dwKeepTime;                       // ��ѯ����
	u8   m_byCycles;                         // ��ѯ���ڴ���
	u8   m_byStatus;                         // ��ǰ������ѯ״̬
	u8   m_byReserved1;
    u8   m_byReserved2;
public:
	THduStyleCfgInfo m_tHduStyleCfgInfo;     // ����Ԥ��Ԥ��������Ϣ

public:
	THduPollSchemeInfo()
	{
        SetNull();
	}
	void SetNull( void )
	{
		m_dwKeepTime = 0;
		m_byCycles = 0;
		m_byStatus = POLL_STATE_NONE;
		m_byReserved1 = 0;
		m_byReserved2 = 0;
		
		m_tHduStyleCfgInfo.SetNull();
	}
	u32   GetKeepTime( void )
	{
		return ntohl(m_dwKeepTime);
	}
	void SetKeepTime( u32 dwKeepTime )
	{
		m_dwKeepTime = htonl(dwKeepTime);
	}

	u8   GetCycles( void )
	{
		return m_byCycles;
	}
	void SetCycles( u8 byCycles )
	{
		m_byCycles = byCycles;
	}

	u8   GetStatus( void )
	{
		return m_byStatus;
	}
	void SetStatus( u8 byStatus )
	{
		m_byStatus = byStatus;
	}

}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// ������ѯǰ��Ԥ���б�ռ��ͨ����Ϣ
struct THduChnlInfoInUse
{
protected:
	u8    m_byConfIdx;       // ����������
	u8    m_byEqpId;         // ����ID
	u8    m_byChlIdx;        // ͨ��������
	u8    m_byResverd;       

public:
	THduChnlInfoInUse()
	{
		memset(this, 0x0, sizeof(THduChnlInfoInUse));
	}

	u8    GetConfIdx( void ){ return m_byConfIdx; }
	void  SetConfIdx( u8 byConfIdx ){ m_byConfIdx = byConfIdx; }

	u8    GetEqpId( void ){ return m_byEqpId; }
	void  SetEqpId( u8 byEqpId ){ m_byEqpId = byEqpId; }

	u8    GetChlIdx( void ){ return m_byChlIdx; }
	void  SetChlIdx( u8 byChlIdx ){ m_byChlIdx = byChlIdx; }

}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//�������û���
struct TEqpCfgInfo
{
protected:    
    s8  m_szAlias[MAXLEN_EQP_ALIAS];		//����
    u16 m_wMcuStartPort;					//mcu������ʼ�˿ں�
    u16 m_wEqpStartPort;					//���������ʼ�˿ں�    
    u8  m_byEqpId;							//�豸ID
    u8  m_bySwitchBrdIndex;					//����������     
    u8  m_byRunningBrdIndex;				//���а�����
    u8  m_byMapCount;						//ʹ�õ�MAP����
    u8  m_abyMapId[MAXNUM_MAP];				//Map�������

public:
    TEqpCfgInfo(void) { memset(this, 0, sizeof(TEqpCfgInfo)); }

    void    SetEqpId(u8 byEqpId) { m_byEqpId = byEqpId; }
    u8      GetEqpId(void) { return m_byEqpId; }
    void    SetMcuStartPort(u16 wPort) { m_wMcuStartPort = htons(wPort); }
    u16     GetMcuStartPort(void)   { return ntohs(m_wMcuStartPort); } 
    void    SetEqpStartPort(u16 wPort) { m_wEqpStartPort = htons(wPort); }
    u16     GetEqpStartPort(void) { return ntohs(m_wEqpStartPort); }
    void    SetSwitchBrdIndex(u8 byIndex) { m_bySwitchBrdIndex = byIndex; }
    u8      GetSwitchBrdIndex(void) { return m_bySwitchBrdIndex; }
    void    SetRunningBrdIndex(u8 byIndex) { m_byRunningBrdIndex = byIndex; }
    u8      GetRunningBrdIndex(void)    { return m_byRunningBrdIndex; }

    //���з��������������MAU���⴦����
protected:
    void    SetMapCount(u8 byCount) { m_byMapCount = byCount; }
    u8      GetMapCount(void) const { return m_byMapCount; }

public:
    void    SetAlias(LPCSTR lpszAlias)
    {
        if(NULL != lpszAlias)
        {
            strncpy(m_szAlias, lpszAlias, sizeof(m_szAlias));
            m_szAlias[sizeof(m_szAlias) - 1] = '\0';
        }        
    }
    const s8* GetAlias(void) { return m_szAlias; }

    BOOL32    SetMapId(u8 *pbyMapId, u8 byCount)
    {
        if(NULL == pbyMapId || byCount > MAXNUM_MAP)
            return FALSE;
        
        memcpy(m_abyMapId, pbyMapId, byCount);
        m_byMapCount = byCount;
        return TRUE;
    }
    BOOL32     GetMapId(u8 *pbyMapId, u8 &byCount)
    {
        if(NULL == pbyMapId)
            return FALSE;
        
        memcpy(pbyMapId, m_abyMapId, m_byMapCount);
        byCount = m_byMapCount;
        return TRUE;
    }

    void PrintMap(void)
    {
        OspPrintf(TRUE, FALSE, "MapCount: %d, MapId: %d,%d,%d,%d,%d\n", 
            m_byMapCount, m_abyMapId[0], m_abyMapId[1], m_abyMapId[2], m_abyMapId[3], m_abyMapId[4]);
        
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// ��������Ϣ
//�豸id,����,mcu��ʼ�˿�,�豸��ʼ�˿�,����������,���а�����,ÿ��map����������,map���
struct TEqpMixerCfgInfo : public TEqpCfgInfo
{
protected:    
    u8  m_byMaxChnnlInGrp;					//���������ͨ����
   
public:
    TEqpMixerCfgInfo(void):m_byMaxChnnlInGrp(MAXNUM_MIXER_CHNNL) {}
    
    void    SetMaxChnnlInGrp(u8 byChnnlNum) { m_byMaxChnnlInGrp = byChnnlNum; }
    u8      GetMaxChnnlInGrp(void)  { return m_byMaxChnnlInGrp; } 
    
    void    Print(void) 
    {
        OspPrintf(TRUE, FALSE, "\nMixer:%s\nEqpId:%d, SwitchBrd:%d, RunBrd:%d, McuPort:%d, MixerPort:%d, MaxChnnl:%d\n",
                  GetAlias(), GetEqpId(), GetSwitchBrdIndex(), GetRunningBrdIndex(), 
                  GetMcuStartPort(), GetEqpStartPort(), GetMaxChnnlInGrp());
        PrintMap();
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// ¼�����Ϣ
//�豸id,����,mcu��ʼ�˿�,�豸��ʼ�˿�,����������,¼���ip
struct TEqpRecCfgInfo : public TEqpCfgInfo
{
protected:
    u32 m_dwIpAddr;							//���ַ���¼�����Ip��ַ

public:
    TEqpRecCfgInfo(void):m_dwIpAddr(0) {}
  
    void    SetIpAddr(u32 dwIpAddr)  { m_dwIpAddr = htonl(dwIpAddr); }  //host order
    u32     GetIpAddr(void) { return ntohl(m_dwIpAddr); }

    void    Print(void)
    {
        OspPrintf(TRUE, FALSE, "\nRec:%s\nEqpId:%d, SwitchBrd:%d, McuPort:%d, RecPort:%d, RecIp:0x%x\n",
                  GetAlias(), GetEqpId(), GetSwitchBrdIndex(), GetMcuStartPort(), 
                  GetEqpStartPort(), GetIpAddr());
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// ����bas����Ϣ
//�豸id,����,mcu��ʼ�˿�,�豸��ʼ�˿�,����������,���а�����,����bas��ip
struct TEqpBasHDCfgInfo : public TEqpCfgInfo
{
protected:
    u32 m_dwIpAddr;							//Ip��ַ

public:
    TEqpBasHDCfgInfo(void):m_dwIpAddr(0) {}
  
    void    SetIpAddr(u32 dwIpAddr)  { m_dwIpAddr = htonl(dwIpAddr); }  //host order
    u32     GetIpAddr(void) { return ntohl(m_dwIpAddr); }
    void    SetType(u8 byType) { SetMapCount(byType); }
    u8      GetType(void) const { return GetMapCount(); }

    void    Print(void)
    {
        OspPrintf(TRUE, FALSE, "\nRec:%s\nEqpId:%d, SwitchBrd:%d, McuPort:%d, RecPort:%d, RecIp:0x%x, Type.%d\n",
                  GetAlias(), GetEqpId(), GetSwitchBrdIndex(), GetMcuStartPort(), 
                  GetEqpStartPort(), GetIpAddr(), GetType());
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// ����ǽ��Ϣ
//�豸id,����,�豸��ʼ�˿�,����������,map���
struct TEqpTvWallCfgInfo : public TEqpCfgInfo
{     
    void    Print(void)
    {
        OspPrintf(TRUE, FALSE, "\nTvWall:%s\nEqpId:%d, RunBrd:%d, TWPort:%d\n",
                 GetAlias(), GetEqpId(), GetRunningBrdIndex(), GetEqpStartPort());
        PrintMap();
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;
struct THduChnlModePort
{
public:
	THduChnlModePort()
	{
		memset(this, 0x0, sizeof(THduChnlModePort));
	}
	u8 GetZoomRate() const { return byZoomRate; }
	void SetZoomRate(u8 val) { byZoomRate = val; }

    u8 GetOutPortType() const { return byOutPortType; }
    void SetOutPortType(u8 val) { byOutPortType = val; }
	
    u8 GetOutModeType() const { return byOutModeType; }
    void SetOutModeType(u8 val) { byOutModeType = val; }
private:
    u8 byOutPortType;
    u8 byOutModeType;
    u8 byZoomRate;
    u8 reserved;
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
; 

//Hdu��Ϣ  jlb
struct TEqpHduCfgInfo : public TEqpCfgInfo 
{
protected:
	
    THduChnlModePort atHduChnlModePort[MAXNUM_HDU_CHANNEL];    
	
public:
	TEqpHduCfgInfo()
	{
        memset(&atHduChnlModePort, 0X0, sizeof(atHduChnlModePort));
	}
	
	void GetHduChnlModePort( u8 byNum, THduChnlModePort &tHduChnModePort )
	{
		if (byNum == 0 || byNum == 1)
		{
			tHduChnModePort.SetOutModeType( atHduChnlModePort[byNum].GetOutModeType() );
			tHduChnModePort.SetOutPortType( atHduChnlModePort[byNum].GetOutPortType() );
		    tHduChnModePort.SetZoomRate( atHduChnlModePort[byNum].GetZoomRate() );	
		}
		else
		{
			OspPrintf(TRUE, FALSE, "[TEqpHduCfgInfo]:GetHduChnlModePort()'s byNum wrong!\n");
			return;			
		}
		
		return;
	}
	
    void SetHduChnlModePort( u8 byNum, THduChnlModePort &tHduChnModePort )
	{
		if (byNum == 0 || byNum == 1)
		{
			atHduChnlModePort[byNum].SetOutModeType( tHduChnModePort.GetOutModeType() );
 			atHduChnlModePort[byNum].SetOutPortType( tHduChnModePort.GetOutPortType() );
            atHduChnlModePort[byNum].SetZoomRate( tHduChnModePort.GetZoomRate() );			
		}
		else
		{
			OspPrintf(TRUE, FALSE, "[TEqpHduCfgInfo]:SetHduChnlModePort()'s byNum wrong!\n");
			return;	
		}
		
		return;
	}
	
	void Print(void)
	{
		OspPrintf(TRUE, FALSE, "\nHdu:%s\nEqpId:%d, RunBrd:%d, HduPort:%d\n,ZoomRate[0] = %d, ZoomRate[1] = %d\n HduOutPortType[0]:%d, HduOutModeType[0]:%d\n,HduOutPortType[1]:%d, HduOutModeType[1]%d:",
			GetAlias(), GetEqpId(), GetRunningBrdIndex(), GetEqpStartPort(), 
			atHduChnlModePort[0].GetZoomRate(), atHduChnlModePort[1].GetZoomRate(),
			atHduChnlModePort[0].GetOutPortType(), atHduChnlModePort[0].GetOutModeType(),
			atHduChnlModePort[1].GetOutPortType(), atHduChnlModePort[1].GetOutModeType());
	}
}
#ifndef WIN32
__attribute__ ( (packed) )
#endif
;

//svmp(��vmpģʽ)��Ϣ   jlb
struct TEqpSvmpCfgInfo : public TEqpCfgInfo
{
    void    Print(void)
    {
        OspPrintf(TRUE, FALSE, "\nDvmp:%s\nEqpId:%d, SwitchBrd:%d, RunBrd:%d, McuPort:%d, DvmpPort:%d\n",
			GetAlias(), GetEqpId(), GetSwitchBrdIndex(), GetRunningBrdIndex(),
			GetMcuStartPort(), GetEqpStartPort());
    }
}
#ifndef WIN32
__attribute__ ( (packed) )
#endif
;

//dvmp(˫vmpģʽ)�е���vmp����Ϣ   jlb
struct TEqpDvmpCfgBasicInfo : public TEqpCfgInfo
{

    void    Print(void)
    {
        OspPrintf(TRUE, FALSE, "\nDvmp:%s\nEqpId:%d, SwitchBrd:%d, RunBrd:%d, McuPort:%d, DvmpPort:%d\n",
			GetAlias(), GetEqpId(), GetSwitchBrdIndex(), GetRunningBrdIndex(),
			GetMcuStartPort(), GetEqpStartPort());
    }
}
#ifndef WIN32
__attribute__ ( (packed) )
#endif
;

//˫vmpģʽ��������Ϣ   jlb
struct TEqpDvmpCfgInfo
{
public:
	TEqpDvmpCfgBasicInfo tEqpDvmpCfgBasicInfo[2];    //�������vmp����Ϣ

public:
	TEqpDvmpCfgInfo()
	{
		memset( this, 0 ,sizeof(TEqpDvmpCfgInfo) );
	}
}
#ifndef WIN32
__attribute__ ( (packed) )
#endif
;

//MpuBas��Ϣ    jlb
struct TEqpMpuBasCfgInfo : public TEqpCfgInfo
{
	void Print(void)
	{
	    OspPrintf(TRUE, FALSE, "\nBas:%s\nEqpId:%d, SwitchBrd:%d, RunBrd:%d, McuPort:%d, BasPort:%d\n",
		    GetAlias(), GetEqpId(), GetSwitchBrdIndex(), GetRunningBrdIndex(),
		    GetMcuStartPort(), GetEqpStartPort());
        PrintMap();
	}
}
#ifndef WIN32
__attribute__ ( (packed) )
#endif
;

// Ebap ��Ϣ
//�豸id,����,mcu��ʼ�˿�,�豸��ʼ�˿�,����������,���а�����,map���
struct TEqpEbapCfgInfo : public TEqpCfgInfo
{
    void    Print(void)
    {
        OspPrintf(TRUE, FALSE, "\nEbap:%s\nEqpId:%d, SwitchBrd:%d, RunBrd:%d, McuPort:%d, EbapPort:%d\n",
			GetAlias(), GetEqpId(), GetSwitchBrdIndex(), GetRunningBrdIndex(),
			GetMcuStartPort(), GetEqpStartPort());
        PrintMap();
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// Evpu ��Ϣ
//�豸id,����,mcu��ʼ�˿�,�豸��ʼ�˿�,����������,���а�����,map���
struct TEqpEvpuCfgInfo : public TEqpCfgInfo
{
    void    Print(void)
    {
        OspPrintf(TRUE, FALSE, "\nVmp:%s\nEqpId:%d, SwitchBrd:%d, RunBrd:%d, McuPort:%d, VmpPort:%d\n",
            GetAlias(), GetEqpId(), GetSwitchBrdIndex(), GetRunningBrdIndex(),
            GetMcuStartPort(), GetEqpStartPort());
        PrintMap();
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;


// Bas ��Ϣ
//�豸id,����,mcu��ʼ�˿�,�豸��ʼ�˿�,����������,���а�����,map���
struct TEqpBasCfgInfo : public TEqpCfgInfo
{
    void    Print(void)
    {
        OspPrintf(TRUE, FALSE, "\nBas:%s\nEqpId:%d, SwitchBrd:%d, RunBrd:%d, McuPort:%d, BasPort:%d\n",
                GetAlias(), GetEqpId(), GetSwitchBrdIndex(), GetRunningBrdIndex(),
                GetMcuStartPort(), GetEqpStartPort());
        PrintMap();
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// Vmp ��Ϣ
//�豸id,����,mcu��ʼ�˿�,�豸��ʼ�˿�,����������,���а�����,map���,ͬʱ��Ƶ����·��
struct TEqpVmpCfgInfo : public TEqpCfgInfo
{
protected:
    u8  m_byEncodeNum;						//ͬʱ֧�ֵ���Ƶ����·��

public:
    TEqpVmpCfgInfo(void) :m_byEncodeNum(0) {}

    void    SetEncodeNum(u8 byEncodeNum) { m_byEncodeNum = byEncodeNum; }
    u8      GetEncodeNum(void)  { return m_byEncodeNum; }

    void    Print(void)
    {
        OspPrintf(TRUE, FALSE, "\nVmp:%s\nEqpId:%d, SwitchBrd:%d, RunBrd:%d, McuPort:%d, VmpPort:%d, EncodeNum:%d\n",
            GetAlias(), GetEqpId(), GetSwitchBrdIndex(), GetRunningBrdIndex(),
            GetMcuStartPort(), GetEqpStartPort(), GetEncodeNum());
        PrintMap();
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//Mtw���ϵ���ǽ��Ϣ
//�豸id,����,�豸��ʼ�˿�,����������,map���
struct TEqpMTvwallCfgInfo : public TEqpCfgInfo
{
    void    Print(void)
    {
        OspPrintf(TRUE, FALSE, "\nMTvwall:%s\nEqpId:%d, RunBrd:%d, MTWPort:%d\n",
            GetAlias(), GetEqpId(), GetRunningBrdIndex(), GetEqpStartPort());
        PrintMap();
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// Prs��Ϣ
//�豸id,����,mcu��ʼ�˿�,�豸��ʼ�˿�,����������,���а�����,�ش�����1,2,3,���ڶ���ʱ��
struct TPrsCfgInfo : public TEqpCfgInfo
{
protected:
    u16 m_wFirstTimeSpan;						//��һ���ش�����(ms)
    u16 m_wSecondTimeSpan;						//�ڶ����ش�����(ms)
    u16 m_wThirdTimeSpan;						//�������ش�����(ms)
    u16 m_wLoseTimeSpan;						//���ڶ�����ʱ����(ms)

public:
    TPrsCfgInfo(void)
    {
        SetFirstTimeSpan(DEF_FIRSTTIMESPAN_PRS);
        SetSecondTimeSpan(DEF_SECONDTIMESPAN_PRS);
        SetThirdTimeSpan(DEF_THIRDTIMESPAN_PRS);
        SetLoseTimeSpan(DEF_LOSETIMESPAN_PRS);
    }

    void    SetFirstTimeSpan(u16 wTimeSpan) { m_wFirstTimeSpan = htons(wTimeSpan); }
    u16     GetFirstTimeSpan(void)  { return ntohs(m_wFirstTimeSpan); }
    void    SetSecondTimeSpan(u16 wTimeSpan) { m_wSecondTimeSpan = htons(wTimeSpan); }
    u16     GetSecondTimeSpan(void) { return ntohs(m_wSecondTimeSpan); }
    void    SetThirdTimeSpan(u16 wTimeSpan) { m_wThirdTimeSpan = htons(wTimeSpan); }
    u16     GetThirdTimeSpan(void)  { return ntohs(m_wThirdTimeSpan); }
    void    SetLoseTimeSpan(u16 wTimeSpan) { m_wLoseTimeSpan = htons(wTimeSpan); }
    u16     GetLoseTimeSpan(void)   { return ntohs(m_wLoseTimeSpan); }

    void    Print(void)
    {
        OspPrintf(TRUE, FALSE, "\nPrs:%s\nEqpId:%d, SwitchBrd:%d, RunBrd:%d, McuPort:%d\nPrsPort:%d, FstTime:%d, SndTime:%d, ThdTime:%d, LoseTime:%d\n",
            GetAlias(), GetEqpId(), GetSwitchBrdIndex(), GetRunningBrdIndex(), 
            GetMcuStartPort(), GetEqpStartPort(), GetFirstTimeSpan(), 
            GetSecondTimeSpan(), GetThirdTimeSpan(), GetLoseTimeSpan());
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//����������Ϣ
struct TBrdCfgInfo
{	
protected:
	u8				m_byIndex;					    // ������
    u8				m_byLayer;					    // ���
    u8              m_bySlotId;                     //��id
    u8              m_bySlotType;                   //������
    u8				m_byType;					    // ����
    u32				m_dwBrdIp;					    // ����Ip
    u8				m_bySelNetPort;				    // ����ѡ��
    u8				m_bySelMulticast;			    // �鲥ѡ��   
    u8              m_byBrdState;                   // ����״̬
    u8              m_byOsType;                     // �����OS���� OS_TYPE_WIN32 ...
    s8              m_szAlias[MAXLEN_BRDALIAS];     // ���������� BRD_ALIAS_TUI
public:
    TBrdCfgInfo(void) { memset(this, 0, sizeof(TBrdCfgInfo)); }

    void    SetIndex(u8 byIndex) { m_byIndex = byIndex; }
    u8      GetIndex(void) const { return m_byIndex; }
    void    SetLayer(u8 byLayer) { m_byLayer = byLayer; }
    u8      GetLayer(void) const { return m_byLayer; }    
    void    SetType(u8 byType) { m_byType = byType; }
    u8      GetType(void) const { return m_byType; }
    void    SetIpAddr(u32 dwIpAddr) { m_dwBrdIp = htonl(dwIpAddr); }    //host order
    u32     GetIpAddr(void) const { return ntohl(m_dwBrdIp); }
    void    SetSelNetPort(u8 bySel) { m_bySelNetPort = bySel; }
    u8      GetSelNetPort(void) const { return m_bySelNetPort; }
    void    SetSelMulticast(u8 bySel) { m_bySelMulticast = bySel; }
    u8      GetSelMulticast(void) const{ return m_bySelMulticast; }
    u8      GetBrdState(void) const { return m_byBrdState;}
    void    SetBrdState(u8 byBrdState) { m_byBrdState = byBrdState;}
    u8      GetOsType(void) const { return m_byOsType; }
    void    SetOsType(u8 byOsType) { m_byOsType = byOsType; }

    void SetSlot(u8 bySlotId, u8 bySlotType)
    {
        m_bySlotType = bySlotType;
        m_bySlotId  = bySlotId;      
    }

    void GetSlot(u8 &bySlotId, u8 &bySlotType) const
    { 
        bySlotId = m_bySlotId;
        bySlotType = m_bySlotType;
    }    

    void SetAlias(const s8* pszAlias)
    {
        memset( m_szAlias, 0, sizeof(m_szAlias) );
        strncpy( m_szAlias, pszAlias,  sizeof(m_szAlias) - 1);
    }
    const s8* GetAlias() const
    {
        return m_szAlias;
    }

    void Print(void) const
    {
        u8 bySlotId;
        u8 bySlotType;
        GetSlot(bySlotId, bySlotType);
        OspPrintf(TRUE, FALSE, "Index:%d, Layer:%d, SlotId%d, SlotType%d, BrdType%d, Alias:%s, BrdIp:0x%x, EthInt:%d, Multi:%d, BrdState:%d, OsType:%d\n",
                  GetIndex(), GetLayer(), bySlotId, bySlotType, GetType(), GetAlias(), GetIpAddr(), GetSelNetPort(), GetSelMulticast(), GetBrdState(), GetOsType());
    }
}
#ifndef WIN32
__attribute__( (packed) )
#endif
;

// ����״̬
struct TBoardStatusNotify
{
public:
    TBoardStatusNotify()
    { 
        memset(this, 0, sizeof(TBoardStatusNotify));
        m_byBrdState = BOARD_OUTLINE;
    }

    u8 GetBrdLayer(void) {return m_byBrdLayer;}
    u8 GetBrdSlot(void) {return m_byBrdSlot;}
    u8 GetBrdType(void) {return m_byBrdType;}
    u8 GetBrdState(void) {return m_byBrdState;}
    u8 GetBrdOsType(void) {return m_byOsType;}

    void SetBrdLayer(u8 byLayer) { m_byBrdLayer = byLayer;}
    void SetBrdSlot(u8 bySlot) { m_byBrdSlot = bySlot;}
    void SetBrdType(u8 byType) { m_byBrdType = byType;}
    void SetBrdState(u8 byState) { m_byBrdState = byState;}
    void SetBrdOsType(u8 byType) { m_byOsType = byType; }

private: 
    u8 m_byBrdLayer;
    u8 m_byBrdSlot;
    u8 m_byBrdType;
    u8 m_byBrdState;
    u8 m_byOsType;
}
#ifndef WIN32
__attribute__( (packed) )
#endif
;

//N+1�䱸����Ϣ�ṹ
struct TNPlusInfo
{
protected:
    u32 m_dwNPlusMcuIp;                     //��֧��N+1�Ҳ��Ǳ��ݹ���ģʽ����Ҫ����N+1����mcu�ĵ�ַ
    u16 m_wNPlusRtdTime;                    //N+1����rtdʱ��(s)
    u16 m_wNPlusRtdNum;                     //N+1����rtd����
    u8  m_byNPlusRollBack;                  //�Ƿ�֧�ֹ��ϻָ���Ĭ��֧��
    u8  m_byNPlusMode;                      //�Ƿ�֧��N+1����
    u8  m_byNPlusBackupMode;                //�Ƿ�N+1���ݹ���ģʽ
    u8  m_byReserved;                       //����
    
public:
    TNPlusInfo() : m_dwNPlusMcuIp(0),
                   m_wNPlusRtdTime(0),
                   m_wNPlusRtdNum(0),
                   m_byNPlusRollBack(0),
                   m_byNPlusMode(0),
                   m_byNPlusBackupMode(0),
                   m_byReserved(0){}
    
    void    SetIsNPlusMode(BOOL32 bNPlus) { m_byNPlusMode = bNPlus ? 1 : 0; }   //�Ƿ�֧��N+1����
    BOOL32  IsNPlusMode(void) const { return (1 == m_byNPlusMode ? TRUE : FALSE); }
    void    SetIsNPlusBackupMode(BOOL32 bBackupMode) { m_byNPlusBackupMode = bBackupMode ? 1 : 0; }
    BOOL32  IsNPlusBackupMode(void) const{ return (1 == m_byNPlusBackupMode ? TRUE : FALSE); } //�Ƿ�N+1���ݹ���ģʽ
    void    SetNPlusMcuIp(u32 dwIp) { m_dwNPlusMcuIp = htonl(dwIp); }   
    u32     GetNPlusMcuIp(void)const { return ntohl(m_dwNPlusMcuIp); } //N+1����mcu�ĵ�ַ(host order)
    void    SetNPlusRtdTime(u16 wTime) { m_wNPlusRtdTime = htons(wTime); }
    u16     GetNPlusRtdTime(void) const{ return ntohs(m_wNPlusRtdTime); }
    void    SetNPlusRtdNum(u16 wNum) { m_wNPlusRtdNum = htons(wNum); }
    u16     GetNPlusRtdNum(void) const{ return ntohs(m_wNPlusRtdNum); }
    void    SetIsNPlusRollBack(BOOL32 bRollBack) { m_byNPlusRollBack = bRollBack ? 1 : 0; }
    BOOL32  GetIsNPlusRollBack(void) const{ return (1 == m_byNPlusRollBack ? TRUE : FALSE); }

    void    Print() const
    {
        OspPrintf(TRUE, FALSE, "\nNPlusInfo:\nNPlusMode:%d, backupMode:%d, mcuIp:0x%x, rtd:%d, Num:%d\n",
                                IsNPlusMode(), IsNPlusBackupMode(), GetNPlusMcuIp(), 
                                GetNPlusRtdTime(), GetNPlusRtdNum());
    }
}
#ifndef WIN32
__attribute__( (packed) )
#endif
;

//mcu����������Ϣ
struct TMcuLocalCfgInfo
{    
protected:
    s8  m_szMcuAlias[MAXLEN_ALIAS];			// Mcu ����
    s8  m_szMcuE164[MAXLEN_E164];			// E164��
    s8  m_szMcuHardVer[MAXLEN_ALIAS];		// Mcu Ӳ���汾��   
    s8  m_szMcuSoftVer[MAXLEN_ALIAS];		// Mcu ����汾��
    
    u16 m_wDiscCheckTime;                   //�ն˶������ʱ��(s)
    u16 m_wDiscCheckTimes;                  //�ն˶���������
    u16 m_wPartlistRefreshTime;             //����ʱ�ն��б�ˢ��ʱ����(s)
    u16 m_wAudInfoRefreshTime;              //����ʱ��Ƶ��Ϣˢ��ʱ����(s)
    u16 m_wVidInfoRefreshTime;              //����ʱ��Ƶ��Ϣˢ��ʱ����(s)
    u8  m_bySaveBandWidth;                  //�Ƿ��ʡ����(0-����ʡ��1-��ʡ)
    u8  m_byReserved;                       //����

    TNPlusInfo m_tNPlusInfo;

public:
    TMcuLocalCfgInfo() : m_wDiscCheckTime(DEF_DISCCHECKTIME),
                         m_wDiscCheckTimes(DEF_DISCCHECKTIMES),
                         m_wPartlistRefreshTime(PARTLIST_REFRESHTIME),
                         m_wAudInfoRefreshTime(AUDINFO_REFRESHTIME),
                         m_wVidInfoRefreshTime(VIDINFO_REFRESHTIME),
                         m_byReserved(0)
    { 
        memset(m_szMcuAlias, 0, sizeof(m_szMcuAlias));
        memset(m_szMcuE164, 0, sizeof(m_szMcuE164));
        memset(m_szMcuHardVer, 0, sizeof(m_szMcuHardVer));
        memset(m_szMcuSoftVer, 0, sizeof(m_szMcuSoftVer));
    }
    BOOL32  IsNull(void)
    {
        TMcuLocalCfgInfo tInfo;
        return (0 == memcmp(this, &tInfo, sizeof(TMcuLocalCfgInfo)));
    }

    void    SetIsSaveBandWidth(u8 bySave) { m_bySaveBandWidth = (0 == bySave) ? 0 : 1; }
    u8      GetIsSaveBandWidth(void) const { return m_bySaveBandWidth; }
    void    SetDiscCheckTime(u16 wTime) { m_wDiscCheckTime = htons(wTime); }
    u16     GetDiscCheckTime(void) const { return ntohs(m_wDiscCheckTime); }
    void    SetDiscCheckTimes(u16 wTimes) { m_wDiscCheckTimes = htons(wTimes); }
    u16     GetDiscCheckTimes(void) const { return ntohs(m_wDiscCheckTimes); }
    void    SetPartListRefreshTime(u16 wTime) { m_wPartlistRefreshTime = htons(wTime); }
    u16     GetPartListRefreshTime(void) const { return ntohs(m_wPartlistRefreshTime); }
    void    SetAudInfoRefreshTime(u16 wTime) { m_wAudInfoRefreshTime = htons(wTime); }
    u16     GetAudInfoRefreshTime(void) const { return ntohs(m_wAudInfoRefreshTime); }
    void    SetVidInfoRefreshTime(u16 wTime) { m_wVidInfoRefreshTime = htons(wTime); }
    u16     GetVidInfoRefreshTime(void) const { return ntohs(m_wVidInfoRefreshTime); }

    void    SetNPlusInfo(TNPlusInfo &tInfo) { m_tNPlusInfo = tInfo; }
    TNPlusInfo GetNPlusInfo() const {return m_tNPlusInfo;}
    void    SetIsNPlusMode(BOOL32 bNPlus) { m_tNPlusInfo.SetIsNPlusMode( bNPlus ); }   //�Ƿ�֧��N+1����
    BOOL32  IsNPlusMode(void) const{ return m_tNPlusInfo.IsNPlusMode(); }
    void    SetIsNPlusBackupMode(BOOL32 bBackupMode) { m_tNPlusInfo.SetIsNPlusBackupMode(bBackupMode); }
    BOOL32  IsNPlusBackupMode(void) const{ return m_tNPlusInfo.IsNPlusBackupMode(); } //�Ƿ�N+1���ݹ���ģʽ
    void    SetNPlusMcuIp(u32 dwIp) { m_tNPlusInfo.SetNPlusMcuIp(dwIp); }   
    u32     GetNPlusMcuIp(void) const{ return m_tNPlusInfo.GetNPlusMcuIp(); } //N+1����mcu�ĵ�ַ(host order)
    void    SetNPlusRtdTime(u16 wTime) { m_tNPlusInfo.SetNPlusRtdTime(wTime); }
    u16     GetNPlusRtdTime(void) const{ return m_tNPlusInfo.GetNPlusRtdTime(); }
    void    SetNPlusRtdNum(u16 wNum) { m_tNPlusInfo.SetNPlusRtdNum(wNum); }
    u16     GetNPlusRtdNum(void) const{ return m_tNPlusInfo.GetNPlusRtdNum(); }
    void    SetIsNPlusRollBack(BOOL32 bRollBack) { m_tNPlusInfo.SetIsNPlusRollBack(bRollBack); }
    BOOL32  GetIsNPlusRollBack(void) const{ return m_tNPlusInfo.GetIsNPlusRollBack(); }
    
    void SetMcuAlias(LPCSTR lpszAlias)
    {
        if(NULL != lpszAlias)
        {
            strncpy(m_szMcuAlias, lpszAlias, sizeof(m_szMcuAlias));
            m_szMcuAlias[sizeof(m_szMcuAlias) - 1] = '\0';
        }        
    }
    const s8* GetMcuAlias(void) const{ return m_szMcuAlias; }

    void SetMcuE164(LPCSTR lpszE164)
    {
        if(NULL != lpszE164)
        {
            strncpy(m_szMcuE164, lpszE164, sizeof(m_szMcuE164));
            m_szMcuE164[sizeof(m_szMcuE164) - 1] = '\0';
        }        
    }
    const s8* GetMcuE164(void) const{ return m_szMcuE164; }

    void SetMcuHardVer(LPCSTR lpszHardVer)          //mcu �ڲ�ʹ��
    {
        if(NULL != lpszHardVer)
        {
            strncpy(m_szMcuHardVer, lpszHardVer, sizeof(m_szMcuHardVer));
            m_szMcuHardVer[sizeof(m_szMcuHardVer) - 1] = '\0';
        }        
    }
    const s8* GetMcuHardVer(void) const{ return m_szMcuHardVer; }

    void SetMcuSoftVer(LPCSTR lpszSoftVer)          //mcu �ڲ�ʹ��
    {
        if(NULL != lpszSoftVer)
        {
            strncpy(m_szMcuSoftVer, lpszSoftVer, sizeof(m_szMcuSoftVer));
            m_szMcuSoftVer[sizeof(m_szMcuSoftVer) - 1] = '\0';
        }        
    }
    const s8* GetMcuSoftVer(void) const{ return m_szMcuSoftVer; }

    void    Print(void) const
    {
        OspPrintf(TRUE, FALSE, "\nLocalInfo:\nMcuAlias:%s, E164:%s \nHardVer:%s \nSoftVer:%s \nIsSaveBW:%d DiscTime:%d, PartList:%d, Aud:%d, Vid:%d \nNPlusMode:%d, backupMode:%d, mcuIp:0x%x, rtd:%d, Num:%d\n",
                  GetMcuAlias(), GetMcuE164(), GetMcuHardVer(), GetMcuSoftVer(), 
                  GetIsSaveBandWidth(), GetDiscCheckTime(), GetPartListRefreshTime(),
                  GetAudInfoRefreshTime(), GetVidInfoRefreshTime(),
                  IsNPlusMode(), IsNPlusBackupMode(), GetNPlusMcuIp(), 
                  GetNPlusRtdTime(), GetNPlusRtdNum());
    }    
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// Trap ��Ϣ
struct TTrapCfgInfo
{
protected:
    u32  m_dwTrapIp;							// Ip    
    u16  m_wReadWritePort;						// ��д�˿�
    u16  m_wSendTrapPort;						// ��Trap�˿�
    s8   m_szReadCom[MAXLEN_TRAP_COMMUNITY];	// ����ͬ��
    s8   m_szWriteCom[MAXLEN_TRAP_COMMUNITY];	// д��ͬ��

public:
    TTrapCfgInfo(void) 
    { 
        memset(this, 0, sizeof(TTrapCfgInfo)); 
        SetReadWritePort(DEF_READWRITE_TRAPPORT);
        SetSendTrapPort(DEF_SEND_TRAPPORT);
    }

    void    SetTrapIp(u32 dwIP) { m_dwTrapIp = htonl(dwIP); }
    u32     GetTrapIp(void) { return ntohl(m_dwTrapIp); }
    void    SetReadWritePort(u16 wPort) { m_wReadWritePort = htons(wPort); }
    u16     GetReadWritePort(void)  { return ntohs(m_wReadWritePort); }
    void    SetSendTrapPort(u16 wPort) { m_wSendTrapPort = htons(wPort); }
    u16     GetSendTrapPort(void)  { return ntohs(m_wSendTrapPort); }

    void SetReadCom(LPCSTR lpszReadCom)          
    {
        if(NULL != lpszReadCom)
        {
            strncpy(m_szReadCom, lpszReadCom, sizeof(m_szReadCom));
            m_szReadCom[sizeof(m_szReadCom) - 1] = '\0';
        }        
    }
    const s8* GetReadCom(void) { return m_szReadCom; }

    void SetWriteCom(LPCSTR lpszWriteCom)          
    {
        if(NULL != lpszWriteCom)
        {
            strncpy(m_szWriteCom, lpszWriteCom, sizeof(m_szWriteCom));
            m_szWriteCom[sizeof(m_szWriteCom) - 1] = '\0';
        }        
    }
    const s8* GetWriteCom(void) { return m_szWriteCom; }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// ����������Ϣ 
struct TMcuNetCfgInfo
{	
protected:
    u32 m_dwGKIpAddr;                               // Gk ��ַ (��Ϊ0��ʾ��ע��gk)
    u32 m_dwRRQMtadpIpAddr;                         // ע��gk����Э��������ַ                      
    u32 m_dwMulticastIpAddr;                        // �鲥��ַ
    u16 m_wuMulticastPort;                          // �鲥�˿�
    u16 m_wRcvStartPort;                            // ������ʼ�˿�
    u16 m_w225245StartPort;                         // 245�˿�
    u16 m_wMaxMtNum;                                // mcu ����ն���
	u16 m_wMTUSize;									// MTU ��С, zgc, 2007-04-02
	u8	m_byMTUSetupMode;							// MTU����ģʽ, zgc, 2007-04-05
    u8  m_byUseMPCTransData;                        // �Ƿ�ʹ��Mpc������
    u8  m_byUseMPCStack;                            // �Ƿ�ʹ��Mpc����Э��ջ

	u8  m_byTrapListNum;                            // trap ����
	TTrapCfgInfo m_tTrapInfoList[MAXNUM_TRAP_LIST]; // trap����Ϣ
    u8  m_byGkCharge;                               // �Ƿ����GK�Ʒ�

public:
	TMcuNetCfgInfo(void) 
    { 
        memset(this, 0, sizeof(TMcuNetCfgInfo)); 
        SetMaxMtNum(MAXNUM_H225H245_MT);
    }
    BOOL32 IsNull(void)
    {
        TMcuNetCfgInfo tInfo;
        return (0 == memcmp(this, &tInfo, sizeof(TMcuNetCfgInfo)));
    }

    void SetGkIpAddr(u32 dwIpAddr) { m_dwGKIpAddr = htonl(dwIpAddr); }
    u32  GetGkIpAddr(void) { return ntohl(m_dwGKIpAddr); }
    void SetRRQMtadpIp(u32 dwIpAddr) { m_dwRRQMtadpIpAddr = htonl(dwIpAddr); }
    u32  GetRRQMtadpIp(void) { return ntohl(m_dwRRQMtadpIpAddr); }
    void SetMultiIpAddr(u32 dwIpAddr) { m_dwMulticastIpAddr = htonl(dwIpAddr); }
    u32  GetMultiIpAddr(void) { return ntohl(m_dwMulticastIpAddr); }
    void SetMultiPort(u16 wPort) { m_wuMulticastPort = htons(wPort); }
    u16  GetMultiPort(void) { return ntohs(m_wuMulticastPort); }
    void SetRcvStartPort(u16 wPort) { m_wRcvStartPort = htons(wPort); }
    u16  GetRcvStartPort(void) { return ntohs(m_wRcvStartPort); }
    void Set225245StartPort(u16 wPort) { m_w225245StartPort = htons(wPort); }
    u16  Get225245StartPort(void) { return ntohs(m_w225245StartPort); }
    void SetMaxMtNum(u16 wNum) { m_wMaxMtNum = htons(wNum); }
    u16  GetMaxMtNum(void) { return ntohs(m_wMaxMtNum); }
	void SetMTUSize(u16 wMTUSize) { m_wMTUSize = htons(wMTUSize); } // ����MTU��С, zgc, 2007-04-02
	u16  GetMTUSize(void) {return ntohs(m_wMTUSize); } // ���MTU��С, zgc, 2007-04-02
	void SetMTUSetupMode( u8 byMode ) { m_byMTUSetupMode = byMode; }
	u8	 GetMTUSetupMode( void ) { return m_byMTUSetupMode; }
    void SetIsUseMpcTransData(u8 byUse) { m_byUseMPCTransData = byUse; }
    u8   GetIsUseMpcTransData(void) { return m_byUseMPCTransData; }
    void SetIsUseMpcStack(u8 byUse) { m_byUseMPCStack = byUse; }
    u8   GetIsUseMpcStack(void) { return m_byUseMPCStack; }
    void   SetIsGKCharge(BOOL32 bCharge) { m_byGkCharge = bCharge ? 1 : 0;  }
    BOOL32 GetIsGKCharge(void) { return m_byGkCharge == 1 ? TRUE : FALSE;   }

    BOOL32 SetTrapList(TTrapCfgInfo *ptTrapInfo, u8 byNum)
    {
        if(NULL == ptTrapInfo || byNum > MAXNUM_TRAP_LIST)
            return FALSE;
        m_byTrapListNum = byNum;
        memcpy((void *)m_tTrapInfoList, (void *)ptTrapInfo, byNum*sizeof(TTrapCfgInfo));
        return TRUE;
    }
    BOOL32 GetTrapList(TTrapCfgInfo *ptTrapInfo, u8 &byNum)
    {
        if(NULL == ptTrapInfo)
            return FALSE;
        byNum = m_byTrapListNum;
        memcpy((void *)ptTrapInfo, (void *)m_tTrapInfoList, byNum*sizeof(TTrapCfgInfo));
        return TRUE;
    }
    
    void Print(void)
    {
        OspPrintf(TRUE, FALSE, "\nNetCfg:\nGKIp:0x%x, RRQMtadpIp:0x%x, MultiIp:0x%x, MultiPort:%d\nRcvPort:%d, 225Port:%d, MaxMtNum:%d, IsMpcTrans:%d, IsMpcStack:%d, MTU size:%d, MTU mode:%d \n",
                                GetGkIpAddr(), GetRRQMtadpIp(), GetMultiIpAddr(), GetMultiPort(), GetRcvStartPort(),
                                Get225245StartPort(), GetMaxMtNum(), GetIsUseMpcTransData(), GetIsUseMpcStack(), GetMTUSize(), GetMTUSetupMode() );
        OspPrintf(TRUE, FALSE, "traplist count: %d\n", m_byTrapListNum);
        for(u8 byTrap = 0; byTrap < m_byTrapListNum; byTrap++)
        {
            OspPrintf(TRUE, FALSE, "%d. IpAddr:0x%x, ReadCom:%s, WriteCom:%s, RWPort:%u, SendPort:%u\n", byTrap,
                                    m_tTrapInfoList[byTrap].GetTrapIp(), m_tTrapInfoList[byTrap].GetReadCom(), 
                                    m_tTrapInfoList[byTrap].GetWriteCom(), m_tTrapInfoList[byTrap].GetReadWritePort(), 
                                    m_tTrapInfoList[byTrap].GetSendTrapPort());
        }
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// Qos ��Ϣ
struct TMcuQosCfgInfo
{	
protected:
    u8  m_byQosType;					// Qos ����
    u8  m_byAudLevel;					// ��Ƶ�ȼ�
    u8  m_byVidLevel;					// ��Ƶ�ȼ�
    u8  m_byDataLevel;					// ���ݵȼ�
    u8  m_bySignalLevel;				// �źŵȼ�
    u8  m_byIpServiceType;				// IP��������
	
public:
    TMcuQosCfgInfo(void) { memset(this, 0, sizeof(TMcuQosCfgInfo)); }
    BOOL32  IsNull(void) const
    {
        TMcuQosCfgInfo tInfo;
        return (0 == memcmp(this, &tInfo, sizeof(TMcuQosCfgInfo)));
    }

    void    SetQosType(u8 byType) { m_byQosType = byType; }
    u8      GetQosType(void) const { return m_byQosType; }
    void    SetAudLevel(u8 byLevel) { m_byAudLevel = byLevel; }
    u8      GetAudLevel(void) const { return m_byAudLevel; }
    void    SetVidLevel(u8 byLevel) { m_byVidLevel = byLevel; }
    u8      GetVidLevel(void) const { return m_byVidLevel; }
    void    SetDataLevel(u8 byLevel) { m_byDataLevel = byLevel; }
    u8      GetDataLevel(void) const { return m_byDataLevel; }
    void    SetSignalLevel(u8 byLevel) { m_bySignalLevel = byLevel; }
    u8      GetSignalLevel(void) const { return m_bySignalLevel; }
    void    SetIpServiceType(u8 byType) { m_byIpServiceType = byType; }
    u8      GetIpServiceType(void) const { return m_byIpServiceType; }

    void    Print(void) const
    {
        OspPrintf(TRUE, FALSE, "QosCfg:  QosType:%d, Aud:%d, Vid:%d, Data:%d, Signal:%d, IpServciType:%d\n",
            GetQosType(), GetAudLevel(), GetVidLevel(), GetDataLevel(), 
            GetSignalLevel(), GetIpServiceType());
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// ��ͬ����Ϣ
struct TMcuNetSynCfgInfo
{	
protected:
    u8	m_byNetSynMode;			    	//��ͬ��ģʽ
    u8	m_byNetSynDTSlot;				//��ͬ��ʹ�õ�DT��� (0-14)
    u8	m_byNetSynE1Index;				//��ͬ��DT���ϵ�E1�� (0-7)
	
public:
    TMcuNetSynCfgInfo(void)   { memset(this, 0, sizeof(TMcuNetSynCfgInfo)); }
    BOOL32  IsNull(void)
    {
        TMcuNetSynCfgInfo tInfo;
        return (0 == memcmp(this, &tInfo, sizeof(TMcuNetSynCfgInfo)));
    }

    void    SetNetSynMode(u8 byMode) { m_byNetSynMode = byMode; }
    u8      GetNetSynMode(void) { return m_byNetSynMode; }
    void    SetNetSynDTSlot(u8 bySlot) { m_byNetSynDTSlot = bySlot; }
    u8      GetNetSynDTSlot(void) { return m_byNetSynDTSlot; }
    void    SetNetSynE1Index(u8 byIndex) { m_byNetSynE1Index = byIndex; }
    u8      GetNetSynE1Index(void) { return m_byNetSynE1Index; }

    void    Print(void)
    {
        OspPrintf(TRUE, FALSE, "\nNetSynCfg:\nSynMode:%d, SynDTSlot:%d, SynE1Index:%d\n",
            GetNetSynMode(), GetNetSynDTSlot(), GetNetSynE1Index());
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//���ֻ��������������Ϣ
struct TDCSCfgInfo
{
protected:
	u32	m_dwDcsEqpIp;					//���ֻ���������豸id

public:
    TDCSCfgInfo(void) : m_dwDcsEqpIp(0) {}
    BOOL32  IsNull(void)
    {
        TDCSCfgInfo tInfo;
        return (0 == memcmp(this, &tInfo, sizeof(TDCSCfgInfo)));
    }

    void    SetDcsEqpIp(u32 dwEqpIp) { m_dwDcsEqpIp = htonl(dwEqpIp); }
    u32      GetDcsEqpIp(void) { return ntohl(m_dwDcsEqpIp); }
    
    void    Print(void)
    {
        OspPrintf(TRUE, FALSE, "\nDcsEqpIp:0x%x\n", GetDcsEqpIp());
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TDscUpdateReqHead
{
	TDscUpdateReqHead()
	{
		memset( this, 0, sizeof(TDscUpdateReqHead) );
	}
	~TDscUpdateReqHead(){;}
public:
	s8 m_acFileName[MAXLEN_MCU_FILEPATH];	//�����ļ���
	u8  m_byMark;			//���һ֡��ǣ�0-�������һ֡��1-���һ֡
private:
	u32 m_dwFileSize;		//�ļ��ܳ���
	u32 m_dwFrmNum;			//�ļ���֡��
	u32 m_dwReqFrmSN;		//��ǰ������֡��
	u32 m_dwFrmSize;		//��ǰ�����ݰ�����
public:
	void SetFileSize(u32 dwFileSize) { m_dwFileSize = htonl(dwFileSize); }
	u32  GetFileSize(void) { return ntohl(m_dwFileSize); }
	void SetFrmNum(u32 dwFrmNum) { m_dwFrmNum = htonl(dwFrmNum); }
	u32  GetFrmNum(void) { return ntohl(m_dwFrmNum); }
	void SetReqFrmSN(u32 dwReqFrmSN) { m_dwReqFrmSN = htonl(dwReqFrmSN); } 
	u32  GetReqFrmSN(void) { return ntohl(m_dwReqFrmSN); }
	void SetFrmSize(u32 dwFrmSize) { m_dwFrmSize = htonl(dwFrmSize); }
	u32  GetFrmSize(void) { return ntohl(m_dwFrmSize); }

}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TDscUpdateRsp
{
	TDscUpdateRsp()
	{
		memset( this, 0, sizeof(TDscUpdateRsp) );
	}
	~TDscUpdateRsp(){;}
public:
	s8 m_acFileName[MAXLEN_MCU_FILEPATH];	//�����ļ���

private:
	u32 m_dwRspFrmSN;		//�������һ֡֡��

public:
	void SetRspFrmSN(u32 dwRspFrmSN) { m_dwRspFrmSN = htonl(dwRspFrmSN); }
	u32  GetRspFrmSN(void) { return ntohl(m_dwRspFrmSN); }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;



struct TMINIMCUNetParam
{
public:
    enum enNetworkType
    {
        enInvalid = 0,
            enWAN = 1,
            enLAN = 2
    };
protected:

	u32 m_dwIpAddr;		// ������
	u32 m_dwIpMask;		// ������
	u32 m_dwGatewayIp;  // ������
	s8  m_asServerAlias[MAXLEN_PWD]; // ��Ӫ�̱���
    u8  m_byNetwordType;    // �����ַ���ͣ�LAN or WAN    
public:
	TMINIMCUNetParam():m_dwIpAddr(0),
					   m_dwIpMask(0),
					   m_dwGatewayIp(0),
                       m_byNetwordType(enInvalid)
	{
		memset(	m_asServerAlias, 0, sizeof(m_asServerAlias) );
	}

public:
    // ����Ϊ������ַ
    void SetWanParam( u32 dwIp, u32 dwIpMask, u32 dwGW, LPCSTR lpszAlias )
    {
        m_byNetwordType = enWAN;
        m_dwIpAddr = htonl(dwIp);
        m_dwIpMask = htonl(dwIpMask); 
        m_dwGatewayIp = htonl(dwGW);

        if (NULL != lpszAlias)
        {
            strncpy(m_asServerAlias, lpszAlias, MAXLEN_PWD-1);
            m_asServerAlias[MAXLEN_PWD-1] = 0;
        }
        else
        {
            memset(	m_asServerAlias, 0, sizeof(m_asServerAlias) );
        }
    }

    // ����Ϊ��������ַ
    void SetLanParam( u32 dwIp, u32 dwMask, u32 dwGW )
    {
        m_byNetwordType = enLAN;
        m_dwIpAddr = htonl(dwIp);
        m_dwIpMask = htonl(dwMask);
        m_dwGatewayIp = htonl(dwGW);

        // ����������Ҫ����
        memset(	m_asServerAlias, 0, sizeof(m_asServerAlias) );
    }

    BOOL32 IsValid() const
    {
        if ( 0 == m_dwIpAddr || enInvalid == m_byNetwordType )
        {
            return FALSE;
        }
        return TRUE;
    }

    // ��ȡ��������
    u8   GetNetworkType() const
    {
        return m_byNetwordType;
    }

    BOOL IsWan() const
    {
        return (m_byNetwordType == enWAN);
    }
    BOOL IsLan() const
    {
        return (m_byNetwordType == enLAN);
    }

    // ��ȡ��ַ����
    u32  GetIpAddr(void) const { return ntohl(m_dwIpAddr); }
	u32  GetIpMask(void) const{ return ntohl(m_dwIpMask); }
    u32  GetGatewayIp(void) const{ return ntohl(m_dwGatewayIp); }

    // ��ȡ����
    const s8 * GetServerAlias(void) const{ return m_asServerAlias; }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TMINIMCUNetParamAll
{
private:
	u8 m_byParamNum;
	TMINIMCUNetParam m_atMINIMCUNetParam[ETH_IP_MAXNUM];

public:
	TMINIMCUNetParamAll()
	{
		m_byParamNum = 0;
		memset( m_atMINIMCUNetParam, 0, sizeof(m_atMINIMCUNetParam) );
	}
	BOOL32 IsValid() const
	{
		return ( m_byParamNum != 0 );
	}
	u8 GetNetParamNum(void) const
	{
		return m_byParamNum;
	}
	u8 GetLANParamNum(void) const
	{
        u8 byNum = 0;
		for ( u8 byLop = 0; byLop < m_byParamNum; byLop++ )
		{
			if ( m_atMINIMCUNetParam[byLop].IsLan() )
			{
				byNum++;
			}
		}
		return byNum;
	}
	BOOL32 AddOneNetParam( const TMINIMCUNetParam &tNetParam )
	{
		if ( !tNetParam.IsValid() )
		{
			return FALSE;
		}
		u8 byIdx = 0;
		u8 byArrayLen = sizeof(m_atMINIMCUNetParam)/sizeof(TMINIMCUNetParam);
		for ( byIdx = 0; byIdx < byArrayLen; byIdx++ )
		{
			if( !m_atMINIMCUNetParam[byIdx].IsValid() )
			{
				memcpy( m_atMINIMCUNetParam+byIdx, &tNetParam, sizeof(TMINIMCUNetParam) );
				break;
			}
		}
		if ( byIdx == byArrayLen )
		{
			return FALSE;
		}
		m_byParamNum ++;
		return TRUE;
	}
	BOOL32 GetNetParambyIdx ( u8 byIdx, TMINIMCUNetParam &tNetParam ) const
	{
		memset( &tNetParam, 0, sizeof(TMINIMCUNetParam) );
		if ( byIdx >= m_byParamNum )
		{
			return FALSE;
		}
		if ( !m_atMINIMCUNetParam[byIdx].IsValid() )
		{
			return FALSE;
		}
		memcpy( &tNetParam, &m_atMINIMCUNetParam[byIdx], sizeof(TMINIMCUNetParam) );
		return TRUE;
	}
	BOOL32 DelNetParamByIdx(u8 byIdx)
	{
        if (m_byParamNum == 0)
        {
            return FALSE;
        }
		if ( byIdx >= m_byParamNum )
		{
			return FALSE;
		}
		u8 byLop = 0;
		for ( byLop = byIdx+1; byLop < m_byParamNum; byLop++ )
		{
			memcpy( &m_atMINIMCUNetParam[byLop-1], &m_atMINIMCUNetParam[byLop], sizeof(TMINIMCUNetParam) );
		}
		memset( &m_atMINIMCUNetParam[byLop-1], 0, sizeof(TMINIMCUNetParam) );
		m_byParamNum--;
		return TRUE;
	}
	BOOL32 IsEqualTo( const TMINIMCUNetParamAll &tMINIMCUNetParamAll )
	{
		return ( 0 == memcmp( &tMINIMCUNetParamAll, this, sizeof(TMINIMCUNetParamAll) ) ) ? TRUE : FALSE;
	}
	void Clear(void)
	{
		memset( this, 0, sizeof(TMINIMCUNetParamAll) );
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//MCU8000B ����DSC����ģ��
struct T8000BDscMod
{
protected:
    u32 m_dwMcuInnerIp;          // DSC Ҫ���ӵ�MCU�ڲ�IP 
    u32 m_dwDscInnerIp;		     // DSC ���ڲ�IP
    u32 m_dwInnerIpMask;         // DSC �ڲ�IP����
    u16 m_wMcuListenPort;		 // DSC Ҫ���ӵ�MCU�˿�,һ����60000
	
	u8  m_byNetType;			 // MCU���ڵ���������
	u8  m_byLanMtProxyIpPos;	 // �����ն˴��������IP������λ�� 
	TMINIMCUNetParamAll m_tDscParamAll;	// ���е�ַ����DSC��IP��
	TMINIMCUNetParamAll m_tMcuParamAll;	// ������ӵ�ַ����MCU��0��IP��
	
    u8 m_byStartMp;
    u8 m_byStartMtAdp;
    u8 m_byStartGk;
    u8 m_byStartProxy;
    u8 m_byStartDcs;

public:
    T8000BDscMod():m_byStartMp(0),
                     m_byStartMtAdp(0),
                     m_byStartGk(0),
                     m_byStartProxy(0),
                     m_byStartDcs(0),
                     m_wMcuListenPort(MCU_LISTEN_PORT),
                     m_dwMcuInnerIp(0),
                     m_dwDscInnerIp(0),
                     m_dwInnerIpMask(0),
					 m_byNetType(NETTYPE_INVALID),
					 m_byLanMtProxyIpPos(0)
    {
		memset( &m_tDscParamAll, 0, sizeof(m_tDscParamAll) );
		memset( &m_tMcuParamAll, 0, sizeof(m_tMcuParamAll) );
	}
    
    void   SetMcuInnerIp(u32 dwIp) { m_dwMcuInnerIp = htonl(dwIp); }
    u32    GetMcuInnerIp() const { return ntohl(m_dwMcuInnerIp); }
    void   SetMcuPort(u16 wPort) { m_wMcuListenPort = htons(wPort); }
    u16    GetMcuPort() const { return ntohs(m_wMcuListenPort); }
    void   SetDscInnerIp(u32 dwIp) { m_dwDscInnerIp = htonl(dwIp); }
    u32    GetDscInnerIp() const { return ntohl(m_dwDscInnerIp); }
    void   SetInnerIpMask(u32 dwMask) { m_dwInnerIpMask = htonl(dwMask); }
    u32    GetInnerIpMask() const {return ntohl(m_dwInnerIpMask); }
	void   SetNetType(u8 byNetType) { m_byNetType = byNetType; }
	u8	   GetNetType(void) const { return m_byNetType; }
	void   SetLanMtProxyIpPos(u8 byLanMtProxyIpPos) { m_byLanMtProxyIpPos = byLanMtProxyIpPos; }
	u8	   GetLanMtProxyIpPos(void) const { return m_byLanMtProxyIpPos; }

	void SetCallAddrAll( TMINIMCUNetParamAll &tDscParamAll)
	{
		if ( tDscParamAll.IsValid() )
		{
			memcpy( &m_tDscParamAll, &tDscParamAll, sizeof(TMINIMCUNetParamAll) );
		}
	}
	void SetMcsAccessAddrAll( TMINIMCUNetParamAll &tMcuParamAll)
	{
		if ( tMcuParamAll.IsValid() )
		{
			memcpy( &m_tMcuParamAll, &tMcuParamAll, sizeof(TMINIMCUNetParamAll) );
		}
	}
	void GetCallAddrAll(TMINIMCUNetParamAll &tDscParamAll) const 
	{ 
		memcpy( &tDscParamAll, &m_tDscParamAll, sizeof(TMINIMCUNetParamAll) ); 
	}
	void GetMcsAccessAddrAll(TMINIMCUNetParamAll &tMcuParamAll) const 
	{ 
		memcpy( &tMcuParamAll, &m_tMcuParamAll, sizeof(TMINIMCUNetParamAll) ); 
	}
	u8 GetCallAddrNum(void) const 
    { 
        return m_tDscParamAll.GetNetParamNum(); 
    }
	u8 GetMcsAccessAddrNum(void) const 
    { 
        return m_tMcuParamAll.GetNetParamNum(); 
    }
    /*
    u8 GetLanCallAddrNum(void) const
    {
        return m_tDscParamAll.GetLANParamNum();
	}
	u8 GetLanMcsAccessAddrNum(void) const
	{
        return m_tMcuParamAll.GetLANParamNum();
	}
    */
   
    void   SetStartMp(BOOL32 bStart){ m_byStartMp = bStart ? 1 : 0;    }
    BOOL32 IsStartMp() const { return m_byStartMp == 1 ? TRUE : FALSE;    }
    void   SetStartMtAdp(BOOL32 bStart){ m_byStartMtAdp = bStart ? 1 : 0;    }
    BOOL32 IsStartMtAdp() const { return m_byStartMtAdp == 1 ? TRUE : FALSE;    }
    void   SetStartGk(BOOL32 bStart) { m_byStartGk = bStart ? 1 : 0; }
    BOOL32 IsStartGk() const { return m_byStartGk == 1 ? TRUE : FALSE; }
    void   SetStartProxy(BOOL32 bStart) { m_byStartProxy = bStart ? 1 : 0; }
    BOOL32 IsStartProxy() const { return m_byStartProxy == 1 ? TRUE : FALSE; }
    void   SetStartDcs(BOOL32 bStart) { m_byStartDcs = bStart ? 1 : 0; }
    BOOL32 IsStartDcs() const { return m_byStartDcs == 1 ? TRUE : FALSE; }

    void   Print() const
    {
        u8 byLop = 0;
        OspPrintf( TRUE, FALSE, "T8000BDscMod: DscInnerIp: 0x%x, McuInnerIp: 0x%x:%d, InnerMask: 0x%x. Module: Mp.%d, MtAdp.%d, GK.%d, Proxy.%d, Dcs.%d\n", 
            m_dwDscInnerIp, m_dwMcuInnerIp, m_wMcuListenPort, m_dwInnerIpMask,
            m_byStartMp, m_byStartMtAdp, m_byStartGk, m_byStartProxy, m_byStartDcs);
		OspPrintf( TRUE, FALSE, "Net Type: ");
		switch( m_byNetType )
		{
		case NETTYPE_INVALID:
			OspPrintf(TRUE, FALSE, "INVALID\n");
			break;
		case NETTYPE_LAN:
			OspPrintf(TRUE, FALSE, "LAN\n");
			break;
		case NETTYPE_WAN:
			OspPrintf(TRUE, FALSE, "WAN\n");
			break;
		case NETTYPE_MIXING_ALLPROXY:
			printf( "MIXING_ALLPROXY\n");
			break;
		case NETTYPE_MIXING_NOTALLPROXY:
			printf( "MIXING_NOTALLPROXY\n" );
			break;
		default:
			break;
		}
		OspPrintf( TRUE, FALSE, "LanMtProxyIpPos: %d\n", m_byLanMtProxyIpPos );
		OspPrintf( TRUE, FALSE, "T8000BDscMod: DSC NetParam--\n");
		TMINIMCUNetParam tTemp;
		for ( byLop = 0; byLop < m_tDscParamAll.GetNetParamNum(); byLop++ )
		{
			if ( m_tDscParamAll.GetNetParambyIdx(byLop, tTemp) )
			{
				if ( tTemp.IsValid() )
				{
					OspPrintf(TRUE, FALSE, "NetType:%s, Ip: 0x%x\tIpMask: 0x%x\tGateway: 0x%x\tServerAlias: %s\n",
                        tTemp.IsLan() ? "LAN" : "WAN",
						tTemp.GetIpAddr(), tTemp.GetIpMask(),
						tTemp.GetGatewayIp(), tTemp.GetServerAlias() );
				}
			}
		}
		OspPrintf( TRUE, FALSE, "T8000BDscMod: MCU NetParam--\n");
		for ( byLop = 0; byLop < ETH_IP_MAXNUM; byLop++ )
		{
			if ( m_tMcuParamAll.GetNetParambyIdx(byLop, tTemp) )
			{
				if ( tTemp.IsValid() )
				{
					OspPrintf(TRUE, FALSE, "NetType:%s, Ip: 0x%x\tIpMask: 0x%x\tGateway: 0x%x\tServerAlias: %s\n",
                        tTemp.IsLan() ? "LAN" : "WAN",
						tTemp.GetIpAddr(), tTemp.GetIpMask(),
						tTemp.GetGatewayIp(), tTemp.GetServerAlias() );
				}
			}
		}
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//Log info
struct TLoginInfo
{
public:
	s8  m_achUser[MAXLEN_PWD+1];//�û���
	s8  m_achPwd[MAXLEN_PWD+1]; //�û�����

public:
	TLoginInfo() { memset( this, 0, sizeof(TLoginInfo) ); }

	void  SetUser( LPCSTR lpszUser )
	{
		memset(m_achUser, 0, sizeof(m_achUser));
		if (NULL != lpszUser)
		{
			strncpy(m_achUser, lpszUser, sizeof(m_achUser));
			m_achUser[sizeof(m_achUser)-1] = '\0';
		}
	}

	LPCSTR GetUser( void ) const{ return m_achUser; }

	BOOL IsEqualUser( LPCSTR lpszUser ) const
	{
		s8 achBuf[MAXLEN_PWD+1] = {0};
		strncpy( achBuf, lpszUser, sizeof( achBuf ) );
		achBuf[sizeof(achBuf)-1] = '\0';
		
		if(0 == strncmp(achBuf, lpszUser, MAXLEN_PWD))
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}

	void SetPwd( LPCSTR lpszPwd )
	{
		memset(m_achPwd, 0, sizeof(m_achPwd));
		if (NULL != lpszPwd)
		{
			strncpy(m_achPwd, lpszPwd, sizeof(m_achPwd));
			m_achPwd[sizeof(m_achPwd)-1] = '\0';
            // �򵥼��ܡ���GetPwd֮ǰҪ�ֶ�����
            EncPwd();
		}
	}

	BOOL32 GetPwd( s8* pchPwd, u8 byLength )
	{
		if ( byLength < strlen(m_achPwd)+1 )
		{
			return FALSE;
		}
		DecPwd();
		strncpy( pchPwd, m_achPwd, byLength );
		pchPwd[byLength-1] = '\0';
		EncPwd();
		return TRUE; 
	}
        
    void DecPwd()
    {
        EncPwd();
    }

	void Print(void)
	{
		OspPrintf( TRUE, FALSE, "Username = %s\n", GetUser() );
		s8 achPwd[MAXLEN_PWD+1];
		memset(achPwd, 0, sizeof(achPwd));
		GetPwd(achPwd, sizeof(achPwd));
		OspPrintf( TRUE, FALSE, "Password = %s\n", achPwd );
	}

private:
    void EncPwd()
    {
        for (u8 byLoop=0; byLoop<strlen(m_achPwd); byLoop++)
        {
            m_achPwd[byLoop] ^= 0x5a;
        }
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//mcu general config info
struct TMcuGeneralCfg
{
    u8                  m_byVmpStyleNum;
    TVmpStyleCfgInfo    m_atVmpStyle[MAX_VMPSTYLE_NUM];
    TMcuLocalCfgInfo    m_tLocal;
    TMcuNetCfgInfo      m_tNet;
    TMcuQosCfgInfo      m_tQos;
    TMcuNetSynCfgInfo   m_tNetSyn;
    TDCSCfgInfo         m_tDcs;
    T8000BDscMod        m_tDscInfo;
	TLoginInfo			m_tLoginInfo;

public:
    void Print(void)
    {
        OspPrintf(TRUE, FALSE, "mcu generalcfg info:\n");
        for(u8 byIndex = 0; byIndex < m_byVmpStyleNum; byIndex++)
        {
            m_atVmpStyle[byIndex].Print();
        }        
        m_tLocal.Print();
        m_tNet.Print();
        m_tQos.Print();
        m_tNetSyn.Print();
        m_tDcs.Print();
        m_tDscInfo.Print();
		m_tLoginInfo.Print();
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//��ַ�����ݽṹ����
//size: 143 byte, �����Ӵ˽ṹ������ע�����ÿ����Ϣ����Ŀ����(ADDRENTRYNUM_PERPKT)
struct TMcuAddrEntry
{
protected:
    u32     m_dwEntryIdx;                                   // ��Ŀ����
    s8	    m_szEntryName[MAXLEN_ADDR_ENTRYNAME+1];		    // ��Ŀ����
    s8	    m_szMtAlias[MAXLEN_ADDR_323ALIAS+1];	        // ���б���
    u32	    m_dwMtIpAddr;							        // IP��ַ(������)
    s8	    m_szMtE164[MAXLEN_ADDR_E164NUM+1];	    	    // ���к���
    u8      m_byMtProtocolType;                             // 0:H323�ն�; ��0:H320�ն�
    s8      m_szH320Id[MAXLEN_ADDR_320ID+1];                // H320ID
    u16	    m_wCallRate;							        // ��������

public:
    TMcuAddrEntry( void ) { memset(this, 0, sizeof(TMcuAddrEntry)); }
    
    void SetEntryIdx(u32 dwIndex) { m_dwEntryIdx = htonl(dwIndex); } 
    u32  GetEntryIdx( void ) { return ntohl(m_dwEntryIdx); }

    void SetEntryName(LPCSTR lpszEntryName)          
    {
        if(NULL != lpszEntryName)
        {
            strncpy(m_szEntryName, lpszEntryName, sizeof(m_szEntryName));
            m_szEntryName[sizeof(m_szEntryName) - 1] = '\0';
        }        
    }
    LPCSTR GetEntryName(void) { return m_szEntryName; }

    void SetMtAlias(LPCSTR lpszMtAlias)          
    {
        if(NULL != lpszMtAlias)
        {
            strncpy(m_szMtAlias, lpszMtAlias, sizeof(m_szMtAlias));
            m_szMtAlias[sizeof(m_szMtAlias) - 1] = '\0';
        }        
    }
    LPCSTR GetMtAlias(void) { return m_szMtAlias; }

    void SetMtIpAddr(u32 dwIp) { m_dwMtIpAddr = htonl(dwIp); }
    u32  GetMtIpAddr( void ) { return ntohl(m_dwMtIpAddr); }

    void SetMtE164(LPCSTR lpszMtE164)
    {
        if(NULL != lpszMtE164)
        {
            strncpy(m_szMtE164, lpszMtE164, sizeof(m_szMtE164));
            m_szMtE164[sizeof(m_szMtE164) - 1] = '\0';
        }
    }
    LPCSTR GetMtE164( void ) { return m_szMtE164; }

    void SetMtProtocolType(u8 byType) { m_byMtProtocolType = byType; }
    u8  GetMtProtocolType( void ) { return m_byMtProtocolType; }

    void SetH320Id(LPCSTR lpszH320Id)
    {
        if(NULL != lpszH320Id)
        {
            strncpy(m_szH320Id, lpszH320Id, sizeof(m_szH320Id));
            m_szH320Id[sizeof(m_szH320Id) - 1] = '\0';
        }
    }
    LPCSTR GetH320Id( void ) { return m_szH320Id; }

    void SetCallRate(u16 wCallRate) { m_wCallRate = htons(wCallRate); }
    u16  GetCallRate( void ) { return ntohs(m_wCallRate); }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//size: 809 byte, �����Ӵ˽ṹ������ע�����ÿ����Ϣ����Ŀ�����(ADDRGROUPNUM_PERPKT)
struct TMcuAddrGroup
{
protected:
    u32 m_dwEntryIdx;								// ��Ŀ����
    u32 m_dwEntryNum;							    // ����ն˸���
    u32 m_adwEntryIdx[MAXNUM_CONF_MT];	            // ����ն�����
    s8  m_szGroupName[MAXLEN_ADDR_ENTRYNAME + 1];	// ����     

public:
    TMcuAddrGroup( void ) { memset(this, 0, sizeof(TMcuAddrGroup)); }

    void SetEntryIdx(u32 dwIndex) { m_dwEntryIdx = htonl(dwIndex); } 
    u32  GetEntryIdx( void ) { return ntohl(m_dwEntryIdx); }

    void SetEntryNum(u32 dwEntryNum) { m_dwEntryNum = htonl(dwEntryNum); }
    u32  GetEntryNum( void ) { return ntohl(m_dwEntryNum); }

    void GetAllEntryIdx(u32 *padwEntryIdx, u32 &dwNum)
    {
        if(NULL == padwEntryIdx) return;

        if(dwNum > GetEntryNum()) 
        {
            dwNum = GetEntryNum();
        }
        
        if(dwNum > MAXNUM_CONF_MT)
        {
            dwNum = MAXNUM_CONF_MT;
        }
        
        for(u32 dwIdx=0; dwIdx < dwNum; dwIdx++)
        {
            padwEntryIdx[dwIdx] = ntohl(m_adwEntryIdx[dwIdx]);
        }        
    }
    void SetAllEntryIdx(u32 *padwEntryIdx, u32 dwNum)
    {
        if(NULL == padwEntryIdx) return;

        if(dwNum > MAXNUM_CONF_MT)
        {
            dwNum = MAXNUM_CONF_MT;
        }

        for(u32 dwIdx=0; dwIdx < dwNum; dwIdx++)
        {
            m_adwEntryIdx[dwIdx] = htonl(padwEntryIdx[dwIdx]);
        }

        m_dwEntryNum = htonl(dwNum);
    }
    
    void SetGroupName(LPCSTR lpszName)
    {
        if(NULL != lpszName)
        {
            strncpy(m_szGroupName, lpszName, sizeof(m_szGroupName));
            m_szGroupName[sizeof(m_szGroupName)-1] = '\0';
        }
    }
    LPCSTR GetGroupName( void ) { return m_szGroupName; }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//mcu����״̬֪ͨ
struct TMcuMsStatus
{
protected:
    u8  m_byIsMsSwitchOK;

public:
    TMcuMsStatus(void) : m_byIsMsSwitchOK(0) {}

    void    SetMsSwitchOK(BOOL32 bSwitchOK) { m_byIsMsSwitchOK = bSwitchOK ? 1:0; }
    BOOL32  IsMsSwitchOK(void) { return (1==m_byIsMsSwitchOK); }

}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//MCU����Ʒѽṹ len: 146
struct TConfChargeInfo
{
protected:
    s8  m_achGKUsrName[MAX_LEN_GK_USRNAME]; //GK�û���
    s8  m_achGKPwd[MAX_LEN_GK_PWD];         //GK����

    s8  m_achConfName[MAXLEN_CONFNAME+1];   //��������
    s8  m_achConfE164[MAXLEN_E164+1];       //����E164��
    
    u16 m_wBitRate;                         //��������
    u16 m_wTerNum;                          //�ն���
    u8  m_byMixerNum;                       //������
    u8  m_byVMPNum;                         //�໭����
    u8  m_byBASNum;                         //����������(��������ʽ����)
    u8  m_byUseCasd;                        //�Ƿ�ʹ�ü���
    u8  m_byUseEncrypt;                     //�Ƿ�ʹ�ü���
    u8  m_byUseDualVideo;                   //�Ƿ�ʹ��˫��
    u8  m_byUseDataConf;                    //�Ƿ��ٿ����ݻ���
    u8  m_byUseStreamBroadCast;             //�Ƿ�ʹ����ý���鲥
public:
    TConfChargeInfo() :m_wBitRate(0),
                       m_wTerNum(0),
                       m_byMixerNum(0),
                       m_byVMPNum(0),
                       m_byBASNum(0),
                       m_byUseCasd(0),
                       m_byUseEncrypt(0),
                       m_byUseDualVideo(0),
                       m_byUseDataConf(0),
                       m_byUseStreamBroadCast(0)
    {
        memset( &m_achGKUsrName, 0, sizeof(m_achGKUsrName) );
        memset( &m_achGKPwd,    0, sizeof(m_achGKPwd) );
        memset( &m_achConfName, 0, sizeof(m_achConfName) );
        memset( &m_achConfE164, 0, sizeof(m_achConfE164) );
    }
    void SetBitRate(u16 wBitRate) { m_wBitRate = htons(wBitRate);    }
    u16  GetBitRate(void) const { return ntohs(m_wBitRate);    }
    void SetTerNum(u16 wNum) { m_wTerNum = htons(wNum);    }
    u16  GetTerNum(void) const { return ntohs(m_wTerNum);    }
    void SetMixerNum(u8 byNum){ m_byMixerNum = byNum;    }
    u8   GetMixerNum(void) const { return m_byMixerNum;    }
    void SetVMPNum(u8 byVMPNum) { m_byVMPNum = byVMPNum;    }
    u8   GetVMPNum(void) const { return m_byVMPNum;    }
    void SetBasNum(u8 byBasNum) { m_byBASNum = byBasNum; }
    u8   GetBasNum(void) const { return m_byBASNum;    }
    void   SetIsUseCascade(BOOL32 bUse) { m_byUseCasd = bUse ? 1 : 0;    }
    BOOL32 GetIsUseCascade(void) const { return m_byUseCasd == 1 ? TRUE : FALSE;    }
    void   SetIsUseEncrypt(BOOL32 bUse) { m_byUseEncrypt = bUse ? 1 : 0;    }
    BOOL32 GetIsUseEncrypt(void) const { return m_byUseEncrypt == 1 ? TRUE : FALSE;    }
    void   SetIsUseDualVideo(BOOL32 bUse) { m_byUseDualVideo = bUse ? 1 : 0;    }
    BOOL32 GetIsUseDualVideo(void) const { return m_byUseDualVideo == 1 ? TRUE : FALSE;    }
    void   SetIsUseDataConf(BOOL32 bUse) { m_byUseDataConf = bUse ? 1 : 0;    }
    BOOL32 GetIsUseDataConf(void) const { return m_byUseDataConf == 1 ? TRUE : FALSE;    }
    void   SetIsUseStreamBroadCast(BOOL32 bUse) { m_byUseStreamBroadCast = bUse ? 1 : 0;    }
    BOOL32 GetIsUseStreamBroadCast(void) const { return m_byUseStreamBroadCast == 1 ? TRUE : FALSE;    }
    void SetGKUsrName(LPCSTR pszUsrName)
    {
        if ( pszUsrName != NULL )
        {
            u16 wLen = min(strlen(pszUsrName), MAX_LEN_GK_USRNAME-1);
            memcpy( m_achGKUsrName, pszUsrName, wLen );
            m_achGKUsrName[wLen] = '\0';
        }
        return;
    }
    LPCSTR GetGKUsrName(void) { return m_achGKUsrName;    }

    void SetGKPwd(LPCSTR pszPwd)
    {
        if ( pszPwd != NULL )
        {
            u16 wLen = min(strlen(pszPwd), MAX_LEN_GK_PWD-1);
            strncpy( m_achGKPwd, pszPwd, wLen );
            m_achGKPwd[wLen] = '\0';
        }
        return;
    }
    LPCSTR GetGKPwd(void) { return m_achGKPwd;    }
    
    void SetConfName(LPCSTR pszConfName)
    {
        if ( pszConfName != NULL )
        {
            u16 wLen = min(strlen(pszConfName), MAXLEN_CONFNAME);
            strncpy( m_achConfName, pszConfName, wLen );
            m_achConfName[wLen] = '\0';
        }
        return;
    }
    LPCSTR GetConfName(void) { return m_achConfName;    }

    void SetConfE164(LPCSTR pszConfE164)
    {
        if ( pszConfE164 != NULL )
        {
            u16 wLen = min(strlen(pszConfE164), MAXLEN_E164);
            strncpy( m_achConfE164, pszConfE164, wLen );
            m_achConfE164[wLen] = '\0';
        }
        return;
    }
    LPCSTR GetConfE164(void) { return m_achConfE164;    }
    
    BOOL32 IsNull(void) const { return (strlen(m_achGKUsrName) == 0 ? TRUE : FALSE); }

}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TMpuChn
{
public:
    TMpuChn():m_dwIpAddr(0),
              m_byChnId(0)
    {
    }
    void   SetIpAddr(u32 dwIp) { m_dwIpAddr = htonl(dwIp); }
    u32    GetIpAddr(void) { return ntohl(m_dwIpAddr);  }
    void   SetChnId(u8 byId) { m_byChnId = byId; }
    u8     GetChnId(void) { return m_byChnId; }
    BOOL32 IsNull()    {    return 0 == m_dwIpAddr;    }
private:
    u32 m_dwIpAddr;
    u8 m_byChnId;
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//mcu��mauʹ��״̬
struct TMcuHdBasStatus
{
    TMcuHdBasStatus()
    {
        Clear();
    }

    //�����
    BOOL32 GetConfMau(const CConfId &cConfId, 
                      u8 &byMauNum, u32 *pdwMau, u8 &byH263pMauNum, u32 *pdwH263pMau)
    {
        u8 byPos = 0xff;
        u8 byIdx = 0;

        if (!IsConfExist(cConfId, byPos))
        {
            return FALSE;
        }
        for(byIdx = 0; byIdx < MAXNUM_CONF_MAU; byIdx ++)
        {
            if (0 != m_aadwUsedMau[byPos][byIdx])
            {
                byMauNum++;
            }
        }

        if (!IsConfExist(cConfId, byPos))
        {
            return FALSE;
        }
        for(byIdx = 0; byIdx < MAXNUM_CONF_MAU; byIdx ++)
        {
            if (0 != m_aadwUsedH263pMau[byPos][byIdx])
            {
                byH263pMauNum++;
            }
        }
        return TRUE;
    }
    //�����
    BOOL32 GetConfMpuChn(const CConfId &cConfId,
                         u8 &byChnNum, TMpuChn *ptMpuChn)
    {
        u8 byPos = 0xff;
        u8 byIdx = 0;
        
        if (!IsConfExist(cConfId, byPos))
        {
            return FALSE;
        }
        for(byIdx = 0; byIdx < MAXNUM_CONF_MPU; byIdx ++)
        {
            if (!m_aatUsedMpuChn[byPos][byIdx].IsNull())
            {
                byChnNum++;
            }
        }
        memcpy(ptMpuChn, m_aatUsedMpuChn, byChnNum*sizeof(TMpuChn));
        return TRUE;
    }

    //�����
    BOOL32 GetIdleMau(u8 &byMauNum, u32 *pdwMau, u8 &byH263pMauNum, u32 *pdwH263pMau)
    {
        u8 byIdx = 0;

        for(byIdx = 0; byIdx < MAXNUM_PERIEQP; byIdx ++)
        {
            if (0 != m_adwIdleMau[byIdx])
            {
                byMauNum++;
            }
        }
        memcpy(pdwMau, &m_adwIdleMau, byMauNum);

        for(byIdx = 0; byIdx < MAXNUM_PERIEQP; byIdx ++)
        {
            if (0 != m_adwIdleH263pMau[byIdx])
            {
                byH263pMauNum++;
            }
        }
        memcpy(pdwMau, &m_adwIdleH263pMau, byH263pMauNum);

        return TRUE;
    }

    //�����(ע��: MPU�Ŀ�����Դ��ͨ��Ϊ��λ����)
    BOOL32 GetIdleMpuChn(u8 &byMpuChnNum, TMpuChn *ptMpuChn)
    {
        u8 byIdx = 0;
        
        for(byIdx = 0; byIdx < MAXNUM_PERIEQP*MAXNUM_MPU_CHN; byIdx ++)
        {
            if (!m_atIdleMpuChn[byIdx].IsNull())
            {
                byMpuChnNum++;
            }
        }
        memcpy(ptMpuChn, &m_atIdleMpuChn, byMpuChnNum);

        return TRUE;
    }

    //����ã�����ʧ�ܡ�ģ�徯��/֪ͨʱ �����������ȡ��
    void GetCurMauNeeded(u8 &byMauNum, u8 &byH263pMauNum)
    {
        byMauNum = m_byCurMau;
        byH263pMauNum = m_byCurH263pMau;
        return;
    }

    //����ã�����ʧ�ܡ�ģ�徯��/֪ͨʱ �����������ȡ��
    //ע��: mpu��Դ����̶���ͨ��Ϊ��λ�����������û����԰忨Ϊ��λ����:4 chn/mpu
    void GetCurMpuChnNeeded(u8 &byChnNum)
    {
        byChnNum = m_byCurMpuChn;
        return;
    }

    //���½ӿ�MCUʹ��

    void SetCurMauNeeded(u8 byMauNum, u8 byH263pMauNum)
    {
        m_byCurMau = byMauNum;
        m_byCurH263pMau = byH263pMauNum;
        return;
    }

    void SetCurMpuChnNeeded(u8 byMpuChn)
    {
        m_byCurMpuChn = byMpuChn;
        return;
    }

    void SetConfMau(const CConfId &cConfId, u32 dwMauIp, BOOL32 bH263p)
    {
        u8 byIdx = 0;
        u8 byPos = 0xff;
        u8 byFstIdlePos = 0xff;
        BOOL32 bExist = FALSE;
        BOOL32 bSet = FALSE;

        if (!bH263p)
        {
            if (IsConfExist(cConfId, byPos))
            {
                byFstIdlePos = 0xff;
                bExist = FALSE;
                for(; byIdx < MAXNUM_CONF_MAU; byIdx++)
                {
                    if (0 == m_aadwUsedMau[byPos][byIdx])
                    {
                        byFstIdlePos = byFstIdlePos == 0xff ? byIdx : byFstIdlePos;
                    }
                    if (dwMauIp == m_aadwUsedMau[byPos][byIdx])
                    {
                        bExist = TRUE;
                        break;
                    }
                }
                if (!bExist)
                {
                    if (0xff == byFstIdlePos)
                    {
                        OspPrintf(TRUE, FALSE, "[THdBasStatus][SetConfMau] no pos in ConfPos.%d\n", byPos);
                        return;
                    }
                    m_aadwUsedMau[byPos][byFstIdlePos] = dwMauIp;
                }
                return;
            }
            
            bSet = FALSE;
            for (byIdx = 0; byIdx < MAXNUM_ONGO_CONF; byIdx ++)
            {
                if (m_acConfId[byIdx].IsNull())
                {
                    m_acConfId[byIdx] = cConfId;
                    m_aadwUsedMau[byIdx][0] = dwMauIp;
                    bSet = TRUE;
                }
            }
            if (!bSet)
            {
                OspPrintf(TRUE, FALSE, "[THdBasStatus][SetConfMau] no pos for new conf!\n");
            }
            return;
        }

        //H263p���
        if (IsConfExist(cConfId, byPos))
        {
            byFstIdlePos = 0xff;
            bExist = FALSE;
            for(; byIdx < MAXNUM_CONF_MAU; byIdx++)
            {
                if (0 == m_aadwUsedH263pMau[byPos][byIdx])
                {
                    byFstIdlePos = byFstIdlePos == 0xff ? byIdx : byFstIdlePos;
                }
                if (dwMauIp == m_aadwUsedH263pMau[byPos][byIdx])
                {
                    bExist = TRUE;
                    break;
                }
            }
            if (!bExist)
            {
                if (0xff == byFstIdlePos)
                {
                    OspPrintf(TRUE, FALSE, "[TMcuHdBasStatus][SetConfMau] no pos in ConfPos.%d(h263p)\n", byPos);
                    return;
                }
                m_aadwUsedH263pMau[byPos][byFstIdlePos] = dwMauIp;
            }
            return;
        }
        
        bSet = FALSE;
        for (byIdx = 0; byIdx < MAXNUM_ONGO_CONF; byIdx ++)
        {
            if (m_acConfId[byIdx].IsNull())
            {
                m_acConfId[byIdx] = cConfId;
                m_aadwUsedH263pMau[byIdx][0] = dwMauIp;
                bSet = TRUE;
            }
        }
        if (!bSet)
        {
            OspPrintf(TRUE, FALSE, "[TMcuHdBasStatus][SetConfMau] no pos for new conf(h263p)!\n");
        }
        return;
    }

    void SetConfMpuChn(const CConfId &cConfId, u32 dwMpuIp, u8 byChnId)
    {
        u8 byIdx = 0;
        u8 byPos = 0xff;
        u8 byFstIdlePos = 0xff;
        BOOL32 bExist = FALSE;

        if (IsConfExist(cConfId, byPos))
        {
            byFstIdlePos = 0xff;
            bExist = FALSE;
            for(; byIdx < MAXNUM_CONF_MPU; byIdx++)
            {
                if (m_aatUsedMpuChn[byPos][byIdx].IsNull())
                {
                    byFstIdlePos = byFstIdlePos == 0xff ? byIdx : byFstIdlePos;
                }
                if (dwMpuIp == m_aatUsedMpuChn[byPos][byIdx].GetIpAddr() &&
                    byChnId == m_aatUsedMpuChn[byPos][byIdx].GetChnId())
                {
                    bExist = TRUE;
                    break;
                }
            }
            if (!bExist)
            {
                if (0xff == byFstIdlePos)
                {
                    OspPrintf(TRUE, FALSE, "[TMcuHdBasStatus][SetConfMpuChn] no pos in ConfPos.%d\n", byPos);
                    return;
                }
                m_aatUsedMpuChn[byPos][byFstIdlePos].SetIpAddr(dwMpuIp);
                m_aatUsedMpuChn[byPos][byFstIdlePos].SetChnId(byChnId);
            }
            return;
        }

        BOOL32 bSet = FALSE;
        for (byIdx = 0; byIdx < MAXNUM_ONGO_CONF; byIdx ++)
        {
            if (m_acConfId[byIdx].IsNull())
            {
                m_acConfId[byIdx] = cConfId;
                m_aatUsedMpuChn[byIdx][0].SetIpAddr(dwMpuIp);
                m_aatUsedMpuChn[byIdx][0].SetChnId(byChnId);
                bSet = TRUE;
            }
        }
        if (!bSet)
        {
            OspPrintf(TRUE, FALSE, "[TMcuHdBasStatus][SetConfMpuChn] no pos for new conf!\n");
        }
        return;
    }

    void SetIdleMau(u32 dwMauIp, BOOL32 bH263p)
    {
        u8 byFstIdlePos = 0xff;
        BOOL32 bExist = FALSE;
        u8 byIdx = 0;
        if (!bH263p)
        {
            for(byIdx = 0; byIdx < MAXNUM_PERIEQP; byIdx++)
            {
                if (0 == m_adwIdleMau[byIdx])
                {
                    byFstIdlePos = byFstIdlePos == 0xff ? byIdx : byFstIdlePos;
                }
                if (dwMauIp == m_adwIdleMau[byIdx])
                {
                    bExist = TRUE;
                    break;
                }
            }
            if (!bExist)
            {
                if (0xff == byFstIdlePos)
                {
                    OspPrintf(TRUE, FALSE, "[TMcuHdBasStatus][SetIdleMau] no pos for new mau!\n");
                    return;
                }
                m_adwIdleMau[byFstIdlePos] = dwMauIp;
            }
            return;
        }
        
        byFstIdlePos = 0xff;
        bExist = FALSE;
        for(byIdx = 0; byIdx < MAXNUM_PERIEQP; byIdx++)
        {
            if (0 == m_adwIdleH263pMau[byIdx])
            {
                byFstIdlePos = byFstIdlePos == 0xff ? byIdx : byFstIdlePos;
            }
            if (dwMauIp == m_adwIdleH263pMau[byIdx])
            {
                bExist = TRUE;
                break;
            }
        }
        if (!bExist)
        {
            if (0xff == byFstIdlePos)
            {
                OspPrintf(TRUE, FALSE, "[TMcuHdBasStatus][SetIdleMau] no pos for new mau(H263p)!\n");
                return;
            }
            m_adwIdleH263pMau[byFstIdlePos] = dwMauIp;
        }
        return;
    }

    void SetIdleMpuChn(u32 dwMpuIp, u8 byChnId)
    {
        u8 byFstIdlePos = 0xff;
        BOOL32 bExist = FALSE;
        u8 byIdx = 0;

        for(byIdx = 0; byIdx < MAXNUM_PERIEQP*MAXNUM_MPU_CHN; byIdx++)
        {
            if (m_atIdleMpuChn[byIdx].IsNull())
            {
                byFstIdlePos = byFstIdlePos == 0xff ? byIdx : byFstIdlePos;
            }
            if (dwMpuIp == m_atIdleMpuChn[byIdx].GetIpAddr() &&
                byChnId == m_atIdleMpuChn[byIdx].GetChnId() )
            {
                bExist = TRUE;
                break;
            }
        }
        if (!bExist)
        {
            if (0xff == byFstIdlePos)
            {
                OspPrintf(TRUE, FALSE, "[TMcuHdBasStatus][SetIdleMpuChn] no pos for new mau!\n");
                return;
            }
            m_atIdleMpuChn[byFstIdlePos].SetIpAddr(dwMpuIp);
            m_atIdleMpuChn[byFstIdlePos].SetChnId(byChnId);
        }
        return;
    }


    void Clear(void)
    {
        memset(m_acConfId, 0, sizeof(m_acConfId));
        memset(m_aadwUsedMau, 0, sizeof(m_aadwUsedMau));
        memset(m_adwIdleMau, 0, sizeof(m_adwIdleMau));
        memset(m_aadwUsedH263pMau, 0, sizeof(m_aadwUsedH263pMau));
        memset(m_adwIdleH263pMau, 0, sizeof(m_adwIdleH263pMau));
        m_byCurMau = 0;
        m_byCurH263pMau = 0;
    }

private:
    BOOL32 IsConfExist(const CConfId &cConfId, u8 &byPos)
    {
        byPos = 0xff;
        BOOL32 bExist = FALSE;
        for(u8 byIdx = 0; byIdx < MAXNUM_ONGO_CONF; byIdx ++)
        {
            if (m_acConfId[byIdx].IsNull())
            {
                continue;
            }
            if (m_acConfId[byIdx] == cConfId)
            {
                bExist = TRUE;
                byPos = byIdx;
                break;
            }
        }
        return bExist;
    }

private:
    CConfId m_acConfId[MAXNUM_ONGO_CONF];

    u32     m_aadwUsedMau[MAXNUM_ONGO_CONF][MAXNUM_CONF_MAU];
    u32     m_aadwUsedH263pMau[MAXNUM_ONGO_CONF][MAXNUM_CONF_MAU];
    TMpuChn m_aatUsedMpuChn[MAXNUM_ONGO_CONF][MAXNUM_CONF_MPU];
    
    u32     m_adwIdleMau[MAXNUM_PERIEQP];
    u32     m_adwIdleH263pMau[MAXNUM_PERIEQP];
    TMpuChn m_atIdleMpuChn[MAXNUM_PERIEQP*MAXNUM_MPU_CHN];

    u8      m_byCurMau;
    u8      m_byCurH263pMau;
    u8      m_byCurMpuChn;
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

/*****************************************************************
 *
 *
 *                         �û�������չ
 *
 *
 *****************************************************************/
class CExUsrInfo: public CUserFullInfo
{
public:
    CExUsrInfo() {};

    CExUsrInfo(const CExUsrInfo &newInfo)
    {
        memcpy( this, &newInfo, sizeof(CUserFullInfo) );
    }

    CExUsrInfo(const CUserFullInfo &newInfo)
    {
        memcpy( this, &newInfo, sizeof(CUserFullInfo) );
    }

    const CExUsrInfo& operator=(const CExUsrInfo& newInfo)
    {
        if (this == &newInfo)
        {
            return *this;
        }

        memcpy( this, &newInfo, sizeof(CExUsrInfo) );

        return (*this);
    }

    BOOL32 operator == (const CExUsrInfo& newInfo)
    {
        return ( memcmp(this, &newInfo, sizeof(CExUsrInfo)) == 0 );
    }

    // ���ص��û���������Id������MCS����ʹ�������ṩ�ķ���

	//�õ��û�����
	char* GetDiscription()
	{
		return (discription+1);
	}
	
	//�����û�����
	void SetDiscription(char* buf)
	{
		if(buf == NULL)
        {
            return;
        }
        u8 byGrpId = discription[0];
		memset(discription, 0, 2 * MAX_CHARLENGTH);

        s32 length = (strlen(buf) >= 2*MAX_CHARLENGTH - 2 ? 2*MAX_CHARLENGTH - 2: strlen(buf));
		strncpy(discription+1, buf, length);

		discription[2*MAX_CHARLENGTH-1] = '\0';
        discription[0] = byGrpId;
	}
    void SetUsrGrpId( u8 byGrdId )
    {
        discription[0] = byGrdId;
    }
    u8 GetUsrGrpId()
    {
        return discription[0];
    }

    void Print( void )
    {
        OspPrintf(TRUE, FALSE, "name:%s actor:%d fullname:%s des:%s\n",
                  GetName(), GetActor(), GetFullName(), GetDiscription());
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;


// Ip��ַ�Σ�������
struct TIpSeg
{    
public:
	u32 dwIpStart;
	u32 dwIpEnd;

    u8  byEnabled;

public:
    TIpSeg()
    {
        SetNull();
    }

    // �����ַҪ��Ϊ������
    void SetSeg( u32 dwStart, u32 dwEnd)    
    {
        byEnabled = 1;
        dwIpStart = dwStart;
        dwIpEnd = dwEnd;
    }
    BOOL32 IsEnabled() const
    {
        return ( byEnabled == 1 ? TRUE : FALSE);
    }

    // ���ص�ַΪ������
    BOOL32 GetSeg ( u32& dwStart, u32& dwEnd ) const 
    {
        dwStart = dwIpStart;
        dwEnd   = dwIpEnd;
        return IsEnabled();
    }
    void SetNull()
    {
        memset(this, 0, sizeof(TIpSeg));
    }

    // ĳ��Ip�Ƿ��ڱ����ڡ���ַҪ����������
    BOOL32 IsIpIn(u32 dwIp) const 
    {
        u32 dwMin = dwIpStart;
        u32 dwMax = dwIpEnd;
        u32 dwTmp = 0;
        if (dwMin > dwMax)
        {
            dwTmp = dwMin;
            dwMin = dwMax;
            dwMax = dwTmp;
        }
        if (dwIp >= dwMin && dwIp <= dwMax )    
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }

    // ����һ��Ip���Ƿ��ڱ�����
    BOOL32 IsIpSegIn( const TIpSeg tAnother ) const
    {
        return ( IsIpIn(tAnother.dwIpStart)  &&
                 IsIpIn(tAnother.dwIpEnd) );
    }
}

#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

/* add by wangliang 2006-12-20 for E164  start */
/*
// E164�����
struct TE164Seg
{
public:
    s8 szE164Start[MAXLEN_E164+1];
    s8 szE164End[MAXLEN_E164+1];
    u8 byEnabled;

public:
    TE164Seg()
    {
        SetNull();
    }

    // ȡ��E164�����
    void SetSeg(LPCSTR pszStart, LPCSTR pszEnd)
    {
        byEnabled = 1;
        if(pszStart != NULL && pszEnd != NULL)
        {
            memset(szE164Start, 0, sizeof(szE164Start));
            memset(szE164End, 0, sizeof(szE164End));
            strncpy(szE164Start, pszStart, MAXLEN_E164);
            strncpy(szE164End, pszEnd, MAXLEN_E164);
        }
        return;
    }

    BOOL32 IsEnabled() const
    {
        return (byEnabled == 1 ? TRUE : FALSE);
    }

    // ����E164�����
    BOOL32 GetSeg(s8 *pszStart, s8 *pszEnd) const 
    {
        strncpy(pszStart, szE164Start, MAXLEN_E164);
        strncpy(pszEnd, szE164End, MAXLEN_E164);
        return IsEnabled();
    }

    // �ṹ�ÿ�
    void SetNull()
    {
        memset(this, 0, sizeof(TE164Seg));
    }

    // E164�����Ƿ��ڱ�E164�������
    // FIXME: ���pszE164��szE164Start��szE164End���Ȳ�ͬ�����ܹ��ϸ��ж��Ƿ��ڶ���
    BOOL32 IsE164In(LPCSTR pszE164) const
    {
        if(strncmp(szE164Start, szE164End, MAXLEN_E164) < 0)
        {
            if(strncmp(pszE164, szE164Start, MAXLEN_E164) >= 0 
                && strncmp(pszE164, szE164End, MAXLEN_E164) <= 0)
                return TRUE;
            else
                return FALSE;
        }
        else
        {
            if(strncmp(pszE164, szE164End, MAXLEN_E164) >= 0 
                && strncmp(pszE164, szE164Start, MAXLEN_E164) <= 0)
                return TRUE;
            else
                return FALSE;
        }  
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;
*/
/* add by wangliang 2006-12-20 for E164  end */

// �û�����Ϣ
struct TUsrGrpInfo
{
public:
    TUsrGrpInfo()
    {
        SetNull();
    }

public:
    void SetNull()
    {
        memset ( this, 0, sizeof(TUsrGrpInfo) );
        SetBanned(TRUE);    // Ĭ���ǽ�ֹ
    }
    // �жϱ��û����Ƿ�Ϊ��
    BOOL32 IsFree() const
    {
        return (byGrpId == 0);
    }
    // ����/��ȡ�û���ID
    void SetUsrGrpId(u8 byId)
    {
        byGrpId = byId;
    }
    u8 GetUsrGrpId() const
    {
        return byGrpId;
    }
    // ����/��ȡ�û�����
    void SetUsrGrpName(LPCSTR lpszName)
    {
        memset(szName, 0, MAX_CHARLENGTH);
        strncpy(szName, lpszName, MAX_CHARLENGTH-1);
    }
    LPCSTR GetUsrGrpName() const
    {
        return szName;
    }
    // ����/��ȡ�û�������
    void SetUsrGrpDesc(LPCSTR lpszDesc)
    {
        memset(szDesc, 0, 2*MAX_CHARLENGTH);
        strncpy(szDesc, lpszDesc, 2*MAX_CHARLENGTH-1);
    }
    LPCSTR GetUsrGrpDesc() const
    {
        return szDesc;
    }
    void SetMaxUsrNum(u8 byMaxNum)
    {
        byMaxUsrNum = byMaxNum;
    }
    u8 GetMaxUsrNum() const
    {
        return byMaxUsrNum;
    }
    void SetBanned(BOOL32 bIsBanned)
    {
        bBanned = bIsBanned ? 1 : 0;
    }
    BOOL32 IsBanned() const
    {
        return bBanned ? TRUE : FALSE;
    }

    // �ж��ն�IP�Ƿ��ںϷ����ڣ�
    // �����ַ��������
    inline BOOL32 IsMtIpInAllowSeg(u32 dwIp) const;

    void Print() const
    {
        if ( IsFree() )
        {            
            OspPrintf( TRUE, FALSE, "\tGroup ID: FREE\n" );
            return;
        }        
        OspPrintf( TRUE, FALSE, "\tGroup ID: %d\n", byGrpId );
        OspPrintf( TRUE, FALSE, "\tName: %s\n", szName);
        OspPrintf( TRUE, FALSE, "\tDesc: %s\n", szDesc);
        OspPrintf( TRUE, FALSE, "\tMax User: %d\n", byMaxUsrNum);

        OspPrintf( TRUE, FALSE, "\tIP Ranges: %s\n", bBanned ? "Banned" : "Allowed");
        for (s32 nLoop = 0; nLoop < MAXNUM_IPSEG; nLoop ++)
        {
            OspPrintf( TRUE, FALSE, "\t\tNo.%d: Enabled: %d IP: 0x%x -- 0x%x\n", 
                       nLoop,
                       atIpSeg[nLoop].IsEnabled(), 
                       atIpSeg[nLoop].dwIpStart, 
                       atIpSeg[nLoop].dwIpEnd );
        }        
    }

protected:
	u8      byGrpId;
	s8      szName[MAX_CHARLENGTH];
	s8      szDesc[2*MAX_CHARLENGTH];
	u8      byMaxUsrNum;
public:
    TIpSeg  atIpSeg[MAXNUM_IPSEG];  // ��ַ��������
    u8      bBanned;     // 0 - ��ʾָ����������, 1 - ��ʾ�ǽ�ֹ
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// VCS�û���Ϣ�������˲�������ϯ�������
class CVCSUsrInfo: public CExUsrInfo
{
public:
	CVCSUsrInfo()
	{
		SetNull();
	}

    ~CVCSUsrInfo() {};

    void SetNull()
	{
		m_wTaskNum = 0;
		memset(m_cTaskID, 0, sizeof(CConfId) * MAXNUM_MCU_VCCONF);
	}

	// ָ�����û��ĵ�������
	BOOL AssignTask(u16 wTaskNum, const CConfId* pConfID)
	{
		if (pConfID == NULL)
		{
			return FALSE;
		}

		SetNull();
		m_wTaskNum = htons(wTaskNum);
		memcpy(m_cTaskID, pConfID, sizeof(CConfId) * wTaskNum);
		return TRUE;
	}

	// ��ȡ���û��ĵ�������
	const CConfId* GetTask() const
	{
		return m_cTaskID;
	}
	u16 GetTaskNum() const
	{
		return ntohs(m_wTaskNum);
	}

	// �����Ƿ���ָ������Χ��
	BOOL IsYourTask(CConfId cTaskID)
	{
		BOOL dwIsYourTask = FALSE;
		for (u16 wIndex = 0; wIndex < MAXNUM_MCU_VCCONF; wIndex++)
		{
			if (cTaskID == m_cTaskID[wIndex])
			{
				dwIsYourTask = TRUE;
				break;
			}
		}
		return dwIsYourTask;
	}

protected:
    u16     m_wTaskNum;
	CConfId m_cTaskID[ MAXNUM_MCU_VCCONF ];
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

/*-------------------------------------------------------------------
                               CServMsg                              
--------------------------------------------------------------------*/

/*====================================================================
    ������      ��CServMsg
    ����        ��constructor
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����
    ����ֵ˵��  ��
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline CServMsg::CServMsg( void )
{
	Init();
}

/*====================================================================
    ������      ��CServMsg
    ����        ��constructor
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u8 * const pbyMsg, Ҫ��ֵ����Ϣָ��
				  u16 wMsgLen, Ҫ��ֵ����Ϣ���ȣ�������ڵ��� SERV_MSGHEAD_LEN
    ����ֵ˵��  ��
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline CServMsg::CServMsg( u8 * const pbyMsg, u16 wMsgLen )
{
	Init();
	
	if( wMsgLen < SERV_MSGHEAD_LEN || pbyMsg == NULL )
		return;
	
	wMsgLen = min( wMsgLen, SERV_MSG_LEN );
	memcpy( this, pbyMsg, wMsgLen );
	
	//set length
	SetMsgBodyLen( wMsgLen - SERV_MSGHEAD_LEN );
}

/*====================================================================
    ������      ��~CServMsg
    ����        ��distructor
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����
    ����ֵ˵��  ��
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline CServMsg::~CServMsg( void )
{

}

/*====================================================================
    ������      ��Init
    ����        ��BUFFER��ʼ��
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����
    ����ֵ˵��  ��
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline void CServMsg::Init( void )
{
	memset( this, 0, SERV_MSG_LEN );	//����
}

/*====================================================================
    ������      ��ClearHdr
    ����        ����Ϣͷ����
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����
    ����ֵ˵��  ��
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline void CServMsg::ClearHdr( void )
{
	u16		wBodyLen = GetMsgBodyLen();

	memset( this, 0, SERV_MSGHEAD_LEN );	//����
	SetMsgBodyLen( wBodyLen );
}

/*====================================================================
    ������      ��GetConfId
    ����        ����ȡ�������Ϣ
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵������
    ����ֵ˵��  ������ţ�ȫ0��ʾ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
    02/12/24    1.0         LI Yi         �޸Ľӿ�
====================================================================*/
inline CConfId CServMsg::GetConfId( void ) const
{
	return( m_cConfId );
}

/*====================================================================
    ������      ��SetConfId
    ����        �����û������Ϣ
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����const CConfId & cConfId������ţ�ȫ0��ʾ����
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
    02/12/24    1.0         LI Yi         �޸Ľӿ�
====================================================================*/
inline void CServMsg::SetConfId( const CConfId & cConfId )
{
	m_cConfId = cConfId;
}

/*====================================================================
    ������      ��SetNullConfId
    ����        �����û������ϢΪ��
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵������
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    03/06/06    1.0         LI Yi         ����
====================================================================*/
inline void CServMsg::SetNullConfId( void )
{
	CConfId		cConfId;
	
	cConfId.SetNull();
	SetConfId( cConfId );
}

/*====================================================================
    ������      ��GetMsgBodyLen
    ����        ����ȡ��Ϣ�峤����Ϣ
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵������
    ����ֵ˵��  ����Ϣ�峤��
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline u16 CServMsg::GetMsgBodyLen( void ) const
{
	return( ntohs( m_wMsgBodyLen ) );
}

/*====================================================================
    ������      ��SetMsgBodyLen
    ����        ��������Ϣ�峤����Ϣ
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u16 wMsgBodyLen, ��Ϣ�峤��
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline void CServMsg::SetMsgBodyLen( u16 wMsgBodyLen )
{
	m_wMsgBodyLen = htons( wMsgBodyLen );
}

/*====================================================================
    ������      ��GetMsgBody
    ����        ����ȡ��Ϣ��ָ�룬�û������ṩBUFFER
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵������
    ����ֵ˵��  ��u8 * constָ��
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline u8 * const CServMsg::GetMsgBody( void ) const
{
	return( ( u8 * const )m_abyMsgBody );
}

/*====================================================================
    ������      ��GetMsgBodyLen
    ����        ����ȡ������Ϣ����
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵������
    ����ֵ˵��  ��������Ϣ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/26    1.0         LI Yi         ����
====================================================================*/
inline u16 CServMsg::GetServMsgLen( void ) const
{
	return( GetMsgBodyLen() + SERV_MSGHEAD_LEN );
}

/*====================================================================
    ������      ��GetMsgBody
    ����        ����ȡ��Ϣ�壬���û�����BUFFER�������С���ضϴ���
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u8 * pbyMsgBodyBuf, ���ص���Ϣ��
				  u16 wBufLen, BUFFER��С
    ����ֵ˵��  ��ʵ�ʷ��ص���Ϣ�峤��
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline u16 CServMsg::GetMsgBody( u8 * pbyMsgBodyBuf, u16 wBufLen ) const
{
    u16 wActLen = min( GetMsgBodyLen(), wBufLen );
	memcpy( pbyMsgBodyBuf, m_abyMsgBody, wActLen );
	return wActLen;
}

/*====================================================================
    ������      ��SetMsgBody
    ����        ��������Ϣ��
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u8 * const pbyMsgBody, �������Ϣ�壬ȱʡΪNULL
				  u16 wLen, �������Ϣ�峤�ȣ�ȱʡΪ0
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline void CServMsg::SetMsgBody( u8 * const pbyMsgBody, u16 wLen )
{
    /*
    if (pbyMsgBody == NULL || wLen == 0)
    {
        SetMsgBodyLen( 0 );
        return;
    }
    */
	wLen = min( wLen, SERV_MSG_LEN - SERV_MSGHEAD_LEN );
	memcpy( m_abyMsgBody, pbyMsgBody, wLen );
	SetMsgBodyLen( wLen );
}

/*====================================================================
    ������      ��CatMsgBody
    ����        �������Ϣ��
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u8 * const pbyMsgBody, �������Ϣ�壬ȱʡΪNULL
				  u16 wLen, �������Ϣ�峤�ȣ�ȱʡΪ0
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/11/07    1.0         Liaoweijiang  ����
====================================================================*/
inline void CServMsg::CatMsgBody( u8 * const pbyMsgBody, u16 wLen )
{
    /*
    if (pbyMsgBody == NULL || wLen == 0)
    {
        return;
    }
    */
	wLen = min( wLen, SERV_MSG_LEN - SERV_MSGHEAD_LEN - GetMsgBodyLen() );
	memcpy( m_abyMsgBody + GetMsgBodyLen(), pbyMsgBody, wLen );
	SetMsgBodyLen( GetMsgBodyLen() + wLen );
}

/*====================================================================
    ������      ��GetMsgBody
    ����        ����ȡ������Ϣָ�룬�û������ṩBUFFER
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵������
    ����ֵ˵��  ��u8 * constָ��
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/26    1.0         LI Yi         ����
====================================================================*/
inline u8 * const CServMsg::GetServMsg( void ) const
{
	return( ( u8 * const )( this ) );
}

/*====================================================================
    ������      ��GetServMsg
    ����        ����ȡ������Ϣ�����û�����BUFFER�������С���ضϴ���
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u8 * pbyMsgBuf, ���ص���Ϣ
				  u16 wBufLen, BUFFER��С
    ����ֵ˵��  ��ʵ�ʷ��ص���Ϣ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline u16 CServMsg::GetServMsg( u8 * pbyMsgBuf, u16 wBufLen ) const
{
	wBufLen = min(SERV_MSG_LEN,wBufLen);
	memcpy( pbyMsgBuf, this, wBufLen );
	return( min( GetMsgBodyLen() + SERV_MSGHEAD_LEN, wBufLen ) );
}

/*====================================================================
    ������      ��SetServMsg
    ����        ������������Ϣ
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u8 * const pbyMsg, �����������Ϣ
				  u16 wMsgLen, �������Ϣ����
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline void CServMsg::SetServMsg( u8 * const pbyMsg, u16 wMsgLen )
{
	if( wMsgLen < SERV_MSGHEAD_LEN )
	{
		OspPrintf( TRUE, FALSE, "CServMsg: SetServMsg() Exception -- invalid MsgLen!\n" );
		return;
	}

	wMsgLen = min( wMsgLen, SERV_MSG_LEN );
	memcpy( this, pbyMsg, wMsgLen );
	SetMsgBodyLen( wMsgLen - SERV_MSGHEAD_LEN );
}

/*====================================================================
    ������      ��operator=
    ����        ������������
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����CServMsg & cServMsg, ��ֵ����Ϣ����
    ����ֵ˵��  ��CServMsg����Ӧ��
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/26    1.0         LI Yi         ����
====================================================================*/
inline const CServMsg & CServMsg::operator= ( const CServMsg & cServMsg )
{
	u16	wLen = cServMsg.GetServMsgLen();

	memcpy( this, cServMsg.GetServMsg(), wLen );
	return( *this );
}

/*-------------------------------------------------------------------
                               TConfMtInfo                           
--------------------------------------------------------------------*/

/*====================================================================
    ������      ��TConfMtInfo
    ����        ��constructor
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵������
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/30    1.0         LI Yi         ����
====================================================================*/
inline TConfMtInfo::TConfMtInfo( void )
{
	memset( this, 0, sizeof( TConfMtInfo ) );
}

/*====================================================================
    ������      ��MtInConf
    ����        ���жϸ�MCU��ĳ�ն��Ƿ��������ն��б���
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u8 byMtId, �ն˺�
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/30    1.0         LI Yi         ����
====================================================================*/
inline BOOL TConfMtInfo::MtInConf( u8 byMtId ) const
{
	if( byMtId == 0 || byMtId > MAXNUM_CONF_MT)return FALSE;
	return ( ( m_abyMt[(byMtId-1) / 8] & ( 1 << ( (byMtId-1) % 8 ) ) ) != 0 );
}

/*====================================================================
    ������      ��MtJoinedConf
    ����        ���жϸ�MCU��ĳ�ն��Ƿ�������ն��б���
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u8 byMtId, �ն˺�
    ����ֵ˵��  ��TRUE/FALSE
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/12/24    1.0         LI Yi         ����
====================================================================*/
inline BOOL TConfMtInfo::MtJoinedConf( u8 byMtId ) const
{
	if( byMtId == 0 || byMtId > MAXNUM_CONF_MT) return FALSE;
	return ( ( m_abyJoinedMt[(byMtId-1) / 8] & ( 1 << ( (byMtId-1) % 8 ) ) ) != 0 );
}

/*====================================================================
    ������      ��AddMt
    ����        �����Ӹ�MCU���ն��������ն��б���
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u8 byMtId, �ն˺�
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/30    1.0         LI Yi         ����
====================================================================*/
inline void TConfMtInfo::AddMt( u8 byMtId )
{
	if( byMtId == 0 || byMtId > MAXNUM_CONF_MT)return;
	m_abyMt[(byMtId-1) / 8] |= 1 << ( (byMtId-1) % 8 );
}

/*====================================================================
    ������      ��AddJoinedMt
    ����        �����Ӹ�MCU���ն�������ն��б��У��ú����Զ������ն�Ҳ
	              ���뵽�����ն��б���
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u8 byMtId, �ն˺�
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/12/25    1.0         LI Yi         ����
====================================================================*/
inline void TConfMtInfo::AddJoinedMt( u8 byMtId )
{
	if( byMtId == 0 || byMtId > MAXNUM_CONF_MT)return;
	m_abyJoinedMt[(byMtId-1) / 8] |= 1 << ( (byMtId-1) % 8 );
	m_abyMt[(byMtId-1) / 8] |= 1 << ( (byMtId-1) % 8 );
}

/*====================================================================
    ������      ��RemoveMt
    ����        ��ɾ����MCU���ն��������ն��б��У��ú����Զ������ն�Ҳ
	              ɾ��������ն��б���
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u8 byMtId, �ն˺�
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/30    1.0         LI Yi         ����
====================================================================*/
inline void TConfMtInfo::RemoveMt( u8 byMtId )
{
	if( byMtId == 0 || byMtId > MAXNUM_CONF_MT)return;
	m_abyMt[(byMtId-1) / 8] &= ~( 1 << ( (byMtId-1) % 8 ) );
	m_abyJoinedMt[(byMtId-1) / 8] &= ~( 1 << ( (byMtId-1) % 8 ) );
}

/*====================================================================
    ������      ��RemoveJoinedMt
    ����        ��ɾ����MCU���ն�������ն��б���
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u8 byMtId, �ն˺�
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/12/25    1.0         LI Yi         ����
====================================================================*/
inline void TConfMtInfo::RemoveJoinedMt( u8 byMtId )
{
	if( byMtId == 0 || byMtId > MAXNUM_CONF_MT)return;
	m_abyJoinedMt[(byMtId-1) / 8] &= ~( 1 << ( (byMtId-1) % 8 ) );
}

/*====================================================================
    ������      ��RemoveAllMt
    ����        ��ɾ����MCU�������ն��������ն��б��У��ú����Զ��������ն�Ҳ
	              ɾ��������ն��б���
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵������
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/30    1.0         LI Yi         ����
====================================================================*/
inline void TConfMtInfo::RemoveAllMt( void )
{
	memset( m_abyMt, 0, sizeof( m_abyMt ) );
	memset( m_abyJoinedMt, 0, sizeof( m_abyMt ) );
}

/*====================================================================
    ������      ��RemoveAllJoinedMt
    ����        ��ɾ����MCU�������ն�������ն��б���
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵������
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/12/25    1.0         LI Yi         ����
====================================================================*/
inline void TConfMtInfo::RemoveAllJoinedMt( void )
{
	memset( m_abyJoinedMt, 0, sizeof( m_abyMt ) );
}

/*====================================================================
    ������      ��GetAllMtNum
    ����        ���õ�һ���ṹ�����������ն˸���
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵������
    ����ֵ˵��  �������������ն˸���
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/08/02    1.0         LI Yi         ����
====================================================================*/
inline u8 TConfMtInfo::GetAllMtNum( void ) const
{
	u8	byMtNum = 0;

	for( u8 byLoop = 0; byLoop < MAXNUM_CONF_MT; byLoop++ )
	{
		if( MtInConf( byLoop + 1 ) )
		{
			byMtNum++;
		}
	}

	return( byMtNum );
}

/*====================================================================
    ������      ��GetLocalJoinedMtNum
    ����        ���õ�һ���ṹ����������ն˸���
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵������
    ����ֵ˵��  ������������ն˸���
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/12/25    1.0         LI Yi         ����
====================================================================*/
inline u8 TConfMtInfo::GetAllJoinedMtNum( void ) const
{
	u8	byMtNum = 0;

	for( u8 byLoop = 0; byLoop < MAXNUM_CONF_MT; byLoop++ )
	{
		if( MtJoinedConf( byLoop + 1 ) )
		{
			byMtNum++;
		}
	}

	return( byMtNum );
}

/*====================================================================
    ������      ��GetLocalUnjoinedMtNum
    ����        ���õ�һ���ṹ������δ����ն˸���
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵������
    ����ֵ˵��  ��������δ����ն˸���
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/12/25    1.0         LI Yi         ����
====================================================================*/
inline u8 TConfMtInfo::GetAllUnjoinedMtNum( void ) const
{
	return( GetAllMtNum() - GetAllJoinedMtNum() );
}

/*==============================================================================
������    :  GetMaxMtIdInConf
����      :  �õ�һ���ṹ�������ն���MTId����Idֵ
�㷨ʵ��  :  
����˵��  :  
����ֵ˵��:  
-------------------------------------------------------------------------------
�޸ļ�¼  :  
��  ��       �汾          �޸���          �߶���          �޸ļ�¼
2008-12-24					Ѧ��							����
==============================================================================*/
inline u8 TConfMtInfo::GetMaxMtIdInConf( void ) const
{
	u8	byMaxMtId= 0;
	
	for( u8 byLoop = 0; byLoop < MAXNUM_CONF_MT; byLoop++ )
	{
		if( MtInConf( byLoop + 1 ) )
		{
			byMaxMtId = byLoop + 1;
		}
	}
	
	return( byMaxMtId );
}


/*-------------------------------------------------------------------
                           TConfAllMtInfo                          
--------------------------------------------------------------------*/

/*====================================================================
    ������      ��AddMt
    ����        ������������һ�������ն�
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u8 byMtId, �ն˺�
    ����ֵ˵��  ���ɹ�����TRUE������FALSE
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/31    1.0         LI Yi         ����
====================================================================*/
inline BOOL TConfAllMtInfo::AddMt(u8 byMtId )
{
	if(byMtId>=MAXNUM_CONF_MT)return FALSE;
	m_tLocalMtInfo.AddMt( byMtId );
	return TRUE;
}

/*====================================================================
    ������      ��AddJoinedMt 
    ����        ������������һ������նˣ��ú����Զ������ն�Ҳ
	              ���뵽�����ն��б���
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u8 byMtId, �ն˺�
    ����ֵ˵��  ���ɹ�����TRUE������FALSE
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/12/30    1.0         LI Yi         ����
====================================================================*/
inline BOOL TConfAllMtInfo::AddJoinedMt(u8 byMtId )
{
    if(byMtId>=MAXNUM_CONF_MT)return FALSE;
	m_tLocalMtInfo.AddJoinedMt( byMtId );
	m_tLocalMtInfo.AddMt( byMtId );
	return TRUE;
}

/*====================================================================
    ������      ��RemoveMt
    ����        ��������ɾ��һ�������նˣ��ú����Զ������ն�Ҳ
	              ɾ��������ն��б���
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u8 byMtId, �ն˺�
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/31    1.0         LI Yi         ����
====================================================================*/
inline void TConfAllMtInfo::RemoveMt(u8 byMtId )
{
    if(byMtId>=MAXNUM_CONF_MT)return;	
	m_tLocalMtInfo.RemoveMt( byMtId );
	m_tLocalMtInfo.RemoveJoinedMt( byMtId );
}

/*====================================================================
    ������      ��RemoveJoinedMt
    ����        ��������ɾ��һ������ն�
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u8 byMtId, �ն˺�
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/12/30    1.0         LI Yi         ����
====================================================================*/
inline void TConfAllMtInfo::RemoveJoinedMt( u8 byMtId )
{
	if(byMtId>=MAXNUM_CONF_MT)return;
	m_tLocalMtInfo.RemoveJoinedMt( byMtId );
}

/*====================================================================
    ������      ��RemoveAllMt
    ����        ��������ɾ��һ��MCU�����������նˣ���ɾ��MCU�����ú���
	              �Զ��������ն�Ҳɾ��������ն��б���
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/31    1.0         LI Yi         ����
====================================================================*/
inline void TConfAllMtInfo::RemoveAllMt( void )
{
	m_tLocalMtInfo.RemoveAllMt();
	m_tLocalMtInfo.RemoveAllJoinedMt();
}

/*====================================================================
    ������      ��RemoveAllJoinedMt
    ����        ��������ɾ��һ��MCU����������նˣ���ɾ��MCU��
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u16 wMcuId, MCU��
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/12/30    1.0         LI Yi         ����
====================================================================*/
inline void TConfAllMtInfo::RemoveAllJoinedMt( void )
{
	m_tLocalMtInfo.RemoveAllJoinedMt();
}

/*====================================================================
    ������      ��MtInConf
    ����        ���ж��ն��Ƿ��������ն��б���
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u8 byMtId, �ն˺�
    ����ֵ˵��  ��TRUE/FALSE
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/08/01    1.0         LI Yi         ����
====================================================================*/
inline BOOL TConfAllMtInfo::MtInConf(u8 byMtId ) const
{
	return m_tLocalMtInfo.MtInConf( byMtId );
}

/*====================================================================
    ������      ��MtJoinedConf
    ����        ���ж��ն��Ƿ�������ն��б���
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u16 wMcuId, MCU��
				  u8 byMtId, �ն˺�
    ����ֵ˵��  ��TRUE/FALSE
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/12/30    1.0         LI Yi         ����
====================================================================*/
inline BOOL TConfAllMtInfo::MtJoinedConf(u8 byMtId ) const
{
	return m_tLocalMtInfo.MtJoinedConf( byMtId );
}

/*==============================================================================
������    : MtJoinedConf 
����      : �ж��ն��Ƿ�������ն��б���(�����¼�MCU�µ�ĳ�ն�)
�㷨ʵ��  :  
����˵��  :  TMt tMt
����ֵ˵��:  BOOL
-------------------------------------------------------------------------------
�޸ļ�¼  :  
��  ��       �汾          �޸���          �߶���          �޸ļ�¼
2009-9-30                   Ѧ��
==============================================================================*/
inline BOOL TConfAllMtInfo::MtJoinedConf(TMt tMt ) const
{
	if(tMt.IsLocal())
	{
		return m_tLocalMtInfo.MtJoinedConf( tMt.GetMtId() );
	}
	else
	{
		u8 byMcuId = tMt.GetMcuId();
		u8 byMtId = tMt.GetMtId();
		if( m_tLocalMtInfo.MtJoinedConf( byMcuId ) )
		{
			return m_atOtherMcMtInfo[byMcuId-1].MtJoinedConf(byMtId);
		}
	}
	return FALSE;
}
/*====================================================================
    ������      ��GetAllMtNum
    ����        ���õ����������ṹ�����������ն˸���
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����void
    ����ֵ˵��  �����صĻ��������������ն˸���
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/08/02    1.0         LI Yi         ����
====================================================================*/
inline u8   TConfAllMtInfo::GetLocalMtNum( void ) const
{
	return m_tLocalMtInfo.GetAllMtNum();
}

/*====================================================================
    ������      ��GetAllJoinedMtNum
    ����        ���õ����������ṹ����������ն˸���
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����void
    ����ֵ˵��  �����صĻ�������������ն˸���
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/12/30    1.0         LI Yi         ����
====================================================================*/
inline u8   TConfAllMtInfo::GetLocalJoinedMtNum( void ) const
{
	return m_tLocalMtInfo.GetAllJoinedMtNum();
}

/*====================================================================
    ������      ��GetAllUnjoinedMtNum
    ����        ���õ����������ṹ������δ����ն˸��� 
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����void
    ����ֵ˵��  �����صĻ���������δ����ն˸���
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/12/30    1.0         LI Yi         ����
====================================================================*/
inline u8   TConfAllMtInfo::GetLocalUnjoinedMtNum( void ) const
{
	return m_tLocalMtInfo.GetAllUnjoinedMtNum();
}

/*====================================================================
    ������      ��SetMtInfo
    ����        ������ĳ��Mc���ն���Ϣ
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����void
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    04/07/29    3.0         ������         ����
====================================================================*/
inline void   TConfAllMtInfo::SetMtInfo(TConfMtInfo tConfMtInfo )
{

	u8 byLoop = 0;
	
	if( LOCAL_MCUID == tConfMtInfo.GetMcuId() )
	{
		m_tLocalMtInfo = tConfMtInfo;
		return;
	}

	//����Mcu��
	while( byLoop < MAXNUM_SUB_MCU )
	{
		if( m_atOtherMcMtInfo[byLoop].GetMcuId() != tConfMtInfo.GetMcuId() )
		{
			byLoop ++;
		}
		else
		{
			//�Ѵ���
			m_atOtherMcMtInfo[byLoop] = tConfMtInfo;
			break;
		}
	}

	//������
	if( byLoop == MAXNUM_SUB_MCU )
	{
		byLoop = 0;
		while( byLoop < MAXNUM_SUB_MCU )
		{
			if( m_atOtherMcMtInfo[byLoop].IsNull() )
			{
				m_atOtherMcMtInfo[byLoop] = tConfMtInfo;
				break;
			}
			else
			{
				byLoop++;
			}
		}
	}
}

/*====================================================================
    ������      ��GetMcMtInfo
    ����        ���õ�ĳ��Mc���ն���Ϣ
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����void
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    04/07/29    3.0         ������         ����
====================================================================*/
inline TConfMtInfo  TConfAllMtInfo::GetMtInfo( u8 byMcuId ) const
{
	TConfMtInfo tConfMtInfo;

	if(byMcuId == m_tLocalMtInfo.GetMcuId())
	{
		return m_tLocalMtInfo;
	}
	u8 byLoop = 0;
	//����Mcu��
	while( byLoop < MAXNUM_SUB_MCU )
	{
		if( m_atOtherMcMtInfo[byLoop].GetMcuId() != byMcuId )
		{
			byLoop ++;
		}
		else
		{
			tConfMtInfo = m_atOtherMcMtInfo[byLoop];
			break;
		}
	}

	return tConfMtInfo;
}

/*====================================================================
    ������      ��GetMtInfoPtr
    ����        ���õ�ĳ��Mc���ն���Ϣ
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����void
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    04/07/29    3.0         ������         ����
====================================================================*/
inline TConfMtInfo*  TConfAllMtInfo::GetMtInfoPtr( u8 byMcuId )
{
	TConfMtInfo *ptConfMtInfo = NULL;

	if(byMcuId == m_tLocalMtInfo.GetMcuId())
	{
		return &m_tLocalMtInfo;
	}
	u8 byLoop = 0;
	//����Mcu��
	while( byLoop < MAXNUM_SUB_MCU )
	{
		if( m_atOtherMcMtInfo[byLoop].GetMcuId() != byMcuId )
		{
			byLoop ++;
		}
		else
		{
			ptConfMtInfo = &(m_atOtherMcMtInfo[byLoop]);
			break;
		}
	}

	return ptConfMtInfo;
}

/*====================================================================
    ������      ��MtInConf
    ����        ���õ�ĳ���ն��Ƿ��������ն��б��е���Ϣ 
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����void
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    04/07/29    3.0         ������         ����
====================================================================*/
inline BOOL TConfAllMtInfo::MtInConf( u8  byMcuId, u8  byMtId ) const//�ж��ն��Ƿ��������ն��б���
{
	TConfMtInfo tConfMtInfo = GetMtInfo( byMcuId );
	if( !tConfMtInfo.IsNull() )
	{
		return tConfMtInfo.MtInConf( byMtId );
	}
	else
	{
		return FALSE;
	}
}

/*====================================================================
    ������      ��MtJoinedConf
    ����        ���õ�ĳ���ն��Ƿ�������Ϣ 
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����void
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    04/07/29    3.0         ������         ����
====================================================================*/
inline BOOL TConfAllMtInfo::MtJoinedConf( u8  byMcuId, u8  byMtId ) const//�ж��ն��Ƿ�������ն��б���
{
	if( m_tLocalMtInfo.GetMcuId() == byMcuId )
	{
		return MtJoinedConf( byMtId );
	}

	TConfMtInfo tConfMtInfo = GetMtInfo( byMcuId );
	if( !tConfMtInfo.IsNull() )
	{
		return tConfMtInfo.MtJoinedConf( byMtId );
	}
	else
	{
		return FALSE;
	}
}
/*====================================================================
    ������      ��GetAllMtNum
    ����        ���õ����������ṹ�����������ն˸���
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����void
    ����ֵ˵��  ���õ����������������ն���
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    04/07/29    3.0         ������         ����
====================================================================*/
inline u16   TConfAllMtInfo::GetAllMtNum( void ) const 
{
	u8 byLoop = 0;
	u16 wMtNum = 0;
/*	
	TConfMtInfo tConfMtInfo;

	//����Mc��
	while( byLoop < MAXNUM_SUB_MCU )
	{
		tConfMtInfo = m_atOtherMcMtInfo[byLoop];
		if( !tConfMtInfo.IsNull() )
		{
			wMtNum = wMtNum + m_atOtherMcMtInfo[byLoop].GetAllMtNum();
		}

		byLoop++;
	}
*/
	// ֻ���ر�Mc���ն�
	wMtNum = m_tLocalMtInfo.GetAllMtNum();

	return wMtNum;
}

/*==============================================================================
������    :  GetMaxMtIdInConf
����      :  �õ����������ṹ�����������ն���ID����ֵ
�㷨ʵ��  :  
����˵��  :  
����ֵ˵��:  u8 
-------------------------------------------------------------------------------
�޸ļ�¼  :  
��  ��       �汾          �޸���          �߶���          �޸ļ�¼
2008-12-24					Ѧ��							����
==============================================================================*/
inline u8 TConfAllMtInfo::GetMaxMtIdInConf( void ) const
{
	// ֻ���ر�Mc��
	u8 byMaxMtId = 0;
	byMaxMtId = m_tLocalMtInfo.GetMaxMtIdInConf();
	return byMaxMtId;
}

/*====================================================================
    ������      ��GetCascadeMcuNum
    ����        ���õ������ı��mcu����
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����void
    ����ֵ˵��  ���¼�Mc�ĸ���
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    04/07/29    3.0         ������         ����
====================================================================*/
inline u8  TConfAllMtInfo::GetCascadeMcuNum( void) const
{   

	u8 byMcNum = 0;
	for( u8 byLoop=0; byLoop < MAXNUM_SUB_MCU; byLoop++ )
	{
		if( !m_atOtherMcMtInfo[byLoop].IsNull() )
		{
			byMcNum++;
		}
	}

	return byMcNum;

}

/*=============================================================================
    �� �� ���� AddMcuInfo
    ��    �ܣ� ����������һ��mcu��Ϣ��������ʱû���ն�
    �㷨ʵ�֣� 
    ȫ�ֱ����� 
    ��    ���� u8 byMcuId
	           u8 m_byConfIdx
    �� �� ֵ�� inline BOOL 
-----------------------------------------------------------------------------
    �޸ļ�¼��
    ��  ��		�汾		�޸���		�߶���    �޸�����
    2005/04/22  3.6			����                  ����
=============================================================================*/
inline BOOL TConfAllMtInfo::AddMcuInfo( u8 byMcuId, u8 m_byConfIdx )
{   
	u8 byLoop = 0;

	//����Mcu��
	while( byLoop < MAXNUM_SUB_MCU )
	{
		//�Ѵ��ڣ����ԭ����Ϣ
		if( m_atOtherMcMtInfo[byLoop].GetMcuId() == byMcuId )
		{
			memset( &m_atOtherMcMtInfo[byLoop], 0, sizeof(TConfMtInfo) );
			m_atOtherMcMtInfo[byLoop].SetMcuId( byMcuId );
			m_atOtherMcMtInfo[byLoop].SetConfIdx( m_byConfIdx );
			return TRUE;
		}
		byLoop++;
	}

	//������,����һ����λ�����з���
	if( byLoop == MAXNUM_SUB_MCU )
	{
		byLoop = 0;
		while( byLoop < MAXNUM_SUB_MCU )
		{
			if( m_atOtherMcMtInfo[byLoop].IsNull() )
			{
				TConfMtInfo tConfMtInfo;
				memset( &tConfMtInfo, 0, sizeof(TConfMtInfo) );
				tConfMtInfo.SetMcuId( byMcuId );
				tConfMtInfo.SetConfIdx( m_byConfIdx );
				m_atOtherMcMtInfo[byLoop] = tConfMtInfo;
				return TRUE;
			}
			byLoop++;
		}
	}

	return FALSE;
}

/*=============================================================================
    �� �� ���� RemoveMcuInfo
    ��    �ܣ� �������Ƴ�һ��mcu��Ϣ��ͬʱ������������ն���Ϣ
    �㷨ʵ�֣� 
    ȫ�ֱ����� 
    ��    ���� u8 byMcuId
	           u8 m_byConfIdx
    �� �� ֵ�� inline BOOL 
-----------------------------------------------------------------------------
    �޸ļ�¼��
    ��  ��		�汾		�޸���		�߶���    �޸�����
    2005/04/22  3.6			����                  ����
=============================================================================*/
inline BOOL TConfAllMtInfo::RemoveMcuInfo( u8 byMcuId, u8 m_byConfIdx )
{   
	u8 byLoop = 0;

	//����Mcu��
	while( byLoop < MAXNUM_SUB_MCU )
	{
		//�Ѵ��ڣ����ԭ����Ϣ
		if( m_atOtherMcMtInfo[byLoop].GetMcuId() == byMcuId )
		{
			memset( &m_atOtherMcMtInfo[byLoop], 0, sizeof(TConfMtInfo) );
			return TRUE;
		}
		byLoop++;
	}

	return FALSE;

}

/*====================================================================
    ������      ��GetAllJoinedMtNum
    ����        ���õ����������ṹ����������ն˸���
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����void
    ����ֵ˵��  �����м��������ն���
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    04/07/29    3.0         ������         ����
====================================================================*/
inline u16   TConfAllMtInfo::GetAllJoinedMtNum( void ) const
{
	u8 byLoop = 0;
	u16 wMtNum = 0;

	TConfMtInfo tConfMtInfo;

	//����Mc��
	while( byLoop < MAXNUM_SUB_MCU )
	{
		tConfMtInfo = m_atOtherMcMtInfo[byLoop];
		if( !tConfMtInfo.IsNull() )
		{
			wMtNum = wMtNum + m_atOtherMcMtInfo[byLoop].GetAllJoinedMtNum();
		}

		byLoop++;
	}

	//���ϱ�Mc���ն�
	wMtNum = wMtNum + m_tLocalMtInfo.GetAllJoinedMtNum();

	return wMtNum;
}

/*====================================================================
    ������      ��SetChnnlStatus
    ����        ������¼����ŵ�״̬��Ϣ������������¼�����ŵ����ٵ��ô˺���
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u8 byChnnlIndex, �ŵ�����
				  u8 byChnnlType, �ŵ����࣬TRecChnnlStatus::TYPE_RECORD��TYPE_PLAY
				  const TRecChnnlStatus * ptStatus, �ŵ�״̬���ں��ŵ�����
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    03/06/11    1.0         LI Yi         ����
====================================================================*/
inline BOOL TRecStatus::SetChnnlStatus( u8 byChnnlIndex, u8 byChnnlType, const TRecChnnlStatus * ptStatus )
{
	//record channel
	if( byChnnlType == TRecChnnlStatus::TYPE_RECORD )
	{
		if( byChnnlIndex < m_byRecChnnlNum )
		{
			m_tChnnlStatus[byChnnlIndex] = *ptStatus;
			return( TRUE );
		}
		else
		{
			OspPrintf( TRUE, FALSE, "TRecStatus: Exception - Wrong record channel index%u\n", byChnnlIndex ); 
			return( FALSE );
		}
	}
	else if( byChnnlType == TRecChnnlStatus::TYPE_PLAY )	//�����ŵ�
	{
		if( byChnnlIndex < m_byPlayChnnlNum )
		{
			m_tChnnlStatus[byChnnlIndex + m_byRecChnnlNum] = *ptStatus;
			return( TRUE );
		}
		else
		{
			OspPrintf( TRUE, FALSE, "TRecStatus: Exception - Wrong play channel index%u\n", byChnnlIndex ); 
			return( FALSE );
		}
	}
	else
	{
		OspPrintf( TRUE, FALSE, "TRecStatus: Exception - Wrong channel type%u\n", byChnnlType ); 
		return( FALSE );
	}
}

/*====================================================================
    ������      ��SetChnnlStatus
    ����        ������¼����ŵ�״̬��Ϣ������������¼�����ŵ����ٵ��ô˺���
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u8 byChnnlIndex, �ŵ�����
				  u8 byChnnlType, �ŵ����࣬TRecChnnlStatus::TYPE_RECORD��TYPE_PLAY
				  TRecChnnlStatus * ptStatus, �ŵ�״̬���ں��ŵ�����
    ����ֵ˵��  ��TRUE/FALSE
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    03/06/11    1.0         LI Yi         ����
====================================================================*/
inline BOOL TRecStatus::GetChnnlStatus( u8 byChnnlIndex, u8 byChnnlType, TRecChnnlStatus * ptStatus ) const
{
	//record channel
	if( byChnnlType == TRecChnnlStatus::TYPE_RECORD )
	{
		if( byChnnlIndex < m_byRecChnnlNum )
		{
			*ptStatus = m_tChnnlStatus[byChnnlIndex];
			return( TRUE );
		}
		else
		{
			OspPrintf( TRUE, FALSE, "TRecStatus: Exception - Wrong record channel index%u\n", byChnnlIndex ); 
			return( FALSE );
		}
	}
	else if( byChnnlType == TRecChnnlStatus::TYPE_PLAY )	//�����ŵ�
	{
		if( byChnnlIndex < m_byPlayChnnlNum )
		{
			*ptStatus = m_tChnnlStatus[byChnnlIndex + m_byRecChnnlNum];
			return( TRUE );
		}
		else
		{
			OspPrintf( TRUE, FALSE, "TRecStatus: Exception - Wrong play channel index%u\n", byChnnlIndex ); 
			return( FALSE );
		}
	}
	else
	{
		OspPrintf( TRUE, FALSE, "TRecStatus: Exception - Wrong channel type%u\n", byChnnlType ); 
		return( FALSE );
	}
}


/*====================================================================
    ������      ��IsMtIpInAllowSeg
    ����        ���ж�IP�Ƿ��ںϷ�����
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u32, IP ��ַ��������
    ����ֵ˵��  ��TRUE/FALSE
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    06/06/26    4.0         ����        ����
====================================================================*/
inline BOOL32 TUsrGrpInfo::IsMtIpInAllowSeg(u32 dwIp) const
{
/*
 *  ���´������� ͬʱ����������ͽ�ֹ�� 
 *  Ŀǰֻ��������һ��
 *  ����ʱע��
    BOOL32 bNoAllowed = TRUE; // �Ƿ������������

    for (u8 byLoop = 0; byLoop < MAXNUM_IPSEG; byLoop ++)
    {
        if ( atIpSegAllow[byLoop].IsEnabled() )
        {
            bNoAllowed = FALSE;
            break;
        }
    }

    // ���û����������Σ����һ�����еĽ�ֹ��
    if (bNoAllowed)
    {
        for (byLoop = 0; byLoop < MAXNUM_IPSEG; byLoop ++)
        {
            if ( atIpSegBan[byLoop].IsEnabled() )
            {
                if ( atIpSegBan[byLoop].IsIpIn( dwIp ) )
                {
                    // �����ڽ�ֹ��
                    return FALSE;
                }
            }
        }
        // ���ڽ�ֹ�Σ���Ϊ����
        return TRUE;
    }
    
    // �������������Σ��ȼ���Ƿ��������
    for (byLoop = 0; byLoop < MAXNUM_IPSEG; byLoop ++)
    {
        if ( atIpSegAllow[byLoop].IsEnabled() )
        {
            if ( atIpSegAllow[byLoop].IsIpIn( dwIp ) )
            {
                // ��ĳ������Σ����ٿ��Ƿ���С���ڲ���ֹ�θ���ֹ��
                for (u8 byLoop2 = 0; byLoop2 < MAXNUM_IPSEG; byLoop2 ++)
                {
                    if ( atIpSegBan[byLoop2].IsEnabled() )
                    {
                        if (atIpSegBan[byLoop2].IsIpIn( dwIp ))
                        {
                            // ȷʵ��ֹ����˭��ΧС˭��Ч
                            if ( atIpSegAllow[byLoop].IsIpSegIn( atIpSegBan[byLoop2] ) )
                            {
                                return FALSE;
                            }
                        }
                    }
                }
                // û�н�ֹ�ι涨
                return TRUE;
            }
        }
    }
*/

    if ( bBanned )
    {
        // �ڵ�ַ���в鿴�Ƿ��ں�������
        for (u8 byLoop = 0; byLoop < MAXNUM_IPSEG; byLoop ++)
        {
            if ( atIpSeg[byLoop].IsEnabled() && atIpSeg[byLoop].IsIpIn( dwIp ) )
            {
                return FALSE;                    
            }
        }
        return TRUE;
    }
    else
    {
        // �ڵ�ַ���в鿴�Ƿ��ڰ�������
        for (u8 byLoop = 0; byLoop < MAXNUM_IPSEG; byLoop ++)
        {
            if ( atIpSeg[byLoop].IsEnabled() && atIpSeg[byLoop].IsIpIn( dwIp ) )
            {
                return TRUE;                    
            }
        }
        return FALSE;
    }

    return FALSE;
}

//�ն���Ƶ���ƣ�Ŀǰ�Ƿֱ��ʣ����ʣ�
struct TMtVidLmt
{
public:
	void SetMtVidRes( u8 byRes)	{ m_byRes = byRes; }
	u8	 GetMtVidRes( void ){ return m_byRes;}	
	void SetMtVidBW( u16 wBandWidth){m_wBandWidth = wBandWidth;}
	u16	 GetMtVidBw( void ){ return m_wBandWidth;}

private:
	
	u16 m_wBandWidth;
	u8	m_byRes;
	u8  m_byReserve;

}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

/*==============================================================================
����    :  CVmpMemVidLmt
����    :  ����ϳɳ�Ա��Ƶ�ֱ��ʵ���������
��Ҫ�ӿ�:  
��ע    :  
-------------------------------------------------------------------------------
�޸ļ�¼:  
��  ��     �汾          �޸���          �߶���          �޸ļ�¼
2009-2-26
==============================================================================*/
class CVmpMemVidLmt
{
private:
	TMtVidLmt m_atMtVidLmtHd[VMP_STYLE_TWENTY +1][MAXNUM_MPUSVMP_MEMBER];  
 	TMtVidLmt m_atMtVidLmtStd[VMP_STYLE_TWENTY +1][MAXNUM_MPUSVMP_MEMBER];

public:
	CVmpMemVidLmt( void )
	{
		Init();
	}
	/*==============================================================================
	������    : GetMtVidLmtForHd 
	����      : �õ��ն˲���VMP�ֱ����������ֵ�����ڸ����նˣ� 
	�㷨ʵ��  :  
	����˵��  :  
	����ֵ˵��:  
	-------------------------------------------------------------------------------
	�޸ļ�¼  :  
	��  ��       �汾          �޸���          �߶���          �޸ļ�¼
	2009-2-20	4.6				Ѧ��							create
	==============================================================================*/
	BOOL32 GetMtVidLmtForHd ( u8 byStyle, u8 byMemPos, u8 &byMtRes, u16 &wMtBandWidth)
	{
		BOOL32 bRet = TRUE;
		byMtRes = m_atMtVidLmtHd[byStyle][byMemPos].GetMtVidRes();
		wMtBandWidth = m_atMtVidLmtHd[byStyle][byMemPos].GetMtVidBw();
		if(byMtRes == 0 || wMtBandWidth == 0)
		{
			bRet = FALSE;
		}
		return bRet;
	}
	
	/*==============================================================================
	������    : GetMtVidLmtForStd 
	����      : �õ��ն˲���VMP�ֱ����������ֵ�����ڱ����նˣ�
	�㷨ʵ��  :  
	����˵��  :  
	����ֵ˵��:  BOOL32
	-------------------------------------------------------------------------------
	�޸ļ�¼  :  
	��  ��       �汾          �޸���          �߶���          �޸ļ�¼
	2009-2-20	4.6				Ѧ��							create
	==============================================================================*/
	BOOL32 GetMtVidLmtForStd ( u8 byStyle, u8 byMemPos, u8 &byMtRes, u16 &wMtBandWidth)
	{
		BOOL32 bRet = TRUE;
		byMtRes = m_atMtVidLmtStd[byStyle][byMemPos].GetMtVidRes();
		wMtBandWidth = m_atMtVidLmtStd[byStyle][byMemPos].GetMtVidBw();
		if(byMtRes == 0 || wMtBandWidth == 0)
		{
			bRet = FALSE;
		}
		return bRet;
	}

	void Init( void )
	{
		u8 byStyle = 0;
		u8 byLoop = 0;
		memset( m_atMtVidLmtHd, 0, sizeof( m_atMtVidLmtHd ) );
		memset( m_atMtVidLmtStd, 0, sizeof( m_atMtVidLmtStd ) );
		const u16 wBW_8M = 8192;
		const u16 wBW_3M = 3072;
		const u16 wBW_1d5M = 1536;
		
		byStyle = VMP_STYLE_ONE;	//1����
		m_atMtVidLmtHd[byStyle][0].SetMtVidRes(VIDEO_FORMAT_HD1080);
		m_atMtVidLmtHd[byStyle][0].SetMtVidBW(wBW_8M);
		
		m_atMtVidLmtStd[byStyle][0].SetMtVidRes(VIDEO_FORMAT_4SIF);
		m_atMtVidLmtStd[byStyle][0].SetMtVidBW(wBW_8M);

		byStyle = VMP_STYLE_VTWO;	//����2����
		for(byLoop = 0; byLoop < 2;byLoop ++)
		{
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_720_960x544);
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidBW(wBW_8M);

			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_4SIF);
			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidBW(wBW_8M);
		}

		
		byStyle = VMP_STYLE_HTWO;	//һ��һС2����
		m_atMtVidLmtHd[byStyle][0].SetMtVidRes(VIDEO_FORMAT_HD1080);
		m_atMtVidLmtHd[byStyle][0].SetMtVidBW(wBW_8M);
		m_atMtVidLmtHd[byStyle][1].SetMtVidRes(VIDEO_FORMAT_640x368);
		m_atMtVidLmtHd[byStyle][1].SetMtVidBW(wBW_3M);
		
		m_atMtVidLmtStd[byStyle][0].SetMtVidRes(VIDEO_FORMAT_4SIF);
		m_atMtVidLmtStd[byStyle][0].SetMtVidBW(wBW_8M);
		m_atMtVidLmtStd[byStyle][1].SetMtVidRes(VIDEO_FORMAT_CIF);
		m_atMtVidLmtStd[byStyle][1].SetMtVidBW(wBW_1d5M);

		byStyle = VMP_STYLE_THREE;	//3����
		for(byLoop = 0; byLoop < 3; byLoop ++)
		{	
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_960x544);
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidBW(wBW_8M);

			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_4SIF);
			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidBW(wBW_8M);
		}
		
		
		byStyle = VMP_STYLE_FOUR;	//4����
		for(byLoop = 0; byLoop < 4; byLoop ++)
		{	
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_960x544);
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidBW(wBW_8M);

			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_4SIF);
			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidBW(wBW_8M);
		}

		
		byStyle = VMP_STYLE_SIX;	//6����
		m_atMtVidLmtHd[byStyle][0].SetMtVidRes(VIDEO_FORMAT_HD720);
		m_atMtVidLmtHd[byStyle][0].SetMtVidBW(wBW_8M);

		m_atMtVidLmtStd[byStyle][0].SetMtVidRes(VIDEO_FORMAT_4SIF);
		m_atMtVidLmtStd[byStyle][0].SetMtVidBW(wBW_8M);

		for(byLoop = 1; byLoop < 6; byLoop ++)
		{	
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_640x368);
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidBW(wBW_3M);

			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_CIF);
			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidBW(wBW_1d5M);
		}

		
		byStyle = VMP_STYLE_EIGHT;	//8����
		m_atMtVidLmtHd[byStyle][0].SetMtVidRes(VIDEO_FORMAT_1440x816);
		m_atMtVidLmtHd[byStyle][0].SetMtVidBW(wBW_8M);

		m_atMtVidLmtStd[byStyle][0].SetMtVidRes(VIDEO_FORMAT_4SIF);
		m_atMtVidLmtStd[byStyle][0].SetMtVidBW(wBW_8M);

		for(byLoop = 1; byLoop < 8; byLoop ++)
		{	
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_480x272);
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidBW(wBW_1d5M);

 			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_CIF);
 			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidBW(wBW_1d5M);
		}

		
		byStyle = VMP_STYLE_NINE;	//9����
		for(byLoop = 0; byLoop < 9; byLoop ++)
		{	
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_640x368);
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidBW(wBW_3M);

			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_CIF);
			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidBW(wBW_1d5M);
		}

				
		byStyle = VMP_STYLE_TEN;	//10����
		m_atMtVidLmtHd[byStyle][0].SetMtVidRes(VIDEO_FORMAT_960x544);
		m_atMtVidLmtHd[byStyle][0].SetMtVidBW(wBW_8M);
		m_atMtVidLmtHd[byStyle][5].SetMtVidRes(VIDEO_FORMAT_960x544);
		m_atMtVidLmtHd[byStyle][5].SetMtVidBW(wBW_8M);

		m_atMtVidLmtStd[byStyle][0].SetMtVidRes(VIDEO_FORMAT_4SIF);
		m_atMtVidLmtStd[byStyle][0].SetMtVidBW(wBW_8M);
		m_atMtVidLmtStd[byStyle][5].SetMtVidRes(VIDEO_FORMAT_4SIF);
		m_atMtVidLmtStd[byStyle][5].SetMtVidBW(wBW_8M);

		for(byLoop = 1; byLoop < 5; byLoop ++)
		{	
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_480x272);
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidBW(wBW_1d5M);

			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_CIF);
			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidBW(wBW_1d5M);
		}
		for(byLoop = 6; byLoop < 10; byLoop ++)
		{	
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_480x272);
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidBW(wBW_1d5M);

			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_CIF);
			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidBW(wBW_1d5M);
		}
		
		byStyle = VMP_STYLE_THIRTEEN;//13����
		m_atMtVidLmtHd[byStyle][0].SetMtVidRes(VIDEO_FORMAT_960x544);
		m_atMtVidLmtHd[byStyle][0].SetMtVidBW(wBW_8M);

		m_atMtVidLmtStd[byStyle][0].SetMtVidRes(VIDEO_FORMAT_4SIF);
		m_atMtVidLmtStd[byStyle][0].SetMtVidBW(wBW_8M);

		for(byLoop = 1; byLoop < 13; byLoop ++)
		{	
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_480x272);
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidBW(wBW_1d5M);

			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_CIF);
			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidBW(wBW_1d5M);
		}

				
		byStyle = VMP_STYLE_SIXTEEN;//16����
		for(byLoop = 0; byLoop < 16; byLoop ++)
		{	
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_480x272);
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidBW(wBW_1d5M);

			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_CIF);
			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidBW(wBW_1d5M);
		}

		
		byStyle = VMP_STYLE_SPECFOUR;//����4����
		m_atMtVidLmtHd[byStyle][0].SetMtVidRes(VIDEO_FORMAT_HD720);
		m_atMtVidLmtHd[byStyle][0].SetMtVidBW(wBW_8M);

		m_atMtVidLmtStd[byStyle][0].SetMtVidRes(VIDEO_FORMAT_4SIF);
		m_atMtVidLmtStd[byStyle][0].SetMtVidBW(wBW_8M);

		for(byLoop = 1; byLoop < 4; byLoop ++)
		{	
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_640x368);
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidBW(wBW_3M);

			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_CIF);
			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidBW(wBW_1d5M);
		}


		byStyle = VMP_STYLE_SEVEN;	//7����
		for(byLoop = 0; byLoop < 3; byLoop ++)
		{	
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_960x544);
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidBW(wBW_8M);

			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_4SIF);
			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidBW(wBW_8M);
		}
		for(byLoop = 3; byLoop < 7; byLoop ++)
		{	
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_480x272);
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidBW(wBW_1d5M);

			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_CIF);
			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidBW(wBW_1d5M);
		}

	    
		byStyle = VMP_STYLE_TWENTY; //20����
		for(byLoop = 0; byLoop < 20; byLoop ++)
		{	
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_480x272);
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidBW(wBW_1d5M);

			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_CIF);
			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidBW(wBW_1d5M);
		}
	}

};
// MCU 8000B ���������߼�
// ʹ�þ�̬�෽���ṩ�����ӿ�
// Ҫʹ����Щ�ӿ�, �������ֻ���� ʵ���ļ�mcupfmlmt.h ͷ�ļ�һ��
// MCS �յ����ṹ�������б���,��MCU�л������ CMcuPfmLmt::SetFilter() �ӿ�����
struct TMcu8kbPfmFilter
{
    TMcu8kbPfmFilter()
    {
        byMaxNumMixSingleMp3   = MAXNUM_MIX_SINGLE_MP3;     
        byMaxNumMixMultiMp3    = MAXNUM_MIX_MULTI_MP3;
        byMaxNumMixSingleG729  = MAXNUM_MIX_SINGLE_G729;
        byMaxNumMixMultiG729   = MAXNUM_MIX_MULTI_G729;
        byMaxNumVacSingleMp3   = MAXNUM_VAC_SINGLE_MP3;
        byMaxNumVacMultiMp3    = MAXNUM_VAC_MULTI_MP3; 
        byMaxNumVacSingleG729  = MAXNUM_VAC_SINGLE_G729;
        byMaxNumVacMultiG729   = MAXNUM_VAC_MULTI_G729;

        byEnable               = 1; 
    }

    void Print() const
    {
        OspPrintf(TRUE, FALSE, "TMcu8kbPfmFilter:\n");
        OspPrintf(TRUE, FALSE, "\t IsEnable: %d\n", byEnable);
        OspPrintf(TRUE, FALSE, "\t byMaxNumMixSingleMp3: %d\n", byMaxNumMixSingleMp3);
        OspPrintf(TRUE, FALSE, "\t byMaxNumMixMultiMp3: %d\n", byMaxNumMixMultiMp3);
        OspPrintf(TRUE, FALSE, "\t byMaxNumMixSingleG729: %d\n", byMaxNumMixSingleG729);
        OspPrintf(TRUE, FALSE, "\t byMaxNumMixMultiG729: %d\n", byMaxNumMixMultiG729);
        OspPrintf(TRUE, FALSE, "\t byMaxNumVacSingleMp3: %d\n", byMaxNumVacSingleMp3);
        OspPrintf(TRUE, FALSE, "\t byMaxNumVacMultiMp3: %d\n", byMaxNumVacMultiMp3);
        OspPrintf(TRUE, FALSE, "\t byMaxNumVacSingleG729: %d\n", byMaxNumVacSingleG729);
        OspPrintf(TRUE, FALSE, "\t byMaxNumVacMultiG729: %d\n", byMaxNumVacMultiG729);
    }

    BOOL32 IsEnable() const
    {
        return (byEnable != 0 ? TRUE : FALSE);
    }

public:
    u8 byMaxNumMixSingleMp3; //MP3����(���ƺ�����)��������
    u8 byMaxNumMixMultiMp3;  //MP3����(���ƺ�����)������(VMP��BAS)�쿪����
    u8 byMaxNumMixSingleG729;//G729����(���ƺ�����)��������;
    u8 byMaxNumMixMultiG729; //G729����(���ƺ�����)������(VMP��BAS)�쿪����
    u8 byMaxNumVacSingleMp3; //MP3��VAC��������
    u8 byMaxNumVacMultiMp3;  //MP3��VAC������(BAS)�쿪����
    u8 byMaxNumVacSingleG729;//G729��VAC��������;
    u8 byMaxNumVacMultiG729; //G729��VAC������(BAS)�쿪����
private:
    u8 byEnable;             //�Ƿ�����

}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

class CMcuPfmLmt
{
public:
    /*=============================================================================
        �� �� ���� GetMaxVmpStyle
        ��    �ܣ� �жϵ�ǰVMP���֧�ֵĻ���ϳ�·��
        �㷨ʵ�֣� 
        ȫ�ֱ����� 
        ��    ���� TConfInfo &tConfInfo         [in]  ���������Ϣ
                   u8 byMtNum                   [in]  �����ն�����
                   u8 byMixingMtNum             [in]  ���ڲ������(���ܻ���)���ն�����
                   u16 &wError                  [out] ���صĴ�����
        �� �� ֵ�� BOOL32
        ----------------------------------------------------------------------
        �޸ļ�¼    ��
        ��  ��		�汾		�޸���		�߶���    �޸�����
        2007/01/29  4.0			����                  ����
    =============================================================================*/
    static u8 GetMaxOprVmpStyle( const TConfInfo &tConfInfo, u8 byMtNum, u8 byMixingMtNum, u16 &wError );
	
    /*=============================================================================
        �� �� ���� GetMaxOprMixNum
        ��    �ܣ� �жϵ�ǰ��������õĻ���(�������ƺ�����)�ն���
        �㷨ʵ�֣� 
        ȫ�ֱ����� 
        ��    ���� TConfInfo &tConfInfo     [in]  ������Ϣ
        �� �� ֵ�� BOOL32
        ----------------------------------------------------------------------
        �޸ļ�¼    ��
        ��  ��		�汾		�޸���		�߶���    �޸�����
        2007/01/29  4.0			����                  ����
    =============================================================================*/
    static u8 GetMaxOprMixNum( const TConfInfo &tConfInfo, u16 &wError );

    /*=============================================================================
        �� �� ���� GetMaxDynVmpStyle
        ��    �ܣ� ��ȡ��ǰ��֧�ֵĶ�̬�ϳɷ��
        �㷨ʵ�֣� 
        ȫ�ֱ����� 
        ��    ���� TConfInfo &tConfInfo         [in]  ���������Ϣ
                   u8 byMtNum                   [in]  �����ն�����
                   u8 byMixingMtNum             [in]  ���ڲ������(���ܻ���)���ն�����
                   u16 &wError                  [out] ���صĴ�����
        �� �� ֵ�� BOOL32
        ˵��    �� MCS��֧��ʹ�ñ�����
        ----------------------------------------------------------------------
        �޸ļ�¼    ��
        ��  ��		�汾		�޸���		�߶���    �޸�����
        2007/01/31  4.0			����                  ����
    =============================================================================*/    
    static u8 GetMaxDynVmpStyle( const TConfInfo &tConfInfo, u8 byMtNum, u8 byMixingMtNum, u16 &wError );
    
    /*=============================================================================
        �� �� ���� IsVmpOprSupported
        ��    �ܣ� �жϵ�ǰ��VMP�����ܷ����
        �㷨ʵ�֣� 
        ȫ�ֱ����� 
        ��    ���� TConfInfo &tConfInfo         [in]  ���������Ϣ
                   u8 byNewStyle                [in]  �µ�VMP�����ķ��
                   u8 byMtNum                   [in]  �����ն�����
                   u8 byMixingMtNum             [in]  ���ڲ������(���ܻ���)���ն�����
                   u16 &wError                  [out] ���صĴ�����
        �� �� ֵ�� BOOL32
        ----------------------------------------------------------------------
        �޸ļ�¼    ��
        ��  ��		�汾		�޸���		�߶���    �޸�����
        2007/01/25  4.0			�ű���                  ����
    =============================================================================*/    
    static BOOL32 IsVmpOprSupported( const TConfInfo &tConfInfo, u8 byNewStyle, u8 byMtNum, u8 byMixingMtNum, u16 &wError );

    /*=============================================================================
        �� �� ���� IsMixOprSupported
        ��    �ܣ� �жϵ�ǰ�Ķ��ƻ��������ܷ����
        �㷨ʵ�֣� 
        ȫ�ֱ����� 
        ��    ���� TConfInfo &tConfInfo         [in]  ������Ϣ
                   u8 byMixingMtNum             [in]  ���ڲ������(���ܻ���)���ն�����
                   u8 byAddNum                  [in]  Ҫ��ӽ��������ն�����
                   u16 &wError                  [out] ���صĴ�����
        �� �� ֵ�� BOOL32
        ----------------------------------------------------------------------
        �޸ļ�¼    ��
        ��  ��		�汾		�޸���		�߶���    �޸�����
        2007/01/25  4.0			�ű���                  ����
    =============================================================================*/
    static BOOL32 IsMixOprSupported( const TConfInfo &tConfInfo, u8 byMixingNum, u8 byAddNum, u16 &wError );

    /*=============================================================================
        �� �� ���� IsVacOprSupported
        ��    �ܣ� �жϿ���VAC�Ƿ��ܱ�����
        �㷨ʵ�֣� 
        ȫ�ֱ����� 
        ��    ���� TConfInfo &tConfInfo   [in]  ������Ϣ
                   u8        byMtNum      [in]  ���鵱ǰ�����������ն���
                   u16 &wError            [out] ���صĴ�����
        �� �� ֵ�� BOOL32
        ----------------------------------------------------------------------
        �޸ļ�¼    ��
        ��  ��		�汾		�޸���		�߶���    �޸�����
        2007/01/30  4.0			����                  ����
    =============================================================================*/    
    static BOOL32 IsVacOprSupported( const TConfInfo &tConfInfo, u8 byMtNum, u16 &wError );

    /*=============================================================================
        �� �� ���� IsBasOprSupported
        ��    �ܣ� �жϿ���BAS�Ƿ��ܱ�����
        �㷨ʵ�֣� 
        ȫ�ֱ����� 
        ��    ���� TConfInfo &tConfInfo   [in]  ������Ϣ
                   u8        byMixNum     [in]  ���鵱ǰ�Ļ����ն���
                   u16 &wError            [out] ���صĴ�����
        �� �� ֵ�� BOOL32
        ----------------------------------------------------------------------
        �޸ļ�¼    ��
        ��  ��		�汾		�޸���		�߶���    �޸�����
        2007/01/30  4.0			����                  ����
    =============================================================================*/   
    static BOOL32 IsBasOprSupported( const TConfInfo &tConfInfo, u8 byMixNum, u16 &wError );
    
    /*=============================================================================
        �� �� ���� IsMtOprSupported
        ��    �ܣ� �жϵ�ǰ�������ն��Ƿ��ܱ�����
        �㷨ʵ�֣� 
        ȫ�ֱ����� 
        ��    ���� TConfInfo &tConfInfo   [in]  ������Ϣ
                   u8        byMtNum      [in]  ���鵱ǰ�����������ն���
                   u8        byMixNum     [in]  ���ڻ���(���ܡ�����)�ն���
                   u16 &wError            [out] ���صĴ�����
        �� �� ֵ�� BOOL32
        ----------------------------------------------------------------------
        �޸ļ�¼    ��
        ��  ��		�汾		�޸���		�߶���    �޸�����
        2007/01/26  4.0			�ű���                  ����
    =============================================================================*/
    static BOOL32 IsMtOprSupported( const TConfInfo &tConfInfo, u8 byMtNum, u8 byMixNum, u16 &wError );

    /*=============================================================================
        �� �� ���� SetFilter
        ��    �ܣ� �����������ƵĹ��˲���
        �㷨ʵ�֣� 
        ȫ�ֱ����� 
        ��    ���� TMcu8kbPfmFilter& tNewFilter   [in]  �µĲ���������û������ã���ȱʡ���켴��
        �� �� ֵ�� 
        ----------------------------------------------------------------------
        �޸ļ�¼    ��
        ��  ��		�汾		�޸���		�߶���    �޸�����
        2007/01/30  4.0			����                  ����
    =============================================================================*/
    static void SetFilter(const TMcu8kbPfmFilter& tNewFilter)
    {
        m_tFilter = tNewFilter;
    }

	/*=============================================================================
        �� �� ���� GetFilter
        ��    �ܣ� �����������ƵĹ��˲���
        �㷨ʵ�֣� 
        ȫ�ֱ����� 
        ��    ���� ��
        �� �� ֵ�� TMcu8kbPfmFilter
        ----------------------------------------------------------------------
        �޸ļ�¼    ��
        ��  ��		�汾		�޸���		�߶���    �޸�����
        2007/02/07  4.0			�ܹ��                  ����
    =============================================================================*/
    static TMcu8kbPfmFilter GetFilter()
    {
        return m_tFilter;
    }

    /* ���º�������MCU8000A, ���ܹ�����Լ�� */
	/*=============================================================================
	�� �� ���� IsVmpStyleSupport
	��    �ܣ� �ж�ĳ������ϳɣ������໭�����ǽ��������Ŀ�����Ƿ���֧�֣�MCU8000A��
	�㷨ʵ�֣� 
	ȫ�ֱ����� 
	��    ���� const TConfInfo &tConfInfo   [in] ������Ϣ
			   u8 byConfIdx                 [in] ����ConfIdx��Ϣ
			   TPeriEqpStatus *ptVmpStatus  [in] ����״̬����
			   u16 wLen                     [in] ����״̬���鳤��
			   u8 byTargetStyle             [in] ָ����Ŀ����
			   u8 &bySelVmpId               [out] ���ط���������Vmp��VmpTw
	�� �� ֵ�� BOOL32 �Ƿ���֧��
	----------------------------------------------------------------------
	�޸ļ�¼    ��
	��  ��		�汾		�޸���		�߶���    �޸�����
	2007/7/13   4.0			�ܹ��      ����      ����
	=============================================================================*/
	static BOOL32 IsVmpStyleSupport( const TConfInfo &tConfInfo, u8 byConfIdx, 
							   	     TPeriEqpStatus *ptVmpStatus, u16 wLen, 
								     u8 byTargetStyle, u8 &bySelVmpId );

	/*=============================================================================
	�� �� ���� GetSupportedVmpStyles
	��    �ܣ� ����ָ�������ܹ�֧�ֵ����л���ϳɷ��
	�㷨ʵ�֣� 
	ȫ�ֱ����� 
	��    ����   const TConfInfo &tConfInfo   [in] ������Ϣ
				 u8 byConfIdx                 [in] ����ConfIdx��Ϣ
				 TPeriEqpStatus *ptVmpStatus  [in] ����״̬����
				 u16 wLen                     [in] ����״̬���鳤��
				 u8 *pabStyle                 [out] ���صķ������
				 u8 &byStyleSize              [I/O] ��������Ĵ�С��ͬʱ����ʵ�ʴ�С��
													���ʵ�ʷ���ֵ���ڴ���ֵ����˵���ռ䲻����ͬʱ���������û�н������
	�� �� ֵ�� void 
	----------------------------------------------------------------------
	�޸ļ�¼    ��
	��  ��		�汾		�޸���		�߶���    �޸�����
	2007/7/13   4.0			�ܹ��      ����      ����
	=============================================================================*/
	static void GetSupportedVmpStyles( const TConfInfo &tConfInfo, u8 byConfIdx, 
										TPeriEqpStatus *ptVmpStatus, u16 wLen, 
										u8 *pabyStyle, u8 &byArraySize );

	/*=============================================================================
	�� �� ���� GetMaxCapVMPByConfInfo
	��    �ܣ� �����ݻ�����Ϣ���㵱ǰ�������֧�ֵĻ���ϳɻ�໭�����ǽ·����MCU8000A��		   
	�㷨ʵ�֣� 
	ȫ�ֱ����� 
	��    ���� const TConfInfo &tConfInfo
	�� �� ֵ�� BOOL32 
	----------------------------------------------------------------------
	�޸ļ�¼    ��
	��  ��		�汾		�޸���		�߶���    �޸�����
	2007/7/14   4.0			����      ����������������
	=============================================================================*/
    static u8 GetMaxCapVMPByConfInfo( const TConfInfo &tConfInfo );

    /*=============================================================================
	�� �� ���� IsConfFormatHD
	��    �ܣ� �������Ƿ�Ϊ������飬����H.264��Ч
	�㷨ʵ�֣� 
	ȫ�ֱ����� 
    ��    ���� const TConfInfo &tConfInfo   [in] ������Ϣ
	�� �� ֵ�� BOOL32
	----------------------------------------------------------------------
	�޸ļ�¼    ��
	��  ��		�汾		�޸���		�߶���    �޸�����
	2007/12/19  4.0			�ű���                  ����
	=============================================================================*/
    static BOOL32 IsConfFormatHD( const TConfInfo &tConfInfo );

    /*=============================================================================
	�� �� ���� IsConfFormatOverCif
	��    �ܣ� �������Ƿ�ΪD1���߸�����飬����H.264��Ч
	�㷨ʵ�֣� 
	ȫ�ֱ����� 
    ��    ���� const TConfInfo &tConfInfo   [in] ������Ϣ
	�� �� ֵ�� BOOL32 �����H.264����ʽ���������FALSE
	----------------------------------------------------------------------
	�޸ļ�¼    ��
	��  ��		�汾		�޸���		�߶���    �޸�����
	2008/03/11  4.5			����                  ����
	=============================================================================*/
    static BOOL32 IsConfFormatOverCif( const TConfInfo &tConfInfo );

	/*=============================================================================
	�� �� ���� IsConfPermitVmp
	��    �ܣ� �������Ƿ�������ϳ�
	�㷨ʵ�֣� 
	ȫ�ֱ����� 
    ��    ���� const TConfInfo &tConfInfo   [in] ������Ϣ
	�� �� ֵ�� BOOL32 �����H.264����ʽ���������FALSE
	----------------------------------------------------------------------
	�޸ļ�¼    ��
	��  ��		�汾		�޸���		�߶���    �޸�����
	2008/03/11  4.5			����                  ����
	=============================================================================*/
    static BOOL32 IsConfPermitVmp( const TConfInfo &tConfInfo );

    /*=============================================================================
	�� �� ���� IsRollCallSupported
	��    �ܣ� �������Ƿ�֧�ֻ������
	�㷨ʵ�֣� 
	ȫ�ֱ����� 
    ��    ���� const TConfInfo &tConfInfo   [in] ������Ϣ
	�� �� ֵ�� BOOL32
	----------------------------------------------------------------------
	�޸ļ�¼    ��
	��  ��		�汾		�޸���		�߶���    �޸�����
	2007/12/19  4.0			�ű���                  ����
	=============================================================================*/
    static BOOL32 IsRollCallSupported( const TConfInfo &tConfInfo );

	/*=============================================================================
	�� �� ���� IsVmpSupported
	��    �ܣ� �������Ƿ�֧�ֻ���ϳ���
	�㷨ʵ�֣� 
	ȫ�ֱ����� 
    ��    ���� const TConfInfo &tConfInfo   [in] ������Ϣ
	�� �� ֵ�� BOOL32
	----------------------------------------------------------------------
	�޸ļ�¼    ��
	��  ��		�汾		�޸���		�߶���    �޸�����
	2007/12/19  4.0			�ű���                  ����
	=============================================================================*/
    static BOOL32 IsVmpSupported( const TConfInfo &tConfInfo );
    
    /*=============================================================================
	�� �� ���� IsMPWSupported
	��    �ܣ� �������Ƿ�֧�ֶ໭�����ǽ
	�㷨ʵ�֣� 
	ȫ�ֱ����� 
    ��    ���� const TConfInfo &tConfInfo   [in] ������Ϣ
	�� �� ֵ�� BOOL32
	----------------------------------------------------------------------
	�޸ļ�¼    ��
	��  ��		�汾		�޸���		�߶���    �޸�����
	2007/12/19  4.0			�ű���                  ����
	=============================================================================*/
    static BOOL32 IsMPWSupported( const TConfInfo &tConfInfo );
    
    /*=============================================================================
	�� �� ���� IsTVWallSupported
	��    �ܣ� �������Ƿ�֧�ֵ���ǽ
	�㷨ʵ�֣� 
	ȫ�ֱ����� 
    ��    ���� const TConfInfo &tConfInfo   [in] ������Ϣ
	�� �� ֵ�� BOOL32
	----------------------------------------------------------------------
	�޸ļ�¼    ��
	��  ��		�汾		�޸���		�߶���    �޸�����
	2007/12/19  4.0			�ű���                  ����
	=============================================================================*/
    static BOOL32 IsTVWallSupported( const TConfInfo &tConfInfo );
    
    /*=============================================================================
	�� �� ���� IsMultiVidStreamSupported
	��    �ܣ� �������Ƿ�֧����Ƶ���ٶ��ʽ
	�㷨ʵ�֣� 
	ȫ�ֱ����� 
    ��    ���� const TConfInfo &tConfInfo   [in] ������Ϣ
               u8 byMode = MODE_VIDEO       [in] ��Ƶ����Ƶ,��֧��MODE_BOTH
	�� �� ֵ�� BOOL32
	----------------------------------------------------------------------
	�޸ļ�¼    ��
	��  ��		�汾		�޸���		�߶���    �޸�����
	2007/12/19  4.0			�ű���                  ����
	=============================================================================*/
    static BOOL32 IsMultiStreamSupported( const TConfInfo &tConfInfo, u8 byMode = MODE_VIDEO );

private:
	/*=============================================================================
	�� �� ���� GetMaxCapVMP
	��    �ܣ� ���㵱ǰ�������֧�ֵĻ���ϳɻ�໭�����ǽ·���Լ���Ӧ���豸ID��MCU8000A��			   
	�㷨ʵ�֣� 
	ȫ�ֱ����� 
	��    ���� const TConfInfo &tConfInfo
			   TPeriEqpStatus *ptVmpStatus : VMP/VMPTW ״̬����
			   u16 wlen : ״̬���鳤��
			   u8 &byVmpCapChnnlNum [OUT]: 
			   u8 &bySelVmpId[OUT]:
	�� �� ֵ�� BOOL32 
	----------------------------------------------------------------------
	�޸ļ�¼    ��
	��  ��		�汾		�޸���		�߶���    �޸�����
	2007/6/20   4.0			�ܹ��      ����      ����
	=============================================================================*/
	static BOOL32 GetMaxCapVMP( const TConfInfo &tConfInfo, u8 byConfIdx, 
								TPeriEqpStatus *ptVmpStatus, u16 wLen, 
								u8 &byVmpCapChnnlNum, 
                                u8 &bySelVmpId, 
								u8 byTargetStyle = 0	//0���Զ����
								);

	/*=============================================================================
	�� �� ���� GetSupportedVmpStyles
	��    �ܣ� �����ܹ�֧�ֵ����л���ϳɷ��MCU8000A��
	�㷨ʵ�֣� 
	ȫ�ֱ����� 
	��    ���� const TConfInfo &tConfInfo
			   u8 byEqpType
			   u8 bySubType
			   u8 byCapChnnlNum             
			   u8 byVmpMaxChnnlNum
               u8 *pabyStyle                [out] ���صķ������
               u8 &byArraySize              [I/O] ��������Ĵ�С��ͬʱ����ʵ�ʴ�С��
                                                  ���ʵ�ʷ���ֵ���ڴ���ֵ����˵���ռ䲻����ͬʱ���������û�н������
	�� �� ֵ�� void 
	----------------------------------------------------------------------
	�޸ļ�¼    ��
	��  ��		�汾		�޸���		�߶���    �޸�����
	2007/7/13   4.0			�ܹ��      ����      ����
	2009/2/18	4.6			Ѧ��					����������VMP���ࣻ����20���
	=============================================================================*/
	static void GetSupportedVmpStyles( const TConfInfo &tConfInfo, u8 byEqpType, u8 bySubType,u8 byCapChnnlNum, u8 byVmpMaxChnnlNum, 
                                       u8 *pabyStyle, u8 &byArraySize );
	/*=============================================================================
	�� �� ���� GetSelVmpCap
	��    �ܣ� ��ȡ��ӽ�����������vmp id��������
	�㷨ʵ�֣� 
	ȫ�ֱ����� 
	��    ���� u8 abySelVmpIdx[]				[in] 
	TPeriEqpStatus *ptStatus		[in] 
	u8 bySelNum						[in]
	u8 byMaxChnlNumByConf			[in]
	u8 &byVmpCapChnnlNum			[out]
	u8 &bySelVmpId					[out]
	�� �� ֵ�� BOOL32
	----------------------------------------------------------------------
	�޸ļ�¼    ��
	��  ��		�汾		�޸���		�߶���    �޸�����
	12/9/2008				Ѧ��					
	=============================================================================*/
	static BOOL32 GetSelVmpCap(u8 abySelVmpIdx[], TPeriEqpStatus *ptStatus, u8 bySelNum, 
		u8 byMaxChnlNumByConf,u8 &byVmpCapChnnlNum, u8 &bySelVmpId);
	
	

private:
    static TMcu8kbPfmFilter m_tFilter;
};

// xliang [3/18/2009] VMP ռ����ǰ����ͨ������Ҫ������ǰ����ͨ����δռ�ɹ����ն���Ϣ
struct TVmpHdChnnlMemInfo
{
public:
	TMt	tMtInHdChnnl[MAXNUM_SVMPB_HDCHNNL];
	TMt	tMtOutHdChnnl[MAXNUM_MPUSVMP_MEMBER];
public:
	TVmpHdChnnlMemInfo( void )
	{
		init();
	}
	void init()
	{
		memset(tMtInHdChnnl,0, sizeof(tMtInHdChnnl));
		memset(tMtOutHdChnnl,0,sizeof(tMtOutHdChnnl));
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// xliang [11/28/2008]VMP ͨ����Ա��Ϣ
struct TChnnlMemberInfo 
{
	enum EmChnnlPriMask
    {
        Mask_BeSelected		=   0x0001,
		Mask_NoneKeda		=   0x0002,
		Mask_Speaker		=   0x0004,
    };
public:
//	u8	m_byMtId;			//ռ��ͨ����MT ID
	TMt m_tSeizedMt;		//ռ��ͨ����MT
	u8	m_byVmpPRIAttr;		//���ȼ�����
	u8  m_byReserved1;		//Ԥ��
	u8  m_byReserved2;		//Ԥ��
public:
	TChnnlMemberInfo(void)
	{
		SetNull();
	}
	void SetNull()
	{
		//m_byMtId = 0;
		m_tSeizedMt.SetNull();
		m_byVmpPRIAttr = 0;
	}
	void SetAttrNull()
	{
		m_byVmpPRIAttr = 0;
	}
	void SetAttrSelected()
	{
		m_byVmpPRIAttr |= Mask_BeSelected;
	}
	void SetAttrNoneKeda()
	{
		m_byVmpPRIAttr |= Mask_NoneKeda;
	}
	void SetAttrSpeaker()
	{
		m_byVmpPRIAttr |= Mask_Speaker;
	}
	BOOL32 IsAttrSpeaker() const
	{
		return ( (m_byVmpPRIAttr & Mask_Speaker) != 0 );
	}
	BOOL32 IsAttrNoneKeda() const
	{
		return ( (m_byVmpPRIAttr & Mask_NoneKeda) != 0 );
	}
	BOOL32 IsAttrSelected() const
	{
		return ( (m_byVmpPRIAttr & Mask_BeSelected) != 0 );
	}
	
	u8 GetMtId( void ) const
	{
		return m_tSeizedMt.GetMtId();
	}
	TMt GetMt(void) const
	{
		return m_tSeizedMt;
	}
	void SetMt(TMt tMt)
	{
		m_tSeizedMt = tMt;
	}
}	
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;
//vmp��ͨ����Ϣ
struct TVmpChnnlInfo
{	
public:
	u8 m_byHDChnnlNum;		//����ͨ����ռ��Ŀ
	u8 m_by4CifChnnlNum;
	u8 m_byCifChnnlNum;		//Ŀǰ����
	u8 m_byAllChnnlNum;		//���б��õ�ͨ������Ŀǰ����
	u8 m_byHdChnnlIdx;		//ͨ��idx
	TChnnlMemberInfo	m_tHdChnnlInfo[MAXNUM_SVMPB_HDCHNNL];
//	TChnnlMemberInfo	t4CifChnnlInfo[MAX_SVMP_4CIFCHNNLNUM];
//	TChnnlMemberInfo	tCifChnnlInfo[MAX_SVMP_CIFCHNNLNUM];
public:
	TVmpChnnlInfo(void)
	{
		clear();
	}
	void clear()
	{
		SetHDChnnlNum(0);
		Set4CifChnnlNum(0);
		SetCifChnnlNum(0);
		SetAllChnnlNum(0);
		memset(m_tHdChnnlInfo,0,sizeof(m_tHdChnnlInfo));

	}
	void SetHDChnnlNum(u8 byHDChnnlNum){m_byHDChnnlNum = byHDChnnlNum;}
	u8	 GetHDChnnlNum( void ){ return m_byHDChnnlNum; }
	void Set4CifChnnlNum(u8 by4CifChnnlNum){m_by4CifChnnlNum = by4CifChnnlNum;}
	void SetCifChnnlNum(u8 byCifChnnlNum){m_byCifChnnlNum = byCifChnnlNum;}
	u8	 GetCifChnnlNum( void ){ return m_byCifChnnlNum; }
	void SetAllChnnlNum(u8 byAllChnnlNum){m_byAllChnnlNum = byAllChnnlNum;}
	
	void SetHdChnnlInfo(u8 byChnnlIdx,const TChnnlMemberInfo *ptChnnlMemberInfo)
	{
		m_tHdChnnlInfo[byChnnlIdx] = *ptChnnlMemberInfo;
	}
	void GetHdChnnlInfo(u8 byChnnlIdx,TChnnlMemberInfo *ptChnnlMemberInfo)
	{
		*ptChnnlMemberInfo = m_tHdChnnlInfo[byChnnlIdx];
	}
	
	//�ҵ���һ�����е�ͨ��,û���򷵻�-1
	s32 FindFreeHdChnnl()
	{
		for(u8 byLoop=0; byLoop< MAXNUM_SVMPB_HDCHNNL; byLoop++)
		{
			if(m_tHdChnnlInfo[byLoop].GetMt().IsNull())
			{
				return byLoop;
			}
		}
		return -1;
	}
	/*==============================================================================
	������    :  IsMtAlreadyInChnnl
	����      :  ��ȡĳMt���ĸ�HDͨ����
	�㷨ʵ��  :  
	����˵��  :  u8 byMtId		[in]
			 
	����ֵ˵��:  ͨ���ţ���MT�����ڸ���ͨ�����򷵻�-1
	-------------------------------------------------------------------------------
	�޸ļ�¼  :  
	��  ��       �汾          �޸���          �߶���          �޸ļ�¼
	2008-12-11					Ѧ��
	==============================================================================*/
	s32 GetChnnlIdxCtnMt(TMt tMt)
	{
		s32 nChnnlIdx = -1;
		if(tMt.IsNull())
		{
			return nChnnlIdx;
		}

		for(u8 byLoop =0; byLoop < MAXNUM_SVMPB_HDCHNNL; byLoop++)
		{
			if(m_tHdChnnlInfo[byLoop].GetMt() == tMt)
			{
				nChnnlIdx = byLoop;
				break;
			}
		}
		return nChnnlIdx;
	}
	/*==============================================================================
	������    :  AddInfoToHdChnnl
	����      :  ����Ϣ�ӵ�����ͨ���У���������ͬ����Ϣ�ӵ���ͬ��ͨ��
	�㷨ʵ��  :  
	����˵��  :  u8 byMtId		[in]
			 
	����ֵ˵��:  ͨ����
	-------------------------------------------------------------------------------
	�޸ļ�¼  :  
	��  ��       �汾          �޸���          �߶���          �޸ļ�¼
	2008-12-11					Ѧ��
	==============================================================================*/
	s32 AddInfoToHdChnnl(const TChnnlMemberInfo *ptChnnlMemberInfo)
	{
		//u8 byMtId = ptChnnlMemberInfo->GetMtId();
		TMt tMt = ptChnnlMemberInfo->GetMt();
		s32 nChnnlIdx = GetChnnlIdxCtnMt(tMt);
		if( nChnnlIdx != -1) 
		{
			OspPrintf(TRUE,FALSE,"Mt.%u is Already in the Hd Channel!\n",tMt.GetMtId());
			// xliang [4/1/2009] ˢ��һ��ͨ����Ա����
			m_tHdChnnlInfo[nChnnlIdx].SetAttrNull();
			if(ptChnnlMemberInfo->IsAttrSpeaker())
			{
				m_tHdChnnlInfo[nChnnlIdx].SetAttrSpeaker();
			}
			if(ptChnnlMemberInfo->IsAttrSelected())
			{
				m_tHdChnnlInfo[nChnnlIdx].SetAttrSelected();
			}
			if(ptChnnlMemberInfo->IsAttrNoneKeda())
			{
				m_tHdChnnlInfo[nChnnlIdx].SetAttrNoneKeda();
			}
			return -1;
		}
		nChnnlIdx = FindFreeHdChnnl();
		if( nChnnlIdx!= -1)
		{
			m_tHdChnnlInfo[nChnnlIdx] = *ptChnnlMemberInfo;
			m_byHDChnnlNum ++;
			return nChnnlIdx;
		}
		else
		{
			return -1;
		}
	}
	/*==============================================================================
	������    :  ClearOneChnnl
	����      :  ��ĳMT��Ӧ��ͨ����Ϣ
	�㷨ʵ��  :  
	����˵��  :  u8	byMtId		[in]
	����ֵ˵��:  TRUE����ɹ�
	-------------------------------------------------------------------------------
	�޸ļ�¼  :  
	��  ��       �汾          �޸���          �߶���          �޸ļ�¼
	2008-12-15					Ѧ��
	==============================================================================*/
	BOOL32 ClearOneChnnl(TMt tMt)
	{
		s32 nChnnlIdx = GetChnnlIdxCtnMt(tMt);
		if(nChnnlIdx!=-1)
		{
			TChnnlMemberInfo tChnnlMemberInfo;
			tChnnlMemberInfo.SetNull();
			SetHdChnnlInfo((u8)nChnnlIdx,&tChnnlMemberInfo);
			m_byHDChnnlNum--;
			//m_byAllChnnlNum--;//û��Ҫ
			return TRUE;
		}
		else
		{
			OspPrintf(TRUE,FALSE,"[TVmpChnnlInfo] Mt.%u isn't in any Hd channel!\n",tMt.GetMtId());
			return FALSE;
		}
	}

	u8 GetHdChnnlMtId(u8 byChnnlIdx)	//��ȡĳͨ���е�MT Id
	{
		return m_tHdChnnlInfo[byChnnlIdx].GetMtId();
	}


	void print(void)//FIXME
	{
		OspPrintf(TRUE, FALSE, "All Chnnl Num: %u\nHd Chnnl Num: %u\n4CIF Chnnl Num: %u\n\
			CIF Chnnl Num: %u\n", \
			m_byAllChnnlNum, m_byHDChnnlNum, m_by4CifChnnlNum, m_byCifChnnlNum);
		OspPrintf(TRUE, FALSE, "---------MtId info in Hd Channels------------\n");
		for(u8 byLoop = 0; byLoop < m_byHDChnnlNum; byLoop++)
		{
			OspPrintf(TRUE, FALSE, "Hd Channel[%u]-->Mt.%u\n",
				byLoop, m_tHdChnnlInfo[byLoop].GetMtId() );
		}

	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;
//�ն�ִ�е���ռѡ�����
struct TSeizeChoice 
{
public:
//	u8	byMtId;
	TMt tSeizedMt;
	u8	byStopVmp;		//��MT�Ƿ�ֹͣVMP
	u8  byStopSelected;	//��MT�Ƿ�ֹͣ��ѡ��
	u8	byStopSpeaker;	//��MT�Ƿ�ȡ��������
public:
	TSeizeChoice(void)
	{
		init();
	}
	void init()
	{
		tSeizedMt.SetNull();
		byStopSelected = 0;
		byStopSpeaker  = 0;
		byStopVmp	   = 0;
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//�ϴα���ʱ�����ĳͨ���е�VMP��Ա��Ϣ(�����˸����������)
struct TLastVmpchnnlMemInfo
{
public:
	u8 m_byLastVmpMemInChnnl;
	u8 m_byLastMemType;
public:
	TLastVmpchnnlMemInfo( void )
	{
		Init();
	}
	void Init()
	{
		m_byLastVmpMemInChnnl = ~0;
		m_byLastMemType = 0;
	}
	void SetLastVmpMemChnnl( u8 byMemChnnl ) { m_byLastVmpMemInChnnl = byMemChnnl; }
	u8	 GetLastVmpMemChnnl( void ) { return m_byLastVmpMemInChnnl; }
	void SetLastVmpMemType( u8 byMemType ) { m_byLastMemType = byMemType; }
	u8   GetLastVmpMemType (void ) { return m_byLastMemType; } 

};

struct TSpyVmpInfo
{
	u8		m_byRes;	//�ֱ�������
	u8		m_byPos;	//ͨ��λ��
	u8		m_bKeepOrgRes;	//������ʹ�¼������˷ֱ���(�����keda��)���ϼ����ǿ���������ȫ�ֱ��ʽ�

}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TSpySwitchInfo     // ѡ����صĶ�ش���ʼ��Ϣ
{
	u8    m_byMcInstId;   // ĳ����ص�id
	u8    m_byDstChlIdx;  // Ŀ��ͨ������
	u8    m_bySrcChlIdx;  // Դͨ��������
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TSpyHduInfo     // ���������ǽ��صĶ�ش���ʼ��Ϣ
{
	u8    m_bySrcMtType;  // ����ǽԴͨ����Ա����
	u8    m_bySchemeIdx;  // Ԥ��������
	u8    m_byDstChlIdx;  // HDUĿ��ͨ������
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TSpyTVWallInfo     // ������ǽ��صĶ�ش���ʼ��Ϣ
{
	u8    m_bySrcMtType;  // ����ǽԴͨ����Ա����
	u8    m_bySchemeIdx;  // Ԥ��������
	u8    m_byDstChlIdx;  // HDUĿ��ͨ������
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TSpyPollInfo     // ������ǽ��صĶ�ش���ʼ��Ϣ
{
	u16   m_wKeepTime;        //�ն���ѯ�ı���ʱ�� ��λ:��(s)
	u8    m_byPollingPos;        //�ն���ѯ�Ĵ���
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TSpyRollCallInfo     // ��ش����������Ϣ
{
	TMt m_tCaller;        // ������
	TMt m_tOldCaller;     // �ϵĵ�����
	TMt m_tOldCallee;     // �ϵı������� 
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

union USpyInfo
{
	TSpySwitchInfo tSpySwitchInfo;   // ѡ���������Ϣ
	TSpyHduInfo    tSpyHduInfo;      // ���������ǽ�������Ϣ
	TSpyPollInfo   tSpyPollInfo;     // ��ѯ�����Ϣ
	TSpyTVWallInfo tSpyTVWallInfo;   // ������ǽ�������Ϣ
	TSpyVmpInfo	   tSpyVmpInfo;		 // VMP��ض�����Ϣ
	TSpyRollCallInfo tSpyRollCallInfo;  // ���������Ϣ

	// �����������Ϣ
	// ����ϳɵ������Ϣ
	// ����ǽ�������Ϣ
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TPreSetInReq            // �ش���ʼ��Ϣ
{
	TMt m_tSrc;        // �ش���Դ
	TMt m_tDest;       // �ش���Ŀ�Ķˣ�����ѡ��������ѡ����Ŀ���նˣ����û����ȷ��Ŀ���նˣ���ش����ϼ���������ʱ��Ŀ���ն˾���NULL�������ϼ����顣
	u32 m_dwEvId;      // ��¼�ڽ��лش�����ǰ������Ӧ��ִ�е���Ϣ����ı䷢���ˣ��ն�ѡ���ȣ�
	u8  m_bySpyMode;   // ����Ļش�ģʽ
	
	// Dst���� FIXME
// 	u8  m_byAdjResRequired;		// Is adjusting resolution required
// 	u8	m_byRes;				// Resolution value
// 	u8  m_byReserved;           // �����ֶ�
	TSimCapSet	m_tSimCapSet;   // Ŀ�Ķ˵�����
// 	union USpyInfo             // ��ش���ҵ����ص�һЩ��Ҫ����Ϣ
// 	{
// 		TSpySwitchInfo tSpySwitchInfo;   // ѡ���������Ϣ
// 		TSpyHduInfo    tSpyHduInfo;      // ������ǽ�������Ϣ
// 		TSpyPollInfo   tSpyPollInfo;     // ��ѯ�����Ϣ
// 		// �����������Ϣ
// 		// ����ϳɵ������Ϣ
// 		// ����ǽ�������Ϣ
// 	} m_tSpyInfo;
	USpyInfo m_tSpyInfo;

public:
	TPreSetInReq()
	{
		memset( this, 0, sizeof(TPreSetInReq) );
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TPreSetInRsp            // PreSetIn Ӧ����Ϣ
{
	TMt m_tSrc;        // �ش���Դ
	TMt m_tDest;       // �ش���Ŀ��
	u32 m_dwEvId;      // ��¼�ڽ��лش�����ǰ������Ӧ��ִ�е���Ϣ����ı䷢���ˣ��ն�ѡ���ȣ�
	u8  m_bySpyMode;   // �ش�ģʽ(BOTH/V/A )
	u32	m_dwSpyBW;	   // �ش���ռ�ö��ٴ���	
// 	u8  m_byAdjResRequired;		// Is adjusting resolution required
// 	u8	m_byRes;				// Resolution value
// 	u8  m_byReserved;           // �����ֶ�
	TSimCapSet	m_tSimCapSet;   // Ŀ�Ķ˵�����

// 	union USpyInfo
// 	{
// 		TSpySwitchInfo tSpySwitchInfo;   // ѡ���������Ϣ
// 		TSpyHduInfo    tSpyHduInfo;      // ������ǽ�������Ϣ
// 		TSpyPollInfo   tSpyPollInfo;     // ��ѯ�����Ϣ
// 		// �����������Ϣ
// 		// ����ϳɵ������Ϣ
// 		// ����ǽ�������Ϣ
// 	} m_tSpyInfo;
	USpyInfo m_tSpyInfo;
	
public:
	TPreSetInRsp()
	{
		memset( this, 0, sizeof(TPreSetInRsp) );
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;


struct TSpyResource         // ��ش�������Ϣ
{
public:
	TMt		m_tSpy;		    // ������MT��Ҳ������EQP(��mixer)
    u16     m_wSpyStartPort;    // ��¼SpyChnnl, ��ֵ * PORTSPAN + SPY_MCU_STARTPORT  ��ӦMMCU ת�����ϵĻش�port
	u32     m_dwTotalBW;    // ��Spy�ش�ռ�ô���
	u8		m_bySpyMode;	// AUDIO,VIDEO,BOTH
	
	u8		m_byOldSpyMode;   // �����ֶ�
	u32		m_dwReserved;

public:
	TSpyResource()
	{
		memset( this, 0, sizeof(TSpyResource) );
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;



#undef SETBITSTATUS
#undef GETBITSTATUS

#ifdef WIN32
#pragma pack( pop )
#endif

#endif /* __MCUSTRUCT_H_ */




