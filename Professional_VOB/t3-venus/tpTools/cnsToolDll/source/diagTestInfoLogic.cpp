// diagTestInfoLogic.cpp: implementation of the CDiagTestInfoLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "diagTestInfoLogic.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



CDiagTestInfoLogic::CDiagTestInfoLogic()
: m_strCamera1("DiagTestInDlg/StcCamera1")						
, m_strCamera2("DiagTestInDlg/StcCamera2")	
, m_strCamera3("DiagTestInDlg/StcCamera3")
, m_StrShowCameraInfo("DiagTestInDlg/StcShowCameraInfo")
, m_strShowCamera("DiagTestInDlg/StcShowCamera")		
, m_strDisPlay1("DiagTestOutDlg/StcDisPlay1")
, m_strCheckDisPlay1("DiagTestOutDlg/CheckDisPlay1")
, m_strDisPlay2("DiagTestOutDlg/StcDisPlay2")
, m_strCheckDisPlay2("DiagTestOutDlg/CheckDisPlay2")
, m_strDisPlay3("DiagTestOutDlg/StcDisPlay3")
, m_strCheckDisPlay3("DiagTestOutDlg/CheckDisPlay3")
, m_strVoiceBox1("DiagTestOutDlg/StcVoiceBox1")	
, m_strCheckVoiceBox1("DiagTestOutDlg/CheckVoiceBox1")
, m_strVoiceBox2("DiagTestOutDlg/StcVoiceBox2")	
, m_strCheckVoiceBox2("DiagTestOutDlg/CheckVoiceBox2")
, m_strVoiceBox3("DiagTestOutDlg/StcVoiceBox3")
, m_strCheckVoiceBox3("DiagTestOutDlg/CheckVoiceBox3")
, m_strShowScreenInfo("DiagTestOutDlg/StcShowScreenInfo")
, m_strShowScreen("DiagTestOutDlg/StcShowScreen")
, m_strCheckShowScreen("DiagTestOutDlg/CheckShowScreen")
{

}

CDiagTestInfoLogic::~CDiagTestInfoLogic()
{

}


bool CDiagTestInfoLogic::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );

	return true;
}

void CDiagTestInfoLogic::RegMsg()
{
	CDiagTestInfoLogic *pThis =  GetSingletonPtr(); 
//	REG_MSG_HANDLER( UI_CNSTOOL_MSG_AVDiag_IND, CDiagTestInfoLogic::OnDomodalDiagTestWnd, pThis, CDiagTestInfoLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_AVDiag_IND, CDiagTestInfoLogic::OnVideoDiagInfoInd, pThis, CDiagTestInfoLogic );	
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_AVDiag_IND, CDiagTestInfoLogic::OnAudioDiagInfoInd, pThis, CDiagTestInfoLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_StopAVMatrix_RSP, CDiagTestInfoLogic::OnStopAVMatrixRsp, pThis, CDiagTestInfoLogic );
}

void CDiagTestInfoLogic::UnRegMsg()
{
	
}

void CDiagTestInfoLogic::RegCBFun()
{
	CDiagTestInfoLogic *pThis =  GetSingletonPtr();	
    REG_GOBAL_MEMBER_FUNC( "CDiagTestInfoLogic::InitWnd", CDiagTestInfoLogic::InitWnd, pThis, CDiagTestInfoLogic );
	REG_GOBAL_MEMBER_FUNC( "CDiagTestInfoLogic::OnCloseDiagTest", CDiagTestInfoLogic::OnCloseDiagTest, pThis, CDiagTestInfoLogic );
	REG_GOBAL_MEMBER_FUNC( "CDiagTestInfoLogic::OnPrePage", CDiagTestInfoLogic::OnPrePage, pThis, CDiagTestInfoLogic );
    REG_GOBAL_MEMBER_FUNC( "CDiagTestInfoLogic::OnNextPage", CDiagTestInfoLogic::OnNextPage, pThis, CDiagTestInfoLogic );
    REG_GOBAL_MEMBER_FUNC( "CDiagTestInfoLogic::OnExRePort", CDiagTestInfoLogic::OnExRePort, pThis, CDiagTestInfoLogic );
	
}

void CDiagTestInfoLogic::UnRegFunc()
{
	UN_REG_GOBAL_FUNC( "CDiagTestInfoLogic::InitWnd" );	
}

void CDiagTestInfoLogic::Clear()
{
	s32 nResult = 0;
	UIFACTORYMGR_PTR->Endmodal(nResult, g_strDiagTestFrame );
}

LRESULT CDiagTestInfoLogic::OnVideoDiagInfoInd( WPARAM wparam, LPARAM lparam )
{
	String strNoSignal = "δ��⵽�ź�";
	TTPVideoDiagInfo tVideoDiagInfo;
	LIBDATAMGRPTR->GetVideoDiagInfo(tVideoDiagInfo);
	//����ӿڲ���
	String strCamera1 = GetVideoInfo( tVideoDiagInfo.m_atPrimVideoInputPort[0] );
	UIFACTORYMGR_PTR->SetCaption( m_strCamera1, strCamera1 );
	if ( strNoSignal == strCamera1 )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmNoSignal", NULL, m_strCamera1 ); 
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmSignal", NULL, m_strCamera1 ); 
	}

	String strCamera2 = GetVideoInfo( tVideoDiagInfo.m_atPrimVideoInputPort[1] );
	UIFACTORYMGR_PTR->SetCaption( m_strCamera2, strCamera2 );
	if ( strNoSignal == strCamera2 )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmNoSignal", NULL, m_strCamera2 ); 
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmSignal", NULL, m_strCamera2 ); 
	}
		
	String strCamera3 = GetVideoInfo( tVideoDiagInfo.m_atPrimVideoInputPort[2] );
	UIFACTORYMGR_PTR->SetCaption( m_strCamera3, strCamera3 );
	if ( strNoSignal == strCamera3 )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmNoSignal", NULL, m_strCamera3 ); 
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmSignal", NULL, m_strCamera3 ); 
	}
	
	EmVgaType emDualInput = (EmVgaType)tVideoDiagInfo.m_byInputDemoIndex;
	if ( emDualInput != emVgaTypeInValid )
	{
		String strShowCameraInfo = VgaInToString(emDualInput);
		strShowCameraInfo += "��";
		UIFACTORYMGR_PTR->SetCaption( m_StrShowCameraInfo, strShowCameraInfo );		
		
		String strShowCamera = GetVideoInfo( tVideoDiagInfo.m_tDemoVideoInputPort );
		UIFACTORYMGR_PTR->SetCaption( m_strShowCamera, strShowCamera );
		if ( strNoSignal == strShowCamera )
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmNoSignal", NULL, m_strShowCamera ); 
		}
		else
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmSignal", NULL, m_strShowCamera );
		}
	} 
	else
	{
		CString strShowCameraInfo = "δѡ����ʾԴ����ӿ�";		
		UIFACTORYMGR_PTR->SetCaption( m_StrShowCameraInfo, (String)strShowCameraInfo );	
		UIFACTORYMGR_PTR->SetCaption( m_strShowCamera, "" );
	}


	//����ӿڲ���
	String strDisPlay1 = GetVideoInfo( tVideoDiagInfo.m_atPrimVideoOutputPort[0] );
	UIFACTORYMGR_PTR->SetCaption( m_strDisPlay1, strDisPlay1 );
	if ( strNoSignal == strDisPlay1 )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmNoSignal", NULL, m_strDisPlay1 ); 
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmSignal", NULL, m_strDisPlay1 ); 
	}
				
	String strDisPlay2 = GetVideoInfo( tVideoDiagInfo.m_atPrimVideoOutputPort[1] );
	UIFACTORYMGR_PTR->SetCaption( m_strDisPlay2, strDisPlay2 );
	if ( strNoSignal == strDisPlay2 )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmNoSignal", NULL, m_strDisPlay2 ); 
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmSignal", NULL, m_strDisPlay2 ); 
	}
				
	String strDisPlay3 = GetVideoInfo( tVideoDiagInfo.m_atPrimVideoOutputPort[2] );
	UIFACTORYMGR_PTR->SetCaption( m_strDisPlay3, strDisPlay3 );
	if ( strNoSignal == strDisPlay3 )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmNoSignal", NULL, m_strDisPlay3 ); 
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmSignal", NULL, m_strDisPlay3 ); 
	}	
				
	EmDualOutputType emDualOutput = (EmDualOutputType)tVideoDiagInfo.m_byOutputDemoIndex;
	if ( emDualOutput != emDualOutputInvalid )
	{
		String strShowScreenInfo = VgaOutToString(emDualOutput);
		strShowScreenInfo += "��";
		UIFACTORYMGR_PTR->SetCaption( m_strShowScreenInfo, strShowScreenInfo );		
		
		String strShowScreen = GetVideoInfo( tVideoDiagInfo.m_tDemoVideoOutputPort );
		UIFACTORYMGR_PTR->SetCaption( m_strShowScreen, strShowScreen );
		if ( strNoSignal == strShowScreen )
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmNoSignal", NULL, m_strShowScreen ); 
		}
		else
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmSignal", NULL, m_strShowScreen ); 
		}
		Value_WindowVisible val;
		val.bVisible = true;
		UIFACTORYMGR_PTR->SetPropertyValue( val, m_strCheckShowScreen );
		UIFACTORYMGR_PTR->SetCaption( "DiagTestOutDlg/StcCheckShowScreen", "ͼ��" );
	} 
	else
	{
		CString strShowScreenInfo = "δѡ����ʾԴ����ӿ�";
		UIFACTORYMGR_PTR->SetCaption( m_strShowScreenInfo, (string)strShowScreenInfo );	
		UIFACTORYMGR_PTR->SetCaption( m_strShowScreen, "" );
		Value_WindowVisible val;
		val.bVisible = false;
		UIFACTORYMGR_PTR->SetPropertyValue( val, m_strCheckShowScreen );
		UIFACTORYMGR_PTR->SetCaption( "DiagTestOutDlg/StcCheckShowScreen", "" );
	}

	return S_OK;
}

