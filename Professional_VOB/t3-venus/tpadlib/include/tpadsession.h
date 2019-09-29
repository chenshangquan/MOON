// tpadsession.h: interface for the CTPadSession class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TPADSESSION_H__C5B58BB4_5F50_4D9C_9277_F5E9847D62BA__INCLUDED_)
#define AFX_TPADSESSION_H__C5B58BB4_5F50_4D9C_9277_F5E9847D62BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tpadsessionif.h"
#include "tpadmsgdriver.h"
#include "msgtransdriver.h"
#include "usermanage.h"

class CTPadSession : public CTPadSessionIF,
                     public CTPadMsgDriver
{
public:
	CTPadSession();
	virtual ~CTPadSession();

    /*功  能  初始化lib库环境
	参    数  dwAppID： 需要的appID
	返 回 值   
	说    明  使用其他接口之前必须调用该接口*/ 
	virtual void InitEnv( u32 dwAppID );

    /*===========================================================================
      函 数 名： ConnectCns
      功    能： 连接Cns
      算法实现： 
      全局变量： 
      参    数： u32 dwIP    要连接的终端IP 本机序
                 u32 dwPort  连接端口
                 const CString &strUser   连接的用户名
                 const CString &strPwd    用户密码
                 achVersion  tpad版本号
      返 回 值： u16 
    ===========================================================================*/
    virtual u16 ConnectCns(u32 dwIP, u32 dwPort, const CString &strUser,
        const CString &strPwd, s8* achVersion, BOOL32 bConnect = TRUE);

    virtual u16 DisconnectCns();
	virtual BOOL IsConnectedCns();
	 /** 功能  获取本地ip
	 *  @param[in] 
	 *  @return  本地ip 
	 *  @remarks 
	 */
    u32 GetLocalHostIP(){ return m_dwLocalIP; }

	u32 GetLoginIp(){ return m_dwCnsIp; }
	/** 
	* 功能  开启/停止双流码流
	* @return  BOOL  TRUE:开启， FALSE:停止
	* @remarks 
	*/
    virtual u16 StartDualCodeStream( const TTPCnMediaTransPort  &tVideoTransAddr , const TTPCnMediaTransPort  &tAudioTransAddr ) const;
   
    virtual u16 StopDualCodeStream() const  ;

	/** 
	* 功能  请求关键帧
	* @return  BOOL  TRUE:不受关键帧保护约束，强制发送关键帧， FALSE:受关键帧包含约束 2012.8.16 by yjj
	* @remarks 
	*/
    virtual u16 ReqKeyFrame( BOOL32 bForce ) const ;

	virtual TTPCnMediaTransPort GetVedioTransAddr() const { return m_tVideoTranAddr ;}

    virtual TTPCnMediaTransPort GetAudioTransAddr() const { return m_tAudioTranAddr ;}

	    /**
	* 功能:  获取本地cns会议状态
	* @param [out]tConfInfo  本级cns参加的会议信息
	* @return 成功返回TRUE,失败返回FALSE
	* @remarks 
	*/
    virtual TTPCnsConfStatus GetCnsConfStatus() const; 

    void NotifyLoginUser();
	
	//文件共享
	virtual u16 FileDualCmd( BOOL bStart );
	virtual u16 FileDualRcvAddrCmd( EmTPAddDualRcvResult emAddDualRcvRes, TTPCnMediaTransPort &tVideoTransAddr, u16 nVideoNode );
	virtual TTPMtVideoEncodeParameter& GetFileDualEncParam();
	virtual TEncryptKey& GetFileDualkey();
	virtual u8 GetFileDualPayload();
	virtual TTPCnMediaTransPort& GetFileDualTransPort();

    /**
	* 功能:  TPad响应Home键通知
	* @return 成功返回TRUE,失败返回FALSE
	* @remarks 
	*/
    void TPadHomeKeyNty();

protected:
    // 初始化OSP 
	u16 InitializeOsp();
    // 构建消息映射表 
    void BuildEventsMap(); 	
    
    virtual void DispEvent(const CMessage &cMsg);
	virtual void OnTimeOut(u16 wEvent);

    //消息处理
    void OnLinkBreak(const CMessage& cMsg);
	void OnCnsLoginRsp(const CMessage& cMsg);
    void OnTpadUpdateCmd(const CMessage& cMsg);
    void OnLoginByOtherNotify(const CMessage& cMsg);
    void OnCentreSleepNty(const CMessage& cMsg);
    void OnCncSetSystemName( const CMessage& cMsg );
	void DisConnectTpad( const CMessage& cMsg );
	void OnRecvDualNty( const CMessage &cMsg );

	void OnFileDualRcvAddrInd( const CMessage& cMsg );
	void OnFileDualRcvInd( const CMessage& cMsg );
	void OnFileDualKeyFrame( const CMessage& cMsg );
	void OnFileDualInd( const CMessage& cMsg );
	void OnFileDualEmResInd(const CMessage& cMsg);
	void OnFileDualEncParamInd(const CMessage& cMsg);
	void OnFileDualKeyInd( const CMessage& cMsg );
	void OnFileDualPayloadInd( const CMessage& cMsg );
	void OnFileDualEmCodeInd( const CMessage& cMsg );

	void OnStartDualCdStrmRsp( const CMessage &cMsg );
    void OnStopDualCdStrmRsp( const CMessage &cMsg );

	void OnConfStateNty( const CMessage &cMsg );

    //判断是否可进行链接(cnc、中控均以连上Tpad)
    BOOL IsReadyLogin( vector<TNodeInfo>&vctNodeList );

private:
	CTPadSession *m_pTpadSession;
	BOOL32 m_bInitOsp;
    u32	   m_dwCnsIp;	  //连接的CNS的IP
    u32    m_dwLocalIP;   //本地ip
	u16    m_nVideoNode;
	u16    m_nAudioNode;
    BOOL32 m_bRecvDual;
	TTPCnMediaTransPort m_tVideoTranAddr;
    TTPCnMediaTransPort m_tAudioTranAddr;
    CLoginRequest   m_cUser; //连接时登录的用户	
	TTPMtVideoEncodeParameter m_tVideoEncodeParam;
	TEncryptKey m_tEncryptKey;
	u8 m_byPayload;
	TTPCnMediaTransPort m_tVideoTransAddr;
	TTPCnsConfStatus m_tCnsConfStatus;
};

#endif // !defined(AFX_TPADSESSION_H__C5B58BB4_5F50_4D9C_9277_F5E9847D62BA__INCLUDED_)
