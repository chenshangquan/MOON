/*****************************************************************************
ģ����      : mcu
�ļ���      : drvCriControl.h
����ļ�    : drvCriControl.c
�ļ�ʵ�ֹ���:  �ڲ�ʹ�õ�һЩ�궨��ͺ�������.
����        : �ŷ���
�汾        : V1.0  Copyright(C) 2003-2005 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2003/8/19   01a         �ŷ���      ����	
******************************************************************************/
#ifndef __INCdrvCriControlh
#define __INCdrvCriControlh

#ifdef __cplusplus
extern "C" {
#endif

#include "time.h"
#include "timers.h"

UINT8 BrdFpgaRead(UINT8 Addr);
STATUS BrdTimeGet( struct tm* pGettm );        /* ��ȡRTCʱ�� */
STATUS BrdTimeSet( struct tm* pSettm );        /* ����RTC��ϵͳʱ�� */ 

#ifdef __cplusplus
}
#endif

#endif /* __INCdrvCriPatchh */