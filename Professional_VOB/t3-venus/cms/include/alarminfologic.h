// alarminfologic.h: interface for the CAlarmInfoLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALARMINFOLOGIC_H__5C4750CE_64C3_4E15_A250_D55E58734A73__INCLUDED_)
#define AFX_ALARMINFOLOGIC_H__5C4750CE_64C3_4E15_A250_D55E58734A73__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"


#define ShowPopMsg(p)\
{\
    CAlarmInfoLogic::GetLogicPtr()->AddMsg(p);\
}

#define ShowPopMsgNow(p)\
{\
    CAlarmInfoLogic::GetLogicPtr()->AddMsg(p, TRUE);\
}

class CAlarmInfoLogic : public CWndLogicBase
{
public:
	CAlarmInfoLogic();
	virtual ~CAlarmInfoLogic();

    static CAlarmInfoLogic* GetLogicPtr(); 

public:  
	virtual bool RegCBFun();
	virtual bool UnRegFunc();
	virtual void RegMsg();
	
    /**	 
	* 功能:  清空所有状态和数据
	* @return   
	* @remarks	 
	*/
    virtual void Clear();

	void AddMsg( CString strMsg, BOOL bShowNow = FALSE );

    vector<String>& GetAlarmMsgLst(){ return m_vctAlarm; }
protected:		
	bool InitWnd( const IArgs & args );	

	bool OnHideDlg( const IArgs & args );

	void ShowPosByVersion();

    HRESULT  OnConnectOk( WPARAM wprame, LPARAM lparam );

private:
	static CAlarmInfoLogic *m_pLogic;

	vector<String> m_vctAlarm;

	BOOL m_bLoginOK;
};

#endif // !defined(AFX_ALARMINFOLOGIC_H__5C4750CE_64C3_4E15_A250_D55E58734A73__INCLUDED_)
