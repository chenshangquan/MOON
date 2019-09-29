// Decoder.cpp: implementation of the CDecoder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cms.h"
#include "Decoder.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define DEC_CHECK_KEY_FRSME_ELAPS  1000  
 
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDecoder *g_pDecoder = NULL;

VOID  CALLBACK  CBTimerPoc( HWND hwnd, UINT  uMsg, UINT_PTR idEvent, DWORD dwTime  );

VOID  CALLBACK  CBTimerPocCBTimerPoc( HWND hwnd, UINT  uMsg, UINT_PTR idEvent, DWORD dwTime  )
{     
    
    if ( NULL != g_pDecoder )
    {
        g_pDecoder->OAskKeyFrame( idEvent );
    } 
}

CCallBackBase* CDecoder::m_pCBAskKeyFrame = NULL;


CDecoder::CDecoder() 
{   
    m_hTimerAskKeyFrm = 0;
    m_hTimerAskKeyFrmForce = 0;

    m_nAskKeyFrameCnt = 0;
    g_pDecoder = this;
    m_hMonitor = NULL;
    m_hFullScreenDlg = NULL;
    
    m_bAudio = TRUE;
    m_emMediaMode = emTPMediaAV;
    ZeroMemory(&m_tVideoNetParam, sizeof(TLocalNetParam));
    ZeroMemory(&m_tAudioNetParam, sizeof(TLocalNetParam));
    ZeroMemory(&m_tAudioAACParam, sizeof(TAudAACParam));
    
    ZeroMemory(&m_tSVDecStatis, sizeof(TKdvDecStatis));
    
    m_bPlayed = FALSE;
    m_bKeyFrame = FALSE;
    m_bInited = FALSE;
    m_pcDecoder = NULL;
    
    m_bG7221cReserve = FALSE;
	InitDecoder();
}

CDecoder::~CDecoder()
{   
    StopPlay();

    if (m_pcDecoder != NULL) 
    {
        delete m_pcDecoder;
        m_pcDecoder = NULL;
    }
    
 
}

 

void CDecoder::SetWnd(HWND hwndPlay )
{
    m_hMonitor = hwndPlay;
    m_pcDecoder->SetPlayHwnd(hwndPlay);
    
}

//dwRTPAddr , dwRTCPAddr  ������ 
void CDecoder::SetInfo(u16 wRTPPort, u32 dwRTPAddr, u32 dwRTCPAddr)
{ 
    dwRTPAddr = htonl(dwRTPAddr);
    dwRTCPAddr = htonl(dwRTCPAddr);
    
	m_tVideoNetParam.m_tLocalNet.m_dwRTPAddr = dwRTPAddr;
	m_tVideoNetParam.m_tLocalNet.m_dwRTCPAddr = dwRTCPAddr;
    m_tVideoNetParam.m_tLocalNet.m_wRTPPort = wRTPPort;
	m_tVideoNetParam.m_tLocalNet.m_wRTCPPort = wRTPPort + 1;

	m_tAudioNetParam.m_tLocalNet.m_dwRTPAddr = dwRTPAddr;
	m_tAudioNetParam.m_tLocalNet.m_dwRTCPAddr = dwRTCPAddr;
    m_tAudioNetParam.m_tLocalNet.m_wRTPPort = wRTPPort + 2;
	m_tAudioNetParam.m_tLocalNet.m_wRTCPPort = wRTPPort + 3;

    
}


void  CDecoder::SetVideoBackParam( u16 wRTPVedioPort, u32 dwRTPVedioAddr )
{
    m_tVideoNetParam.m_dwRtcpBackAddr = dwRTPVedioAddr;
    m_tVideoNetParam.m_wRtcpBackPort = wRTPVedioPort ;
 
}

void  CDecoder::SetAudioBackParam(  u16 wRTPAudioPort, u32 dwRTPAudioAddr  )
{
     
    m_tAudioNetParam.m_dwRtcpBackAddr = dwRTPAudioAddr;
    m_tAudioNetParam.m_wRtcpBackPort = wRTPAudioPort ; 
    
}


u16  CDecoder::SetNetFeedbackVideoParam(TNetRSParam tNetRSParam, BOOL32 bRepeatSnd/* = FALSE*/)
{
    if(NULL == m_pcDecoder)
    {
        return -1;
    }

    return m_pcDecoder->SetNetFeedbackVideoParam( tNetRSParam, bRepeatSnd );
}


u16  CDecoder::SetNetFeedbackAudioParam(TNetRSParam tNetRSParam, BOOL32 bRepeatSnd/* = FALSE*/)
{
    if(NULL == m_pcDecoder)
    {
        return -1;
    }
    
    return m_pcDecoder->SetNetFeedbackAudioParam( tNetRSParam, bRepeatSnd );
}

