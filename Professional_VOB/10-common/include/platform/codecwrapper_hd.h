/*****************************************************************************
  ģ����      : codecwrapper_t300.a
  �ļ���      : codecwrapper_t300.h
  ����ļ�    : codecwrapperdef_hd.h
  �ļ�ʵ�ֹ���: 
  ����        : ����
  �汾        : V4.0  Copyright(C) 2007-2008 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2013/02/20  4.0         ����        ����
******************************************************************************/
#ifndef _CODECWRAPPER_T300_H_
#define _CODECWRAPPER_T300_H_

#ifdef _CODECWRAPPER_TOS_MODULE_ //2013-3-26

#include "tos/codecwrapper_hd.h"

#else

#include "codecwrapperdef_hd.h"

class CVideoEncoder;
class CAudioEncoder;
class CVideoDecoder;
class CAudioDecoder;


//t300 ��Ƶʹ�� start
enum enVideoPIPIndexEX
{
	VIDEO_PIPINDEX_NULL_EX = 0,             //�ջ���
	VIDEO_PIPINDEX_LOCAL_EX,			    //����
	VIDEO_PIPINDEX_DEC1,					//������1
	VIDEO_PIPINDEX_DEC2,					//������2
	VIDEO_PIPINDEX_DEC3,					//������3
	VIDEO_PIPINDEX_AUX_LOCAL,
	VIDEO_PIPINDEX_INVALID_EX
};

//������������Ϣ���û�ͨ���������²�������8377�ϴ���Զ�̵�codec�����ֲ�����ָ����netra��
typedef struct tagNetraCodecInfo
{
	u32     dwNetraID;						//codec���ڵ�Netra��� (enNetraID)
	u32     dwIndex;						//�����ͨ���� 0~x
	u32     dwVidPort;						//�ɼ���(������) ���ſ�(������)
	u32     dwPlayStd;						//video����ʽ��only decoder
	u32     bAdapterOn;						//�����书��
	void*   pReserve;						//���������������书�ܴ�����˴���չ����(TAdapterInfo)
}TNetraCodecInfo;

//���������չ���ܺ󣬻ص�������ַ������䣬���ڸ��û��ϴ��������ݣ��˽ṹ��������������������
typedef struct tagAdapterInfo
{
	u32     dwWidth;						//����ֱ��ʿ��
	u32     dwHeight;						//����ֱ��ʸ߶�
	u32     dwFramerate;					//����֡��
	u32     dwMediaType;					//�����������ͣ�Ĭ��264
	u32     dwBitrate;
	u32     dwProfile;						//Hp or BP
	u32     dwMaxKeyFrameInterval;				//�趨���ؼ�֡���
	FRAMECALLBACK pStreamCallBack;			//����������ص�������ַ
	void*   pContext;						//�ص�������
}TAdapterInfo;
//t300 ��Ƶʹ�� end


class CKdvVidEnc
{
public:
	CKdvVidEnc();
	~CKdvVidEnc();
public:
	//���¼��ݣ�t300 ��ʹ��
	u16    CreateEncoder(TEncoder *pEncoder);                 /*HD1��ʹ��*/
    u16    Create(TVidEncInit* pEnc, void* pReserve = NULL);  /*���������ն���ʹ������ӿ�*/
	u16    CreateHD3(TVidEncHD3RD* pEnc);							/*��������ʹ������ӿ�*/

	/************************************************************************/
	/* ������:  Create                                                      */  
	/* ��������:                                                            */
	/*          TNetraCodecInfo*   pEnc    ������������ʵ��λ���Լ����     */
	/* ��������: �������Ĵ��� �����ɹ�����0 								*/
	/************************************************************************/	
    u16    Create(TNetraCodecInfo* pEnc); 

	/*��ȡ������״̬*/
    u16    GetEncoderStatus(TKdvEncStatus &tKdvEncStatus);

	/*��ȡ��������ͳ����Ϣ*/
    u16    GetEncoderStatis(TKdvEncStatis &tKdvEncStatis);

