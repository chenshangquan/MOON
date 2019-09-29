#ifndef _NETCBB_TRACEROUTE_H_
#define _NETCBB_TRACEROUTE_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* TNetTracerouteCallBack ����ֵ����ӦTNetTracerouteCallBack �� nResult ���� */
#define  NET_TRACEROUTE_CB_ERROR                               101
#define  NET_TRACEROUTE_CB_TIMEOUT                             102
#define  NET_TRACEROUTE_CB_MIDDLE_ROUTE                        103
#define  NET_TRACEROUTE_CB_REACH_DST                           104
#define  NET_TRACEROUTE_CB_NETWORK_UNREACHABLE                 105
#define  NET_TRACEROUTE_CB_HOST_UNREACHABLE                    106        /* �ص�������ʱ traceroute���Զ�ֹͣ */

#define  NET_TRACEROUTE_CREAT_CB_THREAD_FAILED                 (NET_TRACEROUTE_BASE_ERROR + 1)
#define  NET_TRACEROUTE_STASRT_FAILED                          (NET_TRACEROUTE_BASE_ERROR + 2)
#define  NET_TRACEROUTE_STOP_FAILED                            (NET_TRACEROUTE_BASE_ERROR + 3)
#define  NET_TRACEROUTE_CREAT_SEM_FAILED                       (NET_TRACEROUTE_BASE_ERROR + 4)

typedef struct
{
    u32 dwDstIp;               /* ������ip��ַ */
    u32 dwTtl;                 /* TTLֵ ���÷�Χ0-255, 0����255����ȡ��, ҵ������н������ƣ�����󲻳���255 */
}TTraceroutePara;

/************************************************************
 * ������ : TNetTracerouteCallBack
 *
 * ���� : Traceroute �ص�����
 *
 * ���� : ��
 *
 * ����˵�� :
 *      nResult    - Traceroute �ص����(NET_TRACEROUTE_CB_ERROR, NET_TRACEROUTE_CB_TIMEOUT, 
 *                                             NET_TRACEROUTE_CB_MIDDLE_ROUTE, NET_TRACEROUTE_CB_REACH_DST)
 *      nTtl       - TTLֵ
 *      nTripTime  - ���紫��ʱ��ֵ(ע��:��λ��΢��, ���Ǻ���)
 *      dwIp       - ·��ip��ַ
 *      achDomName - ·������(�ݲ�֧��)
 *      nUserID    - �û�ID��־���û����ֲ�ͬ���û�����(��ʱ��֧�ֶ��û����ã���ֵ0)
 *      nErrType   - ��������(��ʱ���Ժ���,��δ֧��)
 *      nErrCode   - ������(��ʱ���Ժ���,��δ֧��)
 *
 * ����ֵ : ���ϲ�ҵ��ʵ��
 ***********************************************************/
typedef int(*TNetTracerouteCallBack)(s32 nResult, s32 nTtl, s32 nTripTime, u32 dwIp, s8* achDomName, s32 nUserID, s32 nErrType, s32 nErrCode);

/************************************************************
 * ������ : NetTracerouteStart
 *
 * ���� : ��̫��Traceroute��ʼ
 *
 * ���� : ��
 *
 * ����˵�� :
 *      ptTraceroutePara   - traceroute ����
 *      nUserID            - �û�ID��־���û����ֲ�ͬ���û�����(��ʱ��֧�ֶ��û����ã��븳ֵ0)
 *      ptCallBackFunc     - traceroute����Ļص�����
 *
 * ����ֵ : NET_CALLBACK_NULL                       - �ص�����û�ж���
 *          NET_TRACEROUTE_CREAT_CB_THREAD_FAILED   - �����ص��߳�ʧ��
 *          NET_TRACEROUTE_CREAT_SEM_FAILED         - �����ź���ʧ��
 *          NET_TRACEROUTE_STASRT_FAILED            - ����ʧ��
 *          OK                                      - �ɹ�
 ***********************************************************/
s32 NetTracerouteStart(TTraceroutePara* ptTraceroutePara, s32 nUserID, TNetTracerouteCallBack ptCallBackFunc);

/************************************************************
 * ������ : NetTracerouteStop
 *
 * ���� : ��̫��Traceroute��ֹ
 *
 * ���� : ��
 *
 * ����˵�� :
 *      nUserID            - �û�ID(��ʱ��֧�֣��븳ֵ0)
 *
 * ����ֵ : NET_TRACEROUTE_STOP_FAILED   - ��ֹʧ��
 *          OK                           - �ɹ�
 ***********************************************************/
s32 NetTracerouteStop(s32 nUserID);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _NETCBB_INTERFACE_H_ */

