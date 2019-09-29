// callingDlg.cpp: implementation of the CCallingDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cms.h"
#include "callingDlg.h"
#include "uiManage.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
u32 g_dwCounter = 0;
u32 g_dwTotal = 5  ;

CCallingDlg *pDlg = NULL;
UINT g_wTimerID = 0;
//g_wLocalTimerID = SetTimer( NULL, 0, 60000, CBTimerFun );
VOID   CALLBACK   CBTimer(  HWND   hwnd,   UINT   uMsg, UINT_PTR  idEvent, DWORD   dwTime  )
{   
     
    if ( pDlg!= NULL && ( idEvent == g_wTimerID || idEvent == 100) )
    {  
        if ( g_dwCounter >= g_dwTotal )
        {  
            ::KillTimer( NULL,g_wTimerID );
            pDlg->HideCallingBox();
            BusinessManagePtr->setLocalCnsState( emLocalCallingTimeOut );
            //显示是 否挂断的对话框  发消息给
            CMsgDispatch::SendMessage( UI_CMS_CALLING_TIME_OUT, 0 , 0 );
            
        }

        g_dwCounter ++;
        pDlg->UpdateCallingImg();
        
    } 
}





CCallingDlg::CCallingDlg( Window * pParent/* = NULL*/ )
:CMsgBox(pParent),m_nNowImgIndex(0)
{  
    g_wTimerID = 0;

    CString str;
    str.Format("%s",UIManagePtr->GetImagePath().c_str() );
    m_strImgArray[0] = str + "callingImg\\calling1.png";
    m_strImgArray[1] = str + "callingImg\\calling2.png";
    m_strImgArray[2] = str + "callingImg\\calling3.png";
    m_strImgArray[3] = str + "callingImg\\calling4.png";

}

CCallingDlg::~CCallingDlg()
{
    pDlg = NULL;
}




BEGIN_MESSAGE_MAP(CCallingDlg, CMsgBox)
//{{AFX_MSG_MAP(CCallingDlg)
//ON_WM_TIMER()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCallingDlg message handlers

BOOL CCallingDlg::OnInitDialog() 
{   
    //CTransparentBaseDlg::OnInitDialog();
    CMsgBox::OnInitDialog();  
   
    TRACE("\n[CCallingDlg::OnInitDialog] parentWnd=%d\n",GetParent());

    //挂断按钮
    RECT rect;
    rect.left =   200;
    rect.top =    241;
    rect.right = rect.left + 138;
    rect.bottom = rect.top + 58;
    m_btnHungup.Create( "挂断会议",WS_CHILD, rect,this,IDOK );
    CString str;
    str.Format("%sbtnHungup",UIManagePtr->GetImagePath().c_str() );
    m_btnHungup.ShowWindow( SW_SHOW );
    m_btnHungup.SetImage( str,FALSE );


    //图片static  m_stcImg
    rect.left =   76;
    rect.top =    104;
    rect.right = rect.left + 64;
    rect.bottom = rect.top + 54;
    m_stcImg.Create("", WS_CHILD, rect, this, 0 );
    m_stcImg.ShowWindow( SW_SHOW );
    m_stcImg.SetImage( m_strImgArray[0] );

    //消息static m_stcMsg
    rect.left =   174;
    rect.top =    115;
    rect.right = rect.left + 200;
    rect.bottom = rect.top + 50;
    m_stcMsg.Create("正在建立会议......", WS_CHILD, rect, this, 0 );  
    m_stcMsg.ShowWindow( SW_SHOW );
    SendMessage( WM_REDRAW_UI);  
    
    pDlg = this;

    g_wTimerID = SetTimer( 100, 500, CBTimer );
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CCallingDlg::OnCommand(WPARAM wParam, LPARAM lParam) 
{
    // TODO: Add your specialized code here and/or call the base class
    UINT message=HIWORD(wParam);
    int nID=LOWORD(wParam);
    if ( lParam != 0 &&  nID == IDOK )
    {
        HideCallingBox();
    }

    return CMsgBox::OnCommand(wParam, lParam);
}

 


//更换呼叫图片
void CCallingDlg::UpdateCallingImg()
{  
    if ( m_nNowImgIndex < 3 )
    {   
        m_nNowImgIndex ++;
        m_stcImg.SetImage( m_strImgArray[ m_nNowImgIndex ], TRUE );
        
    }
    else
    {  
        m_nNowImgIndex = 0;
        m_stcImg.SetImage( m_strImgArray[ m_nNowImgIndex ], TRUE );
    } 
}



// void CCallingDlg::OnTimer(UINT nIDEvent) 
// {
//     // TODO: Add your message handler code here and/or call default
//     if ( nIDEvent == 100 )
//     {
//        UpdateCallingImg();
//     }
//     
//     CDialog::OnTimer(nIDEvent);
// }


void CCallingDlg::HideCallingBox( )
{
   pDlg = NULL;
   KillTimer( g_wTimerID );
   EndDialog(1);
}