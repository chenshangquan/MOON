// NetManageCfgLogic.h: interface for the CNetManageCfgLogic class.
//
//////////////////////////////////////////////////////////////////////

/*****************************************************************************
ģ����      : CNetManageCfgLogic
�ļ���      : NetManageCfgLogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: ��������ҳ��
����        : ���`�`
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/1/10      1.0         ���`�`		����
******************************************************************************/

#if !defined(AFX_NETMANAGECFGLOGIC_H__C0A57808_4F6C_4277_91BF_CFECDE2575A7__INCLUDED_)
#define AFX_NETMANAGECFGLOGIC_H__C0A57808_4F6C_4277_91BF_CFECDE2575A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

#define MIN_NMSERVER_NO		0
#define MAX_NMSERVER_NO		1

class CNetManageCfgLogic : public CWndLogicBase  
{
public:
	virtual ~CNetManageCfgLogic();
	static CNetManageCfgLogic* GetLogicPtr();

	public:
	/**	 
	* ����:  ע���logic�����еĻص�����
	* @return  void
	* @remarks	�ڴ�ע��Ļص�������Ҫ�ǿؼ�����Ӧ�¼�����Ϊ��Ա�ص�����,Ҳ��ע�������Ļص�����
	                    ע��ʱ��Ӧע��ص�������Ӧ���ӵ���������"����::������"
	*/
	virtual bool RegCBFun();

	/**	 
	* ����:  ע��ĳ�ص�����
	* @return  void
	* @remarks	 
	*/
	virtual bool UnRegFunc();

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
	virtual void UnRegMsg();
	
    /**	 
	* ����:  �������״̬������
	* @return    
	*/
    virtual void Clear();

	/**	 
	* ����:  ��ʼ����������,
	* @return  void
	* @remarks	���ڸù��ܱ��������ؼ����Բ���xml����ؼ��󶨣�
	                    ��Ҫ��RegCBFun()��ע�ᵽ�ص���������ģ�� 
	*/
	bool InitWnd( const IArgs & args );

protected:

	CNetManageCfgLogic();
	/**	 
	* ����:  ���ϵͳ���õ���Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnSysCfg( const IArgs & args );
    
	bool OnBtnNetManageCfg( const IArgs & args );
    /**	 
	* ����:  ����½����ܵ���Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnAddNetManage( const IArgs & args );

    /**	 
	* ����:  ���ɾ����ť����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnDelete( const IArgs & args );

    /**	 
	* ����:  ����б���Ŀ��Ӧ����
	* @return   bool
	* @remarks	 
	*/
    bool OnClickWebManageItem( const IArgs & args );

    bool OnBtnEdit( const IArgs & args );

    bool OnBtnSave( const IArgs & args );

    bool OnBtnCancel( const IArgs & args );

	HRESULT OnAddNetMngRsp( WPARAM wparam, LPARAM lparam );

	/**	 
	* ����:  ��Ӧ������������UI_CNS_NETMNG_NTY�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnNetMngNty( WPARAM wparam, LPARAM lparam );

	/**	 
	* ����:  ��Ӧ������������UI_CNS_MODIFY_NETMNG_RSP�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnModifyNetMngRsp( WPARAM wparam, LPARAM lparam );

	/**	 
	* ����:  ��Ӧ������������UI_CNS_DEL_NETMNG_RSP�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnDelNetMngRsp( WPARAM wparam, LPARAM lparam );

 
private:	
    static CNetManageCfgLogic *m_pLogic;

    //�߼���Ԫ��Ӧ�����пؼ���
	static const String m_strListNetMng;
	static const String m_strNMServerIp;
	static const String m_strNMReadCommunity;
	static const String m_strNMWriteCommunity;
	static const String m_strNMGetSetPort;
	static const String m_strNMTrapPort;
	static const String m_strBtnAdd;
	static const String m_strBtnDel;
	static const String m_strBtnModify;
	static const String m_strSchmEdit;

	//���ܲ�������
	EM_NETMNGOPT_TYPE m_emNMType;

	//��ǰѡ�е����ܷ�������Ϣ
	TTPNMServerCfg m_tTPNMServerCfgSel;

    //��ǰ������ʾ�����ܷ�������Ϣ
	TTPNMServerCfg m_tTPNMServerCfgCur;

	//�������ܵ����к�
	u16 m_wCurretNO;

private:
	/**	 
	* ����:  ����Btn״̬
	* @return   void
	* @remarks	 
	*/
	void UpdateBtnState();

	/**	 
	* ����:  ����������Ϣ
	* @return   void
	* @remarks	 
	*/
	void SetAllCtrl( TTPNMServerCfg &tTPNMServerCfg );

	/**	 
	* ����:	 ����������������ҳ��Ĭ��ֵ
	* @return   void
	* @remarks	 
	*/
	void SetAllInitCtrl();

	/**	 
	* ����:  �����пؼ���ֵ��ȡ��tTPNMServerCfg
	* @return   bool : ��ʾ��ȡֵ�Ƿ��д���
	* @remarks	 
	*/
	bool GetAllCtrl( TTPNMServerCfg &tTPNMServerCfg );

    /**	 
	* ����:  ����ǰ���пؼ���UI��ʾֵ��ȡ��tTPNMServerCfg
	* @return  
	* @remarks	 
	*/
	void GetCurrentCtrl();

	/**	 
	* ����:  ��ӦUI_CNS_MSG_NETMNGSELDATA_Click�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnNetMngSelData( WPARAM wparam, LPARAM lparam );

};

#endif // !defined(AFX_NETMANAGECFGLOGIC_H__C0A57808_4F6C_4277_91BF_CFECDE2575A7__INCLUDED_)
