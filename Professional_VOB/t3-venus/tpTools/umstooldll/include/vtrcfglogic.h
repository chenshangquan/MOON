/*****************************************************************************
ģ����      : CVTRCfgLogic
�ļ���      : vtrcfglogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: ��������ҳ��
����        : ʯ��
�汾        : V1.0  Copyright(C) 2013-2014 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/3/4       1.0         ʯ��			����
******************************************************************************/
#if !defined(UMSTOOL_VTRCFGLOGIC_H)
#define UMSTOOL_VTRCFGLOGIC_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CVTRCfgLogic :public CWndLogicBase, public ISingleTon<CVTRCfgLogic>
{
public:
	CVTRCfgLogic();
	virtual ~CVTRCfgLogic();


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
	* ����:  ����VTRLstĳ��Item����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnClickVTRLst( const IArgs & arg );

	/**	 
	* ����:  ����VTRLst�հ��������Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnClickVTRLstBlack( const IArgs& args );


protected:
	/**	 
	* ����:  ��Ӧ������������UI_UMSTOOL_ADD_VTR_RSP�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnAddVTRRsp( WPARAM wparam, LPARAM lparam );

	/**	 
	* ����:  ��Ӧ������������UI_UMSTOOL_VTR_NTY�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnVTRNty( WPARAM wparam, LPARAM lparam );

	/**	 
	* ����:  ��Ӧ������������UI_UMSTOOL_MODIFY_VTR_RSP�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnModifyVTRRsp( WPARAM wparam, LPARAM lparam );

	/**	 
	* ����:  ��Ӧ������������UI_UMSTOOL_DEL_VTR_RSP�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnDelVTRRsp( WPARAM wparam, LPARAM lparam );	


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
	const String m_strListVTR;
	const String m_strBtnAdd;
	const String m_strBtnModify;
	const String m_strBtnDel;


	//��ǰѡ�е����ܷ�������Ϣ
	TVcrCfg m_tVTRCfgSel;
};

#define VTRCFGLOGICRPTR    CVTRCfgLogic::GetSingletonPtr()               //VTRCfglogicָ��

#endif // !defined(UMSTOOL_VTRCFGLOGIC_H)
