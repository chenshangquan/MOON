/*****************************************************************************
ģ����      : �б�����
�ļ���      : TransparentListSlider.h
����ļ�    : TransparentListSlider.cpp transparenBaseWnd.h
�ļ�ʵ�ֹ���: �������б�������ʾ�б�ǰλ��
����        : Ф��Ȼ
�汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
  ��  ��      �汾        �޸���      �޸�����
2012/11/28    1.0         Ф��Ȼ        ����
******************************************************************************/
#if !defined(AFX_TRANSPARENTLISTSLIDER_H__16B233EA_D0F5_459B_9D6C_A50C0DC83B12__INCLUDED_)
#define AFX_TRANSPARENTLISTSLIDER_H__16B233EA_D0F5_459B_9D6C_A50C0DC83B12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "transparenBaseWnd.h"

class CTransparentListSlider : public CTransparentBaseWnd  
{
private:
	enum EmMoveBtnStatus // ��ť״̬
    {
        emStatusMoveBtnNormal = 0,
		emStatusMoveBtnDown
	};
public:
    CTransparentListSlider( CString strName = "", CRect rcWnd = CRect(0,0,0,0), CWnd* pParentWnd = 0, UINT nID = 0, 
		DWORD dStyle = 0, DWORD dwExStyle = 0 );
	virtual ~CTransparentListSlider();

    /**
    * ����:	�����б������ܸ߶�
	* @param [in]  nHeight �б����ݸ߶�
	* @return  ��
	* @remarks �б����������ܸ߶ȣ������б�Ի���߶�
	*/
    void SetListTotalHeight( int nHeight ){ m_nListHeight = nHeight; }

    /**
    * ����:	�����б�Y��ƫ����
	* @param [in]  nOffset ƫ����
	* @return  ��
	* @remarks 
	*/
    void SetListYOffset( int nOffset ){ m_nListYOffset = nOffset; }

    /**
    * ����:	���ö�Ӧ�б�ָ��
	* @param [in]  pWnd �б�ָ��
	* @return  ��
	* @remarks 
	*/
    void SetListWnd( CWnd* pWnd ){ m_pListWnd = pWnd; }

    /**
    * ����:	���û������Ƿ�һֱ��ʾ
	* @param [in]  bAlwaysShow �Ƿ�һֱ��ʾ
	* @return  ��
	* @remarks FALSEʱ��ֻ���б��ƶ�ʱ����ʾ
	*/
    void SetAlwaysShow( BOOL bAlwaysShow ){ m_bAlwaysShow = bAlwaysShow; }

    /**
    * ����:	���û�������ͼ
	* @param [in]  ��ͼ·������ͼ��ԴID
	* @return  ��
	* @remarks 
	*/
    void SetImage( CString strImageFolder );

    void SetImage( CString strImageTop, CString strImageMiddle, CString strImageBottom,
                   CString strBkTop = "", CString strBkMiddle = "", CString strBkBottom = "");
    
    void SetImage( UINT nImgNormalUp, UINT nImgNormalCenter, UINT nImgNormalDown, 
        UINT nImgHilightUp, UINT nImgHilightCenter, UINT nImgHilightDown, 
        UINT nImgBkUp, UINT nImgBkCenter, UINT nImgBkDown, const CString& strImgType);
protected:
    //{{AFX_MSG(CTransparentListSlider)
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );
    afx_msg void OnSize(UINT nType, int cx, int cy);
    //}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    /**
    * ����:	���������λ�úͳ���
	* @param [in]  nAllHeight �б��߶ȣ���������󳤶�
    * @param [in]  nSliderMiniHeight ������С����
    * @param [out] nSliderPos ������ʼλ��
    * @param [out] nSliderHeight ��������
	* @return  ��
	* @remarks 
	*/
    void CalSliderPos( int nAllHeight, int nSliderMinHeight, int& nSliderPos, int& nSliderHeight );

	void CalSliderPos( int nAllHeight, int nListDlgHeight, int nSliderMinHeight, int& nSliderPos, int& nSliderHeight );

	BOOL MoveButtonUpdate(CPoint point); //���������ƶ� ��ť   ���Ƶ����

private:
    int      m_nListHeight;  //�б������ܸ߶�
    int      m_nListYOffset; //�б�Y��ƫ����

    CRect    m_rctSlider;    //��������rect

    BOOL     m_bLButtonDown;
    CPoint   m_ptMouseDown;  //���������

    BOOL     m_bAlwaysShow;  //�Ƿ�һֱ��ʾ

    CWnd*    m_pListWnd;     //��Ӧ�б�ָ��

    //��������ͼ
    Image   *m_pImgSliderBkUp;
    Image   *m_pImgSliderBkCenter;
	Image   *m_pImgSliderBkDown;
	
    Image   *m_pImgSliderNormalUp;
    Image   *m_pImgSliderNormalCenter;
	Image   *m_pImgSliderNormalDown;
    
    Image   *m_pImgSliderHilightUp;
    Image   *m_pImgSliderHilightCenter;
	Image   *m_pImgSliderHilightDown;

	//�� ���ƶ���ͼ
    Image   *m_pImgUpMove;
	Image   *m_pImgUpMoveDown;
	
    Image   *m_pImgDownMove;
    Image   *m_pImgDownMoveDown;

	EmMoveBtnStatus m_emUpMoveStatus;
	EmMoveBtnStatus m_emDownMoveStatus;

	CRect	m_cUpMoveIconRect;
	CRect	m_cDownMoveIconRect;

    int      m_nBkgImgOffset; //���������뻬�����

    const static CString strNormalTop;
    const static CString strNormalMiddle;
    const static CString strNormalBottom;
    const static CString strHilightTop;
    const static CString strHilightMiddle;
    const static CString strHilightBottom;
    const static CString strBkTop;
    const static CString strBkMiddle;
    const static CString strBkBottom;
	const static CString strBkUpMove;
	const static CString strBkDownMove;
	const static CString strBkUpMoveDown;
	const static CString strBkDownMoveDown;

};

#endif // !defined(AFX_TRANSPARENTLISTSLIDER_H__16B233EA_D0F5_459B_9D6C_A50C0DC83B12__INCLUDED_)
