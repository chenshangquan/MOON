#ifndef _NETCBB_DHCPC_H_
#define _NETCBB_DHCPC_H_
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* DHCPC�ص���������Ϣ���ַ */
#define DHCPC_MSG_BASE                 (u32)30000
/* ֪ͨ�û�DHCP��õ�IP��ַ�Ļص���Ϣ����Ϣ�壺TNetDhcpcNotify  */
#define DHCPC_GET_IP_MSG               (u32)(DHCPC_MSG_BASE+1)
/* ֪ͨ�û��豸ʧȥDHCP��õ�IP��ַ�Ļص���Ϣ����Ϣ�壺TNetDhcpcNotify */
#define DHCPC_LOSS_IP_MSG              (u32)(DHCPC_MSG_BASE+2)
/* ֪ͨ�û�����Լ���ڵ��ֵò�����ַԭ�����豸ʧȥDHCP��õ�IP��ַ�Ļص���Ϣ����Ϣ�壺TNetDhcpcNotify */
#define DHCPC_RENEW_FAIL_MSG           (u32)(DHCPC_MSG_BASE+3)

#define DHCPC_IFDOWN_LOSS_IP_MSG       (u32)(DHCPC_MSG_BASE+4)
#define DHCPC_IFERROR_LOSS_IP_MSG      (u32)(DHCPC_MSG_BASE+5)
#define DHCPC_DNS_MAX_DNS_SERVER            64

/* DHCPC���ļ�ʱbuffer�����������ֵ */
#define DHCPC_MAX_READ_FILE_BUFFER_LENGTH   128

/* DHCP ����״̬ */
#define DHCPC_ALREADY_START          1
#define DHCPC_NOT_START              0


/* DNS �������� */
#define DNS_CMD_AUTO        1
#define DNS_CMD_STATIC      0

/* resolv.conf keywords */
#define DNS_KEYWORD_NAMSERV    "nameserver"  /* ����DNS��������IP ��ַ */
#define DNS_KEYWORD_DOMAIN     "domain" ��   /* ���屾������ */
#define DNS_KEYWORD_SEARCH     "search"      /* ���������������б� */
#define DNS_KEYWORD_SORTLIST   "sortlist"    /* �Է��ص������������� */

/* ֪ͨ�û�DHCP��û���ʧȥ��IP��ַ�Ľṹ�� */
typedef struct{
    u32 byEthId;    /* ȡ��/ʧȥIP��ַ�����ں� */
    u32 dwIpAddrs;  /* ȡ��/ʧȥ��IP��ַ�������ֽ��� */
    u32 dwMask;     /* ȡ��/ʧȥ��IP��ַ�������룬�����ֽ��� */
    u32 dwGateWay;  /* ȡ��/ʧȥ��Ĭ�����أ������ֽ����п���Ϊ0����Ϊ�е�DHCP-Server��һ��Ϊ�豸ָ��Ĭ������ */
    u32 dwDnsNum;   /* DNS Server �������Ϊ64�� */
    u32 dwDnsServer[DHCPC_DNS_MAX_DNS_SERVER];  /* ȡ��/ʧȥ��DNS Server �������ֽ��� */
}TNetDhcpcNotify;

/* ������DHCP-Client�˹��ܵ������ϻ�ȡ��IP��ַ����Լ�������Ϣ�ṹ�� */
typedef struct{
    u32 byEthId;     /* ȡ��IP��ַ�����ں� */
    u32 dwIpAddrs;   /* ȡ�õ�IP��ַ�������ֽ��� */
    u32 dwMask;      /* ȡ�õ�IP��ַ�������룬�����ֽ��� */
    u32 dwGateWay;   /* ȡ�õ�Ĭ�����أ������ֽ����п���Ϊ0����Ϊ�е�DHCP-Server��һ��Ϊ�豸ָ��Ĭ������ */
    u32 dwLeaseInfo; /* �ܵ���Լʱ�䣬����Ϊ��λ */
    u32 dwDnsNum;    /*DNS Server �������Ϊ64�� */
    u32 dwDnsServer[DHCPC_DNS_MAX_DNS_SERVER];  /* ȡ��/ʧȥ��DNS Server �������ֽ��� */
}TNetDhcpcLeaseInfo;

typedef struct
{
    u32 dwDhcpcIsRun;
}TNetDhcpcState;

