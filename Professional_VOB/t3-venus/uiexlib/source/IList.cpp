// IList.cpp: implementation of the IList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h" 
#include "list.h"
#include "item.h"
#include "algorithm.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IList::IList( int nWidht, int nHeight, String emLayout /* = IAlgorithm::strVert */, String emSort /* = IAlgorithm::strCharacter */, bool bShowSubItemAlways /* = TRUE */ ) 
: m_nIndex( 0 ), m_bShowSubItemAlways( bShowSubItemAlways ), m_nShowItemIndex(0), m_nShowItemNum(0),m_bItemSizeSame(true)
{
	m_pItemList = new CItemGroup<IBaseItem,int>();
	CImageItem cItem(0, nWidht, nHeight, IBaseItem::strDefaultFunc , emLayout, IAlgorithm::strCharacter, true,true );
	cItem.SetItemStatus( emItemStatusSel );
	m_pItemList->SetItemData( &cItem  );

}

IList::~IList()
{
	if ( NULL != m_pItemList )
	{
		delete m_pItemList;
		m_pItemList = NULL;
	}
}

bool IList::IsClick( IItemList* pList, CPoint point, IItem< IBaseItem, int >** item ,BOOL  bSetSel/* = FALSE */)
{
	int nItemCount = pList->GetItemCount();
	IBaseItem* pBaseItem = pList->GetItemData();
	bool bResult = false;
	if ( pBaseItem != 0 )
	{
		if ( pBaseItem->IsClick( point ) )
		{
            if ( bSetSel)
            {
                pBaseItem->SetItemStatus( emItemStatusSel );
            }
			*item = pList;
			bResult = true;			
		}
		else
		{
			return false;
		}
	}		
	else
	{
		return false;
	}

	// ������Ŀѡ�е�ʱ��Ž�������Ļ���
	bool bItemSel = true;
	if ( pBaseItem->GetItemStatus() != emItemStatusSel )
	{	
		bItemSel = false;
		if ( m_bShowSubItemAlways == false )
		{
			return false;
		}
	}

	CPoint pt = point;
	CRect rcSrc(0,0,0,0);
	if ( pList->GetParentItem() != 0 )
	{
		IItemList* pParentList = pList->GetParentItem();
		IBaseItem* pParentItem = pParentList->GetItemData();
		if ( pParentItem != 0 )
		{
			rcSrc = pParentItem->GetItemRect();			
		}
	}
				
	CRect rcDes = pBaseItem->GetItemRect();		
	pt = TransPoint( rcSrc.TopLeft(), rcDes.TopLeft(), point );
	pt -= pBaseItem->GetOffset();	

	if ( pBaseItem->GetLayoutAlgorithm() == IAlgorithm::strVert && m_bItemSizeSame )
	{
		int nShowItemHead = m_nShowItemIndex;
		int nShowItemNum = m_nShowItemNum;

        int nShowNum = 0;
        //2012-7-9 �Ż��б� ֻ������ǰ��ʾ��item ��by yjj	
        for ( int nIndex = nShowItemHead; nIndex < nItemCount; nIndex++ )
        {
            IItemList* pSubList = pList->GetItemByIndex( nIndex );
            if ( pSubList != 0 )
            {
                IBaseItem* pSubItem = pSubList->GetItemData();
                if ( pSubItem != 0 && ( pSubItem->IsAlwaysShow() || bItemSel ) )
                {		
                    bResult = IsClick( pSubList, pt, item );
                    if ( bResult )
                    {
                        return bResult;
                    }
                }		
            }
            
            nShowNum++;
            if ( nShowNum >= nShowItemNum )
            {
                break;
            }
	    }
	}
    else
    {
        //ͬһ���Item������ӵ���Ϊ������ӵ����棬��˴Ӻ���ǰ���� -2013.1.24 xcr
        for ( int nIndex = nItemCount - 1; nIndex >= 0; nIndex-- )    
        {
            IItemList* pSubList = pList->GetItemByIndex( nIndex );
            if ( pSubList != 0 )
            {
                IBaseItem* pSubItem = pSubList->GetItemData();
                if ( pSubItem != 0 && ( pSubItem->IsAlwaysShow() || bItemSel ) )
                {		
                    bResult = IsClick( pSubList, pt, item );
                    if ( bResult )
                    {
                        return bResult;
                    }
                }           
            }
	    }
    }

	return bResult;
}

