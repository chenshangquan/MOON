// BasicInfoLogic.cpp: implementation of the CBasicInfoLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BasicInfoLogic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//CBasicInfoLogic *m_pThis =  ISingleTon<CBasicInfoLogic>::GetSingletonPtr();


CBasicInfoLogic::CBasicInfoLogic()
: m_strStcSName("StcSName")
, m_strStcIPS("StcIPS")
, m_strStcSE164Num("StcSE164Num")
, m_strStcScrSNum("StcScrSNum")
, m_strStcSDaul("StcSDaul")
, m_strStcSSIP("StcSSIP")
, m_strStcSGK("StcSGK")
, m_strStcSNAT("StcSNAT")
, m_strStcSCPU("StcSCPU")
, m_strStcSRam("StcSRam")
, m_strStcConfSName("StcConfSName")
, m_strStcConfSRate("StcConfSRate")
, m_strStcConfSHold("StcConfSHold")
, m_strStcConfSCallType("StcConfSCallType")
, m_strStcShowSRate("StcShowSRate")
, m_strStcAudioSRate("StcAudioSRate")
{	
	
}

CBasicInfoLogic::~CBasicInfoLogic()
{

}


void CBasicInfoLogic::RegMsg()
{
	CBasicInfoLogic* m_pThis = GetSingletonPtr();
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_TPadIP_NTY, CBasicInfoLogic::OnTPadIPNty, m_pThis, CBasicInfoLogic );
	REG_MSG_HANDLER( UI_CNS_CNSINFO_NOTIFY, CBasicInfoLogic::OnCnsInfoNty, m_pThis, CBasicInfoLogic );
	REG_MSG_HANDLER( UI_CNS_REGSIP_NOTIFY, CBasicInfoLogic::OnRegSipNty, m_pThis, CBasicInfoLogic );
	REG_MSG_HANDLER( UI_CNS_REG_GK_NTY, CBasicInfoLogic::OnRegGkNty, m_pThis, CBasicInfoLogic );
	REG_MSG_HANDLER( UI_CNS_REG_NAT_NTY, CBasicInfoLogic::OnRegNATNty, m_pThis, CBasicInfoLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_CPURAM_NTY, CBasicInfoLogic::OnCPURAMNty, m_pThis, CBasicInfoLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_CONF_NTY, CBasicInfoLogic::OnConfInfoNty, m_pThis, CBasicInfoLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_GKRsp_NTY, CBasicInfoLogic::OnChangeGk, m_pThis, CBasicInfoLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_SIPRsp_NTY, CBasicInfoLogic::OnChangeSip, m_pThis, CBasicInfoLogic );
	
}


void CBasicInfoLogic::UnRegMsg()
{
	
}

void CBasicInfoLogic::RegCBFun()
{
	CBasicInfoLogic* m_pThis = GetSingletonPtr();
	REG_GOBAL_MEMBER_FUNC( "CBasicInfoLogic::InitWnd", CBasicInfoLogic::InitWnd, m_pThis, CBasicInfoLogic ) ;
	REG_GOBAL_MEMBER_FUNC( "CBasicInfoLogic::OnBtnRefresh", CBasicInfoLogic::OnBtnRefresh, m_pThis, CBasicInfoLogic ) ;

}

void CBasicInfoLogic::UnRegFunc()
{
	UN_REG_GOBAL_FUNC( "CBasicInfoLogic::InitWnd" );	
}

bool CBasicInfoLogic::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );
	UIFACTORYMGR_PTR->LoadScheme( "SchNoConf", m_pWndTree );
	return true;
}

void CBasicInfoLogic::Clear()
{
	
}

