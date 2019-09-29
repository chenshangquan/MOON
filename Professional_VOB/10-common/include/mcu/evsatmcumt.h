/*****************************************************************************
   ģ����      : ����  �նˣ�MCU ͨ����Ϣ����
   �ļ���      : evsatmcumt.h
   ����ļ�    : evsatmcumt.cpp
   �ļ�����    : 
   ����        : ������
   �汾        : V1.0  Copyright(C) 2001-2002 KDC, All rights reserved.
-----------------------------------------------------------------------------
   �޸ļ�¼:
   ��  ��      �汾        �޸���      �޸�����
   2004/11/02  1.0         ������      ����
******************************************************************************/

#ifndef _EVENT_SATELLITE_MCU_MT_H_
#define _EVENT_SATELLITE_MCU_MT_H_

#include "osp.h"
#include "eventid.h"

//ע��Ϊ��֤������ȷ���У����гɹ���ʧ��Ӧ���ԭ��Ϣ�ŷֱ��1��2

/**********************************************************
 ����ΪMCU���ն�֮��ҵ��ӿڣ�������MCU��MT�����ڲ���Ϣ��25001-26000��
**********************************************************/

/////////////////////////////////////////////////
//MCU���ն�֮�����Ӳ���---�ն˲�����

//�ն��ϵ�����ϼ�MCU����ĵǼ�����MT->MCU����Ϣ��Ϊ�ṹTMt
OSPEVENT( MT_MCU_REG_REQ,			EV_MCUMT_BGN );
//MCU׼��Ӧ��MCU->MT������Ϣ��
OSPEVENT( MCU_MT_REG_ACK,			EV_MCUMT_BGN + 1 );
//MCU�ܾ�Ӧ��MCU->MT������Ϣ��
OSPEVENT( MCU_MT_REG_NACK,			EV_MCUMT_BGN + 2 );

//�ն˷���MCU��ѯȫ��MCU��������MT->MCU����Ϣ��Ϊ�ṹTMt
OSPEVENT( EV_SAT_MCUMT_TOPO_IND,	EV_MCUMT_BGN + 4 );	
OSPEVENT( MCU_MT_KEY_NOTIF,			EV_MCUMT_BGN + 6 ); 
//�ն�������н���������֪ͨmcu���Խ��к�̲�������Ϣ��ΪTMt
OSPEVENT( MT_MCU_READY_NOTIF,		EV_MCUMT_BGN + 8 );
//���ն�����I֡
OSPEVENT( MCU_MT_SENDIFRAME_NOTIF,		EV_MCUMT_BGN + 10 );
/////////////////////////////////////////////////
//MCU�����ն˼���ָ����������MCU->MT����Ϣ��Ϊ�ṹTMt
OSPEVENT( MCU_MT_INVITEMT_REQ,		EV_MCUMT_BGN + 100 );
//MT����Ӧ��MT->MCU����Ϣ��Ϊ�ṹTMt
OSPEVENT( MT_MCU_INVITEMT_ACK,		EV_MCUMT_BGN + 101 );
//MT�ܾ�Ӧ��MT->MCU����Ϣ��Ϊ�ṹTMt
OSPEVENT( MT_MCU_INVITEMT_NACK,		EV_MCUMT_BGN + 102 );

//MCUǿ���ն��˳��������MCU->MT������Ϣ��
OSPEVENT( MCU_MT_DELMT_CMD,			EV_MCUMT_BGN + 108 );

//MCU����MT�Ĵ��߼�ͨ������MCU->MT����Ϣ��Ϊ�ṹTMt+TLogicalChannel+TMt
OSPEVENT( MCU_MT_OPENLOGICCHNNL_REQ,	EV_MCUMT_BGN + 120 );
//�ն˷���MCU�ĳɹ�Ӧ��MT->MCU����Ϣ��Ϊ�ṹTMt+TLogicalChannel+TMt
OSPEVENT( MT_MCU_OPENLOGICCHNNL_ACK,	EV_MCUMT_BGN + 121 );
//�ն˷���MCU��ʧ��Ӧ��MT->MCU����Ϣ��Ϊ�ṹTMt+TLogicalChannel+TMt
OSPEVENT( MT_MCU_OPENLOGICCHNNL_NACK,	EV_MCUMT_BGN + 122 );

