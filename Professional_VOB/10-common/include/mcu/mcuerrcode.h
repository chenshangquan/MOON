/*****************************************************************************
   ģ����      : MCU��ϵͳ�����붨��
   �ļ���      : mcuerrcode.h
   ����ļ�    : 
   �ļ�ʵ�ֹ���: MCU������
   ����        : ����
   �汾        : V4.0  Copyright(C) 2001-2008 KDC, All rights reserved.
-----------------------------------------------------------------------------
   �޸ļ�¼:
   ��  ��      �汾        �޸���      �޸�����
   2002/08/27  0.9         ����        ����
   2003/02/28  1.0         Qzj         ���������
   2007/11/06  4.0         ����      ������������룬���࣬Ԥ���ռ�
   ******************************************************************************/


/**********************************************************
   ҵ��MCU����Ŷ��壨20001-22000��

   ��Ϊ���²��֣�

   1. һ���Դ����糬ʱ��æ��Ȩ�� ��·���󡪡�20001-20100
   2. ����/ģ�崴��/�޸ĵȡ���20100-20200
   3. MCU�����������ơ���20301-20400
   4. �����������20401-21000
        ϸ��Ϊ���ն˺���/��ϯ/���ԡ���20401-20500
                ѡ��ý�塪��20501-20520
                ���������������20521-20600
                �����������20801-21000
   5. ����/N+1����ר�á���21401-21500
   6. GK/����Ʒ�ר�á���21501-21600
   7. MCU���ý��滯����21601-21700

   0. Ŀǰ���ղ��֣�21021-20300; 20601-20800; 
                    21001-21400; 21701-22000

**********************************************************/


#ifndef _ERR_MCU_H_
#define _ERR_MCU_H_

#include "errorid.h"

#define DefineError(err, num )   \
    err = num,
    
#define DefineErrorEnd  \
    ERR_MCU_CODENDED = ERR_MCU_END
        
