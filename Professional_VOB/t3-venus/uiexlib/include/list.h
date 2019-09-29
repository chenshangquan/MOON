#ifndef LIST_HEAD_H
#define LIST_HEAD_H

#include "iList.h"
#include "transparenBaseWnd.h" 
#include "TransparentListSlider.h"
#include "letterIndex.h"

class CTransparentList : public CTransparentBaseWnd, public IList
{
public:
	const static CString strTopLeft;
	const static CString strTopCenter;
	const static CString strTopRight;
	const static CString strCenterLeft;
	const static CString strCenterRight;
	const static CString strBottomLeft;
	const static CString strBottomCenter;
	const static CString strBottomRight;
    const static CString strSliderTop;
    const static CString strSliderMiddle;
    const static CString strSliderBottom;

    /**
    * ����: �б��캯��
    * @param [in]  strName  �б�����
    * @param [in]  rcWnd  ����λ�ô�С
    * @param [in]  pWnd  ���ڵĸ�����
    * @param [in]  nID ���ڵ�ID
    * @param [in]  dwStyle  ����style   
    * @param [in]  dwExStyle  ��չstyle
    * @remarks
    */
	CTransparentList( CString strName = "", CRect rcWnd = CRect(0,0,0,0), CWnd* pWnd = 0, CString strUI = "", UINT nID = 0, 
		DWORD dStyle = 0, DWORD dwExStyle = 0 );
	
	virtual ~CTransparentList();
	
    /**
    * ����:	��Ӧ�б����¼�
	* @param [in]  ͬOnLButtonUp����
	* @return  ��
	* @remarks �ú����������������أ��û�������Ӧ����¼�
               Ĭ�ϵ���¼���Ӧ����CListFuncManage����ע��
	*/
	virtual void Clicked( UINT nFlags, CPoint point );

    /**
    * ����:	�����б��Ƿ�������ק
	* @param [in]  nOffset ƫ����
	* @return  ��
	* @remarks Ĭ��TRUE
	*/
	void SetDragEnable( BOOL bDrag );
	BOOL GetDragEnable() { return m_bDragEnable; }
	
    /**
    * ����:	�����б�Y��ƫ����
	* @param [in]  nOffset ƫ����
	* @return  ��
	* @remarks
	*/
	void SetYOffset( int nOffset );
	int  GetYOffset();

    /**
    * ����:	�����б��ײ�λ��
	* @return  ��
	* @remarks
	*/
	void SetBottomOffset();

    /**
    * ����:	������Ŀ��������Ƿ�ѡ��
	* @param [in]  bSel �Ƿ�����ѡ��
	* @return  ��
	* @remarks Ĭ��FALSE����Ŀ��������
	*/
	void SetClickNoSel( BOOL bSel );
	BOOL IsClickNoSel() { return m_bClickNoSel; }

    /**
    * ����:	�����б����ʱ�Ƿ��ý���
	* @param [in]  bFocus �Ƿ��ý���
	* @return  ��
	* @remarks Ĭ��TRUE
	*/
	void SetClickFocus( BOOL bFocus );
	BOOL IsClickFocus() { return m_bClickFocus; }

    /**
    * ����:	�����б��Ƿ�������ѡ��
	* @param [in]  bMulti �Ƿ�������ѡ��
	* @return  ��
	* @remarks Ĭ�ϲ��ܸ��������Ŀ
	*/
	void SetMultiSel( BOOL bMulti );
	BOOL IsMultiSel() { return m_bMultiSel; }

    /**
    * ����:	���õ�ǰѡ����Ŀ
	* @param [in]  dwDataKey ��Ŀ���ݵ�Key
	* @return  ��
	* @remarks  ��Ŀ��Ҫ��IDate
	*/
	void SetSelItem( unsigned long dwDataKey, BOOL bResetOffset = TRUE );	
	IBaseItem* GetSelItem();

    /**
    * ����:	����ѡ����Ŀ
	* @param [in]  bResetOffset �Ƿ�ͬʱ����λ��
	* @return  ��
	* @remarks  �����б����ݸ���֮��
	*/
    void ResetSelItem( BOOL bResetOffset = FALSE );

    /**
    * ����:	���û������Ƿ�һֱ��ʾ
	* @param [in]  bAlwaysShow �Ƿ�һֱ��ʾ
	* @return  ��
	* @remarks Ĭ��FALSE��ֻ���б��ƶ�ʱ����ʾ
	*/
    void SetSliderAlwaysShow( BOOL bAlwaysShow ){ m_bAlwaysShowSlider = bAlwaysShow; }

    /**
    * ����:	���û�����λ��
	* @param [in]  rectSlider ������λ��
	* @return  ��
	* @remarks ����Ϊ�б������ϵ����λ��
	*/
    void SetSliderRect( CRect rectSlider );
    
    void SetBkgColor( Color colorBkg, BOOL bInvalidate = FALSE );

    /**
    * ����:	�����б���ͼƬ
	* @param [in]  strImageFolder ͼƬĿ¼·��
	* @return  ��
	* @remarks
	*/ 
	void SetImage( CString strImageFolder  , BOOL bInvalidate = FALSE ,EmImgCompType emImgType = emImgCompMasic);

