/*=======================================================================
模块名      : MOON90三眼摄像机
文件名      : MoonMsgDriver.cpp
相关文件    : 
文件实现功能: 消息驱动器
作者        : 
版本        : V3.0  Copyright(C) 1997-2003 KDC, All rights reserved.
-------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2014/12/2   1.0         吴蒨蒨        创建
=======================================================================*/
#include "StdAfx.h"
#include "moonmsgdriver.h"
#include "moonmsgrecver.h"
#include "moonlib.h"

////////////////////////////////////////////////////////////////////////////
// CMsgDriver

CMoonMsgDriver* CMoonMsgDriver::s_pMsgDriver = NULL;

CMoonMsgDriver::CMoonMsgDriver()
{
    // 构造事件名称表
    MappingEventName();
    // 创建消息接收窗口
    m_hWndOsp = ::CreateWindowEx(0, _T("Static"), _T("MoonMsgDriver"), WS_DISABLED,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, 0, 0);

	if ( m_hWndOsp != NULL )
	{
		m_wndprocOld = reinterpret_cast<WNDPROC>(GetWindowLong(m_hWndOsp, GWL_WNDPROC));
		SetWindowLong(m_hWndOsp, GWL_WNDPROC, reinterpret_cast<s32>(WndProc));
	} 
	else
	{
		m_wndprocOld = NULL;
	}
    m_nTimer = 0;
    m_pCurDispEvent = NULL;
    m_wCurSendEvent = 0;
    s_pMsgDriver = this;
    m_byTransferStatus = FREE;
    m_pbyFile = NULL;
    m_dwFileLength = 0;         // 文件长度
    m_dwFileFragIndex = 0;      // 文件块序号
    m_dwFileCurPos = 0;
	m_wInsID = 0;
    m_wAppID = 0;
    m_dwDesIID = MAKEIID(AID_MOON_UE, 1);
}

CMoonMsgDriver::~CMoonMsgDriver()
{
    if (m_pbyFile != NULL)
    {
        free(m_pbyFile);
        m_pbyFile = NULL;
    }
    ::KillTimer(m_hWndOsp, m_nTimer);
    // 关闭消息接收窗口

	::DestroyWindow( m_hWndOsp );
	m_hWndOsp = NULL;
	s_pMsgDriver = NULL;
}


/*=======================================================================
函 数 名:   GetMtMsgPtr
功    能:   得到发送消息指针(发送TKdvMsg)
参    数:   BOOL bClear = TRUE         [in]返回消息指针时是否清空消息体
返 回 值:   发送消息的消息指针
相关消息:
-------------------------------------------------------------------------
修改纪录:
日      期  版本  修改人  修改内容
2004/09/30  4.0   liuruifei  创建
=======================================================================*/
CTpMsg* CMoonMsgDriver::GetKdvMsgPtr(BOOL32 bClear)
{
    if (bClear) 
    {
        ZeroMemory(&m_cTpMsg, sizeof(CTpMsg));
    }

    return &m_cTpMsg;
}
/*=======================================================================
函 数 名:   GetCMsgPtr
功    能:   得到发送消息指针(发送TMtMsg)
参    数:   BOOL bClear = TRUE         [in]返回消息指针时是否清空消息体
返 回 值:   发送消息的消息指针
相关消息:
-------------------------------------------------------------------------
修改纪录:
日      期  版本  修改人  修改内容
2004/09/30  4.0   liuruifei  修改
=======================================================================*/
CMessage* CMoonMsgDriver::GetCMsgPtr(BOOL32 bClear /* = TRUE */)
{
	if (bClear)
	{
		ZeroMemory(&m_cMsg, sizeof(CMessage));
	}

	return &m_cMsg;
}

/*=======================================================================
函 数 名:   PostMsg
功    能:   发送命令型消息，不需要终端有回应。调用接口前要要通过GetPostMsgPtr
            来设置消息体
参    数:   u32 dwType = TYPE_CMESSAGE   [in]消息类型TYPE_CMESSAGE或TYPE_MTMSG
返 回 值:
相关消息:
-------------------------------------------------------------------------
修改纪录:
日      期  版本  修改人  修改内容
2004/08/25  3.5   李洪强  创建
=======================================================================*/
u16 CMoonMsgDriver::PostMsg(u32 dwType)
{  
    u32 dwDesIID = GetDesIID();//MAKEIID(AID_CN_UE, 1/*m_wInsID*/);	 // 目的：MOON
	u32 dwSrcIID = MAKEIID(GetAppID());	         // 源  ：MOON控制台
	
	u16 wRet = NO_ERROR;
	u16 wEvent = 0;
	if (TYPE_TPMSG == dwType) 
	{  
		//发送CMtMsg消息体
		{
			wRet = m_cTpMsg.Post(dwDesIID, g_MoonApp.GetNodeId(), dwSrcIID);
		}
		wEvent = m_cTpMsg.GetEvent();
    }
	else
	{
		//发送Osp CMessage消息
		if(m_cMsg.dstid != INVALID_NODE)
		{
			dwDesIID = m_cMsg.dstid;
		}
		if(m_cMsg.srcid != INVALID_NODE)
		{
			dwSrcIID = m_cMsg.srcid;
		}

		wRet = OspPost(dwDesIID, m_cMsg.event, m_cMsg.content, m_cMsg.length,
        g_MoonApp.GetNodeId(), dwSrcIID);

		wEvent = m_cMsg.event;
	}
	//打印输出   
// 	if(wRet == NO_ERROR)
// 	{  
// 		if( IS_PRINT_OUT_MSG )
// 		{
// 			CString strEvent = CPrintCtrl::GetPrintCtrl()->GetEventDescribe(wEvent);
// 	        PrtMsg( "[CncLib]: 发送消息:%s(%u).\n", strEvent,wEvent);
// 		}
// 	}
// 	else
// 	{   
// 		CString strEvent = CPrintCtrl::GetPrintCtrl()->GetEventDescribe(wEvent);
// 	    PrtMsg( "[CncLib]: 发送消息:%s(%u)失败,错误码：%d\n", strEvent, wEvent, wRet ); 
// 	}
	
    return wRet;
}



