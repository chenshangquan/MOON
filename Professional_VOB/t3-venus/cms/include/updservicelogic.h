/*****************************************************************************
模块名      : CUpdServiceLogic
文件名      : updservicelogic.h
相关文件    : 
文件实现功能: 升级服务器地址
作者        : 石城
版本        : V1.0  Copyright(C) 2013-2014 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/3/18      1.0         石城			创建
******************************************************************************/
#if !defined(UMC_UPDSERVICELOGIC_H)
#define UMC_UPDSERVICELOGIC_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CUpdServiceLogic : public CWndLogicBase 
{
public:
	CUpdServiceLogic();
	virtual ~CUpdServiceLogic();
	static CUpdServiceLogic* GetLogicPtr();
	
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
	* 功能:  点击系统设置
	* @return  bool
	* @remarks  
	*/
	bool OnSysCfg( const IArgs& args );

	/**	 
	* 功能:  点击编辑
	* @return  bool
	* @remarks  
	*/
	bool OnEdit( const IArgs& args );

	/**	 
	* 功能:  点击取消
	* @return  bool
	* @remarks  
	*/
	bool OnCancel( const IArgs& args );

	/**
	* 功能:  点击保存
	* @return  bool
	* @remarks  
	*/
	bool OnSave( const IArgs& args );

	bool OnCloseDlg( const IArgs & arg );

	LRESULT OnUpdServiceIPNty( WPARAM wParam, LPARAM lParam );
	LRESULT OnUpdServiceIPInd( WPARAM wParam, LPARAM lParam );

private:
	String GetServiceIP();
	void SetServiceIP();
	bool CheckServiceIP( String strServiceIP );

private:
	static CUpdServiceLogic *m_pLogic;
};

#endif // !defined(UMC_UPDSERVICELOGIC_H)
