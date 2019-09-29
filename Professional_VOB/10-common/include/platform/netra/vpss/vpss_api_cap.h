/******************************************************************************
ģ����  �� VPSS_DRV_API
�ļ���  �� vpss_api_cap.h
����ļ��� vpss_api_cap.c
�ļ�ʵ�ֹ��ܣ�
����    ���ŷ���
�汾    ��1.0.0.0.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
04/12/2011  1.0         hcj         ����
******************************************************************************/
#ifndef __VPSS_API_CAP_H
#define __VPSS_API_CAP_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "vpss_api_core.h"
#include "vpss_api_dctrl.h"
#include "vpss_api_frame_mem.h"

/* -------------------------------- �궨�� ----------------------------------*/
/* dwCapId���� */
#define VPSS_CAP_INST_VIP0_PORTA            0x0
#define VPSS_CAP_INST_VIP0_PORTB            0x1
#define VPSS_CAP_INST_VIP1_PORTA            0x2
#define VPSS_CAP_INST_VIP1_PORTB            0x3
#define VPSS_CAP_MAX                        0x4

#define VPSS_CAP_FRAME_LIST_MAX             16

#define VPSS_CAP_STREAM_ID_MAX              4
#define VPSS_CAP_CH_PER_PORT_MAX            16

/* VpssCapCtrl�����붨�� */


/* ------------------------------- ���Ͷ��� ---------------------------------*/


/* ------------------------------- �ṹ���� ---------------------------------*/
/* �ṹ���� */
typedef struct{
    u32             dwDataFormat;               /* �����ɫ��ռ�,���dwNumStream����1�Ļ�ͬʱֻ����1·֧��YUV422_SP */
    u32             dwScEnable;                 /* ʹ��Scale */
    u32             dwMemType;                  /* VPSS_VPDMA_MT_NONTILEDMEM,VPSS_VPDMA_MT_TILEDMEM */
    u32             dwFrameSkipMask;            /* frame skip mask for sequence of 30frames
                                                 * bit0..bit29: bitX = 1, skip frame, else capture frame
                                                 */
} TStreamInfo;

typedef struct{
    u32             dwInWidth;                  /* �������Ƶ��� */
    u32             dwInHeight;                 /* �������Ƶ�߶� */
    u32             dwOutWidth;                 /* �������Ƶ��� */
    u32             dwOutHeight;                /* �������Ƶ�߶� */
    u32             dwCropStartX;               /* �ü���x���� */
    u32             dwCropStartY;               /* �ü���y���� */
    u32             dwCropWidth;                /* �ü��µĿ�� */
    u32             dwCropHeight;               /* �ü��µĸ߶� */
} TVpssCapScParams;

typedef struct{
    BOOL32          bvipCropEnable;             /* �Ƿ�ʹ��VIP�Դ���cropģ��ü�ͼ�񣬽�PG2.0��ʼ��8168��PG2.1��ʼ��8148��֧�� */
    u32             dwCropStartX;               /* �ü���x���� */
    u32             dwCropStartY;               /* �ü���y���� */
    u32             dwCropWidth;                /* �ü���Ŀ�� */
    u32             dwCropHeight;               /* �ü���ĸ߶� */
} TVpssCapVipCrop;

typedef struct{
    TVpssVidStd     tVidStd;                    /* ��Ӧ��������ź���ʽ */

    u32             dwFrameListNum;             /* ���伸��֡buf��,��Χ:1-VPSS_CAP_FRAME_LIST_MAX, 0=Ĭ��5����С��5���Ῠwhy?�� */

    u32             dwNumCh;                    /* ÿ��port���м�·video */

    u32             dwNumStream;                /* �ֳɼ�· stream ���� */

    u32             dwUsrFrameNum;              /* Ϊ0��ʾ����������buf, >0Ϊ�û������buf������
                                                   ���ٷ��� dwFrameListNum*dwNumCh*dwNumStream����
                                                   ������VpssFrameAlloc�������䣬��Tiler�ڴ��޷��ͷţ��û���þ�̬�������������ڴ� */
    TVpssFrame      *ptUsrFrames;               /* ΪNULL��ʾ����������buf, ����Ϊ�û������buf���������׵�ַ */


    TStreamInfo     tStreamInfo[VPSS_CAP_STREAM_ID_MAX];
                                                /* ÿ����������Ĳ��� */

    TVpssCapScParams   tVpssCapScParams;        /* ���Ų�������������ʹ��Scale, 2·ͬʱʹ�����ŵĻ�����ķֱ�����һ������С��Ŀ��
                                                   �Ҳɼ�ͨ����SC������UpScale */

    BOOL32          bFieldMerged;               /* ���ڸ����ź���˵��������2���ϲ�Ϊ1֡��Deque�������� */
    TVpssCapVipCrop tVipCrop;                   /* VIP�Դ���cropģ���������PG2.0��ʼ��8168��PG2.1��ʼ��8148��֧�� */
} TVpssCapParams;

