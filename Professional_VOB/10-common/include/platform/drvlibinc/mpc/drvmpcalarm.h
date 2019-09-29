/*****************************************************************************
ģ����      : mcu
�ļ���      : drvMpcAlarm.h
����ļ�    : drvMpcPatch.c
�ļ�ʵ�ֹ���:  �ڲ�ʹ�õ�һЩ�궨��ͺ�������.
����        : �ŷ���
�汾        : V1.0  Copyright(C) 2003-2005 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2003/8/19   01a         �ŷ���      ����	
******************************************************************************/
#ifndef __INCdrvMpcAlarmh
#define __INCdrvMpcAlarmh

#ifdef __cplusplus
extern "C" {
#endif

/* ��Դ�澯���ݽṹ */
typedef struct{
    BOOL bAlarmPowerDC48VLDown;     /* ���Դ-48V�쳣 */
    BOOL bAlarmPowerDC48VRDown;     /* �ҵ�Դ-48V�쳣 */
    BOOL bAlarmPowerDC5VLDown;      /* ���Դ+5V�쳣 */
    BOOL bAlarmPowerDC5VRDown;      /* �ҵ�Դ+5V�쳣 */
}TBrdMPCAlarmPowerDesc;

/* ��Դ���ȸ澯���ݽṹ */
typedef struct{
    BOOL bAlarmPowerFanLLDown;      /* ���Դ�����ͣת */
    BOOL bAlarmPowerFanLRDown;      /* ���Դ�ҷ���ͣת */
    BOOL bAlarmPowerFanRLDown;      /* �ҵ�Դ�����ͣת */
    BOOL bAlarmPowerFanRRDown;      /* �ҵ�Դ�ҷ���ͣת */
}TBrdMPCAlarmPowerFanDesc;

/* MPC����澯���ݽṹ���� */
typedef struct{
    BOOL bAlarmNetClkLockFailed;     /*  ���໷û����ס�ο�ʱ�� */
    TBrdMPCAlarmPowerDesc tBrdMPCAlarmPower; /* ��Դ�澯 */
    TBrdMPCAlarmPowerFanDesc tBrdMPCAlarmPowerFan; /* ��Դ���ȸ澯 */
}TBrdMPCAlarmVeneer;

/* SDH�澯�ṹ���� */
typedef struct{
    BOOL bAlarmLOS;         /* �źŶ�ʧ */
    BOOL bAlarmLOF;         /* ֡��ʧ */
    BOOL bAlarmOOF;         /* ֡ʧ�� */
    BOOL bAlarmLOM;         /* ��֡��ʧ */
    BOOL bAlarmAU_LOP;      /* ����Ԫָ�붪ʧ */
    BOOL bAlarmMS_RDI;      /* ���ö�Զ��ȱ��ָʾ */
    BOOL bAlarmMS_AIS;      /* ���öα���ָʾ */
    BOOL bAlarmHP_RDI;      /* �߽�ͨ��Զ��ȱ��ָʾ */
    BOOL bAlarmHP_AIS;      /* �߽�ͨ������ָʾ */
    BOOL bAlarmRS_TIM;      /* ������ͨ���ټ��ֽڲ�ƥ�� */
    BOOL bAlarmHP_TIM;      /* ��ͨ���ټ��ֽڲ�ƥ�� */
    BOOL bAlarmHP_UNEQ;     /* �߽�ͨ���źű���ֽ�δװ�� */
    BOOL bAlarmHP_PLSM;     /* �߽�ͨ���źű���ֽڲ�ƥ�� */

    BOOL bAlarmTU_LOP;      /* ֧·��Ԫָ�붪ʧ */
    BOOL bAlarmLP_RDI;      /* �ͽ�ͨ��Զ��ȱ��ָʾ */
    BOOL bAlarmLP_AIS;      /* �ͽ�ͨ������ָʾ */
    BOOL bAlarmLP_TIM;      /* �ͽ�ͨ���ټ��ֽڲ�ƥ�� */
    BOOL bAlarmLP_PLSM;     /* �ͽ�ͨ���źű���ֽڲ�ƥ�� */
}TBrdMPCAlarmSDH;


STATUS BrdMPCAlarmVeneerStateScan(TBrdMPCAlarmVeneer *pTBrdMPCAlarmVeneer); /* MPC����澯�������� */
STATUS BrdMPCAlarmSDHStateScan(TBrdMPCAlarmSDH *pTBrdMPCAlarmSDH);          /* MPC SDH�澯�������� */


#ifdef __cplusplus
}
#endif

#endif /* __INCdrvMpcPatchh */