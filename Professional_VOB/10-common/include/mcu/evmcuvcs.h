/*****************************************************************************
   ģ����      : mcu
   �ļ���      : evmcuvcs.h
   ����ļ�    : 
   �ļ�ʵ�ֹ���: MCU��VCS�ӿ���Ϣ����
   ����        : ���㻪
   �汾        : 
-----------------------------------------------------------------------------
   �޸ļ�¼:
   ��  ��      �汾        �޸���      �޸�����
   2008/11/20              ���㻪      ����
******************************************************************************/
#ifndef _EVMCUVCS_H_
#define _EVMCUVCS_H_

#include "osp.h"
#include "eventid.h"

/*------------------------------------------------------------------------------
 MCU��VCS�ӿ���Ϣ
------------------------------------------------------------------------------*/

//1 �û������ȡMCS��MCU��������Ϣ, ����Ϣ��ΪCVCSUsrInfo
//2 �û�������ȡMCS��MCU��������Ϣ����Ϣ��


//3 ����ģ������ȡMCS��MCU��������Ϣ������Ϣ������
//VCS����ģ�壬     //��Ϣ��: TConfInfo + 2 byte(������,TMtAlias����������,�������n)
//                  + n ��(TMtAlias������,����Ϊ 1byte(��������)+1byte(��������)+xbyte(�����ַ���)+2byte(��������)) 
//                  + TMultiTvWallModule(��ѡ�ֶΣ��ɻ��������е��Ƿ��е���ǽģ�����) 
//                  + TVmpModule(��ѡ�ֶΣ��ɻ��������е��Ƿ��л���ϳ�ǽģ�����)
//                  + 1byte(u8: 0 1  �Ƿ������˸������ǽ)
//                  + (��ѡ, THDTvWall)
//                  + 1byte(u8: ��������HDU��ͨ������)
//                  + (��ѡ, THduModChnlInfo+...)
//                  + 1byte(�Ƿ�Ϊ��������)��(��ѡ��2byte[u16 ���������ô�����ܳ���]+�¼�mcu[1byte(��������)+1byte(��������)+xbyte(�����ַ���)+2byte(��������)...)])
//                  + 1byte(�Ƿ�֧�ַ���)��(��ѡ��2byte(u16 ��������Ϣ�ܳ�)+����(1byte(����)+n��[1TVCSGroupInfo��m��TVCSEntryInfo])

//4 ��������
   //VCS��MCU�ϰ�����ģ�崴��һ����ʱ����, ����Ϣ��                
    OSPEVENT( VCS_MCU_CREATECONF_BYTEMPLATE_REQ,		EV_VCSVC_BGN + 1 );
    //����ģ��ɹ���ת��ɼ�ʱ����, ����Ϣ�� 
    OSPEVENT( MCU_VCS_CREATECONF_BYTEMPLATE_ACK,		EV_VCSVC_BGN + 2 );
    //����ģ��ת��ɼ�ʱ����ʧ��, ����Ϣ��
    OSPEVENT( MCU_VCS_CREATECONF_BYTEMPLATE_NACK,       EV_VCSVC_BGN + 3 );


