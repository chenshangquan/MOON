#ifndef SLIDER_HEAD_H
#define SLIDER_HEAD_H
#include "uiexBaseData.h"
#include "transparenBaseWnd.h"

/*---------------------------------------------------------------------
* ��    �ܣ�͸��slider 
* ��    ע������ֱ��ˮƽ���������ͣ�     ����cnc����������  
* ����			�汾		�޸���		�޸ļ�¼
* 2011.12.21    1.0         �����        ����
----------------------------------------------------------------------*/

enum EmStyle{
	emStyleVert,      //��ֱ
        emStyleHorz,      //ˮƽ����
    };


class CTransparentSliderWnd: public CTransparentBaseWnd  
{
   
public:
    const static CString strNormalLeft;
    const static CString strNormalMid;
    const static CString strNormalRight;
    const static CString strHighLightLeft;
    const static CString strHighLightMid;
    const static CString strHighLightRight;
    const static CString strThumbNormal;
    const static CString strThumbPress;
    //disable
    const static CString strDisableLeft ;
    const static CString strDisableMid  ;
    const static CString strDisableRight ;
    const static CString strDisableHighLightLeft ;
    const static CString strDisableHighLightMid ;
    const static CString strDisableHighLightRight ;
    const static CString strThumbDisable ;
	//������ʾ��
    const static CString strBubble;
  

public:
    CTransparentSliderWnd( CString strName = "", CString strImg = "", CRect rcWnd = CRect(0,0,0,0), CWnd* pParentWnd = 0, UINT nID = 0, 
		DWORD dStyle = 0, DWORD dwExStyle = 0  );

	virtual ~CTransparentSliderWnd(); 

protected:
    //{{AFX_MSG(CTransparentSlideBlock)
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    //}}AFX_MSG
    afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );

    
    DECLARE_MESSAGE_MAP()

    LRESULT  DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) ;
        
public:
    void SetImage( CString strImageFolder, BOOL bInvalidate = FALSE );

    void SetStyle( EmStyle em ){ m_emStyle = em; }
    EmStyle GetStyle(){ return m_emStyle; }
   
    void GetRange( int& nMin, int& nMax ) const; 
    void SetRange( int nMin, int nMax, BOOL bRedraw = FALSE );
    
    int  GetPos( )  ; 
    void SetPos( int nPos ); 


private:
    void UpdateMaxOffSet();

    //���ݵ�ǰ��ƫ�������� slider��Ӧ��ֵ����ֵ�������Range��Χ����
    /*int*/float CalculatePos( /*int*/float nOffSet );

    //���ݵ�ǰ�����range��ֵ��������thumb ��ƫ����
    /*int*/float CalculateOffset( /*int*/float nPos );


    
    void SetThumbPos( /*int*/float nOffset );
    
    void UpdateThumbPos();

    void AdjustSlider();

		/*---------------------------------------------------------------------
	* ��    �ܣ�����ˮƽ�����slider
	* ��    ע�� 
	* ����			�汾		�޸���		�޸ļ�¼
	* 2013.1.23    1.0         �����        ����
    ----------------------------------------------------------------------*/
    void DrawHorizSlider( Graphics *pGraphics, HWND hGraphWnd);

	/*---------------------------------------------------------------------
	* ��    �ܣ�������ֱ�����slider
	* ��    ע�� 
	* ����			�汾		�޸���		�޸ļ�¼
	* 2013.1.23    1.0         �����        ����
    ----------------------------------------------------------------------*/
	void DrawVertSlider( Graphics *pGraphics, HWND hGraphWnd);



	/*---------------------------------------------------------------------
	* ��    �ܣ����ݵ�ǰ״̬����ȡ����ʱ����Ҫ��ͼƬ
	* ��    �룺
	* ��    ����pImgNormalLeft��  thumb����ĵ�ͼ
	* ��    ����pImgNormalMiddle��thumb����ĵ�ͼ
	* ��    ����pImgNormalRight�� thumb����ĵ�ͼ
	* ��    ����pImgHighLightLeft��thumb����ĵ�ͼ
	* ��    ע�� 
	* ����			�汾		�޸���		�޸ļ�¼
	* 2013.1.24    1.0         �����        ����
    ----------------------------------------------------------------------*/
	BOOL GetDrawImg( Image **pImgThumb,
					 Image **pImgNormalLeft,
					 Image **pImgNormalMiddle,
				     Image **pImgNormalRight,	
				     Image **pImgHighLightLeft,
                     Image **pImgHighLightMiddle,
                     Image **pImgHighLightRight );
