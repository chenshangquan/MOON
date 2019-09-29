/******************************************************************************
ģ����  �� DM6437_RESIZER_DRV
�ļ���  �� dm6437_resizer_api.h
����ļ��� dm6437_resizer_api.c
�ļ�ʵ�ֹ��ܣ�
����    ���ŷ���
�汾    ��1.0.0.0.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
04/22/2008  1.0         �ŷ���      ����
******************************************************************************/
#ifndef __DM6437_RESIZER_API_H
#define __DM6437_RESIZER_API_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* runtime include files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "dm6437_drv_common.h"

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
ģ��汾��DM6437_RESIZER_DRV 1.1.1.20080602
���ӹ��ܣ�����
�޸�ȱ�ݣ���
�ύ�ˣ��ŷ���

****************************************************************************/
/* �汾�Ŷ��� */
#define VER_DM6437_RESIZER_DRV         (const s8*)"DM6437_RESIZER_DRV 1.1.1.20080602" 


/* ����ֵ���� */
#define DM6437_RESIZER_NUM_CHANNELS       (16u)     /* һ��DM6437�������Դ���16��RESIZERͨ��,
                                                       ÿ��ͨ��֧��һ��resizeģʽ */

/* Dm6437ResizerCtrl�����붨�� */

/* ���Ͷ��� */
typedef void * HDm6437ResizerChnl;


/* ��ƵRESIZER�豸ͨ�������Ĳ����ṹ���� */
typedef struct{
    u16	    wWidthIn;                       /* ����ͼ�������Ϊ��λ */
    u16	    wHeightIn;                      /* ����ͼ��ߣ���Ϊ��λ */
    u16	    wWidthOut;                      /* ���ͼ�������Ϊ��λ */
    u16	    wHeightOut;                     /* ���ͼ��ߣ���Ϊ��λ */
} TDm6437ResizerChnlParam;

/* ��ƵRESIZER��������ṹ���� */
typedef struct{
    void    *pInBuf;                        /* ����ͼ���Bufָ��,������128Byte���룬Ҫ��ͼ�����ݸ�ʽΪ16λYUV422��UYVYͼ�� */
    u32	    dwInBufSize;                    /* ����ͼ���Buf�Ĵ�С */
    BOOL    bInUseCache;                    /* ΪTRUE��ʾ�����Buf��cache��������������ˢcache����
                                               ΪFALSEΪ����cache�ģ���������ˢcache���� */

    void    *pOutBuf;                       /* ���ͼ���Bufָ��,������128Byte���� */
    u32	    dwOutBufSize;                   /* ���ͼ���Buf�Ĵ�С */
    BOOL    bOutUseCache;                   /* ΪTRUE��ʾ�����Buf��cache��������������ˢcache����
                                               ΪFALSEΪ����cache�ģ���������ˢcache���� */
} TDm6437ResizeParam;


/*==============================================================================
    ������      : Dm6437ResizerChnlOpen
    ����        ����ƵRESIZER�豸ͨ����
    �������˵����dwChnlId: 0~DM6437_RESIZER_NUM_CHANNELS-1
                  ptParam: �򿪵Ĳ���
    ����ֵ˵��  �����󷵻�NULL���ɹ����ؿ��ƾ��
------------------------------------------------------------------------------*/
HDm6437ResizerChnl Dm6437ResizerChnlOpen(u32 dwChnlId, TDm6437ResizerChnlParam *ptParam);

/*==============================================================================
    ������      : Dm6437ResizerChnlClose
    ����        ����ƵRESIZER�豸ͨ���رա�
    �������˵����hResizerChnl: Dm6437ResizerOpen�������صľ��;
    ����ֵ˵��  �����󷵻�DM6437_DRV_FAILURE������룻�ɹ�����DM6437_DRV_SUCCESS
------------------------------------------------------------------------------*/
l32 Dm6437ResizerChnlClose(HDm6437ResizerChnl hResizerChnl);

/*==============================================================================
    ������      : Dm6437ResizerProcess
    ����        ��ȡһ����ƵRESIZER BUF���û����Զ�ε���ȡ���BUF��
    �������˵����hResizerChnl: ����Dm6437ResizerOpen�������صľ��;
                  ptParam: �û����䲢����ָ�룬������BUF��Ϣ�������û�
    ����ֵ˵��  �����󷵻�DM6437_DRV_FAILURE������룻�ɹ�����DM6437_DRV_SUCCESS
------------------------------------------------------------------------------*/
l32 Dm6437ResizerProcess(HDm6437ResizerChnl hResizerChnl, TDm6437ResizeParam *ptParam);

/*====================================================================
    ������      : Dm6437ResizerGetVer
    ����        ��ģ��汾�Ų�ѯ��
    �������˵����pchVer�� �����Ĵ�Ű汾��Ϣ��bufָ��
                  dwBufLen������buf�ĳ���
    ����ֵ˵��  ���汾��ʵ���ַ������ȡ�С��0Ϊ����;
                 ���ʵ���ַ������ȴ���dwBufLen����ֵΪ0
--------------------------------------------------------------------*/
l32 Dm6437ResizerGetVer(s8 *pchVer, u32 dwBufLen);

#ifdef __cplusplus 
} 
#endif /* __cplusplus */

#endif /* __DM6437_RESIZER_API_H */
