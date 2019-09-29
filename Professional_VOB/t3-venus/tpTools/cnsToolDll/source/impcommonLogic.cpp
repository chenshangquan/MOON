// impcommonLogic.cpp: implementation of the CImpCommonDlgLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "impcommonLogic.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
static UINT g_nTransTime = 0;

VOID  CALLBACK  CWaitTimerFun( HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime )
{   
	BOOL bOk = KillTimer( NULL, g_nTransTime );	//�ص���ʱ��
	if ( IMPCOMMONLOGICRPTR->GetFtpStatus() != emFtpEnd )
	{
		IMPCOMMONLOGICRPTR->ClearTransFile();
	}
}

CImpCommonDlgLogic::CImpCommonDlgLogic()
:m_strEdtSaveFolder("EdtImpCommonSaveFolder")
,m_strProgressImp("ProgressImpCommon")
,m_strLstUpgradeFile("BoardUpgradeDlg/LstBoardUpgrade")
{
	m_pWnd = NULL;
	m_emFileFtpStatus = emFtpEnd;
	m_dwTotalFileSize = 0;
	m_dwCurSevr = 0;
}

CImpCommonDlgLogic::~CImpCommonDlgLogic()
{
	UnRegMsg();
	UnRegFunc();
}

bool CImpCommonDlgLogic::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );
	
	m_pWnd = UIFACTORYMGR_PTR->GetWindowPtr( g_stcStrImpCommonDlg );
	if ( NULL != m_pWnd )
	{
		return false;
	}
	
    return true;
}

void CImpCommonDlgLogic::RegMsg()
{
	
}

void CImpCommonDlgLogic::UnRegMsg()
{
	
}

void CImpCommonDlgLogic::RegCBFun()
{
	REG_GOBAL_MEMBER_FUNC( "CImpCommonDlgLogic::InitWnd", CImpCommonDlgLogic::InitWnd, IMPCOMMONLOGICRPTR, CImpCommonDlgLogic);
	REG_GOBAL_MEMBER_FUNC( "CImpCommonDlgLogic::OnBtnClose", CImpCommonDlgLogic::OnBtnClose, IMPCOMMONLOGICRPTR, CImpCommonDlgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CImpCommonDlgLogic::OnBtnImportCamCfg", CImpCommonDlgLogic::OnBtnImportCamCfg, IMPCOMMONLOGICRPTR, CImpCommonDlgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CImpCommonDlgLogic::OnBtnUpgradeCns", CImpCommonDlgLogic::OnBtnUpgradeCns, IMPCOMMONLOGICRPTR, CImpCommonDlgLogic );
	REG_DEFAULT_WINDOW_MSG( WM_CNSTOOL_UPLODEPROGRESS );
	REG_GOBAL_MEMBER_FUNC( "CImpCommonDlgLogic::OnUploadProgress", CImpCommonDlgLogic::OnUploadProgress, IMPCOMMONLOGICRPTR, CImpCommonDlgLogic );
	REG_GOBAL_MEMBER_FUNC( "CImpCommonDlgLogic::OnBtnImportScan", CImpCommonDlgLogic::OnBtnImportScan, IMPCOMMONLOGICRPTR, CImpCommonDlgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CImpCommonDlgLogic::OnFolderEditChange", CImpCommonDlgLogic::OnFolderEditChange, IMPCOMMONLOGICRPTR, CImpCommonDlgLogic ); 

}

void CImpCommonDlgLogic::UnRegFunc()
{
	
}

void CImpCommonDlgLogic::Clear()
{
	BOOL bOk = KillTimer(NULL,g_nTransTime);	//�ص���ʱ��
	CleanTransfer();
	
	s32 nResult = 0;
	UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrImpCommonDlg );
}

bool CImpCommonDlgLogic::OnBtnClose( const IArgs & arg )
{
	CleanTransfer();
	
	s32 nResult = 0;
	UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrImpCommonDlg );
	
	return true;
}

