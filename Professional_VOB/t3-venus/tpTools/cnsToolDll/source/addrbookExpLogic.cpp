// addrbookExpLogic.cpp: implementation of the AddrbookExpLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "addrbookExpLogic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAddrbookExpLogic::CAddrbookExpLogic():
m_strEdtImport("EdtImport"),
m_strProgressImp("ProgressImp"),
m_strEdtExport("EdtExport"),
m_strProgressExp("ProgressExp")
{
	m_pWnd = NULL;
	m_emFileFtpStatus = emFtpEnd;
	m_dwTotalFileSize = 0;
	m_valProgress.nPos = 0;
}

CAddrbookExpLogic::~CAddrbookExpLogic()
{
	UnRegMsg();
	UnRegFunc();
}

void CAddrbookExpLogic::RegMsg()
{    

}

void CAddrbookExpLogic::UnRegMsg()
{

}

void CAddrbookExpLogic::RegCBFun()
{   	 
	REG_GOBAL_MEMBER_FUNC( "CAddrbookExpLogic::InitWnd", CAddrbookExpLogic::InitWnd, ADDRBOOKEXPLOGICRPTR, CAddrbookExpLogic);

	REG_GOBAL_MEMBER_FUNC( "CAddrbookExpLogic::OnBtnImportAddrbook", CAddrbookExpLogic::OnBtnImportAddrbook, ADDRBOOKEXPLOGICRPTR, CAddrbookExpLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CAddrbookExpLogic::OnBtnExportAddrbook", CAddrbookExpLogic::OnBtnExportAddrbook, ADDRBOOKEXPLOGICRPTR, CAddrbookExpLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CAddrbookExpLogic::OnBtnImportAddrbookScan", CAddrbookExpLogic::OnBtnImportAddrbookScan, ADDRBOOKEXPLOGICRPTR, CAddrbookExpLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CAddrbookExpLogic::OnBtnExportAddrbookScan", CAddrbookExpLogic::OnBtnExportAddrbookScan, ADDRBOOKEXPLOGICRPTR, CAddrbookExpLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CAddrbookExpLogic::OnBtnExportFolder", CAddrbookExpLogic::OnBtnExportFolder, ADDRBOOKEXPLOGICRPTR, CAddrbookExpLogic ); 

	REG_DEFAULT_WINDOW_MSG( WM_CNSTOOL_FTPADDRBOOKPROGRESS );
	REG_GOBAL_MEMBER_FUNC( "CAddrbookExpLogic::OnTransAddrbookProgress", CAddrbookExpLogic::OnTransAddrbookProgress, ADDRBOOKEXPLOGICRPTR, CAddrbookExpLogic );

	REG_GOBAL_MEMBER_FUNC( "CAddrbookExpLogic::OnExpFolderEditChange", CAddrbookExpLogic::OnExpFolderEditChange, ADDRBOOKEXPLOGICRPTR, CAddrbookExpLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CAddrbookExpLogic::OnImpFolderEditChange", CAddrbookExpLogic::OnImpFolderEditChange, ADDRBOOKEXPLOGICRPTR, CAddrbookExpLogic ); 

}

void CAddrbookExpLogic::UnRegFunc()
{

}

bool CAddrbookExpLogic::InitWnd(  const IArgs & arg )
{   
	CLogicBase::InitWnd( arg );

	m_pWnd = UIFACTORYMGR_PTR->GetWindowPtr( g_strAddrbookExpDlg );
	if ( NULL != m_pWnd )
	{
		return false;
	}

    return true;
}

void CAddrbookExpLogic::Clear()
{
	if ( emFtpEnd != m_emFileFtpStatus )
	{
		m_cFtp.EndFtpFile();
	}

	CleanTransfer();
}

void CAddrbookExpLogic::CleanTransfer()
{	
	if ( emFtpEnd != m_emFileFtpStatus )
	{
		m_cFtp.EndFtpFile();
	}
	
	m_emFileFtpStatus = emFtpEnd;
	m_dwTotalFileSize = 0;

	UIFACTORYMGR_PTR->LoadScheme( "SchmAddrbookImpClean", m_pWndTree );
	UIFACTORYMGR_PTR->LoadScheme( "SchmAddrbookExpClean", m_pWndTree );
}

bool CAddrbookExpLogic::OnBtnImportAddrbookScan( const IArgs & arg )
{ 	
	String strFilter = "��ַ���ļ�(*.kdv)|*.kdv||";  
	String strImpFileFullPath;
	String strImpFileName;
	UIDATAMGR_PTR->OpenFileDialog( strFilter, ADDRBOOK_FILE_NAME, strImpFileFullPath, strImpFileName );
	if ( !strImpFileFullPath.empty() )
	{
		UIFACTORYMGR_PTR->SetCaption( m_strEdtImport, strImpFileFullPath, m_pWndTree );
	}

	return true;
}

bool CAddrbookExpLogic::OnBtnExportAddrbookScan( const IArgs & arg )
{
	HWND hWnd = m_pWnd->GetSafeHwnd();
	String strExpFileFullPath = UIDATAMGR_PTR->OpenBrowseForFolder(ADDRBOOK_FILE_NAME, hWnd);
	if ( !strExpFileFullPath.empty() )
	{
		UIFACTORYMGR_PTR->SetCaption( m_strEdtExport, strExpFileFullPath, m_pWndTree );
	}

	return true;
}

bool CAddrbookExpLogic::OnBtnImportAddrbook( const IArgs & arg )
{
	m_emFtpTransType = em_FTPTRANS_IMPORT;
	
	UploadCore(ADDRBOOK_FILE_NAME);
	
	return true;
}

bool CAddrbookExpLogic::OnBtnExportAddrbook( const IArgs & arg )
{
	m_emFtpTransType = em_FTPTRANS_EXPORT;
	
	DownloadCore(ADDRBOOK_FILE_NAME);

	return true;
}

BOOL CAddrbookExpLogic::DownloadCore(const String& strCheckFileName)
{	
	Value_WindowCaption valFolderName;
	UIFACTORYMGR_PTR->GetPropertyValue( valFolderName, m_strEdtExport, m_pWndTree );
	
	String strSavePath;
	strSavePath = valFolderName.strCaption.c_str();
	if ( !UIDATAMGR_PTR->CheckTransferFile( strSavePath, strCheckFileName ) )
	{
		return true;
	}

	if ( UIDATAMGR_PTR->IsFileExist( strSavePath.c_str() ) )
	{
		MSGBOX_RET nResult = MSGBOX_OK;
		MSG_BOX( nResult, "�����ļ��Ѵ��ڣ��Ƿ񸲸ǣ�");
		if (nResult != MSGBOX_OK)
		{
			return FALSE;
		}
	}

	if ( !UIDATAMGR_PTR->RecusionMkDir(UIDATAMGR_PTR->GetFileFolderPath(strSavePath).c_str()) )
	{
		MSG_BOX_OK("Ŀ¼����ʧ�ܣ��޷����أ�");
		
		return true;
	}
	
	m_cFtp.RegisterMsgHandle( WM_CNSTOOL_FTPADDRBOOKPROGRESS );
	
	u32 dwIp;
	LIBDATAMGRPTR->GetLoginIp(dwIp);
	CString strIpAddr = UIDATAMGR_PTR->GetIpStr( dwIp );
	
	BOOL32 bRet = m_cFtp.SetServerParam( strIpAddr, "admin", "admin" );  
	if ( !bRet )
	{
		MSG_BOX_OK("���ӷ�����ʧ��!");		
		return false;
	}	
	if ( NULL != m_pWnd )
	{
		String strRemoteFile = ADDRBOOK_FILE_PATH;
		strRemoteFile += strCheckFileName;
		if ( !m_cFtp.BeginDownload( m_pWnd->GetSafeHwnd(), strRemoteFile.c_str(), strSavePath.c_str(),
			FTP_TRANSFER_TYPE_BINARY, FTP_AGENT, FALSE ) )
		{
			MSG_BOX_OK("������ַ������ʧ�ܣ���������!");
			
			return false;
		}
	}
	
	return TRUE;
}

BOOL CAddrbookExpLogic::UploadCore(const String& strCheckFileName)
{
	Value_WindowCaption valFolderName;
	UIFACTORYMGR_PTR->GetPropertyValue( valFolderName, m_strEdtImport, m_pWndTree );
	
	String strSavePath;
	strSavePath = valFolderName.strCaption.c_str();
	
	if ( !UIDATAMGR_PTR->IsFileExist( strSavePath.c_str() ) )
	{
		MSG_BOX_OK("ָ���ļ������ڣ��޷�����!");
		return false;
	}

	if ( !UIDATAMGR_PTR->CheckTransferFile( strSavePath, strCheckFileName ) )
	{
		return true;
	}
	
	m_cFtp.RegisterMsgHandle( WM_CNSTOOL_FTPADDRBOOKPROGRESS );
	
	u32 dwIp;
	LIBDATAMGRPTR->GetLoginIp(dwIp);
	CString strIpAddr = UIDATAMGR_PTR->GetIpStr( dwIp );
	
	BOOL32 bRet = m_cFtp.SetServerParam( strIpAddr, "admin", "admin" );  
	
	if ( !bRet )
	{
		MSG_BOX_OK("���ӵ�������ʧ��!");
		
		return false;
	}
	
	if ( NULL != m_pWnd )
	{
		String strRemoteFile = ADDRBOOK_FILE_PATH;
		strRemoteFile += strCheckFileName;
		strRemoteFile += ".temp";
		m_cFtp.SetIsRenameTransFile(TRUE);
		if ( !m_cFtp.BeginUpload( m_pWnd->GetSafeHwnd(), strRemoteFile.c_str(), strSavePath.c_str(),
			FTP_TRANSFER_TYPE_BINARY, FTP_AGENT ) )
		{
			String strError;
			strError.append("�����ַ������ʧ�ܣ���������!");
			MSG_BOX_OK(strError);
			
			return false;
		}
	}
	
	return TRUE;
}

bool CAddrbookExpLogic::OnTransAddrbookProgress( const IArgs & arg  )
{	
	Args_WindowMsg WinMsg = *dynamic_cast<const Args_WindowMsg*>(&arg);
	WindowMsg msg = WinMsg.m_Msg;
	
	m_emFileFtpStatus = static_cast<EmFtpStatus>(msg.wParam);
	
	switch( m_emFileFtpStatus )
	{
	case emFtpBegin:
		{
			m_dwTotalFileSize = static_cast<u32>(msg.lParam);
			
			if ( em_FTPTRANS_IMPORT == m_emFtpTransType )
			{
				UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strProgressImp );
			}
			else
			{
				UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strProgressExp );
			}
		}
		break;
	case emFtpTransfer:
		{
			if ( m_dwTotalFileSize != 0 )
			{
				u32 dwCurrentTransSize = static_cast<u32>(msg.lParam);   //��ǰ����Ĵ�С
				
				float fCurrTransProgress = (float)dwCurrentTransSize/m_dwTotalFileSize*100;
				if ( dwCurrentTransSize < m_dwTotalFileSize )
				{	
					m_valProgress.nPos = (u32)fCurrTransProgress;
					
					if ( em_FTPTRANS_IMPORT == m_emFtpTransType )
					{
						UIFACTORYMGR_PTR->SetPropertyValue( m_valProgress, m_strProgressImp, m_pWndTree );
					}
					else
					{
						UIFACTORYMGR_PTR->SetPropertyValue( m_valProgress, m_strProgressExp, m_pWndTree );
					}
				}
			}
		}
		break;
	case emFtpEnd:
		{
			DWORD dwSuccess = static_cast<DWORD>(msg.lParam);     //FTP�ӿ�0Ϊ�ɹ�  Ĭ��ʧ��
			if ( 0 == dwSuccess )
			{
				if ( em_FTPTRANS_IMPORT == m_emFtpTransType )
				{
					UIFACTORYMGR_PTR->LoadScheme( "SchmTransferEnd", m_pWndTree, m_strProgressImp );
				}
				else
				{
					UIFACTORYMGR_PTR->LoadScheme( "SchmTransferEnd", m_pWndTree, m_strProgressExp );

					MSG_BOX_OK("������ַ���ɹ���");
					UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strProgressExp );
				}
				
				if ( m_emFtpTransType == em_FTPTRANS_IMPORT )
				{
					//����ɹ�   �޸���ʱ�ļ�Ϊʵ���ļ�   ���⴫������������ն˲������쳣
					String strCurTransRemoteTempFileFullPath;
					String strRemoteFile = ADDRBOOK_FILE_PATH;
					strRemoteFile += ADDRBOOK_FILE_NAME;
					strCurTransRemoteTempFileFullPath = strRemoteFile;
					strCurTransRemoteTempFileFullPath += ".temp";				
					if ( !m_cFtp.RenameFtpFile( strCurTransRemoteTempFileFullPath.c_str(), strRemoteFile.c_str() ) )
					{
						MSG_BOX_OK("�����ļ���������ԭ���������ļ�ʧ��!");
						
						UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strProgressImp );
					}
					else
					{
						//��ַ���ɹ��������Ƿ�����
						MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
						MSG_BOX( nMsgBoxRet, "��ַ������ɹ����Ƿ�����cns��������Ч?"  );
						if ( MSGBOX_OK == nMsgBoxRet)
						{
							u16 nRet = COMIFMGRPTR->RebootCns();
							if ( nRet != NO_ERROR )
							{
								//MSG_BOX_OK( "����cns������ʧ��!" );
								WARNMESSAGE( "����cns������ʧ��!" );
							}
						}
					}
				}
			}
			else
			{
				//FtpFindFirstFile Error With 18--û�и����ļ�.���ǻ�ȡԶ���ļ���С��ʱ����ʾ�Ĵ���,���ر�Ftp,֮����Գɹ�
				if ( dwSuccess == 18 )  
				{
					break;
				}
				
				LPTSTR pszMsg = NULL;
				m_cFtp.FormatFtpError( dwSuccess, &pszMsg );
				String strError = "���뵼���ļ���������ԭ��";
				if( dwSuccess == 122 )    //win7���ļ�������ʱ����쳣���ѡ����ݸ�ϵͳ���õ���������̫С��
				{
					strError += "ϵͳ�Ҳ���ָ�����ļ���";
					OspPrintf( TRUE, FALSE, (char*)strError.c_str() );
					MSG_BOX_OK(strError);
					LocalFree( pszMsg );
				}
				else
				{
					strError += pszMsg;
					OspPrintf( TRUE, FALSE, (char*)strError.c_str() );
					MSG_BOX_OK(strError);
					LocalFree( pszMsg );
				}
				
				UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strProgressImp );
			}
			
			m_cFtp.EndFtpFile();
		}
		break;
	default:
		{
		}
		break;
	}

	return true;
}

