// confCtrlLogic.cpp: implementation of the CConfCtrlLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cms.h"
#include "confCtrlLogic.h"
#include "msgBoxLogic.h"
#include "valueStorage.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CConfCtrlLogic *CConfCtrlLogic::m_pLogic = NULL;
u16 CConfCtrlLogic::m_wCnsID = TP_INVALID_INDEX;
//TCnsInfo CConfCtrlLogic::m_tCnsInfo;    //该操作单元要操作的cns信息，包含该cns对应的静音，哑音 等状态 状态，该结构体由confCnsLstLogic单元进行赋值和更新
u16 CConfCtrlLogic::m_wConfID = TP_INVALID_INDEX;    
TConfCallEpAddrList CConfCtrlLogic::m_tEqAddrLst;
EM_CallType CConfCtrlLogic::m_emCallTp = emCallTpCfTemp;


static UINT g_nTimerHdl;   //timer 的id ，用于关闭计时器使用  

VOID  CALLBACK  CBTmPoc( HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime )
{
    if ( idEvent == g_nTimerHdl )
    {
        KillTimer( NULL, g_nTimerHdl );

        Value_WindowOwer owerVal;
        owerVal.pWnd = UIManagePtr->GetWindowPtr( g_stcStrCnsLstDlg );
        UIManagePtr->SetPropertyValue(owerVal, g_stcStrConfCnsCtrlDlg);

        CConfCtrlLogic::GetLogicPtr()->AdjustMenuPos(); 
        UIManagePtr->ShowWindow( g_stcStrConfCnsCtrlDlg, true );
    }
}


CConfCtrlLogic::CConfCtrlLogic():m_rectClickItem()
{
    m_strConfCnsCtrlDlg = g_stcStrConfCnsCtrlDlg;
}

CConfCtrlLogic::~CConfCtrlLogic()
{

    if ( m_pLogic != NULL )
    {   
        UnRegMsg();
        UnRegFunc();
        delete m_pLogic;
        m_pLogic = NULL;
	}
}



CConfCtrlLogic* CConfCtrlLogic::GetLogicPtr()
{
    if ( m_pLogic == NULL )
    {  
        m_pLogic = new CConfCtrlLogic();  
    }
    
    return m_pLogic;
}


void CConfCtrlLogic::RegMsg()
{     
    //点击会议中会场cns
    REG_MSG_HANDLER( UI_CONF_CNS_ITEM_CLICK, CConfCtrlLogic::OnConfCnsItemClick, m_pLogic, CConfCtrlLogic ) ; 
   
    //点击会议模板中的条目
    REG_MSG_HANDLER( UI_CONF_TEMP_ITEM_CLICK, CConfCtrlLogic::OnConfTempItemClick, m_pLogic, CConfCtrlLogic ) ; 
    REG_MSG_HANDLER( UI_ADDR_ITEM_CALL_CLICK, CConfCtrlLogic::OnAddrItemCallClick, m_pLogic, CConfCtrlLogic );

    REG_MSG_HANDLER( UI_UMS_CHANGE_SPEAKER_NOTIFY,CConfCtrlLogic::OnSetSpeakerCnsRsp , m_pLogic, CConfCtrlLogic  );
    //REG_MSG_HANDLER( UI_UMS_SET_SPEAKER_RSP,CConfCtrlLogic::OnSetSpeakerCnsRsp , m_pLogic, CConfCtrlLogic  );
    REG_MSG_HANDLER( UI_UMS_SET_MUTE_CNS_RSP,CConfCtrlLogic::OnSetMuteCnsRsp , m_pLogic, CConfCtrlLogic  );
    REG_MSG_HANDLER( UI_UMS_SET_QUIET_CNS_RSP,CConfCtrlLogic::OnSetQuietCnsRsp , m_pLogic, CConfCtrlLogic  );
    REG_MSG_HANDLER( UI_UMS_SET_DUAL_CNS_RSP,CConfCtrlLogic::OnSetDualCnsRsp , m_pLogic, CConfCtrlLogic  );
    REG_MSG_HANDLER( UI_UMS_DUAL_CNS_NOTIFY,CConfCtrlLogic::OnDualCnsNotify , m_pLogic, CConfCtrlLogic  ); 


    REG_MSG_HANDLER( UI_UMS_UPDATE_CONFINFO, CConfCtrlLogic::OnConfStateNotify, m_pLogic, CConfCtrlLogic  );
    REG_MSG_HANDLER( UI_UMS_REFRESH_CONFCNS_LIST, CConfCtrlLogic::OnConfCnsListNotify, m_pLogic, CConfCtrlLogic )
}

void CConfCtrlLogic::UnRegMsg()
{
    //UNREG_MSGHANDLER(  UI_UMS_START_CONFTEMPLATE_RSP ); 
}

