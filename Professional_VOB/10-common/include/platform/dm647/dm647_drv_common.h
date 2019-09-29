/******************************************************************************
ģ����  �� DM647_DRV
�ļ���  �� dm647_drv_common.h
����ļ��� 
�ļ�ʵ�ֹ��ܣ�
����    ���ŷ���
�汾    ��1.0.0.0.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
09/11/2008  1.0         �ŷ���      ����
06/08/2009  1.1         �ŷ���      ����CPU���ڴ�ʹ���ʹ��ܺ���
******************************************************************************/
#ifndef __DM647_DRV_COMMON_H
#define __DM647_DRV_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* runtime include files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "brdwrapperdef.h"                /* ʹ�õ�������ID�ź궨�� */
#include "algorithm/algorithmType.h"

/* �弶����ģ�鷵��ֵ����  */
#define DM647_DRV_SUCCESS                0                  /* �ɹ� */

#define DM647_DRV_ERR_BASE               0                  /* �������ֵ */
#define DM647_DRV_DEV_NOT_EXIST          (DM647_DRV_SUCCESS+1)  /* �豸������ */
#define DM647_DRV_DEV_NOT_OPEN           (DM647_DRV_SUCCESS+2)  /* �豸û�д� */
#define DM647_DRV_PARAM_ERR              (DM647_DRV_SUCCESS+3)  /* �����Ƿ� */
#define DM647_DRV_LENGTH_ERR             (DM647_DRV_SUCCESS+4)  /* ��Ϣ���ȴ��� */
#define DM647_DRV_QUEUE_FULL             (DM647_DRV_SUCCESS+5)  /* ���ݶ������� */
#define DM647_DRV_NOT_SUPPORT            (DM647_DRV_SUCCESS+6)  /* �豸��֧�ָò��� */
#define DM647_DRV_OPT_TIMEOUT            (DM647_DRV_SUCCESS+7)  /* ������ʱ */
#define DM647_DRV_NO_MEM                 (DM647_DRV_SUCCESS+8)  /* û�п����ڴ� */
#define DM647_DRV_DEV_BUSY               (DM647_DRV_SUCCESS+9)  /* �豸æ���Ѿ����� */
#define DM647_DRV_GIO_FAILE              (DM647_DRV_SUCCESS+10) /* GIO����ʧ�� */
#define DM647_DRV_FAILURE                -1                 /* δ֪���쳣ʧ�� */

/* �豸�����Ϣ
 */
typedef struct{
    u32 dwBrdID;                                    /* ʹ��brdwrapperdef.h�е�������ID�ź궨�� */
    u32 dwHwVer;                                    /* Ӳ���汾�� */
    u32 dwFpgaVer;                                  /* EPLD/FPGA/CPLD�ĳ���汾�� */
    u32 dwDspId;                                    /* ��ʶ��ǰ����һ��dsp����0��ʼ��� */
} TDm647DevInfo;


/* ---------------------------------------- ��Ƶ�������� ---------------------------------- */

/* ��Ƶ�ӿں궨�� */
#define VID_INTF_NONE                           0x00000000
#define VID_INTF_HDMI0                          0x00000001
#define VID_INTF_VGA0                           0x00000010
#define VID_INTF_YPbPr0                         0x00000100
#define VID_INTF_YPbPr1                         0x00000200
#define VID_INTF_SDI0                           0x00001000

#define VID_INTF_C0                             0x00010000
#define VID_INTF_C1                             0x00020000
#define VID_INTF_C2                             0x00040000
#define VID_INTF_C3                             0x00080000

#define VID_INTF_S0                             0x00100000
#define VID_INTF_S1                             0x00200000
#define VID_INTF_S2                             0x00400000
#define VID_INTF_S3                             0x00800000

#define VID_INTF_HDMI                           0x0000000f
#define VID_INTF_VGA                            0x000000f0
#define VID_INTF_YPbPr                          0x00000f00
#define VID_INTF_SDI                            0x0000f000
#define VID_INTF_C                              0x000f0000
#define VID_INTF_S                              0x00f00000

/* ��ƵԴ�ź���Ϣ�ṹ����
    720P60          = 1280*720  Progressive 60fps
    1080i60         = 1920*1080 interlace   30fps(60��)
    1080P30         = 1920*1080 Progressive 30fps
    D1(PAL)         = 720*576   interlace   25fps(50��)
    D1(NTSC)        = 720*480   interlace   30fps(60��)
    VGA60/75/85     = 640*480   Progressive 60/75/85fps
    SVGA60/75/85    = 800*600   Progressive 60/75/85fps
    XGA60/75/85     = 1024*768  Progressive 60/75/85fps
    SXGA60/75/85    = 1280*1024 Progressive 60/75/85fps
 */
