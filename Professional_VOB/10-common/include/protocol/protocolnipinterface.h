/*******************************************************************************
 *  ģ����   :                                                                 *
 *  �ļ���   : protocolnipinterface.h                                          *
 *  ����ļ� :                                                                 *
 *  ʵ�ֹ��� : Э�����ṩ�Ķ�NIP�ķ�װ�㣬��ָ�뺯������ʽ�ṩ                 *
 *	���øÿ��ÿ������APP����ʵ������ĺ���                                    *
 *  ����     : ��С��                                                          *
 *  �汾     : V1.0  Copyright(c) 1997-2005 KDC, All rights reserved.          *
 *                                                                             *
 *    =======================================================================  *
 *  �޸ļ�¼:                                                                  *
 *    ��  ��      �汾        �޸���      �޸�����                             *
 *  28/5/2010     4.0         ��С��      ����                                 *
 *                                                                             *
 *******************************************************************************/

#ifndef protocolnipinterface_h__
#define protocolnipinterface_h__

#include "osp.h"

//ע��GK��Ҫʹ�õĵײ�⺯��
void InitGKNipFun();

extern s8* ProtocolGKGetConfigPath();

/////GKLIB�еĺ���, ʹ�õĻ�����Ҫ����kdvlib.lib
/*====================================================================
  �� �� ���� ProtocolBrdGetEthState
  ��    �ܣ� 
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� byIndex: ���������� ��ʱ������
			 dwip	: ���ڵ�IP�� ��ʱ������
  �� �� ֵ�� BOOL ��ǰ������״̬���˺���Ŀǰ�㷵��TRUE
  --------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2010/5/28     4.0		    ��С��                   ����
======================================================================*/
extern BOOL32 ProtocolBrdGetEthState(u8 byIndex, u32 dwip);


/*====================================================================
  �� �� ���� ProtocolSetSecondIpAddress
  ��    �ܣ� �趨���ڵڶ���Ip���������û�е�һ��IP��������óɵ�һ��IP
             ���óɹ��󣬻���е�Ʋ��� BrdLedStatusSet( LED_SYS_LINK, BRD_LED_ON );
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� byIndex:  ��������
			 dwIp	:  ��Ҫ���õ�IP  
			 dwMask	:  ��Ӧ������
			 bIsUseSecondIp:  ���Σ� ��ʾ�Ƿ��������ڵĵڶ���IP�ɹ���������ɹ���ΪFALSE
  �� �� ֵ�� BOOL 
  --------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2010/5/28     4.0		    ��С��                   ����
======================================================================*/
extern BOOL32 ProtocolSetSecondIpAddress(u8 byIndex, u32 dwIp, u32 dwMask, BOOL32& bIsUseSecondIp);

/*====================================================================
  �� �� ���� ProtocolDeleteSecondIpAddress
  ��    �ܣ� ɾ�����ڵڶ���IP���ɹ�֮�����йصƲ��� BrdLedStatusSet( LED_SYS_LINK, BRD_LED_OFF );
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� 
  �� �� ֵ�� BOOL 
  --------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2010/5/28     4.0		    ��С��                   ����
======================================================================*/
extern BOOL32 ProtocolDeleteSecondIpAddress(u8 byIndex, u32 dwIp, u32 dwMask, BOOL32 bIsSecond);



extern void	ProtocolBrdHwReset(void);
extern BOOL32	ProtocolIsMdscORHdsc();
extern u32		ProtocolBrdGetEthParam(u8 byIndex);






//pxyserver�еĺ�����ʹ�õĻ���Ҫ����pxyserver

//ע��pxy��Ҫʹ�õĵײ�⺯��
void InitPxyNipFun();

/* ����·�ɲ����ṹ */
typedef struct{
    u32 dwDesIpNet;      /* Ŀ�������������ֽ���	*/
    u32 dwDesIpMask;     /* ���룬�����ֽ���	*/
    u32 dwGwIpAdrs;      /* ����ip��ַ�������ֽ���*/
    u32 dwRoutePri;		/* ·�����ȼ�(1-255)��Ĭ��Ϊ0*/
}TPxyIpRouteParam;//TBrdIpRouteParam;


extern char* ProtocolPxyGetConfigPath(void);

extern BOOL32 ProtocolIsInSameSubnet(u32 dwSrcIP);
extern int ProtocolPxyAddOneIpRoute(TPxyIpRouteParam *ptBrdIpRouteParam);
extern int ProtocolPxyDelOneIpRoute(TPxyIpRouteParam *ptBrdIpRouteParam);
extern int ProtocolPxySetRunStatusLed();
extern int ProtocolGkSetRunStatusLed();


#endif//protocolnipinterface_h__