CPoint IList::TransPoint( CPoint& ptSrcCoordinate, CPoint& ptDesCoordinate, CPoint& point )
{
	CPoint ptResult = point;
	//ptResult.x = point.x - ptDesCoordinate.x + ptSrcCoordinate.x ;
	//ptResult.y = point.y - ptDesCoordinate.y + ptSrcCoordinate.y ;

    //point�Ѿ���Src�еĵ㣬��Ӧ��+ptSrcCoordinate  -xcr
    ptResult.x = point.x - ptDesCoordinate.x;
    ptResult.y = point.y - ptDesCoordinate.y;
	return ptResult;
}

IItem< IBaseItem, int >* IList::AddItem( IBaseItem* pItem, IItemList* pParent /* = 0 */ )
{
	if ( pItem == 0 )
	{
		return 0;
	}
	if ( pParent == 0 )
	{
		pParent = m_pItemList;
	}
	CItemGroup<IBaseItem, int> pItemGroup;
	pItemGroup.SetItemData( pItem );
	pParent->AddItem( m_nIndex++, &pItemGroup );	
	return pParent->GetItemByKey( m_nIndex - 1 );
}


IItem< IBaseItem, int >* IList::AddItem( int nIndex, IBaseItem* pItem, IItemList* pParent /* = 0 */ )
{
	if ( NULL == pItem )
	{
		return NULL;
	}
	if ( NULL == pParent )
	{
		pParent = m_pItemList;
	}
	CItemGroup<IBaseItem, int> pItemGroup;
	pItemGroup.SetItemData( pItem );

	IItemList* pItemList = pParent->AddItem( nIndex, &pItemGroup );	
	if ( NULL == pItemList )
	{
		return NULL;
	}

	//����Itemλ��
	IBaseItem* pBaseItem = pParent->GetItemData();	
	if ( pParent->GetItemType() == emGroup )
	{
		String emAlgorithm = pBaseItem->GetLayoutAlgorithm();
		IAlgorithm* pAlgorithm = CAlgorithmFactory::GetAlgorithm( emAlgorithm );
		if ( pAlgorithm != 0 )
		{
			Args_ItemList argItemList( pParent );
			pAlgorithm->TransitionByIndex( nIndex, &argItemList );
		}		
	}

	return pItemList;
}



bool IList::AddItem( IItemList* pList, IItemList* pParent /* = 0 */ )
{
	if ( pParent == 0 )
	{
		pParent = m_pItemList;
	}
	return pParent->AddItem( m_nIndex++, pList );
}

bool IList::DeleteItem( int nIndex, IItemList* pParent /* = 0 */ )
{
	if ( pParent == 0 )
	{
		pParent = m_pItemList;
	}
	return pParent->DeleteItem( nIndex );
}

IItem< IBaseItem, int >* IList::GetItem( IBaseItem* pItem, IItemList* pParent /* = 0 */ )
{
	if ( pParent == 0 )
	{
		pParent = m_pItemList;
	}
	return pParent->GetItemByData( pItem );
}

CRect IList::GetFrame( IItemList* pList /* = 0 */ )
{
	if ( pList == 0 )
	{
		pList = m_pItemList;
	}
	CRect rcResult = CRect(0,0,0,0);
	int nCounts = pList->GetItemCount();

	//�������������Ŀ��С��һ������Ҫ�������
	if ( !m_bItemSizeSame )
	{
		for ( int i = 0; i < nCounts; i++ )
		{
			IItemList* pSub = pList->GetItemByIndex( i );
			if ( pSub != 0 )
			{
				IBaseItem* pBaseItem = pSub->GetItemData();
				if ( pBaseItem != 0 )
				{
					CRect rcItem = pBaseItem->GetItemRect();
					rcItem.NormalizeRect();
					rcResult.UnionRect( rcItem, rcResult );
				}			
			}
		}
	}
	else
	{	//������Ŀ��С��һ��
		if ( nCounts > 0 )
		{
			IBaseItem* pBaseItem = pList->GetItemData();
			
			IItemList* pSub = pList->GetItemByIndex( 0 );
			if ( pSub != 0 )
			{
				IBaseItem* pSubItem = pSub->GetItemData();
				if ( pSubItem != 0 )
				{
					CRect rcItem = pSubItem->GetItemRect();
					rcItem.NormalizeRect();
					if ( pBaseItem->GetLayoutAlgorithm() == IAlgorithm::strVert )
					{
						rcResult.top = rcItem.top;
						rcResult.left = rcItem.left;
						rcResult.right = rcItem.right;
						rcResult.bottom = rcItem.top + ( rcItem.Height() + CLayoutAlgorithm_Vert::nYSpace ) * nCounts - CLayoutAlgorithm_Vert::nYSpace;
					}
					else if ( pBaseItem->GetLayoutAlgorithm() == IAlgorithm::strHori )
					{						
						rcResult.top = rcItem.top;
						rcResult.left = rcItem.left;
						rcResult.right = rcItem.left + rcItem.Width() * nCounts;
						rcResult.bottom = rcItem.bottom;
					}
					
				}				
			}
		}
	}
	
	return rcResult;
}

void IList::Draw( IArgs* pArgs, int nYOffset, int nHeight )
{
	if ( Args_Graphics* p = dynamic_cast<Args_Graphics*>(pArgs) )
	{	
		DrawItem( m_pItemList, pArgs, nYOffset, nHeight );
	}	
}

void IList::DrawItem( IItemList* pItemList, IArgs* pArgs, int nYOffset, int nHeight )
{
	if ( pItemList == NULL )
	{
		return;
	}

 	//2012-8-6 ȥ��try catch   ���������ı�����  by yjj
	int nItemCount = pItemList->GetItemCount();
	IBaseItem* pBaseItem = pItemList->GetItemData();
	if ( pBaseItem == NULL )
	{
		return;
	}
		
	Args_Graphics* p = 0;
	
	Args_Graphics pSubGraphics( 0, Rect(0,0,0,0) );
	Bitmap* pSubBitmap = 0;
	if ( p = dynamic_cast<Args_Graphics*>(pArgs) )
	{
		if ( pBaseItem != 0 )
		{
			pBaseItem->Draw( pArgs );
			CRect rc = pBaseItem->GetItemRect();
			p->m_rc =  Rect( Point(rc.left,rc.top), Size(rc.Width(),rc.Height()) );
			
			CPoint ptOffset = pBaseItem->GetOffset();
			
		//ȥ��ƫ���� 2012-8-6 ���xp��ocx���б�ֻ����ʾ�߰˰ٸ���Ŀ������ by yjj
		//	p->m_pGraphics->TranslateTransform( ptOffset.x, ptOffset.y );
		
			if ( nItemCount != 0 )
			{	
				//ȥ��ƫ���� 2012-8-6 ���xp��ocx���б�ֻ����ʾ�߰˰ٸ���Ŀ������ by yjj	
 				pSubBitmap = new Bitmap( rc.Width() /*+ abs(ptOffset.x)*/, rc.Height() /*+ abs(ptOffset.y)*/, p->m_pGraphics );
				pSubGraphics.m_pGraphics = Graphics::FromImage( pSubBitmap );
 				pSubGraphics.m_rc = Rect( Point(rc.left,rc.top), Size(rc.Width(),rc.Height()) );
				pSubGraphics.m_ptOffset = ptOffset ;	//ȥ��ƫ���� 2012-8-6 ���xp��ocx���б�ֻ����ʾ�߰˰ٸ���Ŀ������ by yjj
			}
		}		
	}
	else
	{
		return;
	}
	
	bool bSetRect = false;
	int nCurItemCnt = 0;
	int nShowItemNum = 0;

	if ( ( pBaseItem->GetLayoutAlgorithm() != IAlgorithm::strVert ) || !m_bItemSizeSame )
	{
        IItemList* pSubList = m_pItemList->GetItemByIndex( 0 );
        if ( pSubList == 0 )
        {
            return;
        }
        
        IBaseItem* pFirstItem = pSubList->GetItemData();
        if ( pFirstItem->GetLayoutAlgorithm() == IAlgorithm::strFileManagerItem )
        {
            //������Ҫ��ʾ����Ŀ
            int nItemHeight = 0;
            if ( nItemCount != 0 && m_pItemList != NULL )
            {
                IItemList* pSubList = m_pItemList->GetItemByIndex( 0 );
                if ( pSubList != 0 )
                {
                    IBaseItem* pFirstItem = pSubList->GetItemData();
                    nItemHeight = pFirstItem->GetItemHeight() + CLayoutAlgorithm_Vert::nYSpace;
                }
            }
            if ( nItemHeight <= 0 )
            {
                return;
            }
            m_nShowItemIndex = 7* (nYOffset / nItemHeight);
            m_nShowItemNum = 7* (nHeight / nItemHeight + 2);
            
            if ( m_nShowItemNum > nItemCount )
            {
                m_nShowItemNum = nItemCount;
            }
            
            nCurItemCnt = m_nShowItemIndex;
            nShowItemNum = m_nShowItemNum;
            
            bSetRect = true;
	    }
        else
        {
            nCurItemCnt = 0;
		    nShowItemNum = nItemCount;
        }
	}
	else
	{
		//������Ҫ��ʾ����Ŀ
		int nItemHeight = 0;
		if ( nItemCount != 0 && m_pItemList != NULL )
		{
			IItemList* pSubList = m_pItemList->GetItemByIndex( 0 );
			if ( pSubList != 0 )
			{
				IBaseItem* pFirstItem = pSubList->GetItemData();
				nItemHeight = pFirstItem->GetItemHeight() + CLayoutAlgorithm_Vert::nYSpace;
			}
		}
		if ( nItemHeight <= 0 )
		{
			return;
		}
		m_nShowItemIndex = nYOffset / nItemHeight;
		m_nShowItemNum = nHeight / nItemHeight + 2;

		if ( m_nShowItemNum > nItemCount )
		{
			m_nShowItemNum = nItemCount;
		}

		nCurItemCnt = m_nShowItemIndex;
		nShowItemNum = m_nShowItemNum;

		bSetRect = true;
	}

	bool bItemSel = true;
	// ������Ŀѡ�е�ʱ��Ž�������Ļ���
	if ( pBaseItem->GetItemStatus() != emItemStatusSel )
	{	
		bItemSel = false;
		if ( m_bShowSubItemAlways == false )
		{
			return;
		}
	}
		
	int nShowNum = 0;
	for ( int nIndex = nCurItemCnt; nIndex < nItemCount; nIndex++ )
	{
		IItemList* pSubList = pItemList->GetItemByIndex( nIndex );
		if ( pSubList != 0 )
		{
			IBaseItem* pItem = pSubList->GetItemData();

			//����ǰ����Itemλ��
			if ( bSetRect && m_bItemSizeSame )
			{
				CRect cRect = pItem->GetItemRect();
				if ( cRect.left == 0 && cRect.top == 0 )
				{
					LayoutByIndex( nIndex, pItemList );
				}
			}					
									
			if ( pItem != 0 && ( pItem->IsAlwaysShow() || bItemSel ) )
			{
				DrawSubItem( pSubList, &pSubGraphics );
			}
			
			nShowNum++;
			if ( nShowNum >= nShowItemNum )
			{
				break;
			}
		}
	}

	if ( nItemCount != 0)
	{  
		 
		p->m_pGraphics->DrawImage( pSubBitmap, p->m_rc.GetLeft() + p->m_ptOffset.x, p->m_rc.GetTop() + p->m_ptOffset.y);
		delete pSubBitmap;
 		pSubBitmap = 0;
		delete pSubGraphics.m_pGraphics;
		pSubGraphics.m_pGraphics = 0;
	}	
// 		if ( pBaseItem != 0 )
// 		{
// 			p->m_pGraphics->ResetTransform();
// 		}
	 
}


