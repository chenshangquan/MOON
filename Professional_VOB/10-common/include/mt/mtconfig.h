/*******************************************************************************
 *  ģ����   : ϵͳ����                                                        *
 *  �ļ���   : SysConfg.h                                                      *
 *  ����ļ� : SysConfg.cpp                                                    *
 *  ʵ�ֹ��� : ϵͳ������ȡ������                                              *
 *  ����     : �� ��                                                           *
 *  �汾     : V4.0  Copyright(c) 1997-2005 KDC, All rights reserved.          *
 *                                                                             *
 *    =======================================================================  *
 *  �޸ļ�¼:                                                                  *
 *    ��  ��      �汾        �޸���      �޸�����                             *
 *  2005/8/5  1.0         �� ��      ����          *
 *                                                                             *
 *******************************************************************************/


#ifndef MTCONFG_H
#define  MTCONFG_H

#include "cnconst.h"
#include "tptype.h"
#include "tpstruct.h"
#include "mtconfigex.h"
#include "addrbook.h"
#include "tpstruct.h"
//	�������ýӿ�
//	�μ��ط�ʽ��
//�����ݽṹ�����ˣ�
//�����и�����������ϵͳ����ʱ�Ǻμ��صģ�
//����Ӧ��Bitλ��1������ͨ���ļ����أ�
//����������ֶβ�δ�����������ļ��ж�����ϵͳ������Ĭ��ֵ��
struct tagTConfigKeySrc
{
	u32 Language : 1;
	u32 Ethnet   : 1;
	u32 H323     : 1;
	u32 H320     : 1;
	u32 SIP      : 1;
	u32 Sat		 : 1;
	u32 Aliase   : 1;
	u32 E164     : 1;
	u32 GK       : 1;
	u32 H239     : 1;
	u32 UserPWD  : 1;
	u32 NetPWD   : 1;
	u32 UserPWDEnable     : 1;
	u32 NetPWDEnable      : 1;
	u32 EncryptArithmetic : 1;
};
typedef struct tagTConfigKeySrc TConfigKeySrc ;



//ϵͳ��ʼ������
BOOL InitCfg(void);

//�˳�ϵͳ
void QuitCfg(void);

// �����¼Ӷ�д�����ļ��ĺ����ӿ�, ��mtb����ʹ��

// ϵͳ��ʼ������ 
BOOL MtbClientInitCfg(const s8* szFileName, EmMtModel emMtModel);

// �����ڴ���ϢΪĬ��ֵ����
BOOL MtbClientSetDefaultConfigData(EmMtModel emMtModel);

// �����ڴ���Ϣ�������ļ�����
BOOL MtbClientSaveConfigData(const s8* szFileName);

// ���������ļ���Ϣ���ڴ溯��
BOOL MtbClientLoadConfigData(const s8* szFileName);

// �������ļ����浽�ڴ�ͬʱ���������ļ�������Ϣ FIXME: �ж��Ƿ���Ҫ�Ƚ��г�ʼ������
u8 ReadAndSaveDataToCfgFile(const s8* szFileName);

//��ȡ�汾������Ϣ
BOOL mtGetLanguageInfo(EmLanguage& emLanguage);
//���ð汾��������
BOOL mtSetLanguageInfo(EmLanguage emLanguage);

//��ȡ�û��Ƿ������û�����
BOOL mtGetUserPassEnable(BOOL& bEnable);

//�����û��Ƿ������û�����
BOOL mtSetUserPassEnable(BOOL bEnable);

//��ȡ�û�����
BOOL mtGetUserPass(s8 achPass[]);

//�����û�����
BOOL mtSetUserPass(const s8 achPass[]);

//��ȡ�û��Ƿ�������������
BOOL mtGetNetPassEnable(BOOL& bEnable);

//�����û��Ƿ�������������
BOOL mtSetNetPassEnable(BOOL bEnable);

//��ȡ�û���������
BOOL mtGetNetPass(s8 achPass[]);

//�����û���������
BOOL mtSetNetPass(const s8 achPass[]);

//������ʶ�����Ƿ������ļ����ص�
BOOL mtGetConfigKeySrc( TConfigKeySrc& tConfigKeySrc);

//	�������ýӿ�
//IP ��������(IP Quality of Service��)
//IP QoS��ָIP�ķ���������Ҳ��ָIP������ͨ������ʱ�����ܡ�
//����Ŀ�ľ������û��ṩ�˵��˵ķ���������֤��
//Ŀǰ�ն�IP QOS�ṩ�������͵Ĳ������ü� ���ַ���(DiffServ)��IP���ȡ�
//ͨ������API���Զ���Ƶ�����е�������ݡ���Ƶ����Ƶ����QoS��
//��ȡ�ն�Qos��Ϣ��ֵ�洢��tIPQos�ṹ��
//������ȡ�����ź�����ʱ����FALSE;
BOOL  mtGetIPQoS (TIPQoS&  tIPQoS );

//�����ն�Qosֵ
//������ȡ�����ź�����ʱ����FALSE;
BOOL  mtSetIPQos(const TIPQoS&  tIPQoS );

// ��ȡ����ָ��̫������
//��ȡ�ն���̫�����ã�ֵ�洢��ptTEthnetInfo�ṹ��
// ������ȡ�����ź�����ʱ����FALSE;
BOOL mtGetEthnet(u8 byIndex, TEthnetInfo& tTEthnetInfo );

//�����ն���̫�����ã�ֵ�洢��ptTEthnetInfo�ṹ��
//������ȡ�����ź�����ʱ����FALSE;
//����˵����
BOOL mtSetEthnet(u8 byIndex, const TEthnetInfo& tTEthnetInfo);

//��ȡ�û�ѡ���ĸ�����
BOOL mtGetNetInfSel(u8& byNetInfSel);

//�����û�ѡ���ĸ�����
BOOL mtSetNetInfSel(u8 byNetInfSel);

//��ȡ�û��Ƿ�����E1����
BOOL mtGetE1EncryptInfo(u32& dwE1Encrypt);

//�����û��Ƿ�����E1����
BOOL mtSetE1EncryptInfo(u32 dwE1Encrypt);

//E1����
//��ȡ�ն�E1���ã�ֵ�洢��tE1Unit�ṹ��
//������ȡ�����ź�����ʱ����FALSE;
BOOL  mtGetE1Info(u8 byIndex ,TE1Unit& tE1Info );

//�����ն�E1���ã�ֵ�洢��tE1Unit�ṹ��
//������ȡ�����ź�����ʱ����FALSE;
BOOL  mtSetE1Info(u8 byIndex, const TE1Unit& tE1Info );

//E1������
//��ȡ�ն�E1�����ã�ֵ�洢��tE1Group�ṹ��
//������ȡ�����ź�����ʱ����FALSE;
BOOL  mtGetE1GroupInfo(u8 byIndex ,TE1Group& tE1GroupInfo );

//��ȡ�ն�E1�����ã�ֵ�洢��tE1Group�ṹ��
//������ȡ�����ź�����ʱ����FALSE;
BOOL  mtSetE1GroupInfo(u8 byIndex, const TE1Group& tE1GroupInfo );

/******* ��ȡ,����WiFi�������� **********/

//��ȡ�ն�WiFi�������ã�ֵ�洢��tWiFiCfg�ṹ��
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtGetWiFiNetCfgInfo( TWiFiNetCfg& tWiFiCfg );

//�����ն�WiFi��������
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtSetWiFiNetCfgInfo( const TWiFiNetCfg& tWiFiCfg );

//�����ն�WiFi BSSID����
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtSetWiFiBSSIDCfgInfo(const TWiFiBSSIDCfg tWiFiBSSIDCfg[] );