/************************************************************
 * ������ : NetDhcpcNotifyCallBack
 *
 * ���� : ��DHCP���IP��ַ������ĳ��ԭ��ʧȥ�ѻ�õ�IP��ַʱ��
 *        ֪ͨ�û��Ļص�����
 * ���� : ��
 *
 * ����˵�� :
 *      dwMsgID   - �¼����ͣ����������Ϣ���Ͷ���
 *      pMsg      - ����¼�������ƥ�����Ϣ���ݣ���������Ϣ����˵��
 *
 * ����ֵ : ��ʱ����Ϊ0���Ժ������չ 
 ***********************************************************/
typedef int(*NetDhcpcNotifyCallBack)(u32 dwMsgID, void* pMsg);

/************************************************************
 * ������ : NetDhcpcStart
 *
 * ���� : ��ָ���������Ͽ���DHCP-Client�˹���
 *
 * ���� : ��
 *
 * ����˵�� :
 *      byEthId         - Ҫ����DHCP-Client�˹��ܵ����ں�(��0��ʼ)
 *      ptDhcpcCallBack - �ϲ�ע��Ļص�����ָ��
 *      bSetDefautGate  - �ص������Ƿ���ΪĬ������
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ʧ��
 ***********************************************************/
s32 NetDhcpcStart(u32 byEthId, NetDhcpcNotifyCallBack ptDhcpcCallBack, BOOL32 bSetDefautGate);

/************************************************************
 * ������ : NetDhcpcRenew
 *
 * ���� : �ڿ�����DHCP-Client�˹��ܵ��������������������Լ
 *
 * ���� : ��
 *
 * ����˵�� :
 *      byEthId         - Ҫ������Լ�����ں�(��0��ʼ)
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ʧ��
 *          NET_PROCESS_NOT_EXIST - ���̲�����
 ***********************************************************/
s32 NetDhcpcRenew(u32 byEthId);

/************************************************************
 * ������ : NetDhcpcGetLeaseInfo
 *
 * ���� : �ڿ�����DHCP-Client�˹��ܵ������ϻ�ȡ��Լ�������Ϣ
 *
 * ���� : ��
 *
 * ����˵�� :
 *      byEthId            - ������DHCP-Client�˹��ܵ����ں�(��0��ʼ)
 *      ptNetDhcpLeaseInfo - ���صİ�����Լ����Ϣ�Ľṹ��ָ��
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ʧ��
 ***********************************************************/
s32 NetDhcpcGetLeaseInfo(u32 byEthId, TNetDhcpcLeaseInfo* ptNetDhcpcLeaseInfo);

/************************************************************
 * ������ : NetDhcpcStop
 *
 * ���� : ��ָ���������Ϲر�DHCP-Client�˹���
 *
 * ���� : ��
 *
 * ����˵�� :
 *      byEthId   - Ҫ�ر�DHCP-Client�˹��ܵ����ں�(��0��ʼ)
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ʧ��
 ***********************************************************/
s32 NetDhcpcStop(u32 byEthId);

/************************************************************
 * ������ : NetDhcpcGetIfstate
 *
 * ���� : ��ָ���������ϵ�dhcp��Ϣ
 *
 * ���� : ��
 *
 * ����˵�� :
 *      byEthId   - ���ں�(��0��ʼ)
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ʧ��
 *          NET_PROCESS_NOT_EXIST - UDHCPC���̲�����
 ***********************************************************/
s32 NetDhcpcGetIfstate(u32 byEthId, TNetDhcpcState* ptNetdhcpcIfState);

/************************************************************
 * ������ : NetDNSSet
 *
 * ���� : ���þ�̬DNS
 *
 * ���� : ��
 *
 * ����˵�� :
 *      byEthId   - ���ں�(��0��ʼ)
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ʧ��
 ***********************************************************/
s32 NetDNSSet(u32 byEthId, s32 DNSCmd, s8* pchDNSset[], s32 dwNum);

/************************************************************
 * ������ : NetDNSDel
 *
 * ���� : ɾ��DNS
 *
 * ���� : ��
 *
 * ����˵�� :
 *      byEthId   - ���ں�(��0��ʼ)
 *      adwDNSset - dns����(������)
 *      dwNum     - dns����
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ʧ��
 ***********************************************************/
s32 NetDNSDel(u32 dwEthId, u32 adwDNSset[], s32 dwNum);

/************************************************************
 * ������ : NetDNSAdd
 *
 * ���� : ����DNS
 *
 * ���� : ��
 *
 * ����˵�� :
 *      byEthId   - ���ں�(��0��ʼ)
 *      adwDNSset - dns����(������)
 *      dwNum     - dns ����
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ʧ��
 ***********************************************************/
s32 NetDNSAdd(u32 dwEthId, u32 adwDNSset[], s32 dwNum);


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif
