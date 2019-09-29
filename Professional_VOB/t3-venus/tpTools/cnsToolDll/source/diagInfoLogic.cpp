// diagInfoLogic.cpp: implementation of the CDiagInfoLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cnsToolDll.h"
#include "diagInfoLogic.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDiagInfoLogic::CDiagInfoLogic()
: m_strLostPacket("StcLostPacket")
, m_strUpstream("StcUpstream")
, m_strDownstream("StcDownstream")
, m_strComboboxInPort("ComboboxInPort")
, m_strComboboxOutPort("ComboboxOutPort")
, m_strInAdPort1("StcInAdPort1")
, m_strInAdPort2("StcInAdPort2")
, m_strInAdPort3("StcInAdPort3")
{

}

CDiagInfoLogic::~CDiagInfoLogic()
{

}

void CDiagInfoLogic::RegMsg()
{
	CDiagInfoLogic *pThis =  GetSingletonPtr(); 
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_UpDownstream_NTY, CDiagInfoLogic::OnUpDownstreamNty, pThis, CDiagInfoLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_LostPacket_Rsp, CDiagInfoLogic::OnLostPacketRsp, pThis, CDiagInfoLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_AudPort_NTY, CDiagInfoLogic::OnUpdateAudioNty, pThis, CDiagInfoLogic ); 	
	REG_MSG_HANDLER( UI_CNS_VGAINFO_NOTIFY, CDiagInfoLogic::OnVgaInfoNotify, pThis, CDiagInfoLogic ); 	
	REG_MSG_HANDLER( UI_CNS_VGAINFO_NOTIFY, CDiagInfoLogic::OnVgaOutInfoNotify, pThis, CDiagInfoLogic ); 	
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_CONF_NTY, CDiagInfoLogic::OnConfStateNty, pThis, CDiagInfoLogic ); 
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_DftAudPort_NTY, CDiagInfoLogic::OnDefaultAudioNty, pThis, CDiagInfoLogic ); 
}

void CDiagInfoLogic::UnRegMsg()
{
	
}

void CDiagInfoLogic::RegCBFun()
{
	CDiagInfoLogic *pThis =  GetSingletonPtr();	
    REG_GOBAL_MEMBER_FUNC( "CDiagInfoLogic::InitWnd", CDiagInfoLogic::InitWnd, pThis, CDiagInfoLogic );
	REG_GOBAL_MEMBER_FUNC( "CDiagInfoLogic::OnBtnDiagTest", CDiagInfoLogic::OnBtnDiagTest, pThis, CDiagInfoLogic );
}

void CDiagInfoLogic::UnRegFunc()
{
	UN_REG_GOBAL_FUNC( "CDiagInfoLogic::InitWnd" );	
}

bool CDiagInfoLogic::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );

	return true;
}

void CDiagInfoLogic::Clear()
{
	if ( m_pWndTree != NULL )
	{
        m_tDualSrcInfo.Clear();
		memset( &m_tVgaMixInfo, 0, sizeof(m_tVgaMixInfo) );
	}
}

LRESULT CDiagInfoLogic::OnUpDownstreamNty( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL)
	{
		return S_FALSE;
	}

	TTPUpDownSpeedInfo tUpDownSpeedInfo;
	LIBDATAMGRPTR->GetUpDownstreamRate( tUpDownSpeedInfo );
	//��������
	s8 chUp[8] = {0};
	String strUpstream;
	if ( 1024 < tUpDownSpeedInfo.m_wUpSpeed )
	{
		float fUpSpeed = 1.0*tUpDownSpeedInfo.m_wUpSpeed/1024;
		sprintf( chUp, "%.1f", fUpSpeed );
		strUpstream = chUp;
		strUpstream += "Mpbs";
	}
	else
	{
		sprintf( chUp, "%u", tUpDownSpeedInfo.m_wUpSpeed );
		strUpstream = chUp;
		strUpstream += "Kpbs";
	}
 	UIFACTORYMGR_PTR->SetCaption(m_strUpstream, strUpstream, m_pWndTree, true);
	//��������
	s8 chDown[8] = {0};
	String strDownstream;
	if ( 1024 < tUpDownSpeedInfo.m_wDownSpeed )
	{
		float fDownSpeed = 1.0*tUpDownSpeedInfo.m_wDownSpeed/1024;
		sprintf( chDown, "%.1f", fDownSpeed );
		strDownstream = chDown;
		strDownstream += "Mpbs";
	}
	else
	{
		sprintf( chDown, "%u", tUpDownSpeedInfo.m_wDownSpeed );
		strDownstream = chDown;
		strDownstream += "Kpbs";
	}
	UIFACTORYMGR_PTR->SetCaption(m_strDownstream, strDownstream, m_pWndTree, true);
	return S_OK;
}

