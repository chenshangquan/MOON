#include "cnsSession.h"


class CCncCenterCtrl : public CCncCenterCtrlIF
{
public:
	CCncCenterCtrl(CCnsSession &cSession);
	virtual ~CCncCenterCtrl();

    /** 
	* ����  ����ϵͳ��Դ
	* @param [in]  emPower  ����
	* @return 
	* @remarks 
	*/
    virtual u16 SetSysPower( EmSchPower emPower );
    /** 
	* ����  ���õƹ�ȫ��
	* @param [in]  emLight  ����
	* @return 
	* @remarks 
	*/
    virtual u16 SetSysAllLight( EmSchLight emLight );
    /** 
	* ����  �������ƿ���
	* @param [in]  emMidLight  ����
	* @return 
	* @remarks 
	*/
    virtual u16 SetMainLight( EmSchMidLight emMidLight );
    /** 
	* ����  ���ø��ƿ���
	* @param [in]  emScrLight  ����
	* @return 
	* @remarks 
	*/
    virtual u16 SetAuxiLight( EmSchScrLight emScrLight );
    /** 
	* ����  ѡ����ӻ�
	* @param [in]  byIndex  ���
	* @return 
	* @remarks 
	*/
	virtual u16 SelectTV( u8 byIndex );
    /** 
	* ����  ���õ��ӻ���Դ
	* @param [in]  byIndex  ���
	* @return 
	* @remarks 
	*/
    virtual u16 SetTVPowerMode( u8 byIndex, EmTvPowerMode emMode );
    /** 
	* ����  ���õ��ӻ�����ģʽ
	* @param [in]  emMode  ����ģʽ
	* @return 
	* @remarks 
	*/
    virtual u16 SetTVAudVisMode( EmTVAudVisMode emMode );
    /** 
	* ����  ���õ��ӻ���ʾģʽ
	* @param [in]  emMode  ��ʾģʽ
	* @return 
	* @remarks 
	*/
    virtual u16 SetTVDisMode( EmTVDisplayMode emMode );
    /** 
	* ����  ���õ��ӻ�����ѡ��
	* @param [in]  emSelect  ����ѡ��
	* @return 
	*/
    virtual u16 SetTVInpSelect( u8 byIndex, EmTVInputSelect emSelect );
    /** 
	* ����  ��ȡ���ӻ�����
	* @return TCentreTVCfg*  ���ӻ���������ָ��
	*/
    virtual TCentreTVCfg* GetCentreTVCfg(); 

    /** 
	* ����  �����ĵ����������
    * @param [in]  emPower  ����
	* @return 
	*/
    virtual u16 SetDCamPower( EmDCamPower emPower );
    /** 
	* ����  �����ĵ�������Զ��۽�ģʽ
	* @param [in]  emMode  ģʽ
	* @return 
	*/
    virtual u16 SetDCamAFMode( EmDCamAFMode emMode );
    /** 
	* ����  �����ĵ��������ƽ��ģʽ
	* @param [in]  emMode  ģʽ
	* @return 
	*/
    virtual u16 SetDCamWBMode( EmDCamWBMode emMode );
    /** 
	* ����  �����ĵ��������Ұ����
	* @param [in]  emZoom  ��Ұ
	* @return 
	*/
    virtual u16 SetDCamZoom( EmDCamZoom emZoom, EmCnAction emAction );
    /** 
	* ����  �����ĵ������Ԥ��λ
	* @param [in]  emNum  Ԥ��λ
	* @return 
	*/
    virtual u16 SetDCamPreset( EmDCamPresetNum emNum );
    /** 
	* ����  �����ĵ������Ԥ��λ
	* @param [in]  emNum  Ԥ��λ
	* @return 
	*/
    virtual u16 SetDCamRecall( EmDCamRecallNum emNum );

