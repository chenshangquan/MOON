// userDefinedLogic.cpp: implementation of the CUserDefinedLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cms.h"
#include "timeSetLogic.h" 
#include "sysTime.h"
#include "msgboxlogic.h"
 
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
 
const  String CTimeSetLogic::m_stcStrDlgSysTime = "DlgSysTime";   //系统时间设置界面
const  String CTimeSetLogic::m_stcStrEdtDate = "EdtDate";         //系统日期
const  String CTimeSetLogic::m_stcStrEdtHour = "EdtHour";         //系统时
const  String CTimeSetLogic::m_stcStrEdtMin = "EdtMin";           //系统分
const  String CTimeSetLogic::m_stcStrEdtSec = "EdtSec";
const  String CTimeSetLogic::m_stcStrBtnCalender = "BtnCalender";           //日历按钮

 

//方案
const  String CTimeSetLogic::m_SchmSysTime = "SchmSysTime";            //显示系统是时间界面方案
 

CTimeSetLogic *CTimeSetLogic::m_pLogic = NULL;
CTimeSetLogic::CTimeSetLogic(): m_bCouldUpdateTime(TRUE),m_emFocusItem(em_Focus_Hour) 
{
    m_bEnterCalendar = FALSE;
}

CTimeSetLogic::~CTimeSetLogic()
{
    if ( m_pLogic != NULL )
    {   
        UnRegMsg();
        UnRegFunc();
        delete m_pLogic;
        m_pLogic = NULL; 
    }
}


CTimeSetLogic* CTimeSetLogic::GetLogicPtr()
{
    if ( m_pLogic == NULL )
    {  
        m_pLogic = new CTimeSetLogic();   
    }
    
    return m_pLogic;
}

void CTimeSetLogic::RegMsg()
{    
    
   REG_MSG_HANDLER( UI_CMS_UPDATE_SYSTEM_TIME,CTimeSetLogic::OnUpdateSysTime , m_pLogic, CTimeSetLogic  ); 
      
}

void CTimeSetLogic::UnRegMsg()
{
    
}

