/******************************************************************************
ģ����  �� VPSS_DRV_API
�ļ���  �� vpss_api_core.h
����ļ��� vpss_api_core.c
�ļ�ʵ�ֹ��ܣ�
����    ���ŷ���
�汾    ��1.0.0.0.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
03/29/2011  1.0         �ŷ���      ����
******************************************************************************/
#ifndef __VPSS_API_CORE_H
#define __VPSS_API_CORE_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/****************************** ģ��İ汾�������涨 *************************
�ܵĽṹ��mn.mm.ii.cc.tttt
     ��  Osp 1.1.7.20040318 ��ʾ
ģ������Osp
ģ��1�汾
�ӿ�1�汾
ʵ��7�汾
04��3��18���ύ

�汾�޸ļ�¼��
----------------------------------------------------------------------------
ģ��汾: VpssDrvApi 1.1.1.20110329
���ӹ���: ����
�޸�ȱ��: ��
�ύ��:   �ŷ���

****************************************************************************/

#include "kdvtype.h"
#include "vpss_api_def.h"
#include "brdwrapperdef.h"

/* �汾��Ϣ */
#define VPSSDRV_MOD_VERSION             ( const char * )"VpssDrvApi 1.1.1.20110329"


/* ����ֵ�궨�� */
#define VPSS_SUCCESS                    0           /* �ɹ� */
#define VPSS_SMEM_CORRUPT               1           /* �����ڴ������ƻ� */
#define VPSS_LENGTH_ERROR               2           /* ���ȴ��� */
#define VPSS_QUEUE_FULL                 3           /* �������� */
#define VPSS_QUEUE_EMPTY                4           /* ���п� */
#define VPSS_MSG_LOST                   5           /* ��Ϣ��ʧ */
#define VPSS_PARAM_ERR                  6           /* �������� */
#define VPSS_NOT_SUPPORT                7           /* ��֧�ֵĲ��� */
#define VPSS_MULTI_OPEN                 8           /* ��δ��豸 */
#define VPSS_NOT_OPEN                   9           /* �豸û�д� */
#define VPSS_TIMEOUT                    10          /* ������ʱ */
#define VPSS_OPEN_FAIL                  11          /* �豸��ʧ�� */
#define VPSS_IOC_FAIL                   12          /* �豸ioctlʧ�� */
#define VPSS_NO_MEM                     13          /* �ڴ治�� */
#define VPSS_MEM_ERR                    14          /* �ڴ���� */
#define vpss_DEL_FAIL                   15          /* �豸ɾ��ʧ��*/
#define VPSS_FAILURE                    -1          /* δ֪���� */

/* ���ü��޺궨�� */
#define VPSS_MAX_FRAMES_PER_LIST        (64u)       /* ÿ�������֧�ֵ�֡�� */
#define VPSS_MAX_PLANES                 (3u)        /* ���3�����ݣ���YUV planar format - Y, Cb and Cr */
#define VPSS_MAX_FIELDS                 (2u)        /* ���2�� */

#define VPSS_MAX_IN_OUT_PROCESS_LISTS   (4u)

/* dwFid ���� */
#define VPSS_FID_TOP                    0           /* top field */
#define VPSS_FID_BOTTOM                 1           /* Bottom field */
#define VPSS_FID_FRAME                  2           /* Frame mode - Contains both the fields or a progressive frame. */

/* ��Ƶ��ʽ���붨�� */
#define VPSS_VID_STD_MASK_EMBSYNC       0x80000000  /* ͬ��ģʽ���룬1=����ͬ����0=��ͬ�� */
#define VPSS_VID_STD_MASK_SD_16BIT      0x40000000  /* ����ֱ��ʲ���16λ��ʽ�����־�����576i/480i */
#define VPSS_VID_STD_MASK_COLORSPACE    0x000000ff  /* ɫ�ȿռ����룬���ɫ�ȿռ䶨�壬ռ�õ�8λ */
#define VPSS_VID_STD_MASK_CAPMODE       0x000f0000  /* �ɼ�ģʽ���룬���: �ɼ�ģʽ���� */
#define VPSS_VID_STD_MASK_INTF_MODE     0x00f00000  /* �ӿ�ģʽ�����: �ӿ�ģʽ���� */

/* ɫ�ȿռ䶨�� */
#define VPSS_VID_COLORSPACE_YUV422          0       /* YUV422��ʽ */
#define VPSS_VID_COLORSPACE_RGB888          1       /* RGB888��ʽ */
#define VPSS_VID_COLORSPACE_RGB444          2       /* RGB444��ʽ */
#define VPSS_VID_COLORSPACE_RAW16BIT        3       /* 16λ�����ݸ�ʽ */
#define VPSS_VID_COLORSPACE_RGB565          4       /* RGB565��ʽ */
#define VPSS_VID_COLORSPACE_YUV422I_YUYV    5       /* 16λYUV422I_YUYV��ʽ */
#define VPSS_VID_COLORSPACE_YUV422SP_UV     6       /* 16λYUV 422 Semi-Planar - Y separate, UV interleaved. */
#define VPSS_VID_COLORSPACE_YUV420SP_UV     7       /* 12λYUV 420 Semi-Planar - Y separate, UV interleaved. */
#define VPSS_VID_COLORSPACE_YUV444          8       /* YUV444��ʽ */

