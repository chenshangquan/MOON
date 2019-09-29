//
//��������
//
//
#ifndef _PERIPHERY_EQUIPMENT_CONFIG_H_
#define _PERIPHERY_EQUIPMENT_CONFIG_H_

#include "mcuconst.h"

#define MAXNUM_MAP    5

#define QOS_AUDIO   (s32)1  // ��ƵQos
#define QOS_VIDEO   (s32)2  // ��ƵQos
#define QOS_DATA    (s32)3  // ����Qos


#ifdef WIN32
    #pragma pack( push )
    #pragma pack( 1 )
#endif


struct TMAPParam
{
	u32  dwCoreSpd;     // Map�ں��ٶ�
	u32  dwMemSpd;      // �ڴ��ٶ�
	u32  dwMemSize;     // �ڴ��С
	u8   byMapId;	    // Map���
	u32   dwPort;	    // Map�˿ں�
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//����������ýṹ
struct TEqpCfg
{
	char  achAlias[ MAXLEN_ALIAS+1 ];
	u8    byEqpId;          //����ID
	u8    byEqpType;        //��������

	u32   dwLocalIP;        //����IP��ַ
	u32   dwConnectIP;      //����MCUIP��ַ
	u16   wConnectPort;     //����MCU ͨ�Ŷ˿�
	u16   wMcuId;           //MCU id ��
	u16   wRcvStartPort;    //������ʼ�˿ں�
	u16   wMAPCount;        //ʹ�õ�MAP����
	TMAPParam m_atMap[MAXNUM_MAP];	//map��Ϣ

    u32 dwConnectIpB;
    u16 wConnectPortB;
    u16 wRcvStartPortB;

    TEqpCfg(void) { memset(this, 0, sizeof(TEqpCfg)); }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TAudioMixerCfg : public TEqpCfg
{
	u8    byMaxMixGroupCount;
	u8    byMaxChannelInGroup;
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//��DVMP�����𲽷ϳ��ýṹ��// xliang [5/27/2009] 
struct TVmpCfg : public TEqpCfg
{
	u8   by_VmpStyle;
	u8   byDbVid;
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TPrsCfg:public TEqpCfg
{
    u16  m_wFirstTimeSpan;	    //��һ���ش�����(ms)
	u16  m_wSecondTimeSpan;     //�ڶ����ش�����(ms)
	u16  m_wThirdTimeSpan;      //�������ش�����(ms)
	u16  m_wRejectTimeSpan;     //���ڶ�����ʱ����(ms)
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;
//4.6 �¼Ӱ汾 jlb
struct THduModePort
{
public:
	THduModePort()
	{
		memset(this, 0x0, sizeof(THduModePort));
	}
	u8 GetZoomRate() const { return byZoomRate; }
	void SetZoomRate(u8 val) { byZoomRate = val; }
	
    u8   GetOutPortType() const { return byOutPortType; }
    void SetOutPortType(u8 val) { byOutPortType = val; }
	
    u8   GetOutModeType() const { return byOutModeType; }
    void SetOutModeType(u8 val) { byOutModeType = val; }

private:
    u8 byOutPortType;
    u8 byOutModeType;
    u8 byZoomRate;
    u8 reserved;
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct THduCfg : public TEqpCfg
{
protected:
	BOOL  m_bAutoTest;
	u8   byReserved[4];
    THduModePort atHduModePort[MAXNUM_HDU_CHANNEL];
public:
	THduCfg(void)
	{
        memset(atHduModePort, 0x0, sizeof(atHduModePort));
	}
	void GetHduModePort( u8 byNum, THduModePort &tHduModePortType )
	{
        tHduModePortType.SetOutModeType(atHduModePort[byNum].GetOutModeType());
		tHduModePortType.SetOutPortType(atHduModePort[byNum].GetOutPortType());
		tHduModePortType.SetZoomRate(atHduModePort[byNum].GetZoomRate());
	}
	void SetHduModePort( u8 byNum, THduModePort &tHduModePortType )
	{
        atHduModePort[byNum].SetOutModeType(tHduModePortType.GetOutModeType());
		atHduModePort[byNum].SetOutPortType(tHduModePortType.GetOutPortType());
		atHduModePort[byNum].SetZoomRate(tHduModePortType.GetZoomRate());
	}
	u8   GetEqpId( void ){ return byEqpId; }
	u8   GetEqpType( void ){ return byEqpType; }
    u16   GetMcuId( void ){ return wMcuId; }
    
	BOOL GetAutoTest( void ){ return m_bAutoTest; }
	void SetAutoTest( BOOL bAutoTest ){ m_bAutoTest = bAutoTest; }

}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TMpuCfg : public TEqpCfg
{
protected:
	u8		m_byVmpStyle;
	u8		m_byDbVid;
	u8		m_byReserved1;
	u8		m_byReserved2;
	BOOL32  m_bAutoTest;
public:
	TMpuCfg(void)
	{
		m_bAutoTest = FALSE;
		m_byVmpStyle = 0;
		m_byDbVid	= 0;
	}

	BOOL IsAutoTest( void ){ return m_bAutoTest; }
	void SetAutoTest( BOOL bAutoTest ){ m_bAutoTest = bAutoTest; }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;


#ifdef WIN32
    #pragma pack( pop )
#endif

#endif // _PERIPHERY_EQUIPMENT_CONFIG_H_
