#ifndef UIEXBASEDATA_HEAD_H
#define UIEXBASEDATA_HEAD_H

#pragma warning( disable : 4786 ) 
#include <afxtempl.h>
#include <afxole.h>
#include <afxdtctl.h>
#include <map>
#include <vector>
#include <set>

#include "Shlwapi.h"
#pragma comment(lib, "Shlwapi.lib")

#define iterator _iterator

//#define WM_TOUCH_BUTTONDOWN		716    
//win8��ʹ��0x024B��ȷ���ִ���, 716��0x02CC, 587��0x024B 
#define  WM_TOUCH_BUTTONDOWN      587

//��ӦWM_TOUCH��Ϣ
#define  WM_TOUCH       0x0240


#include "msgIddispatch.h"  
//������ϢԽ��Խ�࣬Ϊ���ڹ�������Ϊö����ʽ������  2013.1.21 yjj
enum EmUiexMsg{
	#define UIEX_MSG_BEGIN  UIEXLIB_MSG_BEGIN + 0x01

		/************************************************************************/
		/**  
		wParam =  
		lparam = 
		/************************************************************************/
		msg_dragOver = UIEX_MSG_BEGIN, 
	#define UI_DRAG_OVER   msg_dragOver  

		msg_dragLeave,
	#define UI_DRAG_LEAVE         msg_dragLeave

		msg_dragEnd,
	#define UI_DRAG_END           msg_dragEnd

		/************************************************************************/
		/**  ����ק�Ĵ��ڷ��ͣ�֪ͨ����ק����
		wParam =  
		lparam = 
		/************************************************************************/
		msg_beDragEnd,
	#define UI_BE_DRAG_END        msg_beDragEnd   
		
		msg_letterIndexClick,
	#define UI_LETTERINDEX_CLICK     msg_letterIndexClick

		msg_editDelClick,
	#define UI_EDITDELETE_CLICK      msg_editDelClick

		msg_sliderBlockEndLock,
	#define UI_SLIDEBLOCK_ENDLOCK    msg_sliderBlockEndLock
		
		/************************************************************************/
		/** slider�Ļ���λ�øı�
		wParam =  
		lparam = 
		/************************************************************************/
		msg_sliderChanged,
	#define UI_SLIDER_CHANGED        msg_sliderChanged  
		
		/************************************************************************/
		/** list��ǰû��ѡ�����֪ͨ
		wParam =  
		lparam = 
		/************************************************************************/
		msg_listUnSelItem,
	#define WM_LST_UN_SELECT_ITEM    msg_listUnSelItem
		
		/************************************************************************/
		/** �ػ���Ϣ
		wParam =  
		lparam = 
		/************************************************************************/
		msg_redrawUI,
	#define WM_REDRAW_UI             msg_redrawUI


		/************************************************************************/
		/** ����¼�
		wParam =  
		lparam = 
		/************************************************************************/
		msg_btnClick,
	#define WM_BUTTON_CLICK          msg_btnClick

		/************************************************************************/
		/** ʧȥ����
		wParam =  
		lparam = 
		/************************************************************************/
		msg_killFocus,
	#define WM_KILL_FOCUS            msg_killFocus


		/************************************************************************/
		/** ����ѡ������֪ͨ   
		wParam =  
		lparam = 
		/************************************************************************/
		msg_calenderSelDate,
	#define UI_CALENDAR_SELECT_DATE  msg_calenderSelDate
		
		/************************************************************************/
		/** �༭���ȡ������
		wParam =  
		lparam = 
		/************************************************************************/
		msg_editSetFocus,
	#define WM_EDIT_SETFOCUS         msg_editSetFocus

		/************************************************************************/
		/** �༭���ַ��ı���Ϣ
		wParam =  
		lparam = 
		/************************************************************************/
		msg_editOnChar,
	#define WM_EDIT_ONCHAR           msg_editOnChar

		/************************************************************************/
		/** �༭���ַ��ı���Ϣ
		wParam =  
		lparam = 
		/************************************************************************/
		msg_comboxOnChar,
	#define WM_COMBOX_ONCHAR           msg_comboxOnChar

		/************************************************************************/
		/** �༭��ı���Ϣ
		wParam =  
		lparam = 
		/************************************************************************/
		msg_editChanged,
	#define WM_EDIT_CHANGED          msg_editChanged  

		/************************************************************************/
		/** �༭��ı���Ϣ���ҵ�ǰ�Ľ��㲢���ڱ༭��-------JYY  ��cnstoolʹ��
		wParam =  
		lparam = 
		/************************************************************************/
		msg_editChangedNoFocus,
	#define WM_EDIT_CHANGED_NOFOCUS         msg_editChangedNoFocus  
			
