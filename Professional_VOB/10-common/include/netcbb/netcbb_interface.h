#ifndef _NETCBB_INTERFACE_H_
#define _NETCBB_INTERFACE_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* ��̫����صĽṹ���� */
/* ��̫�������ṹ */
typedef struct{
    u32 dwIpAdrs;  /* �����ֽ��� */
    u32 dwIpMask;  /* �����ֽ��� */
    u8 byMacAdrs[6];
}TNetEthParam;

/* ��̫��mac��ַ�ṹ */
typedef struct{
    u8 byMacAdrs[6];
}TNetEthMac;

/* ��̫�������ṹ */
typedef struct{
    u32 dwIpNum;                                  /* ��Ч��IP��ַ�� */
    TNetEthParam atNetEthParam[IP_ADDR_MAX_NUM];  /* ���IP��ַ����Ϣ������ */
}TNetEthParamAll;

/* ����·�ɲ����ṹ */
typedef struct{
    u32 byEthId;         /* ����id */
    u32 dwDesIpNet;      /* Ŀ�������������ֽ��� */
    u32 dwDesIpMask;     /* ���룬�����ֽ��� */
    u32 dwGwIpAdrs;      /* ����ip��ַ�������ֽ��� */
    u32 dwRoutePri;      /* ·�����ȼ�(1-255)��Ĭ��Ϊ0 */
}TNetIpRouteParam;

/* ���·�ɲ����ṹ */
typedef struct{
    u32 dwIpRouteNum;    /* �õ���ʵ��·�ɸ��� */
    TNetIpRouteParam tNetIpRouteParam[IP_ROUTE_MAX_NUM];
}TNetAllIpRouteInfo;


#define NETCBB_IP_CONFLICT    1
#define NETCBB_MAC_CONFLICT   2

/* IP��ַ��ͻ�ص��������Ͷ��� */
typedef void (*TIpConflictCallBack)(u32 dwType, u8* pbyMacAddr, u32 dwIpAdrs);

/************************************************************
 * ������ : NetGetEthParam
 *
 * ���� : ��ȡ��̫����������ip��mask��mac
 *
 * ���� : ��
 *
 * ����˵�� :
 *      byEthId       - ��̫��ID�ţ�0~x��
 *      ptNetEthParam -�����̫����Ϣ�Ľṹָ��
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ʧ��
 ***********************************************************/
s32 NetGetEthParam(u32 byEthId, TNetEthParam* ptNetEthParam);

/************************************************************
 * ������ : NetGetEthMac
 *
 * ���� : ��ȡ��̫����������ip��mask��mac
 *
 * ���� : ��api���ṩ֧�֣���NetGetEthParam���غϵط�
 *
 * ����˵�� :
 *      byEthId       - ��̫��ID�ţ�0~x��
 *      ptNetEthMac   - �����̫��mac��Ϣ�Ľṹָ��
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ʧ��
 ***********************************************************/
s32 NetGetEthMac(u32 byEthId, TNetEthMac* ptNetEthMac);

/************************************************************
 * ������ : NetGetEthParamAll
 *
 * ���� : ��ȡһ�����������е���̫�����������IP��ַ�����
 *
 * ���� :
 * 
 * ����˵�� :
 *      byEthId          - ��̫��ID�ţ�0~x��
 *      ptNetEthParamAll - �����̫����Ϣ�Ľṹָ��
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ʧ��
 ***********************************************************/
s32 NetGetEthParamAll(u32 byEthId, TNetEthParamAll* ptNetEthParamAll);

/************************************************************
 * ������ : NetGetEthParamSecIP
 *
 * ���� : ��ȡһ�����������еڶ�IP��ַ
 *
 * ���� : ���ṩ֧�֣���NetGetEthParamAll�ظ�����ȡNetGetEthParamAll
 *        �ĵ�2��3������Ի�ȡ����Ӧ��ip��
 * 
 * ����˵�� :
 *      byEthId          - ��̫��ID�ţ�0~x��
 *      ptNetEthParamAll - �����̫����Ϣ�Ľṹָ��
 *                         ���ڷ��صڶ�IP��ַ�ģ����صĵ�ַ������
 *                         dwIpNumָ�����ṹ�е�atNetEthParam�����Ա
 *                         ֻ��IP��Mask��Ч��Mac��ַû��Ч
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ʧ��
 ***********************************************************/
s32 NetGetEthParamSecIP(u32 byEthId, TNetEthParamAll* ptNetEthParamAll);

/************************************************************
 * ������ : NetSetEthParam
 *
 * ���� : ������̫������
 *
 * ���� : 
 * 
 * ����˵�� :
 *      byEthId      - ��̫��ID�ţ�0~x��
 *      byIpOrMac    - Ϊ��������ѡ�񣨼�Netcbb_def.h����صĺ궨�壩������
 *                     ������IP���ڶ�IP��Mac
 *                        Net_SET_IP_AND_MASK    1   ����IP��ַ����������
                          Net_SET_MAC_ADDR       2   ����MAC��ַ(��mac���ܲ�֧�֣���ʵ������)
                          Net_SET_ETH_ALL_PARAM  3   ������̫����IP��ַ�����������MAC��ַ(��֧��)
                          Net_SET_ETH_SEC_IP     4   ������̫���ڶ�IP ��ַ
 *      ptNetEthParam - ָ�����趨ֵ��TNetEthParam���ݽṹ��ָ��
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ϵͳ����
 *          NET_INVALID_PARAMETER - ���������Ч
 ***********************************************************/
s32 NetSetEthParam(u32 byEthId, u32 byIpOrMac, TNetEthParam* ptNetEthParam);

/************************************************************
 * ������ : NetDelEthParamSecIP
 *
 * ���� : ɾ���ڶ�IP��ַ
 *
 * ���� : ���ṩ֧�֣���NetDelEthParamIPAndMask�ظ�
 *
 * ����˵�� :
 *      byEthId       - ��̫��ID�ţ�0~x����x�Ӳ�ͬ�İ��Ӷ���
 *      ptNetEthParam - ָ�����趨ֵ��TNetEthParam���ݽṹ��ָ�룬�ṹ��ֻ��IP��Mask��Ч
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ϵͳ����
 *          NET_INVALID_PARAMETER - ���������Ч
 ***********************************************************/
s32 NetDelEthParamSecIP(u32 byEthId, TNetEthParam* ptNetEthParam);

/************************************************************
 * ������ : NetAddEthParamIPAndMask
 * 
 * ���� : ����ָ��IP��ַ
 *
 * ���� : ���ṩ֧�֣���NetDelEthParamIPAndMask�ظ�
 * 
 * ����˵�� :
 *      byEthId       - ��̫��ID�ţ�0~x����x�Ӳ�ͬ�İ��Ӷ���
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 ***********************************************************/
s32 NetAddEthParamIPAndMask(u32 byEthId, TNetEthParam* ptNetEthParam);

/************************************************************
 * ������ : NetDelEthParamIPAndMask
 *
 * ���� : ɾ��ָ��IP��ַ
 *
 * ���� :
 *
 * ����˵�� :
 *      byEthId       - ��̫��ID�ţ�0~x��
 *      ptNetEthParam - ָ�����趨ֵ��TNetEthParam���ݽṹ��ָ��
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 ***********************************************************/
s32 NetDelEthParamIPAndMask(u32 byEthId, TNetEthParam* ptNetEthParam);

/************************************************************
 * ������ : NetDelEthParam
 *
 * ���� : ɾ��ָ������̫���ӿ�
 *
 * ���� : ��Linux�£�һ�����ڿ������ö��IP��ַ���ýӿڻ�ɾ��
 *        �ýӿ��ϵ�����IP��ַ
 *
 * ����˵�� :
 *      byEthId       - ��̫��ID�ţ�0~x����x�Ӳ�ͬ���Ӷ���
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 ***********************************************************/
s32 NetDelEthParam(u32 byEthId);

/************************************************************
 * ������ : NetSetDefGateway
 *
 * ���� : ����Ĭ������ip
 *
 * ���� : 
 *
 * ����˵�� :
 *      byEthId     - ��̫��ID�ţ�0~x��
 *      dwGateway   - Ĭ������ip��ַ�������ͣ�������
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 ***********************************************************/
s32 NetSetDefGateway(u32 byEthId, u32 dwGateway);

