

#ifndef _PA_STRUCT_H_
#define _PA_STRUCT_H_

#include <memory.h>
#include <time.h>
#include "kdvtype.h"
#include "patype.h"
#include "pamacro.h"
#include <string.h>
#include <stdlib.h>

//2012-3-6 add-by wuhu ����TPAAudChanCmd �ṹ
#define TP_MAX_EPID_LEN			64				//����ʱ��ID����ַ�������
#define SEPCHAR '.'
#define TP_INVALID_INDEX		0xFFFF
#define TP_MAX_STREAMNUM		3				//�᳡�����������
#define TP_RET_OK	            0
#define TP_CONF_MAX_TURNNUM		64				//���������ѯ����

typedef struct tagTYouAreSeeing
{
	u32 m_dwVideoNum;//��Ƶ��������
	u32 m_dwAudioNum;//��Ƶ��������
	u16 m_CNSId;//CNSID
	u16 m_wMcuId;//323mcuId
	BOOL32 m_bExist;//�Ƿ����
	s8  m_achMeetingName[PA_MAX_CONF_NAME_LEN+1];//�����˻᳡��
	u16 m_wSpeakerIndex;
	tagTYouAreSeeing()
	{
		memset( this, 0, sizeof(tagTYouAreSeeing) );
	}
}TYouAreSeeing,*PTYouAreSeeing;

typedef struct tagTPAIPAddress
{
public:
	u32_ip m_dwIP ;
	u16 m_wPort;

	void Clear()
	{
		m_dwIP = 0;
		m_wPort = 0;
	}
	tagTPAIPAddress()
	{
		Clear();
	}
}TPAIPAddress,*PTPAIPAddress;

typedef struct tagTPAConfStatusInd
{
	u16 m_wMeetingId;//�᳡ID	
	s8  m_achConfName[PA_MAX_H323ALIAS_LEN+1];

	time_t m_tBeginTime;
	s8	m_achChairName[PA_MAX_H323ALIAS_LEN+1];	

	s8	m_achSpeakName[PA_MAX_H323ALIAS_LEN+1];	
	u16	m_wChairVidSndCap;
	u16 m_wChairAudSndCap;
	BOOL32   m_bMixMotive;          // �Ƿ�������������
	BOOL32   m_bSpeakOnline;        // �������Ƿ�����

	tagTPAConfStatusInd()
	{
		memset( this, 0, sizeof(tagTPAConfStatusInd) );
	}

}TPAConfStatusInd,*PTPAConfStatusInd;

typedef struct tagTPAEpPathKey
{
	s8	m_szEpID[TP_MAX_EPID_LEN+1];
	tagTPAEpPathKey()
	{
		Clear();
	}
	void Clear()
	{
		m_szEpID[0] = '\0';
	}
	
	BOOL32 IsRoot() const
	{
		if (0 == memcmp(m_szEpID, "root", 4))
		{
			return TRUE;
		}
		return FALSE;
	}
	
	BOOL32 IsValid() const
	{
		u8 byLast = SEPCHAR;
		u16 wIndex = 0;
		
		if (IsRoot())
		{
			return TRUE;
		}
		while (m_szEpID[wIndex] != '\0')
		{
			if (m_szEpID[wIndex] != SEPCHAR && (m_szEpID[wIndex] < '0' || m_szEpID[wIndex] > '9'))
			{
				return FALSE;
			}
			
			if (m_szEpID[wIndex] == SEPCHAR && m_szEpID[wIndex] == byLast)
			{
				return FALSE;
			}
			
			byLast = m_szEpID[wIndex];
			
			wIndex++;
			
			if (wIndex > TP_MAX_EPID_LEN)
			{
				return FALSE;
			}
		}
		return TRUE;
	}
	
	BOOL32 GetKeyPath(u16 awEpID[], u16 wMaxNum, u16& wRealNum) const 
	{
		wRealNum = 0;
		if (IsRoot())
		{
			return TRUE;
		}
		
		if (!IsValid())
		{
			return FALSE;
		}
		s8	szEpID[TP_MAX_EPID_LEN+1];
		memcpy(szEpID, m_szEpID, TP_MAX_EPID_LEN+1);
		
		s8* pChar = szEpID;
		u16 wIndex = 0;
		while (*(pChar+wIndex) != '\0')
		{
			if (*(pChar+wIndex) == SEPCHAR)
			{
				if (wIndex == 0)
				{
					return FALSE;
				}
				*(pChar+wIndex) = '\0';
				awEpID[wRealNum] = atoi(pChar);
				++wRealNum;
				if (wRealNum >= wMaxNum)
				{
					return FALSE;
				}
				pChar = pChar+wIndex+1;
				wIndex = 0;
				continue;
			}
			wIndex++;
		}
		return TRUE;
	}
}TPAEpPathKey;

typedef struct tagTPAEpKey
{
	u16 m_wEpID;			//�ϼ�֪ͨ�¼�ʱΪ�¼�ID
							//�¼�֪ͨ�ϼ�ʱΪ����ID���¼�ID
	TPAEpPathKey m_tKey;
	tagTPAEpKey()
	{
		m_wEpID = TP_INVALID_INDEX;
		m_tKey.Clear();
	}
	void Clear()
	{
		m_wEpID = TP_INVALID_INDEX;
		m_tKey.Clear();
	}

}TPAEpKey;

typedef struct tagTPAPollNodeChange
{
	TPAEpKey  m_tNodeInfo;
	tagTPAPollNodeChange()
	{
		memset( this, 0, sizeof(tagTPAPollNodeChange) );
	}
}TPAPollNodeChange, *PTPAPollNodeChange;

