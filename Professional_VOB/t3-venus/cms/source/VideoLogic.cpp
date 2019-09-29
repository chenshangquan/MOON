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
String CVideoLogic::m_strSchmRestoreScreen = "schmStoreScreen" ;  //小窗口方案
String CVideoLogic::m_strSchmHideScreen = "schmHide" ;  //隐藏方案

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
	//以后换文件只要小于分辨率1920*1080，并且宽高是2的整数倍就可以了
	m_cDecoder.SetStaticPicturePath( strFullPath );

   
}

CVideoLogic::~CVideoLogic()
{

}

void CVideoLogic::InitParam()
{
    SET_ASK_MAIN_FRAME_FUN( CVideoLogic::AskKeyFrame, m_pLogic, CVideoLogic )
   
    //获取重传次数
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

    //tNetRSParam.m_wSecondTimeSpan = 0 /*80*/;  //第二个重传检测点
    //tNetRSParam.m_wThirdTimeSpan = 0 /*120*/;   //第三个重传检测点
	tNetRSParam.m_wRejectTimeSpan = 2000;  //过期丢弃的时间跨度
    m_cDecoder.SetNetFeedbackVideoParam( tNetRSParam, TRUE );
    m_cDecoder.SetNetFeedbackAudioParam( tNetRSParam, TRUE );

    u32 dwLocalIP = 0;
    BusinessManagePtr->GetLocalIP( dwLocalIP ); 
    
	//2012.9.27  避免该端口已经被其他程序占用而导致无法正常接收到音视频码流问题  by yujinjin
    u16 wVedioPort = GetIdlePort( dwLocalIP,RTP_LOCALVIDEO_PORT, RTP_LOCALVIDEO_PORT + 100 );
	u16 wAudioPort = GetIdlePort( dwLocalIP,wVedioPort +2 , RTP_LOCALVIDEO_PORT + 200 );

    /*
    CString strGIp = "225.0.2.1"; //组播地址
    
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
    
    //设置监控信息接受的端口和Ip地址
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
    //显示码流界面
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

//开始观看双流演示
void CVideoLogic::PlayDual()
{  
    if (m_cDecoder.IsPlayed() == FALSE)
        //没在监控
    {   
        InitParam();
        BusinessManagePtr->StartDualCodeStream( m_tVedioIpTransAddr, m_tAudioIpTransAddr );
    
        //等待cns回应然后才开始监控
    }
    else //已经在监控
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
        pVideoWnd->Invalidate(); //2012-7-26 解决窗口最大化后人残留小窗口图像   
     }
  
    //切换大小时请求关键帧，防止白屏 -2014.3.4 xcr
    m_cDecoder.AskKeyFrame( TRUE );

	m_bFullScreen = TRUE;
    return true;
}

HRESULT CVideoLogic::OnShowVideo( WPARAM wparam, LPARAM lparam)
{
	m_bFullScreen = FALSE;
    if ( m_pWndTree != NULL )
    {
        //mainMenu  禁用videobutton 
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
		pVideo->Invalidate();//2012-7-26 解决窗口还原后人残留大窗口图像       
    } 
    
    //切换大小时请求关键帧，防止白屏 -2014.3.4 xcr
    m_cDecoder.AskKeyFrame( TRUE );
     
    UIManagePtr->LoadScheme( g_schmMainMenuEnableVideoBtn, NULL, g_stcStrMainMenuDlg );
   
}

/*
enum EmTPAddDualRcvResult
{
emAddDualRcvSucceed = 0,
emAddDualRcvFailNoDual,       //没有收双流
emAddDualRcvFailIllegalPos,   //非法位置
emAddDualRcvFailNoPos,        //没有空闲位置了
emAddDualRcvFailUnKown,
};
*/
HRESULT CVideoLogic::OnStartRsp( WPARAM wparam, LPARAM lparam)
{
    if ( m_pWndTree == NULL )
    {
        return S_FALSE;
    }

	//防止tpad点击收看演示后出现cnc演示源小窗口图片
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
            ShowPopMsg("观看演示失败：当前未处于接收双流状态");
            break;
            
        case emAddDualRcvFailIllegalPos:
             ShowPopMsg("观看演示失败：通道非法");
             break;
        case emAddDualRcvFailNoPos:
             ShowPopMsg("观看演示失败：无空闲通道");
             break;
        case emAddDualRcvFailUnKown:
			 ShowPopMsg("观看演示失败");
             //ShowPopMsg("观看演示失败：未知错误");  2012-8-7 SE石文娟确认未知错误不做提示 by yjj 
             break;
		case emAddDualRcvFailStatusError:
			 ShowPopMsg("观看演示失败：当前已处于双流状态");
             break;
		default:
			 ShowPopMsg("观看演示失败");
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
            ShowPopMsg("接收演示音频失败：当前未处于接收双流状态");
            break;
            
        case emAddDualRcvFailIllegalPos:
             ShowPopMsg("接收演示音频失败：通道非法");
             break;
        case emAddDualRcvFailNoPos:
             ShowPopMsg("接收演示音频失败：无空闲通道");
             break;
        case emAddDualRcvFailUnKown:
             ShowPopMsg("接收演示音频失败"); //2012-8-7 SE石文娟确认未知错误不做提示 by yjj
             break;
		case emAddDualRcvFailStatusError:
			 ShowPopMsg("接收演示音频失败：当前已处于双流状态");
             break;
		default:
			 ShowPopMsg("接收演示音频失败");
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
            ShowPopMsg("接收演示视频失败：当前未处于接收双流状态");
            break;
            
        case emAddDualRcvFailIllegalPos:
             ShowPopMsg("接收演示视频失败：通道非法");
             break;
        case emAddDualRcvFailNoPos:
             ShowPopMsg("接收演示视频失败：无空闲通道");
             break;
        case emAddDualRcvFailUnKown:
             ShowPopMsg("接收演示视频失败"); //2012-8-7 SE石文娟确认未知错误不做提示 by yjj
             break;
		case emAddDualRcvFailStatusError:
			 ShowPopMsg("接收演示视频失败：当前已处于双流状态");
             break;
		default:
			 ShowPopMsg("接收演示视频失败");
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
        //StopRcvVedio();  cns主动报停止双流时，自己已经清空交换，无需再次发请求清除 2012.8.22 by yjj
        
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
	//     }  2012.8.21 解决 点对点演示抢断后再次显示演示图像时 ，演示button未高亮问题 by yjj
	
    m_bDecod = FALSE;
    if ( m_bRecvStream )
    {
        BusinessManagePtr->StopDualCodeStream(); 
        m_bRecvStream = FALSE;
    } 
}

//根据是否为pc版本，进行位置重新设定后显示 dyy 2013年8月9日
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
	
	//显示演示图像时隐藏其余窗口
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