//��ȡ�ն�WiFi BSSID���ã�ֵ�洢��TWiFiBSSIDCfg�ṹ��
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtGetWiFiBSSIDCfgInfo( TWiFiBSSIDCfg tWiFiBSSIDCfg[] );
  
//·������
//��ȡ�ն�·�����ã�ֵ�洢��aptTRouteCfg�ṹ�����У�
//������ȡ�����ź�����ʱ����FALSE;
BOOL  mtGetRoute(TRouteCfg aptTRouteCfg[]);

//�����ն�·�����ã�ֵ�洢��aptTRouteCfg�ṹ��,
//������ȡ�����ź�����ʱ����FALSE;
BOOL  mtSetRoute(const TRouteCfg aptTRouteCfg[]);

//���ô����ip��ַ����
//��ȡ�����ip
BOOL mtGetPxyIP( TPxyIPCfg aptTPxyIPCfg[] );
//���ô����ip
BOOL mtSetPxyIP(const TPxyIPCfg aptTPxyIPCfg[]);

BOOL mtGetAllChairPollScheme( TMtPollInfo atMtPollInfo[] );
BOOL mtSetAllChairPollScheme( const TMtPollInfo atMtPollInfo[] );
BOOL mtGetOneChairPollScheme( TMtPollInfo &tMtPollInfo, u32 dwIndex );
BOOL mtSetOneChairPollScheme( const TMtPollInfo &tMtPollInfo, u32 dwIndex );

BOOL mtGetOneChairPollSchemeName( char achMtPollSchemeName[MT_MAX_NAME_LEN + 1], u32 dwIndex );
BOOL mtSetOneChairPollSchemeName( const char achMtPollSchemeName[MT_MAX_NAME_LEN + 1], u32 dwIndex );

// PPPOE����
//��ȡ�ն�PPPOE���ã�ֵ�洢��tPPPOECfg�ṹ��
//������ȡ�����ź�����ʱ����FALSE;
BOOL  mtGetPPPOE(TPPPOECfg& tPPPOECfg );

//�����ն�PPPOE���ã�ֵ�洢��tPPPOECfg�ṹ��
//������ȡ�����ź�����ʱ����FALSE;
BOOL  mtSetPPPOE(const TPPPOECfg &tPPPOECfg );

//��������mc�ش�����
BOOL  mtGetMcRSParam(TMTRSParam& tMcRSParam );
BOOL mtSetMcRSParam(const TMTRSParam &tMcRSParam );

//��������(������Ҫ��Ӵ���Ĭ��ֵ)
//���ݴ������ͻ�ȡ�ն���Ӱ���ڵ����ò�����
//���ڵ����ò����洢�� tSerialCfg�Ľṹ��
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtGetSerialCfg( EmSerialType ,TSerialCfg& tSerialCfg );

//���ݴ������������ն˴��ڵ����ò�����
//���ڵ����ò����洢�� tSerialCfg�Ľṹ�С�
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtSetSerialCfg( EmSerialType ,const TSerialCfg& tSerialCfg );

// Add [lj - 2010/05/17]
// �õ���ǰѡ�񴮿�����
// ����ѡ����洢��nSerialType��
// ������ȡ�����ź�����ʱ����FALSE;
BOOL mtGetSerialTypeSel( EmSerialType &nSerialType );

// Add [lj - 2010/05/17]
// ���õ�ǰѡ�񴮿�����
// ����ѡ��������洢��nSerialType��
// ������ȡ�����ź�����ʱ����FALSE;
BOOL mtSetSerialTypeSel( EmSerialType nSerialType );

//�ն���Ϣ����
//��ȡ�����ն˱���
//�ն˱����ṩ�ն�һ�ֱ�ʶ��
//��H323����ϵͳ��Ҳ������H323Id����
//��ȡ�ն˱����������洢�� abyAliase �����β���ִ���
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtGetAliase( s8 abyAliase[] );

//�����ն˱����������洢�� abyAliase �����β���ִ���
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtSetAliase( const s8 abyAliase[] );

// ��ȡ�����ն�E164����
//H323����ϵͳ�б����� "0123456789#*," ���
//��ȡ�ն�E164���룬����洢��abyE164��
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtGetE164( s8 abyE164[] );

//�����ն�E164���룬����洢��abyE164��
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtSetE164( const s8 abyE164[] );

//�Ƿ�����Զҡ
BOOL mtIsRemoteCtrol(BOOL& Enable);
//�Ƿ�����Զҡ
BOOL mtSetRemoteCtrol(BOOL Enable);

//�Ƿ������������
BOOL mtIsSleepEnable(BOOL& Enable);
//�Ƿ������������
BOOL mtSetSleepEnable(BOOL Enable);

//����ʱ��
BOOL mtGetSleepTimes(u16& Enable);
//����ʱ��
BOOL mtSetSleepTimes(u16 Enable);

//��ȡDHCP
BOOL  mtGetDHCP(BOOL& val);
//����DHCP
BOOL  mtSetDHCP(BOOL val);



//�Ƿ�����H323
//��ѡ��ָ���ն��Ƿ�����H323ҵ��
//���ն���H323��H320��SIPͨѶЭ�����ѡ��һ��
//��ȡ�ն��Ƿ�����H323ҵ���Ƿ�����H323ҵ��洢��Enable��
//������ȡ�����ź�����ʱ����FALSE;
BOOL   mtIsH323Enable(BOOL& Enable );

//�����ն��Ƿ�����H323ҵ���Ƿ�����H323ҵ��洢��Enable��
// ������ȡ�����ź�����ʱ����FALSE;
BOOL   mtH323Enable(BOOL Enable);

//�Ƿ�����H320����
//��ѡ��ָ���ն��Ƿ�����H320ҵ��
//���ն���H323��H320��SIPͨѶЭ�����ѡ��һ��
//��ȡ�ն��Ƿ�����H320ҵ���Ƿ�����H320ҵ��洢��Enable��
//������ȡ�����ź�����ʱ����FALSE;
BOOL   mtIsH320Enable(BOOL& Enable);

//�����ն��Ƿ�����H320ҵ���Ƿ�����H320ҵ��洢��Enable��
//������ȡ�����ź�����ʱ����FALSE;
BOOL   mtH320Enable(BOOL Enable);

// �Ƿ�����SIP����
//��ѡ��ָ���ն��Ƿ�����SIPҵ��
//���ն���H323��H320��SIPͨѶЭ�����ѡ��һ��
//��ȡ�ն��Ƿ�����SIPҵ���Ƿ�����SIPҵ��洢��Enable��
//������ȡ�����ź�����ʱ����FALSE;
BOOL   mtIsSIPEnable(BOOL& Enable);

//�����ն��Ƿ�����SIPҵ���Ƿ�����SIPҵ��洢��Enable��
// ������ȡ�����ź�����ʱ����FALSE;
BOOL   mtSIPEnable(BOOL Enable);

//�Ƿ�����H239
//��ѡ��ָ���ն��Ƿ�����H239ҵ��
//��ȡ�ն��Ƿ�����SIPҵ���Ƿ�����SIPҵ��洢��Enable��
//������ȡ�����ź�����ʱ����FALSE;
BOOL  mtIsUseH239(BOOL& Enable);

//�����ն��Ƿ�����SIPҵ���Ƿ�����SIPҵ��洢��Enable��
//������ȡ�����ź�����ʱ����FALSE;
BOOL  mtSetUseH239(BOOL  Enable);

//��ȡ�ն��Ƿ�����Satҵ���Ƿ�����Satҵ��洢��Enable��
//������ȡ�����ź�����ʱ����FALSE;
BOOL   mtIsSatEnable(BOOL& Enable );

