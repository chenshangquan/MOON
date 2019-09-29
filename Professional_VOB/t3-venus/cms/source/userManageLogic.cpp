// userManageLogic.cpp: implementation of the CUserManageLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cms.h"
#include "userManageLogic.h"
#include "msgBoxLogic.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUserManageLogic *CUserManageLogic::m_pLogic = NULL;

const String CUserManageLogic::m_strUserManage = "�û�����";           //
const String CUserManageLogic::m_strManagerModify = "����Ա�����޸�";

//controls

const String CUserManageLogic::m_strLstConfig = "Lst";                 //�����б�
const String CUserManageLogic::m_strLstUser = "LstUser";               //�û��б�

const String CUserManageLogic::m_dlgUserInfo = "DlgUserInfo";
const String CUserManageLogic::m_strEdtUserName = "EdtNote";       //�û���
const String CUserManageLogic::m_strEdtPswd = "EdtPswd";               //����
const String CUserManageLogic::m_strEdtNote = "EdtUserName";               //��ע 


//����Ա����
const String CUserManageLogic::m_dlgManagerInfo = "DlgEdtManager";     //����Ա����
const String CUserManageLogic::m_strEdtManagerName = "EdtUserName";    //�û���
const String CUserManageLogic::m_strEdtOriPswd = "EdtOriPswd";         //ԭ����
const String CUserManageLogic::m_strEdtNewPswd = "EdtNewPswd";         //������
const String CUserManageLogic::m_strEdtReNewPswd = "EdtReNewPswd";     //�ظ����� 

//scheme
const String  CUserManageLogic::m_schmShowUserConfig = "SchmShowUserManage";
const String  CUserManageLogic::m_schmShowUserLst = "SchmShowUserLst";
const String  CUserManageLogic::m_schmShowUserInfo = "SchmShowUserInfo"; 
const String  CUserManageLogic::m_schmNewUser = "SchmNewUser";
const String  CUserManageLogic::m_schmShowEdtState = "SchmEdtUser";
const String  CUserManageLogic::m_schmShowManagerModify = "SchmShowManagerInfo";


CUserManageLogic::CUserManageLogic():m_selUser(),
m_emModifyType( emModifyTpCheck )
{
    const_cast<String&>(m_strEdtUserName) = m_dlgUserInfo + "/" + m_strEdtUserName;
    const_cast<String&>(m_strEdtPswd) = m_dlgUserInfo + "/" + m_strEdtPswd;
    const_cast<String&>(m_strEdtNote) = m_dlgUserInfo + "/" + m_strEdtNote; 
    
    const_cast<String&>(m_strEdtManagerName) = m_dlgManagerInfo + "/" + m_strEdtManagerName;
    const_cast<String&>(m_strEdtOriPswd) = m_dlgManagerInfo + "/" + m_strEdtOriPswd;
    const_cast<String&>(m_strEdtNewPswd) = m_dlgManagerInfo + "/" + m_strEdtNewPswd; 
    const_cast<String&>(m_strEdtReNewPswd) = m_dlgManagerInfo + "/" + m_strEdtReNewPswd; 
    
    
}

CUserManageLogic::~CUserManageLogic()
{
    if ( m_pLogic != NULL )
    {   
        UnRegMsg();
        UnRegFunc();
        delete m_pLogic;
        m_pLogic = NULL;
    }
    
}

CUserManageLogic* CUserManageLogic::GetLogicPtr()
{
    if ( m_pLogic == NULL )
    {  
        m_pLogic = new CUserManageLogic();  
    }
    
    return m_pLogic;
}


void CUserManageLogic::RegMsg()
{     
    REG_MSG_HANDLER( UI_UMS_REFRESH_USER_LIST, CUserManageLogic::OnUserRefreshNotify, m_pLogic, CUserManageLogic );
    REG_MSG_HANDLER( UI_UMS_OPERATE_USER_RET, CUserManageLogic::OnUserModifyRsp, m_pLogic, CUserManageLogic );
     
    
}

