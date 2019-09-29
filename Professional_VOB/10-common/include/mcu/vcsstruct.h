/*****************************************************************************
   ģ����      : mcu
   �ļ���      : vcsstruct.h
   ����ļ�    : 
   �ļ�ʵ�ֹ���: ��VCSͨ�����ýṹ��
   ����        : ���㻪
   �汾        : 
-----------------------------------------------------------------------------
   �޸ļ�¼:
   ��  ��      �汾        �޸���      �޸�����
   2008/11/20              ���㻪      ����
******************************************************************************/
#ifndef __VCSSTRUCT_H_
#define __VCSSTRUCT_H_

#include "osp.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "kdvsys.h"
#include "mcuconst.h"
#include "kdvdef.h"
#include "vccommon.h"
#include "ummessagestruct.h"
#include "mcuerrcode.h"

#define MAX_HDTWDEVNUM      (u8)100        // �������õĸ������ǽģ����
#define MAX_HDTWCHANNUM     (u8)1          // ÿ���������ǽģ��֧�ֵ�ͨ����

// ����ģʽ
#define VCS_SINGLE_MODE     (u8)1      // ��������ģʽ
#define VCS_MULTW_MODE      (u8)2      // �෽����ǽ����ģʽ
#define VCS_MULVMP_MODE     (u8)3      // �෽����ϳɵ���ģʽ
#define VCS_GROUPSPEAK_MODE (u8)4      // ���������ģʽ
#define VCS_GROUPTW_MODE    (u8)5      // �������ǽģʽ
#define VCS_GROUPVMP_MODE   (u8)6      // �������ϳ�ģʽ

// ������������
#define VCS_AUDPROC_MUTE    (u8)0      // ����
#define VCS_AUDPROC_SILENCE (u8)1      // ����

// ������������
#define VCS_OPR_LOCAL       (u8)0      // ��������
#define VCS_OPR_REMOTE      (u8)1      // ����Զ��

// VCS����Ŀ���
#define VCS_ENTRY_MT_MT             (u8)1
#define VCS_ENTRY_MT_MCU            (u8)6
#define VCS_ENTRY_MT_GROUP          (u8)7
#define VCS_ENTRY_MT_CALL_GROUP     (u8)8

// VCS�����ʱ�����ӵĺ����ն���
#define VCS_MAXNEWADDMT_NUM        (u8)32
// VCS���֧�ֵ������
#define VCS_MAXGROUPCALL_NUM       (u8)16
// VCS����������
#define MAX_VCSGROUPNAMELEN        (u8)32

// VCS���Ȳ�������
#define VCS_VCTYPE_DEFAULT         (u8)0
#define VCS_VCTYPE_DROPMT          (u8)1

// VCS����ǿ������
#define VCS_FORCECALL_REQ          (u8)0
#define VCS_FORCECALL_CMD          (u8)1

// VCS��ϯ��ѯ״̬
#define VCS_POLL_START             (u8)1
#define VCS_POLL_PAUSE             (u8)2
#define VCS_POLL_STOP              (u8)3


typedef TMtAlias TSMCUAlias;            // �¼�MCU������Ϣ
typedef TMtAlias THDTWModuleAlias;      // �������ǽ����

// ����������ǽ������,�����ɸ����ն����
struct THDTvWall
{
public:
	THDTvWall()
	{
 		SetNull();
	}
	void SetNull()
	{
		m_byHDTWDevNum = 0;
		m_byReserve    = 0;
		memset(m_awHDTWDialBitRate, 0, sizeof(m_awHDTWDialBitRate));
		memset(m_atHDTWModuleAlias, 0, sizeof(m_atHDTWModuleAlias));
		// ��Ա����ΪTW_MEMBERTYPE_NULL������ָ����ͨ��������
		memset(m_abyMemberType, 0, sizeof(m_abyTvWallMember));
		for (u8 byDevID = 0; byDevID < MAX_HDTWDEVNUM; byDevID++)
		{
			for (u8 byChanID = 0; byChanID < MAX_HDTWCHANNUM; byChanID++)
			{
				// ��ʼ������Ա�������ó�Ϊ�Ƿ���������
				m_abyTvWallMember[byDevID][byChanID] = 0xFF;
			}
		}
	}


public:
	BOOL SetHDTWCfg(u8 byHDTWDevNum, THDTWModuleAlias* const patModuelAlias, u16* const paDialBitRate = NULL)
	{
		if (NULL == patModuelAlias)
		{
			return FALSE;
		}
		THDTWModuleAlias* ptHDTWModuelAlias = patModuelAlias;
		u16* pwHDTWDialBitRate = paDialBitRate;

		m_byHDTWDevNum = byHDTWDevNum;
		for (u8 byDevID = 0; byDevID < byHDTWDevNum; byDevID++)
		{
			m_atHDTWModuleAlias[byDevID] = *ptHDTWModuelAlias++;
			if (pwHDTWDialBitRate != NULL)
			{
				m_awHDTWDialBitRate[byDevID] = *pwHDTWDialBitRate++;
			}

		}
		return TRUE;
	}

