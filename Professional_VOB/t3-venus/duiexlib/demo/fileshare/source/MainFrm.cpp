#include "stdafx.h"
#include "MainFrm.h"
#include <shlwapi.h>
#pragma comment(lib,"shlwapi.lib")

const TCHAR* const kCloseButtonControlName = _T("closebtn");
const TCHAR* const kMinButtonControlName = _T("minbtn");
const TCHAR* const kMaxButtonControlName = _T("maxbtn");
const TCHAR* const kRestoreButtonControlName = _T("restorebtn");

MainFrame::MainFrame()
{
	m_pTxFilePath = NULL;
	m_pFileList = NULL;

	m_pPreWnd = NULL;
	m_pScrollContainerUI = NULL;

	m_nCurFileIndex = -1;

	m_strFolderPath = L"C:\\预览文件";
}

MainFrame::~MainFrame()
{
	PostQuitMessage(0);
}

LPCTSTR MainFrame::GetWindowClassName() const
{
	return _T("TXGuiFoundation");
}

CControlUI* MainFrame::CreateControl(LPCTSTR pstrClass)
{
	return NULL;
}

void MainFrame::Init()
{
	InitChildDialog();

	m_pTxFilePath = static_cast<CTextUI*>(m_cPaintManager.FindControl(_T("txfilepath")));
}

void MainFrame::InitChildDialog()
{
	m_pScrollContainerUI = static_cast<CommonScrollContainerUI*>(m_cPaintManager.FindControl(_T("preimgctui")));
	if( NULL != m_pScrollContainerUI )												//创建预览窗口
	{
		m_pScrollContainerUI->SetVisible(false);

		m_pPreWnd = new CPreWnd(m_cPaintManager);
		if( NULL != m_pPreWnd )														//创建预览窗口
		{
			m_pPreWnd->SetMainFrameWnd( this->GetHWND() );
			m_pPreWnd->SetScrollContainerUI( m_pScrollContainerUI );
			POINT pt;
			pt.x = 2;
			pt.y = 61;
			m_pPreWnd->MoveWnd(pt);
		}
	}
}

void MainFrame::OnFinalMessage(HWND hWnd)
{
	CBaseWindowWnd::OnFinalMessage(hWnd);
	delete this;
}

const TCHAR* MainFrame::GetSkinFile()
{
	return _T("main.xml");
}

const TCHAR* MainFrame::GetSkinFolder()
{
	TCHAR chPath[MAX_PATH] = {0};
	wcscat( chPath, CPaintManagerUI::GetInstancePath() );
	wcscat( chPath, L"skin\\fileshareres\\" );

	return chPath;
}

LRESULT MainFrame::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;

// 	if( NULL != m_wndListUIDrag )
// 	{
// 		delete m_wndListUIDrag;
// 		m_wndListUIDrag = NULL;
// 	}

	return 0;
}

LRESULT MainFrame::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if defined(WIN32) && !defined(UNDER_CE)
	BOOL bZoomed = ::IsZoomed(m_hWnd);
	LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	if (::IsZoomed(m_hWnd) != bZoomed)
	{
		if (!bZoomed)
		{
			CControlUI* pControl = static_cast<CControlUI*>(m_cPaintManager.FindControl(kMaxButtonControlName));
			if( pControl ) pControl->SetVisible(false);
			pControl = static_cast<CControlUI*>(m_cPaintManager.FindControl(kRestoreButtonControlName));
			if( pControl ) pControl->SetVisible(true);
		}
		else 
		{
			CControlUI* pControl = static_cast<CControlUI*>(m_cPaintManager.FindControl(kMaxButtonControlName));
			if( pControl ) pControl->SetVisible(true);
			pControl = static_cast<CControlUI*>(m_cPaintManager.FindControl(kRestoreButtonControlName));
			if( pControl ) pControl->SetVisible(false);
		}
	}
#else
	return __super::OnSysCommand(uMsg, wParam, lParam, bHandled);
#endif

	return 0;
}

LRESULT MainFrame::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return __super::HandleMessage(uMsg, wParam, lParam);
}

LRESULT MainFrame::ResponseDefaultKeyEvent(WPARAM wParam)
{
	if (wParam == VK_RETURN)
	{
		return FALSE;
	}
	else if (wParam == VK_ESCAPE)
	{
		return TRUE;
	}
	return FALSE;
}

void MainFrame::OnTimer(TNotifyUI& msg)
{
}

void MainFrame::OnExit(TNotifyUI& msg)
{
	Close();
}

DWORD MainFrame::GetBkColor()
{
	return 0;
}

void MainFrame::SetBkColor(DWORD dwBackColor)
{
}

