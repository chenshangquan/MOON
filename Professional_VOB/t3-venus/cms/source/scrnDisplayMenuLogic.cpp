// scrnDisplayMenuLogic.cpp: implementation of the CScrnDisplayMenuLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "scrnDisplayMenuLogic.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CScrnDisplayMenuLogic *CScrnDisplayMenuLogic::m_pLogic = NULL;


const String CScrnDisplayMenuLogic::m_strDlgSelView = "SelViewLstDlg";
const String CScrnDisplayMenuLogic::m_strLstSelView = "SelViewLstDlg/LstCns";		     


CScrnDisplayMenuLogic::CScrnDisplayMenuLogic()
{
    m_bScrnID = -1;
}

CScrnDisplayMenuLogic::~CScrnDisplayMenuLogic()
{

    if ( m_pLogic != NULL )
    {   
        UnRegMsg();
        UnRegFunc();
        delete m_pLogic;
        m_pLogic = NULL; 
    }
}


CScrnDisplayMenuLogic* CScrnDisplayMenuLogic::GetLogicPtr()
{
    if ( m_pLogic == NULL )
    {  
        m_pLogic = new CScrnDisplayMenuLogic();   
    }
    
    return m_pLogic;
}

void CScrnDisplayMenuLogic::Clear()
{
	if ( m_pWndTree != NULL )
	{
		HideMenu();
	}
	UIManagePtr->ShowWindow( m_strDlgSelView, false );
}

void CScrnDisplayMenuLogic::RegMsg()
{   

    REG_MSG_HANDLER( UI_CNS_SCREEN_STATE_NOTIFY, CScrnDisplayMenuLogic::OnScreenStateNotify ,m_pLogic, CScrnDisplayMenuLogic);

    REG_MSG_HANDLER( UI_CNS_RECV_DUAL_NOTIFY, CScrnDisplayMenuLogic::OnScreenStateNotify ,m_pLogic, CScrnDisplayMenuLogic);
   

    REG_MSG_HANDLER( UI_CNS_CONFSTATE_NOTIFY, CScrnDisplayMenuLogic::OnConfStateNotify, m_pLogic, CScrnDisplayMenuLogic ); 
    REG_MSG_HANDLER( UI_UMS_UPDATE_CONFINFO, CScrnDisplayMenuLogic::OnConfStateNotify, m_pLogic, CScrnDisplayMenuLogic );
    REG_MSG_HANDLER( UI_UMS_REFRESH_CONFCNS_LIST, CScrnDisplayMenuLogic::OnConfStateNotify, m_pLogic, CScrnDisplayMenuLogic );

    REG_MSG_HANDLER( UI_CNS_SEL_VIEW_RSP, CScrnDisplayMenuLogic::OnSelViewRsp ,m_pLogic, CScrnDisplayMenuLogic);	
    REG_MSG_HANDLER( UI_CNS_CANCLE_SEL_VIEW_RSP, CScrnDisplayMenuLogic::OnCancleSelViewRsp ,m_pLogic, CScrnDisplayMenuLogic);

    REG_MSG_HANDLER( UI_CNS_SCRN_DISPLAY_DUAL_RSP, CScrnDisplayMenuLogic::OnSelDualRsp ,m_pLogic, CScrnDisplayMenuLogic);	
    REG_MSG_HANDLER( UI_CNS_STOP_SCRN_DISPLAY_DUAL_RSP, CScrnDisplayMenuLogic::OnCancleSelDualRsp ,m_pLogic, CScrnDisplayMenuLogic);


    REG_MSG_HANDLER( UI_CNS_SCRN_DISPLAY_LOCAL_RSP, CScrnDisplayMenuLogic::OnSelLocalRsp ,m_pLogic, CScrnDisplayMenuLogic);	
    REG_MSG_HANDLER( UI_CNS_STOP_SCRN_DISPLAY_LOCAL_RSP, CScrnDisplayMenuLogic::OnCancleSelLocalRsp ,m_pLogic, CScrnDisplayMenuLogic);
	
    REG_MSG_HANDLER( UI_CNS_SEL_TVSVIEW_RSP, CScrnDisplayMenuLogic::OnSelTVSViewRsp ,m_pLogic, CScrnDisplayMenuLogic);	
    REG_MSG_HANDLER( UI_CNS_CANCLE_SEL_TVSVIEW_RSP, CScrnDisplayMenuLogic::OnCancleSelTVSViewRsp ,m_pLogic, CScrnDisplayMenuLogic); 

}