bool CBasicInfoLogic::OnBtnRefresh( const IArgs& args )
{
// 	TTPTPadList tTPadList;
// 	tTPadList.m_byTPadNum = 16;
// 	for ( int i=0 ; i<16 ; i++ )
// 	{
// 		tTPadList.m_adwTPadIP[i] = inet_addr("127.0.0.1");
// 	}
// 	Value_ItemTPad TpadList(&tTPadList);
// 	UIFACTORYMGR_PTR->SetPropertyValue( TpadList, "StcTPbg", m_pWndTree);
//	COMIFMGRPTR->ReqSysInfo();
//	COMIFMGRPTR->UpdateTpadListReq();
// 	TTPCnsInfo tCnsInfo;
// 	COMIFMGRPTR->UpdateCnsInfo(tCnsInfo);
	COMIFMGRPTR->RefreshBasicInfo();
	return true;
}

HRESULT CBasicInfoLogic::OnConfInfoNty( WPARAM wparam, LPARAM lparam)
{
	if ( NULL == m_pWndTree )
	{
		return S_FALSE;
	} 
	TTPCnsConfStatus tCnsConfStatus;
	TTPCnConfInfo tCnVideoParam;
	LIBDATAMGRPTR->GetCnConfStatus( tCnsConfStatus );
	LIBDATAMGRPTR->GetCnConfVideoParam( tCnVideoParam );

	if ( tCnsConfStatus.emState != em_CALL_CONNECTED )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchNoConf", m_pWndTree );
		return S_FALSE;
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchConf", m_pWndTree );
	}

	if ( tCnsConfStatus.m_emCallType == emCallType_P2P )
	{
		//会议名字
		UIFACTORYMGR_PTR->SetCaption( m_strStcConfSName, "点对点会议", m_pWndTree);
	} 
	else
	{
		//会议名字
		UIFACTORYMGR_PTR->SetCaption( m_strStcConfSName, tCnsConfStatus.achConfName, m_pWndTree);	
	}

	//会议呼叫类型
	String strConfSCallType;
	switch( tCnsConfStatus.m_emConfProtocal )
	{
	case emTpH323:
		{
			strConfSCallType = "H.323"; 
		}
		break;
	case emTpH320:
		{
			strConfSCallType = "H.320"; 
		}
		break;
	case emTpSIP:
		{		
			strConfSCallType = "SIP"; 			
		}
		break;
	case emTpSat:
		{		
			strConfSCallType = "Sat"; 			
		}
		break;
	default:
		{		
			strConfSCallType = "无效的呼叫类型"; 			
		}
		break;
	}
	UIFACTORYMGR_PTR->SetCaption( m_strStcConfSCallType, strConfSCallType, m_pWndTree );

	//会议能力
	String strConfSHold;
	switch( tCnVideoParam.tCnVideoParam.emFormat )
	{
	case emTPVH261:
		{
			strConfSHold = "H.261 ";  
		}
		break;
	case emTPVH262:
		{
			strConfSHold = "MPEG2 "; 
		}
		break;
	case emTPVH263:
		{		
			strConfSHold = "H.263 "; 
		}
		break;
	case emTPVH263plus:
		{		
			strConfSHold = "H.263plus "; 
		}
		break;
	case emTPVH264:
		{		
			strConfSHold = "H.264 "; 
		}
		break;
	case emTPVMPEG4:
		{		
			strConfSHold = "MPEG4 "; 
		}
		break;
	default:
		{		
		}
		break;
	}

	if ( tCnVideoParam.tCnVideoParam.m_dwProfile == 0 )
	{
		strConfSHold += "BP ";
	}
	else
	{
		strConfSHold += "HP ";
	}

	switch( tCnVideoParam.tCnVideoParam.emRes )
	{
	case emTPVHD720p1280x720:
		{
			strConfSHold += "720P@";  
		}
		break;
	case emTPVHD1080p1920x1080:
		{		
			strConfSHold += "1080P@"; 
		}
		break;
	case emTPVGA1600x1200:
		{
			strConfSHold += " UXGA@";			
		}
		break;
	case emTPVGA1024x768:
		{
			strConfSHold += " XGA@";		
		}
		break;
	case emTPVGA1280x768:
		{
			strConfSHold += " WXGA@";
		}
		break;
	case emTPVGA1280x800:
		{
			strConfSHold += " WXGA@";
		}
		break;
	case emTPVGA1366x768:
		{
			strConfSHold += " WXGA@";
		}
		break;
	case emTPVGA1280x1024:
		{
			strConfSHold += " SXGA@";
		}
		break;
	case emTPV4CIF:
		{
			strConfSHold += " 4CIF@";
		}
		break;
	default:
		{	
			strConfSHold += " ";
		}
		break;
	}
	
	s8 chFrameRate[8] = {0};
	sprintf( chFrameRate, "%u", tCnVideoParam.tCnVideoParam.byFrameRate );
	strConfSHold += chFrameRate;
	strConfSHold += "fps";	
	UIFACTORYMGR_PTR->SetCaption( m_strStcConfSHold, strConfSHold, m_pWndTree);
	
	//会议码率
	CString strConfSRate;
	strConfSRate.Format( "%d Kbps", tCnVideoParam.tCnVideoParam.wChanMaxBitrate);
	UIFACTORYMGR_PTR->SetCaption( m_strStcConfSRate, (String)strConfSRate, m_pWndTree); 
	
	bool bDual = LIBDATAMGRPTR->IsRcvDual();
	if ( bDual )
	{
		//演示码率	
		strConfSRate.Format( "%d Kbps", tCnVideoParam.wDualCallBit );
	} 
	else
	{
		strConfSRate.Format( "--", tCnVideoParam.wDualCallBit );
	}
	UIFACTORYMGR_PTR->SetCaption( m_strStcShowSRate, (String)strConfSRate, m_pWndTree); 
	
	//音频格式	
	CString strFormat = "";
	switch ( tCnVideoParam.emTpAudioFormat )
	{
	case emTPAMpegAACLD:
		{
			strFormat += "MPEG4 AAC-LD单声道";
			break;
		}
	case emTPAG711a:
		{
			strFormat += "G.711A";
			break;
		}
	case emTPAG711u:
		{
			strFormat += "G.711U";
			break;
		}
	case emTPAG719:
		{
			strFormat += "G.719";
			break;
		}
	case emTPAG7221:
		{
			strFormat += "G.722.1 Annex C Polycom Siren14";
			break;
		}
	case emTPAMP3:
		{
			strFormat += "MP3";
			break;
		}
	case emTPAMpegAACLC:
		{
			strFormat += "MPEG4 AAC-LC单声道";
			break;
		}
	default:
		break;
	}	
	UIFACTORYMGR_PTR->SetCaption( m_strStcAudioSRate, (string)strFormat, m_pWndTree );

	return S_OK;
}

