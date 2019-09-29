// conftempLstLogic.cpp: implementation of the CConftempLstLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cms.h"
#include "conftempLstLogic.h"
#include "TouchListProperty.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//TTPConfTemplate CConftempLstLogic::m_tConfTempIDSel  ;                //confTempInfo界面需要操作的模板的ID
CConftempLstLogic *CConftempLstLogic::m_pLogic = NULL;   
const String CConftempLstLogic::m_strStcTitle = "StcLstTitle";
const String CConftempLstLogic::m_strBtnToTemplst = "BtnToConftempLst";

const String  CConftempLstLogic::m_strDlgTempInfo = "DlgTempInfo";					   //模板详细信息界面
const String  CConftempLstLogic::m_strStcTempName = "StcConfName";				    //模板名
const String  CConftempLstLogic::m_strStcTempID = "StcConftempID" ;			        	//模板ID
const String  CConftempLstLogic::m_strStcConfType = "StcConfType";						 //会议类型
const String  CConftempLstLogic::m_strStcPrimaCnsName = "stcPrimaCnsName";	  //主会场名   
const String  CConftempLstLogic::m_strBtnStartConf = "BtnStartConf";						//开启会议
const String  CConftempLstLogic::m_strLstSencondaryCns = "LstSecondaryCns";			 //会议分会场列表

const String  CConftempLstLogic::m_strLstPollCns = "LstTurnOrder";			 //轮询列表

const String  CConftempLstLogic::m_strPollInterval = "stcIntervalValue";		 

const String  CConftempLstLogic::m_strDlgTempList = "DlgTempLst";						 //模板列表界面    
const String  CConftempLstLogic::m_strLstTemp = "LstConftemp";
const String  CConftempLstLogic::m_strBtnRefresh = "BtnRefresh";

CConftempLstLogic::CConftempLstLogic()
{ 
    const_cast<String &> (m_strDlgTempInfo) = g_stcStrConftempDlg + "/" + m_strDlgTempInfo;
    const_cast<String &> (m_strDlgTempList) = g_stcStrConftempDlg + "/" +m_strDlgTempList;

    const_cast<String &> (m_strStcTempName) =m_strDlgTempInfo + "/" + m_strStcTempName;
    const_cast<String &> (m_strStcTempID) = m_strDlgTempInfo + "/" +m_strStcTempID;
    const_cast<String &> (m_strStcConfType)= m_strDlgTempInfo + "/" +m_strStcConfType;
    const_cast<String &> (m_strStcPrimaCnsName) = m_strDlgTempInfo + "/" + m_strStcPrimaCnsName;  
    const_cast<String &> (m_strPollInterval) = m_strDlgTempInfo + "/" + m_strPollInterval;  
    
    const_cast<String &> (m_strLstPollCns) = m_strDlgTempInfo + "/" + m_strLstPollCns;      

    const_cast<String &> (m_strBtnToTemplst) = g_stcStrConftempDlg + "/" + m_strBtnToTemplst;  

	const_cast<String &> (m_strLstSencondaryCns) =  m_strDlgTempInfo +  "/" + m_strLstSencondaryCns ; 
	const_cast<String &> (m_strLstTemp) =  g_stcStrConftempDlg +  "/" + m_strLstTemp ;  
}

CConftempLstLogic::~CConftempLstLogic()
{
	if ( m_pLogic != NULL )
	{   
		UnRegMsg();
		UnRegFunc();
		delete m_pLogic;
		m_pLogic = NULL;
	}
}
 


CConftempLstLogic* CConftempLstLogic::GetLogicPtr()
{
	if ( m_pLogic == NULL )
	{  
		m_pLogic = new CConftempLstLogic();  
	} 
	return m_pLogic;
}


void CConftempLstLogic::RegMsg()
{    
	REG_MSG_HANDLER( UI_CNS_REFRESH_CONFTEMPLATE_LIST, CConftempLstLogic::OnRefreshConftempLstNotify, m_pLogic, CConftempLstLogic );
	REG_MSG_HANDLER( UI_UMS_START_CONFTEMPLATE_RSP, CConftempLstLogic::OnStartConfRsp, m_pLogic, CConftempLstLogic );  

	REG_MSG_HANDLER( UI_CNC_WAITINGREFRESH_OVERTIME, CConftempLstLogic::OnWaitRefreshOverTime, m_pLogic, CConftempLstLogic );
}

void CConftempLstLogic::UnRegMsg()
{
//	UNREG_MSGHANDLER(  UI_UMS_REFRESH_CONFTEMPLATE_LIST ); 
}

