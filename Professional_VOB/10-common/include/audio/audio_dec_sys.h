/*****************************************************************************
ģ   ��   ��: ��Ƶ��davinci��װ
��   ��   ��: audio_dec_sys.h
�� ��  �� ��: 
�ļ�ʵ�ֹ���: ������ؽṹ�����Ͷ���
��        ��: V1.0  Copyright(C) 2006-2008 KDC, All rights reserved.
-----------------------------------------------------------------------------
�� �� �� ¼:
��       ��      �汾        �޸���      �޸�����
 2007/01/23      1.0         ��  ��      ��    ��
******************************************************************************/
#ifndef AUDIO_DEC_SYS_H
#define AUDIO_DEC_SYS_H
#include "audio_com_sys.h"
#ifdef __cplusplus
extern "C" {
#endif
	
/***************************************************/
/*             ������ؽṹ������                  */
/***************************************************/
//��������ṹ
typedef struct tagAUDIODEC_KDC_Params
{
	IAUDDEC_Params tAudDecParams;      // MUST be first field of all XDAS algs 
	TEnumAdCodecMode tAudioMode;       //��ƵCODECģʽ
	TAudCodecSubType tAudCodecSubType; //��Ƶģʽ��������   2007-7-24 xc add
	
	XDAS_Int32 l32FrameSize;           //ÿ֡���������ߴ�(��λ:�ֽ�)
	TEnumAdSrateMode tSamRate;         //���PCM���ݲ�����ģʽ
	TEnumAdBitWthMode tBitWidth;       //���PCMλ��ģʽ
	XDAS_Int32 l32ChannelNum;          //����ģʽ
  XDAS_Int32 l32BitRate;             //�����������  2008-08-14 lzy add
	XDAS_Int32 l32AecFlag;             //AECʹ�� = 1 ���� = 0;(1:�еڶ���buf����process)

}TAUDIODEC_KDC_Params;

//������������ṹ
typedef struct tagAUDIODEC_KDC_InArgs 
{
	IAUDDEC_InArgs tAudDecInArgs;      // MUST be first field of all XDAS algs 

	XDAS_Int32 l32VolIdx;              //��������������

	XDAS_Int32 l32Mp3HuffDecFlag;      //������mp3
	/*
	  ����mp3huffman����,l32Mp3HuffDecFlag = 1����Ϊ0
	  ע��: ÿ����������ߴ�Ϊ(2304 * 4 = 9216)
	*/
	XDAS_Int32 l32AvgPowOutFlag;	   //ƽ�����������־(1:��Ҫ���; 0:����Ҫ���) 

} TAUDIODEC_KDC_InArgs;


//���붯̬�����ṹ
typedef struct tagAUDIODEC_KDC_DynamicParams 
{
	IAUDDEC_DynamicParams  tAudDecDynamicParams;      //MUST be first field of all XDAS algs 
	XDAS_UInt32             u32VerBuf;                //the buffer first_address of  the  version string 
	XDAS_Int32              l32InAudStrLen;           //the biggest length  of  the version string 
	
} TAUDIODEC_KDC_DynamicParams;

//����״̬�����ṹ
typedef struct tagAUDIODEC_KDC_Status 
{
	IAUDDEC_Status    tAudDecStatus;                 // MUST be first field of all XDAS algs              
	XDAS_Int32        l32ErrorCode;                  //������
	XDAS_Int32        l32OutAudStrLen;               //  length  of the version string in fact

	//2007-07-30 xc add
	/*
	*/
	TEnumAdCodecMode tAudioMode;       //��ƵCODECģʽ
	TAudCodecSubType tAudCodecSubType; //��Ƶģʽ��������   2007-7-24 xc add
	
	XDAS_Int32 l32FrameSize;           //ÿ֡���������ߴ�(��λ:�ֽ�)
	TEnumAdSrateMode tSamRate;         //���PCM���ݲ�����ģʽ
	TEnumAdBitWthMode tBitWidth;       //���PCMλ��ģʽ
	XDAS_Int32 l32ChannelNum;          //����ģʽ
	XDAS_Int32 l32AecFlag;             //AECʹ�� = 1 ���� = 0;(1:�еڶ���buf����process)

} TAUDIODEC_KDC_Status;

//������������ṹ
typedef struct tagAUDIODEC_KDC_OutArgs 
{
	IAUDDEC_OutArgs tAudDecOutArgs;                  //MUST be first field of all XDAS algs 

	XDAS_Int32 l32OutSize;                           //���������С 
	XDAS_Int32 l32AvgPow;	                         //ƽ������

	XDAS_Int32 l32StatCycles;                        //2007-07-27 xc add

} TAUDIODEC_KDC_OutArgs;

/***************************************************/
/*             ��Ƶ����Control ID�Ŷ���              */
/***************************************************/
enum XDM_AudioDecId
{
	GETDECVERSION,                     /*�õ�����汾��*/
	GETDEC_STATUS                     //2007-07-26 xc add
};
#ifdef __cplusplus
}
#endif

#endif





