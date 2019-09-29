        #ifndef _MT_INTEGRATION_TEST_H
#define _MT_INTEGRATION_TEST_H

#include "kdvdef.h"
#include "mtctrllib.h"
#include "ummessagestruct.h"
#include "evusermanage.h"
#include "addrbook.h"

#define VER_MT_TESTLIB "testlib36.10.01.04.00.050412"
API void testlibver();

#pragma pack(1)

//�ն˱��
typedef struct tagTerLabel
{
	u8	byMcuNo;
	u8	byTerNo;
}IT_TERLABEL,*IT_PTERLABEL;

//�ն���Ϣ
typedef struct tagTerInfo
{
	IT_TERLABEL label;	//���
	s8	name[32];		//����
}IT_TERINFO,*IT_PTERINFO;

// ͨ��״̬�ṹ(0:�ر�,1:��)
typedef struct tagChannelState
{
	u8		byVideoSend;	// ��Ƶ����ͨ��
	u8		byVideoRecv;	// ��Ƶ����ͨ��
	u8		byAudioSend;	// ��Ƶ����ͨ��
	u8		byAudioRecv;	// ��Ƶ����ͨ��
	u8		byH224Send;		// H224����ͨ��
	u8		byH224Recv;		// H224����ͨ��
}IT_CHANSTATE,*IT_PCHANSTATE;

// ʱ���׼��ʽ
typedef struct SysTime
{
	u8 bySec;	/* seconds after the minute	- [0, 59] */
	u8 byMin;	/* minutes after the hour	- [0, 59] */
	u8 byHour;	/* hours after midnight		- [0, 23] */
	u8 byDay;	/* day of the month		- [1, 31] */
	u8 byMon;	/* months since January		- [0, 11] */
	u8 byYear;	/* years since 1900	*/
}IT_SYSTIME,*IT_PSYSTIME;

//����״̬
typedef struct tagConfState
{
	u8				byMtBoardType;	//�ն˰忨����(0:win,1:8010,2:8010a,3:8018,4:imt,5:8010c)
	u8				byMtStat;		//�ն�״̬
	u8				byConfMode;		//����ģʽ,Ĭ��ΪP2P
	u8				bRasReg;		//�Ƿ���GK��ע��ɹ�
	u8				bLoopTest;		//�Ƿ����Ի�
	u16				wConfRate;		//��������
	u16				wTerNum;		//����ն˸���
	IT_TERINFO		atTerList[ CONF_MT_CAPACITY ];	//�ն��б�	
	IT_TERLABEL		tLocal;			//���˱��
	IT_TERLABEL		tChair;			//��ϯ
	IT_TERLABEL		tBroadcaster;	//������
	IT_TERLABEL		tViewing;		//�������ڹۿ����ն�
	u8				bChimeIn;		//�Ƿ��ڲ廰
	u8				bVac;			//�Ƿ�����������
	u8				bDual;			//˫��״̬,���������ߺͽ�����
	u8				byDualSrc;		//˫��Դ(1:VGA,2:PC,3:Video)
	u8				byDualProtocol;	//˫��ʹ�õ�Э��(1:h245,2:h239)
	u8				byDualMode;		//˫����ʾģʽ(1:����˫��,2:˫��˫��)
	u8				bMtcConnect;	//�տ�����״̬
	u8				byEncryptMode;	//��������(1:������,2:AES,3:DES)
	CLoginRequest	cLoginUser;		//��½�û���Ϣ
	IT_SYSTIME		tSysTime;		//ϵͳʱ��
	IT_CHANSTATE	tChanState;		// ͨ��״̬
}IT_CONFSTAT,*IT_PCONFSTAT;

//��ѭ״̬
typedef struct  tagPollState
{
	u8		bPolling;		//��ѯ״̬
	u8		byPollMedia;	//��ѭý��ģʽ
	u8		byPollIntvl;	//��ѯ���
	u8		byPollNum;		//��ѯ���ն���
	IT_TERLABEL	atPollList[CTRL_POLL_MAXNUM];	//��ѯ�б�
}IT_POLLSTAT,*IT_PPOLLSTAT;

