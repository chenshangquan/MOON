#ifndef _NETCBB_PPPOE_H_
#define _NETCBB_PPPOE_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#define PPPOE_VERSION               "2.4.5"                  /* PPPOEģ��İ汾�Ŷ��� */
#define PPPOE_DUMP_FILE             "/ramdisk/pppoeDump.txt" /* ��PPPOEģ��������Debugģʽʱ��һЩ��Ҫ��Ϣ������ļ�·�� */
#define PPPOE_LOG_FILE              "/ramdisk/pppoelog.txt"  /* ��PPPOEģ�����־�ļ�·�� */
#define MAX_USENAME_LEN             (u16)255                 /* PPPOE����ʱʹ�õ��û�������󳤶� */
#define MAX_PASSWORD_LEN            (u16)255                 /* PPPOE����ʱʹ�õ��������󳤶� */
#define MAX_SERVERNAME_LEN          (u16)255                 /* PPOE����ʱʹ�õ�ָ��ISP���������ֵ���󳤶� */
#define MAX_VERSION_LEN             (u16)255                 /* PPPOE�汾��Ϣ����󳤶� */
#define MIN_DIAL_RETRY              (u16)1                   /* ��С���ų��Դ��� */
#define MAX_DIAL_RETRY              (u16)10                  /* ��󲦺ų��Դ��� */
#define DEFAULT_DIAL_RETRY          (u16)3                   /* Ĭ�ϵĲ��ų��Դ����������ô�������Ϊ����ʧ�� */
#define MIN_LCP_ECHO_INTERVAL       (u16)1                   /* ��С�ķ���lcp-echo��ʱ���� */
#define MAX_LCP_ECHO_INTERVAL       (u16)255                 /* ���ķ���lcp-echo��ʱ���� */
#define DEFAULT_LCPECHO_INTERVAL    (u16)20                  /* ���ӽ����Ժ󣬷���LCP-ECHO����Ĭ��ʱ����(��λ����) */
#define MIN_LCPECHO_TIMEOUT         (u16)1                   /* ��С��lco-echo��ʱ���� */
#define MAX_LCPECHO_TIMEOUT         (u16)255                 /* ����lco-echo��ʱ���� */
#define DEFAULT_LCPECHO_TIMEOUT     (u16)3                   /* ���ӽ����Ժ󣬷���LCP-ECHO����Ĭ�ϳ�ʱ��ʱ */
#define MIN_AUTODIAL_INTERVAL       (u16)0                   /* ��С���Զ�����ʱ���� */
#define MAX_AUTODIAL_INTERVAL       (u16)10                  /* �����Զ�����ʱ���� */
#define DEFAULT_AUTODIAL_INTERVAL   (u16)1                   /* �������ٴ��Զ����ŵ�Ĭ�ϵȴ�ʱ��(��λ����) */

/* �ϲ�ҵ��������PPPOEģ��ӿ�ʱ������ֵͳһ���� */
#define PPPOE_OK                    (u16)0                   /* ���óɹ�ʱ�ķ���ֵ*/
#define PPPOE_INIT_NO_USERNAME      (u16)1                   /* û��ָ���û���ʱ�ķ���ֵ */
#define PPPOE_INIT_NO_PASSWORD      (u16)2                   /* û��ָ����½����ʱ�ķ���ֵ */
#define PPPOE_INIT_PARAM_INVALIDE   (u16)3                   /* ��ʼ��ʱ����Ĳ������������Сֵ��Χ֮�� */
#define PPPOE_START_NO_INIT         (u16)4                   /* û�г�ʼ�� */
#define PPPOE_START_NO_REGCALLBACK  (u16)5                   /* û��ע��ص����� */
#define PPPOE_CALLBACK_NULL         (u16)6                   /* ע��Ļص�����Ϊ��ָ�� */
#define PPPOE_NOT_RUNNING           (u16)7                   /* û�п���PPPOE���� */
#define PPPOE_PARAMETER_NULL        (u16)8                   /* ��ȡ�汾��Ϣʱ�����ָ��ΪNULL */
#define PPPOE_CREAT_PIPE_FAILED     (u16)9                   /* �����ܵ�ʧ�� */
#define PPPOE_CREAT_PROGRESS_FAILED (u16)10                  /* �����ӽ���ʧ�� */