	BOOL SetHDTwWallMember(u8 byHDTWDevID, u8 byHDTWChanID, u8 byMTIndex, u8 byMemberType)
	{
		if (byHDTWDevID >= m_byHDTWDevNum || byHDTWChanID >= MAX_HDTWCHANNUM )
		{
			return FALSE;
		}

		m_abyTvWallMember[byHDTWDevID][byHDTWChanID] = byMTIndex;
		m_abyMemberType[byHDTWDevID][byHDTWChanID] = byMemberType;
		return TRUE;
	}

	BOOL GetHDTwWallMember(u8 byHDTWDevID, u8 byHDTWChanID, u8& byMTIndex, u8& byMemberType) const
	{
		if (byHDTWDevID >= m_byHDTWDevNum || byHDTWChanID >= MAX_HDTWCHANNUM)
		{
			return FALSE;
		}

		byMTIndex = m_abyTvWallMember[byHDTWDevID][byHDTWChanID];
		byMemberType = m_abyMemberType[byHDTWDevID][byHDTWChanID];
		return TRUE;
	}
	
	// ��������ǽ�Զ�����ģʽ��ָ�����õ�ͨ����, �����Զ�ģʽ��ͨ����������
	BOOL StartAutoModel(u8 byUsableChanNum)
	{
		// �Ƿ������㹻�ĵ���ǽ�豸֧��ָ����ͨ����
		if (byUsableChanNum > m_byHDTWDevNum * MAX_HDTWCHANNUM)
		{
			return FALSE;
		}
		u8 byCurUsableChanNum = 0;
		for (u8 byDevID = 0; byDevID < m_byHDTWDevNum; byDevID++)
		{
			for (u8 byChanID = 0; byChanID < MAX_HDTWCHANNUM; byChanID++)
			{
				if (byCurUsableChanNum >= byUsableChanNum)
				{
					return TRUE;
				}
				m_abyMemberType[byDevID][byChanID] = TW_MEMBERTYPE_VCSAUTOSPEC;
				byCurUsableChanNum++;				
			}
		}
		return TRUE;
	}

	// �Ƿ������˸������ǽ
	BOOL IsHDTWCfg()  { return m_byHDTWDevNum != 0; }

	u8               m_byHDTWDevNum;
	u8               m_byReserve;
	u16              m_awHDTWDialBitRate[MAX_HDTWDEVNUM];          //���ϸ������ǽ�豸ʹ�õ�����
	THDTWModuleAlias m_atHDTWModuleAlias[MAX_HDTWDEVNUM];
    u8   m_abyTvWallMember[MAX_HDTWDEVNUM][MAX_HDTWCHANNUM];       //����ǽ��Ա������������ʱTMtAlias��������+1��
    u8   m_abyMemberType  [MAX_HDTWDEVNUM][MAX_HDTWCHANNUM];       //����ǽ��Ա��������

	
}
PACKED
;

// VCS�¼�MCU����
struct TVCSSMCUCfg
{
public:
	TVCSSMCUCfg()
	{
 		SetNull();
	}
	void SetNull()
	{
		m_wSMCUNum = 0;
		memset(m_atSMCUAlias, 0, sizeof(m_atSMCUAlias));
		memset(m_awSMCUDialBitRate, 0, sizeof(m_awSMCUDialBitRate));
	}

	// �Ƿ�������VCS�¼�mcu
	BOOL IsVCSMCUCfg() { return m_wSMCUNum != 0; }