	/************************************************************************/
	/* ������:   SetVidDataCallback                                          */  
	/* ��������:                                                             */
	/*           FRAMECALLBACK fVidData     �ص�������ַ                     */
	/*           void* pContext             �ص������Ĳ���					*/
	/*																		*/
	/* ��������:	������Ƶ�������ݻص�									*/
	/************************************************************************/
	u16    SetVidDataCallback(FRAMECALLBACK fVidData, void* pContext); 

    /************************************************************************/
    /* ������:     SetEncQualityEnhance                                      */  
    /* ��������:                                                             */
    /*              BOOL32 bEnhance                                         */
    /* ��������:  ׷�ӱ��������Ƚӿڣ�										*/
	/*				TRUEΪ��������ȣ�FALSEΪ�ر������ȡ�����������ʧ	    */
    /************************************************************************/
	u16    SetEncQualityEnhance(BOOL32 bEnhance);
	
	/************************************************************************/
	/* ������:   SetVidCapPortType                                           */  
	/* ��������:                                                             */
	/*           u32 dwType                                                  */
	/* ��������:	���òɼ��ӿ�											*/
	/************************************************************************/
	u16    SetVidCapPortType(u32 dwType);

	/************************************************************************/
	/* ������:  SetVideoEncParam                                             */  
	/* ��������:                                                             */
	/*             TVideoEncParam *ptVideoEncParam                          */
	/* ��������: ���ñ�����������������е���								*/
	/************************************************************************/
    u16    SetVideoEncParam(const TVideoEncParam *ptVideoEncParam); 

	/*�õ���Ƶ�������*/
    u16    GetVideoEncParam(TVideoEncParam &tVideoEncParam );
	
	/*��ʼѹ��ͼ��*/
    u16    StartEnc();

	/*ֹͣѹ��ͼ��*/
    u16    StopEnc(); 

	/************************************************************************/
	/* ������:         GetVideoSrcInfo                                       */  
	/* ��������:                                                             */
	/*                 TVidSrcInfo& tInfo                                    */
	/* ��������:	��ȡ������Ƶ�ź���ʽ									*/
	/************************************************************************/
    u16    GetVideoSrcInfo(TVidSrcInfo& tInfo); /**/

	/************************************************************************/
	/* ������:      ScaleVideoCap											*/  
	/* ��������:															*/
	/*              u32 dwVidSrcPort :��Ƶ�ɼ�����							 */
	/*              u8 byType        :�������� VIDCAP_SCALE_BRIGHTNESS ��	*/
	/*				u8 byValue       :������ֵ 0~255; 0x80ΪĬ��ֵ			*/
	/* ��������:	������Ƶ�ɼ�����										*/
	/************************************************************************/
    u16    ScaleVideoCap(u32 dwVidSrcPort,u8 byType, u8 byValue); 

	/************************************************************************/
	/* ������:      SetFastUpata                                             */  
	/* ��������:                                                             */
	/*              BOOL32 bIsNeedProtect �Ƿ���1s�ڱ���                   */
	/* ��������:	ǿ�Ʊ�һ֡�ؼ�֡�����ü������1s						*/
	/************************************************************************/
	u16    SetFastUpata(BOOL32 bIsNeedProtect = TRUE);   

	/************************************************************************/
	/* ������:      SetSendStaticPic                                         */  
	/* ��������:                                                             */
	/*              BOOL32  bSendStaticPic                                   */
	/* ��������:	���;�̬ͼƬ											 */
	/************************************************************************/
	u16    SetSendStaticPic(BOOL32  bSendStaticPic);

	/************************************************************************/
	/* ������:         StartAddLogoInEncStream                              */  
	/* ��������:                                                            */
	/*                 TFullLogoParam &tLogoParm                            */
	/* ��������:	����̨�����������̨��									*/
	/************************************************************************/
    u16	   StartAddLogoInEncStream(TFullLogoParam &tLogoParm);

	/************************************************************************/
	/* ������:         StopAddLogoInEncStream                               */  
	/* ��������:                                                            */
	/* ��������:	�ر�̨��												*/
	/************************************************************************/
	u16    StopAddLogoInEncStream();