		/************************************************************************/
		/** ֪ͨ����Ĵ��ڣ���ǰ���󶨵��Ĵ���handle
		wParam =  
		lparam = 
		/************************************************************************/
		msg_bindWnd,
	#define WM_BIND_WND              msg_bindWnd

		/************************************************************************/
		/**  ֪ͨ����Ĵ��ڣ���ǰ���󶨵��Ĵ�������
		wParam =  
		lparam = 
		/************************************************************************/
		msg_bindWndHide,
	#define WM_BIND_WND_HIDE         msg_bindWndHide       

		/************************************************************************/
		/** ֪ͨ�б�ƫ��λ�� 
		wParam =  
		lparam = 
		/************************************************************************/
		msg_listOffsetNty,
	#define UI_LISTOFFSET_NOTIFY     msg_listOffsetNty

		/************************************************************************/
		/** ֪ͨ���� ��ʼ��д�� 
		wParam =  
		lparam = 
		/************************************************************************/
		msg_endHandWriteNty,
	#define WM_HAND_END_WRITE_NOTIFY    msg_endHandWriteNty

		/************************************************************************/
		/** ֪ͨ���� ��ʼ��д�� 
		wParam =  
		lparam = 
		/************************************************************************/
		msg_beginHandWriteNty,
	#define WM_HAND_BEGIN_WRITE_NOTIFY  msg_beginHandWriteNty

		/************************************************************************/
		/** btn is press in a period  --SXC
		wParam =  
		lparam = 
		/************************************************************************/
		msg_btnHold,
	#define WM_BTN_HOLD                msg_btnHold

		msg_btnHoldEnd,
	#define WM_BTN_HOLD_END             msg_btnHoldEnd

		/************************************************************************/
		/**  �������ʾ
		wParam =  
		lparam = 
		/************************************************************************/
		msg_softKBShow,
	#define WM_SOFTKEYBOARD_SHOW        msg_softKBShow   
		
		/************************************************************************/
		/**  ���������
		wParam =  
		lparam = 
		/************************************************************************/
		msg_softKBHide,
	#define WM_SOFTKEYBOARD_HIDE        msg_softKBHide
		
		/************************************************************************/
		/** �϶���������֪ͨ�б����   
		wParam =  
		lparam = 
		/************************************************************************/
		msg_LstUpdateProgress,
	#define WM_LIST_UPDATEPROGRESS      msg_LstUpdateProgress
		
			 
		/************************************************************************/
		/** ����transparentcombobox�༭������
		wParam =  
		lparam = 
		/************************************************************************/
		msg_updateCombEditTxt,
	#define WM_UPDATE_COMBOEDIT_TEXT      msg_updateCombEditTxt


		/************************************************************************/
		/** ���transparentcombobox�б�
		wParam =  
		lparam = 
		/************************************************************************/
		msg_ClickCombList,
	#define WM_CLICK_COMBOLIST      msg_ClickCombList
	 
		/************************************************************************/
		/**��Ӧ���transparentcombobox�б��¼�
		wParam =  
		lparam = 
		/************************************************************************/
		msg_clickCombLstIcon,
	#define WM_CLICK_COMBOLISTICON        msg_clickCombLstIcon

		/************************************************************************/
		/**����ƶ�transparentcomboboxͼ����ʾ�¼�
		wParam =  
		lparam = 
		/************************************************************************/
		msg_mousemoveCombLstShowIcon,
	#define WM_MOUSEMOVE_COMBOLISTSHOWICON        msg_mousemoveCombLstShowIcon

		/************************************************************************/
		/**�Զ������ش����¼�
		wParam =  
		lparam = 
		/************************************************************************/
		msg_hideWnd,
	#define WM_HIDE_WND        msg_hideWnd
		
		/************************************************************************/
		/**�Ӵ���ʧȥ�����¼�
		wParam =  
		lparam = 
		/************************************************************************/
		msg_childWndInActive,
	#define WM_CHILDWND_INACTIVE        msg_childWndInActive

        /************************************************************************/
		/**  ֪ͨ���ڣ���ǰ���ڱ�����   2013.dyy
		wParam =  
		lparam = 
		/************************************************************************/
		msg_UIWndHide,
	#define UI_WND_HIDE               msg_UIWndHide    

        /************************************************************************/
		/** �յ�����Ϣ����Domodal����
		wParam =  
		lparam = 
		/************************************************************************/
		msg_postdomodal,
	#define WM_POST_DOMODAL          msg_postdomodal

		/************************************************************************/
		/** ֪ͨ�б���ĸ������ָ��
		wParam = NULL
		lparam = CWND*:��ĸ����ָ��
		/************************************************************************/
		msg_bindlist,
	#define WM_BIND_LIST          msg_bindlist

        /************************************************************************/
		/** ֪ͨ�����Ӵ��ڸ��������� Bug00167582
		wParam = NULL
		lparam = NULL
		/************************************************************************/
		msg_parenthide,
	#define WM_PARENT_HIDE        msg_parenthide

