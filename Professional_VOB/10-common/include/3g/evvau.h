/*****************************************************************************
   ģ����      : EVVAU
   �ļ���      : evvau.h
   ����ļ�    : 
   �ļ�ʵ�ֹ���: VAU����Ϣ�ӿڶ���
   ����        : ������
   �汾        : V1.0  Copyright(C) 2006-2007 KDC, All rights reserved.
-----------------------------------------------------------------------------
   �޸ļ�¼:
   ��  ��      �汾        �޸���      �޸�����
   2006/08/21  1.0         ������        ����
******************************************************************************/
#ifndef __EVVAU_H_
#define __EVVAU_H_

#include "osp.h"
#include "eventid.h"

#define ADD_EVENT_DESC(x) OspAddEventDesc(#x, x)
      
//KSS�ڲ���Ϣ����
OSPEVENT( KSS_SETUP_NOTIFY,		    EV_RTSP_BGN + 1 );               //����Session
OSPEVENT( KSS_PLAY_NOTIFY,		    EV_RTSP_BGN + 2 );               //��ʼ����
OSPEVENT( KSS_PAUSE_NOTIFY,		    EV_RTSP_BGN + 3 );              //��ͣ
OSPEVENT( KSS_RECORD_NOTIFY,	    EV_RTSP_BGN + 4 );              //¼��
OSPEVENT( KSS_TEARDOWN_NOTIFY,	    EV_RTSP_BGN + 5 );              //���Session
OSPEVENT( KSS_DESCRIBE_NOTIFY,	    EV_RTSP_BGN + 6 );              //�յ�Describe
OSPEVENT( KSS_OPTIONS_NOTIFY,	    EV_RTSP_BGN + 7 );              //�յ�Options

//OSPEVENT( EV_KSS_CONNECT_VAU,	    EV_RTSP_BGN + 8 );              //����VAU
//OSPEVENT( EV_KSS_REGISTER_VAU,	    EV_RTSP_BGN + 9 );              //ע��VAU

OSPEVENT( EV_KSS_SESSION_CHECK,	    EV_RTSP_BGN + 10 );              //���Ự�Ƿ���

//VAU��KSS֮�����Ϣ����
//KSS����VAU��ע������,��Ϣ��Ϊ�ṹTKss
OSPEVENT( VAU_KSS_REG_REQ,		    EV_RTSP_BGN + 11 );          
//KSS����VAU��ע������,��Ϣ��Ϊ�ṹTKss
OSPEVENT( KSS_VAU_REG_ACK,		    EV_RTSP_BGN + 12 ); 
//KSS�ܾ�VAU��ע������,��Ϣ��Ϊ�ṹTKss
OSPEVENT( KSS_VAU_REG_NACK,		    EV_RTSP_BGN + 13 ); 

//ȷ���Ƿ�ע��
OSPEVENT( VAU_KSS_REG_CMF,			EV_RTSP_BGN + 14 );
//�Ѿ�ע��
OSPEVENT( KSS_VAU_HAS_REG,			EV_RTSP_BGN + 15 );
//û��ע��
OSPEVENT( KSS_VAU_NO_REG,			EV_RTSP_BGN + 16 );

//KSS��VAU֮�����Ϣ����
#define    EV_VAU_RTSP_BGN          (EV_RTSP_BGN+30)                  //��ʼ��Ϣ��

//KSS����VAU�Ľ����Ự����,
//��Ϣ��Ϊ�ṹTSetupParam+u32(����URL�ĳ���)+char *(����URL)+u32(��������ĳ���)+char *(�������)
OSPEVENT( KSS_VAU_SETUP_REQ,		EV_VAU_RTSP_BGN + 1 );          
//VAU����KSS�Ľ����Ự����
//��Ϣ��Ϊ�ṹTSetupParam+u32(����URL�ĳ���)+char *(����URL)+u32(��������ĳ���)+char *(�������)
OSPEVENT( VAU_KSS_SETUP_ACK,		EV_VAU_RTSP_BGN + 2 ); 
//VAU�ܾ�KSS�Ľ����Ự����
//��Ϣ��Ϊ�ṹTSetupParam+u32(����URL�ĳ���)+char *(����URL)+u32(��������ĳ���)+char *(�������)
OSPEVENT( VAU_KSS_SETUP_NACK,		EV_VAU_RTSP_BGN + 3 ); 