typedef struct{
    u32	    dwWidth;                                /* ��Ƶ������Ϊ��λ,Ϊ0��ʾ���ź� */
    u32	    dwHeight;                               /* ��Ƶ�ߣ���Ϊ��λ,Ϊ0��ʾ���ź� */
    BOOL    bProgressive;                           /* ���л���У�TRUE=���У�FALSE=���� */
    u32     dwFrameRate;                            /* ֡�ʣ�����ʱ=��Ƶ������ʱ=��Ƶ/2����60i=30P, Ϊ0��ʾ���ź�
                                                       ���ֵ����1000������Ϊ����С�����3λ����59940��ʾ59.940Hz
                                                       ���õ���60/1.001=59.940; 24/1.001=23.976; 30/1.001=29.970 */
    u32     dwColorSpace;                           /* ���brdwrapperdef.h: ��Ƶ��ʽ���붨�� */
} TVidInfo;


/* -------------------------------------֡���������ṹ����------------------------------------- */

/*  ����֡Buf�ṹ Interlaced frame.
 *  Interlaced frame has two fields in one frame */
typedef struct {
    u8* pbyY1;                                      /**< Character pointer for field 1 Y data */
    u8* pbyCb1;                                     /**< Character pointer for field 1 CB data */
    u8* pbyCr1;                                     /**< Character pointer for field 1 CR data */

    u8* pbyY2;                                      /**< Character pointer for field 2 Y data */
    u8* pbyCb2;                                     /**< Character pointer for field 2 CB data */
    u8* pbyCr2;                                     /**< Character pointer for field 2 CR data */
} TDM647_IFrame;

/* ����֡Buf�ṹ Progressive Frame */
typedef struct {
    u8* pbyY;                                       /**< Character pointer for frame Y data */
    u8* pbyCb;                                      /**< Character pointer for frame CB data */
    u8* pbyCr;                                      /**< Character pointer for frame CR data */
} TDM647_PFrame;

/**
 *  ���ݴ�Ÿ�ʽ����
 */
typedef enum {
    VIDFMT_YCbCr422_INTERLEAVED = 0,                  /* ��ӦUYVY��ʽ����DM64xxϵ��֧�� */
    VIDFMT_YCbCr422_PLANAR,                           /* YUV���ݷֿ���ţ���DM64xϵ��֧�� */
    VIDFMT_YCrCb422_INTERLEAVED,                      /* ��ӦVYUY��ʽ����DM64xxϵ��֧�� */
    VIDFMT_RGB_888_INTERLEAVED,
    VIDFMT_RGB565_INTERLEAVED,
    VIDFMT_DVD_MODE,
    VIDFMT_CLUT_INDEXED,
    VIDFMT_ATTRIBUTE,
    VIDFMT_BAYER_PATTERN,
    VIDFMT_RAW_FORMAT,
    VIDFMT_COLORFORMAT_INVALID = -1
} TDM647_ColorFormat;

typedef struct{
    u32	    dwFBufId;                   /* ֡BUF�������ţ������ڲ�ʹ�ã��û������޸� */
    u8 *    pbyFBuf;                    /* ֡BUF��ָ�룬ָ��֡����Buf��
                                            �û�����BufDescʱ�����NULL�Ļ������Զ�����1������BUF������ʹ���û�ָ���ĵ�ַ��Ϊ��Ƶ����BUF��
                                            !!! ������û����䣬
                                                1���û����뱣֤Buf�Ķ��룬����ʼ��ַ������128�ֽڶ���;
                                                ����BUF��Сʱ��Ƶ���չ�ʽ��round_32(wWidth*bitPerPixel/8)*wHeight��
                                                ����OSD���Բ��豸bitPerPixel=4������ȫΪ16��
                                                2���ر��豸ʱ���������ͷ���Щ�ڴ� */
    BOOL    bUseCache;                  /* �������û�����Buf��Ч�������Զ������Ϊ��cache�ģ�
                                           ΪTRUE��ʾ�û������Buf��cache��������������ˢcache����
                                           ΪFALSEΪ����cache�ģ���������ˢcache���� */
    u32	    dwTimeStamp;                /* ֡��ʱ������ɼ�ʱ�û����Զ�ȡ��ǰ֡��ʱ��� */
} TFBufDesc;

typedef struct{
    u32	    dwFBufId;                               /* ֡BUF�������ţ������ڲ�ʹ�ã��û������޸� */

    TDM647_ColorFormat   tFrameFmt;                 /* ֡���ݴ�Ÿ�ʽ��64xֻ֧��VIDFMT_YCbCr422_PLANAR */

    union {
        void            *pFrameBufferPtr;           /* ���ݴ�Ÿ�ʽΪ *_INTERLEAVED ʱ֡���ݵ�ָ��
                                                       �û�����BufDescʱ�����NULL�Ļ������Զ�����1������BUF��
                                                       ����ʹ�ø��û�ָ���ĵ�ַ��Ϊ��Ƶ����BUF��
                                                        !!! ������û����䣬
                                                        1���û����뱣֤Buf�Ķ��룬����ʼ��ַ������256�ֽڶ���;
                                                           ����BUF��Сʱ��Ƶ���չ�ʽ��round_32(dwWidth*bitPerPixel/8)*dwHeight��
                                                           ����DM64xx��OSD���Բ��豸bitPerPixel=4������ȫΪ16��
                                                        2���ر��豸ʱ���������ͷ���Щ�ڴ� */
        TDM647_IFrame    tIFrame;                   /* ���ݴ�Ÿ�ʽΪ *_PLANAR ʱ�Ҹ��з���ż���������ʱ�ø�ָ��  */
        TDM647_PFrame    tPFrame;                   /* ���ݴ�Ÿ�ʽΪ *_PLANAR ʱ�Ҹ�����ż����֯Ϊһ֡�����е�֡���ʱ�ø�ָ�� */
    } tFrame;

    BOOL    bUseCache;                  /* �������û�����Buf��Ч�������Զ������Ϊ��cache�ģ�
                                           ΪTRUE��ʾ�û������Buf��cache��������������ˢcache����
                                           ΪFALSEΪ����cache�ģ���������ˢcache���� */
    u32	    dwTimeStamp;                /* ֡��ʱ������ɼ�ʱ�û����Զ�ȡ��ǰ֡��ʱ��� */
    u32	    dwUserParam;                /* �û����� */
} TDM647FBufDesc;


