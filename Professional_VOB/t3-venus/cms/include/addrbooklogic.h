// addrbooklogic.h: interface for the CAddrBookLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADDRBOOKLOGIC_H__D29112E1_0564_4B11_9EB0_29FB5EA6F4E2__INCLUDED_)
#define AFX_ADDRBOOKLOGIC_H__D29112E1_0564_4B11_9EB0_29FB5EA6F4E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CAddrBookLogic : public CWndLogicBase
{
public:
	CAddrBookLogic();
	virtual ~CAddrBookLogic();

	static CAddrBookLogic* GetLogicPtr();

public:
	virtual bool RegCBFun();
	virtual bool UnRegFunc();
	virtual void RegMsg();
	
    /**	 
	* 功能:  清空所有状态和数据
	* @return   
	* @remarks	 
	*/
    virtual void Clear();

protected:	

	bool InitWnd( const IArgs & args );
	bool OnBtnLocalAddr( const IArgs& args );
	bool OnBtnGlobalAddr( const IArgs& args );

	//点击选中按钮
	bool OnSelAddrItem( const IArgs& args );

	bool OnUnSelAddrItem( const IArgs& args );

	//返回上一层
	bool OnBtnBack( const IArgs& args );
	//打开多会场界面
	bool OnMultiCall( const IArgs& args );
	
	//点击呼叫多会场
	bool OnCallMultiCn( const IArgs& args );
    //点击取消
	bool OnCancelMulti( const IArgs& args );
	//点击地址簿条目
	bool OnClickAddrItem( const IArgs& args );
	bool OnClickAddrGroup( const IArgs& args );

	bool OnAddToMultiList( const IArgs& args );

	//添加进多会场呼叫列表的组全部展开
	void AddGroupToMultiList( TAddrItem tItem );
	
	bool OnDelFromMultiList( const IArgs& args );
    //点击进入组
    bool OnEnterAddrGroup( const IArgs& args );

	bool OnSearchEditChange( const IArgs& args );
	bool OnDragEnd( const IArgs& args );
	bool OnDragItemOut( const IArgs& args );

    bool OnBtnRefresh( const IArgs & arg );
    //点击全选------2013.10.18  jyy全选按钮已放弃使用,xml中修改
    bool OnBtnSelectAll( const IArgs & arg );
    bool OnBtnUnSelectAll( const IArgs & arg );
    //点击显示选择列表
    bool OnBtnAddrShowOptn( const IArgs & arg );

	LRESULT UpdateLocalAddrBook( WPARAM wParam, LPARAM lParam );
	LRESULT UpdateGlobalAddrBook( WPARAM wParam, LPARAM lParam );

	LRESULT OnConfStateNotify( WPARAM wParam, LPARAM lParam );

	LRESULT OnWaitRefreshOverTime( WPARAM wParam, LPARAM lParam );

    //更新显示出的列表
	void UpdateShowList();
	void UpdateLocalAddrList();
	void UpdateGlobalAddrList();
	void UpdateGroupMemberList( u32 dwGroupIndex );

    //更新多选列表
    void UpdateMultiCallList();   
	void UpdateAddrTitle();

    //更新显示选择列表
    void UpdateShowOption();
    void GetOptnShowList( vector<TAddrItem>& vctList );

    bool OnAddrOptnShowAll( const IArgs & arg );
    bool OnAddrOptnShowGroup( const IArgs & arg );
    bool OnAddrOptnShowOnline( const IArgs & arg );
    bool OnAddrOptnShowOffline( const IArgs & arg );
	
	bool OnCloseDlg( const IArgs & arg );

    //点击地址簿时根据是否为PC版,进行位置设置 dyy
    void SetAddrbookPosByVersion(String SchemeType);

    //更新全选按钮的状态
    void UpdateAllSelButton( BOOL bInLocalList = TRUE );

    //设置列表选中项的值，避免刷新整个列表
    void SetAddrListSelValue( Data_AddrItemInfo& ItemInfo, String strWndName, const IWndTree* pWndTree );
	
private: 
	vector<TAddrItem> m_vctLocalList;            //本地地址簿列表
	vector<TAddrItem> m_vctEntryList;            //本地地址簿所有条目
	vector<TAddrItem> m_vctGlobalList;           //全局地址簿列表
	vector<TAddrItem> m_vctGroupMemberList;      //分组成员列表
	vector<TAddrItem> m_vctMultiCallList;        //多会场呼叫列表
	vector<TAddrItem> m_vctSearchList;           //搜索到的列表
	vector<TAddrItem> m_vctShowList;             //当前实际显示的列表
    vector<TAddrItem> m_vctSelGroupList;         //添加的组列表，用于全选

	vector<s32>       m_vctListOffset;           //记录每一层列表偏移量
    
	BOOL        m_bGlobalAddr; //是否在全局地址簿界面
	BOOL        m_bInConf;
    BOOL        m_bSearchEdit;
	
	BOOL        m_bMultiCall;  //是否在多会场呼叫界面
	TAddrItem   m_SelItem;     //选中条目
	TGroupInfo  m_SelGroup;    //当前所在组
 
    EM_AddrShowState m_emAddrShowState;    //筛选状态

	static CAddrBookLogic *m_pAddrBookLogic;

	static const String m_strDlgNormal;
	static const String m_strListLocalAddr;
	static const String m_strListGlobalAddr;
	static const String m_strBtnBack;
	static const String m_strStcTitle;
	static const String m_strEdtSearch;
	static const String m_strBtnLocalAddr;
	static const String m_strBtnGlobalAddr;
	static const String m_strBtnMultiCall;
	static const String m_strDlgMultiCall;
	static const String m_strListMultiCall;
	static const String m_strBtnCall;
	static const String m_strLetterIndex;
	static const String m_strBtnRefresh;
    static const String m_strBtnAddrShowEx;
    static const String m_strLstAddrShowOptn;
    static const String m_strBtnAllSel;
};

#endif // !defined(AFX_ADDRBOOKLOGIC_H__D29112E1_0564_4B11_9EB0_29FB5EA6F4E2__INCLUDED_)
