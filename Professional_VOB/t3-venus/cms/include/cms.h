// cms.h : main header file for the CMS application
//

#if !defined(AFX_CMS_H__563BEF5B_7F71_48DE_B97B_8D9ECDFB88D1__INCLUDED_)
#define AFX_CMS_H__563BEF5B_7F71_48DE_B97B_8D9ECDFB88D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols 
#include "kdvType.h"		// 公共类型
#include "kdvdef.h"			// 公共宏定义
#include "commoninterface.h"  //与服务器通信的接口
#include "msgdispatch.h"
#include "cmsConst.h"
#include "evCmsLib.h"
#define ComInterface    CCommonInterface::GetCommIF()
 
/////////////////////////////////////////////////////////////////////////////
// CCmsApp:
// See cms.cpp for the implementation of this class
//

class CCmsApp : public CWinApp
{
public:
	CCmsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCmsApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCmsApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
        //从某个窗口中是否含有 默认按钮
	HWND  GetDefIDWndHandle( HWND hwnd );

	HHOOK m_hk;
};


void DisableTaskMgr( BOOL bDisable );
BOOL OnlyStartOne();

//实现开机自启动
BOOL  AutoRun( bool bAutoRun );

//AIP void findeName( LPSTR name );

API void help();

API void task( BOOL bEnable = TRUE );


API void prt(); 

API void prtlevel( u8 byLevel );

API void prtid( u32 msgID );

API void prtrange( u32 beginID, u32 endID );

API void stopprt();

API void prtrecive( BOOL bPrint = TRUE );

API void prtsend( BOOL bPrint = TRUE  );

API void showver();

// 显示所有会议
API void showallconf();

//显示某ID的会议信息
API void showconf( u16 wConfID );


//显示会议中cns的信息
API void showconfcns( u16 wConfID , u16 wCnsID );

//挂断某会议中的某个会场
API void hangupep( u16 wConfID, u16 epID );


//结束会议
API void hangupconf( u16 wConfID );

//显示 会场信息
API void showcns();

//API void showalltemp( );  //显示会议模板

//API void showtemp( u16 tempID   );  //显示会议模板


//显示本地cns状态
API void showcnsstate();

//显示屏信息
API void showscrninfo();

API void showallcns();

//显示所有用户信息
API void showalluser();

API void  showlocalip();

//设置解码器音量
API void  setdecvol( u8 abyVol );

//显示当前解码器音量
API void  showdecvol();

//显示告警信息
API void showalarm();

//显示地址簿信息
API void showaddrbook();
API void showaddrentry( u32 dwEntryIndex );

API void showonlineaddr();
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMS_H__563BEF5B_7F71_48DE_B97B_8D9ECDFB88D1__INCLUDED_)
