#ifndef __NIPDEBUG_KERNEL_H__
#define __NIPDEBUG_KERNEL_H__
/*
 * auth: wangyuantao@kedacom.com
 * date: Wed Oct 11 10:36:21 CST 2006
 */

#define DEBUGMISC_MINOR			199	/* for NIP Debug */

#define DEBUGMISC_FILENAME "/dev/debugmisc"	/* �豸�ļ��� */

#define KERNEL_DATA_MODE_INVALID	0
#define KERNEL_DATA_MODE_READ		1	/* ��ȡ���� */
#define KERNEL_DATA_MODE_WRITE		2	/* д������ */

#define KERNEL_DATA_ATTR_INVALID	0
#define KERNEL_DATA_ATTR_PHYS		1	/* �����ַ */
#define KERNEL_DATA_ATTR_VIRT		2	/* �����ַ */
#define KERNEL_DATA_ATTR_REG		3	/* �Ĵ�����ַ */

#define DEBUG_KERNEL_RWDATA		1	/* ioctlʹ�÷�ʽ���޸Ĳ鿴�ں����� */
#define DEBUG_KERNEL_DATA_TYPE		2	/* ����������� */
#define DEBUG_KERNEL_CALL		3	/* ִ���ں˺��� */
#define DEBUG_KERNEL_BACKTRACE		4	/* ��ӡ�߳��ں�ջ */

typedef void (*func_param0)(void);
typedef void (*func_param1)(int t1);
typedef void (*func_param2)(int t1, int t2);

/* ��Ҫ�����ں˺���ʱ�����ݸ��ں˵����ݽṹ */
typedef struct kernelcall{
	int addr;				/* ������ַ */
	int paramcount;				/* ���������������������ε� */
	int param1;				/* ����1 */
	int param2;				/* ����1 */
}kernelcall_t;

/*��Ҫ��ȡ�޸��ں�����ʱ�����ݸ��ں˵����ݽṹ */
typedef struct kerneldata{
	int mode;				/* ��ȡ���ݻ��� �޸����� */
	int attribute;				/* ��ַ���� */
	int addr;				/* �ں�������ʼ��ַ */
	int len;				/* ���ݳ��� */
	char *buf;				/* ���ݻ����� */
}kerneldata_t;

/* ��ӡ�̵߳��ں˵���ջ */
typedef struct kernelstack{
	int pid;				/* �߳�id */
}kernelstack_t;

/* ȡ�õ�ַ���� */
typedef struct kerneldatatype{
	int addr;				/* �ں˵�ַ */
	int type;				/* ���صĵ�ַ���� */
	int virt_addr;				/* ���ص������ַ�������ַ */
	int phy_addr;
}kerneldatatype_t;

#endif

