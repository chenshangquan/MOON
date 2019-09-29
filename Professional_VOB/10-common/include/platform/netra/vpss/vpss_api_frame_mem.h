/******************************************************************************
ģ����  �� VPSS_DRV_API
�ļ���  �� vpss_api_frame_mem.h
����ļ��� vpss_api_frame_mem.c
�ļ�ʵ�ֹ��ܣ�
����    ���ŷ���
�汾    ��1.0.0.0.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
09/15/2011  1.0         �ŷ���      ����
******************************************************************************/
#ifndef __VPSS_API_FRAME_MEM_H
#define __VPSS_API_FRAME_MEM_H

#ifdef __cplusplus 
extern "C" { 
#endif /* __cplusplus */

#include "kdvtype.h"
#include "vpss_api_def.h"
#include "vpss_api_core.h"


/* �������� */
/*==============================================================================
    ������      : VpssFrameAlloc
    ����        : ����֡buf
    �������˵��: ptFrame: ��Ƶ����
                  dwNumFrames: ֡�� 
    ����ֵ˵��  : ���󷵻�VPSS_FAILURE������룻�ɹ�����VPSS_SUCCESS
------------------------------------------------------------------------------*/
s32 VpssFrameAlloc(TVpssFrame *ptFrame, u32 dwNumFrames);

/*==============================================================================
    ������      : VpssFrameFree
    ����        : �ͷ�֡buf
    �������˵��: ptFrame: ��Ƶ����
                  dwNumFrames: ֡�� 
    ����ֵ˵��  : ���󷵻�VPSS_FAILURE������룻�ɹ�����VPSS_SUCCESS
------------------------------------------------------------------------------*/
s32 VpssFrameFree(TVpssFrame *ptFrame, u32 dwNumFrames);

/*==============================================================================
    ������      : VpssFrameGetSize
    ����        : ��ѯ֡�Ĵ�С
    �������˵��: ptFrame: ��Ƶ����
                  pdwSize: buffer size
                  pdwOffsetC: C plane offset for YUV420SP data
    ����ֵ˵��  : ���󷵻�VPSS_FAILURE������룻�ɹ�����VPSS_SUCCESS
------------------------------------------------------------------------------*/
s32 VpssFrameGetSize(TVpssFrame *ptFrame, u32 *pdwSize, u32 *pdwOffsetC);

/*==============================================================================
    ������      : VpssGetFrameInfo
    ����        : ��ѯframebuffer��ʹ�����
    �������˵��: NULL
    ����ֵ˵��  : NULL
------------------------------------------------------------------------------*/
void VpssGetFrameInfo(void);


#ifdef __cplusplus 
} 
#endif /* __cplusplus */

#endif /* __VPSS_API_FRAME_MEM_H */
