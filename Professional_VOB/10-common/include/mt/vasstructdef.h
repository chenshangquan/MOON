/*****************************************************************************
   ģ����      : VAS
   �ļ���      : VasEventDef.h
   ����ļ�    : 
   �ļ�ʵ�ֹ���: �ṹ����
   ����        : 
   �汾        : 
-----------------------------------------------------------------------------
   �޸ļ�¼:
   ��  ��      �汾        �޸���      �޸�����

******************************************************************************/
#ifndef _VAS_STRUCT_DEF_H
#define _VAS_STRUCT_DEF_H

#include "eventid.h"

//===========================================
//��������
//=============================================
//��������������ͨ����
#define MAXNUB_AVCHAN    16
//����ͨ�����ĳ���
#define MAXLEN_CHANNAME  16


//===========================================
//�ṹ����
//=============================================
#ifdef WIN32
#pragma pack( push )
#pragma pack(1)
#define PACKED 
#else
#define PACKED __attribute__((__packed__))	// ȡ�����������Ż�����
#endif // WIN32

typedef struct tagVasSwitcher
{
	u8 m_byMediaType;//ý������
	u8 m_byInputChann;//����ͨ����
	u8 m_byOutputChann;//���ͨ����
}PACKED TVasSwitcher;

//����ʱ��������
typedef struct tagVasStart
{    
	u32  m_dwIP;;//IP��ַ
	u16 m_wPort;//�˿�
	u8 m_byInputNumber;//����Դ��Ŀ
}PACKED TVasStart;

//��ѯ����
typedef struct tagVasRolling
{    
	u8 m_byMediaType;//ý������
	u8 m_byBeginChann;//��ʼͨ����
	u8 m_byEndChann;//����ͨ����
	u8 m_byoutputChann;//���ͨ����
	u16 m_dwTime;//���ʱ��
	
}PACKED TVasRolling;

//�������÷���
typedef struct VasConfiguAsk
{    
	u8 m_byMediaType;//ý������
	u8 m_byIndex;//����������
	
}PACKED TVasConfiguAsk;

//���÷���
typedef struct tagVasConfigure
{
	u8 m_abyOutputChan[MAXNUB_AVCHAN];//�����ͨ������Ӧ������ͨ��//��m_abyOutputChan[3]=7 ��ʾ ��4���ͨ�����ӵ���8����ͨ��
	u8 m_abyInputChanName[MAXNUB_AVCHAN][MAXLEN_CHANNAME];//����ͨ����
	u8 m_abyOutputChanName[MAXNUB_AVCHAN][MAXLEN_CHANNAME];//���ͨ����
	
	u8 m_byConfigureID;//���÷���������
	u8 m_byMediaType;//ý������

}PACKED TVasConfigu,TVasConfig;



#ifdef WIN32
#pragma pack( pop )
#endif // WIN32

#endif // _VAS_STRUCT_DEF_H



