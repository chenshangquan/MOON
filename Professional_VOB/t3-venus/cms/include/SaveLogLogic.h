// SaveLog.h: interface for the CSaveLog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SAVELOG_H__1D5400CE_572F_41B5_82D6_A9746BE3C111__INCLUDED_)
#define AFX_SAVELOG_H__1D5400CE_572F_41B5_82D6_A9746BE3C111__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"
#include <afxinet.h>
#include <list>
class CSaveLog : public CWndLogicBase, public CWnd
{
public:
	CSaveLog();
	virtual ~CSaveLog();
    static CSaveLog* GetLogicPtr();
    
public:
    virtual bool RegCBFun();
    virtual bool UnRegFunc();
	virtual void RegMsg();
    /**	 
	* 功能:  清空所有状态和数据
	* @return   
	* @remarks	 
	*/
    virtual void Clear();

    //从配置文件中得到日志文件路径
    void GetLogPathFromIni( CString& strPath );

protected:
    bool InitWnd( const IArgs & args );

    bool OnBtnOk( const IArgs & args );
    
    bool OnBtnCancel( const IArgs & args );

    bool OnBtnDwnOk( const IArgs & args );   

    bool OnBtnExit( const IArgs & args );

    static UINT ThreadDwonLoad(LPVOID lpParam);

	BOOL ExistDir( const CString strDir );

	BOOL CreateDir( CString strDir );

private:
    static CSaveLog *m_pLogic;

    CString m_strIPAddress;          //IP from CNS
    
    CString m_strLogPath;            //local log path

    static const String m_strProg;   //progress control Name
    static const String m_strProgInfo;   //progress info Name

    DWORD m_dwTotalFileSize;
    CFtpConnection* m_pConnect;
    
	CInternetFile* m_pInternetFile ;
    CFile m_cFile;

	CWinThread* m_pThread;
public:
    CInternetSession m_sess;
    list<CString> m_lstFtpFile;
    
    CString m_strCfgFile;
    
};

#endif // !defined(AFX_SAVELOG_H__1D5400CE_572F_41B5_82D6_A9746BE3C111__INCLUDED_)
