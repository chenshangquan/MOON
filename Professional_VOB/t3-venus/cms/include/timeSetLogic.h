// userDefinedLogic.h: interface for the CUserDefinedLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TIMESETLOGIC_H__178F8700_0811_417F_BB2D_E1FE182EACC1__INCLUDED_)
#define AFX_TIMESETLOGIC_H__178F8700_0811_417F_BB2D_E1FE182EACC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

enum EmFocusItem  //��ǰ�н������
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
	* ����:  �������״̬������
	* @return   
	* @remarks	 
	*/
    virtual void Clear() ;

    bool BtnSaveToFileClick( const IArgs & arg );
    
    bool OnSysCfg( const IArgs& args );

    //����˱��水ť
    bool BtnSaveClick( const IArgs & arg );
   

    //�����ȡ����ť
    bool BtnCancleClick( const IArgs & arg );


    //��ʼ�༭ϵͳʱ��
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


    //�������
    bool BtnCalendarClick( const IArgs & arg );

	bool OnCalendarDateChange( const IArgs & args );

    //���ʱ��ͬ��
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
     
    void SaveSysTimeDlg( BOOL32 bSave = TRUE );    //����ϵͳʱ����Ϣ 
 
 
    virtual void RegMsg(); 
    virtual void UnRegMsg();
    
    //�Ƿ���Ը��£������ǰ�����ڱ༭״̬�򲻸��£�����͸���
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
   
    
    const static String  m_stcStrDlgSysTime ;   //ϵͳʱ�����ý���
    const static String  m_stcStrEdtDate ;         //ϵͳ����
    const static String  m_stcStrEdtHour  ;         //ϵͳʱ
    const static String  m_stcStrEdtMin  ;           //ϵͳ��
    const static String  m_stcStrEdtSec  ;           //ϵͳmiao
    const static String  m_stcStrBtnCalender; 

   


    //����
    
    const static String m_SchmSysTime;            //��ʾϵͳ��ʱ����淽��
     
    EmFocusItem         m_emFocusItem;
    
    bool    m_bEnterCalendar; //whether clicked calendar Dlg.

};

#endif // !defined(AFX_USERDEFINEDLOGIC_H__178F8700_0811_417F_BB2D_E1FE182EACC1__INCLUDED_)
