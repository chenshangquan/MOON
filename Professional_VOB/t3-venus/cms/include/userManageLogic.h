// userManageLogic.h: interface for the CUserManageLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USERMANAGELOGIC_H__0720ED96_4DB3_48DD_8F13_8753E6FDA4D4__INCLUDED_)
#define AFX_USERMANAGELOGIC_H__0720ED96_4DB3_48DD_8F13_8753E6FDA4D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

/*
1.SchmShowUserLst :显示用户列表界面，同时 title切换为“用户管理”，btn "用户配置"显示，“新建用户”显示，其他界面隐藏
2.SchmShowUserInfo :显示用户信息界面, 同时 title切换为“用户信息”，btn "用户管理"显示，“编辑”显示 
3.SchmEdtUser: 用户信息界面显示为 可编辑的， 同时 title切换为“编辑用户信息”，btn "保存"显示，“取消”显示  
*/

enum EmModifyUserType{
    emModifyTpCheck,                  //查看
    emModifyTpNew,                  //新建用户
    emModifyTpUpdate,               //编辑已有用户
    emModifyManager,
};

class CUserManageLogic : public CWndLogicBase  
{ 
public:  
    static CUserManageLogic* GetLogicPtr(); 
    CUserManageLogic();
    virtual ~CUserManageLogic();
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
    * 功能:  点击了转到用户配置界面的button
    * @return   bool
    * @remarks  
    */  
    bool BtnToUserConfigClick( const IArgs & arg );



    /**	 
    * 功能:  点击了新建用户的button
    * @return   bool
    * @remarks  
    */  
    bool BtnToNewUserClick( const IArgs & arg );



     /**	 
    * 功能:  点击了编辑用户的button
    * @return   bool
    * @remarks  
    */  
    bool BtnToEdtClick( const IArgs & arg );


     /**	 
    * 功能:  点击了保存用户信息的btn
    * @return   bool
    * @remarks  
    */  
    bool BtnToSaveClick( const IArgs & arg );



     /**	 
    * 功能:  点击了取消编辑用户信息的btn
    * @return   bool
    * @remarks  
    */  
    bool BtnToCancleClick( const IArgs & arg );




     /**	 
    * 功能:  点击了删除用户信息的btn
    * @return   bool
    * @remarks  
    */  
    bool BtnToDeleteClick( const IArgs & arg );



    /**	 
    * 功能:  点击了用户配置item
    * @return   bool
    * @remarks  
    */  
    bool OnUserConfigItemIcon( const IArgs & arg );

    bool OnUserConfigItem( const IArgs & arg );

     /**	 
    * 功能:  点击了用户list item上的图标
    * @return   bool
    * @remarks  
    */  
    bool OnUserLstItemIcon( const IArgs & arg );

    bool OnUserLstItem( const IArgs & arg );


    /**	 
    * 功能:  点击了显示用户列表的图标
    * @return   bool
    * @remarks  
    */  
    bool ToUserLstIconClick( const IArgs & arg );




    /**	 
    * 功能:  点击了显示用户信息的图标
    * @return   bool
    * @remarks  
    */  
    bool ToUserInfoIconClick( const IArgs & arg );


     /**	 
    * 功能:  保存界面信息
    * @return   bool
    * @remarks  
    */  
    bool BtnSaveToFileClick( const IArgs & arg );

    bool  OnPswdEdtSetFocus( const IArgs & arg );
protected: 
    virtual void RegMsg(); 
    virtual void UnRegMsg();
    
    HRESULT OnUserRefreshNotify( WPARAM wparam, LPARAM lparam );
    HRESULT OnUserModifyRsp( WPARAM wparam, LPARAM lparam );
   
    void  InitConfigLst();
    void  UpdateUserInfo();
    void  UpdateUserLst();
    void  UpdateDlg();
    void  UpdateManageDlg();
   
    void  ShowSubDlg( String strSubDlgName );

private:
    
    static CUserManageLogic *m_pLogic;
    
    CUserFullInfo       m_selUser;                 //当前选择的用户

    EmModifyUserType    m_emModifyType;            //是修改用户  还是 新建用户
   
    static const String m_strUserManage;           //
    static const String m_strManagerModify;

    //controls 
    static const String m_dlgUserConfig;
    static const String m_dlgUserInfo; 
    static const String m_dlgUserLst;               //用户列表界面
    static const String m_strEdtUserName;           //用户名
    static const String m_strEdtPswd;               //密码
    static const String m_strEdtNote;               //备注
   
    static const String m_strLstUser;               //用户列表
   
    static const String m_strLstConfig;             //配置列表


    //管理员界面
    static const String CUserManageLogic::m_dlgManagerInfo ;     //管理员界面
    static const String CUserManageLogic::m_strEdtManagerName ;    //用户名
    static const String CUserManageLogic::m_strEdtOriPswd ;         //原密码
    static const String CUserManageLogic::m_strEdtNewPswd ;         //新密码
    static const String CUserManageLogic::m_strEdtReNewPswd ;     //重复密码 

    //shceme
    static const String  m_schmShowUserLst;
    static const String  m_schmShowUserInfo;
    static const String  m_schmShowUserConfig;
    static const String  m_schmShowManagerModify;  //管理员密码修改
    static const String  m_schmNewUser;            //新建用户
    static const String  m_schmShowEdtState;
};

#endif // !defined(AFX_USERMANAGELOGIC_H__0720ED96_4DB3_48DD_8F13_8753E6FDA4D4__INCLUDED_)
