// WindowTestDlg.cpp : implementation file
//

#include "stdafx.h"

#include "WindowTest.h"

#include "WindowTestDlg.h"
#include "LogicTest.h"
#include "WndFactory.h"
#include "TestLog.h"
#include "WndTreeHelp.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About



class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWindowTestDlg dialog

CWindowTestDlg::CWindowTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWindowTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWindowTestDlg)
	m_strFile = _T("TPDlg");
	m_strFile1 = _T("TPDlg");
	m_strFile2 = _T("System.xml");
	m_strSave = _T("TPDlg");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWindowTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWindowTestDlg)

	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWindowTestDlg, CDialog)
	//{{AFX_MSG_MAP(CWindowTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWindowTestDlg message handlers

#include "TitleWnd.h"


BOOL CWindowTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	new CTestLog;
	new CAlgorithmFactory;

	// TODO: Add extra initialization here
	
//	BOOL bRet = CWnd::CreateEx(0, _T( "CButton"),   NULL,WS_POPUP|WS_VISIBLE,CRect(0,0,100,100),this,   0);
//	CTitleWnd* pTitle = new CTitleWnd( "1.bmp","1.bmp","1.bmp");
//	pTitle->Create(NULL,"haha",WS_VISIBLE,CRect(0,0,100,100),this,10212);	
//	pTitle->CreateEx( 0, NULL, "haha",WS_VISIBLE,CRect(0,0,100,100),this,10212);	
//	pTitle->ShowWindow(SW_SHOW);
// 	CFlatButton* pBtn = new CFlatButton();
// //	pBtn->Create( "haha",WS_VISIBLE,CRect(0,0,100,100),this,20112);
 //	CBaseWnd* pBase = new CBaseWnd( CRect(0,0,100,100), this, WS_VISIBLE, 10212 );

//  	CBmpWnd* pWnd = new CBmpWnd( 0, "Name", CRect(0,0,100,100), this, WS_CHILD|WS_VISIBLE , "1.bmp" , GETUNIQID,TRUE,FALSE,RGB(0,0,0),TRUE );
//  	pWnd->ShowWindow( SW_SHOW );
// 	CBmpWnd* pWnd1 = new CBmpWnd( 0, "Name", CRect(0,0,100,100), NULL, WS_OVERLAPPEDWINDOW|WS_VISIBLE , "1.bmp" , 0,TRUE,FALSE,RGB(0,0,0),TRUE );
//  	pWnd1->ShowWindow( SW_SHOW );
//	p->Create( "haha", WS_VISIBLE, CRect(0,0,100,100), this, 20000 );
//	Window* pWnd = p;
///	CFlatButton* pFlat = dynamic_cast<CFlatButton*>(p);
// 	IItem< IBaseItem, int >* pLast = 0;
// 	CTouchList* pTouchList = new CTouchList( "1.bmp", CRect( 0,0,200,400), this, 10101 );
// 	for ( int i = 0; i < 5; i++ )
// 	{
// 		CImageItem* pItem = new CImageItem( 0,i*10 + 10 );
// 
// 		Image* pImage =  CSrcManage::GetImage( "..\\layout\\2.bmp" );
// 		if ( pImage != 0 )
// 		{
// 			pItem->SetImage( pImage );
// 		}
// 		
// 		IItem< IBaseItem, int > *p = pTouchList->AddItem( pItem, 0, emLayoutAlgorithm_Hori );
// 		if ( p != 0 )
// 		{
// 			for ( int j = 0; j < 5; j++ )
// 			{
// 				CImageItem* pItem = new CImageItem( 20, 10 );
// 
// 				Image* pImage =  CSrcManage::GetImage( "..\\layout\\3.bmp" );
// 				if ( pImage != 0 )
// 				{
// 					pItem->SetImage( pImage );
// 				}
// 
// 				pLast = pTouchList->AddItem( pItem, p );
// 			}
// 		}		
// 	}
// 	pTouchList->SetMoveStatus( TRUE );
// 	pTouchList->Layout();
// 	CRect rcFrame = pTouchList->GetFrame();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWindowTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWindowTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
// 	CClientDC dc(this);
// 	Graphics* p = new Graphics( dc.GetSafeHdc() );
// 
// 
// 	Bitmap* pBitmap1 = new Bitmap( 50 , 50 , p );
// 	Graphics* pGraphics1 = Graphics::FromImage( pBitmap1 );
// 	pGraphics1->DrawLine( &Pen(Color::Black), 0, 0 , 10, 10);
// 	Bitmap* pBitmap2 = new Bitmap( 50 , 50 , pGraphics1 );
// 	Graphics* pGraphics2 = Graphics::FromImage( pBitmap2 );
// 	pGraphics2->DrawLine( &Pen(Color::Black), 10, 0 , 10, 10);
// 	pGraphics1->DrawImage( pBitmap2, 0, 0 );
// 	p->DrawImage( pBitmap1,50, 50 );
// 	delete pBitmap1;
// 	pBitmap1 = 0;
// 	delete pBitmap2;
// 	pBitmap2 = 0;
// 	delete pGraphics1;
}	

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWindowTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CWindowTestDlg::Print( IWndTree* pTree )
{
	static int nIndex = 0;
	int nCount = pTree->GetItemCount();
	WndInfo* pInfo = pTree->GetItemData();
	String strKey = pTree->GetItemName();
	String strType = pInfo->strType;
	
	String strTemp = strKey + " --- " + strType;
	m_list.AddString( strTemp.c_str() );
	for ( int i = 0; i < nCount; i++ )
	{
		IWndTree* pSub = pTree->GetItemByIndex( i );
		pInfo = pSub->GetItemData();
		strKey = pSub->GetItemName();
		strType = pInfo->strType;

		strTemp = strKey + " --- " + strType;
		m_list.AddString( strTemp.c_str() );
		Print( pSub );
	}
}

void CWindowTestDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CString strName;
	m_edit.GetWindowText( strName );

	IWndTree* pTree2 = const_cast<IWndTree*>(CWindowManage::GetSingletonPtr()->GetWindowTree( strName.GetBuffer(0) ));
	m_list.AddString( "------------------" );
	if ( pTree2 != 0 )
	{
		Print( const_cast<IWndTree*>(pTree2) );
	}
}

void CWindowTestDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	CString strName;
	m_edit2.GetWindowText( strName );
	
	IWndTree* pTree2 = const_cast<IWndTree*>(CWindowManage::GetSingletonPtr()->GetWindowTree( strName.GetBuffer(0) ));
	m_list.AddString( "------------------" );
	if ( pTree2 != 0 )
	{
		Print( const_cast<IWndTree*>(pTree2) );
	}

	CWindowManage::GetSingletonPtr()->DestoryWnd( pTree2 );
}

void CWindowTestDlg::OnButton3() 
{
	CString strName;
	m_edit3.GetWindowText( strName );
	SetCurrentDirectory( "layout" );
	new CSystem( strName.GetBuffer(0) );
	LogicTest* pTest = new LogicTest();
	REG_GOBAL_MEMBER_FUNC( "Login::Click", LogicTest::Test, pTest, LogicTest );
//	REG_WINDOW_FACTORY( "CWindow", CWndFactory );
}

#include "SaveXmlHelp.h"
void CWindowTestDlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
	CString strName;
	m_editsave.GetWindowText( strName );
	CSaveXmlHelp::SaveXml( strName.GetBuffer(0) );
}
