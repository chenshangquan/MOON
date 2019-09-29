/*****************************************************************************
ģ����      : ͨ����ͼ�б�
�ļ���      : TransparentViewList.h
����ļ�    : iList.h transparenBaseWnd.h TransparentListSlider.h
�ļ�ʵ�ֹ���: ͨ���б���ع��ܣ��б���Ժ������򻬶���������������������
����        : Ф��Ȼ
�汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
  ��  ��      �汾        �޸���      �޸�����
2012/11/29    1.0         Ф��Ȼ        ����
******************************************************************************/
#if !defined(AFX_TRANSPARENTVIEWLIST_H__6C136C36_FA5A_4C4C_841A_0F4F2827D2FE__INCLUDED_)
#define AFX_TRANSPARENTVIEWLIST_H__6C136C36_FA5A_4C4C_841A_0F4F2827D2FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "transparenBaseWnd.h"
#include "iList.h"
#include "TransparentListSlider.h"
#include "TransparentListHoriSlider.h"

class CTransparentViewList : public CTransparentBaseWnd, public IList 
{
public:
    /**
    * ����: �б��캯��
    * @param [in]  rcWnd  ����λ�ô�С
    * @param [in]  pWnd  ���ڵĸ�����
    * @param [in]  nID ���ڵ�ID
    * @param [in]  dwStyle  ����style    
    * @param [in]  dwExStyle  ��չstyle
    * @remarks
    */
    CTransparentViewList( CString strName = "", CRect rcWnd = CRect(0,0,0,0), CWnd* pWnd = 0, UINT nID = 0, 
        DWORD dStyle = 0, DWORD dwExStyle = 0 );
    
    virtual ~CTransparentViewList();

    /**
    * ����:	��Ӧ�б����¼�
	* @param [in]  ͬOnLButtonUp����
	* @return  ��
	* @remarks �ú����������������أ��û�������Ӧ����¼�
               Ĭ�ϵ���¼���Ӧ����CListFuncManage����ע��
	*/
    virtual void Clicked( UINT nFlags, CPoint point );

    void SetDragEnable( BOOL bDrag );
    BOOL GetDragEnable() { return m_bDragEnable; }
    
    /**
    * ����:	�����б�ƫ����
	* @param [in]  nOffset/point ƫ��λ��
	* @return  ��
	* @remarks 
	*/
    void SetXOffset( int nOffset );
    void SetYOffset( int nOffset );
    int  GetYOffset();
    void SetListOffset( CPoint point );
    
    //������Ƿ�ѡ��
    void SetClickNoSel( BOOL bSel );
    BOOL IsClickNoSel() { return m_bClickNoSel; }

    void SetMultiSel( BOOL bMulti );
    BOOL IsMultiSel() { return m_bMultiSel; }
    
    //����ѡ����
    void ResetSelItem( BOOL bResetOffset = FALSE );
    /**
    * ����:	���õ�ǰѡ����Ŀ
	* @param [in]  dwDataKey ��Ŀ���ݵ�Key
	* @return  ��
	* @remarks  ��Ŀ��Ҫ��IDate
	*/
    void SetSelItem( unsigned long dwDataKey ); 
    IBaseItem* GetSelItem();
 
    //�����б���ͼƬ
    void SetImage( CString strImageFolder );
    
    //void SetImage( UINT nImgTopLeft, UINT nImgTopCenter, UINT nImgTopRight, UINT nImgCenterLeft, 
    //    UINT nImgCenterRight, UINT nImgBottomLeft, UINT nImgBottomCenter, UINT nImgBottomRight, UINT nImageBK, const CString& strImgType = "PNG" );

    //���ù�����ͼƬ
    void SetVertSliderImage( UINT nImgNormalUp, UINT nImgNormalCenter, UINT nImgNormalDown, UINT nImgHilightUp, UINT nImgHilightCenter, 
        UINT nImgHilightDown, UINT nImgBkUp, UINT nImgBkCenter, UINT nImgBkDown, const CString& strImgType = "PNG" );
    void SetHoriSliderImage( UINT nImgNormalLeft, UINT nImgNormalCenter, UINT nImgNormalRight, UINT nImgHilightLeft, UINT nImgHilightCenter, 
        UINT nImgHilightRight, UINT nImgBkLeft, UINT nImgBkCenter, UINT nImgBkRight, const CString& strImgType = "PNG" );
    
    //Image* MosaicListImage();
    
