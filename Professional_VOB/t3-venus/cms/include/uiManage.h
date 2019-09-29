 
/*****************************************************************************
模块名      : CMS控制台
文件名      : uiManage.h
相关文件    : 
文件实现功能: UI模块的管理，其中封装了cms中需要的UIFactoryLib的接口，同时也添加了cms中需要用的控件
作者        : 俞锦锦
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2011/5/24  1.0          俞锦锦      创建
******************************************************************************/

#if !defined(AFX_UIMANAGE_H__A30C96E8_214E_4915_83D0_C0AF9B2BFF8A__INCLUDED_)
#define AFX_UIMANAGE_H__A30C96E8_214E_4915_83D0_C0AF9B2BFF8A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#pragma warning (disable: 4786) 
#pragma warning (disable: 4503) 


//----uifactoryLib------ 

#include "valueSet.h"

#include "MfcDefaultWndProperty.h"


 
 
#define HANDLE_ERROR ( CUiManage::HandleErr )  

#define HANDLE_ERROR_NOW(p)\
{\
	CUiManage::HandleErr(p, "", TRUE);\
}

 

class CUiManage  
{
 
public:
/** @defgroup  CUiManage  (UI模块的管理，其中封装了cms中需要的UIFactoryLib的接口，同时也添加了cms中需要用的控件)
 *  @{
 */ 

    static CUiManage* GetUiManagePtr();

/** @defgroup   窗口属性部分
 *  @{
 */
    void UpdateUI(   IWndTree* pWndTree );
  
    void UpdateUI( String strWndName,   IWndTree* pWndTree = NULL);
  /**	 
	* 功能:  显示/隐藏某个窗口
	* @param [in]  strWndName  窗口名
	* @param [in]  bShow  是否要显示 
	* @param [in]  bReDraw  是否重绘
	* @return  u16 成功返回0;失败返回非0错误码
	* @remarks	 
	*/
	u16 ShowWindow( String strWndName, bool bShow = true,const IWndTree* pWndTree = NULL, BOOL bReDraw = TRUE );

   /**	 
	* 功能:  获取domodal的窗口
	* @param [in]  strWndName  窗口名 
	* @return   成功返回Window指针;失败返回NULL
	* @remarks	 
	*/
	Window* GetModalWnd( String strWndName );
	
 


	/**  获取控件信息 
	 *  @param[in] strName 控件名称
	 *  @param[in] pWndTree 控件树 
	 *  @return 控件信息
	 *  @remarks 若控件中含有“/” 则会按照分隔符处理
	 */ 
   const IWndTree* GetWindow( String strName, const IWndTree* pWndTree = NULL )  ;
	

   	/**  获取控件信息
	 *  @param[in] pWnd 窗口指针
	 *  @param[in] pWndTree 所要遍历的树
	 *  @return 返回搜索到的窗口
	 */
    const IWndTree* GetWindow( Window* pWnd, const IWndTree* pWndTree );


	/**  获取控件指针 
	 *  @param[in] strName 控件名称
	 *  @param[in] pWndTree 控件树 
	 *  @return 控件信息
	 *  @remarks 若控件中含有“/” 则会按照分隔符处理
	 */ 
	Window* GetWindowPtr( String strName, const IWndTree* pWndTree = NULL );

     /**	 
	* 功能:  把启用方案
	* @param [in] strSchemeName 方案名
    * @param [in] String strWndName 启用该方案的窗口名
    * @param[in] pWndTree 窗口所在的控件树 
	* @return   
	* @remarks	   
	*/
   bool LoadScheme( String strSchemeName, IWndTree* pWndTree = NULL , String strWndName = "", bool bInvalidate = true );

	 /**	 
	* 功能:  设置某控件属性值
	* @param [in]  strWndName  窗口名
	* @param [in]  value 要设置的属性信息 
	* @param[in] pWndTree 控件所在的树
	* @return  bool 成功返回true;失败返回false
	* @remarks	 若控件中含有“/” 则会按照分隔符处理
	*/
 	bool SetPropertyValue( const IValue& value,   String strWndName, const IWndTree* pWndTree = NULL );

