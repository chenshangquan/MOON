/*=======================================================================
ģ����      : ��̬·�ɲ���
�ļ���      : 
����ļ�    : 
�ļ�ʵ�ֹ���: 
����        : Jin Feng
�汾        : LTP Release 1.0
-------------------------------------------------------------------------
�޸ļ�¼:
��  ��				�汾		�޸���					�޸�����
2006/4/20			1.0			Jin Feng					����
=======================================================================*/

#ifndef _ZSTATIC_TEST_H_
#define _ZSTATIC_TEST_H_

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

#define NULL_STR "*"			// �����ԵĲ����У����ַ�����ʱ�����Ϊ��*�������ַ���ָ�븳ΪNULL
#define TC_FLAG(env) (env == -1)?"PRE_DEL :":(env == 0)?"TESTCASE:":(env == 1)?"PRE_ADD :":"UNKNOWN"

/*------------------------------------*/

struct zstatic_test_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    int   add_cmd;
    char  dest_str[MAXLTPLEN];    // Ŀ��·��
    char  mask_str[MAXLTPLEN];    // ·�ɵ���������
    char  gate_str[MAXLTPLEN];    // ·�ɵ�����
    char  distance_str[MAXLTPLEN];              // ·�����ȼ�
    int   errid;                 // add��delete  type
    /* Ԥ�ڽ�� */
   int  val;
   int  rtn;
};

/*------------------------------------*/
#endif