//����״̬
typedef struct tagEncState
{
	u8	byDevId;		//������ID
	u8	byVideoFormat;	//��Ƶ��ʽ
	u8	byAudioFormat;	//��Ƶ��ʽ
	u8	byEncVol;		//��������
	u8	bMute;			//�Ƿ�����
	u8	bAudioEncoding;	//�Ƿ���Ƶ����
	u8	bVideoEncoding;	//�Ƿ���Ƶ����
	u8	bAudioSending;	//�Ƿ�����Ƶ
	u8	bVideoSending;	//�Ƿ�����Ƶ
	u16	wBitRate;		//��������(������)
}IT_ENCSTAT,*IT_PENCSTAT;

//����״̬
typedef struct tagDecState
{
	u8	 byDevId;			//������ID
	u8	 byVideoFormat;		//��Ƶ��ʽ
	u8	 byAudioFormat;		//��Ƶ��ʽ
	u8	 byDecVol;			//��������
	u8	 bQuiet;			//�Ƿ���
	u8	 bAudioDecoding;	//�Ƿ���Ƶ����
	u8	 bVideoDecoding;	//�Ƿ���Ƶ����
	u8	 bAudioRecving;		//�Ƿ������Ƶ
	u8	 bVideoRecving;		//�Ƿ������Ƶ
	u8	 bAecEnable;		//�Ƿ�����������
}IT_DECSTAT,*IT_PDECSTAT;

//����ͷ״̬
typedef struct tagCameraState
{
	struct CamStat
	{
		u8	byNo;			//����ͷ��(1-4)
		u8	bStat;			//�Ƿ����� 1:���� 0:δ����
	};
	u8		byCtrlSrc;		//����Դ(����|Զ��)
	u8		byLocalCtrlNo;	//��ǰ���Ƶı�������ͷ(1-6)
	u8		byRemoteCtrlNo;	//��ǰ���Ƶ�Զ������ͷ(1-6)
	u8		byCamNum;		//���õ�����ͷ����
	u8		bFecc;			//�Ƿ�����Զң 1:yes 0:no
	CamStat	atCamList[4];	//����ͷ״̬
}IT_CAMERASTAT,*IT_PCAMERASTAT;

//����״̬
typedef struct tagMatrixState
{
	u8		bStat;			//�Ƿ����� 1:���� 0:δ����
	u8		byVideoSrc;		//��ǰ��ƵԴ
	u8		byAudioSrc;		//��ǰ��ƵԴ
	_TMATRIXSCHEME	tCurrentScheme;	//��ǰʹ�õķ���
}IT_MATRIXSTAT,*IT_PMATRIXSTAT;

// CODECMANAGER״̬
typedef struct tagCodecState
{
	u32 dwAudioOutputPower;	//	��Ƶ������� 
	u32 dwAudioInputPower;	//	��Ƶ���빦��

}IT_CODECSTATE,*IT_PCODECSTATE;

// ��ַ��״̬
typedef struct tagAddrBookState
{
	u32		dwAddrEntryNum;			// ��ǰ��ַ������Ŀ�ĸ���(������)
	u32		dwAddrGroupNum;			// ��ǰ��ַ���л�����ĸ���(������)
	u8		bAddrEntryIsExist;		// ��ѯĳ����Ŀ�Ƿ����(1:����,0:������)
	u8		bAddrGroupIsExist;		// ��ѯĳ���������Ƿ����(1:����,0:������)
	u8      abyEntryInfo[ 1024 ];	// ���ڷ��ز�ѯĿ����Ŀ����Ϣ(������)
}IT_ADDRBOOK,*IT_PADDRBOOK;


#pragma pack()

