// uiManage.cpp: implementation of the CUiManage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cms.h"
#include "uiManage.h"
#include "ctrlFactory.h"
#include "valueset.h"
#include "WndTreeHelp.h"
#include "UiFactroyLog.h"
#include "listDataAssist.h"
 
#include"saveXmlHelp.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#define  SYSTEM_XML "system.xml"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CUiManage* CUiManage::m_pStMySelf = NULL;


CUiManage::CUiManage():m_vctConfMenu()
{  
}

CUiManage::~CUiManage()
{
    if ( NULL != m_pStMySelf )
    {  
        delete m_pStMySelf;
        m_pStMySelf = NULL;
        CSystem *pSystem = CSystem::GetSingletonPtr();
        if (  pSystem ) 
        {
            delete pSystem ;
            pSystem = NULL;
        }
    } 
}



CUiManage* CUiManage::GetUiManagePtr()
{
    if ( NULL == m_pStMySelf )
    {   
        
        m_pStMySelf = new CUiManage(); 
        //new CUiFactroyLog();

        if (  CSystem::GetSingletonPtr() == NULL  ) 
        {
            new CSystem( SYSTEM_XML );
			CSystem::GetSingletonPtr()->Launch();
        }      

        InitWndName();
        RegWindowProperty();
        RegCtrls();
        
    } 
    return m_pStMySelf;
}

void CUiManage::InitWndName()
{
    
}


bool CUiManage::SetPropertyValue( const IValue& value,   String strWndName, const IWndTree* pWndTree /*= NULL */)
{
    const IWndTree *pItem = UIManagePtr->GetWindow ( strWndName , pWndTree );
    if ( pItem == NULL )
    {
        return false;
    }
    
    return SetPropertyValue( value, pItem->m_ptItemData->pWnd , pItem->m_ptItemData->strType );
}

bool CUiManage::SetPropertyValue( const IValue& value, const Window* window,  const String& strWndType )
{
    return CPropertyAssist::GetSingletonPtr()->SetProperty( value,  window, strWndType );
}


bool CUiManage::GetPropertyValue( IValue& value ,   String strWndName,  const IWndTree* pWndTree /*= NULL */)
{
    const IWndTree *pItem = UIManagePtr->GetWindow ( strWndName ,pWndTree );
    if ( pItem == NULL )
    {
        return false;
    }
    
    return GetPropertyValue( value, pItem->m_ptItemData->pWnd , pItem->m_ptItemData->strType );
}


bool CUiManage::GetPropertyValue(   IValue& value, const Window* window,  const String& strWndType )
{
    return	 CPropertyAssist::GetSingletonPtr()->GetValue(  value,  window, strWndType );
}

bool CUiManage::HandleMsg( WindowMsg* pMsg )
{
    return CWndMsgEventManage::GetSingletonPtr()->TransMsg( pMsg );
}

void CUiManage::UpdateUI(  IWndTree* pWndTree )
{
    if ( pWndTree != NULL )
    {
        WndInfo* pInfo = pWndTree->GetItemData();
        if ( pInfo != NULL  && pInfo->pWnd != NULL)
        {
			HWND hWnd = 0;
			CWnd* pWnd = pInfo->pWnd->GetParent();
			if ( pWnd != NULL && pInfo->pWnd->GetStyle() & WS_CHILD )
			{
				hWnd = pInfo->pWnd->m_hWnd;
				pWnd->PostMessage( WM_REDRAW_UI, 0, (LPARAM)hWnd );
			}
			else
			{
				pInfo->pWnd->PostMessage( WM_REDRAW_UI, 0, TRUE );
			}
        }
    }
}

void CUiManage::UpdateUI( String strWndName,   IWndTree* pWndTree/* = NULL*/)
{
    const IWndTree*  p  =  GetWindow( strWndName, pWndTree);
    IWndTree* p2 = const_cast<IWndTree* > (p);
    UpdateUI( p2 );
}

