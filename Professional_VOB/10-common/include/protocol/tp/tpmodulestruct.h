#ifndef TPMODULESTRUCT_H
#define TPMODULESTRUCT_H
#include "pastruct.h"

#define     TPMODULE_MAX_NAME_LEN             64            //���������
#define     TPMODULE_REGNAME_SIZE			  64            //ע���������
#define     TPMODULE_MAX_PASSWORD_LEN         16            //������󳤶�
#define     TPMODULE_INVALID_VALUE            -1            //����s32����Чֵ  


enum EmPAEndpointType
{
	emPAEndpointTypeUnknown  = 0,
	emPAEndpointTypeCNS	     = 0x01,
	emPAEndpointTypeUMS		 = 0x02,
	emPAEndpointTypeRegister = 0x04
};


enum EmPASipLevel
{
	emPASipCounty,
		emPASipCity,
		emPASipProvince,
		emPASipUnKnown = 255,
};

enum EmPACapSign    //������ʶ�� ������
{
		emPACapBig,  
		emPACapLeft,
		emPACapRight,
		emPACapEnd,
};

enum EmPAAddrType
{
	emPAUnknown =0,
		emPAAlias,
		emPAE164Num,
		emPAIPAddr,
		emPAIP6Addr,
		emPADomain,
};

enum EmPAConnection
{
	emPAConnectionType = 0,
		emPATcpConnection,
		emPAUdpConnection,
		emPASCTPConnection,
		emPATLSConnection,
};

typedef struct tagPARegistLocalInfo
{
	EmPAEndpointType  m_emEndpointType;    //������ums��cns
	u32 m_locolIP;                         //����IP��ַ
	s8  m_softversion[TPMODULE_MAX_NAME_LEN+1];  //����汾��
	s8  m_compileTime[TPMODULE_MAX_NAME_LEN+1];  //����ʱ��
public:
    tagPARegistLocalInfo() {memset(this, 0, sizeof(tagPARegistLocalInfo));}
}TPARegistLocalInfo, *PTPARegistLocalInfo;


typedef struct tagPARegName
{
	EmPAAddrType m_emPAAddrType;                 //ע������type
	s8     m_achUserName[TPMODULE_MAX_NAME_LEN+1];     //ע����
	tagPARegName()
	{
		memset( this, 0, sizeof(tagPARegName) );
	}
}TPARegName,*PTPARegName;

typedef struct tagPARegCfg
{
	u32      dwHostIP;		 //ע������IP��ַ
	u16      wHostPort;      //ע�������˿�
	u32      dwRegIP;        //ע�������IP��ַ
	u16      wRegPort;	     //ע��������˿�
	u16      wExpire;

	s32		           m_nPARegNameSize;                       //ʵ�ʱ�������
	TPARegName         m_atPARegName[TPMODULE_REGNAME_SIZE];         //ע�����֧�ֶ��
	TPARegistLocalInfo m_tRegistLocalInfo;
	EmPAConnection	m_emConnection;	//ע���ַ����

	tagPARegCfg()
	{
		memset( this, 0, sizeof(tagPARegCfg) );
		m_emConnection = emPAUdpConnection;
	}
}TPARegCfg,*PTPARegCfg;


//������ж���Ĳ���
typedef struct tagCallInfoTP
{
	//EmPAEndpointType		  m_emEndpointType;
	EmPASipLevel			  m_emSipLevel;
	s32                       m_nScreenNum;                           //������
	
public:
	tagCallInfoTP()
	{
		Clear();
	}
	
	void Clear()
	{
		//m_emEndpointType = emPAEndpointTypeUnknown;
		m_emSipLevel = emPASipUnKnown;
		m_nScreenNum = TPMODULE_INVALID_VALUE;
	}
}TCallInfoTP;


//ר����������Ĳ���
typedef struct tagDescriptTP
{
	BOOL32 m_bAudMix;
	s32	m_nScreenNo;                //�����
	s32	m_nPACapSignNum;
	EmPACapSign m_aemPACapSign[MAX_TP_STREAM_NUM];				 //��ʶ��С����, ����������ʱһ��Ҫ����˳�� ���У��� 
	TModuleTransportAddress m_atRtpAddr[MAX_TP_STREAM_NUM];
	TModuleTransportAddress m_atRtcpAddr[MAX_TP_STREAM_NUM];
	
	void Clear()
	{
		m_bAudMix = FALSE;
		m_nScreenNo = TPMODULE_INVALID_VALUE;
		m_nPACapSignNum = 0;
		for ( s32 i = 0; i < MAX_TP_STREAM_NUM; i++ )
		{
			m_aemPACapSign[i] = emPACapBig;
			m_atRtpAddr[i].Clear();
			m_atRtcpAddr[i].Clear();
		}
	}

	tagDescriptTP()
	{
		Clear();
	}

}TDescriptTP;