//���ý�������ǰ����Ƶ��ʽ(���ܡ�����)
void CDecoder::SetVideoParam(const TMediaParam& tMonitorParam )
{
    u8 byEncryptMode;
    if(NULL == m_pcDecoder)
    {
        return;
    }
    
    //���ñ��ؼ����Ƶ��̬�غɵ�payloadֵ
    m_pcDecoder->SetVideoActivePT(tMonitorParam.abyDynamicPayLoad[0] , 
		tMonitorParam.abyRealType[0]);
	m_pcDecoder->SetAudioActivePT( tMonitorParam.abyDynamicPayLoad[1],
		tMonitorParam.abyRealType[1]);

 
 
 	
  	if( tMonitorParam.abyRealType[1] == MEDIA_TYPE_G7221C)//�����G7221����G7221c
    {
  	    
        m_pcDecoder->SetReverseG7221c( m_bG7221cReserve );
         
    }


	//������Ƶ����key�ִ��Լ�����ģʽ
	if( tMonitorParam.atEncryptKey[0].byLen != 0  )
	{
		byEncryptMode = AES_ENCRYPT_MODE;
		m_pcDecoder->SetVidDecryptKey((char*)(tMonitorParam.atEncryptKey[0].byKey),
			tMonitorParam.atEncryptKey[0].byLen, byEncryptMode);
		m_pcDecoder->SetAudDecryptKey((char*)(tMonitorParam.atEncryptKey[1].byKey),
			tMonitorParam.atEncryptKey[1].byLen, byEncryptMode);
	}
	else
	{
		//byEncryptMode = AES_ENCRYPT_MODE;
		m_pcDecoder->SetVidDecryptKey(NULL,0, 0);
		m_pcDecoder->SetAudDecryptKey(NULL, 0, 0);
	}
}

void CDecoder::StartPlay()
{    

	StartDec(); 
    AskKeyFrame( TRUE );
	m_bPlayed = TRUE;
    SetOnlyKeyFrame(FALSE);
}

void CDecoder::StartDec()
{
    ASSERT(m_hMonitor != NULL);

	ASSERT(m_pcDecoder != NULL);

    m_pcDecoder->SetPlayHwnd(m_hMonitor);

	if(m_emMediaMode == emTPMediaAV)
	{
		PlayVideo();
        if (m_bAudio) 
        {
            PlayAudio();
        }
	}
	else if(m_emMediaMode == emTPMediaVideo)
	{
		PlayVideo();
	}
	else if(m_emMediaMode == emTPMediaAudio && m_bAudio)
	{
		PlayAudio();
	}
}
void CDecoder::StopPlay()
{   
    KillTimer( NULL, m_hTimerAskKeyFrm );
    KillTimer( NULL, m_hTimerAskKeyFrmForce );

	StopDec();
	m_bPlayed = FALSE;
    m_bKeyFrame = FALSE;
}
void CDecoder::StopDec()
{
	if (m_pcDecoder == NULL) 
    {
        return;
    }
    
	if(m_emMediaMode == emTPMediaAV)
	{
		StopVideo();
        if (m_bAudio) 
        {
            StopAudio();
        }
	}
	else if(m_emMediaMode == emTPMediaVideo)
	{
		StopVideo();
	}
	else if(m_emMediaMode == emTPMediaAudio && m_bAudio)
	{
		StopAudio();
	}
}

BOOL32 CDecoder::IsWaitKeyFrame()
{ 
    TKdvDecStatis  tKdvDecStatis;
    m_pcDecoder->GetDecoderStatis( tKdvDecStatis );
    return tKdvDecStatis.m_bVidCompellingIFrm;
}

void CDecoder::PlayVideo()
{
    StopVideo();

	if(CODEC_NO_ERROR != m_pcDecoder->SetVideoNetRcvParam(&m_tVideoNetParam))//����������ղ���
	{
        SendError();
	}
	if(CODEC_NO_ERROR != m_pcDecoder->StartVideoDec())//��ʼͼ�����
	{
        SendError();
    }
	if(CODEC_NO_ERROR != m_pcDecoder->StartRcvVideo())//��ʼ�������ͼ��
	{
        SendError();
	}
}

void CDecoder::StopVideo()
{
    m_pcDecoder->StopRcvVideo();
	m_pcDecoder->StopVideoDec();
}

