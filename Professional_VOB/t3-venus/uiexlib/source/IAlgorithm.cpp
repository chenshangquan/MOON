// IAlgorithm.cpp: implementation of the IAlgorithm class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h" 
#include "iBaseItem.h"
#include "algorithm.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const std::string IAlgorithm::strHori = "Hori";
const std::string IAlgorithm::strVert = "Vert";
const std::string IAlgorithm::strVertNoSplit = "VertNoSplit";
const std::string IAlgorithm::strHoriConfLst = "HoriConfLst";
const std::string IAlgorithm::strNormalItem = "NormalItem";
const std::string IAlgorithm::strAddrGroupItem = "AddrGroupItem";
const std::string IAlgorithm::strTextOnly = "TextOnly";
const std::string IAlgorithm::strDoubleColumn = "DoubleColumn";
const std::string IAlgorithm::strTPadMainMenu = "TPadMainMenu";
const std::string IAlgorithm::strTextBottom= "TextBottom";
const std::string IAlgorithm::strWifiItem = "WifiItem";
const std::string IAlgorithm::strTvwView = "TvwView";
const std::string IAlgorithm::strTvwItem = "TvwItem"; 
const std::string IAlgorithm::strBoardView = "BoardView";
const std::string IAlgorithm::strBoardItem = "BoardItem";
const std::string IAlgorithm::strTPadIpList = "TPadIpList";
const std::string IAlgorithm::strMultiColumn = "MultiColumn";
const std::string IAlgorithm::strCharacter = "Char";
const std::string IAlgorithm::strDefaultAlg = "";
//const std::string IAlgorithm::strNetMngList = "NetMngList";
const std::string IAlgorithm::strComboxItem = "ComboxItem";
const std::string IAlgorithm::strBoardUpgradItem = "BoardUpgradItem"; 
const std::string IAlgorithm::strFileManagerItem = "FileManagerItem"; //�ļ�����
const std::string IAlgorithm::strPreTextBottom = "PreTextBottom";




IAlgorithm::IAlgorithm()
{

}

IAlgorithm::~IAlgorithm()
{

}

map< std::string, IAlgorithm* > CAlgorithmFactory::m_mapAlgorithms;
IAlgorithm* CAlgorithmFactory::GetAlgorithm( std::string strAlg )
{
	AlgorithmMap::iterator itr = m_mapAlgorithms.find( strAlg );
	if ( itr != m_mapAlgorithms.end() )
	{
		return itr->second;
	}
	return 0;
}

bool CAlgorithmFactory::AddAlgorithm( std::string strName, IAlgorithm* pAlgorithm )
{
	if ( pAlgorithm == 0 )
	{
		return false;
	}
	AlgorithmMap::iterator itr = m_mapAlgorithms.find( strName );

	if ( itr != m_mapAlgorithms.end() )
	{
		if ( pAlgorithm != itr->second )
		{
			delete itr->second;
			itr->second = pAlgorithm;
			return true;
		}
		else
		{
			return false;
		}
	}
	m_mapAlgorithms.insert( AlgorithmMap::value_type( strName, pAlgorithm ) );
	return true;
}

/*const*/ int CLayoutAlgorithm_Vert::nXSpace = 2;
const int CLayoutAlgorithm_Vert::nYSpace = 2;
bool CLayoutAlgorithm_Vert::Transition( IArgs* pArgs )
{
	Args_ItemList* p = 0;
	if ( p = dynamic_cast<Args_ItemList*>(pArgs) )
	{
		IItemList* pList = p->m_pList;
		if ( pList == 0 )
		{
			return false;
		}
		int nItemCounts = pList->GetItemCount();
		IBaseItem* pItem = pList->GetItemData();
		if ( pItem == 0 )
		{
			return false;
		}
		int nParentWidth = pItem->GetItemWidth();
		CRect rcLast( 0, 0, 0, 0 );
		
		for ( int i = 0; i < nItemCounts; i++ )
		{
			IItemList* pSubList = pList->GetItemByIndex( i );
			if ( pSubList == 0 )
			{
				continue;
			}
			IBaseItem* pItem = pSubList->GetItemData();
			if ( pItem == 0 )
			{
				continue;
			}

			int nHeight = pItem->GetItemHeight();
			rcLast.SetRect( nXSpace, rcLast.bottom + nYSpace, nParentWidth - nXSpace, rcLast.bottom + nYSpace + nHeight );
			pItem->SetItemRect( rcLast );
		}

	}
	return false;
}

bool CLayoutAlgorithm_Vert::TransitionByIndex( int nIndex, IArgs* pArgs )
{
	Args_ItemList* p = 0;
	if ( p = dynamic_cast<Args_ItemList*>(pArgs) )
	{
		IItemList* pList = p->m_pList;
		if ( pList == 0 )
		{
			return false;
		}
		int nItemCounts = pList->GetItemCount();
		IBaseItem* pItem = pList->GetItemData();
		if ( pItem == 0 )
		{
			return false;
		}
		int nParentWidth = pItem->GetItemWidth();
		CRect rcRect( 0, 0, 0, 0 );

		if ( nIndex >= 0 && nIndex < nItemCounts )
		{
			IItemList* pSubList = pList->GetItemByIndex( nIndex );
			if ( pSubList == 0 )
			{
				return false;
			}
			IBaseItem* pItem = pSubList->GetItemData();
			if ( pItem == 0 )
			{
				return false;
			}

			int nHeight = pItem->GetItemHeight();
			if ( nIndex == 0 )
			{
				rcRect.SetRect( nXSpace, nYSpace, nParentWidth - nXSpace, nYSpace + nHeight );
			}
			else
			{
				rcRect.SetRect( nXSpace, nYSpace + (nHeight + nYSpace) * nIndex, nParentWidth - nXSpace, nYSpace + (nHeight + nYSpace) * nIndex + nHeight );

				//IItemList* pLastList = pList->GetItemByKey( nIndex - 1 );
				//IBaseItem* pItem = pLastList->GetItemData();
				//CRect rcLast = pItem->GetItemRect();
				//rcRect.SetRect( nXSpace, rcLast.bottom + nYSpace, nParentWidth - nXSpace, rcLast.bottom + nYSpace + nHeight );
			}

			pItem->SetItemRect( rcRect );
		}

	}
	return true;
}

