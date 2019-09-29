// centCtrlLogic.h: interface for the CCentCtrlLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CENTCTRLLOGIC_H__777D44E7_A11A_4507_AA4E_F26B05745548__INCLUDED_)
#define AFX_CENTCTRLLOGIC_H__777D44E7_A11A_4507_AA4E_F26B05745548__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CCentCtrlLogic : public CLogicBase, public ISingleTon<CCentCtrlLogic>    
{
public:
	CCentCtrlLogic();
	virtual ~CCentCtrlLogic();

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

	/** ����:  ���շ������˷���������ϢȻ�������ʾ��״̬
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnDisplayInfoNty( WPARAM wParam, LPARAM lParam );

	/** ����:  ���շ������˷���������ϢȻ����������״̬
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnCameraInfoNty( WPARAM wParam, LPARAM lParam );

	/** ����:  ���շ������˷���������ϢȻ������ĵ������״̬
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnDocCamInfoNty( WPARAM wParam, LPARAM lParam );

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

	/** ����:  ����ʾ���Ŀ���״̬ת��Ϊstring����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	String StateToString( EmTvPowerMode& emSwitchState );

	/** ����:  ��������Ŀ���״̬ת��Ϊstring����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	String CamStateToString( EmCamPowerMode& emSwitchState );
private:
	const String m_strAirInfo;							//�յ�
	const String m_strXinFengInfo;						//�·�
	const String m_strDisPlay1Info;						//��ʾ��һ
	const String m_strDisPlay2Info;						//��ʾ����
	const String m_strDisPlay3Info;						//��ʾ����
	const String m_strCamera1Info;						//�����һ
	const String m_strCamera2Info;						//�������
	const String m_strCamera3Info;						//�������
	const String m_strDocCameraInfo;					//�ĵ������

};

#endif // !defined(AFX_CENTCTRLLOGIC_H__777D44E7_A11A_4507_AA4E_F26B05745548__INCLUDED_)
