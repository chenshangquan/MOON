// tpadmsgdriver.h: interface for the CTpadMsgDriver class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TPADMSGDRIVER_H__DA72E4C3_F117_459E_9B19_9BDEF898E374__INCLUDED_)
#define AFX_TPADMSGDRIVER_H__DA72E4C3_F117_459E_9B19_9BDEF898E374__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tpmsg.h"  
#include "commandqueue.h" 
#include "eventoutcnsallmsg.h"
#include "tpstruct.h"

#define TYPE_CMESSAGE  0         //一般的CMessage消息
#define TYPE_TPMSG     1         //收发的消息为CTPMSG ,需要进行消息类型的转换

class CTPadMsgDriver  
{
public:
	CTPadMsgDriver();
	virtual ~CTPadMsgDriver();

    //获取接口指针
	static CTPadMsgDriver* GetMsgDriverPtr();

	// 得到发送终端消息的指针
	CTpMsg* GetKdvMsgPtr(BOOL32 bClear = TRUE);

    virtual u16 PostMsg(u32 dwType = TYPE_CMESSAGE);

    // 发送请求型消息, 期待多个响应
    u16 PostCommand(CKdvDispEvent *pDispEvent, u16 *pwWaitEvent, s32 nEventNum = 1, 
        u32 dwType = TYPE_CMESSAGE, u32 dwTimeOut = 1500);
    // 发送请求型消息，期待单个响应
    u16 PostCommand(CKdvDispEvent *pDispEvent, u16 wWaitEvent, u32 dwType = TYPE_CMESSAGE, u32 dwTimeOut = 1500);

    //将消息转发到cns
    u16 TransMsg( const CMessage* pMsg );

    //响应收到的Osp消息
    void OnOspMessageComing( CMessage *const pMsg );

    // 注册一个处理消息的类的指针
    void RegHandler(CKdvDispEvent* const pDispEvnet);
    // 注销一个处理消息的类的指针
    void UnregHandler(CKdvDispEvent* const pDispEvnet);
    // 清空所有注册的类的指针
    void ClearHandler();
    // 清空所有命令消息队列
    void ClearAllCommand();

    //设置当前连接节点
    void SetNodeId(u32 dwId) { m_dwNodeId = dwId; }
    u32 GetNodeId(){ return m_dwNodeId;}
    
    // 设置TPad使用的APPID号
    void SetAppId( u16 wAppID ){ m_wAppID = wAppID; } 
    u16  GetAppId(){ return m_wAppID; }

protected:
    // 是否正在处理命令
    BOOL IsHandleCmd() const { return !m_vWaitingEvents.empty(); }
    // 清空等待的消息
    void ClearWaiting();
    // 缺省超时消息处理方法
    virtual void OnTimeOut(u16 wEvent){ return; }
    // 当一条命令发送完成后，发送下一条命令
    void PostNextCommand();

    void MappingEventName();

    // 响应WM_TIMER消息
    void OnTimer(WPARAM wParam, LPARAM lParam);
    
public:
    static CTPadMsgDriver *s_pMsgDriver;

protected:
    CCommandQueue  m_cCommandQueue;     //命令缓冲队列
    
    CTpMsg         m_cTpMsg;            //用于发送TP消息的消息结构
	CMessage	   m_cMsg;			    //用于发送其他消息的消息结构

private:
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    HWND            m_hWndOsp;           // 内嵌接收消息的窗口
    WNDPROC         m_wndprocOld;       // 系统窗口过程
    vector<CKdvDispEvent*> m_vpDispEvent;// 消息分发表
    vector<u16>     m_vWaitingEvents;    // 正在等待应答的消息
    CKdvDispEvent  *m_pCurDispEvent;     // 正在处理的消息对应的响应类的指针
    u16             m_wCurSendEvent;     // 当前发送出去的消息
    s32             m_nTimer;

    u32  m_dwNodeId;        // 当前连接的节点
    u16  m_wAppID;			// 连接的APPID号
};

#endif // !defined(AFX_TPADMSGDRIVER_H__DA72E4C3_F117_459E_9B19_9BDEF898E374__INCLUDED_)