class CMtCtrlRmtTest
{
public:
	CMtCtrlRmtTest() : m_dwTesterNode( INVALID_NODE ) {}
	virtual ~CMtCtrlRmtTest() {}
	/////////////////////////////��·�����ͳ���////////////////////////////////
	BOOL LinkInstance( u32 dwIp, u16 wPort = PORT_MT );
	void DisLinkInstance( void );
	BOOL IsLinked();
	void SetTesterNode( u32 dwNodeId ) { m_dwTesterNode = dwNodeId; }

	/////////////////////////////��ϸ��ѯ�ӿ�//////////////////////////////////

	// �ն�����
	//////////////////////////////////////////////////////////////////////////
	//�ն���Ϣ����
	BOOL	TerInfoCfgQuery( _PTTERCFG ptTerCfg );
	//��������
	BOOL	NetCfgQuery( _PTNETCFG ptNetCfg );
	//��������
	BOOL	CallCfgQuery( _PTCALLCFG ptCallCfg );
	//��Ƶ����
	BOOL	VideoCfgQuery( _PTVENCPARAM ptVEncCfg, _PTVDECPARAM ptVDecCfg, u8 byId = 0 );
	//��Ƶ����
	BOOL	AudioCfgQuery( _PTAENCPARAM ptAEncCfg, _PTADECPARAM ptADecCfg );
	//����ͷ����
	BOOL	CameraCfgQuery( _PTDEVCFG ptCameraCfg, u8 byNo );
	//��������
	BOOL	MatrixCfgQuery( _PTDEVCFG ptMatrixCfg );
	//��ʾ����
	BOOL	OsdCfgQuery( _PTTERCFG ptOsdCfg );

	// �ն˻���״̬
	//////////////////////////////////////////////////////////////////////////
	//����״̬
	BOOL		ConfStatQuery( IT_PCONFSTAT ptConfState );		
	//����״̬
	BOOL	EncodeStatQuery( IT_PENCSTAT ptEncState, u8 byId = 0 );
	//����״̬
	BOOL	DecodeStatQuery( IT_PDECSTAT ptDecState, u8 byId = 0 );
	//����ͷ״̬
	BOOL	CameraStatQuery( IT_PCAMERASTAT ptCamState );
	//����״̬
	BOOL	MatrixStatQuery( IT_PMATRIXSTAT ptMatrixState );
	//��ѭ״̬
	BOOL	PollStatQuery( IT_PPOLLSTAT ptPollState );
	//����Ϣ��ѯ
	BOOL	LastSmsQuery( s8* sms,const u16 wBufLen );

	// Codec״̬��ѯ
	BOOL	CodecStateQuery( IT_PCODECSTATE ptCodecState );
	

	//////////////////////////////////��Ҫ��ѯ�ӿ�////////////////////////////////////

	// ����״̬
	//////////////////////////////////////////////////////////////////////////
	// ��ȡͨ��״̬
	BOOL GetChanState( IT_CHANSTATE *ptChanState = NULL );
	// �Ƿ����
	BOOL IsIdle();
	// �Ƿ��ں��н�����
	BOOL IsCalling();
	// �Ƿ��ڹ���������
	BOOL IsInCommon();
	// �Ƿ��ڻ�����(������Ե�Ͷ�����)
	BOOL IsInConf();
	// �Ƿ��ڶ���������
	BOOL IsUnLinking();
	// �Ƿ��ڴ���
	BOOL IsInSleep();
	// �Ƿ��ڶ�������
	BOOL IsInMultConf();
	// �Ƿ���p2p
	BOOL IsInP2PConf();
	// GK�Ƿ�ע��ɹ�
	BOOL IsGKRegSuccess();
	// �Ƿ����Ի�������
	BOOL IsInSelfTest();
	//��ȡ��ǰ��������
	BOOL GetConfRate( u16 *pwRate = NULL );
	// ��ȡ�ն��б�,����-1��ʾʧ��
	int GetTerList( IT_TERINFO* ptTerList = NULL, u16 wListLen = 0 );
	// ��ȡ���ն�mt��
	BOOL GetLocal( IT_TERINFO *ptTerInfo = NULL );
	// ��ȡ������
	BOOL GetSpeaker( IT_TERINFO *ptTerInfo = NULL );
	// ��ȡ��ϯ
	BOOL GetChairman( IT_TERINFO *ptTerInfo = NULL );
	// ��ȡ��ǰ��ƵԴ(��ǰ�ն˿�����ͼ����Դ)
	BOOL GetVideoSrc( IT_TERINFO *ptTerInfo = NULL );
	// �Ƿ�����
	BOOL IsSpeaker();
	// �Ƿ���ϯ
	BOOL IsChairman();
	// �Ƿ�廰
	BOOL IsChimeIn();
	// �Ƿ�����������
	BOOL IsVac();
	
