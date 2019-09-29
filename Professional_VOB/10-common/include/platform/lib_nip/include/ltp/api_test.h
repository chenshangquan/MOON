/*=======================================================================
ģ����      : API����
�ļ���      : 
����ļ�    : 
�ļ�ʵ�ֹ���: 
����        : Jin Feng
�汾        : LTP Release 1.0
-------------------------------------------------------------------------
�޸ļ�¼:
��  ��				�汾		�޸���					�޸�����
2006/03/03			1.0			Jin Feng					����
=======================================================================*/

#ifndef _API_TEST_H_
#define _API_TEST_H_

#ifndef __NIP_API_H
#include "api/nip_api.h"
#endif

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

#ifndef MAXAPILEN 
#define MAXAPILEN 256
#endif

#define NULL_STR "*"			// �����ԵĲ����У����ַ�����ʱ�����Ϊ��*�������ַ���ָ�븳ΪNULL

/*------------------------------------*/

struct api_mac_02_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ifname[MAXAPILEN];
    char macaddr[MAXAPILEN];
    /* Ԥ�ڽ�� */
   int  val;
   int  rtn;
};

/*------------------------------------*/

struct api_mac_04_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ifname[MAXAPILEN];
    char macaddr[MAXAPILEN];
    int  opcode;

    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ftp_01_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    int  enable;

    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_general_01_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    int  len;

    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_general_02_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
 	int  service_type;
    char pstr_user[MAXAPILEN];
    char pstr_pass[MAXAPILEN];
    int  opcode;

    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_general_03_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    int  id;
    char pstr_user[MAXAPILEN];
    char pstr_pass[MAXAPILEN];
    int  opcode;

    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_general_04_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char pathname[MAXAPILEN];

    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_general_05_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    int opcode;

    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_general_06_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    int opcode;

    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_interface_01_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
  	char ifname[MAXAPILEN];
    int  ifunit;
    char ip_addr[MAXAPILEN];
    char ip_mask[MAXAPILEN];

    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_interface_02_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
	char ifname[MAXAPILEN];
    int  ifunit;
    char ip_addr[MAXAPILEN];
    char ip_mask[MAXAPILEN]; 	

    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_interface_03_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
	char ifname[MAXAPILEN];
    char ip_addr[MAXAPILEN];
    char ip_mask[MAXAPILEN]; 
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_interface_04_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
	char ifname[MAXAPILEN];
    int  num;
    char ip_addr[MAXAPILEN];
    char ip_mask[MAXAPILEN]; 
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_interface_05_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ifname[MAXAPILEN];  
    int  ifunit;  
    char ip_addr[MAXAPILEN];
    char ip_mask[MAXAPILEN];
    int  opcode;  	
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_interface_06_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
	char ifname[MAXAPILEN];
    char ip_addr[MAXAPILEN];
    char ip_mask[MAXAPILEN]; 	
    int  opcode;
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_interface_07_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
	char ifname[MAXAPILEN];
    char ip_addr[MAXAPILEN];
    char ip_mask[MAXAPILEN];
    int  opcode;
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_interface_08_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
	   char ifname[MAXAPILEN];
       char ip_addr[MAXAPILEN];
       char ip_mask[MAXAPILEN];
	   int opcode; 
	   int status;
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_interface_09_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ifname[MAXAPILEN];
    int  ifunit;
    char ip_addr[MAXAPILEN];
    char ip_mask[MAXAPILEN];	
    int  opcode;	
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_interface_10_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
	char ifname[MAXAPILEN];
    char ip_addr[MAXAPILEN];
    char ip_mask[MAXAPILEN];	
    int  opcode;	
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_lib_01_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
	char ifname[MAXAPILEN];

    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_mp_01_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
	char  usrname[MAXAPILEN];
    int   virnum;
    int   opcode;	

    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_mp_02_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
	char ifname[MAXAPILEN];
    int  ifunit;			
    char max_frags[MAXAPILEN];		// auto or <%d>
	int  handle_type;			

    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_mp_03_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
	 char ifname[MAXAPILEN];
     int  ifunit;
     int  min_pktlen;
	 int  handle_type;	

    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_mp_04_t
{
    /* Ԥ������ */      
    int setup_env; 
    /* �������� */
       int   virnum;                // virtual interface number
       char  mluser[MAXAPILEN];     // usernames binded with the virtual interface
       int   num;                   // number of  users
       int   opcode;
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_mp_05_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
	char ifname[MAXAPILEN];
    int  ifunit;            // intface number
	int  loopback;	        // loop back state

    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_mp_06_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
	char ifname[MAXAPILEN];
   	int  ifunit;	
   	char max_frags[MAXAPILEN];
	int  handle_type;
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_mp_07_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
	char ifname[MAXAPILEN];
    int  ifunit;
    int  min_pktlen;

    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ping_01_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char Host[MAXAPILEN];		        // host to ping 
    int opt_packetsize;    // 
    int opt_timeout;
    int opt_ttl;
    int dwOptions;           // ��־λ
    int echoid;            // user data informationЯ�����û�����
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_01_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ifname[MAXAPILEN];
    int  ifunit; 		    
    unsigned long  echo_interval;  
    int handle_type;
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_02_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ifname[MAXAPILEN];         // name of interface
    int  ifunit;                    // intface number 
    char pppauth_type[MAXAPILEN];   // authentication type
    int handle_type;	
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_03_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ifname[MAXAPILEN];       // name of interface        
    int  ifunit;                 // intface number           
    char username[MAXAPILEN];     // pap username             
    char password[MAXAPILEN];     // password of pap user     
    int  handle_type;            // add��delete  type   
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_04_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ifname[MAXAPILEN];         // name of interface
    int  ifunit;                    // intface number 
    char chap_hostname[MAXAPILEN];	// chap hostname
    int  handle_type;            // add��delete  type  
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_05_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char  ifname[MAXAPILEN];           // name of interface
    int   ifunit;                       // intface number 
    char  chap_password[MAXAPILEN];    // chap hostname
    int   handle_type;		            // add��delete  type
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_06_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ifname[MAXAPILEN];    // name of interface
    int  ifunit;                  // intface number 
    char peer_addr[MAXAPILEN];  // default ip addr of the peer 
    int  handle_type;             // add��delete  type

    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_07_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ifname[MAXAPILEN];
    int  ifunit; 		    
    unsigned long  lcp_interval;
    int handle_type;

    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_08_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ifname[MAXAPILEN];
    int  ifunit; 		    
    unsigned long  lcp_maxretry;
    int handle_type;

    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_09_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ifname[MAXAPILEN];
    int  ifunit; 		    
    unsigned long  lcp_maxwait;
    int handle_type;
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_10_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ifname[MAXAPILEN];
    int  ifunit; 		    
    int  multi_flag;
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_11_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ifname[MAXAPILEN];
    int  ifunit; 		    
    char proto[MAXAPILEN];      // protocol
    int handle_type;
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_12_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char  ifname[MAXAPILEN];  // name of interface 	
    int   ifunit; 	          // intface number 
    unsigned long   bandwidth;	      // bandwidth 1-10000000
    int  optcode;
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_13_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ifname[MAXAPILEN];
    int  ifunit;      // intface number 	
    char mode[MAXAPILEN];
    int  handle_type;	// add��delete  type
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_14_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ifname[MAXAPILEN];
    int  ifunit; 		    
    unsigned long  echo_interval;
    int handle_type;
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_15_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ifname[MAXAPILEN];        
    int  ifunit;      
    char pppauth_type[MAXAPILEN];
    int  handle_type;
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};


