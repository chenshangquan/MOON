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
#ifndef __INCVasDrvLibh
#define __INCVasDrvLibh


#ifdef __cplusplus 
extern "C" { 
#endif /* __cplusplus */

#include "time.h"
#include "timers.h"

/* �궨�� */
#define VER_VASVxNIP  ( const char * )"VASVxNIP 30.01.07.07.041016"

/* ָʾ��״̬���ݽṹ */
typedef struct{
    UINT8 byLedRUN; 
    UINT8 byLedALM;
    UINT8 byLedMLNK;
    UINT8 byLedETHLNK;
}TBrdVASLedStateDesc;

/* �������� */
STATUS BrdTimeGet( struct tm* pGettm );        /* ��ȡRTCʱ�� */
STATUS BrdTimeSet( struct tm* pSettm );        /* ����RTC��ϵͳʱ�� */ 

UINT8 BrdGetMatrixType(void);                    /* ��������Ͳ�ѯ */
void  BrdVideoMatrixSet(UINT8 vedioInSelect, UINT8 vedioOutSelect); /* ��Ƶ�������� */
void  BrdAudioMatrixSet(UINT8 audioInSelect, UINT8 audioOutSelect); /* ��Ƶ�������� */
STATUS BrdVASQueryLedState(TBrdVASLedStateDesc *ptBrdVASLedStateDesc);

#ifdef __cplusplus 
} 
#endif /* __cplusplus */

#endif   /*INCDriverInith*/