u16 CUiManage::ShowWindow( String strWndName, bool bShow /*= true */,const IWndTree* pWndTree /*= NULL */, BOOL bReDraw )
{ 

    if ( !strWndName.empty() )
    {
        pWndTree = const_cast<IWndTree* >( CUiManage::GetWindow( strWndName,pWndTree ) );
    } 
    if ( pWndTree == 0   )
    {
        return false;
	}
    
    Value_WindowVisible valueVisible;
    valueVisible.bVisible = bShow;
	   
    bool re =  UIManagePtr->SetPropertyValue( valueVisible , pWndTree->m_ptItemData->pWnd , pWndTree->m_ptItemData->strType ); 

	if ( bReDraw )
	{
		UpdateUI( const_cast<IWndTree *>(pWndTree) );
	}

    u16 wRe = NO_ERROR;
    wRe = ( re == true? NO_ERROR:ERR_CMS);
    return wRe;
}


bool CUiManage::EnableWindow( String strWndName, bool bEnable /* = true */, const IWndTree* pWndTree /* = NULL */ )
{
	Value_WindowEnable valueEnable;
	valueEnable.bEnable = bEnable;
	
	bool bRet = UIManagePtr->SetPropertyValue( valueEnable, strWndName, pWndTree );
	UpdateUI( strWndName, const_cast<IWndTree*>(pWndTree) );
	return bRet;
}


bool CUiManage::SetCaption( String strWndName, String strCaption, const IWndTree* pWndTree /* = NULL */, BOOL bReDraw )
{
	Value_WindowCaption valueCaption;
    valueCaption.strCaption = strCaption;
	
	bool bRet = UIManagePtr->SetPropertyValue( valueCaption, strWndName, pWndTree );
	if ( bReDraw )
	{
		UpdateUI( strWndName, const_cast<IWndTree*>(pWndTree) );
	}	
	return bRet;
}

bool CUiManage::GetCaption( String strWndName, String& strCaption, const IWndTree* pWndTree /* = NULL */ )
{
	Value_WindowCaption valueCaption;
    valueCaption.strCaption = "";
	bool bRe = UIManagePtr->GetPropertyValue( valueCaption, strWndName, pWndTree );
	
    strCaption = valueCaption.strCaption;
	
	return bRe;
}

bool CUiManage::SetFocus( String strWndName, const IWndTree* pWndTree /* = NULL */ )
{
	Window* pWnd = UIManagePtr->GetWindowPtr( strWndName, pWndTree );
	if ( pWnd != NULL )
	{
		pWnd->SetFocus();
	}
	return true;
}

bool CUiManage::SetCheckState( String strWndName, int nCheckState, const IWndTree* pWndTree /* = NULL */ )
{
	Value_CButtonCheckState valueCheckState;
	valueCheckState.nCheckState = nCheckState;
	
	return UIManagePtr->SetPropertyValue( valueCheckState, strWndName, pWndTree );
}

bool CUiManage::SetSwitchState( String strWndName, bool bState, const IWndTree* pWndTree /* = NULL */ )
{
	Value_SwitchState valueState;
	valueState.bState = bState;
	
	return UIManagePtr->SetPropertyValue( valueState, strWndName, pWndTree );
}

bool CUiManage::GetSwitchState( String strWndName, bool& bState, const IWndTree* pWndTree /* = NULL */ )
{
	Value_SwitchState valueState;
    valueState.bState = false;
	bool bRe = UIManagePtr->GetPropertyValue( valueState, strWndName, pWndTree );
	
    bState = valueState.bState;	
	return bRe;
}

bool CUiManage::SetTransparentDlgImage( String strWndName, String strPath, const IWndTree* pWndTree /* = NULL */ )
{
	Value_TransparentDlgImage valueImage;
	valueImage.strImage = strPath;
	bool bRe = UIManagePtr->SetPropertyValue( valueImage, strWndName, pWndTree );
	return bRe;
}

bool CUiManage::SetSelState( String strWndName, bool bState, const IWndTree* pWndTree /* = NULL */ )
{
	Value_DragButtonSel valueSel;
	valueSel.bSel = bState;
	
	return UIManagePtr->SetPropertyValue( valueSel, strWndName, pWndTree );
}

bool CUiManage::GetSelState( String strWndName, bool& bState, const IWndTree* pWndTree /* = NULL */ )
{
	Value_DragButtonSel valueSel;
    valueSel.bSel = false;
	bool bRe = UIManagePtr->GetPropertyValue( valueSel, strWndName, pWndTree );
	bState = valueSel.bSel ;
	return bRe;
}