void CScrnDisplayMenuLogic::UnRegMsg()
{
    
}

bool CScrnDisplayMenuLogic::RegCBFun()
{   	 
    REG_GOBAL_MEMBER_FUNC( "CScrnDisplayMenuLogic::InitWnd", CScrnDisplayMenuLogic::InitWnd, m_pLogic, CScrnDisplayMenuLogic);

    REG_GOBAL_MEMBER_FUNC( "CScrnDisplayMenuLogic::BtnSrcnSelWatch", CScrnDisplayMenuLogic::BtnSrcnSelWatch, m_pLogic, CScrnDisplayMenuLogic);
     
    REG_GOBAL_MEMBER_FUNC( "CScrnDisplayMenuLogic::BtnCancleSrcnSelWatch", CScrnDisplayMenuLogic::BtnCancleSrcnSelWatch, m_pLogic, CScrnDisplayMenuLogic);
    
    REG_GOBAL_MEMBER_FUNC( "CScrnDisplayMenuLogic::BtnSrcnDispDual", CScrnDisplayMenuLogic::BtnSrcnDispDual, m_pLogic, CScrnDisplayMenuLogic);

    REG_GOBAL_MEMBER_FUNC( "CScrnDisplayMenuLogic::BtnCancleSrcnDispDual", CScrnDisplayMenuLogic::BtnCancleSrcnDispDual, m_pLogic, CScrnDisplayMenuLogic);
    
    REG_GOBAL_MEMBER_FUNC( "CScrnDisplayMenuLogic::BtnSrcnDispLocal", CScrnDisplayMenuLogic::BtnSrcnDispLocal, m_pLogic, CScrnDisplayMenuLogic);
    
    REG_GOBAL_MEMBER_FUNC( "CScrnDisplayMenuLogic::BtnCancleSrcnDispLocal", CScrnDisplayMenuLogic::BtnCancleSrcnDispLocal, m_pLogic, CScrnDisplayMenuLogic);
     
    REG_GOBAL_MEMBER_FUNC( "CScrnDisplayMenuLogic::OnCnsSelViewClick", CScrnDisplayMenuLogic::OnCnsSelViewClick, m_pLogic, CScrnDisplayMenuLogic);
    
    REG_GOBAL_MEMBER_FUNC( "CScrnDisplayMenuLogic::OnIconCnsLstAddClick", CScrnDisplayMenuLogic::OnIconCnsLstAddClick, m_pLogic, CScrnDisplayMenuLogic );

    REG_GOBAL_MEMBER_FUNC( "CScrnDisplayMenuLogic::OnBtnSynthesis", CScrnDisplayMenuLogic::OnBtnSynthesis, m_pLogic, CScrnDisplayMenuLogic );   
    return true;
}

bool CScrnDisplayMenuLogic::UnRegFunc()
{
    return true;
}


bool CScrnDisplayMenuLogic::InitWnd( const IArgs & arg )
{   
    CWndLogicBase::InitWnd( arg ); 
    
     
    
    return true;
}



