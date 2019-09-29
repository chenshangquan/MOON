// simulateCnsLogic.cpp: implementation of the CSimulateCnsLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cms.h"
#include "simulateCnsLogic.h"
#include "scrnDisplayMenuLogic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSimulateCnsLogic *CSimulateCnsLogic::m_pLogic = NULL;
 
 
TScreenInfoEx CSimulateCnsLogic::m_screenInfoArry[MAX_SCREEN_COUNT] ; 
TSeatInfoEx CSimulateCnsLogic::m_seatInfoArry[MAX_SEAT_COUNT] ;	
String CSimulateCnsLogic::m_BtnScreenArry[MAX_SEAT_COUNT];
const String CSimulateCnsLogic::m_strConfTitle = "stcConfTitle";
 
const String  CSimulateCnsLogic::m_strSchmActive = "SchmActive";                   //激活方案
const String  CSimulateCnsLogic::m_strSchmUnActive = "SchmUnActive";  
const String  CSimulateCnsLogic::m_strSchnCancleView = "SchmCancleSelView";              //未激活

const String  CSimulateCnsLogic::m_strSwitchBtnScrn1 = "btnSwithcScreen1";                   //
const String  CSimulateCnsLogic::m_strSwitchBtnScrn2 = "btnSwithcScreen2";
const String  CSimulateCnsLogic::m_strSwitchBtnScrn3 = "btnSwithcScreen3";

CSimulateCnsLogic::CSimulateCnsLogic():m_byCurSpokesSeatID( 0xFF )
{ 
	m_screenInfoArry[0].strCtlScreen =  "stcScreen1";
	m_screenInfoArry[0].strCtlScreenState = "stcScreen1State";
	m_screenInfoArry[0].strCtlCnsName =  "stcScreenName1";

	m_screenInfoArry[1].strCtlScreen =  "stcScreen2";
	m_screenInfoArry[1].strCtlScreenState = "stcScreen2State";
	m_screenInfoArry[1].strCtlCnsName = "stcScreenName2";

	m_screenInfoArry[2].strCtlScreen =  "stcScreen3";
	m_screenInfoArry[2].strCtlScreenState =  "stcScreen3State";
	m_screenInfoArry[2].strCtlCnsName = "stcScreenName3";

	m_screenInfoArry[3].strCtlScreen =   "stcScreen4";
	m_screenInfoArry[3].strCtlScreenState =  "stcScreen4State";
	m_screenInfoArry[3].strCtlCnsName = "stcScreenName4";

	m_screenInfoArry[4].strCtlScreen =  "stcScreen5";
	m_screenInfoArry[4].strCtlScreenState = "stcScreen5State";
	m_screenInfoArry[4].strCtlCnsName = "stcScreenName5";


	m_seatInfoArry[0].strCtrlSeat = "stcSpoksman1";
	m_seatInfoArry[0].strCtrlSpoksBtn = "btnSetSpokesman1";		

	m_seatInfoArry[1].strCtrlSeat = "stcSpoksman2";
	m_seatInfoArry[1].strCtrlSpoksBtn = "btnSetSpokesman2";	

	m_seatInfoArry[2].strCtrlSeat = "stcSpoksman3";
	m_seatInfoArry[2].strCtrlSpoksBtn = "btnSetSpokesman3";	

	m_BtnScreenArry[0] = "btnSwithcScreen1";
	m_BtnScreenArry[1] = "btnSwithcScreen2";
	m_BtnScreenArry[2] = "btnSwithcScreen3";

	m_bInConf = FALSE;
	m_bySelScreenID = -1;
}

CSimulateCnsLogic::~CSimulateCnsLogic()
{
	if ( m_pLogic != NULL )
	{   
		UnRegMsg();
		UnRegFunc();
		delete m_pLogic;
		m_pLogic = NULL;
	}
}


CSimulateCnsLogic* CSimulateCnsLogic::GetLogicPtr()
{
	if ( m_pLogic == NULL )
	{  
		m_pLogic = new CSimulateCnsLogic();  
	}
	
	return m_pLogic;
}


