/*****************************************************************************
ģ����      : ����cnclib�и���������Ľӿ�
�ļ���      : sessionmgr.h
����ļ�    : cnclib.h
�ļ�ʵ�ֹ���: ���ⲿ����cnclib
����        : ������
�汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/11/23     1.0						����
******************************************************************************/
#ifndef __SESSIONMGR_H__
#define __SESSIONMGR_H__

#include "rkclib.h"

class CMoonlibSessionMgr
{
public:
	static CMoonlibSessionMgr* GetSingleTon();
	~CMoonlibSessionMgr();
 
	void CreateSession();
	void DestroySession();
	CRkcSessionCtrlIF* GetSessionIF() const					{ return m_pMoonSessionIF; }
    CRkcSysCtrlIF* GetSysCtrlIF() const                       { return m_pSysCtrlIf; }
	CCamConfigIF* GetCamConfigIF() const                        { return m_pCamConfigIF; }
	CSysConfigIF* GetSysConfigIF() const						{ return m_pSysConfigIF; }
	

private:
	CMoonlibSessionMgr();
private:
 	static CMoonlibSessionMgr	*m_pThis;
 	CRkcSessionCtrlIF	*m_pMoonSessionIF;

    CRkcSysCtrlIF *m_pSysCtrlIf;
	CCamConfigIF *m_pCamConfigIF;
	CSysConfigIF *m_pSysConfigIF;
};

#define MOONSESSION_MGR_PTR CMoonlibSessionMgr::GetSingleTon()
 
#endif