const int CLayoutAlgorithm_VertNoSplit::nXSpace = 0;
const int CLayoutAlgorithm_VertNoSplit::nYSpace = 0;
bool CLayoutAlgorithm_VertNoSplit::Transition( IArgs* pArgs )
{
	Args_ItemList* p = 0;
	if ( p = dynamic_cast<Args_ItemList*>(pArgs) )
	{
		IItemList* pList = p->m_pList;
		if ( pList == 0 )
		{
			return false;
		}
		int nItemCounts = pList->GetItemCount();
		IBaseItem* pItem = pList->GetItemData();
		if ( pItem == 0 )
		{
			return false;
		}
		int nParentWidth = pItem->GetItemWidth();
		CRect rcLast( 0, 0, 0, 0 );
		
		for ( int i = 0; i < nItemCounts; i++ )
		{
			IItemList* pSubList = pList->GetItemByIndex( i );
			if ( pSubList == 0 )
			{
				continue;
			}
			IBaseItem* pItem = pSubList->GetItemData();
			if ( pItem == 0 )
			{
				continue;
			}
			
			int nHeight = pItem->GetItemHeight();
			rcLast.SetRect( nXSpace, rcLast.bottom + nYSpace, nParentWidth - nXSpace, rcLast.bottom + nYSpace + nHeight );
			pItem->SetItemRect( rcLast );
		}
		
	}
	return false;
}

bool CLayoutAlgorithm_VertNoSplit::TransitionByIndex( int nIndex, IArgs* pArgs )
{
	Args_ItemList* p = 0;
	if ( p = dynamic_cast<Args_ItemList*>(pArgs) )
	{
		IItemList* pList = p->m_pList;
		if ( pList == 0 )
		{
			return false;
		}
		int nItemCounts = pList->GetItemCount();
		IBaseItem* pItem = pList->GetItemData();
		if ( pItem == 0 )
		{
			return false;
		}
		int nParentWidth = pItem->GetItemWidth();
		CRect rcRect( 0, 0, 0, 0 );
		
		if ( nIndex >= 0 && nIndex < nItemCounts )
		{
			IItemList* pSubList = pList->GetItemByIndex( nIndex );
			if ( pSubList == 0 )
			{
				return false;
			}
			IBaseItem* pItem = pSubList->GetItemData();
			if ( pItem == 0 )
			{
				return false;
			}
			
			int nHeight = pItem->GetItemHeight();
			if ( nIndex == 0 )
			{
				rcRect.SetRect( nXSpace, nYSpace, nParentWidth - nXSpace, nYSpace + nHeight );
			}
			else
			{
				rcRect.SetRect( nXSpace, nYSpace + (nHeight + nYSpace) * nIndex, nParentWidth - nXSpace, nYSpace + (nHeight + nYSpace) * nIndex + nHeight );
				
				//IItemList* pLastList = pList->GetItemByKey( nIndex - 1 );
				//IBaseItem* pItem = pLastList->GetItemData();
				//CRect rcLast = pItem->GetItemRect();
				//rcRect.SetRect( nXSpace, rcLast.bottom + nYSpace, nParentWidth - nXSpace, rcLast.bottom + nYSpace + nHeight );
			}
			
			pItem->SetItemRect( rcRect );
		}
		
	}
	return true;
}

const int CLayoutAlgorithm_Hori::nXSpace = 0;
const int CLayoutAlgorithm_Hori::nYSpace = 0;
bool CLayoutAlgorithm_Hori::Transition( IArgs* pArgs )
{
	Args_ItemList* p = 0;
	if ( p = dynamic_cast<Args_ItemList*>(pArgs) )
	{
		IItemList* pList = p->m_pList;
		if ( pList == 0 )
		{
			return false;
		}
		int nItemCounts = pList->GetItemCount();
		IBaseItem* pItem = pList->GetItemData();
		if ( pItem == 0 )
		{
			return false;
		}
		int nParentHeight = pItem->GetItemHeight();	 
		CRect rcLast( 0, 0, 0, 0 );
		for ( int i = 0; i < nItemCounts; i++ )
		{
			IItemList* pSubList = pList->GetItemByIndex( i );
			if ( pSubList == 0 )
			{
				continue;
			}
			IBaseItem* pItem = pSubList->GetItemData();
			if ( pItem == 0 )
			{
				continue;
			}
			CRect rc = pItem->GetItemRect();
			int nWidht = pItem->GetItemWidth();

			rcLast.SetRect( rcLast.right + nXSpace, nYSpace, rcLast.right + nXSpace + rc.Width(), nParentHeight - nYSpace );	
			pItem->SetItemRect( rcLast );
		}
	}
	return false;
}

/*---------------------------------------------------------------------
* ��	����CLayoutAlgorithm_NormalItem
* ��    �ܣ�һ����Ŀ�����㷨
* ����˵����һ����Ŀ��ǰ����ʾ���֣�������ʾ����ͼ�꣬��������
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/09/01	v1.0		Ф��Ȼ		����
----------------------------------------------------------------------*/
bool CLayoutAlgorithm_NormalItem::Transition( IArgs* pArgs )
{
	Args_ItemList* p = NULL;
	if ( p = dynamic_cast<Args_ItemList*>(pArgs) )
	{
		IItemList* pList = p->m_pList;
		if ( pList == 0 )
		{
			return false;
		}
		int nItemCounts = pList->GetItemCount();
		IBaseItem* pItem = pList->GetItemData();
		if ( pItem == 0 )
		{
			return false;
		}
		int nParentWidth = pItem->GetItemWidth();
		int nParentHeight = pItem->GetItemHeight();
		CRect rcLast( 0, 0, 0, 0 );

		for ( int i = 0; i < nItemCounts; i++ )
		{
			IItemList* pSubList = pList->GetItemByIndex( i );
			if ( pSubList == 0 )
			{
				continue;
			}
			IBaseItem* pItem = pSubList->GetItemData();
			if ( pItem == 0 )
			{
				continue;
			}
			CRect rc = pItem->GetItemRect();
			int nWidth = pItem->GetItemWidth();
			int nHeight = pItem->GetItemHeight();
			//��һ��Ĭ��ΪTextItem������ΪImageItem
			if ( i == 0 ) 
			{	
				if ( nItemCounts > 1 )
				{
					rcLast.SetRect( 19, 0, nParentWidth - 65, nParentHeight );
				}
				else
				{
					rcLast.SetRect( 19, 0, nParentWidth - 5, nParentHeight );
				}			
				pItem->SetItemRect( rcLast );
			}
			else if ( i == 1 )
			{
				int nLeft = nParentWidth - 16 - nWidth;
				int nTop = nParentHeight/2 - nHeight/2;
				rcLast.SetRect( nLeft, nTop, nLeft + nWidth, nTop + nHeight );
				pItem->SetItemRect( rcLast );
			}	
			else
			{
				int nLeft = rcLast.left - nWidth - 2;
				int nTop = nParentHeight/2 - nHeight/2;
				rcLast.SetRect( nLeft, nTop, nLeft + nWidth, nTop + nHeight );
				pItem->SetItemRect( rcLast );
			}
		}
	}
	return false;
}