/*------------------------------------*/

struct api_ppp_16_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char  ifname[MAXAPILEN];       // name of interface        
    int   ifunit;                 // intface number           
    char  username[MAXAPILEN];     // pap username             
    char  password[MAXAPILEN];     // password of pap user     
    int   handle_type;            // add��delete  type     
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_17_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char  ifname[MAXAPILEN];           // name of interface
    int   ifunit;                       // intface number 
    char  chap_hostname[MAXAPILEN];    // chap hostname
    int   handle_type;		            // add��delete  type
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_18_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char  ifname[MAXAPILEN];           // name of interface
    int   ifunit;                       // intface number 
    char  chap_password[MAXAPILEN];    // chap hostname
    int   handle_type;		            // add��delete  type
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_19_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ifname[MAXAPILEN];       // name of interface        
    int  ifunit;                 // intface number           
    char username[MAXAPILEN];     // pap username             
    char password[MAXAPILEN];     // password of pap user     
    int  handle_type;            // add��delete  type    
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};


/*------------------------------------*/

struct api_ppp_20_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ifname[MAXAPILEN];    // name of interface
    int  ifunit;                  // intface number 
    char peer_addr[MAXAPILEN];  // default ip addr of the peer 
    int  handle_type;             // add��delete  type
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_21_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ifname[MAXAPILEN];       // name of interface 
    int  ifunit;        // intface number
    unsigned long lcp_interval;  // interval of  lcp configure-request
    int	 handle_type;		    // add��delete  type
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_22_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ifname[MAXAPILEN];
    int  ifunit; 		    
    unsigned long lcp_maxretry;
    int handle_type;
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_23_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ifname[MAXAPILEN];
    int  ifunit; 		    
    unsigned long lcp_maxwait;
    int handle_type;
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_24_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ifname[MAXAPILEN];
    int  ifunit; 		    
    int  handle_type;
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_25_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ifname[MAXAPILEN];
    int  ifunit; 		    
    char proto[MAXAPILEN];      // protocol
    int  optcode;
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_26_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char  ifname[MAXAPILEN]; // name of interface 	
    int   ifunit; 	        // intface number 
    unsigned long   bandwidth;	    // bandwidth 1-10000000
    int   optcode;
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_27_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ifname[MAXAPILEN];
    int  ifunit;      // intface number 	
    char mode[MAXAPILEN];
    int  handle_type;	// add��delete  type
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_28_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char  ifname[MAXAPILEN]; // name of interface 	
    int   ifunit; 	        // intface number 
    unsigned long   echo_maxretry;	    // echo_maxretry 1-256
    int   handle_type;
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_29_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char  ifname[MAXAPILEN]; // name of interface 	
    int   ifunit; 	        // intface number 
    unsigned long   echo_maxretry;	    // echo_maxretry 1-256
    int   handle_type;
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_30_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char  ifname[MAXAPILEN]; // name of interface 	
    int   ifunit; 	        // intface number 
    unsigned long echo_paddinglen;	    // bandwidth 1-10000000
    int  handle_type;
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_31_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char  ifname[MAXAPILEN]; // name of interface 	
    int   ifunit; 	        // intface number 
    unsigned long echo_paddinglen;	    // bandwidth 1-10000000
    int  handle_type;
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_32_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char  ifname[MAXAPILEN]; // name of interface 	
    int   ifunit; 	        // intface number 
    unsigned long ipcp_interval;	    // ipcp_interval 1-30
    int  handle_type;
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_33_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char  ifname[MAXAPILEN]; // name of interface 	
    int   ifunit; 	        // intface number 
    unsigned long ipcp_interval;	    // ipcp_interval 1-30
    int  handle_type;
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_34_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char  ifname[MAXAPILEN]; // name of interface 	
    int   ifunit; 	        // intface number 
    unsigned long ipcp_maxretry;    // max configure-request retransmissions
    int  handle_type;
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_35_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char  ifname[MAXAPILEN]; // name of interface 	
    int   ifunit; 	        // intface number 
    unsigned long ipcp_maxretry;    // max configure-request retransmissions
    int  handle_type;
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_36_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char  ifname[MAXAPILEN]; // name of interface 	
    int   virtual; 	        // intface number 
    int  handle_type;
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};


