/*****************************************************************************
ģ����      : VPSS_DRV_API
�ļ���      : vpss_api_def.h
����ļ�    : 
�ļ�ʵ�ֹ���: ����ͷ�ļ�����
����        : �ŷ���
�汾        : V1.0  Copyright(C) 2011-2019 KEDACOM, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
03/29/2011  1.0         �ŷ���      ����
******************************************************************************/

#ifndef __VPSS_API_DEF_H
#define __VPSS_API_DEF_H

#ifdef __cplusplus
extern "C" {
#endif

//#define VPS_API_DBG_EN

/* �궨�� */
#ifdef VPS_API_DBG_EN
# define VPS_API_DBG(fmt, args...) \
    do { \
        printf("[VPS_API_DBG]: " fmt, ## args); \
    } while (0)
#else
# define VPS_API_DBG(fmt, args...)
#endif

#define VPS_API_PRT(fmt, args...) \
    do { \
        printf("[VPS_API]: " fmt, ## args); \
    } while (0)

#define VPS_API_ERR(fmt, args...) \
    do { \
        printf("[VPS_API_ERR]%d:%s->" fmt, __LINE__, __FUNCTION__, ## args); \
    } while (0)


#ifdef __cplusplus
}
#endif

#endif /* __VPSS_API_DEF_H */
