// SysCfgDlgLogic.h: interface for the CSysCfgDlgLogic class.
//
//////////////////////////////////////////////////////////////////////
/*****************************************************************************
�ļ���      : CSysCfgDlgLogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: ϵͳ���ý���
����        : ���`�`
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2014/12/22     1.0         ���`�`      ����
******************************************************************************/
#if !defined(AFX_SYSCFGDLGLOGIC_H__B06B345C_CF30_42B5_9B64_5F72C61D6269__INCLUDED_)
#define AFX_SYSCFGDLGLOGIC_H__B06B345C_CF30_42B5_9B64_5F72C61D6269__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CSysCfgDlgLogic : public CLogicBase, public ISingleTon<CSysCfgDlgLogic> 
{
public:
	CSysCfgDlgLogic();
	virtual ~CSysCfgDlgLogic();
	
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

		
	bool IsCfgCnsChange();

	/**	 
	* ����: ��ȡmoon sys���������ݱ仯�ؼ�����Ŀ
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
	
	HRESULT OnSoftWareVerInfoNty( WPARAM wparam, LPARAM lparam );

	HRESULT OnCamOutputInfoNty( WPARAM wparam, LPARAM lparam );

	HRESULT OnCamImageAdjustNty( WPARAM wparam, LPARAM lparam );

	HRESULT OnEthnetInfoNty( WPARAM wparam, LPARAM lparam );

	HRESULT OnCamOutputInfoInd( WPARAM wparam, LPARAM lparam );
	
	HRESULT OnCamImageAdjustInd( WPARAM wparam, LPARAM lparam );

	HRESULT OnLvdsBaudRateInd( WPARAM wparam, LPARAM lparam );
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

	/** ����: ���HDMI����Դ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnHDMISelClick( const IArgs& args );

	/** ����: ���DVI����Դ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnDVISelClick( const IArgs& args );

	/** ����: �������Դѡ��combox
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnCombOutputStyleClick( const IArgs& args );

	/** ����: ���ͼ�񲻷�תradiobtn
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnNoTurnClick( const IArgs& args );

	/** ����: ���ͼ��תradiobtn
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnTurnClick( const IArgs& args );

	/** ����: IP��ַedit
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnIPAddrChanged( const IArgs& args );

	/** ����: ��������edit
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnSubMaskChanged( const IArgs& args );

	/** ����: Ĭ������edit
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnGatewayChanged( const IArgs& args );

	/** ����:  ��������ʱ�۽��ڳ���Ĵ���	
	*  @param[in] strWindow   ��������
	*  @return 
	*  @remarks   
	*/	
	void FocusWindow(String strWindow);	

	void SetOutPortType(EmTPDVIOutPortType emOutPortType);

	void SetMoonOutMode(EmTPMOONOutMode emMoonOutMode);

	void GetMoonOutMode( EmTPMOONOutMode &emMoonOutMode )const;

	void SetImageAdjust(EmTPImageAdjust emImageAdjust);

	void SetEthnetCfgData();

	/** ����:  ������������
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveNet();

	/** ����:  ������������	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveEthnetCfg();

	bool SaveMsgBox();

	bool OnCombBaudRateClick( const IArgs& args );
private:
	/** ����:  �������ʵ�ö��ֵת���ɶ�Ӧ�ַ���	
	*  @param[in] ������ö��ֵ
	*  @return  ��Ӧ�����ַ���
	*  @remarks   
	*/	
	string TransRaudRateTypeToStr( EmTPLVDSBaud emTpLvdBaudValue );
	/** ����:  �������ʵ��ַ���ת���ɶ�Ӧö��ֵ	
	*  @param[in] ������ʾ�������ַ���
	*  @return  ��Ӧ��ö��ֵ
	*  @remarks   
	*/
	EmTPLVDSBaud TransRaudRateStrToType( string strBaudRate );
	/** ����:  ����LVDS������
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool SaveBaudRate();
private:
	//���߼���Ԫ��Ӧ�����пؼ���
	const String m_strCombOutputStyle;
	const String m_strSoftWareInfo;
	const String m_strComboBaudRate;        //Lvds������

	const String m_strEdtIp;				//CNS��ַ
    const String m_strEdtSubMask;			//��������
    const String m_strEdtGateWay;			//Ĭ������

	const String m_strStyleGroup1;
	const String m_strStyleGroup2;
	const String m_strAdjustGroup1;
	const String m_strAdjustGroup2;

	EmTPDVIOutPortType m_emDVIOutPortType;
	EmTPMOONOutMode m_emMOONOutMode;
	EmTPImageAdjust m_emImageAdjust;
	EmTPLVDSBaud m_emBaudRate;

	BOOL m_bCnsIp;
	BOOL m_bSubMask;
	BOOL m_bGateWay;
};

#endif // !defined(AFX_CFGSERVERLOGIC_H__B06B345C_CF30_42B5_9B64_5F72C61D6269__INCLUDED_)
