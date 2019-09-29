/******************************************************************************
ģ����  �� DM_AUDIO_DRV
�ļ���  �� dm_audio_api.h
����ļ��� dm_audio_api.c
�ļ�ʵ�ֹ��ܣ�����ý����Ƶ�ӿ�
����    ���ŷ���
�汾    ��1.0.0.0.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
07/12/2011  1.0         �ŷ���      ����
******************************************************************************/
#ifndef __DM_AUDIO_API_H
#define __DM_AUDIO_API_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* runtime include files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "kdvtype.h"


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
ģ��汾��DM_AUDIO_DRV 1.1.1.20110712
���ӹ��ܣ�����
�޸�ȱ�ݣ���
�ύ�ˣ��ŷ���
----------------------------------------------------------------------------

****************************************************************************/
/* �汾�Ŷ��� */
#define VER_DM_AUDIO_DRV         (const s8*)"DM_AUDIO_DRV 1.1.1.20110712" 

/* ����ģ�鷵��ֵ���� */
#define DM_AUD_ELEN        -8   /**< len err (failure). */
#define DM_AUD_ENOOPEN     -7   /**< IO no open (failure). */
#define DM_AUD_EBUSY       -6   /**< An IO busy occured (failure). */
#define DM_AUD_EINVAL      -5   /**< Invalid input arguments (failure). */
#define DM_AUD_ENOMEM      -4   /**< No memory available (failure). */
#define DM_AUD_EIO         -3   /**< An IO error occured (failure). */
#define DM_AUD_ENOTIMPL    -2   /**< Functionality not implemented (failure). */
#define DM_AUD_EFAIL       -1   /**< General failure code (failure). */
#define DM_AUD_EOK          0   /**< General success code (success). */
#define DM_AUD_EFLUSH       1   /**< The command was flushed (success). */
#define DM_AUD_EPRIME       2   /**< The command was primed (success). */
#define DM_AUD_EFIRSTFIELD  3   /**< Only the first field was processed (success)*/
#define DM_AUD_EBITERROR    4   /**< There was a non fatal bit error (success). */
#define DM_AUD_ETIMEOUT     5   /**< The operation was timed out (success). */
#define DM_AUD_EEOF         6   /**< The operation reached end of file */
#define DM_AUD_EAGAIN       7   /**< The command needs to be rerun (success). */

/* ����ֵ���� */
#define DM_AUD_DEV_MAX_NUM  4   /* Ŀǰ���֧��4����Ƶ�豸 */
#define DM_AUD_BUF_MAX_NUM  32  /* Ŀǰ�����������BUF���� */

/* ��Ƶ�豸��ģʽ����  */
#define DM_AUD_IOM_INPUT    0   /* ����ģʽ�����ɼ� */
#define DM_AUD_IOM_OUTPUT   1   /* ���ģʽ�������� */

/* DmAudCtrl�����붨�� */
#define DM_AUD_GET_RX_STAT  0   /* ��Ƶ����ͳ��״̬��ѯ */
#define DM_AUD_GET_TX_STAT  1   /* ��Ƶ����ͳ��״̬��ѯ */

/* ���Ͷ��� */
typedef void * HDmAudDev;

/* ��Ƶ���ݿڶ��壬����McAsp�豸��˵��Ч������ָ����ǰASP�豸�󶨵������������I2S��· */
#define DM_AUD_SER0    (1 << 0)
#define DM_AUD_SER1    (1 << 1)
#define DM_AUD_SER2    (1 << 2)
#define DM_AUD_SER3    (1 << 3)
#define DM_AUD_SER4    (1 << 4)
#define DM_AUD_SER5    (1 << 5)
#define DM_AUD_SER6    (1 << 6)
#define DM_AUD_SER7    (1 << 7)
#define DM_AUD_SER8    (1 << 8)
#define DM_AUD_SER9    (1 << 9)
#define DM_AUD_SER10   (1 << 10)
#define DM_AUD_SER11   (1 << 11)
#define DM_AUD_SER12   (1 << 12)
#define DM_AUD_SER13   (1 << 13)
#define DM_AUD_SER14   (1 << 14)
#define DM_AUD_SER15   (1 << 15)