void IList::DrawSubItem( IItemList* pItemList, IArgs* pArgs )
{
	int nItemCount = pItemList->GetItemCount();
	IBaseItem* pBaseItem = pItemList->GetItemData();
	if ( pBaseItem == NULL )
	{
		return;
	}
	
	Args_Graphics* p = 0;
	
	Args_Graphics pSubGraphics( 0, Rect(0,0,0,0) );
	Bitmap* pSubBitmap = 0;
	if ( p = dynamic_cast<Args_Graphics*>(pArgs) )
	{
		
		if ( pBaseItem != 0 )
		{
			pBaseItem->Draw( pArgs );
			CRect rc = pBaseItem->GetItemRect();
			p->m_rc =  Rect( Point(rc.left,rc.top), Size(rc.Width(),rc.Height()) );
			
			CPoint ptOffset = pBaseItem->GetOffset();

			 
		//ȥ��ƫ���� 2012-8-6 ���xp��ocx���б�ֻ����ʾ�߰˰ٸ���Ŀ������ by yjj
		//	p->m_pGraphics->TranslateTransform( ptOffset.x, ptOffset.y );
			
			if ( nItemCount != 0 )
			{		
				pSubBitmap = new Bitmap( rc.Width()/* + abs(ptOffset.x)*/, rc.Height() /*+ abs(ptOffset.y)*/, p->m_pGraphics );
				pSubGraphics.m_pGraphics = Graphics::FromImage( pSubBitmap );
				pSubGraphics.m_rc = Rect( Point(rc.left,rc.top), Size(rc.Width(),rc.Height()) );
				pSubGraphics.m_ptOffset = ptOffset ;	//ȥ��ƫ���� 2012-8-6 ���xp��ocx���б�ֻ����ʾ�߰˰ٸ���Ŀ������ by yjj
			}
		}		
	}
	else
	{
		return;
	}
	
	
	bool bItemSel = true;
	// ������Ŀѡ�е�ʱ��Ž�������Ļ���
	if ( pBaseItem->GetItemStatus() != emItemStatusSel )
	{	
		bItemSel = false;
		if ( m_bShowSubItemAlways == false )
		{
			return;
		}
	}
	
	for ( int nIndex = 0; nIndex < nItemCount; nIndex++ )
	{
		IItemList* pSubList = pItemList->GetItemByIndex( nIndex );
		if ( pSubList != 0 )
		{
			IBaseItem* pItem = pSubList->GetItemData();
			//TextItem�븸Item״̬��Ϊһ��
// 			if ( CTextItem* pTextItem = dynamic_cast<CTextItem*>(pItem) )
// 			{
// 				pTextItem->SetItemStatus( pBaseItem->GetItemStatus() );
// 			}
			//û���¼�����Item�븸Item״̬��Ϊһ��
			if ( CListItem* pListItem = dynamic_cast<CListItem*>(pBaseItem) )
			{				
				if ( pItem->GetFunc() == IBaseItem::strDefaultFunc )
				{
					pItem->SetItemStatus( pBaseItem->GetItemStatus() );
				}							
			}
			
			if ( ( pItem != 0 && pItem->IsAlwaysShow() ) || bItemSel )
			{
				DrawSubItem( pSubList, &pSubGraphics );
			}			
		}
	}
	
	if ( nItemCount != 0)
	{
		//ȥ��ƫ���� 2012-8-6 ���xp��ocx���б�ֻ����ʾ�߰˰ٸ���Ŀ������ by yjj
		p->m_pGraphics->DrawImage( pSubBitmap, p->m_rc.GetLeft() + p->m_ptOffset.x, p->m_rc.GetTop() + p->m_ptOffset.y);
		delete pSubBitmap;
		pSubBitmap = 0;
		delete pSubGraphics.m_pGraphics;
		pSubGraphics.m_pGraphics = 0;
	}	
// 	if ( pBaseItem != 0 )
// 	{
// 		p->m_pGraphics->ResetTransform();
// 	}
}


