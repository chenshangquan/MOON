/******************************************************************************
ģ����  �� VPSS_DRV_API
�ļ���  �� vpss_api_dctrl.h
����ļ��� vpss_api_dctrl.c
�ļ�ʵ�ֹ��ܣ�
����    ���ŷ���
�汾    ��1.0.0.0.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
03/29/2011  1.0         �ŷ���      ����
******************************************************************************/
#ifndef __VPSS_API_DCTRL_H
#define __VPSS_API_DCTRL_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "vpss_api_core.h"

/* -------------------------------- �궨�� ----------------------------------*/
/* dwVencId���� */
#define VPSS_VENC_HDMI                      0x1
#define VPSS_VENC_HDCOMP                    0x2
#define VPSS_VENC_DVO2                      0x4
#define VPSS_VENC_SD                        0x8

/* dwClkSrc���� */
#define VPSS_VPLL_OUTPUT_VENC_D             0x1     /* �����������HDMI��PLLʱ�� */
#define VPSS_VPLL_OUTPUT_VENC_A             0x2     /* ģ���������HDCOMP��PLLʱ�� */

#define VPSS_DC_HS_POLARITY_MASK            0xc0    /* �������ͬ���������� */
#define VPSS_DC_VS_POLARITY_MASK            0x30    /* ����ĳ�ͬ���������� */
#define VPSS_DC_HS_POLARITY_SHIFT           6       /* �������ͬ������ƫ�� */
#define VPSS_DC_VS_POLARITY_SHIFT           4       /* ����ĳ�ͬ������ƫ�� */
#define VPSS_DC_POLARITY_AUTO               0
#define VPSS_DC_POLARITY_ACT_LOW            1
#define VPSS_DC_POLARITY_ACT_HIGH           2
/* ����ڵ㶨�� */
#define VPSS_DC_MAX_EDGES                   46

#define VPSS_DC_MAIN_INPUT_PATH             (0u)    /* main input path */
#define VPSS_DC_VCOMP_MUX                   (1u)    /* vcomp multiplexer */
#define VPSS_DC_HDCOMP_MUX                  (2u)    /* hdcomp multiplexer */
#define VPSS_DC_SDVENC_MUX                  (3u)    /* sdvenc multiplexer */
#define VPSS_DC_AUX_INPUT_PATH              (4u)    /* auxiliary input path */
#define VPSS_DC_BP0_INPUT_PATH              (5u)    /* bypass 0 input path */
#define VPSS_DC_BP1_INPUT_PATH              (6u)    /* bypass 1 input path */

#define VPSS_DC_SEC1_INPUT_PATH             (10u)   /* transcode/secondary 2 input path */

#define VPSS_DC_VCOMP                       (14u)   /* VCOMP */

/** \brief macros defining cig constrained output. cig is used for
  * constraning input video. there are three video outputs
  *  from cig, i.e. non-constrained video output (hdmi), which
  *  provides original video stream, constrained
  *  video output (hdcomp), which provides video with the reduced quality
  *  and pip video output, which can be used for pip. */
#define VPSS_DC_CIG_CONSTRAINED_OUTPUT      (15u)
#define VPSS_DC_CIG_PIP_INPUT               (16u)   /* CIG PIP input. In CIG this is the only path
                                                       which can be disabled. Main input path cannot be disabled. */
#define VPSS_DC_CIG_NON_CONSTRAINED_OUTPUT  (17u)   /* cig non-contrained output. */

/** \brief Macro defining CIG PIP output. This output cannot also be used
  * as pip in the display. Input to the pip is aux path, which can be
  * smaller than the actual display size. In this case, CIG fills rest of the
  * display area with the zero. */
#define VPSS_DC_CIG_PIP_OUTPUT              (18u)

#define VPSS_DC_GRPX0_INPUT_PATH            (19u)   /* graphics 0 input path */
#define VPSS_DC_GRPX1_INPUT_PATH            (20u)   /* graphics 1 input path */
#define VPSS_DC_GRPX2_INPUT_PATH            (21u)   /* graphics 2 input path */

