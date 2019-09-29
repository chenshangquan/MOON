/*****************************************************************************
ģ   ��   ��: aud_aec
��   ��   ��: audio_aec_xdm6437.h
�� ��  �� ��: audio_def.h
�ļ�ʵ�ֹ���: ������������
��        ��: V1.0  Copyright(C) 2005-2007 KDC, All rights reserved.
-----------------------------------------------------------------------------
�� �� �� ¼:
��       ��      �汾        �޸���      �޸�����
 2007/09/24      1.0         ��  ��      ��    ��
******************************************************************************/
#ifndef AUDIO_AEC_XDM6437_H
#define AUDIO_AEC_XDM6437_H
#ifdef __cplusplus
extern "C" {
#endif   /* __cplusplus */ 

#define AEC8K
//#define AEC16K
//#define AEC32K

//AEC����ģʽ
typedef enum
{
	AEC_SETREF_MODE=0,                 //�ο��ź�����ģʽ
	AEC_PROC_MODE                      //��������ģʽ
}TEnumAdAecMode;

/***************************************************/
/*             ��Ƶaec Control ID�Ŷ���            */
/***************************************************/
enum XDM_AudioAecId
{
	GETAEC_VERSION = 0,                 //�õ�aec�汾��
	GETAEC_STATUS,                      //�õ�aec״̬��Ϣ
	RESET_AEC                           //����aec                  
}; 

/***************************************************/
/*             ����������ؽṹ������              */
/***************************************************/
//�������������ṹ
typedef struct tagAUDIOAEC_KDC_Params
{
	IAUDENC_Params tAudAecParams;			//MUST be first field of all XDAS algs
	XDAS_UInt32 u32AudAecParamAddr;   //AEC��ʼ�������ṹ���׵�ַ(TAecParam)
} TAUDIOAEC_KDC_Params;


//����������������ṹ
typedef struct tagAUDIOAEC_KDC_InArgs 
{
	IAUDENC_InArgs tAudEncInArgs;			//MUST be first field of all XDAS algs
	TAecPlayInput tAecPlayInput;      //Aec���Ŷ��������ݽṹ��
	TAecCapInput tAecCapInput;        //Aec�ɼ����������ݽṹ��
	TEnumAdAecMode tAdAecMode;        //��ƵAECģʽ
} TAUDIOAEC_KDC_InArgs;

//����������������ṹ
typedef struct tagAUDIOAEC_KDC_OutArgs 
{
	IAUDENC_OutArgs tAudEncOutArgs;			//MUST be first field of all XDAS algs    
} TAUDIOAEC_KDC_OutArgs;

//��������״̬�����ṹ
typedef struct tagtAUDIOAEC_KDC_Status 
{
	IAUDENC_Status tAudEncStatus;			//MUST be first field of all XDAS algs
} TAUDIOAEC_KDC_Status;

//����������̬�����ṹ
typedef struct tagAUDIOAEC_KDC_DynamicParams 
{
	IAUDENC_DynamicParams  tAudEncDynamicParams;      // MUST be first field of all XDAS algs 
	XDAS_UInt32 u32AudAecDynParamAddr;                /* GETENC_VERSIONʱΪTAudVerInfoInput�ṹ���׵�ַ��
	                                                     RESET_AECʱΪTAecParam�ṹ���׵�ַ���������Ϊ��*/
	XDAS_UInt32 u32AudAecStatusParamAddr;             /* GETENC_VERSIONʱΪTAecStatusParam�ṹ���׵�ַ��
	                                                     GETENC_STATUSʱΪTAudVerInfoOutput�ṹ���׵�ַ,�������Ϊ��*/
} TAUDIOAEC_KDC_DynamicParams;

#ifdef __cplusplus
}
#endif  /* __cplusplus */
#endif   //end of AUDIO_AEC_XDM6437_H 