bool CScrnDisplayMenuLogic::BtnSrcnSelWatch( const IArgs & arg )
{   
	//电视墙配置开启后,在点击显示器1、3屏选看后,直接发送消息通知cns切换输出信号源  ----JYY  2014.5.14
	if ( m_bScrnID == 0 || m_bScrnID == 2 )
	{
		BOOL bIsTVWALL = BusinessManagePtr->GetDisplayState();
		if ( bIsTVWALL )
		{
			u16 wRe = BusinessManagePtr->SetSelTVSView( m_bScrnID );
			if ( wRe != NO_ERROR )
			{
				HANDLE_ERROR( wRe );
				return false;
			}
			return true;
		}
	}

	POINT pt;
	
	Value_WindowSize val;
	UIManagePtr->GetPropertyValue( val, m_strDlgSelView );
	
	Value_WindowSize valParent;
	UIManagePtr->GetPropertyValue( valParent, g_stcStrMainFrameDlg );
	
	pt.x = ( valParent.nWidth - val.nWidth ) / 2;
	pt.y = 53; 
	UIFACTORYMGR_PTR->SetWndPos( pt, m_strDlgSelView, NULL, g_stcStrMainFrameDlg );
	
	UIManagePtr->ShowWindow(  m_strDlgSelView, true );
 
    return true;
}


bool CScrnDisplayMenuLogic::BtnCancleSrcnSelWatch( const IArgs & arg )
{   
	BOOL bIsTVWALL = BusinessManagePtr->GetDisplayState();
	if ( bIsTVWALL )
	{
		u16 wRe = BusinessManagePtr->CancleSelTVSView( m_bScrnID );
		if ( wRe != NO_ERROR )
		{
			HANDLE_ERROR( wRe );
			return false;
		}
		return true;
	}

    UIManagePtr->ShowWindow(  m_strDlgSelView, false );
    BusinessManagePtr->CancleSelView( m_bScrnID );
    
    return true;
}

bool CScrnDisplayMenuLogic::BtnSrcnDispDual( const IArgs & arg )
{
    BusinessManagePtr->ScrnDisplayDual( m_bScrnID );
   // HideMenu(   );
    return true;
}

bool CScrnDisplayMenuLogic::BtnCancleSrcnDispDual( const IArgs & arg )
{
    BusinessManagePtr->ScrnStopDisplayDual( m_bScrnID );
   // HideMenu(   );
    return true;
}


bool CScrnDisplayMenuLogic::BtnSrcnDispLocal( const IArgs & arg )
{
    BusinessManagePtr->ScrnDisplayLocal( m_bScrnID );
    //  HideMenu(   );
    return true;
}

bool CScrnDisplayMenuLogic::BtnCancleSrcnDispLocal( const IArgs & arg )
{
    BusinessManagePtr->ScrnStopDisplayLocal( m_bScrnID );
   // HideMenu(   );
    return true;
}



void CScrnDisplayMenuLogic::ShowMenu( u8 bScrnID, CPoint& pos )
{
    if ( m_pWndTree == NULL )
    {
        return ;
    }

    m_bScrnID = bScrnID;
    UpdateMenu( m_bScrnID );
 
    Value_WindowSize wsize;
    UIManagePtr->GetPropertyValue( wsize, "", m_pWndTree );
    
    Value_WindowPos pw;
    pw.nY = pos.y - 13 - wsize.nHeight;
    pw.nX = pos.x - 13 - wsize.nWidth; 
    
    UIManagePtr->SetPropertyValue( pw, "", m_pWndTree );
    
    
    UIManagePtr->ShowWindow( "", true, m_pWndTree );
}

void CScrnDisplayMenuLogic::HideMenu(  )
{
    UIManagePtr->ShowWindow( "", false, m_pWndTree );
}


void CScrnDisplayMenuLogic::UpdateMenu( u8 bSrcnID  )
{   
    TScreenInfo tScrnInfo;
    
    u16 re = BusinessManagePtr->GetCnsScreenInfoByID( bSrcnID, tScrnInfo );
    if ( NO_ERROR == re )
    {
         UpdateScrnSelView( tScrnInfo );
         UpdateScrnSelDual( tScrnInfo );
         UpdateScrnSelLocal( tScrnInfo );
         UIManagePtr->UpdateUI( "",m_pWndTree );

    }
}