//��Ӧ��ÿһ������
typedef struct tagCallDescriptTP
{
	u16 m_wAudioNum;
	TDescriptTP m_tAudioList[MAX_AUDIO_NUM];     
	u16 m_wVideoNum;
	TDescriptTP m_tVideoList[MAX_VIDEO_NUM];

	tagCallDescriptTP()
	{
		Clear();
	}
	
	void Clear()
	{
		m_wAudioNum = 0;
		m_wVideoNum = 0;
		s32 i = 0;
		for ( i = 0; i < MAX_AUDIO_NUM; i++ )
		{
			m_tAudioList[i].Clear();
		}
		for ( i = 0; i < MAX_VIDEO_NUM; i++ )
		{
			m_tVideoList[i].Clear();
		}
	}

}TCallDescriptTP;

typedef struct tagChanDescriptTP
{
	TDescriptTP m_tLocalTP; //����TP����
	TDescriptTP m_tPeerTP;  //�Զ�TP����

	tagChanDescriptTP()
	{
		m_tLocalTP.Clear();
		m_tPeerTP.Clear();
	}

}TChanDescriptTP;

enum EmPAConfMsgType
{
	emPAConfMsgTypeBegin = 0,

		emPAChanMsgBegin = 1,
		emPAConfFastUpdate,//NULL
		emPAConfFlowCtrl,//wBitRate
		emPAChanMeetingSpeaker,//cns->ums �᳡�ڷ�����
		emPAChanSelecteCascad, //add-by wuhu cns��umsָ��ѡ��, ���� u16,��ʾ�᳡id
		emPAChanSelecteCascadRes, //ums�ظ�cnsѡ������� TPAChanSelecteCascadRes, ��ʾ���
        emPAChanSelecteCascadCancel, //ȡ��ѡ�����޲���
		emPAChanSelecteCascadCancelRes, //ȡ��ѡ�������  ����u32, ��ʾ��� 
		emPAChanSeeLocal,               //ums -> cns, �����أ��޲���
		emPAChanSeeLocalCancel,         //ums -> cns  ȡ�������أ��޲���
		emPAChanMsgEnd = 160,

		emPAConfMsgBegin = 161,
		emPAConfYouAreSeeing,//TYouAreSeeing ������ָʾ
		emPAConfBeChairman,//BOOL ums->cns ��Ϊ��ϯ
		emPAConfCascadingSpeaker,//TPACascadingSpeaker �������� �����᳡�ڷ�����
		emPAConfStartPoll,//TPAPollCmd �������� ������ѯ
		emPAConfStartPollAck,//TPAPollAck
		emPAConfPollNodeChange,//TPAPollNodeChange ��������
		emPAConfEndPoll,//u32(Reserved)
		emPAConfPollFastUpdate,//��������u32(Reserved)
		emPAConfStatusIndicate,//TPAConfStatusInd , ums->cns
		emPAConfPeerMuteCmd,//Զ������  TPAPeerMuteCmd
		emPAConfPeerMuteInd,//Զ������״ָ̬ʾ TPAPeerMuteInd
		emPAConfCallCascadingOff,//�����¼�δ���߻᳡ u16 epid
		emPAConfHangUpCascadingConf,//�Ҷ��¼����� THangupCascadingConf
		emPAConfNodeUpdateTrList,//֪ͨ���½����Ϣ TPAConfNodeUpdateTrList
		emPAConfNodeUpdateB2NewTrList,//֪ͨ���½����Ϣ TPAConfNodeUpdateB2NEWTrList
		emPAConfNodeDelTrList,//֪ͨɾ����� TPAConfNodeDelTrList
		emPAConfAudMixEpCmd,//�ϼ�֪ͨ�¼�����ĳ���˵�  TPAAudMixEpCmdTr
		emPAConfAudMixEpAck,// �¼�֪ͨ�ϼ�����ĳ���˵�Ľ�� TPAAudMixEpAckTr
		emPAConfAudMixEpStop,// �ϼ���֪ͨ�¼�ֹͣĳ���˵�Ļ��� u16
		emPAConfAudMixOpenNCmd,// �ϼ�֪ͨ�¼���Nģʽͨ�� TPAAudMixEpCmdTr
		emPAConfAudMixOpenNAck,// �¼�֪ͨ�ϼ���Nģʽͨ�� TPAAudMixEpAckTr
		emPAConfPeerSoundOffCmd,//Զ�˾��� TPAPeerMuteCmd
		emPAConfPeerSoundOffInd,//Զ�˾���ָʾ TPAPeerMuteInd
		emPARequestDualStreamCmd,//����˫�� TDualRequest
		emPARequestDualStreamInd,//����˫��ָʾ BOOl + EmDualReason + TDualRequest
		emPASendDualStream,//��˫�� TDualInfo
		emPASendDualStreamAck,//��˫����� TDualInfoAck
		emPAStopDualStream,//ֹͣ˫�� TPAEpKey
		emPADualStreamFastUpdate,//˫���ؼ�֡���� BOOL32ֵ
		emPAViewLocal,//������ u32(Reserved)
		emPACancelViewlocal,//ȡ�������� u32(Reserved)
		emPAStartRcvDualInd,//����˫��ָʾTPAEpKey
		emPAStopRcvDualInd,//ֹͣ����˫��ָʾEmDualReason
		emPAAddTvMonitorCmd,//����ǽ��� TPATvMonitorCmd 
		emPAAddTvMonitorInd,//����ǽ��� TPATvMonitorInd 
		emPAStopMonitorCmd,	//ֹͣ����ǽ�ļ��	u16
		emPAAskKeybyScreen,//ֹͣ����ǽ�ļ��	TPAAskKeyByScreenTr
		emPAPollDstNameInd,//֪ͨ��ѯĿ����Ϣ ,TPAPollDstName
		emPASrcDualNameInd,//֪ͨ˫��Դ��Ϣ TPAName
		emPAChairCapNotify,//֪ͨ�¼���ϯ��ϯ����
		emPAConfCnsList,   // UMS��CNS���᳡�б�,   ������ TPAConfCnsList;
		emPAConfStartPolling,    //cns��ums������ѯ,  �޲��������贫���������u32ֵ
        emPAConfStartPollingRes, //ums��Ӧcns��ѯ���, ������u32
		emPAConfClosePolling,    //cns��ums�ر���ѯ,   �޲��������贫���������u32ֵ
		emPAConfClosePollingRes, //ums��cns��Ӧ�ر���ѯ���,  ���� u32
		emPAConfNotifyPollingRes, //ums֪ͨcns��ǰ��ѯ���,   ���� BOOL32
		emPACascadeStartViewcmd,	//�ϼ�֪ͨ�¼�ѡ��ĳ���᳡ TPAViewCmd
		emPACascadeStartViewInd,	//�¼�֪ͨ�ϼ�ѡ��ĳ���᳡��� TPAViewAck
		emPACascadeStopView_cmd,	//�ϼ�֪ͨ�¼�ֹͣĳ��ѡ��	u16
		emPACascadeGetVidcmd,	//�ϼ������¼�ͼ�� TPAViewCmd
		emPACascadeGetVidInd,	//�¼������¼�ͼ���� TPAViewAck
		emPACascadeStopGetVidcmd,	//�ϼ�ֹ֪ͨͣ�¼�����	u16
		emPACascadeFlowCtrl,		//�ϼ�֪ͨ�¼�flowctrl�� ����TPAFlowControl
		
		emPAOpenAudChanCmd,         //����Ƶͨ��           TPAAudChanCmd
		emPAOpenAudChanAck,         //����Ƶͨ��Ӧ��       TPAAudChanAck
		emPAOpenVidChanCmd,         //����Ƶͨ��           TPAVidChanCmd
		emPAOpenVidChanAck,         //����Ƶͨ��Ӧ��       TPAVidChanAck
		emPACloseVidChanCmd,          //�ر���Ƶͨ��           u16
		
		emPATppConfAMixUpdate_Cmd,    //�����鿪��           TPAConfAuxMixInfo
		emPATppConfAMixUpdate_Ind,    //�������Ӧ           TPAConfAuxMixInfo
		emPATppConfAMixUpdate_Nty,    //���������ۿ���֪ͨ   TPAConfAuxMixInfo
		