void CDecoder::PlayAudio()
{
    StopAudio();

	if(CODEC_NO_ERROR != m_pcDecoder->SetAudioNetRcvParam(&m_tAudioNetParam))//����������ղ���
	{
        SendError();
	}	
	//����AAC����
	OspPrintf(TRUE, FALSE, "[MTC]PlayAudio: SamplePerSecond = %d, Channel = %d\n", 
		m_tAudioAACParam.dwSamplePerSecond, m_tAudioAACParam.dwChannel);
	if(CODEC_NO_ERROR != m_pcDecoder->SetAudioDecParam(m_tAudioAACParam.dwSamplePerSecond, m_tAudioAACParam.dwChannel))
	{
        SendError();
	}

	if(CODEC_NO_ERROR != m_pcDecoder->StartAudioDec())//��ʼ��������
	{
        SendError();
	}
	if(CODEC_NO_ERROR != m_pcDecoder->StartRcvAudio())//��ʼ�����������
	{
        SendError();
	}
}

void CDecoder::StopAudio()
{
	m_pcDecoder->StopRcvAudio();
	m_pcDecoder->StopAudioDec();
}
 
 
 

BOOL CDecoder::IsPlayed()
{
    return m_bPlayed;
}

 
u16 CDecoder::SetOnlyKeyFrame(BOOL bKeyFrame)
{
    u16 wResult = m_pcDecoder->SetOnlyKeyFrame(bKeyFrame);
    if (wResult == 0)
    {
        m_bKeyFrame = bKeyFrame;
    }
    return wResult;
}

  
void CDecoder::InitDecoder()
{
	if(!m_pcDecoder)
	{
		m_pcDecoder = new CKdvDecoder;
	}

	if(!m_pcDecoder)
	{
		return;
	}
	
	TVideoDecoder tVideoDecoder;
	TAudioDecoder tAudioDecoder;

	ZeroMemory(&tVideoDecoder,sizeof(TVideoDecoder));
	ZeroMemory(&tAudioDecoder,sizeof(TAudioDecoder));
	
	u16 wRet = 0;
	
	tVideoDecoder.m_dwCpuId = 0;
	tVideoDecoder.m_nPriority = THREAD_PRIORITY_LOWEST;
	tVideoDecoder.m_nVideoPlayBufNum = 12;
	tVideoDecoder.m_nVideoStartPlayBufNum = 4;
	tVideoDecoder.m_bOverlay = FALSE;
	tVideoDecoder.m_byMask = SOFT_DEC_ONLY;
	tVideoDecoder.m_hwPlayVideo = m_hMonitor;
	
	tAudioDecoder.m_byAudioMode = AUDIO_MODE_PLAY;
	tAudioDecoder.m_nAudioPlayBufNum = 8;
	tAudioDecoder.m_nAudioStartPlayBufNum = 3;
	
	wRet = m_pcDecoder->CreateDecoder(&tVideoDecoder, &tAudioDecoder);
	if(wRet != CODEC_NO_ERROR)
	{
		BOOL bDel = TRUE;
		m_pcDecoder->GetLastError((u32 &)wRet);
		CString strError;
		strError.Format( "��������������%d" , wRet);
		switch(wRet)
		{
		case ERROR_DEC_ICOPEN:
				strError = "�򿪽�����ʧ��";//STRING_OPEN_DECODE_DRV_ERROR
				break;
		case ERROR_DEC_WAVEOPEN:
        case ERROR_DEC_NEW:  //added by Chris 20050128
			{
				bDel = FALSE;//��ɾ������
				strError = "����Ƶ��ʧ��";//STRING_OPEN_AUDIO_CARD_ERROR;
				//modify by jason0402
				m_bAudio = FALSE;
				break;
			}				
		case ERROR_DEC_WAVE_ENCOPEN:
			{
				strError = "����Ƶ������ʧ��";//STRING_OPEN_AUDIO_DECODE_ERROR;
				break;
			}
		default :break;
		}
        //::SendMessage(m_hParent, WM_DECODER_ERROR, (WPARAM)(LPCTSTR)strError, 0);

		if(bDel)
		{
			if (m_pcDecoder) 
			{
                delete m_pcDecoder;
                m_pcDecoder = NULL;
			}
			return;
		}
    }
}

void CDecoder::SetAACParam(const TAudAACParam& tAACParam)
{
	memcpy(&m_tAudioAACParam, &tAACParam, sizeof(TAudAACParam));
	if(NULL == m_pcDecoder)
	{
		return;
	}
	//���ø�������
	OspPrintf(TRUE, FALSE, " SetAACParam To Decoder: SamplePerSecond = %d, Channel = %d\n", 
			m_tAudioAACParam.dwSamplePerSecond, m_tAudioAACParam.dwChannel);
	m_pcDecoder->SetAudioDecParam(m_tAudioAACParam.dwSamplePerSecond, m_tAudioAACParam.dwChannel);
				
}