typedef struct{
    u32	    dwFBufId;           /* ֡BUF�������ţ������ڲ�ʹ�ã��û������޸� */
    u8 *    pbyFBuf;            /* ֡BUF��ָ�룬ָ��֡����Buf��
                                    �û�����BufDescʱ�����NULL�Ļ������Զ�����1������BUF������ʹ���û�ָ���ĵ�ַ��Ϊ����BUF��
                                    !!! ������û����䣬
                                        1���û����뱣֤Buf�Ķ��룬����ʼ��ַ������128�ֽڶ���;
                                        ����BUF��С=dwBytesPerSample*dwSamplePerFrame*dwChanNum;
                                        2���ر��豸ʱ���������ͷ���Щ�ڴ� */
    BOOL32  bUseCache;          /* �������û�����Buf��Ч�������Զ������Ϊ��cache�ģ�
                                   ΪTRUE��ʾ�û������Buf��cache��������������ˢcache����
                                   ΪFALSEΪ����cache�ģ���������ˢcache���� */
    u32	    dwTimeStamp;        /* ֡��ʱ������ɼ�ʱ�û����Զ�ȡ��ǰ֡��ʱ��� */
} TDmAudFBufDesc;

/* ��ƵIO�豸�����Ĳ����ṹ����
 *  ��buffer�� AUD_SER0 �� AUD_SERn ·�����ҽ���ֲ�������Ϊbuffer��n��֮1, 
    �޷����� AUD_SERn ��buffer�е�λ�á���ɼ�����SER1 SER2 �� SER3�����ڴ�����������Ϊ��
    SER1_L SER2_L SER3_L SER1_R SER2_R SER3_R ... ���DM647��ͬ
 *
 *  dwChnlCfg���ã�
 *                  �����                  ��Ӧ��
 *  H600:
 *      Asp0�ɼ�    ģ����Ƶ                DM_AUD_SER0
 *                  ����MIC                 DM_AUD_SER4 (�̶�48K 32λ����)
 *      Asp0����    3.5��Ƶ�ӿ�             DM_AUD_SER1
 *                  ������                  DM_AUD_SER5
 *  H700:
 *      Asp0�ɼ�    RCAģ����Ƶ             DM_AUD_SER1
 *                  ��ũMIC                 DM_AUD_SER3
 *                  ����MIC                 DM_AUD_SER4 (�̶�48K 32λ����)
 *      Asp0����    RCAģ����Ƶ             DM_AUD_SER0
 *                  6.5ƽ�����             DM_AUD_SER2
 *                  ������                  DM_AUD_SER5
 *      Asp1�ɼ�    HDMI��Ƶ                DM_AUD_SER0 (������Դ��ʽ)
 *  H900:
 *      DM8168:
 *          Asp0�ɼ�    11���ӿ�����ѡһ        DM_AUD_SER0
 *                      9��C6747����ѡһ        DM_AUD_SER1                
 *          Asp1�ɼ�    C6747 AXR0_11           DM_AUD_SER0(��������ͨ)
 *					    C6747 AXR1_11	        DM_AUD_SER1(��������ͨ)
 *	        Asp0����    RCAģ����Ƶ             DM_AUD_SER3
 *	        Asp2����    C6747 AXR0_14           DM_AUD_SER0(��������ͨ)
 *                      C6747 AXR0_15           DM_AUD_SER1(��������ͨ)
 *	HDU2:
 *		Asp0���� 	3.5��Ƶ�ӿ�0 			 DM_AUD_SER0
 *		Asp0���� 	3.5��Ƶ�ӿ�1 			 DM_AUD_SER1
 * 		Asp0���� 	HDMI��Ƶ�ӿ�0 			 DM_AUD_SER2
 * 		Asp0���� 	HDMI��Ƶ�ӿ�1 			 DM_AUD_SER3
 */
typedef struct{
    u32   dwBytesPerSample;     /* һ���������ֽ�����1 2 4 */
    u32   dwSamplePerFrame;     /* һ֡���������� */
    u32   dwChnlNum;            /* ����������2������������n·��������1֡���ֽ���=dwBytesPerSample*dwSamplePerFrame*dwChanNum */
    u32   dwChnlCfg;            /* ��0��ʾ��Ĭ������serial���������·, ����ֵ��DM_AUD_SER0�ȵļ����壬�߼��û�ʹ�� */
    u32   dwFrameNum;           /* ����Frame�ĸ�������Χ��2~DM_AUD_BUF_MAX_NUM-1 */
    u32   dwSampleFreq;         /* 8000��48000��96000��192000Hz ... */
    TDmAudFBufDesc *pBufDescs;  /* ָ���û������FBufDesc�ṹ����������׵�ַ���û������Լ���������Buf����ָ�봫�ݸ�����
                                    �������ΪdwFrameNum, ע�⣺��Ƶ��Ҫ128�ֽڱ߽���룻
                                    ���ڲ����Լ�����Buf���û���ΪNULLʱ���ɣ������ᰴ��ǰ��Ĳ����Զ�����BUF */
} TDmAudDevParam;

