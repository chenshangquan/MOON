/*****************************************************************************
ģ����      : mcu
�ļ���      : drvMpcControl.h
����ļ�    : drvMpcControl.c
�ļ�ʵ�ֹ���:  �ڲ�ʹ�õ�һЩ�궨��ͺ�������.
����        : �ŷ���
�汾        : V1.0  Copyright(C) 2003-2005 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2003/8/19   01a         �ŷ���      ����	
******************************************************************************/
#ifndef __INCdrvMpcControlh
#define __INCdrvMpcControlh

#ifdef __cplusplus
extern "C" {
#endif

#include "time.h"
#include "timers.h"

/* FPGAд�Ĵ���BITλ����  */
#define FPGA_WD_REG0       ((UINT8)0X00) 
#define FPGA_WD_REG1       ((UINT8)0X01)
#define FPGA_WD_REG2       ((UINT8)0X02)

#define FPGA_REG_WDIN      ((UINT8)0x01) 
#define FPGA_REG_WDEN      ((UINT8)0X80) 
#define FPGA_WR_REG_MS     ((UINT8)0X04)

#define FPGA_REG_MSEL      ((UINT8)0X01) 
#define FPGA_REG_FSEL      ((UINT8)0X02) 
#define FPGA_REG_FS1       ((UINT8)0X04) 
#define FPGA_REG_FS2       ((UINT8)0X08) 

#define FPGA_REG_DRST      ((UINT8)0X01) 
#define FPGA_REG_MRST      ((UINT8)0X02) 
#define FPGA_REG_HIRSTO    ((UINT8)0X04) 
#define FPGA_REG_HSRSTEN   ((UINT8)0X08) 


/*==================================��̫��ģ������===============================*/
/* �����豸����netEquipUnit�궨�� */
#define NETEQUIP_IS_ETH1    1    /* ��̫��1�� ��Ӧ8265��FCC2 �� x86�ϵ��������� */
#define NETEQUIP_IS_ETH2    2    /* ��̫��2�� ��Ӧ8265��FCC1 �� x86�ϵ���������*/
#define NETEQUIP_IS_ETH3    3    /* ��̫��3�� ��Ӧ8265��SCC1 */
#define NETEQUIP_IS_IPOH    4    /* IPOH  ��  ��Ӧ8265��MCC1 */


/* MPC�幦�����ò��� 444444444444444444444444444444444444444444444444444 */


/* �������� */
STATUS BrdMPCSetNetSyncMode(UINT8 mode);   /* ���໷��ͬ��ģʽѡ������ */
STATUS BrdMPCResetSDH(void);               /* ��ģ�鸴λ */
STATUS BrdMPCReSetAnotherMPC(void);        /* ��λ�Զ�������� */
STATUS BrdMPCOppReSetDisable (void);       /* ��ֹ�Զ����������λ��������� */
STATUS BrdMPCOppReSetEnable (void);        /* ����Զ����������λ��������� */
void BrdMpcWatchdogMode(UINT8 data);
void BrdMpcFeedDog(void);
STATUS BrdMPCLedBoardSpeakerSet(UINT8 state);
STATUS BrdMPCLedBoardLedSet(UINT8 LedID, UINT8 state);
STATUS BrdTimeGet( struct tm* pGettm );        /* ��ȡRTCʱ�� */
STATUS BrdTimeSet( struct tm* pSettm );        /* ����RTC��ϵͳʱ�� */ 

/*����������IP��ַ��MAC��ַ����������*/
STATUS ethernetSet
    (
    int netEquipUnit,	 /* ���� */
    char *pIpAddrStr,    /* ip��ַ ��:"100.1.1.1" */
    int   netmask  ,     /* �������� ����:0xff000000 ;0 = �Զ�ʶ�� */
    char *pEtherMacAddr  /* mac��ַ��null -> ���ı䵱ǰֵ 
                         ����unsigned char sysFccEnetAddr [6] = {0x08, 0x00, 0x33, 0x02, 0x02, 0x51};*/
    );



/*==============================��ͬ��=============================*/  
/* ͬ��ģʽ�궨�� */
#define SYNC_MODE_TRACK_2M_SLAVE  4   /* ����ģʽ����Ϊ�¼�MCUӦ����Ϊ��ģʽ������DT���Ĵ�2Mʱ�� */

/* �������� */
void BrdNetSyncModeSet(UINT8 mode);                 /* ��ͬ��ģʽ����
                                                       �������: ��ͬ��ģʽ�궨�� */
void BrdNetSyncSrcSelect(UINT8 dtiNo, UINT8 E1No);  /* ��ͬ��Դѡ��
                                                       �������: dtiNo ��Χ0~14��E1No��Χ0~7 */
int BrdNetSyncLock(void);                           /* �����ͬ������ģʽʱ�Ƿ�����ʱ��Դ
                                                       ���������#define SYNC_CLOCK_UNLOCK 0    ����ģʽʱʱ��δ���� 
                                                                #define SYNC_CLOCK_LOCK   1    ����ģʽʱʱ�������ɹ� 
                                                       ע��ֻ�е�ǰMCU��ɸ���ģʽʱ����Ч��������ʱ
                                                       MCU��������κ�ʱ�ӣ����ú�������Ч�ģ���Զ����δ���� */





#ifdef __cplusplus
}
#endif

#endif /* __INCdrvMpcPatchh */