LRESULT CDiagTestInfoLogic::OnAudioDiagInfoInd( WPARAM wparam, LPARAM lparam )
{
	TTPAudioDiagInfo tAudioDiagInfo;
	LIBDATAMGRPTR->GetAudioDiagInfo(tAudioDiagInfo);
	
	//FOR TEST BY JYY
// 	tAudioDiagInfo.m_atPrimAudioInputPort[0].m_abAudioPort[0] = TRUE;
// 	tAudioDiagInfo.m_atPrimAudioInputPort[0].m_abyVolume[0] = 68;
// 	
// 	tAudioDiagInfo.m_atPrimAudioInputPort[0].m_abAudioPort[1] = TRUE;
// 	tAudioDiagInfo.m_atPrimAudioInputPort[0].m_abyVolume[1] = 68;
// 	
// 	tAudioDiagInfo.m_atPrimAudioInputPort[0].m_abAudioPort[2] = TRUE;
// 	tAudioDiagInfo.m_atPrimAudioInputPort[0].m_abyVolume[2] = 68;
// 
// 	tAudioDiagInfo.m_atPrimAudioInputPort[1].m_abAudioPort[0] = TRUE;
// 	tAudioDiagInfo.m_atPrimAudioInputPort[1].m_abyVolume[0] = 68;
// 	
// 	tAudioDiagInfo.m_atPrimAudioInputPort[1].m_abAudioPort[1] = TRUE;
// 	tAudioDiagInfo.m_atPrimAudioInputPort[1].m_abyVolume[1] = 68;
// 	
// 	tAudioDiagInfo.m_atPrimAudioInputPort[1].m_abAudioPort[2] = TRUE;
// 	tAudioDiagInfo.m_atPrimAudioInputPort[1].m_abyVolume[2] = 68;
// 	
// 	tAudioDiagInfo.m_atPrimAudioInputPort[1].m_abAudioPort[3] = TRUE;
// 	tAudioDiagInfo.m_atPrimAudioInputPort[1].m_abyVolume[3] = -1;
// 
// 	tAudioDiagInfo.m_atPrimAudioInputPort[2].m_abAudioPort[0] = TRUE;
// 	tAudioDiagInfo.m_atPrimAudioInputPort[2].m_abyVolume[0] = -1;
// 	
// 	tAudioDiagInfo.m_atPrimAudioInputPort[2].m_abAudioPort[1] = TRUE;
// 	tAudioDiagInfo.m_atPrimAudioInputPort[2].m_abyVolume[1] = -1;
// 	
// 	tAudioDiagInfo.m_atPrimAudioInputPort[2].m_abAudioPort[2] = TRUE;
// 	tAudioDiagInfo.m_atPrimAudioInputPort[2].m_abyVolume[2] = -1;


	//��Ƶ����ӿڲ���
	Value_ItemCOMMON COMMONList(&tAudioDiagInfo);
	UIFACTORYMGR_PTR->SetPropertyValue( COMMONList, "DiagTestInDlg/StcCOMPbg", m_pWndTree);

	//��Ƶ����ӿڲ���	
	GetAudioOutInfo(tAudioDiagInfo.m_atPrimAudioOutputPort[0]);
	GetAudioOutInfo(tAudioDiagInfo.m_atPrimAudioOutputPort[1]);
	GetAudioOutInfo(tAudioDiagInfo.m_atPrimAudioOutputPort[2]);

	return S_OK;
}

