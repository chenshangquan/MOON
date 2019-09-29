/******************************************************************************
ģ����      �� audio_codec              
�ļ���      �� audio_codec.h
����ļ�    ����
�ļ�ʵ�ֹ��ܣ� ����뺯������������
---------------------------------------------------------------------------------------
�޸ļ�¼:
��  ��                  �汾            �޸���     �߶���        �޸�����
09/26/2007              1.0            ½־��                    ����
11/16/2009              1.1            ½־��                    ���ӱ����������ú�������
06/28/2012              1.2            ½־��                    ����TAudDtxParam��TAudBitRateModeInput����
11/21/2012              1.3            ½־��                    ���ע��
**************************************************************************************/
#ifndef _AUDIO_CODEC_H_
#define _AUDIO_CODEC_H_
#ifdef __cplusplus
extern "C" {
#endif   /* __cplusplus */

#define TAudEncStatusParam TAudEncParam
#define TAudDecStatusParam TAudDecParam

//��������ʼ�������ṹ��
typedef struct
{   u32 u32Size ;         //��¼�ṹ��ռ��С
    u32 u32EncType;       //��Ƶ����CODECģʽ��TEnumAudEncCodec��
    l32 l32Channel;       //����ģʽ��TEnumAudChannel��
    l32 l32BitWidth;      //����λ��ģʽ��TEnumAudBitWidth��
    l32 l32SampleRate;    //��Ƶ������ģʽ��TEnumAudSampleRate��
    l32 l32BitRate;       //������ģʽ(TEnumAudBitRate)
    l32 l32FrameLen;      //����һ֡������(������*������ÿ֡��������)
    u32 u32FrameHeadFlag; //ÿ֡�����Ƿ��ͷ��Ϣ(��AAC_LCʹ�ã�1���У�0����)
    u32 u32Reserved;      //��������
}TAudEncParam;

//��������ʼ�������ṹ�岹�����(��AMR_NB��AMR_WBʹ��)                                                
//ע: ���ṹ��ʹ��ʱ,ͨ����������ʼ�������ṹ��(TAudEncParam)�ı������������ָ��
typedef struct                                 
{ 
	u32 u32EncType;         //����������(TEnumAudEncCodec)
	l32 l32DtxFlag;         //�Ƿ�ʹ�ܲ���������ģʽ(1:ʹ�ܣ� 0����ʹ��)
	u32 u32Reserved;        //��������                                                                                                                                                                                                                                                                                               
}TAudDtxParam; 

//��������ṹ��
typedef struct
{
    u32 u32Size ;       //��¼�ṹ��ռ��С
    u8 *pu8InBuf;       //ָ����������뻺��ָ��
    u32 u32InBufSize;   //���뻺���ֽ��� 
    u8 *pu8OutBuf;      //ָ��������������ָ��
    u32 u32OutBufSize;  //��������ֽ���  
    u32 u32Reserved;    //��������
}TAudEncInput;

//��������ṹ�岹�����(��AMR_NB��AMR_WB��G726ʹ��)                                                
//ע: ���ṹ��ʹ��ʱ,ͨ������������ṹ��(TAudEncInput)�ı������������ָ��
typedef struct                                 
{ 
	u32 u32EncType;         //����������(TEnumAudEncCodec)
	l32 l32BitRateMode;     //��ǰ֡���������ģʽ(TEnumAmrNbBitRateMode��TEnumAmrWbBitRateMode��TEnumG726BitRateMode)
	u32 u32Reserved;        //��������                                                                                                                                                                                                                                                                                               
}TAudBitRateModeInput; 

//��������ṹ��
typedef struct
{   
    u32 u32Size ;             //��¼�ṹ��ռ��С    
    u32 u32OutBitStreamSize;  //����������ֽ���
    u32 u32StatisCycles;      //����һ֡Ч��ͳ��
    u32 u32Reserved;          //��������
}TAudEncOutput;

//��������ʼ�������ṹ��                  
typedef struct                                  
{   
    u32 u32Size ;          //��¼�ṹ��ռ��С                                            
    u32 u32DecType;        //����������(TEnumAudDecCodec)
    l32 l32BitRate;        //������ģʽ
    u32 u32FrameHeadFlag;  //ÿ֡�����Ƿ��ͷ��Ϣ(��AACʹ�ã�1���У�0����)
    u32 u32Reserved;       //��������                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
}TAudDecParam;        

//��Ƶ��������(PLC)��ʼ�������ṹ��
//ע: ���ṹ��ʹ��ʱ,ͨ����������ʼ���ṹ��ı������������ָ��
typedef struct                                 
{ 
	u32 u32ReservedType;  //���������չ����(AUDDEC_PLC_PARAM)
	u32 u32EnablePlcFlag; //PLC���ܿ��ر�־(AUDPLC_OFF: �ر�, AUDPLC_ON:��)
	u32 u32Reserved;      //��������                                                                                                                                                                                                                                                                                              
}TAudPlcParam; 

//����������ṹ��                                                 
typedef struct                                 
{                                              
	u32 u32Size ;            //��¼�ṹ��ռ��С
	u8 *pu8InBuf;            //ָ����������뻺��ָ��   
	u32 u32InBufSize;        //���뻺���ֽ���                                                                                                                                                                                                                                                                                      ���ָ�?
	u8 *pu8OutBuf;           //ָ��������������ָ�� 
	u32 u32OutBufSize;       //��������ֽ���                                                                                                                                                                                                                                                                                           
	u32 u32InBitStreamSize;  //ÿ֡�������ֽ���
	u32 u32SampelFreIndex;   //ÿ֡����������(��AACʹ��)
	u32 u32Channels;         //ÿ֡ͨ����  
	u32 u32Reserved;         //��������(G726��ʽʱ���ڶ�������ģʽ��TEnumG726BitRateMode)                                                                                                                                                                                                                                                                                                
}TAudDecInput;      

//��Ƶ��������(PLC)������������ṹ��                                                
//ע: ���ṹ��ʹ��ʱ,ͨ������������ṹ��(TAudDecInput)�ı������������ָ��
typedef struct                                 
{ 
	u32 u32ReservedType;    //����������չ����(AUDDEC_PLC_INPUT)
	u32 u32ErrorFrameFlag;  //��֡��־(AUDFRAME_GOOD: ��ȷ֡, AUDFRAME_BAD:����֡)
	u32 u32Reserved;       //��������                                                                                                                                                                                                                                                                                               
}TAudPlcInput; 

//����������ṹ��
typedef struct
{               
    u32  u32Size;         //��¼�ṹ��ռ��С
    u32  u32OutFrameLen ; //ÿ֡���������
    u32  u32StatisCycles; //����һ֡Ч��ͳ��
    u32  u32Reserved;     //��������
}TAudDecOutput; 
                                                                                                                     
/*====================================================================
������      : AudEncOpen                          
����        : ��ʼ������������                                  
�㷨ʵ��    : ��                                                  
����ȫ�ֱ���: ��                                                      
����        : ppvHandle:         ָ����������ָ���ָ��[out]
              ptAudEncParam:     ��������ʼ�������ṹ��ָ��[in]
              pvAudEncMemParam:  �������ڴ����ṹ���ָ��[in]              
����ֵ˵��  : �ɹ�: AUDIO_SUCCESS, ʧ��: ���ش�����                   
====================================================================*/
l32 AudEncOpen(void **ppvHandle, TAudEncParam *ptAudEncParam, void *ptAudEncMemParam);   

/*====================================================================
������      : AudEncProcess                          
����        : ����һ֡                                 
�㷨ʵ��    : ��                                                  
����ȫ�ֱ���: ��                                                      
����        : pvHandle:       ָ����������ָ��[in]
              ptAudEncInput:  ָ���������ṹ��ָ��[in]
              ptAudEncOutput: ָ���������ṹ��ָ��[out]              
����ֵ˵��  : �ɹ�: AUDIO_SUCCESS, ʧ��: ���ش�����                   
====================================================================*/
l32 AudEncProcess(void *pvHandle, TAudEncInput *ptAudEncInput, TAudEncOutput *ptAudEncOutput);

/*====================================================================                        
������      : AudEncGetStatus                                                                 
����        : �õ�������״̬��Ϣ                                                                        
�㷨ʵ��    : ��                                                                              
����ȫ�ֱ���: ��                                                                              
����        : pvHandle:            ָ����������ָ��[in]
              ptAudEncStatusParam: ָ�����״̬�����ṹ��ָ��[in/out]                                 
����ֵ˵��  : �ɹ�: AUDIO_SUCCESS, ʧ��: ���ش�����                                           
====================================================================*/                        
l32 AudEncGetStatus(void *pvHandle, TAudEncStatusParam *ptAudEncStatusParam);

/*====================================================================                        
������      : AudEncClose                                                                 
����        : �������ر�                                                                        
�㷨ʵ��    : ��                                                                              
����ȫ�ֱ���: ��                                                                              
����        : pvHandle: ָ����������ָ��[in]                                   
����ֵ˵��  : �ɹ�: AUDIO_SUCCESS, ʧ��: ���ش�����                                           
====================================================================*/                        
l32  AudEncClose(void *pvHandle);

/*====================================================================                        
������      : AudEncGetVersion                                                                 
����        : �õ��������汾��Ϣ                                                                        
�㷨ʵ��    : ��                                                                              
����ȫ�ֱ���: ��                                                                              
����        : pvVer:      �������[out]
              l32BufLen:  ���泤��[in]
              pl32VerLen: ��Ϣ����[in/out]
              u32EncType: ����������[in]                              
����ֵ˵��  : �ɹ�: AUDIO_SUCCESS, ʧ��: ���ش�����                                           
====================================================================*/                        
l32 AudEncGetVersion(void *pvVer, l32 l32BufLen, l32 *pl32VerLen, u32 u32EncType);

/*====================================================================                        
������      : AudEncSetParams                                                                 
����        : ���ý���������                                                                     
�㷨ʵ��    : ��                                                                              
����ȫ�ֱ���: ��                                                                              
����        : pvHandle:         ָ����������ָ��[in]
              ptAudEncParam:    �����ʼ�������ṹ��ָ��[in]                          
����ֵ˵��  : �ɹ�: AUDIO_SUCCESS, ʧ��: ���ش�����                                           
====================================================================*/                        
l32 AudEncSetParams(void *pvHandle, TAudEncParam *ptAudEncParam);

/*====================================================================
������      : AudDecOpen                          
����        : ��ʼ������������                                  
�㷨ʵ��    : ��                                                  
����ȫ�ֱ���: ��                                                      
����        : ppvHandle:        ָ����������ָ���ָ��[out]
              ptAudDecParam:    �����ʼ�������ṹ��ָ��[in]
              ptAudDecMemParam: �������ڴ����ṹ���ָ��          
����ֵ˵��  : �ɹ�: AUDIO_SUCCESS, ʧ��: ���ش�����                   
====================================================================*/
l32 AudDecOpen (void **ppvHandle, TAudDecParam *ptAudDecParam, void *ptAudDecMemParam);

/*====================================================================                        
������      : AudDecProcess                                                                   
����        : ����һ֡                                                                        
�㷨ʵ��    : ��                                                                              
����ȫ�ֱ���: ��                                                                              
����        : pvHandle:        ָ����������ָ��[in]                                               
              ptAudDecInput:   ָ���������ṹ��ָ��[in]                                      
              ptAudDecOutput:  ָ���������ṹ��ָ��[out]                                    
����ֵ˵��  : �ɹ�: AUDIO_SUCCESS, ʧ��: ���ش�����                                           
====================================================================*/                        
l32 AudDecProcess(void *pvHandle, TAudDecInput *ptAudDecInput, TAudDecOutput *ptAudDecOutput);

/*====================================================================                        
������      : AudDecGetStatus                                                                 
����        : �õ�������״̬��Ϣ                                                                        
�㷨ʵ��    : ��                                                                              
����ȫ�ֱ���: ��                                                                              
����        : pvHandle:            ָ����������ָ��[in]
            ptAudDecStatusParam: ָ�������״̬�����ṹ��ָ��[in/out]                               
����ֵ˵��  : �ɹ�: AUDIO_SUCCESS, ʧ��: ���ش�����                                           
====================================================================*/                        
l32 AudDecGetStatus(void *pvHandle, TAudDecStatusParam *ptAudDecStatusParam);

/*====================================================================                        
������      : AudDecClose                                                                 
����        : �������ر�                                                                        
�㷨ʵ��    : ��                                                                              
����ȫ�ֱ���: ��                                                                              
����        : ppvHandle: ָ����������ָ��[in]                                  
����ֵ˵��  : �ɹ�: AUDIO_SUCCESS, ʧ��: ���ش�����                                           
====================================================================*/                        
l32 AudDecClose(void *pvHandle);

/*====================================================================                        
������      : AudDecGetVersion                                                                 
����        : ��ý������汾��Ϣ                                                                      
�㷨ʵ��    : ��                                                                              
����ȫ�ֱ���: ��                                                                              
����        : pvVer:      �������[out]
            l32BufLen:  ���泤��[in]
            pl32VerLen: ��Ϣ����[in/out]
            u32DecType: ����������[in]                            
����ֵ˵��  : �ɹ�: AUDIO_SUCCESS, ʧ��: ���ش�����                                           
====================================================================*/                        
l32 AudDecGetVersion(void *pvVer, l32 l32BufLen, l32 *pl32VerLen, u32 u32DecType);

/*====================================================================                        
������      : AudDecSetParams                                                                 
����        : ���ý���������                                                                     
�㷨ʵ��    : ��                                                                              
����ȫ�ֱ���: ��                                                                              
����        : pvHandle:         ָ����������ָ��[in]
              ptAudDecParam:    �����ʼ�������ṹ��ָ��[in]                          
����ֵ˵��  : �ɹ�: AUDIO_SUCCESS, ʧ��: ���ش�����                                           
====================================================================*/                        
l32 AudDecSetParams(void *pvHandle, TAudDecParam *ptAudDecParam);

#ifdef __cplusplus
}
#endif  /* __cplusplus */
#endif 