	/************************************************************************/
	/* ������:   SetVidEncResizeMode                                         */  
	/* ��������:                                                             */
	/*           s32 nMode    0-�ڱߣ� 1-�ñߣ� 2-�ǵȱ�����                 */
	/* ��������: ���ñ���ǰ������ԣ��Ӻڱߣ��ñߵȣ�						*/
	/************************************************************************/
    u16    SetVidEncResizeMode(s32 nMode);

	/************************************************************************/
	/* ������:   SetVidPlayPolicy                                            */  
	/* ��������:                                                             */
	/*           u32 dwTimeout     ��ʱ                                      */
	/*           u32 dwPlayType    ��ͼ���������         					*/
	/* ��������: ���ñ��ز��Ų��ԣ�֧�������;�̬ͼ							*/
	/************************************************************************/
    u16    SetVidPlayPolicy(u32 dwTimeout = 5, u32 dwPlayType = EN_PLAY_LAST);

	/************************************************************************/
	/* ������:      SetVidSrcCutLines                                       */  
	/* ��������:                                                             */
	/*             u32 dwLCutLine ���ñ���������16 ������                 */
	/*             u32 dwRCutline �Ҳ�ñ���������16 ������					*/
	/* ��������: �ɼ�ͼ�����Ҳñߣ���Ҫ���ڲɼ�ͼ�����ұ�Ե���������		*/
	/************************************************************************/
	u16    SetVidSrcCutLines(u32 dwLCutLine, u32 dwRCutline);
protected:
	CVideoEncoder* m_pCodec;
};


class CKdvVidDec
{
public:
	CKdvVidDec();
	~CKdvVidDec();
public:
	//��֮ǰ���ݣ�t300 ppc�಻ʹ��
	u16	   CreateDecoder(TDecoder *pDecoer);   /*HDU, HD1��ʹ��*/
    u16    Create(TVidDecInit* pDec, void* pReserve = NULL); /*���������ն���ʹ������ӿ�*/
	u16    CreateHD3(TVidDecHD3RD* pDec);


	/************************************************************************/
	/* ������:    Create                                                    */  
	/* ��������:                                                            */
	/*            TNetraCodecInfo* pDec    ��������������                   */
	/* ��������:  ����������												*/
	/************************************************************************/
    u16    Create(TNetraCodecInfo* pDec);

	/************************************************************************/
	/* ������:      SetData                                                 */  
	/* ��������:                                                             */
	/*              TFrameHeader& tFrameInfo                                */
	/* ��������:	������Ƶ��������										*/
	/************************************************************************/
	u16    SetData(const TFrameHeader& tFrameInfo);  
	
	/*��ʼͼ�����*/
    u16    StartDec();

	/*ֹͣͼ�����*/
    u16    StopDec(); 

	/*��ȡ������״̬*/
	u16    GetDecoderStatus(TKdvDecStatus &tKdvDecStatus);

	/*��ȡ��������ͳ����Ϣ*/
    u16    GetDecoderStatis(TKdvDecStatis &tKdvDecStatis);	

	//��������
	u16    StartAdapter();
	//ֹͣ����
	u16    StopAdapter();
	//��ȡ�������ò���
	u16    GetAdapterStatus(TAdapterInfo &tKdvEncStatus, BOOL32 &bStart);
	//��ȡ����ͳ����Ϣ
	u16    GetAdapterStatis(TKdvEncStatis &tKdvEncStatis);
	//������ؼ�֡
	void	FastUpdateAda();

	/************************************************************************/
	/* ������:      SetVidPIPParam                                           */  
	/* ��������:                                                             */
	/*             enVideoPIPMode enMode ���л����                          */
	/*             enVideoPIPIndexEX enIndex[3] �ӻ�������           		*/
	/* ��������:	������Ƶ���л�ģʽ�����֧��3����ϳ�					*/
	/************************************************************************/
    u16 SetVidPIPParam(enVideoPIPMode enMode, enVideoPIPIndexEX enIndex[3]);
    

