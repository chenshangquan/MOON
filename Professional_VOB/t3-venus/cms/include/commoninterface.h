/*****************************************************************************
模块名      : CMS控制台
文件名      : commoninterface.h
相关文件    : commoninterface.cpp , umcconf.cpp, umcconftemplate.cpp, umctvw.cpp, umcumsconfig.cpp, umcuser.cpp
文件实现功能: 封装了umclib和cnclib接口，UI与cns和ums的通信统一经过该接口处理
作者        : 俞锦锦
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2011/4/28  1.0          俞锦锦      创建
******************************************************************************/

#if !defined(AFX_COMMONINTERFACE_H__E6AFC64B_E6AB_4404_930B_546D1178FF87__INCLUDED_)
#define AFX_COMMONINTERFACE_H__E6AFC64B_E6AB_4404_930B_546D1178FF87__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "umclib.h" 
#include "cnclib.h"
#include "printCtrl.h"
//#include "netadapter.h"
  
 
enum EM_EqType
{
	emEqUmsCns,     
	emEqUms,         
	emEqCns        
};



// enum EMLocalCnsState
// {   
//     emLocalCnsIdle,          //空闲状态
//         emLocalCnsCalling,   //正在呼叫中
//         emLocalCallingTimeOut,    //呼叫动画已显示超过5秒，应该切换到锁屏状态
//         emLocalCnsInConf,    //在会议中
//         emLocalCnsHunguping, //会议开启后，localCns 不在线，执行了挂断操作
//         emLocalCnsLocking,   //会议开启后，localCns 不在线,当前正处于锁定状态
// };

class CCommonInterface:public CWnd   
{

public: 
/** @defgroup  CCommonInterface（UI 接口部分）
 *  @{
 */

    

//-----session 相关-------------
/** @defgroup  ums和cns 会话管理部分接口
 * @{
 */  


 /**
  * 功  能	创建会话，包括Ums和Cns两个
  * @return u16 成功返回0;失败返回非0错误码 
  */
	void  CreateSession();

 /**
  * 功  能	销毁会话，包括Ums和Cns两个
  * @return u16 成功返回0;失败返回非0错误码 
  */
	void DesdroySession();

  /**
	* 功能   连接到UMS 和 CNS
	* @param [in]  dwIP	被连接UMS的IP地址，主机序
	* @param [in]  pStrUserName 用户名	
	* @param [in]  pStrPswd	密码
	* @return u16 成功返回0;失败返回非0错误码 
	*/
	u16 Connect( u32 dwIp, u16 nPort, LPCTSTR pStrUserName, LPCTSTR pStrPswd ); 
   

  /**
	* 功能:  当前登录的用户是否是管理员
	* @return  TRUE 是管理员，FALSE 一般用户
	*/
	BOOL IsManagerUser();
   
  /**
   * 功能:	是否连接上ums/cns
   * @return 成功返回0,失败返回非0错误码
   */ 
	BOOL32 IsConnect( EM_EqType emConnEq = emEqCns)  ; 

  /**
    * 功能:	断开与UMS和CNS的连接
	* @param [in]  emConnEq	要断开连接的对象
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	在没有连接到UMS/CNS时调用此方法，不起任何作用
	*/
	u16 DisConnect( EM_EqType emConnEq = emEqCns ) ; 
  
    /**
	* 功能:	获取登陆cns 的IP 
	* @return  u32  IP
    */
	u16 GetLoginIp( u32 & IP ); 
  
    /**
	* 功能:	获取本地 的IP 
	* @return  u32  IP
    */
	 u16 GetLocalIP( u32 & IP ) ;

	/**
	* 功能:	获取登录的用户信息
	* @return   
    */
	//u16 GetConnectedUser( CLoginRequest& user);

	/**
	* 功能:	获取连接的Cns列表
	* @return   
    */
	u16 GetConnectCnsList( TTPCnList& tCnList );

	/**
	* 功能:	登录Cns会场
	* @return   
    */
	u16 LoginCnsIns( u8 byIns );

/** @}*/ 

 
//-----会议模板相关 -------------
/** @defgroup  会议模板相关接口
 *  @{
 */

 /**
    * 功 能:	获取会议模板列表
	* @param 无
	* @return  会议模板列表的指针
	*/
    //TplArray<TTPConfTemplate>* GetConfTemplateList();

    /**
    * 功 能:	获取会议模板列表
	* @param 无
	* @return  会议模板列表的指针
	*/
	vector<TTPAlias>* GetConfTempList();

	/**
    * 功 能:	更新会议模板
	* @return  成功返回0,失败返回非0错误码
	*/
	u16 UpdateConfTemplate();


    /*功  能	修改会议模板
    参  数	tConfTem：会议模板 
    返回值  0 表示向ums发送请求成功，非0 表示发送失败
    说  明	 若会议模板已存在，则修改，若不存在，则添加*/
    //u16  ModifyConfTemplate( const TTPConfTemplate & tConfTem ) ;


    /**
    * 功能:  添加会议模板
	* @param [in]	tConfTemp	 会议模板 
	* @return	成功返回0,失败返回非0错误码
	*/
	//u16 AddConfTemplate( const TTPConfTemplate & tConfTem ) ;

    /**
    * 功能:  修改会议模板
	* @param [in]	tConfTemp	 会议模板 
	* @return	成功返回0,失败返回非0错误码
	*/
	//u16 UpdateConfTemplate( const TTPConfTemplate & tConfTem ) ;

    /**
    * 功能:  删除会议模板
	* @param [in] wConfTempID	 会议模板ID 
	* @return	成功返回0,失败返回非0错误码
	*/
	//u16 DeleteConfTemplate( const u16 wConfTemplateID )  ;

	/**获取服务器发过来的网管信息页数据 */

	u16 GetNetMngData( vector<TTPNMServerCfg> &vecTTPNMServerCfg );

 	/**
    * 功能:	 	        发送添加网管请求
 	* @param [in]       网管信息
 	* @return           u16 成功返回0,失败返回非0错误码
 	*/
 	u16  NetMngAddCmd( const TTPNMServerCfg& tTPNMServerCfg );

