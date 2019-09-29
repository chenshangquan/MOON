// ctrlFactory.cpp: implementation of the CCtrlFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cms.h"
#include "ctrlFactory.h"
 
#include "PropertyHelp.h" 
#include "TouchListProperty.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
/*实现控件的创建*/
#define CREATE_CTRL( CtrlName )  \
	Window* CtrlName##Factory::Create( IArgs& iArgs  ) \
{ \
	try \
{ \
	Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs); \
	DWORD dwStyle = 0; \
	if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle ) == false ) \
{ \
	dwStyle = IWindowFactory::m_dwDefaultStyle; \
} \
	CtrlName * pWnd = new CtrlName;	\
	pWnd->Create(  dwStyle, IWindowFactory::m_rcDefaultRect, args.m_pParent, GETUNIQID ); \
	return pWnd; \
} \
	catch( bad_cast ) \
{ \
	return 0; \
} \
}  

//声明属性集
 

DECLARE_PROPERTYSET_BEGIN( CIPAddressCtrl, CWndPropertySet ) 
// 如果有新增属性请到这里添加
DECLARE_PROPERTYSET_END



//声明属性集
DECLARE_PROPERTYSET_BEGIN( CTransparentBaseDlg, CWndPropertySet ) 
AddProperty( "Image", "TransparentDlgImage" );
AddProperty( "TransparentDlgImage", "TransparentDlgImage" );
AddProperty( "MoveStatus", "TransparentDlgMoveStatus" );
AddProperty( "TransparentDlgMoveStatus", "TransparentDlgMoveStatus" );
AddProperty( "AutoHideStatus","TransparentDlgAutoHideStatus" );
DECLARE_PROPERTYSET_END 

/*
DECLARE_PROPERTYSET_BEGIN( CTransparentBaseList, CTransparentBaseDlgPropertySet );
AddProperty( "ListImage", "TransparentBaseListImage" );
AddProperty( "LayoutAlgorithm", "LayoutAlgorithm" );
AddProperty( "SortAlgorithm", "SortAlgorithm" );
AddProperty( "Drag", "TransparentBaseListDrag" );
AddProperty( "ClickNoSel", "TransparentBaseListClickNoSel" );
AddProperty( "ClickFocus", "TransparentBaseListClickFocus" );
AddProperty( "TransparentBaseListSelItem", "TransparentBaseListSelItem" );
AddProperty( "TransparentBaseListOffset", "TransparentBaseListOffset" );
AddProperty( "EveryItemSizeSame", "TransparentBaseListItemSizeSame" );
DECLARE_PROPERTYSET_END
*/

DECLARE_PROPERTYSET_BEGIN( CTransparentAddrList, CTransparentListPropertySet ) 
AddProperty( "TouchListConfTemp", "TouchListData" );
AddProperty( "TouchListAddr", "TouchListData" );
AddProperty( "TouchListTempCns", "TouchListData" );
AddProperty( "TouchListTempPoll", "TouchListData" ); 
AddProperty( "TouchListMenu", "TouchListData" ); 
AddProperty( "TouchListConfInfo", "TouchListData" ); 
AddProperty( "TouchListConf", "TouchListData" );
AddProperty( "TouchListCnsList", "TouchListData" );
AddProperty( "TouchListUser", "TouchListData" );
AddProperty( "TouchListTvw", "TouchListData" );
AddProperty( "TouchListAlarm", "TouchListData" );
AddProperty( "VerListConfMenu", "TouchListData" );
AddProperty( "ListDualSrc", "TouchListData" );

// 如果有新增属性请到这里添加
DECLARE_PROPERTYSET_END

DECLARE_PROPERTYSET_BEGIN( CHoriList, CTransparentHoriListPropertySet ) 
AddProperty( "ListConnectCns", "TouchListData" );
AddProperty( "HoriListConfMenu", "TouchListData" );
AddProperty( "HoriListOffsetIndex", "HoriListOffsetIndex" );
AddProperty( "ClickNoSel", "HoriListClickNoSel" );
AddProperty( "HoriListItemCount", "HoriListItemCount" );
AddProperty( "BindWnd", "HoriListBindWnd" );
AddProperty( "HoriListOffset", "HoriListOffset" );
AddProperty( "HoriListSelItem", "HoriListSelItem" );
DECLARE_PROPERTYSET_END


//声明属性集
DECLARE_PROPERTYSET_BEGIN( CDlgOverLapped, CTransparentBaseDlgPropertySet )  
DECLARE_PROPERTYSET_END 

//声明属性集
DECLARE_PROPERTYSET_BEGIN( CDlgPopup, CTransparentBaseDlgPropertySet ) 
// 如果有新增属性请到这里添加
DECLARE_PROPERTYSET_END 

//声明属性集
DECLARE_PROPERTYSET_BEGIN( CDlgChild, CTransparentBaseDlgPropertySet ) 
// 如果有新增属性请到这里添加
DECLARE_PROPERTYSET_END


