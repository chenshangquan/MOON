#ifndef _NETCBB_PING_H_
#define _NETCBB_PING_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* TPingCallBack�ص��ķ���ֵ����Ӧ����ΪnResult */
#define    NET_PING_REPLY          0    /* ping��������Ӧ */
#define    NET_PING_TIMEOUT        1    /* ping����ʱ */
#define    NET_PING_ERROR          2    /* ping��ϵͳ���� */
#define    NET_PING_NET_UNREACH    3    /* ping�����粻�ɴ� */


#define    NET_PING_CREAT_CB_THREAD_FAILED    (NET_PING_BASE_ERROR + 1)
#define    NET_PING_STASRT_FAILED             (NET_PING_BASE_ERROR + 2)
#define    NET_PING_STOP_FAILED               (NET_PING_BASE_ERROR + 3)
#define    NET_PING_ALREADY_START             (NET_PING_BASE_ERROR + 4)
#define    NET_PING_ALREADY_STOP              (NET_PING_BASE_ERROR + 5)


/* NetPing�ӿڴ�������ṹ�� */
typedef struct{
    s32 nPktSize;   /* Ҫping�����ݱ��Ĵ�С�����ֽ�Ϊ��λ����С��56�����С��56������ֵ56 */
    s32 nTimeOut;   /* ping�ĳ�ʱֵ������Ϊ��λ */
    s32 nTtl;       /* TTLֵ ���÷�Χ0-255, 0����255����ȡ��, ҵ������н������ƣ�����󲻳���255 */
    s32 nCount;     /* ping����Ŀ */
}TPingOpt;

/************************************************************
 * ������ : TNetPingCallBack
 *
 * ���� : ping�ص�����
 *
 * ���� :
 *
 * ����˵�� :
 *      nResult   - ping �ص����(NET_PING_REPLY, NET_PING_TIMEOUT, NET_PING_ERROR)
 *      nTtl      - TTLֵ
 *      nTripTime - ���紫��ʱ��ֵ(ע��:��λ��΢��, ���Ǻ���)
 *      nSeq      - ping������
 *      nUserID   - �û�ID��־���û����ֲ�ͬ���û�����(��ʱ��֧�ֶ��û�����
 *      nErrType  - ��������(��ʱ���Ժ���,��δ֧��)
 *      nErrCode  - ������(��ʱ���Ժ���,��δ֧��)
 * ����ֵ : ���ϲ�ҵ��ʵ��
 ***********************************************************/
typedef int(*TNetPingCallBack)(s32 nResult, s32 nTtl, s32 nTripTime, s32 nSeq, s32 nUserID, s32 nErrType, s32 nErrCode);

/************************************************************
 * ������ : NetPingStart
 *
 * ���� : ��̫��ping�ӿ�
 *
 * ���� :
 *
 * ����˵�� :
 *      dwDestIP       - Ping��Ŀ��IP��ַ(������)
 *      ptPingOpt      - Ping�Ĳ����ṹ��ָ��
 *      nUserID        - �û�ID��־���û����ֲ�ͬ���û�����(��ʱ��֧�ֶ��û����ã��븳ֵ0)
 *      ptCallBackFunc - Ping����Ļص�����
 * ����ֵ : ok - �ɹ�
 *          NET_CALLBACK_NULL  - �ص�����û�ж���
 *          NET_PING_CREAT_CB_THREAD_FAILED  - �����ص��߳�ʧ��
 *          NET_PING_STASRT_FAILED  - ����ʧ��
 ***********************************************************/
s32 NetPingStart(u32 dwDestIP, TPingOpt* ptPingOpt, s32 nUserID, TNetPingCallBack ptCallBackFunc);

/************************************************************
 * ������ : NetPing
 *
 * ���� : ��̫��ping��ֹ
 *
 * ���� :
 *
 * ����˵�� :
 *      nUserID        - �û�ID��־���û����ֲ�ͬ���û�����(��ʱ��֧�ֶ��û����ã��븳ֵ0)
 * ����ֵ : ok - �ɹ�
 *          NET_PING_STOP_FAILED  - ��ֹʧ��
 ***********************************************************/
s32 NetPingStop(s32 nUserID);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*_NETCBB_INTERFACE_H_*/