void CSimulateCnsLogic::RegMsg()
{     
	REG_MSG_HANDLER( UI_CNS_CONFSTATE_NOTIFY, CSimulateCnsLogic::OnConfStateNotify, m_pLogic, CSimulateCnsLogic );
    REG_MSG_HANDLER( UI_UMS_UPDATE_CONFINFO, CSimulateCnsLogic::OnConfStateNotify, m_pLogic, CSimulateCnsLogic );
    REG_MSG_HANDLER( UI_UMS_REFRESH_CONFCNS_LIST, CSimulateCnsLogic::OnConfStateNotify, m_pLogic, CSimulateCnsLogic );
	REG_MSG_HANDLER( UI_CNS_CNSINFO_NOTIFY, CSimulateCnsLogic::OnConfStateNotify, m_pLogic, CSimulateCnsLogic );

//	REG_MSG_HANDLER( UI_CNS_SCREEN_NAME_NOTIFY, CSimulateCnsLogic::OnScreenNameNotify ,m_pLogic, CSimulateCnsLogic); 废弃，改用UI_CNS_SCREEN_STATE_NOTIFY 2012-3-15 yjj
	REG_MSG_HANDLER( UI_CNS_SCREEN_STATE_NOTIFY, CSimulateCnsLogic::OnScreenStateNotify ,m_pLogic, CSimulateCnsLogic);
  
    
    REG_MSG_HANDLER( UI_CNS_SPOKES_SEAT_NOTIFY, CSimulateCnsLogic::OnSpokesManNotify ,m_pLogic, CSimulateCnsLogic);	
}

void CSimulateCnsLogic::UnRegMsg()
{
 
}

bool CSimulateCnsLogic::RegCBFun()
{   	 
	REG_GOBAL_MEMBER_FUNC( "CSimulateCnsLogic::InitWnd", CSimulateCnsLogic::InitWnd, m_pLogic, CSimulateCnsLogic ) ;

	REG_GOBAL_MEMBER_FUNC( "CSimulateCnsLogic::BtnSetSpokesman1Click", CSimulateCnsLogic::BtnSetSpokesman1Click, m_pLogic, CSimulateCnsLogic );
	REG_GOBAL_MEMBER_FUNC( "CSimulateCnsLogic::BtnSetSpokesman2Click", CSimulateCnsLogic::BtnSetSpokesman2Click, m_pLogic, CSimulateCnsLogic ) ;
	REG_GOBAL_MEMBER_FUNC( "CSimulateCnsLogic::BtnSetSpokesman3Click", CSimulateCnsLogic::BtnSetSpokesman3Click, m_pLogic, CSimulateCnsLogic ) ;
	
    //REG_GOBAL_MEMBER_FUNC( "CSimulateCnsLogic::OnIconCnsLstAddClick", CSimulateCnsLogic::OnIconCnsLstAddClick, m_pLogic, CSimulateCnsLogic ) ;
    //选看
    REG_GOBAL_MEMBER_FUNC( "CSimulateCnsLogic::BtnSrcn1Click", CSimulateCnsLogic::BtnSrcn1Click, m_pLogic, CSimulateCnsLogic ) ;
    REG_GOBAL_MEMBER_FUNC( "CSimulateCnsLogic::BtnSrcn2Click", CSimulateCnsLogic::BtnSrcn2Click, m_pLogic, CSimulateCnsLogic ) ;
    REG_GOBAL_MEMBER_FUNC( "CSimulateCnsLogic::BtnSrcn3Click", CSimulateCnsLogic::BtnSrcn3Click, m_pLogic, CSimulateCnsLogic ) ;
    
    
	return true;
}

bool CSimulateCnsLogic::UnRegFunc()
{
	UN_REG_GOBAL_FUNC( "CSimulateCnsLogic::InitWnd" );
	return true;
}


