

#include "stdafx.h"
#include "horilist.h"


CHoriList::CHoriList( CString strName, CRect rcWnd, CWnd* pWnd, UINT nID, 
					 DWORD dwStyle, DWORD dwExStyle ) :
CTransparentHoriList( strName, rcWnd, pWnd, nID, dwStyle, dwExStyle )
{
	
}

CHoriList::~CHoriList()
{
	
}

void CHoriList::Clicked( UINT nFlags, CPoint point )
{
	if ( m_pSelItem == 0 )
	{
		return;
	}
	IBaseItem* pBaseItem = m_pSelItem->GetItemData();
	if ( pBaseItem == 0 )
	{
		return;
	}
	
	bool bFind = false;
	String strFunc = pBaseItem->GetFunc();
	IItemList* pList = m_pSelItem;
	while( pList != 0 && pList->GetParentItem() != 0 )
	{		
		pBaseItem = pList->GetItemData();
		strFunc = pBaseItem->GetFunc();
		if ( strFunc != IBaseItem::strDefaultFunc )
		{
			bFind = true;
			break;
		}
		pList = pList->GetParentItem();
	}
	if ( bFind == true )
	{
		CRect rcFrame = GetFrameInScreen( pList );
		Args_ClickItemInfo clickInfo( this, pList, rcFrame );
		
		CFuncManage::GetSingletonPtr()->ExeFunc( strFunc, clickInfo );
	}	
	else
	{
		LOGEVENT( "条目点击，但是没有找到任何注册的事件" );
	}
}