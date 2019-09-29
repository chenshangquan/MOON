// confCnsLstLogic.cpp: implementation of the CConfCnsLstLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cms.h"
#include "confCnsLstLogic.h" 
#include "confCtrlLogic.h"
#include "volumCtrlLogic.h"
#include "msgBoxLogic.h"
#include "TouchListHelp.h"
#include "AddrList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const String CConfCnsLstLogic::m_strStcTitle = "StcTitle";                          //�᳡�������
const String CConfCnsLstLogic::m_strBtnCnsShowSel = "BtnCnsShowSel"; //�᳡��ʾѡ��
const String CConfCnsLstLogic::m_strBtnMic = "BtnMic";                          //��˷�
const String CConfCnsLstLogic::m_strBtnSpeaker = "BtnSpeaker";              //������
const String CConfCnsLstLogic::m_strBtnDbFlow = "BtnDbFlow";               //˫��
const String CConfCnsLstLogic::m_strBtnHungup = "BtnHungup";             //�Ҷϻ���
const String CConfCnsLstLogic::m_strLstCns = "LstCns";                   //�᳡�б�
const String CConfCnsLstLogic::m_strDlgCnsShowOptn = "CnsShowOptnDlg";
const String CConfCnsLstLogic::m_strLstCnsShowOptn = "LstShowMenuDlg"  ;        



const String CConfCnsLstLogic::m_strShowAllCns = "��ʾȫ���᳡";
const String CConfCnsLstLogic::m_strShowSpeakerCns = "��ʾ���Ի᳡";
const String CConfCnsLstLogic::m_strShowMuteCns = "��ʾ�����᳡";
const String CConfCnsLstLogic::m_strShowQuietCns = "��ʾ�����᳡";
const String CConfCnsLstLogic::m_strShowOffLineCns = "��ʾ�����߻᳡";
const String CConfCnsLstLogic::m_strShowDualCns = "��ʾ��ʾ�᳡";
 
CConfCnsLstLogic *CConfCnsLstLogic::m_pLogic = NULL;


CConfCnsLstLogic::CConfCnsLstLogic():
                    m_emCnsShowState(emShowAll)
{               
             
   const_cast<String&>(m_strLstCns) = g_stcStrCnsLstDlg + "/" + m_strLstCns;
   const_cast<String&>(m_strLstCnsShowOptn) = m_strDlgCnsShowOptn + "/" + m_strLstCnsShowOptn;
}

CConfCnsLstLogic::~CConfCnsLstLogic()
{ 
    if ( m_pLogic != NULL )
    {   
        UnRegMsg();
        UnRegFunc();
        delete m_pLogic;
        m_pLogic = NULL;
	}
}


CConfCnsLstLogic* CConfCnsLstLogic::GetLogicPtr()
{
    if ( m_pLogic == NULL )
    {
        m_pLogic = new CConfCnsLstLogic(); 
    } 
    return m_pLogic;
}


void CConfCnsLstLogic::RegMsg()
{         
    //����֪ͨ
    REG_MSG_HANDLER( UI_UMS_CASCADE_CONF_NOTIFY, CConfCnsLstLogic::OnCascadeConfNotify, m_pLogic, CConfCnsLstLogic);

    //����cns�Ƿ��ڻ����е�״̬�仯֪ͨ ����cns֪ͨ��
    REG_MSG_HANDLER( UI_CNS_CONFSTATE_NOTIFY, CConfCnsLstLogic::OnConfStateNotify, m_pLogic, CConfCnsLstLogic );
    REG_MSG_HANDLER( UI_UMS_UPDATE_CONFINFO, CConfCnsLstLogic::OnConfStateNotify, m_pLogic, CConfCnsLstLogic  );
    //REG_MSG_HANDLER(  UI_UMS_REFRESH_CONFCNS_LIST, CConfCnsLstLogic::OnConfStateNotify, m_pLogic, CConfCnsLstLogic );

    //�����cns�б���� 
    REG_MSG_HANDLER( UI_UMS_REFRESH_CONFCNS_LIST,CConfCnsLstLogic::OnRefreshCnsLstNotify , m_pLogic, CConfCnsLstLogic  );

    //�е��߻᳡������ʾ
    REG_MSG_HANDLER( UI_UMS_UPDATE_CONFCNS_LIST,CConfCnsLstLogic::OnUpdateCnsNotify , m_pLogic, CConfCnsLstLogic  );

    //�����˸���
    REG_MSG_HANDLER( UI_UMS_CHANGE_SPEAKER_NOTIFY,CConfCnsLstLogic::OnChangeSpeakerNotify , m_pLogic, CConfCnsLstLogic  );  

    //�뿪����֪ͨ
    REG_MSG_HANDLER( UI_UMS_HANGUP_CONF_RSP,CConfCnsLstLogic::OnHungupConfRsp , m_pLogic, CConfCnsLstLogic  );

    //������������
    // REG_MSG_HANDLER( UI_UMS_SET_SPEAKER_RSP,CConfCnsLstLogic::OnSetSpeakerCnsRsp , m_pLogic, CConfCnsLstLogic  );
    REG_MSG_HANDLER( UI_UMS_SET_MUTE_CNS_RSP,CConfCnsLstLogic::OnSetMuteCnsRsp , m_pLogic, CConfCnsLstLogic  );
    REG_MSG_HANDLER( UI_UMS_SET_QUIET_CNS_RSP,CConfCnsLstLogic::OnSetQuietCnsRsp , m_pLogic, CConfCnsLstLogic  );
    REG_MSG_HANDLER( UI_UMS_SET_DUAL_CNS_RSP,CConfCnsLstLogic::OnSetDualCnsRsp , m_pLogic, CConfCnsLstLogic  );
    REG_MSG_HANDLER( UI_UMS_DUAL_CNS_NOTIFY,CConfCnsLstLogic::OnDualCnsNotify , m_pLogic, CConfCnsLstLogic  ); 
  
}