bool CDiagInfoLogic::OnBtnDiagTest( const IArgs & arg )
{
// 	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
// 	if ( bInConf )
// 	{		
// 		MSG_BOX_OK( "�����У���ֹʹ��" );	
// 		return true;
// 	}	
	//��ȡ��ʾԴ����ӿڵ�vga����
	String strInPort;
	EmVgaType emDualInput;
	UIFACTORYMGR_PTR->GetComboText( m_strComboboxInPort, strInPort, m_pWndTree );
	if ( strInPort.empty() )
	{
		emDualInput = emVgaTypeInValid;
		//MSGBOX_OK("��ʾԴ����ӿ�δѡ��!");
		//UIFACTORYMGR_PTR->SetFocus( m_strComboboxInPort );
		//return false;
	}
	else
	{
		vector<TVgaInfo>::iterator it =  m_tDualSrcInfo.vctVgaInfo.begin() ;
		while( it != m_tDualSrcInfo.vctVgaInfo.end() )
		{   
			if ( StrCmp( strInPort.c_str(), it->m_achAlias ) == 0 )
			{
				emDualInput = it->m_emVgaType;
			}		
			it++;
		}
	}

	//��ȡ��ʾԴ����ӿڵ�vga����
	String strOutPort;
	EmDualOutputType emDualOutput;
	UIFACTORYMGR_PTR->GetComboText( m_strComboboxOutPort, strOutPort, m_pWndTree );
	if ( strOutPort.empty() )
	{
		emDualOutput = emDualOutputInvalid;
		//MSGBOX_OK("��ʾԴ����ӿ�δѡ��!");
		//UIFACTORYMGR_PTR->SetFocus( m_strComboboxOutPort );
		//return false;
	}
	else
	{
		if ( StrCmp( strOutPort.c_str(), m_tVgaMixInfo.m_achVgaOutputFstName ) == 0 )
		{	
			emDualOutput = emDualOutput001;
		}
		else
		{
			emDualOutput = emDualOutput002;
		}
	}
	TTPVgaMixInfo tVgaMixInfo;
	tVgaMixInfo.m_emCurrentType = emDualInput;
	tVgaMixInfo.m_emDualOutputType = emDualOutput;
	COMIFMGRPTR->SelAVMatrixCmd(tVgaMixInfo);

	UIFACTORYMGR_PTR->Domodal( g_strDiagTestFrame );
	return true;
}

LRESULT CDiagInfoLogic::OnLostPacketRsp( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL)
	{
		return S_FALSE;
	}
	u8 LostPacketInfo;
	LIBDATAMGRPTR->GetLostPacketInfo( LostPacketInfo );

	s8 chLostPacket[8] ={0};
	sprintf( chLostPacket, "%u", LostPacketInfo );
	String strLostInfo = chLostPacket;
	strLostInfo += "%";
	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{
		UIFACTORYMGR_PTR->SetCaption(m_strLostPacket, strLostInfo, m_pWndTree, true);
	}
	else
	{
		UIFACTORYMGR_PTR->SetCaption(m_strLostPacket, "---", m_pWndTree, true);
	}
	return S_OK;
}

