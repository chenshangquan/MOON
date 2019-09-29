#ifndef _CONFIG_TEST_H_
#define  _CONFIG_TEST_H_
#ifndef CMD_SUCCESS
#define CMD_SUCCESS  0
#endif
#ifndef CMD_WARNING
#define CMD_WARNING 1
#endif
enum preset_type
{
    PRE_DEL  = -1, 
    TESTCASE,
    PRE_ADD
};

enum rtn_type
{
    CFG_TST_SUCCEED = 0,   // ���Գɹ�
    CFG_TST_WARNING,   // ����
    CFG_TST_FAILED    // ����ʧ��
};

#ifndef MAXLTPLEN 
#define MAXLTPLEN 256
#endif
#ifndef FILENAME_MAX_LEN
#define FILENAME_MAX_LEN  32
#endif
#define NULL_STR "*"			// �����ԵĲ����У����ַ�����ʱ�����Ϊ��*�������ַ���ָ�븳ΪNULL
#define TC_FLAG(env) (env == -1)?"PRE_DEL :":(env == 0)?"TESTCASE:":(env == 1)?"PRE_ADD :":"UNKNOWN"

struct config_test_01_t 
{
	/* Ԥ������ */      
    int setup_env;
    /* Ԥ�ڽ�� */
   int  val;
   int  rtn;
};
struct config_test_02_t 
{
	/* Ԥ������ */      
    int setup_env;
    /* Ԥ�ڽ�� */
   int  val;
   int  rtn;
};
struct config_test_03_t 
{
    /* Ԥ������ */      
    int setup_env;
   //��������
   char filename[MAXLTPLEN];
    /* Ԥ�ڽ�� */
   int  val;
   int  rtn;
};
struct config_test_04_t 
{
    /* Ԥ������ */      
    int setup_env;
   //��������
   char filename[MAXLTPLEN];
    /* Ԥ�ڽ�� */
   int  val;
   int  rtn;
};
struct config_test_05_t 
{
    /* Ԥ������ */      
    int setup_env;
   //��������
   char filename[MAXLTPLEN];
    /* Ԥ�ڽ�� */
   int  val;
   int  rtn;
};
struct config_test_06_t 
{
	/* Ԥ������ */      
    int setup_env;
    /* Ԥ�ڽ�� */
   int  val;
   int  rtn;
};
struct config_test_07_t 
{
	/* Ԥ������ */      
    int setup_env;
    /* Ԥ�ڽ�� */
   int  val;
   int  rtn;
};
struct config_test_08_t 
{
    /* Ԥ������ */      
    int setup_env;
   //��������
   char filename[MAXLTPLEN];
    /* Ԥ�ڽ�� */
   int  val;
   int  rtn;
};
#endif
