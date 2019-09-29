/******************************************************************************
ģ����  �� DM6437_DRV
�ļ���  �� dm6437_drv_common.h
����ļ��� 
�ļ�ʵ�ֹ��ܣ�
����    ���ŷ���
�汾    ��1.0.0.0.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
04/22/2008  1.0         �ŷ���      ����
06/08/2009  1.1         �ŷ���      ����CPU���ڴ�ʹ���ʹ��ܺ���
******************************************************************************/
#ifndef __DM6437_DRV_COMMON_H
#define __DM6437_DRV_COMMON_H

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
#define DM6437_DRV_SUCCESS                0                  /* �ɹ� */

#define DM6437_DRV_ERR_BASE               0                  /* �������ֵ */
#define DM6437_DRV_DEV_NOT_EXIST          (DM6437_DRV_SUCCESS+1)  /* �豸������ */
#define DM6437_DRV_DEV_NOT_OPEN           (DM6437_DRV_SUCCESS+2)  /* �豸û�д� */
#define DM6437_DRV_PARAM_ERR              (DM6437_DRV_SUCCESS+3)  /* �����Ƿ� */
#define DM6437_DRV_LENGTH_ERR             (DM6437_DRV_SUCCESS+4)  /* ��Ϣ���ȴ��� */
#define DM6437_DRV_QUEUE_FULL             (DM6437_DRV_SUCCESS+5)  /* ���ݶ������� */
#define DM6437_DRV_NOT_SUPPORT            (DM6437_DRV_SUCCESS+6)  /* �豸��֧�ָò��� */
#define DM6437_DRV_OPT_TIMEOUT            (DM6437_DRV_SUCCESS+7)  /* ������ʱ */
#define DM6437_DRV_NO_MEM                 (DM6437_DRV_SUCCESS+8)  /* û�п����ڴ� */
#define DM6437_DRV_DEV_BUSY               (DM6437_DRV_SUCCESS+9)  /* �豸æ���Ѿ����� */
#define DM6437_DRV_GIO_FAILE              (DM6437_DRV_SUCCESS+10) /* GIO����ʧ�� */
#define DM6437_DRV_FAILURE                -1                 /* δ֪���쳣ʧ�� */

/* �豸�����Ϣ
 */
typedef struct{
    u32 dwBrdID;        /* ʹ��brdwrapperdef.h�е�������ID�ź궨�� */
    u32 dwHwVer;        /* Ӳ���汾�� */
    u32 dwFpgaVer;      /* EPLD/FPGA/CPLD�ĳ���汾�� */
    u32 dwDspId;        /* ��ʶ��ǰ����һ��dsp����0��ʼ��� */
} TDm6437DevInfo;


/* ---------------------------------------- ��Ƶ�������� ---------------------------------- */

/* ��Ƶ�ӿں궨�� */
#define VID_INTF_NONE                           0x00000000
#define VID_INTF_HDMI0                          0x00000001
#define VID_INTF_VGA0                           0x00000010
#define VID_INTF_YPbPr0                         0x00000100
#define VID_INTF_YPbPr1                         0x00000200
#define VID_INTF_SDI0                           0x00001000
#define VID_INTF_DVI0                           0x01000000

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
#define VID_INIF_DVI                            0x0f000000

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
    u16	    wWidth;                     /* ��Ƶ������Ϊ��λ,Ϊ0��ʾ���ź� */
    u16	    wHeight;                    /* ��Ƶ�ߣ���Ϊ��λ,Ϊ0��ʾ���ź� */
    BOOL    bProgressive;               /* ���л���У�TRUE=���У�FALSE=���� */
    u32     dwFrameRate;                /* ֡�ʣ�����ʱ=��Ƶ������ʱ=��Ƶ/2����60i=30P,Ϊ0��ʾ���ź� */
    u32     dwColorSpace;               /* ���brdwrapperdef.h: ��Ƶ��ʽ���붨�� */
} TVidInfo;

/* ֡���������ṹ���� */
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