LRESULT CDiagInfoLogic::OnUpdateAudioNty( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	TTpAudioPortInfo* pAudioPortInfo = NULL;
	LIBDATAMGRPTR->GetAudioPortInfo( &pAudioPortInfo );
	TTpAudioPortInfo atAudioPortInfo[3];
	for ( int i = 0; i < 3; i++ )
    {
        TTpAudioPortInfo tAudioPortInfo = *( pAudioPortInfo + i );
        atAudioPortInfo[i] = tAudioPortInfo;
    }

	UIFACTORYMGR_PTR->SetCaption( m_strInAdPort1, "", m_pWndTree );
	UIFACTORYMGR_PTR->SetCaption( m_strInAdPort2, "", m_pWndTree );
	UIFACTORYMGR_PTR->SetCaption( m_strInAdPort3, "", m_pWndTree );

	String strGroup1 = UpdateGroup1( atAudioPortInfo[0] );
	String strGroup2 = UpdateGroup2( atAudioPortInfo[1] );
	String strGroup3 = UpdateGroup3( atAudioPortInfo[2] );

	if ( !strGroup1.empty() )
	{
		UIFACTORYMGR_PTR->SetCaption( m_strInAdPort1, strGroup1, m_pWndTree );
		if ( !strGroup2.empty() )
		{
			UIFACTORYMGR_PTR->SetCaption( m_strInAdPort2, strGroup2, m_pWndTree );
			if ( !strGroup3.empty() )
			{
				UIFACTORYMGR_PTR->SetCaption( m_strInAdPort3, strGroup3, m_pWndTree );
			} 
		} 
		else
		{
			if ( !strGroup3.empty() )
			{
				UIFACTORYMGR_PTR->SetCaption( m_strInAdPort2, strGroup3, m_pWndTree );
			} 
		}
	}
	else
	{
		if ( !strGroup2.empty() )
		{
			UIFACTORYMGR_PTR->SetCaption( m_strInAdPort1, strGroup2, m_pWndTree );
			if ( !strGroup3.empty() )
			{
				UIFACTORYMGR_PTR->SetCaption( m_strInAdPort2, strGroup3, m_pWndTree );
			} 
		} 
		else
		{
			if ( !strGroup3.empty() )
			{
				UIFACTORYMGR_PTR->SetCaption( m_strInAdPort1, strGroup3, m_pWndTree );
			} 
		}
	}
	
	return S_OK;
}
/*---------------------------------------------------------------------
* �������ƣ�UpdateGroup1
* ��    �ܣ�������Ƶ���ý����Group1
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2012/12/29	v1.0		������		����
----------------------------------------------------------------------*/
String CDiagInfoLogic::UpdateGroup1( TTpAudioPortInfo& tAudioPortInfo )
{	
	String strInAdPort1 = "";
	if (tAudioPortInfo.m_byGroupIndex == 0)
	{		
		for( int i = 0; i <4; i++ )
		{
			if ( TRUE == tAudioPortInfo.m_abAudioPort[i] )
			{
				switch( i )
				{
				case 0:
					strInAdPort1 += "��ٯ��˷�1";
					break;
				case 1:
					if ( strInAdPort1.empty() )
					{
						strInAdPort1 += "��ٯ��˷�2";
					}
					else
					{
						strInAdPort1 += ",��ٯ��˷�2";
					}
					break;
				case 2:
					if ( strInAdPort1.empty() )
					{
						strInAdPort1 += "��ٯ��˷�3";
					} 
					else
					{
						strInAdPort1 += ",��ٯ��˷�3";
					}	
					break;
				case 3:
					if ( strInAdPort1.empty() )
					{
						strInAdPort1 += "��ٯ��˷�10";
					} 
					else
					{
						strInAdPort1 += ",��ٯ��˷�10";
					}
					break;
				default:
					break;
				}
			}
		}
		//UIFACTORYMGR_PTR->SetCaption( m_strInAdPort1, strInAdPort1, m_pWndTree );
	} 
	return strInAdPort1;
}
/*---------------------------------------------------------------------
* �������ƣ�UpdateGroup2
* ��    �ܣ�������Ƶ���ý����Group2
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2012/12/29	v1.0		������		����
----------------------------------------------------------------------*/
String CDiagInfoLogic::UpdateGroup2( TTpAudioPortInfo& tAudioPortInfo )
{
	String strInAdPort2 = "";
	if (tAudioPortInfo.m_byGroupIndex == 1)
	{	
		for( int i = 0; i <4; i++ )
		{
			if ( TRUE == tAudioPortInfo.m_abAudioPort[i] )
			{
				switch( i )
				{
				case 0:
					strInAdPort2 += "��ٯ��˷�4";
					break;
				case 1:
					if ( strInAdPort2.empty() )
					{
						strInAdPort2 += "��ٯ��˷�5";
					}
					else
					{
						strInAdPort2 += ",��ٯ��˷�5";
					}
					break;
				case 2:
					if ( strInAdPort2.empty() )
					{
						strInAdPort2 += "��ٯ��˷�6";
					}
					else
					{
						strInAdPort2 += ",��ٯ��˷�6";
					}
					break;
				case 3:
					if ( strInAdPort2.empty() )
					{
						strInAdPort2 += "��ٯ��˷�10";
					}
					else
					{
						strInAdPort2 += ",��ٯ��˷�10";
					}
					break;
				default:
					break;
				}
			}
		}
		//UIFACTORYMGR_PTR->SetCaption( m_strInAdPort2, strInAdPort2, m_pWndTree );
	} 
	return strInAdPort2;
}
/*---------------------------------------------------------------------
* �������ƣ�UpdateGroup3
* ��    �ܣ�������Ƶ���ý����Group3
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2012/12/29	v1.0		������		����
----------------------------------------------------------------------*/
String CDiagInfoLogic::UpdateGroup3( TTpAudioPortInfo& tAudioPortInfo )
{
	String strInAdPort3 = "";
	if (tAudioPortInfo.m_byGroupIndex == 2)
	{	
		for( int i = 0; i <4; i++ )
		{
			if ( TRUE == tAudioPortInfo.m_abAudioPort[i] )
			{
				switch( i )
				{
				case 0:
					strInAdPort3 += "��ٯ��˷�7";
					break;
				case 1:
					if ( strInAdPort3.empty() )
					{
						strInAdPort3 += "��ٯ��˷�8";
					}
					else
					{
						strInAdPort3 += ",��ٯ��˷�8";
					}
					break;
				case 2:
					if ( strInAdPort3.empty() )
					{
						strInAdPort3 += "��ٯ��˷�9";
					}
					else
					{
						strInAdPort3 += ",��ٯ��˷�9";
					}
					break;
				case 3:
					if ( strInAdPort3.empty() )
					{
						strInAdPort3 += "��ٯ��˷�10";
					}
					else
					{
						strInAdPort3 += ",��ٯ��˷�10";
					}
					break;
				default:
					break;
				}
			}
		}
		//UIFACTORYMGR_PTR->SetCaption( m_strInAdPort3, strInAdPort3, m_pWndTree );
	} 
	return strInAdPort3;
}

