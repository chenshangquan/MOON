// dualSrcManageLogic.cpp: implementation of the CDualSrcManageLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dualSrcManageLogic.h"
#include "msgBoxLogic.h"

const String CDualSrcManageLogic::m_strBtnDefDualSwitch = "DlgDualInfo/BtnDefaultDualSwitch";
const String CDualSrcManageLogic::m_strEdtDualName = "DlgDualInfo/EdtDualName";

CDualSrcManageLogic * CDualSrcManageLogic::m_pLogic = NULL;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CDualSrcManageLogic::CDualSrcManageLogic()
{
    m_bDefault = FALSE;
	m_nCurSelInfoIndex = -1;
}

CDualSrcManageLogic::~CDualSrcManageLogic()
{
	if ( m_pLogic != NULL )
	{   
		UnRegMsg();
		UnRegFunc();
		delete m_pLogic;
		m_pLogic = NULL; 
	}
}

CDualSrcManageLogic* CDualSrcManageLogic::GetLogicPtr()
{
	if ( m_pLogic == NULL )
	{  
		m_pLogic = new CDualSrcManageLogic();   
	}
	
	return m_pLogic;
}

void CDualSrcManageLogic::RegMsg()
{
    REG_MSG_HANDLER( UI_CNS_VGAINFO_NOTIFY, CDualSrcManageLogic::OnVgaInfoNotify, m_pLogic, CDualSrcManageLogic ); 		
	
}

void CDualSrcManageLogic::UnRegMsg()
{
}

bool CDualSrcManageLogic::RegCBFun()
{  
	REG_GOBAL_MEMBER_FUNC( "CDualSrcManageLogic::InitWnd", CDualSrcManageLogic::InitWnd, m_pLogic, CDualSrcManageLogic );
	REG_GOBAL_MEMBER_FUNC( "CDualSrcManageLogic::BtnToSysCfg", CDualSrcManageLogic::BtnToSysCfg, m_pLogic, CDualSrcManageLogic );
	REG_GOBAL_MEMBER_FUNC( "CDualSrcManageLogic::BtnToDualConfig", CDualSrcManageLogic::BtnToDualConfig, m_pLogic, CDualSrcManageLogic );
    REG_GOBAL_MEMBER_FUNC( "CDualSrcManageLogic::OnClickDualSrcItem", CDualSrcManageLogic::OnClickDualSrcItem, m_pLogic, CDualSrcManageLogic );
    REG_GOBAL_MEMBER_FUNC( "CDualSrcManageLogic::OnEdit", CDualSrcManageLogic::OnEdit, m_pLogic, CDualSrcManageLogic );
    REG_GOBAL_MEMBER_FUNC( "CDualSrcManageLogic::OnSave", CDualSrcManageLogic::OnSave, m_pLogic, CDualSrcManageLogic );
    REG_GOBAL_MEMBER_FUNC( "CDualSrcManageLogic::OnCancel", CDualSrcManageLogic::OnCancel, m_pLogic, CDualSrcManageLogic );
    
	return true;
}

bool CDualSrcManageLogic::UnRegFunc()
{	
	return true;
}

bool CDualSrcManageLogic::InitWnd( const IArgs & args )
{
	CWndLogicBase::InitWnd( args );
	
	return true;
}



bool CDualSrcManageLogic::BtnToSysCfg( const IArgs & args )
{
	UIManagePtr->LoadScheme( "SchmSysCfg", NULL, "SysCfgDlg" );
	return true;
}


bool CDualSrcManageLogic::BtnToDualConfig( const IArgs & args )
{
    if ( ! UIManagePtr->IsVisible( "DualSrcManageDlg/BtnEdit" ) )
    {
        bool bDefDual = false;
        UIManagePtr->GetSwitchState( m_strBtnDefDualSwitch, bDefDual, m_pWndTree );
        String strName;
        UIManagePtr->GetCaption( m_strEdtDualName, strName, m_pWndTree );
        
        if ( strcmp( strName.c_str(), m_tVgaInfo.m_achAlias ) != 0 || (BOOL)bDefDual != m_bDefault )
        {
            
            CString strMsg = "是否对编辑进行保存?";
            Args_MsgBox argMsg;
            argMsg.pOwnerWnd = UIManagePtr->GetWindowPtr( "DualSrcManageDlg" );
            int nResult = MSG_BOX( strMsg, TRUE, &argMsg);
            if ( IDOK == nResult )
            {
                if ( !OnSave(args) )
                {
                    return false;
                }
            }
            else
            {
                OnCancel(args);
            } 
        }
      
    }
	UIManagePtr->LoadScheme( "SchmShowDualLst", m_pWndTree );
	return true;
}

