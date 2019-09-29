/*****************************************************************************
ģ����      : KDV GK
�ļ���      : KDVGK.h
����ļ�    : 
�ļ�ʵ�ֹ���: 
����        : ����
�汾        : V4.0  Copyright(C) 2004-2005 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2005-02-17  4.0         ����         ����
2006-11-16  4.0         ���Ҿ�       �ύ����ƷѴ���
2007-02-28  4.0         ���Ҿ�       Davinci ����GK
******************************************************************************/

#ifndef __KDVGK_H
#define __KDVGK_H

#include "osp.h"
#include "kdvdef.h"
#include "eventid.h"
#include "cm.h"
#include "stkutils.h"

#ifdef _WINDOWS_
#include <io.h>
#include <direct.h>
#include <windef.h>
#endif // _WINDOWS_

#ifdef _VXWORKS_
#include "usrlib.h"
#include "Dirent.h"
#endif // _VXWORKS_

//////////////////////////////// GK APP ID ///////////////////////////////
#define AID_GK_STACKINIT		        (AID_GKS_BGN + 1)
#define AID_GK_RASOPERATION	            (AID_GKS_BGN + 2)
#define AID_GK_CONTROLSERVER            (AID_GKS_BGN + 3)
#define AID_GK_RADIUSCLIENT             (AID_GKS_BGN + 4)

//gk ���� interworking APPID
#define AID_GK_INTERWORKING             (AID_GKS_BGN + 6)

////////////////////////////////// �궨�� ////////////////////////////////
// ���ȶ���
#define CALLPORT			            (u16)1720	//���ж˿�
#define RASPORT				            (u16)1719	//RAS�˿�
#define MULTIRASPORT                    (u16)1718   //RAS�ಥ�˿�
#define MAX_REGISTER_NUM                (u16)3000   //���ʵ��ע����
#define MAX_ALIAS_NUM		            (u16)128	//��������

//add by yj for support all kinds of pcmts [20120924]
#define MAX_LEN_EPNAME					(u16)128	//�����Ȩʵ��������
#define MAX_PCMT_AUTH_NUM				(u16)16		//�����Ȩʵ��������		
//end [20120924]

#if defined(_DAVINCI_)
#define MAX_CALL_NUM                    (u16)14      //��������(����GK����֧��6��)
#else
#define MAX_CALL_NUM                    (u16)528    //��������
#endif
      
#define MAX_ENTITYALIAS_NUM             (u16)4      //ʵ����֤��ʵ����������      
#define MAX_CHANNEL_NUM                 (u16)0      //���ͨ����
#define MAX_KEEPALIVE_TIME              (s32)60     //RRQע����Чʱ�䣬��λ����
#define MAX_CALLADDR_NUM                (u16)8      //�����������ַ��
#define MAX_ENCODERAS_LEN               (u16)0x1000 //���ѹ�����RAS��Ϣ��buf����
#define MAX_E164_LEN                    (u16)128	//E164��������󳤶�
#define MAX_ALIASNAME_LEN               (u16)512	//������������󳤶�
#define MAX_BUFFER_SIZE                 (u32)4096	//Э��ջ������ͻ���
#define KDC_COUNTRYCODE		            (s32)38		//���Ҵ���
#define KDC_T35EXTENSION	            (s32)0		//��չ����
#define KDC_MANUCODE		            (s32)8888	//���̴���
#define CONFRESPONSE_TIMEOUT            (u32)15     //15s
#define CONFCONNECT_TIMEOUT             (u32)50     //50s 
#define LEN_OID				            (u16)16		//OID����
#define LEN_GUID                        (u16)16
#define LEN_256                         (u16)256
#define MAX_USER_LOGIN                  (u16)16     //����û���½��
#define MAX_USERNAME_LEN                (u16)32     //����û�������
#define MAX_PASSWORD_LEN                (u16)16     //������볤��
#define MAX_GKPREFIX_NUM                (u16)16     //���ǰ׺��
#define MAX_GKPREFIX_LEN                (u16)8      //ǰ׺��󳤶�
#define MAX_AUTHIPRANGE_NUM             (u16)16     //IP��֤��Χ��������
#define MAX_BANDWIDTH_NUM               (u16)16     //���δ�����Ϣ���Ƶ�������
#define MAX_NEIGHBORGK_NUM              (u16)128    //����ھ�GK��
#define IRR_FREQUENCY                   (u16)30     //60s
#define TIMER_ALLOWOFFSET               (u16)10000   //��ʱ������ƫ��10s
#define HBTIME                          (u16)60     //60s
#define HBNUM                           (u16)3

//radius ��֤/�Ʒ���غ궨��
#define MAX_RADIU_SECRET_LEN            (u16)16     //radius secret ����󳤶� 
#define DEFAULT_RADIUS_SECRET           (s8*)"kdc"  //Ĭ��radius��Կ
#define DEFAULT_ACCESS_PORT             (u16)1812   //Ĭ����֤�˿�
#define DEFAULT_ACCT_PORT               (u16)1813   //Ĭ�ϼƷѶ˿�
#define DEFAULT_RETRY_TIME              (u16)1      //Ĭ���ط�����
#define DEFAULT_TIMEOUT_INTERVAL        (u32)10000   //Ĭ�ϳ�ʱ���(����)



//��־������
#define LOG_EXP		        	        (u32)0		//�쳣
#define LOG_DEBUG	        	        (u32)1		//ϵͳ������Ϣ

#define LOG_REGISTER			        (u32)2		//RRQ/RCF/RRJ
#define LOG_ADMISSION		            (u32)4		//ARQ/ACF/ARJ
#define LOG_DISENGAGE                   (u32)6      //DRQ/DCF/DRJ 
#define LOG_UNREGISTER                  (u32)8      //URQ/UCF/URJ
#define LOG_INFORMATION                 (u32)10     //IRQ/IRR
#define LOG_BANDWIDTH                   (u32)12     //BRQ/BCF/BRJ
#define LOG_LOCATION                    (u32)14     //LRQ/LCF/LRJ
#define LOG_GATEKEEPER                  (u32)16     //GRQ/GCG/GRJ

#define LOG_DATABASE_DEBUG              (u32)20     //���ݿ�����ĵ�����Ϣ
#define LOG_CONTRLSERVER_DEBUG          (u32)21     //����̨�����ĵ�����Ϣ
#define LOG_DATABASE_ALL                (u32)22     //�������ݿ��������Ϣ
#define LOG_CONTRLSERVER_ALL            (u32)23     //���п���̨��������Ϣ

#define LOG_ALL		        	        (u32)30     //������Ϣ

//GK����̨��Ϣ��Ӧ
#define CTRLMSGRSP_SUCCESS				(u32)0      // �ɹ�
#define CTRLMSGRSP_UNKOWNERR 			(u32)1      // δ֪����
#define CTRLMSGRSP_INVALIDCTRLVER		(u32)2      // ����̨�汾����
#define CTRLMSGRSP_PARAMCONFLICT		(u32)3      // ������һ��
#define CTRLMSGRSP_ACCESSDENIED			(u32)4      // Ȩ�޲�����
#define CTRLMSGRSP_USERNOTEXIST			(u32)5      // �û���������
#define CTRLMSGRSP_INVALIDPASS			(u32)6      // ����Ƿ�
#define CTRLMSGRSP_USEREXIST			(u32)7      // �û��Ѵ���
#define CTRLMSGRSP_INVALIDUSER			(u32)8      // �û����Ƿ�
#define CTRLMSGRSP_INVALIDDSTUSER		(u32)9      // Ŀ���û����Ƿ�
#define CTRLMSGRSP_INVALIDDSTPASS		(u32)10     // Ŀ������Ƿ�
#define CTRLMSGRSP_INVALIDCALLID		(u32)11     // �Ƿ�call identifier
#define CTRLMSGRSP_INVALIDIPRNG			(u32)12     // �Ƿ�ip��Χ
#define CTRLMSGRSP_IPRNGEXIST			(u32)13     // ip��Χ�Ѵ���
#define CTRLMSGRSP_IPRNGNOTEXIST		(u32)14     // ip��Χ������
#define CTRLMSGRSP_EPNOTREG				(u32)15     // H.323ʵ��û��ע��
#define CTRLMSGRSP_ALIASEXIST			(u32)16     // E164���Ѵ���
#define CTRLMSGRSP_INVALIDALIAS			(u32)17     // �Ƿ�alias
#define CTRLMSGRSP_INVALIDIP			(u32)18     // �Ƿ�ip
#define CTRLMSGRSP_EPNOTEXIST			(u32)19     // endpoint������
#define CTRLMSGRSP_INVALIDEPTYPE		(u32)20     // endpoint type�Ƿ�
#define CTRLMSGRSP_INVALIDPARAM			(u32)21     // �����Ƿ�
#define CTRLMSGRSP_INVALIDMSGBD			(u32)22     // �Ƿ���Ϣ�壬������ִ���
#define CTRLMSGRSP_DBERROR				(u32)23     // DB����
#define CTRLMSGRSP_ENCODEERR			(u32)24     // �������
#define CTRLMSGRSP_DECODEERR			(u32)25     // �������
#define CTRLMSGRSP_INVALIDUS			(u32)26     // �Ƿ��û�����
#define CTRLMSGRSP_TOOSMALLBUF			(u32)27     // ������̫С
#define CTRLMSGRSP_NORECORD				(u32)28     // û�м�¼
#define CTRLMSGRSP_MAXUSER				(u32)29     // �ﵽ����̨�û�����
#define CTRLMSGRSP_USERLOGINED			(u32)30     // �û��ѵ�¼
#define CTRLMSGRSP_USERNOTLOGIN			(u32)31     // �û�δ��¼
#define CTRLMSGRSP_ADMINFORBIDDEL		(u32)32     // ����Ա�û�����ɾ��
#define CTRLMSGRSP_BWEXIST				(u32)33     // ���μ�����Ѵ���
#define CTRLMSGRSP_BWNOTEXIST			(u32)34     // ���μ��������
#define CTRLMSGRSP_KEYEXIST				(u32)35     // ����
#define CTRLMSGRSP_KEYNOTEXIST			(u32)36     // ������
#define CTRLMSGRSP_DSTKEYEXIST			(u32)37     // Ŀ��key�Ѵ��� 
#define CTRLMSGRSP_IPRNGERROR           (u32)38     // ip��Χ����
#define CTRLMSGRSP_EPALIASLEN_INVALID	(u32)39     // ʵ��������ȷǷ�
#define CTRLMSGRSP_ENTITYEXIST          (u32)40     //ʵ���Ѵ���     //[12/27/2007 zhangzhihua]add 
#define CTRLMSGRSP_ERRVERSION           (u32)41     //GKC�汾��ƥ��. //[12/28/2007 zhangzhihua]add 

//GKC�汾��
#define GKC_VESION_NUM                   (u32)10000  //[12/28/2007 zhangzhihua]add.GKC�汾��. 

//GK�������ݿ�Ĵ��·����������
#if defined (WIN32)
#define MakeDirectory(dirname) _mkdir((dirname))
#elif defined (_VXWORKS_)
#define MakeDirectory(dirname) mkdir(dirname)
#elif defined (_LINUX_)
#define MakeDirectory(dirname) mkdir(dirname, 0777)
#else
#error "This version only support windows and vxworks and linux"
#endif // _WINDOWS_

// #if defined(_HHPPC_82XX_) || defined(_HHPPC_85XX_)
#if defined(_LINUX_)

#define GKDB_PATH                   (s8*)"/usr/etc/gk/GKDB"
#define GKCONFIGDB_PATH             (s8*)"/usr/etc/gk/GKDB/GKConfigDB"

#define USERDB_PATH_NAME            (s8*)"/usr/etc/gk/GKDB/GKConfigDB/UserDB.db"
#define BASECONFIGDB_PATH_NAME      (s8*)"/usr/etc/gk/GKDB/GKConfigDB/BaseConfigDB.db"
#define BANDWIDTHDB_PATH_NAME       (s8*)"/usr/etc/gk/GKDB/GKConfigDB/BandwidthDB.db"
#define IPRANGEDB_PATH_NAME         (s8*)"/usr/etc/gk/GKDB/GKConfigDB/IPRangeDB.db"
#define ALIASDB_PATH_NAME           (s8*)"/usr/etc/gk/GKDB/GKConfigDB/EndpointAliasDB.db"
#define ENTITYDB_PATH_NAME            (s8*)"/usr/etc/gk/GKDB/GKConfigDB/EntityDB.db"         //[12/26/2007 zhangzhihua]add 

#else

#define GKDB_PATH                   (s8*)"GKDB"
#define GKCONFIGDB_PATH             (s8*)"GKDB/GKConfigDB"

#define USERDB_PATH_NAME            (s8*)"GKDB/GKConfigDB/UserDB"
#define BASECONFIGDB_PATH_NAME      (s8*)"GKDB/GKConfigDB/BaseConfigDB"
#define BANDWIDTHDB_PATH_NAME       (s8*)"GKDB/GKConfigDB/BandwidthDB"
#define IPRANGEDB_PATH_NAME         (s8*)"GKDB/GKConfigDB/IPRangeDB"
#define ALIASDB_PATH_NAME           (s8*)"GKDB/GKConfigDB/EndpointAliasDB"
#define ENTITYDB_PATH_NAME            (s8*)"GKDB/GKConfigDB/EntityDB"    //[12/26/2007 zhangzhihua]add 

#endif

#ifndef min
#define min(a,b) (((a)<(b))?(a):(b))
#endif
//////////////////////////////// OSP��Ϣ��Χ /////////////////////////////
//////// RAS OSP��Ϣ��Χ: (GKRASOSPEVENT_START, GKRASOSPEVENT_END)////////
OSPEVENT( GKRASOSPEVENT_START, EV_RAS_BGN );

// �յ�RRQ
OSPEVENT( EV_RAS_RECV_RRQ, GKRASOSPEVENT_START + 1 );
// ����RRQ
OSPEVENT( EV_RAS_SEND_RRQ, GKRASOSPEVENT_START + 2 );

// �յ�RCF
OSPEVENT( EV_RAS_RECV_RCF, GKRASOSPEVENT_START + 3 );
// ����RCF
OSPEVENT( EV_RAS_SEND_RCF, GKRASOSPEVENT_START + 4 );

// �յ�RRJ
OSPEVENT( EV_RAS_RECV_RRJ, GKRASOSPEVENT_START + 5 );
// ����RRJ
OSPEVENT( EV_RAS_SEND_RRJ, GKRASOSPEVENT_START + 6 );

// �յ�URQ
OSPEVENT( EV_RAS_RECV_URQ, GKRASOSPEVENT_START + 7 );
// ����URQ
OSPEVENT( EV_RAS_SEND_URQ, GKRASOSPEVENT_START + 8 );

// �յ�UCF
OSPEVENT( EV_RAS_RECV_UCF, GKRASOSPEVENT_START + 9 );
// ����UCF
OSPEVENT( EV_RAS_SEND_UCF, GKRASOSPEVENT_START + 10 );

// �յ�URJ
OSPEVENT( EV_RAS_RECV_URJ, GKRASOSPEVENT_START + 11 );
// ����URJ
OSPEVENT( EV_RAS_SEND_URJ, GKRASOSPEVENT_START + 12 );

// �յ�ARQ
OSPEVENT( EV_RAS_RECV_ARQ, GKRASOSPEVENT_START + 13 );
// ����ARQ
OSPEVENT( EV_RAS_SEND_ARQ, GKRASOSPEVENT_START + 14 );

// �յ�ACF
OSPEVENT( EV_RAS_RECV_ACF, GKRASOSPEVENT_START + 15 );
// ����ACF
OSPEVENT( EV_RAS_SEND_ACF, GKRASOSPEVENT_START + 16 );

// �յ�ARJ
OSPEVENT( EV_RAS_RECV_ARJ, GKRASOSPEVENT_START + 17 );
// ����ARJ
OSPEVENT( EV_RAS_SEND_ARJ, GKRASOSPEVENT_START + 18 );

// �յ�BRQ
OSPEVENT( EV_RAS_RECV_BRQ, GKRASOSPEVENT_START + 19 );
// ����BRQ
OSPEVENT( EV_RAS_SEND_BRQ, GKRASOSPEVENT_START + 20 );

// �յ�BCF
OSPEVENT( EV_RAS_RECV_BCF, GKRASOSPEVENT_START + 21 );
// ����BCF
OSPEVENT( EV_RAS_SEND_BCF, GKRASOSPEVENT_START + 22 );

// �յ�BRJ
OSPEVENT( EV_RAS_RECV_BRJ, GKRASOSPEVENT_START + 23 );
// ����BRJ
OSPEVENT( EV_RAS_SEND_BRJ, GKRASOSPEVENT_START + 24 );

// �յ�LRQ
OSPEVENT( EV_RAS_RECV_LRQ, GKRASOSPEVENT_START + 25 );
// ����LRQ
OSPEVENT( EV_RAS_SEND_LRQ, GKRASOSPEVENT_START + 26 );

// �յ�LCF
OSPEVENT( EV_RAS_RECV_LCF, GKRASOSPEVENT_START + 27 );
// ����LCF
OSPEVENT( EV_RAS_SEND_LCF, GKRASOSPEVENT_START + 28 );

// �յ�LRJ
OSPEVENT( EV_RAS_RECV_LRJ, GKRASOSPEVENT_START + 29 );
// ����LRJ
OSPEVENT( EV_RAS_SEND_LRJ, GKRASOSPEVENT_START + 30 );

// �յ�DRQ
OSPEVENT( EV_RAS_RECV_DRQ, GKRASOSPEVENT_START + 31 );
// ����DRQ
OSPEVENT( EV_RAS_SEND_DRQ, GKRASOSPEVENT_START + 32 );

// �յ�DCF
OSPEVENT( EV_RAS_RECV_DCF, GKRASOSPEVENT_START + 33 );
// ����DCF
OSPEVENT( EV_RAS_SEND_DCF, GKRASOSPEVENT_START + 34 );

// �յ�DRJ
OSPEVENT( EV_RAS_RECV_DRJ, GKRASOSPEVENT_START + 35 );
// ����DRJ
OSPEVENT( EV_RAS_SEND_DRJ, GKRASOSPEVENT_START + 36 );

// �յ�IRQ
OSPEVENT( EV_RAS_RECV_IRQ, GKRASOSPEVENT_START + 37 );
// ����IRQ
OSPEVENT( EV_RAS_SEND_IRQ, GKRASOSPEVENT_START + 38 );

// �յ�IRR
OSPEVENT( EV_RAS_RECV_IRR, GKRASOSPEVENT_START + 39 );
// ����IRR
OSPEVENT( EV_RAS_SEND_IRR, GKRASOSPEVENT_START + 40 );

// �յ�GRQ
OSPEVENT( EV_RAS_RECV_GRQ, GKRASOSPEVENT_START + 41 );
// ����GCF
OSPEVENT( EV_RAS_SEND_GCF, GKRASOSPEVENT_START + 42 );
// ����GRJ
OSPEVENT( EV_RAS_SEND_GRJ, GKRASOSPEVENT_START + 43 );

OSPEVENT( EV_RAS_RECV_IRQ_TIMEOUT, GKRASOSPEVENT_START + 44 );

// �յ�Unsolicite IRR
OSPEVENT( EV_RAS_RECV_UNSOLICITED_IRR, GKRASOSPEVENT_START + 45);

//add by yj for NonStandardMessage [20120823]
//RAS�Ǳ���Ϣ(46,47,49������ռ��)
OSPEVENT(EV_RAS_RECV_NSM, GKRASOSPEVENT_START +48);
//end [20120823]

OSPEVENT( GKRASOSPEVENT_END, EV_RAS_END );

//////////// GKϵͳ��Ϣ��Χ: (GKOSPEVENT_START, GKSYSOSPEVENT_END)////////
OSPEVENT( GKSYSOSPEVENT_START, GKOSPEVENT_START );

// GK��ʼ��
OSPEVENT( EV_GKSYS_INIT, GKSYSOSPEVENT_START + 1 ); 

// GK�˳�
OSPEVENT( EV_GKSYS_QUIT, GKSYSOSPEVENT_START + 2 );

// ϵͳ����Ϣ�����ڶ�ʱ��
OSPEVENT( EV_TIMER_ONE_SECOND, GKSYSOSPEVENT_START + 3 );

// Watchdogע����Ϣ
OSPEVENT( WATCHDOG_CONNECT, GKSYSOSPEVENT_START + 4 );


//֪ͨʵʱ��������ݿ�
OSPEVENT( EV_RELOAD_CONFIGDB, GKSYSOSPEVENT_START + 5 );
OSPEVENT( EV_RELOAD_IPRANGEDB, GKSYSOSPEVENT_START + 6 );
OSPEVENT( EV_RELOAD_ALIASDB, GKSYSOSPEVENT_START + 7 );
OSPEVENT( EV_RELOAD_ENTITYDB, GKSYSOSPEVENT_START + 8);

// ǿ��ע��
OSPEVENT( EV_UNREG, GKSYSOSPEVENT_START + 10 );

// ע��ȫ��
OSPEVENT( EV_UNREG_ALL, GKSYSOSPEVENT_START + 11 );

// �ҶϺ���
OSPEVENT( EV_DROPCALL, GKSYSOSPEVENT_START + 12 );

OSPEVENT( GKSYSOSPEVENT_END, GKSYSOSPEVENT_START + 20 );

/////GK����̨OSP��Ϣ��Χ: (GKCTRLOSPEVENT_START, GKCTRLOSPEVENT_END)//////
OSPEVENT( GKCTRLOSPEVENT_START, GKSYSOSPEVENT_END );

// �û���¼
OSPEVENT(EV_CG_USER_LOGIN_REQ,	GKCTRLOSPEVENT_START + 1);
// �û���¼��Ӧ
OSPEVENT(EV_GC_USER_LOGIN_RSP,	GKCTRLOSPEVENT_START + 2);

// �˳���¼
OSPEVENT(EV_CG_USER_EXIT_REQ,	GKCTRLOSPEVENT_START + 3);
// �˳���¼��Ӧ
OSPEVENT(EV_GC_USER_EXIT_RSP,	GKCTRLOSPEVENT_START + 4);

// �����û�
OSPEVENT(EV_CG_USER_ADD_REQ,	GKCTRLOSPEVENT_START + 5);
// �����û���Ӧ
OSPEVENT(EV_GC_USER_ADD_RSP,	GKCTRLOSPEVENT_START + 6);

// ɾ���û�
OSPEVENT(EV_CG_USER_DEL_REQ,	GKCTRLOSPEVENT_START + 7);
// ɾ���û���Ӧ
OSPEVENT(EV_GC_USER_DEL_RSP,	GKCTRLOSPEVENT_START + 8);

// �޸��û�
OSPEVENT(EV_CG_USER_MODIFY_REQ,	GKCTRLOSPEVENT_START + 9);
// �޸��û���Ӧ
OSPEVENT(EV_GC_CTRLUSER_MODIFY_RSP,	GKCTRLOSPEVENT_START + 10);

// �޸�����
OSPEVENT(EV_CG_USER_MODIFYPASS_REQ,	GKCTRLOSPEVENT_START + 11);
// �޸�������Ӧ
OSPEVENT(EV_GC_USER_MODIFYPASS_RSP,	GKCTRLOSPEVENT_START + 12);

// ��ȡ�û���Ϣ�б�
OSPEVENT(EV_CG_CTRLUSER_GETLIST_REQ,	GKCTRLOSPEVENT_START + 13);
// ��ȡ�û���Ϣ�б���Ӧ
OSPEVENT(EV_GC_CTRLUSER_GETLIST_RSP,	GKCTRLOSPEVENT_START + 14);

// ��ȡһ���û�
OSPEVENT(EV_CG_CTRLUSER_GETONE_REQ,	GKCTRLOSPEVENT_START + 15);
// ��ȡһ���û���Ӧ
OSPEVENT(EV_GC_CTRLUSER_GETONE_RSP,	GKCTRLOSPEVENT_START + 16);

// ����GK��������
OSPEVENT(EV_CG_GKCFG_BASE_SET_REQ,	GKCTRLOSPEVENT_START + 17);
// ����GK����������Ӧ
OSPEVENT(EV_GC_GKCFG_BASE_SET_RSP,	GKCTRLOSPEVENT_START + 18);

// ��ȡGK��������
OSPEVENT(EV_CG_GKCFG_BASE_GET_REQ,	GKCTRLOSPEVENT_START + 19);
// ��ȡGK����������Ӧ
OSPEVENT(EV_GC_GKCFG_BASE_GET_RSP,	GKCTRLOSPEVENT_START + 20);

// ����GKǰ׺
OSPEVENT( EV_CG_GKCFG_PREFIX_ADD_REQ,	GKCTRLOSPEVENT_START + 21);
// ����GKǰ׺��Ӧ
OSPEVENT( EV_GC_GKCFG_PREFIX_ADD_RSP,	GKCTRLOSPEVENT_START + 22);

// ��ȡGKǰ׺
OSPEVENT( EV_CG_GKCFG_PREFIX_GET_REQ,	GKCTRLOSPEVENT_START + 23);
// ��ȡGKǰ׺��Ӧ
OSPEVENT( EV_GC_GKCFG_PREFIX_GET_RSP,	GKCTRLOSPEVENT_START + 24);

// ɾ��GKǰ׺
OSPEVENT( EV_CG_GKCFG_PREFIX_DEL_REQ,	GKCTRLOSPEVENT_START + 25);
// ɾ��GKǰ׺��Ӧ
OSPEVENT( EV_GC_GKCFG_PREFIX_DEL_RSP,	GKCTRLOSPEVENT_START + 26);

// ������֤IP��Χ
OSPEVENT(EV_CG_GKCFG_REGIPRNG_ADD_REQ,	GKCTRLOSPEVENT_START + 27);
// ������֤IP��Χ��Ӧ
OSPEVENT(EV_GC_GKCFG_REGIPRNG_ADD_RSP,	GKCTRLOSPEVENT_START + 28);

// ɾ����֤IP��Χ
OSPEVENT(EV_CG_GKCFG_REGIPRNG_DEL_REQ,	GKCTRLOSPEVENT_START + 29);
// ɾ����֤IP��Χ��Ӧ
OSPEVENT(EV_GC_GKCFG_REGIPRNG_DEL_RSP,	GKCTRLOSPEVENT_START + 30);

// �޸���֤IP��Χ
OSPEVENT(EV_CG_GKCFG_REGIPRNG_MODIFY_REQ,	GKCTRLOSPEVENT_START + 31);
// �޸���֤IP��Χ��Ӧ
OSPEVENT(EV_GC_GKCFG_REGIPRNG_MODIFY_RSP,	GKCTRLOSPEVENT_START + 32);

// ��ȡ��֤����IP��Χ�б�
OSPEVENT(EV_CG_GKCFG_REGIPRNG_GETLIST_REQ,	GKCTRLOSPEVENT_START + 33);
// ��ȡ��֤����IP��Χ�б���Ӧ
OSPEVENT(EV_GC_GKCFG_REGIPRNG_GETLIST_RSP,	GKCTRLOSPEVENT_START + 34);

// �������μ������Ϣ
OSPEVENT(EV_CG_GKCFG_BETWEENSUBNETBANDINFO_ADD_REQ,	GKCTRLOSPEVENT_START + 35);
// �������μ������Ϣ��Ӧ
OSPEVENT(EV_GC_GKCFG_BETWEENSUBNETBANDINFO_ADD_RSP,	GKCTRLOSPEVENT_START + 36);

// ɾ�����μ������Ϣ
OSPEVENT(EV_CG_GKCFG_BETWEENSUBNETBANDINFO_DEL_REQ,	GKCTRLOSPEVENT_START + 37);
// ɾ�����μ������Ϣ��Ӧ
OSPEVENT(EV_GC_GKCFG_BETWEENSUBNETBANDINFO_DEL_RSP,	GKCTRLOSPEVENT_START + 38);

// �޸����μ������Ϣ
OSPEVENT(EV_CG_GKCFG_BETWEENSUBNETBANDINFO_MODIFY_REQ,	GKCTRLOSPEVENT_START + 39);
// �޸����μ������Ϣ��Ӧ
OSPEVENT(EV_GC_GKCFG_BETWEENSUBNETBANDINFO_MODIFY_RSP,	GKCTRLOSPEVENT_START + 40);

// ��ȡ���μ������Ϣ�б�
OSPEVENT(EV_CG_GKCFG_BETWEENSUBNETBANDINFO_GETLIST_REQ,	GKCTRLOSPEVENT_START + 41);
// ��ȡ���μ������Ϣ�б���Ӧ
OSPEVENT(EV_GC_GKCFG_BETWEENSUBNETBANDINFO_GETLIST_RSP,	GKCTRLOSPEVENT_START + 42);

// ��ȡһ�����μ������Ϣ
OSPEVENT(EV_CG_GKCFG_BETWEENSUBNETBANDINFO_GET_REQ,	GKCTRLOSPEVENT_START + 43);
// ��ȡһ�����μ������Ϣ��Ӧ
OSPEVENT(EV_GC_GKCFG_BETWEENSUBNETBANDINFO_GET_RSP,	GKCTRLOSPEVENT_START + 44);

// ����H.323������֤
OSPEVENT(EV_CG_ENDPOINT_ADD_REQ,	GKCTRLOSPEVENT_START + 45);
// ����H.323������֤��Ӧ
OSPEVENT(EV_GC_ENDPOINT_ADD_RSP,	GKCTRLOSPEVENT_START + 46);

// ɾ��H.323������֤
OSPEVENT(EV_CG_ENDPOINT_DEL_REQ,	GKCTRLOSPEVENT_START + 47);
// ɾ��H.323������֤��Ӧ
OSPEVENT(EV_GC_ENDPOINT_DEL_RSP,	GKCTRLOSPEVENT_START + 48);

// �޸�H.323������֤
OSPEVENT(EV_CG_ENDPOINT_MODIFY_REQ,	GKCTRLOSPEVENT_START + 49);
// �޸�H.323������֤��Ӧ
OSPEVENT(EV_GC_ENDPOINT_MODIFY_RSP,	GKCTRLOSPEVENT_START + 50);

// ��ȡH.323������֤�б�
OSPEVENT(EV_CG_GETENDPOINTLIST_REQ,	GKCTRLOSPEVENT_START + 51);
// ��ȡH.323������֤�б���Ӧ
OSPEVENT(EV_GC_GETENDPOINTLIST_RSP,	GKCTRLOSPEVENT_START + 52);

// ����GK
OSPEVENT(EV_CG_RESTARTGK_CMD,	GKCTRLOSPEVENT_START + 53);

// ǿ�ƺ��н���
OSPEVENT(EV_CG_STOPCALL_REQ,	GKCTRLOSPEVENT_START + 54);
// ǿ�ƺ��н�����Ӧ
OSPEVENT(EV_GC_STOPCALL_RSP,	GKCTRLOSPEVENT_START + 55);

// ǿ��H.323ʵ��ע��
OSPEVENT(EV_CG_UNREGENDPOINT_REQ,	GKCTRLOSPEVENT_START + 56);
// ǿ��H.323ʵ��ע����Ӧ
OSPEVENT(EV_GC_UNREGENDPOINT_RSP,	GKCTRLOSPEVENT_START + 57);

// ��ȡ��ע��H.323ʵ���б�
OSPEVENT(EV_CG_GETREGISTEREDENDPOINTLIST_REQ,	GKCTRLOSPEVENT_START + 58);
// ��ȡ��ע��H.323ʵ���б���Ӧ
OSPEVENT(EV_GC_GETREGISTEREDENDPOINTLIST_RSP,	GKCTRLOSPEVENT_START + 59);

// ��ȡ�ض�H.323ʵ��ĺ����б�
OSPEVENT(EV_CG_GETCALLLIST_REQ,	GKCTRLOSPEVENT_START + 60);
// ��ȡ�ض�H.323ʵ��ĺ����б���Ӧ
OSPEVENT(EV_GC_GETCALLLIST_RSP,	GKCTRLOSPEVENT_START + 61);

// H.323ʵ��ע��֪ͨ
OSPEVENT(EV_GC_RTIMEMSG_REG_NTF,	GKCTRLOSPEVENT_START + 62);
// H.323ʵ��ע��֪ͨ
OSPEVENT(EV_GC_RTIMEMSG_UNREG_NTF,	GKCTRLOSPEVENT_START + 63);

// H.323ʵ�����֪ͨ
OSPEVENT(EV_GC_RTIMEMSG_CALL_NTF,	GKCTRLOSPEVENT_START + 64);
// H.323ʵ����н���֪ͨ
OSPEVENT(EV_GC_RTIMEMSG_CALLFINISH_NTF,	GKCTRLOSPEVENT_START + 65);

// ����ı�֪ͨ
OSPEVENT(EV_GC_RTIMEMSG_BANDWISTHCHANGED_NTF,	GKCTRLOSPEVENT_START + 66);
// λ������֪ͨ
OSPEVENT(EV_GC_RTIMEMSG_RECEIVELOCATIONREQ_NTF,	GKCTRLOSPEVENT_START + 67);
// IRR��Ϣ֪ͨ
OSPEVENT(EV_GC_RTIMEMSG_RECEIVEIRR_NTF,	GKCTRLOSPEVENT_START + 68);

// �����ھ�GK
OSPEVENT( EV_CG_GKCFG_NEIGHBORGK_ADD_REQ,	GKCTRLOSPEVENT_START + 69);
// �����ھ�GK��Ӧ
OSPEVENT( EV_GC_GKCFG_NEIGHBORGK_ADD_RSP,	GKCTRLOSPEVENT_START + 70);

// ��ȡ�ھ�GK
OSPEVENT( EV_CG_GKCFG_NEIGHBORGK_GET_REQ,	GKCTRLOSPEVENT_START + 71);
// ��ȡ�ھ�GK��Ӧ
OSPEVENT( EV_GC_GKCFG_NEIGHBORGK_GET_RSP,	GKCTRLOSPEVENT_START + 72);

// ɾ���ھ�GK
OSPEVENT( EV_CG_GKCFG_NEIGHBORGK_DEL_REQ,	GKCTRLOSPEVENT_START + 73);
// ɾ���ھ�GK��Ӧ
OSPEVENT( EV_GC_GKCFG_NEIGHBORGK_DEL_RSP,	GKCTRLOSPEVENT_START + 74);

// ������֤��ʽ
OSPEVENT( EV_CG_GKCFG_AUTHMETHOD_SET_REQ,	GKCTRLOSPEVENT_START + 75);
// ������֤��ʽ��Ӧ
OSPEVENT( EV_GC_GKCFG_AUTHMETHOD_SET_RSP,	GKCTRLOSPEVENT_START + 76);

// ��ȡ��֤��ʽ
OSPEVENT( EV_CG_GKCFG_AUTHMETHOD_GET_REQ,	GKCTRLOSPEVENT_START + 77);
// ��ȡ��֤��ʽ��Ӧ
OSPEVENT( EV_GC_GKCFG_AUTHMETHOD_GET_RSP,	GKCTRLOSPEVENT_START + 78);

// ������֤����
OSPEVENT( EV_CG_GKCFG_AUTHPASSWORD_SET_REQ,	GKCTRLOSPEVENT_START + 79);
// ������֤������Ӧ
OSPEVENT( EV_GC_GKCFG_AUTHPASSWORD_SET_RSP,	GKCTRLOSPEVENT_START + 80);

// ��ȡ��֤����
OSPEVENT( EV_CG_GKCFG_AUTHPASSWORD_GET_REQ,	GKCTRLOSPEVENT_START + 81);
// ��ȡ��֤������Ӧ
OSPEVENT( EV_GC_GKCFG_AUTHPASSWORD_GET_RSP,	GKCTRLOSPEVENT_START + 82);

// ������������
OSPEVENT( EV_CG_GKCFG_ETH_SET_REQ,	GKCTRLOSPEVENT_START + 83);
// ��������������Ӧ
OSPEVENT( EV_GC_GKCFG_ETH_SET_RSP,	GKCTRLOSPEVENT_START + 84);

// ��ȡ��������
OSPEVENT( EV_CG_GKCFG_ETH_GET_REQ,	GKCTRLOSPEVENT_START + 85);
// ��ȡ����������Ӧ
OSPEVENT( EV_GC_GKCFG_ETH_GET_RSP,	GKCTRLOSPEVENT_START + 86);

// ��ȡGK RadiusAuth������Ӧ
//OSPEVENT( EV_RADIUSAUTH_CONFIG_GET_RSP, GKCTRLOSPEVENT_START + 87);


//add by guozhongjun 2006.07.05
//����Radius��֤����
OSPEVENT( EV_CG_GKCFG_RADIUS_SET_REQ, GKCTRLOSPEVENT_START + 87);
//����Radius��֤������Ӧ
OSPEVENT( EV_GC_GKCFG_RADIUS_SET_RSP, GKCTRLOSPEVENT_START + 88);

// ��ȡGK RadiusAuth����
OSPEVENT( EV_CG_GKCFG_RADIUS_GET_REQ,     GKCTRLOSPEVENT_START + 89);
// ��ȡGK RadiusAuth������Ӧ
OSPEVENT( EV_GC_GKCFG_RADIUS_GET_RSP,     GKCTRLOSPEVENT_START + 90);

//[12/26/2007 zhangzhihua]add 
// ����H.323ʵ����֤
OSPEVENT(EV_CG_ENTITY_ADD_REQ,	GKCTRLOSPEVENT_START + 91);
// ����H.323ʵ����֤��Ӧ
OSPEVENT(EV_GC_ENTITY_ADD_RSP,	GKCTRLOSPEVENT_START + 92);

// ɾ��H.323ʵ����֤
OSPEVENT(EV_CG_ENTITY_DEL_REQ,	GKCTRLOSPEVENT_START + 93);
// ɾ��H.323ʵ����֤��Ӧ
OSPEVENT(EV_GC_ENTITY_DEL_RSP,	GKCTRLOSPEVENT_START + 94);

// �޸�H.323ʵ����֤
OSPEVENT(EV_CG_ENTITY_MODIFY_REQ,	GKCTRLOSPEVENT_START + 95);
// �޸�H.323ʵ����֤��Ӧ
OSPEVENT(EV_GC_ENTITY_MODIFY_RSP,	GKCTRLOSPEVENT_START + 96);

// ��ȡH.323ʵ����֤�б�
OSPEVENT(EV_CG_GETENTITYLIST_REQ,	GKCTRLOSPEVENT_START + 97);
// ��ȡH.323ʵ����֤�б���Ӧ
OSPEVENT(EV_GC_GETENTITYLIST_RSP,	GKCTRLOSPEVENT_START + 98);

//��ȡ��֤���н�ֹIP��Χ�б�
OSPEVENT(EV_CG_GKCFG_REGIPRNG_GETFORBIDLIST_REQ,	GKCTRLOSPEVENT_START + 99);
//��ȡ��֤���н�ֹIP��Χ�б���Ӧ
OSPEVENT(EV_CG_GKCFG_REGIPRNG_GETFORBIDLIST_RSP,	GKCTRLOSPEVENT_START + 100);
//��ȡpcmt��Ȩ�������
OSPEVENT( EV_CG_GKCFG_PCMT_AUTH_STATUS_REQ , GKCTRLOSPEVENT_START + 101 );
//��ȡpcmt��Ȩ�����Ӧ
OSPEVENT( EV_CG_GKCFG_PCMT_AUTH_STATUS_RSP , GKCTRLOSPEVENT_START + 102 );
//pcmt��Ȩ���֪ͨ
OSPEVENT( EV_CG_GKCFG_PCMT_AUTH_STATUS_NTF , GKCTRLOSPEVENT_START + 103 ); 
//end add.

//add by yj [20120807]
//��ȡGK�豸�ͺż�MAC��ַ
OSPEVENT( EV_CG_GKCFG_GK_MACADDR_PRODUCTID_REQ , GKCTRLOSPEVENT_START + 104 );
//��ȡGK�豸�ͺż�MAC��ַ��Ӧ
OSPEVENT( EV_CG_GKCFG_GK_MACADDR_PRODUCTID_RSP , GKCTRLOSPEVENT_START + 105 ); 
//end [20120807]

//add by yj for support all kinds of mts [20120924]
//��ȡ�������͵�mt��Ȩ�������
OSPEVENT( EV_CG_GKCFG_ALL_MT_AUTH_STATUS_REQ , GKCTRLOSPEVENT_START + 106 );
//��ȡ�������͵�mt��Ȩ�����Ӧ
OSPEVENT( EV_CG_GKCFG_ALL_MT_AUTH_STATUS_RSP , GKCTRLOSPEVENT_START + 107 );
//�������͵�mt��Ȩ���֪ͨ
OSPEVENT( EV_CG_GKCFG_ALL_MT_AUTH_STATUS_NTF , GKCTRLOSPEVENT_START + 108 ); 
//end [20120924]

//�ڲ���Ϣ
OSPEVENT( EV_PRINT_REG,                   	GKCTRLOSPEVENT_START + 140);
OSPEVENT( EV_PRINT_REGDB,     	            GKCTRLOSPEVENT_START + 141);
OSPEVENT( EV_PRINT_CALL,     	            GKCTRLOSPEVENT_START + 142);
OSPEVENT( EV_PRINT_CALLDB,     	            GKCTRLOSPEVENT_START + 143);
OSPEVENT( EV_PRINT_IRQDB,     	            GKCTRLOSPEVENT_START + 144);
OSPEVENT( EV_PRINT_TIMER,                   GKCTRLOSPEVENT_START + 145);
OSPEVENT( EV_PRINT_DELAYDB,                 GKCTRLOSPEVENT_START + 146);

OSPEVENT( EV_PRINT_CONFIGDB,                GKCTRLOSPEVENT_START + 147);


OSPEVENT( EV_INTER_AUTHENDPOINT,        	GKCTRLOSPEVENT_START + 150);
OSPEVENT( EV_INTER_ISNEIGHBORGKPREFIX,     	GKCTRLOSPEVENT_START + 151);
OSPEVENT( EV_INTER_ISBANDWIDRHALLOWED,     	GKCTRLOSPEVENT_START + 152);
OSPEVENT( EV_INTER_GETALLREGEP,          	GKCTRLOSPEVENT_START + 153);
OSPEVENT( EV_INTER_GETALLCALL,          	GKCTRLOSPEVENT_START + 154);
OSPEVENT( EV_INTER_SHOWALLREALTIMEBWINFO,  	GKCTRLOSPEVENT_START + 155);

OSPEVENT( EV_RADIUS_OFF,  	              GKCTRLOSPEVENT_START + 156);
OSPEVENT( EV_RADIUS_SELECT,     	      GKCTRLOSPEVENT_START + 157);
OSPEVENT( EV_RADIUS_REGACK,  	          GKCTRLOSPEVENT_START + 158);
OSPEVENT( EV_RADIUS_REGREJ,               GKCTRLOSPEVENT_START + 159);

//���ʿ�ʼ
OSPEVENT( EV_RADIUS_ACCOUNT_START,    	      GKCTRLOSPEVENT_START + 161);
//���ʽ���
OSPEVENT( EV_RADIUS_ACCOUNT_STOP,    	      GKCTRLOSPEVENT_START + 162);

//OSPEVENT( EV_RADIUS_ACCTTIMEOUT,  	      GKCTRLOSPEVENT_START + 163);

//��֤����
OSPEVENT( EV_RADIUS_ACCESS_REQ,                  GKCTRLOSPEVENT_START + 164);

//radius��֤���  add by guozhongjun 2006.06.21
OSPEVENT(EV_RADIUS_AUTH_RESULT,               GKCTRLOSPEVENT_START + 165);

OSPEVENT(EV_RADIUS_ACCESS_ACK,               GKCTRLOSPEVENT_START + 166);
OSPEVENT(EV_RADIUS_ACCESS_REJ,               GKCTRLOSPEVENT_START + 167);
OSPEVENT(EV_RADIUS_ACCOUNT_ACK,               GKCTRLOSPEVENT_START + 168);
OSPEVENT(EV_RADIUS_ACCOUNT_REJ,               GKCTRLOSPEVENT_START + 169);

//GK�ڲ�ʹ�õ���Ӧ��Ϣ
//������֤���
OSPEVENT(EV_GK_CONF_AUTH_RESULT, GKCTRLOSPEVENT_START + 170);
//����Ʒѽ��
OSPEVENT(EV_GK_CONF_ACCT_RESULT, GKCTRLOSPEVENT_START + 171);

//GK�ڲ�ʹ�õ���Ӧ��Ϣ
//����Ʒ�ʵ��
OSPEVENT(EV_GK_CONF_ACTIVATE_INST, GKCTRLOSPEVENT_START + 172);  
//����Ʒ�ˢ����Ӧ
OSPEVENT(EV_GK_CONF_UPDATE_RESULT, GKCTRLOSPEVENT_START + 173); 


//GKInterReg ��Ϣ  add by shigubin
OSPEVENT( EV_INTERGK_START,     GKCTRLOSPEVENT_START + 174 );
OSPEVENT( EV_GKINTER_REGINFO,   GKCTRLOSPEVENT_START + 175 );
OSPEVENT( EV_GKINTER_UNREGINFO, GKCTRLOSPEVENT_START + 176 );
OSPEVENT( EV_INTERGK_UNREGALLINTERREG, GKCTRLOSPEVENT_START + 177 );
//GkInterReg ��Ϣ  Add End



OSPEVENT( GKCTRLOSPEVENT_END, GKCTRLOSPEVENT_START+ 200 );

//////////////////////////////////////////////////////////////////////////
OSPEVENT( GKTEST_START, EV_TEST_GKC_BGN );

OSPEVENT( EV_TEST_GETBASECFG,               GKTEST_START+1 );
OSPEVENT( EV_TEST_ISUSEREXIST,              GKTEST_START+2 );
OSPEVENT( EV_TEST_ISUSERLOGINED,            GKTEST_START+3 );
OSPEVENT( EV_TEST_ISFORBIDIPRNGEXIST,       GKTEST_START+4 );
OSPEVENT( EV_TEST_ISREGIPRNGEXIST,          GKTEST_START+5 );
OSPEVENT( EV_TEST_ISBSBEXIST,               GKTEST_START+6 );
OSPEVENT( EV_TEST_ISALLOWEDEPINDB,          GKTEST_START+7 );
OSPEVENT( EV_TEST_ISFORBIDEPINDB,           GKTEST_START+8 );

OSPEVENT( EV_TEST_GETONLINEENDPOINT_COUNT,  GKTEST_START+9 );
OSPEVENT( EV_TEST_ISENDPOINTREGISTERED,     GKTEST_START+10 );
OSPEVENT( EV_TEST_ISCALLEXIST,              GKTEST_START+11 );
OSPEVENT( EV_TEST_ISPREFIXEXIST,            GKTEST_START+12 );
OSPEVENT( EV_TEST_NEIGHBORGKINFO,           GKTEST_START+13 );
OSPEVENT( EV_TEST_GETEPALIASESBYIP,         GKTEST_START+14 );
OSPEVENT( EV_TEST_CLEARALL_CFG,             GKTEST_START+15 );

OSPEVENT( EV_TEST_GETLOGINUSERCOUNT,        GKTEST_START+16 );
OSPEVENT( EV_TEST_REBOOTGK,                 GKTEST_START+17 );

//Radiusconfig add by guozhongjun
OSPEVENT( EV_TEST_RADIUS_CONFIG,            GKTEST_START+18 );

OSPEVENT( GKTEST_END, EV_TEST_GKC_END );


//////////////////////////////// ö������ //////////////////////////////


//����ִ�н��
enum GKResult
{
    gk_err = -1,
    gk_ok
};

#ifndef CM_H
//ʵ������
typedef enum
{
    cmEndpointTypeTerminal,
    cmEndpointTypeGateway,
    cmEndpointTypeMCU,
    cmEndpointTypeGK,
    cmEndpointTypeUndefined,
    cmEndpointTypeSET
} cmEndpointType;

typedef enum
{
    cmCallTypeP2P,
    cmCallTypeOne2N,
    cmCallTypeN2One,
    cmCallTypeN2Nw
} cmCallType;

typedef enum
{
    cmCallModelTypeDirect,
    cmCallModelTypeGKRouted
} cmCallModelType;

typedef enum
{
    cmRASDisengageReasonForcedDrop,
    cmRASDisengageReasonNormalDrop,
    cmRASDisengageReasonUndefinedReason
}cmRASDisengageReason;

typedef enum
{
    cmRASUnregReasonReregistrationRequired,
    cmRASUnregReasonTtlExpired,
    cmRASUnregReasonSecurityDenial,
    cmRASUnregReasonUndefinedReason,
    cmRASUnregReasonMaintenance
}cmRASUnregReason;

typedef enum
{
    cmRASReasonResourceUnavailable,             /* GRJ, RRJ, ARJ, LRJ - gatekeeper resources exhausted */
    cmRASReasonInsufficientResources,           /* BRJ */
    cmRASReasonInvalidRevision,                 /* GRJ, RRJ, BRJ */
    cmRASReasonInvalidCallSignalAddress,        /* RRJ */
    cmRASReasonInvalidRASAddress,               /* RRJ - supplied address is invalid */
    cmRASReasonInvalidTerminalType,             /* RRJ */
    cmRASReasonInvalidPermission,               /* ARJ - permission has expired */
                                                /* BRJ - true permission violation */
                                                /* LRJ - exclusion by administrator or feature */
    cmRASReasonInvalidConferenceID,             /* BRJ - possible revision */
    cmRASReasonInvalidEndpointID,               /* ARJ */
    cmRASReasonCallerNotRegistered,             /* ARJ */
    cmRASReasonCalledPartyNotRegistered,        /* ARJ - can't translate address */
    cmRASReasonDiscoveryRequired,               /* RRJ - registration permission has aged */
    cmRASReasonDuplicateAlias,                  /* RRJ - alias registered to another endpoint */
    cmRASReasonTransportNotSupported,           /* RRJ - one or more of the transports */
    cmRASReasonCallInProgress,                  /* URJ */
    cmRASReasonRouteCallToGatekeeper,           /* ARJ */
    cmRASReasonRequestToDropOther,              /* DRJ - can't request drop for others */
    cmRASReasonNotRegistered,                   /* DRJ, LRJ, INAK - not registered with gatekeeper */
    cmRASReasonUndefined,                       /* GRJ, RRJ, URJ, ARJ, BRJ, LRJ, INAK */
    cmRASReasonTerminalExcluded,                /* GRJ - permission failure, not a resource failure */
    cmRASReasonNotBound,                        /* BRJ - discovery permission has aged */
    cmRASReasonNotCurrentlyRegistered,          /* URJ */
    cmRASReasonRequestDenied,                   /* ARJ - no bandwidrg available */
                                                /* LRJ - cannot find location */
    cmRASReasonLocationNotFound,                /* LRJ - cannot find location */
    cmRASReasonSecurityDenial,                  /* GRJ, RRJ, URJ, ARJ, BRJ, LRJ, DRJ, INAK */
    cmRASReasonTransportQOSNotSupported,        /* RRJ */
    cmRASResourceUnavailable,                   /* Same as cmRASReasonResourceUnavailable */
    cmRASReasonInvalidAlias,                    /* RRJ - alias not consistent with gatekeeper rules */
    cmRASReasonPermissionDenied,                /* URJ - requesting user not allowed to unregister specified user */
    cmRASReasonQOSControlNotSupported,          /* ARJ */
    cmRASReasonIncompleteAddress,               /* ARJ, LRJ */
    cmRASReasonFullRegistrationRequired,        /* RRJ - registration permission has expired */
    cmRASReasonRouteCallToSCN,                  /* ARJ, LRJ */
    cmRASReasonAliasesInconsistent,             /* ARJ, LRJ - multiple aliases in request identify distinct people */
    cmRASReasonAdditiveRegistrationNotSupported,/* RRJ */
    cmRASReasonInvalidTerminalAliases,          /* RRJ */
    cmRASReasonExceedsCallCapacity,             /* ARJ - destination does not have the capacity for this call */
    cmRASReasonCollectDestination,              /* ARJ */
    cmRASReasonCollectPIN,                      /* ARJ */
    cmRASReasonGenericData,                     /* GRJ, RRJ, ARJ, LRJ */
    cmRASReasonNeededFeatureNotSupported,       /* GRJ, RRJ, ARJ, LRJ */
    cmRASReasonUnknownMessageResponse,          /* XRS message was received for the request */
    cmRASReasonHopCountExceeded,                /* LRJ */
    cmRASReasonNoH323ID,                        /* no h323id */
    cmRASReasonAuthFalse                        /* AuthFalse */

}cmRASReason;

#endif //CM_H

//��֤ѡ��
enum emAuthMethod
{
    emAuthMethod_NotAuth        = 0,       //����Ҫ��֤
    emAuthMethod_AuthIPAllow    = 1,       //IP��֤��������Ч
    emAuthMethod_AuthIPForbid   = 2,       //IP��֤����ֹ��Ч

    emAuthMethod_AuthAliasAllow = 4,       //ʵ����֤��������Ч
    emAuthMethod_AuthAliasForbid= 8,       //ʵ����֤����ֹ��Ч

    emAuthMethod_AuthPassword   = 16,       //������֤
    emAuthMethod_AuthRadius     = 32        //Radius��֤ add by guozhongjun 2006.06.21

};

// ���ݿ��������ֵ
enum emGKDBRet
{
    emGKDBRet_Success = 0,        // �ɹ�
    emGKDBRet_UnknownErr,         // δ֪����
    emGKDBRet_KeyExist,           // key����
    emGKDBRet_DstKeyExist,        // key����
    emGKDBRet_DBErr,              // ���ݿ����
    emGKDBRet_InvalidData,        // �Ƿ�����
    emGKDBRet_InvalidRcvParam,    // ���ղ������Ϸ�
    emGKDBRet_KeyNotFound,        // δ�ҵ���¼
    emGKDBRet_AllRemoved          // ���м�¼����ɾ��
};

//GK�豸�ͺ�
typedef enum
{
    cmGKPruduct_Unknown = 0,		//λ���豸�ͺ�
	cmGKPruduct_GK,					//�豸�ͺ�ΪGK
	cmGKPruduct_Win32				//�豸�ͺ�Ϊwin32���԰汾
}cmGKPruductID;

//////////////////////////////////////////////////////////////////////////
#define GK_ERROR_CODE_BASE                      20000

#define GK_ERROR_NEW_FAIL                       (GK_ERROR_CODE_BASE + 10)
#define GK_ERROR_TIMER_PARAM                    (GK_ERROR_CODE_BASE + 11)
#define GK_ERROR_TIMER_ALLOC                    (GK_ERROR_CODE_BASE + 12)
#define GK_ERROR_TIMER_NULL                     (GK_ERROR_CODE_BASE + 13)
#define GK_ERROR_TIMER_NOTFOUND                 (GK_ERROR_CODE_BASE + 14)
#define GK_ERROR_TIMER_STATE                    (GK_ERROR_CODE_BASE + 15)


//AUTH
#define GK_ERROR_AUTH_KEY_NOTFOUND              (GK_ERROR_CODE_BASE + 20)
#define GK_ERROR_BW_TOOBIG                      (GK_ERROR_CODE_BASE + 21)
#define GK_ERROR_REG_FORBID                     (GK_ERROR_CODE_BASE + 22)
#define GK_ERROR_REG_IP_FORBID                  (GK_ERROR_CODE_BASE + 23)
#define GK_ERROR_REG_ALIAS_FORBID               (GK_ERROR_CODE_BASE + 24)
#define GK_ERROR_REG_PASS_FORBID                (GK_ERROR_CODE_BASE + 25)