/************************************************************
 * ������ : NetGetDefGateway
 *
 * ���� : ��ȡĬ������ip
 *
 * ���� :
 *
 * ����˵�� :
 *      byEthId     - ��̫��ID�ţ�0~x��
 *      pdwGateway  - Ĭ������ip��ַ�������ͣ�������
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 ***********************************************************/
s32 NetGetDefGateway(u32 byEthId, u32* pdwGateway);

/************************************************************
 * ������ : NetDelDefGateway
 *
 * ���� : ɾ��Ĭ������ip
 *
 * ���� :
 *
 * ����˵�� :
 *      byEthId     - ��̫��ID�ţ�0~x��
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 ***********************************************************/
s32 NetDelDefGateway(u32 byEthId);

/************************************************************
 * ������ : NetSetMtu
 *
 * ���� : ����ĳһ������MTUֵ
 *
 * ���� :
 *
 * ����˵�� :
 *      byEthId   - ��̫��ID�ţ�0~x��
 *      dwMtu     - ���õ�MTUֵ
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 *          NET_IF_BUSY - ��������ʹ���У�����ʧ��
 ***********************************************************/
s32 NetSetMtu(u32 byEthId, u32 dwMtu);

/************************************************************
 * ������ : NetGetMtu
 *
 * ���� : ��ȡĳһ������MTUֵ
 *
 * ���� :
 *
 * ����˵�� :
 *      byEthId   - ��̫��ID�ţ�0~x��
 *      pdwMtu    - �洢mtuֵ��bufferָ��
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 ***********************************************************/
s32 NetGetMtu(u32 byEthId, u32* pdwMtu);

/************************************************************
 * ������ : NetGetNextHopIpAddr
 *
 * ���� : ��ȡͨ��ָ��ip�ĵ�һ��·��ip��ַ
 *
 * ���� : �ݲ�֧�֣����岻��ʵ�ֽ��鷳����ȫ������NetPing
 *        ���жϵ�ַ�Ƿ���Ե���
 *
 * ����˵�� :
 *      dwDstIpAddr  - Ŀ��ip��ַ�������ͣ�������
 *      dwDstMask    - Ŀ�����룬�����ͣ�������
 *
 * ����ֵ : �ɹ����ص�һ��·��ip��ַ��������
 ***********************************************************/
u32 NetGetNextHopIpAddr(u32 dwDstIpAddr, u32 dwDstMask);

/************************************************************
 * ������ : NetAddOneIpRoute
 *
 * ���� : ����һ��·
 *
 * ���� :
 *
 *
 * ����˵�� :
 *      byEthId   - ��̫��ID�ţ�0~x��
 *      ptNetIpRouteParam    - ָ����·����Ϣ��TNetIpRouteParam�ṹָ��
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 ***********************************************************/
s32 NetAddOneIpRoute(u32 byEthId, TNetIpRouteParam* ptNetIpRouteParam);

/************************************************************
 * ������ : NetDelOneIpRoute
 *
 * ���� : ɾ��һ��·
 *
 * ���� :
 *
 *
 * ����˵�� :
 *      byEthId   - ��̫��ID�ţ�0~x��
 *      ptNetIpRouteParam    - ָ����·����Ϣ��TNetIpRouteParam�ṹָ��
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 ***********************************************************/
s32 NetDelOneIpRoute(u32 byEthId, TNetIpRouteParam* ptNetIpRouteParam);

/************************************************************
 * ������ : NetGetAllIpRoute
 *
 * ���� : ��ȡ����·����Ϣ
 *
 * ���� :
 *
 *
 * ����˵�� :
 *      ptNetIpRouteParam    - ָ����·����Ϣ��TNetIpRouteParam�ṹָ��
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 ***********************************************************/
s32 NetGetAllIpRoute(TNetAllIpRouteInfo* ptNetAllIpRouteInfo);

/************************************************************
 * ������ : NetIpConflictCallBackReg
 *
 * ���� : ע��ip��ַ��ͻʱ�ص�����,���豸��IP��ַ���ⲿ�豸��
 *        ͻʱ������øú���֪ͨҵ�����
 *
 * ���� :
 *
 *
 * ����˵�� :
 *      ptFunc    - ִ��ҵ�����ע��Ļص�����ָ��
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 ***********************************************************/
s32 NetIpConflictCallBackReg(TIpConflictCallBack ptFunc);

