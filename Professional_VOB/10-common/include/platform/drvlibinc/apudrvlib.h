
#ifndef INCApuDrvLibh
#define INCApuDrvLibh


#ifdef __cplusplus 
extern "C" { 
#endif /* __cplusplus */

#include "time.h"
#include "timers.h"

#define VER_APUVxNIP      ( const char * )"APUVxNIP 30.01.07.10.041016"

/*================================ʱ��ģ������====================================*/
/* ʱ��ṹ˵�� */
/*����ϵͳ��׼tm�ṹ���ɲο�tornado��ذ����ĵ�
int tm_sec;  seconds after the minute  - [0, 59] 
int tm_min;  minutes after the hour    - [0, 59] 
int tm_hour;  hours after midnight     - [0, 23] 
int tm_mday;  day of the month         - [1, 31] 
int tm_mon;  months since January      - [1-1, 12-1]    ע��: 0 = һ�£�������淶����
int tm_year;  years since 1900         - [1980-1900,2079-1900]  ע��:������淶����
int tm_wday;  days since Sunday        - [0, 6]   ��֧�֣�����0
int tm_yday;  days since January 1     - [0, 365] ��֧�֣�����0 
int tm_isdst;  Daylight Saving Time flag [ 0 ]    ��֧�֣�����0

/* ʱ�亯������ */

STATUS BrdTimeGet( struct tm* pGettm );        /* ��ȡRTCʱ�� */
STATUS BrdTimeSet( struct tm* pSettm );        /* ����RTC��ϵͳʱ�� */ 


/*==============================�ײ�澯ģ�鲿��====================================*/
/* �ײ�澯��Ϣ�ṹ���� */
typedef struct{
    BOOL bAlarmDSP1FanStop;     /* ͼ��������ͣת */
    BOOL bAlarmDSP2FanStop;     /* ͼ��������ͣת */
    BOOL bAlarmDSP3FanStop;     /* ��Ƶ��������ͣת */
}TBrdIMTAlarmAll;

/* ģ�麯������ */


/*==============================����ת�ټ��ģ��====================================*/
/* ����ID�궨�� */
#define IMT_DSP1FAN       0         /* ͼ�������� */
#define IMT_DSP2FAN       1         /* ͼ�������� */
#define IMT_DSP3FAN       2         /* ��Ƶ�������� */

/* ģ�麯������ */


/* ģ�麯������ */
void BrdVideoMatrixSet
    (
    UINT8 vedioInSelect,    /* ��Ƶ����Դѡ��1~7 = 7����Ƶ����ӿڣ�1������Ӳ���ڲ�
                                              �ѽ���������ͼ�񣬶������Ρ�
                                              ������Ӧ�������ʹ�����涨��ĺ� */
    UINT8 vedioOutSelect   /* ��Ƶ����˿�ѡ��1~7 = 7����Ƶ����ӿڣ�1�����Ӳ���ڲ�
                                              �ѽ�����������Դ���������Ρ����ౣ����*/
    );


/*==============================�ײ�Ӳ���汾��Ϣ=============================*/  
#define BOARD_VERSION         ((UINT8)0x00)
#define EPLD_VERSION          ((UINT8)0x01)

STATUS BrdVersionGet(UINT8 module, UINT8 *pVersion);    


/*==============================��ƵԴ���=============================*/  
/* �궨�� */
#define VIDEOIN_CHKERROR   -1   /* ��Ƶ����оƬMAP[1]û�д������������� */
#define VIDEOIN_OFF         0   /* ��ѡ���������ƵԴ���ź� */
#define VIDEOIN_ON          1   /* ��ѡ���������ƵԴ���ź� */

int BrdVideoInCheck(void);        /* ��ƵԴ���,����ֵ���Ϻ궨�� */

/* ָʾ��״̬���ݽṹ */
typedef struct{
    UINT8 byLedRun; 
    UINT8 byLedDSP1;
    UINT8 byLedDSP2;
    UINT8 byLedDSP3;
    UINT8 byLedSYSALM;
    UINT8 byLedMLINK;
    UINT8 byLedLNK0;
    UINT8 byLedLNK1;
}TBrdIMTLedStateDesc;

STATUS BrdIMTQueryLedState(TBrdIMTLedStateDesc *ptBrdIMTLedState);

#ifdef __cplusplus 
} 
#endif /* __cplusplus */

#endif   /*INCDriverInith*/
