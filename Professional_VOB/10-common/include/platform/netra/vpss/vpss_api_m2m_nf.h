/******************************************************************************
ģ����  �� VPSS_DRV_API
�ļ���  �� vpss_api_m2m_nf.h
����ļ��� vpss_api_m2m_nf.c
�ļ�ʵ�ֹ��ܣ�
����    ���ŷ���
�汾    ��1.0.0.0.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
05/06/2011  1.0         �ŷ���      ����
******************************************************************************/
#ifndef __VPSS_API_M2M_NF_H
#define __VPSS_API_M2M_NF_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "vpss_api_core.h"

/* -------------------------------- �궨�� ----------------------------------*/
/* dwM2mNfId���� */
#define VPSS_M2M_INST_NF0                   (0u)    /* ��1���˿��豸 */
#define VPSS_M2M_NF_INST_MAX                (1u)

#define VPSS_M2M_NF_MAX_CH                  (16u)   /* ���ж˿ڼ�������಻�ܳ���16��channel */
#define VPSS_M2M_NF_MAX_HANDLES             (4u)    /* 1���˿��豸�����Դ������ٴΣ�Ŀǰֻ֧�ִ���1�� */

/* dwBypassMode�궨�� */
#define VPSS_NSF_DISABLE_NONE               (0u)    /* Full NF, Spatial NF ON + Temporal NF ON */
#define VPSS_NSF_DISABLE_SNF                (1u)    /* Only Temporal NF ON, Spatial NF bypassed */
#define VPSS_NSF_DISABLE_TNF                (2u)    /* Only Spatial NF ON, Temporal NF bypassed */
#define VPSS_NSF_DISABLE_SNF_TNF            (3u)    /* No NF, Only YUV422 to YUV420 downsample ON */

/* VpssM2mNfCtrl�����붨�� */
#define VPSS_M2M_NF_SET_XXX                 0   /* pArgs��Ӧ(TVpssM2mNfRtXXX *) */

/* ------------------------------- ���Ͷ��� ---------------------------------*/


/* ------------------------------- �ṹ���� ---------------------------------*/
/* �ṹ���� */
typedef struct{
    u32             dwInWidth;                  /* �����˲������ͼ����,������32�������� */
    u32             dwInHeight;                 /* �����˲������ͼ��߶�,������32�������� */
    u32             dwInPitch[VPSS_MAX_PLANES]; /* ����2�е�һ������ÿ����������֮����ֽ������û���0ʱ����������
                                                   ������Ƶ��ʽ�Զ����㣬����û�ָ����Ҫ32�ֽڶ���, �����ʽ�̶�ΪYUV422I_YUYV */
    u32             dwOutPitch[VPSS_MAX_PLANES];/* ͬ�ϣ������ʽ�̶�ΪYUV420SP_UV */

    u32             dwInMemType;                /* VPSS_VPDMA_MT_NONTILEDMEM,VPSS_VPDMA_MT_TILEDMEM */
    u32             dwOutMemType;               /* VPSS_VPDMA_MT_NONTILEDMEM,VPSS_VPDMA_MT_TILEDMEM */
} TVpssM2mNfDataFormat;

/* This structure is changed ,please note it!!!  */

