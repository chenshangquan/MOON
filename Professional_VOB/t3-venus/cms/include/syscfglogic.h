// syscfglogic.h: interface for the CSysCfgLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSCFGLOGIC_H__D288469E_6B39_43F6_AC35_D46BA9372DEF__INCLUDED_)
#define AFX_SYSCFGLOGIC_H__D288469E_6B39_43F6_AC35_D46BA9372DEF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CSysCfgLogic : public CWndLogicBase 
{
public:
	CSysCfgLogic();
	virtual ~CSysCfgLogic();
	static CSysCfgLogic* GetLogicPtr();
	
public:
	virtual bool RegCBFun();
	virtual bool UnRegFunc();
	virtual void RegMsg();

    /**	 
	* ����:  �������״̬������
	* @return   
	* @remarks	 
	*/
    virtual void Clear();
protected:
	bool InitWnd( const IArgs & args );
	/**
	* ����:  �����������
	* @return  bool
	* @remarks  
	*/	
	bool OnEthnetSet( const IArgs& args );
	/**
	* ����:  ����᳡����
	* @return  bool
	* @remarks  
	*/
	bool OnCnsCfg( const IArgs& args );
	/**	 
	* ����:  ���ע�������
	* @return  bool
	* @remarks  
	*/
	bool OnRegService( const IArgs& args );

    /**	 
	* ����:  ���ע��GK
	* @return  bool
	* @remarks  
	*/
	bool OnRegGK( const IArgs& args );

    /**	 
	* ����:  ��� 
	* @return  bool
	* @remarks  
	*/
    bool OnSetTime( const IArgs& args );

	bool OnDualSrcCfg( const IArgs& args );

	bool OnSysStandBy( const IArgs& args );

	bool OnNetManageCfg( const IArgs& args );

	/**
	* ����:  ���������������ַ
	* @return  bool
	* @remarks  
	*/
	bool OnUpdService( const IArgs& args );

	/**
	* ����:  ������з���������
	* @return  bool
	* @remarks  
	*/
	bool OnCallServerCfg( const IArgs& args );
	
    /*
     *	���ܣ����������־
     *	@return  bool
     *	@remarks 
     */
    bool OnSaveLog( const IArgs& args );

	bool OnOpenSysList( const IArgs& args );

	void InitCfgList();

	bool OnCloseDlg( const IArgs& args );
private:
	static CSysCfgLogic *m_pCfgLogic;

//	static const String m_strEthnetCfg;          
    static const String m_strCnsCfg;
	static const String m_strRegService;
    static const String m_strRegGK;
    static const String m_strSysTem;
    static const String m_strSaveLog;
	static const String m_strDualSrcCfg;
	static const String m_strSysStandBy;
	static const String m_strNetManageCfg;
	static const String m_strUpdService;
	static const String m_strCallServerCfg;
};

#endif // !defined(AFX_SYSCFGLOGIC_H__D288469E_6B39_43F6_AC35_D46BA9372DEF__INCLUDED_)
