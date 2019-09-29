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
#define  KEYWORD_BEGIN      "�ӿ� \""//"\""  
#define  KEYWORD_END        "\" ������"
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
		OspPrintf(1,0,"\n[CIPInfoManager::GetAllLinker]����bat�ļ�ʧ��\n");
		return 0;
	}

	if ( IsFileExist ( DUMPFILE ))
	{
		CFile::Remove(DUMPFILE);
	}

	BOOL bRe = WinExecAndWait(m_strBatFile.GetBuffer(m_strBatFile.GetLength()),NULL ); 
	if (!bRe)
	{   
		//AfxMessageBox("��ȡ����ʧ�ܣ�����������");
		return 0;
	}
	//Sleep(100);//������رպ�5s���ٴδ�ʱ��ȡ�������� 2010-12-17 
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
	strMsgErr = m_strBatFile + "����";
	if (!bRe)
	{
		CFile file;
		if(file.Open(m_strBatFile,CFile::modeCreate|CFile::modeWrite|CFile::typeBinary))
		{  
			file.Write(DUMP_FILE_CMD,strlen(DUMP_FILE_CMD));
			file.Close();
			bRe = TRUE;
			strMsgErr = "����" + m_strBatFile + "�ɹ�";
		}
		else
		{
			m_strBatFile.Empty();
			strMsgErr =  "����" + m_strBatFile + "ʧ��";
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

 //��ȡ��ǰ�����ӿ�����, Ŀǰ���ý��õ������ȷ��ֻ��һ����������
CString CIPInfoManager::GetCurNetWorkName()
{
	//ö�ٵ�ǰPC��������������Ϣ
	vector<CString> v_strLinker;
	GetAllLinker( v_strLinker );

    vector<CString>::iterator itr = v_strLinker.begin();

	CString strText ="";
	
    for(; itr != v_strLinker.end(); itr++)
    {
		strText = *itr;
		strText.TrimLeft();
		strText.TrimRight();

		int nPos = strText.Find("��������");
		if ( nPos != -1 )
		{
			return strText;
		}
    }
	
	strText = "��������";

	return strText;
}