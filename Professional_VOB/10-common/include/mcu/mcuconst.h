/*****************************************************************************
   ģ����      : mcu
   �ļ���      : mcuconst.h
   ����ļ�    : 
   �ļ�ʵ�ֹ���: MCU��������
   ����        : ������
   �汾        : V3.0  Copyright(C) 2001-2002 KDC, All rights reserved.
-----------------------------------------------------------------------------
   �޸ļ�¼:
   ��  ��      �汾        �޸���      �޸�����
   2003/10/13  3.0         ������       ����
   2005/02/19  3.6         ����       �����޸�
******************************************************************************/
#ifndef __MCUCONST_H_
#define __MCUCONST_H_

#ifndef _EXCLUDE_VCCOMMON_H
#include "vccommon.h"
#endif

//OS����
#define     OS_TYPE_VXWORKS                 1   //Vx
#define     OS_TYPE_LINUX                   2   //Linux
#define     OS_TYPE_WIN32                   3   //Windows

//�豸���ඨ��---MCU���Ͷ���
// ����vccommon.h�еĶ���
// MCU_TYPE_KDV8000
// MCU_TYPE_KDV8000B
// MCU_TYPE_KDV8000C
// MCU_TYPE_WIN32

//�豸���ඨ��---�������Ͷ���
#define		EQP_TYPE_MIXER                   1   //������
#define		EQP_TYPE_VMP                     2   //ͼ��ϳ���
#define		EQP_TYPE_RECORDER                3   //¼���
#define		EQP_TYPE_BAS                     4   //����������
#define		EQP_TYPE_TVWALL                  5   //����ǽ
#define		EQP_TYPE_DCS                     6   //���ݷ�����
#define     EQP_TYPE_PRS                     7   //���ش�
#define     EQP_TYPE_FILEENC                 8   //�ļ�������
#define		EQP_TYPE_VMPTW                   9   //ͼ��ϳɵ���ǽ
//4.6�汾 �¼� jlb
#define		EQP_TYPE_HDU					10	 //�������ֵ���ǽ// xliang [12/5/2008]

// ���������������ͣ��ڲ�ʹ��
#define		TYPE_MPUSVMP				11	 //MPU-��VMP
#define		TYPE_MPUDVMP				12   //MPU-VMP
#define		TYPE_MPUBAS					13	 //MPU-BAS
#define		TYPE_EVPU					14	 //EVMP
#define		TYPE_EBAP					15   //EBAP

// mpu�����Ͷ���---------xliang [12/5/2008] ----------
#define		VMP								(u8)0	//��vpu (Ĭ��ֵ0)
#define		EVPU_SVMP						(u8)1	//EVPU-��VMP
#define		EVPU_DVMP						(u8)2	//EVPU-˫VMP
#define		MPU_SVMP						(u8)3	//MPU-��VMP
#define		MPU_DVMP					    (u8)4	//MPU-˫VMP
#define		MPU_BAS							(u8)5	//mpu-bas
#define		MPU_EBAP						(u8)6	//EBAP

//MPU board version
#define		MPU_BOARD_A128					(u8)0	//MPU A ��
#define		MPU_BOARD_B256					(u8)1	//MPU B ��

//VMP���ͨ����Ŀ
#define		MAXNUM_MPU_OUTCHNNL				(u8)4	//MPU  4��
#define		MAXNUM_EVPU_OUTCHNNL			(u8)2	//EVPU 2��

//MPU����ǰ����ͨ����Ŀ
#define		MAXNUM_SVMP_HDCHNNL				(u8)3	//SVMPǰ����ͨ������3   
#define		MAXNUM_DVMP_HDCHNNL				(u8)1	//DVMPǰ����ͨ������1
#define		MAXNUM_SVMPB_HDCHNNL			(u8)4	//SVMP B��ǰ����ͨ����: 4

//MPU���ܷ�h264 CIF����
#define		MAXNUM_SVMP_NON264CIFCHNNL		(u8)12	

//Resolutions that can be acceptable
#define		MAXNUM_ACCEPTABLE_RES			(u8)55

//�豸���ඨ��---�ն����Ͷ���
#define		MT_TYPE_NONE                     0   //������Ҳ������
#define     MT_TYPE_MT                       3
#define		MT_TYPE_MMCU	                 4   //�ϼ�MCU
#define     MT_TYPE_SMCU                     5   //�¼�MCU

//����ͼ����������ģʽ
#define		MODE_NONE			             0	 //����Ƶ������
#define		MODE_VIDEO						 1	 //ֻ����Ƶ
#define		MODE_AUDIO						 2	 //ֻ����Ƶ
#define		MODE_BOTH						 3   //����Ƶ����
#define     MODE_DATA                        4   //���� 
#define     MODE_SECVIDEO                    5   //�ڶ�·��Ƶ

//���̱�Ŷ���
#define		MT_MANU_KDC                      1   //�ƴ�
#define		MT_MANU_NETMEETING               2   //Netmeeting
#define		MT_MANU_POLYCOM                  3   //PolyCom
#define		MT_MANU_HUAWEI                   4   //��Ϊ
#define		MT_MANU_TAIDE                    5   //̩��
#define		MT_MANU_SONY                     6   //SONY
#define		MT_MANU_VCON                     7   //VCON
#define		MT_MANU_RADVISION                8   //Radvision
#define     MT_MANU_KDCMCU                   9   //kedamcu
#define		MT_MANU_PENTEVIEW                10  //��̩
#define		MT_MANU_VTEL                     11  //VTEL
#define     MT_MANU_ZTE                      12  //�����ն�
#define     MT_MANU_ZTEMCU                   13  //����MCU
#define     MT_MANU_CODIAN                   14  //CodianMCU
#define		MT_MANU_OTHER                    15  //����

//�ն˻���״̬
#define     MT_STATUS_AUDIENCE               0   //����  
#define     MT_STATUS_CHAIRMAN               1   //��ϯ
#define     MT_STATUS_SPEAKER                2   //������

//TvWallOutputMode
#define     TW_OUTPUTMODE_NONE               0   //�����ģʽ
#define     TW_OUTPUTMODE_AUDIO              1   //��Ƶ���ģʽ
#define     TW_OUTPUTMODE_VIDEO              2   //��Ƶ���ģʽ
#define     TW_OUTPUTMODE_BOTH               3   //����Ƶ���ģʽ

//HduOutputMode   jlb
#define     HDU_OUTPUTMODE_NONE               0   //�����ģʽ
#define     HDU_OUTPUTMODE_AUDIO              1   //��Ƶ���ģʽ
#define     HDU_OUTPUTMODE_VIDEO              2   //��Ƶ���ģʽ
#define     HDU_OUTPUTMODE_BOTH               3   //����Ƶ���ģʽ
//�ն�����ԭ��
#define     MTLEFT_REASON_EXCEPT             1   //�쳣�����������ת��
#define     MTLEFT_REASON_NORMAL             2   //�����Ҷ�
#define     MTLEFT_REASON_RTD                3   //RTD��ʱ
#define     MTLEFT_REASON_DRQ                4   //DRQ
#define     MTLEFT_REASON_UNMATCHTYPE        5   //���Ͳ�ƥ��
//�ն�δ����ԭ��
#define     MTLEFT_REASON_BUSY               6   //�ն�æ
#define     MTLEFT_REASON_REJECTED           7   //�ն������Ҷ�
#define     MTLEFT_REASON_UNREACHABLE        8   //�ն˲��ɴ�
#define     MTLEFT_REASON_LOCAL              9   //
#define     MTLEFT_REASON_BUSYEXT            10  //�ն�æ,���ն�Ŀǰ���ڻ���ļ��𼰻�������

#define     MTLEFT_REASON_UNKNOW             0xff   //δ֪����

//�������ֱ��ʾܾ���ԭ��
#define		CASCADE_ADJRESNACK_REASON_NONEKEDA	1		//�ǿƴ�(�����µ�)
#define		CASCADE_ADJRESNACK_REASON_INTVWALL	2		//��DEC5�У������ϵ������ɿ��ǻ�ack��
#define		CASCADE_ADJRESNACK_REASON_INVMP		3		//��VMP��
#define		CASCADE_ADJRESNACK_REASON_UNKNOWN	0		//δ֪ԭ��


//Э�����Ͷ���
#define		PROTOCOL_TYPE_H323				1  //H323
#define		PROTOCOL_TYPE_H320              2  //H320
#define		PROTOCOL_TYPE_SIP               3  //SIP

//MCU���ú�ҵ��������
#define     MAXNUM_H225H245_MT              192 //�ײ�Э��ջ����������
#define		MAXNUM_CONF_MT					192  //�������������MT��,ǣ�浽�ӿڣ�8000B��8000ά�ֲ��� 
#define		MAXNUM_CALL_CHANNEL             12   //ÿ�������е����ͨ����

