/*****************************************************************************
文件实现功能: 基于DUI的dialog类
文件名      : DUIDialog.h 
相关文件    : UIlib.h
备注		: 基本的Dialog类，可以根据需要在此基础上通过子类的形式继续扩充 
作者        : 俞锦锦
版本        : V1.0  Copyright(C) 2013-2014 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/3/28      1.0         俞锦锦      创建
******************************************************************************/

#pragma once

  
 

class CDUIDialog: public CWindowWnd, public INotifyUI,public IDialogBuilderCallback, public IMessageFilterUI
{

public:
	/*****************************************************************************
	* 功能: 设置Dialog是否失去焦点就隐藏
	* @param [in]  bStatus  ：TRUE 表示失去焦点就隐藏，否则不隐藏  
	* @return      void 
	* @remarks	 
	-----------------------------------------------------------------------------
	修改记录:
	日  期         版本        修改人      修改内容
	2013/4/9       1.0         俞锦锦      创建
    ******************************************************************************/
	void SetAutoHideStatus( BOOL bStatus ){ m_bAutoHide = bStatus; } 

 
	
	/*****************************************************************************
	* 功能: 调用方案
	* @param [in]  szCaseName  方案名 
	* @return   成功返回  TRUE，失败返回FALSE
	* @remarks	若未创建，则创建出来
	-----------------------------------------------------------------------------
	修改记录:
	日  期         版本        修改人      修改内容
	2013/5/2       1.0         俞锦锦      创建
    ******************************************************************************/
	BOOL DoCase( const LPCTSTR szCaseName  );

public:
	CDUIDialog(LPCTSTR szLayXml);
	~CDUIDialog(void); 
	

	
	virtual UINT GetClassStyle() const;

	virtual void Init();

	//创建自定义控件类型  IDialogBuilderCallback
	virtual CControlUI* CreateControl(LPCTSTR pstrClass); 
	 

	virtual void OnFinalMessage(HWND hWnd);
	
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

 
	//添加失去焦点就隐藏功能
	virtual LRESULT OnActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnMouseWheel(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
 

	virtual LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);	

	virtual LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	//INotifyUI
	virtual void Notify(TNotifyUI& msg);

	//IMessageFilterUI            preTranslateMessage()
	virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

	//winPorc
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	//处理用户自定义消息 
	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

protected:

	//CWindowWnd
	virtual LPCTSTR GetWindowClassName() const { return _T("DUIDialog"); }


protected:
	 
	  tstring m_strLayFile; //当前dlg对应的xml文件
 

protected:
	CPaintManagerUI m_paintMng;
	BOOL            m_bAutoHide;
};

