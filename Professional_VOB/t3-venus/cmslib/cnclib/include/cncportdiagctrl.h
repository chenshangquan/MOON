#include "cnsSession.h"

class CCncPortDiagCtrl : public CCncPortDiagCtrlIF
{
public:
	CCncPortDiagCtrl( CCnsSession &cSession );
	~CCncPortDiagCtrl();
	//��Ƶ�ӿ���Ϣ
	virtual TTpAudioPortInfo* GetAudioPortInfo();							
	virtual	u16 SetAudioPortInfoCmd( const TTpAudioPortInfo** atAudioPortInfo );		
	virtual	u16 DefaultAudioPortCmd( const TTpAudioPortInfo** atAudioPortInfo );		

	//���綪����Ϣ
	virtual u16 LostPacketInfoReq();
	virtual const u8& GetLostPacketInfo()const;			

	//�ϴ���������
	virtual const TTPUpDownSpeedInfo& GetUpDownstreamRate()const;	

	//ѡ������Ƶ���󷽰�������
	virtual u16 SelAVMatrixCmd( const TTPVgaMixInfo& tVgaMixInfo );
	//��ȡ�˿���Ͻ��
	virtual const TTPVideoDiagInfo& GetVideoDiagInfo()const;
	virtual const TTPAudioDiagInfo& GetAudioDiagInfo()const;

	//ֹͣ��ϲ�������
	virtual u16 StopAVMatrixReq();

	//Tpad�б�
	virtual	const TTPTPadList& GetTpadList()const;								
	virtual	u16 UpdateTpadListReq();	

	//����cns
	virtual u16 RebootCns();

	//����T300
	virtual u16 UpgradeCns( const TTPFTPFileInfo& tVerFileInfo );

	//ά������ˢ�½�������
	virtual u16 ReqRefresh();

	//��Ƶ��������������
	virtual u16 AudiotMixerCmd( const u8** aAudioMixerInfo );
	virtual u8* GetAudioMixerInfo();
	virtual u16 DefaultMixerCmd( const u8** aAudioMixerInfo );

	//��Ƶ��������������
	virtual u16 AudioEqualizerCmd( const TTPEqualizer** atEqualizer );
	virtual TTPEqualizer* GetAudioEqualizer();
	virtual u16 DefaultEqCmd( const TTPEqualizer** atEqualizer );

	//���з�������ַ
	virtual u16 CallServerCmd( const TTPCallSerInfo& tCallSerInfo );
	virtual const TTPCallSerInfo& GetCallServerInfo()const;

	//������������ַ
	virtual u16 UpgradeSerCmd( const TTPUpgradeSer& tUpgradeSer );
	virtual const TTPUpgradeSer& GetUpgradeSerInfo()const;

	//̨���ļ��ϴ��ɹ�֪ͨ
	virtual u16 ConfSignCmd( const BOOL& bOk, u8 byIndex );

	//������ѡ��ʽ
	virtual u16 VideoFormatCmd( const TTPVidForamt& tVidForamt );
	virtual const TTPVidForamt& GetVideoFormatInfo()const;

	//��ʾ��ѡ��ʽ
	virtual u16 DualVideoFormatCmd( const TTPVidForamt& tVidForamt );
	virtual const TTPVidForamt& GetDualVideoFormatInfo()const;

	//��������
	virtual u16 CallRateCmd( const u16 wCallRate );
	virtual const u16 GetCallRate()const;

	//��ʾ����
	virtual u16 DualCallRateCmd( const u16 wDualCallRate );
	virtual const u16 GetDualCallRate()const;

	//������ѯ
	virtual u16 ConfPollCmd( const TTPPollInfo& tPollInfo );
	virtual const TTPPollInfo& GetConfPollInfo()const;

	//��������
	virtual u16 ConfDisCmd( const BOOL& bDis );
	virtual const BOOL& GetConfDisInfo()const;

	//��Ƶ��ʽ
	virtual u16 AudioFormatCmd( const EmTpAudioFormat& emAudioFormat );
	virtual const EmTpAudioFormat& GetAudioFormatInfo() const;
protected:
	virtual void OnTimeOut(u16 wEvent); 
    virtual void DispEvent(const CMessage &cMsg);
	void BuildEventsMap();
	void OnLinkBreak(const CMessage& cMsg);

	void OnAudioPortInfoInd(const CMessage& cMsg);
	void OnDefaultAudPortInd(const CMessage& cMsg);
	void OnLostPacketInfoRsp(const CMessage& cMsg);
	void OnUpDownstreamRateNty(const CMessage& cMsg);
	void OnAVMatrixInfoInd(const CMessage& cMsg);
	void OnTpadListRsp(const CMessage& cMsg);
	void OnTpadListNty(const CMessage& cMsg);

	void OnAudiotMixerInd(const CMessage& cMsg);
	void OnDefaulttMixerInd(const CMessage& cMsg);
	void OnAudioEqualizerInd(const CMessage& cMsg);
	void OnDefaultEqInd(const CMessage& cMsg);
	void OnUpgradeCnsInd(const CMessage& cMsg);
	void OnCallServerNty(const CMessage& cMsg);
	void OnCallServerInd(const CMessage& cMsg);

	void OnUpgradeSerNty(const CMessage& cMsg);
	void OnUpgradeSerInd(const CMessage& cMsg);

	void OnVideoFormatInd(const CMessage& cMsg);
	void OnDualVideoFormatInd(const CMessage& cMsg);

	void OnCallRateInd(const CMessage& cMsg);
	void OnDualCallRateInd(const CMessage& cMsg);

	void OnConfPollInd(const CMessage& cMsg);
	void OnConfDisInd(const CMessage& cMsg);

	void OnVerInfoNty(const CMessage& cMsg);
	void OnAudioFormatInd( const CMessage& cMsg );

	void OnStopAVMatrixRsp(const CMessage& cMsg);
private:
	CCnsSession		*m_pSession;
	TTpAudioPortInfo	m_atAudioPortInfo[3];
	u8	m_aAudioMixerInfo[4];
	u8	m_LostPacketInfo;
	TTPAudioDiagInfo	m_tAudioDiagInfo;
	TTPVideoDiagInfo	m_tVideoDiagInfo;
	TTPTPadList		m_tTPadList;
	TTPUpDownSpeedInfo		m_tUpDownSpeedInfo;

	TTPEqualizer     m_atEqualizer[3];
	TTPCallSerInfo   m_tCallSerInfo;
	TTPUpgradeSer	 m_tUpgradeSer;
	TTPVidForamt	 m_tVidForamt;
	TTPVidForamt	 m_tDualVidForamt;
	TTPPollInfo		 m_tPollInfo;
	EmTpAudioFormat  m_emAudioFormat;
	BOOL m_bDis;
	u16	 m_wCallRate;
	u16  m_wDualCallRate;
};