#define     MAXNUM_MCU_VC                   16   //MCU֧��ͬʱ���ӵ����VCS��
#define		MAXNUM_MCU_MC			        16   //MCU���ӻ������̨�����
#define		MAXNUM_MCU_PERIEQP				140    //MCU�����������, ����28��HDU, ����λ��16������12��λ��
//#define		MAXNUM_MCU_PERIEQP				(128+12)    //MCU�����������, ����28��HDU, ����λ��16������12��λ��
#define		MAXNUM_CONF_SPY					128	 //һ���������spy��
#define     SPY_CHANNL_NULL                 65535 // ��ʾ�ü�����ش�ͨ��δ����
#define     DEFAULT_MAX_SENDSPY_BW          100000
#define     DEFAULT_MAX_RECVSPY_BW          100000

#define     MAXNUM_MC_CHANNL                16  // ���̨�������ͨ����

// ����MTU��С, zgc, 2007-04-02
#define		MAXNUM_MTU_SIZE					1468  //MTU��󳤶�
#define		MINNUM_MTU_SIZE					1308  //MTU��С����
#define		DEFAULT_MTU_SIZE				MAXNUM_MTU_SIZE  //MTUĬ�ϳ���

// ȱʡ��DSC��MCU8000�ⲿIP���ڲ�ͨ��IP
#define DEFAULT_MCU_IP                          "192.168.2.1"
#define DEFAULT_DSC_IP                          "192.168.2.2"
#define DEFAULT_IPMASK        					"255.255.255.0"

#define DEFAULT_MCU_INNERIP                     "10.253.253.250"
#define DEFAULT_DSC_INNERIP                     "10.253.253.249"
#define DEFAULT_INNERIPMASK						"255.255.255.252"

#define ETH_IP_MAXNUM						    16
#define MAXNUM_MCSACCESSADDR					2

// MINIMCU���ڵ���������
#define	NETTYPE_INVALID						0
#define NETTYPE_LAN							1
#define NETTYPE_WAN							2
#define NETTYPE_MIXING_ALLPROXY				3
#define NETTYPE_MIXING_NOTALLPROXY			4

#ifdef _MINIMCU_    // 8000B ����

// �������ڲ����ݽṹ��������
#define     MAXNUM_MCU_MT                   (u16)128  //һ��MCU֧������ն�����ͬʱ���ߵ��նˣ� 
#define		MAXNUM_MCU_CONF					64        //һ��MCU�ڲ����õ�������������Χ
#define     MAXNUM_MCU_TEMPLATE             32        //���ģ�����(����16���ӵ�32������16���ָ�VCS)
#define     MAXNUM_MCU_VCSTEMPLATE          16        //VCS�ɴ�����ģ����
#define     MAXNUM_MCU_MCSTEMPLATE          (MAXNUM_MCU_TEMPLATE - MAXNUM_MCU_VCSTEMPLATE)
#define		MAXNUM_DCS_CONF					16
#define		MAXNUM_DCS_CONFMT				16

#define     MAXNUM_MCU_VCCONF              16        //һ��MCU��������ٿ��ĵ��Ȼ����� 

#define		MAXNUM_DRI                      16        //DRI������ 
#define		MAXNUM_DRI_MT                   192       //DRI���ϵ������������ն���

// ��������ҵ��������
#define     MAXLIMIT_MPC_MP                 (u16)32   // MPC ����MPת������, MB
#define     MAXLIMIT_CRI_MP_MDSC            (u16)128  // CRI MP(MDSC) ת������, MB (32*2M*2direction)
#define     MAXLIMIT_CRI_MP_HDSC            (u16)512  // CRI MP(HDSC) ת������, MB (128*2M*2direction)
#define     MAXLIMIT_CRI_MP                 MAXLIMIT_CRI_MP_HDSC

#define     MAXLIMIT_MPC_MP_PMNUM           (u16)16   // MPC����MPת��������PM(�����ʺ��ն����ĳ˻����㣬mcuҵ���MPת�������������������ơ���λPM��һ��1M���ն�Ϊһ��PM)
#define     MAXLIMIT_CRI_MP_MDSC_PMNUM      (u16)64   // CRI MP(MDSC) ת������, PM
#define     MAXLIMIT_CRI_MP_HDSC_PMNUM      (u16)256  // CRI MP(HDSC) ת������, PM
#define     MAXLIMIT_CRI_MP_PMNUM           MAXLIMIT_CRI_MP_HDSC_PMNUM

#define		MAXHDLIMIT_MPC_MTADP			(u8)2	  //MPC ����MtAdp����HD MT����
#define		MAXNUM_HDI_MT					(u16)48  //HDI�ϵ������������ն���

#ifdef WIN32
#define     MAXLIMIT_MPC_MTADP              (u8)112   // MCU ����MtAdp��������
#define     MAXLIMIT_MPC_MTADP_SMCU         (u8)28    // MCU ����MtAdp SMCU��������	
#else
#define     MAXLIMIT_MPC_MTADP              (u8)8     // MCU ����MtAdp��������
#define     MAXLIMIT_MPC_MTADP_SMCU         (u8)4     // MCU ����MtAdp SMCU��������
#endif
#define     MAXLIMIT_CRI_MTADP              (u8)128   // HDSC/MDSC ��������
#define     MAXLIMIT_CRI_MTADP_SMCU         (u8)16    // HDSC/MDSC SMCU��������
#define     MAXLIMIT_HDI_MTADP              (u8)112     // HDI ��������(û�����壬���������)

#define     MAXLIMIT_MCU_CASCONF            (u8)4     // ��༶���������
#define     MAXLIMIT_CONF_SMCU              (u8)4     // ����������� SMCU

#else               // 8000 ����

// �������ڲ����ݽṹ��������
#define     MAXNUM_MCU_MT                   (u16)448  //MCU֧������ն��� 
#define		MAXNUM_MCU_CONF					64        //һ��MCU�ڲ����õ�������������Χ
#define     MAXNUM_MCU_TEMPLATE             64        //���ģ�����
#define     MAXNUM_MCU_VCSTEMPLATE          16        //VCS�ɴ�����ģ����
#define     MAXNUM_MCU_MCSTEMPLATE          (MAXNUM_MCU_TEMPLATE - MAXNUM_MCU_VCSTEMPLATE)
#define		MAXNUM_DCS_CONF					32
#define		MAXNUM_DCS_CONFMT				64

#define     MAXNUM_MCU_VCCONF              16        //һ��MCU��������ٿ��ĵ��Ȼ����� 

#define		MAXNUM_DRI                      64        //DRI������ 
#define		MAXNUM_DRI_MT                   192       //DRI���ϵ������������ն���

// ��������ҵ��������
#define     MAXLIMIT_MPC_MP                 (u16)60   // MPC ����MPת������, MB
#define     MAXLIMIT_CRI_MP                 (u16)120  // CRI MP ת������, MB(�����ʼ��㣬mplib������ͳ��ʹ��)

#define     MAXLIMIT_MPC_MP_PMNUM           (u16)30   // MPC ����MPת������, PM(�����ʺ��ն����ĳ˻����㣬mcuҵ���MPת�������������������ơ���λPM��һ��1M���ն�Ϊһ��PM)
#define     MAXLIMIT_CRI_MP_PMNUM           (u16)60   // CRI MP ת������

#define		MAXHDLIMIT_MPC_MTADP			(u8)2	  //MPC ����MtAdp����HD MT����
#define		MAXNUM_HDI_MT					(u16)48  //HDI�ϵ������������ն���
 
#ifdef WIN32
#define     MAXLIMIT_MPC_MTADP              (u8)112   // MPC ����MtAdp��������
#define     MAXLIMIT_MPC_MTADP_SMCU         (u8)28    // MPC ����MtAdp SMCU��������
#else
#define     MAXLIMIT_MPC_MTADP              (u8)24    // MPC ����MtAdp��������
#define     MAXLIMIT_MPC_MTADP_SMCU         (u8)12    // MPC ����MtAdp SMCU��������
#endif
#define     MAXLIMIT_CRI_MTADP              (u8)112   // CRI ��������
#define     MAXLIMIT_CRI_MTADP_SMCU         (u8)28    // CRI SMCU��������
#define     MAXLIMIT_HDI_MTADP              (u8)112     // HDI ��������

#ifdef WIN32
#define     MAXLIMIT_MCU_CASCONF            (u8)2     // ��༶���������
#define     MAXLIMIT_CONF_SMCU              (u8)4     // ����������� SMCU
#else
#define     MAXLIMIT_MCU_CASCONF            (u8)16    // ��༶���������
#define     MAXLIMIT_CONF_SMCU              (u8)56    // ����������� SMCU
#endif
#endif

