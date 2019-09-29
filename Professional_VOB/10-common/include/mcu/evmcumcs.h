/*****************************************************************************
   ģ����      : mcu
   �ļ���      : evmcumcs.h
   ����ļ�    : 
   �ļ�ʵ�ֹ���: MCU��������̨�ӿ���Ϣ����
   ����        : ������
   �汾        : V3.0  Copyright(C) 2001-2002 KDC, All rights reserved.
-----------------------------------------------------------------------------
   �޸ļ�¼:
   ��  ��      �汾        �޸���      �޸�����
   2003/10/27  3.0         ������      ����
   2005/02/19  3.6         ����      �����޸ġ���3.5�汾�ϲ�
******************************************************************************/
#ifndef _EVMCUMCS_H_
#define _EVMCUMCS_H_

#include "osp.h"
#include "eventid.h"

/*------------------------------------------------------------------------------
 MCU��������̨�ӿ���Ϣ��22001-23000��
------------------------------------------------------------------------------*/

//3.1	��������

//3.1.1	����
    //����̨֪ͨMCU�����ӣ�����׼�룬��Ϣ��: TMcsRegInfo
    OSPEVENT( MCS_MCU_CONNECT_REQ,		    EV_MCSVC_BGN + 1 );	
    //MCU׼��Ӧ����Ϣ��: TMcu + TMtAlias(MCU�ı���) + dwAnotherMpcIP(��һ��MpcIP,������)
    //                    + byMaster(1-��ǰMpc����,0-��ǰMpc����) 
    //                    + u8 byGrpId(�û���������Id) 
    //                    + u8 OS ����(OS_TYPE_VXWORKS��)
	//					 �����8000BMCU (TMcu.GetMcuType() == MCU_TYPE_KDV8000B
	//					  + TMcu8kbPfmFilter CMcuPfmLmt::m_tFilter(8000b�������ƽṹ��,�����б��沢����)
    OSPEVENT( MCU_MCS_CONNECT_ACK,		    EV_MCSVC_BGN + 2 );
    //MCU�ܾ�Ӧ����Ϣ����
    OSPEVENT( MCU_MCS_CONNECT_NACK,		    EV_MCSVC_BGN + 3 );

//3.1.2	ʱ��ͬ��
    //�������̨��ѯmcu����ʱ�䣬����Ϣ��
    OSPEVENT( MCS_MCU_CURRTIME_REQ,		    EV_MCSVC_BGN + 5 );
    //mcu�ɹ�Ӧ����Ϣ��ΪTKdvTime
    OSPEVENT( MCU_MCS_CURRTIME_ACK,		    EV_MCSVC_BGN + 6 );
    //mcu�ܾ�Ӧ������Ϣ��
    OSPEVENT( MCU_MCS_CURRTIME_NACK,        EV_MCSVC_BGN + 7 );

//3.1.3	��ѯMCU״̬
    //��ѯMCU״̬�����Ϣ��: ��
    OSPEVENT( MCS_MCU_GETMCUSTATUS_CMD,     EV_MCSVC_BGN + 9 );
	//��ѯMCU״̬������Ϣ��: ��
    OSPEVENT( MCS_MCU_GETMCUSTATUS_REQ,	    EV_MCSVC_BGN + 10 );
    //���صĳɹ�Ӧ����Ϣ��: TMcuStatus
    OSPEVENT( MCU_MCS_GETMCUSTATUS_ACK,     EV_MCSVC_BGN + 11 );
    //���ص�ʧ��Ӧ����Ϣ��: ��
    OSPEVENT( MCU_MCS_GETMCUSTATUS_NACK,    EV_MCSVC_BGN + 12 );
    //MCU״̬֪ͨ����Ϣ��Ϊ�ṹTMcuStatus
    OSPEVENT( MCU_MCS_MCUSTATUS_NOTIF,	    EV_MCSVC_BGN + 13 );
    
    //��ѯmcu����״̬����Ϣ�壺��
    OSPEVENT( MCS_MCU_GETMSSTATUS_REQ,      EV_MCSVC_BGN + 14 );
    //��Ϣ�壺TMcuMsStatus
    OSPEVENT( MCU_MCS_GETMSSTATUS_ACK,      EV_MCSVC_BGN + 15 );
    
//3.1.4 �ϴ��ļ�(mcu.z, mcuos and mcu.ios)
    //MCS�ϴ��ļ���ɺ��������, ��Ϣ��: u8(byLayer) + u8(bySlot) + u8(bySlotType) + u16(wLen) + s8[wLen]
    // ~~ as seperate between file name in s8[wLen]
    // demo: 0 0 1 21 'mcu.zudp~~mcuosudp~~mcu.iosudp\0'	
//    OSPEVENT( MCS_MCU_UPLOADFILENAME_REQ,   EV_MCSVC_BGN + 17 );
    //MCU���صĳɹ�Ӧ��, ��Ϣ�壺��
//    OSPEVENT( MCU_MCS_UPLOADFILENAME_ACK,   EV_MCSVC_BGN + 18 );
    //MCU���ص�ʧ��Ӧ��, ��Ϣ�壺��
//    OSPEVENT( MCU_MCS_UPLOADFILENAME_NACK,  EV_MCSVC_BGN + 19 );

//3.2	�������
//3.2.1	��������б�	
    //�������̨��ѯMCU�ϵĻ����б�����Ϣ�� 
    OSPEVENT( MCS_MCU_LISTALLCONF_REQ,		EV_MCSVC_BGN + 20 );
    //Ӧ��MCS_MCU_LISTALLCONF_REQ������Ϣ�壬����MCU_MCS_CONF_NOTIF�� 
    OSPEVENT( MCU_MCS_LISTALLCONF_ACK,		EV_MCSVC_BGN + 21 );
    //MCU��û�л���,����Ϣ��
    OSPEVENT( MCU_MCS_LISTALLCONF_NACK,     EV_MCSVC_BGN + 22 );
    //����������Ϣ֪ͨ,��Ϣ��: TConfInfo
	//����ԤԼ����,���п������������ֶ�:
	//                  + TTvWallModule(��ѡ�ֶΣ��ɻ��������е��Ƿ��е���ǽģ�����) 
	//                  + TVmpModule(��ѡ�ֶΣ��ɻ��������е��Ƿ��л���ϳ�ǽģ�����) 
    OSPEVENT( MCU_MCS_CONFINFO_NOTIF,       EV_MCSVC_BGN + 23 );

    //�������Ϣ֪ͨ����Ϣ�壺TBasicConfInfo
    OSPEVENT( MCU_MCS_SIMCONFINFO_NOTIF,    EV_MCSVC_BGN + 24 );

//3.2.2	�������� 	
    //�������̨��MCU�ϴ���һ������  
	//��Ϣ��: TConfInfo + 2 byte(������,TMtAlias����������,�������n)
	//                  + n byte(TMtAlias������,ÿ��Ϊ 1byte(����)+1byte(����)+xbyte(�ַ���)+2byte(��������) 
	//                            ��1�ֽ�ΪTMtAlias����,��2�ֽ�Ϊ����x,�����x�ֽ�ΪTMtAlias����)
	//                  + TTvWallModule(��ѡ�ֶΣ��ɻ��������е��Ƿ��е���ǽģ�����) 
	//                  + TVmpModule(��ѡ�ֶΣ��ɻ��������е��Ƿ��л���ϳ�ǽģ�����)                  
    OSPEVENT( MCS_MCU_CREATECONF_REQ,		EV_MCSVC_BGN + 25 );
    //�������̨��MCU�ϴ���һ������ɹ�Ӧ��, ��Ϣ��: TConfInfo,
    //ע��:�ɹ������ͬʱ����ʾ�Դ�����
    OSPEVENT( MCU_MCS_CREATECONF_ACK,		EV_MCSVC_BGN + 26 );
    //�������̨��MCU�ϴ���һ������ʧ��, ����Ϣ��
    OSPEVENT( MCU_MCS_CREATECONF_NACK,      EV_MCSVC_BGN + 27 );
	
    //�������̨��MCU�ϰ�����ģ�崴��һ����ʱ����, ����Ϣ��                
    OSPEVENT( MCS_MCU_CREATECONF_BYTEMPLATE_REQ,		EV_MCSVC_BGN + 28 );
    //����ģ��ɹ���ת��ɼ�ʱ����, ����Ϣ�� 
    OSPEVENT( MCU_MCS_CREATECONF_BYTEMPLATE_ACK,		EV_MCSVC_BGN + 29 );
    //����ģ��ת��ɼ�ʱ����ʧ��, ����Ϣ��
    OSPEVENT( MCU_MCS_CREATECONF_BYTEMPLATE_NACK,       EV_MCSVC_BGN + 30 );

    //�������̨��MCU�ϰ�����ģ�崴��һ��ԤԼ����, ��Ϣ��: TKdvTime   (��ʼʱ��)             
    OSPEVENT( MCS_MCU_CREATESCHCONF_BYTEMPLATE_REQ,		EV_MCSVC_BGN + 31 );
    //����ģ��ɹ���ת���ԤԼ����, ����Ϣ�� 
    OSPEVENT( MCU_MCS_CREATESCHCONF_BYTEMPLATE_ACK,		EV_MCSVC_BGN + 32 );
    //����ģ��ת���ԤԼ����ʧ��, ����Ϣ��
    OSPEVENT( MCU_MCS_CREATESCHCONF_BYTEMPLATE_NACK,    EV_MCSVC_BGN + 33 );

    //������GK��ע��ɹ�֪ͨ, ��Ϣ��:u8 (1:�ɹ���0:ʧ��)
    OSPEVENT( MCU_MCS_CONFREGGKSTATUS_NOTIF,            EV_MCSVC_BGN + 34 );
    
//3.2.3	�������� 
    //�������̨����MCU����һ������, ����Ϣ��
    OSPEVENT( MCS_MCU_RELEASECONF_REQ,		    EV_MCSVC_BGN + 35 );
    //MCU�ɹ���������Ӧ��, ����Ϣ��
    OSPEVENT( MCU_MCS_RELEASECONF_ACK,		    EV_MCSVC_BGN + 36 );
    //MCU�ܾ���������, ����Ϣ��
    OSPEVENT( MCU_MCS_RELEASECONF_NACK,         EV_MCSVC_BGN + 37 );
    //MCU��������֪ͨ, ��Ϣ��: u8 (takemode: ���궨��) CONF_TAKEMODE_SCHEDULED, CONF_TAKEMODE_ONGOING��ԤԼ�����ʱ����
    OSPEVENT( MCU_MCS_RELEASECONF_NOTIF,        EV_MCSVC_BGN + 38 );

//3.2.4	��������
//3.2.4.1	��������
    //�������̨����MCU�ı���鱣����ʽ, ��Ϣ��:1byte(���鱣����ʽ) 
    OSPEVENT( MCS_MCU_CHANGECONFLOCKMODE_REQ,   EV_MCSVC_BGN + 40 );
    //MCU�ɹ��ı���鱣����ʽ����Ӧ��, ��Ϣ��:1byte(���鱣����ʽ)
    OSPEVENT( MCU_MCS_CHANGECONFLOCKMODE_ACK,   EV_MCSVC_BGN + 41 );
    //MCU�ܾ��ı���鱣����ʽ����, ����Ϣ��
    OSPEVENT( MCU_MCS_CHANGECONFLOCKMODE_NACK,  EV_MCSVC_BGN + 42 );
    //��Ϣ�壺1byte(���鱣����ʽ���������CServMsg��)
    OSPEVENT( MCU_MCS_CONFLOCKMODE_NOTIF,       EV_MCSVC_BGN + 43 );

//3.2.4.8	������� 
	//�õ����������Ϣ
	OSPEVENT( MCS_MCU_GETLOCKINFO_REQ,      EV_MCSVC_BGN + 45 );
	//���������ϢӦ��
	//��Ϣ��: 4byte(�����ص�IP,������)+32byte(�����ص��û���)
	OSPEVENT( MCU_MCS_GETLOCKINFO_ACK,      EV_MCSVC_BGN + 46 );
	//�õ��������ܾ�
	OSPEVENT( MCU_MCS_GETLOCKINFO_NACK,     EV_MCSVC_BGN + 47 );
    //MCU���������̨�ĵ�ǰ�������Ŀ���̨����Ϣ,
	//��Ϣ��: 4byte(�����ص�IP,������)+32byte(�����ص��û���)
    OSPEVENT( MCU_MCS_LOCKUSERINFO_NOTIFY,  EV_MCSVC_BGN + 48 );

//3.2.4.2	��������
    //MCUҪ��������̨�����������, ����Ϣ�� 
    OSPEVENT( MCU_MCS_ENTERCONFPWD_REQ,		EV_MCSVC_BGN + 55 );
    //�������̨��ӦMCU����������, ��Ϣ��: 32byte(��������)
    OSPEVENT( MCS_MCU_ENTERCONFPWD_ACK,		EV_MCSVC_BGN + 56 );
    //�������̨�ܾ�MCU����������, ����Ϣ��
    OSPEVENT( MCS_MCU_ENTERCONFPWD_NACK,    EV_MCSVC_BGN + 57 );
    //MCU��ʾ�������̨�������, ����Ϣ��
    OSPEVENT( MCU_MCS_WRONGCONFPWD_NOTIF,   EV_MCSVC_BGN + 58 );

//3.2.4.3	���Ļ������� 
    //�������̨����MCU���Ļ�������, ��Ϣ��:32byte�ַ���(��������) 
    OSPEVENT( MCS_MCU_CHANGECONFPWD_REQ,	EV_MCSVC_BGN + 61 );
    //MCU�ɹ����Ļ�������Ӧ��, ��Ϣ��:32byte�ַ���(��������
    OSPEVENT( MCU_MCS_CHANGECONFPWD_ACK,	EV_MCSVC_BGN + 62 );
    //MCU�ܾ����Ļ�������, ����Ϣ��
    OSPEVENT( MCU_MCS_CHANGECONFPWD_NACK,   EV_MCSVC_BGN + 63 );
    //��Ϣ��:32byte�ַ���(��������)
    OSPEVENT( MCU_MCS_CHANGECONFPWD_NOTIF,  EV_MCSVC_BGN + 64 );

//3.2.5	������� 
    //�������̨����MCU�������, ��Ϣ��: 1byte(1:����Ϊȱʡ����,0:����Ϊȱʡ����) 
    OSPEVENT( MCS_MCU_SAVECONF_REQ,		    EV_MCSVC_BGN + 65 );
    //MCU�ɹ��������Ӧ��, ��Ϣ��:1byte(1:����Ϊ����ģ��,0:����Ϊ����ģ��) 
    OSPEVENT( MCU_MCS_SAVECONF_ACK,		    EV_MCSVC_BGN + 66 );
    //MCU�ܾ��������, ����Ϣ��
    OSPEVENT( MCU_MCS_SAVECONF_NACK,        EV_MCSVC_BGN + 67 );
	

//3.2.6	�޸�ԤԼ���� 
    //�������̨��MCU�ϴ���һ�����飬��Ϣ��ͬ MCS_MCU_CREATECONF_REQ
	OSPEVENT( MCS_MCU_MODIFYCONF_REQ,		EV_MCSVC_BGN + 69 );
    //MCU�ɹ��޸�ԤԼ����, ����Ϣ��
    OSPEVENT( MCU_MCS_MODIFYCONF_ACK,		EV_MCSVC_BGN + 70 );
    //MCU�ܾ��޸�ԤԼ����, ����Ϣ��
    OSPEVENT( MCU_MCS_MODIFYCONF_NACK,      EV_MCSVC_BGN + 71 ); 
    
    //��ش���ģ�壬��Ϣ��ͬ MCS_MCU_CREATECONF_REQ
    OSPEVENT( MCS_MCU_CREATETEMPLATE_REQ,   EV_MCSVC_BGN + 73 );
    //��Ϣ�壺��
    OSPEVENT( MCU_MCS_CREATETEMPLATE_ACK,   EV_MCSVC_BGN + 74 );
    //��Ϣ�壺��
    OSPEVENT( MCU_MCS_CREATETEMPLATE_NACK,  EV_MCSVC_BGN + 75 );

    //����޸�ģ�壬��Ϣ��ͬ MCS_MCU_CREATECONF_REQ
    OSPEVENT( MCS_MCU_MODIFYTEMPLATE_REQ,   EV_MCSVC_BGN + 77 );
    //��Ϣ�壺��
    OSPEVENT( MCU_MCS_MODIFYTEMPLATE_ACK,   EV_MCSVC_BGN + 78 );
    //��Ϣ�壺��
    OSPEVENT( MCU_MCS_MODIFYTEMPLATE_NACK,  EV_MCSVC_BGN + 79 );

    //���ɾ��ģ�壬��Ϣ�壺��
    OSPEVENT( MCS_MCU_DELTEMPLATE_REQ,      EV_MCSVC_BGN + 81 );
    //��Ϣ�壺��
    OSPEVENT( MCU_MCS_DELTEMPLATE_ACK,      EV_MCSVC_BGN + 82 );
    //��Ϣ�壺��
    OSPEVENT( MCU_MCS_DELTEMPLATE_NACK,     EV_MCSVC_BGN + 83 );
    //��Ϣ�壺��
    OSPEVENT( MCU_MCS_DELTEMPLATE_NOTIF,    EV_MCSVC_BGN + 84 );

	//�ѻ������Ϊģ��, ��Ϣ��: ��	---Ԥ����Ϣ�ӿ�, �����Ժ������, zgc, 2007/04/20
	OSPEVENT( MCS_MCU_SAVECONFTOTEMPLATE_REQ,	EV_MCSVC_BGN + 85 );
	//��Ϣ��: ��
	OSPEVENT( MCU_MCS_SAVECONFTOTEMPLATE_ACK,	EV_MCSVC_BGN + 86 );
	//��Ϣ��: ��
	OSPEVENT( MCU_MCS_SAVECONFTOTEMPLATE_NACK,	EV_MCSVC_BGN + 87 );

    //ģ���ԤԼ������Ϣ֪ͨ����Ϣ��ͬ MCS_MCU_CREATECONF_REQ    
    OSPEVENT( MCU_MCS_TEMSCHCONFINFO_NOTIF, EV_MCSVC_BGN + 88 );

