// uiDataMgr.cpp: implementation of the CUIDataMgr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cnsToolDll.h"
#include "uiDataMgr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const string g_stcMsgboxDlg = "MsgboxDlg";	//��ʾ������
const string g_strMainFrame = "MainFrame" ; // 	CfgCnsDlg
const string g_strBasicInfoDlg = "BasicInfoDlg"; //������Ϣ����		 
const string g_strCfgFrame = "CfgFrame";        //���ÿ��	
const string g_strCfgCnsDlg = "CfgCnsDlg";		//���ÿ���е�cns����
const string g_strCfgAudioPort = "CfgAudioPortDlg";	//���ÿ���е���Ƶ���ý���
const string g_strCfgMixDlg = "CfgMixAudioDlg"; //���ÿ���еĻ������ý���
const string g_strDiagInfoDlg = "DiagInfoDlg";		//��ϲ��Խ���
const string g_strCentCfgFrame = "CentCfgFrame";		//�п���Ϣ����
const string g_strDiagInTestInfo = "DiagTestInDlg";	//������Խ���
const string g_strDiagOutTestInfo = "DiagTestOutDlg";	//������Խ���
const string g_strDiagTestFrame = "DiagTestFrame";	//��ϲ�����ʾ����
const String g_stcStrCfgNetMngDlg		= "CfgNetMngDlg";			//�������ý���
const String g_stcStrNetMngOptDlg		= "NetMngOptDlg";			//���ܲ�������
const String g_StrCameraDlg			= "CameraDlg";				//������ڽ���
const String g_strAddrbookExpDlg = "AddrbookExpDlg";			//��ַ������
const String g_strCfgServerDlg = "CfgServerDlg";		//���ÿ���еķ���������
const String g_strCfgEqDlg = "CfgEqDlg";	//���ÿ���еľ���������
const String g_stcStrImpCommonDlg		= "ImpCommonDlg";		//�ϴ������룩ͨ�õ�������  �磺���������������������ؽ���   ���������ͬ  ͨ����������
const String g_stcStrExpCommonDlg		= "ExpCommonDlg";		//���أ�������ͨ�õ�������  �磺�������á�������־����  ���������ͬ  ͨ����������
const String g_strWarningDlg = "WaringDlg";
const String g_strCfgCallSer = "CfgCallSerDlg";			//�������ý���
const String g_strCentXinFengDlg = "CentCfgXinFengDlg";	//�п��·����
const String g_strCentCameraDlg = "CentCfgCameraDlg";	//�п����������
const String g_strCentLightDlg = "CentCfgLightDlg";		//�пصƹ����
const String g_strCentDisplayDlg = "CentCfgDisplayDlg";	//�пص��ӻ�����
//��Ҫ����
const  string g_strShmShow = "SchmShow"; //��ʾ���� 
const  string g_strShmHide = "SchmHide"; //���ط���


CUIDataMgr::CUIDataMgr()
{

}

CUIDataMgr::~CUIDataMgr()
{

}

BOOL CUIDataMgr::NotifyOuterWnd( UINT nMsg , WPARAM wparam, LPARAM lparam )
{
	BOOL bRe = FALSE;
	if ( NULL != g_hNotifyWnd )
	{
		::SendMessage( g_hNotifyWnd, nMsg, wparam, lparam );
		bRe = TRUE;
	}

	return bRe;
}

String CUIDataMgr::GetFileFolderPath( const String& strFilePath )
{
	String strFolderPath = strFilePath;
	s32 nPos = strFolderPath.rfind( "\\" );
	if ( nPos != std::string::npos )
	{
		strFolderPath = strFolderPath.substr( 0, nPos );
	}
	
	return strFolderPath;
}

String CUIDataMgr::OpenBrowseForFolder( const String& strFileName, HWND hWnd /*= NULL*/, BOOL bIsAddFileName /*= TRUE */ )
{
	String    strFolderPath;
	BROWSEINFO broInfo = {0};
	TCHAR       szDisName[MAX_PATH] = {0};
	
	broInfo.hwndOwner = hWnd/*NULL*/;
	broInfo.pidlRoot  = NULL;
	broInfo.pszDisplayName = szDisName;
	broInfo.lpszTitle = _T("ѡ�񱣴�·��");
	broInfo.ulFlags   = BIF_NEWDIALOGSTYLE | BIF_DONTGOBELOWDOMAIN
		| BIF_BROWSEFORCOMPUTER | BIF_RETURNONLYFSDIRS | BIF_RETURNFSANCESTORS;
	broInfo.lpfn      = NULL;
	broInfo.lParam    = NULL;
	
	LPITEMIDLIST pIDList = SHBrowseForFolder(&broInfo);
	if (pIDList != NULL)
	{
		memset(szDisName, 0, sizeof(szDisName));
		SHGetPathFromIDList(pIDList, szDisName);
		strFolderPath = szDisName;
		CString str(strFolderPath.c_str());
		s32 nIndex = str.Find( "\\", str.GetLength()-1 );
		if ( nIndex == -1 )
		{
			strFolderPath += "\\";
	    }
		//strFolderPath += "\\";

		if ( bIsAddFileName )
		{
			strFolderPath += strFileName;
		}
	}
	
	return strFolderPath;
}