#define     MAXNUM_MCU_MODEM                (u16)16     //���ǻ������modem��

//���������������
#define     CHN_ADPMODE_NONE               (u8)0   //��
#define     CHN_ADPMODE_MVBRD              (u8)1   //�����㲥����
#define     CHN_ADPMODE_DSBRD              (u8)2   //˫���㲥����
#define     CHN_ADPMODE_MVSEL              (u8)3   //����ѡ������
#define     CHN_ADPMODE_DSSEL              (u8)4   //˫��ѡ������

//��������ͨ�����Ͷ���
#define     TYPE_MAU_NORMAL                 (u8)0   //��ͨMAU
#define     TYPE_MAU_H263PLUS               (u8)1   //ΪH263plus���Ƶ�MAU
#define     TYPE_MPU                        (u8)2   //MPU

//MAU����궨��
#define		MAXNUM_VOUTPUT 					(u8)2   // һ·��������������·��
#define		MAXNUM_MAU_VCHN				    (u8)1   // һ��MAU�����������ͨ����
#define		MAXNUM_MAU_DVCHN				(u8)1   // һ��MAU���˫������ͨ����

//MPU����궨��
#define     MAXNUM_MPU_VCHN                 (u8)4   // һ��MPU�������ͨ����, ����������˫��

//��������ͨ���궨��
#define     HDBAS_CHNTYPE_MAU_MV            (u8)0
#define     HDBAS_CHNTYPE_MAU_DS            (u8)1
#define     HDBAS_CHNTYPE_MPU               (u8)2


#define MAXNUM_CONF_MVCHN                   (u8)3       //�������������ͨ����
#define MAXNUM_CONF_DSCHN                   (u8)3       //�������˫������ͨ����
    
#define MAXNUM_CONF_DUALMVCHN               (u8)1
#define MAXNUM_CONF_DUALDSCHN               (u8)2

#define MAXNUM_CONF_MAU                     (u8)4       //�������MAU��
#define MAXNUM_CONF_MPU                     (u8)MAXNUM_MPU_CHN       //�������MPUͨ����

#define MAU_CHN_NONE                        (u8)0
#define MAU_CHN_NORMAL                      (u8)1       //HDBAS/MAU ͨ������ͨ��
#define MAU_CHN_VGA                         (u8)2       //HDBAS/MAU ��VGA�����ͨ��
#define MAU_CHN_263TO264                    (u8)3       //HDBAS/MAU ��263��264�����ͨ��
#define MAU_CHN_264TO263                    (u8)4       //HDBAS/MAU ��264��263�����ͨ��
#define MPU_CHN_NORMAL                      (u8)5       //HDBAS/MPU ͨ������ͨ����ͨ����ǿ��MAU_CHN_NORMAL

#define MAXNUM_MPU_CHN                      (u8)4


// ���ʱ������(ʵ������)
#ifdef _VXWORKS_
    #ifdef _MINIMCU_
    #define     MAXNUM_ONGO_CONF            32   
    #define     MAXNUM_ONGO_VCSCONF         16 // ����ͬʱ�ٿ���VCS������   
    #else
    #define     MAXNUM_ONGO_CONF            32  //mtadp �� mp ��������ʱ
    #define     MAXNUM_ONGO_VCSCONF         16 // ����ͬʱ�ٿ���VCS������ 
    #endif 
#elif defined(_LINUX_)
    #ifdef _MINIMCU_
    #define     MAXNUM_ONGO_CONF            32 // 16������û���⣬�����Ƿ���������ҵ��
    #define     MAXNUM_ONGO_VCSCONF         16 // ����ͬʱ�ٿ���VCS������ 
    #else    
    #define     MAXNUM_ONGO_CONF            32  //����ֵ36(��128M,MCU����ռ18M,Ԥ��20M)
    #define     MAXNUM_ONGO_VCSCONF         16 // ����ͬʱ�ٿ���VCS������ 
    #endif
#else   // WIN32
#define     MAXNUM_ONGO_CONF                32
#define     MAXNUM_ONGO_VCSCONF             16 // ����ͬʱ�ٿ���VCS������ 
#endif

// �����������, 8000/8000B: 8M, 8000C: 4M
#ifdef _MINIMCU_
    #ifndef _MCU8000C_
        #define MAX_CONFBITRATE             8128
    #else
        #define MAX_CONFBITRATE             4096
    #endif
#else
    #define MAX_CONFBITRATE                 8128
#endif

#define     MAXNUM_VIEWINCONF				5    //ÿ������������ͼ��
#define     MAXNUM_GEOINVIEW				5    //ÿ����ͼ����󼸺β�����
#define		MAXNUM_SUBFRAMEINGEO            16   //ÿ�����β��ֵ�����Ա��
#define     MAXNUM_VSCHEMEINVIEW			4    //ÿ����ͼ�����Ƶ������
#define     MAXNUM_MIXERINCONF              16   //ÿ�������е���������  
#define     MAXNUM_ADDMT                    10   //һ�����ӵ����MT��   

#define     MAXNUM_NPLUS_MCU                16
 
//�������(ģ��)��confidxΪ����map��������+1
#define MIN_CONFIDX                         1
#define MAX_CONFIDX                         (MAXNUM_MCU_CONF+MAXNUM_MCU_TEMPLATE)

//���֧�ֵ������  
#define     MAXNUM_HDUBRD                   28   // ���Hdu������Ŀ   4.6   jlb
#define     MAXNUM_OTHERBRD                 64   // ��󵥰��ϵ���Ŀ
#define     MAXNUM_BOARD       (MAXNUM_HDUBRD + MAXNUM_OTHERBRD)   // 64 + 28(hdu)
//ͬһ������������
#define     MAXNUM_PERIEQP                  16   //����HDU
#define     MAXNUM_PERIHDU                  28   //4��tvs,ÿ��7��HDU 
#define		MAXNUM_PERIDVMP					8	 //8��mpu-dvmp // xliang [12/10/2008] 	
#define		MAXLEN_EQP_ALIAS                16   //���������󳤶�

//��󵥰��š��ۺ�
#define     MAXNUM_LAYER                    4   //���
#define     MAXNUM_SLOT                     14  //�ۺ�  
#define     MAXNUM_TVSSLOT                  7   // TVS�Ĳ�λ  jlb 4.6 
#define     MAXLEN_SLOT_ALIAS               16  //�ۺ���󳤶�

 // �Ƿ���MapId
#define INVALID_MAP_ID	        		    (u8)255        

//������
#define     SLOTTYPE_MC                     1   
#define     SLOTTYPE_EX                     2
#define     SLOTTYPE_TVSEX                    3 //TVS�Ĳ����� 4.6 jlb 

#define     LEN_DES                         8	 //byte
#define     LEN_AES                         16	 //byte

//��ַ����������(�ο���ַ��ͷ�ļ�)
#define     MAXLEN_ADDR_ENTRYNAME           64  //��Ϊ64
#define     MAXLEN_ADDR_323ALIAS            32
#define     MAXLEN_ADDR_E164NUM             16
#define     MAXLEN_ADDR_320ID               48

#define     MAXNUM_ADDRGROUP                64
#define     MAXNUM_ADDRENTRY                1024

//������س�������
#define     MAXNUM_SUB_MCU                  56   //����¼�MCU����
//#define     MASTER_MC_ID                    193  //��MC��ID��
#define		MAXNUM_ACCOMMODATE_SPY			(u16)512	 //MMCU�����������SMCU��spy��

#define		MCU_Q931_PORT					1720	//ȱʡQ931�˿ں�
#define		MCU_RAS_PORT					1719	//ȱʡRAS�˿ں�
#define		MCU_LISTEN_PORT					60000	//ȱʡ����/���TCP�����˿ں�(TCP,OSP)
#define		MCU_H225245_STARTPORT	        60002	//ȱʡMCU��MT��������ʼ�˿ں�(TCP) -- 60386(2*192)
//#define		MCU_RCVH224_PORT				2330	//�����ն�H224���ݶ˿ں�


//��־������
#define     LOGLVL_EXCEPTION				0	//�쳣
#define     LOGLVL_IMPORTANT				1	//��Ҫ��־
#define     LOGLVL_DEBUG1					254 //һ��������Ϣ
#define     LOGLVL_DEBUG2					255 //����������Ϣ

