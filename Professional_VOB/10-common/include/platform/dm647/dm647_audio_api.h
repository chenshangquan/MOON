/******************************************************************************
ģ����  �� DM647_AUDIO_DRV
�ļ���  �� dm647_audio_api.h
����ļ��� dm647_audio_api.c
�ļ�ʵ�ֹ��ܣ�
����    ���ŷ���
�汾    ��1.0.0.0.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
08/15/2007  1.0         �ŷ���      ����
04/22/2008  1.1         �ŷ���      �޸����Ͷ���ͷ�ļ����޸�ioctl���ͺ궨��
******************************************************************************/
#ifndef __DM647_AUDIO_API_H
#define __DM647_AUDIO_API_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* runtime include files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "dm647_drv_common.h"


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
ģ��汾��DM647_AUDIO_DRV 1.1.1.200090203
���ӹ��ܣ�����
�޸�ȱ�ݣ���
�ύ�ˣ��ճϽ�
----------------------------------------------------------------------------
ģ��汾��DM647_AUDIO_DRV 1.3.1.200090703
���ӹ��ܣ�1. buff����EDMAʹ���޸�
          2. ������mcasp������Ϣ�ķ���
�޸�ȱ�ݣ���
�ύ�ˣ��ճϽ�
----------------------------------------------------------------------------
ģ��汾��DM647_AUDIO_DRV 1.3.2.200091009
���ӹ��ܣ�1. ��Ƶ����ʱ��ģʽ��ͬ���Զ�����
          2. ���ݲ�ͬ�豸���ò�ͬ����Ƶͨ��
�޸�ȱ�ݣ���
�ύ�ˣ��ճϽ�
----------------------------------------------------------------------------
ģ��汾��DM647_AUDIO_DRV 1.3.3.200091010
���ӹ��ܣ���Ƶ�ɼ������޸�
�޸�ȱ�ݣ���
�ύ�ˣ��ճϽ�
----------------------------------------------------------------------------
ģ��汾��DM647_AUDIO_DRV 1.3.4.200091203
���ӹ��ܣ���Ƶopenʱ��������channel������
�޸�ȱ�ݣ���
�ύ�ˣ��ճϽ�
----------------------------------------------------------------------------
ģ��汾��DM647_AUDIO_DRV 1.3.5.200091230
���ӹ��ܣ�������KDV7820������
�޸�ȱ�ݣ���
�ύ�ˣ��ճϽ�
----------------------------------------------------------------------------
ģ��汾��DM647_AUDIO_DRV 1.3.6.20100107
���ӹ��ܣ���
�޸�ȱ�ݣ������˹ر���Ƶ�ɼ����²����޷�����������
�ύ�ˣ��ճϽ�
----------------------------------------------------------------------------
ģ��汾��DM647_AUDIO_DRV 1.3.7.20100111
���ӹ��ܣ���
�޸�ȱ�ݣ������˹ر���Ƶ��򿪲�ͬser���ֲ�����������
�ύ�ˣ��ճϽ�
----------------------------------------------------------------------------
ģ��汾��DM647_AUDIO_DRV 1.3.8.20100329
���ӹ��ܣ���
�޸�ȱ�ݣ������˰���128�ֽڷ���buffer�ڴ浼�³��������
�ύ�ˣ��ճϽ�
----------------------------------------------------------------------------
ģ��汾��DM647_AUDIO_DRV 1.3.9.20100520
���ӹ��ܣ���
�޸�ȱ�ݣ�����������Ƶʱ��ʱ����Ƶ�ɼ���ѭ������
�ύ�ˣ��ŷ���
----------------------------------------------------------------------------
ģ��汾��DM647_AUDIO_DRV 1.3.10.20100521
���ӹ��ܣ��޸Ĳ��Ե�����Ƶʱ��ʱ����Ƶ�ɼ�����ʧ��
�޸�ȱ�ݣ��������Ƶ�ɼ������豸ʧ�ܺ�û����򿪱�־�����Ժ���Ҳ�򲻿��豸
�ύ�ˣ��ŷ���

****************************************************************************/

/* �汾�Ŷ��� */
#define VER_DM647_AUDIO_DRV         (const s8*)"DM647_AUDIO_DRV 1.3.10.20100521" 

/* �弶����ģ�鷵��ֵ����  */
#define DM647_AUD_SUCCESS                0                  /* �ɹ� */