LRESULT CDiagInfoLogic::OnVgaInfoNotify( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL)
	{
		return S_FALSE;
	}

	LIBDATAMGRPTR->GetDualSrcInfo( m_tDualSrcInfo );

	std::vector<CString> vecMdlTypeData;
	vecMdlTypeData.push_back("");	
	String strComInPort;
	if ( emVgaTypeInValid == m_tDualSrcInfo.emCurrentType )
	{
		m_tDualSrcInfo.emCurrentType = m_tDualSrcInfo.emDefaultType;
	}
	vector<TVgaInfo>::iterator it =  m_tDualSrcInfo.vctVgaInfo.begin() ;
	while( it != m_tDualSrcInfo.vctVgaInfo.end() )
	{   
		if ( m_tDualSrcInfo.emCurrentType == it->m_emVgaType)
		{
			strComInPort = it->m_achAlias;
		}
		vecMdlTypeData.push_back(it->m_achAlias);		
		it++;
	}
	UIFACTORYMGR_PTR->SetComboListData( m_strComboboxInPort, vecMdlTypeData, m_pWndTree );  
	UIFACTORYMGR_PTR->SetComboText( m_strComboboxInPort, strComInPort, m_pWndTree );
	return S_OK;
}

LRESULT CDiagInfoLogic::OnVgaOutInfoNotify( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL)
	{
		return S_FALSE;
	}

	LIBDATAMGRPTR->GetVgaMixInfo(m_tVgaMixInfo);

	String strComOutPort;
	switch(m_tVgaMixInfo.m_emDualOutputType)
	{	
	case emDualOutput001:
		strComOutPort = m_tVgaMixInfo.m_achVgaOutputFstName;
		break;
	case emDualOutput002:
		strComOutPort = m_tVgaMixInfo.m_achVgaOutputSndName;
		break;
	default:
		strComOutPort = "";
		break;
	}

	std::vector<CString> vecMdlTypeData;
	vecMdlTypeData.push_back("");
	vecMdlTypeData.push_back(m_tVgaMixInfo.m_achVgaOutputFstName);
	vecMdlTypeData.push_back(m_tVgaMixInfo.m_achVgaOutputSndName);
	UIFACTORYMGR_PTR->SetComboListData( m_strComboboxOutPort, vecMdlTypeData, m_pWndTree ); 
	UIFACTORYMGR_PTR->SetComboText( m_strComboboxOutPort, strComOutPort, m_pWndTree );

	return S_OK;
}