	u8         m_wSMCUNum;
	TSMCUAlias m_atSMCUAlias[MAXLIMIT_CONF_SMCU];
	u16        m_awSMCUDialBitRate[MAXLIMIT_CONF_SMCU];
}
PACKED
;

// �ն˷�����Ϣ
struct TVCSGroupInfo
{
	s8  achGroupName[MAX_VCSGROUPNAMELEN];    // �÷�������
	u16 dwEntryNum;                           // �÷���ʵ�����
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;
struct TVCSEntryInfo
{
    TVCSEntryInfo()
    {
        memset( this, 0, sizeof(TVCSEntryInfo) );
    }

	s8 achEntryName[MAX_VCSGROUPNAMELEN];   // �����а����ĸ�ʵ������(��Ϊ�ն˵�164��/IP��ַ/H323ID�������ļ�������)
	u8 byEntryType;                         // ��Ŀ���ͣ�MT/MCU/�飩
    u8 byAddrType;                          // ��ַ���ͣ�H323/E164/IP��
  	u16 wDialBitRate;                       //������
	s8 achUIName[MAX_VCSGROUPNAMELEN];      // ������ʾ������
}
PACKED
;

class CBasicVCCStatus
{
public:
	CBasicVCCStatus()
	{
		DefaultStatus();
	}

    u8   GetCurVCMode()               { return m_byVCMode; }
	void SetCurVCMode(u8 byMode)      { m_byVCMode = byMode; }
	
	const TMt& GetCurVCMT()           { return m_tCurVCMT; }
	void  SetCurVCMT(TMt& tMt)        { memcpy(&m_tCurVCMT, &tMt, sizeof(TMt)); }

    BOOL IsLocMute()                  { return (m_byLocalMuteType & (1 << VCS_AUDPROC_MUTE)) != 0; }
	BOOL IsLocSilence()               { return (m_byLocalMuteType & (1 << VCS_AUDPROC_SILENCE)) != 0;}
	void SetLocAudProcType(u8 byOpenFlag, u8 byMuteType)
	{ 
		m_byLocalMuteType = (byOpenFlag ? (m_byLocalMuteType | (1 << byMuteType)) : (m_byLocalMuteType & (~(1 << byMuteType))));
	}

    BOOL IsRemMute()                  { return (m_byRemoteMuteType & (1 << VCS_AUDPROC_MUTE)) != 0; }
	BOOL IsRemSilence()               { return (m_byRemoteMuteType & (1 << VCS_AUDPROC_SILENCE)) != 0;}
	void SetRemAudProcType(u8 byOpenFlag, u8 byMuteType)
	{ 
		m_byRemoteMuteType = (byOpenFlag ? (m_byRemoteMuteType | (1 << byMuteType)) : (m_byRemoteMuteType & (~(1 << byMuteType))));
	}

	// ��ȡ��������б�
	const s8* GetGroupCallList()
	{
		return (s8*)m_achOnLineGroup;
	}
	// ������������б�
    BOOL32 OprGroupCallList(s8* pachGroupName, u8 byNameLen, u8 byAdd, u16 wErrCode)
	{
		wErrCode = 0;

		if (NULL == pachGroupName)
		{
			OspPrintf(TRUE, FALSE, "[OprGroupCallList] NULL == pachGroupName\n");
			return FALSE;
		}
		
		u8 byExistPos = VCS_MAXGROUPCALL_NUM;
		u8 byEmptPos  = VCS_MAXGROUPCALL_NUM;
		for (u8 byIdx = 0; byIdx < VCS_MAXGROUPCALL_NUM; byIdx++)
		{
			if (!memcmp(pachGroupName, m_achOnLineGroup[byIdx], min(byNameLen, MAX_VCSGROUPNAMELEN)) &&
				min(byNameLen, MAX_VCSGROUPNAMELEN) >= strlen(m_achOnLineGroup[byIdx]))
			{
				byExistPos = byIdx;
				break;
			}
			if (!memcmp(m_achOnLineGroup[byIdx], "", sizeof("")) && VCS_MAXGROUPCALL_NUM == byExistPos)
			{
				byEmptPos = byIdx;
			}
		}
		if (byAdd)
		{ 
			if (byExistPos != VCS_MAXGROUPCALL_NUM)
			{
				OspPrintf(TRUE, FALSE, "[OprGroupCallList] %s has on line\n", m_achOnLineGroup[byExistPos]);
				return TRUE;
			}
			if (VCS_MAXGROUPCALL_NUM == byEmptPos)
			{
				wErrCode = ERR_MCU_VCS_OVERGROUPNUM;
				return FALSE;
			}
			else
			{
				memcpy(m_achOnLineGroup[byEmptPos], pachGroupName, min(byNameLen, MAX_VCSGROUPNAMELEN));
				m_achOnLineGroup[byEmptPos][MAX_VCSGROUPNAMELEN - 1] = 0;
			}
		}
		else
		{
			if (byExistPos != VCS_MAXGROUPCALL_NUM)
			{
				memset(m_achOnLineGroup[byExistPos], 0, sizeof(m_achOnLineGroup[byExistPos]));
			}

		}
		return TRUE;
	}

