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
   

    /*功    能  向服务器发送消息 
	参    数  dwType：消息类型，（TYPE_CMESSAGE：直接使用osp的post接口发送，TYPE_TPMSG：使用CKdvMsg的post接口发送）
	返 回 值  成功返回0，失败返回错误码 
	说    明  为便于统一控制是否向服务器发送消息，其它功能类需要与服务器通信时，均使用该接口*/ 
	u16 PostMsg( u32 dwType  = TYPE_CMESSAGE );

    /*功    能  初始化lib库环境
	参    数  wAppID:  自身使用的的appID
              dwDesIID: 目的appID
	返 回 值   
	说    明   使用其他接口之前必须调用该接口*/ 
	virtual void InitEnv( u16 wAppID, u32 dwDesIID = MAKEIID(AID_MOON_UE, 1) );

   
	//获取接口 
	virtual u16 MoonGetInterface(CCamConfigIF **ppCtrl); 
	virtual u16 MoonGetInterface(CSysConfigIF **ppCtrl);

	virtual void SetUseAddrbook( BOOL bUse ){ m_bUseAdddr = bUse; }

	virtual u16 ConnectMoon(u32 dwIP, u32 dwPort, BOOL32 bConnect = TRUE);
    virtual u16 DisconnectMoon();
	virtual BOOL IsConnectedMoon();

	virtual u16 LoginMoonIns( u8 byIns );

	//获取连接的INST
	u8 GetInst(){ return m_uInst; }

	u32 GetLoginIp(){ return m_dwMoonIp; }
    u32 GetLocalHostIP(){ return m_dwLocalIP; }
	
protected:
	// 初始化OSP 
	u16 InitializeOsp();
    // 构建消息映射表 
	void BuildEventsMap(); 	

	virtual void DispEvent(const CMessage &cMsg);
	virtual void OnTimeOut(u16 wEvent);

	//消息处理
	void OnLinkBreak(const CMessage& cMsg);
	void OnMoonLoginRsp(const CMessage& cMsg);
	void OnLoginCnsInsRsp(const CMessage& cMsg);
	void OnLoginByOtherNotify(const CMessage& cMsg);

private:
	BOOL32 m_bInitOsp;
	u32    m_dwLocalIP;	  //本地ip
	u32	   m_dwMoonIp;	  //连接的MOON90的IP(本地记录防止重复登录)
     
	// 各个功能类接口类
	CCamConfigIF   *m_pCamConfigIF;
	CSysConfigIF   *m_pSysConfigIF;

	CLoginRequest   m_cUser; //连接时登录的用户	
	u8              m_uInst;
	BOOL32          m_bUseAdddr;//是否使用地址簿,默认使用 2012.12.12 yjj

public:
    static CMoonSession *s_pMoonSession;//指向自己的指针，调用timer

};

#endif // !defined(AFX_CNSSESSION_H__31AEC8FF_0148_4F53_91EB_A546B7C4AB49__INCLUDED_)