//����ҵ��APP�Ŷ��壨����kdvdef.h�з�Χ����ͳһ���壩
#define     AID_MCONSOLE					AID_MCU_BGN	        //�������̨
#define     AID_MCU_AGENT					AID_MCU_BGN + 5 	//MCU����
#define     AID_MCU_BRDMGR					AID_MCU_BGN + 6 	//�������
#define		AID_MCU_BRDAGENT				AID_MCU_BGN + 7 	//�������
#define		AID_MCU_BRDGUARD				AID_MCU_BGN + 8	    //��������
#define     AID_MCU_MTADP					AID_MCU_BGN + 9	    //MTADP
#define     AID_VMPTW                       AID_MCU_BGN + 10    //�໭�渴�ϵ���ǽ
#define     AID_MIXER						AID_MCU_BGN + 11	//������
#define     AID_TVWALL						AID_MCU_BGN + 12	//����ǽ
#define     AID_RECORDER					AID_MCU_BGN + 13	//¼���
#define     AID_DCS							AID_MCU_BGN + 14	//���ݻ��������
#define     AID_BAS							AID_MCU_BGN + 15	//�������������
#define     AID_MP							AID_MCU_BGN + 16	//MP
#define	    AID_VMP							AID_MCU_BGN + 17	//����ϳ���
#define     AID_PRS							AID_MCU_BGN + 18    //���ط�
#define		AID_PRS_GUARD					AID_MCU_BGN + 19	//prs����
#define     AID_HDU                         AID_MCU_BGN + 20    //HDU
#define		AID_MPU							AID_MCU_BGN + 21	//MPU
#define     AID_MCU_VC				        AID_MCU_BGN + 22    //MCUҵ��
#define     AID_MCU_GUARD					AID_MCU_BGN + 23	//MCU����
#define     AID_MCU_MCSSN					AID_MCU_BGN + 24	//MCU�������̨�Ự
#define     AID_MCU_CONFIG					AID_MCU_BGN + 25	//MCU���ûỰ
#define     AID_MCU_MTADPSSN				AID_MCU_BGN + 26	//MCU��MTADP�Ự
#define     AID_MCU_PERIEQPSSN				AID_MCU_BGN + 27	//MCU����Ự
#define     AID_MCU_MPSSN					AID_MCU_BGN + 28	//MCU��MP�Ự
#define		AID_MCU_DCSSSN					AID_MCU_BGN + 29	//MCU��DCS�Ự
#define     AID_MCU_MSMANAGERSSN			AID_MCU_BGN + 30	//�ȱ��ݻỰģ��
#define     AID_MCU_NPLUSMANAGER            AID_MCU_BGN + 31    //N+1���ݹ���ģ��
#define     AID_MCU_VCSSN					AID_MCU_BGN + 32	//VCS�������̨�Ự

#define     AID_MCU_MTSSN                   AID_MCU_BGN + 33    //����ƽ̨Э������Ự
#define     AID_MCU_MODEMSSN                AID_MCU_BGN + 34    //����ƽ̨Modem�Ự
#define     AID_UDPDISPATCH                 AID_MCU_BGN + 35    //����ƽ̨�ն���Ϣ��udp�Ự
#define     AID_UDPNMS                      22//AID_MCU_BGN + 36    //����ƽ̨NMS������udp�Ự


//CPPUNIT��������
#define     AID_TEST_MCAGT					AID_MCU_BGN + 40	//MC���ɲ���
#define     AID_UNIT_TEST_MCAGT				AID_MCU_BGN + 41	//MC��Ԫ����
#define     AID_TEST_MTCAGT					AID_MCU_BGN + 42	//MTC���ɲ���
#define     AID_UNIT_TEST_MTCAGT			AID_MCU_BGN + 43	//MTC��Ԫ����
#define     AID_TEST_NMCAGT					AID_MCU_BGN + 44	//NMC
#define     AID_UNIT_TEST_MCUAGT			AID_MCU_BGN + 45	//MCU��Ԫ����
#define     AID_UNIT_TEST_MTAGT				AID_MCU_BGN + 46	//MT��Ԫ����
#define     AID_UNIT_TEST_SIMUMT            AID_MCU_BGN + 47
#define     AID_HDUAUTO_TEST                AID_MCU_BGN + 48    //hdu�Զ����

// ������ҪӦ�õ����ȼ�����(�ر���ͬһ�������ж��)
#define     APPPRI_MIXER                    80
#define     APPPRI_BAS                      80
#define     APPPRI_PRS                      80
#define     APPPRI_TVWALL                   80
#define     APPPRI_VMP                      80
#define     APPPRI_MPW                      80
#define     APPPRI_REC                      80
#define     APPPRI_HDU                      80
#define		APPPRI_MPU						80	
 
#define     APPPRI_HDUAUTO                  80   // HDU�Զ�������ȼ�

#define     APPPRI_PRS_GUARD	            75

#define     APPPRI_MTADP                    80
#define     APPPRI_MP                       90

#define     APPPRI_BRDGUARD                 90
#define     APPPRI_BRDAGENT                 100

#define     APPPRI_MCUGUARD                 75
#define     APPPRI_MCUVC                    80
#define     APPPRI_MCUMSMGR                 80
#define     APPPRI_MCUAGT                   80
#define     APPPRI_MSCONFIG                 80
#define     APPPRI_MCUSSN                   90
#define     APPPRI_MCUCONFIG                90
#define     APPPRI_MCUBRDGUARD              90
#define     APPPRI_MCUBRDMANAGER            100
#define     APPPRI_MCUNPLUS                 80

//MCU E1Ӳ������
#define      MAXNUM_MCU_DTI					32  //MCU���DTI��Ŀ
#define      MAXNUM_MCU_E1_PER_DTI			8	//ÿ��DTI�����E1��
#define      MAXNUM_MCU_MT64K				128 //MCU����MT���ʱ϶��:8M
#define      MAXNUM_MCU_SMCU64K				512 //�����¼�MCU���ʱ϶��:4*8M
 
//���賣������
#define		MAXNUM_BASGRP					5   //���������������������RTPͷ��
#define     MAXNUM_PRS_CHNNL				16	//���ط���������
#define     MAXNUM_BAS_CHNNL				32  //�������������ͨ���� 
#define     MAXNUM_MIXER_GROUP				5	//�������������
#define     MAXNUM_MIXER_GRPCHNNL			192 //���������Ա�����
#define     MAXPORTSPAN_MIXER_GROUP			570 //�������鵥��˿ڷ�Χ(Ӧ����>=�������ͨ����*PORTSPAN)
#define     MIXER_INVALID_GRPID				255 //��Ч�������
#define     MIXER_INVALID_CHNNLID			255 //��Ч�����ŵ���
#define     MAXNUM_RECORDER_CHNNL			32	//¼������ͨ������(��¼��ͷ���ͨ��)
#define     MAX_VOD_FILES_LEN				1024//VOD�ļ����б���󳤶�
#define     MAX_VOD_FNAME_LEN				155	//VOD�ļ�����󳤶ȣ������ݿ�һ��
#define     MAX_VODFILEPATH_LEN				100	//VOD�ļ�Ŀ¼��󳤶ȣ������ݿ�һ��
#define     MAXLEN_RECORD_NAME              64  //�ϱ�����״̬ʱ¼���ļ����ĳ���
#define     DEFAULT_MIXER_VOLUME			250	//ȱʡ�Ļ�������
#define		MAXNUM_MAP						5	//�������map��
#define		MAXLEN_TRAP_COMMUNITY			33	//trap community ��󳤶�(��Чλ32)
#define		MAXNUM_TRAP_LIST				16	//trap����󳤶�
#define		MAXNUM_HDU_CHANNEL              2   //һ��HDU�����ͨ����
//���HDU������ͨ����ͨ����   jlb
#define     MAXNUM_HDUCFG_CHNLNUM           56  //��������HDU������ͨ����

// HDUԤ����������󳤶�    jlb
#define		MAX_HDUSTYLE_ALIASLEN           32

//Mcu��DCS��������
#define		MAXNUM_MCU_DCS					1	//MCU����DCS������, Ŀǰֻ֧��һ��

//������������������
#define		MAXNUM_BRD_EQP					5
#define		MAXNUM_HDUBRD_EQP					1