bool CConfCtrlLogic::RegCBFun()
{   	 
    REG_GOBAL_MEMBER_FUNC( "CConfCtrlLogic::InitWnd", CConfCtrlLogic::InitWnd, m_pLogic, CConfCtrlLogic ) ; 
    REG_GOBAL_MEMBER_FUNC( "CConfCtrlLogic::OnHungupConfClick", CConfCtrlLogic::OnHungupConfClick, m_pLogic, CConfCtrlLogic ) ; 
    REG_GOBAL_MEMBER_FUNC( "CConfCtrlLogic::OnHungupCnsClick", CConfCtrlLogic::OnHungupCnsClick, m_pLogic, CConfCtrlLogic ) ; 
    REG_GOBAL_MEMBER_FUNC( "CConfCtrlLogic::OnCallClick", CConfCtrlLogic::OnCallClick, m_pLogic, CConfCtrlLogic ) ; 

    //cns 控制项
    REG_GOBAL_MEMBER_FUNC( "CConfCtrlLogic::OnSetSpokeCnsClick", CConfCtrlLogic::OnSetSpokeCnsClick, m_pLogic, CConfCtrlLogic ) ;
    REG_GOBAL_MEMBER_FUNC( "CConfCtrlLogic::OnSetMuteClick", CConfCtrlLogic::OnSetMuteClick, m_pLogic, CConfCtrlLogic ) ;
    REG_GOBAL_MEMBER_FUNC( "CConfCtrlLogic::OnSetUnMuteClick", CConfCtrlLogic::OnSetUnMuteClick, m_pLogic, CConfCtrlLogic ) ;
    REG_GOBAL_MEMBER_FUNC( "CConfCtrlLogic::OnSetQuietClick", CConfCtrlLogic::OnSetQuietClick, m_pLogic, CConfCtrlLogic ) ;
    REG_GOBAL_MEMBER_FUNC( "CConfCtrlLogic::OnSetUnQuietClick", CConfCtrlLogic::OnSetUnQuietClick, m_pLogic, CConfCtrlLogic ) ;
    REG_GOBAL_MEMBER_FUNC( "CConfCtrlLogic::OnStartDualClick", CConfCtrlLogic::OnStartDualClick, m_pLogic, CConfCtrlLogic ) ;
    REG_GOBAL_MEMBER_FUNC( "CConfCtrlLogic::OnStopDualClick", CConfCtrlLogic::OnStopDualClick, m_pLogic, CConfCtrlLogic ) ;

    REG_GOBAL_MEMBER_FUNC( "CConfCtrlLogic::HungupCns", CConfCtrlLogic::HungupCns, m_pLogic, CConfCtrlLogic ) ;
    
    //REG_GOBAL_MEMBER_FUNC( "CConfCtrlLogic::BtnSave2File", CConfCtrlLogic::BtnSave2File, m_pLogic, CConfCtrlLogic ) ; 
    //REG_GOBAL_MEMBER_FUNC( "CConfCtrlLogic::BtnSaveConfCnsMenu2FileClick", CConfCtrlLogic::BtnSaveConfCnsMenu2FileClick, m_pLogic, CConfCtrlLogic ) ; 
    //REG_GOBAL_MEMBER_FUNC( "CConfCtrlLogic::CloseConfCnsMenuDlg", CConfCtrlLogic::CloseConfCnsMenuDlg, m_pLogic, CConfCtrlLogic ) ; 

    REG_GOBAL_MEMBER_FUNC( "CConfCtrlLogic::UserDefinedFun", CConfCtrlLogic::UserDefinedFun, m_pLogic, CConfCtrlLogic ) ;
    
    return true;
}

bool CConfCtrlLogic::UnRegFunc()
{
   
    return true;
}


bool CConfCtrlLogic::InitWnd(  const IArgs & arg )
{   
    CWndLogicBase::InitWnd( arg ); 
    
    return true;
 }


void CConfCtrlLogic::Clear()
{
    m_wCnsID = TP_INVALID_INDEX;     //要操作的cns的ID
    m_wConfID = TP_INVALID_INDEX;    //对应的会议ID 
    
	m_tTPAlias.Clear();
    m_tEqAddrLst.m_wConfID = INVALID_WORD;
    m_tEqAddrLst.m_tEpAdrLst.m_wNum = 0;
    m_emCallTp = emCallTpCfTemp;  
  
	UIManagePtr->ShowWindow( g_stcStrCallDlg, false );
    UIManagePtr->ShowWindow( g_stcStrCnsLstDlg, false );
	UIManagePtr->ShowWindow( g_stcStrConfCnsCtrlDlg , false );
    UIManagePtr->ShowWindow( "ConfCnsCtrlSpeakerDlg", false );
}


HRESULT CConfCtrlLogic::OnConfStateNotify( WPARAM wParam, LPARAM lParam )
{
	BOOL  be = BusinessManagePtr->IsInConf();
	if ( !be )
	{
		UIManagePtr->ShowWindow( g_stcStrCallDlg, false );
		UIManagePtr->ShowWindow( g_stcStrConfCnsCtrlDlg , false );
        UIManagePtr->ShowWindow( "ConfCnsCtrlSpeakerDlg", false );
	}

	return S_OK;
} 


HRESULT CConfCtrlLogic::OnConfCnsListNotify( WPARAM wParam, LPARAM lParam )
{
    TCMSConf tConf;
    BOOL bInConf = BusinessManagePtr->IsInConf( &tConf );
    if ( !bInConf )
    {
        UIManagePtr->ShowWindow( g_stcStrCallDlg, false );
		UIManagePtr->ShowWindow( m_strConfCnsCtrlDlg , false );
    }
    else
    {
        //当弹出框的会场在线状态变化时，同时刷新弹出框
        if ( m_wCnsID != TP_INVALID_INDEX )
        {
            TCnsInfo *ptCnsInfo = tConf.GetCnsInfoByID( m_wCnsID ); 
            if ( ptCnsInfo == NULL )
            {
                m_wCnsID = TP_INVALID_INDEX;
                UIManagePtr->ShowWindow( g_stcStrCallDlg, false );
		        UIManagePtr->ShowWindow( m_strConfCnsCtrlDlg , false );
                return NO_ERROR;
            } 

            if ( ptCnsInfo->m_bOnline )
            {
                if ( UIManagePtr->IsVisible( g_stcStrCallDlg ) )
                {
                    m_wCnsID = TP_INVALID_INDEX;
                    UIManagePtr->ShowWindow( g_stcStrCallDlg, false );

                    Value_TransparentListSelItem valSel;
                    valSel.dwDataKey = -1;
                    UIManagePtr->SetPropertyValue( valSel, g_stcStrCnsLstDlg + "/LstCns" );
                }
            }
            else
            {
                if ( UIManagePtr->IsVisible( m_strConfCnsCtrlDlg ) )
                {
                    m_wCnsID = TP_INVALID_INDEX;
                    UIManagePtr->ShowWindow( m_strConfCnsCtrlDlg, false );

                    Value_TransparentListSelItem valSel;
                    valSel.dwDataKey = -1;
                    UIManagePtr->SetPropertyValue( valSel, g_stcStrCnsLstDlg + "/LstCns" );
                }
            }
        }
    }

    return NO_ERROR;
}

 

