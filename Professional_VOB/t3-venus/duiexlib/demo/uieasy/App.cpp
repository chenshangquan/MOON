// App.cpp : Defines the entry point for the application.
//
#include "stdafx.h"
#include "App.h"
#include "popdlg.h"

//控件类消息
BEGIN_CONTROL_MSG_MAP(CFrameWnd)
	CTRL_MSG( DUI_MSGTYPE_CLICK, BTN_FILELISTCHILD, OnBtnFileListChildClick )
	CTRL_MSG( DUI_MSGTYPE_ITEMDBCLICK, LIST_FILE, OnFileListItemClick )
	CTRL_MSG( DUI_MSGTYPE_ITEMDBCLICK, LIST_FILE_RIGHT, OnRFileListItemClick )
	CTRL_MSG( DUI_MSGTYPE_CLICK, BTN_POP_DLG, OnBtnPopDlg )
END_CONTROL_MSG_MAP()

//业务类消息
BEGIN_BUSINESS_MSG_MAP(CFrameWnd)
	BUSI_MSG( 1000, OnMsgNotify )
END_BUSINESS_MSG_MAP()

static UINT_PTR g_nTimer;
static int g_nProgress;
void CALLBACK TimerProc( HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime )
{
 	g_nProgress = g_nProgress + 5;
// 	PTR_DLG_UIFRAME->InitDownLeftDynamicList();
//	UI_PTR->UpdateListProgress( LIST_CONF, 3, g_nProgress, UI_PTR->GetPaintMngUI(DLG_UIFRAME) );

	std::vector<IData*> vctProgList;
	TProgressInfo item;
	for( int nIndex = 0; nIndex < 3; nIndex++ )
	{
		item.nIndex = nIndex;
		item.nValue = g_nProgress;

		vctProgList.push_back( Data_ProgressInfo(item).Clone() );
	}

	UI_PTR->UpdateList( LIST_CONF, vctProgList, UI_PTR->GetPaintMngUI(DLG_UIFRAME) );

	if ( 100 == g_nProgress )
	{
		bool bRet = KillTimer( NULL, g_nTimer);
	}
}

CFrameWnd::CFrameWnd() : CMsgHandler()
{
}

CFrameWnd::~CFrameWnd(void)
{
}

void CFrameWnd::InitWnd()
{
	//初始化预览图片窗口
	CommonScrollContainerUI* pScrollContainerUI = 
		static_cast<CommonScrollContainerUI*>(UI_PTR->GetPaintMngUI(DLG_UIFRAME).FindControl(_T("preimgctui")));
	if ( NULL != pScrollContainerUI )
	{
		pScrollContainerUI->SetImage(L"drawimage.jpg");
	}

	//初始化列表
	InitListUI();
	InitFileList();
	InitRightFileList();
	InitConfList();
	InitDownLeftDynamicList();
	InitBoardList();
	InitTvwStyleList();
}

void CFrameWnd::OnBtnFileListChildClick(TNotifyUI& tMsg)
{
	MESSAGEWND(L"点击左侧文件列表子按钮");
}


void CFrameWnd::OnFileListItemClick(TNotifyUI& tMsg)
{
	Node* pNode = (Node*)tMsg.pSender->GetTag();
	if ( NULL != m_pFileLeftList )
	{
		if ( m_pFileLeftList->CanExpand(pNode) )
		{
			OpenFileListFolderSub();
		}
	}
}

void CFrameWnd::OnRFileListItemClick(TNotifyUI& tMsg)
{
	MESSAGEWND(L"点击右侧文件列表条目");
}

void CFrameWnd::InitListUI()
{
	m_pFileLeftList = static_cast<CCommonListUI*>(UI_PTR->GetPaintMngUI(DLG_UIFRAME).FindControl(LIST_FILE));
	m_pFileRightList = static_cast<CCommonListUI*>(UI_PTR->GetPaintMngUI(DLG_UIFRAME).FindControl(LIST_FILE_RIGHT));
	if ( NULL != m_pFileLeftList )
	{
		m_pFileLeftList->SetDragListCtrlWnd(m_pFileRightList);
	}
}

