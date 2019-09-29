// errCodeManage.h: interface for the CErrCodeManage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ERRCODEMANAGE_H__AD793837_2DFE_4643_A93D_6676F1AB731F__INCLUDED_)
#define AFX_ERRCODEMANAGE_H__AD793837_2DFE_4643_A93D_6676F1AB731F__INCLUDED_
#include <map>
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000 
typedef std::map<DWORD,CString> MapErrtInfo;
class CErrCodeManage  
{
public: 
    static CErrCodeManage*GetErrCodeManage();
    void AddErr( DWORD dwErrId, char * format,... );
    
     CString GetErrString( DWORD dwErrId );
    
     void Instance();

protected:
    CErrCodeManage();
	virtual ~CErrCodeManage();
   
private:
    static CErrCodeManage* m_pErrManager;
    static MapErrtInfo m_mapErrInfo;
};


#define  GET_ERR_STRING(dwErrId) CErrCodeManage::GetErrCodeManage()->GetErrString( dwErrId) 
#define  ADD_ERR(dwErrId,str) CErrCodeManage::GetErrCodeManage()->AddErr(dwErrId,str) 

 

#endif // !defined(AFX_ERRCODEMANAGE_H__AD793837_2DFE_4643_A93D_6676F1AB731F__INCLUDED_)