     /**
    * 功能:	 	        发送修改网管请求
 	* @param [in]       网管信息
 	* @return           u16 成功返回0,失败返回非0错误码
 	*/
	u16  NetMngModifyCmd( const TTPNMServerCfg& tTPNMServerCfg );

    /**
    * 功能:	 	        发送删除网管请求
	* @param [in]       网管信息
	* @return           u16 成功返回0,失败返回非0错误码
	*/
	u16  NetMngDeleteCmd( const TTPNMServerCfg& tTPNMServerCfg );
  
  
    /**
    * 功能:  根据会议ID获取会议模板指针
	* @param [in] wConfTempID	 会议模板ID 
	* @return	ID对应的会议模板
	*/  
	//TTPConfTemplate* GetConfTemplateByID( u16 wConfTemplateID ) const ;

     /**
    * 功能:  废弃一个会议模板
	* @param [in] temp	 要废弃的模板 
	* @return 
	*/  
	void InvalidConfTemp( TTPConfTemplate &temp) const ;


    
    /**
    * 功能:  根据会议模板ID和cnsID 获取cns 别名信息
	* @param [in] wConfTempID	 会议模板ID 
	* @return	ID对应的会议模板
	*/  
	//TTPAlias* GetCnsInfoFromTemplateByID( u16 wConfTemplateID , u16 wCnsID ) const ;
    
  
    /**
    * 功能:  会议模板别名是否已存在
	* @param [in] Alias:会议模板别名
	* @return  TRUE：存在，FALSE：不存在
	*/  
	//BOOL32  IsConfTemplateAliasExist( const s8* Alias   ) const;


 
	/**
    * 功能:  判断会议模板的别名和E164号是否可用
	* @param [in] Alias:会议模板别名
	* @return  成功返回0，失败返回非0错误码
	* @remarks 主要用于修改时判断，且该模板的ID必须是UMS分配的 可用的 
	*/  
	//u16    CheckConfTemplateValidate( const TTPConfTemplate & tConfTem ) const;
 
  
    /**
    * 功能:  会议模板E164号是否已存在
	* @param [in] E164：会议模板E164号
	* @return  TRUE：存在，FALSE：不存在
	*/ 
	//BOOL32  IsConfTemplateE164Exist( const s8* E164  ) const;

    /**
    * 功能:  判断会议模板的主席cns 是否为本地主cns
	* @param [in] tConfTem:会议模板 
	* @return  成功返回0，失败返回非0错误码
	* @remarks 主要使用该模板开会时
	*/  
	//u16    CheckConfTemplateChairMan( TCMSConfTemplate & tConfTem )  ;

    /**
    * 功能:  判断会议模板的主席cns 是否为本地主cns
	* @param [in] wConfTemID:会议模板ID
	* @return  成功返回0，失败返回非0错误码
	* @remarks 主要使用该模板开会时
	*/  
	//u16    CheckConfTemplateChairMan( const u16 & wConfTemID )  ;
  

/** @}*/ 	
	
//-----会控相关接口 -------------
/** @defgroup  会控相关接口
 *  @{
 */
 
   BOOL32 IsInConf( TCMSConf *pConf = NULL );

    

   /**
	* 功能:  获取会议信息  
	* @return  返回列表指针
	*/
    TCMSConf  &GetConfInfo(){ return m_tConfInfo ; }


    /**
    * 功能:  判断 cns是否为 会议的主席
	* @param  
	* @return   
	* @remarks  
	*/
    BOOL32 IsCnsChairMan(  u16 wCnsID );

   
 
   
     
 
	/**
	* 功能:  获取会议的cns列表
	* @param [in]wConfID	 会议ID 
	* @return 成功返回会议信息指针,失败返回NULL
	*/
	TplArray<TCnsInfo>* GetConfCnsList( const u16 wConfID ) ;

    /*
	* @param [in]achRoomName 会场名
	* @return 在返回TRUE,不在返回FALSE
	* @remarks 
	*/
	BOOL32 IsCnsInConf( s8* achRoomName )   ;  


    /**
	* 功能:  本级cns是否是发言人
	* @param [int]wConfID 会议信息 
	* @return 成功返回TRUE,失败返回FALSE
	* @remarks  
	*/
    BOOL32 IsLocalCnsSpeaker(  )  ; 


    /**
	* 功能:  多点会议中本级cns是否是发双流
	* @param [int]wConfID 会议信息 
	* @return 成功返回TRUE,失败返回FALSE
	* @remarks  
	*/
    BOOL32 IsLocalCnsDualInConf( )  ; 

     

    /**
	* 功能:  获取本地cns会议状态
	* @param [out]tConfInfo  本级cns参加的会议信息
	* @return 成功返回TRUE,失败返回FALSE
	* @remarks 
	*/
    TTPCnsConfStatus GetLocalCnsConfState() const; 

   



	/**
	* 功能:  本级cns是否是主席 
	* @return 成功返回TRUE,失败返回FALSE
	* @remarks 由CNS负责管理该状态
	*/
	BOOL32 IsLocalCnsChairMan()  ;

 

   /**
    * 功能:  判断 是否为本地主cns
	* @param strAliars 别名
	* @return   
	* @remarks  
	*/
    BOOL32 IsLocalCns( String strAliars );   


   /**
	* 功能:  使用会议模板开会 
	* @param [in]  achTempName: 模板名
	* @return 成功返回0，失败返回错误码
	*/
	u16 StartTemplateConf( s8* achTempName ) ;

	/**
	* 功能:  使用会议模板开会 
	* @param [in]  tTemp: 模板 
	* @return 成功返回0，失败返回错误码
	*/
	u16 StartTemplateConf( const TTPAlias& tTemp ) ; 
	

	/**
	* 功能:  开启一个即时会议 
	* @param [in] tCnsList :与会的终端列表 ,本会场为第一个成员，并设置为主会场
	* @param [out] achConfName :会议名
	* @return 成功返回0，失败返回错误码
	* @remarks ums预存一个用于开启临时会议的会议模板（ID为0），该会议模板界面不显示
	*/
	u16 StartInstantConf( const vector<TCnAddr>& tCnsList );
 
	
 