/* �ɼ�ģʽ���� */
#define VPSS_VID_CAPMODE_SINGLE_CH_NON_MUX_EMBEDDED_SYNC        0 /* Single Channel non multiplexed mode */
#define VPSS_VID_CAPMODE_MULTI_CH_LINE_MUX_EMBEDDED_SYNC        1 /* Multi-channel line-multiplexed mode */
#define VPSS_VID_CAPMODE_MULTI_CH_PIXEL_MUX_EMBEDDED_SYNC       2 /* Multi-channel pixel muxed */
#define VPSS_VID_CAPMODE_SINGLE_CH_NON_MUX_DISSYNC_HSYNC_VBLK   3 /* Single Channel non multiplexed
                                                                   discrete sync mode with HSYNC and
                                                                   VBLK as control signals. */
#define VPSS_VID_CAPMODE_SINGLE_CH_NON_MUX_DISSYNC_HSYNC_VSYNC  4 /**< Single Channel non multiplexed
                                                                    discrete sync mode with HSYNC and
                                                                    VSYNC as control signals. */
#define VPSS_VID_CAPMODE_SINGLE_CH_NON_MUX_DISSYNC_ACTVID_VBLK  5 /* Single Channel non multiplexed
                                                                    discrete sync mode with ACTVID and
                                                                    VBLK as control signals. */
#define VPSS_VID_CAPMODE_SINGLE_CH_NON_MUX_DISSYNC_ACTVID_VSYNC 6 /* Single Channel non multiplexed
                                                                    discrete sync mode with ACTVID and
                                                                    VBLK as control signals. */
#define VPSS_VID_CAPMODE_MULTI_CH_LINE_MUX_SPLIT_LINE_EMBEDDED_SYNC 7 /* Multi-channel line-multiplexed mode - split line mode */

/* �ӿ�ģʽ���� */
#define VPSS_VID_IF_MODE_AUTO               0   /* ���������ݷֱ�������Ĭ�ϵĽӿ�ģʽ  */
#define VPSS_VID_IF_MODE_8BIT               1   /* 8bit - BT656 standard  */
#define VPSS_VID_IF_MODE_16BIT              2   /* 16bit - BT1120 standard  */
#define VPSS_VID_IF_MODE_24BIT              3   /* 24bit */

/* dwMemType ���� */
#define VPSS_VPDMA_MT_NONTILEDMEM           0       /* 1D non-tiled memory. */
#define VPSS_VPDMA_MT_TILEDMEM              1       /* 2D tiled memory. */

/* ���Ͷ��� */
typedef void * HVpssHandle;                         /* ͨ�þ������ */

/* �豸�����Ϣ */
typedef struct{
    u32 dwBrdID;         /* ʹ��brdwrapperdef.h�е�������ID�ź궨�� */
    u32 dwHwVer;         /* Ӳ���汾�� */
    u32 dwFpgaVer;       /* EPLD/FPGA/CPLD�ĳ���汾�� */
    u32 dwDspId;         /* ��ʶ��ǰ����һ��dsp����0��ʼ��� */
} TVpssDevInfo;

/* �ṹ���� */
/* ��Ƶ��ʽ�ṹ���� */
typedef struct{
    u32	    dwWidth;                    /* ��Ƶ������Ϊ��λ,Ϊ0��ʾ���ź� */
    u32	    dwHeight;                   /* ��Ƶ�ߣ���Ϊ��λ,Ϊ0��ʾ���ź� */
    BOOL32  bProgressive;               /* ���л���У�TRUE=���У�FALSE=���� */
    u32     dwFrameRate;                /* ֡�ʣ�����ʱ=��Ƶ������ʱ=��Ƶ/2����60i=30P, Ϊ0��ʾ���ź�
                                           ���ֵ����1000������Ϊ����С�����3λ����59940��ʾ59.940Hz
                                           ���õ���60/1.001=59.940; 24/1.001=23.976; 30/1.001=29.970 */
    u32     dwColorSpace;               /* ���: ��Ƶ��ʽ���붨�� */
} TVpssVidStd;

