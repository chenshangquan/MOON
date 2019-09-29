// msgtransdriver.h: interface for the CMsgTransDriver class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGTRANSDRIVER_H__1672F32B_CC5A_4136_954A_BE5A7821024C__INCLUDED_)
#define AFX_MSGTRANSDRIVER_H__1672F32B_CC5A_4136_954A_BE5A7821024C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMsgTransDriver
{
public:
	virtual ~CMsgTransDriver();

    //获取接口指针
	static CMsgTransDriver* GetMsgDriverPtr();

    void RegTransNode( TNodeInfo tNodeInfo );

    void DelTransNode( u32 dwNodeId );

    /** 
	* 功能  分发消息
    * @param [in] pMsg    消息
	* @return 
	* @remarks 分发消息给所有连接的节点
	*/
    void DispatchMsg( CMessage *const pMsg );

    /** 
	* 功能  转发消息给单个节点
	* @param [in] emType  节点类型
    * @param [in] pMsg    消息
	* @return 
	* @remarks 
	*/
    void TransMsg( emTPadSubType emType, CMessage *const pMsg );

    /** 
	* 功能  转发地址簿消息
    * @param [in] pMsg    消息
	* @return 
	* @remarks
	*/
    void TransAddrMsg( CMessage *const pMsg );

    //响应收到的Osp消息
    void OnOspMessageComing();

    /** 
    * 功能  系统退出时清空OSP消息队列
    * @param [in] pMsg    消息
	* @return 
	* @remarks
	*/
    void ClearOspMsg();

    //判断是否中控、cnc都已注册节点
    BOOL IsAlreadyReg( vector<TNodeInfo>&vctNodeList );
    
protected:
    CMsgTransDriver();

private:
    static CMsgTransDriver* m_pTransDriver;

    vector<TNodeInfo> m_vctNodeList;
};

#define MsgTransDriver  CMsgTransDriver::GetMsgDriverPtr()

#endif // !defined(AFX_MSGTRANSDRIVER_H__1672F32B_CC5A_4136_954A_BE5A7821024C__INCLUDED_)
