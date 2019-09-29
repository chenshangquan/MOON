// confCnsLstLogic.h: interface for the CConfCnsLstLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONFCNSLSTLOGIC_H__51A443CE_70D3_45E4_8A90_D5E56C9450C7__INCLUDED_)
#define AFX_CONFCNSLSTLOGIC_H__51A443CE_70D3_45E4_8A90_D5E56C9450C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

enum EM_CnsShowState{
    emShowAll,
        emShowSpeaker,
        emShowMute,
        emShowQuiet,
        emShowOffLine,
        emShowDual,
    }; //使用菜单

class CConfCnsLstLogic : public CWndLogicBase  
{
public:
    

    static CConfCnsLstLogic*  GetLogicPtr();
	CConfCnsLstLogic();
	virtual ~CConfCnsLstLogic();

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
  * 功能:  点击离开会议
  * @return  bool
  * @remarks  
  */
   bool BtnHangupLocalCnsClick( const IArgs & arg );

  /**	 
  * 功能:  点击挂断会议
  * @return  bool
  * @remarks  
  */
   bool BtnHangupConfClick( const IArgs & arg );

 /**	 
  * 功能:  点击 麦克风
  * @return  bool
  * @remarks  
  */
   bool BtnMicClick( const IArgs & arg );

 /**	 
  * 功能:  点击 麦克风
  * @return  bool
  * @remarks  
  */
   bool BtnSpeakerClick( const IArgs & arg );


 /**	 
  * 功能:  点击 双流开关
  * @return  bool
  * @remarks  
  */
   bool BtnDbFlowClick( const IArgs & arg );
   bool BtnStopDbFlowClick( const IArgs & arg );

 /**	 
  * 功能:  点击  会场显示选项
  * @return  bool
  * @remarks  
  */
   bool BtnCnsShowOptnClick( const IArgs & arg );


   /**	 
  * 功能:  点击会议的会场cns列表中的某个条目
  * @return  bool
  * @remarks ：若为不在线的cns，则弹出呼叫菜单界面，若为在线的cns，则弹出会控菜单界面
  */
   bool BtnConfCnsItemClick( const IArgs & arg );



   /**	 
  * 功能:  点击  保存当前界面信息到文件
  * @return  bool
  * @remarks  
  */
  bool BtnSave2File( const IArgs & arg );

  bool OptDlgBtnSave2File( const IArgs & arg );

  bool CloseOptDlg( const IArgs & arg  ); 

  bool CloseCnsLstDlg( const IArgs & arg  );



//--------显示会场列表选项
   /**	 
  * 功能:  点击显示全部会场
  * @return  bool
  * @remarks  
  */
   bool OnShowAllConfCnsClick( const IArgs & arg );

   /**	 
  * 功能:  点击显示不在线会场
  * @return  bool
  * @remarks  
  */
   bool OnShowOfflineCnsClick( const IArgs & arg );


   /**	 
  * 功能:  点击显示发言会场
  * @return  bool
  * @remarks  
  */
   bool OnShowSpokesCnsClick( const IArgs & arg );


   /**	 
  * 功能:  点击显示哑音会场
  * @return  bool
  * @remarks  
  */
   bool OnShowMuteCnsClick( const IArgs & arg );

   /**	 
  * 功能:  点击显示静音会场
  * @return  bool
  * @remarks  
  */
   bool OnShowSlienceCnsClick( const IArgs & arg );

   /**	 
  * 功能:  点击显示双流会场
  * @return  bool
  * @remarks  
  */
   bool OnShowDbflowCnsClick( const IArgs & arg );


   bool  HungupConf( const IArgs & arg );

   bool  HungupLocalCns( const IArgs & arg );

   
   EM_CnsShowState GetCnsShowState() { return m_emCnsShowState; }
protected:
    
    virtual void RegMsg(); 
	virtual void UnRegMsg();
    HRESULT OnCascadeConfNotify( WPARAM wparam, LPARAM lparam);
    HRESULT OnHungupConfRsp( WPARAM wparam, LPARAM lparam);
    HRESULT OnConfStateNotify( WPARAM wparam, LPARAM lparam);
    HRESULT OnChangeSpeakerNotify( WPARAM wparam, LPARAM lparam);
    
    HRESULT OnUpdateCnsNotify( WPARAM wparam, LPARAM lparam);
    HRESULT OnRefreshCnsLstNotify( WPARAM wparam, LPARAM lparam);
    HRESULT OnSetSpeakerCnsRsp( WPARAM wparam, LPARAM lparam);
    HRESULT OnSetMuteCnsRsp( WPARAM wparam, LPARAM lparam);
    HRESULT OnSetQuietCnsRsp( WPARAM wparam, LPARAM lparam);
    HRESULT OnSetDualCnsRsp( WPARAM wparam, LPARAM lparam);
    HRESULT OnDualCnsNotify( WPARAM wparam, LPARAM lparam);
    
private:
    u16  ShowWindow( bool bShow );
    void UpdateCnsLst( BOOL bRestOffset = FALSE );
    void UpdateWnd();

    //更新显示选项信息
    void UpdateShowOption();

    void ResetLstOffset( String strLst );
    
    void InitLst();

private:

    static const String m_strShowAllCns;
    static const String m_strShowSpeakerCns;
    static const String m_strShowMuteCns;
    static const String m_strShowQuietCns;
    static const String m_strShowOffLineCns;
    static const String m_strShowDualCns;


    static CConfCnsLstLogic *m_pLogic;
    static const String m_strStcTitle;              //会场管理标题
    static const String m_strBtnCnsShowSel;         //会场显示选项
    static const String m_strBtnMic;                //麦克风
    static const String m_strBtnSpeaker;            //扬声器
    static const String m_strBtnDbFlow;             //双流
    static const String m_strBtnHungup;             //挂断会议
    static const String m_strLstCns;                //会场列表
    static const String m_strDlgCnsShowOptn;        //会场显示选项
    static const String m_strLstCnsShowOptn;
    EM_CnsShowState m_emCnsShowState;               //cns 显示状态
              
    
};

#endif // !defined(AFX_CONFCNSLSTLOGIC_H__51A443CE_70D3_45E4_8A90_D5E56C9450C7__INCLUDED_)
