// valueSet.cpp: implementation of the CValueSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cms.h"
#include "valueSet.h"
#include "IPropertyAssist.h"
#include "PropertyHelp.h"
#include "transparentbasedlg.h"
#include "AddrList.h"
#include "horilist.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
using namespace AutoUIFactory;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
void RegWindowProperty()
{

	//注册属性
	REG_PROPERTY( TransparentDlgImage ); 
	REG_PROPERTY( TransparentDlgAutoHideStatus );
	REG_PROPERTY( TransparentDlgMoveStatus ); 

	/*
	REG_PROPERTY( TransparentBaseListImage );
	REG_PROPERTY( TransparentBaseListDrag );
	REG_PROPERTY( TransparentBaseListClickNoSel );
    REG_PROPERTY( TransparentBaseListSelItem );
    REG_PROPERTY( TransparentBaseListOffset );
	REG_PROPERTY( TransparentBaseListClickFocus );
	REG_PROPERTY( TransparentBaseListItemSizeSame );
	*/

	REG_PROPERTY( HoriListOffsetIndex );
	REG_PROPERTY( HoriListClickNoSel );
	REG_PROPERTY( HoriListItemCount );
	REG_PROPERTY( HoriListBindWnd );
	REG_PROPERTY( HoriListOffset );
	REG_PROPERTY( HoriListSelItem );
	
}

 

 
 
 // transparentDlg MoveStatus begin
 bool Property_TransparentDlgMoveStatus::get( const Window* src, IValue& value ) const
 {	
     return false;
 }
 
 bool Property_TransparentDlgMoveStatus::get( const Window* src, String& value ) const
 {
     return false;
 }
 bool Property_TransparentDlgMoveStatus::set(Window* tag, const String& value)
 {   
     if ( CTransparentBaseDlg* pWnd = dynamic_cast<CTransparentBaseDlg*>(const_cast<Window*>(tag)) )
     {
         pWnd->SetMoveStatus( CPropertyHelp::stringToBool( value ) );
         return true;
     }
     return false;
 }
 
