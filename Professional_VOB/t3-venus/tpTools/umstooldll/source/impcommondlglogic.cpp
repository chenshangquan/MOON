// impcommondlglogic.cpp: implementation of the CImpCommonDlgLogic class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "umstooldll.h"
#include "impcommondlglogic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CImpCommonDlgLogic::CImpCommonDlgLogic():
m_strEdtSaveFolder("EdtImpCommonSaveFolder"),
m_strProgressImp("ProgressImpCommon"),
m_strLstUpgradeFile("BoardUpgradeDlg/LstBoardUpgrade")
{
	m_pWnd = NULL;
	m_emFileFtpStatus = emFtpEnd;
	m_dwTotalFileSize = 0;
	m_dwCurSevr = 0;
	m_bReUploadCore = FALSE;
}

CImpCommonDlgLogic::~CImpCommonDlgLogic()
{
	UnRegMsg();
	UnRegFunc();
}

void CImpCommonDlgLogic::RegMsg()
{    

}

void CImpCommonDlgLogic::UnRegMsg()
{

}

bool CImpCommonDlgLogic::RegCBFun()
{   	 
	REG_GOBAL_MEMBER_FUNC( "CImpCommonDlgLogic::InitWnd", CImpCommonDlgLogic::InitWnd, IMPCOMMONLOGICRPTR, CImpCommonDlgLogic);
	REG_GOBAL_MEMBER_FUNC( "CImpCommonDlgLogic::OnBtnClose", CImpCommonDlgLogic::OnBtnClose, IMPCOMMONLOGICRPTR, CImpCommonDlgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CImpCommonDlgLogic::OnBtnImportAuthWork", CImpCommonDlgLogic::OnBtnImportAuthWork, IMPCOMMONLOGICRPTR, CImpCommonDlgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CImpCommonDlgLogic::OnBtnUpgradeBoardWork", CImpCommonDlgLogic::OnBtnUpgradeBoardWork, IMPCOMMONLOGICRPTR, CImpCommonDlgLogic );
	REG_DEFAULT_WINDOW_MSG( WM_UMSTOOL_FTPLOGPROGRESS );
	REG_GOBAL_MEMBER_FUNC( "CImpCommonDlgLogic::OnUploadProgress", CImpCommonDlgLogic::OnUploadProgress, IMPCOMMONLOGICRPTR, CImpCommonDlgLogic );
	REG_GOBAL_MEMBER_FUNC( "CImpCommonDlgLogic::OnBtnImportScan", CImpCommonDlgLogic::OnBtnImportScan, IMPCOMMONLOGICRPTR, CImpCommonDlgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CImpCommonDlgLogic::OnFolderEditChange", CImpCommonDlgLogic::OnFolderEditChange, IMPCOMMONLOGICRPTR, CImpCommonDlgLogic ); 

	return true;
}

bool CImpCommonDlgLogic::UnRegFunc()
{

	return true;
}

bool CImpCommonDlgLogic::InitWnd(  const IArgs & arg )
{   
	CWndLogicBase::InitWnd( arg );
	
	REG_ALGORITHM( IAlgorithm::strBoardUpgradItem, CLayoutAlgorithm_BoardUpgrade )

	m_pWnd = UIFACTORYMGR_PTR->GetWindowPtr( g_stcStrImpCommonDlg );
	if ( NULL != m_pWnd )
	{
		return false;
	}

    return true;
}

void CImpCommonDlgLogic::Clear()
{
	CleanTransfer();

	s32 nResult = 0;
	UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrImpCommonDlg );
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

	m_vecUpgradeFile.clear();
	m_strCurTransRemoteFileFullPath = "";

	UpdateUpgradeFileList();

	UIFACTORYMGR_PTR->LoadScheme( "SchmImpCommonClean", m_pWndTree );
}