#define DM647_AUD_ERR_BASE               0                  /* �������ֵ */
#define DM647_AUD_DEV_NOT_EXIST          (DM647_AUD_SUCCESS+1)  /* �豸������ */
#define DM647_AUD_DEV_NOT_OPEN           (DM647_AUD_SUCCESS+2)  /* �豸û�д� */
#define DM647_AUD_PARAM_ERR              (DM647_AUD_SUCCESS+3)  /* �����Ƿ� */
#define DM647_AUD_LENGTH_ERR             (DM647_AUD_SUCCESS+4)  /* ��Ϣ���ȴ��� */
#define DM647_AUD_QUEUE_FULL             (DM647_AUD_SUCCESS+5)  /* ���ݶ������� */
#define DM647_AUD_NOT_SUPPORT            (DM647_AUD_SUCCESS+6)  /* �豸��֧�ָò��� */
#define DM647_AUD_OPT_TIMEOUT            (DM647_AUD_SUCCESS+7)  /* ������ʱ */
#define DM647_AUD_NO_MEM                 (DM647_AUD_SUCCESS+8)  /* û�п����ڴ� */
#define DM647_AUD_DEV_BUSY               (DM647_AUD_SUCCESS+9)  /* �豸æ���Ѿ����� */
#define DM647_AUD_GIO_FAILE              (DM647_AUD_SUCCESS+10) /* GIO����ʧ�� */
#define DM647_AUD_FAILURE                -1                 /* δ֪���쳣ʧ�� */

/* ����ֵ���� */
#define DM647_AUD_DEV_MAX_NUM             1              /* Ŀǰһ��DM647�����֧��1·��ƵоƬ */
#define DM647_AUD_BUF_MAX_NUM             32             /* Ŀǰ�����������BUF���� */

/* ��Ƶ�豸��ģʽ����  */
#define DM647_AUD_IOM_INPUT               0              /* ����ģʽ�����ɼ� */
#define DM647_AUD_IOM_OUTPUT              1              /* ���ģʽ�������� */

/* Dm647AudCtrl�����붨�� */
#define DM647_AUD_GET_RX_STAT             0              /* ��Ƶ����ͳ��״̬��ѯ */
#define DM647_AUD_GET_TX_STAT             1              /* ��Ƶ����ͳ��״̬��ѯ */

/* ���Ͷ��� */
typedef void * HDm647AudDev;

/* ����ڶ��� */
#define AUD_SER0    (1 << 0)
#define AUD_SER1    (1 << 1)
#define AUD_SER2    (1 << 2)
#define AUD_SER3    (1 << 3)
#define AUD_SER4    (1 << 4)
#define AUD_SER5    (1 << 5)
#define AUD_SER6    (1 << 6)
#define AUD_SER7    (1 << 7)
#define AUD_SER8    (1 << 8)
#define AUD_SER9    (1 << 9)

/* ��ƵIO�豸�����Ĳ����ṹ���� */
typedef struct{
    u32   dwBytesPerSample;      /* һ���������ֽ�����1 2 4 */
    u32   dwSamplePerFrame;      /* һ֡���������� */
    u32   dwChanNum;             /* ����������hdu��4��4��ʾ��·2��������ͬʱ����3·����6����1֡���ֽ���=dwBytesPerSample*dwSamplePerFrame*dwChanNum */
    u32   dwFrameNum;            /* ����Frame�ĸ�������Χ��2~DM647_AUD_BUF_MAX_NUM-1 */
    u32   dwSampleFreq;          /* 8000��48000��96000��192000Hz ... */
    TFBufDesc *pBufDescs;        /* ָ���û������FBufDesc�ṹ����������׵�ַ���û������Լ���������Buf����ָ�봫�ݸ�����
                                    �������ΪdwFrameNum, ע�⣺��Ƶ��Ҫ128�ֽڱ߽���룻
                                    ���ڲ����Լ�����Buf���û���ΪNULLʱ���ɣ������ᰴ��ǰ��Ĳ����Զ�����BUF */
    u32   dwChannelSet;          /* ��0��ʾĬ������ ���������Dm647AudOpen�ͽӿ��ĵ�˵�� */
} TDm647AudDevParam;

/* ��Ƶ�ɼ�ͳ��״̬�ṹ���壬��Ӧ�����룺DM647_AUD_GET_RX_STAT */
typedef struct{
    u32   dwBytesInDrv;          /* �����л���Ĳɼ�������Ƶ�����ֽ�������������ʱҪ�� */
    u32   dwLostBytes;           /* ���ڲɼ���ʾ�������ֽ�����һ����û�п���bufʱ��������������ʱҪ�� */
    u32   dwDmaErr;              /* dma����Ĵ��� */
    u32   dwRunErr;              /* Overrun����Ĵ��� */
    u32   dwSyncErr;             /* ֡ͬ������Ĵ��� */
    u32   dwPingPongErr;         /* ping-pong��ת����Ĵ��� */
    u32   dwPingPongErrLost;     /* ping-pong��ת����Ĵ��� (Lost״̬) */
    u32   dwPingPongErrDebug;    /* ping-pong��ת����Ĵ��� (Debug״̬) */
    u32   adwReserved[6];        /* reserved */
} TDm647AudRxStat;