void CScrnDisplayMenuLogic::UpdateScrnSelView( TScreenInfo& tScrnInfo)
{   
    String strSchm = "";

    TCMSConf tConfInfo;
    BOOL32 bInconf = BusinessManagePtr->IsInConf( &tConfInfo );
    if ( !bInconf )
    {
        return;
    }

	BOOL bIsTVWALL = BusinessManagePtr->GetDisplayState();
    
    if ( tConfInfo.m_emConfType == emCallType_P2P )
    {   
		//电视墙开启后,点对点会议可以点击选看电视墙
		if ( bIsTVWALL )
		{
			if ( tScrnInfo.byScreenID == 1 )		//只有1、3屏幕选看按钮才可用
			{
				strSchm = "SchmSelViewDisable";
			}
			else
			{
				if ( emPic_SelTVS ==  tScrnInfo.emPosPic )
				{
					strSchm =  "SchmCancleSelTVS";
				}
				else
				{
					strSchm =  "SchmSelTVS";
				}
			}
		}
		else
		{
			strSchm = "SchmSelViewDisable";
		}
    }
    else
    {
		if ( bIsTVWALL )
		{
			if ( tScrnInfo.byScreenID == 1 )		//只有1、3屏幕选看按钮才可用
			{
				strSchm = "SchmSelViewDisable";
			}
			else
			{
				if ( emPic_SelTVS ==  tScrnInfo.emPosPic )
				{
					strSchm =  "SchmCancleSelTVS";
				}
				else
				{
					strSchm =  "SchmSelTVS";
				} 
			}
		}
		else
		{
			BOOL32 bChairCns = BusinessManagePtr->IsLocalCnsChairMan();
			if ( !bChairCns )
			{
				strSchm = "SchmSelViewDisable";
			}
			else
			{
				//如果本地为主席会场，则允许选看，否则不允许进行选看操作			
				if ( emPic_SelView ==  tScrnInfo.emPosPic  )
				{
					strSchm =  "SchmCancleSelView";
				}
				else
				{
					strSchm =  "SchmSelView";
				} 
	        }
		}
    }

    UIManagePtr->LoadScheme( strSchm, m_pWndTree, "btnScrnSelView", false ); 
}

void CScrnDisplayMenuLogic::UpdateScrnSelDual( TScreenInfo& tScrnInfo)
{   
     
    String strSchm = "";
    

    BOOL32 bIsRcvDual = BusinessManagePtr->IsRcvDual();
    if ( bIsRcvDual )
    {   
        if ( tScrnInfo.emPosPic == emPic_SelDual )
        {
            strSchm =  "SchmCancleDual";
        }
        else
        {
            strSchm =  "SchmDual"; 
        }

        
    }
    else
    {
        strSchm = "SchmNotRcvDual" ; 
    }
     
    
    UIManagePtr->LoadScheme( strSchm, m_pWndTree, "btnScrnSelDual", false  ); 
}


void CScrnDisplayMenuLogic::UpdateScrnSelLocal( TScreenInfo& tScrnInfo)
{   
    
    String strSchm = "";  
     
    if ( tScrnInfo.emPosPic == emPic_SelLocal )
    {
        strSchm =  "SchmCancleLocal"; 
    }
    else
    {
        strSchm =  "SchmLocal"; 
    } 
    
    UIManagePtr->LoadScheme( strSchm, m_pWndTree, "btnScrnSelLocal", false  ); 
}


void CScrnDisplayMenuLogic::RefreshSelViewLst()
{
    TCMSConf tConfInfo ;
    bool bIn = BusinessManagePtr->IsInConf( &tConfInfo );
    if ( bIn )
    {
        Value_TouchListConfInfo val(tConfInfo);
        val.m_lstType = em_ConfLstTypwSelView;
        val.m_strClickItemFunc = "CScrnDisplayMenuLogic::OnCnsSelViewClick";
        
        UIManagePtr->SetPropertyValue( val, m_strLstSelView );
    }
    
}


void CScrnDisplayMenuLogic::ResetSelViewList()
{
    Value_TransparentListOffset val;
    val.nOffset = 0;
    UIManagePtr->SetPropertyValue( val, m_strLstSelView );
    
    Value_TransparentListSelItem valSel;
    valSel.dwDataKey = -1;
    UIManagePtr->SetPropertyValue( valSel, m_strLstSelView );
}