#define VPSS_DC_HDMI_BLEND                  (22u)   /* for the vps blenders brief macro for the hdmi blender */
#define VPSS_DC_HDCOMP_BLEND                (23u)   /* for the hdcomp blender */
#define VPSS_DC_DVO2_BLEND                  (24u)   /* for the dvo2 blender */
#define VPSS_DC_SDVENC_BLEND                (25u)   /* for the sdvenc blender */


/* ------------------------------- ���Ͷ��� ---------------------------------*/


/* ------------------------------- �ṹ���� ---------------------------------*/

/* VPSS����ṹ���� */
typedef struct{
    u32	    dwStartNode;                /* ���ӵ���ʼ�ڵ㣬ȡֵ��: ����ڵ㶨�� */
    u32	    dwEndNode;                  /* ���ӵ�Ŀ�Ľڵ� */
} TVpssEdge;

typedef struct{
    u32	        dwNumEdges;             /* ��Ƶ������Ϊ��λ,Ϊ0��ʾ���ź� */
    TVpssEdge   atEdgeInfo[VPSS_DC_MAX_EDGES];
} TVpssEdges;

typedef enum
{
    VPSS_DC_CTRL_BRIGHTNESS = 0,
    /**< Brightness control */
    VPSS_DC_CTRL_CONTRAST,
    /**< Contrast control */
    VPSS_DC_CTRL_SATURATION,
    /**< Saturation control */
    VPSS_DC_CTRL_HUE,
    /**< Saturation control */
    VPSS_DC_CTRL_MAX
    /**< Control Max */
} TVpssDcCtrl;

typedef struct
{
    u32  vencNodeNum;
    /**< Node Number of the Venc. */
    u32  control;
    /**< Control to be set For the valid values, se #Vps_DcCtrl */
    s32   level;
    /**< Brightness level,
         Varies from 1 to 256 for brightness/contrast/saturation.
         For Hue, it varies from 1 to 62 */
} TVpssDcVencControl;

typedef struct{
    s16 brightValue;
    s16 contrastValue;
    s16 hueValue;
    s16 saturationValue;
}TVpssCproc;

/* �������� */
/*==============================================================================
    ������      : VpssDcSetVencStd
    ����        : ����ָ��VENC����ڵ���ʽ
    �������˵��: dwVencId: VENC��ID�ţ���: VPSS_VENC_HDMI
                  dwClkSrc: dwVencId=VPSS_VENC_DVO2ʱ��Ҫָ��ʱ��Դѡ��
                            HDMI��   VPSS_VPLL_OUTPUT_VENC_D ��
                            HDCOMP�� VPSS_VPLL_OUTPUT_VENC_A
                  ptVidInfo: ��Ƶ��ʽ
    ����ֵ˵��  : ���󷵻�VPSS_FAILURE������룻�ɹ�����VPSS_SUCCESS
-----------------------------------------------------------------------------*/
s32 VpssDcSetVencStd(u32 dwVencId, u32 dwClkSrc, TVpssVidStd *ptVidInfo);

/*==============================================================================
    ������      : VpssDcConnectEdge
    ����        : ����VPSS�ڲ���������
    �������˵��: ptEdgesInfo: Ҫ���õľ�����Ϣ
                  bConnect: TRUE=����;FALSE=�Ͽ�
    ����ֵ˵��  : ���󷵻�VPSS_FAILURE������룻�ɹ�����VPSS_SUCCESS
-----------------------------------------------------------------------------*/
s32 VpssDcConnectEdge(TVpssEdges *ptEdgesInfo, BOOL32 bConnect);


/*==============================================================================
    ������      : VpssDcCprocConfig
    ����        : ����VPSS�ڲ�cproc����
    �������˵��: cprocParam: Ҫ���ڵĲ�����Ŀǰʵ��������(brightValue)���Աȶ�
                 (contrastValue)���ڣ���Χ��1~100
    ����ֵ˵��  : ���󷵻�VPSS_FAILURE������룻�ɹ�����VPSS_SUCCESS
-----------------------------------------------------------------------------*/
s32 VpssDcCprocConfig(TVpssCproc *cprocParam);

s32 VpssDcSetVencControl(TVpssDcVencControl *adjust_image_param);
s32 VpssDcGetVencControl(TVpssDcVencControl *adjust_image_param);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __VPSS_API_DCTRL_H */