	/************************************************************************/
	/* ������:      SetPlayScale                                             */  
	/* ��������:                                                             */
	/*               u16 wWidth  :��ʾ�������0Ϊ�Զ�                       */
	/*               u16 wHeight :��ʾ�߱�����0Ϊ�Զ�						*/
	/* ��������:	���ò����豸����ʾ����									*/
	/*               ������ʽΪ16:9,����4:3��ͼ�����¼Ӻڱ�                 */
	/*               ������ʽΪ4:3,����16:9��ͼ�����ҼӺڱ�                 */
	/************************************************************************/
    u16    SetPlayScale(u16 wWidth, u16 wHeight);
    
	/************************************************************************/
	/* ������:      SetVidPlyPortType                                        */  
	/* ��������:                                                             */
	/*               u32 dwType   ���ſ�                                    */
	/* ��������:	���������벥�ſ�										*/
	/************************************************************************/
    u16    SetVidPlyPortType(u32 dwType);

	/************************************************************************/
	/* ������:      SetVideoPlyInfo                                          */  
	/* ��������:                                                             */
	/*               u32 dwOutType     ��Ƶ��ʽö��                          */
	/* ��������:	������Ƶ����ź���ʽ									 */
	/************************************************************************/
    u16    SetVideoPlyInfo(u32 dwOutType = VID_OUTTYPE_ORIGIN);

	/************************************************************************/
	/* ������:      SetVideoPlyInfo                                          */  
	/* ��������:                                                             */
	/*               TVidSrcInfo* ptInfo     ��Ƶ��ʽ                        */
	/* ��������:	������Ƶ����ź���ʽ									 */
	/************************************************************************/
    u16    SetVideoPlyInfo(TVidSrcInfo* ptInfo); 

	/*��ȡ�����Ƶ�ź���ʽ*/
    u16    GetVideoSrcInfo(TVidSrcInfo& tInfo);   

	/************************************************************************/
	/* ������:     SetVidDecResizeMode                                       */  
	/* ��������:                                                             */
	/*             s32 nMode     ������ԣ�0���Ӻڱߣ�1���ñ�; 2:�ǵȱ�      */
	/* ��������:   ���ý���������										*/
	/************************************************************************/
	u16	   SetVidDecResizeMode(s32 nMode);

	/************************************************************************/
	/* ������:     SetVidOutCallBack                                        */  
	/* ��������:                                                             */
	/*             VIDOUTTYPECALLBACK fVidOutType  �ص�������ַ             */
	/* ��������:	������Ƶ��ʽ�����ɹ���ص�����							*/
	/************************************************************************/
	u16	   SetVidOutCallBack(VIDOUTTYPECALLBACK fVidOutType);

	/************************************************************************/
	/* ������:      TestImage                                               */  
	/* ��������:                                                            */
	/*              BOOL32 bSet                                             */
	/* ��������:	����/�رյô�����										*/
	/************************************************************************/
	u16	   TestImage(BOOL32 bSet);

	/************************************************************************/
	/* ������:     SnapShot                                                  */  
	/* ��������:                                                             */
	/*             s8* pFileName    �ļ���ȫ·��                            */
	/* ��������:   ����һ֡����ͼ��Ϊjpeg�ļ�								*/
	/************************************************************************/
	u16    SnapShot(s8* pFileName);

	/************************************************************************/
	/* ������:     SnapShotView                                              */  
	/* ��������:                                                             */
	/*             s8* pFileName    �ļ���ȫ·��                             */
	/* ��������:	����ָ����jpegͼƬ�������ǿ���ͼ��ֹͣ					*/
	/************************************************************************/
	u16    SnapShotView(s8* pFileName);

	/************************************************************************/
	/* ������:     SetVidPlayPolicy                                          */  
	/* ��������:                                                             */
	/*           u32 dwTimeout     ��ʱ                                      */
	/*           u32 dwPlayType    ��ͼ���������         					*/
	/* ��������:	���ý��벥����ͼ����ʾ����								*/
	/************************************************************************/
	u16    SetVidPlayPolicy(u32 dwTimeout = 5, u32 dwPlayType = EN_PLAY_LAST);

protected:
	CVideoDecoder* m_pCodec;
};	