bool CTimeSetLogic::RegCBFun()
{   	 
    REG_GOBAL_MEMBER_FUNC( "CTimeSetLogic::InitWnd", CTimeSetLogic::InitWnd, m_pLogic, CTimeSetLogic);
    REG_GOBAL_MEMBER_FUNC( "CTimeSetLogic::BtnSaveToFileClick", CTimeSetLogic::BtnSaveToFileClick, m_pLogic, CTimeSetLogic ) ; 

     REG_GOBAL_MEMBER_FUNC( "CTimeSetLogic::BtnSaveClick", CTimeSetLogic::BtnSaveClick, m_pLogic, CTimeSetLogic ) ; 

    REG_GOBAL_MEMBER_FUNC( "CTimeSetLogic::BtnTCancleClick", CTimeSetLogic::BtnCancleClick ,m_pLogic, CTimeSetLogic ) ; 
    
    REG_GOBAL_MEMBER_FUNC( "CTimeSetLogic::BeginEditSysTime", CTimeSetLogic::BeginEditSysTime ,m_pLogic, CTimeSetLogic ) ; 
     
    REG_GOBAL_MEMBER_FUNC( "CTimeSetLogic::OnSysCfg", CTimeSetLogic::OnSysCfg ,m_pLogic, CTimeSetLogic ) ; 
    
    //hour Add
    REG_GOBAL_MEMBER_FUNC( "CTimeSetLogic::BtnAddHourClick", CTimeSetLogic::BtnAddHourClick ,m_pLogic, CTimeSetLogic ) ; 
     
    //DeleteHour
    REG_GOBAL_MEMBER_FUNC( "CTimeSetLogic::BtnDeleteHourClick", CTimeSetLogic::BtnDeleteHourClick ,m_pLogic, CTimeSetLogic ) ; 
     
    //min Add
    REG_GOBAL_MEMBER_FUNC( "CTimeSetLogic::BtnAddMinClick", CTimeSetLogic::BtnAddMinClick ,m_pLogic, CTimeSetLogic ) ; 
     
    //min delete
    REG_GOBAL_MEMBER_FUNC( "CTimeSetLogic::BtnDeleteMinClick", CTimeSetLogic::BtnDeleteMinClick ,m_pLogic, CTimeSetLogic ) ; 
     
    //点击日历
    REG_GOBAL_MEMBER_FUNC( "CTimeSetLogic::BtnCalendarClick", CTimeSetLogic::BtnCalendarClick ,m_pLogic, CTimeSetLogic ) ; 
   
	REG_GOBAL_MEMBER_FUNC( "CTimeSetLogic::OnCalendarDateChange", CTimeSetLogic::OnCalendarDateChange ,m_pLogic, CTimeSetLogic ) ; 
    
    REG_GOBAL_MEMBER_FUNC( "CTimeSetLogic::BtnSyncTimeToServClick", CTimeSetLogic::BtnSyncTimeToServClick ,m_pLogic, CTimeSetLogic ) ; 
    
    
    REG_GOBAL_MEMBER_FUNC( "CTimeSetLogic::EdtSecOnChar", CTimeSetLogic::FocusOnSec ,m_pLogic, CTimeSetLogic ) ; 
    REG_GOBAL_MEMBER_FUNC( "CTimeSetLogic::EdtMinOnChar", CTimeSetLogic::FocusOnMin ,m_pLogic, CTimeSetLogic ) ; 
    REG_GOBAL_MEMBER_FUNC( "CTimeSetLogic::EdtHourOnChar", CTimeSetLogic::FocusOnHour ,m_pLogic, CTimeSetLogic ) ; 

    REG_GOBAL_MEMBER_FUNC( "CTimeSetLogic::BtnDeleteClick", CTimeSetLogic::BtnMinusClick ,m_pLogic, CTimeSetLogic ) ; 
    REG_GOBAL_MEMBER_FUNC( "CTimeSetLogic::BtnAddClick", CTimeSetLogic::BtnAddClick ,m_pLogic, CTimeSetLogic ) ; 
   
    REG_GOBAL_MEMBER_FUNC( "CTimeSetLogic::EditTimeSetLimit", CTimeSetLogic::EditTimeSetLimit ,m_pLogic, CTimeSetLogic ) ;    
  
    REG_GOBAL_MEMBER_FUNC( "CTimeSetLogic::OnAddBtnHold", CTimeSetLogic::BtnAddClick , m_pLogic, CTimeSetLogic  ); 
    REG_GOBAL_MEMBER_FUNC( "CTimeSetLogic::OnMinusBtnHold", CTimeSetLogic::BtnMinusClick , m_pLogic, CTimeSetLogic  ); 

    REG_GOBAL_MEMBER_FUNC( "CTimeSetLogic::OnAddBtnHoldEnd", CTimeSetLogic::OnBtnHoldEnd , m_pLogic, CTimeSetLogic  ); 
    REG_GOBAL_MEMBER_FUNC( "CTimeSetLogic::OnMinusBtnHoldEnd", CTimeSetLogic::OnBtnHoldEnd , m_pLogic, CTimeSetLogic  );  

    return true;
}

bool CTimeSetLogic::UnRegFunc()
{
    //	UN_REG_GOBAL_FUNC( "CConftempEdtLogic::InitWnd" );
    return true;
}


bool CTimeSetLogic::InitWnd(  const IArgs & arg )
{   
    CWndLogicBase::InitWnd( arg );
     
    
    UpdateSysTime();
    
    Value_TransparentBtnUseTimer valUseTimer;
    valUseTimer.bUseTimer = TRUE;
    UIManagePtr->SetPropertyValue( valUseTimer, "DlgSysTime/BtnAdd", m_pWndTree );
    UIManagePtr->SetPropertyValue( valUseTimer, "DlgSysTime/BtnDel", m_pWndTree );

    return true;
}

 
void CTimeSetLogic::Clear()
{  
    if ( m_pWndTree )
    {
		UIManagePtr->LoadScheme( "SchmNormal", m_pWndTree );
        UIManagePtr->ShowWindow( "CalendarDlg", false );
    }
    if ( m_bCouldUpdateTime == FALSE )
    {
        m_bCouldUpdateTime = TRUE;
    }
    m_emFocusItem = em_Focus_Hour;
    m_bEnterCalendar = FALSE;
}

 
bool CTimeSetLogic::OnSysCfg( const IArgs& args )
{
    if ( ! UIManagePtr->IsVisible( "DlgSysTime/BtnEdit" ) )
    {    
       // if ( !m_bCouldUpdateTime )           
        CString strMsg = "是否对编辑进行保存?";
        Args_MsgBox argMsg;
        argMsg.pOwnerWnd = UIManagePtr->GetWindowPtr( "DlgSysTime" );
        int nResult = MSG_BOX( strMsg, TRUE, &argMsg);
        if ( IDOK == nResult )
        {
            BtnSaveClick(args);
        }
        else
        {
            BtnCancleClick(args);
        }
    }
    UIManagePtr->LoadScheme( "SchmSysCfg", NULL, "SysCfgDlg" );
    return true;
}