bool CUiManage::SetDragBtnOnline( String strWndName, bool bOnline, const IWndTree* pWndTree /* = NULL */ )
{
	Value_DragButtonOnline valueOnline;
	valueOnline.bOnline = bOnline;
	
	return UIManagePtr->SetPropertyValue( valueOnline, strWndName, pWndTree );
}
 
bool CUiManage::IsVisible( String strWndName, const IWndTree* pWndTree /*= NULL*/ )
{
   Value_WindowVisible bVisble;
   bVisble.bVisible = false;
   bool re  = UIManagePtr->GetPropertyValue( bVisble, strWndName, pWndTree );
   if ( re = false )
   {
//       TRACE("\n[CUiManage::IsVisible]GetPropertyValue return false \n");
   }
   return bVisble.bVisible;
}


Window* CUiManage::GetModalWnd( String strWndName ) 
{
    IWndTree *pItem = const_cast<IWndTree*>(UIManagePtr->GetWindow(  strWndName ));
    if ( NULL == pItem )
    { 
        return NULL;
    }
    
    return pItem->m_ptItemData->pWnd ;
}


const IWndTree* CUiManage::GetWindow( String strName, const IWndTree* pWndTree /* = NULL*/ )  
{     
    if ( strName.empty() )
    {
        return pWndTree;
    }


    if ( pWndTree == NULL  )
    {   
        char chPart = CWndTreeHelp::chPartitionChar;
        int size = strName.find( chPart ); 

        if ( size >= 0 ) 
        {
            String strFirstWnd = strName.substr(0,size);
            IWndTree* pTree = const_cast<IWndTree* >( CWindowManage::GetSingletonPtr()->GetWindowTree( strFirstWnd));
            if ( pTree ) 
            {
                String strWnd = strName.substr(size+1,strName.size());
                return GetWindow(strWnd,pTree);
            }
            
        }
        
        return  CWindowManage::GetSingletonPtr()->GetWindowTree( strName);
        
    } 


    
    return  CWndTreeHelp::GetWindow( strName,  pWndTree );	  
}




const IWndTree* CUiManage::GetWindow( Window* pWnd, const IWndTree* pWndTree )
{
    return  CWndTreeHelp::GetWindow( pWnd,pWndTree );		  
}


Window* CUiManage::GetWindowPtr( String strName, const IWndTree* pWndTree /* = NULL*/ )
{
    const IWndTree* pTreeInfo = GetWindow( strName, pWndTree );
    if ( pTreeInfo == NULL )
    {
        return NULL;
    } 
    return pTreeInfo->m_ptItemData->pWnd ;
}

bool CUiManage::LoadScheme( String strSchemeName,IWndTree* pWndTree /*= NULL*/ , String strWndName /*= ""*/ , bool bInvalidate /*= true */)
{
	if ( !strWndName.empty() )
	{
		pWndTree = const_cast<IWndTree* >( CUiManage::GetWindow( strWndName,pWndTree ) );
	} 
	if ( pWndTree == 0   )
	{
		return false;
	}
	bool bRet = CSchemeHelp::LoadScheme(strSchemeName,pWndTree);
	
    if ( bInvalidate )
    {
        UpdateUI( pWndTree );
    }
	
	return bRet;
}


u16 CUiManage::DestroyWindow( String strWndName )
{
    IWndTree* pTreeInfo =   const_cast< IWndTree *>(CUiManage::GetWindow(   strWndName ));
    if ( pTreeInfo == NULL )
    {
        return ERR_CMS;
    } 
    
    bool bRe =  CWindowManage::GetSingletonPtr()->DestoryWnd( pTreeInfo );
    
    u16 wRe = ( bRe == true ? NO_ERROR : ERR_CMS );
    return wRe;
}


bool CUiManage::DestoryWnd( Window* pWnd )
{
    return CWindowManage::GetSingletonPtr()->DestoryWnd( pWnd );
}

bool CUiManage::DestoryWnd( IWndTree* pWndTree )
{
    return CWindowManage::GetSingletonPtr()->DestoryWnd( pWndTree );
}

 

