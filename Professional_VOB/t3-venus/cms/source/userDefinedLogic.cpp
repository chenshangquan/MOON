// userDefinedLogic.cpp: implementation of the CUserDefinedLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cms.h"
#include "userDefinedLogic.h"
#include "loginLogic.h"
#include "sysTime.h"
#include "msgboxlogic.h"
#include "funcLstMenu.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const  String CUserDefinedLogic::m_stcStrLstUserDefined = "UserDefinedLst";   //自定义列表

const  String CUserDefinedLogic::m_stcStrDlgSysName = "DlgSysName";   //系统名定义界面
const  String CUserDefinedLogic::m_stcStrEdtSysName = "EdtSysName";   //系统名

const  String CUserDefinedLogic::m_stcStrDlgScreenPswd = "DlgScreenPswd";   //锁屏密码设置界面
const  String CUserDefinedLogic::m_stcStrEdtScreenPswd = "EdtPswd";   //锁屏密码
const  String CUserDefinedLogic::m_stcStrSwitchBtnScreenPswd = "BtnScreenPswdSwitch";   //锁屏 

const  String CUserDefinedLogic::m_stcStrDlgSysTime = "DlgSysTime";   //系统时间设置界面
const  String CUserDefinedLogic::m_stcStrEdtDate = "EdtDate";         //系统日期
const  String CUserDefinedLogic::m_stcStrEdtHour = "EdtHour";         //系统时
const  String CUserDefinedLogic::m_stcStrEdtMin = "EdtMin";           //系统分
const  String CUserDefinedLogic::m_stcStrBtnCalender = "BtnCalender";           //日历按钮

const  String CUserDefinedLogic::m_stcStrLstFunc = "LstFunc";
//自定义菜单项
const  String CUserDefinedLogic::m_stcStrSysName = "系统名称";
const  String CUserDefinedLogic::m_stcStrSysTime = "系统时间";
const  String CUserDefinedLogic::m_stcStrScreenPswd = "屏幕解锁密码";
const  String CUserDefinedLogic::m_stcStrFuncLst = "功能列表设置";

//方案
const  String CUserDefinedLogic::m_SchmUserDefined = "SchmUserDefined" ;       //显示自定义界面方案
const  String CUserDefinedLogic::m_SchmSysName = "SchmSysName";           //显示设置系统名界面方案
const  String CUserDefinedLogic::m_SchmScreenPswd = "SchmScreenPswd";        //显示设置锁屏密码界面方案
const  String CUserDefinedLogic::m_SchmSysTime = "SchmSysTime";            //显示系统是时间界面方案
const  String CUserDefinedLogic::m_SchmFuncLst = "SchmFuncLst";

CUserDefinedLogic *CUserDefinedLogic::m_pLogic = NULL;
CUserDefinedLogic::CUserDefinedLogic():m_emConfigType(emConfigNon),
                                        m_bCouldUpdateTime(TRUE),
                                        m_vctTConfMenu()
{
    const_cast<String&>(m_stcStrEdtSysName) = m_stcStrDlgSysName + "/" + m_stcStrEdtSysName;

    const_cast<String&>(m_stcStrEdtScreenPswd) = m_stcStrDlgScreenPswd + "/" + m_stcStrEdtScreenPswd;
    const_cast<String&>(m_stcStrSwitchBtnScreenPswd) = m_stcStrDlgScreenPswd + "/" + m_stcStrSwitchBtnScreenPswd;

    const_cast<String&>(m_stcStrEdtDate) = m_stcStrDlgSysTime + "/" + m_stcStrEdtDate;
    const_cast<String&>(m_stcStrEdtHour) = m_stcStrDlgSysTime + "/" + m_stcStrEdtHour; 
    const_cast<String&>(m_stcStrEdtMin) = m_stcStrDlgSysTime + "/" + m_stcStrEdtMin;
    const_cast<String&>(m_stcStrBtnCalender) = m_stcStrDlgSysTime + "/" + m_stcStrBtnCalender;
    

}

CUserDefinedLogic::~CUserDefinedLogic()
{
    if ( m_pLogic != NULL )
    {   
        UnRegMsg();
        UnRegFunc();
        delete m_pLogic;
        m_pLogic = NULL; 
    }
}