typedef struct tagTPACascadingSpeaker
{
	TPAEpKey m_tNodeKey;
	u16 m_wEpID;
	u16 m_wSpeaker;
	tagTPACascadingSpeaker()
	{
		memset( this, 0, sizeof(tagTPACascadingSpeaker) );
	}
}TPACascadingSpeaker;


typedef struct tagTPAPeerMuteCmd
{
	BOOL32 m_bMute;
	u16    m_wEpId;
	s8 m_achPeerMute[PA_MAX_H323ALIAS_LEN+1];
	tagTPAPeerMuteCmd()
	{
		memset( this, 0, sizeof(tagTPAPeerMuteCmd) );
	}	
}TPAPeerMuteCmd,*PTPAPeerMuteCmd;

typedef struct tagTPAPeerMuteInd
{
	BOOL32 m_bMute;
	TPAEpKey m_tPeerMute;
	tagTPAPeerMuteInd()
	{
		memset( this, 0, sizeof(tagTPAPeerMuteInd) );
	}
}TPAPeerMuteInd,*PTPAPeerMuteInd;

typedef struct tagTHangupCascadingConf
{
	u16 m_wEpId;
	BOOL32 m_bClear;
	tagTHangupCascadingConf()
	{
		memset( this, 0, sizeof(tagTHangupCascadingConf) );
	}
}THangupCascadingConf,*PTHangupCascadingConf;


typedef struct tagTPAName
{
	s8				m_abyAlias[PA_MAX_NAME_LEN+1];
	tagTPAName()
	{
		memset( this, 0, sizeof(tagTPAName) );
	}
	void SetAlias(const s8* alias)
	{
		u16 len = strlen(alias)+1;
		len = min(len, PA_MAX_NAME_LEN);
		memcpy(m_abyAlias, alias, len);
		m_abyAlias[len] = '\0';
	}
}TPAName;

typedef struct tagTPAPollDstName
{
	s8				m_abyAlias[PA_MAX_NAME_LEN+1];
	u32             m_nScreenNum;
	tagTPAPollDstName()
	{
		memset( this, 0, sizeof(tagTPAPollDstName) );
	}
	void SetAlias(const s8* alias)
	{
		u16 len = strlen(alias)+1;
		len = min(len, PA_MAX_NAME_LEN);
		memcpy(m_abyAlias, alias, len);
		m_abyAlias[len] = '\0';
	}
}TPAPollDstName;

typedef struct tagTPAAskKeyByScreenTr
{
	u16		m_wEpID;
	u16		m_wScreenNum;
	BOOL32	m_bReqBySys;

    u32		m_dwAskType;               //��������  �����ˡ���ϯ��ѡ����ѯ�����ۡ�¼��������ǽ
    u32		m_dwRervse1;               //����
	u32		m_dwRervse2;               //����
}TPAAskKeyByScreenTr;



//��������
typedef struct tagTPAAlias
{
	EmPAAliasType	m_byType;     
	s8				m_abyAlias[PA_MAX_NAME_LEN+1];
	tagTPAAlias()
	{
		Clear();
	}
	void Clear()
	{
		memset( this, 0, sizeof(tagTPAAlias) );
	}
	void SetAlias(EmPAAliasType type, const s8* alias)
	{
		m_byType = type;
		strncpy(m_abyAlias, alias, PA_MAX_NAME_LEN);
		m_abyAlias[PA_MAX_NAME_LEN] = '\0';
	}
	
	
}TPAAlias, *PTPAAlias;


typedef struct tagTPAEpKeyID
{
	s8	m_szEpID[PA_MAX_EPID_LEN];
	
	tagTPAEpKeyID()
	{
		memset( this, 0, sizeof(tagTPAEpKeyID) );
	}
}TPAEpKeyID,*PTPAEpKeyID;

typedef struct tagTPAUmsVidFormat
{
	EmPAVideoFormat		m_emFormat;
	EmPAVideoResolution	m_emRes;
	EmPAProfileMask	m_emProfile;//profile
	u16				m_byFrameRate;	//֡��
	u16				m_wBitrate;
	
	tagTPAUmsVidFormat()
	{
		Clear();
	}
	void Clear()
	{
		memset(this, 0, sizeof(tagTPAUmsVidFormat));
	}
}TPAUmsVidFormat;

typedef struct tagTPAUmsAudFormat
{
	EmPAAudioFormat		m_emFormat;
	EmPAAACSampleFreq	m_emPASampleFreq;
	EmPAAACChnlCfg		m_emPAChnlCfg;
	u8				m_byReserve1;
	u8				m_byReserve2;
	
	tagTPAUmsAudFormat()
	{
		Clear();
	}
	void Clear()
	{
		memset(this, 0, sizeof(tagTPAUmsAudFormat));
	}
}TPAUmsAudFormat;

//�¼����ϼ����½����Ϣ
typedef struct tagTPAConfNodeUpdateTr
{
	TPAEpKeyID m_tID;						//��״��
	u16		 m_wEpID;						//���¼��е�ID
	
	u32	m_emEpType;			//�������
	u32	m_emCallState;		//����״̬
	u32	m_emCallReason; 
	
	TPAAlias m_tCalledAddr;					//���д˽��ʱ�ĵ�ַ
	TPAAlias m_tConfName;					//�᳡��
	
	u16	m_wLevel;				//�᳡�ȼ�	����
	u32 m_enRcvAlignType;
	
	BOOL32 m_bMute;
	BOOL32 m_bQuiet;
	
	//�����������ͨ�� 0,1,2,3,4���򣬲��ܱ��᳡��ʵ�Ǽ���������
	u16 m_wSpearkIndex;			//������ͨ������
	u16 m_wDualIndex;			//����˫��ͨ������

	tagTPAConfNodeUpdateTr()
	{	
		memset( this, 0, sizeof(tagTPAConfNodeUpdateTr) );
	}
}TPAConfNodeUpdateTr,*PTPAConfNodeUpdateTr;

