#include "cnsSession.h"
#include "eventoutcnsmp.h"
#include "eventoutcnscamera.h"

class CCncSysCtrl : public CCncSysCtrlIF
{
public:
	CCncSysCtrl( CCnsSession &cSession );
	~CCncSysCtrl();
	/** 
	* ����  	�����������cpu/�ڴ����Ϣ
	* @param [in] 	   
	* @return  
	* @remarks 
	*/	
	virtual u16 ReqSysInfo();
	/** 
	* ����  	���շ�����������cpu/�ڴ����Ϣ
	* @param [in] 	   
	* @return  
	* @remarks 
	*/	
	virtual const TTPSysInfo& GetSysInfo()const;
	/** 
	* ����  	��ȡ������Ϣ
	* @param [in] 	   
	* @return  
	* @remarks 
	*/	
 	virtual const TTPCnsConfStatus& GetCnConfStatus()const;
	/** 
	* ����  	��ȡ������Ϣ
	* @param [in] 	   
	* @return  
	* @remarks 
	*/	
	virtual	const TTPCnConfInfo& GetCnConfVideoParam()const;	
	/** 
	* ����  	ѡ�������
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/		
	virtual u16 CamSelCmd( const u8& byCameraIndx );	
	/** 
	* ����  	��ȡ��ѡ�е������
	* @param [in] 	 
	* @return  
	* @remarks 
	*/		
	virtual u8 GetCamSel()const;
	/** 
	* ����  	�ָ������Ĭ�ϲ���
	* @param [in] 	   
	* @return  
	* @remarks 
	*/	
	virtual	u16 CamResetCmd();			
	/** 
	* ����  	��Ұ����
	* @param [in] 	 EmZoom  ��Ϊ:Զ����
	* @return  
	* @remarks 
	*/	
	virtual u16 SetCamZoomCmd( const EmZoom& emZoom );		
	/** 
	* ����  	��Ұ�Ƿ���OSD����ʾ����
	* @param [in] 	 EmOSDShow  ��Ϊ:on��off
	* @return  
	* @remarks 
	*/	
	virtual	u16 SetCamOSDCmd( const EmOSDShow& emOSDShow );	
	/** 
	* ����  	��ȡ��Ұ�Ƿ���OSD����ʾ����
	* @param [in] 	 
	* @return  EmOSDShow  ��Ϊ:on��off
	* @remarks 
	*/	
	virtual EmOSDShow GetCamOSD();
	/** 
	* ����  	������Զ��۽�
	* @param [in] 	 
	* @return  
	* @remarks 
	*/		
	virtual u16 SetCamAutoFocusCmd(const EmFocusMode& emFocusMode);
	/** 
	* ����  	������ֶ��۽�
	* @param [in] 	 EmFocus : Զ��/����	EmCnAction :  ��ʼ/ֹͣ
	* @return  
	* @remarks 
	*/	
	virtual	u16 SetCamFocusCmd( const EmFocus& emFocus, const EmCnAction& emCnAction );		
	/** 
	* ����  	����Ԥ��λ����
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual	u16 CamPresetSaveCmd();
	/** 
	* ����  	���ÿ�������Ԥ��λ1
	* @param [in] 	 BOOL
	* @return  
	* @remarks 
	*/	
	virtual	u16 SetCamPresetMoveCmd( const BOOL& bPresetMove );
	/** 
	* ����  	��ȡ��������Ԥ��λ1״̬
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual BOOL GetCamPresetMove();
	/** 
	* ����  	�����Զ��ع�
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u16 CamAutoExposureCmd( const EmExpMode& emExpAuto );
	/** 
	* ����  	����
	* @param [in] 	 EmGain ���淶Χ 0dB  3dB  6dB ������42dB
	* @return  
	* @remarks 
	*/	
	virtual	u16 CamGainCmd( const EmGain& emGain );	
	/** 
	* ����  	��ȡ���������ֵ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual EmGain GetCamGain();
	/** 
	* ����  ���ŵ���	���ŷ�Χ 1/60  1/100 1/250.....1/4000  1/10000
	* @param [in]  EmShutSpd
	* @return  
	* @remarks 
	*/
	virtual	u16 CamShutSpdCmd( const EmShutSpd& emShutSpd );
	/** 
	* ����  	��ȡ���������ֵ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual EmShutSpd GetCamShutSpd();
	/** 
	* ����  ����ģʽ����
	* @param [in]  EmBackLightType  ����ģʽ:�رգ�multi��Ĭ��7����Χ0-15����center��face detect
	*			   u8  = TP_INVALID_INDEX ��multiģʽ  0--15 multiģʽ����
	* @return  
	* @remarks 
	*/
	virtual	u16 CamBackLightCmd( const EmBackLightType& emBackLightType, const u8& byMulti );
	/** 
	* ����  	��ȡ���������ģʽ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual EmBackLightType GetCamBackLightType();
	/** 
	* ����  	��ȡ���������ģʽ��Ӧ��ֵ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u8 GetCamBackLightIndex();
	/** 
	* ����  ��Ȧ��С����
	* @param [in]  u8  ��Ȧ��С ��Χ 0--100			   
	* @return  
	* @remarks 
	*/	
	virtual	u16 CamAperture( const u8& byAperture);	
	/** 
	* ����  	��ȡ�������Ȧ��С
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u8 GetCamAperture();
	/** 
	* ����  ��ƽ�����(��Ϊ�Զ����ֶ�)
	* @param [in] 		   
	* @return  
	* @remarks 
	*/		
	virtual	u16 CamAutoWBCmd( const EmWBMode& emWBMode );	
	/** 
	* ����  R+����
	* @param [in] 	u16  R Gain ��Χ 0--100	   
	* @return  
	* @remarks 
	*/		
	virtual	u16 CamRGainCmd( const u16& wRGain );
	/** 
	* ����  	��ȡ�������ƽ�����ģʽR+����ֵ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u16 GetCamRGain();
	/** 
	* ����  B+����
	* @param [in] 	u16  B Gain ��Χ 0--100	   
	* @return  
	* @remarks 
	*/		
	virtual	u16 CamBGainCmd( const u16& wBGain );
	/** 
	* ����  	��ȡ�������ƽ�����ģʽB+����ֵ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u16 GetCamBGain();
	/** 
	* ����  ģʽ����  
	* @param [in] 	EmPicSceMode  ��Ϊ:�չ��/̫����/�ֶ�
	* @return  
	* @remarks 
	*/	
	virtual	u16 CamPicSceneModeCmd( const EmPicSceMode& emPicSceMode );	
	/** 
	* ����  	��ȡ�����Picģʽ����״̬
	* @param [in] 	 
	* @return  EmPicSceMode  ��Ϊ:�չ��/̫����/�ֶ�
	* @remarks 
	*/	
	virtual EmPicSceMode GetCamPicSceneMode();
	/** 
	* ����  �ֶ�ģʽ�е�CAMMA����  
	* @param [in] 	EmGamma  ��Ϊ:emGammaOff��emGammaOn ��emSmart1�� emStrat2
	* @return  
	* @remarks 
	*/	
	virtual	u16 CamGammaCmd( const EmGamma& emGamma );
	/** 
	* ����  	��ȡ�����PicģʽCAMMA����״̬
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual EmGamma GetCamGamma();
	/** 
	* ����  �ֶ�ģʽ�еĹ�Ȧ����  
	* @param [in]   u8 ��Ȧ��С  1--15
	* @return  
	* @remarks 
	*/	
    virtual	u16 CamPicSceAptCmd( const u8& byPicSceApt );
	/** 
	* ����  	��ȡ�����Picģʽ��Ȧ����ֵ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u8 GetCamPicSceApt();
	/** 
	* ����  ͼƬ�����еĶԱȶȵ���
	* @param [in]   u16  ��С  0--200
	* @return  
	* @remarks 
	*/		
	virtual	u16 CamContrastCmd( const u16& wContrast );	
	/** 
	* ����  	��ȡ�����ͼƬ�����еĶԱȶ�ֵ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u16 GetCamContrast();
	/** 
	* ����  ͼƬ�����е�ɫ�ȵ���
	* @param [in]   u16  ��С  0--200
	* @return  
	* @remarks 
	*/		
	virtual	u16 CamHueCmd( const u16& wHue );
	/** 
	* ����  	��ȡ�����ͼƬ�����е�ɫ��ֵ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u16 GetCamHue();
	/** 
	* ����  ͼƬ�����еı��Ͷȵ���
	* @param [in]   u16  ��С  0--200
	* @return  
	* @remarks 
	*/	
	virtual	u16 CamSaturatCmd( const u16& wSaturat );
	/** 
	* ����  	��ȡ�����ͼƬ�����еı��Ͷ�ֵ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u16 GetCamSaturat();
	/** 
	* ����  ͼƬ�����е����ȵ���
	* @param [in]   u16  ��С  0--200
	* @return  
	* @remarks 
	*/	
	virtual	u16 CamBrightCmd( const u16& wBright );	
	/** 
	* ����  	��ȡ�����ͼƬ�����е�����ֵ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u16 GetCamBright();
	/** 
	* ����  ����---����������˵�������
	* @param [in]   EmStmClean  Ĭ��LOW  ��ΧOFF,LOW,MID,HIGH
	* @return  
	* @remarks 
	*/	
	virtual	u16 CamNRStmCleanCmd( const EmStmClean& emStmClean );
	/** 
	* ����  	��ȡ�����������ģʽ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual EmStmClean GetCamNRStmClean();
	/** 
	* ����  ����---3D�����������
	* @param [in]   Em3DNR   em3DNROff ��OFF��em3DNROn ��
	* @return  
	* @remarks 
	*/	
	virtual	u16 Cam3DNRCmd( const Em3DNR& em3DNR );	
	/** 
	* ����  	��ȡ�����3D�������ģʽ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual Em3DNR GetCam3DNR();

	/** 
	* ����  	��ȡȫ�����������
	* @param [in] 	 �������Ϣ
	* @return  
	* @remarks 
	*/	
	virtual u16 GetCamCfgAll( vector<TCnCameraCfg>& vecTCnCameraCfg );