// 5 ���Ȳ�������������Ϣ
	// VCS�����ĳ����ϯ��ʼ����       ��Ϣ�壺��(������Ϣͷ��CConfId)
	OSPEVENT( VCS_MCU_OPRCONF_REQ,              EV_VCSVC_BGN + 10 );
	// VCS�����ĳ����ϯ��ʼ������Ӧ�� ��Ϣ�壺��
	OSPEVENT( MCU_VCS_OPRCONF_ACK,              EV_VCSVC_BGN + 11 );
	// VCS�����ĳ����ϯ��ʼ������Ӧ�� ��Ϣ�壺��
	OSPEVENT( MCU_VCS_OPRCONF_NACK,             EV_VCSVC_BGN + 12 );

	// VCS�����˳�����ϯ               ��Ϣ�壺��(������Ϣͷ��CConfId)
	OSPEVENT( VCS_MCU_QUITCONF_REQ,             EV_VCSVC_BGN + 13 );
	// VCS�����˳�����ϯ��Ӧ��         ��Ϣ�壺��
	OSPEVENT( MCU_VCS_QUITCONF_ACK,             EV_VCSVC_BGN + 14 );
	// VCS�����˳�����ϯ��Ӧ��         ��Ϣ�壺��
	OSPEVENT( MCU_VCS_QUITCONF_NACK,            EV_VCSVC_BGN + 15 );

	//VCS�������ĵ���ģʽ,    ��Ϣ�壺��
	OSPEVENT( VCS_MCU_VCMODE_REQ,               EV_VCSVC_BGN + 20 );
	//VCS�������ĵ���ģʽӦ��,��Ϣ�壺u8(VCS_SINGLE_MODE��VCS_MULTW_MODE��VCS_MULVMP_MODE)
	OSPEVENT( MCU_VCS_VCMODE_ACK,               EV_VCSVC_BGN + 21 );
	//VCS�������ĵ���ģʽӦ��,��Ϣ�壺��
	OSPEVENT( MCU_VCS_VCMODE_NACK,              EV_VCSVC_BGN + 22 );

	//VCS���Ļ���ĵ���ģʽ��   ��Ϣ�壺u8(VCS_SINGLE_MODE��VCS_MULTW_MODE��VCS_MULVMP_MODE)
    OSPEVENT( VCS_MCU_CHGVCMODE_REQ,            EV_VCSVC_BGN + 23 );
	//VCS���Ļ���ĵ���ģʽӦ��
	OSPEVENT( MCU_VCS_CHGVCMODE_ACK,            EV_VCSVC_BGN + 24 );
	//VCS���Ļ���ĵ���ģʽӦ��,��Ϣ�壺��
	OSPEVENT( MCU_VCS_CHGVCMODE_NACK,           EV_VCSVC_BGN + 25 );
	//VCS���Ļ���ĵ���ģʽͨ��,��Ϣ�壺u8
	OSPEVENT( MCU_VCS_CHGVCMODE_NOTIF,          EV_VCSVC_BGN + 26 );
	
	//VCS����ָ�����ն�,         ��Ϣ�壺TMt(�����ն˵���Ϣ) + u8(��������:VCS_VCTYPE_DEFAULT, VCS_VCTYPE_DROPMT)
	//                                   u8(ǿ������:VCS_FORCECALL_REQ, VCS_FORCECALL_CMD)
	OSPEVENT( VCS_MCU_VCMT_REQ,                 EV_VCSVC_BGN + 27 );
	//VCS����ָ�����ն˵�Ӧ��,   ��Ϣ�壺TMt(�����ն˵���Ϣ) + u8(��������)
	//                                   u8(ǿ������:VCS_FORCECALL_REQ, VCS_FORCECALL_CMD)
	OSPEVENT( MCU_VCS_VCMT_ACK,                 EV_VCSVC_BGN + 28 );
	//VCS����ָ�����ն�Ӧ��,     ��Ϣ�壺��ERR_MCU_VCS_VCMTING����Ϣ��TMt(��һ�������ն˵���Ϣ)
	OSPEVENT( MCU_VCS_VCMT_NACK,                EV_VCSVC_BGN + 29 );
	//VCS���Ƚ��ͨ�棬          ��Ϣ�壺��ERR_MCU_VCS_VCMTOVERTIME����Ϣ��TMt(��һ�������ն˵���Ϣ)(��������)
	OSPEVENT( MCU_VCS_VCMT_NOTIF,               EV_VCSVC_BGN + 30 );

	//VCS����״̬ͨ��            ��Ϣ�壺CBasicVCCStatus
	OSPEVENT( MCU_VCS_CONFSTATUS_NOTIF,         EV_VCSVC_BGN + 31 );

	//VCS����������/����       ��Ϣ�壺u8(����ʱ�ĵ���ģʽ)+u8(����(1)/�ر�(0))
	//                                  +u8(VCS_OPR_LOCAL/VCS_OPR_REMOTE)+u8(VCS_AUDPROC_MUTE/VCS_AUDPROC_SILENCE)
	OSPEVENT( VCS_MCU_MUTE_REQ,                 EV_VCSVC_BGN + 40 );
	//VCS����������/����Ӧ��   ��Ϣ�壺 ��
	OSPEVENT( MCU_VCS_MUTE_ACK,                 EV_VCSVC_BGN + 41 );
	//VCS����������/����Ӧ��   ��Ϣ�壺 ��(�������룬��ģʽ���л�������ȡ��)
	OSPEVENT( MCU_VCS_MUTE_NACK,                EV_VCSVC_BGN + 42 );

