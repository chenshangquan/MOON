/******************************************************************************
ģ����  �� VPSS_DRV_API
�ļ���  �� vpss_api_m2m_dei.h
����ļ��� vpss_api_m2m_dei.c
�ļ�ʵ�ֹ��ܣ�
����    ��hcj
�汾    ��1.0.0.0.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
04/12/2011  1.0         hcj         ����
06/03/2011  1.1         �ŷ���      ���Ӷ�handle��֧��
******************************************************************************/
#ifndef __VPSS_API_M2M_DEI_H
#define __VPSS_API_M2M_DEI_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "vpss_api_core.h"

/* -------------------------------- �궨�� ----------------------------------*/

/* dwDeiId���� */
#define VPSS_M2M_INST_MAIN_DEIH_SC1_WB0             0x0 /* DEI HQ writeback memory driver instance number */
#define VPSS_M2M_INST_AUX_DEI_SC2_WB1               0x1 /* DEI writeback memory driver instance number */
#define VPSS_M2M_INST_MAIN_DEIH_SC3_VIP0            0x2 /* DEI HQ-VIP0 memory driver instance number */
#define VPSS_M2M_INST_AUX_DEI_SC4_VIP1              0x3 /* DEI VIP1 memory driver instance number */
#define VPSS_M2M_INST_MAIN_DEIH_SC1_SC3_WB0_VIP0    0x4 /* DEI HQ-WRBK-VIP0 dual output memory driver instance number */
#define VPSS_M2M_INST_AUX_DEI_SC2_SC4_WB1_VIP1      0x5 /* DEI WRBK-VIP1 dual output memory driver instance number */
#define VPSS_M2M_DEI_INST_MAX                       0x6

#define VPSS_M2M_DEI_FRAME_LIST_MAX                 16

#define VPSS_M2M_DEI_MAX_HANDLE_PER_INST            4
#define VPSS_M2M_DEI_CH_PER_INST_MAX                16
#define VPSS_M2M_DEIH_REF_FRM_MAX_SIZE              (1920 * 1088 * 4 + 1920 * 272 * 3 * 2)
#define VPSS_M2M_DEIM_REF_FRM_MAX_SIZE              (1920 * 1088 * 3 + 1920 * 272 * 2)

/* dwCfgMode�궨�� */
#define VPSS_M2M_DEI_CONFIG_PER_HANDLE          0   /* �򿪵Ķ˿��豸����ͨ��������ͬ�Ĳ��� */
#define VPSS_M2M_DEI_CONFIG_PER_CHANNEL         1   /* �򿪵Ķ˿��豸����ͨ�����ò�ͬ�Ĳ��� */

/* VpssM2mDeiCtrl�����붨�� */


/* ------------------------------- ���Ͷ��� ---------------------------------*/


/* ------------------------------- �ṹ���� ---------------------------------*/
typedef struct{
    TVpssVidStd     tInVidStd;      /* DEI����ǰ��ͼ����� */
    TVpssVidStd     tDeiOutVidStd;  /* DEI������д��ͼ����� */
    TVpssVidStd     tVipOutVidStd;  /* DEI��������VIP��ͼ����� */

    u32             dwInPitch[VPSS_MAX_PLANES]; /* ����2�е�һ������ÿ����������֮����ֽ������û���0ʱ����������
                                                   ������Ƶ��ʽ�Զ����㣬����û�ָ����Ҫ16�ֽڶ��� */
    u32             dwDeiOutPitch[VPSS_MAX_PLANES]; /* ͬ�� */
    u32             dwVipOutPitch[VPSS_MAX_PLANES]; /* ͬ�� */

    u32             dwInMemType;    /* VPSS_VPDMA_MT_NONTILEDMEM,VPSS_VPDMA_MT_TILEDMEM */
    u32             dwDeiOutMemType;/* �������ΪYUYV��ʽ��ֻ����VPSS_VPDMA_MT_NONTILEDMEM */
    u32             dwVipOutMemType;/* VPSS_VPDMA_MT_NONTILEDMEM,VPSS_VPDMA_MT_TILEDMEM */

    u32             dwDrnEnable;    /* Enables/disables the DRN module in the DEI path. */
    u32             dwComprEnable;  /* Enable compression/decompression for writing back the DEI context
                                       to and from DDR. */
} TVpssM2mDeiChParam;

typedef struct{
    u32             dwChnlNum;                      /* ��������ͨ����ÿ��ͨ�����Դ���һ·ͼƬ��DEI����
                                                      ��Ȼ�������ʱÿ��ͨ���������framelist */
    void            *UsrRefFrameVaddr;
    u32             UsrRefFramePaddr;
    u32             dwCfgMode;                      /* ����ģʽ����: dwCfgMode�궨�� */
    TVpssM2mDeiChParam atChParam[VPSS_M2M_DEI_CH_PER_INST_MAX]; /* ÿ��ͨ���Ĳ��� */
} TVpssM2mDeiParams;

/* �������� */
/*==============================================================================
    ������      : VpssM2mDeiOpen
    ����        : ��ָ��DEI��
    �������˵��: dwDeiId: DEI�ڵ�ID�ţ���: VPSS_M2M_INST_MAIN_DEIH_SC1_WB0
                  ptCapParams: DEI�ڲ���
    ����ֵ˵��  : ���󷵻�VPSS_FAILURE������룻�ɹ�����VPSS_SUCCESS
-----------------------------------------------------------------------------*/
s32 VpssM2mDeiOpen(u32 dwDeiId, u32 dwHdlId, TVpssM2mDeiParams *ptDeiParams);

/*==============================================================================
    ������      : VpssM2mDeiClose
    ����        : �ر�ָ��DEI��
    �������˵��: dwDeiId: DEI�ڵ�ID�ţ���: VPSS_M2M_INST_MAIN_DEIH_SC1_WB0
    ����ֵ˵��  : ���󷵻�VPSS_FAILURE������룻�ɹ�����VPSS_SUCCESS
-----------------------------------------------------------------------------*/
s32 VpssM2mDeiClose(u32 dwDeiId, u32 dwHdlId);

/*==============================================================================
    ������      : VpssM2mDeiProcessFrames
    ����        : DEI������
    �������˵��: dwDeiId: DEI�ڵ�ID�ţ���: VPSS_M2M_INST_MAIN_DEIH_SC1_WB0
    ����ֵ˵��  : ���󷵻�VPSS_FAILURE������룻�ɹ�����VPSS_SUCCESS
==============================================================================*/
s32 VpssM2mDeiProcessFrames(u32 dwDeiId, u32 dwHdlId, TVpssProcessList *ptProcList, s32 nTimeout);

/*==============================================================================
    ������      : VpssM2mDeiCtrl
    ����        ���豸���ƣ�Ŀǰ������
                  ......
    �������˵����dwDeiId: DEI�ڵ�ID�ţ���: VPSS_M2M_INST_MAIN_DEIH_SC1_WB0
                  nCmd: �����룻pArgs: ����ָ�� ���: VpssM2mDeiCtrl�����붨��
    ����ֵ˵��  : ���󷵻�VPSS_FAILURE������룻�ɹ�����VPSS_SUCCESS
------------------------------------------------------------------------------*/
s32 VpssM2mDeiCtrl(u32 dwDeiId, u32 dwHdlId, s32 nCmd, void *pArgs);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __VPSS_API_M2M_DEI_H */