void IList::LayoutItem( IItemList* pList )
{
	if ( pList == 0 )
	{
		pList = m_pItemList;
	}
	Layout( pList );
}

void IList::Layout( IItemList* pItemList )
{
	int nItemCount = pItemList->GetItemCount();
	IBaseItem* pBaseItem = pItemList->GetItemData();
	
	
	if ( pItemList->GetItemType() == emGroup )
	{
		String emAlgorithm = pBaseItem->GetLayoutAlgorithm();

		//�����б�ֱ�ӷ��أ��ڻ���ʱLayout
		if ( m_bItemSizeSame && emAlgorithm == IAlgorithm::strVert )
		{
			return;
		}
		IAlgorithm* pAlgorithm = CAlgorithmFactory::GetAlgorithm( emAlgorithm );
		if ( pAlgorithm != 0 )
		{
			Args_ItemList argItemList( pItemList );
			pAlgorithm->Transition( &argItemList );
		}		
	}
	else
	{
		return;
	}
	for ( int nIndex = 0; nIndex < nItemCount; nIndex++ )
	{
		IItemList* pSubList = pItemList->GetItemByIndex( nIndex );
		if ( pSubList != 0 )
		{
			Layout( pSubList );	
		}
	}
}


void IList::LayoutByIndex( int nIndex, IItemList* pItemList )
{
	IBaseItem* pBaseItem = pItemList->GetItemData();
	if ( pBaseItem == NULL )
	{
		return;
	}

	String emAlgorithm = pBaseItem->GetLayoutAlgorithm();
	IAlgorithm* pAlgorithm = CAlgorithmFactory::GetAlgorithm( emAlgorithm );
	if ( pAlgorithm != 0 )
	{
		Args_ItemList argItemList( pItemList );
		pAlgorithm->TransitionByIndex( nIndex, &argItemList );
	}

	int nItemCount = pItemList->GetItemCount();
	if ( nIndex >= 0 && nIndex < nItemCount )
	{
		IItemList* pSubList = pItemList->GetItemByIndex( nIndex );
		if ( pSubList == 0 )
		{
			return ;
		}
		Layout( pSubList );
	}
}



