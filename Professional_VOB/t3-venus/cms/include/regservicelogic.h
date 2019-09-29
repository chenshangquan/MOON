// regservicelogic.h: interface for the CRegServiceLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REGSERVICELOGIC_H__D10945FA_EC6D_4756_A532_CCE144D9AED7__INCLUDED_)
#define AFX_REGSERVICELOGIC_H__D10945FA_EC6D_4756_A532_CCE144D9AED7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CRegServiceLogic : public CWndLogicBase 
{
public:
	CRegServiceLogic();
	virtual ~CRegServiceLogic();
	static CRegServiceLogic* GetLogicPtr();
	
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

protected:
	bool InitWnd( const IArgs & args );
	/**
	* 功能:  点击保存
	* @return  bool
	* @remarks  
	*/
	bool OnSave( const IArgs& args );
	/**	 
	* 功能:  点击取消
	* @return  bool
	* @remarks  
	*/
	bool OnCancel( const IArgs& args );
	/**	 
	* 功能:  点击编辑
	* @return  bool
	* @remarks  
	*/
	bool OnEdit( const IArgs& args );
	/**	 
	* 功能:  点击是否启用GK按钮
	* @return  bool
	* @remarks  
	*/
	bool BtnSwitchGkClick( const IArgs& args );

	bool OnSysCfg( const IArgs& args );

	bool OnCloseDlg( const IArgs& args );

	LRESULT UpdateSipCfg( WPARAM wParam, LPARAM lParam );
	LRESULT OnRegResultNty( WPARAM wParam, LPARAM lParam );
	LRESULT OnRegAliasRepeatNty( WPARAM wParam, LPARAM lParam );
	LRESULT UpdateGkCfg( WPARAM wParam, LPARAM lParam );
	LRESULT OnRegRsp( WPARAM wParam, LPARAM lParam );
	LRESULT OnCallServiceInfoNty( WPARAM wParam, LPARAM lParam );
	LRESULT OnCallServerInfoInd( WPARAM wParam, LPARAM lParam );
	LRESULT OnUpdServiceIPNty( WPARAM wParam, LPARAM lParam );
	LRESULT OnUpdServiceIPInd( WPARAM wParam, LPARAM lParam );

private:
	void SetCallServerInfo( TTPCallSerInfo tCallSerInfo );
	bool GetCallServerInfo( TTPCallSerInfo& tCallSerInfo );
	string GetServiceIP();
	void SetServiceIP();

private:
	static CRegServiceLogic *m_pRegLogic;
	static String m_stBtnGkSwitch;
    static String m_strGkIP;
	TTPCallSerFormat m_tTPCallSerFormatMain;
	TTPCallSerFormat m_tTPCallSerFormatDual;
};

#endif // !defined(AFX_REGSERVICELOGIC_H__D10945FA_EC6D_4756_A532_CCE144D9AED7__INCLUDED_)