bool CSimulateCnsLogic::InitWnd( const IArgs & arg )
{   
	CWndLogicBase::InitWnd( arg ); 

	BOOL32 bInConf = BusinessManagePtr->IsInConf( NULL );
	if ( bInConf )
	{
		BOOL32 bPIP = BusinessManagePtr->IsViewLocalPIP();		//判断是否开启画中画
		if ( bPIP )
		{
			UIManagePtr->LoadScheme( "SchmLocalPIP", NULL , UIDATAMGR->GetCurSimulateDlgName() );
		}
		else
		{
			UIManagePtr->LoadScheme( "SchmNoLocalPIP", NULL, UIDATAMGR->GetCurSimulateDlgName() );
		}
		RefreshCnsScreen();
		RefreshSpeakSeat(); 
	}
	else
	{
		UIManagePtr->SetCaption( UIDATAMGR->GetCurSimulateDlgName() + "/" + m_strConfTitle, "" );
		UIManagePtr->LoadScheme( "SchmNotInConf", NULL, UIDATAMGR->GetCurSimulateDlgName() );
	}
	
	return true;
}


HRESULT CSimulateCnsLogic::OnConfStateNotify( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
    {  
        PrtMsg(0,emEventTypeCmsWindow,"[CSimulateCnsLogic::OnConfStateNotify]: m_pWndTree=NULL  return" );
        return NO_ERROR;
    }
 

    TCMSConf tConfInfo ;
	BOOL32 bInConf = BusinessManagePtr->IsInConf( &tConfInfo ); 
     
	if ( bInConf )
	{		 
        if ( tConfInfo.m_emConfType == emCallType_Conf )
        {
            UIManagePtr->SetCaption( UIDATAMGR->GetCurSimulateDlgName() + "/" + m_strConfTitle, tConfInfo.m_achConfName );
        } 
		else
		{
			UIManagePtr->SetCaption( UIDATAMGR->GetCurSimulateDlgName() + "/" + m_strConfTitle, "" );
		}
		BOOL32 bPIP = BusinessManagePtr->IsViewLocalPIP();		//判断是否开启画中画
		String strDlg = UIDATAMGR->GetCurSimulateDlgName();
		if ( strDlg == "SimulateCns1Dlg" )
		{
			strDlg += "/btnSwithcScreen1";
		} 
		else
		{
			strDlg += "/btnSwithcScreen2";
		}
		UIManagePtr->LoadScheme( "SchmInConf", NULL, UIDATAMGR->GetCurSimulateDlgName() );
		if ( bPIP )
		{
			UIManagePtr->LoadScheme( "SchmLocalPIP", NULL , strDlg );
		}
        RefreshCnsScreen();
		RefreshSpeakSeat();
		m_bInConf = TRUE;
	}
	else
    {   	    
		UIManagePtr->SetCaption( UIDATAMGR->GetCurSimulateDlgName() + "/" + m_strConfTitle, "" );
		UIManagePtr->LoadScheme( "SchmNotInConf", NULL, UIDATAMGR->GetCurSimulateDlgName() );
        
		if ( m_bInConf )
		{   
			CScrnDisplayMenuLogic::GetLogicPtr()->HideMenu();
			BusinessManagePtr->ClearCnsScreenInfo();
		}
		m_bInConf = FALSE;
	}
	return NO_ERROR;
}


//屏名更改通知
HRESULT CSimulateCnsLogic::OnScreenNameNotify( WPARAM wparam, LPARAM lparam )
{ 
	if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }

	u8 byScreenId = (u8)wparam;
	if ( byScreenId < 0 || byScreenId >= MAX_SCREEN_COUNT )
	{
		return ERR_CMS;
	}

	//更改屏名    
	String strName = (s8*)lparam; 

	TTPCnsInfo tCnsInfo;
	ComInterface->GetLocalCnsInfo( tCnsInfo );
	if ( tCnsInfo.m_emLevel == emTPSipProvince )
	{
		UIManagePtr->SetCaption( UIDATAMGR->GetCurSimulateDlgName() + "/" + m_screenInfoArry[byScreenId + 1].strCtlCnsName, strName, NULL, TRUE );
	}
	else
	{
		UIManagePtr->SetCaption( UIDATAMGR->GetCurSimulateDlgName() + "/" + m_screenInfoArry[byScreenId].strCtlCnsName, strName, NULL, TRUE );
	}
    
	return NO_ERROR;
}

