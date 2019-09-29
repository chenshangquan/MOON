// pollLstManage.cpp: implementation of the CPollLstManage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cms.h"
#include "pollLstManage.h"
#include "TouchListProperty.h" 
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
  CPollLstManage* CPollLstManage::m_stcPThis = NULL;
// const String CPollLstManage::m_strDlgPollManageMenu = "DlgPollManageDlg";
// const String CPollLstManage::m_strLstPollManage = "LstManageMenu";
CPollLstManage::CPollLstManage():
                           m_pTempEdtLog(NULL),
                           m_pTemp(NULL),
                           m_wCnsID(INVALID_WORD)
{

}

CPollLstManage::~CPollLstManage()
{

}

CPollLstManage*CPollLstManage::GetPollLstManage()
{
   if ( m_stcPThis == NULL )
   {
       m_stcPThis = new CPollLstManage();
   }

   return m_stcPThis;
}
 
void CPollLstManage::Init( TCMSConfTemplate* pTemp, CConftempEdtLogic *pLogic )
{
    m_pTemp = pTemp;
    m_pTempEdtLog = pLogic;

//     ARRAY<TMenuItemInfo> menList;
//     TMenuItemInfo t;
//     t.strTxt = "置顶";
//     t.strItemFunc = "CPollLstManage::SetCnsTop";
//     menList.push_back(t);
// 
//     t.strTxt = "上移";
//     t.strItemFunc = "CPollLstManage::SetCnsUp";
//     menList.push_back(t);
// 
//     t.strTxt = "下移";
//     t.strItemFunc = "CPollLstManage::SetCnsDown";
//     menList.push_back(t);
// 
//     t.strTxt = "置底";
//     t.strItemFunc = "CPollLstManage::SetCnsBottom";
//     menList.push_back(t);
// 
//     t.strTxt = "移除";
//     t.strItemFunc = "CPollLstManage::DeletePollCns";
//     menList.push_back(t); 
//     Value_TouchListMenu menu(&menList);
//     UIManagePtr->SetPropertyValue(menu,"PollLstManageMenu/LstManageMenu");
    
    Value_WindowOwer owerVal;
    owerVal.pWnd = UIManagePtr->GetWindowPtr( g_stcStrConftempEdtDlg );
    UIManagePtr->SetPropertyValue(owerVal, "PollLstManageMenu");


    //单击了poll list的条目
   // REG_GOBAL_MEMBER_FUNC( "CPollLstManage::OnClickPollItem", CPollLstManage::OnClickPollItem, m_stcPThis, CPollLstManage ) ; 
    
    //menu 单击事件
    REG_GOBAL_MEMBER_FUNC( "CPollLstManage::DeletePollCns", CPollLstManage::DeletePollCns, m_stcPThis, CPollLstManage ) ; 
    REG_GOBAL_MEMBER_FUNC( "CPollLstManage::ClearPollLst", CPollLstManage::ClearPollLst, m_stcPThis, CPollLstManage ) ;
    REG_GOBAL_MEMBER_FUNC( "CPollLstManage::SetCnsTop", CPollLstManage::SetCnsTop, m_stcPThis, CPollLstManage ) ;
    REG_GOBAL_MEMBER_FUNC( "CPollLstManage::SetCnsBottom", CPollLstManage::SetCnsBottom, m_stcPThis, CPollLstManage ) ;
    REG_GOBAL_MEMBER_FUNC( "CPollLstManage::SetCnsUp", CPollLstManage::SetCnsUp, m_stcPThis, CPollLstManage ) ;
    REG_GOBAL_MEMBER_FUNC( "CPollLstManage::SetCnsDown", CPollLstManage::SetCnsDown, m_stcPThis, CPollLstManage ) ;
}

void CPollLstManage::ShowPollLstManage( BOOL bShow /*= TRUE*/ )
{
    if ( m_pTempEdtLog == NULL  )
    {
        PrtMsg(0, emEventTypeCmsWindow, "------[CPollLstManage::ShowWindow] m_pTempEdtLog  = NULL ,and return ");
        return;
    }

   if ( bShow )
   {   PrtMsg(0, emEventTypeCmsWindow, "------[CPollLstManage::ShowWindow] show ");
       //更新显示
       if ( m_pTemp !=  NULL  )
       {
            if ( m_wCnsID ==  m_pTemp->m_tTurnList.m_awList[0] )
            { //禁用上移和置顶 
                
                UIManagePtr->LoadScheme("SchmDisableUp", NULL ,  "PollLstManageMenu");
            }
            else 
            {
                UIManagePtr->LoadScheme("SchmEnableUp", NULL , "PollLstManageMenu");
            }
            
            int max = m_pTemp->m_tTurnList.m_wNum -1;
            if ( m_wCnsID == m_pTemp->m_tTurnList.m_awList[max]  )
            {//禁用下移和置底

                UIManagePtr->LoadScheme("SchmDisableDown", NULL ,  "PollLstManageMenu");
            }
            else 
            {
                UIManagePtr->LoadScheme("SchmEnableDown", NULL , "PollLstManageMenu");
            } 
           
       } 
       
       UIManagePtr->ShowWindow( "PollLstManageMenu" );
   }
   else
   {
       UIManagePtr->ShowWindow( "PollLstManageMenu",FALSE );
   }
}

 