//MT����MCU�Ĵ��߼�ͨ������MT->MCU����Ϣ��Ϊ�ṹTMt+TLogicalChannel
OSPEVENT( MT_MCU_OPENLOGICCHNNL_REQ,	EV_MCUMT_BGN + 124 );
//MCU�����ն˵ĳɹ�Ӧ��MCU->MT����Ϣ��Ϊ�ṹTMt+TLogicalChannel
OSPEVENT( MCU_MT_OPENLOGICCHNNL_ACK,	EV_MCUMT_BGN + 125 );
//MCU�����ն˵�ʧ��Ӧ��MCU->MT����Ϣ��Ϊ�ṹTMt+TLogicalChannel
OSPEVENT( MCU_MT_OPENLOGICCHNNL_NACK,	EV_MCUMT_BGN + 126 );

//MCU�����ն˵�������֪ͨ��MCU->MT����Ϣ��Ϊ�ṹTMt+TCapSupport
OSPEVENT( MCU_MT_CAPBILITYSET_NOTIF,	EV_MCUMT_BGN + 128 );
//�ն˷���MCU��������֪ͨ��MT->MCU����Ϣ��Ϊ�ṹTMt+TCapSupport
OSPEVENT( MT_MCU_CAPBILITYSET_NOTIF,	EV_MCUMT_BGN + 129 );

//�ն˷���MCU��������ϯ����MT->MCU����Ϣ��Ϊ�ṹTMt
OSPEVENT( MT_MCU_APPLYCHAIRMAN_REQ,		EV_MCUMT_BGN + 132 );
//֪ͨ��ϯ�ն����뷢������MCU->MT����Ϣ��Ϊ�ṹTMt
OSPEVENT( MCU_MT_APPLYCHAIRMAN_NOTIF,	EV_MCUMT_BGN + 135 );

//�ն˷���MCU�����뷢������MT->MCU����Ϣ��Ϊ�ṹTMt
OSPEVENT( MT_MCU_APPLYSPEAKER_CMD,		EV_MCUMT_BGN + 136 );
//֪ͨ��ϯ�ն����뷢������MCU->MT����Ϣ��Ϊ�ṹTMt
OSPEVENT( MCU_MT_APPLYSPEAKER_NOTIF,	EV_MCUMT_BGN + 137 );

//�ն˷���MCU�������˳���������MT->MCU����Ϣ��Ϊ�ṹTMt
OSPEVENT( MT_MCU_APPLYQUITCONF_CMD,		EV_MCUMT_BGN + 140 );
//֪ͨ��ϯ�ն��˳���������MCU->MT����Ϣ��Ϊ�ṹTMt
OSPEVENT( MCU_MT_APPLYQUITCONF_NOTIF,	EV_MCUMT_BGN + 141 );

//�ն˷���MCU�ļ�����������MT->MCU����Ϣ��Ϊ�ṹTMt
OSPEVENT( MT_MCU_APPLYJOINCONF_REQ,		EV_MCUMT_BGN + 144 );
//�ն˷���MCU�ļ�����������ɹ�Ӧ��MT->MCU����Ϣ��Ϊ�ṹTMt
OSPEVENT( MCU_MT_APPLYJOINCONF_ACK,		EV_MCUMT_BGN + 145 );
//�ն˷���MCU�ļ�����������ʧ��Ӧ��MT->MCU������Ϣ��
OSPEVENT( MCU_MT_APPLYJOINCONF_NACK,	EV_MCUMT_BGN + 146 );
//MCU֪ͨ��ϯ�ն����ն����������飬MCU->MT����Ϣ��Ϊ�ṹTMt
OSPEVENT( MCU_MT_APPLYJOINCONF_NOTIF,	EV_MCUMT_BGN + 147 );

