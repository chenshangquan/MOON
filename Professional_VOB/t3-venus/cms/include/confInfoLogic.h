// confInfoLogic.h: interface for the CConfInfoLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONFINFOLOGIC_H__578D6C62_CD8D_4F3B_848F_D9ABC93E74D1__INCLUDED_)
#define AFX_CONFINFOLOGIC_H__578D6C62_CD8D_4F3B_848F_D9ABC93E74D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CConfInfoLogic : public CWndLogicBase  
{
public: 
    static CConfInfoLogic* GetLogicPtr(); 
    CConfInfoLogic();
    virtual ~CConfInfoLogic(); 
    
public:  
    
    virtual bool RegCBFun();
    
    virtual bool UnRegFunc( );
    
    virtual bool InitWnd( const IArgs & arg );

    /**	 
	* 功能:  清空所有状态和数据
	* @return   
	* @remarks	 
	*/
    virtual void Clear() ;

    bool BtnConfLstItemHungupClick( const IArgs & arg );
    
    bool BtnSaveToFileClick( const IArgs & arg );
    bool BtnClsoeClick( const IArgs & arg );
     
    bool OnConfLstItemClick( const IArgs & arg );
protected: 
    
    afx_msg HRESULT OnRefreshConfLst( WPARAM wparam, LPARAM lparam); 
 
private:
    void UpdateConfLst();
    
protected: 
    virtual void RegMsg(); 
    virtual void UnRegMsg();
    
private:
    TCMSConf m_tSelCmsConf;
    static CConfInfoLogic *m_pLogic;

    static const String  m_stcStrLstConf;
};

#endif // !defined(AFX_CONFINFOLOGIC_H__578D6C62_CD8D_4F3B_848F_D9ABC93E74D1__INCLUDED_)
