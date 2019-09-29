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

    /*��  ��  ��ʼ��lib�⻷��
	��    ��  dwAppID�� ��Ҫ��appID
	�� �� ֵ   
	˵    ��  ʹ�������ӿ�֮ǰ������øýӿ�*/ 
	virtual void InitEnv( u32 dwAppID );

    /*===========================================================================
      �� �� ���� ConnectCns
      ��    �ܣ� ����Cns
      �㷨ʵ�֣� 
      ȫ�ֱ����� 
      ��    ���� u32 dwIP    Ҫ���ӵ��ն�IP ������
                 u32 dwPort  ���Ӷ˿�
                 const CString &strUser   ���ӵ��û���
                 const CString &strPwd    �û�����
                 achVersion  tpad�汾��
      �� �� ֵ�� u16 
    ===========================================================================*/
    virtual u16 ConnectCns(u32 dwIP, u32 dwPort, const CString &strUser,
        const CString &strPwd, s8* achVersion, BOOL32 bConnect = TRUE);

    virtual u16 DisconnectCns();
	virtual BOOL IsConnectedCns();
	 /** ����  ��ȡ����ip
	 *  @param[in] 
	 *  @return  ����ip 
	 *  @remarks 
	 */
    u32 GetLocalHostIP(){ return m_dwLocalIP; }

	u32 GetLoginIp(){ return m_dwCnsIp; }
	/** 
	* ����  ����/ֹͣ˫������
	* @return  BOOL  TRUE:������ FALSE:ֹͣ
	* @remarks 
	*/
    virtual u16 StartDualCodeStream( const TTPCnMediaTransPort  &tVideoTransAddr , const TTPCnMediaTransPort  &tAudioTransAddr ) const;
   
    virtual u16 StopDualCodeStream() const  ;

	/** 
	* ����  ����ؼ�֡
	* @return  BOOL  TRUE:���ܹؼ�֡����Լ����ǿ�Ʒ��͹ؼ�֡�� FALSE:�ܹؼ�֡����Լ�� 2012.8.16 by yjj
	* @remarks 
	*/
    virtual u16 ReqKeyFrame( BOOL32 bForce ) const ;

	virtual TTPCnMediaTransPort GetVedioTransAddr() const { return m_tVideoTranAddr ;}

    virtual TTPCnMediaTransPort GetAudioTransAddr() const { return m_tAudioTranAddr ;}

	    /**
	* ����:  ��ȡ����cns����״̬
	* @param [out]tConfInfo  ����cns�μӵĻ�����Ϣ
	* @return �ɹ�����TRUE,ʧ�ܷ���FALSE
	* @remarks 
	*/
    virtual TTPCnsConfStatus GetCnsConfStatus() const; 

    void NotifyLoginUser();
	
	//�ļ�����
	virtual u16 FileDualCmd( BOOL bStart );
	virtual u16 FileDualRcvAddrCmd( EmTPAddDualRcvResult emAddDualRcvRes, TTPCnMediaTransPort &tVideoTransAddr, u16 nVideoNode );
	virtual TTPMtVideoEncodeParameter& GetFileDualEncParam();
	virtual TEncryptKey& GetFileDualkey();
	virtual u8 GetFileDualPayload();
	virtual TTPCnMediaTransPort& GetFileDualTransPort();

    /**
	* ����:  TPad��ӦHome��֪ͨ
	* @return �ɹ�����TRUE,ʧ�ܷ���FALSE
	* @remarks 
	*/
    void TPadHomeKeyNty();

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

    //�ж��Ƿ�ɽ�������(cnc���пؾ�������Tpad)
    BOOL IsReadyLogin( vector<TNodeInfo>&vctNodeList );

private:
	CTPadSession *m_pTpadSession;
	BOOL32 m_bInitOsp;
    u32	   m_dwCnsIp;	  //���ӵ�CNS��IP
    u32    m_dwLocalIP;   //����ip
	u16    m_nVideoNode;
	u16    m_nAudioNode;
    BOOL32 m_bRecvDual;
	TTPCnMediaTransPort m_tVideoTranAddr;
    TTPCnMediaTransPort m_tAudioTranAddr;
    CLoginRequest   m_cUser; //����ʱ��¼���û�	
	TTPMtVideoEncodeParameter m_tVideoEncodeParam;
	TEncryptKey m_tEncryptKey;
	u8 m_byPayload;
	TTPCnMediaTransPort m_tVideoTransAddr;
	TTPCnsConfStatus m_tCnsConfStatus;
};

#endif // !defined(AFX_TPADSESSION_H__C5B58BB4_5F50_4D9C_9277_F5E9847D62BA__INCLUDED_)