bool CImpCommonDlgLogic::OnUploadProgress( const IArgs & arg )
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
					
					UIFACTORYMGR_PTR->SetPropertyValue( m_valProgress, m_strProgressImp, m_pWndTree );
				}
			}
		}
		break;
	case emFtpEnd:
		{
			BOOL bOk = KillTimer( NULL, g_nTransTime );	//�ص���ʱ��
			DWORD dwSuccess = static_cast<DWORD>(msg.lParam);     //FTP�ӿ�0Ϊ�ɹ�  Ĭ��ʧ��
			if ( 0 == dwSuccess )
			{
				UIFACTORYMGR_PTR->LoadScheme( "SchmTransferEnd", m_pWndTree );
				
				//����ɹ�   �޸���ʱ�ļ�Ϊʵ���ļ�   ���⴫������������ն˲������쳣
				String strCurTransRemoteTempFileFullPath;
				strCurTransRemoteTempFileFullPath.append(m_strCurTransRemoteFileFullPath).append(".temp");
				if ( !m_cFtp.RenameFtpFile( strCurTransRemoteTempFileFullPath.c_str(), m_strCurTransRemoteFileFullPath.c_str() ) )
				{
					MSG_BOX_OK("�����ļ�����������ԭ���������ļ�ʧ�ܣ�");
					UIFACTORYMGR_PTR->LoadScheme( "SchmTransferEnd", m_pWndTree );
					UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strProgressImp );
				}
				
				String strCaption;    //�����ļ��ϴ��ɹ�   ����������Ϣ��������
				UIFACTORYMGR_PTR->GetCaption( "ImpCommonDlg/StcImpCommonCap", strCaption, NULL );
				if ( "����T300" == strCaption )
				{
					BOOL bInConf = LIBDATAMGRPTR->IsInConf();
					if ( bInConf )
					{
						MSG_BOX_OK("����ʧ��:��ǰ�᳡���ڿ��ᣬ���Ժ��ٴ�����");
						s32 nResult = 0;
						UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrImpCommonDlg );
					}
					else
					{
// 						MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
// 						MSG_BOX( nMsgBoxRet, "�����ļ��ѵ��룬��Ҫ����������Ч���Ƿ�����������" );	
// 						if ( MSGBOX_OK == nMsgBoxRet )
// 						{
// 							bInConf = LIBDATAMGRPTR->IsInConf();
// 							if ( bInConf )
// 							{
// 								MSG_BOX_OK("����ʧ��:��ǰ�᳡���ڿ��ᣬ���Ժ��ٴ�����");
// 								s32 nResult = 0;
// 								UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrImpCommonDlg );
// 							}
// 							else
// 							{
								TTPFTPFileInfo tVerFileInfo;
								String strPathName = UPDATEFILE_PATH_NAME;
								strPathName += m_strImpFileName;
								tVerFileInfo.byFilePathLen = sprintf(tVerFileInfo.achFilePath,"%s",strPathName.c_str());
								u16 wRe = COMIFMGRPTR->UpgradeCns(tVerFileInfo);
								if ( wRe != 0 )
								{
									MSG_BOX_OK("����ʧ��:����T300�����ʧ��");
								}
								else
								{
									UIFACTORYMGR_PTR->EnableWindow( "BtnImpCommonFolderScan", FALSE, m_pWndTree );
									UIFACTORYMGR_PTR->EnableWindow( "BtnImpCommonExport", FALSE, m_pWndTree );
									UIFACTORYMGR_PTR->EnableWindow( "BtnImpCommonDlgClose", FALSE, m_pWndTree );
								}
//							}
//						}
//						else
//						{
//							s32 nResult = 0;
//							UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrImpCommonDlg );
//						}
					}
				}
				else if ( "�������������" == strCaption )
				{
					COMIFMGRPTR->SetLoadCameraFileNty();

					MSG_BOX_OK("��������������ɹ���");
					UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strProgressImp );
				}
			}
			else
			{
				LPTSTR pszMsg = NULL;
				m_cFtp.FormatFtpError( dwSuccess, &pszMsg );
				OspPrintf( TRUE, FALSE, "�����ļ�����������ԭ��%s��", pszMsg );
				//MSG_BOX_OK(pszMsg);---  ���ӵ�ʱ�������Ϣ�հ�,�ݲ�����
				String strCurTransRemoteTempFileFullPath;
				strCurTransRemoteTempFileFullPath.append(m_strCurTransRemoteFileFullPath).append(".temp");
				m_cFtp.DeleteFile(strCurTransRemoteTempFileFullPath.c_str());
				UIFACTORYMGR_PTR->LoadScheme( "SchmTransferEnd", m_pWndTree );
				UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strProgressImp  );
				LocalFree( pszMsg );
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