	void SetImage( UINT nImgTopLeft, UINT nImgTopCenter, UINT nImgTopRight, UINT nImgCenterLeft, 
		UINT nImgCenterRight, UINT nImgBottomLeft, UINT nImgBottomCenter, UINT nImgBottomRight, UINT nImageBK, const CString& strImgType = "PNG" );

	Image* MosaicListImage();

    //���ù�����ͼƬ
    void SetSliderImage( UINT nImgNormalUp, UINT nImgNormalCenter, UINT nImgNormalDown, UINT nImgHilightUp, UINT nImgHilightCenter, 
        UINT nImgHilightDown, UINT nImgBkUp, UINT nImgBkCenter, UINT nImgBkDown,  const CString& strImgType = "PNG" );

    void SetSliderImage( CString strImageFolder );

	BOOL IsNeedSlider(){ return m_bNeedSlider;};

	void SetRedrawBk(BOOL bRedrawBk){ m_bRedrawBk = bRedrawBk;};                 //�б��С�ı��Ƿ��ػ汳��

    /**
    * ����:	����б�����
	* @return  ��
	* @remarks  �����б����ݸ���֮ǰ
	*/
	void Clear();

	//�����б��Ƿ���ҪOver״̬(��Ϊ��ǩҳ��Ҫ,һ���б���Ҫ)
	void SetListOver( BOOL bNeedOver ){ m_bNeedOver = bNeedOver; }

protected:
    void Draw( IArgs* pArgs );
    
	void DrawUI( Graphics* pGraphics, CWnd* pParent );

	CRect GetFrameInScreen( IItemList* pList );

	CRect GetListRect();
	BOOL IsReadyForDrag();
	void SetSelItemStatus( EmItemStatus emStatus );
	int  GetOffsetHeight( int nIndex );
	void ClearAllSel();
	
	BOOL ListMove();
	void ListAutoMove();

    void CheckYOffset();

    CPoint TransChildPoint( IItemList* pList, CPoint point );

    static void InitList();  //�б��ʼ����ֻ��һ��    

	virtual void ListMouseMove(UINT nFlags, CPoint point);
	virtual void ListKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual	void onReturnKey();
protected:
	CRect   m_rctDlg;                      //�б��Rect
	CRect   m_rctList;	                   //�����б�����Rect	
	int     m_nTotalYOffset;               //��ǰ�ܵ�Y��ƫ����
	int     m_nTotalXOffset;
	CPoint  m_ptMouseLast;
	CPoint  m_ptMouseNow;
	CPoint  m_ptMouseDown;
	int     m_nMoveSpeed;
	BOOL    m_bLBtnDown;
	IItemList*   m_pSelItem;               //��ǰѡ��
	IItemList*   m_pMouseHoverItem;       //��ǰ��꾭������Ŀ 2013.5.3  jyy
	IItemList*   m_pLastItem;
	unsigned long m_dwSelDataKey;          //ѡ��Item����������

	BOOL    m_bDragEnable;                 //�Ƿ�������ק
	BOOL    m_bClickNoSel;                 //������Ƿ���Ŀ��Ϊ��ѡ��
	BOOL    m_bClickFocus;                 //������Ƿ����ý���
	BOOL    m_bMultiSel;                   //�Ƿ�������ѡ��
    BOOL    m_bAlwaysShowSlider;           //�Ƿ�һֱ��ʾ������
    BOOL    m_bNeedSlider;                 //�Ƿ���Ҫ��ʾ������
	BOOL    m_bNeedOver;				   //�Ƿ���ҪOver״̬��ʾ
	BOOL    m_bMouseTrack;				   //�Ƿ������׷��

    CTransparentListSlider* m_pSlider;     //�б������

	CLetterIndex* m_pLetterIndex;			//��ĸ����

	//����ͼƬ
	Image   *m_pImgTopLeft;
    Image   *m_pImgTopCenter;
    Image   *m_pImgTopRight;	
    Image   *m_pImgCenterLeft;
	Image   *m_pImgCenterRight;
    Image   *m_pImgBottomLeft;
    Image   *m_pImgBottomCenter;
	Image   *m_pImgBottomRight;

	Color   m_cBkgColor;                 //������ɫ

    static  BOOL m_bInitList;            //�б��Ƿ��ʼ��
	
	BOOL	m_bRedrawBk;                 //�б��С�ı��Ƿ��ػ汳��
protected:
	//{{AFX_MSG(CTouchList)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);	
	afx_msg void OnSize(UINT nType, int cx, int cy);
	LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT	OnMouseWheels( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnUpdateProgress( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnLetterClick( WPARAM wParam, LPARAM lParam );
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	afx_msg LRESULT OnMouseLeave( WPARAM wParam, LPARAM lParam );//�л����ں����WM_MOUSELEAVE����ؼ�Ϊnormal״̬  
	afx_msg LRESULT OnMouseHover( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnBindList( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnEnableWindow( WPARAM wParam, LPARAM lParam );
	DECLARE_MESSAGE_MAP()
};
#endif