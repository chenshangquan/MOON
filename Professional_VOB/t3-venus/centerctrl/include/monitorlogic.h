// monitorlogic.h: interface for the CMonitorLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MONITORLOGIC_H__5CE31678_BA7C_461F_8C94_834FFE89E3DA__INCLUDED_)
#define AFX_MONITORLOGIC_H__5CE31678_BA7C_461F_8C94_834FFE89E3DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WndLogicBase.h"

class CMonitorLogic : public CWndLogicBase
{
public:	
    virtual ~CMonitorLogic();
    
    static CMonitorLogic* GetLogicPtr();
    
public:  
    virtual bool RegCBFun();
    virtual void RegMsg(); 
    
    virtual bool InitWnd( const IArgs& args );
    
    virtual void Clear();  
    
protected:
    CMonitorLogic();

    bool OnBtnTv1Monitor( const IArgs& args );   
    bool OnBtnTv2Monitor( const IArgs& args );
    bool OnBtnTv3Monitor( const IArgs& args );

    bool OnBtnTv1Power( const IArgs& args );
    bool OnBtnTv2Power( const IArgs& args );
    bool OnBtnTv3Power( const IArgs& args );

    bool OnBtnNormalView( const IArgs& args );
    bool OnBtnMovieView( const IArgs& args );
    bool OnBtnUserView( const IArgs& args );
    bool OnBtnComputerView( const IArgs& args );

    bool OnBtnFullScreen( const IArgs& args );
    bool OnBtnPanoramic( const IArgs& args );
    bool OnBtnPointwise( const IArgs& args );
    bool OnBtnNormalDis( const IArgs& args );

    bool OnBtnHDMI1( const IArgs& args );
    bool OnBtnHDMI2( const IArgs& args );
    bool OnBtnHDMI3( const IArgs& args );
    bool OnBtnHDMI4( const IArgs& args );
    bool OnBtnYPbPr( const IArgs& args );
    bool OnBtnCVBS1( const IArgs& args );
    bool OnBtnCVBS2( const IArgs& args );
    bool OnBtnComputerSrc( const IArgs& args );
	

    HRESULT OnTvStateNty( WPARAM wparam, LPARAM lparam );
    HRESULT OnTvPowerInd( WPARAM wparam, LPARAM lparam );
    HRESULT OnSeleteTvInd( WPARAM wparam, LPARAM lparam );
    
private:
    static CMonitorLogic *m_pLogic;


    TCentreTVCfg          m_atTVCfg[MAX_CENTRETV_NUM];

    static const String m_strBtnTVSwitch1;
    static const String m_strBtnTVSwitch2;
    static const String m_strBtnTVSwitch3;
	static const String m_strBtnScreen1;
	static const String m_strBtnScreen2;
	static const String m_strBtnScreen3;
    static const String m_strStcMonitorTitle;
	u8 m_byIndex;  //记录被选中的电视机序号
};

#endif // !defined(AFX_MONITORLOGIC_H__5CE31678_BA7C_461F_8C94_834FFE89E3DA__INCLUDED_)