 /**
	* 功能:  挂断会议 
	* @param [in] dwConfID：会议ID
	* @return 成功返回0，失败返回错误码
	* @remarks 结束会议
	*/
	u16 HangupConf( )  ;
    
    
  
/**
	* 功能:  邀请某会场参与会议 
	* @param [in] tEp:会场信息
	* @return 成功返回0，失败返回错误码
	* @remarks 当本会场为主会场时方可操作
	*/
	u16 InviteCns( const TConfCallEpAddr &tEp );



    /**
    * 功能:	呼叫会议中已经存在的cns会场加入某会议
	* @param [int]  tEp	 会议和会场信息
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 消息：cms->ums  evtp_CallEP_cmd  \n
                       应回复：ums->cms evtp_CallEP_result   \n
	                   若成功，还应发：ums->cms evtp_UpdateConfCnsList_Notify
	*/ 
   u16 CallConfCns( const TConfEpID &tEp );



    /**
	* 功能:  邀请多个会场参与会议 
	* @param [in] tEp:会场信息
	* @return 成功返回0，失败返回错误码
	* @remarks 当本会场为主会场时方可操作
	*/
	u16 InviteCns( const tagConfCallEpAddrList &tEp );
	 

    /**
	* 功能:  获取会议中cns的信息
	* @param [in] tEp:会场信息
    * @param [out] tCnsInfo:会场信息
	* @return 成功返回0，失败返回错误码
	* @remarks 当本会场为主会场时方可操作
	*/
    u16 GetConfCnsByID( const TConfEpID &tConfEpInfo , TCnsInfo* pTCnsInfo);

   
/**
	* 功能:  挂断某会场 
	* @param [in] tConfEpInfo: eqID 会议ID
	* @return 成功返回0，失败返回错误码
	* @remarks 会议列表中依然存在该会场，只是不在线
	*/
    u16 HangupCNS( const TConfEpID &tConfEpInfo );
 
	
/**
	* 功能:  从会议中移除某会场 
	* @param [in] tConfEpInfo: eqID 会议ID
	* @return 成功返回0，失败返回错误码
	* @remarks 移除后会议列表中不存在该会场 ,暂时不用该接口
	*/
	u16 RemoveCNS( const TConfEpID &tConfEpInfo );

 
	/**
	* 功能:  设置发言 CNS
	* @param [in]wConfID	 会议ID
	* @return 成功返回0，失败返回错误码 
	*/ 
	u16 SetSpokeCns( const TConfEpID &tConfEpInfo );
   
    

    /**
    * 功能:	设置远程cns静音
	* @param [int]  wConfID	 籌nfoList );


 
	/**
	* 功能:  更新轮询列表请求 
	* @param [in]tTurnInfoList	 轮询列表
	* @return 成功返回0，失败返回错误码 
	*/ 
	u16 UpdatePollList( const TConfTurnInfo &tTurnInfoList );
 
 
//   /**
// 	* 功能:  开启混音 
// 	* @param [in]wConfID	 会议ID
// 	* @return 成功返回0，失败返回错误码 
// 	*/ 
// 	u16 StartAuxMix( const u16 wConfID );
// 
//  
// 	/**
// 	* 功能:  停止混音 
// 	* @param [in]wConfID	 会议ID
// 	* @return 成功返回0，失败返回错误码 
// 	*/ 
// 	u16 StopAuxMix( const u16 wConfID );


    
    /*功  能	更新混音列表请求
    参  数	tMixInfo	 混音列表
    返回值	成功返回0,失败返回非0错误码
    说  明	 */
	u16 UpdateAudMixList( const TConfAuxMixInfo &tMixInfoList );

	 /*
	功  能	混音列表操作请求
	参  数	tDisListOpr	 混音列表操作
	返回值	成功返回0,失败返回非0错误码
	说  明	 */
	u16 AudMixDisListOpr( const TTPDisListOpr &tDisListOpr );

	/**
	* 功能:  开启轮询 
	* @param [in]wConfID	 会议ID
	* @return 成功返回0，失败返回错误码 
	*/ 
	u16 StartPoll( const u16 wConfID );


 
	/**
	* 功能:  停止轮询 
	* @param [in]wConfID	 会议ID
	* @return 成功返回0，失败返回错误码 
	*/ 
	u16 StopPoll( const u16 wConfID ); 

	/**
	* 功能:  获取服务器网管配置详情页信息 
	* @param [in]wConfID	 会议ID
	* @return 成功返回0，失败返回错误码 
	*/ 
 
/** @}*/ 
	

//-----会议相关相关接口 -------------
/** @defgroup  会议相关相关接口
 *  @{
 */ 
 
	/**
	* 功能:  获取本级cns信息 
	*  @param[out] tCnsInfo：本CNS信息
	*  @return 成功返回0,失败返回非0错误码
	* @remarks 
	*/
	u16 GetLocalCnsInfo( TTPCnsInfo& tCnsInfo ) const;
  
	/**
	* 功能:  获取本cns列表 
	* @param[out] vctCnsList：本级cns列表信息
	* @return 成功返回0,失败返回非0错误码
	* @remarks 
	*/
	u16 GetLocalCnsList( vector<TTPCnsInfo>& vctCnsList ) const;

	/**
	* 功能:  更新cns信息 
	* @param[in] tInfo CNS信息  byIndex 消息来自哪里(0为cnc 1为维护工具)
	* @return 成功返回0,失败返回非0错误码
	* @remarks 
	*/
	u16 UpdateCnsInfo( const TTPCnsInfo& tInfo, u8 byIndex );

	/**
	* 功能:  设置cns主会场 
	* @param[in] pbyRoomName 会场名
	* @return 成功返回0,失败返回非0错误码
	* @remarks 
	*/
	u16 SetMainCns( s8* pbyRoomName );

	/**
	* 功能:  获取cns主会场 
	* @return 成功返回会场名,失败返回NULL
	* @remarks 
	*/
	const s8* GetMainCnsName();