//3.2.7	�ӳ����� 
	//�������̨����MCU�ӳ�����, ��Ϣ��: 1 u16 (������, �ӳ�ʱ��, ��λ: ����)
	OSPEVENT( MCS_MCU_DELAYCONF_REQ,        EV_MCSVC_BGN + 90 );
	//MCU�ɹ��ӳ�����Ӧ��, ��Ϣ��: 1 u16 (�������ӳ�ʱ�䣬��λ������) 
	OSPEVENT( MCU_MCS_DELAYCONF_ACK,        EV_MCSVC_BGN + 91 );
	//MCU�ܾ��ӳ�����Ӧ��
	OSPEVENT( MCU_MCS_DELAYCONF_NACK,       EV_MCSVC_BGN + 92 );
	//MCU�ӳ�����֪ͨ, ��Ϣ��: 1 u16 (�������ӳ�ʱ�䣬��λ������)
	OSPEVENT( MCU_MCS_DELAYCONF_NOTIF,      EV_MCSVC_BGN + 93 );	
	//MCU֪ͨ��ػ������ʣ��ʱ��, ��Ϣ��: 1 u16 (������, �������ʣ��ʱ��, ��λ: ����)
	OSPEVENT( MCU_MCS_CONFTIMELEFT_NOTIF,   EV_MCSVC_BGN + 94 );

//3.3	�������
//3.3.1	ָ����ϯ 
	//�������ָ̨��һ̨�ն�Ϊ��ϯ, ��Ϣ�壺  TMt(����ϯ���ն�)
    OSPEVENT( MCS_MCU_SPECCHAIRMAN_REQ,		EV_MCSVC_BGN + 95 );
	//MCU�ɹ�ָ��������ϯӦ��, ��Ϣ�壺  ��
	OSPEVENT( MCU_MCS_SPECCHAIRMAN_ACK,		EV_MCSVC_BGN + 96 );
	//MCU�ܾ�ָ��������ϯӦ��, ��Ϣ�壺  ��
	OSPEVENT( MCU_MCS_SPECCHAIRMAN_NACK,	EV_MCSVC_BGN + 97 );
	//ָ����ϯ֪ͨ, ��Ϣ�壺 TMt(����ϯ���ն�) 
	OSPEVENT( MCU_MCS_SPECCHAIRMAN_NOTIF,   EV_MCSVC_BGN + 98 );
	//�ն�������ϯ֪ͨ, ��Ϣ�壺 TMt(������ն�) 
	OSPEVENT( MCU_MCS_MTAPPLYCHAIRMAN_NOTIF,   EV_MCSVC_BGN + 99 );

//3.3.2	ȡ����ϯ 
	//�������̨ȡ����ǰ������ϯ����Ϣ�壺��
    OSPEVENT( MCS_MCU_CANCELCHAIRMAN_REQ,   EV_MCSVC_BGN + 101 );
	//MCU�ɹ�ȡ��������ϯӦ��,   ��Ϣ�壺  ��
    OSPEVENT( MCU_MCS_CANCELCHAIRMAN_ACK,   EV_MCSVC_BGN + 102 );
	//����������ϯ
	OSPEVENT( MCU_MCS_CANCELCHAIRMAN_NACK,  EV_MCSVC_BGN + 103 );
	//ȡ����ϯ֪ͨ
	OSPEVENT( MCU_MCS_CANCELCHAIRMAN_NOTIF, EV_MCSVC_BGN + 104 );

	//�������̨���û������ϯ��ʽ 
	//��Ϣ��: 1byte(0-����ϯ������ȡ����������ָ������ɹ�,1-��������ϯ)
	OSPEVENT( MCS_MCU_SETCHAIRMODE_CMD,     EV_MCSVC_BGN + 105 );
    //��Ϣ�壺1byte(0-����ϯ��1-��������ϯ)
    OSPEVENT( MCU_MCS_CONFCHAIRMODE_NOTIF,  EV_MCSVC_BGN + 106 );    

//3.3.3	ָ������ 
    //�������ָ̨��һ̨�ն˷���, ��Ϣ�壺  TMt(�����ն�)
    OSPEVENT( MCS_MCU_SPECSPEAKER_REQ,      EV_MCSVC_BGN + 111 );
    //MCU�ɹ�ָ��������, ��Ϣ�壺��
    //��Ϣͷ���ܰ��������룬�����벻Ϊ0ʱ��Ҫ��ʾ�ô�����Ϣ
    OSPEVENT( MCU_MCS_SPECSPEAKER_ACK,      EV_MCSVC_BGN + 112 );
    //ָ��֮ǰ�ķ����߱�ȡ��, ��Ϣ�壺��  ��Ϣͷ����������
    OSPEVENT( MCU_MCS_SPECSPEAKER_NACK,     EV_MCSVC_BGN + 113 );
    //ָ������֪ͨ, ��Ϣ�壺  TMt(�����ն�)
    OSPEVENT( MCU_MCS_SPECSPEAKER_NOTIF,    EV_MCSVC_BGN + 114 );

   //ǿ�ƹ㲥������
   //��Ϣ��: 1byte(0-ȡ��ǿ�ƹ㲥������,1-��ʼǿ�ƹ㲥������)
   OSPEVENT( MCS_MCU_MTSEESPEAKER_CMD,      EV_MCSVC_BGN + 115 );

   //MCU֪ͨ����ն����뷢��, ��Ϣ�壺  TMt(�����ն�)
   OSPEVENT( MCU_MCS_MTAPPLYSPEAKER_NOTIF,  EV_MCSVC_BGN + 116 );

//3.3.4	ȡ������
	//�������̨ȡ������Speaker, ��Ϣ�壺  ��
	OSPEVENT( MCS_MCU_CANCELSPEAKER_REQ,    EV_MCSVC_BGN + 121 );
   //MCU�ɹ�ȡ��������ϯӦ�� ,��Ϣ�壺  ��
    OSPEVENT( MCU_MCS_CANCELSPEAKER_ACK,    EV_MCSVC_BGN + 122 );
   //ȡ��������ʧ�ܣ���Ϣ�壺  ��
	OSPEVENT( MCU_MCS_CANCELSPEAKER_NACK,   EV_MCSVC_BGN + 123 );
	//ȡ��������֪ͨ, ��Ϣ�壺  ��
	OSPEVENT( MCU_MCS_CANCELSPEAKER_NOTIF,  EV_MCSVC_BGN + 124 );

//3.3.5 ָ���ش�
    //�������ָ̨�����᳡���ϼ��ش����ն�, ��Ϣ�壺  TMt
    OSPEVENT( MCS_MCU_SPECOUTVIEW_REQ,      EV_MCSVC_BGN + 125 );
    //MCU�ɹ�ָ�����᳡���ϼ��ش����ն� ,��Ϣ�壺  TMt
    OSPEVENT( MCU_MCS_SPECOUTVIEW_ACK,      EV_MCSVC_BGN + 126 );
    //ָ�����᳡���ϼ��ش����ն�ʧ�ܣ���Ϣ�壺  TMt
    OSPEVENT( MCU_MCS_SPECOUTVIEW_NACK,     EV_MCSVC_BGN + 127 );


//3.3.6	�����ն� 
	//�������̨����MCU�����ն�, ��Ϣ�壺  TMcu+TAddMtInfo ����(Ҫ���ӵ��ն��б�)
	OSPEVENT( MCS_MCU_ADDMT_REQ,            EV_MCSVC_BGN + 141 );
	//MCUͬ��������̨�����ն�, ��Ϣ�壺  ��
	OSPEVENT( MCU_MCS_ADDMT_ACK,            EV_MCSVC_BGN + 142 );
	//MCU�ܾ��������̨�����ն�, ��Ϣ�壺  ��
	OSPEVENT( MCU_MCS_ADDMT_NACK,           EV_MCSVC_BGN + 143 );
	//���԰棬�������̨����MCU����ָ���������������ն�
	//��Ϣ�壺TMcu+TAddMtInfoEx(�����ն˵�����)
	OSPEVENT( MCS_MCU_ADDMTEX_REQ,          EV_MCSVC_BGN + 144 );


//3.3.7	ɾ���ն�
	//�������̨�����ն���ᣬ��Ϣ�壺  TMt(��ɾ���ն�)
	OSPEVENT( MCS_MCU_DELMT_REQ,            EV_MCSVC_BGN + 151 );
	//�ն˱��ɹ�������Ϣ�壺  �� 
	OSPEVENT( MCU_MCS_DELMT_ACK,            EV_MCSVC_BGN + 152 );
	//��Ϣ�������ܾ������նˣ���Ϣ�壺  ��
	OSPEVENT( MCU_MCS_DELMT_NACK,           EV_MCSVC_BGN + 153 );

//3.3.8	���ѡ��
    // zw [06/27/2008] ��MCU_MCS_STARTSWITCHMC_ACK��MCU_MCS_STARTPLAY_NOTIF����Ϣ��������TAudAACCap(Audio)
	//���ѡ���ն�, ��Ϣ�壺  TSwitchInfo
	OSPEVENT( MCS_MCU_STARTSWITCHMC_REQ,    EV_MCSVC_BGN + 161 );
	//MCUӦ��������̨ѡ���ն�, 
	//��Ϣ�壺  TSwitchInfo+TMediaEncrypt(video)+TDoublePayload(video)+TMediaEncrypt(Audio)+TDoublePayload(Audio)+TAudAACCap(Audio)
	OSPEVENT( MCU_MCS_STARTSWITCHMC_ACK,    EV_MCSVC_BGN + 162 );
	//MCU�ܾ��������̨ѡ���ն�, ��Ϣ�壺  ��
	OSPEVENT( MCU_MCS_STARTSWITCHMC_NACK,   EV_MCSVC_BGN + 163 );
	//MCU����صĿ�ʼѡ��֪ͨ, 
	//��Ϣ�壺  TSwitchInfo+TMediaEncrypt(video)+TDoublePayload(video)+TMediaEncrypt(Audio)+TDoublePayload(Audio)+TAudAACCap(Audio)
	OSPEVENT( MCU_MCS_STARTPLAY_NOTIF,      EV_MCSVC_BGN + 164 );
	

//3.3.9	���ȡ��ѡ��
	//���ȡ��ѡ���ն�, ��Ϣ�壺  TSwitchInfo
	OSPEVENT( MCS_MCU_STOPSWITCHMC_REQ,     EV_MCSVC_BGN + 171 );
	//MCUӦ��������̨ѡ���ն�, ��Ϣ�壺  TSwitchInfo
	OSPEVENT( MCU_MCS_STOPSWITCHMC_ACK,     EV_MCSVC_BGN + 172 );
	//MCU�ܾ��������̨ѡ���ն�, ��Ϣ�壺  ��
	OSPEVENT( MCU_MCS_STOPSWITCHMC_NACK,    EV_MCSVC_BGN + 173 );
	//MCU����ص�ֹͣѡ��֪ͨ, ��Ϣ�壺  TSwitchInfo
	OSPEVENT( MCU_MCS_STOPPLAY_NOTIF,       EV_MCSVC_BGN + 174 );

//3.3.10	���Ͷ���Ϣ
	//�������̨����MCU���ն˷��Ͷ���Ϣ, 
	//��Ϣ�壺2 byte(�ն���,������,ֵΪN,0Ϊ�㲥�������ն�) + N��TMt +TROLLMSG
   OSPEVENT( MCS_MCU_SENDRUNMSG_CMD,        EV_MCSVC_BGN + 181 );
	//MCU���������̨�ķ��Ͷ���Ϣ֪ͨ, ��Ϣ�壺  TRunMsgInfo 
   OSPEVENT( MCU_MCS_SENDRUNMSG_NOTIF,      EV_MCSVC_BGN + 182 );

//3.3.11	�����ն��б�
   //�������̨����MCU�ĵõ��ն��б�����, ��Ϣ�壺  TMcu (MCU��Ϊ0��ʾ����MCU)
   OSPEVENT( MCS_MCU_GETMTLIST_REQ,         EV_MCSVC_BGN + 191 );
   //MCU��Ӧ�������̨�ĵõ��ն��б�����, ��Ϣ�壺  TMcu
   OSPEVENT( MCU_MCS_GETMTLIST_ACK,         EV_MCSVC_BGN + 192 );
   //MCU�ܾ����������б� ��Ϣ�壺  ��
   OSPEVENT( MCU_MCS_GETMTLIST_NACK,        EV_MCSVC_BGN + 193 );
   //MCU�����������̨���ն��б�֪ͨ, ��Ϣ�壺  TMcu+TMtExt����
   OSPEVENT( MCU_MCS_MTLIST_NOTIF,          EV_MCSVC_BGN + 194 );
   //MCU�����������̨���ն����͸ı�֪ͨ, ��Ϣ�壺  TMt
   OSPEVENT( MCU_MCS_MTTYPECHANGE_NOTIF,    EV_MCSVC_BGN + 195 );
   //MCU�����������̨���ն�������Ϣ֪ͨ, ��Ϣ�壺  TConfAllMtInfo
   OSPEVENT( MCU_MCS_CONFALLMTINFO_NOTIF,   EV_MCSVC_BGN + 197 );
    
//3.3.12	��ѯ������Ϣ
   //�������̨��MCU��ѯ������Ϣ, ��Ϣ�壺  �� 
   OSPEVENT( MCS_MCU_GETCONFINFO_REQ,       EV_MCSVC_BGN + 201 );
   //MCU��Ӧ�������̨�Ļ�����Ϣ����, ��Ϣ�壺  TConfInfo
   OSPEVENT( MCU_MCS_GETCONFINFO_ACK,       EV_MCSVC_BGN + 202 );
   //MCU�ܾ��������̨�Ļ�����Ϣ����, ��Ϣ�壺  ��
   OSPEVENT( MCU_MCS_GETCONFINFO_NACK,      EV_MCSVC_BGN + 203 );
   
//3.3.13 ��ѯMAUʹ��״̬��Ϣ
   //��ѯ����: NULL
   OSPEVENT( MCS_MCU_GETMAUSTATUS_REQ,      EV_MCSVC_BGN + 204 );
   //Ӧ��: TMcuMauStatus
   OSPEVENT( MCU_MCS_GETMAUSTATUS_ACK,      EV_MCSVC_BGN + 205 );
   //�ܾ�Ӧ��: NULL
   OSPEVENT( MCU_MCS_GETMAUSTATUS_NACK,     EV_MCSVC_BGN + 206 );
   //״̬����֪ͨ: TMcuHdBasStatus
   OSPEVENT( MCU_MCS_MAUSTATUS_NOTIFY,      EV_MCSVC_BGN + 207 );
   
   // EV_MCSVC_BGN+208,209,210 �Ѿ��������õ���
//3.4	�������
//3.4.1	��ѯ����
//3.4.1.1	��ѯ����
   //�������̨����û��鿪ʼ��ѯ�㲥, ��Ϣ�壺  TPollInfo + TMtPollParam����
   OSPEVENT( MCS_MCU_STARTPOLL_CMD,         EV_MCSVC_BGN + 211 ); 
   //�������̨����û���ֹͣ��ѯ�㲥, ��Ϣ�壺  ��
   OSPEVENT( MCS_MCU_STOPPOLL_CMD,          EV_MCSVC_BGN + 212 );
   //�������̨����û�����ͣ��ѯ�㲥, ��Ϣ�壺  ��
   OSPEVENT( MCS_MCU_PAUSEPOLL_CMD,         EV_MCSVC_BGN + 213 );
   //�������̨����û��������ѯ�㲥, ��Ϣ�壺  ��
   OSPEVENT( MCS_MCU_RESUMEPOLL_CMD,        EV_MCSVC_BGN + 214 );

   //�������̨����û��������ѯ�б�, ��Ϣ�壺TPollInfo + TMtPollParam���顣ֻ������ѯ������(��ѯ�У���ͣ)���б��޸ģ�δ��ʼ��ѯ���벻Ҫʹ�ø���Ϣ
   OSPEVENT( MCS_MCU_CHANGEPOLLPARAM_CMD,   EV_MCSVC_BGN + 219 );
   //MCU���еĻ��ˢ����ѯ�б�, ��Ϣ�壺��TPollInfo + TMtPollParam����
   OSPEVENT( MCU_MCS_POLLPARAMCHANGE_NTF,   EV_MCSVC_BGN + 220 );
   //�������ָ̨����ѯλ��, ��Ϣ�壺TMt
   OSPEVENT( MCS_MCU_SPECPOLLPOS_REQ,		EV_MCSVC_BGN + 208 );
   //MCUӦ��������ָ̨����ѯλ��, ��Ϣ�壺��
   OSPEVENT( MCU_MCS_SPECPOLLPOS_ACK,		EV_MCSVC_BGN + 209 );
   //MCU�ܾ��������ָ̨����ѯλ��, ��Ϣ�壺��
   OSPEVENT( MCU_MCS_SPECPOLLPOS_NACK,		EV_MCSVC_BGN + 210 );
   


