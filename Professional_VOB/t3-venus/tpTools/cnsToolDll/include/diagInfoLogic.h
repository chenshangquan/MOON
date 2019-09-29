// diagInfoLogic.h: interface for the CDiagInfoLogic class.
 /*****************************************************************************
 ģ����      : CDiagInfoLogic
 �ļ���      : diagInfoLogic.h
 ����ļ�    : 
 �ļ�ʵ�ֹ���: �����Ϣ����
 ����        : ������
 �汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
 -----------------------------------------------------------------------------
 �޸ļ�¼:
 ��  ��         �汾        �޸���      �޸�����
 2013/01/07     1.0         ������        ����
******************************************************************************/

#if !defined(AFX_DIAGINFOLOGIC_H__FF5413C7_513C_4617_BFF6_B87F5FCE8936__INCLUDED_)
#define AFX_DIAGINFOLOGIC_H__FF5413C7_513C_4617_BFF6_B87F5FCE8936__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CDiagInfoLogic : public CLogicBase, public ISingleTon<CDiagInfoLogic>   
{
public:
	CDiagInfoLogic();
	virtual ~CDiagInfoLogic();
	
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
	virtual void UnRegFunc();
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
    virtual void Clear();

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
	/** ����:  �յ����������ʵ���Ϣ��Ӧ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	LRESULT OnUpDownstreamNty( WPARAM wparam, LPARAM lparam);
	/** ����:  �յ�������Ϣ�Ļظ�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	LRESULT OnLostPacketRsp( WPARAM wparam, LPARAM lparam);
	/** ����:  �յ���ũ��˷����Ϣ����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	LRESULT OnUpdateAudioNty( WPARAM wparam, LPARAM lparam);
	/** ����:  ��ʾԴ����ӿ���Ϣ 
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	LRESULT OnVgaInfoNotify( WPARAM wparam, LPARAM lparam);
	/** ����:  ��ʾԴ����ӿ���Ϣ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	LRESULT OnVgaOutInfoNotify( WPARAM wparam, LPARAM lparam);
	/** ����:  �����ϲ��Եİ�ť
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnBtnDiagTest( const IArgs & arg );
				
	/** ����:  ����Group1��COMMON
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	String UpdateGroup1( TTpAudioPortInfo& tAudioPortInfo );
					
	/** ����:  ����Group2��COMMON
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	String UpdateGroup2( TTpAudioPortInfo& tAudioPortInfo );
						
	/** ����:  ����Group3��COMMON
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	String UpdateGroup3( TTpAudioPortInfo& tAudioPortInfo );
					
	/** ����:  ���ݷ���������Ĭ����Ƶ���õķ�����Ϣ�����½���
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	HRESULT OnDefaultAudioNty( WPARAM wparam, LPARAM lparam );
			
	/** ����:  �յ��������Ϣ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	LRESULT OnConfStateNty( WPARAM wparam, LPARAM lparam);
	
private:
	TDualSrcInfo m_tDualSrcInfo;					//��ʾԴ����ӿ���Ϣ
	TTPVgaMixInfo m_tVgaMixInfo;					//��ʾԴ����ӿ���Ϣ
	const String m_strLostPacket;					//������
    const String m_strUpstream;						//������������
    const String m_strDownstream;					//������������
	const String m_strComboboxInPort;				//��ʾԴ����ӿ�
	const String m_strComboboxOutPort;				//��ʾԴ����ӿ�
    const String m_strInAdPort1;					//COMMON1
	const String m_strInAdPort2;					//COMMON2
	const String m_strInAdPort3;					//COMMON3
};
		
#endif // !defined(AFX_DIAGINFOLOGIC_H__FF5413C7_513C_4617_BFF6_B87F5FCE8936__INCLUDED_)