//֪ͨ���½����Ϣ
typedef struct tagTPAConfNodeUpdateTrList
{
	u16		m_wNum;
	TPAConfNodeUpdateTr m_atList[PA_REFRESH_LIST_THREE];
	tagTPAConfNodeUpdateTrList()
	{
		m_wNum = 0;
	}
}TPAConfNodeUpdateTrList,*PTPAConfNodeUpdateTrList;

typedef struct tagTPAConfNodeUpdateB2NEWTr
{
	TPAEpKey tID;						//��״��
	u16		 wEpID;						//���¼��е�ID
	BOOL32	bChanOpen;					//ͨ���Ƿ��

	//B2����
	u16	wVidSnd;		
	u16	wVidRcv;	
	u16	wAudSnd;	
	u16	wAudRcv;
	
	TPAUmsVidFormat	tVidRcv;
	TPAUmsAudFormat	tAudRcv;
	
	TPAUmsVidFormat	tVidSnd;
	TPAUmsAudFormat	tAudSnd;

	TPAUmsVidFormat	tDualVidRcv;		//��������
	TPAUmsAudFormat	tDualAudRcv;
	
	TPAUmsVidFormat	tDualVidSnd;
	TPAUmsAudFormat	tDualAudSnd;

	//�غ�������������˳������Ƶ���� ��Ƶ���� ˫����Ƶ���� ˫����Ƶ���� ��Ƶ���� ��Ƶ���� ˫����Ƶ���� ˫����Ƶ����
	u16 awPd[PA_MAX_CHAN_NUM]; 
	BOOL32		bInPoll;					//�Ƿ�����ѯ�б���

	//
	tagTPAConfNodeUpdateB2NEWTr()
	{	
		memset( this, 0, sizeof(tagTPAConfNodeUpdateB2NEWTr) );
	}
	
}TPAConfNodeUpdateB2NEWTr;

typedef struct tagTPAConfNodeUpdateB2NEWTrList
{
	u16		m_wNum;
	TPAConfNodeUpdateB2NEWTr m_atList[PA_REFRESH_LIST_THREE];
	tagTPAConfNodeUpdateB2NEWTrList()
	{
		m_wNum = 0;
	}
}TPAConfNodeUpdateB2NEWTrList;

//֪ͨɾ�����
typedef struct tagTPAConfNodeDelTrList
{
	u16		m_wNum;
	TPAEpKey m_atList[PA_REFRESH_LIST_FIVE];
	tagTPAConfNodeDelTrList()
	{
		memset( this, 0, sizeof(tagTPAConfNodeDelTrList) );
	}
}TPAConfNodeDelTrList,*PTPAConfNodeDelTrList;


typedef struct tagTPAAudMixEpCmdTr
{
	u16	m_wEpID;
	u16 m_wLocalID;					//�ϼ�����������
	TPAIPAddress m_tRtpAddr;		//�ϼ�����EP����
	TPAIPAddress m_tBackRtpAddr;	//������������BACKRTP��ַ
	tagTPAAudMixEpCmdTr()
	{
		m_tRtpAddr.Clear();
		m_tBackRtpAddr.Clear();
		m_wEpID = 0xffff;
		m_wLocalID = 0xffff;
	}
}TPAAudMixEpCmdTr,*PTPAAudMixEpCmdTr;

typedef struct tagTPAAudMixEpAckTr
{
	u16 m_wReason;				//ԭ��
	u16 m_wLocalID;
	TPAIPAddress m_tRtpAddr;		//�����ϼ������������
	TPAIPAddress m_tBackRtpAddr;	//EP������backrtp��ַ
	tagTPAAudMixEpAckTr()
	{
		m_wReason = 0;
		m_tRtpAddr.Clear();
		m_tBackRtpAddr.Clear();
		m_wLocalID = 255;
	}
}TPAAudMixEpAckTr,*PTPAAudMixEpAckTr;

typedef struct tagTDualInfo
{
	EmPAPayloadType m_emPayload;
	EmPAResolution  m_emReslution;
	u16				m_wFrameRate;
	u16             m_wBitRate;
	s32 m_nScreenNo;
	s32 m_nEpId;
	s8  m_achCascade[PA_MAX_H323ALIAS_LEN+1];
	TPAIPAddress m_tVidRtp;
	TPAIPAddress m_tVidRtcp;
	TPAIPAddress m_tVidBackRtp;

	TPAIPAddress m_tAudRtp;
	TPAIPAddress m_tAudRtcp;
	TPAIPAddress m_tAudBackRtp;

	tagTDualInfo()
	{
		memset( this, 0, sizeof(tagTDualInfo) );
	}

}TDualInfo,*PTDualInfo;

typedef struct tagTDualInfoAck
{
	BOOL32    m_bAccept;
	TDualInfo m_tDualInfo;
	tagTDualInfoAck()
	{
		memset( this, 0, sizeof(tagTDualInfoAck) );
	}
}TDualInfoAck,*PTDualInfoAck;

typedef struct tagTDualRequest
{
	s8 m_achCascade[PA_MAX_H323ALIAS_LEN+1];
	s32 m_nEpId;
	tagTDualRequest()
	{
		memset( this, 0, sizeof(tagTDualRequest) );
	}
}TDualRequest,*PTDualRequest;


