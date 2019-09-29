/******************************************************************
ģ���� 			�������������붨���ļ�
�ļ��� 			��mixErr.h
����ļ�		��
�ļ�ʵ�ֹ���	�������������붨��
����			���Ѵ���	
�汾			��0.1
��������		��2003/6/10
-------------------------------------------------------------------
�޸ļ�¼��
����     	  �汾    	 �޸���    �޸�����
2004/11/19    0.2        ��  ��    �޸��˽ӿ�����MixAud20��MixAud32
******************************************************************/
#ifndef MIXER_H
#define MIXER_H

#define MIXER_OK  0
#define MIXER_ERR -1

#define FAILE 1L
#define SUCCESS 0L

#define MAX_CHANNEL 64


typedef 	struct
{
	void*  mPcmBuf;
	u32	nVolume;
}TMixAudio;

typedef struct
{
    u8    *mPCMValue; //pointer to Audio Buffer
    u32   nVolume;  //Audio Volume
}TAudBuf;


l32 MixAud20(TAudBuf *InBufArray[],
             u64 InChIndex,
             TAudBuf *OutBufArray[],
             TAudBuf *NoutChannel,
             u32 uiPCMLength);
             
l32 MixAud32(TAudBuf *InBufArray[],
             u64 InChIndex,
             TAudBuf *OutBufArray[],
             TAudBuf *NoutChannel,
             u32 uiPCMLength);             

void  GetMixerVersion(s8 *Version, l32 StrLen, l32 * StrLenUsed);

#endif