void CConfCnsLstLogic::UnRegMsg()
{
 
}

bool CConfCnsLstLogic::RegCBFun()
{   	 
    REG_GOBAL_MEMBER_FUNC( "CConfCnsLstLogic::InitWnd", CConfCnsLstLogic::InitWnd, m_pLogic, CConfCnsLstLogic ) ;
    
    REG_GOBAL_MEMBER_FUNC( "CConfCnsLstLogic::BtnHangupLocalCnsClick", CConfCnsLstLogic::BtnHangupLocalCnsClick, m_pLogic, CConfCnsLstLogic ) ;
    REG_GOBAL_MEMBER_FUNC( "CConfCnsLstLogic::BtnHangupConfClick", CConfCnsLstLogic::BtnHangupConfClick, m_pLogic, CConfCnsLstLogic ) ;
    REG_GOBAL_MEMBER_FUNC( "CConfCnsLstLogic::BtnMicClick", CConfCnsLstLogic::BtnMicClick, m_pLogic, CConfCnsLstLogic ) ;
    REG_GOBAL_MEMBER_FUNC( "CConfCnsLstLogic::BtnSpeakerClick", CConfCnsLstLogic::BtnSpeakerClick, m_pLogic, CConfCnsLstLogic ) ;
    REG_GOBAL_MEMBER_FUNC( "CConfCnsLstLogic::BtnDbFlowClick", CConfCnsLstLogic::BtnDbFlowClick, m_pLogic, CConfCnsLstLogic ) ;
    REG_GOBAL_MEMBER_FUNC( "CConfCnsLstLogic::BtnStopDbFlowClick", CConfCnsLstLogic::BtnStopDbFlowClick, m_pLogic, CConfCnsLstLogic ) ;
     
    REG_GOBAL_MEMBER_FUNC( "CConfCnsLstLogic::BtnCnsShowOptnClick", CConfCnsLstLogic::BtnCnsShowOptnClick, m_pLogic, CConfCnsLstLogic ) ;
   
    //�������Ļ᳡cns�б��е�ĳ����Ŀ
    REG_GOBAL_MEMBER_FUNC( "CConfCnsLstLogic::BtnConfCnsItemClick", CConfCnsLstLogic::BtnConfCnsItemClick, m_pLogic, CConfCnsLstLogic ) ;
    
    REG_GOBAL_MEMBER_FUNC( "CConfCnsLstLogic::BtnSave2File", CConfCnsLstLogic::BtnSave2File, m_pLogic, CConfCnsLstLogic ) ;
    REG_GOBAL_MEMBER_FUNC( "CConfCnsLstLogic::OptDlgBtnSave2File", CConfCnsLstLogic::OptDlgBtnSave2File, m_pLogic, CConfCnsLstLogic ) ;
    REG_GOBAL_MEMBER_FUNC( "CConfCnsLstLogic::CloseOptDlg", CConfCnsLstLogic::CloseOptDlg, m_pLogic, CConfCnsLstLogic ) ;
    REG_GOBAL_MEMBER_FUNC( "CConfCnsLstLogic::CloseCnsLstDlg", CConfCnsLstLogic::CloseCnsLstDlg, m_pLogic, CConfCnsLstLogic ) ;
  

    //�᳡�б���ʾѡ��
    REG_GOBAL_MEMBER_FUNC( "CConfCnsLstLogic::OnShowAllConfCnsClick", CConfCnsLstLogic::OnShowAllConfCnsClick, m_pLogic, CConfCnsLstLogic ) ;
    REG_GOBAL_MEMBER_FUNC( "CConfCnsLstLogic::OnShowOfflineCnsClick", CConfCnsLstLogic::OnShowOfflineCnsClick, m_pLogic, CConfCnsLstLogic ) ;
    REG_GOBAL_MEMBER_FUNC( "CConfCnsLstLogic::OnShowSpokesCnsClick", CConfCnsLstLogic::OnShowSpokesCnsClick, m_pLogic, CConfCnsLstLogic ) ;
    REG_GOBAL_MEMBER_FUNC( "CConfCnsLstLogic::OnShowMuteCnsClick", CConfCnsLstLogic::OnShowMuteCnsClick, m_pLogic, CConfCnsLstLogic ) ;
    REG_GOBAL_MEMBER_FUNC( "CConfCnsLstLogic::OnShowSlienceCnsClick", CConfCnsLstLogic::OnShowSlienceCnsClick, m_pLogic, CConfCnsLstLogic ) ;
    REG_GOBAL_MEMBER_FUNC( "CConfCnsLstLogic::OnShowDbflowCnsClick", CConfCnsLstLogic::OnShowDbflowCnsClick, m_pLogic, CConfCnsLstLogic ) ;

    return true;
}