//�����ն��Ƿ�����Satҵ���Ƿ�����Satҵ��洢��Enable��
// ������ȡ�����ź�����ʱ����FALSE;
BOOL   mtSatEnable(BOOL Enable);
// �������
//��ѡ��ָ���ն��Ƿ������������
//��ȡ�ն��Ƿ�������������ܣ��Ƿ�����������ܴ洢��Enable��
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtIsEncrypt(BOOL& Enable);

//�����ն��Ƿ�����������ܣ��Ƿ�����������ܴ洢��Enable��
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtSetEncrypt(BOOL  Enable);
//�����㷨
//��ȡ�ն˼����㷨�������㷨�洢��emModel��
//������ȡ�����ź�����ʱ����FALSE;
BOOL  mtGetEncryArithmetic(EmEncryptArithmetic& emModel);

//�����ն˼����㷨���Ƿ�������������㷨
//������ȡ�����ź�����ʱ����FALSE;
BOOL  mtSetEncryArithmetic(EmEncryptArithmetic emModel);


//��ȡ��������ѡ��
BOOL  mtGetSelectCallRate(u32& dwVal);
//���ú�������ѡ��
BOOL  mtSetSelectCallRate(u32 dwVal);

// ��Ƕ����ǽ��������
//������Ƕ����ǽ����
//��ȡ�ն˷���ǽ�������������ǽ��������洢��tNatProxy��
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtGetEmbedFwNatProxy(TEmbedFwNatProxy& tNatProxy );

//���÷���ǽ������� 
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtSetEmbedFwNatProxy(const TEmbedFwNatProxy& tNatProxy);

// ��̬NATӳ��
//��ȡ�ն˾�̬NAT��ַӳ�䣬��̬NAT��ַӳ������洢��dwAddr��
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtGetStaticNatAddr(TNATMapAddr&  tAddr);

//�����ն˾�̬NAT��ַӳ�� 
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtSetStaticNatAddr(const TNATMapAddr& tAddr);

//���ҵ������
//��ȡ�ն˼��ҵ���л����������ҵ���л������洢��tMonitorService��
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtGetMonitorSerivce(TMonitorService& tMonitorService );

//�����ն˼��ҵ���л�����
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtSetMonitorService(const TMonitorService& tMonitorService );

// ��ȡ����GK��ַ
//��ȡ�ն�GK��ַ��GK��ַ�洢��dwGKIP��
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtGetGKIP(TGKCfg& tGKIP);

//�����ն�GK��ַ
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtSetGKIP(const TGKCfg& tGKIP );

//�����ն�����GK��Ϣ
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtSetInnerGKInfo(const TInnerGKCfg& tInnerGKCfg);

//��ȡ�ն�����GK��Ϣ
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtGetInnerGKInfo(TInnerGKCfg& tInnerGKCfg);

//�����ն����ô�����Ϣ
BOOL mtSetInnerProxyInfo( const TInnerProxyCfg& tInnerProxyCfg );
//��ȡ�ն����ô�����Ϣ
BOOL mtGetInnerProxyInfo( TInnerProxyCfg& tInnerProxyCfg );

//	��������
//��ȡ������Ӧ��ʽ
//��ȡ�ն�Ӧ��ģʽ��Ӧ��ģʽ�洢��Modle��
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtGetAnswerMode(EmTripMode& Modle);

//�����ն�Ӧ��ģʽ
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtSetAnserMode(EmTripMode Modle) ;

// �Ƿ����Զ�����
//��ȡ�ն��Ƿ������Զ�����ģʽ��ֵ�洢��bEnable��
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtIsAutoCallEnable(BOOL& bEnable);

//�����ն��Ƿ������Զ�����ģʽ
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtEnableAutoCall(BOOL  bEnable);


// �Զ������ն˱���
//��ȡ�ն��Զ����е��ն˱�����ֵ�洢��abyAlias��
//������ȡ�����ź�����ʱ����FALSE;
BOOL  mtGetAutoCallMtAlias(s8 abyAlias[]);

//�����ն��Զ����е��ն˱���
//������ȡ�����ź�����ʱ����FALSE;
BOOL  mtSetAutoCallMtAlias (const s8 abyAlias[] );


// �Զ���������
//��ȡ�ն��Զ����е����ʣ�ֵ�洢��wRate��
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtGetAutoCallBitrate(u16& wRate);

//�����ն��Զ����е�����
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtSetAutoCallBitrate(u16 wRate );

// ����ͨ����ʼ�˿ں�
//��ȡ�ն�����ͨ��UDP��ʼ���Ͷ˿ںţ�ֵ�洢��wPort��
//������ȡ�����ź�����ʱ����FALSE;
//BOOL mtGetUDPSndBasePort(u16& wPort );
//�����ն�����ͨ��UDP��ʼ���Ͷ˿ں�
//������ȡ�����ź�����ʱ����FALSE;
//BOOL mtSetUDPSndBasePort(u16  wPort);
//��ȡ�ն�����ͨ��UDP������ʼ�˿ںţ�ֵ�洢��wPort��
//������ȡ�����ź�����ʱ����FALSE;
//BOOL  mtGetUDPRcvBasePort(u16 & wPort);
//�����ն�����ͨ��UDP������ʼ�˿ں�
//������ȡ�����ź�����ʱ����FALSE;
// BOOL  mtSetUDPRcvBasePort(u16 wPort);

//��ȡ�ն�����ͨ��UDP��ʼ�˿ںţ�ֵ�洢��wPort��
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtGetUDPBasePort(u16& wPort);
//�����ն�����ͨ��UDP��ʼ�˿ں�
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtSetUDPBasePort(u16  wPort);

//��ȡ�ն�����ͨ��TCP��׼�˿ںţ�ֵ�洢��wPort��
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtGetTCPBasePort(u16& wPort);

//�����ն�����ͨ��TCP��׼�˿ں�
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtSetTCPBasePort(u16 wPort);

// ��·���ʱ��
//��λ��
//��ȡ�ն���·���ʱ�䣬ֵ�洢��wTimeOut��
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtGetLinkKeepLiveTimeOut(u16& wTimeOut);

//�����ն���·���ʱ��
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtSetLinkKeepLiveTimeOut(u16 wTimeOut );

// �����������
// ��ȡ���ø澯��������ַ
//��ȡ�ն˸澯�������ĵ�ַ��ֵ�洢��dwIP��
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtGetTrapServerIP(u32& dwIP );

//�����ն˸澯�������ĵ�ַ
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtSetTrapServerIP(u32 dwIP);

// ��ȡ��ͬ����
//��ȡ�ն˵Ĺ�ͬ������ֵ�洢��abyName��
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtGetNMPublicName( s8 abyName[]);

//�����ն˵Ĺ�ͬ����
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtSetNMPublicName(const  s8 abyName[] );

//	��ʾ����
// �Զ����л���������
//��ȡ�ն��Ƿ������Զ����л���ֵ�洢��bAuto��
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtIsAutoPIP(BOOL&  bAuto); 

//�����ն��Ƿ������Զ����л�
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtSetAutoPIP(BOOL  bAuto);

// �������ʱ����ʾ��������
//��ȡ�ն��Ƿ����û������ʱ����ʾ���ܣ�ֵ�洢��bShow��
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtIsShowConfLapse(BOOL& bShow);

//�����ն��Ƿ����û������ʱ����ʾ����
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtSetShowConfLaps(BOOL  bShow);

// ̨����ʾ��ʽ����
//���������ȡֵ��Χ��һ����ֵ̬��
//�ٴ�ֻ�ǽ�����EmTripMode����ֵ̬�����������岢����ͬ
//��ȡ�ն�̨����ʾ��ʽ��ֵ�洢��emMode��
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtGetSymbolShowMode(EmLabelType& emMode);

//�����ն�̨����ʾ��ʽ
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtSetSymbolShowMode(EmLabelType emMode);

