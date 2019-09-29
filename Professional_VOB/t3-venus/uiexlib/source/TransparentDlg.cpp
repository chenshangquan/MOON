// TransparentDlg.cpp: implementation of the CTransparentDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TransparentDlg.h"
#include "atlconv.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTransparentDlg::CTransparentDlg():
			     CTransparentDlgBase(0, NULL)
{  
	m_pDlgTemp = NULL;
	m_strTxt.Empty();
}

CTransparentDlg::~CTransparentDlg()
{   
	ClearDlgTempBuff(); 
}


BOOL CTransparentDlg::Create( CString strDlgName, CRect rc,DWORD dwStyle, DWORD dwExtendedStyle, CWnd* pParent, BOOL bModal )
{    
	if ( !CheckParam(dwStyle, pParent,bModal) )
	{
	   return FALSE;
	}


	BOOL re = TRUE;
	DLGTEMPLATE* pTempl = ConstructDlgTemp( rc, dwStyle, dwExtendedStyle );

    if ( !bModal )
    { //����Ƿ�ģ̬������ֱ�Ӵ���
		re =  CreateIndirect(pTempl, pParent);  
		ClearDlgTempBuff();
		if( re )
		{ 
			////���ñ��� 
			SetWindowText( strDlgName );
		}
		else
		{
			PrtError( "CTransparentDlg::CreateModeless", "CreateIndirect()=false" );
		} 
    }
	else
	{ 
		m_pParentWnd = pParent;
		m_strTxt = strDlgName; 
	 
	}  

	return re;
}


 

int  CTransparentDlg::DoModal()
{   
	int nRe = -1;
	if( NULL!= m_pDlgTemp )
	{   
		//DLGTEMPLATE* pTempl = ( DLGTEMPLATE* )(m_hDlgTempBuff);
    	BOOL re = InitModalIndirect(m_pDlgTemp, m_pParentWnd); 
	 	if( re )
		{   
		 //	SetWindowText( m_strTxt );
			nRe =	CTransparentDlgBase::DoModal();
		}
		else
		{
			PrtError( "CTransparentDlg::DoModal", "doMoadl fail: InitModalIndirect() = false " );
		}
	     
	}
	else
	{
		PrtError( "CTransparentDlg::DoModal", "doMoadl fail: m_hDlgTempBuff = NULL " );
	}

	return nRe;
}



int  CTransparentDlg::DoModal(CString strDlgName, CRect rc,DWORD dwStyle, DWORD dwExtendedStyle, CWnd* pParent )
{   
	CheckParam(dwStyle, NULL,TRUE);
 
	int nRe = -1;
	DLGTEMPLATE* pTempl = ConstructDlgTemp( rc, dwStyle, dwExtendedStyle );
	BOOL re = InitModalIndirect(pTempl, pParent); 
	if( re )
	{   
		//	SetWindowText( m_strTxt );
		nRe =	CTransparentDlgBase::DoModal();
	}
	else
	{
		PrtError( "CTransparentDlg::DoModal", "doMoadl fail: InitModalIndirect() = false " );
	}

	ClearDlgTempBuff();
	return nRe;
 
}

BOOL CTransparentDlg::IsInModalLoop()
{
	return m_nFlags&WF_MODALLOOP;
}