bool CTimeSetLogic::BtnSaveToFileClick( const IArgs & arg )
{
    return  UIManagePtr->SaveToFile(  g_stcStrUserdefinedDlg  );   
}

  

//点击了保存按钮
bool CTimeSetLogic::BtnSaveClick( const IArgs & arg )
{
    m_bCouldUpdateTime = TRUE;
    m_emFocusItem = em_Focus_Hour;

    SaveSysTimeDlg();    
    UIManagePtr->LoadScheme( "SchmNormal", m_pWndTree );
   return true;
}

// 开始编辑系统时间
bool CTimeSetLogic::BeginEditSysTime( const IArgs & arg )
{
	UIManagePtr->LoadScheme( "SchmEdit", m_pWndTree );
	//m_bCouldUpdateTime = FALSE;  //改为在编辑框中有改动时设定此标志 2012-07-11
	return true;
}





//点击了取消按钮
bool CTimeSetLogic::BtnCancleClick( const IArgs & arg )
{   
    m_bCouldUpdateTime = TRUE;
    m_emFocusItem = em_Focus_Hour;
    m_bEnterCalendar = false;
    SaveSysTimeDlg(FALSE);     
    UIManagePtr->LoadScheme( "SchmNormal", m_pWndTree );
	return true;
}

//WM_EDIT_SETFOCUS
bool  CTimeSetLogic::FocusOnSec( const IArgs & arg )
{
    String  strSec ;
    UIManagePtr->GetCaption( m_stcStrEdtSec, strSec, m_pWndTree );
    
    m_nExSec  = atoi( strSec.c_str() );

    //m_bCouldUpdateTime = FALSE;
    m_emFocusItem = em_Focus_Sec;
    return true;
}

//response to WM_EDIT_SETFOCUS
bool  CTimeSetLogic::FocusOnMin( const IArgs & arg )
{
    String  strSec ;
    UIManagePtr->GetCaption( m_stcStrEdtSec, strSec, m_pWndTree );
    
    m_nExMin  = atoi( strSec.c_str() );

    //m_bCouldUpdateTime = FALSE;
    m_emFocusItem = em_Focus_Min;
    return true;
}

//WM_EDIT_SETFOCUS
bool  CTimeSetLogic::FocusOnHour( const IArgs & arg )
{
    String  strSec ;
    UIManagePtr->GetCaption( m_stcStrEdtSec, strSec, m_pWndTree );
    
    m_nExHour = atoi( strSec.c_str() );

    //m_bCouldUpdateTime = FALSE;
    m_emFocusItem = em_Focus_Hour;
    return true;
}


//  Add emHour emMin emSec
bool CTimeSetLogic::BtnAddClick( const IArgs & arg )
{   
    m_bCouldUpdateTime = FALSE;

    AddTime();    

    return true;
}

