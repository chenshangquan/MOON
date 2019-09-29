/*****************************************************************************
ģ����      : CommonListUI
�ļ���      : CommonListUI.h
����ļ�    : 
�ļ�ʵ�ֹ���: ͨ���б�ؼ�
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
˵��		: �������������ļ��б�֧�ֽ���Ŀ¼�����¼��б�
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/5/1      1.0         ����ӡ      ����
******************************************************************************/
#ifndef COMMONFILELIST_H
#define COMMONFILELIST_H

class UILIB_API CCommonListUI : public CListUI
{
public:
	enum {SCROLL_TIMERID = 10};

	CCommonListUI();
	~CCommonListUI();

public:
	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);
	/*****************************************************************************
	* ����:			��ӽ������
	* @param		[in]	const IData& item    ������� 
	* @param		[in]	Node* parent         ������ָ�� 
	* @return		�� 
	* @remarks		֧�ֶ�����������չ���������ӦTransData
	-----------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��         �汾        �޸���      �޸�����
	2013/5/1       1.0         ����ӡ      ����
    ******************************************************************************/
	Node* AddNode(const IData& item, Node* pParent = NULL);

	bool CanExpand(Node* pNode) const;

	void SetMainFrameWnd(RECT rcRect);


		 /*****************************************************************************
	* ����:			����/��ȡĿ����ק���ڣ�ʵ�ֶ��б��㻥�ӣ�Ŀǰ֧��˫�б����ʵ�ֶ��б���Ҫ��չע�ᴰ��
	* @param		��
	* @return		�� 
	* @remarks		��
	-----------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��         �汾        �޸���      �޸�����
	2013/5/3       1.0         ����ӡ      ����
    ******************************************************************************/
	CCommonListUI* GetDragListCtrlWnd(){return m_pListDragWnd;};
	void SetDragListCtrlWnd(CCommonListUI* pListDragWnd){ m_pListDragWnd = pListDragWnd;};

	/*****************************************************************************
	* ����:			�����б�����
	* @param		[in]	std::vector<IData*>& vecData    �б����ݼ� 
	* @return		�� 
	* @remarks		��
	-----------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��         �汾        �޸���      �޸�����
	2013/7/22      1.0         ����ӡ      ����
    ******************************************************************************/
	void UpdateList(std::vector<IData*>& vecData);	

	void UpdateList(CStdDataArray<IData*>& vecData);

	void SetManagerUI(CPaintManagerUI* pManageUI){ m_pManageUI = pManageUI;};

	bool SetCheckStateMap(int nKey, bool bSelState);
	void GetCheckStateMap(CStdDataList<bool>** pListCheckState){ *pListCheckState = m_pListCheckState; };

	tString GetProgressName(){return m_strProgressName;};

	void SetListData(CStdDataArray<IData*>& aryListData);
	void GetListData(CStdDataArray<IData*>** paryListData){ *paryListData = m_paryListData; };