//3.4.1.2	��ѯ��ѯ����
   //�������̨��MCU��ѯ������ѯ����, ��Ϣ�壺  �� 
   OSPEVENT( MCS_MCU_GETPOLLPARAM_REQ,      EV_MCSVC_BGN + 215 );
   //MCUӦ��������̨��ѯ������ѯ����, ��Ϣ�壺  TPollInfo + TMtPollParam����
   OSPEVENT( MCU_MCS_GETPOLLPARAM_ACK,      EV_MCSVC_BGN + 216 ); 
   //MCU�ܾ��������̨��ѯ������ѯ����, ��Ϣ�壺  ��
   OSPEVENT( MCU_MCS_GETPOLLPARAM_NACK,     EV_MCSVC_BGN + 217 );
   //MCU֪ͨ�������̨��ǰ����ѯ״̬, ��Ϣ�壺  TPollInfo
   OSPEVENT( MCU_MCS_POLLSTATE_NOTIF,       EV_MCSVC_BGN + 218 );

   // EV_MCSVC_BGN+219 �� EV_MCSVC_BGN+220 �Ѿ��������õ���.

//����ǽ��ѯ
   //�������̨����û��鿪ʼ����ǽ��ѯ, ��Ϣ�壺  TTvWallPollInfo + TMtPollParam����
   OSPEVENT( MCS_MCU_STARTTWPOLL_CMD,       EV_MCSVC_BGN + 221 ); 
   //�������̨����û���ֹͣ����ǽ��ѯ, ��Ϣ�壺  ��
   OSPEVENT( MCS_MCU_STOPTWPOLL_CMD,        EV_MCSVC_BGN + 222 );
   //�������̨����û�����ͣ����ǽ��ѯ, ��Ϣ�壺  ��
   OSPEVENT( MCS_MCU_PAUSETWPOLL_CMD,       EV_MCSVC_BGN + 223 );
   //�������̨����û����������ǽ��ѯ, ��Ϣ�壺  ��
   OSPEVENT( MCS_MCU_RESUMETWPOLL_CMD,      EV_MCSVC_BGN + 224 );
   
   //�������̨��MCU��ѯ������ѯ����, ��Ϣ�壺  �� 
   OSPEVENT( MCS_MCU_GETTWPOLLPARAM_REQ,    EV_MCSVC_BGN + 225 );
   //MCUӦ��������̨��ѯ������ѯ����, ��Ϣ�壺  TTvWallPollInfo + TMtPollParam����
   OSPEVENT( MCU_MCS_GETTWPOLLPARAM_ACK,    EV_MCSVC_BGN + 226 ); 
   //MCU�ܾ��������̨��ѯ������ѯ����, ��Ϣ�壺  ��
   OSPEVENT( MCU_MCS_GETTWPOLLPARAM_NACK,   EV_MCSVC_BGN + 227 );
   //MCU֪ͨ�������̨��ǰ����ѯ״̬, ��Ϣ�壺  TTvWallPollInfo
   OSPEVENT( MCU_MCS_TWPOLLSTATE_NOTIF,     EV_MCSVC_BGN + 228 );
   
//3.4.2	������������
//3.4.2.1	���������������Ʒ���
   //�������̨����MCU��ʼ�����������Ʒ���, ��Ϣ�壺  ��
   OSPEVENT( MCS_MCU_STARTVAC_REQ ,         EV_MCSVC_BGN + 231 );
   //MCUͬ��������̨��ʼ�����������Ʒ��Ե�����, ��Ϣ�壺  ��
   OSPEVENT( MCU_MCS_STARTVAC_ACK,          EV_MCSVC_BGN + 232 );
   //MCU�ܾ��������̨��ʼ�����������Ʒ��Ե�����, ��Ϣ�壺  ��
   OSPEVENT( MCU_MCS_STARTVAC_NACK,         EV_MCSVC_BGN + 233 );
   //MCU���������̨��ʼ�����������Ʒ��Ե�֪ͨ, ��Ϣ�壺  ��
   OSPEVENT( MCU_MCS_STARTVAC_NOTIF,        EV_MCSVC_BGN + 234 );

//3.4.2.2	ȡ�������������Ʒ���
   //�������̨����MCUֹͣ�����������Ʒ���, ��Ϣ�壺  ��
   OSPEVENT( MCS_MCU_STOPVAC_REQ ,          EV_MCSVC_BGN + 241 );
   //MCUͬ��������ֹ̨ͣ�����������Ʒ��Ե�����, ��Ϣ�壺  ��
   OSPEVENT( MCU_MCS_STOPVAC_ACK,           EV_MCSVC_BGN + 242 );
   //MCU�ܾ��������ֹ̨ͣ�����������Ʒ��Ե�����, ��Ϣ�壺  ��
   OSPEVENT( MCU_MCS_STOPVAC_NACK,          EV_MCSVC_BGN + 243 );
   //MCU���������ֹ̨ͣ�����������Ʒ��Ե�֪ͨ, ��Ϣ�壺  ��
   OSPEVENT( MCU_MCS_STOPVAC_NOTIF,         EV_MCSVC_BGN + 244 );

//3.4.2.3  �ı����������л�ʱ��
   //�������̨����MCU�ı����������л�ʱ��, ��Ϣ�壺 1byte(��λ:��)
   OSPEVENT( MCS_MCU_CHANGEVACHOLDTIME_REQ,     EV_MCSVC_BGN + 245 );
   //MCUͬ��������̨�ı����������л�ʱ�������, ��Ϣ�壺 1byte(��λ:��)
   OSPEVENT( MCU_MCS_CHANGEVACHOLDTIME_ACK,     EV_MCSVC_BGN + 246 );
   //MCU�ܾ��������̨�ı����������л�ʱ�������, ��Ϣ�壺 1byte(��λ:��)
   OSPEVENT( MCU_MCS_CHANGEVACHOLDTIME_NACK,    EV_MCSVC_BGN + 247 );
   //MCU���������̨�ı����������л�ʱ���֪ͨ, ��Ϣ�壺  1byte(��λ:��)
   OSPEVENT( MCU_MCS_CHANGEVACHOLDTIME_NOTIF,   EV_MCSVC_BGN + 248 );

  
//3.4.3	��������/����
//3.4.3.1	��ʼ���ܻ���
    //��ʼ���ܻ�������, ��Ϣ�壺  NULL
	OSPEVENT( MCS_MCU_STARTDISCUSS_REQ,		EV_MCSVC_BGN + 250 );
	//MCUͬ�⿪ʼ���ܻ�������, ��Ϣ�壺  
	OSPEVENT( MCU_MCS_STARTDISCUSS_ACK,		EV_MCSVC_BGN + 251 );
	//MCU�ܾ���ʼ���ܻ�������, ��Ϣ�壺  
	OSPEVENT( MCU_MCS_STARTDISCUSS_NACK,	EV_MCSVC_BGN + 252 );

    //zbq[11/01/2007] �����Ż�
	//�������̨����MCU������������, ��Ϣ�壺  TMcu+1byte(ͬʱ�μ�����(����)�ĳ�Ա����)+TMt����(ָ����Ա����ʱ����)   - ���ڿ缶��ʼ���۲���
	//OSPEVENT( MCS_MCU_STARTDISCUSS_CMD,     EV_MCSVC_BGN + 253 );

	//MCU��ʼ��������֪ͨ, ��Ϣ�壺  TMcu+1byte(ͬʱ�μ�����(����)�ĳ�Ա����)
	//OSPEVENT( MCU_MCS_STARTDISCUSS_NOTIF,	EV_MCSVC_BGN + 254 );

//3.4.3.2	�������ܻ���
	//�������̨����MCU�������ܻ�������, ��Ϣ�壺��
	OSPEVENT( MCS_MCU_STOPDISCUSS_REQ,      EV_MCSVC_BGN + 255 );
	//MCUͬ��������̨�������ܻ���������, ��Ϣ�壺 
	OSPEVENT( MCU_MCS_STOPDISCUSS_ACK,      EV_MCSVC_BGN + 256 );
	//MCU�ܾ��������̨�������ܻ���������, ��Ϣ�壺  
	OSPEVENT( MCU_MCS_STOPDISCUSS_NACK,     EV_MCSVC_BGN + 257 );
	
    //zbq[11/01/2007] �����Ż�
    //�������̨����MCU������������, ��Ϣ�壺  TMcu   - ���ڿ缶ֹͣ���۲���
	//OSPEVENT( MCS_MCU_STOPDISCUSS_CMD,      EV_MCSVC_BGN + 258 );

	//MCU���������̨�����������۵�֪ͨ, ��Ϣ�壺  TMcu
	//OSPEVENT( MCU_MCS_STOPDISCUSS_NOTIF,	EV_MCSVC_BGN + 259 );

//3.4.3.3  ���ƻ�����Ա����(��һ��Add��Ϊ�������ƻ��������һ��Remove��Ϊֹͣ���ƻ���)
    //���ӻ�����Ա, ��Ϣ�壺TMt����
    OSPEVENT( MCS_MCU_ADDMIXMEMBER_CMD,	    EV_MCSVC_BGN + 265 );	
    
    //�Ƴ�������Ա, ��Ϣ�壺TMt����
    OSPEVENT( MCS_MCU_REMOVEMIXMEMBER_CMD,	EV_MCSVC_BGN + 268 );
    
    //�滻������Ա����Ϣ�壺TOldMt + TNewMt
    OSPEVENT( MCS_MCU_REPLACEMIXMEMBER_CMD,	EV_MCSVC_BGN + 273 );

//3.4.3.4	��ѯ��������
    
    //��ѯ������������, ��Ϣ�壺 ��
    OSPEVENT( MCS_MCU_GETMIXPARAM_REQ,	        EV_MCSVC_BGN + 260 );
    //MCUͬ���ѯ��������, ��Ϣ�壺u8 ö�� mcuNoMix ��
    OSPEVENT( MCU_MCS_GETMIXPARAM_ACK,	        EV_MCSVC_BGN + 261 );
    //MCU�ܾ���ѯ��������, ��Ϣ�壺  
    OSPEVENT( MCU_MCS_GETMIXPARAM_NACK,	        EV_MCSVC_BGN + 262 );
    //MCU���������̨�Ļ�������֪ͨ, ÿ�λ��������仯ʱ���͡���Ϣ�壺  u8 ö�� mcuNoMix ��
    OSPEVENT( MCU_MCS_MIXPARAM_NOTIF,	        EV_MCSVC_BGN + 263 );

    //zbq[11/01/2007] �����Ż���������Ϣ�ķ�ֹ�����ܵ��»�ص��޸����������
    //���ڱ�����Ϣ�Ĳ�����Ҫ�޸ģ������뷨�ǣ����ڻ���״̬�Ĳ�����ȡConfStatus���ն�״̬�Ĳ�����ȡMtStatus��
    /*
	//��ѯ���۲�������, ��Ϣ�壺  TMcu 
	OSPEVENT( MCS_MCU_GETDISCUSSPARAM_REQ,	EV_MCSVC_BGN + 260 );
	//MCUͬ���ѯ���۲���, ��Ϣ�壺  TMcu+TDiscussParam
	OSPEVENT( MCU_MCS_GETDISCUSSPARAM_ACK,	EV_MCSVC_BGN + 261 );
	//MCU�ܾ���ѯ���۲���, ��Ϣ�壺  TMcu
	OSPEVENT( MCU_MCS_GETDISCUSSPARAM_NACK,	EV_MCSVC_BGN + 262 );
	//MCU���������̨�����۲���֪ͨ, ��Ϣ�壺  TMcu+TDiscussParam
	OSPEVENT( MCU_MCS_DISCUSSPARAM_NOTIF,	EV_MCSVC_BGN + 263 );
    */

	//�ն�����������֪ͨ, ��Ϣ�壺TMt(�����ն�)
    OSPEVENT( MCU_MCS_MTAPPLYMIX_NOTIF,     EV_MCSVC_BGN + 270 );

    //������ʱ����, ��Ϣ��: u8 (��λ����)
    OSPEVENT( MCS_MCU_CHANGEMIXDELAY_REQ,   EV_MCSVC_BGN + 276 );
    //��Ϣ�壺��
    OSPEVENT( MCU_MCS_CHANGEMIXDELAY_ACK,   EV_MCSVC_BGN + 277 );
    //��Ϣ�壺��
    OSPEVENT( MCU_MCS_CHANGEMIXDELAY_NACK,  EV_MCSVC_BGN + 278 );
    //��Ϣ��: u8 (��λ����)
    OSPEVENT( MCU_MCS_CHANGEMIXDELAY_NOTIF, EV_MCSVC_BGN + 279 );

//3.4.4	��Ƶ���Ͽ���
//3.4.4.1	��ʼ��Ƶ����
	//��ʼ��Ƶ��������, ��Ϣ�壺  TVMPParam
	OSPEVENT( MCS_MCU_STARTVMP_REQ,         EV_MCSVC_BGN + 281 );
	//MCUͬ����Ƶ��������, ��Ϣ�壺 ��
	OSPEVENT( MCU_MCS_STARTVMP_ACK,         EV_MCSVC_BGN + 282 );
	//MCU��ͬ����Ƶ��������, ��Ϣ�壺 ��
	OSPEVENT( MCU_MCS_STARTVMP_NACK,        EV_MCSVC_BGN + 283 );
	//��Ƶ���ϳɹ���ʼ֪ͨ, ��Ϣ�壺  TVMPParam
	OSPEVENT( MCU_MCS_STARTVMP_NOTIF,       EV_MCSVC_BGN + 284 );
	

//3.4.4.2 ֹͣ��Ƶ����	
	//������Ƶ��������, ��Ϣ�壺  
	OSPEVENT( MCS_MCU_STOPVMP_REQ,		    EV_MCSVC_BGN + 291 );
	//MCUͬ����Ƶ������������, ��Ϣ�壺  ��
	OSPEVENT( MCU_MCS_STOPVMP_ACK,		    EV_MCSVC_BGN + 292 );
	//MCU��ͬ�������Ƶ��������, ��Ϣ�壺  ��
	OSPEVENT( MCU_MCS_STOPVMP_NACK,		    EV_MCSVC_BGN + 293 );
	//��Ƶ���ϳɹ�����֪ͨ, ��Ϣ�壺  ��
	OSPEVENT( MCU_MCS_STOPVMP_NOTIF,        EV_MCSVC_BGN + 294 );
	
//3.4.4.3	�ı���Ƶ���ϲ���
	//�������̨����MCU�ı���Ƶ���ϲ���, ��Ϣ�壺  TVMPParam
	OSPEVENT( MCS_MCU_CHANGEVMPPARAM_REQ,	EV_MCSVC_BGN + 301 );
	//MCUͬ��������̨�ĸı���Ƶ���ϲ�������, ��Ϣ�壺 TVMPParam
	OSPEVENT( MCU_MCS_CHANGEVMPPARAM_ACK,	EV_MCSVC_BGN + 302 );
	//MCU�ܾ��������̨�ĸı���Ƶ���ϲ�������, ��Ϣ�壺  ��
	OSPEVENT( MCU_MCS_CHANGEVMPPARAM_NACK,	EV_MCSVC_BGN + 303 );
    //��Ƶ���ϲ����ı�֪ͨ,��Ϣ�壺 TVMPParam
    OSPEVENT( MCU_MCS_CHANGEVMPPARAM_NOTIF, EV_MCSVC_BGN + 304 );

//3.4.4.4	��ѯ��Ƶ���ϲ���	
	//��ѯ��Ƶ��������Ա����, ��Ϣ�壺  �� 
	OSPEVENT( MCS_MCU_GETVMPPARAM_REQ,	    EV_MCSVC_BGN + 311 );
	//MCUͬ���ѯ��Ƶ���ϳ�Ա, ��Ϣ�壺  TVMPParam
	OSPEVENT( MCU_MCS_GETVMPPARAM_ACK,	    EV_MCSVC_BGN + 312 );
	//MCU��ͬ���ѯ��Ƶ���ϳ�Ա, ��Ϣ�壺  ��
	OSPEVENT( MCU_MCS_GETVMPPARAM_NACK,	    EV_MCSVC_BGN + 313 );
	//MCU���������̨����Ƶ���ϲ���֪ͨ, ��Ϣ�壺  TVMPParam
	OSPEVENT( MCU_MCS_VMPPARAM_NOTIF,	    EV_MCSVC_BGN + 314 );

//3.4.4.5	������Ƶ���㲥����
	//�������MCU�㲥��Ƶ��������, ��Ϣ����  
	OSPEVENT( MCS_MCU_STARTVMPBRDST_REQ,	EV_MCSVC_BGN + 320 );
	//MCUͬ��㲥��Ƶ��������, ��Ϣ����
	OSPEVENT( MCU_MCS_STARTVMPBRDST_ACK,	EV_MCSVC_BGN + 321 );
	//MCU�ܾ��㲥��Ƶ��������, ��Ϣ����
	OSPEVENT( MCU_MCS_STARTVMPBRDST_NACK,	EV_MCSVC_BGN + 322 );

	//�������MCUֹͣ�㲥��Ƶ��������, ��Ϣ����  
	OSPEVENT( MCS_MCU_STOPVMPBRDST_REQ,		EV_MCSVC_BGN + 325 );
	//MCUͬ��ֹͣ�㲥��Ƶ��������, ��Ϣ����
	OSPEVENT( MCU_MCS_STOPVMPBRDST_ACK,		EV_MCSVC_BGN + 326 );
	//MCU�ܾ�ֹͣ�㲥��Ƶ��������, ��Ϣ����
	OSPEVENT( MCU_MCS_STOPVMPBRDST_NACK,	EV_MCSVC_BGN + 327 );
