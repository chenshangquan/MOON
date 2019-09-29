/*****************************************************************************
ģ   ��   ��: aud_proc
��   ��   ��: audio_process.h
�� ��  �� ��: aud_proc.c, aud_proc_private.h
�ļ�ʵ�ֹ���: ��Ƶ������
��        ��: V1.0  Copyright(C) 2005-2007 KDC, All rights reserved.
-----------------------------------------------------------------------------
�� �� �� ¼:
��       ��      �汾        �޸���      �޸�����
2007/09/24       1.0         ��  ��      ��    ��
2009/03/26       1.1         ½־��      ����ƽ������ͳ�ƺ�������������
2009/04/20       1.2         ½־��      ���������ṹ������ƽ������ͳ�Ƴ�Ա����
2009/11/16       1.3         ½־��      ������Ƶ����������ú�������
******************************************************************************/
#ifndef AUDIO_PROCESS_H
#define AUDIO_PROCESS_H
#ifdef __cplusplus
extern "C" {
#endif   /* __cplusplus */

#include "audio_define.h"

enum
{
	ERR_AUDPROC_START = ERR_AUDPROCESS_MOD, 
	/*��ʼ��ʱ�Ĵ�����*/
	ERR_AUDPROC_PARAM_POINTER_NULL,         //��ʼ�������������ָ��Ϊ��
	ERR_AUDPROC_MEM_INIT,                   //�ڴ�����ʼ��ʧ��
	ERR_AUDPROC_SLOWMEM_LACK,               //�ڴ治��
	ERR_AUDPROC_TAP_TIME,                   //ʱ������
	
	ERR_AUDPROC_IN_BIT_WIDTH,               //��������λ�����
	ERR_AUDPROC_IN_CHANNEL,                 //������������������
	ERR_AUDPROC_IN_SAMPLE_RATE,             //�������������ʴ���
	
	ERR_AUDPROC_OUT_BIT_WIDTH,              //�������λ�����
	ERR_AUDPROC_OUT_CHANNEL,                //�����������������
	ERR_AUDPROC_OUT_SAMPLE_RATE,            //������������ʴ���
	
	ERR_AUDPROC_NO_SURPORT_INIT,            //��ʼ���в�֧�ֵı任
	ERR_AUDPROC_NO_SURPORT_PROC,            //�����в�֧�ֵı任
	ERR_AUDPROC_NO_MODE,                    //��֧�ֵ���Ƶ����ģʽ
	
	/*����ʱ�Ĵ�����*/
	ERR_AUDPROC_PROC_PARA_NULL,             //�������������ָ��Ϊ��
	ERR_AUDPROC_PROC_INOUT_BUF_NULL,        //�������������BUFָ��Ϊ��
	ERR_AUDPROC_NO_PROCESS,                 //��֧�ֵ���Ƶ����
	ERR_AUDPROC_STATUS_NULL,                //��ȡ״̬�����������ָ��Ϊ��
	
	ERR_AUDPROC_VER_BUF_SMALL,              //�汾buf̫С
	ERR_AUDPROC_CLOSE,                      //����ر�ʧ��
	
	//v200����ӵĴ�����
	ERR_AUDPROC_BIT_WIDTH,                 //pcm�ź�λ�����
	ERR_AUDPROC_CHANNEL,                   //pcm�ź�����������
	ERR_AUDPROC_INIT_HANDLE_NULL,           //��ʼ�������������ָ��Ϊ��
	ERR_AUDPROC_SLOWMEM,                   //Ƭ���ڴ����ʧ��
	ERR_AUDPROC_BITWIDTH_CHAN_ATTRIB,       //��֧�ֵ�����32bit����������,��֧��32bit��32bit�ı任	
	ERR_AUDPROC_BITWIDTH_CHAN_MODE,         //λ������ģʽ����
	ERR_AUDPROC_INIT_CLOSE,                //�����ʱ任��ʼ������ʱ�ͷ���Ƶ���������ڴ�ռ����
	ERR_AUDPROC_PROC_HANDLE_NULL,           //�������������ָ��Ϊ��
	ERR_AUDPROC_CLOSE_RESMPLE,              //�ͷŲ����ʱ任ģ���ʧ��
	ERR_AUDPSPLIT_INPUTBUF_SMALL,           //һ·����·���������ڴ�ռ��С 
	ERR_AUDPSPLIT_INFRAMESIZE,              //����֡��С������8��������
	ERR_AUDPROC_AVG_POW_TAUDPOWERSTAT_NULL, //TAUDPOWERSTAT�ṹ��ָ��Ϊ��
	ERR_AUDPROC_AVG_POW_MODE_CHECK,         //ƽ����������ģʽ���ʧ��
    ERR_SPHEXICT_OPEN_FAIL,                 //����������ʧ��
	ERR_AUDPROC_SPH_EXCIT_TAUDSPHEXCIT_NULL,//TAUDSPHEXCIT�ṹ��ָ��Ϊ��
	ERR_AUDPROC_SPH_EXCIT_MODE_CHECK,       //������������ģʽ���ʧ��
	ERR_SPHEXICT_CLOSE_FAIL,                //���������ر�ʧ��

	//v201����ӵĴ�����
	ERR_AUDPROC_INVALID_VOLUME_INDEX,       //��Ч����������
    ERR_AUDPROC_INFRAMESIZE                 //pcm�ź�֡size�Ĵ���    
};

//��Ƶ����ģʽ
typedef enum
{
	AUDPROC_BW_CH_SRC,                      //����λ�������ʱ任
	AUDPROC_AVG_POW,                        //ƽ������ͳ��
	AUDPROC_SPH_EXCIT,                      //��������
	AUDPROC_SPIT1TO4                        //һ·�ɼ��źŷֳ���·�ź�
}TEnumAuddProcMode;                  

//��Ƶ�����ʼ����������ṹ
typedef struct tagAudProcParam
{
	u32 u32Size ;                            //��¼�ṹ��ռ��С
	//���ò���(����ID��Ҫ����)
	u32 u32AudioProcMode;                   //������Ƶ����ģʽ TEnumAuddProcMode
	                                        
	l32 l32InFrameSize;                     //����PCM���ݳߴ�(��λ:�ֽ�)

	//u32AudioProcModeΪAUDPROC_BWCHSRCʱ�����õĲ���
	TEnumAudSampleRate tInSamRate;          //����PCM���ݲ�����ģʽ
	TEnumAudBitWidth tInBitWidth;           //����PCMλ��ģʽ
	l32 l32InChannelNum;                    //��������ģʽ
	
	TEnumAudSampleRate tOutSamRate;         //���PCM���ݲ�����ģʽ
	TEnumAudBitWidth tOutBitWidth;          //���PCMλ��ģʽ
	l32 l32OutChannelNum;                   //�������ģʽ

	u32 u32Reserved;                        //��������
}TAudProcParam;

//��Ƶ����״̬�����ṹ
#define TAudProcStatusParam TAudProcParam

//��Ƶ����֡������������ṹ
typedef struct tagAudProcInput
{
	u32 u32Size ;                            //��¼�ṹ��ռ��С
	u8 *pu8InFrameBuf;	                  	//ָ��һ֡��������ָ��
	void *pvOutFrameBuf;	                  //ָ��һ֡������������ָ��
	u32 u32InBufSize;                        //���뻺��Ĵ�С
	u32 u32OutBufSize;                       //�������Ĵ�С
	l32 l32InVolIndex;                      //������������(�������������32bitλ��,�������������������)
	l32 l32OutVolIndex;                     //�����������
	u32 u32Reserved;                        //��������
}TAudProcInput;

//��Ƶ����֡������������ṹ
typedef struct tagAudProcOutput
{
	u32 u32Size;                         //��¼�ṹ��ռ��С
	u32 u32OutFrameSize;	             //һ֡��������ֽ���
	l32 l32StatisCycles;                 //Ч��ͳ�����
	u32 u32Reserved;                     //��������
}TAudProcOutput;

//��Ƶ����ͳ�ƽṹ��(�ýṹ��ָ��ͨ��TAudProcOutput�ṹ���u32Reserved��������)
typedef struct tagAudPowerStat
{
	u32 u32Size;                           //��¼�ṹ��ռ��С
	u32 u32AudioProcMode;                  //����ƽ������ͳ�ƴ���ģʽ(TEnumAuddProcMode);	         
	l32 l32AvgPower;                       //���һ֡ƽ������ͳ��
	u32 u32Reserved;                       //��������
}TAudPowerStat;

//��Ƶ���������ṹ��(�ýṹ��ָ��ͨ��TAudProcOutput�ṹ���u32Reserved��������)
typedef struct tagAudSphExcit
{
	u32 u32Size;                           //��¼�ṹ��ռ��С
	u32 u32AudioProcMode;                  //����������������ģʽ(TEnumAuddProcMode);	         
	l32 l32SphExcitFlag;                   //�����ǰ֡����������־(1��ʾ������0��ʾ������)
	u32 u32AvgPower;                       //�����ǰ֡ƽ������ͳ��
	u32 u32Reserved;                       //��������
}TAudSphExcit;

//��Ƶ�Զ�������ƽṹ��(�ýṹ��ָ��ͨ��TAudProcInput�ṹ���u32Reserved��������)
typedef struct tagAudAGC
{
	u32 u32Size;                           //��¼�ṹ��ռ��С
	u32 u32AgcEnable;                      //�Ƿ����AGC����(1��ʾ�ǣ�0��ʾ��);	         
	u32 u32Reserved;                       //��������
}TAudAgc;

/*===============================================================
��   ��   ��: AudProcOpen
��        ��: ��Ƶ�����
����ȫ�ֱ���: 
�������˵��: ��
              ppvAudProcHandle     ��Ƶ������ָ���ָ��[out] 
			  ptAudProcParam       ��ʼ�������ṹָ��[in] 
			  ptAudProcMemParam    �ڴ����ṹ���ָ��[in]
���� ֵ ˵��: 
              �ɹ�: AUDIO_SUCCESS
              ʧ��: ������
�� ��  ˵ ��: ��
=================================================================*/
l32 AudProcOpen(void **ppvHandle, TAudProcParam *ptAudProcParam, void *ptAudProcMemParam);
				
/*===============================================================
��   ��   ��: AudProcess
��        ��: һ֡��Ƶ����
����ȫ�ֱ���: ��
�������˵��: ��
              pvHandle             ��Ƶ������ָ���ָ��[in]
			  ptAudProcInput       ��������ṹָ��[in]
			  ptAudProcOutput      ��������ṹָ��[out]
���� ֵ ˵��: 
              �ɹ�: AUDIO_SUCCESS
              ʧ��: ������
�� ��  ˵ ��: ��
=================================================================*/
l32 AudProcess(void *pvHandle, TAudProcInput *ptAudProcInput,
			   TAudProcOutput *ptAudProcOutput);

/*===============================================================
��   ��   ��: AudProcGetStatus
��        ��: ��ȡ״̬
����ȫ�ֱ���: ��
�������˵��: ��
              pvHandle              ��Ƶ������ָ���ָ��[in]
              ptAudProcStatusParam  ��Ƶ����״̬��Ϣ�ṹ��ָ��[out]
���� ֵ ˵��: 
              �ɹ�: AUDIO_SUCCESS
              ʧ��: ������
�� ��  ˵ ��: ��
=================================================================*/
l32 AudProcGetStatus(void *pvHandle, TAudProcStatusParam *ptAudProcStatusParam);

/*===============================================================
��   ��   ��: AudProcGetVersion
��        ��: ȡ����Ƶ����ģ��汾��
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
l32 AudProcGetVersion (void *pvVer, l32 l32BufLen, l32 *pl32VerLen);

/*===============================================================
��   ��   ��: AudProcClose
��        ��: ��Ƶ����ر�
����ȫ�ֱ���: ��
�������˵��: ��
              pvHandle        ��Ƶ������ָ���ָ��[in/out] 
���� ֵ ˵��: 
              �ɹ�: AUDIO_SUCCESS
              ʧ��: ������
�� ��  ˵ ��: ��
=================================================================*/
l32 AudProcClose(void *pvHandle);

/*====================================================================                        
������      : AudProcSetParams                                                                 
����        : ���ý���������                                                                     
�㷨ʵ��    : ��                                                                              
����ȫ�ֱ���: ��                                                                              
����        : pvHandle:         ָ����Ƶ������ָ��[in]
              ptAudProcParam:   ��Ƶ�����ʼ�������ṹ��ָ��[in]                          
����ֵ˵��  : �ɹ�: AUDIO_SUCCESS, ʧ��: ���ش�����                                           
====================================================================*/                        
l32 AudProcSetParams(void *pvHandle, TAudProcParam *ptAudProcParam);

#ifdef __cplusplus
}
#endif  /* __cplusplus */
#endif   //end of AUDIO_PROCESS_H