bool CConfCnsLstLogic::UnRegFunc()
{
     
    return true;
}


bool CConfCnsLstLogic::InitWnd(  const IArgs & arg )
{   
	 CWndLogicBase::InitWnd( arg );

     UpdateCnsLst();
     UpdateShowOption();
     return true;
}

//ֻ����ϯ�뿪���飬�����Ҷ�
bool CConfCnsLstLogic::BtnHangupLocalCnsClick( const IArgs & arg )
{ 
    if ( UIManagePtr->IsVisible( g_stcStrCnsLstDlg ) )
    {
        UIManagePtr->ShowWindow( g_stcStrCnsLstDlg, false );
    }

    CString msg;
    msg.Format("�Ƿ��뿪���飿"); 
    Args_MsgBox argMsg;
    argMsg.pOwnerWnd = UIManagePtr->GetWindowPtr( g_stcStrCnsLstDlg );
	UIDATAMGR->setLocalCnsState(emLocalCnsWillHungup);  
    int nReslut = MSG_BOX( (LPCSTR)msg ,TRUE, &argMsg); 
	if ( IDOK == nReslut )
	{
		IArgs arg("");
		HungupLocalCns( arg );
	}
	else if ( IDCANCEL == nReslut )
	{
	    Value_HoriListSelItem valSel;
		valSel.dwDataKey = -1;
	    UIManagePtr->SetPropertyValue( valSel, "MainMenu/ConfManageMenuDlg/ConfManageList" );
	}
    return true;
}



bool CConfCnsLstLogic::BtnHangupConfClick( const IArgs & arg )
{ 
    if ( UIManagePtr->IsVisible( g_stcStrCnsLstDlg ) )
    {
        UIManagePtr->ShowWindow( g_stcStrCnsLstDlg, false );
    }
    
    CString msg;
    msg.Format("�Ƿ�Ҫ�������飿");
    
    Args_MsgBox argMsg;
    argMsg.pOwnerWnd = UIManagePtr->GetWindowPtr( g_stcStrCnsLstDlg );
	UIDATAMGR->setLocalCnsState(emLocalCnsWillHungup); //Bug00113809  2012.11.14  yjj
    int nReslut = MSG_BOX( (LPCSTR)msg ,TRUE ,&argMsg); 
    if ( IDOK == nReslut )
	{
		IArgs arg("");
		HungupConf( arg );
	}
	return true;
}

