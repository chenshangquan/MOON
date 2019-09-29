// funcLstMenu.cpp: implementation of the CFuncLstMenu class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cms.h"
#include "funcLstMenu.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFuncLstMenu* CFuncLstMenu::m_stcPThis = NULL;

CFuncLstMenu::CFuncLstMenu():m_pUserDefinedLogic(NULL),
                            m_tSelItem(),
                            m_pVctMenuLst( NULL )
{

}

CFuncLstMenu::~CFuncLstMenu()
{

}

CFuncLstMenu*CFuncLstMenu::Instance()
{
    if ( m_stcPThis == NULL )
    {
        m_stcPThis = new CFuncLstMenu();
    }

    return m_stcPThis;
}

void CFuncLstMenu::Init(  CUserDefinedLogic *pLogic  , vector <TConfMenuInfo> *pVctMenuLst)
{ 
    m_pUserDefinedLogic = pLogic;
    m_pVctMenuLst = pVctMenuLst;

    //menu 单击事件
    REG_GOBAL_MEMBER_FUNC( "CFuncLstMenu::SetFuncTop", CFuncLstMenu::SetFuncTop, m_stcPThis, CFuncLstMenu ) ; 
    REG_GOBAL_MEMBER_FUNC( "CFuncLstMenu::SetFuncBottom", CFuncLstMenu::SetFuncBottom, m_stcPThis, CFuncLstMenu ) ;
    REG_GOBAL_MEMBER_FUNC( "CFuncLstMenu::SetFuncUp", CFuncLstMenu::SetFuncUp, m_stcPThis, CFuncLstMenu ) ;
    REG_GOBAL_MEMBER_FUNC( "CFuncLstMenu::SetFuncDown", CFuncLstMenu::SetFuncDown, m_stcPThis, CFuncLstMenu ) ;
    REG_GOBAL_MEMBER_FUNC( "CFuncLstMenu::ShowItem", CFuncLstMenu::ShowItem, m_stcPThis, CFuncLstMenu ) ;
    REG_GOBAL_MEMBER_FUNC( "CFuncLstMenu::HideItem", CFuncLstMenu::HideItem, m_stcPThis, CFuncLstMenu ) ;
 
}


void CFuncLstMenu::SetCusSelItem( TConfMenuInfo tTemp)
{   
    m_tSelItem = tTemp;
    UpdateMenu();
}


//显示
bool CFuncLstMenu::ShowItem( const IArgs &args )
{ 
    if (  !m_tSelItem.strName.IsEmpty() )
    {
        m_tSelItem.bSetShow = TRUE; 
        TConfMenuInfo *p = GetMenuByName( m_tSelItem.strName ); 
        p->bSetShow = TRUE;
        UpdateMenu();
    }
    ShowWindow( FALSE );
    if ( m_pUserDefinedLogic != NULL )
    {
        m_pUserDefinedLogic->UpdateFuncList();
    }
    return true;
}

//隐藏
bool CFuncLstMenu::HideItem( const IArgs &args )
{  
    if ( !m_tSelItem.strName.IsEmpty() )
    {
        m_tSelItem.bSetShow = FALSE; 
        TConfMenuInfo *p = GetMenuByName( m_tSelItem.strName ); 
        p->bSetShow = FALSE;
        UpdateMenu();
    }

    ShowWindow( FALSE );
    if ( m_pUserDefinedLogic != NULL )
    {
        m_pUserDefinedLogic->UpdateFuncList();
    }

    return true;
}

