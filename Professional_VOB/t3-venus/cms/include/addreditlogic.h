// addreditlogic.h: interface for the CAddrEditLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADDREDITLOGIC_H__4E219334_FDE2_43A0_92EF_8168A078CBCC__INCLUDED_)
#define AFX_ADDREDITLOGIC_H__4E219334_FDE2_43A0_92EF_8168A078CBCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

enum EM_AddrBookType
{
	em_AddrBook_Normal,
	em_AddrBook_Add, 
	em_AddrBook_Modify,
};

enum EM_OperateType
{
	em_AddrBook_Copy, 
	em_AddrBook_Cut,
};


class CAddrEditLogic : public CWndLogicBase
{
public:
	CAddrEditLogic();
	virtual ~CAddrEditLogic();
	static CAddrEditLogic* GetLogicPtr();

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

	/**	 
	* 功能:  得到导入地址簿时，剩余的数量
	* @return   
	* @remarks	 
	*/
	u32 GetLoadAddrNum();

protected:	
	bool InitWnd( const IArgs & args );
	/**	 
	* 功能:  点击本地地址簿
	* @return  bool
	* @remarks  
	*/
	bool OnBtnLocalAddr( const IArgs& args );
	/**	 
	* 功能:  点击全局地址簿
	* @return  bool
	* @remarks  
	*/
	bool OnBtnGlobalAddr( const IArgs& args );
	
	/**	 
	* 功能:  点击返回
	* @return  bool
	* @remarks  
	*/
	bool OnBtnBack( const IArgs& args );
	/**	 
	* 功能:  点击添加会场
	* @return  bool
	* @remarks  
	*/
	bool OnAddEntry( const IArgs& args );
	/**	 
	* 功能:  点击添加分组
	* @return  bool
	* @remarks  
	*/
	bool OnAddGroup( const IArgs& args );
	/**	 
	* 功能:  点击保存
	* @return  bool
	* @remarks  
	*/
	bool OnSave( const IArgs& args );
	/**	 
	* 功能:  点击取消
	* @return  bool
	* @remarks  
	*/
	bool OnCancel( const IArgs& args );
	/**	 
	* 功能:  点击编辑
	* @return  bool
	* @remarks  
	*/
	bool OnEdit( const IArgs& args );

	/**	 
	* 功能:  点击本地地址簿条目
	* @return  bool
	* @remarks  
	*/
	bool OnClickAddrItem( const IArgs& args );

	/**	 
	* 功能:  点击全局地址簿条目
	* @return  bool
	* @remarks  
	*/
	bool OnClickGlobalAddrItem( const IArgs& args );

	/**	 
	* 功能:  勾选/反选 地址簿条目
	* @return  bool
	* @remarks  
	*/
	bool OnSelAddrItem( const IArgs& args );
	bool OnUnSelAddrItem( const IArgs& args );

	/**	 
	* 功能:  从选中列表中删除
	* @return  bool
	* @remarks  
	*/
	bool OnBtnDelItem( const IArgs& args );

	/**	 
	* 功能:  搜索框消息响应
	* @return  bool
	* @remarks  
	*/
	bool OnSearchEditChange( const IArgs& args );
	/**	 
	* 功能:  点击复制
	* @return  bool
	* @remarks  
	*/
	bool OnBtnCopy( const IArgs& args );
	/**	 
	* 功能:  点击剪切
	* @return  bool
	* @remarks  
	*/
	bool OnBtnCut( const IArgs& args );
	/**	 
	* 功能:  点击粘贴
	* @return  bool
	* @remarks  
	*/
	bool OnBtnPaste( const IArgs& args );
	/**	 
	* 功能:  点击撤销
	* @return  bool
	* @remarks  
	*/
	bool OnBtnRevoke( const IArgs& args );
	/**	 
	* 功能:  点击删除
	* @return  bool
	* @remarks  
	*/
	bool OnBtnDelete( const IArgs& args );
    /**	 
	* 功能:  点击单个条目删除
	* @return  bool
	* @remarks  
	*/
    bool OnBtnDeleteItem( const IArgs& args );

	bool DelAddrEntry( const IArgs& args );

	bool SaveAddrEntry();
	bool SaveAddrGroup();

	/**	 
	* 功能:  点击更新全局地址簿
	* @return  bool
	* @remarks  
	*/	
	bool OnBtnRefreshGlobalAddr( const IArgs& args );

	/**	 
	* 功能:  确定更新全局地址簿
	* @return  bool
	* @remarks  
	*/
	bool SureRefreshGlobalAddr( const IArgs& args );

	/**	 
	* 功能:  点击全选/反选 全局地址簿
	* @return  bool
	* @remarks  
	*/
	bool OnBtnSelectAll( const IArgs& args );
	bool OnBtnUnSelectAll( const IArgs& args );

	/**	 
	* 功能:  点击全局导入到本地地址簿
	* @return  bool
	* @remarks  
	*/
	bool OnBtnLoadToLocal( const IArgs& args );

	/**	 
	* 功能:  更新当前显示列表
	* @return  
	* @remarks  
	*/
	void UpdateShowList(); 
	
	void UpdateLocalAddrList();
	void UpdateGlobalAddrList();
	void UpdateAddrTitle();
	/**	 
	* 功能:  更新界面控件状态
	* @return  
	* @remarks  
	*/
	void UpdateUIState();