bool CLayoutAlgorithm_NormalItem::TransitionByIndex( int nIndex, IArgs* pArgs )
{
	Args_ItemList* p = 0;
	if ( p = dynamic_cast<Args_ItemList*>(pArgs) )
	{
		IItemList* pList = p->m_pList;
		if ( pList == 0 )
		{
			return false;
		}
		int nItemCounts = pList->GetItemCount();
		IBaseItem* pItem = pList->GetItemData();
		if ( pItem == 0 )
		{
			return false;
		}
		int nParentWidth = pItem->GetItemWidth();
		int nParentHeight = pItem->GetItemHeight();
		CRect rcRect( 0, 0, 0, 0 );

		if ( nIndex >= 0 && nIndex < nItemCounts )
		{
			IItemList* pSubList = pList->GetItemByIndex( nIndex );
			if ( pSubList == 0 )
			{
				return false;
			}
			IBaseItem* pItem = pSubList->GetItemData();
			if ( pItem == 0 )
			{
				return false;
			}
			int nWidth = pItem->GetItemWidth();
			int nHeight = pItem->GetItemHeight();
			if ( nIndex == 0 )
			{
				if ( nItemCounts > 1 )
				{
					rcRect.SetRect( 19, 0, nParentWidth - 65, nParentHeight );
 				}
 				else
 				{
 					rcRect.SetRect( 19, 0, nParentWidth - 5, nParentHeight );
 				}							
			}
			else if ( nIndex == 1 )
			{
				int nLeft = nParentWidth - 16 - nWidth;
				int nTop = nParentHeight/2 - nHeight/2;
				rcRect.SetRect( nLeft, nTop, nLeft + nWidth, nTop + nHeight );
			}
			else
			{
				IItemList* pLastList = pList->GetItemByIndex( nIndex - 1 );
				IBaseItem* pItem = pLastList->GetItemData();
				CRect rcLast = pItem->GetItemRect();
				
				int nLeft = rcLast.left - nWidth - 2;
				int nTop = nParentHeight/2 - nHeight/2;
				rcRect.SetRect( nLeft , nTop, nLeft + nWidth, nTop + nHeight );
			}
			
			pItem->SetItemRect( rcRect );
		}
	}
	return true;
}


/*---------------------------------------------------------------------
* ��	����CLayoutAlgorithm_AddrGroupItem
* ��    �ܣ���ַ��������Ŀ�����㷨
* ����˵����1.������ 2.����  3.ͼ��
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/09/01	v1.0		Ф��Ȼ		����
----------------------------------------------------------------------*/
bool CLayoutAlgorithm_AddrGroupItem::Transition( IArgs* pArgs )
{
	Args_ItemList* p = NULL;
	if ( p = dynamic_cast<Args_ItemList*>(pArgs) )
	{
		IItemList* pList = p->m_pList;
		if ( pList == 0 )
		{
			return false;
		}
		int nItemCounts = pList->GetItemCount();
		IBaseItem* pItem = pList->GetItemData();
		
		if ( pItem == 0 )
		{
			return false;
		}
		int nParentWidth = pItem->GetItemWidth();
		int nParentHeight = pItem->GetItemHeight();
		CRect rcLast( 0, 0, 0, 0 );		
		for ( int i = 0; i < nItemCounts; i++ )
		{
			IItemList* pSubList = pList->GetItemByIndex( i );
			if ( pSubList == 0 )
			{
				continue;
			}
			IBaseItem* pItem = pSubList->GetItemData();
			if ( pItem == 0 )
			{
				continue;
			}

			int nWidth = pItem->GetItemWidth();
			int nHeight = pItem->GetItemHeight();
			int nTop = 0;
			//��һ��ΪGroupName,�ڶ���GroupNum,������ΪImageItem
			if ( i == 0 )
			{   
				int nLeft = 93;
			    
				if ( nItemCounts > 2 )
				{				
					//2012-6-19 ����ֱ�������Ӧ����   by yjj
					IItemList* pSubList2 = pList->GetItemByIndex( 2 );
					if ( pSubList2 != 0 )
					{  
						//ͼƬ�ұߵ�����
						int nRight = 0;
						IBaseItem* pItem = pSubList2->GetItemData();
						if ( pItem != 0 )
						{
							 nRight = pItem->GetItemWidth() + 15;
						} 
                   
						//GroupNum���ұ�����
						IItemList* pSubList1 = pList->GetItemByIndex( 1 );
						if ( pSubList1 != 0 )
						{  				 
							IBaseItem* pItem = pSubList1->GetItemData();
							if ( pItem != 0 )
							{
								nRight = pItem->GetItemWidth() + nRight;
							}
						}
							
						nLeft = nRight;
					} 
				}

				if ( nItemCounts > 3 )
				{
					rcLast.SetRect( nLeft, 0, nParentWidth - 65, nParentHeight );
				}
				else
				{
					rcLast.SetRect( nLeft, 0, nParentWidth - 5, nParentHeight );
				}			
				pItem->SetItemRect( rcLast );
			}
			else if ( i == 1 )
			{
				int nRight = rcLast.left;
				rcLast.SetRect( nRight - nWidth, 0, nRight, nParentHeight );
				pItem->SetItemRect( rcLast );
			}
			else if ( i == 2 ) 
			{	
				nTop = nParentHeight/2 - nHeight/2;
				rcLast.SetRect( 15, nTop, 15 + nWidth, nTop + nHeight );
				pItem->SetItemRect( rcLast );
			}
			else if ( i == 3 )
			{
				int nLeft = nParentWidth - 16 - nWidth;
				nTop = nParentHeight/2 - nHeight/2;
				rcLast.SetRect( nLeft, nTop, nLeft + nWidth, nTop + nHeight );
				pItem->SetItemRect( rcLast );
			}
			else
			{
				int nLeft = rcLast.left - nWidth - 2;
				nTop = nParentHeight/2 - nHeight/2;
				rcLast.SetRect( nLeft, nTop, nLeft + nWidth, nTop + nHeight );
				pItem->SetItemRect( rcLast );
			}
		}
	}
	return false;
}