/* -------------------------------------DSP/BIOSϵͳ��ؽṹ����------------------------------------- */
/* �ڴ�ͳ����Ϣ
 */
typedef struct{
    u32   dwTotal;              /* original size of segment */
    u32   dwUsed;               /* number of bytes used in segment */
    u32   dwFreeBlkMax;         /* length of largest contiguous block */
} TDm647MemStat;

/*==============================================================================
    ������      : Dm647DrvSetup
    ����        ��Dm647����ע�ᰲװ���ú�������ָ���İ����豸�š�Ӳ���汾�ź��߼�
                  оƬEPLD/FPGA/CPLD�ĳ���汾������ʼ���ض������裬�Է��㲻ͬ�豸
                  ����ͬ�豸��ͬӲ���汾֮��ļ��ݡ�
                      ע�⣺�ú���������ʹ������Ƶ����������֮ǰ����!
    �������˵����ptDevInfo���豸��Ϣ
                  ptDevInfo->dwBrdID: ʹ��brdwrapperdef.h�е�������ID�ź궨�壻
                  ptDevInfo->dwHwVer: Ӳ���汾��,��HOST�����ͨ����Ӧ�ĺ�����ȡ�������ֻ��
                  1��Ӳ���汾��������0����Ϊ���������жϴ���
                  ptDevInfo->dwFpgaVer: EPLD/FPGA/CPLD�ĳ���汾��, ��ʱӲ���汾�Ų��ģ�����
                  ���߼�оƬ�ĳ�����ʵ�ֲ�ͬ�Ĺ��ܣ��û���HOST�����ͨ����Ӧ�ĺ���
                  ��ȡ���ð汾�����ֻ��1���汾��汾�޸Ĳ�Ӱ��������Դ�ĸĶ��û�
                  ������0����Ϊ���������жϴ���
                  ptDevInfo->dwDspId: ��ʶ��ǰ����һ��dsp����0��ʼ��ţ����ڶ��dsp�����ʱ��
                  ��Ҫ�����ǰ�������һ��dspоƬ����Ҫ����Դ���
    ����ֵ˵��  �����󷵻�DM647_DRV_FAILURE������룻�ɹ�����DM647_DRV_SUCCESS
------------------------------------------------------------------------------*/
l32 Dm647DrvSetup(TDm647DevInfo *ptDevInfo);

/*==============================================================================
    ������      : Dm647DevInfoGet
    ����        ����ѯDm647�����豸�������Ϣ
    �������˵������
    ����ֵ˵��  �����󷵻�NULL���ɹ����ش���豸�����Ϣ��ָ��
------------------------------------------------------------------------------*/
TDm647DevInfo * Dm647DevInfoGet(void);

/*==============================================================================
    ������      : Dm647GetMemStat
    ����        ����ѯDDR2�ڴ�
    �������˵����nSegId��memory segment identifier
                  ptMemStat: ���ص��ڴ�ͳ����Ϣ��
    ����ֵ˵��  �����󷵻�DM647_DRV_FAILURE������룻�ɹ�����DM647_DRV_SUCCESS
------------------------------------------------------------------------------*/
l32 Dm647GetMemStat(l32 nSegId, TDm647MemStat *ptMemStat);

/*==============================================================================
    ������      : Dm647GetCpuLoad
    ����        ����ѯDSP��ʹ���ʰٷֱȣ�Ҫʹ�øù��ܣ���Ҫ����������������:
                    1����tcf�ļ���import��ص�load.tci
                    2����main�����е���Load_init()������ʼ��������ԭ�ͣ�
                        extern Void Load_init(void);
                      ! ע��cpp�ļ�����ʱ����extern "C"��
    �������˵������
    ����ֵ˵��  �����󷵻�DM647_DRV_FAILURE���ɹ�����ʹ���ʰٷֱ�
------------------------------------------------------------------------------*/
l32 Dm647GetCpuLoad(void);


#ifdef __cplusplus 
} 
#endif /* __cplusplus */

#endif /* __DM647_DRV_COMMON_H */