void CUserManageLogic::UnRegMsg()
{
    //UNREG_MSGHANDLER(  UI_UMS_START_CONFTEMPLATE_RSP ); 
}

bool CUserManageLogic::RegCBFun()
{   	 
    REG_GOBAL_MEMBER_FUNC( "CUserManageLogic::InitWnd", CUserManageLogic::InitWnd, m_pLogic, CUserManageLogic ) ;  
    REG_GOBAL_MEMBER_FUNC( "CUserManageLogic::BtnSaveToFileClick", CUserManageLogic::BtnSaveToFileClick, m_pLogic, CUserManageLogic );
    
    
    REG_GOBAL_MEMBER_FUNC( "CUserManageLogic::ToUserLstIconClick", CUserManageLogic::ToUserLstIconClick, m_pLogic, CUserManageLogic ) ;  
    REG_GOBAL_MEMBER_FUNC( "CUserManageLogic::ToUserInfoIconClick", CUserManageLogic::ToUserInfoIconClick, m_pLogic, CUserManageLogic ) ;  
    REG_GOBAL_MEMBER_FUNC( "CUserManageLogic::BtnToUserConfigClick", CUserManageLogic::BtnToUserConfigClick, m_pLogic, CUserManageLogic ) ;  
    REG_GOBAL_MEMBER_FUNC( "CUserManageLogic::BtnToNewUserClick", CUserManageLogic::BtnToNewUserClick, m_pLogic, CUserManageLogic ) ;  
    REG_GOBAL_MEMBER_FUNC( "CUserManageLogic::BtnToEdtClick", CUserManageLogic::BtnToEdtClick, m_pLogic, CUserManageLogic ) ; 
    REG_GOBAL_MEMBER_FUNC( "CUserManageLogic::BtnToNewUserClick", CUserManageLogic::BtnToNewUserClick, m_pLogic, CUserManageLogic ) ; 
    REG_GOBAL_MEMBER_FUNC( "CUserManageLogic::BtnToSaveClick", CUserManageLogic::BtnToSaveClick, m_pLogic, CUserManageLogic ) ; 
    REG_GOBAL_MEMBER_FUNC( "CUserManageLogic::BtnToCancleClick", CUserManageLogic::BtnToCancleClick, m_pLogic, CUserManageLogic ) ; 
    REG_GOBAL_MEMBER_FUNC( "CUserManageLogic::BtnToDeleteClick", CUserManageLogic::BtnToDeleteClick, m_pLogic, CUserManageLogic ) ; 

    REG_GOBAL_MEMBER_FUNC( "CUserManageLogic::OnPswdEdtSetFocus", CUserManageLogic::OnPswdEdtSetFocus, m_pLogic, CUserManageLogic ) ; 
    
    
    
    REG_GOBAL_MEMBER_FUNC( "CUserManageLogic::OnUserConfigItemIcon", CUserManageLogic::OnUserConfigItemIcon, m_pLogic, CUserManageLogic ) ; 
    REG_GOBAL_MEMBER_FUNC( "CUserManageLogic::OnUserConfigItem", CUserManageLogic::OnUserConfigItem, m_pLogic, CUserManageLogic ) ; 

    REG_GOBAL_MEMBER_FUNC( "CUserManageLogic::OnUserLstItemIcon", CUserManageLogic::OnUserLstItemIcon, m_pLogic, CUserManageLogic ) ; 
    REG_GOBAL_MEMBER_FUNC( "CUserManageLogic::OnUserLstItem", CUserManageLogic::OnUserLstItem, m_pLogic, CUserManageLogic ) ; 
    
    return true;
}

bool CUserManageLogic::UnRegFunc()
{
    UN_REG_GOBAL_FUNC( "CUserManageLogic::InitWnd" );
    return true;
}


bool CUserManageLogic::InitWnd(  const IArgs & arg )
{   
    CWndLogicBase::InitWnd( arg );   
    InitConfigLst();
    UpdateDlg();
    return true;
}