void IList::SortItem( IItemList* pList /* = 0 */ )
{
	if ( pList == 0 )
	{
		pList = m_pItemList;
	}
	Sort( pList );
}

void IList::Sort( IItemList* pItemList )
{
	int nItemCount = pItemList->GetItemCount();
	if ( nItemCount == 0 )
	{
		return;
	}
	IBaseItem* pBaseItem = pItemList->GetItemData();
	
	if ( pItemList->GetItemType() == emGroup )
	{
		String emAlgorithm = pBaseItem->GetSortAlgorithm();
		IAlgorithm* pAlgorithm = CAlgorithmFactory::GetAlgorithm( emAlgorithm );
		if ( pAlgorithm != 0 )
		{
			Args_ItemList argItemList( pItemList );
			pAlgorithm->Transition( &argItemList );
		}
	}
	else
	{
		return;
	}
	for ( int nIndex = 0; nIndex < nItemCount; nIndex++ )
	{
		IItemList* pSubList = pItemList->GetItemByIndex( nIndex );
		if ( pSubList != 0 )
		{
			Sort( pSubList );	
		}
	}
}

void IList::SetListSize( unsigned int nWidht, unsigned int nHeight, IItemList* pList /* = 0 */ )
{
	if ( pList == 0 )
	{
		pList = m_pItemList;
	}
	IBaseItem* pItem = pList->GetItemData();
	if ( pItem != 0 )
	{
		CRect rc = pItem->GetItemRect();
		rc.right = rc.left + nWidht;
		rc.bottom = rc.top + nHeight;
		pItem->SetItemRect( rc );
	}
	LayoutItem();
}

bool IList::SetLayoutAlgroithm( String strAlgorithm, IItemList* pItem /* = 0 */ )
{
	if ( pItem == 0 )
	{
		pItem = m_pItemList;
	}
	IBaseItem* pItemBase = pItem->GetItemData();
	if ( pItemBase != 0 )
	{
		pItemBase->SetLayoutAlgorithm( strAlgorithm );
		return true;
	}
	return false;
}

String IList::GetLayoutAlgroithm( IItemList* pItem /* = 0 */ )
{
	if ( pItem == 0 )
	{
		pItem = m_pItemList;
	}
	IBaseItem* pItemBase = pItem->GetItemData();
	if ( pItemBase != 0 )
	{
		return pItemBase->GetLayoutAlgorithm();
	}
	return "";
}

bool IList::SetSortAlgroithm( String strAlgorithm, IItemList* pItem /* = 0 */ )
{
	if ( pItem == 0 )
	{
		pItem = m_pItemList;
	}
	IBaseItem* pItemBase = pItem->GetItemData();
	if ( pItemBase != 0 )
	{
		pItemBase->SetSortAlgorithm( strAlgorithm );
		return true;
	}
	return false;
}

String IList::GetSortAlgroithm( IItemList* pItem /* = 0 */ )
{
	if ( pItem == 0 )
	{
		pItem = m_pItemList;
	}
	IBaseItem* pItemBase = pItem->GetItemData();
	if ( pItemBase != 0 )
	{
		return pItemBase->GetSortAlgorithm();
	}
	return "";
}


 