bool CConftempLstLogic::RegCBFun()
{   	 
	REG_GOBAL_MEMBER_FUNC( "CConftempLstLogic::InitWnd", CConftempLstLogic::InitWnd, m_pLogic, CConftempLstLogic ) ;
	REG_GOBAL_MEMBER_FUNC( "CConftempLstLogic::BtnToTempInfoClick", CConftempLstLogic::BtnToTempInfoClick, m_pLogic, CConftempLstLogic ) ; 
    REG_GOBAL_MEMBER_FUNC( "CConftempLstLogic::BtnToTemplstClick", CConftempLstLogic::BtnToTemplstClick, m_pLogic, CConftempLstLogic ) ; 
    REG_GOBAL_MEMBER_FUNC( "CConftempLstLogic::OnClickTempItem", CConftempLstLogic::OnClickTempItem, m_pLogic, CConftempLstLogic ) ; 
	REG_GOBAL_MEMBER_FUNC( "CConftempLstLogic::BtnStartConfClick", CConftempLstLogic::BtnStartConfClick, m_pLogic, CConftempLstLogic ) ;     
    REG_GOBAL_MEMBER_FUNC( "CConftempLstLogic::BtnSaveToFileClick", CConftempLstLogic::BtnSaveToFileClick, m_pLogic, CConftempLstLogic ) ;
    REG_GOBAL_MEMBER_FUNC( "CConftempLstLogic::CloseDlg", CConftempLstLogic::CloseDlg, m_pLogic, CConftempLstLogic ); 
   
	REG_GOBAL_MEMBER_FUNC( "CConftempLstLogic::BtnRefreshTemp", CConftempLstLogic::BtnRefreshTemp, m_pLogic, CConftempLstLogic ); 
	
    
#ifdef JUST_FOR_TEST
    REG_GOBAL_MEMBER_FUNC( "CConftempLstLogic::BtnHangupConfClick", CConftempLstLogic::BtnHangupConfClick, m_pLogic, CConftempLstLogic ) ; 
#endif

	return true; 
}

bool CConftempLstLogic::UnRegFunc()
{
	UN_REG_GOBAL_FUNC( "CConftempLstLogic::InitWnd" );
	return true;
}


bool CConftempLstLogic::InitWnd(  const IArgs & arg )
{   
	CWndLogicBase::InitWnd( arg );
  
    OnRefreshConftempLstNotify( 0 , 0 );  
    return true;
}

void CConftempLstLogic::Clear() 
{  
    m_tConfTempIDSel.Clear();  

    if ( m_pWndTree != NULL )
    {  
       Value_TransparentListOffset val;
       val.nOffset = 0;
       UIManagePtr->SetPropertyValue( val, m_strLstTemp, m_pWndTree );

       Value_TransparentListSelItem valSel;
       valSel.dwDataKey = -1;
       UIManagePtr->SetPropertyValue( valSel, m_strLstTemp, m_pWndTree );
       UIManagePtr->LoadScheme( "",m_pWndTree,   "", false  );

       UIManagePtr->ShowWindow( "", false, m_pWndTree);
    }
    
}

bool CConftempLstLogic::BtnSaveToFileClick( const IArgs & arg )
{
      bool re = UIManagePtr->SaveToFile( g_stcStrConftempDlg );  
	  return re;
}

bool CConftempLstLogic::BtnToTemplstClick( const IArgs & arg )
{   
    UIManagePtr->LoadScheme( "",m_pWndTree);
    UIManagePtr->ShowWindow( g_stcStrConftempDlg );
	return true;
}

bool CConftempLstLogic::OnClickTempItem( const IArgs & arg  )
{ 
   if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast<const Args_ClickItemInfo*>(&arg) )
    {
        const IData *pIData = pClickInfo->m_pClickList->GetItemData()->GetUserData();
        if ( const Data_ConfTemp * pDataTemp = dynamic_cast< const Data_ConfTemp*>(pIData) )
        { 
            //m_tConfTempIDSel.Clear();
            //memcpy( &m_tConfTempIDSel, &pDataTemp->m_tConfTemp, sizeof(TCMSConfTemplate)) ;
            CRect rect = const_cast<CRect&>(pClickInfo->m_rcFrame);
            CMsgDispatch::SendMessage( UI_CONF_TEMP_ITEM_CLICK, (WPARAM)&arg, 0);
        }
    } 
    return true;
}


