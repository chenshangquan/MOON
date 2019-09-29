/*****************************************************************************
ģ����      : CVTROptDlgLogic
�ļ���      : vtroptdlglogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: logic¼�������޸�ҳ��
����        : ʯ��
�汾        : V1.0  Copyright(C) 2013-2014 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/3/4       1.0         ʯ��        ����
******************************************************************************/
#if !defined(UMSTOOL_VTROPTDLGLOGIC_H)
#define UMSTOOL_VTROPTDLGLOGIC_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

#define UMSTOOL_MAX_VTR_NAME_LENTH	32

class CVTROptDlgLogic :public CWndLogicBase, public ISingleTon<CVTROptDlgLogic>
{
public:
    CVTROptDlgLogic();
	virtual ~CVTROptDlgLogic();

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
	HRESULT OnSelData( WPARAM wparam, LPARAM lparam );	
	
	

protected:
	/**	 
	* ����:  ����BtnOK�ؼ�����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnOk( const IArgs & arg );
	
	/**	 
	* ����:  ����BtnCancel�ؼ�����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnCancel( const IArgs & arg );
	
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
	void SetAllCtrl( TVcrCfg &tVTRCfg );

	/**	 
	* ����:  �����пؼ���ֵ��ȡ��tTPNMServerCfg
	* @return   bool : ��ʾ��ȡֵ�Ƿ��д���
	* @remarks	 
	*/
	bool GetAllCtrl( TVcrCfg &tVTRCfg );

private:
	//���߼���Ԫ��Ӧ�����пؼ���
	const String  m_strEdtVTRName;
	const String  m_strEdtVTRNo;
	const String  m_strIPCtrlVTRIP;


	//��������
	EM_NETMNGOPT_TYPE m_emNMType;

	//�޸�ǰ��¼�����Ϣ
	TVcrCfg m_tVTRCfgOld;
};

#define VTROPTLOGICRPTR    CVTROptDlgLogic::GetSingletonPtr()               //NetMngOptlogicָ��

#endif // !defined(UMSTOOL_VTROPTDLGLOGIC_H)