		emPATppConfApplySpeaker_Cmd,  //�������л�������     TPAConfEpID
		emPATppConfApplySpeaker_Ind,  //�������л������˻�Ӧ TPAConfEpID,  EmPATpApplySpeakerRet 
		emPATppConfApplySpeaker_Nty,  //�������л�������֪ͨ TPAConfEpID
		
		emPATppConfMute_Cmd,          //���������Զ������      TPAConfEpID, BOOL,  TRUEָʾԶ��������FALSEȡ��Զ������
		emPATppConfMute_Ind,          //���������Զ��������Ӧ  TPAConfEpID, BOOL,  TRUEָʾԶ��������FALSEȡ��Զ������
		emPATppConfMute_Nty,          //���������Զ������֪ͨ  TPAConfEpID, BOOL,  TRUEָʾԶ��������FALSEȡ��Զ������

		emPATppConfQuiet_Cmd,         //���������Զ�˾���        TPAConfEpID, BOOL,  TRUEָʾԶ��������FALSEȡ��Զ������
		emPATppConfQuiet_Ind,		  //���������Զ�˾�����Ӧ    TPAConfEpID, BOOL,  TRUEָʾԶ��������FALSEȡ��Զ������
		emPATppConfQuiet_Nty,         //���������Զ�˾���֪ͨ    TPAConfEpID, BOOL,  TRUEָʾԶ��������FALSEȡ��Զ������
		
		emPATppConfStartDual_Cmd,     //������˫������          TPAConfEpID   
		emPATppConfStartDual_Ind,     //������˫������Ӧ��      TPAConfEpID,  EmPATPDualReason
		emPATppConfStopDual_Cmd,      //������ͣ˫������        TPAConfEpID
		emPATppConfStopDual_Ind,      //������ͣ˫������Ӧ��    TPAConfEpID,  EmPATPDualReason
		emPATppConfDualEp_Nty,        //������˫���᳡�㲥֪ͨ  TPAConfEpID

		emPATppInviteCnsByAlias_Cmd,  //��������ͨ�����������б��в����ڵĻ᳡          TPAAlias
		emPATppInviteCnsByAlias_Ind,  //��������ͨ�����������б��в����ڵĻ᳡��Ӧ      TPAAlias, EmPACnsCallReason
		emPATppInviteCnsByEpId_Cmd,   //��������ͨ�����ֺ����б��д��ڵĲ����߻᳡      u16 wEpId
		emPATppInviteCnsByEpId_Ind,   //��������ͨ�����ֺ����б��д��ڵĲ����߻᳡��Ӧ  u16 wEpId, EmPACnsCallReason
	
		emPATppHangupCns_Cmd,          //���Ҷ�ָ���᳡         u16 wEpId
		emPATppHangupCns_Ind,          //���Ҷ�ָ���᳡��Ӧ     u16 wEpId, EmPACnsCallReason
		emPATppHangupConf_Cmd,         //�Ҷϻ���                 �޲������贫���������u32ֵ
		
		emPATppUpdateConfTurnlist_Nty, //��ѯ�б�֪ͨ           TPAConfTurnInfo
		emPATppCallEPResult_Ind,       //���н����           TPAConfCallEpAddr, EmPACnsCallReason,  
		emPATppChairConfInfo_Nty,      //֪ͨ��ϯ������Ϣ       TPAChairConfInfo
		emPATppAudMixStatus_Nty,       //�᳡��������״̬֪ͨ   TPAAudMixStat

		emPAAdjustFrameRate_Cmd,  //TPAAdjustFrameRate
		emPAAdjustVidRes_Cmd,  //TPAAdjustVidRes
		
		emPAUmsDiscussScreenStat_Notify,      //����ģʽ�еĻ᳡����Ҫ�յ�����״̬֪ͨ, TPADisScreenStat 
		emPAUmsCnsSpeakerIndxAdjust_Notify,   //TPACascadingSpeaker
		
		emPAUmsDiscussFastUpdate_Req,         /*����Դ�᳡ID������ţ��Ϳ���ͨ��AskKeyByScreen����Ŀ��᳡�ķ���������ؼ�֡
		                                        TPADisAskKeyFrame */
		emPAUmsAudMixDisListOpr_Cmd,          //CNC -> CNS -> UMS, TPADisListOpr
		emPAUmsAudMixDisListOpr_Ind,          //UMS -> CNS -> CNC, TPADisListOpr