class CKdvAudEnc
{
public:
	CKdvAudEnc();
	~CKdvAudEnc();
public:
	/************************************************************************/
	/* ������:     CreateEncoder                                            */  
	/* ��������:                                                            */
	/*             TEncoder *pEncoder    ����������                         */
	/*             u32 dwDevVersion      �忨�ͺ�                           */
	/* ��������:   ����������								                                */
	/************************************************************************/
	u16    CreateEncoder(TEncoder *pEncoder, u32 dwDevVersion=en_T300_Board);
		
	/************************************************************************/
	/* ������:   SetAudDataCallback                                         */  
	/* ��������:                                                            */
	/*           FRAMECALLBACK fAudData     �ص�������ַ                    */
	/*           void* pContext             �ص������Ĳ���					        */
	/* ��������:	������Ƶ�������ݻص�									                    */
	/************************************************************************/
	u16    SetAudDataCallback(FRAMECALLBACK fAudData, void* pContext);	

	/************************************************************************/
	/* ������:   GetInputAudioPower                                         */  
	/* ��������:   �������빦�ʣ���Χ��0-31                                                      */
	/*                                                                      */
	/* ��������:	��ȡ������Ƶ����									                        */
	/************************************************************************/
	u32    GetInputAudioPower();

	/*��ȡ��ũ�ɼ�����  byPower��Χ:0-31*/
	u16    GetCanonPower(u32 dwAudPort, u8 &byPower);
	
	/*��ȡ������״̬*/ 
	u16    GetEncoderStatus(TKdvEncStatus &tKdvEncStatus);	

	/*��ȡ��������ͳ����Ϣ*/	
	u16    GetEncoderStatis(TKdvEncStatis &tKdvEncStatis );

	/*��ʼ�����ɼ�*/
	u16    StartAudioCap();

	/*ֹͣ�����ɼ�*/
	u16    StopAudioCap(); 

	/*���������������*/
	u16    SetAudioEncParam(u8 byMediaMode, u8 byMediaType=MEDIA_TYPE_PCMU); 
                        
	/*��ȡ�����������*/                          
	u16    GetAudioEncParam(u8 &byAudioEncParam, u8 *pbyMediaType = NULL);

	/*��ʼѹ������*/
	u16    StartAudioEnc();

	/*ֹͣѹ������*/
	u16    StopAudioEnc(); 

	/*�����Ƿ�ྲ������*/
	u16    SetAudioMute( BOOL32 bMute );    

	/*���������������*/	
	u16    SetAudioVolume(u8 byVolume ); 

	/*���õ�����Ƶ�ӿڲɼ�����,ÿ��ֻ������һ·������ɼ��ڵĻ���Ҫ���ö��*/
	u16	   SetSingleAudInputVol(u32 dwAudPort, u32 dwVol);

	/*��ȡ�ɼ�����*/
	u16    GetAudioVolume(u8 &byVolume );

	/*������Ƶ�ɼ��˿ڣ��������󣬼�������Ƶ�ڣ����ڶ�������ֻ������������AEC���������ӿڲ���AEC����*/	
	u16    SetAudInPort(u32 dwAudPort, u32 dwAudMasterMic);  

	/*��ʼ��������*/
	u16    StartAec();

	/*ֹͣ��������*/
	u16    StopAec();
  
    /*����Aecdebugֵ����Χ4-64*/
	u16	   AecDebug(u32 dwDebug);

    /*��ʼsmp����*/
	u16	   StartAgcSmp(); 
	
	/*ֹͣsmp����*/
	u16	   StopAgcSmp(); 
	
	/*��ʼsin����*/
	u16	   StartAgcSin(); 
	
	/*ֹͣsin����*/	
	u16	   StopAgcSin(); 