bool CConfCtrlLogic::BtnSave2File( const IArgs & arg )
{
    return  UIManagePtr->SaveToFile( g_stcStrCallDlg  );  
}



void CConfCtrlLogic::SetCallInfo( u16 wCnsID, u16 wConfID/* = INVALID_WORD*/)
{ 
   // memcpy( &m_tCnsInfo, &tCnsInfo, sizeof(TCnsInfo) ); 
    m_wCnsID = wCnsID;
    m_wConfID = wConfID;
    if ( m_wConfID == INVALID_WORD )
    {  
        TCMSConf cmsConf;
        BOOL32 bRe = BusinessManagePtr->IsInConf(&cmsConf);
        if (  bRe )
        {
            m_wConfID = cmsConf.m_wConfID;
        }
 
        
    } 
}


void CConfCtrlLogic::SetCallInfo( u16 wConfID /*= INVALID_WORD*/ )
{  
    m_emCallTp = emCallTpCfTemp; 
    m_wConfID = wConfID;
    if ( m_wConfID == INVALID_WORD )
    {  
        TCMSConf cmsConf;
        BusinessManagePtr->IsInConf(&cmsConf);
        m_wConfID = cmsConf.m_wConfID;
    }
}

void CConfCtrlLogic::SetCallInfo( TEpAddrList &tEqAddrLst )
{ 	  
    m_tEqAddrLst.m_tEpAdrLst = tEqAddrLst;
}

void CConfCtrlLogic::SetCallInfo( TConfCallEpAddrList  &tEqAddrLst )
{
   m_tEqAddrLst = tEqAddrLst;
}

void CConfCtrlLogic::SetCallInfo( TTPAlias &tAlias )
{
	m_emCallTp = emCallTpCfTemp; 
	m_tTPAlias = tAlias;
}