		/************************************************************************/
		 /**	��ק��ָ����edit��ʱ��������Ϣ֪ͨedit����
			wParam = 
			lparam = 0*/
		/************************************************************************/ 
	    msg_editselected  ,
#define WM_EDIT_SELECTED msg_editselected

		/************************************************************************/
		 /**	����ָ����editʱ��edit״̬��ԭ
			wParam = 
			lparam = 0*/
		/************************************************************************/ 
	    msg_editleave  ,
#define WM_EDIT_LEAVE msg_editleave

		/************************************************************************/
        /** ������������Ϣ dyy 2014��4��28�� ��Ӧ�ĵ���������downʱ����actBegin��Ϣ
		wParam = NULL
		lparam = NULL
		/************************************************************************/
        msg_buttondwon,
#define WM_BUTTON_DOWN        msg_buttondwon
	
        /************************************************************************/
        /** ���״̬��ԭ��Ϣ
		wParam = NULL
		lparam = NULL
		/************************************************************************/
        msg_buttonstatus_normal,
#define WM_BUTTONSTATUS_NORMAL    msg_buttonstatus_normal
};



//����WM_LBUTTONDOWN����Դ
#define FLAG_TRANSBASEDLG        0
#define FLAG_TRANSBASEWND        2
#define FLAG_TOUCHBUTTONDOWN     3

#ifdef _DEBUG 

static int nGdiPlusObjects = 0;


namespace Gdiplus
{
	namespace DllExports
	{
		#include <GdiplusMem.h>
	};

	#ifndef _GDIPLUSBASE_H
	#define _GDIPLUSBASE_H
	class GdiplusBase
	{
		public:
			void (operator delete)(void* in_pVoid)
			{
				nGdiPlusObjects--;
				DllExports::GdipFree(in_pVoid);
			}

			void* (operator new)(size_t in_size)
			{
				nGdiPlusObjects++;
				return DllExports::GdipAlloc(in_size);
			}

			void (operator delete[])(void* in_pVoid)
			{
				nGdiPlusObjects--;
				DllExports::GdipFree(in_pVoid);
			}

			void* (operator new[])(size_t in_size)
			{
				nGdiPlusObjects++;
				return DllExports::GdipAlloc(in_size);
			}

			void * (operator new)(size_t nSize, LPCSTR /*lpszFileName*/, int /*nLine*/)
			{
				nGdiPlusObjects++;
				return DllExports::GdipAlloc(nSize);
			}

			void operator delete(void* p, LPCSTR /*lpszFileName*/, int /*nLine*/)
			{
				nGdiPlusObjects--;
				DllExports::GdipFree(p);
			}

		};
	#endif // #ifndef _GDIPLUSBASE_H
}
#endif // #ifdef _DEBUG

#ifndef   ULONG_PTR   
#define   ULONG_PTR   unsigned   long*   
#endif

#include <gdiplus.h>
#ifdef _MFC_VER
#include <afx.h>
#endif
#undef iterator

using namespace Gdiplus;
#pragma comment (lib, "Gdiplus.lib")

class QGdiPlus
{
public:
	QGdiPlus(): m_Token(0)	{ 
		Gdiplus::GdiplusStartupInput input; 
		Gdiplus::GdiplusStartup(& m_Token, & input, NULL); 
	}
	~QGdiPlus()
	{
		Gdiplus::GdiplusShutdown(m_Token);
#ifdef _DEBUG
#ifdef _MFC_VER
		if (nGdiPlusObjects > 0)
			afxDump << _T(">>> GdiPlus Memory Leaks: ") << nGdiPlusObjects << _T(" objects! <<<\n");
		else if (nGdiPlusObjects < 0)
			afxDump << _T(">>> GdiPlus Multiple Deletes: ") << -nGdiPlusObjects << _T(" objects! <<<\n");
#endif
#ifdef _ATL_VER
		if (nGdiPlusObjects > 0)
			ATLTRACE2(_T(">>> GdiPlus Memory Leaks: %d objects! <<<\n"), nGdiPlusObjects);
		else if (nGdiPlusObjects < 0)
			ATLTRACE2(_T(">>> GdiPlus Multiple Deletes: %d objects! <<<\n"), -nGdiPlusObjects);
#endif
#endif
	}
private:
	// The token we get from GDI+
	ULONG_PTR m_Token;
};





 



typedef std::string String;
#include "templateClass.h"
using namespace AutoUIFactory;
using namespace std; 



class Args_Graphics : public IArgs
{
public:
	Args_Graphics( Graphics* pGraphics, Rect rc, CPoint pt = 0 ) : IArgs( "Graphics") ,
		m_pGraphics( pGraphics ), m_rc( rc ),m_ptOffset(pt){}
	Graphics* m_pGraphics;
	Rect m_rc;
	CPoint m_ptOffset;  	//  2012-8-6 ���xp��ocx���б�ֻ����ʾ�߰˰ٸ���Ŀ������ by yjj
};