bool Property_TransparentDlgMoveStatus::set( Window* tag, const IValue& value )
{
    try 
    {
        const Value_TransparentDlgMoveStatus& pValue = dynamic_cast<const Value_TransparentDlgMoveStatus&>(value);

        if ( CTransparentBaseDlg* pWnd = dynamic_cast<CTransparentBaseDlg*>(const_cast<Window*>(tag)) )
        {
            pWnd->SetMoveStatus( pValue.bMove );
            return true;
        }
        return false;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentDlgMoveStatus::set 传入的参数不正确" );
        return false;
    }
}
 
 
 
 
 bool Property_TransparentDlgAutoHideStatus::get( const Window* src, IValue& value ) const
 {	
     return false;
 }
 
 bool Property_TransparentDlgAutoHideStatus::get( const Window* src, String& value ) const
 {
     return false;
 }
 bool Property_TransparentDlgAutoHideStatus::set(Window* tag, const String& value)
 {   
     try 
     {
         bool bAutoHide = CPropertyHelp::stringToBool( value );
         if ( CTransparentBaseDlg* pWnd = (dynamic_cast<CTransparentBaseDlg*>(const_cast<Window*>(tag))) )
         {
             pWnd->SetAutoHideStatus( bAutoHide );
         }
         return true;
     }
     catch( bad_cast )
     {
         LOGEVENT( "Property_TransparentDlgAutoHideStatus::set 传入的参数不正确" );
         return false;
     }	
 }
 
 bool Property_TransparentDlgAutoHideStatus::set( Window* tag, const IValue& value )
 {
     try 
     {
         const Value_TransparentDlgAutoHideStatus& pValue = dynamic_cast<const Value_TransparentDlgAutoHideStatus&>(value);		
         if ( CTransparentBaseDlg* pWnd = (dynamic_cast<CTransparentBaseDlg*>(const_cast<Window*>(tag))) )
         {
             pWnd->SetAutoHideStatus( pValue.bHide );
             return true;
         }
         return false;
     }
     catch( bad_cast )
     {
         LOGEVENT( "Property_TransparentDlgAutoHideStatus::set 传入的参数不正确" );
         return false;
     }
}




 // transparent wnd image begin
 bool Property_TransparentDlgImage::get( const Window* src, IValue& value ) const
 {	
     return false;
 }
 
 bool Property_TransparentDlgImage::get( const Window* src, String& value ) const
 {
     return false;
 }
 bool Property_TransparentDlgImage::set(Window* tag, const String& value)
 {   
     try 
     {
         String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
         String strFile = strImageFolder + "//" + value;
         CString str;
         tag->GetWindowText( str );
         if ( CTransparentBaseDlg* pWnd = (dynamic_cast<CTransparentBaseDlg*>(const_cast<Window*>(tag))) )
         {
             pWnd->SetImage( strFile.c_str() );
         }
         return true;
     }
     catch( bad_cast )
     {
         LOGEVENT( "Property_TransparentDlgImage::set 传入的参数不正确" );
         return false;
     }	
 }
 
 bool Property_TransparentDlgImage::set( Window* tag, const IValue& value )
 {
     try 
     {
         const Value_TransparentDlgImage& pValue = dynamic_cast<const Value_TransparentDlgImage&>(value);
         String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
         String strFile = strImageFolder + "//" + pValue.strImage;
         
         if ( CTransparentBaseDlg* pWnd = (dynamic_cast<CTransparentBaseDlg*>(const_cast<Window*>(tag))) )
         {
             pWnd->SetImage( strFile.c_str() );
             return true;
         }
         return false;
     }
     catch( bad_cast )
     {
         LOGEVENT( "Property_TransparentDlgImage::set 传入的参数不正确" );
         return false;
     }
}
/*
// transparentbaselist image begin
bool Property_TransparentBaseListImage::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentBaseListImage::get( const Window* src, String& value ) const
{
	return false;
}

bool Property_TransparentBaseListImage::set(Window* tag, const String& value)
{   
	try 
	{
		String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
		String strFile = strImageFolder + "//" + value;
		CString str;
		tag->GetWindowText( str );
		if ( CTransparentBaseList* pWnd = (dynamic_cast<CTransparentBaseList*>(const_cast<Window*>(tag))) )
		{
			pWnd->SetImage( strFile.c_str() );
		}
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentBaseListImage::set 传入的参数不正确" );
		return false;
	}	
}
 
bool Property_TransparentBaseListImage::set( Window* tag, const IValue& value )
{
	 try 
	 {
		 const Value_TransparentBaseListImage& pValue = dynamic_cast<const Value_TransparentBaseListImage&>(value);
		 String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
		 String strFile = strImageFolder + "//" + pValue.strImage;
		 
		 if ( CTransparentBaseList* pWnd = (dynamic_cast<CTransparentBaseList*>(const_cast<Window*>(tag))) )
		 {
			 pWnd->SetImage( strFile.c_str() );
			 return true;
		 }
		 return false;
	 }
	 catch( bad_cast )
	 {
		 LOGEVENT( "Property_TransparentBaseListImage::set 传入的参数不正确" );
		 return false;
	 }
}


//TransparentBaseList Drag begin
bool Property_TransparentBaseListDrag::get( const Window* src, IValue& value ) const
{	
    try 
    { 
        Value_TransparentBaseListDrag& pValue = dynamic_cast<Value_TransparentBaseListDrag&>(value);
        pValue.bCanDrag = (dynamic_cast<CTransparentBaseList*>(const_cast<Window*>(src)))->GetDragEnable( );
        
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentBaseListDrag::get 传入的参数不正确" );
        return false;
    }	
    return false;
}

bool Property_TransparentBaseListDrag::get( const Window* src, String& value ) const
{
    try 
    { 
        bool bCanDrag = (dynamic_cast<CTransparentBaseList*>(const_cast<Window*>(src)))->GetDragEnable( );
        value = CPropertyHelp::boolToString(bCanDrag);
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentBaseListDrag::get 传入的参数不正确" );
        return false;
    }	
    return false;
}

bool Property_TransparentBaseListDrag::set(Window* tag, const String& value)
{   
    try 
    {  
        bool bCanDrag = CPropertyHelp::stringToBool(value);
        (dynamic_cast<CTransparentBaseList*>(const_cast<Window*>(tag)))->SetDragEnable( bCanDrag );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentBaseListDrag::set 传入的参数不正确" );
        return false;
    }	
}

bool Property_TransparentBaseListDrag::set( Window* tag, const IValue& value )
{
    try 
    {
        const Value_TransparentBaseListDrag& pValue = dynamic_cast<const Value_TransparentBaseListDrag&>(value);
        (dynamic_cast<CTransparentBaseList*>(const_cast<Window*>(tag)))->SetDragEnable( pValue.bCanDrag );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentBaseListDrag::set 传入的参数不正确" );
        return false;
    }	
} 
//TransparentList Drag end


//TransparentList ClickNoSel begin
bool Property_TransparentBaseListClickNoSel::get( const Window* src, IValue& value ) const
{	
    try 
    { 
        Value_TransparentBaseListClickNoSel& pValue = dynamic_cast<Value_TransparentBaseListClickNoSel&>(value);
        pValue.bNoSel = (dynamic_cast<CTransparentBaseList*>(const_cast<Window*>(src)))->IsClickNoSel();
        
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentBaseListClickNoSel::get 传入的参数不正确" );
        return false;
    }	
    return false;
}

bool Property_TransparentBaseListClickNoSel::get( const Window* src, String& value ) const
{
    try 
    { 
        bool bNoSel = (dynamic_cast<CTransparentBaseList*>(const_cast<Window*>(src)))->IsClickNoSel( );
        value = CPropertyHelp::boolToString(bNoSel);
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentBaseListClickNoSel::get 传入的参数不正确" );
        return false;
    }	
    return false;
}

bool Property_TransparentBaseListClickNoSel::set(Window* tag, const String& value)
{   
    try 
    {  
        bool bNoSel = CPropertyHelp::stringToBool(value);
        (dynamic_cast<CTransparentBaseList*>(const_cast<Window*>(tag)))->SetClickNoSel( bNoSel );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentBaseListClickNoSel::set 传入的参数不正确" );
        return false;
    }	
}

bool Property_TransparentBaseListClickNoSel::set( Window* tag, const IValue& value )
{
    try 
    {
        const Value_TransparentBaseListClickNoSel& pValue = dynamic_cast<const Value_TransparentBaseListClickNoSel&>(value);
        (dynamic_cast<CTransparentBaseList*>(const_cast<Window*>(tag)))->SetClickNoSel( pValue.bNoSel );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentBaseListClickNoSel::set 传入的参数不正确" );
        return false;
    }	
} 
//TransparentList ClickNoSel end

//TransparentList ClickFocus begin
bool Property_TransparentBaseListClickFocus::get( const Window* src, IValue& value ) const
{		
    return false;
}

bool Property_TransparentBaseListClickFocus::get( const Window* src, String& value ) const
{
    return false;
}

bool Property_TransparentBaseListClickFocus::set(Window* tag, const String& value)
{   
    try 
    {  
        bool bFocus = CPropertyHelp::stringToBool(value);
        (dynamic_cast<CTransparentBaseList*>(const_cast<Window*>(tag)))->SetClickFocus( bFocus );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentBaseListClickFocus::set 传入的参数不正确" );
        return false;
    }	
}

bool Property_TransparentBaseListClickFocus::set( Window* tag, const IValue& value )
{
    try 
    {
        const Value_TransparentBaseListClickFocus& pValue = dynamic_cast<const Value_TransparentBaseListClickFocus&>(value);
        (dynamic_cast<CTransparentBaseList*>(const_cast<Window*>(tag)))->SetClickFocus( pValue.bFocus );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentBaseListClickFocus::set 传入的参数不正确" );
        return false;
    }	
} 
//TransparentBaseList ClickFocus end

//tranparentlist select item set/get begin 
bool Property_TransparentBaseListSelItem::set(Window* tag, const String& value)
{
	try 
    {  
        int nSel = CPropertyHelp::stringToInt(value);
        (dynamic_cast<CTransparentBaseList*>(const_cast<Window*>(tag)))->SetSelItem( nSel );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentBaseListSelItem::set 传入的参数不正确" );
        return false;
    }
    return false;	
}

bool Property_TransparentBaseListSelItem::get( const Window* src, String& value ) const
{
    return false;
}

bool Property_TransparentBaseListSelItem::set( Window* tag, const IValue& value )
{
    try 
    {
        const Value_TransparentBaseListSelItem& pValue = dynamic_cast<const Value_TransparentBaseListSelItem&>(value);
        (dynamic_cast<CTransparentBaseList*>(const_cast<Window*>(tag)))->SetSelItem( pValue.dwDataKey );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Value_TransparentBaseListSelItem::set 传入的参数不正确" );
        return false;
    }	
} 

bool Property_TransparentBaseListSelItem::get( const Window* src, IValue& value ) const
{	
    try 
    { 
        Value_TransparentBaseListSelItem& pValue = dynamic_cast<Value_TransparentBaseListSelItem&>(value);
        pValue.pSelItem = (dynamic_cast<CTransparentBaseList*>(const_cast<Window*>(src)))->GetSelItem();
        
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Value_TransparentBaseListSelItem::get 传入的参数不正确" );
        return false;
    }	
    return false;
}
//tranparentlist select item set/get end

//tranparentlist Item same size set/get begin 
bool Property_TransparentBaseListItemSizeSame::set(Window* tag, const String& value)
{
	try 
    {  
        bool bSameSize = CPropertyHelp::stringToBool(value);
        (dynamic_cast<CTransparentBaseList*>(const_cast<Window*>(tag)))->SetItemSizeSame( bSameSize );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentBaseListItemSizeSame::set 传入的参数不正确" );
        return false;
    }
    return false;	
} 


bool Property_TransparentBaseListItemSizeSame::get( const Window* src, String& value ) const
{
    return false;
}

bool Property_TransparentBaseListItemSizeSame::set( Window* tag, const IValue& value )
{ 
    return false; 
} 

bool Property_TransparentBaseListItemSizeSame::get( const Window* src, IValue& value ) const
{	
    
    return false;
}
//tranparentlist Item same size set/get end

//tranparentlist offset set/get begin 
bool Property_TransparentBaseListOffset::set(Window* tag, const String& value)
{
	try 
    {  
        int nOffset = CPropertyHelp::stringToInt(value);
        (dynamic_cast<CTransparentBaseList*>(const_cast<Window*>(tag)))->SetYOffset( nOffset );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentBaseListOffset::set 传入的参数不正确" );
        return false;
    }
    return false;	
}

bool Property_TransparentBaseListOffset::get( const Window* src, String& value ) const
{
    return false;
}

bool Property_TransparentBaseListOffset::set( Window* tag, const IValue& value )
{
    try 
    {
        const Value_TransparentBaseListOffset& pValue = dynamic_cast<const Value_TransparentBaseListOffset&>(value);
        (dynamic_cast<CTransparentBaseList*>(const_cast<Window*>(tag)))->SetYOffset( pValue.nOffset );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Value_TransparentBaseListOffset::set 传入的参数不正确" );
        return false;
    }	
} 

bool Property_TransparentBaseListOffset::get( const Window* src, IValue& value ) const
{
    try 
    { 
        Value_TransparentBaseListOffset& pValue = dynamic_cast<Value_TransparentBaseListOffset&>(value);
		if ( CTransparentBaseList* pWnd = (dynamic_cast<CTransparentBaseList*>(const_cast<Window*>(src))) )
		{
			pValue.nOffset = pWnd->GetYOffset();
		}        
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentBaseListOffset::get 传入的参数不正确" );
        return false;
    }
    return false;
}
//tranparentlist offset set/get end 
*/