/*---------------------------------------------------------------------
* ��	����CLayoutAlgorithm_HoriConfLst
* ��    �ܣ�����������Ŀ�����㷨
* ����˵������������3����Ŀ��������ʾ������Ϣ
* �޸ļ�¼����һ�и�Ϊ��ʾ������Ϣ
* ����			�汾		�޸���		�޸ļ�¼
* 2011/09/01	v1.0		�����		����
----------------------------------------------------------------------*/
bool CLayoutAlgorithm_HoriConfLst::Transition( IArgs* pArgs )
{
    Args_ItemList* p = 0;
    if ( p = dynamic_cast<Args_ItemList*>(pArgs) )
    {
        IItemList* pList = p->m_pList;
        if ( pList == 0 )
        {
            return false;
        }
        int nItemCounts = pList->GetItemCount();
        IBaseItem* pItem = pList->GetItemData();
        if ( pItem == 0 )
        {
            return false;
        }
        int nParentHeight = pItem->GetItemHeight();
        int nParentWidth = pItem->GetItemWidth();
        CRect rcLast( 0, 0, 0, 0 );
        for ( int i = 0; i < nItemCounts; i++ )
        {
            IItemList* pSubList = pList->GetItemByIndex( i );
            if ( pSubList == 0 )
            {
                continue;
            }
            IBaseItem* pItem = pSubList->GetItemData();
            if ( pItem == 0 )
            {
                continue;
            }
            if ( i == 0 )
            {
				rcLast.SetRect( 240, 0, nParentWidth - 60, nParentHeight );
                //rcLast.SetRect( 19 , 0, 125, nParentHeight );
            }
            else if( i == 1 )
            {        
				rcLast.SetRect( rcLast.left - 96 , 0, rcLast.left - 10, nParentHeight );
                //rcLast.SetRect( rcLast.right + 19 , 0,  230, nParentHeight);
            }
            else if ( i == 2 )
            {
				rcLast.SetRect( 19 , 0, rcLast.left - 19, nParentHeight );
                //rcLast.SetRect( rcLast.right + 10 , 0, nParentWidth - 60, nParentHeight);
            }
			else
			{
				int nWidth = pItem->GetItemWidth();
				int nHeight = pItem->GetItemHeight();
				int nTop = nParentHeight/2 - nHeight/2;
				rcLast.SetRect( nParentWidth - 19 - nWidth, nTop, nParentWidth - 19, nTop + nHeight);
			}

            pItem->SetItemRect( rcLast );
        }
    }
    return false;
}

/*---------------------------------------------------------------------
* ��	����CLayoutAlgorithm_TextOnly
* ��    �ܣ�ֻ��ʾ���������㷨
* ����˵����ֻ��ʾһ��������Ŀ�����ڸ澯��
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/11/30	v1.0		Ф��Ȼ		����
----------------------------------------------------------------------*/
bool CLayoutAlgorithm_TextOnly::Transition( IArgs* pArgs )
{
	Args_ItemList* p = NULL;
	if ( p = dynamic_cast<Args_ItemList*>(pArgs) )
	{
		IItemList* pList = p->m_pList;
		if ( pList == 0 )
		{
			return false;
		}
		int nItemCounts = pList->GetItemCount();
		IBaseItem* pItem = pList->GetItemData();
		if ( pItem == 0 )
		{
			return false;
		}
		int nParentWidth = pItem->GetItemWidth();
		int nParentHeight = pItem->GetItemHeight();
		CRect rcLast( 0, 0, 0, 0 );		
		for ( int i = 0; i < nItemCounts; i++ )
		{
			IItemList* pSubList = pList->GetItemByIndex( i );
			if ( pSubList == 0 )
			{
				continue;
			}
			IBaseItem* pItem = pSubList->GetItemData();
			if ( pItem == 0 )
			{
				continue;
			}

			rcLast.SetRect( nParentWidth/20, 0, nParentWidth - nParentWidth/20, nParentHeight );
			pItem->SetItemRect( rcLast );
		}
	}
	return false;
}

/*---------------------------------------------------------------------
* ��	����CLayoutAlgorithm_DoubleColumn
* ��    �ܣ�˫����Ŀ�����㷨
* ����˵����ÿ��7��������7����˫�С����ڵ�¼�᳡ѡ�����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/11/30	v1.0		Ф��Ȼ		����
----------------------------------------------------------------------*/
bool CLayoutAlgorithm_DoubleColumn::Transition( IArgs* pArgs )
{
	Args_ItemList* p = NULL;
	if ( p = dynamic_cast<Args_ItemList*>(pArgs) )
	{
		IItemList* pList = p->m_pList;
		if ( pList == 0 )
		{
			return false;
		}
		int nItemCounts = pList->GetItemCount();
		IBaseItem* pItem = pList->GetItemData();
		if ( pItem == 0 )
		{
			return false;
		}

		int nParentWidth = pItem->GetItemWidth();
      
		int nUpDownSpace = 8;
		int nLeftRightSpace = 52 * nParentWidth / 960;
				
		CRect rcLast( 0, 0, 0, 0 );
		if ( nItemCounts < 8 ) //һ�����7����Ŀ������7��������
		{
			//����Ӧ���ȱ������ƫ��λ��
			int nLeft = 239 * nParentWidth / 960;

			for ( int i = 0; i < nItemCounts; i++ )
			{
				IItemList* pSubList = pList->GetItemByIndex( i );
				if ( pSubList == 0 )
				{
					continue;
				}
				IBaseItem* pItem = pSubList->GetItemData();
				if ( pItem == 0 )
				{
					continue;
				}
				CRect rc = pItem->GetItemRect();
				int nWidht = pItem->GetItemWidth();
				int nHeight = pItem->GetItemHeight();
						
				if( i == 0 )
				{
					rcLast.SetRect( /*239*/nLeft, 0, nLeft + nWidht, nHeight );
				}
				else
				{
					rcLast.SetRect( nLeft, rcLast.bottom + nUpDownSpace, nLeft + nWidht, rcLast.bottom + nUpDownSpace + nHeight );
				}
				pItem->SetItemRect( rcLast );
			}
		}
		else
		{
			for ( int i = 0; i < nItemCounts; i++ )
			{
				IItemList* pSubList = pList->GetItemByIndex( i );
				if ( pSubList == 0 )
				{
					continue;
				}
				IBaseItem* pItem = pSubList->GetItemData();
				if ( pItem == 0 )
				{
					continue;
				}
				int nWidht = pItem->GetItemWidth();
				int nHeight = pItem->GetItemHeight();
       				
				if ( i < 7 )
				{   
					if( i == 0 )
					{
						rcLast.SetRect( 0, 0, nWidht, nHeight );
					}
					else
					{
						rcLast.SetRect( 0, rcLast.bottom + nUpDownSpace, nWidht, rcLast.bottom + nUpDownSpace + nHeight );
					}
				}
				else
				{   
					if ( i == 7 )
					{
						rcLast.SetRect( nWidht + nLeftRightSpace, 0, 2 * nWidht + nLeftRightSpace, nHeight );
					}
					else
					{
						rcLast.SetRect( nWidht + nLeftRightSpace, rcLast.bottom + nUpDownSpace, 2 * nWidht + nLeftRightSpace, rcLast.bottom + nUpDownSpace + nHeight );
					}
				}
				
				pItem->SetItemRect( rcLast );
			}
		}		
	}
	return false;
}