HRESULT CScrnDisplayMenuLogic::OnScreenStateNotify( WPARAM wparam, LPARAM lparam )
{
    bool bVis = UIManagePtr->IsVisible( "", m_pWndTree );
    if ( bVis )
    {
        UpdateMenu( m_bScrnID );
    }
    return S_OK;
}

HRESULT CScrnDisplayMenuLogic::OnConfStateNotify( WPARAM wparam, LPARAM lparam )
{
    if ( m_pWndTree == NULL )
    {   
        return NO_ERROR;
    }
    
    
    TCMSConf tConfInfo ;
    BOOL32 bInConf = BusinessManagePtr->IsInConf( &tConfInfo ); 
    
    if ( bInConf  )
    {		 
        RefreshSelViewLst();  //更新选看列表 
    }
    else
    {   
        ResetSelViewList();
        UIManagePtr->ShowWindow( m_strDlgSelView, false );  //隐藏选看列表
        HideMenu();
         
    }
    return NO_ERROR;
}


bool CScrnDisplayMenuLogic::OnCnsSelViewClick( const IArgs & arg )
{
    if ( m_bScrnID == -1 )
    {
        return false;
    }
    
    if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast<const Args_ClickItemInfo*>(&arg) )
    {
        const IData *pIData = pClickInfo->m_pClickList->GetItemData()->GetUserData();
        if ( const Data_ConfCns* pData = dynamic_cast< const Data_ConfCns*>(pIData) )
        {   
            u16 wRe = BusinessManagePtr->SetSelView( m_bScrnID, pData->m_tConfCns.m_wEpID );
            if ( wRe != NO_ERROR )
            {
                HANDLE_ERROR( wRe );
            }

            UIManagePtr->ShowWindow( m_strDlgSelView, false ); 
        }
    } 
    
    return true;
}
 

bool CScrnDisplayMenuLogic::OnIconCnsLstAddClick( const IArgs & arg )
{
    if ( m_bScrnID == -1 )
    {
        return false;
    }
    
    if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast<const Args_ClickItemInfo*>(&arg) )
    {
        const IData *pIData = pClickInfo->m_pClickList->GetParentItem()->GetItemData()->GetUserData();
        if ( const Data_ConfCns* pData = dynamic_cast< const Data_ConfCns*>(pIData) )
        {   
            u16 wRe = BusinessManagePtr->SetSelView( m_bScrnID, pData->m_tConfCns.m_wEpID );
            if ( wRe != NO_ERROR )
            {
                HANDLE_ERROR( wRe );
            }
            
            UIManagePtr->ShowWindow( m_strDlgSelView ,false );   
        }
    } 
    
    return true;
}


 
 
HRESULT CScrnDisplayMenuLogic::OnSelViewRsp( WPARAM wparam, LPARAM lparam )
{
    BOOL32 bInConf = BusinessManagePtr->IsInConf();
    if ( bInConf )
    {   
        TTPCnsInfo tCnsInfo;
        ComInterface->GetLocalCnsInfo( tCnsInfo );

        u8 byScreenID = (u8)wparam;
        CString msg = "" ;
        EmTPViewResult emRe = ( EmTPViewResult ) lparam;  
        if ( emRe != emViewSucceed )
        {              
            CString msg;
            switch ( emRe )
            {
            case emViewFailStatusError:
                msg = "当前屏未处于激活状态";  //不加提示，直接变化状态               
                break;
            case emViewFailOffline:
                msg = "选看会场不在线";
                break;
            case emViewFailDstNoVid:         //dyy 2013年9月26日ln确认swj要求添加
                msg =  "选看失败，会场无视频";
                break;
            case emViewFailNoResource:         //dyy 2013年9月26日ln确认swj要求添加
                msg =  "选看失败，会场无资源";
                break;
            default:
                msg = "未知原因";
                break;                
            }
            
        	if ( tCnsInfo.m_emLevel == emTPSipProvince )
            {
                byScreenID += 2;
            }
            else
            {
                byScreenID += 1;
            }
            
            
            CString tip;
            tip.Format( "%d号屏选看失败: %s", byScreenID, msg );
 //           UIManagePtr->LoadScheme(m_strSchmActive,NULL,UIDATAMGR->GetCurSimulateDlgName() +"/"+m_screenInfoArry[byScreenID -1 ].strCtlScreenState);
            ShowPopMsg(msg);
        } 
 
        //解决选看后 再切换发言人，ums先发送屏未处于激活状态，再发送取消选看消息  2011-12-27 by yjj
       //OnScreenStateNotify(wparam,0);  根据屏状态的notify进行更新 2012-3-15 yjj
    }

    return S_OK;
}