bool CImpCommonDlgLogic::OnBtnClose( const IArgs & arg )
{
	CleanTransfer();

	m_bReUploadCore = FALSE;

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

			if ( 3 == CPrintCtrl::GetPrintCtrl()->GetPrintLevel() )   //��������Ӧ����Ĵ�ӡ  xhx
			{
				OspPrintf( TRUE, FALSE, "OnUploadProgress -- emFtpBegin, m_dwTotalFileSize = %d\n", m_dwTotalFileSize );			
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
					
					UIFACTORYMGR_PTR->SetPropertyValue( m_valProgress, m_strProgressImp, m_pWndTree );
				}

				if ( 3 == CPrintCtrl::GetPrintCtrl()->GetPrintLevel() )   //��������ס����Ĵ�ӡ  xhx
				{
					OspPrintf( TRUE, FALSE, "OnUploadProgress -- emFtpTransfer��dwCurrentTransSize = %d\n", dwCurrentTransSize );
				}
			}
		}
		break;
	case emFtpEnd:
		{
			DWORD dwSuccess = static_cast<DWORD>(msg.lParam);     //FTP�ӿ�0Ϊ�ɹ�  Ĭ��ʧ��

			OspPrintf( TRUE, FALSE, "OnUploadProgress -- emFtpEnd�������� = %d\n", dwSuccess ); //��������ס����Ĵ�ӡ  xhx

			if ( 0 == dwSuccess )
			{
				UIFACTORYMGR_PTR->LoadScheme( "SchmTransferEnd", m_pWndTree );

				//����ɹ�   �޸���ʱ�ļ�Ϊʵ���ļ�   ���⴫������������ն˲������쳣
				String strCurTransRemoteTempFileFullPath;
				strCurTransRemoteTempFileFullPath.append(m_strCurTransRemoteFileFullPath).append(".temp");
				if ( !m_cFtp.RenameFtpFile( strCurTransRemoteTempFileFullPath.c_str(), m_strCurTransRemoteFileFullPath.c_str() ) )
				{
					MSG_BOX_OK("�����ļ���������ԭ���������ļ�ʧ�ܣ�");
					
					UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strProgressImp );
				}
				else
				{
					String strCaption;
					UIFACTORYMGR_PTR->GetCaption( "ImpCommonDlg/StcImpCommonCap", strCaption, NULL );
					if ( "������Ȩ" == strCaption )
					{
					//	OspPrintf( TRUE, FALSE, "������Ȩ�ɹ�MSG_BOX֮ǰ\n" );
						//��ַ���ɹ��������Ƿ�����
						MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
						MSG_BOX( nMsgBoxRet, "��Ȩ�ļ�����ɹ����Ƿ�����ums��������Ч��"  );
						if ( MSGBOX_OK == nMsgBoxRet)
						{
						//	OspPrintf( TRUE, FALSE, "������Ȩ�ɹ�MSG_BOX ok ����������\n" );
							u16 nRet = COMMONMGRIFPTR->RebootReq();;
							if ( nRet != NO_ERROR )
							{
								MESSAGEWND( "����ums������ʧ�ܣ�" );
							}
						}
					}
				}
			}
			else
			{
				LPTSTR pszMsg = NULL;
				m_cFtp.FormatFtpError( dwSuccess, &pszMsg );
				OspPrintf( TRUE, FALSE, "�����ļ���������ԭ��%s, �����룺%d\n", pszMsg , dwSuccess );
				if ( 0 != strlen(pszMsg) )
				{
					String strError = "�����ļ���������ԭ��";
					strError += pszMsg;
					MSG_BOX_OK(strError);
					LocalFree( pszMsg );
				}

				if ( 12029 == dwSuccess )
				{
					MSG_BOX_OK("����FTP������ʧ�ܣ�");
				}
				
				UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strProgressImp  );

				LocalFree( pszMsg );
			}

			m_cFtp.EndFtpFile();


			String strCaption;    //�����ļ��ϴ��ɹ�   ����������Ϣ��������
			UIFACTORYMGR_PTR->GetCaption( "ImpCommonDlg/StcImpCommonCap", strCaption, NULL );
			if ( "��������" == strCaption && 0 == dwSuccess )
			{
				m_vecUpgradeFile.clear();
				UpdateUpgradeFileList();
				
				//��������ɹ��������������ϵĿؼ�Ӧ�ûң���Ӧ�����û��ڴε������
				UIFACTORYMGR_PTR->EnableWindow( "BtnImpCommonFolderScan", FALSE, m_pWndTree );
				UIFACTORYMGR_PTR->EnableWindow( "BtnImpCommonExport", FALSE, m_pWndTree );
				UIFACTORYMGR_PTR->EnableWindow( "BtnImpCommonDlgClose", FALSE, m_pWndTree );

				if ( em_hdu_mdl != m_emEqpTy )
				{
					CMsgDispatch::SendMessage( UI_UMSTOOL_BOARDBEGINUPGRADE, (WPARAM)(LPCTSTR)m_strCurTransFile, 0 );
				}
				else
				{
					CMsgDispatch::SendMessage( UI_UMSTOOL_TVWBOARDBEGINUPGRADE, (WPARAM)(LPCTSTR)m_strCurTransFile, 0 );
				}
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

bool CImpCommonDlgLogic::OnBtnImportScan( const IArgs & arg )
{
	m_bReUploadCore = FALSE;
	String strFile;
	String strCaption;
	String strFilter;
	UIFACTORYMGR_PTR->GetCaption( "ImpCommonDlg/StcImpCommonCap", strCaption, NULL );
	if ( "������Ȩ" == strCaption )
	{
		strFile = AUTH_FILE_NAME_IMP;  
		strFilter = "��Ȩ�ļ�(*.key)|*.key||";  
	}
	if ( "��������" == strCaption )
	{
		strFilter = "���������ļ�(*.*)|*.*||";

		switch( m_emEqpTy )	//����ģʽ����
		{
		case em_adapter_mdl:
			{
				strFile = BOARD_CRI2_SIP_NAME;	
			}
			break;
		case em_dataswitch_mdl:
			{
				strFile = BOARD_CRI2_DSU_NAME;						
			}
			break;
		case em_netbuf_mdl:
			{
				strFile = BOARD_IS22_NAME;						
			}
			break;
		case em_audmix_mdl:
			{
				strFile = BOARD_EAPU_NAME;						
			}
			break;
		case em_mpc_mdl:
			{
				strFile = BOARD_MPC2_NAME;						
			}
			break;
		case em_bas_mdl:
			{
				strFile = BOARD_MPU2_BAS_NAME;						
			}
			break;
		case em_vmp_mdl:
			{
				strFile = BOARD_MPU2_VMP_NAME;						
			}
			break;
		case em_hdu_mdl:
			{
				strFile = BOARD_TVW_NAME;						
			}
			break;
		default:   //em_unknow_mdl
			{		
				strFile = "";
			}
			break;
		}
	}

	String strImpFileFullPath;
	String strImpFileName;
	if ( "��������" == strCaption )
	{
		CUmstoolCommon::OpenFileDialog( strFilter, strFile, strImpFileFullPath, strImpFileName, TRUE, TRUE );
	}
	else
	{
		CUmstoolCommon::OpenFileDialog( strFilter, strFile, strImpFileFullPath, strImpFileName );
	}
	
	if ( !strImpFileFullPath.empty() )
	{
		UIFACTORYMGR_PTR->SetCaption( m_strEdtSaveFolder, strImpFileFullPath, m_pWndTree );
	}

	//������ӵ��ļ����ļ��б�
	TUmsToolFile tFileList;
	strncpy( tFileList.chFileName, strImpFileName.c_str(), _MAX_FNAME );
	strncpy( tFileList.chFileFullPath, strImpFileFullPath.c_str(), MAX_PATH );
	tFileList.nFileSize = CUmstoolCommon::GetFileSize(tFileList.chFileFullPath);
	if ( tFileList.nFileSize > 0 )
	{
		if ( m_vecUpgradeFile.size() > 0 )
		{
			if ( "������Ȩ" == strCaption )
			{
				m_vecUpgradeFile.clear(); 
			}
			else
			{
				MSG_BOX_OK( "�ļ��б��������ݣ����ʧ�ܣ�" );
	    		return true;
			}		
		}
		m_vecUpgradeFile.push_back(tFileList);
		UpdateUpgradeFileList();
	}

	return true;
}

void CImpCommonDlgLogic::UpdateUpgradeFileList()
{
	if ( NULL == m_pWndTree  )
	{
		return;
	}
	
	Value_ItemBoardUpgrade itemBoardUpgrade( &m_vecUpgradeFile );
	UIFACTORYMGR_PTR->SetPropertyValue( itemBoardUpgrade, m_strLstUpgradeFile, m_pWndTree );
}

bool CImpCommonDlgLogic::OnFolderEditChange( const IArgs & arg )
{
	UIFACTORYMGR_PTR->LoadScheme( "SchmImpCommonClean", m_pWndTree, m_strProgressImp );

	return true;
}

bool CImpCommonDlgLogic::OnBtnImportAuthWork( const IArgs & arg )
{
	Value_WindowCaption valFolderName;
	UIFACTORYMGR_PTR->GetPropertyValue( valFolderName, m_strEdtSaveFolder, m_pWndTree );
	
	String strFileFullPath;
	strFileFullPath = valFolderName.strCaption.c_str();

	UploadCore( AUTH_FILE_PATH, strFileFullPath, AUTH_FILE_NAME_IMP );

	return true;
}

bool CImpCommonDlgLogic::OnBtnUpgradeBoardWork( const IArgs & arg )
{
	m_bReUploadCore = FALSE;
	if ( em_hdu_mdl != m_emEqpTy )
	{
		u32 dwData = DATAMGRPTR->GetConfCountData();			
		if ( dwData > 0 )
		{
			MSG_BOX_OK("���л��鿪�������ܽ�������");
			Clear();
			return false;
		}
	}

	TUmsToolFile tFile;
	CString strBoardFile;
	s32 nFileCount = m_vecUpgradeFile.size();
	if( nFileCount == 0 )
	{
		MSG_BOX_OK("��ѡ�������ļ����б�");

		return false;
	}

	for ( s32 nIndex = 0; nIndex < nFileCount; nIndex++ )
	{
		tFile = m_vecUpgradeFile[nIndex];

		switch( m_emEqpTy )	//����ģʽ����
		{
		case em_adapter_mdl:
			{
				strBoardFile = BOARD_CRI2_SIP_NAME;	
			}
			break;
		case em_dataswitch_mdl:
			{
				strBoardFile = BOARD_CRI2_DSU_NAME;						
			}
			break;
		case em_netbuf_mdl:
			{
				strBoardFile = BOARD_IS22_NAME;						
			}
			break;
		case em_audmix_mdl:
			{
				strBoardFile = BOARD_EAPU_NAME;						
			}
			break;
		case em_mpc_mdl:
			{
				strBoardFile = BOARD_MPC2_NAME;						
			}
			break;
		case em_bas_mdl:
			{
				strBoardFile = BOARD_MPU2_BAS_NAME;						
			}
			break;
		case em_vmp_mdl:
			{
				strBoardFile = BOARD_MPU2_VMP_NAME;						
			}
			break;
		case em_hdu_mdl:
			{
				strBoardFile = BOARD_TVW_NAME;						
			}
			break;
		default:   //em_unknow_mdl
			{		
				strBoardFile = "";
			}
			break;
		}
	
		m_strCurTransFile = tFile.chFileName;
		if ( !strBoardFile.IsEmpty() )
		{
			CString strBoardFileGz = strBoardFile + ".gz";
			if ( strBoardFile != m_strCurTransFile && strBoardFileGz != m_strCurTransFile )
			{
				CString strFormat;
				strFormat.Format( "�Ƿ��������ļ����������ļ�����%s", strBoardFile );
				MSG_BOX_OK((String)strFormat);
				
				return false;
			}
		}
		else
		{
			MSG_BOX_OK("�Ƿ��������ļ����������õ���ģʽ��");
			return false;
		}

		UploadCore( BOARDUPGRADE_FILE_PATH, tFile.chFileFullPath, tFile.chFileName, FALSE );
	}

	return true;
}

BOOL CImpCommonDlgLogic::UploadCore( const String& strRemotePath, const String& strLocalFile, const String& strCheckFileName, BOOL bIsDefServ )
{
	if ( !CUmstoolCommon::IsFileExist( strLocalFile.c_str() ) )
	{
		MSG_BOX_OK("ָ���ļ������ڣ��޷����룡");
		return false;
	}

	if ( !CUmstoolCommon::CheckTransferFile( strLocalFile, strCheckFileName ) )
	{
		return false;
	}

	m_cFtp.RegisterMsgHandle( WM_UMSTOOL_FTPLOGPROGRESS );
	if ( 3 == CPrintCtrl::GetPrintCtrl()->GetPrintLevel() )   //��������Ӧ����Ĵ�ӡ  xhx
	{
		OspPrintf( TRUE, FALSE, "m_cFtp.RegisterMsgHandle()\n" );	
	}
	
	CString strIpAddr;
	if ( bIsDefServ )
	{
		TLoginInfo tLoginInfo = COMMONMGRIFPTR->GetLoginInfo();
		strIpAddr = CUmstoolCommon::GetIpStr( htonl(tLoginInfo.dwIp) );
	}
	else
	{
		strIpAddr = CUmstoolCommon::GetIpStr( GetSevrIpAddr() );
	}
	
	BOOL32 bRet = m_cFtp.SetServerParam( strIpAddr, "admin", "admin" );
	if ( !bRet )
	{
		MSG_BOX_OK("���ӷ�����ʧ�ܣ�");
		
		return false;
	}
	if ( 3 == CPrintCtrl::GetPrintCtrl()->GetPrintLevel() )   //��������Ӧ����Ĵ�ӡ  xhx
	{
		OspPrintf( TRUE, FALSE, "m_cFtp.SetServerParam()\n" );	
	}
	
	if ( NULL != m_pWnd )
	{
		String strRemoteFilePath = strRemotePath;
		strRemoteFilePath += strCheckFileName;
		m_strCurTransRemoteFileFullPath = strRemoteFilePath;
		strRemoteFilePath += ".temp";
		m_cFtp.SetIsRenameTransFile(TRUE);
		if ( 3 == CPrintCtrl::GetPrintCtrl()->GetPrintLevel() )   //��������Ӧ����Ĵ�ӡ  xhx
		{
			OspPrintf( TRUE, FALSE, "m_cFtp.SetIsRenameTransFile()\n" );	
		}

/*		PrtMsg("HWND = %d\n",m_pWnd->GetSafeHwnd());*/

		if ( !m_cFtp.BeginUpload( m_pWnd->GetSafeHwnd(), strRemoteFilePath.c_str(), strLocalFile.c_str(),
			FTP_TRANSFER_TYPE_BINARY, FTP_AGENT ) )
		{
			if ( 3 == CPrintCtrl::GetPrintCtrl()->GetPrintLevel() )   //��������Ӧ����Ĵ�ӡ  xhx
			{
				OspPrintf( TRUE, FALSE, "m_cFtp.BeginUpload()\n" );	
			}
// 			LPTSTR pszMsg = NULL;
//             DWORD dwErrorId = GetLastError();
//             CFtpCtrl::FormatFtpError( dwErrorId, &pszMsg );
//             OspPrintf( TRUE, FALSE, "CheckParam Error with %d -- %s\n", dwErrorId, pszMsg );
//             LocalFree(pszMsg);
// 
//             OspPrintf( TRUE, FALSE, "�������ʧ�ܣ���������m_pWnd->GetSafeHwnd()��%d��\n", m_pWnd->GetSafeHwnd() );
//             OspPrintf( TRUE, FALSE, "�������ʧ�ܣ���������strRemoteFilePath��%s��\n", strRemoteFilePath.c_str() );
//             OspPrintf( TRUE, FALSE, "�������ʧ�ܣ���������strLocalFile��%s��\n", strLocalFile.c_str() );
// 	
// 			MSG_BOX_OK("�������ʧ�ܣ���������");

			if ( !m_bReUploadCore )
			{
				OspPrintf( TRUE, FALSE, "��һ�ε������ʧ��!\n" );
				m_bReUploadCore = TRUE;
				CleanTransfer();
				UploadCore( BOARDUPGRADE_FILE_PATH, strLocalFile, strCheckFileName, FALSE );
			}

			UIFACTORYMGR_PTR->LoadScheme( "SchmImpCommonClean", m_pWndTree );			
			
			return false;
		}
	}
	
	return TRUE;
}
