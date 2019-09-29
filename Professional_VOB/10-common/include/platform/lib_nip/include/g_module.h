/* all function macro define for NIP modules */
#ifndef _G_MODULE_H_
#define _G_MODULE_H_

/* --------------- zzm add start ------------------------ */
/* note: INCLUDE_REDUCE should be define in CFLAGS */
#ifndef INCLUDE_REDUCE
#define INCLUDE_TELNETC
#define INCLUDE_TELNETS
#define INCLUDE_WEBS
#define INCLUDE_DDNSC
#define INCLUDE_DNSS
#define INCLUDE_SNTP
#define INCLUDE_PING
#define INCLUDE_TRACERT
#define INCLUDE_ZLOG
#define INCLUDE_QOS
#define INCLUDE_ZDBG
#define INCLUDE_ACL	1
#define INCLUDE_FTP
#define INCLUDE_NAT
#define INCLUDE_ZSNMP
//#define INCLUDE_TELSH 1
#define INCLUDE_TFTPC
#define INCLUDE_DHCPC 1
#define INCLUDE_MEMORY 1
#else
#define INCLUDE_WEBS
#define INCLUDE_DDNSC
#endif

#ifdef INCLUDE_TFTPC
#define MOD_TFTP_CLIENT
#endif 
#ifdef INCLUDE_TELNETC
#define MOD_TELNETC_VER_1
#endif

#ifdef INCLUDE_TELNETS
#define MOD_TELNETS_VER_1
#define MOD_TELNET_SHELL_VER_1
#endif

#ifdef INCLUDE_WEBS
/* ------------------- zyp add start --------------------------- */
#define MOD_WEBSERVER_VER_0
/*  ʱ�䣺2005-09-05 18:21
    ���ܣ�ΪNIP�ṩWeb Server ֧��
*/
#define MOD_WEBSERVER_VER_0_1
/*  ʱ�䣺2006-03-30 8:55
    ���ܣ�ΪWeb Server�ṩ�Զ���⹦��
*/
#endif

#ifdef INCLUDE_DDNSC
#define MOD_DDNSC_VER_0
/* yumilin added 2005-8-30
 *  DDNS CLIENT
 */
#endif

#ifdef INCLUDE_DNSS
#define MOD_DNSS_VER_0
/* yumilin added 2005-9-21
 *  DNS SERVER
 */
#endif

#ifdef INCLUDE_SNTP
#ifdef INCLUDE_ACL
/*-------------------- leyi add start ---------------------------*/
#define MOD_SNTP_VER_0
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  ʱ�䣺2005-10-8 10:21
  ���ܣ�SNTP����
*/
#define MOD_SNTP_VER_1
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  ʱ�䣺2005-12-02
  ���ܣ���������ϵͳʱ�书�ܡ��޸�BUG1452
*/
/*-------------------- leyi add end -----------------------------*/
#endif
#endif

#ifdef INCLUDE_PING
#define MOD_PING_VER_0
/*  ʱ�䣺2005-1-28 12:04
    ���ܣ�PING ģ���״κ���汾
*/
#endif

#ifdef INCLUDE_TRACERT
#define MOD_TRACERT_VER_0
/*  ʱ�䣺2005-7-26 12:04
    ���ܣ�traceroute ģ���״κ���汾
*/
#endif

#ifdef INCLUDE_ZLOG
#define MOD_ZLOG_VER_0
/*  ʱ�䣺2005-10-09 18:21
    ���ܣ�ΪNIP�ṩzlog ���� ֧��
*/
#define MOD_ZLOG_VER_KERNEL
/*  ʱ�䣺2005-10-28 18:21
    ���ܣ�Ϊ�ں��ṩzlog ������ܵ� ֧��
*/
#endif

#define MOD_CONSOLE_VER_1

#ifdef INCLUDE_QOS
#ifdef INCLUDE_ACL
#define MOD_QOS_VER_1
/* Yuanyi Zhang added 2005-7-5 09:52
   QoS
*/
#endif
#endif

#ifdef INCLUDE_ZDBG
#define MOD_ZDBG_VER_1
#define MOD_IPDBG_VER_1
/* Yuanyi Zhang added 2006-4-3 15:15
   IP Packet Debugging
*/
#endif

/* ------------------- zhangyuanyi end ---------------------------------- */

#define MOD_USER_PASS_VER_0
/*  ʱ�䣺2005-1-28 12:04
    ���ܣ�username ��һ�κ���汾
*/