/* -------------------------------------DSP/BIOSϵͳ��ؽṹ����------------------------------------- */
/* �ڴ�ͳ����Ϣ
 */
typedef struct{
    u32   dwTotal;              /* original size of segment */
    u32   dwUsed;               /* number of bytes used in segment */
    u32   dwFreeBlkMax;         /* length of largest contiguous block */
} TDm6437MemStat;


/*==============================================================================
    ������      : Dm6437DrvSetup
    ����        ��Dm6437����ע�ᰲװ���ú�������ָ���İ����豸�š�Ӳ���汾�ź��߼�
                  оƬEPLD/FPGA/CPLD�ĳ���汾������ʼ���ض������裬�Է��㲻ͬ�豸
                  ����ͬ�豸��ͬӲ���汾֮��ļ��ݡ�
                      ע�⣺�ú��ٱ�����ʹ������Ƶ����������֮ǰ����!
    �������˵����dwBrdID: ʹ��brdwrapperdef.h�е�������ID�ź궨�壻
                  dwHwVer: Ӳ���汾��,��HOST�����ͨ����Ӧ�ĺ�����ȡ�������ֻ��
                  1��Ӳ���汾��������0����Ϊ���������жϴ���
                  dwFpgaVer: EPLD/FPGA/CPLD�ĳ���汾��, ��ʱӲ���汾�Ų��ģ�����
                  ���߼�оƬ�ĳ�����ʵ�ֲ�ͬ�Ĺ��ܣ��û���HOST�����ͨ����Ӧ�ĺ���
                  ��ȡ���ð汾�����ֻ��1���汾��汾�޸Ĳ�Ӱ��������Դ�ĸĶ��û�
                  ������0����Ϊ���������жϴ���
                  dwDspId: ��ʶ��ǰ����һ��dsp����0��ʼ��ţ����ڶ��dsp�����ʱ��
                  ��Ҫ�����ǰ�������һ��dspоƬ����Ҫ����Դ���
    ����ֵ˵��  �����󷵻�DM6437_DRV_FAILURE������룻�ɹ�����DM6437_DRV_SUCCESS
------------------------------------------------------------------------------*/
l32 Dm6437DrvSetup(u32 dwBrdID, u32 dwHwVer, u32 dwFpgaVer, u32 dwDspId);

/*==============================================================================
    ������      : Dm6437DevInfoGet
    ����        ����ѯDm6437�����豸�������Ϣ
    �������˵������
    ����ֵ˵��  �����󷵻�NULL���ɹ����ش���豸�����Ϣ��ָ��
------------------------------------------------------------------------------*/
TDm6437DevInfo * Dm6437DevInfoGet(void);

/*==============================================================================
    ������      : Dm6437GetMemStat
    ����        ����ѯDDR2�ڴ�
    �������˵����nSegId��memory segment identifier
                  ptMemStat: ���ص��ڴ�ͳ����Ϣ��
    ����ֵ˵��  �����󷵻�DM6437_DRV_FAILURE������룻�ɹ�����DM6437_DRV_SUCCESS
------------------------------------------------------------------------------*/
l32 Dm6437GetMemStat(l32 nSegId, TDm6437MemStat *ptMemStat);

/*==============================================================================
    ������      : Dm6437GetCpuLoad
    ����        ����ѯDSP��ʹ���ʰٷֱȣ�Ҫʹ�øù��ܣ���Ҫ����������������:
                    1����tcf�ļ���import��ص�load.tci
                    2����main�����е���Load_init()������ʼ��������ԭ�ͣ�
                        extern Void Load_init(void);
                      ! ע��cpp�ļ�����ʱ����extern "C"��
    �������˵������
    ����ֵ˵��  �����󷵻�DM6437_DRV_FAILURE���ɹ�����ʹ���ʰٷֱ�
------------------------------------------------------------------------------*/
l32 Dm6437GetCpuLoad(void);


#ifdef __cplusplus 
} 
#endif /* __cplusplus */

#endif /* __DM6437_DRV_COMMON_H */
