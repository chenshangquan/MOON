// tpadinstance.h: interface for the CTPadInstance class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TPADINSTANCE_H__C0196DB1_28EA_4DEF_AE92_C89D8BDC6653__INCLUDED_)
#define AFX_TPADINSTANCE_H__C0196DB1_28EA_4DEF_AE92_C89D8BDC6653__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define INSTANCE_COUNT	1	// 接收消息的实例的数目

class CTPadInstance : public CInstance
{
public:
	CTPadInstance();
	virtual ~CTPadInstance();

    virtual void InstanceEntry(CMessage *const pMsg);

};

extern zTemplate<CTPadInstance, INSTANCE_COUNT> g_tPadApp;

#endif // !defined(AFX_TPADINSTANCE_H__C0196DB1_28EA_4DEF_AE92_C89D8BDC6653__INCLUDED_)