	/**
	* 功能:  获取本cns屏信息 
	* @param[out] vctScreenInfo：本cns屏信息
	* @return 成功返回0,失败返回非0错误码
	* @remarks 
	*/
	u16 GetCnsScreenInfo( vector<TScreenInfo>& vctScreenInfo ) const;

    u16 GetCnsScreenInfoByID( u8 screenID, TScreenInfo& tScreenInfo ) const;

	/**
	* 功能:  清空本cns屏信息 
	* @remarks 
	*/
	void ClearCnsScreenInfo();

/** @}*/ 
	
//----电视墙相关--------------
/** @defgroup  电视墙相关
 *  @{
 */

    /**
	* 功能:  判断cns是否在电视墙上
	* @return 成功返回true,
	* @remarks 
	*/ 
    BOOL32 IsCnsInTvw( s8 *abyCnsAliars );

	//获取电视墙预案列表
    //TplArray<TCmsTvwInfo>* GetTvwList()  ;
 
    //根据电视墙Handle号获取电视墙信息
    //TCmsTvwInfo * GetTvwInfoByHandleID( const u32 dwHandleID ) const;

	//播放电视墙预案
    //u16 PlayTvw ( const TTPHduPlayReq & tTvwInfo ); 
   
	//删除电视墙预案
    //u16 DeleteTvw( const TTPHduPlayReq & tTvwInfo ); 

	//获取HDU 板卡信息

/** @}*/ 


 //-----用户相关 -------------
/** @defgroup  用户相关
 *  @{
 */
	

 
	/**
	* 功能:  获取用户列表  
	* @return  成功返回用户列表指针，失败返回空
	*/
   TplArray<CUserFullInfo>* GetUserList() ;
	
 
   /**
	* 功能:  添加用户 
	* @param [in]  user  
	* @return  成功返回0，失败返回错误码
	*/
	u16 AddUser( const CUserFullInfo& user )    ;
    

 
	/**
	* 功能:  修改用户信息 
	* @param [in]  user  
	* @return  成功返回0，失败返回错误码
	*/
	u16 UpdateUser( const CUserFullInfo& user )   ;
	 
 
	/**
	* 功能:  删除用户 
	* @param [in]  user  
	* @return  成功返回0，失败返回错误码
	*/
    u16 DeleteUser( const CUserFullInfo & user ) ;
	
 
	/**
	* 功能:  根据用户名获取用户信息 
	* @param [in]  pUserName  
	* @return  成功返回用户信息指针，失败返回空指针
	*/
	CUserFullInfo *GetUserByName ( s8 *pUserName )  const ;


 
/**
	* 功能:  判断用户名是否以存在 
	* @param [in]  pUserName  
	* @return  成功返回TREU，失败返回FLASE
	*/
	BOOL32  IsExistUser ( s8 *pUserName ) const ;

/** @}*/ 

 
	
 //-----CNS  设置-------------  
/** @defgroup  CNS 设置
 *  @{
 */

    /**点对点呼叫
	*  @param[in] 
	*  @return  
	*/
    u16 MakeCall( TCnAddr& tCnAddr );

	u16 MakeCall( const TTPAlias& tAlias );

    u16 HungupPtpConf();

	/**获取当前speaker状态，是否为静音
	*  @param[in] 
	*  @return BOOL 是否为静音
	*/
	BOOL32 IsLocalCnsQuite();

	/**获取当前Mic状态，是否为 哑音
	*  @param[in] 
	*  @return BOOL 是否为哑音
	*/
	BOOL32 IsLocalCnsMute(); 

	/**本地会场静音 设置
	*  @param[in] Quite 是否静音
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 SetLocalCnsQuite( BOOL bQuite = TRUE );

	/**本地会场哑音 设置
	*  @param[in] bMute 是否哑音
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 SetLocalCnsMute( BOOL bMute = TRUE );

	/**调节会场输入音量
	*  @param[in] byVolume 音量
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 AdjustInputVol( u8 byVolume );

	/**调节会场输出音量
	*  @param[in] byVolume 音量
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 AdjustOutputVol( u8 byVolume );
	
	/**获取会场输入音量
	*  @return  byVolume 音量
	*/
	u8 GetInputVol();

	/**获取会场输出音量
	*  @return byVolume 音量
	*/
	u8 GetOutputVol();

  

  /**设置会场发言坐席
	*  @param[in] bySeatId 坐席ID
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 SetCnsInnerSpeaker( u8 bySeatId );

	/**获取会场发言坐席
	*  @param[in] 
	*  @return 坐席ID
	*/
	u8 GetCnsInnerSpeaker();

	/** 功能:  CNS设置SIP注册配置 
	*  @param[in] tSipCfg Sip注册配置
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 CnsRegSipService( const TTPSipRegistrarCfg &tSipCfg );

	/** 功能:  CNS注销SIP服务 
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 CnsUnRegSipService();

	/** 功能   获得SIP配置
	*  @param[out] tSipCfg SIP配置
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 GetSipCfg( TTPSipRegistrarCfg& tSipCfg );


    /** 功能:  CNS设置Gk注册配置 
	*  @param[in] tSipCfg Sip注册配置
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 CnsRegGkService( const TTPGKCfg &tCfg );


    /** 功能   获得Gk配置
	*  @param[out] tGkCfg
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 GetGkCfg( TTPGKCfg& tGkCfg );


	/** 功能:  更新网络配置
	*  @param[in] tInfo 网络配置
	*  @return 成功返回0,失败返回非0错误码
	*  @remarks 
	*/
	u16 UpdateEthnetCfg( const TTPEthnetInfo& tInfo );

	/** 功能   获得网络配置
	*  @param[out] tInfo 网络配置
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 GetEthnetCfg( TTPEthnetInfo& tInfo );

	/** 功能:  更新NAT配置
	*  @param[in] tInfo NAT配置
	*  @return 成功返回0,失败返回非0错误码
	*  @remarks 
	*/
	u16 UpdateNATCfg( const TTPNatCfg& tInfo );

