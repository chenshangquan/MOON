// cfgEqLogic.h: interface for the CCfgEqLogic class.
//
//////////////////////////////////////////////////////////////////////
/*****************************************************************************
�ļ���      : CfgEqLogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: ��������еľ��������ý���
����        : ������
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/02/20     1.0         ������      ����
******************************************************************************/
#if !defined(AFX_CFGEQLOGIC_H__54D81828_1457_401C_A4DF_597F9F16F6EF__INCLUDED_)
#define AFX_CFGEQLOGIC_H__54D81828_1457_401C_A4DF_597F9F16F6EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CCfgEqLogic : public CLogicBase, public ISingleTon<CCfgEqLogic>  
{
public:
	CCfgEqLogic();
	virtual ~CCfgEqLogic();
	
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
	bool IsCfgEqChange();

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

	/** ����:  �л�����������ʱ�����Ƿ񱣴�Ĵ���	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveMsgBox();

	/** ����:  ���շ������˷���������ϢȻ����¾�����״̬
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnUpdateEqNty( WPARAM wParam, LPARAM lParam );

	/** ����:  ���ݷ���������Ĭ����Ƶ���������õķ�����Ϣ�����½���
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnDefaultEqNty( WPARAM wParam, LPARAM lParam );

	/** ����:  ������Ƶ������Ĭ������	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	void SetEqDefaultData();
															
	/** ����:  ���þ�������Ϣ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	void SetEqInfo();
														
	/** ����:  ���þ���������Ƶ����Ϣ
	*  @param[in] strWndName Ƶ�ʴ������� nGroup ����Ƶ���	nNum ���  
	*  @return 
	*  @remarks   
	*/	
	void SetEqRate( String strWndName, s32 nGroup, s32 nNum );

	/** ����:  ��ȡlib���е���Ƶ����������	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	void GetEqData();
														
	/** ����:  ����Ƶ1���е�slider�仯,�ı�Eq100�ؼ���ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld1Eq100Changed( const IArgs& args );
											
	/** ����:  ����Ƶ1���е�slider�仯,�ı�Eq200�ؼ���ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld1Eq200Changed( const IArgs& args );
														
	/** ����:  ����Ƶ1���е�slider�仯,�ı�Eq400�ؼ���ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld1Eq400Changed( const IArgs& args );
															
	/** ����:  ����Ƶ1���е�slider�仯,�ı�Eq600�ؼ���ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld1Eq600Changed( const IArgs& args );
															
	/** ����:  ����Ƶ1���е�slider�仯,�ı�Eq1K�ؼ���ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld1Eq1KChanged( const IArgs& args );
															
	/** ����:  ����Ƶ1���е�slider�仯,�ı�Eq3K�ؼ���ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld1Eq3KChanged( const IArgs& args );
															
	/** ����:  ����Ƶ1���е�slider�仯,�ı�Eq6K�ؼ���ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld1Eq6KChanged( const IArgs& args );
															
	/** ����:  ����Ƶ1���е�slider�仯,�ı�Eq12K�ؼ���ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld1Eq12KChanged( const IArgs& args );
																	
	/** ����:  ����Ƶ1���е�slider�仯,�ı�Eq14K�ؼ���ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld1Eq14KChanged( const IArgs& args );
															
	/** ����:  ����Ƶ1���е�slider�仯,�ı�Eq16K�ؼ���ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld1Eq16KChanged( const IArgs& args );
														
	/** ����:  ����Ƶ2���е�slider�仯,�ı�Eq100�ؼ���ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld2Eq100Changed( const IArgs& args );
											
	/** ����:  ����Ƶ2���е�slider�仯,�ı�Eq200�ؼ���ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld2Eq200Changed( const IArgs& args );
														
	/** ����:  ����Ƶ2���е�slider�仯,�ı�Eq400�ؼ���ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld2Eq400Changed( const IArgs& args );
															
	/** ����:  ����Ƶ2���е�slider�仯,�ı�Eq600�ؼ���ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld2Eq600Changed( const IArgs& args );
															
	/** ����:  ����Ƶ2���е�slider�仯,�ı�Eq1K�ؼ���ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld2Eq1KChanged( const IArgs& args );
															
	/** ����:  ����Ƶ2���е�slider�仯,�ı�Eq3K�ؼ���ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld2Eq3KChanged( const IArgs& args );
															
	/** ����:  ����Ƶ2���е�slider�仯,�ı�Eq6K�ؼ���ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld2Eq6KChanged( const IArgs& args );
															
	/** ����:  ����Ƶ2���е�slider�仯,�ı�Eq12K�ؼ���ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld2Eq12KChanged( const IArgs& args );
																
	/** ����:  ����Ƶ2���е�slider�仯,�ı�Eq14K�ؼ���ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld2Eq14KChanged( const IArgs& args );
															
	/** ����:  ����Ƶ2���е�slider�仯,�ı�Eq16K�ؼ���ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld2Eq16KChanged( const IArgs& args );
																
	/** ����:  ����Ƶ3���е�slider�仯,�ı�Eq100�ؼ���ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld3Eq100Changed( const IArgs& args );
											
	/** ����:  ����Ƶ3���е�slider�仯,�ı�Eq200�ؼ���ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld3Eq200Changed( const IArgs& args );
														
	/** ����:  ����Ƶ3���е�slider�仯,�ı�Eq400�ؼ���ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld3Eq400Changed( const IArgs& args );
															
	/** ����:  ����Ƶ3���е�slider�仯,�ı�Eq600�ؼ���ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld3Eq600Changed( const IArgs& args );
															
	/** ����:  ����Ƶ3���е�slider�仯,�ı�Eq1K�ؼ���ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld3Eq1KChanged( const IArgs& args );
															
	/** ����:  ����Ƶ3���е�slider�仯,�ı�Eq3K�ؼ���ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld3Eq3KChanged( const IArgs& args );
															
	/** ����:  ����Ƶ3���е�slider�仯,�ı�Eq6K�ؼ���ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld3Eq6KChanged( const IArgs& args );
															
	/** ����:  ����Ƶ3���е�slider�仯,�ı�Eq12K�ؼ���ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld3Eq12KChanged( const IArgs& args );
																
	/** ����:  ����Ƶ3���е�slider�仯,�ı�Eq14K�ؼ���ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld3Eq14KChanged( const IArgs& args );
															
	/** ����:  ����Ƶ3���е�slider�仯,�ı�Eq16K�ؼ���ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld3Eq16KChanged( const IArgs& args );
				
	/** ����:  ��������Ƶ1���о������Ŀ���,�ı�slider״̬,�ж������Ƿ�ı�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnSwitchEq1( const IArgs& args );
						
	/** ����:  ��������Ƶ2���о������Ŀ���,�ı�slider״̬,�ж������Ƿ�ı�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnSwitchEq2( const IArgs& args );
							
	/** ����:  ��������Ƶ3���о������Ŀ���,�ı�slider״̬,�ж������Ƿ�ı�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnSwitchEq3( const IArgs& args );
							
	/** ����:  �ж�EqƵ�������Ƿ�ı�,���»�����m_vctWndName��Ŀ
	*  @param[in] strWndName Ƶ�ʴ������� nGroup ����Ƶ���	nNum ��� 
	*  @return 
	*  @remarks   
	*/	
	void CheckEqRate( String strWndName, s32 nGroup, s32 nNum );

	/** ����:  ��������Ƶ1Eq
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveEq1();

	/** ����:  ��������Ƶ2Eq
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveEq2();
	
	/** ����:  ��������Ƶ3Eq
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveEq3();
														
	/** ����:  �������������Ƶ����Ϣ
	*  @param[in] strWndName Ƶ�ʴ������� nGroup ����Ƶ���	nNum ���  
	*  @return 
	*  @remarks   
	*/	
	void SaveEqRate( String strWndName, s32 nGroup, s32 nNum );
			
private:
	TTPEqualizer m_atEqInfo[3];
	TTPEqualizer m_atOldEqInfo[3];
	const String m_strBtnEq1Switch;			//����Ƶ1����������
	const String m_strBtnEq2Switch;			//����Ƶ2����������
	const String m_strBtnEq3Switch;			//����Ƶ3����������
};

#endif // !defined(AFX_CFGEQLOGIC_H__54D81828_1457_401C_A4DF_597F9F16F6EF__INCLUDED_)
