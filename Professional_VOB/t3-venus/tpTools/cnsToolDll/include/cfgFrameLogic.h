// cfgFrameLogic.h: interface for the CCfgFrameLogic class.
 /*****************************************************************************
 ģ����      : cnsTool���ÿ��
 �ļ���      : cfgFrameLogic.h
 ����ļ�    : 
 �ļ�ʵ�ֹ���:  
 ˵��       �� ��ӦcfgFrame.xml,���а������ÿ��dlg �� ���ò˵�
 ����        : �����
 �汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
 -----------------------------------------------------------------------------
 �޸ļ�¼:
 ��  ��         �汾        �޸���      �޸�����
 2012/12/20    1.0          �����      ����
******************************************************************************/

#if !defined(AFX_CFGFRAMELOGIC_H__00B504BC_6D75_40A9_B8CA_3C1D51B04DCA__INCLUDED_)
#define AFX_CFGFRAMELOGIC_H__00B504BC_6D75_40A9_B8CA_3C1D51B04DCA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CCfgFrameLogic : public CLogicBase, public ISingleTon<CCfgFrameLogic>  
{
public:
	CCfgFrameLogic();
	virtual ~CCfgFrameLogic();

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
	/** ����:  �������õİ�ť
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	HRESULT OnDisConnect( WPARAM wparam, LPARAM lparam);
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
	bool OnClickCnsCfg( const IArgs& args );
	/** ����:  �����Ƶ�������ð�ť����Ӧ�¼�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnClickAudioPortCfg( const IArgs& args );
	/** ����:  ����������ð�ť����Ӧ�¼�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnClickNetMgrCfg( const IArgs& args );
	/** ����:  ����������ð�ť����Ӧ�¼�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnClickMixCfg( const IArgs& args );
	/** ����:  ������������ð�ť����Ӧ�¼�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnClickEqCfg( const IArgs& args );
	/** ����:  ������������ð�ť����Ӧ�¼�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnClickServerCfg( const IArgs& args );
	/** ����:  ����������ð�ť����Ӧ�¼�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnClickCallSerCfg( const IArgs& args );

	/** ����:  Tableҳ�л�����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void SwitchCfgTabWnd( string strWnd );
public:
	string m_strCfgCurWnd;//��ǰ��ʾ�Ĵ���
private:
	string m_strLstFunMenu;//�����б� 

};

#endif // !defined(AFX_CFGFRAMELOGIC_H__00B504BC_6D75_40A9_B8CA_3C1D51B04DCA__INCLUDED_)
