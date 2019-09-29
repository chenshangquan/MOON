/*****************************************************************************
   ģ����      : mcu
   �ļ���      : mcuinttest.h
   ����ļ�    : 
   �ļ�ʵ�ֹ���: MCU���ɲ��Խӿ�˵��
   ����        : ������
   �汾        : V3.0  Copyright(C) 2001-2002 KDC, All rights reserved.
-----------------------------------------------------------------------------
   �޸ļ�¼:
   ��  ��      �汾        �޸���      �޸�����
   2004/01/31  3.0         ������       ����
   2005/01/25  3.6         ����       �ӿ�����
******************************************************************************/

#ifndef __MCUINTTEST_H_
#define __MCUINTTEST_H_

#include "osp.h"
#include "mcuconst.h"
#include "mcustruct.h"
#include "mcuutility.h"
#include "mcudata.h"

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif


class CMcuIntTester/**/
{	
public:
    CMcuIntTester();
    virtual ~CMcuIntTester();

public:
	
	// ����Tester��ָ��MCU�������
	virtual BOOL ConnectMcu( u32 dwMcuIp, // Mcu Ip��ַ
					         u16 wPort    // Mcu �����˿�
					       );

	// �Ͽ�Tester��MCU�������
	virtual BOOL DisconnectMcu();

// 2.2.1  ���鲿�� --------------------------
	
	// 2.2.1.1  ��ȡMCUʱ��
	virtual BOOL GetMcuTime( TKdvTime* ptKdvTime );

	// 2.2.1.2  �õ�Mcu�ϵ�ǰ������Ŀ
	virtual BOOL GetConfCount( OUT  u32 &dwConfCount );

	// 2.2.1.3  �õ�MCU�ϵĻ�����б�
	virtual BOOL GetConfIdList( CConfId* pcConfIdList,// ������б�洢�ռ�
					            u32 dwBufSize     // �洢�ռ��С(Ӧ��Ϊsizeof(CConfId)�ı���,�����MAXNUM_MCU_CONF)
					          );

	// 2.2.1.4  �õ�������Ϣ
	virtual BOOL GetConfInfo( CConfId cConfId,    // �����
					          TConfInfo &tConfInfo// ������Ϣ
					        );

	// 2.2.1.5  �õ������ն��б�
	virtual BOOL GetConfMtList( CConfId cConfId,  // �����
						        TMtExt* ptMtList, // �ն��б�洢�ռ�
						        u32 dwBufSize     // �洢�ռ��С(Ӧ��Ϊsizeof(TMtExt)�ı���,�����2*MAXNUM_CONF_MT)
					          );

	// 2.2.1.6  �õ������ն�����
	virtual BOOL GetConfMtData( CConfId cConfId,  // �����
						        u8 byMtId,        // �ն˺�
						        TMtData &tMtData  // �ն�����
					          );
				
	// 2.2.1.7  �������л���
	virtual BOOL ReleaseAllConf();

	// 2.2.1.8  �豸����
	virtual BOOL RebootMCU();
	
	// 2.2.1.9  �õ�MPC��CRI��DRI�ȸ����CPU��ʹ�����
	virtual BOOL GetCPUUsageOfVeneer();

	// 2.2.1.10	�õ�˫�ٹ��ܻ�����Ϣ
	virtual BOOL GetConfInfoOfTwoSpeed( CConfId cConfId, TConfInfo &tConfInfo );

	// 2.2.1.11	�õ����������Ϣ
	virtual BOOL GetConfEncryptInfo( CConfId cConfId, TMediaEncrypt &tMediaEncrypt );

	// 2.2.1.12	��û��齻����Ϣ
	virtual BOOL GetConfSwitchInfo( CConfId cConfId,            // �����
							        u8 byMpId,                  // MpId  [1, MAXNUM_DRI]
							        TSwitchTable &tSwitchTable  // ������
							      );

    virtual BOOL GetConfSwitchInfo( CConfId cConfId,            // �����
							        TConfSwitchTable &tConfSwitchTable  // ������
							      );

	// 2.2.1.13	��ѯ������ѯ״̬
	virtual BOOL GetConfPollInfo( CConfId cConfId,              // �����
		                          TPollInfo &tPollInfo,         // ��ǰ��ѯ����,����ѯʱ��Ч
								  TConfPollParam &tConfPollParam// ��ѯ�ն��б�
								);

	// 2.2.1.14	�õ��������۲���
	virtual BOOL GetConfDiscussInfo( CConfId cConfId, TDiscussParam &tDiscussParam );

	// 2.2.1.15	�õ��������Ƶ���ϲ���
	virtual BOOL GetConfVMPInfo( CConfId cConfId, TVMPParam &tVMPParam );

