
#ifndef ILIST_HEAD_H
#define ILIST_HEAD_H
#include "iBaseItem.h"
class IList  
{
	typedef IItem< IBaseItem, int > IItemList;
public:
	IList( int nWidht, int nHeight, String emLayout = IAlgorithm::strVert, String emSort = IAlgorithm::strCharacter, bool bShowSubItemAlways = TRUE );
	virtual ~IList();

public:
/**  ������Ŀ�������������Ŀ�Ļ��ƺ���
 *  @param[in] pArgs ���Ʋ�����һ�����һ��graphics 
 *  @return
 */
	virtual void Draw( IArgs* pArgs, int nYOffset, int nHeight );
/**  ����Ŀ���в���
 *  @param[in] ����Ŀ���в���
 *  @return 
 */
	void LayoutItem( IItemList* pList = 0 );

/**  ������Ŀ
 *  @param[in] ����Ŀ��������
 *  @return 
 */
	void SortItem( IItemList* pList = 0 );

/**  �ж϶�Ӧ�б�����˭�������
 *  @param[in] pList���ڵ�
 *  @param[in] point���� ���ݲ�ͬ��Σ��ᱻת��Ϊ���Բ������
 *  @param[out] item �����������Ŀ
 *  @return �Ƿ񱻵��
 */
	bool IsClick( IItemList* pList, CPoint point, IItemList** item ,BOOL bSetSel = FALSE );

/**  ���һ����Ŀ
 *  @param[in] pItem ��Ŀ
 *  @param[in] pParent ���ڵ� Ϊ�վͱ����ӵ����ڵ�
 *  @param[in] emLayoutAlgorithmType���ֵ��㷨��emSortAlgorithmType ������㷨
 *  @return ��Ӻ�Ľڵ�
 */
	IItemList* AddItem( IBaseItem* pItem, IItemList* pParent = 0 );
/**  ���һ����Ŀ
 *  @param[in] pList ��Ŀ�б�
 *  @param[in] pParent ���ڵ� Ϊ�վͱ����ӵ����ڵ�
 *  @return �Ƿ�ɹ�
 */
	bool AddItem( IItemList* pList, IItemList* pParent = 0 );


	IItemList* AddItem( int nIndex, IBaseItem* pItem, IItemList* pParent /* = 0 */ );

/**  ��������ɾ��һ����Ŀ
 *  @param[in] nIndex ����
 *  @param[in] pParent ���ڵ� Ϊ�վͱ����Ǹ��ڵ�
 *  @return �Ƿ�ɹ�
 */
	bool DeleteItem( int nIndex, IItemList* pParent = 0 );

/**  ��ø��ڵ�
 *  @return ���ڵ�
 */
	IItemList* GetRoot(){ return m_pItemList; }
/**  ����һ����Ŀ������ݹ飩
 *  @param[in] pItem ��Ŀ��Ӧ������
 *  @param[in] pParent ���ڵ� Ϊ�վͱ����Ǹ��ڵ�
 *  @return �ҵ�����Ŀ
 */
	IItemList* GetItem( IBaseItem* pItem, IItemList* pParent = 0 );

/**  ���һ���б������С��ֻ����ʵ����Ŀ��������Ĵ�С���������б����Item�м�϶���򲻰�������
 *  @param[in] pList ��Ҫ���ҵĽڵ㣬���Ϊ��������Ǹ��ڵ�
 *  @return �б��С
 */
	CRect GetFrame( IItemList* pList = 0 );

	void SetListSize( unsigned int nWidht, unsigned int nHeight, IItemList* pList = 0 );

	bool SetLayoutAlgroithm( String strAlgorithm, IItemList* pItem = 0 );
	String GetLayoutAlgroithm( IItemList* pItem = 0 );

	bool SetSortAlgroithm( String strAlgorithm, IItemList* pItem = 0 );
	String GetSortAlgroithm( IItemList* pItem = 0 );

	void ShowItemAlways( bool bShow ){ m_bShowSubItemAlways = bShow; }
	bool IsShowItemAlways(){ return m_bShowSubItemAlways; }

	//�Ƿ�ÿ����Ŀ�Ĵ�С��һ��  
	void SetItemSizeSame( bool bItemSizeSame = true ){ m_bItemSizeSame = bItemSizeSame; }

/**  
 *  @param[in] 
 *  @param[in] 
 *  @param[out] 
 *  @return �Ƿ�ɹ�
 */
	protected:
/**  ��Ŀ����һ������ϵת��������һ������ϵ
 *  @param[in] ptSrcCoordinate ԭ������ϵԭ�� �������Ͻ�
 *  @param[in] ptDesCoordinate Ŀ������ϵԭ�� �������Ͻ�
 *  @param[in] point ��Ҫת���ĵ�
 *  @return ת����ĵ�
 */
	CPoint TransPoint( CPoint& ptSrcCoordinate, CPoint& ptDesCoordinate, CPoint& point );

	//���Ƶ�һ��Item,ֻ������Ҫ�Ĳ���
	void DrawItem( IItemList* pItemList, IArgs* pArgs, int nYOffset, int nHeight );
	// ���漸�������������ݹ�
	void DrawSubItem( IItemList* pItemList, IArgs* pArgs );
	void Trasition( IItemList* pItemList );
	void Layout( IItemList* pItemList );
	void Sort( IItemList* pItemList );	

	void LayoutByIndex( int nIndex, IItemList* pItemList );

/*
 * ���ڵ�\n 
 */
	IItemList* m_pItemList;
/*
 * ����\n 
 */
	int m_nIndex;
/*
 * �Ƿ���ݸ���Ŀ״̬��ʾ����\n 
 */
	bool m_bShowSubItemAlways;

	int  m_nShowItemIndex;  //��ʾ�����ĵ�һ��item��index
	int  m_nShowItemNum;    //��ʾ������item������
	bool m_bItemSizeSame;   //�Ƿ�ÿ��item�Ĵ�С��һ��,Ĭ��Ϊtrue��2012-7-11 by yjj ���ٻ�ȡ�б��С�ļ�����
};

#endif