// expcommonLogic.cpp: implementation of the CExpCommonDlgLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "expcommonLogic.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CExpCommonDlgLogic::CExpCommonDlgLogic()
:m_strEdtSaveFolder("EdtExpCommonSaveFolder")
,m_strProgressExp("ProgressExpCommon")
{
	m_pWnd = NULL;
	m_emFileFtpStatus = emFtpEnd;
	m_dwTotalFileSize = 0;
	m_nCount = 0;
	m_vctDownFile.clear();
}

CExpCommonDlgLogic::~CExpCommonDlgLogic()
{
	UnRegMsg();
	UnRegFunc();
}

void CExpCommonDlgLogic::RegMsg()
{
	
}

void CExpCommonDlgLogic::UnRegMsg()
{
	
}

void CExpCommonDlgLogic::RegCBFun()
{
	REG_GOBAL_MEMBER_FUNC( "CExpCommonDlgLogic::InitWnd", CExpCommonDlgLogic::InitWnd, EXPCOMMONLOGICRPTR, CExpCommonDlgLogic);
	REG_GOBAL_MEMBER_FUNC( "CExpCommonDlgLogic::OnBtnClose", CExpCommonDlgLogic::OnBtnClose, EXPCOMMONLOGICRPTR, CExpCommonDlgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CExpCommonDlgLogic::OnBtnDownloadLogWork", CExpCommonDlgLogic::OnBtnDownloadLogWork, EXPCOMMONLOGICRPTR, CExpCommonDlgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CExpCommonDlgLogic::OnBtnExportConfigWork", CExpCommonDlgLogic::OnBtnExportConfigWork, EXPCOMMONLOGICRPTR, CExpCommonDlgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CExpCommonDlgLogic::OnBtnExportCameraCfg", CExpCommonDlgLogic::OnBtnExportCameraCfg, EXPCOMMONLOGICRPTR, CExpCommonDlgLogic ); 
	REG_DEFAULT_WINDOW_MSG( WM_CNSTOOL_FTPLOGPROGRESS );
	REG_GOBAL_MEMBER_FUNC( "CExpCommonDlgLogic::OnDownloadProgress", CExpCommonDlgLogic::OnDownloadProgress, EXPCOMMONLOGICRPTR, CExpCommonDlgLogic );
	REG_GOBAL_MEMBER_FUNC( "CExpCommonDlgLogic::OnBtnExportScan", CExpCommonDlgLogic::OnBtnExportScan, EXPCOMMONLOGICRPTR, CExpCommonDlgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CExpCommonDlgLogic::OnBtnOpenFolder", CExpCommonDlgLogic::OnBtnOpenFolder, EXPCOMMONLOGICRPTR, CExpCommonDlgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CExpCommonDlgLogic::OnFolderEditChange", CExpCommonDlgLogic::OnFolderEditChange, EXPCOMMONLOGICRPTR, CExpCommonDlgLogic ); 
}

void CExpCommonDlgLogic::UnRegFunc()
{
	
}

bool CExpCommonDlgLogic::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );
	
	m_pWnd = UIFACTORYMGR_PTR->GetWindowPtr( g_stcStrExpCommonDlg );
	if ( NULL != m_pWnd )
	{
		return false;
	}

	return true;
}

void CExpCommonDlgLogic::Clear()
{
	 if ( NULL== m_pWndTree )
	 {
		 return;
	 }

	s32 nResult = 0;
	UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrExpCommonDlg );
	
	CleanTransfer();	
}

bool CExpCommonDlgLogic::OnBtnClose( const IArgs & arg )
{
	s32 nResult = 0;
	UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrExpCommonDlg );
	
	CleanTransfer();
	
	return true;
}

bool CExpCommonDlgLogic::OnBtnDownloadLogWork( const IArgs & arg )
{
//	DownloadCore( CNSLOG_FILE_PATH, CNSLOG_FILE_NAME );
	//m_lstFtpFile.clear();
    //m_dwTotalFileSize = 0;
    
    //m_pThread = AfxBeginThread(ThreadDwonLoad, this); 
	m_cFtp.RegisterMsgHandle( WM_CNSTOOL_FTPLOGPROGRESS );
	
	u32 dwIp;
	LIBDATAMGRPTR->GetLoginIp(dwIp);
	CString strIpAddr = UIDATAMGR_PTR->GetIpStr( dwIp );
	
	BOOL32 bRet = m_cFtp.SetServerParam( strIpAddr, "admin", "admin" );
	if ( !bRet )
	{
		MSG_BOX_OK("���ӷ�����ʧ�ܣ�");
		
		return false;
	}

	if ( m_cFtp.ConnectServer() )
	{
		m_vctDownFile.clear();
		if ( m_cFtp.FindfFtpFile( CNSLOG_FILE_PATH, "kdvlog_0.txt" ) )
		{
			m_nCount = 1;
			m_vctDownFile.push_back( "kdvlog_0.txt" );
		}
		if ( m_cFtp.FindfFtpFile( CNSLOG_FILE_PATH, "kdvlog_1.txt" ) )
		{
			m_nCount = 2;
			m_vctDownFile.push_back( "kdvlog_1.txt" );
		}
		if ( m_cFtp.FindfFtpFile( CNSLOG_FILE_PATH, "kdvlog_2.txt" ) )
		{
			m_nCount = 3;
			m_vctDownFile.push_back( "kdvlog_2.txt" );
		}

		DownloadCore( CNSLOG_FILE_PATH, m_vctDownFile.at(0) );
		
		//CString str;
		//str.Format( "1 / %d", m_nCount );
		//UIFACTORYMGR_PTR->SetCaption( "StcFileCount", (LPCSTR)str, m_pWndTree );
	}
	return true;	
}

bool CExpCommonDlgLogic::OnBtnExportConfigWork( const IArgs & arg )
{
	DownloadCore(CNSCONFIG_FILE_PATH, CNSCONFIG_FILE_NAME );
	
	return true;
}

bool CExpCommonDlgLogic::OnBtnExportCameraCfg( const IArgs & arg )
{
	DownloadCore(CNSCAMERA_FILE_PATH, CNSCAMERA_FILE_NAME );
	
	return true;
}

bool CExpCommonDlgLogic::OnDownloadProgress( const IArgs & arg )
{
	Args_WindowMsg WinMsg = *dynamic_cast<const Args_WindowMsg*>(&arg);
	WindowMsg msg = WinMsg.m_Msg;
	
	m_emFileFtpStatus = static_cast<EmFtpStatus>(msg.wParam);
	
	switch( m_emFileFtpStatus )
	{
	case emFtpBegin:
		{
			m_dwTotalFileSize = static_cast<u32>(msg.lParam);
			
			UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree );
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
					
					UIFACTORYMGR_PTR->SetPropertyValue( m_valProgress, m_strProgressExp, m_pWndTree );
				}
			}
		}
		break;
	case emFtpEnd:
		{
			DWORD dwSuccess = static_cast<DWORD>(msg.lParam);     //FTP�ӿ�0Ϊ�ɹ�  Ĭ��ʧ��
			if ( 0 == dwSuccess )
			{
				UIFACTORYMGR_PTR->LoadScheme( "SchmTransferEnd", m_pWndTree );

				if ( m_vctDownFile.size() > 0 )
				{
					vector<String>::iterator itr = m_vctDownFile.begin();
					m_vctDownFile.erase(itr);
					u32 n= m_vctDownFile.size();
					//CString str;
					//str.Format( "%d / %d", m_nCount-n+1, m_nCount );
					if ( n > 0 )
					{	
						//UIFACTORYMGR_PTR->SetCaption( "StcFileCount", (LPCSTR)str, m_pWndTree, true );
						DownloadCore( CNSLOG_FILE_PATH, m_vctDownFile.at(0) );
					}
					else
					{
						m_cFtp.EndFtpFile();
					}
				} 	

				String strCaption;
				UIFACTORYMGR_PTR->GetCaption( "ExpCommonDlg/StcExpCommonCap", strCaption, NULL );
				if ( "������־" == strCaption )
				{
					MSG_BOX_OK("������־�ɹ���");
				}
				else if ( "��������" == strCaption )
				{
					MSG_BOX_OK("�������óɹ���");
				}
				else if ( "�������������" == strCaption )
				{
					MSG_BOX_OK("��������������ɹ���");
				}

				UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strProgressExp );

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
				UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBreak", m_pWndTree );
				m_cFtp.EndFtpFile();
			}	
			
		}
		break;
	default:
		{
		}
		break;
	}
	
	return true;
}

