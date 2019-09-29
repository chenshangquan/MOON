// loadinstance.cpp: implementation of the CLoadInstance class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "loadcmc.h"
#include "loadinstance.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


////////////////////////////////////////////////////////////////////////////////
// 全局Osp应用程序对象
zTemplate<CLoadInstance, SERVER_MAX_INST, CAppNoData> g_loadApp;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CLoadInstance::CLoadInstance()
{
	m_dwDstNode = INVALID_NODE;
	m_dwDstId = 0;
}

CLoadInstance::~CLoadInstance()
{

}


void CLoadInstance::InstanceEntry(CMessage *const pMsg)
{
	u16 wCurEvent;
	if (NULL == pMsg)
	{
		OspPrintf(TRUE, FALSE, "InstanceEntry: NULL message!\n");
		return;
	}
	
	wCurEvent = pMsg->event;
	switch (wCurEvent) 
	{
	case ev_LoginLoadCmc_Req:
		OnConnectReq(pMsg);
		break;
	case ev_RebootCmc_Cmd:
		OnRebootCmd();
	case ev_UpdateOver_Nty:
		OnUpdateOverNty();
	case OSP_DISCONNECT:
		//发生断链
		OnOspDisconnect(pMsg);	
	default:
		break;
	}
}


void CLoadInstance::OnConnectReq(CMessage *const pMsg)
{
	m_dwDstNode = pMsg->srcnode;
	m_dwDstId = pMsg->srcid;
	BOOL bLogin = TRUE;
	post( m_dwDstId, ev_LoginLoadCmc_Rsp, &bLogin, sizeof(BOOL), m_dwDstNode );

	::OspNodeDiscCBRegQ(m_dwDstNode, m_appId, m_instId);

	OspPrintf(TRUE, FALSE, "Accept login!\n");	
}




void CLoadInstance::OnOspDisconnect(CMessage *const pMsg)
{
	if ( m_dwDstNode != INVALID_NODE )
	{
		OspDisconnectTcpNode( m_dwDstNode );
	}	
}


void CLoadInstance::OnUpdateOverNty()
{
	AfxGetMainWnd()->PostMessage( UI_UPDATECMC_OVER );
}

void CLoadInstance::OnRebootCmd()
{
	AfxGetMainWnd()->PostMessage( UI_REBOOTCMC_CMD );
}