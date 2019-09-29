/*****************************************************************************
ģ����      : mcu
�ļ���      : drvCriStateQuery.h
����ļ�    : drvCriStateQuery.c
�ļ�ʵ�ֹ���:  �ڲ�ʹ�õ�һЩ�궨��ͺ�������.
����        : �ŷ���
�汾        : V1.0  Copyright(C) 2003-2005 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2003/8/19   01a         �ŷ���      ����	
******************************************************************************/
#ifndef __INCdrvCriStateQueryh
#define __INCdrvCriStateQueryh

#ifdef __cplusplus
extern "C" {
#endif

#define VER_CRIDRVLIB  ( const char * )"CRIVxNIP 30.01.05.02.040715"


/* fpga���Ĵ�����bitλ���붨�� */
#define FPGA_REG_HWVER     ((UINT8)0Xf0) 
#define FPGA_REG_FPGAVER   ((UINT8)0X0f)
#define FPGA_REG_BK        ((UINT8)0X0f)
#define FPGA_REG_LAYER     ((UINT8)0X03)

#define FPGA_RD_REG0       ((UINT8)0X00) 
#define FPGA_RD_REG1       ((UINT8)0X01)
#define FPGA_RD_REG2       ((UINT8)0X02) 
#define FPGA_RD_REG3       ((UINT8)0X03)


/* ָʾ��״̬���ݽṹ */
typedef struct{
    UINT8 byLedRUN;      /* ϵͳ���е� */
    UINT8 byLedMRUN;     /* VOIP/DDNģ�����е� */
    UINT8 byLedSPD0;     /* ����0����ָʾ�� */
    UINT8 byLedLNK0;     /* ����0����ָʾ�� */
    UINT8 byLedACT0;     /* ����0�����շ���Чָʾ�� */
    UINT8 byLedSPD1;     /* ����1����ָʾ�� */
    UINT8 byLedLNK1;     /* ��̫��1���ӵ� */
    UINT8 byLedACT1;     /* ����1�����շ���Чָʾ�� */
    UINT8 byLedWERR;     /* ���������ݴ��� */
    UINT8 byLedMLNK;     /* ��MPC����ָʾ�� */
}TBrdCRILedStateDesc;


UINT8 BrdCRIGetModuelState(void);   /* ��ѯ����ģ�����߷� */
STATUS BrdCRIQueryLedState(TBrdCRILedStateDesc *ptBrdCRILedState);  /* ����ģʽ��ѯ */
void cridrvver(void);               /* criDrv�汾��Ϣ��ӡ */

#ifdef __cplusplus
}
#endif

#endif /* __INCdrvCriPatchh */