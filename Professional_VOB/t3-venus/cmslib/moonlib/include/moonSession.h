// cnsSession.h: interface for the CCnsSession class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNSSESSION_H__31AEC8FF_0148_4F53_91EB_A546B7C4AB49__INCLUDED_)
#define AFX_CNSSESSION_H__31AEC8FF_0148_4F53_91EB_A546B7C4AB49__INCLUDED_

#include "moonSessionCtrlIF.h"
#include "moonmsgdriver.h"
#include "usermanage.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMoonSession : public CMoonSessionCtrlIF, 
					public CMoonMsgDriver
{
public:
	CMoonSession();
	~CMoonSession();
   

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
	virtual void InitEnv( u16 wAppID, u32 dwDesIID = MAKEIID(AID_MOON_UE, 1) );

   
	//��ȡ�ӿ� 
	virtual u16 MoonGetInterface(CCamConfigIF **ppCtrl); 
	virtual u16 MoonGetInterface(CSysConfigIF **ppCtrl);

	virtual void SetUseAddrbook( BOOL bUse ){ m_bUseAdddr = bUse; }

	virtual u16 ConnectMoon(u32 dwIP, u32 dwPort, BOOL32 bConnect = TRUE);
    virtual u16 DisconnectMoon();
	virtual BOOL IsConnectedMoon();

	virtual u16 LoginMoonIns( u8 byIns );

	//��ȡ���ӵ�INST
	u8 GetInst(){ return m_uInst; }

	u32 GetLoginIp(){ return m_dwMoonIp; }
    u32 GetLocalHostIP(){ return m_dwLocalIP; }
	
protected:
	// ��ʼ��OSP 
	u16 InitializeOsp();
    // ������Ϣӳ��� 
	void BuildEventsMap(); 	

	virtual void DispEvent(const CMessage &cMsg);
	virtual void OnTimeOut(u16 wEvent);

	//��Ϣ����
	void OnLinkBreak(const CMessage& cMsg);
	void OnMoonLoginRsp(const CMessage& cMsg);
	void OnLoginCnsInsRsp(const CMessage& cMsg);
	void OnLoginByOtherNotify(const CMessage& cMsg);

private:
	BOOL32 m_bInitOsp;
	u32    m_dwLocalIP;	  //����ip
	u32	   m_dwMoonIp;	  //���ӵ�MOON90��IP(���ؼ�¼��ֹ�ظ���¼)
     
	// ����������ӿ���
	CCamConfigIF   *m_pCamConfigIF;
	CSysConfigIF   *m_pSysConfigIF;

	CLoginRequest   m_cUser; //����ʱ��¼���û�	
	u8              m_uInst;
	BOOL32          m_bUseAdddr;//�Ƿ�ʹ�õ�ַ��,Ĭ��ʹ�� 2012.12.12 yjj

public:
    static CMoonSession *s_pMoonSession;//ָ���Լ���ָ�룬����timer

};

#endif // !defined(AFX_CNSSESSION_H__31AEC8FF_0148_4F53_91EB_A546B7C4AB49__INCLUDED_)