bool CImpCommonDlgLogic::OnBtnImportScan( const IArgs & arg )
{
	String strFile;
	String strCaption;
	String strFilter;
	UIFACTORYMGR_PTR->GetCaption( "ImpCommonDlg/StcImpCommonCap", strCaption, NULL );
	if ( "�������������" == strCaption )
	{
		strFile = /*CNSCAMERA_FILE_NAME*/"";  //����һ����,������������ļ���
		strFilter = "����������ļ�(cameracfg.ini)|cameracfg.ini||";  
	}
	if ( "����T300" == strCaption )
	{
		strFile = /*CNSUPGRADE_FILE_NAME*/"t300.bin";	//����һ����,������T300�����ļ���,��Ϊ��2��,�ݲ�������
		strFilter = "t300�����ļ�(t300.bin;t300.bin.gz)|t300.bin;t300.bin.gz||";
	}
	
	String strImpFileFullPath;
	UIDATAMGR_PTR->OpenFileDialog( strFilter, strFile, strImpFileFullPath, m_strImpFileName );
	if ( !strImpFileFullPath.empty() )
	{
		UIFACTORYMGR_PTR->SetCaption( m_strEdtSaveFolder, strImpFileFullPath, m_pWndTree );
	}
	if ( m_strImpFileName.empty() || strImpFileFullPath.empty() )
	{
		return false;
	}
	//�������ӵ��ļ����ļ��б�
	UIFACTORYMGR_PTR->SetCaption( "UpgradeDlg/StcUpSerName", m_strImpFileName, m_pWndTree );
	s64 nSize = UIDATAMGR_PTR->GetFileSize(strImpFileFullPath);
	s8 chSize[8] = {0};
	String strSize;
	if ( 1024 > nSize )
	{
		sprintf( chSize, "%u", nSize );
		strSize = chSize;
		strSize += "byte";
	}
	else if ( 1024 < nSize && nSize < 1024*1024 )
	{
		float fSize = 1.0*nSize/1024;
		sprintf( chSize, "%.1f", fSize );
		strSize = chSize;
		strSize += "Kb";
	}
	else if ( 1024*1024 < nSize )
	{
		float fSize = 1.0*nSize/(1024*1024);
		sprintf( chSize, "%.1f", fSize );
		strSize = chSize;
		strSize += "M";
	}
 	UIFACTORYMGR_PTR->SetCaption( "UpgradeDlg/StcUpSerByte", strSize, m_pWndTree );
// 	TUmsToolFile tFileList;
// 	strncpy( tFileList.chFileName, strImpFileName.c_str(), _MAX_FNAME );
// 	strncpy( tFileList.chFileFullPath, strImpFileFullPath.c_str(), MAX_PATH );
// 	tFileList.nFileSize = CUmstoolCommon::GetFileSize(tFileList.chFileFullPath);
// 	if ( tFileList.nFileSize > 0 )
// 	{
// 		m_vecUpgradeFile.push_back(tFileList);
// 		UpdateUpgradeFileList();
// 	}
	
	return true;
}

bool CImpCommonDlgLogic::OnFolderEditChange( const IArgs & arg )
{
	UIFACTORYMGR_PTR->LoadScheme( "SchmImpCommonClean", m_pWndTree, m_strProgressImp );
	
	return true;	
}

bool CImpCommonDlgLogic::OnBtnUpgradeCns( const IArgs & arg )
{
	Value_WindowCaption valFolderName;
	UIFACTORYMGR_PTR->GetPropertyValue( valFolderName, m_strEdtSaveFolder, m_pWndTree );
	
	String strFileFullPath;
	strFileFullPath = valFolderName.strCaption.c_str();
	
	UploadCore( /*CNSUPGRADE_FILE_PATH*/UPDATEFILE_PATH_NAME, strFileFullPath, /*CNSUPGRADE_FILE_NAME*/m_strImpFileName );  //������Ҫ��������
	
	return true;
}

