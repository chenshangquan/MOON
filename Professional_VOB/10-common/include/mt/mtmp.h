/*******************************************************************************
 *  ģ����   :                                                                 *
 *  �ļ���   : mtmp.h                                                          *
 *  ����ļ� :                                                                 *
 *  ʵ�ֹ��� :                                                                 *
 *  ����     : ������                                                          *
 *  �汾     : V4.0  Copyright(c) 1997-2005 KDC, All rights reserved.          *
 *                                                                             *
 *    =======================================================================  *
 *  �޸ļ�¼:                                                                  *
 *    ��  ��      �汾        �޸���      �޸�����                             *
 *  2005/12/5     4.0         ������      ����                                 *
 *                                                                             *
 *******************************************************************************/


#ifndef _MT_MP_H_
#define _MT_MP_H_

API BOOL InitDSP();


#ifdef _HD2G_
API BOOL UnloadDSP();
#endif

#ifdef WIN32
#ifdef SOFT_CODEC

#include "codeclib.h"

//��Ƶ���������ػ�ӿ�
void mtRedrawLastFrame( EmCodecComponent emCodec );

void mtSetShowPreview(BOOL bOpen);

//��ȡ��Ƶ���ʻص�����ָ��
void mtGetAudioPowerCallBack(PGETAUDIOPOWER& cb , u32& dwContext);

//���û�ȡ�����Ƶ���ʻص�����
void mtSetAudioPowerOutCallBack( PGETAUDIOPOWER cb , u32 dwContext);

//���û�ȡ������Ƶ���ʻص�����
void mtSetAudioPowerInCallBack( PGETAUDIOPOWER cb, u32 dwContext);

//���ý�������ʾ���ھ��
void mtSetDecoderHandle( HWND hPreview ,HWND hPrimo ,HWND hSecond );

//�Խ���������ץͼ
void mtCodecGrapPic( CDrawWnd *pWnd ,EmVideoType emType);

//�Ա���������ץͼ
void mtCodecGrapPicLocal(CDrawWnd *pWnd);

//���ý��뷽ʽ
void mtCodecSetDecodMod(EmVideoType emType ,BOOL bIFrameOnly );

//������ƵԴ
void mtCodecSelectVidSource(s8* pchFilename, u32 dwLength);

//pcmt ������ѡ��,��ȡ���������б�
u16 mtGetWaveInAudioDevice( s8 pszWaveInAudioDevList[MAX_AUDIO_DEV_NUMBER][MAX_AUDIO_DEV_NAME_LEN] );

//pcmt ������ѡ��,��ȡ��������б�
u16 mtGetWaveOutAudioDevice( s8 pszWaveOutAudioDevList[MAX_AUDIO_DEV_NUMBER][MAX_AUDIO_DEV_NAME_LEN] );

//pcmt ������ѡ��,ѡ����������
void mtSetWaveInAudioDevice( s32 nDeviceID );

//pcmt ������ѡ��,ѡ���������
void mtSetWaveOutAudioDevice( s32 nDeviceID );

#endif  //SOFT_CODEC

#endif //WIN32

#endif