	/** 功能   获得NAT配置
	*  @param[out] tInfo NAT配置
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 GetNATCfg( TTPNatCfg& tInfo );

     /** 功能   设置系统时间
	 *  @return 成功返回会场名,失败返回NULL
	 *  @remarks 
	 */
     u16 UpdateSysTime( const TTPTime& time ) ;
    
    
    /** 功能   获取系统时间
	 *  @return 成功返回会场名,失败返回NULL
	 *  @remarks 
	 */
    u16 ReqSysTime();

	/** 功能   升级服务器地址
	*   @param[in] TTPUpgradeSer 服务器地址结构体
	 *  @return 成功返回0,失败返回非0错误码
	 */
	u16 UpgradeSerCmd( const TTPUpgradeSer& tUpgradeSer );

	/** 功能   获得服务器地址
	*  @param[out] TTPUpgradeSer 服务器地址结构体
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 GetUpgradeSerInfo( TTPUpgradeSer& tUpgradeSer );

	/** 功能   呼叫服务器
	*   @param[in] u32_ip 服务器地址
	 *  @return 成功返回0,失败返回非0错误码
	 */
	u16 CallServerCmd( const TTPCallSerInfo& tCallSerInfo );

	/** 功能   获取呼叫服务器配置
	*  @param[out] TTPCallSerInfo 呼叫服务器配置
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 GetCallServerInfo( TTPCallSerInfo& tCallSerInfo );

    /** 
	* 功能  设置电视墙选看
    * @param [in]  byScreenID  屏号
	* @return  
	* @remarks 
	*/
	u16 SetSelTVSView( u8 byScreenID ) ;

     /** 
	* 功能  取消电视墙选看
    * @param [in]  byScreenID  屏号
    * @param [in]  wEpID  选看的cnsID
	* @return  
	* @remarks 
	*/
	u16 CancleSelTVSView( u8 byScreenID ) ;

    /** 
	* 功能  设置选看
    * @param [in]  byScreenID  屏号
    * @param [in]  wEpID  选看的cnsID
	* @return  
	* @remarks 
	*/
	u16 SetSelView( u8 byScreenID, u16 wEpID ) ;

     /** 
	* 功能  取消选看
    * @param [in]  byScreenID  屏号
    * @param [in]  wEpID  选看的cnsID
	* @return  
	* @remarks 
	*/
	u16 CancleSelView( u8 byScreenID ) ;

   /** 
	* 功能  开启/停止轮询
    * @param [in]  bStart   true:开启，false：关闭
	* @return  
	* @remarks 
	*/
	u16 StartPoll( BOOL  bStart ) ;

   /** 
	* 功能  本地cns是否在轮询
    * @param [in]  
	* @return  true:开启，false：关闭  
	*/
	BOOL32  IsLocalCnsPoll();

    /** 
	* 功能  开启/停止双流
    * @param [in]  bStart   true:开启，false：关闭
	* @return  
	* @remarks 
	*/
	u16 StartDual( BOOL  bStart ) ;

   /** 
	* 功能  本地cns是否开启双流
    * @param [in]  
	* @return  true:开启，false：关闭  
	*/
	BOOL32 IsLocalCnsDual() const;
    
/** @}*/ 

//-----地址簿相关-------------  
/** @defgroup  地址簿相关
 *  @{
 */	 

	/** 功能:  获取地址簿
	 *  @return CAddrBook 返回地址簿对象
	 */
	CAddrBook& GetAddrBook();

	BOOL GetAddrLoadingState();
	void SetAddrLoadingState(BOOL bAddrLoading);

	/** 功能:  添加地址簿条目
	 *  @param[in] entry 地址簿条目
	 *  @return 成功返回0,失败返回非0错误码
	 */ 
	u16 AddEntry( const CAddrEntry& entry );

	/** 功能:  修改地址簿条目
	 *  @param[in] entry 地址簿条目
	 *  @return 成功返回0,失败返回非0错误码
	 */
	u16 ModifyEntry( const CAddrEntry& entry );

	/** 功能:  删除地址簿条目
	 *  @param[in] dwIndex 地址簿条目索引
	 *  @return 成功返回0,失败返回非0错误码
	 */
	u16 DeleteEntry( u32 dwIndex );

	/** 功能:  删除多个地址簿条目
	 *  @param[in] vctEntry 地址簿条目索引表
	 *  @return 成功返回0,失败返回非0错误码
	 */
	u16 DeleteMultiEntry( vector<u32>& vctEntry );

	/** 添加地址簿条目组
	 *  @param[in] group 地址簿条目组
	 *  @return 成功返回0,失败返回非0错误码
	 */
	u16 AddGroup( const CAddrMultiSetEntry& group );

	/** 修改地址簿条目组
	 *  @param[in] entry 地址簿条目组
	 *  @return 成功返回0,失败返回非0错误码
	 */
	u16 ModifyGroup( const CAddrMultiSetEntry& group );

	/** 删除地址簿条目组
	 *  @param[in] dwIndex 地址簿组索引
	 *  @return 成功返回0,失败返回非0错误码
	 */
	u16 DeleteGroup( u32 dwIndex );

    /** 功能:  删除多个地址簿组
	 *  @param[in] vctGroup 地址簿组索引表
	 *  @return 成功返回0,失败返回非0错误码
	 */
    u16 DeleteMultiGroup( vector<u32>& vctGroup );

	/** 添加地址簿组成员
	 *  @param[in] tGroupEntry 地址簿组信息
	 *  @return 成功返回0,失败返回非0错误码
	 */
	u16 AddEntryToGroup( const TADDRMULTISETENTRY& tGroupEntry );

	/** 删除地址簿组成员
	 *  @param[in] tGroupEntry 地址簿组信息
	 *  @return 成功返回0,失败返回非0错误码
	 */
	u16 DelEntryFromGroup( const TADDRMULTISETENTRY& tGroupEntry );

	/** 添加地址簿组关系
	 *  @param[in] dwGroupIndex 组索引
	 *  @param[in] dwUpGroupIndex 上级组索引
	 *  @return 成功返回0,失败返回非0错误码
	 */
	u16 AddGroupToGroup( u32 dwGroupIndex, u32 dwUpGroupIndex );