//tranparenthorilist offsetindex set/get begin 
bool Property_HoriListOffsetIndex::set(Window* tag, const String& value)
{
	try 
    {  
        int nIndex = CPropertyHelp::stringToInt(value);
        (dynamic_cast<CTransparentHoriList*>(const_cast<Window*>(tag)))->SetOffsetIndex( nIndex );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_HoriListOffsetIndex::set 传入的参数不正确" );
        return false;
    }
    return false;	
}

bool Property_HoriListOffsetIndex::get( const Window* src, String& value ) const
{
    return false;
}

bool Property_HoriListOffsetIndex::set( Window* tag, const IValue& value )
{
    try 
    {
        const Value_HoriListOffsetIndex& pValue = dynamic_cast<const Value_HoriListOffsetIndex&>(value);
		if ( CTransparentHoriList* pWnd = (dynamic_cast<CTransparentHoriList*>(const_cast<Window*>(tag))) )
		{
			pWnd->SetOffsetIndex( pValue.nIndex );
		}
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_HoriListOffsetIndex::set 传入的参数不正确" );
        return false;
    }	
} 

bool Property_HoriListOffsetIndex::get( const Window* src, IValue& value ) const
{	
    try 
    { 
        Value_HoriListOffsetIndex& pValue = dynamic_cast<Value_HoriListOffsetIndex&>(value);
		if ( CTransparentHoriList* pWnd = (dynamic_cast<CTransparentHoriList*>(const_cast<Window*>(src))) )
		{
			pValue.nIndex = pWnd->GetOffsetIndex();
		}        
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_HoriListOffsetIndex::get 传入的参数不正确" );
        return false;
    }	
    return false;
}
//tranparenthorilist offsetindex set/get end


