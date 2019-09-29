/******************************************************************************
ģ����  �� DM6437_AUDIO_DRV
�ļ���  �� dm6437_audio_api.h
����ļ��� dm6437_audio_api.c
�ļ�ʵ�ֹ��ܣ�
����    ���ŷ���
�汾    ��1.0.0.0.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
08/15/2007  1.0         �ŷ���      ����
04/22/2008  1.1         �ŷ���      �޸����Ͷ���ͷ�ļ����޸�ioctl���ͺ궨��
******************************************************************************/
#ifndef __DM6437_AUDIO_API_H
#define __DM6437_AUDIO_API_H

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
ģ��汾��DM6437_AUDIO_DRV 1.1.1.20080422
���ӹ��ܣ�����
�޸�ȱ�ݣ���
�ύ�ˣ��ŷ���
----------------------------------------------------------------------------
ģ��汾��DM6437_AUDIO_DRV 1.1.2.20080527
���ӹ��ܣ������Ƶ���open close���д������ʱ������Ƶ��������
�޸�ȱ�ݣ���
�ύ�ˣ��ŷ���
----------------------------------------------------------------------------
ģ��汾��DM6437_AUDIO_DRV 1.1.3.20080605
���ӹ��ܣ����release�汾��Ƶ��������������
�޸�ȱ�ݣ���
�ύ�ˣ��ŷ���
----------------------------------------------------------------------------
ģ��汾��DM6437_AUDIO_DRV 1.1.4.20100331
���ӹ��ܣ���
�޸�ȱ�ݣ������˰���128�ֽڷ���buffer�ڴ浼�³��������(cache����)
�ύ�ˣ��ճϽ�

****************************************************************************/
/* �汾�Ŷ��� */
#define VER_DM6437_AUDIO_DRV         (const s8*)"DM6437_AUDIO_DRV 1.1.4.20100331" 

/* �弶����ģ�鷵��ֵ����  */
#define DM6437_AUD_SUCCESS                0                  /* �ɹ� */

#define DM6437_AUD_ERR_BASE               0                  /* �������ֵ */
#define DM6437_AUD_DEV_NOT_EXIST          (DM6437_AUD_SUCCESS+1)  /* �豸������ */
#define DM6437_AUD_DEV_NOT_OPEN           (DM6437_AUD_SUCCESS+2)  /* �豸û�д� */
#define DM6437_AUD_PARAM_ERR              (DM6437_AUD_SUCCESS+3)  /* �����Ƿ� */
#define DM6437_AUD_LENGTH_ERR             (DM6437_AUD_SUCCESS+4)  /* ��Ϣ���ȴ��� */
#define DM6437_AUD_QUEUE_FULL             (DM6437_AUD_SUCCESS+5)  /* ���ݶ������� */
#define DM6437_AUD_NOT_SUPPORT            (DM6437_AUD_SUCCESS+6)  /* �豸��֧�ָò��� */
#define DM6437_AUD_OPT_TIMEOUT            (DM6437_AUD_SUCCESS+7)  /* ������ʱ */
#define DM6437_AUD_NO_MEM                 (DM6437_AUD_SUCCESS+8)  /* û�п����ڴ� */
#define DM6437_AUD_DEV_BUSY               (DM6437_AUD_SUCCESS+9)  /* �豸æ���Ѿ����� */
#define DM6437_AUD_GIO_FAILE              (DM6437_AUD_SUCCESS+10) /* GIO����ʧ�� */
#define DM6437_AUD_FAILURE                -1                 /* δ֪���쳣ʧ�� */

/* ����ֵ���� */
#define DM6437_AUD_DEV_MAX_NUM             2              /* Ŀǰһ��DM6437�����֧��2·��ƵоƬ */
#define DM6437_AUD_BUF_MAX_NUM             32             /* Ŀǰ�����������BUF���� */

/* ��Ƶ�豸��ģʽ����  */
#define DM6437_AUD_IOM_INPUT               0              /* ����ģʽ�����ɼ� */
#define DM6437_AUD_IOM_OUTPUT              1              /* ���ģʽ�������� */

/* Dm6437AudCtrl�����붨�� */
#define DM6437_AUD_GET_RX_STAT             0              /* ��Ƶ����ͳ��״̬��ѯ */
#define DM6437_AUD_GET_TX_STAT             1              /* ��Ƶ����ͳ��״̬��ѯ */