void CUserManageLogic::Clear() 
{
    m_selUser.Empty();	
	if ( m_pWndTree != NULL )
    {   
		UIManagePtr->LoadScheme( "", m_pWndTree, "", false );
        UIManagePtr->ShowWindow( "", false, m_pWndTree );
	}
}

//��ʼ�����ò˵�
void CUserManageLogic::InitConfigLst()
{   
    TMenuItemInfo tMenu;
    tMenu.strItemFunc = "CUserManageLogic::OnUserConfigItem";
    ARRAY<String> vcItem;
    vcItem.push_back( "ImageItemUserConfig" );
    tMenu.m_pVctSubItem = &vcItem;
    
    
    ARRAY<TMenuItemInfo> menuLst; 
    
    tMenu.strTxt = m_strUserManage;
    menuLst.push_back( tMenu );
 
    //2011-8-15 ����Ŀǰums�������޸Ĺ���Ա���룬���������أ����Ժ��иĽ�����
//     tMenu.strTxt = m_strManagerModify;
//     menuLst.push_back( tMenu );
    
    Value_TouchListMenu val( &menuLst );
    UIManagePtr->SetPropertyValue( val, m_strLstConfig, m_pWndTree );
}


bool CUserManageLogic::BtnSaveToFileClick( const IArgs & arg )
{
    bool bRe = UIManagePtr->SaveToFile( g_stcStrUserManageDlg  );   
    return bRe;
}


/**	 
* ����:  �������ʾ�û��б��ͼ��
* @return   bool
* @remarks  
*/  
bool CUserManageLogic::ToUserLstIconClick( const IArgs & arg )
{  
    String strCaption;
    UIManagePtr->GetCaption( "StcTitle", strCaption, m_pWndTree);
    
    if ( strcmp(strCaption.c_str(), "�༭�û���Ϣ") ==0 )
    {
        String strName;
        UIManagePtr->GetCaption( m_strEdtUserName, strName,m_pWndTree);
        String strPswd;
        UIManagePtr->GetCaption( m_strEdtPswd,strPswd,m_pWndTree);
        //�иı䣬��ʾ�Ƿ���Ҫ����
        if ( strName != m_selUser.GetName() || strPswd != m_selUser.GetPassword() )
        {
            CString strMsg = "�û���Ϣ���޸ģ��Ƿ񱣴�?";
            Args_MsgBox argMsg;
            argMsg.pOwnerWnd = UIManagePtr->GetWindowPtr( "UserManageDlg" );
            int nResult = MSG_BOX( strMsg, TRUE, &argMsg);
            if ( IDOK == nResult )
            {
               if (BtnToSaveClick( arg ))
               {
                   return true;
               }
               else
               {
                   return false;
               }
            }
        }      
    }

    UIManagePtr->LoadScheme( m_schmShowUserLst, m_pWndTree );    

    return true;
}




/**	 
* ����:  �������ʾ�û���Ϣ��ͼ��
* @return   bool
* @remarks  
*/  
bool CUserManageLogic::ToUserInfoIconClick( const IArgs & arg )
{  
    UIManagePtr->LoadScheme( m_schmShowUserInfo, m_pWndTree ); 
    UpdateUserInfo();
    return true;
}


/**	 
* ����:  �����ת���û����ý����button
* @return   bool
* @remarks  
*/  
bool CUserManageLogic::BtnToUserConfigClick( const IArgs & arg )
{   
    m_selUser.Empty();
    UIManagePtr->LoadScheme( m_schmShowUserConfig, m_pWndTree );
    return true;
}



/**	 
* ����:  ������½��û���button
* @return   bool
* @remarks  
*/  
bool CUserManageLogic::BtnToNewUserClick( const IArgs & arg )
{   
    TplArray<CUserFullInfo>*  pUserLst = BusinessManagePtr->GetUserList();
    if ( pUserLst != NULL )
    {
        if ( pUserLst->Size() >= MAX_USER_COUNT )
        {
            Args_MsgBox arg;
            arg.pOwnerWnd = UIManagePtr->GetWindowPtr( g_stcStrUserManageDlg );
            CString str;
            str.Format( "�û������Ѵﵽ���ֵ %d , ��ɾ�������û��������" , MAX_USER_COUNT );
            MSG_BOX( str, FALSE, &arg );
            return false;
        }
    }
    
    m_selUser.Empty();
    UIManagePtr->LoadScheme( m_schmShowEdtState, m_pWndTree ); 
    UIManagePtr->LoadScheme( m_schmNewUser, m_pWndTree ); 
    UIManagePtr->LoadScheme("SchmNewUser",m_pWndTree, m_strEdtUserName ); 
    m_emModifyType = emModifyTpNew;
    UpdateUserInfo();
    return true;
}



/**	 
* ����:  ����˱༭�û���button
* @return   bool
* @remarks  
*/  
bool CUserManageLogic::BtnToEdtClick( const IArgs & arg )
{ 
    UIManagePtr->LoadScheme( m_schmShowEdtState, m_pWndTree );
    m_emModifyType = emModifyTpUpdate;
    return true;
}


/**	 
* ����:  ����˱����û���Ϣ��btn
* @return   bool
* @remarks  
*/  
bool CUserManageLogic::BtnToSaveClick( const IArgs & arg )
{  
    String str;
    Args_MsgBox msgArg; 
    
    if ( emModifyManager == m_emModifyType )
    {   
        msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( m_dlgManagerInfo, m_pWndTree );

        UIManagePtr->GetCaption( m_strEdtOriPswd,str,m_pWndTree); 

        CUserFullInfo cUser;
        cUser.SetPassword( const_cast<char*>(str.c_str())  );
       
        if ( !m_selUser.IsPassWordEqual( cUser.GetPassword()) ) 
        { 
            MSG_BOX( "ԭ�����������", FALSE, &msgArg );
			UIManagePtr->SetFocus( m_strEdtOriPswd, m_pWndTree );			
            return false;
        }
        
        UIManagePtr->GetCaption( m_strEdtNewPswd,str,m_pWndTree);
        
        String str2;
        UIManagePtr->GetCaption( m_strEdtReNewPswd,str2,m_pWndTree);
        if ( str != str2 )
        {    
            MSG_BOX( "��ȷ��������������һ��", FALSE, &msgArg );
			UIManagePtr->SetFocus( m_strEdtReNewPswd, m_pWndTree );
            return false;
        }
        
        m_selUser.SetPassword( const_cast< char * >(str.c_str()) );
        u16 wRe = BusinessManagePtr->UpdateUser( m_selUser ); 
        if ( wRe != NO_ERROR )
        {
            CString strErr = GET_ERR_STRING( wRe );
            Args_MsgBox msgArg;
            msgArg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;
            MSG_BOX( strErr, FALSE, &msgArg);
            return false;
        }
        m_emModifyType = emModifyTpCheck; 
        
        UIManagePtr->LoadScheme( m_schmShowUserConfig, m_pWndTree );
    }
    else
    {
        String strName;
        msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( m_dlgUserInfo, m_pWndTree );
        UIManagePtr->GetCaption( m_strEdtUserName, strName,m_pWndTree);
        if ( strName.empty() )
        {
            Args_MsgBox msgArg;
            msgArg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;
            MSG_BOX( "�û�������Ϊ��", FALSE, &msgArg);
			UIManagePtr->SetFocus( m_strEdtUserName, m_pWndTree );
            return false;
        }

       
        if ( strName.find(" ") != -1 )
        {
            Args_MsgBox msgArg;
            msgArg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;
            MSG_BOX( "�û����в����Ժ��пո�", FALSE, &msgArg);
			UIManagePtr->SetFocus( m_strEdtUserName, m_pWndTree );
            return false;
        }

		if ( strName.compare(MANAGER_USER) == 0 )
		{
			Args_MsgBox msgArg;
            msgArg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;
            MSG_BOX( "������ӹ���Ա�û�", FALSE, &msgArg);
			UIManagePtr->SetFocus( m_strEdtUserName, m_pWndTree );
            return false;
		}

        
        
        String strPswd;
        UIManagePtr->GetCaption( m_strEdtPswd,strPswd,m_pWndTree);
        if ( strPswd.empty() )
        {
            Args_MsgBox msgArg;
            msgArg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;
            MSG_BOX( "���벻��Ϊ��", FALSE, &msgArg);
			UIManagePtr->SetFocus( m_strEdtPswd, m_pWndTree );
            return false;
        }
     
        
        
        
        String strNote;
        UIManagePtr->GetCaption( m_strEdtNote, strNote,m_pWndTree);


        //�иı䣬��Ҫ����
        if ( strName != m_selUser.GetName() || strPswd != m_selUser.GetPassword() 
             || strNote != m_selUser.GetDiscription() )
        {
            m_selUser.SetName( const_cast< char * >(strName.c_str()) );
            
            if ( strPswd != m_selUser.GetPassword() )
            {
                m_selUser.SetPassword( const_cast< char * >(strPswd.c_str()) );
            }
            
            m_selUser.SetDiscription( const_cast< char * >(strNote.c_str()) );
            
            u16 wRe = NO_ERROR;
            if ( m_emModifyType == emModifyTpNew )
            {
                wRe = BusinessManagePtr->AddUser( m_selUser );
            }
            else
            {
                wRe = BusinessManagePtr->UpdateUser( m_selUser );
            } 
            
            if ( wRe != NO_ERROR )
            {
                CString strErr = GET_ERR_STRING( wRe );
                Args_MsgBox msgArg;
                msgArg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;
                MSG_BOX( strErr, FALSE, &msgArg);
                return false;
            }
        }

       
        m_emModifyType = emModifyTpCheck; 
        
        UIManagePtr->LoadScheme( m_schmShowUserLst, m_pWndTree );
    }
    
    
    return true;
}



/**	 
* ����:  �����ȡ���༭�û���Ϣ��btn
* @return   bool
* @remarks  
*/  
bool CUserManageLogic::BtnToCancleClick( const IArgs & arg )
{  
    if ( m_emModifyType == emModifyTpNew )
    {
        UIManagePtr->LoadScheme( m_schmShowUserLst, m_pWndTree ); 
    }
    else
    {
        UIManagePtr->SetCaption( m_strEdtUserName, m_selUser.GetName(), m_pWndTree );
        UIManagePtr->SetCaption( m_strEdtPswd, m_selUser.GetPassword(), m_pWndTree );
        UIManagePtr->LoadScheme( m_schmShowUserInfo, m_pWndTree );
    }
    return true;
}




/**	 
* ����:  �����ɾ���û���Ϣ��btn
* @return   bool
* @remarks  
*/  
bool CUserManageLogic::BtnToDeleteClick( const IArgs & arg )
{   
    CString strMsg = "�Ƿ�ɾ�����û�?";
    Args_MsgBox argMsg;
    argMsg.pOwnerWnd = UIManagePtr->GetWindowPtr( "UserManageDlg" );
    int nResult = MSG_BOX( strMsg, TRUE, &argMsg);
    if ( nResult == IDOK )
    {
        u16 wRe = BusinessManagePtr->DeleteUser( m_selUser );
        if ( wRe != NO_ERROR )
        {
            Args_MsgBox argMsg;
            argMsg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;
            CString strErr = GET_ERR_STRING ( wRe );
            MSG_BOX( strErr, FALSE, &argMsg);
            return false;
        }
        
        UIManagePtr->LoadScheme( m_schmShowUserLst, m_pWndTree );
        return true;
    }
    else
    {
        return false;
    }

}



bool CUserManageLogic::OnPswdEdtSetFocus( const IArgs & arg )
{
    UIManagePtr->SetCaption( m_strEdtPswd, "", m_pWndTree );
    return true;
}
/**	 
* ����:  ������û�����item
* @return   bool
* @remarks  
*/  
bool CUserManageLogic::OnUserConfigItemIcon( const IArgs & arg )
{   
    ZeroMemory( &m_selUser, sizeof(CUserFullInfo));
    if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast< const Args_ClickItemInfo*>(&arg))
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetParentItem()->GetItemData();        
        if ( const Data_Menu *pItemInfo = dynamic_cast<const Data_Menu*>( pBaseItem->GetUserData() )) 
        {    
            ShowSubDlg( pItemInfo->m_tMenuInfo.strTxt );
        }
    }
    return true;
}


bool CUserManageLogic::OnUserConfigItem( const IArgs & arg )
{
    ZeroMemory( &m_selUser, sizeof(CUserFullInfo));
    if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast< const Args_ClickItemInfo*>(&arg))
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetItemData();        
        if ( const Data_Menu *pItemInfo = dynamic_cast<const Data_Menu*>( pBaseItem->GetUserData() )) 
        {    
            ShowSubDlg( pItemInfo->m_tMenuInfo.strTxt );
        }
    }
    return true;
}


void CUserManageLogic::ShowSubDlg( String strSubDlgName )
{
    if ( strSubDlgName == m_strUserManage )
    {     
        UIManagePtr->LoadScheme(m_schmShowUserLst, m_pWndTree);
        m_emModifyType = emModifyTpCheck;
    }
    else
    {
        m_emModifyType = emModifyManager;
        CUserFullInfo * pUser = BusinessManagePtr->GetUserByName( MANAGER_USER );
        if ( pUser != NULL )
        {
            m_selUser.SetActor( pUser->GetActor()) ;
            m_selUser.SetName( pUser->GetName()) ;
            m_selUser.SetEncryptedPassword( pUser->GetPassword()) ;
            m_selUser.SetDiscription( pUser->GetDiscription()) ; 
            m_selUser.SetFullName( pUser->GetFullName());
        }
        
        UpdateManageDlg();
        UIManagePtr->LoadScheme(m_schmShowManagerModify, m_pWndTree);
    } 
}



bool CUserManageLogic::OnUserLstItemIcon( const IArgs & arg )
{
    if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast< const Args_ClickItemInfo*>(&arg))
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetParentItem()->GetItemData();        
        if ( const Data_User *pItemInfo = dynamic_cast<const Data_User*>( pBaseItem->GetUserData() )) 
        {   
            m_selUser = pItemInfo->m_cUser;
           
            UIManagePtr->LoadScheme(m_schmShowUserInfo, m_pWndTree); 
            UpdateUserInfo();
        } 
    }
    return true;
}



bool CUserManageLogic::OnUserLstItem( const IArgs & arg )
{
    if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast< const Args_ClickItemInfo*>(&arg))
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetItemData();        
        if ( const Data_User *pItemInfo = dynamic_cast<const Data_User*>( pBaseItem->GetUserData() )) 
        {   
            m_selUser = pItemInfo->m_cUser;
            
            UIManagePtr->LoadScheme(m_schmShowUserInfo, m_pWndTree); 
            UpdateUserInfo();
        } 
    }
    return true;
}



HRESULT CUserManageLogic::OnUserRefreshNotify( WPARAM wparam, LPARAM lparam )
{
    UpdateUserLst();
    return NO_ERROR;
}

