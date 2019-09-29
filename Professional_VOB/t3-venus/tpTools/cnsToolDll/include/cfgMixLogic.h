// cfgMixLogic.h: interface for the CCfgMixLogic class.
//////////////////////////////////////////////////////////////////////
/*****************************************************************************
�ļ���      : CfgMixLogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: ��������еĻ������ý���
����        : ������
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/02/20     1.0         ������      ����
******************************************************************************/
#if !defined(AFX_CFGMIXLOGIC_H__59D20473_A152_4386_9B30_20974F68D33B__INCLUDED_)
#define AFX_CFGMIXLOGIC_H__59D20473_A152_4386_9B30_20974F68D33B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CCfgMixLogic : public CLogicBase, public ISingleTon<CCfgMixLogic>
{
public:
	CCfgMixLogic();
	virtual ~CCfgMixLogic();
	
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
	bool IsCfgMixChange();

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
	/** ����:  �ָ�Ĭ�����õİ�ť
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnDefault( const IArgs& args );

	/** ����:  ���շ������˷���������ϢȻ����»���״̬
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnUpdateMixerNty( WPARAM wParam, LPARAM lParam );

	/** ����:  ���ݷ���������Ĭ�ϻ������õķ�����Ϣ�����½���
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnDefaultMixerNty( WPARAM wParam, LPARAM lParam );

	/** ����:  ��ȡcns�˵Ļ�������
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	void GetMixInfo();

	/** ����:  ���ݽ��յ����ݸ��»���״̬
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SetMixState();

	/** ����:  ���浥·����Ƶ��1�Ļ���·��
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveGroup1();

	/** ����:  ���浥·����Ƶ��2�Ļ���·��
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveGroup2();

	/** ����:  ���浥·����Ƶ��3�Ļ���·��
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveGroup3();

	/** ����:  ����᳡����Ƶ�Ļ���·��
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveRoomGroup();

	/** ����:  �л�����������ʱ�����Ƿ񱣴�Ĵ���	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveMsgBox();
						
	/** ����:  ѡ������Ƶ��1,�Ա�lib�������ݸı����½Ǳ���ȡ����ť״̬
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSelAudio1Group( const IArgs& args );
						
	/** ����:  ѡ������Ƶ��2,�Ա�lib�������ݸı����½Ǳ���ȡ����ť״̬
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSelAudio2Group( const IArgs& args );
								
	/** ����:  ѡ������Ƶ��3,�Ա�lib�������ݸı����½Ǳ���ȡ����ť״̬
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSelAudio3Group( const IArgs& args );
								
	/** ����:  ѡ�����·��,�Ա�lib�������ݸı����½Ǳ���ȡ����ť״̬
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSelMixGroup( const IArgs& args );

	/** ����:  ���û���Ĭ������	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	void SetDefaultMixInfo();
					
private:
	u8 m_aAudioMixerInfo[4];
	u8 m_aOldAudioMixerInfo[4];
	
	const String m_strAudio1Group1;							//����Ƶ��1�е�1
	const String m_strAudio1Group2;							//����Ƶ��1�е�2
	const String m_strAudio1Group3;							//����Ƶ��1�е�3
	const String m_strAudio1Group4;							//����Ƶ��1�е�4
	const String m_strAudio2Group1;							//����Ƶ��2�е�1
	const String m_strAudio2Group2;							//����Ƶ��2�е�2
	const String m_strAudio2Group3;							//����Ƶ��2�е�3
	const String m_strAudio2Group4;							//����Ƶ��2�е�4
	const String m_strAudio3Group1;							//����Ƶ��3�е�1
	const String m_strAudio3Group2;							//����Ƶ��3�е�2
	const String m_strAudio3Group3;							//����Ƶ��3�е�3
	const String m_strAudio3Group4;							//����Ƶ��3�е�4
	const String m_strMixGroup1;							//����·���е�1
	const String m_strMixGroup2;							//����·���е�2
	const String m_strMixGroup3;							//����·���е�3

};

#endif // !defined(AFX_CFGMIXLOGIC_H__59D20473_A152_4386_9B30_20974F68D33B__INCLUDED_)
