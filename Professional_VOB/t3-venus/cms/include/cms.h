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
#include "kdvType.h"		// ��������
#include "kdvdef.h"			// �����궨��
#include "commoninterface.h"  //�������ͨ�ŵĽӿ�
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
        //��ĳ���������Ƿ��� Ĭ�ϰ�ť
	HWND  GetDefIDWndHandle( HWND hwnd );

	HHOOK m_hk;
};


void DisableTaskMgr( BOOL bDisable );
BOOL OnlyStartOne();

//ʵ�ֿ���������
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

// ��ʾ���л���
API void showallconf();

//��ʾĳID�Ļ�����Ϣ
API void showconf( u16 wConfID );


//��ʾ������cns����Ϣ
API void showconfcns( u16 wConfID , u16 wCnsID );

//�Ҷ�ĳ�����е�ĳ���᳡
API void hangupep( u16 wConfID, u16 epID );


//��������
API void hangupconf( u16 wConfID );

//��ʾ �᳡��Ϣ
API void showcns();

//API void showalltemp( );  //��ʾ����ģ��

//API void showtemp( u16 tempID   );  //��ʾ����ģ��


//��ʾ����cns״̬
API void showcnsstate();

//��ʾ����Ϣ
API void showscrninfo();

API void showallcns();

//��ʾ�����û���Ϣ
API void showalluser();

API void  showlocalip();

//���ý���������
API void  setdecvol( u8 abyVol );

//��ʾ��ǰ����������
API void  showdecvol();

//��ʾ�澯��Ϣ
API void showalarm();

//��ʾ��ַ����Ϣ
API void showaddrbook();
API void showaddrentry( u32 dwEntryIndex );

API void showonlineaddr();
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMS_H__563BEF5B_7F71_48DE_B97B_8D9ECDFB88D1__INCLUDED_)