/*------------------------------------*/

struct api_ppp_37_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char  ifname[MAXAPILEN]; // name of interface 	
    int   vir_unit; 	        // intface number 
    int  handle_type;
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_38_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */

    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_39_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */

    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_40_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ifname[MAXAPILEN]; // name of interface 	
    int  ifunit; 	        // intface number 
    int  handle_type; 
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_41_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ifname[MAXAPILEN]; // name of interface 	
    int  ifunit; 	        // intface number 
    int  defaultroute;
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_42_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ifname[MAXAPILEN]; // name of interface 	
    int  ifunit; 	        // intface number 
    int  handle_type; 
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_43_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ifname[MAXAPILEN]; // name of interface 	
    int  ifunit; 	        // intface number 
    int  shutdown;
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_44_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
       char ifname[MAXAPILEN]; // name of interface 	
       int  ifunit; 	        // intface number 
       int  virtual_unit; 	        // intface number 

    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_45_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ifname[MAXAPILEN]; // name of interface 	
    int  ifunit; 	        // intface number 
    int  virtual_unit; 	        // intface number 
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_46_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    int  virtual_unit;
    char ethname[MAXAPILEN];
    char eth_ip_addr[MAXAPILEN];
    char eth_ip_mask[MAXAPILEN];
    char username[MAXAPILEN];
    char password[MAXAPILEN];
    int  enable_defaultroute;
    int  echo_interval;  // 1-30
    int  echo_retry;     // 1-256
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_47_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char pppoe_ver[MAXAPILEN];
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_48_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    int vunit;
    char pppoe_state[512];
    int handle;
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

struct api_ppp_49_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */		
    int test_func;
    /* Ԥ�ڽ�� */		
    int val;
    int rtn;
};
/*------------------------------------*/

