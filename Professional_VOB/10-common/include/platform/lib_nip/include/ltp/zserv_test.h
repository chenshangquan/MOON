/*=======================================================================
ģ����      : ZSERV�����շ�������ʹ�õ���������
�ļ���      : 
����ļ�    : 
�ļ�ʵ�ֹ���: 
����        : JinFeng
�汾        : LTP Release 1.0
-------------------------------------------------------------------------
�޸ļ�¼:
��  ��				�汾		�޸���					�޸�����
2006/04/11			1.0			Jinfeng					����
=======================================================================*/
#ifdef LTP_NIP_TEST

#ifndef _ZSERV_TEST_H_
#define _ZSERV_TEST_H_

enum preset_type
{
    PRE_DEL  = -1, 
    TESTCASE,
    PRE_ADD
};

enum rtn_type
{
    ZSERV_TST_SUCCEED = 0,   // ���Գɹ�
    ZSERV_TST_WARNING,   // ����
    ZSERV_TST_FAILED,    // ����ʧ��
};


#define MAXZIPCLEN 255
/*------------------------------------*/
//struct for nip testing
struct zserv_test_01
{
    /* Ԥ������ */      
        int setup_env;
    /* �������� */
        int  type;

    /* Ԥ�ڽ�� */
       int   val; 
       int   rtn;
};


#endif

#endif
