// addrinstance.h: interface for the CAddrInstance class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADDRINSTANCE_H__64AD9D9B_50DA_4F4B_A324_11F6CBC612AB__INCLUDED_)
#define AFX_ADDRINSTANCE_H__64AD9D9B_50DA_4F4B_A324_11F6CBC612AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CAddrInstance : public CInstance 
{
public:
	CAddrInstance();
	virtual ~CAddrInstance();

    virtual void InstanceEntry(CMessage *const pMsg);
};

extern zTemplate<CAddrInstance, 1> g_AddrBookApp;

#endif // !defined(AFX_ADDRINSTANCE_H__64AD9D9B_50DA_4F4B_A324_11F6CBC612AB__INCLUDED_)