void CTimeSetLogic::AddTime()
{
    switch( m_emFocusItem )
    {
    case em_Focus_Hour:
        {
            String strHour;
            UIManagePtr->GetCaption( m_stcStrEdtHour, strHour, m_pWndTree );
            
            int nHourt = atoi( strHour.c_str() );            
            
            if ( nHourt == 23 )
            {   
                nHourt = 0;                
            }
            else
            {
                nHourt++;
            }
            
            s8 pHour[3] = {0} ;
            sprintf( pHour,"%.2d", nHourt );   
            //sprintf( pHour,"%d", nHourt ); 
            UIManagePtr->SetCaption( m_stcStrEdtHour, pHour, m_pWndTree );
            
//             Window* pWnd = UIManagePtr->GetWindowPtr( m_stcStrEdtHour, m_pWndTree );
//             if ( pWnd  )
//             { 
//                 pWnd->SetFocus();
//                 CEdit* pEd = ( CEdit *) pWnd ;
//                 pEd->SetSel( 0, -1 );
//                 // UIManagePtr->UpdateUI( m_stcStrEdtHour,  m_pWndTree );                
//             }
        }
        break;
    case em_Focus_Min:
        {  
            String  strMin ;
            UIManagePtr->GetCaption( m_stcStrEdtMin, strMin, m_pWndTree );
            
            int nMin  = atoi( strMin.c_str() );
            if ( nMin == 59 )
            {
                nMin = 0;               
            }            
            else
            {
                nMin++;
            }
            s8 pMin[3] = {0} ;
            sprintf( pMin,"%.2d", nMin );  
            //sprintf( pMin,"%d", nMin ); 
            UIManagePtr->SetCaption( m_stcStrEdtMin, pMin, m_pWndTree );
            
//             Window* pWnd = UIManagePtr->GetWindowPtr( m_stcStrEdtMin, m_pWndTree );
//             if ( pWnd  )
//             {   
//                 pWnd->SetFocus();
//                 CEdit* pEd = ( CEdit *)  pWnd ;
//                 pEd->SetSel( 0, -1 ); 
//                 // UIManagePtr->UpdateUI( m_stcStrEdtMin,  m_pWndTree );
//             }
            
        }
        break;
    case em_Focus_Sec:
        {
            String  strSec ;
            UIManagePtr->GetCaption( m_stcStrEdtSec, strSec, m_pWndTree );
            
            int nSec  = atoi( strSec.c_str() );
            if ( nSec == 59 )
            {
                nSec = 0; 
            }
            else
            {
                nSec++;
            }
            s8 pSec[3] = {0} ;
            sprintf( pSec,"%.2d", nSec );
            //sprintf( pSec,"%d", nSec );            
             UIManagePtr->SetCaption( m_stcStrEdtSec, pSec, m_pWndTree );
//             Window* pWnd = UIManagePtr->GetWindowPtr( m_stcStrEdtSec, m_pWndTree );
//             if ( pWnd  )
//             {   
//                 pWnd->SetFocus();
//                 CEdit* pEd = ( CEdit *)  pWnd ;
//                 pEd->SetSel( 0, -1 );
//                 // UIManagePtr->UpdateUI( m_stcStrEdtSec,  m_pWndTree );
//                 
//             }
            
        }
    } 
    
}

//  Minus the number in the clock edit control
bool CTimeSetLogic::BtnMinusClick( const IArgs & arg )
{ 
    m_bCouldUpdateTime = FALSE;    
    
    MinusTime(); 

   return true;
}

void CTimeSetLogic::MinusTime()
{
    switch( m_emFocusItem )
    {
    case em_Focus_Hour:
        {
            String strHour;
            UIManagePtr->GetCaption( m_stcStrEdtHour, strHour, m_pWndTree );
            
            int nHourt = atoi( strHour.c_str() );
            
            ( 0 == nHourt )? ( nHourt = 23 ):( nHourt-- );   
            
            s8 pHour[3] = {0} ;
            sprintf( pHour,"%.2d", nHourt );            
            //sprintf( pHour,"%d", nHourt );
            UIManagePtr->SetCaption( m_stcStrEdtHour, pHour, m_pWndTree );
            
//             Window* pWnd = UIManagePtr->GetWindowPtr( m_stcStrEdtHour, m_pWndTree );
//             if ( pWnd  )
//             { 
//                 pWnd->SetFocus();
//                 CEdit* pEd = ( CEdit *) pWnd ;
//                 pEd->SetSel( 0, -1 );
//                 // UIManagePtr->UpdateUI( m_stcStrEdtHour,  m_pWndTree );
//             }
            
        }
        break;
    case em_Focus_Min:
        {  
            String  strMin ;
            UIManagePtr->GetCaption( m_stcStrEdtMin, strMin, m_pWndTree );
            
            int nMin  = atoi( strMin.c_str() );
            if ( 0 == nMin )
            {
                nMin = 59;
            }
            else
            {
                nMin--;
            }
            s8 pMin[3] = {0} ;
            sprintf( pMin,"%.2d", nMin ); 
            //sprintf( pMin,"%d", nMin ); 
            UIManagePtr->SetCaption( m_stcStrEdtMin, pMin, m_pWndTree );
            
            
//             Window* pWnd = UIManagePtr->GetWindowPtr( m_stcStrEdtMin, m_pWndTree );
//             if ( pWnd  )
//             {   
//                 pWnd->SetFocus();
//                 CEdit* pEd = ( CEdit *)  pWnd ;
//                 pEd->SetSel( 0, -1 ); 
//                 // UIManagePtr->UpdateUI( m_stcStrEdtMin,  m_pWndTree );
//             }
            
        }
        break;
    case em_Focus_Sec:
        {  
            
            String  strSec ;
            UIManagePtr->GetCaption( m_stcStrEdtSec, strSec, m_pWndTree );
            
            int nSec  = atoi( strSec.c_str() );
            if ( 0 == nSec )
            {
                nSec = 59;
            }
            else
            {
                nSec--;
            }
            
            s8 pSec[3] = {0} ;
            sprintf( pSec,"%.2d", nSec );     
            //sprintf( pSec,"%d", nSec );            
            UIManagePtr->SetCaption( m_stcStrEdtSec, pSec, m_pWndTree );           
            
//             Window* pWnd = UIManagePtr->GetWindowPtr( m_stcStrEdtSec, m_pWndTree );
//             if ( pWnd  )
//             {   
//                 pWnd->SetFocus();
//                 CEdit* pEd = ( CEdit *)  pWnd ;
//                 pEd->SetSel( 0, -1 );
//                 // UIManagePtr->UpdateUI( m_stcStrEdtSec,  m_pWndTree );                
//             }           
            
        }
    }  
}
 