bool CConfCnsLstLogic::HungupConf( const IArgs & arg )
{ 
    TCMSConf ConfInfo ;
    BOOL32 bInConf = ComInterface->IsInConf( &ConfInfo );
     
    if ( !bInConf  )
    {
        PrtMsg( 0, emEventTypeCmsWindow,"[CConfCnsLstLogic::HungupConf]����CNS���ڻ�����");
        return false;
    } 

    u16 wRe = NO_ERROR;

    if ( ConfInfo.m_emConfType == emCallType_Conf )
    {
        wRe = BusinessManagePtr->HangupConf();
    }
    else
    {       
        wRe = BusinessManagePtr->HungupPtpConf();        
    }

    if ( wRe != NO_ERROR )
    {
        HANDLE_ERROR(wRe); 
        return false;
    }
    
    return true;
}

bool CConfCnsLstLogic::HungupLocalCns( const IArgs & arg )
{  
    TCMSConf ConfInfo ;
    BOOL32 bInConf = ComInterface->IsInConf( &ConfInfo );
    
    u16 wRe = NO_ERROR;
    if ( !bInConf  )
    {          
		PrtMsg( 0, emEventTypeCmsWindow,"[CConfCnsLstLogic::HungupConf]����CNS���ڻ�����");
		return false;     
    }
    else
    {
		if ( ConfInfo.m_emConfType == emCallType_P2P )
		{	
			BusinessManagePtr->HungupPtpConf();
		}
		else
		{
			TConfEpID  tConfEpInfo;
			tConfEpInfo.m_wConfID = ConfInfo.m_wConfID;
			// tConfEpInfo.m_wEpID = ConfInfo.m_wDefaultChairMan;  ����¼���Ƿֻ᳡ʱ������������
			TTPCnsInfo tCnsInfo;
			BusinessManagePtr->GetLocalCnsInfo( tCnsInfo );
			tConfEpInfo.m_wEpID = ConfInfo.GetCnsIDByAlias( tCnsInfo.m_achRoomName );
			wRe = BusinessManagePtr->HangupCNS( tConfEpInfo  );
		}
    }
    
    if ( wRe != NO_ERROR)
    {
        HANDLE_ERROR(wRe);
        return false;
    }
    UIDATAMGR->setLocalCnsState ( emLocalCnsHungup );
    
    return true;
}



bool CConfCnsLstLogic::BtnMicClick( const IArgs & arg )
{    
     Window *pOwner = NULL;
     if ( m_pWndTree != NULL )
     {
         pOwner = m_pWndTree->GetItemData()->pWnd;
     }
     CVolumCtrlLogic::GetLogicPtr()->ShowVolum( emVolumMic, pOwner );
     return true;
} 


bool CConfCnsLstLogic::BtnSpeakerClick( const IArgs & arg )
{   
    Window *pOwner = NULL;
    if ( m_pWndTree != NULL )
    {
        pOwner = m_pWndTree->GetItemData()->pWnd;
    }

    CVolumCtrlLogic::GetLogicPtr()->ShowVolum(emVolumSpeaker, pOwner );
    return true;
}


bool CConfCnsLstLogic::BtnDbFlowClick( const IArgs & arg )
{
    TCMSConf ConfInfo ;
    BOOL32 bInConf = ComInterface->IsInConf( &ConfInfo ); 
    if ( bInConf )
    {   
        TConfEpID  tConfEpInfo;
        tConfEpInfo.m_wConfID = ConfInfo.m_wConfID;
        tConfEpInfo.m_wEpID = ConfInfo.GetChairCnsID();
     
       u16 wRe =  BusinessManagePtr->SetDualCns( tConfEpInfo ,TRUE);
       if ( wRe != NO_ERROR )
       {  
          CString strErr = GET_ERR_STRING( wRe );
          Args_MsgBox argMsg;
          argMsg.pOwnerWnd = UIManagePtr->GetWindowPtr( g_stcStrCnsLstDlg );
          MSG_BOX( strErr, FALSE, &argMsg);
          argMsg.pOwnerWnd->SetFocus();
       }
    }
   return true;
     
}


bool CConfCnsLstLogic::BtnStopDbFlowClick( const IArgs & arg )
{
    TCMSConf ConfInfo ;
    BOOL32 bInConf = ComInterface->IsInConf( &ConfInfo ); 
    if ( bInConf  )
    {   
        TConfEpID  tConfEpInfo;
        tConfEpInfo.m_wConfID = ConfInfo.m_wConfID;
        tConfEpInfo.m_wEpID = ConfInfo.GetChairCnsID();
        
        u16 wRe =  BusinessManagePtr->SetDualCns( tConfEpInfo ,FALSE);
        if ( wRe != NO_ERROR )
        {  
            CString strErr = GET_ERR_STRING( wRe );
            Args_MsgBox argMsg;
            argMsg.pOwnerWnd = UIManagePtr->GetWindowPtr( g_stcStrCnsLstDlg );
            MSG_BOX( strErr, FALSE, &argMsg);
            argMsg.pOwnerWnd->SetFocus();
        }
    }
    return true;
    
}