    void SetBkgColor( Color colorBkg, BOOL bInvalidate = FALSE );

    /**
    * ����:	������������λ��
	* @param [in]  ptOffset ƫ��λ��
	* @return  ��
	* @remarks ����������б����Ͻǵ�ƫ��λ��
	*/
    void SetVertSliderOffsetPos( CPoint ptOffset );
     /**
    * ����:	���úỬ����λ��
	* @param [in]  ptOffset ƫ��λ��
	* @return  ��
	* @remarks ����������б����½ǵ�ƫ��λ��
	*/
    void SetHoriSliderOffsetPos( CPoint ptOffset );
    
	void Clear();

	//�����б��Ƿ���ҪOver״̬
	void SetListOver( BOOL bNeedOver ){ m_bNeedOver = bNeedOver; }

    //���ö��ѡ����
    void SetMultiSelSet( set<unsigned long> setMultiSel );
    void ClearAllSel();

protected:
    void Draw( IArgs* pArgs );
    void DrawUI( Graphics* pGraphics, CWnd* pParent );

    CRect GetFrameInScreen( IItemList* pList );
    
    CRect GetListRect();
    BOOL IsReadyForDrag();
    void SetSelItemStatus( EmItemStatus emStatus );
    //int  GetOffsetHeight( int nIndex );
    //void ClearAllSel();
    
    void ListMove();
    void ListAutoMove();

    void CheckXOffset();
    void CheckYOffset();
    virtual void ListMouseMove(UINT nFlags, CPoint point);


protected:
    //{{AFX_MSG(CTransparentViewList)
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnTimer(UINT nIDEvent);    
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT	OnUpdateProgress( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT	OnDragOver( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnDragLeave( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT	OnDragEnd( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT	OnMouseWheels( WPARAM wParam, LPARAM lParam );
    LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
    //}}AFX_MSG
	afx_msg LRESULT OnMouseLeave( WPARAM wParam, LPARAM lParam );  
	afx_msg LRESULT OnMouseHover( WPARAM wParam, LPARAM lParam );
	DECLARE_MESSAGE_MAP()

protected:
    CRect   m_rctDlg;                      //�б��Rect
    CRect   m_rctList;	                   //�����б�����Rect	
    int     m_nTotalYOffset;               //��ǰ�ܵ�Y��ƫ����
    int     m_nTotalXOffset;               //��ǰ�ܵ�X��ƫ����
    CPoint  m_ptMouseLast;                 //���֮ǰλ��
    CPoint  m_ptMouseNow;                  //��굱ǰλ��
    CPoint  m_ptMouseDown;                 //������µ�λ��
    int     m_nMoveSpeed;                 
    BOOL    m_bLBtnDown;
	IItemList*   m_pMouseHoverItem;		   //��ǰ��꾭������Ŀ 2013.5.6  jyy
    IItemList*   m_pSelItem;               //��ǰѡ��
    IItemList*   m_pLastItem;
    unsigned long m_dwSelDataKey;          //ѡ��Item����������

    IItemList*   m_pDragOverItem;          //��ק��������Ŀ
    
    BOOL    m_bDragEnable;                 //�Ƿ�������ק
    BOOL    m_bClickNoSel;                 //������Ƿ���Ŀ��Ϊ��ѡ��
    BOOL    m_bMultiSel;                   //�Ƿ���ѡ��
	BOOL    m_bNeedOver;				   //�Ƿ���ҪOver״̬��ʾ
	BOOL    m_bMouseTrack;				   //�Ƿ������׷��

    CTransparentListSlider*     m_pVertSlider; //���������
    CTransparentListHoriSlider* m_pHoriSlider; //���������
    
    const static CString strBkgImg;
    const static CString strVertSliderImg;
    const static CString strHoriSliderImg;
    /*//����ͼƬ
    Image   *m_pImgTopLeft;
    Image   *m_pImgTopCenter;
    Image   *m_pImgTopRight;	
    Image   *m_pImgCenterLeft;
    Image   *m_pImgCenterRight;
    Image   *m_pImgBottomLeft;
    Image   *m_pImgBottomCenter;
    Image   *m_pImgBottomRight;
    */
    Color   m_cBkgColor;                 //������ɫ
    
};

#endif // !defined(AFX_TRANSPARENTVIEWLIST_H__6C136C36_FA5A_4C4C_841A_0F4F2827D2FE__INCLUDED_)
