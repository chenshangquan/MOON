/*****************************************************************************
ģ   ��   ��: ��������ģ��
��   ��   ��: pitch.h
�� ��  �� ��: 
�ļ�ʵ�ֹ���: ����������ͷ�ļ�
��        ��: V1.0  Copyright(C) 2005-2007 KDC, All rights reserved.
-----------------------------------------------------------------------------
�� �� �� ¼:
��       ��      �汾        �޸���      �޸�����
2005/05/23       1.0         ��  ��      ��    ��
******************************************************************************/
#ifndef PITCH_H
#define PITCH_H



s16 s16PitchOpen(s16 *ps16SpeechWeighted,s16 s16FrameLen,s16 s16PitchMax);
s16 s16PitchClose(s16 *ps16PitchFrac,s16 *ps16Excitation,s16 *ps16Target,
				  s16 *ps16Impulse, s16 s16SubFrameLen,s16 s16Pitch0Min, 
				  s16 s16Pitch0Max,s16 s16Subframe);

#endif