void CTimeSetLogic::SaveSysTimeDlg( BOOL32 bSave /*= TRUE */ )
{ 
    if ( bSave )
    {
        //把时间设置为系统时间 
        
        SYSTEMTIME time;
        ZeroMemory( &time, sizeof(SYSTEMTIME));
        String str;
        UIManagePtr->GetCaption( m_stcStrEdtDate, str,m_pWndTree );
        sscanf( str.c_str(),"%u年%u月%u日",&time.wYear,&time.wMonth,&time.wDay);
        
        
        Args_MsgBox arg;
        arg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;

        UIManagePtr->GetCaption( m_stcStrEdtHour, str,m_pWndTree );
        if ( str.size() == 0 )
        {
            str = "00";
            UIManagePtr->SetCaption( m_stcStrEdtHour, str,m_pWndTree );

        }
        sscanf( str.c_str(),"%d",&time.wHour);
//         if ( time.wHour > 23 || time.wHour < 0 )
//         {
//            MSG_BOX_PROMPT( "小时为 0 ~ 23 间的整数", &arg );
//            return ;
//         }
        
        
        UIManagePtr->GetCaption( m_stcStrEdtMin, str,m_pWndTree );
        if ( str.size() == 0 )
        {
            str = "00";
            UIManagePtr->SetCaption( m_stcStrEdtMin, str,m_pWndTree );

        }
        sscanf( str.c_str(),"%d",&time.wMinute); 
//         if ( time.wMinute > 59 || time.wMinute < 0 )
//         {
//             MSG_BOX_PROMPT( "分钟为 0 ~ 59 间的整数", &arg );
//             return ;
//         }

        UIManagePtr->GetCaption( m_stcStrEdtSec, str,m_pWndTree );
        if ( str.size() == 0 )
        {
            str = "00";
            UIManagePtr->SetCaption( m_stcStrEdtSec, str,m_pWndTree );

        }
        sscanf( str.c_str(),"%d",&time.wSecond); 
//         if ( time.wSecond > 59 || time.wSecond < 0 )
//         {
//             MSG_BOX_PROMPT( "秒为 0 ~ 59 间的整数", &arg );
//             return ;
//         }       

        BOOL32 re = SetLocalTime( &time );
        if ( !re )
        {   
            DWORD  err = GetLastError();
            PrtMsg( 0,emEventTypeCmsWindow,"设置系统时间失败，GetLastError() = %d",err);
            ShowPopMsg("设置系统时间失败");
        }
        else
        {   
            SyncTimeToServ(  time ); 
            CMsgDispatch::SendMessage( UI_CMS_MODIFY_SYSTEM_TIME , 0 , 0 );
        }
    }
    else
    {    
        UpdateSysTime();
    }
    
}
 
 