// 6 
	//��������Զ��� 
	OSPEVENT( VCS_MCU_GETSOFTNAME_REQ  ,        EV_VCSVC_BGN + 60 );
	OSPEVENT( MCU_VCS_GETSOFTNAME_ACK  ,        EV_VCSVC_BGN + 61 );
	OSPEVENT( MCU_VCS_GETSOFTNAME_NACK,         EV_VCSVC_BGN + 62 );

	OSPEVENT( VCS_MCU_CHGSOFTNAME_REQ  ,        EV_VCSVC_BGN + 63 );
	OSPEVENT( MCU_VCS_CHGSOFTNAME_ACK  ,        EV_VCSVC_BGN + 64 );
    OSPEVENT( MCU_VCS_CHGSOFTNAME_NACK ,        EV_VCSVC_BGN + 65 );

	OSPEVENT( VCS_MCU_SOFTNAME_NOTIF   ,        EV_VCSVC_BGN + 66 );

// �������, ������
	//VCS����MCU�������Ӳ�����ն�,   ��Ϣ�壺  u8(����)+u8(��������)+s8�ַ���(����)+u8(�ն���)+TMt����+
	//                                          ...
	OSPEVENT( VCS_MCU_GROUPCALLMT_REQ,            EV_VCSVC_BGN + 70 );
	//MCUͬ���������Ӳ�����ն�,      ��Ϣ�壺  ��
	OSPEVENT( MCU_VCS_GROUPCALLMT_ACK,            EV_VCSVC_BGN + 71 );
	//MCU�ܾ��������Ӳ�����ն�,      ��Ϣ�壺  ��
	OSPEVENT( MCU_VCS_GROUPCALLMT_NACK,           EV_VCSVC_BGN + 72 );
	//ͨ��                            ��Ϣ��:   ����(��ʧ�ܴ�����)
	OSPEVENT( MCU_VCS_GROUPCALLMT_NOTIF ,           EV_VCSVC_BGN + 73 );

	//VCS����MCU�����Ҷ�����ն�,     ��Ϣ�壺 u8(����)+u8(��������)+s8�ַ���(����)+u8(�ն���)+TMt����+
	//                                          ...
	OSPEVENT( VCS_MCU_GROUPDROPMT_REQ,            EV_VCSVC_BGN + 75 );
	//MCUͬ�������Ҷ�����ն�,        ��Ϣ�壺  ��
	OSPEVENT( MCU_VCS_GROUPDROPMT_ACK,            EV_VCSVC_BGN + 76 );
	//MCU�ܾ������ҶϺ��ն�,          ��Ϣ�壺  ��
	OSPEVENT( MCU_VCS_GROUPDROPMT_NACK,           EV_VCSVC_BGN + 77 );

	//VCS����MCU��ʱ�����ն�,    ��Ϣ�壺  TAddMtInfo
	OSPEVENT( VCS_MCU_ADDMT_REQ,                EV_VCSVC_BGN + 80 );
	//MCUͬ�������ն�,           ��Ϣ�壺  ��
	OSPEVENT( MCU_VCS_ADDMT_ACK,                EV_VCSVC_BGN + 81 );
	//MCU�ܾ������ն�,           ��Ϣ�壺  ��
	OSPEVENT( MCU_VCS_ADDMT_NACK,               EV_VCSVC_BGN + 82 );

	//VCS����MCUɾ���ն�,        ��Ϣ�壺  TMt
	//VCS��Ҫ��֤����ɾ�����ն˷ǵ���ģʽ�еĿɵ�����Դ
	OSPEVENT( VCS_MCU_DELMT_REQ,                EV_VCSVC_BGN + 85 );
	//MCUͬ�������ն�,           ��Ϣ�壺  ��
	OSPEVENT( MCU_VCS_DELMT_ACK,                EV_VCSVC_BGN + 86 );
	//MCU�ܾ������ն�,           ��Ϣ�壺  ��
	OSPEVENT( MCU_VCS_DELMT_NACK,               EV_VCSVC_BGN + 87 );

	//VCS������ϯ��ѯ,               ��Ϣ�壺  u8(��ѯ���)
	OSPEVENT( VCS_MCU_STARTCHAIRMANPOLL_REQ,     EV_VCSVC_BGN + 90 );
	//MCUͬ�⿪����ϯ��ѯ,           ��Ϣ�壺  ��
	OSPEVENT( MCU_VCS_STARTCHAIRMANPOLL_ACK,      EV_VCSVC_BGN + 91 );
	//MCU�ܾ�������ϯ��ѯ,           ��Ϣ�壺  ��(��������)
	OSPEVENT( MCU_VCS_STARTCHAIRMANPOLL_NACK,     EV_VCSVC_BGN + 92 );

	//VCSֹͣ��ϯ��ѯ,               ��Ϣ�壺  ��
	OSPEVENT( VCS_MCU_STOPCHAIRMANPOLL_REQ,     EV_VCSVC_BGN + 95 );
	//MCUͬ��ֹͣ��ϯ��ѯ,           ��Ϣ�壺  ��
	OSPEVENT( MCU_VCS_STOPCHAIRMANPOLL_ACK,      EV_VCSVC_BGN + 96 );
	//MCU�ܾ�ֹͣ��ϯ��ѯ,           ��Ϣ�壺  ��
	OSPEVENT( MCU_VCS_STOPCHAIRMANPOLL_NACK,     EV_VCSVC_BGN + 97 );
	
