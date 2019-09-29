/*=======================================================================
ģ����      :  �ӿڹ������
�ļ���      : 
����ļ�    : 
�ļ�ʵ�ֹ���: 
����        : Jin Feng
�汾        : LTP Release 1.0
-------------------------------------------------------------------------
�޸ļ�¼:
��  ��				�汾		�޸���					�޸�����
2006/5/10			1.0			Jin Feng					����
=======================================================================*/

#ifndef _IFMANAGER_TEST_H_
#define _IFMANAGER_TEST_H_

enum preset_type
{
    PRE_DEL  = -1, 
    TESTCASE,
    PRE_ADD
};

enum rtn_type
{
    TST_SUCCEED = 0,   // ���Գɹ�
    TST_WARNING,   // ����
    TST_FAILED,    // ����ʧ��
};


#ifndef MAXLTPLEN 
#define MAXLTPLEN 255
#endif

#define RETURN_OK 0
#define RETURN_ERROR 1

#define NULL_STR "*"			// �����ԵĲ����У����ַ�����ʱ�����Ϊ��*�������ַ���ָ�븳ΪNULL
#define TC_FLAG(env) (env == -1)?"PRE_DEL :":(env == 0)?"TESTCASE:":(env == 1)?"PRE_ADD :":"UNKNOWN"

/*------------------------------------*/

struct ifmanager_test_01_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */

    /* Ԥ�ڽ�� */
   int  val;
   int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_02_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */

    /* Ԥ�ڽ�� */
   int  val;
   int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_03_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    int if_type;            
    char zebra[MAXLTPLEN];  
    char kernel[MAXLTPLEN]; 
    /* Ԥ�ڽ�� */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_04_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    int if_type;
    /* Ԥ�ڽ�� */
   int  val;
   int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_05_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char name[MAXLTPLEN];
    int type;
    int unit;
    /* Ԥ�ڽ�� */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_06_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    int ifindex; 
    /* Ԥ�ڽ�� */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_07_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ifname[MAXLTPLEN];
    /* Ԥ�ڽ�� */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_08_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    int if_type;
    int ifunit;  
    /* Ԥ�ڽ�� */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_09_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ipaddr[MAXLTPLEN];
    /* Ԥ�ڽ�� */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_10_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ipaddr[MAXLTPLEN];
    /* Ԥ�ڽ�� */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_11_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ifname[MAXLTPLEN];
    /* Ԥ�ڽ�� */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_12_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ifname[MAXLTPLEN];
    /* Ԥ�ڽ�� */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_13_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ifname[MAXLTPLEN];
    /* Ԥ�ڽ�� */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_14_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ifname[MAXLTPLEN];
    /* Ԥ�ڽ�� */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_15_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ifname[MAXLTPLEN];
    /* Ԥ�ڽ�� */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_16_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ifname[MAXLTPLEN];
    /* Ԥ�ڽ�� */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_17_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ifname[MAXLTPLEN];
    /* Ԥ�ڽ�� */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_18_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ifname[MAXLTPLEN];
    /* Ԥ�ڽ�� */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_19_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    int ifindex;
    char ifname[MAXLTPLEN];
    /* Ԥ�ڽ�� */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_20_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    int ifindex;
    char ifname[MAXLTPLEN];
    /* Ԥ�ڽ�� */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_21_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ifname[MAXLTPLEN];
    /* Ԥ�ڽ�� */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_22_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ifinfo[MAXLTPLEN];
    /* Ԥ�ڽ�� */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_23_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char nodeinfo[MAXLTPLEN];
    /* Ԥ�ڽ�� */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_24_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ztype[MAXLTPLEN];
    /* Ԥ�ڽ�� */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_25_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ztype[MAXLTPLEN];
    /* Ԥ�ڽ�� */
    int  val;
    int  rtn;
};
/*------------------------------------*/
#endif