/* ��Ƶ����״̬�ṹ���壬��Ӧ�����룺DM647_AUD_GET_TX_STAT */
typedef struct{
    u32   dwBytesInDrv;          /* �����л���Ĵ����ŵ���Ƶ�����ֽ�������������ʱҪ��
                                    (ע�⣺hdu����·���ݵĺͣ���Ҫ���ÿ·���ݶ�Ҫ����2�� */
    u32   dwMuteBytes;           /* ���ڲ��ű�ʾ���ž������ֽ�����һ����û����Ƶ����ʱ��������������ʱҪ�� */
    u32   dwDmaErr;              /* dma����Ĵ��� */
    u32   dwRunErr;              /* Underrun����Ĵ��� */
    u32   dwSyncErr;             /* ֡ͬ������Ĵ��� */
    u32   dwPingPongErr;         /* ping-pong��ת����Ĵ��� */
    u32   dwPingPongErrMute;     /* ping-pong��ת����Ĵ��� (Mute״̬) */
    u32   dwPingPongErrDebug;    /* ping-pong��ת����Ĵ��� (Debug״̬) */
    u32   adwReserved[6];        /* reserved */
} TDm647AudTxStat;


/*==============================================================================
 *  ������      : Dm647AudOpen
 *  ����        ����ƵIO�豸�򿪣�1��dwDevId���Դ�2�Σ��ֱ�ΪINPUT/OUPUT
 *  �������˵����dwDevId: 0~DM647_AUD_DEV_MAX_NUM-1;
 *               nMode: DM647_AUD_IOM_INPUT/DM647_AUD_IOM_OUTPUT
 *               ptParam: �򿪵Ĳ���
 *               dwBoard:��Ӧ���豸
 *  ����ֵ˵��  �����󷵻�NULL���ɹ����ؿ��ƾ��
 *
 *  dwBytesPerSample    һ���������ֽ�����1 2 4 (Ŀǰֻ��4)
 *  dwSamplePerFrame    һ֡����������
 *  dwChanNum           ��Ӧ��Ƶ�ɼ��򲥷�·������2
 *
 *  TDm647AudDevParam�� dwChannelSet˵��
 *
 *  dwChannelSet��32λ����0��ʾĬ������ ��0ʱΪ�Զ��� ���������ȡ����ͬ�ĺ���ʾ�ɼ��򲥷ŵ�·��
 *
 *  ��buffer�� AUD_SER0 �� AUD_SERn ·�����ҷֲ�������Ϊbuffer��n��֮1, �޷����� AUD_SERn ��buffer�е�λ��
 *
 *                  �����                  ��Ӧ��
 *  HDU:
 *      ����        AOUT1                   AUD_SER0
 *                  AOUT2                   AUD_SER1
 *
 *  KDV7820:
 *      dsp0�ɼ�    HDMI                    AUD_SER0 (����Ƶ�ʲ��̶�)
 *      dsp0����    ��������Ƶ����        AUD_SER1 (�̶�48K����)
 *      dsp2�ɼ�    ģ����Ƶ                AUD_SER0
 *                  dsp0��������Ƶ        AUD_SER1
 *                  ����MIC1                AUD_SER2
 *                  ����MIC2                AUD_SER3
 *      dsp2����    ��Ƶ���                AUD_SER4
 *                  ������                AUD_SER5
 *
 *  Ĭ������(dwChannelSet��0ʱ):
 *  HDU:
 *      ����: AUD_SER0 | AUD_SER1                           (dwChanNum��Ӧ4)
 *
 *  KDV7820:
 *      dsp0�ɼ� AUD_SER0                                   (dwChanNum��Ӧ2)
 *      dsp0���� AUD_SER1                                   (dwChanNum��Ӧ2)
 *      dsp2�ɼ� AUD_SER0 | AUD_SER1 | AUD_SER2 | AUD_SER3  (dwChanNum��Ӧ8)
 *      dsp2���� AUD_SER4 | AUD_SER5                        (dwChanNum��Ӧ4)
------------------------------------------------------------------------------*/
HDm647AudDev Dm647AudOpen(u32 dwDevId, l32 nMode, TDm647AudDevParam *ptParam);

/*==============================================================================
    ������      : Dm647AudClose
    ����        ����ƵIO�豸�رա�
    �������˵����hAudDev: Dm647AudOpen�������صľ��;
    ����ֵ˵��  �����󷵻�DM647_AUD_FAILURE������룻�ɹ�����DM647_AUD_SUCCESS
------------------------------------------------------------------------------*/
l32 Dm647AudClose(HDm647AudDev hAudDev);

