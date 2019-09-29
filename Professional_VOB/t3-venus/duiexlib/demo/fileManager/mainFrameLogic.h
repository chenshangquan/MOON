#pragma once
//#include "msghandler.h"

class CMainFrameLogic :
	public CMsgHandler,public ISingleTon<CMainFrameLogic>
{
public:
	CMainFrameLogic(  );
	~CMainFrameLogic(void);

	virtual LPCTSTR GetClassName(){ return _T("mainFrame");}
protected:
	//window msg handler
	void OnCancleClick(  TNotifyUI& tMsg );
	void OnTestClick(  TNotifyUI& tMsg );


	//business msg handler
	LRESULT OnMsgNotify( WPARAM wparam, LPARAM lparam );






DECLARE_MSG_MAP()
};

