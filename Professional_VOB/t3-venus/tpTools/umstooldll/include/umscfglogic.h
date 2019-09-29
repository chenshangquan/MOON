/*****************************************************************************
ģ����      : CUmsCfgLogic
�ļ���      : umscfglogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: ums����ҳ��
����        : ʯ��
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/12/24     1.0         ʯ��			����
******************************************************************************/
#if !defined(AFX_UMSCFGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
#define AFX_UMSCFGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CUmsCfgLogic :public CWndLogicBase, public ISingleTon<CUmsCfgLogic>
{
public:
	CUmsCfgLogic();
	virtual ~CUmsCfgLogic();

public:  
	/**	 
	* ����:  ע���logic�����еĻص�����
	* @return  void
	* @remarks	�ڴ�ע��Ļص�������Ҫ�ǿؼ�����Ӧ�¼�����Ϊ��Ա�ص�����,Ҳ��ע�������Ļص�����
	                    ע��ʱ��Ӧע��ص�������Ӧ���ӵ��������򣺡�����::��������
	*/
	virtual bool RegCBFun();

	/**	 
	* ����:  ע��Ҫ�������Ϣ
	* @return  void
	* @remarks	 ע������Ϣ���ܷ��͵����߼�ģ�飬���򣬽��ղ�������Ϣ
	*/
	virtual void RegMsg(); 

	/**	 
	* ����:  ע��ĳ�ص�����
	* @return  void
	* @remarks	 
	*/
	virtual bool UnRegFunc( );

	/**	 
	* ����:  ע��ĳ�ص�����
	* @return  void
	* @remarks	 
	*/
	virtual void UnRegMsg();

	/**	 
	* ����:  ��ʼ����������,
	* @return  void
	* @remarks	���ڸù��ܱ��������ؼ����Բ���xml����ؼ��󶨣�
	                    ��Ҫ��RegCBFun������ע�ᵽ�ص���������ģ�� 
	*/
    virtual bool InitWnd( const IArgs & arg );

	/**	 
	* ����:  ��ʾ�����ش���
	* @return  bool ��ʾ�Ƿ����ʾ
	* @remarks
	*/
	virtual bool ShowWindow( BOOL32 bShow );

	/**	 
	* ����:  ��⵱ǰ�����������ı�ؼ�״̬
	* @return
	* @remarks
	*/
	void CheckCtrlState();

   /**	 
	* ����:  ����ʱ�������״̬������
	* @return   
	* @remarks	 
	*/
    virtual void Clear();

protected:
	/**	 
	* ����:  ����GK����Btn�ؼ�����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnSwitchGKClick( const IArgs& args );

	/**	 
	* ����:  ������������Btn�ؼ�����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnSaveClick( const IArgs& args );

	/**	 
	* ����:  �����ָ�����Btn�ؼ�����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnReductionClick( const IArgs& args );

	/**	 
	* ����:  ������������Btn�ؼ�����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnExportClick( const IArgs& args );

	/**	 
	* ����:  �ı�UmsIP�ؼ����ַ�ʱ����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnChangedIPCtrlUmsIP( const IArgs& args );

	/**	 
	* ����:  �ı���������IP�ؼ����ַ�ʱ����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnChangedIPCtrlSubnetMask( const IArgs& args );

	/**	 
	* ����:  �ı�����IP�ؼ����ַ�ʱ����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnChangedIPCtrlGateway( const IArgs& args );

	/**	 
	* ����:  �ı�SipIP�ؼ����ַ�ʱ����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnChangedIPCtrlSipIP( const IArgs& args );

	/**	 
	* ����:  �ı�GKIP�ؼ����ַ�ʱ����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnChangedIPCtrlGKIP( const IArgs& args );

protected:
	/**	 
	* ����:  ��Ӧ������������UI_UMS_ETHNETINFO_NOTIFY�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	LRESULT OnEthnetInfoNty( WPARAM wParam, LPARAM lParam );
	
	/**	 
	* ����:  ��Ӧ������������UI_UMS_REG_INFO_NOTIFY�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	LRESULT OnSipInfoNty( WPARAM wParam, LPARAM lParam );

	/**	 
	* ����:  ��Ӧ������������UI_UMS_REG_INFO_NOTIFY�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	LRESULT OnSipInfoRsp( WPARAM wParam, LPARAM lParam );

	/**	 
	* ����:  ��Ӧ������������UI_UMS_REG_SERV_RSP�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	LRESULT OnRegSipResult( WPARAM wParam, LPARAM lParam );
	
	/**	 
	* ����:  ��Ӧ������������UI_CNS_REG_GK_NTY�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	LRESULT OnGKInfoNty( WPARAM wParam, LPARAM lParam );

	/**	 

	* ����:  ��Ӧ������������UI_CNS_REG_GK_NTY�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	LRESULT OnGKInfoRsp( WPARAM wParam, LPARAM lParam );

	/**	 
	* ����:  ��Ӧ������������UI_CNS_REG_GK_RSP�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	LRESULT OnRegGKResult( WPARAM wParam, LPARAM lParam );
	
	/**	 
	* ����:  ��Ӧ������������UI_UMS_CMD_TIMEOUT�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	LRESULT OnTimeOut( WPARAM wParam, LPARAM lParam );

	/**	 
	* ����:  ��Ӧ������������UI_UMSTOOL_MSG_CONFCOUNT_NTY�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	LRESULT OnConfCount( WPARAM wParam, LPARAM lParam );

private:
	/**	 
	* ����:  ����������Ϣ
	* @return   
	* @remarks	 
	*/
	void SetEthnetInfo();

	/**	 
	* ����:  ����Sip��Ϣ
	* @return   
	* @remarks	 
	*/
	void SetSipInfo();

	/**	 
	* ����:  ����GK��Ϣ
	* @return   
	* @remarks	 
	*/
	void SetGKInfo();

	/**	 
	* ����:  �����������
	* @return   bool : ��ʾ�����Ƿ��д���
	* @remarks	 
	*/
	bool CheckAll();

	/**	 
	* ����:  ������������
	* @return   void
	* @remarks	 
	*/
	void SaveAll();

	/**	 
	* ����:  ���Ethnet����
	* @return   bool : ��ʾ�����Ƿ��д���
	* @remarks	 
	*/
	bool CheckEthnet();

	/**	 
	* ����:  ���Sip����
	* @return   bool : ��ʾ�����Ƿ��д���
	* @remarks	 
	*/
	bool CheckSip();

	/**	 
	* ����:  ���GK����
	* @return   bool : ��ʾ�����Ƿ��д���
	* @remarks	 
	*/
	bool CheckGK();

	/**	 
	* ����:  ����Ethnet
	* @return  
	* @remarks	 
	*/
	void SaveEthnet( TTPEthnetInfo &tTPEthnetInfo );

	/**	 
	* ����:  ����Sip
	* @return  
	* @remarks	 
	*/
	void SaveSip( TTPSipRegistrarCfg &tTPSipRegistrarCfg );

	/**	 
	* ����:  ����GK
	* @return  
	* @remarks	 
	*/
	void SaveGK( TTPGKCfg &tTPGKCfg );

	/**	 
	* ����:  ��������Btn״̬
	* @return  
	* @remarks	 
	*/
	void UpdBtnState();

	/**	 
	* ����: �����������ڳ�Ա����
	* @return  
	* @remarks	 
	*/
	void ResetAllData();

	/**	 
	* ����: �ָ�Ums����
	* @return  
	* @remarks	 
	*/
	void RecductUmsCfg();

private:
	//���߼���Ԫ��Ӧ�����пؼ���
	const String m_strEdtUmsIp;
	const String m_strEdtSubnetMask;
	const String m_strEdtGateWay;
	const String m_strEdtSipIP;
	const String m_strBtnGKSwitch;
	const String m_strEdtGKIP;
	const String m_strBtnSave;
	const String m_strBtnReduction;
	const String m_strBtnExport;

	//���߼���Ԫ��Ӧ�����������Ƿ�䶯
	BOOL m_bIsUmsIPChanged;
	BOOL m_bIsSubnetMaskChanged;
	BOOL m_bIsGateWayChanged;
	BOOL m_bIsSipIPChanged;
	BOOL m_bIsGKIPSwitchChanged;
	BOOL m_bIsGKIPChanged;
};

#define UMSCFGLOGICRPTR    CUmsCfgLogic::GetSingletonPtr()               //UmsCfglogicָ��

#endif // !defined(AFX_UMSCFGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