HRESULT CBasicInfoLogic::OnTPadIPNty( WPARAM wparam, LPARAM lparam)
{
	if ( NULL == m_pWndTree )
	{
		return S_FALSE;
	} 
	TTPTPadList tTPadList;
	LIBDATAMGRPTR->GetTpadList( tTPadList );
	Value_ItemTPad TpadList(&tTPadList);
	UIFACTORYMGR_PTR->SetPropertyValue( TpadList, "StcTPbg", m_pWndTree);
	return S_OK;
}

HRESULT CBasicInfoLogic::OnCnsInfoNty( WPARAM wparam, LPARAM lparam)
{
	if ( NULL == m_pWndTree )
	{
		return S_FALSE;
	} 
	TTPCnsInfo tCnsInfo;
	LIBDATAMGRPTR->GetLocalCnsInfo( tCnsInfo );

	String strRoomName(tCnsInfo.m_achRoomName);
	UIFACTORYMGR_PTR->SetCaption( m_strStcSName, strRoomName, m_pWndTree);

	in_addr tAddr;
	tAddr.S_un.S_addr = tCnsInfo.m_adwIP[0];
	String strIPS = inet_ntoa(tAddr);
	UIFACTORYMGR_PTR->SetCaption( m_strStcIPS, strIPS, m_pWndTree);

	String strE164Num(tCnsInfo.m_achE164);
	UIFACTORYMGR_PTR->SetCaption( m_strStcSE164Num, strE164Num, m_pWndTree);
	
// 	stringstream ss;
// 	string strScrNum;
// 	ss<<tCnsInfo.m_wScreenNum;
// 	ss>>strScrNum;
 	CString strScrNum;
 	strScrNum.Format("%d",tCnsInfo.m_wScreenNum);
	UIFACTORYMGR_PTR->SetCaption( m_strStcScrSNum, (string)strScrNum, m_pWndTree);

	CString strDaul;
	if ( 255 == tCnsInfo.m_byDualPos)
	{
		strDaul.Format("没有双流源");
	} 
	else
	{
		//strDaul.Format("%d",tCnsInfo.m_byDualPos);
		TDualSrcInfo tDualSrcInfo;
		LIBDATAMGRPTR->GetDualSrcInfo( tDualSrcInfo );
		
		vector<TVgaInfo>::iterator it =  tDualSrcInfo.vctVgaInfo.begin() ;
		while( it != tDualSrcInfo.vctVgaInfo.end() )
		{   
			if ( tCnsInfo.m_byDualPos == it->m_emVgaType)
			{
				strDaul = it->m_achAlias;
			}		
			it++;
		}
	}
	UIFACTORYMGR_PTR->SetCaption( m_strStcSDaul, (string)strDaul, m_pWndTree, true);

	return S_OK;
}