enum emMcuErrorCode
{




/* һ���Դ���20001-20100�� */

//MCU�ȴ�Ӧ��ʱ
DefineError( ERR_MCU_TIMEROUT				   , ERR_MCU_BGN + 0)

//MCU���ڳ�ʼ��
DefineError( ERR_MCU_INITIALIZING			   , ERR_MCU_BGN + 1)

//MCU��æ
DefineError( ERR_MCU_BUSY        			   , ERR_MCU_BGN + 2)

//MCU���ڵȴ�ǰһ������Ĵ���
DefineError( ERR_MCU_WAITINGSTATE			   , ERR_MCU_BGN + 3)

//Ȩ�޲���������ִ�д˲���
DefineError( ERR_MCU_OPERATION_NOPERMIT        , ERR_MCU_BGN + 4)

//�����ڵ�ͨ�Ű汾��MCU��һ�£������룺20017��ע������ϰ汾�����ܸ��ģ�
DefineError( ERR_MCU_VER_UNMATCH               , ERR_MCU_BGN + 16)

//ָ�����費����
DefineError( ERR_MCU_EQPOFFLINE				   , ERR_MCU_BGN + 50)

// ָ�������費�Ϸ�
DefineError( ERR_MCU_WRONGEQP				   , ERR_MCU_BGN + 51)

// �������ӵ�����Ƿ�
DefineError( ERR_MCU_REGEQP_INVALID			   , ERR_MCU_BGN + 52)

// 4.6 jlb
// �õ�mt���߼�ͨ��ʧ��
DefineError( ERR_MCU_GETMTLOGCHN_FAIL          , ERR_MCU_BGN + 53 )

// hduѡ�������費����
DefineError( ERR_MCU_MCUPERI_NOTEXIST          , ERR_MCU_BGN + 54 )

// ����ǽ��ѯ�в���ѡ��VMP���ն�
DefineError( ERR_MCU_NOTSWITCHVMPORMT          , ERR_MCU_BGN + 55 )

// ��ͬһ���飬���ܸı�������С�����þ���
DefineError( ERR_MCU_HDUCHANGEVOLUME           , ERR_MCU_BGN + 56 )

// hdu������ѯǰ����ͨ����ռ�ã����ͷ�
DefineError( ERR_MCU_HDUBATCHPOLL_CHNLINUSE    , ERR_MCU_BGN + 57 )

// hdu������ѯʱ������û���ն�
DefineError( ERR_MCU_HDUBATCHPOLL_NONEMT       , ERR_MCU_BGN + 58 )



/* ���������ģ��ʧ�� (20101-20200) */

//MCU�޷�Ϊ�˻��������Դ�����Ժ��ٴ����»���
DefineError( ERR_MCU_CONFOVERFLOW			   , ERR_MCU_BGN + 100)

//��������ʧ��,�Ѵ���������
DefineError( ERR_MCU_CONFNUM_EXCEED			   , ERR_MCU_BGN + 101)

//����ģ��ʧ�ܣ�û�п��õ�ģ��ռ�
DefineError( ERR_MCU_TEMPLATE_NOFREEROOM       , ERR_MCU_BGN + 102)

//��Ҫ�Ľ����ת����δ���ӣ����Ժ��ٴ����»���
DefineError( ERR_MCU_CREATECONF_MCS_NOMPMTADP  , ERR_MCU_BGN + 103)

//�������Ѵ���
DefineError( ERR_MCU_CONFNAME_REPEAT		   , ERR_MCU_BGN + 104)

//������Ѵ���
DefineError( ERR_MCU_CONFIDREPEAT              , ERR_MCU_BGN + 105)

//��E164�����Ѵ���
DefineError( ERR_MCU_CONFE164_REPEAT		   , ERR_MCU_BGN + 106)

//��������ָ��ģ��δ�ҵ�
DefineError( ERR_MCU_TEMPLATE_NOTEXIST         , ERR_MCU_BGN + 107)

//û�п��е�������������˫��ʽý��������Ԥ������������ʧ��
DefineError( ERR_MCU_NOIDLEADAPTER  		   , ERR_MCU_BGN + 110)

//û�п��еĻ�����,�������鴴��ʧ��
DefineError( ERR_MCU_NOIDLEMIXER    	       , ERR_MCU_BGN + 111)

//û�п��еĶ����ش���,�����ش����鴴��ʧ��
DefineError( ERR_MCU_NOIDLEPRS    	           , ERR_MCU_BGN + 112)

//��������������Ƿ����ü��ܲ�һ��,���鴴��ʧ��
DefineError( ERR_MCU_SETENCRYPT    	           , ERR_MCU_BGN + 113)

//û�п��еĵ���ǽ,������ǽ�Ļ��鴴��ʧ��
DefineError( ERR_MCU_NOIDLETVWALL  	           , ERR_MCU_BGN + 114)

//ָ����¼��������ߣ������Զ�¼�����ʧ��
DefineError( ERR_MCU_CONFSTARTREC_MAYFAIL      , ERR_MCU_BGN + 115)

//û�п��е�dcs���������ݻ���ʧ��
DefineError( ERR_MCU_NOIDLEDCS                 , ERR_MCU_BGN + 116)

//û��ָ���ն��б����ն��Զ������Ļ��鴴��ʧ��
DefineError( ERR_MCU_NOMTINCONF                , ERR_MCU_BGN + 117)

//�������ʱ��Ӧ���ڵ�ǰʱ��֮��
DefineError( ERR_MCU_STARTTIME_WRONG		   , ERR_MCU_BGN + 118)

//�������ʲ�֧��
DefineError( ERR_MCU_CONFBITRATE      		   , ERR_MCU_BGN + 119)

//ָ���Ļ�����Ƶ����Ƶ��ʽ��֧��
DefineError( ERR_MCU_CONFFORMAT				   , ERR_MCU_BGN + 120)

//�����鲥��ַ�Ƿ�
DefineError( ERR_MCU_MCASTADDR_INVALID         , ERR_MCU_BGN + 121)

//�����鲥��ַ�Ѿ���ռ��
DefineError( ERR_MCU_MCASTADDR_USED            , ERR_MCU_BGN + 122)

//��ɢ�����鲥��ַ�Ƿ�
DefineError( ERR_MCU_DCASTADDR_INVALID         , ERR_MCU_BGN + 123)

//��ɢ���鲻����˫��˫��ʽ
DefineError( ERR_MCU_DCAST_NOADP               , ERR_MCU_BGN + 124)

//��ɢ�����鲥��ַ�Ѿ���ռ��
DefineError( ERR_MCU_DCASTADDR_USED            , ERR_MCU_BGN + 125)

//��ɢ���鳬�����ش�ͨ����
DefineError( ERR_MCU_DCAST_OVERCHNNLNUM        , ERR_MCU_BGN + 126)

//�û��鲻�ܽ��е����鲥
DefineError( ERR_MCU_MCLOWNOSUPPORT            , ERR_MCU_BGN + 127)

//�û��鲻�ܽ��е���¼��
DefineError( ERR_MCU_RECLOWNOSUPPORT           , ERR_MCU_BGN + 128)

//û���㹻Ȩ�ޱ���ȱʡ����
DefineError( ERR_MCU_SAVEDEFCONF_NOPERMIT      , ERR_MCU_BGN + 150)

//�����Ϊ�գ�ͬʱ�����ն˿�ѡ��Ļ����б�(����Ų����޸�)
DefineError( ERR_MCU_NULLCID                   , ERR_MCU_BGN + 160)


/* MCU �����������ƵĴ����� (20301-20400) */

//����MCU�������ն�����
DefineError( ERR_MCU_OVERMAXCONNMT				 , ERR_MCU_BGN + 300)

//ת���帺����������
DefineError( ERR_MCU_MPNETTRFCOVERRUN            , ERR_MCU_BGN + 301)

// ��������ʱ���ܽ��л���ϳ�
DefineError( ERR_MCU_VACNOVMP                    , ERR_MCU_BGN + 302)

// ����ϳ�ʱ���ܽ�����������
DefineError( ERR_MCU_VMPNOVAC                    , ERR_MCU_BGN + 303)

// ��ǰ�����ʽ��֧�ֻ���ϳ�
DefineError( ERR_MCU_VMPNOSUPPORT                , ERR_MCU_BGN + 304)

// ����ͬʱ���л���ʱ�޷�����ָ�����Ļ���ϳ�
DefineError( ERR_MCU_VMPNOSUPPORTONMIX           , ERR_MCU_BGN + 305)

// ����������������ʱ�޷�����ָ�����Ļ���
DefineError( ERR_MCU_MIXNOSUPPORTONBAS           , ERR_MCU_BGN + 306)

// �������ڻ���ϳ�ʱ�޷�����ָ�����Ļ���
DefineError( ERR_MCU_MIXNOSUPPORTONVMP           , ERR_MCU_BGN + 307)

// �����ն�����������������
DefineError( ERR_MCU_MIXNOSUPPORT                , ERR_MCU_BGN + 308)

// �����ն����������������������
DefineError( ERR_MCU_VACNOSUPPORT                , ERR_MCU_BGN + 309)

// ����������������ʱ�޷��Ը������ն˽�����������
DefineError( ERR_MCU_VACNOSUPPORTONBAS           , ERR_MCU_BGN + 310)

// �������ڶԸ������ն˽�����������ʱ�޷���������
DefineError( ERR_MCU_BASNOSUPPORTONVAC           , ERR_MCU_BGN + 311)

// �������ڶԸ������ն˽��л���ʱ�޷���������
DefineError( ERR_MCU_BASNOSUPPORTONMIX           , ERR_MCU_BGN + 312)

// �޷�֧�ָ�����ն�����ͬʱ���л������ۣ������Ѿ��Զ�ֹͣ���л�Ϊ���ƻ���
DefineError( ERR_MCU_DISCUSSAUTOCHANGE2SPECMIX   , ERR_MCU_BGN + 313)

//����������������ͨ����
DefineError( ERR_MCU_OVERMAXMIXERCHNNL           , ERR_MCU_BGN + 314)

//û�п��еĻ�����,��ʼ��������ʧ��
DefineError( ERR_MCU_NOIDLEMIXER_INCONF          , ERR_MCU_BGN + 315)

//���������붨�ƻ�������
DefineError( ERR_MCU_VACMUTEXSPECMIX             , ERR_MCU_BGN + 316)

//�������ƻ����ͱ���������������
//DefineError( ERR_MCU_CASSPECMIXMUTEXVAC          , ERR_MCU_BGN + 317)

//ǿ�Ʒ�����ʱ���������
DefineError( ERR_MUSTSEESPEAKER_NOTPLAY          , ERR_MCU_BGN + 318)

//�¼�VAC���������ƻ������ ��ʾ
DefineError( ERR_MCU_MMCUSPECMIX_VAC             , ERR_MCU_BGN + 319)


//���鵱ǰ�п��л���ϳ���������֧��������(�޷����л���ϳɻ��ٿ�����)
DefineError( ERR_MCU_ALLIDLEVMP_NO_SUPPORT       , ERR_MCU_BGN + 330)

//���鵱ǰʹ�õĻ���ϳ�����֧�������񣬵���MCU������������ϳ���֧�����������ȷʵ��Ҫ�����Ļ���ϳɣ����¿����û���ϳɷ��Ļ���ϳɼ��ɡ�
DefineError( ERR_MCU_OTHERVMP_SUPPORT            , ERR_MCU_BGN + 331)

//ָ���Ļ���ϳɷ�񲻱�֧��
DefineError( ERR_INVALID_VMPSTYLE                , ERR_MCU_BGN + 332)

//���п��еĻ���ϳ��������ܽ��л���ϳ�
DefineError( ERR_MCU_NOIDLEVMP			         , ERR_MCU_BGN + 333)

//��ǰ�Ŀ���mau/mpu���㣬���ܻᵼ���Ժ���ٿ�����ʧ��
DefineError( ERR_MCU_NOENOUGH_HDBAS_TEMP         , ERR_MCU_BGN + 334)

//û�п��е�mau/mpu�������ٿ�����
DefineError( ERR_MCU_NOENOUGH_HDBAS_CONF         , ERR_MCU_BGN + 335)

//����ռ��mau/mpuʧ��
DefineError( ERR_MCU_OCUPPYHDBAS                 , ERR_MCU_BGN + 336)

//VMP��֧����ϯ����
DefineError( ERR_VMPUNSUPPORTCHAIRMAN			 , ERR_MCU_BGN + 337)

//û�п��е�mpu�������ٿ�����
DefineError( ERR_MCU_NOENOUGH_MPU_CONF           , ERR_MCU_BGN + 338)

//����ռ��MPUʧ��
DefineError( ERR_MCU_OCUPPYMPU                   , ERR_MCU_BGN + 339)

//�����ѿ�ʼ��ѯ�����ܿ�ʼ��������
DefineError( ERR_MCU_CONFSTARTPOLLVACMODE        , ERR_MCU_BGN + 340)

//�����Ѵ����Ѵ�������״̬�����ܽ���������������
DefineError( ERR_MCU_CONFINVACMODE_BYDISCUSSC    , ERR_MCU_BGN + 341)

//�����Ѵ����Ѵ��������������ƣ����ܽ�������
DefineError( ERR_MCU_CONFINDISCUSSCMODE_BYVAC    , ERR_MCU_BGN + 342)

//���鴦������������ʽ������ȡ��������
DefineError( ERR_MCU_VACNOSPEAKERCANCEL          , ERR_MCU_BGN + 343)

//���鴦�����۷�ʽ������ָ��������
DefineError( ERR_MCU_DISCUSSNOSPEAKER            , ERR_MCU_BGN + 344)

//���鴦������������ʽ������ָ��������
DefineError( ERR_MCU_VACNOSPEAKERSPEC            , ERR_MCU_BGN + 345)

//���鴦��ǿ�ƹ㲥������ģʽ������ѡ���ն�
DefineError( ERR_MCU_MUSTSEESPEAKER              , ERR_MCU_BGN + 346)
 
//���η������л����С����Сʱ����������ָ��������
DefineError( ERR_MCU_LESSPEAKERHOLDTIME          , ERR_MCU_BGN + 347)

//��ǰ�Ķ��ƻ���״̬����� ��ʾ
DefineError( ERR_MCU_SPECMIX_CANCEL_NTF          , ERR_MCU_BGN + 348)

//��ǰ�����ܻ���״̬����� ��ʾ
DefineError( ERR_MCU_AUTOMIX_CANCEL_NTF          , ERR_MCU_BGN + 349)

//���������ͨ��������
DefineError( ERR_BASCHANNEL_INVALID              , ERR_MCU_BGN + 370)

//��ɢ���鲻��ִ�б�����
DefineError( ERR_MCU_DCAST_NOOP                  , ERR_MCU_BGN + 380)

//HDI ����������������MT����mcuʧ��
DefineError( ERR_MCU_MTCALLFAIL_HDIFULL			 , ERR_MCU_BGN + 381)

//HD��������������������Ƕ���룩
DefineError( ERR_MCU_CALLHDMTFAIL				 , ERR_MCU_BGN + 382)

//Ϊ����Ԥ����ת�����������������·���ת����
DefineError( ERR_MCU_MPRESERVEDBANDWIDTH_FULL    , ERR_MCU_BGN + 383)


/* �����������20401-21000�� */

//�����ն�/�������[20401-20430]

//ָ���ն˲��ɼ������ܲ�����
DefineError( ERR_MCU_MTUNREACHABLE			    , ERR_MCU_BGN + 400)

//ָ���ն˾ܾ��������
DefineError( ERR_MCU_MTREJECT				    , ERR_MCU_BGN + 401)

//ָ���ն����ڻ�����
DefineError( ERR_MCU_ADDEDMT_INCONF			    , ERR_MCU_BGN + 402)

//����ϯ�ն˲���ִ�д������
DefineError( ERR_MCU_INVALID_OPER			    , ERR_MCU_BGN + 403)

//���е��ն��Ѿ����
DefineError( ERR_MCU_CALLEDMT_JOINEDCONF	    , ERR_MCU_BGN + 404)

//���е��ն�û�п��õĺ��е�ַ��Ϣ
DefineError( ERR_MCU_CALLEDMT_NOADDRINFO	    , ERR_MCU_BGN + 405)

//���ܼ����¼�MCU���飬�������
DefineError( ERR_MCU_INVALIDPWD                 , ERR_MCU_BGN + 406)

//�ϼ�MCUû��Ӧ�� 
DefineError( ERR_MCU_MMCUNORESPONSE             , ERR_MCU_BGN + 407) 

//���ܺ��л��鱾��
DefineError( ERR_MCU_NOTCALL_CONFITSELF	        , ERR_MCU_BGN + 408)

//ָ���ն�æ����������һ������
DefineError( ERR_MCU_MTBUSY					    , ERR_MCU_BGN + 409)

//�ն�Round trip delay ��ʱ,������·ʧ��
DefineError( ERR_MCU_MTRTDFAIL				    , ERR_MCU_BGN + 410)

//�˻���Ϊ�ǿ��Ż��飬����ϯ��׼
DefineError( ERR_MCU_NOT_OPENCONF			    , ERR_MCU_BGN + 411)

//�ѽ������ύ��ϯ
DefineError( ERR_MCU_CHAIRMANEXIST			    , ERR_MCU_BGN + 412)

//�����������ϼ�MCU
DefineError( ERR_MCU_HAS_MMCU	                , ERR_MCU_BGN + 413)

//���е��ն˺�MCU�����Ͳ�ƥ��
DefineError( ERR_MCU_CALLEDMT_TYPENOTMATCH		, ERR_MCU_BGN + 420)

//�ն˲��ڿɵ�����Դ�ķ�Χ��
DefineError( ERR_MCU_MT_NOTINVC                 , ERR_MCU_BGN + 421)


//�ն˲���/ָ����ϯ/������[20431-20500]

//ָ���ն���ֻ�����ն�
DefineError( ERR_MCU_RCVONLYMT			        , ERR_MCU_BGN + 430)

//��ָ���ն��Ѿ��ǻ�����ϯ
DefineError( ERR_MCU_SAMECHAIRMAN			    , ERR_MCU_BGN + 431)

//���鴦������ϯģʽ,����ָ����ϯ
DefineError( ERR_MCU_NOCHAIRMANMODE			    , ERR_MCU_BGN + 432)

//����������ϯ
DefineError( ERR_MCU_NOCHAIRMAN				    , ERR_MCU_BGN + 433)

//ָ���ն�δ���
DefineError( ERR_MCU_MT_NOTINCONF			    , ERR_MCU_BGN + 434)

//ָ����MCUδ���
DefineError( ERR_MCU_THISMCUNOTJOIN             , ERR_MCU_BGN + 435)

//ָ���ն��Ѿ��Ƿ����ն�
DefineError( ERR_MCU_SAMESPEAKER			    , ERR_MCU_BGN + 436)

//���������з�����
DefineError( ERR_MCU_HASSPEAKER				    , ERR_MCU_BGN + 437)

//�������޷�����
DefineError( ERR_MCU_NOSPEAKER				    , ERR_MCU_BGN + 438)

//����δ����
DefineError( ERR_MCU_CONFNOTCASCADE             , ERR_MCU_BGN + 439)

//�˲���ֻ����Ա����ն�
DefineError( ERR_MCU_OPRONLYLOCALMT             , ERR_MCU_BGN + 440)

//ָ�����¼�MCU������,��������ʧ��
DefineError( ERR_LOCKSMCU_NOEXIT                , ERR_MCU_BGN + 441)

// �ն˰汾��֧�ְ汾�Ż�ȡ
DefineError( ERR_MCU_MT_NOVERINFO               , ERR_MCU_BGN + 442)

// �ն˵�ý��������֧��ָ������
DefineError( ERR_MT_MEDIACAPABILITY             , ERR_MCU_BGN + 443)


//Media Source Select[20501-20510]

//Դ��Ŀ�ĵ�ý�����Ͳ�ͬ������ѡ��
DefineError( ERR_MCU_NOTSAMEMEDIATYPE           , ERR_MCU_BGN + 500)

//�����������ն˲���ѡ��
DefineError( ERR_MCU_DSTMTNEEDADAPT	    	    , ERR_MCU_BGN + 501)

//����ʱ����ѡ����Ƶģʽѡ��
DefineError( ERR_MCU_SELAUDIO_INMIXING    	    , ERR_MCU_BGN + 502)

//����ʱѡ������Ƶģʽ����Ƶѡ����ʧ��
DefineError( ERR_MCU_SELBOTH_INMIXING           , ERR_MCU_BGN + 503)

//ѡ���ն��޷����ջ���ѡ��Ŀ�겻�ڷ��ͣ��޷�����ָ��ѡ��
DefineError( ERR_MCU_SRCISRECVONLY  	        , ERR_MCU_BGN + 504)

//��ز���ѡ�������ն�
DefineError( ERR_MCU_MCSSELMT_HD                , ERR_MCU_BGN + 505)

//��Ƶѡ�����ܾ�, ѡ��ģʽ�ı�
DefineError( ERR_MCU_SELMODECHANGE_AUDIOFAIL    , ERR_MCU_BGN + 506)
//��Ƶѡ�����ܾ�, ѡ��ģʽ�ı�
DefineError( ERR_MCU_SELMODECHANGE_VIDEOFAIL    , ERR_MCU_BGN + 507)


//�������[20521-20600]

//�������Ȩ��������ض���
DefineError( ERR_MCU_CTRLBYOTHER			    , ERR_MCU_BGN + 520)

//��Ч�Ļ��鱣����ʽ
DefineError( ERR_MCU_INVALID_CONFLOCKMODE	    , ERR_MCU_BGN + 521)

//��Ч���ն˺��в���
DefineError( ERR_MCU_INVALID_CALLMODE	        , ERR_MCU_BGN + 522)

// ��ѯֹͣ����������Ϊ���д���ѯ�ն�û����ƵԴ�����߻��ߴ��������
DefineError( ERR_MCU_POLLING_NOMTORVIDSRC       , ERR_MCU_BGN + 523)

// ָ����ѯλ��ʧ�ܣ���Ϊָ��λ���ն˲�����ѯ�б���
DefineError( ERR_MCU_SPECPOLLPOS_MTNOTINTABLE   , ERR_MCU_BGN + 524)

// ָ����ѯλ��ʧ�ܣ���Ϊָ���ն˲��ڻ�����
DefineError( ERR_MCU_SPECPOLLPOS_MTNOTINCONF	, ERR_MCU_BGN + 525)

// ָ����ѯλ��ʧ�ܣ���Ϊ���鲻����ѯ
DefineError( ERR_MCU_SPECPOLLPOS_CONFNOTPOLL	, ERR_MCU_BGN + 526)

// �޸���ѯ�б�ʧ�ܣ���ǰ��ѯ�ն˲��ܱ�ɾ��
DefineError( ERR_MCU_DELCURPOLLMT_FAIL   	    , ERR_MCU_BGN + 527)


// ����ĵ�������
DefineError( ERR_MCU_ROLLCALL_MODE              , ERR_MCU_BGN + 528)

// ����ĵ���������Ϣ����
DefineError( ERR_MCU_ROLLCALL_MSGLEN            , ERR_MCU_BGN + 529)

// �¼��ն˲�����������
DefineError( ERR_MCU_ROLLCALL_CALLER_SMCUMT     , ERR_MCU_BGN + 530)

// �����˲���Ϊ��
DefineError( ERR_MCU_ROLLCALL_CALLERNULL        , ERR_MCU_BGN + 531)

// �������˲���Ϊ��
DefineError( ERR_MCU_ROLLCALL_CALLEENULL        , ERR_MCU_BGN + 532)

// ǿ�ƹ㲥���ܵ���
DefineError( ERR_MCU_ROLLCALL_MUSTSEESPEAKER    , ERR_MCU_BGN + 533)

// ����ϳɷ�񼰳�Ա�����ʾ
DefineError( ERR_MCU_ROLLCALL_VMPSTYLE          , ERR_MCU_BGN + 534)

// ��������ֹͣ��ʾ
DefineError( ERR_MCU_ROLLCALL_VACING            , ERR_MCU_BGN + 535)

// ���ƻ�����Ա�����ʾ
DefineError( ERR_MCU_ROLLCALL_SPECMIXING        , ERR_MCU_BGN + 536)

// ��������ֹͣ��ʾ
DefineError( ERR_MCU_ROLLCALL_AUTOMIXING        , ERR_MCU_BGN + 537)

// ֹͣ����ϳ���ʾ
DefineError( ERR_MCU_ROLLCALL_VMPING            , ERR_MCU_BGN + 538)

// �����ѡ��ֹͣ��ʾ
DefineError( ERR_MCU_ROLLCALL_SEL               , ERR_MCU_BGN + 539)

// ������ѯ��ʱ��ܾ�����
DefineError( ERR_MCU_ROLLCALL_POLL              , ERR_MCU_BGN + 540)

// �����˵��ߣ�����ֹͣ
DefineError( ERR_MCU_ROLLCALL_CALLERLEFT        , ERR_MCU_BGN + 541)

// �������˵��ߣ�����ֹͣ
DefineError( ERR_MCU_ROLLCALL_CALLEELEFT        , ERR_MCU_BGN + 542)

// ���������ߣ�����ֹͣ
DefineError( ERR_MCU_ROLLCALL_MIXERLEFT         , ERR_MCU_BGN + 543)

// VMP���ߣ�����ֹͣ
DefineError( ERR_MCU_ROLLCALL_VMPLEFT           , ERR_MCU_BGN + 544)

// H264-D1���鲻�����⳧���ն˼���VMP
DefineError( ERR_MCU_NONKEDAMT_JOINVMP          , ERR_MCU_BGN + 545)

// û�п��еĻ�������ֹͣ��ܾ�����
DefineError( ERR_MCU_ROLLCALL_NOMIXER           , ERR_MCU_BGN + 546)

// û�п��е�VMP�� ֹͣ��ܾ�����
DefineError( ERR_MCU_ROLLCALL_NOVMP            , ERR_MCU_BGN + 547)

// VMP�������㣬ֹͣ��ܾ�����
DefineError( ERR_MCU_ROLLCALL_VMPABILITY       , ERR_MCU_BGN + 548)

// VMP�������㣬�л��ϳɷ��
DefineError( ERR_MCU_ROLLCALL_STYLECHANGE      , ERR_MCU_BGN + 549)

// ���ǻ�����صĴ�����

// ��������Ƶ��ʧ��
DefineError( ERR_MCU_NOTGETFREQUENCE           , ERR_MCU_BGN + 550)

// ���ܾܾ������е��ն�
DefineError( ERR_MCU_NMSNOPARTICIPANT          , ERR_MCU_BGN + 551)

// ���ܾܾ��˻���
DefineError( ERR_MCU_NMSNOTAGREE               , ERR_MCU_BGN + 552)

// ԤԼ���鿪����ʱ
DefineError( ERR_MCU_SCHEDTIMEROUT             , ERR_MCU_BGN + 553)

// ������Ӧ��ʱ
DefineError( ERR_MCU_NMSTIMEROUT               , ERR_MCU_BGN + 554)

// ������Ӧ �ܾ�
DefineError( ERR_MCU_NMSNACK                   , ERR_MCU_BGN + 555)



//�����������[20801-21000]

//��ǰ���ڽ��л���¼��
DefineError( ERR_MCU_CONFRECORDING			    , ERR_MCU_BGN + 800)

//��ǰ���ڽ��л���¼��
DefineError( ERR_MCU_CONFNOTRECORDING		    , ERR_MCU_BGN + 801)

//��ǰδ����ͣ����¼��
DefineError( ERR_MCU_CONFNOTRECPAUSE			, ERR_MCU_BGN + 802)

//��ǰ���ڽ��л������
DefineError( ERR_MCU_CONFPLAYING				, ERR_MCU_BGN + 803)

//��ǰ���ڽ��л������
DefineError( ERR_MCU_CONFNOTPLAYING			    , ERR_MCU_BGN + 804)

//��ǰδ����ͣ�������
DefineError( ERR_MCU_CONFNOTPLAYPAUSE		    , ERR_MCU_BGN + 805)

//ָ�����ն˴���¼��״̬
DefineError( ERR_MCU_MTRECORDING			    , ERR_MCU_BGN + 806)

//ָ�����ն�δ����¼��״̬
DefineError( ERR_MCU_MTNOTRECORDING			    , ERR_MCU_BGN + 807)

//ָ�����ն�δ����¼����ͣ״̬
DefineError( ERR_MCU_MTNOTRECPAUSE			    , ERR_MCU_BGN + 808)


//��ǰ���ڽ��л������
DefineError( ERR_MCU_CONFMIXING				    , ERR_MCU_BGN + 810)

//��ǰ���ڽ��л������
DefineError( ERR_MCU_CONFNOTMIXING			    , ERR_MCU_BGN + 811)

//��ǰδ����ͣ�������
DefineError( ERR_MCU_CONFNOTMIXPAUSE		    , ERR_MCU_BGN + 812)

//ָ���ն˲��ǻ������Ա
DefineError( ERR_MCU_MTNOTMIXMEMBER			    , ERR_MCU_BGN + 813)


//�����Ѵ��������������Ʒ���״̬,�����ٴο�ʼ
DefineError( ERR_MCU_CONFINVACMODE  		    , ERR_MCU_BGN + 815)

//����δ���������������Ʒ���״̬,����ֹͣ
DefineError( ERR_MCU_CONFNOTINVACMODE  		    , ERR_MCU_BGN + 816)

//�����Ѵ�������״̬,�����ٴο�ʼ
DefineError( ERR_MCU_CONFINDISCUSSCMODE  	    , ERR_MCU_BGN + 817)

//����δ��������״̬,����ֹͣ
DefineError( ERR_MCU_CONFNOTINDISCUSSCMODE  	, ERR_MCU_BGN + 818)


//�л���ϳ�ģ��ʱ������Ϊ��̬����
DefineError( ERR_MCU_DYNAMCIVMPWITHMODULE       , ERR_MCU_BGN + 820)     

//����ϳ��ѿ�ʼ
DefineError( ERR_MCU_VMPRESTART  			    , ERR_MCU_BGN + 821)

//����ϳ���δ��ʼ,���ܽ��д������
DefineError( ERR_MCU_VMPNOTSTART  			    , ERR_MCU_BGN + 822)

//����ϳ�δ�㲥����
DefineError( ERR_MCU_VMPNOTBRDST                , ERR_MCU_BGN + 823)

//��̬����ʱ�������Զ��ϳ�
DefineError( ERR_MCU_DYNAMICMUSTBYAUTO          , ERR_MCU_BGN + 824)           

//VMP��Ա�ظ�
DefineError( ERR_MCU_REPEATEDVMPMEMBER			, ERR_MCU_BGN + 825)

//�ж��ͨ������ɷ����˸���
DefineError( ERR_MCU_REPEATEDVMPSPEAKER			, ERR_MCU_BGN + 826)

//�ж��ͨ���������ѯ����
DefineError( ERR_MCU_REPEATEDVMPPOLL			, ERR_MCU_BGN + 827)

//�������Ƶ��ѯʱ������ϳ�����֧����ѯ����ͷ����˸���ͬʱ����
DefineError( ERR_AUDIOPOLL_CONFLICTVMPFOLLOW	,	ERR_MCU_BGN + 828)

//VMP��æ
DefineError( ERR_VMPBUSY						,   ERR_MCU_BGN + 829)

//�ϰ�VMP��֧�ָù���
DefineError( ERR_FUNCTIONNOTSUPPORTBYOLDVMP		,	ERR_MCU_BGN + 830)

/*N+1���ݴ���(21401-21500)*/

//���ܴ���ģ�桢����
DefineError( ERR_MCU_NPLUS_CREATETEMPLATE        , ERR_MCU_BGN + 1400)  

//���ܱ༭�û�
DefineError( ERR_MCU_NPLUS_EDITUSER              , ERR_MCU_BGN + 1401)  
 
//��֧���ֶ��ع����û�ѡ�����Զ��ع���
DefineError( ERR_MCU_NPLUS_AUTOROLLBACK          , ERR_MCU_BGN + 1402)

//��Ҫ�ع���MCUδ����
DefineError( ERR_MCU_NPLUS_BAKCLIENT_NOTREG      , ERR_MCU_BGN + 1403)

//�����ڱ�����еĻ���ϳ��޷�������ָ�������û�л���ϳ���
DefineError( ERR_MCU_NPLUS_MASTER_VMP_NONE       , ERR_MCU_BGN + 1404)

//N+1���ݻָ����ǻع��Ļ��飬���鵱ǰ�п��л���ϳ���������֧��������
//����ϳɽ��޷��ָ������ܱ��ݶ˵Ļ���ϳ��������ڱ����˵��¡�(map��,8000B... etc)
DefineError( ERR_MCU_ALLIDLEVMP_NO_SUPPORT_NPLUS , ERR_MCU_BGN + 1405)


/*END OF N+1���ݴ���. */


/* GK/����ƷѴ���(21501-21600) */

//GK��Դ�ľ�GRJ, RRJ, ARJ, LRJ
DefineError( ERR_MCU_RAS_RESOURCE_UNAVAILABLE 	 , ERR_MCU_BGN + 1500)

//������Դ����BRJ
DefineError( ERR_MCU_RAS_INSUFFICIENT_RESOURCE	 , ERR_MCU_BGN + 1503)

//���б�GK�ܾ�
DefineError( ERR_MCU_RAS_GK_REJECT       	     , ERR_MCU_BGN + 1504)

//��Ч���������ַRRJ
DefineError( ERR_MCU_RAS_INVALID_CALLADDR		 , ERR_MCU_BGN + 1505)

//�����Ѿ�����������ʵ��ע��RRJ
DefineError( ERR_MCU_RAS_DUPLICATE_ALIAS	     , ERR_MCU_BGN + 1507)

//�Է�æ
DefineError( ERR_MCU_RAS_MTISBUSY  			     , ERR_MCU_BGN + 1508)

//����ԭ��
DefineError( ERR_MCU_RAS_UNDEFINED				 , ERR_MCU_BGN + 1509)

//�����Ҷ�
DefineError( ERR_MCU_RAS_NORMALDROP				 , ERR_MCU_BGN + 1510)

//GK����ʱ
DefineError( ERR_MCU_RAS_TIMEOUT				 , ERR_MCU_BGN + 1512)

//ע��Gkʧ�ܣ���Ȼ��RASʧ�ܣ��������
DefineError( ERR_MCU_RAS_GKUNREG				 , ERR_MCU_BGN + 1520)

//GK�ڲ�����
DefineError( ERR_MCU_RAS_INTERNALERR 			 , ERR_MCU_BGN + 1521)

//GK�û���������
DefineError( ERR_MCU_GK_USRNAME                  , ERR_MCU_BGN + 1530)

//GK���벻��ȷ
DefineError( ERR_MCU_GK_USRPWD                   , ERR_MCU_BGN + 1531)

//GK���ݿ����
DefineError( ERR_MCU_GK_DB                       , ERR_MCU_BGN + 1532)

//GK���鲻����
DefineError( ERR_MCU_GK_CONF                     , ERR_MCU_BGN + 1533)

//����ʼ�Ʒѳ�ʱ
DefineError( ERR_MCU_GK_STARTCHARGE_TIMEOUT      , ERR_MCU_BGN + 1534)

//��������Ʒѳ�ʱ
DefineError( ERR_MCU_GK_STOPCHARGE_TIMEOUT       , ERR_MCU_BGN + 1535)

//����δ��ȷ��GK����
DefineError( ERR_MCU_GK_UNKNOW                   , ERR_MCU_BGN + 1536)

//GK�����ڣ����ܵ���ģ�崴��ʧ��
DefineError( ERR_MCU_GK_UNEXIST_CREATEMODULE     , ERR_MCU_BGN + 1537)

//GK�����ڣ�����ʧ��
DefineError( ERR_MCU_GK_UNEXIST_CREATECONF       , ERR_MCU_BGN + 1538)

//GK�Ʒѷ�����ע��ʧ��
DefineError( ERR_MCU_GK_REGFAILED                , ERR_MCU_BGN + 1539)

//����Ʒ��쳣
DefineError( ERR_MCU_GK_CONFCHARGE_EXCEPTION 	 , ERR_MCU_BGN + 1540)

//GK�Ʒ���·��
DefineError( ERR_MCU_GK_DISCONNECT		         , ERR_MCU_BGN + 1541)

//GKδ����Radius���������ٿ��Ʒѻ���ʧ��
DefineError( ERR_MCU_GK_WITHOUT_RADIUS           , ERR_MCU_BGN + 1542)

//GK����Radius������ʧ��
DefineError( ERR_MCU_GK_OP_RADIUS_FAILED         , ERR_MCU_BGN + 1543)

//����ļƷ��ʺ��Ѿ���ʹ��
DefineError( ERR_MCU_GK_ACCT_IN_USE              , ERR_MCU_BGN + 1544)

//������GK, ��û�����üƷѹ���, ���ܵ���ģ�崴��ʧ��
DefineError( ERR_MCU_GK_NOCHARGE_CREATEMODULE    , ERR_MCU_BGN + 1545)

//������GK, ��û�����üƷѹ��ܣ�����ʧ��
DefineError( ERR_MCU_GK_NOCHARGE_CREATECONF      , ERR_MCU_BGN + 1546)

//�Ʒ�sessionIdΪ�գ�ֹͣ�Ʒ�ʧ��
DefineError( ERR_MCU_GK_SSNID_NULL               , ERR_MCU_BGN + 1547)

//GK�Ʒѷ���������
DefineError( ERR_MCU_GK_INST_FULL                , ERR_MCU_BGN + 1548)

/*END OF GK/����ƷѴ���*/


/* mcu ���ý��滯������ 21601-21700 */

//�޸�����ʱ��������Ƿ�
DefineError( ERR_MCU_CFG_INVALID_BRD             , ERR_MCU_BGN + 1600)
//������
DefineError( ERR_MCU_CFG_INVALID_MIXER           , ERR_MCU_BGN + 1601)
//¼���
DefineError( ERR_MCU_CFG_INVALID_REC             , ERR_MCU_BGN + 1602)
//vmp
DefineError( ERR_MCU_CFG_INVALID_VMP             , ERR_MCU_BGN + 1603)
//����ǽ
DefineError( ERR_MCU_CFG_INVALID_TVWALL          , ERR_MCU_BGN + 1604)
//��������
DefineError( ERR_MCU_CFG_INVALID_BAS             , ERR_MCU_BGN + 1605)
//�����ش���
DefineError( ERR_MCU_CFG_INVALID_PRS             , ERR_MCU_BGN + 1606)
//�໭�����ǽ
DefineError( ERR_MCU_CFG_INVALID_MTVWALL         , ERR_MCU_BGN + 1607)
//mcu eqp �����Ƿ�
DefineError( ERR_MCU_CFG_INVALID_MCUEQP          , ERR_MCU_BGN + 1608)  //��������� 1610->1608     
//mcu general cfg�����Ƿ�
DefineError( ERR_MCU_CFG_INVALID_MCUGEN          , ERR_MCU_BGN + 1609)  //��������� 1611->1609
//mcu rrq mtadp ipaddr �����Ƿ�
DefineError( ERR_MCU_CFG_INVALID_RRQMTADPIP      , ERR_MCU_BGN + 1610)  //��������� 1612->1610
//����bas
DefineError( ERR_MCU_CFG_INVALID_BASHD           , ERR_MCU_BGN + 1611)  //��������� 1613->1611
//4.6�¼�
//HDU
DefineError( ERR_MCU_CFG_INVALID_HDU             , ERR_MCU_BGN + 1612)
//SVMP
DefineError( ERR_MCU_CFG_INVALID_SVMP            , ERR_MCU_BGN + 1613)
//DVMP
DefineError( ERR_MCU_CFG_INVALID_DVMP            , ERR_MCU_BGN + 1614)
//MPUBAS
DefineError( ERR_MCU_CFG_INVALID_MPUBAS          , ERR_MCU_BGN + 1615)
//EBAP
DefineError( ERR_MCU_CFG_INVALID_EBAP            , ERR_MCU_BGN + 1616)
//EVPU
DefineError( ERR_MCU_CFG_INVALID_EVPU            , ERR_MCU_BGN + 1617)

//д�����ļ�ʧ��
//����
DefineError( ERR_MCU_CFG_WRITE_BRD               , ERR_MCU_BGN + 1620)
//������
DefineError( ERR_MCU_CFG_WRITE_MIXER             , ERR_MCU_BGN + 1621)
//¼���
DefineError( ERR_MCU_CFG_WRITE_REC               , ERR_MCU_BGN + 1622)
//vmp
DefineError( ERR_MCU_CFG_WRITE_VMP               , ERR_MCU_BGN + 1623)
//����ǽ
DefineError( ERR_MCU_CFG_WRITE_TVWALL            , ERR_MCU_BGN + 1624)
//��������
DefineError( ERR_MCU_CFG_WRITE_BAS               , ERR_MCU_BGN + 1625)
//�����ش���
DefineError( ERR_MCU_CFG_WRITE_PRS               , ERR_MCU_BGN + 1626)
//�໭�����ǽ
DefineError( ERR_MCU_CFG_WRITE_MTVWALL           , ERR_MCU_BGN + 1627)

//mcu eqp
DefineError( ERR_MCU_CFG_WRITE_MCUEQP            , ERR_MCU_BGN + 1628)
//����ϳɷ��
DefineError( ERR_MCU_CFG_WRITE_VMPSTYLE          , ERR_MCU_BGN + 1629)
//mcu������Ϣ
DefineError( ERR_MCU_CFG_WRITE_LOCALINFO         , ERR_MCU_BGN + 1630)
//mcu������Ϣ
DefineError( ERR_MCU_CFG_WRITE_NET               , ERR_MCU_BGN + 1631)
//qos
DefineError( ERR_MCU_CFG_WRITE_QOS               , ERR_MCU_BGN + 1632)
//��ͬ��
DefineError( ERR_MCU_CFG_WRITE_NETSYN            , ERR_MCU_BGN + 1633)
//dcs����
DefineError( ERR_MCU_CFG_WRITE_DCS               , ERR_MCU_BGN + 1634)
//MCU���ñ�ʶ
DefineError( ERR_MCU_CFG_WRITE_ISCONFIGED        , ERR_MCU_BGN + 1635)
//dsc����
DefineError( ERR_MCU_CFG_WRITE_DSC			  	 , ERR_MCU_BGN + 1636)
//LoginInfo����
DefineError( ERR_MCU_CFG_WRITE_LOGININFO		 , ERR_MCU_BGN + 1637)
//����bas
DefineError( ERR_MCU_CFG_WRITE_BASHD             , ERR_MCU_BGN + 1638)
//4.6�¼Ӱ汾 jlb
//hdu
DefineError( ERR_MCU_CFG_WRITE_HDU               , ERR_MCU_BGN + 1639)
//SVMP 
DefineError( ERR_MCU_CFG_WRITE_SVMP              , ERR_MCU_BGN + 1640)
//DVMP
DefineError( ERR_MCU_CFG_WRITE_DVMP              , ERR_MCU_BGN + 1641)
//MPUBAS
DefineError( ERR_MCU_CFG_WRITE_MPUBAS            , ERR_MCU_BGN + 1642)
//EBAP
DefineError( ERR_MCU_CFG_WRITE_EBAP              , ERR_MCU_BGN + 1643)
//EVPU
DefineError( ERR_MCU_CFG_WRITE_EVPU              , ERR_MCU_BGN + 1644)

//�޸����õ���Ϊ������ͻ
DefineError( ERR_MCU_CFG_CONFLICT_WITHOTHERMCS	 , ERR_MCU_BGN + 1649)

//��д�ļ�δ֪����
DefineError( ERR_MCU_CFG_FILEERR                 , ERR_MCU_BGN + 1650)

//HduԤ�������������
DefineError( ERR_MCU_CFG_HDUSCHEME_NUM_OVER      , ERR_MCU_BGN + 1651)

//��hdu����ʧ��
DefineError( ERR_MCU_CFG_READ_HDU                , ERR_MCU_BGN + 1652)

//Ԥ�����ڱ�ʹ�ã������޸�
DefineError( ERR_MCU_CFG_CHANGEHDUSCHEME         , ERR_MCU_BGN + 1653)

//�п�Ԥ�����������
DefineError( ERR_MCU_CFG_HDUSCHEMEVOID           , ERR_MCU_BGN + 1654)

//VCSҵ����ش���(21701-)
//VCS����ϯδ���õ���ǽ���������˵���ǽ����������
DefineError( ERR_MCU_VCS_NOUSABLETW               , ERR_MCU_BGN + 1700)
//VCS����ϯδ���û���ϳ������������˵�������
DefineError( ERR_MCU_VCS_NOUSABLEVMP              , ERR_MCU_BGN + 1701)
// VCS��ǰ����ģʽ����Ҫ��ı�Ļ���ģʽ
DefineError( ERR_MCU_VCS_NOMODECHG                , ERR_MCU_BGN + 1702)
// ������ȵ���Դ�ǿɵ�����Դ
DefineError( ERR_MCU_VCS_NOVCSOURCE               , ERR_MCU_BGN + 1703)
// ģʽ�Ѹ��ģ�������ȡ��
DefineError( ERR_MCU_VCS_CANCEL                   , ERR_MCU_BGN + 1704)
// �õ���ϯ���ڱ����ȣ������޸Ļ�ɾ��
DefineError( ERR_MCU_TEMPLATE_INVC                , ERR_MCU_BGN + 1705)
// ѡ����Ƶʧ�ܣ�ѡ���߲�������Ƶ���߱�ѡ���߲�������Ƶ����
DefineError( ERR_MCU_VCS_NOVCMTAUD                , ERR_MCU_BGN + 1706)
// ѡ����Ƶʧ�ܣ�ѡ���߲�������Ƶ���߱�ѡ���߲�������Ƶ����
DefineError( ERR_MCU_VCS_NOVCMTVID                , ERR_MCU_BGN + 1707)
// ѡ������Ƶʧ�ܣ�ѡ���߲���������Ƶ���߱�ѡ���߲���������Ƶ����
DefineError( ERR_MCU_VCS_NOVCMTAV                 , ERR_MCU_BGN + 1708)
// δ��⵽���õĻ�������Դ������������Դ���������෽����Զ�˵�������
DefineError( ERR_MCU_VCS_NOMIXER                  , ERR_MCU_BGN + 1709)
// �����ն˵��ߣ�����������κε��Ȳ������ҵ���ϯ�ָ������״̬
DefineError( ERR_MCU_VCS_LOCMTOFFLINE             , ERR_MCU_BGN + 1710)
// �����ն��������㣬�޷�����ͼ��
DefineError( ERR_MCU_VCS_LOCNOACCEPTVIDEO         , ERR_MCU_BGN + 1711)
// ��ǰ�����ն��������㣬�޷�����ͼ��
DefineError( ERR_MCU_VCS_REMNOACCEPTVIDEO         , ERR_MCU_BGN + 1712)
// �����ն��������㣬�޷���������
DefineError( ERR_MCU_VCS_LOCNOACCEPTAUDIO         , ERR_MCU_BGN + 1713)
// ��ǰ�����ն��������㣬�޷���������
DefineError( ERR_MCU_VCS_REMNOACCEPTAUDIO         , ERR_MCU_BGN + 1714)
// ���ڵ����ն�
DefineError( ERR_MCU_VCS_VCMTING                  , ERR_MCU_BGN + 1715)
// �����ն˳�ʱ
DefineError( ERR_MCU_VCS_VCMTOVERTIME             , ERR_MCU_BGN + 1716)
// �����˿�ͬʱ���е������
DefineError( ERR_MCU_VCS_OVERGROUPNUM             , ERR_MCU_BGN + 1717)
// ��ϯ��ѯ�ѿ���
DefineError( ERR_MCU_VCS_CHAIRPOLLING             , ERR_MCU_BGN + 1718)
// ��ǰ����ϯ�������ʱ������������������������
DefineError( ERR_MCU_VCS_OVERADDMTNUM             , ERR_MCU_BGN + 1719)

//��ǰ����Ա���߱������û����Ȩ��
DefineError( ERR_MCU_VCS_NOTALLOWOPR              , ERR_MCU_BGN + 1720)
//MCS��VCS����ͬʱ��½
DefineError( ERR_MCU_VCSMCS_LOGONLYONE            , ERR_MCU_BGN + 1721)
//����MCU��������VCS����
DefineError( ERR_MCU_VCSMCS_LOGVCSNUMOVER         , ERR_MCU_BGN + 1722)
//VCS������޸�ʧ��
DefineError( ERR_MCU_VCS_WRITESOTTNAME            , ERR_MCU_BGN + 1723)
//����ͬʱ�ٿ�VCS��MCS����
DefineError( ERR_MCU_VCSMCS_ONETYPECONF           , ERR_MCU_BGN + 1724)
//��ǰ����ϯ�ѽ��뼶��ģʽ�����ڱ��ϼ����ȣ������޷�����
DefineError( ERR_MCU_VCS_MMCUINVC                 , ERR_MCU_BGN + 1725)
//**����ϯ���ڵ����У��޷����뼶��ģʽ�������޷�����
DefineError( ERR_MCU_VCS_SMCUINVC                 , ERR_MCU_BGN + 1726)
//δ��⵽���õĻ�������Դ������������Դ����������ģʽ����������
DefineError( ERR_MCU_VCS_NOMIXSPEAKER             , ERR_MCU_BGN + 1727)
//ָ���ն�æ���ڻ�����,�Ƿ����ǿ��
DefineError( ERR_MCU_VCS_MTBUSY					  , ERR_MCU_BGN + 1728)


/* �û�����ģ����չ�Ĵ����� 19900-20000 */

DefineError( UM_EX_START                         , 19900 )
// �û�����
DefineError( UM_EX_USRGRPFULL                    , UM_EX_START + 1 )
// �����Ѵ���
DefineError( UM_EX_USRGRPDUP                     , UM_EX_START + 2 )
// �鲻����
DefineError( UM_EX_USRGRPNOEXIST                 , UM_EX_START + 3 )
// ��ID�Ѵ���
DefineError( UM_EX_USRGRPIDDUP                   , UM_EX_START + 4 )
// ��ID�Ƿ�
DefineError( UM_EX_USRGRPIDINV                   , UM_EX_START + 5 )


DefineErrorEnd
};

#undef DefineError
#undef DefineErrorEnd


#endif /* _ERR_MCU_H_ */