    /** 
	* ����  ���ȿյ��¶�
	* @param [in]  wTemp  �¶�
	* @return 
	*/
    virtual u16 SetACTemp( u8 byTemp );
    /** 
	* ����  ���ȿյ��¶�
	* @param [in]  wTemp  �¶�
	* @return 
	*/
    u16 SetACMode( EmCentreACMode emMode );
    /** 
	* ����  �����·����
	* @param [in]  byVol  ����
	* @return 
	*/
    virtual u16 SetACAirVol( EmCentreACAirVol emAirVol );
	/** 
	* ����  ���ȿյ������Դ����
	* @param [in] empower ��Դ����
	* @return 
	*/
 /*   virtual u16 SetAirPower( EmCentreACPower emPower );*/
    /** 
	* ����  ѡ��յ�
	* @param [in]  byIndex  ���
	* @return 
	* @remarks 
	*/
	virtual u16 SelectAir( u8 byIndex );
	/** 
	* ����  ��ȡ�յ���������
	* @return TCentreACCfg*  �յ���������ָ��
	*/
    virtual void GetCentreACCfg( vector<TCentreACCfg> &vecTCentreACCfg )const; 
    /** 
	* ����  ���ÿյ���Դ
	* @param [in]  byIndex  ���
	* @return 
	* @remarks 
	*/
    virtual u16 SetACPowerMode( u8 byIndex, EmCentreACPower emMode );
    /** 
	* ����  ����Ӧ�õ�����
	* @param [in]  byIndex  ���
	* @return 
	* @remarks 
	*/
	virtual u16 SetApplyToAll( u8 byIndex, BOOL** atbIsCtrl );
	virtual BOOL* GetApplyToAllInfo();

	virtual u16 SetCurtainState( BOOL** bIsCtrl, EmCurAction emCurAction );

	void GetCentreCurName( vector<TCentreCurName> &vecTCentreCurName )const;
	
	virtual u16 SetDisplayCmd( BOOL bDisplay, const TTPDisplayType& tDisplayType1, const TTPDisplayType& tDisplayType3 );
	virtual const BOOL& GetDisplayState() const;
	virtual const TTPDisplayType& GetDisplayType1() const;
	virtual const TTPDisplayType& GetDisplayType3() const;

protected:
    virtual void OnTimeOut(u16 wEvent); 
    virtual void DispEvent(const CMessage &cMsg);
	void BuildEventsMap();
	//������Ϣ����
	void OnLinkBreak(const CMessage& cMsg);


    //�������
    void OnSchStateNty(const CMessage& cMsg);
    void OnSchTempNty(const CMessage& cMsg);
    void OnSchPowerInd(const CMessage& cMsg);
    void OnSchPowerNty(const CMessage& cMsg);
    void OnSchLightInd(const CMessage& cMsg);
    void OnSchMainLightInd(const CMessage& cMsg);
    void OnSchAuxiLightInd(const CMessage& cMsg);
    void OnSchLightNty(const CMessage& cMsg);
    //��ʾ��
    void OnTvStateNty(const CMessage& cMsg);
    void OnSeleteTvInd(const CMessage& cMsg);
    void OnTvPowerModeInd(const CMessage& cMsg);
    void OnTvAudVisModeInd(const CMessage& cMsg);
    void OnTvDisModeInd(const CMessage& cMsg);
    void OnTvAudInpSelectInd(const CMessage& cMsg);
    //�ĵ������
    void OnDCamPowerInd(const CMessage& cMsg);
    void OnDCamAFModeInd(const CMessage& cMsg);
    void OnDCamWBModeInd(const CMessage& cMsg);
    void OnDCamZoomInd(const CMessage& cMsg);
    void OnDCamPresetInd(const CMessage& cMsg);
    void OnDCamRecallInd(const CMessage& cMsg);
    void OnDCamStateNty(const CMessage& cMsg);
    //�յ�
    void OnACTempInd(const CMessage& cMsg);
    void OnACModeInd(const CMessage& cMsg);
    void OnACAirVolInd(const CMessage& cMsg);
    void OnACStateNty(const CMessage& cMsg);
	void OnAirPowerInd(const CMessage& cMsg);
	void OnSeleteAirInd(const CMessage& cMsg);
	void OnApplyToAllInd(const CMessage& cMsg);
	//����
	void OnCurtainStateNty(const CMessage& cMsg);
	void OnCurtainActInd(const CMessage& cMsg);
	//�����
	void OnCamStateNty(const CMessage& cMsg);
    //�пش���
    void OnCentreSleepNty(const CMessage& cMsg);
	//�пص���ǽ
	void OnDisplayInd(const CMessage& cMsg);
private:
	CCnsSession				*m_pSession;
    TCentreTVCfg            m_atTVCfg[MAX_CENTRETV_NUM];   //��ʾ����Ϣ 
	#define MAX_AC_NUM      3                         //����
	vector<TCentreACCfg>	m_vecTCentreACCfg;		//�յ���ʾ����Ϣ
	vector<TCentreCurName>  m_vecTCentreCurName;    //������������
	BOOL m_atbIsCtrl[3];
	BOOL m_bIsCtrl[3];
	BOOL m_bDisplay;
	TTPDisplayType m_tDisplayType1;
	TTPDisplayType m_tDisplayType3;
};