/* �������� */
/*==============================================================================
    ������      : VpssCapOpen
    ����        : ��ָ��CAP��
    �������˵��: dwCapId: CAP�ڵ�ID�ţ���: VPSS_CAP_INST_VIP0_PORTA
                  ptCapParams: CAP�ڲ���
        !!!�������ƣ�
        1�����Ų����������϶�Ӧstream��ʹ��Scale����, 2·ͬʱʹ�����ŵĻ������
           �ֱ�����һ������С��Ŀ�ߣ�
        2���ɼ�ͨ����SC������UpScale����߶�����
        3�����dwNumStream����1����2·�Ļ�ͬʱֻ����1·֧��YUV422_SP��ʽ(dwDataFormat)
           ����2·YUYV��2·YUV420_SP����ӣ����ǲ���2·����YUV422_SP��оƬ�������Ʋ�֧�֣�
    ����ֵ˵��  : ���󷵻�VPSS_FAILURE������룻�ɹ�����VPSS_SUCCESS
-----------------------------------------------------------------------------*/
s32 VpssCapOpen(u32 dwCapId, TVpssCapParams *ptCapParams);

/*==============================================================================
    ������      : VpssCapClose
    ����        : �ر�ָ��CAP��
    �������˵��: dwCapId: CAP�ڵ�ID�ţ���: VPSS_CAP_INST_VIP0_PORTA
    ����ֵ˵��  : ���󷵻�VPSS_FAILURE������룻�ɹ�����VPSS_SUCCESS
-----------------------------------------------------------------------------*/
s32 VpssCapClose(u32 dwCapId);

/*==============================================================================
    ������      : VpssCapDequeue
    ����        : �Ӳɼ��ն�����ȡһ��buf�б�
    �������˵��:
    ����ֵ˵��  : ���󷵻�VPSS_FAILURE������룻�ɹ�����VPSS_SUCCESS
------------------------------------------------------------------------------*/
s32 VpssCapDequeue(u32 dwCapId, TVpssFrameList *ptFrameList, u32 dwStreamId, s32 nTimeout);

/*==============================================================================
    ������      : VpssCapQueue
    ����        : ����һ��buf�б��ɼ�����
    �������˵��:
    ����ֵ˵��  : ���󷵻�VPSS_FAILURE������룻�ɹ�����VPSS_SUCCESS
------------------------------------------------------------------------------*/
s32 VpssCapQueue(u32 dwCapId, TVpssFrameList *ptFrameList, u32 dwStreamId);

/*==============================================================================
    ������      : VpssCapCtrl
    ����        ���豸���ƣ�Ŀǰ������
                  ......
    �������˵����dwCapId: CAP�ڵ�ID�ţ���: VPSS_CAP_INST_VIP0_PORTA
                  nCmd: �����룻pArgs: ����ָ�� ���: VpssCapCtrl�����붨��
    ����ֵ˵��  : ���󷵻�VPSS_FAILURE������룻�ɹ�����VPSS_SUCCESS
------------------------------------------------------------------------------*/
s32 VpssCapCtrl(u32 dwCapId, s32 nCmd, void *pArgs);

/*==============================================================================
    ������      : VpssCapPrtStatus
    ����        ����ӡ״̬
    �������˵����dwCapId: CAP�ڵ�ID�ţ���: VPSS_CAP_INST_VIP0_PORTA
    ����ֵ˵��  : ���󷵻�VPSS_FAILURE������룻�ɹ�����VPSS_SUCCESS
------------------------------------------------------------------------------*/
s32 VpssCapPrtStatus(u32 dwCapId);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __VPSS_API_CAP_H */
