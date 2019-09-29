// mainmenulogic.h: interface for the CMainMenuLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINMENULOGIC_H__AE60AA16_3E9D_4041_9DAE_45EE6EC8E14F__INCLUDED_)
#define AFX_MAINMENULOGIC_H__AE60AA16_3E9D_4041_9DAE_45EE6EC8E14F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WndLogicBase.h"

class CMainMenuLogic : public CWndLogicBase
{
public:	
	virtual ~CMainMenuLogic();
    
    static CMainMenuLogic* GetLogicPtr();
    
public:  
    virtual bool RegCBFun();
    virtual void RegMsg(); 
    
    virtual bool InitWnd( const IArgs& args );
    
    virtual void Clear();  
    
protected:
    CMainMenuLogic();

    bool OnClickAirCondition( const IArgs& args );

    bool OnClickCamera( const IArgs& args );

    bool OnClickMonitor( const IArgs& args );

    bool OnClickTouchPad( const IArgs& args );

	bool OnClickCurtainCfg( const IArgs& args );

    bool OnBtnToCnc( const IArgs& args );

    bool OnBtnMinimize( const IArgs& args );

    bool OnBtnExit( const IArgs& args );
    
private:
	static CMainMenuLogic *m_pLogic;

	static const String m_strBtnTouchPad;
	static const String	m_strBtnMonitor;
	static const String m_strBtnCamera;
	static const String m_strBtnCurtainCfg;
};

#endif // !defined(AFX_MAINMENULOGIC_H__AE60AA16_3E9D_4041_9DAE_45EE6EC8E14F__INCLUDED_)