//TransparentHoriList ClickNoSel begin
bool Property_HoriListClickNoSel::get( const Window* src, IValue& value ) const
{	
    try 
    { 
        Value_HoriListClickNoSel& pValue = dynamic_cast<Value_HoriListClickNoSel&>(value);
        pValue.bNoSel = (dynamic_cast<CTransparentHoriList*>(const_cast<Window*>(src)))->IsClickNoSel();
        
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_HoriListClickNoSel::get 传入的参数不正确" );
        return false;
    }	
    return false;
}

bool Property_HoriListClickNoSel::get( const Window* src, String& value ) const
{
    try 
    { 
        bool bNoSel = (dynamic_cast<CTransparentHoriList*>(const_cast<Window*>(src)))->IsClickNoSel( );
        value = CPropertyHelp::boolToString(bNoSel);
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_HoriListClickNoSel::get 传入的参数不正确" );
        return false;
    }	
    return false;
}

bool Property_HoriListClickNoSel::set(Window* tag, const String& value)
{   
    try 
    {  
        bool bNoSel = CPropertyHelp::stringToBool(value);
		if ( CTransparentHoriList* pWnd = (dynamic_cast<CTransparentHoriList*>(const_cast<Window*>(tag))) )
		{
			pWnd->SetClickNoSel( bNoSel );
		}
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_HoriListClickNoSel::set 传入的参数不正确" );
        return false;
    }	
}