//��ȡ״̬��ʾ
BOOL mtIsShowState(BOOL& bShow);
//��ȡ״̬��ʾ
BOOL mtSetShowState(BOOL bShow);

//��ȡ״̬��ʾ
BOOL mtGetIsVGAShowLocal(BOOL& bShow);
//��ȡ״̬��ʾ
BOOL mtSetIsVGAShowLocal(BOOL bShow);

// ̨����ʾλ��
//��ȡ̨�����Ͻǵ�����λ��ע:  16 �� X �� 600  ; 8 �� Y �� 500
// ����̨�����Ͻǵ�����λ�ã�ֵ�洢��tPos��
BOOL mtGetSymbolXY(TSymboPoint& tPos);

// ����̨�����Ͻǵ�����λ��ע:  16 �� X �� 600  ; 8 �� Y �� 500
BOOL mtSetSymbolXY(const TSymboPoint& tPos);

//�����ն˱���̨��λ��
BOOL mtSetLabelPosType(const EmLabelPosType& tType);
//��ȡ�ն˱���̨��λ��
BOOL mtGetLabelPosType(EmLabelPosType& tType);


//���ú����ʾ����
BOOL mtGetBannerInfo(TBannerInfo& tInfo);
//��ȡ�����ʾ����
BOOL mtSetBannerInfo(const TBannerInfo& tInfo);
//˫����ʾ��ʽ���ã�û���ҵ�Ĭ��ֵ,�����ı䣬���޸ģ�
//��ȡ�ն�˫����ʾ��ʽ���ã�ֵ�洢��emMode��
//������ȡ�����ź�����ʱ����FALSE;
BOOL  mtGetDualVideoShowMode(EmDualVideoShowMode& emMode);

//�����ն�˫����ʾ��ʽ����
BOOL  mtSetDualVideoShowMode(EmDualVideoShowMode emMode);

//��ȡ��ʾ����ģʽ
BOOL  mtGetDisplayRatio(EmVideoType eVideoType,EmDisplayRatio& emDR);
//������ʾ����ģʽ
BOOL  mtSetDisplayRatio(EmVideoType eVideoType,EmDisplayRatio emDR);

// ϵͳʱ����ʾ���ã�û���ҵ�Ĭ��ֵ,�����ı䣬���޸ģ�
//��ȡ�ն�ϵͳʱ����ʾ���ã�ֵ�洢��bShow��
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtIsShowSysTime(BOOL& bShow);

//�����ն�ϵͳʱ����ʾ����
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtShowSysTime(BOOL  bShow);

//��ȡ�Ƿ��;�̬ͼƬѡ��
BOOL mtGetSendStaticPic( BOOL &bSend );

//�����Ƿ��;�̬ͼƬѡ��
BOOL mtSetSendStaticPic( BOOL bSend );

//��Ƶ����
// ��Ƶ��ѡ����
//��ȡ�ն���Ƶ�ı����ʽ��ֵ�洢��emFormat�У�emTypeΪ��Ƶ����
//������ȡ�����ź�����ʱ����FALSE;
BOOL  mtGetVideoFormatPriorStrategy(EmVideoType emType, EmVideoFormat& emFormat);

//�����ն���Ƶ�ı����ʽ��emTypeΪ��Ƶ����
//������ȡ�����ź�����ʱ����FALSE;
BOOL  mtSetVideoFormatPriorStrategy(EmVideoType emType, EmVideoFormat emFormat);

//��ȡ�ն���Ƶ��ͼ��ֱ��ʣ�ֵ�洢��emFormat�У�emTypeΪ��Ƶ����
//������ȡ�����ź�����ʱ����FALSE;
BOOL  mtGetVideoResolvePriorStrategy(EmVideoType emType, EmVideoResolution& emFormat);

//�����ն���Ƶ��ͼ��ֱ��ʣ�emTypeΪ��Ƶ����
//������ȡ�����ź�����ʱ����FALSE;
BOOL  mtSetVideoResolvePriorStrategy(EmVideoType emType, EmVideoResolution emFormat);


// ��ȡ��������Ƶ��ʽ���ã�δ��ɣ�
//��ȡ�ն������Ƶ����ʽ���ã�ֵ�洢��emStand�У�emTypeΪ��Ƶ����
//������ȡ�����ź�����ʱ����FALSE;
BOOL  mtGetOutVideoStandard(EmVideoType emType, EmVideoStandard& emStand );

//�����ն������Ƶ����ʽ����emTypeΪ��Ƶ����
//������ȡ�����ź�����ʱ����FALSE;
BOOL  mtSetOutVideoStandard(EmVideoType emType  ,EmVideoStandard  emStand);

//��ȡ�ն�������Ƶ����ʽ���ã�ֵ�洢��emStand�У�emTypeΪ��Ƶ����
//������ȡ�����ź�����ʱ����FALSE;
BOOL  mtGetInVideoStandard(EmVideoType emType , EmVideoStandard& emStand );

//�����ն�������Ƶ����ʽ����emTypeΪ��Ƶ����
//������ȡ�����ź�����ʱ����FALSE;
BOOL  mtSetInVideoStandard(EmVideoType emType  ,EmVideoStandard  emStand);

//������ƵԴ����

//��ȡ�ն���ƵԴ�����뷽ʽ��
//emVideoType����������Ƶ����𣨵�һ·���ڶ�·����������
//ֵ�洢��tVideoSource�У�
//ֻ��TvideoSource.emVideoInterface 
//Ϊc���ӵ�ʱ��TvideoSource.byCPortIndex��������
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtGetVideoSource(EmVideoType emVideoType , EmMtVideoPort& tVideoSource);

//�����ն���ƵԴ�����뷽ʽ��
//emVideoType����������Ƶ����𣨵�һ·���ڶ�·����������
//ֵ�洢��tVideoSource��
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtSetVideoSource(EmVideoType emVideoType , EmMtVideoPort  tVideoSource);

//��ȡ�ն˻��������������ֵ����tImageParam
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtGetImageAdjustParam(EmVideoType emVideoType , TImageAdjustParam& tImageParam);

//�����ն˻������������
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtSetImageAdjustParam(EmVideoType emVideoType , const TImageAdjustParam& tImageParam);

//��ý��
//���á���ȡ��ý�����ã��¼��û��Ĭ��ֵ���Ѵ���
//��ȡ�ն���ý�������ֵ����tStream
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtGetStreamMedia(TStreamMedia& tStream );

//�����ն���ý�������ֵ����tStream
//������ȡ�����ź�����ʱ����FALSE
BOOL mtSetStreamMedia(const TStreamMedia& tStream );

//����ͷ����
//��ȡ����������ͷ����(����ͷ���ܳ���һ�����Ѵ���)
//��ȡ�ն������������Ϣ��ֵ����tCfg
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtGetCameraCfg( u8 byIndex,TCameraCfg& atCfg );

//�����ն������������Ϣ��ֵ����tCfg
//������ȡ�����ź�����ʱ����FALSE;
BOOL mtSetCameraCfg( u8 byIndex,const TCameraCfg& atCfg );


//	��Ƶ
// ��Ƶ�����������¼��û��Ĭ��ֵ���Ѵ���
//������������ 
//��ȡ�ն��������������ֵ��ֵ�洢��wVal��
//������ȡ�����ź�����ʱ����FALSE;
BOOL  mtGetInputVolume(u8&  wVal);

//�����ն��������������ֵ
//������ȡ�����ź�����ʱ����FALSE;
BOOL  mtSetInputVolume(u8   wVal);

// �����������
//��ȡ�ն�������������ֵ��ֵ�洢��wVal��
//������ȡ�����ź�����ʱ����FALSE;
BOOL  mtGetOutputVolume(u8& wVal);

