/*****************************************************************************
ģ   ��   ��: g723encoder
��   ��   ��: g723encoder.h
�� ��  �� ��: 
�ļ�ʵ�ֹ���: G723������ͷ�ļ�
��        ��: V1.0  Copyright(C) 2005-2007 KDC, All rights reserved.
-----------------------------------------------------------------------------
�� �� �� ¼:
��       ��      �汾        �޸���      �޸�����
                 1.0         ******      ��    ��         
 2005/04/28      2.0         ��  ��      1.����˰������ƺ�G723ENCODER_H
 2005/09/02      2.1         ��ˮ��      �������͹淶��,for linux testt
******************************************************************************/
#ifndef G723ENCODER_H
#define G723ENCODER_H


#define G723_CODEC_TRUE 0
#define G723_CODEC_FALSE 1

#define G723_53_RATE 0
#define G723_63_RATE 1

#define G723_HF_ON	0
#define G723_HF_OFF 1

l32 G723CodeInit(void **phHandle, l32 iHfFlg);
l32 G723CodeChunk(void *phHandle, s16 *PcmDataBuff, \
				  s8 *G723Stream, l32 iWorkRate );
void G723CodeClose( void *phHandle);
void GetG723Version(char *Version, l32 StrLen, l32 * StrLenUsed);

#endif //end of G723ENCODER_H