/* ���Ͷ��� */
typedef void * HDm6437AudDev;


/* ��ƵIO�豸�����Ĳ����ṹ���� */
typedef struct{
    u32   dwBytesPerSample;      /* һ���������ֽ�����1 2 4 */
    u32   dwSamplePerFrame;      /* һ֡���������� */
    u32   dwChanNum;             /* �����������̶���2������������1֡���ֽ���=dwBytesPerSample*dwSamplePerFrame*dwChanNum */
    u32   dwFrameNum;            /* ����Frame�ĸ�������Χ��2~DM6437_AUD_BUF_MAX_NUM-1 */
    u32   dwSampleFreq;          /* 8000��48000��96000��192000Hz ... */
    TFBufDesc *pBufDescs;        /* ָ���û������FBufDesc�ṹ����������׵�ַ���û������Լ���������Buf����ָ�봫�ݸ�����
                                    �������ΪdwFrameNum, ע�⣺��Ƶ��Ҫ128�ֽڱ߽���룻
                                    ���ڲ����Լ�����Buf���û���ΪNULLʱ���ɣ������ᰴ��ǰ��Ĳ����Զ�����BUF */
} TDm6437AudDevParam;

/* ��Ƶ�ɼ�ͳ��״̬�ṹ���壬��Ӧ�����룺DM6437_AUD_GET_RX_STAT */
typedef struct{
    u32   dwBytesInDrv;          /* �����л���Ĳɼ�������Ƶ�����ֽ�������������ʱҪ�� */
    u32   dwLostBytes;           /* ���ڲɼ���ʾ�������ֽ�����һ����û�п���bufʱ��������������ʱҪ�� */
    u32   adwReserved[10];        /* reserved */
} TDm6437AudRxStat;

/* ��Ƶ����״̬�ṹ���壬��Ӧ�����룺DM6437_AUD_GET_TX_STAT */
typedef struct{
    u32   dwBytesInDrv;          /* �����л���Ĵ����ŵ���Ƶ�����ֽ�������������ʱҪ�� */
    u32   dwMuteBytes;           /* ���ڲ��ű�ʾ���ž������ֽ�����һ����û����Ƶ����ʱ��������������ʱҪ�� */
    u32   adwReserved[10];        /* reserved */
} TDm6437AudTxStat;


/*==============================================================================
    ������      : Dm6437AudOpen
    ����        ����ƵIO�豸�򿪣�1��dwDevId���Դ�2�Σ��ֱ�ΪINPUT/OUPUT
    �������˵����dwDevId: 0~DM6437_AUD_DEV_MAX_NUM-1;
                 nMode: DM6437_AUD_IOM_INPUT/DM6437_AUD_IOM_OUTPUT
                 ptParam: �򿪵Ĳ���
    ����ֵ˵��  �����󷵻�NULL���ɹ����ؿ��ƾ��
------------------------------------------------------------------------------*/
HDm6437AudDev Dm6437AudOpen(u32 dwDevId, l32 nMode, TDm6437AudDevParam *ptParam);

/*==============================================================================
    ������      : Dm6437AudClose
    ����        ����ƵIO�豸�رա�
    �������˵����hAudDev: Dm6437AudOpen�������صľ��;
    ����ֵ˵��  �����󷵻�DM6437_AUD_FAILURE������룻�ɹ�����DM6437_AUD_SUCCESS
------------------------------------------------------------------------------*/
l32 Dm6437AudClose(HDm6437AudDev hAudDev);

/*==============================================================================
    ������      : Dm6437AudRead
    ����        ����ƵIO�豸�����ݣ���ȡ���ȱ�����dwBytesPerSample*dwChanNum����������
    �������˵����hAudDev: ��DM6437_AUD_IOM_INPUTģʽ����Dm6437AudOpen�������صľ��;
                 pBuf: ָ���û������Buf��������Ųɼ�����Ƶ����
                 size��Ҫ��ȡ�������ֽ���
                 nTimeoutMs: -1=wait forever; 0=no wait;������ֵΪ��ʱ������
    ����ֵ˵��  �����󷵻�DM6437_AUD_FAILURE����ʱ����0���ɹ����ض������ֽ���(=size)
------------------------------------------------------------------------------*/
l32 Dm6437AudRead(HDm6437AudDev hAudDev, void *pBuf, size_t size, l32 nTimeoutMs);

