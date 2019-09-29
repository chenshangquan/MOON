// audmixLogic.cpp: implementation of the CAudmixLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cms.h"
#include "audmixLogic.h"
#include "cmsstruct.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CAudmixLogic *CAudmixLogic::m_pLogic = NULL;

const String CAudmixLogic::m_strCnsLst = "DlgLst/CnsList";              //cns 列表
const String CAudmixLogic::m_strDlgAudmixSet = "DlgAudMixSet";   //混音设置界面
TAudMixCtrls CAudmixLogic::m_tCtrlAudmixArray[MAX_AUD_MIX_COUNT];  
String CAudmixLogic::m_strBtnAudSwitch;


CAudmixLogic::CAudmixLogic()
{
    m_tCtrlAudmixArray[0].strRadioSpokes = m_strDlgAudmixSet + "/" + "RadioSpokesCns1";
    m_tCtrlAudmixArray[0].strEdtMem = m_strDlgAudmixSet + "/" + "EdtAudmixCns1";

    m_tCtrlAudmixArray[1].strRadioSpokes = m_strDlgAudmixSet + "/" + "RadioSpokesCns2";
    m_tCtrlAudmixArray[1].strEdtMem = m_strDlgAudmixSet + "/" + "EdtAudmixCns2";

    m_tCtrlAudmixArray[2].strRadioSpokes = m_strDlgAudmixSet + "/" + "RadioSpokesCns3";
    m_tCtrlAudmixArray[2].strEdtMem = m_strDlgAudmixSet + "/" + "EdtAudmixCns3";

    m_tCtrlAudmixArray[3].strRadioSpokes = m_strDlgAudmixSet + "/" + "RadioSpokesCns4";
    m_tCtrlAudmixArray[3].strEdtMem = m_strDlgAudmixSet + "/" + "EdtAudmixCns4";

	m_strBtnAudSwitch = m_strDlgAudmixSet + "/" + "BtnAudmixSwitch";

	m_bAudSwitchOn = FALSE;
	m_nSelRadioSpeak = -1;
	m_nSelEdit = -1;
	m_nDragSelEdit = -1;
}

CAudmixLogic::~CAudmixLogic()
{
    if ( m_pLogic != NULL )
    {   
        UnRegMsg();
        UnRegFunc();
        delete m_pLogic;
        m_pLogic = NULL;
	}
}


CAudmixLogic* CAudmixLogic::GetLogicPtr()
{
    if ( m_pLogic == NULL )
    {  
        m_pLogic = new CAudmixLogic();  
    }
    
    return m_pLogic;
}


void CAudmixLogic::RegMsg()
{    
	REG_MSG_HANDLER( UI_CNS_CONFSTATE_NOTIFY, CAudmixLogic::OnConfStateNotify, m_pLogic, CAudmixLogic );
//  REG_MSG_HANDLER( UI_UMS_REFRESH_CONFCNS_LIST, CAudmixLogic::OnConfStateNotify , m_pLogic, CAudmixLogic  );

    REG_MSG_HANDLER( UI_UMS_UPDATE_CONFINFO, CAudmixLogic::OnConfStateNotify , m_pLogic, CAudmixLogic );  
	REG_MSG_HANDLER( UI_UMS_REFRESH_CONFAUDMIX_LIST, CAudmixLogic::RefreshAudMixList, m_pLogic, CAudmixLogic );


    //会议的cns列表更新 
	REG_MSG_HANDLER( UI_UMS_REFRESH_CONFCNS_LIST, CAudmixLogic::OnRefreshCnsList, m_pLogic, CAudmixLogic );

}

void CAudmixLogic::UnRegMsg()
{
}