void MainFrame::OnBtnNextPage()
{
	if ( NULL != m_pPreWnd && NULL != m_pScrollContainerUI && m_vecFiles.size() > 0 )
	{
		++m_nCurFileIndex;
		if ( m_nCurFileIndex == m_vecFiles.size() )
		{
			m_nCurFileIndex = 0;
		}

		Data_FileList* pItemData = const_cast<Data_FileList*>(dynamic_cast<Data_FileList*>(m_vecFiles[m_nCurFileIndex]));
		if ( NULL == pItemData )return;

		tString strFullPath;
		strFullPath = pItemData->m_tData.strPath;
		strFullPath += pItemData->m_tData.strFileName;
		m_pPreWnd->ShowPageDown(strFullPath);

		if ( NULL != m_pTxFilePath )						//设置路径控件显示内容
		{
			m_pTxFilePath->SetText(strFullPath.c_str());
		}
	}
}

void MainFrame::OnBtnReturn()
{
	tString strFolderPath;
	size_t szFind = m_strFolderPath.rfind(L"\\");
	if ( std::string::npos != szFind )
	{
		if ( m_strFolderPath.size() -1 == szFind )									//最后一个字符为"\"继续向前找
		{
			m_strFolderPath = m_strFolderPath.substr( 0, m_strFolderPath.size() -1 );
			szFind = m_strFolderPath.rfind(L"\\");
		}

		if ( std::string::npos != szFind )
		{
			strFolderPath = m_strFolderPath.substr( 0, szFind );
		}
	}

	if ( !strFolderPath.empty() )
	{
		m_strFolderPath = strFolderPath;
		EnumerateFolder(m_strFolderPath);
		UpdateFileList();	
	}
}

void MainFrame::OnListItemClick(TNotifyUI& msg)
{
	if ( m_pFileList != NULL )
	{
		if ( m_pFileList->GetItemIndex(msg.pSender) != -1 )				//目前暂时不需要展开
		{
			if ( _tcsicmp(msg.pSender->GetClass(), _T("ListContainerElementUI")) == 0 )
			{
				Node* node = (Node*)msg.pSender->GetTag();

				const Data_FileList* pData = dynamic_cast<const Data_FileList*>( node->GetUserData() );
				Data_FileList* pItemData = const_cast<Data_FileList*>(pData);
				tString strFullPath;
				if ( NULL != pData )
				{	
					m_nCurFileIndex = pItemData->GetDataKey();	
					strFullPath = pItemData->m_tData.strPath;
					strFullPath += pItemData->m_tData.strFileName;
					m_pPreWnd->ShowPageDown(strFullPath);

					if ( NULL != m_pTxFilePath )						//设置路径控件显示内容
					{
						m_pTxFilePath->SetText(strFullPath.c_str());
					}
				}
			}
		}
	}
}

void MainFrame::OnListItemDbClick(TNotifyUI& msg)
{
	if ( m_pFileList != NULL )
	{
		if ( m_pFileList->GetItemIndex(msg.pSender) != -1)			//目前暂时不需要展开
		{
			if ( _tcsicmp(msg.pSender->GetClass(), _T("ListContainerElementUI")) == 0 )
			{
				Node* node = (Node*)msg.pSender->GetTag();

				if ( m_pFileList->CanExpand(node) )
				{
					const Data_FileList* pData = dynamic_cast<const Data_FileList*>( node->GetUserData() );
					Data_FileList* pItemData = const_cast<Data_FileList*>(pData);
					tString strFullPath;
					if ( NULL != pData )
					{	
						strFullPath = pItemData->m_tData.strPath;
						strFullPath += pItemData->m_tData.strFileName;
						m_strFolderPath = strFullPath;
						EnumerateFolder(m_strFolderPath);

						UpdateFileList();
					}
				}
			}
		}
	}
}

void MainFrame::OnPrepare(TNotifyUI& msg)
{
	EnumerateFolder(m_strFolderPath);
	InitListUI();
}