struct api_route_01_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
 	char ip_net[MAXAPILEN]; 		        // ��̬·��ǰ׺
	char ip_mask[MAXAPILEN]; 		        // ��̬·���������� 
	char intfName_or_address[MAXAPILEN];    // ��һ��,�����һ��ΪĿ�ĵص�ַ,���ߵ�unit����������ΪNULL
	char if_unit[MAXAPILEN]; 		            // ��һ���ӿڵĵ�Ԫ�� 
	int  pri;                               // ��·�ɵ����ȼ�,���û������,�������Ϊ0
	int  dsize;
	int  opcode;			                // add��delete  type
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_route_02_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    int   num;
    char  dest_str[MAXAPILEN];    // Ŀ��·��
    char  mask_str[MAXAPILEN];    // ·�ɵ���������
    char  gate_str[MAXAPILEN];    // ·�ɵ�����
    int   distance;             // ·�����ȼ�
    int   opcode;                 // add��delete  type
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_route_03_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
 	char ip_net[MAXAPILEN]; 		        // ��̬·��ǰ׺
	char ip_mask[MAXAPILEN]; 		        // ��̬·���������� 
	char intfName_or_address[MAXAPILEN];    // ��һ��,�����һ��ΪĿ�ĵص�ַ,���ߵ�unit����������ΪNULL
	char unit[MAXAPILEN]; 		            // ��һ���ӿڵĵ�Ԫ�� 
	int  pri;                               // ��·�ɵ����ȼ�,���û������,�������Ϊ0
	int  opcode;			                // add��delete  type
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_route_04_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    int   num;
    char  dest_str[MAXAPILEN];    // Ŀ��·��
    char  mask_str[MAXAPILEN];    // ·�ɵ���������
    char  gate_str[MAXAPILEN];    // ·�ɵ�����
    int   distance;              // ·�����ȼ�
    int   opcode;                 // add��delete  type
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_route_05_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char  dest_str[MAXAPILEN];    // Ŀ��·��
    char  mask_str[MAXAPILEN];    // ·�ɵ���������
    char  gate_str[MAXAPILEN];    // ·�ɵ�����
    int   distance;              // ·�����ȼ�
    int   num;
    int   opcode;                 // add��delete  type
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_route_06_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char  dest_str[MAXAPILEN];    // Ŀ��·��
    char  mask_str[MAXAPILEN];    // ·�ɵ���������
    char  gate_str[MAXAPILEN];    // ·�ɵ�����
    int   distance;              // ·�����ȼ�
    int   num;
    int   opcode;                 // add��delete  type
    /* Ԥ�ڽ�� */
    int val;
    int rtn;
};


/*------------------------------------*/