CUserDefinedLogic* CUserDefinedLogic::GetLogicPtr()
{
    if ( m_pLogic == NULL )
    {  
        m_pLogic = new CUserDefinedLogic();   
    }
    
    return m_pLogic;
}

void CUserDefinedLogic::RegMsg()
{    
    
  // REG_MSG_HANDLER( UI_CMS_UPDATE_SYSTEM_TIME,CUserDefinedLogic::OnUpdateSysTime , m_pLogic, CUserDefinedLogic  ); 
    
}

void CUserDefinedLogic::UnRegMsg()
{
    
}

bool CUserDefinedLogic::RegCBFun()
{   	 
    REG_GOBAL_MEMBER_FUNC( "CUserDefinedLogic::InitWnd", CUserDefinedLogic::InitWnd, m_pLogic, CUserDefinedLogic);
    REG_GOBAL_MEMBER_FUNC( "CUserDefinedLogic::BtnSaveToFileClick", CUserDefinedLogic::BtnSaveToFileClick, m_pLogic, CUserDefinedLogic ) ; 

    REG_GOBAL_MEMBER_FUNC( "CUserDefinedLogic::OnDefinedItemClick", CUserDefinedLogic::OnDefinedItemClick, m_pLogic, CUserDefinedLogic ) ; 
    REG_GOBAL_MEMBER_FUNC( "CUserDefinedLogic::OnDefinedItemIconClick", CUserDefinedLogic::OnDefinedItemIconClick, m_pLogic, CUserDefinedLogic ) ; 
    
    REG_GOBAL_MEMBER_FUNC( "CUserDefinedLogic::OnFuncLstItemClick", CUserDefinedLogic::OnFuncLstItemClick, m_pLogic, CUserDefinedLogic ) ; 
    

    REG_GOBAL_MEMBER_FUNC( "CUserDefinedLogic::BtnToUserDefinedClick", CUserDefinedLogic::BtnToUserDefinedClick, m_pLogic, CUserDefinedLogic ) ; 

    REG_GOBAL_MEMBER_FUNC( "CUserDefinedLogic::BtnSaveClick", CUserDefinedLogic::BtnSaveClick, m_pLogic, CUserDefinedLogic ) ; 

    REG_GOBAL_MEMBER_FUNC( "CUserDefinedLogic::BtnTCancleClick", CUserDefinedLogic::BtnCancleClick ,m_pLogic, CUserDefinedLogic ) ; 
    
    REG_GOBAL_MEMBER_FUNC( "CUserDefinedLogic::BeginEditSysTime", CUserDefinedLogic::BeginEditSysTime ,m_pLogic, CUserDefinedLogic ) ; 
    
	REG_GOBAL_MEMBER_FUNC( "CUserDefinedLogic::BtnSwitchClick", CUserDefinedLogic::BtnSwitchClick, m_pLogic, CUserDefinedLogic ) ;
    
    //hour Add
    REG_GOBAL_MEMBER_FUNC( "CUserDefinedLogic::BtnAddHourClick", CUserDefinedLogic::BtnAddHourClick ,m_pLogic, CUserDefinedLogic ) ; 
     
    //DeleteHour
    REG_GOBAL_MEMBER_FUNC( "CUserDefinedLogic::BtnDeleteHourClick", CUserDefinedLogic::BtnDeleteHourClick ,m_pLogic, CUserDefinedLogic ) ; 
     
    //min Add
    REG_GOBAL_MEMBER_FUNC( "CUserDefinedLogic::BtnAddMinClick", CUserDefinedLogic::BtnAddMinClick ,m_pLogic, CUserDefinedLogic ) ; 
     
    //min delete
    REG_GOBAL_MEMBER_FUNC( "CUserDefinedLogic::BtnDeleteMinClick", CUserDefinedLogic::BtnDeleteMinClick ,m_pLogic, CUserDefinedLogic ) ; 
     
    //点击日历
    REG_GOBAL_MEMBER_FUNC( "CUserDefinedLogic::BtnCalendarClick", CUserDefinedLogic::BtnCalendarClick ,m_pLogic, CUserDefinedLogic ) ; 
   
	REG_GOBAL_MEMBER_FUNC( "CUserDefinedLogic::OnCalendarDateChange", CUserDefinedLogic::OnCalendarDateChange ,m_pLogic, CUserDefinedLogic ) ; 
    
    REG_GOBAL_MEMBER_FUNC( "CUserDefinedLogic::BtnSyncTimeToServClick", CUserDefinedLogic::BtnSyncTimeToServClick ,m_pLogic, CUserDefinedLogic ) ; 
    
    REG_GOBAL_MEMBER_FUNC( "CUserDefinedLogic::EdtMinOnChar", CUserDefinedLogic::EdtMinOnChar ,m_pLogic, CUserDefinedLogic ) ; 
    REG_GOBAL_MEMBER_FUNC( "CUserDefinedLogic::EdtHourOnChar", CUserDefinedLogic::EdtHourOnChar ,m_pLogic, CUserDefinedLogic ) ; 
    
    return true;
}

