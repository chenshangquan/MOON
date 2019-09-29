/******************************************************************************
ģ����  �� VPSS_DRV_API
�ļ���  �� vpss_api_grpx.h
����ļ��� vpss_api_grpx.c
�ļ�ʵ�ֹ��ܣ�
����    ���ŷ���
�汾    ��1.0.0.0.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
03/31/2011  1.0         �ŷ���      ����
******************************************************************************/
#ifndef __VPSS_API_GRPX_H
#define __VPSS_API_GRPX_H

#ifdef __cplusplus 
extern "C" { 
#endif /* __cplusplus */

#include "vpss_api_core.h"
#include "vpss_api_dctrl.h"

/* -------------------------------- �궨�� ----------------------------------*/
/* dwGrpxId���� */
#define VPSS_GRPX0                          0x0
#define VPSS_GRPX1                          0x1
#define VPSS_GRPX2                          0x2
#define VPSS_GRPX_MAX                       0x3

#define VPSS_GRPX_WIN_MAX                    12
#define VPSS_GRPX_FRAME_LIST_MAX             8

/* dwBlendType ���� */
#define VPSS_GRPX_BLEND_NO                  0   /* ��͸������ͬ��͸������Ϊ0xff��� */
#define VPSS_GRPX_BLEND_REGION_GLOBAL       1   /* ȫ�����а�͸������͸���������û�ָ�� */
#define VPSS_GRPX_BLEND_COLOR               2   /* color (palette) blending, alpha value in the CLUT is applied*/
#define VPSS_GRPX_BLEND_PIXEL               3   /* pixel(embedding alpha)blending, embedded alpha value is applied */

/* dwTransColorMask ȫ͸����ɫ���붨�� */
#define VPSS_GRPX_TRANS_NO_MASK             0   /* No mask, 8 bits compared */
#define VPSS_GRPX_TRANS_1BIT_MASK           1   /* 1bit mask, MSB 7Bits compared */
#define VPSS_GRPX_TRANS_2BIT_MASK           2   /* 2bit mask, MSB 6Bits compared */
#define VPSS_GRPX_TRANS_3BIT_MASK           3   /* 3bit maks, MSB 5bits compared */

/* VpssGrpxCtrl�����붨�� */
#define VPSS_GRPX_SET_WIN_PARAM             0   /* pArgs��Ӧ(TVpssGrpxRtWinParam *) */

/* ------------------------------- ���Ͷ��� ---------------------------------*/


/* ------------------------------- �ṹ���� ---------------------------------*/
/* �ṹ���� */
typedef struct{
    u32             dwImgWidth;                 /* osdͼƬ���ݿ�ȣ���0��ʾȫ����С */
    u32             dwImgHeight;                /* osdͼƬ���ݸ߶ȣ���0��ʾȫ����С */
    u32             dwWinX;                     /* osd������Ե�ͼ�������n�����أ�����ͼ�����ƣ�ע�⣺���ܳ�����ͼ��Χ  */
    u32             dwWinY;                     /* osd������Ե�ͼ��������n�У�����ͼ�����ƣ�ע�⣺���ܳ�����ͼ��Χ */
    u32             dwWinWidth;                 /* ��0�����dwImgWidth,��0��ʾosd���ڿ�ȣ������dwImgWidth���ȵĻ��������ţ�ע�⣺���ܳ�����ͼ��Χ */
    u32             dwWinHight;                 /* ��0�����dwImgHeight,��0��ʾosd���ڸ߶ȣ������dwImgHeight���ȵĻ��������ţ�ע�⣺���ܳ�����ͼ��Χ */
    u32             dwFBufSize;                 /* ��0��ʾ�Զ�����ÿ֡Buf��С,��0��ʾ�û�ָ��ÿ֡Buf��С */
    u32             dwFPitch;                   /* �û�������ֵ���������Զ������С */

    u32             dwBlendType;                /* ͸���ϳɷ���, ��: VPSS_GRPX_BLEND_REGION_GLOBAL */
    u32             dwBlendAlpha;               /* ȫ��͸��ʱ��͸������,0-255,��dwBlendTypeΪȫ��͸��ʱ����Ч */

    u32             dwTransEnable;              /* ȫ͸�������Ƿ�����: 1=en */
    u32             dwTransColorMask;           /* ȫ͸����ɫ����, ��: VPSS_GRPX_TRANS_NO_MASK */
    u32             dwTransColorRgb24;          /* ȫ͸����ɫRGB888��ʽ */
} TVpssGrpxWin;

typedef struct{
    TVpssVidStd     tVidStd;                    /* ��Ӧ��VENC������ź���ʽ */

    u32             dwFrameListNum;             /* ���伸��֡buf��,��Χ:1-VPSS_GRPX_FRAME_LIST_MAX, 0=Ĭ��3�� */

    u32             dwWinNum;                   /* ����������������,��Χ:1-VPSS_GRPX_WIN_MAX
                                                   Ŀǰ��ʱ֧��һ������, 0=Ĭ��1�� */
    TVpssGrpxWin    tGrpxWin[VPSS_GRPX_WIN_MAX];/* ÿ����������Ĳ��� */
} TVpssGrpxParam;

/* ����(run time)��̬�������� */
typedef struct{
    u32             dwWinId;                    /* ��0��ʾȫ����ʾ,��0��ʾosd���ڿ�ȣ� ע�⣺���ܳ�����ͼ��Χ */

    u32             dwWinX;                     /* osd������Ե�ͼ�������n�����أ�����ͼ�����ƣ�ע�⣺���ܳ�����ͼ��Χ  */
    u32             dwWinY;                     /* osd������Ե�ͼ��������n�У�����ͼ�����ƣ�ע�⣺���ܳ�����ͼ��Χ */

    u32             dwBlendType;                /* ͸���ϳɷ���, ��: VPSS_GRPX_BLEND_REGION_GLOBAL */
    u32             dwBlendAlpha;               /* ȫ��͸��ʱ��͸������,0-255,��dwBlendTypeΪȫ��͸��ʱ����Ч */

    u32             dwTransEnable;              /* ȫ͸�������Ƿ�����: 1=en */
    u32             dwTransColorMask;           /* ȫ͸����ɫ����, ��: VPSS_GRPX_TRANS_NO_MASK */
    u32             dwTransColorRgb24;          /* ȫ͸����ɫRGB888��ʽ */
} TVpssGrpxRtWinParam;


/* �������� */
/*==============================================================================
    ������      : VpssGrpxOpen
    ����        : ��ָ��GRPX��
    �������˵��: dwGrpxId: GRPX�ڵ�ID�ţ���: VPSS_GRPX0
                  ptGrpxParam: GRPX�ڲ���
    ����ֵ˵��  : ���󷵻�VPSS_FAILURE������룻�ɹ�����VPSS_SUCCESS
-----------------------------------------------------------------------------*/
s32 VpssGrpxOpen(u32 dwGrpxId, TVpssGrpxParam *ptGrpxParam);

/*==============================================================================
    ������      : VpssGrpxClose
    ����        : �ر�ָ��GRPX��
    �������˵��: dwGrpxId: GRPX�ڵ�ID�ţ���: VPSS_GRPX0
    ����ֵ˵��  : ���󷵻�VPSS_FAILURE������룻�ɹ�����VPSS_SUCCESS
-----------------------------------------------------------------------------*/
s32 VpssGrpxClose(u32 dwGrpxId);

/*==============================================================================
    ������      : VpssGrpxDequeue
    ����        : �Ӳ��ſն�����ȡһ��buf�б�
    �������˵��: 
    ����ֵ˵��  : ���󷵻�VPSS_FAILURE������룻�ɹ�����VPSS_SUCCESS
------------------------------------------------------------------------------*/
s32 VpssGrpxDequeue(u32 dwGrpxId, TVpssFrameList *ptFrameList, u32 dwStreamId, s32 nTimeout);

/*==============================================================================
    ������      : VpssGrpxQueue
    ����        : ����һ��buf�б����Ŷ���
    �������˵��: 
    ����ֵ˵��  : ���󷵻�VPSS_FAILURE������룻�ɹ�����VPSS_SUCCESS
------------------------------------------------------------------------------*/
s32 VpssGrpxQueue(u32 dwGrpxId, TVpssFrameList *ptFrameList, u32 dwStreamId);

/*==============================================================================
    ������      : VpssGrpxCtrl
    ����        ���豸���ƣ�Ŀǰ������
                  ......
    �������˵����dwGrpxId: GRPX�ڵ�ID�ţ���: VPSS_GRPX0
                  nCmd: �����룻pArgs: ����ָ�� ���: VpssGrpxCtrl�����붨��
    ����ֵ˵��  : ���󷵻�VPSS_FAILURE������룻�ɹ�����VPSS_SUCCESS
------------------------------------------------------------------------------*/
s32 VpssGrpxCtrl(u32 dwGrpxId, s32 nCmd, void *pArgs);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __VPSS_API_GRPX_H */