//RRQ
#define GK_ERROR_ALIAS_DUPLICATE                (GK_ERROR_CODE_BASE + 26)
#define GK_ERROR_EPID_NOTFOUND                  (GK_ERROR_CODE_BASE + 27)
#define GK_ERROR_INVALID_REQSN					(GK_ERROR_CODE_BASE + 28)

//RCF
#define GK_ERROR_RCF_SET_CALLADDR               (GK_ERROR_CODE_BASE + 35)
#define GK_ERROR_RCF_SET_ALIAS                  (GK_ERROR_CODE_BASE + 36)
#define GK_ERROR_RCF_SET_EPID                   (GK_ERROR_CODE_BASE + 37)
#define GK_ERROR_RCF_SET_WILLIRR                (GK_ERROR_CODE_BASE + 38)
#define GK_ERROR_RCF_SEND_RCF                   (GK_ERROR_CODE_BASE + 39)


//UCF
#define GK_ERROR_UCF_SEND_UCF                   (GK_ERROR_CODE_BASE + 40)

//ARQ
#define GK_ERROR_ARQ_STATE                      (GK_ERROR_CODE_BASE + 41)

//ACF
#define GK_ERROR_ACF_SET_BANDWIDTH              (GK_ERROR_CODE_BASE + 51)
#define GK_ERROR_ACF_SET_CALLMODEL              (GK_ERROR_CODE_BASE + 52)
#define GK_ERROR_ACF_SET_CALLADDR               (GK_ERROR_CODE_BASE + 53)
#define GK_ERROR_ACF_SET_RESPONDIRR             (GK_ERROR_CODE_BASE + 54)
#define GK_ERROR_ACF_SEND                       (GK_ERROR_CODE_BASE + 55)


//DCF
#define GK_ERROR_DCF_SEND                       (GK_ERROR_CODE_BASE + 60)

//BCF
#define GK_ERROR_BCF_SET_BANDWIDTH              (GK_ERROR_CODE_BASE + 70)
#define GK_ERROR_BCF_SEND                       (GK_ERROR_CODE_BASE + 71)



//LRQ
#define GK_ERROR_LRQ_SET_ALIAS                  (GK_ERROR_CODE_BASE + 80)
#define GK_ERROR_LRQ_SET_REPLAYADDR             (GK_ERROR_CODE_BASE + 81)
#define GK_ERROR_LRQ_SEND                       (GK_ERROR_CODE_BASE + 82)
//���ӻ���GK��ͨ(CallId)
#define GK_ERROR_LRQ_SET_NONSTD                 (GK_ERROR_CODE_BASE + 83)
//end

//LCF
#define GK_ERROR_LCF_SET_CALLADDR               (GK_ERROR_CODE_BASE + 90)
#define GK_ERROR_LCF_SET_RASADDR                (GK_ERROR_CODE_BASE + 91)
#define GK_ERROR_LCF_SEND                       (GK_ERROR_CODE_BASE + 92)

//GCF
#define GK_ERROR_GCF_SET_RASADDR                (GK_ERROR_CODE_BASE + 100)
#define GK_ERROR_GCF_SEND                       (GK_ERROR_CODE_BASE + 101)
#define GK_ERROR_REJECT_MSG_NULL                (GK_ERROR_CODE_BASE + 102)

#define GK_ERROR_REJECT_SEND                    (GK_ERROR_CODE_BASE + 200)
#define GK_ERROR_MSG                            (GK_ERROR_CODE_BASE + 201)
#define GK_MSG_DELAY                            (GK_ERROR_CODE_BASE + 202)
#define GK_ERROR_GKID                           (GK_ERROR_CODE_BASE + 203)

/* DB ERROR CODE */
#define GK_ERROR_DB_BASE                   (GK_ERROR_CODE_BASE + 1000)
#define GK_ERROR_DB_UNKNOWN                (GK_ERROR_DB_BASE + emGKDBRet_UnknownErr)
#define GK_ERROR_DB_KEYEXIST               (GK_ERROR_DB_BASE + emGKDBRet_KeyExist)
#define GK_ERROR_DB_DSTKEYEXIST            (GK_ERROR_DB_BASE + emGKDBRet_DstKeyExist)
#define GK_ERROR_DB_DBERR                  (GK_ERROR_DB_BASE + emGKDBRet_DBErr)
#define GK_ERROR_DB_INVALIDDATA            (GK_ERROR_DB_BASE + emGKDBRet_InvalidData)
#define GK_ERROR_DB_INVALIDPARAM           (GK_ERROR_DB_BASE + emGKDBRet_InvalidRcvParam)
#define GK_ERROR_DB_KEYNOTFOUND            (GK_ERROR_DB_BASE + emGKDBRet_KeyNotFound)
#define GK_ERROR_DB_ALLREMOVED             (GK_ERROR_DB_BASE + emGKDBRet_AllRemoved)



//////////////////////////////// �ṹ���� //////////////////////////////



//��������
typedef struct tagAliasAddr
{
private:
    cmAliasType 	m_emAliasType;
    s8			    m_achAliasName[MAX_ALIASNAME_LEN+1];
    u16             m_wAliasNameLen;

public:
    tagAliasAddr()
	{
		Clear();
	}

	BOOL operator==(tagAliasAddr& tAlias)
	{
		if ( GetAliasType() == tAlias.GetAliasType() )
		{
			s8 szSrcAliasName[MAX_ALIASNAME_LEN+1] = {0};
			s8 szDstAliasName[MAX_ALIASNAME_LEN+1] = {0};

			u16 wSrcLen = GetAliasName( szSrcAliasName, MAX_ALIASNAME_LEN );
			u16 wDstLen = tAlias.GetAliasName( szDstAliasName, MAX_ALIASNAME_LEN );

			if ( wSrcLen == wDstLen &&
				 memcmp( szSrcAliasName, szDstAliasName, wSrcLen ) == 0 )
			{
				return TRUE;
			}
		}

		return FALSE;
	}

	void Clear()
    {
        m_emAliasType = (cmAliasType)0;
        m_wAliasNameLen = 0;
        memset( m_achAliasName, 0, MAX_ALIASNAME_LEN+1 );
    }

    void SetAliasType(cmAliasType aliasType)
    {
        m_emAliasType = (cmAliasType)htonl(aliasType);
    }

    cmAliasType GetAliasType()
    {
        return (cmAliasType)ntohl(m_emAliasType);
    }
    
    u16 GetAliasNameLen()
    {
        return ntohs(m_wAliasNameLen);
    }

    BOOL SetAlias(cmAliasType aliasType, s8 *pszName, u16 wLen, BOOL bGetFromStack = FALSE)
    {
        SetAliasType(aliasType);
        return SetAliasName(pszName, wLen, bGetFromStack);
    }

    //��֮ǰ�������趨��������
    //��ΪBMP���͵ı��������ڲ�����ΪBMPString�����ظ��ϲ�ʱΪString
    BOOL SetAliasName(s8 *pszName, u16 wLen, BOOL bGetFromStack = FALSE)
    {
        
        u16 maxLen = 0;
        cmAliasType aliasType = GetAliasType();
        
        if ( bGetFromStack == FALSE )
        {
            if ( aliasType == cmAliasTypeH323ID
                || aliasType == cmAliasTypeEndpointID
                || aliasType == cmAliasTypeGatekeeperID)
            {
                //ת��BMPString
                s8 chrStr[MAX_ALIASNAME_LEN+1] = {0};
                memcpy( chrStr, pszName, wLen );

                m_wAliasNameLen = utlChr2Bmp( chrStr, (BYTE*)m_achAliasName );

                maxLen = (aliasType == cmAliasTypeH323ID? MAX_ALIASNAME_LEN:MAX_E164_LEN);

                if (m_wAliasNameLen > maxLen) 
                    return FALSE;

                m_achAliasName[m_wAliasNameLen] = '\0';
                m_wAliasNameLen = htons(m_wAliasNameLen);

                return TRUE;
            }
        }

       
        maxLen = (aliasType == cmAliasTypeE164 ? MAX_E164_LEN:MAX_ALIASNAME_LEN);
        if (wLen > maxLen) 
            return FALSE;
        memset(m_achAliasName,0,MAX_ALIASNAME_LEN+1);
        memcpy(m_achAliasName, pszName, wLen);
        m_achAliasName[wLen] = '\0';

        m_wAliasNameLen = htons(wLen);
        return TRUE;
    }

    u16 GetAliasName( INOUT s8 *pszName, IN u16 wNameLen, IN BOOL bToStack = FALSE )
    {
        if ( pszName == NULL )
            return 0;

        u16 wAliasNameLen = ntohs(m_wAliasNameLen);

        if ( bToStack == TRUE )
        {
            if ( wNameLen < wAliasNameLen )
                return 0;

            memcpy( pszName, m_achAliasName, wAliasNameLen );
            return wAliasNameLen;
        }

        cmAliasType aliasType = GetAliasType();

        if ( aliasType == cmAliasTypeH323ID
            || aliasType == cmAliasTypeEndpointID
            || aliasType == cmAliasTypeGatekeeperID)
        {
            //ת���ɵ��ֽ�string
            s8 chrStr[MAX_ALIASNAME_LEN+1] = {0};
            utlBmp2Chr( chrStr, (BYTE*)m_achAliasName, wAliasNameLen );
            wAliasNameLen = strlen( chrStr );

            if ( wNameLen < wAliasNameLen )
                return 0;

            strcpy( pszName, chrStr );
        }
        else
        {
            if ( wNameLen < wAliasNameLen )
                return 0;

            strcpy( pszName, m_achAliasName );
        }

        return wAliasNameLen;
    }

}TAliasAddr,*PTAliasAddr;

//transport��ַ
typedef struct tagNetAddr
{
private:
    u32 m_dwIP;
    u16 m_wPort;
public:
    void SetNetAddr(u32 dwIP, u16 wPort)
    {
        m_dwIP = dwIP;
        m_wPort = htons(wPort);
    }

    void SetIPAddr(u32 dwIP)
    {
        m_dwIP = dwIP;
    }
    u32 GetIPAddr()
    {
        return m_dwIP;
    }

    void SetIPPort(u16 wPort)
    {
        m_wPort = htons(wPort);
    }
    u16 GetIPPort()
    {
        return ntohs(m_wPort);
    }

	BOOL operator==(tagNetAddr& tAddr)
	{
		if ( GetIPAddr() == tAddr.GetIPAddr()
			&& GetIPPort() == tAddr.GetIPPort() )
		{
			return TRUE;
		}

		return FALSE;
	}

    tagNetAddr()
    {
        m_dwIP  = 0;
        m_wPort = 0;
    }    
}TNETADDR,*PTNETADDR;

//����̨����ͨ�ýṹ
//�����������Ϣ�Ĺ���ͷ������Ϣ��Ϊ��Ӧ��Ϣ����ʹ�õĽṹ��
typedef struct tagGKCtrlBufHead
{
private:
    u32     m_dwSequenceNumber;  //���к�
    u32     m_dwErrorCode;       //������
    u32     m_dwContentLen;      //��Ϣ�����ݳ���
    u32     m_dwStructNum;       //��Ϣ��Ľṹ����Ŀ
    BOOL    m_bStructLenChange;  //��Ϣ��Ľṹ�����Ƿ�仯
    BOOL    m_bWillContinue;     //�Ƿ��к�������Ϣ��������Ϣ�峤��̫�������    
  
public:
    tagGKCtrlBufHead()
    {
        m_dwSequenceNumber = 0;
        m_dwErrorCode = 0;
        m_dwContentLen = 0;
        m_dwStructNum = 0;
        m_bStructLenChange = FALSE;
        m_bWillContinue = FALSE;
    }

    void SetSequenceNumber(u32 dwSequenceNumber)
    {
        m_dwSequenceNumber = htonl(dwSequenceNumber);//zhx�޸ĳ�������
    }
    u32 GetSequenceNumber()
    {
        return ntohl(m_dwSequenceNumber);
    }

    void SetErrorCode(u32 dwErrorCode)
    {
        m_dwErrorCode = htonl(dwErrorCode);
    }
    u32 GetErrorCode()
    {
        return ntohl(m_dwErrorCode);
    }

    void SetContentLen(u32 dwContentLen)
    {
        m_dwContentLen = htonl(dwContentLen);
    }
    u32 GetContentLen()
    {
        return ntohl(m_dwContentLen);
    }
    
    void SetStructNum(u32 dwStructNum)
    {
        m_dwStructNum = htonl(dwStructNum);
    }
    u32 GetStructNum()
    {
        return ntohl(m_dwStructNum);
    }

    void SetStructLenChange(BOOL bStructLenChange)
    {
        m_bStructLenChange = htonl(bStructLenChange);
    }
    BOOL IsStructLenChange()
    {
        return ntohl(m_bStructLenChange);
    }
    
    void SetWillContinue(BOOL bWillContinue)
    {
        m_bWillContinue = htonl(bWillContinue);
    }
    BOOL IsWillContinue()
    {
        return ntohl(m_bWillContinue);
    }

}TGKCtrlBufHead,*PTGKCtrlBufHead;

