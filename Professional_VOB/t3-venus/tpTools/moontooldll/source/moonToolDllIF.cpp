// moonToolDllIF.cpp : main header file for the MOONTOOLDLL DLL
/*---------------------------------------------------------------------
* �� ��	���� moonToolDllIF.cpp
* ��    �ܣ� moonToolDll �Ľӿ��ļ� 
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2014.11.25   1.0         ���`�`        ����
----------------------------------------------------------------------*/

#include "stdafx.h"
#include "moonToolDllIF.h"
 
#include "logicMgr.h"

#include "moonlibdatamgr.h"
#include "moonlibcommonif.h"
//�쳣����
#include "exceptioncatch.h" 

#define _NMS_COMMON_CPP_
#include "common.h"

#pragma comment(lib, "moonlib.lib") 

//cns���ṩ�Ŀ�
#pragma comment(lib, "xmlengine.lib")
//#pragma comment(lib, "cnmsg.lib")

#pragma comment(lib, "moonmsg.lib")
#pragma comment(lib, "tpmsgmgr.lib") 


//windows ��
#pragma comment (lib, "UIFactory.lib ") 

//nms���ṩ�Ŀ�
#pragma comment(lib, "nmscommon.lib")

//������
#pragma comment(lib, "osplib.lib")
#pragma comment(lib, "kdvsys.lib")
#pragma comment(lib, "kdvlog.lib")
//#pragma comment(lib, "kdvaddrbook.lib")


//�쳣��������ļ�
#define EXCEPTION_FILE_PATH _T("moonToolExcep.log")
   


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
 
static BOOL bInit = FALSE;
HWND g_hNotifyWnd = 0;

MOONTOOLDLL_API BOOL _stdcall IsInitMoonTool()
{   
	return bInit;
}


MOONTOOLDLL_API void _stdcall InitMoonTool( HWND hNotifyWnd )
{ 
	AFX_MANAGE_STATE( AfxGetStaticModuleState());
	g_hNotifyWnd = hNotifyWnd;

	if( !bInit )
	{    
		bInit = TRUE;
		//�쳣����
		CString strFullPath = GetModuleFullPath();
		strFullPath += EXCEPTION_FILE_PATH;
		CExceptionCatch::LogToFile( (LPSTR)(LPCSTR)strFullPath );
		CExceptionCatch::Start();  

		//��ʼ��lib
 		MOONLIBDATAMGRPTR->InitDataMgr();

		
 		//��ʼ��uifactory
 		UIFACTORYMGR_PTR->InitUIFactory("resmoontool\\system.xml");
		
 		//��ʼ�����ڹ����߼���Ϣ
 		CLogicMgr::GetSingletonPtr()->CreateLogic(); 
       
 		//��ʼ�������еĴ��ڴ���,��������ʾ,�ȵ����ճɹ��ظ�ʱ����ʾ(���domal������ʾ��mainframe����)----JYY
  		UIFACTORYMGR_PTR->ShowWindow( g_strMoonMainFrame, FALSE );
 
 		//��OSPע�᱾ģ��
 		ModuleRegToOsp();
 		
 		DWORD dwProcessId = GetCurrentProcessId();
 		TCHAR aszPrompt[32] = "";
 		
 		sprintf( aszPrompt, "tptool(%d):", dwProcessId );
 		OspSetPrompt( aszPrompt );

	}
}


MOONTOOLDLL_API void _stdcall DestroyMoonTool()
{  
	
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if( bInit ) 
	{   
		bInit = FALSE; 
	
		//2013.9.5----JYY  ��֤mainframe�������ȴ���,���ٲ�����init������ͻ
		//����lib
		//CNCSESSION_MGR_PTR->DesdroySession();

		//����uifactroy
		//UIFACTORYMGR_PTR->DestoryAllWnd();		------���ܴ���ָ��û���,�����鿴
		//UIFACTORYMGR_PTR->UnInitUIFactory();

		//�ͷ��쳣���
    	CExceptionCatch::Free();
	}
}

 
 
MOONTOOLDLL_API UINT _stdcall ConnectMoon( DWORD dwCnsIP, DWORD dwCnsPort )
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState());
	//����common�е����ӽӿڵ�½cns 	 JYY  2013.4.2  �����߳�������cns,���ӽ��ֱ����mainframe�������
 	/*u16 wRet = */

	COMIFMGRPTR->connect(dwCnsIP, dwCnsPort);