bool CConfCtrlLogic::OnCallClick( const IArgs & arg )
{  
    bool bVis = UIManagePtr->IsVisible( g_stcStrCallDlg );
    if ( !bVis )
    {
        return false;
    }

	u16 wRe = NO_ERROR;
 	TCMSConf tConfInfo;
  	BOOL32 bIsInconf = BusinessManagePtr->IsInConf(&tConfInfo); 
    UIManagePtr->ShowWindow( g_stcStrCallDlg, false ); 

   
	if ( bIsInconf && m_emCallTp == emCallTpCfTemp )
	{
		ShowPopMsg( "已经在会议中" );
		return false;	
    }  

	switch ( m_emCallTp )
	{
	case emCallTpCfTemp:
		{  
            BusinessManagePtr->SetCurConfName( "" );
			
			TTPCnsInfo tCnsInfo;
            BusinessManagePtr->GetLocalCnsInfo( tCnsInfo );
            if( strlen( tCnsInfo.m_achRoomName ) == 0 )
            {  
                Args_MsgBox msgArg; 
                msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( g_stcStrConftempDlg );
                //MSG_BOX( "开启会议失败：本地会场不在线", FALSE  , &msgArg );
                MSG_BOX_POST( "开启会议失败：本地会场不在线", FALSE, &msgArg );
                return false;
			}
            
		    wRe = BusinessManagePtr->StartTemplateConf( m_tTPAlias );
            if ( wRe == NO_ERROR )
            {   
                //呼叫时隐藏界面
                UIManagePtr->ShowWindow( g_stcStrConftempDlg , false );
                //2011-9-5 添加呼叫中状态
                CMsgDispatch::SendMessage( UI_UMS_SHOW_CALLING_DLG ,0 , 0 );  
                
                //TTPConfTemplate* pTemp = BusinessManagePtr->GetConfTemplateByID(m_wConfID);
                //if ( pTemp != NULL )
                //{
                //    BusinessManagePtr->SetCurConfTemplate( *pTemp  );
                //}               
            }

            m_tTPAlias.Clear();
        }      
		break;
	case emCallTpInstantCf: 
		{   
			CString strErr;
			TTPCallSerInfo tCallSerInfo;
			ComInterface->GetCallServerInfo(tCallSerInfo);
			if ( tCallSerInfo.dwCallServiceIP == NULL ) 
			{
				strErr.Format( "呼叫失败：未配置呼叫服务器" );
				ShowPopMsg( strErr );
				return false;
		    }

            TTPCnsInfo tCnsInfo;
            BusinessManagePtr->GetLocalCnsInfo( tCnsInfo );
            if( strlen( tCnsInfo.m_achRoomName ) == 0 )
            {  
                Args_MsgBox msgArg; 
                msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( g_stcStrAddrbookDlg );
                //MSG_BOX( "开启会议失败：本地会场不在线", FALSE  , &msgArg );
				MSG_BOX_POST( "开启会议失败：本地会场不在线", FALSE, &msgArg );
                return false;
			}

            //检查呼叫的是不是本地会场
            /*if ( m_tEqAddrLst.m_tEpAdrLst.m_wNum == 1)
            {   
                if ( (m_tEqAddrLst.m_tEpAdrLst.m_tCnsList[0].m_tAlias.m_byType == tp_Alias_h323 && 
					   strcmp( m_tEqAddrLst.m_tEpAdrLst.m_tCnsList[0].m_tAlias.m_abyAlias ,tCnsInfo.m_achRoomName ) == 0  ) ||
					 (m_tEqAddrLst.m_tEpAdrLst.m_tCnsList[0].m_tAlias.m_byType == tp_Alias_e164 &&  
					   strcmp( m_tEqAddrLst.m_tEpAdrLst.m_tCnsList[0].m_tAlias.m_abyAlias ,tCnsInfo.m_achE164 ) == 0  ) )
                {    
                     Args_MsgBox msgArg; 
                     msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( g_stcStrAddrbookDlg );
                     //MSG_BOX( "不能呼叫本地会场", FALSE  , &msgArg );
					 MSG_BOX_POST( "不能呼叫本地会场", FALSE, &msgArg );
                     return false;
                }
            }*/

			TCMSConf tConf;
			BOOL32 bIsInconf = BusinessManagePtr->IsInConf( &tConf );
			if ( bIsInconf  )
			{
				//B3版本 点对点会议转换多点会议
				if ( tConf.m_emConfType == emCallType_P2P )
				{
                    //检查呼叫的是否是本地会场,防止点对点转多点时，出现会场控制界面
					if ( m_tEqAddrLst.m_tEpAdrLst.m_wNum == 1) 
					{  
						TTPCnsInfo tCnsInfo;  
						BusinessManagePtr->GetLocalCnsInfo( tCnsInfo );
						if ( (strlen(m_tEqAddrLst.m_tEpAdrLst.m_tCnsList[0].m_tAlias.m_abyAlias) > 0 &&
							strcmp( m_tEqAddrLst.m_tEpAdrLst.m_tCnsList[0].m_tAlias.m_abyAlias, tCnsInfo.m_achRoomName ) == 0) || 
							(strlen(m_tEqAddrLst.m_tEpAdrLst.m_tCnsList[0].m_tE164.m_abyAlias) > 0 &&
							strcmp( m_tEqAddrLst.m_tEpAdrLst.m_tCnsList[0].m_tE164.m_abyAlias, tCnsInfo.m_achE164 ) == 0) )
						{    
							Args_MsgBox msgArg; 
							msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( g_stcStrAddrbookDlg );
							MSG_BOX_POST( "不能呼叫本地会场", FALSE, &msgArg );
							return false;
						}
					}

				    //检查呼叫的是否是对端会场，防止会场控制界面出现多余164号的同一不在线会场
					CString strErr;

					TTPCnsConfStatus status = ComInterface->GetLocalCnsConfState();

					if ( strcmp(status.achConfName,m_tEqAddrLst.m_tEpAdrLst.m_tCnsList[0].m_tAlias.m_abyAlias) == 0 )
					{
						strErr.Format( "会场 %s 已在本会议中", status.achConfName );
						ShowPopMsg( strErr );
						return false;
					}
				}			
			}
 
	    	wRe = BusinessManagePtr->StartInstantConf( m_tCnAddrList );
            if ( wRe == NO_ERROR )
            { 
                UIManagePtr->ShowWindow( g_stcStrAddrbookDlg, false );
                //2011-9-5 添加呼叫中状态
                CMsgDispatch::SendMessage( UI_UMS_SHOW_CALLING_DLG ,0 , 0 );  
            }

            m_tCnAddrList.clear();
        }
        
		break;
	case emCallTpInvitCns: 
        {
			if ( !bIsInconf )
			{
				return false; 
			}
            //检查呼叫的是不是本地会场 
            if ( m_tEqAddrLst.m_tEpAdrLst.m_wNum == 1) 
            {  
                TTPCnsInfo tCnsInfo;  
                BusinessManagePtr->GetLocalCnsInfo( tCnsInfo );
               // if ( strcmp( m_tEqAddrLst.m_tEpAdrLst.m_tCnsList[0].m_tAlias.m_abyAlias ,tCnsInfo.m_achRoomName ) == 0 )
				if ( (strlen(m_tEqAddrLst.m_tEpAdrLst.m_tCnsList[0].m_tAlias.m_abyAlias) > 0 &&
					strcmp( m_tEqAddrLst.m_tEpAdrLst.m_tCnsList[0].m_tAlias.m_abyAlias, tCnsInfo.m_achRoomName ) == 0) || 
					(strlen(m_tEqAddrLst.m_tEpAdrLst.m_tCnsList[0].m_tE164.m_abyAlias) > 0 &&
					strcmp( m_tEqAddrLst.m_tEpAdrLst.m_tCnsList[0].m_tE164.m_abyAlias, tCnsInfo.m_achE164 ) == 0) )
                {    
                    Args_MsgBox msgArg; 
                    msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( g_stcStrAddrbookDlg );
                    //MSG_BOX( "不能呼叫本地会场", FALSE  , &msgArg );
					MSG_BOX_POST( "不能呼叫本地会场", FALSE, &msgArg );
                    return false;
                }
            }

			//邀请入会时过滤掉已在会议中的会场
			CString strErr;
			TConfCallEpAddrList tConfAddrList;
			TEpAddrList tEqAddrLst;
			for ( int i =0; i < m_tEqAddrLst.m_tEpAdrLst.m_wNum; i++ )
			{
				TEpAddr tEpAddr = m_tEqAddrLst.m_tEpAdrLst.m_tCnsList[i];

				TCnsInfo* ptCnsInfo = tConfInfo.GetCnsInfoByAlias( tEpAddr.m_tAlias.m_abyAlias );
				if ( ptCnsInfo != NULL )
				{
					if ( ptCnsInfo->m_bOnline )
					{
						strErr.Format( "会场 %s 已在本会议中", tEpAddr.m_tAlias.m_abyAlias );
						ShowPopMsg( strErr );
						continue;
					}
					else
					{
						//存在但不在线的，使用EpID呼叫，防止列表出现相同条目
						TConfEpID tEp;
						tEp.m_wConfID =  tConfInfo.m_wConfID;
						tEp.m_wEpID = ptCnsInfo->m_wEpID;
						wRe =  BusinessManagePtr->CallConfCns( tEp );  
						continue;
					}
				}

				//会场只有E164号时,会场名字的处理	----JYY  2014.7.10
				EmConfAddEpRet emRet = TP_ConfAddEpRet_Unknow;
				if ( tEpAddr.m_tE164.m_byType == tp_Alias_e164 && strlen( tEpAddr.m_tE164.m_abyAlias ) > 0 )
				{
					emRet = tEqAddrLst.Add( tEpAddr.m_tE164.m_byType, tEpAddr.m_tE164.m_abyAlias );
				} 
				else if ( tEpAddr.m_tAlias.m_byType == tp_Alias_h323 && strlen( tEpAddr.m_tAlias.m_abyAlias ) > 0 )
				{	
					emRet = tEqAddrLst.Add( tEpAddr.m_tAlias.m_byType, tEpAddr.m_tAlias.m_abyAlias );	
				}

				if ( emRet != TP_ConfAddEpRet_Success )
				{
					continue;
				}				
			}

			if ( tEqAddrLst.m_wNum > 0 )
			{
				tConfAddrList.m_tEpAdrLst = tEqAddrLst;
				tConfAddrList.m_wConfID = tConfInfo.m_wConfID;
				
				wRe =  BusinessManagePtr->InviteCns( tConfAddrList );  
			}
			  
            m_tEqAddrLst.Clear();
        }		
		
		break;
    case emCallTpCallConfCns:
        {
            TConfEpID tEp;
            tEp.m_wConfID = m_wConfID;
            tEp.m_wEpID = m_wCnsID;
            wRe =  BusinessManagePtr->CallConfCns(tEp);  
            m_wConfID = TP_INVALID_INDEX;
            m_wCnsID = TP_INVALID_INDEX;

        }
        break;
    case emCallTpPtp:
        {
            TTPCnsInfo tCnsInfo;
            BusinessManagePtr->GetLocalCnsInfo( tCnsInfo );
            if( strlen( tCnsInfo.m_achRoomName ) == 0 )
            {  
                Args_MsgBox msgArg; 
                msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( g_stcStrAddrbookDlg );
                //MSG_BOX( "开启会议失败：本地会场不在线", FALSE  , &msgArg );
				//msgArg.pOwnerWnd->SetFocus();
                MSG_BOX_POST( "开启会议失败：本地会场不在线", FALSE, &msgArg );
                return false;
            }
            
            //检查呼叫的是不是本地会场           
            /*if ( m_tEqAddrLst.m_tEpAdrLst.m_wNum == 1)
            {   
                //if ( strcmp( m_tEqAddrLst.m_tEpAdrLst.m_tCnsList[0].m_tAlias.m_abyAlias ,tCnsInfo.m_achRoomName ) == 0 )
				if ( (m_tEqAddrLst.m_tEpAdrLst.m_tCnsList[0].m_tAlias.m_byType == tp_Alias_h323 && 
					strcmp( m_tEqAddrLst.m_tEpAdrLst.m_tCnsList[0].m_tAlias.m_abyAlias ,tCnsInfo.m_achRoomName ) == 0  ) ||
					(m_tEqAddrLst.m_tEpAdrLst.m_tCnsList[0].m_tAlias.m_byType == tp_Alias_e164 &&  
					   strcmp( m_tEqAddrLst.m_tEpAdrLst.m_tCnsList[0].m_tAlias.m_abyAlias ,tCnsInfo.m_achE164 ) == 0  ) )
                {    
                    Args_MsgBox msgArg; 
                    msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( g_stcStrAddrbookDlg );
                    //MSG_BOX( "不能呼叫本地会场", FALSE, &msgArg );
					//msgArg.pOwnerWnd->SetFocus();
                    //POSTMESSAGE之后Domodal,防止焦点错误
                    MSG_BOX_POST( "不能呼叫本地会场", FALSE, &msgArg );
                    return false;
                }
            }*/
            
            if ( (strlen( m_tCallAddr.achAlias ) > 0 && strcmp( m_tCallAddr.achAlias, tCnsInfo.m_achRoomName ) == 0 ) ||
                 (strlen( m_tCallAddr.achE164 ) > 0 && strcmp( m_tCallAddr.achE164, tCnsInfo.m_achE164 ) == 0 ) )
            {
                Args_MsgBox msgArg; 
                msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( g_stcStrAddrbookDlg );
                MSG_BOX_POST( "不能呼叫本地会场", FALSE, &msgArg );
                return false;
            }
                            
            BusinessManagePtr->SetCurConfName( "" );

            wRe = BusinessManagePtr->MakeCall( m_tCallAddr );
            //wRe = BusinessManagePtr->MakeCall( m_tEqAddrLst.m_tEpAdrLst.m_tCnsList[0].m_tAlias );
            if ( wRe == NO_ERROR )
            { 
                 UIManagePtr->ShowWindow( g_stcStrAddrbookDlg, false );
                //2011-9-5 添加呼叫中状态
                CMsgDispatch::SendMessage( UI_UMS_SHOW_CALLING_DLG ,0 , 0 );  
                
                BusinessManagePtr->SetCurConfName( PTP_CONF );
            }
            
            m_tEqAddrLst.Clear();
        }
        break;
	}
	

	if ( wRe != NO_ERROR )
	{
		HANDLE_ERROR(wRe); 
	}

	return true;
}

