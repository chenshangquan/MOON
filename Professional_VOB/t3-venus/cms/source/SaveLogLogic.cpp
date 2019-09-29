// SaveLog.cpp: implementation of the CSaveLog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SaveLogLogic.h"



CSaveLog * CSaveLog::m_pLogic = NULL;

#define READ_BUF_MAX        256 
#define READ_BUF     65536
#define CFG_FILE    _T("configure.ini")

#define LOGPATH     /*_T("kdvlog/log")*/_T("/usr/kdvlog/log")

#define CFG_PATH    _T("path")

const String CSaveLog::m_strProg = "SaveLogDlg/Progress";
const String CSaveLog::m_strProgInfo = "SaveLogDlg/StDwonProg";

template <class T> void SafeRelease(T **ppT)
{
    if (*ppT)
    {
        (*ppT)->Release();
        *ppT = NULL;
    }
}


#define SAFERELEASE(x) if (x) { x->Release(); x=NULL; }

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//下载线程 lpParam 为类指针
UINT CSaveLog::ThreadDwonLoad(LPVOID lpParam)
{    
    CSaveLog* handle = (CSaveLog*)lpParam;    
    
    TLoginInfo tLoginInfo;
    ComInterface->GetLoginInfo( tLoginInfo );
    
    in_addr inaddr;
    inaddr.S_un.S_addr = htonl(tLoginInfo.dwIp);
    handle->m_strIPAddress = inet_ntoa(inaddr);
    
    handle->m_pConnect = NULL;
    
    try
    {           
		PrtMsg(0,emEventTypeCmsWindow,"\n[CSaveLog::ThreadDwonLoad]正在建立连接\n");
        handle->m_pConnect = handle->m_sess.GetFtpConnection( handle->m_strIPAddress, "admin", "admin", INTERNET_DEFAULT_FTP_PORT );
        bool bRet = handle->m_pConnect->SetCurrentDirectory( LOGPATH );
        if ( bRet == 0 )
        {
            bRet = GetLastError();
            if ( bRet == ERROR_SUCCESS )
            {   
				PrtMsg(0,emEventTypeCmsWindow,"\n[CSaveLog::ThreadDwonLoad]建立连接失败\n");
				handle->m_pThread = NULL;
                return 1;
            }
            
        }
        
		PrtMsg(0,emEventTypeCmsWindow,"\n[CSaveLog::ThreadDwonLoad]已建立连接\n");
        
        // use a file find object to enumerate files        
        CFtpFileFind finder(handle->m_pConnect);
        
        // start looping        
        BOOL bWorking = finder.FindFile( "*"/*LOGPATH*/ );
        DWORD dwFieSize;
        CString strFileURL; 
        CString strFileName;
        DWORD dwIndex;
        while (bWorking)
        {
            bWorking = finder.FindNextFile();  
            strFileName = finder.GetFileName();  
            dwIndex = strFileName.ReverseFind( '.' );
            strFileName.Delete( 0, dwIndex );
            if ( strFileName == ".txt")
            {
                dwFieSize = finder.GetLength();
                handle->m_dwTotalFileSize += dwFieSize;
                strFileURL = finder.GetFileURL();  
                
                PrtMsg(0,emEventTypeCmsWindow,_T("\n[CSaveLog::ThreadDwonLoad]strFileURL:%s    size: %d\n"), (LPCTSTR)strFileURL, dwFieSize );
                handle->m_lstFtpFile.push_back( finder.GetFileName() );            
            }
        }
        
        finder.Close();
    }
    catch (CInternetException* pEx)
    {
        TCHAR sz[1024];
        pEx->GetErrorMessage(sz, 1024);
        PrtMsg(0,emEventTypeCmsWindow,_T("ERROR!  %s\n"), sz);
        pEx->Delete();
		handle->m_pThread = NULL;
        return false;
    }
    
    PrtMsg(0,emEventTypeCmsWindow,"\n[CSaveLog::ThreadDwonLoad]FTP file count: %d\n", handle->m_lstFtpFile.size() );
    
    //--------------------- begin download file  ---------------//
  
    DWORD dwSliceBase;
    DWORD dwRecPercent;
    DWORD dwFileSlice = handle->m_dwTotalFileSize / READ_BUF;
    if ( dwFileSlice == 0)
    {
        dwFileSlice = 1;
    }
    else
    {
        dwFileSlice += 3;
    }
    if ( dwFileSlice > 100 )
    {
        dwSliceBase = dwFileSlice / 100;        
    }
    else
    {
        dwSliceBase = 0;
    }
    
    UINT dwCount;
    DWORD dwRecCount = 0;
    Value_ProgressPos val;
    u8 byBuf[ READ_BUF ] = { 0 };
 

    list<CString>::iterator iter = handle->m_lstFtpFile.begin();
    for (; iter != handle->m_lstFtpFile.end(); iter++ )
    {  
        CString strName = *iter;
        CString strPath = handle->m_strLogPath + strName;
        
        bool bTrans = true;
        CString strDir;
        handle->m_pConnect->GetCurrentDirectory( strDir );
        handle->m_pInternetFile = handle->m_pConnect->OpenFile( (LPCTSTR)strName, GENERIC_READ );
        CFileException Error;
        
        bool bRet = handle->m_cFile.Open( strPath, CFile::modeCreate | CFile::modeWrite, &Error );
        if ( bRet == 0 )
        {
            TCHAR szError[1024];
            Error.GetErrorMessage(szError, 1024);
            PrtMsg(0,emEventTypeCmsWindow,_T("\n[CSaveLog::ThreadDwonLoad]Couldn't open source file: %s,errorcode(1024)\n"), szError);
            break;
        }

        //UIManagePtr->ShowWindow( "SaveLogDlg/BtnUnDownload", true );

        DWORD dwFileSize = handle->m_pInternetFile->GetLength();
        do 
        {   
            dwRecCount++;
            dwCount = handle->m_pInternetFile->Read( byBuf, READ_BUF );
            handle->m_cFile.Write( byBuf, dwCount );
            //pInternetFile->GetPosition();  ??
            if (  dwCount == 0 )
            {
                bTrans = false;
                
                handle->m_cFile.Close();
            }
            if ( dwFileSlice <= 100 )
            {
                dwRecPercent = dwRecCount * 100 / ( (dwFileSlice) );
                if ( dwRecPercent >= 99 )
                {
                    dwRecPercent = 100;
                }

                val.nPos = dwRecPercent;
                UIManagePtr->SetPropertyValue( val, m_strProg/*, m_pWndTree*/);    
                CString strInfo;
                strInfo.Format( "已完成%d %%", dwRecPercent);
                UIManagePtr->SetCaption( m_strProgInfo, (LPCTSTR)strInfo);
            }
            else if ( 0 == dwRecCount % dwSliceBase )
            {
                dwRecPercent = dwRecCount * 100 / ( (dwFileSlice) );                
                if ( dwRecPercent >= 99 )
                {
                    dwRecPercent = 100;
                }

                val.nPos = dwRecPercent;
                UIManagePtr->SetPropertyValue( val, m_strProg/*, m_pWndTree*/);    
                CString strInfo;
                strInfo.Format( "已完成%d %%", dwRecPercent);
                UIManagePtr->SetCaption( m_strProgInfo, (LPCTSTR)strInfo);
            }
            Sleep( 50 );
           
            
            
        } while ( bTrans );     

        handle->m_pInternetFile->Close(); 

    }

    

    val.nPos = 0;
    UIManagePtr->SetPropertyValue( val, m_strProg/*, m_pWndTree*/);            
    UIManagePtr->LoadScheme( "SchmDownLoadOk", handle->m_pWndTree );  
    handle->m_pThread = NULL;
    return 0;
}