private:
	//bool Add(CControlUI* pControl); 
	//bool AddAt(CControlUI* pControl, int iIndex);
	bool AddAtEnd( CControlUI* pItemList, Node* pParent );
	bool AddAt( CControlUI* pControl, Node* pParent );
	bool RemoveAt(int iIndex);
	//bool Remove(CControlUI* pControl);
	//bool RemoveAt(int iIndex);
	void RemoveAll();
	
	void DoEvent(TEventUI& event);
	Node* GetRoot();

	void ResetNodeRoot();


	 /*****************************************************************************
	* ����:			ɾ���������
	* @param		[in]	const IData& item    ������� 
	* @return		�� 
	* @remarks		��
	-----------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��         �汾        �޸���      �޸�����
	2013/5/1       1.0         ����ӡ      ����
    ******************************************************************************/
	void RemoveNode(Node* pNode);

	 /*****************************************************************************
	* ����:			ѡ��ָ����
	* @param		[in]	int iIndex   ��ѡ���к�
	* @return		�� 
	* @remarks		��
	-----------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��         �汾        �޸���      �޸�����
	2013/5/1       1.0         ����ӡ      ����
    ******************************************************************************/
	bool SelectItem(int iIndex);

	 /*****************************************************************************
	* ����:			�����б�����
	* @param		[in]	LPCTSTR pstrName	����name
	* @param		[in]	LPCTSTR pstrValue	����value
	* @return		�� 
	* @remarks		��
	-----------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��         �汾        �޸���      �޸�����
	2013/5/1       1.0         ����ӡ      ����
    ******************************************************************************/
	void SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue );

	 /*****************************************************************************
	* ����:			����/��ȡ��ǰѡ�н��
	* @param		[in]	Node* pNodeSelItem   ѡ��Node
	* @return		�� 
	* @remarks		��
	-----------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��         �汾        �޸���      �޸�����
	2013/5/1       1.0         ����ӡ      ����
    ******************************************************************************/
	void SetSelectItemNode(Node* pNodeSelItem){ m_pNodeSelItem = pNodeSelItem;};
	Node* GetSelectItemNode(){ return m_pNodeSelItem;};


	 /*****************************************************************************
	* ����:			��ʽһ�������б�����(XML��ʽ)
	* @param		[in]	const Data_FileList &data   �ļ��б������� 
	* @param		[in]	Node* parent				������ָ�� 
	* @return		�� 
	* @remarks		��Բ�ͬ�б�����ͬ�����ݹ���
	-----------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��         �汾        �޸���      �޸�����
	2013/5/3       1.0         ����ӡ      ����
    ******************************************************************************/
	Node* DrawItemEx( const Data_FileList* pData, Node* pParent );
	Node* DrawItemEx( const Data_ConfList* pData, Node* pParent );
	Node* DrawItemEx( const Data_AddrList* pData, Node* pParent );     //by xhx

	CListContainerElementUI* CreateElement();
	void SetContainerVisible( CControlUI* pItemList, const tString& strWndName, bool bVisible = false );
	CButtonUI* SetButtonNode( CControlUI* pItemList, const tString& strWndName, bool (*pFn)(void*) );
	CLabelUI* SetLabelNode( CControlUI* pItemList, const tString& strWndName, const tString& strText, bool bShowHtml = false );
	CProgressUI* SetProgressNode( CControlUI* pItemList, const tString& strWndName, int nValue = 0, bool bShowHtml = false );
	//nIndex->��ţ�bSelState->�Ƿ�Ϊ��ѡ״̬��bIsActivate->�Ƿ���Ӧclick��Ϣ  by xhx
	CListIconUI* SetClickLabelNode( CControlUI* pItemList, const tString& strWndName, int nIndex = -1,
		bool bSelState = false, const tString& strItemName = _T(""), Node* pItemNode = NULL );


	 /*****************************************************************************
	* ����:			��ʽ���������б�����(��̬���� ��Ŀ �����)
	* @param		[in]	const Data_DynamicList &data   ��̬�б������� 
	* @param		[in]	Node* parent				   ������ָ�� 
	* @return		�� 
	* @remarks		��Բ�ͬ�б�����ͬ�����ݹ���
	-----------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��         �汾        �޸���      �޸�����
	2013/5/3       1.0         ����ӡ      ����
    ******************************************************************************/
	Node* DrawItem( const Data_DynamicList* pData, Node* pParent );
	Node* DrawItem( const Data_BoardList* pData, Node* pParent );
	Node* DrawItem( const Data_TvwStyleList* pData, Node* pParent );

	CListContainerElementUI* CreateElement( const tString& strHeight, const tString& strWidth = L"" );
	CLabelUI* CreateLabel(const TItemNodeUI& tItemNodeUI);
	CTextUI* CreateText(const TItemNodeUI& tItemNodeUI);
	CButtonUI* CreateButton(const TItemNodeUI& tItemNodeUI);
	CProgressUI* CreateProgress(const TItemNodeUI& tItemNodeUI);

	BOOL RemoveVirtualItem();      //ɾ���Ѳ���������б���
	void ShowVirtualItemData();    //��ʾ�����б���

	void SetVirtualItemPos( int nIndex ){ m_nVirtualItemPos = nIndex; };
	int GetVirtualItemPos(){ return m_nVirtualItemPos; };

	void SetVirtualItemShow( BOOL bShowVirtualItem ){ m_bShowVirtualItem = bShowVirtualItem; };
	BOOL IsVirtualItemShow(){ return m_bShowVirtualItem; };

	BOOL DragEnd();					//��ק����ͬʱ�����б�����

private:
	Node*	m_pNodeRoot;
	LONG	m_delayDeltaY;
	DWORD	m_delayNumber;
	DWORD	m_delayLeft;
	CRect	m_rcTextPadding;
	int m_nLevelTextStartPos;

	tString m_strLevelExpandImg;
	tString m_strLevelCollapseImg;

	tString m_strProgressName;

	int m_nListItemHeight;				//ITEM�߶�
	int m_nListItemSelHeight;			//ITEMѡ�и߶�
	int m_nListItemSelBkPos;            //ITEMѡ�б���λ��

	CListUIDragWnd* m_wndListUIDrag;    //�б���ק����

	BOOL m_bLButtonDown;
	POINT m_ptLButtonDown;				//��갴��λ��
	BOOL m_bTimer;
	CRect m_rcPaintWindow;

	BOOL m_bDrag;

	CCommonListUI* m_pListDragWnd;
	Node* m_pNodeSelItem;				//��ǰѡ�е���������Ϣ
	HWND m_hWndMain;

	tString m_strStyle;

	CDialogBuilder m_dlgBuilder;

	CPaintManagerUI* m_pManageUI;

	CStdDataList<bool>* m_pListCheckState;
	CStdDataArray<IData*>* m_paryListData;

	int m_nVirtualItemPos;             //�����б����λ��
	BOOL m_bShowVirtualItem;           //�����б����Ƿ�����ʾ
};

#define ADD_NODE_VALUE( name, item, parent ) \
	if( L###name == item.GetType() ) { \
	if ( const name* pData = dynamic_cast<const name*>( &item ) )	\
{	\
	if ( NULL != pData )	\
	{	\
	return DrawItem( pData, parent );	\
}	\
}	\
}

#define ADD_NODE_VALUE_EX( name, item, parent ) \
if( L###name == item.GetType() ) { \
if ( const name* pData = dynamic_cast<const name*>( &item ) )	\
{	\
	if ( NULL != pData )	\
	{	\
	return DrawItemEx( pData, parent );	\
}	\
}	\
}


#endif // COMMONFILELIST_H