	 /**	 
	* 功能:  获取某控件属性值
	* @param [in&out]  IValue  要获取的属性信息
	* @param [in]  window  要获取的属性的窗口指针
	* @param [in]  strWndType  要获取的属性的窗口类型
	* @return  bool 成功返回true;失败返回false
	* @remarks	 
	*/
    bool SetPropertyValue( const IValue& value, const Window* window,  const String& strWndType );


   	 /**	 
	* 功能:  获取某控件属性值
	* @param [in&out]  IValue  要获取的属性信息
	* @param [in]  strWndName  窗口名 
	* @param[in] pWndTree 控件所在的树
	* @return  bool 成功返回true;失败返回false
	* @remarks	 若控件中含有“/” 则会按照分隔符处理
	*/
	bool GetPropertyValue( IValue& value, String strWndName, const IWndTree* pWndTree = NULL);

	 /**	 
	* 功能:  获取某控件属性值
	* @param [in&out]  IValue  要获取的属性信息
	* @param [in]  window  要获取的属性的窗口指针
	* @param [in]  strWndType  要获取的属性的窗口类型
	* @return  bool 成功返回true;失败返回false
	* @remarks	 
	*/
 	bool GetPropertyValue( IValue& value, const Window* window,  const String& strWndType );

	/**	 
	* 功能:  设置控件是否可用
	* @param [in]  strWndName  控件名
	* @param [in]  bEnable  状态
	* @param [in]  pWndTree 控件树 
	* @return  bool 成功返回true;失败返回false
	* @remarks	 
	*/
	bool EnableWindow( String strWndName, bool bEnable = true, const IWndTree* pWndTree = NULL );

	/**	 
	* 功能:  设置控件标题
	* @param [in]  strWndName  控件名
	* @param [in]  strCaption  标题
	* @param [in]  pWndTree 控件树 
	* @param [in]  bReDraw  是否重绘 
	* @return  bool 成功返回true;失败返回false
	* @remarks	 
	*/
	bool SetCaption( String strWndName, String strCaption, const IWndTree* pWndTree = NULL, BOOL bReDraw = FALSE );

	/**	 
	* 功能:  获取控件标题
	* @param [in]  strWndName  控件名
	* @param [out] strCaption  标题
	* @param [in]  pWndTree 控件树 
	* @return  bool 成功返回true;失败返回false
	* @remarks	 
	*/
	bool GetCaption( String strWndName, String& strCaption, const IWndTree* pWndTree = NULL );

	/**	 
	* 功能:  设置焦点
	* @param [in]  strWndName  控件名
	* @param [in]  pWndTree 控件树 
	* @return  bool 成功返回true;失败返回false
	* @remarks	 
	*/
	bool SetFocus( String strWndName, const IWndTree* pWndTree = NULL );

	/**	 
	* 功能:  设置Button Check状态
	* @param [in]  strWndName  控件名
	* @param [in] nCheckState  状态
	* @param [in]  pWndTree 控件树 
	* @return  bool 成功返回true;失败返回false
	* @remarks	 
	*/
	bool SetCheckState( String strWndName, int nCheckState, const IWndTree* pWndTree = NULL );

	/**	 
	* 功能:  设置SwitchButton Check状态
	* @param [in]  strWndName  控件名
	* @param [in]  bState  状态
	* @param [in]  pWndTree 控件树 
	* @return  bool 成功返回true;失败返回false
	* @remarks	 
	*/
	bool SetSwitchState( String strWndName, bool bState, const IWndTree* pWndTree = NULL );

	/**	 
	* 功能:  获取SwitchButton Check状态
	* @param [in]  strWndName  控件名
	* @param [out] bState  状态
	* @param [in]  pWndTree 控件树 
	* @return  bool 成功返回true;失败返回false
	* @remarks	 
	*/
	bool GetSwitchState( String strWndName, bool& bState, const IWndTree* pWndTree = NULL );

   	/**	 
	* 功能:  查看控件是否显示
	* @param [in]  strWndName  控件名 
	* @param [in]  pWndTree 控件树 
	* @return  bool 显示返回true;未显示返回false
	* @remarks	 
	*/
	bool IsVisible( String strWndName, const IWndTree* pWndTree = NULL );

