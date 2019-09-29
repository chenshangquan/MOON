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
	BOOL bOk = KillTimer( NULL, g_nTransTime );	//关掉定时器
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
	BOOL bOk = KillTimer(NULL,g_nTransTime);	//关掉定时器
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
				u32 dwCurrentTransSize = static_cast<u32>(msg.lParam);   //当前传输的大小
				
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
			BOOL bOk = KillTimer( NULL, g_nTransTime );	//关掉定时器
			DWORD dwSuccess = static_cast<DWORD>(msg.lParam);     //FTP接口0为成功  默认失败
			if ( 0 == dwSuccess )
			{
				UIFACTORYMGR_PTR->LoadScheme( "SchmTransferEnd", m_pWndTree );
				
				//导入成功   修改临时文件为实际文件   避免传输过程中意外终端产生的异常
				String strCurTransRemoteTempFileFullPath;
				strCurTransRemoteTempFileFullPath.append(m_strCurTransRemoteFileFullPath).append(".temp");
				if ( !m_cFtp.RenameFtpFile( strCurTransRemoteTempFileFullPath.c_str(), m_strCurTransRemoteFileFullPath.c_str() ) )
				{
					MSG_BOX_OK("导入文件出错，错误原因：重命名文件失败！");
					UIFACTORYMGR_PTR->LoadScheme( "SchmTransferEnd", m_pWndTree );
					UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strProgressImp );
				}
				
				String strCaption;    //升级文件上传成功   发送升级消息到服务器
				UIFACTORYMGR_PTR->GetCaption( "ImpCommonDlg/StcImpCommonCap", strCaption, NULL );
				if ( "升级T300" == strCaption )
				{
					BOOL bInConf = LIBDATAMGRPTR->IsInConf();
					if ( bInConf )
					{
						MSG_BOX_OK("升级失败:当前会场正在开会，请稍后再次升级");
						s32 nResult = 0;
						UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrImpCommonDlg );
					}
					else
					{
// 						MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
// 						MSG_BOX( nMsgBoxRet, "升级文件已导入，需要重启才能生效，是否立即重启？" );	
// 						if ( MSGBOX_OK == nMsgBoxRet )
// 						{
// 							bInConf = LIBDATAMGRPTR->IsInConf();
// 							if ( bInConf )
// 							{
// 								MSG_BOX_OK("升级失败:当前会场正在开会，请稍后再次升级");
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
									MSG_BOX_OK("升级失败:升级T300命令发送失败");
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
				else if ( "导入摄像机参数" == strCaption )
				{
					COMIFMGRPTR->SetLoadCameraFileNty();

					MSG_BOX_OK("导入摄像机参数成功！");
					UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strProgressImp );
				}
			}
			else
			{
				LPTSTR pszMsg = NULL;
				m_cFtp.FormatFtpError( dwSuccess, &pszMsg );
				OspPrintf( TRUE, FALSE, "导入文件出错，错误原因：%s！", pszMsg );
				//MSG_BOX_OK(pszMsg);---  连接的时候错误信息空白,暂不提醒
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
	if ( "导入摄像机参数" == strCaption )
	{
		strFile = /*CNSCAMERA_FILE_NAME*/"";  //定义一个宏,内容是摄像机文件名
		strFilter = "摄像机配置文件(cameracfg.ini)|cameracfg.ini||";  
	}
	if ( "升级T300" == strCaption )
	{
		strFile = /*CNSUPGRADE_FILE_NAME*/"t300.bin";	//定义一个宏,内容是T300升级文件名,因为有2种,暂不做限制
		strFilter = "t300升级文件(t300.bin;t300.bin.gz)|t300.bin;t300.bin.gz||";
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
	//更新添加的文件到文件列表
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
	
	UploadCore( /*CNSUPGRADE_FILE_PATH*/UPDATEFILE_PATH_NAME, strFileFullPath, /*CNSUPGRADE_FILE_NAME*/m_strImpFileName );  //参数需要重新设置
	
	return true;
}

BOOL CImpCommonDlgLogic::UploadCore( const String& strRemotePath, const String& strLocalFile, const String& strCheckFileName, BOOL bIsDefServ /*= TRUE */ )
{
	if ( !UIDATAMGR_PTR->IsFileExist( strLocalFile.c_str() ) )
	{
		MSG_BOX_OK("指定文件不存在，无法导入!");
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
		MSG_BOX_OK("连接服务器失败!");
		
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
			MSG_BOX_OK("导入操作失败!");
			
			return false;
		}
		//设置定时器 时间间隔30s
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
	MSG_BOX_OK("导入文件出错，错误原因：超时");
	UIFACTORYMGR_PTR->LoadScheme( "SchmTransferEnd", m_pWndTree );
	UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strProgressImp );
	m_cFtp.EndFtpFile();
}