CSaveLog::CSaveLog():m_sess(_T("My FTP Session")) ,
					m_dwTotalFileSize(0),
					m_pConnect( NULL ),
					m_pInternetFile( NULL ),
					m_cFile(),
					m_pThread( NULL )
{

}

CSaveLog::~CSaveLog()
{
    if ( m_pLogic != NULL )
    {   
        UnRegMsg();
        UnRegFunc();
        delete m_pLogic;
        m_pLogic = NULL;
	}
}

CSaveLog* CSaveLog::GetLogicPtr()
{
    if ( m_pLogic == NULL )
    {  
        m_pLogic = new CSaveLog();  
    }    
    return m_pLogic;
}

void CSaveLog::RegMsg()
{
   
    //REG_MSG_HANDLER( UI_UPDATE_POS, CSaveLog::OnProgressUpdate ,m_pLogic, CSaveLog);
}

bool CSaveLog::RegCBFun()
{
    REG_GOBAL_MEMBER_FUNC( "CSaveLog::InitWnd", CSaveLog::InitWnd, m_pLogic, CSaveLog );
    REG_GOBAL_MEMBER_FUNC( "CSaveLog::OnBtnOk", CSaveLog::OnBtnOk, m_pLogic, CSaveLog );
    REG_GOBAL_MEMBER_FUNC( "CSaveLog::OnBtnExit", CSaveLog::OnBtnExit, m_pLogic, CSaveLog );

    REG_GOBAL_MEMBER_FUNC( "CSaveLog::OnBtnCancel", CSaveLog::OnBtnCancel, m_pLogic, CSaveLog );

    REG_GOBAL_MEMBER_FUNC( "CSaveLog::OnBtnDwnOk", CSaveLog::OnBtnDwnOk, m_pLogic, CSaveLog );

    return true;
}

