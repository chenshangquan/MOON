// CentCfgFrameLogic.h: interface for the CCentCfgFrameLogic class.
//
//////////////////////////////////////////////////////////////////////
/*****************************************************************************
 ģ����      : cnsTool���ÿ��
 �ļ���      : CentCfgFrameLogic.h
 ����ļ�    : 
 �ļ�ʵ�ֹ���:  
 ˵��        : �п����ý�����:�����ƹ⡢��������·����ڽ�����ڼ򵥽���Ϣ��Ӧ����CCentCfgFrameLogic��
			   ������3��������������ش���°汾,������������������
 ����        : ������
 �汾        : 
 -----------------------------------------------------------------------------
 �޸ļ�¼:
 ��  ��         �汾        �޸���      �޸�����
 2014/05/12     1.0                       ����
******************************************************************************/

#if !defined(AFX_CENTCFGFRAMELOGIC_H__F0748436_1FCC_4573_842C_9AF1991CD365__INCLUDED_)
#define AFX_CENTCFGFRAMELOGIC_H__F0748436_1FCC_4573_842C_9AF1991CD365__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CCentCfgFrameLogic : public CLogicBase, public ISingleTon<CCentCfgFrameLogic>   
{
public:
	CCentCfgFrameLogic();
	virtual ~CCentCfgFrameLogic();

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
	/** ����:  �������д���
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void HideAllWnd();
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
	/** ����:  ��ʼ�����ò˵�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void InitCfgFuncMenu();	

	/** ����:  ���cns���ð�ť����Ӧ�¼�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnClickXinFengCfg( const IArgs& args );

	/** ����:  �����Ƶ�������ð�ť����Ӧ�¼�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnClickCameraCfg( const IArgs& args );

	/** ����:  ����������ð�ť����Ӧ�¼�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnClickLightCfg( const IArgs& args );

	/** ����:  ����������ð�ť����Ӧ�¼�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnClickDisplayCfg( const IArgs& args );

	/** ����:  Tableҳ�л�����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void SwitchCfgTabWnd( string strWnd );
	
	/** ����:  ���շ������˷���������ϢȻ����������״̬
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnCameraInfoNty( WPARAM wParam, LPARAM lParam );
	
	/** ����:  ��������Ŀ���״̬ת��Ϊstring����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	String CamStateToString( EmCamPowerMode& emSwitchState );

	/** ����:  ���շ������˷���������ϢȻ������ĵ������״̬
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnDocCamInfoNty( WPARAM wParam, LPARAM lParam );

	/** ����:  ���շ������˷���������ϢȻ����¿յ�״̬
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnAirInfoNty( WPARAM wParam, LPARAM lParam );

	/** ����:  ���շ������˷���������ϢȻ������·�״̬
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnXinFengInfoNty( WPARAM wParam, LPARAM lParam );

	/** ����:  ���շ������˷���������ϢȻ����µƹ�״̬
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnLightInfoNty( WPARAM wParam, LPARAM lParam );

	/** ����:  ���շ������˷������Ĵ�����ϢȻ��ע���ص���½����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnCentSleepNty( WPARAM wParam, LPARAM lParam );

public:
	string m_strCfgCurWnd;//��ǰ��ʾ�Ĵ���
private:
	string m_strLstFunMenu;//�����б� 

};

#endif // !defined(AFX_CENTCFGFRAMELOGIC_H__F0748436_1FCC_4573_842C_9AF1991CD365__INCLUDED_)
