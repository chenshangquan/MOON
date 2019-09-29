// loadcmcDlg.cpp : implementation file
//

#include "stdafx.h"
#include "loadcmc.h"
#include "loadcmcDlg.h"
#include "loadinstance.h"
#include "nmscommon.h"
#include "direct.h"
#include <Tlhelp32.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define CONFIG_FILE			"D:\\Program Files (x86)\\Kedacom\\updatecmc\\UpdateConfig.ini"

#define READ_BUF_MAX        128

//key名称
#define FILE_NAME           "Name"
#define FILE_PATH           "Path"
#define FILE_MOVE	        "NeedMove"
#define FILE_REG	        "NeedReg"

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
// CLoadcmcDlg dialog

CLoadcmcDlg::CLoadcmcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoadcmcDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoadcmcDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_bInitOsp = FALSE;

	m_strFileStorePath = "D:\\Program Files (x86)\\Kedacom\\updatecmc\\";
}

CLoadcmcDlg::~CLoadcmcDlg()
{
	if(!m_bInitOsp)
    {
        OspQuit();
    }
}

void CLoadcmcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoadcmcDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLoadcmcDlg, CDialog)
	//{{AFX_MSG_MAP(CLoadcmcDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_MESSAGE(UI_UPDATECMC_OVER, OnUpdateOver)
	ON_MESSAGE(UI_REBOOTCMC_CMD, OnRebootCmc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoadcmcDlg message handlers

BOOL CLoadcmcDlg::OnInitDialog()
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
	
	// TODO: Add extra initialization here
	MoveWindow( -1, -1, 1, 1 );

	//初始化OSP
	InitializeOsp();
	//初始化FTP服务
	InitFtpServer();

	CopyFiles();

	SetTimer( 1, 5000, NULL );
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLoadcmcDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CLoadcmcDlg::OnPaint() 
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
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLoadcmcDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}




void CLoadcmcDlg::CopyFiles()
{
	char readtemp[READ_BUF_MAX];	
	char achFileName[1024] = {0};
	int i = GetPrivateProfileSectionNames( achFileName, 1024, CONFIG_FILE );
	i = 0;
	for( char* Name = achFileName; *Name != '\0'; Name += strlen(Name) + 1 )
	{
		i++;
	}
	int nFileNum = i;
	
	CString strSectionIndex;
	CString strFileName;
	CString strFilePath;
	BOOL bMove = FALSE;
	BOOL bFileReg = FALSE;
	memset(readtemp, 0, READ_BUF_MAX);
	char achFileFrom[READ_BUF_MAX] = {0};
	char achFileTo[READ_BUF_MAX] = {0};
	BOOL bOK = FALSE;

	for ( i = 1; i <= nFileNum; i++ )
	{
		CString strIndex;
		strIndex.Format( "%d", i );
		
		strSectionIndex = "File";
		strSectionIndex += strIndex;
		
		//取得文件名
		GetPrivateProfileString( strSectionIndex, FILE_NAME, TEXT(""), readtemp, sizeof(readtemp), CONFIG_FILE );
		strFileName = readtemp;
		
		//取得文件路径
		GetPrivateProfileString( strSectionIndex, FILE_PATH, TEXT(""), readtemp, sizeof(readtemp), CONFIG_FILE );
		strFilePath = readtemp;
		strFilePath += "\\";
		
		//是否需要剪切
		GetPrivateProfileString( strSectionIndex, FILE_MOVE, TEXT(""), readtemp, sizeof(readtemp), CONFIG_FILE );
		bMove = atoi(readtemp);

		//是否需要注册
		GetPrivateProfileString( strSectionIndex, FILE_REG, TEXT(""), readtemp, sizeof(readtemp), CONFIG_FILE );
		bFileReg = atoi(readtemp);
		
		if ( bMove )
		{
			CString strFileFrom = m_strFileStorePath + strFileName;
			CString strFileTo = strFilePath /*+ strFileName*/;

			memset( achFileFrom, 0, READ_BUF_MAX );
			memset( achFileTo, 0, READ_BUF_MAX );
			strncpy( achFileFrom, (LPTSTR)(LPCTSTR)strFileFrom, READ_BUF_MAX );
			strncpy( achFileTo, (LPTSTR)(LPCTSTR)strFileTo, READ_BUF_MAX );
			
			bOK = MoveFile( achFileFrom, achFileTo );		
		}
		else
		{
			//拷贝文件到指定目录
			bOK = CopyFile( m_strFileStorePath + strFileName, strFilePath + strFileName, FALSE );
		}
				
		if ( TRUE == bFileReg )
		{
			strFilePath += strFileName;
			//要按照" regsvr32 "......" "这个格式来，所以\" 的位置就至关重要,/s是不显示结果对话框
			strFilePath = "Regsvr32 \"" + strFilePath + "\"" + " /s";
			WinExec( strFilePath, SW_HIDE );
		}
	}
}



void CLoadcmcDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
    KillTimer( 1 );

	// 启动手写输入程序
	CString cstrPath = GetModuleFullPath();
	cstrPath += "handInputTablet\\handInputTablet.exe";
    int hIns = (int)ShellExecute( NULL, "open", cstrPath, NULL, NULL, SW_SHOW );

	Sleep( 1000 );
    // 延时启动cmc.exe程序
	cstrPath = GetModuleFullPath();
	cstrPath += "cmc.exe";
    hIns = (int)ShellExecute( NULL, "open", cstrPath, NULL, NULL, SW_SHOW );
	
	CDialog::OnTimer(nIDEvent);
}



LRESULT CLoadcmcDlg::OnUpdateOver( WPARAM wParam, LPARAM lParam )
{
	CloseCmc();

	//等待进程完全关闭
	Sleep( 3000 );

	//CopyFiles();

	//重启
	ReBootCmc();

	return NO_ERROR;
}

LRESULT CLoadcmcDlg::OnRebootCmc( WPARAM wParam, LPARAM lParam )
{
	Sleep( 1000 );
		
	//重启
	ReBootCmc();
	
	return NO_ERROR;
}


void CLoadcmcDlg::InitializeOsp()
{
	// 初始化OSP
    const u32 dwTelnetPort = 0;
    if( !IsOspInitd() )
    {
		
        BOOL bTelnet  = FALSE ;
		
#ifdef _DEBUG
        bTelnet = TRUE;
#endif
		
        if(!OspInit( bTelnet, dwTelnetPort))
        {
            return;
        }
        else
        {
            m_bInitOsp = FALSE;
        }
    }
    else
    {
        m_bInitOsp = TRUE;
    }
   
	//创建本地监听节点
	s32 sIsSucc = ::OspCreateTcpNode(0, CONNETCT_PORT);
	if (INVALID_SOCKET == sIsSucc)
	{
		return;
	}
	
	char szOspApp[] = "loadcmc1.0";
	const u32 dwPrior = 80;
	int nRet = g_loadApp.CreateApp(&szOspApp[0], AID_LOADCMC_APP, dwPrior, 300, 200);
	ASSERT(nRet == 0);
    
    return;
}


BOOL CLoadcmcDlg::ExistDir(const CString strDir)
{
	CFileStatus fs;
	return CFile::GetStatus(strDir, fs);
}

BOOL CLoadcmcDlg::CreateDir(CString strDir)
{
	if (ExistDir(strDir))
		return TRUE;
	if (strDir.Right(1) != _T("\\"))
		strDir += _T("\\");
	
	// can not create network directory
	int nPos = strDir.Find(_T(":"));
	if (nPos == -1)
		return FALSE;
	// no need to create drive
	nPos = strDir.Find(_T("\\"), nPos + 1);
	if (nPos + 1 == strDir.GetLength())
		return TRUE;
	
	CFileStatus fs;
	while (nPos < strDir.GetLength() - 1)
	{
		nPos = strDir.Find(_T("\\"), nPos + 1);
		if (!CFile::GetStatus(strDir.Left(nPos), fs))
		{
			if (/*_tmkdir*/_mkdir(strDir.Left(nPos)) == -1)
				return FALSE;
		}
	}
	return TRUE;
}