CKdvDecoder* CDecoder::GetDecoder()
{
	if ( m_pcDecoder != NULL )
	{
		return m_pcDecoder;
	}
	else
		return NULL;
}


 
void CDecoder::SendError()
{
    u32 dwError = 0;
    m_pcDecoder->GetLastError(dwError);
    CString csError;
    csError.Format("����������%d" , dwError);
   // ::SendMessage(m_hParent, WM_DECODER_ERROR, (WPARAM)(LPCTSTR)csError, 0);
}

void CDecoder::SetG7221cReverse(BOOL bReverse)
{
    m_bG7221cReserve = bReverse;	
}

u16   CDecoder::SetAudioVolume(u8 byVolume )   /*���������������*/	
{
    return m_pcDecoder->SetAudioVolume(byVolume);
}
u16    CDecoder::GetAudioVolume(u8 &pbyVolume ) /*�õ������������*/
{
    return m_pcDecoder->GetAudioVolume(pbyVolume);
}	

void CDecoder::AskKeyFrame( BOOL32 bForce )
{   
    KillTimer( NULL, m_hTimerAskKeyFrm );
    KillTimer(  NULL, m_hTimerAskKeyFrmForce );
    if ( m_pCBAskKeyFrame != NULL )
    {
        (*m_pCBAskKeyFrame)( bForce );
    }
    m_hTimerAskKeyFrmForce = SetTimer(NULL,0, DEC_CHECK_KEY_FRSME_ELAPS,CBTimerPocCBTimerPoc);
}


BOOL32 CDecoder::SetStaticPicturePath( CString strImgPath)
{
	if ( NULL == m_pcDecoder )
	{
		return FALSE;
	}

	return m_pcDecoder->SetStaticPicturePath( (PSTR)(LPCTSTR)strImgPath);
}

/*====================================================================
  �� �� ���� OnAskKeyFrame
  ��    �ܣ� 
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� CMtMsg *const ptMsg
  �� �� ֵ�� void  
======================================================================*/
void CDecoder::OAskKeyFrame( UINT timerID )
{  
    if ( NULL == m_pCBAskKeyFrame )
    {
        return;
    }
    
    TKdvDecStatis  tKdvDecStatis;
    m_pcDecoder->GetDecoderStatis( tKdvDecStatis );
   
    bool bGoOn = true;  //�Ƿ��������timer
    bool bAsk = false;  //�Ƿ�����ؼ�֡
    if ( timerID == m_hTimerAskKeyFrm )
    {
   
        KillTimer(NULL,timerID);

        if (  ( TRUE == tKdvDecStatis.m_bVidCompellingIFrm )  //��˶���ȷ�ϣ���֡���⣬�˴����账���ɽ���⴦�� 2012.9.17 by yjj
            /*|| ( tKdvDecStatis.m_dwVideoLoseFrame != m_tSVDecStatis.m_dwVideoLoseFrame )*/ )
        { 	 
            (*m_pCBAskKeyFrame)( FALSE );
            memcpy(&m_tSVDecStatis, &tKdvDecStatis, sizeof(TKdvDecStatis) );
        }
        
        m_hTimerAskKeyFrm = SetTimer(NULL,0, DEC_CHECK_KEY_FRSME_ELAPS,CBTimerPocCBTimerPoc);
    }
    else if ( timerID == m_hTimerAskKeyFrmForce )
    {
        KillTimer(NULL,m_hTimerAskKeyFrmForce);
        KillTimer( NULL, m_hTimerAskKeyFrm );
        
        if ( m_nAskKeyFrameCnt >= 2 )
        {
            m_nAskKeyFrameCnt = 0;
            bAsk = false;
            bGoOn = false;
            
            m_hTimerAskKeyFrm = SetTimer(NULL,0, DEC_CHECK_KEY_FRSME_ELAPS,CBTimerPocCBTimerPoc);  //��ϵ����3�κ�תΪ��ʱȥ����Ƿ���Ҫȥ����ؼ�֡
        }
        else
        {   
            
            m_nAskKeyFrameCnt ++;
            (*m_pCBAskKeyFrame)( TRUE );
            memcpy(&m_tSVDecStatis, &tKdvDecStatis, sizeof(TKdvDecStatis) );
            m_hTimerAskKeyFrmForce = SetTimer(NULL,0, DEC_CHECK_KEY_FRSME_ELAPS,CBTimerPocCBTimerPoc);
        }
    }
    else
    {
        return;
    }  
   

}