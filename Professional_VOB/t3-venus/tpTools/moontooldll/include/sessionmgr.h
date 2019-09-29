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

#include "moonlib.h"

class CMoonlibSessionMgr
{
public:
	static CMoonlibSessionMgr* GetSingleTon();
	~CMoonlibSessionMgr();
 
	void CreateSession();
	void DestroySession();
	CMoonSessionCtrlIF* GetSessionIF() const					{ return m_pMoonSessionIF; }
	CCamConfigIF* GetCamConfigIF() const                        { return m_pCamConfigIF; }
	CSysConfigIF* GetSysConfigIF() const						{ return m_pSysConfigIF; }
	

private:
	CMoonlibSessionMgr();
private:
 	static CMoonlibSessionMgr	*m_pThis;
 	CMoonSessionCtrlIF	*m_pMoonSessionIF;
	CCamConfigIF *m_pCamConfigIF;
	CSysConfigIF *m_pSysConfigIF;
};

#define MOONSESSION_MGR_PTR CMoonlibSessionMgr::GetSingleTon()
 
#endif