//ÿ��map������ͨ����
#ifdef _MINIMCU_
#define     MAXNUM_MIXER_CHNNL              32
#else
#define     MAXNUM_MIXER_CHNNL              MAXNUM_MIXING_MEMBER
#endif
//���Ƿ�ɢ����������ƻ�������
#define     MAXNUM_MIXERCHNNL_SATDCONF      4
//Ĭ���ش�����ʱ��
#define     DEF_FIRSTTIMESPAN_PRS           40
#define     DEF_SECONDTIMESPAN_PRS          120
#define     DEF_THIRDTIMESPAN_PRS           240
#define     DEF_LOSETIMESPAN_PRS            480
//Ĭ��trap�˿�
#define     DEF_READWRITE_TRAPPORT          161
#define     DEF_SEND_TRAPPORT               162
//Ĭ���ն˶������ʱ��ʹ���
#define     DEF_DISCCHECKTIME               10
#define     DEF_DISCCHECKTIMES              3
//�ն���С�������ʱ��ʹ���
#define     MIN_DISCCHECKTIME               5   //5s 
#define     MIN_DISCCHECKTIMES              1   //1��
//����ʱ�ն��б�ˢ��ʱ����
#define     PARTLIST_REFRESHTIME            (u16)600 //(��λ����)
//����ʱ��Ƶ��Ϣ����ʱ����
#define     AUDINFO_REFRESHTIME             (u16)600
//����ʱ��Ƶ��Ϣ����ʱ����
#define     VIDINFO_REFRESHTIME             (u16)600
//������Ϣ��������ʱ����(12hour)
#define     CASCADEINFO_MAX_REFRESHTIME     (u16)43200
//������Ϣ�������Сʱ����(30s)
#define     CASCADEINFO_MIN_REFRESHTIME     (u16)30

// �������������Զ�ʱͬ��ʱ���� 300��
#define MS_SYN_MAX_SPAN_TIMEOUT             (u32)300

// �������osp�������Ĭ����������
#define     DEF_OSPDISC_HBTIME              (u16)10
// �������osp�������Ĭ����������
#define     DEF_OSPDISC_HBNUM               (u8)3

//N+1����RTDĬ����������
#define     DEF_NPLUSRTD_TIME               5

//N+1����RTDĬ����������
#define     DEF_NPLUSRTD_NUM                3

//Qos type
#define     QOSTYPE_DIFFERENCE_SERVICE      1   //���ַ���
#define     QOSTYPE_IP_PRIORITY             2   //ip����
//qos �ȼ�
#define     QOS_IP_MAXLEVEL                 7   //ip ���ȷ���ȼ���0��7��
#define     QOS_DIFF_MAXLEVEL               63  //���ַ���ȼ���0��63��
//ip ��������
#define     IPSERVICETYPE_NONE              0   //ȫ����ѡ
#define     IPSERVICETYPE_LOW_DELAY         1   //��С�ӳ�
#define     IPSERVICETYPE_HIGH_THROUGHPUT   2   //���������
#define     IPSERVICETYPE_HIGH_RELIABILITY  4   //��߿ɿ���
#define     IPSERVICETYPE_LOW_EXPENSE       8   //��ͷ���

//�����ѯ����״̬��ʱʱ��
#define     WAITING_MSSTATUS_TIMEOUT        (8*1000) // guzh [9/12/2006] �޸�Ϊ8s

//����ϳɷ��Ĭ��RGBֵ
#define     VMPSTYLE_DEFCOLOR               (u32)(246|(246<<8)|(246<<16))// r|(g<<8)|(b<<16)
//����ϳ���󷽰�����
#define     MAX_VMPSTYLE_NUM                5
//HDUԤ����󷽰�����
#define   MAX_HDUSTYLE_NUM                  16
// ����ϳɷ���������󳤶�
#define  MAX_VMPSTYLE_ALIASLEN              32   
// ����ϳ��������
// ����
#define FONT_HEI    (u8)01 // ����
#define FONT_SONG   (u8)02 // ���� (Ĭ��)
#define FONT_KAI    (u8)03 // ����
// �ֺ�
#define FONT_SIZE_24  24	// 24*24 (Ĭ��)
#define FONT_SIZE_32  32	// 32*32
// ���뷽ʽ
#define LEFT_ALIGN    (u8)1  // ��
#define MIDDLE_ALIGN  (u8)2  // ��
#define RIGHT_ALIGN   (u8)3  // ��

// ����ϳ�����Ĭ��������ɫ
#define DEFAULT_TEXT_COLOR  (u32)(44|(94<<8)|(180<<16))  // blue
// ����ϳ�����Ĭ�ϱ���ɫ
#define DEFAULT_BACKGROUND_COLOR (u32)(255|(255<<8)|(255<<16)) // white
// ����ϳ�����Ĭ��͸����
#define DEFAULT_DIAPHANEITY   0 // 
// ����ϳ�����Ĭ���ı�����
#define DEFAULT_TEXT_LEN     (u8)32 
 // ����ϳ�����Ĭ�ϸ߶�
#define wDEFAULT_BMP_HEIGHT  (u16)50 
// BMP�ļ������С
#define  MAX_BMPFILE_SIZE   (u32)800*600  
// ���BMP�ļ����ݴ�С
#define  MAX_BMPDATA_BUFFER (u32)720*576  

// mcucfg.ini �����ļ�����󳤶�
#define    MAXLEN_MCUCFG_INI                8192
// mcuunproccfg.ini�ļ�����󳤶�
#define    MAXLEN_MCUUNPROCCFG_INI          8192

// �����ļ�ȫ·������󳤶�
#define	   MAXLEN_MCU_FILEPATH			128

//Read and save /conf file
#ifdef _VXWORKS_
#define DIR_CONFIG               ( LPCSTR )"/conf"
#define DIR_DATA                 ( LPCSTR )"/data"
#define DIR_FTP                  ( LPCSTR )"/ftp"
#define DIR_WEB                  ( LPCSTR )"/webfiles/doc"
#define DIR_LOG					 ( LPCSTR )"/log"
#endif

#ifdef _LINUX_
#ifdef _X86_  // Redhat
#define DIR_CONFIG               ( LPCSTR )"/usr/etc/conf"
#endif
#if defined(_PPC_) || defined(_ARM_)
#define DIR_CONFIG               ( LPCSTR )"/usr/etc/config/conf"	
#endif 

#define DIR_DATA                 ( LPCSTR )"/usr/etc/data"	
#define DIR_FTP                  ( LPCSTR )"/usr/ftp"	
#define DIR_WEB                  ( LPCSTR )"/usr/webroot"
#define DIR_LOG					 ( LPCSTR )"/usr/log"
#endif

#ifdef WIN32
#define DIR_CONFIG               ( LPCSTR )"./conf"	
#define DIR_DATA                 ( LPCSTR )"./data"	
#define DIR_FTP                  ( LPCSTR )"./ftp"	
#define DIR_WEB                  ( LPCSTR )"./webfiles/doc"	
#define DIR_LOG					 ( LPCSTR )"./log"
#endif

#define DIR_EXCLOG               ( LPCSTR )"/usr/log/exc.log"

#define FILE_BRDCFG_INI          ( LPCSTR )"brdcfg.ini"
#define FILE_BRDCFGDEBUG_INI     ( LPCSTR )"brdcfgdebug.ini"    //4.6  jlb
#define MCUCFGFILENAME           ( LPCSTR )"mcucfg.ini"
#define MCUDEBUGFILENAME         ( LPCSTR )"mcudebug.ini"
#define MCUCFGBAKFILENAME		 ( LPCSTR )"mcucfg.bak"
#define MCU_VCSUSER_FILENAME     ( LPCSTR )"vcslogin.usr"
#define MCUUNPROCCFGFILENAME     ( LPCSTR )"mcuunproccfg.ini" 
#define MCU_SAT_CFGFILENAME      ( LPCSTR )"mcusatcfg.ini"        

//linux�°汾���´���ļ���׺
#define LINUXAPP_POSTFIX         ( LPCSTR )"image"
#define LINUXAPP_POSTFIX_BIN     ( LPCSTR )"bin"
//linux�°汾OS�ļ���׺
#define LINUXOS_POSTFIX          ( LPCSTR )"linux"

// License����
#define KEY_FILENAME                  "kedalicense.key"

//#define KEDA_AES_KEY				  "kedacom200606231"
//#define KEDA_COPYRIGHT			      "Suzhou Keda Technology Co.,ltd. Tel:86-512-68418188, Fax: 86-512-68412699, http://www.kedacom.com"

// �������ݵĳ���
//#define LEN_KEYFILE_CONT              (u16)512

//MCU������Ϣ����, zgc, 2007-03-16
#define		MCUCFGINFO_LEVEL_NEWEST			0	//��ǰ���µ������ļ���Ϣ
#define		MCUCFGINFO_LEVEL_LAST			1	//���һ�γɹ���ȡ�������ļ���Ϣ
#define		MCUCFGINFO_LEVEL_DEFAULT		2	//Ĭ��������Ϣ
#define		MCUCFGINFO_LEVEL_PARTNEWEST		3	//ֻ�в��������µ������ļ���Ϣ��
												//���в��ֱ��޸�ΪĬ�ϻ����һ�γɹ���ȡ��������Ϣ

#define     MAX_FILESTREAM_NUM                  3   //ý���ļ����ý������, zgc, 2008-08-02

