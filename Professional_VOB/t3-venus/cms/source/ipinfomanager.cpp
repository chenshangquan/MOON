// IPInfoManager.cpp: implementation of the CIPInfoManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cms.h"
#include "IPInfoManager.h"
#include <direct.h>
#include <stdio.h>
#include <stdlib.h>


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


#define  DUMPFILE    "d:\\net.txt" 
#define  DUMP_FILE_CMD "netsh interface ip show config >d:\\net.txt"
#define  BAT_FILE      "dumpFile.bat"
#define  EXEFILE     "c:\\WINDOWS\\system32\\netsh.exe"
#define  KEYWORD_BEGIN      "接口 \""//"\""  
#define  KEYWORD_END        "\" 的配置"
#define  DELETEWORD  "Loopback Pseudo-Interface 1"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BOOL IsFileExist(LPCTSTR lpszFilePath)
{
	BOOL bExist = FALSE;
	HANDLE hFile = NULL;

	hFile = CreateFile( lpszFilePath
		, GENERIC_READ
		, FILE_SHARE_READ | FILE_SHARE_WRITE
		, NULL
		, OPEN_EXISTING
		, 0
		, 0
		);

	if( hFile != INVALID_HANDLE_VALUE )
	{
		CloseHandle( hFile );
		bExist = TRUE;
	}

	return bExist;
}

CIPInfoManager::CIPInfoManager()
{   
	m_strDumpFile = "";
	m_strBatFile  = "";
	ExistBatFile(); 
}

CIPInfoManager::~CIPInfoManager()
{   
	
}


int CIPInfoManager::GetAllLinker(vector<CString> &v_strLinker)
{    
    v_strLinker.clear();
// 	CString temp ;	
// 	temp = GetAppPath() + "dumpFile.bat";	//"netsh interface ip show config >c:\\net.txt";
	if ( ExistBatFile() == FALSE)
	{   
		OspPrintf(1,0,"\n[CIPInfoManager::GetAllLinker]生产bat文件失败\n");
		return 0;
	}

	if ( IsFileExist ( DUMPFILE ))
	{
		CFile::Remove(DUMPFILE);
	}

	BOOL bRe = WinExecAndWait(m_strBatFile.GetBuffer(m_strBatFile.GetLength()),NULL ); 
	if (!bRe)
	{   
		//AfxMessageBox("获取网卡失败，请重新启动");
		return 0;
	}
	//Sleep(100);//解决：关闭后5s内再次打开时获取不到网卡 2010-12-17 
	CFile cfNetfile;
	if (cfNetfile.Open(DUMPFILE,CFile::modeRead))
	{
		DWORD dwLen = cfNetfile.GetLength();
		char buf[32767] ={0};
		DWORD dwCurLen = 0;
		while (dwCurLen < dwLen)
		{
			dwCurLen += cfNetfile.Read(buf,sizeof(buf));
			char* index = NULL;
			index = strstr(buf,KEYWORD_BEGIN);
			while (index != NULL)
			{   
				char * tem = NULL;
				int t  = (index-buf);
				tem = strstr/*strchr*/(buf+t+strlen(KEYWORD_BEGIN),KEYWORD_END);
				
				if (tem == NULL)
				{
					break;
				} 

				char linker[100] ={0}; 
				_snprintf(linker,tem-index-strlen(KEYWORD_BEGIN) ,"%s",buf+(index-buf+strlen(KEYWORD_BEGIN))); 
				CString ee(linker);
				OutputDebugString("\n" + ee +"\n");
				if (ee != DELETEWORD)
				{
					v_strLinker.push_back(ee); 
				}
							 
				//index = strstr(buf+(tem-buf)+1,KEYWORD);
				index = strstr(buf+(tem-buf)+sizeof(KEYWORD_END),KEYWORD_BEGIN);
			}
			
		} 
		cfNetfile.Close();
	}
	

	return v_strLinker.size();
}



CString CIPInfoManager::GetAppPath()
{
	DWORD dwSize;
	CString strAppPath;
	CString strResult;
	int iIndex;
	dwSize=::GetModuleFileName(NULL,strAppPath.GetBufferSetLength(MAX_PATH),MAX_PATH);
	if (dwSize<0 || dwSize>MAX_PATH)
	{
		strAppPath="";
		return strAppPath;
	}
	
    iIndex=strAppPath.ReverseFind('\\') ;
	
    strAppPath=strAppPath.Left(iIndex+1);
	return strAppPath;
}

BOOL CIPInfoManager::ExistBatFile()
{   
	BOOL bRe = FALSE;
	CString strAppPath = GetAppPath();
	m_strBatFile = strAppPath + BAT_FILE ;  
	bRe = IsFileExist((LPCSTR)m_strBatFile);
    CString strMsgErr;
	strMsgErr = m_strBatFile + "存在";
	if (!bRe)
	{
		CFile file;
		if(file.Open(m_strBatFile,CFile::modeCreate|CFile::modeWrite|CFile::typeBinary))
		{  
			file.Write(DUMP_FILE_CMD,strlen(DUMP_FILE_CMD));
			file.Close();
			bRe = TRUE;
			strMsgErr = "创建" + m_strBatFile + "成功";
		}
		else
		{
			m_strBatFile.Empty();
			strMsgErr =  "创建" + m_strBatFile + "失败";
		}
	}
	
	OutputDebugString("\n[CIPInfoManager::ExistBatFile] " + strMsgErr);
	
	return bRe;
}


BOOL CIPInfoManager::WinExecAndWait(LPSTR lpExeName, LPSTR lpCmdLine)
{  
	BOOL bRe = FALSE;
	PROCESS_INFORMATION pi;
	
	STARTUPINFO si;
	
	memset(&si,0,sizeof(si));
	
	si.cb=sizeof(si);
	
	si.wShowWindow=SW_HIDE;
	
	si.dwFlags=STARTF_USESHOWWINDOW;	
	
	bRe = CreateProcess( lpExeName, lpCmdLine,NULL, FALSE,NULL,NULL,NULL,NULL,&si,&pi);
    
	if (bRe != FALSE)
	{
		WaitForSingleObject(pi.hProcess,INFINITE);
	}

	return bRe;
} 

 //获取当前网卡接口名称, 目前采用禁用的情况，确保只用一个本地连接
CString CIPInfoManager::GetCurNetWorkName()
{
	//枚举当前PC所有网卡连接信息
	vector<CString> v_strLinker;
	GetAllLinker( v_strLinker );

    vector<CString>::iterator itr = v_strLinker.begin();

	CString strText ="";
	
    for(; itr != v_strLinker.end(); itr++)
    {
		strText = *itr;
		strText.TrimLeft();
		strText.TrimRight();

		int nPos = strText.Find("本地连接");
		if ( nPos != -1 )
		{
			return strText;
		}
    }
	
	strText = "本地连接";

	return strText;
}