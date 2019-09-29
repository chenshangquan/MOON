#include "cnsSession.h"

class CCncPortDiagCtrl : public CCncPortDiagCtrlIF
{
public:
	CCncPortDiagCtrl( CCnsSession &cSession );
	~CCncPortDiagCtrl();
	//音频接口信息
	virtual TTpAudioPortInfo* GetAudioPortInfo();							
	virtual	u16 SetAudioPortInfoCmd( const TTpAudioPortInfo** atAudioPortInfo );		
	virtual	u16 DefaultAudioPortCmd( const TTpAudioPortInfo** atAudioPortInfo );		

	//网络丢包信息
	virtual u16 LostPacketInfoReq();
	virtual const u8& GetLostPacketInfo()const;			

	//上传下行速率
	virtual const TTPUpDownSpeedInfo& GetUpDownstreamRate()const;	

	//选择音视频矩阵方案的命令
	virtual u16 SelAVMatrixCmd( const TTPVgaMixInfo& tVgaMixInfo );
	//获取端口诊断结果
	virtual const TTPVideoDiagInfo& GetVideoDiagInfo()const;
	virtual const TTPAudioDiagInfo& GetAudioDiagInfo()const;

	//停止诊断测试请求
	virtual u16 StopAVMatrixReq();

	//Tpad列表
	virtual	const TTPTPadList& GetTpadList()const;								
	virtual	u16 UpdateTpadListReq();	

	//重启cns
	virtual u16 RebootCns();

	//升级T300
	virtual u16 UpgradeCns( const TTPFTPFileInfo& tVerFileInfo );

	//维护工具刷新界面请求
	virtual u16 ReqRefresh();

	//音频混音数配置命令
	virtual u16 AudiotMixerCmd( const u8** aAudioMixerInfo );
	virtual u8* GetAudioMixerInfo();
	virtual u16 DefaultMixerCmd( const u8** aAudioMixerInfo );

	//音频均衡器配置命令
	virtual u16 AudioEqualizerCmd( const TTPEqualizer** atEqualizer );
	virtual TTPEqualizer* GetAudioEqualizer();
	virtual u16 DefaultEqCmd( const TTPEqualizer** atEqualizer );

	//呼叫服务器地址
	virtual u16 CallServerCmd( const TTPCallSerInfo& tCallSerInfo );
	virtual const TTPCallSerInfo& GetCallServerInfo()const;

	//升级服务器地址
	virtual u16 UpgradeSerCmd( const TTPUpgradeSer& tUpgradeSer );
	virtual const TTPUpgradeSer& GetUpgradeSerInfo()const;

	//台标文件上传成功通知
	virtual u16 ConfSignCmd( const BOOL& bOk, u8 byIndex );

	//会议优选格式
	virtual u16 VideoFormatCmd( const TTPVidForamt& tVidForamt );
	virtual const TTPVidForamt& GetVideoFormatInfo()const;

	//演示优选格式
	virtual u16 DualVideoFormatCmd( const TTPVidForamt& tVidForamt );
	virtual const TTPVidForamt& GetDualVideoFormatInfo()const;

	//单屏码率
	virtual u16 CallRateCmd( const u16 wCallRate );
	virtual const u16 GetCallRate()const;

	//演示码率
	virtual u16 DualCallRateCmd( const u16 wDualCallRate );
	virtual const u16 GetDualCallRate()const;

	//会议轮询
	virtual u16 ConfPollCmd( const TTPPollInfo& tPollInfo );
	virtual const TTPPollInfo& GetConfPollInfo()const;

	//会议讨论
	virtual u16 ConfDisCmd( const BOOL& bDis );
	virtual const BOOL& GetConfDisInfo()const;

	//音频格式
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