/* ע�⣺�ϲ�ҵ����������յ���Щ��Ϣ�Ļص������н��й���Ĵ���Ӧ�þ��췵�أ������ܵ���pppoeģ���PppoeStart()��PppoeStop()������������������ */

/* PPPOEģ������ϲ�ҵ�����ע��Ļص���������֪ͨ��Ϣ����ϢID�Ŷ��� */
/* ��ϢID�Ļ�ַ--------����1ǧ����Ϣ���ԣ�9000--10000�� */
#define PPPOE_MSG_BASE              (u32)9000

/* ��Ϊ�û����������벻��ȷ�����PPPOEģ�鲦�������֤ʧ�ܵ�֪ͨ��Ϣ */
/* ��Ϣ����--- �ṹ��TAuthFailed */
#define PPPOE_AUTH_FAILED_MSG       (u32)(PPPOE_MSG_BASE + 1)
	
/* ���ų�ʱ֪ͨ��Ϣ */
/* ��Ϣ����--- �� */
#define PPPOE_DIAL_TIMEOUT_MSG      (u32)(PPPOE_MSG_BASE + 2)

/* ����֪ͨ��Ϣ,��Ϣ�������»�õ�IP��ַ */
/* ��Ϣ����--- �ṹ��TConnNotify */
#define PPPOE_LINK_UP_MSG           (u32)(PPPOE_MSG_BASE + 3)

/* ����֪ͨ��Ϣ */
/* ��Ϣ����--- �� */
#define PPPOE_LINK_DOWN_MSG         (u32)(PPPOE_MSG_BASE + 4)

/* �Ҳ���ָ����ISP������֪ͨ��Ϣ */
/* ��Ϣ����--- �ṹ�� TNoServer */
#define PPPOE_NO_REQUIREDSERVER_MSG (u32)(PPPOE_MSG_BASE + 5)
#define PPPOE_DIALING_MSG           (u32)(PPPOE_MSG_BASE + 6)

/* �Ҳ�������������ʱ����� */
#define PPPOE_GENERAL_SERVER_ERROR_MSG     (u32)(PPPOE_MSG_BASE + 7)


/* �ϲ�ҵ������ʼ��PPPOEģ��ʱʹ�õĽṹ�� */
typedef struct  PppoeInitParam{
    char      abyUserName [MAX_USENAME_LEN];     /* ����ʱʹ�õ��û���,������ */
    char      abyPassword [MAX_PASSWORD_LEN];    /* ����ʱʹ�õ�����,������ */
    char      abyServerName[MAX_SERVERNAME_LEN]; /* ָ�����ŷ����̵�����,���Բ��� */
    BOOL32    bAutoDialEnable;                   /* �Ƿ�����������Զ�����,Ĭ�ϲ��Զ�����,ֻ�������Զ����ź��ز��������ز�ʱ��������塣������Ч */
    BOOL32    bDefaultRouteEnable;               /* �Ƿ������Զ˵ĵ�ַ��ΪĬ�����أ�Ĭ�ϲ���Ϊ���� */
    BOOL32    bDebug;                            /* �Ƿ���debugģʽ����pppoe��Ĭ�ϲ�������debugģʽ */
    u32       dwAutoDialInterval;                /* �������ٴ��Զ�������Ҫ�ȴ���ʱ�䣨�������ó�0s��*/
    u16       wDialRetryTimes;                   /* ���ų��ԵĴ���������ﵽ�ô�����û����Ӧ�򲦺�ʧ��,Ĭ��Ϊ10��Ϊ0�������Ʋ��� */
    u16       wLcpEchoSendInterval;              /* ���ӽ����󣬷���LCP-ECHO����ʱ����,Ĭ������Ϊ20 */
    u16       wLcpEchoRetryTimes;                /* ���ͼ���LCP-ECHO��û�еõ���Ӧ����Ϊ���ӶϿ�,Ĭ������Ϊ3 */
    u32       dwEthID;                           /* PPPOE������Ҫ�󶨵���̫����ID�ţ���0��ʼ��*/
}TPppoeInitParam;



/*�ϲ�ҵ�����ע��Ļص����Ͷ���*/
/*����˵�� : u32 dwMsgID   - ��Ϣ��ID��,��PPPOEģ�����
             u8 *pbyMsg    - ָ����Ϣ���ݵ�ָ��,��PPPOEģ�����
             u32 dwMsgLen  - ��Ϣ���ݵ���Ч����,��PPPOEģ����� */
