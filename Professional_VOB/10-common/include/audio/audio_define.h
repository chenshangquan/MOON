/******************************************************************************
ģ����      :  AUDIO_DEFINE               
�ļ���      :  AUDIO_DEFINE.h
����ļ�    :  ��
�ļ�ʵ�ֹ���:  ��Ƶ���ⳣ�����궨��
---------------------------------------------------------------------------------------
�޸ļ�¼:
��  ��          �汾            �޸���          �߶���    �޸�����
09/26/2007      1.0             ½־��                    ����
09/27/2007      1.1             ��  ɯ                    ���AEC��غ��ö������
10/30/2007      1.2             ��  ��                    ��ӻ�������غ��ö������
11/16/2007      1.3             ��  ��                    �޸���g7221c�ڴ��С�궨��
                                                          �������������ڴ��С�궨��
06/28/2012      1.4             ½־��                    ����AMR_NB��ض���
11/21/2012      1.5             ½־��                    ����AMR_WB��ض���
12/20/2012      1.6             ½־��                    ����G726��ض���
05/06/2013      1.7             ��  ��                    ����MP2��ض���
09/03/2013      1.8             ��  ��                    ����MAEC��ض���
**************************************************************************************/
#ifndef _AUDIO_DEFINE_H_
#define _AUDIO_DEFINE_H_
#ifdef __cplusplus
extern "C" {
#endif   /* __cplusplus */

#define AUDIO_SUCCESS          0      //�ɹ�����ֵ        
#define AUDIO_FAILURE          (-1)   //ʧ�ܷ���ֵ

/*************common �ڴ�ռ��С************/
#define AUDIO_VER_LEN          128    //�汾����Ҫ����С�ڴ�ռ��С

/***********codec �ڴ�ռ��С***************/
#define AUDENC_MAX_MEM_HANDLE  92504   //��Ƶ�����������Ҫ������ڴ�ռ��С 
#define AUDDEC_MAX_MEM_HANDLE  69944   //��Ƶ�����������Ҫ������ڴ�ռ��С
#define AUDMIX_MAX_MEM_SIZE    18696   //��Ƶ��������Ҫ���ڴ�ռ��С

/*************audio_process �ڴ�ռ��С*********/
#define AGC_MEM_HANDLE  66400                           //�������ģ����Ҫ���ڴ�ռ��С
#define RESAMPLE_MEM_HANDLE    25344                          //�����ʱ任��Ҫ���ڴ�ռ��С
#define AUDPROC_MAX_MEM_SIZE   (25528 + RESAMPLE_MEM_HANDLE)  //��Ƶ������Ҫ���ڴ�ռ��С
#define AUDPROC_AGC_MAX_MEM_SIZE   (25528 + RESAMPLE_MEM_HANDLE + AGC_MEM_HANDLE)  //��Ƶ���������������ģ����Ҫ���ڴ�ռ��С

/*************aec �ڴ�ռ��С*******************/
#define AEC8K_SLOWMEM_SIZE           58488   //8k AEC v100Ƭ���ڴ��С(Byte) 
#define AEC8K_FASTMEM_SIZE           0       //8k AEC v100Ƭ���ڴ��С(Byte)

#define AEC16K_SLOWMEM_SIZE          120500  //16k AEC v100Ƭ���ڴ��С(Byte)
#define AEC16K_FASTMEM_SIZE          0       //16k AEC v100Ƭ���ڴ��С(Byte)

#define AEC32K_SLOWMEM_SIZE          206076  //32k AEC v100Ƭ���ڴ��С(Byte)
#define AEC32K_FASTMEM_SIZE          0       //32k AEC v100Ƭ���ڴ��С(Byte)

#define AEC32K_V200_SLOWMEM_SIZE     275824  //32k AEC v200Ƭ���ڴ��С(Byte)
#define AEC32K_V200_FASTMEM_SIZE     0       //32k AEC v200Ƭ���ڴ��С(Byte)

#define SAEC32K_V100_SLOWMEM_SIZE    690424  //32k SAEC(������AEC)v100Ƭ���ڴ��С(Byte)
#define SAEC32K_V100_FASTMEM_SIZE    0       //32k SAEC(������AEC)v100Ƭ���ڴ��С(Byte)

#define SAEC32K_V200_SLOWMEM_SIZE    400428  //32k SAEC(������AEC)v200Ƭ���ڴ��С(Byte)
#define SAEC32K_V200_FASTMEM_SIZE    0       //32k SAEC(������AEC)v200Ƭ���ڴ��С(Byte)
  
#define MAEC_SLOWMEM_SIZE            1797120 //32k ������Ƭ���ڴ��С(Byte)  

/*************������ǿSPE�ڴ�ռ��С*********/
#define SPE_MAX_MEM_HANDLE           104400   //������ǿ�����Ҫ������ڴ�ռ��С

/*************equalizer�ڴ�ռ��С*********/
#define EQ_MAX_MEM_HANDLE           14832     //���־�������Ҫ������ڴ�ռ��С

/*************AFC�ڴ�ռ��С*********/
#define AFC_MAX_MEM_HANDLE          69632    //Х�����ƾ����Ҫ������ڴ�ռ��С

/*************mixer*****************/
#define AUDMIX_MAX_CHANNEL           32      //������·��
#define AUDMIX_MAX_SAMPLE_COUNT      2304    //������ÿ·ÿ֡��������������
                                             //ע��: 16λ����ÿ������2���ֽ�, 32λ����ÿ������4���ֽ�

//����ģʽ����
typedef enum
{
    AUD_MIX16_MODE,                //16λ����ģʽ
    AUD_MIX32_MODE,                //32λ����ģʽ
    AUD_MIX16_N_MODE               //��16λ����ģʽ(����Nģʽ���)
}TEnumAudMixMode;

/***********codec***************/
//��Ƶ����CODECģʽ
typedef  enum
{
	AUDENC_G711A = 0,              //g.711��A�ɱ�����
	AUDENC_G711U,                  //g.711��u�ɱ�����
    AUDENC_G722,                   //g.722������
    AUDENC_G7231,                  //g.7231������
	AUDENC_G728,                   //g.728������
	AUDENC_G729,                   //g.729������
	AUDENC_ADPCM,                  //adpcm������
	AUDENC_G7221C,                 //g.7221c������
	AUDENC_MP3,                    //MP3������
	AUDENC_HUFFMAN,                //Huffman������(����MP3����ģ��)
	AUDENC_AACLC,                  //AAC�͸��Ӷȱ�����
	AUDENC_AACLD,                  //AAC����ʱ������
	AUDENC_EAACPLUS,               //eAACPlus������
	AUDENC_G719,                   //g.719������
    AUDENC_AMR_NB,                 //AMRխ��������
	AUDENC_AMR_WB,				   //AMR_WB������
	AUDENC_G726,                   //g.726������(����pcm��ʽ����)
	AUDENC_G726a,                  //g.726��A�ɱ�����(����a�ɸ�ʽ����)
	AUDENC_G726u,                  //g.726��u�ɱ�����(����u�ɸ�ʽ����)
	AUDENC_MP2,                    //MP2������
	AUDENC_NONE
}TEnumAudEncCodec; 

//��Ƶ����CODECģʽ
typedef  enum
{
	AUDDEC_G711A = 0,              //g.711��A�ɽ�����
	AUDDEC_G711U,                  //g.711��u�ɽ�����
    AUDDEC_G722,                   //g722������
    AUDDEC_G7231,                  //g7231������
	AUDDEC_G728,                   //g.728������
	AUDDEC_G729,                   //g.729������
	AUDDEC_ADPCM,                  //adpcm������
	AUDDEC_G7221C,                 //g.7221c������
	AUDDEC_MP3,                    //MP3������
	AUDDEC_HUFFMAN,                //Huffman������(����MP3����ģ��)
	AUDDEC_AACLC,                  //AAC�͸��ӶȽ�����
	AUDDEC_AACLD,                  //AAC����ʱ������
	AUDDEC_EAACPLUS,               //eAACPlus������
	AUDDEC_G719,                   //g.719������
	AUDDEC_AMR_NB,                 //AMRխ��������
	AUDDEC_AMR_WB,                 //AMRխ��������
	AUDDEC_G726,                   //g.726������(���pcm��ʽ����)
	AUDDEC_G726a,                  //g.726��A�ɽ�����(���a�ɸ�ʽ����)
	AUDDEC_G726u,                  //g.726��u�ɽ�����(���u�ɸ�ʽ����)
	AUDDEC_MP2,                    //MP2������
	AUDDEC_NONE
}TEnumAudDecCodec;

//��Ƶ���������չ����
typedef enum
{
    AUDDEC_PLC_PARAM = 100         // ���������չ����
}TEnumAudDecParamReservedType;

//��Ƶ����������չ����
typedef enum
{
	AUDDEC_PLC_INPUT = 200         // ����������չ����
}TEnumAudDecInputReservedType;

//�Ƿ����ö������صı�־
typedef enum
{
    AUDPLC_OFF = 0,                // �رն�������
    AUDPLC_ON                      // ������������
}TEnumAudPLCSwitchFLAG;

//��Ƶ֡�жϱ�־
typedef enum
{
    AUDFRAME_GOOD = 0,            // ��ȷ֡
    AUDFRAME_BAD                  // ����֡��ʧ֡
}TEnumAudPLCFrameFLAG;

//��Ƶ������ģʽ
typedef enum
{
	SAMPLE_RATE_8K = 8000,         //������Ϊ8kHz
	SAMPLE_RATE_16K = 16000,       //������Ϊ16kHz
	SAMPLE_RATE_24K = 24000,       //������Ϊ24kHz
	SAMPLE_RATE_32K = 32000,       //������Ϊ32kHz
	SAMPLE_RATE_44K = 44100,       //������Ϊ44.1kHz
	SAMPLE_RATE_48K = 48000        //������Ϊ48kHz
}TEnumAudSampleRate;

//��Ƶ����������
typedef enum
{
    SAMPLE_RATE96000_INDEX = 0,    //������Ϊ96kHz��������0
    SAMPLE_RATE88200_INDEX,        //������Ϊ88.2kHz��������1
    SAMPLE_RATE64000_INDEX,        //������Ϊ64kHz��������2
    SAMPLE_RATE48000_INDEX,        //������Ϊ48kHz��������3
    SAMPLE_RATE44100_INDEX,        //������Ϊ44.1kHz��������4
    SAMPLE_RATE32000_INDEX,        //������Ϊ32kHz��������5
    SAMPLE_RATE24000_INDEX,        //������Ϊ24kHz��������6  
    SAMPLE_RATE22050_INDEX,        //������Ϊ22.05kHz��������7
    SAMPLE_RATE16000_INDEX,        //������Ϊ16kHz��������8
    SAMPLE_RATE12000_INDEX,        //������Ϊ12kHz��������9
    SAMPLE_RATE11025_INDEX,        //������Ϊ11.025kHz��������10 
    SAMPLE_RATE8000_INDEX          //������Ϊ8kHz��������11
}TEnumAudSampleRateIndex;

//����λ��ģʽ
typedef enum
{
	BIT_WIDTH_16 = 16,             //����λ��Ϊ16bit
	BIT_WIDTH_32 = 32              //����λ��Ϊ32bit
}TEnumAudBitWidth;                 
                                   
//����ģʽ                         
typedef enum                       
{                                  
	CH_MONO = 1,                   //������
	CH_STEREO                      //˫����
}TEnumAudChannel;

//���������
typedef enum
{
	G7221C_MO_32K_24K = 24000,     //������ʽ���㷨_����_������_������
	G7221C_MO_32K_32K = 32000,
	G7221C_MO_32K_48K = 48000,
	G719_MO_48K_64K = 64000,
	G722_MO_16K_64K = 64000,
	G7231_MO_8K_53K = 53000,
    G7231_MO_8K_63K = 63000,
	AACLC_MO_16K_48K = 48000,
	AACLC_MO_32K_72K = 72000,
	AACLC_MO_48K_128K = 128000,
	AACLC_ST_16K_48K = 48000,
	AACLC_ST_32K_72K = 72000,
	AACLC_ST_48K_128K = 128000,
	AACLD_ST_24K_64K = 64000,
	AACLD_ST_32K_96K = 96000,
	AACLD_ST_48K_128K = 128000,
	AACLD_MO_24K_32K = 32000,
	AACLD_MO_32K_48K = 48000,
	AACLD_MO_48K_64K = 64000,
	MP2_32K = 32000,
	MP2_64K = 64000,
	MP2_128K = 128000
}TEnumAudBitRate;

//AMR NB������ģʽ
typedef enum
{ 
	MR475 = 0,
	MR515,            
	MR59,
	MR67,
	MR74,
	MR795,
	MR102,
	MR122
}TEnumAmrNbBitRateMode;

//AMR WB������ģʽ
typedef enum
{ 
    MR66 = 0,
    MR885,            
    MR1265,
    MR1425,
    MR1585,
    MR1825,
    MR1985,
    MR2305,
    MR2385
}TEnumAmrWbBitRateMode;

//G726������ģʽ
typedef enum
{ 
    G726_40K = 5,
    G726_32k = 4,
    G726_24k = 3,
    G726_16k = 2 
}TEnumG726BitRateMode;

/*************AGC*******************/

/*************aec*******************/
//AEC����
typedef  enum
{
	AEC_TYPE_8K = 8,               //������AEC��8k������
	AEC_TYPE_16K = 16,             //������AEC��16k������
	AEC_TYPE_32K = 32,             //������AEC��32k������
	AEC_MIX_TYPE_32K = 33,         //���ڸ���64xƽ̨����˫����AEC���ʹ��ʱ��������32k AEC�ı�־
	                               //��AEC_TYPE_32K��֮ͬ������api�ķ�װʹ�õ�Ƭ���ڴ��С��ͬ
	SAEC_TYPE_32K = 64             //˫����AEC��32k������
}TAecType;

//�����붨��
//���д�ģ�鶨�壨ռ��4��bitλ��28��29��30�� 31λ��Ϊ
#define ERR_AUDIOENC_MOD     (1 << 29)     //��Ƶ����ģ��
#define ERR_AUDIODEC_MOD     (2 << 29)     //��Ƶ����ģ��
#define ERR_AUDPROCESS_MOD   (3 << 29)     //��Ƶ����ģ��

//��ģ�鶨�壨ռ��8��bitΪ����20-27λ)Ϊ
#define ERR_G711ENC          (1 << 20)     //G711������ģ��   
#define ERR_G711DEC          (2 << 20)     //G711������ģ��  

#define ERR_G722ENC          (3 << 20)     //G722������ģ��
#define ERR_G722DEC          (4 << 20)     //G722 ������ģ��

#define ERR_G7221CENC        (5 << 20)     //G7221C������ģ��
#define ERR_G7221CDEC        (6 << 20)     //G7221C������ģ��

#define ERR_G728ENC          (7 << 20)     //G728������ģ��
#define ERR_G728DEC          (8 << 20)     //G728������ģ��

#define ERR_G729ENC          (9 << 20)     //G729������ģ��
#define ERR_G729DEC          (10 << 20)    //G729������ģ��

#define ERR_MP3ENC           (11 << 20)    //MP3������ģ��
#define ERR_MP3DEC           (12 << 20)    //MP3������ģ��

#define ERR_ADPCMENC         (13 << 20)    //ADPCM������ģ��
#define ERR_ADPCMDEC         (14 << 20)    //ADPCM������ģ��

#define ERR_AACLCENC         (15 << 20)    //AACLC������ģ��    
#define ERR_AACLCDEC         (16 << 20)    //AACLC������ģ��

#define ERR_AACLDENC         (17 << 20)    //AACLD������ģ��    
#define ERR_AACLDDEC         (18 << 20)    //AACLD������ģ��

#define ERR_G7231ENC         (19 << 20)    //G7231������ģ��
#define ERR_G7231DEC         (20 << 20)    //G7231������ģ��

#define ERR_EAACPLUSENC      (21 << 20)    //eAACPlus������ģ��    
#define ERR_EAACPLUSDEC      (22 << 20)    //eAACPlus������ģ��

#define ERR_G719ENC          (23 << 20)    //G719������ģ��    
#define ERR_G719DEC          (24 << 20)    //G719������ģ��

#define ERR_AMR_NB_ENC       (25 << 20)    //AMR_NB������ģ��    
#define ERR_AMR_NB_DEC       (26 << 20)    //AMR_NB������ģ��

#define ERR_AMR_WB_ENC       (27 << 20)    //AMR_WB������ģ��
#define ERR_AMR_WB_DEC       (28 << 20)    //AMR_WB������ģ��

#define ERR_G726ENC          (29 << 20)    //G726������ģ��
#define ERR_G726DEC          (30 << 20)    //G726������ģ��

#define ERR_MP2ENC           (31 << 20)    //MP2������ģ��
#define ERR_MP2DEC           (32 << 20)    //MP2 ������ģ��

#define ERR_MAEC32K          (127 << 20)   //MAEC32K��ģ��  
#define ERR_AEC8K            (128 << 20)   //AEC8K��ģ��  
#define ERR_AEC16K           (129 << 20)   //AEC16K��ģ��  
#define ERR_AEC32K           (130 << 20)   //AEC32K��ģ��  

#define ERR_DTMF             (131 << 20)   //DTMF��ģ��            
#define ERR_MIXER            (132 << 20)   //������ģ��
#define ERR_SPLIT            (133 << 20)   //SPLIT��ģ��
#define ERR_RESAMPLE         (134 << 20)   //�����ʱ任ģ�� 
#define ERR_SAEC32K          (135 << 20)   //SAEC32K��ģ�� 
#define ERR_SPE              (136 << 20)   //������ǿģ�� 
#define ERR_EQ               (137 << 20)   //���־���ģ�� 
#define ERR_AGC              (138 << 20)   //�Զ�����ģ�� 
#define ERR_AFC              (139 << 20)   //Х�п���ģ��
#define ERR_MDD32K           (140 << 20)   //MDD��ʱ���ģ�� 

#ifdef __cplusplus
}
#endif  /* __cplusplus */           
#endif

