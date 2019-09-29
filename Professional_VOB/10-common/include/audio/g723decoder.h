/*****************************************************************************
ģ   ��   ��: g723decoder
��   ��   ��: g723decoder.h
�� ��  �� ��: 
�ļ�ʵ�ֹ���: G723������ͷ�ļ�
��        ��: V1.0  Copyright(C) 2005-2007 KDC, All rights reserved.
-----------------------------------------------------------------------------
�� �� �� ¼:
��       ��      �汾        �޸���      �޸�����
                 1.0         ******      ��    ��         
 2005/04/28      2.0         ��  ��      1.����˰������ƺ�G723DECODER_H
 2005/09/02      2.1         ��ˮ��      �������͹淶��,for linux test
******************************************************************************/
#ifndef G723DECODER_H
#define G723DECODER_H


l32 G723DecodeChunk(void *phHanlde, s16 *PcmDataBuff,\
					s8 *G723Stream, s16 Crc );
l32 G723DecodeInit(void **phHandle);
l32 G723DecodeClose(void *phHandle);
void GetG723Version(char *Version, l32 StrLen, l32 * StrLenUsed);

#endif //end of G723DECODER_H