/*
#define UM_LOGIN_NOUSER		19001
#define UM_LOGIN_ERRPSW		19002
#define UM_ACTOR_NOTMATCH	19003
#define UM_USER_DUPLICATE	19004
#define UM_USER_NOTEXIST	19005
#define UM_NOT_ENOUGHMEM	19006
#define UM_ACTOR_ONLY		19007
#define UM_OPERATE_NOTPERMIT    19008
*/
HRESULT CUserManageLogic::OnUserModifyRsp( WPARAM wparam, LPARAM lparam )
{   
  
    if ( lparam != NO_ERROR )
    {        
        CString strErr = "";
        switch(lparam)
        {
        case UM_LOGIN_NOUSER:
            strErr = "���û�������";
            break;
        case UM_LOGIN_ERRPSW:
            strErr = "�û����в����Ժ��пո�" ;//"�������";
            break;
        case UM_ACTOR_NOTMATCH:
            strErr = "�û�Ȩ�޲�ƥ��";
            break;
        case UM_USER_DUPLICATE:
            strErr = "���û����Ѵ���";
            break;
        case UM_USER_NOTEXIST:
            strErr = "���û�������";
            break;
        case UM_NOT_ENOUGHMEM:
            strErr = "�û������Ѵﵽ���ֵ";
            break;
        case UM_ACTOR_ONLY:
            strErr = "";
            break;

        case UM_OPERATE_NOTPERMIT:
             strErr = "�޲���Ȩ��";
             break;
        default:
            strErr = "";//"δ֪����";//2012-8-7 SEʯ�ľ�ȷ��δ֪��������ʾ by yjj
             break; 

        }

        CString msg;
        if ( strErr.IsEmpty() )
        {
            msg = "�����û�ʧ��";
            
        }
        else
        {
            msg = "�����û�ʧ��: " + strErr;
        }

        if ( UIManagePtr->IsVisible( g_stcStrUserManageDlg  ) )
        {   
            Args_MsgBox arg;
            arg.pOwnerWnd = UIManagePtr->GetWindowPtr(g_stcStrUserManageDlg );
           
            MSG_BOX(msg, FALSE,&arg);
          
        }
        else
        {    
            ShowPopMsg(msg); 
        }
 
    }
    return NO_ERROR;
}

void CUserManageLogic::UpdateUserLst()
{   
    if( m_pWndTree != NULL )
    {
        TplArray<CUserFullInfo>* pUserLst = BusinessManagePtr->GetUserList();
        Value_TouchListUser valUser(pUserLst);
        
        ARRAY<String > arryItem;
        arryItem.push_back("ImageItemUserLstToInfo");
        valUser.m_pVctSubItem = &arryItem;
        
        valUser.m_strClickItemFunc = "CUserManageLogic::OnUserLstItem";
        UIManagePtr->SetPropertyValue( valUser, m_strLstUser,m_pWndTree  );
    }
    
}



void CUserManageLogic::UpdateUserInfo()
{
    //m_selUser
    if ( m_pWndTree != NULL )
    {   
        if ( m_selUser.IsEmpty() )
        {
            UIManagePtr->SetCaption( m_strEdtUserName, "", m_pWndTree );
            UIManagePtr->SetCaption( m_strEdtPswd, "", m_pWndTree );
            UIManagePtr->SetCaption( m_strEdtNote, "", m_pWndTree );
        }
        else
        {
            UIManagePtr->SetCaption( m_strEdtUserName, m_selUser.GetName(), m_pWndTree );
            UIManagePtr->SetCaption( m_strEdtPswd, m_selUser.GetPassword(), m_pWndTree );
            UIManagePtr->SetCaption( m_strEdtNote, m_selUser.GetDiscription(), m_pWndTree );
        }
        
    }
    
}





void CUserManageLogic::UpdateDlg()
{
    UpdateUserInfo();
    UpdateUserLst();
    
}


void CUserManageLogic::UpdateManageDlg()
{
    //����Ա����
    if ( m_pWndTree != NULL )
    {
        UIManagePtr->SetCaption( m_strEdtManagerName, m_selUser.GetName(), m_pWndTree );
        UIManagePtr->SetCaption( m_strEdtOriPswd, "", m_pWndTree );
        UIManagePtr->SetCaption( m_strEdtNewPswd, "", m_pWndTree );
        UIManagePtr->SetCaption( m_strEdtReNewPswd, "", m_pWndTree );
        
    }
    
}