// 置顶
bool CFuncLstMenu::SetFuncTop( const IArgs &args )
{   
    if (  m_tSelItem.strName.IsEmpty() )
    {
        PrtMsg( 0,emEventTypeCmsWindow,"CFuncLstMenu::SetFuncTop  fail: m_pSelItem == NULL ");
        return false;
    }

    if ( m_pVctMenuLst == NULL )
    {
        PrtMsg( 0,emEventTypeCmsWindow,"CFuncLstMenu::SetFuncTop  m_pVctMenuLst == NULL ");
        return false;
    }
   
    int nIndex = m_tSelItem.nIndex;
    if ( nIndex == 0 )
    {
        return true;
    } 
    else
    {   
         
        vector<TConfMenuInfo>::iterator it = m_pVctMenuLst->begin();
        while ( it !=  m_pVctMenuLst->end() )
        {
            if ( it->nIndex == nIndex )
            {
                it->nIndex = 0;
                
            }
            else if ( it->nIndex < nIndex )
            {  
                 it->nIndex += 1;
            }

            it ++;
        }
    }
    ShowWindow( FALSE );
    if ( m_pUserDefinedLogic != NULL )
    {  
//         m_pUserDefinedLogic->SetFuncLstOffset(  0);
        m_pUserDefinedLogic->SetFuncLstSel( 0 );
        m_pUserDefinedLogic->UpdateFuncList();
    }

    return true;
}


// 
bool CFuncLstMenu::SetFuncBottom( const IArgs &args )
{  

    if (  m_tSelItem.strName.IsEmpty() )
    {   
        PrtMsg( 0,emEventTypeCmsWindow,"CFuncLstMenu::SetFuncBottom  fail: m_pSelItem == NULL ");
        return false;
    }

    if ( m_pVctMenuLst == NULL )
    {
        PrtMsg( 0,emEventTypeCmsWindow,"CFuncLstMenu::SetFuncBottom  m_pVctMenuLst == NULL ");
        return false;
    }
    
    
    int nIndex = m_tSelItem.nIndex;
    if ( nIndex == m_pVctMenuLst->size() - 1  )
    {
        return true;
    } 
    else
    {    
        vector<TConfMenuInfo>::iterator it = m_pVctMenuLst->begin();
        while ( it !=  m_pVctMenuLst->end() )
        {
            if ( it->nIndex == nIndex )
            {
                 it->nIndex = m_pVctMenuLst->size() - 1 ;
            }
            else if ( it->nIndex > nIndex )
            {  
                  it->nIndex -= 1;
            }
            
            it ++;
        }
    }
      
    ShowWindow( FALSE );
    if ( m_pUserDefinedLogic != NULL )
    { 
        m_pUserDefinedLogic->SetFuncLstSel( m_pVctMenuLst->size() - 1 );
        m_pUserDefinedLogic->UpdateFuncList();
    }
    
    return true;


}


//cns上移
bool CFuncLstMenu::SetFuncUp( const IArgs &args )
{
    if (  m_tSelItem.strName.IsEmpty() )
    {   
        PrtMsg( 0,emEventTypeCmsWindow,"CFuncLstMenu::SetFuncTop  fail: m_pSelItem == NULL ");
        return false;
    }

    if ( m_pVctMenuLst == NULL )
    {
        PrtMsg( 0,emEventTypeCmsWindow,"CFuncLstMenu::SetFuncUp  m_pVctMenuLst == NULL ");
        return false;
    }

    
    int nIndex = m_tSelItem.nIndex;
    if ( nIndex == 0 )
    {
        return true;
    } 
    else
    {   
        TConfMenuInfo *pPre = NULL;
        TConfMenuInfo *pThis = NULL;
        vector<TConfMenuInfo>::iterator it = m_pVctMenuLst->begin();
        while ( it !=  m_pVctMenuLst->end() )
        {
            if ( it->nIndex == nIndex )
            {
                pThis = it;
                if ( pPre != NULL )
                {
                    pThis->nIndex = pPre->nIndex;
                    pPre->nIndex = nIndex;
                    
                    break;
                }
            }
            else if ( it->nIndex == nIndex - 1 )
            {  
                pPre = it;
                
                if ( pThis!= NULL )
                {
                    pThis->nIndex = pPre->nIndex;
                    pPre->nIndex = nIndex;
                    break;
                }
            }
            
            it ++;
        }
    }

    ShowWindow( FALSE );
     
    if ( m_pUserDefinedLogic != NULL )
    {
        m_pUserDefinedLogic->SetFuncLstSel( nIndex - 1 );
        m_pUserDefinedLogic->UpdateFuncList();
    }
    
    return true;
}


