// regservicelogic.h: interface for the CRegServiceLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REGKLOGIC_H__D10945FA_EC6D_4756_A532_CCE144D9AED7__INCLUDED_)
#define AFX_REGKLOGICLOGIC_H__D10945FA_EC6D_4756_A532_CCE144D9AED7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CRegGkLogic : public CWndLogicBase 
{
public:
	CRegGkLogic();
	virtual ~CRegGkLogic();
	static CRegGkLogic* GetLogicPtr();
	
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
	* ����:  �������
	* @return  bool
	* @remarks  
	*/
	bool OnSave( const IArgs& args );
	/**	 
	* ����:  ���ȡ��
	* @return  bool
	* @remarks  
	*/
	bool OnCancel( const IArgs& args );
	/**	 
	* ����:  ����༭
	* @return  bool
	* @remarks  
	*/
	bool OnEdit( const IArgs& args );

    bool BtnSwitchGkClick( const IArgs& args );

	bool OnSysCfg( const IArgs& args );

	bool OnCloseDlg( const IArgs& args );

	LRESULT UpdateGkCfg( WPARAM wParam, LPARAM lParam );
	LRESULT OnRegRsp( WPARAM wParam, LPARAM lParam );
private:
	static CRegGkLogic *m_pRegLogic;
    static String m_stBtnGkSwitch;
    static String m_strGkIP;

};

#endif // !defined(AFX_REGSERVICELOGIC_H__D10945FA_EC6D_4756_A532_CCE144D9AED7__INCLUDED_)
