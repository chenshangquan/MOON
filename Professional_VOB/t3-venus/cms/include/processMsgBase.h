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
	* ����:  ��ʼ��logic 
	* @return  void
	* @remarks	�������ڣ��Ի�ȡm_hWnd���ܹ����յ�mfc��Ϣ 
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