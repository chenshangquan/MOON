/*=======================================================================
ģ����      : ZUSER����
�ļ���      : 
����ļ�    : 
�ļ�ʵ�ֹ���: 
����        : feixiaoping
�汾        : LTP Release 1.0
-------------------------------------------------------------------------
�޸ļ�¼:
��  ��				�汾		�޸���					�޸�����
2006/02/14			1.0			feixiaoping					����
=======================================================================*/
#ifdef LTP_NIP_TEST

#ifndef _ZUSR_TEST_H_
#define _ZUSR_TEST_H_

#include <sys/mman.h>

#if 0
enum preset_type
{
    PRE_DEL  = -1,         // �����
    TESTCASE,���������// ��������
    PRE_ADD       // �����
};
#endif


enum rtn_type
{
    ZUSR_TST_SUCCEED = 0,   // ���Գɹ�
    ZUSR_TST_WARNING,   // ����
    ZUSR_TST_FAILED,    // ����ʧ��
};

#if 1
enum preset_type
{
	PRE_DEL = -1,
	TESTCASE = 0,
	PRE_ADD = 1,
};
#endif

#define MAXZUSRLEN 256
#define NULL_STR "*"
/*------------------------------------*/
//struct for nip testing
struct zusr_add_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    int  id;
    char pstr_user[MAXZUSRLEN];
    char pstr_pass[MAXZUSRLEN];

    /* Ԥ�ڽ�� */
   int val;
   int     rtn;
};

/*------------------------------------*/
//struct for nip testing
struct zusr_get_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    int  id;
    char pstr_user[MAXZUSRLEN];
    char pstr_pass[MAXZUSRLEN];

    /* Ԥ�ڽ�� */
    int val;
    int     rtn;
};

/*------------------------------------*/
//struct for nip testing
struct zusr_del_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    int  id;
    char pstr_user[MAXZUSRLEN];
    char pstr_pass[MAXZUSRLEN];

    /* Ԥ�ڽ�� */
    int val;
    int     rtn;
};

/*------------------------------------*/
//struct for nip testing
struct zusr_check_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    int  id;
    char pstr_user[MAXZUSRLEN];
    char pstr_pass[MAXZUSRLEN];

    /* Ԥ�ڽ�� */
    int val;
    int     rtn;
};

/*interproc*/
/*------------------------------------*/
//struct for nip testing
struct zusr_add_interproc_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    int  id;
    char pstr_user[MAXZUSRLEN];
    char pstr_pass[MAXZUSRLEN];

    /* Ԥ�ڽ�� */
    int val;
    int     rtn;
};

/*------------------------------------*/
//struct for nip testing
struct zusr_del_interproc_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    int  id;
    char pstr_user[MAXZUSRLEN];
    char pstr_pass[MAXZUSRLEN];

    /* Ԥ�ڽ�� */
    int val;
    int     rtn;
};

/*------------------------------------*/
//struct for nip testing
struct zusr_check_interproc_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    int  id;
    char pstr_user[MAXZUSRLEN];
    char pstr_pass[MAXZUSRLEN];

    /* Ԥ�ڽ�� */
    int val;
    int     rtn;
};

/*------------------------------------*/
//struct for nip testing
struct zusr_get_interproc_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    int  id;
    char pstr_user[MAXZUSRLEN];
    char pstr_pass[MAXZUSRLEN];

    /* Ԥ�ڽ�� */
    int val;
    int     rtn;
};

#endif

#endif