BOOL CImpCommonDlgLogic::UploadCore( const String& strRemotePath, const String& strLocalFile, const String& strCheckFileName, BOOL bIsDefServ /*= TRUE */ )
{
	if ( !UIDATAMGR_PTR->IsFileExist( strLocalFile.c_str() ) )
	{
		MSG_BOX_OK("ָ���ļ������ڣ��޷�����!");
		return false;
	}
	
	if ( !UIDATAMGR_PTR->CheckTransferFile( strLocalFile, strCheckFileName ) )
	{
		return false;
	}
	
	m_cFtp.RegisterMsgHandle( WM_CNSTOOL_UPLODEPROGRESS );
	
	CString strIpAddr;
	if ( bIsDefServ )
	{
		u32 dwIp;
		LIBDATAMGRPTR->GetLoginIp(dwIp);
		strIpAddr = UIDATAMGR_PTR->GetIpStr( dwIp );
	}
	else
	{
		strIpAddr = UIDATAMGR_PTR->GetIpStr( GetSevrIpAddr() );
	}
	
	BOOL32 bRet = m_cFtp.SetServerParam( strIpAddr, "admin", "admin" );
	if ( !bRet )
	{
		MSG_BOX_OK("���ӷ�����ʧ��!");
		
		return false;
	}
	
	if ( NULL != m_pWnd )
	{
		String strRemoteFilePath = strRemotePath;
		strRemoteFilePath += strCheckFileName;
		m_strCurTransRemoteFileFullPath = strRemoteFilePath;
		strRemoteFilePath += ".temp";
		m_cFtp.SetIsRenameTransFile(TRUE);
		if ( !m_cFtp.BeginUpload( m_pWnd->GetSafeHwnd(), strRemoteFilePath.c_str(), strLocalFile.c_str(),
			FTP_TRANSFER_TYPE_BINARY, FTP_AGENT ) )
		{
			MSG_BOX_OK("�������ʧ��!");
			
			return false;
		}
		//���ö�ʱ�� ʱ����30s
		g_nTransTime = SetTimer( NULL, 0, 30000, CWaitTimerFun );
	}
	
	return TRUE;
}

void CImpCommonDlgLogic::CleanTransfer()
{
	if ( emFtpEnd != m_emFileFtpStatus )
	{
		m_cFtp.EndFtpFile();
	}
	
	m_emFileFtpStatus = emFtpEnd;
	m_dwTotalFileSize = 0;
	m_dwCurSevr = 0;
	
	m_strCurTransRemoteFileFullPath = "";
	m_strImpFileName = "";
	//UpdateUpgradeFileList();
	
	UIFACTORYMGR_PTR->LoadScheme( "SchmImpCommonClean", m_pWndTree );
}
// 
// void CImpCommonDlgLogic::UpdateUpgradeFileList()
// {
// 	if ( NULL == m_pWndTree  )
// 	{
// 		return;
// 	}
// 	
// 	Value_ItemBoardUpgrade itemBoardUpgrade( &m_vecUpgradeFile );
// 	UIFACTORYMGR_PTR->SetPropertyValue( itemBoardUpgrade, m_strLstUpgradeFile, m_pWndTree );
// }

bool CImpCommonDlgLogic::OnBtnImportCamCfg( const IArgs & arg )
{
	Value_WindowCaption valFolderName;
	UIFACTORYMGR_PTR->GetPropertyValue( valFolderName, m_strEdtSaveFolder, m_pWndTree );
	
	String strFileFullPath;
	strFileFullPath = valFolderName.strCaption.c_str();
	
	UploadCore( CNSCAMERA_FILE_PATH, strFileFullPath, CNSCAMERA_FILE_NAME );
	
	return true;
}

void CImpCommonDlgLogic::ClearTransFile()
{
	if ( m_cFtp.GetIsRenameTransFile() && m_emFileFtpStatus == emFtpTransfer )
	{
		String strCurTransRemoteTempFileFullPath;
		strCurTransRemoteTempFileFullPath.append(m_strCurTransRemoteFileFullPath).append(".temp");
		m_cFtp.DeleteFile(strCurTransRemoteTempFileFullPath.c_str());
	}
	MSG_BOX_OK("�����ļ�����������ԭ�򣺳�ʱ");
	UIFACTORYMGR_PTR->LoadScheme( "SchmTransferEnd", m_pWndTree );
	UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strProgressImp );
	m_cFtp.EndFtpFile();
}