/*=======================================================================
函 数 名:   PostCommand
功    能:   发送请求型消息，一般会需要终端有回应，如无回应则报超时。调用接口前
要通过GetPostMsgPtr来设置消息体
参    数:   CDispEvent *pDispEvent     [in]响应消息的处理指针
u16 *pwWaitEvent           [in]期待响应的消息数组
s32 nEventNum = 1          [in]期待响应的消息数量
u32 dwTimeOut = 1000       [in]期待响应的消息超时时间
返 回 值:
相关消息:
-------------------------------------------------------------------------
修改纪录:
日      期  版本  修改人  修改内容
2004/08/25  3.5   李洪强  创建
=======================================================================*/
u16 CMoonMsgDriver::PostCommand(CKdvDispEvent *pDispEvent, u16 *pwWaitEvent,
                            s32 nEventNum, u32 dwType, u32 dwTimeOut)
{
    // 检测是否有前一个命令正在执行中
    if(IsHandleCmd())
    {
        m_cCommandQueue.PushCommand(m_cMsg, m_cTpMsg, pDispEvent, pwWaitEvent,
                                    nEventNum, dwType, dwTimeOut);

        return ERR_CNC_WAIT_FOR_SEND_CMD;
    }
    // 保存当前命令参数
    if(TYPE_CMESSAGE == dwType)
    {
        m_wCurSendEvent = m_cMsg.event;
    }
    else
    {
        m_wCurSendEvent = m_cTpMsg.GetEvent();
    }
    m_pCurDispEvent = pDispEvent;
    
    for(s32 nIndex = 0; nIndex < nEventNum; nIndex++)
    {
        m_vWaitingEvents.push_back(pwWaitEvent[nIndex]);
    }
    // 超时计时器
    m_nTimer = SetTimer(m_hWndOsp, 1, dwTimeOut, NULL);
    // 发送
    u16 wRet = PostMsg(dwType);
    if(wRet != NO_ERROR)
    {
        // 发送失败
        ::KillTimer(m_hWndOsp, m_nTimer);
        ClearWaiting();
        PostNextCommand();
    }
    return wRet;
}

/*=======================================================================
函 数 名:   PostCommand
功    能:   发送请求型消息，一般会需要终端有回应，如无回应则报超时。调用接口前
            要要通过GetPostMsgPtr来设置消息体（单个等待消息）
参    数:   CDispEvent *pDispEvent     [in]响应消息的处理指针
            u16 wWaitEvent             [in]期待响应的消息
            u32 dwTimeOut = 1000       [in]期待响应的消息超时时间
返 回 值:
相关消息:
-------------------------------------------------------------------------
修改纪录:
日      期  版本  修改人  修改内容
2004/08/25  3.5   李洪强  创建
2004/10/28  3.5   王慧琛   修改
=======================================================================*/
u16 CMoonMsgDriver::PostCommand(CKdvDispEvent *pDispEvent, u16 wWaitEvent, u32 dwType, u32 dwTimeOut)
{
    return PostCommand(pDispEvent, &wWaitEvent, 1, dwType, dwTimeOut);
}


/*=======================================================================
函 数 名:   RegHandler
功    能:   注册一个处理消息的类的指针
参    数:   CDispEvent* const pDispEvnet       [in]处理消息的类指针
返 回 值:
相关消息:
-------------------------------------------------------------------------
修改纪录:
日      期  版本  修改人  修改内容
2004/08/23  3.5   李洪强  创建
=======================================================================*/
void CMoonMsgDriver::RegHandler(CKdvDispEvent* const pDispEvnet)
{
    m_vpDispEvent.push_back(pDispEvnet);
}

/*=======================================================================
函 数 名:   RegHandler
功    能:   注销一个处理消息的类的指针
参    数:   CDispEvent* const pDispEvnet       [in]处理消息的类指针
返 回 值:
相关消息:
-------------------------------------------------------------------------
修改纪录:
日      期  版本  修改人  修改内容
2004/08/23  3.5   李洪强  创建
=======================================================================*/
void CMoonMsgDriver::UnregHandler(CKdvDispEvent* const pDispEvnet)
{
    vector<CKdvDispEvent*>::iterator itr = m_vpDispEvent.begin();
    for(; itr != m_vpDispEvent.end(); itr++)
    {
        if (*itr == pDispEvnet) 
        {
            m_vpDispEvent.erase(itr);
            break;
        }
    }
}

