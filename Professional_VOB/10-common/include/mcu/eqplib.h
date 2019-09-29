/*
	����� ��ʼ��������ں���
*/
#ifndef _KDV_EQP_LIB_INI_H_
#define _KDV_EQP_LIB_INI_H_

#include "eqpcfg.h"
//������������ʼ������
BOOL basInit(TEqpCfg* ptCfg);
//bool basInit( TEqpCfg* ptCfg );


//����ǽ��ʼ������
BOOL twInit(TEqpCfg* ptCfg);
//bool  twInit( TEqpCfg* ptCfg );


//��������ʼ������
BOOL mixInit(TAudioMixerCfg* tAudioMixerCfg);
//bool  mixInit(TAudioMixerCfg* tAudioMixerCfg);


// ����ϳɳ�ʼ��
BOOL vmpinit(TVmpCfg * ptVmpCfg);
//void  vmpinit(TEqpCfg* tVmpCfg, u8 byDbVid);

BOOL32 MpwInit(TVmpCfg& tVmpCfg);

BOOL MpuInit( TMpuCfg* ptCfg, u8 byWorkMode, u8 byEqpId2 );
API void vmphelp(void);
API void vmpver(void);

API void twver(void);
API void basver(void);
API void mixerver(void);

API void mmpagtver(void);
API void imtagtver(void);

#ifdef WIN32
API bool prsinit(TPrsCfg* tPrsCfg);
#else
bool prsinit(TPrsCfg* tPrsCfg);
#endif
API void prsver(void);
API void prshelp(void);

#endif/*! _KDV_EQP_LIB_INI_H_*/