//下移
bool CFuncLstMenu::SetFuncDown(const IArgs &args )
{
    if (  m_tSelItem.strName.IsEmpty() )
    {   
        PrtMsg( 0,emEventTypeCmsWindow,"CFuncLstMenu::SetFuncTop  fail: m_pSelItem == NULL ");
        return false;
    }
    
    if ( m_pVctMenuLst == NULL )
    {
        PrtMsg( 0,emEventTypeCmsWindow,"CFuncLstMenu::SetFuncDown  m_pVctMenuLst == NULL ");
        return false;
    }
     
     
    int nIndex = m_tSelItem.nIndex;
    if ( nIndex == m_pVctMenuLst->size() - 1 )
    {
        return true;
    } 
    else
    {   
        TConfMenuInfo *pNext = NULL;
        TConfMenuInfo *pThis = NULL;
        vector<TConfMenuInfo>::iterator it = m_pVctMenuLst->begin();
        while ( it !=  m_pVctMenuLst->end() )
        {
            if ( it->nIndex == nIndex )
            {
                pThis = it;
                if ( pNext != NULL )
                {
                    pThis->nIndex = pNext->nIndex;
                    pNext->nIndex = nIndex;
                    
                    break;
                }
            }
            else if ( it->nIndex == nIndex + 1 )
            {  
                pNext = it;
                
                if ( pThis!= NULL )
                {
                    pThis->nIndex = pNext->nIndex;
                    pNext->nIndex = nIndex;
                    break;
                }
            }
            
            it ++;
        }
    }

    ShowWindow( FALSE );
    if ( m_pUserDefinedLogic != NULL )
    {  
        m_pUserDefinedLogic->SetFuncLstSel( nIndex + 1 );
        m_pUserDefinedLogic->UpdateFuncList();
    }
   
    return true;
}

void CFuncLstMenu::UpdateMenu()
{
    if ( m_tSelItem.bSetShow )
    {
        UIManagePtr->LoadScheme("SchmDisplayHide", NULL ,  g_stcStrFuncLstManageMenu);
    }
    else
    {
        UIManagePtr->LoadScheme("SchmDisplayShow", NULL ,  g_stcStrFuncLstManageMenu);
    }


    if ( m_tSelItem.nIndex  == 0 )
    {//禁用置顶 和 上移
        
        UIManagePtr->LoadScheme("SchmDisableUp", NULL ,  g_stcStrFuncLstManageMenu);
    }
    else 
    {
        UIManagePtr->LoadScheme("SchmEnableUp", NULL ,  g_stcStrFuncLstManageMenu);
    }

   
    if ( m_tSelItem.nIndex  == m_pVctMenuLst->size() - 1 )
    {//禁用置底 和 下移
        UIManagePtr->LoadScheme("SchmDisableDown", NULL ,  g_stcStrFuncLstManageMenu);
    }
    else 
    {
        UIManagePtr->LoadScheme("SchmEnableDown", NULL ,  g_stcStrFuncLstManageMenu);
    }

    

}

TConfMenuInfo * CFuncLstMenu::GetMenuByName( CString strName )
{
    if ( m_pVctMenuLst == NULL )
    {
        PrtMsg( 0,emEventTypeCmsWindow,"CFuncLstMenu::GetMenuByName  m_pVctMenuLst == NULL ");
        return NULL;
    }

    vector<TConfMenuInfo>::iterator it = m_pVctMenuLst->begin();
    while ( it != m_pVctMenuLst->end() )
    {
        if ( it->strName == strName )
        {
            return it;
        }

        it ++;
    }
    return NULL;
}


void CFuncLstMenu::ShowWindow( BOOL bShow /*= TRUE*/ )
{
    if ( bShow )
    {
        UIManagePtr->ShowWindow( g_stcStrFuncLstManageMenu);
    }
    else
    {
        UIManagePtr->ShowWindow( g_stcStrFuncLstManageMenu, false );
    }
}