//KSS����VAU�Ŀ�ʼ��������
//��Ϣ��Ϊdouble(��ʼ����ʱ��)
OSPEVENT( KSS_VAU_PLAY_REQ,		    EV_VAU_RTSP_BGN + 4 );          
//VAU����KSS�Ŀ�ʼ��������
OSPEVENT( VAU_KSS_PLAY_ACK,		    EV_VAU_RTSP_BGN + 5 ); 
//VAU�ܾ�KSS�Ŀ�ʼ��������
OSPEVENT( VAU_KSS_PLAY_NACK,		EV_VAU_RTSP_BGN + 6 );  

//KSS����VAU����ͣ����
OSPEVENT( KSS_VAU_PAUSE_REQ,		EV_VAU_RTSP_BGN + 7 );          
//VAU����KSS����ͣ����
OSPEVENT( VAU_KSS_PAUSE_ACK,		EV_VAU_RTSP_BGN + 8 ); 
//VAU�ܾ�KSS����ͣ����
OSPEVENT( VAU_KSS_PAUSE_NACK,		EV_VAU_RTSP_BGN + 9 );            

//KSS����VAU��¼������
OSPEVENT( KSS_VAU_RECORD_REQ,		EV_VAU_RTSP_BGN + 10 );          
//VAU����KSS��¼������
OSPEVENT( VAU_KSS_RECORD_ACK,		EV_VAU_RTSP_BGN + 11 ); 
//VAU�ܾ�KSS��¼������
OSPEVENT( VAU_KSS_RECORD_NACK,		EV_VAU_RTSP_BGN + 12 ); 

//KSS����VAU�Ĳ���Ự����
OSPEVENT( KSS_VAU_TEARDOWN_REQ,		EV_VAU_RTSP_BGN + 13 );          
//VAU����KSS�Ĳ���Ự����
OSPEVENT( VAU_KSS_TEARDOWN_ACK,		EV_VAU_RTSP_BGN + 14 ); 
//VAU�ܾ�KSS�Ĳ���Ự����
OSPEVENT( VAU_KSS_TEARDOWN_NACK,	EV_VAU_RTSP_BGN + 15 ); 

//KSS����VAU�ĵõ���������
OSPEVENT( KSS_VAU_DESCRIBE_REQ,		EV_VAU_RTSP_BGN + 16 );          
//VAU����KSS�ĵõ���������
OSPEVENT( VAU_KSS_DESCRIBE_ACK,		EV_VAU_RTSP_BGN + 17 ); 
//VAU�ܾ�KSS�ĵõ���������
OSPEVENT( VAU_KSS_DESCRIBE_NACK,	EV_VAU_RTSP_BGN + 18 );


OSPEVENT( VAU_KSS_ADD_TRANS_ACK,  	EV_VAU_RTSP_BGN + 20 );
OSPEVENT( VAU_KSS_ADD_TRANS_NACK,  	EV_VAU_RTSP_BGN + 21 );  

//VAU�ڲ���Ϣ����
#define    EV_VAU_BGN          EV_VAU_RTSP_BGN+30 

OSPEVENT( EV_VAU_CONNECT_KSS,	    EV_VAU_BGN + 1 );              //����VAU
OSPEVENT( EV_VAU_REGISTER_KSS,	    EV_VAU_BGN + 2 );              //ע��VAU
OSPEVENT( EV_VAU_DISCONNECT_KSS,	EV_VAU_BGN + 3 );              //����VAU
OSPEVENT( EV_VAU_LOGINOUT_KSS,		EV_VAU_BGN + 4 );              //����VAU

#endif