//�����������Ϣ��Ϊ�䳤�ṹʱÿ���䳤�ṹ��ͷ����
//��Ϣ��Ϊ:
//ѹ����ĳ���Ϊm_dwAliasBufLen�ı������������е�m_byCallAddrNum�����������ַ
//���б�����������ʵ���������ʵ���EndpointIdentifier
typedef struct tagGKCtrlBufBodyHead
{
private:
    cmEndpointType	m_emEndpointType;       //�ն�����
    TNETADDR        m_tRasAddr;             //RAS��ַ
    u16				m_wCallAddrNum;         //���������ַ�ĸ���    
    u16				m_wAliasNum;            //��������
    u32             m_dwAliasBufLen;        //ѹ����ı���buf����
    u32             m_dwTimerId;
    u32             m_dwTTL;

public:
    void SetTimerId( u32 dwTimerId)
    {
        m_dwTimerId = htonl(dwTimerId);
    }
    u32 GetTimerId()
    {
        return ntohl(m_dwTimerId);
    }

    void SetTerminalType( cmEndpointType emEndpointType )
    {
        m_emEndpointType = (cmEndpointType)htonl(emEndpointType);
    }
    cmEndpointType GetTerminalType()
    {
        return (cmEndpointType)ntohl(m_emEndpointType);
    }

    void SetAliasNum( u16 wAliasNum )
    {
        m_wAliasNum = htons(wAliasNum);
    }
    u16 GetAliasNum()
    {
        return ntohs(m_wAliasNum);
    }
    
    void SetAliasBufLen( u32 dwAliasBufLen )
    {
        m_dwAliasBufLen = htonl(dwAliasBufLen);
    }
    u32 GetAliasBufLen()
    {
        return ntohl(m_dwAliasBufLen);
    }

    void SetRASAddr( TNETADDR &tRASAddr )
    {
        m_tRasAddr = tRASAddr;
    }
    TNETADDR* GetRASAddr()
    {
        return &m_tRasAddr;
    }

    void SetCallAddrNum( u16 wCallAddrNum )
    {
        m_wCallAddrNum = htons(wCallAddrNum);
    }
    u16 GetCallAddrNum()
    {
        return ntohs(m_wCallAddrNum);
    }
}TGKCtrlBufBodyHead,*PTGKCtrlBufBodyHead;

//����̨�û���½��Ϣ���ݿ�ṹ
//���û���Ϊkey
typedef struct tagCtrlUserDBData
{
private:
    u8		m_abyUserName[MAX_USERNAME_LEN];
    u16		m_wUserNameLen;
    u8		m_abyPassword[MAX_PASSWORD_LEN];
    u16		m_wPasswordLen;
    BOOL 	m_bAdministrator;

public:
    BOOL SetUserName( IN u8 *pbyUserName, IN u16 wNameLen )
    {
        if ( pbyUserName == NULL || wNameLen > MAX_USERNAME_LEN )
            return FALSE;

        memcpy( m_abyUserName, pbyUserName, wNameLen );
        m_wUserNameLen = htons( wNameLen );
        return TRUE;
    }

    u16 GetUserNameLen()
    {
        return ntohs( m_wUserNameLen );
    }

    void GetUserName( OUT u8 *pbyUserName, OUT u16 &wNameLen )
    {
        if ( pbyUserName == NULL || wNameLen < ntohs( m_wUserNameLen ) )
            return;

        wNameLen = ntohs( m_wUserNameLen );
        memcpy( pbyUserName, m_abyUserName, wNameLen );
    }

    BOOL SetPassword( IN u8 *pbyPassword, IN u16 wPassLen )
    {
        if ( pbyPassword == NULL || wPassLen > MAX_PASSWORD_LEN )
            return FALSE;
        
        memcpy( m_abyPassword, pbyPassword, wPassLen );
        m_wPasswordLen = htons( wPassLen );
        return TRUE;
    }
  
    u16 GetPasswordLen()
    {
        return ntohs( m_wPasswordLen );
    }
    
    void GetPassword( OUT u8 *pbyPassword, OUT u16 &wPassLen )
    {
        if ( pbyPassword == NULL || wPassLen < ntohs( m_wPasswordLen ) )
            return;
        
        wPassLen = ntohs( m_wPasswordLen );
        memcpy( pbyPassword, m_abyPassword, wPassLen );
    }

    void SetAdministrator( IN BOOL bAdministrator )
    {
        m_bAdministrator = htonl( bAdministrator );
    }
    
    BOOL IsAdministrator()
    {
        return ntohl( m_bAdministrator );
    }
    
    tagCtrlUserDBData()
    {
        memset( m_abyUserName, 0, sizeof(m_abyUserName) );
        memset( m_abyPassword, 0, sizeof(m_abyPassword) );
        
        m_wUserNameLen = 0;
        m_wPasswordLen = 0;
        m_bAdministrator = FALSE;
    }    
}TCtrlUserDBData,*PTCtrlUserDBData;


#ifdef WIN32
#pragma comment( lib, "ws2_32.lib" ) 
#pragma pack( push )
#pragma pack( 1 )
#define window( x )	x
#define PACKED 
#else
#include <netinet/in.h>
#define window( x )
#define PACKED __attribute__((__packed__))	// ȡ�����������Ż�����
#endif


//GKǰ׺�ṹ
typedef struct tagGKPrefix
{
private:
    u8		m_abyPrefix[MAX_GKPREFIX_LEN];
    u8		m_abyPrefixLen;

public:
    BOOL SetPrefix( IN u8 *pbyPrefix, IN u8 byPrefixLen )
    {
        if ( pbyPrefix == NULL || byPrefixLen > MAX_GKPREFIX_LEN )
            return FALSE;
        
        memset(m_abyPrefix,0,MAX_GKPREFIX_LEN);
        memcpy( m_abyPrefix, pbyPrefix, byPrefixLen );
        m_abyPrefixLen = byPrefixLen;
        return TRUE;
    }
    
    u8 GetPrefixLen()
    {
        return m_abyPrefixLen;
    }
    
    void GetPrefix( OUT u8 *pbyPrefix, OUT u8 &byPrefixLen )
    {
        if ( pbyPrefix == NULL || byPrefixLen < m_abyPrefixLen )
		{
			byPrefixLen = 0;
            return;
		}
        
        byPrefixLen = m_abyPrefixLen;
        memcpy( pbyPrefix, m_abyPrefix, byPrefixLen );
    }
    
    tagGKPrefix()
    {
        memset(m_abyPrefix,0,MAX_GKPREFIX_LEN);
        m_abyPrefixLen = 0;
    }
}
#if defined(_VXWORKS_) || defined(_LINUX_)
__attribute__ ( (packed) ) 
#endif // _VXWORKS_

TGKPrefix,*PTGKPrefix;


//�ھ�GK��Ϣ
typedef struct tagNeighborGKInfo
{
	//����ṹ����Ҫ�������ת����Ip����Ϊ������
	//TGKPrefix��Ա����u8��(zhx 05-10-13 ע)
    u32         m_dwNeighborGKIP;
    TGKPrefix   m_tNeighborGKPrefix;

    tagNeighborGKInfo()
    {
        m_dwNeighborGKIP = 0;
    }
}

#if defined(_VXWORKS_) || defined(_LINUX_)
__attribute__ ( (packed) ) 
#endif // _VXWORKS_

TNeighborGKInfo;

#ifdef WIN32
#pragma pack( pop )
#endif

//������Ϣ���ݿ��е�GK����������Ϣ���ݿ�ṹ
//��AuthMethodΪkey �� m_emAuthMethod
//��TNeighborGKInfoΪkey �� NULL
//��PrefixΪkey �� NULL
typedef struct tagConfigBaseGKDBData
{
private:
    emAuthMethod	  m_emAuthMethod;
    TNeighborGKInfo   m_atNeighborGKInfo[MAX_NEIGHBORGK_NUM];
	u16				  m_wNeighborGKInfoNum;
    TGKPrefix         m_atLocalPrefix[MAX_GKPREFIX_NUM];
	u16				  m_wLocalPrefixNum;
    s8                m_szAuthPassword[MAX_PASSWORD_LEN+1];
	u16				  m_wAuthPasswordLen;
    u8                m_byIsUseEthFront;
    
public:
    void SetAuthPassword( s8 *pszPwd, u16 wPwdLen )
    {
        u16 wLen = min(wPwdLen, MAX_PASSWORD_LEN);
        strncpy( m_szAuthPassword, pszPwd, wLen );
        m_szAuthPassword[wLen] = '\0';

		m_wAuthPasswordLen = htons( wLen );
    }

	u16 GetAuthPasswordLen()
	{
		return ntohs( m_wAuthPasswordLen );
	}

    s8* GetAuthPassword()
    {
        return m_szAuthPassword;
    }

    void SetAuthMethod( emAuthMethod authMethod )
    {
        m_emAuthMethod = (emAuthMethod)htonl(authMethod);
    }
    emAuthMethod GetAuthMethod()
    {
        return (emAuthMethod)ntohl(m_emAuthMethod);
    }
    
    void SetNeighborGKInfo( TNeighborGKInfo atNeighborGKInfo[], u16 wNum )
    {
        for( s32 nIndex = 0; nIndex < min(wNum, MAX_NEIGHBORGK_NUM); nIndex++ )
            m_atNeighborGKInfo[nIndex] = atNeighborGKInfo[nIndex];

		m_wNeighborGKInfoNum = htons( min(wNum, MAX_NEIGHBORGK_NUM) );
    }	
    TNeighborGKInfo& GetNeighborGKInfo( u16 wNo )
    {
        if ( wNo < MAX_NEIGHBORGK_NUM ) 
            return m_atNeighborGKInfo[wNo];

        return m_atNeighborGKInfo[0];
    }
	u16 GetNeighborGKInfoNum()
	{
		return ntohs( m_wNeighborGKInfoNum );
	}
	void SetNeighborGKInfoNum( u16 wNum )
	{
		m_wNeighborGKInfoNum = htons( wNum );
	}
    TNeighborGKInfo* GetNeighborGKInfo()
    {
        return m_atNeighborGKInfo;
    }

    void SetLocalPrefix( TGKPrefix atGKPrefix[], u16 wNum )
    {
        for( s32 nIndex = 0; nIndex < min(wNum, MAX_GKPREFIX_NUM); nIndex++ )
            m_atLocalPrefix[nIndex] = atGKPrefix[nIndex];

		m_wLocalPrefixNum = htons( min(wNum,MAX_GKPREFIX_NUM) );
    }
    TGKPrefix& GetLocalPrefix( u16 wNo )
    {
        if ( wNo < MAX_GKPREFIX_NUM ) 
            return m_atLocalPrefix[wNo];
        
        return m_atLocalPrefix[0];
    }
	u16 GetLocalPrefixNum()
	{
		return ntohs( m_wLocalPrefixNum );
	}
	void SetLocalPrefixNum( u16 wNum )
	{
		m_wLocalPrefixNum = htons( wNum );
	}
    TGKPrefix* GetLocalPrefix()
    {
        return m_atLocalPrefix;
    }

    void SetIsUseEthFront(u8 byIsUseFront)
    {
        m_byIsUseEthFront = byIsUseFront;
    }

    u8 GetIsUseEthFront()
    {
        return m_byIsUseEthFront;
    }

    tagConfigBaseGKDBData()
    {
        m_emAuthMethod  = emAuthMethod_NotAuth;
        memset( m_szAuthPassword, 0, MAX_PASSWORD_LEN );
		m_wLocalPrefixNum = 0;
		m_wNeighborGKInfoNum = 0;
		m_wAuthPasswordLen = 0;
        m_byIsUseEthFront = 0;
    } 
    
}TConfigBaseGKDBData,*PTConfigBaseGKDBData;

//IP��Χ��֤
typedef struct tagAddrRng
{
private:
    u32 	m_dwIPAddrFrom;
    u32 	m_dwIPAddrTo;
public:
    tagAddrRng()
    {
        m_dwIPAddrFrom = 0;
        m_dwIPAddrTo = 0;
    }

    void SetIPAddrFrom( u32 dwIPAddr )
    {
        m_dwIPAddrFrom = dwIPAddr;
    }
    u32 GetIPAddrFrom()
    {
        return m_dwIPAddrFrom;
    }
    
    void SetIPAddrTo( u32 dwIPAddr )
    {
        m_dwIPAddrTo = dwIPAddr;
    }
    u32 GetIPAddrTo()
    {
        return m_dwIPAddrTo;
    }
}TAddrRng,*PTAddrRng;

//������Ϣ���ݿ��е�IP��Χ��֤���ݿ�ṹ
//��IndexΪkey
typedef struct tagConfigAuthIPDBData
{
private:
    TAddrRng 	m_tAddrRng;
    BOOL        m_bAllowed;     //�Ƿ�������Ч

public:
    void SetAddrRng( TAddrRng &tAddrRng )
    {
        m_tAddrRng = tAddrRng;
    }
    TAddrRng* GetAddrRng()
    {
        return &m_tAddrRng;
    }    

    void SetAuthMethod( BOOL bAuthAllow )
    {
        m_bAllowed = htonl( bAuthAllow );
    }
    BOOL IsAuthAllow()
    {
        return ntohl( m_bAllowed );
    }

    tagConfigAuthIPDBData()
    {
        m_bAllowed = FALSE;
    }    
}TConfigAuthIPDBData,*PTConfigAuthIPDBData;

//IP ��Χ�ṹ
typedef struct tagIPRange
{
private:
    u32		m_dwIPFrom;
    u32		m_dwIPFromMask;
    
    u32		m_dwIPTo;
    u32		m_dwIPToMask;
public:
    void SetIPFrom( u32 dwIPAddr, u32 dwIPMask )
    {
        m_dwIPFrom = dwIPAddr;
        m_dwIPFromMask = dwIPMask;
    }
    u32 GetIPFrom()
    {
        return m_dwIPFrom;
    }
    u32 GetIPFromMask()
    {
        return m_dwIPFromMask;
    }
    
    void SetIPTo( u32 dwIPAddr, u32 dwIPMask )
    {
        m_dwIPTo = dwIPAddr;
        m_dwIPToMask = dwIPMask;
    }
    u32 GetIPTo()
    {
        return m_dwIPTo;
    }
    u32 GetIPToMask()
    {
        return m_dwIPToMask;
    }
    
    tagIPRange()
    {
        m_dwIPFrom = 0;
        m_dwIPFromMask = 0;
        
        m_dwIPTo = 0;
        m_dwIPToMask = 0;
    }
}TIPRange,*PTIPRange;

