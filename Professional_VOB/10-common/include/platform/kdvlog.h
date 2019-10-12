/*****************************************************************************
   ģ����      : kdvlog
   �ļ���      : kdvlog.h
   ����ļ�    : 
   �ļ�ʵ�ֹ���: kdvlog.lib����ͷ�ļ�
   ����        : ����
   �汾        : V4.6  Copyright(C) 2001-2011 KDC, All rights reserved.
-----------------------------------------------------------------------------
   �޸ļ�¼:
   ��  ��      �汾        �޸���      �޸�����
   2011/04/5   4.6          ����        ����
******************************************************************************/


#ifndef KDV_LOG_LIB_H
#define KDV_LOG_LIB_H

#include "kdvtype.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef DllExport
#ifdef WIN32
#define DllExport __declspec(dllexport)
#else     /* VxWorks*/
#define DllExport
#endif
#endif

// ��������
#define		LOG_DEF_USER_NAME				(s8*)"KdvLog"		// Ĭ�ϵ��û���
#define		LOG_MAX_LENGTH_NAME				(u8)108				// �û�������󳤶�
#define		LOG_MAX_LENGTH_PATH				(u8)128				// �ļ�����·������󳤶�			
#define		LOG_MSG_MAX_LENGTH				(u8)255				// ÿ��log��Ϣ����󳤶�

// Ĭ�ϵ�ģ��������
#define		LOG_DEF_MODULE_INDEX			(u16)0xFFFF			// Ĭ��log�в����ģ����

// log�ȼ�����
#define		LOG_LVL_ERROR					(u8)1				// �������д���(�߼���ҵ�����),�������
#define		LOG_LVL_WARNING					(u8)2				// �澯��Ϣ, ������ȷ, Ҳ���ܴ���
#define		LOG_LVL_KEYSTATUS				(u8)3				// �������е�һ���ؼ�״̬ʱ����Ϣ���
#define		LOG_LVL_DETAIL					(u8)4				// ��ͨ��Ϣ, ��ò�Ҫд��log�ļ���

// ����豸����, ͨ��λ������������, Ĭ��������ļ�
#define		LOG_DST_NULL					(u8)0				// �����Log
#define		LOG_DST_FILE					(u8)0x01			// Log������ļ�
#define		LOG_DST_SERIAL					(u8)0x02			// Log���������
#define		LOG_DST_TELNET					(u8)0x04			// Log�����Telnet
#define		LOG_DST_DEFAULT					LOG_DST_FILE		// Log�����Telnet

// ģ��������
#define MODULE_DEF( x, y)		const u16 x = (y)

// ������
#define Err_t					u16								// ����������
#define	LOG_ERR_NO_ERR						(Err_t)(0)			// �޴���
#define	LOG_ERR_INIT_GDATA_FAILED			(Err_t)(1)			// ȫ�ֱ�����ʼ��ʧ��
#define	LOG_ERR_CFGPATH_TOO_LONG			(Err_t)(2)			// �����ļ�·������
#define	LOG_ERR_OPEN_CFGFILE_FAILED			(Err_t)(3)			// ������������ļ�ʧ��,��ȷ���Ƿ���������ռ��
#define	LOG_ERR_WIN_SOCK_INIT_ERR			(Err_t)(4)			// WSAStartup����ʧ��
#define	LOG_ERR_SOCKET_CREATE_ERR			(Err_t)(5)			// ����soecktʧ��
#define	LOG_ERR_SET_NET_BUF_FAILED			(Err_t)(6)			// ����soeckt�Ļ�����ʧ��
#define	LOG_ERR_INIT_PRINTER_FAILED			(Err_t)(7)			// ��ʼ����ӡʧ��
#define	LOG_ERR_CREATE_SEM_FAILED			(Err_t)(8)			// �����ź���ʧ��
#define	LOG_ERR_CREATE_RECVTASK_ERR			(Err_t)(9)			// ���������߳�ʧ��
#define	LOG_ERR_CLIENT_CONNECT_ERR			(Err_t)(10)			// �ͻ���connectʧ��
#define	LOG_ERR_CLIENT_BIND_ERR				(Err_t)(11)			// �ͻ��˰󶨶˿�ʧ��

/*====================================================================
������      ��LogInit
����        ��KdvLogģ���ʼ��
�㷨ʵ��    ���ڲ���ȥ�������ļ�, �������Ͱ�Ĭ������logģ��.
			  �����ļ��������Ƿ�����log, ��������С, ��������ַ����Ϣ
����ȫ�ֱ�����
�������˵����[in] pszCfgFileFullPath, log�����ļ����ļ���, ����·��. ����Ϊ��
����ֵ˵��  ��Err_t, ���մ����붨��
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
11/03/13    1.0         liuxu           ����
====================================================================*/
DllExport Err_t LogInit( const s8* pszCfgFileFullPath = 0);

