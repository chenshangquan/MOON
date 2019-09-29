#ifndef _NETCBB_DHCPS_H_
#define _NETCBB_DHCPS_H_
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* DHCP-Server �ص���������Ϣ���ַ */
#define DHCPS_MSG_BASE        (u32)80000

/* DHCP-Server ���������*/
#define DHCPS_MAX_ETH_NUM     (u32)16

/* dhcp ��������DNS������Ϣ */
typedef struct{
    u8 IsAssignDns;           /* 0 : ��ָ��(����Ĭ�� dns ������); 1: ָ�� */
    u32 dwDnsIp;              /* ������ : DNS��IP��ַ */
    s8 achDnsName[128];       /* ������ : DNS ������ ���� */
}TDhcpServerDnsInfo;

/* dhcp �������������ṹ�嶨�� */
typedef struct{
    u32 dwNetMask;            /* ������ : ���� */
    u32 dwSubNetMask;         /* ������ : �������� */
    u32 dwIpPoolStart;        /* ������ : ��ʼ����ĵ�ַ */
    u32 dwIpPoolEnd;          /* ������ : ��ֹ����ĵ�ַ */
    u32 dwRoutes;             /* ������ : Ĭ�����ػ���·������ַ */
    u32 dwEthIp;              /* ������ : ������ַ */
    u32 dwEthId;              /* ����ID */
}TDhcpServerEthInfo;

/* dhcp ��������������Ϣ�ṹ�嶨�� */
typedef struct{
    TDhcpServerEthInfo achTDhcpServerEthInfo[DHCPS_MAX_ETH_NUM];
    u32 dwDhcpServerEthCount; /* dhcp-server ������Ŀ */
    TDhcpServerDnsInfo tTDhcpServerDnsInfo;
}TDhcpServerConfInfo;

typedef struct
{
    u32 dwDhcpsIsRun;         /* 0:ֹͣ; 1: ���� */
}TNetDhcpsState;

/************************************************************
 * ������ : NetDhcpsNotifyCallBack
 *
 * ���� : ��DHCP-Server֪ͨ�û��Ļص�����
 *
 * ���� : ��
 *
 * ����˵�� :
 *      dwMsgID   - �¼����ͣ����������Ϣ���Ͷ���
 *                 (��ʱ����Ҫ�ص������δ�����κλص�ֵ)
 *      pMsg      - ����¼�������ƥ�����Ϣ���ݣ���������Ϣ����˵��
 *
 * ����ֵ : ��ʱ����Ϊ0���Ժ������չ
 ***********************************************************/
typedef int(*NetDhcpsNotifyCallBack)(u32 dwMsgID, void* pMsg);

/************************************************************
 * ������ : NetDhcpsStart
 *
 * ���� : ����DHCP-Server����
 *
 * ���� : ��
 *
 * ����˵�� :
 *      ptTDhcpsServerConfInfo   - dhcp-server ������Ϣ�ṹ��ָ��
 *      ptDhcpsCallBack          - �ϲ�ע��Ļص�����ָ��
 *
 * ����ֵ : ��ʱ����Ϊ0���Ժ������չ
 ***********************************************************/
s32 NetDhcpsStart(TDhcpServerConfInfo* ptDhcpServerConfInfo, NetDhcpsNotifyCallBack ptDhcpsCallBack);

/************************************************************
 * ������ : NetDhcpsStop
 *
 * ���� : �ر�DHCP-Server����
 *
 * ���� : ��
 *
 * ����˵�� :
 *     ��
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ʧ��
 ***********************************************************/
s32 NetDhcpsStop();

/************************************************************
 * ������ : NetDhcpsStopOneEth
 *
 * ���� : �ر�ĳ��������DHCP-Server����
 *
 * ���� : ��
 *
 * ����˵�� :
 *     dwEthId - ����Id
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ʧ��
 ***********************************************************/
s32 NetDhcpsStopOneEth(u32 dwEthId);

/************************************************************
 * ������ : NetDhcpsGetState
 *
 * ���� : ��ȡdhcp-server ����״̬
 *
 * ���� : ��
 *
 * ����˵�� :
 *     dwEthId - ����Id
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ʧ��
 ***********************************************************/
s32 NetDhcpsGetState(u32 dwEthId, TNetDhcpsState* ptNetdhcpsState);


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif