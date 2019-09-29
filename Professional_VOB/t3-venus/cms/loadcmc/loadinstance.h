// loadinstance.h: interface for the CLoadInstance class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOADINSTANCE_H__F7E2E14F_0F7D_4A41_A05D_AB826786DA9D__INCLUDED_)
#define AFX_LOADINSTANCE_H__F7E2E14F_0F7D_4A41_A05D_AB826786DA9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "osp.h"

//using namespace std;


//app中实例的最大数
#define SERVER_MAX_INST (20)


class CLoadInstance : public CInstance  
{
public:
	CLoadInstance();
	virtual ~CLoadInstance();

	virtual void InstanceEntry(CMessage *const pMsg);		//消息入口函数
private:
	void OnConnectReq(CMessage *const pMsg);
	void OnOspDisconnect(CMessage *const pMsg);
	void OnUpdateOverNty();
	void OnRebootCmd();

	u32 m_dwDstNode;		//源NodeId
	u32 m_dwDstId;			//实例Id		
};

extern zTemplate<CLoadInstance, SERVER_MAX_INST, CAppNoData> g_loadApp;

#endif // !defined(AFX_LOADINSTANCE_H__F7E2E14F_0F7D_4A41_A05D_AB826786DA9D__INCLUDED_)