void  CTimeSetLogic::UpdateSysTime()
{
    SYSTEMTIME sysTime;
	::GetLocalTime( &sysTime );
    OnUpdateSysTime( (WPARAM)&sysTime, 0 );
}

 
//wparam: SYSTEMTIME
HRESULT CTimeSetLogic::OnUpdateSysTime( WPARAM wparem, LPARAM lparem )
{    
    if ( m_pWndTree == NULL ||  !IsCouldUpdate() )
    {
        return NO_ERROR;
    }

    Window* pWnd = NULL;
    String strTxt;

    SYSTEMTIME time = * reinterpret_cast< SYSTEMTIME *>(wparem);

    s8 buf[20] = { 0 };
    if ( !m_bEnterCalendar )
    {
        sprintf( buf, "%d年%d月%d日",time.wYear, time.wMonth, time.wDay );            
        UIManagePtr->SetCaption( m_stcStrEdtDate, buf ,m_pWndTree );
    }    

    int nNum;
    UIManagePtr->GetCaption( m_stcStrEdtHour, strTxt ,m_pWndTree ); 
    nNum = atoi( strTxt.c_str() );
    if ( nNum != time.wHour )
    {
        sprintf( buf, "%.2d",time.wHour );
        UIManagePtr->SetCaption( m_stcStrEdtHour, buf ,m_pWndTree );

        if ( m_emFocusItem == em_Focus_Hour )
        {
            pWnd = UIManagePtr->GetWindowPtr( m_stcStrEdtHour, m_pWndTree ); 
            (( CEdit *) pWnd)->SetSel( 0, -1 );   
        }
    }

    UIManagePtr->GetCaption( m_stcStrEdtMin, strTxt ,m_pWndTree ); 
    nNum = atoi( strTxt.c_str() );
    if ( nNum != time.wMinute )
    {
        sprintf( buf, "%.2d",time.wMinute );
        UIManagePtr->SetCaption( m_stcStrEdtMin, buf ,m_pWndTree );

        if ( m_emFocusItem == em_Focus_Min )
        {
            pWnd = UIManagePtr->GetWindowPtr( m_stcStrEdtMin, m_pWndTree );   
            (( CEdit *) pWnd)->SetSel( 0, -1 );
            
        }
    }

    sprintf( buf, "%.2d",time.wSecond );
    UIManagePtr->SetCaption( m_stcStrEdtSec, buf ,m_pWndTree ); 
    
    //for cursor not keep in the same position, when set focus on the Edit
    //SXC 20120711    
     if ( m_emFocusItem == em_Focus_Sec )
    {
        pWnd = UIManagePtr->GetWindowPtr( m_stcStrEdtSec, m_pWndTree );   
        (( CEdit *) pWnd)->SetSel( 0, -1 );
    }
    
    pWnd = NULL;

    return NO_ERROR;
}

//是否可以更新，如果当前正处在编辑状态则不更新，否则就更新
BOOL32 CTimeSetLogic::IsCouldUpdate()
{
    return m_bCouldUpdateTime;
}


//hour Add
bool CTimeSetLogic::BtnAddHourClick( const IArgs & arg )
{  
   m_bCouldUpdateTime = FALSE; 
   
   String strHour;
   UIManagePtr->GetCaption( m_stcStrEdtHour, strHour, m_pWndTree );
   
   int nHourt = atoi( strHour.c_str() );
   
   if ( nHourt < 23 )
   {
       s8 pHour[3] = {0} ;
       sprintf( pHour,"%.2d", nHourt +  1 );
       
      UIManagePtr->SetCaption( m_stcStrEdtHour, pHour, m_pWndTree );
   }
   else
   {
       ShowPopMsg("小时为 0 ~ 23 间的整数");
   }
   

   return true;
}


//DeleteHour
bool CTimeSetLogic::BtnDeleteHourClick( const IArgs & arg )
{
    m_bCouldUpdateTime = FALSE; 
    
    String strHour;
    UIManagePtr->GetCaption( m_stcStrEdtHour, strHour, m_pWndTree );
    
    int nHourt = atoi( strHour.c_str() );
    
    if ( nHourt > 0 )
    {
        s8 pHour[3] = {0} ;
        sprintf( pHour,"%.2d", nHourt - 1 );
        
       UIManagePtr->SetCaption( m_stcStrEdtHour, pHour, m_pWndTree );
   }
    else
    {
        ShowPopMsg("小时为 0 ~ 23 间的整数");
    }

    
    
   return true;
}