bool CAudmixLogic::RegCBFun()
{   	 
    REG_GOBAL_MEMBER_FUNC( "CAudmixLogic::InitWnd", CAudmixLogic::InitWnd, m_pLogic, CAudmixLogic );  
	REG_GOBAL_MEMBER_FUNC( "CAudmixLogic::OnBtnSwitchAudMixClick", CAudmixLogic::OnBtnSwitchAudMixClick, m_pLogic, CAudmixLogic ) ;
	
	REG_GOBAL_MEMBER_FUNC( "CAudmixLogic::OnAddToAudMixList", CAudmixLogic::OnAddToAudMixList, m_pLogic, CAudmixLogic );
	
	REG_GOBAL_MEMBER_FUNC( "CAudmixLogic::OnBtnEdtAudMix1", CAudmixLogic::OnBtnEdtAudMix1, m_pLogic, CAudmixLogic );
	REG_GOBAL_MEMBER_FUNC( "CAudmixLogic::OnBtnEdtAudMix2", CAudmixLogic::OnBtnEdtAudMix2, m_pLogic, CAudmixLogic );
	REG_GOBAL_MEMBER_FUNC( "CAudmixLogic::OnBtnEdtAudMix3", CAudmixLogic::OnBtnEdtAudMix3, m_pLogic, CAudmixLogic );
	REG_GOBAL_MEMBER_FUNC( "CAudmixLogic::OnBtnEdtAudMix4", CAudmixLogic::OnBtnEdtAudMix4, m_pLogic, CAudmixLogic );
	REG_GOBAL_MEMBER_FUNC( "CAudmixLogic::OnBtnRadioSpeak1", CAudmixLogic::OnBtnRadioSpeak1, m_pLogic, CAudmixLogic );
	REG_GOBAL_MEMBER_FUNC( "CAudmixLogic::OnBtnRadioSpeak2", CAudmixLogic::OnBtnRadioSpeak2, m_pLogic, CAudmixLogic );
	REG_GOBAL_MEMBER_FUNC( "CAudmixLogic::OnBtnRadioSpeak3", CAudmixLogic::OnBtnRadioSpeak3, m_pLogic, CAudmixLogic );
	REG_GOBAL_MEMBER_FUNC( "CAudmixLogic::OnBtnRadioSpeak4", CAudmixLogic::OnBtnRadioSpeak4, m_pLogic, CAudmixLogic );
	REG_GOBAL_MEMBER_FUNC( "CAudmixLogic::OnDelEdtAudMix1", CAudmixLogic::OnDelEdtAudMix1, m_pLogic, CAudmixLogic );
	REG_GOBAL_MEMBER_FUNC( "CAudmixLogic::OnDelEdtAudMix2", CAudmixLogic::OnDelEdtAudMix2, m_pLogic, CAudmixLogic );
	REG_GOBAL_MEMBER_FUNC( "CAudmixLogic::OnDelEdtAudMix3", CAudmixLogic::OnDelEdtAudMix3, m_pLogic, CAudmixLogic );
	REG_GOBAL_MEMBER_FUNC( "CAudmixLogic::OnDelEdtAudMix4", CAudmixLogic::OnDelEdtAudMix4, m_pLogic, CAudmixLogic );

	REG_GOBAL_MEMBER_FUNC( "CAudmixLogic::OnDragEnd", CAudmixLogic::OnDragEnd, m_pLogic, CAudmixLogic );  
	REG_GOBAL_MEMBER_FUNC( "CAudmixLogic::OnEdtKillFocus", CAudmixLogic::OnEdtKillFocus, m_pLogic, CAudmixLogic );  
    REG_GOBAL_MEMBER_FUNC( "CAudmixLogic::CloseDlg", CAudmixLogic::CloseDlg, m_pLogic, CAudmixLogic ); 
	
    REG_GOBAL_MEMBER_FUNC( "CAudmixLogic::OnDragOverEdit", CAudmixLogic::OnDragOverEdit, m_pLogic, CAudmixLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CAudmixLogic::OnDragLeaveEdit", CAudmixLogic::OnDragLeaveEdit, m_pLogic, CAudmixLogic ); 
    
    return true;
}

bool CAudmixLogic::UnRegFunc()
{
     
    return true;
}


bool CAudmixLogic::InitWnd( const IArgs & arg )
{   
	CWndLogicBase::InitWnd( arg ); 

	RefreshAudMixList( 0, 0 );

	for ( int i = 0; i < MAX_AUD_MIX_COUNT; i++ )
	{
		Window* pEdit = UIManagePtr->GetWindowPtr( m_tCtrlAudmixArray[i].strEdtMem, m_pWndTree );
		CDragWindow* p = CDragWindow::GetDragWindow();
		if ( p != NULL )
		{   
			p->RegisterDropWindow( pEdit );
		}
	}

	return true;
}

bool CAudmixLogic::OnBtnSwitchAudMixClick( const IArgs & arg )
{
	bool bState;
	UIManagePtr->GetSwitchState( m_strBtnAudSwitch, bState, m_pWndTree );

	if ( bState )
	{
		StartAudMix();
	}
	else
	{
		StopAudMix();	
	}

    UIManagePtr->EnableWindow( m_strBtnAudSwitch, false, m_pWndTree );

	return true;
}

void CAudmixLogic::StartAudMix()
{
   	TCMSConf tConf;
	BOOL32 bInConf = BusinessManagePtr->IsInConf( &tConf );
    if ( bInConf )
	{
		if ( IsAudMixListEmpty() )
		{
			u16 wSpeaker = TP_INVALID_INDEX;
			if ( tConf.m_wSpeaker != TP_INVALID_INDEX )
			{
				wSpeaker = tConf.m_wSpeaker;
			}
			else
			{
				wSpeaker = tConf.GetChairCnsID();
			}
			String strCaption;
			TCnsInfo* tCnsInfo = tConf.GetCnsInfoByID( wSpeaker );
			if ( tCnsInfo != NULL )
			{			
				m_tCtrlAudmixArray[0].wCnsID = tCnsInfo->m_wEpID;  
				m_nSelRadioSpeak = 0;
				if ( UpdateAudMixLst() )
				{
					m_bAudSwitchOn = TRUE;	
				}			
			}

		}
		else
		{
			UpdateAudMixLst();
		}
	}
}
    
 
void CAudmixLogic::StopAudMix()
{
	TCMSConf tConf;
	BOOL32 bInConf = BusinessManagePtr->IsInConf( &tConf );
	if ( bInConf )
	{
		u16 wConfID = tConf.m_wConfID;

		TConfAuxMixInfo tMixInfoList;
		tMixInfoList.m_wConfID = wConfID;
		tMixInfoList.m_bStart = FALSE;
		tMixInfoList.m_atAuxMixList = tConf.m_tAudmixList;
		//tMixInfoList.m_atAuxMixList.Clear();
		u16 wRe =  BusinessManagePtr->UpdateAudMixList( tMixInfoList );
		if ( wRe != NO_ERROR )
		{
			HANDLE_ERROR(wRe);
			return;
		}
		m_bAudSwitchOn = FALSE;
	}

}

bool CAudmixLogic::OnAddToAudMixList( const IArgs& args )
{
	int nSelEdit = -1;
	if ( -1 == m_nSelEdit )
	{
		//没有选中编辑框时，优先加到没有会场的Edit中
		for ( s32 i = 0; i < MAX_AUD_MIX_COUNT; i++ )
		{
			String strName;
			UIManagePtr->GetCaption( m_tCtrlAudmixArray[i].strEdtMem, strName, m_pWndTree );
			if ( strName.empty() )
			{
				nSelEdit = i;
				break;
			}
		}
		if ( -1 == nSelEdit )
		{
			UpdateCnsList();
			return false;
		}	
	}
	else
	{
		nSelEdit = m_nSelEdit;
	}
	if ( const Args_ClickItemInfo *pClickInfo = dynamic_cast<const Args_ClickItemInfo*>(&args) )
	{
		IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetParentItem()->GetItemData();
        if ( const Data_ConfCns* pDataCns = dynamic_cast< const Data_ConfCns*>( pBaseItem->GetUserData() ) )
        { 			
			TCnsInfo tCnsInfo = pDataCns->m_tConfCns;

			if ( IsInAudMixCtrl(tCnsInfo.m_wEpID) )
			{
				return false;
			}

			//UIManagePtr->SetCaption( m_tCtrlAudmixArray[nSelEdit].strEdtMem, tCnsInfo.m_achRoomName, m_pWndTree );
			m_tCtrlAudmixArray[nSelEdit].wCnsID = tCnsInfo.m_wEpID;  
			//UpdateAudMixLst();
			//OprAudMixCtrl( nSelEdit, em_DisListOpr_Add );
			//开启/关闭状态下，添加/删除/替换会场，走不同消息 2013/1/12 by wqq
 			bool bState ;
 			UIManagePtr->GetSwitchState( m_strBtnAudSwitch, bState, m_pWndTree );

			if ( bState )
			{
				OprAudMixCtrl( nSelEdit, em_DisListOpr_Add );
			} 
			else
			{
				UIManagePtr->SetCaption( m_tCtrlAudmixArray[nSelEdit].strEdtMem, tCnsInfo.m_achRoomName, m_pWndTree );
				UpdateAudMixLst();
			}

		}
	}
    
    UIManagePtr->LoadScheme( "SchmNormalCns", m_pWndTree, m_tCtrlAudmixArray[nSelEdit].strEdtMem );
	
    return true;
}


void CAudmixLogic::OprAudMixCtrl( int nIndex, EmDisListOprType emOprType )
{
	if ( nIndex < 0 && nIndex >= MAX_AUD_MIX_COUNT )
	{
		return;
	}

	TCMSConf tConf;
	BOOL32 bInConf = BusinessManagePtr->IsInConf( &tConf );	
	if ( bInConf )
	{
		u16 wConfID = tConf.m_wConfID;
		TTPDisListOpr tListOpr;
		tListOpr.m_wConfID = wConfID;
		tListOpr.m_wEpID = m_tCtrlAudmixArray[nIndex].wCnsID;
		tListOpr.m_wIndex = nIndex;
		tListOpr.m_emOprType = emOprType;

		u16 wRe = BusinessManagePtr->AudMixDisListOpr( tListOpr );
				
		if ( wRe != NO_ERROR )
		{
			HANDLE_ERROR(wRe);
			return;
		}
	}
}



BOOL CAudmixLogic::IsInAudMixCtrl( u16 wCnsId )
{
	for ( s32 i = 0; i < MAX_AUD_MIX_COUNT; i++ )
	{
		if ( m_tCtrlAudmixArray[i].wCnsID == wCnsId )
		{
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CAudmixLogic::IsAudMixListEmpty()
{
	for ( s32 i = 0; i < MAX_AUD_MIX_COUNT; i++ )
	{
		if ( m_tCtrlAudmixArray[i].wCnsID != TP_INVALID_INDEX )
		{
			return FALSE;
		}
	}
	return TRUE;	
}


void CAudmixLogic::ClearAudMixCtrl()
{
	if ( m_nSelRadioSpeak != -1 )
	{
		UIManagePtr->SetCheckState( m_tCtrlAudmixArray[m_nSelRadioSpeak].strRadioSpokes, 0, m_pWndTree );
		m_nSelRadioSpeak = -1;
	}
	if ( m_nSelEdit != -1 )
	{
		m_nSelEdit = -1;
	}
	for ( s32 i = 0; i < MAX_AUD_MIX_COUNT; i++ )
	{
		m_tCtrlAudmixArray[i].wCnsID = TP_INVALID_INDEX;
		UIManagePtr->SetCaption( m_tCtrlAudmixArray[i].strEdtMem, "", m_pWndTree );
	}
	UIManagePtr->LoadScheme( "SchmAudMixOff", m_pWndTree );
}

bool CAudmixLogic::UpdateAudMixLst()
{
	TCMSConf tConf;
	BOOL32 bInConf = BusinessManagePtr->IsInConf( &tConf );
	if ( bInConf )
	{
		u16 wConfID = tConf.m_wConfID;
		TConfAuxMixInfo tMixInfoList;
		tMixInfoList.m_wConfID = wConfID;
		// 获取当前状态下的会议讨论按钮的开关状态 2013/1/12 by wqq
 		bool bState ;
 	    UIManagePtr->GetSwitchState( m_strBtnAudSwitch, bState, m_pWndTree );
 		tMixInfoList.m_bStart = (BOOL32)bState;
		tMixInfoList.m_atAuxMixList.m_wSpeakerIndex = m_nSelRadioSpeak;
		for ( u16 i = 0; i < MAX_AUD_MIX_COUNT; i++ )
		{ 
			tMixInfoList.m_atAuxMixList.m_awList[i] = m_tCtrlAudmixArray[i].wCnsID ;
		}		

		u16 wRe =  BusinessManagePtr->UpdateAudMixList( tMixInfoList );
		if ( wRe != NO_ERROR )
		{
			HANDLE_ERROR(wRe);
			return false;
		}
    }
    return true;
}


HRESULT CAudmixLogic::RefreshAudMixList( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }

	u16 wConfID = (u16)wparam;
	
	TCMSConf tConfInfo;
    BOOL32 bInConf = BusinessManagePtr->IsInConf( &tConfInfo );
//     if ( ! bInConf )
//     {
//         return NO_ERROR;
//     }

	//更新控件
	bool bStart = (bool)tConfInfo.IsStartAudMix();

	bool bState = false;
	UIManagePtr->GetSwitchState( m_strBtnAudSwitch, bState, m_pWndTree );
	if ( bState != bStart )
	{
		UIManagePtr->SetSwitchState( m_strBtnAudSwitch, bStart, m_pWndTree );
	}
	UIManagePtr->EnableWindow( m_strBtnAudSwitch, true, m_pWndTree );

	//判断混音成员数量，如果只有一个，则不能删除
	int nMixNum = 0;
	for ( u16 j = 0; j< MAX_AUD_MIX_COUNT; j++ )
	{ 
		u16 wCnsID = tConfInfo.m_tAudmixList.m_awList[j];
		if ( wCnsID != TP_INVALID_INDEX )
		{  
			nMixNum++;
		}
	}
	
	String strCaption = "";
	int nCheck = 0;
	for ( int i = 0; i< MAX_AUD_MIX_COUNT; i++ )
	{ 
		u16 wCnsID = tConfInfo.m_tAudmixList.m_awList[i];
		if ( wCnsID == TP_INVALID_INDEX )
		{   
			strCaption = "";  
			nCheck = 0; 
			UIManagePtr->EnableWindow( m_tCtrlAudmixArray[i].strRadioSpokes, false, m_pWndTree );	
		}
		else 
		{  
			if ( i == tConfInfo.m_tAudmixList.m_wSpeakerIndex )
			{
				nCheck = 1; 	
				m_nSelRadioSpeak = i;
				//发言人现在也可以从混音列表中去掉
				//UIManagePtr->LoadScheme( "SchmSpeakCns", m_pWndTree, m_tCtrlAudmixArray[i].strEdtMem );					
			}
			else
			{
				nCheck = 0; 
				//UIManagePtr->LoadScheme( "SchmNormalCns", m_pWndTree, m_tCtrlAudmixArray[i].strEdtMem );
			}
			
			TCnsInfo* tCnsInfo = tConfInfo.GetCnsInfoByID( wCnsID );
			if ( tCnsInfo != NULL )
			{
				strCaption = tCnsInfo->m_achRoomName;
			}
			UIManagePtr->EnableWindow( m_tCtrlAudmixArray[i].strRadioSpokes, true, m_pWndTree );

            //bool bState ;
 	        //UIManagePtr->GetSwitchState( m_strBtnAudSwitch, bState, m_pWndTree );

            //on状态,只有一个会场不能删除该会场 ；off状态随意删除 dyy 2013年8月16日 Bug00152479
            //if ( 1 == nMixNum && tConfInfo.IsStartAudMix() )
			//{
				//B3版本 jyy 开启和关闭都可以删除会场
				//UIManagePtr->LoadScheme( "SchmSpeakCns", m_pWndTree, m_tCtrlAudmixArray[i].strEdtMem );
			//}
			//else
			//{
				//UIManagePtr->LoadScheme( "SchmNormalCns", m_pWndTree, m_tCtrlAudmixArray[i].strEdtMem );
			//}
		} 
		m_tCtrlAudmixArray[i].wCnsID = wCnsID;
		UIManagePtr->SetCaption( m_tCtrlAudmixArray[i].strEdtMem, strCaption, m_pWndTree );
		UIManagePtr->SetCheckState( m_tCtrlAudmixArray[i].strRadioSpokes, nCheck, m_pWndTree );	
		if ( !strCaption.empty() )
		{
			UIManagePtr->LoadScheme( "SchmNormalCns", m_pWndTree, m_tCtrlAudmixArray[i].strEdtMem );
		}
		else
		{
			UIManagePtr->LoadScheme( "SchmSpeakCns", m_pWndTree, m_tCtrlAudmixArray[i].strEdtMem );
		}
	}

	if ( bStart )
	{
		UIManagePtr->LoadScheme( "SchmAudMixOn", m_pWndTree );
	}
	else
	{
		UIManagePtr->LoadScheme( "SchmAudMixOff", m_pWndTree );
		//ClearAudMixCtrl();
	}

	UpdateCnsList();
	return NO_ERROR;
}

HRESULT CAudmixLogic::OnRefreshCnsList( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }
 

    UpdateCnsList(); 
	return NO_ERROR;
}


HRESULT CAudmixLogic::OnConfStateNotify( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }

    BOOL bInConf = BusinessManagePtr->IsInConf();
    if ( !bInConf )
    {
        ClearAudMixCtrl();

		Value_TransparentListOffset val;
		val.nOffset = 0;
		UIManagePtr->SetPropertyValue( val, m_strCnsLst, m_pWndTree );

		Value_TransparentListSelItem valSel;
		valSel.dwDataKey = -1;
		UIManagePtr->SetPropertyValue( valSel, m_strCnsLst, m_pWndTree );

        UIManagePtr->ShowWindow( g_stcStrAudMixDlg, false );
    }

	return NO_ERROR;
}


void CAudmixLogic::UpdateCnsList()
{
    if ( m_pWndTree == NULL )
    {
        return ;
    }
	
    TCMSConf tConfInfo;
    BOOL32 re = BusinessManagePtr->IsInConf( &tConfInfo );

    if ( re )
    {   
        Value_TouchListConfInfo val( tConfInfo );
		val.m_bDrag = TRUE;
		val.m_lstType = em_ConfLstTypeAudmix;
        UIManagePtr->SetPropertyValue( val, m_strCnsLst, m_pWndTree);
    }
	else
	{
		UIManagePtr->ShowWindow( g_stcStrAudMixDlg, false );
	}
}

bool CAudmixLogic::OnDragEnd( const IArgs& args )
{
	Args_WindowMsg WinMsg = *dynamic_cast<const Args_WindowMsg*>(&args);
	WindowMsg msg = WinMsg.m_Msg;
	
	s32 x = LOWORD(msg.lParam);
	s32 y = HIWORD(msg.lParam);
	CPoint point(x, y);
    
    CRect rect;
    
    for ( int i = 0; i < MAX_AUD_MIX_COUNT; i++ )
    {
        Window* pEdit = UIManagePtr->GetWindowPtr( m_tCtrlAudmixArray[i].strEdtMem, m_pWndTree );
        pEdit->GetWindowRect(&rect);
        if ( rect.PtInRect(point) )
        { 
            try
            {
                if ( Data_ConfCns *pConfCns = dynamic_cast<Data_ConfCns*>( (IData*)msg.wParam ) )
                {
                    TCnsInfo tCnsInfo = pConfCns->m_tConfCns;
                    
                    if ( IsInAudMixCtrl(tCnsInfo.m_wEpID) )
                    {
                        return false;
                    }
                    
                    UIManagePtr->SetCaption( m_tCtrlAudmixArray[i].strEdtMem, tCnsInfo.m_achRoomName, m_pWndTree );				
					m_tCtrlAudmixArray[i].wCnsID = tCnsInfo.m_wEpID; 

					pEdit->SendMessage( WM_EDIT_LEAVE, 0, 0 );

					//开启/关闭状态下拖动走不同消息 by wqq
 					bool bState ;
 					UIManagePtr->GetSwitchState( m_strBtnAudSwitch, bState, m_pWndTree );
					
					if ( bState )
					{
						OprAudMixCtrl( i, em_DisListOpr_Add );
					} 
					else
					{
						UpdateAudMixLst();
					}

					//UpdateAudMixLst();
					//OprAudMixCtrl( i, em_DisListOpr_Add );
                    
                    return true;
                }
            }
            catch (...)
            {
                return false;
            }                   
        }
    }
	
	return true;
}

bool CAudmixLogic::OnEdtKillFocus( const IArgs& args )
{
	if ( m_nSelEdit != -1 )
	{
		m_nSelEdit = -1;
	}
	return true;
}


bool CAudmixLogic::OnBtnEdtAudMix1( const IArgs & arg )
{
	m_nSelEdit = 0;
	return true;
}

bool CAudmixLogic::OnBtnEdtAudMix2( const IArgs & arg )
{
	m_nSelEdit = 1;
	return true;
}

bool CAudmixLogic::OnBtnEdtAudMix3( const IArgs & arg )
{
	m_nSelEdit = 2;
	return true;
}

bool CAudmixLogic::OnBtnEdtAudMix4( const IArgs & arg )
{
	m_nSelEdit = 3;
	return true;
}

bool CAudmixLogic::OnDelEdtAudMix1( const IArgs & arg )
{
 	bool bState ;
 	UIManagePtr->GetSwitchState( m_strBtnAudSwitch, bState, m_pWndTree );
	if ( m_tCtrlAudmixArray[0].wCnsID != TP_INVALID_INDEX )
	{		
		//OprAudMixCtrl( 0, em_DisListOpr_Del );
		if ( bState )
		{
			OprAudMixCtrl( 0, em_DisListOpr_Del );
		} 
		else
		{
			m_tCtrlAudmixArray[0].wCnsID = TP_INVALID_INDEX;
			UpdateAudMixLst();
		}
		//UpdateAudMixLst();
	}

    //dyy Bug00152479 2013年8月16日
    UIManagePtr->LoadScheme( "SchmSpeakCns", m_pWndTree, m_tCtrlAudmixArray[0].strEdtMem );

	return true;
}

bool CAudmixLogic::OnDelEdtAudMix2( const IArgs & arg )
{
 	bool bState ;
 	UIManagePtr->GetSwitchState( m_strBtnAudSwitch, bState, m_pWndTree );
	if ( m_tCtrlAudmixArray[1].wCnsID != TP_INVALID_INDEX )
	{
		//OprAudMixCtrl( 1, em_DisListOpr_Del );
		if ( bState )
		{
			OprAudMixCtrl( 1, em_DisListOpr_Del );
		} 
		else
		{
			m_tCtrlAudmixArray[1].wCnsID = TP_INVALID_INDEX;
			UpdateAudMixLst();
		}
		//UpdateAudMixLst();
	}

    //dyy Bug00152479 2013年8月16日
    UIManagePtr->LoadScheme( "SchmSpeakCns", m_pWndTree, m_tCtrlAudmixArray[1].strEdtMem );

	return true;
}

bool CAudmixLogic::OnDelEdtAudMix3( const IArgs & arg )
{
 	bool bState ;
 	UIManagePtr->GetSwitchState( m_strBtnAudSwitch, bState, m_pWndTree );
	if ( m_tCtrlAudmixArray[2].wCnsID != TP_INVALID_INDEX )
	{
		//OprAudMixCtrl( 2, em_DisListOpr_Del );
		if ( bState )
		{
			OprAudMixCtrl( 2, em_DisListOpr_Del );
		} 
		else
		{
			m_tCtrlAudmixArray[2].wCnsID = TP_INVALID_INDEX;
			UpdateAudMixLst();
		}
		//UpdateAudMixLst();
	}

    //dyy Bug00152479 2013年8月16日
    UIManagePtr->LoadScheme( "SchmSpeakCns", m_pWndTree, m_tCtrlAudmixArray[2].strEdtMem );

	return true;
}

bool CAudmixLogic::OnDelEdtAudMix4( const IArgs & arg )
{
 	bool bState ;
 	UIManagePtr->GetSwitchState( m_strBtnAudSwitch, bState, m_pWndTree );
	if ( m_tCtrlAudmixArray[3].wCnsID != TP_INVALID_INDEX )
	{
		//OprAudMixCtrl( 3, em_DisListOpr_Del );
		if ( bState )
		{
			OprAudMixCtrl( 3, em_DisListOpr_Del );
		} 
		else
		{
			m_tCtrlAudmixArray[3].wCnsID = TP_INVALID_INDEX;
			UpdateAudMixLst();
		}


		//UpdateAudMixLst();
	}

    //dyy Bug00152479 2013年8月16日
    UIManagePtr->LoadScheme( "SchmSpeakCns", m_pWndTree, m_tCtrlAudmixArray[3].strEdtMem );

	return true;
}

bool CAudmixLogic::OnBtnRadioSpeak1( const IArgs & arg )
{
	if ( m_nSelRadioSpeak != 0 )
	{
		m_nSelRadioSpeak = 0;
		UpdateAudMixLst();
	}

	return true;
}

bool CAudmixLogic::OnBtnRadioSpeak2( const IArgs & arg )
{
	if ( m_nSelRadioSpeak != 1 )
	{
		m_nSelRadioSpeak = 1;
		UpdateAudMixLst();
	}

	return true;
}

bool CAudmixLogic::OnBtnRadioSpeak3( const IArgs & arg )
{
	if ( m_nSelRadioSpeak != 2 )
	{
		m_nSelRadioSpeak = 2;
		UpdateAudMixLst();
	}

	return true;
}

bool CAudmixLogic::OnBtnRadioSpeak4( const IArgs & arg )
{
	if ( m_nSelRadioSpeak != 3 )
	{
		m_nSelRadioSpeak = 3;
		UpdateAudMixLst();
	}

	return true;
}

void CAudmixLogic::Clear()
{
	if ( m_pWndTree != NULL )
	{
		ClearAudMixCtrl();
		
		Value_TransparentListOffset val;
		val.nOffset = 0;
		UIManagePtr->SetPropertyValue( val, m_strCnsLst, m_pWndTree );

		Value_TransparentListSelItem valSel;
		valSel.dwDataKey = -1;
		UIManagePtr->SetPropertyValue( valSel, m_strCnsLst, m_pWndTree );

		UIManagePtr->ShowWindow( g_stcStrAudMixDlg, false );
	}	
}

bool CAudmixLogic::BtnSave2File( const IArgs & arg )
{
    return  UIManagePtr->SaveToFile( g_stcStrAudMixDlg  );  
}

bool  CAudmixLogic::CloseDlg( const IArgs & arg )
{
	return  UIManagePtr->ShowWindow( g_stcStrAudMixDlg, FALSE );  
}

//577 左侧列表拖至右侧edit上 右侧edit高亮
bool CAudmixLogic::OnDragOverEdit( const IArgs& args )
{
	if ( m_pWndTree == NULL )
    {
        return true;
    }
	
    Args_WindowMsg WinMsg = *dynamic_cast<const Args_WindowMsg*>(&args);
    WindowMsg msg = WinMsg.m_Msg;  
	
	s32 x = LOWORD(msg.lParam);
	s32 y = HIWORD(msg.lParam);
	CPoint point(x, y);
    
    CRect rect;
	for ( int i = 0; i < MAX_AUD_MIX_COUNT; i++ )
    {
        Window* pEdit = UIManagePtr->GetWindowPtr( m_tCtrlAudmixArray[i].strEdtMem, m_pWndTree );
        pEdit->GetWindowRect(&rect);
        if ( rect.PtInRect(point) )
        {
			if ( Data_ConfCns *pData = dynamic_cast<Data_ConfCns*>( (IData*)msg.wParam ) )
			{
				TCnsInfo tCnsInfo = pData->m_tConfCns;		
				m_nDragSelEdit = i;
				pEdit->SendMessage( WM_EDIT_SELECTED, 0, 0 );
//				OutputDebugString(("\n焦点落入框中\n"));
				return true;
			}
		}
	}
	return true;
}

bool CAudmixLogic::OnDragLeaveEdit( const IArgs& args )
{
	if ( m_pWndTree == NULL )
    {
        return true;
    }
	
    Args_WindowMsg WinMsg = *dynamic_cast<const Args_WindowMsg*>(&args);
    WindowMsg msg = WinMsg.m_Msg;  
	
	s32 x = LOWORD(msg.lParam);
	s32 y = HIWORD(msg.lParam);
	CPoint point(x, y);
    
    CRect rect;

	Window* pEdit = UIManagePtr->GetWindowPtr( m_tCtrlAudmixArray[m_nDragSelEdit].strEdtMem, m_pWndTree );
	pEdit->GetWindowRect(&rect);
    if ( !rect.PtInRect(point) )
	{
		pEdit->SendMessage( WM_EDIT_LEAVE, 0, 0 );
//		OutputDebugString(("\n焦点离开edit\n"));
		return true;
	}


	return true;
}