//��ϯ�ն˷���MCU�������ն�����MT->MCU����Ϣ��Ϊ�ṹTMt
OSPEVENT( MT_MCU_ADDMT_REQ,				EV_MCUMT_BGN + 152 );
//MCU�صĳɹ�Ӧ��MCU->MT��TMt
OSPEVENT( MCU_MT_ADDMT_ACK,				EV_MCUMT_BGN + 153 );
//MCU�ص�ʧ��Ӧ��MCU->MT��TMt
OSPEVENT( MCU_MT_ADDMT_NACK,			EV_MCUMT_BGN + 154 );
OSPEVENT( MT_MCU_ADDMT_CMD,				EV_MCUMT_BGN + 155 );
//��ϯ�ն˷���MCU��ǿ���ն��˳�����MT->MCU����Ϣ��Ϊ�ṹTMt
OSPEVENT( MT_MCU_DELMT_REQ,				EV_MCUMT_BGN + 156 );
//MCU�صĳɹ�Ӧ��MCU->MT��TMt
OSPEVENT( MCU_MT_DELMT_ACK,				EV_MCUMT_BGN + 157 );
//MCU�ص�ʧ��Ӧ��MCU->MT��TMt
OSPEVENT( MCU_MT_DELMT_NACK,			EV_MCUMT_BGN + 158 );
OSPEVENT( MT_MCU_DELMT_CMD,				EV_MCUMT_BGN + 159 );

//��ϯ�ն˷���MCU����ֹ��������MT->MCU������Ϣ��
OSPEVENT( MT_MCU_DROPCONF_CMD,			EV_MCUMT_BGN + 160 );

//��ϯ�ն˷���MCU��ָ����ϯ����MT->MCU����Ϣ��Ϊ�ṹTMt����������ϯ
OSPEVENT( MT_MCU_SPECCHAIRMAN_REQ,		EV_MCUMT_BGN + 164 );
//MCU�صĳɹ�Ӧ��MCU->MT������Ϣ��
OSPEVENT( MCU_MT_SPECCHAIRMAN_ACK,		EV_MCUMT_BGN + 165 );
//MCU�ص�ʧ��Ӧ��MCU->MT������Ϣ��
OSPEVENT( MCU_MT_SPECCHAIRMAN_NACK,		EV_MCUMT_BGN + 166 );

//��ϯ�ն˷���MCU��ָ������������MT->MCU����Ϣ��Ϊ�ṹTMt�������·�����
OSPEVENT( MT_MCU_SPECSPEAKER_REQ,		EV_MCUMT_BGN + 168 );
//MCU�صĳɹ�Ӧ��MCU->MT������Ϣ��
OSPEVENT( MCU_MT_SPECSPEAKER_ACK,		EV_MCUMT_BGN + 169 );
//MCU�ص�ʧ��Ӧ��MCU->MT������Ϣ��
OSPEVENT( MCU_MT_SPECSPEAKER_NACK,		EV_MCUMT_BGN + 170 );

//��ϯ�ն˷���MCU��ȡ����ϯ����MT->MCU������Ϣ��
OSPEVENT( MT_MCU_CANCELCHAIRMAN_CMD,	EV_MCUMT_BGN + 172 );

//��ϯ�ն˷���MCU��ȡ������������MT->MCU������Ϣ��
OSPEVENT( MT_MCU_CANCELSPEAKER_CMD,		EV_MCUMT_BGN + 176 );

//�г����л�����Ϣ��MT->MCU������Ϣ��
OSPEVENT( MT_MCU_CREATECONF_REQ,		EV_MCUMT_BGN + 180 );
//�г����л�����Ϣ�ɹ�Ӧ��MCU->MT������Ϣ��
OSPEVENT( MCU_MT_CREATECONF_ACK,		EV_MCUMT_BGN + 181 );
//�г����л�����Ϣʧ��Ӧ������Ϣ��
OSPEVENT( MCU_MT_CREATECONF_NACK,		EV_MCUMT_BGN + 182 );