	// 2.2.1.16	�õ�Mcu������Ϣ ��32���ֽڱ�����32�ֽ�E164��
	virtual BOOL GetMcuAlias( s8* pszInfoBuf, u8 byBufLen );

	// 2.2.1.17	��ü򵥼���������Ϣ
//	virtual BOOL GetConfInfoOfSCascade( CConfId cConfId, 
//		                                TConfCascadeInfo* ptConfCascadeInfo );

	// 2.2.1.18	��ü򵥼��������ն���Ϣ
	virtual BOOL GetConfAllMtInfOfSCascadeo( CConfId cConfId, 
		                                     TConfAllMtInfo* ptConfAllMtInfo);
	
	// 2.2.1.19	��úϲ�����������Ϣ
//	virtual BOOL GetConfInfoOfUCascade( CConfId cConfId, 
//		                                TConfCascadeInfo* ptConfCascadeInfo );

	// 2.2.1.20	��úϲ����������ն���Ϣ
	virtual BOOL GetConfAllMtInfoOfUCascade( CConfId cConfId, 
		                                     TConfAllMtInfo* ptConfAllMtInfo);

	// 2.2.1.21	�õ�����Mcu�б�
//	virtual BOOL GetConfCascadeMcuList( CConfId cConfId, 
//		                                TConfCascadeInfo* ptConfCascadeInfo );

// 2.2.2  ���貿�� --------------------------

	// 2.2.2.1  �õ������豸��Ϣ
	virtual BOOL GetConfEqp( CConfId cConfId,    // �����
					         TEqp& tVmpEqp,      // ����ϳ�����
					         TEqp& tMixEqp,		 // ��������
					         u8&   byMixGrpId,   // ������ID
					         TEqp& tAdaptEqp,	 // ��������
					         u8&   byBasChnnl,   // ������ͨ����
					         TEqp& tRecEqp,  	 // ¼������
					         u8&   byRecChnnl,	 // ¼���ŵ���
					         TEqp& tPlayEqp,	 // ��������
					         u8&   byPlayChnnl,	 // �����ŵ���
					         TEqp& tPrsEqp,		 // �ش��豸
					         u8&   byPrsChnnl	 // �ش�ͨ��
					       );

	// 2.2.2.2  ���Mcu������������Ϣ������MCU��ע��ģ�
	virtual BOOL GetMcuEqpList( TEqp* ptEqpList, // �豸�б�洢�ռ�
						        u32 dwBufSize    // �洢�ռ��С sizeof(TEqp)*MAXNUM_MCU_PERIEQP 
						      );

	// 2.2.2.3  �õ�ָ���豸״̬
	BOOL GetEqpStatus( u8 byEqpId,                                 // �豸��
					   TPeriEqpData &tPeriEqpData                  // �豸״̬
					 );

	// 2.2.2.4  �õ�ָ������ϳ�������
	virtual BOOL GetCurrEqpVmpData( CConfId cConfId,               // �����
						            u8 byEqpId,                    // �豸��
					                TVMPParam &tVMPParam           // �豸״̬
					              );
	
	// 2.2.2.5  �õ�ָ����������������
	virtual BOOL GetCurrEqpMixerData( CConfId cConfId,             // �����
						              u8 byEqpId,                  // �豸��
					                  TDiscussParam &tDiscussParam // �豸״̬
					                );

	// 2.2.2.6  �õ�Mp��Ϣ��
	virtual BOOL GetMpList( TMpData* ptMpList,   // Mp�б�洢�ռ�
					        u32 dwBufSize    // �洢�ռ��С(Ӧ��Ϊsizeof(TMpData)�ı���,�����MAXNUM_DRI)
					      );

	// 2.2.2.7  �õ�Mp������Ϣ�б�
	virtual BOOL GetMPSwitchInfo( u8 byMpId,                       // MpId  [1, MAXNUM_DRI]
							      TSwitchTable &tSwitchTable       // ������
							    );

	//�Ͽ����������
	virtual BOOL DisconnectEqp(u8 byEqpId);

	
	//���л����ն�
	virtual BOOL GetConfAllMtInfo( CConfId cConfId, TConfAllMtInfo* ptConfAllMtInfo);

	//����MCU�ն���Ϣ
//	virtual BOOL GetOtherMcData( u8 byMcuId, TConfOtherMcInfo &tConfOtherMcInfo );
	
	virtual u32 GetMcuNode();

	virtual BOOL IsUserExist(LPCSTR pszUserName );

private:
	u32  m_dwMcuAppId;
	u32  m_dwMcuNode;
	
}

#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;
#endif