	/** 删除地址簿组关系
	 *  @param[in] dwGroupIndex 组索引
	 *  @param[in] dwUpGroupIndex 上级组索引
	 *  @return 成功返回0,失败返回非0错误码
	 */
	u16 DelGroupFromGroup( u32 dwGroupIndex, u32 dwUpGroupIndex );

	/** 更新全局地址簿
	 *  @return 成功返回0,失败返回非0错误码
	 */
	u16 UpdateGlobalAddrbook();

	/**
	* 功能:  获取本地地址簿列表  
	* @return  成功返回地址簿列表指针，失败返回空
	*/
	const vector<TAddrItem>* GetLocalAddrList();

	/**
	* 功能:  获取全局地址簿列表  
	* @return  成功返回地址簿列表指针，失败返回空
	*/
	const vector<TAddrItem>* GetGlobalAddrList();

	/**
	* 功能:  获取cns注册的地址簿条目  
	* @return  成功返回地址簿列表指针，失败返回空
	*/
	void GetCnsRegInfo( vector<TAddrInfo>* pvctCnsRegInfo );

	/**
	* 功能:  获取地址簿组列表 
	* @return  成功返回地址簿组列表指针，失败返回空
	*/
	const vector<TAddrItem>* GetAddrGroupList();

    /**
	* 功能:  获取本地地址簿条目列表  
	* @return  成功返回地址簿列表指针，失败返回空
	*/
    const vector<TAddrItem>* GetAddrEntryList();

	/**
	* 功能:  获取地址簿分组成员列表  
	* @param[in]  dwGroupIndex  组索引
	* @param[out] vctGroupMemberList  分组成员列表
	* @return  
	*/
	void GetAddrGroupMember( u32 dwGroupIndex, vector<TAddrItem>& vctGroupMemberList );

	/**
	* 功能:  获取地址簿分组信息
	*  @param[in]  dwGroupIndex  组索引
	*  @param[out] tGroupInfo  分组信息
	*  @return
	*/
	void GetAddrGroupInfo( u32 dwGroupIndex, TGroupInfo& tGroupInfo );

	/**
	* 功能:  获取地址簿分组路径名
	*  @param[in]  dwGroupIndex  组索引
	*  @return  路径名
	*/
	CString GetAddrGroupPath( u32 dwGroupIndex );

	/** 将CAddrEntry数据设到TAddrInfo中
	 *  @param[out] tAddrInfo  地址条目信息
	 *  @param[in]  cAddrEntry 地址簿条目信息
	 *  @return 
	 */
	void SetAddrItemInfo( TAddrInfo& tAddrInfo, CAddrEntry& cAddrEntry );

	/** 获取组中的条目信息
	 *  @param[in]   tGroupInfo  地址组信息
	 *  @param[out]  vctAddrInfo 地址条目信息列表
	 *  @return 
	 */
	void GetGroupAddrInfo( const TGroupInfo& tGroupInfo, vector<TAddrInfo>& vctAddrInfo );  
/** @}*/


    u16  IsThisCnsHaveConf() const;


    //设置当前操作的会议名
    void SetCurConfName( s8 *pConfName ){ 
        InvalidConfTemp(m_tCurConfTemplate );
        _snprintf(m_tCurConfTemplate.m_achConfName, sizeof(m_tCurConfTemplate.m_achConfName),"%s" , pConfName);
    }

    void SetCurConfTemplate( TTPConfTemplate  &tCurConfTemplate ){
        m_tCurConfTemplate = tCurConfTemplate ;
        m_tCurConfTemplate.m_wID = tCurConfTemplate.m_wID; 
    }

    //获取当前操作的会议名
    s8*GetCurConfName(){ return m_tCurConfTemplate.m_achConfName; }
    TTPConfTemplate GetCurConfTemplate(){ return m_tCurConfTemplate; }
/** @}*/
    
    void  ShutDownOS(BOOL bRestart = FALSE );
    
    void  ShutDownCmc( BOOL bRestart = FALSE );


    void DisableTaskMgr( BOOL bDisable );


    //请求码流
    u16 StartDualCodeStream( const TTPCnMediaTransPort  &tVedioTransAddr, const TTPCnMediaTransPort  &tAudioTransAddr  ) const;
    u16 StopDualCodeStream() const;

    u16 ReqKeyFrame( BOOL32 bForce = TRUE ) const;

    TTPCnMediaTransPort GetVedioTransAddr() const  ;
    TTPCnMediaTransPort GetAudioTransAddr() const  ;

  
     /** 
	* 功能  屏幕显示双流图像
	* @return  BOOL  TRUE:开启， FALSE:停止
	* @remarks 
	*/
    u16 ScrnDisplayDual( const u16 wScrnID ) const ;

     /** 
	* 功能  屏幕显示双流图像
	* @return  
	* @remarks 
	*/
    u16 ScrnStopDisplayDual( const u16 wScrnID ) const ;

    /** 
	* 功能  屏幕回显
	* @return    

	* @remarks 
	*/
    u16 ScrnDisplayLocal( const u16 wScrnID ) const  ;


    /** 
	* 功能  取消屏幕回显
	* @return    
	* @remarks 
	*/
    u16 ScrnStopDisplayLocal( const u16 wScrnID ) const  ;


	BOOL32 IsRcvDual() const; 


	u16 SetMuteCns( const TConfEpID &tConfEpInfo , BOOL32 bMute);

	u16 SetQuietCns( const TConfEpID &tConfEpInfo, BOOL32 bQuiet);

	u16 SetDualCns( const TConfEpID &tConfEpInfo, BOOL32 bStart );

    /** 功能   获得登陆CNS的配置
	*  @param[out] tLoginInfo
	*  @return 成功返回0,失败返回非0错误码
	*/
    u16 GetLoginInfo( TLoginInfo& tLoginInfo );


	/** 功能  清空获取到的Sip注册信息
	*  @param[in] emTyep  类型
	*  @return 无
	*/
	void ClearSipRegInfo( EmGetRegInfoType emTyep );

    /** 功能   获得演示源信息
	*  @param[out] tDualSrcinfo 演示源配置
	*  @return 成功返回0,失败返回非0错误码
	*/
    u16 GetDualSrcInfo( TDualSrcInfo& tDualSrcinfo );