void CFrameWnd::InitFileList()
{
	if ( !m_vecFileListInfo.empty() )
	{
		m_vecFileListInfo.clear();
	}

	TFileListItemInfo item;
	WCHAR chIndex[4];
	for( int nIndex = 0; nIndex < 20; nIndex++ )
	{
		wsprintf( chIndex, L"%d", nIndex);
		item.strKey = chIndex;
		item.bFolder = false;
		if ( nIndex % 8 == 0 )
		{
			item.bFolder = true;
			item.strFileName = _T("目录");
			item.strFileName += chIndex;
			item.strPath = _T("");
		}
		else
		{
			item.bFolder = false;
			item.strFileName = _T("文件");
			item.strFileName += chIndex;
			item.strPath = _T("D:/Files/file");
			item.strPath += chIndex;
		}

		m_vecFileListInfo.push_back(Data_FileList(item).Clone());
	}

	UI_PTR->UpdateList( LIST_FILE, m_vecFileListInfo, UI_PTR->GetPaintMngUI(DLG_UIFRAME) );
}

void CFrameWnd::OpenFileListFolderSub()
{
	if ( !m_vecSubFileListInfo.empty() )
	{
		m_vecSubFileListInfo.clear();
	}

	TFileListItemInfo item;
	WCHAR chIndex[4];
	for( int nIndex = 0; nIndex < 100; nIndex++ )
	{
		wsprintf( chIndex, L"%d", nIndex);
		item.strKey = chIndex;
		item.bFolder = false;
		if ( nIndex % 8 == 0 )
		{
			item.bFolder = true;
			item.strFileName = _T("child目录");
			item.strFileName += chIndex;
			item.strPath = _T("");
		}
		else
		{
			item.bFolder = false;
			item.strFileName = _T("child文件");
			item.strFileName += chIndex;
			item.strPath = _T("F:/Fileschild/file");
			item.strPath += chIndex;
		}

		m_vecSubFileListInfo.push_back(Data_FileList(item).Clone());
	}

	UI_PTR->UpdateList( LIST_FILE, m_vecSubFileListInfo, UI_PTR->GetPaintMngUI(DLG_UIFRAME) );
}

void CFrameWnd::InitRightFileList()
{
	if ( !m_vecRightFileListInfo.empty() )
	{
		m_vecRightFileListInfo.clear();
	}

	TFileListItemInfo item;
	WCHAR chIndex[4];
	for( int nIndex = 0; nIndex < 20; nIndex++ )
	{
		wsprintf( chIndex, L"%d", nIndex);
		item.strKey = chIndex;
		item.bFolder = false;
		if ( nIndex % 8 == 0 )
		{
			item.bFolder = true;
			item.strFileName = _T("r_目录");
			item.strFileName += chIndex;
			item.strPath = _T("");
		}
		else
		{
			item.bFolder = false;
			item.strFileName = _T("r_文件");
			item.strFileName += chIndex;
			item.strPath = _T("r_D:/Files/file");
			item.strPath += chIndex;
		}

		m_vecRightFileListInfo.push_back(Data_FileList(item).Clone());
	}

	UI_PTR->UpdateList( LIST_FILE_RIGHT, m_vecRightFileListInfo, UI_PTR->GetPaintMngUI(DLG_UIFRAME) );
}

void CFrameWnd::InitConfList()
{
	if ( !m_vecConfRightListInfo.empty() )
	{
		m_vecConfRightListInfo.clear();
	}

	TConfListItemInfo item;
	WCHAR chIndex[4];
	for( int nIndex = 0; nIndex < 100; nIndex++ )
	{
		wsprintf( chIndex, L"%d", nIndex);
		item.strKey = chIndex;

		item.strConfID = _T("NO");
		item.strConfID += chIndex;

		item.strConfName = _T("我的会议");
		item.strConfName += chIndex;

		item.nProgress = 0;

		m_vecConfRightListInfo.push_back(Data_ConfList(item).Clone());
	}

	UI_PTR->UpdateList( LIST_CONF, m_vecConfRightListInfo, UI_PTR->GetPaintMngUI(DLG_UIFRAME) );

	if ( 0 == g_nProgress )
	{
		g_nTimer = SetTimer( NULL, 1, 1000, TimerProc );
	}
}