#define MOD_USER_PASS_VER_1
/*  ʱ�䣺2005-1-28 12:04
    ���ܣ��޸�bug

    ʱ�䣺2005-5-28 12:04
    ���ܣ����ӿ���̽ӿں���
*/

/* ------------------- zzm add start ------------------------- */
/* NIP get notifies from Linux kenrel via netlink thread */
#define NIP_READ_KERNEL 1

#if 0
#define NIP_TELSH	1
/*
  at: 		2005-09-05 09:40
  describe:	add telnet to shell function,
  	guys can use "telnet shell port ? interface * enable" to enable this
*/
#endif

#define SHELL_NIP_SWITCH	1
#define SHELL_NIP_SWITCH_0  1
/* at:		2005-9-13 15:32
    describe:	add nip shell switch function,
    	everyone can use "shell" in nip back to shell, and "exit" in shell to nip
*/

/* ------------------- zzm add end --------------------------- */

/* ----------------SHELL_NIP_SWITCH_0-----------------------
   at:		2006-2-16 10:32
    describe:	1.����һ��ϵͳ������Զ�����shell������
                     2.����һ��API�ӿں���(ϵͳ������Զ�����shell)
*/

/* ------------------- fxp add end --------------------------- */


#define ZEBRA_MULTITHREAD   1
/*  ʱ�䣺2005-1-28 12:04
    ���ܣ�zebra ���߳�
*/

#define ZEBRA_MULTITHREAD_V1   1
/*  ʱ�䣺2005-1-28 12:04
    ���ܣ�zebra ���̰߳汾1
*/

#define ZEBRA_TIMER_V0	    1
/*  ʱ�䣺2005-1-28 12:04
    ���ܣ�zebra ��ʱ��
*/

#define ZEBRA_FIX_VER1      1
/*  ʱ�䣺2005-1-28 12:04
    ���ܣ�telnet bug ��\r' ��'\n'�����ظ�����
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ʱ�䣺2005-1-28 12:04
    ���ܣ��źų�ʼ��������ĳЩ�ж��ź�
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#define MOD_CON_VER_1	 1
/*  ʱ�䣺2005-7-15 12:04
    ���ܣ�reboot��ʱ,���������Ϣ���޸ģ�������
    ������Ϣ��ʾ��

*/

#ifdef MOD_CON_VER_1
#define MOD_CON_VER_1_1	 1
/*  ʱ�䣺2005-11-22 12:04
    ���ܣ�ʹ�����ļ��Ĺ�����
    (erase/write/read/show running/show cfgfiles/show content)��vxworks����һ��

*/
#endif

#define MOD_ZSERV_VER_0	    1
/*  ʱ�䣺2005-1-28 12:04
    ���ܣ�zserv ֧�ֶ��߳�
*/

/* -------------------- zhangyan add start ----------------------- */
/* 	Linux-2.4.24 & Linux-2.6.10 difference
	undefine LINUX_2_6_10 for linux-2.4.24
*/
#define LINUX_2_6_10	1	// for linux-2.6.10
/* for ethernet speed duplex and mac address function */
#define ETHERNET_FUNCTION	1
#define ETH_ADD_FGETH	1

/* -------------------- zhangyan add end ----------------------- */




/* ------------------- linzhe add start ------------------------- */

#ifdef INCLUDE_FTP
#define MOD_FTP_SERVER_VER_0 1
/*	linzhe added 2005-2-28
	ftp server
*/

#define MOD_FTP_SERVER_VER_0_1 1
/*	linzhe added 2005-6-23
	add show debug timeout and erase functions
	add total info when list file
*/

#define MOD_FTP_SERVER_VER_1 1
/*	linzhe added 2005-9-22
       change ftp-server to thread mode
*/

#define MOD_FTP_SERVER_VER_1_1 1
/*	Jinfeng added 2006-7-26
       change ftp-server to multi-thread mode and insert memory lib 
*/

#endif

#ifdef INCLUDE_DHCPC
#define MOD_DHCPC_VER_0 1
/*	linzhe added 2005-4-13
	DHCP client
*/
#define MOD_DHCPC_VER_0_1 1
/*	linzhe added 2005-4-13
	some bug-fixes
*/
#define MOD_DHCPC_VER_1 1
/*	linzhe added 2005-10-10
	change to thread mode
*/

#define MOD_DHCPC_VER_2       1
/*	zhanka added 2006-08-08
	Mod pipe synchronization problem
*/

#endif

