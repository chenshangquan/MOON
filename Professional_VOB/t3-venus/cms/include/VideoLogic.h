// VideoLogic.h: interface for the CVideoLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIDEOLOGIC_H__CADB08C8_4F5E_4A84_8E0B_299DB7E039C0__INCLUDED_)
#define AFX_VIDEOLOGIC_H__CADB08C8_4F5E_4A84_8E0B_299DB7E039C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

#include "Decoder.h"
class CVideoLogic: public CWndLogicBase  
{

public: 
    static CVideoLogic* GetLogicPtr(); 
    CVideoLogic();
    virtual ~CVideoLogic(); 

public:  

    virtual bool RegCBFun();

    virtual bool UnRegFunc( );

    virtual bool InitWnd( const IArgs & arg );

    bool OnBtnRestoreVedioWnd( const IArgs & arg ); 

    bool OnBtnFullScreenVedio( const IArgs & arg );

    bool BtnHideVedio( const IArgs & arg );
    
    bool OnBtnDBLCLKVedioWnd( const IArgs & arg );

    void AskKeyFrame( BOOL32 bForce );

    void SetDecVol( u8 abyVol );

    u8 GetDecVol();

    /**	 
    * 功能:  清空所有状态和数据
    * @return   
    * @remarks	 
    */
    virtual void Clear();
 
protected: 
    virtual void RegMsg(); 
    virtual void UnRegMsg();

    HRESULT OnShowVideo( WPARAM wparam, LPARAM lparam); 
    HRESULT OnHideVedioNotify( WPARAM wparam, LPARAM lparam); 

    HRESULT OnStartRsp( WPARAM wparam, LPARAM lparam); 

    HRESULT OnDualRecvStateNotify( WPARAM wparam, LPARAM lparam); 
    HRESULT OnHungupConf( WPARAM wparam, LPARAM lparam); 
    HRESULT OnConfStateNotify( WPARAM wparam, LPARAM lparam);
    void StopRcvVedio();
    void ShowVideoByVersion(String SchemeType);
private:
    //开始/停止 观看双流演示
    void PlayDual();

    void InitParam();

    void RestoreVedioWnd(  );

private:
    CDecoder  m_cDecoder;
    TTPCnMediaTransPort		m_tVedioIpTransAddr;
    TTPCnMediaTransPort		m_tAudioIpTransAddr;

    
    static CVideoLogic *m_pLogic;

    static String m_wndVedio;     //用于显示vedio的wnd

    static String m_strSchmFullScreen;  //全屏方案
    static String m_strSchmRestoreScreen;  //小窗口方案
    static String m_strSchmHideScreen;  //隐藏方案

     

    BOOL32 m_bRecvStream;
    BOOL32 m_bDecod;

	BOOL32 m_bFullScreen;
};

#endif // !defined(AFX_VIDEOLOGIC_H__CADB08C8_4F5E_4A84_8E0B_299DB7E039C0__INCLUDED_)