//-----------------------------------------------------------------------


//3.4.4	���ϵ���ǽ
//3.4.4.1	��ʼ���ϵ���ǽ
    //��ʼ���ϵ���ǽ����, ��Ϣ�壺  TVMPParam
    OSPEVENT( MCS_MCU_STARTVMPTW_REQ,       EV_MCSVC_BGN + 330 );
    //MCUͬ�⸴�ϵ���ǽ����, ��Ϣ�壺 ��
    OSPEVENT( MCU_MCS_STARTVMPTW_ACK,       EV_MCSVC_BGN + 331 );
    //MCU��ͬ�⸴�ϵ���ǽ����, ��Ϣ�壺 ��
    OSPEVENT( MCU_MCS_STARTVMPTW_NACK,      EV_MCSVC_BGN + 332 );
    //���ϵ���ǽ�ɹ���ʼ֪ͨ, ��Ϣ�壺  TVMPParam
    OSPEVENT( MCU_MCS_STARTVMPTW_NOTIF,     EV_MCSVC_BGN + 333 );

//3.4.4.2 ֹͣ���ϵ���ǽ	
    //�������ϵ���ǽ����, ��Ϣ�壺  
    OSPEVENT( MCS_MCU_STOPVMPTW_REQ,        EV_MCSVC_BGN + 335 );
    //MCUͬ��������ϵ���ǽ����, ��Ϣ�壺  ��
    OSPEVENT( MCU_MCS_STOPVMPTW_ACK,        EV_MCSVC_BGN + 336 );
    //MCU��ͬ��������ϵ���ǽ����, ��Ϣ�壺  ��
    OSPEVENT( MCU_MCS_STOPVMPTW_NACK,       EV_MCSVC_BGN + 337 );
    //���ϵ���ǽ�ɹ�����֪ͨ, ��Ϣ�壺  ��
    OSPEVENT( MCU_MCS_STOPVMPTW_NOTIF,      EV_MCSVC_BGN + 338 );

//3.4.4.3	�ı临�ϵ���ǽ����
    //�������̨����MCU�ı临�ϵ���ǽ����, ��Ϣ�壺  TVMPParam
    OSPEVENT( MCS_MCU_CHANGEVMPTWPARAM_REQ, EV_MCSVC_BGN + 340 );
    //MCUͬ��������̨�ĸı临�ϵ���ǽ��������, ��Ϣ�壺 TVMPParam
    OSPEVENT( MCU_MCS_CHANGEVMPTWPARAM_ACK, EV_MCSVC_BGN + 341 );
    //MCU�ܾ��������̨�ĸı临�ϵ���ǽ��������, ��Ϣ�壺  ��
    OSPEVENT( MCU_MCS_CHANGEVMPTWPARAM_NACK,EV_MCSVC_BGN + 342 );

    //MCU���������̨����Ƶ���ϲ���֪ͨ, ��Ϣ�壺  TVMPParam
	OSPEVENT( MCU_MCS_VMPTWPARAM_NOTIF,     EV_MCSVC_BGN + 343 );
//-----------------------------------------------------------------------


//3.4.5	��ѯ����״̬
	//�������̨��MCU��ѯ����״̬, ��Ϣ�壺  ��
	OSPEVENT( MCS_MCU_GETCONFSTATUS_REQ,	EV_MCSVC_BGN + 351 );
	//MCU������ѯ����״̬Ӧ��, ��Ϣ�壺 TConfStatus 
	OSPEVENT( MCU_MCS_GETCONFSTATUS_ACK,	EV_MCSVC_BGN + 352 );
	//MCU�ܾ�������ѯ����״̬Ӧ��, ��Ϣ�壺 ��
	OSPEVENT( MCU_MCS_GETCONFSTATUS_NACK,	EV_MCSVC_BGN + 353 );
	//MCU���������̨�Ļ���״̬֪ͨ, ��Ϣ�壺 TConfStatus
	OSPEVENT( MCU_MCS_CONFSTATUS_NOTIF,	    EV_MCSVC_BGN + 354 );

	
	//�������̨����MCU��ˢ������MCU������, ��Ϣ�壺  TMcu
	OSPEVENT( MCS_MCU_REFRESHMCU_CMD,       EV_MCSVC_BGN + 355 );
	
	//�����м�����Mcuý��Դ����, ��Ϣ�壺  TMcu
	OSPEVENT( MCS_MCU_MCUMEDIASRC_REQ,      EV_MCSVC_BGN + 356 );
	//�����м�����Mcuý��Դ�ɹ�Ӧ��, ��Ϣ�壺  TMcu
	OSPEVENT( MCU_MCS_MCUMEDIASRC_ACK,      EV_MCSVC_BGN + 357 );
	//�����м�����Mcuý��Դʧ��Ӧ��, ��Ϣ�壺  TMcu
	OSPEVENT( MCU_MCS_MCUMEDIASRC_NACK,     EV_MCSVC_BGN + 358 );

	//�����м�����Mcuý��Դ֪ͨ,��Ϣ�壺  TMcu+TMt
	OSPEVENT( MCU_MCS_MCUMEDIASRC_NOTIF,    EV_MCSVC_BGN + 359 );

    //����ģʽ֪ͨ,��Ϣ�壺TConfMode
    OSPEVENT( MCU_MCS_CONFMODE_NOTIF,       EV_MCSVC_BGN + 360 );

//3.4.6 ��������
    //��ʼ��������, ��Ϣ�壺����ģʽ u8 (ROLLCALL_MODE_NONE ��)
    OSPEVENT( MCS_MCU_STARTROLLCALL_REQ,	EV_MCSVC_BGN + 285 );
    //MCUͬ�⿪ʼ�������� ��Ϣ�壺  ����ģʽ u8
    OSPEVENT( MCU_MCS_STARTROLLCALL_ACK,	EV_MCSVC_BGN + 286 );
    //MCU�ܾ���ʼ�������� ��Ϣ�壺  
    OSPEVENT( MCU_MCS_STARTROLLCALL_NACK,	EV_MCSVC_BGN + 287 );
    //MCU���������̨�Ŀ�ʼ����֪ͨ, ��Ϣ�壺  ����ģʽ u8
    OSPEVENT( MCU_MCS_STARTROLLCALL_NOTIF,	EV_MCSVC_BGN + 288 );
    
    //ֹͣ��������, ��Ϣ�壺
    OSPEVENT( MCS_MCU_STOPROLLCALL_REQ,		EV_MCSVC_BGN + 295 );
    //MCUͬ��ֹͣ�������� ��Ϣ�壺  
    OSPEVENT( MCU_MCS_STOPROLLCALL_ACK,		EV_MCSVC_BGN + 296 );
    //MCU�ܾ�ֹͣ�������� ��Ϣ�壺  
    OSPEVENT( MCU_MCS_STOPROLLCALL_NACK,	EV_MCSVC_BGN + 297 );
    //MCU���������̨��ֹͣ����֪ͨ, ��Ϣ�壺  
    OSPEVENT( MCU_MCS_STOPROLLCALL_NOTIF,	EV_MCSVC_BGN + 298 );
    
    //�����������, ��Ϣ�壺TMt��TMt
    OSPEVENT( MCS_MCU_CHANGEROLLCALL_REQ,	EV_MCSVC_BGN + 305 );
    //MCUͬ������������ ��Ϣ�壺  TMt��TMt
    OSPEVENT( MCU_MCS_CHANGEROLLCALL_ACK,	EV_MCSVC_BGN + 306 );
    //MCU�ܾ������������ ��Ϣ�壺  
    OSPEVENT( MCU_MCS_CHANGEROLLCALL_NACK,	EV_MCSVC_BGN + 307 );
    //MCU���������̨�ĵ������֪ͨ, ��Ϣ�壺  TMt��TMt
    OSPEVENT( MCU_MCS_CHANGEROLLCALL_NOTIF, EV_MCSVC_BGN + 308 );
    


//3.5	�ն˲���
//3.5.1	�����ն�
	//�������̨����MCU�����ն�, ��Ϣ�壺  TMt(�������ն�)
	OSPEVENT( MCS_MCU_CALLMT_REQ,			EV_MCSVC_BGN + 365 );
	//MCUͬ������ն�Ӧ��, ��Ϣ�壺  TMt(����ն�)
	OSPEVENT( MCU_MCS_CALLMT_ACK,			EV_MCSVC_BGN + 366 );
	//MCU�ܾ������ն�, ��Ϣ�壺  ��
	OSPEVENT( MCU_MCS_CALLMT_NACK,			EV_MCSVC_BGN + 367 );
    //�ն�����״̬�仯֪ͨ, ��Ϣ�壺  TMt+1byte(״̬:0-���� 1-����)+1byte(����ԭ��: 0(MTLEFT_REASON_EXCEPT)-�쳣 1-�����Ҷ� 2-��·�� 3-���Ͳ�ƥ��)
    OSPEVENT( MCU_MCS_MTONLINECHANGE_NOTIF,	EV_MCSVC_BGN + 368 );
    //�ն˺��в��ɹ�֪ͨ, ��Ϣ�壺  TMt+ (��ԭ��ΪERR_MCU_VCS_MTBUSY, ��Ϣ��+ s8[MAXLEN_CONFNAME](��ǰ���ڻ��������))  ԭ���������
    OSPEVENT( MCU_MCS_CALLMTFAILURE_NOTIF,	EV_MCSVC_BGN + 369 );


//3.5.2	���ú����ն˷�ʽ
	//�������̨����MCU�����ն˷�ʽ, ��Ϣ�壺  TMt(�������ն�)+1byte(���з�ʽ)
	OSPEVENT( MCS_MCU_SETCALLMTMODE_REQ,	EV_MCSVC_BGN + 371 );
	//�ɹ�����MCU�����ն˷�ʽ  ��Ϣ�壺  TMt(�������ն�)+1byte(���з�ʽ)
	OSPEVENT( MCU_MCS_SETCALLMTMODE_ACK,	EV_MCSVC_BGN + 372 );
	//�ܾ�����MCU�����ն˷�ʽ, ��Ϣ�壺  ��
	OSPEVENT( MCU_MCS_SETCALLMTMODE_NACK,	EV_MCSVC_BGN + 373 );
	//MCU�����ն˷�ʽ֪ͨ  ��Ϣ�壺  TMtExt
	OSPEVENT( MCU_MCS_CALLMTMODE_NOTIF,		EV_MCSVC_BGN + 374 );
	

//3.5.3	�Ҷ��ն�
	//�������̨�Ҷ��ն�����, ��Ϣ�壺  TMt (���Ҷ��ն�)
	OSPEVENT( MCS_MCU_DROPMT_REQ,			EV_MCSVC_BGN + 381 );
	//�ն˱��ɹ��Ҷ�   ��Ϣ�壺  ��
	OSPEVENT( MCU_MCS_DROPMT_ACK,			EV_MCSVC_BGN + 382 );
	//MCU�ܾ��Ҷϸ��ն�, ��Ϣ�壺  ��
	OSPEVENT( MCU_MCS_DROPMT_NACK,			EV_MCSVC_BGN + 383 );


//3.5.4	ǿ���ն�ѡ��
	//���ǿ��Ŀ���ն�ѡ��Դ�ն�, ��Ϣ�壺  TSwitchInfo
	OSPEVENT( MCS_MCU_STARTSWITCHMT_REQ,	EV_MCSVC_BGN + 391 );
	//MCUӦ����ǿ��Ŀ���ն�ѡ��Դ�ն�, ��Ϣ�壺  TSwitchInfo
	OSPEVENT( MCU_MCS_STARTSWITCHMT_ACK,	EV_MCSVC_BGN + 392 );
	//�ܾ����ǿ��Ŀ���ն�ѡ��Դ�ն�, ��Ϣ�壺  ��
	OSPEVENT( MCU_MCS_STARTSWITCHMT_NACK,	EV_MCSVC_BGN + 393 );



//3.5.5	ȡ���ն�ѡ��  
	//���ȡ��Ŀ���ն�ѡ��Դ�ն�, ��Ϣ�壺  TSwitchInfo
	OSPEVENT( MCS_MCU_STOPSWITCHMT_REQ,		EV_MCSVC_BGN + 401 );
	//MCUӦ����ȡ��Ŀ���ն�ѡ��Դ�ն�, ��Ϣ�壺  TSwitchInfo
	OSPEVENT( MCU_MCS_STOPSWITCHMT_ACK,		EV_MCSVC_BGN + 402 );
	//MCU�ܾ����ȡ��Ŀ���ն�ѡ��Դ�ն�, ��Ϣ�壺  ��
	OSPEVENT( MCU_MCS_STOPSWITCHMT_NACK,	EV_MCSVC_BGN + 403 );


//3.5.6	��ѯ�ն�״̬
	//�����MCU��ѯ�ն�״̬, ��Ϣ�壺  TMt(Ҫ��ѯ���ն�)
	OSPEVENT( MCS_MCU_GETMTSTATUS_REQ,		EV_MCSVC_BGN + 411 );
	//MCUӦ��������̨��ѯ�ն�״̬, ��Ϣ�壺  TMtStatus
	OSPEVENT( MCU_MCS_GETMTSTATUS_ACK,		EV_MCSVC_BGN + 412 );
	//MCU�ܾ��������̨�Ĳ�ѯ�ն�״̬, ��Ϣ�壺  ��
	OSPEVENT( MCU_MCS_GETMTSTATUS_NACK,		EV_MCSVC_BGN + 413 );
	//MCU���������̨�Ĳ�ѯ�ն�״̬֪ͨ, ��Ϣ�壺  TMtStatus���� 
	OSPEVENT( MCU_MCS_MTSTATUS_NOTIF,		EV_MCSVC_BGN + 414 );
	
	//�����MCU��ѯ�����ն�״̬, ��Ϣ�壺  TMCU
	OSPEVENT( MCS_MCU_GETALLMTSTATUS_REQ,	EV_MCSVC_BGN + 395 );
	//MCUӦ��������̨��ѯ�����ն�״̬, ��Ϣ�壺  TMCU + TMtStatus���� 
	OSPEVENT( MCU_MCS_GETALLMTSTATUS_ACK,	EV_MCSVC_BGN + 396 );
	//MCU�ܾ��������̨�Ĳ�ѯ�����ն�״̬, ��Ϣ�壺  TMCU
	OSPEVENT( MCU_MCS_GETALLMTSTATUS_NACK,	EV_MCSVC_BGN + 397 );
	//MCU���������̨�������ն�״̬֪ͨ, ��Ϣ�壺  TMCU + TMtStatus���� 
	OSPEVENT( MCU_MCS_ALLMTSTATUS_NOTIF,	EV_MCSVC_BGN + 398 );

//3.5.7 ��ѯ�ն˱���
	//�����MCU��ѯ�ն˱���, ��Ϣ�壺  TMt(Ҫ��ѯ���ն�)
	OSPEVENT( MCS_MCU_GETMTALIAS_REQ,		EV_MCSVC_BGN + 415 );
	//MCUӦ��������̨��ѯ�ն˱���, ��Ϣ�壺  TMt+TMtAlias����
	OSPEVENT( MCU_MCS_GETMTALIAS_ACK,		EV_MCSVC_BGN + 416 );
	//MCUû���ն˵ı�����Ϣ, ��Ϣ�壺  TMt(Ҫ��ѯ���ն�)
	OSPEVENT( MCU_MCS_GETMTALIAS_NACK,		EV_MCSVC_BGN + 417 );
	//MCU���������̨���ն˱���֪ͨ, ��Ϣ�壺  TMt+TMtAlias����
	OSPEVENT( MCU_MCS_MTALIAS_NOTIF,		EV_MCSVC_BGN + 418 );

	//�����MCU��ѯ�����ն˱���, ��Ϣ�壺  TMCU
	OSPEVENT( MCS_MCU_GETALLMTALIAS_REQ,	EV_MCSVC_BGN + 405 );
	//MCUӦ��������̨��ѯ�����ն˱���, ��Ϣ�壺  TMCU
	OSPEVENT( MCU_MCS_GETALLMTALIAS_ACK,	EV_MCSVC_BGN + 406 );
	//MCU�ܾ��������̨�Ĳ�ѯ�����ն˱���, ��Ϣ�壺  TMCU
	OSPEVENT( MCU_MCS_GETALLMTALIAS_NACK,	EV_MCSVC_BGN + 407 );
	//MCU���������̨�Ĳ�ѯ�����ն˱���֪ͨ, 
    //��Ϣ�壺 ĳMcu��McuId(u8) + �ն˸���n(u8) + n*ÿ���ն˱����������(MtId(u8)+ ��������m(u8) + m*(��������(u8)+��������(u8)+����(����\0)) )
	OSPEVENT( MCU_MCS_ALLMTALIAS_NOTIF,		EV_MCSVC_BGN + 408 );

