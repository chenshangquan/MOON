// touchpadlogic.h: interface for the CTouchPadLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOUCHPADLOGIC_H__336DBFA6_6A26_4CD9_A0A8_9F259B265051__INCLUDED_)
#define AFX_TOUCHPADLOGIC_H__336DBFA6_6A26_4CD9_A0A8_9F259B265051__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WndLogicBase.h"

class CTouchPadLogic : public CWndLogicBase
{
public:	
    virtual ~CTouchPadLogic();
    
    static CTouchPadLogic* GetLogicPtr();
    
public:  
    virtual bool RegCBFun();
    virtual void RegMsg(); 
    
    virtual bool InitWnd( const IArgs& args );
    
    virtual void Clear();  

    void UpdateWaitingImg();
    void EndWaiting();
    
protected:
    CTouchPadLogic();

    bool OnBtnSysSwitch( const IArgs& args );
    bool OnBtnAllLight( const IArgs& args );
    bool OnBtnMainLight( const IArgs& args );
    bool OnBtnAuxiLight( const IArgs& args );
	bool OnBtnCancle( const IArgs& args );
	bool OnBtnCurtainUp( const IArgs& args );
	bool OnBtnCurtainDown( const IArgs& args );
    
    void UpdateTempImg( u16 wTemp );

    HRESULT OnSchStateNty( WPARAM wparam, LPARAM lparam );
    HRESULT OnSchPowerInd( WPARAM wParam, LPARAM lParam );
    HRESULT OnSchAllLightInd( WPARAM wParam, LPARAM lParam );
    HRESULT OnSchMidLightInd( WPARAM wParam, LPARAM lParam );
    HRESULT OnSchScrLightInd( WPARAM wParam, LPARAM lParam );
	HRESULT OnCurtainStateNty( WPARAM wparam, LPARAM lparam );
        
    HRESULT OnSchTempNty( WPARAM wparam, LPARAM lparam );
private:
    static CTouchPadLogic *m_pLogic;

    BOOL         m_bPowerOn;
    BOOL         m_bLightOn;  
    BOOL         m_bMainLightOn;
    BOOL         m_bAuxiLightOn;
	BOOL         m_bCurtainLogicExist;       //窗帘界面是否存在
	BOOL         m_bIsCheck[MAX_CURTAIN_NUM];//窗帘选中数组
	BOOL         m_bOff;                     //是否为关闭 关闭时主动跟cns断链

    int          m_nUpdateTime;
    int          m_nWaitTime;
    Em_ImgSchm   m_emImgSchm;

    static const String m_stcUpdateImg;
    static const String m_shmImg1;
    static const String m_shmImg2;
    static const String m_shmImg3;
	static const String m_shmImg4;
	static const String m_stcWaitingDlg;

    u16    m_wLocalTemp;    //当前温度
	u8     m_nCurNum;       //底层通知过来的窗帘数目
};

#endif // !defined(AFX_TOUCHPADLOGIC_H__336DBFA6_6A26_4CD9_A0A8_9F259B265051__INCLUDED_)