bool CSaveLog::UnRegFunc()
{
    
    return true;
}

bool CSaveLog::InitWnd( const IArgs & args )
{
    CWndLogicBase::InitWnd( args );      
    
    //pc版本没有CFG_FILE，下载路径直接确定 -2014.2.20 xcr
    if ( UIDATAMGR->IsPcVersion() )
    {
        m_strLogPath = _T("D:\\log\\");
		
        BOOL bExist = ComInterface->ExistDir( m_strLogPath );	
        if ( !bExist )
        {
            ComInterface->CreateDir( m_strLogPath );
		}
    }
    else
    {
        GetLogPathFromIni( m_strLogPath );
        DWORD dwIndex = m_strLogPath.ReverseFind( _T('\\') );
        DWORD dwLen = m_strLogPath.GetLength();
        if ( dwIndex != (dwLen-1) )
        {
            m_strLogPath += _T("\\");
        }
    }

    return true;
}

//抢断情况发生
void CSaveLog::Clear()
{    
    UIManagePtr->ShowWindow( g_strSaveLogDlg, false );  
    
    // if the connection is open, close it 
//     if (m_pConnect != NULL) 
//     {
//         m_pConnect->Close();
//         delete m_pConnect;
//         m_pConnect = NULL;
//     }    
   
}

//
bool CSaveLog::OnBtnOk( const IArgs & args )
{    

    UIManagePtr->LoadScheme( "SchmDownLoad", m_pWndTree);
    
    //restore data
    m_lstFtpFile.clear();
    m_dwTotalFileSize = 0;
    
    m_pThread = AfxBeginThread(ThreadDwonLoad, this); 
    //_beginthread( ThreadDwonLoad , NULL, this );
   
    return true;
}

//do not download
bool CSaveLog::OnBtnExit( const IArgs & args )
{   

	
    UIManagePtr->ShowWindow( g_strSaveLogDlg, false );
    
    return true;
}

//cancel download progress
bool CSaveLog::OnBtnCancel( const IArgs & args )
{    
	if ( NULL != m_pThread )
	{
		DWORD dwErr = 0;
		BOOL re = TerminateThread( m_pThread->m_hThread, dwErr );
		if ( NULL != m_pConnect )
		{
			m_pConnect->Close();
			m_pConnect = NULL;

			PrtMsg(0,emEventTypeCmsWindow,"\n[CSaveLog::OnBtnCancel]已取消下载日志线程");
		}
		
		if ( CFile::hFileNull != m_cFile.m_hFile )
		{
			m_cFile.Close();
		}
		
		if ( NULL != m_pInternetFile )
		{
			m_pInternetFile->Close();
		}

        Value_ProgressPos val;
        val.nPos = 0;
        UIManagePtr->SetPropertyValue( val, m_strProg/*, m_pWndTree*/); 
		
	}
 
    
    UIManagePtr->ShowWindow( g_strSaveLogDlg, false ); 

    return true;
}

void CSaveLog::GetLogPathFromIni( CString& strPath )
{
    TCHAR chExeFullPath[MAX_PATH] = _T(""); 
    GetModuleFileName(NULL,chExeFullPath,MAX_PATH);//
    
    CString strCfgPath = chExeFullPath;
    int dwIndex = strCfgPath.ReverseFind( _T('\\') );    
    strCfgPath.Delete( dwIndex, strCfgPath.GetLength() - dwIndex );
    dwIndex = strCfgPath.ReverseFind( _T('\\') );
    dwIndex++;
    strCfgPath.Delete( dwIndex, strCfgPath.GetLength() - dwIndex );
    m_strCfgFile = strCfgPath + CFG_FILE;

    LPCSTR psz = "log";   
    TCHAR szReadPath[READ_BUF_MAX] = { 0 };	
   
    GetPrivateProfileString( psz,       //section
        CFG_PATH, TEXT("ERROR"),        //part
        szReadPath, sizeof(szReadPath), 
        m_strCfgFile );

    strPath = szReadPath;

    if ( strPath == _T("ERROR") )
    {
        PrtMsg( "\n[CSaveLog::GetLogPathFromIni] can't get the path of the log folder \n");
        return;
    }

	BOOL bExist = ComInterface->ExistDir( strPath );	
	if ( !bExist )
	{
		//D盘log文件夹不存在则创建 13/7/26 by wqq
		ComInterface->CreateDir( strPath );
	}
}

//download complete
bool CSaveLog::OnBtnDwnOk( const IArgs & args )
{  
    
    UIManagePtr->ShowWindow( g_strSaveLogDlg, false );

    // if the connection is open, close it 
    if (m_pConnect != NULL) 
    {
        m_pConnect->Close();
        delete m_pConnect;
        m_pConnect = NULL;
    } 
    
    return true;
}