//声明属性集
DECLARE_PROPERTYSET_BEGIN( CDlgModal, CTransparentBaseDlgPropertySet ) 
// 如果有新增属性请到这里添加
DECLARE_PROPERTYSET_END

//声明属性集
DECLARE_PROPERTYSET_BEGIN( CPopupDlg, CTransparentBaseDlgPropertySet ) 
// 如果有新增属性请到这里添加
DECLARE_PROPERTYSET_END

void  RegCtrls()
{
	//注册控件
    REG_WINDOW_FACTORY( CListCtrl);
   // REG_WINDOW_FACTORY( CAddrList );
    REG_WINDOW_FACTORY( CTransparentAddrList );    
    REG_WINDOW_FACTORY( CHoriList );  

    REG_WINDOW_FACTORY( CDlgModal);
    REG_WINDOW_FACTORY( CDlgChild );
    REG_WINDOW_FACTORY( CDlgPopup);
    REG_WINDOW_FACTORY( CDlgOverLapped );
    REG_WINDOW_FACTORY( CPopupDlg);

    REG_PROPERTY( TouchListData );

    //注册属性集
	//REG_PROPERTY_SET( CTransparentBaseList );
	REG_PROPERTY_SET( CTransparentAddrList );
	REG_PROPERTY_SET( CHoriList );
	
	REG_PROPERTY_SET( CDlgModal);
	REG_PROPERTY_SET( CDlgChild );
	REG_PROPERTY_SET( CDlgPopup );
	REG_PROPERTY_SET( CDlgOverLapped );
	REG_PROPERTY_SET( CPopupDlg );
   
}




//实现部分
CREATE_CTRL( CListCtrl ) 
//CREATE_CTRL(CIPAddressCtrl)




#include "AddrList.h"
Window* CTransparentAddrListFactory::Create( IArgs& iArgs )
{
	try
	{
		Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);
		DWORD dwStyle = 0;
		if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle ) == false )
		{
			dwStyle = IWindowFactory::m_dwDefaultStyle;
		}
// #ifdef _DEBUG
// 		dwStyle = dwStyle | m_dwDebugStyle; 
// #endif
		CTransparentAddrList* pWnd = new CTransparentAddrList( args.m_strName.c_str(), "", IWindowFactory::m_rcDefaultRect, 
			args.m_pParent, GETUNIQID, dwStyle, 0 );

		return pWnd;
	}
	catch (bad_cast)
	{
		return 0;
	}
}

#include "horilist.h"
Window* CHoriListFactory::Create( IArgs& iArgs )
{
	try
	{
		Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);
		DWORD dwStyle = 0;
		if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle ) == false )
		{
			dwStyle = IWindowFactory::m_dwDefaultStyle;
		}
// #ifdef _DEBUG
// 		dwStyle = dwStyle | m_dwDebugStyle; 
// #endif
		CHoriList* pWnd = new CHoriList( args.m_strName.c_str(), IWindowFactory::m_rcDefaultRect, args.m_pParent, GETUNIQID, dwStyle );
		//pWnd->Create( CDlgChild::IDD, args.m_pParent );
		
		return pWnd;
	}
	catch (bad_cast)
	{
		return 0;
	}
}

 
#include "dlgoverlapped.h"
Window* CDlgOverLappedFactory::Create( IArgs& iArgs )
{
    try
    {
        Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);
        
        CDlgOverLapped* pWnd = new CDlgOverLapped();
        pWnd->Create( CDlgOverLapped::IDD, args.m_pParent );

        DWORD dwStyle = pWnd->GetStyle();
        DWORD dwStyleEx = pWnd->GetExStyle();

        if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle,dwStyleEx ) == false )
        {
            dwStyle = IWindowFactory::m_dwDefaultStyle;
        }
#ifdef _DEBUG
        dwStyle = dwStyle | m_dwDebugStyle; 
#endif
        pWnd->ModifyStyleEx( 0, dwStyleEx );
        pWnd->ModifyStyle( 0, dwStyle );


#ifdef _DEBUG
        if ( pWnd != NULL )
        {
            pWnd->SetMoveStatus(TRUE);
        } 
#endif 
		TRACE( "\n[CDlgOverLappedFactory::Create] %p = %s \n", pWnd, args.m_strName.c_str() );
        return pWnd;
    }
    catch (bad_cast)
    {
        return 0;
    }
}


#include "dlgpopup.h"
Window* CDlgPopupFactory::Create( IArgs& iArgs )
{
    try
    {
        Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);
       
        CDlgPopup* pWnd = new CDlgPopup();
        pWnd->Create( CDlgPopup::IDD,  args.m_pParent  );

        DWORD dwStyle = 0;
        DWORD dwExStyle = 0;    
        if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle ) == false )
        {
            dwStyle = IWindowFactory::m_dwDefaultStyle;
        }
		dwStyle = dwStyle | pWnd->GetStyle();
		if ( CWindowDefaultStyleMap::StringToStyle( args.m_strExStyle, dwExStyle ) == false )
		{
			dwExStyle = 0;
		}
		dwExStyle = dwExStyle | pWnd->GetExStyle();
		
