// handleErr.cpp: implementation of the CHandleErr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cms.h"
#include "handleErr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
 

CHandleErr::CHandleErr():m_vctErr()
{
    
}

CHandleErr::~CHandleErr()
{

}

void CHandleErr::DeclareErr( u32 dwErrID, CString strDescribe )
{
	m_vctErr.insert( ErrMap::value_type( dwErrID, strDescribe ));
}
 

CString CHandleErr::GetErrDescribe( u32 dwErrID )
{  
	CString str = "";
	ErrMap::iterator it = m_vctErr.find(dwErrID);
	if ( it!=m_vctErr.end() )  
	{ 
		 str = it->second; 
	} 
   return str; 
}
 

