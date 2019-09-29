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
#if !defined(AFX_ORDERPOSINFOLOGIC_H__B06B345C_CF30_42B5_9B64_5F72C61D6269__INCLUDED_)
#define AFX_ORDERPOSINFOLOGIC_H__B06B345C_CF30_42B5_9B64_5F72C61D6269__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class COrderPosInfoLogic : public CLogicBase, public ISingleTon<COrderPosInfoLogic> 
{
public:
	COrderPosInfoLogic();
	virtual ~COrderPosInfoLogic();
	
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

	bool OnComboboxpresetIndexClick( const IArgs& args );

	bool OnBtnPresetInfoOk( const IArgs& args );

	bool OnBtnPresetInfoCancel( const IArgs& args );

	bool OnBtnClose( const IArgs& args );

	void UpdatePreData( TTPCamPre tTPCamPre );

protected:
	HRESULT OnOrderPosSelData( WPARAM wparam, LPARAM lparam );

	HRESULT OnCamPreSetListInd( WPARAM wparam, LPARAM lparam );
	
	HRESULT OnUpdateBtnStatus( WPARAM wparam, LPARAM lparam );
private:	
	/** ����:  ��������ʱ�۽��ڳ���Ĵ���	
	*  @param[in] strWindow   ��������
	*  @return 
	*  @remarks   
	*/	
	void FocusWindow(String strWindow);
	

	s32 GetPresetIndex( string strPresetInfo );
private:
	//���߼���Ԫ��Ӧ�����пؼ���
	const String m_strCombOutputStyle;
	const String m_strSoftWareInfo;
	const String m_strEdtPresetInfo;

	//Ԥ��λ��������
	EM_ORDERPOSOPT_TYPE m_emOPType;

	//��ǰѡ�е�Ԥ��λ��Ϣ
	TTPCamPre m_tCamPreSel;
	std::vector<TTPCamPre> m_vecTPCamPreInfo;
	bool				   m_bIsWaitForTra;
};

#define ORDERPOSINFOLOGICRPTR    COrderPosInfoLogic::GetSingletonPtr()               //�ϴ������룩ͨ�õ�������logicָ��

#endif // !defined(AFX_CFGSERVERLOGIC_H__B06B345C_CF30_42B5_9B64_5F72C61D6269__INCLUDED_)