/*---------------------------------------------------------------------
* ��	����CLayoutAlgorithm_TPadMainMenu
* ��    �ܣ�TPad���˵������㷨
* ����˵��������Tpad�����棬ÿ��3����Ŀ
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2012/04/01	v1.0		Ф��Ȼ		����
----------------------------------------------------------------------*/
bool CLayoutAlgorithm_TPadMainMenu::Transition( IArgs* pArgs )
{
	Args_ItemList* p = NULL;
	if ( p = dynamic_cast<Args_ItemList*>(pArgs) )
	{
		IItemList* pList = p->m_pList;
		if ( pList == 0 )
		{
			return false;
		}
		int nItemCounts = pList->GetItemCount();
		IBaseItem* pItem = pList->GetItemData();
		if ( pItem == 0 )
		{
			return false;
		}
		int nParentWidth = pItem->GetItemWidth();

		//�ȱ�������Ӧ
		int nFirstLeft = 272 * nParentWidth / 1366;   //��ʼ��λ��
		int nVertSpace = 241 * nParentWidth / 1366;   //��ֱ���
		int nHoriSpace = 219 * nParentWidth / 1366;   //ˮƽ���
//         int nFirstLeft = 272;
//         int nVertSpace = 241;
//         int nHoriSpace = 219;

		CRect rcLast( 0, 0, 0, 0 );
		for ( int i = 0; i < nItemCounts; i++ )
		{
			IItemList* pSubList = pList->GetItemByIndex( i );
			if ( pSubList == 0 )
			{
				continue;
			}
			IBaseItem* pItem = pSubList->GetItemData();
			if ( pItem == 0 )
			{
				continue;
			}
			int nWidht = pItem->GetItemWidth();
			int nHeight = pItem->GetItemHeight();

			int nRow = i / 3; //һ��3��Item
			if ( nItemCounts == 3 )
			{
				if ( i%3 == 0 )
				{
					rcLast.SetRect( nFirstLeft, 236 + nVertSpace*nRow , nFirstLeft + nWidht, 236 + nVertSpace*nRow + nHeight );
				}
				else
				{
					rcLast.SetRect( rcLast.right + nHoriSpace, 236 + nVertSpace*nRow, rcLast.right + nHoriSpace + nWidht, 236 + nVertSpace*nRow + nHeight );
				}
			}
			else
			{
				if( i%3 == 0 )
				{
					rcLast.SetRect( nFirstLeft, 115 + nVertSpace*nRow, nFirstLeft + nWidht, 115 + nVertSpace*nRow + nHeight );
				}
				else
				{
					rcLast.SetRect( rcLast.right + nHoriSpace, 115 + nVertSpace*nRow, rcLast.right + nHoriSpace + nWidht, 115 + nVertSpace*nRow + nHeight );
				}
			}
			pItem->SetItemRect( rcLast );
		}
	}

	return false;
}

/*---------------------------------------------------------------------
* ��	����CLayoutAlgorithm_TextBottom
* ��    �ܣ�����λ�ڵײ������㷨
* ����˵��������Tpad������
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2012/04/01	v1.0		Ф��Ȼ		����
----------------------------------------------------------------------*/
bool CLayoutAlgorithm_TextBottom::Transition( IArgs* pArgs )
{
	Args_ItemList* p = NULL;
	if ( p = dynamic_cast<Args_ItemList*>(pArgs) )
	{
		IItemList* pList = p->m_pList;
		if ( pList == 0 )
		{
			return false;
		}
		int nItemCounts = pList->GetItemCount();
		IBaseItem* pItem = pList->GetItemData();
		if ( pItem == 0 )
		{
			return false;
		}
		int nParentWidth = pItem->GetItemWidth();
		int nParentHeight = pItem->GetItemHeight();
		CRect rcLast( 0, 0, 0, 0 );		
		for ( int i = 0; i < nItemCounts; i++ )
		{
			IItemList* pSubList = pList->GetItemByIndex( i );
			if ( pSubList == 0 )
			{
				continue;
			}
			IBaseItem* pItem = pSubList->GetItemData();
			if ( pItem == 0 )
			{
				continue;
			}
			int nHeight = pItem->GetItemHeight();
			rcLast.SetRect( 0, nParentHeight - nHeight + 29, nParentWidth, nParentHeight );
			pItem->SetItemRect( rcLast );
		}
	}
	return false;
}

