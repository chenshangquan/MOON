// titleBarLogic.h: interface for the CTitleBarLogic class.
 /*****************************************************************************
 模块名      : CMS控制台
 文件名      : titleBarLogic.h
 相关文件    : 
 文件实现功能: 主界面上的标题
 说明       ： 会议中实时更会议时间 和本地cns的静音 哑音 双流 状态
 作者        : 俞锦锦
 版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
 -----------------------------------------------------------------------------
 修改记录:
 日  期         版本        修改人      修改内容
 2011/5/24  1.0          俞锦锦      创建
******************************************************************************/

#if !defined(AFX_TITLEBARLOGIC_H__05CDA343_9A18_4A1D_9F89_D9F3349926D9__INCLUDED_)
#define AFX_TITLEBARLOGIC_H__05CDA343_9A18_4A1D_9F89_D9F3349926D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CTitleBarLogic : public CWndLogicBase  
{
public: 
    static CTitleBarLogic* GetLogicPtr(); 
    CTitleBarLogic();
    virtual ~CTitleBarLogic(); 
    
public:  
    
    virtual bool RegCBFun();
    
    virtual bool UnRegFunc( );
    
    virtual bool InitWnd( const IArgs & arg );
    
    virtual bool ShowWindow( BOOL32 bShow );
    /**	 
	* 功能:  清空所有状态和数据
	* @return   
	* @remarks	 
	*/
    virtual void Clear();

    bool BtnSaveToFileClick( const IArgs & arg );
    
    void UpdateSysTime();//更新系统时间
    void UpdateConfTime();//更新会议持续时间
protected:  
    
    HRESULT OnCnsInfoNotify( WPARAM wparam, LPARAM lparam );
    HRESULT OnVoiceNotify( WPARAM wparam, LPARAM lparam); 
    HRESULT OnDualNotify( WPARAM wparam, LPARAM lparam); 

    HRESULT OnConfStateNotify( WPARAM wparam, LPARAM lparam); 
    HRESULT OnChangeSpeakerNotify( WPARAM wparam, LPARAM lparam); 
    
    HRESULT OnModifySysTimeNotify( WPARAM wparam, LPARAM lparam); 
    
    void  AdjustTime( s64 &time );
protected: 
    virtual void RegMsg(); 
    virtual void UnRegMsg();
    
private:
    void Init();
    void UnInit();

private:
    
    static CTitleBarLogic *m_pLogic;
    static const String m_stcStrCnsName;
    static const String m_stcStrMuteIcon;  //哑音图标
    static const String m_stcStrQuietIcon; //静音图标
    static const String m_stcStrDualIcon;  //双流图标
    static const String m_stcStrSpeakerIcon;//发言人图标

    static const String m_stcStrDate;      //系统日期
    static const String m_stcStrTime;      //系统时间 

    static const String m_stcStrConfTime;  //会议持续时间


    s64   m_dwConfStartTime;                //会议的开始时间   
    
    s16   m_nElapse;                       //timer间隔
    TCMSConf m_tCurConf;
    CTimeSpan  m_tmConfDuration;                   //当前会议持续时长
};

#endif // !defined(AFX_TITLEBARLOGIC_H__05CDA343_9A18_4A1D_9F89_D9F3349926D9__INCLUDED_)
