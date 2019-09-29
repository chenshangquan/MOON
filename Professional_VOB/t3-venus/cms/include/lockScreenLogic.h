// lockScreenLogic.h: interface for the CLockScreenLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOCKSCREENLOGIC_H__E9D7E6B7_60D9_40C4_8312_618B9FF42939__INCLUDED_)
#define AFX_LOCKSCREENLOGIC_H__E9D7E6B7_60D9_40C4_8312_618B9FF42939__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "wndLogicBase.h"

class CLockScreenLogic : public CWndLogicBase 
{
public:
	static CLockScreenLogic* GetLogicPtr(); 
	CLockScreenLogic();
	virtual ~CLockScreenLogic(); 
  
public:  
	virtual bool RegCBFun();
	
	virtual bool UnRegFunc( );
	
    virtual bool InitWnd( const IArgs & arg );

    /**	 
	* 功能:  清空所有状态和数据
	* @return   
	* @remarks	 
	*/
    virtual void Clear();

	bool OnEndLock( const IArgs & arg );	

	bool OnBtnOkClick( const IArgs & arg );
	
	bool OnBtnCancleClick( const IArgs & arg );

	bool OnBtnClickEdit( const IArgs & arg );

protected: 
	
	//afx_msg HRESULT OnConnectRep( WPARAM wparam, LPARAM lparam);*/
		
protected: 
	virtual void RegMsg(); 
	virtual void UnRegMsg();
	
private:	
    static CLockScreenLogic *m_pLogic;

	TLockScreenInfo  m_tLockInfo;

	static const String	m_strScreenPswDlg;
	static const String m_strEdtPswd;
	static const String m_strStcErrMsg;
};

#endif // !defined(AFX_LOCKSCREENLOGIC_H__E9D7E6B7_60D9_40C4_8312_618B9FF42939__INCLUDED_)