	/**	 
	* 功能:  设置Dlg图片
	* @param [in]  strWndName  控件名
	* @param [in]  strPath  图片路径
	* @param [in]  pWndTree 控件树 
	* @return  bool 成功返回true;失败返回false
	* @remarks	 
	*/
	bool SetTransparentDlgImage( String strWndName, String strPath, const IWndTree* pWndTree = NULL );

	/**	 
	* 功能:  设置DragButton Sel状态
	* @param [in]  strWndName  控件名
	* @param [out] bState  状态
	* @param [in]  pWndTree 控件树 
	* @return  bool 成功返回true;失败返回false
	*/
	bool SetSelState( String strWndName, bool bState, const IWndTree* pWndTree = NULL );

	/**	 
	* 功能:  获取DragButton Sel状态
	* @param [in]  strWndName  控件名
	* @param [out] bState  状态
	* @param [in]  pWndTree 控件树 
	* @return  bool 成功返回true;失败返回false
	*/
	bool GetSelState( String strWndName, bool& bState, const IWndTree* pWndTree = NULL );

	/**	 
	* 功能:  设置DragButton Online状态
	* @param [in]  strWndName  控件名
	* @param [out] bOnline  状态
	* @param [in]  pWndTree 控件树 
	* @return  bool 成功返回true;失败返回false
	*/
	bool SetDragBtnOnline( String strWndName, bool bOnline, const IWndTree* pWndTree = NULL );   
/**@} */  //窗口属性处理部分

  
  /**	 
	* 功能:  处理windows消息
	* @param [in]  pMsg 要处理的消息信息
	* @return  bool 成功返回true;失败返回false
	* @remarks	在uifactroy内部查找注册过该消息的处理函数 对该消息做出响应
	*/
	bool HandleMsg( WindowMsg* pMsg );

 

     /**  隐藏所有窗口
 *  @param[in]  
 *  @return 是否隐藏成功
 */
    bool HideAllWindow();
   

   	/**	 
	* 功能:  销毁窗口	 
	* @param [in]  strWndName 要销毁的窗口名
	* @return  u16 成功返回0，失败返回错码
	* @remarks	   
	*/ 
	u16 DestroyWindow( String strWndName );


	/**  销毁窗口，这里会调用CWnd的Destory
   *  @param[in] pWnd 窗口指针
   *  @return 是否销毁成功
  */
	bool DestoryWnd( Window* pWnd );


  /**  销毁窗口，这里会调用CWnd的Destory
  *  @param[in] pWndTree 窗口树
  *  @return 是否销毁成功
 */
	bool DestoryWnd( IWndTree* pWndTree );


 
/**@} */  //wnd管理部分
   
   	/**	 
	* 功能:  把窗口风格的改变记录到文件中 
	* @param [in]   String strWndName窗口名
    *  @param[in] strSavePropertyName 要保存的属性名
    *  @param[in] bForceSave 如果要保存的属性不在当前方案中，是否强制保存
	* @return   
	* @remarks	   
	*/
   bool  SaveToFile( String strWndName, string strSaveWndName = "" ,string strSavePropertyName = "" , BOOL bForceSave = FALSE );
 
   String GetImagePath();

   static void HandleErr( DWORD dwErrID, CString strMsp = "", BOOL bShowNow = FALSE );


   vector<TConfMenuInfo> *GetConfMenu(){ return &m_vctConfMenu ; }
   
   BOOL SaveConfMenu( vector<TConfMenuInfo> & lst ); 
 
   BOOL UpdateConfMenuAccordFile( );
private:
   IWndTree * m_pRoot;

/** @}*/ 

public:   
	virtual ~CUiManage();
private:
	CUiManage();
	static void InitWndName();

private:
    static CUiManage* m_pStMySelf;
    vector<TConfMenuInfo> m_vctConfMenu;

};


#define UIManagePtr CUiManage::GetUiManagePtr()

