// cfgServerLogic.h: interface for the CCfgServerLogic class.
//
//////////////////////////////////////////////////////////////////////
/*****************************************************************************
�ļ���      : CfgServerLogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: ��������еľ��������ý���
����        : ������
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/02/20     1.0         ������      ����
******************************************************************************/
#if !defined(AFX_CFGSERVERLOGIC_H__B06B345C_CF30_42B5_9B64_5F72C61D6269__INCLUDED_)
#define AFX_CFGSERVERLOGIC_H__B06B345C_CF30_42B5_9B64_5F72C61D6269__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CCfgServerLogic : public CLogicBase, public ISingleTon<CCfgServerLogic> 
{
public:
	CCfgServerLogic();
	virtual ~CCfgServerLogic();
	
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
	bool IsCfgSerChange();

	/**	 
	* ����: ��ȡ���������ݱ仯�ؼ�����Ŀ
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

	/** ����:  ����GK���õİ�ť
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	bool OnBtnSwitchGK( const IArgs& args );

	/** ����:  ���շ������˷���������ϢȻ�����GK״̬
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnUpdateGkNty( WPARAM wParam, LPARAM lParam );

	/** ����:  ���շ������˷���������ϢȻ�����SIP��Ϣ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnUpdateSipNty( WPARAM wParam, LPARAM lParam );

	/** ����:  ���շ������˷�������ע��SIP������Ϣ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnRegSIPAliasRepeatNty( WPARAM wParam, LPARAM lParam );

	/** ����:  ���շ������˷�������ע��SIP�Ľ��
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnRegSIPResultNty( WPARAM wParam, LPARAM lParam );

	/** ����:  ���շ������˷�������ע��GK�Ľ��
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnRegGKRsp( WPARAM wParam, LPARAM lParam );

	/** ����:  ���շ������˷������ĺ��з�������֪ͨ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnCallSerNty( WPARAM wParam, LPARAM lParam );

	/** ����:  ���շ������˷������ĺ��з������Ļظ�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnCallSerInd( WPARAM wParam, LPARAM lParam );

	/** ����:  ���շ������˷������ĺ��з�������֪ͨ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnUpgradeSerNty( WPARAM wParam, LPARAM lParam );

	/** ����:  ���շ������˷������ĺ��з������Ļظ�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnUpgradeSerInd( WPARAM wParam, LPARAM lParam );

	/** ����:  ����ע�����ʷ���������	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	bool SaveSip();

	/** ����:  ����GK����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveGk();

	/** ����:  ������з���������
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveCallSer();

	/** ����:  ����������������ַ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveUpgradeSer();

	/** ����:  ��������ʱ�۽��ڳ���Ĵ���	
	*  @param[in] strWindow   ��������
	*  @return 
	*  @remarks   
	*/	
	void FocusWindow(String strWindow);	

	/** ����:  �л�����������ʱ�����Ƿ񱣴�Ĵ���	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveMsgBox();
	
	/** ����:  �ı�ע��������ؼ�ʱ����Ӧ����	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnChangedSIp( const IArgs& args );	
	
	/** ����:  �ı�GK�������ؼ�ʱ����Ӧ����	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnChangedGKIp( const IArgs& args );	
			
	/** ����:  �ı���з������ؼ�ʱ����Ӧ����	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnChangedCallSerIp( const IArgs& args );	
					
	/** ����:  �ı������������ؼ�ʱ����Ӧ����	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnChangedUpSerIp( const IArgs& args );	

	/** ����:  ����GK��ַ
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/	
	void SetGKData();
														
	/** ����:  ����Sip��ַ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	void SetSipData();
															
	/** ����:  ���ú��з�������ַ�ͻ��顢��ʾ��ʽ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	void SetCallSerData();
																
	/** ����:  ����������������ַ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	void SetUpgradeSerData();

	/** ����:  �յ�����״̬����Ϣ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	LRESULT OnConfStateNty( WPARAM wparam, LPARAM lparam);

	/** ����:  ת��edit�����ip��ַΪdw��ʽ	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	DWORD StrToDWIp( String strName );
											
private:

	const String m_strEdtSIp;					//���ʷ�������ַ
	const String m_strBtnGKSwitch;				//GK����
	const String m_strEdtGKIP;					//GK��ַ
	const String m_strEdtCSIP;					//���з�������ַ
	const String m_strEdtUGIP;					//������������ַ

};

#endif // !defined(AFX_CFGSERVERLOGIC_H__B06B345C_CF30_42B5_9B64_5F72C61D6269__INCLUDED_)