/*---------------------------------------------------------------------
* ��	����CLayoutAlgorithm_WifiItem
* ��    �ܣ�Wifi��Ŀ�����㷨
* ����˵��������Tpad wifi��������
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2012/04/01	v1.0		Ф��Ȼ		����
----------------------------------------------------------------------*/
bool CLayoutAlgorithm_WifiItem::Transition( IArgs* pArgs )
{
	Args_ItemList* p = NULL;
	if ( p = dynamic_cast<Args_ItemList*>(pArgs) )
	{
		IItemList* pList = p->m_pList;
		if ( pList == 0 )
		{
			return false;
		}
		int nItemCounts = pList->GetItemCount();
		IBaseItem* pItem = pList->GetItemData();
		if ( pItem == 0 )
		{
			return false;
		}
		int nParentWidth = pItem->GetItemWidth();
		int nParentHeight = pItem->GetItemHeight();
		CRect rcLast( 0, 0, 0, 0 );
		
		for ( int i = 0; i < nItemCounts; i++ )
		{
			IItemList* pSubList = pList->GetItemByIndex( i );
			if ( pSubList == 0 )
			{
				continue;
			}
			IBaseItem* pItem = pSubList->GetItemData();
			if ( pItem == 0 )
			{
				continue;
			}
			int nWidth = pItem->GetItemWidth();
			int nHeight = pItem->GetItemHeight();
			//�ڶ���ΪTextItem������ΪImageItem
			if ( i == 0 ) 
			{	
				int nTop = nParentHeight/2 - nHeight/2;
				rcLast.SetRect( 10, nTop, 10 + nWidth, nTop + nHeight );
				pItem->SetItemRect( rcLast );
			}
			else if ( i == 1 )
			{
				rcLast.SetRect( 45, 0, 45 + nWidth, nParentHeight );
				pItem->SetItemRect( rcLast );
			}	
			else if ( i == 2 )
			{
                int nLeft = nParentWidth - 13 - nWidth;
                int nTop = nParentHeight/2 - nHeight/2;
                rcLast.SetRect( nLeft, nTop, nLeft + nWidth, nTop + nHeight );
                pItem->SetItemRect( rcLast );
			}
			else
			{
				int nLeft = rcLast.left - nWidth - 13;
				int nTop = nParentHeight/2 - nHeight/2;
				rcLast.SetRect( nLeft, nTop, nLeft + nWidth, nTop + nHeight );
				pItem->SetItemRect( rcLast );
			}
		}
	}
	return true;
}

/*---------------------------------------------------------------------
* ��	CLayoutAlgorithm_BoardView
* ��    �ܣ�������ͼ�����㷨
* ����˵�������ڵ�������
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2012/12/18	v1.0		����ӡ		����
----------------------------------------------------------------------*/
bool CLayoutAlgorithm_BoardView::Transition( IArgs* pArgs )
{
    Args_ItemList* p = NULL;
    if ( p = dynamic_cast<Args_ItemList*>(pArgs) )
    {
        IItemList* pList = p->m_pList;
        if ( pList == 0 )
        {
            return false;
        }
        int nItemCounts = pList->GetItemCount();
        IBaseItem* pItem = pList->GetItemData();
        if ( pItem == 0 )
        {
            return false;
        }
        int nParentWidth = pItem->GetItemWidth();
       
        int nFirstLeft = 22;
        int nVertSpace = 13;
        int nHoriSpace = 9;
		int nTopSpace  = 13;
        
        CRect rcLast( 0, 0, 0, 0 );
        for ( int i = 0; i < nItemCounts; i++ )
        {
            IItemList* pSubList = pList->GetItemByIndex( i );
            if ( pSubList == 0 )
            {
                continue;
            }
            IBaseItem* pItem = pSubList->GetItemData();
            if ( pItem == 0 )
            {
                continue;
            }
            int nWidht = pItem->GetItemWidth();
            int nHeight = pItem->GetItemHeight();
            
            int nRow = i / 9; //һ��9��Item
            if( i%9 == 0 )
            {
                rcLast.SetRect( nFirstLeft, nTopSpace + (nHeight + nVertSpace)*nRow, nFirstLeft + nWidht, nTopSpace + (nHeight + nVertSpace)*nRow + nHeight );
            }
            else
            {
                rcLast.SetRect( rcLast.right + nHoriSpace, nTopSpace + (nHeight + nVertSpace)*nRow, rcLast.right + nHoriSpace + nWidht, nTopSpace+ (nHeight + nVertSpace)*nRow + nHeight );
            }

            pItem->SetItemRect( rcLast );
        }
	}
    return true;
}

/*---------------------------------------------------------------------
* ��	CLayoutAlgorithm_BoardItem
* ��    �ܣ�������Ŀ�����㷨
* ����˵�������ڵ��������ڲ�
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2012/12/18	v1.0		����ӡ		����
----------------------------------------------------------------------*/
bool CLayoutAlgorithm_BoardItem::Transition( IArgs* pArgs )
{
    Args_ItemList* p = NULL;
    if ( p = dynamic_cast<Args_ItemList*>(pArgs) )
    {
        IItemList* pList = p->m_pList;
        if ( pList == 0 )
        {
            return false;
        }
        int nItemCounts = pList->GetItemCount();
        IBaseItem* pItem = pList->GetItemData();
        if ( pItem == 0 )
        {
            return false;
        }
        int nParentWidth = pItem->GetItemWidth();
        int nParentHeight = pItem->GetItemHeight();
        CRect rcLast( 0, 0, 0, 0 );		
        for ( int i = 0; i < nItemCounts; i++ )
        {
            IItemList* pSubList = pList->GetItemByIndex( i );
            if ( pSubList == 0 )
            {
                continue;
            }
            IBaseItem* pSubItem = pSubList->GetItemData();
            if ( pItem == 0 )
            {
                continue;
            }

			int nYOffset = 32;
			int nTextOffset = 20;

			
			int nWidth = pSubItem->GetItemWidth();
            int nHeight = pSubItem->GetItemHeight();

            if ( i == 0 ) 
            {	
                rcLast.SetRect( 0, nYOffset, nParentWidth, nHeight + nYOffset );
                pSubItem->SetItemRect( rcLast );
			}
			else
            {		
                rcLast.SetRect( 0, rcLast.bottom, nParentWidth, nYOffset + nTextOffset);
                pSubItem->SetItemRect( rcLast );
			}        
        }
	}
    return true;
}

bool CSortAlgorithm_Char::Transition( IArgs* pArgs )
{
	Args_ItemList* p = NULL;
	if ( p = dynamic_cast<Args_ItemList*>(pArgs) )
	{
		IItemList* pList = p->m_pList;
		if ( pList == NULL )
		{
			return false;
		}
		int nItemCounts = pList->GetItemCount();
//		Qsort( pList, 0, nItemCounts - 1 );
	}
	return false;
}