void CFrameWnd::InitDownLeftDynamicList()
{
	if ( !m_vecDynamicLeftListInfo.empty() )
	{
		m_vecDynamicLeftListInfo.clear();
	}

	TDynamicListItemInfo item;
	WCHAR chIndex[4];
	for( int nIndex = 0; nIndex < 100; nIndex++ )
	{
		wsprintf( chIndex, L"%d", nIndex);
		item.strKey = chIndex;

		item.strID = _T("NO");
		item.strID += chIndex;

		item.strName = _T("我的动态");
		item.strName += chIndex;

		item.nProgress = 100;//g_nProgress;

		m_vecDynamicLeftListInfo.push_back(Data_DynamicList(item).Clone());
	}

	UI_PTR->UpdateList( LIST_DOWNDYNAMIC, m_vecDynamicLeftListInfo, UI_PTR->GetPaintMngUI(DLG_UIFRAME) );
}

void CFrameWnd::InitBoardList()
{
	if ( !m_vecBoardListInfo.empty() )
	{
		m_vecBoardListInfo.clear();
	}

	TBoardListItemInfo item;
	WCHAR chIndex[4];
	for( int nIndex = 0; nIndex < 2; nIndex++ )
	{
		wsprintf( chIndex, L"%d", nIndex);
		item.strKey = chIndex;

		item.strID = _T("NO");
		item.strID += chIndex;

		item.strName = _T("空板");
		item.strName += chIndex;

		m_vecBoardListInfo.push_back(Data_BoardList(item).Clone());
	}

	UI_PTR->UpdateList( LIST_BOARD, m_vecBoardListInfo, UI_PTR->GetPaintMngUI(DLG_UIFRAME) );
}

void CFrameWnd::InitTvwStyleList()
{
	if ( !m_vecTvwStyleListInfo.empty() )
	{
		m_vecTvwStyleListInfo.clear();
	}

	TTvwStyleListItemInfo item;
	WCHAR chIndex[4];
	for( int nIndex = 0; nIndex < 6; nIndex++ )
	{
		wsprintf( chIndex, L"%d", nIndex);
		item.strKey = chIndex;

		item.strID = _T("NO");
		item.strID += chIndex;

		item.strName = _T("空板");
		item.strName += chIndex;

		m_vecTvwStyleListInfo.push_back(Data_TvwStyleList(item).Clone());
	}

	UI_PTR->UpdateList( LIST_TVWSTYLE, m_vecTvwStyleListInfo, UI_PTR->GetPaintMngUI(DLG_UIFRAME) );
}

void CFrameWnd::OnBtnPopDlg(TNotifyUI& tMsg)
{
	REG_LOGIC( PTR_DLG_POPTEST, PTR_DLG_POPTEST->GetClassName() );
	int n = UI_PTR->GetDUIDialogPtr(DLG_POPTEST)->DoModal();
}

LRESULT CFrameWnd::OnMsgNotify( WPARAM wparam, LPARAM lparam )
{
	return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	CPaintManagerUI::SetInstance( hInstance );
	TCHAR chPath[MAX_PATH] = {0};
	wcscat( chPath, CPaintManagerUI::GetInstancePath() );
	wcscat( chPath, _T("skin\\uieasyres\\") );
	CPaintManagerUI::SetResourcePath( chPath );

	CDlgManager::GetSingletonPtr()->InitDlgMap( XML_DLGMAP );
	REG_LOGIC( PTR_DLG_UIFRAME, PTR_DLG_UIFRAME->GetClassName() ); 

	::ShowWindow( UI_PTR->GetDUIDialogPtr(DLG_UIFRAME)->GetHWND(),SW_SHOW );
	UI_PTR->GetDUIDialogPtr(DLG_UIFRAME)->CenterWindow();

	CPaintManagerUI::MessageLoop();

    return 0;
}
