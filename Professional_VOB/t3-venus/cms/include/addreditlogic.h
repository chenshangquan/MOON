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
	* ����:  �������״̬������
	* @return   
	* @remarks	 
	*/
    virtual void Clear();

	/**	 
	* ����:  �õ������ַ��ʱ��ʣ�������
	* @return   
	* @remarks	 
	*/
	u32 GetLoadAddrNum();

protected:	
	bool InitWnd( const IArgs & args );
	/**	 
	* ����:  ������ص�ַ��
	* @return  bool
	* @remarks  
	*/
	bool OnBtnLocalAddr( const IArgs& args );
	/**	 
	* ����:  ���ȫ�ֵ�ַ��
	* @return  bool
	* @remarks  
	*/
	bool OnBtnGlobalAddr( const IArgs& args );
	
	/**	 
	* ����:  �������
	* @return  bool
	* @remarks  
	*/
	bool OnBtnBack( const IArgs& args );
	/**	 
	* ����:  �����ӻ᳡
	* @return  bool
	* @remarks  
	*/
	bool OnAddEntry( const IArgs& args );
	/**	 
	* ����:  �����ӷ���
	* @return  bool
	* @remarks  
	*/
	bool OnAddGroup( const IArgs& args );
	/**	 
	* ����:  �������
	* @return  bool
	* @remarks  
	*/
	bool OnSave( const IArgs& args );
	/**	 
	* ����:  ���ȡ��
	* @return  bool
	* @remarks  
	*/
	bool OnCancel( const IArgs& args );
	/**	 
	* ����:  ����༭
	* @return  bool
	* @remarks  
	*/
	bool OnEdit( const IArgs& args );

	/**	 
	* ����:  ������ص�ַ����Ŀ
	* @return  bool
	* @remarks  
	*/
	bool OnClickAddrItem( const IArgs& args );

	/**	 
	* ����:  ���ȫ�ֵ�ַ����Ŀ
	* @return  bool
	* @remarks  
	*/
	bool OnClickGlobalAddrItem( const IArgs& args );

	/**	 
	* ����:  ��ѡ/��ѡ ��ַ����Ŀ
	* @return  bool
	* @remarks  
	*/
	bool OnSelAddrItem( const IArgs& args );
	bool OnUnSelAddrItem( const IArgs& args );

	/**	 
	* ����:  ��ѡ���б���ɾ��
	* @return  bool
	* @remarks  
	*/
	bool OnBtnDelItem( const IArgs& args );

	/**	 
	* ����:  ��������Ϣ��Ӧ
	* @return  bool
	* @remarks  
	*/
	bool OnSearchEditChange( const IArgs& args );
	/**	 
	* ����:  �������
	* @return  bool
	* @remarks  
	*/
	bool OnBtnCopy( const IArgs& args );
	/**	 
	* ����:  �������
	* @return  bool
	* @remarks  
	*/
	bool OnBtnCut( const IArgs& args );
	/**	 
	* ����:  ���ճ��
	* @return  bool
	* @remarks  
	*/
	bool OnBtnPaste( const IArgs& args );
	/**	 
	* ����:  �������
	* @return  bool
	* @remarks  
	*/
	bool OnBtnRevoke( const IArgs& args );
	/**	 
	* ����:  ���ɾ��
	* @return  bool
	* @remarks  
	*/
	bool OnBtnDelete( const IArgs& args );
    /**	 
	* ����:  ���������Ŀɾ��
	* @return  bool
	* @remarks  
	*/
    bool OnBtnDeleteItem( const IArgs& args );

	bool DelAddrEntry( const IArgs& args );

	bool SaveAddrEntry();
	bool SaveAddrGroup();

	/**	 
	* ����:  �������ȫ�ֵ�ַ��
	* @return  bool
	* @remarks  
	*/	
	bool OnBtnRefreshGlobalAddr( const IArgs& args );

	/**	 
	* ����:  ȷ������ȫ�ֵ�ַ��
	* @return  bool
	* @remarks  
	*/
	bool SureRefreshGlobalAddr( const IArgs& args );

	/**	 
	* ����:  ���ȫѡ/��ѡ ȫ�ֵ�ַ��
	* @return  bool
	* @remarks  
	*/
	bool OnBtnSelectAll( const IArgs& args );
	bool OnBtnUnSelectAll( const IArgs& args );

	/**	 
	* ����:  ���ȫ�ֵ��뵽���ص�ַ��
	* @return  bool
	* @remarks  
	*/
	bool OnBtnLoadToLocal( const IArgs& args );

	/**	 
	* ����:  ���µ�ǰ��ʾ�б�
	* @return  
	* @remarks  
	*/
	void UpdateShowList(); 
	
	void UpdateLocalAddrList();
	void UpdateGlobalAddrList();
	void UpdateAddrTitle();
	/**	 
	* ����:  ���½���ؼ�״̬
	* @return  
	* @remarks  
	*/
	void UpdateUIState();

	void UpdateGlobalUIState();

    /**	 
	* ����:  ����ȫѡ�ؼ�״̬
	* @return  
	* @remarks  
	*/
    void UpdateAllSelButton();

	void SetAddrItemInfo( TAddrInfo& tAddrInfo, CAddrEntry& cEntry );
	/**	 
	* ����:  ��ȡ�����Ա�б�
	* @param[in]  dwGroupIndex  ������
	* @remarks  
	*/
	void GetAddrGroupMember( u32 dwGroupIndex );

	/**	 
	* ����:  ɾ���鼰���¼���
	* @param[in]  dwGroupIndex  ������
	* @remarks  
	*/
	void DelGroupAndLowGroup( u32 dwGroupIndex );

    /**	 
	* ����:  ��ȡ�鼰���¼���
	* @param[in]  dwGroupIndex  ������
    * @param[out] vctGroup      �鼰�¼����б�
	* @remarks  
	*/
    void GetGroupAndLowGroup( u32 dwGroupIndex, vector<u32>& vctGroup );

	/**	 
	* ����:  �б�û��ѡ����֪ͨ
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

    //������ʾѡ���б�
    void UpdateShowOption();
    //���ɸѡ����б�
    void GetOptnShowList( vector<TAddrItem>& vctCurrentList );

	/**	 
	* ����:  ��ȫ����ַ���е��루ÿ�ε���һ�����ӵ���Ӧ�������һ���� 20131212 by xhx
	* @return  
	* @remarks
	*/
	void LoadToLocal();

    //�����б�ѡ�����ֵ������ˢ�������б�
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
	vector<TAddrItem> m_vctLocalList;        //���ص�ַ���б�
	vector<TAddrItem> m_vctGlobalList;       //ȫ�ֵ�ַ���б�
	vector<TAddrItem> m_vctGroupMemberList;  //���Ա�б�
	vector<TAddrItem> m_vctSelectList;       //ѡ���б�
	vector<TAddrItem> m_vctShowList;         //��ǰ��ʾ�б�
	vector<TAddrItem> m_vctSearchList;       //���������б�
	vector<TAddrItem> m_vctOperateList;      //ѡ�����ѱ������б�

	vector<s32>       m_vctListOffset;       //��¼ÿһ���б�ƫ����
	
	TAddrItem         m_SelItem;             //��ǰѡ����Ŀ
	TGroupInfo        m_SelGroup;            //��ǰ������

	EM_ItemType       m_emEditType;          //�༭����
	EM_AddrBookType   m_emAddrBookType;      //���/�޸�
	EM_OperateType    m_emOperateType;       //����/����
	BOOL              m_bWaitAddEntry;       //�ȴ������Ϣ
	BOOL              m_bWaitAddGroup;
	BOOL              m_bGlobalAddr;         //�Ƿ���ȫ�ֵ�ַ������
    BOOL              m_bSearchEdit;         //�Ƿ�������
	BOOL              m_bLoadToLocal;        //�Ƿ��е�ַ������        20131212 by xhx
	u32               m_dwGlobalAddrIndex;   //��¼Ҫ�����ַ�������  20131212 by xhx

    EM_AddrShowState  m_emShowState;         //ɸѡ״̬

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
