 #include "stdafx.h"
 #include "popdlg.h"

#define LIST_ADDR			_T("listAddr")
#define LIST_SEL_ADDR       _T("listSelAddr")

//控件类消息
BEGIN_CONTROL_MSG_MAP(CPopDlg)
	CTRL_MSG( DUI_MSGTYPE_CLICK, _T("btnclose"), OnBtnClose)
	CTRL_MSG( DUI_MSGTYPE_CLICK, _T("btntest"), OnBtnTest)
	CTRL_MSG( DUI_MSGTYPE_ITEMCLICK, LIST_ADDR, OnAddrListItemClick )
	CTRL_MSG( DUI_MSGTYPE_ITEMCLICKICON, LIST_ADDR, OnAddrListItemClickIcon )
	CTRL_MSG( DUI_MSGTYPE_DRAG_END, LIST_ADDR, OnDragEnd )
END_CONTROL_MSG_MAP()

//业务类消息
BEGIN_BUSINESS_MSG_MAP(CPopDlg)
	BUSI_MSG( 1000, OnMsgNotify )
END_BUSINESS_MSG_MAP()

CPopDlg::CPopDlg() : CMsgHandler()
{
	m_nSelAddr = -1;
	m_pAddrList = NULL;
	m_pSelAddrList = NULL;
}


CPopDlg::~CPopDlg(void)
{
}
 
void CPopDlg::OnBtnClose(  TNotifyUI& tMsg )
{
	UI_PTR->GetDUIDialogPtr(DLG_POPTEST)->EndModal( 0 );
}

void CPopDlg::OnBtnTest(TNotifyUI& tMsg)
{
	MESSAGEWND(L"测试！");
}

void CPopDlg::OnAddrListItemClick(TNotifyUI& tMsg)
{
	if ( UI_PTR->GetListIndex( LIST_ADDR, tMsg.pSender, UI_PTR->GetPaintMngUI(DLG_POPTEST) ) != -1 )
	{
		if ( _tcsicmp(tMsg.pSender->GetClass(), _T("ListContainerElementUI")) == 0 )
		{
			Node* pNode = (Node*)tMsg.pSender->GetTag();
			if ( NULL != pNode )
			{
				const Data_AddrList* pData = dynamic_cast<const Data_AddrList*>( pNode->GetUserData() );
				Data_AddrList* pItemData = const_cast<Data_AddrList*>(pData);
				if ( NULL != pItemData )
				{	
					m_nSelAddr = pItemData->GetDataKey();	
				}
			}
		}
	}
}

void CPopDlg::OnAddrListItemClickIcon(TNotifyUI& tMsg)
{
	int nSelAddrIndex = (int)tMsg.wParam;
	bool bSelState = (bool)tMsg.lParam;

	if ( _tcsicmp(tMsg.pSender->GetClass(), _T("ListContainerElementUI")) == 0 )
	{
		//得到列表项的数据
		Node* pNode = (Node*)tMsg.pSender->GetTag();
		if ( NULL != pNode )
		{
			const Data_AddrList* pData = dynamic_cast<const Data_AddrList*>( pNode->GetUserData() );
			Data_AddrList* pItemData = const_cast<Data_AddrList*>(pData);
			if ( NULL != pItemData )
			{	
				CStdDataArray<IData*>* parr = NULL;
				m_pSelAddrList->GetListData(&parr);

				CStdDataArray<IData*> vctSelectList = *parr;
				if ( bSelState )
				{
					vctSelectList.AddAtAnd( pItemData );
				}
				else
				{
					vctSelectList.Remove( vctSelectList.FindByData(pItemData) );
				}

				UI_PTR->UpdateList( LIST_SEL_ADDR, vctSelectList, UI_PTR->GetPaintMngUI(DLG_POPTEST) );
			}
		}
	}
}

void CPopDlg::OnDragEnd(TNotifyUI& tMsg)
{
	int nSelAddrIndex = (int)tMsg.wParam;
}
 
 LRESULT CPopDlg::OnMsgNotify( WPARAM wparam, LPARAM lparam )
 {
 	return 0;
 }
 
 void CPopDlg::InitWnd()
 {
	 //REG_LOGIC( PTR_DLG_POPTEST, GetClassName() ); 

	 m_pAddrList = static_cast<CCommonListUI*>(UI_PTR->GetPaintMngUI(DLG_POPTEST).FindControl(LIST_ADDR));
	 m_pSelAddrList = static_cast<CCommonListUI*>(UI_PTR->GetPaintMngUI(DLG_POPTEST).FindControl(LIST_SEL_ADDR));
	 if ( NULL != m_pAddrList )
	 {
		 m_pAddrList->SetDragListCtrlWnd( m_pSelAddrList );
	 }

	 UpdateAddrList();
 }

 void CPopDlg::UpdateAddrList()
 {
	 CStdDataArray<IData*> vctShowList;
	 TAddrListItemInfo item;
	 WCHAR chIndex[4];
	 for( int nIndex = 0; nIndex < 25; nIndex++ )
	 {
		 wsprintf( chIndex, L"%d", nIndex + 1);
		 item.strKey = chIndex;
		 item.strAddrName = _T("文件");
		 item.strAddrName += chIndex;
		 item.strAddrNum = _T("123456");

		 vctShowList.AddAtAnd(Data_AddrList(item).Clone());
	 }

	 UI_PTR->UpdateList( LIST_ADDR, vctShowList, UI_PTR->GetPaintMngUI(DLG_POPTEST) );
 }
