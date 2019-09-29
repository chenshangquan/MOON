/*****************************************************************************
ģ����      : 
�ļ���      : audenc_api.h
����ļ�    : 
�ļ�ʵ�ֹ���: 
����        : ½־��
�汾        : V1.0  Copyright(C) 2006-2007 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2008/5/13   1.0         ½־��        ����
2009/11/16  1.1         ½־��        ���� AUDENC_SETPARAMS ָ��
******************************************************************************/
#ifndef  _AUDENC_API_H_
#define  _AUDENC_API_H_
#ifdef __cplusplus
extern "C" {
#endif   /* __cplusplus */

#include "audcom_api.h"

enum AudEncCmdId
{
    AUDENC_GET_STATUS = 501,
    AUDENC_ANALYZE_ERRCODE,
    AUDENC_DEBUG,
    AUDENC_SET_PARAMS		
};

l32 AudEncodeOpen(void **ppvHandle, void *ptAudEncParam);
l32 AudEncodeClose(void *pvHandle);
l32 AudEncodeProcess(void *pvHandle, void *ptAudEncInputIn, void *ptAudEncOutputOut, void *unionparam);
l32 AudEncodeControl(void *pvHandle, l32 cmdid, void *ptAudEncControlInParam, void *ptAudEncControlOutParam);
l32 AudEncodeGetVersion(void *ptAudVerInfoInput, void *ptAudVerInfoOutput);

extern TAudCodecApi tAudEnc;

#ifdef __cplusplus
}
#endif  /* __cplusplus */
#endif