/*====================================================================
������      ��LogQuit
����        ���˳�KdvLogģ�飬�ͷŰ����߳����ڵĸ�����Դ
�㷨ʵ��    ��
����ȫ�ֱ�����
�������˵������
����ֵ˵��  ����
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
2014/02/13  1.5         ������          ����
====================================================================*/
DllExport void LogQuit( void );

/*====================================================================
������      ��LogPrint, LogDstPrint
����        ��LogPrint, Ĭ�ϴ�ӡ�ӿ�, Ĭ��������ļ�;
LogDstPrint, �ɿ�����������豸,
�㷨ʵ��    ��
����ȫ�ֱ�����
�������˵����[in] byLevel, ��ӡ����, Ĭ������ͼ���
			  [in] wModuleId, ģ������, Ĭ����ͨ������
			  [in] pszFormat, ��ӡ����, �����Ч������108
����ֵ˵��  ��
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
11/03/13    1.0         liuxu           ����
====================================================================*/
DllExport void LogPrint( const u8 byLevel, const u16 wModule, const s8* pszFormat, ...);

/*====================================================================
������      ��logflush
����        ��������������д���ļ�.ĳЩ�ǳ���Ҫ����Ϣ��Ҫȷ����д���ļ�ʱ,����ô˽ӿ�
�㷨ʵ��    ��
����ȫ�ֱ�����
�������˵����
����ֵ˵��  ��
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
11/03/13    1.0         liuxu           ����
====================================================================*/
DllExport void logflush();

/*====================================================================
������      ��logsetdst
����        ������Log�������
�㷨ʵ��    ��
����ȫ�ֱ�����
�������˵����[in] byDst, �ο�����豸����. ֧��"��"����
			  [in] bOpen, trueΪ��; false,�ر�
����ֵ˵��  ��
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
11/03/13    1.0         liuxu           ����
====================================================================*/
DllExport void logsetdst( const u8 byDst );

/*====================================================================
������      ��logsetlvl
����        ������log�����ȼ�, һ�������
�㷨ʵ��    ��֧�ֶ�ȫ��log level�򵥶���ĳ��ģ���log level��������
��ȫ��level����ʱ, �����ÿ��ģ���log level.
����ȫ�ֱ�����
�������˵����[in] byLevel, ���ȼ�. 1�� error; 2, warning; 3, key status; 4, common
����ֵ˵��  ��
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
11/03/13    1.0         liuxu           ����
====================================================================*/
DllExport void logsetlvl( u8 byLevel = LOG_LVL_KEYSTATUS , u8 byFileLevel = LOG_LVL_KEYSTATUS);

/*====================================================================
������      ��logdisablemod
����        ������ӡbyModuleId������ģ���log��Ϣ, ������
�㷨ʵ��    ��
����ȫ�ֱ�����
�������˵����[in] wModuleId, Ҫ����ֹ��ӡ��ģ������
����ֵ˵��  ��
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
11/03/13    1.0         liuxu           ����
====================================================================*/
DllExport void logdisablemod(const u16 wModuleId);

/*====================================================================
������      ��logsetport
����        �����ÿͻ��˶˿ڰ󶨵ķ�Χ, ���������,����25020~25100
�㷨ʵ��    ��
����ȫ�ֱ�����
�������˵����[in] wStartPort, ��ʼ�˿�
			  [in] wPortNum, �˿ڷ�Χ
����ֵ˵��  ��
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
11/03/13    1.0         liuxu           ����
====================================================================*/
DllExport void logsetport(const u16 wStartPort, const u16 wPortNum);

/*====================================================================
������      ��logenablemod
����        ���ָ���ӡwModuleId������ģ���log��Ϣ, ������
�㷨ʵ��    ��
����ȫ�ֱ�����
�������˵����[in] wModuleId, ��Ҫ�򿪴�ӡ��ģ���id, Ĭ��ȫ����
����ֵ˵��  ��
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
11/03/13    1.0         liuxu           ����
====================================================================*/
DllExport void logenablemod(const u16 wModuleId = LOG_DEF_MODULE_INDEX);

/*====================================================================
������      ��loghelp
����        ��KdvLog��telnet��������
�㷨ʵ��    ��
����ȫ�ֱ�����
�������˵����
����ֵ˵��  ��
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
11/03/13    1.0         liuxu           ����
====================================================================*/
DllExport void loghelp( );

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif
//end of file