bool CDiagTestInfoLogic::OnNextPage( const IArgs & arg )
{
	UIFACTORYMGR_PTR->ShowWindow( g_strDiagInTestInfo, false );
	UIFACTORYMGR_PTR->ShowWindow( g_strDiagOutTestInfo );

	return true;
}

bool CDiagTestInfoLogic::OnPrePage( const IArgs & arg )
{
	UIFACTORYMGR_PTR->ShowWindow( g_strDiagOutTestInfo, false );	
	UIFACTORYMGR_PTR->ShowWindow( g_strDiagInTestInfo );

	return true;
}

bool CDiagTestInfoLogic::OnCloseDiagTest( const IArgs & arg )
{
	MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
	MSG_BOX( nMsgBoxRet, "�Ƿ�ֹͣ���ԣ�" );
	if ( MSGBOX_OK == nMsgBoxRet )
	{
		u16 wRet = COMIFMGRPTR->StopAVMatrixReq();
		if ( wRet != NO_ERROR )
		{
			WARNMESSAGE( "ֹͣ����������ʧ��" );
		}

		//�ر�ʱˢ�²��Խ���
		//UIFACTORYMGR_PTR->LoadScheme( "", NULL, g_strDiagInTestInfo );
		//UIFACTORYMGR_PTR->LoadScheme( "", NULL, g_strDiagOutTestInfo );
		s32 nResult = 0;
		UIFACTORYMGR_PTR->Endmodal(nResult, g_strDiagTestFrame );
		//��֤ÿ�δ򿪵�������ӿڲ��Խ���
		UIFACTORYMGR_PTR->ShowWindow( g_strDiagInTestInfo );
		UIFACTORYMGR_PTR->ShowWindow( g_strDiagOutTestInfo, false );			
	}
	return true;	
}


bool CDiagTestInfoLogic::OnExRePort( const IArgs & arg )
{
// 	OPENFILENAMEA ofn;      
// 	s8 szFile[260]; 
//     sprintf( szFile, "%s", "DiagTest.txt" );
// 	ZeroMemory(&ofn, sizeof(ofn));
// 	ofn.lStructSize       = sizeof(ofn);
// 	ofn.hwndOwner         = NULL;
// 	ofn.lpstrFile         = szFile;
// 	ofn.nMaxFile          = sizeof(szFile);
// 	ofn.lpstrFilter       = "�ı��ļ�\0*.txt\0";
// 	ofn.nFilterIndex      = 1;
// 	ofn.lpstrFileTitle    = NULL;
// 	ofn.nMaxFileTitle     = 0;
// 	ofn.lpstrInitialDir   = NULL;
// 	ofn.Flags = 0;	
// 	if (GetSaveFileNameA(&ofn)==FALSE)
// 	{
// 		return S_FALSE;
// 	}
// 	CString c_save_path=ofn.lpstrFile;
//	AfxMessageBox(c_save_path);
// 	
// 	CFile cFile(TEXT(c_save_path), CFile::modeCreate|CFile::modeWrite);
// 	
// 	cFile.Write(c_save_path.GetBuffer(c_save_path.GetLength()),c_save_path.GetLength());
// 	cFile.Close();
// 	u16 wRet = COMIFMGRPTR->StopAVMatrixReq();
// 	if ( wRet != NO_ERROR )
// 	{
// 		MSG_BOX_OK( "ֹͣ����������ʧ��" );
// 	}

	String	strExport = GetAVPortInfo();

	String strFilter = "�ı��ļ�(*.txt)|*.txt||";  
	String strImpFileFullPath;
	String strImpFileName;
	BOOL bRe = UIDATAMGR_PTR->OpenFileDialog( strFilter, "DiagTest.txt", strImpFileFullPath, strImpFileName, FALSE );
	if ( !bRe )
	{
		return false;
	}

	CFile cFile(strImpFileFullPath.c_str(), CFile::modeCreate|CFile::modeWrite);
	if ( cFile.m_hFile == (UINT)INVALID_HANDLE_VALUE )
	{
		return false;
	}	
	cFile.Write( strExport.c_str(), strExport.size() );
	cFile.Close();

	return true;
}

LRESULT CDiagTestInfoLogic::OnDomodalDiagTestWnd( WPARAM wparam, LPARAM lparam )
{
	UIFACTORYMGR_PTR->Domodal( g_strDiagTestFrame );
	return S_OK;
}