typedef struct tagTPATvMonitorCmd
{
	s8				m_achCascade[PA_MAX_H323ALIAS_LEN+1];
	u16				m_wIndex;
	u16				m_wEpID;
	TPAIPAddress	m_tVidRtp;
	TPAIPAddress	m_tVidRtcp;
	TPAIPAddress	m_tVidBackRtp;
	
	TPAIPAddress	m_tAudRtp;
	TPAIPAddress	m_tAudRtcp;
	TPAIPAddress	m_tAudBackRtp;

	u16 m_wScreenNum;
	
	tagTPATvMonitorCmd()
	{
		memset( this, 0, sizeof(tagTPATvMonitorCmd) );
		m_wScreenNum = 0xffff;
	}
}TPATvMonitorCmd;

typedef struct tagTPATvMonitorInd
{
	BOOL32			m_bAccept;
	s8				m_achCascade[PA_MAX_H323ALIAS_LEN+1];
	u16				m_wIndex;
	u16				m_wEpID;
	TPAIPAddress	m_tVidRtp;
	TPAIPAddress	m_tVidRtcp;
	TPAIPAddress	m_tVidBackRtp;
	
	TPAIPAddress	m_tAudRtp;
	TPAIPAddress	m_tAudRtcp;
	TPAIPAddress	m_tAudBackRtp;

    u16 m_wScreenNum;

	tagTPATvMonitorInd()
	{
		memset( this, 0, sizeof(tagTPATvMonitorInd) );
		m_wScreenNum = 0xffff;
	}
}TPATvMonitorInd;


typedef struct tagTPANodeCapsetTr
{
	u16 m_wSpeakindex;
	tagTPANodeCapsetTr()
	{
		memset( this, 0, sizeof(tagTPANodeCapsetTr) );
	}
}TPANodeCapsetTr;

//addy-by wuhu 2011-11-1  ����TPAConfCnsList�ṹ

typedef struct tagTPaMediaTransAddr
{
	TPAIPAddress m_tRtpAddr;
	TPAIPAddress m_tRtcpAddr;	
	TPAIPAddress m_tBackRtcpAddr;	
}TPaMediaTransAddr;


#define PA_REFRESH_LIST_FIVE	5
#define PA_MAX_ALIAS_LEN		64				//������󳤶�
#define PA_MAX_STREAMNUM		3				//�᳡�����������


typedef struct tagTPACnsInfo
{
	u16	m_wEpID;							//�᳡ID
	u16	m_wParentEpID;						//���᳡ID
	u16 m_wChildEpID;
	u16 m_wBrotherEpID;
	
	EmPATPEndpointType m_emPAEpType;			//�������
	TPAAlias m_tCalledAddr;
	
	BOOL32	m_bOnline;			            //����״̬
	EmPACnsCallReason m_emPACallReason; 
	s8	m_achRoomName[PA_MAX_ALIAS_LEN+1];	//�᳡��
	u16	m_wLevel;							//�᳡�ȼ�	����
	
	BOOL32 m_bMute;
	BOOL32 m_bQuiet;
	
	u16 m_wSpeakerNum;						//�᳡����	
	s8	m_achSpeakerName[PA_MAX_STREAMNUM][PA_MAX_ALIAS_LEN+1];
	
	tagTPACnsInfo()
	{	
		Clear();
	}
	
	void Clear()
	{
		m_wEpID = PA_INVALID_VALUE;
		m_wParentEpID = PA_INVALID_VALUE;
		m_wChildEpID = PA_INVALID_VALUE;
		m_wBrotherEpID = PA_INVALID_VALUE;
		m_emPAEpType = emPATPEndpointTypeUMS;
		
		m_bOnline = FALSE;
		m_achRoomName[0] = '\0';
		m_wLevel = PA_INVALID_VALUE;
		
		m_bMute = FALSE;
		m_bQuiet = FALSE;
		m_wSpeakerNum = PA_INVALID_VALUE;
		m_emPACallReason = EmPACnsCallReason_Local;
	}
	
	BOOL32 operator == (const tagTPACnsInfo& tRhs)
	{
		return this->m_wEpID == tRhs.m_wEpID;
	}
}TPACnsInfo;

typedef struct tagTConfCnsList
{
	EmPAOprType	    m_emPAOpr;
	u16             m_wMcuId;
	u16			    m_wConfID; 
	u16		    	m_wNum;
	TPACnsInfo	    m_tConfCnsList[PA_REFRESH_LIST_FIVE];
	tagTConfCnsList()
	{
		m_emPAOpr = PA_OprType_Add;
		m_wConfID = PA_INVALID_VALUE;
		m_wNum = 0;
		m_wMcuId = 0;
	}
}TConfCnsList;

typedef struct tagTPAConfCnsList
{
    TConfCnsList tCnsList;
    tagTPAConfCnsList()
	{
		memset(this, 0, sizeof(tagTPAConfCnsList));
	}
	
}TPAConfCnsList;

typedef struct tagTPAChanSelecteCascad
{
   s32 nPeerID;
   u16 wCascadID;
}TPAChanSelecteCascad;

typedef struct tagTPAChanSelecteCascadRes
{
    u32 nRes;
	s8  achName[PA_MAX_ALIAS_LEN+1];
	tagTPAChanSelecteCascadRes()
	{
		memset(this, 0, sizeof(tagTPAChanSelecteCascadRes));
	}
}TPAChanSelecteCascadRes;

typedef struct tagTPATmpChanSelecteCascadRes
{
	s32 nPeerID;
    u32 nRes;
	s8 achName[PA_MAX_ALIAS_LEN+1];
	tagTPATmpChanSelecteCascadRes()
	{
		memset(this, 0, sizeof(tagTPATmpChanSelecteCascadRes));
	}
}TPATmpChanSelecteCascadRes;

typedef struct tagTPAChanSelecteCascadCancelRes
{
	s32 nPeerID;
    u32 nRes;
}TPAChanSelecteCascadCancelRes;