/*=======================================================================
函 数 名:   ClearHandler
功    能:   清空所有注册的类的指针
参    数:
返 回 值:
相关消息:
-------------------------------------------------------------------------
修改纪录:
日      期  版本  修改人  修改内容
2004/08/23  3.5   李洪强  创建
=======================================================================*/
void CMoonMsgDriver::ClearHandler()
{
    m_vpDispEvent.clear();
}

void CMoonMsgDriver::ClearAllCommand()
{
    m_cCommandQueue.ClearCommand();
}

/*=============================================================================
  函 数 名： OnOspMessageComing
  功    能： 从OSP回调线程提取消息，打印消息分发消息
  算法实现： 
  全局变量： 
  参    数： WPARAM wParam  0
             LPARAM lParam  0
  返 回 值： void 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2004/10/13     3.5		王慧琛                  规范化
=============================================================================*/
void CMoonMsgDriver::OnOspMessageComing(WPARAM wParam, LPARAM lParam)
{
    // 从OSP回调线程提取消息
    CMoonMsgHandler *pHandler = CMoonMsgHandler::GetMsgHandler();
    if (!pHandler) 
    {
        return;
    }
    CMoonMsgQueue cMsgQue;
    pHandler->PopAllMsg(cMsgQue);
    // 分发消息
    while(!cMsgQue.IsEmpty())
    {
        const CMessage &cMsg = cMsgQue.Front();

		//打印输出
		CString strEvent = CPrintCtrl::GetPrintCtrl()->GetEventDescribe(cMsg.event);
		if( IS_PRINT_OUT_MSG )
		{   	 
			PrtMsg( "[MoonLib]: 收到消息:%s(%u).\n", strEvent,cMsg.event);
		}

        // 检索命令应答消息
        if(IsHandleCmd())
        {	
            vector<u16>::iterator itr = m_vWaitingEvents.begin();
            for(; itr != m_vWaitingEvents.end(); itr++)
            {
                if(*itr == cMsg.event)
                {
                    // 2004/08/24 李洪强 得到回应，清除定时器
                    ::KillTimer(m_hWndOsp, m_nTimer);
                    ClearWaiting();
                    PostNextCommand();
                    break;
                }
            }
        }
        // 检索消息分发表
        vector<CKdvDispEvent*>::iterator itr = m_vpDispEvent.begin();
        BOOL bFind = FALSE;
        for(; itr != m_vpDispEvent.end(); itr++)
        {
            if ((*itr)->HasRegEvent(cMsg.event)) 
            {
                (*itr)->DispEvent(cMsg);
                bFind = TRUE;
            }
        }
        if (!bFind) 
        {	  	 
			PrtMsg( "[MoonLib]: 消息:%s(%d)被抛弃,因为没有找到匹配的消息处理器.\n", strEvent, cMsg.event);		
        }

        cMsgQue.Pop();
    }
}

/*=============================================================================
  函 数 名： OnOspSyncMsgComing
  功    能： 同步消息处理
  算法实现： 
  全局变量： 
  参    数： WPARAM wParam 消息指针
             LPARAM lParam 0
  返 回 值： void 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2004/11/30     3.5		    王慧琛                   创建
=============================================================================*/
void CMoonMsgDriver::OnOspSyncMsgComing(WPARAM wParam, LPARAM lParam)
{    
    CMessage *pMsg = (CMessage *)wParam;
   
	//打印输出
	CString strEvent = CPrintCtrl::GetPrintCtrl()->GetEventDescribe(pMsg->event);
	if( IS_PRINT_OUT_MSG )
	{   	 
		PrtMsg( "[MoonLib]: 收到消息:%s(%u).\n", strEvent, pMsg->event);
	}

    // 检索消息分发表
    vector<CKdvDispEvent*>::iterator itr = m_vpDispEvent.begin();
    BOOL bFind = FALSE;
    for(; itr != m_vpDispEvent.end(); itr++)
    {
        if ((*itr)->HasRegEvent(pMsg->event)) 
        {
            (*itr)->DispEvent(*pMsg);
            bFind = TRUE;
        }
    }
    if (!bFind) 
    {
        // 没有注册处理函数的消息
//         map<u16, CString>::iterator itrName = m_mapEventsName.find(pMsg->event);
//         if(itrName != m_mapEventsName.end())
//         {
//             OspLog(1, "[CncLib]: 消息:%s(%d)被抛弃,因为没有找到匹配的消息处理器.\n",
//                 (LPCTSTR)((*itrName).second), pMsg->event);
//         }
//         else
//         {
//             OspLog(1, "[CncLib]: 消息:%d被抛弃,因为没有找到匹配的消息处理器.\n",
//                 pMsg->event);
//         }
		PrtMsg( "[MoonLib]: 消息:%s(%d)被抛弃,因为没有找到匹配的消息处理器.\n", strEvent, pMsg->event);
    }

}