	void UpdateGlobalUIState();

    /**	 
	* 功能:  更新全选控件状态
	* @return  
	* @remarks  
	*/
    void UpdateAllSelButton();

	void SetAddrItemInfo( TAddrInfo& tAddrInfo, CAddrEntry& cEntry );
	/**	 
	* 功能:  获取分组成员列表
	* @param[in]  dwGroupIndex  组索引
	* @remarks  
	*/
	void GetAddrGroupMember( u32 dwGroupIndex );

	/**	 
	* 功能:  删除组及其下级组
	* @param[in]  dwGroupIndex  组索引
	* @remarks  
	*/
	void DelGroupAndLowGroup( u32 dwGroupIndex );

    /**	 
	* 功能:  获取组及其下级组
	* @param[in]  dwGroupIndex  组索引
    * @param[out] vctGroup      组及下级组列表
	* @remarks  
	*/
    void GetGroupAndLowGroup( u32 dwGroupIndex, vector<u32>& vctGroup );

	/**	 
	* 功能:  列表没有选中项通知
	* @return  bool
	* @remarks  
	*/
	bool UnSelAddrList( const IArgs& args );

    bool OnEnterAddrGroup( const IArgs& args );

    bool OnBtnAddrShowOptn( const IArgs& args );

    bool OnAddrOptnShowAll( const IArgs & arg );
    bool OnAddrOptnShowGroup( const IArgs & arg );
    bool OnAddrOptnShowOnline( const IArgs & arg );
    bool OnAddrOptnShowOffline( const IArgs & arg );

    //更新显示选择列表
    void UpdateShowOption();
    //获得筛选后的列表
    void GetOptnShowList( vector<TAddrItem>& vctCurrentList );

	/**	 
	* 功能:  从全部地址簿中导入（每次导入一条，接到回应后继续下一条） 20131212 by xhx
	* @return  
	* @remarks
	*/
	void LoadToLocal();

    //设置列表选中项的值，避免刷新整个列表
    void SetAddrListSelValue( Data_AddrItemInfo& ItemInfo, String strWndName, const IWndTree* pWndTree );


	LRESULT UpdateAddrBook(WPARAM wParam, LPARAM lParam);
	LRESULT UpdateGlobalAddrBook( WPARAM wParam, LPARAM lParam );

	LRESULT OnAddEntryNty(WPARAM wParam, LPARAM lParam);

	LRESULT OnAddGroupNty(WPARAM wParam, LPARAM lParam);

	LRESULT OnAddrModifyNty(WPARAM wParam, LPARAM lParam);

    LRESULT OnAddrOptFailed(WPARAM wParam, LPARAM lParam);

	LRESULT OnWaitRefreshOverTime( WPARAM wParam, LPARAM lParam );
	
private: 
    static CAddrEditLogic *m_pAddrEditLogic;

	CAddrBook  m_cAddrBook;
	vector<TAddrItem> m_vctLocalList;        //本地地址簿列表
	vector<TAddrItem> m_vctGlobalList;       //全局地址簿列表
	vector<TAddrItem> m_vctGroupMemberList;  //组成员列表
	vector<TAddrItem> m_vctSelectList;       //选中列表
	vector<TAddrItem> m_vctShowList;         //当前显示列表
	vector<TAddrItem> m_vctSearchList;       //搜索出的列表
	vector<TAddrItem> m_vctOperateList;      //选中且已被操作列表

	vector<s32>       m_vctListOffset;       //记录每一层列表偏移量
	
	TAddrItem         m_SelItem;             //当前选中条目
	TGroupInfo        m_SelGroup;            //当前所在组

	EM_ItemType       m_emEditType;          //编辑类型
	EM_AddrBookType   m_emAddrBookType;      //添加/修改
	EM_OperateType    m_emOperateType;       //复制/剪切
	BOOL              m_bWaitAddEntry;       //等待添加消息
	BOOL              m_bWaitAddGroup;
	BOOL              m_bGlobalAddr;         //是否在全局地址簿界面
    BOOL              m_bSearchEdit;         //是否在搜索
	BOOL              m_bLoadToLocal;        //是否有地址簿导入        20131212 by xhx
	u32               m_dwGlobalAddrIndex;   //记录要导入地址簿的序号  20131212 by xhx

    EM_AddrShowState  m_emShowState;         //筛选状态

	static const String m_strDlgAddrEdit;
	static const String m_strEdtEntryName;
	static const String m_strEdtEntryNumber;
	static const String m_strBtnEdit;

	static const String m_strBtnBack;
	static const String m_strStcTitle;
	static const String m_strBtnCopy;
	static const String m_strBtnCut;
    static const String m_strBtnPaste;
	static const String m_strBtnRefresh;
	static const String m_strBtnAllSel;
	static const String m_strBtnLoadToLocal;
	static const String m_strEdtSearch;

    static const String m_strListLocalAddr;
    static const String m_strListGlobalAddr;	
	static const String m_strListMultiSel;

    static const String m_strAddrEditOptnDlg;
    static const String m_strLstAddrShowOptn;
    static const String m_strBtnAddrShowEx;
};

#endif // !defined(AFX_ADDREDITLOGIC_H__4E219334_FDE2_43A0_92EF_8168A078CBCC__INCLUDED_)
