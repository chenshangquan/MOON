// userDefinedLogic.h: interface for the CUserDefinedLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USERDEFINEDLOGIC_H__178F8700_0811_417F_BB2D_E1FE182EACC1__INCLUDED_)
#define AFX_USERDEFINEDLOGIC_H__178F8700_0811_417F_BB2D_E1FE182EACC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"
enum EmConfigType{
    emConfigNon,
    emConfigSysName,
    emConfigSysTime,
    emConfigScreenPswd,
    emConfigFuncLst
};
class CUserDefinedLogic : public CWndLogicBase  
{
public: 
    static CUserDefinedLogic* GetLogicPtr(); 
    CUserDefinedLogic();
    virtual ~CUserDefinedLogic(); 
    
public:  
    
    virtual bool RegCBFun();
    
    virtual bool UnRegFunc( );
    
    virtual bool InitWnd( const IArgs & arg );
    /**	 
	* 功能:  清空所有状态和数据
	* @return   
	* @remarks	 
	*/
    virtual void Clear() ;

    bool BtnSaveToFileClick( const IArgs & arg );
    
    
    //点击自定义列表条目
    bool OnDefinedItemClick( const IArgs & arg );


    //点击功能列表条目
    bool OnFuncLstItemClick( const IArgs & arg );
    

    bool OnDefinedItemIconClick( const IArgs & arg );

    //点击转到自定义界面
    bool BtnToUserDefinedClick( const IArgs & arg );
    

    //点击了保存按钮
    bool BtnSaveClick( const IArgs & arg );
   

    //点击了取消按钮
    bool BtnCancleClick( const IArgs & arg );


    //开始编辑系统时间
    bool BeginEditSysTime( const IArgs & arg );


    //hour Add
    bool BtnAddHourClick( const IArgs & arg );


    //DeleteHour
    bool BtnDeleteHourClick( const IArgs & arg );


    //min Add
    bool BtnAddMinClick( const IArgs & arg );
    
    
    //min delete
    bool BtnDeleteMinClick( const IArgs & arg );


    //点击日历
    bool BtnCalendarClick( const IArgs & arg );

	bool OnCalendarDateChange( const IArgs & args );

    //点击时间同步
    bool  BtnSyncTimeToServClick( const IArgs & arg );


    bool  EdtMinOnChar( const IArgs & arg );
    
    bool  EdtHourOnChar( const IArgs & arg );


    u16   SyncTimeToServ( const SYSTEMTIME sysTime  );

    void UpdateFuncList();

    void SetFuncLstOffset( int nOffset = 0);
    void SetFuncLstSel( int nIndex = -1 );
protected: 
    
    HRESULT OnUpdateSysTime( WPARAM wparam, LPARAM lparam); 
    
    void SaveSysNameDlg( BOOL32 bSave = TRUE );  //保存系统名称信息
    void SaveScreenPswdDlg( BOOL32 bSave = TRUE ); //保存锁屏密码信息
    void SaveSysTimeDlg( BOOL32 bSave = TRUE );    //保存系统时间信息
    void SaveFuncLstDlg( BOOL32 bSave = TRUE );  //保存功能列表

    void  InitUserDefinedLst();
    
    void  ShowSubDlg( String StrDlgName );
    
 
    virtual void RegMsg(); 
    virtual void UnRegMsg();
    
    //是否可以更新，如果当前正处在编辑状态则不更新，否则就更新
    BOOL32 IsCouldUpdate();

    void UpdateSysTime();

    bool BtnSwitchClick( const IArgs& args );

    void InitFuncLst();
    void SetMenuLst( vector<TConfMenuInfo> *pLst );
private:
    
    BOOL32             m_bCouldUpdateTime;
    EmConfigType        m_emConfigType;          //当前是哪个配置界面
    static CUserDefinedLogic *m_pLogic;

    const static String m_stcStrLstUserDefined;   //自定义列表
    
    const static String  m_stcStrDlgSysName ;   //系统名定义界面
    const static String  m_stcStrEdtSysName  ;   //系统名
    
    const static String  m_stcStrDlgScreenPswd ;   //锁屏密码设置界面
    const static String  m_stcStrEdtScreenPswd ;   //锁屏密码
    const static String  m_stcStrSwitchBtnScreenPswd ;   //锁屏 
    
    const static String  m_stcStrDlgSysTime ;   //系统时间设置界面
    const static String  m_stcStrEdtDate ;         //系统日期
    const static String  m_stcStrEdtHour  ;         //系统时
    const static String  m_stcStrEdtMin  ;           //系统分
    const static String  m_stcStrBtnCalender;

    const static String  m_stcStrLstFunc;


    //自定义菜单项
    const static String m_stcStrSysName;
    const static String m_stcStrSysTime;
    const static String m_stcStrScreenPswd;
    const static String m_stcStrFuncLst;


    //方案
    const static String m_SchmUserDefined;       //显示自定义界面方案
    const static String m_SchmSysName;           //显示设置系统名界面方案
    const static String m_SchmScreenPswd;        //显示设置锁屏密码界面方案
    const static String m_SchmSysTime;            //显示系统是时间界面方案
    const static String m_SchmFuncLst;            //显示系统功能列表方案

   
   vector<TConfMenuInfo> m_vctTConfMenu;
   

};

#endif // !defined(AFX_USERDEFINEDLOGIC_H__178F8700_0811_417F_BB2D_E1FE182EACC1__INCLUDED_)