String CDiagTestInfoLogic::ChangeResToString( EmTpVideoResolution& emVideoRes )
{
	String strR;
	switch(emVideoRes)
	{
	case emTPVHD720p1280x720:
		{
			strR = "�ֱ���720p,";  
		}
		break;
	case emTPVHD1080i1920x1080:
		{
			strR = "�ֱ���1080i,"; 
		}
		break;
	case emTPVHD1080p1920x1080:
		{		
			strR = "�ֱ���1080p,"; 
		}
		break;
	default:
		{	
			strR = "�ֱ���720p����,";
		}
		break;
	}
	return strR;
}

String CDiagTestInfoLogic::GetVideoInfo( TTPVideoPortInfo& tVideoPortInfo )
{	
	String strVideo;
	BOOL bIsSignal = tVideoPortInfo.m_bIsHaveVideoSrcOutput;
	if ( !bIsSignal )
	{
		strVideo = "δ��⵽�ź�";
		return strVideo;
	}
	EmTpVideoResolution emVideoResolution = tVideoPortInfo.m_emRes;
	strVideo = ChangeResToString(emVideoResolution);
	
	strVideo += "֡��";
	s8 chFRate[8] = {0};
	sprintf( chFRate, "%u", tVideoPortInfo.m_byFrameRate );
	strVideo += chFRate;
	strVideo += "Hz";
	return strVideo;
}

String CDiagTestInfoLogic::VgaInToString( EmVgaType& emDualInput )
{
	String strVgaIn;
	TDualSrcInfo tDualSrcInfo;
	LIBDATAMGRPTR->GetDualSrcInfo( tDualSrcInfo );
	
	vector<TVgaInfo>::iterator it =  tDualSrcInfo.vctVgaInfo.begin() ;
	while( it != tDualSrcInfo.vctVgaInfo.end() )
	{   
		if ( emDualInput == it->m_emVgaType)
		{
			strVgaIn = it->m_achAlias;
			break;
		}	
		it++;
	}
	return strVgaIn;
}

String CDiagTestInfoLogic::VgaOutToString( EmDualOutputType& emDualOutput )
{
	TTPVgaMixInfo tVgaMixInfo;
	LIBDATAMGRPTR->GetVgaMixInfo(tVgaMixInfo);
	
	String strVgaOut;
	switch(emDualOutput)
	{	
	case emDualOutput001:
		strVgaOut = tVgaMixInfo.m_achVgaOutputFstName;
		break;
	case emDualOutput002:
		strVgaOut = tVgaMixInfo.m_achVgaOutputSndName;
		break;
	default:
		strVgaOut = "";
		break;
	}
	return strVgaOut;
}

String CDiagTestInfoLogic::GetAudioOutInfo( TTpAudioPortInfo& tAudioPortInfo )
{	
	String strAudio = "";//����
	String strRecord;
	if (tAudioPortInfo.m_abAudioPort[0])
	{
		s8 chCOMMON[8] = {0};		
		sprintf( chCOMMON, "%u", tAudioPortInfo.m_abyVolume[0] );
		strAudio += chCOMMON;
		switch(tAudioPortInfo.m_byGroupIndex)
		{
		case 0:
			UIFACTORYMGR_PTR->SetCaption( m_strVoiceBox1, strAudio );
			UIFACTORYMGR_PTR->LoadScheme( "SchmSignal", NULL, m_strVoiceBox1 );
			strRecord = "������1��";
			break;
		case 1:
			UIFACTORYMGR_PTR->SetCaption( m_strVoiceBox2, strAudio );
			UIFACTORYMGR_PTR->LoadScheme( "SchmSignal", NULL, m_strVoiceBox2 ); 
			strRecord = "������2��";
			break;
		case 2:
			UIFACTORYMGR_PTR->SetCaption( m_strVoiceBox3, strAudio );
			UIFACTORYMGR_PTR->LoadScheme( "SchmSignal", NULL, m_strVoiceBox3 ); 
			strRecord = "������3��";
			break;
		default:
			break;
		}
	}
	else
	{
		strAudio = "δ��⵽�ź�";
		switch(tAudioPortInfo.m_byGroupIndex)
		{
		case 0:
			UIFACTORYMGR_PTR->SetCaption( m_strVoiceBox1, strAudio );
			UIFACTORYMGR_PTR->LoadScheme( "SchmNoSignal", NULL, m_strVoiceBox1 );
			strRecord = "������1��";
			break;
		case 1:
			UIFACTORYMGR_PTR->SetCaption( m_strVoiceBox2, strAudio );
			UIFACTORYMGR_PTR->LoadScheme( "SchmNoSignal", NULL, m_strVoiceBox2 ); 
			strRecord = "������2��";
			break;
		case 2:
			UIFACTORYMGR_PTR->SetCaption( m_strVoiceBox3, strAudio );
			UIFACTORYMGR_PTR->LoadScheme( "SchmNoSignal", NULL, m_strVoiceBox3 ); 
			strRecord = "������3��";
			break;;
		default:
			break;
		}
	}	
	strRecord += strAudio;

	return strRecord;
}