void MainFrame::Notify(TNotifyUI& msg)
{
	if ( _tcsicmp( msg.sType, _T("windowinit") ) == 0)
	{
		OnPrepare(msg);
	}
	else if ( _tcsicmp( msg.sType, DUI_MSGTYPE_CLICK ) == 0)
	{
		if ( _tcsicmp( msg.pSender->GetName().c_str(), kCloseButtonControlName ) == 0)
		{
			OnExit(msg);
		}
		else if ( _tcsicmp( msg.pSender->GetName().c_str(), kMinButtonControlName ) == 0)
		{
#if defined(UNDER_CE)
			::ShowWindow( m_hWnd, SW_MINIMIZE);
#else
			SendMessage( WM_SYSCOMMAND, SC_MINIMIZE, 0 );
#endif
		}
		else if ( _tcsicmp( msg.pSender->GetName().c_str(), kMaxButtonControlName ) == 0)		//最大化及复原
		{
// #if defined(UNDER_CE)
// 			::ShowWindow(m_hWnd, SW_MAXIMIZE);
// 			CControlUI* pControl = static_cast<CControlUI*>(paint_manager_.FindControl(kMaxButtonControlName));
// 			if( pControl ) pControl->SetVisible(false);
// 			pControl = static_cast<CControlUI*>(paint_manager_.FindControl(kRestoreButtonControlName));
// 			if( pControl ) pControl->SetVisible(true);
// #else
// 			SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
// #endif
// 		}
// 		else if (_tcsicmp(msg.pSender->GetName(), kRestoreButtonControlName) == 0)
// 		{
// #if defined(UNDER_CE)
// 			::ShowWindow(m_hWnd, SW_RESTORE);
// 			CControlUI* pControl = static_cast<CControlUI*>(paint_manager_.FindControl(kMaxButtonControlName));
// 			if( pControl ) pControl->SetVisible(true);
// 			pControl = static_cast<CControlUI*>(paint_manager_.FindControl(kRestoreButtonControlName));
// 			if( pControl ) pControl->SetVisible(false);
// #else
// 			SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
// #endif
		}
		else if( _tcsicmp( msg.pSender->GetName().c_str(), L"btnnextpage" ) == 0 ) 
		{
			OnBtnNextPage();
		}
		else if( _tcsicmp( msg.pSender->GetName().c_str(), L"btnfolderret" ) == 0 )				//返回上一级
		{
			OnBtnReturn();														
		}
		else if ( _tcsicmp( msg.pSender->GetName().c_str(), L"btnlisticon") == 0 )
		{
			//MESSAGEWND(L"点击了列表条目中按钮");										//点击列表中的按钮和点击普通按钮一样
		}
	}
	else if ( _tcsicmp(msg.sType, DUI_MSGTYPE_TIMER) == 0 )
	{
		return OnTimer(msg);
	}
	else if ( _tcsicmp(msg.sType, DUI_MSGTYPE_SELECTCHANGED ) == 0 )
	{
	}
	else if ( _tcsicmp(msg.sType, DUI_MSGTYPE_ITEMCLICK ) == 0 )					//itemactivate 单击列表条目
	{
		OnListItemClick(msg);
	}
	else if( _tcsicmp(msg.sType, DUI_MSGTYPE_ITEMDBCLICK) == 0 )					//itemactivate 双击列表条目
	{
		OnListItemDbClick(msg);
	}
}

void MainFrame::EnumerateFolder(const tString& strPath)
{
	if ( strPath.empty() )
	{
		return;
	}

	if ( !::PathFileExists(strPath.c_str()) )
	{
		m_strFolderPath = L"C:";
	}

	tString strFindPath = L"";
	HANDLE hFind = NULL;

	strFindPath = strPath.c_str();
	strFindPath.append(L"\\*.*");

	WIN32_FIND_DATA fd;
	hFind = FindFirstFile(strFindPath.c_str(),&fd);

	m_vecFiles.clear();
	m_nCurFileIndex = -1;

	WCHAR chIndex[4];
	int nCount = 0;
	TFileListItemInfo tFile;
	do
	{
		if (0 == ( wcscmp( L".", fd.cFileName ) ) ||
			0 == ( wcscmp( L"..", fd.cFileName ) ) )
		{
			continue;
		}

		if( 0 == ( fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) )
		{
			tFile.bFolder = false;
		}
		else
		{
			tFile.bFolder = true;
		}

		wsprintf( chIndex, L"%d", nCount );
		tFile.strKey = chIndex;
		++nCount;

		tFile.strFileName = fd.cFileName;
		tFile.strPath = strPath.c_str();
		tFile.strPath += L"\\";

		m_vecFiles.push_back(Data_FileList(tFile).Clone());

	}while( FindNextFile( hFind,&fd ) );
}

LRESULT MainFrame::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

void MainFrame::InitListUI()
{
	m_pFileList = static_cast<CCommonListUI*>(m_cPaintManager.FindControl(LIST_FILESHARELEFT));
	UpdateFileList();
}

void MainFrame::UpdateFileList()
{
	UI_PTR->UpdateList( LIST_FILESHARELEFT, m_vecFiles, m_cPaintManager );
}

#if defined(WIN32) && !defined(UNDER_CE)
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
#else
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpCmdLine, int nCmdShow)
#endif
{
	CPaintManagerUI::SetInstance(hInstance);

	//设置资源路径
	TCHAR chPath[MAX_PATH] = {0};
	wcscat( chPath, CPaintManagerUI::GetInstancePath() );
	wcscat( chPath, _T("skin\\fileshareres\\") );
	CPaintManagerUI::SetResourcePath( chPath );

	::CoInitialize(NULL);
	::OleInitialize(NULL);

#if defined(WIN32) && !defined(UNDER_CE)
	HRESULT Hr = ::CoInitialize(NULL);
#else
	HRESULT Hr = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
#endif
	if( FAILED(Hr) ) return 0;

	MainFrame* pFrame = new MainFrame();
	if( pFrame == NULL ) return 0;
#if defined(WIN32) && !defined(UNDER_CE)
	pFrame->Create(NULL, _T("文件共享系统"), UI_WNDSTYLE_FRAME, WS_EX_STATICEDGE | WS_EX_APPWINDOW, 0, 0, 600, 800);
#else
	pFrame->Create(NULL, _T("文件共享系统"), UI_WNDSTYLE_FRAME, WS_EX_TOPMOST, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
#endif
	pFrame->CenterWindow();
	::ShowWindow(*pFrame, SW_SHOW);

	CPaintManagerUI::MessageLoop();

	::OleUninitialize();
	::CoUninitialize();

	return 0;
}