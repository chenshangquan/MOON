 /*****************************************************************************
模块名      : CMS控制台
文件名      : MainWndLogic.h
相关文件    : 
文件实现功能: 主窗口逻辑单元 
说明       ： 其对应的xml中包含主框架dlg、主菜单dlg （地址簿，会议模板列表，会议讨论，电视墙管理 ，工具箱，锁屏）
作者        : 俞锦锦
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2011/5/24  1.0          俞锦锦      创建
******************************************************************************/

#if !defined(AFX_MAINWNDLOGIC_H__336C3B31_4484_4F36_9B80_1BA09DB004FA__INCLUDED_)
#define AFX_MAINWNDLOGIC_H__336C3B31_4484_4F36_9B80_1BA09DB004FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"


class CMainFrameLogic :public CWndLogicBase//, public CProcessMsgBase<CMainFrameLogic>// ,public Singleton<CMainFrameLogic>
{
public:   
	 static CMainFrameLogic*  GetLogicPtr();
     CMainFrameLogic();
	 virtual ~CMainFrameLogic();  
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

/**	 
  * 功能:  点击工具箱
  * @return  bool
  * @remarks  
  */
    bool BtnToolMenuClick( const IArgs & arg );
   
  /**	 
  * 功能:  点击锁屏
  * @return   bool
  * @remarks  
  */
    bool BtnLockScreenClick( const IArgs & arg );

   
    /**	 
  * 功能:  点击地址簿
  * @return   bool
  * @remarks  
  */
	bool BtnCnsManageClick( const IArgs & arg );


/**	 
  * 功能:  点击地址簿
  * @return   bool
  * @remarks  
  */
	bool BtnAddrbookClick( const IArgs & arg );
 
   
 /**	 
  * 功能:  点击会议模板
  * @return   bool
  * @remarks  
  */
	bool BtnConftempClick( const IArgs & arg );
 
   
	/**	 
  * 功能:  点击会场列表
  * @return   bool
  * @remarks  
  */
	bool BtnCnsListClick( const IArgs & arg );


	/**	 
  * 功能:  点击会议讨论
  * @return   bool
  * @remarks  
  */
	bool BtnMixAudClick( const IArgs & arg );

/**	 
  * 功能:  点击电视墙
  * @return   bool
  * @remarks  
  */
	bool BtnTvwClick( const IArgs & arg );


 /**	 
  * 功能:  点击管理地址簿
  * @return   bool
  * @remarks  
  */
	bool BtnAddrbookManageClick( const IArgs & arg );


  /**	 
  * 功能:  点击会议模板编辑but
  * @return   bool
  * @remarks  
  */
	bool BtnConftempManageClick( const IArgs & arg );


 /**	 
  * 功能:  点击会议信息but
  * @return   bool
  * @remarks  
  */
    bool BtnConfInfoClick( const IArgs & arg );


	bool BtnSysCfgClick( const IArgs & arg );

    /**	 
  * 功能:  点击用户管理button
  * @return   bool
  * @remarks  
  */
    bool BtnUserManageClick( const IArgs & arg );


	/**	 
	* 功能:  点击自定义button
	* @return   bool
	* @remarks  
	*/
    bool BtnUserDefineClick( const IArgs & arg );

	/**	 
	* 功能:  点击告警button
	* @return   bool
	* @remarks  
	*/
	bool BtnAlarmClick( const IArgs & arg );

	/**	 
	* 功能:  把wnd属性的修改保存到文件
	* @return   bool
	* @remarks  
	*/
    bool BtnSaveToFileClick( const IArgs & arg );


    //显示码流图像界面
    bool BtnVideoClick( const IArgs & args );

	/**	 
	* 功能:  更新主菜单界面
	* @return   
	* @remarks 会议中需要把“会议模板列表按钮”转换为“会场列表按钮“，
			   同时"  电视墙管理"和“讨论组”两个button置为可用，
			   若不在会议中则把这两个button置灰禁用
	*/
	void UpdateMainMenuDlg();


    //刷新呼叫状态
    void  RefreshCallState();

