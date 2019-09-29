// dlgModal.cpp: implementation of the CDlgModal class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cms.h"
#include "dlgModal.h"
#include "uiManage.h"
#include "transparentbasedlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

 
CDlgModal::CDlgModal(CWnd* pParent /*=NULL*/)
: CDlgPopup(pParent) 
{
   
}

 

CDlgModal::~CDlgModal()
{ 
}

BEGIN_MESSAGE_MAP(CDlgModal, CDlgPopup)
//{{AFX_MSG_MAP(CTransparentBaseDlg)
 ON_WM_SHOWWINDOW()
//ON_WM_PAINT()
//}}AFX_MSG_MAP
 
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransparentBaseDlg message handlers

BOOL CDlgModal::OnInitDialog() 
{
    CDlgPopup::OnInitDialog();

    // 
    //UIManagePtr->CreateDlgControls( this, m_strDlgName );
 

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgModal::OnShowWindow(BOOL bShow, UINT nStatus) 
{
    CDialog::OnShowWindow(bShow, nStatus);
   
    // TODO: Add your message handler code here

    
    DWORD dwCurID = GetCurrentProcessId(); 
    if ( TRUE == bShow )
    {    
        DWORD dwID = 0 ;
    
       //禁用该进程中所有dlg
       Window *p = UIManagePtr->GetWindowPtr( g_stcStrMainFrameDlg );
       
        CWnd* child  = p->GetWindow( GW_HWNDFIRST );
        while ( child )
        {   
            GetWindowThreadProcessId(child->GetSafeHwnd(), &dwID) ;
            if ( dwID == dwCurID )
            {
                child->EnableWindow(FALSE);
            }
            
            dwID = 0;
            child = child->GetWindow( GW_HWNDNEXT );
        }
         
        this->EnableWindow(TRUE);
        //RunModalLoop();
        SendMessage(WM_REDRAW_UI,0,0);
        SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );

        UIDATAMGR->SetUILockScreen( TRUE );
    }
    else
    {  
        DWORD dwID = 0 ;
        //起用该进程中所有dlg
        Window *p = UIManagePtr->GetWindowPtr( g_stcStrMainFrameDlg );
        
        CWnd* child  = p->GetWindow( GW_HWNDFIRST );
        while ( child )
        {   
            GetWindowThreadProcessId(child->GetSafeHwnd(), &dwID) ;
            if ( dwID == dwCurID )
            {
                child->EnableWindow(TRUE);
            } 
            
            dwID = 0 ;

            child = child->GetWindow( GW_HWNDNEXT );
        }

        if ( UIDATAMGR->IsUILockScreen() )
        {
            UIDATAMGR->SetUILockScreen( FALSE );
        }
        
    }
}