//strSavePropertyName 要保存的属性名，bForceSave 如果要保存的属性不在当前方案中，是否强制保存
bool   CUiManage::SaveToFile( String strWndName ,string strSaveWndName/* = ""*/,string strSavePropertyName/* = ""*/, BOOL32 bForceSave/* = false*/)
{ 
 
   return CSaveXmlHelp::SaveXml( strWndName,strSaveWndName ,strSavePropertyName, bForceSave ); 
}


String CUiManage::GetImagePath()
{
   return CSystem::GetSingletonPtr()->GetImagePath();
}

bool CUiManage::HideAllWindow()
{
    
    IWndTree* pWndTree = CWindowManage::GetSingletonPtr()->GetRoot();
    if ( NULL == pWndTree )
    {
        return false;
    }
    
    int count = pWndTree->GetItemCount();
    IWndTree*  pLogin = pWndTree->GetItemByKey( g_stcStrLoginDlg );
    IWndTree*  pMainFrame= pWndTree->GetItemByKey( g_stcStrMainFrameDlg );
    
    for ( int i = 0; i<count; i++ )
    {
        IWndTree* pSubWndTree = pWndTree->GetItemByIndex( i );
        
        if ( NULL != pSubWndTree && NULL != pSubWndTree->GetItemData()->pWnd && 
                ( pSubWndTree != pLogin && pSubWndTree != pMainFrame) )
        {   
             
            pSubWndTree->GetItemData()->pWnd->ShowWindow( SW_HIDE );
        }
    }
   
     UIManagePtr->SetTransparentDlgImage( g_stcStrMainFrameDlg, g_strMainFrameLoginBkg );
    
    return true;   
}

void CUiManage::HandleErr( DWORD dwErrID, CString strMsp /* =  */, BOOL bShowNow /* = FALSE */ )
{
	CString str = "" ;

	//等待osp发送消息,不用报错
	if ( ERR_CNC_WAIT_FOR_SEND_CMD == dwErrID )
	{
		return;
	}

    if ( strMsp.IsEmpty() )
    {
        str = GET_ERR_STRING( dwErrID );
    }
    else
    {
        str.Format( "%s: %s", strMsp, GET_ERR_STRING(dwErrID) ) ;
    }
    
	if ( !str.IsEmpty() )
	{
		if ( bShowNow )
		{
			ShowPopMsgNow( str );
		}
		else
		{
			ShowPopMsg( str );
		}		
	}
}


BOOL CUiManage::SaveConfMenu( vector<TConfMenuInfo> & lstFunc)
{ 
     
    String strFileName = CSystem::GetSingletonPtr()->GetWindowXml( g_strFuncLstData );
    
    if ( !strFileName.empty() )
    {  
        TListItem item;
        vector<TListItem> lst;
        vector<TConfMenuInfo>::iterator it = lstFunc.begin();
        while( it != lstFunc.end() )
        {
            item.strItemName = it->strName;
            item.nIndex = it->nIndex;
            item.bVisible = it->bSetShow;
            lst.push_back( item );
            it++;
        }

        CListDataAssist  cLstAssist;
        
        BOOL re = cLstAssist.SetListData( strFileName, g_strFuncLstData, lst );
        UpdateConfMenuAccordFile();
        return re;
    }
    return FALSE;
}


BOOL CUiManage::UpdateConfMenuAccordFile()
{
    String strFileName = CSystem::GetSingletonPtr()->GetWindowXml( g_strFuncLstData );
    
    if ( !strFileName.empty() )
    { 
        CListDataAssist  cLstAssist;
        vector<TListItem> lstFile;
        BOOL re = cLstAssist.GetListData(strFileName, g_strFuncLstData,lstFile);
        if ( re )
        {
            vector<TConfMenuInfo>::iterator it = m_vctConfMenu.begin();
            while ( it != m_vctConfMenu.end() )
            {
                vector<TListItem>::iterator itFile = lstFile.begin();
                while( itFile != lstFile.end() )
                {
                    if ( strcmp( itFile->strItemName.c_str(), (LPCTSTR)it->strName) == 0 )
                    {

                        it->nIndex = itFile->nIndex;
                        it->bSetShow = itFile->bVisible;
                        break;
                    }
                    itFile ++;
                }

                it++;
            }
        }
    }

    return FALSE;
     
}