/*
enum EmTPViewResult
{
emViewSucceed = 0,
emViewFailUnKown,
emViewFailStatusError,
emViewFailOffline
};
*/ 
HRESULT CScrnDisplayMenuLogic::OnCancleSelViewRsp( WPARAM wparam, LPARAM lparam )
{
    BOOL32 bInConf = BusinessManagePtr->IsInConf();
    if ( bInConf )
    {   
        TTPCnsInfo tCnsInfo;
        ComInterface->GetLocalCnsInfo( tCnsInfo );

        u8 byScreenID = (u8)wparam;
        EmTPViewResult emRe = ( EmTPViewResult ) lparam; 
        if ( emRe != emViewSucceed )
        {  
            
            CString msg;
            switch ( emRe )
            {
            case emViewFailStatusError:
                msg = "当前未处于选看状态";  //不加提示，直接变化状态
                
                if ( tCnsInfo.m_emLevel == emTPSipProvince )
                {
                    byScreenID += 1;
                }
                
                return S_OK;
                break;
            case emViewFailOffline:
                msg = "选看会场不在线";
                break;
            default:
                msg = "未知原因";
                break; 
            }
          
            if ( tCnsInfo.m_emLevel == emTPSipProvince )
            {
                byScreenID += 2;
            }
            else
            {
                byScreenID += 1;
            }

            CString tip;
            tip.Format("%d号屏取消选看失败:%s",byScreenID,msg);
           // UIManagePtr->LoadScheme(m_strSchnCancleView,NULL,g_strSimulateCnsDlgName+"/"+m_screenInfoArry[byScreenID -1 ].strCtlScreenState);
            ShowPopMsg(tip);
        } 
 
        
        //解决选看后 再切换发言人，ums先发送屏未处于激活状态，再发送取消选看消息  2011-12-27 by yjj
        //OnScreenStateNotify( wparam,0);  根据屏状态的notify消息进行更新 2012-3-15
    }
    
    return S_OK;
}

/*
emAddDualRcvSucceed = 0,
emAddDualRcvFailNoDual,       //没有收双流
emAddDualRcvFailIllegalPos,   //非法位置
emAddDualRcvFailNoPos,        //没有空闲位置了
emAddDualRcvFailStatusError,  //当前已经是双流状态了
emAddDualRcvFailUnKown,
*/
HRESULT CScrnDisplayMenuLogic::OnSelDualRsp( WPARAM wparam, LPARAM lparam )
{   
    BOOL32 bIsInconf  =  BusinessManagePtr->IsInConf();
    if ( bIsInconf )
    {
        u8 sCrnID =  (u8)wparam;
        EmTPAddDualRcvResult em =  (EmTPAddDualRcvResult)lparam;
        switch( em )
        {
        case emAddDualRcvFailNoDual:
            ShowPopMsg("看演示失败：当前未处于接收双流状态");
            break;
            
        case emAddDualRcvFailIllegalPos:
            ShowPopMsg("看演示失败：通道非法");
            break;
        case emAddDualRcvFailNoPos:
            ShowPopMsg("看演示失败：无空闲通道");
            break;
        case emAddDualRcvFailUnKown:
            ShowPopMsg("看演示失败"); //("看演示失败：未知错误"); 2012-8-7 SE石文娟确认未知错误不做提示 by yjj
            break;
        }
    }
    
    return S_OK;

}   


HRESULT CScrnDisplayMenuLogic::OnCancleSelDualRsp( WPARAM wparam, LPARAM lparam )
{

     return S_OK;
}

