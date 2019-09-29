// scrnDisplayMenuLogic.h: interface for the CScrnDisplayMenuLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCRNDISPLAYMENULOGIC_H__27B820A9_DA78_4176_A5DB_B336FAC33906__INCLUDED_)
#define AFX_SCRNDISPLAYMENULOGIC_H__27B820A9_DA78_4176_A5DB_B336FAC33906__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CScrnDisplayMenuLogic : public CWndLogicBase  
{
public:
    static CScrnDisplayMenuLogic* GetLogicPtr(); 
    CScrnDisplayMenuLogic();
    virtual ~CScrnDisplayMenuLogic();
    
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


public:    
    void ShowMenu( u8 bScrnID, CPoint& pos  );

    void HideMenu(  );

    bool BtnSrcnSelWatch( const IArgs & arg );

    
    bool BtnCancleSrcnSelWatch( const IArgs & arg );

    bool BtnSrcnDispDual( const IArgs & arg );

    bool BtnCancleSrcnDispDual( const IArgs & arg );


    bool BtnSrcnDispLocal( const IArgs & arg );
    
    bool BtnCancleSrcnDispLocal( const IArgs & arg );

    //选看列表操作
    bool OnCnsSelViewClick( const IArgs & arg );

    bool OnIconCnsLstAddClick( const IArgs & arg );

    bool OnBtnSynthesis( const IArgs & arg );

private:
    void UpdateMenu( u8 bSrcnID );//更新menu

    void UpdateScrnSelView( TScreenInfo& tScrnInfo);
    void UpdateScrnSelDual( TScreenInfo& tScrnInfo);
    void UpdateScrnSelLocal( TScreenInfo& tScrnInfo);


    //选看列表
    void RefreshSelViewLst();
    
	void ResetSelViewList();

protected:  

    HRESULT OnScreenStateNotify( WPARAM wparam, LPARAM lparam );

    HRESULT OnConfStateNotify( WPARAM wparam, LPARAM lparam );

    
    HRESULT OnSelViewRsp( WPARAM wparam, LPARAM lparam );    
    HRESULT OnCancleSelViewRsp( WPARAM wparam, LPARAM lparam );
    
    HRESULT OnSelTVSViewRsp( WPARAM wparam, LPARAM lparam );    
    HRESULT OnCancleSelTVSViewRsp( WPARAM wparam, LPARAM lparam );

    HRESULT OnSelDualRsp( WPARAM wparam, LPARAM lparam );    
    HRESULT OnCancleSelDualRsp( WPARAM wparam, LPARAM lparam );


    HRESULT OnSelLocalRsp( WPARAM wparam, LPARAM lparam );    
    HRESULT OnCancleSelLocalRsp( WPARAM wparam, LPARAM lparam );

protected: 
    virtual void RegMsg(); 
    virtual void UnRegMsg();

    static CScrnDisplayMenuLogic *m_pLogic;

    u8     m_bScrnID;

    const  static String         m_strDlgSelView;
    const  static String         m_strLstSelView;		            //选看列表 


};

#endif // !defined(AFX_SCRNDISPLAYMENULOGIC_H__27B820A9_DA78_4176_A5DB_B336FAC33906__INCLUDED_)