//3.5.8	�����ն�����
	//�������̨����MCU�����ն�����, ��Ϣ�壺  TMt + u16 (��������(��λ:Kbps,1K=1024)������)
	OSPEVENT( MCS_MCU_SETMTBITRATE_CMD,     EV_MCSVC_BGN + 421 );
    
    //�������̨��ѯ�ն����ʣ���Ϣ�壺TMt (��TMtΪ��Ĭ��Ϊ���������ն�����)
    OSPEVENT( MCS_MCU_GETMTBITRATE_REQ,     EV_MCSVC_BGN + 423 );
    //��Ϣ�壺��
    OSPEVENT( MCU_MCS_GETMTBITRATE_ACK,     EV_MCSVC_BGN + 424 );
    //��Ϣ�壺��
    OSPEVENT( MCU_MCS_GETMTBITRATE_NACK,    EV_MCSVC_BGN + 425 ); 
    //�����ն�����֪ͨ, ��Ϣ�壺TMtBitrate
    OSPEVENT( MCU_MCS_MTBITRATE_NOTIF,      EV_MCSVC_BGN + 426 );

//3.5.9	�����ն���ƵԴ
	//���Ҫ��MCU�����ն���ƵԴ, ��Ϣ�壺  TMt(Ҫ���õ��ն�)+1byte(��ƵԴ����0:S���� 1-16:C����)
	OSPEVENT( MCS_MCU_SETMTVIDSRC_CMD,		EV_MCSVC_BGN + 431 );

//3.5.10 �ն���Ϣ��ȡ
    //��������ն���Ϣ����Ϣ�壺 TMt(��������ն�,  tMt.IsNull()��ʾ��������)
    OSPEVENT( MCS_MCU_GETMTEXTINFO_REQ,     EV_MCSVC_BGN + 440 );
    //��Ϣ�壺TMtExt2
    OSPEVENT( MCU_MCS_GETMTEXTINFO_ACK,     EV_MCSVC_BGN + 441 );
    //��Ϣ�壺TMtExt2
    OSPEVENT( MCU_MCS_GETMTEXTINFO_NACK,    EV_MCSVC_BGN + 442 );
    

//3.5.12	�����ն˾���
	//���Ҫ��MCU�����ն˾���, ��Ϣ�壺  TMt +1byte(1- MUTE 0-NOMUTE)+1byte(1-DECODER 2-CAPTURE)
	OSPEVENT( MCS_MCU_MTAUDMUTE_REQ,		EV_MCSVC_BGN + 451 );
	//MCUӦ��������̨�����ն˾���, ��Ϣ�壺TMt +1byte(1- MUTE 0-NOMUTE)+1byte(1-DECODER 2-CAPTURE) 
	OSPEVENT( MCU_MCS_MTAUDMUTE_ACK,		EV_MCSVC_BGN + 452 );
	//MCU�ܾ��������̨�����ն˾���, ��Ϣ�壺  TMt
	OSPEVENT( MCU_MCS_MTAUDMUTE_NACK,		EV_MCSVC_BGN + 453 );
	//MCU֪ͨ�������̨�����ն˾���, ��Ϣ�壺  TMt +1byte(1- MUTE 0-NOMUTE)+1byte(1-DECODER 2-CAPTURE)
	OSPEVENT( MCU_MCS_MTAUDMUTE_NOTIF,		EV_MCSVC_BGN + 454 );
	

//3.5.13	�ն�����ͷ����
	//�������̨�����ն��������ͷ�˶�����, ��Ϣ�壺  TMt +1byte(�μ�����ͷ���Ʋ�������)
	OSPEVENT( MCS_MCU_MTCAMERA_CTRL_CMD,	    EV_MCSVC_BGN + 461 );
	//�������̨�����ն��������ͷֹͣ�˶�����, ��Ϣ�壺  TMt +1byte(�μ�����ͷ���Ʋ�������)
	OSPEVENT( MCS_MCU_MTCAMERA_CTRL_STOP,	    EV_MCSVC_BGN + 462 );
	//�������̨�����ն������ң��ʹ�ܣ���Ϣ�壺  TMt +1byte(1-ENABLE 0-DISABLE) 
	OSPEVENT( MCS_MCU_MTCAMERA_RCENABLE_CMD,	EV_MCSVC_BGN + 463 );
	//�������̨�����ն����������ǰλ����Ϣ����ָ��λ�ã���Ϣ�壺  TMt +1byte(1��4��Ԥ��λ�ú�) 
	OSPEVENT( MCS_MCU_MTCAMERA_SAVETOPOS_CMD,	EV_MCSVC_BGN + 464 );
	//�������̨�����ն������������ָ��λ�ã���Ϣ�壺  TMt +1byte(1��4��Ԥ��λ�ú�) 
	OSPEVENT( MCS_MCU_MTCAMERA_MOVETOPOS_CMD,	EV_MCSVC_BGN + 465 );

	
//3.5.14�й���Ƶ���þ������    
    
    //���о��󷽰�����  MC->ter, ��Ϣ�壺TMt
    OSPEVENT( MCS_MCU_MATRIX_GETALLSCHEMES_CMD,     EV_MCSVC_BGN + 470 );
    //���о��󷽰���Ϣ֪ͨ����Ϣ��Ϊ��TMt +u8( ������ ) + ITInnerMatrixScheme[]
    OSPEVENT( MCU_MCS_MATRIX_ALLSCHEMES_NOTIF,      EV_MCSVC_BGN + 473 );
    
    //�������󷽰�����  MC->ter, ��Ϣ�壺TMt +u8 ( 0 ΪĬ�Ϸ��� )       ����������( 0 - 6 )
    OSPEVENT( MCS_MCU_MATRIX_GETONESCHEME_CMD,      EV_MCSVC_BGN + 474 );
    //��Ϣ�壺TMt +ITInnerMatrixScheme
    OSPEVENT( MCU_MCS_MATRIX_ONESCHEME_NOTIF,       EV_MCSVC_BGN + 477 );
    
    //������󷽰�����,��Ϣ��:TMt +ITInnerMatrixScheme
    OSPEVENT( MCS_MCU_MATRIX_SAVESCHEME_CMD,		EV_MCSVC_BGN + 478 );
    //��Ϣ�壺TMt +ITInnerMatrixScheme
    OSPEVENT( MCU_MCS_MATRIX_SAVESCHEME_NOTIF,      EV_MCSVC_BGN + 481 );
    
    //ָ����ǰ����,��Ϣ�壺TMt +u8  ��������
    OSPEVENT( MCS_MCU_MATRIX_SETCURSCHEME_CMD,      EV_MCSVC_BGN + 482 );
    //��Ϣ�壺TMt +u8  ��������
    OSPEVENT( MCU_MCS_MATRIX_SETCURSCHEME_NOTIF,    EV_MCSVC_BGN + 485 );
    
    //��ȡ��ǰ����,��Ϣ�壺TMt 
    OSPEVENT( MCS_MCU_MATRIX_GETCURSCHEME_CMD,      EV_MCSVC_BGN + 486 );
    //��Ϣ�壺TMt +u8  ��������
    OSPEVENT( MCU_MCS_MATRIX_CURSCHEME_NOTIF,       EV_MCSVC_BGN + 489 );
    
// 3.5.15 �ն���������

    //�������̨�����ն���������Ϣ�壺TMt + u8(�������� VOLUME_TYPE_IN ...) + u8(�����������)
    //PCMT��������Χ��0-255����ͨKeda�ն˵�������Χ��0-32
    OSPEVENT( MCS_MCU_SETMTVOLUME_CMD,              EV_MCSVC_BGN + 490 );
    

//DSC�汾����
	//mcs֪ͨ8000B/C����DSC�汾, zgc, 20070820
	//��Ϣ�壺u8(��������) + u8(�ļ�������) + u8(�ļ�һ������) + s8[](�ļ�һ��) + u8(�ļ���������) + s8[](�ļ�����) + ���� ע��(�ļ�����������·��)
	OSPEVENT( MCS_MCU_STARTUPDATEDSCVERSION_REQ,	EV_MCSVC_BGN + 492 );
	//MCUͬ���������
	//��Ϣ�壺u8(��������) + u8(�ļ�������) + u8(�ļ�һ������) + s8[](�ļ�һ��) + u8(�ļ���������) + s8[](�ļ�����) + ���� ע��(�ļ�����������·��)
	OSPEVENT( MCU_MCS_STARTUPDATEDSCVERSION_ACK,	EV_MCSVC_BGN + 493 );
	//MCU��ͬ���������
	//��Ϣ�壺u8(��������) + u8(�ļ�������) + u8(�ļ�һ������) + s8[](�ļ�һ��) + u8(�ļ���������) + s8[](�ļ�����) + ���� ע��(�ļ�����������·��)
	OSPEVENT( MCU_MCS_STARTUPDATEDSCVERSION_NACK,	EV_MCSVC_BGN + 494 );
	//MCS��MCU���������ļ����ݰ�����
	//��Ϣ�壺u8(��������) + TDscUpdateReqHead + [filecontent]����
	OSPEVENT( MCS_MCU_DSCUPDATEFILE_REQ,			EV_MCSVC_BGN + 495 );
	//MCU��MCS�����Ľ��ճɹ���Ӧ
	//��Ϣ�壺u8(��������) + TDscUpdateRsp����д��һ֡��ţ�
	OSPEVENT( MCU_MCS_DSCUPDATEFILE_ACK,		EV_MCSVC_BGN + 496 );
	//MCU��MCS�����Ľ���ʧ�ܻ�Ӧ
	//��Ϣ�壺u8(��������) + TDscUpdateRsp����д��֡��ţ���ͬ��֪ͨ����ط���
	OSPEVENT( MCU_MCS_DSCUPDATEFILE_NACK,		EV_MCSVC_BGN + 497 );

//3.6	�������
//3.6.1	¼���������
//3.6.1.1	¼�����
//3.6.1.1.1	����¼��
    //�����MCU����¼��
    //��Ϣ��ΪTMt(��¼����նˣ����MCU��Ϊ�գ���ʾ�Ի���¼����������ͬ)
    // + TEqp(��Ҫʹ�õ�¼���) + TRecStartPara(¼�����) + ¼����(0��β�ַ���)
    OSPEVENT( MCS_MCU_STARTREC_REQ,		    EV_MCSVC_BGN + 501 );
    //MCUͬ���ط�������,��Ϣ��TMt + TEqp
    OSPEVENT( MCU_MCS_STARTREC_ACK,		    EV_MCSVC_BGN + 502 );
    //MCU�ܾ���ط�������,��Ϣ��TMt + TEqp
    OSPEVENT( MCU_MCS_STARTREC_NACK,	    EV_MCSVC_BGN + 503 );
    
    //MCS��ѯ¼����ȣ���Ϣ�壺TMt����Ϊ����Ϊ���飩
    OSPEVENT( MCS_MCU_GETRECPROG_CMD,       EV_MCSVC_BGN + 504 );
    //MCU֪ͨ���¼�����, ��Ϣ�壺  TMt + TEqp+TRecProg
    OSPEVENT( MCU_MCS_RECPROG_NOTIF,        EV_MCSVC_BGN + 505 );

//3.6.1.1.2	��ͣ¼������
	//�����MCU��ͣ¼�� TMt
	OSPEVENT( MCS_MCU_PAUSEREC_REQ,		    EV_MCSVC_BGN + 506 );
	//MCUͬ������ͣ��������,��Ϣ��TMt
	OSPEVENT( MCU_MCS_PAUSEREC_ACK,		    EV_MCSVC_BGN + 507 );
	//MCU�ܾ������ͣ��������,��Ϣ��TMt
	OSPEVENT( MCU_MCS_PAUSEREC_NACK,	    EV_MCSVC_BGN + 508 );

//3.6.1.1.3	�ָ�¼��
	//�����MCU�ָ�¼�� TMt
	OSPEVENT( MCS_MCU_RESUMEREC_REQ,		EV_MCSVC_BGN + 511 );
	//MCUͬ���ػָ���������,��Ϣ��TMt
	OSPEVENT( MCU_MCS_RESUMEREC_ACK,		EV_MCSVC_BGN + 512 );
	//MCU�ܾ���ػָ���������,��Ϣ��TMt
	OSPEVENT( MCU_MCS_RESUMEREC_NACK,		EV_MCSVC_BGN + 513 );


//3.6.1.1.4	ֹͣ¼��
	//�����MCUֹͣ¼��TMt
	OSPEVENT( MCS_MCU_STOPREC_REQ,		    EV_MCSVC_BGN + 515 );
	//MCUͬ����ֹͣ��������,��Ϣ��TMt
	OSPEVENT( MCU_MCS_STOPREC_ACK,		    EV_MCSVC_BGN + 516 );
	//MCU�ܾ����ֹͣ��������,��Ϣ��TMt
	OSPEVENT( MCU_MCS_STOPREC_NACK,		    EV_MCSVC_BGN + 517 );

//3.6.1.1.5	�ı�¼��ģʽ
	//�ı�¼��ģʽ����, ��Ϣ��TMt �� u8( REC_MODE_NORMAL, REC_MODE_SKIPFRAME )
	OSPEVENT( MCS_MCU_CHANGERECMODE_REQ,	EV_MCSVC_BGN + 520 );
	//ͬ�⣬MCU->MCS����Ϣ��Ϊ TMt 
	OSPEVENT( MCU_MCS_CHANGERECMODE_ACK,	EV_MCSVC_BGN + 521 );
	//���ԣ�MCU->MCS����Ϣ��Ϊ TMt 
	OSPEVENT( MCU_MCS_CHANGERECMODE_NACK,	EV_MCSVC_BGN + 522 );   

//3.6.1.2	�������
//3.6.1.2.1	��ʼ����
	//��ؿ�ʼ��������, ��Ϣ�壺  TEqp + u8(�Ƿ�˫������) + ¼����(0��β�ַ���)
	OSPEVENT( MCS_MCU_STARTPLAY_REQ,        EV_MCSVC_BGN + 530 );
	//MCU��ʼ����Ӧ��, ��Ϣ�壺  TEqp
	OSPEVENT( MCU_MCS_STARTPLAY_ACK,        EV_MCSVC_BGN + 531 );
	//MCU�ܾ���ʼ����, ��Ϣ�壺  TEqp
	OSPEVENT( MCU_MCS_STARTPLAY_NACK,       EV_MCSVC_BGN + 532 );
	
    //MCS��ѯ�������, ��Ϣ��:��
    OSPEVENT( MCS_MCU_GETPLAYPROG_CMD,      EV_MCSVC_BGN + 533 );
    //�������֪ͨ,��Ϣ�壺  TEqp+TRecProg
	OSPEVENT( MCU_MCS_PLAYPROG_NOTIF,       EV_MCSVC_BGN + 534 );
	

//3.6.1.2.2	��ͣ����
	//�����ͣ��������, ��Ϣ�壺  TEqp
	OSPEVENT( MCS_MCU_PAUSEPLAY_REQ,        EV_MCSVC_BGN + 535 );
	//MCU��ͣ����Ӧ��, ��Ϣ�壺  TEqp
	OSPEVENT( MCU_MCS_PAUSEPLAY_ACK,        EV_MCSVC_BGN + 536 );
	//MCU�ܾ���ͣ����, ��Ϣ�壺  TEqp
	OSPEVENT( MCU_MCS_PAUSEPLAY_NACK,       EV_MCSVC_BGN + 537 );

//3.6.1.2.3	�ָ�����
	//��ػָ���������, ��Ϣ�壺  TEqp
	OSPEVENT( MCS_MCU_RESUMEPLAY_REQ,       EV_MCSVC_BGN + 540 );
	//MCU�ָ�����Ӧ��, ��Ϣ�壺  TEqp
	OSPEVENT( MCU_MCS_RESUMEPLAY_ACK,       EV_MCSVC_BGN + 541 );
	//MCU�ܾ��ָ�����, ��Ϣ�壺  TEqp
	OSPEVENT( MCU_MCS_RESUMEPLAY_NACK,      EV_MCSVC_BGN + 542 );

//3.6.1.2.4	ֹͣ����
	//���ֹͣ��������, ��Ϣ�壺  TEqp
	OSPEVENT( MCS_MCU_STOPPLAY_REQ,         EV_MCSVC_BGN + 545 );
	//MCUֹͣ����Ӧ��, ��Ϣ�壺  TEqp
	OSPEVENT( MCU_MCS_STOPPLAY_ACK,         EV_MCSVC_BGN + 546 );
	//MCUֹͣ�ָ�����, ��Ϣ�壺  TEqp
	OSPEVENT( MCU_MCS_STOPPLAY_NACK,        EV_MCSVC_BGN + 547 );


//3.6.1.2.5	����������
	//��ؿ����������, ��Ϣ�壺  TEqp���������(u8)
	OSPEVENT( MCS_MCU_FFPLAY_REQ,           EV_MCSVC_BGN + 550 );
	//MCU�������Ӧ��, ��Ϣ�壺  TEqp
	OSPEVENT( MCU_MCS_FFPLAY_ACK,           EV_MCSVC_BGN + 551 );
	//MCU�������, ��Ϣ�壺  TEqp
	OSPEVENT( MCU_MCS_FFPLAY_NACK,          EV_MCSVC_BGN + 552 );

//3.6.1.2.6	������˷���
//��ؿ��˷�������, ��Ϣ�壺  TEqp���������(u8)
	OSPEVENT( MCS_MCU_FBPLAY_REQ,           EV_MCSVC_BGN + 555 );
	//MCU�������Ӧ��, ��Ϣ�壺  TEqp
	OSPEVENT( MCU_MCS_FBPLAY_ACK,           EV_MCSVC_BGN + 556 );
	//MCU�������, ��Ϣ�壺  TEqp
	OSPEVENT( MCU_MCS_FBPLAY_NACK,          EV_MCSVC_BGN + 557 );