//min Add
bool CTimeSetLogic::BtnAddMinClick( const IArgs & arg )
{
    m_bCouldUpdateTime = FALSE;
    
    String  strMin ;
    UIManagePtr->GetCaption( m_stcStrEdtMin, strMin, m_pWndTree );
    
    int nMin  = atoi( strMin.c_str() );
    if ( nMin < 59 )
    {
        s8 pMin[3] = {0} ;
        sprintf( pMin,"%.2d", nMin + 1 );

        UIManagePtr->SetCaption( m_stcStrEdtMin, pMin, m_pWndTree );
    }
    else
    {
        ShowPopMsg("分钟为 0 ~ 59 间的整数");
    }

    
    
   return true;
}


//min delete
bool CTimeSetLogic::BtnDeleteMinClick( const IArgs & arg )
{
    m_bCouldUpdateTime = FALSE;
    
    String  strMin ;
    UIManagePtr->GetCaption( m_stcStrEdtMin, strMin, m_pWndTree );
    
    int nMin  = atoi( strMin.c_str() );
    if ( nMin > 0 )
    {
        s8 pMin[3] = {0} ;
        sprintf( pMin,"%.2d", nMin - 1 );

        UIManagePtr->SetCaption( m_stcStrEdtMin, pMin, m_pWndTree );
    }
    else
    {
        ShowPopMsg("分钟为 0 ~ 59 间的整数");
    }
    
    
    return true;
}


//点击日历
bool CTimeSetLogic::BtnCalendarClick( const IArgs & arg )
{
    String str;
    UIManagePtr->GetCaption( m_stcStrEdtDate, str,m_pWndTree );
    int nYear = 0;
    int nMonth = 0;
    int nDay = 0;
    sscanf( str.c_str(), "%u年%u月%u日", &nYear,&nMonth, &nDay );
    
    if ( CTransparentCalendar* pCalendar = dynamic_cast<CTransparentCalendar*>( UIManagePtr->GetWindowPtr( "CalendarDlg/Calender" ) )  )
    {
        pCalendar->SetSelDate( nYear, nMonth, nDay );
    }
    
    Value_WindowOwer owerVal;
    owerVal.pWnd = m_pWndTree->GetItemData()->pWnd;
    UIManagePtr->SetPropertyValue( owerVal, "CalendarDlg");
    
    UIManagePtr->ShowWindow( "CalendarDlg", true );
    return true;
}


bool CTimeSetLogic::OnCalendarDateChange( const IArgs & args )
{
	Args_WindowMsg WinMsg = *dynamic_cast<const Args_WindowMsg*>(&args);
	WindowMsg msg = WinMsg.m_Msg;
	
	CString strDate = *(CString*)(msg.wParam);
    UIManagePtr->SetCaption( m_stcStrEdtDate, (LPCTSTR)strDate, m_pWndTree );
	//m_bCouldUpdateTime = FALSE;
    m_bEnterCalendar = TRUE;

	return true;
}

 
//点击时间同步
bool CTimeSetLogic::BtnSyncTimeToServClick( const IArgs & arg )
{
    SYSTEMTIME sysTime;
	::GetLocalTime( &sysTime ); 
    u16 re = SyncTimeToServ( sysTime ); 
    if ( re != NO_ERROR )
    {  
        HANDLE_ERROR( re ); 
    }  
    
    return true;
}
 



u16 CTimeSetLogic::SyncTimeToServ( const SYSTEMTIME sysTime  )
{  
    TTPTime time;
    time.m_wYear = sysTime.wYear;
    time.m_byMonth = sysTime.wMonth;
    time.m_byMDay = sysTime.wDay;
    time.m_byHour = sysTime.wHour;
    time.m_byMinute = sysTime.wMinute;
    time.m_bySecond = sysTime.wSecond;
    u16 re =  BusinessManagePtr->UpdateSysTime( time ); 
   
    if ( re == NO_ERROR )
    {  
        BusinessManagePtr->ReqSysTime();
    } 

    return re;
}