//��ͬ������
#define     NETSYNTYPE_VIBRATION            1   //������
#define     NETSYNTYPE_TRACE                2   //����
#define     NETSYN_MAX_DTNUM                14  //���DT���
#define     NETSYN_MAX_E1NUM                7   //���E1��

//���鳣������ 
#define     MAXNUM_MC_CHANNL   				16	//�������̨���ͨ����
#define     MAXNUM_MT_CHANNL   				16	//�ն˼�����ͨ����

#define     EQP_CHANNO_INVALID              0xFF //��Ч����ͨ����

//�����������Ͷ���
#define     ADAPT_TYPE_NONE                 0   //������������
#define     ADAPT_TYPE_AUD                  1   //��Ƶ��������
#define     ADAPT_TYPE_VID                  2   //��Ƶ��������
#define     ADAPT_TYPE_BR                   3   //��������
#define     ADAPT_TYPE_CASDAUD              4   //��Ƶ��������
#define     ADAPT_TYPE_CASDVID              5   //��Ƶ��������

//��������ͨ�����Ͷ���
#define     BAS_CHAN_AUDIO                  1   //��Ƶ����ͨ��
#define     BAS_CHAN_VIDEO                  2   //��Ƶ����ͨ��

//cppunit���Խ��
#define		CPPTEST_OK						0	//�ɹ�

//����������Դ��������, zgc, 2008-04-14
#define		SPEAKER_SRC_NOTSEL				(u8)0		// �����˷�ѡ��
#define		SPEAKER_SRC_MCSDRAGSEL			(u8)1		// �������ѡ��
#define		SPEAKER_SRC_CONFSEL				(u8)2		// �����ڲ��߼�ѡ��

enum emChangeSpeakerSrcReason
{
	emReasonUnkown = 0,
	emReasonChangeSpeaker,
	emReasonChangeChairman,
	emReasonChangeBrdSrc
};


//����ͷ���Ʋ�������
#define     CAMERA_CTRL_UP					1   //��
#define     CAMERA_CTRL_DOWN				2   //��
#define     CAMERA_CTRL_LEFT				3   //��
#define     CAMERA_CTRL_RIGHT				4   //��
#define     CAMERA_CTRL_UPLEFT				5   //����
#define     CAMERA_CTRL_UPRIGHT				6   //����
#define     CAMERA_CTRL_DOWNLEFT			7   //����
#define     CAMERA_CTRL_DOWNRIGHT			8   //����
#define     CAMERA_CTRL_ZOOMIN				9   //��ҰС
#define     CAMERA_CTRL_ZOOMOUT				10  //��Ұ��
#define     CAMERA_CTRL_FOCUSIN				11  //������
#define     CAMERA_CTRL_FOCUSOUT			12  //������
#define     CAMERA_CTRL_BRIGHTUP			13  //���ȼ�
#define     CAMERA_CTRL_BRIGHTDOWN			14  //���ȼ�
#define     CAMERA_CTRL_AUTOFOCUS			15  //�Զ�����

// ��ƵԴ����
#define      MAX_OUTPUTNUM					7
#define      MATRIX_MAXPORT					16	

// ʹ����ƵԴ���
#define      VIDEO_OUTPUT_CLOSE				0xfb
#define      VIDEO_OUTPUT_OPEN				0xfc

//MP ��س���
#ifdef _MINIMCU_
#define      MAX_SWITCH_CHANNEL				500
#else
#define      MAX_SWITCH_CHANNEL				500
#endif
#define      MAX_IP_NUM						2

//������ʽ
// guzh [2/13/2007] ˵�������ڽ�����ʽ��4.0R3��ǰ��Ҫ��������
// һ�� H.320 ������������
// ���� ҵ�����ֽ�������ʱ�Ƿ�Ҫ���ţ������ SWITCH_MODE_SELECT ��������
// 
// R4�Ż��󣬵�һ�����ñ���
// �ڶ�������Ŀǰ�߼�ʼ�ն��ն˿�MP�������ţ����Ա��ֶβ���������
// ��������ת����˵�������ɱ�����MP�������ŵ��߼�
// ͬʱ���Ӹ�Ϊ��ʶ֪ͨMP�Ľ�����Ϣ���ͣ�������ȫ�ı䣩
// MP���ݱ�������������ͨ���ڲ���ת�ڵ㣨ÿ����������Ƶ��һ·��ת��ת������ֱ��ת������
#define      SWITCH_MODE_NONE               0   //��Ч��ѡ����ʽ
#define      SWITCH_MODE_BROADCAST			1	//�㲥������ʽ
#define      SWITCH_MODE_SELECT				2	//ѡ��������ʽ


//ȱʡ���ж˿�
#define      DEFAULT_Q931_PORT				MCU_Q931_PORT

//��Ϣ�������
#define      SERV_MSG_LEN					0x7000  //��Ϣ����
#define      SERV_MSGHEAD_LEN				0x30    //��Ϣͷ����


//��Ƶ��������
#define      MATRIXTYPE_INNER				1	//�ڲ���Ƶ����
#define      MATRIXTYPE_VAS					2	//VAS��
#define      MATRIXTYPE_EXTRON				3	//Extron��Ƶ��������

#define      MATRIXPORT_IN					1	//����˿�
#define      MATRIXPORT_OUT					2	//����˿�

#define      MATRIXPORT_SVIDEO				0	//S����
#define      MATRIXPORT_ENCODER				1	//�������˿�
#define      MATRIXPORT_DECODER				1	//�������˿�

#define      PRSCHANMODE_FIRST              1   //��һ��Ƶͨ��
#define      PRSCHANMODE_SECOND             2   //�ڶ���Ƶͨ��
#define		 PRSCHANMODE_BOTH               3   //������Ƶͨ��
#define      PRSCHANMODE_AUDIO              4   //��Ƶͨ��
#define      PRSCHANMODE_AUDBAS             5   //���������Ƶ�ش�ͨ��
#define      PRSCHANMODE_VIDBAS             6   //��ý���������Ƶ�ش�ͨ��
#define      PRSCHANMODE_BRBAS              7   //�������������Ƶ�ش�ͨ��
#define      PRSCHANMODE_VMP2               8   //VMP�ڶ�·�����Ķ����ش�ͨ��

// ���Ӹ���PRSͨ��, zgc, 2008-08-13
#define      PRSCHANMODE_HDBAS_VID          9   //����BAS����Ƶ�Ķ����ش�ͨ��
#define      PRSCHANMODE_HDBAS_DVID         10  //����BAS˫���Ķ����ش�ͨ��

// xliang [4/30/2009]  ��·�����Ĺ㲥Դ(��MPU) PRSͨ��
#define      PRSCHANMODE_VMPOUT1			11	//1080��
#define      PRSCHANMODE_VMPOUT2				12  //720��
#define		 PRSCHANMODE_VMPOUT3			13	//4CIF
#define		 PRSCHANMODE_VMPOUT4		14	//CIF/other

#define      AP_MIN                         96  //��̬�غ���Сֵ
#define      AP_MAX                         126 //��̬�غ���Сֵ

/*����MPC�ĵ����λ��*/
#define		 MCU_BOARD_MPC					16
#define      MCU_BOARD_MPCD                 8

#define      BOARD_INLINE                   (u8)1     // ��������
#define      BOARD_OUTLINE                  (u8)2     // ���岻����
#define      BOARD_UNKNOW                   (u8)3     // ����δ֪
#define      BOARD_CFGCONFLICT              (u8)4     // �������ó�ͻ(��ʱδʹ��)

//�������Ͷ���
#define		BRD_TYPE_MPC					0
#define		BRD_TYPE_DTI					1
#define		BRD_TYPE_DIC					2
#define		BRD_TYPE_CRI					3
#define		BRD_TYPE_VAS					4
#define		BRD_TYPE_MMP					5
#define		BRD_TYPE_DRI					6
#define		BRD_TYPE_IMT					7
#define		BRD_TYPE_APU					8
#define		BRD_TYPE_DSI					9
#define		BRD_TYPE_VPU					10
#define		BRD_TYPE_DEC5					11
#define     BRD_TYPE_DSC                    13
#define     BRD_TYPE_MDSC                   0x10
#define     BRD_TYPE_16E1                   0x11
#define     BRD_TYPE_HDSC                   0x14
//4.6�汾���������� jlb
#define     BRD_TYPE_HDU                    0x15
#define     BRD_TYPE_MPU                    0x16
#define     BRD_TYPE_EBAP                   0x17
#define     BRD_TYPE_EVPU                   0x18
#define		BRD_TYPE_UNKNOW					0xff