/* wParam =  wConfTempID
	lparam = 所单击的item相对于屏幕的rect*/
HRESULT  CConfCtrlLogic::OnConfTempItemClick( WPARAM wparam, LPARAM lparam )
{
	IArgs* pArgs = (IArgs*)wparam;
	if ( Args_ClickItemInfo *pClickInfo =  dynamic_cast<Args_ClickItemInfo*>(pArgs) )
    {
        const IData *pIData = pClickInfo->m_pClickList->GetItemData()->GetUserData();
        if ( const Data_ConfTemp * pDataTemp = dynamic_cast< const Data_ConfTemp*>(pIData) )
        { 
			TTPAlias tAlias = pDataTemp->m_tConfTemp;
			CRect rect = pClickInfo->m_rcFrame;
			SetCallInfo( tAlias );
			
			Value_WindowOwer owerVal;
			owerVal.pWnd = UIManagePtr->GetWindowPtr( g_stcStrConftempDlg );//pClickInfo->m_pSrcWnd;
			UIManagePtr->SetPropertyValue(owerVal, g_stcStrCallDlg);

			Value_WindowPos posVal;
			posVal.nX =  rect.right ;
			posVal.nY = rect.top  ;
			UIManagePtr->SetPropertyValue(posVal, g_stcStrCallDlg);	

			UIManagePtr->ShowWindow( g_stcStrCallDlg);
			return NO_ERROR;
        }
    } 
 
    return NO_ERROR;
}