//屏状态更改通知
HRESULT CSimulateCnsLogic::OnScreenStateNotify( WPARAM wparam, LPARAM lparam)
{ 
	if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }
 

	vector<TScreenInfo> vctScreenInfo;
	BusinessManagePtr->GetCnsScreenInfo( vctScreenInfo );

	for ( int i = 0; i < vctScreenInfo.size(); i++ )
	{
		TScreenInfo tInfo = vctScreenInfo.at(i);
		if ( tInfo.byScreenID == (u16)wparam )
		{
			//更改屏的状态图标 
			UpdateScreenState( tInfo );
			break;
		}
	}
	
	return NO_ERROR;
}

//发言人更改通知
HRESULT CSimulateCnsLogic::OnSpokesManNotify( WPARAM wparam, LPARAM lparam)
{  
	if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }

    RefreshSpeakSeat();
    return S_OK;

     

    TCMSConf  tConfInfo;
	BOOL32 bInConf = BusinessManagePtr->IsInConf( &tConfInfo );
	if ( !bInConf  || emCallType_P2P == tConfInfo.m_emConfType)
	{
		return NO_ERROR;
	}

	//更新坐席的图标，发言坐席设为绿色边框，其余无边框
	u8 bySeatId = (u8)wparam;

    if ( 0xff == bySeatId  )
    {//三个坐席全亮
        UIManagePtr->LoadScheme( "SchmSeatSpk", NULL,  UIDATAMGR->GetCurSimulateDlgName() );
    }
    else
    {//先把三个坐席都置为非亮的
        UIManagePtr->LoadScheme( "SchmSeatNotSpk", NULL, UIDATAMGR->GetCurSimulateDlgName()  );
    }

	if ( bySeatId < 0 || bySeatId >= MAX_SEAT_COUNT )
	{
		return NO_ERROR;
	}
	
	//获取上一次发言人坐席ID，如果和wSeatID不同，则设置原发言人为非发言人
    if( m_byCurSpokesSeatID == bySeatId )
	{
		return NO_ERROR;
	}

	if ( m_byCurSpokesSeatID != 0xFF )
	{
	//	UIManagePtr->EnableWindow( UIDATAMGR->GetCurSimulateDlgName() + "/" + m_seatInfoArry[m_byCurSpokesSeatID].strCtrlSpoksBtn, true );
		UIManagePtr->LoadScheme( "SchmSeatNotSpk", NULL, UIDATAMGR->GetCurSimulateDlgName() + "/" + m_seatInfoArry[m_byCurSpokesSeatID].strCtrlSeat );
	}	

//	UIManagePtr->EnableWindow( UIDATAMGR->GetCurSimulateDlgName() + "/" + m_seatInfoArry[bySeatId].strCtrlSpoksBtn, false );
	UIManagePtr->LoadScheme( "SchmSeatSpk", NULL,  UIDATAMGR->GetCurSimulateDlgName() + "/" + m_seatInfoArry[bySeatId].strCtrlSeat );
		
	m_byCurSpokesSeatID = bySeatId;
	return NO_ERROR;
}



