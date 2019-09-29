/*****************************************************************************
ģ����      : 
�ļ���      : audproc_api.h
����ļ�    : 
�ļ�ʵ�ֹ���: 
����        : ½־��
�汾        : V1.0  Copyright(C) 2006-2007 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2008/5/13   1.0         ½־��        ����
2009/11/16  1.1         ½־��        ���� AUDPROC_SETPARAMS ָ��
******************************************************************************/
#ifndef  _AUDPROC_API_H_
#define  _AUDPROC_API_H_
#ifdef __cplusplus
extern "C" {
#endif   /* __cplusplus */

#include "audcom_api.h"

enum AudProcCmdId
{
    AUDPROC_GET_STATUS = 701,
    AUDPROC_ANALYZE_ERRCODE,
    AUDPROC_DEBUG,
    AUDPROC_SET_PARAMS		
};

l32 AudioProcOpen(void **ppvHandle, void *ptAudProcParam);
l32 AudioProcClose(void *pvHandle);
l32 AudioProcProcess(void *pvHandle, void *ptAudProcInput, void *ptAudProcOutput, void *unionparam);
l32 AudioProcControl(void *pvHandle, l32 cmdid, void *ptAudProControlInParam, void *ptAudProControlOutParam);
l32 AudioProcGetVersion(void *ptAudVerInfoInput, void *ptAudVerInfoOutput);

extern TAudCodecApi tAudioProc;

#ifdef __cplusplus
}
#endif  /* __cplusplus */
#endif


