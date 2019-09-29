// TouchListProperty.cpp: implementation of the CTouchListProperty class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TouchListProperty.h"
#include "TouchListHelp.h"
#include "AddrList.h"
#include "horilist.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
typedef IItem< IBaseItem, int > IItemList;
 
bool Property_TouchListData::set(Window* tag, const String& value)
{   	
	return false;
}

bool Property_TouchListData::set( Window* tag, const IValue& value )
{
 	try   
	{
 
		if ( CTransparentList* pTouchList = dynamic_cast<CTransparentList*>(const_cast<Window*>(tag)) )
        {  
            pTouchList->Clear();
			bool bRet = CTouchListHelp::SetData( pTouchList->GetRoot(), &value );
			if ( bRet == true )
			{ 
				pTouchList->LayoutItem();				
			}
			pTouchList->ResetSelItem(); 
			pTouchList->SendMessage( WM_REDRAW_UI, 0, (LPARAM)0 );
		}
		else if ( CTransparentHoriList* pList = dynamic_cast<CTransparentHoriList*>( const_cast<Window*>(tag) ) )
		{
            pList->Clear();
			bool bRet = CTouchListHelp::SetData( pList->GetRoot(), &value );
			if ( bRet == true )
			{ 
				pList->LayoutItem();				
			}
			pList->ResetSelItem(); 
			pList->SendMessage( WM_REDRAW_UI, 0, (LPARAM)0 );
		}
		
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TouchListData::set 传入的参数不正确" );
		return false;
	}
 }
 