HRESULT CConfCtrlLogic::OnConfCnsItemClick( WPARAM wparam, LPARAM lparam )
{ 
    IArgs* pArgs = (IArgs*)wparam;
    if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast<const Args_ClickItemInfo*>(pArgs) )
    {
        const IData *pIData = pClickInfo->m_pClickList->GetItemData()->GetUserData();
        if ( const Data_ConfCns * pDataTemp = dynamic_cast< const Data_ConfCns*>(pIData) )
        {   
            Value_WindowOwer owerVal;
            owerVal.pWnd = UIManagePtr->GetWindowPtr( g_stcStrCnsLstDlg );//pClickInfo->m_pSrcWnd;
            UIManagePtr->SetPropertyValue(owerVal, g_stcStrConfCnsCtrlDlg);
            UIManagePtr->SetPropertyValue(owerVal, "ConfCnsCtrlSpeakerDlg");
			UIManagePtr->SetPropertyValue(owerVal, g_stcStrCallDlg); 

            CRect rect = const_cast<CRect&>(pClickInfo->m_rcFrame);
            m_rectClickItem = rect;

            TCnsInfo tCnsInfo = pDataTemp->m_tConfCns; 

            SetCallInfo( tCnsInfo.m_wEpID ,INVALID_WORD );
            Value_WindowPos posVal;
            posVal.nX = rect.right;
            posVal.nY = rect.top; 
            
            
            if ( !tCnsInfo.m_bOnline )
            {   
                m_emCallTp = emCallTpCallConfCns;
                UIManagePtr->SetPropertyValue(posVal, g_stcStrCallDlg);
                UIManagePtr->ShowWindow( g_stcStrCallDlg);
            }
            else
            {    
				UIManagePtr->ShowWindow( m_strConfCnsCtrlDlg, false );
                RefreshConfCnsCtrlDlg();
                AdjustMenuPos();
                UIManagePtr->ShowWindow( m_strConfCnsCtrlDlg, true );
            }
        }
    }
    return NO_ERROR;
}

void CConfCtrlLogic::AdjustMenuPos ( )
{

    Value_WindowPos posVal;
    posVal.nX = m_rectClickItem.right;
    posVal.nY = m_rectClickItem.top; 

    Value_WindowSize valSize;
    UIManagePtr->GetPropertyValue( valSize, m_strConfCnsCtrlDlg );
    
    Value_WindowPos valLargerBottom;
    UIManagePtr->GetPropertyValue( valLargerBottom, g_stcStrMainMenuDlg  );
    
    if ( posVal.nY + valSize.nHeight >= valLargerBottom.nY )
    {  
        posVal.nY = m_rectClickItem.bottom -  valSize.nHeight;
        UIManagePtr->LoadScheme( "SchmImgEx", NULL, m_strConfCnsCtrlDlg, false ); 
    }
    else
    {
        UIManagePtr->LoadScheme( "SchmImgNormal", NULL, m_strConfCnsCtrlDlg, false );
    } 
    
    UIManagePtr->SetPropertyValue(posVal, m_strConfCnsCtrlDlg);
    
}