bool CUserDefinedLogic::UnRegFunc()
{
    //	UN_REG_GOBAL_FUNC( "CConftempEdtLogic::InitWnd" );
    return true;
}


bool CUserDefinedLogic::InitWnd(  const IArgs & arg )
{   
    CWndLogicBase::InitWnd( arg );
    InitUserDefinedLst();
    UIManagePtr->LoadScheme(  m_SchmUserDefined , m_pWndTree );
    
    UpdateSysTime();


	TLockScreenInfo tInfo  = UIDATAMGR->GetLockScreenInfo(); 
	UIManagePtr->GetSwitchState( m_stcStrSwitchBtnScreenPswd, tInfo.bOpen, m_pWndTree );
	String strPsw;
    UIManagePtr->GetCaption( m_stcStrEdtScreenPswd, strPsw, m_pWndTree );
	tInfo.strPswd.Format( "%s", strPsw.c_str() );
	String strName;
	UIManagePtr->GetCaption( m_stcStrEdtSysName, strName, m_pWndTree );
	tInfo.strSysName.Format( "%s", strName.c_str() );
	UIDATAMGR->SetLockScreenInfo( tInfo );	
    

    UpdateFuncList();
   
    
    CFuncLstMenu::Instance()->Init( m_pLogic, &m_vctTConfMenu);

    Value_WindowOwer val;
    val.pWnd = m_pWndTree->GetItemData()->pWnd;
    UIManagePtr->SetPropertyValue( val, g_stcStrFuncLstManageMenu );
    
    return true;
}

// set m_vctTConfMenu
void CUserDefinedLogic::SetMenuLst( vector<TConfMenuInfo> *pLst )
{
    if ( pLst == NULL )
    {
        return;
    }
   //sxc 20120614
    m_vctTConfMenu = *pLst;

//     m_vctTConfMenu.clear();
//     vector<TConfMenuInfo>::iterator it = pLst->begin();
//     while ( it != pLst->end() )
//     {
//         m_vctTConfMenu.push_back( *it );
//         it ++;
//     }
}

void CUserDefinedLogic::Clear()
{  
    if ( m_pWndTree )
    {
        UIManagePtr->LoadScheme(  m_SchmUserDefined , m_pWndTree , "", false );
        UIManagePtr->ShowWindow( g_stcStrUserdefinedDlg, false );
    }
   

}

//初始化自定义配置菜单
void CUserDefinedLogic::InitUserDefinedLst()
{   
    TMenuItemInfo tMenu;
    ARRAY<String> vcItem;
    vcItem.push_back( "ImageItemUserdinfed" );
    tMenu.m_pVctSubItem = &vcItem;
    
    
    ARRAY<TMenuItemInfo> menuLst; 
    tMenu.strItemFunc = "CUserDefinedLogic::OnDefinedItemClick";

    tMenu.strTxt = m_stcStrSysName;
    menuLst.push_back( tMenu );
    
    tMenu.strTxt = m_stcStrScreenPswd;
    menuLst.push_back( tMenu );


//     tMenu.strTxt = m_stcStrSysTime;
//     menuLst.push_back( tMenu ); 

    tMenu.strTxt = m_stcStrFuncLst;
    menuLst.push_back( tMenu );  
    
    Value_TouchListMenu val( &menuLst );
    UIManagePtr->SetPropertyValue( val, m_stcStrLstUserDefined, m_pWndTree );
}



