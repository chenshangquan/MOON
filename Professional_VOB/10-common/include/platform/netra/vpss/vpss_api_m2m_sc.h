/******************************************************************************
ģ����  �� VPSS_DRV_API
�ļ���  �� vpss_api_m2m_sc.h
����ļ��� vpss_api_m2m_sc.c
�ļ�ʵ�ֹ��ܣ�
����    ���ŷ���
�汾    ��1.0.0.0.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
04/25/2011  1.0         �ŷ���      ����
******************************************************************************/
#ifndef __VPSS_API_M2M_SC_H
#define __VPSS_API_M2M_SC_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "vpss_api_core.h"

/* -------------------------------- �궨�� ----------------------------------*/
/* dwM2mScId���� */
#define VPSS_M2M_INST_SEC0_SC5_WB2          (0u)    /* 0 1 2��3·ͬʱֻ�� */
#define VPSS_M2M_INST_BP0_SC5_WB2           (1u)    /* ��һ·����Ϊ���� */
#define VPSS_M2M_INST_BP1_SC5_WB2           (2u)    /* ����SC5 */
#define VPSS_M2M_INST_SEC0_SC3_VIP0         (3u)    /* 3��0���ڹ���SEC0���� */
#define VPSS_M2M_INST_SEC1_SC4_VIP1         (4u)
#define VPSS_M2M_INST_HDMI_SC5_WB2          (5u)    /* hdmi blend -> sc5 -> write back to mem  */
#define VPSS_M2M_SC_INST_MAX                (6u)

#define VPSS_M2M_SC_MAX_HANDLE_PER_INST            20
#define VPSS_M2M_SC_MAX_CH                  (36u)   /* ���ж˿ڼ�������಻�ܳ���36��channel */

/* dwCfgMode�궨�� */
#define VPSS_M2M_CONFIG_PER_HANDLE          0   /* �򿪵Ķ˿��豸����ͨ��������ͬ�Ĳ��� */
#define VPSS_M2M_CONFIG_PER_CHANNEL         1   /* �򿪵Ķ˿��豸����ͨ�����ò�ͬ�Ĳ��� */

/* dwVertScType�궨�� */
#define VPSS_SC_VST_POLYPHASE   0 /* Selects polyphase filter. Used for both down as well as up scaling. */
#define VPSS_SC_VST_RAV         1 /* Uses Running Average Filter. Used for down scaling only. Vertical
                                     Scaling ratio <= 0.5x should use RAV. */

/* VpssM2mScCtrl�����붨�� */
#define VPSS_M2M_SC_SET_XXX                 0   /* pArgs��Ӧ(TVpssM2mScRtXXX *) */

/* ------------------------------- ���Ͷ��� ---------------------------------*/


/* ------------------------------- �ṹ���� ---------------------------------*/
/* �ṹ���� */
typedef struct{
    TVpssVidStd     tInVidStd;                  /* ����ǰ��ͼ����� */
    TVpssVidStd     tOutVidStd;                 /* ���ź��ͼ����� */

    u32             dwInPitch[VPSS_MAX_PLANES]; /* ����2�е�һ������ÿ����������֮����ֽ������û���0ʱ����������
                                                   ������Ƶ��ʽ�Զ����㣬����û�ָ����Ҫ16�ֽڶ��� */
    u32             dwOutPitch[VPSS_MAX_PLANES];/* ͬ�� */

    u32             dwInMemType;                /* VPSS_VPDMA_MT_NONTILEDMEM,VPSS_VPDMA_MT_TILEDMEM */
    u32             dwOutMemType;               /* VPSS_VPDMA_MT_NONTILEDMEM,VPSS_VPDMA_MT_TILEDMEM */

    u32             dwCropStartX;               /* ��ԭʼͼ��ü���ʼλ��X���� */
    u32             dwCropStartY;               /* ��ԭʼͼ��ü���ʼλ��Y���� */
    u32             dwCropWidth;                /* ��ԭʼͼ��ü���Ŀ�ȣ�0=���ü� */
    u32             dwCropHeight;               /* ��ԭʼͼ��ü���ĸ߶ȣ�0=���ü� */

    u32             dwVertScType;               /* ��ֱ�������Ŵ���������dwVertScType�궨�� */
    BOOL32          bNonlinearScaling;          /* ���������ű�־ */
    u32             dwStripSize;                /* Strip size for the non linear scaling. */
    u32             dwScBypass;                 /* Scalar should be bypassed or not. */
    u32             dwSubFrameProcEn;           /* �Ƿ����÷ֿ鴦��Ŀǰ�Ȳ�֧�֣��û���0 */
    u32             dwNumSubFrames;             /* ���÷ֿ鴦��ʱ�ּ��飬ÿ���ͼƬ�߶�Ϊԭʼ�߶ȵ�1/dwNumSubFrames */
} TVpssM2mScChParam;