void CSimulateCnsLogic::UpdateScreenState( TScreenInfo tInfo )
{
	u8 byScreenId = tInfo.byScreenID;
   	if ( byScreenId >= MAX_SCREEN_COUNT )
    {
		return;
	}

    TTPCnsInfo tCnsInfo;
    ComInterface->GetLocalCnsInfo( tCnsInfo );

    //更新屏名 去掉回放时的后缀 dyy 2013年9月2日
    String strCnsName = tInfo.achCnsName;
    string::size_type wIndex = strCnsName.find("_255_");
    if ( wIndex != string::npos )
    {
        strCnsName = strCnsName.substr( 0, wIndex );
    } 

    if ( tCnsInfo.m_emLevel == emTPSipProvince )
    {
        UIManagePtr->SetCaption( UIDATAMGR->GetCurSimulateDlgName() + "/" + m_screenInfoArry[byScreenId + 1].strCtlCnsName, strCnsName, NULL, TRUE );
    }
    else
    {
        UIManagePtr->SetCaption( UIDATAMGR->GetCurSimulateDlgName() + "/" + m_screenInfoArry[byScreenId].strCtlCnsName, strCnsName, NULL, TRUE );
	}

   
    
    //更新屏状态
    String strSchm = "";
    switch( tInfo.emPosPic )
    {
        case emPic_SelView:  
            strSchm = "SchmScrnSelCns";
            break;//选看远端 
        case emPic_SelDual: 
            strSchm = "SchmScrnSelDual";
            break;//选看双流
        case emPic_SelLocal:   
            strSchm = "SchmScrnSelLocal";
            break;//选看本地
		case emPic_SelTVS:  
            strSchm = "SchmScrnSelTVS";
            break;//选看电视墙
        default:
            strSchm = "SchmNotInConf";
            break;
    }

    

    if ( !strSchm.empty() )
    {
        if ( tCnsInfo.m_emLevel == emTPSipProvince )
        {
            UIManagePtr->LoadScheme( strSchm, NULL, UIDATAMGR->GetCurSimulateDlgName() + "/" + m_screenInfoArry[ byScreenId + 1 ].strCtlScreenState );
        }
        else
        {
            UIManagePtr->LoadScheme( strSchm, NULL, UIDATAMGR->GetCurSimulateDlgName() + "/" + m_screenInfoArry[ byScreenId ].strCtlScreenState );
        }
    }
/*
    
    String strSchm;
	String strBtnSchm;
    if ( tInfo.emScreenState == emPosAcitve )
    {		
		if ( tInfo.emPosPic == emPic_SelView )
		{
			strSchm = m_strSchnCancleView;
		}
		else
		{
			strSchm = m_strSchmActive;
		}
		strBtnSchm = m_strSchmActive;
    }
    else
    {		
        strSchm = m_strSchmUnActive;
		strBtnSchm = m_strSchmUnActive;
    }

	TTPCnsInfo tCnsInfo;
	ComInterface->GetLocalCnsInfo( tCnsInfo );
	if ( tCnsInfo.m_emLevel == emTPSipProvince )
	{
		UIManagePtr->LoadScheme( strSchm, NULL, UIDATAMGR->GetCurSimulateDlgName() + "/" + m_screenInfoArry[byScreenID + 1].strCtlScreenState );
	}
	else
	{
        UIManagePtr->LoadScheme( strSchm, NULL, UIDATAMGR->GetCurSimulateDlgName() + "/" + m_screenInfoArry[byScreenID].strCtlScreenState );
	}
	UIManagePtr->LoadScheme( strBtnSchm, NULL, UIDATAMGR->GetCurSimulateDlgName() + "/" + m_BtnScreenArry[byScreenID] );
*/

     
}

void CSimulateCnsLogic::RefreshCnsScreen()
{
	vector<TScreenInfo> vctScreenInfo;
	BusinessManagePtr->GetCnsScreenInfo( vctScreenInfo );

	TTPCnsInfo tCnsInfo;
	BusinessManagePtr->GetLocalCnsInfo( tCnsInfo );

	for ( int i = 0; i < vctScreenInfo.size(); i++ )
	{		
		u8 byScreenId = vctScreenInfo[i].byScreenID;
		String strName = vctScreenInfo[i].achCnsName;
		EmTPPosStatus emState = vctScreenInfo[i].emScreenState;
		EMPosPic emPosPoc = vctScreenInfo[i].emPosPic;  
		 
		if ( tCnsInfo.m_emLevel == emTPSipProvince )
		{
			UIManagePtr->SetCaption( UIDATAMGR->GetCurSimulateDlgName() + "/" +  m_screenInfoArry[byScreenId + 1].strCtlCnsName, strName );			
			
		}
		else
		{
			UIManagePtr->SetCaption( UIDATAMGR->GetCurSimulateDlgName() + "/" +  m_screenInfoArry[byScreenId].strCtlCnsName, strName );
			
		}

        UpdateScreenState( vctScreenInfo[i] );
		
	}
}	