//   	if ( NO_ERROR != wRet )
//   	{
//   		LPCTSTR strErr = "��������ʧ��";
//   		UIDATAMGR_PTR->NotifyOuterWnd(  WM_TPTOOL_LOGINRESULT, em_LOGIN_ERROR_RSQ, LPARAM(strErr)); 
// 		wRet = 1;
//   	}	
	return NO_ERROR;
}

 

MOONTOOLDLL_API BOOL _stdcall HandleMoonToolMsg( MSG* pMsg )
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState());
	if ( NULL == pMsg )
	{
		return FALSE;
	}

	//20130805---------CCTransparentDlg�Ѿ��Իس�������sc
	//20130522sc edit�ؼ���Ӧ�س���Ϣ
// 	if ( pMsg->wParam == VK_RETURN && pMsg->hwnd )
// 	{		
// 		if ( UIFACTORYMGR_PTR->IsVisible( g_strMainFrame ) && UIFACTORYMGR_PTR->IsVisible( g_StrCameraDlg )  )
// 		{
// 			return AfxGetApp()->PreTranslateMessage(pMsg);
// 		}
// 	}

	if ( pMsg->message == WM_COMMAND && pMsg->wParam == WM_DESTROY )	//�������Ҽ�����رճ���  2013��11��8�� JYY
	{

		if ( !UIDATAMGR_PTR->NotifyOuterWnd(WM_CLOSE, 0, 0) )
		{
			UINT uExitCode = 0; 
			ExitProcess( uExitCode );
		}

	}

	

	//���domodal�� �޷����յ�cns��Ϣ������  2013.1.23  yjj
	// UIFACTORYMGR_PTR->HandleMsg(pMsg );    
	return AfxGetApp()->PreTranslateMessage(pMsg);

  
}


//////////////////////////////////OSP��ӡ����/////////////////////////////////////////////
API void help()
{
    PrtMsg( "\n    showver:                    ��ʾ�汾�ͱ���ʱ��");
	PrtMsg( "\n    prt:                        ��ӡ���м���Ϊ3���ϵ���Ϣ");
	PrtMsg( "\n    prtlevel nLevel:            ��ӡ����ΪnLevel����Ϣ����Ϣ���� 1-3��\n \
                                               1Ϊ������ߵ���Ϣ���ü������Ϣ��ϵͳ���ܲ�������Ӱ��\n \
                                               2Ϊһ�㼶�����Ϣ\n \
                                               3Ϊ��ͼ�����Ϣ " );
	PrtMsg( "\n    stopprt:                    ֹͣ��ӡ");
	PrtMsg( "\n    prtid msgID:                ��ӡ��Ϣ����msgID����Ϣ");
    PrtMsg( "\n    prtrange beginID endID:     ��ӡ��Ϣ�ŷ�Χ�� beginID �� endID ֮�����Ϣ");
    PrtMsg( "\n    prtrecive 0 / 1:            ��ӡ���н��ܵ�����Ϣ, 0:����ӡ��1:��ӡ");
    PrtMsg( "\n    prtsend 0 / 1:              ��ӡ���з��ͳ�ȥ����Ϣ, 0:����ӡ��1:��ӡ");
}

API void showver()
{   
    PrtMsg( "moontool version: %s ", GetMoonToolBuildVersion() ); 
    PrtMsg( "compile time:%s %s", __DATE__, __TIME__ );
}

API void prt()
{
    CPrintCtrl::GetPrintCtrl()->PrintAllMsg();
}


API void prtlevel( u8 byLevel )
{
    CPrintCtrl::GetPrintCtrl()->PrintMsgLevel( byLevel );
}

API void stopprt()
{
	CPrintCtrl::GetPrintCtrl()->StopPrint();
}

API void prtid( u32 msgID )
{
	CPrintCtrl::GetPrintCtrl()->SetPrintMsgID( msgID );
}

API void prtrange( u32 beginID, u32 endID )
{ 
    CPrintCtrl::GetPrintCtrl()->SetPrintMsgRange( beginID, endID ); 
}

API void prtrecive( BOOL bPrint /*= TRUE */ )
{
    CPrintCtrl::GetPrintCtrl()->PrintEnterMsg( bPrint ); 
}

API void prtsend( BOOL bPrint/* = TRUE */)
{
	CPrintCtrl::GetPrintCtrl()->PrintOutMsg( bPrint );
}