HRESULT CBasicInfoLogic::OnRegSipNty( WPARAM wparam, LPARAM lparam )
{
	if ( NULL == m_pWndTree )
	{
		return S_FALSE;
	} 
	TTPSipRegistrarCfg tSipCfg;
	LIBDATAMGRPTR->GetSipCfg( tSipCfg );

	String strSIPIp;
	if ( !tSipCfg.bUsed || !tSipCfg.bRegistered )
	{
		UIFACTORYMGR_PTR->SetCaption( m_strStcSSIP, "未注册", m_pWndTree);
	}

	if ( tSipCfg.bUsed && !tSipCfg.bRegistered && tSipCfg.dwRegIP != 0 )
	{
		UIFACTORYMGR_PTR->SetCaption( m_strStcSSIP, "注册失败", m_pWndTree);
	}
	else if ( tSipCfg.bUsed && tSipCfg.bRegistered )
	{
		if ( tSipCfg.dwRegIP != 0 )
		{
			in_addr tAddr;
			tAddr.S_un.S_addr = tSipCfg.dwRegIP;
			strSIPIp = inet_ntoa(tAddr);
		} 
		else
		{
			strSIPIp = "";
		}
		UIFACTORYMGR_PTR->SetCaption( m_strStcSSIP, strSIPIp, m_pWndTree);
	}

	return S_OK;
}

HRESULT CBasicInfoLogic::OnRegGkNty( WPARAM wparam, LPARAM lparam )
{
	if ( NULL == m_pWndTree )
	{
		return S_FALSE;
	} 
	TTPGKCfg tGKCfg;
	LIBDATAMGRPTR->GetGkCfg( tGKCfg );

	String strGkIp;
	if ( !tGKCfg.bRegistered && !tGKCfg.bUsed )
	{
		UIFACTORYMGR_PTR->SetCaption( m_strStcSGK, "未注册", m_pWndTree);
	}
	else if ( !tGKCfg.bUsed && tGKCfg.bRegistered )
	{
		UIFACTORYMGR_PTR->SetCaption( m_strStcSGK, "未使用", m_pWndTree);
	}
	else if ( tGKCfg.bUsed && tGKCfg.bRegistered )
	{
		in_addr tAddr;
		tAddr.S_un.S_addr = tGKCfg.dwGKIP;		
		strGkIp = inet_ntoa(tAddr);	
		if ( "0.0.0.0" == strGkIp )
		{
			strGkIp = "";
		}
		UIFACTORYMGR_PTR->SetCaption( m_strStcSGK, strGkIp, m_pWndTree);
	}
	else if ( tGKCfg.bUsed && !tGKCfg.bRegistered )
	{
		UIFACTORYMGR_PTR->SetCaption( m_strStcSGK, "注册失败", m_pWndTree);
	}

	return S_OK;
}

