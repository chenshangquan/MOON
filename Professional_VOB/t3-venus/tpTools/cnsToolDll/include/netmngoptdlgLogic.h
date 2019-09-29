/*****************************************************************************
ģ����      : CNetMngOptDlgLogic
�ļ���      : netmngoptdlglogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: logic��������޸�ҳ��
����        : ʯ��
�汾        : V1.0  Copyright(C) 2013-2014 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/1/17      1.0         ʯ��        ����
******************************************************************************/
#if !defined(AFX_NETMNGOPTDLGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
#define AFX_NETMNGOPTDLGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LogicBase.h"

enum EM_NETMNGOPT_TYPE      //���ܲ�������
{
	em_NETMNGOPT_ADD,
	em_NETMNGOPT_MODIFY,
};

#define CNSTOOL_MAX_COMMUNITY_LENGTH	31

class CNetMngOptDlgLogic :public CLogicBase, public ISingleTon<CNetMngOptDlgLogic>
{
public:
    CNetMngOptDlgLogic();
	virtual ~CNetMngOptDlgLogic();

public:  
	/**	 
	* ����:  ע���logic�����еĻص�����
	* @return  void
	* @remarks	�ڴ�ע��Ļص�������Ҫ�ǿؼ�����Ӧ�¼�����Ϊ��Ա�ص�����,Ҳ��ע�������Ļص�����
	                    ע��ʱ��Ӧע��ص�������Ӧ���ӵ��������򣺡�����::��������
	*/
	virtual void RegCBFun();

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
	virtual void UnRegFunc( );

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
	* ����:  ����ʱ�������״̬������
	* @return   
	* @remarks	 
	*/
    virtual void Clear();

protected:
	/**	 
	* ����:  ��ӦUI_UMSTOOL_MSG_NETMNGSELDATA_Click�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnNetMngSelData( WPARAM wparam, LPARAM lparam );	
	
	

protected:
	/**	 
	* ����:  ����BtnOK�ؼ�����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnOptNetMngOk( const IArgs & arg );
	
	/**	 
	* ����:  ����BtnCancel�ؼ�����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnOptNetMngCancel( const IArgs & arg );
	
private:
	/**	 
	* ����:  ������пؼ�
	* @return   void
	* @remarks	 
	*/
	void ClearAllCtrl();

	/**	 
	* ����:  ��tTPNMServerCfg��ֵ���õ����пؼ�
	* @return   void
	* @remarks	 
	*/
	void SetAllCtrl( TTPNMServerCfg &tTPNMServerCfg );

	/**	 
	* ����:  �����пؼ���ֵ��ȡ��tTPNMServerCfg
	* @return   bool : ��ʾ��ȡֵ�Ƿ��д���
	* @remarks	 
	*/
	bool GetAllCtrl( TTPNMServerCfg &tTPNMServerCfg );

	/*=============================================================================
    �� �� ��:GetIpStr
    ��    ��:����ͨ����ת��ΪIP��
    ��    ��:unsigned int dwIPAddr    [in]     IP�����ͱ�ʾ��ʽ
    ע    ��:��
    �� �� ֵ:���ơ�127.0.0.1����ʽ
    =============================================================================*/
	CString GetIpStr(unsigned int dwIPAddr);

private:
	//���߼���Ԫ��Ӧ�����пؼ���
	const String  m_strIPCtrlNMServerIP;
	const String  m_strEdtNMReadCommunity;
	const String  m_strEdtNMWriteCommunity;
	const String  m_strEdtNMGetSetPort;
	const String  m_strEdtNMTrapPort;
	const String  m_strEdtNMServerNO;


	//���ܲ�������
	EM_NETMNGOPT_TYPE m_emNMType;

	//��ǰѡ�е����ܷ�������Ϣ
	TTPNMServerCfg m_tTPNMServerCfgSel;
};

#define NETMNGOPTLOGICRPTR    CNetMngOptDlgLogic::GetSingletonPtr()               //NetMngOptlogicָ��

#endif // !defined(AFX_NETMNGOPTDLGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
