
#ifndef _SHORT_MESSAGE_HEADER
#define _SHORT_MESSAGE_HEADER

#include "tpstruct.h"
// ����Ϣ�ṹ
class CShortMsg
{
public:
    CShortMsg();
    CShortMsg( EmSMSType emSMSType,TMtId tMtSrc, u8 byDstNum,
			       TMtId* ptDstMt, u8 byRollSpeed, u8 byRollTimes, u8* pchText );
	BOOL Marshal( u8 *pchContent, u16 wInLen, u16 &wOutLen );//pack
	BOOL UnMarshal( u8 *pchContent, u16 wInLen );            //unpack
	void SetType( EmSMSType emSMSType ) { m_emType = emSMSType; };//���ù�����Ϣ����
	EmSMSType GetType( void ) { return m_emType; }//��ȡ������Ϣ����
	void SetRollTimes ( u8 byTimes ) { m_byRollTimes = byTimes; } //���ù�������
	u8 GetRollTimes( void ) { return m_byRollTimes; }  //��ȡ��������
	void SetRollSpeed( u8 byRollSpeed ) { m_byRollSpeed = byRollSpeed;} //���ù����ٶ�
	u8 GetRollSpeed( void ) { return m_byRollSpeed; }  //��ȡ�����ٶ�
	void SetMsgSrcMtId( TMtId tMtId ) { SetMsgSrcMtId( tMtId.byMcuNo, tMtId.byTerNo ); } //������ϢԴ
	void SetMsgSrcMtId( u8 byMcuNo, u8 byMtNo ) { m_tMtSrc.byMcuNo = byMcuNo, m_tMtSrc.byTerNo  = byMtNo; }  //������ϢԴ
	TMtId GetMsgSrcMtId( void ) { return m_tMtSrc; } //��ȡ��Ϣ��Դ�ն�ID
	u8   GetDstMtNum( void ) { return m_byDstNum; }//��ȡĿ���ն˸���
	void AddDstMt( const TMtId *ptMtList, u16 wDstMtNum ); //����Ŀ���ն��б�
	void AddDstMt( u8 byMcuNo, u8 byMtNo ); //����Ŀ���ն��б�
	void AddDstMt( TMtId tMt );      //����Ŀ���ն��б�
	BOOL GetDstMt( TMtId &tMt, u8 byIndex  ); //��ȡָ����Ŀ���ն��б�
	u8  GetDstMt( TMtId *ptMt, u8 byMaxCount  ); //��ȡָ�������ն��б�
	s8 *GetText( void ) { return m_abyContent; } //��ȡ�ı�
	void SetText( const s8* pbyText, u16 wTextLen );  //�����ı�


private :
	EmSMSType m_emType;
	TMtId m_tMtSrc;
	u8   m_byDstNum;
	TMtId m_atMtDst[MT_MAXNUM_SMSDST];
	u8    m_byRollSpeed; //�ٶ� (1-5)
	u8    m_byRollTimes; //��������
	s8    m_abyContent[MT_MAXLEN_SMSTEXT+1];
};

//const default value
class CDefaultCfg
{
protected:
	CDefaultCfg(){};
	CDefaultCfg(CDefaultCfg&){};
public:
	~CDefaultCfg(){};
	static CDefaultCfg* GetInstance();
public:
	void Serial(TSerialCfg& tCfg);
	void ImageAdjustParam(TImageAdjustParam& tCfg, EmMtModel emModel);
	void ResetOsdCfg( TOsdCfg& tCfg );
	void ResetUserCfg( TUserCfg& tUserCfg );
	void ResetH323Cfg( TH323Cfg& tCfg );
	void ResetSipCfg( TSipCfg& tSipCfg );
	void ResetAVPriorCfg(TAVPriorStrategy& tAVPriorCfg);
	void ResetEthnetCfg( TEthnetInfo& tEthInfo );
	void ResetSNMPCfg( TSNMPCfg& tSnmpCfg );
	void ResetCommonBasePort( u32& dwTCPPort, u32& dwUDPPort );
	void ResetLostPacketResend( TLostPackResend &tCfg );
	void ResetStreamCfg( TStreamMedia &tStreamCfg );
	void ResetPCVideoParam( TVideoParam& tVideoCfg , EmMtModel emModel);//modified by huzhiding
	void ResetCamerCfg( TCameraCfg& tCfg );
	void ResetQosCfg( TIPQoS& tCfg  );
	void ResetE1Cfg( TE1Config& tCfg );
    void ResetPPOECfg( TPPPOECfg& tcfg );
	void ResetVideoDisplayFrm( TVideoDisplayFrm& tFrm );
	void ResetCallProtocal( TGuideCfg& tGuideCfg );
	void ResetAudioPrecedence( u32& dwAudioPrecedence );
	void ResetIPQOs( TIPQoS& val );
	void ResetMainImageCode( TVideoParam& val,EmMtModel emModel  );
	void ResetDualImageCode( TVideoParam& val,EmMtModel emModel  );//added by huzhiding
	void ResetIsSendingStaticPic( BOOL& bSendStaticPic );
	void ResetMTU( s32& dwVal );
	void ResetMiscCfg( TMiscCfg& tInfo );
	void ResetHDResOutputParam( u32& dwHDResEnable );
	void ResetHDPicPlusParam( BOOL& bPicPlusEnable );
	void ResetConfTime( BOOL& bConfTimeShow );
	void ResetFarCtrl( BOOL& bFarCtrlEnable );
public:
	void ResetAll();
};