bool CUserDefinedLogic::BtnSaveToFileClick( const IArgs & arg )
{
    return  UIManagePtr->SaveToFile(  g_stcStrUserdefinedDlg  );   
}


//点击自定义列表条目
bool CUserDefinedLogic::OnDefinedItemClick( const IArgs & arg )
{ 
    if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast< const Args_ClickItemInfo*>(&arg))
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetItemData();        
        if ( const Data_Menu *pItemInfo = dynamic_cast<const Data_Menu*>( pBaseItem->GetUserData() )) 
        {   
            ShowSubDlg( pItemInfo->m_tMenuInfo.strTxt ); 
        } 
    }
    return true;
}

bool CUserDefinedLogic::OnFuncLstItemClick( const IArgs & arg )
{
    if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast< const Args_ClickItemInfo*>(&arg))
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetItemData();        
        if ( const Data_ConfMenu *pItemInfo = dynamic_cast<const Data_ConfMenu*>( pBaseItem->GetUserData() )) 
        {   
             //m_wCnsID = pData->m_wData; 
            CFuncLstMenu::Instance()->SetCusSelItem( pItemInfo->m_tConfMenuInfo );
            CRect rect = const_cast<CRect&>(pClickInfo->m_rcFrame);
            
            //在此rect的左下角显示弹出菜单 
            Value_WindowPos val; 
            val.nX = rect.right;
            val.nY = rect.top; 
            
            Value_WindowSize valSize;
            UIManagePtr->GetPropertyValue( valSize, g_stcStrFuncLstManageMenu );
            
            Value_WindowPos valLargerBottom;
            UIManagePtr->GetPropertyValue( valLargerBottom, g_stcStrMainMenuDlg  );
            
            if ( val.nY + valSize.nHeight >= valLargerBottom.nY )
            {   
                val.nY = rect.bottom -  valSize.nHeight;
                UIManagePtr->LoadScheme( "SchmImgEx", NULL, g_stcStrFuncLstManageMenu, false ); 
            }
            else
            {
                UIManagePtr->LoadScheme( "SchmImgNormal", NULL, g_stcStrFuncLstManageMenu, false );
            }


            UIManagePtr->SetPropertyValue(val,g_stcStrFuncLstManageMenu);
            UIManagePtr->ShowWindow(g_stcStrFuncLstManageMenu);
        } 
    }
    return true ;
}

bool CUserDefinedLogic::OnDefinedItemIconClick( const IArgs & arg )
{

    if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast< const Args_ClickItemInfo*>(&arg))
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetParentItem()->GetItemData();        
        if ( const Data_Menu *pItemInfo = dynamic_cast<const Data_Menu*>( pBaseItem->GetUserData() )) 
        {   
            ShowSubDlg( pItemInfo->m_tMenuInfo.strTxt ); 
        } 
    }
    return true;
}

void  CUserDefinedLogic::ShowSubDlg( String StrDlgName )
{
    if ( StrDlgName == m_stcStrSysName )
    {     
        m_emConfigType = emConfigSysName;
        SaveSysNameDlg(FALSE);
        UIManagePtr->LoadScheme( m_SchmSysName, m_pWndTree ); 
		UIManagePtr->SetFocus( "BtnSave", m_pWndTree );
    }
    else if ( StrDlgName == m_stcStrSysTime)
    {
        m_emConfigType = emConfigSysTime;
        m_bCouldUpdateTime = TRUE;
        UIManagePtr->LoadScheme( m_SchmSysTime, m_pWndTree );
        UIManagePtr->SetFocus( m_stcStrBtnCalender, m_pWndTree );
        UpdateSysTime();
    }
    else if ( StrDlgName == m_stcStrScreenPswd)
    {
        m_emConfigType = emConfigScreenPswd;
        SaveScreenPswdDlg(FALSE);
        UIManagePtr->LoadScheme( m_SchmScreenPswd, m_pWndTree );
		UIManagePtr->SetFocus( "BtnSave", m_pWndTree );
   }
    else if ( StrDlgName == m_stcStrFuncLst)
    {
        SetMenuLst( UIManagePtr->GetConfMenu() );
        m_emConfigType = emConfigFuncLst;
        //SaveFuncLstDlg(FALSE);   //sxc 20120614 duplicate
        UIManagePtr->LoadScheme( m_SchmFuncLst, m_pWndTree );
        InitFuncLst();
        UpdateFuncList();  
        
    }
   
}