/*==============================================================================
    ������      : Dm647AudRead
    ����        ����ƵIO�豸�����ݣ���ȡ���ȱ�����dwBytesPerSample*dwChanNum����������
    �������˵����hAudDev: ��DM647_AUD_IOM_INPUTģʽ����Dm647AudOpen�������صľ��;
                 pBuf: ָ���û������Buf��������Ųɼ�����Ƶ����
                 size��Ҫ��ȡ�������ֽ���
                 nTimeoutMs: -1=wait forever; 0=no wait;������ֵΪ��ʱ������
    ����ֵ˵��  �����󷵻�DM647_AUD_FAILURE����ʱ����0���ɹ����ض������ֽ���(=size)
------------------------------------------------------------------------------*/
l32 Dm647AudRead(HDm647AudDev hAudDev, void *pBuf, size_t size, l32 nTimeoutMs);

/*==============================================================================
    ������      : Dm647AudWrite
    ����        ������ƵIO�豸д���ݣ������ֽ���������dwBytesPerSample*dwChanNum��������
    �������˵����hAudDev: ��DM647_AUD_IOM_OUTPUTģʽ����Dm647AudOpen�������صľ��;
                 pData: ָ���û���Ŵ����ŵ���Ƶ����
                 size��Ҫ���ŵ������ֽ���
                 nTimeoutMs: -1=wait forever; 0=no wait;������ֵΪ��ʱ������
    ����ֵ˵��  �����󷵻�DM647_AUD_FAILURE����ʱ����0���ɹ�����д����ֽ���(=size)
------------------------------------------------------------------------------*/
l32 Dm647AudWrite(HDm647AudDev hAudDev, void *pData, size_t size, l32 nTimeoutMs);

/*==============================================================================
    ������      : Dm647AudFBufGet
    ����        ��ȡһ֡��ƵBUF�����ڲɼ��û��õ�������Ƶ����Buf�����ڲ����û�
                  �õ����ǿ�Buf���û����Զ�ε���ȡ���BUF��
                  # ����û�ʹ��read write�Ļ���Ҫʹ�øú���!!!
    �������˵����hAudDev: ����Dm647AudOpen�������صľ��;
                  ptBufDesc: �û����䲢����ָ�룬������BUF��Ϣ�������û�
                  nTimeoutMs: -1=wait forever; 0=no wait;������ֵΪ��ʱ������
    ����ֵ˵��  �����󷵻�DM647_AUD_FAILURE������룻�ɹ�����DM647_AUD_SUCCESS
------------------------------------------------------------------------------*/
l32 Dm647AudFBufGet(HDm647AudDev hAudDev, TFBufDesc *ptBufDesc, l32 nTimeoutMs);

/*==============================================================================
    ������      : Dm647AudFBufPut
    ����        ���黹һ֡��ƵBUF
                  # ����û�ʹ��read write�İ��Ҫʹ�øú��?!!
    �������˵����hAudDev: ����Dm647AudOpen�������صľ��;
                  ptBufDesc: �û�����Dm647AudFBufGet�õ���BufDesc��Ϣ
    ����ֵ˵��  �����󷵻�DM647_AUD_FAILURE������룻�ɹ�����DM647_AUD_SUCCESS
------------------------------------------------------------------------------*/
l32 Dm647AudFBufPut(HDm647AudDev hAudDev, TFBufDesc *ptBufDesc);

/*====================================================================
    ������      : Dm647AudCtrl
    ����        ����ƵIO�豸���ƣ�Ŀǰû�ã��Ժ���չ��
                  ......
    �������˵����hAudDev: ����Dm647AudOpen�������صľ��;
                 nCmd: �����룻pArgs: ����ָ��
    ����ֵ˵��  �����󷵻�DM647_AUD_FAILURE������룻�ɹ�����DM647_AUD_SUCCESS
---------------------------------------------------------------------*/
l32 Dm647AudCtrl(HDm647AudDev hAudDev, l32 nCmd, void *pArgs);

/*====================================================================
    ������      : Dm647AudGetVer
    ����        ��ģ��汾�Ų�ѯ��
    �������˵����pchVer�� �����Ĵ�Ű汾��Ϣ��bufָ��
                  dwBufLen������buf�ĳ���
    ����ֵ˵��  ���汾��ʵ���ַ������ȡ�С��0Ϊ����;
                 ���ʵ���ַ������ȴ���dwBufLen����ֵΪ0
--------------------------------------------------------------------*/
l32 Dm647AudGetVer(s8 *pchVer, u32 dwBufLen);


#ifdef __cplusplus 
} 
#endif /* __cplusplus */

#endif /* __DM647_AUDIO_API_H */
