// MoonAdjustDlg.h: interface for the CMoonAdjustDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOONADJUSTDLG_H__7481DAC9_C5BC_4E5F_83A4_F91E5016E6B1__INCLUDED_)
#define AFX_MOONADJUSTDLG_H__7481DAC9_C5BC_4E5F_83A4_F91E5016E6B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CMoonAdjustDlg  : public CLogicBase, public ISingleTon<CMoonAdjustDlg>
{
public:
	CMoonAdjustDlg();
	virtual ~CMoonAdjustDlg();
public:	 	
	/** ����:  ע��ص�����
	*  @param[in] 
	*  @return 
	*  @remarks  �ڶ�ȡxml�ļ�ʱ��,���������ע��ĺ���
	*/
	virtual void RegCBFun();
	/** ����:  ��ע��ص�����
	*  @param[in] 
	*  @return 
	*  @remarks  �����溯���෴,ע��ע��ĺ���
	*/
	virtual void UnRegFunc( );

	/** ����:  ��ʼ������
	*  @param[in] 
	*  @return 
	*  @remarks  �ڶ�ȡxml�ļ�ʱ�����,������������ݳ�ʼ������
	*/	
    virtual bool InitWnd( const IArgs & arg ); 
 
	/** ����:  ������
	*  @param[in] 
	*  @return 
	*  @remarks  �ڴ��ڹرյ�ʱ�����,��մ�������
	*/
    virtual void Clear() ;

protected:	
	/** ����: ע����Ϣ,��������lib���з���������Ϣ
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/	
	virtual void RegMsg(); 
		
	/** ����: ��ע����Ϣ,�����溯���෴,ע��ע�����Ϣ
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/	
	virtual void UnRegMsg();


private:
	/** ����: ���òο���
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	bool OnRefLineSwitchBtnChange( const IArgs & arg );
	/** ����: �������ν���
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	bool OnTraCorSwitchBtnChange( const IArgs & arg );
	/** ����: ����ˮƽ��ת
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	bool OnHorFlipSwitchBtnChange( const IArgs & arg );
	/** ����: ����
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	bool OnSnapShotBtnClick( const IArgs & arg );
	/** ����: �������Ϊ
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	bool OnSnapShotSaveBtnClick( const IArgs & arg );
	/** ����: ����ˮƽ�������ٷ��Ȱ�ť��
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	bool OnBtnHorCorReduceHold( const IArgs & arg );
	/** ����: �ɿ�ˮƽ�������ٷ��Ȱ�ť
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	bool OnBtnHorCorReduceHoldEnd( const IArgs & arg );
	/** ����: ˮƽ�����༭��ֵ�����仯
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	bool OnHorCorEditChange( const IArgs & arg );
	
	/** ����: ˮƽ�����༭��ֵʧȥ����
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	bool OnHorCorEditKillFocus( const IArgs & arg );

	bool OnBtnHorCorIncreaseHoldEnd( const IArgs & arg );
	bool OnBtnHorCorIncreaseHold( const IArgs & arg );

	bool OnBtnHorStrReduceHold( const IArgs & arg );
	bool OnBtnHorStrReduceHoldEnd( const IArgs & arg );
	/** ����: ˮƽ����༭��ֵ�����仯
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	bool OnHorStrEditChange( const IArgs & arg );
	/** ����: ˮƽ����༭��ֵʧȥ����
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	bool OnHorStrEditKillFocus( const IArgs & arg );
	bool OnBtnHorStrIncreaseHold( const IArgs & arg );
	bool OnBtnHorStrIncreaseHoldEnd( const IArgs & arg );

	bool OnBtnVerCorReduceHold( const IArgs & arg );
	bool OnBtnVerCorReduceHoldEnd( const IArgs & arg );
	bool OnContrastAreaBtnClick( const IArgs & arg );
	bool OnCorrectParaBtnClick( const IArgs & arg );
	bool OnAutoCalculateBtnClick( const IArgs & arg );
	bool OnRgbConsisSwitchBtnChange( const IArgs & arg );  //��ɫһ���Կ���
	/************     ��ͼ����     ************/

	//��ͼR
	bool OnRLeftReduceBtnClick( const IArgs & arg );
	bool OnRLeftCorEditChange( const IArgs & arg );
	bool OnRLeftCorEditKillFocus( const IArgs & arg );
	bool OnRLeftIncreaseBtnClick( const IArgs & arg );

	//��ͼG
	bool OnGLeftReduceBtnClick( const IArgs & arg );
	bool OnGLeftCorEditChange( const IArgs & arg );
	bool OnGLeftCorEditKillFocus( const IArgs & arg );
	bool OnGLeftIncreaseBtnClick( const IArgs & arg );
	
	//��ͼB
	bool OnBLeftReduceBtnClick( const IArgs & arg );
	bool OnBLeftCorEditChange( const IArgs & arg );
	bool OnBLeftCorEditKillFocus( const IArgs & arg );
    bool OnBLeftIncreaseBtnClick(  const IArgs & arg );

	/************     ��ͼ����     ************/

	//��ͼR
	bool OnRMidReduceBtnClick( const IArgs & arg );
	bool OnRMidCorEditChange( const IArgs & arg );
	bool OnRMidCorEditKillFocus( const IArgs & arg );
	bool OnRMidIncreaseBtnClick( const IArgs & arg );

	//��ͼG
	bool OnGMidReduceBtnClick( const IArgs & arg );
	bool OnGMidCorEditChange( const IArgs & arg );
	bool OnGMidCorEditKillFocus( const IArgs & arg );
	bool OnGMidIncreaseBtnClick( const IArgs & arg );

	//��ͼB
	bool OnBMidReduceBtnClick( const IArgs & arg );
	bool OnBMidCorEditChange( const IArgs & arg );
	bool OnBMidCorEditKillFocus( const IArgs & arg );
	bool OnBMidIncreaseBtnClick( const IArgs & arg );

	/************     ��ͼ����     ************/

	//��ͼR
	bool OnRRightReduceBtnClick( const IArgs & arg );
	bool OnRRightCorEditChange( const IArgs & arg );
    bool OnRRightCorEditKillFocus( const IArgs & arg );
	bool OnRRightIncreaseBtnClick( const IArgs & arg );

	//��ͼG
	bool OnGRightReduceBtnClick( const IArgs & arg );
	bool OnGRightCorEditChange( const IArgs & arg );
	bool OnGRightCorEditKillFocus( const IArgs & arg );
	bool OnGRightIncreaseBtnClick( const IArgs & arg );

	//��ͼB
	bool OnBRightReduceBtnClick( const IArgs & arg );
	bool OnBRightCorEditChange( const IArgs & arg );
	bool OnBRightCorEditKillFocus( const IArgs & arg );
	bool OnBRightIncreaseBtnClick( const IArgs & arg );

	/** ����: ��ֱ�����༭��ֵ�����仯
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	bool OnVerStrEditChange( const IArgs & arg );
	/** ����: ��ֱ�����༭��ֵʧȥ����
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	bool OnVerCorEditKillFocus( const IArgs & arg );

	bool OnBtnVerCorIncreaseHold( const IArgs & arg );
	bool OnBtnVerCorIncreaseHoldEnd( const IArgs & arg );

	bool OnBtnVerStrReduceHold( const IArgs & arg );
	bool OnBtnVerStrReduceHoldEnd( const IArgs & arg );

	/** ����: ��ֱ����༭��ֵ�����仯
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	bool OnVerCorEditChange( const IArgs & arg );
	/** ����: ��ֱ����༭��ֵʧȥ����
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	bool OnVerStrEditKillFocus( const IArgs & arg );

	bool OnBtnVerStrIncreaseHold( const IArgs & arg );
	bool OnBtnVerStrIncreaseHoldEnd( const IArgs & arg );


	/************     ��ʱ����     ************/
	//��ͼ
    bool OnLeftDelayReduceBtnClick( const IArgs & arg );
	bool OnLeftDelayCorEditChange( const IArgs & arg );
	bool OnLeftDelayCorEditKillFocus( const IArgs & arg );
	bool OnLeftDelayIncreaseBtnClick( const IArgs & arg );

	//��ͼ
    bool OnMiddleDelayReduceBtnClick( const IArgs & arg );
	bool OnMiddleDelayCorEditChange( const IArgs & arg );
	bool OnMiddleDelayCorEditKillFocus( const IArgs & arg );
	bool OnMiddleDelayIncreaseBtnClick( const IArgs & arg );

	//��ͼ
	bool OnRightDelayReduceBtnClick( const IArgs & arg );
	bool OnRightDelayCorEditChange( const IArgs & arg );
	bool OnRightDelayCorEditKillFocus( const IArgs & arg );
	bool OnRightDelayIncreaseBtnClick( const IArgs & arg );

	LRESULT OnSnapShotNty( WPARAM wparam, LPARAM lparam );


	/** ����: ���½�����ʾ
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	HRESULT OnTralCorParamInd( WPARAM wparam, LPARAM lparam );
	/** ����: �ο�������֪ͨ
	*  @param[in] lparam �Ƿ�ɹ�
	*  @return 
	*  @remarks  
	*/
	HRESULT OnReferenceLineInd( WPARAM wparam, LPARAM lparam );

	/** ����: ˮƽ��ת����֪ͨ
	*  @param[in] lparam �Ƿ�ɹ�
	*  @return 
	*  @remarks  
	*/
	HRESULT OnHorizontalFlipInd( WPARAM wparam, LPARAM lparam );
	/** ����: ���ν�������֪ͨ
	*  @param[in] lparam �Ƿ�ɹ�
	*  @return 
	*  @remarks  
	*/
	HRESULT OnTrapezoidalCorInd( WPARAM wparam, LPARAM lparam );

	HRESULT OnCameraSelectInd( WPARAM wparam, LPARAM lparam );

	HRESULT OnSetCamDistortParamInd( WPARAM wparam, LPARAM lparam );

	HRESULT OnTraCorValueInd( WPARAM wparam, LPARAM lparam );

	HRESULT OnSecBoundaryNty( WPARAM wparam, LPARAM lparam );
	
	HRESULT OnSetChangeSideRGBNty( WPARAM wparam, LPARAM lparam );

	HRESULT OnSetDefaultParamNty( WPARAM wparam, LPARAM lparam );

	HRESULT OnSetColorRGBInd( WPARAM wparam, LPARAM lparam );

	HRESULT OnSetDirectColorRGBInd( WPARAM wparam, LPARAM lparam );

	HRESULT OnSetAutoColConstancyInd( WPARAM wparam, LPARAM lparam );
	
	HRESULT OnShowRectRegionInd( WPARAM wparam, LPARAM lparam );

	HRESULT OnSetOnColorSwitchInd( WPARAM wparam, LPARAM lparam );

	/** ����: ��ʱ��������֪ͨ
	*  @param[in] lparam �Ƿ�ɹ�
	*  @return 
	*  @remarks  
	*/
    HRESULT OnSetDelayCorrectInd( WPARAM wparam, LPARAM lparam );

	HRESULT OnSetDelayCorrectNty( WPARAM wparam, LPARAM lparam );
private:
	bool SetSnapShotImage( const string strFileName );
	/** ����: �������ν����Ĳ���
	*  @param[in] emTpMyOption ��������    dwValue ����ֵ
	*  @return 
	*  @remarks  
	*/
	void SetTraCorrectionParam( EmTPCorrect emTpMyOption , TTPDistortParam &tTraCorParam );
	/** ����: �ͷű�����ռ���Ҳ���ʹ�õ�ͼƬ��Դ
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	void ReleaseSnapImage();
		/** ����: ���±༭�����ֵ����ֹ�����߽缰����0��ʼ����ֵ
	*  @param[in] strEditName ��ӦXML�еĿؼ����� nMaxValue ��Ӧ������ʾ���ֵ
	*  @return 
	*  @remarks  
	*/
	void UpdateEditNum( const IArgs & arg, String strEditName ,s32 nMaxValue ,s32 nMinValue);
	
	/** ����:��ȡ��������
	*  @param[in] strFileName ��ʼ��������
	*  @return  ��ȡ�������ƣ������һ�鱻ʹ�ã����ڿ������������TEMPͷ
	*  @remarks  
	*/
	string GetSnapShotFileName( const string strFileName );
	/** ����: �����ļ�
	*  @param[in] strFilePath �������ļ�����·�� strFileName �����ļ���
	*  @return 
	*  @remarks  
	*/
	BOOL DownloadCore(const String& strFilePath,const String & strFileName );

	bool OnDownloadProgress( const IArgs & arg );

	void CopyImage( string strCopyPath, string strSavePath );

public:
	void CopyFile( string strCopyFilePath, string strSaveFilePath );

private:
	void UpdateColorRGBVal( TTPColorCoeff tTPColorCoeff);
	void SetRGBColorValCmd( CString str, u8 nPosition, EmTPColorConsistency emMyColorOption );

	float StringToFloatThree( CString str );
	CString OnlyFloat( CString str );


private:
	const string m_strRefLineSwitchBtn;							 //�ο��߿���
	const string m_strHorFlipSwitchBtn;							 //ˮƽ��ת����
	const string m_strTraCorSwitchBtn;							 //���ν�������
	const string m_strRgbConsisSwitchBtn;                        //��ɫһ���Կ���
	const String m_strSchemeEnable;                              //����ʹ�����ν�������ģʽ
	const String m_strSchemeDisable;                             //�������ν�������ģʽ
	const string m_strHorCorEdit;                                //����XML��ˮƽ�����༭����ַ���
	const string m_strHorStrEdit;                                //����XML��ˮƽ����༭����ַ���
	const string m_strVerCorEdit;                                //����XML�д�ֱ�����༭����ַ���
	const string m_strVerStrEdit;                                //����XML�д�ֱ����༭����ַ���
	//��ɫRGBһ����
	const string m_strRLeftCorEdit;
	const string m_strGLeftCorEdit;
	const string m_strBLeftCorEdit;
	const string m_strRMidCorEdit;
	const string m_strGMidCorEdit;
	const string m_strBMidCorEdit;
	const string m_strRRightCorEdit;
	const string m_strGRightCorEdit;
	const string m_strBRightCorEdit;
	//��ʱ����
    const string m_strLeftDelayCorEdit;
	const string m_strMiddleDelayCorEdit;
	const string m_strRightDelayCorEdit;

	std::map<string,s32> m_mapMaxValue;                          //����XML�б༭����ַ�������Ӧ�Ľ������ֵ
	std::map<string,s32> m_mapMinValue;
	CFtpCtrl m_cFtp;
	std::vector<string>  m_vecFilePath;                          //���������ļ�Ŀ¼
	std::vector<string>  m_vecDownFile;                          //����δ�����ļ���
	std::vector<string>  m_vecShatShot;                          //��Ӧ������տؼ�
	BOOL m_bIsFirstGroupUsed;                                    //�Ƿ�ʹ�õ�һ�����ͼƬ
	BOOL m_bRefLineOpen;										//�Ƿ����ο���
	BOOL m_bHorFlipOpen;										//�Ƿ���ˮƽ��ת
	BOOL m_bTraCorOpen;											//�Ƿ������ν���
	BOOL m_bIsSaveAsSnapShot;								    //�Ƿ�������
	TTPDistortParam     m_tHorParam;                            // ����ˮƽ����
	TTPDistortParam     m_tVerParam;                            // ���洹ֱ����
	EmFtpStatus m_emFileFtpStatus;
	BOOL       m_bIsOption;                                     //�Ƿ���й����ղ���
};

#endif // !defined(AFX_MOONADJUSTDLG_H__7481DAC9_C5BC_4E5F_83A4_F91E5016E6B1__INCLUDED_)