LRESULT CDiagInfoLogic::OnConfStateNty( WPARAM wparam, LPARAM lparam )
{
	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{
		if ( UIFACTORYMGR_PTR->IsVisible( g_strDiagTestFrame ) )
		{
			//ֹͣ��������
			COMIFMGRPTR->StopAVMatrixReq();

			s32 nResult = 0;
			UIFACTORYMGR_PTR->Endmodal(nResult, g_strDiagTestFrame );
		}
		UIFACTORYMGR_PTR->EnableWindow( "BtnDiagPort", false, m_pWndTree );
		CWnd* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strComboboxInPort, m_pWndTree ); 
		((CTransparentComboBox*)pWnd)->SetEnableWindow(FALSE);
		CWnd* pWndShow = UIFACTORYMGR_PTR->GetWindowPtr( m_strComboboxOutPort, m_pWndTree ); 
		((CTransparentComboBox*)pWndShow)->SetEnableWindow(FALSE);
	} 
	else
	{
		UIFACTORYMGR_PTR->EnableWindow( "BtnDiagPort", true, m_pWndTree );
		CWnd* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strComboboxInPort, m_pWndTree ); 
		((CTransparentComboBox*)pWnd)->SetEnableWindow(TRUE);
		CWnd* pWndShow = UIFACTORYMGR_PTR->GetWindowPtr( m_strComboboxOutPort, m_pWndTree ); 
		((CTransparentComboBox*)pWndShow)->SetEnableWindow(TRUE);
		//û�л����ʱ��,��������ʾ---  ʯ�ľ�ȷ��
		UIFACTORYMGR_PTR->SetCaption(m_strLostPacket, "---", m_pWndTree, true);
	}
	return S_OK;
}

HRESULT CDiagInfoLogic::OnDefaultAudioNty( WPARAM wparam, LPARAM lparam )
{
	BOOL bSuccess = *(BOOL*)lparam;
	if ( bSuccess )
	{
		UIFACTORYMGR_PTR->SetCaption( m_strInAdPort1, "��ٯ��˷�1", m_pWndTree );
		UIFACTORYMGR_PTR->SetCaption( m_strInAdPort2, "��ٯ��˷�4", m_pWndTree );
		UIFACTORYMGR_PTR->SetCaption( m_strInAdPort3, "��ٯ��˷�7", m_pWndTree );
	}
	return S_OK;
}
