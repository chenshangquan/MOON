/*****************************************************************************
   ģ����      : MCU��T120����
   �ļ���      : evmcudcs.h
   ����ļ�    : 
   �ļ�ʵ�ֹ���: MCU��DCS�ӿ���Ϣ����
                 *_REQ: ��Ӧ������
				 *_ACK, *_NACK: ����֮��
				 *_CMD: ����Ӧ������
				 *_NOTIF: ״̬֪ͨ
   ����        : �ű���
   �汾        : V4.0  Copyright(C) 2005-2008 KDC, All rights reserved.
-----------------------------------------------------------------------------
   �޸ļ�¼:
   ��  ��      �汾        �޸���      �޸�����
   2005/12/09  4.0         �ű���      ����
******************************************************************************/
#ifndef _EV_MCUDCS_H_
#define _EV_MCUDCS_H_

#include "osp.h"
#include "eventid.h"

//ע��Ϊ��֤������ȷ���У����гɹ���ʧ��Ӧ���ԭ��Ϣ�ŷֱ��1��2

/**********************************************************
 ����ΪMCU(�Ự)��DCSҵ��ӿ� (38301-38500)
**********************************************************/

// ---MCU_DCS CONNECT (38301-38310)---
//MCU������DCServer������MCU->DCS
OSPEVENT( MCU_DCS_CONNECT_REQ,			EV_DCSMCU_BGN );	
//DCS��MCU�����ɹ���DCS->MCU
OSPEVENT( DCS_MCU_CONNECT_ACK,			EV_DCSMCU_BGN + 1 );
//DCS�ܾ�������DCS->MCU������Ϣ��
OSPEVENT( DCS_MCU_CONNECT_NACK,			EV_DCSMCU_BGN + 2 );

//MCU������DCServer������MCU->DCC
OSPEVENT( MCU_DCS_DISCONNECT_REQ,		EV_DCSMCU_BGN + 4 );
//DCS��MCU�����ɹ���DCS->MCU������Ϣ��
OSPEVENT( DCS_MCU_DISCONNECT_ACK,		EV_DCSMCU_BGN + 5 );
//DCS�ܾ�������DCS->MCU������Ϣ��
OSPEVENT( DCS_MCU_DISCONNECT_NACK,		EV_DCSMCU_BGN + 6);

// ---REGISTER (38311-38320)---
//DCS��MCUע������, DCS->MCU, ��Ϣ��ΪCDcsMcuRegReqPDU
OSPEVENT( DCS_MCU_REG_REQ,				EV_DCSMCU_BGN + 10 );
//MCU��DCSע�����Ӧ��, MCU->DCS, ��Ϣ��ΪCMcuDcsRegAckPDU
OSPEVENT( MCU_DCS_REG_ACK,				EV_DCSMCU_BGN + 11 );
//MCU��DCSע��ܾ�Ӧ��, MCU->DCS, ��Ϣ��ΪCMcuDcsRegNackPDU
OSPEVENT( MCU_DCS_REG_NACK,				EV_DCSMCU_BGN + 12 );

// ---MCU_DCS CONF (38321-38340)---
//MCU����DCServer�������飬MCU->DCS����Ϣ��ΪCMcuDcsCreateConfReqPDU
OSPEVENT( MCU_DCS_CREATECONF_REQ,		EV_DCSMCU_BGN +	20 );
//DCS���ʹ�������ͬ��Ӧ��DCS->MCU����Ϣ��ΪCDcsMcuCreateConfAckPDU
OSPEVENT( DCS_MCU_CREATECONF_ACK,		EV_DCSMCU_BGN + 21 );
//DCS�ܾ��������飬DCS->MCU����Ϣ��ΪCDcsMcuCreateConfNackPDU
OSPEVENT( DCS_MCU_CREATECONF_NACK,		EV_DCSMCU_BGN + 22 );
//DCS�������ͻ���֪ͨ,DCS->MCU,��Ϣ��ΪCDcsMcuCreateConfNotifyPDU
OSPEVENT( DCS_MCU_CONFCREATED_NOTIF,	EV_DCSMCU_BGN +	23 );

//MCU����DCServer�������飬MCU->DCS����Ϣ��ΪCMcuDcsReleaseConfReqPDU
OSPEVENT( MCU_DCS_RELEASECONF_REQ,		EV_DCSMCU_BGN +	24 );
//DCS���ͽ�������ͬ��Ӧ��DCS->MCU����Ϣ��ΪCDcsMcuReleaseConfAckPDU
OSPEVENT( DCS_MCU_RELEASECONF_ACK,		EV_DCSMCU_BGN + 25 );
//DCS�ܾ��������飬DCS->MCU����Ϣ��ΪCDcsMcuReleaseConfNackPDU
OSPEVENT( DCS_MCU_RELEASECONF_NACK,		EV_DCSMCU_BGN + 26 );
//DCS�������ͻ������֪ͨ,DCS->MCU,��Ϣ��ΪCDcsMcuReleaseConfNotifyPDU
OSPEVENT( DCS_MCU_CONFRELEASED_NOTIF,	EV_DCSMCU_BGN +	27 );

