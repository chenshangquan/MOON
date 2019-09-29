/*****************************************************************************
ģ   ��   ��: ��Ƶ��davinci��װ
��   ��   ��: audio_enc_sys.h
�� ��  �� ��: 
�ļ�ʵ�ֹ���: ��������ؽṹ�����Ͷ���
��        ��: V1.0  Copyright(C) 2006-2008 KDC, All rights reserved.
-----------------------------------------------------------------------------
�� �� �� ¼:
��       ��      �汾        �޸���      �޸�����
 2007/01/23      1.0         ��  ��      ��    ��
******************************************************************************/
#ifndef AUDIO_ENC_SYS_H
#define AUDIO_ENC_SYS_H

#include "audio_com_sys.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************/
/*             ��Ƶ����Control ID�Ŷ���            */
/***************************************************/
enum XDM_AudioEncId{
    AECENC_RESET_BUF=0,                /*AEC ���渴λ*/
	AECENC_SET_TYPE ,                  /*AEC��������, �������渴λ��*/
	AUDPROCENC_RESET_BWCHSRC,          /*λ�����������������id*/
	AUDPROCENC_RESET_AVGPOW,           /*ƽ����ͳ�������id*/
	AUDPROCENC_RESET_SPHEXCIT,         /*�������������id*/
	GETENCVERSION,                     /*�õ�����汾��*/
	GETENC_STATUS                      //2007-07-26 xc add
}; 

//2007-8-13 xc add
#define  AUDPROCENC_BWCHSRC          AUDPROCENC_RESET_BWCHSRC
#define  AUDPROCENC_AVGPOW           AUDPROCENC_RESET_AVGPOW
#define  AUDPROCENC_SPHEXCIT         AUDPROCENC_RESET_SPHEXCIT

/***************************************************/
/*             ������ؽṹ������                  */
/***************************************************/
//��������ṹ
typedef struct tagAUDIOENC_KDC_Params 
{
	IAUDENC_Params tAudEncParams;      //MUST be first field of all XDAS algs
	TEnumAdCodecMode tAudioMode;       //��Ƶģʽ
	TAudCodecSubType tAudCodecSubType; //��Ƶģʽ��������   2007-7-16 xc add

	XDAS_Int32 l32FrameSize;           //ÿ֡����PCM���ݳߴ�(��λ:�ֽ�)
	TEnumAdSrateMode tSamRate;         //����PCM���ݲ�����ģʽ
	TEnumAdBitWthMode tBitWidth;       //����PCMλ��ģʽ
	XDAS_Int32 l32ChannelNum;          //��������ģʽ
  XDAS_Int32 l32BitRate;             //����������� 2008-08-14 lzy add
	//XDAS_Int32 ptExtendStruct;       //2007-07-26 xc add
} TAUDIOENC_KDC_Params;

//������������ṹ
typedef struct tagAUDIOENC_KDC_InArgs 
{
	IAUDENC_InArgs tAudEncInArgs;      //MUST be first field of all XDAS algs 

	XDAS_Int32 l32VolIdx;              //��������������
	XDAS_Int32 l32Mp3HuffEncFlag;      //������mp3
	/*
	  ����mp3huffman����,��l32Mp3HuffEncFlag = 1����Ϊ0
	  ע��: ÿ�����������ߴ�Ϊ(2304 * 4 = 9216)
	*/
	XDAS_Int32 l32AvgPowOutFlag;	   //ƽ�����������־(1:��Ҫ���; 0:����Ҫ���) 

} TAUDIOENC_KDC_InArgs;

//���붯̬�����ṹ
typedef struct tagAUDIOENC_KDC_DynamicParams 
{
	IAUDENC_DynamicParams  tAudEncDynamicParams;      // MUST be first field of all XDAS algs 
	XDAS_UInt32             u32VerBuf;                //  the buffer first_address of  the  version string 
	XDAS_Int32              l32InAudStrLen;           // the biggest length  of  the version string 

} TAUDIOENC_KDC_DynamicParams;