typedef struct tagTPAPollCmd
{
	TPAIPAddress m_tRtpAddr[PA_MAX_STREAMNUM];
	TPAIPAddress m_tRtcpAddr[PA_MAX_STREAMNUM];	
	TPAIPAddress m_tBackRtcpAddr[PA_MAX_STREAMNUM];
	 
	u16 m_wBitrate;				//��ѯ����
	u16	m_wInterval;			//��ѯʱ����
	tagTPAPollCmd()
	{
		m_wBitrate = 0;
		m_wInterval = 0;
	}
}TPAPollCmd;

typedef struct tagTPAPollAck
{
	u16 m_wReason;
	TPAIPAddress m_tRtpAddr[PA_MAX_STREAMNUM];
	TPAIPAddress m_tRtcpAddr[PA_MAX_STREAMNUM];	
	TPAIPAddress m_tBackRtcpAddr[PA_MAX_STREAMNUM];
	tagTPAPollAck()
	{
		m_wReason = 0;
	}
}TPAPollAck;


typedef struct tagTPAViewCmd
{
	u16 m_wEpID;
	u16 m_wChanID;

	TPAIPAddress m_tRtpAddr;
	TPAIPAddress m_tRtcpAddr;	
	TPAIPAddress m_tBackRtcpAddr;

	TPAIPAddress m_tSmallRtpAddr;
	TPAIPAddress m_tSmallRtcpAddr;	
	TPAIPAddress m_tSmallBackRtcpAddr;
	
	TPAIPAddress m_tLeftRtpAddr;
	TPAIPAddress m_tLeftRtcpAddr;	
	TPAIPAddress m_tLeftBackRtcpAddr;

	TPAIPAddress m_tLeftSmallRtpAddr;
	TPAIPAddress m_tLeftSmallRtcpAddr;	
	TPAIPAddress m_tLeftSmallBackRtcpAddr;

	TPAIPAddress m_tRightRtpAddr;
	TPAIPAddress m_tRightRtcpAddr;	
	TPAIPAddress m_tRightBackRtcpAddr;

	TPAIPAddress m_tRightSmallRtpAddr;
	TPAIPAddress m_tRightSmallRtcpAddr;	
	TPAIPAddress m_tRightSmallBackRtcpAddr;

	BOOL32		 m_bMidOpen;
	BOOL32		 m_bSmallMidOpen;

	BOOL32		 m_bLeftOpen;
	BOOL32		 m_bSmallLeftOpen;

	BOOL32		 m_bRightOpen;
	BOOL32		 m_bSmallRightOpen;
	BOOL32		 m_bViewSpeaker;	//�Ƿ��ǽ���������ϯ

	u32          m_dwType;              //��ȡ����
	u16          m_wSrcScreenIndex;	    //Դ����

	//B2����
	TPaMediaTransAddr m_atAudAddr[TP_MAX_STREAMNUM];	//��Ƶ���յ�ַ	
	TPaMediaTransAddr m_tMixAddr;				//�������յ�ַ

	BOOL32			  m_bNeedBas;						//�Ƿ���Ҫ����

	tagTPAViewCmd()
	{
		m_bMidOpen = FALSE;
		m_bSmallMidOpen = FALSE;
		
		m_bLeftOpen = FALSE;
		m_bSmallLeftOpen = FALSE;

		m_bRightOpen = FALSE;
		m_bSmallRightOpen = FALSE;
		m_bViewSpeaker = FALSE;

		m_dwType = 0;
		m_wSrcScreenIndex = -1;

		m_bNeedBas = FALSE;
	}
}TPAViewCmd;

typedef struct tagTPAAdjustFrameRate
{
	u16    m_wEpID;
	u16	 m_wFrameRate;
	tagTPAAdjustFrameRate()
	{
		m_wEpID = TP_INVALID_INDEX;
		m_wFrameRate = 0;
	}
}TPAAdjustFrameRate;

typedef struct tagTPAAdjustVidRes
{
	u16    m_wEpID;
	u32	 m_dwVidRes;
	tagTPAAdjustVidRes()
	{
		m_wEpID = TP_INVALID_INDEX;
		m_dwVidRes = 0;
	}
}TPAAdjustVidRes;


typedef struct tagTPAViewAck
{
	u16 m_wReason;
	u16 m_wChanID;

	TPAIPAddress m_tRtpAddr;
	TPAIPAddress m_tRtcpAddr;	
	TPAIPAddress m_tBackRtcpAddr;

	TPAIPAddress m_tSmallRtpAddr;
	TPAIPAddress m_tSmallRtcpAddr;	
	TPAIPAddress m_tSmallBackRtcpAddr;
	
	TPAIPAddress m_tLeftRtpAddr;
	TPAIPAddress m_tLeftRtcpAddr;	
	TPAIPAddress m_tLeftBackRtcpAddr;
	
	TPAIPAddress m_tLeftSmallRtpAddr;
	TPAIPAddress m_tLeftSmallRtcpAddr;	
	TPAIPAddress m_tLeftSmallBackRtcpAddr;
	
	TPAIPAddress m_tRightRtpAddr;
	TPAIPAddress m_tRightRtcpAddr;	
	TPAIPAddress m_tRightBackRtcpAddr;
	
	TPAIPAddress m_tRightSmallRtpAddr;
	TPAIPAddress m_tRightSmallRtcpAddr;	
	TPAIPAddress m_tRightSmallBackRtcpAddr;

	BOOL32		 m_bMidOpen;
	BOOL32		 m_bSmallMidOpen;
	
	BOOL32		 m_bLeftOpen;
	BOOL32		 m_bSmallLeftOpen;
	
	BOOL32		 m_bRightOpen;
	BOOL32		 m_bSmallRightOpen;

	//B2����
	TPaMediaTransAddr m_atAudAddr[TP_MAX_STREAMNUM];	//��Ƶ���յ�ַ	
	TPaMediaTransAddr m_tMixAddr;			      //�������յ�ַ
		
	tagTPAViewAck()
	{
		m_wReason = 0;

		m_bMidOpen = FALSE;
		m_bSmallMidOpen = FALSE;
		
		m_bLeftOpen = FALSE;
		m_bSmallLeftOpen = FALSE;

		m_bRightOpen = FALSE;
		m_bSmallRightOpen = FALSE;
	}
}TPAViewAck;