bool CConftempLstLogic::BtnToTempInfoClick( const IArgs & arg )
{   
    if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast<const Args_ClickItemInfo*>(&arg) )
    {
        const IData *pIData = pClickInfo->m_pClickList->GetParentItem()->GetItemData()->GetUserData();
        if ( const Data_ConfTemp * pDataTemp = dynamic_cast< const Data_ConfTemp*>(pIData) )
        { 
            m_tConfTempIDSel.Clear();
            memcpy( &m_tConfTempIDSel, &pDataTemp->m_tConfTemp, sizeof(TCMSConfTemplate)) ;

			Value_TransparentListOffset val;
			val.nOffset = 0;
			UIManagePtr->SetPropertyValue( val, m_strLstSencondaryCns );
			UIManagePtr->SetPropertyValue( val, m_strLstPollCns );
         
            //设置没有选中项
            Value_TransparentListSelItem valSel;
            valSel.dwDataKey = -1;
            UIManagePtr->SetPropertyValue( valSel, m_strLstSencondaryCns );
            UIManagePtr->SetPropertyValue( valSel, m_strLstPollCns );
         

            UpdateTempInfoDlg(); 
            
            Value_WindowVisible bVisible; 
            UIManagePtr->GetPropertyValue( bVisible, m_strDlgTempInfo  ); 
            if ( bVisible.bVisible == false )
            {    //水平的转换两个窗口
                //TransWnd( m_strDlgTempList,m_strDlgTempinfo,emTransWndHorizon);
//                 UIManagePtr->ShowWindow( m_strDlgTempList, false  ); 
//                 UIManagePtr->ShowWindow( m_strDlgTempInfo );
//                 UIManagePtr->ShowWindow( m_strBtnToTemplst );
                UIManagePtr->LoadScheme( "SchmTempInfo",m_pWndTree);
            }
        }
    }
    return true;
}

void CConftempLstLogic::UpdateTempInfoDlg()
{  
    Value_WindowCaption captVal;
    captVal.strCaption = m_tConfTempIDSel.m_achConfName;
    UIManagePtr->SetPropertyValue( captVal, m_strStcTempName );
     
    TCMSConfTemplate tem;
    tem =  m_tConfTempIDSel ;
    captVal.strCaption = "";
    TEpAddr * pEp = tem.GetCnsAddrByID( m_tConfTempIDSel.m_wDefaultChairMan );
    if ( pEp != NULL )
    {
        captVal.strCaption =  pEp->m_tAlias.m_abyAlias;
    } 
    UIManagePtr->SetPropertyValue( captVal, m_strStcPrimaCnsName );
   
    CString str;
    str.Format("%d",m_tConfTempIDSel.m_tTurnList.m_wInterval);
    captVal.strCaption =  (LPCTSTR)str;
    UIManagePtr->SetPropertyValue( captVal,  m_strPollInterval );
 
    //刷新列表 
    Value_TouchListTempCns touchListConfCns( m_tConfTempIDSel.m_atEpList, "",NULL,FALSE); 
    touchListConfCns.m_wChairManID = m_tConfTempIDSel.m_wDefaultChairMan;
    UIManagePtr->SetPropertyValue( touchListConfCns ,m_strLstSencondaryCns  );


    //刷新列表 
    TCMSConfTemplate tTemp;
    tTemp = m_tConfTempIDSel  ;
    Value_TouchListTempPoll  PollCns(  tTemp ); 
    UIManagePtr->SetPropertyValue( PollCns ,m_strLstPollCns  );

}


//刷新会议模板
bool CConftempLstLogic::BtnRefreshTemp( const IArgs & arg )
{
	UIManagePtr->EnableWindow( m_strBtnRefresh, false, m_pWndTree ); 
	
	
	u16 re = BusinessManagePtr->UpdateConfTemplate();
	if ( re !=  NO_ERROR )
    {
        HANDLE_ERROR(re);
        return false;
	}

    Window* pWnd = UIManagePtr->GetWindowPtr( g_stcStrConftempDlg );	
	CMsgDispatch::SendMessage( UI_CNC_BEGINWAITING_REFRESH, (WPARAM)pWnd, /*emGetRegInfoType_UMS*/emWaitRegInfo );
	return true;
}



bool CConftempLstLogic::BtnStartConfClick( const IArgs & arg )
{  
	//通过参数得到 当前模板ID
// 	u32 dwTempID = 0; 
// 	Value_WindowCaption val;
// 	UIManagePtr->GetPro = atol(val.strCaption.c_str());
   
    bool bVis =  UIManagePtr->IsVisible( g_stcStrConftempDlg );
    if ( !bVis )
    {
        PrtMsg( 0,emEventTypeCmsWindow, "CConftempLstLogic::BtnStartConfClick, 界面未显示，return出来" );
        return false;
    }

    PrtMsg( 0,emEventTypeCmsWindow, "CConftempLstLogic::BtnStartConfClick" );
    //u16 re =  BusinessManagePtr->CheckConfTemplateChairMan( m_tConfTempIDSel.m_wID );
    //if ( re !=  NO_ERROR )
    //{
    //    HANDLE_ERROR(re);
    //    return false;
    //}
	/*
    u16 wRe = BusinessManagePtr->StartTemplateConf(m_tConfTempIDSel.m_wID );

	if ( wRe != NO_ERROR )
	{
		HANDLE_ERROR( wRe );
	}
    else
    {
        //2011-9-5 添加呼叫中状态 
        CMsgDispatch::SendMessage( UI_UMS_SHOW_CALLING_DLG ,0 , 0 );  
        BusinessManagePtr->SetCurConfTemplate(m_tConfTempIDSel);
       
    }
	*/
    return true;
}

