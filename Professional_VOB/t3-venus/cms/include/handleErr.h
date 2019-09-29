// handleErr.h: interface for the CHandleErr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HANDLEERR_H__68823878_875E_4882_A3CA_D383A1DA16D2__INCLUDED_)
#define AFX_HANDLEERR_H__68823878_875E_4882_A3CA_D383A1DA16D2__INCLUDED_
#include <map>   
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CHandleErr  
{
public:
	CHandleErr();
	virtual ~CHandleErr();
   
	void DeclareErr( u32 dwErrID, CString strDescribe );
	CString GetErrDescribe( u32 dwErrID );
private:
  typedef std::map<u32 , CString > ErrMap ;
   ErrMap m_vctErr;    
};

#endif // !defined(AFX_HANDLEERR_H__68823878_875E_4882_A3CA_D383A1DA16D2__INCLUDED_)
