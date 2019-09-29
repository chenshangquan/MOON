// msgBoxLogic.cpp: implementation of the CMsgBoxLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cms.h"
#include "msgBoxLogic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMsgBoxLogic *CMsgBoxLogic::m_pLogic = NULL;
const String CMsgBoxLogic::m_strEdtMsg = "EdtMsg";
//IArgs CMsgBoxLogic::m_args;

CMsgBoxLogic::CMsgBoxLogic():m_pOkFunc(NULL),
                              m_pCancleFunc(NULL),
                              m_pArgs(NULL),
							  m_pOwnerWnd(NULL),
                              m_IsDisConnectBoxShow(FALSE)
{
   const_cast<String&>(m_strEdtMsg) = g_stcStrMsgBox + "/" + m_strEdtMsg;
}

CMsgBoxLogic::~CMsgBoxLogic()
{
    if ( m_pLogic != NULL )
    {   
        UnRegMsg();
        UnRegFunc();
        delete m_pLogic;
        m_pLogic = NULL; 
    }
}

CMsgBoxLogic* CMsgBoxLogic::GetLogicPtr()
{
    if ( m_pLogic == NULL )
    {  
        m_pLogic = new CMsgBoxLogic();   
    }
    
    return m_pLogic;
}

void CMsgBoxLogic::RegMsg()
{    
    
    
}

void CMsgBoxLogic::UnRegMsg()
{
    
}

bool CMsgBoxLogic::RegCBFun()
{   	 
    REG_GOBAL_MEMBER_FUNC( "CMsgBoxLogic::InitWnd", CMsgBoxLogic::InitWnd, m_pLogic, CMsgBoxLogic);
    REG_GOBAL_MEMBER_FUNC( "CMsgBoxLogic::OnBtnOkClick", CMsgBoxLogic::OnBtnOkClick, m_pLogic, CMsgBoxLogic);
    REG_GOBAL_MEMBER_FUNC( "CMsgBoxLogic::OnBtnCancleClick", CMsgBoxLogic::OnBtnCancleClick, m_pLogic, CMsgBoxLogic);
    REG_GOBAL_MEMBER_FUNC( "CMsgBoxLogic::BtnSaveToFileClick", CMsgBoxLogic::BtnSaveToFileClick, m_pLogic, CMsgBoxLogic ); 
    REG_GOBAL_MEMBER_FUNC( "CMsgBoxLogic::OnPostDomodal", CMsgBoxLogic::OnPostDomodal, m_pLogic, CMsgBoxLogic ); 
      
    return true;
}

bool CMsgBoxLogic::UnRegFunc()
{
    //	UN_REG_GOBAL_FUNC( "CConftempEdtLogic::InitWnd" );
    return true;
}

    
bool CMsgBoxLogic::InitWnd(  const IArgs & arg )
{   
    CWndLogicBase::InitWnd( arg ); 
 
    return true;
}

void CMsgBoxLogic::HideWindow()
{   
    m_IsDisConnectBoxShow = FALSE;
	UIFACTORYMGR_PTR->Endmodal( IDCANCEL, g_stcStrMsgBox );
	if ( m_pOwnerWnd != NULL )
	{
		m_pOwnerWnd->SetFocus();
	}
}
 
 