class CAddrGroupOpt
{
public:
    CAddrGroupOpt();
   	BOOL Marshal( u8 *pchContent, u16 wInLen, u16 &wOutLen );//�ֽ���ת���Լ�����
	BOOL UnMarshal( u8 *pchContent, u16 wInLen );            
	void SetType( EmAddrGroupOptType emType ){ m_emOptType = emType; }//���ò�������
	EmAddrGroupOptType GetType(){ return m_emOptType; }//��ȡ��������
	void SetVersion( u8 byVersion ){ m_byVersion = byVersion; }//���ð汾
	u8 GetVersion(){ return m_byVersion; }//��ȡ�汾
    //�������к�����Ϣ
    void SetSiteCallInfo( TSitecallInformation tSiteCallInfo ) { m_tSiteCallInfo = tSiteCallInfo; }
	TSitecallInformation GetSiteCallInfo(){ return m_tSiteCallInfo; }//��ȡ���к�����Ϣ

	//���û���ģ����Ϣ
	void SetConfTemplateInfo( TConfBaseInfo tConfTemplateInfo ) { m_tConfInfo = tConfTemplateInfo; }
	TConfBaseInfo GetConfTemplateInfo(){ return m_tConfInfo; }//��ȡ����ģ����Ϣ

private :
	BOOL Check( u16 wLen ); 
    TConfBaseInfo m_tConfInfo;
	TSitecallInformation m_tSiteCallInfo;
	EmAddrGroupOptType m_emOptType;
	u8    m_byVersion;
	s8    m_abyContent[MT_MAX_ADDRUSERDEF_LEN+1];
};

class CKedaPeerDualCap
{
	typedef struct tagKedaCapItem
	{
		EmVideoResolution emVRes;
		u8   byFps;
public:
	tagKedaCapItem()
	{
		memset( this, 0, sizeof(struct tagKedaCapItem) );
	}
	}TKedaCapItem;
	
	typedef struct tagKedaModuleCap
	{
		char achModuleName[256];
		u32 dwCapItemNum;
		TKedaCapItem *ptCapItem;
public:
	tagKedaModuleCap()
	{
		memset( this, 0, sizeof( struct tagKedaModuleCap ) );
	}
	void Release()
	{
		if ( ptCapItem )
		{
			delete [] ptCapItem;
			ptCapItem = NULL;
		}
	}
	}TKedaModuleCap;
	
	typedef struct tagKedaCapTable
	{
		u32 dwModuleNum;
		TKedaModuleCap *ptModuleCap;
public:
	tagKedaCapTable()
	{
		memset( this, 0, sizeof( struct tagKedaCapTable ) );
	}
	void Release()
	{
		if ( ptModuleCap )
		{
			for ( u32 i = 0; i < dwModuleNum; i++ )
			{
				ptModuleCap[i].Release();
			}
			delete [] ptModuleCap;
			ptModuleCap = NULL;
		}
	}
	}TKedaCapTable, PTKedaCapTable;
	
public:
	~CKedaPeerDualCap(){}
	static CKedaPeerDualCap* GetInstance();
	BOOL  ParseKedaDualVgaCapTable();
	BOOL  GetKedaMtCap( IN_PARAM char* pszModuleName, EmVideoResolution emVRes, u8 &byFps );
	void  PrintKedacapTable();
	
private:
	CKedaPeerDualCap(){ m_bParseSucceed = FALSE; }
	const char * GetKedaCapTableFile();
	BOOL  ReadStringVal(FILE *file, s8* const achBuf,
		u16 wLen,
		const s8*const  szSection,
		const s8*const szKey );
	BOOL  InstallKedaDualVgaCapTable();
	
private:
	static CKedaPeerDualCap* m_pcInstance;
	TKedaCapTable m_tKedaCapTable;
	BOOL m_bParseSucceed;
};


#endif

