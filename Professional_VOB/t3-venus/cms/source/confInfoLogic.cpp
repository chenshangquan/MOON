// confInfoLogic.cpp: implementation of the CConfInfoLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cms.h"
#include "confInfoLogic.h"
#include "confCtrlLogic.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CConfInfoLogic *CConfInfoLogic::m_pLogic = NULL;
const String CConfInfoLogic::m_stcStrLstConf = "LstConf";

CConfInfoLogic::CConfInfoLogic()
{

}

CConfInfoLogic::~CConfInfoLogic()
{
    if ( m_pLogic != NULL )
    {   
        UnRegMsg();
        UnRegFunc();
        delete m_pLogic;
        m_pLogic = NULL; 
    }
}


CConfInfoLogic* CConfInfoLogic::GetLogicPtr()
{
    if ( m_pLogic == NULL )
    {  
        m_pLogic = new CConfInfoLogic();   
    }
    
    return m_pLogic;
}

void CConfInfoLogic::RegMsg()
{     
    REG_MSG_HANDLER(  UI_UMS_REFRESH_CONF_LIST, CConfInfoLogic::OnRefreshConfLst , m_pLogic, CConfInfoLogic  );
    //会议的cns列表更新 
    REG_MSG_HANDLER( UI_UMS_REFRESH_CONFCNS_LIST,CConfInfoLogic::OnRefreshConfLst, m_pLogic, CConfInfoLogic  );
    REG_MSG_HANDLER(  UI_UMS_HANGUP_CONF_RSP, CConfInfoLogic::OnRefreshConfLst , m_pLogic, CConfInfoLogic  );
   
}

void CConfInfoLogic::UnRegMsg()
{
    
}

bool CConfInfoLogic::RegCBFun()
{   	 
    REG_GOBAL_MEMBER_FUNC( "CConfInfoLogic::InitWnd", CConfInfoLogic::InitWnd, m_pLogic, CConfInfoLogic);

    REG_GOBAL_MEMBER_FUNC( "CConfInfoLogic::BtnConfLstItemHungupClick", CConfInfoLogic::BtnConfLstItemHungupClick, m_pLogic, CConfInfoLogic ) ; 


    REG_GOBAL_MEMBER_FUNC( "CConfInfoLogic::BtnSaveToFileClick", CConfInfoLogic::BtnSaveToFileClick, m_pLogic, CConfInfoLogic ) ; 
    REG_GOBAL_MEMBER_FUNC( "CConfInfoLogic::BtnClsoeClick", CConfInfoLogic::BtnClsoeClick, m_pLogic, CConfInfoLogic ) ; 


    REG_GOBAL_MEMBER_FUNC( "CConfInfoLogic::OnConfLstItemClick", CConfInfoLogic::OnConfLstItemClick, m_pLogic, CConfInfoLogic ) ; 
    
    return true;
}

bool CConfInfoLogic::UnRegFunc()
{
    //	UN_REG_GOBAL_FUNC( "CConftempEdtLogic::InitWnd" );
    return true;
}


bool CConfInfoLogic::InitWnd(  const IArgs & arg )
{   
    CWndLogicBase::InitWnd( arg );
    UpdateConfLst();
    return true;
}

bool CConfInfoLogic::BtnConfLstItemHungupClick( const IArgs & arg )
{  
   Window *p = UIManagePtr->GetWindowPtr( g_stcStrConfInfoDlg );

   UIManagePtr->ShowWindow( g_stcStrHungupConfPopDlg,FALSE);

   CConfCtrlLogic::GetLogicPtr()->HungupLocalConf( m_tSelCmsConf.m_wConfID , "是否要挂断会议?",true,p); 
    
   return true;
}

bool CConfInfoLogic::BtnSaveToFileClick( const IArgs & arg )
{
    return  UIManagePtr->SaveToFile( g_stcStrConfInfoDlg  );   
}

bool CConfInfoLogic::BtnClsoeClick( const IArgs & arg )
{
   return  UIManagePtr->ShowWindow( g_stcStrConfInfoDlg, false );
}


bool CConfInfoLogic::OnConfLstItemClick( const IArgs & arg )
{
    if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast<const Args_ClickItemInfo*>(&arg) )
    {
        const IData *pIData = pClickInfo->m_pClickList->GetItemData()->GetUserData();
        if ( const Data_Conf * pDataTemp = dynamic_cast< const Data_Conf*>(pIData) )
        {   
            m_tSelCmsConf = pDataTemp->m_tCmsConf;
            
            CRect rect = pClickInfo->m_rcFrame; 
            
            Value_WindowOwer owerVal;
            owerVal.pWnd = pClickInfo->m_pSrcWnd;
            UIManagePtr->SetPropertyValue(owerVal, g_stcStrHungupConfPopDlg);
            
            Value_WindowPos posVal;
            posVal.nX =  rect.right ;
            posVal.nY = rect.top  ;
			UIManagePtr->SetPropertyValue(posVal, g_stcStrHungupConfPopDlg);	

            UIManagePtr->ShowWindow( g_stcStrHungupConfPopDlg );
        }
    }

    return true;
}

void CConfInfoLogic::UpdateConfLst()
{
  if ( m_pWndTree == NULL )
  {
      return;
  }
 // ARRAY<TCMSConf>  *pConfLst = BusinessManagePtr->GetConfList();
//   ARRAY<String> vctSubItem;
//   vctSubItem.push_back("ImageItemConfHuangup");
//  Value_TouchListConf val( pConfLst , "CConfInfoLogic::OnConfLstItemClick"/*, &vctSubItem */);
  UIManagePtr->SetPropertyValue( val, m_stcStrLstConf, m_pWndTree);
}



HRESULT CConfInfoLogic::OnRefreshConfLst( WPARAM wparam, LPARAM lparam)
{
   UpdateConfLst();
   return NO_ERROR;
}

/**	 
* 功能:  清空所有状态和数据
* @return   
* @remarks	 
*/
void CConfInfoLogic::Clear()
{   if ( m_pWndTree )
    {
        Value_TransparentListSelItem valSel;
        valSel.dwDataKey = -1 ;
        UIManagePtr->SetPropertyValue( valSel, m_stcStrLstConf, m_pWndTree );

        Value_TransparentBaseListOffset val;
        val.nOffset = 0;
        UIManagePtr->SetPropertyValue( val, m_stcStrLstConf, m_pWndTree );
        
        UIManagePtr->ShowWindow("",false,m_pWndTree);

    }
    

};