typedef struct{
    u32             dwBypassMode;
    /* ���: dwBypassMode�궨�� */               
    u32             dwSubFrameProcEn;
    /* �Ƿ����÷ֿ鴦��Ŀǰ�Ȳ�֧�֣��û���0 */           
    u32             dwNumLinesPerSubFrame;
    /* ���÷ֿ鴦��ʱÿ���ͼƬ�߶ȣ������� */      
    u32             frameNoiseAutoCalcEnable;
  /**< TRUE: "frameNoise" auto-calculated by HW,
   *  FALSE: auto-calculation disabled, staticFrameNoise[] used instead */

    u32             frameNoiseCalcReset;
  /**< TRUE: "frameNoise" calculation is reset,
   *  FALSE: "frameNoise" calculation is not reset
   *  Use this when changing input stream or input resolution or
   *  for the first frame of processing.
   */

    //u32             subFrameModeEnable;
  /**< TRUE: SubFrame based NSF is ON,
   *   Vps_NsfPerFrameCfgSubFrameCfg must be set for FVID2_Frame.perFrameCfg,
   *  FALSE: Frame/field based NSF  */

    //u32             numLinesPerSubFrame;
  /**< Num lines per subframe, except for last subframe. */

    u32             staticFrameNoise[VPSS_MAX_PLANES];
  /**< Static "frameNoise", valid only when frameNoiseAutoCalcEnable = FALSE */

    u32             spatialStrengthLow[VPSS_MAX_PLANES];
  /**< Advanced NSF parameters, refer to NSF spec for details,
   *  set to VPS_NSF_PROCESSING_CFG_DEFAULT for default values  */

    u32             spatialStrengthHigh[VPSS_MAX_PLANES];
  /**< Advanced NSF parameters, refer to NSF spec for details,
   *  set to VPS_NSF_PROCESSING_CFG_DEFAULT for default values  */

    u32             temporalStrength;
  /**< Advanced NSF parameters, refer to NSF spec for details,
   *  set to VPS_NSF_PROCESSING_CFG_DEFAULT for default values  */

    u32             temporalTriggerNoise;
  /**< Advanced NSF parameters, refer to NSF spec for details,
   *  set to VPS_NSF_PROCESSING_CFG_DEFAULT for default values  */

    u32             noiseIirCoeff;
  /**< Advanced NSF parameters, refer to NSF spec for details,
   *  set to VPS_NSF_PROCESSING_CFG_DEFAULT for default values  */

    u32             maxNoise;
  /**< Advanced NSF parameters, refer to NSF spec for details,
   *  set to VPS_NSF_PROCESSING_CFG_DEFAULT for default values  */

    u32             pureBlackThres;
  /**< Advanced NSF parameters, refer to NSF spec for details,
   *  set to VPS_NSF_PROCESSING_CFG_DEFAULT for default values  */

    u32             pureWhiteThres;
  /**< Advanced NSF parameters, refer to NSF spec for details,
   *  set to VPS_NSF_PROCESSING_CFG_DEFAULT for default values  */
} TVpssM2mNfProcingCfg;

typedef struct{
    u32             dwChnlNum;                      /* ��������ͨ����ÿ��ͨ�����Դ���һ·ͼƬ�������˲�����
                                                       ��Ȼ�������ʱÿ��ͨ���������framelist */
    TVpssM2mNfDataFormat atDataFormat[VPSS_M2M_NF_MAX_CH];/* ÿ��ͨ�������ݸ�ʽ */
    TVpssM2mNfProcingCfg atProcingCfg[VPSS_M2M_NF_MAX_CH];/* ÿ��ͨ�����˲��������� */
} TVpssM2mNfParam;


/* �������� */
/*==============================================================================
    ������      : VpssM2mNfOpen
    ����        : ��ָ��M2M_NF�˿�
    �������˵��: dwM2mNfId: M2M_NF�˿ڵ�ID�ţ���: VPSS_M2M_INST_NF0
                  ptM2mNfParam: M2M_NF�˿ڲ���
    ����ֵ˵��  : ���󷵻�VPSS_FAILURE������룻�ɹ�����VPSS_SUCCESS
-----------------------------------------------------------------------------*/
s32 VpssM2mNfOpen(u32 dwM2mNfId, TVpssM2mNfParam *ptM2mNfParam);

/*==============================================================================
    ������      : VpssM2mNfClose
    ����        : �ر�ָ��M2M_NF�˿�
    �������˵��: dwM2mNfId: M2M_NF�˿ڵ�ID�ţ���: VPSS_M2M_INST_NF0
    ����ֵ˵��  : ���󷵻�VPSS_FAILURE������룻�ɹ�����VPSS_SUCCESS
-----------------------------------------------------------------------------*/
s32 VpssM2mNfClose(u32 dwM2mNfId);

/*==============================================================================
    ������      : VpssM2mNfProcessFrames
    ����        : �����˲�����
    �������˵��: dwM2mNfId: M2M_NF�˿ڵ�ID�ţ���: VPSS_M2M_INST_NF0
    ����ֵ˵��  : ���󷵻�VPSS_FAILURE������룻�ɹ�����VPSS_SUCCESS
------------------------------------------------------------------------------*/
s32 VpssM2mNfProcessFrames(u32 dwM2mNfId, TVpssProcessList *ptProcList, s32 nTimeout);

/*==============================================================================
    ������      : VpssM2mNfCtrl
    ����        ���豸���ƣ�Ŀǰ������
                  ......
    �������˵����dwM2mNfId: M2M_NF�˿ڵ�ID�ţ���: VPSS_M2M_INST_NF0
                  nCmd: �����룻pArgs: ����ָ�� ���: VpssM2mNfCtrl�����붨��
    ����ֵ˵��  : ���󷵻�VPSS_FAILURE������룻�ɹ�����VPSS_SUCCESS
------------------------------------------------------------------------------*/
s32 VpssM2mNfCtrl(u32 dwM2mNfId, s32 nCmd, void *pArgs);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __VPSS_API_M2M_NF_H */
