 
/*****************************************************************************
模块名      : CMS控制台
文件名      : toolMenuLogic.h
相关文件    : 
文件实现功能:  主设置菜单dlg
说明       ：包含：会议管理，系统设置，登出，关闭会议室电源和关机 5个设置项
作者        : 俞锦锦
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2011/5/24  1.0          俞锦锦      创建
******************************************************************************/

#if !defined(AFX_TOOLMENULOGIC_H__58E085DD_3999_4E94_9521_DE2D3B5B49AC__INCLUDED_)
#define AFX_TOOLMENULOGIC_H__58E085DD_3999_4E94_9521_DE2D3B5B49AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "wndLogicBase.h"
class CToolMenuLogic :public CWndLogicBase 
{

public:  
	static CToolMenuLogic* GetLogicPtr(); 
	CToolMenuLogic();
	virtual ~CToolMenuLogic();
public:  
	
	virtual bool RegCBFun();
	
	virtual bool UnRegFunc( );
	
    virtual bool InitWnd( const IArgs & arg );
  
    /**	 
	* 功能:  清空所有状态和数据
	* @return   
	* @remarks	 
	*/
    virtual void Clear();

    /**	 
  * 功能:  会议管理
  * @return   bool
  * @remarks  
  */
	bool BtnMeetingManageClick( const IArgs & arg );
	
    /**	 
    * 功能:  会场管理button
    * @return   bool
    * @remarks  
    */
    bool BtnCnsManageClick( const IArgs & arg );
  

    bool BtnSystemSetClick( const IArgs & arg );
  
    /**	 
    * 功能: 关机button
    * @return   bool
    * @remarks  
    */
    bool BtnShutDownClick( const IArgs & arg );
    
    bool ShutDown( const IArgs & arg );

   /**	 
    * 功能: 登出button
    * @return   bool
    * @remarks  
    */
    bool BtnLogoutClick( const IArgs & arg );

    
    bool DisConnect( const IArgs & arg );


    bool BtnHideToolBarClick( const IArgs & arg );
    
    /**	 
    * 功能:  关闭界面
    * @return   bool
    * @remarks  
    */ 
    bool CloseDlg( const IArgs & arg  );
 

    bool BtnSaveToFileClick( const IArgs & arg );


    bool BtnMinmizeClick( const IArgs & arg );


    bool OnBtnExitClick( const IArgs & arg );
  
    bool ExitCmc( const IArgs & arg );


    bool OnBtnCenterCtrl( const IArgs & arg );

    bool OnWndHide( const IArgs & arg );


    /**	 
    * 功能:  更新设置菜单界面
    * @return   
    * @remarks 管理员用户需要显示：会议管理、系统配置 按钮	  
    */
    void UpdateDlg();
protected: 
	virtual void RegMsg(); 
	virtual void UnRegMsg();

	HRESULT OnDisConnect( WPARAM wparam, LPARAM lparam );
    HRESULT OnMainMenuClickToolBtn( WPARAM wparam, LPARAM lparam );
     
private:
	BOOL  m_bFirstShow;  //如果是第一次显示，则需要使用 UpdateDlg
    static CToolMenuLogic *m_pLogic;  


	static const String  m_strBtnConfManage ;  ///<会议管理
	static const String  m_strBtnSysSet ;           ///<系统设置
	static const String  m_strBtnLogoff  ;          ///<登出
	static const String  m_strBtnPowerdown  ;  ///<关闭会议室电源
	static const String  m_strBtnShutdown ;     ///<关机
};

#endif // !defined(AFX_TOOLMENULOGIC_H__58E085DD_3999_4E94_9521_DE2D3B5B49AC__INCLUDED_)
