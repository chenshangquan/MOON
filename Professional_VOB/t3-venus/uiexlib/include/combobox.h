#ifndef TRANSPARETNCOMBOBOX_HEAD_H
#define TRANSPARETNCOMBOBOX_HEAD_H

#include "uiexBaseData.h"


class Data_ComboMenu : public IData
{
public:
    Data_ComboMenu( CString &strMenu ) : IData( "ComboMenu" ), m_strMenuInfo( strMenu ){}
    IData* Clone()
    {
        Data_ComboMenu* pData = new Data_ComboMenu( m_strMenuInfo );
        pData->SetDataKey( GetDataKey() );
        return pData;
    }
    
    CString m_strMenuInfo;
};

class CComboBoxList :public CTransparentList
{
public:
	CComboBoxList( CString strName = "", CRect rcWnd = CRect(0,0,0,0), CWnd* pWnd = 0, CString strUI = "", UINT nID = 0, 
		DWORD dStyle = 0, DWORD dwExStyle = 0 );
	virtual ~CComboBoxList();

	virtual void Clicked( UINT nFlags, CPoint point );
	virtual void ListMouseMove(UINT nFlags, CPoint point);
	virtual void ListKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	void SetComboWnd(CWnd* hComboWnd){ m_hComboWnd = hComboWnd;};
	CWnd* GetComboWnd(){ return m_hComboWnd;};
	void GoToListItem( s32 nOffset , IData * pSelData );
	void UpdateListItem( s32 nBorderIndex , s32 nOffset ,IItemList *pLastSelList );
	void UpArrowPress( s32 nItemHeight , s32 nItemShowIndex );
	void DownArrowPress( s32 nItemHeight , s32 nItemShowIndex );
	void onReturnKey();
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CComboBoxList)
	//}}AFX_MSG
	
	//DECLARE_MESSAGE_MAP()

private:
	CWnd* m_hComboWnd;
	static BOOL m_bIsRegAlgo;
	CString m_strLastMoveItem;    //��¼���һ�����ͣ������Ŀ  ��ֹ��˸
};

class CComboxDropBaseWnd : public CTransparentBaseWnd
{
public:
    CComboxDropBaseWnd( CRect rcWnd, CWnd* pWnd,DWORD dStyle,
		CString strUI,UINT nID, DWORD dwExStyle = 0,int nTrans = 255,BOOL bCanMove = FALSE, BOOL bStretchImage = TRUE );
    virtual ~CComboxDropBaseWnd();
	
	// Generated message map functions
protected:
    //{{AFX_MSG(CComboxDropBaseWnd)
    //}}AFX_MSG
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	DECLARE_MESSAGE_MAP()
	
private:

};


class CTransparentComboBox : public CTransparentBaseWnd  
{
	typedef IItem< IBaseItem, int > IItemList;
	// Construction
public:
	CTransparentComboBox( CString strName = "", CWnd* pWnd = 0, CRect rcWnd = CRect(0,0,0,0), 
		UINT nID = 0, DWORD dStyle = 0 );
	virtual ~CTransparentComboBox();
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CTransparentComboBox)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnDropListClick( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnSetFocus( WPARAM wParam, LPARAM lParam );
	//afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg LRESULT OnUpdateEditText( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnClickListIcon( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnMouseMoveShowIcon( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnComboEditChange( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnComboEditChar( WPARAM wParam, LPARAM lParam );
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()

public:
	void    InitComboControl();
	void    SetIpStyle(BOOL bIPStyle){ m_bIsIPStyle = bIPStyle;};
    void	SetImage( const CString& strImageFolder = "" );
	void	SetReadOnly( BOOL bReadOnly = TRUE );
	void	SetComboText(CString strComboText);
	CString GetComboText();								//��ͨ���combox��ȡ����
	DWORD   GetIpAddress( DWORD dwIp );					//IP���combox��ȡ����   
	void    SetIpAddress( DWORD dwIp );					//IP���combox��������   
	void	SetDropListHeight(int nListHeight){ m_nListHeight = nListHeight;};		//���������б�߶�   ����ΪĬ�ϸ߶�
	void    SetEditEdgeHeight(int nEditEdge){ m_nEditEdge = nEditEdge;};			//����Ϊͨ�ýӿ�   �༭���Ե�Ĵ�С��ȷ��Edit&List�޷�ƴ��
	void    SetItemHeight(int nListItemHeight){ m_nListItemHeight = nListItemHeight;};
	void	SetFont( unsigned int dwFontSize = 9, CString strFontFamily = ("΢���ź�"), BOOL bInvalidate = FALSE );
	void    SetImgHeight(int nListImgHeight){ m_nListImgHeight = nListImgHeight;};
	void    SetShowIcon(BOOL bIsShowListIcon){ m_bIsShowListIcon = bIsShowListIcon;};
	void    SetEnableWindow( BOOL bEnable );										//���Ʊ༭���enable״̬
	void    SetListBkgColor( Color colorBkg );
	void    SetItemSelColor( Color colorItemSel ){ m_itemSelColor = colorItemSel;};
	void	SetEditFrontLen(int nEditFrontLen);		//���ñ༭���һ�������ַ��������ƫ�� 
	void	SetEditBackLen(int nEditBackLen);		//���ñ༭��ͼ������Ҳ�ƫ�� 

	void	SetTextColor( Color colorNormal, Color colorFocus, BOOL bInvalidate = FALSE );
    void	SetDisableColor( Color colorDisable, BOOL bInvalidate = FALSE );

	BOOL	AddString(CString strString);
	BOOL	DeleteString(CString strString);
	void	UpdateComboList( std::vector<CString>* pListData, s32 nCurMoveItem = -1 );
	s32		JumpToSelItem(const CString& strEditText);			//�����Զ���ת������ѡ����    ����ƥ���к�


	void	SetListOver(BOOL bNeedOver);

	void	SetTipStr( CString strTip );
	void	SetTipFont( unsigned int dwFontSize = 12, CString strFontFamily = ("΢���ź�"), BOOL bInvalidate = FALSE );
	void	SetTipColor( Color colorTip, BOOL bInvalidate = FALSE );

	CTransparentEdit* GetEditPoint();
private:
	Image   *m_pImgBkg;

	CTransparentEdit* m_pTransEdit;
	CComboxDropBaseWnd* m_pDropWnd;
	CComboBoxList* m_pDropList;

	std::vector<CString> m_vecListData;

	CString m_strListItemFolder;   //�б��ӦĿ¼
 	CString m_strImageItemFolder;

	CString m_strComboText;    

	BOOL m_bIsIPStyle;           //�Ƿ���IP���
	CRect m_rcWnd;
	int m_nListHeight;         //�����б�߶�
	int m_nListItemHeight;     //�����б��и߶�
	int m_nListImgHeight;      //�����б���ͼ��߶�

	int m_nEditEdge;          //�༭���Ե�Ĵ�С��ȷ��Edit&List�޷�ƴ��     ���ϱ�Ե����ͬ��

	BOOL m_bIsShowListIcon;
	Color m_colorBkg;


	int m_nFontSize;
	int m_nSliderWidth;
	int m_nEditBackLen;

	BOOL m_bSetBkColor;
	Color m_itemNormalColor;
	Color m_itemSelColor;

	Color m_colorNormal;
	Color m_colorFocus;
    Color m_colorDisable;
};




#endif