typedef void (*TPppoeCallBack)(u32 dwMsgID, u8* pbyMsg, u32 dwMsgLen);


/*�й�PPPOEģ�����ͳ����Ϣ�Ľṹ��*/
typedef struct PppoeStates{
    BOOL32  bPppoeRunning;                       /* PPPOE�Ƿ����У�TRUR�����У�FALSE��û������ */
    u32     dwLocalIpAddr;                       /* ����IP��ַ,������ */
    u32     dwPeerIpAddr;                        /* �Զ�IP��ַ,������ */
    char    abyServerName[MAX_SERVERNAME_LEN];   /* ISP Server������ */
    u32     dwLinkKeepTimes;                     /* ��·������ʱ�� */
    u32     dwLinkDownTimes;                     /* ��·�����Ĵ���ͳ�� */
    u32     dwPktsSend;                          /* �ܹ����͵����ݰ���--��������Э����Լ��ϲ�ҵ���������ݰ� */
    u32     dwPktsRecv;                          /* �ܹ����յ����ݰ��� */
    u32     dwBytesSend;                         /* �ܹ����͵��ֽ��� */
    u32     dwBytesRecv;                         /* �ܹ����յ��ֽ��� */
}TPppoeStates;

/* �����ϲ�ҵ�����ע��Ļص�����������֤ʧ��ʱ��Ϣ�����ݽṹ�� */
typedef struct AuthFailed{
    char  abyUserName[MAX_USENAME_LEN];          /* ҵ�������Ĳ���ʱʹ�õ��û��� */
    char  abyPassword[MAX_PASSWORD_LEN];         /* ҵ�������Ĳ���ʱʹ�õ����� */
}TAuthFailed;

/* �����ϲ�ҵ�����ע��Ļص��������ͽ���֪ͨ��Ϣ�Ľṹ�� */
typedef struct ConnNotify{
    u32  dwOurIpAddr;   /* ���ϻ�õ�IP��ַ,������ */
    u32  dwPeerIpAddr;  /* �Զ˵�IP��ַ */
    u32  dwDnsServer1;  /* DNS Server1,������ */
    u32  dwDnsServer2;  /* DNS Server1,������ */
}TConnNotify;

/* ֪ͨҵ������Ҳ���ָ����ISP Server����Ϣ�ṹ�� */
typedef struct NoServer{
    char  abyServerName[MAX_SERVERNAME_LEN]; /* ISP Server������ */
}TNoServer;

/*�洢PPPOE�汾��Ϣ�Ľṹ��*/
typedef struct Version{
    char  abyVersion[MAX_VERSION_LEN];
}TVersion;


/************************************************************
 * ������ : PppoeStart
 *
 * ���� : ����PPPoE����
 *
 * ���� : ԭPppoeInit��PppoeCallBackReg��������NetPppoeStart��		
 *
 * ����˵�� :
 *
 * ����ֵ : oK - �ɹ�
 *          ERROR - ʧ��
 *          �ο�netcbb_def.h
 ***********************************************************/
s32 NetPppoeStart(TPppoeInitParam* ptPppoeInitParam, TPppoeCallBack ptNotifyCallBack);

/************************************************************
 * ������ : PppoeStop
 *
 * ���� : ֹͣPPPoE����
 *
 * ���� :
 *
 * ����˵�� :
 *
 * ����ֵ : #define PPPOE_ OK           0
 *          #define PPPOE_NOT_RUNNING   6
 ***********************************************************/
s32 NetPppoeStop(void);

/************************************************************
 * ������ : NetPppoeStatesDump
 *
 * ���� : ��ȡPPPoEģ���ͳ����Ϣ
 *
 * ���� : ���ṩ֧��
 *
 * ����˵�� :
 *      ptPppoeStates - ָ����ͳ�ƽ����ָ��
 *
 * ����ֵ : ��
 ***********************************************************/
void NetPppoeStatesDump(TPppoeStates* ptPppoeStates);

/************************************************************
 * ������ : NetPppoeVer
 *
 * ���� : ��ȡPPPoEģ��İ汾��Ϣ
 *
 * ���� :
 * 
 * ����˵�� :
 *      ptVersion - ָ���Ű汾��Ϣ��ָ��
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ʧ��
 ***********************************************************/
s32 NetPppoeVer(TVersion* ptVersion);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _NETCBB_PPPOE_H_ */

