// Expcommondlglogic.cpp: Explementation of the CExpCommonDlgLogic class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "umstooldll.h"
#include "expcommondlglogic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CExpCommonDlgLogic::CExpCommonDlgLogic():
m_strEdtSaveFolder("EdtExpCommonSaveFolder"),
m_strProgressExp("ProgressExpCommon")
{
	m_pWnd = NULL;
	m_emFileFtpStatus = emFtpEnd;
	m_dwTotalFileSize = 0;
}

CExpCommonDlgLogic::~CExpCommonDlgLogic()
{
	UnRegMsg();
	UnRegFunc();
}

void CExpCommonDlgLogic::RegMsg()
{    
	REG_MSG_HANDLER( UI_UMSTOOL_EXPAUTH_RSP, CExpCommonDlgLogic::OnExpAuthRsp, EXPCOMMONLOGICRPTR, CExpCommonDlgLogic );
}

void CExpCommonDlgLogic::UnRegMsg()
{

}

bool CExpCommonDlgLogic::RegCBFun()
{   	 
	REG_GOBAL_MEMBER_FUNC( "CExpCommonDlgLogic::InitWnd", CExpCommonDlgLogic::InitWnd, EXPCOMMONLOGICRPTR, CExpCommonDlgLogic);
	REG_GOBAL_MEMBER_FUNC( "CExpCommonDlgLogic::OnBtnClose", CExpCommonDlgLogic::OnBtnClose, EXPCOMMONLOGICRPTR, CExpCommonDlgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CExpCommonDlgLogic::OnBtnDownloadLogWork", CExpCommonDlgLogic::OnBtnDownloadLogWork, EXPCOMMONLOGICRPTR, CExpCommonDlgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CExpCommonDlgLogic::OnBtnExportAuthWork", CExpCommonDlgLogic::OnBtnExportAuthWork, EXPCOMMONLOGICRPTR, CExpCommonDlgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CExpCommonDlgLogic::OnBtnExportConfigWork", CExpCommonDlgLogic::OnBtnExportConfigWork, EXPCOMMONLOGICRPTR, CExpCommonDlgLogic ); 
	REG_DEFAULT_WINDOW_MSG( WM_UMSTOOL_FTPLOGPROGRESS );
	REG_GOBAL_MEMBER_FUNC( "CExpCommonDlgLogic::OnDownloadProgress", CExpCommonDlgLogic::OnDownloadProgress, EXPCOMMONLOGICRPTR, CExpCommonDlgLogic );
	REG_GOBAL_MEMBER_FUNC( "CExpCommonDlgLogic::OnBtnExportScan", CExpCommonDlgLogic::OnBtnExportScan, EXPCOMMONLOGICRPTR, CExpCommonDlgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CExpCommonDlgLogic::OnBtnOpenFolder", CExpCommonDlgLogic::OnBtnOpenFolder, EXPCOMMONLOGICRPTR, CExpCommonDlgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CExpCommonDlgLogic::OnFolderEditChange", CExpCommonDlgLogic::OnFolderEditChange, EXPCOMMONLOGICRPTR, CExpCommonDlgLogic ); 
	
	return true;
}

bool CExpCommonDlgLogic::UnRegFunc()
{

	return true;
}

bool CExpCommonDlgLogic::InitWnd(  const IArgs & arg )
{   
	CWndLogicBase::InitWnd( arg );

	m_pWnd = UIFACTORYMGR_PTR->GetWindowPtr( g_stcStrExpCommonDlg );
	if ( NULL != m_pWnd )
	{
		return false;
	}

    return true;
}

void CExpCommonDlgLogic::Clear()
{
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

void CExpCommonDlgLogic::CleanTransfer()
{	
	if ( emFtpEnd != m_emFileFtpStatus )
	{
		m_cFtp.EndFtpFile();
	}

	m_emFileFtpStatus = emFtpEnd;
	m_dwTotalFileSize = 0;

	UIFACTORYMGR_PTR->LoadScheme( "SchmExpCommonClean", m_pWndTree );
}

bool CExpCommonDlgLogic::OnBtnDownloadLogWork( const IArgs & arg )
{
	DownloadCore( UMSLOG_FILE_PATH, UMSLOG_FILE_NAME );

	return true;
}

bool CExpCommonDlgLogic::OnBtnExportAuthWork( const IArgs & arg )
{
	u16 nRet = COMMONMGRIFPTR->ExportAuthReq();;
	if ( nRet != NO_ERROR )
	{
		MESSAGEWND( "������Ȩums������ʧ�ܣ�" );
	}

	return true;
}

bool CExpCommonDlgLogic::OnBtnExportConfigWork( const IArgs & arg )
{
	DownloadCore(UMSCONFIG_FILE_PATH, UMSCONFIG_FILE_NAME );

	return true;
}	

BOOL CExpCommonDlgLogic::DownloadCore( const String& strFilePath, const String& strCheckFileName )
{
	Value_WindowCaption valFolderName;
	UIFACTORYMGR_PTR->GetPropertyValue( valFolderName, m_strEdtSaveFolder, m_pWndTree );
	
	String strSavePath;
	strSavePath = valFolderName.strCaption.c_str();

	if ( !CUmstoolCommon::CheckTransferFile( strSavePath, strCheckFileName ) )
	{
		return FALSE;
	}

	if ( CUmstoolCommon::IsFileExist( strSavePath.c_str() ) )
	{
		MSGBOX_RET nResult = MSGBOX_OK;
		MSG_BOX( nResult, "�����ļ��Ѵ��ڣ��Ƿ񸲸ǣ�");
		if (nResult != MSGBOX_OK)
		{
			return FALSE;
		}
	}
	
	if ( !CUmstoolCommon::RecusionMkDir(CUmstoolCommon::GetFileFolderPath(strSavePath).c_str()) )
	{
		MSG_BOX_OK("Ŀ¼����ʧ�ܣ��޷�������");
		
		return FALSE;
	}
	
	m_cFtp.RegisterMsgHandle( WM_UMSTOOL_FTPLOGPROGRESS );
	
	TLoginInfo tLoginInfo = COMMONMGRIFPTR->GetLoginInfo();
	CString strIpAddr = CUmstoolCommon::GetIpStr( htonl(tLoginInfo.dwIp) );
	
	BOOL32 bRet = m_cFtp.SetServerParam( strIpAddr, "admin", "admin" );
	if ( !bRet )
	{
		MSG_BOX_OK("���ӷ�����ʧ�ܣ�");
		
		return FALSE;
	}
	
	if ( NULL != m_pWnd )
	{
		String strRemoteFile = strFilePath;
		strRemoteFile += strCheckFileName;
		if ( !m_cFtp.BeginDownload( m_pWnd->GetSafeHwnd(), strRemoteFile.c_str(), strSavePath.c_str(),
			FTP_TRANSFER_TYPE_BINARY, FTP_AGENT, FALSE ) )
		{
			MSG_BOX_OK("��������ʧ�ܣ���������");
			
			return FALSE;
		}
	}

	return TRUE;
}

bool CExpCommonDlgLogic::OnDownloadProgress( const IArgs & arg  )
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

				String strCaption;
				UIFACTORYMGR_PTR->GetCaption( "ExpCommonDlg/StcExpCommonCap", strCaption, NULL );
				if ( "������־" == strCaption )
				{
					MSG_BOX_OK("������־�ɹ���");

				}
				else if ( "������Ȩ" == strCaption )
				{
					MSG_BOX_OK("������Ȩ�ɹ���");
				}
				else if ( "��������" == strCaption )
				{
					MSG_BOX_OK("�������óɹ���");
				}

				UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strProgressExp );
			}
			else
			{
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

bool CExpCommonDlgLogic::OnBtnExportScan( const IArgs & arg )
{
	String strFile;
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( "ExpCommonDlg/StcExpCommonCap", strCaption, NULL );
	if ( "������־" == strCaption )
	{
		strFile+= UMSLOG_FILE_NAME;  
	}
	else if ( "������Ȩ" == strCaption )
	{
		strFile+= AUTH_FILE_NAME_EXP;
	}
	else if ( "��������" == strCaption )
	{
		strFile+= UMSCONFIG_FILE_NAME;  
	}

	HWND hWnd = m_pWnd->GetSafeHwnd();
	String strExpFileFullPath = CUmstoolCommon::OpenBrowseForFolder(strFile, hWnd);
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
	
	CString strFileFullPath;
	strFileFullPath = valFolderName.strCaption.c_str();

	if ( CUmstoolCommon::IsFileExist( strFileFullPath ) )
	{
 		CString strParam("/select,");
 		strParam += strFileFullPath;

		u32 dwIns = (u32)ShellExecute( 0, "open", "Explorer.exe", strParam, 0, SW_NORMAL );
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

HRESULT CExpCommonDlgLogic::OnExpAuthRsp( WPARAM wparam, LPARAM lparam)
{
	BOOL32 bRet = (BOOL32)wparam;
	s8 strPathAll[255] = {0};
	s8* pStrPathAll = (s8*)lparam;

	if ( pStrPathAll )
	{
		strncpy( strPathAll, pStrPathAll, 255 );
	}

	CString str = strPathAll;
	int nPos = str.ReverseFind('/');
	CString strPath = str.Left(nPos + 1);
	CString strName = str.Right(str.GetLength() - nPos - 1);


	DownloadCore( (LPCTSTR)strPath, (LPCTSTR)strName );

	return 0;
}