    /** 功能   选择演示源端口
	*  @param[out] emType 演示源类型
	*  @return 成功返回0,失败返回非0错误码
	*/
    u16 SelDualInputPort( EmVgaType emType );

    /** 功能   设置演示源信息
	*  @param[in] tVgaInfo 演示源信息
    *  @param[in] bDefault 是否默认演示源
	*  @return 成功返回0,失败返回非0错误码
	*/
    u16 SetDualPortInfo( const TVgaInfo& tVgaInfo, BOOL bDefault );

	/** 功能   设置系统待机信息
	*  @param[in] tTPSleepInfo 系统待机信息
    *  @param[in] bDefault 是否启用系统待机
	*  @return 成功返回0,失败返回非0错误码
	*/
    u16 SetSysSleepInfo( const TCenDevSleepInfo& tCenDevSleepInfo );

	/** 功能   获得系统待机信息
	*  @param[out] tDualSrcinfo 演示源配置
	*  @return 成功返回0,失败返回非0错误码
	*/
    u16 GetSysSleepInfo( TCenDevSleepInfo& tCenDevSleepInfo );

	/** 功能   台标文件上传成功通知
	*  @param[in] byIndex 消息来自哪里(0为cnc 1为维护工具)
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 ConfSignCmd( const BOOL& bOk, u8 byIndex );

	//判断目录是否存在
	BOOL ExistDir( const CString strDir );
	
	//创建目录
    BOOL CreateDir( CString strDir );

	/**
    * 功能:	 	        设置会议优选格式
	* @param [in]       
	* @return           u16 成功返回0,失败返回非0错误码
	*/
	u16  VideoFormatCmd( const TTPVidForamt& tVidForamt );
 
	/**
    * 功能:	 	        设置演示优选格式
	* @param [in]       
	* @return           u16 成功返回0,失败返回非0错误码
	*/
	u16  DualVideoFormatCmd( const TTPVidForamt& tVidForamt );
 
	/**
    * 功能:	 	        设置单屏码率
	* @param [in]       
	* @return           u16 成功返回0,失败返回非0错误码
	*/
	u16  CallRateCmd( const u16 wCallRate );
 
	/**
    * 功能:	 	        设置演示码率
	* @param [in]       
	* @return           u16 成功返回0,失败返回非0错误码
	*/
	u16  DualCallRateCmd( const u16 wDualCallRate );
 
	/**
    * 功能:	 	        设置会议讨论状态
	* @param [in]       
	* @return           u16 成功返回0,失败返回非0错误码
	*/
	u16  ConfDisCmd( const BOOL& bDis );
 
	/**
    * 功能:	 	        设置会议轮询信息
	* @param [in]       
	* @return           u16 成功返回0,失败返回非0错误码
	*/
	u16  ConfPollCmd( const TTPPollInfo& tPollInfo );
 
	/**
    * 功能:	 	        开启画中画通知
	* @param [in]       
	* @return           u16 成功返回0,失败返回非0错误码
	*/
	u16  ViewLocalPIPCmd( const u8 byScrnID, const BOOL bLocalP );
  
	/**
    * 功能:	 	        设置音频格式信息
	* @param [in]       
	* @return           u16 成功返回0,失败返回非0错误码
	*/
	u16  AudioFormatCmd( const EmTpAudioFormat& emAudioFormat );
 
	/** 
	* 功能  	获取会议优选格式
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetVideoFormatInfo( TTPVidForamt& tVidForamt )const;
	/** 
	* 功能  	获取演示优选格式
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetDualVideoFormatInfo( TTPVidForamt& tVidForamt )const;
	/** 
	* 功能  	获取单屏码率
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCallRateInfo( u16& wCallRate )const;
	/** 
	* 功能  	获取演示码率
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetDualCallRateInfo( u16& wDualCallRate )const;
	/** 
	* 功能  	获取会议轮询信息
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetConfPollInfo( TTPPollInfo& tPollInfo )const;
	/** 
	* 功能  	获取会议讨论信息
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetConfDisInfo( BOOL& bDis )const;
	/** 
	* 功能  	获取音频格式信息
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	EmTpAudioFormat GetAudioFormatInfo()const;
	/** 
	* 功能  	画中画开启结果
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	BOOL IsViewLocalPIP()const;

	/** 
	* 功能  	获取中控电视墙开启状态
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	BOOL GetDisplayState() const;

protected:
    /**
	* 功能   连接到UMS 
	* @param [in]  dwIP	被连接UMS的IP地址，主机序
	* @param [in]  pStrUserName 用户名	
	* @param [in]  pStrPswd	密码
	* @return u16 成功返回0;失败返回非0错误码 
	*/
	u16 ConnectUms(); 


    
  /**
	* 功能   连接到CNS 
	* @param [in]  dwIP	被连接UMS的IP地址，主机序
	* @param [in]  pStrUserName 用户名	
	* @param [in]  pStrPswd	密码
	* @return u16 成功返回0;失败返回非0错误码 
	*/
	u16 ConnectCns( /*u32 dwIp, u16 nPort, CString strUserName, CString strPswd */); 


protected:  
/** @defgroup  消息响应函数
 *  @{
 */	
	 
	afx_msg LRESULT OnRefreshConfTemplateLst(  WPARAM wParam, LPARAM lParam ) ;
	afx_msg LRESULT OnRefreshUserLst(  WPARAM wParam, LPARAM lParam ) ;
	