	// �Ƿ�˫��
	BOOL IsDual();
	// ��ȡ˫��Դ����
	BOOL GetDualSrcType( u8 *pbyType = NULL );
	// ��ȡ˫��Э������
	BOOL GetDualProtocolType( u8 *pbyType = NULL );
	// ��ȡ˫����ʾģʽ
	BOOL GetDualMode( u8 *pbyType = NULL );

	// �Ƿ��Ǽ��ܻ���
	BOOL IsEncryptConf();
	// ����ģʽ
	BOOL GetEncryptMode( u8 *pbyType = NULL );
	// ��ȡ�ն˰忨����
	BOOL GetMtBoardType( u8* pbyType = NULL );

	// ��ȡ��ǰ��һ·��Ƶ�����ʽ
	BOOL GetMainVideoEncType( u8 *pbyType = NULL );
	// ��ȡ��ǰ�ڶ�·��Ƶ�����ʽ
	BOOL GetSecVideoEncType( u8 *pbyType = NULL );
	// ��ȡ��ǰ��һ·��Ƶ�����ʽ
	BOOL GetMainVideoDecType( u8 *pbyType = NULL );
	// ��ȡ��ǰ�ڶ�·��Ƶ�����ʽ
	BOOL GetSecVideoDecType( u8 *pbyType = NULL );
	// ��ȡ��ǰ��һ·��Ƶ�����ʽ
	BOOL GetMainAudioEncType( u8 *pbyType = NULL );
	// ��ȡ��ǰ��һ·��Ƶ�����ʽ
	BOOL GetMainAudioDecType( u8 *pbyType = NULL );

	//�Ƿ��� 
	BOOL IsLocalSpeakerMute();
	//�Ƿ�����
	BOOL IsLocalMicMute();
	//�������������
	BOOL GetLocalSpeakerVolume(s32 *pnVolNum);
	//�����˷�����
	BOOL GetLocalMicVolume(s32 *pnVolNum);
	
	//��ѯ�տ��Ƿ��������ն�
	BOOL IsMtcConnectedMt();
	//��õ�ǰ��½�û�
	BOOL GetConnectedUser(CLoginRequest *pcLoginuser);
	//��õ�ַ����Ŀ����
	BOOL GetEntriesCount(s32 *pnCount);
	//��ѯһ��Ŀ�Ƿ����
	BOOL  IsEntryExist(CAddrEntry *pcEntry);
	//���������
	BOOL GetGroupCount(s32 *pnCount);	
	//��ѯһ���Ƿ����
	BOOL IsGroupExist(CAddrMultiSetEntry *pcAddrMentry);

	// ��ȡϵͳʱ��
	BOOL GetSysTime( IT_SYSTIME* ptSysTime );
	
protected:
	void	PostMsg(u16 wEvent,void* pContent = NULL,u16 wLen =0);
	BOOL	IntTestQuery(u16  wEvent,
						 void* buf,
						 u16  wBufLen,
						 u16* pwRetLen,
						 const void* pParam = NULL,
						 u16  wParamLen = 0,
						 u16  wAppId = AID_MT_CTRL );
protected:
	u32	m_dwTesterNode;

};

#endif 