/*=============================================================================
  函 数 名： OnTimer
  功    能： 超时计时器消息，等待的消息超时回应，清空等待消息数组
  算法实现： 
  全局变量： 
  参    数： WPARAM wParam
             LPARAM lParam
  返 回 值： void 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2004/10/13     3.5		王慧琛                  规范化
=============================================================================*/
void CMoonMsgDriver::OnTimer(WPARAM wParam, LPARAM lParam)
{
    if (wParam == m_nTimer)
    {
        // 超时计时器消息
        ::KillTimer(m_hWndOsp, m_nTimer);
        if(IsHandleCmd())
        {
            if (m_pCurDispEvent) 
            {
                m_pCurDispEvent->OnTimeOut(m_wCurSendEvent);
            }
            ClearWaiting();
            PostNextCommand();
        }
    }
	//发送文件超时,复位,即重头开始重新发送
    else if (wParam == m_nFileTransferTimer)
    {
        if (m_pbyFile == NULL)
        {
            EndTransFile();
            ::KillTimer(m_hWndOsp, m_nFileTransferTimer);
            return;
        }
        if (m_dwFileCurPos < m_dwFileLength)
        //未传送完文件，继续传送，每包30K字节
        {
            u32 dwLeft = m_dwFileLength - m_dwFileCurPos;
            if (dwLeft > 1024*30)
            {
                dwLeft = 1024*30;
            }
            PostFile(&m_pbyFile[m_dwFileCurPos], dwLeft, m_dwFileFragIndex);
            m_dwFileCurPos = m_dwFileCurPos + 1024 * 30;
            m_dwFileFragIndex++;
        }
        //传送完文件，发送停止传送请求
        else
        {
            if (m_pbyFile != NULL)
            {
                free(m_pbyFile);
                m_pbyFile = NULL;
            }
            m_dwFileCurPos = 0;
            m_dwFileFragIndex = 0;
            EndTransFile();
            ::KillTimer(m_hWndOsp, m_nFileTransferTimer);
        }
    }
    
}

/*=============================================================================
  函 数 名： WndProc
  功    能： 自定义的窗口处理函数，来区分windows消息和OSP消息以及超时消息
  算法实现： 
  全局变量： 
  参    数： HWND hWnd
             UINT uMsg
             WPARAM wParam
             LPARAM lParam
  返 回 值： LRESULT CALLBACK 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2004/10/13     3.5		王慧琛                  规范化
=============================================================================*/
LRESULT CALLBACK CMoonMsgDriver::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // 拦截OSP消息和超时计时器消息
    if (CMoonMsgDriver::s_pMsgDriver) 
    {
        if (uMsg == CMoonMsgHandler::WM_OSPMESSAGECOMING) 
        {
            CMoonMsgDriver::s_pMsgDriver->OnOspMessageComing(wParam, lParam);
        }
        else if (uMsg == CMoonMsgHandler::WM_OSPSYNCMSGCOMING)
        {
            CMoonMsgDriver::s_pMsgDriver->OnOspSyncMsgComing(wParam, lParam);            
        }
        else if (uMsg == WM_TIMER) 
        {
            CMoonMsgDriver::s_pMsgDriver->OnTimer(wParam, lParam);
        }
        else if (uMsg == CMoonMsgHandler::WM_REQMTCSTATUS)
        {
            CMoonMsgDriver::s_pMsgDriver->Dump();
        }
		else if (uMsg == CMoonMsgHandler::WM_REQIKEY)
		{
			CMoonMsgDriver::s_pMsgDriver->ReqIKey(wParam);
		}
        else
        {
			if ( CMoonMsgDriver::s_pMsgDriver->m_wndprocOld != NULL )
			{
				return CallWindowProc(CMoonMsgDriver::s_pMsgDriver->m_wndprocOld,
                                hWnd, uMsg, wParam, lParam);
			}
            
        }
    }
    return 0;
}

/*=============================================================================
  函 数 名： ClearWaiting
  功    能： 清空等待消息数组，以便调用IsHandleCmd时为FALSE，使消息得以继续发送
  算法实现： 
  全局变量： 
  参    数： 
  返 回 值： void 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2004/10/13     3.5		王慧琛                  规范化
=============================================================================*/
void CMoonMsgDriver::ClearWaiting()
{
    m_vWaitingEvents.clear();
    m_pCurDispEvent = NULL;
    m_wCurSendEvent = 0;
}

void CMoonMsgDriver::PostNextCommand()
{
    ClearWaiting();

    // 没有待发送消息时直接返回
    if(TRUE == m_cCommandQueue.IsEmpty())
    {
        return;
    }

    // 取出下一条待发送的命令
    TCOMMAND tCommand;
    BOOL32 bSucess = m_cCommandQueue.GetNextCommand(tCommand);
    if(FALSE == bSucess)
    {
        return;
    }
    
    u16* pwWaitEvent = new u16[tCommand.m_nEventNum];

    ASSERT(tCommand.m_nEventNum == tCommand.m_vctWaitEvent.size());
    
    for(u32 nIndex = 0; nIndex < tCommand.m_nEventNum; nIndex++)
    {
        pwWaitEvent[nIndex] = tCommand.m_vctWaitEvent[nIndex];
    }

    if(TYPE_CMESSAGE == tCommand.m_dwType)
    {
        m_cMsg = tCommand.m_cMsg;
    }
    else
    {
        m_cTpMsg = tCommand.m_cMtMsg;
    }

    // 将该条命令发送出去
    PostCommand(tCommand.m_pCDispEvent, pwWaitEvent, tCommand.m_nEventNum,
                tCommand.m_dwType, tCommand.m_dwTimeout);

    delete []pwWaitEvent;
}