//����״̬�����ṹ
typedef struct tagAUDIOENC_KDC_Status 
{
	IAUDENC_Status    tAudEncStatus;                 // MUST be first field of all XDAS algs              
	XDAS_Int32        l32ErrorCode;                  // ������
	XDAS_Int32        l32OutAudStrLen;               // length  of the version string in fact
    
	//2007-07-30 xc add
	TEnumAdCodecMode tAudioMode;                     //��Ƶģʽ
	TAudCodecSubType tAudCodecSubType;               //��Ƶģʽ��������   2007-7-16 xc add

	XDAS_Int32 l32FrameSize;                         //ÿ֡����PCM���ݳߴ�(��λ:�ֽ�)
	TEnumAdSrateMode tSamRate;                       //����PCM���ݲ�����ģʽ
	TEnumAdBitWthMode tBitWidth;                     //����PCMλ��ģʽ
	XDAS_Int32 l32ChannelNum;                        //����ģʽ

} TAUDIOENC_KDC_Status;

//������������ṹ
typedef struct tagAUDIOENC_KDC_OutArgs 
{
	IAUDENC_OutArgs tAudEncOutArgs;                  //MUST be first field of all XDAS algs 

	XDAS_Int32 l32OutSize;                           //���������С 
	XDAS_Int32 l32AvgPow;	                         //ƽ������

	XDAS_Int32 l32StatCycles;                        //2007-07-27 xc add

} TAUDIOENC_KDC_OutArgs;

/***************************************************/
/*              ������ؽṹ������                 */
/***************************************************/
//���������ṹ
typedef struct tagAUDIOMIX_KDC_Params
{
	IAUDENC_Params tAudEncParams;      // MUST be first field of all XDAS algs
	XDAS_Int32 l32FrameSize;           //ÿ·ÿ֡�������ݳߴ�(��λ:�ֽ�)
} TAUDIOMIX_KDC_Params;

//������������ṹ
typedef struct tagAUDIOMIX_KDC_InArgs 
{
	IAUDENC_InArgs tAudEncInArgs;      //MUST be first field of all XDAS algs 

	TEnumAdMixMode eAudioMixMode;      //��Ƶ����ģʽ
	XDAS_Int32 l32MixChNum;            //����·��
	XDAS_Int16 as16Val[MAX_MIX_CH_NUM];//ÿ·��������

} TAUDIOMIX_KDC_InArgs;

/***************************************************/
/*             ��Ƶ�任��ؽṹ������              */
/***************************************************/
//��Ƶ�任�����ṹ
typedef struct tagAUDIOPROC_KDC_Params
{
	IAUDENC_Params tAudProcParams;     //MUST be first field of all XDAS algs

	//���ò���(����ID��Ҫ����)
	XDAS_UInt32  u32AudioProcFlag;     /*
									     ��Ƶ�任�����־, ȡ�����������ֵ:
										 AUDPROCENC_BWCHSRC  λ�����������ʴ����־
										 AUDPROCENC_AVGPOW   ƽ����ͳ�Ʊ�־
										 AUDPROCENC_SPHEXCIT �������������־
	                                   */
	XDAS_Int32 l32InFrameSize;         //����PCM���ݳߴ�(��λ:�ֽ�)

	//u32AudioProcFlagΪAUDPROCENC_BWCHSRCʱ�����õĲ���
	TEnumAdSrateMode tInSamRate;       //����PCM���ݲ�����ģʽ
	TEnumAdBitWthMode tInBitWidth;     //����PCMλ��ģʽ
	XDAS_Int32 l32InChannelNum;        //��������ģʽ
	
	TEnumAdSrateMode tOutSamRate ;     //���PCM���ݲ�����ģʽ
	TEnumAdBitWthMode tOutBitWidth;    //���PCMλ��ģʽ
	XDAS_Int32 l32OutChannelNum;       //�������ģʽ

} TAUDIOPROC_KDC_Params;

//��Ƶ�任��������ṹ
typedef struct tagAUDIOPROC_KDC_InArgs 
{
	IAUDENC_InArgs tAudEncInArgs;      //MUST be first field of all XDAS algs 

	XDAS_Int32 l32InVolIndex;          //������������(�������������32bitλ��,�������������������)
	XDAS_Int32 l32OutVolIndex;         //�����������
} TAUDIOPROC_KDC_InArgs;