BOOL CLoadcmcDlg::InitFtpServer()
{
	CString cstrPath = GetModuleFullPath();
	cstrPath += "ftpserver\\FTPServer.exe";
	
	BOOL32 bExist = ExistDir( cstrPath );	
	if ( !bExist )
	{
		OspPrintf(1,0, "Init Ftp Server Failed. Because file is not exist\n");
		return FALSE; 
	}
	
	//判断ftp权限目录是否存在
	CString strFtpDebug = "D:\\Program Files (x86)\\Kedacom\\updatecmc";
	
	bExist = ExistDir( strFtpDebug );	
	if ( !bExist )
	{
		//不存在则 创建
		CreateDir( strFtpDebug );
	}
	
	int hIns1 = (int)ShellExecute( NULL, "open", cstrPath, NULL, NULL, SW_SHOWMINIMIZED );
	
	OspPrintf(1,0, "Loadcmc init Ftp Server Succ\n");
	
	return TRUE;
}



BOOL CLoadcmcDlg::MoveFile( char *pFrom, char *pTo )
{
	SHFILEOPSTRUCT FileOp={0};
	FileOp.fFlags = FOF_NOCONFIRMATION | FOF_NOCONFIRMMKDIR// 不出现确认对话框 | 需要时直接创建一个文件夹,不需确定
		| FOF_NOERRORUI | FOF_SILENT;              // 不提示错误信息 | 不显示进度框
	FileOp.pFrom = pFrom;
	FileOp.pTo = pTo;
	FileOp.wFunc = FO_MOVE;
	return SHFileOperation(&FileOp) == 0;   
}


void CLoadcmcDlg::CloseCmc()
{
	HANDLE hSnapshot, hProcess;
	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);	//创建进程快照
	
	PROCESSENTRY32 pe;
	ZeroMemory(&pe,sizeof(PROCESSENTRY32));
	pe.dwSize = sizeof(PROCESSENTRY32);
	BOOL bFirstProcess = TRUE, bSucceed = FALSE;
	
	bSucceed = Process32First(hSnapshot, &pe);	//获取第一个进程的信息
	while(bSucceed)
	{
        CString strExeFile = pe.szExeFile;
        strExeFile.MakeLower();
        if( strExeFile == "cmc.exe" )
		{
			hProcess = OpenProcess (PROCESS_ALL_ACCESS, FALSE, pe.th32ProcessID);	//打开进程
			TerminateProcess(hProcess,0);
			break;
		}
		else
		{
			bSucceed = Process32Next(hSnapshot, &pe);	//获取下一个进程的信息
		}
	}
	CloseHandle(hSnapshot);		//关闭快照句柄
}

void CLoadcmcDlg::ReBootCmc()
{
	HANDLE hToken;
    TOKEN_PRIVILEGES tkp;
	
    //   Get   a   token   for   this   process.
    if ( TRUE == OpenProcessToken( GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken ) )
    {
        // Get   the   LUID   for   the   shutdown   privilege.
        LookupPrivilegeValue( NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid );
		
        tkp.PrivilegeCount = 1;     //   one   privilege   to   set
        tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		
        // Get   the   shutdown   privilege   for   this   process.
        AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0 );
		
        if ( GetLastError() == ERROR_SUCCESS )
        {   
            //   Shut   down   the   system   and   force   all   applications   to   close.
            if ( TRUE == ExitWindowsEx( EWX_REBOOT , 0 ) )
            {
                ExitWindowsEx( EWX_REBOOT , 0 ); //关机
            }
        }
    }
}