	/*����������ǿ�ȼ� dwSpeLevel��Χ0-3, 0������3��ǿ*/
    u16    SetSpeLevel(u32 dwAudPort, u32 dwSpeLevel);

	/*�Ƿ�ʹ��������ǿ Ĭ�Ϲر�*/
	u16    StartSpe(u32 dwAudPort, BOOL32 bStart);
protected:
private:
	CAudioEncoder *m_pCodec;
};

class CKdvAudDec
{
public:
	CKdvAudDec();
	~CKdvAudDec();
public:
	/************************************************************************/
	/* ������:     CreateDecoder                                            */  
	/* ��������:                                                            */
	/*             TDecoder *pDecoer     ����������                         */
	/*             u32 dwDevVersion      �忨�ͺ�                           */
	/* ��������:   ����������								                                */
	/************************************************************************/
	u16	   CreateDecoder(TDecoder *pDecoer, u32 dwDevVersion=en_T300_Board);
	
	/*��ȡ������״̬*/
	u16    GetDecoderStatus(TKdvDecStatus &tKdvDecStatus);
	
	/*��ȡ��������ͳ����Ϣ*/	
	u16    GetDecoderStatis(TKdvDecStatis &tKdvDecStatis);

	/*������Ƶ��������*/
	u16    SetData(const TFrameHeader& tFrameInfo); 

	/*��Ƶ���������AAC_LC��AAC_LD��Ч*/ 
	u16    SetAudioDecParam(const TAudioDecParam& tAudParam);

	/*������Ƶ���Ŷ˿�*/
	u16    SetAudOutPort(u32 dwAudPort);  

	/*��ʼ��������*/
	u16    StartDec();	

	/*ֹͣ��������*/
	u16    StopDec(); 	

	/*���������������*/
	u16    SetAudioVolume(u8 byVolume );  	

	/*�õ������������*/	
	u16    GetAudioVolume(u8 &pbyVolume );

	/*���þ���*/
	u16    SetAudioMute(BOOL32 bMute);
		
	/*��ȡ�����Ƶ����*/
	u32    GetOutputAudioPower();
	
	/*��������*/
	u16   PlayRing(s8* pData = NULL);
	
	/*ֹͣ��������*/
	u16   StopRing();

	/*���þ�����,����ÿ��Ƶ�εĵ�������Ŀǰʹ��10��Ƶ��(�ο�ȡֵ��ΧΪ(-12��+12))
	����Զ���һ������swEquVal[10] = {0,  6,  -8,  0, 0, //1~5Ƶ��
									  0,  0,  0,  0, 12, //6~10Ƶ��}   
    dwBufLenָ�ֽ���*/
	u16  SetAudEQValue(s16* pszEQValue, u32 dwBufLen);

	/*Ĭ�Ϲر�*/
	u16  StartAudEQ(BOOL32 bStart);
protected:
private:
	CAudioDecoder *m_pCodec;
};

//���û���ϳ�С����ߴ�λ����Ϣ

void SetSubPicInfo(u32 dwNetraId, TSmallPicRectInfo tSubPicInfo);
//�ɼ�����ϳɿ���
void StartCapMerge(BOOL32 bMerge);
//���������ص�
typedef void (*SPEECHACTIVECALLBACK)(u32 dwChID, void* pContext);

//�������������ص�
u16 SetSpeechActiveCallBack(SPEECHACTIVECALLBACK fSpeechActiveCB, void* pContext);

//����������������ʱ�䣬��λ��
u16 SetSpeechActiveKeepTime(u32 dwKeepTime);

/*=============================================================================
  �� �� ���� SetAudPlayMode
  ��    �ܣ� ������Ƶ����ģʽ
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� u32 dwPlayMode   EN_PLAY_FULL:3·���ţ�EN_PLAY_SINGLE:��·����
             u32 dwChnID      ��·����ʱͨ���ţ���Χ0-2��ֻ��EN_PLAY_SINGLE��Ч
  �� �� ֵ�� u16 
=============================================================================*/
u16 SetAudPlayMode(u32 dwPlayMode = EN_PLAY_FULL, u32 dwChnID = 0);

