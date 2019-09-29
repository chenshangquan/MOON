/*****************************************************************************
�ļ�ʵ�ֹ���: ����DUI��dialog��
�ļ���      : DUIDialog.h 
����ļ�    : UIlib.h
��ע		: ������Dialog�࣬���Ը�����Ҫ�ڴ˻�����ͨ���������ʽ�������� 
����        : �����
�汾        : V1.0  Copyright(C) 2013-2014 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/3/28      1.0         �����      ����
******************************************************************************/

#pragma once

namespace DuiLib {
 

class UILIB_API CDUIDialog: public CWindowWnd/*, public INotifyUI*/,public IDialogBuilderCallback, public IMessageFilterUI
{

public:
	/*****************************************************************************
	* ����: ����Dialog�Ƿ�ʧȥ���������
	* @param [in]  bStatus  ��TRUE ��ʾʧȥ��������أ���������  
	* @return      void 
	* @remarks	 
	-----------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��         �汾        �޸���      �޸�����
	2013/4/9       1.0         �����      ����
    ******************************************************************************/
	void SetAutoHideStatus( BOOL bStatus ){ m_bAutoHide = bStatus; } 

 
	
	/*****************************************************************************
	* ����: ���÷���
	* @param [in]  szCaseName  ������ 
	* @return   �ɹ�����  TRUE��ʧ�ܷ���FALSE
	* @remarks	��δ�������򴴽�����
	-----------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��         �汾        �޸���      �޸�����
	2013/5/2       1.0         �����      ����
    ******************************************************************************/
	BOOL DoCase( const LPCTSTR szCaseName  ); 


	/*****************************************************************************
	* ����: domodal 
	* @return   �÷�ΧֵΪ EndModal �еĲ���
	* @remarks	��δ�������򴴽�����
	-----------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��         �汾        �޸���      �޸�����
	2013/6/13      1.0         �����      ����
    ******************************************************************************/
	int DoModal(); 
	

	/*****************************************************************************
	* ����: ����domodal 
	* @param [in] domodal�ķ���ֵ
	* @return   �÷�ΧֵΪ EndModal �еĲ���
	* @remarks	��δ�������򴴽�����
	-----------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��         �汾        �޸���      �޸�����
	2013/6/13      1.0         �����      ����
    ******************************************************************************/
	void EndModal( int nResult );

	/*****************************************************************************
	* ����: �ж��Ƿ��ܱ��϶�
	* @param [BOOL]
	* @return
	* @remarks ���λ�ô��ڿؼ����б�������ڲ����϶�
	-----------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��         �汾        �޸���      �޸�����
	2014/3/25      1.0         �컪��      ����
    ******************************************************************************/
	BOOL CanBeMoved( CControlUI* pControl = NULL );

public:
	CDUIDialog(LPCTSTR szLayXml);
	~CDUIDialog(void); 


	CPaintManagerUI* GetPaintMng(){ return &m_paintMng;};   //by xhx
	



	//INotifyUI
	//virtual void Notify(TNotifyUI& msg);

	//IMessageFilterUI            preTranslateMessage()
	virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

	//winPorc
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	//�����û��Զ�����Ϣ 
	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	

	virtual UINT GetClassStyle() const; 


	//�����Զ���ؼ�����  IDialogBuilderCallback
	virtual CControlUI* CreateControl(LPCTSTR pstrClass); 


	virtual void OnFinalMessage(HWND hWnd);

private: 
	
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

 
	//���ʧȥ��������ع���
	virtual LRESULT OnActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnMouseWheel(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
 

	virtual LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);	

	virtual LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	

protected:

	//CWindowWnd
	virtual LPCTSTR GetWindowClassName() const { return _T("DUIDialog"); }


protected:
	 
	  CStdString m_strLayFile; //��ǰdlg��Ӧ��xml�ļ�
 

protected:
	CPaintManagerUI m_paintMng;
	BOOL            m_bAutoHide;

private:
	BOOL m_bContinueModal;//�Ƿ����modal ״̬
	int  m_nModalResult;
};

//////////////////////////////////////////////////////////////////////////
//
//����DUI���ӶԻ����� (�ɸ�����Ҫ��չ)
class UILIB_API CWindowChildUI : public CContainerUI
{
public:
	CWindowChildUI();
	virtual ~CWindowChildUI(){};

public:
	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);

	// 	bool SetItemIndex(CControlUI* pControl, int iIndex);
	// 	bool Add(CControlUI* pControl);
	// 	bool AddAt(CControlUI* pControl, int iIndex);	
};

}