//3.6.1.2.7	������ȵ���
    //��ص��������������, ��Ϣ�壺  TEqp��TRecProg
	OSPEVENT( MCS_MCU_SEEK_REQ,             EV_MCSVC_BGN + 560 );
	//MCUͬ������������Ӧ��, ��Ϣ�壺  TEqp
	OSPEVENT( MCU_MCS_SEEK_ACK,             EV_MCSVC_BGN + 561 );
	//MCU�ܾ������������Ӧ��, ��Ϣ�壺  TEqp
	OSPEVENT( MCU_MCS_SEEK_NACK,            EV_MCSVC_BGN + 562 );
	//��Ϣ����������¼�����쳣֪ͨ, ��Ϣ�壺  TEqp
	OSPEVENT( MCU_MCS_RECORDEREXCPT_NOTIF,  EV_MCSVC_BGN + 563 );
   
//3.6.1.3	��ѯ����¼�ļ�����
//3.6.1.3.1	��ѯ¼���״̬
	//��ѯ¼���״̬, ��Ϣ�壺  TEqp
	OSPEVENT( MCS_MCU_GETRECSTATUS_REQ,     EV_MCSVC_BGN + 570 );
	//MCU��ѯ¼���״̬Ӧ��, ��Ϣ�壺  TPeriEqpStatus.
	OSPEVENT( MCU_MCS_GETRECSTATUS_ACK,     EV_MCSVC_BGN + 571 );
	//MCU��ѯ¼���״̬�ܾ�, ��Ϣ�壺  TEqp
	OSPEVENT( MCU_MCS_GETRECSTATUS_NACK,    EV_MCSVC_BGN + 572 );

//3.6.1.3.2	��¼�б�����
    //��ز�ѯ��¼����, ��Ϣ�壺  TEqp��
	OSPEVENT( MCS_MCU_LISTALLRECORD_REQ,    EV_MCSVC_BGN + 575 );
	//��ѯ��¼Ӧ��, ��Ϣ�壺  TEqp
	OSPEVENT( MCU_MCS_LISTALLRECORD_ACK,    EV_MCSVC_BGN + 576 );
	//��ѯ��¼�ܾ�, ��Ϣ�壺  TEqp
	OSPEVENT( MCU_MCS_LISTALLRECORD_NACK,   EV_MCSVC_BGN + 577 );
    //¼����б�֪ͨ��Ϣ, ��Ϣ��ΪTEqp+TRecFileListNotify
    OSPEVENT( MCU_MCS_LISTALLRECORD_NOTIF,	EV_MCSVC_BGN + 578 );


//3.6.1.3.3	ɾ����¼�ļ�����
	//�������ɾ���ļ�, ��Ϣ�壺  TEqp+��¼����
	OSPEVENT( MCS_MCU_DELETERECORD_REQ,     EV_MCSVC_BGN + 580 );
	//�������ɾ���ļ�Ӧ��, ��Ϣ�壺  TEqp
	OSPEVENT( MCU_MCS_DELETERECORD_ACK,     EV_MCSVC_BGN + 581 );
	//�������ɾ���ļ��ܾ�, ��Ϣ�壺  TEqp
	OSPEVENT( MCU_MCS_DELETERECORD_NACK,    EV_MCSVC_BGN + 582 );

//3.6.1.3.4 �������MCU���ļ�¼�ļ�(�¾�����Ҫ��·��)
	//���ļ�¼�ļ�����, ��Ϣ��ΪTEqp + u8(�ɼ�¼������) + �ɼ�¼�� + u8(�¼�¼������) + �¼�¼�� 
    //�¾����ƶ�Ҫ��·��������·������Ӧ���޸�
	OSPEVENT( MCS_MCU_RENAMERECORD_REQ,     EV_MCSVC_BGN + 583 );
	//ͬ�⣬��Ϣ��ΪTEqp
	OSPEVENT( MCU_MCS_RENAMERECORD_ACK,     EV_MCSVC_BGN + 584 );
	//���ԣ���Ϣ��ΪTEqp
	OSPEVENT( MCU_MCS_RENAMERECORD_NACK,    EV_MCSVC_BGN + 585 );

//3.6.1.4 �ļ���������
//3.6.1.4.1 �������MCU�����ļ�
	//����¼������ ��Ϣ��ΪTEqp + u8(PUBLISH_LEVEL) + ¼����
	OSPEVENT( MCS_MCU_PUBLISHREC_REQ,		EV_MCSVC_BGN + 590 );
	//ͬ�⣬��Ϣ��ΪTEqp + u8(PUBLISH_LEVEL) + ¼����
	OSPEVENT( MCU_MCS_PUBLISHREC_ACK,		EV_MCSVC_BGN + 591 );
	//���ԣ���Ϣ��ΪTEqp + u8(PUBLISH_LEVEL) + ¼����
	OSPEVENT( MCU_MCS_PUBLISHREC_NACK,		EV_MCSVC_BGN + 592 );
	
//3.6.1.4.2 �������MCUȡ�������ļ�
	//����¼������ ��Ϣ��ΪTEqp + u8(PUBLISH_LEVEL) + ¼����
	OSPEVENT( MCS_MCU_CANCELPUBLISHREC_REQ,	EV_MCSVC_BGN + 595 );
	//ͬ�⣬��Ϣ��ΪTEqp + u8(PUBLISH_LEVEL) + ¼����
	OSPEVENT( MCU_MCS_CANCELPUBLISHREC_ACK,	EV_MCSVC_BGN + 596 );
	//���ԣ���Ϣ��ΪTEqp + u8(PUBLISH_LEVEL) + ¼����
	OSPEVENT( MCU_MCS_CANCELPUBLISHREC_NACK,EV_MCSVC_BGN + 597 );


//3.6.2	����������
	//��ѯ����������, ��Ϣ�壺  TEqp
	OSPEVENT( MCS_MCU_GETMIXERSTATUS_REQ,   EV_MCSVC_BGN + 641 );
	//��ѯ����������Ӧ��, ��Ϣ�壺  TPeriEqpStatus
	OSPEVENT( MCU_MCS_GETMIXERSTATUS_ACK,   EV_MCSVC_BGN + 642 );
	//��ѯ����������ܾ�, ��Ϣ�壺  TEqp
	OSPEVENT( MCU_MCS_GETMIXERSTATUS_NACK,  EV_MCSVC_BGN + 643 );

//3.6.3	����ǽ����
	//�������̨����ָ��Mt��ͼ�񽻻���ָ������ǽ��ָ��������ͨ����,��Ϣ�� TTWSwitchInfo
	OSPEVENT( MCS_MCU_START_SWITCH_TW_REQ,  EV_MCSVC_BGN + 651 );
	//MCUͬ�⿪ʼ����ͼ��, ��Ϣ�� ��
	OSPEVENT( MCU_MCS_START_SWITCH_TW_ACK,  EV_MCSVC_BGN + 652 );
	//MCU�ܾ���ʼ����ͼ��, ��Ϣ�� ��
	OSPEVENT( MCU_MCS_START_SWITCH_TW_NACK, EV_MCSVC_BGN + 653 );

	//�������̨����ֹͣ��ָ��Mt��ͼ�񽻻���ָ������ǽ��ָ��������ͨ����,��Ϣ�� TTWSwitchInfo
	OSPEVENT( MCS_MCU_STOP_SWITCH_TW_REQ,   EV_MCSVC_BGN + 661 );
	//MCUͬ��ֹͣ����ͼ��, ��Ϣ�� ��
	OSPEVENT( MCU_MCS_STOP_SWITCH_TW_ACK,   EV_MCSVC_BGN + 662 );
	//MCU�ܾ�ֹͣ����ͼ��, ��Ϣ�� ��
	OSPEVENT( MCU_MCS_STOP_SWITCH_TW_NACK,  EV_MCSVC_BGN + 663 );

	//�������̨�����ѯMCU����״̬, ��Ϣ��: TEqp
	OSPEVENT( MCS_MCU_GETMCUPERIEQPSTATUS_REQ,  EV_MCSVC_BGN + 666 );
	//MCUӦ��������̨�Ĳ�ѯ����״̬����, ��Ϣ�壺TPeriEqpStatus  
	OSPEVENT( MCU_MCS_GETMCUPERIEQPSTATUS_ACK,  EV_MCSVC_BGN + 667 );
	//MCU�ܻ������̨�Ĳ�ѯ����״̬����, ��Ϣ�壺  
	OSPEVENT( MCU_MCS_GETMCUPERIEQPSTATUS_NACK, EV_MCSVC_BGN + 668 );	

//3.6.4 ���ݻ������������
    //��ѯDCS����: TEqp
    OSPEVENT( MCS_MCU_GETPERIDCSSTATUS_REQ,     EV_MCSVC_BGN + 670 );
    //MCUӦ��������̨��ѯ����: TPeriDcsStatus
    OSPEVENT( MCU_MCS_GETPERIDCSSTATUS_ACK,     EV_MCSVC_BGN + 671 );
    //MCU�ܾ��������̨��ѯ����: TEqp
    OSPEVENT( MCU_MCS_GETPERIDCSSTATUS_NACK,    EV_MCSVC_BGN + 672 );
    //֪ͨ���DCS״̬�ı䣺TPeriDcsStatus
    OSPEVENT( MCU_MCS_MCUPERIDCSSTATUS_NOTIF,   EV_MCSVC_BGN + 673 );

//3.6.5	����״̬֪ͨ
	//֪ͨ�������״̬�ı�,��Ϣ��:TPeriEqpStatus
	OSPEVENT( MCU_MCS_MCUPERIEQPSTATUS_NOTIF,   EV_MCSVC_BGN + 678 );

	//zgc [2007/01/12] ֪ͨ���MPת���������ޣ���Ϣ�壺u32 MP ��IP��ַ(������)��ͬʱ CServMsgͷ�� srcdriid ������MpId
	OSPEVENT( MCU_MCS_MPFLUXOVERRUN_NOTIFY,		EV_MCSVC_BGN + 679);

//3.8	MCU�û�����
//3.8.1	����û�
	//�������̨����MCU����û�, ��Ϣ�壺CExUsrInfo
	OSPEVENT( MCS_MCU_ADDUSER_REQ,          EV_MCSVC_BGN + 681 );
	//MCU���ܻ������̨������û�����, ��Ϣ�壺�û���(32byte, ����ͬ) 
	OSPEVENT( MCU_MCS_ADDUSER_ACK,          EV_MCSVC_BGN + 682 );
	//MCU�ܾ��������̨������û�����, ��Ϣ�壺�û��� 
	OSPEVENT( MCU_MCS_ADDUSER_NACK,         EV_MCSVC_BGN + 683 );
    //MCU�����������̨������û�֪ͨ, ��Ϣ�壺CExUsrInfo
    OSPEVENT( MCU_MCS_ADDUSER_NOTIF,        EV_MCSVC_BGN + 684 );

//3.8.2	ɾ���û�
	//�������̨����MCUɾ���û�, ��Ϣ�壺CExUsrInfo
	OSPEVENT( MCS_MCU_DELUSER_REQ,          EV_MCSVC_BGN + 685 );
	//MCU���ܻ������̨��ɾ���û�����, ��Ϣ�壺�û���
	OSPEVENT( MCU_MCS_DELUSER_ACK,          EV_MCSVC_BGN + 686 );
	//MCU�ܾ��������̨��ɾ���û�����, ��Ϣ�壺�û���
	OSPEVENT( MCU_MCS_DELUSER_NACK,         EV_MCSVC_BGN + 687 );
    //MCU�����������̨��ɾ���û�֪ͨ, ��Ϣ�壺�û���
    OSPEVENT( MCU_MCS_DELUSER_NOTIF,        EV_MCSVC_BGN + 688 );

//3.8.3	��ȡ�û��б�
	//�������̨����MCU�õ��û��б�, ��Ϣ�壺��
	OSPEVENT( MCS_MCU_GETUSERLIST_REQ,      EV_MCSVC_BGN + 691 );
	//MCU���ܻ������̨�ĵõ��û��б�����, ��Ϣ����
	OSPEVENT( MCU_MCS_GETUSERLIST_ACK,      EV_MCSVC_BGN + 692 );
	//MCU�ܾ��������̨�ĵõ��û��б�����, ��Ϣ�壺��
	OSPEVENT( MCU_MCS_GETUSERLIST_NACK,     EV_MCSVC_BGN + 693 );
	//MCU����MCS���û��б�֪ͨ����Ϣ��ΪCLongMessage+CExUsrInfo����
	OSPEVENT( MCU_MCS_USERLIST_NOTIF,       EV_MCSVC_BGN + 694 );

//3.8.4	�޸��û���Ϣ
	//�������̨����MCU�޸��û���Ϣ, ��Ϣ�壺CExUsrInfo
	OSPEVENT( MCS_MCU_CHANGEUSER_REQ,       EV_MCSVC_BGN + 695 );
	//MCU���ܻ������̨���޸��û���Ϣ����, ��Ϣ�壺�û���
	OSPEVENT( MCU_MCS_CHANGEUSER_ACK,       EV_MCSVC_BGN + 696 );
	//MCU�ܾ��������̨���޸��û���Ϣ����, ��Ϣ�壺�û���
	OSPEVENT( MCU_MCS_CHANGEUSER_NACK,      EV_MCSVC_BGN + 697 );
    //MCU�����������̨���޸��û���Ϣ֪ͨ, ��Ϣ�壺CExUsrInfo
    OSPEVENT( MCU_MCS_CHANGEUSER_NOTIF,     EV_MCSVC_BGN + 698 );
        

//����MCU����
    //�����¼�MCU���� ��Ϣ�� TMCU+u8 (1-������0-����) 
	OSPEVENT( MCS_MCU_LOCKSMCU_REQ,         EV_MCSVC_BGN + 710 );
	//�����¼�MCU����ɹ�Ӧ�� ��Ϣ�� TMCU+u8 (1-������0-����) 
	OSPEVENT( MCU_MCS_LOCKSMCU_ACK,         EV_MCSVC_BGN + 711 );
	//�����¼�MCU����ʧ��Ӧ�� ��Ϣ�� TMCU+u8 (1-������0-����) 
	OSPEVENT( MCU_MCS_LOCKSMCU_NACK,        EV_MCSVC_BGN + 712 );

	//�����¼�MCU������״̬ ��Ϣ�� TMCU 
	OSPEVENT( MCS_MCU_GETMCULOCKSTATUS_REQ, EV_MCSVC_BGN + 715 );
	//�����¼�MCU������״̬�ɹ�Ӧ�� ��Ϣ�� TMCU + u8 (1-������0-����) 
	OSPEVENT( MCU_MCS_GETMCULOCKSTATUS_ACK, EV_MCSVC_BGN + 716 );
	//�����¼�MCU������״̬ʧ��Ӧ�� ��Ϣ�� TMCU
	OSPEVENT( MCU_MCS_GETMCULOCKSTATUS_NACK,EV_MCSVC_BGN + 717 );
	//�¼�MCU������״̬֪ͨ ��Ϣ�� TMCU + u8 (1-������0-����) 
	OSPEVENT( MCU_MCS_MCULOCKSTATUS_NOTIF,  EV_MCSVC_BGN + 718 );