BOOL CUIDataMgr::OpenFileDialog( const String& strFilter, const String& strDefFileName, String& strFilePathName, String& strFileName, BOOL bOpenStyle /*= TRUE */ )
{
	CFileDialog dlg( bOpenStyle, NULL, strDefFileName.c_str(), OFN_FILEMUSTEXIST|OFN_HIDEREADONLY|OFN_NOCHANGEDIR, strFilter.c_str() ); // ����һ������������Ǳ���
	if ( dlg.DoModal() == IDOK )  
	{  
		strFilePathName = (String)dlg.GetPathName();  
		strFileName = (String)dlg.GetFileName();
    } 
	else
	{
		return FALSE;
	}
	
	if ( FALSE == bOpenStyle )
	{	
		CFile cFile;
		CFileFind cFindExit;
		BOOL bWorking = cFindExit.FindFile(strFilePathName.c_str());
		if (bWorking == 1)
		{
			MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
			MSG_BOX( nMsgBoxRet, "ͬ���ļ��Ѵ���,�Ƿ��滻��" );
			if ( MSGBOX_OK == nMsgBoxRet )
			{
				cFile.Remove(strFilePathName.c_str());
			}
			else
			{
				return false;
			}
		}
	}

	return TRUE;
}

BOOL CUIDataMgr::CheckTransferFile( const String& strFileFullPath, const String& strCheckFileName )
{
	if ( strFileFullPath.empty() )
	{
		MSG_BOX_OK("·������Ϊ��!");	
		
		return FALSE;
	}
	
	s32 nPos = strFileFullPath.rfind( "\\" );
	String strFileName = strFileFullPath;
	if ( nPos != std::string::npos )
	{
		strFileName = strFileName.substr( nPos + 1, strFileName.size() );
	}
	
	if ( strCheckFileName != strFileName )
	{
		MSG_BOX_OK("������Ϸ����ļ�ȫ·��!"); 
		
		return FALSE;
	}
	
	return TRUE;
}

u64 CUIDataMgr::GetFileSize( const String& strFilePath )
{
	if( strFilePath.empty() )
	{
		return 0;
	}
	
	if ( !::PathFileExists(strFilePath.c_str()) )
	{
		return 0;
	}
	
	CFileException ex;
	CFile file;
	if ( !file.Open( strFilePath.c_str(), CFile::modeRead|CFile::shareDenyNone ) )
	{
		TCHAR chError[1024];
		ex.GetErrorMessage( chError, 1024 );
		return 0;
	}
	
	u64 nFileSize = file.GetLength();
	file.Close();
	
	return nFileSize;
}

BOOL CUIDataMgr::IsFileExist( const CString& strFileFullPath )
{
	if( strFileFullPath.IsEmpty() )
	{
		return FALSE;
	}
	
	DWORD dwAttr = GetFileAttributes(strFileFullPath);
	if( INVALID_FILE_ATTRIBUTES == dwAttr || ( dwAttr & FILE_ATTRIBUTE_DIRECTORY ) )
	{
		return FALSE;
	}
	
	return TRUE;
}

BOOL CUIDataMgr::IsFolderExist( const CString& strFolderFullPath )
{
	DWORD dwAttr; 
    dwAttr = GetFileAttributes(strFolderFullPath); 
    return ( dwAttr != INVALID_FILE_ATTRIBUTES ) && ( dwAttr & FILE_ATTRIBUTE_DIRECTORY); 
}

BOOL CUIDataMgr::IsIniFile( const String& strFileName )
{
	if ( !IsFileExist(strFileName.c_str()) )
	{
		return FALSE;
	}
	
	String strFileExtName;
	s32 nPos = strFileName.rfind( "." );
	if ( nPos != std::string::npos )
	{
		strFileExtName = strFileName.substr( nPos + 1, strFileName.size() );
		if ( strFileExtName == "ini" )
		{
			return TRUE;
		}
	}
	else
	{
		return FALSE;
	}
	
	return FALSE;
}

CString CUIDataMgr::GetIpStr( unsigned int dwIPAddr )
{
	CString strIP;
	struct in_addr addrIPAddr;
	addrIPAddr.S_un.S_addr = htonl(dwIPAddr);
	strIP = inet_ntoa(addrIPAddr);
	
    return strIP;
}

BOOL CUIDataMgr::RecusionMkDir( CString strFolder )
{
	s32 nLen = strFolder.GetLength();
    if( nLen < 2 ) 
	{
		return FALSE; 
    }
	
    if( '\\' == strFolder[nLen-1] )
    {
        strFolder = strFolder.Left( nLen-1 );
        nLen = strFolder.GetLength();
    }
	
    if ( nLen <= 0 ) 
	{
		return FALSE;
    }
	
    if ( nLen <= 3 ) 
    {
        if ( IsFolderExist(strFolder) )
		{
			return TRUE;
        }
		else
		{
			return FALSE; 
		}
    }
	
    if ( IsFolderExist(strFolder) )
	{
		return TRUE;
	}
	
    CString strParent;
    strParent = strFolder.Left( strFolder.ReverseFind('\\') );
    if( strParent.GetLength() <= 0)
	{
		return FALSE; 
    }
	
    BOOL bRet = RecusionMkDir(strParent); 
    if( bRet ) 
    {
        SECURITY_ATTRIBUTES sa;
        sa.nLength = sizeof(SECURITY_ATTRIBUTES);
        sa.lpSecurityDescriptor = NULL;
        sa.bInheritHandle = 0;
        bRet = CreateDirectory( strFolder, &sa );
		
        return bRet;
    }
    else
	{
        return FALSE;
	}
	
	return TRUE;
}

void CUIDataMgr::SetLstSelItem(const String& strLstWnd, IWndTree* pWndTree /*= NULL*/, s32 nItemNo)
{
	CTransparentList* pWnd = (CTransparentList*)UIFACTORYMGR_PTR->GetWindowPtr( strLstWnd, pWndTree );
	if ( NULL != pWnd )
	{
		pWnd->SetSelItem(nItemNo);
	}
}


