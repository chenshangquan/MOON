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
	* ����:  �������״̬������
	* @return   
	* @remarks	 
	*/
    virtual void Clear();

protected:	

	bool InitWnd( const IArgs & args );
	bool OnBtnLocalAddr( const IArgs& args );
	bool OnBtnGlobalAddr( const IArgs& args );

	//���ѡ�а�ť
	bool OnSelAddrItem( const IArgs& args );

	bool OnUnSelAddrItem( const IArgs& args );

	//������һ��
	bool OnBtnBack( const IArgs& args );
	//�򿪶�᳡����
	bool OnMultiCall( const IArgs& args );
	
	//������ж�᳡
	bool OnCallMultiCn( const IArgs& args );
    //���ȡ��
	bool OnCancelMulti( const IArgs& args );
	//�����ַ����Ŀ
	bool OnClickAddrItem( const IArgs& args );
	bool OnClickAddrGroup( const IArgs& args );

	bool OnAddToMultiList( const IArgs& args );

	//��ӽ���᳡�����б����ȫ��չ��
	void AddGroupToMultiList( TAddrItem tItem );
	
	bool OnDelFromMultiList( const IArgs& args );
    //���������
    bool OnEnterAddrGroup( const IArgs& args );

	bool OnSearchEditChange( const IArgs& args );
	bool OnDragEnd( const IArgs& args );
	bool OnDragItemOut( const IArgs& args );

    bool OnBtnRefresh( const IArgs & arg );
    //���ȫѡ------2013.10.18  jyyȫѡ��ť�ѷ���ʹ��,xml���޸�
    bool OnBtnSelectAll( const IArgs & arg );
    bool OnBtnUnSelectAll( const IArgs & arg );
    //�����ʾѡ���б�
    bool OnBtnAddrShowOptn( const IArgs & arg );

	LRESULT UpdateLocalAddrBook( WPARAM wParam, LPARAM lParam );
	LRESULT UpdateGlobalAddrBook( WPARAM wParam, LPARAM lParam );

	LRESULT OnConfStateNotify( WPARAM wParam, LPARAM lParam );

	LRESULT OnWaitRefreshOverTime( WPARAM wParam, LPARAM lParam );

    //������ʾ�����б�
	void UpdateShowList();
	void UpdateLocalAddrList();
	void UpdateGlobalAddrList();
	void UpdateGroupMemberList( u32 dwGroupIndex );

    //���¶�ѡ�б�
    void UpdateMultiCallList();   
	void UpdateAddrTitle();

    //������ʾѡ���б�
    void UpdateShowOption();
    void GetOptnShowList( vector<TAddrItem>& vctList );

    bool OnAddrOptnShowAll( const IArgs & arg );
    bool OnAddrOptnShowGroup( const IArgs & arg );
    bool OnAddrOptnShowOnline( const IArgs & arg );
    bool OnAddrOptnShowOffline( const IArgs & arg );
	
	bool OnCloseDlg( const IArgs & arg );

    //�����ַ��ʱ�����Ƿ�ΪPC��,����λ������ dyy
    void SetAddrbookPosByVersion(String SchemeType);

    //����ȫѡ��ť��״̬
    void UpdateAllSelButton( BOOL bInLocalList = TRUE );

    //�����б�ѡ�����ֵ������ˢ�������б�
    void SetAddrListSelValue( Data_AddrItemInfo& ItemInfo, String strWndName, const IWndTree* pWndTree );
	
private: 
	vector<TAddrItem> m_vctLocalList;            //���ص�ַ���б�
	vector<TAddrItem> m_vctEntryList;            //���ص�ַ��������Ŀ
	vector<TAddrItem> m_vctGlobalList;           //ȫ�ֵ�ַ���б�
	vector<TAddrItem> m_vctGroupMemberList;      //�����Ա�б�
	vector<TAddrItem> m_vctMultiCallList;        //��᳡�����б�
	vector<TAddrItem> m_vctSearchList;           //���������б�
	vector<TAddrItem> m_vctShowList;             //��ǰʵ����ʾ���б�
    vector<TAddrItem> m_vctSelGroupList;         //��ӵ����б�����ȫѡ

	vector<s32>       m_vctListOffset;           //��¼ÿһ���б�ƫ����
    
	BOOL        m_bGlobalAddr; //�Ƿ���ȫ�ֵ�ַ������
	BOOL        m_bInConf;
    BOOL        m_bSearchEdit;
	
	BOOL        m_bMultiCall;  //�Ƿ��ڶ�᳡���н���
	TAddrItem   m_SelItem;     //ѡ����Ŀ
	TGroupInfo  m_SelGroup;    //��ǰ������
 
    EM_AddrShowState m_emAddrShowState;    //ɸѡ״̬

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