/*=============================================================================
  函 数 名： CanBeTraceOut
  功    能： 信息输出裁判，判断改事件是否需要输出打印
  算法实现： 
  全局变量： 
  参    数： u16 wEvent  需要判断的事件ID
  返 回 值： BOOL        TRUE需要输出打印
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2004/10/13     3.5		王慧琛                  规范化
=============================================================================*/
BOOL CMoonMsgDriver::CanBeTraceOut(u16 wEvent) const
{
//    static u32 dwSN = 0;
//    static u32 dwCatalog[MTC_MSGCATALOG_COUNT];
//   //yjj CMtcLib::GetTraceStatus(dwSN, dwCatalog);
//    
//    map<u16, u32>::const_iterator itr = m_mapEventType.find(wEvent);
//    if(itr != m_mapEventType.end())
//    {
//        return dwCatalog[itr->second];
//    }
//    else
//    {
//        return dwCatalog[0];
//    }

	return TRUE;
}

/*=============================================================================
  函 数 名： TransferFile
  功    能： 开启发送定时器
  算法实现： 
  全局变量： 
  参    数： 
  返 回 值： u16 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2004/12/27     3.5		    王慧琛                   创建
=============================================================================*/
u16 CMoonMsgDriver::TransferFile()
{
    if (m_pbyFile == NULL) return 1;
    //先发送第一包
    m_dwFileCurPos = 0;
    m_dwFileFragIndex = 0;
	u16 wResult = 0;
    if (m_dwFileCurPos < m_dwFileLength)
    {
        u32 dwLeft = m_dwFileLength - m_dwFileCurPos;
        if (dwLeft > m_wMaxPackageLen)
        {
            dwLeft = m_wMaxPackageLen;
        }
		TRACE("\n开始传输文件");
        wResult = PostFile(&m_pbyFile[m_dwFileCurPos], dwLeft, m_dwFileFragIndex);
        m_dwFileCurPos = m_dwFileCurPos + m_wMaxPackageLen;
        m_dwFileFragIndex++;
    }

	return wResult;
}

void CMoonMsgDriver::StopTransferFile()
{
    m_byTransferStatus = FREE;
	if (m_pbyFile != NULL)
    {
        free(m_pbyFile);
        m_pbyFile = NULL;
    }
    
}

/*函数名： PostFile
功    能： 发送文件段
参    数： u8 *pbyBuf      文件段指针
           u32 dwBufLenth  文件段长度
           u32 nIndex      文件段序号
返 回 值： u16 
说    明： */
u16 CMoonMsgDriver::PostFile(u8 *pbyBuf, u32 dwBufLenth, u32 nIndex)
{
/*    //包头必须附带：传输协议版本号，文件标识符，文件类型，文件分片号，包长度。
	//包体：文件数据
    ZeroMemory(&m_cTpMsg, sizeof(CTpMsg));
    //传输文件
    TFileTransfer tMsgHead;
    memset( &tMsgHead, 0, sizeof (tMsgHead) );
	tMsgHead.wProtocolIdentifer = MTC_MT_FILE_VER;
	tMsgHead.wFileSliceNo = MTC_MT_MSG_BGN + nIndex;
	tMsgHead.byType = m_wFileType;
	tMsgHead.wDataLen = dwBufLenth + sizeof(TFileTransfer);

	//设置消息体
//	m_cKdvMsg.SetEvent(ev_FTSendFileCmd);
	m_cTpMsg.SetBody(&tMsgHead, sizeof( TFileTransfer ));
	m_cTpMsg.CatBody( pbyBuf, dwBufLenth );
 
//	OspPrintf(TRUE, FALSE, "传送的数据长度%d\n", dwBufLenth);
	TRACE("传送的数据长度%d\n", dwBufLenth);
*/
    u16 wResult = PostMsg(TYPE_TPMSG);
    
    return wResult;
}

/*=============================================================================
  函 数 名： MappingHelper
  功    能： 映射事件名称，同时注册到事件类别数组里面
  算法实现： 
  全局变量： 
  参    数： u16 wEvent                 事件ID
             const CString& strName     事件名称
             CATALOG catalog            类别
  返 回 值： void 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2004/10/13     3.5		王慧琛                  规范化
=============================================================================*/
void CMoonMsgDriver::MappingHelper(u16 wEvent, const CString& strName, CATALOG catalog)
{
    m_mapEventsName[wEvent] = strName;
    m_mapEventType[wEvent] = catalog;
}