// #ifdef _DEBUG
//         dwStyle = dwStyle | m_dwDebugStyle; 
// #endif
        pWnd->ModifyStyleEx( 0, dwExStyle );
        pWnd->ModifyStyle( 0, dwStyle );

#ifdef _DEBUG
        if ( pWnd != NULL )
        {
            pWnd->SetMoveStatus(TRUE);
        } 

        TRACE( "\n[CDlgPopupFactory::Create] ( wnd %p, handle %p ) = %s \n", pWnd,pWnd->GetSafeHwnd(), args.m_strName.c_str() );
#endif 
        
        return pWnd;
    }
    catch (bad_cast)
    {
        return 0;
    }
}


#include "dlgchild.h"
Window* CDlgChildFactory::Create( IArgs& iArgs )
{
    try
    {
        Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);
     
        CDlgChild* pWnd = new CDlgChild(); 
        pWnd->Create( CDlgChild::IDD, args.m_pParent  ); 
   

        DWORD dwStyle = pWnd->GetStyle();
        DWORD dwStyleEx = pWnd->GetExStyle();
        
        if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle,dwStyleEx ) == false )
        {
            dwStyle = IWindowFactory::m_dwDefaultStyle;
        }
// #ifdef _DEBUG
//         dwStyle = dwStyle | m_dwDebugStyle; 
// #endif
        pWnd->ModifyStyleEx( 0, dwStyleEx );
        pWnd->ModifyStyle( 0, dwStyle );

#ifdef _DEBUG
//         if ( pWnd != NULL )
//         {
//             pWnd->SetMoveStatus(TRUE);
//         } 
        TRACE( "\n[CDlgChildFactory::Create] ( wnd %p, handle %p ) = %s \n", pWnd, pWnd->GetSafeHwnd(), args.m_strName.c_str() );
#endif 
        
        return pWnd;
    }
    catch (bad_cast)
    {
        return 0;
    }
}


#include "dlgModal.h"
Window* CDlgModalFactory::Create( IArgs& iArgs )
{
    try
    {
        Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);
        
        CDlgModal* pWnd = new CDlgModal(); 
        pWnd->Create( CDlgModal::IDD, args.m_pParent  ); 
        
        DWORD dwStyle = 0;
        DWORD dwExStyle = 0;    
        if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle ) == false )
        {
            dwStyle = IWindowFactory::m_dwDefaultStyle;
        }
		dwStyle = dwStyle | pWnd->GetStyle();
		if ( CWindowDefaultStyleMap::StringToStyle( args.m_strExStyle, dwExStyle ) == false )
		{
			dwExStyle = 0;
		}
		dwExStyle = dwExStyle | pWnd->GetExStyle();

#ifdef _DEBUG
        dwStyle = dwStyle | m_dwDebugStyle; 
#endif
        pWnd->ModifyStyleEx( 0, dwExStyle );
        pWnd->ModifyStyle( 0, dwStyle );
            
        
#ifdef _DEBUG
        if ( pWnd != NULL )
        {
            pWnd->SetMoveStatus(TRUE);
        } 
        TRACE( "\n[CDlgModalFactory::Create] ( wnd %p, handle %p ) = %s \n", pWnd, pWnd->GetSafeHwnd(), args.m_strName.c_str() );
#endif 
        
        return pWnd;
    }
    catch (bad_cast)
    {
        return 0;
    }
}


#include "popupdlg.h"
Window* CPopupDlgFactory::Create( IArgs& iArgs )
{
    try
    {
        Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);
		
        CPopupDlg* pWnd = new CPopupDlg();
        pWnd->Create( CPopupDlg::IDD,  args.m_pParent  );
		
        DWORD dwStyle = 0;
        DWORD dwExStyle = 0;    
        if ( CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle ) == false )
        {
            dwStyle = IWindowFactory::m_dwDefaultStyle;
        }
		dwStyle = dwStyle | pWnd->GetStyle();
		if ( CWindowDefaultStyleMap::StringToStyle( args.m_strExStyle, dwExStyle ) == false )
		{
			dwExStyle = 0;
		}
		dwExStyle = dwExStyle | pWnd->GetExStyle();
		
		// #ifdef _DEBUG
		//         dwStyle = dwStyle | m_dwDebugStyle; 
		// #endif
        pWnd->ModifyStyleEx( 0, dwExStyle );
        pWnd->ModifyStyle( 0, dwStyle );
		
#ifdef _DEBUG
	
        TRACE( "\n[CPopupDlgFactory::Create] ( wnd %p, handle %p ) = %s \n", pWnd,pWnd->GetSafeHwnd(), args.m_strName.c_str() );
#endif 
        
        return pWnd;
    }
    catch (bad_cast)
    {
        return 0;
    }
}