//�����ն�������������ֵ
//������ȡ�����ź�����ʱ����FALSE;
BOOL  mtSetOutputVolume(u8 wVal);

//���û����������¼��û��Ĭ��ֵ���Ѵ���
//��ȡ�ն��Ƿ����û���������ֵ�洢��bEnable��
//������ȡ�����ź�����ʱ����FALSE;
BOOL  mtIsAECEnable(BOOL& bEnable);

//�����ն��Ƿ����û�������
//������ȡ�����ź�����ʱ����FALSE;
BOOL  mtEnableAEC(BOOL  bEnable);

//�Զ�������ƣ��¼��û��Ĭ��ֵ���Ѵ���
//��ȡ�ն��Ƿ������Զ�������ƣ�ֵ�洢��bEnable��
//������ȡ�����ź�����ʱ����FALSE;
BOOL  mtIsAGCEnable(BOOL& bEnable);

//�����ն��Ƿ������Զ��������
//������ȡ�����ź�����ʱ����FALSE;
BOOL  mtEnableAGC(BOOL  bEnable);

//
//�Զ��������ƵĹ���
BOOL mtEnableANS( BOOL bEnable );
BOOL mtIsANSEnable( BOOL &bEnable );


//��ȡ�ն���Ƶ�ı����ʽ��ֵ�洢��emFormat��
//������ȡ�����ź�����ʱ����FALSE;
BOOL  mtGetAudioFormatPriorStrategy(EmAudioFormat&  emFormat);

//�����ն���Ƶ�ı����ʽ
//������ȡ�����ź�����ʱ����FALSE;
BOOL  mtSetAudioFormatPriorStrategy(EmAudioFormat  emFormat);

//��ȡ��Ƶ�������
BOOL  mtGetVideoParamter(EmVideoType emType,TVideoParam& atImageInfo);
//������Ƶ�������
BOOL  mtSetVideoParamter(EmVideoType emType,TVideoParam& atImageInfo);
//��ȡ���þ���Ĵ�����������
BOOL mtGetExtronMatrixComType(EmSerialType& emType);
//�������þ���Ĵ�����������
BOOL mtSetExtronMatrixComType(EmSerialType emType);
//��ȡ���þ���Ĵ���IP��ַ
BOOL mtGetExtronMatrixComIP(TIPTransAddr& tIP);
//�������þ���Ĵ���IP��ַ
BOOL mtSetExtronMatrixComIP(const TIPTransAddr& tIP);

//��ȡ�ն˿���̨��������˫���������
BOOL mtGetMtcVideoEncParam( TVideoParam& tParam );

//�����ն˿���̨��������˫���������
BOOL mtSetMtcVideoEncParam( const TVideoParam& tParam );

//��ȡ�����ش�����
BOOL mtGetLostPackResend(TLostPackResend& tInfo);
//���ö����ش�����
BOOL mtSetLostPackResend(const TLostPackResend& tInfo);

BOOL mtIsLostPackParamCustom( BOOL &bCustom );
BOOL mtSetLostPackParamCustom( const BOOL &bCustom );

//��ȡvod�û�����
BOOL mtGetVODUserInfo(TVODUserInfo& tInfo);
//����vod�û�����
BOOL mtSetVODUserInfo(const TVODUserInfo& tInfo);


//��ȡ��ƵԴ��Ϣ
BOOL mtGetVideoSorceInfo(u8 byIndex , s8*const achBuf,u8 byBufSize);
//������ƵԴ��Ϣ
BOOL mtSetVideoSorceInfo(u8 byIndex , const s8*const szStr);

//��ȡĬ����Ƶ��ʾ�ӿ�
BOOL mtGetDefaultVideoIndex(EmVideoType type , EmMtVideoPort& index);
//����Ĭ����Ƶ��ʾ�ӿ�
BOOL mtSetDefaultVideoIndex(EmVideoType type , EmMtVideoPort index);

//8010c��ʾvideo����VGA��0Ϊvideo,����ΪVGA��ˢ����
//��ȡ
//BOOL mtGet8010CShowModel(u16& wVal);
BOOL mtGet8010CShowModel(TVgaOutCfg& tVgaOutCfg);
//����
//BOOL mtSet8010CShowModel(u16 wVal);
BOOL mtSet8010CShowModel(const TVgaOutCfg & tVgaOutCfg);

//�����ն˼����˿�
BOOL  mtSetMTCListenPort(u16 wPort);
//��ȡ�ն˼����˿�
BOOL  mtGetMTCListenPort(u16& wPort);
//��ȡ˫����ע����Ϣ
BOOL  mtGetDualStreamBoxInfo(TDualStreamBoxInfo& tInfo);
//����˫���е�ע����Ϣ
BOOL  mtSetDualStreamBoxInfo(const TDualStreamBoxInfo& tInfo);
//��ȡ�Ƿ�ʹ��MC��Ϣ
BOOL  mtGetUsedMC(BOOL& bUsed);
//�����Ƿ�ʹ��MC��Ϣ
BOOL  mtSetUsedMC(BOOL bUsed);

//��ȡmc����ģʽ
BOOL  mtGetMCModle(EmMCMode& emModel);
//����mc����ģʽ
BOOL  mtSetMCModle(EmMCMode emModel);

//[xujinxing-2006-10-17]
//��ȡmc�Ƿ��Զ�����ϳ�
BOOL mtGetMcAutoVMP(BOOL &bAutoVMP);
//����mc�Ƿ��Զ�����ϳ�
BOOL mtSetMcAutoVMP(BOOL bAutoVMP);


//��ȡ˫�����ʱ�
BOOL  mtGetDualCodeRation(TDualRation& tRation);
//����˫�����ʱ�
BOOL  mtSetDualCodeRation(TDualRation tRation);

/****add by FangTao****/
//����Pcmt��ƵԴ����
BOOL mtSetPcmtCapType(EmCapType &emCapType);
BOOL mtSetTelnetPwd(u8 *pPwd, u16 len);
BOOL mtGetTelnetPwd(s8 * pBuf, u8 bufLen);

//��ȡPcmt��ƵԴ����
BOOL mtGetPcmtCapType(EmCapType &emCapType);

BOOL mtGetPcmtCapFileName(s8*const achBuf,u8 byBufSize);
BOOL mtSetPcmtCapFileName(const  s8 abyName[]);
//��ȡ�ڶ�·��Ƶ���
BOOL  mtGetSecondVideoOutput(BOOL& bIsVGA);
//���õڶ�·��Ƶ���
BOOL  mtSetSecondVideoOutput(BOOL bIsVGA);
//��ȡ�������
BOOL  mtGetMicVolume(u8& byPlus );
//�����������
BOOL  mtSetMicVolume(u8 byPlus );
//����DNS��������ַ
BOOL mtSetDNSSvrAddr(u32_ip dwAddr);
//��ȡDNS��������ַ
BOOL mtGetDNSSvrAddr(u32_ip& dwAddr);
//����LDAP����������
BOOL mtSetLDAPSvrName( const s8 achSrvName[] );
//��ȡLDAP����������
BOOL mtGetLDAPSvrName( s8 achSrvName[] );
//�������ص�ַ
BOOL mtSetWanGWAddr(u32_ip dwAddr);
//��ȡ���ص�ַ
BOOL mtGetWanGWAddr(u32_ip& dwAddr);
//�������ص�ַ
BOOL mtSetLanGWAddr(u32_ip dwAddr);
//��ȡ���ص�ַ
BOOL mtGetLanGWAddr(u32_ip& dwAddr);


// ��ȡ��ݼ�����
BOOL mtSetRapidKey(TRapidKey tRpdKey);
// ���ÿ�ݼ�����
BOOL mtGetRapidKey(TRapidKey &tRpdKey);