/*==============================================================================
    ������      : Dm6437AudWrite
    ����        ������ƵIO�豸д���ݣ������ֽ���������dwBytesPerSample*dwChanNum��������
    �������˵����hAudDev: ��DM6437_AUD_IOM_OUTPUTģʽ����Dm6437AudOpen�������صľ��;
                 pData: ָ���û���Ŵ����ŵ���Ƶ����
                 size��Ҫ���ŵ������ֽ���
                 nTimeoutMs: -1=wait forever; 0=no wait;������ֵΪ��ʱ������
    ����ֵ˵��  �����󷵻�DM6437_AUD_FAILURE����ʱ����0���ɹ�����д����ֽ���(=size)
------------------------------------------------------------------------------*/
l32 Dm6437AudWrite(HDm6437AudDev hAudDev, void *pData, size_t size, l32 nTimeoutMs);

/*==============================================================================
    ������      : Dm6437AudFBufGet
    ����        ��ȡһ֡��ƵBUF�����ڲɼ��û��õ�������Ƶ����Buf�����ڲ����û�
                  �õ����ǿ�Buf���û����Զ�ε���ȡ���BUF��
                  # ����û�ʹ��read write�Ļ���Ҫʹ�øú���!!!
    �������˵����hAudDev: ����Dm6437AudOpen�������صľ��;
                  ptBufDesc: �û����䲢����ָ�룬������BUF��Ϣ�������û�
                  nTimeoutMs: -1=wait forever; 0=no wait;������ֵΪ��ʱ������
    ����ֵ˵��  �����󷵻�DM6437_AUD_FAILURE������룻�ɹ�����DM6437_AUD_SUCCESS
------------------------------------------------------------------------------*/
l32 Dm6437AudFBufGet(HDm6437AudDev hAudDev, TFBufDesc *ptBufDesc, l32 nTimeoutMs);

/*==============================================================================
    ������      : Dm6437AudFBufPut
    ����        ���黹һ֡��ƵBUF
                  # ����û�ʹ��read write�Ļ���Ҫʹ�øú���!!!
    �������˵����hAudDev: ����Dm6437AudOpen�������صľ��;
                  ptBufDesc: �û�����Dm6437AudFBufGet�õ���BufDesc��Ϣ
    ����ֵ˵��  �����󷵻�DM6437_AUD_FAILURE������룻�ɹ�����DM6437_AUD_SUCCESS
------------------------------------------------------------------------------*/
l32 Dm6437AudFBufPut(HDm6437AudDev hAudDev, TFBufDesc *ptBufDesc);

/*====================================================================
    ������      : Dm6437AudCtrl
    ����        ����ƵIO�豸���ƣ�Ŀǰ������
                    DM6437_AUD_GET_RX_STAT: pArgsΪTDm6437AudRxStat *
                    DM6437_AUD_GET_TX_STAT: pArgsΪTDm6437AudTxStat *
                  ......
    �������˵����hAudDev: ����Dm6437AudOpen�������صľ��;
                 nCmd: �����룻pArgs: ����ָ��
    ����ֵ˵��  �����󷵻�DM6437_AUD_FAILURE������룻�ɹ�����DM6437_AUD_SUCCESS
---------------------------------------------------------------------*/
l32 Dm6437AudCtrl(HDm6437AudDev hAudDev, l32 nCmd, void *pArgs);

/*====================================================================
    ������      : Dm6437AudGetVer
    ����        ��ģ��汾�Ų�ѯ��
    �������˵����pchVer�� �����Ĵ�Ű汾��Ϣ��bufָ��
                  dwBufLen������buf�ĳ���
    ����ֵ˵��  ���汾��ʵ���ַ������ȡ�С��0Ϊ����;
                 ���ʵ���ַ������ȴ���dwBufLen����ֵΪ0
--------------------------------------------------------------------*/
l32 Dm6437AudGetVer(s8 *pchVer, u32 dwBufLen);


#ifdef __cplusplus 
} 
#endif /* __cplusplus */

#endif /* __DM6437_AUDIO_API_H */