#ifdef INCLUDE_ACL
#define MOD_ACL_VER_0 1
/*	linzhe added 2005-6-29
	Access-list
*/
#define MOD_ACL_VER_0_1 1
/*	linzhe added 2005-9-21
	some bug-fixes
*/
#define MOD_ACL_VER_0_2 1
#define MOD_ACL_VER_0_3 1

#ifdef INCLUDE_NAT
#define MOD_NAT_VER_0 1
/*	linzhe added 2005-11-21
	Network Address Translation(NAT)
*/
#endif
#endif
/* ------------------- linzhe add end ------------------------- */



/* ------------------- fxp add start ------------------------- */

/* add  range_multi,mac address node type,and add a vty_advanced_read function*/
#define NIP_CTN_VER_0  1
#define NIP_CTN_VER_1  1 /*add inside node   zpj*/
#define NIP_CTN_VER_2  1
#define NIP_CTN_VER_3  1 /*add can be changed node  zyp*/
#define NIP_CTN_VER_4  1
#define NIP_CTN_VER_5  1

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   NIP_CTN_VER_0
   ʱ�䣺 2005-3-31 8:56
   ���ܣ�  1������range_multi,ac address node type
           2. ����vty_advanced_read ����
 					 3. �޸�ipv4 ,range node type

   ʱ�䣺 2005-4-04 10:25
   ���ܣ� 1. ��vty_advanced_read �����õ��û�����ĳ�������
   			���ܴ��ڣ����������ƣ�����ʹ����������Ŀ���
   			��Ա��֪��������ٸ��ռ�Ͳ��������ڴ����


  ~~~~~~~~~~~~NIP_CTN_VER_2~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  ʱ�䣺2005-12-02
  ���ܣ����Ӷ����ѡ�ڵ�֧��(a b | c d e)

 ~~~~~~~~~~~~NIP_CTN_VER_4~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  ʱ�䣺2005-12-02
  ���ܣ����������е���Ӣ��֧�ּ���ӡ��������Ӣ��֧��

*/

#define MOD_ARP_VER_0                 /* arp v0 zhangyuanyi */
/*  ʱ�䣺2005-06-01 17:21
    ���ܣ�ΪNIP�ṩARP֧��
*/

/* ------------------- zhzs add start ------------------------- */

#define MOD_INTF_BUG_1	1
/* MOD_INTF_BUG_1, zhzs, added 2005-7-2
 *   Not need to up the interface to set IP address.
 */
#define MOD_INTF_ADD_FE_GE_NODE 1
/* MOD_INTF_ADD_FE_GE_NODE, zhzs, added 2006-1-17
 * Add fastEthernet and gigabitEthernet node type.
 */
 
#define MOD_SNMP_VER_0  1
//#define MOD_SNMP_VER_0_1 1
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  ʱ�䣺2005-07-07 10:21
    ���ܣ�ΪNIP�ṩsnmp֧��
    ~~~~~~~~~~~MOD_SNMP_VER_0_1~~~~~~~~~~~~~~~~~~~~
    ʱ��2005-9-20 8�?8
    ����ʹSNMP�ṩȫ�߳�֧��

*/


/* ------------------- zhzs add end --------------------------- */

#ifdef INCLUDE_MEMORY
/* MOD_MEMORY_LIB, liangyulin added 2005-9-2 to enable memory lib */
#define MOD_MEMORY_LIB 1
/* -------------------liangyulin add end -----------------------*/
#endif 

/* ------------------- zhuzhm add start ------------------------- */

#ifndef INCLUDE_REDUCE
#define INCLUDE_RIP 1
#endif
#define INCLUDE_IGMP_HOST 1

/* RIP */
#ifdef INCLUDE_RIP
#define MOD_RIP 1
#define RIP_IF_APP 1
#define RIP_RECVMSG 1
#define RIP_IF_V35 1
#endif

/* serial loopback */
#define ZHUZHM_SERIAL_LOOPBACK 1
/* loopback */
#define ZHUZHM_CFG_LOOPBACK 1
/* rib */
#define ZHUZHM_STATIC_ROUTE_NUM_LIMIT 1
#define ZHUZHM_DEL_KERNEL_ROUTE 1
#define ZHUZHM_ADD_RIB_TABLE_LOCK 1
#define ZHUZHM_ADD_RIB_NODE_LOCK 1
#define ZHUZHM_DEFAULT_ROUTE_AND_GATEWAY 1
/* igmp host */
#ifdef INCLUDE_IGMP_HOST
#define MOD_IGMP_HOST_VER_0 1
#endif
/* multicast */
#define ZHUZHM_MULTICAST_CHANGE 1
/* load-sharing */
#define ZHUZHM_MULTIPATH_SELECT 1

