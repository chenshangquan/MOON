#ifndef _NETCBB_SERV_H
#define _NETCBB_SERV_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#ifndef NETCBBS_OS_ANDROID

#define NETSERVICE_TELNETD  "telnetd" /* �궨��telnetd */
#define NETSERVICE_SSH      "ssh"     /* �궨��ssh */
#define NETSERVICE_FTPD     "ftpd"    /* �궨��ftpd */
#define NETSERVICE_TFTPD    "tftpd"   /* �궨��tftpd */
#define NETSERVICE_HTTPD    "httpd"   /* �궨��httpd */

#define NETPROTO_TCP         "tcp"
#define NETPROTO_UDP         "udp"


typedef struct {
    s8  *pchServName;   /* ������ */
    u16  wPort;         /* ����˿ں� */
    s8  *pchProto;      /* Э������ */
    s8  *pchArgPath;
}TServInfo;


/************************************************************
 * ������ : NetServiceStart
 *
 * ���� : ����������
 *
 * ���� :
 *
 * ����˵�� :
 *      pchServName - ������
 *      ptParaM     - ָ��TServInfo �Ľṹ��ָ��
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 ***********************************************************/
s32 NetServiceStart(s8 *pchServName, TServInfo* ptParaM);


/************************************************************
 * ������ : NetServiceStop
 *
 * ���� : �رշ�����
 *
 * ���� :
 *
 * ����˵�� :
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 ***********************************************************/
s32 NetServiceStop(s8* pchServName, u16 wPort);

#else   /* NETCBBS_OS_ANDROID */

/* The service name below defined according to 'netstat -tap' */
#define NETSERVICE_TELNETD  "telnet"
#define NETSERVICE_FTPD     "ftp"
#define NETSERVICE_HTTPD    "webcache"

/* The service name below defined according to inetd.conf */
#define NET_TELNETD_CONF    "telnetd"
#define NET_FTPD_CONF       "ftpd"
#define NET_HTTPD_CONF      "httpd"

#define INETD_CONF_PATH     "/etc/inetd.conf"


/************************************************************
 * ������ : NetServiceFtpStart
 *
 * ���� : ����ftp����
 *
 * ���� :
 *
 * ����˵�� :
 *
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 ***********************************************************/
s32 NetServiceFtpStart();

/************************************************************
 * ������ : NetServiceFtpStop
 *
 * ���� : �ر�ftp����
 *
 * ���� :
 *
 * ����˵�� :
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 ***********************************************************/
s32 NetServiceFtpStop();

/************************************************************
 * ������ : NetServiceTelnetStart
 *
 * ���� : ����telnet����
 *
 * ���� :
 *
 * ����˵�� :
 *
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 ***********************************************************/
s32 NetServiceTelnetStart();

/************************************************************
 * ������ : NetServiceTelnetStart
 *
 * ���� : �ر�telnet����
 *
 * ���� :
 *
 * ����˵�� :
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 ***********************************************************/
s32 NetServiceTelnetStop();

/************************************************************
 * ������ : NetServiceHttpStart
 *
 * ���� : ����http����
 *
 * ���� :
 *
 * ����˵�� :
 *
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 ***********************************************************/
s32 NetServiceHttpStart();

/************************************************************
 * ������ : NetServiceHttpStop
 *
 * ���� : �ر�http����
 *
 * ���� :
 *
 * ����˵�� :
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 ***********************************************************/
s32 NetServiceHttpStop();

#endif /* NETCBBS_OS_ANDROID */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif