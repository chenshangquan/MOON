/*****************************************************************************
ģ����      : mcu
�ļ���      : drvCriAlarm.h
����ļ�    : drvCriAlarm.c
�ļ�ʵ�ֹ���:  �ڲ�ʹ�õ�һЩ�궨��ͺ�������.
����        : �ŷ���
�汾        : V1.0  Copyright(C) 2003-2005 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2003/8/19   01a         �ŷ���      ����	
******************************************************************************/
#ifndef __INCdrvCriAlarmh
#define __INCdrvCriAlarmh

#ifdef __cplusplus
extern "C" {
#endif


/* DIC�澯���ݽṹ */
typedef struct{
    BOOL bAlarmModuleOffLine;     /* ģ������ */
}TBrdCRIAlarmVeneer;

/* CRI ����澯�������� */
STATUS BrdCRIAlarmVeneerStateScan(TBrdCRIAlarmVeneer *pTBrdCRIAlarmVeneer); 

#ifdef __cplusplus
}
#endif

#endif /* __INCdrvMpcPatchh */