bool CExpCommonDlgLogic::OnBtnExportScan( const IArgs & arg )
{
	String strFile;
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( "ExpCommonDlg/StcExpCommonCap", strCaption, NULL );
	if ( "������־" == strCaption )
	{
		strFile+= "";  
	}
	else if ( "��������" == strCaption )
	{
		strFile+= CNSCONFIG_FILE_NAME;  
	}
	else if ( "�������������" == strCaption )
	{
		strFile+= CNSCAMERA_FILE_NAME;  
	}
	HWND hWnd = m_pWnd->GetSafeHwnd();
	String strExpFileFullPath = UIDATAMGR_PTR->OpenBrowseForFolder(strFile, hWnd);
	if ( !strExpFileFullPath.empty() )
	{
		UIFACTORYMGR_PTR->SetCaption( m_strEdtSaveFolder, strExpFileFullPath, m_pWndTree );
	}
	
	return true;
}

bool CExpCommonDlgLogic::OnBtnOpenFolder( const IArgs & arg )
{
	Value_WindowCaption valFolderName;
	UIFACTORYMGR_PTR->GetPropertyValue( valFolderName, m_strEdtSaveFolder, m_pWndTree );
	
	String strFileFullPath;
	strFileFullPath = valFolderName.strCaption.c_str();

	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( "ExpCommonDlg/StcExpCommonCap", strCaption, NULL );
	if ( "������־" == strCaption )
	{
		strFileFullPath+= "kdvlog_0.txt";  
	}	

	if ( UIDATAMGR_PTR->IsFileExist( strFileFullPath.c_str() ) )
	{
		CString strParam("/select,");
		strParam += strFileFullPath.c_str();
		u32 dwIns = (u32)ShellExecute( 0, "open", "Explorer.exe", strParam, 0, SW_NORMAL );
		//u32 dwIns = (u32)::ShellExecute( NULL, "open", UIDATAMGR_PTR->GetFileFolderPath(strFileFullPath).c_str(), NULL, NULL, SW_SHOWNORMAL );
		if ( dwIns <= 32 )
		{
			MSG_BOX_OK("Ŀ¼���쳣��");
		}
	}
	else
	{
		MSG_BOX_OK("·���ļ������ڣ���ʧ�ܣ�");
	}
	
	return true;
}

bool CExpCommonDlgLogic::OnFolderEditChange( const IArgs & arg )
{
	UIFACTORYMGR_PTR->LoadScheme( "SchmExpCommonClean", m_pWndTree, m_strProgressExp );
	
	return true;
}

void CExpCommonDlgLogic::CleanTransfer()
{
	if ( NULL == m_pWndTree )
	{
		return;
	}

	if ( emFtpEnd != m_emFileFtpStatus )
	{
		m_cFtp.EndFtpFile();
	}
	
	m_emFileFtpStatus = emFtpEnd;
	m_dwTotalFileSize = 0;
	
	UIFACTORYMGR_PTR->LoadScheme( "SchmExpCommonClean", m_pWndTree );
}

BOOL CExpCommonDlgLogic::DownloadCore( const String& strFilePath, const String& strCheckFileName )
{
	Value_WindowCaption valFolderName;
	UIFACTORYMGR_PTR->GetPropertyValue( valFolderName, m_strEdtSaveFolder, m_pWndTree );
	
	String strSavePath;
	strSavePath = valFolderName.strCaption.c_str();

	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( "ExpCommonDlg/StcExpCommonCap", strCaption, NULL );
	if ( "������־" == strCaption )
	{
		strSavePath+= m_vctDownFile.at(0);  
	}	
// 	if ( !UIDATAMGR_PTR->CheckTransferFile( strSavePath, strCheckFileName ) )
// 	{
// 		return true;
// 	}
	
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
		MSG_BOX_OK("Ŀ¼����ʧ�ܣ��޷�������");
		
		return true;
	}
	
	m_cFtp.RegisterMsgHandle( WM_CNSTOOL_FTPLOGPROGRESS );
	
	u32 dwIp;
	LIBDATAMGRPTR->GetLoginIp(dwIp);
	CString strIpAddr = UIDATAMGR_PTR->GetIpStr( dwIp );
		
	BOOL32 bRet = m_cFtp.SetServerParam( strIpAddr, "admin", "admin" );
	if ( !bRet )
	{
		MSG_BOX_OK("���ӷ�����ʧ�ܣ�");
		
		return false;
	}
	
	if ( NULL != m_pWnd )
	{
		String strRemoteFile = strFilePath;
		strRemoteFile += strCheckFileName;
		if ( !m_cFtp.BeginDownload( m_pWnd->GetSafeHwnd(), strRemoteFile.c_str(), strSavePath.c_str(),
			FTP_TRANSFER_TYPE_BINARY, FTP_AGENT, FALSE ) )
		{
			MSG_BOX_OK("��������ʧ�ܣ���������");
			
			return false;
		}
	}
	
	return TRUE;
}