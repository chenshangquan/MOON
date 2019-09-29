/*****************************************************************************
ģ����      : �б���򻬶���
�ļ���      : TransparentListHoriSlider.cpp
����ļ�    : TransparentListHoriSlider.h
�ļ�ʵ�ֹ���: �������б�������ʾ�б�ǰ����λ��
����        : Ф��Ȼ
�汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
  ��  ��      �汾        �޸���      �޸�����
2012/11/29    1.0         Ф��Ȼ        ����
******************************************************************************/
#if !defined(AFX_TRANSPARENTLISTHORISLIDER_H__13CB0A08_FEE9_4C75_8652_D39C2899C43D__INCLUDED_)
#define AFX_TRANSPARENTLISTHORISLIDER_H__13CB0A08_FEE9_4C75_8652_D39C2899C43D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "transparenBaseWnd.h"

class CTransparentListHoriSlider : public CTransparentBaseWnd
{
private:
	enum EmMoveBtnStatus // ��ť״̬
    {
        emStatusMoveBtnNormal = 0,
		emStatusMoveBtnDown
	};

public:
    CTransparentListHoriSlider( CString strName = "", CRect rcWnd = CRect(0,0,0,0), CWnd* pParentWnd = 0, UINT nID = 0, 
        DWORD dStyle = 0, DWORD dwExStyle = 0 );
	virtual ~CTransparentListHoriSlider();
    
    /**
    * ����:	�����б������ܿ��
	* @param [in]  nHeight �б����ݿ��
	* @return  ��
	* @remarks �б����������ܿ�ȣ������б�Ի�����
	*/
    void SetListTotalWidth( int nHeight ){ m_nListWidth = nHeight; }
    
    /**
    * ����:	�����б�X��ƫ����
	* @param [in]  nOffset ƫ����
	* @return  ��
	* @remarks 
	*/
    void SetListXOffset( int nOffset ){ m_nListXOffset = nOffset; }

    /**
    * ����:	���ö�Ӧ�б�ָ��
	* @param [in]  pWnd �б�ָ��
	* @return  ��
	* @remarks 
	*/
    void SetListWnd( CWnd* pWnd ){ m_pListWnd = pWnd; }
    
    /**
    * ����:	���û�������ͼ
	* @param [in]  ��ͼ·������ͼ��ԴID
	* @return  ��
	* @remarks 
	*/
    void SetImage( CString strImageFolder );
    
    void SetImage( UINT nImgNormalLeft, UINT nImgNormalCenter, UINT nImgNormalRight, 
        UINT nImgHilightLeft, UINT nImgHilightCenter, UINT nImgHilightRight, 
        UINT nImgBkLeft, UINT nImgBkCenter, UINT nImgBkRight, const CString& strImgType);  
    
protected:
    //{{AFX_MSG(CTransparentListHoriSlider)
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );
    afx_msg void OnSize(UINT nType, int cx, int cy);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
        
    /**
    * ����:	���������λ�úͿ��
	* @param [in]  nAllHeight �б��߶ȣ���������󳤶�
    * @param [in]  nSliderMiniHeight ������С����
    * @param [out] nSliderPos ������ʼλ��
    * @param [out] nSliderHeight ��������
	* @return  ��
	* @remarks 
	*/
    void CalSliderPos( int nBkgWidth, int nSliderMinWidth, int& nSliderPos, int& nSliderWidth );

	void CalSliderPos( int nBkgWidth, int nListDlgWidth, int nSliderMinWidth, int& nSliderPos, int& nSliderWidth );   

	BOOL MoveButtonUpdate(CPoint point); //���������ƶ� ��ť   ���Ƶ���ǹ�������� ���� ���Ƶ���ʾ

private:
    int      m_nListWidth;   //�б������ܿ��
    int      m_nListXOffset; //�б�X��ƫ����
    
    CRect    m_rctSlider;    //��������rect
    
    BOOL     m_bLButtonDown;
    CPoint   m_ptMouseDown;  //���������
    
    CWnd*    m_pListWnd;     //��Ӧ�б�ָ��
    
    //��������ͼ
    Image   *m_pImgSliderBkLeft;
    Image   *m_pImgSliderBkCenter;
    Image   *m_pImgSliderBkRight;

	//�� ���ƶ���ͼ
    Image   *m_pImgLeftMove;
	Image   *m_pImgLeftMoveDown;

    Image   *m_pImgRightMove;
    Image   *m_pImgRightMoveDown;

	CRect	m_cLeftMoveIconRect;
	CRect	m_cRightMoveIconRect;

	EmMoveBtnStatus m_emLeftMoveStatus;
	EmMoveBtnStatus m_emRightMoveStatus;

    Image   *m_pImgSliderNormalLeft;
    Image   *m_pImgSliderNormalCenter;
    Image   *m_pImgSliderNormalRight;
    
    Image   *m_pImgSliderHilightLeft;
    Image   *m_pImgSliderHilightCenter;
	Image   *m_pImgSliderHilightRight;

    int      m_nBkgImgOffset; //���������뻬�����

    const static CString strNormalLeft;
    const static CString strNormalMiddle;
    const static CString strNormalRight;
    const static CString strHilightLeft;
    const static CString strHilightMiddle;
    const static CString strHilightRight;
    const static CString strBkLeft;
    const static CString strBkMiddle;
    const static CString strBkRight;
	const static CString strBkLeftMove;
	const static CString strBkRightMove;
	const static CString strBkLeftMoveDown;
	const static CString strBkRightMoveDown;
};

#endif // !defined(AFX_TRANSPARENTLISTHORISLIDER_H__13CB0A08_FEE9_4C75_8652_D39C2899C43D__INCLUDED_)