struct api_vc_ioctl_01_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    int   cmd;
    char  dest_str[MAXAPILEN];    // Ŀ��·��         
    char  mask_str[MAXAPILEN];    // ·�ɵ���������   
    char  gate_str[MAXAPILEN];    // ·�ɵ�����       
    int   distance;              // ·�����ȼ�        
    int   opcode;                 // add��delete  type

	/* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_webserver_01_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    int   opcode;                 // add��delete  type	
	
	/* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_webserver_02_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char path[MAXAPILEN];                // add��delete  type
	
	/* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_driver_01_t
{
    /* Ԥ������ */      
    int setup_env;
    /* �������� */
    char ifname[MAXAPILEN]; 
    int  e1;
    int  channel;
    char timeslot[MAXAPILEN]; 
    int  serial;
    int  cmd;	
	/* Ԥ�ڽ�� */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_driver_02_t
{
    /* Ԥ������ */      
    int  setup_env;
    /* �������� */
    char ifname[MAXAPILEN]; 
    int  e1;
    int  cmd;
	/* Ԥ�ڽ�� */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct api_driver_03_t
{
    /* Ԥ������ */      
    int  setup_env;
    /* �������� */
    /* �������� */
    char ifname[MAXAPILEN];
    int  e1;
    char mode[MAXAPILEN];
    int  serial;
    int  cmd;
	/* Ԥ�ڽ�� */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct api_driver_04_t
{
    /* Ԥ������ */      
    int  setup_env;
    /* �������� */
    /* �������� */
    char ifname[MAXAPILEN];
    int  e1;
    char frame[MAXAPILEN];
    int  cmd;
	/* Ԥ�ڽ�� */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct api_driver_05_t
{
    /* Ԥ������ */      
    int  setup_env;
    /* �������� */
    /* �������� */
    char ifname[MAXAPILEN];
    int  e1;
    char loop[MAXAPILEN];
    int  cmd;
	/* Ԥ�ڽ�� */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct api_driver_06_t
{
    /* Ԥ������ */      
    int  setup_env;
    /* �������� */
    /* �������� */
    char  ifname[MAXAPILEN];
    int   e1;
    char  clock[MAXAPILEN];
    int   cmd;
	/* Ԥ�ڽ�� */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct api_driver_07_t
{
    /* Ԥ������ */      
    int  setup_env;
    /* �������� */
    /* �������� */
    char ifname[MAXAPILEN]; 
    int  e1;
    int  channel;
    char timeslot[MAXAPILEN]; 
    int  serial;
    char cfg_str[MAXAPILEN]; 
    int  cmd;   
	/* Ԥ�ڽ�� */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct api_driver_08_t
{
    /* Ԥ������ */      
    int  setup_env;
    /* �������� */
    char ifname[MAXAPILEN];
    int  e1;
    char mode[MAXAPILEN];
    int  serial;
    int  cmd; 
	/* Ԥ�ڽ�� */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct api_driver_09_t
{
    /* Ԥ������ */      
    int  setup_env;
    /* �������� */
    char ifname[MAXAPILEN];
    int  e1;
    char frame[MAXAPILEN];
    int  cmd;
	/* Ԥ�ڽ�� */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct api_driver_10_t
{
    /* Ԥ������ */      
    int  setup_env;
    /* �������� */
    char ifname[MAXAPILEN];
    int  e1;
    char clock[MAXAPILEN];
    int  cmd;
	/* Ԥ�ڽ�� */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct api_driver_11_t
{
    /* Ԥ������ */      
    int  setup_env;
    /* �������� */
    char ifname[MAXAPILEN];
    int  e1;
    char loop[MAXAPILEN];
    int  cmd;
	/* Ԥ�ڽ�� */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct api_driver_14_t
{
    /* Ԥ������ */      
    int  setup_env;
    /* �������� */
    char  para[MAXAPILEN];
	/* Ԥ�ڽ�� */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct api_driver_16_t
{
    /* Ԥ������ */      
    int  setup_env;
    /* �������� */
    int  ret;
    char cpuinfo[128];	
    char binfo[64];	
    char kinfo[128];
    long memory_size;
    long flash_size;
    long cpu_frequency;
    long cpm_frequency;
    long bus_frequency;
	int eth_num;
	int v35_num;
	int e1_num;	
	/* Ԥ�ڽ�� */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct api_driver_17_t
{
    /* Ԥ������ */
    	int setup_env;
    /* �������� */
        char ifname[MAXAPILEN]; 
        int  e1;
        int  channel;
        char timeslot[MAXAPILEN]; 
        int  serial;
        char signal[MAXAPILEN]; 
        int  cmd;
    /* Ԥ�ڽ�� */
        int val;
        int  rtn;
};

/*------------------------------------*/

struct api_driver_18_t
{
  /* Ԥ������ */
  	int setup_env;
  /* �������� */
    char ifname[MAXAPILEN]; 
    int  e1;
    char signal[MAXAPILEN]; 
    int  cmd;
  /* Ԥ�ڽ�� */
    int val;
    int  rtn;
};

/*------------------------------------*/
struct api_ipcd_01_t
{
    /* Ԥ������ */      
    int  setup_env;
    /* �������� */

	/* Ԥ�ڽ�� */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct api_ipcd_02_t
{
    /* Ԥ������ */      
    int  setup_env;
    /* �������� */
    int time_to_detect;
	/* Ԥ�ڽ�� */
    int  val;
    int  rtn;
};

/*------------------------------------*/


struct api_dhcpc_01_t
{
    /* Ԥ������ */
        int  setup_env;
    /* �������� */
    	int enable;
        char ifname[MAXAPILEN];
	 int set_gateway;
    /* Ԥ�ڽ�� */
        int val;
		int rtn;
};

struct api_dhcpc_02_t
{
    /* Ԥ������ */
        int  setup_env;
    /* �������� */
        char ifname[MAXAPILEN];
    /* Ԥ�ڽ�� */
        int val;
		int rtn;
} ;

struct api_dhcpc_03_t
{
    /* Ԥ������ */
        int  setup_env;
    /* �������� */
        char ifname[MAXAPILEN];
    /* Ԥ�ڽ�� */
        int val;
		int rtn;
} ;

struct api_dhcpc_04_t
{
    /* Ԥ������ */
    	int setup_env;
    /* �������� */	 
	 int err;
    	 unsigned long ip;
        unsigned long mask;
        unsigned long gateway;	
        char ifname[MAXAPILEN];
	 
    /* Ԥ�ڽ�� */
        int val;
	 int rtn;

} ;
#endif