/*=============================================================================
  �� �� ���� SetAudSubPlay
  ��    �ܣ� ������Ƶ˫�����ز���
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� BOOL32 bPlay        
  �� �� ֵ�� u16 
=============================================================================*/
u16 SetAudSubPlay(BOOL32 bPlay);

/*=============================================================================
  �� �� ���� SetAudNoisePlay
  ��    �ܣ� ������Ƶ���������ز��ţ����ڲ��Բɼ��Ͳ��ŵ�һ����
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� BOOL32 bPlay     
             u32 dwAudPort
  �� �� ֵ�� u16 
=============================================================================*/
u16 SetAudNoisePlay(BOOL32 bPlay, u32 dwAudPort);

//�趨��ǰ*.bin,*.out·����Ĭ��/usr/bin
void SetCodecAppDir(s8* szPath);
//ע��OSP����
void RegsterCommands();

//��ʼ��DSPоƬ
u16 HardCodecInitDSP(TDSPInit* pInit);
u16 HardCodecDestroyDSP(u32 dwDSPID);
//��ʼ��FPGA
u16 HardCodecDevInit(u32 nDecDevNum, u32 nEncDevNum);
u16 HardCodecDestroy();
u16 HardEnvInitial(u32 dwHWtype);

s32    ScaleVideoCap(u32 dwVidSrcPort,u8 byType, u8 byValue); /* ��Ƶ�ɼ����� */

/*=============================================================================
  �� �� ���� GetVGAPhaseClock
  ��    �ܣ� ��ȡVGAԴ��λʱ�Ӻͷֱ���
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� u32 dwVGAPort
             TVidSrcInfo* ptVGAInfo
             u32& dwPhaseValue
  �� �� ֵ�� u16 
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2010/6/17     1.0	        ��ѩ��                   ����
=============================================================================*/
u16 GetVGAPhaseClock(u32 dwVGAPort, TVidSrcInfo* ptVGAInfo, u32& dwPhaseValue);
/*=============================================================================
  �� �� ���� SetVGAPhaseClock
  ��    �ܣ� ����VGAԴ��λʱ��
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� u32 dwVGAPort
             u32 dwPhaseValue
  �� �� ֵ�� u16 
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2010/6/17     1.0	        ��ѩ��                   ����
=============================================================================*/
u16 SetVGAPhaseClock(u32 dwVGAPort, u32 dwPhaseValue);
/*=============================================================================
  �� �� ���� GetVGAFiltStatus
  ��    �ܣ� ��ȡVGAԴ�˲�״̬
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� u32 dwVGAPort
             TVidSrcInfo* ptVGAInfo
             u32& dwFiltSet
  �� �� ֵ�� u16 
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2010/6/17     1.0	        ��ѩ��                   ����
=============================================================================*/
u16 GetVGAFiltStatus(u32 dwVGAPort, TVidSrcInfo* ptVGAInfo, u32& dwFiltSet);
/*=============================================================================
  �� �� ���� SetVGAFiltStatus
  ��    �ܣ� ����VGAԴ�˲�
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� u32 dwVGAPort
             u32 dwFiltSet
  �� �� ֵ�� u16 
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2010/6/17     1.0	        ��ѩ��                   ����
=============================================================================*/
u16 SetVGAFiltStatus(u32 dwVGAPort, u32 dwFiltSet);


/*=============================================================================
  �� �� ���� GetVidPortInfo
  ��    �ܣ� ��ȡ��ƵԴ�˿ں���ʽ
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� u32 dwVidPortType:��ѯ�ӿڣ���VIDIO_DVI0��
             TVidPortInfo* ptVidPortInfo:����ʵ�ʶ˿ں���ʽ
  �� �� ֵ�� void 
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2011/4/27     1.0	        ��ѩ��                   ����
=============================================================================*/
void GetVidPortInfo(u32 dwVidPortType, TVidPortInfo* ptVidPortInfo);