	/** 
	* ����  	��ȡ��ǰ���������
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual TCnCameraCfg GetCamCfg();

	/** 
	* ����  	��ȡ�ع�ģʽ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual EmExpMode GetCamExpMode();

	/** 
	* ����  	��ȡ��ƽ��ģʽ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual EmWBMode GetCamWBMode();

	/** 
	* ����  	����������͵���֪ͨ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual	u16 SetLoadCameraFileNty();

	/** 
	* ����  	��ȡzoom
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u16 GetCamZoom();

	/** 
	* ����  	����zoomֵ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u16 SetCamZoomCmd( const u16& wZoom );


protected:
	virtual void OnTimeOut(u16 wEvent); 
    virtual void DispEvent(const CMessage &cMsg);
	void BuildEventsMap();
	void OnLinkBreak(const CMessage& cMsg);

	void OnSysInfoRsp(const CMessage& cMsg);
	void OnSysInfoNty(const CMessage& cMsg);
	void OnCnConfInfoNty(const CMessage& cMsg);
	void OnCameraCfgNty(const CMessage& cMsg);
	void OnCamSelInd(const CMessage& cMsg);
	void OnCamResetInd(const CMessage& cMsg);
	void OnCamZoomInd(const CMessage& cMsg);
	void OnCamOSDInd(const CMessage& cMsg);	
	void OnCamAutoFocusInd(const CMessage& cMsg);
	void OnCamFocusInd(const CMessage& cMsg);
	void OnCamPresetSaveInd(const CMessage& cMsg);
	void OnAutoExposureInd(const CMessage& cMsg);
	void OnCamGainInd(const CMessage& cMsg);
	void OnCamShutSpdCInd(const CMessage& cMsg);
	void OnCamBackLightInd(const CMessage& cMsg);
	void OnCamApertureInd(const CMessage& cMsg);
	void OnCamAutoWBInd(const CMessage& cMsg);
	void OnCamRGainInd(const CMessage& cMsg);
	void OnCamBGainInd(const CMessage& cMsg);
	void OnCamPicSceneModeInd(const CMessage& cMsg);
	void OnCamGammaInd(const CMessage& cMsg);
	void OnCamPicSceAptInd(const CMessage& cMsg);
	void OnCamContrastInd(const CMessage& cMsg);
	void OnCamHueInd(const CMessage& cMsg);
	void OnCamSaturatInd(const CMessage& cMsg);
	void OnCamBrightInd(const CMessage& cMsg);
	void OnCamNRStmCleanInd(const CMessage& cMsg);
	void OnCam3DNRInd(const CMessage& cMsg);
	void OnCamPresetMoveInd(const CMessage& cMsg);
	void OnSetCameraZoomInd(const CMessage& cMsg);
	void OnCameraPowerOnNty(const CMessage& cMsg);

public:
	void SetCameraCfgPtr();

private:
	CCnsSession		*m_pSession;
	TTPSysInfo	     m_tSysInfo;
	TTPCnsConfStatus m_tConfStatus;
	TTPCnConfInfo    m_tVideoParam;
	u8	m_byCameraSel;
	TCnCameraCfg m_tCnCameraCfg1;
	TCnCameraCfg m_tCnCameraCfg2;
	TCnCameraCfg m_tCnCameraCfg3;
	TCnCameraCfg *m_pTCnCameraCfg;
};
