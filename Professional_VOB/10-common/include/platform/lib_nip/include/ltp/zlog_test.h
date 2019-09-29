/*=======================================================================
ģ����      : ZLOG����ʹ�ܼ��رչ���
�ļ���      :
����ļ�    :
�ļ�ʵ�ֹ���:
����        : LinZhe
�汾        : LTP Release 1.0
-------------------------------------------------------------------------
�޸ļ�¼:
��  ��				�汾		�޸���					�޸�����
2006/02/07			1.0			LinZhe					����
=======================================================================*/
#ifdef LTP_NIP_TEST

#ifndef _ZLOG_TEST_H_
#define _ZLOG_TEST_H_

enum preset_type
{
    PRE_DEL  = -1, 
    TESTCASE,
    PRE_ADD
};

enum
{
    ZLOG_TST_SUCCEED,   // ���Գɹ�
    ZLOG_TST_WARNING,   // ����
    ZLOG_TST_FAILED,    // ����ʧ��
};

#define ZLOGMAXLEN 255
#define NULL_STR "*"			// �����ԵĲ����У����ַ�����ʱ�����Ϊ��*�������ַ���ָ�븳ΪNULL
#define TC_FLAG(env) (env == -1)?"PRE_DEL :":(env == 0)?"TESTCASE:":(env == 1)?"PRE_ADD :":"UNKNOWN"

/*------------------------------------*/
//struct for nip testing
struct zlog_test_t
{
	int		setup_env;
    int     enable;
	int     priority;
	char    module[ZLOGMAXLEN];
    int     val;
    int     rtn;
};

#endif

#endif
