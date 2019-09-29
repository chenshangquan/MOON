/*=======================================================================
ģ����      : ZIPC�����շ�������ʹ�õ���������
�ļ���      : 
����ļ�    : 
�ļ�ʵ�ֹ���: 
����        : JinFeng
�汾        : LTP Release 1.0
-------------------------------------------------------------------------
�޸ļ�¼:
��  ��				�汾		�޸���					�޸�����
2006/02/07			1.0			Jinfeng					����
=======================================================================*/
#ifdef LTP_NIP_TEST

#ifndef _ZIPC_TEST_H_
#define _ZIPC_TEST_H_

enum
{
    ZIPC_TST_SUCCEED,   // ���Գɹ�
    ZIPC_TST_WARNING,   // ����
    ZIPC_TST_FAILED,    // ����ʧ��
};

#define MAXZIPCLEN 255
/*------------------------------------*/
//struct for nip testing
struct zipc_create_t
{
    char  sockname[MAXZIPCLEN];
    int     val;
    int     rtn;
};

/*------------------------------------*/
//struct for nip testing
struct zipc_close_t
{
    char  sockname[MAXZIPCLEN];
    int     val;
    int     rtn;
};

/*------------------------------------*/

//struct for nip testing
struct zipc_zmsg_tst
{
    int     length;
    int     val;
    int     rtn;
};

/*------------------------------------*/

//struct for nip testing
struct zipc_send_tst
{
    int     length;
    int     val;
    int     rtn;
};

/*------------------------------------*/

//struct for nip testing
struct zipc_recv_tst
{
    int     length;
    int     val;
    int     rtn;
};

/*------------------------------------*/

//struct for nip testing
struct zipc_send_recv_tst
{
    int     length;
    int     val;
    int     rtn;
};
/*------------------------------------*/
//struct for nip testing
struct zipc_zmsg_set_type_tst
{
 
    int		length;
	u_long	msgtype;
	int		val;
    int		rtn;
};

#endif

#endif
