// centCfgDisplayDlg.h: interface for the CCentCfgDisplayDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CENTCFGDISPLAYDLG_H__A5904C57_8B69_4078_9C21_1F98E93477C9__INCLUDED_)
#define AFX_CENTCFGDISPLAYDLG_H__A5904C57_8B69_4078_9C21_1F98E93477C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CCentCfgDisplayDlg : public CLogicBase, public ISingleTon<CCentCfgDisplayDlg>      
{
public:
	CCentCfgDisplayDlg();
	virtual ~CCentCfgDisplayDlg();

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
    virtual void Clear();

	/** ����:  �ж��п���ʾ���������Ϣ�Ƿ�ı�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	bool IsCentCfgDisplayChange();

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
	/** ����:  ����NAT���õİ�ť
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	bool OnBtnSwitchTVWALL( const IArgs& args );

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
						
	/** ����:  �ı���ʾ��1�ն��ź�ʱ����Ӧ����	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnTerminalOut1Change( const IArgs& args );	
							
	/** ����:  �ı���ʾ��1����ǽ�ź�ʱ����Ӧ����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnTVWALLOut1Change( const IArgs& args );	
							
	/** ����:  �ı���ʾ��3�ն��ź�ʱ����Ӧ����	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnTerminalOut3Change( const IArgs& args );	
							
	/** ����:  �ı���ʾ��3����ǽ�ź�ʱ����Ӧ����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnTVWALLOut3Change( const IArgs& args );	
	
	/** ����:  �յ�����״̬����Ϣ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	LRESULT OnConfStateNty( WPARAM wparam, LPARAM lparam);

	/** ����:  ���շ������˷���������ϢȻ���пص���ǽ״̬
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnUpdateDisplayInfo( WPARAM wParam, LPARAM lParam );
	
	void SetDisplayInfo();
	
	/** ����:  ��ȡ�ź�Դ״̬
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	EmTVInputSelect GetDisplayType( String strCtrl );

	/** ����:  �����ź�Դ״̬
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	string TransDisplayType( EmTVInputSelect emType );

	/** ����:  ��������Ŀ���״̬ת��Ϊstring����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	//String CamStateToString( EmCamPowerMode& emSwitchState );

	/** ����:  ���շ������˷���������ϢȻ������ĵ������״̬
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	//LRESULT OnDocCamInfoNty( WPARAM wParam, LPARAM lParam );

private:
	vector<CString> m_vecOut;			//�ź�Դ
	const String m_strTerminalOut1;					
	const String m_strTVWALLOut1;
	const String m_strTerminalOut3;					
	const String m_strTVWALLOut3;	
};

#endif // !defined(AFX_CENTCFGDISPLAYDLG_H__A5904C57_8B69_4078_9C21_1F98E93477C9__INCLUDED_)
