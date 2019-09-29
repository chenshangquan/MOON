/*****************************************************************************
ģ����      : mcu
�ļ���      : drvMpcStateQuery.h
����ļ�    : drvMpcStateQuery.c
�ļ�ʵ�ֹ���:  �ڲ�ʹ�õ�һЩ�궨��ͺ�������.
����        : �ŷ���
�汾        : V1.0  Copyright(C) 2003-2005 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2003/8/19   01a         �ŷ���      ����	
******************************************************************************/
#ifndef __INCdrvMpcStateQueryh
#define __INCdrvMpcStateQueryh

#ifdef __cplusplus
extern "C" {
#endif

#define VER_MCUDRVLIB  ( const char * )"MCUDrvLib 30.01.04.02.040715"


/* fpga���Ĵ�����bitλ���붨�� */
#define FPGA_REG_BA        ((UINT8)0X80) 
#define FPGA_REG_HSNSI     ((UINT8)0X40) 
#define FPGA_REG_MS        ((UINT8)0X20) 
#define FPGA_REG_OUS       ((UINT8)0X10) 
#define FPGA_REG_HSRSTI    ((UINT8)0X08) 
#define FPGA_REG_MKA       ((UINT8)0X07)
 
#define FPGA_REG_DC48L     ((UINT8)0X80) 
#define FPGA_REG_DC48R     ((UINT8)0X40) 
#define FPGA_REG_DC5L      ((UINT8)0X20) 
#define FPGA_REG_DC5R      ((UINT8)0X10) 
#define FPGA_REG_HPIRDY    ((UINT8)0X08) 
#define FPGA_REG_LOCK      ((UINT8)0X04) 
#define FPGA_REG_TRACK     ((UINT8)0X02) 
#define FPGA_REG_FREERUN   ((UINT8)0X01)

#define FPGA_REG_HWVER     ((UINT8)0Xf0) 
#define FPGA_REG_FPGAVER   ((UINT8)0X0f)
 
#define FPGA_RD_REG0       ((UINT8)0X00) 
#define FPGA_RD_REG1       ((UINT8)0X01)
#define FPGA_RD_REG2       ((UINT8)0X02) 





/* ָʾ��״̬���ݽṹ */
typedef struct{
    UINT8 byLedRUN;     /* ϵͳ���е� */
    UINT8 byLedDSP;     /* DSP���е� */
    UINT8 byLedALM;     /* ϵͳ�澯�� */
    UINT8 byLedMS;      /* ������ָʾ�� */
    UINT8 byLedOUS;     /* ousָʾ�� */
    UINT8 byLedSYN;     /* ͬ��ָʾ�� */
    UINT8 byLedLNK0;    /* ��̫��0���ӵ� */
    UINT8 byLedLNK1;    /* ��̫��1���ӵ� */
    UINT8 byLedNMS;     /* nmsָʾ�� */
    UINT8 byLedNORM;    /* �ư�������ָʾ�� */
    UINT8 byLedNALM;    /* �ư���һ��澯ָʾ�� */
    UINT8 byLedSALM ;   /* �ư������ظ澯ָʾ�� */
}TBrdMPCLedStateDesc;

/* �������� */
UINT8 BrdCheckPowerState(void);
UINT8 BrdCheckSyncLockState(void);

UINT8 BrdMPCQueryAnotherMPCState(void);  /* �Զ�����������Ƿ���λ��ѯ */
UINT8 BrdMPCQueryLocalMSState(void);     /* ��ǰ���������������״̬��ѯ */
UINT8 BrdMPCQuerySDHType(void);          /* ��ģ�������ѯ */
UINT8 BrdMPCQueryNetSyncMode(void);      /* ���໷����ģʽ��ѯ */
STATUS BrdMPCQueryLedState(TBrdMPCLedStateDesc *ptBrdMPCLedState);  /* ����ģʽ��ѯ */
void mcudrvver(void);               /* mcuDrv�汾��Ϣ��ӡ */

#ifdef __cplusplus
}
#endif

#endif /* __INCdrvMpcPatchh */