bool Property_HoriListClickNoSel::set( Window* tag, const IValue& value )
{
    try 
    {
        const Value_HoriListClickNoSel& pValue = dynamic_cast<const Value_HoriListClickNoSel&>(value);
        (dynamic_cast<CTransparentHoriList*>(const_cast<Window*>(tag)))->SetClickNoSel( pValue.bNoSel );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_HoriListClickNoSel::set 传入的参数不正确" );
        return false;
    }	
} 
//TransparentHoriList ClickNoSel end


//tranparenthorilist ItemCount set/get begin 
bool Property_HoriListItemCount::set(Window* tag, const String& value)
{
    return false;	
}

bool Property_HoriListItemCount::get( const Window* src, String& value ) const
{
    return false;
}

bool Property_HoriListItemCount::set( Window* tag, const IValue& value )
{
	return false;	
} 

bool Property_HoriListItemCount::get( const Window* src, IValue& value ) const
{	
    try 
    { 
        Value_HoriListItemCount& pValue = dynamic_cast<Value_HoriListItemCount&>(value);
		if ( CTransparentHoriList* pWnd = (dynamic_cast<CTransparentHoriList*>(const_cast<Window*>(src))) )
		{
			pValue.nCount = pWnd->GetItemCount();
		}        
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_HoriListItemCount::get 传入的参数不正确" );
        return false;
    }	
    return false;
}
//tranparenthorilist ItemCount set/get end


// transparent switchbtn BindWnd begin
bool Property_HoriListBindWnd::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_HoriListBindWnd::get( const Window* src, String& value ) const
{
	return false;
}

