/*****************************************************************************
ģ����      : mcu
�ļ���      : vasDrvLib.h
����ļ�    : drvMpcControl.c
�ļ�ʵ�ֹ���:  �ڲ�ʹ�õ�һЩ�궨��ͺ�������.
����        : �ŷ���
�汾        : V1.0  Copyright(C) 2003-2005 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2003/8/19   01a         �ŷ���      ����	
******************************************************************************/
#ifndef __INCMMPDrvLibh
#define __INCMMPDrvLibh


#ifdef __cplusplus 
extern "C" { 
#endif /* __cplusplus */

#include "time.h"
#include "timers.h"

/* �궨�� */
#define VER_MMPVxNIP  ( const char * )"MMPVxNIP 30.01.07.09.041016"

/* ָʾ��״̬���ݽṹ */
typedef struct{
    UINT8 byLedRUN; 
    UINT8 byLedDSPRUN1;
    UINT8 byLedDSPRUN2;
    UINT8 byLedDSPRUN3;
    UINT8 byLedDSPRUN4;
    UINT8 byLedDSPRUN5;
    UINT8 byLedALM;
    UINT8 byLedLNK;
    UINT8 byLedETH0;
    UINT8 byLedETH1;
}TBrdMMPLedStateDesc;

STATUS BrdMMPQueryLedState(TBrdMMPLedStateDesc *ptBrdMMPLedStateDesc);

/* �������� */
STATUS BrdTimeGet( struct tm* pGettm );        /* ��ȡRTCʱ�� */
STATUS BrdTimeSet( struct tm* pSettm );        /* ����RTC��ϵͳʱ�� */ 

#ifdef __cplusplus 
} 
#endif /* __cplusplus */

#endif   /*__INCMMPDrvLibh*/