int CTransparentDlg::StartModalLoop()
{ 
	if ( m_hWnd == NULL )
	{   
		PrtError("CTransparentDlg::BeginModalLoop"," m_hWnd = 0 ");
		return -1;
	}  

	 
	LONG lStyle = ::GetWindowLong(m_hWnd, GWL_STYLE);
	if( lStyle & WS_CHILDWINDOW )
	{
		PrtError("CTransparentDlg::BeginModalLoop"," ��ǰ����Ϊchild���ͣ�����domodal ");
		return -1;
	}
	
 
	if (  (m_nFlags & WF_MODALLOOP) &&  (m_nFlags| WF_CONTINUEMODAL ) )
	{   
		PrtError("CTransparentDlg::BeginModalLoop"," StartModalLoopʧ�ܣ���ǰ�����Ѿ�����domodal״̬");
	  /*  StopModalLoop(-1);  �����ظ�����һ�����ڵ�domoadlʱ��
		���ܼ�ʱ������modalloop��������������IsInModalLoop��
		�����ڵ���startmodalǰ�жϣ��Ա���startmodalʧ�����2013.2.28 yjj*/
		
	 	return -1; 
	 
	}
   

	m_nFlags  |=  WF_CONTINUEMODAL;
	
	
  //-------PreModal();-------
	// disable parent  
	// allow OLE servers to disable themselves
	CWinApp* pApp = AfxGetApp();
	if (pApp != NULL)
       pApp->EnableModeless(FALSE);
	// find parent HWND
  	HWND hWndParent =  CWnd::GetSafeOwner_(m_pParentWnd->GetSafeHwnd(), &m_hWndTop);

	if ( hWndParent == m_hWnd )//��ʱ���ȡ��owner����Ϊ����
	{
		hWndParent = AfxGetMainWnd()->GetSafeHwnd();
	}
 
  	BOOL bEnableParent = FALSE;
	if (hWndParent != NULL && ::IsWindowEnabled(hWndParent))
	{
		::EnableWindow(hWndParent, FALSE); 
		bEnableParent = TRUE;
	}

    // find owner HWND
    BOOL bEnableOwner = FALSE;
    HWND hOwnerWnd = NULL;
    CWnd* pWnd = CWnd::FromHandle(m_hWnd);
    if ( pWnd != NULL )
    {
        CWnd* pOwnerWnd = pWnd->GetOwner();
        if ( pOwnerWnd != NULL )
        {
            hOwnerWnd = pOwnerWnd->GetSafeHwnd();
            if (hOwnerWnd != NULL && ::IsWindowEnabled(hOwnerWnd))
            {
                ::EnableWindow(hOwnerWnd, FALSE); 
                bEnableOwner = TRUE;
	        }
        }
    }       
	
	TRY
	{ 
		if (m_nFlags & WF_CONTINUEMODAL)
		{
			// enter modal loop
			DWORD dwFlags = MLF_SHOWONIDLE;
			if (GetStyle() & DS_NOIDLEMSG)
				dwFlags |= MLF_NOIDLEMSG;
			::ShowWindow( m_hWnd, SW_SHOWNORMAL);
			BOOL bOk = SetForegroundWindow(); 
			VERIFY(RunModalLoop(dwFlags) == m_nModalResult);
		}
		
		// hide the window before enabling the parent, etc.
		if (m_hWnd != NULL)
			SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW|
			SWP_NOSIZE|SWP_NOMOVE|SWP_NOACTIVATE|SWP_NOZORDER);
		 
	}
	CATCH_ALL(e)
	{
		do { e->Delete(); } while (0);
		m_nModalResult = -1;
	}
	END_CATCH_ALL
		

    if ( bEnableOwner && hOwnerWnd != NULL )
    {
        ::EnableWindow(hOwnerWnd, TRUE); 
	}

	if (bEnableParent)
	{
		::EnableWindow(hWndParent, TRUE);
	}

	if (hWndParent != NULL && ::GetActiveWindow() == m_hWnd)
	{
		::SetActiveWindow(hWndParent);
	}
		
	// destroy modal window
    //DestroyWindow();  //2012.12.4 yjj
	   
  //-----------PostModal();---------------
    //AfxUnhookWindowCreate();   // just in case 
	//Detach(); ���ڴ��ڲ������٣����������handlemap
	//re-enable windows
	if (::IsWindow(m_hWndTop))
	{
		::EnableWindow(m_hWndTop, TRUE);
	} 
	//m_hWndTop = NULL; 
	if (pApp != NULL)
	{
		pApp->EnableModeless(TRUE);
	}
 

	return m_nModalResult;
}
 