bool Property_HoriListBindWnd::set(Window* tag, const String& value)
{   	
	IWndTree* pTree = const_cast<IWndTree* >( CWindowManage::GetSingletonPtr()->GetWindowTree( value ) );
	if ( pTree == NULL )
	{
		return false;
	}
	if ( CTransparentBaseDlg* pWnd = dynamic_cast<CTransparentBaseDlg*>(pTree->GetItemData()->pWnd) )
	{	
		if ( CTransparentHoriList* pList = dynamic_cast<CTransparentHoriList*>(const_cast<Window*>(tag)) )
		{
			pWnd->SetBindWnd( pList->GetSafeHwnd() );
			return true;
		}
	}
	return false;	
}

bool Property_HoriListBindWnd::set( Window* tag, const IValue& value )											  
{
	try
	{
		const Value_BindList& pValue = dynamic_cast<const Value_BindList&>(value);
		IWndTree* pTree = const_cast<IWndTree* >( CWindowManage::GetSingletonPtr()->GetWindowTree( pValue.strListName ) );
		if ( pTree == NULL )
		{
			return false;
		}
		if ( CTransparentBaseDlg* pWnd = dynamic_cast<CTransparentBaseDlg*>(pTree->GetItemData()->pWnd) )
		{	
			if ( CTransparentHoriList* pList = dynamic_cast<CTransparentHoriList*>(const_cast<Window*>(tag)) )
			{
				pWnd->SetBindWnd( pList->GetSafeHwnd() );
				return true;
			}
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_HoriListBindWnd::set 传入的参数不正确" );
		return false;
	}
}
// transparent HoriList BindWnd end


//tranparenthorilist offset set/get begin 
bool Property_HoriListOffset::set(Window* tag, const String& value)
{
	try 
    {  
        int nOffset = CPropertyHelp::stringToInt(value);
        (dynamic_cast<CTransparentHoriList*>(const_cast<Window*>(tag)))->SetTotalOffset( nOffset );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_HoriListOffset::set 传入的参数不正确" );
        return false;
    }
    return false;	
}

bool Property_HoriListOffset::get( const Window* src, String& value ) const
{
    return false;
}

bool Property_HoriListOffset::set( Window* tag, const IValue& value )
{
    try 
    {
        const Value_HoriListOffset& pValue = dynamic_cast<const Value_HoriListOffset&>(value);
        (dynamic_cast<CTransparentHoriList*>(const_cast<Window*>(tag)))->SetTotalOffset( pValue.nOffset );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_HoriListOffset::set 传入的参数不正确" );
        return false;
    }	
} 

bool Property_HoriListOffset::get( const Window* src, IValue& value ) const
{	    
    return false;
}
//tranparenthorilist offset set/get end 

//tranparenthorilist select item set/get begin 
bool Property_HoriListSelItem::set(Window* tag, const String& value)
{
	try 
    {  
        int nSel = CPropertyHelp::stringToInt(value);
        (dynamic_cast<CTransparentHoriList*>(const_cast<Window*>(tag)))->SetSelItem( nSel );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_HoriListSelItem::set 传入的参数不正确" );
        return false;
    }
    return false;	
}

bool Property_HoriListSelItem::get( const Window* src, String& value ) const
{
    return false;
}

bool Property_HoriListSelItem::set( Window* tag, const IValue& value )
{
    try 
    {
        const Value_HoriListSelItem& pValue = dynamic_cast<const Value_HoriListSelItem&>(value);
        (dynamic_cast<CTransparentHoriList*>(const_cast<Window*>(tag)))->SetSelItem( pValue.dwDataKey );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_HoriListSelItem::set 传入的参数不正确" );
        return false;
    }	
} 

bool Property_HoriListSelItem::get( const Window* src, IValue& value ) const
{	
    try 
    { 
        Value_HoriListSelItem& pValue = dynamic_cast<Value_HoriListSelItem&>(value);
        pValue.pSelItem = (dynamic_cast<CTransparentHoriList*>(const_cast<Window*>(src)))->GetSelItem();
        
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_HoriListSelItem::get 传入的参数不正确" );
        return false;
    }	
    return false;
}
//tranparenthorilist select item set/get end