// ��ȡ�Ƿ���ô�绰����
BOOL mtSetTelephoneDisable(BOOL bDisable);
// �����Ƿ���ô�绰����
BOOL mtGetTelephoneDisable(BOOL& bDisable);

// ��ȡĬ�ϵ������������ĵ�ַ
BOOL mtGetDefaultUpdateSrvAddr( s8 abySrvAddr[]);
// ��ȡ�û����õ������������ĵ�ַ
BOOL mtGetUserCfgUpdateSrvAddr( s8 abySrvAddr[] );
//����������������ַ
BOOL mtSetUserCfgUpdateSrvAddr(const  s8 abySrvAddr[] );

// ��ȡT2��Ƶ�������
BOOL mtGetT2VideoOut(BOOL& bT2VidOutVideo);
// ����T2��Ƶ�������
BOOL mtSetT2VideoOut(BOOL bT2VidOutVideo);

// ��ȡ�������������
BOOL mtGetLoudspeakerVal(EmMtLoudspeakerVal& emMtLoudspeakerVal);
// �����������������
BOOL mtSetLoudspeakerVal(EmMtLoudspeakerVal  emMtLoudspeakerVal);

//��ȡT2��̫��������λ������
BOOL mtGetLanEthMask(u8 &byLanEthMask);
//����T2��̫��������λ������
BOOL mtSetLanEthMask(u8 byLanEthMask);

//��ȡ��Ԫ������
BOOL mtGetMTU(s32& dwMTU);
//���õ�Ԫ������
BOOL mtSetMTU(s32 tMTU);

// ��ȡ��Ƶ��������
BOOL mtGetAudioPrecedence(u32& dwAudioPrecedence);
// ������Ƶ��������
BOOL mtSetAudioPrecedence(u32 dwAudioPrecedence);
// ��ȡǰ������㷨��������
BOOL mtGetFecType( TFecInfo& tInfo );
// ����ǰ������㷨��������
BOOL mtSetFecType( TFecInfo tInfo );

//��ȡ�����������
BOOL mtGetLastCallRate(u16& wLastCallRate);
//���������������
BOOL mtSetLastCallRate(u16 wLastCallRate);

//��ȡ���е�ַ��¼
BOOL mtGetCallAddrRecord(s8 astrCallAddrRecord[MT_MAXNUM_CALLADDR_RECORD][MT_MAX_H323ALIAS_LEN+1]);
//���ú��е�ַ��¼
BOOL mtSetCallAddrRecord(s8 astrCallAddrRecord[MT_MAXNUM_CALLADDR_RECORD][MT_MAX_H323ALIAS_LEN+1]);
//��ȡ�绰�����¼
BOOL mtGetTeleAddrRecord(s8 astrTeleAddrRecord[MT_MAXNUM_CALLADDR_RECORD][MT_MAX_H323ALIAS_LEN+1]);
//���õ绰�����¼
BOOL mtSetTeleAddrRecord(s8 astrTeleAddrRecord[MT_MAXNUM_CALLADDR_RECORD][MT_MAX_H323ALIAS_LEN+1]);

// ��ȡ������Ƶ�˿�����
BOOL mtGetHdAudioPort( THdAudioPort& tInfo );
// ���ø�����Ƶ�˿�����
BOOL mtSetHdAudioPort( THdAudioPort tInfo );
// ��ȡ�Ƿ������а�����
BOOL mtGetUseSliceCfg( BOOL& bUseSlice );
// �����Ƿ��а�����
BOOL mtSetUseSliceCfg( BOOL bUseSlice );

// ��ȡ����ͼ���������
BOOL mtGetHdImageParam( TImageAdjustParam  atImgParam[] );
// ���ø���ͼ���������
BOOL mtSetHdImageParam( const TImageAdjustParam  atImgParam[] );

//��ȡ����ģʽ����
BOOL mtGetScreenModeCfg( u8& byScreenMode);
//���û���ģʽ����
BOOL mtSetScreenModeCfg( u8 byScreenMode);

BOOL mtGetDVICfg(BOOL& bDVIEnable);

BOOL mtSetDVICfg( BOOL bDVIEnable );

BOOL mtIsAutoSecSrc(BOOL& bDVIEnable);

BOOL mtSetAutoSecSrc( BOOL bDVIEnable );

u32 mtGetHDResCfg( u32& dwHDResEnable );

u32 mtSetHDResCfg( u32 dwHDResEnable );

BOOL mtGetPicPlusCfg( BOOL& bPicPlusEnable );

BOOL mtSetPicPlusCfg( BOOL bPicPlusEnable );

BOOL mtGetAddrEntryInfo( TADDRENTRYINFO& tAddrEntryInfo,  u32 dwIndex );

BOOL mtSetAddrEntryInfo( TADDRENTRYINFO tAddrEntryInfo,  u32 dwIndex );

//��ȡ����ģʽ
BOOL mtGetEthMode( u32& dwEthMode );
//��������ģʽ
BOOL mtSetEthMode( u32 dwEthMode );

// ��ȡ�������ģʽ֡������
BOOL mtGetVideoDisplayFrm( TVideoDisplayFrm& tInfo );
// ���ø������ģʽ֡������
BOOL mtSetVideoDisplayFrm( TVideoDisplayFrm tInfo );

BOOL mtSetVGAFiltStatus(u32 dwVGA012, u32 dwRes, u32 dwVGAFiltStatus );
BOOL mtSetVGAPhaseClock(u32 dwVGA012, u32 dwRes, u32 dwVGAPhaseClock );
BOOL mtGetVGAFiltStatus(u32 dwVGA012, u32 dwRes, u32 &dwVGAFiltStatus );
BOOL mtGetVGAPhaseClock(u32 dwVGA012, u32 dwRes, u32 &dwVGAPhaseClock );

BOOL mtSetDFVGAFiltStatus(u32 dwRes, u32 dwVGAFiltStatus);
BOOL mtSetDFVGAPhaseClock(u32 dwRes, u32 dwVGAPhaseClock);
BOOL mtGetDFVGAFiltStatus(u32 dwRes, u32& dwVGAFiltStatus);
BOOL mtGetDFVGAPhaseClock(u32 dwRes, u32& dwVGAPhaseClock);

//��ȡPCMT��Ƶ����ģʽ
BOOL mtGetPcmtVEncModeCfg( u8& byPcmtVEncMode);
//����PCMT��Ƶ����ģʽ
BOOL mtSetPcmtVEncModeCfg( u8 byPcmtVEncMode);

//�Ƿ�֧�ֶ�pcmt..
BOOL mtGetMorePcMtEnable(BOOL& bEnable);
//BOOL mtSetMorePcMtEnable(BOOL bEnable);


//��ȡ��־����״̬
BOOL mtGetLogStatus( u8& bStatus);
BOOL mtSetLogStatus(u8 bStatus);

//��Ƶ����������ýӿ�
BOOL mtGetCurInnerMatrixSchemeIndex( u8 &byCurInnerMatrixSchemeIndex );
BOOL mtSetCurInnerMatrixSchemeIndex( u8 byCurInnerMatrixSchemeIndex );
BOOL mtGetExtraVideoMoudle( u8 &byExtraVideoMoudle );
BOOL mtSetExtraVideoMoudle( u8 byExtraVideoMoudle );
BOOL mtGetVInnerMatrixSchemeByIndex( TVInnerMatrixScheme &tVInnerMatrixScheme, u8 byIndex );
BOOL mtSetVInnerMatrixSchemeByIndex( TVInnerMatrixScheme tVInnerMatrixScheme, u8 byIndex );
BOOL mtGetAllVInnerMatrixScheme( TVInnerMatrixScheme *ptVInnerMatrixScheme, u8 &bySchemeNum );
//��ȡ��������һ֡�����Լ��ȴ�ʱ��
BOOL mtGetLastBlueandTime( u32 &dwLastBlue, u32 &dwWaitTime );
BOOL mtSetLastBlueandTime( const u32 dwLastBlue, const u32 dwWaitTime );

