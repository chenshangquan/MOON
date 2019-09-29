// tvwLogic.h: interface for the CTvwLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TVWLOGIC_H__762D3553_5715_4807_AF81_CFCC9AE3E490__INCLUDED_)
#define AFX_TVWLOGIC_H__762D3553_5715_4807_AF81_CFCC9AE3E490__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

#define MAX_TVW_COUNT      5



class Data_TvwInfo : public IData
{
public:
	Data_TvwInfo() : IData( "TvwInfo" ){}
    Data_TvwInfo( TTPHduPlayReq &tTvw ) : IData( "TvwInfo" ), m_tTvwInfo( tTvw ){}
    
	IData* Clone()
    {
        Data_TvwInfo* pData = new Data_TvwInfo( m_tTvwInfo );
        pData->SetDataKey( GetDataKey() );
        return pData;
    }

	void SetData( TTPHduPlayReq& tTvw )
	{
		m_tTvwInfo = tTvw;
	}

    TTPHduPlayReq m_tTvwInfo;
};

struct TTvwCtrl
{
	String           strBtnTvw;	
	Data_TvwInfo     tTvwData;
	
	TTvwCtrl()
	{
		strBtnTvw = "";
	}
}; 

class CTvwLogic : public CWndLogicBase  
{
public: 
    static CTvwLogic* GetLogicPtr(); 
    CTvwLogic();
    virtual ~CTvwLogic(); 
    
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

    bool BtnSaveToFileClick( const IArgs & arg );
    
    //click list item
    bool  OnCnsItemClick( const IArgs & arg ) ;
    
    bool  OnTvwItemClick( const IArgs & arg ) ;
   
    //click cns list icon (add cns to tvw )
    bool  OnIconCnsLstAddClick( const IArgs & arg ) ;

    //end drag
    bool  OnEndDragToTvw( const IArgs & args );
    bool  OnEndDragFrmTvw( const IArgs & args );
	bool  OnDragOverTvw( const IArgs & args );
	bool  OnDragLeaveTvw( const IArgs & args );

    bool  ClearHudClick( const IArgs& args );   
	bool  OnTvwBtnKillFocus( const IArgs& args );
protected: 
     
	HRESULT OnRefreshCnsLstNotify( WPARAM wparam, LPARAM lparam); 
	HRESULT OnHungupConfRsp( WPARAM wparam, LPARAM lparam);

	HRESULT OnRefreshTvw( WPARAM wparam, LPARAM lparam);

	HRESULT OnPlayRsp( WPARAM wparam, LPARAM lparam);
	HRESULT OnStopRsp( WPARAM wparam, LPARAM lparam);

	void UpdateTvwLst();
	void UpdateCnsLst();

	void SetCnsInTvw( u16 wHandle, TCnsInfo tCnsInfo, BOOL bSel = FALSE );
	u16  GetFirstAddHdu(); //获取要操作的电视墙通道号
protected: 
	virtual void RegMsg(); 
    virtual void UnRegMsg();
    
private:
    
    static CTvwLogic *m_pLogic;
	u16                 m_wSelChannel;
    TTPHduPlayReq       m_tSelTvwInfo;
	static const String m_stcStrDlgTvwSet;
	static const String m_stcStrLstTvw;
	static const String m_stcStrBtnDelete;
	
	static const String m_stcStrDlgCnsLst;
	static const String m_stcStrLstCns;

	TTvwCtrl m_tTvwCtrlArray[MAX_TVW_COUNT];
};

#endif // !defined(AFX_TVWLOGIC_H__762D3553_5715_4807_AF81_CFCC9AE3E490__INCLUDED_)
