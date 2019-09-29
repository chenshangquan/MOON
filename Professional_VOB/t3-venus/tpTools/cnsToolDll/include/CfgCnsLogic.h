// CfgCnsLogic.h: interface for the CCfgCnsLogic class.
/*****************************************************************************
�ļ���      : CfgCnsLogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: ��������е�cns���ý���
����        : ������
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/01/04     1.0         ������      ����
******************************************************************************/
#if !defined(AFX_CFGCNSLOGIC_H__5E754113_422F_4B4C_A8B0_D9907522897E__INCLUDED_)
#define AFX_CFGCNSLOGIC_H__5E754113_422F_4B4C_A8B0_D9907522897E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CCfgCnsLogic : public CLogicBase, public ISingleTon<CCfgCnsLogic>
{
public:
	CCfgCnsLogic();
	virtual ~CCfgCnsLogic();
	
	//CLogicBase
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
	/** ����:  �ж�cns����ҳ�����Ϣ�Ƿ�ı�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	bool IsCfgCnsChange();
	
	/**	 
	* ����: �����ϴ�����
	* @return   bool
	* @remarks  
	*/
	bool OnUploadProgress( const IArgs & arg );

	/**	 
	* ����: �ϴ�����
	* @param    const String strRemotePath      [in]     linux�˴��洢·��
	* @param    const String strLocalFile       [in]     ��������ļ�ȫ·�� 
	* @param    const String strCheckFileName   [in]     ��������ļ��� 
	* @return   bool
	* @remarks  
	*/
	BOOL UploadCore( const String& strRemotePath, const String& strLocalFile, const String& strCheckFileName ); 

	/**	 
	* ����: ��ȡcns���������ݱ仯�ؼ�����Ŀ
	* @return   bool
	* @remarks  
	*/
	s32 GetCtrlChangeNum() { return m_vctWndName.size(); }
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
	/** ����:  �������õİ�ť
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnBtnSave( const IArgs& args );
	/** ����:  ��ԭ���õİ�ť
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnCancel( const IArgs& args );
	/** ����:  �����İ�ť
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	bool OnBtnUpgrade( const IArgs& args );
	/** ����:  �������õİ�ť
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	bool OnBtnExport( const IArgs& args );
	/** ����:  ����NAT���õİ�ť
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	bool OnBtnSwitchNAT( const IArgs& args );

	/** ����:  ���շ������˷���������ϢȻ�����NAT״̬
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnUpdateNATNty( WPARAM wParam, LPARAM lParam );

	/** ����:  ���շ������˷���������ϢȻ�������������״̬
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnUpdateEthnetNty( WPARAM wParam, LPARAM lParam );

	/** ����:  ���շ������˷���������ϢȻ����»᳡���Ƽ�E164��
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnUpdateCnsInfoNty( WPARAM wParam, LPARAM lParam );

	/** ����:  ���շ������˷�����������T300�Ľ��
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnUpgradeCnsNty( WPARAM wParam, LPARAM lParam );

	/** ����:  ����᳡���ƺ�E164�Ų���
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveNameAndE164();

	/** ����:  ������������
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveNet();

	/** ����:  ���澲̬NAT����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveNAT();

	/** ����:  ������������	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveEthnetCfg();

	/** ����:  �л�����������ʱ�����Ƿ񱣴�Ĵ���	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveMsgBox();

	/** ����:  ��������ʱ�۽��ڳ���Ĵ���	
	*  @param[in] strWindow   ��������
	*  @return 
	*  @remarks   
	*/	
	void FocusWindow(String strWindow);	
	
	/** ����:  �ı�᳡���ƿؼ�ʱ����Ӧ����	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnChangedName( const IArgs& args );	
	
	/** ����:  �ı�᳡E164�ſؼ�ʱ����Ӧ����	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnChangedE164( const IArgs& args );	
	
	/** ����:  �ı�cns��ַ�ؼ�ʱ����Ӧ����	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnChangedCnsIp( const IArgs& args );	
	
	/** ����:  �ı�Ĭ�����ؿؼ�ʱ����Ӧ����	
	*  @param[in]
	*  @return 
	*  @remarks   
	*/	
	bool OnChangedGatewayIp( const IArgs& args );	
	
	/** ����:  �ı���������ؼ�ʱ����Ӧ����	
	*  @param[in]
	*  @return 
	*  @remarks   
	*/	
	bool OnChangedSubMaskIp( const IArgs& args );	
	
	/** ����:  �ı�NAT��ַ�ؼ�ʱ����Ӧ����	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnChangedNATIp( const IArgs& args );	
							
	/** ����:  ����NAT��ַ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	void SetNATData();
														
	/** ����:  ���û᳡���Ƽ��᳡E164��
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	void SetCnsInfoData();
														
	/** ����:  ����cns�������õ�����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	void SetEthnetCfgData();

	/** ����:  �յ�����״̬����Ϣ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	LRESULT OnConfStateNty( WPARAM wparam, LPARAM lparam);

	/** ����:  �յ��汾֪ͨ��Ϣ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	LRESULT OnVerInfoNty( WPARAM wparam, LPARAM lparam);
																
private:
	EmFtpStatus m_emFileFtpStatus;
	CFtpCtrl m_cFtp;
	Window* m_pWnd;
	std::vector<String> m_vecConfFile;
	const String m_strEdtIp;				//CNS��ַ
    const String m_strEdtSubMask;			//��������
    const String m_strEdtGateWay;			//Ĭ������
	const String m_strNameEdit;				//�᳡����
	const String m_strBtnNATSwitch;			//NAT����
	const String m_strEdtNatIP;				//NAT��ַ
	const String m_strName164Edit;			//�᳡E164����
	BOOL m_bNameChange;
	BOOL m_bCnsIp;
	BOOL m_bSubMask;
	BOOL m_bGateWay;
};

#endif // !defined(AFX_CFGCNSLOGIC_H__5E754113_422F_4B4C_A8B0_D9907522897E__INCLUDED_)