/*�������� SetMicVol
��    �ܣ� ��ũ��˷����棬��Χ0-50
��    ���� u32 dwAudPort
           s32 nVol
�� �� ֵ�� API void 
˵    ���� */
API void SetMicVol(u32 dwAudPort, s32 nVol);

API s32 GetMicVol();

//����h600����ͷ��ʽ
API void SetVidInPortStd(TVidSrcInfo* ptCamInfo);

//��ȡ���DVI�ӿ���ʵ�ʵ�����ӿ�����
void GetVidOutPortType(u32 dwDVIId, u32 &dwRealPortType);
//��ȡ����ӿ��ϵ���ʽ
void GetVidInPortStd(u32 dwCapPort, TVidSrcInfo& tCamStdInfo);

/*�������� SetCanonPowerOn
��    �ܣ� ��ũ��˷�����ӿ�48v���翪�ؽӿ�ʵ��
��    ���� BOOL32 bEnable=TRUE
�� �� ֵ�� 
˵    ���� */
void SetCanonPowerOn(u32 dwAudPort, BOOL32 bEnable=TRUE);

//��ȡ���������״̬
API BOOL32 GetDigitalMicStatus(u32 dwAudPort);

//��ȡ3.5�ڲ���״̬  bIsAudIn = TRUE:�ɼ���  FALSE:���ſ�
API BOOL32 Get35InOrOutStatus(BOOL32 bIsAudIn);

API BOOL32 GetTRS635Status(u32 dwAudPort);

//��ȡHDMI��Ƶ��״̬
API BOOL32 GetAudHdmiStatus(u32 dwAudPort);

/*��ȡSDI�ӿ����� SDITYPE_ININ SDITYPE_INOUT*/
API u32 GetHDMtSDIIntType();

/*���ò��ŷֱ��ʸı���Ϣ֪ͨ*/
API void SetNtscPalChangeCallBack(CHANGECALLBACK pChangeProc);

//����оƬ����֪ͨ�ص�
API void SetCpuResetNotify(CpuResetNotify fNotify);
//����ƵԴ��������ʱ����ʱ����ͼ��:EN_PLAY_LAST/EN_PLAY_BLUE
u16    SetVidPlayPolicy(u32 dwTimeout = 5, u32 dwPlayType = EN_PLAY_LAST);

//�Ƿ�����ȫ��OSD
API void UseFullOSD(BOOL32 bFullOsd = TRUE);
//HDMI�����HDMI��DVI�ź�ѡ��
API void HDMIDVISwitch(BOOL32 bHDMI = TRUE);
//����SD�ź������ʽ
API void SetSDOutType(u32 dwOutType = VID_OUTTYPE_ORIGIN);	   //�����μ�codecwrapperdef_hd
//����������豸
API void RebootCodecDev(u32 dwDevID = CODECDEV_VIDENC);	   //�����μ�codecwrapperdef_hd
//�ж�2��D���֮ǰ�汾
API void SetHardWareVer(BOOL32 bBefore2ndD = FALSE);

//׷��kdvlog����ص��ӿ�
API void SetKdvLogOutputCallBack(KdvLogOutput fLogoutput);
s32 HardMPUInit(u32 dwHWType_Mode); //ָ�������������Լ�����ģʽ:codecwrapperdef_hd:enBoardType
s32 HardMPUInitDev(u32 nEncTos, u32 nDecTos, u32 nDspNum);
s32 HardMPUDestroy();
//�����ն˳�ʼ��
s32 HardMTInit(u32 nMode);
s32 HardMTDestroy();
//�ر���ָ���Ƶ��ʾ
void SetVideoShow(BOOL32 bShow);
//���ý���ȼ� �μ� codecwrapperdef_hd.h�� NF_MODE_DISABLE etc�����Ե�һ·��Ч
void SetNfMode(u32 dwMode);
//���ý��뿪�� �Ƽ�ʹ�� TRUE
void SetNfEnable(BOOL32 bOpen);
//�����Ƿ����õڶ�·����ǰ����
void SetAuxEncScaleEnable(BOOL32 bEnable);
#endif

#endif  //2013-3-21
