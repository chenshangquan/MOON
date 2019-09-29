#ifndef DRAGWINDOW_HEAD_H
#define DRAGWINDOW_HEAD_H 
#include "transparenBaseWnd.h"

class CDragWindow : public CTransparentBaseWnd
{
	// Construction
public:
	CDragWindow( CRect rcList, CWnd* pWnd = NULL, UINT nID = 0 );
	//CDragWindow(CWnd* pParent = NULL);   // standard constructor
		
protected:
	//{{AFX_MSG(CDragWindow)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
public:
	static CDragWindow* GetDragWindow();
	
	// ע����Ҫ�����¼��Ĵ���
	BOOL RegisterDropWindow( CWnd* pWnd );
	// ȡ����ע��Ĵ���
    BOOL UnRegisterDropWindow(CWnd* pWnd);		
	// ����DragOverʱһֱ֪ͨ�Ĵ���	
    void SetNotifyWindow( CWnd* pWnd );
	
    /**  ��ʼ��ק
     *  @param[in] pSrcWnd Դ����
     *  @param[in] point ���λ��
     *  @param[in] pBitmap ��ק��ͼƬ
     *  @param[in] pData ��ק������
     *  @return �Ƿ�ɹ�
     */
	BOOL BeginDrag( CWnd* pSrcWnd, CPoint point, Image* pBitmap, IData* pData = NULL );
	BOOL Draging( CPoint point );
	BOOL EndDrag( CPoint point );
    CWnd* GetSrcWnd(){ return m_pSrcWnd; }
	void ClearUserData(){ m_pUserData = NULL; }

protected:
    //��õ�ǰ���ڵ���Ҫ֪ͨ�Ĵ���
    CWnd* GetActiveWindow( CPoint point );
    //��קʱ��Ϣ֪ͨ
    void ReportDragOver( CPoint point );
    
    //֪ͨNotifyWnd
    void ReportNotifyWnd( UINT message, CPoint point );

private:	
	CWnd*   m_pLastWnd;                     //�ϴξ����Ĵ���	
	IData*  m_pUserData;                    //��ק������
                	
	vector<CWnd*> m_vctWnd;                 //ע��Ĵ���	
	static CDragWindow* m_pcDragWindow;

    CPoint  m_pLastPoint;
    CWnd*   m_pSrcWnd;                      //Դ����

    CWnd*   m_pNotifyWnd;                   //DragOverʱһֱ֪ͨ�Ĵ��ڣ���ʱֻ��һ��
};

#endif