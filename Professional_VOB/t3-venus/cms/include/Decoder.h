// Decoder.h: interface for the CDecoder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DECODER_H__53DB286A_35A9_48CE_B5CC_DC2AE7D0A62B__INCLUDED_)
#define AFX_DECODER_H__53DB286A_35A9_48CE_B5CC_DC2AE7D0A62B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "cmsstruct.h" 


//�����
#define SOFT_CODEC 
#include "codeclib.h"
//#pragma comment(lib, "kdvencoder.lib")  
#pragma comment(lib, "KdvDecoder.lib")
#pragma comment(lib, "kdvmedianet.lib")
#pragma comment(lib, "kdvencrypt.lib")
#pragma comment(lib, "kdimg.lib")

typedef struct tagMediaParam
{
    u8 abyRealType[2];			        //��һ·��Ƶ����Ƶ���غ�����
    u8 abyDynamicPayLoad[2];			//��һ·��Ƶ����Ƶ�Ķ�̬�غ�����
    TTpEncryptKey  atEncryptKey[2];		//��һ·��Ƶ����Ƶ����Կ
//    EmSite emSite;
public:
    tagMediaParam()
    {
        memset(this, 0 ,sizeof(struct tagMediaParam));
    }
}TMediaParam; 


typedef struct tagAudAACParam
{
    u32 dwSamplePerSecond;
    u32 dwChannel;
}TAudAACParam;





class CCallBackBase
{ 
public:
    //����ص������ĸ�ʽ
    virtual void operator() (BOOL32) = 0;
};

template<class T> class CClsCallBackFun:public  CCallBackBase
{
public:
    //����ص������ĸ�ʽ
    typedef void (T::*MemberFunctionType)(BOOL32);
    
    // �����ʱ����ҪΪ������ֵ
    CClsCallBackFun ( MemberFunctionType pFunc, T* pObject )
    {
        m_pObject = pObject;
        m_pFuc = pFunc ;
    }

    
    virtual void operator()(BOOL32 bValue )
    {
         (m_pObject->*m_pFuc)( bValue );
    }
    
private:
    T* m_pObject;
    MemberFunctionType m_pFuc;	
};





class CDecoder  
{
public:
	CDecoder();
	virtual ~CDecoder();

public:
    CKdvDecoder* GetDecoder();
    void SnapShot();
    u16  SetOnlyKeyFrame(BOOL bKeyFrame);
    BOOL IsPlayed();
    BOOL IsKeyFrame() { return m_bKeyFrame;}
   
    
    //  dwRTPAddr��dwRTCPAddrֵ��һ���ģ����Ǳ��ص�ַ 
    void SetWnd(HWND hwndPlay);
    void SetInfo(u16 wRTPPort, u32 dwRTPAddr, u32 dwRTCPAddr);
    void SetVideoBackParam( u16 wRTPVedioPort, u32 dwRTPVedioAddr );
    void SetAudioBackParam(  u16 wRTPAudioPort, u32 dwRTPAudioAddr  );
    void StartPlay();
    void StopPlay();
    void StartDec();
    void StopDec(); 
    BOOL32 IsWaitKeyFrame();  //�Ƿ��ڵȴ��ؼ�֡


    u16 SetNetFeedbackVideoParam(TNetRSParam tNetRSParam, BOOL32 bRepeatSnd = FALSE);
	u16 SetNetFeedbackAudioParam(TNetRSParam tNetRSParam, BOOL32 bRepeatSnd = FALSE);
     
    void SetVideoParam(const TMediaParam& tMonitorParam);
    void SetAACParam(const TAudAACParam & tAACParam);
    void SetG7221cReverse(BOOL bReverse);


    u16    SetAudioVolume(u8 byVolume );  /*���������������*/	
    u16    GetAudioVolume(u8 &pbyVolume );/*�õ������������*/ 
    
    void AskKeyFrame( BOOL32 bForce ); // ����3������ؼ�֡


    //ͨ���궨�������øú���
    static void SetAskFrameFun( CCallBackBase *pAskKeyFrame )
    { m_pCBAskKeyFrame = pAskKeyFrame; }
     

    void OAskKeyFrame(  UINT timerID );

    //�Ժ��ļ�ֻҪС�ڷֱ���1920*1080�����ҿ����2���������Ϳ�����
    BOOL32 SetStaticPicturePath( CString strImgPath );
private:
    void InitDecoder();
    void PlayVideo();
    void StopVideo();
    void PlayAudio();
    void StopAudio();
    void SendError();

    
private:
    BOOL m_bInited;
    BOOL m_bPlayed;
    BOOL m_bKeyFrame;         //�Ƿ��֡����
    CKdvDecoder     *m_pcDecoder;
    HWND            m_hMonitor;
    HWND            m_hFullScreenDlg;

     
    TLocalNetParam  m_tVideoNetParam;
    TLocalNetParam  m_tAudioNetParam;
    EmTpMediaType   m_emMediaMode;
    BOOL            m_bAudio;
    
    TAudAACParam    m_tAudioAACParam;
	BOOL			m_bG7221cReserve;
   
    TKdvDecStatis   m_tSVDecStatis;
    static CCallBackBase*   m_pCBAskKeyFrame;
    

    u16             m_nAskKeyFrameCnt;
    s16             m_hTimerAskKeyFrm;
    s16             m_hTimerAskKeyFrmForce;// //ǿ������ؼ�֡��һ�����ڸտ�������������������3�ιؼ�֡ PS:���ڽ�������δ�ȶ��Ƿ���Ҫ�ؼ�֡״̬����׼ȷ
};


/*
* ע��ȫ�ֺ����������Ա������Ϊ����ָ�� \n
* dwMsgID ����ID func ������ obj ��ָ�� objType ������
*/
 
#define SET_ASK_MAIN_FRAME_FUN(func, obj, objType ) \
CDecoder::SetAskFrameFun( new CClsCallBackFun<objType>( func, obj ) );
 

#endif // !defined(AFX_DECODER_H__53DB286A_35A9_48CE_B5CC_DC2AE7D0A62B__INCLUDED_)