HRESULT CConfCtrlLogic::OnAddrItemCallClick( WPARAM wparam, LPARAM lparam )
{
	IArgs* pArgs = (IArgs*)wparam;
	if ( Args_ClickItemInfo *pClickInfo =  dynamic_cast<Args_ClickItemInfo*>(pArgs) )
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetItemData();
        if ( const Data_AddrItemInfo *pItemInfo = dynamic_cast< const Data_AddrItemInfo*>(pBaseItem->GetUserData()) )
        { 
			TAddrItem tAddrItem = pItemInfo->m_tAddrItem;
			CRect rect = pClickInfo->m_rcFrame;

			Value_WindowOwer owerVal;
			owerVal.pWnd = UIManagePtr->GetWindowPtr( g_stcStrAddrbookDlg );//pClickInfo->m_pSrcWnd;
			UIManagePtr->SetPropertyValue(owerVal, g_stcStrCallDlg);

			TEpAddrList tEqAddrLst;
            
            m_tCnAddrList.clear();

			TCMSConf tConf;
			BOOL32 bIsInconf = BusinessManagePtr->IsInConf( &tConf );
			if ( bIsInconf  )
			{
				//B3版本  点对点会议转换多点会议	JYY
				if ( tConf.m_emConfType == emCallType_P2P )
				{
					m_emCallTp = emCallTpInstantCf; 
                    TTPCnsInfo tCnsInfo;
                    ComInterface->GetLocalCnsInfo( tCnsInfo );
					TTPCnsConfStatus status = ComInterface->GetLocalCnsConfState();

                    TCnAddr tCnAddr;
					//本地会场
					if ( strlen( tCnsInfo.m_achRoomName ) > 0  )
					{
						//tEqAddrLst.Add( tp_Alias_h323, tCnsInfo.m_achRoomName );
                        tCnAddr.emType = emTpAlias;
					}
					else
					{
						//tEqAddrLst.Add( tp_Alias_e164, tCnsInfo.m_achE164 );
                        tCnAddr.emType = emTpE164Num;
					}
                    strncpy( tCnAddr.achAlias, tCnsInfo.m_achRoomName, TP_MAX_H323ALIAS_LEN+1 );
                    strncpy( tCnAddr.achE164, tCnsInfo.m_achE164, TP_MAX_H323ALIAS_LEN+1 );
                    m_tCnAddrList.push_back( tCnAddr );

                    memset( &tCnAddr, 0, sizeof(TCnAddr) );
					//点对点会议对端会场              
                    if ( strlen( status.achConfName ) > 0  )
                    {
						//tEqAddrLst.Add( tp_Alias_h323, status.achConfName );
                        tCnAddr.emType = emTpAlias;
                        strncpy( tCnAddr.achAlias, status.achConfName, TP_MAX_H323ALIAS_LEN+1 );
                        m_tCnAddrList.push_back( tCnAddr );
				    }
					else
					{
						//tEqAddrLst.Add( tp_Alias_e164, m_tCallAddr.achE164 );
					}
				}
				else
				{
					m_emCallTp = emCallTpInvitCns;
				}		
			}
            else
            {
                if ( tAddrItem.emItemType == emEntryItem )
                {
                    m_emCallTp = emCallTpPtp;
                }
                /*else 现在多会场呼叫中不会有组条目 -2014.6.3 xcr
                {
                    m_emCallTp = emCallTpInstantCf; 
                    TTPCnsInfo tCnsInfo;
                    ComInterface->GetLocalCnsInfo( tCnsInfo );

					if ( strlen( tCnsInfo.m_achRoomName ) > 0  )
					{
						tEqAddrLst.Add( tp_Alias_h323, tCnsInfo.m_achRoomName );
					}
					else
					{
						tEqAddrLst.Add( tp_Alias_e164, tCnsInfo.m_achE164 );
					}			    	
                }*/
            }		 
			
			if ( tAddrItem.emItemType == emEntryItem   )
            {  
                if ( m_emCallTp == emCallTpPtp )
                {
                    memset( &m_tCallAddr, 0, sizeof(TCnAddr) );
                                      
                    if ( strlen( tAddrItem.tAddrInfo.achEntryName ) > 0  )
                    {
                        m_tCallAddr.emType = emTpAlias;
                        strncpy( m_tCallAddr.achAlias, tAddrItem.tAddrInfo.achEntryName, sizeof(m_tCallAddr.achAlias) );
				    }
					
					if ( strlen( tAddrItem.tAddrInfo.achE164 ) > 0 )
                    {
                        m_tCallAddr.emType = emTpE164Num;
                        strncpy( m_tCallAddr.achE164, tAddrItem.tAddrInfo.achE164, sizeof(m_tCallAddr.achE164) );
                    }
                }
                else
                {
                    TCnAddr tCnAddr;
                    if ( strlen( tAddrItem.tAddrInfo.achEntryName ) > 0  )
                    {
						//tEqAddrLst.Add( tp_Alias_h323, tAddrItem.tAddrInfo.achEntryName );
						//将别名和E614号全部添加 ----JYY  2014.7.11
						tEqAddrLst.Add( tAddrItem.tAddrInfo.achEntryName, tAddrItem.tAddrInfo.achE164 );
                        tCnAddr.emType = emTpAlias;
                    }
                    else
                    {
                        tEqAddrLst.Add( tp_Alias_e164, tAddrItem.tAddrInfo.achE164 );

                        tCnAddr.emType = emTpE164Num;
				    }
                  
                    strncpy( tCnAddr.achAlias, tAddrItem.tAddrInfo.achEntryName, TP_MAX_H323ALIAS_LEN+1 );
                    strncpy( tCnAddr.achE164, tAddrItem.tAddrInfo.achE164, TP_MAX_H323ALIAS_LEN+1 );
                    m_tCnAddrList.push_back( tCnAddr );
                }
             				 		
			}
			/*else
            { 
				vector<TAddrInfo> vctAddrInfo;
				ComInterface->GetGroupAddrInfo( tAddrItem.tGroupInfo, vctAddrInfo );
				
				for( int i = 0; i < vctAddrInfo.size(); i++ )
				{
 
					EmConfAddEpRet emRet = TP_ConfAddEpRet_Unknow;				
					if ( strlen( vctAddrInfo[i].achEntryName ) > 0  )
					{
						emRet = tEqAddrLst.Add( tp_Alias_h323, vctAddrInfo[i].achEntryName );
					}
					else
					{
						emRet = tEqAddrLst.Add( tp_Alias_e164, vctAddrInfo[i].achE164 );
					}
					if ( emRet != TP_ConfAddEpRet_Success )
					{
						if ( emRet == TP_ConfAddEpRet_MaxNum )
						{
							break;
						}
						continue;
					}
				}
			}*/

			SetCallInfo( tEqAddrLst );
			Value_WindowPos posVal;
			posVal.nX = rect.right;
			posVal.nY = rect.top;
			UIManagePtr->SetPropertyValue( posVal, g_stcStrCallDlg );
			UIManagePtr->ShowWindow( g_stcStrCallDlg ); 
		}
	}
	return NO_ERROR;
}