//删除列表的cns
bool  CPollLstManage::DeletePollCns(const IArgs &args )
{    
    if ( m_pTemp !=  NULL && m_pTempEdtLog != NULL )
   {
       u16 re = m_pTemp->DeletePollCns(m_wCnsID);
       if ( re!= NO_ERROR )
       {
           HANDLE_ERROR(re);
           return false;
        }
       m_pTempEdtLog->UpdateTempInfoDlg();
   } 

    ShowPollLstManage( FALSE );
    return true;
}

//清空轮询列表
bool CPollLstManage::ClearPollLst(const IArgs &args )
{
    if ( m_pTemp !=  NULL && m_pTempEdtLog != NULL )
    {
        return m_pTemp->ClearPollLst( );
        m_pTempEdtLog->UpdateTempInfoDlg();
    } 
    return true;
}

 

//把CNS 置顶
bool CPollLstManage::SetCnsTop(const IArgs &args )
{
    if ( m_pTemp !=  NULL && m_pTempEdtLog != NULL )
    {
        u16 re = m_pTemp->TopPollCns(m_wCnsID);
        if ( re!= NO_ERROR )
        {
            HANDLE_ERROR(re);
            return false;
        }
         
        m_pTempEdtLog->UpdateTempInfoDlg();
    } 

    ShowPollLstManage(FALSE);
    return true;
}

//cns 置底
bool CPollLstManage::SetCnsBottom(const IArgs &args )
{
    if ( m_pTemp !=  NULL && m_pTempEdtLog != NULL )
    {
        u16 re = m_pTemp->BottomPollCns(m_wCnsID);
        if ( re!= NO_ERROR )
        {
            HANDLE_ERROR(re);
            return false;
        }
        m_pTempEdtLog->UpdateTempInfoDlg();
    } 
    ShowPollLstManage(FALSE);
    return true;
}

//cns上移
bool CPollLstManage::SetCnsUp( const IArgs &args )
{
    if ( m_pTemp !=  NULL && m_pTempEdtLog != NULL )
    {
        u16 re = m_pTemp->UpPollCns(m_wCnsID);
        if ( re!= NO_ERROR )
        {
            HANDLE_ERROR(re); 
            return false;
        }
        m_pTempEdtLog->UpdateTempInfoDlg();
    } 
    ShowPollLstManage(FALSE);
    return true;
}

//cns下移
bool CPollLstManage::SetCnsDown(const IArgs &args )
{
    if ( m_pTemp !=  NULL && m_pTempEdtLog != NULL )
    {
        u16 re = m_pTemp->DownPollCns(m_wCnsID);
        if ( re!= NO_ERROR )
        {
            HANDLE_ERROR(re); 
            return false;
        }
        m_pTempEdtLog->UpdateTempInfoDlg();
    } 
    ShowPollLstManage(FALSE);
    return true;
}

u16 CPollLstManage::GetCnsIDFrmItem(const IArgs &args)
{
    if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast<const Args_ClickItemInfo*>(&args) )
    {
        const IData *pIData = pClickInfo->m_pClickList->GetParentItem()->GetItemData()->GetUserData();
        if ( const Data_CnsID *pData = dynamic_cast<const Data_CnsID *>(pIData) )
        {
             return pData->m_wData;
        }
    }

    return INVALID_WORD;
}

//单击了轮询列表的某个条目
// bool CPollLstManage::OnClickPollItem(const IArgs &args )
// {  
//     if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast<const Args_ClickItemInfo*>(&args) )
//     {
//         const IData *pIData = pClickInfo->m_pClickList->GetParentItem()->GetItemData()->GetUserData();
//         if ( const Data_CnsID *pData = dynamic_cast<const Data_CnsID *>(pIData) )
//         {
//             m_wCnsID = pData->m_wData;
//             CRect rect = const_cast<CRect&>(pClickInfo->m_rcFrame);
//             
//             //在此rect的左下角显示弹出菜单 
//             Value_WindowPos val; 
//             val.nX = rect.left;
//             val.nY = rect.top;
//             UIManagePtr->SetPropertyValue(val,m_strDlgPollManageMenu);
//             UIManagePtr->ShowWindow(m_strDlgPollManageMenu);
//         }
//     }
//     return true;
// }