/* ------------------- zhuzhm add end --------------------------- */

#define MOD_PPP_MULTITHREAD 1

/*--------------------zhengpeijun add start------------------------*/

#define MOD_DHCPC_VER_1_1 1
/*zhengpeijun add 2005 10 18
 */

/*--------------------zhengpeijun add end------------------------*/

/* MOD MP */
/*-------------------- xuyiping add end -----------------------------*/

#define MOD_NIP_API_COMM
/* Yuanyi Zhang added 2005-12-09 10:06
   NIP API communicate library.
*/

//#endif
#define HAVE_MULTILINK 1
#define ZHZS_ADD_VIRTUAL_INTF_MP 1
#define HAVE_MULTILINK_ZHZS    1

#define NEW_MP_1 	1
#define MP_MODEL_NEW 	1
#define MOD_MP_VER_1	1		/*WJ FOR multilink api 05-12-14*/
//#define MP_DEBUG_FLAG_ 1
/*-------------------- xuyping add end -----------------------------*/
#define peer_default /*���öԶ�ip add ��������*/
#define WJ_DEBUG_TERMINAL
#define MOD_PPP_VER_1	1/*PPP_SEPARATE_VTY ; ����������vty���롣WJ 1207*/
#define MOD_PPP_VER_1_1	1/*�������������������ֵ�Ķ���Ϊ��ֵ���롣
			WJ 1212��lcp_interval,lcp_maxretry,l*/
#define MOD_PPP_VER_2	1	/*wj use zipc in PPP*/
#define MOD_PPP_VER_3	1	/*����pppģ���ʼ������*/
#define MOD_PPP_VER_4	1	/*�޸�pppģ������Ӧblackfin*/
#define MOD_PPP_VER_5	1	/*pppģ�������ڴ��*/
#define MOD_PPP_VER_6	1	/*�޸�pppģ���ڴ�û���ͷ�*/
#define NIP_API_V35	1
#define NIP_API_PPP	1
#define WJ_DELE_WARNING_1	1/*ȥ��PPP��PPPOE��MP�б��뾯��*/
#define NIP_API_BANDWIDTH 1
/*-------------------- wanjiang add end 2005-11-28-----------------------------*/
#define MOD_DEBUG_PPP 1
#define MOD_MP_PEERIP  1
#define MOD_MP_DEBUG_EVENT 1

#define ZHZS_NETDEVICE_BANDWIDTH_NEW 1

/*------------------------------zhanka add start----------------------------------*/
#ifndef INCLUDE_REDUCE
#define INCLUDE_HDLC
#define INCLUDE_SUB_VLAN
#endif 

#define CONTROLLER_DELETE_VTY                              /* For controller_add_serial_and_return_e1 delete vty */
#define PPP_AND_PPPOE_MEM_ZHANKA                           /* For ppp and pppoE  */

#ifdef INCLUDE_HDLC
#define HDLC_ZHANKA_INIT
#endif 

#ifdef INCLUDE_SUB_VLAN
#define SUB_VLAN_ZHANKA
#define KDC_SUB_VLAN_MOD                                   /* For kernel */ 
//#define SUB_VLAN_ZHANKA_BWD                           /* fix bandwitch for vlan tmp */
#define SUB_VLAN_VER_2                  1
#endif   

#define V35_PPPoE_ZHANKA                                   /* like changed node (serial <0-15>|serial <16-63> */
#define ETH_FETH_ZHANKA                                    /* slove for (fastethernet <0-1>) */

#define BLACK_FIN_TMP

#define DHCPC_GETIP_RMVIP_ONE      1

#define HTTP_RESTART_INSPECT_BUG 1           
#define DHCPC_GATEWAY_CALLBACK     1                /* give callback geteway */

#define MOD_DHCPC_API_ENABLE 1
/*   zhanka mod dhcpc api enable
      default don't set gateway , just give 
      app the gateway.
*/
/* -------------------- luchen add start ----------------------- */

/* For e1 config delete vty */
#define INTERFACE_E1_DELETE_VTY		1
#define MOD_V35_VER_1				1
/* For switch device: IS2 */
#define INCLUDE_SWITCH_FUNC		1

/* -------------------- luchen add end ----------------------- */
#define MOD_NETLINK_OVERRUN			1

#ifndef INCLUDE_REDUCE
#define INCLUDE_MP	1
#endif

#define NO_MAC_CFG_ZHUZHM   /* 1026 : temp, delete in one month */

#endif