/*
emViewLocalSucceed = 0,
emViewLocalFailUnKown,
emViewLocalFailStatusError,       //状态错误，取消时表示当前屏不在VIEW LOCAL，选看时表示已在看本地状态
emViewLocalFailOffline,
emViewLocalFailIllegalPos,
*/
HRESULT CScrnDisplayMenuLogic::OnSelLocalRsp( WPARAM wparam, LPARAM lparam )
{
 
    BOOL32 bIsInconf  =  BusinessManagePtr->IsInConf();
    if ( bIsInconf )
    {
        u8 sCrnID =  (u8)wparam;
        EmTPViewLocalResult em =  (EmTPViewLocalResult)lparam;
        switch( em )
        {
        case  emViewLocalFailUnKown:
            ShowPopMsg("回显失败"); //：未知错误");2012-8-7 SE石文娟确认未知错误不做提示 by yjj
            break;
        case emViewLocalFailStatusError:       //状态错误，取消时表示当前屏不在VIEW LOCAL，选看时表示已在看本地状态
           // ShowPopMsg("回显失败：当前正在看本地");
            break;
        case emViewLocalFailOffline:
            ShowPopMsg("回显失败：本地会场不在线");
            break;

        case emViewLocalFailIllegalPos:
            ShowPopMsg("回显失败：非法位置");
            break;

        }
    }

    return S_OK;
}  

HRESULT CScrnDisplayMenuLogic::OnCancleSelLocalRsp( WPARAM wparam, LPARAM lparam )
{

    return S_OK;
}


bool CScrnDisplayMenuLogic::OnBtnSynthesis( const IArgs & arg )
{
    if ( m_bScrnID == -1 )
    {
        return false;
    }

    u16 wRe = BusinessManagePtr->SetSelView( m_bScrnID, TP_INVALID_INDEX );
    if ( wRe != NO_ERROR )
    {
        HANDLE_ERROR( wRe );
    }
    
    UIManagePtr->ShowWindow( m_strDlgSelView, false ); 

    return true;
}

HRESULT CScrnDisplayMenuLogic::OnSelTVSViewRsp( WPARAM wparam, LPARAM lparam )
{
    BOOL32 bInConf = BusinessManagePtr->IsInConf();
    if ( bInConf )
    {   
        TTPCnsInfo tCnsInfo;
        ComInterface->GetLocalCnsInfo( tCnsInfo );
		
        u8 byScreenID = (u8)wparam;
        BOOL bSuccess = (BOOL) lparam;  
        if ( !bSuccess )
        {    
			UIManagePtr->LoadScheme( "SchmSelTVS", m_pWndTree, "btnScrnSelView", false ); 
			if ( tCnsInfo.m_emLevel == emTPSipProvince )
            {
                byScreenID += 2;
            }
            else
            {
                byScreenID += 1;
            }
                   
            CString tip;
            tip.Format( "%d号屏选看电视墙失败", byScreenID );
            ShowPopMsg(tip);
        } 
    }
	
    return S_OK;
}

HRESULT CScrnDisplayMenuLogic::OnCancleSelTVSViewRsp( WPARAM wparam, LPARAM lparam )
{
    BOOL32 bInConf = BusinessManagePtr->IsInConf();
    if ( bInConf )
    {   
        TTPCnsInfo tCnsInfo;
        ComInterface->GetLocalCnsInfo( tCnsInfo );
		
        u8 byScreenID = (u8)wparam;
        BOOL bSuccess = (BOOL) lparam;  
        if ( !bSuccess )
        {  		
			UIManagePtr->LoadScheme( "SchmCancleSelTVS", m_pWndTree, "btnScrnSelView", false ); 
            if ( tCnsInfo.m_emLevel == emTPSipProvince )
            {
                byScreenID += 2;
            }
            else
            {
                byScreenID += 1;
            }
			
            CString tip;
            tip.Format( "%d号屏取消选看电视墙失败", byScreenID );
            ShowPopMsg(tip);
        } 
    }
    
    return S_OK;
}