bool CConfCnsLstLogic::BtnCnsShowOptnClick( const IArgs & arg )
{ 
	bool bOn = false;
    UIManagePtr->GetSwitchState( m_strBtnCnsShowSel, bOn , m_pWndTree );
    if ( bOn == true )
    {   
		Value_WindowOwer owerVal;
		owerVal.pWnd = UIManagePtr->GetWindowPtr( g_stcStrCnsLstDlg );
		UIManagePtr->SetPropertyValue(owerVal, m_strDlgCnsShowOptn);

        POINT pt;        
        pt.x = 920;
        pt.y = 53; 
        UIFACTORYMGR_PTR->SetWndPos( pt, m_strDlgCnsShowOptn, NULL, g_stcStrMainFrameDlg );

        UIManagePtr->ShowWindow( m_strDlgCnsShowOptn );
    }
    else
    {
        UIManagePtr->ShowWindow(  m_strDlgCnsShowOptn, false );
    }
    return true; 
}


bool CConfCnsLstLogic::BtnConfCnsItemClick( const IArgs & arg )
{
    if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast<const Args_ClickItemInfo*>(&arg) )
    {
        const IData *pIData = pClickInfo->m_pClickList->GetItemData()->GetUserData();
        if ( const Data_ConfCns * pDataTemp = dynamic_cast< const Data_ConfCns*>(pIData) )
        {   
//             //���ػ᳡�޵����¼�
//             BOOL32 bLocal = BusinessManagePtr->IsLocalCns( pDataTemp->m_tConfCns.m_achRoomName ) ;
//             if ( bLocal )
//             {   
//                 PrtMsg( 0,emEventTypeCmsWindow,"[CConfCnsLstLogic::BtnConfCnsItemClick] �������᳡�޵����¼�");
//                 return false;
//             }
//             else
            {
               CMsgDispatch::SendMessage( UI_CONF_CNS_ITEM_CLICK, (WPARAM)(&arg), 0 );
            }
            //CRect rect = const_cast<CRect&>(pClickInfo->m_rcFrame);
            //CMsgDispatch::SendMessage( UI_CONF_CNS_ITEM_CLICK, (u32)(&pDataTemp->m_tConfCns), (u32)&rect);
            
        }
    } 
 
   return true; 
}

bool CConfCnsLstLogic::BtnSave2File( const IArgs & arg )
{
    return  UIManagePtr->SaveToFile( g_stcStrCnsLstDlg  );  
}

bool CConfCnsLstLogic::OptDlgBtnSave2File( const IArgs & arg )
{
    return  UIManagePtr->SaveToFile( m_strDlgCnsShowOptn  );  
}

bool CConfCnsLstLogic::CloseOptDlg( const IArgs & arg  )
{
   return UIManagePtr->ShowWindow( m_strDlgCnsShowOptn, false);
 
}

bool CConfCnsLstLogic::CloseCnsLstDlg( const IArgs & arg  )
{
   return UIManagePtr->ShowWindow( g_stcStrCnsLstDlg, false);
}

HRESULT CConfCnsLstLogic::OnCascadeConfNotify( WPARAM wparam, LPARAM lparam)
{
    //UpdateWnd();
    UpdateCnsLst();
    return NO_ERROR;
}

HRESULT CConfCnsLstLogic::OnHungupConfRsp( WPARAM wparam, LPARAM lparam)
{ 
    if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }
    
    //��ԭ��ʾѡ��
    m_emCnsShowState = emShowAll; 
    UpdateShowOption();
    UpdateCnsLst( TRUE ); 
    
    return NO_ERROR;
}

HRESULT CConfCnsLstLogic::OnRefreshCnsLstNotify( WPARAM wparam, LPARAM lparam)
{   
    if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }
     
    TCMSConf tConf;
    bool bRe = BusinessManagePtr->IsInConf( &tConf );
    
    if( bRe )
    {
        UpdateCnsLst(); 
    }
   
    return NO_ERROR;
}


