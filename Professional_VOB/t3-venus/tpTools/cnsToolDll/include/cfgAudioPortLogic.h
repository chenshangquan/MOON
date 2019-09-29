// cfgAudioPortLogic.h: interface for the CCfgAudioPortLogic class.
/*****************************************************************************
ģ����      : CCfgAudioPortLogic
�ļ���      : cfgAudioPortLogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: ��������е���Ƶ���ý���
����        : ������
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/01/04     1.0         ������      ����
******************************************************************************/

#if !defined(AFX_CFGAUDIOPORTLOGIC_H__77D62CD0_FC1C_4BEF_91F2_3ED104CF6C3D__INCLUDED_)
#define AFX_CFGAUDIOPORTLOGIC_H__77D62CD0_FC1C_4BEF_91F2_3ED104CF6C3D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CCfgAudioPortLogic : public CLogicBase, public ISingleTon<CCfgAudioPortLogic> 
{
public:
	CCfgAudioPortLogic();
	virtual ~CCfgAudioPortLogic();

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

	/** ����:  �ж�audio���ý����Ƿ�Ķ�(�л�tableҳʱ��������)
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
    bool IsCfgAudioChange();
	
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
		
	/** ����:  ���������������
	*  @param[in] IArgs  �������
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnSave( const IArgs& args );
		
	/** ����:  �ָ������ʼ��
	*  @param[in] IArgs  �������
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
		
	/** ����:  ������Ƶ������
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	void SetAudioData();
		
	/** ����:  ��ʼ����Ƶ�ӿڽ���ؼ�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	void InitCtrlEnable();
					
	/** ����:  ������Ƶ���ý����1��2��3
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	bool SaveGroup1();
			
	/** ����:  ������Ƶ���ý����4��5��6
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool SaveGroup2();
				
	/** ����:  ������Ƶ���ý����7��8��9
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool SaveGroup3();
				
	/** ����:  ������Ƶ���ý����и������е�10
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool SaveGroup10();
				
	/** ����:  ������Ƶ���ý����Group1
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool UpdateGroup1( TTpAudioPortInfo& tAudioPortInfo );
					
	/** ����:  ������Ƶ���ý����Group2
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool UpdateGroup2( TTpAudioPortInfo& tAudioPortInfo );
						
	/** ����:  ������Ƶ���ý����Group3
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool UpdateGroup3( TTpAudioPortInfo& tAudioPortInfo );
						
	/** ����:  ���շ�����������Ƶ���õ���Ϣ�����½���
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	HRESULT OnUpdateAudioNty( WPARAM wparam, LPARAM lparam );
						
	/** ����:  ���ݷ���������Ĭ����Ƶ���õķ�����Ϣ�����½���
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	HRESULT OnDefaultAudioNty( WPARAM wparam, LPARAM lparam );
							
	/** ����:  ����slider�仯,�ı������ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSliderGain1Changed( const IArgs& args );
						
	/** ����:  ����slider�仯,�ı䱳��������ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSliderBNA1Changed( const IArgs& args );
						
	/** ����:  ����edit�仯,�ı�������ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnEditGain1Changed( const IArgs& args );
						
	/** ����:  ����edit�仯,�ı�������ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnEditBNA1Changed( const IArgs& args );
						
	/** ����:  ����slider�仯,�ı������ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSliderGain2Changed( const IArgs& args );
						
	/** ����:  ����slider�仯,�ı䱳��������ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSliderBNA2Changed( const IArgs& args );
						
	/** ����:  ����edit�仯,�ı�������ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnEditGain2Changed( const IArgs& args );
						
	/** ����:  ����edit�仯,�ı�������ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnEditBNA2Changed( const IArgs& args );
												
	/** ����:  ����slider�仯,�ı������ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSliderGain3Changed( const IArgs& args );
						
	/** ����:  ����slider�仯,�ı䱳��������ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSliderBNA3Changed( const IArgs& args );
						
	/** ����:  ����edit�仯,�ı�������ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnEditGain3Changed( const IArgs& args );
						
	/** ����:  ����edit�仯,�ı�������ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnEditBNA3Changed( const IArgs& args );
												
	/** ����:  ����slider�仯,�ı������ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSliderGain4Changed( const IArgs& args );
						
	/** ����:  ����slider�仯,�ı䱳��������ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSliderBNA4Changed( const IArgs& args );
						
	/** ����:  ����edit�仯,�ı�������ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnEditGain4Changed( const IArgs& args );
						
	/** ����:  ����edit�仯,�ı�������ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnEditBNA4Changed( const IArgs& args );
												
	/** ����:  ����slider�仯,�ı������ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSliderGain5Changed( const IArgs& args );
						
	/** ����:  ����slider�仯,�ı䱳��������ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSliderBNA5Changed( const IArgs& args );
						
	/** ����:  ����edit�仯,�ı�������ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnEditGain5Changed( const IArgs& args );
						
	/** ����:  ����edit�仯,�ı�������ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnEditBNA5Changed( const IArgs& args );
												
	/** ����:  ����slider�仯,�ı������ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSliderGain6Changed( const IArgs& args );
						
	/** ����:  ����slider�仯,�ı䱳��������ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSliderBNA6Changed( const IArgs& args );
						
	/** ����:  ����edit�仯,�ı�������ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnEditGain6Changed( const IArgs& args );
						
	/** ����:  ����edit�仯,�ı�������ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnEditBNA6Changed( const IArgs& args );
												
	/** ����:  ����slider�仯,�ı������ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSliderGain7Changed( const IArgs& args );
						
	/** ����:  ����slider�仯,�ı䱳��������ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSliderBNA7Changed( const IArgs& args );
						
	/** ����:  ����edit�仯,�ı�������ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnEditGain7Changed( const IArgs& args );
						
	/** ����:  ����edit�仯,�ı�������ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnEditBNA7Changed( const IArgs& args );
												
	/** ����:  ����slider�仯,�ı������ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSliderGain8Changed( const IArgs& args );
						
	/** ����:  ����slider�仯,�ı䱳��������ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSliderBNA8Changed( const IArgs& args );
						
	/** ����:  ����edit�仯,�ı�������ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnEditGain8Changed( const IArgs& args );
						
	/** ����:  ����edit�仯,�ı�������ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnEditBNA8Changed( const IArgs& args );
												
	/** ����:  ����slider�仯,�ı������ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSliderGain9Changed( const IArgs& args );
						
	/** ����:  ����slider�仯,�ı䱳��������ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSliderBNA9Changed( const IArgs& args );
						
	/** ����:  ����edit�仯,�ı�������ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnEditGain9Changed( const IArgs& args );
						
	/** ����:  ����edit�仯,�ı�������ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnEditBNA9Changed( const IArgs& args );
												
	/** ����:  ����slider�仯,�ı������ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSliderGain10Changed( const IArgs& args );
						
	/** ����:  ����slider�仯,�ı䱳��������ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSliderBNA10Changed( const IArgs& args );
						
	/** ����:  ����edit�仯,�ı�������ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnEditGain10Changed( const IArgs& args );
						
	/** ����:  ����edit�仯,�ı�������ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnEditBNA10Changed( const IArgs& args );
												
	/** ����:  δѡ��audio1֮�������������Ӧ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnNoSelAudio1( const IArgs& args );
						
	/** ����:  ѡ��audio1֮�������������Ӧ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSelAudio1( const IArgs& args );
													
	/** ����:  δѡ��audio2֮�������������Ӧ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnNoSelAudio2( const IArgs& args );
						
	/** ����:  ѡ��audio2֮�������������Ӧ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSelAudio2( const IArgs& args );
												
	/** ����:  δѡ��audio3֮�������������Ӧ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnNoSelAudio3( const IArgs& args );
						
	/** ����:  ѡ��audio3֮�������������Ӧ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSelAudio3( const IArgs& args );
												
	/** ����:  δѡ��audio4֮�������������Ӧ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnNoSelAudio4( const IArgs& args );
						
	/** ����:  ѡ��audio4֮�������������Ӧ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSelAudio4( const IArgs& args );
												
	/** ����:  δѡ��audio5֮�������������Ӧ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnNoSelAudio5( const IArgs& args );
						
	/** ����:  ѡ��audio5֮�������������Ӧ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSelAudio5( const IArgs& args );
												
	/** ����:  δѡ��audio6֮�������������Ӧ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnNoSelAudio6( const IArgs& args );
						
	/** ����:  ѡ��audio6֮�������������Ӧ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSelAudio6( const IArgs& args );
												
	/** ����:  δѡ��audio7֮�������������Ӧ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnNoSelAudio7( const IArgs& args );
						
	/** ����:  ѡ��audio7֮�������������Ӧ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSelAudio7( const IArgs& args );
												
	/** ����:  δѡ��audio8֮�������������Ӧ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnNoSelAudio8( const IArgs& args );
						
	/** ����:  ѡ��audio8֮�������������Ӧ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSelAudio8( const IArgs& args );
												
	/** ����:  δѡ��audio9֮�������������Ӧ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnNoSelAudio9( const IArgs& args );
						
	/** ����:  ѡ��audio9֮�������������Ӧ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSelAudio9( const IArgs& args );
												
	/** ����:  δѡ��audio10֮�������������Ӧ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnNoSelAudio10( const IArgs& args );
						
	/** ����:  ѡ��audio10֮�������������Ӧ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSelAudio10( const IArgs& args );
						
	/** ����:  ѡ��ũ1���󹩵簴ť֮��,�ж������Ƿ�ı�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnSwitchSimPower1( const IArgs& args );
						
	/** ����:  ѡ��ũ2���󹩵簴ť֮��,�ж������Ƿ�ı�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnSwitchSimPower2( const IArgs& args );
						
	/** ����:  ѡ��ũ3���󹩵簴ť֮��,�ж������Ƿ�ı�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnSwitchSimPower3( const IArgs& args );
						
	/** ����:  ѡ��ũ4���󹩵簴ť֮��,�ж������Ƿ�ı�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnSwitchSimPower4( const IArgs& args );
						
	/** ����:  ѡ��ũ5���󹩵簴ť֮��,�ж������Ƿ�ı�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnSwitchSimPower5( const IArgs& args );
						
	/** ����:  ѡ��ũ6���󹩵簴ť֮��,�ж������Ƿ�ı�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnSwitchSimPower6( const IArgs& args );
						
	/** ����:  ѡ��ũ7���󹩵簴ť֮��,�ж������Ƿ�ı�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnSwitchSimPower7( const IArgs& args );
						
	/** ����:  ѡ��ũ8���󹩵簴ť֮��,�ж������Ƿ�ı�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnSwitchSimPower8( const IArgs& args );
						
	/** ����:  ѡ��ũ9���󹩵簴ť֮��,�ж������Ƿ�ı�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnSwitchSimPower9( const IArgs& args );
						
	/** ����:  ѡ��ũ10���󹩵簴ť֮��,�ж������Ƿ�ı�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnSwitchSimPower10( const IArgs& args );
								
	/** ����:  ��ȡ���濨ũ10�е�����
	*  @param[in] nGroup  ����Ƶ���
	*  @return 
	*  @remarks   
	*/	
	void GetAudio10( s32 nGroup );

	/** ����:  �л�����������ʱ�����Ƿ񱣴�Ĵ���	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveMsgBox();

	/** ����:  ��ȡlib���е���Ƶ�ӿ�����	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	void GetAudioInfo();

	/** ����:  ��ȡ������뿪��״̬Ȼ����lib���бȶ�,���»���m_vctWndName��Ŀ
	*  @param[in] strWndName ��������	nGroup ����Ƶ���	nNum ���   
	*  @return 
	*  @remarks   
	*/	
	void UpdateSimPowerNum( String strWndName, s32 nGroup, s32 nNum );

	/** ����:  ��ȡ���������ֵȻ����lib���бȶ�,���½���
				Edit�������ݺͻ���m_vctWndName����Ŀ
	*  @param[in] strWndName slider�ؼ����� strEditName edit������	nGroup ����Ƶ���	nNum ���   
	*  @return 
	*  @remarks   
	*/	
	void UpdateGainNum( String strGainName, String strEditName, s32 nGroup, s32 nNum );

	/** ����:  ��ȡ���汳��������ֵȻ����lib���бȶ�,���½���
				Edit�������ݺͻ���m_vctWndName����Ŀ
	*  @param[in] strWndName slider�ؼ����� strEditName edit������	nGroup ����Ƶ���	nNum ���   
	*  @return 
	*  @remarks   
	*/	
	void UpdateBNANum( String strBNAName, String strEditName, s32 nGroup, s32 nNum );

	/** ����:  ����edit���е����ݸ�������slider�ؼ�
				���BNA�����Ƿ�仯,���»���m_vctWndName��Ŀ
	*  @param[in] strWndName slider�ؼ����� strEditName edit������   nGroup ����Ƶ���	nNum ���  
	*  @return 
	*  @remarks   
	*/	
	void UpdateGainEdit( String strEditName, String strSliderName, s32 nGroup, s32 nNum );

	/** ����:  ����edit���е����ݸ��±�������slider�ؼ�
				���BNA�����Ƿ�仯,���»���m_vctWndName��Ŀ
	*  @param[in] strWndName slider�ؼ����� strEditName edit������   nGroup ����Ƶ���	nNum ���  
	*  @return 
	*  @remarks   
	*/	
	void UpdateBNAEdit( String strEditName, String strSliderName, s32 nGroup, s32 nNum );

	/** ����:  ����check���Ƿ�ѡ��������ͬһ��ؼ��Ƿ���ʾ������m_vctWndName����Ŀ
	*  @param[in] strCheckName check�ؼ�����	nGroup ����Ƶ���	nNum ���  
					strShmShow ѡ��ִ����ʾ����	strShmHide δѡ��ִ�����ط���
	*  @return 
	*  @remarks   
	*/	
	bool UpdateCheckNum( String strCheckName, s32 nGroup, s32 nNum, String strShmShow, String strShmHide );

	/** ����:  ������Ƶ�ӿ�Ĭ������	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	void SetDefaultAudioInfo();
		
private:
	TTpAudioPortInfo m_atAudioPortInfo[3];
	TTpAudioPortInfo m_atOldAudioPortInfo[3];
	const String m_strAudioPort1;							//GANNON1
	const String m_strAudioPort2;							//GANNON2
	const String m_strAudioPort3;							//GANNON3
	const String m_strAudioPort4;							//GANNON4
	const String m_strAudioPort5;							//GANNON5
	const String m_strAudioPort6;							//GANNON6
	const String m_strAudioPort7;							//GANNON7
	const String m_strAudioPort8;							//GANNON8
	const String m_strAudioPort9;							//GANNON9
	const String m_strAudioPort110;							//GANNON110
	const String m_strAudioPort210;							//GANNON210
	const String m_strAudioPort310;							//GANNON310
	const String m_strNoPort10;								//GANNON10û������
};

#endif // !defined(AFX_CFGAUDIOPORTLOGIC_H__77D62CD0_FC1C_4BEF_91F2_3ED104CF6C3D__INCLUDED_)