	// �Ƿ񳬹���֧�ֵ���ʱ������
	BOOL32 IsAddEnable()
	{
		for (u8 byIdx = 0; byIdx < VCS_MAXNEWADDMT_NUM; byIdx++)
		{
			if (m_atNewAddMt[byIdx].IsNull())
			{
				return TRUE;
			}
		}	
		return FALSE;
	}
	// ��ȡ��ʱ�����ն��б�
	const TMt* GetNewMtList()
	{
		return m_atNewAddMt;
	}
	// ������ʱ���е��ն��б�
	BOOL32 OprNewMt(const TMt& tMt, u8 byAdd)
	{
		u8 byExistPos = VCS_MAXNEWADDMT_NUM;
		u8 byEmptyPos = VCS_MAXNEWADDMT_NUM;
		for (u8 byIdx = 0; byIdx < VCS_MAXNEWADDMT_NUM; byIdx++)
		{
			if (m_atNewAddMt[byIdx] == tMt)
			{
				byExistPos = byIdx;
				break;
			}
			if (m_atNewAddMt[byIdx].IsNull() && VCS_MAXNEWADDMT_NUM == byEmptyPos)
			{
				byEmptyPos = byIdx;
			}
		}
		if (byAdd)
		{
			if (byExistPos != VCS_MAXNEWADDMT_NUM)
			{
				return TRUE;
			}
			if (VCS_MAXNEWADDMT_NUM == byEmptyPos)
			{
				return FALSE;
			}
			else
			{
				m_atNewAddMt[byEmptyPos] = tMt;
				return TRUE;
			}
		}
		else
		{
			if (byExistPos != VCS_MAXNEWADDMT_NUM)
			{
				m_atNewAddMt[byExistPos].SetNull();
				return TRUE;
			}

		}
		return FALSE;

	}

	// ��ȡ��ǰ����ϯ��ѯ�ն�
	const TMt& GetCurChairPollMt()
	{
		return m_tMtPolling;
	}
	// ���õ�ǰ����ϯ��ѯ�ն�
	void SetCurChairPollMt(const TMt& tMt)
	{
		m_tMtPolling = tMt;
	}
	// ��ȡ��ϯ��ѯ״̬
	u8 GetChairPollState()
	{
		return m_byPollState;
	}
	void SetChairPollState(u8 byPollState)
	{
		m_byPollState = byPollState;
	}
	// ��ȡ��ϯ��ѯ���
	u8 GetPollIntval()
	{
		return m_byPollIntval;
	}
	void SetPollIntval(u8 byIntval)
	{
		m_byPollIntval = byIntval;
	}

	// ����ģʽ�л�ʱ��������ģʽ ��ʱ��ӵ��ն��б� ������״̬������״̬������Ҫ�ָ�Ϊԭʼֵ
	void  RestoreStatus()
	{
		m_tCurVCMT.SetNull();
// 		m_byLocalMuteType  = 0;
// 		m_byRemoteMuteType = 0; 
		memset(m_achOnLineGroup, 0, sizeof(m_achOnLineGroup));
		m_tMtPolling.SetNull();
		m_byPollIntval = 0;
		m_byPollState  = VCS_POLL_STOP;
	}

	// �����ģʽ�л�,��������ѯ״̬�������״̬
	void RestoreGroupStatus()
	{
		m_tCurVCMT.SetNull();
// 		m_byLocalMuteType  = 0;
// 		m_byRemoteMuteType = 0; 
	}

