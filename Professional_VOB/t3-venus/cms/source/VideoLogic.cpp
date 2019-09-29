// VideoLogic.cpp: implementation of the CVideoLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VideoLogic.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CVideoLogic *CVideoLogic::m_pLogic = NULL;
String CVideoLogic::m_wndVedio = "MediaFullDlg";
String CVideoLogic::m_strSchmFullScreen = "schmFullScreen";
String CVideoLogic::m_strSchmRestoreScreen = "schmStoreScreen" ;  //С���ڷ���
String CVideoLogic::m_strSchmHideScreen = "schmHide" ;  //���ط���

CVideoLogic::CVideoLogic() 
{   
    m_bRecvStream = FALSE;
    m_bDecod = FALSE;
	m_bFullScreen = FALSE;    
    m_cDecoder.SetAudioVolume( 255 );

	char strFullPath[MAX_PATH] = _T(""); 
#ifndef _DEBUG
	TCHAR achDllName[MAX_PATH] = _T(""); 
    GetModuleFileName(AfxGetInstanceHandle(), achDllName, sizeof (achDllName));
    String str( achDllName ); 
    
    int pos = str.find_last_of('\\'); 
    String strSub = str.substr( 0,pos+1 ); 
    _snprintf(strFullPath , sizeof(strFullPath), "%ssrc\\dualStatic.bmp",strSub.c_str());  
#else 
    _snprintf(strFullPath , sizeof(strFullPath), "src\\dualStatic.bmp");  
#endif
	//�Ժ��ļ�ֻҪС�ڷֱ���1920*1080�����ҿ����2���������Ϳ�����
	m_cDecoder.SetStaticPicturePath( strFullPath );

   
}

CVideoLogic::~CVideoLogic()
{

}

void CVideoLogic::InitParam()
{
    SET_ASK_MAIN_FRAME_FUN( CVideoLogic::AskKeyFrame, m_pLogic, CVideoLogic )
   
    //��ȡ�ش�����
    String strTime;
    UIManagePtr->GetCaption( "StResendTime", strTime, m_pWndTree );
    int nResendTime = atoi( strTime.c_str() );

    TNetRSParam tNetRSParam;
    tNetRSParam.m_wFirstTimeSpan = 40;

    switch( nResendTime )
    {
    case 1:
        tNetRSParam.m_wSecondTimeSpan = 0;
        tNetRSParam.m_wThirdTimeSpan = 0;
        break;
    case 2:
        tNetRSParam.m_wSecondTimeSpan = 80;
        tNetRSParam.m_wThirdTimeSpan = 0;
        break;
    case 3:
        tNetRSParam.m_wSecondTimeSpan = 80;
        tNetRSParam.m_wThirdTimeSpan = 120;
        break;
    default:
        tNetRSParam.m_wSecondTimeSpan = 0;
        tNetRSParam.m_wThirdTimeSpan = 0;
        break;
    }

    //tNetRSParam.m_wSecondTimeSpan = 0 /*80*/;  //�ڶ����ش�����
    //tNetRSParam.m_wThirdTimeSpan = 0 /*120*/;   //�������ش�����
	tNetRSParam.m_wRejectTimeSpan = 2000;  //���ڶ�����ʱ����
    m_cDecoder.SetNetFeedbackVideoParam( tNetRSParam, TRUE );
    m_cDecoder.SetNetFeedbackAudioParam( tNetRSParam, TRUE );

    u32 dwLocalIP = 0;
    BusinessManagePtr->GetLocalIP( dwLocalIP ); 
    
	//2012.9.27  ����ö˿��Ѿ�����������ռ�ö������޷��������յ�����Ƶ��������  by yujinjin
    u16 wVedioPort = GetIdlePort( dwLocalIP,RTP_LOCALVIDEO_PORT, RTP_LOCALVIDEO_PORT + 100 );
	u16 wAudioPort = GetIdlePort( dwLocalIP,wVedioPort +2 , RTP_LOCALVIDEO_PORT + 200 );

    /*
    CString strGIp = "225.0.2.1"; //�鲥��ַ
    
    int nIp[4] = {0};
    sscanf( (LPTSTR)(LPCTSTR)strGIp, "%d.%d.%d.%d", &nIp[0],&nIp[1],&nIp[2],&nIp[3] );
    
    CString strIP;
    strIP.Format( _T("%d.%d.%d.%d"), nIp[0], nIp[1], nIp[2], nIp[3] );
    
	u32 dwIp = ntohl( inet_addr( strIP ) );

    dwLocalIP = dwIp; */

    m_tVedioIpTransAddr.m_tRtpPort.m_dwIP = htonl(dwLocalIP);
    m_tVedioIpTransAddr.m_tRtpPort.m_wPort = wVedioPort;
    
	
    m_tAudioIpTransAddr.m_tRtpPort.m_dwIP = htonl(dwLocalIP);
    m_tAudioIpTransAddr.m_tRtpPort.m_wPort = wAudioPort;
    
    //���ü����Ϣ���ܵĶ˿ں�Ip��ַ
    m_cDecoder.SetInfo(m_tVedioIpTransAddr.m_tRtpPort.m_wPort , dwLocalIP , dwLocalIP );
    TMediaParam  tMonitorParam;
    tMonitorParam.abyDynamicPayLoad[0] = MEDIA_TYPE_H264;
    tMonitorParam.abyDynamicPayLoad[1] = MEDIA_TYPE_AACLC;
    
    tMonitorParam.abyRealType[0] = MEDIA_TYPE_H264;
    tMonitorParam.abyRealType[1] = MEDIA_TYPE_AACLC;
    
    tMonitorParam.atEncryptKey[0].byLen = 0;
    tMonitorParam.atEncryptKey[1].byLen = 0;
    
    m_cDecoder.SetVideoParam(tMonitorParam);
    
    TAudAACParam tAACParam;
    tAACParam.dwChannel = 1;
    tAACParam.dwSamplePerSecond = 32000;
    m_cDecoder.SetAACParam(tAACParam);

}
CVideoLogic* CVideoLogic::GetLogicPtr()
{
    if ( m_pLogic == NULL )
    {  
        m_pLogic = new CVideoLogic();   
    }
    
    return m_pLogic;
}