//��Ƶ�任״̬�����ṹ
typedef struct tagtAUDIOPROC_KDC_Status 
{
	IAUDENC_Status tAudEncStatus;      //MUST be first field of all XDAS algs
	XDAS_Int32 l32ErrorCode;           //������
	 
	XDAS_UInt32 u32AudioProcFlag;      //��Ƶ�任�����־
	XDAS_Int32 l32InFrameSize;         //����PCM���ݳߴ�(��λ:�ֽ�)

	//���������������
	TEnumAdSrateMode tInSamRate;       //����PCM���ݲ�����ģʽ
	TEnumAdBitWthMode tInBitWidth;     //����PCMλ��ģʽ
	XDAS_Int32 l32InChannelNum;        //��������ģʽ
	
	TEnumAdSrateMode tOutSamRate;      //���PCM���ݲ�����ģʽ
	TEnumAdBitWthMode tOutBitWidth;    //���PCMλ��ģʽ
	XDAS_Int32 l32OutChannelNum;       //�������ģʽ

} TAUDIOPROC_KDC_Status;

//��Ƶ�任��̬�����ṹ
typedef struct tagAUDIOPROC_KDC_DynamicParams 
{
	IAUDENC_DynamicParams  tAudEncDynamicParams;      // MUST be first field of all XDAS algs 
	//���ò���(����ID��Ҫ����)
	XDAS_UInt32  u32AudioProcFlag;     /*
									     ��Ƶ�任�����־, ȡ�����������ֵ:
										 AUDPROCENC_BWCHSRC  λ�����������ʴ����־
										 AUDPROCENC_AVGPOW   ƽ����ͳ�Ʊ�־
										 AUDPROCENC_SPHEXCIT �������������־
	                                   */
	XDAS_Int32 l32InFrameSize;         //����PCM���ݳߴ�(��λ:�ֽ�)

	//IDΪAUDPROCENC_RESET_BWCHSRCʱ�����õĲ���
	TEnumAdSrateMode tInSamRate;       //����PCM���ݲ�����ģʽ
	TEnumAdBitWthMode tInBitWidth;     //����PCMλ��ģʽ
	XDAS_Int32 l32InChannelNum;        //��������ģʽ
	
	TEnumAdSrateMode tOutSamRate ;     //���PCM���ݲ�����ģʽ
	TEnumAdBitWthMode tOutBitWidth;    //���PCMλ��ģʽ
	XDAS_Int32 l32OutChannelNum;       //�������ģʽ

} TAUDIOPROC_KDC_DynamicParams;

//��Ƶ�任��������ṹ
typedef struct tagAUDIOPROC_KDC_OutArgs 
{
	IAUDENC_OutArgs tAudEncOutArgs;    //MUST be first field of all XDAS algs 

	XDAS_Int32 l32OutSize;             //���������С 
	XDAS_Int32 l32AvgPow;	           //ƽ������
	XDAS_Int32 l32ExciteLev;           //�������� 
	XDAS_Int32 l32StatCycles;          //2007-08-13 xc add

} TAUDIOPROC_KDC_OutArgs;

/***************************************************/
/*             ����������ؽṹ������              */
/***************************************************/
//AEC�����ṹ
typedef struct tagAUDIOAEC_KDC_Params
{
	IAUDENC_Params tAudAecParams;      // MUST be first field of all XDAS algs
	
	//�Ƿ���Ҫ,��Ҫʱֻ���ڽ��˲��ź���?
	XDAS_Int32 l32VolIdx;              //������������

	//AEC����ʱ���������
	XDAS_Int32 l32AecType;             //eg. AEC_NEW_TYPE_MP3, AEC_NEW_TYPE_G711 etc

	//����ο��ź�����
	XDAS_Int32 l32RefInFrameSize;      //�ο��ź�����PCM���ݳߴ�(��λ:�ֽ�)
	TEnumAdSrateMode tRefInSamRate;    //�ο��ź�����PCM���ݲ�����ģʽ
	TEnumAdBitWthMode tRefInBitWidth;  //�ο��ź�����PCMλ��ģʽ
	XDAS_Int32 l32RefInChannelNum;     //�ο��ź�����ģʽ
	
	//��������ź�����
	XDAS_Int32 l32NearInFrameSize;     //�����ź�����PCM���ݳߴ�(��λ:�ֽ�)
	TEnumAdSrateMode tNearInSamRate;   //�����ź�����PCM���ݲ�����ģʽ
	TEnumAdBitWthMode tNearInBitWidth; //�����ź�����PCMλ��ģʽ
	XDAS_Int32 l32NearInChannelNum;    //�����ź�����ģʽ

}TAUDIOAEC_KDC_Params;