/* ��Ƶ�ɼ�ͳ��״̬�ṹ���壬��Ӧ�����룺DM_AUD_GET_RX_STAT */
typedef struct{
    u32   dwFragsTotal;         /* ����������ܻ������Ƶ����֡������ */
    u32   dwFragSize;           /* �����л���һ֡��Ƶ���ݵ��ֽ���,��·�������ܺ� */
    u32   dwFragments;          /* �������ܶ�ȡ����Ƶ����֡�ĸ��� */
    u32   dwBytesCanRd;         /* �������ܶ�ȡ����Ƶ�����ֽ�������������ʱҪ�� */
    u32   dwLostBytes;          /* ���ڲɼ���ʾ�������ֽ�����һ����û�п���bufʱ��������������ʱҪ�� */
    u32   dwDmaErr;             /* dma����Ĵ��� */
    u32   dwOverRunErr;         /* Overrun����Ĵ��� */
    u32   dwSyncErr;            /* ֡ͬ������Ĵ��� */
    u32   dwPingPongErr;        /* ping-pong��ת����Ĵ��� */
    u32   adwReserved[5];       /* reserved */
} TDmAudRxStat;

/* ��Ƶ����״̬�ṹ���壬��Ӧ�����룺DM_AUD_GET_TX_STAT */
typedef struct{
    u32   dwFragsTotal;         /* ����������ܻ������Ƶ����֡������ */
    u32   dwFragSize;           /* �����л���һ֡��Ƶ���ݵ��ֽ��� */
    u32   dwFragments;          /* ��������д�����Ƶ����֡�ĸ��� */
    u32   dwBytesCanWrt;        /* ��������д�����Ƶ�����ֽ�����dwFragsTotal*dwFragSize-dwBytesCanWrt=��ǰ�����ŵ���Ƶ�����ֽ��� */
    u32   dwMuteBytes;          /* ���ڲ��ű�ʾ���ž������ֽ�����һ����û����Ƶ����ʱ��������������ʱҪ�� */
    u32   dwDmaErr;             /* dma����Ĵ��� */
    u32   dwUnderRunErr;        /* Underrun����Ĵ��� */
    u32   dwSyncErr;            /* ֡ͬ������Ĵ��� */
    u32   dwPingPongErr;        /* ping-pong��ת����Ĵ��� */
    u32   adwReserved[5];       /* reserved */
} TDmAudTxStat;


/*==============================================================================
    ������      : DmAudOpen
    ����        ����ƵIO�豸�򿪣�1��dwDevId���Դ�2�Σ��ֱ�ΪINPUT/OUPUT
    �������˵����dwDevId: 0~DM_AUD_DEV_MAX_NUM-1;
                  nMode: DM_AUD_IOM_INPUT/DM_AUD_IOM_OUTPUT
                  ptParam: �򿪵Ĳ���
                  phAudDev: ���ƾ��ָ��
    ����ֵ˵��  �����󷵻�DM_AUD_EFAIL������룻�ɹ�����DM_AUD_EOK�Ϳ��ƾ��
------------------------------------------------------------------------------*/
s32 DmAudOpen(u32 dwDevId, s32 nMode, TDmAudDevParam *ptParam, HDmAudDev *phAudDev);

/*==============================================================================
    ������      : DmAudClose
    ����        ����ƵIO�豸�رա�
    �������˵����hAudDev: DmAudOpen�������صľ��;
    ����ֵ˵��  �����󷵻�DM_AUD_EFAIL������룻�ɹ�����DM_AUD_EOK
------------------------------------------------------------------------------*/
s32 DmAudClose(HDmAudDev hAudDev);