bool CAddrbookExpLogic::OnBtnExportFolder( const IArgs & arg )
{
	Value_WindowCaption valFolderName;
	UIFACTORYMGR_PTR->GetPropertyValue( valFolderName, m_strEdtExport, m_pWndTree );
	
	String strFileFullPath;
	strFileFullPath = valFolderName.strCaption.c_str();
	
	if ( UIDATAMGR_PTR->IsFileExist( strFileFullPath.c_str() ) )
	{
		CString strParam("/select,");
		strParam += strFileFullPath.c_str();
		u32 dwIns = (u32)ShellExecute( 0, "open", "Explorer.exe", strParam, 0, SW_NORMAL );
		//u32 dwIns = (u32)::ShellExecute( NULL, "open", UIDATAMGR_PTR->GetFileFolderPath(strFileFullPath).c_str(), NULL, NULL, SW_SHOWNORMAL );
		if ( dwIns <= 32 )
		{
			MSG_BOX_OK("Ŀ¼���쳣!");
		}
	}
	else
	{
		MSG_BOX_OK("·���ļ������ڣ���ʧ��!");
	}

	return true;
}

bool CAddrbookExpLogic::OnImpFolderEditChange( const IArgs & arg )
{
	UIFACTORYMGR_PTR->LoadScheme( "SchmAddrbookImpClean", m_pWndTree, m_strProgressImp );
	
	return true;
}

bool CAddrbookExpLogic::OnExpFolderEditChange( const IArgs & arg )
{
	UIFACTORYMGR_PTR->LoadScheme( "SchmAddrbookExpClean", m_pWndTree, m_strProgressExp );
	
	return true;
}