//��������������
// DRI ������Ϊ: DRI / TUI
// VPU ������Ϊ: VPU / BAP
// CRI ������Ϊ: CRI / PRS / TUI / HDI
#define     BRD_ALIAS_MPC                   "MPC"
#define     BRD_ALIAS_CRI                   "CRI"
#define     BRD_ALIAS_DRI                   "DRI"
#define     BRD_ALIAS_APU                   "APU"
#define     BRD_ALIAS_VPU                   "VPU"
#define     BRD_ALIAS_DEC5                  "DEC5"
#define     BRD_ALIAS_DSC                   "DSC"
#define     BRD_ALIAS_MDSC                  "MDSC"
#define     BRD_ALIAS_HDSC                  "HDSC"
#define     BRD_ALIAS_TUI                   "TUI"
#define     BRD_ALIAS_HDI                   "HDI"
#define     BRD_ALIAS_PRS                   "PRS"
#define     BRD_ALIAS_BAP                   "BAP"
#define     BRD_ALIAS_MMP                   "MMP"
//4.6�汾������������������ jlb
#define     BRD_ALIAS_MPU                   "MPU"
#define     BRD_ALIAS_HDU                   "HDU"
#define     BRD_ALIAS_EBAP                  "EBAP"
#define     BRD_ALIAS_EVPU                  "EVPU"

#define     MAXLEN_BRDALIAS                 8   // ��Ч����7

#define      DISABLE						0	//��Ч
#define      ENABLE							1	//��Ч

#define		ISTRUE(b)						((b)!=0) 
#define		GETBBYTE(b)						((b)?1:0)
#define		kmax(a,b)						(((a) > (b)) ? (a) : (b))
#define		kmin(a,b)						(((a) < (b)) ? (a) : (b))
#define		astrncpy(a, b, al, bl)  { s32 l = min(al, bl); strncpy((s8 *)a, b, l); a[l-1] = 0;}

#define		arraynum(a)						(sizeof(a)/sizeof(a[0]))

enum emDisconnectReason
{
	emDisconnectReasonDRQ = 1,      // DRQ from GK
	emDisconnectReasonRtd,          // roundtripdelay timeout
	emDisconnectReasonBusy,
	emDisconnectReasonNormal,
	emDisconnectReasonRejected,
	emDisconnectReasonUnreachable,
	emDisconnectReasonLocal,
    emDisconnectReasonUnmatched,    // ��ԭ�����ҵ���壬��Э��ջ�޹ء������䡣
	emDisconnectReasonUnknown,
	emDisconnectReasonBysyExt
};

#define  ADDMTMODE_MCS                  1   //�ն��Ǳ�MCS�����
#define  ADDMTMODE_CHAIRMAN             2   //�ն��Ǳ���ϯ�����
//#define  ADDMTMODE_MTSELF               3   //�ն����Լ������

#define  MIXERID_MIN                    1
#define  MIXERID_MAX                    16
#define  RECORDERID_MIN                 17
#define  RECORDERID_MAX                 32
#define  TVWALLID_MIN                   33
#define  TVWALLID_MAX                   48
#define  BASID_MIN                      49
#define  BASID_MAX                      64
#define  VMPID_MIN                      65
#define  VMPID_MAX                      80
#define  VMPTWID_MIN                    81
#define  VMPTWID_MAX                    96
#define  PRSID_MIN                      97
#define  PRSID_MAX                      112
#define  HDUID_MIN                      113
#define  HDUID_MAX                      140

#define  DEFAULT_PRS_CHANNELS           (u8)3       // Ĭ����Ҫ��Prsͨ����
#define  MAX_TIMES_CREATE_CONF			(u8)5       // ����Դ������
#define  LEN_WAIT_TIME					(u32)5000   // �ȴ�ʱ�䲽��
#define  MAXNUM_CHECK_CAS_TIMES         (u8)3

#define  PORTSPAN                       (u16)10     // �˿ڵļ��

//UDP �˿ڷ��䣬ʹ�÷�Χ��30000--65500

#define CASCADE_SPY_STARTPORT			(u16)30000	// 30000��37000 �ϼ����ɻش�Դ�˿ڣ�10 * 512 = 5120; ���� 1880 
#define CASCADE_BRD_STARTPORT			(u16)38000	// 37000��39000	�¼������ϼ��㲥�˿ڣ�10 * 128 = 1280; ���� 720

//����mcu��Ĭ����ʼ�˿� (VMP)
#define VMP_MCU_STARTPORT               (u16)39000  // 39000��40000 �����VMP: 30  * 16 = 480;    ���ж˿�: 520

//����Ĭ����ʼ�˿�
//����BAS/VMP/MIX/PRS��������MCU8000B�ϣ��ʲ��ܺ�������˿ڳ�ͻ
#define MIXER_EQP_STARTPORT             (u16)40000  // 40000��40600 �����һ��MIX: ���ж˿�: 30
#define BAS_EQP_STARTPORT               (u16)40600  // 40600��40700 �����һ��BAS: ���ж˿�: 50
#define VMP_EQP_STARTPORT               (u16)40700  // 40700��40900 �����һ��VMP: ���ж˿�: 40
#define PRS_EQP_STARTPORT               (u16)40900  // 40900��41000 �����һ��PRS: ���ж˿�: 40
#define TVWALL_EQP_STARTPORT            (u16)41000  // 41000��41500 �����һ��TW:  ���ж˿�: xxx
#define MTW_EQP_STARTPORT               (u16)41500  // �����Ǻ�MCU���������ʼ�˿ڳ�ͻ
#define HDU_EQP_STARTPORT				(u16)42000	// 42000��42100 �����һ��HDU: ���ж˿�: 80
#define REC_EQP_STARTPORT               (u16)7200   // ���ǵ�������ǽ�������¼��������ã�

//����mcu��Ĭ����ʼ�˿�
#define REC_MCU_STARTPORT               (u16)41500  // 41500��46700 �����REC: 320 * 16 = 5120;   ���ж˿�: 80
#define BAS_MCU_STARTPORT               (u16)46700  // 46700��48000 �����BAS: 80  * 16 = 1280;    ���ж˿�: 20
// xliang [12/22/2008]  vmp����ǰ��
// 48000��53000 Ϊ����ǽ����ռ�ö˿�(������xDSC�ϣ�������PRS/MT����˿ڳ�ͻ);
#define MIXER_MCU_STARTPORT             (u16)50000  // 50000��58000 �����MIX: 570 * 14 = 8980;   ���ж˿�: 20
#define PRS_MCU_STARTPORT               (u16)58000  // 58000��59000 �����PRS: 60  * 16 = 960;    ���ж˿�: 40
#define RESV_MCU_STARTPORT              (u16)59000  // 59000��61000 ΪMCU�ڲ��㲥Ĭ�϶˿�: 10 * 128 = 1280;   ���ж˿�: 720
													// 61000��65530 ������ն�: 10 * 448 = 4480;  ���ж˿�: 50
//�ն�mcu��Ĭ����ʼ�˿�
#define MT_MCU_STARTPORT                (u16)61000
//#define MT_MCU_STARTPORT                (u16)21000

//����mcu��˿ڷ�����
#define BAS_MCU_PORTSPAN               (u16)(8 * PORTSPAN)/*(5 * PORTSPAN)*/
#define VMP_MCU_PORTSPAN               (u16)(4 * PORTSPAN)/*(2 * PORTSPAN)*/
#define MPW_MCU_PORTSPAN               (u16)(2 * PORTSPAN)
#define PRS_MCU_PORTSPAN               (u16)(6 * PORTSPAN)   
#define MIXER_MCU_PORTSPAN             (u16)(57 * PORTSPAN)
#define REC_MCU_PORTSPAN               (u16)(32 * PORTSPAN)
#define HDU_MCU_PORTSPAN               (u16)(2 * PORTSPAN)

// �鲥��ַ����ʼ/����IP��
#define MULTICAST_IP_START              ntohl(inet_addr("225.0.0.0"))
#define MULTICAST_IP_END                ntohl(inet_addr("239.255.255.255"))
// �鲥��ַ����Ҫ������IP��
#define MULTICAST_IP_RESV_START         ntohl(inet_addr("231.255.255.255"))
#define MULTICAST_IP_RESV_END           ntohl(inet_addr("233.0.0.0"))
// Ĭ���鲥�˿�
#define MULTICAST_DEFPORT               (u16)60100

#define MAXBITRATE_MTSEND_INVMP         (u16)4032   //����ϳ�ʱ�ն����������(4096-64)

//����telnet�˿ڶ���
#define BRD_TELNET_PORT                 2500

//mcu telnet �˿ڶ���
#define MCU_TELNET_PORT                 2500

// ����Linux��inet_addrʱ���� "0"��Ϊ�Ǵ����ַ��������Ҫ����һ��
// ��������Linux��صĵ�ַת��ʹ�ñ��ꡣ
// ����Ҫ���ַ�����\0��β
#define INET_ADDR( szAddr )   ( strncmp(szAddr, "0", strlen(szAddr)) == 0 ? 0 : inet_addr(szAddr) )