void CVideoLogic::RegMsg()
{   
    //��ʾ��������
   REG_MSG_HANDLER( WM_CMS_SHOWVIDEO, CVideoLogic::OnShowVideo, m_pLogic, CVideoLogic );
   REG_MSG_HANDLER( UI_CNSINS_START_DUALCODESTREAM_RSP, CVideoLogic::OnStartRsp, m_pLogic, CVideoLogic );
   
   REG_MSG_HANDLER( UI_CNS_RECV_DUAL_NOTIFY, CVideoLogic::OnDualRecvStateNotify, m_pLogic, CVideoLogic );
   REG_MSG_HANDLER( UI_UMS_HANGUP_CONF_RSP, CVideoLogic::OnHungupConf , m_pLogic, CVideoLogic ); 

   REG_MSG_HANDLER( UI_CNS_CONFSTATE_NOTIFY, CVideoLogic::OnConfStateNotify, m_pLogic, CVideoLogic );

   REG_MSG_HANDLER( WM_CMS_HIDE_VEDIO, CVideoLogic::OnHideVedioNotify, m_pLogic, CVideoLogic );
   
}

void CVideoLogic::UnRegMsg()
{
    
}

bool CVideoLogic::RegCBFun()
{   	 
    REG_GOBAL_MEMBER_FUNC( "CVideoLogic::InitWnd", CVideoLogic::InitWnd, m_pLogic, CVideoLogic);
    REG_GOBAL_MEMBER_FUNC( "CVideoLogic::OnBtnRestoreVedioWnd", CVideoLogic::OnBtnRestoreVedioWnd, m_pLogic, CVideoLogic);
    REG_GOBAL_MEMBER_FUNC( "CVideoLogic::OnBtnFullScreenVedio", CVideoLogic::OnBtnFullScreenVedio, m_pLogic, CVideoLogic);
    REG_GOBAL_MEMBER_FUNC( "CVideoLogic::BtnHideVedio", CVideoLogic::BtnHideVedio, m_pLogic, CVideoLogic);
	REG_GOBAL_MEMBER_FUNC( "CVideoLogic::OnBtnDBLCLKVedioWnd", CVideoLogic::OnBtnDBLCLKVedioWnd, m_pLogic, CVideoLogic);

    return true;
}

