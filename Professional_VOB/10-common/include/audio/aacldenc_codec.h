/******************************************************************************
ģ����      ��AacLd������
�ļ���      : aacldenc_codec.h
����ļ�    ����
�ļ�ʵ�ֹ��ܣ�AacLd�������������Ͷ���Ͷ��⺯������
����        ��
�汾        ��
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2007/10/10  1.0         ½־��      ��    ��
*******************************************************************************/
#ifndef AACLDENC_CODEC_H
#define AACLDENC_CODEC_H

#ifdef __cplusplus
extern "C" {
#endif                                           /* __cplusplus */

#include "audio_codec.h"

enum aacLd_enc_errcode
{
	ERR_AACLDENC_SLOWMEM_NULL = ERR_AACLDENC,  //�ڴ�ռ�Ϊ�մ���
	ERR_AACLDENC_SLOWMEM_SMALL,                //�ڴ�ռ䲻��
	ERR_AACLDENC_ENCTYPE,                      //�������ʹ���
	ERR_AACLDENC_BITWIDTH,                     //λ�����
	ERR_AACLDENC_FRAMLEN,                      //֡������
	ERR_AACLDENC_CHANNEL,                      //������Ŀ�ж�
	ERR_AACLDENC_BITRATE,                      //�����ʴ���
	ERR_AACLDENC_BITSIZE,                      //�������ȴ���
	ERR_AACLDENC_INOUTBUF_NULL,                //���������������Ϊ�մ���        
	ERR_AACLDENC_HANDLE_NULL,                  //������Ϊ�մ���  
	ERR_AACLDENC_VERSION,                      //�汾����
	ERR_AACLDENC_CLOSE,                        //�����ͷ��ڴ����
	ERR_AACLDENC_PPVHANDLE_NULL,               //���Ϊ��
	ERR_AACLDENC_INIT,                         //��ʼ������
	ERR_AACLDENC_GETSTATUS,                    //�õ�״̬��Ϣ����
	ERR_AACLDENC_CLOSE_NULL,                   //�ͷŵ��ڴ�Ϊ��
	ERR_AACLDENC_INIT_FREE,                    //AacEncInit�ͷŵ��ڴ����
	ERR_AACLDENC_SAMPLERATE,                   //�����ʴ���
	ERR_AACLDENC_INITELEMENTINFO,              //ͨ����ѡ��ͳ�ʼ������
	ERR_AACLDENC_PSY_ALLOCATE,                 //allocate the PsyOut����             
	ERR_AACLDENC_PSYMAIN_INIT,                 //PsyMain��ʼ������
	ERR_AACLDENC_BITUSED,                      //�ڱ��س�ʹ���У�ʹ�õı����������˱��س����������������һ�㲻�ᷢ��
	ERR_AACLDENC_WRITEBITS                     //д��������
};

/*====================================================================
������      : AacLdEncOpen                          
����        : ��ʼ������������                                  
�㷨ʵ��    : ��                                                  
����ȫ�ֱ���: ��                                                      
����        : ppvHandle: ָ����������ָ���ָ��[out]
              ptAudEncParam: ��������ʼ�������ṹ��ָ��[in]
              pvAudMemParam:  �������ڴ����ṹ���ָ��[in]              
����ֵ˵��  : �ɹ�: AUDIO_SUCCESS, ʧ��: ���ش�����                   
====================================================================*/
l32 AacLdEncOpen(void **ppvHandle, TAudEncParam *ptAudEncParam, void *pvAudMemParam);

/*====================================================================
������      : AacLdEncProcess                          
����        : ����һ֡                                 
�㷨ʵ��    : ��                                                  
����ȫ�ֱ���: ��                                                      
����        : pvHandle: ָ����������ָ��[in]
              ptAudEncInput: ָ���������ṹ��ָ��[in]
              ptAudEncOutput: ָ���������ṹ��ָ��[out]              
����ֵ˵��  : �ɹ�: AUDIO_SUCCESS, ʧ��: ���ش�����                   
====================================================================*/
l32 AacLdEncProcess(void *pvHandle, TAudEncInput *ptAudEncInput, TAudEncOutput *ptAudEncOutput);

/*====================================================================                        
������      : AacLdEncClose                                                                 
����        : �������ر�                                                                        
�㷨ʵ��    : ��                                                                              
����ȫ�ֱ���: ��                                                                              
����        : pvHandle: ָ����������ָ��[in]                                   
����ֵ˵��  : �ɹ�: AUDIO_SUCCESS, ʧ��: ���ش�����                                           
====================================================================*/                        
l32 AacLdEncClose(void *pvHandle);

/*====================================================================                        
������      : AacLdEncGetStatus                                                                 
����        : �õ�������״̬��Ϣ                                                                        
�㷨ʵ��    : ��                                                                              
����ȫ�ֱ���: ��                                                                              
����        : pvHandle: ָ����������ָ��[in]
              ptAudEncStatusParam: ָ�����״̬�����ṹ��ָ��[in/out]                                 
����ֵ˵��  : �ɹ�: AUDIO_SUCCESS, ʧ��: ���ش�����                                           
====================================================================*/                        
l32 AacLdEncGetStatus(void *pvHandle, TAudEncStatusParam *ptAudEncStatusParam);

/*====================================================================                        
������      : AacLdEncGetVersion                                                                 
����        : �õ��������汾��Ϣ                                                                        
�㷨ʵ��    : ��                                                                              
����ȫ�ֱ���: ��                                                                              
����        : pvVer: �������[out]
              l32BufLen: ���泤��[in]
              pl32VerLen: ��Ϣ����[in/out]                          
����ֵ˵��  : �ɹ�: AUDIO_SUCCESS, ʧ��: ���ش�����                                           
====================================================================*/                        
l32 AacLdEncGetVersion(void *pvVer, l32 l32BufLen, l32 *pl32VerLen);

#ifdef __cplusplus
}
#endif  /* __cplusplus */
#endif