	// Ĭ��״̬
	void DefaultStatus()
	{
		// Ĭ��Ϊ��������ģʽ
		m_byVCMode = VCS_SINGLE_MODE;
		m_byLocalMuteType  = 0;
		m_byRemoteMuteType = 0; 
		memset(m_atNewAddMt, 0, sizeof(m_atNewAddMt));
		RestoreStatus();
	}

	void Print()
	{
		OspPrintf(TRUE, FALSE, "m_byVCMode:%d\n", m_byVCMode);
		OspPrintf(TRUE, FALSE, "m_byLocalMuteType:%d\n", m_byLocalMuteType);
		OspPrintf(TRUE, FALSE, "m_byRemoteMuteType:%d\n", m_byRemoteMuteType);
		OspPrintf(TRUE, FALSE, "m_tCurVCMT:mcuid��%d mtid��%d\n", m_tCurVCMT.GetMcuId(), m_tCurVCMT.GetMtId());
		OspPrintf(TRUE, FALSE, "m_tMtPolling:mcuid-%d mtid-%d\n", m_tMtPolling.GetMcuId(), m_tMtPolling.GetMtId());
		OspPrintf(TRUE, FALSE, "m_byPollIntval:%d\n", m_byPollIntval);
		OspPrintf(TRUE, FALSE, "m_byPollState:%d\n", m_byPollState);
		OspPrintf(TRUE, FALSE,  "m_atNewAddMt:\n");
		for (u8 byIdx = 0, byPrintIdx = 0; byIdx < VCS_MAXNEWADDMT_NUM; byIdx++)
		{ 
			if (!m_atNewAddMt[byIdx].IsNull())
			{
				OspPrintf(TRUE, FALSE, "%d)mtid(%d)\n", byPrintIdx, m_atNewAddMt[byIdx].GetMtId());
				byPrintIdx++;
			}
		}
	}

protected:
	u8  m_byVCMode;         // VCS���鵱ǰ�����ĵ���ģʽ(VCS_SINGLE_MODE,VCS_MULTW_MODE,VCS_MULVMP_MODE) 
	TMt m_tCurVCMT;         // VCS��ǰ���ڵ��ȵ��ն�
	u8  m_byLocalMuteType;  // ���ؾ���������
	u8  m_byRemoteMuteType; // Զ�˾���������

	TMt m_atNewAddMt[VCS_MAXNEWADDMT_NUM]; // VCS��ʱ�����ն��б�
	s8  m_achOnLineGroup[VCS_MAXGROUPCALL_NUM][MAX_VCSGROUPNAMELEN]; // VCS��ǰ���������

	TMt m_tMtPolling;    // ��ǰ���ڽ�����ϯ��ѯ���ն�
	u8  m_byPollIntval;  // ��ѯ���(s)
	u8  m_byPollState;   // ��ѯ״̬

}
PACKED
;


// ��HDUͨ�������Ϣ
struct THduModChnlInfo
{
public:
	THduModChnlInfo()
	{
		SetNull();
	}

	void SetNull()
	{
		m_byHduId = 0;
		m_byHduChnlIdx = MAXNUM_HDU_CHANNEL;
		m_byHduChnlMember = MAXNUM_CONF_MT + 1;
		m_byMemberType = TW_MEMBERTYPE_NULL;
	}

	void SetHduId(u8 byHduId)  { m_byHduId = byHduId; }
	u8   GetHduID()            { return m_byHduId; }

	void SetHduChnlIdx(u8 byHduChnlIdx)  { m_byHduChnlIdx = byHduChnlIdx; }
	u8   GetHduChnlIdx()                 { return m_byHduChnlIdx; }

	void SetHduChnlMember(u8 byHduChnlMember)  { m_byHduChnlMember = byHduChnlMember; }
	u8   GetHduChnlMember()                    { return m_byHduChnlMember; }

	void SetMemberType(u8 byMemberType)  { m_byMemberType = byMemberType; }
	u8   GetMemberType()                 { return m_byMemberType; }

private:
	u8    m_byHduId;             //ͨ�������豸ID
	u8    m_byHduChnlIdx;        //��Ӧ�豸��ͨ����
    u8    m_byHduChnlMember;     //��ͨ����Ա����
    u8    m_byMemberType;        //��ͨ����Ա��������,TW_MEMBERTYPE_MCSSPEC,TW_MEMBERTYPE_SPEAKER...
}
PACKED
;

#endif  /* __VCSSTRUCT_H_ */


