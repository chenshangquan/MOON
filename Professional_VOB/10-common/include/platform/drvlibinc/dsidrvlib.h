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
#ifndef __INCDsiDrvLibh
#define __INCDsiDrvLibh


#ifdef __cplusplus 
extern "C" { 
#endif /* __cplusplus */

#include "time.h"
#include "timers.h"

/* �궨�� */
#define VER_DSIVxNIP  ( const char * )"DSIVxNIP 30.01.07.07.041016"


/* �ײ�E1�澯��Ϣ�ṹ���� */
typedef struct{
    BOOL bAlarmE1RUA1;     /* E1ȫ1�澯 */
    BOOL bAlarmE1RLOS;     /* E1ʧͬ���澯 */
    BOOL bAlarmE1RRA;      /* E1Զ�˸澯 */
    BOOL bAlarmE1RCL;      /* E1ʧ�ز��澯 */
    BOOL bAlarmE1RCMF;     /* E1��CRC��֡����澯 */
    BOOL bAlarmE1RMF;      /* E1��·��֡����澯 */
}TBrdE1AlarmDesc;

typedef struct{
    TBrdE1AlarmDesc tBrdE1AlarmDesc[4];
}TBrdAllE1Alarm;

/* ָʾ��״̬���ݽṹ */
typedef struct{
    UINT8 byLedRun; 
    UINT8 byLedE1_ALM0;
    UINT8 byLedE1_ALM1;
    UINT8 byLedE1_ALM2;
    UINT8 byLedE1_ALM3;
    UINT8 byLedE1_ALM4;
    UINT8 byLedE1_ALM5;
    UINT8 byLedE1_ALM6;
    UINT8 byLedE1_ALM7;
    UINT8 byLedMLINK;
    UINT8 byLedLNK0;
    UINT8 byLedLNK1;
}TBrdDSILedStateDesc;


/* �������� */
STATUS BrdTimeGet( struct tm* pGettm );        /* ��ȡϵͳʱ�� */
STATUS BrdTimeSet( struct tm* pSettm );        /* ����ϵͳʱ�� */ 

STATUS BrdDSIAlarmE1StateScan(TBrdAllE1Alarm *ptBrdAllE1Alarm); /* DSI��·�澯�������� */
STATUS BrdDSISetRelayMode(UINT8 byE1ID, UINT8 mode);            /* E1��·���ü̵���ģʽ */
STATUS BrdDSISelectNetSyncClk(UINT8 byE1ID);                    /* DSI����ͬ���ο�ʱ�����ѡ�� */
STATUS BrdDSISetNetSyncMode(UINT8 mode);                        /* DSI����ͬ��ʱ��������� */
UINT8 BrdQueryE1Imp(UINT8 byE1ID);                              /* ȡe12�迹ֵ */

STATUS BrdDSIQueryLedState(TBrdDSILedStateDesc *ptBrdDSILedState);  /* ����ģʽ��ѯ */




#ifdef __cplusplus 
} 
#endif /* __cplusplus */

#endif   /*INCDsiverInith*/