	bool OnGrabLogin( const IArgs & arg );

	void UpdateAlarmImg();

    //挂断会议后（主动挂断以及ums重启）隐藏所以操作界面
    void HideAllDlg();
  

   
protected:

	virtual void RegMsg(); 
	virtual void UnRegMsg();
  
    void ShowVideo( BOOL32 bFullScreen );
private:
  
  
 /**	 
  * 功能:  创建模拟会场界面
  * @return   
  * @remarks  根据cns屏个数来选择相应的xml来创建
  */
   void CreateSimulateCnsDlg();

   void UpdateSimulateCnsDlg();

   /**	 
 arks  如果未连接，则返回到登陆界面
  */
   BOOL32 CheckLinkState();

   void  CreateWnd();

   void  InitConfMenu();

   void  UpdateConfMenu( EM_ConfType emConfType );
 
protected: 

	HRESULT OnStratConftempRsp( WPARAM wparam, LPARAM lparam);
	HRESULT OnInvitCnsRsp( WPARAM wparam, LPARAM lparam);
 
	HRESULT OnConfStateNotify( WPARAM wparam, LPARAM lparam );
    HRESULT OnHungupP2pConfNotify( WPARAM wparam, LPARAM lparam );
	HRESULT	OnCnsInfoNotify( WPARAM wparam, LPARAM lparam );
	HRESULT OnCnsOfflineNotify( WPARAM wparam, LPARAM lparam );
     
    HRESULT	OnRefreshConfLst( WPARAM wparam, LPARAM lparam );
    HRESULT	OnRefreshConfCnsLst( WPARAM wparam, LPARAM lparam );
    HRESULT OnHungupConf( WPARAM wparam, LPARAM lparam );
  
    //该账户已经在另一个地方登录
    HRESULT GrabLoginNotify( WPARAM wparam, LPARAM lparam );

    //呼叫动画显示 已达到5秒钟，主会场还未上线
    HRESULT CallingTimeOut( WPARAM wparam, LPARAM lparam );
    
    HRESULT OnShowAlarmNotify( WPARAM wparam, LPARAM lparam ); 
	
    HRESULT OnDualRecvStateNotify( WPARAM wparam, LPARAM lparam );

	HRESULT OnDualOffLineNotify( WPARAM wparam, LPARAM lparam );

    HRESULT OnDualRcvInterruptNotify( WPARAM wparam, LPARAM lparam );

	HRESULT OnCnsLeaveConfNotify( WPARAM wparam, LPARAM lparam );

    HRESULT OnCentreSleepNotify( WPARAM wparam, LPARAM lparam );

    //UMS发过来的错误消息提示
    HRESULT OnUmsReasonInd( WPARAM wparam, LPARAM lparam );

    //TPad Home键响应
    HRESULT OnTPadHomeKeyNotify( WPARAM wparam, LPARAM lparam );

private:
	//该逻辑单元对应的所有窗口名 
	static const String  m_strBtnConftempLst ;  ///<会议模板列表
	static const String  m_strBtnCnsLst ;           ///<会议的会场列表
	static const String  m_strBtnAddrbook ;      ///< 地址簿
    static const String  m_strBtnAddrbookMng ;      ///< 地址簿管理
	static const String  m_strBtnLockScreen;     ///< 锁屏
    static const String  m_strBtnToolMenu;        ///<设置按钮菜单栏 ，用于弹出或者隐藏设置对话框
    static const String  m_strBtnMixaud  ;
    static const String  m_strBtnTvw ;
	static const String  m_strBtnAlarm;
	static const String  m_strDlgConfManageMenu;
	static const String  m_strBtnPrePage;
	static const String  m_strBtnNextPage;
	static const String  m_strConfManageList;
    static const String  m_strBtnVideo;
    static CMainFrameLogic *m_pLogic;
    
	BOOL32               m_bAlarmOn; 	
	EM_ConfType          m_emConfType;    

};



#endif // !defined(AFX_MAINWNDLOGIC_H__336C3B31_4484_4F36_9B80_1BA09DB004FA__INCLUDED_)
