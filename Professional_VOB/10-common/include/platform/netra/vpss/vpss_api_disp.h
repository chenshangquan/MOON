/******************************************************************************
ģ����  �� VPSS_DRV_API
�ļ���  �� vpss_api_disp.h
����ļ��� vpss_api_disp.c
�ļ�ʵ�ֹ��ܣ�
����    ���ŷ���
�汾    ��1.0.0.0.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
04/12/2011  1.0         �ŷ���      ����
******************************************************************************/
#ifndef __VPSS_API_DISP_H
#define __VPSS_API_DISP_H

#ifdef __cplusplus
extern "C" { 
#endif /* __cplusplus */

#include "vpss_api_core.h"
#include "vpss_api_dctrl.h"

/* -------------------------------- �궨�� ----------------------------------*/
/* dwDispId����
 * ����BP0��BP1�����ݸ�ʽֻ֧��: VPSS_VID_COLORSPACE_YUV422I_YUYV
 * DEC1����֧��: VPSS_VID_COLORSPACE_YUV422I_YUYV
                 VPSS_VID_COLORSPACE_YUV422SP_UV
                 VPSS_VID_COLORSPACE_YUV420SP_UV
 */
#define VPSS_DISP_INST_BP0                  0x0 /* Bypass path 0 display driver instance number. */
#define VPSS_DISP_INST_BP1                  0x1 /* Bypass path 1 display driver instance number. */
#define VPSS_DISP_INST_SEC1                 0x2 /* Secondary path SD display driver instance number. */
#define VPSS_DISP_INST_DEIH                 0x3 /* DEI HQ path display driver instance number. */
#define VPSS_DISP_INST_DEI                  0x4 /* DEI path display driver instance number. */
#define VPSS_DISP_MAX                       0x5

#define VPSS_DISP_DEFAULT_MAX               0x3
#define VPSS_DISP_FRAME_LIST_DEFAULT_MAX    0x5
#define VPSS_DISP_WIN_DEFAULT_MAX           0x1

#define VPSS_DISP_WIN_MAX                   20
#define VPSS_DISP_FRAME_LIST_MAX            8
#define VPSS_DISP_LAYOUT_MAX                16


/* VpssDispCtrl�����붨�� */
#define VPSS_DISP_SET_WIN_PARAM             0   /* pArgs��Ӧ(TVpssDispRtWinParam *) */
#define VPSS_DISP_GET_DISP_STATUS           1

/* ------------------------------- ���Ͷ��� ---------------------------------*/


/* ------------------------------- �ṹ���� ---------------------------------*/
/* �ṹ���� */
typedef struct{
    u32             dwWinX;                     /* ������Ե�ͼ�������n�����أ�ע�⣺������8�������������ܳ�����ͼ��Χ  */
    u32             dwWinY;                     /* ������Ե�ͼ��������n�У�����ͼ�����ƣ�ע�⣺���ܳ�����ͼ��Χ */
    u32             dwWinWidth;                 /* ��0��ʾȫ����ʾ,��0��ʾ���ڿ�ȣ� ע�⣺���ܳ�����ͼ��Χ */
    u32             dwWinHight;                 /* ��0��ʾȫ����ʾ,��0��ʾ���ڸ߶ȣ� ע�⣺���ܳ�����ͼ��Χ */
    u32             dwFBufSize;                 /* ��0��ʾ�Զ�����ÿ֡Buf��С,��0��ʾ�û�ָ��ÿ֡Buf��С */
    u32             dwPriority;                 /* ������ʾ���ȼ�: 0=��ߣ���������������һ��;1���...���εݼ�
                                                   �������֮�����ص��Ļ��������ò�ͬ�����ȼ�������������
                                                   û���ص��Ĵ��ھ���������ͬ�����ȼ� */
} TVpssDispWin;

typedef struct
{
    u32             dwWinNum;                   /* �ò��ַ���м������� */
    TVpssDispWin    atWinFmt[VPSS_DISP_WIN_MAX];/* ÿ�����ڵĲ��� */
} TVpssDispLayout;


/*defined the memory informaton shared between A8 and M3 for each submodule*/
typedef struct 
{
    u32     paddr;  /* phy  addr */
    void    *vaddr; /* virt addr */
    u32     size;   /* size in byte */
}TVpssFramebufInfo;

typedef struct{
    /* ��Ӧ��VENC������ź���ʽ */
    TVpssVidStd     tVidStd;
    /* ���伸��֡buf��,��Χ:1-VPSS_DISP_FRAME_LIST_MAX, 0=Ĭ��3�� */
    u32             dwFrameListNum;             
     /**
     *Ϊ0��ʾ����������buf, >0Ϊ�û������buf����
     *���ٷ���wFrameListNum * dwWinNumMax 
     *������VpssFbufAlloc�������䣬��Tiler�ڴ��޷��ͷ�
     *�û���þ�̬�������������ڴ� 
     */
    u32             dwUsrFrameNum;
    /**
      * ΪNULL��ʾ����������buf
      * ����Ϊ�û������buf���������׵�ַ 
      */
    TVpssFramebufInfo *ptUsrFrames;
    u32             dwLayoutNum;                /* �м��ִ��ڲ��ַ�񣬷�Χ: 1~VPSS_DISP_LAYOUT_MAX,0=Ĭ��1�� */
    u32             dwLayoutDisp;               /* �����������ֲ��ַ����ʾ */
    TVpssDispLayout atDispLayout[VPSS_DISP_LAYOUT_MAX];/* ���ڲ��ַ����� */

    u32             dwMemType;                  /* �ݲ�֧��: VPSS_VPDMA_MT_NONTILEDMEM,VPSS_VPDMA_MT_TILEDMEM */
} TVpssDispParam;

/* ����(run time)��̬�������� */
typedef struct{
    u32             dwLayoutDisp;               /* �������ִ��ڲ��ַ�� */
} TVpssDispRtWinParam;


/* �������� */
/*==============================================================================
    ������      : VpssDispOpen
    ����        : ��ָ��DISP��
    �������˵��: dwDispId: DISP�ڵ�ID�ţ���: VPSS_DISP_INST_BP0
                  ptDispParam: DISP�ڲ���
    ����ֵ˵��  : ���󷵻�VPSS_FAILURE������룻�ɹ�����VPSS_SUCCESS
-----------------------------------------------------------------------------*/
s32 VpssDispOpen(u32 dwDispId, TVpssDispParam *ptDispParam);

/*==============================================================================
    ������      : VpssDispClose
    ����        : �ر�ָ��DISP��
    �������˵��: dwDispId: DISP�ڵ�ID�ţ���: VPSS_DISP_INST_BP0
    ����ֵ˵��  : ���󷵻�VPSS_FAILURE������룻�ɹ�����VPSS_SUCCESS
-----------------------------------------------------------------------------*/
s32 VpssDispClose(u32 dwDispId);

/*==============================================================================
    ������      : VpssDispDequeue
    ����        : �Ӳ��ſն�����ȡһ��buf�б�
    �������˵��: 
    ����ֵ˵��  : ���󷵻�VPSS_FAILURE������룻�ɹ�����VPSS_SUCCESS
------------------------------------------------------------------------------*/
s32 VpssDispDequeue(u32 dwDispId, TVpssFrameList *ptFrameList, u32 dwStreamId, s32 nTimeout);

/*==============================================================================
    ������      : VpssDispQueue
    ����        : ����һ��buf�б����Ŷ���
    �������˵��: 
    ����ֵ˵��  : ���󷵻�VPSS_FAILURE������룻�ɹ�����VPSS_SUCCESS
------------------------------------------------------------------------------*/
s32 VpssDispQueue(u32 dwDispId, TVpssFrameList *ptFrameList, u32 dwStreamId);

/*==============================================================================
    ������      : VpssDispCtrl
    ����        ���豸���ƣ�Ŀǰ������
                  ......
    �������˵����dwDispId: DISP�ڵ�ID�ţ���: VPSS_DISP_INST_BP0
                  nCmd: �����룻pArgs: ����ָ�� ���: VpssDispCtrl�����붨��
    ����ֵ˵��  : ���󷵻�VPSS_FAILURE������룻�ɹ�����VPSS_SUCCESS
------------------------------------------------------------------------------*/
s32 VpssDispCtrl(u32 dwDispId, s32 nCmd, void *pArgs);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __VPSS_API_DISP_H */