// ---MCU_DCS MT (38341-38350)---
//MCU����DCServer�����նˣ�MCU->DCS����Ϣ��ΪCMcuDcsAddMtReqPDU
OSPEVENT( MCU_DCS_ADDMT_REQ,			EV_DCSMCU_BGN +	40 );
//DCS���������ն�ͬ��Ӧ��DCS->MCU����Ϣ��ΪCDcsMcuAddMtAckPDU
OSPEVENT( DCS_MCU_ADDMT_ACK,			EV_DCSMCU_BGN + 41 );
//DCS�ܾ������նˣ�DCS->MCU����Ϣ��ΪCDcsMcuAddMtNackPDU
OSPEVENT( DCS_MCU_ADDMT_NACK,			EV_DCSMCU_BGN + 42 );
//DCS�ն˼���֪ͨ��DCS->MCU����Ϣ��ΪCDcsMcuMtMtOnlineNotifyPDU
OSPEVENT( DCS_MCU_MTJOINED_NOTIF,		EV_DCSMCU_BGN + 43 );


//MCU����DCServerɾ���նˣ�MCU->DCS����Ϣ��ΪCMcuDcsDelMtReqPDU
OSPEVENT( MCU_DCS_DELMT_REQ,			EV_DCSMCU_BGN +	44 );
//DCS����ɾ���ն�ͬ��Ӧ��DCS->MCU����Ϣ��ΪCDcsMcuDelMtAckPDU
OSPEVENT( DCS_MCU_DELMT_ACK,			EV_DCSMCU_BGN + 45 );
//DCS�ܾ�ɾ���նˣ�DCS->MCU����Ϣ��ΪCDcsMcuDelMtNackPDU
OSPEVENT( DCS_MCU_DELMT_NACK,			EV_DCSMCU_BGN + 46 );
//DCS�ն����(����, ���Ǳ�ɾ��)֪ͨ��DCS->MCU����Ϣ��ΪCDcsMcuMtMtOfflineNotifyPDU
OSPEVENT( DCS_MCU_MTLEFT_NOTIF,			EV_DCSMCU_BGN + 47 );


// ---MCU_DCS OTHER (38351-38360)---
//MCU����DCS��������Ӧ�÷���
OSPEVENT( MCU_DCS_STARTT120_REQ,		EV_DCSMCU_BGN + 50 );
//DCSͬ�⿪������Ӧ�÷���Ӧ��
OSPEVENT( DCS_MCU_STARTT120_ACK,		EV_DCSMCU_BGN + 51 );
//DCS�ܾ���������Ӧ�÷���Ӧ��
OSPEVENT( DCS_MCU_STARTT120_NACK,		EV_DCSMCU_BGN + 52 );
//DCS��������Ӧ�÷���֪ͨ
OSPEVENT( DCS_MCU_STARTT120_NOTIF,		EV_DCSMCU_BGN + 53 );

//DCS����MCU������״̬: CDcsMcuGetmsstatusReqPdu
OSPEVENT( DCS_MCU_GETMSSTATUS_REQ,		EV_DCSMCU_BGN + 54 );
//MCUӦ������״̬: CMcuDcsGetmsstatusAckPdu
OSPEVENT( MCU_DCS_GETMSSTATUS_ACK,		EV_DCSMCU_BGN + 55 );
//MCU�ܾ�Ӧ������״̬: CMcuDcsGetmsstatusNackPdu
OSPEVENT( MCU_DCS_GETMSSTATUS_NACK,		EV_DCSMCU_BGN + 56 );


// ---Reserved (38371-38490) total 130---

// ---TEST (38491-38500)---
//MCU����DCServer�����նˣ�MCU->DCS����Ϣ��ΪCMcuDcsAddMtReqPDU
OSPEVENT( TEST_MCU_DCS_DELMT_REQ,		EV_DCSMCU_BGN + 90 );
//MCU����DCServerɾ���նˣ�MCU->DCS����Ϣ��ΪCMcuDcsDelMtReqPDU
OSPEVENT( TEST_MCU_DCS_ADDMT_REQ,		EV_DCSMCU_BGN + 91 );


#endif /* _EV_MCUDCS_H_ */