u32 CDiagTestInfoLogic::GetAudioNum()
{
	TTPAudioDiagInfo tAudioDiagInfo;
	LIBDATAMGRPTR->GetAudioDiagInfo(tAudioDiagInfo);
	u32 count = 0;			//��ʾ����ĳ����ٯ��˷�ı��
	u32 bUse10 = 0;			//������������ĸ���Ŀ�ٯ��˷�10
	for ( int i=0; i<3; i++ )
	{
		for ( int j=0; j<4; j++ )
		{
			if (TRUE == tAudioDiagInfo.m_atPrimAudioInputPort[i].m_abAudioPort[j])
			{
				for ( count; count<10; )			
				{
					if ( 0 == i )
					{
						m_bIsUse[count] = j;
					}
					if ( 1 == i )
					{
						m_bIsUse[count] = j+3;
					}
					if ( 2 == i )
					{
						m_bIsUse[count] = j+6;
					}
					if ( 3 == j && 0 == i )
					{
						bUse10 = 110;
						count -= 1;
					}
					if ( 3 == j && 1 == i )
					{
						bUse10 = 210;
						count -= 1;
					}
					if ( 3 == j && 2 == i )
					{
						bUse10 = 310;
						count -= 1;
					}
					count++;
					break;
				}
			}
		}
	}
	if ( bUse10 != 0 )
	{
		m_bIsUse[count] = bUse10;
		count += 1;
	}
	return count;
}