		emPAUmsCascadeOpenChairChan_Cmd,       // UMS �������� ����ϯͨ������, TPACascadeOpenChanCmd
		emPAUmsCascadeOpenChairChan_Ack,       // UMS �������� ����ϯͨ��Ӧ��, TPACascadeOpenChanAck

		emPAUmsCommonReasonToUI_Ind,           // ��Ϣ����: ums -> cns -> cnc, ��Ϣ����: TPAUmsReasonInd

        emPAUmsConfRecPlayState_Nty,            // ���·���״̬, ��Ϣ����: TPAUmsUpRecPlayState
        emPAUmsConfStopRecPlay_Req,             // ֹͣ�¼��ķ����޲��������贫���������u32ֵ
		
		emPAChanResetFastUpdate,				//ͨ����Ϣ������ȥ��ums�Ĺؼ�֡������u32
		emPAJoinWBConf_Cmd,						//��Ϣ�壺U32 dwDsIPAddr
		emPAJoinWBConf_Ind,					//��Ϣ�壺BOOL bIsSucc
		emPAHangupWBConf_Cmd,				//��Ϣ�壺Null
};

enum EmPAGetRegInfoType
{
	emPAGetRegInfoType_CNS = 0,
	emPAGetRegInfoType_UMS,
	emPAGetRegInfoType_ALL
};
typedef struct tagPAGetRegInfo
{
	EmPAGetRegInfoType emType;
	u32    dwRegIP;         //ע�������IP��ַ
	u16    wRegPort;        //ע��������˿�
	u32    dwLocalIP;       //����ip
	u16    wLocalPort;      //���ض˿�
	
	tagPAGetRegInfo()
	{
		memset( this, 0, sizeof(tagPAGetRegInfo) );
	}
}TPAGetRegInfo;

 
typedef struct tagTPARegPackInfo
{
	u16 m_wPackSeq;       //����ţ���1��ʼ��0Ϊ��Чֵ
	u16 m_wTotalPackNum;  //������
	tagTPARegPackInfo()
	{
		m_wPackSeq = 0;
		m_wTotalPackNum = 0;
	}
	
}TPARegPackInfo, *PTPARegPackInfo;


typedef struct tagTPARegInfo
{
	u16		   m_wAliasNum;
	TPAAlias   m_atAlias[PA_REGNAME_SIZE];           //��ʱ��Ϊ���ֵΪ64������Ϊһ������
	EmPAEndpointType m_emSelfType;                   //ע�᷽ ��ϵͳ����(UMS��CNS)    
	
	tagTPARegInfo()
	{
		m_wAliasNum = 0;
		memset( m_atAlias, 0, sizeof( m_atAlias ) );
		m_emSelfType = emPAEndpointTypeUnknown;
	}
	
}TPARegInfo;

typedef struct tagTPARegInfoUms
{
	u16		   m_wAliasNum;
	TPAAlias  m_atAlias[PA_REGNAME_SIZE];       //��ʱ��Ϊ���ֵΪ64������Ϊһ������
	TPAIPAddress  m_atContactAddr[PA_CONTACT_ADDR_SIZE];//ע���ַ
	u32 m_dwExpires;//��ʱʱ��,��λ��
	EmPAConnection emPaConnection;
	TPARegistLocalInfo m_tPaRegistLocalInfo;
	
	tagTPARegInfoUms()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTPARegInfoUms));
	}
	
}TPARegInfoUms;

typedef struct tagTPARegInfoCns
{
	u16		   m_wAliasNum;
	TPAAlias  m_atAlias[PA_REGNAME_SIZE_CNS];       //��ʱ��Ϊ���ֵΪ2������Ϊһ������
	TPAIPAddress  m_atContactAddr[PA_CONTACT_ADDR_SIZE];//ע���ַ
	u32 m_dwExpires;//��ʱʱ��,��λ��
	EmPAConnection emPaConnection;
	TPARegistLocalInfo m_tPaRegistLocalInfo;
	
	tagTPARegInfoCns()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTPARegInfoCns));
	}
	
}TPARegInfoCns;

typedef struct tagTPARegPack
{
	TPARegPackInfo tPackInfo;
	EmPAGetRegInfoType emType;
	EmPAEndpointType  emEndpointType;
	u16	wTotalRegInfo;

	tagTPARegPack()
	{
		Clear();
		emType = emPAGetRegInfoType_ALL;
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTPARegPack));
	}

}TPARegPack;




#endif
