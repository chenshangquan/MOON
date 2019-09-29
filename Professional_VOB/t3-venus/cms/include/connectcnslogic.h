// connectcnslogic.h: interface for the CConnectCnsLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONNECTCNSLOGIC_H__1BA7A180_4F02_4105_AA36_F58C5CD17BB3__INCLUDED_)
#define AFX_CONNECTCNSLOGIC_H__1BA7A180_4F02_4105_AA36_F58C5CD17BB3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

#define MAX_PAGE    5

class CConnectCnsLogic : public CWndLogicBase  
{
public:
	CConnectCnsLogic();
	virtual ~CConnectCnsLogic();
	static CConnectCnsLogic* GetLogicPtr();

public:
	virtual bool RegCBFun();
	virtual bool UnRegFunc();
	virtual void RegMsg();
	virtual void UnRegMsg();
	
    /**	 
	* 功能:  清空所有状态和数据
	* @return    
	*/
    virtual void Clear();

	bool InitWnd( const IArgs & args );

	bool OnClickCnItem( const IArgs & args );

	bool OnListOffsetNotify( const IArgs & args );

protected:
	HRESULT OnCnListNotify( WPARAM wparam, LPARAM lparam );
	HRESULT OnConnectCnsInsRsp( WPARAM wparam, LPARAM lparam );
	HRESULT OnAutoLogCnsIns( WPARAM wparam, LPARAM lparam );

	void UpdateRadioButton();

private:	
    static CConnectCnsLogic *m_pLogic;
	TTPCnList  m_tCnList;
	int        m_nPage;

	static const String m_strListCns;
	static String  m_strScheme[MAX_PAGE];
	static String  m_strRadioBtn[MAX_PAGE];
	static const String m_strStcLastCns;
};

#endif // !defined(AFX_CONNECTCNSLOGIC_H__1BA7A180_4F02_4105_AA36_F58C5CD17BB3__INCLUDED_)