void CTransparentDlg::StopModalLoop( int nResult )
{ 
	if ( m_nFlags &( WF_MODALLOOP | WF_CONTINUEMODAL ) && ( NULL != m_hWnd) )   //δ��domodal״̬���򲻽����κδ��� 2013.1.31 yjj
	{
		EndModalLoop(nResult);    //������domodal���ڲ���ɵ���²㴰������
	} 
}
 

DLGTEMPLATE* CTransparentDlg::ConstructDlgTemp( CRect rc, DWORD dwStyle, DWORD dwExtendedStyle )
{
	ClearDlgTempBuff();     
	int nLen = sizeof(DLGTEMPLATE) + sizeof(DWORD)  + sizeof(DWORD) + sizeof(DWORD) + sizeof(DWORD); //menu + class + title + font ��Ϊ0 ,����Ҫ��������
    HANDLE h = GlobalAlloc(GHND, nLen); 
	m_pDlgTemp = (DLGTEMPLATE*) GlobalLock(h);  
	
	m_pDlgTemp-> style = dwStyle; //WS_OVERLAPPEDWINDOW | WS_VISIBLE | DS_CENTER | DS_3DLOOK; 
	m_pDlgTemp-> dwExtendedStyle = dwExtendedStyle; 

	m_pDlgTemp-> cdit = 0; 

	//����DLGTEMPLATE ��ʹ�õ��Ǵ��ڵ�λ������Ҫ������תΪ�Դ���Ϊ��λ�Ĵ�С
	//���⣬�ɴ��ڵ�λתΪ���ص�λ��ʹ�ýӿڣ�MapDialogRect() 
	CSize base = ::GetDialogBaseUnits(); 
	int xDlg = MulDiv(rc.Width(), 4, base.cx); // rc.Width();
	int yDlg = MulDiv(rc.Height(), 8, base.cy); //rc.Height(); 
    
	int x = MulDiv( rc.left, 8, base.cy);//rc.left; 
	int y = MulDiv( rc.top, 8, base.cy);//rc.top; 

	m_pDlgTemp-> x = x; 
	m_pDlgTemp-> y = y; 
	m_pDlgTemp-> cx = xDlg; 
	m_pDlgTemp-> cy = yDlg;    
    return m_pDlgTemp;

}



void CTransparentDlg::ClearDlgTempBuff()
{
	if ( NULL != m_pDlgTemp )
	{
		GlobalUnlock( (HGLOBAL)m_pDlgTemp ); 
		GlobalFree( (HGLOBAL)m_pDlgTemp );	
		m_pDlgTemp = NULL;
		m_pParentWnd = NULL;
		m_strTxt = "";
		
	}
}


BOOL CTransparentDlg::CheckParam( DWORD& dStyle, CWnd* pParent, BOOL bModalDlg )
{
	BOOL bRe = TRUE;

    //domodal ���Ͳ�����Ϊchild
	if ( bModalDlg && (dStyle & WS_CHILD) )
	{
		dStyle &= ~WS_CHILD;
		dStyle |= WS_POPUP;
	}  

	//��Ϊ�Ӵ��ڣ����丸���ڲ�����Ϊ��
	if ( (dStyle & WS_CHILD) && NULL == pParent )
	{  
		PrtError("CTransparentDlg::CheckParam","child���͵�dlg�ĸ����ڲ�����Ϊ��");
		bRe = FALSE;
	}

	return bRe;
	
}


void CTransparentDlg::PrtError( CString strErrFun,CString strErr  )
{
	CString str; 
	str.Format("\n[%s] %s , errorCode=%d\n",strErrFun, strErr ,GetLastError());
	AfxOutputDebugString(str);//�����release�棬����debugview���鿴�������
}

BOOL CTransparentDlg::PreTranslateMessage( MSG* pMsg )
{
	if( ( IsInModalLoop()|| GetWindowLong(GetSafeHwnd(),GWL_STYLE)&WS_CHILD )&& pMsg->message == WM_KEYDOWN 
		&& ( pMsg->wParam == VK_ESCAPE ||pMsg->wParam == VK_RETURN ) )
	{  
		return TRUE;
	}
    
	return CDialog::PreTranslateMessage(pMsg);
				 
}
