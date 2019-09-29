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

    //��ȡ�ӿ�ָ��
	static CMsgTransDriver* GetMsgDriverPtr();

    void RegTransNode( TNodeInfo tNodeInfo );

    void DelTransNode( u32 dwNodeId );

    /** 
	* ����  �ַ���Ϣ
    * @param [in] pMsg    ��Ϣ
	* @return 
	* @remarks �ַ���Ϣ���������ӵĽڵ�
	*/
    void DispatchMsg( CMessage *const pMsg );

    /** 
	* ����  ת����Ϣ�������ڵ�
	* @param [in] emType  �ڵ�����
    * @param [in] pMsg    ��Ϣ
	* @return 
	* @remarks 
	*/
    void TransMsg( emTPadSubType emType, CMessage *const pMsg );

    /** 
	* ����  ת����ַ����Ϣ
    * @param [in] pMsg    ��Ϣ
	* @return 
	* @remarks
	*/
    void TransAddrMsg( CMessage *const pMsg );

    //��Ӧ�յ���Osp��Ϣ
    void OnOspMessageComing();

    /** 
    * ����  ϵͳ�˳�ʱ���OSP��Ϣ����
    * @param [in] pMsg    ��Ϣ
	* @return 
	* @remarks
	*/
    void ClearOspMsg();

    //�ж��Ƿ��пء�cnc����ע��ڵ�
    BOOL IsAlreadyReg( vector<TNodeInfo>&vctNodeList );
    
protected:
    CMsgTransDriver();

private:
    static CMsgTransDriver* m_pTransDriver;

    vector<TNodeInfo> m_vctNodeList;
};

#define MsgTransDriver  CMsgTransDriver::GetMsgDriverPtr()

#endif // !defined(AFX_MSGTRANSDRIVER_H__1672F32B_CC5A_4136_954A_BE5A7821024C__INCLUDED_)