//������� �᳡ �� �����Ҷϵĵ������ʾ
HRESULT CConfCnsLstLogic::OnUpdateCnsNotify( WPARAM wparam, LPARAM lparam)
{   
//     TCMSConf tConfInfo;
//     BOOL32 IsLocalInConf = BusinessManagePtr->IsLocalCnsInConf( &tConfInfo );
//     if (  !IsLocalInConf )
//     {
//         return NO_ERROR;
//     }
// 
//     TConfCnsInfo tConfCns = * (( TConfCnsInfo*)lparam);
//     if ( tConfCns.m_wConfID != tConfInfo.m_wConfID )
//     {
//          return NO_ERROR;
//     }
// 
//     for ( int i = 0 ; i< tConfCns.m_wNum; i++ )
//     {
//         
//         if ( EmCnsCallReason_hungup == tConfCns.m_tConfCnsList[i].m_emCallReason )
//         {
//             CString str;
//             str.Format("�᳡ %s �����ܺ��� ���� �����Ҷ� ");
//             ShowPopMsg( str );
//         }
//     }

    return NO_ERROR;
}

HRESULT CConfCnsLstLogic::OnChangeSpeakerNotify( WPARAM wparam, LPARAM lparam)
{   
    if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }

    u16 wConfID = (u16) wparam;
    TCMSConf tConf;
    bool bRe = BusinessManagePtr->IsInConf( &tConf );  
    if( bRe )
    {
        UpdateCnsLst(); 
    } 
   
    return NO_ERROR;
}


HRESULT CConfCnsLstLogic::OnConfStateNotify( WPARAM wparam, LPARAM lparam)
{   
    if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }
   
    BOOL32 bInConf = BusinessManagePtr->IsInConf();
    if ( !bInConf )
    {
		InitLst();
		UpdateShowOption();
		ShowWindow( false );
    }
    else
    {
		UpdateCnsLst();
    } 
    return NO_ERROR;
}

 

HRESULT CConfCnsLstLogic::OnSetSpeakerCnsRsp( WPARAM wparam, LPARAM lparam)
{
    if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }

    UpdateCnsLst(); 
    return NO_ERROR;
}

HRESULT CConfCnsLstLogic::OnSetMuteCnsRsp( WPARAM wparam, LPARAM lparam)
{
    if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }

    UpdateCnsLst(); 
    return NO_ERROR;
}

HRESULT CConfCnsLstLogic::OnSetQuietCnsRsp( WPARAM wparam, LPARAM lparam)
{
    if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }

    UpdateCnsLst(); 
    return NO_ERROR;
}

HRESULT CConfCnsLstLogic::OnSetDualCnsRsp( WPARAM wparam, LPARAM lparam)
{
    if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }

    UpdateCnsLst(); 
    return NO_ERROR;
}

HRESULT CConfCnsLstLogic::OnDualCnsNotify( WPARAM wparam, LPARAM lparam)
{
    if ( m_pWndTree == NULL )
    {
        return NO_ERROR ;
    }

    UpdateCnsLst();
 
    return NO_ERROR;
}

u16 CConfCnsLstLogic::ShowWindow( bool bShow )
 {
    if ( bShow )
    {
        return  UIManagePtr->ShowWindow( g_stcStrCnsLstDlg );
    }
    else
    {
        UIManagePtr->ShowWindow(  m_strDlgCnsShowOptn, false );
        return UIManagePtr->ShowWindow( g_stcStrCnsLstDlg, false);
    }
 }

