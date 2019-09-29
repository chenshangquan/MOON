/*****************************************************************************
ģ����      : CBaseWindowWnd
�ļ���      : BaseWindowWnd.h
����ļ�    : 
�ļ�ʵ�ֹ���: ͨ�ý��洰�ڻ���
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/5/22     1.0         ����ӡ      ����
******************************************************************************/
#ifndef BASEWINDOWWND_H
#define BASEWINDOWWND_H

namespace DuiLib {
	class CWindowWnd;
	class INotifyUI;
	class IMessageFilterUI;
	class IDialogBuilderCallback;
}

class UILIB_API CBaseWindowWnd : public CWindowWnd, public INotifyUI, public IMessageFilterUI, public IDialogBuilderCallback
{
public:
	CBaseWindowWnd();
	virtual ~CBaseWindowWnd();

	virtual void OnFinalMessage(HWND hWnd);
	virtual UINT GetClassStyle() const;
	virtual void Init();
	virtual CControlUI* CreateControl(LPCTSTR pstrClass);
	virtual LRESULT MessageHandler( UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled );
	virtual LRESULT OnClose( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
	virtual LRESULT OnDestroy( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );

#if defined(WIN32) && !defined(UNDER_CE)
	virtual LRESULT OnNcActivate( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
	virtual LRESULT OnNcCalcSize( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
	virtual LRESULT OnNcPaint( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
	virtual LRESULT OnNcHitTest( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
	virtual LRESULT OnGetMinMaxInfo( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
	virtual LRESULT OnMouseWheel( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
#endif

	virtual LRESULT OnSize( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );	
	virtual LRESULT OnSysCommand( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
	virtual LRESULT OnCreate( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
	virtual LRESULT OnKeyDown( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
	virtual LRESULT OnKillFocus( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
	virtual LRESULT OnSetFocus( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
	virtual LRESULT OnLButtonDown( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
	virtual LRESULT OnLButtonUp( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
	virtual LRESULT OnMouseMove( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
	virtual LRESULT HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam );
	virtual LRESULT HandleCustomMessage( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );

protected:
	virtual const TCHAR* GetSkinFolder();
	virtual const TCHAR* GetSkinFile() = 0;

	virtual LRESULT ResponseDefaultKeyEvent(WPARAM wParam);

protected:
	CPaintManagerUI m_cPaintManager;
};

#endif // BASEWINDOWWND_H