typedef BOOL(WINAPI *PFN_UpdateLayeredWindow)( 
                                              HWND hWnd,
                                              HDC hdcDst,
                                              POINT *pptDst,
                                              SIZE *psize,
                                              HDC hdcSrc,
                                              POINT *pptSrc,
                                              COLORREF crKey,
                                              BLENDFUNCTION *pblend,
											  DWORD dwFlags);

#ifndef WS_EX_LAYERED
#	define WS_EX_LAYERED			0x00080000
#endif

#ifndef LWA_ALPHA
#	define LWA_ALPHA				0x00000002
#endif

#ifndef ULW_ALPHA
#	define ULW_ALPHA				0x00000002
#endif





#define NOTIF_PARENT_WND \
	if ( GetParent() != NULL ) \
{		\
	GetParent()->SendMessage( WM_REDRAW_UI, NULL, /*(LPARAM)m_hWnd*/ (LPARAM)0  ); \
}
#define NOTIF_ALL_WND \
	if ( GetParent() != NULL ) \
{		\
	GetParent()->SendMessage( WM_REDRAW_UI, NULL, (LPARAM)0 ); \
}

#define NOTIF_PARENT_WND_IMMEDIATLY_DRAW \
	if ( GetParent() != NULL ) \
{		\
	GetParent()->SendMessage( WM_REDRAW_UI, NULL, 1 ); \
}




// 
template <class T> class TransparentAssist
{
public:
	typedef LRESULT (CALLBACK* WNDPROC)( HWND,UINT,WPARAM,LPARAM);
	static WNDPROC m_pWndProc;
	void RegsiterWndProc()
	{
		T* pObject = (T*)this;
		m_pWndProc = (WNDPROC)GetWindowLong( pObject->m_hWnd, GWL_WNDPROC );
		::SetWindowLong( pObject->m_hWnd,GWL_WNDPROC,(LONG)AssistProc );
	}
	static LRESULT CALLBACK AssistProc( HWND hWnd , UINT message, WPARAM wParam, LPARAM lParam )
	{
		LRESULT ret = CallWindowProc( m_pWndProc, hWnd, message, wParam, lParam );
		HWND hParent = ::GetParent( hWnd );
#define UPDATEUI_ALL SendMessage( hParent, WM_REDRAW_UI, 0, (LPARAM)0 );
#define UPDATEUI_SUB SendMessage( hParent, WM_REDRAW_UI, 0, (LPARAM)hWnd );	
		switch ( message )
		{
		case WM_SIZING:
			{
				if ( IsWindowVisible( hParent ) )
				{
					UPDATEUI_ALL
				}
			}
			break;
		case WM_MOVING:
			{
				if ( IsWindowVisible( hParent ) )
				{
					UPDATEUI_ALL
				}
			}
			break;
		default:
			break;
		}
		return ret;
	}		
};



class IData
{
public:
	IData( std::string strType ) : m_strType( strType ), m_dwKey( -1 ){}
	virtual ~IData(){}
	std::string GetType() const { return m_strType; } 
	unsigned long GetDataKey() { return m_dwKey; }
	void SetDataKey( unsigned long dwKey ) { m_dwKey = dwKey; }
	
	virtual IData* Clone() = 0;
protected:
	unsigned long m_dwKey;      //Data��ֵ�����ڲ���Item
	std::string m_strType;
};


/*
 * Touch input flag values (TOUCHINPUT.dwFlags)
 */
#define TOUCHEVENTF_MOVE            0x0001
#define TOUCHEVENTF_DOWN            0x0002
#define TOUCHEVENTF_UP              0x0004
#define TOUCHEVENTF_INRANGE         0x0008

//WM_TOUCH��Ϣ�ṹ��
typedef struct tagTOUCHINPUT {
    LONG x;
    LONG y;
    HANDLE hSource;
    DWORD dwID;
    DWORD dwFlags;
    DWORD dwMask;
    DWORD dwTime;
    ULONG_PTR dwExtraInfo;
    DWORD cxContact;
    DWORD cyContact;
} TOUCHINPUT, *PTOUCHINPUT;
typedef TOUCHINPUT const * PCTOUCHINPUT;


typedef VOID (*WINSDK_RegTouchWindow)(HWND hWnd);
typedef BOOL (*WINSDK_GetTouchInputInfo)( LPARAM lParam, UINT cInputs, TOUCHINPUT& tInput );
typedef BOOL (*WINSDK_GetTouchInputPoint)( LPARAM lParam, UINT cInputs, POINT& ptInput );

#define TOUCH_COORD_TO_PIXEL(l)         ((l) / 100)

#endif