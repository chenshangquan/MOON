#include "stdafx.h"
#include "moonToolDll.h"
#include "sessionmgr.h"
#include "tpmsginit.h"

CMoonlibSessionMgr* CMoonlibSessionMgr::m_pThis = NULL;

CMoonlibSessionMgr::CMoonlibSessionMgr():
 				  m_pMoonSessionIF(NULL)
{
	CreateSession();
}

CMoonlibSessionMgr::~CMoonlibSessionMgr()
{
	DestroySession(); 
}

CMoonlibSessionMgr* CMoonlibSessionMgr::GetSingleTon()
{
	if ( m_pThis == NULL )
    {
        m_pThis = new CMoonlibSessionMgr();	 
    }
	return m_pThis;
}

void CMoonlibSessionMgr::CreateSession()
{
	InitTpEvent();
	//´´½¨cnssession
	CMoonLib::CreateSession( &m_pMoonSessionIF );
	if ( NULL == m_pMoonSessionIF )
	{
		return;
	}
	m_pMoonSessionIF->InitEnv( AID_MOONTOOL2CAM_APP );
	// if point init 
	m_pMoonSessionIF->MoonGetInterface( &m_pCamConfigIF );
	m_pMoonSessionIF->MoonGetInterface( &m_pSysConfigIF );
    
}

void CMoonlibSessionMgr::DestroySession()
{
 	CMoonLib::DestroySession( &m_pMoonSessionIF );
     
 	m_pMoonSessionIF = NULL;
 
	if (  NULL != m_pThis)
	{
		delete m_pThis;
		m_pThis = NULL;		
	}
}