bool CDualSrcManageLogic::OnClickDualSrcItem( const IArgs & args )
{
    if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast<const Args_ClickItemInfo*>(&args) )
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetItemData();
        if ( const Data_DualSrc *pItemInfo = dynamic_cast<const Data_DualSrc*>( pBaseItem->GetUserData() ) )
        {
			m_tVgaInfo = pItemInfo->m_tVgaInfo;

            m_bDefault = FALSE;
            if ( m_tVgaInfo.m_emVgaType == m_tDualSrcInfo.emDefaultType )
            {
                m_bDefault = TRUE;
            }
            

			//记录当前编辑项的序号 [Bug00108862]  2012.10.8 by yujinjin
			m_nCurSelInfoIndex = -1;
			int nIndex = -1;
			vector<TVgaInfo> ::iterator it =  m_tDualSrcInfo.vctVgaInfo.begin() ;
			while( it != m_tDualSrcInfo.vctVgaInfo.end() )
			{   
				nIndex ++;
				if ( strcmp( m_tVgaInfo.m_achAlias, it->m_achAlias) == 0 )
				{
					m_nCurSelInfoIndex = nIndex;
					break;
				}

				it++;
			}
			

            UIManagePtr->SetSwitchState( m_strBtnDefDualSwitch, m_bDefault, m_pWndTree );
            UIManagePtr->SetCaption( m_strEdtDualName, m_tVgaInfo.m_achAlias, m_pWndTree );

            UIManagePtr->LoadScheme( "SchmShowDualInfo", m_pWndTree );
        }
    }
    return true;
}

bool CDualSrcManageLogic::OnEdit( const IArgs & args )
{
    UIManagePtr->LoadScheme( "SchmEdit", m_pWndTree );

    if ( m_bDefault )
    {
        UIManagePtr->EnableWindow( m_strBtnDefDualSwitch, false, m_pWndTree );
    }

    return true;
}

bool CDualSrcManageLogic::OnSave( const IArgs & args )
{
    bool bDefDual = false;
    UIManagePtr->GetSwitchState( m_strBtnDefDualSwitch, bDefDual, m_pWndTree );

    String strName;
    UIManagePtr->GetCaption( m_strEdtDualName, strName, m_pWndTree );

    Args_MsgBox msgArg;
	msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( m_strEdtDualName, m_pWndTree );
    if ( strName.empty() )
    {
        MSG_BOX( "演示源名称不能为空", FALSE, &msgArg );
		msgArg.pOwnerWnd->SetFocus();
        return false;
	}

    if ( strcmp( strName.c_str(), m_tVgaInfo.m_achAlias ) != 0 )
    {
        for ( int i = 0; i < m_tDualSrcInfo.vctVgaInfo.size(); i++ )
        {
            if ( strcmp( strName.c_str(), m_tDualSrcInfo.vctVgaInfo.at(i).m_achAlias ) == 0 )
            {
                MSG_BOX( "演示源名称已存在", FALSE, &msgArg );
				msgArg.pOwnerWnd->SetFocus();
                return false;
            }
        }
    }

    if ( strcmp( strName.c_str(), m_tVgaInfo.m_achAlias ) != 0 || (BOOL)bDefDual != m_bDefault )
    {
        TVgaInfo tVgaInfo;
        tVgaInfo.m_emVgaType = m_tVgaInfo.m_emVgaType;
        strncpy( tVgaInfo.m_achAlias, strName.c_str(), sizeof(tVgaInfo.m_achAlias) );


        ComInterface->SetDualPortInfo( tVgaInfo, (BOOL)bDefDual );
    }

    UIManagePtr->LoadScheme( "SchmShowDualInfo", m_pWndTree );
    
    return true;
}

bool CDualSrcManageLogic::OnCancel( const IArgs & args )
{
    UIManagePtr->SetSwitchState( m_strBtnDefDualSwitch, m_tVgaInfo.m_emVgaType == m_tDualSrcInfo.emDefaultType, m_pWndTree );
    UIManagePtr->SetCaption( m_strEdtDualName, m_tVgaInfo.m_achAlias, m_pWndTree );

    UIManagePtr->LoadScheme( "SchmShowDualInfo", m_pWndTree );
    return true;
}


LRESULT CDualSrcManageLogic::OnVgaInfoNotify( WPARAM wParam, LPARAM lParam )
{
    if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }
    
    ComInterface->GetDualSrcInfo( m_tDualSrcInfo );
    
    Value_ListDualSrc listDualSrc( m_tDualSrcInfo, "CDualSrcManageLogic::OnClickDualSrcItem", TRUE );
    UIManagePtr->SetPropertyValue( listDualSrc, "LstDualSrc", m_pWndTree );

   
	//同步更新当前编辑界面的双流原信息[Bug00108862] 2012.10.8 by yujinjin
    int nIndex = -1;
	vector<TVgaInfo> ::iterator it =  m_tDualSrcInfo.vctVgaInfo.begin() ;
	while( it != m_tDualSrcInfo.vctVgaInfo.end() )
	{   
		nIndex ++;
		if ( nIndex == m_nCurSelInfoIndex )
		{
			m_tVgaInfo = *it;
			if ( m_tVgaInfo.m_emVgaType == m_tDualSrcInfo.emDefaultType )
            {
                m_bDefault = TRUE;
            }
			break;
		}
		
		it++;
	}
    
    return NO_ERROR;
}


void CDualSrcManageLogic::Clear()
{ 
	if ( m_pWndTree != NULL )
	{
        m_tDualSrcInfo.Clear();
        m_bDefault = FALSE;
		m_nCurSelInfoIndex = -1;
	}
}