//response to WM_EDIT_ONCHAR , can change to WM_EDIT_CHANGED
//
bool CTimeSetLogic::EditTimeSetLimit( const IArgs & arg )
{
    m_bCouldUpdateTime = FALSE;
    switch( m_emFocusItem )
    {
    case em_Focus_Hour:
        {
            String strHour;
            UIManagePtr->GetCaption( m_stcStrEdtHour, strHour, m_pWndTree );
            
            int nHour = atoi( strHour.c_str() );            
            
            if ( nHour > 23 )
            {   
                nHour = m_nExHour;                
            }
            else
            {
                m_nExHour = nHour;
                break;
            }
            
            s8 pHour[3] = {0} ;
            sprintf( pHour,"%d", nHour );            
            UIManagePtr->SetCaption( m_stcStrEdtHour, pHour, m_pWndTree );
            
            Window* pWnd = UIManagePtr->GetWindowPtr( m_stcStrEdtHour, m_pWndTree );
            if ( pWnd  )
            { 
                (( CEdit *) pWnd)->SetSel( -1 );
//                 //pWnd->SetFocus();
//                 CEdit* pEd = ( CEdit *) pWnd ;
//                 pEd->SetSel( 0, -1 );
//                 // UIManagePtr->UpdateUI( m_stcStrEdtHour,  m_pWndTree );                
             }
        }
        break;
    case em_Focus_Min:
        {  
            String  strMin ;
            UIManagePtr->GetCaption( m_stcStrEdtMin, strMin, m_pWndTree );
            
            int nMin  = atoi( strMin.c_str() );
            if ( nMin > 59 )
            {
                nMin = m_nExMin;               
            } 
            else
            {
                m_nExMin = nMin;
                break;
            }
           
            s8 pMin[3] = {0} ;
            sprintf( pMin,"%d", nMin );            
            UIManagePtr->SetCaption( m_stcStrEdtMin, pMin, m_pWndTree );
            
            Window* pWnd = UIManagePtr->GetWindowPtr( m_stcStrEdtMin, m_pWndTree );
            if ( pWnd  )
            {   
                (( CEdit *) pWnd)->SetSel( -1 );
            }
            
        }
        break;
    default:
        {
            String  strSec ;
            UIManagePtr->GetCaption( m_stcStrEdtSec, strSec, m_pWndTree );
            
            int nSec  = atoi( strSec.c_str() );
            if ( nSec > 59 )
            {
                nSec = m_nExSec; 
            }
            else
            {
                m_nExSec = nSec;
                break;
            }

            s8 pSec[3] = {0} ;
            sprintf( pSec,"%d", nSec );            
            UIManagePtr->SetCaption( m_stcStrEdtSec, pSec, m_pWndTree );
            Window* pWnd = UIManagePtr->GetWindowPtr( m_stcStrEdtSec, m_pWndTree );
             if ( pWnd  )
             { 
                 (( CEdit *) pWnd)->SetSel( -1 );               
             }
            
        }
    } 
    return true;
}


bool CTimeSetLogic::OnBtnHoldEnd( const IArgs & arg )
{
    Window* pWnd;
    switch( m_emFocusItem )
    {
    case em_Focus_Hour: 
        {
             pWnd = UIManagePtr->GetWindowPtr( m_stcStrEdtHour, m_pWndTree );
//             if ( pWnd  )
//             {     
//                 pWnd->SetFocus();
//                 CEdit* pEd = ( CEdit *) pWnd ;               
//                 pEd->SetSel( 0, -1 );
//                             
//              }
        }
        break;
    case em_Focus_Min: 
        {
           pWnd = UIManagePtr->GetWindowPtr( m_stcStrEdtMin, m_pWndTree );
//             if ( pWnd  )
//             { 
//                 pWnd->SetFocus();
//                 CEdit* pEd = ( CEdit *) pWnd ;
//                 pEd->SetSel( 0, -1 );
//                 
//             } 
         }
        break;
    case em_Focus_Sec: 
        {
            pWnd = UIManagePtr->GetWindowPtr( m_stcStrEdtSec, m_pWndTree );
            
        }
        break;
    }

    if ( pWnd  )
    { 
        pWnd->SetFocus();
        CEdit* pEd = ( CEdit *) pWnd ;
        pEd->SetSel( 0, -1 );
        
    }
    return 0;
}

// bool CTimeSetLogic::OnMinusBtnHoldEnd( const IArgs & arg )
// {
//     
//     return 0;
// }

