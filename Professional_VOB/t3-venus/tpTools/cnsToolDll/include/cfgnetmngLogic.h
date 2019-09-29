/*****************************************************************************
ģ����      : CCfgNetMngLogic
�ļ���      : cfgnetmngLogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: ��������ҳ��
����        : ʯ��
�汾        : V1.0  Copyright(C) 2013-2014 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/1/17      1.0         ʯ��			����
******************************************************************************/
#if !defined(AFX_CFGNETMNGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
#define AFX_CFGNETMNGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

#define MIN_NMSERVER_NO		0
#define MAX_NMSERVER_NO		1

class CCfgNetMngLogic : public CLogicBase, public ISingleTon<CCfgNetMngLogic>
{
public:
	CCfgNetMngLogic();
	virtual ~CCfgNetMngLogic();


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
	* ����:  �������״̬������
	* @return   
	* @remarks	 
	*/
    virtual void Clear();

protected:
	/**	 
	* ����:  ����BtnAdd����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnClickBtnAdd( const IArgs& args );

	/**	 
	* ����:  ����BtnModify����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnClickBtnModify( const IArgs& args );

	/**	 
	* ����:  ����BtnDel����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnClickBtnDelete( const IArgs& args );


	/**	 
	* ����:  ����NetMngLstĳ��Item����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnClickNetMngLst( const IArgs & arg );

	/**	 
	* ����:  ����NetMngLst�հ��������Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnClickNetMngLstBlack( const IArgs& args );


protected:
	/**	 
	* ����:  ��Ӧ������������UI_UMSTOOL_ADD_NETMNG_RSP�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnAddNetMngRsp( WPARAM wparam, LPARAM lparam );

	/**	 
	* ����:  ��Ӧ������������UI_UMSTOOL_NETMNG_NTY�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnNetMngNty( WPARAM wparam, LPARAM lparam );

	/**	 
	* ����:  ��Ӧ������������UI_UMSTOOL_MODIFY_NETMNG_RSP�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnModifyNetMngRsp( WPARAM wparam, LPARAM lparam );

	/**	 
	* ����:  ��Ӧ������������UI_UMSTOOL_DEL_NETMNG_RSP�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnDelNetMngRsp( WPARAM wparam, LPARAM lparam );	


private:
	/**	 
	* ����:  �������пؼ�
	* @return   void
	* @remarks	 
	*/
	void ResetAllCtrl();

	/**	 
	* ����:  ������������
	* @return   void
	* @remarks	 
	*/
	void ResetAllData();

	/**	 
	* ����:  ����Btn״̬
	* @return   void
	* @remarks	 
	*/
	void UpdateBtnState();

private:
	//���߼���Ԫ��Ӧ�����пؼ���
	const String m_strListNetMng;
	const String m_strBtnAdd;
	const String m_strBtnModify;
	const String m_strBtnDel;


	//��ǰѡ�е����ܷ�������Ϣ
	TTPNMServerCfg m_tTPNMServerCfgSel;
};

#define CFGNETMNGLOGICRPTR    CCfgNetMngLogic::GetSingletonPtr()               //CfgNetMnglogicָ��

#endif // !defined(AFX_CFGNETMNGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