/*=============================================================================
  函 数 名： MappingEventName
  功    能： 注册事件
  算法实现： 
  全局变量： 
  参    数： 
  返 回 值： void 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
 2011/05/10     1.0		    肖楚然                  创建
=============================================================================*/
void CMoonMsgDriver::MappingEventName()
{
    //登陆
	MAPPING_HELPER( OSP_DISCONNECT, _T("OSP_DISCONNECT") );
	MAPPING_HELPER( ev_TpMoonLogin_Req, _T("ev_TpMoonLogin_Req") );
	MAPPING_HELPER( ev_TpMoonLogin_Rsp, _T("ev_TpMoonLogin_Rsp") );
	//摄像机
	MAPPING_HELPER( ev_TpMoonCamInfo_Nty, _T("ev_TpMoonCamInfo_Nty"));
	MAPPING_HELPER( ev_TpCamSelect_Cmd, _T("ev_TpCamSelect_Cmd"));
	MAPPING_HELPER( ev_TpCamSelect_Ind, _T("ev_TpCamSelect_Ind"));
	MAPPING_HELPER( ev_TpCamSelect_Nty, _T("ev_TpCamSelect_Nty"));
	MAPPING_HELPER( ev_CamParaSynchronize_Cmd, _T("ev_CamParaSynchronize_Cmd"));
	MAPPING_HELPER( ev_CamParaSynchronize_Ind, _T("ev_CamParaSynchronize_Ind"));
	MAPPING_HELPER( ev_TpMechanismSelect_Nty, _T("ev_TpMechanismSelect_Nty"));
	MAPPING_HELPER( ev_TpMechVer_Nty, _T("ev_TpMechVer_Nty"));
	MAPPING_HELPER( ev_TpMechanismSelect_Cmd, _T("ev_TpMechanismSelect_Cmd"));
	MAPPING_HELPER( ev_TpMechanismSelect_Ind, _T("ev_TpMechanismSelect_Ind"));
	MAPPING_HELPER( ev_TpCamSetZoonStart_Cmd, _T("ev_TpCamSetZoonStart_Cmd"));
	MAPPING_HELPER( ev_TpCamSetZoonStart_Ind, _T("ev_TpCamSetZoonStart_Ind"));
	MAPPING_HELPER( ev_TpCamSetZoonStop_Cmd, _T("ev_TpCamSetZoonStop_Cmd"));	
	MAPPING_HELPER( ev_TpCamSetZoonStop_Ind, _T("ev_TpCamSetZoonStop_Ind"));
	MAPPING_HELPER( ev_TpCamSetDrectZoon_Cmd, _T("ev_TpCamSetDrectZoon_Cmd"));	
	MAPPING_HELPER( ev_TpCamSetDrectZoon_Ind, _T("ev_TpCamSetDrectZoon_Ind"));	
	MAPPING_HELPER( ev_TpCamFocusMode_Cmd, _T("ev_TpCamFocusMode_Cmd"));
	MAPPING_HELPER( ev_TpCamFocusMode_Ind, _T("ev_TpCamFocusMode_Ind"));
	MAPPING_HELPER( ev_TpCamFocusNear_Cmd, _T("ev_TpCamFocusNear_Cmd"));
	MAPPING_HELPER( ev_TpCamFocusStop_Cmd, _T("ev_TpCamFocusStop_Cmd"));
	MAPPING_HELPER( ev_TpCamFocusFar_Cmd, _T("ev_TpCamFocusFar_Cmd"));
	MAPPING_HELPER( ev_TpCamFocusNear_Ind, _T("ev_TpCamFocusNear_Ind"));
	MAPPING_HELPER( ev_TpCamFocusStop_Ind, _T("ev_TpCamFocusStop_Ind"));
	MAPPING_HELPER( ev_TpCamFocusFar_Ind, _T("ev_TpCamFocusFar_Ind"));
	MAPPING_HELPER( ev_TpCamExpMode_Cmd, _T("ev_TpCamExpMode_Cmd"));
	MAPPING_HELPER( ev_TpCamExpMode_Ind, _T("ev_TpCamExpMode_Ind"));
	MAPPING_HELPER( ev_TpCamExpAperture_Cmd, _T("ev_TpCamExpAperture_Cmd"));
	MAPPING_HELPER( ev_TpCamExpAperture_Ind, _T("ev_TpCamExpAperture_Ind"));
	MAPPING_HELPER( ev_TpCamExpSOrThShutter_Cmd, _T("ev_TpCamExpSOrThShutter_Cmd"));
	MAPPING_HELPER( ev_TpCamExpSOrThShutter_Ind, _T("ev_TpCamExpSOrThShutter_Ind"));
	MAPPING_HELPER( ev_TpCamExpGain_Cmd, _T("ev_TpCamExpGain_Cmd"));
	MAPPING_HELPER( ev_TpCamExpGain_Ind, _T("ev_TpCamExpGain_Ind"));
	MAPPING_HELPER( ev_TpCamWhiteBalanceMode_Cmd, _T("ev_TpCamWhiteBalanceMode_Cmd"));
	MAPPING_HELPER( ev_TpCamWhiteBalanceMode_Ind, _T("ev_TpCamWhiteBalanceMode_Ind"));
	MAPPING_HELPER( ev_TpCamWhiteBalanceRGain_Cmd, _T("ev_TpCamWhiteBalanceRGain_Cmd"));
	MAPPING_HELPER( ev_TpCamWhiteBalanceRGain_Ind, _T("ev_TpCamWhiteBalanceRGain_Ind"));
	MAPPING_HELPER( ev_TpCamWhiteBalanceBGain_Cmd, _T("ev_TpCamWhiteBalanceBGain_Cmd"));
	MAPPING_HELPER( ev_TpCamWhiteBalanceBGain_Ind, _T("ev_TpCamWhiteBalanceBGain_Ind"));
	MAPPING_HELPER( ev_TpCamImagePara_Cmd, _T("ev_TpCamImagePara_Cmd"));
	MAPPING_HELPER( ev_TpCamImagePara_Ind, _T("ev_TpCamImagePara_Ind"));
	MAPPING_HELPER( ev_TpCamSetGamma_Cmd, _T("ev_TpCamSetGamma_Cmd"));
	MAPPING_HELPER( ev_TpCamSetGamma_Ind, _T("ev_TpCamSetGamma_Ind"));
	MAPPING_HELPER( ev_TpCamBackLight_Cmd, _T("ev_TpCamBackLight_Cmd"));
	MAPPING_HELPER( ev_TpCamBackLight_Ind, _T("ev_TpCamBackLight_Ind"));
	MAPPING_HELPER( ev_TpImageDistortCorrect_Cmd, _T("ev_TpImageDistortCorrect_Cmd"));
	MAPPING_HELPER( ev_TpImageDistortCorrect_Ind, _T("ev_TpImageDistortCorrect_Ind"));	
	MAPPING_HELPER( ev_TpCamReduNoise_Cmd, _T("ev_TpCamReduNoise_Cmd"));
	MAPPING_HELPER( ev_TpCamReduNoise_Ind, _T("ev_TpCamReduNoise_Ind"));
	MAPPING_HELPER( ev_TpSetCam2DNoiseLevle_Cmd, _T("ev_TpSetCam2DNoiseLevle_cmd"));
	MAPPING_HELPER( ev_TpSetCam2DNoiseLevle_Ind, _T("ev_TpSetCam2DNoiseLevle_Ind"));	
	MAPPING_HELPER( ev_TpSetCam3DNoiseLevle_Cmd, _T("ev_TpSetCam3DNoiseLevle_cmd"));
	MAPPING_HELPER( ev_TpSetCam3DNoiseLevle_Ind, _T("ev_TpSetCam3DNoiseLevle_Ind"));
	MAPPING_HELPER( ev_TpCamInitPreset_Cmd, _T("ev_TpCamInitPreset_Cmd"));
	MAPPING_HELPER( ev_TpCamInitPreset_Ind, _T("ev_TpCamInitPreset_Ind"));
	MAPPING_HELPER( ev_tpMoonReboot_Cmd, _T("ev_tpMoonReboot_Cmd"));
	MAPPING_HELPER( ev_TpCamPreSet_Nty, _T("ev_TpCamPreSet_Nty"));
	MAPPING_HELPER( ev_TpCamPreSet_Cmd, _T("ev_TpCamPreSet_Cmd"));
	MAPPING_HELPER( ev_TpCamPreSet_Ind, _T("ev_TpCamPreSet_Ind"));
	MAPPING_HELPER( ev_TpCamPreReset_Cmd, _T("ev_TpCamPreReset_Cmd"));
	MAPPING_HELPER( ev_TpCamPreReset_Ind, _T("ev_TpCamPreReset_Ind"));
	MAPPING_HELPER( ev_TpCamPreModify_Cmd, _T("ev_TpCamPreModify_Cmd"));
	MAPPING_HELPER( ev_TpCamPreModify_Ind, _T("ev_TpCamPreModify_Ind"));
	MAPPING_HELPER( ev_TpCamPreRecall_Cmd, _T("ev_TpCamPreRecall_Cmd"));
	MAPPING_HELPER( ev_TpCamPreRecall_Ind, _T("ev_TpCamPreRecall_Ind"));
	MAPPING_HELPER( ev_TpCamParamUpload_Cmd, _T("ev_TpCamParamUpload_Cmd"));
	MAPPING_HELPER( ev_TpCamParamUpload_Ind, _T("ev_TpCamParamUpload_Ind"));
	MAPPING_HELPER( ev_TpCamParamUpload_Nty, _T("ev_TpCamParamUpload_Nty"));
	MAPPING_HELPER( ev_TpMoonUpgrade_Ind, _T("ev_TpMoonUpgrade_Ind"));
	MAPPING_HELPER( ev_TpMoonUpgrade_Cmd, _T("ev_TpMoonUpgrade_Cmd"));	
	MAPPING_HELPER( ev_CamUpgrade_Cmd, _T("ev_CamUpgrade_Cmd"));	
	MAPPING_HELPER( ev_CamUpgrade_Ind, _T("ev_CamUpgrade_Ind"));
	MAPPING_HELPER( ev_TpCamParamDefault_Cmd, _T("ev_TpCamParamDefault_Cmd"));
	MAPPING_HELPER( ev_TpCamParamDefault_Ind, _T("ev_TpCamParamDefault_Ind"));	
	MAPPING_HELPER( ev_TpSetRefer_Cmd, _T("ev_TpSetRefer_Cmd"));	
	MAPPING_HELPER( ev_TpSetRefer_Ind, _T("ev_TpSetRefer_Ind"));
	MAPPING_HELPER( ev_TpSetRefer_Nty, _T("ev_TpSetRefer_Nty"));	
	MAPPING_HELPER( ev_TpFlatTurn_Cmd, _T("ev_TpFlatTurn_Cmd"));	
	MAPPING_HELPER( ev_TpFlatTurn_Ind, _T("ev_TpFlatTurn_Ind"));
	MAPPING_HELPER( ev_TpFlatTurn_Nty, _T("ev_TpFlatTurn_Nty"));
	MAPPING_HELPER( ev_TpDisortSwitch_Cmd, _T("ev_TpDisortSwitch_Cmd"));
	MAPPING_HELPER( ev_TpDisortSwitch_Ind, _T("ev_TpDisortSwitch_Ind"));
	MAPPING_HELPER( ev_TpSetDisort_Cmd, _T("ev_TpSetDisort_Cmd"));
	MAPPING_HELPER( ev_TpSetDisort_Ind, _T("ev_TpSetDisort_Ind"));
	MAPPING_HELPER( ev_TpCamSnapshot_Cmd, _T("ev_TpCamSnapshot_Cmd"));
	MAPPING_HELPER( ev_TpCamSnapshot_Ind, _T("ev_TpCamSnapshot_Ind"));
	MAPPING_HELPER( ev_TPSetColorRGB_Cmd, _T("ev_TPSetColorRGB_Cmd"));
	MAPPING_HELPER( ev_TPSetColorRGB_Ind, _T("ev_TPSetColorRGB_Ind"));
	MAPPING_HELPER( ev_TPAutoSetColorConstancy_Cmd, _T("ev_TPAutoSetColorConstancy_Cmd"));
	MAPPING_HELPER( ev_TPAutoSetColorConstancy_Ind, _T("ev_TPAutoSetColorConstancy_Ind"));	
	MAPPING_HELPER( ev_TPDirectSetColorRGB_Cmd, _T("ev_TPDirectSetColorRGB_Cmd"));
	MAPPING_HELPER( ev_TPDirectSetColorRGB_Ind, _T("ev_TPDirectSetColorRGB_Ind"));
	MAPPING_HELPER( ev_TPChangeSideRGB_Nty, _T("ev_TPChangeSideRGB_Nty"));
//	MAPPING_HELPER( ev_TPRectInfo_Nty, _T("ev_TPRectInfo_Nty"));
	MAPPING_HELPER( ev_TPChooseRectangle_Cmd, _T("ev_TPChooseRectangle_Cmd"));
	MAPPING_HELPER( ev_TPChooseRectangle_Ind, _T("ev_TPChooseRectangle_Ind"));
	MAPPING_HELPER( ev_TPChangeDistor_Cmd, _T("ev_TPChangeDistor_Cmd"));
	MAPPING_HELPER( ev_TPChangeDistor_Ind, _T("ev_TPChangeDistor_Ind"));
	MAPPING_HELPER( ev_TPDirectSetDistor_Cmd, _T("ev_TPDirectSetDistor_Cmd"));
	MAPPING_HELPER( ev_TPDirectSetDistor_Ind, _T("ev_TPDirectSetDistor_Ind"));	
	MAPPING_HELPER( ev_TPMoonShowRectRegion_Cmd, _T("ev_TPMoonShowRectRegion_Cmd"));
	MAPPING_HELPER( ev_TPMoonShowRectRegion_Ind, _T("ev_TPMoonShowRectRegion_Ind"));
	MAPPING_HELPER( ev_TpColorSwich_Cmd, _T("ev_TpColorSwich_Cmd"));
	MAPPING_HELPER( ev_TpColorSwich_Ind, _T("ev_TpColorSwich_Ind"));
//	MAPPING_HELPER( ev_TPMoonShowRectRegion_Nty, _T("ev_TPMoonShowRectRegion_Nty"));
	MAPPING_HELPER( ev_TpSecDefault_Nty, _T("ev_TpSecDefault_Nty"));
	MAPPING_HELPER( ev_TpSecBoundary_Nty, _T("ev_TpSecBoundary_Nty"));
    MAPPING_HELPER( ev_TpFpgaDelayCorrect_Cmd, _T("ev_TpFpgaDelayCorrect_Cmd"));
    MAPPING_HELPER( ev_TpFpgaDelayCorrect_Ind, _T("ev_TpFpgaDelayCorrect_Ind"));
    MAPPING_HELPER( ev_TpFpgaDelayCorrect_Nty, _T("ev_TpFpgaDelayCorrect_Nty"));

	//系统设置
	MAPPING_HELPER( ev_TpMoonVerInfo_Nty, _T("ev_TpMoonVerInfo_Nty"));
	MAPPING_HELPER( ev_TpCamOutPortInfo_Nty, _T("ev_TpCamOutPortInfo_Nty"));
	MAPPING_HELPER( ev_TpCamImageAdjust_Nty, _T("ev_TpCamImageAdjust_Nty"));
	MAPPING_HELPER( ev_TpMoonCfgEthnet_Ind, _T("ev_TpMoonCfgEthnet_Ind"));
	MAPPING_HELPER( ev_TpCamOutPortInfo_Cmd, _T("ev_TpCamOutPortInfo_Cmd"));
	MAPPING_HELPER( ev_TpCamOutPortInfo_Ind, _T("ev_TpCamOutPortInfo_Ind"));
	MAPPING_HELPER( ev_TpCamImageAdjust_Cmd, _T("ev_TpCamImageAdjust_Cmd"));
	MAPPING_HELPER( ev_TpCamImageAdjust_Ind, _T("ev_TpCamImageAdjust_Ind"));	
	MAPPING_HELPER( ev_TpMoonCfgEthnet_Cmd, _T("ev_TpMoonCfgEthnet_Cmd"));	
	MAPPING_HELPER( ev_TpSetLVDSBaud_Ind, _T("ev_TpSetLVDSBaud_Ind"));
	MAPPING_HELPER( ev_TpSetLVDSBaud_Nty, _T("ev_TpSetLVDSBaud_Nty"));
}

void CMoonMsgDriver::SetInsID( u16 wDstInsID )
{
	m_wInsID = wDstInsID;
}
u16  CMoonMsgDriver::GetInsID()
{
	return m_wInsID;
}

void CMoonMsgDriver::SetAppID( u16 wAppID )
{
	m_wAppID = wAppID;
}

u16 CMoonMsgDriver::GetAppID()
{
	return m_wAppID;
}


void CMoonMsgDriver::SetDesIID( u32 dwDesID )
{
    m_dwDesIID = dwDesID;
}

u32 CMoonMsgDriver::GetDesIID()
{
    return m_dwDesIID;
}


