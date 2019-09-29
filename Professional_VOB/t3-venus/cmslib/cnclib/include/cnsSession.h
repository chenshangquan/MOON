// cnsSession.h: interface for the CCnsSession class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNSSESSION_H__31AEC8FF_0148_4F53_91EB_A546B7C4AB49__INCLUDED_)
#define AFX_CNSSESSION_H__31AEC8FF_0148_4F53_91EB_A546B7C4AB49__INCLUDED_

#include "cnsSessionCtrlIF.h"
#include "cncmsgdriver.h"
#include "usermanage.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCnsSession : public CCnsSessionCtrlIF, 
					public CCncMsgDriver
{
public:
	CCnsSession();
	~CCnsSession();
   

    /*��    ��  �������������Ϣ 
	��    ��  dwType����Ϣ���ͣ���TYPE_CMESSAGE��ֱ��ʹ��osp��post�ӿڷ��ͣ�TYPE_TPMSG��ʹ��CKdvMsg��post�ӿڷ��ͣ�
	�� �� ֵ  �ɹ�����0��ʧ�ܷ��ش����� 
	˵    ��  Ϊ����ͳһ�����Ƿ��������������Ϣ��������������Ҫ�������ͨ��ʱ����ʹ�øýӿ�*/ 
	u16 PostMsg( u32 dwType  = TYPE_CMESSAGE );

    /*��    ��  ��ʼ��lib�⻷��
	��    ��  wAppID:  ����ʹ�õĵ�appID
              dwDesIID: Ŀ��appID
	�� �� ֵ   
	˵    ��   ʹ�������ӿ�֮ǰ������øýӿ�*/ 
	virtual void InitEnv( u16 wAppID, u32 dwDesIID = MAKEIID(AID_CN_UE, 1) );

   
	//��ȡ�ӿ� 
	virtual u16 CncGetInterface(CCncAddrbookIF **ppCtrl);
	virtual u16 CncGetInterface(CCncConfigIF **ppCtrl);   
	virtual u16 CncGetInterface(CCncConfCtrlIF **ppCtrl);
	virtual u16 CncGetInterface(CUmcConfCtrlIF **ppCtrl); 
	virtual u16 CncGetInterface(CCncUserCtrlIF **ppCtrl);
	virtual u16 CncGetInterface(CCncSipInfoCtrlIF **ppCtrl);
 	virtual u16 CncGetInterface(CCncSysCtrlIF **ppCtrl);
 	virtual u16 CncGetInterface(CCncPortDiagCtrlIF **ppCtrl);
 	virtual u16 CncGetInterface(CCncCenterCtrlIF **ppCtrl);
	virtual u16 CncGetInterface(CCncNetMngCtrlIF **ppCtrl);

	virtual void SetUseAddrbook( BOOL bUse ){ m_bUseAdddr = bUse; }

	virtual u16 ConnectCns(u32 dwIP, u32 dwPort, const CString &strUser,
        const CString &strPwd, BOOL32 bConnect = TRUE);
    virtual u16 DisconnectCns();
	virtual BOOL IsConnectedCns();

	virtual u16 LoginCnsIns( u8 byIns );

	virtual const TTPCnList& GetConnectCnsList() const;

	//��ȡ���ӵ�INST
	u8 GetInst(){ return m_uInst; }

	u32 GetLoginIp(){ return m_dwCnsIp; }
    u32 GetLocalHostIP(){ return m_dwLocalIP; }

	virtual u16 DisConnectTpad(); //577

    TTPadSubInfo GetTPadSubInfo(){ return m_tTPadSubInfo; }

    virtual u16 ConnectTPad( TTPadSubInfo tSubInfo );

    virtual u16 SetTpadSysName( string strSysName );//dyy 2013��8��29��
	
protected:
	// ��ʼ��OSP 
	u16 InitializeOsp();
    // ������Ϣӳ��� 
	void BuildEventsMap(); 	

	virtual void DispEvent(const CMessage &cMsg);
	virtual void OnTimeOut(u16 wEvent);

	//��Ϣ����
	void OnLinkBreak(const CMessage& cMsg);
	void OnCnsLoginRsp(const CMessage& cMsg);
	void OnCnsListNty(const CMessage& cMsg);
	void OnLoginCnsInsRsp(const CMessage& cMsg);
	void OnCnsOnlineNty(const CMessage& cMsg);
	void OnCnsOfflineNty(const CMessage& cMsg);
	void OnLoginByOtherNotify(const CMessage& cMsg);

    //�пش�����Ϣ
    void OnCentreSleepNty(const CMessage& cMsg);
    //TPad��¼�û���Ϣ
    void OnTPadLoginUserNotify(const CMessage& cMsg);
    //TPad Home����Ӧ֪ͨ
    void OnTPadHomeKeyNotify(const CMessage& cMsg);

private:
	BOOL32 m_bInitOsp;
	u32    m_dwLocalIP;	  //����ip
	u32	   m_dwCnsIp;	  //���ӵ�CNS��IP
     
	// ����������ӿ���
	CCncAddrbookIF *m_pAddrBookIF;
	CCncConfigIF   *m_pConfigIF;
	CCncConfCtrlIF *m_pConfCtrlIF;
    CUmcConfCtrlIF *m_pUmcConfCtrlIF;
	CCncUserCtrlIF *m_pUserCtrlIF;
	CCncSipInfoCtrlIF *m_pSipInfoCtrlIF;
	CCncPortDiagCtrlIF	*m_pPortDiagIF;
	CCncSysCtrlIF       *m_pSysCtrlIF;
	CCncCenterCtrlIF    *m_pCenterCtrlIF;
	CCncNetMngCtrlIF    *m_pNetMngCtrlIF;

	CLoginRequest   m_cUser; //����ʱ��¼���û�	
	TTPCnList       m_tCnList;
	u8              m_uInst;
	BOOL32          m_bUseAdddr;//�Ƿ�ʹ�õ�ַ��,Ĭ��ʹ�� 2012.12.12 yjj
	TTPadSubInfo    m_tTPadSubInfo;//��¼��½Tpadʱ��½��Ϣ,������½IP���˿ڼ���½����

public:
    static CCnsSession *s_pCnsSession;//ָ���Լ���ָ�룬����timer

};

#endif // !defined(AFX_CNSSESSION_H__31AEC8FF_0148_4F53_91EB_A546B7C4AB49__INCLUDED_)
