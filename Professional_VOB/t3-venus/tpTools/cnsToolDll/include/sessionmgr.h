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

#include "cnclib.h"

class CCnclibSessionMgr
{
public:
	static CCnclibSessionMgr* GetSingleTon();
	~CCnclibSessionMgr();
 
	void CreateSession();
	void DesdroySession();
	CCnsSessionCtrlIF* GetSessionIF() const					{ return m_pCnsSessionIF; }
	CCncConfigIF* GetConfigIF() const						{ return m_pCnsConfigIF; }
	CCncConfCtrlIF* GetConfCtrlIF() const					{ return m_pCnsConfIF; }
	CCncSipInfoCtrlIF* GetSipInfoCtrlIF() const				{ return m_pSipInfoIF; }
	CCncPortDiagCtrlIF* GetPortDiagCtrlIF() const			{ return m_pPortDiagIF; }
	CCncSysCtrlIF* GetSysCtrlIF() const						{ return m_pSysCtrlIF; }
	CCncCenterCtrlIF* GetCenterCtrlIF() const				{ return m_pCenterCtrlIF; }
	CCncNetMngCtrlIF* GetNetMngCtrlIF() const				{ return m_pNetMngCtrlIF; }
private:
	CCnclibSessionMgr();
private:
 	static CCnclibSessionMgr	*m_pThis;
 	CCnsSessionCtrlIF	*m_pCnsSessionIF;
	CCncConfigIF        *m_pCnsConfigIF;
	CCncConfCtrlIF      *m_pCnsConfIF;
	CCncSipInfoCtrlIF   *m_pSipInfoIF;
	CCncPortDiagCtrlIF	*m_pPortDiagIF;
	CCncSysCtrlIF       *m_pSysCtrlIF;
	CCncCenterCtrlIF    *m_pCenterCtrlIF;
	CCncNetMngCtrlIF	*m_pNetMngCtrlIF;
};

#define CNCSESSION_MGR_PTR CCnclibSessionMgr::GetSingleTon()
 
#endif