#ifndef _NETCBB_WRAPPER_H_
#define _NETCBB_WRAPPER_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "netcbb_def.h"
#include "netcbb_interface.h"
#include "netcbb_dhcpc.h"
#include "netcbb_pppoe.h"
#include "netcbb_sntp.h"
#include "netcbb_webs.h"
#include "netcbb_dhcps.h"
#include "netcbb_ntpc.h"
#include "netcbb_serv.h"
#include "netcbb_e1.h"
#include "netcbb_ping.h"
#include "netcbb_traceroute.h"

/************************************************************
 * ������ : NetInit
 *
 * ���� : ��ģ��ĳ�ʼ������
 *
 * ���� : ��
 *
 * ����˵�� :
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ʧ��
 ***********************************************************/
s32 NetInit(void);

/************************************************************
 * ������ : NetQueryNetcbbVersion
 *
 * ���� : �ṩ��ҵ�����õ�os�汾�Ų�ѯ
 *
 * ���� : ��
 *
 * ����˵�� :
 *      pchVer    - ��ȡ�汾���ַ���ָ��
 *      dwBufLen  - ���ַ����ĳ���
 *      pdwVerLen - ��ȡ�汾��ʵ���ַ������ȣ��ó��ȷ���֮ǰ�����dwBufLen�Ƚ��Ƿ����������ʱ�Ŷ�pVer��ֵ
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ʧ��
 ***********************************************************/
s32 NetQueryVersion(char* pchVer, u32 dwBufLen);

/************************************************************
 * ������ : NetLogSwitch
 *
 * ���� : ��ģ���ӡ����(Ĭ�Ϲر�)
 *
 * ���� : ��
 *
 * ����˵�� :
 *      1  -  ��log
 *      0  -  �ر�log
 *       Ĭ�Ϲر�
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ʧ��
 ***********************************************************/
s32 NetLogSwitch(u32 dwSwitch);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _NETCBB_WRAPPER_H_ */

