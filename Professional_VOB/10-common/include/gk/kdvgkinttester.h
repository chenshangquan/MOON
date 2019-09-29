/////////////////////////////////////////////////////////
// GKTester.h
//
// Interface of CGKTester.
// require header (s):	osp.h	kdvgk.h
/////////////////////////////////////////////////////////

#ifndef __GKTESTER_H
#define __GKTESTER_H

//�ӿڲ�ѯʧ�ܷ���ֵ
#define GKINT_ERROR  (int)-1

//
// class CGKTester
// GK���ɲ�����
//
// @ �÷���
// 		# ����Init()������ʼ��
// 		# ����UnInit()
//		# ������Ӧ�Ĳ��Ժ������в���
//
class CGKTester
{
public:
	CGKTester();
	
public:
	// initialize
	// GKIP : ������
	BOOL Init(DWORD GKIP);
	// uninit
	void UnInit();

public:
    
/*=============================================================================
  �� �� ���� GetBaseCfg
  ��    �ܣ� �õ�GK����������Ϣ 
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� TConfigBaseGKDBData tBaseConfig [in/out] GK��������
  �� �� ֵ�� FALSE : ��ѯʧ�� �� TRUE����ѯ�ɹ�
=============================================================================*/
	BOOL GetBaseCfg( TConfigBaseGKDBData &tBaseConfig );

/*=============================================================================
  �� �� ���� IsUserExist
  ��    �ܣ� ��ѯ����̨�û��Ƿ����  
  ��    ���� const char * User [in] �û���
             BYTE UserLen		 [in] �û�������	
  �� �� ֵ�� GKINT_ERROR: ��ѯʧ��
			 0			: ������
			 1			������
=============================================================================*/
	int IsUserExist(const char * User, BYTE UserLen);
 
/*=============================================================================
  �� �� ���� IsUserLoginged
  ��    �ܣ� ��ѯ�û��Ƿ��¼  
  ��    ���� const char * User [in] �û���
             BYTE UserLen	   [in] �û�������
  �� �� ֵ�� GKINT_ERROR: ��ѯʧ��
			 0			: û�е�¼
			 1			���Ѿ���¼
=============================================================================*/
	int IsUserLoginged(const char * User,BYTE UserLen);

/*=============================================================================
  �� �� ���� IsRegIPRngExist
  ��    �ܣ� ��ѯ��ע��IP��Χ�Ƿ����  
  ��    ���� const TAddrRng & tIPRng [in] IP��Χ
  �� �� ֵ�� GKINT_ERROR: ��ѯʧ��
			  0			: ������
			  1			������
=============================================================================*/
	int IsRegIPRngExist(const TAddrRng & tIPRng);

/*=============================================================================
  �� �� ���� IsForbidIPRngExist
  ��    �ܣ� ��ѯ��ֹIP��Χ�Ƿ����
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� const TAddrRng & tIPRng [in] IP��Χ
  �� �� ֵ�� GKINT_ERROR: ��ѯʧ��
			  0			: ������
			  1			������
=============================================================================*/
	int IsForbidIPRngExist(const TAddrRng & tIPRng);

/*=============================================================================
  �� �� ���� IsBSBExist
  ��    �ܣ� ��ѯ���μ�����Ƿ����  
  ��    ���� const TConfigBandWidthDBData & tCfgBWDBData [in] ���δ�����Ϣ
  �� �� ֵ�� GKINT_ERROR: ��ѯʧ��
			 0			: ������
			 1			������
=============================================================================*/
	int IsBSBExist(const TConfigBandWidthDBData & tCfgBWDBData);

/*=============================================================================
  �� �� ���� IsAllowedEPInDB
  ��    �ܣ� ��ѯ�����H.323ʵ���Ƿ���DB��
  ��    ���� const TAliasAuthKey & tAliasArray [in] ʵ����֤��Ϣ
  �� �� ֵ�� GKINT_ERROR: ��ѯʧ��
			  0			: ������
			  1			������
=============================================================================*/
	int IsAllowedEPInDB(const TAliasAuthKey & tAliasArray);

/*=============================================================================
  �� �� ���� IsForbidEPInDB
  ��    �ܣ� ��ѯ��ֹ��H.323ʵ���Ƿ���DB��
  ��    ���� const TAliasAuthKey & tAliasArray [in] ʵ����֤��Ϣ
  �� �� ֵ�� GKINT_ERROR: ��ѯʧ��
			  0			: ������
			  1			������
=============================================================================*/
	int IsForbidEPInDB(const TAliasAuthKey & tAliasArray);

/*=============================================================================
  �� �� ���� GetOnlineEndPointCount
  ��    �ܣ� ��ѯ����ʵ���б��е�ʵ������   
  ��    ���� DWORD dwCount [in/out]  ����ʵ�����
  �� �� ֵ�� FALSE : ��ѯʧ�� �� TRUE����ѯ�ɹ�
=============================================================================*/
	BOOL GetOnlineEndPointCount(DWORD &dwCount);

/*=============================================================================
  �� �� ���� IsEndpointRegistered
  ��    �ܣ� ��ѯH.323ʵ���Ƿ���ע��, ���Ƿ��ʵ����GK������ʵ���б���
  ��    ���� const TAliasAddr & tAlias [in] ʵ�����
  �� �� ֵ�� GKINT_ERROR: ��ѯʧ��
			  0			: ������
			  1			������
=============================================================================*/
	int IsEndpointRegistered(const TAliasAddr & tAlias);

/*=============================================================================
  �� �� ���� IsCallExist
  ��    �ܣ� ��ѯ�����Ƿ����
  ��    ���� const u32 dwTimerId   [in] Ҫ��ѯ�ĺ���TimerId
  �� �� ֵ�� GKINT_ERROR: ��ѯʧ��
			  0			: ������
			  1			������
=============================================================================*/
	int IsCallExist( const u32 dwTimerId );
    
/*=============================================================================
  �� �� ���� IsZoneExist
  ��    �ܣ� ǰ׺(����)�Ƿ����   
  ��    ���� const char *pZone [in] ǰ׺
             BYTE byLen		 [in] ����
  �� �� ֵ�� GKINT_ERROR: ��ѯʧ��
			 0			: ������
			 1			������
=============================================================================*/
	int IsPrefixExist(const char *pPrefix, BYTE byLen);

/*=============================================================================
  �� �� ���� GetNeighborGKInfo
  ��    �ܣ� ��ѯ�ھ�GK��Ϣ
  ��    ���� TNeighborGKInfo &tNeighborGK   [in] �ھ�GK��Ϣ
  �� �� ֵ�� FALSE : ��ѯʧ�� �� TRUE����ѯ�ɹ�
=============================================================================*/
	BOOL GetNeighborGKInfo(TNeighborGKInfo &tNeighborGK);

/*=============================================================================
  �� �� ���� GetEpAliasByIP
  ��    �ܣ� ��ʵ�����͡�ras��ַ��call��ַ���ұ����б� 
  ��    ���� cmEndpointType &epType           [in]      ʵ������
             TNETADDR &cRasAddr               [in]      ras��ַ
             TNETADDR &cCallAddr              [in]      call��ַ
             TAliasAddr *pByAliasBuf          [in/out]  ����
             u32 &dwAliasNum                  [in]      ��������
             
  �� �� ֵ�� FALSE : ��ѯʧ�� �� TRUE����ѯ�ɹ�  
=============================================================================*/
    BOOL GetEpAliasByIP(cmEndpointType &epType, TNETADDR &cRasAddr, TNETADDR &cCallAddr,
                        TAliasAddr *pByAliasBuf, u32 &dwAliasNum);
	
/*=============================================================================
  �� �� ���� ClearAllConfig
  ��    �ܣ� ������п���̨������Ϣ���û�������adminĬ���û���
  ��    ���� ��
  �� �� ֵ�� FALSE : ʧ�� �� TRUE���ɹ�
=============================================================================*/
	BOOL ClearAllConfig();

/**/
/*=============================================================================
  �� �� ���� GetLoginedUserCount
  ��    �ܣ� ��ѯ��ǰ�ѵ�¼�Ŀ���̨�û�����(������)
  ��    ���� DWORD dwCount [in/out]  �û�����
  �� �� ֵ�� FALSE : ��ѯʧ�� �� TRUE����ѯ�ɹ�
=============================================================================*/
	BOOL GetLoginedUserCount(DWORD &dwCount);

/*=============================================================================
  �� �� ���� RebootGK
  ��    �ܣ� �Ƿ������ɹ�
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� 
  �� �� ֵ�� FALSE : ����ʧ�� �� TRUE�������ɹ�			 
=============================================================================*/
	BOOL RebootGK();

private:
	BOOL ConnectToCtrlSessioner();
	BOOL DisconnectFromCtrlSessioner();
	BOOL SendMsg( WORD dwMsgId, const void *pContent, u16 wContentLen, 
		          void *pAckBuf, u16 &wAckBufLen, BOOL bSendToCtrl = TRUE );

private:
	DWORD 	m_GKIP;     // GK ip��ַ
	DWORD 	m_GKNodeId; // �ڵ�id
};

#endif // __GKTESTER_H