// ����
    // ͬ��ǿ������                   ��Ϣ��:   TMt(�����ͷŵ��ն�) + s8[](������ռ�Ļ�������)
	OSPEVENT( MCU_VCS_RELEASEMT_REQ,             EV_VCSVC_BGN + 100 );
    // ͬ��ǿ��                       ��Ϣ��:   TMt(�����ͷŵ��ն�) + s8[](������ռ�Ļ�������)
	OSPEVENT( VCS_MCU_RELEASEMT_ACK,             EV_VCSVC_BGN + 101 );
	// �ܾ�ǿ��                       ��Ϣ��:�� TMt(�����ͷŵ��ն�) + s8[](������ռ�Ļ�������)��
	OSPEVENT( VCS_MCU_RELEASEMT_NACK,            EV_VCSVC_BGN + 102 );
	// ǿ��ִ��ͨ��                   ��Ϣ��:   TMt(�����ͷŵ��ն�) + s8[](������ռ�Ļ�������)
	OSPEVENT( MCU_VCS_RELEASEMT_NOTIF,           EV_VCSVC_BGN + 103 );
 
// 7 Ϊ���汣��mcu��������Ϣ
    //VCS�����ȡ��������Ϣ��        ��Ϣ�壺  ��
    OSPEVENT( VCS_MCU_GETUNPROCFGINFO_REQ,       EV_VCSVC_BGN + 150 );
    //�����ȡ��������Ϣ�ɹ�,        ��Ϣ�壺  s8[] ʵ������
    OSPEVENT( MCU_VCS_GETUNPROCFGINFO_ACK,       EV_VCSVC_BGN + 151 );
    //�����ȡ��������Ϣʧ��,        ��Ϣ�壺  ��
    OSPEVENT( MCU_VCS_GETUNPROCFGINFO_NACK ,     EV_VCSVC_BGN + 152 );

    //VCS����mcu���治������Ϣ��     ��Ϣ�壺  s8[] ʵ������
    OSPEVENT( VCS_MCU_SETUNPROCFGINFO_REQ,       EV_VCSVC_BGN + 153 );
    //���󱣴�mcu��������Ϣ�ɹ�,     ��Ϣ�壺  ��
    OSPEVENT( MCU_VCS_SETUNPROCFGINFO_ACK,       EV_VCSVC_BGN + 154 );
    //���󱣴�mcu��������Ϣʧ��,     ��Ϣ�壺  ��  
    OSPEVENT( MCU_VCS_SETUNPROCFGINFO_NACK,      EV_VCSVC_BGN + 155 );
    //mcu��������Ϣͨ��,             ��Ϣ�壺  s8[] ʵ������
    OSPEVENT( MCU_VCS_SETUNPROCFGINFO_NOTIF,     EV_VCSVC_BGN + 156 );


#endif /*_EVMCUVCS_H_*/


