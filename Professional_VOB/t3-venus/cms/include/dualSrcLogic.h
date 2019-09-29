// dualSrcLogic.h: interface for the CDualSrcLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DUALSRCLOGIC_H__7F3C8288_922F_4478_B372_A8CDE4E61BA3__INCLUDED_)
#define AFX_DUALSRCLOGIC_H__7F3C8288_922F_4478_B372_A8CDE4E61BA3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "wndLogicBase.h"
class CDualSrcLogic: public CWndLogicBase    
{
public:
	CDualSrcLogic();
	virtual ~CDualSrcLogic();
 
 
	static CDualSrcLogic* GetLogicPtr();

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

    bool OnCnsLstItem( const IArgs & args );
protected:

    LRESULT OnVgaInfoNotify( WPARAM wParam, LPARAM lParam );

    LRESULT OnSelDualPortInd( WPARAM wParam, LPARAM lParam );
 
private:	
    static CDualSrcLogic *m_pLogic;

    TDualSrcInfo  m_tDualSrcInfo;
};

#endif // !defined(AFX_DUALSRCLOGIC_H__7F3C8288_922F_4478_B372_A8CDE4E61BA3__INCLUDED_)