typedef struct{
    u32             dwChnlNum;                      /* ��������ͨ����ÿ��ͨ�����Դ���һ·ͼƬ�����Ŵ���
                                                       ��Ȼ�������ʱÿ��ͨ���������framelist */
    u32             dwCfgMode;                      /* ����ģʽ����: dwCfgMode�궨�� */
    TVpssM2mScChParam atChParam[VPSS_M2M_SC_MAX_CH];/* ÿ��ͨ���Ĳ��� */
} TVpssM2mScParam;


/* �������� */
/*==============================================================================
    ������      : VpssM2mScOpen
    ����        : ��ָ��M2M_SC�˿�
    �������˵��: dwM2mScId: M2M_SC�˿ڵ�ID�ţ���: VPSS_M2M_INST_SEC0_SC5_WB2
                  ptM2mScParam: M2M_SC�˿ڲ���
    ����ֵ˵��  : ���󷵻�VPSS_FAILURE������룻�ɹ�����VPSS_SUCCESS
-----------------------------------------------------------------------------*/
s32 VpssM2mScOpen(u32 dwM2mScId, u32 dwHdlId, TVpssM2mScParam *ptM2mScParam);

/*==============================================================================
    ������      : VpssM2mScClose
    ����        : �ر�ָ��M2M_SC�˿�
    �������˵��: dwM2mScId: M2M_SC�˿ڵ�ID�ţ���: VPSS_M2M_INST_SEC0_SC5_WB2
    ����ֵ˵��  : ���󷵻�VPSS_FAILURE������룻�ɹ�����VPSS_SUCCESS
-----------------------------------------------------------------------------*/
s32 VpssM2mScClose(u32 dwM2mScId, u32 dwHdlId);

/*==============================================================================
    ������      : VpssM2mScProcessFrames
    ����        : ���Ŵ���
    �������˵��: dwM2mScId: M2M_SC�˿ڵ�ID�ţ���: VPSS_M2M_INST_SEC0_SC5_WB2
    ����ֵ˵��  : ���󷵻�VPSS_FAILURE������룻�ɹ�����VPSS_SUCCESS
------------------------------------------------------------------------------*/
s32 VpssM2mScProcessFrames(u32 dwM2mScId, u32 dwHdlId, TVpssProcessList *ptProcList, s32 nTimeout);

/*==============================================================================
    ������      : VpssM2mScCtrl
    ����        ���豸���ƣ�Ŀǰ������
                  ......
    �������˵����dwM2mScId: M2M_SC�˿ڵ�ID�ţ���: VPSS_M2M_INST_SEC0_SC5_WB2
                  nCmd: �����룻pArgs: ����ָ�� ���: VpssM2mScCtrl�����붨��
    ����ֵ˵��  : ���󷵻�VPSS_FAILURE������룻�ɹ�����VPSS_SUCCESS
------------------------------------------------------------------------------*/
s32 VpssM2mScCtrl(u32 dwM2mScId, u32 dwHdlId, s32 nCmd, void *pArgs);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __VPSS_API_M2M_SC_H */
