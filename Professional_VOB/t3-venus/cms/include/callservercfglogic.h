/*****************************************************************************
ģ����      : CCallServerCfgLogic
�ļ���      : callservercfglogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: ���з���������
����        : ʯ��
�汾        : V1.0  Copyright(C) 2013-2014 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/3/19      1.0         ʯ��			����
******************************************************************************/
#if !defined(UMC_CALLSERVERCFGLOGIC_H)
#define UMC_CALLSERVERCFGLOGIC_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CCallServerCfgLogic : public CWndLogicBase 
{
public:
	CCallServerCfgLogic();
	virtual ~CCallServerCfgLogic();
	static CCallServerCfgLogic* GetLogicPtr();
	
public:
	virtual bool RegCBFun();
	virtual bool UnRegFunc();
	virtual void RegMsg();

    /**	 
	* ����:  �������״̬������
	* @return   
	* @remarks	 
	*/
    virtual void Clear();

protected:
	bool InitWnd( const IArgs & args );

	/**	 
	* ����:  ���ϵͳ����
	* @return  bool
	* @remarks  
	*/
	bool OnSysCfg( const IArgs& args );
	
	bool IsAudioFormatChange();
		
	bool IsConfPollChange();
		
	bool IsConfDisChange();	
	
	bool IsDualCallRateChange();	
	
	bool IsCallRateChange();	
	
	bool IsDualVideoFomatChange();
	
	bool IsVideoFomatChange();

	/**	 
	* ����:  ����༭
	* @return  bool
	* @remarks  
	*/
	bool OnEdit( const IArgs& args );

	/**	 
	* ����:  ���ȡ��
	* @return  bool
	* @remarks  
	*/
	bool OnCancel( const IArgs& args );

	/**
	* ����:  �������
	* @return  bool
	* @remarks  
	*/
	bool OnSave( const IArgs& args );

	bool OnCloseDlg( const IArgs & arg );

	bool OnBtnCallMode( const IArgs & arg );
	bool OnBtnCallShowMode( const IArgs & arg );
	bool OnBtnAudioMode( const IArgs & arg );

	LRESULT OnCallServiceInfoNty( WPARAM wParam, LPARAM lParam );
	LRESULT OnCallServerInfoInd( WPARAM wParam, LPARAM lParam );
	LRESULT OnModeChoose2CallServerModeNty( WPARAM wParam, LPARAM lParam );
	LRESULT OnShowModeChoose2CallServerModeNty( WPARAM wParam, LPARAM lParam );
	LRESULT OnAudioMode2CallSerNty( WPARAM wParam, LPARAM lParam );

	/** ����:  ���ݷ�����������Ƶ��ʽ�ķ�����Ϣ�����½���
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	HRESULT OnUpdateAudioFormat( WPARAM wparam, LPARAM lparam );

	/** ����:  ���ݷ��������ջ�����ѡ��ʽ�ķ�����Ϣ�����½���
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	HRESULT OnUpdateVideoFormat( WPARAM wparam, LPARAM lparam );
						
	/** ����:  ���ݷ�����������ʾ��ѡ��ʽ�ķ�����Ϣ�����½���
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	HRESULT OnUpdateDualVideoFormat( WPARAM wparam, LPARAM lparam );
						
	/** ����:  ���ݷ��������յ������ʵķ�����Ϣ�����½���
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	HRESULT OnUpdateCallRate( WPARAM wparam, LPARAM lparam );
						
	/** ����:  ���ݷ�����������ʾ���ʵķ�����Ϣ�����½���
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	HRESULT OnUpdateDualCallRate( WPARAM wparam, LPARAM lparam );
						
	/** ����:  ���ݷ��������ջ������۵ķ�����Ϣ�����½���
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	HRESULT OnUpdateConfDis( WPARAM wparam, LPARAM lparam );
						
	/** ����:  ���ݷ��������ջ�����ѯ�ķ�����Ϣ�����½���
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	HRESULT OnUpdateConfPoll( WPARAM wparam, LPARAM lparam );
					
	/**	 
	* ����:  ����������ʼ��ٰ�ť��Ӧ����
	* @return  bool
	* @remarks  
	*/
	bool OnConfMinus( const IArgs& args );

	/**	 
	* ����:  �������������Ӱ�ť��Ӧ����
	* @return  bool
	* @remarks  
	*/
	bool OnConfAdd( const IArgs& args );			
	
	//����ʧȥ������ж��Ƿ�Ϊ64�ı���  ����WM_KILL_FOCUS��Ϣ
	bool OnConfRateNoFocus( const IArgs& args );
	
	bool OnShowRateNoFocus( const IArgs& args );

	bool RateIsDividedBy64();
	/**	 
	* ����:  �����ʾ���ʼ��ٰ�ť��Ӧ����
	* @return  bool
	* @remarks  
	*/
	bool OnShowMinus( const IArgs& args );

	/**	 
	* ����:  �����ʾ������Ӱ�ť��Ӧ����
	* @return  bool
	* @remarks  
	*/
	bool OnShowAdd( const IArgs& args );			

	/**	 
	* ����:  �����ѯ������ٰ�ť��Ӧ����
	* @return  bool
	* @remarks  
	*/
	bool OnPollMinus( const IArgs& args );

	/**	 
	* ����:  �����ѯ�����Ӱ�ť��Ӧ����
	* @return  bool
	* @remarks  
	*/
	bool OnPollAdd( const IArgs& args );			
											
	/** ����:  ������ѯ�İ�ť
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnBtnSwitchPolling( const IArgs& args );

	/**	 
	* ����:  ������ѯ������ť��Ӧ����
	* @return  bool
	* @remarks  
	*/
	bool OnBtnHoldEnd( const IArgs& args );

	/**	 
	* ����:  �����������ʳ�����ť��Ӧ����
	* @return  bool
	* @remarks  
	*/
	bool OnConfHoldEnd( const IArgs& args );

	/**	 
	* ����:  ������ʾ���ʳ�����ť��Ӧ����
	* @return  bool
	* @remarks  
	*/
	bool OnShowHoldEnd( const IArgs& args );
											
	/** ����:  �ı���ѯʱ��ؼ�ʱ����Ӧ����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnPollTimeChange( const IArgs& args );	
											
	/** ����:  �ı䵥�����ʿؼ�ʱ����Ӧ����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnConfRateChange( const IArgs& args );	

	/** ����:  �ı���ʾ���ʿؼ�ʱ����Ӧ����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnShowRateChange( const IArgs& args );	

	bool SaveConfRate();
	bool SaveShowRate();
	bool SaveVideoFormat();
	bool SaveDualVideoFormat();
	bool SaveConfDis();
	bool SaveConfPoll();
	bool SaveAudioFormat();
	
private:
	void SetCallServerMode();
	void SetCallServerShowMode();
	void SetAudioFormat();
private:
	static CCallServerCfgLogic *m_pLogic;
	TTPVidForamt m_tVidForamt;
	TTPVidForamt m_tDualVidForamt;
	EmTpAudioFormat m_emAudioFormat;
};

#endif // !defined(UMC_CALLSERVERCFGLOGIC_H)
