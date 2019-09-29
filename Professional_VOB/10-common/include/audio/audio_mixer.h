/*****************************************************************************
ģ   ��   ��: ������
��   ��   ��: mixer16.c, mixer32.c
�� ��  �� ��: 
�ļ�ʵ�ֹ���: ����������ӿ�����
��        ��: V1.0  Copyright(C) 2005-2009 KDC, All rights reserved.
-----------------------------------------------------------------------------
�� �� �� ¼:
��       ��      �汾        �޸���      �޸�����
2003/06/10       1.0         �Ѵ���      ��    ��
2006/12/20       1.1         ��  ��      ������32λ�����ӿ�
******************************************************************************/
#ifndef MIXER_V100_H
#define MIXER_V100_H

#ifdef __cplusplus
extern "C" {
#endif   /* __cplusplus */

#include "audio_define.h"

enum mixer_errcode
{
	ERR_AUDMIX_START = ERR_MIXER,

	ERR_AUDMIX_MODE,              //����ģʽ����

	ERR_AUDMIX_MEM_INIT,          //�ڴ�����ʼ��ʧ��
	ERR_AUDMIX_INIT_PARA_NULL,    //��ʼ�������������ָ��Ϊ��
	ERR_AUDMIX_SLOWMEM_NULL,      //�ڴ�Ϊ�ջ���

	ERR_AUDMIX_VER_BUF_SMALL,     //�汾buf̫С
	ERR_AUDMIX_STATUS_NULL,       //��ȡ״̬�����������ָ��Ϊ��

	ERR_AUDMIX_PROC_PARM_NULL,    //�����������������ָ��Ϊ��
	ERR_AUDMIX16_SAMPLE_CNT,      //16λ������������������������
	ERR_AUDMIX32_SAMPLE_CNT,      //32λ������������������������

	ERR_AUDMIX_CLOSE              //����ر�ʧ��
};

//һ·�����ṹ�嶨��
typedef struct
{
    u8 *pu8ChanBuf;               //һ·��������ָ��mPCMValue
    u32 u32Volume;                //��Ӧ������(0~255,�������ϯ����ԷŴ�һЩ)nVolume
}TAudMixBuf;

//������ʼ�������ṹ��
typedef struct
{
    u32 u32Reserved;              //��������
}TAudMixParam;

#define TAudMixStatusParam TAudMixParam

//��������ṹ��
typedef struct
{
	TEnumAudMixMode tAudMixMode;
	                              //����ģʽ
	TAudMixBuf **pptInAudBuf;     //ָ�����������ṹ��ָ������
	u32 u32InChList;              //��������ͨ���б� 
    TAudMixBuf **pptOutAudBuf;    //ָ�������N-1ģʽ����ṹ��ָ������
    TAudMixBuf *ptOutNAudBuf;     //Nģʽ����ṹ��ָ��
    u32 u32InSampleCnt;           //ÿ·����������
    u32 u32Reserved;              //��������
}TAudMixInput;

//��������ṹ��
typedef struct
{       
    u32  u32StatisCycles;         //����һ֡Ч��ͳ��
    u32  u32Reserved;             //��������
}TAudMixOutput;

/*===============================================================
��   ��   ��: AudMixOpen
��        ��: ��������ʼ��
����ȫ�ֱ���: 
�������˵��: ��
              ppvHandle            ָ����������ָ���ָ��[out]
			  ptAudMixParam        ��ʼ�������ṹָ��[in]
			  pvAudMemParam        �ڴ����ṹ���ָ��[in]
���� ֵ ˵��: 
              �ɹ�: AUDIO_SUCCESS
              ʧ��: ������
�� ��  ˵ ��: ��
=================================================================*/
l32 AudMixOpen(void **ppvHandle,
			   TAudMixParam *ptAudMixParam,
			   void *pvAudMemParam);

/*====================================================================
��   ��   ��: AudMixProcess
��        ��: ʵ�ֻ����㷨
����ȫ�ֱ���: ��
�������˵��: 
			 pvHandle            ָ����������ָ��[in]
			 ptAudMixInput       ָ���������ṹ��ָ��[in/out]
			 ptAudMixOutput      ָ���������ṹ��[out]
���� ֵ ˵��: 
              �ɹ�-AUDIO_SUCCESS, ʧ��-������
�� ��  ˵ ��: ��
======================================================================*/
l32 AudMixProcess(void *pvHandle,
				  TAudMixInput *ptAudMixInput,
				  TAudMixOutput *ptAudMixOutput);

/*===============================================================
��   ��   ��: AudMixClose
��        ��: �������ر�
����ȫ�ֱ���: 
�������˵��: ��
              pvHandle             ָ������������ָ��[in]
���� ֵ ˵��: 
              �ɹ�: AUDIO_SUCCESS
              ʧ��: ������
�� ��  ˵ ��: ��
=================================================================*/
l32 AudMixClose(void *pvHandle);

/*===============================================================
��   ��   ��: AudMixGetStatus
��        ��: ��ȡ������״̬��Ϣ
����ȫ�ֱ���: 
�������˵��: ��
              pvHandle             ָ������������ָ��[in]
			  ptAudMixStatusParam  ָ�����״̬�����ṹ��ָ��[out]
���� ֵ ˵��: 
              �ɹ�: AUDIO_SUCCESS
              ʧ��: ������
�� ��  ˵ ��: ��
=================================================================*/
l32 AudMixGetStatus(void *pvHandle, 
					TAudMixStatusParam *ptAudMixStatusParam);

/*===============================================================
��   ��   ��: AudMixGetVersion
��        ��: ȡ����Ƶ������ģ��汾��
����ȫ�ֱ���: ��
�������˵��: ��
              pvVer      ��ȡ�汾�����뻺��[in]
			  l32BufLen  ���뻺���С[out]
			  pl32VerLen �汾���ַ�����С[in]
���� ֵ ˵��: 
			  �ɹ�: AUDIO_SUCCESS
			  ʧ��: ������
�� ��  ˵ ��: ��
=================================================================*/
l32 AudMixGetVersion(void *pvVer, l32 l32BufLen, l32 *pl32VerLen);

#ifdef __cplusplus
}
#endif  /* __cplusplus */
#endif// end of MIXER_V100_H

