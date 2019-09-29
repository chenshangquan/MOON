
#ifndef IBASEITEM_HEAD_H
#define IBASEITEM_HEAD_H
#include "iAlgorithm.h"
#include "uiexBaseData.h"


enum EmItemStatus
{    
	emItemStatusNormal = 0,
		emItemStatusSel,
		emItemStatusDown,
		emItemStatusOver,
		emItemStatusDisable   
};


class IBaseItem  
{
public:
	static const String strDefaultFunc;
	
	const static String strNormalImg;
	const static String strDownImg;
	const static String strDisableImg;
	const static String strOverImg;
    const static String strSelImg;
public:
	IBaseItem( int nWidht, int nHeight, String strFunc = IBaseItem::strDefaultFunc,
		String emLayout = IAlgorithm::strHori, String emSort = IAlgorithm::strDefaultAlg, 
		bool bCanDrag = false, bool bCanMove = false, CPoint ptOffset = CPoint(0,0), EmItemStatus emItemStatus = emItemStatusNormal, bool bAlwaysShow = true );

	IBaseItem(const IBaseItem& item);
	virtual ~IBaseItem();
 
public:
/**  ������Ŀ
 *  @param[in] pArgs ���Ʋ��� 
 *  @return 
 */
	virtual void Draw( IArgs* pArgs ) = 0;
/**  ��Ŀ��¡
 *  @return ��¡�����Ŀ
 */
	virtual IBaseItem* Clone() = 0;	

/*
 * ��Ŀ��һЩ���Ի�ȡ\n 
 */
	CRect GetItemRect(){ return m_rcItem; }
	void SetItemRect(CRect rc){ m_rcItem = rc; }
	int GetItemHeight(){ return m_rcItem.Height(); }
	int GetItemWidth(){ return m_rcItem.Width(); }

/*
 * ��Ŀ�Ƿ񱻵���\n 
 */
	bool IsClick( CPoint ptMouse )
	{
		return m_rcItem.PtInRect( ptMouse );
	}
	virtual void SetItemStatus( EmItemStatus emStatus = emItemStatusNormal ){ m_emItemStatus = emStatus; }
	EmItemStatus GetItemStatus(){ return m_emItemStatus; }

/**  ��Ŀ�󶨵��¼�ִ��
 *  @return 
 */
	bool ExeFunc();
	String GetFunc(){ return m_strFunc; }
	void SetFunc( String strFunc ){ m_strFunc = strFunc; }

/*
 * ���úͻ�ȡ�û�����\n 
 */
	void SetUserData( IData* pData );
	const IData* GetUserData();

/*
 * Item�������¼�\n 
 */
	virtual void Click(){};
    virtual void SetImageFolder( String strFolder ) {}

    virtual void OnItemDown(){ SetItemStatus( emItemStatusDown ); }
    virtual void OnItemUp( CPoint point ){ }

/*
 * ����ImageItem��ͼƬȫ·�� 
 */
	virtual void SetImagePath( String strImagePath ) {};
protected:
	CRect m_rcItem;
	String m_strFunc;
	EmItemStatus m_emItemStatus;
	IData* m_pData;// ��ʱ����ı���

public:
	void SetLayoutAlgorithm( String strType ){ m_strLayoutAlgorithm = strType; }
	String GetLayoutAlgorithm(){ return m_strLayoutAlgorithm; }
	void SetSortAlgorithm( String strType ){ m_strSortAlgorithm = strType; }
 	String GetSortAlgorithm(){ return m_strSortAlgorithm; }

	CPoint GetOffset(){ return m_ptOffset; }
	void SetOffset( CPoint pt ){ m_ptOffset = pt; }
	bool GetDragStatus(){ return m_bCanDrag; }
 	void SetDragStatus( bool bDrag ){ m_bCanDrag = bDrag; }
	bool GetMoveStatus(){ return m_bCanMove; }
	void SetMoveStatus( bool bMove ){ m_bCanMove = bMove; }
	bool IsAlwaysShow(){ return m_bAlwaysShow; }
	void SetAlwaysShow( bool bShow ){ m_bAlwaysShow = bShow; } 
protected:
	/*
 * �����㷨 ��ʾ���Item�ڲ���Ŀ�Ĳ����㷨\n 
 */
	String m_strLayoutAlgorithm;
/*
 * �����㷨 ��ʾ���Item�ڲ���Ŀ�������㷨\n 
 */
	String m_strSortAlgorithm;
/*
 * ƫ�Ƶ� ��ʾ���Item������Ŀ��ƫ�ƣ����������\n 
 */
	CPoint m_ptOffset;
/*
 * �Ƿ���ק\n 
 */
	bool m_bCanDrag;
/*
 * �Ƿ��ƶ�\n 
 */
	bool m_bCanMove;
/*
 * �Ƿ�һֱ��ʾ��falseʱ����Ŀѡ�в���ʾ\n 
 */
	bool m_bAlwaysShow;
};

typedef IItem<IBaseItem,int> IItemList;
//���Item��ķ��ز���
class Args_ClickItemInfo : public IArgs
{
public:
    
    Args_ClickItemInfo( CWnd* pSrcWnd, IItemList* pList, CRect rcFrame ) : IArgs( "ClickItemInfo" ), m_pSrcWnd( pSrcWnd ),m_pClickList( pList ), m_rcFrame( rcFrame ){}
    CWnd* m_pSrcWnd;
    IItemList* m_pClickList;
    CRect m_rcFrame;
};

#endif