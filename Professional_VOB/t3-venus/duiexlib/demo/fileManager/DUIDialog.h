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

  
 

class CDUIDialog: public CWindowWnd, public INotifyUI,public IDialogBuilderCallback, public IMessageFilterUI
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

public:
	CDUIDialog(LPCTSTR szLayXml);
	~CDUIDialog(void); 
	

	
	virtual UINT GetClassStyle() const;

	virtual void Init();

	//�����Զ���ؼ�����  IDialogBuilderCallback
	virtual CControlUI* CreateControl(LPCTSTR pstrClass); 
	 

	virtual void OnFinalMessage(HWND hWnd);
	
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

	//INotifyUI
	virtual void Notify(TNotifyUI& msg);

	//IMessageFilterUI            preTranslateMessage()
	virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

	//winPorc
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	//�����û��Զ�����Ϣ 
	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

protected:

	//CWindowWnd
	virtual LPCTSTR GetWindowClassName() const { return _T("DUIDialog"); }


protected:
	 
	  tstring m_strLayFile; //��ǰdlg��Ӧ��xml�ļ�
 

protected:
	CPaintManagerUI m_paintMng;
	BOOL            m_bAutoHide;
};

