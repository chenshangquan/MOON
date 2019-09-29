// cfgCallSerLogic.h: interface for the CCfgCallSerLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CFGCALLSERLOGIC_H__8B0F0488_400D_4306_A6D1_ACE682E941FE__INCLUDED_)
#define AFX_CFGCALLSERLOGIC_H__8B0F0488_400D_4306_A6D1_ACE682E941FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CCfgCallSerLogic : public CLogicBase, public ISingleTon<CCfgCallSerLogic>  
{
public:
	CCfgCallSerLogic();
	virtual ~CCfgCallSerLogic();
	
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
	bool IsCfgCallChange();

	/** ����:  �л�����������ʱ�����Ƿ񱣴�Ĵ���	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveMsgBox();

	/**	 
	* ����: ��ȡ���������ݱ仯�ؼ�����Ŀ
	* @return   bool
	* @remarks  
	*/
	//s32 GetCtrlChangeNum() { return m_vctWndName.size(); }
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
				
	/** ����:  �ı������ʾ��ʽ�ؼ�ʱ����Ӧ����	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnShowModeChange( const IArgs& args );	
						
	/** ����:  �ı���л����ʽ�ؼ�ʱ����Ӧ����	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnCallModeChange( const IArgs& args );	
																
	/** ����:  ��ȡ�û�ѡ��ĺ��л����ʽ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	void GetCallMode( TTPVidForamt& tVidForamt )const;

	/** ����:  ��ȡѡ�и�ʽ�ķֱ��ʺ�֡��
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	TTPVidForamt GetMode( String strMode )const;
											
	/** ����:  ��ȡ�û�ѡ��ĺ�����ʾ��ʽ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	void GetShowMode( TTPVidForamt& tVidForamt )const;
											
	/** ����:  �������۵İ�ť
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnBtnSwitchDiscuss( const IArgs& args );	
											
	/** ����:  ������ѯ�İ�ť
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnBtnSwitchPolling( const IArgs& args );	
											
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

	bool OnConfRateNoFocus( const IArgs& args );

	bool OnShowRateNoFocus( const IArgs& args );

	bool OnAudioModeChange( const IArgs& args );

	/** ����:  �ı���ʾ���ʿؼ�ʱ����Ӧ����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnShowRateChange( const IArgs& args );	
						
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
						
	/** ����:  ������ѡ��ʽ��Ϣ
	*  @param[in] strControl  �ؼ�����
	*  @return 
	*  @remarks   
	*/	
	void SetFormat( TTPVidForamt& tVidForamt, String strControl );
						
	/** ����:  ���û�����ѡ��ʽ��Ϣ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void SetVideoFormat();							
	/** ����:  ������ʾ��ѡ��ʽ��Ϣ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void SetDualVideoFormat();
						
	/** ����:  ���õ���������Ϣ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void SetCallRate();							
	/** ����:  ������ʾ������Ϣ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void SetDualCallRate();
						
	/** ����:  ���û���������Ϣ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void SetConfDisState();							
	/** ����:  ���û�����ѯ��Ϣ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void SetConfPollInfo();

	/** ����:  �յ�����״̬����Ϣ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	HRESULT OnConfStateNty( WPARAM wparam, LPARAM lparam);
						
	/** ����:  ���ݷ�����������Ƶ��ʽ�ķ�����Ϣ�����½���
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	HRESULT OnUpdateAudioFormat( WPARAM wparam, LPARAM lparam );						
	/** ����:  ������Ƶ��ʽ��Ϣ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void SetAudioFormat();

	EmTpAudioFormat GetAudioFormat();

private:
	vector<CString> m_vecCallModeData;			//�����ʽ
	vector<CString> m_vecShowModeData;			//��ʾ��ʽ
	vector<CString> m_vecConfRateData;			//��������
	vector<CString> m_vecShowRateData;			//��ʾ����
	vector<CString> m_vecAudioRateData;			//��Ƶ��ʽ
	const String m_strCallMode;					//��᳡���л����ʽ
	const String m_strShowMode;					//��᳡������ʾ��ʽ
};

#endif // !defined(AFX_CFGCALLSERLOGIC_H__8B0F0488_400D_4306_A6D1_ACE682E941FE__INCLUDED_)