//���ն˶���Ϣ֪ͨ��MCU->MT����Ϣ��Ϊ�ṹTMt+����Ϣ�ṹ
OSPEVENT( MCU_MT_SENDMSG_NOTIF,			EV_MCUMT_BGN + 184 );
//�ն˸�λ���MCU->MT����Ϣ��Ϊ�ṹTMt+���ֽ�
OSPEVENT( MCU_MT_RESETDECODER_CMD,		EV_MCUMT_BGN + 185 );
//�ն����ն˶���Ϣ���MT->MCU����Ϣ��Ϊ�ṹTMt(Դ)+TMt(Ŀ��)+����Ϣ�ṹ
//TMt: MCU���ն˺Ŷ�Ϊ0��ʾ�������л����նˣ�ֻ�ն˺�Ϊ0����MCU�������նˣ�����Ϊ0����ָ���ն�
OSPEVENT( MT_MCU_SENDMSG_CMD,			EV_MCUMT_BGN + 186 );
//�ն����������̨����Ϣ���MT->MCU����Ϣ��Ϊ�ṹTMt+����Ϣ�ṹ
OSPEVENT( MT_MCU_SENDMCMSG_CMD,			EV_MCUMT_BGN + 187 );

//��ʼ������MCU->MT������Ϣ��
OSPEVENT( MCU_MT_STARTMIX_CMD,			EV_MCUMT_BGN + 228 );
//ֹͣ������MCU->MT������Ϣ��
OSPEVENT( MCU_MT_STOPMIX_CMD,			EV_MCUMT_BGN + 229 );
//�����ն����� TBitRate
OSPEVENT( MCU_MT_SETBITRATE_CMD,			EV_MCUMT_BGN + 230 );

//���ն�����I֡
//OSPEVENT( MCU_MT_SENDIFRAME_NOTIF,			EV_MCUMT_BGN + 230 );

//��ϯ�ն�����MCU�����ն˾������ã�MT->MCU����Ϣ��Ϊ�ṹITSatMtId+cmd
//1��MUTE��2��NOTMUTE
OSPEVENT( MT_MCU_MTMUTE_CMD,		EV_MCUMT_BGN + 343 );
//��ϯ�ն�����MCU�����ն��������ã�MT->MCU����Ϣ��Ϊ�ṹITSatMtId+cmd
//1��MUTE��2��NOTMUTE
OSPEVENT( MT_MCU_MTDUMB_CMD,		EV_MCUMT_BGN + 345 );

/*******************************SPECIAL FOR SATELLATE MCU***********************/
//MCU���ն˵�����֪ͨ����Ϣ��TSatMtTopo����
OSPEVENT( MCU_MT_TOPO_NOTIF,								EV_MCUMT_BGN + 800 );
//MCU���ն˵Ļ����б�֪ͨ����Ϣ��u8����
OSPEVENT( MCU_MT_CONFLIST_NOTIF,							EV_MCUMT_BGN + 801 );
//MCU���ն˵��ն�״̬֪ͨ����Ϣ��CSatMtStatus
OSPEVENT( MCU_MT_MTSTATUS_NOTIF,							EV_MCUMT_BGN + 802 );
//MCU���ն˵Ļ���״̬֪ͨ����Ϣ��CSatConfInfo
OSPEVENT( MCU_MT_CONFSTATUS_NOTIF,							EV_MCUMT_BGN + 803 );