	/**ums会议相关*/
	afx_msg LRESULT OnRefreshConf( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnRefreshConfCnsLst( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnRefreshConfAudMixLst( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnRefreshConfPollLst( WPARAM wParam, LPARAM lParam ); 

    
    afx_msg LRESULT OnSpeakerNotify( WPARAM wParam, LPARAM lParam ); 
    afx_msg LRESULT OnSetSpeakerRsp( WPARAM wParam, LPARAM lParam ); 
    afx_msg LRESULT OnSetMuteCnsRsp( WPARAM wParam, LPARAM lParam ); 
    afx_msg LRESULT OnSetSlienceCnsRsp( WPARAM wParam, LPARAM lParam ); 
    afx_msg LRESULT OnSetDaulCnsRsp( WPARAM wParam, LPARAM lParam ); 
    afx_msg LRESULT OnDaulCnsUpdateNotify( WPARAM wParam, LPARAM lParam );     

    /*cns 本地会议相关*/ 
    
    afx_msg LRESULT OnCnsEthnetInfoNotify( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnCnsRegSigServNotify( WPARAM wParam, LPARAM lParam );

    afx_msg LRESULT OnConnectCns(  WPARAM wParam, LPARAM lParam ) ;
	afx_msg LRESULT OnCnsInfoNotify( WPARAM wParam, LPARAM lParam );

	afx_msg LRESULT UpdateAddrBook( WPARAM wParam, LPARAM lParam );
	
	afx_msg LRESULT OnRefreshGlobalAddrBook( WPARAM wParam, LPARAM lParam );

    afx_msg LRESULT OnTPadLoginUserNty( WPARAM wParam, LPARAM lParam );

    //电视墙
    //afx_msg LRESULT OnRefreshTvw(WPARAM wParam, LPARAM lParam);
    //afx_msg LRESULT OnPlayHduRsp(WPARAM wParam, LPARAM lParam);
    //afx_msg LRESULT OnStopHduRsp(WPARAM wParam, LPARAM lParam);
    //afx_msg LRESULT OnHduCodeStreamNotify(WPARAM wParam, LPARAM lParam);    
   
    DECLARE_MESSAGE_MAP()
/** @}*/ 

protected:

	void UpdateAddrList();
	void UpdateAddrEntryList();
	void UpdateAddrGroupList();
	void UpdateLevelOneGroup();
   
public:
    u16 LinkUms();
    u16 LinkCns();

    //连接到TPad
    u16 ConnectTPad();
        
    //修改系统名称 dyy 2013年8月29日
    u16 SetTpadSysName( string strSysName );
   
private:
/** @defgroup  成员 变量定义
 *  @{
 */	
    //CUmsSessionCtrlIF   * m_pUmsSessionCtrl;  ///<ums的会话控制
    CCnsSessionCtrlIF   *m_pCnsSession;       ///<cns会话
    TLoginInfo           m_tLoginInfo;
	u32	   m_dwCnsIp;	  //连接的CNS的IP
	CLoginRequest   m_cUser; 
    
	/**UMS 相关接口*/
	//CConfTemplateCtrlIF *m_pConfTemplateCtrl;
	//CConfCtrlIF         *m_pConfCtrl;
	//CTvwCtrlIF          *m_pTvwCtrl;
	//CUmsConfigCtrlIF    *m_pUmsConfigCtrl;
	//CUserCtrlIF         *m_pUserCtrl;

	/**CNS 相关接口*/
	CCncConfigIF        *m_pCnsConfigCtrl;
	CCncConfCtrlIF      *m_pCnsConfCtrl;
    CUmcConfCtrlIF      *m_pUmsConfCtrl;
	CCncAddrbookIF      *m_pAddrBookCtrl;
	CCncUserCtrlIF      *m_pCnsUserCtrl;
	CCncSipInfoCtrlIF   *m_pSipInfoCtrl;
	CCncNetMngCtrlIF    *m_pNetMngCtrl;
	CCncPortDiagCtrlIF	*m_pPortDiagCtrl;
	CCncCenterCtrlIF    *m_pCenterCtrlIF;

	/**ums 相关数据*/
	//TplArray<TTPConfTemplate> m_tplConfTempList;       ///< 会议模板列表
	TplArray<CUserFullInfo>   m_tplUserList;           ///<用户列表
	ARRAY<TCMSConf>           m_tplConfList;           ///<会议列表  解决： Bug00073719:同一个会场开多点会议6个后，无法再挂断该会场。 
    //TplArray<TCmsTvwInfo>     m_tplTvwList;            ///<电视墙列表
    
 
	/**cns 相关数据*/
	vector<TAddrItem>         m_vctLocalAddrList;       //本地地址簿
	vector<TAddrItem>         m_vctGlobalAddrList;      //全局地址簿
    vector<TAddrItem>         m_vctEntryList;           //本地地址簿所有条目
	vector<TAddrItem>         m_vctGroupList;

	vector<TTPAlias>          m_vctConfTempList;        //会议模板列表	

	static const u16 m_stcCstConnectUmsFail;			//连接 ums失败
	static const u16 m_stcCstConnectUmsSuc;				//连接 ums成功
	static const u16 m_stcCstConnectCnsFail;			//连接 cns成功
	static const u16 m_stcCstConnectCnsOk;              //连接cns失败
	static const u16 m_stcCstConnectSuc;                //连接成功
	static const u16 m_stcCstConnectFail;               //连接失败
   
    TTPSipRegistrarCfg        m_tSipRegCfg;             ///<  注册sip的配置信息
    TTPEthnetInfo             m_tServEthnetInfo;

	enum EM_ConnectState{
		emConnectNotStart,
			emConnectUmsFail,
			emConnectCnsFail,
			emConnectSuc,
			emConnectUmsSuc, 
			emConnectCnsSuc, 
	};
	EM_ConnectState                  m_emConnectState;                    //连接状态
/** @}*/ 
public:
	
	/** 获取接口指针 */
	static CCommonInterface* GetCommIF();

   /**销毁接口指针 */
    void DestroyCommIF();
    
	HWND GetRecvWnd(){return m_pMySelf->GetSafeHwnd();}
 
	virtual ~CCommonInterface();

private:
	CCommonInterface();
   
protected:
    virtual BOOL PreCreateWindow( CREATESTRUCT& cs );
    virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam); 
    
    
private:
   static  CCommonInterface*  m_pMySelf;

  
   TTPConfTemplate      m_tCurConfTemplate;         ///<当前操作的会议名称

   TCMSConf                  m_tConfInfo;

/** @}*/   
};

#define ComInterface    CCommonInterface::GetCommIF()
#define BusinessManagePtr CCommonInterface::GetCommIF()
#endif // !defined(AFX_COMMONINTERFACE_H__E6AFC64B_E6AB_4404_930B_546D1178FF87__INCLUDED_)
