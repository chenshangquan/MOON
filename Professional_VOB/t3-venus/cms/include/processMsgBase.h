// processMsgBase.h: interface for the CProcessMsgBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined  (AFX_PROCESSMSGBASE_H__D317AF0A_AF9E_4D99_B57B_0B338A2486D2__INCLUDED_)
#define  AFX_PROCESSMSGBASE_H__D317AF0A_AF9E_4D99_B57B_0B338A2486D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000 

class CProcessMsgBase:public CWnd  
{
public:
	CProcessMsgBase() 
	{
		 Init();
	}
	
	virtual ~CProcessMsgBase() 
	{ 
	}
 
public:
  /**	 
	* 功能:  初始化logic 
	* @return  void
	* @remarks	创建窗口，以获取m_hWnd，能够接收到mfc消息 
	*/
    void Init()
	{
		if ( this->m_hWnd == NULL ) 
		{
             CWnd::CreateEx( 0, AfxRegisterWndClass(CS_DBLCLKS), _T("procedueMsgView"),
			WS_OVERLAPPEDWINDOW, CRect(10, 10, 10, 10), NULL, NULL, NULL ) ;   
		}
	}
 
 
};  

 
 
 
 

#endif // !defined(AFX_PROCESSMSGBASE_H__D317AF0A_AF9E_4D99_B57B_0B338A2486D2__INCLUDED_)