void CSimulateCnsLogic::RefreshSpeakSeat()
{
	u8 bySeatId = BusinessManagePtr->GetCnsInnerSpeaker();

    TCMSConf  tConfInfo;
    BOOL32 bInConf = BusinessManagePtr->IsInConf( &tConfInfo );
    if ( !bInConf  )
    {
        return ;
    } 
     
	//2014.5.6  B3中没有语音激励,根据发言席别直接来改变状态-----Bug00181156
//  TTPCnsConfStatus status = BusinessManagePtr->GetLocalCnsConfState();

//  if ( status.m_bMixMotive )
//     {  
        UIManagePtr->LoadScheme( "SchmHideSpokeBtn", NULL, UIDATAMGR->GetCurSimulateDlgName()  );
        if ( CN_INNERSPEAKER_ALL == bySeatId  )
        {	//三个坐席全亮
            UIManagePtr->LoadScheme( "SchmSeatSpk", NULL,  UIDATAMGR->GetCurSimulateDlgName() );
        }
        else if( CN_INNERSPEAKER_NONE == bySeatId )
		{
			//全不亮
			UIManagePtr->LoadScheme( "SchmSeatNotSpk", NULL, UIDATAMGR->GetCurSimulateDlgName()  );
		}
		else
        {	//先把三个坐席都置为非亮的
            UIManagePtr->LoadScheme( "SchmSeatNotSpk", NULL, UIDATAMGR->GetCurSimulateDlgName()  );

            if ( bySeatId < 0 || bySeatId >= MAX_SEAT_COUNT )
            {
                return  ;
            } 
            
            UIManagePtr->LoadScheme( "SchmSeatSpk", NULL,  UIDATAMGR->GetCurSimulateDlgName() + "/" + m_seatInfoArry[bySeatId].strCtrlSeat );
        }
        
        
//     }
//     else
//     {
//          
//         UIManagePtr->LoadScheme( "SchmSeatNotSpk", NULL, UIDATAMGR->GetCurSimulateDlgName()  );
//         //B3一直不显示切换发言坐席的button  -2014.4.17 xcr
//         //UIManagePtr->LoadScheme( "SchmShowSpokeBtn", NULL, UIDATAMGR->GetCurSimulateDlgName()  );
// 
//         if ( bySeatId < 0 || bySeatId >= MAX_SEAT_COUNT )
//         {
//             return  ;
//         }
//         UIManagePtr->LoadScheme( "SchmSeatSpk", NULL,  UIDATAMGR->GetCurSimulateDlgName() + "/" + m_seatInfoArry[bySeatId].strCtrlSeat );
//         
//         UIManagePtr->LoadScheme( "SchmSeatSpk", NULL,  UIDATAMGR->GetCurSimulateDlgName() + "/" + m_seatInfoArry[bySeatId].strCtrlSpoksBtn ); 
//         
//     }
    
   

    /*
	for ( int i = 0; i < MAX_SEAT_COUNT; i++ )
	{
		if ( bySeatId == i )
		{
			UIManagePtr->EnableWindow( UIDATAMGR->GetCurSimulateDlgName() + "/" + m_seatInfoArry[bySeatId].strCtrlSpoksBtn, false );
			UIManagePtr->LoadScheme( "SchmInConfAndSel", NULL,  UIDATAMGR->GetCurSimulateDlgName() + "/" + m_seatInfoArry[bySeatId].strCtrlSeat );
			m_byCurSpokesSeatID = bySeatId;
		}
		else
		{
			UIManagePtr->EnableWindow(  UIDATAMGR->GetCurSimulateDlgName() + "/" + m_seatInfoArry[i].strCtrlSpoksBtn, true );
			UIManagePtr->LoadScheme( "SchmInConf", NULL, UIDATAMGR->GetCurSimulateDlgName() + "/" + m_seatInfoArry[i].strCtrlSeat );
		}		
	}
    */
}


 
bool CSimulateCnsLogic::BtnSetSpokesman1Click( const IArgs & arg )
{
	u16 wRet = BusinessManagePtr->SetCnsInnerSpeaker( 0 );

	return true;
}

bool CSimulateCnsLogic::BtnSetSpokesman2Click( const IArgs & arg )
{
	u16 wRet = BusinessManagePtr->SetCnsInnerSpeaker( 1 );

	return true;
}