bool CConftempLstLogic::BtnHangupConfClick( const IArgs & arg )
{
   
   Value_WindowCaption val; 
    UIManagePtr->GetPropertyValue(val,   m_strStcTempID );
    u32 dwTempID = atol(val.strCaption.c_str());
     u16 wRe = BusinessManagePtr->HangupConf();
   
     if ( wRe != NO_ERROR )
     {
         HANDLE_ERROR(wRe);
     }
    return true;
}


HRESULT CConftempLstLogic::OnRefreshConftempLstNotify( WPARAM wparam, LPARAM lparam)
{   
    if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }

	m_vctConfTempList = *BusinessManagePtr->GetConfTempList();

    //刷新会议模板列表
    Value_TouchListConfTemp touchListConfTemp( &m_vctConfTempList, "CConftempLstLogic::OnClickTempItem", NULL );
    UIManagePtr->SetPropertyValue( touchListConfTemp, m_strLstTemp, m_pWndTree );

    CMsgDispatch::SendMessage( UI_CNC_ENDWAITING_REFRESH, 0, 0 );
    UIManagePtr->EnableWindow( m_strBtnRefresh, true, m_pWndTree );


	/*
     TplArray<TTPConfTemplate>* pTplConftempLst = BusinessManagePtr->GetConfTemplateList();
	 if (  pTplConftempLst != NULL )
	 {
		 //刷新会议模板列表
         ARRAY<string> vcIconitem;
         vcIconitem.push_back("ImageItemConftempShowInfo");
         Value_TouchListConfTemp touchListConfTemp( 0, "CConftempLstLogic::OnClickTempItem",&vcIconitem );
         touchListConfTemp.m_pAryConfTemplate = BusinessManagePtr->GetConfTemplateList();
         
        UIManagePtr->SetPropertyValue( touchListConfTemp ,m_strLstTemp  );  

        if (  m_tConfTempIDSel.m_wID == (u16)wparam )
        {   
            TTPConfTemplate* p = BusinessManagePtr->GetConfTemplateByID( m_tConfTempIDSel.m_wID );
            if ( p == NULL )
            {
                
               m_tConfTempIDSel.Clear();
               m_tConfTempIDSel.m_wID = INVALID_WORD;
            }
            else
            memcpy( &m_tConfTempIDSel, p,sizeof(TTPConfTemplate));

            UpdateTempInfoDlg();
        }
	 }
	 */
	return NO_ERROR;
}

/*	wParam = confTemplateID 
			lparam =  errorCode*/ 
HRESULT CConftempLstLogic::OnStartConfRsp( WPARAM wparam, LPARAM lparam)
{
	if ( lparam == NO_ERROR )
	{
		UIManagePtr->ShowWindow( g_stcStrConftempDlg, false);
	}

	return S_OK;
}


LRESULT CConftempLstLogic::OnWaitRefreshOverTime( WPARAM wParam, LPARAM lParam )
{
	if( m_pWndTree == NULL )
	{
		return NO_ERROR;
	}
	
	//2013.1.16 yjj  
	bool bVisSelf = UIFACTORYMGR_PTR->IsVisible( "", m_pWndTree );
	if (   !bVisSelf )
	{
		return S_OK;
	}
	
	BusinessManagePtr->ClearSipRegInfo( emGetRegInfoType_UMS );

//	EmGetRegInfoType emType = (EmGetRegInfoType)wParam;
	
//	if ( emType == emGetRegInfoType_UMS )
	{
		
		vector<TTPAlias>* pvctConfTempList = BusinessManagePtr->GetConfTempList();
		if ( pvctConfTempList != NULL )
		{
			//刷新会议模板列表			
			Value_TouchListConfTemp touchListConfTemp( 0, "CConftempLstLogic::OnClickTempItem", NULL );
			touchListConfTemp.m_pvctConfTemplate = BusinessManagePtr->GetConfTempList();			
			UIManagePtr->SetPropertyValue( touchListConfTemp, m_strLstTemp, m_pWndTree );
		}

        UIManagePtr->EnableWindow( m_strBtnRefresh, true, m_pWndTree );	
	}
	return NO_ERROR;
}



bool CConftempLstLogic::CloseDlg( const IArgs & arg  )
{
    return UIManagePtr->ShowWindow( g_stcStrConftempDlg, false);
}