bool CVideoLogic::UnRegFunc()
{
    return true;
}


bool CVideoLogic::InitWnd( const IArgs & arg )
{   
    CWndLogicBase::InitWnd( arg ); 

    CWnd* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_wndVedio );
    if ( pWnd != NULL )
    {
        ::SetWindowPos( pWnd->GetSafeHwnd(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOMOVE);
    }

    return true;
}

void CVideoLogic::Clear()
{   
    if ( m_pWndTree != NULL )
    { 
        m_bRecvStream = FALSE;
        UIManagePtr->ShowWindow( "", false, m_pWndTree ); 

        UIManagePtr->LoadScheme( m_strSchmHideScreen, NULL, m_wndVedio );
        m_cDecoder.StopPlay();
        m_bDecod = FALSE;
        
        Value_SwitchState vState;
        vState.bState = false;
		UIManagePtr->SetPropertyValue( vState,  g_stcStrMainMenuDlg + "/" +  "btnVedio" );
		UIManagePtr->LoadScheme( g_schmMainMenuEnableVideoBtn, NULL, g_stcStrMainMenuDlg );
    }
    
}

//��ʼ�ۿ�˫����ʾ
void CVideoLogic::PlayDual()
{  
    if (m_cDecoder.IsPlayed() == FALSE)
        //û�ڼ��
    {   
        InitParam();
        BusinessManagePtr->StartDualCodeStream( m_tVedioIpTransAddr, m_tAudioIpTransAddr );
    
        //�ȴ�cns��ӦȻ��ſ�ʼ���
    }
    else //�Ѿ��ڼ��
    {  
        
        BusinessManagePtr->StopDualCodeStream(  );
        m_cDecoder.StopPlay();
        m_bRecvStream = FALSE;
        m_bDecod = FALSE;
       
	}
}

 

bool CVideoLogic::BtnHideVedio( const IArgs & arg )
{
    if ( m_pWndTree != NULL )
    {         
        BOOL bVis = FALSE;
        CWnd* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_wndVedio );
        if ( pWnd != NULL )
        {
            bVis = pWnd->GetStyle() & WS_VISIBLE;
        }

        if ( !bVis )
        {
            return true;
        }
        UIManagePtr->ShowWindow( "", false, m_pWndTree ); 
        UIManagePtr->LoadScheme( m_strSchmHideScreen, NULL, m_wndVedio );
        //m_cDecoder.SetWnd(NULL);
        m_cDecoder.StopPlay();
        m_bDecod = FALSE;

		Value_SwitchState vState;
		vState.bState = false;
		UIManagePtr->SetPropertyValue( vState,  g_stcStrMainMenuDlg + "/" +  "btnVedio" );
    }
    return true;
}


bool CVideoLogic::OnBtnDBLCLKVedioWnd( const IArgs & arg )
{
	IArgs args("");
	OnBtnFullScreenVedio( args );
	return true;
}


bool CVideoLogic::OnBtnRestoreVedioWnd( const IArgs & arg )
{
    RestoreVedioWnd( );
    return true;
}


void CVideoLogic::SetDecVol( u8 abyVol )
{
   m_cDecoder.SetAudioVolume(abyVol);
}

u8 CVideoLogic::GetDecVol()
{
    u8 abyVol = 0;
    m_cDecoder.GetAudioVolume( abyVol );
    return abyVol;

}


 

bool CVideoLogic::OnBtnFullScreenVedio( const IArgs & arg )
{ 
    ShowVideoByVersion( m_strSchmFullScreen );
    Window *pVideoWnd = UIManagePtr->GetWindowPtr( m_wndVedio );
    
    if ( pVideoWnd != NULL )
    {   
		m_cDecoder.SetWnd( pVideoWnd->GetSafeHwnd() ); 
        pVideoWnd->Invalidate(); //2012-7-26 ���������󻯺��˲���С����ͼ��   
     }
  
    //�л���Сʱ����ؼ�֡����ֹ���� -2014.3.4 xcr
    m_cDecoder.AskKeyFrame( TRUE );

	m_bFullScreen = TRUE;
    return true;
}

