 /*****************************************************************************
   ģ����      : mcu
   �ļ���      : mcuinttest.h
   ����ļ�    : 
   �ļ�ʵ�ֹ���: Eqp���ɲ��Խӿ�˵��
   ����        : zhangsh
   �汾        : V3.5  Copyright(C) 2001-2004 KDC, All rights reserved.
-----------------------------------------------------------------------------
   �޸ļ�¼:
   ��  ��      �汾        �޸���      �޸�����
   2004/09/11  3.5         zhangsh       ����
******************************************************************************/
#ifndef __MCUEQPINT_H_
#define __MCUEQPINT_H_
#include "kdvtype.h"
#include "osp.h"
#include "codeccommon.h"
#include "mcustruct.h"
#include "eqpcfg.h"
#ifdef WIN32
    #pragma comment( lib, "ws2_32.lib" ) 
    #pragma pack( push )
    #pragma pack( 1 )
    #define window( x )	x
#else
    #include <netinet/in.h>
    #define window( x )
#endif

#define MIXLISTEN_PORT 2031
#define BASLISTEN_PORT 2032
#define TWLISTEN_PORT 2033
#define PRSLISTEN_PORT 2034
#define VMPLISTEN_PORT 2035
struct TKDVVMPParam
{
	u8          m_byVMPStyle;      //����ϳɷ��,�μ�mcuconst.h�л���ϳɷ����
	u8    	    m_byEncType;       //ͼ���������
	u16         m_wBitRate;        //���������(Kbps)
	u16   	    m_wVideoWidth;     //ͼ����(default:720)
	u16   		m_wVideoHeight;    //ͼ��߶�(default:576)
	u8      	m_byMemberNum;     //�μ���Ƶ���ϵĳ�Ա����
	TMt        	m_atMtMember[16];  //��Ƶ���ϳ�Ա�����ո��Ϸ�ʽ���߼����˳��
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TVmpWorkData
{
	u16 m_wLocalPort;//��ʼ�˿ں�,�������ļ�����
	BOOL32 m_bConnected; //��·״̬
	TNetAddress m_tSndAddr[2];   //�ϳɺ������ַ
	BOOL32  bDbVid;	//�Ƿ�˫��Ƶ	
	u8      channelnum;
	TKDVVMPParam tParam[2];	
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TBasWorkData
{
	//��ʵ���������ݳ�Ա
	static  unsigned long       m_dwMcuRcvIP;//MCU ���յ�ַ
	static  unsigned short        m_wMcuRcvStartPort;//MCU ������ʼ�˿ں�
	static  unsigned char        m_byChnNum;//ͨ������
	static  TEqpCfg     m_tCfg;//����������
	static  TEqp        m_tEqp;//���豸
	static  u32         m_bEmbedMcu; //�Ƿ���Ƕ��MCU��
	CConfId             m_cConfId;    // ���������Ļ���ID
	unsigned short                m_wLocalBindPort; //���ذ���ʼ�˿ں�    
	unsigned short                m_wLocalRcvPort;  //���ؽ�����ʼ�˿ں�
	unsigned char                m_byGrpIdx; //��
	unsigned char                m_byChnIdx; //ͨ������
	unsigned char                m_bySN;
	TBasChnStatus       m_tChnStatus;
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TPrsWorkData
{
	u16      m_wLocalPort;//��ʼ�˿ں�,�������ļ�����
	int       m_byMcuNode; //���ӵ�MCUNode��
	BOOL     m_bConnected; //��·״̬
	TPrsCfg m_tPrsCfg;      //��������
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TTwWorkData
{
	u32        m_dwMcuIId ;// ͨ��mcu��ʾ
    u32        m_dwMcuNode;// ��MCUͨ�Žڵ��
	u8          m_byTvNum;  // ����ǽ������
	TEqpCfg     m_tCfg;
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TEqpWorkData
{
	union
	{
		TTwWorkData tTw;
		TPrsWorkData tPrs;
		TBasWorkData tBas;
		TVmpWorkData tVmp;
	}m_tData;
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

class CMcuEqpIntTester/**/
{	
private:
	u32  m_dwMcuNode;
public:
    CMcuEqpIntTester();
    virtual ~CMcuEqpIntTester();
public:
	
	//����Tester��ָ��Vmp������
	virtual BOOL ConnectEqp( u32 dwVmpIp, //Mcu Ip��ַ
					 u16 wPort    //Mcu �����˿�
					 );

	//�Ͽ�Tester��vmp�������
	virtual BOOL DisconnectEqp();

	//��ȡ
	/*
	*	#define     AID_MIXER						62	//������
	#define     AID_TVWALL						63	//����ǽ
	#define     AID_RECORDER					64	//¼���
	#define     AID_DCS							65	//���ݻ��������
	#define     AID_BAS							66	//�������������
	#define     AID_MP							67	//MP
	#define	    AID_VMP			1��ʵ��			68	//����ϳ���
	#define     AID_PRS							69  //���ط�
	 */
	virtual BOOL GetEqpData(u16 wApp,u16 ins,TEqpWorkData &data);
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

#ifdef WIN32
#pragma pack( pop )
#endif

#endif