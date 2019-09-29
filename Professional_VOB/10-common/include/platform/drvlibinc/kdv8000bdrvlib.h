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
#ifndef __INCKdv8000bDrvLibh
#define __INCKdv8000bDrvLibh


#ifdef __cplusplus 
extern "C" { 
#endif /* __cplusplus */

#include "time.h"
#include "timers.h"

/* �궨�� */
#define VER_KDV8000BVxNIP  ( const char * )"KDV8000BVxNIP 30.01.02.04.041016"


/* ָʾ��״̬���ݽṹ */
typedef struct{
    UINT8 byLedRun; 
    UINT8 byLedLNK0;
    UINT8 byLedLNK1;
}TBrdKDV8000BLedStateDesc;


/* �������� */
STATUS BrdTimeGet( struct tm* pGettm );        /* ��ȡϵͳʱ�� */
STATUS BrdTimeSet( struct tm* pSettm );        /* ����ϵͳʱ�� */ 

STATUS BrdKDV8000BQueryLedState(TBrdKDV8000BLedStateDesc *ptBrdKDV8000BLedState);  /* ����ģʽ��ѯ */




#ifdef __cplusplus 
} 
#endif /* __cplusplus */

#endif   /* INCKdv8000bDrvLibh */
