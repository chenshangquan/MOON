// dualSrcManageLogic.h: interface for the CDualSrcManageLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DUALSRCMANAGELOGIC_H__22C6B2D7_E5B2_46BF_85F6_C9F98D04792B__INCLUDED_)
#define AFX_DUALSRCMANAGELOGIC_H__22C6B2D7_E5B2_46BF_85F6_C9F98D04792B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "wndLogicBase.h"
class CDualSrcManageLogic : public CWndLogicBase   
{
public:
	CDualSrcManageLogic();
	virtual ~CDualSrcManageLogic(); 
 
	static CDualSrcManageLogic* GetLogicPtr();

public:
	virtual bool RegCBFun();
	virtual bool UnRegFunc();
	virtual void RegMsg();
	virtual void UnRegMsg();
	
    /**	 
	* 功能:  清空所有状态和数据
	* @return    
	*/
    virtual void Clear();

	bool InitWnd( const IArgs & args );

	bool BtnToSysCfg( const IArgs & args );

	bool BtnToDualConfig( const IArgs & args );

    bool OnClickDualSrcItem( const IArgs & args );

    bool OnEdit( const IArgs & args );

    bool OnSave( const IArgs & args );

    bool OnCancel( const IArgs & args );
 
protected:

    LRESULT OnVgaInfoNotify( WPARAM wParam, LPARAM lParam );
 
private:	
    static CDualSrcManageLogic *m_pLogic;

    TDualSrcInfo   m_tDualSrcInfo;
    TVgaInfo       m_tVgaInfo;         //当前演示源信息
    BOOL           m_bDefault;         //当前演示源是否默认
    int            m_nCurSelInfoIndex;    //当前演示源在m_tDualSrcInfo中的序号，以便更新时同步更新当前编辑项信息 2012.10.8 by yujinjin
    static const String m_strBtnDefDualSwitch;
    static const String m_strEdtDualName;
};

#endif // !defined(AFX_DUALSRCMANAGELOGIC_H__22C6B2D7_E5B2_46BF_85F6_C9F98D04792B__INCLUDED_)
