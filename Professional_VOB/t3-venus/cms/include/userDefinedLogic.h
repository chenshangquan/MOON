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
	* ����:  �������״̬������
	* @return   
	* @remarks	 
	*/
    virtual void Clear() ;

    bool BtnSaveToFileClick( const IArgs & arg );
    
    
    //����Զ����б���Ŀ
    bool OnDefinedItemClick( const IArgs & arg );


    //��������б���Ŀ
    bool OnFuncLstItemClick( const IArgs & arg );
    

    bool OnDefinedItemIconClick( const IArgs & arg );

    //���ת���Զ������
    bool BtnToUserDefinedClick( const IArgs & arg );
    

    //����˱��水ť
    bool BtnSaveClick( const IArgs & arg );
   

    //�����ȡ����ť
    bool BtnCancleClick( const IArgs & arg );


    //��ʼ�༭ϵͳʱ��
    bool BeginEditSysTime( const IArgs & arg );


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


    bool  EdtMinOnChar( const IArgs & arg );
    
    bool  EdtHourOnChar( const IArgs & arg );


    u16   SyncTimeToServ( const SYSTEMTIME sysTime  );

    void UpdateFuncList();

    void SetFuncLstOffset( int nOffset = 0);
    void SetFuncLstSel( int nIndex = -1 );
protected: 
    
    HRESULT OnUpdateSysTime( WPARAM wparam, LPARAM lparam); 
    
    void SaveSysNameDlg( BOOL32 bSave = TRUE );  //����ϵͳ������Ϣ
    void SaveScreenPswdDlg( BOOL32 bSave = TRUE ); //��������������Ϣ
    void SaveSysTimeDlg( BOOL32 bSave = TRUE );    //����ϵͳʱ����Ϣ
    void SaveFuncLstDlg( BOOL32 bSave = TRUE );  //���湦���б�

    void  InitUserDefinedLst();
    
    void  ShowSubDlg( String StrDlgName );
    
 
    virtual void RegMsg(); 
    virtual void UnRegMsg();
    
    //�Ƿ���Ը��£������ǰ�����ڱ༭״̬�򲻸��£�����͸���
    BOOL32 IsCouldUpdate();

    void UpdateSysTime();

    bool BtnSwitchClick( const IArgs& args );

    void InitFuncLst();
    void SetMenuLst( vector<TConfMenuInfo> *pLst );
private:
    
    BOOL32             m_bCouldUpdateTime;
    EmConfigType        m_emConfigType;          //��ǰ���ĸ����ý���
    static CUserDefinedLogic *m_pLogic;

    const static String m_stcStrLstUserDefined;   //�Զ����б�
    
    const static String  m_stcStrDlgSysName ;   //ϵͳ���������
    const static String  m_stcStrEdtSysName  ;   //ϵͳ��
    
    const static String  m_stcStrDlgScreenPswd ;   //�����������ý���
    const static String  m_stcStrEdtScreenPswd ;   //��������
    const static String  m_stcStrSwitchBtnScreenPswd ;   //���� 
    
    const static String  m_stcStrDlgSysTime ;   //ϵͳʱ�����ý���
    const static String  m_stcStrEdtDate ;         //ϵͳ����
    const static String  m_stcStrEdtHour  ;         //ϵͳʱ
    const static String  m_stcStrEdtMin  ;           //ϵͳ��
    const static String  m_stcStrBtnCalender;

    const static String  m_stcStrLstFunc;


    //�Զ���˵���
    const static String m_stcStrSysName;
    const static String m_stcStrSysTime;
    const static String m_stcStrScreenPswd;
    const static String m_stcStrFuncLst;


    //����
    const static String m_SchmUserDefined;       //��ʾ�Զ�����淽��
    const static String m_SchmSysName;           //��ʾ����ϵͳ�����淽��
    const static String m_SchmScreenPswd;        //��ʾ��������������淽��
    const static String m_SchmSysTime;            //��ʾϵͳ��ʱ����淽��
    const static String m_SchmFuncLst;            //��ʾϵͳ�����б���

   
   vector<TConfMenuInfo> m_vctTConfMenu;
   

};

#endif // !defined(AFX_USERDEFINEDLOGIC_H__178F8700_0811_417F_BB2D_E1FE182EACC1__INCLUDED_)