/*---------------------------------------------------------------------
* ��	CLayoutAlgorithm_TPaddView
* ��    �ܣ�TPad�б������㷨
* ����˵��������TPad�б���ʾ
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2012/12/19	v1.0		������		����
----------------------------------------------------------------------*/
bool CLayoutAlgorithm_TPadIPList::Transition( IArgs* pArgs )
{
	Args_ItemList* p = NULL;
	if ( p = dynamic_cast<Args_ItemList*>(pArgs) )
	{
		IItemList* pList = p->m_pList;
		if ( pList == 0 )
		{
			return false;
		}
		int nItemCounts = pList->GetItemCount();
		IBaseItem* pItem = pList->GetItemData();
		if ( pItem == 0 )
		{
			return false;
		}

		CRect rcLast( 0, 0, 0, 0 );
		for ( int i = 0; i < nItemCounts; i++ )
		{
			IItemList* pSubList = pList->GetItemByIndex( i );
			if ( pSubList == 0 )
			{
				continue;
			}
			IBaseItem* pItem = pSubList->GetItemData();
			if ( pItem == 0 )
			{
				continue;
			}
			int nWidht = pItem->GetItemWidth();
			int nHeight = pItem->GetItemHeight();
			
			 
			int nRow = i / 2; //һ��2��Item
			if( i%2 == 0 )
			{   
				if ( 0 == i )
				{    
					nHeight = 52;
					rcLast.SetRect( 0, nHeight*nRow, nWidht, nHeight*nRow   + nHeight );
				}
				else
				{
					rcLast.SetRect( 0, nHeight*nRow+6, nWidht, nHeight*nRow+6 + nHeight );
				}
				
			}
			else
			{
				
				if ( 1 == i )
				{
					nHeight = 52;
					rcLast.SetRect( nWidht, nHeight*nRow, 2*nWidht, nHeight*nRow  + nHeight );
				}
				else
				{
					rcLast.SetRect(nWidht, nHeight*nRow+6, 2*nWidht, nHeight*nRow+6 + nHeight  );
				}
			 
			}
			pItem->SetItemRect( rcLast );
		}
	}

	return false;
}

/*---------------------------------------------------------------------
* ��	CLayoutAlgorithm_NetMngList
* ��    �ܣ������б������㷨
* ����˵�������������б���ʾ
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2013/1/8   	v1.0		ʯ��		����
----------------------------------------------------------------------*/
// bool CLayoutAlgorithm_NetMngList::Transition( IArgs* pArgs )
// {
// 	Args_ItemList* p = NULL;
// 	if ( p = dynamic_cast<Args_ItemList*>(pArgs) )
// 	{
// 		IItemList* pList = p->m_pList;
// 		if ( pList == 0 )
// 		{
// 			return false;
// 		}
// 		int nItemCounts = pList->GetItemCount();
// 		IBaseItem* pItem = pList->GetItemData();
// 		if ( pItem == 0 )
// 		{
// 			return false;
// 		}
// 		
// 		CRect rcLast( 0, 0, 0, 0 );
// 		for ( int i = 0; i < nItemCounts; i++ )
// 		{
// 			IItemList* pSubList = pList->GetItemByIndex( i );
// 			if ( pSubList == 0 )
// 			{
// 				continue;
// 			}
// 			IBaseItem* pItem = pSubList->GetItemData();
// 			if ( pItem == 0 )
// 			{
// 				continue;
// 			}
// 			int nWidth = pItem->GetItemWidth();
// 			int nHeight = pItem->GetItemHeight();
// 			
// 			
// 			int nRow = i / 5; //һ��5��Item
// 			int nCol = i % 5;
// 			if (nCol == 0)
// 			{
// 				rcLast.SetRect( nWidth*nCol, nHeight*nRow, nWidth*(nCol+1), nHeight*nRow   + nHeight );
// 			}
// 			else
// 			{
// 				int nWidthOffSet = 1;
// 				rcLast.SetRect( nWidth*nCol+nWidthOffSet*nCol, nHeight*nRow, 
// 					nWidth*(nCol+1)+nWidthOffSet*nCol, nHeight*nRow+nHeight );
// 			}
// 
// 			pItem->SetItemRect( rcLast );
// 		}
// 	}
// 	
// 	return false;
// }


/*---------------------------------------------------------------------
* ��	CLayoutAlgorithm_MultiColumn
* ��    �ܣ�����ͨ���㷨
* ����˵�������������б���ʾ
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2013/1/16   	v1.0		Ф��Ȼ		  ����
----------------------------------------------------------------------*/
bool CLayoutAlgorithm_MultiColumn::Transition( IArgs* pArgs )
{
    Args_ItemList* p = NULL;
    if ( p = dynamic_cast<Args_ItemList*>(pArgs) )
    {
        IItemList* pList = p->m_pList;
        if ( pList == 0 )
        {
            return false;
        }
        int nItemCounts = pList->GetItemCount();
        IBaseItem* pItem = pList->GetItemData();
        if ( pItem == 0 )
        {
            return false;
        }

        if ( const Data_ListRangeInfo *pRangeInfo = dynamic_cast<const Data_ListRangeInfo*>( pItem->GetUserData() ) ) 
		{     
            TListRangeInfo tRangeInfo = pRangeInfo->m_tRangeInfo;
            CRect rcLast( 0, 0, 0, 0 );

            int nMaxCol = tRangeInfo.nMaxColumn;
            int nFirstLeft = tRangeInfo.nFirstLeft;
            int nVertSpace = tRangeInfo.nVertSpace;
            int nHoriSpace = tRangeInfo.nHoriSpace;
            if ( nMaxCol == 0 )
            {
                return false;
            }

            for ( int i = 0; i < nItemCounts; i++ )
            {
                IItemList* pSubList = pList->GetItemByIndex( i );
                if ( pSubList == 0 )
                {
                    continue;
                }
                IBaseItem* pItem = pSubList->GetItemData();
                if ( pItem == 0 )
                {
                    continue;
                }
                int nWidth = pItem->GetItemWidth();
                int nHeight = pItem->GetItemHeight();
                        
                int nRow = i / nMaxCol; //����
                if( i%nMaxCol == 0 )
                {
                    rcLast.SetRect( nFirstLeft, tRangeInfo.nFirstTop + (nHeight + nVertSpace)*nRow, 
                                    nFirstLeft + nWidth, tRangeInfo.nFirstTop + (nHeight + nVertSpace)*nRow + nHeight );
                }
                else
                {
                    rcLast.SetRect( rcLast.right + nHoriSpace, tRangeInfo.nFirstTop + (nHeight + nVertSpace)*nRow, 
                                    rcLast.right + nHoriSpace + nWidth, tRangeInfo.nFirstTop + (nHeight + nVertSpace)*nRow + nHeight );
                }
           
                pItem->SetItemRect( rcLast );
            }
        }
    }
    
    return false;
}