HRESULT CVideoLogic::OnShowVideo( WPARAM wparam, LPARAM lparam)
{
	m_bFullScreen = FALSE;
    if ( m_pWndTree != NULL )
    {
        //mainMenu  ����videobutton 
        UIManagePtr->LoadScheme( g_schmMainMenuDisableVideoBtn, NULL, g_stcStrMainMenuDlg );
        if ( m_bDecod && m_bRecvStream )
        {
           bool bVis = UIManagePtr->IsVisible(m_wndVedio);
           if ( bVis )
           {   
			    
               IArgs *arg = NULL;
               BtnHideVedio( *arg );
               UIManagePtr->LoadScheme( g_schmMainMenuEnableVideoBtn, NULL, g_stcStrMainMenuDlg );
           }
           else
           { 
               RestoreVedioWnd( );
           }
            
        }
        else if ( !m_bDecod && m_bRecvStream )
        {
            m_cDecoder.StartPlay(); 
            RestoreVedioWnd( );
            m_bDecod = true;

        }
        else
        {             
            PlayDual();

			//2012-7-23 
			if ( wparam == 1 )
			{   
				m_bFullScreen = TRUE; 
			}
        }
     
    }
    return S_OK;
}


HRESULT CVideoLogic::OnHideVedioNotify( WPARAM wparam, LPARAM lparam)
{   
    
    IArgs *arg = NULL;
    BtnHideVedio( *arg );
    return S_OK;
}

void CVideoLogic::RestoreVedioWnd( )
{    
    ShowVideoByVersion( m_strSchmRestoreScreen );

    Window *pVideo = UIManagePtr->GetWindowPtr(m_wndVedio);
    
    if ( pVideo != NULL )
    {   
		m_cDecoder.SetWnd( pVideo->GetSafeHwnd() ); 
		pVideo->Invalidate();//2012-7-26 ������ڻ�ԭ���˲����󴰿�ͼ��       
    } 
    
    //�л���Сʱ����ؼ�֡����ֹ���� -2014.3.4 xcr
    m_cDecoder.AskKeyFrame( TRUE );
     
    UIManagePtr->LoadScheme( g_schmMainMenuEnableVideoBtn, NULL, g_stcStrMainMenuDlg );
   
}

