/*****************************************************************************
   ģ����      : VAS
   �ļ���      : VasEventDef.h
   ����ļ�    : 
   �ļ�ʵ�ֹ���: vas����ͽ������Ϣ����
   ����        : 
   �汾        : 
-----------------------------------------------------------------------------
   �޸ļ�¼:
   ��  ��      �汾        �޸���      �޸�����

******************************************************************************/
#ifndef _VAS_EVENT_DEF_H
#define _VAS_EVENT_DEF_H

#include "eventid.h"



//=============================================
//��������
//==============================================
const u8 AID_VASLIB = 110 ; //	lib��instance��
const u8 AID_VASINTERFACE =111;// �����instance��

const u8 VAS_LIB_VIDEO = 0;
const u8 VAS_LIB_AUDIO = 1;
const u8 VAS_LIB_BOTH = 2;

const u8 OUTPUT_LIB_ON = 1;
const u8 OUTPUT_LIB_OFF = 0;



const u8 EVENT_CONNECT_NOTIFY_OK =1;//�ص�����֪ͨ
const u8 EVENT_CONNECT_NOTIFY_FAIL =2;
const u8 EVENT_GET_CONFIG_NOTIFY =3;


//��������������ͨ����
#define MAX_MATRIX_INPUTCHANN	16
//��������������ͨ������lib��
#define MAXNUB_AVCHAN    16
//����ͨ�������֣�lib��
#define MAXLEN_CHANNAME  16


#define		VAS_LOG_ERROR		0
//==========================================
//��Ϣ����
//==========================================

//������ϢUI->LIB, ��Ϣ��ΪTVasStart
OSPEVENT(EV_VAS_LIB_START_CMD,								EV_MT_BGN + 1000);

//�������LIB->UI��u8Ϊʧ��ԭ�����Ϊu8Ϊ0��˵���ɹ�
OSPEVENT(EV_VAS_LIB_START_IND,								EV_MT_BGN + 1009);

//��ѯָʾ,LIB->UI��u8Ϊ��ǰ��ѵ����channel��,�����������ͼ�ν�������ʾ����
OSPEVENT(EV_VAS_LIB_ROLLING_IND,								EV_MT_BGN + 1001);

//��ѯ,UI->LIB����Ϣ��ΪTVasRolling
OSPEVENT(EV_VAS_LIB_ROLLING_CMD,								EV_MT_BGN + 1002);

//ʵʩ��������,UI->LIB����Ϣ��ΪTVasConfigu
OSPEVENT(EV_VAS_LIB_APPLY_CMD,								EV_MT_BGN + 1003);

//ȡ����ѯ��UI->LIB
OSPEVENT(EV_VAS_LIB_CANCEL_ROLLING_CMD,								EV_MT_BGN + 1004);

//���������ļ�UI->LIB,��Ϣ��ΪTVasConfiguAsk
OSPEVENT(EV_VAS_LIB_ASK_CONFIGUE_REQ,								EV_MT_BGN + 1005 );

//�õ������ļ�LIB->UI����Ϣ��ΪTVasConfigu�ṹ
OSPEVENT(EV_VAS_LIB_GET_CONFIGUE_RSP,								EV_MT_BGN + 1006 );

//���浱ǰ����UI->LIB,��Ϣ��ΪTVasConfigu�ṹ
OSPEVENT(EV_VAS_LIB_SAVE_CONFIGUE_CMD,								EV_MT_BGN + 1007);

//����VAS������UI->LIB, ��Ϣ��ΪTVasSwitcher
OSPEVENT(EV_VAS_LIB_SWITCH_CMD,								EV_MT_BGN + 1008);

//EV_MT_BGN + 1009 �Ѿ���ʹ��

////////////////////////////////////////
//������洰�ھ��, ��Ϣ��ΪHWND
OSPEVENT(EV_VAS_LIB_SET_HWND_CMD,								EV_MT_BGN + 1010);

//����ص�����, ��Ϣ��ΪTVasCallBack
OSPEVENT(EV_VAS_LIB_CALLBACK_CMD,								EV_MT_BGN + 1011);

#endif // _VAS_EVENT_DEF_H



