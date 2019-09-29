// confCtrlLogic.h: interface for the CConfCtrlLogic class.
//包含呼叫菜单界面  
//包含会场控制菜单（远端cns的静音 哑音等的设置）
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONFCTRLLOGIC_H__88CFE78B_FF1C_4A35_A5A4_77BEE3083150__INCLUDED_)
#define AFX_CONFCTRLLOGIC_H__88CFE78B_FF1C_4A35_A5A4_77BEE3083150__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"
enum EM_CallType
{
    emCallTpCfTemp,             //呼叫一个会议模板
    emCallTpInstantCf,          //即时会议
    emCallTpInvitCns,          //邀请原来不在会议中的cns入会
    emCallTpCallConfCns,       //呼叫会议中掉线的cns
    emCallTpPtp,//点对点
};


 

class CConfCtrlLogic : public CWndLogicBase  
{
public:
    static CConfCtrlLogic* GetLogicPtr(); 
	CConfCtrlLogic();
	virtual ~CConfCtrlLogic();

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


    void RefreshConfCnsCtrlDlg( );

 /**	 
  * 功能:  设置该单元要操作的cns的信息
  * @return  bool
  * @remarks  
  */
    void SetCallInfo(   u16 wCnsID, u16 wConfID );
    
    void SetCallInfo(  u16 wConfTempID = INVALID_WORD); 

    void SetCallInfo(  TEpAddrList  &tEqAddrLst ); 

    void SetCallInfo(  TConfCallEpAddrList  &tEqAddrLst ); 

	void SetCallInfo( TTPAlias &tAlias );
 /**	 
  * 功能:  呼叫
  * @return  bool
  * @remarks  
  */
    bool OnCallClick( const IArgs & arg );


 /**	 
  * 功能:  指定发言cns
  * @return  bool
  * @remarks  
  */
    bool OnSetSpokeCnsClick( const IArgs & arg );


      /**	 
  * 功能:  点击哑音图标
  * @return  bool
  * @remarks  
  */
   bool OnSetMuteClick( const IArgs & arg );


    /**	 
  * 功能:  点击取消哑音图标
  * @return  bool
  * @remarks  
  */
   bool OnSetUnMuteClick( const IArgs & arg );

    /**	 
  * 功能:  点击 静音图标
  * @return  bool
  * @remarks  
  */
   bool OnSetQuietClick( const IArgs & arg );


    /**	 
  * 功能:  点击 取消静音图标
  * @return  bool
  * @remarks  
  */
   bool OnSetUnQuietClick( const IArgs & arg );

   
    /**	 
  * 功能:  点击开启双流开关
  * @return  bool
  * @remarks  
  */
   bool OnStartDualClick ( const IArgs & arg );

    /**	 
  * 功能:  点击关闭双流开关
  * @return  bool
  * @remarks  
  */
   bool OnStopDualClick ( const IArgs & arg );
  

/**	 
  * 功能:  邀请cns入会
  * @return  bool
  * @remarks  
  */
   bool OnInviteCnsClick( const IArgs & arg );

 /**	 
  * 功能:  点击挂断会议c
  * @return  bool
  * @remarks  
  */
   bool OnHungupConfClick( const IArgs &arg);

    /**	 
  * 功能:  挂断会议c
  * @return  bool
  * @remarks  
  */
   bool HungupConf( const IArgs & arg );


   /**	 
  * 功能:  点击挂断cns
  * @return  bool
  * @remarks  
  */ 
   bool OnHungupCnsClick( const IArgs &arg );

  
 /**	 
  * 功能:   挂断cns
  * @return  bool
  * @remarks  
  */ 
   bool HungupCns( const IArgs & arg); 


  
  
   /**	 
  * 功能:   挂断cns
  * param [in] strMsg 要提示的消息
  * param [in] tCns 要挂断的cns信息
  * param [in] bShowCancle 是否显示取消
  * @return  bool
  * @remarks 供外部调用 
  */ 
   bool HungupLocalConf( const confID, const CString strMsg, bool bShowCancle = true, Window *pParendWnd = NULL ); 
  

   //挂断本地cns
   bool HungupLocalCns( const TConfEpID& tCns, const CString strMsg, bool bShowCancle = true ,Window *pParendWnd = NULL); 
 
   /**	 
  * 功能:  点击  保存当前界面信息到文件
  * @return  bool
  * @remarks  
  */
   bool BtnSave2File( const IArgs & arg );

   bool CloseConfCnsMenuDlg( const IArgs & arg  );
   
   bool BtnSaveConfCnsMenu2FileClick( const IArgs & arg );


   bool UserDefinedFun( const IArgs & arg );

   
   void  AdjustMenuPos ( );
protected: 
    virtual void RegMsg(); 
    virtual void UnRegMsg();

    
	/**	 
	* 功能:  单击了会议中某个cns条目
	* @return  bool
	* @remarks  
	*/
	HRESULT OnConfCnsItemClick( WPARAM wparam, LPARAM lparam );

	 /**	 
	* 功能:  单击了会议模板列表中某个模板条目
	* @return  bool
	* @remarks  
	*/ 
	HRESULT  OnConfTempItemClick( WPARAM wparam, LPARAM lparam );

	/**	 
	* 功能:  单击地址簿列表中某个条目进行呼叫
	* @return  bool
	* @remarks  
	*/  
	HRESULT OnAddrItemCallClick( WPARAM wparam, LPARAM lparam );


    //静音哑音回复
    HRESULT OnSetSpeakerCnsRsp( WPARAM wparam, LPARAM lparam);
    HRESULT OnSetMuteCnsRsp( WPARAM wparam, LPARAM lparam);
    HRESULT OnSetQuietCnsRsp( WPARAM wparam, LPARAM lparam);
    HRESULT OnSetDualCnsRsp( WPARAM wparam, LPARAM lparam);
    HRESULT OnDualCnsNotify( WPARAM wparam, LPARAM lparam);
 
    HRESULT OnConfStateNotify( WPARAM wParam, LPARAM lParam );
    HRESULT OnConfCnsListNotify( WPARAM wParam, LPARAM lParam );
   
private:
    static CConfCtrlLogic *m_pLogic;  

    //-----邀请cns入会所需信息
    // static TCnsInfo            m_tCnsInfo;    //该操作单元要操作的cns信息，包含该cns对应的静音，哑音 等状态 状态，该结构体由confCnsLstLogic单元进行赋值和更新
    static  u16                   m_wCnsID;     //要操作的cns的ID
    static  u16                   m_wConfID;    //对应的会议ID 

    TTPAlias                     m_tTPAlias;   //呼叫的别名信息

    TCnAddr                      m_tCallAddr;  //点对点呼叫的地址

    vector<TCnAddr>              m_tCnAddrList; //临时会议呼叫地址

    //开启一个临时会议所需信息/邀请cns
    static TConfCallEpAddrList    m_tEqAddrLst;

    static EM_CallType           m_emCallTp;     //呼叫类型 

    CRect       m_rectClickItem;

    String      m_strConfCnsCtrlDlg;
};

#endif // !defined(AFX_CONFCTRLLOGIC_H__88CFE78B_FF1C_4A35_A5A4_77BEE3083150__INCLUDED_)
