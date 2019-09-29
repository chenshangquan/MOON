// UiFactroyLog.cpp: implementation of the UiFactroyLog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cms.h"
#include "UiFactroyLog.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define  UIFACTORY_LOG  "uifactory.log"  //记录创建界面的日志 

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUiFactroyLog::CUiFactroyLog()
{
   //清除上次的log 
//     String strLog =  GetLogFile();
//     
//     try
//     {
//         CFile::Remove( strLog.c_str()  );
//     }
//     catch( ... )
//     {
//        WriteWrongInfo("删除 uifacotryLog 失败，uifacotryLog 不存在");
//     }
 
}

CUiFactroyLog::~CUiFactroyLog()
{

}


bool CUiFactroyLog::LogEvent( String strEvent, LogLevel emLoglv /* = Standard */ )
{
	//TRACE( strEvent.c_str() );
    // WriteWrongInfo( strEvent );
	 return true;
}


String CUiFactroyLog::GetLogFile()
{
    TCHAR achDllName[MAX_PATH] = _T(""); 
    GetModuleFileName(AfxGetInstanceHandle(), achDllName, sizeof (achDllName));
    String str( achDllName ); 
    
    int pos = str.find_last_of('\\'); 
    String strSub = str.substr( 0,pos+1 );
    char strFullPath[MAX_PATH] = _T(""); 
    _snprintf(strFullPath , sizeof(strFullPath), "%s%s",strSub.c_str(),UIFACTORY_LOG  );
    
    str = strFullPath ;
    return str;
}

void CUiFactroyLog::WriteWrongInfo(  String str )
{   
    String strLog =  GetLogFile();
    SYSTEMTIME sysTime;
    GetLocalTime(&sysTime);
    char strTime[256] = {0} ;
    
    _snprintf(strTime, sizeof(strTime), "\n\n %d/%d/%d %d:%d:%d \n %s", 
        sysTime.wYear, sysTime.wMonth, sysTime.wDay, 
        sysTime.wHour, sysTime.wMinute, sysTime.wSecond,str.c_str() ); 
    
    

    CFile file;
    if ( file.Open( strLog.c_str(), CFile::modeNoTruncate|CFile::modeCreate|CFile::modeWrite  ,NULL) )
    {  
        file.SeekToEnd();  
        file.Write( strTime, strlen( strTime ) );
        file.Close();

    }
   
}  //// WriteWrongInfo( strMsg.c_str() );