int CMsgBoxLogic::InitInfo(CString strMsg, BOOL32 bShowCancleBtn ,IArgs *pArgs)
{
	CMsgDispatch::SendMessage( WM_CMS_HIDE_VEDIO, 0, 0 );
	m_pOwnerWnd = NULL; 
    if (  Args_MsgBox *pMsgArg = dynamic_cast< Args_MsgBox * > (pArgs) )
    {
        Value_WindowOwer val;
        val.pWnd = pMsgArg->pOwnerWnd;
        UIManagePtr->SetPropertyValue(val,g_stcStrMsgBox);
        
        if ( pMsgArg->pOwnerWnd != NULL && IsWindow( pMsgArg->pOwnerWnd->GetSafeHwnd() ) )
        {
            m_pOwnerWnd = pMsgArg->pOwnerWnd;
        } 
    }  
	
    if ( bShowCancleBtn )
    {  
        UIManagePtr->SetCaption(m_strEdtMsg, (LPCSTR)strMsg  ,m_pWndTree);
		
        UIManagePtr->LoadScheme( "SchmMsgBoxShowCancleBtn", NULL, g_stcStrMsgBox );
    }
    else
    {   
        UIManagePtr->SetCaption(m_strEdtMsg, (LPCSTR)strMsg  ,m_pWndTree);
        UIManagePtr->LoadScheme( "SchmMsgBoxNotShowCancleBtn", NULL, g_stcStrMsgBox ); 
    }

    return UIFACTORYMGR_PTR->Domodal( g_stcStrMsgBox );
}


void CMsgBoxLogic::InitPostInfo(CString strMsg, BOOL32 bShowCancleBtn ,IArgs *pArgs)
{
    CMsgDispatch::SendMessage( WM_CMS_HIDE_VEDIO, 0, 0 );
    m_pOwnerWnd = NULL; 
    if (  Args_MsgBox *pMsgArg = dynamic_cast< Args_MsgBox * > (pArgs) )
    {
        Value_WindowOwer val;
        val.pWnd = pMsgArg->pOwnerWnd;
        UIManagePtr->SetPropertyValue(val,g_stcStrMsgBox);
        
        if ( pMsgArg->pOwnerWnd != NULL && IsWindow( pMsgArg->pOwnerWnd->GetSafeHwnd() ) )
        {
            m_pOwnerWnd = pMsgArg->pOwnerWnd;
        } 
    }  
    
    if ( bShowCancleBtn )
    {  
        UIManagePtr->SetCaption(m_strEdtMsg, (LPCSTR)strMsg  ,m_pWndTree);
        
        UIManagePtr->LoadScheme( "SchmMsgBoxShowCancleBtn", NULL, g_stcStrMsgBox );
    }
    else
    {   
        UIManagePtr->SetCaption(m_strEdtMsg, (LPCSTR)strMsg  ,m_pWndTree);
        UIManagePtr->LoadScheme( "SchmMsgBoxNotShowCancleBtn", NULL, g_stcStrMsgBox ); 
    }

    CWnd* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( g_stcStrMsgBox );

    if ( pWnd != NULL )
    {   
        pWnd->PostMessage( WM_POST_DOMODAL );
    }
     
    //return UIFACTORYMGR_PTR->Domodal( g_stcStrMsgBox );
}

bool CMsgBoxLogic::OnPostDomodal( const IArgs & arg )
{
    return UIFACTORYMGR_PTR->Domodal( g_stcStrMsgBox );
}


bool CMsgBoxLogic::OnBtnOkClick( const IArgs & arg  )
{   
	//2013.1.29 结束domodal
	UIFACTORYMGR_PTR->Endmodal( IDOK , g_stcStrMsgBox );  

	if ( m_pOwnerWnd != NULL )
	{	 
 		m_pOwnerWnd->SetFocus();
	}
    return true;
}

bool CMsgBoxLogic::OnBtnCancleClick( const IArgs & arg  )
{
	//2013.1.29 结束domodal
	UIFACTORYMGR_PTR->Endmodal( IDCANCEL, g_stcStrMsgBox );
 
    if ( m_pOwnerWnd != NULL )
	{
		m_pOwnerWnd->SetFocus();
	}
    return true;
}

bool CMsgBoxLogic::BtnSaveToFileClick( const IArgs & arg )
{
    return  UIManagePtr->SaveToFile( g_stcStrMsgBox  );   
}



//是否是断链时的提示窗口
void CMsgBoxLogic::SetDisCntMsgBoxFlag( BOOL32 bDIsConnectMsgBox )
{
    m_IsDisConnectBoxShow = bDIsConnectMsgBox;
}

BOOL32 CMsgBoxLogic::IsDisCntMsgBoxShow()
{
    return m_IsDisConnectBoxShow; 
}