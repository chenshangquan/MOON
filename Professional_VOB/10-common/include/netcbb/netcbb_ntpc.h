#ifndef _NETCBB_NTPC_H_
#define _NETCBB_NTPC_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#define NETCBB_NTPC_INTERVAL_MIN              (u32)5                           /* ������NTP-Servr����ʱ��ͬ����ʱ��������Сֵ */
#define NETCBB_NTPC_INTERVAL_MAX              (u32)1024                        /* ������NTP-Servr����ʱ��ͬ����ʱ���������ֵ */
#define NETCBB_NTPC_MSG_BASE                  (u32)30000                       /*NTP�е���������NTP-Serverͬ��ʱ��ʱ�ص���������Ϣ���ַ */
#define NETCBB_NTPC_SYNC_TIME_SUCCESS_MSG     (u32)(NETCBB_NTPC_MSG_BASE + 1)  /*��NTP-Serverͬ��ʱ��Уʱ�ɹ�����Ϣ�壺��*/
#define NETCBB_NTPC_SYNC_TIME_FAILED_MSG      (u32)(NETCBB_NTPC_MSG_BASE + 2)  /*��NTP-Serverͬ��ʱ��Уʱʧ�ܣ���Ϣ�壺��*/


/************************************************************
 * ������ : NetCbbNTPCSyncTimeCallBack
 *
 * ���� : ������ͬ��NTP-Serverͬ��ϵͳʱ��ʱ��֪ͨ�û���������Ļص�����
 *
 * ���� : ��
 *
 *
 * ����˵�� :
 *      dwMsgID   - �¼����ͣ����������Ϣ���Ͷ���
 *      pMsg      - ����¼�������ƥ�����Ϣ���ݣ�Ŀǰ������ΪNULL���Ժ������չ
 *
 * ����ֵ : ��ʱ����Ϊ0���Ժ������չ
 ***********************************************************/
typedef int(*NetCbbNtpcSyncTimeCallBack)(u32 dwMsgID, void* pMsg);


/************************************************************
 * ������ : NetCbbNTPCStart
 *
 * ���� : ����NTP-Client�˹���
 *
 * ���� : ��
 *
 *
 * ����˵��:
 *      dwServerIp          - NTP-Server��IP��ַ�������ֽ���
 *      dwSyncTimeInterval  - ��NTP-Server����ʱ��ͬ����ʱ����������Ϊ��λ����Χ��64s~1024s��
 *                            �����ù���֮�󣬵ײ�ᰴ���û����õ�ʱ������
 *                            ÿ��һ��ʱ�����NTP-Serverͬ��ϵͳʱ�䲢���õ�����ϵͳ��
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ʧ��
 ***********************************************************/
s32 NetCbbNtpcStart(u32 dwServerIp, u32 dwSyncTimeInterval, NetCbbNtpcSyncTimeCallBack ptCallBack);


/************************************************************
 * ������ : NetCbbNTPCStop
 *
 * ���� : �ر�NTP-Client�˹���
 *
 * ���� : ��
 *
 * ����˵�� :
 *        ��
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ʧ��
 ***********************************************************/
s32 NetCbbNtpcStop(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*_NETCBB_NTP_H_*/