//�ն˷����渴�ϵĲ���
//�ն˿�ʼ��Ƶ��������,MT->MCU,��Ϣ��TVMPParam
OSPEVENT( MT_MCU_STARTVMP_CMD,								EV_MCUMT_BGN + 810 );
//�ն˽�����Ƶ��������,MT->MCU,��Ϣ���	
OSPEVENT( MT_MCU_STOPVMP_CMD ,								EV_MCUMT_BGN + 811 );
//�ն�����MCU�ı临�ϲ���,MT->MCU,��Ϣ��TVMPParam	
OSPEVENT( MT_MCU_CHANGEVMPPARAM_CMD,							EV_MCUMT_BGN + 812 );
//�ն�����MCU��ʼ�ѻ���ϳ�ͼ��㲥,MT->MCU,��Ϣ���
OSPEVENT( MT_MCU_STARTVMPBRDST_CMD,							EV_MCUMT_BGN + 813 );
//�������̨����MCUֹͣ�ѻ���ϳ�ͼ��㲥,MT->MCU,��Ϣ���
OSPEVENT( MT_MCU_STOPVMPBRDST_CMD,							EV_MCUMT_BGN + 814 );

//�ն˷����������
//�ն��������������MT->MCU,��Ϣ���
OSPEVENT( MT_MCU_STARTMIX_CMD,							EV_MCUMT_BGN + 820 );
//�ն�ֹͣ����,MT->MCU,��Ϣ���
OSPEVENT( MT_MCU_STOPMIX_CMD,							EV_MCUMT_BGN + 821 );

//����ǩ��
//MCUҪ���ն�ǩ��,MCU->MT,��Ϣ��Ϊ��
OSPEVENT( MCU_MT_SIGNNOW_CMD,							EV_MCUMT_BGN + 830);
//�ն�ǩ��,MT->MCU,��Ϣ��ΪTMt
OSPEVENT( MT_MCU_SIGNNOW_NOTIF,							EV_MCUMT_BGN + 831);
//�ն�ָ�����鷢���˼����MT->MCU,��Ϣ��Ϊu8(��Ϊ��λ)
OSPEVENT( MT_MCU_SPECSPEAKERINTERV_CMD,					EV_MCUMT_BGN + 840);
//MT��MCU����ͷ���ƣ���Ϣ��ΪCmd(u8)+CmdVal(u8) 
OSPEVENT( MT_MCU_CAMCTRL_CMD,					EV_MCUMT_BGN + 841);

/*
 *	����Ϊ�㲥��Ϣ
 */
//�㲥TOPO��Ϣ��ǰ4�ֽ�Ϊʱ��(MCU����ʱ��д),TInterfaceMtTopo����
#define EV_SAT_MCUMT_TOPO_IND MCU_MT_TOPO_NOTIF
//�㲥�ն����룬ITSatMtKey����
#define EV_SAT_MCUMT_KEY_IND MCU_MT_KEY_NOTIF
//�����б���Ϣ, ITSatTransAddr(MCU �����ַ�Ͷ˿�)+ITSatConfList����
#define EV_SAT_MCUMT_CONFLIST_IND MCU_MT_CONFLIST_NOTIF
//������Ϣ��ITSatConfInfo����ַ��Ϣ
#define EV_SAT_MCUMT_CONFINFO_IND MCU_MT_CONFSTATUS_NOTIF
/*
 *	������ϢΪMT--MCU����Ϣ
 */
//����������Ϣ����Ϣ��ΪITSateConfInfo
#define EV_SAT_MTMCU_CREATECONF_CMD MT_MCU_CREATECONF_REQ

//�����ն����ʣ���Ϣ��ΪITSatBitrate
#define EV_SAT_MCUMT_BITRATE_IND MCU_MT_SETBITRATE_CMD 

//MCUҪ���ն�ǩ������Ϣ��ΪITSatMtId
#define EV_SAT_MCUMT_SIGNNOW_CMD MCU_MT_SIGNNOW_CMD 

//MT��MCUǩ��Ӧ����Ϣ��ΪITSatMtId
#define EV_SAT_MTMCU_SIGNNOW_IND MT_MCU_SIGNNOW_NOTIF

//MT��MCU���뷢�ԣ���Ϣ��ΪNULL
#define EV_SAT_MCUMT_APPLYSPEAKER_CMD MT_MCU_APPLYSPEAKER_CMD

