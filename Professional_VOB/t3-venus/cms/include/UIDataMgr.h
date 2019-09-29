// UIDataMgr.h: interface for the CUIDataMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UIDATAMGR_H__27046F30_49B2_4F4B_8662_2133B7CC3BCC__INCLUDED_)
#define AFX_UIDATAMGR_H__27046F30_49B2_4F4B_8662_2133B7CC3BCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum EMLocalCnsState 
{   
	emLocalCnsIdle = em_CALL_IDLE , //空闲状态 ，与EmCALLSTATE 对齐， 2012.11.14  by yjj  
        emLocalCnsCalling   = em_CALL_CALLING,      //正在呼叫中
		emLocalCnsConnected = em_CALL_CONNECTED,
        emLocalCallingTimeOut,  //呼叫动画已显示超过5秒，应该切换到锁屏状态
        emLocalCnsInConf,       //在会议中
        emLocalCnsHungup,       //会议开启后，localCns 不在线，执行了挂断操作
        
	   
		/*将要挂断/离开会议
         Note:表示此时正显示 （ 是否要挂断/离开会议的）提示框，
		 若此时会议从其他途径已经结束，则此时的提示框应自动隐藏 
         Bug00113809
		 2012.11.14 俞锦锦*/
		emLocalCnsWillHungup,	

		emLocalCnsLocking,      //会议开启后，localCns 不在线,当前正处于锁定状态
};


enum EmWaitType{
	emWaitRegInfo,		//等待注册信息
	emWaitConfInfo,  //等待会议信息
	emWaitLoadAddr   //等待导入地址簿
};



enum EMTimer{
	emTimerCalling,  
		emTimerRefreshUI
};


enum EM_NETMNGOPT_TYPE      //网管操作类型
{
	em_NETMNGOPT_ADD,
	em_NETMNGOPT_MODIFY,
	em_NETMNGOPT_IDLE
};

class CUIDataMgr  
{
public:
	virtual ~CUIDataMgr();

    static CUIDataMgr* GetSingleTon();
private:
	CUIDataMgr();


public:
	bool IsPcVersion();//是否是PC版
    String GetCurSimulateDlgName(){ return m_strSimulateCnsDlgName; }
    void SetCurSimulateDlgName( String strName ){ m_strSimulateCnsDlgName = strName ; }


    String GetCurMainMenuType(){ return m_strSchmMainMenuShow ;}
    void SetCurMainMenuType( String strType ) { m_strSchmMainMenuShow = strType ;}

 	
	/** 设置屏幕解锁信息
	 *  @param[in]  tInfo  屏幕解锁信息
	 *  @return 
	 */
	void SetLockScreenInfo( TLockScreenInfo tInfo );

	/** 获取屏幕解锁信息
	 *  @param[out]  TLockScreenInfo 屏幕解锁信息
	 *  @return 
	 */
	TLockScreenInfo& GetLockScreenInfo();
 
   
     /**
	* 功能:  获取本地cns状态
	* @param [out]tConfInfo  本级cns参加的会议信息
	* @return 成功返回TRUE,失败返回FALSE
	* @remarks 
	*/
    EMLocalCnsState GetLocalCnsState( ){ return m_emLocalCnsState ;}


    /**
	* 功能:  获取本地cns会议信息
	* @param [out]tConfInfo  本级cns参加的会议信息
	* @return 成功返回TRUE,失败返回FALSE
	* @remarks 
	*/
    void setLocalCnsState( EMLocalCnsState emState  ){ m_emLocalCnsState = emState; }


    //设置当前操作的会议名
    void SetCurConfName( s8 *pConfName ){ _snprintf(m_achCurConfName, sizeof(m_achCurConfName),"%s" , pConfName); }

    //获取当前操作的会议名
    s8*GetCurConfName(){ return m_achCurConfName; }


	/*
	功能：PinYin检索判断
	参数：const CString strTextInput: 待判断的对象串(用户输入PY项)
	      const CString strTextSrc  : 判断源字对象串(汉字项)
	返回值:配对成功 TRUE, 配对失败 FALSE;
	*/
	BOOL  HZPYMatchList( const CString strTextInput,  const CString strTextSrc );


    //当前是否锁屏状态
    BOOL  IsUILockScreen() { return m_bUILockScreen; }
    void  SetUILockScreen( BOOL bLockScreen ) { m_bUILockScreen = bLockScreen; }
 
private:
    static CUIDataMgr *m_pThis;

    String  m_strSimulateCnsDlgName;  //当前使用的模拟会场的界面名，便于界面切换的时候做隐藏和显示
    String  m_strSchmMainMenuShow;    //当前主菜单显示的某种菜单的方案类型

    TLockScreenInfo    m_tLockScreenInfo;

    EMLocalCnsState m_emLocalCnsState;         ///<本地cns的当前状态
    s8  m_achCurConfName[TP_MAX_ALIAS_LEN];	         ///<当前操作的会议名称
    
    BOOL    m_bUILockScreen;          //当前界面是否锁屏
};



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

#define  CNSCONF_FILE_PATH		"/usr/conf/"				//台标存放位置

#define UIDATAMGR CUIDataMgr::GetSingleTon()   
#endif // !defined(AFX_UIDATAMGR_H__27046F30_49B2_4F4B_8662_2133B7CC3BCC__INCLUDED_)