protected:

   
   
    int     m_nMax;
    int     m_nMin;

    int     m_nPos;

    EmStyle m_emStyle;
    
    CPoint  m_ptMouseLast;
	CPoint  m_ptMouseNow; 
     
    RectF    m_rectfThumbRect;
    
    int     m_nMaxOffset;  //��ƫ�Ƶ���󳤶�
    BOOL    m_bLBtnDown;


    Image   *m_pImgNormalLeft;
    Image   *m_pImgNormalMiddle;
    Image   *m_pImgNormalRight;

    Image   *m_pImgHighLightLeft;
    Image   *m_pImgHighLightMiddle;
    Image   *m_pImgHighLightRight;

    Image   *m_pImgThumbNormal;
    Image   *m_pImgThumbPress;

    //disable
    Image   *m_pImgDisableLeft ;
    Image   *m_pImgDisableMid  ;
    Image   *m_pImgDisableRight ;

    Image   *m_pImgDisableHighLightLeft ;
    Image   *m_pImgDisableHighLightMid ;
    Image   *m_pImgDisableHighLightRight ;

    Image   *m_pImgThumbDisable ;  

	Image   *m_pImgBubble; 
	BOOL m_bDownInThumb;		//���down����ʱ�Ƿ���Thumb��,�����down����Thumb��,�򲻷���SLIDER_CHANGED��Ϣ
};





class CTransparentSlideBlock : public CTransparentBaseWnd
{
public:
	const static CString strBkImg;
	const static CString strBlockNormal;
	const static CString strBlockPress;
public:
	CTransparentSlideBlock( CString strName = "", CString strUI = "", CRect rcWnd = CRect(0,0,0,0), CWnd* pWnd = 0, UINT nID = 0, 
		DWORD dStyle = 0, DWORD dwExStyle = 0  );
	virtual ~CTransparentSlideBlock();
	
protected:
    //{{AFX_MSG(CTransparentSlideBlock)
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
    //}}AFX_MSG
    afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );
    DECLARE_MESSAGE_MAP()
		
public:
	void SetImage( CString strImageFolder, BOOL bInvalidate = FALSE );
	
	void BlockMove();
	void BlockAutoMove();
	void BlockAutoBack();
	
protected:
    Image   *m_pImgBkg;
	Image   *m_pImgBlockNormal;
	Image   *m_pImgBlockPress;
	
	CRect    m_cBlockRect;
	int     m_nOffset;
	int     m_nMaxOffset;
	BOOL    m_bLBtnDown;
	CPoint  m_ptMouseLast;
	CPoint  m_ptMouseNow;
	int     m_nMoveSpeed;
};




#include "AFXCMN.H"
class CTransparentSliderCtrl : public CSliderCtrl, public TransparentAssist<CTransparentSliderCtrl>
{
public:
	const static CString strNormalLeft;
	const static CString strNormalMid;
	const static CString strNormalRight;
	const static CString strHighLightLeft;
	const static CString strHighLightMid;
	const static CString strHighLightRight;
	const static CString strThumbNormal;
	const static CString strThumbPress;
	//disable
    const static CString strDisableLeft ;
    const static CString strDisableMid  ;
    const static CString strDisableRight ;
    const static CString strDisableHighLightLeft ;
    const static CString strDisableHighLightMid ;
    const static CString strDisableHighLightRight ;
    const static CString strThumbDisable ;
    // Construction
public:
    CTransparentSliderCtrl();
    CTransparentSliderCtrl( CString strImage );
    // Attributes
public:
    
    // Operations
public:
    
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CTransparentSliderCtrl)
    //}}AFX_VIRTUAL
    
    // Implementation
public:
    virtual ~CTransparentSliderCtrl();
    
    // Generated message map functions
protected:
    //{{AFX_MSG(CTransparentSliderCtrl)
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnCaptureChanged(CWnd *pWnd);
    //}}AFX_MSG
    afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );
    DECLARE_MESSAGE_MAP()
		
		
public:
    void    SetImage( CString strFolder, BOOL bInvalidate = FALSE );
	BOOL	ResetWindowSize();
protected:
    HWND    m_hParent;
	
    Image   *m_pImgNormalLeft;
    Image   *m_pImgNormalMiddle;
    Image   *m_pImgNormalRight;
	
    Image   *m_pImgHighLightLeft;
    Image   *m_pImgHighLightMiddle;
    Image   *m_pImgHighLightRight;
	
    Image   *m_pImgThumbNormal;
    Image   *m_pImgThumbPress;
	
	//disable
    Image   *m_pImgDisableLeft ;
    Image   *m_pImgDisableMid  ;
    Image   *m_pImgDisableRight ;
	
    Image   *m_pImgDisableHighLightLeft ;
    Image   *m_pImgDisableHighLightMid ;
    Image   *m_pImgDisableHighLightRight ;
	
    Image   *m_pImgThumbDisable ;
	
	
	
    enum EmStatus
    {
        emStatusNormal = 0,
			emStatusSetFocus,
    };
    EmStatus    m_emStatus;
};

#endif
