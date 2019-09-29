// loginLogic.h: interface for the CLoginLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGINLOGIC_H__F2021CA2_9B1C_47DE_9614_7E1EC7FDCAA8__INCLUDED_)
#define AFX_LOGINLOGIC_H__F2021CA2_9B1C_47DE_9614_7E1EC7FDCAA8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CLoginLogic : public CWndLogicBase 
{
public:  
 	static CLoginLogic* GetLogicPtr(); 
    CLoginLogic();
	virtual ~CLoginLogic();
public:  
	
	virtual bool RegCBFun();
	
	virtual bool UnRegFunc( );
	
    virtual bool InitWnd( const IArgs & arg );

   /**	 
	* ����:  �������״̬������
	* @return   
	* @remarks	 
	*/
    virtual void Clear();

	/**	 
	* ����:  ��¼
	* @return   
	* @remarks   
	*/
	bool Login( const IArgs & arg );

    /**	 
	* ����:  ����IP
	* @return   
	* @remarks   
	*/
	bool BtnSetIP( const IArgs & arg );


	/**	 
	* ����:  �˳�
	* @return   
	* @remarks   
	*/
	bool  Exit( const IArgs & arg );

	/**	 
	* ����: �ػ�button
	* @return   bool
	* @remarks  
	*/
	bool BtnPowerOff( const IArgs & arg );

	bool BtnBackLogin( const IArgs & arg );

	bool BtnSaveToFileClick( const IArgs & arg );


	//����ϵͳ�����ļ���
	//note�����û��Զ������ʹ�� 
	void SaveSysNameToFile( String strSysName );

protected: 
	
	HRESULT OnConnectRep( WPARAM wparam, LPARAM lparam);
	HRESULT OnCnsLoginTimeOut( WPARAM wparam, LPARAM lparam);
	HRESULT OnUmsLoginTimeOut( WPARAM wparam, LPARAM lparam);
	HRESULT OnDisConnect( WPARAM wparam, LPARAM lparam );
	HRESULT OnCnListNotify( WPARAM wparam, LPARAM lparam );
		
protected: 
	virtual void RegMsg(); 
	virtual void UnRegMsg();
	
private:

    static CLoginLogic *m_pLogic;

	BOOL   m_bAutoLogin;
	enum EM_AutoLoginState{
		emNotLogin,
		emReceiveLoginRsp,
		emReceiveCnList, 
		emLogin,
	};
	EM_AutoLoginState    m_emAutoLoginState; 
	
    static const String  m_strDlgLoginFrame;
	static const String  m_strIpServIP;
    static const String  m_strEdtUserName;
	static const String  m_strEdtPswd;
	static const String  m_strBtnLogin; 
	static const String  m_strBtnPower; 
    static const String  m_strStcSysName;
    static const String  m_strSwtchBtnMemPswd;    ///<�Ƿ���û�����
	static const String  m_strSwtchBtnAutoLog;

};

#endif // !defined(AFX_LOGINLOGIC_H__F2021CA2_9B1C_47DE_9614_7E1EC7FDCAA8__INCLUDED_)
