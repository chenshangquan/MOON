// NetManageCfgLogic.h: interface for the CNetManageCfgLogic class.
//
//////////////////////////////////////////////////////////////////////

/*****************************************************************************
模块名      : CNetManageCfgLogic
文件名      : NetManageCfgLogic.h
相关文件    : 
文件实现功能: 网管配置页面
作者        : 吴蒨蒨
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/1/10      1.0         吴蒨蒨		创建
******************************************************************************/

#if !defined(AFX_NETMANAGECFGLOGIC_H__C0A57808_4F6C_4277_91BF_CFECDE2575A7__INCLUDED_)
#define AFX_NETMANAGECFGLOGIC_H__C0A57808_4F6C_4277_91BF_CFECDE2575A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

#define MIN_NMSERVER_NO		0
#define MAX_NMSERVER_NO		1

class CNetManageCfgLogic : public CWndLogicBase  
{
public:
	virtual ~CNetManageCfgLogic();
	static CNetManageCfgLogic* GetLogicPtr();

	public:
	/**	 
	* 功能:  注册该logic中所有的回调函数
	* @return  void
	* @remarks	在此注册的回调函数主要是控件的响应事件，多为成员回调函数,也可注册其他的回调函数
	                    注册时，应注意回调函数对应名子的命名规则："类名::函数名"
	*/
	virtual bool RegCBFun();

	/**	 
	* 功能:  注销某回调函数
	* @return  void
	* @remarks	 
	*/
	virtual bool UnRegFunc();

	/**	 
	* 功能:  注册要处理的消息
	* @return  void
	* @remarks	 注册后该消息才能发送到本逻辑模块，否则，接收不到该消息
	*/
	virtual void RegMsg();

	/**	 
	* 功能:  注销某回调函数
	* @return  void
	* @remarks	 
	*/
	virtual void UnRegMsg();
	
    /**	 
	* 功能:  清空所有状态和数据
	* @return    
	*/
    virtual void Clear();

	/**	 
	* 功能:  初始化窗口数据,
	* @return  void
	* @remarks	由于该功能被归属到控件属性并在xml中与控件绑定，
	                    需要在RegCBFun()中注册到回调函数管理模块 
	*/
	bool InitWnd( const IArgs & args );

protected:

	CNetManageCfgLogic();
	/**	 
	* 功能:  点击系统设置的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnSysCfg( const IArgs & args );
    
	bool OnBtnNetManageCfg( const IArgs & args );
    /**	 
	* 功能:  点击新建网管的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnAddNetManage( const IArgs & args );

    /**	 
	* 功能:  点击删除按钮的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnDelete( const IArgs & args );

    /**	 
	* 功能:  点击列表条目响应函数
	* @return   bool
	* @remarks	 
	*/
    bool OnClickWebManageItem( const IArgs & args );

    bool OnBtnEdit( const IArgs & args );

    bool OnBtnSave( const IArgs & args );

    bool OnBtnCancel( const IArgs & args );

	HRESULT OnAddNetMngRsp( WPARAM wparam, LPARAM lparam );

	/**	 
	* 功能:  响应服务器发来的UI_CNS_NETMNG_NTY的函数
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnNetMngNty( WPARAM wparam, LPARAM lparam );

	/**	 
	* 功能:  响应服务器发来的UI_CNS_MODIFY_NETMNG_RSP的函数
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnModifyNetMngRsp( WPARAM wparam, LPARAM lparam );

	/**	 
	* 功能:  响应服务器发来的UI_CNS_DEL_NETMNG_RSP的函数
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnDelNetMngRsp( WPARAM wparam, LPARAM lparam );

 
private:	
    static CNetManageCfgLogic *m_pLogic;

    //逻辑单元对应的所有控件名
	static const String m_strListNetMng;
	static const String m_strNMServerIp;
	static const String m_strNMReadCommunity;
	static const String m_strNMWriteCommunity;
	static const String m_strNMGetSetPort;
	static const String m_strNMTrapPort;
	static const String m_strBtnAdd;
	static const String m_strBtnDel;
	static const String m_strBtnModify;
	static const String m_strSchmEdit;

	//网管操作类型
	EM_NETMNGOPT_TYPE m_emNMType;

	//当前选中的网管服务器信息
	TTPNMServerCfg m_tTPNMServerCfgSel;

    //当前界面显示的网管服务器信息
	TTPNMServerCfg m_tTPNMServerCfgCur;

	//新增网管的序列号
	u16 m_wCurretNO;

private:
	/**	 
	* 功能:  更新Btn状态
	* @return   void
	* @remarks	 
	*/
	void UpdateBtnState();

	/**	 
	* 功能:  更新网管信息
	* @return   void
	* @remarks	 
	*/
	void SetAllCtrl( TTPNMServerCfg &tTPNMServerCfg );

	/**	 
	* 功能:	 设置网关配置详情页的默认值
	* @return   void
	* @remarks	 
	*/
	void SetAllInitCtrl();

	/**	 
	* 功能:  将所有控件的值读取到tTPNMServerCfg
	* @return   bool : 表示读取值是否有错误
	* @remarks	 
	*/
	bool GetAllCtrl( TTPNMServerCfg &tTPNMServerCfg );

    /**	 
	* 功能:  将当前所有控件的UI显示值读取到tTPNMServerCfg
	* @return  
	* @remarks	 
	*/
	void GetCurrentCtrl();

	/**	 
	* 功能:  响应UI_CNS_MSG_NETMNGSELDATA_Click的函数
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnNetMngSelData( WPARAM wparam, LPARAM lparam );

};

#endif // !defined(AFX_NETMANAGECFGLOGIC_H__C0A57808_4F6C_4277_91BF_CFECDE2575A7__INCLUDED_)