//������ʾѡ����Ϣ
void CConfCnsLstLogic::UpdateShowOption()
{ 
    if ( m_pWndTree == NULL )
    {
        return;
    }

    ARRAY<String> vcItem; 
    vcItem.push_back( "ImageItemSelected" ); 
    

    ARRAY<TMenuItemInfo> menuLst;  

    TMenuItemInfo tMenu;
    

    if ( m_emCnsShowState == emShowAll )
    { 
        tMenu.m_pVctSubItem = &vcItem;
    } 
    tMenu.strTxt = m_strShowAllCns;
    tMenu.strItemFunc = "CConfCnsLstLogic::OnShowAllConfCnsClick";
    tMenu.strImageItem = "TempListItem" ;  
    tMenu.strTxtItem = CTouchListHelp::strItemText;  
    menuLst.push_back( tMenu );
    
   
    tMenu.Clear();
    tMenu.strImageItem = "TempListItem" ;  
    tMenu.strTxtItem = CTouchListHelp::strItemText;  
    if ( m_emCnsShowState == emShowSpeaker )
    {   
       tMenu.m_pVctSubItem = &vcItem;
    }
    
    tMenu.strTxt = m_strShowSpeakerCns;
    tMenu.strItemFunc = "CConfCnsLstLogic::OnShowSpokesCnsClick";
    menuLst.push_back( tMenu );
    
    tMenu.Clear();
    tMenu.strImageItem = "TempListItem" ;  
    tMenu.strTxtItem = CTouchListHelp::strItemText;  
    if ( m_emCnsShowState == emShowQuiet )
    {   
        tMenu.m_pVctSubItem = &vcItem;
    } 
    tMenu.strTxt = m_strShowQuietCns;
    tMenu.strItemFunc = "CConfCnsLstLogic::OnShowSlienceCnsClick";
    menuLst.push_back( tMenu );

    tMenu.Clear();
    tMenu.strImageItem = "TempListItem" ;  
    tMenu.strTxtItem = CTouchListHelp::strItemText;  
    if ( m_emCnsShowState == emShowMute )
    {
       tMenu.m_pVctSubItem = &vcItem;
    }
    tMenu.strTxt = m_strShowMuteCns;
    tMenu.strItemFunc = "CConfCnsLstLogic::OnShowMuteCnsClick";
    menuLst.push_back( tMenu );

    tMenu.Clear();
    tMenu.strImageItem = "TempListItem" ;  
    tMenu.strTxtItem = CTouchListHelp::strItemText;  
    if ( m_emCnsShowState == emShowOffLine )
    {
        tMenu.m_pVctSubItem = &vcItem;
    }
    tMenu.strTxt = m_strShowOffLineCns;
    tMenu.strItemFunc = "CConfCnsLstLogic::OnShowOfflineCnsClick";
    menuLst.push_back( tMenu );

    tMenu.Clear();
    tMenu.strImageItem = "TempListItem" ;  
    tMenu.strTxtItem = CTouchListHelp::strItemText;  
    if ( m_emCnsShowState == emShowDual )
    {
        tMenu.m_pVctSubItem = &vcItem;
    }
    tMenu.strTxt = m_strShowDualCns;
    tMenu.strItemFunc = "CConfCnsLstLogic::OnShowDbflowCnsClick";
    menuLst.push_back( tMenu );
    
    Value_TouchListMenu val( &menuLst );
    
    UIManagePtr->SetPropertyValue( val, m_strLstCnsShowOptn );
}

void CConfCnsLstLogic::UpdateWnd()
{
    if ( m_pWndTree == NULL )
    {
        return;
    }
   
    TCMSConf tConfInfo;
    BOOL32 re =  BusinessManagePtr->IsInConf(  &tConfInfo ); 
    if ( re )
    {  
		/*
        BOOL32 bChairMan = BusinessManagePtr->IsLocalCnsChairMan( );
        if (  tConfInfo.m_bCascadeConf || !bChairMan )
        {
            //��ʾ �뿪���� button ������ʾ ˫�� button
             UIManagePtr->LoadScheme("SchmLocalCnsNotChairMan",m_pWndTree);
        }
        else
        {
            UIManagePtr->LoadScheme("SchmLocalCnsChairMan",m_pWndTree);
            BOOL32 bDual  = BusinessManagePtr->IsLocalCnsDual( tConfInfo.m_wConfID );
            if ( bDual )
            {
                UIManagePtr->LoadScheme("SchmLocalCnsDual",m_pWndTree,m_strBtnDbFlow);
            }
            else
            {
                UIManagePtr->LoadScheme("",m_pWndTree,m_strBtnDbFlow);
            } 
        } 
		*/
    }
    else
    {     
        ShowWindow( false );
    }

}

