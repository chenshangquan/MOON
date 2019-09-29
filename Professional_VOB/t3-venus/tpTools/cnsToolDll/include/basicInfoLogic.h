// BasicInfoLogic.h: interface for the CBasicInfoLogic class.
/*****************************************************************************
ģ����      : CBasicInfoLogic
�ļ���      : BasicInfoLogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: ������Ϣ����
����        : ������
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/01/04     1.0         ������      ����
******************************************************************************/

#if !defined(AFX_BASICINFOLOGIC_H__3C7B10DF_6193_494D_BAD6_6822AB12AA2C__INCLUDED_)
#define AFX_BASICINFOLOGIC_H__3C7B10DF_6193_494D_BAD6_6822AB12AA2C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CBasicInfoLogic : public CLogicBase, public ISingleTon<CBasicInfoLogic>
{
public:
	CBasicInfoLogic();
	virtual ~CBasicInfoLogic();

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

	/** ����:  ���շ������Ļ᳡��Ϣ�����½���
	*  @param[in] 
	*  @return �ɹ�����true,ʧ�ܷ���false
	*  @remarks 
	*/
	HRESULT OnCnsInfoNty( WPARAM wparam, LPARAM lparam);

	/** ����:  ���շ������Ļ�����Ϣ�����½���
	*  @param[in] 
	*  @return �ɹ�����true,ʧ�ܷ���false
	*  @remarks 
	*/
	HRESULT OnConfInfoNty( WPARAM wparam, LPARAM lparam);
	
	/** ����:  ���շ���������TPad��IP��Ϣ�����½���
	*  @param[in] 
	*  @return �ɹ�����true,ʧ�ܷ���false
	*  @remarks 
	*/
	HRESULT OnTPadIPNty( WPARAM wparam, LPARAM lparam);
	
	/** ����:  ���շ������Ļ᳡ע��SIP��Ϣ�����½���
	*  @param[in] 
	*  @return �ɹ�����true,ʧ�ܷ���false
	*  @remarks 
	*/
	HRESULT OnRegSipNty( WPARAM wparam, LPARAM lparam);
	
	/** ����:  ���շ������Ļ᳡ע��GK��Ϣ�����½���
	*  @param[in] 
	*  @return �ɹ�����true,ʧ�ܷ���false
	*  @remarks 
	*/
	HRESULT OnRegGkNty( WPARAM wparam, LPARAM lparam);
	
	/** ����:  ���շ������Ļ᳡ע��NAT��Ϣ�����½���
	*  @param[in] 
	*  @return �ɹ�����true,ʧ�ܷ���false
	*  @remarks 
	*/
	HRESULT OnRegNATNty( WPARAM wparam, LPARAM lparam);
	
	/** ����:  ���շ���������CPU��RAM����Ϣ�����½���
	*  @param[in] 
	*  @return �ɹ�����true,ʧ�ܷ���false
	*  @remarks 
	*/
	HRESULT OnCPURAMNty( WPARAM wparam, LPARAM lparam);	
	
	/** ����:  ����ע��GK�Ļظ���Ϣ�ı����
	*  @param[in] 
	*  @return �ɹ�����true,ʧ�ܷ���false
	*  @remarks 
	*/
	HRESULT OnChangeGk( WPARAM wparam, LPARAM lparam);	
	
	/** ����:  ����ע��SIP�Ļظ���Ϣ�ı����
	*  @param[in] 
	*  @return �ɹ�����true,ʧ�ܷ���false
	*  @remarks 
	*/
	HRESULT OnChangeSip( WPARAM wparam, LPARAM lparam);	

private:
	/** ����:  ��������������ݲ����½���
	*  @param[in] IArgs  �������
	*  @return �ɹ�����true,ʧ�ܷ���false
	*  @remarks 
	*/
	bool OnBtnRefresh( const IArgs& args );
	
private:
	const String m_strStcSName;							//�᳡����
	const String m_strStcIPS;							//�᳡IP
	const String m_strStcSE164Num;						//�᳡E164
	const String m_strStcScrSNum;						//����
	const String m_strStcSDaul;							//˫��Դ
	const String m_strStcSSIP;							//ע�����ʷ�����
	const String m_strStcSGK;							//ע��GK
	const String m_strStcSNAT;							//��̬NAT��ַ
	const String m_strStcSCPU;							//CPUʹ����
	const String m_strStcSRam;							//�ڴ�ʹ����
	const String m_strStcConfSName;						//��������
	const String m_strStcConfSRate;						//��������
	const String m_strStcShowSRate;						//��ʾ����
	const String m_strStcAudioSRate;					//��Ƶ��ʽ
	const String m_strStcConfSHold;						//��������
	const String m_strStcConfSCallType;					//�����������

};

#endif // !defined(AFX_BASICINFOLOGIC_H__3C7B10DF_6193_494D_BAD6_6822AB12AA2C__INCLUDED_)