//点击转到自定义界面
bool CUserDefinedLogic::BtnToUserDefinedClick( const IArgs & arg )
{  
    //IArgs *p = NULL ;
    //BtnSaveClick( *p );
    UIManagePtr->LoadScheme( m_SchmUserDefined, m_pWndTree );
    return true;
}

//点击了保存按钮
bool CUserDefinedLogic::BtnSaveClick( const IArgs & arg )
{
   switch( m_emConfigType )
   {
   case emConfigScreenPswd:
       SaveScreenPswdDlg();
       break;
   case emConfigSysName:
       SaveSysNameDlg();
       break;
   case emConfigSysTime:
       SaveSysTimeDlg();
       break;
   case emConfigFuncLst:
      SaveFuncLstDlg();
      break;
   default:
       break;
       
   }
   m_bCouldUpdateTime = TRUE;
   return true;
}

// 开始编辑系统时间
bool CUserDefinedLogic::BeginEditSysTime( const IArgs & arg )
{
   m_bCouldUpdateTime = FALSE;
   return true;
}


//点击了取消按钮
bool CUserDefinedLogic::BtnCancleClick( const IArgs & arg )
{   
    m_bCouldUpdateTime = TRUE;
    switch( m_emConfigType )
    {
    case emConfigScreenPswd:
        SaveScreenPswdDlg(FALSE);
        break;
    case emConfigSysName:
        SaveSysNameDlg(FALSE);
        break;
    case emConfigSysTime:
        SaveSysTimeDlg(FALSE);
        break;
    case emConfigFuncLst:
       SaveFuncLstDlg(FALSE);
       break;
    default:
        break;
        
    }
    
   
   return true;
}

void CUserDefinedLogic::SaveSysNameDlg( BOOL32 bSave /*= TRUE*/ )
{    
    if ( bSave )
    {
        String str;
        UIManagePtr->GetCaption( m_stcStrEdtSysName, str, m_pWndTree );

        CLoginLogic::GetLogicPtr()->SaveSysNameToFile( str  );
        UIManagePtr->SaveToFile( g_stcStrUserdefinedDlg ,/*m_stcStrEdtSysName*/"EdtSysName", "WindowCaption", TRUE );
        
        if( !UIDATAMGR->IsPcVersion() )//tpad版本发送消息给pad进行系统名保存 dyy 2013年8月29日
        {
           u16 wRet = BusinessManagePtr->SetTpadSysName( str );
           if (wRet != NO_ERROR)
           {
               Args_MsgBox msgArg;
               msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( m_stcStrEdtSysName, m_pWndTree );
               MSG_BOX( "系统名称设置失败", FALSE, &msgArg );
           }
        }

		TLockScreenInfo tInfo = UIDATAMGR->GetLockScreenInfo(); 
		tInfo.strSysName.Format( "%s", str.c_str() );
		UIDATAMGR->SetLockScreenInfo( tInfo );
    }
    else
    {  
//         UIManagePtr->LoadScheme( "", m_pWndTree , m_stcStrDlgSysName  );
//         UIManagePtr->ShowWindow( m_stcStrDlgSysName,TRUE, m_pWndTree); 
		TLockScreenInfo tInfo;
		tInfo = UIDATAMGR->GetLockScreenInfo();
		UIManagePtr->SetCaption( m_stcStrEdtSysName, (LPCTSTR)tInfo.strSysName, m_pWndTree );
    } 
    
}