void CConfCnsLstLogic::UpdateCnsLst( BOOL bRestOffset /*= FALSE*/ )
{   

	if ( m_pWndTree == NULL )
	{
		return ;
	}

    UpdateWnd();
    
    TCMSConf tConfInfoTemp;
    BOOL32 re =  BusinessManagePtr->IsInConf( &tConfInfoTemp );
 
     if ( !re )
     {  
         //��ԭ��ʾѡ��
         InitLst();
         UpdateShowOption();
         ShowWindow(false);
         PrtMsg(0,emEventTypeCmsWindow,"[CConfCnsLstLogic::UpdateCnsLst]: ����cns���ڻ����У���ˢ��cns�б�����cns�б����");
         return;
     }
 
  

//   TCMSConf *pTConfInfoBk = BusinessManagePtr->GetConfByID( confID );
//   
//   if ( pTConfInfoBk == NULL )
//   {  
//       ShowWindow(false);
//       return ;
//   }

	TCMSConf tConfInfo = tConfInfoTemp; 
	switch( m_emCnsShowState )
	{
    case emShowSpeaker:
       {
         tConfInfo.m_tplCnsList.Clear(); 
         TCnsInfo *pTCns = tConfInfoTemp.GetCnsInfoByID( tConfInfo.m_wSpeaker );
         if ( pTCns != NULL && pTCns->m_bOnline  )
         {
             tConfInfo.m_tplCnsList.Add(pTCns);
         }
         
       }
       break;
    case emShowDual:
       {
           tConfInfo.m_tplCnsList.Clear(); 
           TCnsInfo *pTCns = tConfInfoTemp.GetCnsInfoByID( tConfInfo.m_wDual);
           if ( pTCns != NULL && pTCns->m_bOnline   )
           {
               tConfInfo.m_tplCnsList.Add(pTCns);
           }
       }
       break;
    case emShowQuiet:
       {
           tConfInfo.m_tplCnsList.Clear(); 
           for ( int i = 0; i< tConfInfoTemp.m_tplCnsList.Size(); i++)
           {
               if ( tConfInfoTemp.m_tplCnsList.GetAt(i).m_bQuiet && tConfInfoTemp.m_tplCnsList.GetAt(i).m_bOnline   )
               {
                   tConfInfo.m_tplCnsList.Add(&tConfInfoTemp.m_tplCnsList.GetAt(i));
               }
           }
            
       }
       break; 
    case emShowMute:
       {
           tConfInfo.m_tplCnsList.Clear(); 
           for ( int i = 0; i< tConfInfoTemp.m_tplCnsList.Size(); i++)
           {
               if (tConfInfoTemp.m_tplCnsList.GetAt(i).m_bMute && tConfInfoTemp.m_tplCnsList.GetAt(i).m_bOnline   )
               {
                   tConfInfo.m_tplCnsList.Add(&tConfInfoTemp.m_tplCnsList.GetAt(i));
               }
           }
           
       }
       break;
    case emShowOffLine:
       {
           tConfInfo.m_tplCnsList.Clear(); 
           for ( int i = 0; i< tConfInfoTemp.m_tplCnsList.Size(); i++)
           {
               if ( !tConfInfoTemp.m_tplCnsList.GetAt(i).m_bOnline )
               {
                   tConfInfo.m_tplCnsList.Add(&tConfInfoTemp.m_tplCnsList.GetAt(i));
               }
           } 
       }
       break;
    default:
       break;   
	}
    
	Value_TouchListConfInfo val(tConfInfo );
	if ( BusinessManagePtr->IsLocalCnsChairMan() )
	{
		val.m_strClickItemFunc = "CConfCnsLstLogic::BtnConfCnsItemClick" ; 
	}
	else 
	{
		//PrtMsg( 0 , emEventTypeCmsWindow, "[CConfCnsLstLogic::UpdateCnsLst] ����cns������ϯ���޻������Ȩ��");
	}


	if ( tConfInfo.m_tplCnsList.Size() == 0   )
	{
		UIManagePtr->ShowWindow( g_stcStrConfCnsCtrlDlg,false );
        UIManagePtr->ShowWindow( "ConfCnsCtrlSpeakerDlg", false );
	}

	UIManagePtr->SetPropertyValue(val,m_strLstCns,m_pWndTree);

	if ( bRestOffset )
	{
        ResetLstOffset( m_strLstCns );               
	}
     
}

void CConfCnsLstLogic::ResetLstOffset( String strLst )
{
    Value_TransparentListOffset val;
    val.nOffset = 0;
    UIManagePtr->SetPropertyValue( val, strLst, m_pWndTree );

	Value_TransparentListSelItem valSel;
    valSel.dwDataKey = -1;
    UIManagePtr->SetPropertyValue( valSel, strLst, m_pWndTree );
}


/**	 
	* ����:  �������״̬������
	* @return   
	* @remarks	 
	*/
void CConfCnsLstLogic::Clear()
{ 
    if ( m_pWndTree )
    {
        InitLst();        
        UpdateShowOption(); 
		UIManagePtr->ShowWindow( g_stcStrCnsLstDlg, false );
    }
    
}  



void CConfCnsLstLogic::InitLst()
{
    m_emCnsShowState = emShowAll ; 
    
    //�����б�ǰû��ѡ�����ƫ����Ϊ0
    ResetLstOffset( m_strLstCns );
    
    Value_TransparentListSelItem valSel;
    valSel.dwDataKey = -1;
    
    UIManagePtr->SetPropertyValue( valSel, m_strLstCnsShowOptn );
}