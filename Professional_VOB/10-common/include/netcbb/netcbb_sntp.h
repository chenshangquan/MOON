#ifndef _NETCBB_SNTP_H_
#define _NETCBB_SNTP_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



#define SNTP_INTERVEL_MIN            (u32)64                 /* ������SNTP-Servr����ʱ��ͬ����ʱ��������Сֵ */
#define SNTP_INTERVEL_MAX            (u32)1024               /* ������SNTP-Servr����ʱ��ͬ����ʱ���������ֵ */
#define SNTP_MSG_BASE                (u32)40000              /* SNTP�е���������SNTP-Serverͬ��ʱ��ʱ�ص���������Ϣ���ַ */
#define SNTP_SYNC_TIME_SUCCESS_MSG   (u32)( SNTP_MSG_BASE+1) /* ��SNTP-Serverͬ��ʱ��Уʱ�ɹ�����Ϣ�壺�� */
#define SNTP_SYNC_TIME_FAILED_MSG    (u32)( SNTP_MSG_BASE+2) /* ��SNTP-Serverͬ��ʱ��Уʱʧ�ܣ���Ϣ�壺�� */


/************************************************************
 * ������ : NetSNTPSyncTimeCallBack
 *
 * ���� : ������ͬ��SNTP-Serverͬ��ϵͳʱ��ʱ��֪ͨ�û���������Ļص�����
 *
 * ���� :
 *
 * ����˵�� :
 *      dwMsgID    - �¼����ͣ����������Ϣ���Ͷ���
 *      pMsg       - ����¼�������ƥ�����Ϣ���ݣ�Ŀǰ������ΪNULL���Ժ������չ
 *
 * ����ֵ : ��ʱ����Ϊ0���Ժ������չ
 ***********************************************************/
typedef int(*NetSNTPSyncTimeCallBack)(u32 dwMsgID, void* pMsg);

/************************************************************
 * ������ : NetSNTPStart
 *
 * ���� : ����SNTP-Client�˹���
 *
 * ���� :
 *
 * ����˵�� :
 *      dwServerIp         - SNTP-Server��IP��ַ�������ֽ���
 *      dwSyncTimeInterval - ��SNTP-Server����ʱ��ͬ����ʱ������
 *                               ����Ϊ��λ����Χ��64s~1024s�������ù���֮�󣬵ײ�
 *                               �ᰴ���û����õ�ʱ������ÿ��һ��ʱ�����
 *                               SNTP-Serverͬ��ϵͳʱ�䲢���õ�����ϵͳ��
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ʧ��
 ***********************************************************/
s32 NetSNTPStart(u32 dwServerIp, u32 dwSyncTimeInterval, NetSNTPSyncTimeCallBack ptCallBack);

/************************************************************
 * ������ : NetSNTPStop
 *
 * ���� : �ر�SNTP-Client�˹���
 *
 * ���� :
 *
 *
 * ����˵�� :
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ʧ��
 ***********************************************************/
s32 NetSNTPStop(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _NETCBB_SNTP_H_ */