void CUserDefinedLogic::SaveScreenPswdDlg(  BOOL32 bSave/* = TRUE */ )
{
    if ( bSave )
    {
        UIManagePtr->SaveToFile( g_stcStrUserdefinedDlg, m_stcStrEdtScreenPswd, "WindowCaption", TRUE );
        UIManagePtr->SaveToFile( g_stcStrUserdefinedDlg, m_stcStrSwitchBtnScreenPswd, "SwitchState", TRUE );

		TLockScreenInfo tInfo  = UIDATAMGR->GetLockScreenInfo(); 
		UIManagePtr->GetSwitchState( m_stcStrSwitchBtnScreenPswd, tInfo.bOpen, m_pWndTree );
		String strPsw;
		UIManagePtr->GetCaption( m_stcStrEdtScreenPswd, strPsw, m_pWndTree );
		tInfo.strPswd.Format( "%s", strPsw.c_str() );
		UIDATAMGR->SetLockScreenInfo( tInfo );
    }
    else
    {
        //UIManagePtr->LoadScheme( "", m_pWndTree , m_stcStrDlgScreenPswd  );
		//UIManagePtr->ShowWindow( m_stcStrDlgScreenPswd, TRUE, m_pWndTree);
		TLockScreenInfo tInfo;
		tInfo = UIDATAMGR->GetLockScreenInfo();
		UIManagePtr->SetSwitchState( m_stcStrSwitchBtnScreenPswd, tInfo.bOpen, m_pWndTree );
		if ( !tInfo.bOpen )
		{
			UIManagePtr->LoadScheme( "SchmScreenPswdOff", m_pWndTree , m_stcStrDlgScreenPswd );
		}
		else
		{
			UIManagePtr->LoadScheme( "SchmScreenPswdOn", m_pWndTree , m_stcStrDlgScreenPswd );
		}
		UIManagePtr->SetCaption( m_stcStrEdtScreenPswd, (LPCTSTR)tInfo.strPswd, m_pWndTree );
    }    
}

bool CUserDefinedLogic::BtnSwitchClick( const IArgs& args )
{
	TLockScreenInfo tInfo  = UIDATAMGR->GetLockScreenInfo(); 
	UIManagePtr->GetSwitchState( m_stcStrSwitchBtnScreenPswd, tInfo.bOpen, m_pWndTree );
	if ( !tInfo.bOpen )
	{
		UIManagePtr->LoadScheme( "SchmScreenPswdOff", m_pWndTree , m_stcStrDlgScreenPswd );
	}
	else
	{
		UIManagePtr->LoadScheme( "SchmScreenPswdOn", m_pWndTree , m_stcStrDlgScreenPswd );
	}
    return true;
}

void CUserDefinedLogic::SaveSysTimeDlg( BOOL32 bSave /*= TRUE */ )
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
        sscanf( str.c_str(),"%d",&time.wHour);
        if ( time.wHour > 23 || time.wHour < 0 )
        {
           MSG_BOX( "小时为 0 ~ 23 间的整数", FALSE, &arg );
		   UIManagePtr->SetFocus( m_stcStrEdtHour, m_pWndTree );
           return ;
        }
        
        
        UIManagePtr->GetCaption( m_stcStrEdtMin, str,m_pWndTree );
        sscanf( str.c_str(),"%d",&time.wMinute); 
        if ( time.wMinute > 59 || time.wMinute < 0 )
        {
            MSG_BOX ( "分钟为 0 ~ 59 间的整数", FALSE, &arg );
			UIManagePtr->SetFocus( m_stcStrEdtMin, m_pWndTree );
            return ;
        }


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
 


void CUserDefinedLogic::SaveFuncLstDlg( BOOL32 bSave/* = TRUE */)
{
    if ( bSave )
    {  
        UIManagePtr->SaveConfMenu(  m_vctTConfMenu );
        CMsgDispatch::SendMessage( WM_CMS_UPDATE_CONFMENU, 0, 0 );
    }
    else
    {
        SetMenuLst( UIManagePtr->GetConfMenu() );
        UpdateFuncList();
    }

}



void  CUserDefinedLogic::UpdateSysTime()
{
    SYSTEMTIME sysTime;
	::GetLocalTime( &sysTime );
    OnUpdateSysTime( (WPARAM)&sysTime, 0 );
}