//��������Data
typedef struct tagBandwidthCtrlData
{
private:
    u32			m_dwMaxBandwidth;           //ĳ����������������� ��λ��kbps
    u32			m_dwPerCallMaxBandwidth;    //ÿ�����е�˫�������� ��λ��kbps

public:
    tagBandwidthCtrlData()
    {
        m_dwMaxBandwidth = 0;
        m_dwPerCallMaxBandwidth = 0;
    }

    void SetMaxBandwidth( u32 dwBandwidth )
    {
        m_dwMaxBandwidth = htonl( dwBandwidth );
    }
    u32 GetMaxBandwidth()
    {
        return ntohl( m_dwMaxBandwidth );
    }
    
    void SetPerCallMaxBandwidth( u32 dwBandwidth )
    {
        m_dwPerCallMaxBandwidth = htonl( dwBandwidth );
    }
    u32 GetPerCallMaxBandwidth()
    {
        return ntohl( m_dwPerCallMaxBandwidth );
    }
}TBandwidthCtrlData, *PTBandwidthCtrlData;

//������Ϣ���ݿ��е����δ�����Ϣ���ݿ�ṹ
//��TIPRangeΪkey
typedef struct tagConfigBandWidthDBData
{
private:
    TIPRange	        m_tIPRange;
    TBandwidthCtrlData  m_tBWCtrlData;
public:
    void SetIPRange( TIPRange &tIPRange )
    {
        m_tIPRange = tIPRange;
    }
    PTIPRange GetIPRange()
    {
        return &m_tIPRange;
    }

    void SetBWCtrlData( TBandwidthCtrlData &tBWCtrlData )
    {
        m_tBWCtrlData = tBWCtrlData;
    }
    PTBandwidthCtrlData GetBWCtrlData()
    {
        return &m_tBWCtrlData;
    }
}TConfigBandWidthDBData,*PTConfigBandWidthDBData;

//������Ϣ���ݿ��е�������֤���ݿ��key
typedef struct tagAliasAuthKey
{
private:
    cmEndpointType  m_emEndpointType;
    TAliasAddr	    m_tAliasAddr;
public:
    void SetAliasAddr( TAliasAddr &tAliasAddr )
    {
        m_tAliasAddr = tAliasAddr;
    }
    PTAliasAddr GetAliasAddr()
    {
        return &m_tAliasAddr;
    }
    
    void SetEndpointType( cmEndpointType emEndpointType )
    {
        m_emEndpointType = (cmEndpointType)htonl(emEndpointType);
    }
    cmEndpointType GetEndpointType()
    {
        return (cmEndpointType)ntohl(m_emEndpointType);
    }
}TAliasAuthKey,*PTAliasAuthKey;

//[12/26/2007 zhangzhihua]add. 
//������Ϣ���ݿ��е�ʵ����֤���ݿ��Key.
typedef struct tagEntityAuthKey
{
private:
    cmEndpointType  m_emEndpointType;
	u16             m_wAliasNum;
    TAliasAddr	    m_atAliasAddr[MAX_ENTITYALIAS_NUM];
public:
	tagEntityAuthKey()
	{
		m_wAliasNum = 0;
		m_emEndpointType = cmEndpointTypeTerminal;
		memset(m_atAliasAddr, 0, sizeof(TAliasAddr)*MAX_ENTITYALIAS_NUM);

	}
	//����ʵ�����.
    void SetAliasAddr( TAliasAddr atAliasAddr[], u16 wAliasNum )
    {
		if (wAliasNum > MAX_ENTITYALIAS_NUM)
		{
			return;
		}

		for (u16 wAliasIndex = 0; wAliasIndex < wAliasNum; wAliasIndex++)
		{
			m_atAliasAddr[wAliasIndex] = atAliasAddr[wAliasIndex];
		}

		m_wAliasNum = htons(wAliasNum);
    }
	//��ȡʵ�����.
	TAliasAddr& GetAliasAddr(u16 wAliasNo)
	{
		if (wAliasNo < MAX_ENTITYALIAS_NUM)
		{
			return m_atAliasAddr[wAliasNo];
		}
		else
		{
           return m_atAliasAddr[0];
		}
	}

    //�õ�������.
	u16 GetAliasNum()
	{
		return ntohs(m_wAliasNum);
	}
    //�����ն�����.
    void SetEndpointType( cmEndpointType emEndpointType )
    {
        m_emEndpointType = (cmEndpointType)htonl(emEndpointType);
    }
	//��ȡ�ն�����.
    cmEndpointType GetEndpointType()
    {
        return (cmEndpointType)ntohl(m_emEndpointType);
    }

	void clear()
	{
		m_wAliasNum = 0;
		m_emEndpointType = cmEndpointTypeTerminal;
		memset(m_atAliasAddr, 0, sizeof(TAliasAddr)*MAX_ENTITYALIAS_NUM);
	}

}TEntityAuthKey,*PTEntityAuthKey;

// end add.
//������Ϣ���ݿ��е�ʵ����֤���ݿ��data
//emAuthMethodֻ�������¼��֣�
//      emAuthMethod_AuthAliasAllow = 4,                            //ʵ����֤��������Ч
//      emAuthMethod_AuthAliasForbid= 8,                            //ʵ����֤����ֹ��Ч
//      emAuthMethod_AuthAliasAllow|emAuthMethod_AuthPassword = 20  //ʵ��������֤
typedef struct tagAliasAuthData
{
private:
//    emAuthMethod    m_emAuthMethod;                 //[12/26/2007 zhangzhihua]del. 
    u8              m_byPasswordLen;
    u8              m_abyPassword[MAX_PASSWORD_LEN];
public:
    tagAliasAuthData()
    {
//         m_emAuthMethod = emAuthMethod_AuthAliasForbid;
        m_byPasswordLen = 0;
        memset( m_abyPassword, 0, sizeof(m_abyPassword));
    }
//     void SetAuthMethod( emAuthMethod method )
//     {
//         m_emAuthMethod = (emAuthMethod)htonl(method);
//     }
//     emAuthMethod GetAuthMethod()
//     {
//         return (emAuthMethod)ntohl(m_emAuthMethod);
//     }
//     
    BOOL SetPassword( u8 *pbyPwd, u8 byLen )
    {
        if ( pbyPwd != NULL && byLen < MAX_PASSWORD_LEN ) 
        {
            m_byPasswordLen = byLen;
            memcpy( m_abyPassword, pbyPwd, byLen );
            m_abyPassword[byLen] = 0;
            return TRUE;
        }
        
        return FALSE;
    }
    
    u8 GetPassword( u8 *pbyPwd, u8 byLen )
    {
        if ( pbyPwd == NULL || byLen < m_byPasswordLen )
            return 0;
        
        memcpy( pbyPwd, m_abyPassword, m_byPasswordLen );
        return m_byPasswordLen;
    }

    u8 GetPasswordLen()
    {
        return m_byPasswordLen;
    }
}TAliasAuthData,*PTAliasAuthData;

//������Ϣ���ݿ��е�������֤���ݿ�ṹ
//��TAliasAuthKeyΪkey
//��TAliasAuthDataΪdata
typedef struct tagConfigAliasAuthDBData
{
private:
    TAliasAuthKey	m_tAliasAuthKey;
    TAliasAuthData  m_tAliasAuthData;
public:
    void SetAliasAuthKey( TAliasAuthKey &tAliasAuthKey )
    {
        m_tAliasAuthKey = tAliasAuthKey;
    }
    PTAliasAuthKey GetAliasAuthKey()
    {
        return &m_tAliasAuthKey;
    }
    
    void SetAliasAuthData( TAliasAuthData &tAliasAuthData )
    {
        m_tAliasAuthData = tAliasAuthData;
    }
    PTAliasAuthData GetAliasAuthData()
    {
        return &m_tAliasAuthData;
    }
}TConfigAliasAuthDBData,*PTConfigAliasAuthDBData;

//[12/26/2007 zhangzhihua]add. 
//������Ϣ���ݿ��е�ʵ����֤���ݿ�ṹ
//��TEntityAuthKeyΪKey.
typedef struct tagConfigEntityAuthDBData
{
private:
    TEntityAuthKey	m_tEntityAuthKey;
// 	u8              m_abData;
public:
    void SetEntityAuthKey( TEntityAuthKey &tEntityAuthKey )
    {
        m_tEntityAuthKey = tEntityAuthKey;
    }
    PTEntityAuthKey GetEntityAuthKey()
    {
        return &m_tEntityAuthKey;
    }
// 	void SetEntityAuthData(u8 abData)
// 	{
// 		m_abData = abData;
// 	}
  
}TConfigEntityAuthDBData,*PTConfigEntityAuthDBData;
//end add.

//����ID�ṹ������̨����ʵʱ������Ϣʱʹ�øýṹ
typedef struct tagCtrlCallId
{
    s8  m_achCallId[LEN_GUID];
    
    tagCtrlCallId()
    {
        memset( m_achCallId, 0, LEN_GUID );
    }    
}TCtrlCallId,*PTCtrlCallId;

//����֪ͨ,�����̨�û�֪ͨ���е���
typedef struct tagCallIncInfoNtf
{
 private:
    TNETADDR			m_tSrcCallAddr;
    TAliasAddr          m_tSrcAliasAddr;
    u32					m_dwSrcCRV;
    
    TNETADDR			m_tDstCallAddr;
    TAliasAddr          m_tDstAliasAddr;
    u32					m_dwDstCRV;
    
    u16					m_wSendBandwidth;       //��λ��kbps
    u16					m_wRecvBandwidth;       //��λ��kbps
    
    time_t				m_dwStartTime;

    u32                 m_dwIRRTimerId;

public:
    void SetIRRTimerId( u32 dwIRRTimerId )
    {
        m_dwIRRTimerId = htonl( dwIRRTimerId );
    }
    u32 GetIRRTimerId()
    {
        return ntohl( m_dwIRRTimerId );
    }
    void SetSrcCallAddr( TNETADDR &tAddr )
    {
        m_tSrcCallAddr = tAddr;
    }
    TNETADDR& GetSrcCallAddr()
    {
        return m_tSrcCallAddr;
    }
    void SetSrcAliasAddr(cmAliasType AliasType, s8 *pszName, u16 wLen )
    {
        m_tSrcAliasAddr.SetAlias( AliasType, pszName, wLen );
    }
    TAliasAddr& GetSrcAliasAddr()
    {
        return m_tSrcAliasAddr;
    }
    void SetSrcCRV( u32 dwCRV )
    {
        m_dwSrcCRV = htonl( dwCRV );
    }
    u32 GetSrcCRV()
    {
        return ntohl( m_dwSrcCRV );
    }

    void SetDstCallAddr( TNETADDR &tAddr )
    {
        m_tDstCallAddr = tAddr;
    }
    TNETADDR& GetDstCallAddr()
    {
        return m_tDstCallAddr;
    }
    void SetDstAliasAddr(cmAliasType AliasType, s8 *pszName, u16 wLen )
    {
        m_tDstAliasAddr.SetAlias(AliasType, pszName, wLen );
    }
    TAliasAddr& GetDstAliasAddr()
    {
        return m_tDstAliasAddr;
    }
    void SetDstCRV( u32 dwCRV )
    {
        m_dwDstCRV = htonl( dwCRV );
    }
    u32 GetDstCRV()
    {
        return ntohl( m_dwDstCRV );
    }

    void SetSendBandwidth( u16 wSend )
    {
        m_wSendBandwidth = htons(wSend);
    }

    void SetRecvBandwidth( u16 wReceive )
    {
        m_wRecvBandwidth = htons(wReceive);
    }

    u16 GetSendBandwidth()
    {
        return ntohs(m_wSendBandwidth);
    }
    u16 GetRecvBandwidth()
    {
        return ntohs(m_wRecvBandwidth);
    }

    void SetStartTime(time_t tStartTime)
    {
        m_dwStartTime = htonl(tStartTime);
    }
    time_t GetStartTime()
    {
        return ntohl(m_dwStartTime);
    }

    tagCallIncInfoNtf()
    {
        m_dwSrcCRV = 0;
        m_dwDstCRV = 0;
        
        m_wSendBandwidth = 0;
        m_wRecvBandwidth = 0;

        m_dwStartTime = 0;
        m_dwIRRTimerId = 0;
    }       
}TCallIncInfoNtf;