//AEC��������ṹ
typedef struct tagAUDIOAEC_KDC_InArgs 
{
	IAUDENC_InArgs tAudEncInArgs;      //MUST be first field of all XDAS algs 

	TEnumAdAecMode  tAdAecMode;        //��ƵAECģʽ
	XDAS_Int32 l32CapSamples;          //�Ѳɼ�δ�����������
	XDAS_Int32 l32PlySamples;          //δ���ŵ�������
	XDAS_Int32 l32UseFlag;             //aec_spe_agc_16kʹ��
	                                   //bit2=1��ʾaec��ʹ�ã�bit1=1��ʾspe��ʹ�ã�bit0=1��ʾagc��ʹ��
} TAUDIOAEC_KDC_InArgs;

typedef struct tagAUDIOAEC_KDC_DynamicParams 
{
	IAUDENC_DynamicParams  tAudEncDynamicParams;      // MUST be first field of all XDAS algs 
	/*
	Control ID = AECENC_RESET_BUFʱ,��Ҫ���õĲ���:
	��
	*/
	//Control ID = AECENC_SET_TYPE,��Ҫ���õĲ���:
	XDAS_Int32 l32AecType;             //eg. AEC_NEW_TYPE_MP3, AEC_NEW_TYPE_G711 etc

	//����ο��ź�����
	XDAS_Int32 l32RefInFrameSize;      //�ο��ź�����PCM���ݳߴ�(��λ:�ֽ�)
	TEnumAdSrateMode tRefInSamRate;    //�ο��ź�����PCM���ݲ�����ģʽ
	TEnumAdBitWthMode tRefInBitWidth;  //�ο��ź�����PCMλ��ģʽ
	XDAS_Int32 l32RefInChannelNum;     //�ο��ź�����ģʽ
	
	//��������ź�����
	XDAS_Int32 l32NearInFrameSize;     //�����ź�����PCM���ݳߴ�(��λ:�ֽ�)
	TEnumAdSrateMode tNearInSamRate;   //�����ź�����PCM���ݲ�����ģʽ
	TEnumAdBitWthMode tNearInBitWidth; //�����ź�����PCMλ��ģʽ
	XDAS_Int32 l32NearInChannelNum;    //�����ź�����ģʽ
	
	XDAS_UInt32             u32VerBuf;                //  the buffer first_address of  the  version string 
	XDAS_Int32              l32InAudStrLen;               // the biggest length  of  the version string 

} TAUDIOAEC_KDC_DynamicParams;

/***************************************************/
/*             DTMF��ؽṹ������                  */
/***************************************************/
//DTMF��������ṹ
typedef struct tagDTMFENC_KDC_InArgs 
{
	IAUDENC_InArgs tAudEncInArgs;      //MUST be first field of all XDAS algs 

    XDAS_Int32 l32DTMFSampleLen;	   //DTMF������ʱ��,8K�����ĵ���, ����480(��60msʱ��)
    XDAS_Int32 l32DTMFZeroLen;		   //DTMF�����ʱ��,8K�����ĵ���, ����480(��60msʱ��)
	XDAS_UInt16 u16DTMFNum;            //��Ҫ����DTMF����ĺ���λ��
	
} TDTMFENC_KDC_InArgs;


/***************************************************/
/*             SPLIT��ؽṹ������                 */
/***************************************************/
typedef struct tagAUDIOSPLIT_KDC_InArgs 
{
	IAUDENC_InArgs tAudEncInArgs;      //MUST be first field of all XDAS algs 

	XDAS_Int32 l32InSize;              //���������Ĵ�С,���ֽ�Ϊ��λ,����Ϊ8�ı���
	
} TAUDIOSPLIT_KDC_InArgs;


#ifdef __cplusplus
}
#endif

#endif