/************************************************************
 * ������ : NetIpOnceConflicted
 *
 * ���� : ��ѯϵͳ�Ƿ�����ip��ַ��ͻ
 *
 * ���� :
 *
 *
 * ����˵�� :
 *      ��
 *
 * ����ֵ : TRUE or FALSE
 ***********************************************************/
BOOL32 NetIpOnceConflicted(void);

/************************************************************
 * ������ : NetSetDscp
 *
 * ���� : ����ip��ͷdscpֵ(0-63)
 *
 * ���� :
 *
 *
 * ����˵�� :
 *      nSockfd    - Ҫ���õ��׽���������
 *      byDscp     - Ҫ���õ�dscpֵ(0-63)
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 ***********************************************************/
s32 NetSetDscp(s32 nSockfd, u8 byDscp);

/************************************************************
 * ������ : NetInterfaceShutdown
 *
 * ���� : �ر���ѡ�ӿ�
 *
 * ���� :
 *
 *
 * ����˵�� :
 *      byEthId    - ��̫���ı��
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 ***********************************************************/
s32 NetInterfaceShutdown(u32 byEthId);

/************************************************************
 * ������ : NetInterfaceNoShutdown
 *
 * ���� : ����ѡ�ӿ�
 *
 * ���� :
 *
 *
 * ����˵�� :
 *      byEthId    - ��̫���ı��
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 ***********************************************************/
s32 NetInterfaceNoShutdown(u32 byEthId);

/************************************************************
 * ������ : NetCheckTheSameNet
 *
 * ���� : У���������
 *
 * ���� :
 *
 *
 * ����˵�� :
 *      dwIpAddr  - ip ��ַ
 *      dwMask    - ����
 *      dwGateway - ����
 *
 * ����ֵ : OK    - У��ɹ�, ��ͬһ������
 *          NET_NOT_THE_SAME_NET  - ����ͬһ������
 *          NET_INVALID_PARAMETER - �����������
 ***********************************************************/
s32 NetCheckTheSameNet(u32 dwIpAddr, u32 dwMask, u32 dwGateway);

/************************************************************
 * ������ : NetGetEthNum
 *
 * ���� : �����������
 *
 * ���� :
 *
 * ����˵�� :
 *      pnEthNum  - ָ����Ҫ��ȡ��������
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 ***********************************************************/
s32 NetGetEthNum(s32* pnEthNum);

/************************************************************
 * ������ : NetGetEthState
 *
 * ���� : ��ȡ����״̬
 *
 * ���� :
 *
 *
 * ����˵�� :
 *      nEthNum  - ָ����Ҫ��ȡ��������
 *      pdwFlag  - ����״̬��NET_IF_UP     ����up
 *                           NET_IF_DOWN   ����down
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 ***********************************************************/
s32 NetGetEthState(s32 nEthNum, u32* pdwFlag);

/************************************************************
 * ������ : NetModifyNetPwd
 *
 * ���� : �����������Э������ (�漰��Э����ftp telnet ssh)
 *
 * ���� :
 *
 *
 * ����˵�� :
 *      pUser    - �û���
 *      pPasswd  - �û���������
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 ***********************************************************/
s32 NetModifyNetPwd(s8* pUser, s8* pPasswd);

/************************************************************
 * ������ : NetAddNetUser
 *
 * ���� : �����û�(�漰��Э����ftp telnet ssh)
 *
 * ���� :
 *
 *
 * ����˵�� :
 *      pUser    - �û���
 *      pPasswd  - �û���������
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 ***********************************************************/
s32 NetAddNetUser(s8* pUser, s8* pPasswd);

/************************************************************
 * ������ : NetDelNetUser
 *
 * ���� : ɾ���û�(�漰��Э����ftp telnet ssh)
 *
 * ���� :
 *
 *
 * ����˵�� :
 *      pUser    - �û���
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 ***********************************************************/
s32 NetDelNetUser(s8* pUser);

/************************************************************
 * ������ : NetModifyIpRouteMetric
 *
 * ���� : �޸�һ��·�ɵ�metric
 *
 * ���� :
 *
 *
 * ����˵�� :
 *      ptNetIpRouteParam    - ָ����·����Ϣ��TNetIpRouteParam�ṹָ��
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 ***********************************************************/
s32 NetModifyIpRouteMetric(TNetIpRouteParam* ptNetIpRouteParam);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _NETCBB_INTERFACE_H_ */
