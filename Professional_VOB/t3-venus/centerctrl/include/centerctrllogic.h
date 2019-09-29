// centerctrllogic.h: interface for the CCenterCtrlLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CENTERCTRLLOGIC_H__E20B43DB_AA08_4693_BD17_CFDB11DC9F56__INCLUDED_)
#define AFX_CENTERCTRLLOGIC_H__E20B43DB_AA08_4693_BD17_CFDB11DC9F56__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WndLogicBase.h"

class CCenterCtrlLogic : public CWndLogicBase  
{
public:
	virtual ~CCenterCtrlLogic();

    static CCenterCtrlLogic* GetLogicPtr();

public:  
    virtual bool RegCBFun();
    virtual bool UnRegFunc( );
    virtual void RegMsg(); 
    virtual void UnRegMsg();
    
    virtual bool InitWnd( const IArgs& args );
    
    virtual void Clear() ;  

protected:
    CCenterCtrlLogic();

    void CreateWnd();

    HRESULT OnConnectRsp( WPARAM wparam, LPARAM lparam );
    HRESULT OnDisConnect( WPARAM wparam, LPARAM lparam );

private:
	static CCenterCtrlLogic *m_pLogic;

};

#endif // !defined(AFX_CENTERCTRLLOGIC_H__E20B43DB_AA08_4693_BD17_CFDB11DC9F56__INCLUDED_)