//mcu���ý��滯
    //4.6 �¼� jlb
	//ȡHduԤ��
	OSPEVENT( MCS_MCU_GETHDUSCHEMEINFO_REQ , EV_MCSVC_BGN + 719);
	// ��Ϣ�壺TVmpStyleCfgInfo[MAX_VMPSTYLE_NUM]
    OSPEVENT( MCU_MCS_GETHDUSCHEMEINFO_ACK,     EV_MCSVC_BGN + 720 );
    // ��Ϣ�壺�ޣ�ԭ���������
    OSPEVENT( MCU_MCS_GETHDUSCHEMEINFO_NACK,    EV_MCSVC_BGN + 721 );

    //MCS����mcu ��cpuռ���� ��Ϣ�壺��
    OSPEVENT( MCS_MCU_CPUPERCENTAGE_REQ,    EV_MCSVC_BGN + 722 );
    //��Ϣ�壺��
    OSPEVENT( MCU_MCS_CPUPERCENTAGE_ACK,    EV_MCSVC_BGN + 723 );
    //��Ϣ�壺��
    OSPEVENT( MCU_MCS_CPUPERCENTAGE_NACK,   EV_MCSVC_BGN + 724 );
    //MCS����mcu ��cpuռ���� ��Ϣ�壺��
    OSPEVENT( MCS_MCU_CPUPERCENTAGE_CMD,    EV_MCSVC_BGN + 725 );
    //��Ϣ�壺u8  (0-100)%
    OSPEVENT(MCU_MCS_CPUPERCENTAGE_NOTIF,   EV_MCSVC_BGN + 726 );

    //MCS�����޸�mcu�豸������Ϣ ��Ϣ�壺TMcuEqpCfg
    OSPEVENT( MCS_MCU_CHANGEMCUEQPCFG_REQ,  EV_MCSVC_BGN + 728 );
    //��Ϣ�壺��
    OSPEVENT( MCU_MCS_CHANGEMCUEQPCFG_ACK,  EV_MCSVC_BGN + 729 );
    //��Ϣ�壺��
    OSPEVENT( MCU_MCS_CHANGEMCUEQPCFG_NACK, EV_MCSVC_BGN + 730 );
    //MCS����mcu�豸������Ϣ ��Ϣ�壺��
    OSPEVENT( MCS_MCU_GETMCUEQPCFG_REQ,     EV_MCSVC_BGN + 731 );
    //��Ϣ�壺��
    OSPEVENT( MCU_MCS_GETMCUEQPCFG_ACK,     EV_MCSVC_BGN + 732 );
    //��Ϣ�壺��
    OSPEVENT( MCU_MCS_GETMCUEQPCFG_NACK,    EV_MCSVC_BGN + 733 );
    //��Ϣ�壺TMcuEqpCfg
    OSPEVENT( MCU_MCS_MCUEQPCFG_NOTIF,      EV_MCSVC_BGN + 734 );
   
	//mcs�޸ĵ���������Ϣ 
    //��Ϣ��:u8(�������)+TBrdCfgInfo����+u8(����������)+TEqpMixerCfgInfo����
    //+u8(¼�������)+TEqpRecCfgInfo����+u8(����ǽ����)+TEqpTvWallCfgInfo����
    //+u8(bas����)+TEqpBasCfgInfo����+u8(vmp����)+TEqpVmpCfgInfo����
    //+u8(prs����)+TPrsCfgInfo+u8(���ϵ���ǽ����)+TMTvwallInfo����
	//+T8000BDscMod+u8(HDbas����)+TEqpBasHDCfgInfo����
    OSPEVENT( MCS_MCU_CHANGEBRDCFG_REQ,     EV_MCSVC_BGN + 737 );
    //��Ϣ�� :��
    OSPEVENT( MCU_MCS_CHANGEBRDCFG_ACK,     EV_MCSVC_BGN + 738 );
    //��Ϣ�� :�� ԭ���������
    OSPEVENT( MCU_MCS_CHANGEBRDCFG_NACK,    EV_MCSVC_BGN + 739 );
	//mcs ���󵥰�������Ϣ ��Ϣ��:��
	OSPEVENT( MCS_MCU_GETBRDCFG_REQ,        EV_MCSVC_BGN + 740 );
	//��Ϣ�� :��
	OSPEVENT( MCU_MCS_GETBRDCFG_ACK,        EV_MCSVC_BGN + 741 );
	//��Ϣ�� :�� ԭ���������
	OSPEVENT( MCU_MCS_GETBRDCFG_NACK,       EV_MCSVC_BGN + 742 );	
	//����������Ϣ֪ͨ ��Ϣ��: ͬMCS_MCU_CHANGEBRDCFG_REQ
	OSPEVENT( MCU_MCS_BRDCFG_NOTIF,         EV_MCSVC_BGN + 743 );
	//δ���õ�DSC��ע��֪ͨ ��Ϣ�壺��
	OSPEVENT( MCU_MCS_UNCFGDSCREG_NOTIF,	EV_MCSVC_BGN + 744 );
    	
	//mcs�޸�mcu������Ϣ�������� ��Ϣ�壺TMcuGeneralCfg
    OSPEVENT( MCS_MCU_CHANGEMCUGENERALCFG_REQ,  EV_MCSVC_BGN + 746 );
    //��Ϣ�壺��
    OSPEVENT( MCU_MCS_CHANGEMCUGENERALCFG_ACK,  EV_MCSVC_BGN + 747 );
    //��Ϣ�壺�� ԭ���������
    OSPEVENT( MCU_MCS_CHANGEMCUGENERALCFG_NACK, EV_MCSVC_BGN + 748 );

    // mcs ����mcu����������Ϣ ��Ϣ�壺��
    OSPEVENT( MCS_MCU_GETMCUGENERALCFG_REQ,     EV_MCSVC_BGN + 749 );
    //��Ϣ�壺��
    OSPEVENT( MCU_MCS_GETMCUGENERALCFG_ACK,     EV_MCSVC_BGN + 750 );
    //��Ϣ�壺�� ԭ���������
    OSPEVENT( MCU_MCS_GETMCUGENERALCFG_NACK,    EV_MCSVC_BGN + 751 );
    //��Ϣ�壺ͬMCS_MCU_CHANGEMCUGENERALCFG_REQ
    OSPEVENT( MCU_MCS_MCUGENERALCFG_NOTIF,      EV_MCSVC_BGN + 752 );
    // ȡVmpStyle��������
    OSPEVENT( MCS_MCU_GETVMPSCHEMEINFO_REQ,     EV_MCSVC_BGN + 753 );
    // ��Ϣ�壺TVmpStyleCfgInfo[MAX_VMPSTYLE_NUM]
    OSPEVENT( MCU_MCS_GETVMPSCHEMEINFO_ACK,     EV_MCSVC_BGN + 754 );
    // ��Ϣ�壺�ޣ�ԭ���������
    OSPEVENT( MCU_MCS_GETVMPSCHEMEINFO_NACK,    EV_MCSVC_BGN + 755 );
    // ��Ϣ�壺TBoardStatusNotify
    OSPEVENT(  MCU_MCS_BOARDSTATUS_NOTIFY,      EV_MCSVC_BGN +756 );

	// ���µ�DSC�巢��ע��, ��Ϣ��: u8(DSC����)+u32(DSC �ⲿip(������))+u32(DSC �ڲ�ip (������))+u32(DSC���ӵı���MCU���ڲ�IP(������)) + u32( �ڲ�IP MASK, ������) , zgc, 2007-03-05
	OSPEVENT( MCU_MCS_NEWDSCREGREQ_NOTIFY,		EV_MCSVC_BGN + 757);

    //���Զ������MCU,��Ϣ�壺u32 (Ҫ������mpc��ip(������)����Ϊ0����mpc�������)
    OSPEVENT( MCS_MCU_REBOOT_CMD,           EV_MCSVC_BGN + 760 );
    //����޸�mcuϵͳʱ��, ��Ϣ��: TKdvTime
    OSPEVENT( MCS_MCU_CHANGESYSTIME_REQ,    EV_MCSVC_BGN + 765 );
    //����޸�mcuϵͳʱ��ɹ�����Ϣ�壺TKdvTime(��ǰmcuϵͳʱ��)
    OSPEVENT( MCU_MCS_CHANGESYSTIME_ACK,    EV_MCSVC_BGN + 766 );
    //����޸�mcuϵͳʱ��ɹ�����Ϣ�壺��
    OSPEVENT( MCU_MCS_CHANGESYSTIME_NACK,   EV_MCSVC_BGN + 767 );

    //�������ĳ����,��Ϣ�壺u8 (��������)
    OSPEVENT( MCS_MCU_REBOOTBRD_REQ,        EV_MCSVC_BGN + 770 );
    //��Ϣ�壺u8 (��������)
    OSPEVENT( MCU_MCS_REBOOTBRD_ACK,        EV_MCSVC_BGN + 771 );
    //��Ϣ�壺u8 (��������)
    OSPEVENT( MCU_MCS_REBOOTBRD_NACK,       EV_MCSVC_BGN + 772 );

    //�����������MCU�����ļ�����Ϣ�壺��
    OSPEVENT( MCU_MCS_DOWNLOADCFG_REQ,      EV_MCSVC_BGN + 775 );
    //��Ϣ�壺u32 (���ݳ���,������) + s8[] ʵ���ļ�(������ǰ��ָ��)
    OSPEVENT( MCU_MCS_DOWNLOADCFG_ACK,      EV_MCSVC_BGN + 776 );
    //��Ϣ�壺��
    OSPEVENT( MCU_MCS_DOWNLOADCFG_NACK,     EV_MCSVC_BGN + 777 );

    //��������ϴ������ļ�����Ϣ�壺u32 (���ݳ���,������) + s8[] ʵ���ļ�(������ǰ��ָ��)
    OSPEVENT( MCU_MCS_UPLOADCFG_REQ,        EV_MCSVC_BGN + 778 );
    //�ϴ������ļ��ɹ�����Ϣ�壺��
    OSPEVENT( MCU_MCS_UPLOADCFG_ACK,        EV_MCSVC_BGN + 779 );
    //�ϴ������ļ�ʧ�ܡ���Ϣ�壺��
    OSPEVENT( MCU_MCS_UPLOADCFG_NACK ,      EV_MCSVC_BGN + 780 );

    //mcs֪ͨmcu���µ���汾
    //��Ϣ�壺u8(��������) + u8(Դ�ļ�������) + u8(�ļ�������) + s8[](�ļ���)  //ע��(�ļ�����������·��)
    OSPEVENT( MCS_MCU_UPDATEBRDVERSION_CMD,         EV_MCSVC_BGN + 782 );    
    //�汾���½��֪ͨ����Ϣ�壺u8(��������) + u8(�����ļ���byNum)  + u8[byNum](���ļ��Ƿ�ɹ�)
    OSPEVENT( MCU_MCS_UPDATEBRDVERSION_NOTIF,       EV_MCSVC_BGN + 785 );

	//mcs����mcu����telnet��½��Ϣ, zgc, 2007-10-19
	//��Ϣ��: TLoginInfo
	OSPEVENT( MCS_MCU_UPDATETELNETLOGININFO_REQ,	EV_MCSVC_BGN + 786 );
	OSPEVENT( MCU_MCS_UPDATETELNETLOGININFO_ACK,	EV_MCSVC_BGN + 787 );
	OSPEVENT( MCU_MCS_UPDATETELNETLOGININFO_NACK,	EV_MCSVC_BGN + 788 );
	
    
//���þ���
    //��ȡ�ն����þ������ͣ���Ϣ�壺TMt 
    OSPEVENT( MCS_MCU_EXMATRIX_GETINFO_CMD,         EV_MCSVC_BGN + 790 );
    //�ն����þ�������ָʾ, ��Ϣ�壺TMt ��u8 ����������˿��� 0��ʾû�о���
    OSPEVENT( MCU_MCS_EXMATRIXINFO_NOTIFY,          EV_MCSVC_BGN + 793 );
    
    //�������þ������Ӷ˿ں�,��Ϣ�壺TMt ��u8  (1-64 )
    OSPEVENT( MCS_MCU_EXMATRIX_SETPORT_CMD,         EV_MCSVC_BGN + 794 );
    
    //�����ȡ���þ������Ӷ˿�,��Ϣ�壺TMt 
    OSPEVENT( MCS_MCU_EXMATRIX_GETPORT_REQ,         EV_MCSVC_BGN + 798 );
    //��Ϣ�壺��
    OSPEVENT( MCU_MCS_EXMATRIX_GETPORT_ACK,         EV_MCSVC_BGN + 799 );
    //��Ϣ�壺��
    OSPEVENT( MCU_MCS_EXMATRIX_GETPORT_NACK,        EV_MCSVC_BGN + 800 );
    //��Ϣ�壺TMt ��u8  (1-64 )
    OSPEVENT( MCU_MCS_EXMATRIX_GETPORT_NOTIF,       EV_MCSVC_BGN + 801 );
    
    //�������þ������Ӷ˿���,��Ϣ�壺TMt ��u8  (1-64 )+s8[MAXLEN_MATRIXPORTNAME] 0��β���ַ��� 
    OSPEVENT( MCS_MCU_EXMATRIX_SETPORTNAME_CMD,     EV_MCSVC_BGN + 802 );
    //���þ���˿���ָʾ, ��Ϣ�壺TMt ��u8  (1-64 )+s8[MAXLEN_MATRIXPORTNAME] 0��β���ַ��� 
    OSPEVENT( MCU_MCS_EXMATRIX_PORTNAME_NOTIF,      EV_MCSVC_BGN + 805 );
    
    //�����ȡ���þ�������ж˿���,��Ϣ�壺��
    OSPEVENT( MCS_MCU_EXMATRIX_GETALLPORTNAME_CMD,  EV_MCSVC_BGN + 806 );
    //���þ�������ж˿���ָʾ����Ϣ�壺TMt ��s8[][MAXLEN_MATRIXPORTNAME] ����0 ��ʾ����˿��� ����Ϊ����˿ڣ����ַ������飩
    OSPEVENT( MCU_MCS_EXMATRIX_ALLPORTNAME_NOTIF,   EV_MCSVC_BGN + 809 );

//��չ��ƵԴ
    //��ȡ�ն���ƵԴ��Ϣ,��Ϣ�壺TMt
    OSPEVENT( MCS_MCU_GETVIDEOSOURCEINFO_CMD,       EV_MCSVC_BGN + 810 );
    //�ն�ȫ����ƵԴָʾ����Ϣ�壺TMt��tagITVideoSourceInfo[]
    OSPEVENT( MCU_MCS_ALLVIDEOSOURCEINFO_NOTIF,     EV_MCSVC_BGN + 813 );

    //�����ն���ƵԴ��Ϣ����Ϣ�壺TMt��tagITVideoSourceInfo
    OSPEVENT( MCS_MCU_SETVIDEOSOURCEINFO_CMD,       EV_MCSVC_BGN + 814 );
    //�ն���ƵԴ��Ϣָʾ,��Ϣ�壺TMt��tagITVideoSourceInfo
    OSPEVENT( MCU_MCS_VIDEOSOURCEINFO_NOTIF,        EV_MCSVC_BGN + 817 );
    
    //�����ն˵�ѡ����չ��ƵԴ����, ��Ϣ�壺TMt + u8
    OSPEVENT( MCS_MCU_SELECTEXVIDEOSRC_CMD,         EV_MCSVC_BGN + 820 );

// mcu��ַ������    
    //��ȡ���е�ַ���б���Ϣ�壺��
    OSPEVENT( MCS_MCU_ADDRBOOK_GETENTRYLIST_REQ,    EV_MCSVC_BGN + 840 );
    //��Ϣ�壺��
    OSPEVENT( MCU_MCS_ADDRBOOK_GETENTRYLIST_ACK,    EV_MCSVC_BGN + 841 );
    //��Ϣ�壺��
    OSPEVENT( MCU_MCS_ADDRBOOK_GETENTRYLIST_NACK,   EV_MCSVC_BGN + 842 );
    //��Ϣ�壺TMcuAddrEntry���� ������Ŀ�϶�ֶ����Ϣ֪ͨ��CServMsg��Ϣͷ�п��Ի�ȡ��Ϣ�ܰ�������ǰ�����������»�����ͬ��
    OSPEVENT( MCU_MCS_ADDRBOOK_GETENTRYLIST_NOTIF,  EV_MCSVC_BGN + 843 );
    
    //��ȡ���л������б���Ϣ�壺��
    OSPEVENT( MCS_MCU_ADDRBOOK_GETGROUPLIST_REQ,    EV_MCSVC_BGN + 844 );
    //��Ϣ�壺��
    OSPEVENT( MCU_MCS_ADDRBOOK_GETGROUPLIST_ACK,    EV_MCSVC_BGN + 845 );
    //��Ϣ�壺��
    OSPEVENT( MCU_MCS_ADDRBOOK_GETGROUPLIST_NACK,   EV_MCSVC_BGN + 846 );
    //��Ϣ�壺TMcuAddrGroup����
    OSPEVENT( MCU_MCS_ADDRBOOK_GETGROUPLIST_NOTIF,  EV_MCSVC_BGN + 847 );     

    //���ӵ�ַ����Ŀ����Ϣ�壺TMcuAddrEntry
    OSPEVENT( MCS_MCU_ADDRBOOK_ADDENTRY_REQ,        EV_MCSVC_BGN + 848 );
    //��Ϣ�壺��
    OSPEVENT( MCU_MCS_ADDRBOOK_ADDENTRY_ACK,        EV_MCSVC_BGN + 849 );
    //��Ϣ�壺��
    OSPEVENT( MCU_MCS_ADDRBOOK_ADDENTRY_NACK,       EV_MCSVC_BGN + 850 );
    //��Ϣ�壺TMcuAddrEntry
    OSPEVENT( MCU_MCS_ADDRBOOK_ADDENTRY_NOTIF,      EV_MCSVC_BGN + 851 );

    //ɾ����ַ����Ŀ����Ϣ�壺u32 ����ַ������, ������
    OSPEVENT( MCS_MCU_ADDRBOOK_DELENTRY_REQ,        EV_MCSVC_BGN + 852 );
    //��Ϣ�壺��
    OSPEVENT( MCU_MCS_ADDRBOOK_DELENTRY_ACK,        EV_MCSVC_BGN + 853 );
    //��Ϣ�壺��
    OSPEVENT( MCU_MCS_ADDRBOOK_DELENTRY_NACK,       EV_MCSVC_BGN + 854 );
    //��Ϣ�壺u32
    OSPEVENT( MCU_MCS_ADDRBOOK_DELENTRY_NOTIF,      EV_MCSVC_BGN + 855 );

    //�޸ĵ�ַ����Ŀ����Ϣ�壺TMcuAddrEntry
    OSPEVENT( MCS_MCU_ADDRBOOK_MODIFYENTRY_REQ,     EV_MCSVC_BGN + 856 );
    //��Ϣ�壺��
    OSPEVENT( MCU_MCS_ADDRBOOK_MODIFYENTRY_ACK,     EV_MCSVC_BGN + 857 );
    //��Ϣ�壺��
    OSPEVENT( MCU_MCS_ADDRBOOK_MODIFYENTRY_NACK,    EV_MCSVC_BGN + 858 );
    //��Ϣ�壺TMcuAddrEntry
    OSPEVENT( MCU_MCS_ADDRBOOK_MODIFYENTRY_NOTIF,   EV_MCSVC_BGN + 859 );

    //���ӻ�������Ŀ����Ϣ�壺TMcuAddrGroup
    OSPEVENT( MCS_MCU_ADDRBOOK_ADDGROUP_REQ,        EV_MCSVC_BGN + 860 );
    //��Ϣ�壺��
    OSPEVENT( MCU_MCS_ADDRBOOK_ADDGROUP_ACK,        EV_MCSVC_BGN + 861 );
    //��Ϣ�壺��
    OSPEVENT( MCU_MCS_ADDRBOOK_ADDGROUP_NACK,       EV_MCSVC_BGN + 862 );
    //��Ϣ�壺TMcuAddrGroup
    OSPEVENT( MCU_MCS_ADDRBOOK_ADDGROUP_NOTIF,      EV_MCSVC_BGN + 863 );

    //ɾ����������Ŀ����Ϣ�壺u32������������, ������
    OSPEVENT( MCS_MCU_ADDRBOOK_DELGROUP_REQ,        EV_MCSVC_BGN + 864 );
    //��Ϣ�壺��
    OSPEVENT( MCU_MCS_ADDRBOOK_DELGROUP_ACK,        EV_MCSVC_BGN + 865 );
    //��Ϣ�壺��
    OSPEVENT( MCU_MCS_ADDRBOOK_DELGROUP_NACK,       EV_MCSVC_BGN + 866 );
    //��Ϣ�壺u32
    OSPEVENT( MCU_MCS_ADDRBOOK_DELGROUP_NOTIF,      EV_MCSVC_BGN + 867 );

    //�޸Ļ�������Ŀ����Ϣ�壺TMcuAddrGroup
    OSPEVENT( MCS_MCU_ADDRBOOK_MODIFYGROUP_REQ,     EV_MCSVC_BGN + 868 );
    //��Ϣ�壺��
    OSPEVENT( MCU_MCS_ADDRBOOK_MODIFYGROUP_ACK,     EV_MCSVC_BGN + 869 );
    //��Ϣ�壺��
    OSPEVENT( MCU_MCS_ADDRBOOK_MODIFYGROUP_NACK,    EV_MCSVC_BGN + 870 );
    //��Ϣ�壺TMcuAddrGroup
    OSPEVENT( MCU_MCS_ADDRBOOK_MODIFYGROUP_NOTIF,   EV_MCSVC_BGN + 871 );

    //���ӵ�ַ����Ŀ�������飬��Ϣ�壺TMcuAddrGroup
    OSPEVENT( MCS_MCU_ADDRBOOK_ADDENTRYTOGROUP_REQ,     EV_MCSVC_BGN + 872 );
    //��Ϣ�壺��
    OSPEVENT( MCU_MCS_ADDRBOOK_ADDENTRYTOGROUP_ACK,     EV_MCSVC_BGN + 873 );
    //��Ϣ�壺��
    OSPEVENT( MCU_MCS_ADDRBOOK_ADDENTRYTOGROUP_NACK,    EV_MCSVC_BGN + 874 );
    //��Ϣ�壺TMcuAddrGroup
    OSPEVENT( MCU_MCS_ADDRBOOK_ADDENTRYTOGROUP_NOTIF,   EV_MCSVC_BGN + 875 );

    //�ӻ�������ɾ����ַ����Ŀ����Ϣ�壺TMcuAddrGroup
    OSPEVENT( MCS_MCU_ADDRBOOK_DELENTRYFROMGROUP_REQ,   EV_MCSVC_BGN + 876 );
    //��Ϣ�壺��
    OSPEVENT( MCU_MCS_ADDRBOOK_DELENTRYFROMGROUP_ACK,   EV_MCSVC_BGN + 877 );
    //��Ϣ�壺��
    OSPEVENT( MCU_MCS_ADDRBOOK_DELENTRYFROMGROUP_NACK,  EV_MCSVC_BGN + 878 );
    //��Ϣ�壺TMcuAddrGroup
    OSPEVENT( MCU_MCS_ADDRBOOK_DELENTRYFROMGROUP_NOTIF, EV_MCSVC_BGN + 879 );