bool CSimulateCnsLogic::BtnSetSpokesman3Click( const IArgs & arg )
{  
	u16 wRet = BusinessManagePtr->SetCnsInnerSpeaker( 2 );

	return true;
}

bool CSimulateCnsLogic::GetPosFrmArg( const IArgs & arg , CPoint &pos)
{
    const Args_WindowMsg *pMsg =  dynamic_cast<const Args_WindowMsg*>(&arg) ;
    
    HWND hwnd  = pMsg->m_Msg.hwnd;
    if ( hwnd != NULL )
    {
       CRect rc;
       ::GetWindowRect( hwnd, &rc ); 
       pos = rc.BottomRight();

       return true;
    }
    return false;
}

bool CSimulateCnsLogic::BtnSrcn1Click( const IArgs & arg )
{   
    CScrnDisplayMenuLogic::GetLogicPtr()->HideMenu();
    CPoint pos;
    bool re = GetPosFrmArg( arg , pos);
    if (re )
    {    
        bool bOn = false;
        UIManagePtr->GetSwitchState(  UIDATAMGR->GetCurSimulateDlgName() + "/" + m_strSwitchBtnScrn1, bOn   );
        if ( bOn  )
        {    
            Value_SwitchBtnBindWnd valueBindWnd;
            valueBindWnd.strWndName = g_stcStrScrnDisplayMenu;
            UIManagePtr->SetPropertyValue( valueBindWnd, UIDATAMGR->GetCurSimulateDlgName() + "/" + m_strSwitchBtnScrn1 );
            CScrnDisplayMenuLogic::GetLogicPtr()->ShowMenu( 0, pos );
        } 
        
    } 
    return true;
}

bool CSimulateCnsLogic::BtnSrcn2Click( const IArgs & arg )
{
    CScrnDisplayMenuLogic::GetLogicPtr()->HideMenu();
    CPoint pos;
    bool re = GetPosFrmArg( arg , pos);
    if (re )
    {    
        bool bOn = false;
        UIManagePtr->GetSwitchState(  UIDATAMGR->GetCurSimulateDlgName() + "/" + m_strSwitchBtnScrn2, bOn   );
        if ( bOn  )
        {    
            Value_SwitchBtnBindWnd valueBindWnd;
            valueBindWnd.strWndName = g_stcStrScrnDisplayMenu;
            UIManagePtr->SetPropertyValue( valueBindWnd, UIDATAMGR->GetCurSimulateDlgName() + "/" + m_strSwitchBtnScrn2 );
            CScrnDisplayMenuLogic::GetLogicPtr()->ShowMenu( 1, pos );
        }
    } 
    return true;
}

bool CSimulateCnsLogic::BtnSrcn3Click( const IArgs & arg )
{
    CScrnDisplayMenuLogic::GetLogicPtr()->HideMenu();
    CPoint pos;
    bool re = GetPosFrmArg( arg , pos);
    if (re )
    { 
        bool bOn = false;
        UIManagePtr->GetSwitchState(  UIDATAMGR->GetCurSimulateDlgName() + "/" + m_strSwitchBtnScrn3, bOn   );
        if ( bOn )
        {    
            Value_SwitchBtnBindWnd valueBindWnd;
            valueBindWnd.strWndName = g_stcStrScrnDisplayMenu;
            UIManagePtr->SetPropertyValue( valueBindWnd, UIDATAMGR->GetCurSimulateDlgName() + "/" + m_strSwitchBtnScrn3 );
            CScrnDisplayMenuLogic::GetLogicPtr()->ShowMenu( 2, pos );
        }
    } 
    return true;
}


void CSimulateCnsLogic::Clear()
{
	UIManagePtr->SetCaption( UIDATAMGR->GetCurSimulateDlgName() + "/" + m_strConfTitle, "" );
    UIManagePtr->LoadScheme( "SchmNotInConf", NULL, UIDATAMGR->GetCurSimulateDlgName() );
    UIManagePtr->ShowWindow( UIDATAMGR->GetCurSimulateDlgName(), false );
    m_bInConf = FALSE;
}

  