//show function list
void CUserDefinedLogic::UpdateFuncList()
{    

    Value_VerListConfMenu val( &m_vctTConfMenu ,"CUserDefinedLogic::OnFuncLstItemClick");
    UIManagePtr->SetPropertyValue( val, m_stcStrLstFunc, m_pWndTree );
}

void CUserDefinedLogic::InitFuncLst()
{
    //设置无偏移量，无选中项 
    SetFuncLstOffset( 0 );
        
    
    //设置当前没有选中项  
    SetFuncLstSel( -1 );
}


void CUserDefinedLogic::SetFuncLstOffset( int nOffset )
{
    //设置无偏移量，无选中项 
    Value_TransparentListOffset val;
    val.nOffset = nOffset;
    UIManagePtr->SetPropertyValue( val, m_stcStrLstFunc, m_pWndTree );
}

void CUserDefinedLogic::SetFuncLstSel( int nIndex )
{ 
    //设置当前没有选中项  
    Value_TransparentListSelItem valSel;
    valSel.dwDataKey =  nIndex;
	UIManagePtr->SetPropertyValue( valSel, m_stcStrLstFunc, m_pWndTree);
}


//wparam: SYSTEMTIME
HRESULT CUserDefinedLogic::OnUpdateSysTime( WPARAM wparem, LPARAM lparem )
{
    if ( m_pWndTree == NULL ||  !IsCouldUpdate() )
    {
        return NO_ERROR;
    }

   SYSTEMTIME time = * reinterpret_cast< SYSTEMTIME *>(wparem);
   s8 buf[20] = { 0 };
   sprintf( buf, "%d年%d月%d日",time.wYear, time.wMonth, time.wDay );

   UIManagePtr->SetCaption( m_stcStrEdtDate, buf ,m_pWndTree );
  
   sprintf( buf, "%.2d",time.wHour );
   UIManagePtr->SetCaption( m_stcStrEdtHour, buf ,m_pWndTree );

   sprintf( buf, "%.2d",time.wMinute );
   UIManagePtr->SetCaption( m_stcStrEdtMin, buf ,m_pWndTree ); 

   return NO_ERROR;
}

//是否可以更新，如果当前正处在编辑状态则不更新，否则就更新
BOOL32 CUserDefinedLogic::IsCouldUpdate()
{
    return m_bCouldUpdateTime;
}


//hour Add
bool CUserDefinedLogic::BtnAddHourClick( const IArgs & arg )
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
bool CUserDefinedLogic::BtnDeleteHourClick( const IArgs & arg )
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
bool CUserDefinedLogic::BtnAddMinClick( const IArgs & arg )
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
bool CUserDefinedLogic::BtnDeleteMinClick( const IArgs & arg )
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
bool CUserDefinedLogic::BtnCalendarClick( const IArgs & arg )
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
    owerVal.pWnd = UIManagePtr->GetWindowPtr( g_stcStrUserdefinedDlg );
    UIManagePtr->SetPropertyValue( owerVal, "CalendarDlg");
    
    UIManagePtr->ShowWindow( "CalendarDlg", true );
    return true;
}


bool CUserDefinedLogic::OnCalendarDateChange( const IArgs & args )
{
	Args_WindowMsg WinMsg = *dynamic_cast<const Args_WindowMsg*>(&args);
	WindowMsg msg = WinMsg.m_Msg;
	
	CString strDate = *(CString*)(msg.wParam);
    UIManagePtr->SetCaption( m_stcStrEdtDate, (LPCTSTR)strDate, m_pWndTree );
	m_bCouldUpdateTime = FALSE;
	return true;
}

 
//点击时间同步
bool CUserDefinedLogic::BtnSyncTimeToServClick( const IArgs & arg )
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

bool  CUserDefinedLogic::EdtMinOnChar( const IArgs & arg )
{
     m_bCouldUpdateTime = FALSE;
     return true;
}

bool  CUserDefinedLogic::EdtHourOnChar( const IArgs & arg )
{
     m_bCouldUpdateTime = FALSE;
     return true;
}


u16 CUserDefinedLogic::SyncTimeToServ( const SYSTEMTIME sysTime  )
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