void CConfCtrlLogic::RefreshConfCnsCtrlDlg( )
{
    TCMSConf tConfInfo ;
    BOOL32 bRe = BusinessManagePtr->IsInConf(&tConfInfo) ;
    if (  !bRe )
    {
        return;
    }

   TCnsInfo *pTCnsInfo = tConfInfo.GetCnsInfoByID( m_wCnsID ); 
   if ( pTCnsInfo == NULL )
   {
       return;
   } 
    

    //如果开启混音则不可以设置发言人
    if ( tConfInfo.m_wSpeaker != pTCnsInfo->m_wEpID  &&  !tConfInfo.m_bStartAudmix )
    {
        //发言人与非发言人的对话框分为两个，防止刷新时闪一下黑框 -2014.3.25 xcr
        m_strConfCnsCtrlDlg = "ConfCnsCtrlSpeakerDlg";
        //UIManagePtr->LoadScheme("SchmSpeaker",NULL,g_stcStrConfCnsCtrlDlg, false );      
    }
    else
    {
        m_strConfCnsCtrlDlg = g_stcStrConfCnsCtrlDlg;
       //UIManagePtr->LoadScheme("SchmUnSpeaker",NULL,g_stcStrConfCnsCtrlDlg, false ); 
    }

    if ( tConfInfo.m_wDual == pTCnsInfo->m_wEpID )
    {
        UIManagePtr->LoadScheme( "SchmStopDual", NULL, m_strConfCnsCtrlDlg, false );
    }
    else
    {
        UIManagePtr->LoadScheme( "SchmStartDual", NULL, m_strConfCnsCtrlDlg, false );
    }

    if ( pTCnsInfo->m_bMute )
    {
        UIManagePtr->LoadScheme( "SchmUnMuteCns", NULL, m_strConfCnsCtrlDlg, false );
    }
    else
    {
        UIManagePtr->LoadScheme( "SchmMuteCns", NULL, m_strConfCnsCtrlDlg, false );
    }

	//通过最后一个按钮的状态刷新整个dlg
    if ( pTCnsInfo->m_bQuiet )
    {
        UIManagePtr->LoadScheme( "SchmUnQuietCns", NULL, m_strConfCnsCtrlDlg );
    }
    else
    {
        UIManagePtr->LoadScheme( "SchmQuietCns", NULL, m_strConfCnsCtrlDlg );
    }
}


 

HRESULT CConfCtrlLogic::OnSetSpeakerCnsRsp( WPARAM wparam, LPARAM lparam)
{  
    Value_WindowVisible val;
    UIManagePtr->GetPropertyValue( val, m_strConfCnsCtrlDlg );
    if ( !val.bVisible )
    {
        return NO_ERROR;
    } 

    UIManagePtr->ShowWindow( m_strConfCnsCtrlDlg, false );
    RefreshConfCnsCtrlDlg();
    AdjustMenuPos();
    UIManagePtr->ShowWindow( m_strConfCnsCtrlDlg, true );

    return NO_ERROR;
}


HRESULT CConfCtrlLogic::OnSetMuteCnsRsp( WPARAM wparam, LPARAM lparam)
{
    Value_WindowVisible val;
    UIManagePtr->GetPropertyValue( val, m_strConfCnsCtrlDlg );
    if ( !val.bVisible )
    {
        return NO_ERROR;
    }
    RefreshConfCnsCtrlDlg();
    return NO_ERROR;

}


HRESULT CConfCtrlLogic::OnSetQuietCnsRsp( WPARAM wparam, LPARAM lparam)
{ 
    Value_WindowVisible val;
    UIManagePtr->GetPropertyValue( val, m_strConfCnsCtrlDlg );
    if ( !val.bVisible )
    {
        return NO_ERROR;
    }
    RefreshConfCnsCtrlDlg();
    return NO_ERROR;

}

/*
emTpDualAccept,
		emTpDualBusy,
		emTpDualPreemptive,
		emTpDualPeerReject,
		emTpDualPeerStop,
        emTpDualNoVideo,
        emTpDualLocalStop,
		emTpDualSndFail,
*/ 
HRESULT CConfCtrlLogic::OnSetDualCnsRsp( WPARAM wparam, LPARAM lparam)
{   
	TCMSConf tConf;
	BOOL32 bInConf = ComInterface->IsInConf( &tConf );
	if ( !bInConf )
	{
		return NO_ERROR;
	}
	
	u16	wConfID = (u16)wparam;
	if ( wConfID != tConf.m_wConfID )
	{
		return NO_ERROR;
	}
/*
    EmTPDualReason emRe = (EmTPDualReason)lparam;
    switch( emRe )
    {
    case emTpDualBusy:
        ShowPopMsg( "操作演示失败：演示源忙");
        break;  
    case emTpDualPreemptive:
        ShowPopMsg( "操作演示失败：演示已经在进行");
        break;
    case emTpDualPeerReject:
        ShowPopMsg( "操作演示失败：演示被拒绝");
        break;
    case emTpDualPeerStop:
        ShowPopMsg( "操作演示失败：演示已关闭");
        break;
    case emTpDualNoVideo:
        ShowPopMsg( "操作演示失败：无演示源");
        break;
    case emTpDualLocalStop:
        ShowPopMsg( "操作演示失败：本地停止演示");
        break;
    
    case emTpDualSndFail:
        ShowPopMsg( "操作演示失败：发送双流失败");
        break;
        
    default: 
        break;
    }
*/	
    Value_WindowVisible val;
    UIManagePtr->GetPropertyValue( val, m_strConfCnsCtrlDlg );
    if ( !val.bVisible )
    {
        return NO_ERROR;
    }
    RefreshConfCnsCtrlDlg();
    return NO_ERROR;

}

HRESULT CConfCtrlLogic::OnDualCnsNotify( WPARAM wparam, LPARAM lparam)
{  
    Value_WindowVisible val;
    UIManagePtr->GetPropertyValue( val, m_strConfCnsCtrlDlg );
    if ( !val.bVisible )
    {
        return NO_ERROR;
    }
    RefreshConfCnsCtrlDlg();
    return NO_ERROR;

}