/*==============================================================================
    ������      : DmAudRead
    ����        ����ƵIO�豸�����ݣ���ȡ���ȱ�����dwBytesPerSample*dwChanNum����������
    �������˵����hAudDev: ��DM_AUD_IOM_INPUTģʽ����DmAudOpen�������صľ��;
                 pBuf: ָ���û������Buf��������Ųɼ�����Ƶ����
                 size��Ҫ��ȡ�������ֽ���
                 nTimeoutMs: -1=wait forever; 0=no wait;������ֵΪ��ʱ������
    ����ֵ˵��  �����󷵻�DM_AUD_EFAIL����ʱ����0���ɹ����ض������ֽ���(=size)
------------------------------------------------------------------------------*/
s32 DmAudRead(HDmAudDev hAudDev, void *pBuf, size_t size, s32 nTimeoutMs);

/*==============================================================================
    ������      : DmAudWrite
    ����        ������ƵIO�豸д���ݣ������ֽ���������dwBytesPerSample*dwChanNum��������
    �������˵����hAudDev: ��DM_AUD_IOM_OUTPUTģʽ����DmAudOpen�������صľ��;
                 pData: ָ���û���Ŵ����ŵ���Ƶ����
                 size��Ҫ���ŵ������ֽ���
                 nTimeoutMs: -1=wait forever; 0=no wait;������ֵΪ��ʱ������
    ����ֵ˵��  �����󷵻�DM_AUD_EFAIL����ʱ����0���ɹ�����д����ֽ���(=size)
------------------------------------------------------------------------------*/
s32 DmAudWrite(HDmAudDev hAudDev, void *pData, size_t size, s32 nTimeoutMs);

/*==============================================================================
    ������      : DmAudFBufGet
    ����        ��ȡһ֡��ƵBUF�����ڲɼ��û��õ�������Ƶ����Buf�����ڲ����û�
                  �õ����ǿ�Buf���û����Զ�ε���ȡ���BUF��
                  # ����û�ʹ��read write�Ļ�����ʹ�øú���!!!
    �������˵����hAudDev: ����DmAudOpen�������صľ��;
                  ptBufDesc: �û����䲢����ָ�룬������BUF��Ϣ�������û�
                  nTimeoutMs: -1=wait forever; 0=no wait;������ֵΪ��ʱ������
    ����ֵ˵��  �����󷵻�DM_AUD_EFAIL������룻�ɹ�����DM_AUD_EOK
------------------------------------------------------------------------------*/
s32 DmAudFBufGet(HDmAudDev hAudDev, TDmAudFBufDesc *ptBufDesc, s32 nTimeoutMs);

/*==============================================================================
    ������      : DmAudFBufPut
    ����        ���黹һ֡��ƵBUF
                  # ����û�ʹ��read write�Ļ�����ʹ�øú���!!!
    �������˵����hAudDev: ����DmAudOpen�������صľ��;
                  ptBufDesc: �û�����DmAudFBufGet�õ���BufDesc��Ϣ
    ����ֵ˵��  �����󷵻�DM_AUD_EFAIL������룻�ɹ�����DM_AUD_EOK
------------------------------------------------------------------------------*/
s32 DmAudFBufPut(HDmAudDev hAudDev, TDmAudFBufDesc *ptBufDesc);

/*====================================================================
    ������      : DmAudCtrl
    ����        ����ƵIO�豸���ƣ�Ŀǰ������
                    DM_AUD_GET_RX_STAT: pArgsΪTDmAudRxStat *
                    DM_AUD_GET_TX_STAT: pArgsΪTDmAudTxStat *
                  ......
    �������˵����hAudDev: ����DmAudOpen�������صľ��;
                 nCmd: �����룻pArgs: ����ָ��
    ����ֵ˵��  �����󷵻�DM_AUD_EFAIL������룻�ɹ�����DM_AUD_EOK
---------------------------------------------------------------------*/
s32 DmAudCtrl(HDmAudDev hAudDev, s32 nCmd, void *pArgs);

/*====================================================================
    ������      : DmAudGetVer
    ����        ��ģ��汾�Ų�ѯ��
    �������˵����pchVer�� �����Ĵ�Ű汾��Ϣ��bufָ��
                  dwBufLen������buf�ĳ���
    ����ֵ˵��  ���汾��ʵ���ַ������ȡ�С��0Ϊ����;
                 ���ʵ���ַ������ȴ���dwBufLen����ֵΪ0
--------------------------------------------------------------------*/
s32 DmAudGetVer(s8 *pchVer, u32 dwBufLen);


#ifdef __cplusplus 
} 
#endif /* __cplusplus */

#endif /* __DM_AUDIO_API_H */