HRESULT CBasicInfoLogic::OnRegNATNty( WPARAM wparam, LPARAM lparam )
{
	if ( NULL == m_pWndTree )
	{
		return S_FALSE;
	} 
	TTPNatCfg tNATIp;
	LIBDATAMGRPTR->GetNATCfg( tNATIp );

	String strNATIp;
	if ( tNATIp.bUsed )
	{
		in_addr tAddr;
		tAddr.S_un.S_addr = tNATIp.dwNatIP;		
		strNATIp = inet_ntoa(tAddr);
		if ( "0.0.0.0" == strNATIp )
		{
			strNATIp = "";
		}
		UIFACTORYMGR_PTR->SetCaption( m_strStcSNAT, strNATIp, m_pWndTree);
	}
	else
	{
		UIFACTORYMGR_PTR->SetCaption( m_strStcSNAT, "未使用", m_pWndTree);
	}

	return S_OK;
}

HRESULT CBasicInfoLogic::OnCPURAMNty( WPARAM wparam, LPARAM lparam )
{
	if ( NULL == m_pWndTree )
	{
		return S_FALSE;
	} 
	TTPSysInfo tSysInfo;
	LIBDATAMGRPTR->GetSysInfo( tSysInfo );

	String strCPU;
	s8 chMemRate[8] = {0};
	sprintf( chMemRate, "%u", tSysInfo.m_byCpuRate );
	strCPU += chMemRate;
	strCPU += "%";
	UIFACTORYMGR_PTR->SetCaption( m_strStcSCPU, strCPU, m_pWndTree, true);

	u32 t = tSysInfo.m_dwAllocByte*100/tSysInfo.m_dwTotalByte;
	CString strCRam;
	strCRam.Format( "%u", t);
	strCRam += "%";
	UIFACTORYMGR_PTR->SetCaption( m_strStcSRam, (String)strCRam, m_pWndTree, true);
	
	return S_OK;
}

HRESULT CBasicInfoLogic::OnChangeGk( WPARAM wparam, LPARAM lparam )
{
	if ( NULL == m_pWndTree )
	{
		return S_FALSE;
	} 
	bool bRegistered = (bool)wparam;
	if ( bRegistered )
	{
		TTPGKCfg tGKCfg;
		LIBDATAMGRPTR->GetGkCfg( tGKCfg );
		in_addr tAddr;
		tAddr.S_un.S_addr = tGKCfg.dwGKIP;		
		String strGkIp = inet_ntoa(tAddr);	
		UIFACTORYMGR_PTR->SetCaption( m_strStcSGK, strGkIp, m_pWndTree);
	} 
	else
	{
		UIFACTORYMGR_PTR->SetCaption( m_strStcSGK, "注册失败", m_pWndTree);
	}
	
	return S_OK;
}

HRESULT CBasicInfoLogic::OnChangeSip( WPARAM wparam, LPARAM lparam )
{
	if ( NULL == m_pWndTree )
	{
		return S_FALSE;
	} 
	bool bRegistered = (bool)wparam;
	if ( bRegistered )
	{
		TTPSipRegistrarCfg tSipCfg;
		LIBDATAMGRPTR->GetSipCfg( tSipCfg );
		in_addr tAddr;
		tAddr.S_un.S_addr = tSipCfg.dwRegIP;
		String strSIPIp = inet_ntoa(tAddr);
		UIFACTORYMGR_PTR->SetCaption( m_strStcSSIP, strSIPIp, m_pWndTree);
	} 
	else
	{
		UIFACTORYMGR_PTR->SetCaption( m_strStcSSIP, "注册失败", m_pWndTree);
	}

	return S_OK;
}
