/*****************************************************************************
ģ   ��   ��: aud_proc
��   ��   ��: audio_proc_xdm6437.h
�� ��  �� ��: audio_process.h, audio_def.h
�ļ�ʵ�ֹ���: ��Ƶ������
��        ��: V1.0  Copyright(C) 2005-2007 KDC, All rights reserved.
-----------------------------------------------------------------------------
�� �� �� ¼:
��       ��      �汾        �޸���      �޸�����
 2007/09/24      1.0         ��  ��      ��    ��
******************************************************************************/
#ifndef AUDIO_PROC_XDM6437_H
#define AUDIO_PROC_XDM6437_H
#ifdef __cplusplus
extern "C" {
#endif   /* __cplusplus */

/***************************************************/
/*             ��Ƶ����Control ID�Ŷ���            */
/***************************************************/
enum XDM_AudioProId
{
	GETPRO_VERSION = 0,                 //�õ���Ƶ����汾��
	GETPRO_STATUS,                      //�õ���Ƶ����״̬             
}; 


/***************************************************/
/*             ��Ƶ�任��ؽṹ������              */
/***************************************************/
//��Ƶ�任�����ṹ
typedef struct tagAUDIOPROC_KDC_Params
{
	IAUDENC_Params tAudProcParams;			//MUST be first field of all XDAS algs
	XDAS_UInt32 u32AudProcParamAddr;
} TAUDIOPROC_KDC_Params;

//��Ƶ�任��������ṹ
typedef struct tagAUDIOPROC_KDC_InArgs 
{
	IAUDENC_InArgs tAudEncInArgs;			//MUST be first field of all XDAS algs
	TAudProcInput  tAudProcInput;
} TAUDIOPROC_KDC_InArgs;

//��Ƶ�任��������ṹ
typedef struct tagAUDIOPROC_KDC_OutArgs 
{
	IAUDENC_OutArgs tAudEncOutArgs;			//MUST be first field of all XDAS algs 
  TAudProcOutput  tAudProcOutput;     //      
} TAUDIOPROC_KDC_OutArgs;

//��Ƶ�任״̬�����ṹ
typedef struct tagtAUDIOPROC_KDC_Status 
{
	IAUDENC_Status tAudEncStatus;			//MUST be first field of all XDAS algs
} TAUDIOPROC_KDC_Status;

//��Ƶ�任��̬�����ṹ
typedef struct tagAUDIOPROC_KDC_DynamicParams 
{
	IAUDENC_DynamicParams  tAudEncDynamicParams;      // MUST be first field of all XDAS algs 
	XDAS_UInt32 u32AudProcDynParamAddr;
	XDAS_UInt32 u32AudProcStatusParamAddr;
} TAUDIOPROC_KDC_DynamicParams;

#ifdef __cplusplus
}
#endif  /* __cplusplus */
#endif   //end of AUDIO_PROC_XDM6437_H 



