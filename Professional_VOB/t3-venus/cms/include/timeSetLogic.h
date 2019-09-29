// userDefinedLogic.h: interface for the CUserDefinedLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TIMESETLOGIC_H__178F8700_0811_417F_BB2D_E1FE182EACC1__INCLUDED_)
#define AFX_TIMESETLOGIC_H__178F8700_0811_417F_BB2D_E1FE182EACC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

enum EmFocusItem  //当前有焦点的项
{
    em_Focus_Hour,
    em_Focus_Min,
    em_Focus_Sec,
};


class CTimeSetLogic : public CWndLogicBase  
{
public: 
    static CTimeSetLogic* GetLogicPtr(); 
    CTimeSetLogic();
    virtual ~CTimeSetLogic(); 
    
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
    
    bool OnSysCfg( const IArgs& args );

    //点击了保存按钮
    bool BtnSaveClick( const IArgs & arg );
   

    //点击了取消按钮
    bool BtnCancleClick( const IArgs & arg );


    //开始编辑系统时间
    bool BeginEditSysTime( const IArgs & arg );

    //  Add
    bool BtnAddClick( const IArgs & arg );
    
    
    //  delete
    bool BtnMinusClick( const IArgs & arg );    


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

    bool  FocusOnSec( const IArgs & arg );

    bool  FocusOnMin( const IArgs & arg );
    
    bool  FocusOnHour( const IArgs & arg );
    
    //limit the time number
    bool EditTimeSetLimit ( const IArgs& arg );

    u16   SyncTimeToServ( const SYSTEMTIME sysTime  );
  
protected: 
    
    HRESULT OnUpdateSysTime( WPARAM wparam, LPARAM lparam); 

    bool OnBtnHoldEnd( const IArgs & arg ); 

    //bool OnMinusBtnHoldEnd( const IArgs & arg ); 
     
    void SaveSysTimeDlg( BOOL32 bSave = TRUE );    //保存系统时间信息 
 
 
    virtual void RegMsg(); 
    virtual void UnRegMsg();
    
    //是否可以更新，如果当前正处在编辑状态则不更新，否则就更新
    BOOL32 IsCouldUpdate();

    void UpdateSysTime();

    void AddTime();

    void MinusTime();
     
private:
    
    BOOL32             m_bCouldUpdateTime;

    int                m_nExHour;
    int                m_nExMin;
    int                m_nExSec;

    
    static CTimeSetLogic *m_pLogic; 
   
    
    const static String  m_stcStrDlgSysTime ;   //系统时间设置界面
    const static String  m_stcStrEdtDate ;         //系统日期
    const static String  m_stcStrEdtHour  ;         //系统时
    const static String  m_stcStrEdtMin  ;           //系统分
    const static String  m_stcStrEdtSec  ;           //系统miao
    const static String  m_stcStrBtnCalender; 

   


    //方案
    
    const static String m_SchmSysTime;            //显示系统是时间界面方案
     
    EmFocusItem         m_emFocusItem;
    
    bool    m_bEnterCalendar; //whether clicked calendar Dlg.

};

#endif // !defined(AFX_USERDEFINEDLOGIC_H__178F8700_0811_417F_BB2D_E1FE182EACC1__INCLUDED_)