typedef struct tagTPACascadeOpenChanCmd
{
	u16 m_wEpID;
	
	TPaMediaTransAddr m_atVidAddr[TP_MAX_STREAMNUM];	//���յ�ַ
	TPaMediaTransAddr m_atAudAddr[TP_MAX_STREAMNUM];	//���յ�ַ
	TPaMediaTransAddr m_atSmallAddr[TP_MAX_STREAMNUM];	//���յ�ַ
	TPaMediaTransAddr m_tMixAudAddr;

	BOOL32		 m_abVidOpen[TP_MAX_STREAMNUM];
	BOOL32		 m_abAudOpen[TP_MAX_STREAMNUM];
	BOOL32		 m_abSmallOpen[TP_MAX_STREAMNUM];
	BOOL32		 m_bMixAudOpen;

	tagTPACascadeOpenChanCmd()
	{
		m_wEpID = TP_INVALID_INDEX;
		
		memset(m_abVidOpen, 0, sizeof(m_abVidOpen));
		memset(m_abSmallOpen, 0, sizeof(m_abSmallOpen));
		memset(m_abAudOpen, 0, sizeof(m_abVidOpen));

		m_bMixAudOpen = FALSE;
	}
	
}TPACascadeOpenChanCmd;

typedef struct tagTPACascadeOpenChanAck
{
	u16 m_wEpID;
	
	TPaMediaTransAddr m_atVidAddr[TP_MAX_STREAMNUM];	//���յ�ַ
	TPaMediaTransAddr m_atAudAddr[TP_MAX_STREAMNUM];	//���յ�ַ
	TPaMediaTransAddr m_atSmallAddr[TP_MAX_STREAMNUM];	//���յ�ַ
	TPaMediaTransAddr m_tMixAudAddr;

	BOOL32		 m_abVidOpen[TP_MAX_STREAMNUM];
	BOOL32		 m_abSmallOpen[TP_MAX_STREAMNUM];
	BOOL32		 m_abAudOpen[TP_MAX_STREAMNUM];
	BOOL32		 m_bMixAudOpen;

	tagTPACascadeOpenChanAck()
	{
		m_wEpID = TP_INVALID_INDEX;
		
		memset(m_abVidOpen, 0, sizeof(m_abVidOpen));
		memset(m_abSmallOpen, 0, sizeof(m_abSmallOpen));
		memset(m_abAudOpen, 0, sizeof(m_abVidOpen));

		m_bMixAudOpen = FALSE;
	}
	
}TPACascadeOpenChanAck;


typedef struct tagTPAUmsReasonInd
{
    u16	m_wConfID;     //����
    u16 m_wEpID;       //���� ʵ�� ���ʹ��
    u32 m_dwReason;    //���� tperror.h�е�ԭ��
    
    u32 m_dwReserve1;  //����
    u32 m_dwReserve2;
    u32 m_dwReserve3;
    
    tagTPAUmsReasonInd()
    {
        m_wConfID = TP_INVALID_INDEX;
        m_wEpID   = TP_INVALID_INDEX;
        
        m_dwReason = 0;
        
        m_dwReserve1 = 0;
        m_dwReserve2 = 0;
        m_dwReserve3 = 0;
    }
}TPAUmsReasonInd;



#define PA_TP_REC_FILE_LEN  192  //¼���ļ�����󳤶�

typedef struct tagTPAUmsUpRecPlayState
{
    BOOL32		m_bIsPlayIng;	//�Ƿ��ڷ���
    BOOL32		m_bIsDualPlayIng;	//�Ƿ��˫��
    s8			m_achFileName[PA_TP_REC_FILE_LEN];	//�ļ���
    
    tagTPAUmsUpRecPlayState()
    {
        Clear();
    }
    
    void Clear()
    {
        m_bIsPlayIng = FALSE;
        m_bIsDualPlayIng = FALSE;
        memset(m_achFileName, 0, PA_TP_REC_FILE_LEN);
    }
}TPAUmsUpRecPlayState;

typedef struct tagTPAFlowControl
{
	TPAEpKey	m_tEpKey;
	u16	m_wEncNo;	//-1���������
	u16	m_wBand;
	u32 m_enOpr;
	tagTPAFlowControl()
	{
		m_tEpKey.Clear();
		m_wEncNo = -1;
		m_wBand = 0;
		m_enOpr = 0;
	}
}TPAFlowControl;

typedef struct tagTPAAudChanCmd
{
	TPAEpKey		m_tEpKey;
	TPAIPAddress	m_atRtpAddr[TP_MAX_STREAMNUM];
	TPAIPAddress	m_tMixRtpAddr;
	tagTPAAudChanCmd()
	{
		m_tEpKey.Clear();
		memset(m_atRtpAddr, 0, sizeof(m_atRtpAddr));
		memset(&m_tMixRtpAddr, 0, sizeof(m_tMixRtpAddr) );
	}
	
}TPAAudChanCmd;