//3.8.5 �û����������@2006.06.21
	//�������̨����MCU����û���, ��Ϣ�壺TUsrGrpInfo
	OSPEVENT( MCS_MCU_ADDUSERGRP_REQ,                   EV_MCSVC_BGN + 880 );
	//MCU���ܻ������̨������û�������, ��Ϣ�壺TUsrGrpInfo
	OSPEVENT( MCU_MCS_ADDUSERGRP_ACK,                   EV_MCSVC_BGN + 881 );
	//MCU�ܾ��������̨������û�������, ��Ϣ�壺�û����� 
	OSPEVENT( MCU_MCS_ADDUSERGRP_NACK,                  EV_MCSVC_BGN + 882 );
    //MCU�����������̨���û���֪ͨ, ��Ϣ�壺TUsrGrpInfo
    OSPEVENT( MCU_MCS_USERGRP_NOTIF,                    EV_MCSVC_BGN + 883 );

    //�������̨����MCU�޸��û���, ��Ϣ�壺TUsrGrpInfo
	OSPEVENT( MCS_MCU_CHANGEUSERGRP_REQ,                EV_MCSVC_BGN + 884 );
	//MCU���ܻ������̨���޸��û�������, ��Ϣ�壺TUsrGrpInfo��ͬʱ���� MCU_MCS_USERGRP_NOTIF
	OSPEVENT( MCU_MCS_CHANGEUSERGRP_ACK,                EV_MCSVC_BGN + 885 );
	//MCU�ܾ��������̨���޸��û�������, ��Ϣ�壺u8 byGrpId
	OSPEVENT( MCU_MCS_CHANGEUSERGRP_NACK,               EV_MCSVC_BGN + 886 );

    //�������̨����MCUɾ���û���, ��Ϣ�壺u8 byGrpId
	OSPEVENT( MCS_MCU_DELUSERGRP_REQ,                   EV_MCSVC_BGN + 888 );
	//MCU���ܻ������̨���޸��û�������, ��Ϣ�壺u8 byGrpId
	OSPEVENT( MCU_MCS_DELUSERGRP_ACK,                   EV_MCSVC_BGN + 889 );
	//MCU�ܾ��������̨������û�������, ��Ϣ�壺u8 byGrpId
	OSPEVENT( MCU_MCS_DELUSERGRP_NACK,                  EV_MCSVC_BGN + 890 );
    //MCU�����������̨��ɾ���û���֪ͨ, ��Ϣ�壺u8 byGrpId
    OSPEVENT( MCU_MCS_DELUSERGRP_NOTIF,                 EV_MCSVC_BGN + 891 );
    
    //�������̨����MCU�û�����Ϣ
	OSPEVENT( MCS_MCU_GETUSERGRP_REQ,                   EV_MCSVC_BGN + 892 );
	//MCU���ܻ������̨���û�����Ϣ����, ��Ϣ�壺u8 byNum + TUsrGrpInfo[]����
	OSPEVENT( MCU_MCS_GETUSERGRP_ACK,                   EV_MCSVC_BGN + 893 );
	//MCU�ܾ��������̨���û�����Ϣ����, ��Ϣ�壺��
	OSPEVENT( MCU_MCS_GETUSERGRP_NACK,                  EV_MCSVC_BGN + 894 );

//����ʧ����ʾ�û���Ϣ����Ϣ�壺CServMsg��Ŀǰֻ���������Ϣ��
    OSPEVENT( MCU_MCS_ALARMINFO_NOTIF,                  EV_MCSVC_BGN + 900 );
    
//N+1������Ϣ
    //�����ֶ������ݷ����������ݻع���N�ˣ����������ݷ��������ڽ��湤��״̬����δ�����Զ��ع�ʱ��Ч����admin��Ȩ�ޡ���Ϣ�壺��
    OSPEVENT( MCS_MCU_NPLUSROLLBACK_REQ,                EV_MCSVC_BGN + 910 );
    OSPEVENT( MCU_MCS_NPLUSROLLBACK_ACK,                EV_MCSVC_BGN + 911 ); 
    OSPEVENT( MCU_MCS_NPLUSROLLBACK_NACK,               EV_MCSVC_BGN + 912 );

    //�ֶ������ڽ��湤���ı��ݷ���������Ϊ����״̬����admin��Ȩ�ޣ������û�ȷ�ϡ���Ϣ�壺��
    OSPEVENT( MCS_MCU_NPLUSRESET_CMD,                   EV_MCSVC_BGN + 914 );

	// xliang [11/28/2008] mpu-vmp��ز���
	//VMP������VIP��ݵ�MT����VMP��������Ϣ�壺TVmpHdChnnlMemInfo
	OSPEVENT( MCU_MCS_VMPOVERHDCHNNLLMT_NTF,				EV_MCSVC_BGN + 919) ;
	//VMP���ȼ���ռ������Ϣ�壺TMt + TChnnlMemberInfo[] + u8
	OSPEVENT( MCU_MCS_VMPPRISEIZE_REQ,						EV_MCSVC_BGN + 920 );
	//vmp���ȼ���ռӦ����Ϣ�壺u8 byMtId+TSeizeChoice[]
	OSPEVENT( MCS_MCU_VMPPRISEIZE_ACK,						EV_MCSVC_BGN + 921 );
	//vmp���ȼ���ռʧ��Ӧ����Ϣ�壺u8 byMtId
	OSPEVENT( MCS_MCU_VMPPRISEIZE_NACK,						EV_MCSVC_BGN + 922 );
	//��ʼVMP������ѯ, ��Ϣ�壺
	OSPEVENT( MCS_MCU_START_VMPBATCHPOLL_REQ,				EV_MCSVC_BGN + 923 );
	OSPEVENT( MCU_MCS_START_VMPBATCHPOLL_ACK,				EV_MCSVC_BGN + 924 );
	OSPEVENT( MCU_MCS_START_VMPBATCHPOLL_NACK,				EV_MCSVC_BGN + 925 );
	//��ͣVMP������ѯ, ��Ϣ��:��
	OSPEVENT( MCS_MCU_PAUSE_VMPBATCHPOLL_CMD,				EV_MCSVC_BGN + 926 );
	//�ָ�VMP������ѯ, ��Ϣ��:��
	OSPEVENT( MCS_MCU_RESUME_VMPBATCHPOLL_CMD,				EV_MCSVC_BGN + 927 );
	//ֹͣVMP������ѯ, ��Ϣ�壺��
	OSPEVENT( MCS_MCU_STOP_VMPBATCHPOLL_CMD,				EV_MCSVC_BGN + 928 );
	//��ϯMTѡ��VMP����Ϣ�壺TMt
	OSPEVENT( MCS_MCU_STARTSWITCHVMPMT_REQ,					EV_MCSVC_BGN + 929 );
	OSPEVENT( MCU_MCS_STARTSWITCHVMPMT_ACK,				    EV_MCSVC_BGN + 930 );
	OSPEVENT( MCU_MCS_STARTSWITCHVMPMT_NACK,                EV_MCSVC_BGN + 931 );

	
	//ֹͣHDUͼ�񽻻�����Ϣ�壺THduSwitchInfo
	OSPEVENT( MCS_MCU_STOP_SWITCH_HDU_REQ,					EV_MCSVC_BGN + 933 );
	OSPEVENT( MCU_MCS_STOP_SWITCH_HDU_ACK,					EV_MCSVC_BGN + 934 );
	OSPEVENT( MCU_MCS_STOP_SWITCH_HDU_NACK,				    EV_MCSVC_BGN + 935 );
	
	//���������ý��滯��Ϣ
        //hduԤ��֪ͨ
    OSPEVENT( MCU_MCS_HDUSCHEMEINFO_NOTIF,                   EV_MCSVC_BGN + 936 );

	//HduԤ��
    OSPEVENT( MCS_MCU_CHANGEHDUSCHEMEINFO_REQ,              EV_MCSVC_BGN + 937 );
    OSPEVENT( MCU_MCS_CHANGEHDUSCHEMEINFO_ACK,              EV_MCSVC_BGN + 938 );
    OSPEVENT( MCU_MCS_CHANGEHDUSCHEMEINFO_NACK,             EV_MCSVC_BGN + 939 );

    //hduͨ��ѡ��vmp
	OSPEVENT( MCS_MCU_STARTSWITCH_HDUVMP_REQ,               EV_MCSVC_BGN + 940 );
	OSPEVENT( MCS_MCU_STARTSWITCH_HDUVMP_ACK,               EV_MCSVC_BGN + 941 );
	OSPEVENT( MCS_MCU_STARTSWITCH_HDUVMP_NACK,              EV_MCSVC_BGN + 942 );

	//hduͨ��ֹͣѡ��vmp
	OSPEVENT( MCS_MCU_STOPSWITCH_HDUVMP_REQ,                EV_MCSVC_BGN + 943 );
	OSPEVENT( MCS_MCU_STOPSWITCH_HDUVMP_ACK,                EV_MCSVC_BGN + 944 );
	OSPEVENT( MCS_MCU_STOPSWITCH_HDUVMP_NACK,               EV_MCSVC_BGN + 945 );

	//hdu��ѯ
	//�������̨����û��鿪ʼHDU��ѯ, ��Ϣ�壺  THduPollInfo + TMtPollParam����
	OSPEVENT( MCS_MCU_STARTHDUPOLL_CMD,                     EV_MCSVC_BGN + 950 ); 
	//�������̨����û���ֹͣHDU��ѯ, ��Ϣ�壺  ��
	OSPEVENT( MCS_MCU_STOPHDUPOLL_CMD,                      EV_MCSVC_BGN + 951 );
	//�������̨����û�����ͣHDU��ѯ, ��Ϣ�壺  ��
	OSPEVENT( MCS_MCU_PAUSEHDUPOLL_CMD,                     EV_MCSVC_BGN + 952 );
	//�������̨����û������HDU��ѯ, ��Ϣ�壺  ��
	OSPEVENT( MCS_MCU_RESUMEHDUPOLL_CMD,                    EV_MCSVC_BGN + 953 );
	
	//�������̨��MCU��ѯHDU��ѯ����, ��Ϣ�壺  �� 
	OSPEVENT( MCS_MCU_GETHDUPOLLPARAM_REQ,                  EV_MCSVC_BGN + 954 );
	//MCUӦ��������̨��ѯHDU��ѯ����, ��Ϣ�壺  THduPollInfo + TMtPollParam����
	OSPEVENT( MCU_MCS_GETHDUPOLLPARAM_ACK,                  EV_MCSVC_BGN + 955 ); 
	//MCU�ܾ��������̨��ѯHDU��ѯ����, ��Ϣ�壺  ��
	OSPEVENT( MCU_MCS_GETHDUPOLLPARAM_NACK,                 EV_MCSVC_BGN + 956 );
	//MCU֪ͨ�������̨��ǰ����ѯ״̬, ��Ϣ�壺  THduPollInfo
    OSPEVENT( MCU_MCS_HDUPOLLSTATE_NOTIF,                   EV_MCSVC_BGN + 957 );

	// xliang [12/3/2008] hdu��ز���
	//��ʼHDUͼ�񽻻�����Ϣ�壺THduSwitchInfo
	OSPEVENT( MCS_MCU_START_SWITCH_HDU_REQ,					EV_MCSVC_BGN + 958 );
	OSPEVENT( MCU_MCS_START_SWITCH_HDU_ACK,					EV_MCSVC_BGN + 959 );
	OSPEVENT( MCU_MCS_START_SWITCH_HDU_NACK,				EV_MCSVC_BGN + 960 );

	// ����������С ��Ϣ�� ��THduVolumeInfo
	OSPEVENT( MCS_MCU_CHANGEHDUVOLUME_REQ,		            EV_MCSVC_BGN + 961 );
	OSPEVENT( MCU_MCS_CHANGEHDUVOLUME_ACK,		            EV_MCSVC_BGN + 962 );
	OSPEVENT( MCU_MCS_CHANGEHDUVOLUME_NACK,		            EV_MCSVC_BGN + 963 );

	// ��ʼ������ѯ ��Ϣ�� ��THduSchemePollInfo
	OSPEVENT( MCS_MCU_STARTHDUBATCHPOLL_REQ,		        EV_MCSVC_BGN + 964 );
	OSPEVENT( MCU_MCS_STARTHDUBATCHPOLL_ACK,		        EV_MCSVC_BGN + 965 );
	OSPEVENT( MCU_MCS_STARTHDUBATCHPOLL_NACK,		        EV_MCSVC_BGN + 966 );

	// ֹͣ������ѯ ��Ϣ�� ����
	OSPEVENT( MCS_MCU_STOPHDUBATCHPOLL_REQ,		            EV_MCSVC_BGN + 967 );
	OSPEVENT( MCU_MCS_STOPHDUBATCHPOLL_ACK,		            EV_MCSVC_BGN + 968 );
	OSPEVENT( MCU_MCS_STOPHDUBATCHPOLL_NACK,		        EV_MCSVC_BGN + 969 );

	// ��ͣ������ѯ ��Ϣ�� ����
	OSPEVENT( MCS_MCU_PAUSEHDUBATCHPOLL_REQ,		        EV_MCSVC_BGN + 970 );
	OSPEVENT( MCU_MCS_PAUSEHDUBATCHPOLL_ACK,		        EV_MCSVC_BGN + 971 );
	OSPEVENT( MCU_MCS_PAUSEHDUBATCHPOLL_NACK,		        EV_MCSVC_BGN + 972 );

	// �ָ�������ѯ ��Ϣ�� ����
	OSPEVENT( MCS_MCU_RESUMEHDUBATCHPOLL_REQ,		        EV_MCSVC_BGN + 973 );
	OSPEVENT( MCU_MCS_RESUMEHDUBATCHPOLL_ACK,		        EV_MCSVC_BGN + 974 );
	OSPEVENT( MCU_MCS_RESUMEHDUBATCHPOLL_NACK,		        EV_MCSVC_BGN + 975 );

    // ������ѯ֪ͨ ��Ϣ�壺ThduSchemePollInfo
	OSPEVENT( MCU_MCS_HDUBATCHPOLL_STATUS_NOTIF,		    EV_MCSVC_BGN + 976 );


#endif /*_EVMCUMCS_H_*/
