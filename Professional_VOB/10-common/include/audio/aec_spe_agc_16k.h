/*****************************************************************************
ģ����      : aec_spe_agc_16k_interface
�ļ���      : aec_spe_agc_interface.h
����ļ�    : aecpack.c
�ļ�ʵ�ֹ���: AEC/SPE/AGC/����ӿں���
�汾        : V1.0  Copyright(C) 2006-2008 KDC, All rights reserved.
����        : ��ɯ
-----------------------------------------------------------------------------
�޸ļ�¼:
��    ��      �汾        �޸���      �޸�����
2008/08/04    v100        ��  ɯ      ��16K AEC�Ļ����ϼ�����SPE��AGC
******************************************************************************/
#ifndef AEC_SPE_AGC_16K_INTERFACE_H
#define AEC_SPE_AGC_16K_INTERFACE_H

#ifndef AEC_NEW_TYPE_MP3
#define AEC_NEW_TYPE_MP3	2
#endif

#ifndef AEC_NEW_TYPE_G711
#define AEC_NEW_TYPE_G711	3
#endif

#ifndef AEC_NEW_TYPE_G722
#define AEC_NEW_TYPE_G722	4
#endif

#ifndef AEC_NEW_TYPE_G729
#define AEC_NEW_TYPE_G729	5
#endif

#ifndef AEC_NEW_TYPE_G7221C
#define AEC_NEW_TYPE_G7221C	6
#endif

#define AEC_OK      1
#define AEC_ERR     0

#define AEC_HANDLE void *

/*====================================================================
��   ��   ��: AEC_SPE_AGC_Proc_Init
��        �ܣ�AEC/SPE/AGC�ĳ�ʼ��
����ȫ�ֱ���: ��
�������˵��: 1.(i)pvAecHandle      ���ָ���ָ��
              2.(i)pvPackBuf        3��������buffer���ڴ�ռ��ָ��
              3.(i)pvAdFiltHd       AEC�˲��������ָ��
			  4.(i)pvSPEHd          SPE���ָ��
			  5.(i)pvAGCHd          AGC���ָ��
			  6.(i)l32AecType       ��Ƶ����������
			  ���� ֵ ˵��: �ɹ�������AEC_OK
              ʧ�ܣ�����AEC_ERR
			  �� �� ˵  ��: �����Ƿ���AEC/SPE/AGC�����ȳ�ʼ��
======================================================================*/
l32 AEC_SPE_AGC_Proc_Init(void *pvAecHandle, void *pvPackBuf, void *pvAdFiltHd, void *pvSPEHd, void *pvAGCHd, l32 l32AecType);

/*====================================================================
��   ��   ��: AecRefSetNew
��        �ܣ���Զ���źŷ���Զ���źŵĻ�����
����ȫ�ֱ���: ��
�������˵��: 1.(i/o)pHandle		  ���ָ��
              2.(i)ps16RefBuf         ����Ĳο��źŵ�ָ��
              3.(i)l32CapSamples      �ɼ�������������
              4.(i)l32NoPlySamples    ���Ż�����������
���� ֵ ˵��: AEC_OK���ɹ�
              AEC_ERR��ʧ��
�� �� ˵  ��: ��
======================================================================*/
l32 AecRefSetNew(void *pHandle, s16 *ps16RefBuf, l32 l32CapSamples, l32 l32NoPlySamples);

/*====================================================================
��   ��   ��: AEC_SPE_AGC_Proc
��        �ܣ���ɻ��������˲�
����ȫ�ֱ���: ��
�������˵��: 1.(i/o)pHandle           ���ָ��
              2.(i)ps16EchoSig	       �����ź�
              3.(o)ps16AecOutSig       ����ź�
              4.(i)l32UseFlag          AEC/SPE/AGCʹ�ܵı�־
���� ֵ ˵��: �ɹ�������AEC_OK
�� �� ˵  ��: ��
======================================================================*/
l32 AEC_SPE_AGC_Proc(void *pHandle, s16 *ps16EchoSig, s16 *ps16AecOutSig, l32 l32UseFlag);

/*====================================================================
��   ��   ��:  AecFapFreeNew
��        �ܣ� �ͷŻ��������ľ���ռ�
����ȫ�ֱ���:  ��
�������˵��:  1.(i/0)pHandle          ���ָ��
���� ֵ ˵��:  AEC_OK���ɹ���AEC_ERR��ʧ��
�� �� ˵  ��:  ��
======================================================================*/
l32	AecFapFreeNew(void *pHandle);

/*====================================================================
��   ��   ��: AecTypeSetNew
��        �ܣ���������������
����ȫ�ֱ���: ��
�������˵��: 1.(i/o)pHandle       ���ָ��
			  2.(i)l32AecType      ��Ƶ����������
���� ֵ ˵��: AEC_OK���ɹ���AEC_ERR��ʧ��
�� �� ˵  ��: ��
======================================================================*/
l32 AecTypeSetNew(void *pHandle, l32 l32AecType);

/*====================================================================
��   ��   ��: GetAecVersionNew
��        �ܣ��õ�AEC/SPE/AGC�İ汾
����ȫ�ֱ���: ��
�������˵��: 1.(o)*Version: ����ȡ�ð汾�Ŀռ䡣
			  2.(o)StrLen, ����ȡ�ð汾�Ŀռ��С��
			  3.(o)*StrLenUsed���汾�ַ�����ռ�õĿռ��С
���� ֵ ˵��: ��
�� �� ˵  ��: ��
======================================================================*/
void GetAecVersionNew(s8 *Version, l32 StrLen, l32 *pStrLenUsed);

#endif //end of AEC_SPE_AGC_16K_INTERFACE_H