typedef struct tagTPAAudChanAck
{
	u16		  	    m_wReason;					//ԭ��
	TPAEpKey		m_tEpKey;
	TPAIPAddress    m_atBackRtcpAddr[TP_MAX_STREAMNUM];
	TPAIPAddress    m_tMixBackRtcpAddr;
	tagTPAAudChanAck()
	{
		m_tEpKey.Clear();
		m_wReason = TP_RET_OK;
		
		memset( m_atBackRtcpAddr, 0, sizeof(m_atBackRtcpAddr) );
		memset( &m_tMixBackRtcpAddr, 0, sizeof(m_tMixBackRtcpAddr) );
	}
	
}TPAAudChanAck;


typedef struct tagTPAVidUpAddr
{
	TPAIPAddress		m_tAddr;
	TPAIPAddress		m_tSmallAddr;
	tagTPAVidUpAddr()
	{
		Clear();
	}
	
	void Clear()
	{
		m_tAddr.Clear();
		m_tSmallAddr.Clear();
	}
}TPAVidUpAddr;

typedef struct tagTPAVidDownAddr
{
	TPAIPAddress	m_tAddr;
	TPAIPAddress	m_tSmallAddrL;
	TPAIPAddress	m_tSmallAddrR;
	tagTPAVidDownAddr()
	{
		Clear();
	}
	
	void Clear()
	{
		m_tAddr.Clear();
		m_tSmallAddrL.Clear();
		m_tSmallAddrR.Clear();
	}
}TPAVidDownAddr;

typedef struct tagTPAVidChanCmd
{
	TPAEpKey				m_tEpKey;
	TPAVidUpAddr			m_atUpRtp[TP_MAX_STREAMNUM];	//�ϴ���Rtp�˿�
	TPAVidDownAddr		m_atDownBackRtcp[TP_MAX_STREAMNUM]; //�´���BackRtcp�˿�
	TPAIPAddress		m_atAudBackRtcp[TP_MAX_STREAMNUM];
	
	tagTPAVidChanCmd()
	{
		m_tEpKey.Clear();
		memset(m_atUpRtp, 0, sizeof(m_atUpRtp));
		memset(m_atDownBackRtcp, 0, sizeof(m_atDownBackRtcp) );
		memset(m_atAudBackRtcp, 0, sizeof(m_atAudBackRtcp) );
	}
}TPAVidChanCmd;

typedef struct tagTPAVidChanAck
{
	u16					m_wReason;	//ԭ��
	TPAEpKey				m_tEpKey;
	TPAVidUpAddr			m_atUpBackRtcp[TP_MAX_STREAMNUM];	//�ϴ���BackRtcp�˿�
	TPAVidDownAddr		m_atDownRtp[TP_MAX_STREAMNUM];		    //�´���Rtp�˿�
	TPAIPAddress		m_atAudRtp[TP_MAX_STREAMNUM];

	tagTPAVidChanAck()
	{
		m_wReason = TP_RET_OK;
		m_tEpKey.Clear();
		memset(m_atUpBackRtcp, 0, sizeof(m_atUpBackRtcp));
		memset(m_atDownRtp, 0, sizeof(m_atDownRtp));
		memset( m_atAudRtp, 0, sizeof(m_atAudRtp) );
	}
}TPAVidChanAck;


#define TP_CONF_MAX_AUDMIXNUM	4			//��������������
typedef struct tagTPAAuxMixList
{
	u16 m_wSpeakerIndex;					//�������������
	u16	m_awList[TP_CONF_MAX_AUDMIXNUM];	//����ID
	tagTPAAuxMixList()
	{
		memset(this, 0, sizeof(tagTPAAuxMixList) );
	}
}TPAAuxMixList;

typedef struct tagTPAConfAuxMixInfo
{
	u16			m_wConfID;
	BOOL32		m_bStart;
	TPAAuxMixList	m_atAuxMixList;
	tagTPAConfAuxMixInfo()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_bStart = FALSE;
	}
}TPAConfAuxMixInfo;

typedef struct tagTPAConfEpID
{
	u16	m_wConfID;
	u16	m_wEpID;
	tagTPAConfEpID()
	{
		Clear();
	}
	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_wEpID = TP_INVALID_INDEX;
	}
}TPAConfEpID;


typedef struct tagTPAConfTurnList
{
	u16 m_wInterval;						//��ѯ�������λ��
	u16	m_wNum;								//������ѯ����
	u16	m_awList[TP_CONF_MAX_TURNNUM];
	tagTPAConfTurnList()
	{
		Clear();
	}
	void Clear()
	{
		m_wInterval = 20;
		m_wNum = 0;
	}
}TPAConfTurnList;

typedef struct tagTPAConfTurnInfo
{
	u16				m_wConfID;
	TPAConfTurnList	m_atTurnList;
	tagTPAConfTurnInfo()
	{
		m_wConfID = TP_INVALID_INDEX;
	}
}TPAConfTurnInfo;


typedef struct tagTPAConfCallEpAddr
{
	u16	m_wConfID;
	TPAAlias	m_tAlias;
	tagTPAConfCallEpAddr()
	{
		m_wConfID = TP_INVALID_INDEX;
	}
}TPAConfCallEpAddr;

typedef struct tagTPAChairConfInfo
{
	u16			m_wConfID;
	time_t		m_tBeginTime;		//���鿪ʼʱ��
	TPAAlias	m_tConfName;		//��������
	TPAAlias	m_tChairName;		//��ϯ����
	tagTPAChairConfInfo()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_tBeginTime = 0;
	}
}TPAChairConfInfo;


typedef struct tagTPAAudMixStat
{
	u16		m_wConfID;
	u16		m_wEpID;
	BOOL32	m_bIsStart;
	EmPATpMixStatus	m_emMixStatus;
	tagTPAAudMixStat()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_wEpID = TP_INVALID_INDEX;
		m_bIsStart = FALSE;
		m_emMixStatus = emPAAudMixIdle;
	}
}TPAAudMixStat;