//所有窗口名定义
extern const String g_stcStrLoginDlg;
extern const String g_stcStrMsgBox;
extern const String g_stcStrMainFrameDlg;
extern  const String g_stcStrMainMenuDlg;
extern  const String g_stcStrToolMenuDlg;
extern  const String g_stcStrSimulateCns1Dlg;			///<一屏模拟会场
extern  const String g_stcStrSimulateCns3Dlg;			///<三屏模拟会场
extern  const String g_stcStrSimulateCns5Dlg;			///<五屏模拟会场  
extern  const String g_stcStrLockScreenDlg;			     ///<锁屏界面
extern  const String g_stcStrAddrbookDlg;				 ///<地址簿
extern  const String g_stcStrAddrEditDlg;
extern  const String g_stcStrConftempDlg;				 ///<会议模板列表
extern  const String g_stcStrCnsLstDlg;                     ///<会场列表
extern  const String g_stcStrCallDlg;                         ///<呼叫
extern  const String g_stcStrConfCnsCtrlDlg;            ///会议中cns的控制界面
extern  const String g_stcStrVolumCtrlDlg;
extern  const String g_stcStrAudMixDlg;                   ///<混音界面
extern  const String g_stcStrTvwDlg;                         ///<电视墙界面
extern  const String g_stcStrConftempEdtDlg ;          ///<会议模板编辑界面
extern  const String g_stcStrConfInfoDlg ;                ///<会议信息界面
extern  const String g_stcStrTitleBarDlg ;                ///<标题栏
extern  const String g_stcStrUserManageDlg ;                ///<用户管理界面
extern  const String g_stcStrUserdefinedDlg ;                ///<用户自定义界面
extern  const String g_stcStrHungupConfPopDlg ;      //会议列表中挂断会议弹出框
extern  const String g_stcStrAlarmInfoDlg;
extern  const String g_stcStrIpCfgDlg;
extern  const String g_stcStrConnectCnsDlg;
extern  const String g_stcStrLoginFrame;
extern  const String g_stcStrVideoDlg;
extern  const String g_stcStrFuncLstManageMenu;            //菜单列表管理的菜单
extern  const String g_stcStrScrnDisplayMenu;            //屏选看菜单
extern  const String g_strSaveLogDlg;                    //Log download 界面
extern  const String g_strWaitingRefreshDlg;
extern  const String g_strDualSrcDlg;
extern  const String g_strSysStandBy;
extern  const String g_strNetManageCfg;
extern  const String g_strAddrShowOptnDlg;

//scheme
extern  const String g_schmMainMenuConfManage;            //mainMenu 的会议管理对应的菜单项 
extern  const String g_schmMainMenuCnsManageInconfBase ;     //mainMenu 的会议中会场的基本操作
extern  const String g_schmMainMenuCnsManageInconf;          //mainMenu 的会议中会场的所有会控操作
extern  const string g_schmSimScrPtpConf;                   //模拟屏点对点会议方案
extern  const string g_schmSimScrMiltConf;                   //模拟屏多点会议方案
extern  const String g_schmMainMenuSysManage ;                //mainMenu 的系统管理对应的菜单项
extern  const String g_schmMainMenuCnsManage ;                //mainMenu 的会场管理菜单

extern  const String g_schmMainMenuDisableVideoBtn ;                //mainMenu  禁用videobutton
extern  const String g_schmMainMenuEnableVideoBtn ;                //mainMenu 用videobutton

extern  const String g_stcStrCallingBox ;                   //呼叫过程中的动画dlg

extern  const String g_schmMainFrameCnsBkg;                           //模拟会场背景
extern  const String g_schmMainFrameBlankBkg ;                          //空白背景

extern  const String g_strMainFrameSimulateBkg;
extern  const String g_strMainFrameSysCfgBkg;                        //系统配置的背景
extern  const String g_strMainFrameConfManageBkg;                    //会议管理的背景
extern  const String g_strMainFrameLoginBkg;    

extern const String g_strFuncLstData;                      //功能列表对应的数据 xml

              
 
#endif // !defined(AFX_UIMANAGE_H__A30C96E8_214E_4915_83D0_C0AF9B2BFF8A__INCLUDED_)
