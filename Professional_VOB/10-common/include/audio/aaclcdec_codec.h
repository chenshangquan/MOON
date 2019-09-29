/******************************************************************************
ģ����      ��AacLc������
�ļ���      : aacdeclc_codec.h
����ļ�    ����
�ļ�ʵ�ֹ��ܣ�AacLc���������ʹ�����Ͷ��⺯������
����        ��
�汾        ��
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2007/10/10  1.0         Ҧ��ǿ      ��    ��
*******************************************************************************/
#ifndef AACLCDEC_CODEC_H
#define AACLCDEC_CODEC_H

#ifdef __cplusplus
extern "C" {
#endif                                         /* __cplusplus */

#include "audio_codec.h"

enum aaclc_dec_errcode 
{
	ERR_AACLCDEC_SLOWMEM_NULL = ERR_AACLCDEC, //�����ڴ�Ϊ��
	ERR_AACLCDEC_SLOWMEM_SMALL,               //�������ڴ治��
	ERR_AACLCDEC_DECTYPE,                     //�������ʹ���
	ERR_AACLCDEC_BITSIZE,                     //�������ȴ���
	ERR_AACLCDEC_HANDLE_NULL,                 //������Ϊ�մ���
	ERR_AACLCDEC_INOUTBUF_NULL,               //�������뻺��Ϊ�մ���
	ERR_AACLCDEC_VERSION,                     //����汾���� 
	ERR_AACLCDEC_CLOSE,                        //�����ͷ��ڴ����
	ERR_AACLCDEC_CLOSE_NULL,                   //�����ͷ��ڴ�Ϊ��
	ERR_AACLCDEC_PPVHANDLE_NULL,               //ppvHandleΪ��
	ERR_AACLCDEC_NEAACDECOPEN,                 //NeAACDecOpen����
	ERR_AACLCDEC_NEAACDECCONFIG,               //NeAACDecSetConfiguration����
	ERR_AACLCDEC_NEAACDECINIT,                 //NeAACDecInit����
	ERR_AACLCDEC_FRAMEDECODE,                  //aac_frame_decode����
	ERR_AACLCDEC_ADTSHEAD,                      //ADTSͷ����
	ERR_AACLCDEC_GETSTATUS_NULL,                //״̬��Ϣ���Ϊ��
	ERR_AACLCDEC_NEAACDECOPEN_FREE,             //NeAACDecOpen�ͷ��ڴ����
	ERR_AACLCDEC_NEAACDECCONFIG_FREE           //NeAACDecSetConfiguration�ͷ��ڴ����
};

/*====================================================================
������      : AacLcDecOpen                          
����        : ��ʼ�����������������ڲ�����                                 
�㷨ʵ��    : ��                                                  
����ȫ�ֱ���: ��                                                      
����        : ppvHandle: ָ����������ָ���ָ��[out]
              ptAudDecParam: ��������ʼ�������ṹ��ָ��[in]
              pvAudMemParam:  �������ڴ����ṹ���ָ��[in]              
����ֵ˵��  : �ɹ�: AUDIO_SUCCESS, ʧ��: ���ش�����                   
====================================================================*/
l32 AacLcDecOpen(void **ppvHandle, TAudDecParam *ptAudDecParam, void *pvAudMemParam);

/*====================================================================
������      : AacLcDecProcess                          
����        : ����һ֡�����ڲ�����                                  
�㷨ʵ��    : ��                                                  
����ȫ�ֱ���: ��                                                      
����        : pvHandle: ָ����������ָ��[in]
              ptAudDecInput: ָ���������ṹ��ָ��[in]
              ptAudDecOutput: ָ���������ṹ��ָ��[out]              
����ֵ˵��  : �ɹ�: AUDIO_SUCCESS, ʧ��: ���ش�����                   
====================================================================*/
l32 AacLcDecProcess(void *pvHandle, TAudDecInput *ptAudDecInput, TAudDecOutput *ptAudDecOutput);

/*====================================================================                        
������      : AacLcDecClose                                                                 
����        : �������ر�                                                                        
�㷨ʵ��    : ��                                                                              
����ȫ�ֱ���: ��                                                                              
����        : pvHandle: ָ����������ָ��[in]                                   
����ֵ˵��  : �ɹ�: AUDIO_SUCCESS, ʧ��: ���ش�����                                           
====================================================================*/                        
l32 AacLcDecClose(void *pvHandle);

/*====================================================================                        
������      : AacLcDecGetStatus                                                                 
����        : �õ�������״̬��Ϣ                                                                        
�㷨ʵ��    : ��                                                                              
����ȫ�ֱ���: ��                                                                              
����        : pvHandle: ָ����������ָ��[in]
              ptAudDecStatusParam: ָ�����״̬�����ṹ��ָ��[in/out]                                 
����ֵ˵��  : �ɹ�: AUDIO_SUCCESS, ʧ��: ���ش�����                                           
====================================================================*/                        
l32 AacLcDecGetStatus(void *pvHandle, TAudDecStatusParam *ptAudDecStatusParam);

/*====================================================================                        
������      : AacLcDecGetVersion                                                                 
����        : �õ��������汾��Ϣ                                                                        
�㷨ʵ��    : ��                                                                              
����ȫ�ֱ���: ��                                                                              
����        : pvVer: �������[out]
              l32BufLen: ���泤��[in]
              pl32VerLen: ��Ϣ����[in/out]                            
����ֵ˵��  : �ɹ�: AUDIO_SUCCESS, ʧ��: ���ش�����                                           
====================================================================*/                        
l32 AacLcDecGetVersion(void *pvVer, l32 l32BufLen, l32 *pl32VerLen);

/*====================================================================
������      : AacLcDecOpen_ti                          
����        : ��ʼ������������, ����ʵ�ʵ�ϵͳ��                                  
�㷨ʵ��    : ��                                                  
����ȫ�ֱ���: ��                                                      
����        : ppvHandle: ָ����������ָ���ָ��[out]
              ptAudDecParam: ��������ʼ�������ṹ��ָ��[in]
              pvAudMemParam:  �������ڴ����ṹ���ָ��[in]              
����ֵ˵��  : �ɹ�: AUDIO_SUCCESS, ʧ��: ���ش�����                   
====================================================================*/
l32 AacLcDecOpen_ti(void **ppvHandle, TAudDecParam *ptAudDecParam, void *pvAudMemParam);

/*====================================================================
������      : AacLcEncProcess_ti                          
����        : ����һ֡������ʵ�ʵ�ϵͳ��                                 
�㷨ʵ��    : ��                                                  
����ȫ�ֱ���: ��                                                      
����        : pvHandle: ָ����������ָ��[in]
              ptAudDecInput: ָ���������ṹ��ָ��[in]
              ptAudDecOutput: ָ���������ṹ��ָ��[out]              
����ֵ˵��  : �ɹ�: AUDIO_SUCCESS, ʧ��: ���ش�����                   
====================================================================*/
l32 AacLcDecProcess_ti(void *pvHandle, TAudDecInput *ptAudDecInput, TAudDecOutput *ptAudDecOutput);

#ifdef __cplusplus
}
#endif  /* __cplusplus */
#endif