BOOL mtGet323UseSpecialIp( BOOL& b323UseSpecialIp );
BOOL mtSet323UseSpecialIp( BOOL b323UseSpecialIp );


BOOL mtGetPopChairControl( u32 &dwPopChairControl );
BOOL mtSetPopChairControl( const u32 dwPopChairControl );

//--------------------����ΪSYSAPIת�������ӵ�������--------------------
//��ȡ����������Ϣ��
CConfigEx* GetConfigEx();

//------����ΪmtConfig��mtAgent����Ĵ��벻Ϊ����ģ������------
/*-------------------------------------------------------------
   ��ȡ�������
---------------------------------------------------------------*/
//�û���Ϣ����
typedef struct tagTUserInfo
{
	BOOL                  m_bUserPWDEnable;//�Ƿ������û�����
	EmLanguage            m_emLanguage;//ϵͳ��������
	BOOL                  m_bNetPWDEnable; //�Ƿ�������������
	s8                    m_achUserPWD[MT_MAX_PASSWORD_LEN];//�û�����
	s8                    m_achNetPWD[MT_MAX_PASSWORD_LEN];//��������
	public:
		tagTUserInfo(){memset(this,0,sizeof(struct tagTUserInfo));}
} TUserInfo,*PTUserInfo;

//��������
typedef struct tagSleepInfo
{
	BOOL        m_bIsSleepEnable;//�Ƿ��������
	u16         m_wSleepTimes;//����ʱ��
public:
	tagSleepInfo(){memset(this,0,sizeof(tagSleepInfo));}
}TSleepInfo,*PTSleepInfo;

//�����ն�����
typedef struct tagTLocalInfo
{
	TSleepInfo  m_tSleepInfo;//������Ϣ
	BOOL        m_bUsedMC;   //�Ƿ�ʹ��MC
	EmMCMode    m_emMCModel; //MC���з�ʽ
	BOOL        m_bAutoVMP;  //�Ƿ��Զ����ӻ���ϳ���[xujinxing-2006-10-17]
	u32_ip      m_dwDNSSvrIP;//DNS��������ַ
	s8          m_achLDAPSvrName[MT_MAX_LDAPSERVER_NAME_LEN]; //LDAP����������
	BOOL        m_bIsRemoteCtrol;//�Ƿ�����Զ�̿�֮
	BOOL        m_bDHCP;
	u16         m_wMTCPort;  //�ն˼����˿� 
	s8          m_achLocalAliase[MT_MAX_H323ALIAS_LEN + 1];//�ն˱���
	s8          m_achE164[MT_MAX_E164NUM_LEN + 1];//E164����
	BOOL        m_bDisableTelephone;  // �Ƿ���õ绰����

	s8          m_achDefaultServerAddr[MT_MAX_UPDATASERVER_NAME_LEN]; //ȱʡ������������������
	s8          m_achUserCfgServerAddr[MT_MAX_UPDATASERVER_NAME_LEN]; //�û����õ���������������
	u8          m_byLanEthMask; //����ѡ��(WAN/LAN)���룬1Ϊѡ��LAN��������λ��Ч: MT/GK/PXY
	s32         m_dwMTU; //���Ԫ����
	u32         m_dwAudioPrecedence; // ��������
	u16         m_wLastCallRate; //��һ�κ�������
	s8          m_astrCallAddrRecord[MT_MAXNUM_CALLADDR_RECORD][MT_MAX_H323ALIAS_LEN+1]; // ���е�ַ��¼
	s8          m_astrTeleAddrRecord[MT_MAXNUM_CALLADDR_RECORD][MT_MAX_H323ALIAS_LEN+1]; // �绰�����¼
public:
		tagTLocalInfo(){memset(this,0,sizeof(struct tagTLocalInfo));}
}TLocalInfo,*PTLocalInfo;

//Э������
typedef struct tagTProtocolInfo
{
	BOOL        m_bH323Enable;//����H323Э��
	BOOL        m_bH320Enable;//����H320Э��
	BOOL        m_bSIPEnable;//����SIPЭ��
	BOOL        m_bH239Enable;//����H239Э��
	BOOL        m_bSatEnable;
	public:
		tagTProtocolInfo(){memset(this,0,sizeof(struct tagTProtocolInfo));}
}TProtocolInfo,*PTProtocolInfo;

//��������
typedef struct tagTCallInfo
{
	TDualRation	      m_tDualRation;
	EmTripMode        m_emAnswerMode;//Ӧ��ģʽ
	BOOL              m_bIsAutoCallEnable;//�Ƿ��Զ�����
	BOOL              m_bEncryptEnable;//�����Ƿ����
	EmEncryptArithmetic m_emEncryArithmetic;//�����㷨
	u32               m_dwSelectCallRate;
	u16               m_wAutoCallBitrate;//�Զ���������
	u16               m_wUDPBasePort;//UDP��׼�˿�
	u16               m_wTCPBasePort;//TCP��׼�˿�
	u16               m_wLinkKeepLiveTimeOut;//��·����ʱ��
	s8                m_abyAutoCallMtAlias[MT_MAX_H323ALIAS_LEN];//�Զ����жԶ˱���
	public:
		tagTCallInfo(){memset(this,0,sizeof(struct tagTCallInfo));}
}TCallInfo,*PTCallInfo;

//�澯����
typedef struct tagTTrapServerInfo
{
	u32               m_dwTrapServerIP;//�澯����������
	s8                m_abyNMPublicName[MT_MAX_COMM_LEN];//��ͬ����
	public:
		tagTTrapServerInfo(){memset(this,0,sizeof( struct tagTTrapServerInfo));}
} TTrapServerInfo,*PTrapServerInfo;
//��ʾ��Ϣ
typedef struct tagTDisplayInfo
{
    //[xujinxing]
	TVgaOutCfg        m_tVgaOutCfg; //8010c�����vga����video,��ˢ����
	BOOL              m_bIsAutoPIP;//�Ƿ��Զ����л�
	BOOL              m_bIsShowConfLapse;//�Ƿ���ʾ̨��
	BOOL              m_bIsShowSysTime;//�Ƿ���ʾϵͳʱ��
	BOOL              m_bIsShowState;//�Ƿ���ʾ״̬��Ϣ
	BOOL              m_bVGAShowLocal;//��ʾ���ػ��滹��Զ�˻���
	BOOL              m_bSendStaticPic;//���;�̬ͼƬ
	BOOL              m_bSecondvideoToVGA;//���õڶ�·��Ƶ�����VGA
	//u16               m_w8010cShowModel;//8010c��ʾvideo����VGA��0Ϊvideo,����ΪVGA��ˢ���� 
	EmMtVideoPort     m_abyDefaultVideoIndex[2];
	EmLabelType        m_emSymbolShowMode;//̨����������
	TSymboPoint       m_tSymbolXY;//�Զ���̨��λ��
	EmLabelPosType    m_emLabelPosType;//�ն˱���̨��λ��
	EmDualVideoShowMode  m_emDualVideoShowMode;//˫����ʾģʽ
	BOOL              m_bT2MainVidOutVideo; //T2�汾��Ƶ����Ƿ�ΪVideo
	EmDisplayRatio	emPrimaryDisplayRatio;//��һ·��ʾ����ģʽ
	EmDisplayRatio  emSecondDisplayRatio;//�ڶ�·��ʾ����ģʽ
	public:
		tagTDisplayInfo(){memset(this,0,sizeof(struct tagTDisplayInfo));}
}TDisplayInfo,*PTDisplayInfo;