String CDiagTestInfoLogic::CommonToStr( u32 u )
{
	TTPAudioDiagInfo tAudioDiagInfo;
	LIBDATAMGRPTR->GetAudioDiagInfo(tAudioDiagInfo);
	s8 chCOMMON[8] = {0};	
	String strNoSignal = "255";
	String strAudio = "";//����	
	switch(u)
	{
	case 0:
		
		sprintf( chCOMMON, "%u", tAudioDiagInfo.m_atPrimAudioInputPort[0].m_abyVolume[0] );
		if ( !StrCmp( chCOMMON, strNoSignal.c_str() ) )
		{
			strAudio = "δ��⵽�ź�";
			break;
		}
		strAudio += chCOMMON;
		break;
	case 1:
			
		sprintf( chCOMMON, "%u", tAudioDiagInfo.m_atPrimAudioInputPort[0].m_abyVolume[1] );
		if ( !StrCmp( chCOMMON, strNoSignal.c_str() ) )
		{
			strAudio = "δ��⵽�ź�";
			break;
		}
		strAudio += chCOMMON;
		break;
	case 2:
	
		sprintf( chCOMMON, "%u", tAudioDiagInfo.m_atPrimAudioInputPort[0].m_abyVolume[2] );
		if ( !StrCmp( chCOMMON, strNoSignal.c_str() ) )
		{
			strAudio = "δ��⵽�ź�";
			break;
		}
		strAudio += chCOMMON;
		break;
	case 3:
		
		sprintf( chCOMMON, "%u", tAudioDiagInfo.m_atPrimAudioInputPort[1].m_abyVolume[0] );
		if ( !StrCmp( chCOMMON, strNoSignal.c_str() ) )
		{
			strAudio = "δ��⵽�ź�";
			break;
		}	
		strAudio += chCOMMON;
		break;
	case 4:
	
		sprintf( chCOMMON, "%u", tAudioDiagInfo.m_atPrimAudioInputPort[1].m_abyVolume[1] );
		if ( !StrCmp( chCOMMON, strNoSignal.c_str() ) )
		{
			strAudio = "δ��⵽�ź�";
			break;
		}
		strAudio += chCOMMON; 
		break;
	case 5:
	
		sprintf( chCOMMON, "%u", tAudioDiagInfo.m_atPrimAudioInputPort[1].m_abyVolume[2] );
		if ( !StrCmp( chCOMMON, strNoSignal.c_str() ) )
		{
			strAudio = "δ��⵽�ź�";
			break;
		}
		strAudio += chCOMMON; 
		break;
	case 6:
	
		sprintf( chCOMMON, "%u", tAudioDiagInfo.m_atPrimAudioInputPort[2].m_abyVolume[0] );
		if ( !StrCmp( chCOMMON, strNoSignal.c_str() ) )
		{
			strAudio = "δ��⵽�ź�";
			break;
		}
		strAudio += chCOMMON;
		break;
	case 7:
		
		sprintf( chCOMMON, "%u", tAudioDiagInfo.m_atPrimAudioInputPort[2].m_abyVolume[1] );
		if ( !StrCmp( chCOMMON, strNoSignal.c_str() ) )
		{
			strAudio = "δ��⵽�ź�";
			break;
		}
		strAudio += chCOMMON;
		break;
	case 8:
	
		sprintf( chCOMMON, "%u", tAudioDiagInfo.m_atPrimAudioInputPort[2].m_abyVolume[2] );
		if ( !StrCmp( chCOMMON, strNoSignal.c_str() ) )
		{
			strAudio = "δ��⵽�ź�";
			break;
		}
		strAudio += chCOMMON;
		break;
	case 110:		//���������Ե�һ���е�10
 			
 		sprintf( chCOMMON, "%u", tAudioDiagInfo.m_atPrimAudioInputPort[0].m_abyVolume[3] );
		if ( !StrCmp( chCOMMON, strNoSignal.c_str() ) )
		{
			strAudio = "δ��⵽�ź�";
			break;
		}
		strAudio += chCOMMON;
		break;
	case 210:		//���������Եڶ����е�10
		
		sprintf( chCOMMON, "%u", tAudioDiagInfo.m_atPrimAudioInputPort[1].m_abyVolume[3] );
		if ( !StrCmp( chCOMMON, strNoSignal.c_str() ) )
		{
			strAudio = "δ��⵽�ź�";
			break;
		}
		strAudio += chCOMMON;
		break;
	case 310:		//���������Ե������е�10
		
		sprintf( chCOMMON, "%u", tAudioDiagInfo.m_atPrimAudioInputPort[2].m_abyVolume[3] );
		if ( !StrCmp( chCOMMON, strNoSignal.c_str() ) )
		{
			strAudio = "δ��⵽�ź�";
			break;
		}	
		strAudio += chCOMMON;
		break;
	default:
		break;	
	}
	return strAudio;
}

s32 CDiagTestInfoLogic::GetCheckState( String strWnd )
{
	s32 wCheck;
	UIFACTORYMGR_PTR->GetCheckState( strWnd, wCheck );
	return wCheck;
}

LRESULT CDiagTestInfoLogic::OnStopAVMatrixRsp( WPARAM wparam, LPARAM lparam )
{
	s32 nResult = 0;
//	UIFACTORYMGR_PTR->Endmodal(nResult, g_strDiagTestFrame );
	return S_OK;
}