/*---------------------------------------------------------------------
* ��	����CLayoutAlgorithm_ComboxItem
* ��    �ܣ�combox�б���Ŀ�����㷨
* ����˵����һ����Ŀ��ǰ����ʾ���֣�������ʾ����ͼ�꣬��������
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2013/04/22	v1.0		����ӡ		����
----------------------------------------------------------------------*/
bool CLayoutAlgorithm_ComboxItem::Transition( IArgs* pArgs )
{
	Args_ItemList* p = NULL;
	if ( p = dynamic_cast<Args_ItemList*>(pArgs) )
	{
		IItemList* pList = p->m_pList;
		if ( pList == 0 )
		{
			return false;
		}
		int nItemCounts = pList->GetItemCount();
		IBaseItem* pItem = pList->GetItemData();
		if ( pItem == 0 )
		{
			return false;
		}
		int nParentWidth = pItem->GetItemWidth();
		int nParentHeight = pItem->GetItemHeight();
		CRect rcLast( 0, 0, 0, 0 );
		
		for ( int i = 0; i < nItemCounts; i++ )
		{
			IItemList* pSubList = pList->GetItemByIndex( i );
			if ( pSubList == 0 )
			{
				continue;
			}
			IBaseItem* pItem = pSubList->GetItemData();
			if ( pItem == 0 )
			{
				continue;
			}
			CRect rc = pItem->GetItemRect();
			int nWidth = pItem->GetItemWidth();
			int nHeight = pItem->GetItemHeight();
			//��һ��Ĭ��ΪTextItem������ΪImageItem
			if ( i == 0 ) 
			{	
				if ( nItemCounts > 1 )
				{
					rcLast.SetRect( 9, 0, nParentWidth - 65, nParentHeight );
				}
				else
				{
					rcLast.SetRect( 9, 0, nParentWidth - 5, nParentHeight );
				}			
				pItem->SetItemRect( rcLast );
			}
			else if ( i == 1 )
			{
				int nLeft = nParentWidth - 10 - nWidth;
				int nTop = nParentHeight/2 - nHeight/2;
				rcLast.SetRect( nLeft, nTop, nLeft + nWidth, nTop + nHeight );
				pItem->SetItemRect( rcLast );
			}	
			else
			{
				int nLeft = rcLast.left - nWidth - 2;
				int nTop = nParentHeight/2 - nHeight/2;
				rcLast.SetRect( nLeft, nTop, nLeft + nWidth, nTop + nHeight );
				pItem->SetItemRect( rcLast );
			}
		}
	}
	return false;
}

/*---------------------------------------------------------------------
* ��	����CLayoutAlgorithm_FileManagerItem
* ��    �ܣ��ļ������б���Ŀ�����㷨
* ����˵����һ����Ŀ��ǰ����ʾ���֣�������ʾ����ͼ�꣬��������
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2013/10/22	v1.0		��ӨӨ		����
----------------------------------------------------------------------*/
bool CLayoutAlgorithm_FileManagerItem::Transition( IArgs* pArgs )
{
	Args_ItemList* p = NULL;
	if ( p = dynamic_cast<Args_ItemList*>(pArgs) )
	{
		IItemList* pList = p->m_pList;
		if ( pList == 0 )
		{
			return false;
		}
		int nItemCounts = pList->GetItemCount();
		IBaseItem* pItem = pList->GetItemData();
		if ( pItem == 0 )
		{
			return false;
		}
		int nParentWidth = pItem->GetItemWidth();
				
		CRect rcLast( 0, 0, 0, 0 );
		for ( int i = 0; i < nItemCounts; i++ )
		{
			IItemList* pSubList = pList->GetItemByIndex( i );
			if ( pSubList == 0 )
			{
				continue;
			}
			IBaseItem* pItem = pSubList->GetItemData();
			if ( pItem == 0 )
			{
				continue;
			}
			int nWidht = pItem->GetItemWidth();
			int nHeight = pItem->GetItemHeight();

		    if( i == 0 )
		    {
			    rcLast.SetRect( 0, 34, nWidht, 34 + nHeight );
		    }
		    else
		    {
			    rcLast.SetRect( rcLast.right + 20, 0, nParentWidth, nHeight );
		    }

			pItem->SetItemRect( rcLast );
		}
	}
    return false;
}

/*---------------------------------------------------------------------
* ��	����CLayoutAlgorithm_PreTextBottom
* ��    �ܣ�����λ��ͼƬ�ײ������㷨
* ����˵��������Ԥ��λ�б����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2015/01/28	v1.0		���`�`		����
----------------------------------------------------------------------*/
bool CLayoutAlgorithm_PreTextBottom::Transition( IArgs* pArgs )
{
	Args_ItemList* p = NULL;
	if ( p = dynamic_cast<Args_ItemList*>(pArgs) )
	{
		IItemList* pList = p->m_pList;
		if ( pList == 0 )
		{
			return false;
		}
		int nItemCounts = pList->GetItemCount();
		IBaseItem* pItem = pList->GetItemData();
		if ( pItem == 0 )
		{
			return false;
		}
		int nParentWidth = pItem->GetItemWidth();
		int nParentHeight = pItem->GetItemHeight();
		CRect rcLast( 0, 0, 0, 0 );		
		for ( int i = 0; i < nItemCounts; i++ )
		{
			IItemList* pSubList = pList->GetItemByIndex( i );
			if ( pSubList == 0 )
			{
				continue;
			}
			IBaseItem* pItem = pSubList->GetItemData();
			if ( pItem == 0 )
			{
				continue;
			}
			int nWidth = pItem->GetItemWidth();
			int nHeight = pItem->GetItemHeight();
			if ( i == 0 )
			{
				rcLast.SetRect( 18, 20, 18 + nWidth, 20 + nHeight );
			}
			else
			{
				rcLast.SetRect( 18, 196, nParentWidth - 18, nParentHeight - 20 );
			}
			
			pItem->SetItemRect( rcLast );
		}
	}
	return false;
}