//��Ƶ��Ϣ
typedef struct tagTVideoInfo
{
	TImageAdjustParam    m_tImageAdjustParam;//��Ƶͼ���������
	EmVideoFormat        m_emVideoFormatPriorStrategy;//��Ƶ�������Ȳ���
	EmVideoResolution    m_emVideoResolvePriorStrategy;//��Ƶ�ֱ������Ȳ���
	EmVideoStandard      m_emOutVideoStandard;//��Ƶ�����׼
	EmVideoStandard      m_emInVideoStandard;//��Ƶ�����׼
	EmMtVideoPort         m_emVideoSource;//��ƵԴ
	public:
		tagTVideoInfo(){memset(this,0,sizeof(struct tagTVideoInfo));}
}TVideoInfo,*PTVideoInfo;
//��Ƶ��Ϣ
typedef struct tagTAudioInfo
{
	BOOL                 m_bIsAECEnable;//�Ƿ����û�������
	BOOL                 m_bIsAGCEnable;//�Ƿ������Զ�����
	BOOL                 m_bIsANSEnable; //�Ƿ������Զ���������
	EmAudioFormat        m_emAudioFormatPriorStrategy;//��Ƶ�������Ȳ���
	u8                   m_byInputVolume;//��������������������
	u8                   m_byOutputVolume;//�������������������
	u8                   m_byMicVolume;
	EmMtLoudspeakerVal   m_emLoudspeakerVal; //����������ֵ��T2�汾��

	public:
		tagTAudioInfo(){memset(this,0,sizeof(struct tagTAudioInfo));}
}TAudioInfo,*PTAudioInfo;

typedef struct tagTExtronMatrixComInfo
{
	//����������Ϊtcpipʱ��һ���ֶ�����
	//���ڷ�����IP ,����ֵΪ0ʱ��ʾʹ�ñ��ش���
	//���ڷ������˿ں�   	
	TIPTransAddr m_tIP;
    EmSerialType m_emSerialType;
}TExtronMatrixComInfo,*PTExtronMatrixComInfo;

//pcmt����
typedef struct tagTPCMTInfo
{
	//������������汾�Ĵ�����ֻ���ֶ��޸������ļ������ṩ�����޸�
	BOOL	m_bMorePcMtEnable;
	//���뷽ʽ������룬Ӳ����
	u8		m_byPcmtVEncMode;
}TPCMTInfo,*PTPCMTInfo;



BOOL  GetUserInfo(TUserInfo&   tUserInfo);
BOOL  GetIPQos(TIPQoS&      tIPQoS);
BOOL  GetEthnetInfo(TEthnetInfo atTEthnetInfo[MT_MAX_ETHNET_NUM]);
BOOL  GetE1Info(TE1Unit  atE1Info[MT_MAX_E1UNIT_NUM]);
BOOL  GetRouteInfo(TRouteCfg   atTRouteCfg[MT_MAX_ROUTE_NUM]);
BOOL  GetPPPOEInfo(TPPPOECfg&   tPPPOECfg);
BOOL  GetSerialInco(TSerialCfg  atSerialCfg[MT_MAX_SERIAL_NUM]);
BOOL  GetLocalInfo(TLocalInfo&  tLocalInfo);
BOOL  GetProtocolInfo(TProtocolInfo&     tProtocolInfo);
BOOL  GetFirwareInfo(TEmbedFwNatProxy&  tEmbedNatProxy);
BOOL  GetNatMapAddrInfo(TNATMapAddr&  tInlineStaticNatAddr);
BOOL  GetMonitorInfo(TMonitorService&   tMonitorSerivce);
BOOL  GetGKInfo(TGKCfg&   tGKIP);
BOOL  GetCallInfo(TCallInfo&  tCallConfig);
BOOL  GetTrapInfo(TTrapServerInfo&   tTrapInfo);
BOOL  GetDisplayInfo(TDisplayInfo&      tDisplayInfo);
BOOL  GetVideoInfo(TVideoInfo      atVideoConfig[MT_MAX_VIDEO_NUM]);
BOOL  GetAudioInfo(TAudioInfo&        tAudioConfig);
BOOL  GetStreamInfo(TStreamMedia&      tStreamMedia);
BOOL  GetCameraInfo(TCameraCfg  atCameraCfg[MT_MAX_CAMERA_NUM]);

//add by fanjunshuang for inner mc
BOOL mtGetDualFormat( EmVideoFormat& emDualFormat );
BOOL mtSetDualFormat( EmVideoFormat emDualFormat );
BOOL mtGetDualRes( EmVideoResolution& emDualRes );
BOOL mtSetDualRes( EmVideoResolution emDualRes );
BOOL mtGetDualFrameRate( u32& dwDualFrameRate );
BOOL mtSetDualFrameRate( u32 dwDualFrameRate );
//end add by fanjunshuang

//����mtcbox���в���
BOOL mtGetMtcBoxCallCfg(TMtcBoxCallCfg  atMtcBoxCallCfg[MAX_MTCBOX_SHORTCUT_CALL_NUM]);
BOOL mtSetMtcBoxCallCfg( EmMtcBoxCallIndex emCallIndex , const TMtcBoxCallCfg &atMtcBoxCallCfg);

//Sip���
BOOL mtGetSipCfg( TSipCfg& tCfg );
BOOL mtSetSipCfg( TSipCfg tCfg );
BOOL mtGetSipDisplayName( s8 achDisplayName[MT_MAX_NAME_LEN+1] );
BOOL mtSetSipDisplayName( s8* achDisplayName );
BOOL mtGetSipUserName( s8 achUserName[MT_MAX_NAME_LEN+1] );
BOOL mtSetSipUserName( s8* achUserName );
BOOL mtGetSipPassword( s8 achPassword[MT_MAX_PASSWORD_LEN+1] );
BOOL mtSetSipPassword( s8* achPassword );
BOOL mtGetSipHostDomain( s8 achDomain[MT_MAX_PROXYSERVER_NAME_LEN] );
BOOL mtSetSipHostDomain( s8* achDomain );
BOOL mtGetSipHostPort( u16& wPort );
BOOL mtSetSipHostPort( u16 wPort );

BOOL mtGetSipRegistrarCfg( TSipRegistrarCfg& tCfg );
BOOL mtSetSipRegistrarCfg( TSipRegistrarCfg tCfg );

BOOL mtGetSipProxy( TEmbedFwNatProxy& tProxy );
BOOL mtSetSipProxy( TEmbedFwNatProxy tProxy );

BOOL mtGetTCNTPEpParam(TMtTPEpParam &tCNTPChannelParam);
void mtSetTCNTPEpParam(TMtTPEpParam tCNTPChannelParam);
void mtSetCnsName(s8  achRoomName[]);

BOOL mtGetCnsIp( u32_ip &dwip );
void mtSetCnsIp( u32_ip dwip );

BOOL mtGetTerPos( u16 &dwPos );
void mtSetTerPos( u16 dwPos );
BOOL mtGetTerCount( u16 &dwCount );
void mtSetTerCount( u16 dwCount );
BOOL mtGetIsTpDual( BOOL &bIsDual );
void mtSetIsTpDual( BOOL bIsDual );

BOOL mtGetAECVal( u32 &dwAECVal );
BOOL mtSetAECVal(const u32 &dwAECVal );

API void  mtconfighelp();
API void  CfgAllData(void);
API void  ResetDallData(void);

#ifndef MTVGACFGNOVALUE 
#define MTVGACFGNOVALUE 0xFE
#endif

#ifndef MTVGACFGRESETVALUE 
#define MTVGACFGRESETVALUE 0xFF
#endif

#endif