//�û�����չ
#define MAXNUM_USRGRP                   32
#define MAXNUM_GRPUSRNUM                MAX_USERNUM
#define MAXNUM_IPSEG                    3

//����û�����
#define MAXNUM_USRNUM                   MAX_USERNUM

// �Ϸ�����ID�� 1 - MAXNUM_USRGRP���Լ� USRGRPID_SADMIN
#define USRGRPID_INVALID                (u8)0
#define USRGRPID_SADMIN                 (u8)0xFF

//MCU����Ӧ��OSP��ʼ��Ȩ����
#define MCU_TEL_USRNAME                 "admin"
#define MCU_TEL_PWD                     "admin"


//NPlus��Mcs����ĺ꣬Ϊ�˴�����ֵ
#define NPLUS_NONE                      (u8)200    //��NPlusģʽ

#define NPLUS_BAKCLIENT_IDLE            (u8)201     //N�� - ����״̬
#define NPLUS_BAKCLIENT_MSGLEN_ERR      (u8)202     //N�� - ���ӱ��ݶ�ʧ�ܣ���Ϣ�������ʾΪδ֪����
#define NPLUS_BAKCLIENT_CAP_ERR         (u8)203     //N�� - ���ӱ��ݶ�ʧ�ܣ����ݶ���������֧��
#define NPLUS_BAKCLIENT_OVERLOAD        (u8)204     //N�� - ���ӱ��ݶ�ʧ�ܣ����ݶ˱�����������
#define NPLUS_BAKCLIENT_ENV_UNMATCHED   (u8)205     //N�� - ���ӱ��ݶ�ʧ�ܣ����ݶ�Ϊ8000B����֧�ֶԱ���KDV8000�ı���; �� ���ݶ�Ϊ8000C �� ����Ϊ8000C �� ���߾�Ϊ8000C�����ܹ��ɱ���
#define NPLUS_BAKCLIENT_CONNECT_MASTER  (u8)206     //N�� - ���ӱ��ݶ�ʧ�ܣ����ݶ�Ϊ����MCU �� ��N+1ģʽ��MCU
#define NPLUS_BAKCLIENT_CONNECT         (u8)210     //N�� - �����ӷ�����

#define NPLUS_BAKSERVER_IDLE            (u8)211     //���ݶ� - ����״̬
#define NPLUS_BAKSERVER_SWITCHED        (u8)212     //���ݶ� - ���л�
#define NPLUS_BAKSERVER_SWITCHERR       (u8)213     //���ݶ� - �л�ʧ��

//8000B�����������⴦�� �궨��
#define MAXNUM_MIX_SINGLE_MP3           (u8)32      //MP3����(���ƺ�����)��������
#define MAXNUM_MIX_MULTI_MP3            (u8)8       //MP3����(���ƺ�����)������(VMP��BAS)�쿪����
#define MAXNUM_MIX_SINGLE_G729          (u8)10      //G729����(���ƺ�����)��������
#define MAXNUM_MIX_MULTI_G729           (u8)4       //G729����(���ƺ�����)������(VMP��BAS)�쿪����
#define MAXNUM_VAC_SINGLE_MP3           (u8)32      //MP3��VAC��������
#define MAXNUM_VAC_MULTI_MP3            (u8)16      //MP3��VAC������(BAS)�쿪����
#define MAXNUM_VAC_SINGLE_G729          (u8)16      //G729��VAC��������
#define MAXNUM_VAC_MULTI_G729           (u8)4       //G729��VAC������(BAS)�쿪����

//����ģʽ�궨��
#define ROLLCALL_MODE_NONE              (u8)0       //�ǵ���״̬
#define ROLLCALL_MODE_VMP               (u8)1       //VMPģʽ�������˱������˻����������˿����ǵ�VMP
#define ROLLCALL_MODE_CALLER            (u8)2       //CALLERģʽ�������˿��������ˣ������˿�������
#define ROLLCALL_MODE_CALLEE            (u8)3       //CALLEEģʽ���������˿������ˣ������˿���������

//mcu��mcs�Ự�汾���û��������ʱ��֤���޸����ݽṹӰ��mcs��mcu����ʱ��ֵ��1��45����4.0R5�汾��01����ÿ���޸İ汾��
#define MCUMCS_VER                      (u16)46005  //temperary

// zw [06/27/2008] AAC LC����
#define AAC_SAMPLE_FRQ_8                (u8)1
#define AAC_SAMPLE_FRQ_11               (u8)2
#define AAC_SAMPLE_FRQ_12               (u8)3
#define AAC_SAMPLE_FRQ_16               (u8)4
#define AAC_SAMPLE_FRQ_22               (u8)5
#define AAC_SAMPLE_FRQ_24               (u8)6
#define AAC_SAMPLE_FRQ_32               (u8)7
#define AAC_SAMPLE_FRQ_44               (u8)8
#define AAC_SAMPLE_FRQ_48               (u8)9
#define AAC_SAMPLE_FRQ_64               (u8)10
#define AAC_SAMPLE_FRQ_88               (u8)11
#define AAC_SAMPLE_FRQ_96               (u8)12

#define AAC_CHNL_TYPE_CUST              (u8)11
#define AAC_CHNL_TYPE_SINGLE            (u8)1
#define AAC_CHNL_TYPE_DOUBLE            (u8)2
#define AAC_CHNL_TYPE_3                 (u8)3
#define AAC_CHNL_TYPE_4                 (u8)4
#define AAC_CHNL_TYPE_5                 (u8)5
#define AAC_CHNL_TYPE_5P1               (u8)51
#define AAC_CHNL_TYPE_7P1               (u8)71

#define AAC_MAX_FRM_NUM                 1


// xliang [11/28/2008] vmpͨ����Ŀ FIXME
#define MAX_SVMP_HDCHNNLNUM				(u8)3		//
#define MAX_SVMP_4CIFCHNNLNUM			(u8)16
#define MAX_SVMP_CIFCHNNLNUM			(u8)12

// xliang [11/28/2008] vmp ��Ա�漰���ȼ������� -�ݲ���
#define VMPMEMBER_NORMAL				(u8)1	//��ͨMT
#define VMPMEMBER_BESELECTED			(u8)2	//��ѡ��
#define VMPMEMBER_NONEKEDA				(u8)3	//�ǿƴ�
#define VMPMEMBER_SPEAKER				(u8)4	//������

// xliang [12/23/2008] vmp������ѯʱ��T������
#define VMP_BATCHPOLL_TMAX				(u32)(300*1000)
#define VMP_BATCHPOLL_TMIN				(u32)(60*1000)

//4.6�¼Ӱ汾  jlb
//HDU ����ӿ�
#define HDU_OUTPUT_YPbPr   (u8)0    
#define HDU_OUTPUT_VGA     (u8)1 

#define HDU_VOLUME_DEFAULT (u8)24

//���ű���
#define HDU_ZOOMRATE_4_3   (u8)0  
#define HDU_ZOOMRATE_16_9  (u8)1

//HDU �����ʽ
#define HDU_YPbPr_1080P_24fps         (u8)0
#define HDU_YPbPr_1080P_25fps         (u8)1
#define HDU_YPbPr_1080P_30fps         (u8)2
#define HDU_YPbPr_1080P_50fps         (u8)3
#define HDU_YPbPr_1080P_60fps         (u8)4
#define HDU_YPbPr_1080i_50HZ          (u8)5    //(Ĭ��)
#define HDU_YPbPr_1080i_60HZ          (u8)6
#define HDU_YPbPr_720P_60fps          (u8)7
#define HDU_YPbPr_576i_50HZ           (u8)8
#define HDU_YPbPr_480i_60HZ           (u8)9

#define HDU_VGA_SXGA_60HZ            (u8)10
#define HDU_VGA_XGA_60HZ             (u8)11     //(Ĭ��)
#define HDU_VGA_XGA_75HZ             (u8)12
#define HDU_VGA_SVGA_60HZ            (u8)13
#define HDU_VGA_SVGA_75HZ            (u8)14
#define HDU_VGA_VGA_60HZ             (u8)15
#define HDU_VGA_VGA_75HZ             (u8)16
#define HDU_VGA_SXGA_75HZ            (u8)17


//�鲥������ʽ
#define CAST_UNI					 (u8)1
#define CAST_FST				     (u8)2
#define CAST_SEC				     (u8)3
#define CAST_DST				     (u8)4

//VCS֧�����õ�����û���
#define MAXNUM_VCSUSERNUM               MAX_USERNUM

#define MAXNUM_SAT_MODEM			 (u8)16
#endif