/*
enum EmTPAddDualRcvResult
{
emAddDualRcvSucceed = 0,
emAddDualRcvFailNoDual,       //û����˫��
emAddDualRcvFailIllegalPos,   //�Ƿ�λ��
emAddDualRcvFailNoPos,        //û�п���λ����
emAddDualRcvFailUnKown,
};
*/
HRESULT CVideoLogic::OnStartRsp( WPARAM wparam, LPARAM lparam)
{
    if ( m_pWndTree == NULL )
    {
        return S_FALSE;
    }

	//��ֹtpad����տ���ʾ�����cnc��ʾԴС����ͼƬ
	if ( !UIDATAMGR->IsPcVersion() )
	{
		if ( !UIManagePtr->IsVisible( g_stcStrMainFrameDlg ) ) 			
		{
			return S_OK;
		}
    }

    EmTPAddDualRcvResult emReVideo = (EmTPAddDualRcvResult)wparam;
    EmTPAddDualRcvResult emReAudio = (EmTPAddDualRcvResult)lparam;
    if( emReAudio != emAddDualRcvSucceed && emReVideo != emAddDualRcvSucceed )
    {
        switch( emReVideo )
        {
        case emAddDualRcvFailNoDual:
            ShowPopMsg("�ۿ���ʾʧ�ܣ���ǰδ���ڽ���˫��״̬");
            break;
            
        case emAddDualRcvFailIllegalPos:
             ShowPopMsg("�ۿ���ʾʧ�ܣ�ͨ���Ƿ�");
             break;
        case emAddDualRcvFailNoPos:
             ShowPopMsg("�ۿ���ʾʧ�ܣ��޿���ͨ��");
             break;
        case emAddDualRcvFailUnKown:
			 ShowPopMsg("�ۿ���ʾʧ��");
             //ShowPopMsg("�ۿ���ʾʧ�ܣ�δ֪����");  2012-8-7 SEʯ�ľ�ȷ��δ֪��������ʾ by yjj 
             break;
		case emAddDualRcvFailStatusError:
			 ShowPopMsg("�ۿ���ʾʧ�ܣ���ǰ�Ѵ���˫��״̬");
             break;
		default:
			 ShowPopMsg("�ۿ���ʾʧ��");
			 break;
        }

		UIManagePtr->LoadScheme( g_schmMainMenuEnableVideoBtn, NULL, g_stcStrMainMenuDlg );

        return S_FALSE;
    }


    if ( emReAudio != emAddDualRcvSucceed )
    {
        switch( emReVideo )
        {
        case emAddDualRcvFailNoDual:
            ShowPopMsg("������ʾ��Ƶʧ�ܣ���ǰδ���ڽ���˫��״̬");
            break;
            
        case emAddDualRcvFailIllegalPos:
             ShowPopMsg("������ʾ��Ƶʧ�ܣ�ͨ���Ƿ�");
             break;
        case emAddDualRcvFailNoPos:
             ShowPopMsg("������ʾ��Ƶʧ�ܣ��޿���ͨ��");
             break;
        case emAddDualRcvFailUnKown:
             ShowPopMsg("������ʾ��Ƶʧ��"); //2012-8-7 SEʯ�ľ�ȷ��δ֪��������ʾ by yjj
             break;
		case emAddDualRcvFailStatusError:
			 ShowPopMsg("������ʾ��Ƶʧ�ܣ���ǰ�Ѵ���˫��״̬");
             break;
		default:
			 ShowPopMsg("������ʾ��Ƶʧ��");
			 break;
        }
    }
    else
    {
         TTPCnMediaTransPort tMediaTranAddr = BusinessManagePtr->GetAudioTransAddr();
         m_cDecoder.SetAudioBackParam( tMediaTranAddr.m_tBackRtcpPort.GetPort(), 
                                          tMediaTranAddr.m_tBackRtcpPort.GetIP() );  
       
    }
        
    if ( emReVideo != emAddDualRcvSucceed )
    {
        switch( emReVideo )
        {
        case emAddDualRcvFailNoDual:
            ShowPopMsg("������ʾ��Ƶʧ�ܣ���ǰδ���ڽ���˫��״̬");
            break;
            
        case emAddDualRcvFailIllegalPos:
             ShowPopMsg("������ʾ��Ƶʧ�ܣ�ͨ���Ƿ�");
             break;
        case emAddDualRcvFailNoPos:
             ShowPopMsg("������ʾ��Ƶʧ�ܣ��޿���ͨ��");
             break;
        case emAddDualRcvFailUnKown:
             ShowPopMsg("������ʾ��Ƶʧ��"); //2012-8-7 SEʯ�ľ�ȷ��δ֪��������ʾ by yjj
             break;
		case emAddDualRcvFailStatusError:
			 ShowPopMsg("������ʾ��Ƶʧ�ܣ���ǰ�Ѵ���˫��״̬");
             break;
		default:
			 ShowPopMsg("������ʾ��Ƶʧ��");
			 break;
        }
    }
    else
    {   
        String strScreenSizeSchem = m_strSchmRestoreScreen;
		if ( m_bFullScreen )
		{
			strScreenSizeSchem = m_strSchmFullScreen;
		}
        
        ShowVideoByVersion( strScreenSizeSchem );

        TTPCnMediaTransPort tMediaTranAddr = BusinessManagePtr->GetVedioTransAddr();
        m_cDecoder.SetVideoBackParam( tMediaTranAddr.m_tBackRtcpPort.GetPort(), 
                                            tMediaTranAddr.m_tBackRtcpPort.GetIP() ); 
        
		
        
     
        Window *pVideo = UIManagePtr->GetWindowPtr( m_wndVedio);
        
	//	bool bSetWnd = false;
		HWND hVideo = NULL;
        if ( pVideo != NULL )
        {   
			hVideo = pVideo->GetSafeHwnd() ;
		//	bSetWnd = true;
            m_cDecoder.SetWnd( hVideo );  
            
        }

// 		PrtMsg(0,emEventTypeCmsWindow, "\n[CVideoLogic::OnStartRsp]videoHandle=%x, is MediaWindow show :%d , bSetWnd = %d\n",
// 			   hVideo, ::IsWindowVisible( hVideo ), bSetWnd );

		m_cDecoder.StartPlay(); 
        
        m_bRecvStream = TRUE;
        m_bDecod = TRUE;
    }   

     
    
    UIManagePtr->LoadScheme( g_schmMainMenuEnableVideoBtn, NULL, g_stcStrMainMenuDlg );

    return S_OK;
}