/* ÿ֡��������Ϣ�ṹ */
typedef struct
{
    /**<
         FVID2 buffer pointers for supporting multiple addresses like
         Y, U, V etc for a given frame. The interpretation of these pointers
         depend on the format configured for the driver.
         The first dimension represents the field and the second dimension
         represents the color plane.
         Not all pointers are valid for a given format.

         Representation of YUV422 Planar Buffer:
         Field 0 Y -> addr[0][0], Field 1 Y -> addr[1][0]
         Field 0 U -> addr[0][1], Field 1 U -> addr[1][1]
         Field 0 V -> addr[0][2], Field 1 V -> addr[1][2]
         Other pointers are not valid.

         Representation of YUV422 Interleaved Buffer:
         Field 0 YUV -> addr[0][0], Field 1 YUV -> addr[1][0]
         Other pointers are not valid.

         Representation of YUV420SP or YUV422SP Buffer:
         Field 0 Y  -> addr[0][0], Field 1 Y  -> addr[1][0]
         Field 0 UV -> addr[0][1], Field 1 UV -> addr[1][1]
         Other pointers are not valid.

         Representation of RGB888 Buffer
         Field 0 RGB -> addr[0][0], Field 1 RGB -> addr[1][0],
         Other pointers are not valid.

         For progressive mode data formats
         or when fields are processed by driver in frame mode.
         addr[1][x] is not used.

         Instead of using numerical for accessing the buffers, the application
         can use the macros defined for each buffer formats like
         FVID2_YUV_INT_ADDR_IDX, FVID2_RGB_ADDR_IDX, FVID2_FID_TOP etc. */
    void   *pbyVirtAddr[VPSS_MAX_FIELDS][VPSS_MAX_PLANES];  /* ֡���ݵ������ַ,�����÷������������ */
    u32     adwPhyAddr[VPSS_MAX_FIELDS][VPSS_MAX_PLANES];   /* ֡���ݵ������ַ,������DMA���� */
    u32     dwColorSpace;   /* ��Ƶ����ɫ�ȿռ䣬��: ɫ�ȿռ䶨�� */

    u32     dwMemType;      /* VPSS_VPDMA_MT_NONTILEDMEM,VPSS_VPDMA_MT_TILEDMEM */
    u32     dwImgWidth;     /* ͼ��Ŀ�� */
    u32     dwImgHight;     /* ͼ��ĸ߶� */
    u32     dwImgPitch[VPSS_MAX_PLANES];  /* ͼ���һ��ռ�õ��ֽ���,�����3������Y=0, U=1, V=2; Y_UV:Y=0,UV=1; YUYV/RGBֻ��[0] */
    u32     dwImgSize;      /* һ֡ͼ���ռ�õ��ֽ��� */

    u32     dwFid;          /* ����ʶ,��: VPSS_FID_FRAME */
    u32     dwChannelId;    /* ��Ӧ��ͨ���� */
    u32     dwTimeStamp;    /* ʱ���, ����Ϊ��λ */
    void    *pDrvData;      /* ����˽�����ݣ��û������޸� */
    void    *pReserved;     /* ���� */
} TVpssFrame;

typedef struct
{
    u32         dwNumFrames;    /* ʵ���ж����ӻ����֡���� */
    TVpssFrame  atFrame[VPSS_MAX_FRAMES_PER_LIST];  /* ÿ���ӻ����֡���� */

    void        *pDrvData;      /* �����ڲ�ʹ�õ�˽�����ݣ��û������޸� */
    void        *pAppData;      /* Ŀǰû��ʵ��! �û�ʹ�õ�˽�����ݣ��������޸� */
} TVpssFrameList;

typedef struct
{
    TVpssFrameList  *ptInFrameList[VPSS_MAX_IN_OUT_PROCESS_LISTS];
    TVpssFrameList  *ptOutFrameList[VPSS_MAX_IN_OUT_PROCESS_LISTS];
    u32              dwNumInLists;  /* Number of input frame lists */
    u32              dwNumOutLists; /* Number of output frame lists */
    void            *pbyDrvData;    /* ����˽�����ݣ��û������޸� */
    void            *pbyReserved;   /* reserved */
} TVpssProcessList;


/* �������� */
/*==============================================================================
    ������      : VpssOpen
    ����        : ��VPSSģ�鲢��ʼ��
    �������˵��: ��
    ����ֵ˵��  : ���󷵻�VPSS_FAILURE������룻�ɹ�����VPSS_SUCCESS
------------------------------------------------------------------------------*/
s32 VpssOpen(TVpssDevInfo *ptVpssDevInfo);

/*==============================================================================
    ������      : VpssClose
    ����        : �ر�VPSSģ�鲢�ͷ���Դ
    �������˵��: ��
    ����ֵ˵��  : ���󷵻�VPSS_FAILURE������룻�ɹ�����VPSS_SUCCESS
------------------------------------------------------------------------------*/
s32 VpssClose(TVpssDevInfo *ptVpssDevInfo);

/*==============================================================================
    ������      : VpssFbufAlloc
    ����        : ����֡buf���ӹ����ڴ��з��䣬���Ա���˷���
    �������˵��: ��
    ����ֵ˵��  : ���󷵻�VPSS_FAILURE������룻�ɹ�����VPSS_SUCCESS
------------------------------------------------------------------------------*/
void *VpssFbufAlloc(u32 dwSize, u32 *pdwPhyAddr);

/*==============================================================================
    ������      : VpssFbufFree
    ����        : �ͷ�֡buf
    �������˵��: ��
    ����ֵ˵��  : ���󷵻�VPSS_FAILURE������룻�ɹ�����VPSS_SUCCESS
------------------------------------------------------------------------------*/
s32 VpssFbufFree(u32 dwPhyAddr, void *pbyVirAddr, u32 dwSize);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __VPSS_API_CORE_H */
