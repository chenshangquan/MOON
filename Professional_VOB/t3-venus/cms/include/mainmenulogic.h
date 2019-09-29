// mainmenulogic.h: interface for the CMainMenuLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINMENULOGIC_H__4B76AF6A_BAE2_4235_8AAE_75757E550A2F__INCLUDED_)
#define AFX_MAINMENULOGIC_H__4B76AF6A_BAE2_4235_8AAE_75757E550A2F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CMainMenuLogic : public CWndLogicBase  
{
public:
	CMainMenuLogic();
	virtual ~CMainMenuLogic();
	static CMainMenuLogic* GetLogicPtr();
 
public:  
	virtual bool RegCBFun();
	
	virtual bool UnRegFunc();
	
    virtual bool InitWnd( const IArgs& args );

    virtual void Clear();

	bool OnBtnPrePage( const IArgs& args );
	bool OnBtnNextPage( const IArgs& args );

	bool OnBtnCnsCtrlClick( const IArgs& args );

	bool OnBtnAudMixClick( const IArgs& args );
	
	bool OnBtnPIPClick( const IArgs& args );

	bool OnBtnTvwClick( const IArgs& args );

	bool OnBtnAddrbookClick( const IArgs& args );

	bool OnBtnCnsMic( const IArgs& args );

	bool OnBtnCnsSpeaker( const IArgs& args );

	bool OnBtnCnsPoll( const IArgs& args );

	bool OnBtnLocalCnsMute( const IArgs& args );

	bool OnBtnLocalCnsQuite( const IArgs& args );

	bool OnBtnLocalCnsDual( const IArgs& args );

	bool OnBtnDualSrc( const IArgs& args );

	bool OnListOffsetNotify( const IArgs & args );

    void TimeProtect();

protected: 
	
	virtual void RegMsg(); 
	virtual void UnRegMsg();

	void UpdateConfMenu();
	void UpdatePageBtn();

    HRESULT OnCnsPollRsp( WPARAM wparam, LPARAM lparam );
	HRESULT OnCnsPollStateNty( WPARAM wparam, LPARAM lparam );
	HRESULT OnCnsDualRsp( WPARAM wparam, LPARAM lparam );
	HRESULT OnCnsDualNotify( WPARAM wparam, LPARAM lparam );
	HRESULT OnCnsQuiteMuteRsp( WPARAM wparam, LPARAM lparam );
	HRESULT OnUpdateConfMenu( WPARAM wparam, LPARAM lparam );
    HRESULT OnConfStateNotify( WPARAM wparam, LPARAM lparam );
	HRESULT OnViewLocalPIPRsp( WPARAM wparam, LPARAM lparam );
	HRESULT OnViewLocalPIPStateNty( WPARAM wparam, LPARAM lparam );
	HRESULT RefreshAudMixState( WPARAM wparam, LPARAM lparam );
private:	
    static CMainMenuLogic *m_pLogic;

    BOOL   m_bOptProtect; //²Ù×÷±£»¤

	static const String  m_strDlgConfManageMenu;
	static const String  m_strBtnPrePage;
	static const String  m_strBtnNextPage;
	static const String  m_strConfManageList;
};

#endif // !defined(AFX_MAINMENULOGIC_H__4B76AF6A_BAE2_4235_8AAE_75757E550A2F__INCLUDED_)