//ʵʱ������Ϣ���ݿ�����CallIdentifierΪkey�Ľṹ
typedef struct tagCallIdDBData
{
private:
    TNETADDR			m_tSrcCallAddr;
    TAliasAddr          m_tSrcEpId;
    TAliasAddr          m_tSrcAlias;
    u32					m_dwSrcCRV;
    
    TNETADDR			m_tDstCallAddr;
    TAliasAddr          m_tDstEpId;
    TAliasAddr          m_tDstAlias;
    u32					m_dwDstCRV;
    
    u16					m_wSendBandwidth;       //��λ��kbps
    u16					m_wRecvBandwidth;       //��λ��kbps
    
    time_t				m_dwStartTime;

    u32                 m_dwIRRTimerId;

    s8  			    m_achConferenceID[LEN_GUID];//����ID

    u32                 m_dwIRRTTL;
    
    u32                m_dwSrcCall;
    u32                m_dwDstCall;

public:
    void SetIRRTTL(u32 dwTTL)
    {
        m_dwIRRTTL = htonl(dwTTL);
    }
    
    u32 GetIRRTTL()
    {
        return ntohl(m_dwIRRTTL);
    }
    
    void SetIRRTimerId( u32 dwIRRTimerId )
    {
        m_dwIRRTimerId = htonl( dwIRRTimerId );
    }
    u32 GetIRRTimerId()
    {
        return ntohl( m_dwIRRTimerId );
    }
    void SetSrcCallAddr( TNETADDR &tAddr )
    {
        m_tSrcCallAddr = tAddr;
    }
    TNETADDR& GetSrcCallAddr()
    {
        return m_tSrcCallAddr;
    }
    void SetSrcEpId( s8 *pszName, u16 wLen )
    {
        m_tSrcEpId.SetAlias( cmAliasTypeEndpointID, pszName, wLen );
    }
    TAliasAddr& GetSrcEpId()
    {
        return m_tSrcEpId;
    }

    void SetSrcAlias(TAliasAddr tAlias)
    {
        m_tSrcAlias = tAlias;
    }
    
    TAliasAddr& GetSrcAlias()
    {
        return m_tSrcAlias;
    }

    void SetSrcCRV( u32 dwCRV )
    {
        m_dwSrcCRV = htonl( dwCRV );
    }
    u32 GetSrcCRV()
    {
        return ntohl( m_dwSrcCRV );
    }

    void SetDstCallAddr( TNETADDR &tAddr )
    {
        m_tDstCallAddr = tAddr;
    }
    TNETADDR& GetDstCallAddr()
    {
        return m_tDstCallAddr;
    }
    void SetDstEpId( s8 *pszName, u16 wLen )
    {
        m_tDstEpId.SetAlias( cmAliasTypeEndpointID, pszName, wLen );
    }

    TAliasAddr& GetDstEpId()
    {
        return m_tDstEpId;
    }
    
    void SetDstAlias(TAliasAddr tAlias)
    {
        m_tDstAlias = tAlias;
    }

    TAliasAddr& GetDstAlias()
    {
        return m_tDstAlias;
    }

    void SetDstCRV( u32 dwCRV )
    {
        m_dwDstCRV = htonl( dwCRV );
    }
    u32 GetDstCRV()
    {
        return ntohl( m_dwDstCRV );
    }

    void SetSendBandwidth( u16 wSend )
    {
        m_wSendBandwidth = htons(wSend);
    }

    void SetRecvBandwidth( u16 wReceive )
    {
        m_wRecvBandwidth = htons(wReceive);
    }

    u16 GetSendBandwidth()
    {
        return ntohs(m_wSendBandwidth);
    }
    u16 GetRecvBandwidth()
    {
        return ntohs(m_wRecvBandwidth);
    }

    void SetStartTime(time_t tStartTime)
    {
        m_dwStartTime = htonl(tStartTime);
    }
    time_t GetStartTime()
    {
        return ntohl(m_dwStartTime);
    }

    void SetConferenceID(s8* pchConfId)
    {
        memcpy(m_achConferenceID, pchConfId, sizeof(m_achConferenceID));
    }

    s8* GetConferenceID()
    {
        return m_achConferenceID;
    }

    void SetDstCall(HCALL hsCall)
    {
        m_dwDstCall = htonl((u32)hsCall);
    }

    HCALL GetDstCall()
    {
        return (HCALL)ntohl(m_dwDstCall);
    }


    void SetSrcCall(HCALL hsCall)
    {
        m_dwSrcCall = htonl((u32)hsCall);
    }

    HCALL GetSrcCall()
    {
        return (HCALL)ntohl(m_dwSrcCall);
    }

    tagCallIdDBData()
    {
        m_dwSrcCRV = 0;
        m_dwDstCRV = 0;
        
        m_wSendBandwidth = 0;
        m_wRecvBandwidth = 0;

        m_dwStartTime = 0;
        
        m_dwIRRTimerId = 0;

        m_dwSrcCall = NULL;
        m_dwDstCall = NULL;
    }

}TCallIdDBData,*PTCallIdDBData;

//�Ʒ�����֤
//Radius secret�ṹ 
typedef struct tagRadiusSecret
{  
  private:
    u8  m_abySecret[MAX_RADIU_SECRET_LEN];       //secret : ��д�������  
    u16 m_wSecretLen;                           //length :  ������������ 
    
  public:
    tagRadiusSecret()
    {
        m_wSecretLen = 0;
        memset(m_abySecret,0,sizeof(m_abySecret));
    }

    /*====================================================================
    ������	��   RadiusAccessRejectCB
    ����:		����Secret
    �㷨ʵ��	������ѡ�
    ����ȫ�ֱ�����
    �������˵����pbySecret: secret buf.
                  wLen: secret�ĳ���.������������.
    ����ֵ˵����  �ɹ����� TRUE, ���򷵻� FALSE.
     ====================================================================*/
    BOOL SetSecret(IN u8* pbySecret, IN u16 wLen)
    {
        if(wLen > MAX_RADIU_SECRET_LEN)
        {
            return FALSE;
        }
        memset(m_abySecret, 0, sizeof(m_abySecret));
        memcpy(m_abySecret, pbySecret, wLen);
        m_wSecretLen = htons(wLen);        
        return TRUE;            
    }

    /*====================================================================
    ������	��   GetSecret 
    ����:		 ��ȡSecret
    �㷨ʵ��	������ѡ�
    ����ȫ�ֱ�����
    �������˵����pOutBuf: ��ȡsecret��Buf
                  wLen: Buf�ĳ���.
    ����ֵ˵����  �ɹ�����Secret�ĳ���(������������),���򷵻�0.
    ====================================================================*/
    u16 GetSecret(IN OUT u8* pOutBuf, IN u16 wBufLen)
    {
        u16 wLen = ntohs(m_wSecretLen);
        if((NULL == pOutBuf)||(wBufLen < wLen))
        {
            return 0;
        }        
        memcpy(pOutBuf,m_abySecret,wLen);
        return wLen;       
    }

    u16 GetSecretLen()
    {
        return ntohs(m_wSecretLen);
    }

}TRadiusSecret, *PTRadiusSecret;


//Radius������Ϣ 
typedef struct tagRadiusConfigInfo
{
private:        
    u32             m_dwServerIP;         //Radius������IP
    u32             m_dwTimeOutInterval;  //�ط����(����)    
    u16             m_wIsUseRadius;       //�Ƿ�ʹ��Radius��֤    
    u16             m_wAccessPort;        //��֤�˿ں�
    u16             m_wAccountPort;       //�ƷѶ˿ں�
    u16             m_wRetryNum;          //��ʱ�ط�����
    TRadiusSecret   m_tSecret;             //������Կ

public:
    tagRadiusConfigInfo()
    {
        m_wIsUseRadius = 0;
        m_dwServerIP = inet_addr("127.0.0.1");
        m_wAccessPort = htons(DEFAULT_ACCESS_PORT);
        m_wAccountPort = htons(DEFAULT_ACCT_PORT);
        m_wRetryNum = htons(DEFAULT_RETRY_TIME);
        m_dwTimeOutInterval = htonl(DEFAULT_TIMEOUT_INTERVAL);
        m_tSecret.SetSecret((u8*)DEFAULT_RADIUS_SECRET,strlen(DEFAULT_RADIUS_SECRET));
    }     
    
    void SetUseRadius(u16 wIsUseRadius)
    {
        m_wIsUseRadius = htons(wIsUseRadius);
    }

    u16 GetUseRadius()
    {
        return ntohs(m_wIsUseRadius);
    }      
    
    void SetServerIP(u32 dwServerIP)
    {
        m_dwServerIP = htonl(dwServerIP);
    }

    u32 GetServerIP()
    {
        return ntohl(m_dwServerIP);
    }

    void SetAccessPort(u16 wAccessPort)
    {
        m_wAccessPort = htons(wAccessPort);
    }

    u16 GetAccessPort()
    {
        return ntohs(m_wAccessPort);
    }      

    void SetAccountPort(u16 wAccountPort)
    {
        m_wAccountPort = htons(wAccountPort);
    }

    u16 GetAccountPort()
    {
        return ntohs(m_wAccountPort);
    }

    void SetRetryNum(u16 wRetryNum)
    {
        m_wRetryNum = htons(wRetryNum);
    }

    u16 GetRetryNum()
    {
        return ntohs(m_wRetryNum);
    }

    void SetRetryInterval(u32 dwRetryInterval)
    {
        m_dwTimeOutInterval = htonl(dwRetryInterval);
    }

    u32 GetRetryInterval()
    {
        return ntohl(m_dwTimeOutInterval);
    }      

    void SetSecret(u8* pSecrect, u16 wLen)
    {
        m_tSecret.SetSecret(pSecrect,wLen);
    }     
    
    u16 GetSecret(u8* pBuf, u16 wLen)
    {
        return m_tSecret.GetSecret(pBuf,wLen);
    }                      
}TRadiusConfigInfo, *PTRadiusConfigInfo;

//add by daiqing for pcmt gk permision
typedef struct tagPcmtAuthStatus
{
private:
	u32 m_dwTotalNum;
	u32 m_dwUsedNum;

public:
	tagPcmtAuthStatus()
	{
		m_dwTotalNum = 0;
		m_dwUsedNum = 0;
	}

	void SetPcmtAuthStatus( u32 dwTotalNum , u32 dwUsedNum )
	{
		m_dwTotalNum = htonl(dwTotalNum);
		m_dwUsedNum = htonl(dwUsedNum);
	}

	void GetPcmtAuthStatus( u32* dwTotalNum , u32* dwUsedNum )
	{
		*dwTotalNum = ntohl(m_dwTotalNum);
		*dwUsedNum = ntohl(m_dwUsedNum);
	}

}TPcmtAuthStatus;

//add by yj for support all kinds of mts [20120924]
typedef struct tagmtAuth
{
	s8  m_abyEndpointName[MAX_LEN_EPNAME+1];
	u32 m_dwTotalNum;
	u32 m_dwUsedNum;
	
	tagmtAuth()
	{
		clear();
	}

	void clear()
	{
		memset( m_abyEndpointName , 0 , sizeof(m_abyEndpointName) );
		m_dwTotalNum = 0;
		m_dwUsedNum = 0;
	}

	void SetMtsAuth( u32 dwTotalNum, u32 dwUsedNum, s8* EndpointName )
	{
		m_dwTotalNum = htonl(dwTotalNum);
		m_dwUsedNum = htonl(dwUsedNum);
		memcpy( m_abyEndpointName, EndpointName, strlen( EndpointName )+1 );
	}

	void GetMtsAuth( u32* dwTotalNum, u32* dwUsedNum, s8* EndpointName )
	{
		*dwTotalNum = ntohl(m_dwTotalNum);
		*dwUsedNum = ntohl(m_dwUsedNum);
		memcpy( EndpointName, m_abyEndpointName, strlen( m_abyEndpointName )+1 );
	}

}TMtAuth;
//end [20120924]

//add by yj [20120807]
//��ȡGK�豸�ͺż�MAC��ַ
typedef struct tagMACAndProductid
{
	s8		m_abymacaddress[18];			//MAC��ַ
	cmGKPruductID		m_dwProductId;	//��Ʒ��

	tagMACAndProductid()
	{
		memset(m_abymacaddress, 0, 18);
		m_dwProductId = cmGKPruduct_Unknown;
	}

	void SetProductId( cmGKPruductID  productid )
	{
		m_dwProductId = (cmGKPruductID)htonl( productid );
	}
	
	cmGKPruductID GetProductID()
	{
		return (cmGKPruductID)ntohl( m_dwProductId );
	}

}TMACAndProductid;
//end [20120807]

//
//////////////////////////////// �����ӿ� //////////////////////////////
API void setgklog(s32 nLevel);
//��־����
void KdvGKRASLog(s32 nLevel, s8 *pchFormat,...);

//ѹ������
inline BOOL EncodeAlias(IN TAliasAddr *ptAlias, IN u16 wAliasNum, 
                        OUT u8 *pbyOutBuf, OUT u32 *pdwBufLen)
{
    if ( ptAlias == NULL || pbyOutBuf == NULL || pdwBufLen == NULL )
        return FALSE;

    u8 *pbyPos = pbyOutBuf;
    u32 bufLen = 0;

    for( u16 wIndex = 0; wIndex < wAliasNum; wIndex++)
    {
        s8 aliasName[MAX_ALIASNAME_LEN+1] = {0};
        
        u32 dwAliasType = ptAlias[wIndex].GetAliasType();
        
        u16 wAliasNameLen = ptAlias[wIndex].GetAliasName( aliasName, MAX_ALIASNAME_LEN );
        u16 wAliasLen = wAliasNameLen + sizeof(cmAliasType);

        //�����ܳ�: �������ͣ���������
        u16 aliasLen = htons(wAliasLen);
        memcpy(pbyPos, &aliasLen, sizeof(u16));
        pbyPos += sizeof(u16);

        //��������
        u32 aliasType = htonl(dwAliasType);
        memcpy(pbyPos, &aliasType, sizeof(u32));
        pbyPos += sizeof(u32);
        
        //��������
        memcpy(pbyPos, aliasName, wAliasNameLen);
        pbyPos += wAliasNameLen;

        bufLen += sizeof(u16) + wAliasLen;
    }

    *pdwBufLen = bufLen;
    return TRUE;
}

//�ָ������ṹ
inline BOOL DecodeAlias(IN u8 *pbyAliasBuf, IN u16 wAliasNum, 
                        IN u32 dwAliasBufLen, OUT TAliasAddr atAlias[])
{
    if (pbyAliasBuf == NULL || atAlias == NULL)
        return FALSE;

    u8 *ptPos = (u8*)pbyAliasBuf;
    u32 dwTotalLen = 0;

    for(u16 wIndex = 0; wIndex < wAliasNum; wIndex++)
    {
        //�����ܳ�: �������ͣ���������
        //for Davinci alignment error
        u16 wTmp = 0;
        memcpy(&wTmp,ptPos,sizeof(u16));
        //u16 wAliasLen = ntohs(*(u16*)ptPos);
        u16 wAliasLen = ntohs(wTmp);
        ptPos += sizeof(u16);

        //��������
        u32 dwTmp = 0;
        memcpy(&dwTmp,ptPos,sizeof(u32));
        u32 aliasType = ntohl(dwTmp);
        //u32 aliasType = ntohl(*(u32*)ptPos);
        ptPos += sizeof(u32);

        //��������
        u16 wAliasnameLen = wAliasLen - sizeof(cmAliasType);
                    
        atAlias[wIndex].SetAliasType((cmAliasType)aliasType);
        atAlias[wIndex].SetAliasName((s8*)ptPos, wAliasnameLen);

        ptPos += wAliasnameLen;

        dwTotalLen += sizeof(u16) + wAliasLen;
    }

    if ( dwTotalLen != dwAliasBufLen )
        return FALSE;

    return TRUE;
}

s32 MainStartGk( s8* pszGkFile);


#endif //__KDVGK_H