HRESULT CVideoLogic::OnDualRecvStateNotify( WPARAM wparam, LPARAM lparam)
{  
    BOOL32 bDual = (BOOL32)wparam;
    if ( ! bDual )
    {
		IArgs *arg = NULL;
        BtnHideVedio( *arg ); 
        //StopRcvVedio();  cns������ֹͣ˫��ʱ���Լ��Ѿ���ս����������ٴη�������� 2012.8.22 by yjj
        
        m_bRecvStream = FALSE;
    }
    
    
    return S_OK;
} 


HRESULT CVideoLogic::OnHungupConf( WPARAM wparam, LPARAM lparam)
{
    
    IArgs *arg = NULL;
	BtnHideVedio( *arg ); 
    StopRcvVedio();
    
    return S_OK;
} 


HRESULT CVideoLogic::OnConfStateNotify( WPARAM wparam, LPARAM lparam)
{   
    if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }
    
    BOOL32 bInConf = BusinessManagePtr->IsInConf();
    if ( !bInConf )
    {
        IArgs *arg = NULL;
        BtnHideVedio( *arg ); 
        StopRcvVedio();
    }
    
    return NO_ERROR;
}

 

void CVideoLogic::AskKeyFrame( BOOL32 bForce )
{
    BusinessManagePtr->ReqKeyFrame( bForce );
}


void CVideoLogic::StopRcvVedio()
{
   // if ( m_bDecod )
//     {  TRACE("\n[CVideoLogic::StopRcvVedio]  BtnHideVedio( *arg );\n");
	//         IArgs *arg = NULL;
	//         BtnHideVedio( *arg );
	//         //m_cDecoder.StopPlay(); 
	//         m_bDecod = FALSE;
	//         
	//     }  2012.8.21 ��� ��Ե���ʾ���Ϻ��ٴ���ʾ��ʾͼ��ʱ ����ʾbuttonδ�������� by yjj
	
    m_bDecod = FALSE;
    if ( m_bRecvStream )
    {
        BusinessManagePtr->StopDualCodeStream(); 
        m_bRecvStream = FALSE;
    } 
}

//�����Ƿ�Ϊpc�汾������λ�������趨����ʾ dyy 2013��8��9��
void CVideoLogic::ShowVideoByVersion( String SchemeType )
{
    UIManagePtr->LoadScheme( SchemeType, m_pWndTree);
    UIManagePtr->LoadScheme( SchemeType ,NULL,m_wndVedio);
    
//    if ( UIDATAMGR->IsPcVersion() ) 
    {
        POINT ptVedio; 
        if ( SchemeType == m_strSchmFullScreen )
        {
            ptVedio.x = 0;
            ptVedio.y = 0; 
        }
        else
        {
            ptVedio.x = 28;
            ptVedio.y = 418; 
        }         
        UIFACTORYMGR_PTR->SetWndPos( ptVedio, m_wndVedio, NULL, g_stcStrMainFrameDlg );
        
        POINT ptVedioDlg;  
        ptVedioDlg.x = 18;
        ptVedioDlg.y = 374; 
        UIFACTORYMGR_PTR->SetWndPos( ptVedioDlg, g_stcStrVideoDlg, NULL, g_stcStrMainFrameDlg );
    }
	
	//��ʾ��ʾͼ��ʱ�������ര��
	if ( UIManagePtr->IsVisible( g_stcStrCnsLstDlg ) )
	{
		UIManagePtr->ShowWindow( g_stcStrConfCnsCtrlDlg , false );
        UIManagePtr->ShowWindow( "ConfCnsCtrlSpeakerDlg", false );
		UIManagePtr->ShowWindow( g_stcStrCnsLstDlg, false );
    }
	
	Value_HoriListSelItem valSel;
	valSel.dwDataKey = -1;
	UIManagePtr->SetPropertyValue( valSel, "MainMenu/ConfManageMenuDlg/ConfManageList" );
    
    UIManagePtr->ShowWindow( g_stcStrVideoDlg );
    UIManagePtr->ShowWindow( m_wndVedio );   
}