String CDiagTestInfoLogic::GetAVPortInfo()
{
	m_strDiagInVideo = "�������\r\n";
	m_strDiagOutVideo1 = "�������\r\n";
	m_strDiagInAudio = "";
	m_strDiagOutVideo2 = "";
	m_strDiagOutVideo3 = "";
	m_strDiagOutAudio1 = "";
	m_strDiagOutAudio2 = "";
	m_strDiagOutAudio3 = "";
	m_strDiagOutVideo4 = "";
	//����ӿڲ�����Ϣ
	String strDiagIn;
	UIFACTORYMGR_PTR->GetCaption( m_strCamera1, strDiagIn );
	m_strDiagInVideo += "����ͷ1��";
	m_strDiagInVideo += strDiagIn;
	m_strDiagInVideo += "\r\n";

	UIFACTORYMGR_PTR->GetCaption( m_strCamera2, strDiagIn );
	m_strDiagInVideo += "����ͷ2��";
	m_strDiagInVideo += strDiagIn;
	m_strDiagInVideo += "\r\n";

	UIFACTORYMGR_PTR->GetCaption( m_strCamera3, strDiagIn );
	m_strDiagInVideo += "����ͷ3��";
	m_strDiagInVideo += strDiagIn;
	m_strDiagInVideo += "\r\n";

	UIFACTORYMGR_PTR->GetCaption( m_StrShowCameraInfo, strDiagIn );
	m_strDiagInVideo += strDiagIn;
	UIFACTORYMGR_PTR->GetCaption( m_strShowCamera, strDiagIn );
	m_strDiagInVideo += strDiagIn;
	m_strDiagInVideo += "\r\n";

	u32 dwNum = GetAudioNum();
	s8 chCOMMON[50] = {0};
	for ( int i = 0; i<dwNum; i++ )
	{
		sprintf( chCOMMON, "��ٯ��˷�%u��", m_bIsUse[i]+1 );
		m_strDiagInAudio += chCOMMON;
		m_strDiagInAudio += CommonToStr( m_bIsUse[i] );
		m_strDiagInAudio += "\r\n";
	}
	//����ӿڽ�����Ϣ
	String strDiagOut;
	UIFACTORYMGR_PTR->GetCaption( m_strDisPlay1, strDiagOut );
	m_strDiagOutVideo1 += "��ʾ��1��";
	m_strDiagOutVideo1 += strDiagOut;
	if ( 0 != GetCheckState(m_strCheckDisPlay1) )
	{
		m_strDiagOutVideo1 += "		ͼ����ʾ�쳣";
	}
	m_strDiagOutVideo1 += "\r\n";

	UIFACTORYMGR_PTR->GetCaption( m_strDisPlay2, strDiagOut );
	m_strDiagOutVideo2 += "��ʾ��2��";
	m_strDiagOutVideo2 += strDiagOut;
	if ( 0 != GetCheckState(m_strCheckDisPlay2) )
	{
		m_strDiagOutVideo2 += "		ͼ����ʾ�쳣";
	}
	m_strDiagOutVideo2 += "\r\n";

	UIFACTORYMGR_PTR->GetCaption( m_strDisPlay3, strDiagOut );
	m_strDiagOutVideo3 += "��ʾ��3��";
	m_strDiagOutVideo3 += strDiagOut;
	if ( 0 != GetCheckState(m_strCheckDisPlay3) )
	{
		m_strDiagOutVideo3 += "		ͼ����ʾ�쳣";
	}
	m_strDiagOutVideo3 += "\r\n";

	UIFACTORYMGR_PTR->GetCaption( m_strVoiceBox1, strDiagOut );	
	m_strDiagOutAudio1 += "������1��";
	m_strDiagOutAudio1 += strDiagOut;
	if ( 0 != GetCheckState(m_strCheckVoiceBox1) )
	{
		m_strDiagOutAudio1 += "		�����쳣";
	}
	m_strDiagOutAudio1 += "\r\n";
	
	UIFACTORYMGR_PTR->GetCaption( m_strVoiceBox2, strDiagOut );	
	m_strDiagOutAudio2 += "������2��";
	m_strDiagOutAudio2 += strDiagOut;
	if ( 0 != GetCheckState(m_strCheckVoiceBox2) )
	{
		m_strDiagOutAudio2 += "		�����쳣";
	}
	m_strDiagOutAudio2 += "\r\n";
	
	UIFACTORYMGR_PTR->GetCaption( m_strVoiceBox3, strDiagOut );	
	m_strDiagOutAudio3 += "������3��";
	m_strDiagOutAudio3 += strDiagOut;
	if ( 0 != GetCheckState(m_strCheckVoiceBox3) )
	{
		m_strDiagOutAudio3 += "		�����쳣";
	}
	m_strDiagOutAudio3 += "\r\n";
	
	UIFACTORYMGR_PTR->GetCaption( m_strShowScreenInfo, strDiagOut );
	m_strDiagOutVideo4 += strDiagOut;
	UIFACTORYMGR_PTR->GetCaption( m_strShowScreen, strDiagOut );
	m_strDiagOutVideo4 += strDiagOut;
	if ( 0 != GetCheckState(m_strCheckShowScreen) )
	{
		m_strDiagOutVideo4 += "		ͼ����ʾ�쳣";
	}
	m_strDiagOutVideo4 += "\r\n";

	String strAVDiagInfo;
	strAVDiagInfo += m_strDiagInVideo;
	strAVDiagInfo += m_strDiagInAudio;
	strAVDiagInfo += m_strDiagOutVideo1;
	strAVDiagInfo += m_strDiagOutVideo2;
	strAVDiagInfo += m_strDiagOutVideo3;
	strAVDiagInfo += m_strDiagOutAudio1;
	strAVDiagInfo += m_strDiagOutAudio2;
	strAVDiagInfo += m_strDiagOutAudio3;
	strAVDiagInfo += m_strDiagOutVideo4;
	return strAVDiagInfo;
}