//MT��MCU������ϯ����Ϣ��ΪNULL
#define EV_SAT_MTMCU_APPLYCHAIR_CMD MT_MCU_APPLYCHAIRMAN_REQ

//MT��MCUָ�������ˣ���Ϣ��ΪITSatMtId
#define EV_SAT_MTMCU_SPECSPEAKER_CMD MT_MCU_SPECSPEAKER_REQ

//MT��MCUȡ�������ˣ���Ϣ��ΪNULL
#define EV_SAT_MTMCU_CANCELSPEAKER_CMD MT_MCU_CANCELSPEAKER_CMD

//MT��MCUָ����ϯ����Ϣ��ΪITSatMtId
#define EV_SAT_MTMCU_SPECCHAIRMAN_CMD MT_MCU_SPECCHAIRMAN_REQ

//MT��MCUȡ����ϯ����Ϣ��ΪNULL
#define EV_SAT_MTMCU_CANCELCHAIRMAN_CMD MT_MCU_CANCELCHAIRMAN_CMD

//MT��MCU��ʼ���渴�ϣ���Ϣ��ΪITMtList
#define EV_SAT_MTMCU_SETVMP_CMD MT_MCU_STARTVMP_CMD
//MT��MCUֹͣ���渴�ϣ���Ϣ��ΪNULL
#define EV_SAT_MTMCU_STOPVMP_CMD MT_MCU_STOPVMP_CMD

//MT��MCU��ʼ��������Ϣ��ΪNULL
#define EV_SAT_MTMCU_SETMIX_CMD MT_MCU_STARTMIX_CMD
//MT��MCUֹͣ��������Ϣ��ΪNULL
#define EV_SAT_MTMCU_STOPMIX_CMD MT_MCU_STOPMIX_CMD

//MT��MCU����նˣ���Ϣ��ΪITSatMtId
#define EV_SAT_MTMCU_INVITEMT_CMD MT_MCU_ADDMT_CMD

//MT��MCU���������飬��Ϣ��ΪNULL
#define EV_SAT_MTMCU_APPLYJOINCONF_CMD MT_MCU_APPLYJOINCONF_REQ

//MT��MCU�����˻ᣬ��Ϣ��ΪNULL
#define EV_SAT_MTMCU_APPLYLEAVECONF_CMD MT_MCU_APPLYQUITCONF_CMD

//MT��MCU�������飬��Ϣ��ΪNULL
#define EV_SAT_MTMCU_QUITCONF_CMD MT_MCU_DROPCONF_CMD

//MT��MCU����Ϣ����Ϣ��ΪITSatMtId,NULL(�����)
#define EV_SAT_MTMCU_MESSAGE_IND MT_MCU_SENDMSG_CMD

//MT��MCU����ͷ���ƣ���Ϣ��ΪCmd(u8)+CmdVal(u8) 
#define EV_SAT_MTMCU_CAMCTRL_CMD    MT_MCU_CAMCTRL_CMD

//���ն˶���Ϣ֪ͨ��MCU->MT����Ϣ��ΪITSatShortMsg
#define EV_SAT_MCUMT_MSG_IND  MCU_MT_SENDMSG_NOTIF

//MCU֪ͨ��ϯ�����ն�������ϯ��MCU->MT����Ϣ��ΪITSatMtId
#define EV_SAT_MCUMT_APPLYCHAIR_IND MCU_MT_APPLYCHAIRMAN_NOTIF

//MCU֪ͨ��ϯ�����ն�������ϯ��MCU->MT����Ϣ��ΪITSatMtId
#define EV_SAT_MCUMT_APPLYSPEAKER_IND MCU_MT_APPLYSPEAKER_NOTIF
//���ն�����ؼ�֡��MCU->MT����Ϣ��ΪITSatMsgHdr
#define EV_SAT_MCUMT_SENDIFRAME_CMD MCU_MT_SENDIFRAME_NOTIF
#endif//!_EVENT_SATELLITE_MCU_MT_H_