typedef struct tagTPADisScreenStat
{
	BOOL32 m_bInDiscard;//�û᳡�Ƿ���������
	u16 m_wEpIDDst;//UMS������
	
	u16 m_awScreenNum[TP_MAX_STREAMNUM]; //��������Ӧ�᳡������
	u16 m_awSpeakerIndx[TP_MAX_STREAMNUM];//��������Ӧ�᳡�Ķ�Ӧ�ķ�����ϯ����
	TPAAlias m_atAlias[TP_MAX_STREAMNUM];//��������Ӧ�Ļ᳡��������Чֵ����˴��᳡Ϊ���迴��̬ͼƬ������Ϊ�м�
	u32 m_dwOprType;//��������

	tagTPADisScreenStat(){Clear();}
	
	void Clear()
	{
		m_bInDiscard = FALSE;
		m_wEpIDDst = TP_INVALID_INDEX;
		for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
		{
			m_atAlias[wIndex].Clear();
			m_awScreenNum[wIndex] = TP_INVALID_INDEX;
			m_awSpeakerIndx[wIndex] = TP_INVALID_INDEX;
		}
		m_dwOprType = 0;
	}
	
	void SetByScreenID( u16 wScreenID, TPAAlias tAlias, u16 wScreenNum, u16 wSpeakerIndex )
	{
		if ( wScreenID >= TP_MAX_STREAMNUM )
		{
			return ;
		}
		
		m_atAlias[wScreenID].SetAlias( tAlias.m_byType, tAlias.m_abyAlias);
		m_awSpeakerIndx[wScreenID] = wSpeakerIndex;
		m_awScreenNum[wScreenID] = wScreenNum;
		
		return ;
	}
	
}TPADisScreenStat;



typedef struct tagTPADisAskKeyFrame
{
	u16 m_wEpID;//�ؼ�֡�����Դ�᳡ID
	u16 m_wScreenNo;//Դ�᳡���ĸ�������
	BOOL32 m_bReqBySys;
	tagTPADisAskKeyFrame(){Clear();}
	
	void Clear()
	{
		m_wEpID = TP_INVALID_INDEX;
		m_wScreenNo = TP_INVALID_INDEX;
		m_bReqBySys = FALSE;
	}
	
}TPADisAskKeyFrame; 


typedef struct tagTPADisListOpr
{
	u16 m_wConfID;
	u16 m_wEpID;
	u16 m_wIndex;//��CNC�����λ�� 0-3
	EmPADisListOprType m_emOprType;
	EmPADisListOprReslt m_emOprReslt; //�ظ�CNCʱʹ��
	tagTPADisListOpr()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_wEpID = TP_INVALID_INDEX;
		m_wIndex = TP_INVALID_INDEX;
		m_emOprType = emPA_DisListOpr_Add;
		m_emOprReslt = emPA_DisListOpr_Sucess;
	}
}TPADisListOpr;

// added by ganxiebin 20120814 >>> 

// ����ն�����, ��ӦMAX_CONFMT_NUM
#define PA_MAX_CONFMT_NUM		192	

// �ն˱�Ų���
// ��Ӧmodulcallstruct.h�е�TMDLTERLABEL�ṹ��
typedef struct tagTPATerminalLabel 
{
	u8 m_byMcuNo;
	u8 m_byTerNo;
	
	tagTPATerminalLabel()
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
		if( m_byTerNo <= PA_MAX_CONFMT_NUM && m_byMcuNo != 0xff )
			return TRUE;

		return FALSE;
	}

	BOOL32 operator == (const tagTPATerminalLabel& tTerLabel)
	{
      if(memcmp(this, (void*)&tTerLabel, sizeof(tTerLabel)) == 0)
			  return TRUE;
		
		  return FALSE;
	}

}TPATerminalLabel,*PTPATerminalLabel;
			

// �ն˱���б�
// ��Ӧmodulcallstruct.h�е�TMDLTERLABELLIST�ṹ��
typedef struct tagTPATerLabelList
{
	u8 m_byNum;
	TPATerminalLabel m_atTerLabelList[PA_MAX_CONFMT_NUM];
	
	tagTPATerLabelList()
	{
		Clear();
	}
	
	void Clear()
	{
		m_byNum = 0;
		memset( m_atTerLabelList, 0, sizeof(m_atTerLabelList) );
	}
}TPATerLabelList;

// �ն˱�������, ��ӦMAX_TERMINALID_LEN
#define PA_MAX_TERMINALID_LEN		128	

//�ն���Ϣ(�����), ��ӦTMDLTERMINALINFO
typedef struct tagTPATerminalInfo
{
	u8 m_byMcuNo;   
	u8 m_byTerNo;
	u8 m_byConfNo;   //�������
	s8 m_achTerminalId[PA_MAX_TERMINALID_LEN+1];    //TerminalID
	BOOL32 m_bIsChair;   //�Ƿ�����ϯ
	BOOL32 m_bIsFloor;   //�Ƿ��Ƿ�����
	
	BOOL32 m_bLastPack;  // �Ƿ������һ��
	BOOL32 m_bOnline;    // �Ƿ�����
	
	TPATerminalLabel m_tTerYouAreView;    //����ѡ��˭
	u32 m_anSeenByOtherListMask[6];   //6��int��ʾ192��λ������ʾ192���նˣ�˭ѡ��������ն�

	tagTPATerminalInfo()
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
	
}TPATerminalInfo,*PTPATerminalInfo;

// added by ganxiebin 20120814 <<<
#endif








