/*=======================================================================
ģ����      : MEMORYLIB����
�ļ���      : 
����ļ�    : 
�ļ�ʵ�ֹ���: 
����        : Chen Shuang
�汾        : LTP Release 1.0
-------------------------------------------------------------------------
�޸ļ�¼:
��  ��				�汾		�޸���					�޸�����
2006/05/30			1.0		Chen Shuang				����
=======================================================================*/

#ifndef _MEMORYLIB_TEST_H_
#define _MEMORYLIB_TEST_H_
#define NIP_RETURN_OK 0x0
#define NIP_RETURN_ERROR  (~0)
enum preset_type
{
    PRE_DEL  = -1, 
    TESTCASE,
    PRE_ADD
};

enum rtn_type
{
    API_TST_SUCCEED = 0,   // ���Գɹ�
    API_TST_WARNING,   // ����
    API_TST_FAILED,    // ����ʧ��
};

#ifndef MAXLTPLEN 
#define MAXLTPLEN 256
#endif

#define NULL_STR "*"			// �����ԵĲ����У����ַ�����ʱ�����Ϊ��*�������ַ���ָ�븳ΪNULL
#define TC_FLAG(env) (env == -1)?"PRE_DEL :":(env == 0)?"TESTCASE:":(env == 1)?"PRE_ADD :":"UNKNOWN"

/*------------------------------------*/
struct memorylib_test_01_t
{
	/*Ԥ������*/
	int setup_env;
	/*��������*/
	int mtype;
	size_t size;
	/*Ԥ�ڽ��*/
	int val;
	int rtn;
};

/*------------------------------------*/

struct memorylib_test_02_t
{
	/*Ԥ������*/
	int setup_env;
	/*��������*/
	int mtype;
	size_t size;
	/*Ԥ�ڽ��*/
	int val;
	int rtn;
};

/*------------------------------------*/

struct memorylib_test_03_t
{
	/*Ԥ������*/
	int setup_env;
	/*��������*/
	int mtype;
	int ptrstat;
	size_t size;
	/*Ԥ�ڽ��*/
	int val;
	int rtn;
};

/*------------------------------------*/

struct memorylib_test_04_t
{
	/*Ԥ������*/
	int setup_env;
	/*��������*/
	int mtype;
	int ptrstat;
	/*Ԥ�ڽ��*/
	int val;
	int rtn;
};

/*------------------------------------*/

struct memorylib_test_05_t
{
	/*Ԥ������*/
	int setup_env;
	/*��������*/
	int mtype;
	char str[MAXLTPLEN];
	/*Ԥ�ڽ��*/
	int val;
	int rtn;
};
#endif
